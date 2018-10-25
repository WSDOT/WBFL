///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2014  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef _COGOCP_H_
#define _COGOCP_H_

#pragma once

template <class T>
class CProxyDDisplayUnitFormatterEvents : public IConnectionPointImpl<T, &IID_IDisplayUnitFormatterEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnFormatChanged()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IDisplayUnitFormatterEvents> events(sp);
         if ( events )
            events->OnFormatChanged();
		}
	
	}
};

template <class T>
class CProxyDPathCollectionEvents : public IConnectionPointImpl<T, &IID_IPathCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPathChanged(IPathCollection* coll,CogoElementKey key, IPath * Path)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPathCollectionEvents> events(sp);
         if ( events )
            events->OnPathChanged(coll,key,Path);
		}
	}
	VOID Fire_OnProfileChanged(IPathCollection* coll,IProfile * Profile)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPathCollectionEvents> events(sp);
         if ( events )
            events->OnProfileChanged(coll,Profile);
		}
	}
	VOID Fire_OnPathAdded(IPathCollection* coll,CogoElementKey key, IPath * Path)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPathCollectionEvents> events(sp);
         if ( events )
            events->OnPathAdded(coll,key,Path);
		}
	}
	VOID Fire_OnPathRemoved(IPathCollection* coll,CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPathCollectionEvents> events(sp);
         if ( events )
            events->OnPathRemoved(coll,key);
		}
	}
	VOID Fire_OnPathsCleared(IPathCollection* coll)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPathCollectionEvents> events(sp);
         if ( events )
            events->OnPathsCleared(coll);
		}
	}
};

template <class T>
class CProxyDPathElementEvents : public IConnectionPointImpl<T, &IID_IPathElementEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPathElementChanged(IPathElement * element)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPathElementEvents> events(sp);
         if ( events )
            events->OnPathElementChanged(element);
		}
	}
};

template <class T>
class CProxyDPathEvents : public IConnectionPointImpl<T, &IID_IPathEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPathChanged(IPath * path)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPathEvents> events(sp);
         if ( events )
            events->OnPathChanged(path);
		}
	}
	VOID Fire_OnProfileChanged(IProfile * Profile)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPathEvents> events(sp);
         if ( events )
            events->OnProfileChanged(Profile);
		}
	}
};

template <class T>
class CProxyDCogoModelEvents : public IConnectionPointImpl<T, &IID_ICogoModelEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPointChanged(ICogoModel * cm, CogoElementKey key, IPoint2d * point)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnPointChanged(cm,key,point);
		}
	}
	VOID Fire_OnPointAdded(ICogoModel * cm, CogoElementKey key, IPoint2d * point)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnPointAdded(cm,key,point);
		}
	}
	VOID Fire_OnPointRemoved(ICogoModel * cm, CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnPointRemoved(cm,key);
		}
	}
	VOID Fire_OnPointsCleared(ICogoModel * cm)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnPointsCleared(cm);
		}
	}
	VOID Fire_OnLineSegmentChanged(ICogoModel * cm, CogoElementKey key, ILineSegment2d * lineSeg)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnLineSegmentChanged(cm,key,lineSeg);
		}
	}
	VOID Fire_OnLineSegmentAdded(ICogoModel * cm, CogoElementKey key, ILineSegment2d * lineSeg)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnLineSegmentAdded(cm,key,lineSeg);
		}
	}
	VOID Fire_OnLineSegmentRemoved(ICogoModel * cm, CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnLineSegmentRemoved(cm,key);
		}
	}
	VOID Fire_OnLineSegmentsCleared(ICogoModel * cm)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnLineSegmentsCleared(cm);
		}
	}
	VOID Fire_OnProfilePointChanged(ICogoModel * cm, CogoElementKey key, IProfilePoint * pp)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnProfilePointChanged(cm,key,pp);
		}
	}
	VOID Fire_OnProfilePointAdded(ICogoModel * cm, CogoElementKey key, IProfilePoint * pp)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnProfilePointAdded(cm,key,pp);
		}
	}
	VOID Fire_OnProfilePointRemoved(ICogoModel * cm, CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnProfilePointRemoved(cm,key);
		}
	}
	VOID Fire_OnProfilePointsCleared(ICogoModel * cm)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnProfilePointsCleared(cm);
		}
	}
	VOID Fire_OnVertCurveChanged(ICogoModel * cm, CogoElementKey key, IVertCurve * vc)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnVertCurveChanged(cm,key,vc);
		}
	}
	VOID Fire_OnVertCurveAdded(ICogoModel * cm, CogoElementKey key, IVertCurve * vc)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnVertCurveAdded(cm,key,vc);
		}
	}
	VOID Fire_OnVertCurveRemoved(ICogoModel * cm, CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnVertCurveRemoved(cm,key);
		}
	}
	VOID Fire_OnVertCurvesCleared(ICogoModel * cm)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnVertCurvesCleared(cm);
		}
	}
	VOID Fire_OnHorzCurveChanged(ICogoModel * cm, CogoElementKey key, IHorzCurve * vc)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnHorzCurveChanged(cm,key,vc);
		}
	}
	VOID Fire_OnHorzCurveAdded(ICogoModel * cm, CogoElementKey key, IHorzCurve * vc)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnHorzCurveAdded(cm,key,vc);
		}
	}
	VOID Fire_OnHorzCurveRemoved(ICogoModel * cm, CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnHorzCurveRemoved(cm,key);
		}
	}
	VOID Fire_OnHorzCurvesCleared(ICogoModel * cm)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnHorzCurvesCleared(cm);
		}
	}
	VOID Fire_OnProfileChanged(ICogoModel * cm, IProfile * Profile)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnProfileChanged(cm,Profile);
		}
	}
	VOID Fire_OnAlignmentChanged(ICogoModel * cm, CogoElementKey key, IAlignment * alignment)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnAlignmentChanged(cm,key,alignment);
		}
	}
	VOID Fire_OnAlignmentAdded(ICogoModel * cm, CogoElementKey key, IAlignment * alignment)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnAlignmentAdded(cm,key,alignment);
		}
	}
	VOID Fire_OnAlignmentRemoved(ICogoModel * cm, CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnAlignmentRemoved(cm,key);
		}
	}
	VOID Fire_OnAlignmentsCleared(ICogoModel * cm)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnAlignmentsCleared(cm);
		}
	}

	VOID Fire_OnPathChanged(ICogoModel * cm, CogoElementKey key, IPath * path)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnPathChanged(cm,key,path);
		}
	}
	VOID Fire_OnPathAdded(ICogoModel * cm, CogoElementKey key, IPath * path)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnPathAdded(cm,key,path);
		}
	}
	VOID Fire_OnPathRemoved(ICogoModel * cm, CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnPathRemoved(cm,key);
		}
	}
	VOID Fire_OnPathsCleared(ICogoModel * cm)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICogoModelEvents> events(sp);
         if ( events )
            events->OnPathsCleared(cm);
		}
	}
};

template <class T>
class CProxyDCrossSectionCollectionEvents : public IConnectionPointImpl<T, &IID_ICrossSectionCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnCrossSectionChanged(ICrossSection * csect)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICrossSectionCollectionEvents> events(sp);
         if ( events )
            events->OnCrossSectionChanged(csect);
		}
	}
	VOID Fire_OnCrossSectionAdded(ICrossSection * csect)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICrossSectionCollectionEvents> events(sp);
         if ( events )
            events->OnCrossSectionAdded(csect);
		}
	}
	VOID Fire_OnCrossSectionRemoved()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICrossSectionCollectionEvents> events(sp);
         if ( events )
            events->OnCrossSectionRemoved();
		}
	}
	VOID Fire_OnCrossSectionsCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICrossSectionCollectionEvents> events(sp);
         if ( events )
            events->OnCrossSectionsCleared();
		}
	}
};

template <class T>
class CProxyDCrossSectionEvents : public IConnectionPointImpl<T, &IID_ICrossSectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnCrossSectionChanged(ICrossSection * csect)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICrossSectionEvents> events(sp);
         if ( events )
            events->OnCrossSectionChanged(csect);
		}
	}
	VOID Fire_OnCrossSectionMoved(ICrossSection * csect)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICrossSectionEvents> events(sp);
         if ( events )
            events->OnCrossSectionMoved(csect);
		}
	}
};

template <class T>
class CProxyDHorzCurveCollectionEvents : public IConnectionPointImpl<T, &IID_IHorzCurveCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnHorzCurveChanged(CogoElementKey key, IHorzCurve * vc)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IHorzCurveCollectionEvents> events(sp);
         if ( events ) 
            events->OnHorzCurveChanged(key,vc);
		}
	}
	VOID Fire_OnHorzCurveAdded(CogoElementKey key, IHorzCurve * vc)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IHorzCurveCollectionEvents> events(sp);
         if ( events ) 
            events->OnHorzCurveAdded(key,vc);
		}
	}
	VOID Fire_OnHorzCurveRemoved(CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IHorzCurveCollectionEvents> events(sp);
         if ( events ) 
            events->OnHorzCurveRemoved(key);
		}
	}
	VOID Fire_OnHorzCurvesCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IHorzCurveCollectionEvents> events(sp);
         if ( events ) 
            events->OnHorzCurvesCleared();
		}
	}
};

template <class T>
class CProxyDHorzCurveEvents : public IConnectionPointImpl<T, &IID_IHorzCurveEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnHorzCurveChanged(IHorzCurve * hc)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IHorzCurveEvents> events(sp);
         if ( events )
            events->OnHorzCurveChanged(hc);
		}
	}
};


template <class T>
class CProxyDCubicSplineEvents : public IConnectionPointImpl<T, &IID_ICubicSplineEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSplineChanged(ICubicSpline* spline)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ICubicSplineEvents> events(sp);
         if ( events )
            events->OnSplineChanged(spline);
		}
	}
};

template <class T>
class CProxyDLineSegmentCollectionEvents : public IConnectionPointImpl<T, &IID_ILineSegmentCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLineSegmentChanged(CogoElementKey key, ILineSegment2d * lineSeg)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILineSegmentCollectionEvents> events(sp);
         if ( events )
            events->OnLineSegmentChanged(key,lineSeg);
		}
	}
	VOID Fire_OnLineSegmentAdded(CogoElementKey key, ILineSegment2d * lineSeg)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILineSegmentCollectionEvents> events(sp);
         if ( events )
            events->OnLineSegmentAdded(key,lineSeg);
		}
	}
	VOID Fire_OnLineSegmentRemoved(CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILineSegmentCollectionEvents> events(sp);
         if ( events )
            events->OnLineSegmentRemoved(key);
		}
	}
	VOID Fire_OnLineSegmentsCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILineSegmentCollectionEvents> events(sp);
         if ( events )
            events->OnLineSegmentsCleared();
		}
	}
};

template <class T>
class CProxyDProfileElementEvents : public IConnectionPointImpl<T, &IID_IProfileElementEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnProfileElementChanged(IProfileElement * pe)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IProfileElementEvents> events(sp);
         if ( events )
             events->OnProfileElementChanged(pe);
		}
	}
};

template <class T>
class CProxyDProfileEvents : public IConnectionPointImpl<T, &IID_IProfileEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnProfileChanged(IProfile * Profile)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IProfileEvents> events(sp);
         if ( events )
            events->OnProfileChanged(Profile);
		}
	}
};

template <class T>
class CProxyDProfilePointCollectionEvents : public IConnectionPointImpl<T, &IID_IProfilePointCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnProfilePointChanged(CogoElementKey key, IProfilePoint * pp)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IProfilePointCollectionEvents> events(sp);
         if ( events )
            events->OnProfilePointChanged(key,pp);
		}
	}
	VOID Fire_OnProfilePointAdded(CogoElementKey key, IProfilePoint * pp)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IProfilePointCollectionEvents> events(sp);
         if ( events )
            events->OnProfilePointAdded(key,pp);
		}
	}
	VOID Fire_OnProfilePointRemoved(CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IProfilePointCollectionEvents> events(sp);
         if ( events )
            events->OnProfilePointRemoved(key);
		}
	}
	VOID Fire_OnProfilePointsCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IProfilePointCollectionEvents> events(sp);
         if ( events )
            events->OnProfilePointsCleared();
		}
	}
};

template <class T>
class CProxyDProfilePointEvents : public IConnectionPointImpl<T, &IID_IProfilePointEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnProfilePointChanged(IProfilePoint * pp)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IProfilePointEvents> events(sp);
         if (events)
            events->OnProfilePointChanged(pp);
		}
	}
};

template <class T>
class CProxyDVertCurveCollectionEvents : public IConnectionPointImpl<T, &IID_IVertCurveCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnVertCurveChanged(CogoElementKey key, IVertCurve * vc)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVertCurveCollectionEvents> events(sp);
         if ( events )
            events->OnVertCurveChanged(key,vc);
		}
	}
	VOID Fire_OnVertCurveAdded(CogoElementKey key, IVertCurve * vc)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVertCurveCollectionEvents> events(sp);
         if ( events )
            events->OnVertCurveAdded(key,vc);
		}
	}
	VOID Fire_OnVertCurveRemoved(CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVertCurveCollectionEvents> events(sp);
         if ( events )
            events->OnVertCurveRemoved(key);
		}
	}
	VOID Fire_OnVertCurvesCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVertCurveCollectionEvents> events(sp);
         if ( events )
            events->OnVertCurvesCleared();
		}
	}
};

template <class T>
class CProxyDVertCurveEvents : public IConnectionPointImpl<T, &IID_IVertCurveEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnVertCurveChanged(IVertCurve * vc)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVertCurveEvents> events(sp);
         if ( events )
            events->OnVertCurveChanged(vc);
		}
	}
};

template <class T>
class CProxyDStationEvents : public IConnectionPointImpl<T, &IID_IStationEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnStationChanged(Float64 newVal)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStationEvents> events(sp);
         if ( events )
            events->OnStationChanged(newVal);
		}
	}
};


template <class T>
class CProxyDPointCollectionEvents : public IConnectionPointImpl<T, &IID_IPointCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPointChanged(CogoElementKey key, IPoint2d * point)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPointCollectionEvents> events(sp);
         if ( events )
            events->OnPointChanged(key,point);
		}
	}
	VOID Fire_OnPointAdded(CogoElementKey key, IPoint2d * point)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPointCollectionEvents> events(sp);
         if ( events )
            events->OnPointAdded(key,point);
		}
	}
	VOID Fire_OnPointRemoved(CogoElementKey key)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPointCollectionEvents> events(sp);
         if ( events )
            events->OnPointRemoved(key);
		}
	}
	VOID Fire_OnPointsCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPointCollectionEvents> events(sp);
         if ( events )
            events->OnPointsCleared();
		}
	}
};

#endif