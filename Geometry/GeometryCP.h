///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifndef _GEOMETRYCP_H_
#define _GEOMETRYCP_H_









template <class T>
class CProxyDPoint2dCollectionEvents : public IConnectionPointImpl<T, &IID_IPoint2dCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPointChanged(IPoint2d * Point2d)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPoint2dCollectionEvents> events(sp);
         if ( events )
         {
            events->OnPointChanged(Point2d);
			}
		}

	}
	VOID Fire_OnPointAdded(CollectionIndexType idx, IPoint2d * Point2d)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPoint2dCollectionEvents> events(sp);
         if ( events )
         {
            events->OnPointAdded(idx,Point2d);
			}
		}

	}
	VOID Fire_OnPointRemoved(CollectionIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPoint2dCollectionEvents> events(sp);
         if ( events )
         {
            events->OnPointRemoved(idx);
			}
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
         CComQIPtr<IPoint2dCollectionEvents> events(sp);
         if ( events )
         {
            events->OnPointsCleared();
			}
		}
	
	}
};

template <class T>
class CProxyDPoint3dEvents : public IConnectionPointImpl<T, &IID_IPoint3dEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPointChanged(IPoint3d * point)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPoint3dEvents> events(sp);
         if ( events )
            events->OnPointChanged(point);
		}
	}
};

template <class T>
class CProxyDPoint3dCollectionEvents : public IConnectionPointImpl<T, &IID_IPoint3dCollectionEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPointChanged(IPoint3d * Point3d)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPoint3dCollectionEvents> events(sp);
         if ( events )
            events->OnPointChanged(Point3d);
		}
	}
	VOID Fire_OnPointAdded(CollectionIndexType idx, IPoint3d * Point3d)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPoint3dCollectionEvents> events(sp);
         if ( events )
            events->OnPointAdded(idx,Point3d);
		}
	
	}
	VOID Fire_OnPointRemoved(CollectionIndexType idx)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPoint3dCollectionEvents> events(sp);
         if ( events )
            events->OnPointRemoved(idx);
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
         CComQIPtr<IPoint3dCollectionEvents> events(sp);
         if ( events )
            events->OnPointsCleared();
		}
	}
};



template <class T>
class CProxyDPoint2dEvents : public IConnectionPointImpl<T, &IID_IPoint2dEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnPointChanged(IPoint2d * point)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IPoint2dEvents> events(sp);
         if ( events )
            events->OnPointChanged(point);
		}
	}
};

template <class T>
class CProxyDLineSegment2dEvents : public IConnectionPointImpl<T, &IID_ILineSegment2dEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLineSegmentChanged(ILineSegment2d * lineSegment)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILineSegment2dEvents> events(sp);
         if ( events )
            events->OnLineSegmentChanged(lineSegment);
		}
	}
};


template <class T>
class CProxyDLineSegment3dEvents : public IConnectionPointImpl<T, &IID_ILineSegment3dEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLineSegmentChanged(ILineSegment3d * lineSegment)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILineSegment3dEvents> events(sp);
         if ( events )
            events->OnLineSegmentChanged(lineSegment);
		}
	}
};
#endif