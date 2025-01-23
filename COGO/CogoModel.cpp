///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


template <class C>
IDType CCogoModel::GetID(const C& container, IndexType index)
{
   if (container.size() <= index) return INVALID_ID;

   auto iter = container.begin();
   std::advance(iter, index);
   return iter->first;
}

/////////////////////////////////////////////////////////////////////////////
// CCogoModel
HRESULT CCogoModel::FinalConstruct()
{
   m_Engine.CoCreateInstance(CLSID_CogoEngine);
   return S_OK;
}

void CCogoModel::FinalRelease()
{
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
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCogoModel::StorePoint(IDType id, Float64 x, Float64 y)
{
   return m_Model->StorePoint(id, x, y) ? S_OK : E_FAIL;
}

STDMETHODIMP CCogoModel::StorePointEx(IDType id, IPoint2d* pPoint)
{
   CHECK_IN(pPoint);
   return m_Model->StorePoint(id, cogoUtil::GetPoint(pPoint)) ? S_OK : E_FAIL;
}

STDMETHODIMP CCogoModel::StorePoints(IDType firstID, IDType idInc, IPoint2dCollection* pPoints)
{
   CHECK_IN(pPoints);
   IndexType nPoints;
   pPoints->get_Count(&nPoints);
   std::vector<WBFL::Geometry::Point2d> vPoints;
   for (IndexType i = 0; i < nPoints; i++)
   {
      CComPtr<IPoint2d> pnt;
      pPoints->get_Item(i, &pnt);
      vPoints.emplace_back(cogoUtil::GetPoint(pnt));
   }

   return m_Model->StorePoints(firstID, idInc, vPoints) ? S_OK : E_FAIL;
}

STDMETHODIMP CCogoModel::GetPointCount(IndexType* nPoints)
{
   CHECK_RETVAL(nPoints);
   *nPoints = m_Model->GetPoints().size();
   return S_OK;
}

STDMETHODIMP CCogoModel::GetPointByID(IDType id, IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   HRESULT hr = S_OK;
   try
   {
      const auto& point = m_Model->GetPoint(id);
      hr = cogoUtil::CreatePoint(point, ppPoint);
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetPointByIndex(IndexType idx, IDType* pID, IPoint2d** ppPoint)
{
   IDType id;
   if ((id = GetID(m_Model->GetPoints(), idx)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetPointByID(*pID, ppPoint);
}

STDMETHODIMP CCogoModel::ReplacePointByID(IDType id, Float64 x, Float64 y)
{
   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->ReplacePoint(id, x, y);
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::ReplacePointByIDEx(IDType id, IPoint2d* pPoint)
{
   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->ReplacePoint(id, cogoUtil::GetPoint(pPoint));
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::ReplacePointByIndex(IndexType idx, Float64 x, Float64 y)
{
   IDType id;
   if ((id = GetID(m_Model->GetPoints(), idx)) == INVALID_ID) return E_INVALIDARG;
   return ReplacePointByID(id, x, y);
}

STDMETHODIMP CCogoModel::ReplacePointByIndexEx(IndexType idx, IPoint2d* pPoint)
{
   IDType id;
   if ((id = GetID(m_Model->GetPoints(), idx)) == INVALID_ID) return E_INVALIDARG;
   return ReplacePointByIDEx(id, pPoint);
}

STDMETHODIMP CCogoModel::RemovePointByID(IDType id)
{
   return m_Model->RemovePoint(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemovePointByIndex(IndexType index)
{
   IDType id;
   if((id=GetID(m_Model->GetPoints(),index)) == INVALID_ID) return E_INVALIDARG;
   return RemovePointByID(id);
}

STDMETHODIMP CCogoModel::ClearPoints()
{
   m_Model->ClearPoints();
   return S_OK;
}

STDMETHODIMP CCogoModel::StorePathSegment(IDType id, IDType startID, IDType endID)
{
   return m_Model->StorePathSegment(id, startID, endID) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetPathSegmentByID(IDType id, IDType* pStartID, IDType* pEndID)
{
   CHECK_RETVAL(pStartID);
   CHECK_RETVAL(pEndID);

   HRESULT hr = S_OK;
   try
   {
      const auto& definition = m_Model->GetPathSegment(id);
      *pStartID = definition.startID;
      *pEndID = definition.endID;
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return S_OK;
}

STDMETHODIMP CCogoModel::GetPathSegmentByIndex(IndexType idx, IDType* pID, IDType* pStartID, IDType* pEndID)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetPathSegments(), idx)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetPathSegmentByID(id, pStartID, pEndID);
}

STDMETHODIMP CCogoModel::CreatePathSegmentByID(IDType id, IPathSegment** ppSegment)
{
   CHECK_RETOBJ(ppSegment);
   HRESULT hr = S_OK;
   try
   {
      auto path_segment = m_Model->CreatePathSegment(id);
      hr = cogoUtil::CreatePathSegment(path_segment, ppSegment);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreatePathSegmentByIndex(IndexType idx, IPathSegment** ppSegment)
{
   IDType id;
   if ((id = GetID(m_Model->GetPathSegments(), idx)) == INVALID_ID) return E_INVALIDARG;
   return CreatePathSegmentByID(id, ppSegment);
}

STDMETHODIMP CCogoModel::RemovePathSegmentByID(IDType id)
{
   return m_Model->RemovePathSegment(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemovePathSegmentByIndex(IndexType index)
{
   IDType id;
   if ((id = GetID(m_Model->GetPathSegments(), index)) == INVALID_ID) return E_INVALIDARG;

   return RemovePathSegmentByID(id);
}

STDMETHODIMP CCogoModel::ClearPathSegments()
{
   m_Model->ClearPathSegments();
   return S_OK;
}

STDMETHODIMP CCogoModel::StoreCompoundCurve(IDType id, IDType pbtID, IDType piID, IDType pftID, Float64 radius, Float64 lsEntry, TransitionCurveType lsEntryType, Float64 lsExit, TransitionCurveType lsExitType)
{
   return m_Model->StoreCompoundCurve(id, pbtID, piID, pftID, radius, lsEntry, WBFL::COGO::TransitionCurveType(lsEntryType), lsExit, WBFL::COGO::TransitionCurveType(lsExitType)) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetCompoundCurveCountByID(IDType id, IndexType* nCurves)
{
   CHECK_RETVAL(nCurves);
   *nCurves = m_Model->GetCompoundCurves().size();
   return S_OK;
}

STDMETHODIMP CCogoModel::GetCompoundCurveCountByIndex(IndexType index, IDType* pID, IndexType* nCurves)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetCompoundCurves(), index)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetCompoundCurveCountByID(id, nCurves);
}

STDMETHODIMP CCogoModel::GetCompoundCurveByID(IDType id, IDType* pbtID, IDType* piID, IDType* pftID, Float64* pRadius, Float64* pLsEntry, TransitionCurveType* pLsEntryType, Float64* pLsExit, TransitionCurveType* pLsExitType)
{
   CHECK_RETVAL(pbtID);
   CHECK_RETVAL(piID);
   CHECK_RETVAL(pftID);
   CHECK_RETVAL(pRadius);
   CHECK_RETVAL(pLsEntry);
   CHECK_RETVAL(pLsEntryType);
   CHECK_RETVAL(pLsExit);
   CHECK_RETVAL(pLsExitType);

   HRESULT hr = S_OK;
   try
   {
      const auto& definition = m_Model->GetCompoundCurve(id);
      *pbtID = definition.pbtID;
      *piID = definition.piID;
      *pftID = definition.pftID;
      *pRadius = definition.radius;
      *pLsEntry = definition.entry_spiral_length;
      *pLsEntryType = TransitionCurveType(definition.entry_spiral_type);
      *pLsExit = definition.exit_spiral_length;
      *pLsExitType = TransitionCurveType(definition.exit_spiral_type);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}
STDMETHODIMP CCogoModel::GetCompoundCurveByIndex(IndexType idx, IDType* pbtID, IDType* piID, IDType* pftID, Float64* pRadius, Float64* pLsEntry, TransitionCurveType* pLsEntryType, Float64* pLsExit, TransitionCurveType* pLsExitType)
{
   IDType id;
   if ((id = GetID(m_Model->GetCompoundCurves(), idx)) == INVALID_ID) return E_INVALIDARG;
   return GetCompoundCurveByID(id, pbtID, piID, pftID, pRadius, pLsEntry, pLsEntryType, pLsExit, pLsExitType);
}

STDMETHODIMP CCogoModel::CreateCompoundCurveByID(IDType id, ICompoundCurve** ppCurve)
{
   CHECK_RETOBJ(ppCurve);
   HRESULT hr = S_OK;
   try
   {
      auto curve = m_Model->CreateCompoundCurve(id);
      hr = cogoUtil::CreateCompoundCurve(curve, ppCurve);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreateCompoundCurveByIndex(IndexType idx, ICompoundCurve** ppCurve)
{
   IDType id;
   if ((id = GetID(m_Model->GetCompoundCurves(), idx)) == INVALID_ID) return E_INVALIDARG;
   return CreateCompoundCurveByID(id, ppCurve);
}

STDMETHODIMP CCogoModel::RemoveCompoundCurveByID(IDType id)
{
   return m_Model->RemoveCompoundCurve(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemoveCompoundCurveByIndex(IndexType index)
{
   IDType id;
   if ((id = GetID(m_Model->GetCompoundCurves(), index)) == INVALID_ID) return E_INVALIDARG;
   return RemoveCompoundCurveByID(id);
}

STDMETHODIMP CCogoModel::ClearCompoundCurves()
{
   m_Model->ClearCompoundCurves();
   return S_OK;
}

STDMETHODIMP CCogoModel::StoreCircularCurve(IDType id, IDType pbtID, IDType piID, IDType pftID, Float64 radius)
{
   return m_Model->StoreCircularCurve(id, pbtID, piID, pftID, radius) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetCircularCurveByID(IDType id, IDType* pbtID, IDType* piID, IDType* pftID, Float64* pRadius)
{
   CHECK_RETVAL(pbtID);
   CHECK_RETVAL(piID);
   CHECK_RETVAL(pftID);
   CHECK_RETVAL(pRadius);

   HRESULT hr = S_OK;
   try
   {
      const auto& definition = m_Model->GetCircularCurve(id);
      *pbtID = definition.pbtID;
      *piID = definition.piID;
      *pftID = definition.pftID;
      *pRadius = definition.radius;
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetCircularCurveByIndex(IndexType idx, IDType* pID, IDType* pbtID, IDType* piID, IDType* pftID, Float64* pRadius)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetCircularCurves(), idx)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetCircularCurveByID(id,pbtID,piID,pftID,pRadius);
}

STDMETHODIMP CCogoModel::CreateCircularCurveByID(IDType id, ICircularCurve** ppCurve)
{
   CHECK_RETOBJ(ppCurve);
   HRESULT hr = S_OK;
   try
   {
      auto curve = m_Model->CreateCircularCurve(id);
      hr = cogoUtil::CreateCircularCurve(curve, ppCurve);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreateCircularCurveByIndex(IndexType idx, ICircularCurve** ppCurve)
{
   IDType id;
   if ((id = GetID(m_Model->GetCircularCurves(), idx)) == INVALID_ID) return E_INVALIDARG;
   return CreateCircularCurveByID(id, ppCurve);
}

STDMETHODIMP CCogoModel::RemoveCircularCurveByID(IDType id)
{
   return m_Model->RemoveCircularCurve(id) ? S_OK : E_FAIL;
}

STDMETHODIMP CCogoModel::RemoveCircularCurveByIndex(IndexType index)
{
   IDType id;
   if ((id = GetID(m_Model->GetCircularCurves(), index)) == INVALID_ID) return E_INVALIDARG;
   return RemoveCircularCurveByID(id);
}

STDMETHODIMP CCogoModel::ClearCircularCurves()
{
   m_Model->ClearCircularCurves();
   return S_OK;
}

STDMETHODIMP CCogoModel::StoreTransitionCurve(IDType id, IDType startID, VARIANT varDirection, Float64 r1, Float64 r2, Float64 L, TransitionCurveType transitionType)
{
   auto [hr,direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;
   return m_Model->StoreTransitionCurve(id, startID, direction, r1, r2, L, WBFL::COGO::TransitionCurveType(transitionType)) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetTransitionCurveByID(IDType id, IDType* startID, IDirection** ppDirection, Float64* r1, Float64* r2, Float64* L, TransitionCurveType* transitionType)
{
   CHECK_RETVAL(startID);
   CHECK_RETOBJ(ppDirection);
   CHECK_RETVAL(r1);
   CHECK_RETVAL(r2);
   CHECK_RETVAL(L);
   CHECK_RETVAL(transitionType);

   HRESULT hr = S_OK;
   try
   {
      const auto& definition = m_Model->GetTransitionCurve(id);
      *startID = definition.startID;
      *r1 = definition.start_radius;
      *r2 = definition.end_radius;
      *L = definition.length;
      *transitionType = TransitionCurveType(definition.transition_type);
      hr = cogoUtil::CreateDirection(definition.start_direction, ppDirection);
   }
   catch(...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetTransitionCurveByIndex(IndexType index, IDType* pID, IDType* startID, IDirection** ppDirection, Float64* r1, Float64* r2, Float64* L, TransitionCurveType* transitionType)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetTransitionCurves(), index)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetTransitionCurveByID(id, startID, ppDirection, r1, r2, L, transitionType);
}

STDMETHODIMP CCogoModel::CreateTransitionCurveByID(IDType id, ITransitionCurve** ppCurve)
{
   CHECK_RETOBJ(ppCurve);
   HRESULT hr = S_OK;
   try
   {
      auto curve = m_Model->CreateTransitionCurve(id);
      hr = cogoUtil::CreateTransitionCurve(curve, ppCurve);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreateTransitionCurveByIndex(IndexType index, ITransitionCurve** ppCurve)
{
   IDType id;
   if ((id = GetID(m_Model->GetTransitionCurves(), index)) == INVALID_ID) return E_INVALIDARG;
   return CreateTransitionCurveByID(id, ppCurve);
}

STDMETHODIMP CCogoModel::RemoveTransitionCurveByID(IDType id)
{
   return m_Model->RemoveTransitionCurve(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemoveTransitionCurveByIndex(IndexType index)
{
   IDType id;
   if ((id = GetID(m_Model->GetTransitionCurves(), index)) == INVALID_ID) return E_INVALIDARG;
   return RemoveTransitionCurveByID(id);
}

STDMETHODIMP CCogoModel::ClearTransitionCurvese()
{
   m_Model->ClearTransitionCurves();
   return S_OK;
}

STDMETHODIMP CCogoModel::StoreCubicSpline(IDType id, IIDArray* pIDs)
{
   CHECK_IN(pIDs);
   IndexType nIDs;
   pIDs->get_Count(&nIDs);
   std::vector<IDType> vID;
   for (IndexType i = 0; i < nIDs; i++)
   {
      IDType id;
      pIDs->get_Item(i, &id);
      vID.emplace_back(id);
   }

   return m_Model->StoreCubicSpline(id, vID) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetCubicSplineByID(IDType id, IIDArray** ppIDs)
{
   CHECK_RETOBJ(ppIDs);
   CComPtr<IIDArray> idArray;
   HRESULT hr  = idArray.CoCreateInstance(CLSID_IDArray);
   if (FAILED(hr)) return hr;

   const auto& vID = m_Model->GetCubicSpline(id);
   idArray->Reserve(vID.size());
   for (const auto& id : vID)
   {
      idArray->Add(id);
   }

   return idArray.CopyTo(ppIDs);
}

STDMETHODIMP CCogoModel::GetCubicSplineByIndex(IndexType index, IDType* pID, IIDArray** ppIDs)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetCubicSplines(), index)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetCubicSplineByID(id,ppIDs);
}

STDMETHODIMP CCogoModel::CreateCubicSplineByID(IDType id, ICubicSpline** ppCurve)
{
   CHECK_RETOBJ(ppCurve);
   HRESULT hr = S_OK;
   try
   {
      auto spline = m_Model->CreateCubicSpline(id);
      hr = cogoUtil::CreateCubicSpline(spline, ppCurve);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreateCubicSplineByIndex(IndexType index, ICubicSpline** ppCurve)
{
   IDType id;
   if ((id = GetID(m_Model->GetCubicSplines(), index)) == INVALID_ID) return E_INVALIDARG;
   return CreateCubicSplineByID(id, ppCurve);
}

STDMETHODIMP CCogoModel::RemoveCubicSplineByID(IDType id)
{
   return m_Model->RemoveCubicSpline(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemoveCubicSplineByIndex(IndexType index)
{
   IDType id;
   if ((id = GetID(m_Model->GetCubicSplines(), index)) == INVALID_ID) return E_INVALIDARG;
   return RemoveCubicSplineByID(id);
}

STDMETHODIMP CCogoModel::ClearCubicSplines()
{
   m_Model->ClearCubicSplines();
   return S_OK;
}

STDMETHODIMP CCogoModel::StoreAlignment(IDType id)
{
   return m_Model->StoreAlignment(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetAlignmentCount(IndexType* nAlignments)
{
   CHECK_RETVAL(nAlignments);
   *nAlignments = m_Model->GetAlignments().size();
   return S_OK;
}

STDMETHODIMP CCogoModel::AddPathElementToAlignmentByID(IDType alignemntID, PathElementType elementType, IDType elementID)
{
   return m_Model->AppendElementToAlignment(alignemntID, WBFL::COGO::Model::PathElementType(elementType), elementID) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::AddPathElementToAlignmentByIndex(IndexType alignmentIndex, PathElementType elementType, IDType elementID)
{
   IDType id;
   if ((id = GetID(m_Model->GetAlignments(), alignmentIndex)) == INVALID_ID) return E_INVALIDARG;
   return AddPathElementToAlignmentByID(id, elementType, elementID);
}

STDMETHODIMP CCogoModel::GetAlignmentPathElementCountByID(IDType alignmentID, IndexType* nElements)
{
   CHECK_RETVAL(nElements);
   HRESULT hr = S_OK;
   try
   {
      const auto& vAlignmentElements = m_Model->GetAlignment(alignmentID);
      *nElements = vAlignmentElements.size();
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetAlignmentPathElementCountByIndex(IndexType alignmentIndex, IndexType* nElements)
{
   IDType id;
   if ((id = GetID(m_Model->GetAlignments(), alignmentIndex)) == INVALID_ID) return E_INVALIDARG;
   return GetAlignmentPathElementCountByID(id, nElements);
}

STDMETHODIMP CCogoModel::GetAlignmentPathElementByID(IDType alignmentID, IndexType elementIndex, PathElementType* pType, IDType* pElementID)
{
   CHECK_RETVAL(pType);
   CHECK_RETVAL(pElementID);
   HRESULT hr = S_OK;
   try
   {
      const auto& vAlignmentElements = m_Model->GetAlignment(alignmentID);
      if (vAlignmentElements.size() <= elementIndex)
      {
         hr = E_INVALIDARG;
      }
      else
      {
         const auto& [type,id] = vAlignmentElements[elementIndex];
         *pType = PathElementType(type);
         *pElementID = id;
         hr = S_OK;
      }
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetAlignmentPathElementByIndex(IndexType alignmentIndex, IndexType elementIndex, IDType* pID,PathElementType* pType, IDType* pElementID)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetAlignments(), alignmentIndex)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetAlignmentPathElementByID(id, elementIndex, pType, pElementID);
}

STDMETHODIMP CCogoModel::GetAlignmentID(IndexType alignmentIndex, IDType* pID)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetAlignments(), alignmentIndex)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return S_OK;
}

STDMETHODIMP CCogoModel::CreateAlignmentByID(IDType id, IAlignment** ppAlignment)
{
   CHECK_RETOBJ(ppAlignment);
   HRESULT hr = S_OK;
   try
   {
      auto alignment = m_Model->CreateAlignment(id);
      hr = cogoUtil::CreateAlignment(alignment, ppAlignment);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreateAlignmentByIndex(IndexType alignmentIndex, IAlignment** ppAlignment)
{
   IDType id;
   if ((id = GetID(m_Model->GetAlignments(), alignmentIndex)) == INVALID_ID) return E_INVALIDARG;
   return CreateAlignmentByID(id, ppAlignment);
}

STDMETHODIMP CCogoModel::RemoveAlignmentByID(IDType id)
{
   return m_Model->RemoveAlignment(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemoveAlignmentByIndex(IndexType index)
{
   IDType id;
   if ((id = GetID(m_Model->GetAlignments(), index)) == INVALID_ID) return E_INVALIDARG;
   return RemoveAlignmentByID(id);
}

STDMETHODIMP CCogoModel::ClearAlignments()
{
   m_Model->ClearAlignments();
   return S_OK;
}

STDMETHODIMP CCogoModel::SetAlignmentReferenceStation(IDType alignmentID, VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;
   return m_Model->SetAlignmentReferenceStation(alignmentID, station) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemoveAlignmentReferenceStation(IDType alignmentID)
{
   return m_Model->RemoveAlignmentReferenceStation(alignmentID) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetAlignmentReferenceStation(IDType alignmentID, IStation** ppStation)
{
   CHECK_RETOBJ(ppStation);
   HRESULT hr = S_OK;
   try
   {
      hr = cogoUtil::CreateStation(m_Model->GetAlignmentReferenceStation(alignmentID), ppStation);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::AddStationEquation(IDType alignmentID, Float64 back, Float64 ahead)
{
   return m_Model->AddStationEquation(alignmentID, back, ahead) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetStationEquationCount(IDType alignmentID, IndexType* nEquations)
{
   CHECK_RETVAL(nEquations);
   *nEquations = m_Model->GetStationEquations(alignmentID).size();
   return S_OK;
}

STDMETHODIMP CCogoModel::GetStationEquation(IDType alignmentID, IndexType equationIndex, Float64* pBack, Float64* pAhead)
{
   CHECK_RETVAL(pBack);
   CHECK_RETVAL(pAhead);
   const auto& equations = m_Model->GetStationEquations(alignmentID);
   if (equations.size() <= equationIndex) return E_INVALIDARG;
   const auto& [back,ahead] = equations[equationIndex];
   *pBack = back;
   *pAhead = ahead;
   return S_OK;
}

STDMETHODIMP CCogoModel::ClearStationEquations()
{
   m_Model->ClearStationEquations();
   return S_OK;
}

STDMETHODIMP CCogoModel::StorePath(IDType id)
{
   return m_Model->StorePath(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetPathCount(IndexType* nPaths)
{
   CHECK_RETVAL(nPaths);
   *nPaths = m_Model->GetPaths().size();
   return S_OK;
}

STDMETHODIMP CCogoModel::AddPathElementToPathByID(IDType pathID, PathElementType elementType, IDType elementID)
{
   return m_Model->AppendElementToPath(pathID, WBFL::COGO::Model::PathElementType(elementType), elementID) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::AddPathElementToPathByIndex(IndexType pathIndex, PathElementType elementType, IDType elementID)
{
   IDType id;
   if ((id = GetID(m_Model->GetPaths(), pathIndex)) == INVALID_ID) return E_INVALIDARG;
   return AddPathElementToPathByID(id, elementType, elementID);
}

STDMETHODIMP CCogoModel::GetPathElementCountByID(IDType id, IndexType* nElements)
{
   CHECK_RETVAL(nElements);
   HRESULT hr = S_OK;
   try
   {
      const auto& vPathElements = m_Model->GetPath(id);
      *nElements = vPathElements.size();
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetPathElementCountByIndex(IndexType index, IndexType* nElements)
{
   IDType id;
   if ((id = GetID(m_Model->GetPaths(), index)) == INVALID_ID) return E_INVALIDARG;
   return GetPathElementCountByID(id, nElements);
}

STDMETHODIMP CCogoModel::GetPathElementByID(IDType pathID, IndexType elementIndex, PathElementType* pType, IDType* pElementID)
{
   CHECK_RETVAL(pType);
   CHECK_RETVAL(pElementID);
   HRESULT hr = S_OK;
   try
   {
      const auto& vPathElements = m_Model->GetPath(pathID);
      if (vPathElements.size() <= elementIndex)
      {
         hr = E_INVALIDARG;
      }
      else
      {
         const auto& [type,id] = vPathElements[elementIndex];
         *pType = PathElementType(type);
         *pElementID = id;
         hr = S_OK;
      }
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetPathElementByIndex(IndexType pathIndex, IndexType elementIndex, IDType* pID, PathElementType* pType, IDType* pElementID)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetPaths(), pathIndex)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetPathElementByID(id, elementIndex, pType, pElementID);
}

STDMETHODIMP CCogoModel::GetPathID(IndexType pathIndex, IDType* pID)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetPaths(), pathIndex)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return S_OK;
}

STDMETHODIMP CCogoModel::CreatePathByID(IDType id, IPath** ppPath)
{
   CHECK_RETOBJ(ppPath);
   HRESULT hr = S_OK;
   try
   {
      auto path = m_Model->CreatePath(id);
      hr = cogoUtil::CreatePath(path, ppPath);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreatePathByIndex(IndexType pathIndex, IPath** ppPath)
{
   IDType id;
   if ((id = GetID(m_Model->GetPaths(), pathIndex)) == INVALID_ID) return E_INVALIDARG;
   return CreatePathByID(id, ppPath);
}

STDMETHODIMP CCogoModel::RemovePathByID(IDType id)
{
   return m_Model->RemovePath(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemovePathByIndex(IndexType pathIndex)
{
   IDType id;
   if ((id = GetID(m_Model->GetPaths(), pathIndex)) == INVALID_ID) return E_INVALIDARG;
   return RemovePathByID(id);
}

STDMETHODIMP CCogoModel::ClearPaths()
{
   m_Model->ClearPaths();
   return S_OK;
}

STDMETHODIMP CCogoModel::StoreProfilePoint(IDType id, VARIANT varStation, Float64 elevation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;
   return m_Model->StoreProfilePoint(id, station, elevation) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::StoreProfilePointEx(IDType id, IProfilePoint* pPoint)
{
   auto point = cogoUtil::GetProfilePoint(pPoint);
   return m_Model->StoreProfilePoint(id, point) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetProfilePointCount(IndexType* nPoints)
{
   CHECK_RETVAL(nPoints);
   *nPoints = m_Model->GetProfilePoints().size();
   return S_OK;
}

STDMETHODIMP CCogoModel::GetProfilePointByID(IDType id, IProfilePoint** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   HRESULT hr = S_OK;
   try
   {
      const auto& point = m_Model->GetProfilePoint(id);
      hr = cogoUtil::CreateProfilePoint(point, ppPoint);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetProfilePointByIndex(IndexType index, IDType* pID, IProfilePoint** ppPoint)
{
   IDType id;
   if ((id = GetID(m_Model->GetProfilePoints(), index)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetProfilePointByID(*pID, ppPoint);
}

STDMETHODIMP CCogoModel::RemoveProfilePointByID(IDType id)
{
   return m_Model->RemoveProfilePoint(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemoveProfilePointByIndex(IndexType index)
{
   IDType id;
   if ((id = GetID(m_Model->GetProfilePoints(), index)) == INVALID_ID) return E_INVALIDARG;
   return RemoveProfilePointByID(id);
}

STDMETHODIMP CCogoModel::ClearProfilePoints()
{
   m_Model->ClearProfilePoints();
   return S_OK;
}

STDMETHODIMP CCogoModel::StoreProfileSegment(IDType id, IDType startID, IDType endID)
{
   return m_Model->StoreProfileSegment(id, startID, endID) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetProfileSegmentCount(IndexType* nSegments)
{
   CHECK_RETVAL(nSegments);
   *nSegments = m_Model->GetProfileSegments().size();
   return S_OK;
}

STDMETHODIMP CCogoModel::GetProfileSegmentByID(IDType id, IDType* pStartID, IDType* pEndID)
{
   CHECK_RETVAL(pStartID);
   CHECK_RETVAL(pEndID);

   HRESULT hr = S_OK;
   try
   {
      const auto& definition = m_Model->GetProfileSegment(id);
      *pStartID = definition.startID;
      *pEndID = definition.endID;
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return S_OK;
}

STDMETHODIMP CCogoModel::GetProfileSegmentByIndex(IndexType index, IDType* pID, IDType* pStartID, IDType* pEndID)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetProfileSegments(), index)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetProfileSegmentByID(id, pStartID, pEndID);
}

STDMETHODIMP CCogoModel::CreateProfileSegmentByID(IDType id, IProfileSegment** ppSegment)
{
   CHECK_RETOBJ(ppSegment);
   HRESULT hr = S_OK;
   try
   {
      auto profile_segment = m_Model->CreateProfileSegment(id);
      hr = cogoUtil::CreateProfileSegment(profile_segment, ppSegment);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreateProfileSegmentByIndex(IndexType index, IProfileSegment** ppSegment)
{
   IDType id;
   if ((id = GetID(m_Model->GetProfileSegments(), index)) == INVALID_ID) return E_INVALIDARG;
   return CreateProfileSegmentByID(id, ppSegment);
}

STDMETHODIMP CCogoModel::RemoveProfileSegmentByID(IDType id)
{
   return m_Model->RemoveProfileSegment(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemoveProfileSegmentByIndex(IndexType index)
{
   IDType id;
   if ((id = GetID(m_Model->GetProfileSegments(), index)) == INVALID_ID) return E_INVALIDARG;
   return RemoveProfileSegmentByID(id);
}

STDMETHODIMP CCogoModel::ClearProfileSegments()
{
   m_Model->ClearProfileSegments();
   return S_OK;
}

STDMETHODIMP CCogoModel::StoreVerticalCurve(IDType id, IDType pbg, IDType pvi, IDType pfg, Float64 l1_or_g1, Float64 l2_or_g2)
{
   return m_Model->StoreVerticalCurve(id, pbg, pvi, pfg, l1_or_g1, l2_or_g2) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetVerticalCurveCount(IndexType* nCurves)
{
   CHECK_RETVAL(nCurves);
   *nCurves = m_Model->GetVerticalCurves().size();
   return S_OK;
}

STDMETHODIMP CCogoModel::GetVerticalCurveByID(IDType id, IDType* pbg, IDType* pvi, IDType* pfg, Float64* l1_or_g1, Float64* l2_or_g2)
{
   CHECK_RETOBJ(pbg);
   CHECK_RETVAL(pvi);
   CHECK_RETVAL(pfg);
   CHECK_RETVAL(l1_or_g1);
   CHECK_RETVAL(l2_or_g2);
   HRESULT hr = S_OK;
   try
   {
      const auto& definition = m_Model->GetVerticalCurve(id);
      *pbg = definition.pbgID;
      *pvi = definition.pviID;
      *pfg = definition.pfgID;
      *l1_or_g1 = definition.l1_or_g1;
      *l2_or_g2 = definition.l2_or_g2;
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetVerticalCurveByIndex(IndexType index, IDType* pID, IDType* pbg, IDType* pvi, IDType* pfg, Float64* l1_or_g1, Float64* l2_or_g2)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetVerticalCurves(), index)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetVerticalCurveByID(id, pbg, pvi, pfg, l1_or_g1, l2_or_g2);
}

STDMETHODIMP CCogoModel::CreateVerticalCurveByID(IDType id, IVerticalCurve** ppVertCurve)
{
   CHECK_RETOBJ(ppVertCurve);
   HRESULT hr = S_OK;
   try
   {
      auto vc = m_Model->CreateVerticalCurve(id);
      hr = cogoUtil::CreateVerticalCurve(vc, ppVertCurve);
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreateVerticalCurveByIndex(IndexType index, IVerticalCurve** ppVertCurve)
{
   IDType id;
   if ((id = GetID(m_Model->GetVerticalCurves(), index)) == INVALID_ID) return E_INVALIDARG;
   return CreateVerticalCurveByID(id, ppVertCurve);
}

STDMETHODIMP CCogoModel::RemoveVerticalCurveByID(IDType id)
{
   return m_Model->RemoveVerticalCurve(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemoveVerticalCurveByIndex(IndexType index)
{
   IDType id;
   if ((id = GetID(m_Model->GetVerticalCurves(), index)) == INVALID_ID) return E_INVALIDARG;
   return RemoveVerticalCurveByID(id);
}

STDMETHODIMP CCogoModel::ClearVerticalCurves()
{
   m_Model->ClearVerticalCurves();
   return S_OK;
}

STDMETHODIMP CCogoModel::StoreProfile(IDType id)
{
   return m_Model->StoreProfile(id);
}

STDMETHODIMP CCogoModel::GetProfileCount(IndexType* nProfiles)
{
   CHECK_RETVAL(nProfiles);
   *nProfiles = m_Model->GetProfiles().size();
   return S_OK;
}

STDMETHODIMP CCogoModel::AddProfileElementByID(IDType profileID, ProfileElementType elementType, IDType elementID)
{
   return m_Model->AppendElementToProfile(profileID, WBFL::COGO::Model::ProfileElementType(elementType), elementID);
}

STDMETHODIMP CCogoModel::AddProfileElementByIndex(IndexType profileIndex, ProfileElementType elementType, IDType elementID)
{
   IDType id;
   if ((id = GetID(m_Model->GetProfiles(), profileIndex)) == INVALID_ID) return E_INVALIDARG;
   return AddProfileElementByID(id, elementType, elementID);
}

STDMETHODIMP CCogoModel::GetProfileElementCountByID(IDType id, IndexType* nElements)
{
   CHECK_RETVAL(nElements);
   HRESULT hr = S_OK;
   try
   {
      const auto& vProfileElements = m_Model->GetProfile(id);
      *nElements = vProfileElements.size();
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetProfileElementCountByIndex(IndexType index, IndexType* nElements)
{
   IDType id;
   if ((id = GetID(m_Model->GetProfiles(), index)) == INVALID_ID) return E_INVALIDARG;
   return GetProfileElementCountByID(id, nElements);
}

STDMETHODIMP CCogoModel::GetProfileElementByID(IDType profileID, IndexType elementIndex, ProfileElementType* pType, IDType* pElementID)
{
   CHECK_RETVAL(pType);
   CHECK_RETVAL(pElementID);
   HRESULT hr = S_OK;
   try
   {
      const auto& vProfileElements = m_Model->GetProfile(profileID);
      if (vProfileElements.size() <= elementIndex)
      {
         hr = E_INVALIDARG;
      }
      else
      {
         const auto& [type,id] = vProfileElements[elementIndex];
         *pType = ProfileElementType(type);
         *pElementID = id;
         hr = S_OK;
      }
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetProfileElementByIndex(IndexType profileIndex, IndexType elementIndex, ProfileElementType* pType, IDType* pElementID)
{
   IDType id;
   if ((id = GetID(m_Model->GetProfiles(), profileIndex)) == INVALID_ID) return E_INVALIDARG;
   return GetProfileElementByID(id, elementIndex, pType, pElementID);
}

STDMETHODIMP CCogoModel::CreateProfileByID(IDType profileID, IProfile** ppProfile)
{
   CHECK_RETOBJ(ppProfile);
   HRESULT hr = S_OK;
   try
   {
      auto profile = m_Model->CreateProfile(profileID);
      hr = cogoUtil::CreateProfile(profile, ppProfile);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreateProfileByIndex(IndexType profileIndex, IProfile** ppProfile)
{
   IDType id;
   if ((id = GetID(m_Model->GetProfiles(), profileIndex)) == INVALID_ID) return E_INVALIDARG;
   return CreateProfileByID(id, ppProfile);
}

STDMETHODIMP CCogoModel::RemoveProfileByID(IDType id)
{
   return m_Model->RemoveProfile(id) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemoveProfileByIndex(IndexType index)
{
   IDType id;
   if ((id = GetID(m_Model->GetProfiles(), index)) == INVALID_ID) return E_INVALIDARG;
   return RemoveProfileByID(id);
}

STDMETHODIMP CCogoModel::ClearProfiles()
{
   m_Model->ClearProfiles();
   return S_OK;
}

STDMETHODIMP CCogoModel::StoreSurface(IDType surfaceID, IndexType nSegments, IndexType alignmentPointIdx, IndexType profilePointIdx)
{
   return m_Model->StoreSurface(surfaceID, nSegments, alignmentPointIdx, profilePointIdx) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::GetSurfaceCount(IndexType* nSurfaces)
{
   CHECK_RETOBJ(nSurfaces);
   *nSurfaces = m_Model->GetSurfaces().size();
   return S_OK;
}

STDMETHODIMP CCogoModel::AddSurfaceTemplate(IDType surfaceID, VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;
   return m_Model->AddSurfaceTemplate(surfaceID, station) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::CopySurfaceTemplateByID(IDType surfaceID, IndexType templateIdx, VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;
   return m_Model->CopySurfaceTemplate(surfaceID, templateIdx, station) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::CopySurfaceTemplateByIndex(IndexType surfaceIndex, IndexType templateIdx, VARIANT varStation)
{
   IDType id;
   if ((id = GetID(m_Model->GetSurfaces(), surfaceIndex)) == INVALID_ID) return E_INVALIDARG;
   return CopySurfaceTemplateByID(id, templateIdx, varStation);
}

STDMETHODIMP CCogoModel::MoveSurfaceTemplateByID(IDType surfaceID, IndexType templateIdx, VARIANT varNewStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varNewStation);
   if (FAILED(hr)) return hr;
   return m_Model->MoveSurfaceTemplate(surfaceID, templateIdx, station);
}

STDMETHODIMP CCogoModel::MoveSurfaceTemplateByIndex(IndexType surfaceIndex, IndexType templateIdx, VARIANT varNewStation)
{
   IDType id;
   if ((id = GetID(m_Model->GetSurfaces(), surfaceIndex)) == INVALID_ID) return E_INVALIDARG;
   return MoveSurfaceTemplateByID(id, templateIdx, varNewStation);
}

STDMETHODIMP CCogoModel::GetSurfaceTemplateCountByID(IDType surfaceID, IndexType* nSurfaceTemplates)
{
   CHECK_RETVAL(nSurfaceTemplates);
   *nSurfaceTemplates = m_Model->GetSurfaceTemplateCount(surfaceID);
   return S_OK;
}

STDMETHODIMP CCogoModel::GetSurfaceTemplateCountByIndex(IndexType surfaceIndex, IDType* pID, IndexType* nSurfaceTemplates)
{
   CHECK_RETVAL(pID);
   IDType id;
   if ((id = GetID(m_Model->GetSurfaces(), surfaceIndex)) == INVALID_ID) return E_INVALIDARG;
   *pID = id;
   return GetSurfaceTemplateCountByID(id, nSurfaceTemplates);
}

STDMETHODIMP CCogoModel::GetSurfaceTemplateLocationByID(IDType surfaceID, IndexType templateIdx, IStation** ppStation)
{
   HRESULT hr = S_OK;
   try
   {
      const auto& station = m_Model->GetSurfaceTemplateLocation(surfaceID,templateIdx);
      hr = cogoUtil::CreateStation(station, ppStation);
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::GetSurfaceTemplateLocationByIndex(IndexType surfaceIndex, IndexType templateIdx, IStation** ppStation)
{
   IDType id;
   if ((id = GetID(m_Model->GetSurfaces(), surfaceIndex)) == INVALID_ID) return E_INVALIDARG;
   return GetSurfaceTemplateLocationByID(id, templateIdx, ppStation);
}

STDMETHODIMP CCogoModel::UpdateSurfaceTemplateSegmentByID(IDType surfaceID, IndexType templateIndex, IndexType segmentIndex, Float64 width, Float64 slope, TemplateSlopeType slopeType)
{
   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->UpdateSurfaceTemplateSegment(surfaceID, templateIndex, segmentIndex, width, slope, WBFL::COGO::SurfaceTemplateSegment::SlopeType(slopeType)) ? S_OK : E_INVALIDARG;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::UpdateSurfaceTemplateSegmentByIndex(IndexType surfaceIndex, IndexType templateIndex, IndexType segmentIndex, Float64 width, Float64 slope, TemplateSlopeType slopeType)
{
   IDType id;
   if ((id = GetID(m_Model->GetSurfaces(), surfaceIndex)) == INVALID_ID) return E_INVALIDARG;
   return UpdateSurfaceTemplateSegmentByID(id, templateIndex, surfaceIndex, width, slope, slopeType);
}

STDMETHODIMP CCogoModel::RemoveSurfaceByID(IDType surfaceID)
{
   return m_Model->RemoveSurface(surfaceID) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::RemoveSurfaceByIndex(IndexType surfaceIndex)
{
   IDType id;
   if ((id = GetID(m_Model->GetSurfaces(), surfaceIndex)) == INVALID_ID) return E_INVALIDARG;
   return RemoveSurfaceByID(id);
}

STDMETHODIMP CCogoModel::StoreSuperelevationByID(IDType surfaceID, VARIANT varBeginTransitionStation, VARIANT varBeginFullSuperStation, VARIANT varEndFullSuperStation, VARIANT varEndTransitionStation, Float64 rate, IndexType pivotPointIdx, SuperTransitionType beginTransitionType, Float64 beginL1, Float64 beginL2, SuperTransitionType endTransitionType, Float64 endL1, Float64 endL2)
{
   HRESULT hr;
   WBFL::COGO::Station beginTransitionStation, beginFullSuperStation, endFullSuperStation, endTransitionStation;
   std::tie(hr, beginTransitionStation) = cogoUtil::StationFromVariant(varBeginTransitionStation);
   if (FAILED(hr)) return hr;

   std::tie(hr, beginFullSuperStation) = cogoUtil::StationFromVariant(varBeginFullSuperStation);
   if (FAILED(hr)) return hr;

   std::tie(hr, endFullSuperStation) = cogoUtil::StationFromVariant(varEndFullSuperStation);
   if (FAILED(hr)) return hr;

   std::tie(hr, endTransitionStation) = cogoUtil::StationFromVariant(varEndTransitionStation);
   if (FAILED(hr)) return hr;

   return m_Model->StoreSuperelevation(surfaceID, beginTransitionStation, beginFullSuperStation, endFullSuperStation, endTransitionStation, rate, pivotPointIdx,
      WBFL::COGO::Superelevation::TransitionType(beginTransitionType), beginL1, beginL2, WBFL::COGO::Superelevation::TransitionType(endTransitionType), endL1, endL2) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::StoreSuperelevationByIndex(IndexType surfaceIndex, VARIANT varBeginTransitionStation, VARIANT varBeginFullSuperStation, VARIANT varEndFullSuperStation, VARIANT varEndTransitionStation, Float64 rate, IndexType pivotPointIdx, SuperTransitionType beginTransitionType, Float64 beginL1, Float64 beginL2, SuperTransitionType endTransitionType, Float64 endL1, Float64 endL2)
{
   IDType id;
   if ((id = GetID(m_Model->GetSurfaces(), surfaceIndex)) == INVALID_ID) return E_INVALIDARG;
   return StoreSuperelevationByID(id, varBeginTransitionStation, varBeginFullSuperStation, varEndFullSuperStation, varEndTransitionStation, rate, pivotPointIdx, beginTransitionType, beginL1, beginL2, endTransitionType, endL1, endL2);
}

STDMETHODIMP CCogoModel::StoreWideningByID(IDType surfaceID, VARIANT varBeginTransitionStation, VARIANT varBeginFullWidening, VARIANT varEndFullWidening, VARIANT varEndTransitionStation, Float64 widening, IndexType segment1, IndexType segment2)
{
   HRESULT hr;
   WBFL::COGO::Station beginTransitionStation, beginFullWidening, endFullWidening, endTransitionStation;
   std::tie(hr, beginTransitionStation) = cogoUtil::StationFromVariant(varBeginTransitionStation);
   if (FAILED(hr)) return hr;

   std::tie(hr, beginFullWidening) = cogoUtil::StationFromVariant(varBeginFullWidening);
   if (FAILED(hr)) return hr;

   std::tie(hr, endFullWidening) = cogoUtil::StationFromVariant(varEndFullWidening);
   if (FAILED(hr)) return hr;

   std::tie(hr, endTransitionStation) = cogoUtil::StationFromVariant(varEndTransitionStation);
   if (FAILED(hr)) return hr;

   return m_Model->StoreWidening(surfaceID, beginTransitionStation, beginFullWidening, endFullWidening, endTransitionStation, widening, segment1, segment2) ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CCogoModel::StoreWideningByIndex(IndexType surfaceIndex, VARIANT varBeginTransitionStation, VARIANT varBeginFullWidening, VARIANT varEndFullWidening, VARIANT varEndTransitionStation, Float64 widening, IndexType segment1, IndexType segment2)
{
   IDType id;
   if ((id = GetID(m_Model->GetSurfaces(), surfaceIndex)) == INVALID_ID) return E_INVALIDARG;
   return StoreWideningByID(id, varBeginTransitionStation, varBeginFullWidening, varEndFullWidening, varEndTransitionStation, widening, segment1, segment2);
}

STDMETHODIMP CCogoModel::CreateSurfaceByID(IDType surfaceID, ISurface** ppSurface)
{
   HRESULT hr = S_OK;
   try
   {
      auto surface = m_Model->CreateSurface(surfaceID);
      hr = cogoUtil::CreateSurface(surface, ppSurface);
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CreateSurfaceByIndex(IndexType surfaceIndex, ISurface** ppSurface)
{
   IDType id;
   if ((id = GetID(m_Model->GetSurfaces(), surfaceIndex)) == INVALID_ID) return E_INVALIDARG;
   return CreateSurfaceByID(id, ppSurface);
}

STDMETHODIMP CCogoModel::AttachProfileToAlignment(IDType profileID, IDType alignmentID)
{
   m_Model->AttachProfileToAlignment(profileID, alignmentID);
   return S_OK;
}

STDMETHODIMP CCogoModel::AttachSurfaceToProfile(IDType surfaceID, IDType profileID)
{
   m_Model->AttachSurfaceToProfile(surfaceID, profileID);
   return S_OK;
}

STDMETHODIMP CCogoModel::Clear()
{
   m_Model->Clear();
   return S_OK;
}

STDMETHODIMP CCogoModel::get_Engine(ICogoEngine** ppEngine)
{
   CHECK_RETOBJ(ppEngine);
   return m_Engine.CopyTo(ppEngine);
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

///////////////////////////////////////////////////////
// IMeasure
STDMETHODIMP CCogoModel::Angle(IDType fromID, IDType vertexID, IDType toID, IAngle** angle)
{
   CHECK_RETOBJ(angle);
   HRESULT hr;
   try
   {
      hr = cogoUtil::CreateAngle(m_Model->MeasureAngle(fromID, vertexID, toID), angle);
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::Area(VARIANT IDs,Float64* area)
{
   CHECK_RETVAL(area);

   if ( IDs.vt != (VT_BYREF | VT_VARIANT) &&  // VB Script
        IDs.vt != (VT_ARRAY | VT_I2)      &&  // VB/C++
        IDs.vt != (VT_ARRAY | VT_I4) )        // VB/C++
   {
      return E_INVALIDARG;
   }

   // Extract the SAFEARRAY
   SAFEARRAY* pIDs;
   if ( IDs.vt & VT_BYREF )
   {
      if ( !(IDs.pvarVal->vt & (VT_BYREF | VT_ARRAY)) )
         return E_INVALIDARG;

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
      return E_INVALIDARG;

   if ( IDs.vt & VT_ARRAY && vt != VT_I4 && vt != VT_I2 )
      return E_INVALIDARG;

   // Make sure this is a 1 dimensional array
   if ( SafeArrayGetDim(pIDs) != 1 )
      return E_INVALIDARG;

   // Need a container to hold the points
   std::vector<IDType> vIDs;

   // Get the array bounds, loop over the array,
   // find the specified points, and build up the polyshape
   long lb,ub;
   SafeArrayGetLBound(pIDs,1,&lb);
   SafeArrayGetUBound(pIDs,1,&ub);
   if ( (ub - lb + 1) < 3 )
   {
      // Must consist of at least 3 points
      return E_INVALIDARG;
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

      vIDs.push_back(ID);
   }

   try
   {
      *area = m_Model->MeasureArea(vIDs);
   }
   catch (...)
   {
      return E_FAIL;
   }

   return S_OK;
}

STDMETHODIMP CCogoModel::Distance(IDType fromID, IDType toID, Float64* dist)
{
   CHECK_RETVAL(dist);
   try
   {
      *dist = m_Model->MeasureDistance(fromID, toID);
   }
   catch (...)
   {
      return E_FAIL;
   }
   return S_OK;
}

STDMETHODIMP CCogoModel::Direction(IDType fromID, IDType toID, IDirection** dir)
{
   CHECK_RETOBJ(dir);
   HRESULT hr;
   try
   {
      hr = cogoUtil::CreateDirection(m_Model->MeasureDirection(fromID, toID), dir);
   }
   catch (...)
   {
      hr = E_FAIL;
   }
   return hr;
}

STDMETHODIMP CCogoModel::Inverse(IDType fromID,IDType toID, Float64* dist, IDirection** dir)
{
   CHECK_RETOBJ(dir);
   WBFL::COGO::Direction direction;
   std::tie(*dist, direction) = m_Model->ComputeInverse(fromID, toID);
   return cogoUtil::CreateDirection(direction, dir);
}

///////////////////////////////////////////////////////
// ILocate
STDMETHODIMP CCogoModel::ByDistAngle(IDType newID,IDType fromID,IDType toID,Float64 dist,VARIANT varAngle,Float64 offset)
{
   auto [hr, angle] = cogoUtil::AngleFromVariant(varAngle);
   if (FAILED(hr)) return hr;
   try
   {
      bool bResult = m_Model->LocateByDistanceAndAngle(newID, fromID, toID, dist, angle, offset);
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }

   return hr;
}

STDMETHODIMP CCogoModel::ByDistDefAngle(IDType newID,IDType fromID,IDType toID,Float64 dist,VARIANT varDefAngle,Float64 offset)
{
   auto [hr, defAngle] = cogoUtil::AngleFromVariant(varDefAngle);
   if (FAILED(hr)) return hr;
   try
   {
      bool bResult = m_Model->LocateByDistanceAndDeflectionAngle(newID, fromID, toID, dist, defAngle, offset);
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }

   return hr;
}

STDMETHODIMP CCogoModel::ByDistDir(IDType newID,IDType fromID,Float64 dist,VARIANT varDir,Float64 offset)
{
   auto [hr, dir] = cogoUtil::DirectionFromVariant(varDir);
   if (FAILED(hr)) return hr;
  
   try
   {
      bool bResult = m_Model->LocateByDistanceAndDirection(newID, fromID, dist, dir, offset);
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::PointOnLine(IDType newID, IDType fromID, IDType toID, Float64 dist, Float64 offset)
{
   m_Model->LocatePointOnLine(newID, fromID, toID, dist, offset);
   return S_OK;
}

STDMETHODIMP CCogoModel::ParallelLineByPoints(IDType newFromID, IDType newToID, IDType fromID, IDType toID, Float64 offset)
{
   HRESULT hr;
   try
   {
      bool bResult = m_Model->LocateParallelLineByPoints(newFromID, newToID, fromID, toID, offset);
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::ParallelLineSegment(IDType newLineID, IDType newFromID, IDType newToID, IDType lineID, Float64 offset)
{
   HRESULT hr = S_OK;
   try
   {
      bool bResult = m_Model->LocateParallelLineSegment(newLineID, newFromID, newToID, lineID, offset);
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

////////////////////////////////////////////////////////
// IIntersect
STDMETHODIMP CCogoModel::Bearings(IDType newID, IDType id1, VARIANT varDir1, Float64 offset1, IDType id2, VARIANT varDir2, Float64 offset2, VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);
   HRESULT hr = S_OK;
   WBFL::COGO::Direction dir1, dir2;
   
   std::tie(hr, dir1) = cogoUtil::DirectionFromVariant(varDir1);
   if (FAILED(hr)) return hr;

   std::tie(hr, dir2) = cogoUtil::DirectionFromVariant(varDir2);
   if (FAILED(hr)) return hr;

   try
   {
      bool bResult = m_Model->IntersectBearings(newID, id1, dir1, offset1, id2, dir2, offset2);
      *bFound = bResult ? VARIANT_TRUE : VARIANT_FALSE;
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::BearingCircle(IDType newID, IDType id1, VARIANT varDir, Float64 offset, IDType idc, Float64 radius, IDType idNearest, VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   if (radius <= 0.0)
      return E_INVALIDARG;

   auto [hr, dir] = cogoUtil::DirectionFromVariant(varDir);
   if (FAILED(hr)) return hr;
   try
   {
      bool bResult = m_Model->IntersectBearingAndCircle(newID, id1, dir, offset, idc, radius, idNearest);
      *bFound = bResult ? VARIANT_TRUE : VARIANT_FALSE;
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::Circles(IDType newID, IDType id1, Float64 r1, IDType id2, Float64 r2, IDType idNearest, VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   if ( r1 <= 0.0 || r2 <= 0.0 )
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      bool bResult = m_Model->IntersectCircles(newID, id1, r1, id2, r2, idNearest);
      *bFound = bResult ? VARIANT_TRUE : VARIANT_FALSE;
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::LineByPointsCircle(IDType newID, IDType id1, IDType id2, Float64 offset, IDType idc, Float64 radius, IDType idNearest, VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   if ( radius <= 0.0 )
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      bool bResult = m_Model->IntersectLineByPointsAndCircle(newID, id1, id2, offset, idc, radius, idNearest);
      *bFound = bResult ? VARIANT_TRUE : VARIANT_FALSE;
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::LinesByPoints(IDType newID, IDType id11, IDType id12, Float64 offset1, IDType id21, IDType id22, Float64 offset2, VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   HRESULT hr = S_OK;
   try
   {
      bool bResult = m_Model->IntersectLinesByPoints(newID, id11, id12, offset1, id21, id22, offset2);
      *bFound = bResult ? VARIANT_TRUE : VARIANT_FALSE;
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::Lines(IDType newID,IDType id1,Float64 offset1,IDType id2,Float64 offset2,VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   HRESULT hr = S_OK;
   try
   {
      bool bResult = m_Model->IntersectPathSegments(newID, id1, offset1, id2, offset2);
      *bFound = bResult ? VARIANT_TRUE : VARIANT_FALSE;
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::LineSegmentCircle(IDType newID,IDType lineID,Float64 offset,IDType idc,Float64 radius,IDType idNearest,VARIANT_BOOL* bFound)
{
   CHECK_RETVAL(bFound);

   if (radius <= 0)
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      bool bResult = m_Model->IntersectPathSegmentAndCircle(newID, lineID, offset, idc, radius, idNearest);
      *bFound = bResult ? VARIANT_TRUE : VARIANT_FALSE;
      hr = bResult ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

////////////////////////////////////////////////////////
// IProject
STDMETHODIMP CCogoModel::PointOnLineByPoints(IDType newID, IDType fromID, IDType startID, IDType endID, Float64 offset)
{
   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->ProjectPointOnLineByPoints(newID, fromID, startID, endID, offset) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::PointOnLineSegment(IDType newID, IDType fromID, IDType lineID, Float64 offset)
{
   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->ProjectPointOnPathSegment(newID, fromID, lineID, offset) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::PointOnCurve(IDType newID, IDType fromID, IDType curveID)
{
   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->ProjectPointOnCompoundCurve(newID, fromID, curveID) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

////////////////////////////////////////////////////////
// IDivide
STDMETHODIMP CCogoModel::Arc(IDType firstID, IDType idInc, IDType fromID, IDType vertexID, IDType toID, IndexType nParts)
{
   if ( nParts <= 1 || nParts == INVALID_INDEX )
      return E_INVALIDARG;

   if ( idInc == 0 )
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->DivideArc(firstID, idInc, fromID, vertexID, toID, nParts) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::BetweenPoints(IDType firstID, IDType idInc, IDType fromID, IDType toID, IndexType nParts)
{
   if ( nParts <= 1 || nParts == INVALID_INDEX )
      return E_INVALIDARG;

   if ( idInc == 0 )
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->DivideBetweenPoints(firstID, idInc, fromID, toID, nParts) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::LineSegment(IDType firstID, IDType idInc, IDType lineID, IndexType nParts)
{
   if ( nParts <= 1 || nParts == INVALID_INDEX )
      return E_INVALIDARG;

   if ( idInc == 0 )
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->DivideLineSegment(firstID, idInc, lineID, nParts) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::CompoundCurve(IDType firstID, IDType idInc, IDType curveID, IndexType nParts)
{
   if ( nParts <= 1 || nParts == INVALID_INDEX)
      return E_INVALIDARG;

   if ( idInc == 0 )
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->DivideCompoundCurve(firstID, idInc, curveID, nParts) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::Path(IDType firstID,IDType idInc,IDType pathID,IndexType nParts,Float64 start,Float64 end)
{
   if ( nParts <= 1 || nParts == INVALID_INDEX)
      return E_INVALIDARG;

   if ( idInc == 0 )
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->DividePath(firstID, idInc, pathID, nParts, start, end) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

////////////////////////////////////////////////////////
// ITangent
STDMETHODIMP CCogoModel::Cross(IDType newID1, IDType idCenter1, Float64 radius1, IDType newID2, IDType idCenter2, Float64 radius2, TangentSignType sign)
{
   // Check the radii
   if ( radius1 <= 0.0 )
      return E_INVALIDARG;

   if ( radius2 <= 0.0 )
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->CrossingTangents(newID1, idCenter1, radius1, newID2, idCenter2, radius2, WBFL::COGO::TangentSign(sign)) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::External(IDType newID1, IDType idCenter1, Float64 radius1, IDType newID2, IDType idCenter2, Float64 radius2, TangentSignType sign)
{
   // Check the radii
   if ( radius1 <= 0.0 )
      return E_INVALIDARG;

   if ( radius2 <= 0.0 )
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->ExternalTangents(newID1, idCenter1, radius1, newID2, idCenter2, radius2, WBFL::COGO::TangentSign(sign)) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}

STDMETHODIMP CCogoModel::Point(IDType newID, IDType idCenter, Float64 radius,IDType pointID,TangentSignType sign)
{
   // Check the radius
   if ( radius <= 0.0 )
      return E_INVALIDARG;

   HRESULT hr = S_OK;
   try
   {
      hr = m_Model->TangentPoint(newID, idCenter, radius, pointID, WBFL::COGO::TangentSign(sign)) ? S_OK : S_FALSE;
   }
   catch (...)
   {
      hr = E_INVALIDARG;
   }
   return hr;
}
