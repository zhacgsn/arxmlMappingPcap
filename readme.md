arxmlMappingPcap
=========
如何运行
------
cmake .

make

./xmltest

部分文件说明
----------
tinyxml2.h, tinyxml2.cpp: XML解析所需定义与实现，其中XMLDocument在tinyxml基础上增添了遍历函数AcceptTree()和generateMap3()，后者用于对给定文件Network.arxml生成其内PDU和Signal之间的映射结构。

···std::map<int, std::string> id_to_pdu_map;···


xmltest.cpp: 生成可执行程序的测试文件

xmltest_copy.cpp: 原tinyxml的xmltest.cpp

