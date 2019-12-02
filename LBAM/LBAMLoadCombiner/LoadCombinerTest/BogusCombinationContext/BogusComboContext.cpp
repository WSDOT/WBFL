///////////////////////////////////////////////////////////////////////
// BogusCombinationContext - Test driver for LBAM load combinations
// Copyright © 1999-2019  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// BogusComboContext.cpp : Implementation of CBogusComboContext
#include "stdafx.h"

#if defined VBA_BUILD
#if defined _DEBUG
#if defined _WIN64
#include "x64\VBA_Debug\BogusCombinationContext.h"
#else
#include "Win32\VBA_Debug\BogusCombinationContext.h"
#endif
#else
#if defined _WIN64
#include "x64\VBA_Release\BogusCombinationContext.h"
#else
#include "Win32\VBA_Release\BogusCombinationContext.h"
#endif
#endif
#else // VBA_BUILD
#if defined _DEBUG
#if defined _WIN64
#include "x64\Debug\BogusCombinationContext.h"
#else
#include "Win32\Debug\BogusCombinationContext.h"
#endif
#else
#if defined _WIN64
#include "x64\Release\BogusCombinationContext.h"
#else
#include "Win32\Release\BogusCombinationContext.h"
#endif
#endif
#endif // VBA_BUILD

#include "BogusComboContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBogusComboContext

STDMETHODIMP CBogusComboContext::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadCombinationAnalysisContext
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CBogusComboContext::Initialize(ILBAMModel *model, ILoadGroupResponse *loadGroupResponse, 
                                            ILiveLoadModelResponse *liveLoadModelResponse, /*[in]*/IBasicVehicularResponse* basicVres, 
                                            IAnalysisPOIs* pois, IGetStressPoints* stressPoints)
{
   ATLASSERT(false);
   return E_FAIL;
}

HRESULT CBogusComboContext::FinalConstruct()
{
   try
   {
      CHRException hr;
      // stages
      hr = m_Stage1.CoCreateInstance(CLSID_Stage);
      hr = m_Stage2.CoCreateInstance(CLSID_Stage);
      hr = m_Stage3.CoCreateInstance(CLSID_Stage);

      hr = m_Stage1->put_Name(CComBSTR("Stage 1"));
      hr = m_Stage2->put_Name(CComBSTR("Stage 2"));
      hr = m_Stage3->put_Name(CComBSTR("Stage 3"));

      // Load Cases
      hr = m_LoadCase1.CoCreateInstance(CLSID_LoadCase);
      hr = m_LoadCase2.CoCreateInstance(CLSID_LoadCase);
      hr = m_LoadCase3.CoCreateInstance(CLSID_LoadCase);

      hr = m_LoadCase1->put_Name(CComBSTR("Load Case 1"));
      hr = m_LoadCase1->AddLoadGroup(CComBSTR("Lg1_1"));
      hr = m_LoadCase1->AddLoadGroup(CComBSTR("Lg1_2"));
      hr = m_LoadCase1->AddLoadGroup(CComBSTR("Lg1_3"));

      hr = m_LoadCase2->put_Name(CComBSTR("Load Case 2"));
      hr = m_LoadCase2->AddLoadGroup(CComBSTR("Lg2_1"));
      hr = m_LoadCase2->AddLoadGroup(CComBSTR("Lg2_2"));

      hr = m_LoadCase3->put_Name(CComBSTR("Load Case 3"));
      hr = m_LoadCase3->AddLoadGroup(CComBSTR("Lg3_1"));

      // Load Combinations
      hr = m_LoadCombo1.CoCreateInstance(CLSID_LoadCombination);
      hr = m_LoadCombo2.CoCreateInstance(CLSID_LoadCombination);
      hr = m_LoadCombo3.CoCreateInstance(CLSID_LoadCombination);
      hr = m_LoadCombo1->put_Name(CComBSTR("Load Combination 1"));
      hr = m_LoadCombo2->put_Name(CComBSTR("Load Combination 2"));
      hr = m_LoadCombo3->put_Name(CComBSTR("Load Combination 3"));

      Float64 fct_cb1_ll     = 1.4;
      Float64 fct_cb1_lc1_mn = 0.3;
      Float64 fct_cb1_lc1_mx = 1.2;
      Float64 fct_cb1_lc2_mn = 1.4;
      Float64 fct_cb1_lc2_mx = 0.3;
      Float64 fct_cb1_lc3_mn = 1.1;
      Float64 fct_cb1_lc3_mx = 1.1;
      hr = m_LoadCombo1->put_LiveLoadFactor(fct_cb1_ll);
      hr = m_LoadCombo1->AddLiveLoadModel(lltDesign);
      hr = m_LoadCombo1->AddLoadCaseFactor(CComBSTR("Load Case 1"), fct_cb1_lc1_mn, fct_cb1_lc1_mx);
      hr = m_LoadCombo1->AddLoadCaseFactor(CComBSTR("Load Case 2"), fct_cb1_lc2_mn, fct_cb1_lc2_mx);
      hr = m_LoadCombo1->AddLoadCaseFactor(CComBSTR("Load Case 3"), fct_cb1_lc3_mn, fct_cb1_lc3_mx);

      Float64 fct_cb2_ll     = 0.5;
      Float64 fct_cb2_lc1_mn = 0.5;
      Float64 fct_cb2_lc1_mx = 0.5;
      hr = m_LoadCombo2->put_LiveLoadFactor(fct_cb2_ll);
      hr = m_LoadCombo2->AddLiveLoadModel(lltDesign);
      hr = m_LoadCombo2->AddLoadCaseFactor(CComBSTR("Load Case 1"), fct_cb2_lc1_mn, fct_cb2_lc1_mx);

      Float64 fct_cb3_ll     = 1.5;
      Float64 fct_cb3_lc3_mn = 0.5;
      Float64 fct_cb3_lc3_mx = 1.5;
      hr = m_LoadCombo3->put_LiveLoadFactor(fct_cb3_ll);
      hr = m_LoadCombo3->AddLiveLoadModel(lltDesign);
      hr = m_LoadCombo3->AddLoadCaseFactor(CComBSTR("Load Case 3"), fct_cb3_lc3_mn, fct_cb3_lc3_mx);

      // Set up Response values
      ////////
      // POI 1
      ////////
      ComboBenchMark p1bm_t(1);
      // insert empty into collection so we don't have to do a lot of nested copying
      std::pair<BenchMarkIterator, bool> itp1bm = m_BenchMarks.insert(std::make_pair((PoiIDType)1, p1bm_t));
      ComboBenchMark& p1bm = itp1bm.first->second;

      p1bm.SetCombinationFactors(CComBSTR("Stage 1"), lctService, 1.0, 1.0);

      // stress points
      CComPtr<IStressPoints> stg1_sps, stg2_sps, stg3_sps;
      stg1_sps.CoCreateInstance(CLSID_StressPoints);
      stg2_sps.CoCreateInstance(CLSID_StressPoints);
      stg3_sps.CoCreateInstance(CLSID_StressPoints);

      Float64 stg1_sa1 = 0.5;   //stage 1
      Float64 stg1_sm1 = 0.25;
      Float64 stg1_sa2 = 0.5;
      Float64 stg1_sm2 = -0.25;
      CComPtr<IStressPoint> stg1_sp1, stg1_sp2;
      stg1_sp1.CoCreateInstance(CLSID_StressPoint);
      stg1_sp2.CoCreateInstance(CLSID_StressPoint);
      stg1_sp1->put_Sa(stg1_sa1);
      stg1_sp1->put_Sm(stg1_sm1);
      stg1_sp2->put_Sa(stg1_sa2);
      stg1_sp2->put_Sm(stg1_sm2);
      stg1_sps->Add(stg1_sp1);
      stg1_sps->Add(stg1_sp2);

      Float64 stg2_sa1 = 0.4;   //stage 2
      Float64 stg2_sm1 = 0.15;
      Float64 stg2_sa2 = 0.4;
      Float64 stg2_sm2 = -0.15;
      CComPtr<IStressPoint> stg2_sp1, stg2_sp2;
      stg2_sp1.CoCreateInstance(CLSID_StressPoint);
      stg2_sp2.CoCreateInstance(CLSID_StressPoint);
      stg2_sp1->put_Sa(stg2_sa1);
      stg2_sp1->put_Sm(stg2_sm1);
      stg2_sp2->put_Sa(stg2_sa2);
      stg2_sp2->put_Sm(stg2_sm2);
      stg2_sps->Add(stg2_sp1);
      stg2_sps->Add(stg2_sp2);

      Float64 stg3_sa1 = 0.3;   //stage 2
      Float64 stg3_sm1 = 0.10;
      Float64 stg3_sa2 = 0.3;
      Float64 stg3_sm2 = -0.10;
      CComPtr<IStressPoint> stg3_sp1, stg3_sp2;
      stg3_sp1.CoCreateInstance(CLSID_StressPoint);
      stg3_sp2.CoCreateInstance(CLSID_StressPoint);
      stg3_sp1->put_Sa(stg3_sa1);
      stg3_sp1->put_Sm(stg3_sm1);
      stg3_sp2->put_Sa(stg3_sa2);
      stg3_sp2->put_Sm(stg3_sm2);
      stg3_sps->Add(stg3_sp1);
      stg3_sps->Add(stg3_sp2);

      p1bm.SetStressPoints(CComBSTR("Stage 1"), stg1_sps);
      p1bm.SetStressPoints(CComBSTR("Stage 2"), stg2_sps);
      p1bm.SetStressPoints(CComBSTR("Stage 3"), stg3_sps);

      // live load
      Float64 ll_min = -2120.0;
      Float64 ll_max =  2140.0;
      p1bm.SetLiveLoadValue(ll_min, ll_max);

      // load group responses
      Float64 lg1_1_1i = 1011.0;
      Float64 lg1_1_1c = 1011.0;
      Float64 lg1_1_2i = 1012.0;
      Float64 lg1_1_2c = 2023.0;
      Float64 lg1_1_3i = 1013.0;
      Float64 lg1_1_3c = 3036.0;
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_1"), CComBSTR("Stage 1"), rsIncremental, lg1_1_1i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_1"), CComBSTR("Stage 1"), rsCumulative, lg1_1_1c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_1"), CComBSTR("Stage 2"), rsIncremental, lg1_1_2i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_1"), CComBSTR("Stage 2"), rsCumulative, lg1_1_2c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_1"), CComBSTR("Stage 3"), rsIncremental, lg1_1_3i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_1"), CComBSTR("Stage 3"), rsCumulative, lg1_1_3c);

      Float64 lg1_2_1i = 1021.0;
      Float64 lg1_2_1c = 1021.0;
      Float64 lg1_2_2i = 1022.0;
      Float64 lg1_2_2c = 2043.0;
      Float64 lg1_2_3i = 1023.0;
      Float64 lg1_2_3c = 3066.0;
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_2"), CComBSTR("Stage 1"), rsIncremental, lg1_2_1i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_2"), CComBSTR("Stage 1"), rsCumulative, lg1_2_1c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_2"), CComBSTR("Stage 2"), rsIncremental, lg1_2_2i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_2"), CComBSTR("Stage 2"), rsCumulative, lg1_2_2c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_2"), CComBSTR("Stage 3"), rsIncremental, lg1_2_3i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_2"), CComBSTR("Stage 3"), rsCumulative, lg1_2_3c);

      Float64 lg1_3_1i = 1031.0;
      Float64 lg1_3_1c = 1031.0;
      Float64 lg1_3_2i = 1032.0;
      Float64 lg1_3_2c = 2063.0;
      Float64 lg1_3_3i = 1033.0;
      Float64 lg1_3_3c = 3096.0;
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_3"), CComBSTR("Stage 1"), rsIncremental, lg1_3_1i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_3"), CComBSTR("Stage 1"), rsCumulative, lg1_3_1c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_3"), CComBSTR("Stage 2"), rsIncremental, lg1_3_2i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_3"), CComBSTR("Stage 2"), rsCumulative, lg1_3_2c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_3"), CComBSTR("Stage 3"), rsIncremental, lg1_3_3i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg1_3"), CComBSTR("Stage 3"), rsCumulative, lg1_3_3c);

      Float64 lg2_1_1i =  2011.0;
      Float64 lg2_1_1c =  2011.0;
      Float64 lg2_1_2i = -2012.0;
      Float64 lg2_1_2c =    -1.0;
      Float64 lg2_1_3i = -2013.0;
      Float64 lg2_1_3c = -2014.0;
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_1"), CComBSTR("Stage 1"), rsIncremental, lg2_1_1i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_1"), CComBSTR("Stage 1"), rsCumulative, lg2_1_1c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_1"), CComBSTR("Stage 2"), rsIncremental, lg2_1_2i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_1"), CComBSTR("Stage 2"), rsCumulative, lg2_1_2c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_1"), CComBSTR("Stage 3"), rsIncremental, lg2_1_3i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_1"), CComBSTR("Stage 3"), rsCumulative, lg2_1_3c);

      Float64 lg2_2_1i =  2021.0;
      Float64 lg2_2_1c =  2021.0;
      Float64 lg2_2_2i = -2022.0;
      Float64 lg2_2_2c =    -1.0;
      Float64 lg2_2_3i = -2023.0;
      Float64 lg2_2_3c = -2024.0;
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_2"), CComBSTR("Stage 1"), rsIncremental, lg2_2_1i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_2"), CComBSTR("Stage 1"), rsCumulative, lg2_2_1c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_2"), CComBSTR("Stage 2"), rsIncremental, lg2_2_2i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_2"), CComBSTR("Stage 2"), rsCumulative, lg2_2_2c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_2"), CComBSTR("Stage 3"), rsIncremental, lg2_2_3i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg2_2"), CComBSTR("Stage 3"), rsCumulative, lg2_2_3c);

      Float64 lg3_1_1i =-3011.0;
      Float64 lg3_1_1c =-3011.0;
      Float64 lg3_1_2i = 3012.0;
      Float64 lg3_1_2c =    1.0;
      Float64 lg3_1_3i = 3013.0;
      Float64 lg3_1_3c = 3014.0;
      p1bm.SetLoadGroupValue(CComBSTR("Lg3_1"), CComBSTR("Stage 1"), rsIncremental, lg3_1_1i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg3_1"), CComBSTR("Stage 1"), rsCumulative, lg3_1_1c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg3_1"), CComBSTR("Stage 2"), rsIncremental, lg3_1_2i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg3_1"), CComBSTR("Stage 2"), rsCumulative, lg3_1_2c);
      p1bm.SetLoadGroupValue(CComBSTR("Lg3_1"), CComBSTR("Stage 3"), rsIncremental, lg3_1_3i);
      p1bm.SetLoadGroupValue(CComBSTR("Lg3_1"), CComBSTR("Stage 3"), rsCumulative, lg3_1_3c);

      // load group stresses
      Float64 lg1_1_1s1i = lg1_1_1i*(stg1_sa1+stg1_sm1);
      Float64 lg1_1_1s2i = lg1_1_1i*(stg1_sa2+stg1_sm2);
      Float64 lg1_1_1s1c = lg1_1_1s1i;
      Float64 lg1_1_1s2c = lg1_1_1s2i;
      Float64 lg1_1_2s1i = lg1_1_2i*(stg2_sa1+stg2_sm1);
      Float64 lg1_1_2s2i = lg1_1_2i*(stg2_sa2+stg2_sm2);
      Float64 lg1_1_2s1c = lg1_1_1s1i + lg1_1_2s1i;
      Float64 lg1_1_2s2c = lg1_1_1s2i + lg1_1_2s2i;
      Float64 lg1_1_3s1i = lg1_1_3i*(stg3_sa1+stg3_sm1);
      Float64 lg1_1_3s2i = lg1_1_3i*(stg3_sa2+stg3_sm2);
      Float64 lg1_1_3s1c = lg1_1_1s1i + lg1_1_2s1i + lg1_1_3s1i;
      Float64 lg1_1_3s2c = lg1_1_1s2i + lg1_1_2s2i + lg1_1_3s2i;
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_1"), CComBSTR("Stage 1"), rsIncremental, lg1_1_1s1i, lg1_1_1s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_1"), CComBSTR("Stage 1"), rsCumulative, lg1_1_1s1c, lg1_1_1s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_1"), CComBSTR("Stage 2"), rsIncremental, lg1_1_2s1i, lg1_1_2s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_1"), CComBSTR("Stage 2"), rsCumulative, lg1_1_2s1c, lg1_1_2s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_1"), CComBSTR("Stage 3"), rsIncremental, lg1_1_3s1i, lg1_1_3s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_1"), CComBSTR("Stage 3"), rsCumulative, lg1_1_3s1c, lg1_1_3s2c);

      Float64 lg1_2_1s1i = lg1_2_1i*(stg1_sa1+stg1_sm1);
      Float64 lg1_2_1s2i = lg1_2_1i*(stg1_sa2+stg1_sm2);
      Float64 lg1_2_1s1c = lg1_2_1s1i;
      Float64 lg1_2_1s2c = lg1_2_1s2i;
      Float64 lg1_2_2s1i = lg1_2_2i*(stg2_sa1+stg2_sm1);
      Float64 lg1_2_2s2i = lg1_2_2i*(stg2_sa2+stg2_sm2);
      Float64 lg1_2_2s1c = lg1_2_1s1i + lg1_2_2s1i;
      Float64 lg1_2_2s2c = lg1_2_1s2i + lg1_2_2s2i;
      Float64 lg1_2_3s1i = lg1_2_3i*(stg3_sa1+stg3_sm1);
      Float64 lg1_2_3s2i = lg1_2_3i*(stg3_sa2+stg3_sm2);
      Float64 lg1_2_3s1c = lg1_2_1s1i + lg1_2_2s1i + lg1_2_3s1i;
      Float64 lg1_2_3s2c = lg1_2_1s2i + lg1_2_2s2i + lg1_2_3s2i;
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_2"), CComBSTR("Stage 1"), rsIncremental, lg1_2_1s1i, lg1_2_1s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_2"), CComBSTR("Stage 1"), rsCumulative, lg1_2_1s1c, lg1_2_1s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_2"), CComBSTR("Stage 2"), rsIncremental, lg1_2_2s1i, lg1_2_2s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_2"), CComBSTR("Stage 2"), rsCumulative, lg1_2_2s1c, lg1_2_2s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_2"), CComBSTR("Stage 3"), rsIncremental, lg1_2_3s1i, lg1_2_3s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_2"), CComBSTR("Stage 3"), rsCumulative, lg1_2_3s1c, lg1_2_3s2c);

      Float64 lg1_3_1s1i = lg1_3_1i*(stg1_sa1+stg1_sm1);
      Float64 lg1_3_1s2i = lg1_3_1i*(stg1_sa2+stg1_sm2);
      Float64 lg1_3_1s1c = lg1_3_1s1i;
      Float64 lg1_3_1s2c = lg1_3_1s2i;
      Float64 lg1_3_2s1i = lg1_3_2i*(stg2_sa1+stg2_sm1);
      Float64 lg1_3_2s2i = lg1_3_2i*(stg2_sa2+stg2_sm2);
      Float64 lg1_3_2s1c = lg1_3_1s1i + lg1_3_2s1i;
      Float64 lg1_3_2s2c = lg1_3_1s2i + lg1_3_2s2i;
      Float64 lg1_3_3s1i = lg1_3_3i*(stg3_sa1+stg3_sm1);
      Float64 lg1_3_3s2i = lg1_3_3i*(stg3_sa2+stg3_sm2);
      Float64 lg1_3_3s1c = lg1_3_1s1i + lg1_3_2s1i + lg1_3_3s1i;
      Float64 lg1_3_3s2c = lg1_3_1s2i + lg1_3_2s2i + lg1_3_3s2i;
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_3"), CComBSTR("Stage 1"), rsIncremental, lg1_3_1s1i, lg1_3_1s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_3"), CComBSTR("Stage 1"), rsCumulative, lg1_3_1s1c, lg1_3_1s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_3"), CComBSTR("Stage 2"), rsIncremental, lg1_3_2s1i, lg1_3_2s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_3"), CComBSTR("Stage 2"), rsCumulative, lg1_3_2s1c, lg1_3_2s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_3"), CComBSTR("Stage 3"), rsIncremental, lg1_3_3s1i, lg1_3_3s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg1_3"), CComBSTR("Stage 3"), rsCumulative, lg1_3_3s1c, lg1_3_3s2c);

      Float64 lg2_1_1s1i = lg2_1_1i*(stg1_sa1+stg1_sm1);
      Float64 lg2_1_1s2i = lg2_1_1i*(stg1_sa2+stg1_sm2);
      Float64 lg2_1_1s1c = lg2_1_1s1i;
      Float64 lg2_1_1s2c = lg2_1_1s2i;
      Float64 lg2_1_2s1i = lg2_1_2i*(stg2_sa1+stg2_sm1);
      Float64 lg2_1_2s2i = lg2_1_2i*(stg2_sa2+stg2_sm2);
      Float64 lg2_1_2s1c = lg2_1_1s1i + lg2_1_2s1i;
      Float64 lg2_1_2s2c = lg2_1_1s2i + lg2_1_2s2i;
      Float64 lg2_1_3s1i = lg2_1_3i*(stg3_sa1+stg3_sm1);
      Float64 lg2_1_3s2i = lg2_1_3i*(stg3_sa2+stg3_sm2);
      Float64 lg2_1_3s1c = lg2_1_1s1i + lg2_1_2s1i + lg2_1_3s1i;
      Float64 lg2_1_3s2c = lg2_1_1s2i + lg2_1_2s2i + lg2_1_3s2i;
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_1"), CComBSTR("Stage 1"), rsIncremental, lg2_1_1s1i, lg2_1_1s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_1"), CComBSTR("Stage 1"), rsCumulative, lg2_1_1s1c, lg2_1_1s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_1"), CComBSTR("Stage 2"), rsIncremental, lg2_1_2s1i, lg2_1_2s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_1"), CComBSTR("Stage 2"), rsCumulative, lg2_1_2s1c, lg2_1_2s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_1"), CComBSTR("Stage 3"), rsIncremental, lg2_1_3s1i, lg2_1_3s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_1"), CComBSTR("Stage 3"), rsCumulative, lg2_1_3s1c, lg2_1_3s2c);
      
      Float64 lg2_2_1s1i = lg2_2_1i*(stg1_sa1+stg1_sm1);
      Float64 lg2_2_1s2i = lg2_2_1i*(stg1_sa2+stg1_sm2);
      Float64 lg2_2_1s1c = lg2_2_1s1i;
      Float64 lg2_2_1s2c = lg2_2_1s2i;
      Float64 lg2_2_2s1i = lg2_2_2i*(stg2_sa1+stg2_sm1);
      Float64 lg2_2_2s2i = lg2_2_2i*(stg2_sa2+stg2_sm2);
      Float64 lg2_2_2s1c = lg2_2_1s1i + lg2_2_2s1i;
      Float64 lg2_2_2s2c = lg2_2_1s2i + lg2_2_2s2i;
      Float64 lg2_2_3s1i = lg2_2_3i*(stg3_sa1+stg3_sm1);
      Float64 lg2_2_3s2i = lg2_2_3i*(stg3_sa2+stg3_sm2);
      Float64 lg2_2_3s1c = lg2_2_1s1i + lg2_2_2s1i + lg2_2_3s1i;
      Float64 lg2_2_3s2c = lg2_2_1s2i + lg2_2_2s2i + lg2_2_3s2i;
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_2"), CComBSTR("Stage 1"), rsIncremental, lg2_2_1s1i, lg2_2_1s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_2"), CComBSTR("Stage 1"), rsCumulative, lg2_2_1s1c, lg2_2_1s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_2"), CComBSTR("Stage 2"), rsIncremental, lg2_2_2s1i, lg2_2_2s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_2"), CComBSTR("Stage 2"), rsCumulative, lg2_2_2s1c, lg2_2_2s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_2"), CComBSTR("Stage 3"), rsIncremental, lg2_2_3s1i, lg2_2_3s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg2_2"), CComBSTR("Stage 3"), rsCumulative, lg2_2_3s1c, lg2_2_3s2c);

      Float64 lg3_1_1s1i = lg3_1_1i*(stg1_sa1+stg1_sm1);
      Float64 lg3_1_1s2i = lg3_1_1i*(stg1_sa2+stg1_sm2);
      Float64 lg3_1_1s1c = lg3_1_1s1i;
      Float64 lg3_1_1s2c = lg3_1_1s2i;
      Float64 lg3_1_2s1i = lg3_1_2i*(stg2_sa1+stg2_sm1);
      Float64 lg3_1_2s2i = lg3_1_2i*(stg2_sa2+stg2_sm2);
      Float64 lg3_1_2s1c = lg3_1_1s1i + lg3_1_2s1i;
      Float64 lg3_1_2s2c = lg3_1_1s2i + lg3_1_2s2i;
      Float64 lg3_1_3s1i = lg3_1_3i*(stg3_sa1+stg3_sm1);
      Float64 lg3_1_3s2i = lg3_1_3i*(stg3_sa2+stg3_sm2);
      Float64 lg3_1_3s1c = lg3_1_1s1i + lg3_1_2s1i + lg3_1_3s1i;
      Float64 lg3_1_3s2c = lg3_1_1s2i + lg3_1_2s2i + lg3_1_3s2i;
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg3_1"), CComBSTR("Stage 1"), rsIncremental, lg3_1_1s1i, lg3_1_1s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg3_1"), CComBSTR("Stage 1"), rsCumulative, lg3_1_1s1c, lg3_1_1s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg3_1"), CComBSTR("Stage 2"), rsIncremental, lg3_1_2s1i, lg3_1_2s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg3_1"), CComBSTR("Stage 2"), rsCumulative, lg3_1_2s1c, lg3_1_2s2c);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg3_1"), CComBSTR("Stage 3"), rsIncremental, lg3_1_3s1i, lg3_1_3s2i);
      p1bm.SetLoadGroupStressValue(CComBSTR("Lg3_1"), CComBSTR("Stage 3"), rsCumulative, lg3_1_3s1c, lg3_1_3s2c);
      // Load Cases
      // do calcs for load cases in-line here
      Float64 lc1_1_i = lg1_1_1i + lg1_2_1i + lg1_3_1i;
      Float64 lc1_1_c = lc1_1_i;
      Float64 lc1_2_i = lg1_1_2i + lg1_2_2i + lg1_3_2i;
      Float64 lc1_2_c = lc1_1_i + lc1_2_i;
      Float64 lc1_3_i = lg1_1_3i + lg1_2_3i + lg1_3_3i;
      Float64 lc1_3_c = lc1_1_i + lc1_2_i + lc1_3_i;
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 1"), rsIncremental, lc1_1_i);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 1"), rsCumulative, lc1_1_c);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 2"), rsIncremental, lc1_2_i);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 2"), rsCumulative, lc1_2_c);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 3"), rsIncremental, lc1_3_i);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 3"), rsCumulative, lc1_3_c);

      Float64 lc2_1_i = lg2_1_1i + lg2_2_1i;
      Float64 lc2_1_c = lc2_1_i;
      Float64 lc2_2_i = lg2_1_2i + lg2_2_2i;
      Float64 lc2_2_c = lc2_1_i + lc2_2_i;
      Float64 lc2_3_i = lg2_1_3i + lg2_2_3i;
      Float64 lc2_3_c = lc2_1_i + lc2_2_i + lc2_3_i;
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 1"), rsIncremental, lc2_1_i);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 1"), rsCumulative, lc2_1_c);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 2"), rsIncremental, lc2_2_i);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 2"), rsCumulative, lc2_2_c);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 3"), rsIncremental, lc2_3_i);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 3"), rsCumulative, lc2_3_c);

      Float64 lc3_1_i = lg3_1_1i;
      Float64 lc3_1_c = lc3_1_i;
      Float64 lc3_2_i = 3012.0;
      Float64 lc3_2_c = lc3_1_i + lc3_2_i;
      Float64 lc3_3_i = 3013.0;
      Float64 lc3_3_c = lc3_1_i + lc3_2_i + lc3_3_i;
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 1"), rsIncremental, lc3_1_i);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 1"), rsCumulative, lc3_1_c);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 2"), rsIncremental, lc3_2_i);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 2"), rsCumulative, lc3_2_c);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 3"), rsIncremental, lc3_3_i);
      p1bm.SetLoadCaseBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 3"), rsCumulative, lc3_3_c);

      // load case stresses
      Float64 lc1s1_1_i = lc1_1_i*(stg1_sa1+stg1_sm1);
      Float64 lc1s1_1_c = lc1s1_1_i;
      Float64 lc1s2_1_i = lc1_1_i*(stg1_sa2+stg1_sm2);
      Float64 lc1s2_1_c = lc1s2_1_i;
      Float64 lc1s1_2_i = lc1_2_i*(stg2_sa1+stg2_sm1);
      Float64 lc1s1_2_c = lc1s1_1_i + lc1s1_2_i;
      Float64 lc1s2_2_i = lc1_2_i*(stg2_sa2+stg2_sm2);
      Float64 lc1s2_2_c = lc1s2_1_i + lc1s2_2_i;
      Float64 lc1s1_3_i = lc1_3_i*(stg3_sa1+stg3_sm1);
      Float64 lc1s1_3_c = lc1s1_1_i + lc1s1_2_i + lc1s1_3_i;
      Float64 lc1s2_3_i = lc1_3_i*(stg3_sa2+stg3_sm2);
      Float64 lc1s2_3_c = lc1s2_1_i + lc1s2_2_i + lc1s2_3_i;
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 1"), rsIncremental, lc1s1_1_i, lc1s2_1_i);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 1"), rsCumulative, lc1s1_1_c, lc1s2_1_c);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 2"), rsIncremental, lc1s1_2_i, lc1s2_2_i);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 2"), rsCumulative, lc1s1_2_c, lc1s2_2_c);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 3"), rsIncremental, lc1s1_3_i, lc1s2_3_i);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 1"), CComBSTR("Stage 3"), rsCumulative, lc1s1_3_c, lc1s2_3_c);

      Float64 lc2s1_1_i = lc2_1_i*(stg1_sa1+stg1_sm1);
      Float64 lc2s1_1_c = lc2s1_1_i;
      Float64 lc2s2_1_i = lc2_1_i*(stg1_sa2+stg1_sm2);
      Float64 lc2s2_1_c = lc2s2_1_i;
      Float64 lc2s1_2_i = lc2_2_i*(stg2_sa1+stg2_sm1);
      Float64 lc2s1_2_c = lc2s1_1_i + lc2s1_2_i;
      Float64 lc2s2_2_i = lc2_2_i*(stg2_sa2+stg2_sm2);
      Float64 lc2s2_2_c = lc2s2_1_i + lc2s2_2_i;
      Float64 lc2s1_3_i = lc2_3_i*(stg3_sa1+stg3_sm1);
      Float64 lc2s1_3_c = lc2s1_1_i + lc2s1_2_i + lc2s1_3_i;
      Float64 lc2s2_3_i = lc2_3_i*(stg3_sa2+stg3_sm2);
      Float64 lc2s2_3_c = lc2s2_1_i + lc2s2_2_i + lc2s2_3_i;
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 1"), rsIncremental, lc2s1_1_i, lc2s2_1_i);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 1"), rsCumulative, lc2s1_1_c, lc2s2_1_c);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 2"), rsIncremental, lc2s1_2_i, lc2s2_2_i);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 2"), rsCumulative, lc2s1_2_c, lc2s2_2_c);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 3"), rsIncremental, lc2s1_3_i, lc2s2_3_i);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 2"), CComBSTR("Stage 3"), rsCumulative, lc2s1_3_c, lc2s2_3_c);

      Float64 lc3s1_1_i = lc3_1_i*(stg1_sa1+stg1_sm1);
      Float64 lc3s1_1_c = lc3s1_1_i;
      Float64 lc3s2_1_i = lc3_1_i*(stg1_sa2+stg1_sm2);
      Float64 lc3s2_1_c = lc3s2_1_i;
      Float64 lc3s1_2_i = lc3_2_i*(stg2_sa1+stg2_sm1);
      Float64 lc3s1_2_c = lc3s1_1_i + lc3s1_2_i;
      Float64 lc3s2_2_i = lc3_2_i*(stg2_sa2+stg2_sm2);
      Float64 lc3s2_2_c = lc3s2_1_i + lc3s2_2_i;
      Float64 lc3s1_3_i = lc3_3_i*(stg3_sa1+stg3_sm1);
      Float64 lc3s1_3_c = lc3s1_1_i + lc3s1_2_i + lc3s1_3_i;
      Float64 lc3s2_3_i = lc3_3_i*(stg3_sa2+stg3_sm2);
      Float64 lc3s2_3_c = lc3s2_1_i + lc3s2_2_i + lc3s2_3_i;
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 1"), rsIncremental, lc3s1_1_i, lc3s2_1_i);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 1"), rsCumulative, lc3s1_1_c, lc3s2_1_c);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 2"), rsIncremental, lc3s1_2_i, lc3s2_2_i);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 2"), rsCumulative, lc3s1_2_c, lc3s2_2_c);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 3"), rsIncremental, lc3s1_3_i, lc3s2_3_i);
      p1bm.SetLoadCaseStressBenchMark(CComBSTR("Load Case 3"), CComBSTR("Stage 3"), rsCumulative, lc3s1_3_c, lc3s2_3_c);

      // Load Combinations
      Float64 cb1_1_mn_i = fct_cb1_lc1_mn*lc1_1_i + fct_cb1_lc2_mn*lc2_1_i + fct_cb1_lc3_mx*lc3_1_i;
      Float64 cb1_1_mx_i = fct_cb1_lc1_mx*lc1_1_i + fct_cb1_lc2_mx*lc2_1_i + fct_cb1_lc3_mn*lc3_1_i;
      Float64 cb1_1_mn_c = cb1_1_mn_i;
      Float64 cb1_1_mx_c = cb1_1_mx_i;
      Float64 cb1_2_mn_i = fct_cb1_lc1_mn*lc1_2_i + fct_cb1_lc2_mx*lc2_2_i + fct_cb1_lc3_mn*lc3_2_i;
      Float64 cb1_2_mx_i = fct_cb1_lc1_mx*lc1_2_i + fct_cb1_lc2_mn*lc2_2_i + fct_cb1_lc3_mx*lc3_2_i;
      Float64 cb1_2_mn_c = fct_cb1_lc1_mn*lc1_2_c + fct_cb1_lc2_mx*lc2_2_c + fct_cb1_lc3_mn*lc3_2_c;
      Float64 cb1_2_mx_c = fct_cb1_lc1_mx*lc1_2_c + fct_cb1_lc2_mn*lc2_2_c + fct_cb1_lc3_mx*lc3_2_c;
      Float64 cb1_3_mn_i = fct_cb1_lc1_mn*lc1_3_i + fct_cb1_lc2_mx*lc2_3_i + fct_cb1_lc3_mn*lc3_3_i + fct_cb1_ll*ll_min;
      Float64 cb1_3_mx_i = fct_cb1_lc1_mx*lc1_3_i + fct_cb1_lc2_mn*lc2_3_i + fct_cb1_lc3_mx*lc3_3_i + fct_cb1_ll*ll_max;
      Float64 cb1_3_mn_c = fct_cb1_lc1_mn*lc1_3_c + fct_cb1_lc2_mx*lc2_3_c + fct_cb1_lc3_mn*lc3_3_c + fct_cb1_ll*ll_min;
      Float64 cb1_3_mx_c = fct_cb1_lc1_mx*lc1_3_c + fct_cb1_lc2_mn*lc2_3_c + fct_cb1_lc3_mx*lc3_3_c + fct_cb1_ll*ll_max;
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 1"), rsIncremental, cb1_1_mn_i, cb1_1_mx_i);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 1"), rsCumulative, cb1_1_mn_c, cb1_1_mx_c);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 2"), rsIncremental, cb1_2_mn_i, cb1_2_mx_i);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 2"), rsCumulative, cb1_2_mn_c, cb1_2_mx_c);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 3"), rsIncremental, cb1_3_mn_i, cb1_3_mx_i);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 3"), rsCumulative, cb1_3_mn_c, cb1_3_mx_c);

      Float64 cb2_1_mn_i = fct_cb2_lc1_mn*lc1_1_i;
      Float64 cb2_1_mx_i = fct_cb2_lc1_mx*lc1_1_i;
      Float64 cb2_1_mn_c = cb2_1_mn_i;
      Float64 cb2_1_mx_c = cb2_1_mx_i;
      Float64 cb2_2_mn_i = fct_cb2_lc1_mn*lc1_2_i;
      Float64 cb2_2_mx_i = fct_cb2_lc1_mn*lc1_2_i;
      Float64 cb2_2_mn_c = fct_cb2_lc1_mn*lc1_2_c;
      Float64 cb2_2_mx_c = fct_cb2_lc1_mx*lc1_2_c;
      Float64 cb2_3_mn_i = fct_cb2_lc1_mn*lc1_3_i + fct_cb2_ll*ll_min;
      Float64 cb2_3_mx_i = fct_cb2_lc1_mn*lc1_3_i + fct_cb2_ll*ll_max;
      Float64 cb2_3_mn_c = fct_cb2_lc1_mn*lc1_3_c + fct_cb2_ll*ll_min;
      Float64 cb2_3_mx_c = fct_cb2_lc1_mx*lc1_3_c + fct_cb2_ll*ll_max;
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 1"), rsIncremental, cb2_1_mn_i, cb2_1_mx_i);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 1"), rsCumulative, cb2_1_mn_c, cb2_1_mx_c);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 2"), rsIncremental, cb2_2_mn_i, cb2_2_mx_i);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 2"), rsCumulative, cb2_2_mn_c, cb2_2_mx_c);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 3"), rsIncremental, cb2_3_mn_i, cb2_3_mx_i);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 3"), rsCumulative, cb2_3_mn_c, cb2_3_mx_c);

      Float64 cb3_1_mn_i = fct_cb3_lc3_mx*lc3_1_i;
      Float64 cb3_1_mx_i = fct_cb3_lc3_mn*lc3_1_i;
      Float64 cb3_1_mn_c = cb3_1_mn_i;
      Float64 cb3_1_mx_c = cb3_1_mx_i;
      Float64 cb3_2_mn_i = fct_cb3_lc3_mn*lc3_2_i;
      Float64 cb3_2_mx_i = fct_cb3_lc3_mx*lc3_2_i;
      Float64 cb3_2_mn_c = fct_cb3_lc3_mn*lc3_2_c;
      Float64 cb3_2_mx_c = fct_cb3_lc3_mx*lc3_2_c;
      Float64 cb3_3_mn_i = fct_cb3_lc3_mn*lc3_3_i + fct_cb3_ll*ll_min;
      Float64 cb3_3_mx_i = fct_cb3_lc3_mx*lc3_3_i + fct_cb3_ll*ll_max;
      Float64 cb3_3_mn_c = fct_cb3_lc3_mn*lc3_3_c + fct_cb3_ll*ll_min;
      Float64 cb3_3_mx_c = fct_cb3_lc3_mx*lc3_3_c + fct_cb3_ll*ll_max;
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 1"), rsIncremental, cb3_1_mn_i, cb3_1_mx_i);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 1"), rsCumulative, cb3_1_mn_c, cb3_1_mx_c);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 2"), rsIncremental, cb3_2_mn_i, cb3_2_mx_i);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 2"), rsCumulative, cb3_2_mn_c, cb3_2_mx_c);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 3"), rsIncremental, cb3_3_mn_i, cb3_3_mx_i);
      p1bm.SetCombinedBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 3"), rsCumulative, cb3_3_mn_c, cb3_3_mx_c);

      // combined stresses
      // Cumulative combined stresses are a nightmare because we have to look at the signs of the 
      // cumulative combined forces in order to determine which combination factors to use. 
      // We can't just accumulate incremental stresses
      Float64 stg1_sf1 = stg1_sa1+stg1_sm1; // we can take this shortcut because all force values are equal in our test 
      Float64 stg1_sf2 = stg1_sa2+stg1_sm2;
      Float64 stg2_sf1 = stg2_sa1+stg2_sm1;
      Float64 stg2_sf2 = stg2_sa2+stg2_sm2;
      Float64 stg3_sf1 = stg3_sa1+stg3_sm1;
      Float64 stg3_sf2 = stg3_sa2+stg3_sm2;

      Float64 cb1_1_mn_i_sp1 = cb1_1_mn_i*stg1_sf1;
      Float64 cb1_1_mn_i_sp2 = cb1_1_mn_i*stg1_sf2;
      Float64 cb1_1_mx_i_sp1 = cb1_1_mx_i*stg1_sf1;
      Float64 cb1_1_mx_i_sp2 = cb1_1_mx_i*stg1_sf2;
      Float64 cb1_1_mn_c_sp1 = cb1_1_mn_i_sp1;
      Float64 cb1_1_mn_c_sp2 = cb1_1_mn_i_sp2;
      Float64 cb1_1_mx_c_sp1 = cb1_1_mx_i_sp1;
      Float64 cb1_1_mx_c_sp2 = cb1_1_mx_i_sp2;
      Float64 cb1_2_mn_i_sp1 = cb1_2_mn_i*stg2_sf1;
      Float64 cb1_2_mn_i_sp2 = cb1_2_mn_i*stg2_sf2;
      Float64 cb1_2_mx_i_sp1 = cb1_2_mx_i*stg2_sf1;
      Float64 cb1_2_mx_i_sp2 = cb1_2_mx_i*stg2_sf2;
      // factors are chosen based on those used in force combination
      Float64 cb1_2_mn_c_sp1 = fct_cb1_lc1_mn*(lc1_1_i*stg1_sf1 + lc1_2_i*stg2_sf1) + 
                              fct_cb1_lc2_mx*(lc2_1_i*stg1_sf1 + lc2_2_i*stg2_sf1) +
                              fct_cb1_lc3_mn*(lc3_1_i*stg1_sf1 + lc3_2_i*stg2_sf1);
      Float64 cb1_2_mn_c_sp2 = fct_cb1_lc1_mn*(lc1_1_i*stg1_sf2 + lc1_2_i*stg2_sf2) + 
                              fct_cb1_lc2_mx*(lc2_1_i*stg1_sf2 + lc2_2_i*stg2_sf2) +
                              fct_cb1_lc3_mn*(lc3_1_i*stg1_sf2 + lc3_2_i*stg2_sf2);
      Float64 cb1_2_mx_c_sp1 = fct_cb1_lc1_mx*(lc1_1_i*stg1_sf1 + lc1_2_i*stg2_sf1) + 
                              fct_cb1_lc2_mn*(lc2_1_i*stg1_sf1 + lc2_2_i*stg2_sf1) +
                              fct_cb1_lc3_mx*(lc3_1_i*stg1_sf1 + lc3_2_i*stg2_sf1);
      Float64 cb1_2_mx_c_sp2 = fct_cb1_lc1_mx*(lc1_1_i*stg1_sf2 + lc1_2_i*stg2_sf2) + 
                              fct_cb1_lc2_mn*(lc2_1_i*stg1_sf2 + lc2_2_i*stg2_sf2) +
                              fct_cb1_lc3_mx*(lc3_1_i*stg1_sf2 + lc3_2_i*stg2_sf2);
      Float64 cb1_3_mn_i_sp1 = cb1_3_mn_i*(stg3_sa1+stg3_sm1);
      Float64 cb1_3_mn_i_sp2 = cb1_3_mn_i*(stg3_sa2+stg3_sm2);
      Float64 cb1_3_mx_i_sp1 = cb1_3_mx_i*(stg3_sa1+stg3_sm1);
      Float64 cb1_3_mx_i_sp2 = cb1_3_mx_i*(stg3_sa2+stg3_sm2);
      Float64 cb1_3_mn_c_sp1 = fct_cb1_lc1_mn*(lc1_1_i*stg1_sf1 + lc1_2_i*stg2_sf1 + lc1_3_i*stg3_sf1) + 
                              fct_cb1_lc2_mx*(lc2_1_i*stg1_sf1 + lc2_2_i*stg2_sf1 + lc2_3_i*stg3_sf1) +
                              fct_cb1_lc3_mn*(lc3_1_i*stg1_sf1 + lc3_2_i*stg2_sf1 + lc3_3_i*stg3_sf1) +
                              fct_cb1_ll*ll_min*stg3_sf1;
      Float64 cb1_3_mn_c_sp2 = fct_cb1_lc1_mn*(lc1_1_i*stg1_sf2 + lc1_2_i*stg2_sf2 + lc1_3_i*stg3_sf2) + 
                              fct_cb1_lc2_mx*(lc2_1_i*stg1_sf2 + lc2_2_i*stg2_sf2 + lc2_3_i*stg3_sf2) +
                              fct_cb1_lc3_mn*(lc3_1_i*stg1_sf2 + lc3_2_i*stg2_sf2 + lc3_3_i*stg3_sf2) +
                              fct_cb1_ll*ll_min*stg3_sf2;
      Float64 cb1_3_mx_c_sp1 = fct_cb1_lc1_mx*(lc1_1_i*stg1_sf1 + lc1_2_i*stg2_sf1 + lc1_3_i*stg3_sf1) + 
                              fct_cb1_lc2_mn*(lc2_1_i*stg1_sf1 + lc2_2_i*stg2_sf1 + lc2_3_i*stg3_sf1) +
                              fct_cb1_lc3_mx*(lc3_1_i*stg1_sf1 + lc3_2_i*stg2_sf1 + lc3_3_i*stg3_sf1) +
                              fct_cb1_ll*ll_max*stg3_sf1;
      Float64 cb1_3_mx_c_sp2 = fct_cb1_lc1_mx*(lc1_1_i*stg1_sf2 + lc1_2_i*stg2_sf2 + lc1_3_i*stg3_sf2) + 
                              fct_cb1_lc2_mn*(lc2_1_i*stg1_sf2 + lc2_2_i*stg2_sf2 + lc2_3_i*stg3_sf2) +
                              fct_cb1_lc3_mx*(lc3_1_i*stg1_sf2 + lc3_2_i*stg2_sf2 + lc3_3_i*stg3_sf2) +
                              fct_cb1_ll*ll_max*stg3_sf2;
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 1"), rsIncremental, optMinimize, cb1_1_mn_i_sp1, cb1_1_mn_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 1"), rsIncremental, optMaximize, cb1_1_mx_i_sp1, cb1_1_mx_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 1"), rsCumulative, optMinimize, cb1_1_mn_c_sp1, cb1_1_mn_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 1"), rsCumulative, optMaximize, cb1_1_mx_c_sp1, cb1_1_mx_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 2"), rsIncremental, optMinimize, cb1_2_mn_i_sp1, cb1_2_mn_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 2"), rsIncremental, optMaximize, cb1_2_mx_i_sp1, cb1_2_mx_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 2"), rsCumulative, optMinimize, cb1_2_mn_c_sp1, cb1_2_mn_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 2"), rsCumulative, optMaximize, cb1_2_mx_c_sp1, cb1_2_mx_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 3"), rsIncremental, optMinimize, cb1_3_mn_i_sp1, cb1_3_mn_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 3"), rsIncremental, optMaximize, cb1_3_mx_i_sp1, cb1_3_mx_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 3"), rsCumulative, optMinimize, cb1_3_mn_c_sp1, cb1_3_mn_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 1"), CComBSTR("Stage 3"), rsCumulative, optMaximize, cb1_3_mx_c_sp1, cb1_3_mx_c_sp2);

      Float64 cb2_1_mn_i_sp1 = cb2_1_mn_i*stg1_sf1;
      Float64 cb2_1_mn_i_sp2 = cb2_1_mn_i*stg1_sf2;
      Float64 cb2_1_mx_i_sp1 = cb2_1_mx_i*stg1_sf1;
      Float64 cb2_1_mx_i_sp2 = cb2_1_mx_i*stg1_sf2;
      Float64 cb2_1_mn_c_sp1 = cb2_1_mn_i_sp1;
      Float64 cb2_1_mn_c_sp2 = cb2_1_mn_i_sp2;
      Float64 cb2_1_mx_c_sp1 = cb2_1_mx_i_sp1;
      Float64 cb2_1_mx_c_sp2 = cb2_1_mx_i_sp2;
      Float64 cb2_2_mn_i_sp1 = cb2_2_mn_i*stg2_sf1;
      Float64 cb2_2_mn_i_sp2 = cb2_2_mn_i*stg2_sf2;
      Float64 cb2_2_mx_i_sp1 = cb2_2_mx_i*stg2_sf1;
      Float64 cb2_2_mx_i_sp2 = cb2_2_mx_i*stg2_sf2;
      Float64 cb2_2_mn_c_sp1 = fct_cb2_lc1_mn*(lc1_1_i*stg1_sf1 + lc1_2_i*stg2_sf1);
      Float64 cb2_2_mn_c_sp2 = fct_cb2_lc1_mn*(lc1_1_i*stg1_sf2 + lc1_2_i*stg2_sf2);
      Float64 cb2_2_mx_c_sp1 = fct_cb2_lc1_mx*(lc1_1_i*stg1_sf1 + lc1_2_i*stg2_sf1);
      Float64 cb2_2_mx_c_sp2 = fct_cb2_lc1_mx*(lc1_1_i*stg1_sf2 + lc1_2_i*stg2_sf2);
      Float64 cb2_3_mn_i_sp1 = cb2_3_mn_i*stg3_sf1;
      Float64 cb2_3_mn_i_sp2 = cb2_3_mn_i*stg3_sf2;
      Float64 cb2_3_mx_i_sp1 = cb2_3_mx_i*stg3_sf1;
      Float64 cb2_3_mx_i_sp2 = cb2_3_mx_i*stg3_sf2;
      Float64 cb2_3_mn_c_sp1 = fct_cb2_lc1_mn*(lc1_1_i*stg1_sf1 + lc1_2_i*stg2_sf1 + lc1_3_i*stg3_sf1) + 
                              fct_cb2_ll*ll_min*stg3_sf1;
      Float64 cb2_3_mn_c_sp2 = fct_cb2_lc1_mn*(lc1_1_i*stg1_sf2 + lc1_2_i*stg2_sf2 + lc1_3_i*stg3_sf2) + 
                              fct_cb2_ll*ll_min*stg3_sf2;
      Float64 cb2_3_mx_c_sp1 = fct_cb2_lc1_mx*(lc1_1_i*stg1_sf1 + lc1_2_i*stg2_sf1 + lc1_3_i*stg3_sf1) + 
                              fct_cb2_ll*ll_max*stg3_sf1;
      Float64 cb2_3_mx_c_sp2 = fct_cb2_lc1_mx*(lc1_1_i*stg1_sf2 + lc1_2_i*stg2_sf2 + lc1_3_i*stg3_sf2) + 
                              fct_cb2_ll*ll_max*stg3_sf2;
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 1"), rsIncremental, optMinimize, cb2_1_mn_i_sp1, cb2_1_mn_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 1"), rsIncremental, optMaximize, cb2_1_mx_i_sp1, cb2_1_mx_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 1"), rsCumulative, optMinimize, cb2_1_mn_c_sp1, cb2_1_mn_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 1"), rsCumulative, optMaximize, cb2_1_mx_c_sp1, cb2_1_mx_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 2"), rsIncremental, optMinimize, cb2_2_mn_i_sp1, cb2_2_mn_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 2"), rsIncremental, optMaximize, cb2_2_mx_i_sp1, cb2_2_mx_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 2"), rsCumulative, optMinimize, cb2_2_mn_c_sp1, cb2_2_mn_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 2"), rsCumulative, optMaximize, cb2_2_mx_c_sp1, cb2_2_mx_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 3"), rsIncremental, optMinimize, cb2_3_mn_i_sp1, cb2_3_mn_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 3"), rsIncremental, optMaximize, cb2_3_mx_i_sp1, cb2_3_mx_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 3"), rsCumulative, optMinimize, cb2_3_mn_c_sp1, cb2_3_mn_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 2"), CComBSTR("Stage 3"), rsCumulative, optMaximize, cb2_3_mx_c_sp1, cb2_3_mx_c_sp2);

      Float64 cb3_1_mn_i_sp1 = cb3_1_mn_i*(stg1_sa1+stg1_sm1);
      Float64 cb3_1_mn_i_sp2 = cb3_1_mn_i*(stg1_sa2+stg1_sm2);
      Float64 cb3_1_mx_i_sp1 = cb3_1_mx_i*(stg1_sa1+stg1_sm1);
      Float64 cb3_1_mx_i_sp2 = cb3_1_mx_i*(stg1_sa2+stg1_sm2);
      Float64 cb3_1_mn_c_sp1 = cb3_1_mn_i_sp1;
      Float64 cb3_1_mn_c_sp2 = cb3_1_mn_i_sp2;
      Float64 cb3_1_mx_c_sp1 = cb3_1_mx_i_sp1;
      Float64 cb3_1_mx_c_sp2 = cb3_1_mx_i_sp2;
      Float64 cb3_2_mn_i_sp1 = cb3_2_mn_i*(stg2_sa1+stg2_sm1);
      Float64 cb3_2_mn_i_sp2 = cb3_2_mn_i*(stg2_sa2+stg2_sm2);
      Float64 cb3_2_mx_i_sp1 = cb3_2_mx_i*(stg2_sa1+stg2_sm1);
      Float64 cb3_2_mx_i_sp2 = cb3_2_mx_i*(stg2_sa2+stg2_sm2);
      Float64 cb3_2_mn_c_sp1 = fct_cb3_lc3_mn*(lc3_1_i*stg1_sf1 + lc3_2_i*stg2_sf1);
      Float64 cb3_2_mn_c_sp2 = fct_cb3_lc3_mn*(lc3_1_i*stg1_sf2 + lc3_2_i*stg2_sf2);
      Float64 cb3_2_mx_c_sp1 = fct_cb3_lc3_mx*(lc3_1_i*stg1_sf1 + lc3_2_i*stg2_sf1);
      Float64 cb3_2_mx_c_sp2 = fct_cb3_lc3_mx*(lc3_1_i*stg1_sf2 + lc3_2_i*stg2_sf2);
      Float64 cb3_3_mn_i_sp1 = cb3_3_mn_i*(stg3_sa1+stg3_sm1);
      Float64 cb3_3_mn_i_sp2 = cb3_3_mn_i*(stg3_sa2+stg3_sm2);
      Float64 cb3_3_mx_i_sp1 = cb3_3_mx_i*(stg3_sa1+stg3_sm1);
      Float64 cb3_3_mx_i_sp2 = cb3_3_mx_i*(stg3_sa2+stg3_sm2);
      Float64 cb3_3_mn_c_sp1 = fct_cb3_lc3_mn*(lc3_1_i*stg1_sf1 + lc3_2_i*stg2_sf1 + lc3_3_i*stg3_sf1) + 
                              fct_cb3_ll*ll_min*stg3_sf1;
      Float64 cb3_3_mn_c_sp2 = fct_cb3_lc3_mn*(lc3_1_i*stg1_sf2 + lc3_2_i*stg2_sf2 + lc3_3_i*stg3_sf2) + 
                              fct_cb3_ll*ll_min*stg3_sf2;
      Float64 cb3_3_mx_c_sp1 = fct_cb3_lc3_mx*(lc3_1_i*stg1_sf1 + lc3_2_i*stg2_sf1 + lc3_3_i*stg3_sf1) + 
                              fct_cb3_ll*ll_max*stg3_sf1;
      Float64 cb3_3_mx_c_sp2 = fct_cb3_lc3_mx*(lc3_1_i*stg1_sf2 + lc3_2_i*stg2_sf2 + lc3_3_i*stg3_sf2) + 
                              fct_cb3_ll*ll_max*stg3_sf2;
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 1"), rsIncremental, optMinimize, cb3_1_mn_i_sp1, cb3_1_mn_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 1"), rsIncremental, optMaximize, cb3_1_mx_i_sp1, cb3_1_mx_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 1"), rsCumulative, optMinimize, cb3_1_mn_c_sp1, cb3_1_mn_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 1"), rsCumulative, optMaximize, cb3_1_mx_c_sp1, cb3_1_mx_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 2"), rsIncremental, optMinimize, cb3_2_mn_i_sp1, cb3_2_mn_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 2"), rsIncremental, optMaximize, cb3_2_mx_i_sp1, cb3_2_mx_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 2"), rsCumulative, optMinimize, cb3_2_mn_c_sp1, cb3_2_mn_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 2"), rsCumulative, optMaximize, cb3_2_mx_c_sp1, cb3_2_mx_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 3"), rsIncremental, optMinimize, cb3_3_mn_i_sp1, cb3_3_mn_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 3"), rsIncremental, optMaximize, cb3_3_mx_i_sp1, cb3_3_mx_i_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 3"), rsCumulative, optMinimize, cb3_3_mn_c_sp1, cb3_3_mn_c_sp2);
      p1bm.SetCombinedStressBenchMark(CComBSTR("Load Combination 3"), CComBSTR("Stage 3"), rsCumulative, optMaximize, cb3_3_mx_c_sp1, cb3_3_mx_c_sp2);
   }
   catch(...)
   {
      ATLASSERT(false);
      return E_FAIL;
   }

   return S_OK;
}


// ILoadGroupResponse
STDMETHODIMP CBogusComboContext::ComputeForces(BSTR LoadGroup, IIDArray* POIs, BSTR stage, ResultsOrientation Orientation, ResultsSummationType summ, ISectionResult3Ds * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLoadGroupSectionValue(LoadGroup, stage, summ, true, Results);
   }

   return E_FAIL;
}
STDMETHODIMP CBogusComboContext::ComputeDeflections(BSTR LoadGroup, IIDArray* POIs, BSTR stage, ResultsSummationType summ, ISectionResult3Ds * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLoadGroupSectionValue(LoadGroup, stage, summ, false, Results);
   }

   return E_FAIL;
}
STDMETHODIMP CBogusComboContext::ComputeReactions(BSTR LoadGroup, IIDArray* POIs, BSTR stage, ResultsSummationType summ, IResult3Ds * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLoadGroupValue(LoadGroup, stage, summ, Results);
   }

   return E_FAIL;
}
STDMETHODIMP CBogusComboContext::ComputeSupportDeflections(BSTR LoadGroup, IIDArray* POIs, BSTR stage, ResultsSummationType summ, IResult3Ds * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLoadGroupValue(LoadGroup, stage, summ, Results);
   }

   return E_FAIL;
}
STDMETHODIMP CBogusComboContext::ComputeStresses(BSTR LoadGroup, IIDArray* POIs, BSTR stage, ResultsSummationType summ, ISectionStressResults * * results)
{
	if (results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLoadGroupStressValue(LoadGroup, stage, summ, results);
   }

   return E_FAIL;
}
// ILiveLoadModelResponse
STDMETHODIMP CBogusComboContext::ComputeForces(IIDArray* POIs, BSTR stage, LiveLoadModelType type, ResultsOrientation Orientation, ForceEffectType effect, OptimizationType Optimization, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, VARIANT_BOOL computePlacement, ILiveLoadModelSectionResults * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLiveLoadSectionValue(Optimization, true, Results);
   }

   return E_FAIL;
}
STDMETHODIMP CBogusComboContext::ComputeDeflections(IIDArray* POIs, BSTR stage, LiveLoadModelType type, ForceEffectType effect, OptimizationType Optimization, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, VARIANT_BOOL computePlacement, ILiveLoadModelSectionResults * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLiveLoadSectionValue(Optimization, false, Results);
   }

   return E_FAIL;
}
STDMETHODIMP CBogusComboContext::ComputeReactions(IIDArray* POIs, BSTR stage, LiveLoadModelType type, ForceEffectType effect, OptimizationType Optimization, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, VARIANT_BOOL computePlacement, ILiveLoadModelResults * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLiveLoadValue(Optimization, Results);
   }

   return E_FAIL;
}
STDMETHODIMP CBogusComboContext::ComputeSupportDeflections(IIDArray* POIs, BSTR stage, LiveLoadModelType type, ForceEffectType effect, OptimizationType Optimization, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, VARIANT_BOOL computePlacement, ILiveLoadModelResults * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLiveLoadValue(Optimization, Results);
   }

   return E_FAIL;
}
STDMETHODIMP CBogusComboContext::ComputeStresses(IIDArray* POIs, BSTR stage, LiveLoadModelType type, ForceEffectType effect, OptimizationType Optimization, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, VARIANT_BOOL computePlacement, ILiveLoadModelStressResults * * results)
{
	if (results == nullptr)
		return E_POINTER;

	return E_NOTIMPL;
}
// IBasicVehicularResponse
STDMETHODIMP CBogusComboContext::ComputeForces(IIDArray* POIs, BSTR stage, ResultsOrientation Orientation, ILiveLoadConfiguration * config, ISectionResult3Ds * * Results)
{
	if (Results == nullptr)
		return E_POINTER;

   PoiIDType poi;
   POIs->get_Item(0,&poi);

   OptimizationType optmization;
   config->get_Optimization(&optmization);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLiveLoadSectionValue(optmization, true, Results);
   }

	return E_FAIL;
}

STDMETHODIMP CBogusComboContext::ComputeDeflections(IIDArray* POIs, BSTR stage, ILiveLoadConfiguration * config, ISectionResult3Ds * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   OptimizationType optmization;
   config->get_Optimization(&optmization);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLiveLoadSectionValue(optmization, false, Results);
   }
		
	return E_FAIL;
}

STDMETHODIMP CBogusComboContext::ComputeReactions(IIDArray* POIs, BSTR stage, ILiveLoadConfiguration * config, IResult3Ds * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   OptimizationType optmization;
   config->get_Optimization(&optmization);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLiveLoadValue(optmization, Results);
   }

	return E_FAIL;
}

STDMETHODIMP CBogusComboContext::ComputeSupportDeflections(IIDArray* POIs, BSTR stage, ILiveLoadConfiguration * config, IResult3Ds * * Results)
{
	if (Results == nullptr)
		return E_POINTER;
		
   PoiIDType poi;
   POIs->get_Item(0,&poi);

   OptimizationType optmization;
   config->get_Optimization(&optmization);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLiveLoadValue(optmization, Results);
   }

	return E_FAIL;
}

STDMETHODIMP CBogusComboContext::ComputeStresses(IIDArray* POIs, BSTR stage, ILiveLoadConfiguration * config, ISectionStressResults * * results)
{
	if (results == nullptr)
		return E_POINTER;

   PoiIDType poi;
   POIs->get_Item(0,&poi);

   OptimizationType optmization;
   config->get_Optimization(&optmization);

   BenchMarkIterator it = m_BenchMarks.find(poi);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      return bm.GetLiveLoadStress(stage, optmization, results);
   }

   return E_FAIL;
}

// IGetActiveLoadGroups
STDMETHODIMP CBogusComboContext::GetActiveLoadGroups(IBstrArray* *loadGroups)
{
	if (loadGroups == nullptr)
		return E_POINTER;

   CComPtr<IBstrArray> groups;
   groups.CoCreateInstance(CLSID_BstrArray);
   groups->Reserve(6);

   groups->Add( CComBSTR("Lg1_1"));
   groups->Add( CComBSTR("Lg1_2"));
   groups->Add( CComBSTR("Lg1_3"));
   groups->Add( CComBSTR("Lg2_1"));
   groups->Add( CComBSTR("Lg2_2"));
   groups->Add( CComBSTR("Lg3_1"));

   *loadGroups = groups.Detach();
		
	return S_OK;
}
// IGetCombinationFactors
STDMETHODIMP CBogusComboContext::GetPOICombinationFactors(PoiIDType POI, BSTR stage, LoadCombinationType type, Float64 * minLoadModifier, Float64 * maxLoadModifier)
{
	if (minLoadModifier == nullptr)
		return E_POINTER;

	if (maxLoadModifier == nullptr)
		return E_POINTER;

   BenchMarkIterator it = m_BenchMarks.find(POI);
   if (it!=m_BenchMarks.end())
   {
      return it->second.GetCombinationFactors(stage, type, minLoadModifier, maxLoadModifier);
   }

	return E_FAIL;
}
STDMETHODIMP CBogusComboContext::GetSupportCombinationFactors(SupportIDType supportID, BSTR stage, LoadCombinationType type, Float64 * minLoadModifier, Float64 * maxLoadModifier)
{
	if (minLoadModifier == nullptr)
		return E_POINTER;
		
	if (maxLoadModifier == nullptr)
		return E_POINTER;
		
   BenchMarkIterator it = m_BenchMarks.find(supportID);
   if (it!=m_BenchMarks.end())
   {
      return it->second.GetCombinationFactors(stage, type, minLoadModifier, maxLoadModifier);
   }

	return E_FAIL;
}
// IAnalysisPOIs
STDMETHODIMP CBogusComboContext::get_SpanPoiIncrement(PoiIDType * pVal)
{
	if (pVal == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::put_SpanPoiIncrement(PoiIDType pVal)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::get_CantileverPoiIncrement(PoiIDType * pVal)
{
	if (pVal == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::put_CantileverPoiIncrement(PoiIDType pVal)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::GetSuperstructurePois(BSTR stage, IIDArray* *poiIDs, IDblArray* *poiLocations)
{
	if (poiIDs == nullptr)
		return E_POINTER;
		
	if (poiLocations == nullptr)
		return E_POINTER;

   // get poi id's from list of benchmarks
   CollectionIndexType siz = m_BenchMarks.size();

   CComPtr<IIDArray> pois;
   pois.CoCreateInstance(CLSID_IDArray);

   for (BenchMarkIterator it=m_BenchMarks.begin(); it!=m_BenchMarks.end(); it++)
   {
      pois->Add(it->first);
   }

   *poiIDs = pois.Detach();
   poiLocations = nullptr;

	return S_OK;
}
STDMETHODIMP CBogusComboContext::GetPoiInfo(BSTR stage, PoiIDType poiID, MemberType * lbamMemberType, MemberIDType * MemberID, Float64 * memberLocation)
{
	if (lbamMemberType == nullptr)
		return E_POINTER;
		
	if (MemberID == nullptr)
		return E_POINTER;
		
	if (memberLocation == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
// ILoadCases
STDMETHODIMP CBogusComboContext::get_Count(CollectionIndexType * pVal)
{
	if (pVal == nullptr)
		return E_POINTER;

   // NOTE: that the count is three for LoadCases, LoadCombinations, and Stages
   // If you want to make it different for each, you will need to use COM aggregation
   *pVal = 3;
		
	return S_OK;
}
STDMETHODIMP CBogusComboContext::get_Item(CollectionIndexType index, ILoadCase * * pVal)
{
	if (pVal == nullptr)
		return E_POINTER;

   if (index==0)
   {
      return m_LoadCase1.CopyTo(pVal);
   }
   else if (index==1)
   {
      return m_LoadCase2.CopyTo(pVal);
   }
   else if (index==2)
   {
      return m_LoadCase3.CopyTo(pVal);
   }
   else
   {
      ATLASSERT(false);
   }
		
	return E_FAIL;
}
STDMETHODIMP CBogusComboContext::get__NewEnum(IUnknown * * retval)
{
	if (retval == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::get__EnumElements(IEnumLoadCase * * pVal)
{
	if (pVal == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::Find(BSTR Name, ILoadCase * * __MIDL_0043)
{
	if (__MIDL_0043 == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::Add(ILoadCase * __MIDL_0044)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::RemoveByName(BSTR Name)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::RemoveByIndex(CollectionIndexType index, BSTR * Name)
{
	if (Name == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::Clone(ILoadCases * * __MIDL_0045)
{
	if (__MIDL_0045 == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::Clear()
{
	return E_NOTIMPL;
}
// IStages
STDMETHODIMP CBogusComboContext::get_Item(StageIndexType index, IStage * * pVal)
{
	if (pVal == nullptr)
		return E_POINTER;
		
   if (index==0)
   {
      return m_Stage1.CopyTo(pVal);
   }
   else if (index==1)
   {
      return m_Stage2.CopyTo(pVal);
   }
   else if (index==2)
   {
      return m_Stage3.CopyTo(pVal);
   }
   else
   {
      ATLASSERT(false);
   }

	return E_FAIL;
}
STDMETHODIMP CBogusComboContext::Add(IStage * __MIDL_0034)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::Insert(StageIndexType relPosition, IStage * member)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::MoveTo(StageIndexType fromPosition, StageIndexType toPosition)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::RemoveByIndex(StageIndexType position)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::Reverse()
{
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::get__EnumElements(IEnumStage * * pVal)
{
	if (pVal == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::Clone(IStages * * Clone)
{
	if (Clone == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::FindIndex(BSTR Name, StageIndexType * index)
{
	if (index == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
// ILoadCombinations
STDMETHODIMP CBogusComboContext::get_Item(CollectionIndexType index, ILoadCombination * * pVal)
{
	if (pVal == nullptr)
		return E_POINTER;
		
   if (index==0)
   {
      return m_LoadCombo1.CopyTo(pVal);
   }
   else if (index==1)
   {
      return m_LoadCombo2.CopyTo(pVal);
   }
   else if (index==2)
   {
      return m_LoadCombo3.CopyTo(pVal);
   }
   else
   {
      ATLASSERT(false);
   }

   return E_FAIL;
}
STDMETHODIMP CBogusComboContext::get__EnumElements(IEnumLoadCombination * * pVal)
{
	if (pVal == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::Find(BSTR Name, ILoadCombination * * __MIDL_0046)
{
	if (__MIDL_0046 == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::Add(ILoadCombination * __MIDL_0047)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBogusComboContext::Clone(ILoadCombinations * * __MIDL_0048)
{
	if (__MIDL_0048 == nullptr)
		return E_POINTER;
		
	return E_NOTIMPL;
}

// IGetStressPoints
STDMETHODIMP CBogusComboContext::GetStressPointsAtPOI(PoiIDType poiID, BSTR stage, IStressPoints * * LeftStressPoints, IStressPoints * * RightStressPoints)
{
	if (LeftStressPoints == nullptr)
		return E_POINTER;
		
	if (RightStressPoints == nullptr)
		return E_POINTER;

   BenchMarkIterator it = m_BenchMarks.find(poiID);
   if (it!=m_BenchMarks.end())
   {
      ComboBenchMark& bm = it->second;

      CComPtr<IStressPoints> sps;
      bm.GetStressPoints(stage, &sps);
      sps.CopyTo(LeftStressPoints);
      return sps.CopyTo(RightStressPoints);
   }

   return E_FAIL;
}

STDMETHODIMP CBogusComboContext::CompareLoadCaseSectionResults(BSTR loadCase, BSTR stage, ResultsSummationType summ, VARIANT_BOOL doFlip, ISectionResult3Ds* results)
{
   // iterate through benchmarks in same order as pois
   CollectionIndexType i = 0;
   for (BenchMarkIterator it=m_BenchMarks.begin(); it!=m_BenchMarks.end(); it++)
   {
      ComboBenchMark& rbench = it->second;
      Float64 bench;
      rbench.GetLoadCaseResult(loadCase, stage, summ, &bench);

      CComPtr<ISectionResult3D> secres;
      results->get_Item(i, &secres);

      Float64 lx, ly, lz, rx, ry, rz;
      secres->GetResult(&lx, &ly, &lz, &rx, &ry, &rz);

      TRY_TEST(lx, bench);
      TRY_TEST(ly, bench);
      TRY_TEST(lz, bench);

      if (doFlip==VARIANT_TRUE)
         bench *= -1;

      TRY_TEST(rx, bench);
      TRY_TEST(ry, bench);
      TRY_TEST(rz, bench);

      i++;
   }

   return S_OK;
}

STDMETHODIMP CBogusComboContext::CompareLoadCaseResults(BSTR loadCase, BSTR stage, ResultsSummationType summ, IResult3Ds* results)
{
   // iterate through benchmarks in same order as pois
   CollectionIndexType i = 0;
   for (BenchMarkIterator it=m_BenchMarks.begin(); it!=m_BenchMarks.end(); it++)
   {
      ComboBenchMark& rbench = it->second;
      Float64 bench;
      rbench.GetLoadCaseResult(loadCase, stage, summ, &bench);

      CComPtr<IResult3D> res;
      results->get_Item(i, &res);

      Float64 x, y, z;
      res->GetResult(&x, &y, &z);

      TRY_TEST(x, bench);
      TRY_TEST(y, bench);
      TRY_TEST(z, bench);

      i++;
   }

   return S_OK;
}

STDMETHODIMP CBogusComboContext::CompareLoadCaseStressResults(BSTR loadCase, BSTR stage, ResultsSummationType summ, ISectionStressResults* results)
{
   // iterate through benchmarks in same order as pois
   CollectionIndexType i = 0;
   for (BenchMarkIterator it=m_BenchMarks.begin(); it!=m_BenchMarks.end(); it++)
   {
      ComboBenchMark& rbench = it->second;
      Float64 benchsp1, benchsp2;
      rbench.GetLoadCaseStress(loadCase, stage, summ, &benchsp1, &benchsp2);

      CComPtr<ISectionStressResult> res;
      results->get_Item(i, &res);

      Float64 r;
      res->GetLeftResult(0, &r);
      TRY_TEST(IsEqual(r, benchsp1), true);
      res->GetRightResult(0, &r);
      TRY_TEST(IsEqual(r, benchsp1), true);

      res->GetLeftResult(1, &r);
      TRY_TEST(IsEqual(r, benchsp2), true);
      res->GetRightResult(1, &r);
      TRY_TEST(IsEqual(r, benchsp2), true);

      i++;
   }

   return S_OK;
}


STDMETHODIMP CBogusComboContext::CompareLoadCombinationSectionResults(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                                                      ForceEffectType fet, OptimizationType opt, 
                                                                      VARIANT_BOOL doFlip,
                                                                      ILoadCombinationSectionResults* results)
{
   // iterate through benchmarks in same order as pois
   CollectionIndexType i = 0;
   for (BenchMarkIterator it=m_BenchMarks.begin(); it!=m_BenchMarks.end(); it++)
   {
      ComboBenchMark& rbench = it->second;
      Float64 minbench, maxbench;
      rbench.GetCombinedResult(loadCombo, stage, summ, &minbench, &maxbench);

      CComPtr<ILoadCombinationResultConfiguration> leftconfig, rightconfig;
      Float64 leftval, rightval;
      results->GetResult(i, &leftval, &leftconfig, &rightval, &rightconfig);

      if (doFlip==VARIANT_FALSE)
      {
         if (opt==optMaximize)
         {
            TRY_TEST(IsEqual(leftval,   maxbench), true);
            TRY_TEST(IsEqual(rightval,  maxbench), true);
         }
         else
         {
            TRY_TEST(IsEqual(leftval,   minbench), true);
            TRY_TEST(IsEqual(rightval,  minbench), true);
         }
      }
      else
      {
         // our loadgroup input forces the left and right section values to be equal. This
         // represents a complete sign reversal if we are thinking about forces, and makes
         // it a bit tricky when thinking about how we apply max/min factors.
         if (opt==optMaximize)
         {
            TRY_TEST(IsEqual(leftval,   maxbench), true);
            TRY_TEST(IsEqual(rightval, -maxbench), true);
         }
         else
         {
            TRY_TEST(IsEqual(leftval,   minbench), true);
            TRY_TEST(IsEqual(rightval, -minbench), true);
         }
      }

      i++;
   }

   return S_OK;
}

STDMETHODIMP CBogusComboContext::CompareLoadCombinationSectionRes(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                                                  OptimizationType opt, VARIANT_BOOL doFlip,
                                                                  ISectionResult3Ds* results)
{
   // iterate through benchmarks in same order as pois
   CollectionIndexType i = 0;
   for (BenchMarkIterator it=m_BenchMarks.begin(); it!=m_BenchMarks.end(); it++)
   {
      ComboBenchMark& rbench = it->second;
      Float64 minbench, maxbench;
      rbench.GetCombinedResult(loadCombo, stage, summ, &minbench, &maxbench);

      CComPtr<ISectionResult3D> res;
      results->get_Item(i, &res);

      Float64 lx, ly, lz, rx, ry, rz;
      res->GetResult(&lx, &ly, &lz, &rx, &ry, &rz);

      // deal with sign flipping for left and right sides
      if (doFlip==VARIANT_FALSE)
      {
         if (opt==optMaximize)
         {
            TRY_TEST(IsEqual(lx,  maxbench), true);
            TRY_TEST(IsEqual(ly,  maxbench), true);
            TRY_TEST(IsEqual(lz,  maxbench), true);
            TRY_TEST(IsEqual(rx,  maxbench), true);
            TRY_TEST(IsEqual(ry,  maxbench), true);
            TRY_TEST(IsEqual(rz,  maxbench), true);
         }
         else
         {
            TRY_TEST(IsEqual(lx,  minbench), true);
            TRY_TEST(IsEqual(ly,  minbench), true);
            TRY_TEST(IsEqual(lz,  minbench), true);
            TRY_TEST(IsEqual(rx,  minbench), true);
            TRY_TEST(IsEqual(ry,  minbench), true);
            TRY_TEST(IsEqual(rz,  minbench), true);
         }
      }
      else
      {
         if (opt==optMaximize)
         {
            TRY_TEST(IsEqual(lx,  maxbench), true);
            TRY_TEST(IsEqual(ly,  maxbench), true);
            TRY_TEST(IsEqual(lz,  maxbench), true);
            TRY_TEST(IsEqual(rx, -maxbench), true);
            TRY_TEST(IsEqual(ry, -maxbench), true);
            TRY_TEST(IsEqual(rz, -maxbench), true);
         }
         else
         {
            TRY_TEST(IsEqual(lx,  minbench), true);
            TRY_TEST(IsEqual(ly,  minbench), true);
            TRY_TEST(IsEqual(lz,  minbench), true);
            TRY_TEST(IsEqual(rx, -minbench), true);
            TRY_TEST(IsEqual(ry, -minbench), true);
            TRY_TEST(IsEqual(rz, -minbench), true);
         }
      }

      i++;
   }

   return S_OK;
}

STDMETHODIMP CBogusComboContext::CompareLoadCombinationResults(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                                                      ForceEffectType fet, OptimizationType opt, 
                                                                      ILoadCombinationResults* results)
{
   // iterate through benchmarks in same order as pois
   CollectionIndexType i = 0;
   for (BenchMarkIterator it=m_BenchMarks.begin(); it!=m_BenchMarks.end(); it++)
   {
      ComboBenchMark& rbench = it->second;
      Float64 minbench, maxbench;
      rbench.GetCombinedResult(loadCombo, stage, summ, &minbench, &maxbench);

      CComPtr<ILoadCombinationResultConfiguration> config;
      Float64 val;
      results->GetResult(i, &val, &config);

      if (opt==optMaximize)
      {
         TRY_TEST(IsEqual(val,   maxbench), true);
      }
      else
      {
         TRY_TEST(IsEqual(val,   minbench), true);
      }

      i++;
   }

   return S_OK;
}

STDMETHODIMP CBogusComboContext::CompareLoadCombinationRes(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                                           OptimizationType opt, IResult3Ds* results)
{
   // iterate through benchmarks in same order as pois
   CollectionIndexType i = 0;
   for (BenchMarkIterator it=m_BenchMarks.begin(); it!=m_BenchMarks.end(); it++)
   {
      ComboBenchMark& rbench = it->second;
      Float64 minbench, maxbench;
      rbench.GetCombinedResult(loadCombo, stage, summ, &minbench, &maxbench);

      CComPtr<IResult3D> res;
      results->get_Item(i, &res);

      Float64 rx, ry, rz;
      res->GetResult(&rx, &ry, &rz);


      if (opt==optMaximize)
      {
         TRY_TEST(IsEqual(rx,  maxbench), true);
         TRY_TEST(IsEqual(ry,  maxbench), true);
         TRY_TEST(IsEqual(rz,  maxbench), true);
      }
      else
      {
         TRY_TEST(IsEqual(rx,  minbench), true);
         TRY_TEST(IsEqual(ry,  minbench), true);
         TRY_TEST(IsEqual(rz,  minbench), true);
      }

      i++;
   }

   return S_OK;
}

STDMETHODIMP CBogusComboContext::CompareLoadCombinationStressResults(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                                                     ForceEffectType fet, OptimizationType opt, 
                                                                     ILoadCombinationStressResults* results)
{
   // iterate through benchmarks in same order as pois
   CollectionIndexType i = 0;
   for (BenchMarkIterator it=m_BenchMarks.begin(); it!=m_BenchMarks.end(); it++)
   {
      ComboBenchMark& rbench = it->second;
      Float64 sp1bench, sp2bench;
      rbench.GetCombinedStressResult(loadCombo, stage, summ, opt, &sp1bench, &sp2bench);

      CComPtr<ILoadCombinationResultConfiguration> leftconfig, rightconfig;
      CComPtr<IStressResult> leftres, rightres;
      results->GetResult(i , &leftres, &leftconfig, &rightres, &rightconfig);

      Float64 leftval, rightval;
      leftres->GetResult(0, &leftval);
      rightres->GetResult(0, &rightval);

      TRY_TEST(IsEqual(leftval,  sp1bench),true);
      TRY_TEST(IsEqual(rightval, sp1bench),true);

      leftres->GetResult(1, &leftval);
      rightres->GetResult(1, &rightval);

      TRY_TEST(IsEqual(leftval,  sp2bench),true);
      TRY_TEST(IsEqual(rightval, sp2bench),true);

      i++;
   }

   return S_OK;
}

STDMETHODIMP CBogusComboContext::CompareLoadCombinationStressRes(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                                           OptimizationType opt, ISectionStressResults* results)
{
   // iterate through benchmarks in same order as pois
   CollectionIndexType i = 0;
   for (BenchMarkIterator it=m_BenchMarks.begin(); it!=m_BenchMarks.end(); it++)
   {
      ComboBenchMark& rbench = it->second;
      Float64 sp1bench, sp2bench;
      rbench.GetCombinedStressResult(loadCombo, stage, summ, opt, &sp1bench, &sp2bench);

      CComPtr<ISectionStressResult> res;
      results->get_Item(i, &res);

      Float64 leftval, rightval;
      res->GetLeftResult(0, &leftval);
      res->GetRightResult(0, &rightval);

      TRY_TEST(IsEqual(leftval,  sp1bench),true);
      TRY_TEST(IsEqual(rightval, sp1bench),true);

      res->GetLeftResult(1, &leftval);
      res->GetRightResult(1, &rightval);

      TRY_TEST(IsEqual(leftval,  sp2bench),true);
      TRY_TEST(IsEqual(rightval, sp2bench),true);

      i++;
   }

   return S_OK;
}


HRESULT ComboBenchMark::GetLoadGroupSectionValue(BSTR LoadGroup, BSTR stage, ResultsSummationType summ, bool flip, ISectionResult3Ds * * Results)
{
   CComPtr<ISectionResult3Ds> results;
   results.CoCreateInstance(CLSID_SectionResult3Ds);

   CComPtr<ISectionResult3D> result;
   result.CoCreateInstance(CLSID_SectionResult3D);

   Float64 minval, maxval;
   m_LoadGroupResults.GetValues(LoadGroup, stage, summ, &minval, &maxval);

   if (flip)
      result->SetResult(minval, minval, minval,-minval,-minval,-minval); // flip right-side values
   else
      result->SetResult(minval, minval, minval, minval, minval, minval);

   results->Add(result);

   return results.CopyTo(Results);
}


HRESULT ComboBenchMark::GetLoadGroupStressValue(BSTR LoadGroup, BSTR stage, ResultsSummationType summ, ISectionStressResults * * Results)
{
   CComPtr<ISectionStressResults> results;
   results.CoCreateInstance(CLSID_SectionStressResults);

   CComPtr<ISectionStressResult> result;
   result.CoCreateInstance(CLSID_SectionStressResult);

   Float64 valsp1, valsp2;
   m_LoadGroupStressResults.GetValues(LoadGroup, stage, summ, &valsp1, &valsp2);

   result->AddLeftResult(valsp1);
   result->AddLeftResult(valsp2);

   result->AddRightResult(valsp1);
   result->AddRightResult(valsp2);

   results->Add(result);

   return results.CopyTo(Results);
}


HRESULT ComboBenchMark::GetLoadGroupValue(BSTR LoadGroup, BSTR stage, ResultsSummationType summ, IResult3Ds * * Results)
{
   CComPtr<IResult3Ds> results;
   results.CoCreateInstance(CLSID_Result3Ds);

   CComPtr<IResult3D> result;
   result.CoCreateInstance(CLSID_Result3D);

   Float64 minval, maxval;
   m_LoadGroupResults.GetValues(LoadGroup, stage, summ, &minval, &maxval);

   result->SetResult(minval, minval, minval);

   results->Add(result);

   return results.CopyTo(Results);
}

HRESULT ComboBenchMark::GetLiveLoadSectionValue( OptimizationType Optimization, bool doFlip, ILiveLoadModelSectionResults * * Results)
{
   CComPtr<ILiveLoadModelSectionResults> results;
   results.CoCreateInstance(CLSID_LiveLoadModelSectionResults);

   Float64 lres = Optimization==optMaximize ? m_MaxLiveLoadValue : m_MinLiveLoadValue;
   Float64 rres = doFlip ? -lres : lres;

   CComPtr<ILiveLoadConfiguration> config;
   config.CoCreateInstance(CLSID_LiveLoadConfiguration);
   config->put_Optimization(Optimization);



   results->Add(lres, config, rres, config);

   return results.CopyTo(Results);
}

HRESULT ComboBenchMark::GetLiveLoadSectionValue( OptimizationType Optimization, bool doFlip, ISectionResult3Ds * * Results)
{
   Float64 lres = Optimization==optMaximize ? m_MaxLiveLoadValue : m_MinLiveLoadValue;
   Float64 rres = doFlip ? -lres : lres;

   CComPtr<ISectionResult3D> result;
   result.CoCreateInstance(CLSID_SectionResult3D);
   result->SetResult(lres,lres,lres,rres,rres,rres);

   CComPtr<ISectionResult3Ds> results;
   results.CoCreateInstance(CLSID_SectionResult3Ds);
   results->Add(result);

   return results.CopyTo(Results);
}


HRESULT ComboBenchMark::GetLiveLoadValue( OptimizationType Optimization, ILiveLoadModelResults * * Results)
{
   CComPtr<ILiveLoadModelResults> results;
   results.CoCreateInstance(CLSID_LiveLoadModelResults);

   Float64 res = Optimization==optMaximize ? m_MaxLiveLoadValue : m_MinLiveLoadValue;

   CComPtr<ILiveLoadConfiguration> config;
   config.CoCreateInstance(CLSID_LiveLoadConfiguration);
   config->put_Optimization(Optimization);

   results->Add(res, config);

   return results.CopyTo(Results);
}

HRESULT ComboBenchMark::GetLiveLoadValue( OptimizationType Optimization, IResult3Ds * * Results)
{
   Float64 res = Optimization==optMaximize ? m_MaxLiveLoadValue : m_MinLiveLoadValue;

   CComPtr<IResult3Ds> results;
   results.CoCreateInstance(CLSID_Result3Ds);

   CComPtr<IResult3D> result;
   result.CoCreateInstance(CLSID_Result3D);

   result->SetResult(res, res, res);

   results->Add(result);

   return results.CopyTo(Results);
}

HRESULT ComboBenchMark::GetLiveLoadStress( BSTR stage, OptimizationType Optimization, ISectionStressResults * * Results)
{
   Float64 force = Optimization==optMaximize ? m_MaxLiveLoadValue : m_MinLiveLoadValue;

   CComPtr<ISectionStressResults> results;
   results.CoCreateInstance(CLSID_SectionStressResults);

   CComPtr<ISectionStressResult> result;
   result.CoCreateInstance(CLSID_SectionStressResult);

   results->Add(result);

   CComPtr<IStressPoints> sps;
   HRESULT hr = this->GetStressPoints(stage, &sps);
   if (FAILED(hr))
      return hr;

   CollectionIndexType num_sps;
   sps->get_Count(&num_sps);

   for (CollectionIndexType isp = 0; isp<num_sps; isp++)
   {
      CComPtr<IStressPoint> sp;
      sps->get_Item(isp, &sp);
      Float64 sa, sm;
      sp->get_Sa(&sa);
      sp->get_Sm(&sm);

      Float64 stress = force*(sa+sm);
      result->AddLeftResult(stress);
      result->AddRightResult(stress);
   }

   return results.CopyTo(Results);
}



HRESULT ComboBenchMark::GetCombinationFactors(BSTR stage, LoadCombinationType type, Float64* minFactor, Float64* maxFactor)
{
   *minFactor = m_MinCombinationFactor;
   *maxFactor = m_MaxCombinationFactor;

   return S_OK;
}

// BENCHMARKS
void ComboBenchMark::GetLoadCaseResult(BSTR loadCase, BSTR stage, ResultsSummationType summ, Float64* result)
{
   Float64 bogus;
   m_LoadCaseBenchMarks.GetValues(loadCase, stage, summ, result, &bogus);
}

void ComboBenchMark::GetLoadCaseStress(BSTR loadCase, BSTR stage, ResultsSummationType summ, Float64* result1, Float64* result2)
{
   m_LoadCaseStressBenchMarks.GetValues(loadCase, stage, summ, result1, result2);
}

void ComboBenchMark::GetCombinedResult(BSTR loadCombination, BSTR stage, ResultsSummationType summ, Float64* minResult, Float64* maxResult)
{
   m_LoadCombinationBenchMarks.GetValues(loadCombination, stage, summ, minResult, maxResult);
}

void ComboBenchMark::GetCombinedStressResult(BSTR loadCombination, BSTR stage, ResultsSummationType summ, OptimizationType opt, Float64* minResult, Float64* maxResult)
{
   if (opt==optMinimize)
      m_LoadCombinationMinStressBenchMarks.GetValues(loadCombination, stage, summ, minResult, maxResult);
   else
      m_LoadCombinationMaxStressBenchMarks.GetValues(loadCombination, stage, summ, minResult, maxResult);
}


// SET UP
void ComboBenchMark::SetLoadGroupValue(BSTR loadGroup, BSTR stage, ResultsSummationType summ, Float64 value)
{
   m_LoadGroupResults.SetValues(loadGroup, stage, summ, value, value);
}

void ComboBenchMark::SetLoadGroupStressValue(BSTR loadGroup, BSTR stage, ResultsSummationType summ, Float64 valsp1, Float64 valsp2)
{
   m_LoadGroupStressResults.SetValues(loadGroup, stage, summ, valsp1, valsp2);
}


void ComboBenchMark::SetLiveLoadValue(Float64 minValue, Float64 maxValue)
{
   m_MinLiveLoadValue = minValue;
   m_MaxLiveLoadValue = maxValue;
}

void ComboBenchMark::SetCombinationFactors(BSTR stage, LoadCombinationType type, Float64 minFactor, Float64 maxFactor)
{
   m_MinCombinationFactor = minFactor;
   m_MaxCombinationFactor = maxFactor;
}

void ComboBenchMark::SetLoadCaseBenchMark(BSTR loadCase, BSTR stage, ResultsSummationType summ, Float64 value)
{
   m_LoadCaseBenchMarks.SetValues(loadCase, stage, summ, value, value);
}

void ComboBenchMark::SetLoadCaseStressBenchMark(BSTR loadCase, BSTR stage, ResultsSummationType summ, Float64 value1, Float64 value2)
{
   m_LoadCaseStressBenchMarks.SetValues(loadCase, stage, summ, value1, value2);
}

void ComboBenchMark::SetCombinedBenchMark(BSTR loadCombination, BSTR stage, ResultsSummationType summ, Float64 minValue, Float64 maxValue)
{
   m_LoadCombinationBenchMarks.SetValues(loadCombination, stage, summ, minValue, maxValue);
}

void ComboBenchMark::SetCombinedStressBenchMark(BSTR loadCombination, BSTR stage, ResultsSummationType summ, OptimizationType opt, Float64 sp1Value, Float64 sp2Value)
{
   if (opt==optMinimize)
      m_LoadCombinationMinStressBenchMarks.SetValues(loadCombination, stage, summ, sp1Value, sp2Value);
   else
      m_LoadCombinationMaxStressBenchMarks.SetValues(loadCombination, stage, summ, sp1Value, sp2Value);
}

HRESULT ComboBenchMark::GetStressPoints(BSTR stage, IStressPoints** sps)
{
   StressPointsIterator it = m_StressPoints.find(stage);
   if (it!=m_StressPoints.end())
   {
      return it->second.CopyTo(sps);
   }
   else
   {
      ATLASSERT(false);
   }

   return E_FAIL;
}

void ComboBenchMark::SetStressPoints(BSTR stage, IStressPoints* sps)
{
   StressPointsIterator it = m_StressPoints.find(stage);
   if (it!=m_StressPoints.end())
   {
      ATLASSERT(false); // test shouldn't replace stress points?
   }
   else
   {
      m_StressPoints.insert(std::make_pair(stage, sps));
   }
}
