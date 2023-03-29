arxmlMappingPcap
=========

arxmlMappingPcap是一个根据给定.arxml配置文件读取.pcap文件中UDP报文中PDU及Signal的工具，其工作流程大致如下图所示

## What it does

简单来说，arxmlMappingPcap程序从.arxml文件中获取PDU及Signal相关定义，再根据定义从UDP报文中读出各PDU及Signal的具体数据。目前只支持样例文件：Network.arxml和VGW_PDU_Packets.pcap。

Build and run
------

```shell
$ git clone https://github.com/zhacgsn/arxmlMappingPcap

$ cd build

$ cmake ..

$ make

$ ./xmltest
```

What these files do
----------

### tinyxml2.h, tinyxml2.cpp

XML解析所需定义与实现，主要完成解析.arxml文件，建立DOM树

### arxml_mapping.h, arxml_mapping.cc

定义及实现类ArxmlMapping，主要包括数据结构与函数如

`std::unordered_map<int, std::string> id_to_pdu_map_`: HEADER-ID与PDU名之间的映射

`std::map<std::string, std::vector<signal_offset_pair>> signal_to_pdu_map_`: PDU名与(Signal名, Signal偏移量（bit）)之间的映射

`std::unordered_map<pdu_signal_pair, int, HashPair> signal_index_in_pdu_map_`: (PDU名, Signal名)与Signal在该PDU中的编号之间的映射

`std::unordered_map<std::string, int> signal_to_length_map_`: Signal名与长度（bit）之间的映射

`std::unordered_map<std::string, BaseType> signal_to_type_map_`: Signal名与其数据类型枚举值之间的映射

`std::unordered_map<std::string, PackingByteOrder> signal_to_byte_order_map_`: Signal名与其字节序枚举值之间的映射

```void PrintIdToPduMap()```: 打印 id_to_pdu_map_

```void PrintSignalToPduMap()```: 打印 signal_to_pdu_map_

```void PrintSignalIndexInPduMap()```: 打印 signal_index_in_pdu_map_

```void PrintSignalToLengthMap()```: 打印 signal_to_length_map_

`void PrintSignalToTypeMap()`：打印 signal_to_type_map_

`void PrintSignalToByteOrderMap()`: 打印 signal_to_byte_order_map_

### PDUBuffer.h, PDUBuffer.cc

定义内存管理类` class PDUBuffer`，用于将UDP报文Data段中各signal数据部分读入数据成员 `char* buffer_`指定的内存区域，实现 `PDUBuffer`。

### xmltest.cpp:

生成可执行测试程序。定义了用于读取.pcap文件内容的函数 `void get_pcap_data()`，依次读取文件中的每个UDP报文。
