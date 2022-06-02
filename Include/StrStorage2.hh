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

#ifndef INCLUDED_STRSTORAGE_HH_
#define INCLUDED_STRSTORAGE_HH_

#define IDH_Load_Open                           3501
#define IDH_Load_Begin_Unit                     3502
#define IDH_Load_End_Unit                       3503
#define IDH_Load_Version                        3504
#define IDH_Load_TopVersion                     3505
#define IDH_Load_Property                       3506
#define IDH_Load_End_Of_Storage                 3507
#define IDH_Load_Close                          3508
#define IDH_Load_End_Of_Storage2                3509
 
#define IDH_Save_Open                           3531
#define IDH_Save_Begin_Unit                     3532
#define IDH_Save_End_Unit                       3533
#define IDH_Save_Version                        3534
#define IDH_Save_TopVersion                     3535
#define IDH_Save_Property                       3536
#define IDH_Save_Close                          3537

#define IDH_ISS_Save                            3541
#define IDH_ISS_Load                            3542
#define IDH_ISS2_Save                           3543
#define IDH_ISS2_Load                           3544

#define IDH_STRLOAD_E_CLASS_ISTRUCTUREDSTORAGE2 3551
#define IDH_STRLOAD_E_FILENOTFOUND              3552
#define IDH_STRLOAD_E_CANTOPEN                  3553
#define IDH_STRLOAD_E_INVALIDFORMAT             3554
#define IDH_STRLOAD_E_CLASS_NOT_REGISTERED      3555

#define IDH_STRSAVE_E_CANTOPEN                  3571
#define IDH_STRSAVE_E_INITIALIZING_THE_PARSER   3572
#define IDH_STRSAVE_E_BADWRITE                  3573
#define IDH_STRSAVE_E_IPERSIST                  3574
#define IDH_STRSAVE_E_CLASS_ISTRUCTUREDSTORAGE2 3575
#define IDH_STRSAVE_E_FILE_NOT_OPEN             3576
#define IDH_STRSAVE_E_INVALID_VARIANT_TYPE      3577
#define IDH_STRSAVE_E_MUST_HAVE_ONE_UNIT        3578
#define IDH_STRSAVE_E_ONLY_ONE_UNIT             3579

#endif // INCLUDED_WBFLTOOLS_HM_