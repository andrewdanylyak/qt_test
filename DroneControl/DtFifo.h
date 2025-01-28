/**
 ******************************************************************************
 * @file    DtFifo
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

#pragma once

#include <cstdint>
#include <cstddef>

namespace Dt {

class DtFifo {
public:
    DtFifo(uint8_t* buffer, size_t capacity);
    ~DtFifo();
    bool push(uint8_t value);
    bool pop(uint8_t& value);
    bool isEmpty() const;
    bool isFull() const;
    size_t size() const;
    void clear();
    bool pushBuffer(const uint8_t* buff, size_t count);
    bool popBuffer(uint8_t* buff, size_t count);
    size_t availableSpace();
    size_t getHead() const;
    size_t getSize() const;
    size_t getCapacity() const;
    const uint8_t* getBuffer() const;
private:
    uint8_t* _buffer = nullptr;
    size_t _capacity = 0;
    size_t _size = 0;
    size_t _head = 0;
    size_t _tail = 0;
};

} // Dt
