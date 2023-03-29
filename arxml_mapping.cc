#include "tinyxml2.h"
#include "PDUStruct.h"
#include "arxml_mapping.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <stack>

// 深度优先
bool ArxmlMapping::GenerateMap(const tinyxml2::XMLElement* element)
{
    std::stack<const tinyxml2::XMLElement*> elementStack;
    const tinyxml2::XMLElement* tempElement = element;

    // 记录当前遍历层级
    int count = -1;
    int pdu_count = INT_MAX;
    int pdu_name_count = INT_MAX;
    int pdu_id_count = INT_MAX;
    int signal_count = INT_MAX;

    // 标识是否位于 signal标签内部
    bool is_in_signal = false;
    // 标识是否位于 pdu标签内部（I-SIGNAL-I-PDU和其他 PDU如 NM-PDU是并列关系）
    bool is_in_pdu = false;

    // 标识是否已确定 signal名和 offset
    bool signal_set = false;
    bool offset_set = false;
    
    int pdu_id;
    std::string pdu_ref_name;
    std::string pdu_name;
    std::string signal_name;
    // 从 PDU定义中取出
    std::string real_signal_name;
    // 从 Signal定义中取出
    std::string real_signal_name2;
    // std::string father_name = "";
    std::string data_type_name;
    int signal_offset;
    int signal_lenth = 0;
    int signal_in_pdu_count = 0;

    std::vector<signal_offset_pair> signal_offset_pair_vec;

    while (tempElement != NULL || !elementStack.empty())
    {
        while (tempElement != NULL)
        {
            // 遍历到 HEADER-ID标签
            if (tempElement->Name() == kId_tagname)
            {
                // std::cout << "HEADER-ID: " << tempElement->GetText() << std::endl;
                pdu_id_count = count;
                pdu_id = atoi(tempElement->GetText());
            }
            // 处理 PDU-TRIGGERING-REF，从路径取出 PDU名
            if (count == pdu_id_count && tempElement->Name() == kPdu_ref_tagname)
            {
                // std::cout << "PDU-TRIGGERING-REF: " << tempElement->GetText() << std::endl;
                pdu_ref_name = tempElement->GetText();
                // int pos = pdu_ref_name.find_last_of('_') + 1;
                int pos = pdu_ref_name.find(pdu_ref_prefix);
                pdu_ref_name = pdu_ref_name.substr(pos + pdu_ref_prefix.size());
                // std::cout << "HEADER-ID " << pdu_id << "---->PDU: " << pdu_ref_name << std::endl;
                id_to_pdu_map_.emplace(pdu_id, pdu_ref_name);
            }
            // 遍历到 pdu标签名，记录此时层级 count
            if (tempElement->Name() == kPdu_tagname1 || tempElement->Name() == kPdu_tagname2)
            {
                // std::cout << tempElement->Name();
                pdu_count = count;
                pdu_name_count = pdu_count + 1;
                is_in_pdu = true;
                // 进入新 pdu，signal重新计数
            }
            // pdu SHORT-NAME, 不只是 I-PDU这一种 PDU!
            if (count == pdu_name_count && tempElement->Name() == kName_tagname)
            {
                // std::cout << "pdu名: " << tempElement->GetText() << std::endl;
                pdu_name = tempElement->GetText();
                signal_in_pdu_count = 0;
            }
            // signal SHORT-NAME (IDxx)
            if (count > pdu_name_count && tempElement->Name() == kName_tagname)
            {
                // std::cout << "signal SHORT-NAME: " << tempElement->GetText() << std::endl;
                signal_name = tempElement->GetText();
                signal_set = true;
            }
            // 处理 I-SIGNAL-REF，从路径取出 signal名
            if (count > pdu_name_count && tempElement->Name() == kSignal_ref_tagname)
            {
                // std::cout << "signal名: " << tempElement->GetText() << std::endl;
                real_signal_name = tempElement->GetText();
                int pos = real_signal_name.find_last_of('/') + 1;
                real_signal_name = real_signal_name.substr(pos);
                // std::cout << "real signal名: " << real_signal_name << std::endl;
            }
            if (count > pdu_name_count && tempElement->Name() == kSignal_byte_order_tagname)
            {
                std::string byte_order = tempElement->GetText();
                if (byte_order == "MOST-SIGNIFICANT-BYTE-LAST")
                {
                    PackingByteOrder order = PackingByteOrder::most_significant_byte_last;
                    signal_to_byte_order_map_.emplace(real_signal_name, order);
                }
                if (byte_order == "MOST-SIGNIFICANT-BYTE-FIRST")
                {
                    PackingByteOrder order = PackingByteOrder::most_significant_byte_first;
                    signal_to_byte_order_map_.emplace(real_signal_name, order);
                }
            }
            // 映射标签名
            if (count > pdu_count && tempElement->Name() == kSignal_to_pdu_map_tagname)
            {
                // std::cout << tempElement->Name();
            }
            // signal偏移量
            if (count > pdu_count && tempElement->Name() == kSignal_offset_tagname)
            {
                // std::cout << tempElement->GetText() << std::endl;
                signal_offset = atoi(tempElement->GetText());
                offset_set = true;
            }
            // 某 pdu内某 signal的名字和偏移量均已确定
            if (count > pdu_count && signal_set && offset_set)
            {
                // std::cout << "pdu: " << pdu_name << " has signal: " << real_signal_name << "at " << signal_offset << std::endl;
                // signal index vector
                signal_offset_pair_vec.push_back(std::make_pair(real_signal_name, signal_offset));
                // std::cout << "In PDU " << pdu_name << ", signal " << real_signal_name << " is at number " << signal_in_pdu_count << std::endl;
                signal_index_in_pdu_map_.emplace(std::make_pair(pdu_name, real_signal_name), signal_in_pdu_count);
                signal_in_pdu_count++;

                signal_set = false;
                offset_set = false;
            }
            // 当前 pdu内 signal名字与偏移量已加入 vector
            if (count > pdu_count && tempElement->Name() == kEnd_of_pdu_tagname)
            {
                // vector加入 map
                signal_to_pdu_map_.emplace(pdu_name, signal_offset_pair_vec);
                // 清空 vector，用于存放下一个 pdu的signal
                signal_offset_pair_vec.clear();
                is_in_pdu = false;
            }
            if (tempElement->Name() == kSignal_tagname)
            {
                signal_count = count;
                is_in_signal = true;
            }
            if (count == signal_count + 1 && tempElement->Name() == kName_tagname)
            {
                real_signal_name2 = tempElement->GetText();
                // std::cout << "signal: " << real_signal_name2;
            }
            // signal长度
            if (count == signal_count + 1 && tempElement->Name() == kSignal_length_tagname)
            {
                signal_lenth = atoi(tempElement->GetText());
                // std::cout << " length: " << signal_lenth << std::endl;
                signal_to_length_map_.emplace(real_signal_name2, signal_lenth);
            }
            // signal数据类型 有层级正确但不是signal的！
            if (is_in_signal && count > signal_count + 1 && tempElement->Name() == kSignal_data_type_tagname)
            {
                data_type_name = tempElement->GetText();
                int pos = data_type_name.find_last_of('/') + 1;
                data_type_name = data_type_name.substr(pos);

                // 插入 Signal名与类型枚举值映射
                if (data_type_name == "A_UINT8")
                {
                    BaseType type = BaseType::A_UINT8;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "A_UINT16")
                {
                    BaseType type = BaseType::A_UINT16;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "A_UINT32")
                {
                    BaseType type = BaseType::A_UINT32;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "boolean")
                {
                    BaseType type = BaseType::boolean;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "float32")
                {
                    BaseType type = BaseType::float32;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "float64")
                {
                    BaseType type = BaseType::float64;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "sint8")
                {
                    BaseType type = BaseType::sint8;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "sint16")
                {
                    BaseType type = BaseType::sint16;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "sint32")
                {
                    BaseType type = BaseType::sint32;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "uint8")
                {
                    BaseType type = BaseType::uint8;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "uint16")
                {
                    BaseType type = BaseType::uint16;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "uint32")
                {
                    BaseType type = BaseType::uint32;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                else if (data_type_name == "uint64")
                {
                    BaseType type = BaseType::uint64;
                    signal_to_type_map_.emplace(real_signal_name2, type);
                }
                // std::cout << "signal: " << real_signal_name2 << " data type: " << data_type_name << " enum BaseType: " << static_cast<int>(signal_to_type_map.at(real_signal_name2)) << std::endl;
                is_in_signal = false;
            }
            elementStack.push(tempElement);
            // 进入孩子
            tempElement = tempElement->FirstChildElement();
            count++;
        }
        // father_name = tempElement->Name();
        count--;
        tempElement = elementStack.top();
        elementStack.pop();
        // 进入兄弟
        tempElement = tempElement->NextSiblingElement();
    }
    return true;
}

// 打印 std::map<int, std::string> id_to_pdu_map
void ArxmlMapping::PrintIdToPduMap() const
{
    std::cout << "id_to_pdu_map: " << std::endl;
    for (const auto &[id, pdu] : id_to_pdu_map_)
    {
        std::cout << "HEADER-ID " << id << "---->PDU: " << pdu << std::endl;
    }
}

// 打印 std::map<std::string, std::vector<signal_pair>> signal_to_pdu_map
void ArxmlMapping::PrintSignalToPduMap() const
{
    std::cout << "signal_to_pdu_map: " << std::endl;
    for (const auto &it : signal_to_pdu_map_)
    {
        std::cout << "PDU " << it.first << " has signal: " << std::endl;

        for (const auto &signal_it : it.second)
        {
            std::cout << "\t" << signal_it.first << " at offset " << signal_it.second << std::endl;
        }
    }
}

// 打印 std::unordered_map<pdu_signal_pair, int, HashPair> signal_index_in_pdu_map;
void ArxmlMapping::PrintSignalIndexInPduMap() const
{
    std::cout << "signal_index_in_pdu_map: " << std::endl;
    for (const auto &it : signal_index_in_pdu_map_)
    {
        std::cout << "In PDU " << it.first.first << ", signal " << it.first.second << " is at index " << it.second << std::endl;
    }
}

// 打印 std::map<std::string, int> signal_to_length_map
void ArxmlMapping::PrintSignalToLengthMap() const
{
    std::cout << "signal_to_length_map: " << std::endl;
    for (const auto &[signal, length] : signal_to_length_map_)
    {
        std::cout << "Signal " << signal << " has length: " << length << std::endl;
    }
}

// 打印 std::unordered_map<std::string, BaseType> signal_to_type_map
void ArxmlMapping::PrintSignalToTypeMap() const
{
    std::cout << "signal_to_type_map: " << std::endl;
    for (const auto &[signal, type] : signal_to_type_map_)
    {
        std::cout << "Signal " << signal << "'s BaseType is (enum) " << static_cast<int>(type) << std::endl;
    }
}

// 打印 std::unordered_map<std::string, PackingByteOrder> signal_to_byte_order_map
void ArxmlMapping::PrintSignalToByteOrderMap() const
{
    std::cout << "signal_to_byte_order_map: " << std::endl;
    for (const auto &[signal, byte_order] : signal_to_byte_order_map_)
    {
        std::cout << "Signal " << signal << "'s PackingByteOrder is " << static_cast<int>(byte_order) << std::endl;
    }
}