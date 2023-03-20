#if defined( _MSC_VER )
	#if !defined( _CRT_SECURE_NO_WARNINGS )
		#define _CRT_SECURE_NO_WARNINGS		// This test file is not intended to be secure.
	#endif
#endif

#include "tinyxml2.h"
#include "tinyxml2.cpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>
#define MAXSIZE 100

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
int gPass = 0;
int gFail = 0;

bool XMLTest (const char* testString, const char* expected, const char* found, bool echo=true, bool extraNL=false )
{
	bool pass;
	if ( !expected && !found )
		pass = true;
	else if ( !expected || !found )
		pass = false;
	else
		pass = !strcmp( expected, found );
	if ( pass )
		printf ("[pass]");
	else
		printf ("[fail]");

	if ( !echo ) {
		printf (" %s\n", testString);
	}
	else {
		if ( extraNL ) {
			printf( " %s\n", testString );
			printf( "%s\n", expected );
			printf( "%s\n", found );
		}
		else {
			printf (" %s [%s][%s]\n", testString, expected, found);
		}
	}

	if ( pass )
		++gPass;
	else
		++gFail;
	return pass;
}

bool XMLTest(const char* testString, XMLError expected, XMLError found, bool echo = true, bool extraNL = false)
{
    return XMLTest(testString, XMLDocument::ErrorIDToName(expected), XMLDocument::ErrorIDToName(found), echo, extraNL);
}

bool XMLTest(const char* testString, bool expected, bool found, bool echo = true, bool extraNL = false)
{
    return XMLTest(testString, expected ? "true" : "false", found ? "true" : "false", echo, extraNL);
}

template< class T > bool XMLTest( const char* testString, T expected, T found, bool echo=true )
{
	bool pass = ( expected == found );
	if ( pass )
		printf ("[pass]");
	else
		printf ("[fail]");

	if ( !echo )
		printf (" %s\n", testString);
	else {
		char expectedAsString[64];
		XMLUtil::ToStr(expected, expectedAsString, sizeof(expectedAsString));

		char foundAsString[64];
		XMLUtil::ToStr(found, foundAsString, sizeof(foundAsString));

		printf (" %s [%s][%s]\n", testString, expectedAsString, foundAsString );
	}

	if ( pass )
		++gPass;
	else
		++gFail;
	return pass;
}

void NullLineEndings( char* p )
{
	while( p && *p ) {
		if ( *p == '\n' || *p == '\r' ) {
			*p = 0;
			return;
		}
		++p;
	}
}
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <arpa/inet.h>
#include <math.h>
#include "PDUBuffer.cc"

/*pcap file header*/
typedef struct PcapFileHeader
{
    char   magic[4];
    uint16_t   version_major;
    uint16_t   version_minor;
    int32_t    thiszone;      /*时区修正*/
    uint32_t   sigfigs;       /*精确时间戳*/
    uint32_t   snaplen;       /*抓包最大长度*/
    uint32_t   linktype;      /*链路类型*/
} PcapFileHeader_t;

/*pcap packet header*/
typedef struct PcapPkthdr
{
    uint32_t   seconds;     /*秒数*/
    uint32_t   u_seconds;   /*毫秒数*/
    uint32_t   caplen;      /*数据包长度*/
    uint32_t   len;         /*文件数据包长度*/
} PcapPkthdr_t;


const int LEN_GLOBAL_PCAP_HEADER = 24;
const int LEN_PCAP_HEADER = 16;
const int LEN_UDP_HEADER = 46;
std::string file_name("./VGW_PDU_Packets.pcap");

// int为 在buffer中的起始位置
using pdu_pair = std::pair<std::string, int>;
// std::vector<std::pair<int, std::map<std::string, std::vector<char*>>>> pcap_data;
// 需要保存siganal的索引位置，因为buffer扩容后地址可能发生变化，int 为偏移量
std::vector<std::pair<int, std::map<std::string, int>>> pcap_data;
PDUBuffer buffer;

void get_pcap_data()
{ 
    int count = 0;

    FILE *fp = fopen(file_name.c_str(), "rb");
    if (fp==NULL) 
    {
        printf("open file error... \n");
    }
    PcapFileHeader_t pcapFileHeader = {0};
    PcapPkthdr_t packetHeader = {0};
    fread(&packetHeader, sizeof(PcapFileHeader_t), 1, fp);
    // 每个udp最后包含的pdu是一个完整的pdu
    while (!feof(fp))
    {
        fread(&packetHeader, sizeof(PcapPkthdr_t), 1, fp);
        int len = packetHeader.caplen;
        std::cout << "packetHeadergetLen: " << len << std::endl;
        fseek(fp, LEN_UDP_HEADER, SEEK_CUR);
        len -= LEN_UDP_HEADER;
        while (len > 0)
        {
            //void *p_net_id = nullptr;
            uint32_t net_id;
            fread(&net_id, sizeof(uint32_t), 1, fp);
            //fread(p_net_id, 4, 1, fp);
            //printf("hello world \n");
            //uint32_t *net_id = ((uint32_t *)p_net_id);
            uint32_t id = htonl(net_id);
            len -= sizeof(uint32_t);
            std::cout << "id: " << id << " len: " << len << std::endl;
            
            uint32_t net_pdu_len;
            fread(&net_pdu_len, sizeof(uint32_t), 1, fp);
            uint32_t pdu_len = htonl(net_pdu_len);
            len -= sizeof(uint32_t);
            std::cout << "pdu_len: " << pdu_len << " len: "<< len << std::endl;

            // 读入内存
            // char *buf = (char *)malloc(pdu_len);
            // fread(buf, 1, pdu_len, fp);
            // len -= pdu_len;
            int start_write_index = buffer.get_write_index();
            fread(buffer.get_next_write_address(pdu_len), 1, pdu_len, fp);
            buffer.update_write_index(pdu_len);
            len -= pdu_len;

            std::string name = id_to_pdu_map[id];
            std::map<std::string, int> mp;
            mp[name] = start_write_index;
            pcap_data.push_back(std::make_pair(count, mp));
            
            // // int *tmp = (int *)&buf[0];
            // // std::cout << " value " << *tmp << std::endl;
            // std::string name = id_to_pdu_map[id];
            // std::vector<signal_pair> sigs = signal_to_pdu_map[name];
            // // std::map<std::string, std::vector<char*>> mp;
            // std::map<pdu_pair, std::vector<int>> mp;
            // pdu_pair tmp_pdu_pair(name, start_write_index);
            // for (auto sig : sigs)
            // {
            //     uint64_t start_index = sig.second;
            //     // mp[name].push_back(&buf[start_index]);
            //     mp[tmp_pdu_pair].push_back(start_index);
            // }
            // pcap_data.push_back(std::make_pair(count, mp));
            count++;
        }
    }
}

// void print_pcap_data()
// {
//     for (auto v : pcap_data)
//     {
//         std::cout << "The number is " << v.first;
//         for (auto [m_k, m_v] : v.second)
//         {
//             std::cout << " The PDU is " << m_k << " The index is ";
//             for (auto v_v : m_v)
//             {
//                 std::cout << v_v << "  ";
//             }
//         }
//         std::cout << std::endl;
//     }
// }

// void print_pcap_data()
// {
//     for (auto v : pcap_data)
//     {
//         std::cout << "The number is " << v.first;
//         for (auto [m_k, m_v] : v.second)
//         {
//             std::cout << " The PDU is " << m_k.first  << ", PDU offset(Byte): " << m_k.second << " The signal offset(Bit) and address are ";
//             for (int i = 0; i < m_v.size(); ++i)
//             {
//                 std::cout << "\t" << m_v[i] << "  " << static_cast<void*>(buffer.get_start_address_by_index((int)m_v[i] / 8));
//             }
//         }
//         std::cout << std::endl;
//     }
    
// }

char* get_signal_data(std::string pdu_name, std::string signal_name)
{
    // for (auto [key, value] : pcap_data)
    // {
    //     for (auto [k, v] : value)
    //     {
    //         if (k.first == pdu_name)
    //         {
    //             int start_index = k.second;
    //             // 需进行非空判断
    //             pdu_signal_pair tmp(pdu_name, signal_name);
    //             int index = signal_index_in_pdu_map[tmp];
    //             std::vector<signal_offset_pair>  tmp_vec = signal_to_pdu_map[pdu_name];
    //             signal_offset_pair sig = tmp_vec[index];
    //             int number = sig.second;
    //             int siganl_offset = v[number];
    //             return buffer.get_start_address_by_index(start_index + siganl_offset\8);
    //         }
    //     }
    // }

    for (auto v : pcap_data)
    {
        if (v.second.count(pdu_name) == 0)
        {
            continue;
        }
        else
        {
            int start_index = v.second[pdu_name];
            pdu_signal_pair tmp(pdu_name, signal_name);
            int signal_index = signal_index_in_pdu_map[tmp];
            std::vector<signal_offset_pair>  tmp_vec = signal_to_pdu_map[pdu_name];
            signal_offset_pair sig = tmp_vec[signal_index];
            int offset_bit = sig.second;
            std::cout << "signal_index: " << signal_index << endl;
            std::cout << "offset_bit: " << offset_bit << "  " << "start_index: " << start_index << endl;
            return buffer.get_start_address_by_index(start_index + offset_bit / 8);

        }
    }
    return nullptr;
}

void test1()
{
    // 输入 pdu名字与signal名字
    int *value = (int *)get_signal_data("VehicleSpeed", "VehicleSpeed");
    std::cout << "the value is " << *index << std::endl;
}

int main()
{
    XMLDocument doc;
    doc.LoadFile("Network.arxml");

    {
		XMLElement* rootElement = doc.FirstChildElement();
		// doc.Print();
		doc.GenerateMap(rootElement);
		PrintIdToPduMap();
		std::cout << endl;
		PrintSignalToPduMap();
		std::cout << endl;
		PrintSignalToLengthMap();
		std::cout << endl;
		PrintSignalIndexInPduMap();
		std::cout << std::endl;
		get_pcap_data();
		// print_pcap_data();

        test1();
	}
    return 0;
}