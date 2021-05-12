///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
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

// TestSimpleTwoSpan.cpp: implementation of the TestSimpleTwoSpan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSimpleTwoSpan.h"

#include <string>
#include <fstream>
#include <iomanip>

#include <MathEx.h>
#include "..\..\LBAMTestUtils.h"
#include "LiveLoadTestUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static HRESULT CreateASimpleLBAM(ILBAMModel** model);

inline HRESULT CreateDistributedLoad(IDistributedLoads* dls, BSTR stage, BSTR loadGroup, MemberIDType mbrId, MemberType mType, Float64 ldVal)
{
   CComPtr<IDistributedLoad> dl;
   TRY_TEST( dl.CoCreateInstance(CLSID_DistributedLoad), S_OK);
   TRY_TEST( dl->put_Direction(ldFy), S_OK);
   TRY_TEST( dl->put_MemberID(mbrId), S_OK);
   TRY_TEST( dl->put_MemberType(mType), S_OK);
   TRY_TEST( dl->put_StartLocation(0.0), S_OK);
   TRY_TEST( dl->put_EndLocation(-1.0), S_OK);
   TRY_TEST( dl->put_WStart(ldVal), S_OK);
   TRY_TEST( dl->put_WEnd(ldVal), S_OK);
   TRY_TEST( dls->Add(stage, loadGroup,dl,nullptr), S_OK);
   return S_OK;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestSimpleTwoSpan::TestSimpleTwoSpan()
{
}

TestSimpleTwoSpan::~TestSimpleTwoSpan()
{
}

void TestSimpleTwoSpan::Test()
{
   // create a simple lbam model to analyze
   CComPtr<ILBAMModel> model;
   TRY_TEST(CreateASimpleLBAM(&model), S_OK);

   // set up response engine 
   CComPtr<ILBAMAnalysisEngine> pengine;
   TRY_TEST(pengine.CoCreateInstance( CLSID_LBAMAnalysisEngine ), S_OK );

   TRY_TEST(pengine->Initialize(model, atForce), S_OK);

   CComPtr<ILiveLoadModelResponse> llm_response;
   TRY_TEST(pengine->get_LiveLoadModelResponse(&llm_response), S_OK);

   CComPtr<IBasicVehicularResponse> basic_response;
   TRY_TEST(pengine->get_BasicVehicularResponse(&basic_response), S_OK);

   // dump results to a file
   std::_tofstream os("TestSimpleTwoSpan.txt");

   for (long is = 0; is<1; is++)
   {
      CComBSTR stage;
      if (is==0)
         stage = "Stage 1";
      else
         stage = "Stage 2";

      // ready to compute something
      // ----------------------------------------------------------
      // Forces
      // Mz
      CompLLForceResults(stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   // -----
      CompLLForceResults(stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   //-------
      CompLLForceResults(stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      // Fy
      CompLLForceResults(stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   // -----
      CompLLForceResults(stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   //-------
      CompLLForceResults(stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLForceResults(stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLForceResults(stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      // ----------------------------------------------------------
      // Deflections
      // Mz
      CompLLDeflResults(stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   // -----
      CompLLDeflResults(stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   //-------
      CompLLDeflResults(stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      // Fy
      CompLLDeflResults(stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   // -----
      CompLLDeflResults(stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   //-------
      CompLLDeflResults(stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLDeflResults(stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLDeflResults(stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      // ----------------------------------------------------------
      // Reactions
      // Mz
      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   // -----
      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   //-------
      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      // Fy
      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   // -----
      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   //-------
      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLReactionResults(model, stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLReactionResults(model, stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      // ----------------------------------------------------------
      // SupportDeflections
      // Mz
      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   // -----
      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   //-------
      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetMz, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      // Fy
      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_TRUE, llm_response, basic_response, os);
   // -----
      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_TRUE,  VARIANT_TRUE, llm_response, basic_response, os);
   //-------
      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcTruckOnly,          VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcLaneOnly,           VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcTruckPlusLane,      VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcTruckLaneEnvelope,  VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

      CompLLSupportDeflectionResults(model, stage, optMaximize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);
      CompLLSupportDeflectionResults(model, stage, optMinimize, fetFy, vlcSidewalkOnly,       VARIANT_FALSE, VARIANT_FALSE, llm_response, basic_response, os);

   }
}




HRESULT CreateASimpleLBAM(ILBAMModel** model)
{
   HRESULT hr;
   // create a simple two span model
   CComPtr<ILBAMFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_LRFDFactory), S_OK);
   CComPtr<IDblArray> span_lengths;
   span_lengths.CoCreateInstance(CLSID_DblArray);
   span_lengths->Add(90.0);
   span_lengths->Add(90.0);
   hr = factory->CreateSimpleModel(span_lengths, 1, 1, 1, 1, model);
   TRY_TEST(hr, S_OK);

   // configure LRFD live loads and combinations
   ConfigureLrfdLiveLoadModelInKipFeet(*model);
   ConfigureLrfdLoadCombinations(*model);

   // create a barrier load group and add it to the dc load case
   // create some load groups with loads (or not)
   CComPtr<ILoadGroups> lgs;
   TRY_TEST( (*model)->get_LoadGroups(&lgs), S_OK);

   CComPtr<IDistributedLoads> dls;
   TRY_TEST( (*model)->get_DistributedLoads(&dls), S_OK);

   CComBSTR lgn_sw("Self Weight");
   CComPtr<ILoadGroup> lgsw;
   TRY_TEST( lgsw.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgsw->put_Name(lgn_sw), S_OK);
   TRY_TEST( lgs->Add(lgsw), S_OK);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_sw, 0, mtSuperstructureMember, -1.0);

   CComBSTR lgn_br("Barrier");
   CComPtr<ILoadGroup> lgbr;
   TRY_TEST( lgbr.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgbr->put_Name(lgn_br), S_OK);
   TRY_TEST( lgs->Add(lgbr), S_OK);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_br, 0, mtSuperstructureMember, -0.25);

   CComPtr<ILoadCases> lcs;
   TRY_TEST( (*model)->get_LoadCases(&lcs), S_OK);
   CComPtr<ILoadCase> lcdc;
   TRY_TEST( lcs->Find(CComBSTR("DC"),&lcdc), S_OK);
   lcdc->AddLoadGroup(lgn_br);
   lcdc->AddLoadGroup(lgn_sw);

   // add some pois
   PoiIDType last_val;
   TRY_TEST(factory->GeneratePOIsOnSuperstructure(*model, 0, 10, &last_val), S_OK);


   // Save off to file for later inspection
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("TestSimpleTwoSpan.xml")), S_OK );

      // get interface pointer 
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( (*model)->QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );
      TRY_TEST( pss->Close(), S_OK );
   }

   return S_OK;
}
