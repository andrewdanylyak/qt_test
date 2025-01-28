/**
 ******************************************************************************
 * @file    DtProtocol
 * @date    21.11.2024
 * @author  Georgiy Lutsenko <georgiy.lutsenko@droid-technologies.com>
 * @brief
 ******************************************************************************
 *
 * COPYRIGHT(c) 2022 Droid-Technologies LLC
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *   3. Neither the name of Droid-Technologies LLC nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************
 */

#ifndef DT_PROTOCOL_H
#define DT_PROTOCOL_H

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <functional>
#include <vector>
#include <iostream>

#include "DtCRC.h"
#include "DtFifo.h"

namespace Dt {

#define DT_PROTOCOL_FRAME_MTU               100U //
#define  CMD_ID_SIZE                        1u

enum class DtBuffType {
    kRx,
    kTx,
};

enum class DtRoleType {
    kMaster,
    kSlave,
};

enum class DtFrameType {
    kFrameTypeFirst                = 0,
    kFrameTypeConsecutive          = 1,
    kFrameTypeLast                 = 2,
    kFrameTypeSingle               = 3
};

enum class DtProtocolAckEnum {
    kProtocolAck_OK            = 0x00,
    kProtocolAck_SyncError     = 0x01,
    kProtocolAck_BadCRC        = 0x02,
    kProtocolAck_MissingFrame  = 0x03,
    kProtocolAck_OutOfMemory   = 0x04,
    kProtocolAck_None          = 0xFF,
};

enum class DtFrameStatusEnum {
    kFrameWaitingHeader,
    kFrameWaitingData,
    kFrameCompleted
};

#pragma pack(push, 1)
typedef struct
{
    struct
    {
        uint8_t syncBytes[2];               // Synchronization bytes
        uint16_t sn             : 12;       // Sequence number
        uint16_t spec           : 2;        // Frame specification
        uint16_t type           : 2;        // Packet Type
        uint8_t length;                     // The length of the following data bytes
    } header;
    uint8_t data[DT_PROTOCOL_FRAME_MTU];    // Data of the frame
    uint16_t crc;                           // CRC16
} DtFrame_t;
#pragma pack(pop)

typedef struct
{
    uint8_t* buffer;
    uint32_t capacity;
    uint32_t size;
    uint16_t sn;
    DtFrame_t frame;
    DtFrameStatusEnum status;
} DtProtocolRx_t;

typedef struct
{
    uint8_t* buffer;
    uint32_t capacity;
    uint32_t size;
    uint32_t offset;
    uint16_t sn;
    bool firstFrame;
    bool access;
    DtFrame_t frame;
} DtProtocolTx_t;

typedef struct {
    uint8_t commandId;
    std::function<void(const uint8_t* pData , size_t size)> commandFunc;
} DtProtocolCommand_t;

class DtProtocol {
public:
    DtProtocol(DtRoleType role, uint8_t* pRxBuff, uint32_t rxSize, uint8_t* pTxBuff, uint32_t txSize);

    typedef void (*AckCallback_t)(DtProtocolAckEnum ack);
    typedef void (*TimeoutCallback_t)(void);
    typedef uint32_t (*GetTimeStamp_t)(void);

    typedef void (*DtProtocolDataHandler_t)(void); // for data parsing

    void setTimeoutCallback(TimeoutCallback_t handler);
    void setAckCallback(AckCallback_t handler);
    void setFuncForGetTimeStamp(GetTimeStamp_t handler);

    bool send(DtFifo* pTxFifo, uint32_t timeout);
    bool parser(DtFifo* pRxFifo);
    bool prepareToSend(uint8_t* pBuff, size_t size);
    bool addCommand(DtProtocolCommand_t& command);
private:
    DtRoleType _role;

    DtProtocolRx_t _rx;
    DtProtocolTx_t _tx;
    DtProtocolAckEnum _sendAck;
    bool _waitAck;
    bool _resend;
    uint8_t _txError;
    uint32_t _timestamp;

    AckCallback_t _ackCallback = nullptr;
    TimeoutCallback_t _timeoutCallback = nullptr;
    GetTimeStamp_t _getTimeStamp = nullptr;

    bool _resetData(DtBuffType buffType);

    //------------------------------------------
    const unsigned int _kFrameSyncByte1 = 0x17;
    const unsigned int _kFrameSyncByte2 = 0xE8;
    const unsigned int _kFrameSpecData = 0u;
    const unsigned int _kFrameSpecAck = 3u;
    const unsigned int _kFrameHeaderLength = 5u;
    const unsigned int _kFrameCrcLength = 2u;
    const unsigned int _kFrameAckLength = 1u;
    const unsigned int _kFrameSnMask = 0x0FFFu;

    const unsigned int _kFrameRxErrorMax = 10u;
    //------------------------------------------

    uint16_t _maskSN(uint16_t sn);
    bool _checkSN(uint16_t sn, uint16_t prevSN);
    bool _searchSyncBytes(const DtFifo* pRxFifo, uint16_t* pOffset);
    bool _prepareToSend(uint8_t *buff, uint32_t size);
    bool _parse(const DtFrame_t* pFrame);
    bool _checkCRC(const DtFrame_t* pFrame);
    bool _sendAckCode(DtProtocolAckEnum ackCode);
    bool _checkAck(const DtFrame_t* pFrame, DtProtocolAckEnum* pAckCode);

    std::vector<DtProtocolCommand_t> _commands;

    void _executor(const uint8_t *data, uint32_t size);

};

} // Dt

#endif //DT_PROTOCOL_H
