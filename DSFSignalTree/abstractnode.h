#pragma once

#include "../DSFCommon/dsfcommon.h"

namespace dsf
{
    class AbstractNode
    {
    public:
        
        // Constructor
        AbstractNode(string name = "", AbstractNode* parent = NULL);
        virtual ~AbstractNode();

        // Add Child
		void add(AbstractNode* _child);
        // Remove Child
		void remove(dsf_name _name);
        // Get Child
		const AbstractNode* child(dsf_name _name) const;
		AbstractNode* child(dsf_name _name);

	protected:

        // Name
        string m_name;
        // Parent Node
        AbstractNode* m_parent;
        // Child Nodes
        map<dsf_name, AbstractNode*> m_children;

    };
}