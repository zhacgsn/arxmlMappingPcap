// #include <string>
// #include <map>
// #include "AIGCJson.hpp"

// class I_SIGNAL_I_PDU;
// class I_PDU_TIMING_SPECIFICATIONS;
// class I_PDU_TIMING;
// class TRANSMISSION_MODE_DECLARATION;
// class TRANSMISSION_MODE_CONDITIONS;
// class TRANSMISSION_MODE_CONDITION;
// class DATA_FILTER;
// class I_SIGNAL_IN_I_PDU_REF;
// class TRANSMISSION_MODE_TRUE_TIMING;
// class CYCLIC_TIMING;
// class TIME_PERIOD;
// class I_SIGNAL_TO_PDU_MAPPINGS;
// class I_SIGNAL_TO_I_PDU_MAPPING;
// class I_SIGNAL_REF;

// std::map<std::string, int> ClassType = {{"I_SIGNAL_I_PDU", 0}, {"I_PDU_TIMING_SPECIFICATIONS", 1}, {"I_PDU_TIMING", 2}, 
//                                         {"TRANSMISSION_MODE_DECLARATION", 3}, {"TRANSMISSION_MODE_CONDITIONS", 4}, {"TRANSMISSION_MODE_CONDITION", 5}, 
//                                         {"DATA_FILTER", 6}, {"I_SIGNAL_IN_I_PDU_REF", 7}, {"TRANSMISSION_MODE_TRUE_TIMING", 8}, 
//                                         {"CYCLIC_TIMING", 9}, {"TIME_PERIOD", 10}, {"I_SIGNAL_TO_PDU_MAPPINGS", 11}, 
//                                         {"I_SIGNAL_TO_I_PDU_MAPPING", 12}, {"I_SIGNAL_REF", 13}, {"UUID", 14}, 
//                                         {"SHORT_NAME", 15}, {"LENGTH", 16}, {"UNUSED_BIT_PATTERN", 17}, 
//                                         {"DATA_FILTER_TYPE", 18}, {"DEST", 19}, {"VALUE", 20}};


// class I_SIGNAL_REF
// {
// public:
//     std::string DEST;
//     std::string text;
// };

// class I_SIGNAL_TO_I_PDU_MAPPING
// {
// public:
//     std::string UUID;
//     std::string SHORT_NAME;
//     I_SIGNAL_REF i_signal_ref;
//     std::string PACKING_BYTE_ORDER;
//     std::string START_POSITION;
//     std::string TRANSFER_PROPERTY;
// };

// class I_SIGNAL_TO_PDU_MAPPINGS
// {
// public:
//     I_SIGNAL_TO_I_PDU_MAPPING i_signal_to_i_pdu_mapping[18];
// };

// class TIME_PERIOD
// {
// public:
//     std::string VALUE;
// };

// class CYCLIC_TIMING
// {
// public:
//     TIME_PERIOD time_period;
// };

// class TRANSMISSION_MODE_TRUE_TIMING
// {
// public:
//     CYCLIC_TIMING cyclic_timing;
// };

// class I_SIGNAL_IN_I_PDU_REF
// {
// public:
//     std::string DEST;
//     std::string text;
// };

// class DATA_FILTER
// {
// public:
//     std::string DATA_FILTER_TYPE;
// };

// class TRANSMISSION_MODE_CONDITION
// {
// public:
//     DATA_FILTER data_filter;
//     I_SIGNAL_IN_I_PDU_REF i_signal_in_i_pdu_ref;
// };

// class TRANSMISSION_MODE_CONDITIONS
// {
// public:
//     TRANSMISSION_MODE_CONDITION transmission_mode_condition[18];
// };

// class TRANSMISSION_MODE_DECLARATION
// {
// public:
//     TRANSMISSION_MODE_CONDITIONS transmission_mode_conditions;
//     TRANSMISSION_MODE_TRUE_TIMING transmission_mode_true_timing;
// };

// class I_PDU_TIMING
// {
// public:
//     TRANSMISSION_MODE_DECLARATION transmission_mode_declaration;
// };

// class I_PDU_TIMING_SPECIFICATIONS
// {
// public:
//     I_PDU_TIMING i_pdu_timing;
// };

// class I_SIGNAL_I_PDU
// {
// public:
//     std::string UUID;
//     std::string SHORT_NAME;
//     std::string LENGTH;
//     I_PDU_TIMING_SPECIFICATIONS i_pdu_timing_specifications;
//     I_SIGNAL_TO_PDU_MAPPINGS i_signal_to_pdu_mappings;
//     std::string UNUSED_BIT_PATTERN;
// };