///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2011  Washington State Department of Transportation
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>
/****************************************************************************
CLASS
   bamTransientLdEnvelope
****************************************************************************/

#include <BridgeAnalysis\TransientLdEnvelope.h>        // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bamTransientLdEnvelope::bamTransientLdEnvelope(Int32 id) :
bamEnvelope(id)
{
}

bamTransientLdEnvelope::bamTransientLdEnvelope(const bamTransientLdEnvelope& rOther) :
bamEnvelope(rOther)
{
   MakeCopy(rOther);
}

bamTransientLdEnvelope::~bamTransientLdEnvelope()
{
}

//======================== OPERATORS  =======================================
bamTransientLdEnvelope& bamTransientLdEnvelope::operator= (const bamTransientLdEnvelope& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
bamEnvelope* bamTransientLdEnvelope::CreateClone() const
{
   return new bamTransientLdEnvelope( *this );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamTransientLdEnvelope::MakeCopy(const bamTransientLdEnvelope& rOther)
{
   // Add copy code here...
   // There is no additional data to copy in this calss
}

void bamTransientLdEnvelope::MakeAssignment(const bamTransientLdEnvelope& rOther)
{
   bamEnvelope::MakeAssignment( rOther );
   MakeCopy( rOther );
}

void bamTransientLdEnvelope::InitEnvelope(bamSectionResults* pMin,bamSectionResults* pMax) const
{
   pMin->Fx() = 0;
   pMin->Fy() = 0;
   pMin->Mz() = 0;
   pMin->Dx() = 0;
   pMin->Dy() = 0;
   pMin->Rz() = 0;

   pMax->Fx() = 0;
   pMax->Fy() = 0;
   pMax->Mz() = 0;
   pMax->Dx() = 0;
   pMax->Dy() = 0;
   pMax->Rz() = 0;
}

void bamTransientLdEnvelope::InitEnvelope(bamReaction* pMin,bamReaction* pMax) const
{
   pMin->Fx() = 0;
   pMin->Fy() = 0;
   pMin->Mz() = 0;
   pMin->Dx() = 0;
   pMin->Dy() = 0;
   pMin->Rz() = 0;

   pMax->Fx() = 0;
   pMax->Fy() = 0;
   pMax->Mz() = 0;
   pMax->Dx() = 0;
   pMax->Dy() = 0;
   pMax->Rz() = 0;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

