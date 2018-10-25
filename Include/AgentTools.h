///////////////////////////////////////////////////////////////////////
#ifndef INCLUDED_AGENTTOOLS_H_
#define INCLUDED_AGENTTOOLS_H_

#include <ATLBase.h>

#define GET_IFACE(i,p) \
   CComPtr<i> p; \
   m_pBroker->GetInterface( IID_##i, (void**)&p ); \
   ASSERT( p != NULL )

#define GET_IFACE2(b,i,p) \
   CComPtr<i> p; \
   b->GetInterface( IID_##i, (void**)&p ); \
   ASSERT( p != NULL )


#endif // INCLUDED_AGENTTOOLS_H_