///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2012  Washington State Department of Transportation
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

// VehicularAnalysisContext.cpp : Implementation of CVehicularAnalysisContext
#include "stdafx.h"
#include "WBFLLBAMLiveLoader.h"
#include "LBAMLiveLoader.hh"
#include "VehicularAnalysisContext.h"
#include "LiveLoaderUtils.h"

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVehicularAnalysisContext

STDMETHODIMP CVehicularAnalysisContext::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVehicularAnalysisContext
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CVehicularAnalysisContext::CVehicularAnalysisContext():
m_IsComputed(false),
m_LeftOverhang(0.0),
m_RightOverhang(0.0),
m_SuperstructureLength(0.0),
m_NumSupports(0)
{
}

HRESULT CVehicularAnalysisContext::FinalConstruct()
{
   return m_SupportLocations.CoCreateInstance(CLSID_DblArray);
}


void CVehicularAnalysisContext::Compute()
{
   if (!m_IsComputed)
   {
      ComputeSupportLocations();
   
      m_IsComputed = true;
   }
}

void CVehicularAnalysisContext::ComputeSupportLocations()
{
   m_SupportLocations->Clear();
   m_RightOverhang = 0.0;
   m_LeftOverhang = 0.0;
   m_SuperstructureLength=0.0;

   CHRException hr;
   // get overhangs and support locations
   CComPtr<ISupports> supports;
   hr = m_pModel->get_Supports(&supports);

   SupportIndexType num_supports;
   hr = supports->get_Count(&num_supports);

   m_NumSupports = num_supports;

   CComPtr<ISpans> spans;
   hr = m_pModel->get_Spans(&spans);

   SpanIndexType num_spans;
   hr = spans->get_Count(&num_spans);

   if (num_spans==0 && num_supports==0)
   {
      return;
   }
   else if (num_spans != num_supports-1)
   {
      THROW_LBAMLL(MUST_BE_ONE_MORE_SUPPORT_THAN_SPANS);
   }

   Float64 loc = 0.0;
   m_SupportLocations->Add(loc); // always a support at 0.0
   for (SpanIndexType i=0; i<num_spans; i++)
   {
      CComPtr<ISpan> span;
      hr = spans->get_Item(i, &span);

      Float64 length;
      hr = span->get_Length(&length);

      loc += length;
      m_SupportLocations->Add(loc); // always a support at 0.0
   }

   CComPtr<ISuperstructureMembers> ssms;
   hr = m_pModel->get_SuperstructureMembers(&ssms);

   Float64 offset;
   hr = ssms->get_Offset(&offset);

   m_LeftOverhang = offset;

   hr = ssms->get_Length(&m_SuperstructureLength);

   m_RightOverhang = m_SuperstructureLength - loc - m_LeftOverhang;

   if (IsZero(m_RightOverhang) )
   {
      m_RightOverhang = 0.0; // deal with round off -here
   }
   else if (m_RightOverhang<0.0)
   {
      THROW_LBAMLL(SUPERSTRUCTURE_TOO_SHORT);
   }
}

void CVehicularAnalysisContext::Invalidate()
{
   m_IsComputed = false;
}


void CVehicularAnalysisContext::FinalRelease()
{
   HRESULT hr;

   // unwire events
   hr = CrUnadvise(m_pModel, this, IID_ILBAMModelEvents, m_ModelEventsCookie);
   ATLASSERT(SUCCEEDED(hr));

   hr = CrUnadvise(m_pLiveLoad, this, IID_ILiveLoadEvents, m_LiveLoadEventsCookie);
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP CVehicularAnalysisContext::Initialize(ILBAMModel *model, /*[in]*/IInfluenceLineResponse* influence, 
                                                   ILiveLoadNegativeMomentRegion* llnmr, IAnalysisPOIs* pois,
                                                   IGetDistributionFactors* dfs, IGetStressPoints* gcs)
{
	CHECK_IN(model);
	CHECK_IN(influence);
	CHECK_IN(llnmr);
	CHECK_IN(pois);
	CHECK_IN(dfs);
	CHECK_IN(gcs);

   CHRException hr;
   try
   {

      if (m_pModel != NULL)
      {
         // can only initialize once
         THROW_LBAMLL(LL_INITIALIZATION);
      }

      // set up model and connection to live load
      m_pModel = model;
      hr = m_pModel->get_LiveLoad(&m_pLiveLoad);

      // set up influence lines and contraflexure
      m_pInfluenceResponse      = influence;
      m_pLiveLoadNegativeMomentRegion  = llnmr;
      m_pAnalysisPOIs           = pois;
      m_pGetDistributionFactors = dfs;
      m_pGetStressPoints        = gcs;


      hr = CrAdvise(m_pModel, this, IID_ILBAMModelEvents, &m_ModelEventsCookie);
      hr = CrAdvise(m_pLiveLoad, this, IID_ILiveLoadEvents, &m_LiveLoadEventsCookie);

      // compute support locations
      Compute();

   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IVehicularAnalysisContext);
   }

	return S_OK;
}

///////////////////////////////////////////////////////////////
////// ISupportLocations
///////////////////////////////////////////////////////////////
STDMETHODIMP CVehicularAnalysisContext::get_LeftOverhang(/*[out,retval]*/Float64* overhang)
{
   CHECK_RETVAL(overhang);

   try
   {
      Compute();

      *overhang = m_LeftOverhang;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IVehicularAnalysisContext);
   }

   return S_OK;
}

STDMETHODIMP CVehicularAnalysisContext::get_RightOverhang(/*[out,retval]*/Float64* overhang)
{
   CHECK_RETVAL(overhang);

   try
   {
      Compute();

      *overhang = m_RightOverhang;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IVehicularAnalysisContext);
   }

   return S_OK;
}

STDMETHODIMP CVehicularAnalysisContext::get_SupportLocations(/*[out,retval]*/IDblArray* *vLocs)
{
   CHECK_RETOBJ(vLocs);
   try
   {
      Compute();

      return m_SupportLocations.CopyTo(vLocs);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IVehicularAnalysisContext);
   }

   return S_OK;
}

STDMETHODIMP CVehicularAnalysisContext::get_TotalLength(/*[out,retval]*/Float64* length)
{
   CHECK_RETVAL(length);
   try
   {
      Compute();

      *length = m_SuperstructureLength;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IVehicularAnalysisContext);
   }

   return S_OK;
}

STDMETHODIMP CVehicularAnalysisContext::IsInteriorSupport(SupportIDType supportID, VARIANT_BOOL *isInterior)
{
   CHECK_RETVAL(isInterior);

   // we dont check if temporary supports exist
	if (supportID <= 0 || (m_NumSupports-1) <= supportID)
      *isInterior = VARIANT_FALSE;
   else
      *isInterior = VARIANT_TRUE;

	return S_OK;
}


///////////////////////////////////////////////////////////////
////// IInfluenceLineResponse
///////////////////////////////////////////////////////////////
// 


STDMETHODIMP CVehicularAnalysisContext::ComputeForceInfluenceLine(PoiIDType poiID, BSTR stage, ForceEffectType forceEffect, ResultsOrientation orientation, IInfluenceLine** lftVal, IInfluenceLine** rgtVal)
{
   return m_pInfluenceResponse->ComputeForceInfluenceLine(poiID, stage, forceEffect, orientation, lftVal, rgtVal);
}

STDMETHODIMP CVehicularAnalysisContext::ComputeDeflectionInfluenceLine(PoiIDType poiID, BSTR stage, ForceEffectType deflectionEffect, IInfluenceLine** lftVal, IInfluenceLine** rgtVal)
{
   return m_pInfluenceResponse->ComputeDeflectionInfluenceLine(poiID, stage, deflectionEffect, lftVal, rgtVal);
}

STDMETHODIMP CVehicularAnalysisContext::ComputeReactionInfluenceLine(SupportIDType supportID, BSTR stage, ForceEffectType ReactionEffect, IInfluenceLine** newVal)
{
   return m_pInfluenceResponse->ComputeReactionInfluenceLine(supportID, stage, ReactionEffect, newVal);
}

STDMETHODIMP CVehicularAnalysisContext::ComputeSupportDeflectionInfluenceLine(SupportIDType supportID, BSTR stage, ForceEffectType SupportDeflectionEffect, IInfluenceLine** newVal)
{
   return m_pInfluenceResponse->ComputeSupportDeflectionInfluenceLine(supportID, stage, SupportDeflectionEffect, newVal);
}

STDMETHODIMP CVehicularAnalysisContext::SetZeroTolerance(Float64 forceTol, Float64 deflTol)
{
   return m_pInfluenceResponse->SetZeroTolerance( forceTol, deflTol);
}

STDMETHODIMP CVehicularAnalysisContext::GetZeroTolerance(Float64* forceTol, Float64* deflTol)
{
   return m_pInfluenceResponse->GetZeroTolerance( forceTol, deflTol );
}


///////////////////////////////////////////////////////////////
////// ILiveLoadNegativeMomentRegion
///////////////////////////////////////////////////////////////
// 

STDMETHODIMP CVehicularAnalysisContext::get_IsPOIInNegativeLiveLoadMomentZone(PoiIDType poiID, BSTR stage, InZoneType* isInZone)
{
   return m_pLiveLoadNegativeMomentRegion->get_IsPOIInNegativeLiveLoadMomentZone( poiID, stage, isInZone);
}

STDMETHODIMP CVehicularAnalysisContext::ComputeNegativeMomentRegions(BSTR stage, IDblArray* *locations)
{
   return m_pLiveLoadNegativeMomentRegion->ComputeNegativeMomentRegions( stage, locations);
}

///////////////////////////////////////////////////////////////
////// IInfluenceLineResponse
///////////////////////////////////////////////////////////////

STDMETHODIMP CVehicularAnalysisContext::get_Design(ILiveLoadModel **pVal)
{
	return m_pLiveLoad->get_Design(pVal);
}

STDMETHODIMP CVehicularAnalysisContext::putref_Design(ILiveLoadModel *newVal)
{
	return m_pLiveLoad->putref_Design(newVal);
}

STDMETHODIMP CVehicularAnalysisContext::get_Deflection(ILiveLoadModel **pVal)
{
	return m_pLiveLoad->get_Deflection(pVal);
}

STDMETHODIMP CVehicularAnalysisContext::putref_Deflection(ILiveLoadModel *newVal)
{
	return m_pLiveLoad->putref_Deflection(newVal);
}

STDMETHODIMP CVehicularAnalysisContext::get_Fatigue(ILiveLoadModel **pVal)
{
	return m_pLiveLoad->get_Fatigue(pVal);
}

STDMETHODIMP CVehicularAnalysisContext::putref_Fatigue(ILiveLoadModel *newVal)
{
	return m_pLiveLoad->putref_Fatigue(newVal);
}

STDMETHODIMP CVehicularAnalysisContext::get_Permit(ILiveLoadModel **pVal)
{
	return m_pLiveLoad->get_Permit(pVal);
}

STDMETHODIMP CVehicularAnalysisContext::putref_Permit(ILiveLoadModel *newVal)
{
	return m_pLiveLoad->putref_Permit(newVal);
}

STDMETHODIMP CVehicularAnalysisContext::get_Special(ILiveLoadModel **pVal)
{
	return m_pLiveLoad->get_Special(pVal);
}

STDMETHODIMP CVehicularAnalysisContext::putref_Special(ILiveLoadModel *newVal)
{
	return m_pLiveLoad->putref_Special(newVal);
}

STDMETHODIMP CVehicularAnalysisContext::get_Pedestrian(ILiveLoadModel **pVal)
{
	return m_pLiveLoad->get_Pedestrian(pVal);
}

STDMETHODIMP CVehicularAnalysisContext::putref_Pedestrian(ILiveLoadModel *newVal)
{
	return m_pLiveLoad->putref_Pedestrian(newVal);
}

STDMETHODIMP CVehicularAnalysisContext::get_LegalRoutineRating(ILiveLoadModel* *pVal)
{
	return m_pLiveLoad->get_LegalRoutineRating(pVal);
}

STDMETHODIMP CVehicularAnalysisContext::putref_LegalRoutineRating(ILiveLoadModel* newVal)
{
	return m_pLiveLoad->putref_LegalRoutineRating(newVal);
}

STDMETHODIMP CVehicularAnalysisContext::get_LegalSpecialRating(ILiveLoadModel* *pVal)
{
	return m_pLiveLoad->get_LegalSpecialRating(pVal);
}

STDMETHODIMP CVehicularAnalysisContext::putref_LegalSpecialRating(ILiveLoadModel* newVal)
{
	return m_pLiveLoad->putref_LegalSpecialRating(newVal);
}

STDMETHODIMP CVehicularAnalysisContext::get_PermitRoutineRating(ILiveLoadModel* *pVal)
{
	return m_pLiveLoad->get_PermitRoutineRating(pVal);
}

STDMETHODIMP CVehicularAnalysisContext::putref_PermitRoutineRating(ILiveLoadModel* newVal)
{
	return m_pLiveLoad->putref_PermitRoutineRating(newVal);
}

STDMETHODIMP CVehicularAnalysisContext::get_PermitSpecialRating(ILiveLoadModel* *pVal)
{
	return m_pLiveLoad->get_PermitSpecialRating(pVal);
}

STDMETHODIMP CVehicularAnalysisContext::putref_PermitSpecialRating(ILiveLoadModel* newVal)
{
	return m_pLiveLoad->putref_PermitSpecialRating(newVal);
}

STDMETHODIMP CVehicularAnalysisContext::Clear()
{
	return m_pLiveLoad->Clear();
}

STDMETHODIMP CVehicularAnalysisContext::Clone(ILiveLoad** clone)
{
	return m_pLiveLoad->Clone(clone);
}

//////////////////////////
///////  ILBAMModelEvents
//////////////////////////
// 
STDMETHODIMP CVehicularAnalysisContext::OnModelChanged(/*[in]*/ILBAMModel* Model, ChangeType change)
{
   // a few things we dont care about
   if (change!=cgtStress &&
       change!=cgtCombination &&
       change!=cgtDistributionFactor &&
       change!=cgtLoads &&
       change!=cgtLiveLoad)
   {
      Invalidate();

      Fire_OnStiffnessResponseChanged(lcsEntireModel, -1);
   }
   else if (change==cgtLiveLoad)
   {
      // most live load change events are handled in OnLiveLoadChanged below except for the case where the entire 
      // ILiveLoad object is swapped out of the model. This requires more draconian measures
      HRESULT hr;
      CComPtr<ILiveLoad> ll;
      hr = m_pModel->get_LiveLoad(&ll);
      if (FAILED(hr))
         return hr;

      if (!ll.IsEqualObject(m_pLiveLoad))
      {
         Invalidate();

         hr = CrUnadvise(m_pLiveLoad, this, IID_ILiveLoadEvents, m_LiveLoadEventsCookie);
         if (FAILED(hr))
            return hr;

         m_pLiveLoad = ll;

         hr = CrAdvise(m_pLiveLoad, this, IID_ILiveLoadEvents, &m_LiveLoadEventsCookie);
         if (FAILED(hr))
            return hr;

         // have to assume at this point that all is hosed.
         Fire_OnStiffnessResponseChanged(lcsEntireModel, -1);
      }
   }

   return S_OK;
}

// ILiveLoadEvents
STDMETHODIMP CVehicularAnalysisContext::OnLiveLoadChanged(ILiveLoad* load, LiveLoadModelType lltype)
{
   Fire_OnLiveLoadChanged(lltype);
   return S_OK;
}


///////////////////////////////////////////////////////////////
////// IAnalysisPOIs
///////////////////////////////////////////////////////////////

HRESULT CVehicularAnalysisContext::get_SpanPoiIncrement( PoiIDType *pVal)
{
   return m_pAnalysisPOIs->get_SpanPoiIncrement( pVal);
}

HRESULT CVehicularAnalysisContext::put_SpanPoiIncrement( PoiIDType newVal)
{
   return m_pAnalysisPOIs->put_SpanPoiIncrement( newVal);
}

HRESULT CVehicularAnalysisContext::get_CantileverPoiIncrement(PoiIDType *pVal)
{
   return m_pAnalysisPOIs->get_CantileverPoiIncrement( pVal);
}

HRESULT CVehicularAnalysisContext::put_CantileverPoiIncrement( PoiIDType newVal)
{
   return m_pAnalysisPOIs->put_CantileverPoiIncrement(newVal);
}

HRESULT CVehicularAnalysisContext::GetSuperstructurePois(BSTR stage, ILongArray* *poiIDs, IDblArray* *poiLocations)
{
   return m_pAnalysisPOIs->GetSuperstructurePois(stage, poiIDs, poiLocations);
}

HRESULT CVehicularAnalysisContext::GetPoiInfo(BSTR stage, PoiIDType poiID, MemberType* lbamMemberType, MemberIDType* memberID, Float64* memberLocation)
{
   return m_pAnalysisPOIs->GetPoiInfo(stage, poiID, lbamMemberType, memberID, memberLocation);
}

///////////////////////////////////////////////////////////////
////// IGetDistributionFactors
///////////////////////////////////////////////////////////////

// IGetDistributionFactors
HRESULT CVehicularAnalysisContext::GetPOIDistributionFactor(PoiIDType poiID, BSTR stage, IDistributionFactor* *leftFactor, IDistributionFactor* *rightFactor)
{
   return m_pGetDistributionFactors->GetPOIDistributionFactor(poiID, stage, leftFactor, rightFactor);
}


STDMETHODIMP CVehicularAnalysisContext::GetSupportDistributionFactor(SupportIDType supportID, BSTR Stage, IDistributionFactor **Factor)
{
   return m_pGetDistributionFactors->GetSupportDistributionFactor(supportID, Stage, Factor);
}

///////////////////////////////////////////////////////////////
// IGetStressPointss
///////////////////////////////////////////////////////////////
STDMETHODIMP CVehicularAnalysisContext::GetStressPointsAtPOI(/*[in]*/PoiIDType poiID, /*[in]*/BSTR stage, /*[out]*/IStressPoints* *leftCs,  /*[out]*/IStressPoints* *rightCs)
{
   return m_pGetStressPoints->GetStressPointsAtPOI(poiID, stage, leftCs, rightCs);
}
