#pragma once

#include <map>
#include <string>
#include <list>

using std::string;
using std::map;
using std::list;

#if 1
#define DSF_NULLPTR NULL
#else
#define DSF_NULLPTR nullptr
#endif

#define DSF_DELETE(p) if(p!=DSF_NULLPTR){delete p;p=DSF_NULLPTR;}

namespace dsf
{
    typedef string dsf_name;
    typedef double dsf_scale;

    enum DataType
    {
        DSF_BOOLEAN,
        DSF_INT8,
        DSF_UINT8,
        DSF_INT16,
        DSF_UINT16,
        DSF_INT32,
        DSF_UINT32,
        DSF_INT164,
        DSF_UINT64,
        DSF_FLOAT32,
        DSF_FLOAT64,
        DSF_ENUM,
        DSF_STRING
    };
}