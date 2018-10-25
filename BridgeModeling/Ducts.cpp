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
   bmfDucts
****************************************************************************/

#include <BridgeModeling\Ducts.h>        // class implementation
#include <BridgeModeling\XBridgeModel.h>
#include <BridgeModeling\Girder.h>
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DIAG_DECLARE_GROUP( bmf )

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfDucts::bmfDucts()
{
   m_pGirder = 0;
   m_bEnableReflection = false;
}

bmfDucts::bmfDucts(const bmfDucts& rOther)
{
   MakeCopy( rOther );
}

bmfDucts::~bmfDucts()
{
}

//======================== OPERATORS  =======================================
bmfDucts& bmfDucts::operator=(const bmfDucts& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
void bmfDucts::EnableReflection(bool bEnable)
{
   m_bEnableReflection = bEnable;
}

bool bmfDucts::IsReflectionEnabled() const
{
   return m_bEnableReflection;
}

void bmfDucts::AddDuct(const bmfDuct& duct)
{
   m_Ducts.push_back(duct);

   Float64 x1,y1,x2,y2;
   duct.GetDuctPosition(&x1,&y1,&x2,&y2);
   if ( m_bEnableReflection == true && (0 < fabs(x1) || 0 < fabs(x2)) )
   {
      bmfDuct reflected_duct(duct);
      reflected_duct.SetDuctPosition(-x1,y1,-x2,y2);
      m_Ducts.push_back(reflected_duct);
   }
}

void bmfDucts::RemoveDuct(long index)
{
   m_Ducts.erase(m_Ducts.begin() + index);
}

void bmfDucts::RemoveAllDucts()
{
   m_Ducts.clear();
}

DuctIndexType bmfDucts::GetDuctCount() const
{
   return m_Ducts.size();
}

const bmfDuct& bmfDucts::GetDuct(DuctIndexType index) const
{
   CHECK( 0 <= index && index < m_Ducts.size() );
   return m_Ducts[index];
}

bmfDuct& bmfDucts::GetDuct(DuctIndexType index)
{
   CHECK( 0 <= index && index < m_Ducts.size() );
   return m_Ducts[index];
}

gpPoint2d bmfDucts::GetDuctLocation(DuctIndexType index,Float64 z) const
{
   const bmfDuct& duct = GetDuct(index);
   Float64 length = m_pGirder->GetLength();
   
   Float64 x,y;
   duct.GetDuctLocation(z,length,&x,&y);

   return gpPoint2d(x,y);
}

Float64 bmfDucts::GetDuctDiameter(DuctIndexType index) const
{
   const bmfDuct& duct = GetDuct(index);
   return duct.GetDuctDiameter();
}

StrandIndexType bmfDucts::GetMaxStrands() const
{
   StrandIndexType max = 0;
   std::vector<bmfDuct>::const_iterator iter;
   for ( iter = m_Ducts.begin(); iter != m_Ducts.end(); iter++ )
   {
      const bmfDuct& duct = *iter;
      max += duct.GetMaxStrands();
   }

   return max;
}

void bmfDucts::SetGirder(bmfGirder* pGirder)
{
   m_pGirder = pGirder;
}

void bmfDucts::SetNumStrands(DuctIndexType ductIndex,StrandIndexType nStrands)
{
   CHECK( 0 <= ductIndex && ductIndex < m_Ducts.size() );

   bmfDuct& duct = GetDuct(ductIndex);
   duct.SetNumStrands(nStrands);
}

StrandIndexType bmfDucts::GetNumStrands(DuctIndexType ductIndex) const
{
   CHECK( 0 <= ductIndex && ductIndex < m_Ducts.size() );

   const bmfDuct& duct = GetDuct(ductIndex);
   return duct.GetNumStrands();
}

StrandIndexType bmfDucts::GetNumStrands() const
{
   StrandIndexType nStrands = 0;
   std::vector<bmfDuct>::const_iterator iter;
   for ( iter = m_Ducts.begin(); iter != m_Ducts.end(); iter++ )
   {
      const bmfDuct& duct = *iter;
      nStrands += duct.GetNumStrands();
   }

   return nStrands;
}

gpPoint2d bmfDucts::GetPTCG(Float64 x) const
{
   gpPoint2d YA(0,0);
   Float64 length = m_pGirder->GetLength();
   StrandIndexType nStrands = 0;
   std::vector<bmfDuct>::const_iterator iter;
   for ( iter = m_Ducts.begin(); iter != m_Ducts.end(); iter++ )
   {
      const bmfDuct& duct = *iter;
      StrandIndexType ns = duct.GetNumStrands();
      gpPoint2d Y;
      duct.GetTendonCG(x,length,&Y.X(),&Y.Y());

      YA.X() += Y.X()*ns;
      YA.Y() += Y.Y()*ns;
      nStrands += ns;
   }

   if ( nStrands == 0 )
      return gpPoint2d(0,0);

   YA.X() /= nStrands;
   YA.Y() /= nStrands;

   return YA;
}

Float64 bmfDucts::GetDuctSlope(Float64 x,DuctIndexType ductIndex) const
{
   const bmfDuct& duct = GetDuct(ductIndex);
   Float64 length = m_pGirder->GetLength();
   return duct.GetDuctSlope(x,length);
}

void bmfDucts::GetDuctControlPoints(DuctIndexType ductIndex,gpPoint2d* pe1,gpPoint2d* pe2) const
{
   const bmfDuct& duct = GetDuct(ductIndex);

   Float64 x1, y1, x2, y2;
   duct.GetDuctPosition(&x1,&y1,&x2,&y2);

   pe1->X() = x1;
   pe1->Y() = y1;

   pe2->X() = x2;
   pe2->Y() = y2;
}

//void bmfDucts::GetDuctControlPoints(gpPoint2d* pe1,gpPoint2d* pe2) const
//{
//   Float64 area = 0;
//   Float64 x1_area = 0;
//   Float64 y1_area = 0;
//   Float64 x2_area = 0;
//   Float64 y2_area = 0;
//
//   Uint32 index = 0;
//   std::vector<bmfDuct>::const_iterator iter;
//   for ( iter = m_Ducts.begin(); iter != m_Ducts.end(); iter++, index++ )
//   {
//      const bmfDuct& duct = *iter;
//
//      Float64 x1,y1,x2,y2;
//      duct.GetDuctPosition(&x1,&y1,&x2,&y2);
//
//      Uint32 nStrands = duct.GetNumStrands();
//
//      x1_area += x1*nStrands;
//      y1_area += y1*nStrands;
//      x2_area += x2*nStrands;
//      y2_area += y2*nStrands;
//
//      area += nStrands;
//   }
//
//   if ( area != 0 )
//   {
//      *pe1 = gpPoint2d(x1_area/area,y1_area/area);
//      *pe2 = gpPoint2d(x2_area/area,y2_area/area);
//   }
//   else
//   {
//      *pe1 = gpPoint2d(0,0);
//      *pe2 = gpPoint2d(0,0);
//   }
//}

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void bmfDucts::MakeCopy( const bmfDucts& rOther)
{
   m_pGirder           = rOther.m_pGirder;
   m_Ducts             = rOther.m_Ducts;
   m_bEnableReflection = rOther.m_bEnableReflection;
}

void bmfDucts::MakeAssignment( const bmfDucts& rOther )
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
bool bmfDucts::AssertValid() const
{
   return true;
}

void bmfDucts::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfDucts" << endl;
}

#endif // _DEBUG

#if defined _UNITTEST
bool bmfDucts::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE( "bmfDucts" );
   TESTME_EPILOG( "bmfDucts" );
}
#endif // _UNITTEST

