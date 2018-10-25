///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfPrecastGirderSection
****************************************************************************/

#include <BridgeModeling\PrecastGirderSection.h>        // class implementation
#include <Material\ConcreteEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfPrecastGirderSection::bmfPrecastGirderSection(const gmIPrecastBeam* pShape,
                                                 const matConcreteEx* pConc ) :
bmfConcGirderSection( pShape, pConc )
{
}


bmfPrecastGirderSection::bmfPrecastGirderSection(const bmfPrecastGirderSection& rOther) :
bmfConcGirderSection( rOther )
{
   MakeCopy(rOther);
}

bmfPrecastGirderSection::~bmfPrecastGirderSection()
{
}

//======================== OPERATORS  =======================================
bmfPrecastGirderSection& bmfPrecastGirderSection::operator= (const bmfPrecastGirderSection& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
bmfIGirderSection* bmfPrecastGirderSection::CreateClone() const
{
   return new bmfPrecastGirderSection(*this);
}

//======================== ACCESS     =======================================
const gmIPrecastBeam* bmfPrecastGirderSection::GetGirderShape() const
{
   // This cast is to recover type information.  If the cast fails,
   // something is messed up.  We only let gmPrecastBeam objects into this
   // object.
   const gmCompositeShape* pCompShape = dynamic_cast<const gmCompositeShape*>(bmfConcGirderSection::GetGirderShape());
   const gmIPrecastBeam* pShape;
   pShape = dynamic_cast<const gmIPrecastBeam*>( pCompShape->GetShape(1) );
   CHECK( pShape != 0 );
   return pShape;
}

Float64 bmfPrecastGirderSection::GetAvgWebWidth() const
{
   return GetGirderShape()->GetShearWidth();
}

Float64 bmfPrecastGirderSection::GetTopFlangeWidth() const
{
   return GetGirderShape()->GetTopFlangeWidth();
}

Float64 bmfPrecastGirderSection::GetTopWidth() const
{
   return GetGirderShape()->GetTopWidth();
}

Float64 bmfPrecastGirderSection::GetHeight() const
{
   return GetGirderShape()->GetHeight();
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfPrecastGirderSection::MakeCopy(const bmfPrecastGirderSection& rOther)
{
}

void bmfPrecastGirderSection::MakeAssignment(const bmfPrecastGirderSection& rOther)
{
   bmfConcGirderSection::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

