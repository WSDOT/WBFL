///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
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

#ifndef __LBAMError_H_
#define __LBAMError_H_

// HRESULT's for the Fem2d System

#define LBAM_E_STAGE_NOT_EXISTS      	                    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,601)
#define LBAM_E_BLANK_NAMES_NOT_ALLOWED    				     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,602)
#define LBAM_E_MUST_HAVE_ONE_SPAN                         MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,605)
#define LBAM_E_MUST_HAVE_ONE_SSM                          MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,606)
#define LBAM_E_SPAN_LENGTH_MUST_BE_GT_ZERO                MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,607)
#define LBAM_E_SPAN_LENGTH_EXCEEDS_SUPERSTRUCTUREMEMBERS  MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,608)
#define LBAM_E_SSM_LENGTH_MUST_BE_GT_ZERO                 MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,609)
#define LBAM_E_TEMPSUPPORT_NOT_EXIST                      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,610)
#define LBAM_E_SPAN_NOT_EXIST                             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,611)
#define LBAM_E_SUPPORT_NOT_EXIST                          MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,612)
#define LBAM_E_SSM_NOT_EXIST                              MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,613)
#define LBAM_E_LOCATION_OOR                               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,614)
#define LBAM_E_TEMPSUPPORT_OFFSET_GT_LENGTH               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,615)
#define LBAM_E_SUPPORT_OFFSET_GT_LENGTH                   MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,616)
#define LBAM_E_INVALID_MEMBERTYPE                         MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,617)
#define LBAM_E_NO_SEGMENTS_FOR_STAGE                      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,618)
#define LBAM_E_POI_NO_STAGE                               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,619)


#endif