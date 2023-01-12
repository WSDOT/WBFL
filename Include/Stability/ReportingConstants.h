///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2023  Washington State Department of Transportation
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

#pragma once

#define LG Sub2(_T("L"),_T("g"))
#define LS Sub2(_T("L"),_T("s"))
#define LL Sub2(_T("L"),_T("l"))
#define LT Sub2(_T("L"),_T("t"))
#define LR Sub2(_T("L"),_T("r"))
#define LA Sub2(_T("L"),_T("a"))
#define LB Sub2(_T("L"),_T("b"))
#define H_RC Sub2(_T("H"), _T("rc"))
#define YR Sub2(_T("y"),_T("r"))
#define Y_WIND Sub2(_T("y"), _T("wind"))
#define Y_CF Sub2(_T("y"),_T("cf"))
#define Y_LIFT Sub2(_T("y"), _T("lift"))
#define ZO Sub2(_T("z"),_T("o"))
#define FO Sub2(_T("F"), _T("o"))
#define EI Sub2(_T("e"), _T("i"))
#define D_SWEEP Sub2(symbol(DELTA),_T("sweep"))
#define E_LIFT Sub2(_T("e"), _T("lift"))
#define E_BUNK Sub2(_T("e"), _T("bunk"))
#define E_WIND Sub2(_T("e"),_T("wind"))
#define Z_MAX Sub2(_T("z"),_T("max"))
#define Z_WIND Sub2(_T("z"),_T("wind"))
#define Z_CF Sub2(_T("z"),_T("cf"))
#define W_WIND Sub2(_T("W"),_T("wind"))
#define W_CF Sub2(_T("W"),_T("cf"))
#define M_OT Sub2(_T("M"),_T("ot"))
#define M_CR Sub2(_T("M"), _T("cr"))
#define K_THETA Sub2(_T("K"), symbol(theta))
#define K_THETA1 Sub2(_T("K"), symbol(theta) << _T("1"))
#define THETA_EQ Sub2(symbol(theta), _T("eq"))
#define THETA_CRACK Sub2(symbol(theta),_T("cr")) //Sub2(symbol(theta),_T("max"))
#define THETA_FAILURE Sub2(symbol(theta),_T("f")) //Sub2(symbol(theta) << _T("'"),_T("max"))
#define THETA_ROLLOVER Sub2(symbol(theta),_T("ro")) //Sub2(symbol(theta) << _T("''"),_T("max"))
#define R_SEAT Sub2(_T("R"),_T("seat"))
#define R_LIFT Sub2(_T("R"),_T("lift"))
#define FS_CR Sub2(_T("FS"), _T("cr"))
#define FS_F Sub2(_T("FS"),_T("f"))
#define FS_R Sub2(_T("FS"), _T("ro"))

#define CD_PASS_SINGLE_LINE(_cdr_,_cd_) RPT_PASS << _T(" (") << _cdr_.SetValue(_cd_ < 0 ? CDR_SKIP : _cd_,true) << _T(")")
#define CD_FAIL_SINGLE_LINE(_cdr_,_cd_) RPT_FAIL << _T(" (") << _cdr_.SetValue(_cd_ < 0 ? CDR_SKIP : _cd_,false) << _T(")")