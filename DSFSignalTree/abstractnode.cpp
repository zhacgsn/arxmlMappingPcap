#include "abstractnode.h"



dsf::AbstractNode::AbstractNode(string name, AbstractNode* parent /*= NULL*/) :m_name(name), m_parent(parent)
{

}

dsf::AbstractNode::~AbstractNode()
{
	for (std::pair<dsf_name, AbstractNode*> p : m_children)
	{
		DSF_DELETE(p.second);
	}
}

void dsf::AbstractNode::add(AbstractNode* _child)
{
    string _name = _child->m_name;
	if (m_children.find(_name) != m_children.end())
	{
		return;
	}
	m_children.insert({ _name,_child });
    _child->m_parent = this;
}

void dsf::AbstractNode::remove(dsf_name _name)
{
	if (m_children.find(_name) == m_children.end())
	{
		return;
	}
	AbstractNode* node = child(_name);
	DSF_DELETE(node);
	m_children.erase(_name);
}

dsf::AbstractNode* dsf::AbstractNode::child(dsf_name _name)
{
	if (m_children.find(_name) == m_children.end())
	{
		return NULL;
	}
	return m_children.at(_name);
}

const dsf::AbstractNode* dsf::AbstractNode::child(dsf_name _name) const
{
    if (m_children.find(_name) == m_children.end())
    {
        return NULL;
    }
    return m_children.at(_name);
}
