///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifndef _SupportCP_H_
#define _SupportCP_H_

template <class T>
class CProxyDSupportEvents : public IConnectionPointImpl<T, &IID_ISupportEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSupportChanged(ISupport * Support, BSTR Stage, ChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISupportEvents> events(sp);
         if ( events )
            events->OnSupportChanged(Support,Stage,change);
		}
	}
};


template <class T>
class CProxyDTemporarySupportEvents : public IConnectionPointImpl<T, &IID_ITemporarySupportEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnTemporarySupportChanged(ITemporarySupport * TemporarySupport, BSTR Stage, ChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemporarySupportEvents> events(sp);
         if ( events )
            events->OnTemporarySupportChanged(TemporarySupport,Stage,change);
		}
	}
};




template <class T>
class CProxyDTemporarySupportsEvents : public IConnectionPointImpl<T, &IID_ITemporarySupportsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnTemporarySupportsChanged(ITemporarySupport * Support, BSTR Stage, ChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemporarySupportsEvents> events(sp);
         if (events)
            events->OnTemporarySupportsChanged(Support,Stage,change);
		}
	}
	VOID Fire_OnTemporarySupportsAdded(ITemporarySupport * Support, SupportIndexType id)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemporarySupportsEvents> events(sp);
         if (events)
            events->OnTemporarySupportsAdded(Support,id);
		}
	}
	VOID Fire_OnTemporarySupportsBeforeRemove(ITemporarySupport * Support, SupportIndexType id)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemporarySupportsEvents> events(sp);
         if (events)
            events->OnTemporarySupportsBeforeRemove(Support,id);
		}
	}
};

template <class T>
class CProxyDSupportsEvents : public IConnectionPointImpl<T, &IID_ISupportsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSupportsChanged(ISupport * Support, BSTR Stage, ChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISupportsEvents> events(sp);
         if ( events )
            events->OnSupportsChanged(Support,Stage,change);
		}
	}
	VOID Fire_OnSupportsAdded(ISupport * Support, SupportIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISupportsEvents> events(sp);
         if ( events )
            events->OnSupportsAdded(Support,idx);
		}
	}
	VOID Fire_OnSupportsBeforeRemove(ISupport * Support, SupportIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISupportsEvents> events(sp);
         if ( events )
            events->OnSupportsBeforeRemove(Support,idx);
		}
	}
	VOID Fire_OnSupportsMoveTo(SupportIndexType from, SupportIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISupportsEvents> events(sp);
         if ( events )
            events->OnSupportsMoveTo(from,to);
		}
	}
	VOID Fire_OnSupportsCopyTo(SupportIndexType from, SupportIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISupportsEvents> events(sp);
         if ( events )
            events->OnSupportsCopyTo(from,to);
		}
	}
	VOID Fire_OnSupportsReverse()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISupportsEvents> events(sp);
         if ( events )
            events->OnSupportsReverse();
		}
	}
};

#endif