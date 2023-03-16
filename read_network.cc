// #include <iostream>
// #include <stdio.h>
// #include <vector>
// #include <string>
// #include <map>
// #include <arpa/inet.h>
// #include <math.h>
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


// const int LEN_GLOBAL_PCAP_HEADER = 24;
// const int LEN_PCAP_HEADER = 16;
// const int LEN_UDP_HEADER = 46;
// std::string file_name("./VGW_PDU_Packets.pcap");

// using signal_pair = std::pair<std::string, int>;
// // HEADER-ID, pdu名
// std::map<uint32_t, std::string> id_to_pdu_map;

// // signal名 pdu名 index
// // std::unordered_map<std::pair<std::string, std::string>, int> map;

// std::map<std::string, std::vector<signal_pair>> signal_to_pdu_map;
// // signal名, length
// std::map<std::string, int> signal_to_length_map;

// // pdu编号 pdu名 signal地址
// std::vector<std::pair<int, std::map<std::string, std::vector<char*>>>> pcap_data;
// int count = 0;

// void get_pcap_data()
// {
//     FILE *fp = fopen(file_name.c_str(), "rb");
//     if (fp==NULL) 
//     {
// 		printf("open file error... \n");
// 	}
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
//             char *buf = (char *)malloc(pdu_len);
//             fread(buf, 1, pdu_len, fp);
//             len -= pdu_len;
//             // int *tmp = (int *)&buf[0];
//             // std::cout << " value " << *tmp << std::endl;
//             std::string name = id_to_pdu_map[id];
//             std::vector<signal_pair> sigs = signal_to_pdu_map[name];
//             std::map<std::string, std::vector<char*>> mp;
//             for (auto sig : sigs)
//             {
//                 uint64_t start_index = sig.second;
//                 mp[name].push_back(&buf[start_index]);
//             }
//             pcap_data.push_back(std::make_pair(count, mp));
//             count++;
//         }
//     }
// }


// void print_pcap_data()
// {
//     for (auto v : pcap_data)
//     {
//         std::cout << "The number is " << v.first;
//         for (auto [m_k, m_v] : v.second)
//         {
//             std::cout << "The PDU is " << m_k << " The address is ";
//             for (auto v_v : m_v)
//             {
//                 std::cout << v_v << "  ";
//             }
//         }
//         std::cout << std::endl;
//     }
    
// }

// // 第几个 pdu_name,signal_to_pdu_map 想办法由名字知道是第几个
// // void* get_signal_data(std::string pdu_name, std::string signal_name)
// // {

// // }

// int main()
// {
//     get_pcap_data();
//     print_pcap_data();
//     return 0;
// }