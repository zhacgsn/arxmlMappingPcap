#if defined( _MSC_VER )
	#if !defined( _CRT_SECURE_NO_WARNINGS )
		#define _CRT_SECURE_NO_WARNINGS		// This test file is not intended to be secure.
	#endif
#endif

#include "tinyxml2.h"
#include "ARXMLDocument.h"


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

int main()
{

    dsf::ArxmlDocument arxml_mapping_instance;
    arxml_mapping_instance.load("../Network.arxml");
    // arxml_mapping_instance.load("../FEEA30.arxml");
    arxml_mapping_instance.PrintSignalTree();
    
    dsf::ArxmlMessageRef arxml_message(&arxml_mapping_instance);
    dsf::DSFTime dfstime;
    char buf[12]{0x03, static_cast<char>(0xe8), 0x00, 0x64, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01, static_cast<char>(0xff)};
    arxml_message.update(buf, 12, dfstime);

    char buf1[16]{0x03, static_cast<char>(0xe8), 0x00, 0x65, 0x00, 0x00, 0x00, 0x08, static_cast<char>(0x80), static_cast<char>(0x96), static_cast<char>(0x98), 0x00, static_cast<char>(0xa4), 0x4d, 0x18, 0x00};
    arxml_message.update(buf1, 16, dfstime);
    
    return 0;
}