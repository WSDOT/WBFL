///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2013  Washington State Department of Transportation
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
	VOID Fire_OnPathChanged(IPathCollection* coll,CogoObjectID id, IPath * Path)
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
            events->OnPathChanged(coll,id,Path);
		}
	}
	VOID Fire_OnPathAdded(IPathCollection* coll,CogoObjectID id, IPath * Path)
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
            events->OnPathAdded(coll,id,Path);
		}
	}
	VOID Fire_OnPathRemoved(IPathCollection* coll,CogoObjectID id)
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
            events->OnPathRemoved(coll,id);
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
};

template <class T>
class CProxyDAlignmentCollectionEvents : public IConnectionPointImpl<T, &IID_IAlignmentCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnAlignmentChanged(IAlignmentCollection* coll,CogoObjectID id, IAlignment* Alignment)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAlignmentCollectionEvents> events(sp);
         if ( events )
            events->OnAlignmentChanged(coll,id,Alignment);
		}
	}
	VOID Fire_OnAlignmentAdded(IAlignmentCollection* coll,CogoObjectID id, IAlignment * Alignment)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAlignmentCollectionEvents> events(sp);
         if ( events )
            events->OnAlignmentAdded(coll,id,Alignment);
		}
	}
	VOID Fire_OnAlignmentRemoved(IAlignmentCollection* coll,CogoObjectID id)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAlignmentCollectionEvents> events(sp);
         if ( events )
            events->OnAlignmentRemoved(coll,id);
		}
	}
	VOID Fire_OnAlignmentsCleared(IAlignmentCollection* coll)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAlignmentCollectionEvents> events(sp);
         if ( events )
            events->OnAlignmentsCleared(coll);
		}
	}
	VOID Fire_OnProfileChanged(IAlignmentCollection* coll,IProfile* Profile)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAlignmentCollectionEvents> events(sp);
         if ( events )
            events->OnProfileChanged(coll,Profile);
		}
	}
	VOID Fire_OnStationEquationsChanged(IAlignmentCollection* coll,IStationEquationCollection* Equations)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAlignmentCollectionEvents> events(sp);
         if ( events )
            events->OnStationEquationsChanged(coll,Equations);
		}
	}
};

template <class T>
class CProxyDAlignmentEvents : public IConnectionPointImpl<T, &IID_IAlignmentEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnAlignmentChanged(IAlignment * alignmnet)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAlignmentEvents> events(sp);
         if ( events )
            events->OnAlignmentChanged(alignmnet);
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
         CComQIPtr<IAlignmentEvents> events(sp);
         if ( events )
            events->OnProfileChanged(Profile);
		}
	}
	VOID Fire_OnStationEquationsChanged(IStationEquationCollection * Equations)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IAlignmentEvents> events(sp);
         if ( events )
            events->OnStationEquationsChanged(Equations);
		}
	}
};

template <class T>
class CProxyDCogoModelEvents : public IConnectionPointImpl<T, &IID_ICogoModelEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPointChanged(ICogoModel * cm, CogoObjectID id, IPoint2d * point)
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
            events->OnPointChanged(cm,id,point);
		}
	}
	VOID Fire_OnPointAdded(ICogoModel * cm, CogoObjectID id, IPoint2d * point)
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
            events->OnPointAdded(cm,id,point);
		}
	}
	VOID Fire_OnPointRemoved(ICogoModel * cm, CogoObjectID id)
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
            events->OnPointRemoved(cm,id);
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
	VOID Fire_OnLineSegmentChanged(ICogoModel * cm, CogoObjectID id, ILineSegment2d * lineSeg)
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
            events->OnLineSegmentChanged(cm,id,lineSeg);
		}
	}
	VOID Fire_OnLineSegmentAdded(ICogoModel * cm, CogoObjectID id, ILineSegment2d * lineSeg)
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
            events->OnLineSegmentAdded(cm,id,lineSeg);
		}
	}
	VOID Fire_OnLineSegmentRemoved(ICogoModel * cm, CogoObjectID id)
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
            events->OnLineSegmentRemoved(cm,id);
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
	VOID Fire_OnProfilePointChanged(ICogoModel * cm, CogoObjectID id, IProfilePoint * pp)
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
            events->OnProfilePointChanged(cm,id,pp);
		}
	}
	VOID Fire_OnProfilePointAdded(ICogoModel * cm, CogoObjectID id, IProfilePoint * pp)
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
            events->OnProfilePointAdded(cm,id,pp);
		}
	}
	VOID Fire_OnProfilePointRemoved(ICogoModel * cm, CogoObjectID id)
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
            events->OnProfilePointRemoved(cm,id);
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
	VOID Fire_OnVertCurveChanged(ICogoModel * cm, CogoObjectID id, IVertCurve * vc)
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
            events->OnVertCurveChanged(cm,id,vc);
		}
	}
	VOID Fire_OnVertCurveAdded(ICogoModel * cm, CogoObjectID id, IVertCurve * vc)
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
            events->OnVertCurveAdded(cm,id,vc);
		}
	}
	VOID Fire_OnVertCurveRemoved(ICogoModel * cm, CogoObjectID id)
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
            events->OnVertCurveRemoved(cm,id);
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
	VOID Fire_OnHorzCurveChanged(ICogoModel * cm, CogoObjectID id, IHorzCurve * vc)
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
            events->OnHorzCurveChanged(cm,id,vc);
		}
	}
	VOID Fire_OnHorzCurveAdded(ICogoModel * cm, CogoObjectID id, IHorzCurve * vc)
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
            events->OnHorzCurveAdded(cm,id,vc);
		}
	}
	VOID Fire_OnHorzCurveRemoved(ICogoModel * cm, CogoObjectID id)
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
            events->OnHorzCurveRemoved(cm,id);
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
	VOID Fire_OnStationEquationsChanged(ICogoModel * cm, IStationEquationCollection * Equations)
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
            events->OnStationEquationsChanged(cm,Equations);
		}
	}
	VOID Fire_OnAlignmentChanged(ICogoModel * cm, CogoObjectID id, IAlignment * alignment)
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
            events->OnAlignmentChanged(cm,id,alignment);
		}
	}
	VOID Fire_OnAlignmentAdded(ICogoModel * cm, CogoObjectID id, IAlignment * alignment)
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
            events->OnAlignmentAdded(cm,id,alignment);
		}
	}
	VOID Fire_OnAlignmentRemoved(ICogoModel * cm, CogoObjectID id)
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
            events->OnAlignmentRemoved(cm,id);
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

	VOID Fire_OnPathChanged(ICogoModel * cm, CogoObjectID id, IPath * path)
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
            events->OnPathChanged(cm,id,path);
		}
	}
	VOID Fire_OnPathAdded(ICogoModel * cm, CogoObjectID id, IPath * path)
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
            events->OnPathAdded(cm,id,path);
		}
	}
	VOID Fire_OnPathRemoved(ICogoModel * cm, CogoObjectID id)
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
            events->OnPathRemoved(cm,id);
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
class CProxyDHorzCurveCollectionEvents : public IConnectionPointImpl<T, &IID_IHorzCurveCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnHorzCurveChanged(CogoObjectID id, IHorzCurve * vc)
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
            events->OnHorzCurveChanged(id,vc);
		}
	}
	VOID Fire_OnHorzCurveAdded(CogoObjectID id, IHorzCurve * vc)
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
            events->OnHorzCurveAdded(id,vc);
		}
	}
	VOID Fire_OnHorzCurveRemoved(CogoObjectID id)
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
            events->OnHorzCurveRemoved(id);
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
	VOID Fire_OnLineSegmentChanged(CogoObjectID id, ILineSegment2d * lineSeg)
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
            events->OnLineSegmentChanged(id,lineSeg);
		}
	}
	VOID Fire_OnLineSegmentAdded(CogoObjectID id, ILineSegment2d * lineSeg)
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
            events->OnLineSegmentAdded(id,lineSeg);
		}
	}
	VOID Fire_OnLineSegmentRemoved(CogoObjectID id)
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
            events->OnLineSegmentRemoved(id);
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
	VOID Fire_OnProfilePointChanged(CogoObjectID id, IProfilePoint * pp)
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
            events->OnProfilePointChanged(id,pp);
		}
	}
	VOID Fire_OnProfilePointAdded(CogoObjectID id, IProfilePoint * pp)
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
            events->OnProfilePointAdded(id,pp);
		}
	}
	VOID Fire_OnProfilePointRemoved(CogoObjectID id)
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
            events->OnProfilePointRemoved(id);
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
	VOID Fire_OnVertCurveChanged(CogoObjectID id, IVertCurve * vc)
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
            events->OnVertCurveChanged(id,vc);
		}
	}
	VOID Fire_OnVertCurveAdded(CogoObjectID id, IVertCurve * vc)
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
            events->OnVertCurveAdded(id,vc);
		}
	}
	VOID Fire_OnVertCurveRemoved(CogoObjectID id)
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
            events->OnVertCurveRemoved(id);
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
	VOID Fire_OnStationChanged(ZoneIndexType zoneIdx,Float64 station)
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
            events->OnStationChanged(zoneIdx,station);
		}
	}
};


template <class T>
class CProxyDPointCollectionEvents : public IConnectionPointImpl<T, &IID_IPointCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPointChanged(CogoObjectID id, IPoint2d * point)
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
            events->OnPointChanged(id,point);
		}
	}
	VOID Fire_OnPointAdded(CogoObjectID id, IPoint2d * point)
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
            events->OnPointAdded(id,point);
		}
	}
	VOID Fire_OnPointRemoved(CogoObjectID id)
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
            events->OnPointRemoved(id);
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



template <class T>
class CProxyDStationEquationCollectionEvents : public IConnectionPointImpl<T, &IID_IStationEquationCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnEquationAdded(CollectionIndexType idx, IStationEquation* pEquation)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStationEquationCollectionEvents> events(sp);
         if ( events )
            events->OnEquationAdded(idx,pEquation);
		}
	}
	VOID Fire_OnEquationRemoved(CollectionIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStationEquationCollectionEvents> events(sp);
         if ( events )
            events->OnEquationRemoved(idx);
		}
	}
	VOID Fire_OnEquationsCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IStationEquationCollectionEvents> events(sp);
         if ( events )
            events->OnEquationsCleared();
		}
	}
};


template <class T>
class CProxyDWideningEvents : public IConnectionPointImpl<T, &IID_IWideningEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnWideningChanged(IWidening* pWidening)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IWideningEvents> events(sp);
         if ( events )
            events->OnWideningChanged(pWidening);
		}
	}
};

template <class T>
class CProxyDWideningCollectionEvents : public IConnectionPointImpl<T, &IID_IWideningCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnWideningChanged(IWidening* pWidening)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IWideningCollectionEvents> events(sp);
         if ( events )
            events->OnWideningChanged(pWidening);
		}
	}
	VOID Fire_OnWideningAdded(IWidening* pWidening)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IWideningCollectionEvents> events(sp);
         if ( events )
            events->OnWideningAdded(pWidening);
		}
	}
	VOID Fire_OnWideningRemoved()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IWideningCollectionEvents> events(sp);
         if ( events )
            events->OnWideningRemoved();
		}
	}
	VOID Fire_OnWideningsCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IWideningCollectionEvents> events(sp);
         if ( events )
            events->OnWideningsCleared();
		}
	}
};


template <class T>
class CProxyDSuperelevationEvents : public IConnectionPointImpl<T, &IID_ISuperelevationEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSuperelevationChanged(ISuperelevation* pSuperelevation)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperelevationEvents> events(sp);
         if ( events )
            events->OnSuperelevationChanged(pSuperelevation);
		}
	}
};


template <class T>
class CProxyDSuperelevationCollectionEvents : public IConnectionPointImpl<T, &IID_ISuperelevationCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSuperelevationChanged(ISuperelevation* pSuperelevation)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperelevationCollectionEvents> events(sp);
         if ( events )
            events->OnSuperelevationChanged(pSuperelevation);
		}
	}
	VOID Fire_OnSuperelevationAdded(ISuperelevation* pSuperelevation)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperelevationCollectionEvents> events(sp);
         if ( events )
            events->OnSuperelevationAdded(pSuperelevation);
		}
	}
	VOID Fire_OnSuperelevationRemoved()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperelevationCollectionEvents> events(sp);
         if ( events )
            events->OnSuperelevationRemoved();
		}
	}
	VOID Fire_OnSuperelevationsCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISuperelevationCollectionEvents> events(sp);
         if ( events )
            events->OnSuperelevationsCleared();
		}
	}
};


template <class T>
class CProxyDTemplateSegmentEvents : public IConnectionPointImpl<T, &IID_ITemplateSegmentEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnTemplateSegmentChanged(ITemplateSegment* pSegment)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ITemplateSegmentEvents> events(sp);
         if ( events )
            events->OnTemplateSegmentChanged(pSegment);
		}
	}
};



template <class T>
class CProxyDSurfaceTemplateEvents : public IConnectionPointImpl<T, &IID_ISurfaceTemplateEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSurfaceTemplateChanged(ISurfaceTemplate* pTemplate)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceTemplateEvents> events(sp);
         if ( events )
            events->OnSurfaceTemplateChanged(pTemplate);
		}
	}

	VOID Fire_OnTemplateSegmentAdded(ISurfaceTemplate* pTemplate,ITemplateSegment* pSegment)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceTemplateEvents> events(sp);
         if ( events )
            events->OnTemplateSegmentAdded(pTemplate,pSegment);
		}
	}
	VOID Fire_OnTemplateSegmentRemoved(ISurfaceTemplate* pTemplate)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceTemplateEvents> events(sp);
         if ( events )
            events->OnTemplateSegmentRemoved(pTemplate);
		}
	}
	VOID Fire_OnTemplateSegmentsCleared(ISurfaceTemplate* pTemplate)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceTemplateEvents> events(sp);
         if ( events )
            events->OnTemplateSegmentsCleared(pTemplate);
		}
	}
};



template <class T>
class CProxyDSurfaceTemplateCollectionEvents : public IConnectionPointImpl<T, &IID_ISurfaceTemplateCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSurfaceTemplateChanged(ISurfaceTemplate* pSurfaceTemplate)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceTemplateCollectionEvents> events(sp);
         if ( events )
            events->OnSurfaceTemplateChanged(pSurfaceTemplate);
		}
	}
	VOID Fire_OnSurfaceTemplateAdded(ISurfaceTemplate* pSurfaceTemplate)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceTemplateCollectionEvents> events(sp);
         if ( events )
            events->OnSurfaceTemplateAdded(pSurfaceTemplate);
		}
	}
	VOID Fire_OnSurfaceTemplateRemoved()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceTemplateCollectionEvents> events(sp);
         if ( events )
            events->OnSurfaceTemplateRemoved();
		}
	}
	VOID Fire_OnSurfaceTemplatesCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceTemplateCollectionEvents> events(sp);
         if ( events )
            events->OnSurfaceTemplatesCleared();
		}
	}
};


template <class T>
class CProxyDSurfaceEvents : public IConnectionPointImpl<T, &IID_ISurfaceEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSurfaceChanged(ISurface* pSurface)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceEvents> events(sp);
         if ( events )
            events->OnSurfaceChanged(pSurface);
		}
	}
};


template <class T>
class CProxyDSurfaceCollectionEvents : public IConnectionPointImpl<T, &IID_ISurfaceCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSurfaceChanged(ISurface* pSurface)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceCollectionEvents> events(sp);
         if ( events )
            events->OnSurfaceChanged(pSurface);
		}
	}
	VOID Fire_OnSurfaceAdded(ISurface* pSurface)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceCollectionEvents> events(sp);
         if ( events )
            events->OnSurfaceAdded(pSurface);
		}
	}
	VOID Fire_OnSurfaceRemoved()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceCollectionEvents> events(sp);
         if ( events )
            events->OnSurfaceRemoved();
		}
	}
	VOID Fire_OnSurfacesCleared()
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ISurfaceCollectionEvents> events(sp);
         if ( events )
            events->OnSurfacesCleared();
		}
	}
};
#endif