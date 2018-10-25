///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2014  Washington State Department of Transportation
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

#include "LBAMAnalysisErrors.h"

// Help Context IDs
#define IDH_WBFLLBAMAnalysis                      	                 1600000


// Errors
#define IDH_E_DUPLICATE_STAGE_NAME                                   1600001
#define IDH_E_BLANK_LOADGROUP_NAMES_NOT_ALLOWED                      1600002
#define IDH_E_BLANK_STAGE_NAMES_NOT_ALLOWED                          1600003
#define IDH_E_DUPLICATE_STAGE_NAMES                                  1600005
#define IDH_E_DUPLICATE_LOADGROUP_NAMES                              1600006
#define IDH_E_MEMBER_LENGTH_MUST_BE_GT_ZERO                          1600009
#define IDH_E_SEGMENT_LENGTH_MUST_BE_GT_ZERO                         1600010
#define IDH_E_NO_SEGMENT_FOR_MEMBER                                  1600011
#define IDH_E_NO_REM_STAGE_FOR_TS                                    1600013
#define IDH_E_INVALID_TS_LOCATION                                    1600015
#define IDH_E_INVALID_SECTION_PROP                                   1600016
#define IDH_E_INVALID_SUPPORTS                                       1600017
#define IDH_E_SUPPORT_ROLLER_RELEASE                                 1600019
#define IDH_E_NO_SEGMENT_FOR_SUPPORT                                 1600020
#define IDH_E_SUPPORT_LENGTH_MUST_BE_GT_ZERO                         1600022
#define IDH_E_INVALID_TS_ID_SUPPORT                                  1600023
#define IDH_E_NONZERO_TEMPSUPPORT_ROLLER                             1600024
#define IDH_E_TEMPSUPPORT_LENGTH_MUST_BE_GT_ZERO                     1600026
#define IDH_E_INVALID_SEGMENT_LENGTH                                 1600027
#define IDH_E_INVALID_SS_SEGMENT_LENGTH                              1600028
#define IDH_E_TEMPORARY_SUPPORT_ID                                   1600029
#define IDH_E_POI_SPAN_OOR                                           1600031
#define IDH_E_POI_SSM_OOR                                            1600032
#define IDH_E_POI_SUPPORT_OOR                                        1600033
#define IDH_E_INVALID_POI_LOC                                        1600035
#define IDH_E_DUPLICATE_POI_ID                                       1600036
#define IDH_E_TEMPSUPPORT_DIST                                       1600037
#define IDH_E_POI_ZERO_LENGTH_SUPPORT                                1600038
#define IDH_E_LOC_4_ZERO_LENGTH_ZERO                                 1600044
#define IDH_E_POINT_LOAD_LOC                                         1600045
#define IDH_E_POINT_LOAD_UNKNOWN                                     1600046
#define IDH_E_LOADGROUP_NOT_FOUND                                    1600047
#define IDH_E_STAGE_NOT_FOUND                                        1600048
#define IDH_E_MODEL_DOES_NOT_EXIST                                   1600049
#define IDH_E_INVALID_MEMBER_TYPE                                    1600050
#define IDH_E_DIST_LOAD_ZERO_LENGTH                                  1600051
#define IDH_E_INVALID_DISTR_LOAD_LOCATION                            1600052
#define IDH_E_INVALID_LOAD_ORIENTATION                               1600053
#define IDH_E_INVALID_LOAD_DIRECTION                                 1600054
#define IDH_E_INVALID_STRAIN_LOC                                     1600055
#define IDH_E_GENERATING_STRAIN_LOAD                                 1600056
#define IDH_E_INVALID_TEMPERATURE_LOC                                1600057
#define IDH_E_GENERATING_TEMPERATURE_LOAD                            1600058
#define IDH_E_INVALID_DIST_LOC                                       1600059
#define IDH_E_TEMPERATURE_ZERO_DEPTH                                 1600060
#define IDH_E_SETTLEMENT_LOC                                         1600061
#define IDH_E_INVALID_HINGE_REMOVAL_STAGE                            1600062
#define IDH_E_TEMPORARY_SUPPORTS_TOO_CLOSE                           1600063
#define IDH_E_POI_NOT_FOUND                                          1600065
#define IDH_E_STRESS_NC                                              1600066
#define IDH_E_TEMP_POIS_CUMMULATIVE                                  1600071
#define IDH_E_INVALID_REGION                                         1600072
#define IDH_E_MM_STRESSPOINTS                                        1600073
#define IDH_E_INCOMP_STRESSRESULTS                                   1600074
#define IDH_E_NO_INFLUENCE_LOCATIONS                                 1600075
#define IDH_E_INSTABILITY                                            1600076
#define IDH_E_FEM2D                                                  1600077
#define IDH_E_POINT_LOAD_ZERO_LENGTH                                 1600078

// Constants
#define IDH_AnalysisType                                             1610000
#define IDH_ResultsOrientation                                       1610001
#define IDH_ResultsSummationType                                     1610002
#define IDH_InfluenceLocationType                                    1610003
#define IDH_ForceEffectType                                          1610004
#define IDH_OptimizationType                                         1610005
#define IDH_InfluenceSideType                                        1610006

// objects

#define IDH_AnalysisPOIs                                             1620000
#define IDH_AnalysisPOIs_CantileverPOIIncrement                      1620001
#define IDH_AnalysisPOIs_GetPoiInfo                                  1620002
#define IDH_AnalysisPOIs_GetSuperstructurePois                 1620003
#define IDH_AnalysisPOIs_SpanPOIIncrement                            1620004

#define IDH_ContraflexureResponse                                    1620005
#define IDH_ContraflexureResponse_ComputeContraflexureLocations      1620006
#define IDH_ContraflexureResponse_ComputeContraflexureResponse       1620007
#define IDH_ContraflexureResponse_IsPoiInContraflexureZone           1620008

#define IDH_DependOnLBAM                                             1620009
#define IDH_DependOnLBAM_IDependOnLBAM                               1620010
#define IDH_DependOnLBAM_Model                                       1620011

#define IDH_GetActiveLoadGroups                                      1620012
#define IDH_GetActiveLoadGroups_IGetActiveLoadGroups                 1620013

#define IDH_GetSegmentCrossSection                                          1620014
#define IDH_GetSegmentCrossSection_GetSegmentCrossSectionAtPOI                     1620015
#define IDH_GetSegmentCrossSection_IGetSegmentCrossSection                         1620016

#define IDH_GetDistributionFactors                                   1620017
#define IDH_GetDistributionFactors_GetPOIDistributionFactor          1620018
#define IDH_GetDistributionFactors_GetSupportDistributionFactor      1620019
#define IDH_GetDistributionFactors_IGetDistributionFactors           1620020

#define IDH_GetFemForLoadGroupResponse                               1620021
#define IDH_GetFemForLoadGroupResponse_IGetFemForLoadGroupResponse   1620022
#define IDH_GetFemForLoadGroupResponse_SaveFem2D                     1620023

#define IDH_GetStressPoints                                          1620024
#define IDH_GetStressPoints_GetStressPointsAtPOI                     1620025
#define IDH_GetStressPoints_IGetStressPoints                         1620026

#define IDH_InfluenceLine                                            1620027
#define IDH_InfluenceLine_Add                                        1620028
#define IDH_InfluenceLine_Bounds                                     1620029
#define IDH_InfluenceLine_Clear                                      1620030
#define IDH_InfluenceLine_Clone                                      1620031
#define IDH_InfluenceLine_ComputeArea                                1620032
#define IDH_InfluenceLine_ComputeAreaInRegions                       1620033
#define IDH_InfluenceLine_ComputeNonZeroRegions                      1620034
#define IDH_InfluenceLine_Count                                      1620035
#define IDH_InfluenceLine_Evaluate                                   1620036
#define IDH_InfluenceLine_IsZero                                     1620037
#define IDH_InfluenceLine_Item                                       1620038
#define IDH_InfluenceLine_Remove                                     1620039

#define IDH_InfluenceLineResponse                                    1620040
#define IDH_InfluenceLineResponse_ComputeDeflectionInfluenceLine     1620041
#define IDH_InfluenceLineResponse_ComputeForceInfluenceLine          1620042
#define IDH_InfluenceLineResponse_ComputeReactionInfluenceLine       1620043
#define IDH_InfluenceLineResponse_ComputeSupportDeflectionInfluenceLine 1620044
#define IDH_InfluenceLineResponse_GetZeroTolerance                   1620045
#define IDH_InfluenceLineResponse_IInfluenceLineResponse             1620046
#define IDH_InfluenceLineResponse_SetZeroTolerance                   1620047

#define IDH_LoadGroupDeflectionResponse                              1620049

#define IDH_LoadGroupForceResponse                                   1620050

#define IDH_LoadGroupResponse                                        1620051
#define IDH_LoadGroupResponse_ComputeDeflections                     1620052
#define IDH_LoadGroupResponse_ComputeForces                          1620053
#define IDH_LoadGroupResponse_ComputeReactions                       1620054
#define IDH_LoadGroupResponse_ComputeStresses                        1620055
#define IDH_LoadGroupResponse_ComputeSupportDeflections              1620056

#define IDH_Result3D                                                 1620057
#define IDH_Result3D_Clone                                           1620058
#define IDH_Result3D_FactorAndSum                                    1620059
#define IDH_Result3D_GetResult                                       1620060
#define IDH_Result3D_GetSingleResult                                 1620061
#define IDH_Result3D_SetResult                                       1620062
#define IDH_Result3D_SetSingleResult                                 1620063
#define IDH_Result3D_Sum                                             1620064
#define IDH_Result3D_X                                               1620065
#define IDH_Result3D_Y                                               1620066
#define IDH_Result3D_Z                                               1620067
#define IDH_Result3D_Zero                                            1620068

#define IDH_Result3Ds                                                1620069
#define IDH_Result3Ds_Add                                            1620070
#define IDH_Result3Ds_Clear                                          1620071
#define IDH_Result3Ds_Clone                                          1620072
#define IDH_Result3Ds_Count                                          1620073
#define IDH_Result3Ds_Insert                                         1620074
#define IDH_Result3Ds_Item                                           1620075
#define IDH_Result3Ds_Remove                                         1620076
#define IDH_Result3Ds_Reserve                                        1620077
#define IDH_Result3Ds__EnumElements                                  1620078

#define IDH_SectionResult3D                                          1620079
#define IDH_SectionResult3D_Clone                                    1620080
#define IDH_SectionResult3D_FactorAndSum                             1620081
#define IDH_SectionResult3D_GetResult                                1620082
#define IDH_SectionResult3D_GetSingleResult                          1620083
#define IDH_SectionResult3D_SetResult                                1620084
#define IDH_SectionResult3D_SetSingleResult                          1620085
#define IDH_SectionResult3D_Sum                                      1620086
#define IDH_SectionResult3D_XLeft                                    1620087
#define IDH_SectionResult3D_XRight                                   1620088
#define IDH_SectionResult3D_YLeft                                    1620089
#define IDH_SectionResult3D_YRight                                   1620090
#define IDH_SectionResult3D_Zero                                     1620091
#define IDH_SectionResult3D_ZLeft                                    1620092
#define IDH_SectionResult3D_ZRight                                   1620093

#define IDH_SectionResult3Ds                                         1620094
#define IDH_SectionResult3Ds_Add                                     1620095
#define IDH_SectionResult3Ds_Clear                                   1620096
#define IDH_SectionResult3Ds_Clone                                   1620097
#define IDH_SectionResult3Ds_Count                                   1620098
#define IDH_SectionResult3Ds_Insert                                  1620099
#define IDH_SectionResult3Ds_Item                                    1620100
#define IDH_SectionResult3Ds_Remove                                  1620101
#define IDH_SectionResult3Ds_Reserve                                 1620102
#define IDH_SectionResult3Ds__EnumElements                           1620103

#define IDH_SectionStressResult                                      1620104
#define IDH_SectionStressResult_AddLeftResult                        1620105
#define IDH_SectionStressResult_AddRightResult                       1620106
#define IDH_SectionStressResult_Clone                                1620107
#define IDH_SectionStressResult_CreateLeftStressResult               1620108
#define IDH_SectionStressResult_CreateRightStressResult              1620109
#define IDH_SectionStressResult_FactorAndSum                         1620110
#define IDH_SectionStressResult_GetLeftResult                        1620111
#define IDH_SectionStressResult_GetRightResult                       1620112
#define IDH_SectionStressResult_LeftCount                            1620113
#define IDH_SectionStressResult_RightCount                           1620114
#define IDH_SectionStressResult_SetLeftResult                        1620115
#define IDH_SectionStressResult_SetRightResult                       1620116

#define IDH_SectionStressResults                                     1620117
#define IDH_SectionStressResults_Add                                 1620118
#define IDH_SectionStressResults_Clear                               1620119
#define IDH_SectionStressResults_Clone                               1620120
#define IDH_SectionStressResults_Count                               1620121
#define IDH_SectionStressResults_Insert                              1620122
#define IDH_SectionStressResults_Item                                1620123
#define IDH_SectionStressResults_Remove                              1620124
#define IDH_SectionStressResults_Reserve                             1620125
#define IDH_SectionStressResults__EnumElements                       1620126

#define IDH_StressResult                                             1620127
#define IDH_StressResult_AddResult                                   1620128
#define IDH_StressResult_Clone                                       1620129
#define IDH_StressResult_Count                                       1620130
#define IDH_StressResult_FactorAndSum                                1620131
#define IDH_StressResult_GetResult                                   1620132
#define IDH_StressResult_SetResult                                   1620133

#define IDH_StressResults                                            1620134
#define IDH_StressResults_Add                                        1620135
#define IDH_StressResults_Clear                                      1620136
#define IDH_StressResults_Clone                                      1620137
#define IDH_StressResults_Count                                      1620138
#define IDH_StressResults_Insert                                     1620139
#define IDH_StressResults_Item                                       1620140
#define IDH_StressResults_Remove                                     1620141
#define IDH_StressResults_Reserve                                    1620142
#define IDH_StressResults__EnumElements                              1620143

#define IDH_LiveLoadNegativeMomentRegion                             1620144
#define IDH_LiveLoadNegativeMomentRegion_IsPOIInNegativeLiveLoadMomentZone  1620145
#define IDH_LiveLoadNegativeMomentRegion_ComputeNegativeMomentRegions  1620146
