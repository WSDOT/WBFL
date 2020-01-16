///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2020  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#pragma once

#if defined USING_OPENBRIDGEML

#include <WBFLCogo\CogoExp.h>
#include <OpenBridgeML_Alignments.hxx>
#include <WBFLCogo.h>
#include <WBFLUnitServer.h>

BOOL COGOFUNC CreateAlignment(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::Alignment& obmlAlignment,IAlignment** ppAlignment);
BOOL COGOFUNC CreateAlignmentsCollection(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::AlignmentsType& obmlAlignments,IAlignmentCollection** ppAlignments);
BOOL COGOFUNC GetAlignments(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::AlignmentsType& obmlAlignments,IAlignmentCollection* pAlignments);

#endif USING_OPENBRIDGEML