///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2017  Washington State Department of Transportation
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

// Help Context IDs
#define IDH_WBFLLOADING                           	                  150000

// Errors
#define IDH_E_STAGE_NOT_EXISTS                                       150001
#define IDH_E_BLANK_NAMES_NOT_ALLOWED                                150002
#define IDH_E_INVALID_INTEGER_ARRAY                                  150003
#define IDH_E_MUST_HAVE_ONE_SPAN                                     150004
#define IDH_E_MUST_HAVE_ONE_SSM                                      150005
#define IDH_E_SPAN_LENGTH_MUST_BE_GT_ZERO                            150006
#define IDH_E_SPAN_LENGTH_EXCEEDS_SUPERSTRUCTUREMEMBERS              150007
#define IDH_E_SSM_LENGTH_MUST_BE_GT_ZERO                             150008
#define IDH_E_TEMPSUPPORT_NOT_EXIST                                  150009
#define IDH_E_SPAN_NOT_EXIST                                         150010
#define IDH_E_SUPPORT_NOT_EXIST                                      150011
#define IDH_E_SSM_NOT_EXIST                                          150012
#define IDH_E_LOCATION_OOR                                           150013
#define IDH_E_SUPPORT_OFFSET_GT_LENGTH                               150014
#define IDH_E_TEMPSUPPORT_OFFSET_GT_LENGTH                           150015
#define IDH_E_INVALID_MEMBERTYPE                                     150016
#define IDH_E_NO_SEGMENTS_FOR_STAGE                                  150017
#define IDH_E_POI_NO_STAGE                                           150018
#define IDH_E_INVALID_POI_MEMBER_TYPE                                150019
#define IDH_E_POI_TEMP_SUPPORT_OOR                                   150020


// Constants
#define IDH_ChangeType                                               151001
#define IDH_MemberReleaseType                                        151002
#define IDH_MemberType                                               151003
#define IDH_BoundaryConditionType                                    151004
#define IDH_Side                                                     151005
#define IDH_LoadOrientation                                          151006
#define IDH_LoadDirection                                            151007
#define IDH_DistributionFactorType                                   151008
#define IDH_VehicularLoadConfigurationType                           151009
#define IDH_LiveLoadApplicabilityType                                151010
#define IDH_LiveLoadModelType                                        151011
#define IDH_TruckDirectionType                                       151012
#define IDH_InZoneType                                               151013
#define IDH_LoadCombinationType                                      151014
#define IDH_ChangeScopeType                                          151015


// Objects
#define IDH_Axle                                                         152000
#define IDH_Axle_Clone                                                   152001
#define IDH_Axle_OnAxleChanged                                           152002
#define IDH_Axle_Spacing                                                 152003
#define IDH_Axle_Weight                                                  152004

#define IDH_Axles                                                        152006
#define IDH_Axles_Add                                                    152007
#define IDH_Axles_Clear                                                  152008
#define IDH_Axles_Clone                                                  152009
#define IDH_Axles_CopyTo                                                 152010
#define IDH_Axles_Count                                                  152011
#define IDH_Axles_Insert                                                 152012
#define IDH_Axles_Item                                                   152013
#define IDH_Axles_MoveTo                                                 152014
#define IDH_Axles_OnAxlesAdded                                           152015
#define IDH_Axles_OnAxlesBeforeRemove                                    152016
#define IDH_Axles_OnAxlesChanged                                         152017
#define IDH_Axles_OnAxlesCopyTo                                          152018
#define IDH_Axles_OnAxlesMoveTo                                          152019
#define IDH_Axles_OnAxlesReverse                                         152020
#define IDH_Axles_Remove                                                 152021
#define IDH_Axles_Reverse                                                152022
#define IDH_Axles__EnumElements                                          152023

#define IDH_CrossSection                                                 152025
#define IDH_CrossSection_Clone                                           152026
#define IDH_CrossSection_Depth                                           152027
#define IDH_CrossSection_EADefl                                          152028
#define IDH_CrossSection_EAForce                                         152029
#define IDH_CrossSection_EIDefl                                          152030
#define IDH_CrossSection_EIForce                                         152031
#define IDH_CrossSection_GetStiffness                                    152032
#define IDH_CrossSection_OnCrossSectionChanged                           152033
#define IDH_CrossSection_SetStiffness                                    152034
#define IDH_CrossSection_StressPoints                                    152035
#define IDH_CrossSection_ThermalCoeff                                    152036

#define IDH_DistributedLoad                                              152038
#define IDH_DistributedLoad_Clone                                        152039
#define IDH_DistributedLoad_Direction                                    152040
#define IDH_DistributedLoad_EndLocation                                  152041
#define IDH_DistributedLoad_MemberID                                     152042
#define IDH_DistributedLoad_MemberType                                   152043
#define IDH_DistributedLoad_OnDistributedLoadChanged                     152044
#define IDH_DistributedLoad_Orientation                                  152045
#define IDH_DistributedLoad_StartLocation                                152046
#define IDH_DistributedLoad_WEnd                                         152047
#define IDH_DistributedLoad_WStart                                       152048

#define IDH_DistributedLoads                                             152050

#define IDH_DistributionFactor                                           152052
#define IDH_DistributionFactor_Clone                                     152053
#define IDH_DistributionFactor_GDMul                                     152054
#define IDH_DistributionFactor_GDSgl                                     152055
#define IDH_DistributionFactor_GetG                                      152056
#define IDH_DistributionFactor_GFat                                      152057
#define IDH_DistributionFactor_GNMMul                                    152058
#define IDH_DistributionFactor_GNMSgl                                    152059
#define IDH_DistributionFactor_GPMMul                                    152060
#define IDH_DistributionFactor_GPMSgl                                    152061
#define IDH_DistributionFactor_GRMul                                     152062
#define IDH_DistributionFactor_GRSgl                                     152063
#define IDH_DistributionFactor_GTMul                                     152064
#define IDH_DistributionFactor_GTSgl                                     152065
#define IDH_DistributionFactor_GVMul                                     152066
#define IDH_DistributionFactor_GVSgl                                     152067
#define IDH_DistributionFactor_OnDistibutionFactorChanged                152068
#define IDH_DistributionFactor_SetG                                      152069

#define IDH_DistributionFactors                                          152071
#define IDH_DistributionFactors_Add                                      152072
#define IDH_DistributionFactors_Clear                                    152073
#define IDH_DistributionFactors_Clone                                    152074
#define IDH_DistributionFactors_CopyTo                                   152075
#define IDH_DistributionFactors_Count                                    152076
#define IDH_DistributionFactors_GetMemberSegments                        152077
#define IDH_DistributionFactors_GetSegmentForLocation                    152078
#define IDH_DistributionFactors_Insert                                   152079
#define IDH_DistributionFactors_IsSymmetrical                            152080
#define IDH_DistributionFactors_Item                                     152081
#define IDH_DistributionFactors_Length                                   152082
#define IDH_DistributionFactors_MoveTo                                   152083
#define IDH_DistributionFactors_OnDistributionFactorsAdded               152084
#define IDH_DistributionFactors_OnDistributionFactorsBeforeRemove        152085
#define IDH_DistributionFactors_OnDistributionFactorsChanged             152086
#define IDH_DistributionFactors_OnDistributionFactorsCopyTo              152087
#define IDH_DistributionFactors_OnDistributionFactorsMoveTo              152088
#define IDH_DistributionFactors_OnDistributionFactorsReverse             152089
#define IDH_DistributionFactors_Remove                                   152090
#define IDH_DistributionFactors_Reverse                                  152091
#define IDH_DistributionFactors__EnumElements                            152092

#define IDH_DistributionFactorSegment                                    152094
#define IDH_DistributionFactorSegment_Clone                              152095
#define IDH_DistributionFactorSegment_DistributionFactor                 152096
#define IDH_DistributionFactorSegment_Length                             152097
#define IDH_DistributionFactorSegment_OnDistributionFactorSegmentChanged 152098

#define IDH_FastEnumerators                                              152100

#define IDH_FilteredDfSegmentCollection                                  152102
#define IDH_FilteredDfSegmentCollection_Count                            152103
#define IDH_FilteredDfSegmentCollection_Item                             152104
#define IDH_FilteredDfSegmentCollection__EnumElements                    152105

#define IDH_FilteredSegmentCollection                                    152107
#define IDH_FilteredSegmentCollection_Count                              152108
#define IDH_FilteredSegmentCollection_Item                               152109
#define IDH_FilteredSegmentCollection__EnumElements                      152110

#define IDH_LiveLoad                                                     152112
#define IDH_LiveLoad_Clear                                               152113
#define IDH_LiveLoad_Clone                                               152114
#define IDH_LiveLoad_Deflection                                          152115
#define IDH_LiveLoad_Design                                              152116
#define IDH_LiveLoad_Fatigue                                             152117
#define IDH_LiveLoad_OnLiveLoadChanged                                   152118
#define IDH_LiveLoad_Pedestrian                                          152119
#define IDH_LiveLoad_Permit                                              152120
#define IDH_LiveLoad_Special                                             152121

#define IDH_LiveLoadModel                                                152123
#define IDH_LiveLoadModel_Clear                                          152124
#define IDH_LiveLoadModel_Clone                                          152125
#define IDH_LiveLoadModel_DistributionFactorType                         152126
#define IDH_LiveLoadModel_Name                                           152127
#define IDH_LiveLoadModel_OnLiveLoadModelChanged                         152128
#define IDH_LiveLoadModel_VehicularLoads                                 152129

#define IDH_LoadCase                                                     152131
#define IDH_LoadCase_AddLoadGroup                                        152132
#define IDH_LoadCase_Clear                                               152133
#define IDH_LoadCase_Clone                                               152134
#define IDH_LoadCase_Description                                         152135
#define IDH_LoadCase_GetLoadGroup                                        152136
#define IDH_LoadCase_ItemData                                            152137
#define IDH_LoadCase_LoadGroupCount                                      152138
#define IDH_LoadCase_Name                                                152139
#define IDH_LoadCase_OnLoadCaseChanged                                   152140
#define IDH_LoadCase_OnLoadCaseRenamed                                   152141
#define IDH_LoadCase_RemoveLoadGroup                                     152142
#define IDH_LoadCase_RemoveLoadGroupByIndex                              152143
#define IDH_LoadCase_SetLoadGroup                                        152144

#define IDH_LoadCases                                                    152146
#define IDH_LoadCases_Add                                                152147
#define IDH_LoadCases_Clear                                              152148
#define IDH_LoadCases_Clone                                              152149
#define IDH_LoadCases_Count                                              152150
#define IDH_LoadCases_Find                                               152151
#define IDH_LoadCases_Insert                                             152152
#define IDH_LoadCases_Item                                               152153
#define IDH_LoadCases_OnLoadCasesAdded                                   152154
#define IDH_LoadCases_OnLoadCasesBeforeRemove                            152155
#define IDH_LoadCases_OnLoadCasesChanged                                 152156
#define IDH_LoadCases_OnLoadCasesRenamed                                 152157
#define IDH_LoadCases_RemoveByIndex                                      152158
#define IDH_LoadCases_RemoveByName                                       152159
#define IDH_LoadCases__EnumElements                                      152160

#define IDH_LoadCombination                                              152162
#define IDH_LoadCombination_AddLoadCaseFactor                            152163
#define IDH_LoadCombination_Clear                                        152164
#define IDH_LoadCombination_Clone                                        152165
#define IDH_LoadCombination_Description                                  152166
#define IDH_LoadCombination_GetLoadCaseFactor                            152167
#define IDH_LoadCombination_ItemData                                     152168
#define IDH_LoadCombination_LiveLoadFactor                               152169
#define IDH_LoadCombination_LiveLoadModel                                152170
#define IDH_LoadCombination_LoadCaseFactorCount                          152171
#define IDH_LoadCombination_LoadCombinationType                          152172
#define IDH_LoadCombination_Name                                         152173
#define IDH_LoadCombination_OnLoadCombinationChanged                     152174
#define IDH_LoadCombination_OnLoadCombinationRenamed                     152175
#define IDH_LoadCombination_RemoveLoadCaseFactor                         152176
#define IDH_LoadCombination_SetLoadCaseFactor                            152177

#define IDH_LoadCombinations                                             152179
#define IDH_LoadCombinations_Add                                         152180
#define IDH_LoadCombinations_Clear                                       152181
#define IDH_LoadCombinations_Clone                                       152182
#define IDH_LoadCombinations_Count                                       152183
#define IDH_LoadCombinations_Find                                        152184
#define IDH_LoadCombinations_Insert                                      152185
#define IDH_LoadCombinations_Item                                        152186
#define IDH_LoadCombinations_OnLoadCombinationsAdded                     152187
#define IDH_LoadCombinations_OnLoadCombinationsBeforeRemove              152188
#define IDH_LoadCombinations_OnLoadCombinationsChanged                   152189
#define IDH_LoadCombinations_OnLoadCombinationsRenamed                   152190
#define IDH_LoadCombinations_RemoveByIndex                               152191
#define IDH_LoadCombinations_RemoveByName                                152192
#define IDH_LoadCombinations__EnumElements                               152193

#define IDH_LoadGroup                                                    152195
#define IDH_LoadGroup_Clone                                              152196
#define IDH_LoadGroup_Description                                        152197
#define IDH_LoadGroup_Name                                               152198
#define IDH_LoadGroup_OnLoadGroupChanged                                 152199
#define IDH_LoadGroup_OnLoadGroupRenamed                                 152200
#define IDH_LoadGroup_Transient                                          152201

#define IDH_LoadGroups                                                   152203
#define IDH_LoadGroups_Add                                               152204
#define IDH_LoadGroups_Clear                                             152205
#define IDH_LoadGroups_Clone                                             152206
#define IDH_LoadGroups_Count                                             152207
#define IDH_LoadGroups_Find                                              152208
#define IDH_LoadGroups_Insert                                            152209
#define IDH_LoadGroups_Item                                              152210
#define IDH_LoadGroups_OnLoadGroupsAdded                                 152211
#define IDH_LoadGroups_OnLoadGroupsBeforeRemove                          152212
#define IDH_LoadGroups_OnLoadGroupsChanged                               152213
#define IDH_LoadGroups_OnLoadGroupsRenamed                               152214
#define IDH_LoadGroups_RemoveByIndex                                     152215
#define IDH_LoadGroups_RemoveByName                                      152216
#define IDH_LoadGroups__EnumElements                                     152217

#define IDH_LoadItem                                                     152219
#define IDH_LoadItem_ID                                                  152220
#define IDH_LoadItem_Load                                                152221
#define IDH_LoadItem_LoadGroup                                           152222
#define IDH_LoadItem_Stage                                               152223

#define IDH_Load_Collections                                             152225
#define IDH_Load_Collections_Add                                         152226
#define IDH_Load_Collections_Clear                                       152227
#define IDH_Load_Collections_Clone                                       152228
#define IDH_Load_Collections_Count                                       152229
#define IDH_Load_Collections_FilterByStageGroup                          152230
#define IDH_Load_Collections_Find                                        152231
#define IDH_Load_Collections_Item                                        152232
#define IDH_Load_Collections_Load                                        152233
#define IDH_Load_Collections_OnLoadsAdded                                152234
#define IDH_Load_Collections_OnLoadsBeforeRemove                         152235
#define IDH_Load_Collections_OnLoadsChanged                              152236
#define IDH_Load_Collections_RemoveByID                                  152237
#define IDH_Load_Collections_RemoveByIndex                               152238
#define IDH_Load_Collections_RemoveStage                                 152239
#define IDH_Load_Collections__EnumElements                               152240

#define IDH_Model                                                        152242
#define IDH_Model_Clear                                                  152243
#define IDH_Model_Clone                                                  152244
#define IDH_Model_ComputeLocation                                        152245
#define IDH_Model_DistributedLoads                                       152246
#define IDH_Model_DistributionFactors                                    152247
#define IDH_Model_LeftSpan                                               152248
#define IDH_Model_LeftSupport                                            152249
#define IDH_Model_LiveLoad                                               152250
#define IDH_Model_LoadCases                                              152251
#define IDH_Model_LoadCombinations                                       152252
#define IDH_Model_LoadGroups                                             152253
#define IDH_Model_OnModelChanged                                         152254
#define IDH_Model_PointLoads                                             152255
#define IDH_Model_POIs                                                   152256
#define IDH_Model_RemoveStage                                            152257
#define IDH_Model_RightSpan                                              152258
#define IDH_Model_RightSupport                                           152259
#define IDH_Model_SettlementLoads                                        152260
#define IDH_Model_Spans                                                  152261
#define IDH_Model_Stages                                                 152262
#define IDH_Model_StrainLoads                                            152263
#define IDH_Model_SuperstructureMembers                                  152264
#define IDH_Model_Supports                                               152265
#define IDH_Model_TemperatureLoads                                       152266

#define IDH_POI                                                          152268
#define IDH_POI_Clone                                                    152269
#define IDH_POI_ID                                                       152270
#define IDH_POI_Location                                                 152271
#define IDH_POI_MemberID                                                 152272
#define IDH_POI_MemberType                                               152273
#define IDH_POI_OnPOIChanged                                             152274
#define IDH_POI_OnPOIRenamed                                             152275
#define IDH_POI_POIStressPoints                                          152276

#define IDH_PointLoad                                                    152278
#define IDH_PointLoad_Clone                                              152279
#define IDH_PointLoad_Fx                                                 152280
#define IDH_PointLoad_Fy                                                 152281
#define IDH_PointLoad_GetForce                                           152282
#define IDH_PointLoad_Location                                           152283
#define IDH_PointLoad_MemberID                                           152284
#define IDH_PointLoad_MemberType                                         152285
#define IDH_PointLoad_Mz                                                 152286
#define IDH_PointLoad_OnPointLoadChanged                                 152287
#define IDH_PointLoad_SetForce                                           152288

#define IDH_PointLoads                                                   152290

#define IDH_POIs                                                         152292
#define IDH_POIs_Add                                                     152293
#define IDH_POIs_Clear                                                   152294
#define IDH_POIs_Clone                                                   152295
#define IDH_POIs_Count                                                   152296
#define IDH_POIs_Find                                                    152297
#define IDH_POIs_Item                                                    152298
#define IDH_POIs_OnPOIsAdded                                             152299
#define IDH_POIs_OnPOIsBeforeRemove                                      152300
#define IDH_POIs_OnPOIsChanged                                           152301
#define IDH_POIs_OnPOIsRenamed                                           152302
#define IDH_POIs_RemoveByID                                              152303
#define IDH_POIs_RemoveByIndex                                           152304
#define IDH_POIs__EnumElements                                           152305

#define IDH_POIStressPoints                                              152307
#define IDH_POIStressPoints_Clear                                        152308
#define IDH_POIStressPoints_Clone                                        152309
#define IDH_POIStressPoints_Count                                        152310
#define IDH_POIStressPoints_Insert                                       152311
#define IDH_POIStressPoints_Item                                         152312
#define IDH_POIStressPoints_OnPOIStressPointsAdded                       152313
#define IDH_POIStressPoints_OnPOIStressPointsBeforeRemove                152314
#define IDH_POIStressPoints_OnPOIStressPointsChanged                     152315
#define IDH_POIStressPoints_Remove                                       152316
#define IDH_POIStressPoints__EnumElements                                152317

#define IDH_POIStressPointsItem                                          152319
#define IDH_POIStressPointsItem_LeftStressPoints                         152320
#define IDH_POIStressPointsItem_RightStressPoints                        152321
#define IDH_POIStressPointsItem_Stage                                    152322

#define IDH_Segment                                                      152324
#define IDH_Segment_Clone                                                152325
#define IDH_Segment_CrossSection                                         152326
#define IDH_Segment_Length                                               152327
#define IDH_Segment_OnSegmentChanged                                     152328

#define IDH_SegmentItem                                                  152330
#define IDH_SegmentItem_Clone                                            152331
#define IDH_SegmentItem_OnSegmentItemChanged                             152332
#define IDH_SegmentItem_RelPosition                                      152333
#define IDH_SegmentItem_Segment                                          152334
#define IDH_SegmentItem_Stage                                            152335

#define IDH_SettlementLoad                                               152337
#define IDH_SettlementLoad_Clone                                         152338
#define IDH_SettlementLoad_Dx                                            152339
#define IDH_SettlementLoad_Dy                                            152340
#define IDH_SettlementLoad_MemberID                                      152341
#define IDH_SettlementLoad_OnSettlementLoadChanged                       152342
#define IDH_SettlementLoad_Rz                                            152343

#define IDH_SettlementLoads                                              152345

#define IDH_Span                                                         152347
#define IDH_Span_Clone                                                   152348
#define IDH_Span_Length                                                  152349
#define IDH_Span_LoadModifier                                            152350
#define IDH_Span_OnSpanChanged                                           152351
#define IDH_Span_RemoveStage                                             152352
#define IDH_Span_TemporarySupports                                       152353

#define IDH_Spans                                                        152355
#define IDH_Spans_Add                                                    152356
#define IDH_Spans_Clear                                                  152357
#define IDH_Spans_Clone                                                  152358
#define IDH_Spans_CopyTo                                                 152359
#define IDH_Spans_Count                                                  152360
#define IDH_Spans_Insert                                                 152361
#define IDH_Spans_Item                                                   152362
#define IDH_Spans_Length                                                 152363
#define IDH_Spans_MoveTo                                                 152364
#define IDH_Spans_OnSpansAdded                                           152365
#define IDH_Spans_OnSpansBeforeRemove                                    152366
#define IDH_Spans_OnSpansChanged                                         152367
#define IDH_Spans_OnSpansCopyTo                                          152368
#define IDH_Spans_OnSpansMoveTo                                          152369
#define IDH_Spans_OnSpansReverse                                         152370
#define IDH_Spans_Remove                                                 152371
#define IDH_Spans_Reverse                                                152372
#define IDH_Spans__EnumElements                                          152373

#define IDH_Stage                                                        152375
#define IDH_Stage_Clone                                                  152376
#define IDH_Stage_Description                                            152377
#define IDH_Stage_Name                                                   152378
#define IDH_Stage_OnStageChanged                                         152379

#define IDH_Stages                                                       152381
#define IDH_Stages_Add                                                   152382
#define IDH_Stages_Clear                                                 152383
#define IDH_Stages_Clone                                                 152384
#define IDH_Stages_Count                                                 152385
#define IDH_Stages_FindIndex                                             152386
#define IDH_Stages_Insert                                                152387
#define IDH_Stages_Item                                                  152388
#define IDH_Stages_MoveTo                                                152389
#define IDH_Stages_OnStagesAdded                                         152390
#define IDH_Stages_OnStagesBeforeRemove                                  152391
#define IDH_Stages_OnStagesChanged                                       152392
#define IDH_Stages_OnStagesCopyTo                                        152393
#define IDH_Stages_OnStagesMoveTo                                        152394
#define IDH_Stages_OnStagesReverse                                       152395
#define IDH_Stages_RemoveByIndex                                         152396
#define IDH_Stages_RemoveByName                                          152397
#define IDH_Stages_Reverse                                               152398
#define IDH_Stages__EnumElements                                         152399

#define IDH_StrainLoad                                                   152401
#define IDH_StrainLoad_AxialStrain                                       152402
#define IDH_StrainLoad_Clone                                             152403
#define IDH_StrainLoad_CurvatureStrain                                   152404
#define IDH_StrainLoad_MemberID                                          152405
#define IDH_StrainLoad_MemberType                                        152406
#define IDH_StrainLoad_OnStrainLoadChanged                               152407

#define IDH_StrainLoads                                                  152409

#define IDH_StressPoint                                                  152411
#define IDH_StressPoint_Clone                                            152412
#define IDH_StressPoint_OnStressPointChanged                             152413
#define IDH_StressPoint_Sa                                               152414
#define IDH_StressPoint_Sm                                               152415

#define IDH_StressPoints                                                 152417
#define IDH_StressPoints_Add                                             152418
#define IDH_StressPoints_Clear                                           152419
#define IDH_StressPoints_Clone                                           152420
#define IDH_StressPoints_Count                                           152421
#define IDH_StressPoints_Insert                                          152422
#define IDH_StressPoints_Item                                            152423
#define IDH_StressPoints_OnStressPointsAdded                             152424
#define IDH_StressPoints_OnStressPointsChanged                           152425
#define IDH_StressPoints_OnStressPointsRemoved                           152426
#define IDH_StressPoints_Remove                                          152427
#define IDH_StressPoints__EnumElements                                   152428

#define IDH_SuperstructureMember                                         152430
#define IDH_SuperstructureMember_AddSegment                              152431
#define IDH_SuperstructureMember_Clone                                   152432
#define IDH_SuperstructureMember_CopySegmentTo                           152433
#define IDH_SuperstructureMember_GetEndRelease                           152434
#define IDH_SuperstructureMember_GetMemberSegments                       152435
#define IDH_SuperstructureMember_GetSegmentForMemberLocation             152436
#define IDH_SuperstructureMember_GetSegmentsForStage                     152437
#define IDH_SuperstructureMember_InsertSegment                           152438
#define IDH_SuperstructureMember_IsSymmetrical                           152439
#define IDH_SuperstructureMember_Length                                  152440
#define IDH_SuperstructureMember_MoveSegmentTo                           152441
#define IDH_SuperstructureMember_OnSuperstructureMemberChanged           152442
#define IDH_SuperstructureMember_RemoveSegment                           152443
#define IDH_SuperstructureMember_RemoveStage                             152444
#define IDH_SuperstructureMember_ReverseSegments                         152445
#define IDH_SuperstructureMember_Segment                                 152446
#define IDH_SuperstructureMember_SegmentCount                            152447
#define IDH_SuperstructureMember_SegmentLength                           152448
#define IDH_SuperstructureMember_SetEndRelease                           152449
#define IDH_SuperstructureMember__EnumElements                           152450

#define IDH_SuperstructureMembers                                        152452
#define IDH_SuperstructureMembers_Add                                    152453
#define IDH_SuperstructureMembers_Clear                                  152454
#define IDH_SuperstructureMembers_Clone                                  152455
#define IDH_SuperstructureMembers_CopyTo                                 152456
#define IDH_SuperstructureMembers_Count                                  152457
#define IDH_SuperstructureMembers_Insert                                 152458
#define IDH_SuperstructureMembers_Item                                   152459
#define IDH_SuperstructureMembers_Length                                 152460
#define IDH_SuperstructureMembers_MoveTo                                 152461
#define IDH_SuperstructureMembers_Offset                                 152462
#define IDH_SuperstructureMembers_OnSuperstructureMemberAdded            152463
#define IDH_SuperstructureMembers_OnSuperstructureMembersBeforeRemove    152464
#define IDH_SuperstructureMembers_OnSuperstructureMembersChanged         152465
#define IDH_SuperstructureMembers_OnSuperstructureMembersCopyTo          152466
#define IDH_SuperstructureMembers_OnSuperstructureMembersMoveTo          152467
#define IDH_SuperstructureMembers_OnSuperstructureMembersOffset          152468
#define IDH_SuperstructureMembers_OnSuperstructureMembersReverse         152469
#define IDH_SuperstructureMembers_Remove                                 152470
#define IDH_SuperstructureMembers_Reverse                                152471
#define IDH_SuperstructureMembers__EnumElements                          152472

#define IDH_Support                                                      152474
#define IDH_Support_AddSegment                                           152475
#define IDH_Support_BottomOffset                                         152476
#define IDH_Support_Clone                                                152477
#define IDH_Support_BoundaryCondition                                    152478
#define IDH_Support_TopRelease                                           152479
#define IDH_Support_CopySegmentTo                                        152480
#define IDH_Support_DistributionFactor                                   152481
#define IDH_Support_GetMemberSegments                                    152482
#define IDH_Support_GetSegmentForMemberLocation                          152483
#define IDH_Support_GetSegmentsForStage                                  152484
#define IDH_Support_InsertSegment                                        152485
#define IDH_Support_IsSymmetrical                                        152486
#define IDH_Support_Length                                               152487
#define IDH_Support_LoadModifier                                         152488
#define IDH_Support_MoveSegmentTo                                        152489
#define IDH_Support_OnSupportChanged                                     152490
#define IDH_Support_RemoveSegment                                        152491
#define IDH_Support_RemoveStage                                          152492
#define IDH_Support_ReverseSegments                                      152493
#define IDH_Support_Segment                                              152494
#define IDH_Support_SegmentCount                                         152495
#define IDH_Support_SegmentLength                                        152496
#define IDH_Support__EnumElements                                        152497

#define IDH_Supports                                                     152499
#define IDH_Supports_Add                                                 152500
#define IDH_Supports_Clear                                               152501
#define IDH_Supports_Clone                                               152502
#define IDH_Supports_CopyTo                                              152503
#define IDH_Supports_Count                                               152504
#define IDH_Supports_Insert                                              152505
#define IDH_Supports_Item                                                152506
#define IDH_Supports_MoveTo                                              152507
#define IDH_Supports_OnSupportsAdded                                     152508
#define IDH_Supports_OnSupportsBeforeRemove                              152509
#define IDH_Supports_OnSupportsChanged                                   152510
#define IDH_Supports_OnSupportsCopyTo                                    152511
#define IDH_Supports_OnSupportsMoveTo                                    152512
#define IDH_Supports_OnSupportsReverse                                   152513
#define IDH_Supports_Remove                                              152514
#define IDH_Supports_Reverse                                             152515
#define IDH_Supports__EnumElements                                       152516

#define IDH_TemperatureLoad                                              152518
#define IDH_TemperatureLoad_Clone                                        152519
#define IDH_TemperatureLoad_MemberID                                     152520
#define IDH_TemperatureLoad_MemberType                                   152521
#define IDH_TemperatureLoad_OnTemperatureLoadChanged                     152522
#define IDH_TemperatureLoad_TBottom                                      152523
#define IDH_TemperatureLoad_TTop                                         152524

#define IDH_TemperatureLoads                                             152526

#define IDH_TemporarySupport                                             152528
#define IDH_TemporarySupport_AddSegment                                  152529
#define IDH_TemporarySupport_BottomOffset                                152530
#define IDH_TemporarySupport_Clone                                       152531
#define IDH_TemporarySupport_BoundaryCondition                           152532
#define IDH_TemporarySupport_TopRelease                                  152533
#define IDH_TemporarySupport_CopySegmentTo                               152534
#define IDH_TemporarySupport_DistributionFactor                          152535
#define IDH_TemporarySupport_GetMemberSegments                           152536
#define IDH_TemporarySupport_GetSegmentForMemberLocation                 152537
#define IDH_TemporarySupport_GetSegmentsForStage                         152538
#define IDH_TemporarySupport_ID                                          152539
#define IDH_TemporarySupport_InsertSegment                               152540
#define IDH_TemporarySupport_IsSymmetrical                               152541
#define IDH_TemporarySupport_Length                                      152542
#define IDH_TemporarySupport_LoadModifier                                152543
#define IDH_TemporarySupport_Location                                    152544
#define IDH_TemporarySupport_MoveSegmentTo                               152545
#define IDH_TemporarySupport_OnTemporarySupportChanged                   152546
#define IDH_TemporarySupport_RemoveSegment                               152547
#define IDH_TemporarySupport_RemoveStage                                 152548
#define IDH_TemporarySupport_ReverseSegments                             152549
#define IDH_TemporarySupport_Segment                                     152550
#define IDH_TemporarySupport_SegmentCount                                152551
#define IDH_TemporarySupport_SegmentLength                               152552
#define IDH_TemporarySupport_StageRemoved                                152553
#define IDH_TemporarySupport__EnumElements                               152554

#define IDH_TemporarySupports                                            152556
#define IDH_TemporarySupports_Add                                        152557
#define IDH_TemporarySupports_Clear                                      152558
#define IDH_TemporarySupports_Clone                                      152559
#define IDH_TemporarySupports_Count                                      152560
#define IDH_TemporarySupports_Insert                                     152561
#define IDH_TemporarySupports_Item                                       152562
#define IDH_TemporarySupports_OnTemporarySupportsAdded                   152563
#define IDH_TemporarySupports_OnTemporarySupportsBeforeRemove            152564
#define IDH_TemporarySupports_OnTemporarySupportsChanged                 152565
#define IDH_TemporarySupports_Remove                                     152566
#define IDH_TemporarySupports__EnumElements                              152567

#define IDH_VehicularLoad                                                152569
#define IDH_VehicularLoad_Applicability                                  152570
#define IDH_VehicularLoad_Axles                                          152571
#define IDH_VehicularLoad_Clone                                          152572
#define IDH_VehicularLoad_Configuration                                  152573
#define IDH_VehicularLoad_IMLane                                         152574
#define IDH_VehicularLoad_IMTruck                                        152575
#define IDH_VehicularLoad_LaneFactor                                     152576
#define IDH_VehicularLoad_LaneLoad                                       152577
#define IDH_VehicularLoad_Name                                           152578
#define IDH_VehicularLoad_OnVehicularLoadChanged                         152579
#define IDH_VehicularLoad_SidewalkLoad                                   152580
#define IDH_VehicularLoad_TruckFactor                                    152581
#define IDH_VehicularLoad_UseNotional                                    152582
#define IDH_VehicularLoad_VariableAxle                                   152583
#define IDH_VehicularLoad_VariableMaxSpacing                             152584

#define IDH_VehicularLoads                                               152586
#define IDH_VehicularLoads_Add                                           152587
#define IDH_VehicularLoads_Clear                                         152588
#define IDH_VehicularLoads_Clone                                         152589
#define IDH_VehicularLoads_Count                                         152590
#define IDH_VehicularLoads_Insert                                        152591
#define IDH_VehicularLoads_Item                                          152592
#define IDH_VehicularLoads_OnVehicularLoadsAdded                         152593
#define IDH_VehicularLoads_OnVehicularLoadsBeforeRemove                  152594
#define IDH_VehicularLoads_OnVehicularLoadsChanged                       152595
#define IDH_VehicularLoads_OnVehicularLoadsRenamed                       152596
#define IDH_VehicularLoads_Remove                                        152597
#define IDH_VehicularLoads__EnumElements                                 152598
