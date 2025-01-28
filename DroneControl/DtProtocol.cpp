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

#include "DtProtocol.h"

namespace Dt {

DtProtocol::DtProtocol(DtRoleType role, uint8_t *pRxBuff, uint32_t rxSize, uint8_t *pTxBuff, uint32_t txSize)
{
    this->_role = role;
    this->_rx.buffer = pRxBuff;
    this->_rx.capacity = rxSize;

    this->_tx.buffer = pTxBuff;
    this->_tx.capacity = txSize;

    this->_sendAck = DtProtocolAckEnum::kProtocolAck_None;

    this->_resetData(DtBuffType::kRx);
    this->_resetData(DtBuffType::kTx);
}

bool DtProtocol::_resetData(DtBuffType buffType)
{
    if (buffType == DtBuffType::kRx) {
        this->_rx.size = 0;
        this->_rx.sn = 0;
        this->_rx.status = DtFrameStatusEnum::kFrameWaitingHeader;
        return true;
    } else if (buffType == DtBuffType::kTx) {
        this->_tx.size = 0;
        this->_tx.offset = 0;
        this->_tx.sn = 0;
        this->_tx.firstFrame = false;
        this->_tx.access = true;

        this->_waitAck = false;
        this->_resend = false;
        this->_txError = 0;
        return true;
    } else {
        return false;
    }
}

void DtProtocol::setAckCallback(AckCallback_t handler)
{
    this->_ackCallback = handler;
}

void DtProtocol::setTimeoutCallback(TimeoutCallback_t handler)
{
    this->_timeoutCallback = handler;
}

void DtProtocol::setFuncForGetTimeStamp(GetTimeStamp_t handler)
{
    this->_getTimeStamp = handler;
}


bool DtProtocol::send(DtFifo *pTxFifo, uint32_t timeout)
{
    if (pTxFifo == nullptr) {
        return false;
    }

    DtFrameType frameType = DtFrameType::kFrameTypeSingle;
    bool firstFrame = false;

    DtProtocolTx_t *txData = &(this->_tx);
    uint32_t size = txData->size - txData->offset;

    if (this->_sendAck != DtProtocolAckEnum::kProtocolAck_None) {
        DtFrame_t frame;

        if (pTxFifo->availableSpace() < this->_kFrameHeaderLength + this->_kFrameAckLength + this->_kFrameCrcLength)
        {
            return false;
        }

        frame.header.syncBytes[0] = this->_kFrameSyncByte1;
        frame.header.syncBytes[1] = this->_kFrameSyncByte2;
        frame.header.type = static_cast<uint16_t>(DtFrameType::kFrameTypeSingle);
        frame.header.spec = this->_kFrameSpecAck;
        frame.header.sn = 0;
        frame.header.length = this->_kFrameAckLength;
        frame.data[0] = static_cast<uint8_t>(this->_sendAck);

        frame.crc = DtCRC::getInstance().init(reinterpret_cast<uint8_t*>(&(frame.header)),
                                              frame.header.length + this->_kFrameHeaderLength);

        int err = 0;
        err += pTxFifo->pushBuffer(reinterpret_cast<uint8_t*>(&(frame.header)), frame.header.length + this->_kFrameHeaderLength);

        err += pTxFifo->pushBuffer(reinterpret_cast<uint8_t*>(&(frame.crc)), this->_kFrameCrcLength);

        this->_sendAck = DtProtocolAckEnum::kProtocolAck_None;
    }

    if (this->_waitAck) {
        if (timeout != 0) {
            uint32_t timestamp = this->_getTimeStamp();
            if (timestamp - this->_timestamp >= timeout) {
                if (this->_txError < this->_kFrameRxErrorMax) {
                    ++this->_txError;
                    this->_waitAck = false;
                    this->_resend = true;
                    this->_timestamp = timestamp;
                } else {
                    this->_resetData(DtBuffType::kTx);

                    if (this->_timeoutCallback != nullptr) {
                        this->_timeoutCallback();
                    }
                }
            }
        }

        //LOG_DBG("Wait Ack");
        return false;
    }

    if (this->_resend == false) {
        this->_txError = 0;
        if (size == 0) {
            txData->access = true;
            return false;
        }

        if (txData->firstFrame == false) {
            txData->sn = 0;
        }

        if (size > DT_PROTOCOL_FRAME_MTU) {
            size = DT_PROTOCOL_FRAME_MTU;
            frameType = txData->firstFrame ? DtFrameType::kFrameTypeConsecutive : DtFrameType::kFrameTypeFirst;
            firstFrame = true;
        } else if (size > 0) {
            frameType = txData->firstFrame ? DtFrameType::kFrameTypeLast : DtFrameType::kFrameTypeSingle;
            firstFrame = false;
        }

        if (pTxFifo->availableSpace() < size + this->_kFrameHeaderLength + this->_kFrameCrcLength)
        {
            return false;
        }

        txData->frame.header.syncBytes[0] = this->_kFrameSyncByte1;
        txData->frame.header.syncBytes[1] = this->_kFrameSyncByte2;
        txData->frame.header.type = static_cast<uint16_t>(frameType);
        txData->frame.header.spec = this->_kFrameSpecData;
        txData->frame.header.sn = txData->sn;
        txData->frame.header.length = size;
        std::memcpy(txData->frame.data, txData->buffer + txData->offset, size);

        txData->frame.crc = DtCRC::getInstance().init((uint8_t *)&(txData->frame.header), txData->frame.header.length + this->_kFrameHeaderLength);

        pTxFifo->pushBuffer(reinterpret_cast<uint8_t*>(&(txData->frame.header)), txData->frame.header.length + this->_kFrameHeaderLength);
        pTxFifo->pushBuffer(reinterpret_cast<uint8_t*>(&(txData->frame.crc)), this->_kFrameCrcLength);

        txData->sn = this->_maskSN(txData->sn + 1);
        txData->offset += size;
        txData->firstFrame = firstFrame;
    } else {
        if (pTxFifo->availableSpace() < txData->frame.header.length + this->_kFrameHeaderLength + this->_kFrameCrcLength)
        {
            return false;
        }
        pTxFifo->pushBuffer(reinterpret_cast<uint8_t*>(&(txData->frame.header)),
                            txData->frame.header.length + this->_kFrameHeaderLength);
        pTxFifo->pushBuffer(reinterpret_cast<uint8_t*>(&(txData->frame.crc)), this->_kFrameCrcLength);
    }

    if (this->_role == DtRoleType::kMaster) {
        this->_waitAck = true;
    } else {
        this->_waitAck = false;
    }

    this->_resend = false;
    this->_timestamp = this->_getTimeStamp();

    return true;
}

bool DtProtocol::_prepareToSend(uint8_t *buff, uint32_t size)
{
    if (buff == nullptr) {
        return false;
    }

    if (size == 0 || size > this->_tx.capacity) {
        return false;
    }

    if (this->_tx.access == false)
    {
        return false;
    }

    memcpy(this->_tx.buffer, buff, size);
    this->_tx.size = size;
    this->_tx.offset = 0;
    this->_tx.firstFrame = false;
    this->_tx.access = false;

    return true;
}

uint16_t DtProtocol::_maskSN(uint16_t sn)
{
    return (sn & this->_kFrameSnMask);
}

bool DtProtocol::_checkSN(uint16_t sn, uint16_t prevSN)
{
    return (sn == this->_maskSN(prevSN + 1));
}

bool DtProtocol::_searchSyncBytes(const DtFifo* pRxFifo, uint16_t* pOffset)
{
    if (pRxFifo == nullptr || pOffset == nullptr)
    {
        return false;
    }

    uint16_t head = pRxFifo->getHead();
    uint16_t count = pRxFifo->getSize();
    uint16_t counter = 0;

    if (count == 0) {
        return false;
    }

    for (counter = 0; counter < count; ++counter) {
        if (pRxFifo->getBuffer()[head] == this->_kFrameSyncByte1) {
            if (pRxFifo->getBuffer()[(head + 1) % pRxFifo->getCapacity()] == this->_kFrameSyncByte2) {
                *pOffset = counter;
                break;
            }
        } else {
            head = (head + 1) % pRxFifo->getCapacity();
        }
    }

    return counter == count ? false : true;
}

bool DtProtocol::_parse(const DtFrame_t* pFrame)
{
    if (pFrame == nullptr) {
        return false;
    }

    auto ackCode = DtProtocolAckEnum::kProtocolAck_OK;
    DtProtocolRx_t* rxData = &(this->_rx);

    if (this->_checkCRC(pFrame) == false) {
        this->_sendAckCode(DtProtocolAckEnum::kProtocolAck_BadCRC);
        return false;
    }

    if (this->_checkAck(pFrame, &ackCode)) {
        switch (ackCode)
        {
        case DtProtocolAckEnum::kProtocolAck_OK:
            this->_txError = 0;
            if (this->_ackCallback != nullptr) {
                this->_ackCallback(DtProtocolAckEnum::kProtocolAck_OK);
            }
            break;

        case DtProtocolAckEnum::kProtocolAck_SyncError:
            if (this->_ackCallback != nullptr) {
                this->_ackCallback(DtProtocolAckEnum::kProtocolAck_SyncError);
            }
            break;

        case DtProtocolAckEnum::kProtocolAck_BadCRC:
            if (this->_txError < this->_kFrameRxErrorMax) {
                ++this->_txError;
                this->_resend = true;
            } else {
                this->_resetData(DtBuffType::kTx);
                if (this->_ackCallback != nullptr) {
                    this->_ackCallback(DtProtocolAckEnum::kProtocolAck_BadCRC);
                }
            }
            break;

        case DtProtocolAckEnum::kProtocolAck_MissingFrame:
            if (this->_txError < this->_kFrameRxErrorMax) {
                ++this->_txError;
                this->_tx.offset = 0;
                this->_tx.firstFrame = 0;
            } else {
                this->_resetData(DtBuffType::kTx);
                if (this->_ackCallback != nullptr) {
                    this->_ackCallback(DtProtocolAckEnum::kProtocolAck_MissingFrame);
                }
            }
            break;

        case DtProtocolAckEnum::kProtocolAck_OutOfMemory:
            this->_resetData(DtBuffType::kTx);
            if (this->_ackCallback != nullptr) {
                this->_ackCallback(DtProtocolAckEnum::kProtocolAck_OutOfMemory);
            }
            break;

        default:
            break;
        }

        this->_waitAck = false;

        return true;
    }

    if (rxData->size + rxData->frame.header.length > rxData->capacity) {
        // Send Ack: - Out Of Memory
        this->_sendAckCode(DtProtocolAckEnum::kProtocolAck_OutOfMemory);
        this->_resetData(DtBuffType::kRx);
        return false;
    }

    switch (static_cast<DtFrameType>(pFrame->header.type))
    {
    case DtFrameType::kFrameTypeFirst:
        if (this->_waitAck == true) {
            this->_waitAck = false;
            this->_resetData(DtBuffType::kRx);
        }

        rxData->sn = pFrame->header.sn;
        memcpy(rxData->buffer, pFrame->data, pFrame->header.length);
        rxData->size = pFrame->header.length;

        // Send Ack: OK
        this->_sendAckCode(DtProtocolAckEnum::kProtocolAck_OK);
        break;

    case DtFrameType::kFrameTypeConsecutive:
        if (!this->_checkSN(pFrame->header.sn, rxData->sn)) {
            // Send Ack: Missing Frame
            this->_sendAckCode(DtProtocolAckEnum::kProtocolAck_MissingFrame);
            return false;
        }

        rxData->sn = pFrame->header.sn;
        memcpy(rxData->buffer + rxData->size, pFrame->data, pFrame->header.length);
        rxData->size += pFrame->header.length;

        this->_sendAckCode(DtProtocolAckEnum::kProtocolAck_OK);
        break;

    case DtFrameType::kFrameTypeLast:
        if (!this->_checkSN(pFrame->header.sn, rxData->sn)) {
            this->_sendAckCode(DtProtocolAckEnum::kProtocolAck_MissingFrame);
            return false;
        }

        memcpy(rxData->buffer + rxData->size, pFrame->data, pFrame->header.length);
        rxData->size += pFrame->header.length;

        // Data handler
        if (!this->_commands.empty()) {
            this->_executor(rxData->buffer, rxData->size);
        } else {
            this->_sendAckCode(DtProtocolAckEnum::kProtocolAck_OK);
        }

        rxData->size = 0;
        break;

    case DtFrameType::kFrameTypeSingle:
        if (this->_waitAck == true) {
            this->_waitAck = false;
            this->_resetData(DtBuffType::kRx);
        }

        rxData->sn = pFrame->header.sn;
        memcpy(rxData->buffer, pFrame->data, pFrame->header.length);
        rxData->size = pFrame->header.length;

        // Data handler
        if (!this->_commands.empty()) {
            this->_executor(rxData->buffer, rxData->size);
        } else {
            this->_sendAckCode(DtProtocolAckEnum::kProtocolAck_OK);
        }

        rxData->size = 0;
        break;
    default:
        break;
    }

    return true;
}

bool DtProtocol::parser(DtFifo* pRxFifo)
{
    if (pRxFifo == nullptr) {
        return false;
    }

    DtProtocolRx_t* rxData = &(this->_rx);

    switch (rxData->status)
    {
    case DtFrameStatusEnum::kFrameWaitingHeader:
        if (pRxFifo->getSize() >= this->_kFrameHeaderLength) {
            uint16_t offset = 0;
            if (this->_searchSyncBytes(pRxFifo, &offset) == false) {
                this->_sendAckCode(DtProtocolAckEnum::kProtocolAck_SyncError);
                pRxFifo->clear();
                break;
            }

            if (offset > 0) {
                // TODO:  Send Ack: Sync Error
                uint8_t temp[DT_PROTOCOL_FRAME_MTU + this->_kFrameHeaderLength + this->_kFrameCrcLength];
                pRxFifo->popBuffer(temp, offset);
                break;
            }

            if (!pRxFifo->popBuffer(reinterpret_cast<uint8_t*>(&(rxData->frame.header)), _kFrameHeaderLength)) {
                break;
            }

            rxData->status = DtFrameStatusEnum::kFrameWaitingData;
        } else {
            break;
        }
        //break;
    case DtFrameStatusEnum::kFrameWaitingData:
        if (pRxFifo->getSize() >= rxData->frame.header.length + this->_kFrameCrcLength) {
            pRxFifo->popBuffer(reinterpret_cast<uint8_t *>(&(rxData->frame.data)), rxData->frame.header.length);
            pRxFifo->popBuffer(reinterpret_cast<uint8_t *>(&(rxData->frame.crc)), this->_kFrameCrcLength);

            rxData->status = DtFrameStatusEnum::kFrameCompleted;
        } else {
            break;
        }
        //break;
    case DtFrameStatusEnum::kFrameCompleted:
        this->_parse(&(rxData->frame));
        rxData->status = DtFrameStatusEnum::kFrameWaitingHeader;
        break;
    default:
        break;
    }

    return true;
}

bool DtProtocol::_checkCRC(const DtFrame_t* pFrame)
{
    if (pFrame == nullptr) {
        return false;
    }
    return (pFrame->crc == DtCRC::getInstance().init(
                reinterpret_cast<const uint8_t*>(&(pFrame->header)),
                pFrame->header.length + this->_kFrameHeaderLength
                ));
}

bool DtProtocol::_sendAckCode(DtProtocolAckEnum ackCode)
{
    this->_sendAck = ackCode;
    return true;
}

bool DtProtocol::_checkAck(const DtFrame_t* pFrame, DtProtocolAckEnum* pAckCode)
{
    if (pFrame == nullptr) {
        return false;
    }

    if (pFrame->header.spec == 3 && pFrame->header.length == 1) {
        if (pAckCode != nullptr) {
            *pAckCode = static_cast<DtProtocolAckEnum>(pFrame->data[0]);
        }

        return true;
    }

    return false;
}

bool DtProtocol::prepareToSend(uint8_t* pBuff, size_t size)
{
    if (pBuff == nullptr) {
        return false;
    }

    if (size == 0 || size > this->_tx.capacity) {
        return false;
    }

    if (this->_tx.access == false) {
        return false;
    }

    memcpy(this->_tx.buffer, pBuff, size);
    this->_tx.size = size;
    this->_tx.offset = 0;
    this->_tx.firstFrame = false;
    this->_tx.access = false;

    return true;
}

bool DtProtocol::addCommand(DtProtocolCommand_t& command)
{
    this->_commands.push_back(command);
    //ToDo add a check for already created records to avoid duplicate clients
    return true;
}

void DtProtocol::_executor(const uint8_t *data, uint32_t size)
{
    if (data == nullptr) {
        return;
    }

    uint8_t cmd = data[0];

    for (auto const &command: this->_commands) {
        if (cmd == command.commandId) {
            if (nullptr != command.commandFunc) {
                command.commandFunc(data + CMD_ID_SIZE, size - CMD_ID_SIZE);
                if (this->_role == DtRoleType::kMaster) {
                    //ToDo add clear ack
                }
            } else {
                this->_sendAckCode(DtProtocolAckEnum::kProtocolAck_OK);
            }
            break;
        }
    }

    return;
}



} // Dt
