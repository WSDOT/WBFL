///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#include <ReinforcedConcrete\ReinfConcLib.h>
#include <MathEx.h>
#include <iostream>
#include <ReinforcedConcrete\CapacitySolution.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rcaCapacitySolution
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rcaCapacitySolution::rcaCapacitySolution()
{
   // The default state of the solution is that of a "no capacity" beam.
   // The solver will have to supply a "more correct" beta 1, NaLine, are coordiates
   // for force resultants.
   m_P                    = 0.0;
   m_Mx                   = 0.0;
   m_My                   = 0.0;
   m_Beta1                = 0.0;
   m_NaLine               = WBFL::Geometry::Line2d(0.0,WBFL::Geometry::Vector2d(1.0,PI_OVER_2));
   m_CompFiberDist        = 0.0;
   m_CompBlockOffset      = 0.0;
   m_AreaAboveNeutralAxis = 0.0;
   m_CompBlockArea        = 0.0;
   m_CompRes              = 0.0;
   m_CompResLoc           = WBFL::Geometry::Point2d(0.0,0.0);
   m_TensRes              = 0.0;
   m_TensResLoc           = WBFL::Geometry::Point2d(0.0,0.0);
}

rcaCapacitySolution::rcaCapacitySolution(Float64 P,
                                         Float64 Mx,
                                         Float64 My,
                                         Float64 beta1,
                                         const WBFL::Geometry::Line2d& naLine,
                                         Float64 compFiberDist,
                                         Float64 compBlockOffset,
                                         Float64 areaAboveNeutralAxis,
                                         Float64 compBlockArea,
                                         Float64 compRes, const WBFL::Geometry::Point2d& compResLoc,
                                         Float64 tensRes, const WBFL::Geometry::Point2d& tensResLoc):
m_P(P),
m_Mx(Mx),
m_My(My),
m_Beta1(beta1),
m_NaLine(naLine),
m_CompFiberDist(compFiberDist),
m_CompBlockOffset(compBlockOffset),
m_AreaAboveNeutralAxis(areaAboveNeutralAxis),
m_CompBlockArea(compBlockArea),
m_CompRes(compRes),
m_CompResLoc(compResLoc),
m_TensRes(tensRes),
m_TensResLoc(tensResLoc)
{
   CHECK(compBlockArea>=0);
   CHECK(beta1>0);
}

rcaCapacitySolution::rcaCapacitySolution(const rcaCapacitySolution& rOther)
{
   MakeCopy(rOther);
}

rcaCapacitySolution::~rcaCapacitySolution()
{
}

//======================== OPERATORS  =======================================
rcaCapacitySolution& rcaCapacitySolution::operator= (const rcaCapacitySolution& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void rcaCapacitySolution::GetNeutralAxis(WBFL::Geometry::Line2d* line) const
{
   *line = m_NaLine;
}

void rcaCapacitySolution::SetNeutralAxis(const WBFL::Geometry::Line2d& line)
{
   m_NaLine = line;
}

Float64 rcaCapacitySolution::GetCompressionBlockBoundary() const
{
   return m_CompBlockOffset;
}

void rcaCapacitySolution::SetCompressionBlockBoundary(Float64 compBlockOffset)
{
   m_CompBlockOffset = compBlockOffset;
}

void rcaCapacitySolution::GetCompressionBlockBoundary(WBFL::Geometry::Line2d* line)
{
   *line = m_NaLine.Parallel(m_CompBlockOffset, WBFL::Geometry::Line2d::Side::Left);
}

Float64 rcaCapacitySolution::GetAxialForce() const
{
   return m_P;
}

void rcaCapacitySolution::SetAxialForce(Float64 p)
{
   m_P = p;
}

Float64 rcaCapacitySolution::GetMx() const
{
   return m_Mx;
}

void rcaCapacitySolution::SetMx(Float64 mx)
{
   m_Mx = mx;
}

Float64 rcaCapacitySolution::GetMy() const
{
   return m_My;
}

void rcaCapacitySolution::SetMy(Float64 my)
{
   m_My = my;
}

Float64 rcaCapacitySolution::GetCompFiberDistance() const
{
   return m_CompFiberDist;
}

void rcaCapacitySolution::SetCompFiberDistance(Float64 compFiberDist)
{
   m_CompFiberDist = compFiberDist;
}

void rcaCapacitySolution::GetForceRes(Float64* compRes, WBFL::Geometry::Point2d* compResLoc, 
                                      Float64* tensRes, WBFL::Geometry::Point2d* tensResLoc)const
{
   *compRes    = m_CompRes;
   *compResLoc = m_CompResLoc;
   *tensRes    = m_TensRes;
   *tensResLoc = m_TensResLoc;
}

void rcaCapacitySolution::SetForceRes(Float64 compRes, const WBFL::Geometry::Point2d& compResLoc, 
                                      Float64 tensRes, const WBFL::Geometry::Point2d& tensResLoc)
{
   m_CompRes    = compRes;
   m_CompResLoc = compResLoc;
   m_TensRes    = tensRes;
   m_TensResLoc = tensResLoc;
}

Float64 rcaCapacitySolution::GetBeta1() const
{
   return m_Beta1;
}

void rcaCapacitySolution::SetBeta1(Float64 beta1)
{
   m_Beta1 = beta1;
}

Float64 rcaCapacitySolution::GetAreaAboveNeutralAxis() const
{
   return m_AreaAboveNeutralAxis;
}

void rcaCapacitySolution::SetAreaAboveNeutralAxis(Float64 areaAboveNeutralAxis)
{
   m_AreaAboveNeutralAxis = areaAboveNeutralAxis;
}

Float64 rcaCapacitySolution::GetCompressionBlockArea() const
{
   return m_CompBlockArea;
}

void rcaCapacitySolution::SetCompressionBlockArea(Float64 compBlockArea)
{
   m_CompBlockArea = compBlockArea;
}

Float64 rcaCapacitySolution::GetCompressionBlockDepth() const
{
   return m_CompFiberDist - m_CompBlockOffset;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rcaCapacitySolution::AssertValid() const
{
   return true;
}

void rcaCapacitySolution::Dump(dbgDumpContext& os) const
{
   os << "Dump for rcaCapacitySolution" << endl;
   os << " m_P              ="<<m_P              <<endl;
   os << " m_Mx             ="<<m_Mx             <<endl;
   os << " m_My             ="<<m_My             <<endl;
   os << " m_Beta1          ="<<m_Beta1          <<endl;
   os << " m_NaLine         ="; m_NaLine.Dump(os);
   os << " m_CompFiberDist  ="<<m_CompFiberDist  <<endl;
   os << " m_CompBlockOffset="<<m_CompBlockOffset<<endl;
   os << " m_CompRes        ="<<m_CompRes        <<endl;
   os << " m_CompResLoc     ="; m_CompResLoc.Dump(os);
   os << " m_TensRes        ="<<m_TensRes        <<endl;
   os << " m_TensResLoc     ="; m_TensResLoc.Dump(os);
}
#endif // _DEBUG


#if defined _UNITTEST
bool rcaCapacitySolution::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rcaCapacitySolution");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for rcaCapacitySolution");
   TESTME_EPILOG("rcaCapacitySolution");
}
#endif



////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rcaCapacitySolution::MakeCopy(const rcaCapacitySolution& rOther)
{
   m_P                    = rOther.m_P;
   m_Mx                   = rOther.m_Mx;
   m_My                   = rOther.m_My;
   m_Beta1                = rOther.m_Beta1;
   m_NaLine               = rOther.m_NaLine;
   m_CompFiberDist        = rOther.m_CompFiberDist;
   m_CompBlockOffset      = rOther.m_CompBlockOffset;
   m_AreaAboveNeutralAxis = rOther.m_AreaAboveNeutralAxis;
   m_CompBlockArea        = rOther.m_CompBlockArea;
   m_CompRes              = rOther.m_CompRes;
   m_CompResLoc           = rOther.m_CompResLoc;
   m_TensRes              = rOther.m_TensRes;
   m_TensResLoc           = rOther.m_TensResLoc;
}

void rcaCapacitySolution::MakeAssignment(const rcaCapacitySolution& rOther)
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


