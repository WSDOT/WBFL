///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2021  Washington State Department of Transportation
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

// CogoModel.cpp : Implementation of CCogoModel
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CogoModel.h"
#include "CogoEngine.h"
#include "PointCollection.h"
#include "PathCollection.h"
#include "AlignmentCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCogoModel
HRESULT CCogoModel::FinalConstruct()
{
   HRESULT hr;

   // Geometry Utility Object
   CComObject<CCogoEngine>* pEngine;
   CComObject<CCogoEngine>::CreateInstance(&pEngine);
   m_Engine = pEngine;
 
   // Points collection
   CComObject<CPointCollection>* pPoints;
   CComObject<CPointCollection>::CreateInstance(&pPoints);
   m_Points = pPoints;

   hr = CrAdvise(m_Points,this,IID_IPointCollectionEvents,&m_dwPointsCookie);
   ATLASSERT(SUCCEEDED(hr));

   // Line segment collection
   hr = m_Lines.CoCreateInstance(CLSID_LineSegmentCollection);
   if ( FAILED(hr) )
      return hr;

   hr = CrAdvise(m_Lines,this,IID_ILineSegmentCollectionEvents,&m_dwLinesCookie);
   ATLASSERT(SUCCEEDED(hr));

   // ProfilePoints collection
   hr = m_ProfilePoints.CoCreateInstance(CLSID_ProfilePointCollection);
   if ( FAILED(hr) )
      return hr;

   hr = CrAdvise(m_ProfilePoints,this,IID_IProfilePointCollectionEvents,&m_dwProfilePointsCookie);
   ATLASSERT(SUCCEEDED(hr));

   // VertCurves collection
   hr = m_VertCurves.CoCreateInstance(CLSID_VertCurveCollection);
   if ( FAILED(hr) )
      return hr;

   hr = CrAdvise(m_VertCurves,this,IID_IVertCurveCollectionEvents,&m_dwVertCurvesCookie);
   ATLASSERT(SUCCEEDED(hr));

   // HorzCurves collection
   hr = m_HorzCurves.CoCreateInstance(CLSID_HorzCurveCollection);
   if ( FAILED(hr) )
      return hr;

   hr = CrAdvise(m_HorzCurves,this,IID_IHorzCurveCollectionEvents,&m_dwHorzCurvesCookie);
   ATLASSERT(SUCCEEDED(hr));

   // Alignments collection
   CComObject<CAlignmentCollection>* pAlignments;
   hr = CComObject<CAlignmentCollection>::CreateInstance(&pAlignments);
   if ( FAILED(hr) )
      return hr;

   pAlignments->SetCollectionName(CComBSTR("Alignments"));
   pAlignments->SetItemName(CComBSTR("Alignment"));
   m_Alignments = pAlignments;

   hr = CrAdvise(m_Alignments,this,IID_IAlignmentCollectionEvents,&m_dwAlignmentCookie);
   ATLASSERT(SUCCEEDED(hr));


   // Paths collection
   CComObject<CPathCollection>* pPaths;
   hr = CComObject<CPathCollection>::CreateInstance(&pPaths);
   if ( FAILED(hr) )
      return hr;

   m_Paths = pPaths;

   hr = CrAdvise(m_Paths,this,IID_IPathCollectionEvents,&m_dwPathCookie);
   ATLASSERT(SUCCEEDED(hr));

   return S_OK;
}

void CCogoModel::FinalRelease()
{
   CrUnadvise(m_Points,        this, IID_IPoint2dCollectionEvents,      m_dwPointsCookie);
   CrUnadvise(m_Lines,         this, IID_ILineSegmentCollectionEvents,  m_dwLinesCookie);
   CrUnadvise(m_ProfilePoints, this, IID_IProfilePointCollectionEvents, m_dwProfilePointsCookie);
   CrUnadvise(m_VertCurves,    this, IID_IVertCurveCollectionEvents,    m_dwVertCurvesCookie);
   CrUnadvise(m_HorzCurves,    this, IID_IHorzCurveCollectionEvents,    m_dwHorzCurvesCookie);
   CrUnadvise(m_Alignments,    this, IID_IAlignmentCollectionEvents,    m_dwAlignmentCookie);
   CrUnadvise(m_Paths,         this, IID_IPathCollectionEvents,         m_dwPathCookie);
}

HRESULT CCogoModel::PutRef_Alignments(IAlignmentCollection* alignments)
{
   return CrAssignPointer(m_Alignments,alignments,this,IID_IAlignmentCollectionEvents,&m_dwAlignmentCookie);
}

HRESULT CCogoModel::PutRef_Paths(IPathCollection* paths)
{
   return CrAssignPointer(m_Paths,paths,this,IID_IPathCollectionEvents,&m_dwPathCookie);
}

HRESULT CCogoModel::PutRef_HorzCurves(IHorzCurveCollection* horzCurves)
{
   return CrAssignPointer(m_HorzCurves,horzCurves,this,IID_IHorzCurveCollectionEvents,&m_dwHorzCurvesCookie);
}

HRESULT CCogoModel::PutRef_Lines(ILineSegmentCollection* lines)
{
   return CrAssignPointer(m_Lines,lines,this,IID_ILineSegmentCollectionEvents,&m_dwLinesCookie);
}

HRESULT CCogoModel::PutRef_Points(IPointCollection* points)
{
   return CrAssignPointer(m_Points,points,this,IID_IPointCollectionEvents,&m_dwPointsCookie);
}

HRESULT CCogoModel::PutRef_ProfilePoints(IProfilePointCollection* profilePoints)
{
   return CrAssignPointer(m_ProfilePoints,profilePoints,this,IID_IProfilePointCollectionEvents,&m_dwProfilePointsCookie);
}

HRESULT CCogoModel::PutRef_VertCurves(IVertCurveCollection* vertCurves)
{
   return CrAssignPointer(m_VertCurves,vertCurves,this,IID_IVertCurveCollectionEvents,&m_dwVertCurvesCookie);
}

STDMETHODIMP CCogoModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICogoModel,
      &IID_IIntersect,
      &IID_ILocate,
      &IID_IMeasure,
      &IID_IProject,
      &IID_IDivide,
      &IID_ITangent,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCogoModel::get_Points(IPointCollection **pVal)
{
   CHECK_RETOBJ(pVal);
   *pVal = m_Points;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CCogoModel::get_LineSegments(ILineSegmentCollection* *pVal)
{
   CHECK_RETOBJ(pVal);
   *pVal = m_Lines;
   (*pVal)->AddRef();
   
   return S_OK;
}

STDMETHODIMP CCogoModel::get_ProfilePoints(IProfilePointCollection* *pVal)
{
   CHECK_RETOBJ(pVal);
   *pVal = m_ProfilePoints;
   (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CCogoModel::get_VertCurves(IVertCurveCollection* *pVal)
{
   CHECK_RETOBJ(pVal);
   *pVal = m_VertCurves;
   (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CCogoModel::get_HorzCurves(IHorzCurveCollection* *pVal)
{
   CHECK_RETOBJ(pVal);
   *pVal = m_HorzCurves;
   (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CCogoModel::get_Alignments(IAlignmentCollection* *pVal)
{
   CHECK_RETOBJ(pVal);
   *pVal = m_Alignments;
   (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CCogoModel::get_Paths(IPathCollection* *pVal)
{
   CHECK_RETOBJ(pVal);
   *pVal = m_Paths;
   (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CCogoModel::Clear()
{
   m_Lines->Clear();
   m_Points->Clear();
   m_ProfilePoints->Clear();
   m_VertCurves->Clear();
   m_HorzCurves->Clear();
   m_Alignments->Clear();

   return S_OK;
}

STDMETHODIMP CCogoModel::get_Intersect(IIntersect **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IIntersect,(void**)pVal);
}

STDMETHODIMP CCogoModel::get_Locate(ILocate **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_ILocate,(void**)pVal);
}

STDMETHODIMP CCogoModel::get_Measure(IMeasure **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IMeasure,(void**)pVal);
}

STDMETHODIMP CCogoModel::get_Project(IProject **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IProject,(void**)pVal);
}

STDMETHODIMP CCogoModel::get_Divide(IDivide **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IDivide,(void**)pVal);
}

STDMETHODIMP CCogoModel::get_Tangent(ITangent **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_ITangent,(void**)pVal);
}

STDMETHODIMP CCogoModel::putref_PointFactory(IPoint2dFactory* factory)
{
   m_Points->putref_Factory(factory);
   return m_Engine->putref_PointFactory(factory);
}

STDMETHODIMP CCogoModel::get_PointFactory(IPoint2dFactory** factory)
{
   return m_Engine->get_PointFactory(factory);
}

STDMETHODIMP CCogoModel::putref_LineSegmentFactory(ILineSegment2dFactory* factory)
{
   m_Lines->putref_Factory(factory);
   return m_Engine->putref_LineSegmentFactory(factory);
}

STDMETHODIMP CCogoModel::get_LineSegmentFactory(ILineSegment2dFactory** factory)
{
   return m_Engine->get_LineSegmentFactory(factory);
}

STDMETHODIMP CCogoModel::putref_ProfilePointFactory(IProfilePointFactory* factory)
{
   return m_ProfilePoints->putref_Factory(factory);
}

STDMETHODIMP CCogoModel::get_ProfilePointFactory(IProfilePointFactory** factory)
{
   return m_ProfilePoints->get_Factory(factory);
}

STDMETHODIMP CCogoModel::putref_VertCurveFactory(IVertCurveFactory* factory)
{
   return m_VertCurves->putref_Factory(factory);
}

STDMETHODIMP CCogoModel::get_VertCurveFactory(IVertCurveFactory** factory)
{
   return m_VertCurves->get_Factory(factory);
}

STDMETHODIMP CCogoModel::putref_HorzCurveFactory(IHorzCurveFactory* factory)
{
   return m_HorzCurves->putref_Factory(factory);
}

STDMETHODIMP CCogoModel::get_HorzCurveFactory(IHorzCurveFactory** factory)
{
   return m_HorzCurves->get_Factory(factory);
}

STDMETHODIMP CCogoModel::putref_AlignmentFactory(IAlignmentFactory* factory)
{
   return m_Alignments->putref_Factory(factory);
}

STDMETHODIMP CCogoModel::get_AlignmentFactory(IAlignmentFactory** factory)
{
   return m_Alignments->get_Factory(factory);
}

STDMETHODIMP CCogoModel::putref_PathFactory(IPathFactory* factory)
{
   return m_Paths->putref_Factory(factory);
}

STDMETHODIMP CCogoModel::get_PathFactory(IPathFactory** factory)
{
   return m_Paths->get_Factory(factory);
}

STDMETHODIMP CCogoModel::get_Engine(ICogoEngine** engine)
{
   CHECK_RETOBJ(engine);
   return m_Engine.CopyTo(engine);
}

STDMETHODIMP CCogoModel::Clone(ICogoModel* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CCogoModel>* pClone;
   CComObject<CCogoModel>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CComPtr<IAlignmentCollection> cloneAlignments;
   m_Alignments->Clone(&cloneAlignments);
   pClone->PutRef_Alignments(cloneAlignments);

   CComPtr<IPathCollection> clonePaths;
   m_Paths->Clone(&clonePaths);
   pClone->PutRef_Paths(clonePaths);

   CComPtr<IHorzCurveCollection> cloneHorzCurves;
   m_HorzCurves->Clone(&cloneHorzCurves);
   pClone->PutRef_HorzCurves(cloneHorzCurves);

   CComPtr<ILineSegmentCollection> cloneLines;
   m_Lines->Clone(&cloneLines);
   pClone->PutRef_Lines(cloneLines);

   CComPtr<IPointCollection> clonePoints;
   m_Points->Clone(&clonePoints);
   pClone->PutRef_Points(clonePoints);

   CComPtr<IProfilePointCollection> cloneProfilePoints;
   m_ProfilePoints->Clone(&cloneProfilePoints);
   pClone->PutRef_ProfilePoints(cloneProfilePoints);

   CComPtr<IVertCurveCollection> cloneVertCurves;
   m_VertCurves->Clone(&cloneVertCurves);
   pClone->PutRef_VertCurves(cloneVertCurves);

   return S_OK;
}

STDMETHODIMP CCogoModel::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

///////////////////////////////////////////////////////
// IMeasure
STDMETHODIMP CCogoModel::Angle(CogoObjectID fromID, CogoObjectID vertexID, CogoObjectID toID, IAngle** angle)
{
   CHECK_RETOBJ(angle);

   CComPtr<IPoint2d> from;
   CComPtr<IPoint2d> vertex;
   CComPtr<IPoint2d> to;
   HRESULT hr;

   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->get_Item(vertexID,&vertex);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->get_Item(toID,&to);
   if ( FAILED(hr) )
      return hr;

   CComQIPtr<IMeasure2> measure(m_Engine);
   return measure->Angle(from,vertex,to,angle);
}

STDMETHODIMP CCogoModel::Area(VARIANT IDs,Float64* area)
{
   CHECK_RETVAL(area);

   if ( IDs.vt != (VT_BYREF | VT_VARIANT) &&  // VB Script
        IDs.vt != (VT_ARRAY | VT_I2)      &&  // VB/C++
        IDs.vt != (VT_ARRAY | VT_I4) )        // VB/C++
   {
      return Error(IDS_E_AREA,IID_IMeasure,COGO_E_AREA);
   }

   // Extract the SAFEARRAY
   SAFEARRAY* pIDs;
   if ( IDs.vt & VT_BYREF )
   {
      if ( !(IDs.pvarVal->vt & (VT_BYREF | VT_ARRAY)) )
         return Error(IDS_E_AREA,IID_IMeasure,COGO_E_AREA);

      pIDs = *(IDs.pvarVal->pparray); // VBScript
   }
   else
   {
      pIDs = IDs.parray; // VB or C++
   }

   // Check out the safe array. Make sure it is the right size
   // and contains the right stuff
   HRESULT hr;
   VARTYPE vt;
   hr = SafeArrayGetVartype(pIDs,&vt);
   if ( FAILED(hr) )
      return hr;

   if ( IDs.vt & VT_BYREF && vt != VT_VARIANT )
      return Error(IDS_E_AREA,IID_IMeasure,COGO_E_AREA);

   if ( IDs.vt & VT_ARRAY && vt != VT_I4 && vt != VT_I2 )
      return Error(IDS_E_AREA,IID_IMeasure,COGO_E_AREA);

   // Make sure this is a 1 dimensional array
   if ( SafeArrayGetDim(pIDs) != 1 )
      return Error(IDS_E_AREA,IID_IMeasure,COGO_E_AREA);

   // Need a container to hold the points
   CComPtr<IPoint2dCollection> points;
   hr = points.CoCreateInstance(CLSID_Point2dCollection);
   if ( FAILED(hr) )
      return hr;

   // Get the array bounds, loop over the array,
   // find the specified points, and build up the polyshape
   long lb,ub;
   SafeArrayGetLBound(pIDs,1,&lb);
   SafeArrayGetUBound(pIDs,1,&ub);
   if ( (ub - lb + 1) < 3 )
   {
      // Must consist of at least 3 points
      return Error(IDS_E_THREEPNTSREQD,IID_IMeasure,COGO_E_THREEPNTSREQD);
   }

   for ( long i = lb; i <= ub; i++ )
   {
      LONG ID;
      VARIANT varID;
      if ( pIDs->fFeatures & FADF_VARIANT )
      {
         // VBScript
         hr = SafeArrayGetElement(pIDs,&i,&varID);
         ATLASSERT(SUCCEEDED(hr));
         ID = varID.iVal;
      }
      else
      {
         // VB
         hr = SafeArrayGetElement(pIDs,&i,&ID);
         ATLASSERT(SUCCEEDED(hr));
      }

      CComPtr<IPoint2d> point;
      hr = m_Points->get_Item(ID,&point);
      if ( FAILED(hr) )
         return hr;

      hr = points->Add(point);
      ATLASSERT(SUCCEEDED(hr));
   }

   CComQIPtr<IMeasure2> measure(m_Engine);
   hr = measure->Area(points,area);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoModel::Distance(CogoObjectID fromID, CogoObjectID toID, Float64* dist)
{
   CHECK_RETVAL(dist);

   CComPtr<IPoint2d> from;
   CComPtr<IPoint2d> to;
   HRESULT hr;

   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->get_Item(toID,&to);
   if ( FAILED(hr) )
      return hr;

   CComQIPtr<IMeasure2> measure(m_Engine);
   return measure->Distance(from,to,dist);
}

STDMETHODIMP CCogoModel::Direction(CogoObjectID fromID, CogoObjectID toID, IDirection** dir)
{
   CHECK_RETOBJ(dir);

   CComPtr<IPoint2d> from;
   CComPtr<IPoint2d> to;
   HRESULT hr;

   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->get_Item(toID,&to);
   if ( FAILED(hr) )
      return hr;

   CComQIPtr<IMeasure2> measure(m_Engine);
   return measure->Direction(from,to,dir);
}

STDMETHODIMP CCogoModel::Inverse(CogoObjectID fromID,CogoObjectID toID, Float64* dist, IDirection** dir)
{
   CComPtr<IPoint2d> from;
   CComPtr<IPoint2d> to;
   HRESULT hr;

   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->get_Item(toID,&to);
   if ( FAILED(hr) )
      return hr;

   CComQIPtr<IMeasure2> measure(m_Engine);
   return measure->Inverse(from,to,dist,dir);
}


///////////////////////////////////////////////////////
// ILocate
STDMETHODIMP CCogoModel::ByDistAngle(CogoObjectID newID,CogoObjectID fromID,CogoObjectID toID,Float64 dist,VARIANT varAngle,Float64 offset)
{
   CComPtr<IPoint2d> from;
   CComPtr<IPoint2d> to;
   HRESULT hr;

   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->get_Item(toID,&to);
   if ( FAILED(hr) )
      return hr;

   CComQIPtr<ILocate2> locate(m_Engine);
   CComPtr<IPoint2d> newPnt;
   hr = locate->ByDistAngle(from,to,dist,varAngle,offset,&newPnt);
   if ( FAILED(hr) )
      return hr;

   // Add the point. If a point with this ID already exists,
   // this method will fail. Return the error if this happens
   hr = m_Points->AddEx(newID,newPnt);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoModel::ByDistDefAngle(CogoObjectID newID,CogoObjectID fromID,CogoObjectID toID,Float64 dist,VARIANT varDefAngle,Float64 offset)
{
   CComPtr<IPoint2d> from;
   CComPtr<IPoint2d> to;
   HRESULT hr;

   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->get_Item(toID,&to);
   if ( FAILED(hr) )
      return hr;

   CComQIPtr<ILocate2> locate(m_Engine);
   CComPtr<IPoint2d> newPnt;
   hr = locate->ByDistDefAngle(from,to,dist,varDefAngle,offset,&newPnt);
   if ( FAILED(hr) )
      return hr;

   // Add the point. If a point with this ID already exists,
   // this method will fail. Return the error if this happens
   hr = m_Points->AddEx(newID,newPnt);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoModel::ByDistDir(CogoObjectID newID,CogoObjectID fromID,Float64 dist,VARIANT varDir,Float64 offset)
{
   CComPtr<IPoint2d> from;
   HRESULT hr;

   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   CComQIPtr<ILocate2> locate(m_Engine);
   CComPtr<IPoint2d> point;
   hr = locate->ByDistDir(from,dist,varDir,offset,&point);
   if ( FAILED(hr) )
      return hr;

   // Add the point. If a point with this ID already exists,
   // this method will fail. Return the error if this happens
   hr = m_Points->AddEx(newID,point);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoModel::PointOnLine(CogoObjectID newID, CogoObjectID fromID, CogoObjectID toID, Float64 dist, Float64 offset)
{
   CComPtr<IPoint2d> from;
   CComPtr<IPoint2d> to;
   HRESULT hr;

   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->get_Item(toID,&to);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> point;
   CComQIPtr<ILocate2> locate(m_Engine);
   hr = locate->PointOnLine(from,to,dist,offset,&point);
   if ( FAILED(hr) )
      return hr;

   // Add the point. If a point with this ID already exists,
   // this method will fail. Return the error if this happens
   hr = m_Points->AddEx(newID,point);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoModel::ParallelLineByPoints(CogoObjectID newFromID, CogoObjectID newToID, CogoObjectID fromID, CogoObjectID toID, Float64 offset)
{
   HRESULT hr;

   CComPtr<IPoint2d> pnt;
   hr = m_Points->get_Item(newFromID,&pnt);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ILocate,COGO_E_POINTALREADYDEFINED);

   pnt.Release();
   hr = m_Points->get_Item(newToID,&pnt);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ILocate,COGO_E_POINTALREADYDEFINED);

   CComPtr<IPoint2d> start;
   hr = m_Points->get_Item(fromID,&start);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> end;
   hr = m_Points->get_Item(toID,&end);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> lsStartEx, lsEndEx;
   CComQIPtr<ILocate2> locate(m_Engine);
   hr = locate->ParallelLineByPoints(start,end,offset,&lsStartEx,&lsEndEx);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->AddEx(newFromID,lsStartEx);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->AddEx(newToID,lsEndEx);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoModel::ParallelLineSegment(CogoObjectID newLineID, CogoObjectID newFromID, CogoObjectID newToID, CogoObjectID lineID, Float64 offset)
{
   HRESULT hr;
   CComPtr<ILineSegment2d> line;
   hr = m_Lines->get_Item(lineID,&line);
   if ( FAILED(hr) )
      return hr;

   // check if we can store the new line segment and end points
   CComPtr<ILineSegment2d> newLine;
   hr = m_Lines->get_Item(newLineID,&newLine);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_LINESEGMENTALREADYDEFINED,IID_ILocate,COGO_E_LINESEGMENTALREADYDEFINED);

   CComPtr<IPoint2d> from;
   hr = m_Points->get_Item(newFromID,&from);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ILocate,COGO_E_POINTALREADYDEFINED);

   CComPtr<IPoint2d> to;
   hr = m_Points->get_Item(newToID,&to);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ILocate,COGO_E_POINTALREADYDEFINED);

   CComQIPtr<ILocate2> locate(m_Engine);
   hr = locate->ParallelLineSegment(line,offset,&newLine);
   if ( FAILED(hr) )
      return hr;

   hr = m_Lines->AddEx(newLineID,newLine);
   if ( FAILED(hr) )
      return hr;

   // Add the new end points
   CComPtr<IPoint2d> lsFrom;
   newLine->get_StartPoint(&lsFrom);
   CComQIPtr<IPoint2d> lsFromEx(lsFrom);
   hr = m_Points->AddEx(newFromID,lsFromEx);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> lsTo;
   newLine->get_EndPoint(&lsTo);
   CComQIPtr<IPoint2d> lsToEx(lsTo);
   hr = m_Points->AddEx(newToID,lsToEx);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

////////////////////////////////////////////////////////
// IIntersect
STDMETHODIMP CCogoModel::Bearings(CogoObjectID newID, CogoObjectID id1, VARIANT varDir1, Float64 offset1, CogoObjectID id2, VARIANT varDir2, Float64 offset2, VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   // Get the input data and validate
   CComPtr<IPoint2d> pnt[2];
   HRESULT hr;

   hr = m_Points->get_Item(id1,&pnt[0]);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->get_Item(id2,&pnt[1]);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> newPnt;
   CComQIPtr<IIntersect2> intersect(m_Engine);
   hr = intersect->Bearings(pnt[0],varDir1,offset1,pnt[1],varDir2,offset2,&newPnt);
   if ( FAILED(hr) )
      return hr;

   if (newPnt == nullptr )
   {
      *bFound = VARIANT_FALSE;
   }
   else
   {
      *bFound = VARIANT_TRUE;

      // Add the point. If a point with this ID already exists,
      // this method will fail. Return the error if this happens

      hr = m_Points->AddEx(newID,newPnt);
      if ( FAILED(hr) )
         return hr;
   }

   return S_OK;
}

STDMETHODIMP CCogoModel::BearingCircle(CogoObjectID newID, CogoObjectID id1, VARIANT varDir, Float64 offset, CogoObjectID idc, Float64 radius, CogoObjectID idNearest, VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   if ( radius <= 0.0 )
      return Error(IDS_E_RADIUS,IID_IIntersect,COGO_E_RADIUS);

   // Get the input data and validate
   CComPtr<IPoint2d> pnt1;
   HRESULT hr;

   hr = m_Points->get_Item(id1,&pnt1);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pntCenter;
   hr = m_Points->get_Item(idc,&pntCenter);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pntNearest;
   hr = m_Points->get_Item(idNearest,&pntNearest);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> newPnt;
   CComQIPtr<IIntersect2> intersect(m_Engine);
   hr = intersect->BearingCircle(pnt1,varDir,offset,pntCenter,radius,pntNearest,&newPnt);

   if ( newPnt == nullptr )
   {
      *bFound = VARIANT_FALSE;
   }
   else
   {
      hr = m_Points->AddEx(newID,newPnt);
      if ( FAILED(hr) )
         return hr;

      *bFound = VARIANT_TRUE;
   }

   return S_OK;
}

STDMETHODIMP CCogoModel::Circles(CogoObjectID newID, CogoObjectID id1, Float64 r1, CogoObjectID id2, Float64 r2, CogoObjectID idNearest, VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   if ( r1 <= 0.0 || r2 <= 0.0 )
      return Error(IDS_E_RADIUS,IID_IIntersect,COGO_E_RADIUS);

   // Get the input data and validate
   CComPtr<IPoint2d> c1;
   HRESULT hr;

   hr = m_Points->get_Item(id1,&c1);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> c2;
   hr = m_Points->get_Item(id2,&c2);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pntNearest;
   hr = m_Points->get_Item(idNearest,&pntNearest);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> newPnt;
   CComQIPtr<IIntersect2> intersect(m_Engine);
   hr = intersect->Circles(c1,r1,c2,r2,pntNearest,&newPnt);
   if ( FAILED(hr) )
      return hr;

   if ( newPnt == nullptr )
   {
      *bFound = VARIANT_FALSE;
   }
   else
   {
      hr = m_Points->AddEx(newID,newPnt);
      if ( FAILED(hr) )
         return hr;

      *bFound = VARIANT_TRUE;
   }


   return S_OK;
}

STDMETHODIMP CCogoModel::LineByPointsCircle(CogoObjectID newID, CogoObjectID id1, CogoObjectID id2, Float64 offset, CogoObjectID idc, Float64 radius, CogoObjectID idNearest, VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   if ( radius <= 0.0 )
      return Error(IDS_E_RADIUS,IID_IIntersect,COGO_E_RADIUS);

   // Get the input data and validate
   HRESULT hr;
   CComPtr<IPoint2d> pnt1;
   hr = m_Points->get_Item(id1,&pnt1);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pnt2;
   hr = m_Points->get_Item(id2,&pnt2);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pntCenter;
   hr = m_Points->get_Item(idc,&pntCenter);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pntNearest;
   hr = m_Points->get_Item(idNearest,&pntNearest);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pnt;
   CComQIPtr<IIntersect2> intersect(m_Engine);
   hr = intersect->LineByPointsCircle(pnt1,pnt2,offset,pntCenter,radius,pntNearest,&pnt);

   if ( pnt == nullptr )
   {
      *bFound = VARIANT_FALSE;
   }
   else
   {
      *bFound = VARIANT_TRUE;
      hr = m_Points->AddEx(newID,pnt);
      if ( FAILED(hr) )
         return hr;
   }

   return S_OK;
}

STDMETHODIMP CCogoModel::LinesByPoints(CogoObjectID newID, CogoObjectID id11, CogoObjectID id12, Float64 offset1, CogoObjectID id21, CogoObjectID id22, Float64 offset2, VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   // Get the input data and validate
   HRESULT hr;
   CComPtr<IPoint2d> pnt11;
   hr = m_Points->get_Item(id11,&pnt11);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pnt12;
   hr = m_Points->get_Item(id12,&pnt12);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pnt21;
   hr = m_Points->get_Item(id21,&pnt21);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pnt22;
   hr = m_Points->get_Item(id22,&pnt22);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> newPnt;
   CComQIPtr<IIntersect2> intersect(m_Engine);
   hr = intersect->LinesByPoints(pnt11,pnt12,offset1,pnt21,pnt22,offset2,&newPnt);
   if ( FAILED(hr) )
      return hr;

   if ( newPnt == nullptr )
   {
      *bFound = VARIANT_FALSE;
   }
   else
   {
      hr = m_Points->AddEx(newID,newPnt);
      if ( FAILED(hr) )
         return hr;

      *bFound = VARIANT_TRUE;
   }

   return S_OK;
}

STDMETHODIMP CCogoModel::Lines(CogoObjectID newID,CogoObjectID id1,Float64 offset1,CogoObjectID id2,Float64 offset2,VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);
   HRESULT hr;

   // Make sure we will be able to store the new point
   CComPtr<IPoint2d> testPnt;
   hr = m_Points->get_Item(newID,&testPnt);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ILocate,COGO_E_POINTALREADYDEFINED);

   CComPtr<ILineSegment2d> seg1;
   hr = m_Lines->get_Item(id1,&seg1);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ILineSegment2d> seg2;
   hr = m_Lines->get_Item(id2,&seg2);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> newPnt;
   CComQIPtr<IIntersect2> intersect(m_Engine);
   hr = intersect->Lines(seg1,offset1,seg2,offset2,&newPnt);
   if ( FAILED(hr) )
      return hr;

   if ( newPnt == nullptr )
   {
      *bFound = VARIANT_FALSE;
      return S_OK;
   }

   *bFound = VARIANT_TRUE;

   hr = m_Points->AddEx(newID,newPnt);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoModel::LineSegmentCircle(CogoObjectID newID,CogoObjectID lineID,Float64 offset,CogoObjectID idc,Float64 radius,CogoObjectID idNearest,VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);
   HRESULT hr;

   if ( radius <= 0 )
      return Error(IDS_E_RADIUS,IID_ILocate,COGO_E_RADIUS);

   CComPtr<IPoint2d> testPnt;
   hr = m_Points->get_Item(newID,&testPnt);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ILocate,COGO_E_POINTALREADYDEFINED);

   CComPtr<ILineSegment2d> seg;
   hr = m_Lines->get_Item(lineID,&seg);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pntCenter;
   hr = m_Points->get_Item(idc,&pntCenter);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pntNearest;
   hr = m_Points->get_Item(idNearest,&pntNearest);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> newPnt;
   CComQIPtr<IIntersect2> intersect(m_Engine);
   hr = intersect->LineSegmentCircle(seg,offset,pntCenter,radius,pntNearest,&newPnt);
   if ( FAILED(hr) )
      return hr;

   if ( newPnt == nullptr )
   {
      *bFound = VARIANT_FALSE;
   }
   else
   {
      hr = m_Points->AddEx(newID,newPnt);
      if ( FAILED(hr) )
         return hr;

      *bFound = VARIANT_TRUE;
   }

   return S_OK;
}

////////////////////////////////////////////////////////
// IProject
STDMETHODIMP CCogoModel::PointOnLineByPoints(CogoObjectID newID, CogoObjectID fromID, CogoObjectID startID, CogoObjectID endID, Float64 offset)
{
   HRESULT hr;
   CComPtr<IPoint2d> pntFrom;
   hr = m_Points->get_Item(fromID,&pntFrom);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pntStart;
   hr = m_Points->get_Item(startID,&pntStart);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pntEnd;
   hr = m_Points->get_Item(endID,&pntEnd);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> newPnt;
   CComQIPtr<IProject2> project(m_Engine);
   hr = project->PointOnLineByPoints(pntFrom,pntStart,pntEnd,offset,&newPnt);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->AddEx(newID,newPnt);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoModel::PointOnLineSegment(CogoObjectID newID, CogoObjectID fromID, CogoObjectID lineID, Float64 offset)
{
   HRESULT hr;

   CComPtr<ILineSegment2d> seg;
   hr = m_Lines->get_Item(lineID,&seg);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> from;
   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> newPnt;
   CComQIPtr<IProject2> project(m_Engine);
   hr = project->PointOnLineSegment(from,seg,offset,&newPnt);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->AddEx(newID,newPnt);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CCogoModel::PointOnCurve(CogoObjectID newID, CogoObjectID fromID, CogoObjectID curveID)
{
   HRESULT hr;

   CComPtr<IPoint2d> testPnt;
   hr = m_Points->get_Item(newID,&testPnt);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_IProject,COGO_E_POINTALREADYDEFINED);

   CComPtr<IPoint2d> fromPnt;
   hr = m_Points->get_Item(fromID,&fromPnt);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IHorzCurve> curve;
   hr = m_HorzCurves->get_Item(curveID,&curve);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> newPnt;
   CComQIPtr<IProject2> project(m_Engine);
   hr = project->PointOnCurve(fromPnt,curve,&newPnt);
   if ( FAILED(hr) )
      return hr;

   hr = m_Points->AddEx(newID,newPnt);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

////////////////////////////////////////////////////////
// IDivide
STDMETHODIMP CCogoModel::Arc(CogoObjectID firstID, CogoObjectID idInc, CogoObjectID fromID, CogoObjectID vertexID, CogoObjectID toID, CollectionIndexType nParts)
{
   if ( nParts <= 1 || nParts == INVALID_INDEX )
      return E_INVALIDARG;

   if ( idInc == 0 )
      return E_INVALIDARG;

   if ( fromID == vertexID || fromID == toID || vertexID == toID )
   {
      return Error(IDS_E_ANGLE,IID_IDivide,COGO_E_ANGLE);
   }

   // Check to see if the ID's of the new points are already in use
   HRESULT hr;
   CComPtr<IPoint2d> pnt;
   for ( CollectionIndexType i = 0; i < nParts-1; i++ )
   {
      CogoObjectID id = CogoObjectID(firstID + i*idInc);
      pnt.Release();
      hr = m_Points->get_Item(id,&pnt);
      if ( SUCCEEDED(hr) )
         return Error(IDS_E_POINTALREADYDEFINED,IID_IDivide,COGO_E_POINTALREADYDEFINED);
   }

   // Get the 3 points that define the arc
   CComPtr<IPoint2d> from;
   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> vertex;
   hr = m_Points->get_Item(vertexID,&vertex);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> to;
   hr = m_Points->get_Item(toID,&to);
   if ( FAILED(hr) )
      return hr;

   // Divide the arc
   CComPtr<IPoint2dCollection> points;
   CComQIPtr<IDivide2> divide(m_Engine);
   hr = divide->Arc(from,vertex,to,nParts,&points);
   if ( FAILED(hr) )
      return hr;

   // Store the points in the points collection
   for (CollectionIndexType i = 0; i < nParts-1; i++)
   {
      CogoObjectID id = firstID + i*idInc;
      CComPtr<IPoint2d> p;
      points->get_Item(i+1,&p); // get the point from the collection

      CComQIPtr<IPoint2d> pEx(p);
    
      // m_GeomUtil's factory must create a IPoint2d object.
      // If not, a factory got let in that shouldn't have
      ATLASSERT(pEx != nullptr);

      hr = m_Points->AddEx(id,pEx); // add it to the cogo model
      ATLASSERT(SUCCEEDED(hr));
   }

   return S_OK;
}

STDMETHODIMP CCogoModel::BetweenPoints(CogoObjectID firstID, CogoObjectID idInc, CogoObjectID fromID, CogoObjectID toID, CollectionIndexType nParts)
{
   if ( nParts <= 1 || nParts == INVALID_INDEX )
      return E_INVALIDARG;

   if ( idInc == 0 )
      return E_INVALIDARG;

   // Check to see if the ID's of the new points are already in use
   HRESULT hr;
   CComPtr<IPoint2d> pnt;
   for ( CollectionIndexType i = 0; i < nParts-1; i++ )
   {
      CogoObjectID id = CogoObjectID(firstID + i*idInc);
      pnt.Release();
      hr = m_Points->get_Item(id,&pnt);
      if ( SUCCEEDED(hr) )
         return Error(IDS_E_POINTALREADYDEFINED,IID_IDivide,COGO_E_POINTALREADYDEFINED);
   }

   // Get the points that define the line
   CComPtr<IPoint2d> from;
   hr = m_Points->get_Item(fromID,&from);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> to;
   hr = m_Points->get_Item(toID,&to);
   if ( FAILED(hr) )
      return hr;

   // Divide the line
   CComPtr<IPoint2dCollection> points;
   CComQIPtr<IDivide2> divide(m_Engine);
   hr = divide->BetweenPoints(from,to,nParts,&points);
   if ( FAILED(hr) )
      return hr;

   // Store the points in the points collection
   for (CollectionIndexType i = 0; i < nParts-1; i++)
   {
      CogoObjectID id = firstID + i*idInc;
      CComPtr<IPoint2d> p;
      points->get_Item(i+1,&p); // get the point from the collection

      CComQIPtr<IPoint2d> pEx(p);

      // m_GeomUtil's factory must create a IPoint2d object.
      // If not, a factory got let in that shouldn't have
      ATLASSERT(pEx != nullptr);

      hr = m_Points->AddEx(id,pEx); // add it to the cogo model
      ATLASSERT(SUCCEEDED(hr));
   }

   return S_OK;
}

STDMETHODIMP CCogoModel::LineSegment(CogoObjectID firstID, CogoObjectID idInc, CogoObjectID lineID, CollectionIndexType nParts)
{
   if ( nParts <= 1 || nParts == INVALID_INDEX )
      return E_INVALIDARG;

   if ( idInc == 0 )
      return E_INVALIDARG;

   // Check to see if the ID's of the new points are already in use
   HRESULT hr;
   CComPtr<IPoint2d> pnt;
   for ( CollectionIndexType i = 0; i < nParts-1; i++ )
   {
      CogoObjectID id = CogoObjectID(firstID + i*idInc);
      pnt.Release();
      hr = m_Points->get_Item(id,&pnt);
      if ( SUCCEEDED(hr) )
         return Error(IDS_E_POINTALREADYDEFINED,IID_IDivide,COGO_E_POINTALREADYDEFINED);
   }

   // Get the line segment
   CComPtr<ILineSegment2d> seg;
   hr = m_Lines->get_Item(lineID,&seg);
   if ( FAILED(hr) )
      return hr;

   // Divide the line
   CComPtr<IPoint2dCollection> points;
   CComQIPtr<IDivide2> divide(m_Engine);
   hr = divide->LineSegment(seg,nParts,&points);
   if ( FAILED(hr) )
      return hr;

   // Store the points in the points collection
   for (CollectionIndexType i = 0; i < nParts-1; i++)
   {
      CogoObjectID id = firstID + i*idInc;
      CComPtr<IPoint2d> p;
      points->get_Item(i+1,&p); // get the point from the collection

      CComQIPtr<IPoint2d> pEx(p);

      // m_GeomUtil's factory must create a IPoint2d object.
      // If not, a factory got let in that shouldn't have
      ATLASSERT(pEx != nullptr);

      hr = m_Points->AddEx(id,pEx); // add it to the cogo model
      ATLASSERT(SUCCEEDED(hr));
   }

   return S_OK;
}

STDMETHODIMP CCogoModel::HorzCurve(CogoObjectID firstID, CogoObjectID idInc, CogoObjectID curveID, CollectionIndexType nParts)
{
   if ( nParts <= 1 || nParts == INVALID_INDEX)
      return E_INVALIDARG;

   if ( idInc == 0 )
      return E_INVALIDARG;

   // Check to see if the ID's of the new points are already in use
   HRESULT hr;
   CComPtr<IPoint2d> pnt;
   for ( CollectionIndexType i = 0; i < nParts-1; i++ )
   {
      CogoObjectID id = firstID + i*idInc;
      pnt.Release();
      hr = m_Points->get_Item(id,&pnt);
      if ( SUCCEEDED(hr) )
         return Error(IDS_E_POINTALREADYDEFINED,IID_IDivide,COGO_E_POINTALREADYDEFINED);
   }

   // Get the curve
   CComPtr<IHorzCurve> hc;
   hr = m_HorzCurves->get_Item(curveID,&hc);
   if ( FAILED(hr) )
      return hr;

   // Divide the curve
   CComPtr<IPoint2dCollection> points;
   CComQIPtr<IDivide2> divide(m_Engine);
   hr = divide->HorzCurve(hc,nParts,&points);
   if ( FAILED(hr) )
      return hr;

   // Store the points in the points collection
   CComPtr<IEnumPoint2d> enum_points;
   points->get__Enum(&enum_points);
   CComPtr<IPoint2d> p;
   CogoObjectID i = 0;
   while ( enum_points->Next(1,&p,nullptr) != S_FALSE )
   {
      CogoObjectID id = firstID + i*idInc;

      CComQIPtr<IPoint2d> pEx(p);

      // m_GeomUtil's factory must create a IPoint2d object.
      // If not, a factory got let in that shouldn't have
      ATLASSERT(pEx != nullptr);

      hr = m_Points->AddEx(id,pEx); // add it to the cogo model
      if ( FAILED(hr) )
         return hr;

      p.Release();
      i++;
   }

   return S_OK;
}

STDMETHODIMP CCogoModel::Path(CogoObjectID firstID,CogoObjectID idInc,CogoObjectID pathID,CollectionIndexType nParts,Float64 start,Float64 end)
{
   if ( nParts <= 1 || nParts == INVALID_INDEX)
      return E_INVALIDARG;

   if ( idInc == 0 )
      return E_INVALIDARG;

   // Check to see if the ID's of the new points are already in use
   HRESULT hr;
   CComPtr<IPoint2d> pnt;
   for ( CollectionIndexType i = 0; i < nParts-1; i++ )
   {
      CogoObjectID id = firstID + i*idInc;
      pnt.Release();
      hr = m_Points->get_Item(id,&pnt);
      if ( SUCCEEDED(hr) )
         return Error(IDS_E_POINTALREADYDEFINED,IID_IDivide,COGO_E_POINTALREADYDEFINED);
   }

   // Get the curve
   CComPtr<IPath> path;
   hr = m_Paths->get_Item(pathID,&path);
   if ( FAILED(hr) )
      return hr;

   // Divide the path
   CComPtr<IPoint2dCollection> points;
   CComQIPtr<IDivide2> divide(m_Engine);
   hr = divide->Path(path,nParts,start,end,&points);
   if ( FAILED(hr) )
      return hr;

   // Store the points in the points collection
   CComPtr<IEnumPoint2d> enum_points;
   points->get__Enum(&enum_points);
   CComPtr<IPoint2d> p;
   CogoObjectID i = 0;
   while ( enum_points->Next(1,&p,nullptr) != S_FALSE )
   {
      CogoObjectID id = firstID + i*idInc;

      CComQIPtr<IPoint2d> pEx(p);

      // m_GeomUtil's factory must create a IPoint2d object.
      // If not, a factory got let in that shouldn't have
      ATLASSERT(pEx != nullptr);

      hr = m_Points->AddEx(id,pEx); // add it to the cogo model
      if ( FAILED(hr) )
         return hr;

      p.Release();
      i++;
   }

   return S_OK;
}

////////////////////////////////////////////////////////
// ITangent
STDMETHODIMP CCogoModel::Cross(CogoObjectID newID1, CogoObjectID idCenter1, Float64 radius1, CogoObjectID newID2, CogoObjectID idCenter2, Float64 radius2, TangentSignType sign)
{
   // Check the radii
   if ( radius1 <= 0.0 )
      return Error(IDS_E_RADIUS,IID_ITangent,COGO_E_RADIUS);

   if ( radius2 <= 0.0 )
      return Error(IDS_E_RADIUS,IID_ITangent,COGO_E_RADIUS);

   // Verify newID1 and newID2 are available
   HRESULT hr;
   CComPtr<IPoint2d> pnt;
   hr = m_Points->get_Item(newID1,&pnt);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ITangent,COGO_E_POINTALREADYDEFINED);

   pnt.Release();
   hr = m_Points->get_Item(newID2,&pnt);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ITangent,COGO_E_POINTALREADYDEFINED);

   CComPtr<IPoint2d> A, B; // Center of circle A and B
   hr = m_Points->get_Item(idCenter1,&A);
   if ( FAILED(hr) ) // Point doesn't exist in cogo model
      return hr;

   hr = m_Points->get_Item(idCenter2,&B);
   if ( FAILED(hr) ) // Point doesn't exist in cogo model
      return hr;

   CComQIPtr<ITangent2> tangent(m_Engine);
   CComPtr<IPoint2d> pnt1,pnt2;
   hr = tangent->Cross(A,radius1,B,radius2,sign,&pnt1,&pnt2);
   if ( FAILED(hr) )
      return hr;

   // store the two new points
   m_Points->AddEx(newID1,pnt1);
   m_Points->AddEx(newID2,pnt2);

   return S_OK;
}

STDMETHODIMP CCogoModel::External(CogoObjectID newID1, CogoObjectID idCenter1, Float64 radius1, CogoObjectID newID2, CogoObjectID idCenter2, Float64 radius2, TangentSignType sign)
{
   // Check the radii
   if ( radius1 <= 0.0 )
      return Error(IDS_E_RADIUS,IID_ITangent,COGO_E_RADIUS);

   if ( radius2 <= 0.0 )
      return Error(IDS_E_RADIUS,IID_ITangent,COGO_E_RADIUS);

   // Verify newID1 and newID2 are available
   HRESULT hr;
   CComPtr<IPoint2d> pnt;
   hr = m_Points->get_Item(newID1,&pnt);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ITangent,COGO_E_POINTALREADYDEFINED);

   pnt.Release();
   hr = m_Points->get_Item(newID2,&pnt);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ITangent,COGO_E_POINTALREADYDEFINED);

   CogoObjectID idA, idB; // ID's of center points of circle A and B. Circle A is the one with the larger radius
   Float64 Ar, Br; // Radius of circle A and B
   CogoObjectID idTanA, idTanB; // ID's of tangent points to cirle A and B
   if ( radius2 <= radius1 )
   {
      idA = idCenter1;
      Ar = radius1;
      idTanA = newID1;

      idB = idCenter2;
      Br = radius2;
      idTanB = newID2;
   }
   else
   {
      idA = idCenter2;
      Ar = radius2;
      idTanA = newID2;

      idB = idCenter1;
      Br = radius1;
      idTanB = newID1;
   }

   CComPtr<IPoint2d> A, B; // Center of circle A and B
   hr = m_Points->get_Item(idA,&A);
   if ( FAILED(hr) ) // Point doesn't exist in cogo model
      return hr;

   hr = m_Points->get_Item(idB,&B);
   if ( FAILED(hr) ) // Point doesn't exist in cogo model
      return hr;

   CComQIPtr<ITangent2> tangent(m_Engine);
   CComPtr<IPoint2d> pnt1,pnt2;
   hr = tangent->External(A,Ar,B,Br,sign,&pnt1,&pnt2);
   if ( FAILED(hr) )
      return hr;

   // store the two new points
   m_Points->AddEx(idTanA,pnt1);
   m_Points->AddEx(idTanB,pnt2);

   return S_OK;
}

STDMETHODIMP CCogoModel::Point(CogoObjectID newID, CogoObjectID idCenter, Float64 radius,CogoObjectID pointID,TangentSignType sign)
{
   // Check the radius
   if ( radius <= 0.0 )
      return Error(IDS_E_RADIUS,IID_ITangent,COGO_E_RADIUS);

   // Verify newID is available
   HRESULT hr;
   CComPtr<IPoint2d> pnt;
   hr = m_Points->get_Item(newID,&pnt);
   if ( SUCCEEDED(hr) )
      return Error(IDS_E_POINTALREADYDEFINED,IID_ITangent,COGO_E_POINTALREADYDEFINED);

   CComPtr<IPoint2d> A, B; // Center of circle A and B
   hr = m_Points->get_Item(idCenter,&A);
   if ( FAILED(hr) ) // Point doesn't exist in cogo model
      return hr;

   hr = m_Points->get_Item(pointID,&B);
   if ( FAILED(hr) ) // Point doesn't exist in cogo model
      return hr;

   CComQIPtr<ITangent2> tangent(m_Engine);
   CComPtr<IPoint2d> pntTangent;
   hr = tangent->Point(A,radius,B,sign,&pntTangent);
   if ( FAILED(hr) )
      return hr;

   // store the new point
   m_Points->AddEx(newID,pntTangent);

   return S_OK;
}

////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CCogoModel::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("CogoModel"),1.0);

   CComPtr<IPoint2dFactory> factory;
   m_Engine->get_PointFactory(&factory);
   pSave->put_Property(CComBSTR("PointFactory"),CComVariant(factory));

   // Save collections by value (we own them by value here, no one can
   // give us a collection)
   CComQIPtr<IStructuredStorage2> ssPoints(m_Points);
   ssPoints->Save(pSave);

   CComQIPtr<IStructuredStorage2> ssLines(m_Lines);
   ssLines->Save(pSave);

   CComQIPtr<IStructuredStorage2> ssHorzCurves(m_HorzCurves);
   ssHorzCurves->Save(pSave);

   CComQIPtr<IStructuredStorage2> ssProfilePoints(m_ProfilePoints);
   ssProfilePoints->Save(pSave);

   CComQIPtr<IStructuredStorage2> ssVertCurves(m_VertCurves);
   ssVertCurves->Save(pSave);

   CComQIPtr<IStructuredStorage2> ssAlignments(m_Alignments);
   ssAlignments->Save(pSave);

   CComQIPtr<IStructuredStorage2> ssPaths(m_Paths);
   ssPaths->Save(pSave);

   pSave->EndUnit();
   return S_OK;
}

STDMETHODIMP CCogoModel::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;

   pLoad->BeginUnit(CComBSTR("CogoModel"));
   
   pLoad->get_Property(CComBSTR("PointFactory"),&var);
   CComPtr<IPoint2dFactory> factory;
   _CopyVariantToInterface<IPoint2dFactory>::copy(&factory,&var);
   m_Engine->putref_PointFactory(factory);

   // Load collections by value (we own them by value here, no one can
   // give us a collection)
   CComQIPtr<IStructuredStorage2> ssPoints(m_Points);
   ssPoints->Load(pLoad);

   CComQIPtr<IStructuredStorage2> ssLines(m_Lines);
   ssLines->Load(pLoad);

   CComQIPtr<IStructuredStorage2> ssHorzCurves(m_HorzCurves);
   ssHorzCurves->Load(pLoad);

   CComQIPtr<IStructuredStorage2> ssProfilePoints(m_ProfilePoints);
   ssProfilePoints->Load(pLoad);

   CComQIPtr<IStructuredStorage2> ssVertCurves(m_VertCurves);
   ssVertCurves->Load(pLoad);

   CComQIPtr<IStructuredStorage2> ssAlignments(m_Alignments);
   ssAlignments->Load(pLoad);

   CComQIPtr<IStructuredStorage2> ssPaths(m_Paths);
   ssPaths->Load(pLoad);

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

////////////////////////////////////////////////////////
// IPointCollectionEvents
STDMETHODIMP CCogoModel::OnPointChanged(CogoObjectID id,IPoint2d* point)
{
   Fire_OnPointChanged(this,id,point);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnPointAdded(CogoObjectID id,IPoint2d* point)
{
   Fire_OnPointAdded(this,id,point);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnPointRemoved(CogoObjectID id)
{
   Fire_OnPointRemoved(this,id);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnPointsCleared()
{
   Fire_OnPointsCleared(this);
   return S_OK;
}

////////////////////////////////////////////////////////
// ILineSegmentCollectionEvents
STDMETHODIMP CCogoModel::OnLineSegmentChanged(CogoObjectID id, ILineSegment2d* lineSeg)
{
   Fire_OnLineSegmentChanged(this,id,lineSeg);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnLineSegmentAdded(CogoObjectID id, ILineSegment2d* lineSeg)
{
   Fire_OnLineSegmentAdded(this,id,lineSeg);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnLineSegmentRemoved(CogoObjectID id)
{
   Fire_OnLineSegmentRemoved(this,id);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnLineSegmentsCleared()
{
   Fire_OnLineSegmentsCleared(this);
   return S_OK;
}

////////////////////////////////////////////////////////
// IProfilePointCollectionEvents
STDMETHODIMP CCogoModel::OnProfilePointChanged(CogoObjectID id,IProfilePoint* pp)
{
   Fire_OnProfilePointChanged(this,id,pp);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnProfilePointAdded(CogoObjectID id,IProfilePoint* pp)
{
   Fire_OnProfilePointAdded(this,id,pp);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnProfilePointRemoved(CogoObjectID id)
{
   Fire_OnProfilePointRemoved(this,id);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnProfilePointsCleared()
{
   Fire_OnProfilePointsCleared(this);
   return S_OK;
}

////////////////////////////////////////////////////////
// IVertCurveCollectionEvents
STDMETHODIMP CCogoModel::OnVertCurveChanged(CogoObjectID id,IVertCurve* vc)
{
   Fire_OnVertCurveChanged(this,id,vc);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnVertCurveAdded(CogoObjectID id,IVertCurve* vc)
{
   Fire_OnVertCurveAdded(this,id,vc);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnVertCurveRemoved(CogoObjectID id)
{
   Fire_OnVertCurveRemoved(this,id);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnVertCurvesCleared()
{
   Fire_OnVertCurvesCleared(this);
   return S_OK;
}

////////////////////////////////////////////////////////
// IHorzCurveCollectionEvents
STDMETHODIMP CCogoModel::OnHorzCurveChanged(CogoObjectID id,IHorzCurve* hc)
{
   Fire_OnHorzCurveChanged(this,id,hc);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnHorzCurveAdded(CogoObjectID id,IHorzCurve* hc)
{
   Fire_OnHorzCurveAdded(this,id,hc);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnHorzCurveRemoved(CogoObjectID id)
{
   Fire_OnHorzCurveRemoved(this,id);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnHorzCurvesCleared()
{
   Fire_OnHorzCurvesCleared(this);
   return S_OK;
}

////////////////////////////////////////////////////////
// IPathCollectionEvents

STDMETHODIMP CCogoModel::OnPathChanged(IPathCollection* coll,CogoObjectID id,IPath* path)
{
   CComQIPtr<IAlignment> alignment(path);
   if ( m_Alignments.IsEqualObject(coll) )
      Fire_OnAlignmentChanged(this,id,alignment);
   else
      Fire_OnPathChanged(this,id,path);

   return S_OK;
}

STDMETHODIMP CCogoModel::OnPathAdded(IPathCollection* coll,CogoObjectID id,IPath* path)
{
   CComQIPtr<IAlignment> alignment(path);
   if ( m_Alignments.IsEqualObject(coll) )
      Fire_OnAlignmentAdded(this,id,alignment);
   else
      Fire_OnPathAdded(this,id,path);

   return S_OK;
}

STDMETHODIMP CCogoModel::OnPathRemoved(IPathCollection* coll,CogoObjectID id)
{
   if ( m_Alignments.IsEqualObject(coll) )
      Fire_OnAlignmentRemoved(this,id);
   else
      Fire_OnPathRemoved(this,id);

   return S_OK;
}

STDMETHODIMP CCogoModel::OnPathsCleared(IPathCollection* coll)
{
   if ( m_Alignments.IsEqualObject(coll) )
      Fire_OnAlignmentsCleared(this);
   else
      Fire_OnPathsCleared(this);

   return S_OK;
}

////////////////////////////////////////////////////////
// IAlignmentCollectionEvents

STDMETHODIMP CCogoModel::OnProfileChanged(IAlignmentCollection* coll,IProfile* profile)
{
   Fire_OnProfileChanged(this,profile);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnStationEquationsChanged(IAlignmentCollection* coll,IStationEquationCollection* equations)
{
   Fire_OnStationEquationsChanged(this,equations);
   return S_OK;
}

STDMETHODIMP CCogoModel::OnAlignmentChanged(IAlignmentCollection* coll,CogoObjectID id,IAlignment* Alignment)
{
   CComQIPtr<IAlignment> alignment(Alignment);
   if ( m_Alignments.IsEqualObject(coll) )
      Fire_OnAlignmentChanged(this,id,alignment);
   else
      Fire_OnAlignmentChanged(this,id,Alignment);

   return S_OK;
}

STDMETHODIMP CCogoModel::OnAlignmentAdded(IAlignmentCollection* coll,CogoObjectID id,IAlignment* Alignment)
{
   CComQIPtr<IAlignment> alignment(Alignment);
   if ( m_Alignments.IsEqualObject(coll) )
      Fire_OnAlignmentAdded(this,id,alignment);
   else
      Fire_OnAlignmentAdded(this,id,Alignment);

   return S_OK;
}

STDMETHODIMP CCogoModel::OnAlignmentRemoved(IAlignmentCollection* coll,CogoObjectID id)
{
   if ( m_Alignments.IsEqualObject(coll) )
      Fire_OnAlignmentRemoved(this,id);
   else
      Fire_OnAlignmentRemoved(this,id);

   return S_OK;
}

STDMETHODIMP CCogoModel::OnAlignmentsCleared(IAlignmentCollection* coll)
{
   if ( m_Alignments.IsEqualObject(coll) )
      Fire_OnAlignmentsCleared(this);
   else
      Fire_OnAlignmentsCleared(this);

   return S_OK;
}
