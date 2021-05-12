///////////////////////////////////////////////////////////////////////
// LBAM Analysis Utility - Longitindal Bridge Analysis Model
// Copyright © 1999-2021  Washington State Department of Transportation
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

// LoadCaseResponseAgg.cpp : Implementation of CLoadCaseResponseAgg
#include "stdafx.h"

#include "LoadCaseResponseAgg.h"
#include "..\LBAMUtils.h"
#include "LBAMAnalysisUtility.hh"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// handle dealing with cancel from progress monitor
#define HANDLE_CANCEL_PROGRESS() if (m_pEnveloper->CheckForCancel()) throw S_FALSE;


// comparision functions
static bool MaxCmp(Float64 val1, Float64 val2)
{
   return val2>val1 && !IsEqual(val1,val2);
}

static bool MinCmp(Float64 val1, Float64 val2)
{
   return val2<val1 && !IsEqual(val1,val2);
}


///////////////////////////////////////////
// CLoadCaseResponseAgg
///////////////////////////////////////////

STDMETHODIMP CLoadCaseResponseAgg::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ILoadCaseResponse
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// ILoadCaseResponse
STDMETHODIMP CLoadCaseResponseAgg::ComputeForces(BSTR loadCase, IIDArray* POIs, BSTR Stage, ResultsOrientation orientation, ResultsSummationType summ, ISectionResult3Ds** pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<ISectionResult3Ds> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng = 0;  ieng<eng_cnt; ieng++)
      {
         HANDLE_CANCEL_PROGRESS();

         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<ILoadCaseResponse> response;
         hr = engine->get_LoadCaseResponse(&response);

         CComPtr<ISectionResult3Ds> results;

         hr = response->ComputeForces(loadCase, POIs, Stage, orientation, summ, &results);
         result_vec.push_back( results );
      }

      // intialize our vector of controlling engine id's to engine zero
      CollectionIndexType poi_cnt;
      hr = POIs->get_Count(&poi_cnt);
      m_ControllingEngine.clear();
      m_ControllingEngine.resize(poi_cnt);

      // now that we have all results from all engines, envelope them
      // controlling results are placed in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLoadCaseSectionResults(result_vec[0].m_T,result_vec[ieng].m_T,true,ieng);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILoadCaseResponse);
   }

   return S_OK;
}

STDMETHODIMP CLoadCaseResponseAgg::ComputeDeflections(BSTR loadCase, IIDArray* POIs, BSTR Stage, ResultsSummationType summ, ISectionResult3Ds** pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<ISectionResult3Ds> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng = 0;  ieng<eng_cnt; ieng++)
      {
         HANDLE_CANCEL_PROGRESS();

         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<ILoadCaseResponse> response;
         hr = engine->get_LoadCaseResponse(&response);

         CComPtr<ISectionResult3Ds> results;

         hr = response->ComputeDeflections(loadCase, POIs, Stage, summ, &results);
         result_vec.push_back( results );
      }

      // intialize our vector of controlling engine id's to engine zero
      CollectionIndexType poi_cnt;
      hr = POIs->get_Count(&poi_cnt);
      m_ControllingEngine.assign(poi_cnt,LRPair());

      // now that we have all results from all engines, envelope them
      // controlling results are placed in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLoadCaseSectionResults(result_vec[0].m_T,result_vec[ieng].m_T,false,ieng);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILoadCaseResponse);
   }

   return S_OK;
}

STDMETHODIMP CLoadCaseResponseAgg::ComputeReactions(BSTR loadCase, IIDArray* POIs, BSTR Stage, ResultsSummationType summ, IResult3Ds** pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<IResult3Ds> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng = 0;  ieng<eng_cnt; ieng++)
      {
         HANDLE_CANCEL_PROGRESS();

         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<ILoadCaseResponse> response;
         hr = engine->get_LoadCaseResponse(&response);

         CComPtr<IResult3Ds> results;

         hr = response->ComputeReactions(loadCase, POIs, Stage, summ, &results);
         result_vec.push_back( results );
      }

      // intialize our vector of controlling engine id's to engine zero
      CollectionIndexType poi_cnt;
      hr = POIs->get_Count(&poi_cnt);
      m_ControllingEngine.clear();
      m_ControllingEngine.resize(poi_cnt);

      // now that we have all results from all engines, envelope them
      // controlling results are placed in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLoadCaseResults(result_vec[0].m_T,result_vec[ieng].m_T);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILoadCaseResponse);
   }

   return S_OK;
}

STDMETHODIMP CLoadCaseResponseAgg::ComputeSupportDeflections(BSTR loadCase, IIDArray* POIs, BSTR Stage, ResultsSummationType summ, IResult3Ds** pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<IResult3Ds> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng = 0;  ieng<eng_cnt; ieng++)
      {
         HANDLE_CANCEL_PROGRESS();

         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<ILoadCaseResponse> response;
         hr = engine->get_LoadCaseResponse(&response);

         CComPtr<IResult3Ds> results;

         hr = response->ComputeSupportDeflections(loadCase, POIs, Stage, summ, &results);
         result_vec.push_back( results );
      }

      // intialize our vector of controlling engine id's to engine zero
      CollectionIndexType poi_cnt;
      hr = POIs->get_Count(&poi_cnt);
      m_ControllingEngine.clear();
      m_ControllingEngine.resize(poi_cnt);

      // now that we have all results from all engines, envelope them
      // controlling results are placed in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLoadCaseResults(result_vec[0].m_T,result_vec[ieng].m_T);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILoadCaseResponse);
   }

   return S_OK;
}

STDMETHODIMP CLoadCaseResponseAgg::ComputeStresses(BSTR loadCase, IIDArray* POIs, BSTR Stage, ResultsSummationType summ, ISectionStressResults** pResults)
{
   CHECK_RETOBJ(pResults);
   CHRException hr;

   try
   {
      // loop over all of our engines and get results from each
      CollectionIndexType eng_cnt = m_pEnveloper->EngineCount();
      if (eng_cnt==0)
      {
         THROW_LBAMAU(ENGINE_INIT);
      }

      std::vector< CAdapt< CComPtr<ISectionStressResults> > > result_vec;
      result_vec.reserve(eng_cnt);

      for (CollectionIndexType ieng = 0;  ieng<eng_cnt; ieng++)
      {
         HANDLE_CANCEL_PROGRESS();

         CComPtr<ILBAMAnalysisEngine> engine;
         m_pEnveloper->GetEngine(ieng, &engine);

         CComPtr<ILoadCaseResponse> response;
         hr = engine->get_LoadCaseResponse(&response);

         CComPtr<ISectionStressResults> results;

         hr = response->ComputeStresses(loadCase, POIs, Stage, summ, &results);
         result_vec.push_back( results );
      }

      // intialize our vector of controlling engine id's to engine zero
      CollectionIndexType poi_cnt;
      hr = POIs->get_Count(&poi_cnt);
      m_ControllingEngine.clear();
      m_ControllingEngine.resize(poi_cnt);

      // now that we have all results from all engines, envelope them
      // controlling results are placed in the first member of the vector
      for (CollectionIndexType ieng=1; ieng<eng_cnt; ieng++)
      {
         EnvelopeLoadCaseSectionStressResults(result_vec[0].m_T,result_vec[ieng].m_T);
      }

      hr = result_vec[0].m_T.CopyTo(pResults);
   }
   catch(...)
   {
      return DealWithExceptions(m_pEnveloper, IID_ILoadCaseResponse);
   }

   return S_OK;
}

// Make sure maximum value is in res1
void CLoadCaseResponseAgg::EnvelopeLoadCaseSectionResults(ISectionResult3Ds* res1, ISectionResult3Ds* res2,bool doFlip,CollectionIndexType engineIdx)
{
   CHRException hr;

   // use a function pointer to streamline min/max'ing
   bool (*lftcmp)(Float64, Float64);
   bool (*rgtcmp)(Float64, Float64);

   if (m_Optimization == optMaximize)
   {
      lftcmp = &MaxCmp;

      if (doFlip)
         rgtcmp = &MinCmp;
      else
         rgtcmp = &MaxCmp;
   }
   else
   {
      lftcmp = &MinCmp;

      if (doFlip)
         rgtcmp = &MaxCmp;
      else
         rgtcmp = &MinCmp;
   }

   // loop over all pois and replace res1 with optmized results from res2 if needed.
   CollectionIndexType poi_cnt;
   hr = res1->get_Count(&poi_cnt);

   for (CollectionIndexType ipoi = 0; ipoi<poi_cnt; ipoi++)
   {
      CComPtr<ISectionResult3D> sr1, sr2;

      // section results
      hr = res1->get_Item(ipoi,&sr1);
      hr = res2->get_Item(ipoi,&sr2);

      Float64 lval1, rval1;
      Float64 lval2, rval2;
      switch( m_ForceEffect )
      {
      case fetFx:
         sr1->get_XLeft(&lval1);
         sr1->get_XRight(&rval1);
         sr2->get_XLeft(&lval2);
         sr2->get_XRight(&rval2);
         break;

      case fetFy:
         sr1->get_YLeft(&lval1);
         sr1->get_YRight(&rval1);
         sr2->get_YLeft(&lval2);
         sr2->get_YRight(&rval2);
         break;

      case fetMz:
         sr1->get_ZLeft(&lval1);
         sr1->get_ZRight(&rval1);
         sr2->get_ZLeft(&lval2);
         sr2->get_ZRight(&rval2);
         break;
      }

      bool ldo, rdo;
      ldo = lftcmp(lval1, lval2);
      rdo = rgtcmp(rval1, rval2);

      Float64 xl, xr, yl, yr, zl, zr;
      if (ldo)
      {
         m_ControllingEngine[ipoi].Left = engineIdx;

         if (rdo)
         {
            m_ControllingEngine[ipoi].Right = engineIdx;

            // replace res1's right and left
            sr2->GetResult(&xl,&yl,&zl,&xr,&yr,&zr);
            sr1->SetResult(xl,yl,zl,xr,yr,zr);
         }
         else
         {
            // left only
            sr2->GetResult(&xl,&yl,&zl,&xr,&yr,&zr);
            sr1->put_XLeft(xl);
            sr1->put_YLeft(yl);
            sr1->put_ZLeft(zl);
         }
      }
      else if (rdo)
      {
         // right only
         m_ControllingEngine[ipoi].Right = engineIdx;

         sr2->GetResult(&xl,&yl,&zl,&xr,&yr,&zr);
         sr1->put_XRight(xl);
         sr1->put_YRight(yl);
         sr1->put_ZRight(zl);
      }
   }
}


void CLoadCaseResponseAgg::EnvelopeLoadCaseResults(IResult3Ds* res1, IResult3Ds* res2)
{
   CHRException hr;

   // use a function pointer to streamline min/max'ing
   bool (*cmp)(Float64, Float64);

   if (m_Optimization == optMaximize)
   {
      cmp = &MaxCmp;
   }
   else
   {
      cmp = &MinCmp;
   }

   // loop over all pois and replace res1 with optmized results from res2 if needed.
   CollectionIndexType poi_cnt;
   hr = res1->get_Count(&poi_cnt);

   for (CollectionIndexType ipoi = 0; ipoi<poi_cnt; ipoi++)
   {
      CComPtr<IResult3D> r1,r2;

      hr = res1->get_Item(ipoi,&r1);
      hr = res2->get_Item(ipoi,&r2);

      Float64 val1, val2;
      switch( m_ForceEffect )
      {
      case fetFx:
         r1->get_X(&val1);
         r2->get_X(&val2);
         break;

      case fetFy:
         r1->get_Y(&val1);
         r2->get_Y(&val2);
         break;

      case fetMz:
         r1->get_Z(&val1);
         r2->get_Z(&val2);
         break;
      }

      bool did;
      did = cmp(val1, val2);

      if (did)
      {
         Float64 x,y,z;
         r2->GetResult(&x,&y,&z);
         r1->SetResult(x,y,z);
      }
   }
}


void CLoadCaseResponseAgg::EnvelopeLoadCaseSectionStressResults(ISectionStressResults* res1, ISectionStressResults* res2)
{
   CHRException hr;

   // use a function pointer to streamline min/max'ing
   bool (*lftcmp)(Float64, Float64);
   bool (*rgtcmp)(Float64, Float64);

   if (m_Optimization == optMaximize)
   {
      lftcmp = &MaxCmp;
      rgtcmp = &MaxCmp;
   }
   else
   {
      lftcmp = &MinCmp;
      rgtcmp = &MinCmp;
   }

   // loop over all pois and replace res1 with optmized results from res2 if needed.
   CollectionIndexType poi_cnt;
   hr = res1->get_Count(&poi_cnt);

   for (CollectionIndexType ipoi = 0; ipoi<poi_cnt; ipoi++)
   {
      CComPtr<ISectionStressResult> sr1, sr2;
      res1->get_Item(ipoi,&sr1);
      res2->get_Item(ipoi,&sr2);

      CollectionIndexType lcount1, rcount1;
      CollectionIndexType lcount2, rcount2;

      sr1->get_LeftCount(&lcount1);
      sr1->get_RightCount(&rcount1);

      sr2->get_LeftCount(&lcount2);
      sr2->get_RightCount(&rcount2);

      // must be comparing the same things...
      // hr will thrown an exception if set to an error value
      if ( (lcount1 != lcount2) || (rcount1 != rcount2) )
         hr = E_FAIL;

      // left section of stress point
      for ( CollectionIndexType spIdx = 0; spIdx < lcount1; spIdx++ )
      {
         Float64 f1, f2;

         sr1->GetLeftResult(spIdx,&f1);
         sr2->GetLeftResult(spIdx,&f2);

         if ( lftcmp(f1,f2) )
         {
            sr1->SetLeftResult(spIdx,f2);
         }
      }

      // right section of stress point
      for ( CollectionIndexType spIdx = 0; spIdx < rcount1; spIdx++ )
      {
         Float64 f1, f2;

         sr1->GetRightResult(spIdx,&f1);
         sr2->GetRightResult(spIdx,&f2);

         if ( lftcmp(f1,f2) )
         {
            sr1->SetRightResult(spIdx,f2);
         }
      }
   }
}
