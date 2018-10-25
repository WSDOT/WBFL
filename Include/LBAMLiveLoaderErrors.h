///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
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

#ifndef __LBAMLiveLoaderError_H_
#define __LBAMLiveLoaderError_H_

// HRESULT's for the LiveLoader System
#define LBAMLL_E_MUST_BE_ONE_MORE_SUPPORT_THAN_SPANS	     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1101)
#define LBAMLL_E_SUPERSTRUCTURE_TOO_SHORT                  MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1102)
#define LBAMLL_E_LL_INITIALIZATION                         MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1103)
#define LBAMLL_E_INVALID_VEHICULAR_CONTEXT                 MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1106)
#define LBAMLL_E_VAR_AXLE_OOR                              MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1107)
#define LBAMLL_E_VAR_SPACING_OOR                           MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1108)
#define LBAMLL_E_INVALID_VAR_SPACING                       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1109)
#define LBAMLL_E_TS_NOT_FOUND                              MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1110)
#define LBAMLL_E_VEHICULARLOAD_NOT_FOUND                   MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1111)
#endif 