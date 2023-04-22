#include "document.h"


dsf::Document::Document() :SignalNode("")
{
    m_isValue = false;
    m_isList = false;
}

dsf::Document::~Document()
{
    clear();
}

void dsf::Document::clear()
{
    for (std::pair<dsf_name, AbstractNode*>child : m_children)
    {
        DSF_DELETE(child.second);
    }
    m_children.clear();
}

dsf::SignalNode* dsf::Document::createStruct(string name)
{
    SignalNode* structNode = new SignalNode(name);
    structNode->m_isValue = false;
    structNode->m_isList = false;
    return structNode;
}

dsf::SignalNode* dsf::Document::createList(string name)
{
    SignalNode* listNode = new SignalNode(name);
    listNode->m_isValue = false;
    listNode->m_isList = true;
    return listNode;
}

dsf::SignalValue* dsf::Document::createValue(string name, SignalValueParam param, const map<int, string>& enumStr /*= map<int, string>()*/)
{
    SignalValue* valNode = new SignalValue(name);
    *(valNode->m_valParam) = param;
    valNode->m_data->setEnumName(enumStr);
    valNode->m_isValue = true;
    valNode->m_isList = false;
    return valNode;
}

void dsf::Document::removeNode(SignalNode*& node)
{
    node->m_parent->remove(node->m_name);
}

void dsf::Document::nodeAppend(SignalNode* root, SignalNode* child)
{
    if (!root->isList())
    {
        return;
    }
    child->m_name = std::to_string(root->size());
    root->add(child);
}

void dsf::Document::nodeAdd(SignalNode* root, SignalNode* child)
{
    if (!root->isStruct())
    {
        return;
    }
    root->add(child);
}
