///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
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
// 4500 3rd Ave SE, P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_RCCAPACITY_HH_
#define INCLUDED_RCCAPACITY_HH_

#define IDH_TransvReinforcementType			400
#define IDH_SolutionMethod					401
#define IDH_StrandGradeType					402
#define IDH_ProductionMethodType			403

#define IDH_IRCBeam                       500
#define IDH_IRCBeam_b                     501
#define IDH_IRCBeam_bw                    502
#define IDH_IRCBeam_hf                    503
#define IDH_IRCBeam_h                     504
#define IDH_IRCBeam_As                    505
#define IDH_IRCBeam_Aps                   506
#define IDH_IRCBeam_ds                    507  
#define IDH_IRCBeam_dps                   508
#define IDH_IRCBeam_fy                    509
#define IDH_IRCBeam_fpu                   510
#define IDH_IRCBeam_fpy                   511
#define IDH_IRCBeam_fpe                   512
#define IDH_IRCBeam_FcSlab                513
#define IDH_IRCBeam_FcBeam                514
#define IDH_IRCBeam_Es                    515
#define IDH_IRCBeam_Eps                   516
   
#define IDH_IRCBeam2                      600
#define IDH_IRCBeam2_b                    601
#define IDH_IRCBeam2_bw                   602
#define IDH_IRCBeam2_hf                   603
#define IDH_IRCBeam2_h                    604
#define IDH_IRCBeam2_AddRebarLayer        605
#define IDH_IRCBeam2_RebarLayerCount      606
#define IDH_IRCBeam2_RebarLayerDepth      607
#define IDH_IRCBeam2_RebarLayerSteel      608
#define IDH_IRCBeam2_RebarLayerDevFactor  609
#define IDH_IRCBeam2_GetRebarLayer        610
#define IDH_IRCBeam2_RemoveRebarLayer     611
#define IDH_IRCBeam2_ClearRebarLayers     612
#define IDH_IRCBeam2_AddStrandLayer       613
#define IDH_IRCBeam2_StrandLayerCount     614
#define IDH_IRCBeam2_StrandLayerDepth     615
#define IDH_IRCBeam2_StrandLayerSteel     616
#define IDH_IRCBeam2_StrandLayerDevFactor 617
#define IDH_IRCBeam2_GetStrandLayer       618
#define IDH_IRCBeam2_RemoveStrandLayer    619
#define IDH_IRCBeam2_ClearStrandLayers    620
#define IDH_IRCBeam2_fy                   621
#define IDH_IRCBeam2_fpu                  622
#define IDH_IRCBeam2_fpy                  623
#define IDH_IRCBeam2_fpe                  624
#define IDH_IRCBeam2_FcSlab               625
#define IDH_IRCBeam2_FcBeam               626
#define IDH_IRCBeam2_Es                   627
#define IDH_IRCBeam2_Eps                  628

#define IDH_IRCBeam2Ex                       650
#define IDH_IRCBeam2Ex_b                     651
#define IDH_IRCBeam2Ex_hf                    652
#define IDH_IRCBeam2Ex_Beam                  653
#define IDH_IRCBeam2Ex_AddRebarLayer         654
#define IDH_IRCBeam2Ex_RebarLayerCount       655
#define IDH_IRCBeam2Ex_RebarLayerDepth       656
#define IDH_IRCBeam2Ex_RebarLayerSteel       657
#define IDH_IRCBeam2Ex_RebarLayerDevFactor   658
#define IDH_IRCBeam2Ex_GetRebarLayer         659
#define IDH_IRCBeam2Ex_RemoveRebarLayer      660
#define IDH_IRCBeam2Ex_ClearRebarLayers      661
#define IDH_IRCBeam2Ex_AddStrandLayer        662
#define IDH_IRCBeam2Ex_StrandLayerCount      663
#define IDH_IRCBeam2Ex_StrandLayerDepth      664
#define IDH_IRCBeam2Ex_StrandLayerSteel      665
#define IDH_IRCBeam2Ex_StrandLayerDevFactor  666
#define IDH_IRCBeam2Ex_GetStrandLayer        667
#define IDH_IRCBeam2Ex_RemoveStrandLayer     668
#define IDH_IRCBeam2Ex_ClearStrandLayers     669
#define IDH_IRCBeam2Ex_fy                    670
#define IDH_IRCBeam2Ex_fpu                   671
#define IDH_IRCBeam2Ex_fpy                   672
#define IDH_IRCBeam2Ex_fpe                   673
#define IDH_IRCBeam2Ex_FcSlab                674
#define IDH_IRCBeam2Ex_FcBeam                675
#define IDH_IRCBeam2Ex_Es                    676
#define IDH_IRCBeam2Ex_Eps                   677

#define IDH_IRCSolution                   700
#define IDH_IRCSolution_InitSolution      701
#define IDH_IRCSolution_Mn                702
#define IDH_IRCSolution_IsOverReinforced  703
#define IDH_IRCSolution_NeutralAxisDepth  704
#define IDH_IRCSolution_fps               705
#define IDH_IRCSolution_Cflange           706
#define IDH_IRCSolution_Cweb              707
#define IDH_IRCSolution_T                 708
#define IDH_IRCSolution_Yflange           709
#define IDH_IRCSolution_Yweb              710

#define IDH_IRCSolutionEx                  750
#define IDH_IRCSolutionEx_InitSolution     751
#define IDH_IRCSolutionEx_Mn               752
#define IDH_IRCSolutionEx_NeutralAxisDepth 753
#define IDH_IRCSolutionEx_fs               754
#define IDH_IRCSolutionEx_fps              755
#define IDH_IRCSolutionEx_Cflange          756
#define IDH_IRCSolutionEx_Cweb             757
#define IDH_IRCSolutionEx_T                758
#define IDH_IRCSolutionEx_Yflange          759
#define IDH_IRCSolutionEx_Yweb             760

#define IDH_IRCSolver                     800
#define IDH_IRCSolver_Solve               801

#define IDH_IRCSolver2                    810
#define IDH_IRCSolver2_Solver             811

#define IDH_IRCSolver2Ex                  815
#define IDH_IRCSolver2Ex_Solver           816

#define IDH_IPCISolver                    820
#define IDH_IPCISolver_Tolerance          821
#define IDH_IPCISolver_StrandModel        822
#define IDH_IPCISolver_RebarModel         823
#define IDH_IPCISolver_UnitMode           824
#define IDH_IPCISolver_IsCflangeOverhangOnly 825

#define IDH_INLSolver                     830
#define IDH_INLSolver_Slices              831
#define IDH_INLSolver_Tolerance           832
#define IDH_INLSolver_SlabConcreteModel   833
#define IDH_INLSolver_BeamConcreteModel   834
#define IDH_INLSolver_StrandModel         835
#define IDH_INLSolver_RebarModel          836
#define IDH_INLSolver_IsCflangeOverhangOnly 837
#define IDH_INLSolver_ConcreteCrushingStrain 838
#define IDH_INLSolver_AxialForce			839

#define IDH_ILRFDSolver                   840
#define IDH_ILRFDSolver_UnitMode          841
#define IDH_ILRFDSolver_IsCflangeOverhangOnly 842

#define IDH_ILFDSolver                    850
#define IDH_ILFDSolver_UnitMode           851
#define IDH_ILFDSolver_IsCflangeOverhangOnly 852

#define IDH_ILRFDSolver2                  860
#define IDH_ILRFDSolver2_Tolerance          861
#define IDH_ILRFDSolver2_StrandModel        862
#define IDH_ILRFDSolver2_RebarModel         863
#define IDH_ILRFDSolver2_UnitMode           864
#define IDH_ILRFDSolver2_IsCflangeOverhangOnly 865

#define IDH_IStressStrain                 900
#define IDH_IStressStrain_ComputeStress   901
#define	IDH_IStressStrain_StrainLimits	  902
#define IDH_IStressStrain_ModulusOfElasticity 903
#define IDH_IStressStrain_YieldStrain     904
#define IDH_IStressStrain_Name            905
#define IDH_IStressStrain_StrainAtPeakStress 906


#define IDH_IUnconfinedConcrete           910
#define IDH_IUnconfinedConcrete_fc        911

#define IDH_IPSPowerFormula               920
#define IDH_IPSPowerFormula_fpu           921

#define IDH_IRebarModel                   930
#define IDH_IRebarModel_Init              931
#define IDH_IRebarModel_fy                932
#define IDH_IRebarModel_Es                933
#define IDH_IRebarModel_MaxStrain		  934

#define IDH_IPCISolution                  940
#define IDH_IPCISolution_InitSolution     941
#define IDH_IPCISolution_AvgBeta1         942

#define IDH_IPCISolutionEx                944
#define IDH_IPCISolutionEx_InitSolution   945
#define IDH_IPCISolutionEx_AvgBeta1       946

#define IDH_IMixedSolver                  950
#define IDH_IMixedSolver_UnitMode         951
#define IDH_IMixedSolver_IsCflangeOverhangOnly 952

#define IDH_IStrainHardenedRebarModel		1000
#define IDH_IStrainHardenedRebarModel_Init	1001
#define IDH_IStrainHardenedRebarModel_fy	1002
#define IDH_IStrainHardenedRebarModel_fu	1003
#define IDH_IStrainHardenedRebarModel_Es	1004
#define IDH_IStrainHardenedRebarModel_esh	1005
#define IDH_IStrainHardenedRebarModel_efr	1006

#define IDH_IRoundColumn								1100
#define IDH_IRoundColumn_Diameter						1101
#define IDH_IRoundColumn_Cover							1102
#define IDH_IRoundColumn_As								1103
#define IDH_IRoundColumn_fc								1104
#define IDH_IRoundColumn_fy								1105
#define IDH_IRoundColumn_Es								1106
#define IDH_IRoundColumn_ComputerInteractionSurface		1107

#define IDH_IGeneralSection								1200
#define IDH_IGeneralSection_AddShape					1201
#define IDH_IGeneralSection_ShapeCount					1202
#define IDH_IGeneralSection_Shape						1203
#define IDH_IGeneralSection_ForegroundMaterial			1204
#define IDH_IGeneralSection_BackgroundMaterial			1205
#define IDH_IGeneralSection_InitialStrain				1206

#define IDH_IGeneralSectionSolution						1220
#define IDH_IGeneralSectionSolution_InitSolution		1221
#define IDH_IGeneralSectionSolution_NeutralAxis			1222
#define IDH_IGeneralSectionSolution_Fz					1223
#define IDH_IGeneralSectionSolution_Mx					1224
#define IDH_IGeneralSectionSolution_My					1225
#define IDH_IGeneralSectionSolution_CompressionResultant	1226
#define IDH_IGeneralSectionSolution_TensionResultant	1227
#define IDH_IGeneralSectionSolution_CompressionResultantLocation	1228
#define IDH_IGeneralSectionSolution_TensionResultantLocation	1229
#define IDH_IGeneralSectionSolution_SliceCount	1230
#define IDH_IGeneralSectionSolution_Slice	1231
#define IDH_IGeneralSectionSolution_AddSlice 1232
#define IDH_IGeneralSectionSolution_NeutralAxisDirection	1233

#define IDH_IGeneralSectionSlice			1240
#define IDH_IGeneralSectionSlice_InitSlice	1241
#define IDH_IGeneralSectionSlice_Area		1242
#define IDH_IGeneralSectionSlice_CG			1243
#define IDH_IGeneralSectionSlice_Strain		1244
#define IDH_IGeneralSectionSlice_ForegroundStress	1245
#define IDH_IGeneralSectionSlice_BackgroundStress	1246
#define IDH_IGeneralSectionSlice_Shape					1247
#define IDH_IGeneralSectionSlice_ForegroundMaterial	1248
#define IDH_IGeneralSectionSlice_BackgroundMaterial	1249

#define IDH_IGeneralSectionSolver						1250
#define IDH_IGeneralSectionSolver_Section				1251
#define IDH_IGeneralSectionSolver_Slices				1252
#define IDH_IGeneralSectionSolver_SliceGrowthFactor 1253
#define IDH_IGeneralSectionSolver_Solve					1254

#define IDH_IMomentCurvatureSolution					1300
#define IDH_IMomentCurvatureSolution_MaxMoment			1301
#define IDH_IMomentCurvatureSolution_MaxMomentCurvature 1302
#define IDH_IMomentCurvatureSolution_Moment				1303
#define IDH_IMomentCurvatureSolution_Curvature			1304
#define IDH_IMomentCurvatureSolution_StrainPlane		1305
#define IDH_IMomentCurvatureSolution_PointCount			1306
#define IDH_IMomentCurvatureSolution_PeakCapacity       1307

#define IDH_IMomentCurvatureSolver      				1350
#define IDH_IMomentCurvatureSolver_Section				1351
#define IDH_IMomentCurvatureSolver_Slices			    1352
#define IDH_IMomentCurvatureSolver_AxialTolerance	    1353
#define IDH_IMomentCurvatureSolver_MaxIterations			1354
#define IDH_IMomentCurvatureSolver_InitialCurvatureStep 1355
#define IDH_IMomentCurvatureSolver_Solve				1356

#define IDH_IMomentCapacitySolver						1400
#define IDH_IMomentCapacitySolver_Slices			    1401
#define IDH_IMomentCapacitySolver_SliceGrowthFactor 1402
#define IDH_IMomentCapacitySolver_Section				1403
#define IDH_IMomentCapacitySolver_Solve 				1404
#define IDH_IMomentCapacitySolver_PlasticCentroid       1405
#define IDH_IMomentCapacitySolver_CompressionLimit      1406
#define IDH_IMomentCapacitySolver_TensionLimit          1407
#define IDH_IMomentCapacitySolver_AxialTolerance	    1408
#define IDH_IMomentCapacitySolver_MaxIterations			1409

#define IDH_IMomentCapacitySolution						1420
#define IDH_IMomentCapacitySolution_InitSolution		1421
#define IDH_IMomentCapacitySolution_Fz					1422
#define IDH_IMomentCapacitySolution_Mx					1423
#define IDH_IMomentCapacitySolution_My					1424
#define IDH_IMomentCapacitySolution_StrainPlane			1425
#define IDH_IMomentCapacitySolution_NeutralAxis			1426
#define IDH_IMomentCapacitySolution_NeutralAxisDirection			1427
#define IDH_IMomentCapacitySolution_CompressionResultant 1428
#define IDH_IMomentCapacitySolution_TensionResultant	1429
#define IDH_IMomentCapacitySolution_CompressionResultantLocation	1430
#define IDH_IMomentCapacitySolution_TensionResultantLocation	1431
#define IDH_IMomentCapacitySolution_GeneralSectionSolution	1432

#define IDH_IManderModelSection							1450
#define IDH_IManderModelSection_TransvYieldStrength		1451
#define IDH_IManderModelSection_TransvReinforcementRatio	1452
#define IDH_IManderModelSection_ConfinementEffectivenessCoefficient	1453

#define IDH_ICircularManderSection								1500
#define IDH_ICircularManderSection_TransvReinforcementType		1501
#define IDH_ICircularManderSection_Asp							1502
#define IDH_ICircularManderSection_As							1503
#define IDH_ICircularManderSection_db							1504
#define IDH_ICircularManderSection_S							1505
#define IDH_ICircularManderSection_Diameter						1506
#define IDH_ICircularManderSection_Cover						1507

#define IDH_IManderModel										1550
#define IDH_IManderModel_Section								1551
#define IDH_IManderModel_fco									1552
#define IDH_IManderModel_eco									1553
#define IDH_IManderModel_R										1554

#define IDH_IInteractionCurveSolution								1600
#define IDH_IInteractionCurveSolution_NeutralAxisDirection		1601
#define IDH_IInteractionCurveSolution_MomentCurvatureSolution		1602
#define IDH_IInteractionCurveSolution_AddSolutionPoint			1603
#define IDH_IInteractionCurveSolution_SolutionPointCount			1604

#define IDH_IInteractionCurveSolver								1650
#define IDH_IInteractionCurveSolver_Section						1651
#define IDH_IInteractionCurveSolver_Slices						1652
#define IDH_IInteractionCurveSolver_AxialTolerance				1653
#define IDH_IInteractionCurveSolver_MaxIterations					1654
#define IDH_IInteractionCurveSolver_InitialCurvatureStep			1655
#define IDH_IInteractionCurveSolver_Solve							1656

#define IDH_IPowerFormula										1700
#define IDH_IPowerFormula_Grade									1701
#define IDH_IPowerFormula_ProductionMethod						1702

#define IDH_IInteractionCapacityCurveSolution						1800
#define IDH_IInteractionCapacityCurveSolution_MomentCapacitySolution	1801
#define IDH_IInteractionCapacityCurveSolution_AddSolutionPoint			1802
#define IDH_IInteractionCapacityCurveSolution_SolutionPointCount		1803

#define IDH_IAxialInteractionCurveSolver						1840
#define IDH_IAxialInteractionCurveSolver_Section				1841
#define IDH_IAxialInteractionCurveSolver_Slices					1842
#define IDH_IAxialInteractionCurveSolver_AxialTolerance			1843
#define IDH_IAxialInteractionCurveSolver_MaxIterations			1844
#define IDH_IAxialInteractionCurveSolver_CompressionLimit		1845
#define IDH_IAxialInteractionCurveSolver_TensionLimit			1846
#define IDH_IAxialInteractionCurveSolver_Solve					1847

#define IDH_IMomentInteractionCurveSolver						1860
#define IDH_IMomentInteractionCurveSolver_Section				1861
#define IDH_IMomentInteractionCurveSolver_Slices				1862
#define IDH_IMomentInteractionCurveSolver_AxialTolerance		1863
#define IDH_IMomentInteractionCurveSolver_MaxIterations			1864
#define IDH_IMomentInteractionCurveSolver_CompressionLimit		1865
#define IDH_IMomentInteractionCurveSolver_TensionLimit			1866
#define IDH_IMomentInteractionCurveSolver_Solve					1867

#define IDH_ISectionBuilder										1900
#define IDH_ISectionBuilder_RectangularColumn					1901
#define IDH_ISectionBuilder_CircularColumn						1902

#define IDH_ICapacityReductionFactor							1920
#define IDH_ICapacityReductionFactor_Compute					1921
#define IDH_ICapacityReductionFactor_ComputeEx					1922

#define IDH_ICrackedSectionSolution                         2000
#define IDH_ICrackedSectionSolution_InitSolution            2001
#define IDH_ICrackedSectionSolution_CG                      2002
#define IDH_ICrackedSectionSolution_SliceCount              2003
#define IDH_ICrackedSectionSolution_Slice                   2004
#define IDH_ICrackedSectionSolution_ElasticProperties       2005

#define IDH_ICrackedSectionSolver                           2010
#define IDH_ICrackedSectionSolver_Section                   2011
#define IDH_ICrackedSectionSolver_Slices                    2012
#define IDH_ICrackedSectionSolver_SliceGrowthFactor         2013
#define IDH_ICrackedSectionSolver_Solve                     2014
#define IDH_ICrackedSectionSolver_CGTolerance               2015
#define IDH_ICrackedSectionSolver_MaxIterations             2016

#define IDH_ICrackedSectionSlice                            2020
#define IDH_ICrackedSectionSlice_InitSlice                  2021
#define IDH_ICrackedSectionSlice_Area                       2022
#define IDH_ICrackedSectionSlice_CG                         2023
#define IDH_ICrackedSectionSlice_Efg                        2024
#define IDH_ICrackedSectionSlice_Ebg                        2025
#define IDH_ICrackedSectionSlice_Shape                      2026

#endif //  INCLUDED_RCCAPACITY_HH_
