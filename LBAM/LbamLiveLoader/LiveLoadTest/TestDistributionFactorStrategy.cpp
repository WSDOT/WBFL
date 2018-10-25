///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// TestDistributionFactorStrategy.cpp: implementation of the CTestDistributionFactorStrategy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDistributionFactorStrategy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// a lamo class to implement IGetDistributionFactors
class LameIdf: public IGetDistributionFactors
{
public:
   STDMETHOD(GetPOIDistributionFactor)(/*[in]*/PoiIDType POI, /*[in]*/BSTR stage, /*[out]*/IDistributionFactor* *leftFactor, /*[out]*/IDistributionFactor* *rightFactor)
   {
      _ASSERT(POI==0);
      m_LeftFactor.CopyTo(leftFactor);
      m_RightFactor.CopyTo(rightFactor);
      return S_OK;
   }

	STDMETHOD(GetSupportDistributionFactor)(/*[in]*/SupportIDType supportID, /*[in]*/BSTR Stage, /*[out,retval]*/IDistributionFactor* *Factor)
   {
      _ASSERT(supportID==0);
      m_LeftFactor.CopyTo(Factor);
      return S_OK;
   }


   // com details - we don't need no stinkin atl
   STDMETHOD(QueryInterface)(const struct _GUID &,void ** ) {_ASSERT(0); return E_FAIL;}
   unsigned long __stdcall AddRef(void) {_ASSERT(0); return 0;}
   unsigned long __stdcall Release(void) {_ASSERT(0); return 0;}
   long __stdcall GetTypeInfoCount(unsigned int *) {_ASSERT(0); return 0;}
   long __stdcall GetIDsOfNames(const struct _GUID &,unsigned short ** ,unsigned int,unsigned long,long *) {_ASSERT(0); return 0;}
   long __stdcall GetTypeInfo(unsigned int,unsigned long,struct ITypeInfo ** ) {_ASSERT(0); return 0;}
   long __stdcall Invoke(long,const struct _GUID &,unsigned long,unsigned short,struct tagDISPPARAMS *,struct tagVARIANT *,struct tagEXCEPINFO *,unsigned int *) {_ASSERT(0); return 0;}

   CComPtr<IDistributionFactor> m_LeftFactor;
   CComPtr<IDistributionFactor> m_RightFactor;
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TestDistributionFactorStrategy::TestDistributionFactorStrategy()
{;}
TestDistributionFactorStrategy::~TestDistributionFactorStrategy()
{;}

void TestDistributionFactorStrategy::Test()
{
   // create some distribution factors to test
   CComPtr<IDistributionFactor> df_left, df_right;
   df_left.CoCreateInstance(CLSID_DistributionFactor);
   df_right.CoCreateInstance(CLSID_DistributionFactor);

   const Float64 lftPMSgl = 1;
   const Float64 lftPMMul = 2;
   const Float64 lftNMSgl = 3;
   const Float64 lftNMMul = 4;
   const Float64 lftVSgl  = 5;
   const Float64 lftVMul  = 6;
   const Float64 lftDSgl  = 7;
   const Float64 lftDMul  = 8;
   const Float64 lftRSgl  = 9;
   const Float64 lftRMul  = 10;
   const Float64 lftTSgl  = 11;
   const Float64 lftTMul  = 12;
   const Float64 lftFatM  = 13;
   const Float64 lftFatV  = 14;
   const Float64 lftPed   = 15;
   df_left->SetG(lftPMSgl, lftPMMul, lftNMSgl, lftNMMul, lftVSgl, lftVMul, lftDSgl, lftDMul, lftRSgl, lftRMul, lftTSgl, lftTMul, lftFatM, lftFatV, lftPed);

   const Float64 rgtPMSgl = 101;
   const Float64 rgtPMMul = 102;
   const Float64 rgtNMSgl = 103;
   const Float64 rgtNMMul = 104;
   const Float64 rgtVSgl  = 105;
   const Float64 rgtVMul  = 106;
   const Float64 rgtDSgl  = 107;
   const Float64 rgtDMul  = 108;
   const Float64 rgtRSgl  = 109;
   const Float64 rgtRMul  = 110;
   const Float64 rgtTSgl  = 111;
   const Float64 rgtTMul  = 112;
   const Float64 rgtFatM  = 113;
   const Float64 rgtFatV  = 114;
   const Float64 rgtPed   = 115;
   df_right->SetG(rgtPMSgl, rgtPMMul, rgtNMSgl, rgtNMMul, rgtVSgl, rgtVMul, rgtDSgl, rgtDMul, rgtRSgl, rgtRMul, rgtTSgl, rgtTMul, rgtFatM, rgtFatV, rgtPed);

   LameIdf my_idf;
   my_idf.m_LeftFactor  = df_left;
   my_idf.m_RightFactor = df_right;

   Float64 left_factor, right_factor;
   DistributionFactorType left_dftype, right_dftype;

   Float64 lft_fx_fac, lft_fy_fac, lft_mz_fac;
   Float64 rgt_fx_fac, rgt_fy_fac, rgt_mz_fac;

   CComBSTR stage("Stage 1");

   try
   {
      // test force strategy
      // maximize
      ForceDistributionFactorStrategy f_max_strategy(&my_idf, optMaximize);

      f_max_strategy.GetOptimalDfs(0, stage, fetFx, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVSgl);
      TRY_TEST(right_factor, rgtVSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      f_max_strategy.GetOptimalDfs(0, stage, fetFx, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVMul);
      TRY_TEST(right_factor, rgtVMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_max_strategy.GetOptimalDfs(0, stage, fetFx, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVMul);
      TRY_TEST(right_factor, rgtVMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_max_strategy.GetOptimalDfs(0, stage, fetFx, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, rgtFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      f_max_strategy.GetOptimalDfs(0, stage, fetFx, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      f_max_strategy.GetOptimalDfs(0, stage, fetFy, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVSgl);
      TRY_TEST(right_factor, rgtVSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      f_max_strategy.GetOptimalDfs(0, stage, fetFy, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVMul);
      TRY_TEST(right_factor, rgtVMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_max_strategy.GetOptimalDfs(0, stage, fetFy, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVMul);
      TRY_TEST(right_factor, rgtVMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_max_strategy.GetOptimalDfs(0, stage, fetFy, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, rgtFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      f_max_strategy.GetOptimalDfs(0, stage, fetFy, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      f_max_strategy.GetOptimalDfs(0, stage, fetMz, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPMSgl);
      TRY_TEST(right_factor, rgtPMSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      f_max_strategy.GetOptimalDfs(0, stage, fetMz, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPMMul);
      TRY_TEST(right_factor, rgtPMMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_max_strategy.GetOptimalDfs(0, stage, fetMz, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPMMul);
      TRY_TEST(right_factor, rgtPMMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_max_strategy.GetOptimalDfs(0, stage, fetMz, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatM);
      TRY_TEST(right_factor, rgtFatM);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      f_max_strategy.GetOptimalDfs(0, stage, fetMz, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      f_max_strategy.GetConcurrentDfs(0, stage, dftSingleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftVSgl);
      TRY_TEST(lft_fy_fac,  lftVSgl);
      TRY_TEST(lft_mz_fac,  lftPMSgl);
      TRY_TEST(rgt_fx_fac,  rgtVSgl);
      TRY_TEST(rgt_fy_fac,  rgtVSgl);
      TRY_TEST(rgt_mz_fac,  rgtPMSgl);

      f_max_strategy.GetConcurrentDfs(0, stage, dftMultipleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftVMul);
      TRY_TEST(lft_fy_fac,  lftVMul);
      TRY_TEST(lft_mz_fac,  lftPMMul);
      TRY_TEST(rgt_fx_fac,  rgtVMul);
      TRY_TEST(rgt_fy_fac,  rgtVMul);
      TRY_TEST(rgt_mz_fac,  rgtPMMul);

      f_max_strategy.GetConcurrentDfs(0, stage, dftEnvelope, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftVMul);
      TRY_TEST(lft_fy_fac,  lftVMul);
      TRY_TEST(lft_mz_fac,  lftPMMul);
      TRY_TEST(rgt_fx_fac,  rgtVMul);
      TRY_TEST(rgt_fy_fac,  rgtVMul);
      TRY_TEST(rgt_mz_fac,  rgtPMMul);

      f_max_strategy.GetConcurrentDfs(0, stage, dftFatigue, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftFatV);
      TRY_TEST(lft_fy_fac,  lftFatV);
      TRY_TEST(lft_mz_fac,  lftFatM);
      TRY_TEST(rgt_fx_fac,  rgtFatV);
      TRY_TEST(rgt_fy_fac,  rgtFatV);
      TRY_TEST(rgt_mz_fac,  rgtFatM);

      f_max_strategy.GetConcurrentDfs(0, stage, dftPedestrian, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftPed);
      TRY_TEST(lft_fy_fac,  lftPed);
      TRY_TEST(lft_mz_fac,  lftPed);
      TRY_TEST(rgt_fx_fac,  rgtPed);
      TRY_TEST(rgt_fy_fac,  rgtPed);
      TRY_TEST(rgt_mz_fac,  rgtPed);

      // minimize
      ForceDistributionFactorStrategy f_min_strategy(&my_idf, optMinimize);

      f_min_strategy.GetOptimalDfs(0, stage, fetFx, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVSgl);
      TRY_TEST(right_factor, rgtVSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      f_min_strategy.GetOptimalDfs(0, stage, fetFx, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVMul);
      TRY_TEST(right_factor, rgtVMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_min_strategy.GetOptimalDfs(0, stage, fetFx, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVMul);
      TRY_TEST(right_factor, rgtVMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_min_strategy.GetOptimalDfs(0, stage, fetFx, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, rgtFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      f_min_strategy.GetOptimalDfs(0, stage, fetFx, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      f_min_strategy.GetOptimalDfs(0, stage, fetFy, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVSgl);
      TRY_TEST(right_factor, rgtVSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      f_min_strategy.GetOptimalDfs(0, stage, fetFy, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVMul);
      TRY_TEST(right_factor, rgtVMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_min_strategy.GetOptimalDfs(0, stage, fetFy, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftVMul);
      TRY_TEST(right_factor, rgtVMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_min_strategy.GetOptimalDfs(0, stage, fetFy, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, rgtFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      f_min_strategy.GetOptimalDfs(0, stage, fetFy, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      f_min_strategy.GetOptimalDfs(0, stage, fetMz, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftNMSgl);
      TRY_TEST(right_factor, rgtNMSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      f_min_strategy.GetOptimalDfs(0, stage, fetMz, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftNMMul);
      TRY_TEST(right_factor, rgtNMMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_min_strategy.GetOptimalDfs(0, stage, fetMz, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftNMMul);
      TRY_TEST(right_factor, rgtNMMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      f_min_strategy.GetOptimalDfs(0, stage, fetMz, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatM);
      TRY_TEST(right_factor, rgtFatM);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      f_min_strategy.GetOptimalDfs(0, stage, fetMz, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      f_min_strategy.GetConcurrentDfs(0, stage, dftSingleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftVSgl);
      TRY_TEST(lft_fy_fac,  lftVSgl);
      TRY_TEST(lft_mz_fac,  lftNMSgl);
      TRY_TEST(rgt_fx_fac,  rgtVSgl);
      TRY_TEST(rgt_fy_fac,  rgtVSgl);
      TRY_TEST(rgt_mz_fac,  rgtNMSgl);

      f_min_strategy.GetConcurrentDfs(0, stage, dftMultipleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftVMul);
      TRY_TEST(lft_fy_fac,  lftVMul);
      TRY_TEST(lft_mz_fac,  lftNMMul);
      TRY_TEST(rgt_fx_fac,  rgtVMul);
      TRY_TEST(rgt_fy_fac,  rgtVMul);
      TRY_TEST(rgt_mz_fac,  rgtNMMul);

      f_min_strategy.GetConcurrentDfs(0, stage, dftEnvelope, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftVMul);
      TRY_TEST(lft_fy_fac,  lftVMul);
      TRY_TEST(lft_mz_fac,  lftNMMul);
      TRY_TEST(rgt_fx_fac,  rgtVMul);
      TRY_TEST(rgt_fy_fac,  rgtVMul);
      TRY_TEST(rgt_mz_fac,  rgtNMMul);

      f_min_strategy.GetConcurrentDfs(0, stage, dftFatigue, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftFatV);
      TRY_TEST(lft_fy_fac,  lftFatV);
      TRY_TEST(lft_mz_fac,  lftFatM);
      TRY_TEST(rgt_fx_fac,  rgtFatV);
      TRY_TEST(rgt_fy_fac,  rgtFatV);
      TRY_TEST(rgt_mz_fac,  rgtFatM);

      f_min_strategy.GetConcurrentDfs(0, stage, dftPedestrian, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftPed);
      TRY_TEST(lft_fy_fac,  lftPed);
      TRY_TEST(lft_mz_fac,  lftPed);
      TRY_TEST(rgt_fx_fac,  rgtPed);
      TRY_TEST(rgt_fy_fac,  rgtPed);
      TRY_TEST(rgt_mz_fac,  rgtPed);
   }
   catch(...)
   {
      _ASSERT(0);
      TRY_TEST(1,2);
   }

   try
   {
      // test deflection strategy
      // maximize
      DeflectionDistributionFactorStrategy d_max_strategy(&my_idf);

      d_max_strategy.GetOptimalDfs(0, stage, fetFx, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDSgl);
      TRY_TEST(right_factor, rgtDSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFx, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, rgtDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFx, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, rgtDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFx, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, rgtFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_max_strategy.GetOptimalDfs(0, stage, fetFx, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_max_strategy.GetOptimalDfs(0, stage, fetFy, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDSgl);
      TRY_TEST(right_factor, rgtDSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFy, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, rgtDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFy, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, rgtDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFy, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, rgtFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_max_strategy.GetOptimalDfs(0, stage, fetFy, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_max_strategy.GetOptimalDfs(0, stage, fetMz, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTSgl);
      TRY_TEST(right_factor, rgtTSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetMz, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTMul);
      TRY_TEST(right_factor, rgtTMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetMz, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTMul);
      TRY_TEST(right_factor, rgtTMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetMz, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatM);
      TRY_TEST(right_factor, rgtFatM);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_max_strategy.GetOptimalDfs(0, stage, fetMz, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_max_strategy.GetConcurrentDfs(0, stage, dftSingleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDSgl);
      TRY_TEST(lft_fy_fac,  lftDSgl);
      TRY_TEST(lft_mz_fac,  lftTSgl);
      TRY_TEST(rgt_fx_fac,  rgtDSgl);
      TRY_TEST(rgt_fy_fac,  rgtDSgl);
      TRY_TEST(rgt_mz_fac,  rgtTSgl);

      d_max_strategy.GetConcurrentDfs(0, stage, dftMultipleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDMul);
      TRY_TEST(lft_fy_fac,  lftDMul);
      TRY_TEST(lft_mz_fac,  lftTMul);
      TRY_TEST(rgt_fx_fac,  rgtDMul);
      TRY_TEST(rgt_fy_fac,  rgtDMul);
      TRY_TEST(rgt_mz_fac,  rgtTMul);

      d_max_strategy.GetConcurrentDfs(0, stage, dftEnvelope, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDMul);
      TRY_TEST(lft_fy_fac,  lftDMul);
      TRY_TEST(lft_mz_fac,  lftTMul);
      TRY_TEST(rgt_fx_fac,  rgtDMul);
      TRY_TEST(rgt_fy_fac,  rgtDMul);
      TRY_TEST(rgt_mz_fac,  rgtTMul);

      d_max_strategy.GetConcurrentDfs(0, stage, dftFatigue, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftFatV);
      TRY_TEST(lft_fy_fac,  lftFatV);
      TRY_TEST(lft_mz_fac,  lftFatM);
      TRY_TEST(rgt_fx_fac,  rgtFatV);
      TRY_TEST(rgt_fy_fac,  rgtFatV);
      TRY_TEST(rgt_mz_fac,  rgtFatM);

      d_max_strategy.GetConcurrentDfs(0, stage, dftPedestrian, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftPed);
      TRY_TEST(lft_fy_fac,  lftPed);
      TRY_TEST(lft_mz_fac,  lftPed);
      TRY_TEST(rgt_fx_fac,  rgtPed);
      TRY_TEST(rgt_fy_fac,  rgtPed);
      TRY_TEST(rgt_mz_fac,  rgtPed);

      // minimize
      DeflectionDistributionFactorStrategy d_min_strategy(&my_idf);

      d_min_strategy.GetOptimalDfs(0, stage, fetFx, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDSgl);
      TRY_TEST(right_factor, rgtDSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFx, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, rgtDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFx, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, rgtDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFx, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, rgtFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_min_strategy.GetOptimalDfs(0, stage, fetFx, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_min_strategy.GetOptimalDfs(0, stage, fetFy, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDSgl);
      TRY_TEST(right_factor, rgtDSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFy, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, rgtDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFy, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, rgtDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFy, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, rgtFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_min_strategy.GetOptimalDfs(0, stage, fetFy, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_min_strategy.GetOptimalDfs(0, stage, fetMz, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTSgl);
      TRY_TEST(right_factor, rgtTSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetMz, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTMul);
      TRY_TEST(right_factor, rgtTMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetMz, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTMul);
      TRY_TEST(right_factor, rgtTMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetMz, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatM);
      TRY_TEST(right_factor, rgtFatM);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_min_strategy.GetOptimalDfs(0, stage, fetMz, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, rgtPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_min_strategy.GetConcurrentDfs(0, stage, dftSingleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDSgl);
      TRY_TEST(lft_fy_fac,  lftDSgl);
      TRY_TEST(lft_mz_fac,  lftTSgl);
      TRY_TEST(rgt_fx_fac,  rgtDSgl);
      TRY_TEST(rgt_fy_fac,  rgtDSgl);
      TRY_TEST(rgt_mz_fac,  rgtTSgl);

      d_min_strategy.GetConcurrentDfs(0, stage, dftMultipleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDMul);
      TRY_TEST(lft_fy_fac,  lftDMul);
      TRY_TEST(lft_mz_fac,  lftTMul);
      TRY_TEST(rgt_fx_fac,  rgtDMul);
      TRY_TEST(rgt_fy_fac,  rgtDMul);
      TRY_TEST(rgt_mz_fac,  rgtTMul);

      d_min_strategy.GetConcurrentDfs(0, stage, dftEnvelope, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDMul);
      TRY_TEST(lft_fy_fac,  lftDMul);
      TRY_TEST(lft_mz_fac,  lftTMul);
      TRY_TEST(rgt_fx_fac,  rgtDMul);
      TRY_TEST(rgt_fy_fac,  rgtDMul);
      TRY_TEST(rgt_mz_fac,  rgtTMul);

      d_min_strategy.GetConcurrentDfs(0, stage, dftFatigue, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftFatV);
      TRY_TEST(lft_fy_fac,  lftFatV);
      TRY_TEST(lft_mz_fac,  lftFatM);
      TRY_TEST(rgt_fx_fac,  rgtFatV);
      TRY_TEST(rgt_fy_fac,  rgtFatV);
      TRY_TEST(rgt_mz_fac,  rgtFatM);

      d_min_strategy.GetConcurrentDfs(0, stage, dftPedestrian, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftPed);
      TRY_TEST(lft_fy_fac,  lftPed);
      TRY_TEST(lft_mz_fac,  lftPed);
      TRY_TEST(rgt_fx_fac,  rgtPed);
      TRY_TEST(rgt_fy_fac,  rgtPed);
      TRY_TEST(rgt_mz_fac,  rgtPed);
   }
   catch(...)
   {
      _ASSERT(0);
      TRY_TEST(1,2);
   }

   try
   {
      // test reaction strategy
      // maximize
      ReactionDistributionFactorStrategy t_max_strategy(&my_idf);

      t_max_strategy.GetOptimalDfs(0, stage, fetFx, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRSgl);
      TRY_TEST(right_factor, lftRSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      t_max_strategy.GetOptimalDfs(0, stage, fetFx, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_max_strategy.GetOptimalDfs(0, stage, fetFx, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_max_strategy.GetOptimalDfs(0, stage, fetFx, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, lftFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      t_max_strategy.GetOptimalDfs(0, stage, fetFx, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      t_max_strategy.GetOptimalDfs(0, stage, fetFy, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRSgl);
      TRY_TEST(right_factor, lftRSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      t_max_strategy.GetOptimalDfs(0, stage, fetFy, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_max_strategy.GetOptimalDfs(0, stage, fetFy, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_max_strategy.GetOptimalDfs(0, stage, fetFy, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, lftFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      t_max_strategy.GetOptimalDfs(0, stage, fetFy, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      t_max_strategy.GetOptimalDfs(0, stage, fetMz, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRSgl);
      TRY_TEST(right_factor, lftRSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      t_max_strategy.GetOptimalDfs(0, stage, fetMz, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_max_strategy.GetOptimalDfs(0, stage, fetMz, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_max_strategy.GetOptimalDfs(0, stage, fetMz, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatM);
      TRY_TEST(right_factor, lftFatM);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      t_max_strategy.GetOptimalDfs(0, stage, fetMz, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      t_max_strategy.GetConcurrentDfs(0, stage, dftSingleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftRSgl);
      TRY_TEST(lft_fy_fac,  lftRSgl);
      TRY_TEST(lft_mz_fac,  lftRSgl);
      TRY_TEST(rgt_fx_fac,  lftRSgl);
      TRY_TEST(rgt_fy_fac,  lftRSgl);
      TRY_TEST(rgt_mz_fac,  lftRSgl);

      t_max_strategy.GetConcurrentDfs(0, stage, dftMultipleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftRMul);
      TRY_TEST(lft_fy_fac,  lftRMul);
      TRY_TEST(lft_mz_fac,  lftRMul);
      TRY_TEST(rgt_fx_fac,  lftRMul);
      TRY_TEST(rgt_fy_fac,  lftRMul);
      TRY_TEST(rgt_mz_fac,  lftRMul);

      t_max_strategy.GetConcurrentDfs(0, stage, dftEnvelope, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftRMul);
      TRY_TEST(lft_fy_fac,  lftRMul);
      TRY_TEST(lft_mz_fac,  lftRMul);
      TRY_TEST(rgt_fx_fac,  lftRMul);
      TRY_TEST(rgt_fy_fac,  lftRMul);
      TRY_TEST(rgt_mz_fac,  lftRMul);

      t_max_strategy.GetConcurrentDfs(0, stage, dftFatigue, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftFatV);
      TRY_TEST(lft_fy_fac,  lftFatV);
      TRY_TEST(lft_mz_fac,  lftFatM);
      TRY_TEST(rgt_fx_fac,  lftFatV);
      TRY_TEST(rgt_fy_fac,  lftFatV);
      TRY_TEST(rgt_mz_fac,  lftFatM);

      t_max_strategy.GetConcurrentDfs(0, stage, dftPedestrian, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftPed);
      TRY_TEST(lft_fy_fac,  lftPed);
      TRY_TEST(lft_mz_fac,  lftPed);
      TRY_TEST(rgt_fx_fac,  lftPed);
      TRY_TEST(rgt_fy_fac,  lftPed);
      TRY_TEST(rgt_mz_fac,  lftPed);

      // minimize
      ReactionDistributionFactorStrategy t_min_strategy(&my_idf);

      t_min_strategy.GetOptimalDfs(0, stage, fetFx, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRSgl);
      TRY_TEST(right_factor, lftRSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      t_min_strategy.GetOptimalDfs(0, stage, fetFx, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_min_strategy.GetOptimalDfs(0, stage, fetFx, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_min_strategy.GetOptimalDfs(0, stage, fetFx, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, lftFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      t_min_strategy.GetOptimalDfs(0, stage, fetFx, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      t_min_strategy.GetOptimalDfs(0, stage, fetFy, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRSgl);
      TRY_TEST(right_factor, lftRSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      t_min_strategy.GetOptimalDfs(0, stage, fetFy, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_min_strategy.GetOptimalDfs(0, stage, fetFy, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_min_strategy.GetOptimalDfs(0, stage, fetFy, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, lftFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      t_min_strategy.GetOptimalDfs(0, stage, fetFy, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      t_min_strategy.GetOptimalDfs(0, stage, fetMz, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRSgl);
      TRY_TEST(right_factor, lftRSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      t_min_strategy.GetOptimalDfs(0, stage, fetMz, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_min_strategy.GetOptimalDfs(0, stage, fetMz, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftRMul);
      TRY_TEST(right_factor, lftRMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      t_min_strategy.GetOptimalDfs(0, stage, fetMz, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatM);
      TRY_TEST(right_factor, lftFatM);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      t_min_strategy.GetOptimalDfs(0, stage, fetMz, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      t_min_strategy.GetConcurrentDfs(0, stage, dftSingleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftRSgl);
      TRY_TEST(lft_fy_fac,  lftRSgl);
      TRY_TEST(lft_mz_fac,  lftRSgl);
      TRY_TEST(rgt_fx_fac,  lftRSgl);
      TRY_TEST(rgt_fy_fac,  lftRSgl);
      TRY_TEST(rgt_mz_fac,  lftRSgl);

      t_min_strategy.GetConcurrentDfs(0, stage, dftMultipleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftRMul);
      TRY_TEST(lft_fy_fac,  lftRMul);
      TRY_TEST(lft_mz_fac,  lftRMul);
      TRY_TEST(rgt_fx_fac,  lftRMul);
      TRY_TEST(rgt_fy_fac,  lftRMul);
      TRY_TEST(rgt_mz_fac,  lftRMul);

      t_min_strategy.GetConcurrentDfs(0, stage, dftEnvelope, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftRMul);
      TRY_TEST(lft_fy_fac,  lftRMul);
      TRY_TEST(lft_mz_fac,  lftRMul);
      TRY_TEST(rgt_fx_fac,  lftRMul);
      TRY_TEST(rgt_fy_fac,  lftRMul);
      TRY_TEST(rgt_mz_fac,  lftRMul);

      t_min_strategy.GetConcurrentDfs(0, stage, dftFatigue, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftFatV);
      TRY_TEST(lft_fy_fac,  lftFatV);
      TRY_TEST(lft_mz_fac,  lftFatM);
      TRY_TEST(rgt_fx_fac,  lftFatV);
      TRY_TEST(rgt_fy_fac,  lftFatV);
      TRY_TEST(rgt_mz_fac,  lftFatM);

      t_min_strategy.GetConcurrentDfs(0, stage, dftPedestrian, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftPed);
      TRY_TEST(lft_fy_fac,  lftPed);
      TRY_TEST(lft_mz_fac,  lftPed);
      TRY_TEST(rgt_fx_fac,  lftPed);
      TRY_TEST(rgt_fy_fac,  lftPed);
      TRY_TEST(rgt_mz_fac,  lftPed);
   }
   catch(...)
   {
      _ASSERT(0);
      TRY_TEST(1,2);
   }

   try
   {
      /////////////////////////////////////////
      // test support deflection strategy
      // maximize
      SupportDeflectionDistributionFactorStrategy d_max_strategy(&my_idf);

      d_max_strategy.GetOptimalDfs(0, stage, fetFx, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDSgl);
      TRY_TEST(right_factor, lftDSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFx, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, lftDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFx, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, lftDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFx, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, lftFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_max_strategy.GetOptimalDfs(0, stage, fetFx, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_max_strategy.GetOptimalDfs(0, stage, fetFy, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDSgl);
      TRY_TEST(right_factor, lftDSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFy, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, lftDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFy, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, lftDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetFy, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, lftFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_max_strategy.GetOptimalDfs(0, stage, fetFy, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_max_strategy.GetOptimalDfs(0, stage, fetMz, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTSgl);
      TRY_TEST(right_factor, lftTSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetMz, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTMul);
      TRY_TEST(right_factor, lftTMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetMz, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTMul);
      TRY_TEST(right_factor, lftTMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_max_strategy.GetOptimalDfs(0, stage, fetMz, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatM);
      TRY_TEST(right_factor, lftFatM);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_max_strategy.GetOptimalDfs(0, stage, fetMz, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_max_strategy.GetConcurrentDfs(0, stage, dftSingleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDSgl);
      TRY_TEST(lft_fy_fac,  lftDSgl);
      TRY_TEST(lft_mz_fac,  lftTSgl);
      TRY_TEST(rgt_fx_fac,  lftDSgl);
      TRY_TEST(rgt_fy_fac,  lftDSgl);
      TRY_TEST(rgt_mz_fac,  lftTSgl);

      d_max_strategy.GetConcurrentDfs(0, stage, dftMultipleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDMul);
      TRY_TEST(lft_fy_fac,  lftDMul);
      TRY_TEST(lft_mz_fac,  lftTMul);
      TRY_TEST(rgt_fx_fac,  lftDMul);
      TRY_TEST(rgt_fy_fac,  lftDMul);
      TRY_TEST(rgt_mz_fac,  lftTMul);

      d_max_strategy.GetConcurrentDfs(0, stage, dftEnvelope, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDMul);
      TRY_TEST(lft_fy_fac,  lftDMul);
      TRY_TEST(lft_mz_fac,  lftTMul);
      TRY_TEST(rgt_fx_fac,  lftDMul);
      TRY_TEST(rgt_fy_fac,  lftDMul);
      TRY_TEST(rgt_mz_fac,  lftTMul);

      d_max_strategy.GetConcurrentDfs(0, stage, dftFatigue, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftFatV);
      TRY_TEST(lft_fy_fac,  lftFatV);
      TRY_TEST(lft_mz_fac,  lftFatM);
      TRY_TEST(rgt_fx_fac,  lftFatV);
      TRY_TEST(rgt_fy_fac,  lftFatV);
      TRY_TEST(rgt_mz_fac,  lftFatM);

      d_max_strategy.GetConcurrentDfs(0, stage, dftPedestrian, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftPed);
      TRY_TEST(lft_fy_fac,  lftPed);
      TRY_TEST(lft_mz_fac,  lftPed);
      TRY_TEST(rgt_fx_fac,  lftPed);
      TRY_TEST(rgt_fy_fac,  lftPed);
      TRY_TEST(rgt_mz_fac,  lftPed);

      // minimize
      SupportDeflectionDistributionFactorStrategy d_min_strategy(&my_idf);

      d_min_strategy.GetOptimalDfs(0, stage, fetFx, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDSgl);
      TRY_TEST(right_factor, lftDSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFx, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, lftDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFx, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, lftDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFx, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, lftFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_min_strategy.GetOptimalDfs(0, stage, fetFx, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_min_strategy.GetOptimalDfs(0, stage, fetFy, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDSgl);
      TRY_TEST(right_factor, lftDSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFy, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, lftDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFy, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftDMul);
      TRY_TEST(right_factor, lftDMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetFy, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatV);
      TRY_TEST(right_factor, lftFatV);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_min_strategy.GetOptimalDfs(0, stage, fetFy, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_min_strategy.GetOptimalDfs(0, stage, fetMz, dftSingleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTSgl);
      TRY_TEST(right_factor, lftTSgl);
      TRY_TEST(left_dftype,  dftSingleLane);
      TRY_TEST(right_dftype, dftSingleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetMz, dftMultipleLane, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTMul);
      TRY_TEST(right_factor, lftTMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetMz, dftEnvelope, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftTMul);
      TRY_TEST(right_factor, lftTMul);
      TRY_TEST(left_dftype,  dftMultipleLane);
      TRY_TEST(right_dftype, dftMultipleLane);
      d_min_strategy.GetOptimalDfs(0, stage, fetMz, dftFatigue, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftFatM);
      TRY_TEST(right_factor, lftFatM);
      TRY_TEST(left_dftype,  dftFatigue);
      TRY_TEST(right_dftype, dftFatigue);
      d_min_strategy.GetOptimalDfs(0, stage, fetMz, dftPedestrian, &left_factor, &left_dftype, &right_factor, &right_dftype);
      TRY_TEST(left_factor,  lftPed);
      TRY_TEST(right_factor, lftPed);
      TRY_TEST(left_dftype,  dftPedestrian);
      TRY_TEST(right_dftype, dftPedestrian);

      d_min_strategy.GetConcurrentDfs(0, stage, dftSingleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDSgl);
      TRY_TEST(lft_fy_fac,  lftDSgl);
      TRY_TEST(lft_mz_fac,  lftTSgl);
      TRY_TEST(rgt_fx_fac,  lftDSgl);
      TRY_TEST(rgt_fy_fac,  lftDSgl);
      TRY_TEST(rgt_mz_fac,  lftTSgl);

      d_min_strategy.GetConcurrentDfs(0, stage, dftMultipleLane, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDMul);
      TRY_TEST(lft_fy_fac,  lftDMul);
      TRY_TEST(lft_mz_fac,  lftTMul);
      TRY_TEST(rgt_fx_fac,  lftDMul);
      TRY_TEST(rgt_fy_fac,  lftDMul);
      TRY_TEST(rgt_mz_fac,  lftTMul);

      d_min_strategy.GetConcurrentDfs(0, stage, dftEnvelope, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftDMul);
      TRY_TEST(lft_fy_fac,  lftDMul);
      TRY_TEST(lft_mz_fac,  lftTMul);
      TRY_TEST(rgt_fx_fac,  lftDMul);
      TRY_TEST(rgt_fy_fac,  lftDMul);
      TRY_TEST(rgt_mz_fac,  lftTMul);

      d_min_strategy.GetConcurrentDfs(0, stage, dftFatigue, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftFatV);
      TRY_TEST(lft_fy_fac,  lftFatV);
      TRY_TEST(lft_mz_fac,  lftFatM);
      TRY_TEST(rgt_fx_fac,  lftFatV);
      TRY_TEST(rgt_fy_fac,  lftFatV);
      TRY_TEST(rgt_mz_fac,  lftFatM);

      d_min_strategy.GetConcurrentDfs(0, stage, dftPedestrian, &lft_fx_fac, &lft_fy_fac, &lft_mz_fac, &rgt_fx_fac, &rgt_fy_fac, &rgt_mz_fac);
      TRY_TEST(lft_fx_fac,  lftPed);
      TRY_TEST(lft_fy_fac,  lftPed);
      TRY_TEST(lft_mz_fac,  lftPed);
      TRY_TEST(rgt_fx_fac,  lftPed);
      TRY_TEST(rgt_fy_fac,  lftPed);
      TRY_TEST(rgt_mz_fac,  lftPed);
   }
   catch(...)
   {
      _ASSERT(0);
      TRY_TEST(1,2);
   }


}

