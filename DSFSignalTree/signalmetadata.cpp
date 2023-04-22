#include "signalmetadata.h"



void dsf::SignalMetaData::setEnumName(const map<int, string>& enumMap)
{
    if (enumMap.empty())
    {
        return;
    }
	m_enumMap = enumMap;
}

string dsf::SignalMetaData::paintEnum() const
{
	if (m_enumMap.find(getInt32()) == m_enumMap.end())
	{
		return "";
	}
	return m_enumMap.at(getInt32());
}

void dsf::SignalMetaData::set(void* data)
{
	switch (m_type)
	{
	case dsf::DSF_BOOLEAN:return setBool(*(bool*)data);
	case dsf::DSF_INT8:return setInt8(*(char*)data);
	case dsf::DSF_UINT8:return setUint8(*(unsigned char*)data);
	case dsf::DSF_INT16:return setInt16(*(short*)data);
	case dsf::DSF_UINT16:return setUint16(*(unsigned short*)data);
	case dsf::DSF_ENUM:
	case dsf::DSF_INT32:return setInt32(*(int*)data);
	case dsf::DSF_UINT32:return setUint32(*(unsigned int*)data);
	case dsf::DSF_INT164:return setInt64(*(long*)data);
	case dsf::DSF_UINT64:return setUint64(*(unsigned long*)data);
	case dsf::DSF_FLOAT32:return setFloat32(*(float*)data);
	case dsf::DSF_FLOAT64:return setFloat64(*(double*)data);
	case dsf::DSF_STRING:return setString(*(string*)data);
	default:return setInt32(*(int*)data);
	}

}

const void* dsf::SignalMetaData::get() const
{
	if (m_type == DSF_STRING)
	{
		return &m_strData;
	}
	else
	{
		return &m_data;
	}
}
