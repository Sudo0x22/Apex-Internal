#pragma once
#include<cstdint>
#include <string.h>
#include"../capture/capture.hpp"
class recv_table;

class RecvProp
{
public:
    char* m_pVarName;
    void* m_RecvType;
    int                     m_Flags;
    int                     m_StringBufferSize;
    int                     m_bInsideArray;
    const void* m_pExtraData;
    RecvProp* m_pArrayProp;
    void* m_ArrayLengthProxy;
    void* m_ProxyFn;
    void* m_DataTableProxyFn;
    recv_table* m_pDataTable;
    int                     m_Offset;
    int                     m_ElementStride;
    int                     m_nElements;
    const char* m_pParentArrayPropName;
};

class recv_table
{
public:

    RecvProp* m_pProps;
    int            m_nProps;
    void* m_pDecoder;
    char* m_pNetTableName;
    bool        m_bInitialized;
    bool        m_bInMainList;
};

