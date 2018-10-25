///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef _SuperstructureMemberCP_H_
#define _SuperstructureMemberCP_H_

template <class T>
class CProxyDSuperstructureMemberEvents : public IConnectionPointImpl<T, &IID_ISuperstructureMemberEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSuperstructureMemberChanged(ISuperstructureMember * SuperstructureMember, BSTR Stage, ChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMemberEvents> events(sp);
         if (events)
            events->OnSuperstructureMemberChanged(SuperstructureMember,Stage,change);
		}
	}
};


template <class T>
class CProxyDSuperstructureMembersEvents : public IConnectionPointImpl<T, &IID_ISuperstructureMembersEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSuperstructureMembersChanged(ISuperstructureMember * SuperstructureMember, BSTR Stage, ChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMembersEvents> events(sp);
         if ( events )
            events->OnSuperstructureMembersChanged(SuperstructureMember,Stage,change);
		}
	}
	VOID Fire_OnSuperstructureMembersAdded(ISuperstructureMember * SuperstructureMember, CollectionIndexType index)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMembersEvents> events(sp);
         if ( events )
            events->OnSuperstructureMembersAdded(SuperstructureMember,index);
		}
	}
	VOID Fire_OnSuperstructureMembersBeforeRemove(ISuperstructureMember * SuperstructureMember, CollectionIndexType index)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMembersEvents> events(sp);
         if ( events )
            events->OnSuperstructureMembersBeforeRemove(SuperstructureMember,index);
		}
	}
	VOID Fire_OnSuperstructureMembersMoveTo(CollectionIndexType from, CollectionIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMembersEvents> events(sp);
         if ( events )
            events->OnSuperstructureMembersMoveTo(from,to);
		}
	}
	VOID Fire_OnSuperstructureMembersCopyTo(CollectionIndexType from, CollectionIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMembersEvents> events(sp);
         if ( events )
            events->OnSuperstructureMembersCopyTo(from,to);
		}
	}
	VOID Fire_OnSuperstructureMembersReverse()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMembersEvents> events(sp);
         if ( events )
            events->OnSuperstructureMembersReverse();
		}
	}
	VOID Fire_OnSuperstructureMembersOffset()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperstructureMembersEvents> events(sp);
         if ( events )
            events->OnSuperstructureMembersOffset();
		}
	}
};


#endif