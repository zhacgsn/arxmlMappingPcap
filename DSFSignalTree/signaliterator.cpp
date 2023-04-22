#include "signaliterator.h"
#include "signalnode.h"

bool dsf::SignalIterator::operator!=(const SignalIterator& itr)
{
	return m_itr != itr.m_itr;
}

bool dsf::SignalIterator::operator==(const SignalIterator& itr)
{
	return m_itr == itr.m_itr;
}

void dsf::SignalIterator::operator=(const SignalIterator& itr)
{
	m_itr = itr.m_itr;
}

dsf::SignalIterator::SignalIterator(map<dsf_name, AbstractNode*>::const_iterator itr): m_itr(itr)
{

}

dsf::SignalIterator& dsf::SignalIterator::operator++()
{
	m_itr++;
	return *this;
}

dsf::dsf_name dsf::SignalIterator::name() const
{
	return m_itr->first;
}

dsf::SignalNode* dsf::SignalIterator::signal() const
{
    AbstractNode* child = (m_itr->second);
    return (SignalNode*)child;
}
