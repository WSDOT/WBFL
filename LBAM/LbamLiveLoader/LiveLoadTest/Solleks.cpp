///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
// Copyright © 1999-2019  Washington State Department of Transportation
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

// Solleks.cpp: implementation of the Solleks class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Solleks.h"

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
Solleks::Solleks()
{
}

Solleks::~Solleks()
{
}

void Solleks::Test()
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
   std::_tofstream os("Solleks.txt");

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
      // Support Deflections
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

#define RETURN_ON_FAIL(_hr_) if (FAILED(_hr_)) return _hr_

HRESULT CreateASegment(ISegment** Segment, Float64 E, Float64 A, Float64 I, Float64 Depth, Float64 Length)
{
   // set up cross section
   HRESULT hr;
   CComPtr<ISegmentCrossSection> pcs;
   hr = pcs.CoCreateInstance( CLSID_SegmentCrossSection );
   RETURN_ON_FAIL(hr);

   Float64 ea = E*A;
   Float64 ei = E*I;
   hr = pcs->put_EAForce(ea);
   RETURN_ON_FAIL(hr);
   hr = pcs->put_EIForce(ei);
   RETURN_ON_FAIL(hr);
   hr = pcs->put_EADefl(ea);
   RETURN_ON_FAIL(hr);
   hr = pcs->put_EIDefl(ei);
   RETURN_ON_FAIL(hr);
   hr = pcs->put_ThermalCoeff(0.0);
   RETURN_ON_FAIL(hr);
   hr = pcs->put_Depth(Depth);
   RETURN_ON_FAIL(hr);

   // put one stress point on the top and bottom of the section
   Float64 sa = 1.0/A;
   Float64 sm = (Depth/2.0)/I;

   CComPtr<IStressPoints> psps;
   hr = pcs->get_StressPoints(&psps);

   CComPtr<IStressPoint> psst, pssb;
   hr = psst.CoCreateInstance( CLSID_StressPoint ) ;
   RETURN_ON_FAIL(hr);
   hr = pssb.CoCreateInstance( CLSID_StressPoint ) ;
   RETURN_ON_FAIL(hr);

   hr = psst->put_Sm(-sm);
   RETURN_ON_FAIL(hr);
   hr = psst->put_Sa(sa);
   RETURN_ON_FAIL(hr);
   hr = psps->Add(psst);
   RETURN_ON_FAIL(hr);

   hr = pssb->put_Sm(sm);
   RETURN_ON_FAIL(hr);
   hr = pssb->put_Sa(sa);
   RETURN_ON_FAIL(hr);
   hr = psps->Add(pssb);
   RETURN_ON_FAIL(hr);

   // segment
   CComPtr<ISegment> pseg;
   hr = pseg.CoCreateInstance( CLSID_Segment );
   RETURN_ON_FAIL(hr);

   hr = pseg->put_Length(Length);
   RETURN_ON_FAIL(hr);

   hr = pseg->putref_SegmentCrossSection(pcs);
   RETURN_ON_FAIL(hr);

   return pseg.CopyTo(Segment);
}


HRESULT CreateASimpleLBAM(ILBAMModel** model)
{
   HRESULT hr;
   // create a simple two span model
   CComPtr<ILBAMLRFDFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_LRFDFactory), S_OK);
   CComPtr<IDblArray> span_lengths;
   span_lengths.CoCreateInstance(CLSID_DblArray);
   span_lengths->Add(70.0);
   span_lengths->Add(90.0);
   span_lengths->Add(70.0);
   hr = factory->CreateSimpleModel(span_lengths, 1, 1, 1, 1, model);
   TRY_TEST(hr, S_OK);

   // make the model have two stages
   CComPtr<IStages> stages;
   TRY_TEST( (*model)->get_Stages(&stages), S_OK);
   CComPtr<IStage> stage2;
   TRY_TEST(stage2.CoCreateInstance(CLSID_Stage), S_OK);
   TRY_TEST(stage2->put_Name(CComBSTR("Stage 2")), S_OK);
   TRY_TEST(stages->Add(stage2), S_OK);

   // modify supports so they slant
   CComPtr<ISegment> segment;
   TRY_TEST(CreateASegment(&segment, 1.0, 1.0, 1.0, 1.0, 64.5), S_OK);

   CComPtr<ISupports> supports;
   TRY_TEST( (*model)->get_Supports(&supports), S_OK);

   CComPtr<ISupport> s0, s1, s2, s3;
   TRY_TEST( supports->get_Item(0, &s0), S_OK);
   TRY_TEST( s0->put_BoundaryCondition(bcRoller), S_OK);

   TRY_TEST( supports->get_Item(1, &s1), S_OK);
   TRY_TEST( s1->put_Length(64.5), S_OK);
   TRY_TEST( s1->put_BottomOffset(-39.26), S_OK);
   TRY_TEST( s1->put_BoundaryCondition(bcFixed), S_OK);
   TRY_TEST( s1->put_TopRelease(VARIANT_TRUE), S_OK);
   TRY_TEST( s1->AddSegment(CComBSTR("Stage 1"), segment), S_OK);
   TRY_TEST( s1->AddSegment(CComBSTR("Stage 2"), segment), S_OK);

   TRY_TEST( supports->get_Item(2, &s2), S_OK);
   TRY_TEST( s2->put_Length(64.5), S_OK);
   TRY_TEST( s2->put_BottomOffset( 39.26), S_OK);
   TRY_TEST( s2->put_BoundaryCondition(bcFixed), S_OK);
   TRY_TEST( s2->put_TopRelease(VARIANT_TRUE), S_OK);
   TRY_TEST( s2->AddSegment(CComBSTR("Stage 1"), segment), S_OK);
   TRY_TEST( s2->AddSegment(CComBSTR("Stage 2"), segment), S_OK);

   TRY_TEST( supports->get_Item(3, &s3), S_OK);
   TRY_TEST( s3->put_BoundaryCondition(bcRoller), S_OK);

   // add superstructure members so we can have hinges
   CComPtr<ISuperstructureMembers> ssms;
   TRY_TEST( (*model)->get_SuperstructureMembers(&ssms), S_OK);
   CComPtr<ISuperstructureMember> ssm1, ssm2, ssm3;
   TRY_TEST( ssms->get_Item(0,&ssm1), S_OK);
   TRY_TEST( ssm1->put_Length(77.5), S_OK);
   CComPtr<ISegment> ssegment;
   TRY_TEST( ssm1->get_Segment(CComBSTR("Stage 1"),0,&ssegment), S_OK);
   TRY_TEST( ssm1->AddSegment(CComBSTR("Stage 2"), ssegment), S_OK);

   TRY_TEST( ssm1->Clone(&ssm2), S_OK);
   TRY_TEST( ssm2->put_Length(75.0), S_OK);
   TRY_TEST( ssms->Add(ssm2), S_OK);
   TRY_TEST( ssm1->Clone(&ssm3), S_OK);
   TRY_TEST( ssms->Add(ssm3), S_OK);
   // hinges become continuous in stage 2
   TRY_TEST( ssm1->SetEndReleaseRemovalStage(ssRight,CComBSTR("Stage 2")),S_OK);
   TRY_TEST( ssm1->SetEndRelease(ssRight, mrtMz), S_OK);
   TRY_TEST( ssm3->SetEndReleaseRemovalStage(ssLeft,CComBSTR("Stage 2")),S_OK);
   TRY_TEST( ssm3->SetEndRelease(ssLeft,  mrtMz), S_OK);

   // add variable distribution factors
   CComPtr<IDistributionFactor> end_df, mid_df;
   TRY_TEST(end_df.CoCreateInstance(CLSID_DistributionFactor), S_OK);
   TRY_TEST(mid_df.CoCreateInstance(CLSID_DistributionFactor), S_OK);
   end_df->SetG(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
   mid_df->SetG(21,22,23,24,25,26,27,28,29,30,31,32,33,34,35);

   CComPtr<IDistributionFactorSegment> end_seg, mid_seg;
   TRY_TEST( end_seg.CoCreateInstance( CLSID_DistributionFactorSegment ) , S_OK );
   TRY_TEST( mid_seg.CoCreateInstance( CLSID_DistributionFactorSegment ) , S_OK );
   end_seg->put_Length(77.5);
   end_seg->putref_DistributionFactor(end_df);
   mid_seg->put_Length(75.0);
   mid_seg->putref_DistributionFactor(mid_df);

   CComPtr<IDistributionFactors> ssdfs;
   TRY_TEST( (*model)->get_DistributionFactors(&ssdfs), S_OK);
   ssdfs->Add(end_seg);
   ssdfs->Add(mid_seg);
   ssdfs->Add(end_seg);

   // configure LRFD live loads and combinations
   CComPtr<IUnitServer> unitserver;
   unitserver.CoCreateInstance(CLSID_UnitServer);
   unitserver->SetBaseUnits(CComBSTR("lbm"), CComBSTR("ft"), CComBSTR("sec"), CComBSTR("fahr"), CComBSTR("deg"));

   hr = factory->ConfigureLiveLoad(*model, VARIANT_TRUE, suUS, unitserver);
   hr = factory->ConfigureLoadCombinations(*model);

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
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_sw, 0, mtSuperstructureMember, -1000.0);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_sw, 1, mtSuperstructureMember, -1000.0);
   CreateDistributedLoad(dls, CComBSTR("Stage 1"), lgn_sw, 2, mtSuperstructureMember, -1000.0);

   CComBSTR lgn_br("Barrier");
   CComPtr<ILoadGroup> lgbr;
   TRY_TEST( lgbr.CoCreateInstance(CLSID_LoadGroup), S_OK);
   TRY_TEST( lgbr->put_Name(lgn_br), S_OK);
   TRY_TEST( lgs->Add(lgbr), S_OK);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_br, 0, mtSuperstructureMember, -250.0);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_br, 1, mtSuperstructureMember, -250.0);
   CreateDistributedLoad(dls, CComBSTR("Stage 2"), lgn_br, 2, mtSuperstructureMember, -250.0);

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
      TRY_TEST( pss->Open( CComBSTR("SolleksDf.xml")), S_OK );

      // get interface pointer 
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( (*model)->QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );
      TRY_TEST( pss->Close(), S_OK );
   }

   return S_OK;
}
