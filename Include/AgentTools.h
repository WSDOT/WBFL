///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2017  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
#ifndef INCLUDED_AGENTTOOLS_H_
#define INCLUDED_AGENTTOOLS_H_

#include <ATLBase.h>

#if defined _DEBUG
template <class T>
class CIFacePtr : public ATL::CComPtr<T>
{
public:
	CIFacePtr() throw()
	{
      m_bUsed = false;
	}
	CIFacePtr(int nNull) throw() :
		ATL::CComPtr<T>(nNull)
	{
      m_bUsed = false;
	}
	CIFacePtr(T* lp) throw() :
		ATL::CComPtr<T>(lp)
	{
      m_bUsed = false;
	}
	CIFacePtr(_In_ const CIFacePtr<T>& lp) throw() :
		ATL::CComPtr<T>(lp.p)
	{
      m_bUsed = false;
	}
	~CIFacePtr() throw()
	{
      // this assert fires when the interface is never used
      ATLASSERT(m_bUsed == true);
	}

   operator T*() const throw()
	{
      m_bUsed = true;
		return p;
	}

	ATL::_NoAddRefReleaseOnCComPtr<T>* operator->() const throw()
	{
      m_bUsed = true;
		ATLASSERT(p!=nullptr);
		return (ATL::_NoAddRefReleaseOnCComPtr<T>*)p;
	}

protected:
   mutable bool m_bUsed; // gets set to true if the interface is used
};
#else
#define CIFacePtr CComPtr
#endif

#define GET_IFACE(_i_,_ptr_) \
   CIFacePtr<_i_> _ptr_; \
   m_pBroker->GetInterface( IID_##_i_, (IUnknown**)&_ptr_ ); \
   ASSERT( _ptr_.p != nullptr )

#define GET_IFACE_(_ns_,_i_,_ptr_) \
   CIFacePtr<_ns_::_i_> _ptr_; \
   m_pBroker->GetInterface( ##_ns_::IID_##_i_, (IUnknown**)&_ptr_ ); \
   ASSERT( _ptr_.p != nullptr )

#define GET_IFACE_NOCHECK(_i_,_ptr_) \
   CComPtr<_i_> _ptr_; \
   m_pBroker->GetInterface( IID_##_i_, (IUnknown**)&_ptr_ ); \
   ASSERT( _ptr_.p != nullptr )

#define GET_IFACE_NOCHECK_(_ns_,_i_,_ptr_) \
   CComPtr<_ns_::_i_> _ptr_; \
   m_pBroker->GetInterface( ##_ns_::IID_##_i_, (IUnknown**)&_ptr_ ); \
   ASSERT( _ptr_.p != nullptr )

#define GET_IFACE2(_b_,_i_,_ptr_) \
   CIFacePtr<_i_> _ptr_; \
   _b_->GetInterface( IID_##_i_, (IUnknown**)&_ptr_ ); \
   ASSERT( _ptr_.p != nullptr )

#define GET_IFACE2_(_ns_,_b_,_i_,_ptr_) \
   CIFacePtr<_ns_::_i_> _ptr_; \
   _b_->GetInterface( ##_ns_::IID_##_i_, (IUnknown**)&_ptr_ ); \
   ASSERT( _ptr_.p != nullptr )

#define GET_IFACE2_NOCHECK(_b_,_i_,_ptr_) \
   CComPtr<_i_> _ptr_; \
   _b_->GetInterface( IID_##_i_, (IUnknown**)&_ptr_ ); \
   ASSERT( _ptr_.p != nullptr )

#define GET_IFACE2_NOCHECK_(_ns_,_b_,_i_,_ptr_) \
   CComPtr<_i_> _ptr_; \
   _b_->GetInterface( ##_ns_::IID_##_i_, (IUnknown**)&_ptr_ ); \
   ASSERT( _ptr_.p != nullptr )


#endif // INCLUDED_AGENTTOOLS_H_