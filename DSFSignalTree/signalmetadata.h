#pragma once
#include "../DSFCommon/dsfcommon.h"

namespace dsf
{
    class SignalMetaData
    {
    public:

        // Get data type of meta data
		inline DataType type()const { return m_type; }
		inline DataType& type() { return m_type; }
        
        // Set enum name map
		void setEnumName(const map<int, string>& enumMap);

        // Print enum using name in map
        string paintEnum()const;

        // Set/Get meta data as data type
        void set(void* data);
        const void* get()const;

		inline void setBool(bool val) { m_data.b = val; }
		inline bool getBool() const { return m_data.b; }
		inline void setInt8(char val) { m_data.i8 = val; }
		inline char getInt8() const { return m_data.i8; }
		inline void setUint8(unsigned char val) { m_data.ui8 = val; }
		inline unsigned char getUint8()const { return m_data.ui8; }
		inline void setInt16(short val) { m_data.i16 = val; }
		inline short getInt16()const { return m_data.i16; }
		inline void setUint16(unsigned short val) { m_data.ui16 = val; }
		inline unsigned short getUint16()const { return m_data.ui16; }
		inline void setInt32(int val) { m_data.i32 = val; }
		inline int getInt32()const { return m_data.i32; }
		inline void setUint32(unsigned int val) { m_data.ui32 = val; }
		inline unsigned int getUint32()const { return m_data.ui32; }
		inline void setInt64(long val) { m_data.i64 = val; }
		inline long getInt64()const { return m_data.i64; }
		inline void setUint64(unsigned long val) { m_data.ui64 = val; }
		inline unsigned long getUint64()const { return m_data.ui64; }
		inline void setFloat32(float val) { m_data.f32 = val; }
		inline float getFloat32() const { return m_data.f32; }
		inline void setFloat64(double val) { m_data.f64 = val; }
		inline double getFloat64()const { return m_data.f64; }
		inline void setString(const string& val) { m_strData = val; }
		inline string getString()const { return m_strData; }
		inline void setEnum(int val) { setInt32(val); }
		inline int getEnum()const { return getInt32(); }

    protected:
        // Basic data type union
        union Data
        {
            bool b;
            char i8;
            unsigned char ui8;
            short i16;
            unsigned short ui16;
            int i32;
            unsigned int ui32;
            long i64;
            unsigned long ui64;
            float f32;
            double f64;
        };

    protected:
        // String data
        string m_strData;
        // Meta data
        Data m_data;
        // Enum map
        map<int, string> m_enumMap;
        // Data type
        DataType m_type;
    };
}