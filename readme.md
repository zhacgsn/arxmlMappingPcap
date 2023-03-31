arxmlMappingPcap
=========

arxmlMappingPcap是一个根据给定.arxml配置文件读取.pcap文件中UDP报文中PDU及Signal的工具，其工作流程大致如下图所示

<img src="./Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230323221253319.png" alt="image-20230323221253319" style="zoom: 50%;" />

## What it does

简单来说，arxmlMappingPcap程序从.arxml文件中获取PDU及Signal相关定义，再根据定义从UDP报文中读出各PDU及Signal的具体数据。目前只支持样例文件：Network.arxml和VGW_PDU_Packets.pcap。

## What it doesn't do

对任意.arxml文件生成PDU及Signal定义，并从任意.pcap文件中读出PDU及Signal数据。因为

1. PDU和Signal的相关定义是从.arxml文件中某些特定标签（Element）的文本（Text）中找出来的，选择从哪些标签来找的这一过程，是在编写源代码前由我们**观察**出来的
2. 对于某些定义如Signal的数据类型，不同的定义值需要不同的条件分支来处理，而不同.arxml文件中这些定义的命名规则未必一致

于是，想得到一个对任意.arxml和.pcap文件都通用的解析工具，首先需要考虑如何以统一的方法处理不同.arxml文件中定义的不统一情况。

Build and run
------

```shell
$ git clone https://github.com/zhacgsn/arxmlMappingPcap

$ cd build

$ cmake ..

$ make

$ ./xmltest
```

### Some results

id_to_pdu_map（HEADER-ID到PDU名的映射）: 

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230320211758758.png" alt="image-20230320211758758" style="zoom:50%;" />

signal_to_pdu_map（PDU名到Signal名及后者在前者中的位偏移量的映射）: 

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230320211842423.png" alt="image-20230320211842423" style="zoom:50%;" />

signal_to_length_map（Signal名到Signal位数的映射）: 

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230320211946536.png" alt="image-20230320211946536" style="zoom:50%;" />

signal_index_in_pdu_map（PDU及其包含的Signal到后者在前者中序号的映射）**:** 

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230320212052710.png" alt="image-20230320212052710" style="zoom:50%;" />

PDU在UDP报文中编号与PDU名、字节偏移量：

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230320212159398.png" alt="image-20230320212159398" style="zoom:50%;" />

样例.pcap文件中各Signal数据

![image-20230323203143171](/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230323203143171.png)

## Figure out .arxml file structure

为读取报文中PDU及Signal，主要关注.arxml文件中PDU与Signal定义及关系。

首先从下图这部分标签可确定I-PDU在socket通信中的标识符HEADER-ID，如HEADER-ID 65536100标识了.pcap文件中UDP报文Data段开头为65536100的报文属于PDU VehicleSpeed。

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230323204030766.png" alt="image-20230323204030766"  />

接着，再从下图这部分标签结构确定I-SIGNAL-I-PDU VehicleSpeed长度为4个字节，它包含了I-SIGNAL VehicleSpeed和VehicleDirection（不同.arxml文件中，PDU和SIGNAL命名不一定，SHORT-NAME标签的文本是否为命名也不一定），这两个Signal在该PDU中的起始位置分别为0和16位（bit），最高有效字节在最后。

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230321095035216.png" alt="image-20230321095035216" style="zoom: 33%;" />

值得一提的是，可以猜测像PDU-TRIGGERING-REF和I-SIGNAL-REF这类“REF”标签的文本的末尾大概为PDU和Signal名称，而SHORT-NAME则不一定。

接着，根据上图I-SIGNAL-REF可找到各对应Signal定义，如从下图标签结构可确定I-SIGNAL VehicleSpeed长度为16个比特，在AUTOSAR中的基本数据类型为A_UINT16。

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230321095500189.png" alt="image-20230321095500189" style="zoom:33%;" />

再根据SYSTEM-SIGNAL-REF可进而找到SYSTEM-SIGNAL和COMPU-METHOD中Signal VehicleSpeed的定义，包含了该Signal的物理单位和计算方法等。

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230321095947521.png" alt="image-20230321095947521" style="zoom:33%;" />

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230321100053422.png" alt="image-20230321100053422" style="zoom:33%;" />

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

<img src="/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230320210550500.png" alt="image-20230320210550500" style="zoom:50%;" />

部分报文结构如上图，其中标注彩色部分为UDP报文Data段数据，读取时先去除前面非彩色部分的报文头部，再读取HEADER-ID，据此确定之后的字节为哪个PDU的Signal数据，再读取LENGTH（PDU的字节数）确定该PDU中Signal的总长度。如该例可确定HEADER-ID为03e80064 H（十进制为65536100）的PDU（名称为VehicleSpeed）包含的Signal的总长度为00000004 H（十进制为4）个字节，于是之后的4个字节000001ff H为该PDU中各Signal的数据部分，至于如何确定PDU名、包括的Signal以及各Signal长度、数据类型，则通过查询之前定义的各个映射结构来进行。

目前，Signal的数据是读入了根据其数据类型定义好的c语言中对应数据类型（如uint8_t、uint16_t、uint32_t）的变量。

除Data段外，.pcap文件中UDP报文的头部信息也可读入如下所示的结构体

```C++
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
```

## Problems

1. API格式是什么样的？
2. 根据 HEADER-ID取PDU名时，PDU-TRIGGERING-REF命名不规范，目前从最后一个'/'分割，如果分割后含'pdu_triggering_'，将其去除![image-20230331155632413](/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230331155632413.png)

![image-20230331155655920](/Users/zhacgsn/VSProjects/arxml-mapping-pcap/resources/image-20230331155655920.png)