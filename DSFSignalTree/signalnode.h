#pragma once

#include "../DSFCommon/dsftime.h"
#include "abstractnode.h"
#include "signaliterator.h"

namespace dsf
{
	class SignalNode :protected AbstractNode
	{
        friend class Document;
	public:

		// Get node type
		bool isValue()const;
		bool isList()const;
		bool isStruct()const;

        // Get parameter
        void setParam(const string& key, const string& val);
        string getParam(const string& par)const;
		int size()const;

        // Get child node
        SignalNode* at(unsigned int key);
        SignalNode* at(const string& key);

        // Iterator
		SignalIterator find(const string& key) const;
		SignalIterator begin()const;
		SignalIterator end()const;


    protected:

        // Hidden functions
        using AbstractNode::add;
        using AbstractNode::remove;
        using AbstractNode::child;

        // Data update callback
        virtual void onUpdate(const DSFTime& time) const;

        // Reference CallUpdate
        void callUpdate(const DSFTime& time)const;

        // Constructor
        SignalNode(string name);
        SignalNode(SignalNode* ori);
		virtual ~SignalNode();

    protected:

        // Root
        SignalNode* m_origin = NULL;
        // References
        list<SignalNode*> m_reference;
        // Parameter
        map<string, string>* m_param;
        // Is value type
        bool m_isValue = false;
        // Is list type
		bool m_isList = false;

    private:
        // Hidden members and functions in base class 
        using AbstractNode::m_parent;

    };
}