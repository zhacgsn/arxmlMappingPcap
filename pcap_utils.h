// #pragma once

// #include <stdlib.h>
// #include <stdio.h>
// #include <string>
// #include <map>
// #include <vector>

// #include "arxml_mapping.h"
// #include "PDUBuffer.h"


// namespace pcap
// {

// const int LEN_GLOBAL_PCAP_HEADER = 24;
// const int LEN_PCAP_HEADER = 16;
// const int LEN_UDP_HEADER = 46;

// // 需要保存siganal的索引位置，因为buffer扩容后地址可能发生变化，int 为偏移量
// std::vector<std::pair<int, std::map<std::string, int>>> pcap_data;

// /*pcap file header*/
// typedef struct PcapFileHeader
// {
//     char   magic[4];
//     uint16_t   version_major;
//     uint16_t   version_minor;
//     int32_t    thiszone;      /*时区修正*/
//     uint32_t   sigfigs;       /*精确时间戳*/
//     uint32_t   snaplen;       /*抓包最大长度*/
//     uint32_t   linktype;      /*链路类型*/
// } PcapFileHeader_t;

// /*pcap packet header*/
// typedef struct PcapPkthdr
// {
//     uint32_t   seconds;     /*秒数*/
//     uint32_t   u_seconds;   /*毫秒数*/
//     uint32_t   caplen;      /*数据包长度*/
//     uint32_t   len;         /*文件数据包长度*/
// } PcapPkthdr_t;

// void get_pcap_data(const dsf::ArxmlMapping &arxml_mapping_instance, const std::string &file_name, PDUBuffer &buffer)
// {
//     int count = 0;

//     FILE *fp = fopen(file_name.c_str(), "rb");
//     if (fp==NULL) 
//     {
//         printf("open file error... \n");
//     }
//     PcapFileHeader_t pcapFileHeader = {0};
//     PcapPkthdr_t packetHeader = {0};
//     // 读取PcapFileHeader头部
//     fread(&packetHeader, sizeof(PcapFileHeader_t), 1, fp);
//     // 每个udp最后包含的pdu是一个完整的pdu
//     while (!feof(fp))
//     {
//         // 读取 PcapPkthdr 头部
//         fread(&packetHeader, sizeof(PcapPkthdr_t), 1, fp);
//         int len = packetHeader.caplen;
//         fseek(fp, LEN_UDP_HEADER, SEEK_CUR);
//         len -= LEN_UDP_HEADER;
//         while (len > 0)
//         {
//             uint32_t net_id;
//             fread(&net_id, sizeof(uint32_t), 1, fp);

//             long long id = htonl(net_id);
//             len -= sizeof(uint32_t);

//             uint32_t net_pdu_len;
//             fread(&net_pdu_len, sizeof(uint32_t), 1, fp);
//             uint32_t pdu_len = htonl(net_pdu_len);
//             len -= sizeof(uint32_t);

//             int start_write_index = buffer.get_write_index();
//             // 将 signal 数据 读入 buffer中
//             fread(buffer.get_next_write_address(pdu_len), 1, pdu_len, fp);
//             buffer.update_write_index(pdu_len);
//             len -= pdu_len;
//             std::string name = arxml_mapping_instance.id_to_pdu_map_.at(id);
//             std::map<std::string, int> mp;
//             mp[name] = start_write_index;
//             // 更新pcap_data
//             pcap_data.push_back(std::make_pair(count, mp));
//             count++;
//         }
//     }
// }
// };


