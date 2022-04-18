///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifndef _LBAMCP_H_
#define _LBAMCP_H_

template <class T>
class CProxyDLBAMModelEvents : public IConnectionPointImpl<T, &IID_ILBAMModelEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnModelChanged(ILBAMModel * me, ChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILBAMModelEvents> events(sp);
         if ( events)
            events->OnModelChanged(me,change);
		}
	}
};



template <class T>
class CProxyDDistributionFactorSegmentEvents : public IConnectionPointImpl<T, &IID_IDistributionFactorSegmentEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnDistributionFactorSegmentChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributionFactorSegmentEvents> events(sp);
         if ( events )
            events->OnDistributionFactorSegmentChanged();
		}
	}
};

template <class T>
class CProxyDDistributionFactorEvents : public IConnectionPointImpl<T, &IID_IDistributionFactorEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnDistributionFactorChanged(IDistributionFactor * me)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributionFactorEvents> events(sp);
         if ( events )
            events->OnDistributionFactorChanged(me);
		}
	}
};



template <class T>
class CProxyDDistributionFactorsEvents : public IConnectionPointImpl<T, &IID_IDistributionFactorsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnDistributionFactorsChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributionFactorsEvents> events(sp);
         if ( events )
            events->OnDistributionFactorsChanged();
		}
	}
	VOID Fire_OnDistributionFactorsAdded(IDistributionFactorSegment * DistributionFactor, CollectionIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributionFactorsEvents> events(sp);
         if ( events )
            events->OnDistributionFactorsAdded(DistributionFactor,idx);
		}
	}
	VOID Fire_OnDistributionFactorsBeforeRemove(IDistributionFactorSegment * DistributionFactor, CollectionIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributionFactorsEvents> events(sp);
         if ( events )
            events->OnDistributionFactorsBeforeRemove(DistributionFactor,idx);
		}
	}
	VOID Fire_OnDistributionFactorsMoveTo(CollectionIndexType from, CollectionIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributionFactorsEvents> events(sp);
         if ( events )
            events->OnDistributionFactorsMoveTo(from,to);
		}
	}
	VOID Fire_OnDistributionFactorsCopyTo(CollectionIndexType from, CollectionIndexType to)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributionFactorsEvents> events(sp);
         if ( events )
            events->OnDistributionFactorsCopyTo(from,to);
		}
	}
	VOID Fire_OnDistributionFactorsReverse()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDistributionFactorsEvents> events(sp);
         if ( events )
            events->OnDistributionFactorsReverse();
		}
	}
};

template <class T>
class CProxyDLoadCasesEvents : public IConnectionPointImpl<T, &IID_ILoadCasesEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLoadCasesChanged(ILoadCase * Load, ChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILoadCasesEvents> events(sp);
         if ( events )
            events->OnLoadCasesChanged(Load,change);
		}
	}
	VOID Fire_OnLoadCasesRenamed(BSTR oldName, BSTR newName)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILoadCasesEvents> events(sp);
         if ( events )
            events->OnLoadCasesRenamed(oldName,newName);
		}
	}
	VOID Fire_OnLoadCasesAdded(ILoadCase * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILoadCasesEvents> events(sp);
         if ( events )
            events->OnLoadCasesAdded(Load);
		}
	}
	VOID Fire_OnLoadCasesBeforeRemove(ILoadCase * Load)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILoadCasesEvents> events(sp);
         if ( events )
            events->OnLoadCasesBeforeRemove(Load);
		}
	}
};

#endif