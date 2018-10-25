///////////////////////////////////////////////////////////////////////
// LBAM Live Load Test - Test driver for LBAM analysis library
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef __LiveLoadTestUtils_H_
#define __LiveLoadTestUtils_H_



inline void CompLLForceResults(BSTR Stage, OptimizationType optmization, ForceEffectType forceType, 
                             VehicularLoadConfigurationType vlcType, VARIANT_BOOL doApplyImpact,
                             VARIANT_BOOL doApplyDistribution,
                             ILiveLoadModelResponse* llmResponse, IBasicVehicularResponse* basicResponse,
                             std::_tofstream& os)
{
   // This function compares the enveloped result computed by the enveloping engine and then stuffs
   // the optimal configuration into the basic engine. The result should be the same if both engines are
   // working correctly. 
   // Of course, both engines could be computing the wrong answer....
   os<<"---------------------------------------------------"<< std::endl;
   os<<"Force Reponse for "<<(TCHAR*)_bstr_t(Stage)<<std::endl;
   os<< (optmization==optMaximize ? "Maximized Positive ":"Maximized Negative ")<<
      (forceType==fetMz? "Moment " : "Shear ")<<std::endl;

   switch (vlcType)
   {
   case vlcDefault:
      os <<"Truck Type: vlcDefault"<<std::endl;
      break;
   case vlcTruckOnly:
      os <<"Truck Type: vlcTruckOnly"<<std::endl;
      break;
   case vlcLaneOnly:
      os <<"Truck Type: vlcLaneOnly"<<std::endl;
      break;
   case vlcTruckPlusLane:
      os <<"Truck Type: vlcTruckPlusLane"<<std::endl;
      break;
   case vlcTruckLaneEnvelope:
      os <<"Truck Type: vlcTruckLaneEnvelope"<<std::endl;
      break;
   case vlcSidewalkOnly:
      os <<"Truck Type: vlcSidewalkOnly"<<std::endl;
      break;
   default:
      _ASSERT(0);
   }

   os << (doApplyImpact==VARIANT_FALSE? "No Impact": "Impact Applied")<<std::endl;
   os << (doApplyDistribution==VARIANT_FALSE? "No Distribution": "Distribution Applied")<<std::endl<<std::endl;

   os << " POI     Left Value     Right Value"<<std::endl;
   os << "-----  -------------   -------------"<<std::endl;

   const CollectionIndexType NUMPOIS=10;
   CComPtr<IIDArray> apois;
   apois.CoCreateInstance(CLSID_IDArray);
   apois->Reserve(NUMPOIS);
   for (CollectionIndexType i = 0; i<NUMPOIS; i++)
   {
      apois->Add((PoiIDType)i);
   }

   // compute enveloped results for all pois
   CComPtr<ILiveLoadModelSectionResults> results;
   TRY_TEST(llmResponse->ComputeForces(apois, Stage,lltDesign, roGlobal, forceType, optmization,
                                       vlcType, doApplyImpact, doApplyDistribution, VARIANT_TRUE, &results), S_OK);

   // have to compute basic result for a single poi for each configuration optimized at that poi
   CComPtr<IIDArray> apoi;
   apoi.CoCreateInstance(CLSID_IDArray);
   apoi->ReDim(1);

   for (CollectionIndexType j = 0; j<NUMPOIS; j++)
   {
      apoi->put_Item(0,(PoiIDType)j);

      // get enveloped value - with optimal configuration
      Float64 left_val, right_val;
      CComPtr<ILiveLoadConfiguration> left_config, right_config;
      TRY_TEST(results->GetResult(j, &left_val, &left_config, &right_val, &right_config), S_OK);

      // compute result using config and basic engine
      // left config first,
      CComPtr<ISectionResult3Ds> res3Ds;
      CComPtr<ISectionResult3D> res3D;
      Float64 vleft, vright;
      TRY_TEST(basicResponse->ComputeForces(apoi, Stage, roGlobal, left_config, &res3Ds), S_OK);

      // basic value
      TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
      TRY_TEST(res3D->GetSingleResult(forceType, &vleft, &vright), S_OK);

      // compare response
//      TRY_TEST(IsEqual(vleft,  left_val), true);

      os <<"L"<<std::setw(3) << j
         <<std::setw(16)<< left_val
         <<std::setw(16)<< right_val<<std::endl;

      // then right config if there was one
      if (right_config!=nullptr)
      {
         res3Ds.Release();
         TRY_TEST(basicResponse->ComputeForces(apoi, Stage, roGlobal, right_config, &res3Ds), S_OK);

         // basic value
         res3D.Release();
         TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
         TRY_TEST(res3D->GetSingleResult(forceType, &vleft, &vright), S_OK);

         // compare response
//         TRY_TEST(IsEqual(vright, right_val), true);

         os <<"R"<<std::setw(3) << j
            <<std::setw(16)<< left_val
            <<std::setw(16)<< right_val<<std::endl;
      }
   }
}


inline void CompLLDeflResults(BSTR Stage, OptimizationType optmization, ForceEffectType forceType, 
                              VehicularLoadConfigurationType vlcType, VARIANT_BOOL doApplyImpact,
                              VARIANT_BOOL doApplyDistribution,
                              ILiveLoadModelResponse* llmResponse, IBasicVehicularResponse* basicResponse,
                              std::_tofstream& os)
{
   // This function compares the enveloped result computed by the enveloping engine and then stuffs
   // the optimal configuration into the basic engine. The result should be the same if both engines are
   // working correctly. 
   // Of course, both engines could be computing the wrong answer....
   os<<"---------------------------------------------------"<< std::endl;
   os<<"Deflection Reponse for "<<(TCHAR*)_bstr_t(Stage)<<std::endl;
   os<< (optmization==optMaximize ? "Maximized Positive ":"Maximized Negative ")<<
      (forceType==fetMz? "Rotation " : "Vertical Deflection ")<<std::endl;

   switch (vlcType)
   {
   case vlcDefault:
      os <<"Truck Type: vlcDefault"<<std::endl;
      break;
   case vlcTruckOnly:
      os <<"Truck Type: vlcTruckOnly"<<std::endl;
      break;
   case vlcLaneOnly:
      os <<"Truck Type: vlcLaneOnly"<<std::endl;
      break;
   case vlcTruckPlusLane:
      os <<"Truck Type: vlcTruckPlusLane"<<std::endl;
      break;
   case vlcTruckLaneEnvelope:
      os <<"Truck Type: vlcTruckLaneEnvelope"<<std::endl;
      break;
   case vlcSidewalkOnly:
      os <<"Truck Type: vlcSidewalkOnly"<<std::endl;
      break;
   default:
      _ASSERT(0);
   }

   os << (doApplyImpact==VARIANT_FALSE? "No Impact": "Impact Applied")<<std::endl;
   os << (doApplyDistribution==VARIANT_FALSE? "No Distribution": "Distribution Applied")<<std::endl<<std::endl;

   os << " POI     Left Value     Right Value"<<std::endl;
   os << "-----  -------------   -------------"<<std::endl;

   const CollectionIndexType NUMPOIS=10;
   CComPtr<IIDArray> apois;
   apois.CoCreateInstance(CLSID_IDArray);
   apois->Reserve(NUMPOIS);
   for (CollectionIndexType i = 0; i<NUMPOIS; i++)
   {
      apois->Add((PoiIDType)i);
   }

   // compute enveloped results for all pois
   CComPtr<ILiveLoadModelSectionResults> results;
   TRY_TEST(llmResponse->ComputeDeflections(apois, Stage,lltDesign, forceType, optmization,
                                            vlcType, doApplyImpact, doApplyDistribution, VARIANT_TRUE, &results), S_OK);

   // have to compute basic result for a single poi for each configuration optimized at that poi
   CComPtr<IIDArray> apoi;
   apoi.CoCreateInstance(CLSID_IDArray);
   apoi->ReDim(1);

   for (CollectionIndexType j = 0; j<NUMPOIS; j++)
   {
      apoi->put_Item(0,(PoiIDType)j);

      // get enveloped value - with optimal configuration
      Float64 left_val, right_val;
      CComPtr<ILiveLoadConfiguration> left_config, right_config;
      TRY_TEST(results->GetResult(j, &left_val, &left_config, &right_val, &right_config), S_OK);

      // compute result using config and basic engine
      // left config first,
      CComPtr<ISectionResult3Ds> res3Ds;
      CComPtr<ISectionResult3D> res3D;
      Float64 vleft, vright;
      TRY_TEST(basicResponse->ComputeDeflections(apoi, Stage, left_config, &res3Ds), S_OK);

      // basic value
      TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
      TRY_TEST(res3D->GetSingleResult(forceType, &vleft, &vright), S_OK);

      // compare response
      TRY_TEST(IsEqual(vleft,  left_val, 0.01), true);

      os <<"L"<<std::setw(3) << j
         <<std::setw(16)<< left_val
         <<std::setw(16)<< right_val<<std::endl;

      // then right config if there was one
      if (right_config!=nullptr)
      {
         res3Ds.Release();
         TRY_TEST(basicResponse->ComputeDeflections(apoi, Stage, right_config, &res3Ds), S_OK);

         // basic value
         res3D.Release();
         TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
         TRY_TEST(res3D->GetSingleResult(forceType, &vleft, &vright), S_OK);

         // compare response
         TRY_TEST(IsEqual(vright, right_val,0.01), true);

         os <<"R"<<std::setw(3) << j
            <<std::setw(16)<< left_val
            <<std::setw(16)<< right_val<<std::endl;
      }
   }
}


inline void CompLLReactionResults(ILBAMModel* Model, BSTR Stage, OptimizationType optmization, ForceEffectType forceType, 
                                  VehicularLoadConfigurationType vlcType, VARIANT_BOOL doApplyImpact,
                                  VARIANT_BOOL doApplyDistribution,
                                  ILiveLoadModelResponse* llmResponse, IBasicVehicularResponse* basicResponse,
                                  std::_tofstream& os)
{
   HRESULT hr;
   // This function compares the enveloped result computed by the enveloping engine and then stuffs
   // the optimal configuration into the basic engine. The result should be the same if both engines are
   // working correctly. 
   // Of course, both engines could be computing the wrong answer....
   os<<"---------------------------------------------------"<< std::endl;
   os<<"Reaction Reponse for "<<(TCHAR*)_bstr_t(Stage)<<std::endl;
   os<< (optmization==optMaximize ? "Maximized Positive ":"Maximized Negative ");
   if (forceType==fetFx)
      os<<"X Direction"<<std::endl;
   else if (forceType==fetFy)
      os<<"Y Direction"<<std::endl;
   else
      os<<"Moment"<<std::endl;

   switch (vlcType)
   {
   case vlcDefault:
      os <<"Truck Type: vlcDefault"<<std::endl;
      break;
   case vlcTruckOnly:
      os <<"Truck Type: vlcTruckOnly"<<std::endl;
      break;
   case vlcLaneOnly:
      os <<"Truck Type: vlcLaneOnly"<<std::endl;
      break;
   case vlcTruckPlusLane:
      os <<"Truck Type: vlcTruckPlusLane"<<std::endl;
      break;
   case vlcTruckLaneEnvelope:
      os <<"Truck Type: vlcTruckLaneEnvelope"<<std::endl;
      break;
   case vlcSidewalkOnly:
      os <<"Truck Type: vlcSidewalkOnly"<<std::endl;
      break;
   default:
      _ASSERT(0);
   }

   os << (doApplyImpact==VARIANT_FALSE? "No Impact": "Impact Applied")<<std::endl;
   os << (doApplyDistribution==VARIANT_FALSE? "No Distribution": "Distribution Applied")<<std::endl<<std::endl;

   os << " POI     Reaction"<<std::endl;
   os << "-----  -------------"<<std::endl;

   // get list of supports for this stage
   CComPtr<IIDArray> support_ids;
   CComPtr<ILBAMFactory> gen_util;
   hr = gen_util.CoCreateInstance(CLSID_LRFDFactory);
   ATLASSERT(SUCCEEDED(hr));
   hr = gen_util->GetSupportIDsForStage(Model, Stage, &support_ids);
   ATLASSERT(SUCCEEDED(hr));

   CollectionIndexType nSupportIDs;
   support_ids->get_Count(&nSupportIDs);

   // compute enveloped results for all pois
   CComPtr<ILiveLoadModelResults> results;
   TRY_TEST(llmResponse->ComputeReactions(support_ids, Stage, lltDesign, forceType, optmization,
                                          vlcType, doApplyImpact, doApplyDistribution, VARIANT_TRUE, &results), S_OK);

   // have to compute basic result for a single poi for each configuration optimized at that poi
   CComPtr<IIDArray> asup;
   asup.CoCreateInstance(CLSID_IDArray);
   asup->ReDim(1);

   for (CollectionIndexType supportIDIdx = 0; supportIDIdx < nSupportIDs; supportIDIdx++)
   {
      asup->put_Item(0, (SupportIDType)supportIDIdx);

      // get enveloped value - with optimal configuration
      Float64 llmval;
      CComPtr<ILiveLoadConfiguration> config;
      TRY_TEST(results->GetResult(supportIDIdx, &llmval, &config), S_OK);

      // compute result using config and basic engine
      // left config first,
      CComPtr<IResult3Ds> res3Ds;
      CComPtr<IResult3D> res3D;
      TRY_TEST(basicResponse->ComputeReactions(asup, Stage, config, &res3Ds), S_OK);

      // basic value
      Float64 bval;
      TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
      TRY_TEST(res3D->GetSingleResult(forceType, &bval), S_OK);

      // compare response
      TRY_TEST(IsEqual(llmval,  bval,0.01), true);

      os <<"L"<<std::setw(3) << supportIDIdx <<std::setw(16)<< llmval<<std::endl;
   }
}

inline void CompLLSupportDeflectionResults(ILBAMModel* Model, BSTR Stage, OptimizationType optmization, ForceEffectType forceType, 
                                  VehicularLoadConfigurationType vlcType, VARIANT_BOOL doApplyImpact,
                                  VARIANT_BOOL doApplyDistribution,
                                  ILiveLoadModelResponse* llmResponse, IBasicVehicularResponse* basicResponse,
                                  std::_tofstream& os)
{
   HRESULT hr;
   // This function compares the enveloped result computed by the enveloping engine and then stuffs
   // the optimal configuration into the basic engine. The result should be the same if both engines are
   // working correctly. 
   // Of course, both engines could be computing the wrong answer....
   os<<"---------------------------------------------------"<< std::endl;
   os<<"SupportDeflection Reponse for "<<(TCHAR*)_bstr_t(Stage)<<std::endl;
   os<< (optmization==optMaximize ? "Maximized Positive ":"Maximized Negative ");
   if (forceType==fetFx)
      os<<"X Direction"<<std::endl;
   else if (forceType==fetFy)
      os<<"Y Direction"<<std::endl;
   else
      os<<"Moment"<<std::endl;

   switch (vlcType)
   {
   case vlcDefault:
      os <<"Truck Type: vlcDefault"<<std::endl;
      break;
   case vlcTruckOnly:
      os <<"Truck Type: vlcTruckOnly"<<std::endl;
      break;
   case vlcLaneOnly:
      os <<"Truck Type: vlcLaneOnly"<<std::endl;
      break;
   case vlcTruckPlusLane:
      os <<"Truck Type: vlcTruckPlusLane"<<std::endl;
      break;
   case vlcTruckLaneEnvelope:
      os <<"Truck Type: vlcTruckLaneEnvelope"<<std::endl;
      break;
   case vlcSidewalkOnly:
      os <<"Truck Type: vlcSidewalkOnly"<<std::endl;
      break;
   default:
      _ASSERT(0);
   }

   os << (doApplyImpact==VARIANT_FALSE? "No Impact": "Impact Applied")<<std::endl;
   os << (doApplyDistribution==VARIANT_FALSE? "No Distribution": "Distribution Applied")<<std::endl<<std::endl;

   os << " POI     SupportDeflection"<<std::endl;
   os << "-----  -------------"<<std::endl;

   // get list of supports for this stage
   CComPtr<IIDArray> support_ids;
   CComPtr<ILBAMFactory> gen_util;
   hr = gen_util.CoCreateInstance(CLSID_LRFDFactory);
   ATLASSERT(SUCCEEDED(hr));
   hr = gen_util->GetSupportIDsForStage(Model, Stage, &support_ids);
   ATLASSERT(SUCCEEDED(hr));

   CollectionIndexType nSupportIDs;
   support_ids->get_Count(&nSupportIDs);

   // compute enveloped results for all pois
   CComPtr<ILiveLoadModelResults> results;
   TRY_TEST(llmResponse->ComputeSupportDeflections(support_ids, Stage, lltDesign, forceType, optmization,
                                          vlcType, doApplyImpact, doApplyDistribution, VARIANT_TRUE, &results), S_OK);

   // have to compute basic result for a single poi for each configuration optimized at that poi
   CComPtr<IIDArray> asup;
   asup.CoCreateInstance(CLSID_IDArray);
   asup->ReDim(1);

   for (CollectionIndexType supportIDIdx = 0; supportIDIdx < nSupportIDs; supportIDIdx++)
   {
      asup->put_Item(0, (SupportIDType)supportIDIdx);

      // get enveloped value - with optimal configuration
      Float64 llmval;
      CComPtr<ILiveLoadConfiguration> config;
      TRY_TEST(results->GetResult(supportIDIdx, &llmval, &config), S_OK);

      // compute result using config and basic engine
      // left config first,
      CComPtr<IResult3Ds> res3Ds;
      CComPtr<IResult3D> res3D;
      TRY_TEST(basicResponse->ComputeSupportDeflections(asup, Stage, config, &res3Ds), S_OK);

      // basic value
      Float64 bval;
      TRY_TEST(res3Ds->get_Item(0, &res3D), S_OK);
      TRY_TEST(res3D->GetSingleResult(forceType, &bval), S_OK);

      // compare response
      TRY_TEST(IsEqual(llmval,  bval, 0.01), true);

      os <<"L"<<std::setw(3) << supportIDIdx <<std::setw(16)<< llmval<<std::endl;
   }
}


#endif

