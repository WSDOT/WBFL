///////////////////////////////////////////////////////////////////////
// LBAM Analysis Utility - Longitindal Bridge Analysis Model
// Copyright © 1999-2013  Washington State Department of Transportation
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

// Help Context IDH
#define IDH_WbflLLBAMAnalysisUtility               	                 2000000

// errors
#define IDH_E_ENGINE_INIT_ONCE                                       2000013
#define IDH_E_INVALID_CONTEXT                                        2000014
#define IDH_E_ENGINE_INIT                                            2000015
#define IDH_E_PROGRESS_INIT_SEQUENCE                                 2000016

// objects
#define IDH_ISupportProgressMonitorForEngine                                   2020000
#define IDH_ISupportProgressMonitorForEngine_InitializeProgressMonitor4E       2020001
#define IDH_ISupportProgressMonitorForEngine_SupportProgressMonitorForEngine   2020002

#define IDH_LBAMAnalysisEngine                                                 2020003
#define IDH_LBAMAnalysisEngine_AnalysisPOIs                                    2020004
#define IDH_LBAMAnalysisEngine_AnalysisType                                    2020005
#define IDH_LBAMAnalysisEngine_BasicVehicularResponse                          2020006
#define IDH_LBAMAnalysisEngine_ConcurrentLoadCombinationResponse               2020007
#define IDH_LBAMAnalysisEngine_ContraflexureResponse                           2020008
#define IDH_LBAMAnalysisEngine_EnvelopedVehicularResponse                      2020009
#define IDH_LBAMAnalysisEngine_InfluenceLineResponse                           2020010
#define IDH_LBAMAnalysisEngine_Initialize                                      2020011
#define IDH_LBAMAnalysisEngine_LiveLoadModelResponse                           2020012
#define IDH_LBAMAnalysisEngine_LoadCaseResponse                                2020013
#define IDH_LBAMAnalysisEngine_LoadCombinationResponse                         2020014
#define IDH_LBAMAnalysisEngine_LoadGroupResponse                               2020015
#define IDH_LBAMAnalysisEngine_Model                                           2020016
#define IDH_LBAMAnalysisEngine_LiveLoadNegativeMomentRegion                    2020017

#define IDH_LBAMModelEnveloper                                                 2020020
#define IDH_LBAMModelEnveloper_Engines                                         2020021
#define IDH_LBAMModelEnveloper_Initialize                                      2020022
#define IDH_LBAMModelEnveloper_AnalysisType                                    2020023
#define IDH_LBAMModelEnveloper_LoadCombinationResponse                         2020024
#define IDH_LBAMModelEnveloper_LiveLoadModelResponse						   2020025
#define IDH_LBAMModelEnveloper_EnvelopedVehicularResponse					   2020026
#define IDH_LBAMModelEnveloper_AddModel										   2020027
#define IDH_LBAMModelEnveloper_OptimizationType                                2020028