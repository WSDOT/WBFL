///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright (C) 2009  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#ifndef _CrossSection_H_
#define _CrossSection_H_


template <class T>
class CProxyDStressPointEvents : public IConnectionPointImpl<T, &IID_IStressPointEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnStressPointChanged(IStressPoint * StressPoint)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStressPointEvents> events(sp);
         if ( events )
            events->OnStressPointChanged(StressPoint);
		}
	}
};

template <class T>
class CProxyDStressPointsEvents : public IConnectionPointImpl<T, &IID_IStressPointsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnStressPointsChanged(CollectionIndexType index)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStressPointsEvents> events(sp);
         if ( events )
            events->OnStressPointsChanged(index);
		}
	}
	VOID Fire_OnStressPointsAdded(CollectionIndexType index)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStressPointsEvents> events(sp);
         if ( events )
            events->OnStressPointsAdded(index);
		}
	}
	VOID Fire_OnStressPointsRemoved(CollectionIndexType index)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStressPointsEvents> events(sp);
         if ( events )
            events->OnStressPointsRemoved(index);
		}
	}
};

template <class T>
class CProxyDSegmentEvents : public IConnectionPointImpl<T, &IID_ISegmentEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSegmentChanged(ISegment * segment, ChangeType type)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISegmentEvents> events(sp);
         if ( events )
            events->OnSegmentChanged(segment,type);
		}
	}
};





template <class T>
class CProxyDSegmentCrossSectionEvents : public IConnectionPointImpl<T, &IID_ISegmentCrossSectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSegmentCrossSectionChanged(ISegmentCrossSection * crosssection, ChangeType type)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISegmentCrossSectionEvents> events(sp);
         if ( events )
            events->OnSegmentCrossSectionChanged(crosssection,type);
		}
	}
};





template <class T>
class CProxyDSegmentItemEvents : public IConnectionPointImpl<T, &IID_ISegmentItemEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSegmentItemChanged(ISegmentItem * segmentItem, BSTR Stage, ChangeType change)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISegmentItemEvents> events(sp);
         if ( events )
            events->OnSegmentItemChanged(segmentItem,Stage,change);
		}
	}
};


#endif