#if defined( _MSC_VER )
	#if !defined( _CRT_SECURE_NO_WARNINGS )
		#define _CRT_SECURE_NO_WARNINGS		// This test file is not intended to be secure.
	#endif
#endif

#include "tinyxml2.h"
#include "arxml_mapping.h"
#include "pcap_utils.h"
#include "PDUStruct.h"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <arpa/inet.h>
#include <math.h>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>

#if defined( _MSC_VER ) || defined (WIN32)
	#include <crtdbg.h>
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	_CrtMemState startMemState;
	_CrtMemState endMemState;
#else
	#include <sys/stat.h>
	#include <sys/types.h>
#endif

using namespace tinyxml2;
using namespace std;
using namespace pcap;

std::string file_name("../VGW_PDU_Packets.pcap");

<<<<<<< HEAD
PDUBuffer buffer;

void print_pcap_data()
{
    for (auto v : pcap_data)
    {
        std::cout << "The number is " << v.first;
        for (auto [m_k, m_v] : v.second)
        {
            std::cout << " The PDU is " << m_k  << ", PDU offset(Byte): " << m_v << std::endl;
        }
        std::cout << std::endl;
    }
=======
// int为 在buffer中的起始位置
using pdu_pair = std::pair<std::string, int>;
// std::vector<std::pair<int, std::map<std::string, std::vector<char*>>>> pcap_data;
// 需要保存siganal的索引位置，因为buffer扩容后地址可能发生变化，int 为偏移量
std::vector<std::pair<int, std::map<std::string, int>>> pcap_data;
// PDUBuffer buffer;

// void get_pcap_data(const ArxmlMapping &arxml_mapping_instance)
// { 
//     int count = 0;

//     FILE *fp = fopen(file_name.c_str(), "rb");
//     if (fp==NULL) 
//     {
//         printf("open file error... \n");
//     }
//     PcapFileHeader_t pcapFileHeader = {0};
//     PcapPkthdr_t packetHeader = {0};
//     fread(&packetHeader, sizeof(PcapFileHeader_t), 1, fp);
//     // 每个udp最后包含的pdu是一个完整的pdu
//     while (!feof(fp))
//     {
//         fread(&packetHeader, sizeof(PcapPkthdr_t), 1, fp);
//         int len = packetHeader.caplen;
//         // std::cout << "packetHeadergetLen: " << len << std::endl;
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
//             // std::cout << "id: " << id << " len: " << len << std::endl;
            
//             uint32_t net_pdu_len;
//             fread(&net_pdu_len, sizeof(uint32_t), 1, fp);
//             uint32_t pdu_len = htonl(net_pdu_len);
//             len -= sizeof(uint32_t);
//             // std::cout << "pdu_len: " << pdu_len << " len: "<< len << std::endl;

//             // 读入内存
//             // char *buf = (char *)malloc(pdu_len);
//             // fread(buf, 1, pdu_len, fp);
//             // len -= pdu_len;
//             int start_write_index = buffer.get_write_index();
//             fread(buffer.get_next_write_address(pdu_len), 1, pdu_len, fp);
//             buffer.update_write_index(pdu_len);
//             len -= pdu_len;

//             std::string name = arxml_mapping_instance.id_to_pdu_map_.at(id);
//             std::map<std::string, int> mp;
//             mp[name] = start_write_index;
//             pcap_data.push_back(std::make_pair(count, mp));
            
//             // // int *tmp = (int *)&buf[0];
//             // // std::cout << " value " << *tmp << std::endl;
//             // std::string name = id_to_pdu_map[id];
//             // std::vector<signal_pair> sigs = signal_to_pdu_map[name];
//             // // std::map<std::string, std::vector<char*>> mp;
//             // std::map<pdu_pair, std::vector<int>> mp;
//             // pdu_pair tmp_pdu_pair(name, start_write_index);
//             // for (auto sig : sigs)
//             // {
//             //     uint64_t start_index = sig.second;
//             //     // mp[name].push_back(&buf[start_index]);
//             //     mp[tmp_pdu_pair].push_back(start_index);
//             // }
//             // pcap_data.push_back(std::make_pair(count, mp));
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
//             std::cout << " The PDU is " << m_k  << ", PDU offset(Byte): " << m_v << std::endl;
//             // for (int i = 0; i < m_v.size(); ++i)
//             // {
//             //     std::cout << "\t" << m_v[i] << "  " << static_cast<void*>(buffer.get_start_address_by_index((int)m_v[i] / 8));
//             // }
//         }
//         std::cout << std::endl;
//     }
>>>>>>> 2e0775b (modified types)
    
// }

<<<<<<< HEAD
void get_signal_data(std::string pdu_name, std::string signal_name, const ArxmlMapping &arxml_mapping_instance)
{
    for (auto v : pcap_data)
    {
        if (v.second.count(pdu_name) == 0)
        {
            continue;
        }
        else
        {
            int start_index = v.second[pdu_name];
            ArxmlMapping::pdu_signal_pair tmp(pdu_name, signal_name);
            int signal_index = arxml_mapping_instance.signal_index_in_pdu_map_.at(tmp);
            std::vector<ArxmlMapping::signal_offset_pair>  tmp_vec = arxml_mapping_instance.signal_to_pdu_map_.at(pdu_name);
            ArxmlMapping::signal_offset_pair sig = tmp_vec[signal_index];
            int offset_bit = sig.second;
            std::cout << "signal_index: " << signal_index << endl;
            std::cout << "signal offset_bit: " << offset_bit << "  " << " PDU offset_byte: " << start_index << endl;
            int signal_len = arxml_mapping_instance.signal_to_length_map_.at(signal_name);
            // 获取signal数据
            auto value = buffer.get_signal_value(start_index, offset_bit, signal_len, arxml_mapping_instance.base_type_to_native_map_.at(arxml_mapping_instance.signal_to_base_type_map_.at(signal_name)), arxml_mapping_instance.signal_to_byte_order_map_.at(signal_name));
            break;
        }
    }
}

void test1(const ArxmlMapping &arxml_mapping_instance)
{
    // 输入 pdu名字与signal名字，获得signal
    get_signal_data("VehicleSpeed", "VehicleSpeed", arxml_mapping_instance);

    get_signal_data("VehicleSpeed", "VehicleDirection", arxml_mapping_instance);

    get_signal_data("VehicleDistance", "VehicleTripDistance", arxml_mapping_instance);

    get_signal_data("VehicleDistance", "VehicleTotalDistance", arxml_mapping_instance);
}
=======
// char* get_signal_data(std::string pdu_name, std::string signal_name, const ArxmlMapping &arxml_mapping_instance)
// {

//     for (auto v : pcap_data)
//     {
//         if (v.second.count(pdu_name) == 0)
//         {
//             continue;
//         }
//         else
//         {
//             int start_index = v.second[pdu_name];
//             ArxmlMapping::pdu_signal_pair tmp(pdu_name, signal_name);
//             int signal_index = arxml_mapping_instance.signal_index_in_pdu_map_.at(tmp);
//             std::vector<ArxmlMapping::signal_offset_pair>  tmp_vec = arxml_mapping_instance.signal_to_pdu_map_.at(pdu_name);
//             ArxmlMapping::signal_offset_pair sig = tmp_vec[signal_index];
//             int offset_bit = sig.second;
//             std::cout << "signal_index: " << signal_index << endl;
//             std::cout << "signal offset_bit: " << offset_bit << "  " << " PDU offset_byte: " << start_index << endl;
//             int signal_len = arxml_mapping_instance.signal_to_length_map_.at(signal_name);
//             auto value = buffer.get_signal_value(start_index, offset_bit, signal_len, arxml_mapping_instance.base_type_to_native_map_.at(arxml_mapping_instance.signal_to_base_type_map_.at(signal_name)));
//             // std::cout << "The value is " << value << std::endl;
//             return buffer.get_start_address_by_index(start_index + offset_bit / 8);
//         }
//     }
//     return nullptr;
// }

// void test1(const ArxmlMapping &arxml_mapping_instance)
// {
//     // 输入 pdu名字与signal名字
//     uint16_t *value = (uint16_t*)get_signal_data("VehicleSpeed", "VehicleSpeed", arxml_mapping_instance);
//     std::cout << "signal value is: " << int(*value) << std::endl;

//     uint8_t *value1 = (uint8_t*)get_signal_data("VehicleSpeed", "VehicleDirection", arxml_mapping_instance);
//     std::cout << "signal value is: " << int(*value1) << std::endl;

//     uint32_t *value2 = (uint32_t*)get_signal_data("VehicleDistance", "VehicleTripDistance", arxml_mapping_instance);
//     std::cout << "signal value is: " << int(*value2) << std::endl;

//     value2 = (uint32_t*)get_signal_data("VehicleDistance", "VehicleTotalDistance", arxml_mapping_instance);
//     std::cout << "signal value is: " << int(*value2) << std::endl;
// }
>>>>>>> 2e0775b (modified types)

int main()
{
    XMLDocument doc;
    doc.LoadFile("../FEEA30.arxml");
    // doc.LoadFile("../Network.arxml");

    ArxmlMapping arxml_mapping_instance;

    XMLElement* rootElement = doc.FirstChildElement();
    // doc.Print();

    arxml_mapping_instance.GenerateMap(rootElement);

    arxml_mapping_instance.PrintIdToPduMap();
    std::cout << std::endl;

<<<<<<< HEAD
=======
    arxml_mapping_instance.PrintSignalToPduMap();
    std::cout << std::endl;

    arxml_mapping_instance.PrintSignalToLengthMap();
    std::cout << std::endl;
    
>>>>>>> 2e0775b (modified types)
    arxml_mapping_instance.PrintSignalToBaseTypeMap();
    std::cout << std::endl;

    arxml_mapping_instance.PrintBaseTypeToNativeMap();
<<<<<<< HEAD
=======
    std::cout << std::endl;
    
    arxml_mapping_instance.PrintSignalIndexInPduMap();
>>>>>>> 2e0775b (modified types)
    std::cout << std::endl;

    arxml_mapping_instance.PrintSignalToByteOrderMap();
    std::cout << std::endl;

<<<<<<< HEAD
    std::cout << "get_pcacp_data(): " << std::endl;
    get_pcap_data(arxml_mapping_instance, file_name, buffer);
    std::cout << std::endl;

    print_pcap_data();
=======
    // std::cout << "get_pcacp_data(): " << std::endl;
    // get_pcap_data(arxml_mapping_instance);
    // std::cout << std::endl;
    // print_pcap_data();
>>>>>>> 2e0775b (modified types)

    // std::cout << "If using BaseTypes: " << std::endl;
    // test1(arxml_mapping_instance);

    return 0;
}