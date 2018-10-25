///////////////////////////////////////////////////////////////////////
// LBAM Utility - Longitindal Bridge Analysis Model
// Copyright © 1999-2016  Washington State Department of Transportation
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

// LBAMFactory.cpp : Implementation of CLBAMFactory
#include "stdafx.h"
#include "WBFLLBAMUtility.h"
#include "LBAMFactory.h"
#include "..\LBAMUtils.h"
#include <WBFLComCollections.h>

#include "LBAMUtility.hh" 
#include "LBAM.hh" 

#include <MathEx.h>
#include <vector>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// free functions
HRESULT AddPOI(IPOIs* pPOIs, IPOI* pPOI);

// utility classes
struct PoiLoc
{
   Float64      m_Location;
   PoiIDType    m_ID;
   MemberType   m_MbrType;
   Float64      m_MbrLoc;
   MemberIDType m_MbrID;

   PoiLoc(PoiIDType id, MemberType mbrType, MemberIDType mbrId, Float64 mbrLoc, Float64 location):
   m_ID(id),
   m_Location(location),
   m_MbrType(mbrType),
   m_MbrLoc(mbrLoc),
   m_MbrID(mbrId)
   {;}

   bool operator< (const PoiLoc& other) const
   { 
      if (IsEqual(m_Location, other.m_Location))
      {
         // tie breaker if equal locations - to stablize sort somewhat
         if (m_MbrType==mtSpan && other.m_MbrType==mtSpan)
         {
            return m_MbrID < other.m_MbrID;
         }
         else if (m_MbrType==mtSuperstructureMember && other.m_MbrType==mtSpan)
         {
            return other.m_MbrLoc==0.0;
         }
         else if (m_MbrType==mtSpan && other.m_MbrType==mtSuperstructureMember)
         {
            return m_MbrLoc!=0.0;
         }
         else
         {
            // use random cpu chatter
            return m_Location < other.m_Location;
         }
      }
      else
      {
         return m_Location < other.m_Location; 
      }
   }
private:
   PoiLoc();
};


STDMETHODIMP CLBAMFactory::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILBAMFactory
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLBAMFactory::CreateSimpleModel(IDblArray* SpanLengths, Float64 E, Float64 A, Float64 I, Float64 Depth, ILBAMModel **newModel)
{
   CHECK_IN(SpanLengths);
   CHECK_RETOBJ(newModel);
   // first do some data checking
   // let's see how many pois we have to return results for
   try
   {
      CHRException hr;

      CollectionIndexType span_cnt;
      hr = SpanLengths->get_Count(&span_cnt);
      SpanIndexType nSpans = SpanIndexType(span_cnt);

      // check input data
      if (E<=0.0)
         THROW_LBAMU(E_MUST_BE_GT_ZERO);

      if (A<=0.0)
         THROW_LBAMU(A_MUST_BE_GT_ZERO);

      if (I<=0.0)
         THROW_LBAMU(I_MUST_BE_GT_ZERO);

      if (Depth<=0.0)
         THROW_LBAMU(DEPTH_MUST_BE_GT_ZERO);

      // create a model and start building it.
      CComPtr<ILBAMModel> pmodel;
      hr = pmodel.CoCreateInstance(CLSID_LBAMModel);

      // create spans
      CComPtr<ISpans> pspans;
      hr = pmodel->get_Spans(&pspans);

      Float64 total_length = 0.0;
      for (SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++)
      {
         Float64 length;
         hr = SpanLengths->get_Item(spanIdx,&length);

         if (length<=0.0)
            THROW_LBAMU(SPAN_LENGTH_MUST_BE_GT_ZERO);

         CComPtr<ISpan> pspan;
         hr = pspan.CoCreateInstance(CLSID_Span);
         hr = pspan->put_Length(length);
         hr = pspans->Add(pspan);

         total_length += length;
      }

      // set up cross section
      CComPtr<ISegmentCrossSection> pcs;
      hr = pcs.CoCreateInstance( CLSID_SegmentCrossSection );

      Float64 ea = E*A;
      Float64 ei = E*I;
      hr = pcs->put_EAForce(ea);
      hr = pcs->put_EIForce(ei);
      hr = pcs->put_EADefl(ea);
      hr = pcs->put_EIDefl(ei);
      hr = pcs->put_ThermalCoeff(0.0);
      hr = pcs->put_Depth(Depth);

      // put one stress point on the top, middle, and bottom of the section
      Float64 sa = 1.0/A;
      Float64 sm = (Depth/2.0)/I;

      CComPtr<IStressPoints> psps;
      hr = pcs->get_StressPoints(&psps);

      CComPtr<IStressPoint> psst, pssc, pssb;
      hr = psst.CoCreateInstance( CLSID_StressPoint ) ;
      hr = pssc.CoCreateInstance( CLSID_StressPoint ) ;
      hr = pssb.CoCreateInstance( CLSID_StressPoint ) ;

      hr = psst->put_Sm(-sm);
      hr = psst->put_Sa(sa);
      hr = psps->Add(psst);

      hr = pssc->put_Sm(0.0);
      hr = pssc->put_Sa(sa);
      hr = psps->Add(pssc);

      hr = pssb->put_Sm(sm);
      hr = pssb->put_Sa(sa);
      hr = psps->Add(pssb);

      // one prismatic segment across entire superstructure
      CComPtr<ISegment> pseg;
      hr = pseg.CoCreateInstance( CLSID_Segment );
      hr = pseg->put_Length(total_length);
      hr = pseg->putref_SegmentCrossSection(pcs);

      // create superstructure member
      CComPtr<ISuperstructureMembers> pssms;
      hr = pmodel->get_SuperstructureMembers(&pssms);

      CComPtr<ISuperstructureMember> pssm;
      hr = pssm.CoCreateInstance( CLSID_SuperstructureMember );
      hr = pssm->put_Length(total_length);
      hr = pssm->AddSegment(_bstr_t("Stage 1"), pseg);

      hr = pssms->Add(pssm);

      // create supports
      CComPtr<ISupports> psupports;
      hr = pmodel->get_Supports(&psupports);

      SupportIndexType nSupports = SupportIndexType(nSpans+1);
      for (SupportIndexType supportIdx = 0; supportIdx < nSupports; supportIdx++)
      {
         CComPtr<ISupport> psupport;
         hr = psupport.CoCreateInstance(CLSID_Support);

         if (supportIdx == 0 || supportIdx == (nSupports-1) )
         {
            hr = psupport->put_BoundaryCondition(bcPinned);
         }
         else
         {
            hr = psupport->put_BoundaryCondition(bcRoller);
         }

         hr = psupports->Add(psupport);
      }

      // create stage
      CComPtr<IStages> pstages;
      hr = pmodel->get_Stages(&pstages);

      CComPtr<IStage> pstage;
      hr = pstage.CoCreateInstance(CLSID_Stage);
      hr = pstage->put_Name(_bstr_t("Stage 1"));
      hr = pstages->Add(pstage);

      hr = pmodel.CopyTo(newModel);
   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMFactory);
   }

	return S_OK;
}

STDMETHODIMP CLBAMFactory::GetSupportIDsForStage(ILBAMModel *pModel, BSTR stage, IIDArray* *supportIDs)
{
   CHECK_IN(pModel);
   CHECK_IN(stage);
   CHECK_RETOBJ(supportIDs);

   CHRException hr;

   try
   {
      // start of by putting ids in a temporary vector
      std::vector<SupportIDType> suppids;
      CComPtr<ISupports> Supports;
      hr = pModel->get_Supports(&Supports); // list of Supports in document

      SupportIndexType nSupports;
      hr = Supports->get_Count(&nSupports);
      suppids.reserve(nSupports*12/10);
      if (nSupports != 0)
      {
         for (SupportIndexType supportIdx = 0; supportIdx < nSupports; supportIdx++)
         {
            suppids.push_back( SupportIDType(supportIdx) ); // temporary support index is the ID
         }
      }

      // Next Temporary supports
      CComPtr<ISpans> spans;
      hr = pModel->get_Spans(&spans); // list of Spans in document

      CComPtr<IStages> stages;
      hr = pModel->get_Stages(&stages);

      // get index of current stage
      StageIndexType currentStageIdx;
      hr = stages->FindIndex(stage, &currentStageIdx);

      SpanIndexType nSpans;
      hr = spans->get_Count(&nSpans);
      if (nSpans != 0)
      {
         for (SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++)
         {
            CComPtr<ISpan> span;
            hr = spans->get_Item(spanIdx, &span);

            CComPtr<ITemporarySupports> tempSupports;
            hr = span->get_TemporarySupports(&tempSupports); 

            SupportIndexType nTempSupports;
            hr = tempSupports->get_Count(&nTempSupports);
            for (SupportIndexType tempSupportIdx = 0; tempSupportIdx < nTempSupports; tempSupportIdx++)
            {
               CComPtr<ITemporarySupport> tempSupport;
               hr = tempSupports->get_Item(tempSupportIdx, &tempSupport);

               CComBSTR bstrTempSupportRemovalStage;
               hr = tempSupport->get_StageRemoved(&bstrTempSupportRemovalStage);

               bool bIsInStage = false;
               if (bstrTempSupportRemovalStage.Length()==0)
               {
                  bIsInStage = true;
               }
               else
               {
                  StageIndexType removalStageIdx;
                  hr = stages->FindIndex(bstrTempSupportRemovalStage, &removalStageIdx);

                  if (currentStageIdx < removalStageIdx)
                  {
                     bIsInStage=true;
                  }
               }

               if (bIsInStage)
               {
                  SupportIDType tempSupportID;
                  hr = tempSupport->get_ID(&tempSupportID);

                  suppids.push_back(tempSupportID);
               }
            }
         }
      }

      CComPtr<IIDArray> vsuppids;
      hr = vsuppids.CoCreateInstance(CLSID_IDArray);
      CollectionIndexType size = suppids.size();
      vsuppids->Reserve(size);
      for (CollectionIndexType i=0; i<size; i++)
      {
         vsuppids->Add(suppids[i]);
      }

      *supportIDs = vsuppids.Detach();

   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMLRFDFactory);
   }

	return S_OK;
}

STDMETHODIMP CLBAMFactory::ConfigureLiveLoad(ILBAMModel* pModel, VARIANT_BOOL includeLowBoy, SpecUnitType units, IUnitServer* pUnitServer)
{
   CHRException hr;

   try
   {
      hr = ConfigureDesignLiveLoad(     pModel, lltDesign,     1.33, 1.00, VARIANT_TRUE, includeLowBoy, units, pUnitServer);
      hr = ConfigureFatigueLiveLoad(    pModel, lltFatigue,    1.15, 1.00,                              units, pUnitServer);
      hr = ConfigureDeflectionLiveLoad( pModel, lltDeflection, 1.33, 1.00,                              units, pUnitServer);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMLRFDFactory);
   }
   return S_OK;
}

STDMETHODIMP CLBAMFactory::ConfigureLoadCombinations(ILBAMModel* model)
{
   CHECK_IN(model);

   // This function adds load cases and combinations as per LRFD 3.4.1
   CHRException hr;

   try
   {
      CComPtr<ILoadCases> loadcases;
      hr = model->get_LoadCases(&loadcases);

      // Add load cases
      AddLoadCase(loadcases, CComBSTR("DC"), CComBSTR("Component and Attachments"));
      AddLoadCase(loadcases, CComBSTR("DD"), CComBSTR("Downdrag"));
      AddLoadCase(loadcases, CComBSTR("DW"), CComBSTR("Wearing Surfaces and Utilities"));
      AddLoadCase(loadcases, CComBSTR("EH"), CComBSTR("Horizontal Earth Pressure"));
      AddLoadCase(loadcases, CComBSTR("EV"), CComBSTR("Vertical Earth Pressure"));
      AddLoadCase(loadcases, CComBSTR("ES"), CComBSTR("Earth Surcharge"));
      AddLoadCase(loadcases, CComBSTR("CE"), CComBSTR("Centrifugal Forces"));
      AddLoadCase(loadcases, CComBSTR("BR"), CComBSTR("Braking Force"));
      AddLoadCase(loadcases, CComBSTR("PL"), CComBSTR("Pedestrian Live Load"));
      AddLoadCase(loadcases, CComBSTR("LS"), CComBSTR("Live Load Surcharge"));
      AddLoadCase(loadcases, CComBSTR("EL"), CComBSTR("Locked in Erection Stresses"));
      AddLoadCase(loadcases, CComBSTR("WA"), CComBSTR("Water Loads"));
      AddLoadCase(loadcases, CComBSTR("WS"), CComBSTR("Wind on Structure"));
      AddLoadCase(loadcases, CComBSTR("WL"), CComBSTR("Wind on Live Load"));
      AddLoadCase(loadcases, CComBSTR("FR"), CComBSTR("Friction Forces"));
      AddLoadCase(loadcases, CComBSTR("TU"), CComBSTR("Temperature Uniform"));
      AddLoadCase(loadcases, CComBSTR("CR"), CComBSTR("Creep"));
      AddLoadCase(loadcases, CComBSTR("SH"), CComBSTR("Shrinkage"));
      AddLoadCase(loadcases, CComBSTR("TG"), CComBSTR("Temperature Gradient"));
      AddLoadCase(loadcases, CComBSTR("SE"), CComBSTR("Settlement"));
      AddLoadCase(loadcases, CComBSTR("EQ"), CComBSTR("Earthquake"));
      AddLoadCase(loadcases, CComBSTR("IC"), CComBSTR("Ice"));
      AddLoadCase(loadcases, CComBSTR("CT"), CComBSTR("Vehicular Collision"));
      AddLoadCase(loadcases, CComBSTR("CV"), CComBSTR("Vessel Collision"));

      CComPtr<ILoadCombinations> loadcombos;
      hr = model->get_LoadCombinations(&loadcombos) ;

      // add load combinations
      // STRENGTH-I
      CComPtr<ILoadCombination> strength1;
      hr = strength1.CoCreateInstance(CLSID_LoadCombination) ;
      hr = strength1->put_Name(CComBSTR("STRENGTH-I")) ;
      hr = strength1->put_LoadCombinationType(lctStrength) ;
      hr = strength1->put_LiveLoadFactor(1.75) ;
      hr = strength1->AddLiveLoadModel(lltDesign) ;

      ApplyTypicalLoadFactors(strength1, false);
      ApplyTypicalLiveLoadFactors(strength1, 1.75);
      ApplyTUCRSHLoadFactors(strength1, 0.50);

      hr = loadcombos->Add(strength1) ;

      // STRENGTH-II
      CComPtr<ILoadCombination> strength2;
      hr = strength2.CoCreateInstance(CLSID_LoadCombination) ;
      hr = strength2->put_Name(CComBSTR("STRENGTH-II")) ;
      hr = strength2->put_LoadCombinationType(lctStrength) ;
      hr = strength2->put_LiveLoadFactor(1.35) ;
      hr = strength2->AddLiveLoadModel(lltPermit) ;

      ApplyTypicalLoadFactors(strength2, false);
      ApplyTypicalLiveLoadFactors(strength2, 1.35);
      ApplyTUCRSHLoadFactors(strength2, 0.0);

      hr = loadcombos->Add(strength2) ;

      // STRENGTH-III
      CComPtr<ILoadCombination> strength3;
      hr = strength3.CoCreateInstance(CLSID_LoadCombination) ;
      hr = strength3->put_Name(CComBSTR("STRENGTH-III")) ;
      hr = strength3->put_LoadCombinationType(lctStrength) ;
      hr = strength3->AddLiveLoadModel(lltNone) ;

      ApplyTypicalLoadFactors(strength3, false);
      ApplyTUCRSHLoadFactors(strength3, 0.0);

      hr = strength3->AddLoadCaseFactor(CComBSTR("WS"), 1.40, 1.40) ;

      hr = loadcombos->Add(strength3) ;

      // STRENGTH-IV
      CComPtr<ILoadCombination> strength4;
      hr = strength4.CoCreateInstance(CLSID_LoadCombination) ;
      hr = strength4->put_Name(CComBSTR("STRENGTH-IV")) ;
      hr = strength4->put_LoadCombinationType(lctStrength) ;
      hr = strength4->AddLiveLoadModel(lltNone) ;

      ApplyTypicalLoadFactors(strength4, true);
      ApplyTUCRSHLoadFactors(strength4, 0.0);

      hr = loadcombos->Add(strength4) ;

      // STRENGTH-V
      CComPtr<ILoadCombination> strength5;
      hr = strength5.CoCreateInstance(CLSID_LoadCombination) ;
      hr = strength5->put_Name(CComBSTR("STRENGTH-V")) ;
      hr = strength5->put_LoadCombinationType(lctStrength) ;
      hr = strength5->put_LiveLoadFactor(1.35) ;
      hr = strength5->AddLiveLoadModel(lltDesign) ;

      ApplyTypicalLoadFactors(strength5, false);
      ApplyTypicalLiveLoadFactors(strength5, 1.35);
      ApplyTUCRSHLoadFactors(strength5, 0.0);

      hr = strength5->AddLoadCaseFactor(CComBSTR("WS"), 0.40, 0.40) ;
      hr = strength5->AddLoadCaseFactor(CComBSTR("WL"), 1.00, 1.00) ;

      hr = loadcombos->Add(strength5) ;

      // EXTREME EVENT-I
      CComPtr<ILoadCombination> extevent1;
      hr = extevent1.CoCreateInstance(CLSID_LoadCombination) ;
      hr = extevent1->put_Name(CComBSTR("EXTREME EVENT-I")) ;
      hr = extevent1->put_LoadCombinationType(lctExtremeEvent) ;
      hr = extevent1->put_LiveLoadFactor(1.00); // should be on a project bass
      hr = extevent1->AddLiveLoadModel(lltDesign) ;

      ApplyTypicalLoadFactors(extevent1, false);
      ApplyTypicalLiveLoadFactors(extevent1, 1.75);

      hr = extevent1->AddLoadCaseFactor(CComBSTR("EQ"), 1.00, 1.00) ;

      hr = loadcombos->Add(extevent1) ;

      // EXTREME EVENT-II
      CComPtr<ILoadCombination> extevent2;
      hr = extevent2.CoCreateInstance(CLSID_LoadCombination) ;
      hr = extevent2->put_Name(CComBSTR("EXTREME EVENT-II")) ;
      hr = extevent2->put_LoadCombinationType(lctExtremeEvent) ;
      hr = extevent2->put_LiveLoadFactor(0.50) ;
      hr = extevent2->AddLiveLoadModel(lltDesign) ;

      ApplyTypicalLoadFactors(extevent2, false);
      ApplyTypicalLiveLoadFactors(extevent2, 0.50);

      hr = extevent2->AddLoadCaseFactor(CComBSTR("IC"), 1.00, 1.00) ;
      hr = extevent2->AddLoadCaseFactor(CComBSTR("CT"), 1.00, 1.00) ;
      hr = extevent2->AddLoadCaseFactor(CComBSTR("CV"), 1.00, 1.00) ;

      hr = loadcombos->Add(extevent2) ;

      // SERVICE-I
      CComPtr<ILoadCombination> service1;
      hr = service1.CoCreateInstance(CLSID_LoadCombination) ;
      hr = service1->put_Name(CComBSTR("SERVICE-I")) ;
      hr = service1->put_LoadCombinationType(lctService) ;
      hr = service1->put_LiveLoadFactor(1.00) ;
      hr = service1->AddLiveLoadModel(lltDesign) ;

      ApplyTypicalServiceLoadFactors(service1);
      ApplyTypicalLiveLoadFactors(service1, 1.0);

      hr = service1->AddLoadCaseFactor(CComBSTR("WS"), 0.30, 0.30) ;
      hr = service1->AddLoadCaseFactor(CComBSTR("WL"), 1.00, 1.00) ;

      hr = loadcombos->Add(service1) ;

      // SERVICE-II
      CComPtr<ILoadCombination> service2;
      hr = service2.CoCreateInstance(CLSID_LoadCombination) ;
      hr = service2->put_Name(CComBSTR("SERVICE-II")) ;
      hr = service2->put_LoadCombinationType(lctService) ;
      hr = service2->put_LiveLoadFactor(1.30) ;
      hr = service2->AddLiveLoadModel(lltDesign) ;

      ApplyTypicalServiceLoadFactors(service2);
      ApplyTypicalLiveLoadFactors(service2, 1.3);

      hr = loadcombos->Add(service2) ;

      // SERVICE-III
      CComPtr<ILoadCombination> service3;
      hr = service3.CoCreateInstance(CLSID_LoadCombination) ;
      hr = service3->put_Name(CComBSTR("SERVICE-III")) ;
      hr = service3->put_LoadCombinationType(lctService) ;
      hr = service3->put_LiveLoadFactor(0.80) ;
      hr = service3->AddLiveLoadModel(lltDesign) ;

      ApplyTypicalServiceLoadFactors(service3);
      ApplyTypicalLiveLoadFactors(service3, 0.8);

      hr = loadcombos->Add(service3) ;

      // FATIGUE
      CComPtr<ILoadCombination> fatigue;
      hr = fatigue.CoCreateInstance(CLSID_LoadCombination) ;
      hr = fatigue->put_Name(CComBSTR("FATIGUE")) ;
      hr = fatigue->put_LoadCombinationType(lctFatigue) ;
      hr = fatigue->put_LiveLoadFactor(0.75) ;
      hr = fatigue->AddLiveLoadModel(lltFatigue) ;

      hr = fatigue->AddLoadCaseFactor(CComBSTR("CE"), 0.75, 0.75) ;

      hr = loadcombos->Add(fatigue) ;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMFactory);
   }
   return S_OK;
}

STDMETHODIMP CLBAMFactory::ConfigureDesignLiveLoad(ILBAMModel* pModel, LiveLoadModelType llmt,Float64 imTruck,Float64 imLane, VARIANT_BOOL includeDualTrucks, VARIANT_BOOL includeLowBoy, SpecUnitType units, IUnitServer* pUnitServer)
{
   CHECK_IN(pModel);
   CHECK_IN(pUnitServer);

   CHRException hr;

   try
   {
      CComPtr<IUnitConvert> convert;
      hr = pUnitServer->get_UnitConvert(&convert);

      // set up ll model
      CComPtr<ILiveLoadModel> liveloadmodel;
      hr = GetLiveLoadModel(pModel,llmt,&liveloadmodel);

      hr = liveloadmodel->put_Name(CComBSTR("LRFD Design Vehicular Live Load"));
      hr = liveloadmodel->put_DistributionFactorType(dftEnvelope);

      CComPtr<IVehicularLoads> vehicles;
      hr = liveloadmodel->get_VehicularLoads(&vehicles);

      // get the loads and axle spacing in base units
      Float64 lane_load = (units == suUS ? 0.64 : 9.3);
      hr = convert->ConvertToBaseUnits(lane_load,units==suUS?CComBSTR("kip/ft"):CComBSTR("kN-m"),&lane_load);

      Float64 design_truck_weight[3];
      design_truck_weight[0] = (units == suUS ?  8.0 :  35.0);
      design_truck_weight[1] = (units == suUS ? 32.0 : 145.0);
      design_truck_weight[2] = (units == suUS ? 32.0 : 145.0);
      hr = convert->ConvertToBaseUnits(design_truck_weight[0],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&design_truck_weight[0]);
      hr = convert->ConvertToBaseUnits(design_truck_weight[1],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&design_truck_weight[1]);
      hr = convert->ConvertToBaseUnits(design_truck_weight[2],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&design_truck_weight[2]);

      Float64 design_truck_axles[4]; // index 1,2 are the min and max spacing for the variable axle
                                    // index 3 = minimum headway spacing for dual truck train
      design_truck_axles[0] = (units == suUS ? 14.0 : 4.3);
      design_truck_axles[1] = (units == suUS ? 14.0 : 4.3);
      design_truck_axles[2] = (units == suUS ? 30.0 : 9.1);
      design_truck_axles[3] = (units == suUS ? 50.0 : 15.0);
      hr = convert->ConvertToBaseUnits(design_truck_axles[0],units==suUS?CComBSTR("ft"):CComBSTR("m"),&design_truck_axles[0]);
      hr = convert->ConvertToBaseUnits(design_truck_axles[1],units==suUS?CComBSTR("ft"):CComBSTR("m"),&design_truck_axles[1]);
      hr = convert->ConvertToBaseUnits(design_truck_axles[2],units==suUS?CComBSTR("ft"):CComBSTR("m"),&design_truck_axles[2]);
      hr = convert->ConvertToBaseUnits(design_truck_axles[3],units==suUS?CComBSTR("ft"):CComBSTR("m"),&design_truck_axles[3]);

      Float64 design_tandem_weight[2];
      design_tandem_weight[0] = (units == suUS ? 25.0 : 110.0);
      design_tandem_weight[1] = (units == suUS ? 25.0 : 110.0);
      hr = convert->ConvertToBaseUnits(design_tandem_weight[0],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&design_tandem_weight[0]);
      hr = convert->ConvertToBaseUnits(design_tandem_weight[1],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&design_tandem_weight[1]);

      Float64 design_tandem_axles;
      design_tandem_axles = (units == suUS ? 4.0 : 1.2);
      hr = convert->ConvertToBaseUnits(design_tandem_axles,units==suUS?CComBSTR("ft"):CComBSTR("m"),&design_tandem_axles);
   
      // create variable axle design truck with lane vehicular load
      {
         CComPtr<IVehicularLoad> design_truck; 
         hr = design_truck.CoCreateInstance(CLSID_VehicularLoad);

         hr = design_truck->put_Name(CComBSTR("LRFD Design Truck + Lane"));
         hr = design_truck->put_Applicability(llaEntireStructure);
         hr = design_truck->put_Configuration(vlcTruckPlusLane);
         hr = design_truck->put_UseNotional(VARIANT_TRUE);
         hr = design_truck->put_IMLane(imLane);
         hr = design_truck->put_IMTruck(imTruck);
         hr = design_truck->put_LaneFactor(1.0);
         hr = design_truck->put_TruckFactor(1.0);
         hr = design_truck->put_LaneLoad(lane_load);

         CComPtr<IAxles> axles;
         hr = design_truck->get_Axles(&axles);

         CComPtr<IAxle> axle0, axle1, axle2;
         hr = axle0.CoCreateInstance(CLSID_Axle);
         hr = axle0->put_Weight(design_truck_weight[0]);
         hr = axle0->put_Spacing(design_truck_axles[0]);
         hr = axles->Add(axle0);

         hr = axle1.CoCreateInstance(CLSID_Axle);
         hr = axle1->put_Weight(design_truck_weight[1]);
         hr = axle1->put_Spacing(design_truck_axles[1]);
         hr = axles->Add(axle1);

         hr = axle2.CoCreateInstance(CLSID_Axle);
         hr = axle2->put_Weight(design_truck_weight[2]);
         hr = axles->Add(axle2);

         hr = design_truck->put_VariableAxle(1);
         hr = design_truck->put_VariableMaxSpacing(design_truck_axles[2]);

         hr = vehicles->Add(design_truck);
      }

      // create tandem with lane vehicular load
      {
         CComPtr<IVehicularLoad> design_tandem;
         hr = design_tandem.CoCreateInstance(CLSID_VehicularLoad);

         hr = design_tandem->put_Name(CComBSTR("LRFD Design Tandem + Lane"));
         hr = design_tandem->put_Applicability(llaEntireStructure);
         hr = design_tandem->put_Configuration(vlcTruckPlusLane);
         hr = design_tandem->put_UseNotional(VARIANT_TRUE);
         hr = design_tandem->put_IMLane(imLane);
         hr = design_tandem->put_IMTruck(imTruck);
         hr = design_tandem->put_LaneFactor(1.0);
         hr = design_tandem->put_TruckFactor(1.0);
         hr = design_tandem->put_LaneLoad(lane_load);

         CComPtr<IAxles> axles;
         hr = design_tandem->get_Axles(&axles);

         CComPtr<IAxle> axle0, axle1;
         hr = axle0.CoCreateInstance(CLSID_Axle);
         hr = axle0->put_Weight(design_tandem_weight[0]);
         hr = axle0->put_Spacing(design_tandem_axles);
         hr = axles->Add(axle0);

         hr = axle1.CoCreateInstance(CLSID_Axle);
         hr = axle1->put_Weight(design_tandem_weight[1]);
         hr = axles->Add(axle1);

         hr = vehicles->Add(design_tandem);
      }      

      // create dual truck train
      if ( includeDualTrucks == VARIANT_TRUE )
      {
         CComPtr<IVehicularLoad> dual_truck_train;
         hr = dual_truck_train.CoCreateInstance(CLSID_VehicularLoad);

         hr = dual_truck_train->put_Name(CComBSTR("LRFD Truck Train [90%(Truck + Lane)]"));
         hr = dual_truck_train->put_Applicability(llaContraflexure);
         hr = dual_truck_train->put_Configuration(vlcTruckPlusLane);
         hr = dual_truck_train->put_UseNotional(VARIANT_TRUE);  // this truck must be notional
         hr = dual_truck_train->put_IMLane(imLane);
         hr = dual_truck_train->put_IMTruck(imTruck);
         hr = dual_truck_train->put_LaneFactor(0.9);
         hr = dual_truck_train->put_TruckFactor(0.9);
         hr = dual_truck_train->put_LaneLoad(lane_load);

         CComPtr<IAxles> axles;
         hr = dual_truck_train->get_Axles(&axles);

         CComPtr<IAxle> axle0, axle1, axle2, axle3, axle4, axle5;
         hr = axle0.CoCreateInstance(CLSID_Axle);
         hr = axle0->put_Weight(design_truck_weight[0]);
         hr = axle0->put_Spacing(design_truck_axles[0]);
         hr = axles->Add(axle0);

         hr = axle1.CoCreateInstance(CLSID_Axle);
         hr = axle1->put_Weight(design_truck_weight[1]);
         hr = axle1->put_Spacing(design_truck_axles[1]);
         hr = axles->Add(axle1);

         hr = axle2.CoCreateInstance(CLSID_Axle);
         hr = axle2->put_Weight(design_truck_weight[2]);
         hr = axle2->put_Spacing(design_truck_axles[3]);
         hr = axles->Add(axle2);

         hr = axle3.CoCreateInstance(CLSID_Axle);
         hr = axle3->put_Weight(design_truck_weight[0]);
         hr = axle3->put_Spacing(design_truck_axles[0]);
         hr = axles->Add(axle3);

         hr = axle4.CoCreateInstance(CLSID_Axle);
         hr = axle4->put_Weight(design_truck_weight[1]);
         hr = axle4->put_Spacing(design_truck_axles[1]);
         hr = axles->Add(axle4);

         hr = axle5.CoCreateInstance(CLSID_Axle);
         hr = axle5->put_Weight(design_truck_weight[2]);
         hr = axles->Add(axle5);

         // Use an outrageously high value for the max variable spacing.
         hr = dual_truck_train->put_VariableAxle(2);
         hr = dual_truck_train->put_VariableMaxSpacing(1.0E100);

         hr = vehicles->Add(dual_truck_train);
      }

      // only apply low boy only if asked
      if (includeLowBoy == VARIANT_TRUE)
      {
         Float64 min_spac_axles = (units == suUS ? 26.0 : 8.0);
         hr = convert->ConvertToBaseUnits(min_spac_axles,units==suUS?CComBSTR("ft"):CComBSTR("m"),&min_spac_axles);
         
         Float64 max_spac_axles = (units == suUS ? 40.0 : 12.0);
         hr = convert->ConvertToBaseUnits(max_spac_axles,units==suUS?CComBSTR("ft"):CComBSTR("m"),&max_spac_axles);

         CComPtr<IVehicularLoad> lowboy;
         hr = lowboy.CoCreateInstance(CLSID_VehicularLoad);

         hr = lowboy->put_Name(CComBSTR("LRFD Low Boy (Dual Tandem + Lane)"));
         hr = lowboy->put_Applicability(llaContraflexure);
         hr = lowboy->put_Configuration(vlcTruckPlusLane);
         hr = lowboy->put_UseNotional(VARIANT_TRUE);
         hr = lowboy->put_IMLane(imLane);
         hr = lowboy->put_IMTruck(imTruck);
         hr = lowboy->put_LaneFactor(1.0);
         hr = lowboy->put_TruckFactor(1.0);
         hr = lowboy->put_LaneLoad(lane_load);

         CComPtr<IAxles> axles;
         hr = lowboy->get_Axles(&axles);

         CComPtr<IAxle> axle0, axle1, axle2, axle3;
         hr = axle0.CoCreateInstance(CLSID_Axle);
         hr = axle0->put_Weight(design_tandem_weight[0]);
         hr = axle0->put_Spacing(design_tandem_axles);
         hr = axles->Add(axle0);

         hr = axle1.CoCreateInstance(CLSID_Axle);
         hr = axle1->put_Weight(design_tandem_weight[1]);
         hr = axle1->put_Spacing(min_spac_axles);
         hr = axles->Add(axle1);

         hr = axle2.CoCreateInstance(CLSID_Axle);
         hr = axle2->put_Weight(design_tandem_weight[0]);
         hr = axle2->put_Spacing(design_tandem_axles);
         hr = axles->Add(axle2);

         hr = axle3.CoCreateInstance(CLSID_Axle);
         hr = axle3->put_Weight(design_tandem_weight[1]);
         hr = axles->Add(axle3);

         hr = lowboy->put_VariableAxle(1);
         hr = lowboy->put_VariableMaxSpacing(max_spac_axles);

         hr = vehicles->Add(lowboy);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMLRFDFactory);
   }
   return S_OK;
}

STDMETHODIMP CLBAMFactory::ConfigureFatigueLiveLoad(ILBAMModel* pModel, LiveLoadModelType llmt,Float64 imTruck,Float64 imLane,SpecUnitType units,IUnitServer* pUnitServer)
{
   CHECK_IN(pModel);
   CHECK_IN(pUnitServer);
   CHRException hr;

   try
   {
      CComPtr<IUnitConvert> convert;
      hr = pUnitServer->get_UnitConvert(&convert);

      CComPtr<ILiveLoadModel> liveloadmodel;
      hr = GetLiveLoadModel(pModel,llmt,&liveloadmodel);

      hr = liveloadmodel->put_Name(CComBSTR("LRFD Fatigue Vehicular Live Load"));
      hr = liveloadmodel->put_DistributionFactorType(dftFatigue);

      CComPtr<IVehicularLoads> vehicles;
      hr = liveloadmodel->get_VehicularLoads(&vehicles);

      // get the loads and axle spacing in base units
      Float64 fatigue_truck_weight[3];
      fatigue_truck_weight[0] = (units == suUS ?  8.0 :  35.0);
      fatigue_truck_weight[1] = (units == suUS ? 32.0 : 145.0);
      fatigue_truck_weight[2] = (units == suUS ? 32.0 : 145.0);
      hr = convert->ConvertToBaseUnits(fatigue_truck_weight[0],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&fatigue_truck_weight[0]);
      hr = convert->ConvertToBaseUnits(fatigue_truck_weight[1],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&fatigue_truck_weight[1]);
      hr = convert->ConvertToBaseUnits(fatigue_truck_weight[2],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&fatigue_truck_weight[2]);

      Float64 fatigue_truck_axles[2];
      fatigue_truck_axles[0] = (units == suUS ? 14.0 : 4.3);
      fatigue_truck_axles[1] = (units == suUS ? 30.0 : 9.0);
      hr = convert->ConvertToBaseUnits(fatigue_truck_axles[0],units==suUS?CComBSTR("ft"):CComBSTR("m"),&fatigue_truck_axles[0]);
      hr = convert->ConvertToBaseUnits(fatigue_truck_axles[1],units==suUS?CComBSTR("ft"):CComBSTR("m"),&fatigue_truck_axles[1]);

      // create fixed axle fatigue truck without lane 
      {
         CComPtr<IVehicularLoad> fatigue_truck; 
         hr = fatigue_truck.CoCreateInstance(CLSID_VehicularLoad);

         hr = fatigue_truck->put_Name(CComBSTR("LRFD Fatigue Truck"));
         hr = fatigue_truck->put_Applicability(llaEntireStructure);
         hr = fatigue_truck->put_Configuration(vlcTruckOnly);
         hr = fatigue_truck->put_UseNotional(VARIANT_FALSE);
         hr = fatigue_truck->put_IMLane(imLane);
         hr = fatigue_truck->put_IMTruck(imTruck);
         hr = fatigue_truck->put_LaneFactor(1.0);
         hr = fatigue_truck->put_TruckFactor(1.0);
         hr = fatigue_truck->put_LaneLoad(0.0);

         CComPtr<IAxles> axles;
         hr = fatigue_truck->get_Axles(&axles);

         CComPtr<IAxle> axle0, axle1, axle2;
         hr = axle0.CoCreateInstance(CLSID_Axle);
         hr = axle0->put_Weight(fatigue_truck_weight[0]);
         hr = axle0->put_Spacing(fatigue_truck_axles[0]);
         hr = axles->Add(axle0);

         hr = axle1.CoCreateInstance(CLSID_Axle);
         hr = axle1->put_Weight(fatigue_truck_weight[1]);
         hr = axle1->put_Spacing(fatigue_truck_axles[1]);
         hr = axles->Add(axle1);

         hr = axle2.CoCreateInstance(CLSID_Axle);
         hr = axle2->put_Weight(fatigue_truck_weight[2]);
         hr = axles->Add(axle2);

         hr = vehicles->Add(fatigue_truck);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMLRFDFactory);
   }
   return S_OK;
}

STDMETHODIMP CLBAMFactory::ConfigureDeflectionLiveLoad(ILBAMModel* pModel, LiveLoadModelType llmt,Float64 imTruck,Float64 imLane,SpecUnitType units,IUnitServer* pUnitServer)
{
   CHECK_IN(pModel);
   CHECK_IN(pUnitServer);
   CHRException hr;

   try
   {
      CComPtr<IUnitConvert> convert;
      hr = pUnitServer->get_UnitConvert(&convert);

      CComPtr<ILiveLoadModel> liveloadmodel;
      hr = GetLiveLoadModel(pModel,llmt,&liveloadmodel);

      hr = liveloadmodel->put_Name(CComBSTR("LRFD Optional Vehicular Live Load For Deflection"));
      hr = liveloadmodel->put_DistributionFactorType(dftSingleLane);

      CComPtr<IVehicularLoads> vehicles;
      hr = liveloadmodel->get_VehicularLoads(&vehicles);

      Float64 deflection_lane_load = (units == suUS ? 0.64 : 9.3);
      hr = convert->ConvertToBaseUnits(deflection_lane_load,units==suUS?CComBSTR("kip/ft"):CComBSTR("kN-m"),&deflection_lane_load);

      Float64 deflection_truck_weight[3];
      deflection_truck_weight[0] = (units == suUS ?  8.0 :  35.0);
      deflection_truck_weight[1] = (units == suUS ? 32.0 : 145.0);
      deflection_truck_weight[2] = (units == suUS ? 32.0 : 145.0);
      hr = convert->ConvertToBaseUnits(deflection_truck_weight[0],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&deflection_truck_weight[0]);
      hr = convert->ConvertToBaseUnits(deflection_truck_weight[1],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&deflection_truck_weight[1]);
      hr = convert->ConvertToBaseUnits(deflection_truck_weight[2],units==suUS?CComBSTR("kip"):CComBSTR("kN"),&deflection_truck_weight[2]);

      Float64 deflection_truck_axles[4]; // index 1,2 are the min and max spacing for the variable axle
      deflection_truck_axles[0] = (units == suUS ? 14.0 : 4.3);
      deflection_truck_axles[1] = (units == suUS ? 14.0 : 4.3);
      deflection_truck_axles[2] = (units == suUS ? 30.0 : 9.1);
      hr = convert->ConvertToBaseUnits(deflection_truck_axles[0],units==suUS?CComBSTR("ft"):CComBSTR("m"),&deflection_truck_axles[0]);
      hr = convert->ConvertToBaseUnits(deflection_truck_axles[1],units==suUS?CComBSTR("ft"):CComBSTR("m"),&deflection_truck_axles[1]);
      hr = convert->ConvertToBaseUnits(deflection_truck_axles[2],units==suUS?CComBSTR("ft"):CComBSTR("m"),&deflection_truck_axles[2]);
      hr = convert->ConvertToBaseUnits(deflection_truck_axles[3],units==suUS?CComBSTR("ft"):CComBSTR("m"),&deflection_truck_axles[3]);

      // create variable axle design truck WITHOUT lane vehicular load
      {
         CComPtr<IVehicularLoad> deflection_truck_1; 
         hr = deflection_truck_1.CoCreateInstance(CLSID_VehicularLoad);

         hr = deflection_truck_1->put_Name(CComBSTR("LRFD Deflection Solo Truck"));
         hr = deflection_truck_1->put_Applicability(llaEntireStructure);
         hr = deflection_truck_1->put_Configuration(vlcTruckOnly);
         hr = deflection_truck_1->put_UseNotional(VARIANT_TRUE);
         hr = deflection_truck_1->put_IMLane(imLane);
         hr = deflection_truck_1->put_IMTruck(imTruck);
         hr = deflection_truck_1->put_LaneFactor(1.0);
         hr = deflection_truck_1->put_TruckFactor(1.0);
         hr = deflection_truck_1->put_LaneLoad(0.0);

         CComPtr<IAxles> axles;
         hr = deflection_truck_1->get_Axles(&axles);

         CComPtr<IAxle> axle0, axle1, axle2;
         hr = axle0.CoCreateInstance(CLSID_Axle);
         hr = axle0->put_Weight(deflection_truck_weight[0]);
         hr = axle0->put_Spacing(deflection_truck_axles[0]);
         hr = axles->Add(axle0);

         hr = axle1.CoCreateInstance(CLSID_Axle);
         hr = axle1->put_Weight(deflection_truck_weight[1]);
         hr = axle1->put_Spacing(deflection_truck_axles[1]);
         hr = axles->Add(axle1);

         hr = axle2.CoCreateInstance(CLSID_Axle);
         hr = axle2->put_Weight(deflection_truck_weight[2]);
         hr = axles->Add(axle2);

         hr = deflection_truck_1->put_VariableAxle(1);
         hr = deflection_truck_1->put_VariableMaxSpacing(deflection_truck_axles[2]);

         hr = vehicles->Add(deflection_truck_1);
      }

      // create variable axle design truck using 0.25 of axles plus lane vehicular load
      {
         CComPtr<IVehicularLoad> deflection_truck_2; 
         hr = deflection_truck_2.CoCreateInstance(CLSID_VehicularLoad);

         hr = deflection_truck_2->put_Name(CComBSTR("LRFD Deflection 0.25 Truck plus Lane"));
         hr = deflection_truck_2->put_Applicability(llaEntireStructure);
         hr = deflection_truck_2->put_Configuration(vlcTruckPlusLane);
         hr = deflection_truck_2->put_UseNotional(VARIANT_TRUE);
         hr = deflection_truck_2->put_IMLane(imLane);
         hr = deflection_truck_2->put_IMTruck(imTruck);
         hr = deflection_truck_2->put_LaneFactor(1.0);
         hr = deflection_truck_2->put_TruckFactor(1.0);
         hr = deflection_truck_2->put_LaneLoad(deflection_lane_load);

         CComPtr<IAxles> axles;
         hr = deflection_truck_2->get_Axles(&axles);

         CComPtr<IAxle> axle0, axle1, axle2;
         hr = axle0.CoCreateInstance(CLSID_Axle);
         hr = axle0->put_Weight( 0.25*deflection_truck_weight[0]);
         hr = axle0->put_Spacing(deflection_truck_axles[0]);
         hr = axles->Add(axle0);

         hr = axle1.CoCreateInstance(CLSID_Axle);
         hr = axle1->put_Weight( 0.25*deflection_truck_weight[1]);
         hr = axle1->put_Spacing(deflection_truck_axles[1]);
         hr = axles->Add(axle1);

         hr = axle2.CoCreateInstance(CLSID_Axle);
         hr = axle2->put_Weight( 0.25*deflection_truck_weight[2]);
         hr = axles->Add(axle2);

         hr = deflection_truck_2->put_VariableAxle(1);
         hr = deflection_truck_2->put_VariableMaxSpacing(deflection_truck_axles[2]);

         hr = vehicles->Add(deflection_truck_2);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMLRFDFactory);
   }
   return S_OK;
}

STDMETHODIMP CLBAMFactory::ConfigureLegalLiveLoad(ILBAMModel* pModel, LiveLoadModelType llmt,
                                     Float64 imTruck,
                                     Float64 imLane, 
                                     VARIANT_BOOL includeType33, // 0.75Type3-3 + Lane
                                     VARIANT_BOOL includeDualType33, // 2@0.75Type3-3 + Lane
                                     VARIANT_BOOL removeLaneLoad, // removes lane from Type33 and Dual Type 33 and uses a factor of 1.0
                                     IUnitServer* pUnitServer)
{
   CHECK_IN(pModel);
   CHECK_IN(pUnitServer);

   CHRException hr;

   try
   {
      CComPtr<ILiveLoad> liveload;
      hr = pModel->get_LiveLoad(&liveload);

      CComPtr<IUnitConvert> convert;
      hr = pUnitServer->get_UnitConvert(&convert);

      // set up ll model
      CComPtr<ILiveLoadModel> liveloadmodel;
      switch(llmt)
      {
      case lltNone:
         return E_INVALIDARG;

      case lltDeflection:
         hr = liveload->get_Deflection(&liveloadmodel);
         break;

      case lltDesign:
         hr = liveload->get_Design(&liveloadmodel);
         break;

      case lltPedestrian:
         hr = liveload->get_Pedestrian(&liveloadmodel);
         break;

      case lltFatigue:
         hr = liveload->get_Fatigue(&liveloadmodel);
         break;

      case lltPermit:
         hr = liveload->get_Permit(&liveloadmodel);
         break;

      case lltSpecial:
         hr = liveload->get_Special(&liveloadmodel);
         break;

      case lltLegalRoutineRating:
         hr = liveload->get_LegalRoutineRating(&liveloadmodel);
         break;

      case lltLegalSpecialRating:
         hr = liveload->get_LegalSpecialRating(&liveloadmodel);
         break;

      case lltPermitRoutineRating:
         hr = liveload->get_PermitRoutineRating(&liveloadmodel);
         break;

      case lltPermitSpecialRating:
         hr = liveload->get_PermitSpecialRating(&liveloadmodel);
         break;

      default:
         ATLASSERT(false); // SHOULD NEVER GET HERE
         hr = liveload->get_Design(&liveloadmodel);
         break;
      }

      hr = liveloadmodel->put_Name(CComBSTR("AASHTO Legal Loads"));
      hr = liveloadmodel->put_DistributionFactorType(dftEnvelope);

      CComPtr<IVehicularLoads> vehicles;
      hr = liveloadmodel->get_VehicularLoads(&vehicles);

      // get the loads and axle spacing in base units
      Float64 lane_load = 0.20;
      hr = convert->ConvertToBaseUnits(lane_load,CComBSTR("kip/ft"),&lane_load);

      // create type 3 truck
      Float64 type_3_weight[3];
      hr = convert->ConvertToBaseUnits(16.0,CComBSTR("kip"),&type_3_weight[0]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&type_3_weight[1]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&type_3_weight[2]);

      Float64 type_3_axles[2];
      hr = convert->ConvertToBaseUnits(15.0,CComBSTR("ft"),&type_3_axles[0]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&type_3_axles[1]);

      {
         CComPtr<IVehicularLoad> type_3_truck; 
         hr = type_3_truck.CoCreateInstance(CLSID_VehicularLoad);

         hr = type_3_truck->put_Name(CComBSTR("Type 3"));
         hr = type_3_truck->put_Applicability(llaEntireStructure);
         hr = type_3_truck->put_Configuration(vlcTruckOnly);
         hr = type_3_truck->put_UseNotional(VARIANT_FALSE);
         hr = type_3_truck->put_IMLane(imLane);
         hr = type_3_truck->put_IMTruck(imTruck);
         hr = type_3_truck->put_LaneFactor(1.0);
         hr = type_3_truck->put_TruckFactor(1.0);
         hr = type_3_truck->put_LaneLoad(0.0);

         CComPtr<IAxles> axles;
         hr = type_3_truck->get_Axles(&axles);

         int nAxles = 3;
         for ( int i = 0; i < nAxles; i++ )
         {
            CComPtr<IAxle> axle;
            hr = axle.CoCreateInstance(CLSID_Axle);
            hr = axle->put_Weight(type_3_weight[i]);
            if ( i != nAxles-1 )
               hr = axle->put_Spacing(type_3_axles[i]);
            
            hr = axles->Add(axle);
         }

         hr = vehicles->Add(type_3_truck);
      }


      // create type 3S2 truck
      Float64 type_3S2_weight[5];
      hr = convert->ConvertToBaseUnits(10.0,CComBSTR("kip"),&type_3S2_weight[0]);
      hr = convert->ConvertToBaseUnits(15.5,CComBSTR("kip"),&type_3S2_weight[1]);
      hr = convert->ConvertToBaseUnits(15.5,CComBSTR("kip"),&type_3S2_weight[2]);
      hr = convert->ConvertToBaseUnits(15.5,CComBSTR("kip"),&type_3S2_weight[3]);
      hr = convert->ConvertToBaseUnits(15.5,CComBSTR("kip"),&type_3S2_weight[4]);

      Float64 type_3S2_axles[4];
      hr = convert->ConvertToBaseUnits(11.0,CComBSTR("ft"),&type_3S2_axles[0]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&type_3S2_axles[1]);
      hr = convert->ConvertToBaseUnits(22.0,CComBSTR("ft"),&type_3S2_axles[2]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&type_3S2_axles[3]);

      {
         CComPtr<IVehicularLoad> type_3S2_truck; 
         hr = type_3S2_truck.CoCreateInstance(CLSID_VehicularLoad);

         hr = type_3S2_truck->put_Name(CComBSTR("Type 3S2"));
         hr = type_3S2_truck->put_Applicability(llaEntireStructure);
         hr = type_3S2_truck->put_Configuration(vlcTruckOnly);
         hr = type_3S2_truck->put_UseNotional(VARIANT_FALSE);
         hr = type_3S2_truck->put_IMLane(imLane);
         hr = type_3S2_truck->put_IMTruck(imTruck);
         hr = type_3S2_truck->put_LaneFactor(1.0);
         hr = type_3S2_truck->put_TruckFactor(1.0);
         hr = type_3S2_truck->put_LaneLoad(0.0);

         CComPtr<IAxles> axles;
         hr = type_3S2_truck->get_Axles(&axles);

         int nAxles = 5;
         for ( int i = 0; i < nAxles; i++ )
         {
            CComPtr<IAxle> axle;
            hr = axle.CoCreateInstance(CLSID_Axle);
            hr = axle->put_Weight(type_3S2_weight[i]);
            if ( i != nAxles-1 )
               hr = axle->put_Spacing(type_3S2_axles[i]);
            
            hr = axles->Add(axle);
         }

         hr = vehicles->Add(type_3S2_truck);
      }

      // create type 3-3 truck
      Float64 type_3_3_weight[6];
      hr = convert->ConvertToBaseUnits(12.0,CComBSTR("kip"),&type_3_3_weight[0]);
      hr = convert->ConvertToBaseUnits(12.0,CComBSTR("kip"),&type_3_3_weight[1]);
      hr = convert->ConvertToBaseUnits(12.0,CComBSTR("kip"),&type_3_3_weight[2]);
      hr = convert->ConvertToBaseUnits(16.0,CComBSTR("kip"),&type_3_3_weight[3]);
      hr = convert->ConvertToBaseUnits(14.0,CComBSTR("kip"),&type_3_3_weight[4]);
      hr = convert->ConvertToBaseUnits(14.0,CComBSTR("kip"),&type_3_3_weight[5]);

      Float64 type_3_3_axles[6]; // index 5 is the headway spacing for dual type 3-3
      hr = convert->ConvertToBaseUnits(15.0,CComBSTR("ft"),&type_3_3_axles[0]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&type_3_3_axles[1]);
      hr = convert->ConvertToBaseUnits(15.0,CComBSTR("ft"),&type_3_3_axles[2]);
      hr = convert->ConvertToBaseUnits(16.0,CComBSTR("ft"),&type_3_3_axles[3]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&type_3_3_axles[4]);
      hr = convert->ConvertToBaseUnits(30.0,CComBSTR("ft"),&type_3_3_axles[5]);

      {
         CComPtr<IVehicularLoad> type_3_3_truck; 
         hr = type_3_3_truck.CoCreateInstance(CLSID_VehicularLoad);

         hr = type_3_3_truck->put_Name(CComBSTR("Type 3-3"));
         hr = type_3_3_truck->put_Applicability(llaEntireStructure);
         hr = type_3_3_truck->put_Configuration(vlcTruckOnly);
         hr = type_3_3_truck->put_UseNotional(VARIANT_FALSE);
         hr = type_3_3_truck->put_IMLane(imLane);
         hr = type_3_3_truck->put_IMTruck(imTruck);
         hr = type_3_3_truck->put_LaneFactor(1.0);
         hr = type_3_3_truck->put_TruckFactor(1.0);
         hr = type_3_3_truck->put_LaneLoad(0.0);

         CComPtr<IAxles> axles;
         hr = type_3_3_truck->get_Axles(&axles);

         int nAxles = 6;
         for ( int i = 0; i < nAxles; i++ )
         {
            CComPtr<IAxle> axle;
            hr = axle.CoCreateInstance(CLSID_Axle);
            hr = axle->put_Weight(type_3_3_weight[i]);
            if ( i != nAxles-1 )
               hr = axle->put_Spacing(type_3_3_axles[i]);
            
            hr = axles->Add(axle);
         }

         hr = vehicles->Add(type_3_3_truck);
      }

      if ( includeType33 == VARIANT_TRUE && removeLaneLoad == VARIANT_FALSE )
      {
         // include the 0.75(Type 3-3) + Lane Load
         CComPtr<IVehicularLoad> type_3_3_truck_with_lane; 
         hr = type_3_3_truck_with_lane.CoCreateInstance(CLSID_VehicularLoad);

         hr = type_3_3_truck_with_lane->put_Name(CComBSTR("0.75(Type 3-3) + Lane Load"));
         hr = type_3_3_truck_with_lane->put_Applicability(llaEntireStructure);
         hr = type_3_3_truck_with_lane->put_Configuration(vlcTruckPlusLane);
         hr = type_3_3_truck_with_lane->put_UseNotional(VARIANT_FALSE);
         hr = type_3_3_truck_with_lane->put_IMLane(imLane);
         hr = type_3_3_truck_with_lane->put_IMTruck(imTruck);
         hr = type_3_3_truck_with_lane->put_LaneFactor(1.0);
         hr = type_3_3_truck_with_lane->put_TruckFactor(0.75);
         hr = type_3_3_truck_with_lane->put_LaneLoad(lane_load);

         CComPtr<IAxles> axles;
         hr = type_3_3_truck_with_lane->get_Axles(&axles);

         int nAxles = 6;
         for ( int i = 0; i < nAxles; i++ )
         {
            CComPtr<IAxle> axle;
            hr = axle.CoCreateInstance(CLSID_Axle);
            hr = axle->put_Weight(type_3_3_weight[i]);
            if ( i != nAxles-1 )
               hr = axle->put_Spacing(type_3_3_axles[i]);
            
            hr = axles->Add(axle);
         }

         hr = vehicles->Add(type_3_3_truck_with_lane);
      }

      if ( includeDualType33 == VARIANT_TRUE )
      {
         // include the 2x0.75(Type 3-3) + Lane Load
         CComPtr<IVehicularLoad> dual_type_3_3_truck_with_lane; 
         hr = dual_type_3_3_truck_with_lane.CoCreateInstance(CLSID_VehicularLoad);

         if ( removeLaneLoad == VARIANT_TRUE )
         {
            hr = dual_type_3_3_truck_with_lane->put_Name(CComBSTR("Two Type 3-3 separated by 30ft"));
            hr = dual_type_3_3_truck_with_lane->put_Configuration(vlcTruckOnly);
            hr = dual_type_3_3_truck_with_lane->put_TruckFactor(1.0);
            hr = dual_type_3_3_truck_with_lane->put_LaneLoad(0.0);
         }
         else
         {
            hr = dual_type_3_3_truck_with_lane->put_Name(CComBSTR("0.75(Two Type 3-3 separated by 30ft) + Lane Load"));
            hr = dual_type_3_3_truck_with_lane->put_Configuration(vlcTruckPlusLane);
            hr = dual_type_3_3_truck_with_lane->put_TruckFactor(0.75);
            hr = dual_type_3_3_truck_with_lane->put_LaneLoad(lane_load);
         }

         hr = dual_type_3_3_truck_with_lane->put_Applicability(llaNegMomentAndInteriorPierReaction);
         hr = dual_type_3_3_truck_with_lane->put_UseNotional(VARIANT_FALSE);
         hr = dual_type_3_3_truck_with_lane->put_IMLane(imLane);
         hr = dual_type_3_3_truck_with_lane->put_IMTruck(imTruck);
         hr = dual_type_3_3_truck_with_lane->put_LaneFactor(1.0);

         CComPtr<IAxles> axles;
         hr = dual_type_3_3_truck_with_lane->get_Axles(&axles);

         int nAxles = 6;
         for ( int j = 0; j < 2; j++ )
         {
            for ( int i = 0; i < nAxles; i++ )
            {
               CComPtr<IAxle> axle;
               hr = axle.CoCreateInstance(CLSID_Axle);
               hr = axle->put_Weight(type_3_3_weight[i]);

               if ( j == 0 )
               {
                  hr = axle->put_Spacing(type_3_3_axles[i]);
               }
               else
               {
                  if (i != nAxles-1)
                     hr = axle->put_Spacing(type_3_3_axles[i]);
               }
               
               hr = axles->Add(axle);
            }
         }

         hr = vehicles->Add(dual_type_3_3_truck_with_lane);
      }

   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMLRFDFactory);
   }
   return S_OK;
}


STDMETHODIMP CLBAMFactory::ConfigureNotionalRatingLoad(ILBAMModel* pModel, LiveLoadModelType llmt,
                                     Float64 imTruck,
                                     Float64 imLane, 
                                     IUnitServer* pUnitServer)
{
   CHECK_IN(pModel);
   CHECK_IN(pUnitServer);

   CHRException hr;

   try
   {
      CComPtr<ILiveLoad> liveload;
      hr = pModel->get_LiveLoad(&liveload);

      CComPtr<IUnitConvert> convert;
      hr = pUnitServer->get_UnitConvert(&convert);

      // set up ll model
      CComPtr<ILiveLoadModel> liveloadmodel;
      switch(llmt)
      {
      case lltNone:
         return E_INVALIDARG;

      case lltDeflection:
         hr = liveload->get_Deflection(&liveloadmodel);
         break;

      case lltDesign:
         hr = liveload->get_Design(&liveloadmodel);
         break;

      case lltPedestrian:
         hr = liveload->get_Pedestrian(&liveloadmodel);
         break;

      case lltFatigue:
         hr = liveload->get_Fatigue(&liveloadmodel);
         break;

      case lltPermit:
         hr = liveload->get_Permit(&liveloadmodel);
         break;

      case lltSpecial:
         hr = liveload->get_Special(&liveloadmodel);
         break;

      case lltLegalRoutineRating:
         hr = liveload->get_LegalRoutineRating(&liveloadmodel);
         break;

      case lltLegalSpecialRating:
         hr = liveload->get_LegalSpecialRating(&liveloadmodel);
         break;

      case lltPermitRoutineRating:
         hr = liveload->get_PermitRoutineRating(&liveloadmodel);
         break;

      case lltPermitSpecialRating:
         hr = liveload->get_PermitSpecialRating(&liveloadmodel);
         break;

      default:
         ATLASSERT(false); // SHOULD NEVER GET HERE
         hr = liveload->get_Design(&liveloadmodel);
         break;
      }

      hr = liveloadmodel->put_Name(CComBSTR("Notional Rating Load (NRL)"));
      hr = liveloadmodel->put_DistributionFactorType(dftEnvelope);

      CComPtr<IVehicularLoads> vehicles;
      hr = liveloadmodel->get_VehicularLoads(&vehicles);

      Float64 nrl_truck_weight[8];
      hr = convert->ConvertToBaseUnits( 6.0,CComBSTR("kip"),&nrl_truck_weight[0]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&nrl_truck_weight[1]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&nrl_truck_weight[2]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&nrl_truck_weight[3]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&nrl_truck_weight[4]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&nrl_truck_weight[5]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&nrl_truck_weight[6]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&nrl_truck_weight[7]);

      Float64 nrl_truck_axles[9]; // index 8 = max value for variable axle spacing
      hr = convert->ConvertToBaseUnits( 6.0,CComBSTR("ft"),&nrl_truck_axles[0]); // min variable axle
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&nrl_truck_axles[1]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&nrl_truck_axles[2]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&nrl_truck_axles[3]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&nrl_truck_axles[4]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&nrl_truck_axles[5]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&nrl_truck_axles[6]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&nrl_truck_axles[7]);
      hr = convert->ConvertToBaseUnits(14.0,CComBSTR("ft"),&nrl_truck_axles[8]); // max variable axle

      {
         CComPtr<IVehicularLoad> nrl_truck; 
         hr = nrl_truck.CoCreateInstance(CLSID_VehicularLoad);

         hr = nrl_truck->put_Name(CComBSTR("NRL"));
         hr = nrl_truck->put_Applicability(llaEntireStructure);
         hr = nrl_truck->put_Configuration(vlcTruckOnly);
         hr = nrl_truck->put_UseNotional(VARIANT_TRUE);
         hr = nrl_truck->put_IMLane(imLane);
         hr = nrl_truck->put_IMTruck(imTruck);
         hr = nrl_truck->put_LaneFactor(1.0);
         hr = nrl_truck->put_TruckFactor(1.0);
         hr = nrl_truck->put_LaneLoad(0.0);

         CComPtr<IAxles> axles;
         hr = nrl_truck->get_Axles(&axles);

         int nAxles = 8;
         for ( int i = 0; i < nAxles; i++ )
         {
            CComPtr<IAxle> axle;
            hr = axle.CoCreateInstance(CLSID_Axle);
            hr = axle->put_Weight(nrl_truck_weight[i]);
            if ( i != nAxles-1 )
               hr = axle->put_Spacing(nrl_truck_axles[i]);
            
            hr = axles->Add(axle);
         }

         hr = nrl_truck->put_VariableAxle(0);
         hr = nrl_truck->put_VariableMaxSpacing(nrl_truck_axles[8]);

         hr = vehicles->Add(nrl_truck);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMLRFDFactory);
   }
   return S_OK;
}


STDMETHODIMP CLBAMFactory::ConfigureSpecializedHaulingUnits(ILBAMModel* pModel, LiveLoadModelType llmt,
                                                            Float64 imTruck,
                                                            Float64 imLane, 
                                                            IUnitServer* pUnitServer)
{
   CHECK_IN(pModel);
   CHECK_IN(pUnitServer);

   CHRException hr;

   try
   {
      CComPtr<ILiveLoad> liveload;
      hr = pModel->get_LiveLoad(&liveload);

      CComPtr<IUnitConvert> convert;
      hr = pUnitServer->get_UnitConvert(&convert);

      // set up ll model
      CComPtr<ILiveLoadModel> liveloadmodel;
      switch(llmt)
      {
      case lltNone:
         return E_INVALIDARG;

      case lltDeflection:
         hr = liveload->get_Deflection(&liveloadmodel);
         break;

      case lltDesign:
         hr = liveload->get_Design(&liveloadmodel);
         break;

      case lltPedestrian:
         hr = liveload->get_Pedestrian(&liveloadmodel);
         break;

      case lltFatigue:
         hr = liveload->get_Fatigue(&liveloadmodel);
         break;

      case lltPermit:
         hr = liveload->get_Permit(&liveloadmodel);
         break;

      case lltSpecial:
         hr = liveload->get_Special(&liveloadmodel);
         break;

      case lltLegalRoutineRating:
         hr = liveload->get_LegalRoutineRating(&liveloadmodel);
         break;

      case lltLegalSpecialRating:
         hr = liveload->get_LegalSpecialRating(&liveloadmodel);
         break;

      case lltPermitRoutineRating:
         hr = liveload->get_PermitRoutineRating(&liveloadmodel);
         break;

      case lltPermitSpecialRating:
         hr = liveload->get_PermitSpecialRating(&liveloadmodel);
         break;

      default:
         ATLASSERT(false); // SHOULD NEVER GET HERE
         hr = liveload->get_Design(&liveloadmodel);
         break;
      }

      hr = liveloadmodel->put_Name(CComBSTR("Single-Unit SHVs"));
      hr = liveloadmodel->put_DistributionFactorType(dftEnvelope);

      CComPtr<IVehicularLoads> vehicles;
      hr = liveloadmodel->get_VehicularLoads(&vehicles);

      ///////////////////////////////////////
      // SU4
      ///////////////////////////////////////
      Float64 su4_truck_weight[4];
      hr = convert->ConvertToBaseUnits(12.0,CComBSTR("kip"),&su4_truck_weight[0]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&su4_truck_weight[1]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&su4_truck_weight[2]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&su4_truck_weight[3]);

      Float64 su4_truck_axles[3]; 
      hr = convert->ConvertToBaseUnits(10.0,CComBSTR("ft"),&su4_truck_axles[0]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su4_truck_axles[1]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su4_truck_axles[2]);

      {
         CComPtr<IVehicularLoad> su4_truck; 
         hr = su4_truck.CoCreateInstance(CLSID_VehicularLoad);

         hr = su4_truck->put_Name(CComBSTR("SU4"));
         hr = su4_truck->put_Applicability(llaEntireStructure);
         hr = su4_truck->put_Configuration(vlcTruckOnly);
         hr = su4_truck->put_UseNotional(VARIANT_FALSE);
         hr = su4_truck->put_IMLane(imLane);
         hr = su4_truck->put_IMTruck(imTruck);
         hr = su4_truck->put_LaneFactor(1.0);
         hr = su4_truck->put_TruckFactor(1.0);
         hr = su4_truck->put_LaneLoad(0.0);

         CComPtr<IAxles> axles;
         hr = su4_truck->get_Axles(&axles);

         int nAxles = 4;
         for ( int i = 0; i < nAxles; i++ )
         {
            CComPtr<IAxle> axle;
            hr = axle.CoCreateInstance(CLSID_Axle);
            hr = axle->put_Weight(su4_truck_weight[i]);
            if ( i != nAxles-1 )
               hr = axle->put_Spacing(su4_truck_axles[i]);
            
            hr = axles->Add(axle);
         }

         hr = vehicles->Add(su4_truck);
      }

      ///////////////////////////////////////
      // SU5
      ///////////////////////////////////////
      Float64 su5_truck_weight[5];
      hr = convert->ConvertToBaseUnits(12.0,CComBSTR("kip"),&su5_truck_weight[0]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&su5_truck_weight[1]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&su5_truck_weight[2]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&su5_truck_weight[3]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&su5_truck_weight[4]);

      Float64 su5_truck_axles[4]; 
      hr = convert->ConvertToBaseUnits(10.0,CComBSTR("ft"),&su5_truck_axles[0]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su5_truck_axles[1]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su5_truck_axles[2]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su5_truck_axles[3]);

      {
         CComPtr<IVehicularLoad> su5_truck; 
         hr = su5_truck.CoCreateInstance(CLSID_VehicularLoad);

         hr = su5_truck->put_Name(CComBSTR("SU5"));
         hr = su5_truck->put_Applicability(llaEntireStructure);
         hr = su5_truck->put_Configuration(vlcTruckOnly);
         hr = su5_truck->put_UseNotional(VARIANT_FALSE);
         hr = su5_truck->put_IMLane(imLane);
         hr = su5_truck->put_IMTruck(imTruck);
         hr = su5_truck->put_LaneFactor(1.0);
         hr = su5_truck->put_TruckFactor(1.0);
         hr = su5_truck->put_LaneLoad(0.0);

         CComPtr<IAxles> axles;
         hr = su5_truck->get_Axles(&axles);

         int nAxles = 5;
         for ( int i = 0; i < nAxles; i++ )
         {
            CComPtr<IAxle> axle;
            hr = axle.CoCreateInstance(CLSID_Axle);
            hr = axle->put_Weight(su5_truck_weight[i]);
            if ( i != nAxles-1 )
               hr = axle->put_Spacing(su5_truck_axles[i]);
            
            hr = axles->Add(axle);
         }

         hr = vehicles->Add(su5_truck);
      }

      ///////////////////////////////////////
      // SU6
      ///////////////////////////////////////
      Float64 su6_truck_weight[6];
      hr = convert->ConvertToBaseUnits(11.5,CComBSTR("kip"),&su6_truck_weight[0]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&su6_truck_weight[1]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&su6_truck_weight[2]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&su6_truck_weight[3]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&su6_truck_weight[4]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&su6_truck_weight[5]);

      Float64 su6_truck_axles[5]; 
      hr = convert->ConvertToBaseUnits(10.0,CComBSTR("ft"),&su6_truck_axles[0]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su6_truck_axles[1]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su6_truck_axles[2]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su6_truck_axles[3]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su6_truck_axles[4]);

      {
         CComPtr<IVehicularLoad> su6_truck; 
         hr = su6_truck.CoCreateInstance(CLSID_VehicularLoad);

         hr = su6_truck->put_Name(CComBSTR("SU6"));
         hr = su6_truck->put_Applicability(llaEntireStructure);
         hr = su6_truck->put_Configuration(vlcTruckOnly);
         hr = su6_truck->put_UseNotional(VARIANT_FALSE);
         hr = su6_truck->put_IMLane(imLane);
         hr = su6_truck->put_IMTruck(imTruck);
         hr = su6_truck->put_LaneFactor(1.0);
         hr = su6_truck->put_TruckFactor(1.0);
         hr = su6_truck->put_LaneLoad(0.0);

         CComPtr<IAxles> axles;
         hr = su6_truck->get_Axles(&axles);

         int nAxles = 6;
         for ( int i = 0; i < nAxles; i++ )
         {
            CComPtr<IAxle> axle;
            hr = axle.CoCreateInstance(CLSID_Axle);
            hr = axle->put_Weight(su6_truck_weight[i]);
            if ( i != nAxles-1 )
               hr = axle->put_Spacing(su6_truck_axles[i]);
            
            hr = axles->Add(axle);
         }

         hr = vehicles->Add(su6_truck);
      }

      ///////////////////////////////////////
      // SU7
      ///////////////////////////////////////
      Float64 su7_truck_weight[7];
      hr = convert->ConvertToBaseUnits(11.5,CComBSTR("kip"),&su7_truck_weight[0]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&su7_truck_weight[1]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&su7_truck_weight[2]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&su7_truck_weight[3]);
      hr = convert->ConvertToBaseUnits(17.0,CComBSTR("kip"),&su7_truck_weight[4]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&su7_truck_weight[5]);
      hr = convert->ConvertToBaseUnits( 8.0,CComBSTR("kip"),&su7_truck_weight[6]);

      Float64 su7_truck_axles[6]; 
      hr = convert->ConvertToBaseUnits(10.0,CComBSTR("ft"),&su7_truck_axles[0]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su7_truck_axles[1]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su7_truck_axles[2]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su7_truck_axles[3]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su7_truck_axles[4]);
      hr = convert->ConvertToBaseUnits( 4.0,CComBSTR("ft"),&su7_truck_axles[5]);

      {
         CComPtr<IVehicularLoad> su7_truck; 
         hr = su7_truck.CoCreateInstance(CLSID_VehicularLoad);

         hr = su7_truck->put_Name(CComBSTR("SU7"));
         hr = su7_truck->put_Applicability(llaEntireStructure);
         hr = su7_truck->put_Configuration(vlcTruckOnly);
         hr = su7_truck->put_UseNotional(VARIANT_FALSE);
         hr = su7_truck->put_IMLane(imLane);
         hr = su7_truck->put_IMTruck(imTruck);
         hr = su7_truck->put_LaneFactor(1.0);
         hr = su7_truck->put_TruckFactor(1.0);
         hr = su7_truck->put_LaneLoad(0.0);

         CComPtr<IAxles> axles;
         hr = su7_truck->get_Axles(&axles);

         int nAxles = 7;
         for ( int i = 0; i < nAxles; i++ )
         {
            CComPtr<IAxle> axle;
            hr = axle.CoCreateInstance(CLSID_Axle);
            hr = axle->put_Weight(su7_truck_weight[i]);
            if ( i != nAxles-1 )
               hr = axle->put_Spacing(su7_truck_axles[i]);
            
            hr = axles->Add(axle);
         }

         hr = vehicles->Add(su7_truck);
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMLRFDFactory);
   }
   return S_OK;
}

STDMETHODIMP CLBAMFactory::MapLoadGroupToLoadCase(ILBAMModel* pModel,BSTR lgName,BSTR lgDesc,BSTR lcName)
{
   CHECK_IN(pModel);
   CHECK_IN(lcName);
   CHECK_IN(lgName);

   CHRException hr;

   try
   {
      // create load group
      CComPtr<ILoadGroup> loadGroup;
      hr = loadGroup.CoCreateInstance(CLSID_LoadGroup);
      hr = loadGroup->put_Name(lgName);
      hr = loadGroup->put_Description(lgDesc);

      // put it in the load group collection
      CComPtr<ILoadGroups> loadGroups;
      hr = pModel->get_LoadGroups(&loadGroups);
      hr = loadGroups->Add(loadGroup);

      // get the load case and associated the group
      CComPtr<ILoadCases> loadCases;
      hr = pModel->get_LoadCases(&loadCases);
      CComPtr<ILoadCase> loadCase;
      hr = loadCases->Find(lcName,&loadCase);
      hr = loadCase->AddLoadGroup(lgName);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMFactory);
   }
   return S_OK;
}

STDMETHODIMP CLBAMFactory::CreateSelfWeightDeadLoad(ILBAMModel* pModel,BSTR stage,BSTR lgName,Float64 unitWgt,Float64 E)
{
   CHECK_IN(pModel);
   CHECK_IN(stage);
   CHECK_IN(lgName);

   // NOTE: I'm checking the count of elements in a container before accessing their enumerators.
   //       If the container is empty ATL goes out to lunch when you call enum->Next

   CHRException hr;
   try
   {
      CComPtr<IDistributedLoads> loads;
      hr = pModel->get_DistributedLoads(&loads);

      // Superstructure Member Segments
      CComPtr<ISuperstructureMembers> ssmbrs;
      hr = pModel->get_SuperstructureMembers(&ssmbrs);

      CollectionIndexType count;
      ssmbrs->get_Count(&count);

      if ( 0 < count )
      {
         CComPtr<IEnumSuperstructureMember> enum_ssmbrs;
         hr = ssmbrs->get__EnumElements(&enum_ssmbrs);
      
         int ssmbr_idx = 0;
         CComPtr<ISuperstructureMember> ssmbr;
         while ( enum_ssmbrs->Next(1,&ssmbr,NULL) != S_FALSE)
         {
            CComPtr<IEnumSegmentItem> enum_segments;
            hr = ssmbr->get__EnumElements(&enum_segments);

            CreateSegmentLoad(ssmbr_idx,mtSuperstructureMember,enum_segments,loads,stage,lgName,unitWgt,E);

            ssmbr.Release();

            ssmbr_idx++;
         }
      }

      // Supports
      CComPtr<ISupports> supports;
      hr = pModel->get_Supports(&supports);

      SupportIndexType nSupports;
      supports->get_Count(&nSupports);

      if ( 0 < nSupports )
      {
         CComPtr<IEnumSupport> enum_supports;
         hr = supports->get__EnumElements(&enum_supports);
         SupportIndexType supportIdx = 0;
         CComPtr<ISupport> support;
         while ( enum_supports->Next(1,&support,NULL) != S_FALSE )
         {
            SegmentIndexType seg_count;
            support->get_SegmentCount(stage,&seg_count);

            if ( 0 < seg_count )
            {
               CComPtr<IEnumSegmentItem> enum_segments;
               hr = support->get__EnumElements(&enum_segments);

               CreateSegmentLoad(supportIdx,mtSupport,enum_segments,loads,stage,lgName,unitWgt,E);
            }

            support.Release();

            supportIdx++;
         }
      }

      // Temporary Supports
      CComPtr<ISpans> spans;
      hr = pModel->get_Spans(&spans);
      SpanIndexType nSpans;
      hr = spans->get_Count(&nSpans);
      if ( 0 < nSpans )
      {
         CComPtr<IEnumSpan> enum_spans;
         hr = spans->get__EnumElements(&enum_spans);

         CComPtr<ISpan> span;
         while ( enum_spans->Next(1,&span,NULL) != S_FALSE )
         {
            CComPtr<ITemporarySupports> temp_supports;
            hr = span->get_TemporarySupports(&temp_supports);

            SupportIndexType temp_support_count;
            hr = temp_supports->get_Count(&temp_support_count);

            if ( 0 < temp_support_count )
            {
               CComPtr<IEnumTemporarySupport> enum_temp_supports;
               hr = temp_supports->get__EnumElements(&enum_temp_supports);

               CComPtr<ITemporarySupport> temp_support;
               while ( enum_temp_supports->Next(1,&temp_support,NULL) != S_FALSE )
               {
                  SupportIndexType temp_support_segment_count;
                  hr = temp_support->get_SegmentCount(stage,&temp_support_segment_count);

                  if ( 0 < temp_support_segment_count )
                  {
                     SupportIDType id;
                     hr = temp_support->get_ID(&id);

                     CComPtr<IEnumSegmentItem> enum_segments;
                     hr = temp_support->get__EnumElements(&enum_segments);

                     CreateSegmentLoad(id,mtTemporarySupport,enum_segments,loads,stage,lgName,unitWgt,E);
                  }


                  temp_support.Release();
               }
            }

            span.Release();
         }
      }

   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMFactory);
   }

   return S_OK;
}

//////////////////////////////
// Private helper functions
void CLBAMFactory::AddLoadCase(ILoadCases* loadCases, BSTR name, BSTR description)
{
   CHRException hr;
   CComPtr<ILoadCase> load_case;
   hr = load_case.CoCreateInstance(CLSID_LoadCase) ;
   hr = load_case->put_Name(name) ;
   hr = load_case->put_Description(name) ;
   hr = loadCases->Add(load_case) ;
}

void CLBAMFactory::ApplyTypicalLoadFactors(ILoadCombination* loadCombo, bool Strength4)
{
   CHRException hr;
   // apply the most common load factors
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("DC"), 0.90, 1.25);
   if (!Strength4)
   {
      hr = loadCombo->AddLoadCaseFactor(CComBSTR("DD"), 0.45, 1.80);
   }
   else
   {
      hr = loadCombo->AddLoadCaseFactor(CComBSTR("DD"), 1.50, 1.50);
   }

   hr = loadCombo->AddLoadCaseFactor(CComBSTR("DW"), 0.65, 1.50) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EH"), 0.90, 1.35) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EV"), 0.90, 1.35) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("ES"), 0.75, 1.50) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EL"), 1.00, 1.00) ;

   hr = loadCombo->AddLoadCaseFactor(CComBSTR("WA"), 1.00, 1.00) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("FR"), 1.00, 1.00) ;
}

void CLBAMFactory::ApplyTypicalServiceLoadFactors(ILoadCombination* loadCombo)
{
   CHRException hr;
   // apply the most common load factors
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("DC"), 1.0, 1.0) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("DD"), 1.0, 1.0) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("DW"), 1.0, 1.0) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EH"), 1.0, 1.0) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EV"), 1.0, 1.0) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("ES"), 1.0, 1.0) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EL"), 1.0, 1.00) ;

   hr = loadCombo->AddLoadCaseFactor(CComBSTR("WA"), 1.00, 1.00) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("FR"), 1.00, 1.00) ;

   hr = loadCombo->AddLoadCaseFactor(CComBSTR("TU"), 1.0, 1.2) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("CR"), 1.0, 1.2) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("SH"), 1.0, 1.2) ;
}


void CLBAMFactory::ApplyTypicalLiveLoadFactors(ILoadCombination* loadCombo, Float64 factor)
{
   CHRException hr;
   // apply the most common load factors
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("CE"), factor, factor) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("BR"), factor, factor) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("PL"), factor, factor) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("LS"), factor, factor) ;
}

void CLBAMFactory::ApplyTUCRSHLoadFactors(ILoadCombination* loadCombo, Float64 gradientFactor)
{
   CHRException hr;
   // apply the most common load factors
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("TU"), 0.5, 1.2) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("CR"), 0.5, 1.2) ;
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("SH"), 0.5, 1.2) ;

   if (gradientFactor!=0.0)
   {
      hr = loadCombo->AddLoadCaseFactor(CComBSTR("TG"), gradientFactor, gradientFactor);
      hr = loadCombo->AddLoadCaseFactor(CComBSTR("SE"), gradientFactor, gradientFactor);
   }
}

void CLBAMFactory::CreateSegmentLoad(MemberIDType mbrID,MemberType mbrType,IEnumSegmentItem* enum_segments,IDistributedLoads* loads,BSTR stage,BSTR lgName,Float64 unitWgt,Float64 E)
{
   CHRException hr;

   Float64 start_location = 0.0;

   CComPtr<ISegmentItem> segment_item;
   while ( enum_segments->Next(1,&segment_item,NULL) != S_FALSE )
   {
      CComPtr<ISegment> segment;
      hr = segment_item->get_Segment(&segment);

      Float64 segment_length;
      hr = segment->get_Length(&segment_length);

      Float64 end_location = start_location + segment_length;

      CComPtr<ISegmentCrossSection> section;
      hr = segment->get_SegmentCrossSection(&section);

      Float64 ea;
      hr = section->get_EAForce(&ea);

      CComPtr<IDistributedLoad> load;
      hr = load.CoCreateInstance(CLSID_DistributedLoad);

      Float64 w = -unitWgt*ea/E;
      hr = load->put_Direction(ldFy);
      hr = load->put_Orientation(loGlobal);
      hr = load->put_StartLocation(start_location);
      hr = load->put_EndLocation(end_location);
      hr = load->put_WStart(w);
      hr = load->put_WEnd(w);
      hr = load->put_MemberID(mbrID);
      hr = load->put_MemberType(mbrType);

      hr = loads->Add(stage,lgName,load,NULL);

      start_location = end_location;
      segment_item.Release();
   }
}


STDMETHODIMP CLBAMFactory::GeneratePOIsOnSuperstructure(ILBAMModel *Model, PoiIDType startID, PoiIDType Increment, PoiIDType* lastVal)
{
	CHECK_IN(Model);
   CHECK_RETVAL(lastVal);

   CHRException hr;

   try
   {
      if (Increment<1)
         THROW_LBAMU(POI_INCREMENT_MUST_BE_GT_ZERO);

      // see if we have any spans
      CComPtr<ISpans> pspans;
      hr = Model->get_Spans(&pspans);

      SpanIndexType num_spans;
      hr = pspans->get_Count(&num_spans);

      if (num_spans==0)
         THROW_LBAMU(MUST_HAVE_ONE_SPAN);

      // see if we have any SuperstructureMembers
      CComPtr<ISuperstructureMembers> pssms;
      hr = Model->get_SuperstructureMembers(&pssms);

      CollectionIndexType num_ssms;
      hr = pssms->get_Count(&num_ssms);

      if (num_ssms==0)
         THROW_LBAMU(MUST_HAVE_ONE_SSM);

      // get poi collection
      CComPtr<IPOIs> ppois;
      hr = Model->get_POIs(&ppois);

      // see if we have an overhang
      Float64 left_oh;
      hr = pssms->get_Offset(&left_oh);

      PoiIDType curr_id = startID-1;

      if (left_oh>0.0)
      {
         curr_id++;
         // we have an overhang - put a poi at the ends of the first ssm
         CComPtr<IPOI> pohpoi;
         hr = CreatePOI(curr_id, mtSuperstructureMember, 0, 0.0, &pohpoi);
         hr = AddPOI(ppois,pohpoi);

         curr_id++;
         CComPtr<IPOI> pohpoi2;
         CreatePoiAlongSuperstructure(0.0, curr_id, pssms, &pohpoi2);

         hr = AddPOI(ppois,pohpoi2);
      }

      Float64 incval = 1.0/Increment;

      // put pois on spans at given increment
      for (SpanIndexType ispan=0; ispan<num_spans; ispan++)
      {

         Float64 curinc = 0.0;

         for (PoiIDType iinc=0; iinc<Increment+1; iinc++)
         {
            curr_id++;

            // make sure location does not exceed -1.0 due to floating errors
            if (iinc == Increment)
            {
               if (curinc<-1.0)
                  curinc = -1.0;
            }

            CComPtr<IPOI> ppoi;
            hr = CreatePOI(curr_id, mtSpan, ispan, curinc, &ppoi);
            hr = AddPOI(ppois,ppoi);

            curinc -= incval;
         }
      }

      // check if an overhang exists on right end
      Float64 spans_length;
      hr = pspans->get_Length(&spans_length);

      Float64 ssms_length;
      hr = pssms->get_Length(&ssms_length);

      Float64 right_oh = ssms_length - left_oh - spans_length;

      if (right_oh>0.0)
      {
         // we have an overhang - put a poi at the ends of the overhang
         Float64 poi_loc = ssms_length - left_oh - right_oh;
         if (poi_loc>0.0)
         {
            // poi at start of overhang
            curr_id++;
            CComPtr<IPOI> pohpoi;
            CreatePoiAlongSuperstructure(poi_loc, curr_id, pssms, &pohpoi);

            hr = AddPOI(ppois,pohpoi);

            // poi at end of overhang
            poi_loc = ssms_length - left_oh;
            curr_id++;
            CComPtr<IPOI> pohpoi2;
            CreatePoiAlongSuperstructure(poi_loc, curr_id, pssms, &pohpoi2);

            hr = AddPOI(ppois,pohpoi2);
         }
         else
         {
            ATLASSERT(false); // length of overhangs exceeds length of ss?
         }
      }

      *lastVal = curr_id;

   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMLRFDFactory);
   }

	return S_OK;
}

HRESULT AddPOI(IPOIs* pPOIs, IPOI* pPOI)
{
   HRESULT hr;
   // try to add poi
   hr = pPOIs->Add(pPOI);
   if (hr==WCC_E_NAME_ALREADY_EXISTS)
   {
      PoiIDType id;
      hr = pPOI->get_ID(&id);

      // poi already exists - remove it and add ours
      hr = pPOIs->RemoveByID(id);
      hr = pPOIs->Add(pPOI);
   }

   return hr;
}

STDMETHODIMP CLBAMFactory::GetSuperstructurePOIs(ILBAMModel* pModel, IIDArray* *pPoiIDs, IDblArray* *pPoiLocations)
{
	CHECK_IN(pModel);
   CHECK_RETOBJ(pPoiIDs);
   CHECK_RETOBJ(pPoiLocations);

   try
   {
      // Plan is walk through all pois and insert pois in superstructure into a vector
      // Then sort the vector.
      typedef std::vector<PoiLoc> PoiList;
      typedef PoiList::iterator   PoiListIterator;
      PoiList poi_list;

      CHRException hr;
      CComPtr<IPOIs> lbam_pois;

      hr = pModel->get_POIs(&lbam_pois);

      CollectionIndexType num_pois;
      hr = lbam_pois->get_Count(&num_pois);

      // reserve the list size to save allocations
      poi_list.reserve(num_pois);

      for (CollectionIndexType ipoi=0; ipoi<num_pois; ipoi++)
      {
         CComPtr<IPOI> lbam_poi;
         hr = lbam_pois->get_Item(ipoi, &lbam_poi);

         MemberType mbr_type;
         hr = lbam_poi->get_MemberType(&mbr_type);

         if (mbr_type==mtSpan || mbr_type==mtSuperstructureMember)
         {
            // Poi is on superstructure. Get its id and location
            PoiIDType poi_id;
            hr = lbam_poi->get_ID(&poi_id);

            MemberIDType mbr_id;
            hr = lbam_poi->get_MemberID(&mbr_id);

            Float64 poi_loc;
            hr = lbam_poi->get_Location(&poi_loc);

            Float64 xloc, yloc;
            hr = pModel->ComputeLocation(mbr_id, mbr_type, poi_loc, &xloc, &yloc);

            poi_list.push_back( PoiLoc(poi_id, mbr_type, mbr_id, poi_loc, xloc) );
         }
      }

      // have list, now sort it by location
      std::sort(poi_list.begin(), poi_list.end());

      #if defined(_DEBUG_LOGGING)
         ATLTRACE(_T("Sorted POIs - %d of them\n"), poi_list.size());
         for (PoiListIterator pit=poi_list.begin(); pit!=poi_list.end(); pit++)
         {
            PoiLoc& poi_loc = *pit;
            if (poi_loc.m_MbrType==mtSpan)
               ATLTRACE(_T("%d, Span %d, mbrLoc %f at %f\n"), poi_loc.m_ID, poi_loc.m_MbrID , poi_loc.m_MbrLoc, poi_loc.m_Location );
            else
               ATLTRACE(_T("%d, SSM  %d, mbrLoc %f at %f\n"), poi_loc.m_ID, poi_loc.m_MbrID , poi_loc.m_MbrLoc, poi_loc.m_Location );
         }
      #endif

      CollectionIndexType array_size = poi_list.size();

      // Create safe arrays that are to be returned.
      CComPtr<IIDArray> poi_ids;
      hr = poi_ids.CoCreateInstance(CLSID_IDArray);
      hr = poi_ids->Reserve(array_size);

      CComPtr<IDblArray> poi_locs;
      hr = poi_locs.CoCreateInstance(CLSID_DblArray);
      hr = poi_locs->Reserve(array_size);

      // copy ids and locations into safearrays
      CollectionIndexType i=0;
      for (PoiListIterator it= poi_list.begin(); it!=poi_list.end(); it++)
      {
         PoiLoc& rpl = *it;
         poi_ids->Add( rpl.m_ID);
         poi_locs->Add(rpl.m_Location);
         i++;
      }

      // assign our arrays to outbound variables
      *pPoiIDs = poi_ids.Detach();
      *pPoiLocations = poi_locs.Detach();

   }
   catch(...)
   {
      return DealWithExceptions(this,IID_ILBAMFactory);
   }

	return S_OK;
}

void CLBAMFactory::CreatePoiAlongSuperstructure(Float64 xloc, PoiIDType id, ISuperstructureMembers* pSsms, IPOI** pPoi)
{
   CHRException hr;

   *pPoi = NULL;

   CollectionIndexType ssm_cnt;
   hr = pSsms->get_Count(&ssm_cnt);

   // we need to deal with the case where the poi location is at the junction of two ssm's
   // set up a tolerance to determine if this is true.
   Float64 ssms_length;
   hr = pSsms->get_Length(&ssms_length);

   Float64 LOC_TOL = ssms_length*1.0e-05;

   // left overhang
   Float64 left_oh;
   hr = pSsms->get_Offset(&left_oh);

   // loop over ssms until we find the one with our location in it
   Float64 start_loc = -left_oh;

   if (xloc<start_loc)
   {
      ATLASSERT(false); // location off of left end
      return;
   }

   for (CollectionIndexType i_ssm=0; i_ssm<ssm_cnt; i_ssm++)
   {
      CComPtr<ISuperstructureMember> ssm;
      hr = pSsms->get_Item(i_ssm, &ssm);

      Float64 ssm_length;
      hr = ssm->get_Length(&ssm_length);

      Float64 end_loc = start_loc + ssm_length;

      if (xloc <= end_loc)
      {
         Float64 ssm_loc = xloc - start_loc;
         // found our ssm
         hr = CreatePOI(id, mtSuperstructureMember, i_ssm, ssm_loc, pPoi);
         return;
      }

      if (i_ssm=ssm_cnt-1)
      {
         // we hit the end and did not find our location - let's see if we're within tolerance
         if (xloc-end_loc<LOC_TOL)
         {
            hr = CreatePOI(id, mtSuperstructureMember, i_ssm, ssm_length, pPoi);
         }
         else
            ATLASSERT(false); // off of right end
      }

      start_loc = end_loc;
   }
}

STDMETHODIMP CLBAMFactory::CreatePOI(PoiIDType ID, MemberType Type, MemberIDType memberID, Float64 Location, IPOI** newPOI)
{
   CHECK_RETOBJ(newPOI);

   CHRException hr;

	CComPtr<IPOI> ppoi;
   hr = ppoi.CoCreateInstance(CLSID_POI);
   hr = ppoi->put_ID(ID);
   hr = ppoi->put_MemberType(Type);
   hr = ppoi->put_MemberID(memberID);
   hr = ppoi->put_Location(Location);

   return ppoi.CopyTo(newPOI);
}


STDMETHODIMP CLBAMFactory::GetLiveLoadModel(ILBAMModel* pModel,LiveLoadModelType llmt,ILiveLoadModel** ppLiveLoadModel)
{
   CComPtr<ILiveLoad> liveload;
   HRESULT hr = pModel->get_LiveLoad(&liveload);
   if ( FAILED(hr) )
      return hr;

   switch(llmt)
   {
   case lltNone:
      return E_INVALIDARG;

   case lltDeflection:
      hr = liveload->get_Deflection(ppLiveLoadModel);
      break;

   case lltDesign:
      hr = liveload->get_Design(ppLiveLoadModel);
      break;

   case lltPedestrian:
      hr = liveload->get_Pedestrian(ppLiveLoadModel);
      break;

   case lltFatigue:
      hr = liveload->get_Fatigue(ppLiveLoadModel);
      break;

   case lltPermit:
      hr = liveload->get_Permit(ppLiveLoadModel);
      break;

   case lltSpecial:
      hr = liveload->get_Special(ppLiveLoadModel);
      break;

   case lltLegalRoutineRating:
      hr = liveload->get_LegalRoutineRating(ppLiveLoadModel);
      break;

   case lltLegalSpecialRating:
      hr = liveload->get_LegalSpecialRating(ppLiveLoadModel);
      break;
   
   case lltPermitRoutineRating:
      hr = liveload->get_PermitRoutineRating(ppLiveLoadModel);
      break;
   
   case lltPermitSpecialRating:
      hr = liveload->get_PermitSpecialRating(ppLiveLoadModel);
      break;

   default:
      ATLASSERT(false); // is there a new live load type???
      hr = liveload->get_Design(ppLiveLoadModel);
      break;
   }

   return hr;
}