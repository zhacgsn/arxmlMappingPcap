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
// using namespace pcap;

// std::string file_name("../VGW_PDU_Packets.pcap");
// PDUBuffer buffer;

// void print_pcap_data()
// {
//     for (auto v : pcap_data)
//     {
//         std::cout << "The number is " << v.first;
//         for (auto [m_k, m_v] : v.second)
//         {
//             std::cout << " The PDU is " << m_k  << ", PDU offset(Byte): " << m_v << std::endl;
//         }
//         std::cout << std::endl;
//     }
// }
// 根据 pdu_name 与 siganlname 来取siganl 示例
// void get_signal_data(std::string pdu_name, std::string signal_name, const ArxmlMapping &arxml_mapping_instance)
// {
//     for (auto v : pcap_data)
//     {
//         if (v.second.count(pdu_name) == 0)
//         {
//             continue;
//         }
//         else
//         {
//             // 根据mapping，进行相应数据的取出，最后送至get_signal_value进行解析
//             int start_index = v.second[pdu_name];
//             ArxmlMapping::pdu_signal_pair tmp(pdu_name, signal_name);
//             int signal_index = arxml_mapping_instance.signal_index_in_pdu_map_.at(tmp);
//             std::vector<ArxmlMapping::signal_offset_pair>  tmp_vec = arxml_mapping_instance.signal_to_pdu_map_.at(pdu_name);
//             ArxmlMapping::signal_offset_pair sig = tmp_vec[signal_index];
//             int offset_bit = sig.second;
//             std::cout << "signal_index: " << signal_index << endl;
//             std::cout << "signal offset_bit: " << offset_bit << "  " << " PDU offset_byte: " << start_index << endl;
//             int signal_len = arxml_mapping_instance.signal_to_length_map_.at(signal_name);
//             // 根据mapping取得signal数据
//             auto value = buffer.get_signal_value(start_index, offset_bit, signal_len, arxml_mapping_instance.base_type_to_native_map_.at(arxml_mapping_instance.signal_to_base_type_map_.at(signal_name)), arxml_mapping_instance.signal_to_byte_order_map_.at(signal_name));
//             break;
//         }
//     }
// }

// void test1(const ArxmlMapping &arxml_mapping_instance)
// {
//     // 输入 pdu名字与signal名字，获得signal
//     get_signal_data("VehicleSpeed", "VehicleSpeed", arxml_mapping_instance);

//     get_signal_data("VehicleSpeed", "VehicleDirection", arxml_mapping_instance);

//     get_signal_data("VehicleDistance", "VehicleTripDistance", arxml_mapping_instance);

//     get_signal_data("VehicleDistance", "VehicleTotalDistance", arxml_mapping_instance);
// }

int main()
{
    // XMLDocument doc;
    // doc.LoadFile("../Network.arxml");
    // doc.LoadFile("../FEEA30.arxml");

    dsf::ArxmlDocument arxml_mapping_instance;
    arxml_mapping_instance.load("../Network.arxml");
    // arxml_mapping_instance.load("../FEEA30.arxml");
    arxml_mapping_instance.PrintSignalTree();
    
    // 检查各 map
    // XMLElement* rootElement = doc.FirstChildElement();
    // arxml_mapping_instance.GenerateMap(rootElement);

    // arxml_mapping_instance.PrintIdToPduMap();
    // std::cout << std::endl;

    // arxml_mapping_instance.PrintSignalToPduMap();
    // std::cout << std::endl;

    // std::cout << "get_pcacp_data(): " << std::endl;
    // get_pcap_data(arxml_mapping_instance, file_name, buffer);
    // std::cout << std::endl;
    // print_pcap_data();

    // std::cout << "If using BaseTypes: " << std::endl;
    // test1(arxml_mapping_instance);

    return 0;
}