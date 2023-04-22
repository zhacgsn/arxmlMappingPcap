#pragma once

#include "signalvalue.h"

namespace dsf
{
    class NodeReference :public SignalValue
    {

    public:
        // Validity of root
		bool isValid()const;
		void setValid(bool is_valid);

    protected:

		//  Constructor
        NodeReference(SignalNode* ori);
        virtual ~NodeReference() = default;

        virtual void onUpdate(const DSFTime& time) const;
    private:
        // Hidden members and functions in base class 
        using AbstractNode::m_children;
        using AbstractNode::add;
        using AbstractNode::remove;
        using AbstractNode::child;

    private:

		// Is root valid
        bool m_isValid = false;
    };
    
}

