///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2024  Washington State Department of Transportation
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
#define IDH_WBFLLBAMLoadCombiner                   	             2100000

// Errors
#define IDH_E_LC_INITIALIZATION                                      2110001
#define IDH_E_INVALID_LC_CONTEXT                                     2110002
#define IDH_E_LOADCASE_NO_EXIST                                      2110003
#define IDH_E_INVALID_LG_RESP                                        2110004
#define IDH_E_LOADCASE_DUPLICATE                                     2110005
#define IDH_E_POI_INVALID_MBR                                        2110006
#define IDH_E_INVALID_POI                                            2110007
#define IDH_E_LOADCOMBO_DUPLICATE                                    2110008
#define IDH_E_INVALID_CASE_COMBO                                     2110009
#define IDH_E_LOADCOMBO_NO_EXIST                                     2110010
#define IDH_E_SUM_INTERNAL_POI                                       2110012

// Constants
#define IDH_ComboType                                                2120001

// objects
#define IDH_ConcurrentLoadCombinationResponse                                  21200100
#define IDH_ConcurrentLoadCombinationResponse_ComputeDeflections               21200001
#define IDH_ConcurrentLoadCombinationResponse_ComputeForces                    21200002
#define IDH_ConcurrentLoadCombinationResponse_ComputeReactions                 21200003
#define IDH_ConcurrentLoadCombinationResponse_ComputeStresses                  21200004
#define IDH_ConcurrentLoadCombinationResponse_ComputeSupportDeflections        21200005

#define IDH_DependOnLoadCombinationAnalysisContext                             21200006
#define IDH_DependOnLoadCombinationAnalysisContext_Initialize                  21200007

#define IDH_GetCombinationFactors                                              21200008
#define IDH_GetCombinationFactors_GetPOICombinationFactors                     21200009
#define IDH_GetCombinationFactors_GetSupportCombinationFactors                 21200010
#define IDH_GetCombinationFactors_IGetCombinationFactors                       21200011

#define IDH_LoadCaseResponse                                                   21200012
#define IDH_LoadCaseResponse_ComputeDeflections                                21200013
#define IDH_LoadCaseResponse_ComputeForces                                     21200014
#define IDH_LoadCaseResponse_ComputeReactions                                  21200015
#define IDH_LoadCaseResponse_ComputeStresses                                   21200016
#define IDH_LoadCaseResponse_ComputeSupportDeflections                         21200017

#define IDH_LoadCombinationAnalysisContext                                     21200018
#define IDH_LoadCombinationAnalysisContext_Initialize                          21200019
#define IDH_LoadCombinationAnalysisContext_OnCombinationChanged                21200020
#define IDH_LoadCombinationAnalysisContext_OnResultsChanged                    21200021

#define IDH_LoadCombinationResponse                                            21200022
#define IDH_LoadCombinationResponse_ComputeDeflections                         21200023
#define IDH_LoadCombinationResponse_ComputeForces                              21200024
#define IDH_LoadCombinationResponse_ComputeReactions                           21200025
#define IDH_LoadCombinationResponse_ComputeStresses                            21200026
#define IDH_LoadCombinationResponse_ComputeSupportDeflections                  21200027

#define IDH_LoadCombinationResultConfiguration                                 21200028
#define IDH_LoadCombinationResultConfiguration_AddLoadCaseFactor               21200029
#define IDH_LoadCombinationResultConfiguration_GetLoadCaseFactor               21200030
#define IDH_LoadCombinationResultConfiguration_LiveLoadConfiguration           21200031
#define IDH_LoadCombinationResultConfiguration_LiveLoadFactor                  21200032
#define IDH_LoadCombinationResultConfiguration_LoadCaseFactorCount             21200033
#define IDH_LoadCombinationResultConfiguration_SummationType                   21200034

#define IDH_LoadCombinationResults                                             21200035
#define IDH_LoadCombinationResults_Add                                         21200036
#define IDH_LoadCombinationResults_Clear                                       21200037
#define IDH_LoadCombinationResults_Count                                       21200038
#define IDH_LoadCombinationResults_GetResult                                   21200039
#define IDH_LoadCombinationResults_Remove                                      21200040
#define IDH_LoadCombinationResults_Reserve                                     21200041
#define IDH_LoadCombinationResults_SetResult                                   21200042

#define IDH_LoadCombinationSectionResults                                      21200043
#define IDH_LoadCombinationSectionResults_Add                                  21200044
#define IDH_LoadCombinationSectionResults_Clear                                21200045
#define IDH_LoadCombinationSectionResults_Count                                21200046
#define IDH_LoadCombinationSectionResults_GetResult                            21200047
#define IDH_LoadCombinationSectionResults_Remove                               21200048
#define IDH_LoadCombinationSectionResults_Reserve                              21200049
#define IDH_LoadCombinationSectionResults_SetResult                            21200050

#define IDH_LoadCombinationStressResults                                       21200051
#define IDH_LoadCombinationStressResults_Add                                   21200052
#define IDH_LoadCombinationStressResults_Clear                                 21200053
#define IDH_LoadCombinationStressResults_Count                                 21200054
#define IDH_LoadCombinationStressResults_GetResult                             21200055
#define IDH_LoadCombinationStressResults_Remove                                21200056
#define IDH_LoadCombinationStressResults_Reserve                               21200057
#define IDH_LoadCombinationStressResults_SetResult                             21200058
