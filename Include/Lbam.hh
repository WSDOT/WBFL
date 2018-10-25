///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2010  Washington State Department of Transportation
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

///////////////////////////////////////////////////////////////////////
// LBAM - Longitudinal Bridge Analysis Model
// Copyright © 1999-2010  Washington State Department of Transportation
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

// this include is here to trick the midl compiler into thinking that LBAM.idl is dependent on the errors file
#include "LBAMErrors.h"

// Help Context IDs
#define IDH_WBFLLBAM                           	                 1500000

// Errors
#define IDH_E_STAGE_NOT_EXISTS                                        1500001
#define IDH_E_BLANK_NAMES_NOT_ALLOWED                                 1500002
#define IDH_E_INVALID_INTEGER_ARRAY                                   1500003
#define IDH_E_MUST_HAVE_ONE_SPAN                                      1500004
#define IDH_E_MUST_HAVE_ONE_SSM                                       1500005
#define IDH_E_SPAN_LENGTH_MUST_BE_GT_ZERO                             1500006
#define IDH_E_SPAN_LENGTH_EXCEEDS_SUPERSTRUCTUREMEMBERS               1500007
#define IDH_E_SSM_LENGTH_MUST_BE_GT_ZERO                              1500008
#define IDH_E_TEMPSUPPORT_NOT_EXIST                                   1500009
#define IDH_E_SPAN_NOT_EXIST                                          1500010
#define IDH_E_SUPPORT_NOT_EXIST                                       1500011
#define IDH_E_SSM_NOT_EXIST                                           1500012
#define IDH_E_LOCATION_OOR                                            1500013
#define IDH_E_SUPPORT_OFFSET_GT_LENGTH                                1500014
#define IDH_E_TEMPSUPPORT_OFFSET_GT_LENGTH                            1500015
#define IDH_E_INVALID_MEMBERTYPE                                      1500016
#define IDH_E_NO_SEGMENTS_FOR_STAGE                                   1500017
#define IDH_E_POI_NO_STAGE                                            1500018
#define IDH_E_INVALID_POI_MEMBER_TYPE                                 1500019
#define IDH_E_POI_TEMP_SUPPORT_OOR                                    1500020


// Constants
#define IDH_ChangeType                                               1510001
#define IDH_MemberReleaseType                                        1510002
#define IDH_MemberType                                               1510003
#define IDH_BoundaryConditionType                                    1510004
#define IDH_Side                                                     1510005
#define IDH_LoadOrientation                                          1510006
#define IDH_LoadDirection                                            1510007
#define IDH_DistributionFactorType                                   1510008
#define IDH_VehicularLoadConfigurationType                           1510009
#define IDH_LiveLoadApplicabilityType                                1510010
#define IDH_LiveLoadModelType                                        1510011
#define IDH_TruckDirectionType                                       1510012
#define IDH_InZoneType                                               1510013
#define IDH_LoadCombinationType                                      1510014
#define IDH_ChangeScopeType                                          1510015


// Objects
#define IDH_Axle                                                         1520000
#define IDH_Axle_Clone                                                   1520001
#define IDH_Axle_OnAxleChanged                                           1520002
#define IDH_Axle_Spacing                                                 1520003
#define IDH_Axle_Weight                                                  1520004

#define IDH_Axles                                                        1520006
#define IDH_Axles_Add                                                    1520007
#define IDH_Axles_Clear                                                  1520008
#define IDH_Axles_Clone                                                  1520009
#define IDH_Axles_CopyTo                                                 1520010
#define IDH_Axles_Count                                                  1520011
#define IDH_Axles_Insert                                                 1520012
#define IDH_Axles_Item                                                   1520013
#define IDH_Axles_MoveTo                                                 1520014
#define IDH_Axles_OnAxlesAdded                                           1520015
#define IDH_Axles_OnAxlesBeforeRemove                                    1520016
#define IDH_Axles_OnAxlesChanged                                         1520017
#define IDH_Axles_OnAxlesCopyTo                                          1520018
#define IDH_Axles_OnAxlesMoveTo                                          1520019
#define IDH_Axles_OnAxlesReverse                                         1520020
#define IDH_Axles_Remove                                                 1520021
#define IDH_Axles_Reverse                                                1520022
#define IDH_Axles__EnumElements                                          1520023

#define IDH_SegmentCrossSection                                                 1520025
#define IDH_SegmentCrossSection_Clone                                           1520026
#define IDH_SegmentCrossSection_Depth                                           1520027
#define IDH_SegmentCrossSection_EADefl                                          1520028
#define IDH_SegmentCrossSection_EAForce                                         1520029
#define IDH_SegmentCrossSection_EIDefl                                          1520030
#define IDH_SegmentCrossSection_EIForce                                         1520031
#define IDH_SegmentCrossSection_GetStiffness                                    1520032
#define IDH_SegmentCrossSection_OnSegmentCrossSectionChanged                           1520033
#define IDH_SegmentCrossSection_SetStiffness                                    1520034
#define IDH_SegmentCrossSection_StressPoints                                    1520035
#define IDH_SegmentCrossSection_ThermalCoeff                                    1520036

#define IDH_DistributedLoad                                              1520038
#define IDH_DistributedLoad_Clone                                        1520039
#define IDH_DistributedLoad_Direction                                    1520040
#define IDH_DistributedLoad_EndLocation                                  1520041
#define IDH_DistributedLoad_MemberID                                     1520042
#define IDH_DistributedLoad_MemberType                                   1520043
#define IDH_DistributedLoad_OnDistributedLoadChanged                     1520044
#define IDH_DistributedLoad_Orientation                                  1520045
#define IDH_DistributedLoad_StartLocation                                1520046
#define IDH_DistributedLoad_WEnd                                         1520047
#define IDH_DistributedLoad_WStart                                       1520048

#define IDH_DistributedLoads                                             1520050

#define IDH_DistributionFactor                                           1520052
#define IDH_DistributionFactor_Clone                                     1520053
#define IDH_DistributionFactor_GDMul                                     1520054
#define IDH_DistributionFactor_GDSgl                                     1520055
#define IDH_DistributionFactor_GetG                                      1520056
#define IDH_DistributionFactor_GFat                                      1520057
#define IDH_DistributionFactor_GNMMul                                    1520058
#define IDH_DistributionFactor_GNMSgl                                    1520059
#define IDH_DistributionFactor_GPMMul                                    1520060
#define IDH_DistributionFactor_GPMSgl                                    1520061
#define IDH_DistributionFactor_GRMul                                     1520062
#define IDH_DistributionFactor_GRSgl                                     1520063
#define IDH_DistributionFactor_GTMul                                     1520064
#define IDH_DistributionFactor_GTSgl                                     1520065
#define IDH_DistributionFactor_GVMul                                     1520066
#define IDH_DistributionFactor_GVSgl                                     1520067
#define IDH_DistributionFactor_OnDistibutionFactorChanged                1520068
#define IDH_DistributionFactor_SetG                                      1520069

#define IDH_DistributionFactors                                          1520071
#define IDH_DistributionFactors_Add                                      1520072
#define IDH_DistributionFactors_Clear                                    1520073
#define IDH_DistributionFactors_Clone                                    1520074
#define IDH_DistributionFactors_CopyTo                                   1520075
#define IDH_DistributionFactors_Count                                    1520076
#define IDH_DistributionFactors_GetMemberSegments                        1520077
#define IDH_DistributionFactors_GetSegmentForLocation                    1520078
#define IDH_DistributionFactors_Insert                                   1520079
#define IDH_DistributionFactors_IsSymmetrical                            1520080
#define IDH_DistributionFactors_Item                                     1520081
#define IDH_DistributionFactors_Length                                   1520082
#define IDH_DistributionFactors_MoveTo                                   1520083
#define IDH_DistributionFactors_OnDistributionFactorsAdded               1520084
#define IDH_DistributionFactors_OnDistributionFactorsBeforeRemove        1520085
#define IDH_DistributionFactors_OnDistributionFactorsChanged             1520086
#define IDH_DistributionFactors_OnDistributionFactorsCopyTo              1520087
#define IDH_DistributionFactors_OnDistributionFactorsMoveTo              1520088
#define IDH_DistributionFactors_OnDistributionFactorsReverse             1520089
#define IDH_DistributionFactors_Remove                                   1520090
#define IDH_DistributionFactors_Reverse                                  1520091
#define IDH_DistributionFactors__EnumElements                            1520092

#define IDH_DistributionFactorSegment                                    1520094
#define IDH_DistributionFactorSegment_Clone                              1520095
#define IDH_DistributionFactorSegment_DistributionFactor                 1520096
#define IDH_DistributionFactorSegment_Length                             1520097
#define IDH_DistributionFactorSegment_OnDistributionFactorSegmentChanged 1520098

#define IDH_FastEnumerators                                              1520100

#define IDH_FilteredDfSegmentCollection                                  1520102
#define IDH_FilteredDfSegmentCollection_Count                            1520103
#define IDH_FilteredDfSegmentCollection_Item                             1520104
#define IDH_FilteredDfSegmentCollection__EnumElements                    1520105

#define IDH_FilteredSegmentCollection                                    1520107
#define IDH_FilteredSegmentCollection_Count                              1520108
#define IDH_FilteredSegmentCollection_Item                               1520109
#define IDH_FilteredSegmentCollection__EnumElements                      1520110

#define IDH_LiveLoad                                                     1520112
#define IDH_LiveLoad_Clear                                               1520113
#define IDH_LiveLoad_Clone                                               1520114
#define IDH_LiveLoad_Deflection                                          1520115
#define IDH_LiveLoad_Design                                              1520116
#define IDH_LiveLoad_Fatigue                                             1520117
#define IDH_LiveLoad_OnLiveLoadChanged                                   1520118
#define IDH_LiveLoad_Pedestrian                                          1520119
#define IDH_LiveLoad_Permit                                              1520120
#define IDH_LiveLoad_Special                                             1520121

#define IDH_LiveLoadModel                                                1520123
#define IDH_LiveLoadModel_Clear                                          1520124
#define IDH_LiveLoadModel_Clone                                          1520125
#define IDH_LiveLoadModel_DistributionFactorType                         1520126
#define IDH_LiveLoadModel_Name                                           1520127
#define IDH_LiveLoadModel_OnLiveLoadModelChanged                         1520128
#define IDH_LiveLoadModel_VehicularLoads                                 1520129

#define IDH_LoadCase                                                     1520131
#define IDH_LoadCase_AddLoadGroup                                        1520132
#define IDH_LoadCase_Clear                                               1520133
#define IDH_LoadCase_Clone                                               1520134
#define IDH_LoadCase_Description                                         1520135
#define IDH_LoadCase_GetLoadGroup                                        1520136
#define IDH_LoadCase_ItemData                                            1520137
#define IDH_LoadCase_LoadGroupCount                                      1520138
#define IDH_LoadCase_Name                                                1520139
#define IDH_LoadCase_OnLoadCaseChanged                                   1520140
#define IDH_LoadCase_OnLoadCaseRenamed                                   1520141
#define IDH_LoadCase_RemoveLoadGroup                                     1520142
#define IDH_LoadCase_RemoveLoadGroupByIndex                              1520143
#define IDH_LoadCase_SetLoadGroup                                        1520144

#define IDH_LoadCases                                                    1520146
#define IDH_LoadCases_Add                                                1520147
#define IDH_LoadCases_Clear                                              1520148
#define IDH_LoadCases_Clone                                              1520149
#define IDH_LoadCases_Count                                              1520150
#define IDH_LoadCases_Find                                               1520151
#define IDH_LoadCases_Insert                                             1520152
#define IDH_LoadCases_Item                                               1520153
#define IDH_LoadCases_OnLoadCasesAdded                                   1520154
#define IDH_LoadCases_OnLoadCasesBeforeRemove                            1520155
#define IDH_LoadCases_OnLoadCasesChanged                                 1520156
#define IDH_LoadCases_OnLoadCasesRenamed                                 1520157
#define IDH_LoadCases_RemoveByIndex                                      1520158
#define IDH_LoadCases_RemoveByName                                       1520159
#define IDH_LoadCases__EnumElements                                      1520160

#define IDH_LoadCombination                                              1520162
#define IDH_LoadCombination_AddLoadCaseFactor                            1520163
#define IDH_LoadCombination_Clear                                        1520164
#define IDH_LoadCombination_Clone                                        1520165
#define IDH_LoadCombination_Description                                  1520166
#define IDH_LoadCombination_GetLoadCaseFactor                            1520167
#define IDH_LoadCombination_ItemData                                     1520168
#define IDH_LoadCombination_LiveLoadFactor                               1520169
#define IDH_LoadCombination_LiveLoadModel                                1520170
#define IDH_LoadCombination_LoadCaseFactorCount                          1520171
#define IDH_LoadCombination_LoadCombinationType                          1520172
#define IDH_LoadCombination_Name                                         1520173
#define IDH_LoadCombination_OnLoadCombinationChanged                     1520174
#define IDH_LoadCombination_OnLoadCombinationRenamed                     1520175
#define IDH_LoadCombination_RemoveLoadCaseFactor                         1520176
#define IDH_LoadCombination_SetLoadCaseFactor                            1520177

#define IDH_LoadCombinations                                             1520179
#define IDH_LoadCombinations_Add                                         1520180
#define IDH_LoadCombinations_Clear                                       1520181
#define IDH_LoadCombinations_Clone                                       1520182
#define IDH_LoadCombinations_Count                                       1520183
#define IDH_LoadCombinations_Find                                        1520184
#define IDH_LoadCombinations_Insert                                      1520185
#define IDH_LoadCombinations_Item                                        1520186
#define IDH_LoadCombinations_OnLoadCombinationsAdded                     1520187
#define IDH_LoadCombinations_OnLoadCombinationsBeforeRemove              1520188
#define IDH_LoadCombinations_OnLoadCombinationsChanged                   1520189
#define IDH_LoadCombinations_OnLoadCombinationsRenamed                   1520190
#define IDH_LoadCombinations_RemoveByIndex                               1520191
#define IDH_LoadCombinations_RemoveByName                                1520192
#define IDH_LoadCombinations__EnumElements                               1520193

#define IDH_LoadGroup                                                    1520195
#define IDH_LoadGroup_Clone                                              1520196
#define IDH_LoadGroup_Description                                        1520197
#define IDH_LoadGroup_Name                                               1520198
#define IDH_LoadGroup_OnLoadGroupChanged                                 1520199
#define IDH_LoadGroup_OnLoadGroupRenamed                                 1520200
#define IDH_LoadGroup_Transient                                          1520201

#define IDH_LoadGroups                                                   1520203
#define IDH_LoadGroups_Add                                               1520204
#define IDH_LoadGroups_Clear                                             1520205
#define IDH_LoadGroups_Clone                                             1520206
#define IDH_LoadGroups_Count                                             1520207
#define IDH_LoadGroups_Find                                              1520208
#define IDH_LoadGroups_Insert                                            1520209
#define IDH_LoadGroups_Item                                              1520210
#define IDH_LoadGroups_OnLoadGroupsAdded                                 1520211
#define IDH_LoadGroups_OnLoadGroupsBeforeRemove                          1520212
#define IDH_LoadGroups_OnLoadGroupsChanged                               1520213
#define IDH_LoadGroups_OnLoadGroupsRenamed                               1520214
#define IDH_LoadGroups_RemoveByIndex                                     1520215
#define IDH_LoadGroups_RemoveByName                                      1520216
#define IDH_LoadGroups__EnumElements                                     1520217

#define IDH_LoadItem                                                     1520219
#define IDH_LoadItem_ID                                                  1520220
#define IDH_LoadItem_Load                                                1520221
#define IDH_LoadItem_LoadGroup                                           1520222
#define IDH_LoadItem_Stage                                               1520223

#define IDH_Load_Collections                                             1520225
#define IDH_Load_Collections_Add                                         1520226
#define IDH_Load_Collections_Clear                                       1520227
#define IDH_Load_Collections_Clone                                       1520228
#define IDH_Load_Collections_Count                                       1520229
#define IDH_Load_Collections_FilterByStageGroup                          1520230
#define IDH_Load_Collections_Find                                        1520231
#define IDH_Load_Collections_Item                                        1520232
#define IDH_Load_Collections_Load                                        1520233
#define IDH_Load_Collections_OnLoadsAdded                                1520234
#define IDH_Load_Collections_OnLoadsBeforeRemove                         1520235
#define IDH_Load_Collections_OnLoadsChanged                              1520236
#define IDH_Load_Collections_RemoveByID                                  1520237
#define IDH_Load_Collections_RemoveByIndex                               1520238
#define IDH_Load_Collections_RemoveStage                                 1520239
#define IDH_Load_Collections__EnumElements                               1520240

#define IDH_Model                                                        1520242
#define IDH_Model_Clear                                                  1520243
#define IDH_Model_Clone                                                  1520244
#define IDH_Model_ComputeLocation                                        1520245
#define IDH_Model_DistributedLoads                                       1520246
#define IDH_Model_DistributionFactors                                    1520247
#define IDH_Model_LeftSpan                                               1520248
#define IDH_Model_LeftSupport                                            1520249
#define IDH_Model_LiveLoad                                               1520250
#define IDH_Model_LoadCases                                              1520251
#define IDH_Model_LoadCombinations                                       1520252
#define IDH_Model_LoadGroups                                             1520253
#define IDH_Model_OnModelChanged                                         1520254
#define IDH_Model_PointLoads                                             1520255
#define IDH_Model_POIs                                                   1520256
#define IDH_Model_RemoveStage                                            1520257
#define IDH_Model_RightSpan                                              1520258
#define IDH_Model_RightSupport                                           1520259
#define IDH_Model_SettlementLoads                                        1520260
#define IDH_Model_Spans                                                  1520261
#define IDH_Model_Stages                                                 1520262
#define IDH_Model_StrainLoads                                            1520263
#define IDH_Model_SuperstructureMembers                                  1520264
#define IDH_Model_Supports                                               1520265
#define IDH_Model_TemperatureLoads                                       1520266

#define IDH_POI                                                          1520268
#define IDH_POI_Clone                                                    1520269
#define IDH_POI_ID                                                       1520270
#define IDH_POI_Location                                                 1520271
#define IDH_POI_MemberID                                                 1520272
#define IDH_POI_MemberType                                               1520273
#define IDH_POI_OnPOIChanged                                             1520274
#define IDH_POI_OnPOIRenamed                                             1520275
#define IDH_POI_POIStressPoints                                          1520276

#define IDH_PointLoad                                                    1520278
#define IDH_PointLoad_Clone                                              1520279
#define IDH_PointLoad_Fx                                                 1520280
#define IDH_PointLoad_Fy                                                 1520281
#define IDH_PointLoad_GetForce                                           1520282
#define IDH_PointLoad_Location                                           1520283
#define IDH_PointLoad_MemberID                                           1520284
#define IDH_PointLoad_MemberType                                         1520285
#define IDH_PointLoad_Mz                                                 1520286
#define IDH_PointLoad_OnPointLoadChanged                                 1520287
#define IDH_PointLoad_SetForce                                           1520288

#define IDH_PointLoads                                                   1520290

#define IDH_POIs                                                         1520292
#define IDH_POIs_Add                                                     1520293
#define IDH_POIs_Clear                                                   1520294
#define IDH_POIs_Clone                                                   1520295
#define IDH_POIs_Count                                                   1520296
#define IDH_POIs_Find                                                    1520297
#define IDH_POIs_Item                                                    1520298
#define IDH_POIs_OnPOIsAdded                                             1520299
#define IDH_POIs_OnPOIsBeforeRemove                                      1520300
#define IDH_POIs_OnPOIsChanged                                           1520301
#define IDH_POIs_OnPOIsRenamed                                           1520302
#define IDH_POIs_RemoveByID                                              1520303
#define IDH_POIs_RemoveByIndex                                           1520304
#define IDH_POIs__EnumElements                                           1520305

#define IDH_POIStressPoints                                              1520307
#define IDH_POIStressPoints_Clear                                        1520308
#define IDH_POIStressPoints_Clone                                        1520309
#define IDH_POIStressPoints_Count                                        1520310
#define IDH_POIStressPoints_Insert                                       1520311
#define IDH_POIStressPoints_Item                                         1520312
#define IDH_POIStressPoints_OnPOIStressPointsAdded                       1520313
#define IDH_POIStressPoints_OnPOIStressPointsBeforeRemove                1520314
#define IDH_POIStressPoints_OnPOIStressPointsChanged                     1520315
#define IDH_POIStressPoints_Remove                                       1520316
#define IDH_POIStressPoints__EnumElements                                1520317

#define IDH_POIStressPointsItem                                          1520319
#define IDH_POIStressPointsItem_LeftStressPoints                         1520320
#define IDH_POIStressPointsItem_RightStressPoints                        1520321
#define IDH_POIStressPointsItem_Stage                                    1520322

#define IDH_Segment                                                      1520324
#define IDH_Segment_Clone                                                1520325
#define IDH_Segment_SegmentCrossSection                                         1520326
#define IDH_Segment_Length                                               1520327
#define IDH_Segment_OnSegmentChanged                                     1520328

#define IDH_SegmentItem                                                  1520330
#define IDH_SegmentItem_Clone                                            1520331
#define IDH_SegmentItem_OnSegmentItemChanged                             1520332
#define IDH_SegmentItem_RelPosition                                      1520333
#define IDH_SegmentItem_Segment                                          1520334
#define IDH_SegmentItem_Stage                                            1520335

#define IDH_SettlementLoad                                               1520337
#define IDH_SettlementLoad_Clone                                         1520338
#define IDH_SettlementLoad_Dx                                            1520339
#define IDH_SettlementLoad_Dy                                            1520340
#define IDH_SettlementLoad_MemberID                                      1520341
#define IDH_SettlementLoad_OnSettlementLoadChanged                       1520342
#define IDH_SettlementLoad_Rz                                            1520343

#define IDH_SettlementLoads                                              1520345

#define IDH_Span                                                         1520347
#define IDH_Span_Clone                                                   1520348
#define IDH_Span_Length                                                  1520349
#define IDH_Span_LoadModifier                                            1520350
#define IDH_Span_OnSpanChanged                                           1520351
#define IDH_Span_RemoveStage                                             1520352
#define IDH_Span_TemporarySupports                                       1520353

#define IDH_Spans                                                        1520355
#define IDH_Spans_Add                                                    1520356
#define IDH_Spans_Clear                                                  1520357
#define IDH_Spans_Clone                                                  1520358
#define IDH_Spans_CopyTo                                                 1520359
#define IDH_Spans_Count                                                  1520360
#define IDH_Spans_Insert                                                 1520361
#define IDH_Spans_Item                                                   1520362
#define IDH_Spans_Length                                                 1520363
#define IDH_Spans_MoveTo                                                 1520364
#define IDH_Spans_OnSpansAdded                                           1520365
#define IDH_Spans_OnSpansBeforeRemove                                    1520366
#define IDH_Spans_OnSpansChanged                                         1520367
#define IDH_Spans_OnSpansCopyTo                                          1520368
#define IDH_Spans_OnSpansMoveTo                                          1520369
#define IDH_Spans_OnSpansReverse                                         1520370
#define IDH_Spans_Remove                                                 1520371
#define IDH_Spans_Reverse                                                1520372
#define IDH_Spans__EnumElements                                          1520373

#define IDH_Stage                                                        1520375
#define IDH_Stage_Clone                                                  1520376
#define IDH_Stage_Description                                            1520377
#define IDH_Stage_Name                                                   1520378
#define IDH_Stage_OnStageChanged                                         1520379

#define IDH_Stages                                                       1520381
#define IDH_Stages_Add                                                   1520382
#define IDH_Stages_Clear                                                 1520383
#define IDH_Stages_Clone                                                 1520384
#define IDH_Stages_Count                                                 1520385
#define IDH_Stages_FindIndex                                             1520386
#define IDH_Stages_Insert                                                1520387
#define IDH_Stages_Item                                                  1520388
#define IDH_Stages_MoveTo                                                1520389
#define IDH_Stages_OnStagesAdded                                         1520390
#define IDH_Stages_OnStagesBeforeRemove                                  1520391
#define IDH_Stages_OnStagesChanged                                       1520392
#define IDH_Stages_OnStagesCopyTo                                        1520393
#define IDH_Stages_OnStagesMoveTo                                        1520394
#define IDH_Stages_OnStagesReverse                                       1520395
#define IDH_Stages_RemoveByIndex                                         1520396
#define IDH_Stages_RemoveByName                                          1520397
#define IDH_Stages_Reverse                                               1520398
#define IDH_Stages__EnumElements                                         1520399

#define IDH_StrainLoad                                                   1520401
#define IDH_StrainLoad_AxialStrain                                       1520402
#define IDH_StrainLoad_Clone                                             1520403
#define IDH_StrainLoad_CurvatureStrain                                   1520404
#define IDH_StrainLoad_MemberID                                          1520405
#define IDH_StrainLoad_MemberType                                        1520406
#define IDH_StrainLoad_OnStrainLoadChanged                               1520407

#define IDH_StrainLoads                                                  1520409

#define IDH_StressPoint                                                  1520411
#define IDH_StressPoint_Clone                                            1520412
#define IDH_StressPoint_OnStressPointChanged                             1520413
#define IDH_StressPoint_Sa                                               1520414
#define IDH_StressPoint_Sm                                               1520415

#define IDH_StressPoints                                                 1520417
#define IDH_StressPoints_Add                                             1520418
#define IDH_StressPoints_Clear                                           1520419
#define IDH_StressPoints_Clone                                           1520420
#define IDH_StressPoints_Count                                           1520421
#define IDH_StressPoints_Insert                                          1520422
#define IDH_StressPoints_Item                                            1520423
#define IDH_StressPoints_OnStressPointsAdded                             1520424
#define IDH_StressPoints_OnStressPointsChanged                           1520425
#define IDH_StressPoints_OnStressPointsRemoved                           1520426
#define IDH_StressPoints_Remove                                          1520427
#define IDH_StressPoints__EnumElements                                   1520428

#define IDH_SuperstructureMember                                         1520430
#define IDH_SuperstructureMember_AddSegment                              1520431
#define IDH_SuperstructureMember_Clone                                   1520432
#define IDH_SuperstructureMember_CopySegmentTo                           1520433
#define IDH_SuperstructureMember_GetEndRelease                           1520434
#define IDH_SuperstructureMember_GetMemberSegments                       1520435
#define IDH_SuperstructureMember_GetSegmentForMemberLocation             1520436
#define IDH_SuperstructureMember_GetSegmentsForStage                     1520437
#define IDH_SuperstructureMember_InsertSegment                           1520438
#define IDH_SuperstructureMember_IsSymmetrical                           1520439
#define IDH_SuperstructureMember_Length                                  1520440
#define IDH_SuperstructureMember_MoveSegmentTo                           1520441
#define IDH_SuperstructureMember_OnSuperstructureMemberChanged           1520442
#define IDH_SuperstructureMember_RemoveSegment                           1520443
#define IDH_SuperstructureMember_RemoveStage                             1520444
#define IDH_SuperstructureMember_ReverseSegments                         1520445
#define IDH_SuperstructureMember_Segment                                 1520446
#define IDH_SuperstructureMember_SegmentCount                            1520447
#define IDH_SuperstructureMember_SegmentLength                           1520448
#define IDH_SuperstructureMember_SetEndRelease                           1520449
#define IDH_SuperstructureMember__EnumElements                           1520450

#define IDH_SuperstructureMembers                                        1520452
#define IDH_SuperstructureMembers_Add                                    1520453
#define IDH_SuperstructureMembers_Clear                                  1520454
#define IDH_SuperstructureMembers_Clone                                  1520455
#define IDH_SuperstructureMembers_CopyTo                                 1520456
#define IDH_SuperstructureMembers_Count                                  1520457
#define IDH_SuperstructureMembers_Insert                                 1520458
#define IDH_SuperstructureMembers_Item                                   1520459
#define IDH_SuperstructureMembers_Length                                 1520460
#define IDH_SuperstructureMembers_MoveTo                                 1520461
#define IDH_SuperstructureMembers_Offset                                 1520462
#define IDH_SuperstructureMembers_OnSuperstructureMemberAdded            1520463
#define IDH_SuperstructureMembers_OnSuperstructureMembersBeforeRemove    1520464
#define IDH_SuperstructureMembers_OnSuperstructureMembersChanged         1520465
#define IDH_SuperstructureMembers_OnSuperstructureMembersCopyTo          1520466
#define IDH_SuperstructureMembers_OnSuperstructureMembersMoveTo          1520467
#define IDH_SuperstructureMembers_OnSuperstructureMembersOffset          1520468
#define IDH_SuperstructureMembers_OnSuperstructureMembersReverse         1520469
#define IDH_SuperstructureMembers_Remove                                 1520470
#define IDH_SuperstructureMembers_Reverse                                1520471
#define IDH_SuperstructureMembers__EnumElements                          1520472

#define IDH_Support                                                      1520474
#define IDH_Support_AddSegment                                           1520475
#define IDH_Support_BottomOffset                                         1520476
#define IDH_Support_Clone                                                1520477
#define IDH_Support_BoundaryCondition                                    1520478
#define IDH_Support_TopRelease                                           1520479
#define IDH_Support_CopySegmentTo                                        1520480
#define IDH_Support_DistributionFactor                                   1520481
#define IDH_Support_GetMemberSegments                                    1520482
#define IDH_Support_GetSegmentForMemberLocation                          1520483
#define IDH_Support_GetSegmentsForStage                                  1520484
#define IDH_Support_InsertSegment                                        1520485
#define IDH_Support_IsSymmetrical                                        1520486
#define IDH_Support_Length                                               1520487
#define IDH_Support_LoadModifier                                         1520488
#define IDH_Support_MoveSegmentTo                                        1520489
#define IDH_Support_OnSupportChanged                                     1520490
#define IDH_Support_RemoveSegment                                        1520491
#define IDH_Support_RemoveStage                                          1520492
#define IDH_Support_ReverseSegments                                      1520493
#define IDH_Support_Segment                                              1520494
#define IDH_Support_SegmentCount                                         1520495
#define IDH_Support_SegmentLength                                        1520496
#define IDH_Support__EnumElements                                        1520497

#define IDH_Supports                                                     1520499
#define IDH_Supports_Add                                                 1520500
#define IDH_Supports_Clear                                               1520501
#define IDH_Supports_Clone                                               1520502
#define IDH_Supports_CopyTo                                              1520503
#define IDH_Supports_Count                                               1520504
#define IDH_Supports_Insert                                              1520505
#define IDH_Supports_Item                                                1520506
#define IDH_Supports_MoveTo                                              1520507
#define IDH_Supports_OnSupportsAdded                                     1520508
#define IDH_Supports_OnSupportsBeforeRemove                              1520509
#define IDH_Supports_OnSupportsChanged                                   1520510
#define IDH_Supports_OnSupportsCopyTo                                    1520511
#define IDH_Supports_OnSupportsMoveTo                                    1520512
#define IDH_Supports_OnSupportsReverse                                   1520513
#define IDH_Supports_Remove                                              1520514
#define IDH_Supports_Reverse                                             1520515
#define IDH_Supports__EnumElements                                       1520516

#define IDH_TemperatureLoad                                              1520518
#define IDH_TemperatureLoad_Clone                                        1520519
#define IDH_TemperatureLoad_MemberID                                     1520520
#define IDH_TemperatureLoad_MemberType                                   1520521
#define IDH_TemperatureLoad_OnTemperatureLoadChanged                     1520522
#define IDH_TemperatureLoad_TBottom                                      1520523
#define IDH_TemperatureLoad_TTop                                         1520524

#define IDH_TemperatureLoads                                             1520526

#define IDH_TemporarySupport                                             1520528
#define IDH_TemporarySupport_AddSegment                                  1520529
#define IDH_TemporarySupport_BottomOffset                                1520530
#define IDH_TemporarySupport_Clone                                       1520531
#define IDH_TemporarySupport_BoundaryCondition                           1520532
#define IDH_TemporarySupport_TopRelease                                  1520533
#define IDH_TemporarySupport_CopySegmentTo                               1520534
#define IDH_TemporarySupport_DistributionFactor                          1520535
#define IDH_TemporarySupport_GetMemberSegments                           1520536
#define IDH_TemporarySupport_GetSegmentForMemberLocation                 1520537
#define IDH_TemporarySupport_GetSegmentsForStage                         1520538
#define IDH_TemporarySupport_ID                                          1520539
#define IDH_TemporarySupport_InsertSegment                               1520540
#define IDH_TemporarySupport_IsSymmetrical                               1520541
#define IDH_TemporarySupport_Length                                      1520542
#define IDH_TemporarySupport_LoadModifier                                1520543
#define IDH_TemporarySupport_Location                                    1520544
#define IDH_TemporarySupport_MoveSegmentTo                               1520545
#define IDH_TemporarySupport_OnTemporarySupportChanged                   1520546
#define IDH_TemporarySupport_RemoveSegment                               1520547
#define IDH_TemporarySupport_RemoveStage                                 1520548
#define IDH_TemporarySupport_ReverseSegments                             1520549
#define IDH_TemporarySupport_Segment                                     1520550
#define IDH_TemporarySupport_SegmentCount                                1520551
#define IDH_TemporarySupport_SegmentLength                               1520552
#define IDH_TemporarySupport_StageRemoved                                1520553
#define IDH_TemporarySupport__EnumElements                               1520554

#define IDH_TemporarySupports                                            1520556
#define IDH_TemporarySupports_Add                                        1520557
#define IDH_TemporarySupports_Clear                                      1520558
#define IDH_TemporarySupports_Clone                                      1520559
#define IDH_TemporarySupports_Count                                      1520560
#define IDH_TemporarySupports_Insert                                     1520561
#define IDH_TemporarySupports_Item                                       1520562
#define IDH_TemporarySupports_OnTemporarySupportsAdded                   1520563
#define IDH_TemporarySupports_OnTemporarySupportsBeforeRemove            1520564
#define IDH_TemporarySupports_OnTemporarySupportsChanged                 1520565
#define IDH_TemporarySupports_Remove                                     1520566
#define IDH_TemporarySupports__EnumElements                              1520567

#define IDH_VehicularLoad                                                1520569
#define IDH_VehicularLoad_Applicability                                  1520570
#define IDH_VehicularLoad_Axles                                          1520571
#define IDH_VehicularLoad_Clone                                          1520572
#define IDH_VehicularLoad_Configuration                                  1520573
#define IDH_VehicularLoad_IMLane                                         1520574
#define IDH_VehicularLoad_IMTruck                                        1520575
#define IDH_VehicularLoad_LaneFactor                                     1520576
#define IDH_VehicularLoad_LaneLoad                                       1520577
#define IDH_VehicularLoad_Name                                           1520578
#define IDH_VehicularLoad_OnVehicularLoadChanged                         1520579
#define IDH_VehicularLoad_SidewalkLoad                                   1520580
#define IDH_VehicularLoad_TruckFactor                                    1520581
#define IDH_VehicularLoad_UseNotional                                    1520582
#define IDH_VehicularLoad_VariableAxle                                   1520583
#define IDH_VehicularLoad_VariableMaxSpacing                             1520584

#define IDH_VehicularLoads                                               1520586
#define IDH_VehicularLoads_Add                                           1520587
#define IDH_VehicularLoads_Clear                                         1520588
#define IDH_VehicularLoads_Clone                                         1520589
#define IDH_VehicularLoads_Count                                         1520590
#define IDH_VehicularLoads_Insert                                        1520591
#define IDH_VehicularLoads_Item                                          1520592
#define IDH_VehicularLoads_OnVehicularLoadsAdded                         1520593
#define IDH_VehicularLoads_OnVehicularLoadsBeforeRemove                  1520594
#define IDH_VehicularLoads_OnVehicularLoadsChanged                       1520595
#define IDH_VehicularLoads_OnVehicularLoadsRenamed                       1520596
#define IDH_VehicularLoads_Remove                                        1520597
#define IDH_VehicularLoads__EnumElements                                 1520598
