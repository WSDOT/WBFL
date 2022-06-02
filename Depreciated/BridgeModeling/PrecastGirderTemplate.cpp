///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2022  Washington State Department of Transportation
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
   bmfPrecastGirderTemplate
****************************************************************************/

#include <BridgeModeling\PrecastGirderTemplate.h>
#include <BridgeModeling\PrecastGirder.h>
#include <GeomModel\PrecastBeam.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfPrecastGirderTemplate::bmfPrecastGirderTemplate(const std::_tstring& name,
                                                   const bmfGirderProfile* pProfile,
                                                   const matConcreteEx* pConc,
                                                   const matPsStrand* pStrand,
                                                   const bmfStrandPattern& strPtrn,
                                                   const bmfStrandPattern& endPtrn,
                                                   const bmfStrandPattern& hpPtrn,
                                                   const bmfStrandPattern& tmpPtrn,
                                                   const bmfLrLayout&      lrLayout,
                                                   Float64 hpLoc,
                                                   bmfMeasuredFrom hpLocMeasFrom) :
bmfGirderTemplate( name, pProfile ),
m_pConc( pConc ),
m_pStrand( pStrand ),
m_StraightPattern( strPtrn ),
m_TempPattern( tmpPtrn ),
m_EndPattern( endPtrn ),
m_HPPattern( hpPtrn ),
m_LrLayout(lrLayout)
{
   SetHarpPointLocation( hpLoc, hpLocMeasFrom );
}

bmfPrecastGirderTemplate::bmfPrecastGirderTemplate(const bmfPrecastGirderTemplate& rOther) :
bmfGirderTemplate( rOther )
{
   MakeCopy( rOther );
}

bmfPrecastGirderTemplate::~bmfPrecastGirderTemplate()
{
}

//======================== OPERATORS  =======================================
bmfPrecastGirderTemplate& bmfPrecastGirderTemplate::operator= (const bmfPrecastGirderTemplate& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

bmfGirder* bmfPrecastGirderTemplate::CreateGirder()
{
   return new bmfPrecastGirder( this );
}

bmfGirderTemplate* bmfPrecastGirderTemplate::CreateClone() const
{
   return new bmfPrecastGirderTemplate( *this );
}

void bmfPrecastGirderTemplate::SetStraightStrandPattern( const bmfStrandPattern& rPattern )
{
   m_StraightPattern = rPattern;
}

const bmfStrandPattern& bmfPrecastGirderTemplate::GetStraightStrandPattern() const
{
   return m_StraightPattern;
}

bmfStrandPattern& bmfPrecastGirderTemplate::GetStraightStrandPattern()
{
   return m_StraightPattern;
}

void bmfPrecastGirderTemplate::SetHarpedStrandPatternEnd(const bmfStrandPattern& rPtrn)
{
   m_EndPattern = rPtrn;
}

const bmfStrandPattern& bmfPrecastGirderTemplate::GetHarpedStrandPatternEnd() const
{
   return m_EndPattern;
}

bmfStrandPattern& bmfPrecastGirderTemplate::GetHarpedStrandPatternEnd()
{
   return m_EndPattern;
}

void bmfPrecastGirderTemplate::SetHarpedStrandPatternHP(const bmfStrandPattern& rPtrn)
{
   m_HPPattern = rPtrn;
}

const bmfStrandPattern& bmfPrecastGirderTemplate::GetHarpedStrandPatternHP() const
{
   return m_HPPattern;
}

bmfStrandPattern& bmfPrecastGirderTemplate::GetHarpedStrandPatternHP()
{
   return m_HPPattern;
}

void bmfPrecastGirderTemplate::SetTemporaryStrandPattern( const bmfStrandPattern& rPattern )
{
   m_TempPattern = rPattern;
}

const bmfStrandPattern& bmfPrecastGirderTemplate::GetTemporaryStrandPattern() const
{
   return m_TempPattern;
}

bmfStrandPattern& bmfPrecastGirderTemplate::GetTemporaryStrandPattern()
{
   return m_TempPattern;
}

const bmfLrLayout& bmfPrecastGirderTemplate::GetLrLayout() const
{
   return m_LrLayout;
}

void bmfPrecastGirderTemplate::SetLrLayout(const bmfLrLayout& rLayout)
{
   m_LrLayout = rLayout;
}

void bmfPrecastGirderTemplate::SetHarpPointLocation( Float64 hpLoc, bmfMeasuredFrom measFrom )
{
   // If hpLoc is really close to 0.50, the just force it here!
   if ( IsEqual( hpLoc, -0.50 ) )
      hpLoc = -0.50;

   // fractional measure (0,0.5] or absolute measure. Fractional measure < 0
   PRECONDITION( -0.5 <= hpLoc && hpLoc < 0 || 0 <= hpLoc );

   m_HpLoc = hpLoc;
   m_HpLocMeasuredFrom = measFrom;
}

Float64 bmfPrecastGirderTemplate::GetHarpPointLocation() const
{
   return m_HpLoc;
}

bmfMeasuredFrom bmfPrecastGirderTemplate::HarpPointLocationMeasuredFrom() const
{
   return m_HpLocMeasuredFrom;
}

IndexType bmfPrecastGirderTemplate::GetHarpingPointCount() const
{
   IndexType cHP = ( m_HpLoc < 0.5 ? 2 : 1 );
   return cHP;
}

//const bmfGirderProfile* bmfPrecastGirderTemplate::GetProfile() const
//{
//   // Cast to recover type information
//   const gmIPrecastBeam* pBeam;
//   pBeam = dynamic_cast<const gmIPrecastBeam*>( bmfGirderTemplate::GetShape() );
//   CHECK( pBeam != 0 );
//   return pBeam;
//}

gmIPrecastBeam* bmfPrecastGirderTemplate::CreateShape(Float64 distFromStart,Float64 length) const
{
   const bmfGirderProfile* pProfile = GetProfile();
   gmIShape* pShape = pProfile->CreateShape(distFromStart,length);
   gmIPrecastBeam* pBeam = dynamic_cast<gmIPrecastBeam*>(pShape);
   CHECK(pBeam != NULL);
   return pBeam;
}

void bmfPrecastGirderTemplate::SetConcrete(const matConcreteEx* pConc)
{
   m_pConc = pConc;
}

const matConcreteEx* bmfPrecastGirderTemplate::GetConcrete() const
{
   return m_pConc;
}

void bmfPrecastGirderTemplate::SetStrand(const matPsStrand* pStrand)
{
   m_pStrand = pStrand;
}

const matPsStrand* bmfPrecastGirderTemplate::GetStrand() const
{
   return m_pStrand;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfPrecastGirderTemplate::MakeCopy(const bmfPrecastGirderTemplate& rOther)
{
   m_StraightPattern   = rOther.m_StraightPattern;
   m_EndPattern        = rOther.m_EndPattern;
   m_HPPattern         = rOther.m_HPPattern;
   m_TempPattern       = rOther.m_TempPattern;
   m_HpLoc             = rOther.m_HpLoc;
   m_HpLocMeasuredFrom = rOther.m_HpLocMeasuredFrom;
   m_LrLayout          = rOther.m_LrLayout;
}

void bmfPrecastGirderTemplate::MakeAssignment(const bmfPrecastGirderTemplate& rOther)
{
   bmfGirderTemplate::MakeAssignment( rOther );
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


//======================== DEBUG      =======================================
#if defined _DEBUG
bool bmfPrecastGirderTemplate::AssertValid() const
{
   if ( m_HpLoc < 0 || 0.5 < m_HpLoc )
      return false;

   if ( !m_StraightPattern.AssertValid() )
      return false;

   if ( !m_HPPattern.AssertValid() )
      return false;

   if ( !m_EndPattern.AssertValid() )
      return false;

   if ( !m_TempPattern.AssertValid() )
      return false;

   return true;
}

void bmfPrecastGirderTemplate::Dump(dbgDumpContext& os) const
{
   ASSERTVALID;

   os << "Dump for bmfPrecastGirderTemplate" << endl;
   os << "Straight Strand Pattern" << endl;
   m_StraightPattern.Dump( os );
   os << endl;
   os << "End Strand Pattern" << endl;
   m_EndPattern.Dump( os );
   os << endl;
   os << "Harped Strand Pattern" << endl;
   m_HPPattern.Dump( os );
   os << endl;
   os << "LrLayout" << endl;
   m_LrLayout.Dump( os );
   os << endl;
   os << "m_HpLoc = " << m_HpLoc << endl;
   os << "m_HpLocMeasuredFrom = " << m_HpLocMeasuredFrom << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfPrecastGirderTemplate::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfPrecastGirderTemplate");

   bmfBundlePattern ptrn;

   TEST_NOT_IMPLEMENTED("bmfPrecastGirderTemplate");

   TESTME_EPILOG("bmfPrecastGirderTemplate");
}
#endif // _UNITTEST
