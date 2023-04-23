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
#include "DSFSignalTree/nodereference.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>





namespace dsf
{
class ArxmlDocument : public Document
{
public:
    // 解析文件,生成信号树
    virtual bool load(const std::string &file);
    // 打印信号树
    void PrintSignalTree() const;

private:

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

    using signal_offset_pair = std::pair<std::string, int>;
    using pdu_signal_pair = std::pair<std::string, std::string>;

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
 // namespace dsf

class ARXMLMessageRef : public NodeReference
{
public:
    ARXMLMessageRef(SignalNode* ori) : NodeReference(ori) {}
    void update(const char *buf, size_t len, const DSFTime& time)
    {
        // 当前索引下标
        int cur_idx = 0;

        uint32_t *net_id;
        net_id = (uint32_t *)&buf[cur_idx];
        uint32_t id = htonl(*net_id);
        cur_idx += m_pdu_id_len;

        uint32_t *net_pdu_len;
        net_pdu_len = (uint32_t *)&buf[cur_idx];
        uint32_t pdu_len = htonl(*net_pdu_len);
        cur_idx += m_pdu_length_len;
        
        // 找到pdu
        std::string str_id = std::to_string(id);
        std::cout << "The pdu id is " << str_id << std::endl;
        SignalNode *pdu =  m_origin->at(str_id);

        for (auto itr = pdu->begin(); itr != pdu->end(); ++itr) {
            DataType t = dynamic_cast<SignalValue*>(itr.signal())->type();
            dsf_scale offset_bit = dynamic_cast<SignalValue*>(itr.signal())->offset();
        //     switch (t)
        //     {
        //     case DSF_UINT8:
        //         if (offset_bit % 8 == 0 && signal_len == 8)
        //         {
        //             uint8_t *tmp_value = (uint8_t*)&buffer_[start_index + offset_bit/8];
        //             //uint8_t value = htonl(*tmp_value);
        //             std::cout << "(1)A_UINT8: " << int(*tmp_value)<< std::endl;
        //             return *tmp_value;
        //         }
        //         else if (offset_bit % 8 == 0)
        //         {
        //             int left_bit = 8 - signal_len;
        //             uint8_t *tmp_value = (uint8_t*)&buffer_[start_index + offset_bit/8];
        //             uint8_t value = *tmp_value >> left_bit;
        //             std::cout << "(2)A_UINT8: " << (int)value<< std::endl;
        //             return value;
        //         }
        //         else
        //         {
        //             uint16_t *tmp_value = (uint16_t*)&buffer_[start_index + offset_bit/8];
        //             int left_offset = offset_bit % 8;
        //             int left_bit = 8 - signal_len;
        //             uint16_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htons(*tmp_value);
        //             uint8_t value = uint16_t(tmp_v << left_offset) >> (8 + left_bit);
        //             std::cout << "(3)A_UINT8: " << (uint16_t)value<< std::endl;
        //             return value;
        //         }
        //         break;
        //     case NativeType::A_SIGNED_CHAR:
        //         if (offset_bit % 8 == 0 && signal_len == 8)
        //         {
        //             int8_t *tmp_value = (int8_t*)&buffer_[start_index + offset_bit/8];
        //             //uint8_t value = htonl(*tmp_value);
        //             std::cout << "(1)A_INT8: " << int(*tmp_value)<< std::endl;
        //             return *tmp_value;
        //         }
        //         else if (offset_bit % 8 == 0)
        //         {
        //             int left_bit = 8 - signal_len;
        //             int8_t *tmp_value = (int8_t*)&buffer_[start_index + offset_bit/8];
        //             int8_t value = *tmp_value >> left_bit;
        //             std::cout << "(2)A_INT8: " << (int)value<< std::endl;
        //             return value;
        //         }
        //         else
        //         {
        //             int16_t *tmp_value = (int16_t*)&buffer_[start_index + offset_bit/8];
        //             int left_offset = offset_bit % 8;
        //             int left_bit = 8 - signal_len;
        //             int16_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htons(*tmp_value);
        //             int8_t value = int16_t(tmp_v << left_offset) >> (8 + left_bit);
        //             std::cout << "(3)A_INT8: " << (int16_t)value<< std::endl;
        //             return value;
        //         }
        //         break;
        //     case NativeType::A_UNSIGNED_SHORT:
        //         if (offset_bit % 8 == 0 && signal_len == 16)
        //         {
        //             uint16_t *tmp_value = (uint16_t*)&buffer_[start_index + offset_bit/8];
        //             uint16_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htons(*tmp_value);
        //             uint16_t value = tmp_v;
        //             std::cout << "(1)A_UINT16: " << value << std::endl;
        //             return value;
        //         }
        //         else if (offset_bit % 8 == 0)
        //         {
        //             int left_bit = 16 - signal_len;
        //             uint32_t *tmp_value = (uint32_t*)&buffer_[start_index + offset_bit/8];
        //             uint32_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
        //             uint16_t value = tmp_v >> (16 + left_bit);
        //             std::cout << "(2)A_UINT16: " << value << std::endl;
        //             return value;            
        //         }
        //         else
        //         {
        //             uint32_t *tmp_value = (uint32_t*)&buffer_[start_index + offset_bit/8];
        //             int left_offset = offset_bit % 8;
        //             int left_bit = 16 - signal_len;
        //             uint32_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
        //             uint16_t value = uint32_t(tmp_v << left_offset) >> (16 + left_bit);
        //             std::cout << "(3)A_UINT16: " << value<< std::endl;
        //             return value;
        //         }
        //         break;
        //     case NativeType::A_SIGNED_SHORT:
        //         if (offset_bit % 8 == 0 && signal_len == 16)
        //         {
        //             int16_t *tmp_value = (int16_t*)&buffer_[start_index + offset_bit/8];
        //             int16_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htons(*tmp_value);
        //             int16_t value = tmp_v;
        //             std::cout << "(1)A_INT16: " << value << std::endl;
        //             return value;
        //         }
        //         else if (offset_bit % 8 == 0)
        //         {
        //             int left_bit = 16 - signal_len;
        //             int32_t *tmp_value = (int32_t*)&buffer_[start_index + offset_bit/8];
        //             int32_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
        //             int16_t value = tmp_v >> (16 + left_bit);
        //             std::cout << "(2)A_INT16: " << value << std::endl;
        //             return value;            
        //         }
        //         else
        //         {
        //             int32_t *tmp_value = (int32_t*)&buffer_[start_index + offset_bit/8];
        //             int left_offset = offset_bit % 8;
        //             int left_bit = 16 - signal_len;
        //             int32_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
        //             int16_t value = int32_t(tmp_v << left_offset) >> (16 + left_bit);
        //             std::cout << "(3)A_INT16: " << value<< std::endl;
        //             return value;
        //         }
        //         break;
        //     case NativeType::A_UNSIGNED_LONG:
        //         if (offset_bit % 8 == 0 && signal_len == 32)
        //         {
        //             uint32_t *tmp_value = (uint32_t*)&buffer_[start_index + offset_bit/8];
        //             uint32_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
        //             uint32_t value = tmp_v;
        //             std::cout << "(1)A_UINT32: " << value << std::endl;
        //             return value;
        //         }
        //         else if (offset_bit % 8 == 0)
        //         {
        //             int left_bit = 32 - signal_len;
        //             uint64_t *tmp_value = (uint64_t*)&buffer_[start_index + offset_bit/8];
        //             uint64_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonll(*tmp_value);
        //             uint32_t value = tmp_v >> (32 + left_bit);
        //             std::cout << "(2)A_UINT32: " << value << std::endl;
        //             return value;              
        //         }
        //         else
        //         {
        //             uint64_t *tmp_value = (uint64_t*)&buffer_[start_index + offset_bit/8];
        //             int left_offset = offset_bit % 8;
        //             int left_bit = 32 - signal_len;
        //             uint64_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonll(*tmp_value);
        //             uint32_t value = uint64_t(tmp_v << left_offset) >> (32 + left_bit);
        //             std::cout << "(3)A_UINT32: " << value<< std::endl;
        //             return value;
        //         }   
        //         break;
        //     case NativeType::A_SIGNED_LONG:
        //         if (offset_bit % 8 == 0 && signal_len == 32)
        //         {
        //             int32_t *tmp_value = (int32_t*)&buffer_[start_index + offset_bit/8];
        //             int32_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonl(*tmp_value);
        //             int32_t value = tmp_v;
        //             std::cout << "(1)A_INT32: " << value << std::endl;
        //             return value;
        //         }
        //         else if (offset_bit % 8 == 0)
        //         {
        //             int left_bit = 32 - signal_len;
        //             int64_t *tmp_value = (int64_t*)&buffer_[start_index + offset_bit/8];
        //             int64_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonll(*tmp_value);
        //             int32_t value = tmp_v >> (32 + left_bit);
        //             std::cout << "(2)A_INT32: " << value << std::endl;
        //             return value;              
        //         }
        //         else
        //         {
        //             int64_t *tmp_value = (int64_t*)&buffer_[start_index + offset_bit/8];
        //             int left_offset = offset_bit % 8;
        //             int left_bit = 32 - signal_len;
        //             int64_t tmp_v = *tmp_value;
        //             if (order == PackingByteOrder::most_significant_byte_first)  tmp_v = htonll(*tmp_value);
        //             int32_t value = int64_t(tmp_v << left_offset) >> (32 + left_bit);
        //             std::cout << "(3)A_INT32: " << value<< std::endl;
        //             return value;
        //         }   
        //         break;
        //     default:
        //         break;
        //     }            
        }

        callUpdate(time);
    }
private:
    const int m_pdu_id_len{4};
    const int m_pdu_length_len{4};
};

}
#endif 