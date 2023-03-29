#pragma once

enum class BaseType
{
    // SW-BASE-TYPE, NATIVE-DECLARATION
    A_UINT8,        // uint8_t
    A_UINT16,       // uint16_t
    A_UINT32,       // uint32_t
    boolean,        // unsigned char
    float32,        // float
    float64,        // double
    sint8,          // signed char
    sint16,         // signed short
    sint32,         // signed long
    uint8,          // unsigned char
    uint16,         // unsigned short
    uint32,         // unsigned long
    uint64          // unsigned long long
};

enum class PackingByteOrder
{
    most_significant_byte_last,
    most_significant_byte_first
};