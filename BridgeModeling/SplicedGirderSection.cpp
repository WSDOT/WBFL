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
   bmfSplicedGirderSection
****************************************************************************/

#include <BridgeModeling\SplicedGirderSection.h>        // class implementation
#include <Material\ConcreteEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfSplicedGirderSection::bmfSplicedGirderSection(const gmIPrecastBeam* pShape,
                                                 const std::vector<Duct>& ducts,
                                                 const matConcreteEx* pConc ) :
bmfPrecastGirderSection( pShape, pConc )
{
   m_Ducts = ducts;
}


bmfSplicedGirderSection::bmfSplicedGirderSection(const bmfSplicedGirderSection& rOther) :
bmfPrecastGirderSection( rOther )
{
   MakeCopy(rOther);
}

bmfSplicedGirderSection::~bmfSplicedGirderSection()
{
}

//======================== OPERATORS  =======================================
bmfSplicedGirderSection& bmfSplicedGirderSection::operator= (const bmfSplicedGirderSection& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
bmfIGirderSection* bmfSplicedGirderSection::CreateClone() const
{
   return new bmfSplicedGirderSection(*this);
}

const gmIPrecastBeam* bmfSplicedGirderSection::GetBasicGirderShape() const
{
   return bmfPrecastGirderSection::GetGirderShape();
}
 
const gmCompositeShape* bmfSplicedGirderSection::GetGirderShape() const
{
   UpdateSection();
   const gmCompositeShape* pCompShape = dynamic_cast<const gmCompositeShape*>(bmfConcGirderSection::GetGirderShape());
   return pCompShape;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfSplicedGirderSection::MakeCopy(const bmfSplicedGirderSection& rOther)
{
   m_Ducts = rOther.m_Ducts;
}

void bmfSplicedGirderSection::MakeAssignment(const bmfSplicedGirderSection& rOther)
{
   bmfPrecastGirderSection::MakeAssignment( rOther );
   MakeCopy( rOther );
}

void bmfSplicedGirderSection::UpdateSection() const
{
   std::auto_ptr<gmIShape> pBeam( m_pShape->GetShape(1)->CreateClone() );
   m_pShape->Clear();

   m_pShape->AddShape(*pBeam);

   // Now add the duct holes to the cross section
   std::vector<Duct>::const_iterator iter;
   for ( iter = m_Ducts.begin(); iter != m_Ducts.end(); iter++ )
   {
      Duct duct = *iter;

      gmCircle circle(duct.location,duct.diameter/2);

      circle.MakeSolid(false);

      m_pShape->AddShape(circle);
   }

   bmfPrecastGirderSection::UpdateSection(); // default update
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

