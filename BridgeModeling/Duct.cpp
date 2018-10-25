///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2015  Washington State Department of Transportation
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
   bmfDuct
****************************************************************************/

#include <BridgeModeling\Duct.h>        // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DIAG_DECLARE_GROUP( bmf )

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfDuct::bmfDuct(Float64 x1,Float64 y1, Float64 x2,Float64 y2, Float64 diaDuct,Float64 diaStrand,Float64 maxEccentricity,Uint32 nStrands,Uint32 maxStrands)
{
   m_X1 = x1;
   m_Y1 = y1;
   m_X2 = x2;
   m_Y2 = y2;
   m_DuctDiameter = diaDuct;
   m_StrandDiameter = diaStrand;
   m_Ecc = maxEccentricity;
   m_nStrands = nStrands;
   m_MaxStrands = maxStrands;
}

bmfDuct::bmfDuct(const bmfDuct& rOther)
{
   MakeCopy( rOther );
}

bmfDuct::~bmfDuct()
{
}

//======================== OPERATORS  =======================================
bmfDuct& bmfDuct::operator=(const bmfDuct& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
Float64 bmfDuct::GetDuctDiameter() const
{
   return m_DuctDiameter;
}

void bmfDuct::SetDuctDiameter(Float64 dia)
{
   m_DuctDiameter = dia;
}

Float64 bmfDuct::GetStrandDiameter() const
{
   return m_StrandDiameter;
}

void bmfDuct::SetStrandDiameter(Float64 dia)
{
   m_StrandDiameter = dia;
}

Float64 bmfDuct::GetMaxTendonEccentricity() const
{
   return m_Ecc;
}

void bmfDuct::SetMaxTendonEccentricity(Float64 ecc)
{
   m_Ecc = ecc;
}

void bmfDuct::GetDuctPosition(Float64* px1,Float64* py1,Float64* px2,Float64* py2) const
{
   *px1 = m_X1;
   *py1 = m_Y1;
   *px2 = m_X2;
   *py2 = m_Y2;
}

void bmfDuct::SetDuctPosition(Float64 x1,Float64 y1, Float64 x2,Float64 y2)
{
   m_X1 = x1;
   m_Y1 = y1;
   m_X2 = x2;
   m_Y2 = y2;
}

StrandIndexType bmfDuct::GetMaxStrands() const
{
   return m_MaxStrands;
}

void bmfDuct::SetMaxStrands(StrandIndexType max)
{
   m_MaxStrands = max;
}

StrandIndexType bmfDuct::GetNumStrands() const
{
   return m_nStrands;
}

void bmfDuct::SetNumStrands(StrandIndexType nStrands)
{
   if ( nStrands <= m_MaxStrands )
      m_nStrands = nStrands;
}

void bmfDuct::GetDuctLocation(Float64 z,Float64 L,Float64 *pX,Float64 *pY) const
{
   Float64 y = 4*(m_Y1 - m_Y2)*z*z/(L*L) - 4*(m_Y1 - m_Y2)*z/L + m_Y1;
   Float64 x = 4*(m_X1 - m_X2)*z*z/(L*L) - 4*(m_X1 - m_X2)*z/L + m_X1;

   *pX = x;
   *pY = y;
}

Float64 bmfDuct::GetDuctSlope(Float64 z,Float64 L) const
{
   gpPoint2d pnt_e1(m_X1,m_Y1), pnt_e2(m_X2,m_Y2);

   Float64 e1 = pnt_e1.Magnitude();
   Float64 e2 = pnt_e2.Magnitude();

   Float64 slope = 8*(e1 - e2)*z/(L*L) - 4*(e1 - e2)/L;

   return slope;
}

void bmfDuct::GetTendonCG(Float64 z,Float64 L,Float64 *pX,Float64 *pY) const
{
   Float64 x,y;
   GetDuctLocation(z,L,&x,&y);

   // Adjust for tendon eccentricity within the duct
   Float64 Emax = (m_DuctDiameter - m_StrandDiameter)/2;
   Float64 Emin = m_Ecc;

   // Eccentricity at centerline of the span
   Float64 n = (Float64)m_nStrands;
   Float64 N = (Float64)m_MaxStrands;
   Float64 Ecl = (n - 1)*Emin/(N - 1) + (N - n)*Emax/(N - 1);

   // Adjust for position along girder
   Float64 e;
   if ( z < L/2 )
   {
      e = 2*Ecl*z/L;
   }
   else
   {
      e = 2*Ecl*(1 - z/L);
   }

   // Adjust for slope tendon plane
#pragma Reminder("Adjust tendon eccentricty of slope of tendon plane")

   // using dummy values
   Float64 ex = 0;
   Float64 ey = e;

   // NOTE: Assumes parabolic duct... Strands at top of duct
   x += ex;
   y += ey;

   *pX = x;
   *pY = y;
}

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void bmfDuct::MakeCopy( const bmfDuct& rOther)
{
   m_X1             = rOther.m_X1;
   m_Y1             = rOther.m_Y1;
   m_X2             = rOther.m_X2;
   m_Y2             = rOther.m_Y2;
   m_DuctDiameter   = rOther.m_DuctDiameter;
   m_StrandDiameter = rOther.m_StrandDiameter;
   m_Ecc            = rOther.m_Ecc;
   m_nStrands       = rOther.m_nStrands;
   m_MaxStrands     = rOther.m_MaxStrands;
}

void bmfDuct::MakeAssignment( const bmfDuct& rOther )
{
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

#if defined _DEBUG
bool bmfDuct::AssertValid() const
{
   return true;
}

void bmfDuct::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfDuct" << endl;
}

#endif // _DEBUG

#if defined _UNITTEST
bool bmfDuct::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE( "bmfDuct" );
   TESTME_EPILOG( "bmfDuct" );
}
#endif // _UNITTEST
