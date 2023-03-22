arxmlMappingPcap
=========
如何运行
------
cd build

cmake ..

make

./xmltest

部分文件说明
----------
tinyxml2.h, tinyxml2.cpp: XML解析所需定义与实现，其中XMLDocument在tinyxml基础上增添了遍历函数```AcceptTree()```和```GenerateMap()```，后者用于对给定文件Network.arxml生成其内PDU和Signal之间的映射结构。tinuxml2.cpp中定义了数据结构


```std::unordered_map<int, std::string> id_to_pdu_map```: HEADER-ID与PDU名之间的映射

```std::map<std::string, std::vector<signal_offset_pair>> signal_to_pdu_map```: PDU名与(Signal名, Signal偏移量)之间的映射

```std::unordered_map<pdu_signal_pair, int, HashPair> signal_index_in_pdu_map```: (PDU名, signal名)与signal在该PDU中的编号之间的映射

```std::unordered_map<std::string, int> signal_to_length_map```: Signal名与长度之间的映射

```void PrintIdToPduMap()```: 打印 id_to_pdu_map

```void PrintSignalToPduMap()```: 打印 signal_to_pdu_map

```void PrintSignalIndexInPduMap()```: 打印 signal_index_in_pdu_map

```void PrintSignalToLengthMap()```: 打印 signal_to_length_map


xmltest.cpp: 生成可执行程序的测试文件

xmltest_copy.cpp: 原tinyxml的xmltest.cpp

