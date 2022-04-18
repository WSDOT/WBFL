///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
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
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_WBFLTOOLS_HM_
#define INCLUDED_WBFLTOOLS_HM_

#define IDH_WbflTools						100

#define IDH_LicenseType                      200
#define IDH_AcceptanceType                   201

#define IDH_ArpNotice						1000
#define IDH_ArpNotice_ShowAgain				1001
#define IDH_ArpNotice_Show					1002

#define IDH_MohrCircle                 2000 
#define IDH_MohrCircle_Sii             2001
#define IDH_MohrCircle_Sjj             2002
#define IDH_MohrCircle_Sij             2003
#define IDH_MohrCircle_Center          2004
#define IDH_MohrCircle_Radius          2005
#define IDH_MohrCircle_Smax            2006
#define IDH_MohrCircle_Smin            2007
#define IDH_MohrCircle_Tmax            2008
#define IDH_MohrCircle_PrincipleDirection 2009
#define IDH_MohrCircle_ComputeState    2010
#define IDH_MohrCircle_ComputeSxx      2011
#define IDH_MohrCircle_ComputeSxy      2012
#define IDH_MohrCircle_ComputeSyy      2013

#define IDH_BStrArray                                                          2020
#define IDH_BStrArray_Add                                                      2021
#define IDH_BStrArray_BstrArray                                                2022
#define IDH_BStrArray_Clear                                                    2023
#define IDH_BStrArray_Clone                                                    2024
#define IDH_BStrArray_Count                                                    2025
#define IDH_BStrArray_Find                                                     2026
#define IDH_BStrArray_Insert                                                   2027
#define IDH_BStrArray_Item                                                     2028
#define IDH_BStrArray_ReDim                                                    2029
#define IDH_BStrArray_Remove                                                   2030
#define IDH_BStrArray_Reserve                                                  2031

#define IDH_DblArray                                                           2032
#define IDH_DblArray_Add                                                       2033
#define IDH_DblArray_Clear                                                     2034
#define IDH_DblArray_Clone                                                     2035
#define IDH_DblArray_Count                                                     2036
#define IDH_DblArray_Insert                                                    2037
#define IDH_DblArray_Item                                                      2038
#define IDH_DblArray_ReDim                                                     2039
#define IDH_DblArray_Remove                                                    2040
#define IDH_DblArray_Reserve                                                   2041

#define IDH_LongArray                                                           2042
#define IDH_LongArray_Add                                                       2043
#define IDH_LongArray_Clear                                                     2044
#define IDH_LongArray_Clone                                                     2045
#define IDH_LongArray_Count                                                     2046
#define IDH_LongArray_Find                                                      2047
#define IDH_LongArray_Insert                                                    2048
#define IDH_LongArray_Item                                                      2049
#define IDH_LongArray_ReDim                                                     2050
#define IDH_LongArray_Remove                                                    2051
#define IDH_LongArray_Reserve                                                   2052
#define IDH_LongArray_Assign                                                    2053


#define IDH_ULongArray                                                           2062
#define IDH_ULongArray_Add                                                       2063
#define IDH_ULongArray_Clear                                                     2064
#define IDH_ULongArray_Clone                                                     2065
#define IDH_ULongArray_Count                                                     2066
#define IDH_ULongArray_Find                                                      2067
#define IDH_ULongArray_Insert                                                    2068
#define IDH_ULongArray_Item                                                      2069
#define IDH_ULongArray_ReDim                                                     2070
#define IDH_ULongArray_Remove                                                    2071
#define IDH_ULongArray_Reserve                                                   2072

#define IDH_UnkArray                                                           2089
#define IDH_UnkArray_Add                                                       2090
#define IDH_UnkArray_Clear                                                     2091
#define IDH_UnkArray_Clone                                                     2092
#define IDH_UnkArray_Count                                                     2093
#define IDH_UnkArray_Insert                                                    2094
#define IDH_UnkArray_Item                                                      2095
#define IDH_UnkArray_Remove                                                    2096
#define IDH_UnkArray_Reserve                                                   2097

#define IDH_ProgressMonitorWindow                                              2100
#define IDH_ProgressMonitorWindow_Show                                         2101
#define IDH_ProgressMonitorWindow_Hide                                         2102
#define IDH_ProgressMonitorWindow_HasCancel                                    2103
#define IDH_ProgressMonitorWindow_HasGauge                                     2104
#define IDH_ProgressMonitorWindow_Close              						   2105

#define IDH_ILogProgressToFile                                                 2110
#define IDH_ILogProgressToFile_OpenLogFile                                     2111
#define IDH_ILogProgressToFile_CloseLogFile                                    2112

#endif // INCLUDED_WBFLTOOLS_HM_