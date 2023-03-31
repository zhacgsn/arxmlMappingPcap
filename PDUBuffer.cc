#include "PDUBuffer.h"
#include <stdio.h>
#include <string>
#include <variant>
#include "PDUStruct.h"
#include <iostream>
const uint32_t INITIAL_SIZE = 10240;
const uint32_t MORE_SIZE = 10240;


PDUBuffer::PDUBuffer()
    : writeIndex_(0),
    buffer_(nullptr),
    size_(0)
{
    buffer_ = (char *)malloc(INITIAL_SIZE);
    if (buffer_ == nullptr)
    {
        printf("initial error \n");
        exit(0);
    }
    size_ = INITIAL_SIZE;
}

PDUBuffer::~PDUBuffer()
{
    free(buffer_);
}

void PDUBuffer::ensure_writable_bytes(size_t len)
{
    if (writable_bytes() < len)
    {
        make_space(len); 
    }
}

char* PDUBuffer::get_next_write_address(size_t len)
{
    ensure_writable_bytes(len);
    return &buffer_[writeIndex_];

}

char* PDUBuffer::get_start_address_by_index(int start_index)
{
    if (start_index < 0 || start_index > writeIndex_)
    {
        printf("The start_index is wrong \n");
        return nullptr;
    }
    // std::cout << "&buffer_[start_index]: " << static_cast<void*>(&buffer_[start_index]) << std::endl;
    return &buffer_[start_index];
}

void PDUBuffer::make_space(size_t len)
{
    buffer_ = (char*)realloc(buffer_, size_ + MORE_SIZE);
    size_ = size_ + MORE_SIZE;
}

void PDUBuffer::update_write_index(size_t len)
{
    writeIndex_ += len;
}

int PDUBuffer::get_write_index()
{
    return writeIndex_;
}

char* PDUBuffer::get_head_address()
{
    return buffer_;
}

std::variant<uint8_t, uint16_t, uint32_t, int8_t, int16_t, int32_t> PDUBuffer::get_signal_value(int start_index, int offset_bit, int signal_len, NativeType type, PackingByteOrder order)
{
    switch (type)
    {
    case NativeType::A_UNSIGNED_CHAR:
        if (offset_bit % 8 == 0 && signal_len == 8)
        {
            uint8_t *tmp_value = (uint8_t*)&buffer_[start_index + offset_bit/8];
            //uint8_t value = htonl(*tmp_value);
            std::cout << "(1)A_UINT8: " << int(*tmp_value)<< std::endl;
            return *tmp_value;
        }
        else if (offset_bit % 8 == 0)
        {
            int left_bit = 8 - signal_len;
            uint8_t *tmp_value = (uint8_t*)&buffer_[start_index + offset_bit/8];
            uint8_t value = *tmp_value >> left_bit;
            std::cout << "(2)A_UINT8: " << (int)value<< std::endl;
            return value;
        }
        else
        {
            uint16_t *tmp_value = (uint16_t*)&buffer_[start_index + offset_bit/8];
            int left_offset = offset_bit % 8;
            int left_bit = 8 - signal_len;
            uint16_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htons(*tmp_value);
            uint8_t value = uint16_t(tmp_v << left_offset) >> (8 + left_bit);
            std::cout << "(3)A_UINT8: " << (uint16_t)value<< std::endl;
            return value;
        }
        break;
    case NativeType::A_SIGNED_CHAR:
        if (offset_bit % 8 == 0 && signal_len == 8)
        {
            int8_t *tmp_value = (int8_t*)&buffer_[start_index + offset_bit/8];
            //uint8_t value = htonl(*tmp_value);
            std::cout << "(1)A_INT8: " << int(*tmp_value)<< std::endl;
            return *tmp_value;
        }
        else if (offset_bit % 8 == 0)
        {
            int left_bit = 8 - signal_len;
            int8_t *tmp_value = (int8_t*)&buffer_[start_index + offset_bit/8];
            int8_t value = *tmp_value >> left_bit;
            std::cout << "(2)A_INT8: " << (int)value<< std::endl;
            return value;
        }
        else
        {
            int16_t *tmp_value = (int16_t*)&buffer_[start_index + offset_bit/8];
            int left_offset = offset_bit % 8;
            int left_bit = 8 - signal_len;
            int16_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htons(*tmp_value);
            int8_t value = int16_t(tmp_v << left_offset) >> (8 + left_bit);
            std::cout << "(3)A_INT8: " << (int16_t)value<< std::endl;
            return value;
        }
        break;
    case NativeType::A_UNSIGNED_SHORT:
        if (offset_bit % 8 == 0 && signal_len == 16)
        {
            uint16_t *tmp_value = (uint16_t*)&buffer_[start_index + offset_bit/8];
            uint16_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htons(*tmp_value);
            uint16_t value = tmp_v;
            std::cout << "(1)A_UINT16: " << value << std::endl;
            return value;
        }
        else if (offset_bit % 8 == 0)
        {
            int left_bit = 16 - signal_len;
            uint32_t *tmp_value = (uint32_t*)&buffer_[start_index + offset_bit/8];
            uint32_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
            uint16_t value = tmp_v >> (16 + left_bit);
            std::cout << "(2)A_UINT16: " << value << std::endl;
            return value;            
        }
        else
        {
            uint32_t *tmp_value = (uint32_t*)&buffer_[start_index + offset_bit/8];
            int left_offset = offset_bit % 8;
            int left_bit = 16 - signal_len;
            uint32_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
            uint16_t value = uint32_t(tmp_v << left_offset) >> (16 + left_bit);
            std::cout << "(3)A_UINT16: " << value<< std::endl;
            return value;
        }
        break;
    case NativeType::A_SIGNED_SHORT:
        if (offset_bit % 8 == 0 && signal_len == 16)
        {
            int16_t *tmp_value = (int16_t*)&buffer_[start_index + offset_bit/8];
            int16_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htons(*tmp_value);
            int16_t value = tmp_v;
            std::cout << "(1)A_INT16: " << value << std::endl;
            return value;
        }
        else if (offset_bit % 8 == 0)
        {
            int left_bit = 16 - signal_len;
            int32_t *tmp_value = (int32_t*)&buffer_[start_index + offset_bit/8];
            int32_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
            int16_t value = tmp_v >> (16 + left_bit);
            std::cout << "(2)A_INT16: " << value << std::endl;
            return value;            
        }
        else
        {
            int32_t *tmp_value = (int32_t*)&buffer_[start_index + offset_bit/8];
            int left_offset = offset_bit % 8;
            int left_bit = 16 - signal_len;
            int32_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
            int16_t value = int32_t(tmp_v << left_offset) >> (16 + left_bit);
            std::cout << "(3)A_INT16: " << value<< std::endl;
            return value;
        }
        break;
    case NativeType::A_UNSIGNED_LONG:
        if (offset_bit % 8 == 0 && signal_len == 32)
        {
            uint32_t *tmp_value = (uint32_t*)&buffer_[start_index + offset_bit/8];
            uint32_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
            uint32_t value = tmp_v;
            std::cout << "(1)A_UINT32: " << value << std::endl;
            return value;
        }
        else if (offset_bit % 8 == 0)
        {
            int left_bit = 32 - signal_len;
            uint64_t *tmp_value = (uint64_t*)&buffer_[start_index + offset_bit/8];
            uint64_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonll(*tmp_value);
            uint32_t value = tmp_v >> (32 + left_bit);
            std::cout << "(2)A_UINT32: " << value << std::endl;
            return value;              
        }
        else
        {
            uint64_t *tmp_value = (uint64_t*)&buffer_[start_index + offset_bit/8];
            int left_offset = offset_bit % 8;
            int left_bit = 32 - signal_len;
            uint64_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonll(*tmp_value);
            uint32_t value = uint64_t(tmp_v << left_offset) >> (32 + left_bit);
            std::cout << "(3)A_UINT32: " << value<< std::endl;
            return value;
        }   
        break;
    case NativeType::A_SIGNED_LONG:
        if (offset_bit % 8 == 0 && signal_len == 32)
        {
            int32_t *tmp_value = (int32_t*)&buffer_[start_index + offset_bit/8];
            int32_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
            int32_t value = tmp_v;
            std::cout << "(1)A_INT32: " << value << std::endl;
            return value;
        }
        else if (offset_bit % 8 == 0)
        {
            int left_bit = 32 - signal_len;
            int64_t *tmp_value = (int64_t*)&buffer_[start_index + offset_bit/8];
            int64_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonll(*tmp_value);
            int32_t value = tmp_v >> (32 + left_bit);
            std::cout << "(2)A_INT32: " << value << std::endl;
            return value;              
        }
        else
        {
            int64_t *tmp_value = (int64_t*)&buffer_[start_index + offset_bit/8];
            int left_offset = offset_bit % 8;
            int left_bit = 32 - signal_len;
            int64_t tmp_v = *tmp_value;
            if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonll(*tmp_value);
            int32_t value = int64_t(tmp_v << left_offset) >> (32 + left_bit);
            std::cout << "(3)A_INT32: " << value<< std::endl;
            return value;
        }   
        break;
    default:
        break;
    }
    uint32_t tmp;
    return tmp;
}