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
   bmfConcGirderSection
****************************************************************************/

#include <BridgeModeling\ConcGirderSection.h>
#include <Material\ConcreteEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfConcGirderSection::bmfConcGirderSection(const gmIShape* pShape,
                                           const matConcreteEx* pConc )
{
   m_pShape = std::auto_ptr<gmCompositeShape>(new gmCompositeShape);
   m_pShape->AddShape(*pShape);
   m_bUpdateSection = true;
   m_pConc  = pConc;
}


bmfConcGirderSection::bmfConcGirderSection(const bmfConcGirderSection& rOther)
{
   m_bUpdateSection = true;
   m_pConc  = 0;
   MakeCopy(rOther);
}

bmfConcGirderSection::~bmfConcGirderSection()
{
}

//======================== OPERATORS  =======================================
bmfConcGirderSection& bmfConcGirderSection::operator= (const bmfConcGirderSection& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

gmElasticProperties bmfConcGirderSection::GetElasticProperties() const
{
   UpdateSection();
   gmElasticProperties prop;
   m_pSection->GetElasticProperties( &prop );
   return prop;
}

void bmfConcGirderSection::Draw(HDC hdc,const grlibPointMapper& mapper) const
{
   UpdateSection();
   m_pSection->Draw( hdc, mapper );
}

//======================== ACCESS     =======================================
const gmIShape* bmfConcGirderSection::GetGirderShape() const
{
   return m_pShape.get();
}

const matConcreteEx* bmfConcGirderSection::GetConcrete() const
{
   return m_pConc;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfConcGirderSection::MakeCopy(const bmfConcGirderSection& rOther)
{
   m_pShape = std::auto_ptr<gmCompositeShape>(dynamic_cast<gmCompositeShape*>(rOther.m_pShape->CreateClone()));
   m_pConc = rOther.m_pConc;

   m_pSection = std::auto_ptr<gmSection>(0);
   m_bUpdateSection = true;
}

void bmfConcGirderSection::MakeAssignment(const bmfConcGirderSection& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfConcGirderSection::UpdateSection() const
{
   if ( !m_bUpdateSection )
      return;

   m_pSection = std::auto_ptr<gmSection>( new gmSection );

   m_pSection->AddComponent( *m_pShape, m_pConc->GetE(), m_pConc->GetDensityForWeight() );

   m_bUpdateSection = false;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

