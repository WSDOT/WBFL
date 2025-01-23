///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
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

// LBAMCollection.h : 

#ifndef __LBAMTestUtils_H_
#define __LBAMTestUtils_H_

#include <WBFLLBAM.h>
inline void ConfigureLrfdLiveLoadModelInKipFeet(ILBAMModel* model)
{
   CHRException hr;
   CComPtr<ILiveLoad> liveload;
   hr = model->get_LiveLoad(&liveload);

   // set up design ll model
   CComPtr<ILiveLoadModel> design;
   hr = liveload->get_Design(&design);
   hr = design->put_Name(CComBSTR("LRFD Design Vehicular Live Load"));
   hr = design->put_DistributionFactorType(dftMultipleLane);

   CComPtr<IVehicularLoads> des_vehls;
   hr = design->get_VehicularLoads(&des_vehls);

   // create variable axle design truck with lane vehicular load
   {
      CComPtr<IVehicularLoad> des_vhl; 
      hr = des_vhl.CoCreateInstance(CLSID_VehicularLoad);

      hr = des_vhl->put_Name(CComBSTR("LRFD Design Truck"));
      hr = des_vhl->put_Applicability(llaEntireStructure);
      hr = des_vhl->put_Configuration(vlcTruckPlusLane);
      hr = des_vhl->put_UseNotional(VARIANT_TRUE);
      hr = des_vhl->put_IMLane(1.0);
      hr = des_vhl->put_IMTruck(1.33);
      hr = des_vhl->put_LaneFactor(1.0);
      hr = des_vhl->put_TruckFactor(1.0);
      hr = des_vhl->put_LaneLoad(0.64);

      CComPtr<IAxles> axles;
      hr = des_vhl->get_Axles(&axles);

      CComPtr<IAxle> axle0, axle1, axle2;
      hr = axle0.CoCreateInstance(CLSID_Axle);
      axle0->put_Weight(8.0);
      axle0->put_Spacing(14.0);
      axles->Add(axle0);

      hr = axle1.CoCreateInstance(CLSID_Axle);
      axle1->put_Weight(32.0);
      axle1->put_Spacing(14.0);
      axles->Add(axle1);

      hr = axle2.CoCreateInstance(CLSID_Axle);
      axle2->put_Weight(32.0);
      axles->Add(axle2);

      hr = des_vhl->put_VariableAxle(1);
      hr = des_vhl->put_VariableMaxSpacing(30);

      hr = des_vehls->Add(des_vhl);
   }

   // create tandem with lane vehicular load
   {
      CComPtr<IVehicularLoad> tdm_vhl;
      hr = tdm_vhl.CoCreateInstance(CLSID_VehicularLoad);

      hr = tdm_vhl->put_Name(CComBSTR("LRFD Design Tandem"));
      hr = tdm_vhl->put_Applicability(llaEntireStructure);
      hr = tdm_vhl->put_Configuration(vlcTruckPlusLane);
      hr = tdm_vhl->put_UseNotional(VARIANT_TRUE);
      hr = tdm_vhl->put_IMLane(1.0);
      hr = tdm_vhl->put_IMTruck(1.33);
      hr = tdm_vhl->put_LaneFactor(1.0);
      hr = tdm_vhl->put_TruckFactor(1.0);
      hr = tdm_vhl->put_LaneLoad(0.64);
      hr = tdm_vhl->put_SidewalkLoad(0.32);

      CComPtr<IAxles> tdm_axles;
      hr = tdm_vhl->get_Axles(&tdm_axles);

      CComPtr<IAxle> tdm_axle0, tdm_axle1;
      hr = tdm_axle0.CoCreateInstance(CLSID_Axle);
      tdm_axle0->put_Weight(25.0);
      tdm_axle0->put_Spacing(4.0);
      tdm_axles->Add(tdm_axle0);

      hr = tdm_axle1.CoCreateInstance(CLSID_Axle);
      tdm_axle1->put_Weight(25.0);
      tdm_axles->Add(tdm_axle1);

      hr = des_vehls->Add(tdm_vhl);
   }      

   // create dual truck train
   {
      CComPtr<IVehicularLoad> trk_trn;
      hr = trk_trn.CoCreateInstance(CLSID_VehicularLoad);

      hr = trk_trn->put_Name(CComBSTR("LRFD Truck Train"));
      hr = trk_trn->put_Applicability(llaContraflexure);
      hr = trk_trn->put_Configuration(vlcTruckPlusLane);
      hr = trk_trn->put_UseNotional(VARIANT_TRUE);  // this truck must be notional
      hr = trk_trn->put_IMLane(1.0);
      hr = trk_trn->put_IMTruck(1.33);
      hr = trk_trn->put_LaneFactor(0.9);
      hr = trk_trn->put_TruckFactor(0.9);
      hr = trk_trn->put_LaneLoad(0.64);

      CComPtr<IAxles> axles;
      hr = trk_trn->get_Axles(&axles);

      CComPtr<IAxle> axle0, axle1, axle2, axle3, axle4, axle5;
      hr = axle0.CoCreateInstance(CLSID_Axle);
      hr = axle0->put_Weight(8.0);
      hr = axle0->put_Spacing(14.0);
      hr = axles->Add(axle0);

      hr = axle1.CoCreateInstance(CLSID_Axle);
      hr = axle1->put_Weight(32.0);
      hr = axle1->put_Spacing(14.0);
      hr = axles->Add(axle1);

      hr = axle2.CoCreateInstance(CLSID_Axle);
      hr = axle2->put_Weight(32.0);
      hr = axle2->put_Spacing(50.0);
      hr = axles->Add(axle2);

      hr = axle3.CoCreateInstance(CLSID_Axle);
      hr = axle3->put_Weight(8.0);
      hr = axle3->put_Spacing(14.0);
      hr = axles->Add(axle3);

      hr = axle4.CoCreateInstance(CLSID_Axle);
      hr = axle4->put_Weight(32.0);
      hr = axle4->put_Spacing(14.0);
      hr = axles->Add(axle4);

      hr = axle5.CoCreateInstance(CLSID_Axle);
      hr = axle5->put_Weight(32.0);
      hr = axles->Add(axle5);

      hr = trk_trn->put_VariableAxle(2);
      hr = trk_trn->put_VariableMaxSpacing(10000);

      hr = des_vehls->Add(trk_trn);
   }
}

inline void AddLoadCase(ILoadCases* loadCases, BSTR name, BSTR description)
{
   CHRException hr;

   CComPtr<ILoadCase> load_case;
   hr = load_case.CoCreateInstance(CLSID_LoadCase);
   hr = load_case->put_Name(name);
   hr = load_case->put_Description(name);
   hr = loadCases->Add(load_case);
}

inline void ApplyTypicalLoadFactors(ILoadCombination* loadCombo, bool Strength4)
{
   CHRException hr;

   // apply the most common load factors
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("DC"), 0.90, 1.25);
   if (!Strength4)
      hr = loadCombo->AddLoadCaseFactor(CComBSTR("DD"), 0.45, 1.80);
   else
      hr = loadCombo->AddLoadCaseFactor(CComBSTR("DD"), 1.50, 1.50);

   hr = loadCombo->AddLoadCaseFactor(CComBSTR("DW"), 0.65, 1.50);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EH"), 0.90, 1.35);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EV"), 0.90, 1.35);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("ES"), 0.75, 1.50);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EL"), 1.00, 1.00);

   hr = loadCombo->AddLoadCaseFactor(CComBSTR("WA"), 1.00, 1.00);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("FR"), 1.00, 1.00);
}

inline void ApplyTypicalServiceLoadFactors(ILoadCombination* loadCombo)
{
   CHRException hr;

   // apply the most common load factors
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("DC"), 1.0, 1.0);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("DD"), 1.0, 1.0);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("DW"), 1.0, 1.0);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EH"), 1.0, 1.0);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EV"), 1.0, 1.0);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("ES"), 1.0, 1.0);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("EL"), 1.0, 1.00);

   hr = loadCombo->AddLoadCaseFactor(CComBSTR("WA"), 1.00, 1.00);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("FR"), 1.00, 1.00);

   hr = loadCombo->AddLoadCaseFactor(CComBSTR("TU"), 1.0, 1.2);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("CR"), 1.0, 1.2);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("SH"), 1.0, 1.2);
}


inline void ApplyTypicalLiveLoadFactors(ILoadCombination* loadCombo, Float64 factor)
{
   CHRException hr;
   // apply the most common load factors
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("CE"), factor, factor);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("BR"), factor, factor);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("PL"), factor, factor);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("LS"), factor, factor);
}

inline void ApplyTUCRSHLoadFactors(ILoadCombination* loadCombo, Float64 gradientFactor)
{
   CHRException hr;
   // apply the most common load factors
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("TU"), 0.5, 1.2);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("CR"), 0.5, 1.2);
   hr = loadCombo->AddLoadCaseFactor(CComBSTR("SH"), 0.5, 1.2);

   if (gradientFactor!=0.0)
   {
      hr = loadCombo->AddLoadCaseFactor(CComBSTR("TG"), gradientFactor, gradientFactor);
      hr = loadCombo->AddLoadCaseFactor(CComBSTR("SE"), gradientFactor, gradientFactor);
   }
}

inline void ConfigureLrfdLoadCombinations(ILBAMModel* model)
{
   // This function adds load cases and combinations as per LRFD 3.4.1
   CHRException hr;
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
   hr = model->get_LoadCombinations(&loadcombos);

   // add load combinations
   // STRENGTH-I
   CComPtr<ILoadCombination> strength1;
   hr = strength1.CoCreateInstance(CLSID_LoadCombination);
   hr = strength1->put_Name(CComBSTR("STRENGTH-I"));
   hr = strength1->put_LoadCombinationType(lctStrength);
   hr = strength1->put_LiveLoadFactor(1.75);
   hr = strength1->AddLiveLoadModel(lltDesign);

   ApplyTypicalLoadFactors(strength1, false);
   ApplyTypicalLiveLoadFactors(strength1, 1.75);
   ApplyTUCRSHLoadFactors(strength1, 0.50);

   hr = loadcombos->Add(strength1);

   // STRENGTH-II
   CComPtr<ILoadCombination> strength2;
   hr = strength2.CoCreateInstance(CLSID_LoadCombination);
   hr = strength2->put_Name(CComBSTR("STRENGTH-II"));
   hr = strength2->put_LoadCombinationType(lctStrength);
   hr = strength2->put_LiveLoadFactor(1.35);
   hr = strength2->AddLiveLoadModel(lltPermit);

   ApplyTypicalLoadFactors(strength2, false);
   ApplyTypicalLiveLoadFactors(strength2, 1.35);
   ApplyTUCRSHLoadFactors(strength2, 0.0);

   hr = loadcombos->Add(strength2);

   // STRENGTH-III
   CComPtr<ILoadCombination> strength3;
   hr = strength3.CoCreateInstance(CLSID_LoadCombination);
   hr = strength3->put_Name(CComBSTR("STRENGTH-III"));
   hr = strength3->put_LoadCombinationType(lctStrength);
   hr = strength3->AddLiveLoadModel(lltNone);

   ApplyTypicalLoadFactors(strength3, false);
   ApplyTUCRSHLoadFactors(strength3, 0.0);

   hr = strength3->AddLoadCaseFactor(CComBSTR("WS"), 1.40, 1.40);

   hr = loadcombos->Add(strength3);

   // STRENGTH-IV
   CComPtr<ILoadCombination> strength4;
   hr = strength4.CoCreateInstance(CLSID_LoadCombination);
   hr = strength4->put_Name(CComBSTR("STRENGTH-IV"));
   hr = strength4->put_LoadCombinationType(lctStrength);
   hr = strength4->AddLiveLoadModel(lltNone);

   ApplyTypicalLoadFactors(strength4, true);
   ApplyTUCRSHLoadFactors(strength4, 0.0);

   hr = loadcombos->Add(strength4);

   // STRENGTH-V
   CComPtr<ILoadCombination> strength5;
   hr = strength5.CoCreateInstance(CLSID_LoadCombination);
   hr = strength5->put_Name(CComBSTR("STRENGTH-V"));
   hr = strength5->put_LoadCombinationType(lctStrength);
   hr = strength5->put_LiveLoadFactor(1.35);
   hr = strength5->AddLiveLoadModel(lltDesign);

   ApplyTypicalLoadFactors(strength5, false);
   ApplyTypicalLiveLoadFactors(strength5, 1.35);
   ApplyTUCRSHLoadFactors(strength5, 0.0);

   hr = strength5->AddLoadCaseFactor(CComBSTR("WS"), 0.40, 0.40);
   hr = strength5->AddLoadCaseFactor(CComBSTR("WL"), 1.00, 1.00);

   hr = loadcombos->Add(strength5);

   // EXTREME EVENT-I
   CComPtr<ILoadCombination> extevent1;
   hr = extevent1.CoCreateInstance(CLSID_LoadCombination);
   hr = extevent1->put_Name(CComBSTR("EXTREME EVENT-I"));
   hr = extevent1->put_LoadCombinationType(lctExtremeEvent);
   hr = extevent1->put_LiveLoadFactor(1.00); // should be on a project basis
   hr = extevent1->AddLiveLoadModel(lltDesign);

   ApplyTypicalLoadFactors(extevent1, false);
   ApplyTypicalLiveLoadFactors(extevent1, 1.75);

   hr = extevent1->AddLoadCaseFactor(CComBSTR("EQ"), 1.00, 1.00);

   hr = loadcombos->Add(extevent1);

   // EXTREME EVENT-II
   CComPtr<ILoadCombination> extevent2;
   hr = extevent2.CoCreateInstance(CLSID_LoadCombination);
   hr = extevent2->put_Name(CComBSTR("EXTREME EVENT-II"));
   hr = extevent2->put_LoadCombinationType(lctExtremeEvent);
   hr = extevent2->put_LiveLoadFactor(0.50); 
   hr = extevent2->AddLiveLoadModel(lltDesign);

   ApplyTypicalLoadFactors(extevent2, false);
   ApplyTypicalLiveLoadFactors(extevent2, 0.50);

   hr = extevent2->AddLoadCaseFactor(CComBSTR("IC"), 1.00, 1.00);
   hr = extevent2->AddLoadCaseFactor(CComBSTR("CT"), 1.00, 1.00);
   hr = extevent2->AddLoadCaseFactor(CComBSTR("CV"), 1.00, 1.00);

   hr = loadcombos->Add(extevent2);

   // SERVICE-I
   CComPtr<ILoadCombination> service1;
   hr = service1.CoCreateInstance(CLSID_LoadCombination);
   hr = service1->put_Name(CComBSTR("SERVICE-I"));
   hr = service1->put_LoadCombinationType(lctService);
   hr = service1->put_LiveLoadFactor(1.00);
   hr = service1->AddLiveLoadModel(lltDesign);

   ApplyTypicalServiceLoadFactors(service1);
   ApplyTypicalLiveLoadFactors(service1, 1.0);

   hr = service1->AddLoadCaseFactor(CComBSTR("WS"), 0.30, 0.30);
   hr = service1->AddLoadCaseFactor(CComBSTR("WL"), 1.00, 1.00);

   hr = loadcombos->Add(service1);

   // SERVICE-II
   CComPtr<ILoadCombination> service2;
   hr = service2.CoCreateInstance(CLSID_LoadCombination);
   hr = service2->put_Name(CComBSTR("SERVICE-II"));
   hr = service2->put_LoadCombinationType(lctService);
   hr = service2->put_LiveLoadFactor(1.30);
   hr = service2->AddLiveLoadModel(lltDesign);

   ApplyTypicalServiceLoadFactors(service2);
   ApplyTypicalLiveLoadFactors(service2, 1.3);

   hr = loadcombos->Add(service2);

   // SERVICE-III
   CComPtr<ILoadCombination> service3;
   hr = service3.CoCreateInstance(CLSID_LoadCombination);
   hr = service3->put_Name(CComBSTR("SERVICE-III"));
   hr = service3->put_LoadCombinationType(lctService);
   hr = service3->put_LiveLoadFactor(0.80);
   hr = service3->AddLiveLoadModel(lltDesign);

   ApplyTypicalServiceLoadFactors(service3);
   ApplyTypicalLiveLoadFactors(service3, 0.8);

   hr = loadcombos->Add(service3);

   // FATIGUE
   CComPtr<ILoadCombination> fatigue;
   hr = fatigue.CoCreateInstance(CLSID_LoadCombination);
   hr = fatigue->put_Name(CComBSTR("FATIGUE"));
   hr = fatigue->put_LoadCombinationType(lctFatigue);
   hr = fatigue->put_LiveLoadFactor(0.75);
   hr = fatigue->AddLiveLoadModel(lltFatigue);

   hr = fatigue->AddLoadCaseFactor(CComBSTR("CE"), 0.75, 0.75);

   hr = loadcombos->Add(fatigue);
}

template<class T>
void TestPersistance(T* pllc, const CLSID& ClsId)
{
   HRESULT hr;
   // test persistence by saving and retrieving data and comparing raw xml
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestCS"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pllc->QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a cross section to work with
      CComPtr<T> pcs2;
      TRY_TEST(pcs2.CoCreateInstance( ClsId ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestCS"));

         IStructuredStorage2* piss2=nullptr;
         TRY_TEST( pcs2.QueryInterface(&piss2), S_OK);

         // Load 
         TRY_TEST( piss2->Load(psl), S_OK );

         piss2->Release();

         VARIANT_BOOL end;
         hr = psl->EndUnit(&end);

         TRY_TEST( psl->Close(), S_OK );

         // now save to a different file so we can compare files
         CComPtr<IStructuredSave2> pss2;
         TRY_TEST( pss2.CoCreateInstance( CLSID_StructuredSave2 ), S_OK );
         TRY_TEST( pss2->Open( CComBSTR("Test2.xml")), S_OK );

         // save our loaded version
         hr = pss2->BeginUnit(CComBSTR("TestCS"), 1.0);
         TRY_TEST( piss2->Save(pss2), S_OK );
         hr = pss2->EndUnit();
         TRY_TEST( pss2->Close(), S_OK );
      }
   }
}

#endif //
