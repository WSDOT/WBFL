///////////////////////////////////////////////////////////////////////
// LBAM Utility - Longitindal Bridge Analysis Model
// Copyright © 1999-2019  Washington State Department of Transportation
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
// Help Context IDH
#define IDH_WBFLLBAMUtility                       	                 1800000

// errors
#define IDH_E_E_MUST_BE_GT_ZERO                                      1800003
#define IDH_E_A_MUST_BE_GT_ZERO                                      1800004
#define IDH_E_I_MUST_BE_GT_ZERO                                      1800005
#define IDH_E_DEPTH_MUST_BE_GT_ZERO                                  1800006
#define IDH_E_POI_INCREMENT_MUST_BE_GT_ZERO                          1800008
#define IDH_E_POI_BAD_LOCATION                                       1800011

// constants
#define IDH_SpecificationUnitsType                                   1810020
#define IDH_DesignVehicularLoadOrder                                 1810021

// objects
#define IDH_LBAMFactory                                              1820000
#define IDH_LBAMFactory_CreateSimpleModel                            1820001

#define IDH_LBAMFactory_GetSupportIDsForStage                        1820002
#define IDH_LBAMFactory_MapLoadGroupToLoadCase                       1820003
#define IDH_LBAMFactory_CreateSelfWeightDeadLoad                     1820004
#define IDH_LBAMFactory_GeneratePOIsOnSuperstructure                 1820005
#define IDH_LBAMFactory_GetSuperstructurePOIs                        1820006

#define IDH_LBAMLRFDFactory                                          1820030
#define IDH_LBAMLRFDFactory_ConfigureLiveLoad                        1820031
#define IDH_LBAMLRFDFactory_ConfigureLoadCombinations                1820032
#define IDH_LBAMLRFDFactory_ConfigureDesignLiveLoad                  1820033
#define IDH_LBAMLRFDFactory_ConfigureDeflectionLiveLoad              1820034
#define IDH_LBAMLRFDFactory_ConfigureFatigueLiveLoad                 1820035
#define IDH_LBAMLRFDFactory_ConfigureLegalLiveLoad                   1820036
#define IDH_LBAMLRFDFactory_ConfigureNotionalRatingLoad              1820037
#define IDH_LBAMLRFDFactory_ConfigureSpecializedHaulingUnits         1820038
