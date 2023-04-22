#ifndef ARXML_MAPPING_H_
#define ARXML_MAPPING_H_ 

#include "tinyxml2.h"
#include "PDUStruct.h"
#include "DSFSignalTree/abstractnode.h"
#include "DSFSignalTree/signaliterator.h"
#include "DSFSignalTree/signalmetadata.h"
#include "DSFSignalTree/document.h"
#include "DSFSignalTree/nodereference.h"
#include "DSFSignalTree/signalvalue.h"
#include "DSFCommon/dsfcommon.h"
#include "DSFCommon/dsftime.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

// 定义各标签名常量
const std::string kId_tagname = "HEADER-ID";
const std::string kPdu_ref_tagname = "PDU-TRIGGERING-REF";
const std::string pdu_ref_prefix = "pdu_triggering_";
const std::string kPdu_tagname1 = "I-SIGNAL-I-PDU";
const std::string kPdu_tagname2 = "NM-PDU";
const std::string kSignal_to_pdu_map_tagname = "I-SIGNAL-TO-I-PDU-MAPPING";
const std::string kSignal_ref_tagname = "I-SIGNAL-REF";
const std::string kName_tagname = "SHORT-NAME";
const std::string kSignal_offset_tagname = "START-POSITION";
const std::string kEnd_of_pdu_tagname = "UNUSED-BIT-PATTERN";
const std::string kSignal_tagname = "I-SIGNAL";
const std::string kSignal_length_tagname = "LENGTH";
const std::string kSignal_data_type_tagname = "BASE-TYPE-REF";
const std::string kSignal_byte_order_tagname = "PACKING-BYTE-ORDER";
const std::string kBase_type_tagname = "SW-BASE-TYPE";
const std::string kNative_type_name_tagname = "NATIVE-DECLARATION";

struct HashPair
{
    template <class T1, class T2>
    size_t operator() (const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{} (p.first);
        auto hash2 = std::hash<T2>{} (p.second);

        if (hash1 != hash2)
        {
            return hash1 ^ hash2;
        }
        return hash1;
    }
};

namespace dsf
{
class ArxmlMapping : public Document
{
public:
    using signal_offset_pair = std::pair<std::string, int>;
    using pdu_signal_pair = std::pair<std::string, std::string>;

    friend void get_signal_data(std::string pdu_name, std::string signal_name, const ArxmlMapping &arxml_mapping_instance);

    // 生成包含了 PDU与 Signal信息的各个 map
    bool GenerateMap(const tinyxml2::XMLElement* element);
    // 打印 std::map<int, std::string> id_to_pdu_map_
    void PrintIdToPduMap() const;
    // 打印 std::map<std::string, std::vector<signal_pair>> signal_to_pdu_map_
    void PrintSignalToPduMap() const;
    // 打印 std::unordered_map<pdu_signal_pair, int, HashPair> signal_index_in_pdu_map_
    void PrintSignalIndexInPduMap() const;
    // 打印 std::map<std::string, int> signal_to_length_map_
    void PrintSignalToLengthMap() const;
    // 打印 std::unordered_map<std::string, BaseType> signal_to_base_type_map_
    void PrintSignalToBaseTypeMap() const;
    // 打印 std::unordered_map<std::string, std::string> base_type_to_native_map_
    void PrintBaseTypeToNativeMap() const;
    // 打印 std::unordered_map<std::string, PackingByteOrder> signal_to_byte_order_map_
    void PrintSignalToByteOrderMap() const;
    // 解析文件,生成信号树
    virtual bool load(const std::string &file);
    // 打印信号树
    void PrintSignalTree() const;

public:
    tinyxml2::XMLDocument doc_;
    // PDU名和 Signal名都从引用路径中取出，未必和 SHORT-NAME相同
    // 根据 HEADER-ID取 pdu名
    std::unordered_map<long long, std::string> id_to_pdu_map_;
    // 根据 pdu名取 (signal名，signal偏移量)数组
    std::map<std::string, std::vector<signal_offset_pair>> signal_to_pdu_map_;
    // 根据 (pdu名, signal名)取 signal编号，从 1开始
    std::unordered_map<pdu_signal_pair, int, HashPair> signal_index_in_pdu_map_;
    // 根据 signal名取 length
    std::unordered_map<std::string, int> signal_to_length_map_;
    // 根据 signal名取 SW-BASE-TYPE名
    std::unordered_map<std::string, std::string> signal_to_base_type_map_;
    // 根据 SW-BASE-TYPE名取数据类型枚举值
    std::unordered_map<std::string, dsf::DataType> base_type_to_native_map_;     // 原 signal_to_type_map_
    // 根据 signal名取字节序枚举值
    std::unordered_map<std::string, PackingByteOrder> signal_to_byte_order_map_;
};
}  // namespace dsf

#endif 