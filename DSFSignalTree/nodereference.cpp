#include "nodereference.h"



bool dsf::NodeReference::isValid() const
{
    return m_isValid;
}

void dsf::NodeReference::setValid(bool is_valid)
{
	m_isValid = is_valid;
}


dsf::NodeReference::NodeReference(SignalNode* ori) :SignalValue(ori)
{
    if (ori != DSF_NULLPTR)
    {
        setValid(true);
    }
}


void dsf::NodeReference::onUpdate(const DSFTime& time) const
{
    printf("ou\n");
}

