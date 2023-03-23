#pragma once
#include <stdio.h>
// 分配内存，并返回指定下标的指针
// index，知道该从哪个位置分配内存
class PDUBuffer
{
public:
    PDUBuffer();
    ~PDUBuffer();
    char* get_start_address_by_index(int start_index);
    char* get_next_write_address(size_t len);
    void update_write_index(size_t len);
    int get_write_index();
    size_t writable_bytes() const
    {
        return size_ - writeIndex_;
    }

    void ensure_writable_bytes(size_t len);
    char* get_head_address();

    std::variant<uint8_t, uint16_t, uint32_t> get_signal_value(int start_index, int offset_bit, int signal_len, BaseType type);
private:
    void make_space(size_t len);
    char* buffer_;
    size_t size_;
    size_t writeIndex_;

};