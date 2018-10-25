///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
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

#ifndef _LiveLoadCP_H_
#define _LiveLoadCP_H_

template <class T>
class CProxyDVehicularLoadEvents : public IConnectionPointImpl<T, &IID_IVehicularLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnVehicularLoadChanged(IVehicularLoad * me, ChangeType type)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVehicularLoadEvents> events(sp);
         if ( events )
            events->OnVehicularLoadChanged(me,type);
		}
	}
};

template <class T>
class CProxyDVehicularLoadsEvents : public IConnectionPointImpl<T, &IID_IVehicularLoadsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnVehicularLoadsChanged(IVehicularLoad * Load, ChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVehicularLoadsEvents> events(sp);
         if ( events )
            events->OnVehicularLoadsChanged(Load,change);
		}
	}
	VOID Fire_OnVehicularLoadsRenamed(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVehicularLoadsEvents> events(sp);
         if ( events )
            events->OnVehicularLoadsRenamed(oldName,newName);
		}
	}
	VOID Fire_OnVehicularLoadsAdded(IVehicularLoad * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVehicularLoadsEvents> events(sp);
         if ( events )
            events->OnVehicularLoadsAdded(Load);
		}
	}
	VOID Fire_OnVehicularLoadsBeforeRemove(IVehicularLoad * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVehicularLoadsEvents> events(sp);
         if ( events )
            events->OnVehicularLoadsBeforeRemove(Load);
		}
	}
};

template <class T>
class CProxyDLiveLoadModelEvents : public IConnectionPointImpl<T, &IID_ILiveLoadModelEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLiveLoadModelChanged(ILiveLoadModel * me, ChangeType type)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILiveLoadModelEvents> events(sp);
         if ( events )
            events->OnLiveLoadModelChanged(me,type);
		}
	}
};

template <class T>
class CProxyDLiveLoadEvents : public IConnectionPointImpl<T, &IID_ILiveLoadEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLiveLoadChanged(ILiveLoad * me, LiveLoadModelType lltype)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILiveLoadEvents> events(sp);
         if ( events )
            events->OnLiveLoadChanged(me,lltype);
		}
	}
};


#endif