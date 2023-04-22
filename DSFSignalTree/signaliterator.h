#pragma once

#include "abstractnode.h"

namespace dsf
{
    class SignalNode;

    class SignalIterator
    {
    public:
        
		SignalIterator(map<dsf_name, AbstractNode*>::const_iterator itr);

		void operator=(const SignalIterator& itr);
		bool operator==(const SignalIterator& itr);
		bool operator!=(const SignalIterator& itr);
		SignalIterator& operator++();

        // Name
		dsf_name name()const;

        // Node
        SignalNode* signal()const;
        
    private:
        map<dsf_name, AbstractNode*>::const_iterator m_itr;
    };
}