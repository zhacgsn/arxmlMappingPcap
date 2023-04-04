#pragma once
#include <stdio.h>
#include <stdint.h>
#include <variant>
#include "PDUStruct.h"
// PDUBuffer类，将pcap文件中的signal数据读取到buffer中
class PDUBuffer
{
public:
    PDUBuffer();
    ~PDUBuffer();
    
    char* get_start_address_by_index(int start_index);
    // 获得下一个写地址
    char* get_next_write_address(size_t len);
   // 更新写地址
    void update_write_index(size_t len);
    // 获得写的index
    int get_write_index();
    size_t writable_bytes() const
    {
        return size_ - writeIndex_;
    }
    // 确保缓存够写
    void ensure_writable_bytes(size_t len);
    char* get_head_address();
    // 根据偏移量，偏移字节数以及signal长度和类型获取数据
    std::variant<uint8_t, uint16_t, uint32_t, int8_t, int16_t, int32_t> get_signal_value(int start_index, int offset_bit, int signal_len, NativeType type, PackingByteOrder order);
private:
    void make_space(size_t len);
    char* buffer_;
    size_t size_;
    size_t writeIndex_;

};