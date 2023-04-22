#pragma once

#include "signalvalue.h"

namespace dsf
{
    class Document :public SignalNode
    {
    public:
        Document();
        virtual ~Document();;

        virtual bool load(const string& file) = 0;
        void clear();

    protected:
        SignalNode* createStruct(string name);
        SignalNode* createList(string name);
        SignalValue* createValue(string name, SignalValueParam param, const map<int, string>& enumStr = map<int, string>());
        void removeNode(SignalNode*& node);
        void nodeAppend(SignalNode* root, SignalNode* child);
        void nodeAdd(SignalNode* root, SignalNode* child);

    private:
        // ���صĻ���ӿ�
        using SignalNode::isValue;
        using SignalNode::isList;
        using SignalNode::onUpdate;
        using SignalNode::m_reference;

    };

}