///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifndef __LBAMLoadCombinerError_H_
#define __LBAMLoadCombinerError_H_

// HRESULT's for the LBAM Load Combiner system

#define LBAMC_E_LC_INITIALIZATION                     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1901)
#define LBAMC_E_INVALID_LC_CONTEXT                    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1902)
#define LBAMC_E_LOADCASE_NO_EXIST                     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1903)
#define LBAMC_E_INVALID_LG_RESP                       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1904)
#define LBAMC_E_LOADCASE_DUPLICATE                    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1905)
#define LBAMC_E_POI_INVALID_MBR                       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1906)
#define LBAMC_E_INVALID_POI                           MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1907)
#define LBAMC_E_LOADCOMBO_DUPLICATE                   MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1908)
#define LBAMC_E_INVALID_CASE_COMBO                    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1909)
#define LBAMC_E_LOADCOMBO_NO_EXIST                    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1910)
#define LBAMC_E_SUM_INTERNAL_POI                      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1912)
#define LBAMC_E_SUPPORT_NOT_EXIST                     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1913)

#endif 