#include "PDUBuffer.h"
#include <stdio.h>
#include <string>

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