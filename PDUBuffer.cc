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

std::variant<uint8_t, uint16_t, uint32_t> PDUBuffer::get_signal_value(int start_index, int offset_bit, int signal_len, BaseType type)
{
    switch (type)
    {
    case BaseType::A_UINT8:
        if (offset_bit % 8 == 0 && signal_len == 8)
        {
            uint8_t *tmp_value = (uint8_t*)&buffer_[start_index + offset_bit/8];
            //uint8_t value = htonl(*tmp_value);
            std::cout << "A_UINT8: " << int(*tmp_value)<< std::endl;
            return *tmp_value;
        }
        else if (offset_bit % 8 == 0)
        {
            int left_bit = 8 - signal_len;
            uint8_t *tmp_value = (uint8_t*)&buffer_[start_index + offset_bit/8];
            uint8_t value = htonl(*tmp_value) >> left_bit;
            std::cout << "A_UINT8: " << value<< std::endl;
            return value;
        }
        else
        {
            // 去头去尾,多读一个字节
            uint16_t *tmp_value = (uint16_t*)&buffer_[start_index + offset_bit/8];
            int left_offset = offset_bit % 8;
            int left_bit = 8 - signal_len;
            uint8_t value = (htonl(*tmp_value) << left_offset) >> (8 + left_offset + left_bit);
            std::cout << "A_UINT8: " << value<< std::endl;
            return value;
        }
        break;
    case BaseType::A_UINT16:
        if (offset_bit % 8 == 0 && signal_len == 16)
        {
            uint16_t *tmp_value = (uint16_t*)&buffer_[start_index + offset_bit/8];
            uint16_t value = htonl(*tmp_value);
            std::cout << "A_UINT16: " << value << std::endl;
            return value;
        }
        else if (offset_bit % 8 == 0)
        {
            int left_bit = 16 - signal_len;
            uint16_t *tmp_value = (uint16_t*)&buffer_[start_index + offset_bit/8];
            uint16_t value = htonl(*tmp_value) >> left_bit;
            std::cout << "A_UINT16: " << value << std::endl;
            return value;            
        }
        else
        {
            uint32_t *tmp_value = (uint32_t*)&buffer_[start_index + offset_bit/8];
            int left_offset = offset_bit % 8;
            int left_bit = 8 - signal_len;
            uint8_t value = (htonl(*tmp_value) << left_offset) >> (16 + left_offset + left_bit);
            std::cout << "A_UINT16: " << value<< std::endl;
            return value;
        }
        break;
    case BaseType::A_UINT32:
         if (offset_bit % 8 == 0 && signal_len == 32)
        {
            uint32_t *tmp_value = (uint32_t*)&buffer_[start_index + offset_bit/8];
            uint32_t value = htonl(*tmp_value);
            std::cout << "A_UINT32: " << value << std::endl;
            return value;
        }
        else if (offset_bit % 8 == 0)
        {
            int left_bit = 32 - signal_len;
            uint32_t *tmp_value = (uint32_t*)&buffer_[start_index + offset_bit/8];
            uint32_t value = htonl(*tmp_value) >> left_bit;
            std::cout << "A_UINT32: " << value << std::endl;
            return value;              
        }
        else
        {
            uint64_t *tmp_value = (uint64_t*)&buffer_[start_index + offset_bit/8];
            int left_offset = offset_bit % 8;
            int left_bit = 8 - signal_len;
            uint32_t value = (htonl(*tmp_value) << left_offset) >> (32 + left_offset + left_bit);
            std::cout << "A_UINT32: " << value<< std::endl;
            return value;
        }   
        break;
    default:
        break;
    }
    uint32_t tmp;
    return tmp;
}
// // std::vector<std::pair<int, std::map<std::string, std::vector<int>>>> pcap_data;
// PDUBuffer buffer;
// int count = 0;

// void get_pcap_data()
// {
//     FILE *fp = fopen(file_name.c_str(), "rb");
//     if (fp==NULL) 
//     {
//   printf("open file error... \n");
//  }
//     PcapFileHeader_t pcapFileHeader = {0};
//     PcapPkthdr_t packetHeader = {0};
//     fread(&packetHeader, sizeof(PcapFileHeader_t), 1, fp);
//     // 每个udp最后包含的pdu是一个完整的pdu
//     while (!feof(fp))
//     {
//         fread(&packetHeader, sizeof(PcapPkthdr_t), 1, fp);
//         int len = packetHeader.caplen;
//         std::cout << "packetHeadergetLen: " << len << std::endl;
//         fseek(fp, LEN_UDP_HEADER, SEEK_CUR);
//         len -= LEN_UDP_HEADER;
//         while (len > 0)
//         {
//             //void *p_net_id = nullptr;
//             uint32_t net_id;
//             fread(&net_id, sizeof(uint32_t), 1, fp);
//             //fread(p_net_id, 4, 1, fp);
//             //printf("hello world \n");
//             //uint32_t *net_id = ((uint32_t *)p_net_id);
//             uint32_t id = htonl(net_id);
//             len -= sizeof(uint32_t);
//             std::cout << "id: " << id << " len: " << len << std::endl;
            
//             uint32_t net_pdu_len;
//             fread(&net_pdu_len, sizeof(uint32_t), 1, fp);
//             uint32_t pdu_len = htonl(net_pdu_len);
//             len -= sizeof(uint32_t);
//             std::cout << "pdu_len: " << pdu_len << " len: "<< len << std::endl;

//             // 读入内存
//             // char *buf = (char *)malloc(pdu_len);
//             // fread(buf, 1, pdu_len, fp);
//             // len -= pdu_len;
//             int start_write_index = buffer.get_write_index();
//             fread(buffer.get_next_write_address(pdu_len), 1, pdu_len, fp);
//             buffer.update_write_index(pdu_len);
//             len -= pdu_len;

//             // int *tmp = (int *)&buf[0];
//             // std::cout << " value " << *tmp << std::endl;
//             std::string name = id_to_pdu_map[id];
//             std::vector<signal_pair> sigs = signal_to_pdu_map[name];
//             // std::map<std::string, std::vector<char*>> mp;
//             std::map<pdu_pair, std::vector<int>> mp;
//             pdu_pair tmp_pdu_pair(name, start_write_index);
//             for (auto sig : sigs)
//             {
//                 uint64_t start_index = sig.second;
//                 // mp[name].push_back(&buf[start_index]);
//                 mp[tmp_pdu_pair].push_back(start_index);
//             }
//             pcap_data.push_back(std::make_pair(count, mp));
//             count++;
//         }
//     }
// }