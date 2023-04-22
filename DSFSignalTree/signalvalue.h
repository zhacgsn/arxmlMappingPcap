#pragma once

#include "signalnode.h"
#include "signalmetadata.h"

namespace dsf
{
    struct SignalValueParam
    {
        DataType type;
        dsf_scale max;
        dsf_scale min;
        dsf_scale factor;
        dsf_scale offset;
        string unit;

    };


    class SignalValue :public SignalNode
    {
        friend class Document;
    public:
        // Data type of physical value
        inline DataType type()const { return m_valParam->type; }
        // Maximum value of physical value
		inline dsf_scale max()const { return m_valParam->max; }
        // Minimum value of physical value
		inline dsf_scale min()const { return m_valParam->min; }
        // Factor of physical value
		inline dsf_scale factor()const { return m_valParam->factor; }
        // Offset of physical value
		inline dsf_scale offset()const { return m_valParam->offset; }
        // Unit of physical value
        inline string unit()const { return m_valParam->unit; }
        // Meta data
        inline SignalMetaData data()const { return *m_data; }

    protected:
        // Constructor
        SignalValue(string name);
        SignalValue(SignalNode* ori);
		virtual ~SignalValue() = default;

    protected:

        SignalValueParam* m_valParam;
        SignalMetaData* m_data;

    };
}