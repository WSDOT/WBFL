///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
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

// PrecastGirder.cpp : Implementation of CPrecastGirder
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "PrecastGirder.h"
#include <MathEx.h>


// CPrecastGirder
HRESULT CPrecastGirder::FinalConstruct()
{
   m_UpdateLengths = true;

   return S_OK;
}

void CPrecastGirder::FinalRelease()
{
}

STDMETHODIMP CPrecastGirder::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPrecastGirder
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPrecastGirder::Initialize(ISuperstructureMemberSegment* segment)
{
   CHECK_IN(segment);

   m_pSegment = segment;

   // ALSO DO THIS WHEN WE SET THE STRAND MODEL OBJECT
   if (m_StrandModel)
   {
      m_StrandModel->Initialize(m_pSegment,this);
   }

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_SpanLength(Float64* length)
{
   CHECK_RETVAL(length);

   DoUpdateLengths();

   *length = m_Lengths.dbSpanLength;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_GirderLength(Float64* length)
{
   CHECK_RETVAL(length);

   DoUpdateLengths();

   *length = m_Lengths.dbGirderLength;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_LeftEndDistance(Float64* size)
{
   CHECK_RETVAL(size);

   DoUpdateLengths();

   *size = m_Lengths.dbLeftEndDistance;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_RightEndDistance(Float64* size)
{
   CHECK_RETVAL(size);

   DoUpdateLengths();

   *size = m_Lengths.dbRightEndDistance;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_LeftBearingOffset(Float64* offset)
{
   CHECK_RETVAL(offset);

   DoUpdateLengths();

   *offset = m_Lengths.dbLeftBearingOffset;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_RightBearingOffset(Float64* offset)
{
   CHECK_RETVAL(offset);

   DoUpdateLengths();

   *offset = m_Lengths.dbRightBearingOffset;

   return S_OK;
}

STDMETHODIMP CPrecastGirder::GetEndPoints(IPoint2d** pntPier1,IPoint2d** pntEnd1,IPoint2d** pntBrg1,IPoint2d** pntBrg2,IPoint2d** pntEnd2,IPoint2d** pntPier2)
{
   CComPtr<IGirderLine> girderLine;
   m_pSegment->get_GirderLine(&girderLine);

   return girderLine->GetEndPoints(pntPier1,pntEnd1,pntBrg1,pntBrg2,pntEnd2,pntPier2);
}

STDMETHODIMP CPrecastGirder::get_SuperstructureMemberSegment(ISuperstructureMemberSegment** segment)
{
   CHECK_RETOBJ(segment);
   (*segment) = m_pSegment;
   if ( m_pSegment )
   {
      (*segment)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CPrecastGirder::putref_StrandModel(IStrandModel* pStrandModel)
{
   CHECK_IN(pStrandModel);
   m_StrandModel = pStrandModel;
   m_StrandModel->Initialize(m_pSegment, this);
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_StrandModel(IStrandModel** ppStrandModel)
{
   CHECK_RETOBJ(ppStrandModel);
   *ppStrandModel = nullptr;
   if (m_StrandModel)
   {
      m_StrandModel.CopyTo(ppStrandModel);
   }
   return S_OK;
}

STDMETHODIMP CPrecastGirder::putref_Tendons(ITendonCollection* pTendons)
{
   CHECK_IN(pTendons);
   m_Tendons = pTendons;
   IndexType nTendons;
   m_Tendons->get_Count(&nTendons);
   for (IndexType idx = 0; idx < nTendons; idx++)
   {
      CComPtr<ITendon> tendon;
      m_Tendons->get_Item(idx, &tendon);
      tendon->putref_SuperstructureMemberSegment(m_pSegment);
   }
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_Tendons(ITendonCollection** ppTendons)
{
   CHECK_RETOBJ(ppTendons);
   *ppTendons = nullptr;
   return m_Tendons.CopyTo(ppTendons);
}

STDMETHODIMP CPrecastGirder::get_RebarLayout(IRebarLayout** rebarLayout)
{
   CHECK_RETOBJ(rebarLayout);

   if ( m_RebarLayout == nullptr )
   {
      HRESULT hr = m_RebarLayout.CoCreateInstance(CLSID_RebarLayout);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   (*rebarLayout) = m_RebarLayout;
   (*rebarLayout)->AddRef();
   return S_OK;
}

STDMETHODIMP CPrecastGirder::get_ClosureJointRebarLayout(IRebarLayout** rebarLayout)
{
   CHECK_RETOBJ(rebarLayout);

   if ( m_ClosureJointRebarLayout == nullptr )
   {
      HRESULT hr = m_ClosureJointRebarLayout.CoCreateInstance(CLSID_RebarLayout);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   (*rebarLayout) = m_ClosureJointRebarLayout;
   (*rebarLayout)->AddRef();
   return S_OK;
}

void CPrecastGirder::DoUpdateLengths()
{
   if (m_UpdateLengths)
   {
      CComPtr<IPoint2d> pntPier1, pntEnd1, pntBrg1;
      CComPtr<IPoint2d> pntPier2, pntEnd2, pntBrg2;
      GetEndPoints(&pntPier1,&pntEnd1,&pntBrg1,&pntBrg2,&pntEnd2,&pntPier2);

      pntEnd1->DistanceEx(pntEnd2,&m_Lengths.dbGirderLength);
      pntBrg1->DistanceEx(pntBrg2,&m_Lengths.dbSpanLength);

      pntPier1->DistanceEx(pntBrg1,&m_Lengths.dbLeftBearingOffset);
      pntPier2->DistanceEx(pntBrg2,&m_Lengths.dbRightBearingOffset);

      pntEnd1->DistanceEx(pntBrg1,&m_Lengths.dbLeftEndDistance);
      pntEnd2->DistanceEx(pntBrg2,&m_Lengths.dbRightEndDistance);

      CComPtr<ICogoEngine> cogoEngine;
      cogoEngine.CoCreateInstance(CLSID_CogoEngine);
      CComPtr<IMeasure2> measure;
      cogoEngine->get_Measure(&measure);

      CComPtr<IDirection> direction; // direction from end to pier point
      Float64 offset; // this is always a positive value because it is a distance
      measure->Inverse(pntPier1,pntBrg1,&offset,&direction);
      if ( !IsZero(offset) )
      {
         // need to determine if the intersection with the pier line is before or after the
         // start CL Brg. we do this by comparing directions
         CComPtr<IDirection> dirSegment;
         measure->Direction(pntEnd1,pntEnd2,&dirSegment); // direction of segment

         Float64 d1,d2;
         direction->get_Value(&d1);
         dirSegment->get_Value(&d2);

         if ( !IsEqual(d1,d2) )
         {
            m_Lengths.dbLeftBearingOffset *= -1;
         }
      }

      direction.Release();
      measure->Inverse(pntBrg2,pntPier2,&offset,&direction);
      if ( !IsZero(offset) )
      {
         // need to determine if the intersection with the pier line is before or after the
         // start CL Brg. we do this by comparing directions
         CComPtr<IDirection> dirSegment;
         measure->Direction(pntEnd1,pntEnd2,&dirSegment); // direction of segment

         Float64 d1,d2;
         direction->get_Value(&d1);
         dirSegment->get_Value(&d2);

         if ( !IsEqual(d1,d2) )
         {
            m_Lengths.dbRightBearingOffset *= -1;
         }
      }

      m_UpdateLengths = false;
   }
}
