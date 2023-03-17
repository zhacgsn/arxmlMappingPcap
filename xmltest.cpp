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
#include <map>
#include <arpa/inet.h>
#include <math.h>
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
// pdu编号 pdu名 signal地址
std::vector<std::pair<int, std::map<std::string, std::vector<char*>>>> pcap_data;

std::vector<std::string> char_vec;

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
            // std::cout << "id: " << id << " len: " << len << std::endl;
            uint32_t net_pdu_len;
            fread(&net_pdu_len, sizeof(uint32_t), 1, fp);
            uint32_t pdu_len = htonl(net_pdu_len);
            len -= sizeof(uint32_t);
            // std::cout << "pdu_len: " << pdu_len << " len: "<< len << std::endl;

            // 读入内存
            char *buf;
			buf = (char *)malloc(pdu_len);
            fread(buf, 1, pdu_len, fp);
			char_vec.push_back(buf);
			// std::cout << "buf len: " << strlen(buf) << std::endl;

            len -= pdu_len;
            // int *tmp = (int *)&buf[0];
            // std::cout << " value " << *tmp << std::endl;
            std::string name = id_to_pdu_map[id];
            std::vector<signal_offset_pair> sigs = signal_to_pdu_map[name];
            std::map<std::string, std::vector<char*>> mp;
            for (auto sig : sigs)
            {
                uint64_t start_offset = sig.second;

				if (count < 4)
				{
					std::cout << "start_offset: " << start_offset << std::endl;
					printf("buf %p\n", buf);
					printf("buf[start_offset] %p\n", &buf[start_offset]);
				}
                mp[name].push_back(&buf[start_offset]);
				
            }
            pcap_data.push_back(std::make_pair(count, mp));
            count++;
        }
    }
}

void print_pcap_data()
{
    for (auto v : pcap_data)
    {
        std::cout << "The number is " << v.first;
        for (auto [m_k, m_v] : v.second)
        {
            std::cout << "The PDU is " << m_k << " The address is ";
            for (auto v_v : m_v)
            {
                printf("%p\t", v_v);
            }
        }
        std::cout << std::endl;
    }
    
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
    	print_pcap_data();
	}
    return 0;
}