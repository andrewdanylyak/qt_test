/**
 ******************************************************************************
 * @file    DtCRC
 * @date    22.11.2024
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

#include "DtCRC.h"

namespace Dt {

DtCRC& DtCRC::getInstance()
{
    static DtCRC instance;
    return instance;
}

uint16_t DtCRC::init(const uint8_t* pData, size_t size)
{
    if (pData == nullptr || size == 0) {
        return 0;
    }

    this->_crc = 0xFFFFu; //reset _crc

    for (size_t i = 0; i < size; ++i) {
        this->_crc = (this->_crc << 8) ^ DtCRC::table[(this->_crc >> 8) ^ pData[i]];
    }
    return this->_crc;
}

uint16_t DtCRC::update(const uint8_t* pData, size_t size)
{
    if (pData == nullptr || size == 0) {
        return this->_crc;
    }
    for (size_t i = 0; i < size; ++i) {
        this->_crc = (this->_crc << 8) ^ DtCRC::table[(this->_crc >> 8) ^ pData[i]];
    }
    return this->_crc;
}


uint16_t DtCRC::getCRC() const
{
    return this->_crc;
}

} // Dt
