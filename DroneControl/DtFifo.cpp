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

#include "DtFifo.h"

namespace Dt {

/**
* @brief Constructor for DtFifo class
*
* This constructor initializes a DtFIFO object with the given buffer and capacity.
*
* @param buffer Pointer to the buffer used for the FIFO
* @param capacity The size of the buffer in bytes
*/
DtFifo::DtFifo(uint8_t* buffer, size_t capacity)
{
    this->_buffer = buffer;
    this->_capacity = capacity;

    // ToDo add a check of the buffer for a null pointer, perhaps add an overload of the constructor to simply give the size, and the buffer will be created itself
}

/**
* @brief Destructor for DtFifo class.
*
* This method is responsible for deallocating the buffer array used by the DtFifo instance.
* It must be called when the DtFifo instance is no longer needed to prevent memory leaks.
*/
DtFifo::~DtFifo()
{
    //    delete[] this->_buffer;
}

/**
 * Pushes a new element into the FIFO buffer.
 *
 * @param value The value to be added to the FIFO buffer.
 * @return True if the value was successfully added, false if the buffer is full.
 */
bool DtFifo::push(uint8_t value)
{
    if (this->isFull()) {
        return false;
    }

    this->_buffer[this->_tail] = value;
    this->_tail = (this->_tail + 1) % this->_capacity;
    this->_size++;
    return true;
}

/**
* @brief Removes the element at the front of the FIFO buffer and retrieves its value.
*
* If the FIFO buffer is empty, returns false without modifying the input value.
* The head of the buffer is moved forward by one position to simulate the removal of the element.
* Decrements the size of the buffer by one.
*
* @param value Reference to store the value of the removed element.
* @return True if an element was successfully removed, false if the buffer is empty.
*/
bool DtFifo::pop(uint8_t& value) {
    if (this->isEmpty()) {
        return false;
    }
    value = this->_buffer[this->_head];
    this->_head = (this->_head + 1) % this->_capacity;
    this->_size--;
    return true;
}

/**
* @brief Check if the FIFO is empty.
*
* This method checks if the FIFO (First In First Out) data structure is empty.
*
* @return true if the FIFO is empty, false otherwise.
*/
bool DtFifo::isEmpty() const
{
    return this->_size == 0;
}

/**
* @brief Check if the FIFO buffer is full.
*
* This function checks whether the current size of the FIFO buffer is equal to its capacity.
*
* @return True if the FIFO buffer is full, false otherwise.
*/
bool DtFifo::isFull() const
{
    return this->_size == this->_capacity;
}

/**
 * @brief Get the current number of elements in the FIFO.
 *
 * This function returns the current size of the FIFO, which represents the number of elements
 * currently stored in the FIFO buffer.
 *
 * @return The number of elements in the FIFO as size_t.
 */
size_t DtFifo::size() const
{
    return this->_size;
}

/**
 * @brief Clear the FIFO by resetting head, tail, and size to zero.
 */
void DtFifo::clear()
{
    this->_head = 0;
    this->_tail = 0;
    this->_size = 0;
}

/**
* @brief Pushes the given buffer of bytes into the FIFO buffer
* @param buff Pointer to the buffer of bytes to push into the FIFO
* @param count Number of bytes in the buffer to push
* @return True if the buffer was successfully pushed, false if there was not enough space in the FIFO
*/
bool DtFifo::pushBuffer(const uint8_t* buff, size_t count)
{
    if ((this->_capacity - this->_size) < count) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        this->_buffer[this->_tail] = buff[i];
        this->_tail = (this->_tail + 1) % this->_capacity;
    }

    this->_size += count;
    return true;
}

/**
*  Pop elements from the FIFO buffer.
*
*  @param buff Pointer to an array where popped elements will be stored.
*  @param count Number of elements to pop from the buffer.
*  @return true if the elements were successfully popped, false if count exceeds current buffer size.
*/
bool DtFifo::popBuffer(uint8_t* buff, size_t count)
{
    if (this->_size < count) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        buff[i] = this->_buffer[this->_head];
        this->_head = (this->_head + 1) % this->_capacity;
    }

    this->_size -= count;
    return true;
}

size_t DtFifo::availableSpace()
{
    return this->_capacity - this->_size;
}

size_t DtFifo::getHead() const
{
    return this->_head;
}

size_t DtFifo::getSize() const
{
    return this->_size;
}

size_t DtFifo::getCapacity() const
{
    return this->_capacity;
}

const uint8_t* DtFifo::getBuffer() const
{
    return this->_buffer;
}

} // Dt
