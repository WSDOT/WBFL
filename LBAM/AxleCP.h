///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#ifndef _Axle_H_
#define _Axle_H_


template <class T>
class CProxyDAxlesEvents : public IConnectionPointImpl<T, &IID_IAxlesEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnAxlesChanged(IAxle * Axle)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAxlesEvents> events(sp);
         if ( events )
            events->OnAxlesChanged(Axle);
		}
	}
	VOID Fire_OnAxlesAdded(IAxle * Axle, AxleIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAxlesEvents> events(sp);
         if ( events )
            events->OnAxlesAdded(Axle,idx);
		}
	}
	VOID Fire_OnAxlesBeforeRemove(IAxle * Axle, AxleIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAxlesEvents> events(sp);
         if ( events )
            events->OnAxlesBeforeRemove(Axle,idx);
		}
	}
	VOID Fire_OnAxlesMoveTo(AxleIndexType from, AxleIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAxlesEvents> events(sp);
         if ( events )
            events->OnAxlesMoveTo(from,to);
		}
	}
	VOID Fire_OnAxlesCopyTo(AxleIndexType from, AxleIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAxlesEvents> events(sp);
         if ( events )
            events->OnAxlesCopyTo(from,to);
		}
	}
	VOID Fire_OnAxlesReverse()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAxlesEvents> events(sp);
         if ( events )
            events->OnAxlesReverse();
		}
	}
};

template <class T>
class CProxyDAxleEvents : public IConnectionPointImpl<T, &IID_IAxleEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnAxleChanged(IAxle * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAxleEvents> events(sp);
         if ( events )
            events->OnAxleChanged(me);
      }
	}
};

#endif