#include "signalvalue.h"


dsf::SignalValue::SignalValue(SignalNode* ori) :SignalNode(ori)
{
    if (!m_origin || !m_origin->isValue())
    {
        return;
    }
    m_valParam = dynamic_cast<SignalValue*>(m_origin)->m_valParam;
    m_data = dynamic_cast<SignalValue*>(m_origin)->m_data;
}

dsf::SignalValue::SignalValue(string name) : SignalNode(name)
{
    m_valParam = new SignalValueParam;
    m_data = new SignalMetaData;
}
