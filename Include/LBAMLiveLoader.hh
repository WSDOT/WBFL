///////////////////////////////////////////////////////////////////////
// LBAM - Longitudinal Bridge Analysis Model Live Loader
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

#include "LBAMAnalysisErrors.h"

// Help Context IDs
#define IDH_WBFLLBAMLiveLoader                   	                 1900000

// Errors
#define IDH_E_MUST_BE_ONE_MORE_SUPPORT_THAN_SPANS                   1900001
#define IDH_E_SUPERSTRUCTURE_TOO_SHORT                              1900002
#define IDH_E_LL_INITIALIZATION                                     1900003
#define IDH_E_INVALID_VEHICULAR_CONTEXT                             1900006
#define IDH_E_VAR_AXLE_OOR                                          1900007
#define IDH_E_VAR_SPACING_OOR                                       1900008
#define IDH_E_INVALID_VAR_SPACING                                   1900009
#define IDH_E_TS_NOT_FOUND                                          1900010
#define IDH_E_VEHICULARLOAD_NOT_FOUND                               1900011

// objects

#define IDH_BasicVehicularResponse                                             1920000
#define IDH_BasicVehicularResponse_ComputeDeflections                          1920001
#define IDH_BasicVehicularResponse_ComputeForces                               1920002
#define IDH_BasicVehicularResponse_ComputeReactions                            1920003
#define IDH_BasicVehicularResponse_ComputeStresses                             1920004
#define IDH_BasicVehicularResponse_ComputeSupportDeflections                   1920005

#define IDH_DependOnVehicularAnalysisContext                                   1920006
#define IDH_DependOnVehicularAnalysisContext_Initialize                        1920007

#define IDH_EnvelopedVehicularResponse                                         1920008
#define IDH_EnvelopedVehicularResponse_BruteForceVehicularResponse             1920009
#define IDH_EnvelopedVehicularResponse_ComputeDeflections                      1920010
#define IDH_EnvelopedVehicularResponse_ComputeForces                           1920011
#define IDH_EnvelopedVehicularResponse_ComputeReactions                        1920012
#define IDH_EnvelopedVehicularResponse_ComputeStresses                         1920013
#define IDH_EnvelopedVehicularResponse_ComputeSupportDeflections               1920014

#define IDH_EnvelopingStrategy                                                 1920015
#define IDH_EnvelopingStrategy_Strategy                                        1920016

#define IDH_LiveLoadConfiguration                                              1920017
#define IDH_LiveLoadConfiguration_AxleConfig                                   1920018
#define IDH_LiveLoadConfiguration_Clone                                        1920019
#define IDH_LiveLoadConfiguration_DistributionFactorType                       1920020
#define IDH_LiveLoadConfiguration_DoApplyImpact                                1920021
#define IDH_LiveLoadConfiguration_ForceEffect                                  1920022
#define IDH_LiveLoadConfiguration_IsApplicable                                 1920023
#define IDH_LiveLoadConfiguration_LiveLoadModel                                1920024
#define IDH_LiveLoadConfiguration_OnLiveLoadConfigurationChanged               1920025
#define IDH_LiveLoadConfiguration_Optimization                                 1920026
#define IDH_LiveLoadConfiguration_TruckDirection                               1920027
#define IDH_LiveLoadConfiguration_TruckPosition                                1920028
#define IDH_LiveLoadConfiguration_VariableSpacing                              1920029
#define IDH_LiveLoadConfiguration_VehicleIndex                                 1920030
#define IDH_LiveLoadConfiguration_VehicularLoadConfiguration                   1920031
#define IDH_LiveLoadConfiguration_PivotAxleIndex							   1920075

#define IDH_LiveLoadModelResponse                                              1920032
#define IDH_LiveLoadModelResponse_ComputeDeflections                           1920033
#define IDH_LiveLoadModelResponse_ComputeForces                                1920034
#define IDH_LiveLoadModelResponse_ComputeReactions                             1920035
#define IDH_LiveLoadModelResponse_ComputeStresses                              1920036
#define IDH_LiveLoadModelResponse_ComputeSupportDeflections                    1920037

#define IDH_LiveLoadModelResults                                               1920038
#define IDH_LiveLoadModelResults_Add                                           1920039
#define IDH_LiveLoadModelResults_Clear                                         1920040
#define IDH_LiveLoadModelResults_Count                                         1920041
#define IDH_LiveLoadModelResults_GetResult                                     1920042
#define IDH_LiveLoadModelResults_Remove                                        1920043
#define IDH_LiveLoadModelResults_Reserve                                       1920044
#define IDH_LiveLoadModelResults_SetResult                                     1920045

#define IDH_LiveLoadModelSectionResults                                        1920046
#define IDH_LiveLoadModelSectionResults_Add                                    1920047
#define IDH_LiveLoadModelSectionResults_Clear                                  1920048
#define IDH_LiveLoadModelSectionResults_Count                                  1920049
#define IDH_LiveLoadModelSectionResults_GetResult                              1920050
#define IDH_LiveLoadModelSectionResults_Remove                                 1920051
#define IDH_LiveLoadModelSectionResults_Reserve                                1920052
#define IDH_LiveLoadModelSectionResults_SetResult                              1920053

#define IDH_LiveLoadModelStressResults                                         1920054
#define IDH_LiveLoadModelStressResults_Add                                     1920055
#define IDH_LiveLoadModelStressResults_Clear                                   1920056
#define IDH_LiveLoadModelStressResults_Count                                   1920057
#define IDH_LiveLoadModelStressResults_GetResult                               1920058
#define IDH_LiveLoadModelStressResults_Remove                                  1920059
#define IDH_LiveLoadModelStressResults_Reserve                                 1920060
#define IDH_LiveLoadModelStressResults_SetResult                               1920061

#define IDH_SupportLocations                                                   1920062
#define IDH_SupportLocations_IsInteriorSupport                                 1920063
#define IDH_SupportLocations_ISupportLocations                                 1920064
#define IDH_SupportLocations_LeftOverhang                                      1920065
#define IDH_SupportLocations_RightOverhang                                     1920066
#define IDH_SupportLocations_TotalLength                                       1920067

#define IDH_VehicularAnalysisContext                                           1920068
#define IDH_VehicularAnalysisContext_Initialize                                1920069
#define IDH_VehicularAnalysisContext_OnLiveLoadChanged                         1920070
#define IDH_VehicularAnalysisContext_OnStiffnessResponseChanged                1920071

#define IDH_EnvelopedVehicularResponseFactory								   1920072
#define IDH_EnvelopedVehicularResponseFactory_CreateEnvelopedVehicularResponse 1920073

#define IDH_SupportEnvelopedVehicularResponseFactory                           1920074

// next value is 1920076