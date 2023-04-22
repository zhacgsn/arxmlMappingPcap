#include "signalnode.h"

#include "nodereference.h"


bool dsf::SignalNode::isValue() const
{
	return m_isValue;
}

bool dsf::SignalNode::isList() const
{
	return m_isList;
}

bool dsf::SignalNode::isStruct() const
{
	return !isValue() && !isList();
}

void dsf::SignalNode::setParam(const string& key, const string& val)
{
    m_param->insert({key,val});
}

string dsf::SignalNode::getParam(const string& par) const
{

    if (m_param->find(par) == m_param->end())
	{
		return "";
	}
    return m_param->at(par);
}

int dsf::SignalNode::size() const
{
	return m_children.size();
}

dsf::SignalNode* dsf::SignalNode::at(const string& key) 
{
	return (SignalNode*)(child(key));
}

dsf::SignalNode* dsf::SignalNode::at(unsigned int key) 
{
	return at(std::to_string(key));
}

dsf::SignalIterator dsf::SignalNode::find(const string& key) const
{
	return m_children.find(key);
}

dsf::SignalIterator dsf::SignalNode::begin() const
{
	return m_children.begin();
}

dsf::SignalIterator dsf::SignalNode::end() const
{
	return m_children.end();
}

dsf::SignalNode::SignalNode(SignalNode* ori) :
m_origin(ori),
m_param(ori->m_param)
{
    if (ori != NULL)
    {
        ori->m_reference.push_back(this);
    }
}

dsf::SignalNode::SignalNode(string name) :AbstractNode(name)
{
    m_param = new map<string, string>();
}

dsf::SignalNode::~SignalNode()
{
    if (m_origin)
    {
        m_origin->m_reference.remove(this);
    }

    for (SignalNode* ref : m_reference)
	{
        ref->m_origin = DSF_NULLPTR;
        dynamic_cast<NodeReference*>(ref)->setValid(false);
	}
    m_reference.clear();
}


void dsf::SignalNode::onUpdate(const DSFTime& time) const
{
	SignalIterator itr = begin();
	for (; itr != end(); ++itr)
	{
        SignalNode* ref = itr.signal();
        ref->onUpdate(time);
	}

    for (SignalNode* ref : m_reference)
    {
        ref->onUpdate(time);
    }
}

void dsf::SignalNode::callUpdate(const DSFTime& time) const
{
    if (m_origin != NULL)
    {
        m_origin->onUpdate(time);
    }
}

