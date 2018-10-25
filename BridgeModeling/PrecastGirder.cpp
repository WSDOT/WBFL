///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfPrecastGirder
****************************************************************************/

#include <BridgeModeling\PrecastGirder.h>        // class implementation
#include <BridgeModeling\Span.h>
#include <BridgeModeling\Pier.h>
#include <BridgeModeling\Connection.h>
#include <BridgeModeling\PrecastGirderSection.h>
#include <GeomModel\Section.h>
#include <algorithm>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DIAG_DECLARE_GROUP( bmf )

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfPrecastGirder::bmfPrecastGirder(bmfPrecastGirderTemplate* pTpl) :
bmfGirder( pTpl )
{
   m_EndPtrn = pTpl->GetHarpedStrandPatternEnd();
   m_HPPtrn = pTpl->GetHarpedStrandPatternHP();
   m_SsPtrn = pTpl->GetStraightStrandPattern();
   m_TmpPtrn = pTpl->GetTemporaryStrandPattern();
   
   m_EndPtrn.RemoveAllStrands();
   m_HPPtrn.RemoveAllStrands();
   m_SsPtrn.RemoveAllStrands();
   m_TmpPtrn.RemoveAllStrands();

   m_LrLayout = pTpl->GetLrLayout();
   m_LrLayout.SetGirder(this);
}

bmfPrecastGirder::bmfPrecastGirder(const bmfPrecastGirder& rOther) :
bmfGirder( rOther )
{
   m_EndPtrn.RemoveAllStrands();
   m_HPPtrn.RemoveAllStrands();
   m_SsPtrn.RemoveAllStrands();
   m_TmpPtrn.RemoveAllStrands();

   MakeCopy( rOther );
}

bmfPrecastGirder::~bmfPrecastGirder()
{
}

//======================== OPERATORS  =======================================
bmfPrecastGirder& bmfPrecastGirder::operator=(const bmfPrecastGirder& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================

void bmfPrecastGirder::PlanView(HDC hDC,const grlibPointMapper& mapper) const
{
   WATCHX( bmf, BMF_LEVEL_DRAW, "Drawing girder " << GetGirderPath()->GetGirderIdx() );
   bmfGirder::PlanView( hDC, mapper );

   // Draw the top flange of the girder
   POINT points[5];
   mapper.WPtoDP( m_StartLeft,  &points[0].x, &points[0].y );
   mapper.WPtoDP( m_EndLeft,    &points[1].x, &points[1].y );
   mapper.WPtoDP( m_EndRight,   &points[2].x, &points[2].y );
   mapper.WPtoDP( m_StartRight, &points[3].x, &points[3].y );
   points[4] = points[0]; // Close the polgon.
   ::Polyline( hDC, points, 5 );
}

gpRect2d bmfPrecastGirder::GetBoundingBox() const
{
   Float64 slx, sly; // start left;
   Float64 srx, sry; // start right;
   Float64 elx, ely; // end left
   Float64 erx, ery; // end right;

   m_StartLeft->get_X(&slx);   m_StartLeft->get_Y(&sly);
   m_StartRight->get_X(&srx);  m_StartRight->get_Y(&sry);
   m_EndLeft->get_X(&elx);     m_EndLeft->get_Y(&ely);
   m_EndRight->get_X(&erx);    m_EndRight->get_Y(&ery);

   return gpRect2d( min( min(slx, elx),    // left
                         min(srx, erx) ),
                    min( min(sly, ely),    // bottom
                         min(sry, ery) ),
                    max( max(slx, elx),    // right
                         max(srx, erx) ),
                    max( max(sly, ely),    // top
                         max(sry, ery) ) );
}

void bmfPrecastGirder::OnGirderPathChanged()
{
   bmfGirder::OnGirderPathChanged();
   UpdateTopFlangeCorners();
}

bmfIGirderSection* bmfPrecastGirder::CreateGirderSection(Float64 distFromStart) const
{
   std::auto_ptr<gmIPrecastBeam> pBeam( GetTemplate()->CreateShape(distFromStart,GetLength()) );
   CHECK( pBeam.get() != 0 );

   const matConcreteEx* pConc = GetTemplate()->GetConcrete();
   CHECK( pConc != 0 );

#pragma Reminder("Should the girder section account for strands?")

   bmfIGirderSection* p_section = new bmfPrecastGirderSection( pBeam.get(), pConc );

   return p_section;
}

//======================== ACCESS     =======================================
const matConcreteEx* bmfPrecastGirder::GetConcrete() const
{
   return GetTemplate()->GetConcrete();
}

const matPsStrand* bmfPrecastGirder::GetStrand() const
{
   return GetTemplate()->GetStrand();
}

bmfStrandPattern bmfPrecastGirder::GetStraightStrandPattern() const
{
   return m_SsPtrn;
}

bmfStrandPattern bmfPrecastGirder::GetEndStrandPattern() const
{
   return m_EndPtrn;
}

bmfStrandPattern bmfPrecastGirder::GetHPStrandPattern() const
{
   return m_HPPtrn;
}

Float64 bmfPrecastGirder::GetHarpedStrandEccentricity( Float64 distFromStart ) const
{
   return GetHarpedStrandEccentricity( GetNumHarpedStrands(), distFromStart, m_EndShift, m_HpShift );
}

Float64 bmfPrecastGirder::GetHarpedStrandEccentricity( StrandIndexType nStrands, Float64 distFromStart, const gpSize2d& endShift, const gpSize2d& hpShift ) const
{
   if ( nStrands == 0 )
      return 0;

   PRECONDITION( distFromStart <= GetLength() + TOLERANCE );

   // NOTE: Remember that CG's are measured from the bottom center of the girder.

   // Get the CG's of the harped strands at the end of the girder and
   // at the harping points.
   gpPoint2d cg_end = m_EndPtrn.GetCenterOfGravity( nStrands );
   gpPoint2d cg_hp  = m_HPPtrn.GetCenterOfGravity( nStrands );

   // Adjust CG's for strand pattern offsets
   cg_end -= endShift; // lower ends
   cg_hp  += hpShift; // raise hp

   CHECK( IsZero(cg_end.X()) );
   CHECK( IsZero(cg_hp.X()) );

   Float64 length = GetLength();

   // Get the girder properties
   const bmfPrecastGirderTemplate* pTpl = GetTemplate();
   std::auto_ptr<gmIPrecastBeam> pBeam(pTpl->CreateShape(distFromStart,length));
   gmProperties prop;
   pBeam->GetProperties( &prop );

   // Get the harping point locations
   Float64 hp1, hp2;
   GetHarpingPointLocations( &hp1, &hp2 );
   CHECK( !IsZero( hp1 ) );
   CHECK( !IsEqual( hp2, length ) );

   Float64 cgY;
   if ( distFromStart < hp1 )
   {
      // Requested location is left of the first harping point
      cgY = distFromStart*(cg_hp.Y() - cg_end.Y())/hp1 + cg_end.Y();
   }
   else if ( distFromStart > hp2 )
   {
      // Requested location is right of the second harping point
      cgY = (cg_end.Y() - cg_hp.Y())*(distFromStart-hp2)/(length-hp2) + cg_hp.Y();
   }
   else
   {
      // Requested location is between harping points
      CHECK( hp1 <= distFromStart && distFromStart <= hp2 );
      cgY = cg_hp.Y();
   }

   Float64 ecc;
   ecc = fabs(prop.Ybottom()) - cgY;
   return ecc;
}

Float64 bmfPrecastGirder::GetStraightStrandEccentricity( Float64 distFromStart ) const
{
   return GetStraightStrandEccentricity( GetNumStraightStrands(), distFromStart );
}

Float64 bmfPrecastGirder::GetStraightStrandEccentricity( StrandIndexType nStrands, Float64 distFromStart ) const
{
   // Get the CG of the straight strand pattern for nStrands.
   // The CG is measured up from the bottom of the girder.
   if (nStrands==0)
      return 0.0;
   else
   {
      gpPoint2d cg = m_SsPtrn.GetCenterOfGravity( nStrands );

      CHECK( IsZero(cg.X()) );

      const bmfPrecastGirderTemplate* pTpl = GetTemplate();
      std::auto_ptr<gmIPrecastBeam> pBeam(pTpl->CreateShape(distFromStart,GetLength()));
      gmProperties prop;
      pBeam->GetProperties( &prop );

      Float64 ecc = fabs(prop.Ybottom()) - cg.Y();
      return ecc;
   }
}

Float64 bmfPrecastGirder::GetTemporaryStrandEccentricity( Float64 distFromStart ) const
{
   return GetTemporaryStrandEccentricity( GetNumTemporaryStrands(), distFromStart );
}

Float64 bmfPrecastGirder::GetTemporaryStrandEccentricity( StrandIndexType nStrands, Float64 distFromStart ) const
{
   // Get the CG of the straight strand pattern for nStrands.
   // The CG is measured up from the bottom of the girder.
   if (nStrands==0)
      return 0.0;
   else
   {
      gpPoint2d cg = m_TmpPtrn.GetCenterOfGravity( nStrands );

      CHECK( IsZero(cg.X()) );

      const bmfPrecastGirderTemplate* pTpl = GetTemplate();
      std::auto_ptr<gmIPrecastBeam> pBeam(pTpl->CreateShape(distFromStart,GetLength()));
      gmProperties prop;
      pBeam->GetProperties( &prop );

      Float64 ecc = fabs(prop.Ybottom()) - cg.Y();
      return ecc;
   }
}

Float64 bmfPrecastGirder::GetStrandEccentricity( Float64 distFromStart, bool bIncTemp ) const
{
   StrandIndexType nStraight = GetNumStraightStrands();
   StrandIndexType nHarped   = GetNumHarpedStrands();
   StrandIndexType nTemp     = bIncTemp ? GetNumTemporaryStrands() : 0;
   return GetStrandEccentricity( nStraight, nHarped, nTemp, distFromStart, m_EndShift, m_HpShift );
}

Float64 bmfPrecastGirder::GetStrandEccentricity( StrandIndexType nStraight, StrandIndexType nHarped, StrandIndexType nTemp, Float64 distFromStart, const gpSize2d& endShift, const gpSize2d& hpShift  ) const
{
   if ( nStraight == 0 && nHarped == 0 && nTemp == 0)
      return 0.0;

   Float64 ss_ecc;
   Float64 hs_ecc;
   Float64 tmp_ecc;
   Float64 ttl_ecc;

   ss_ecc  = GetStraightStrandEccentricity( nStraight, distFromStart );
   hs_ecc  = GetHarpedStrandEccentricity( nHarped, distFromStart, endShift, hpShift );
   tmp_ecc = GetTemporaryStrandEccentricity( nTemp, distFromStart );

   ttl_ecc = ((nStraight*ss_ecc) + (nHarped*hs_ecc) + (nTemp*tmp_ecc)) / ( nStraight + nHarped + nTemp );

   return ttl_ecc;
}

gpPoint2d bmfPrecastGirder::GetStraightStrandPosition(Float64 distFromStart, StrandIndexType strIdx) const
{
   return m_SsPtrn.GetStrandPoint( strIdx );
}

gpPoint2d bmfPrecastGirder::GetStraightStrandPoint(Float64 distFromStart, StrandIndexType strIdx) const
{
   return m_SsPtrn.GetStrandPatternPoint( strIdx );
}

gpPoint2d bmfPrecastGirder::GetTemporaryStrandPosition(Float64 distFromStart, StrandIndexType strIdx) const
{
   return m_TmpPtrn.GetStrandPoint( strIdx );
}

gpPoint2d bmfPrecastGirder::GetTemporaryStrandPoint(Float64 distFromStart, StrandIndexType strIdx) const
{
   return m_TmpPtrn.GetStrandPatternPoint( strIdx );
}

gpPoint2d bmfPrecastGirder::GetHarpedStrandPosition(Float64 distFromStart, StrandIndexType strIdx) const
{
   return GetHarpedStrandPosition(distFromStart,strIdx,m_EndShift,m_HpShift);
}

gpPoint2d bmfPrecastGirder::GetHarpedStrandPoint(Float64 distFromStart, StrandIndexType strIdx) const
{
   return GetHarpedStrandPoint(distFromStart,strIdx,m_EndShift,m_HpShift);
}

gpPoint2d bmfPrecastGirder::GetHarpedStrandPoint(Float64 distFromStart, StrandIndexType strIdx,StrandIndexType numHarpedStrands) const
{
   return GetHarpedStrandPoint(distFromStart,strIdx,m_EndShift,m_HpShift,numHarpedStrands);
}

gpPoint2d bmfPrecastGirder::GetHarpedStrandPosition(Float64 distFromStart, StrandIndexType strIdx,const gpSize2d& endShift,const gpSize2d& hpShift) const
{
   return GetHarpedStrandPoint(distFromStart, strIdx, endShift, hpShift);
} 

gpPoint2d bmfPrecastGirder::GetHarpedStrandPoint(Float64 distFromStart, StrandIndexType strIdx,const gpSize2d& endShift,const gpSize2d& hpShift) const
{
   return GetHarpedStrandPoint(distFromStart, strIdx, endShift, hpShift, GetNumHarpedStrands());
}

gpPoint2d bmfPrecastGirder::GetHarpedStrandPoint(Float64 distFromStart, StrandIndexType strIdx,const gpSize2d& endShift,const gpSize2d& hpShift,StrandIndexType numHarpedStrands) const
{

   gpPoint2d pnt;

   const bmfPrecastGirderTemplate* pTpl = GetTemplate();

   // Get the harping point locations
   Float64 hp1, hp2;
   GetHarpingPointLocations( &hp1, &hp2 );
   CHECK( !IsZero( hp1 ) );
   CHECK( !IsEqual( hp2, GetLength() ) );

   if ( distFromStart < hp1 )
   {
      // Requested location is left of the first harping point
      gpPoint2d end_pnt = m_EndPtrn.GetStrandPoint( strIdx );
      gpPoint2d hp_pnt = m_HPPtrn.GetStrandPoint( numHarpedStrands - strIdx - 1 );
      hp_pnt.X() *= -1;

      Float64 dx, dy;
      dx = hp_pnt.X() - end_pnt.X();
      dy = hp_pnt.Y() - end_pnt.Y();

      gpSize2d shiftHP;
      shiftHP.Dy() = hpShift.Dy();
      shiftHP.Dx() = hpShift.Dy()*dx/dy;

      gpSize2d shiftEnd;
      shiftEnd.Dy() = endShift.Dy();
      shiftEnd.Dx() = endShift.Dy()*dx/dy;

      hp_pnt += shiftHP;
      end_pnt -= shiftEnd;

      pnt.X() = distFromStart*(hp_pnt.X() - end_pnt.X())/hp1 + end_pnt.X();
      pnt.Y() = distFromStart*(hp_pnt.Y() - end_pnt.Y())/hp1 + end_pnt.Y();
   }
   else if ( distFromStart > hp2 )
   {
      // Requested location is right of the second harping point
      gpPoint2d end_pnt = m_EndPtrn.GetStrandPoint( strIdx );

      gpPoint2d hp_pnt = m_HPPtrn.GetStrandPoint( numHarpedStrands - strIdx - 1);
      hp_pnt.X() *= -1;


      Float64 dx, dy;
      dx = hp_pnt.X() - end_pnt.X();
      dy = hp_pnt.Y() - end_pnt.Y();

      gpSize2d shiftHP;
      shiftHP.Dy() = hpShift.Dy();
      shiftHP.Dx() = hpShift.Dy()*dx/dy;

      gpSize2d shiftEnd;
      shiftEnd.Dy() = endShift.Dy();
      shiftEnd.Dx() = endShift.Dy()*dx/dy;

      hp_pnt += shiftHP;
      end_pnt -= shiftEnd;

      pnt.X() = (end_pnt.X() - hp_pnt.X())*(distFromStart-hp2)/(GetLength()-hp2) + hp_pnt.X();
      pnt.Y() = (end_pnt.Y() - hp_pnt.Y())*(distFromStart-hp2)/(GetLength()-hp2) + hp_pnt.Y();
   }
   else
   {
      // Requested location is between harping points
      CHECK( hp1 <= distFromStart && distFromStart <= hp2 );

      gpPoint2d end_pnt = m_EndPtrn.GetStrandPoint( strIdx );
      gpPoint2d hp_pnt  = m_HPPtrn.GetStrandPoint( numHarpedStrands - strIdx - 1);
      hp_pnt.X() *= -1;

      Float64 dx, dy;
      dx = hp_pnt.X() - end_pnt.X();
      dy = hp_pnt.Y() - end_pnt.Y();

      gpSize2d shiftHP;
      shiftHP.Dy() = hpShift.Dy();
      shiftHP.Dx() = hpShift.Dy()*dx/dy;

      gpSize2d shiftEnd;
      shiftEnd.Dy() = endShift.Dy();
      shiftEnd.Dx() = endShift.Dy()*dx/dy;

      hp_pnt += shiftHP;
      end_pnt -= shiftEnd;

      pnt = hp_pnt;
   }

   return pnt;
}

Float64 bmfPrecastGirder::GetHarpedStrandSlope( Float64 distFromStart ) const
{
   return GetHarpedStrandSlope( GetNumHarpedStrands(), distFromStart, m_EndShift, m_HpShift );
}

Float64 bmfPrecastGirder::GetHarpedStrandSlope( StrandIndexType nStrands, Float64 distFromStart,const gpSize2d& endShift,const gpSize2d& hpShift  ) const
{
   if ( nStrands == 0 )
      return Float64_Max;

   Float64 slope;

   // Get the harping point locations
   Float64 hp1, hp2;
   GetHarpingPointLocations( &hp1, &hp2 );
   CHECK( !IsZero( hp1 ) );
   CHECK( !IsEqual( hp2, GetLength() ) );

   if ( distFromStart < hp1 )
   {
      // Requested location is left of the first harping point
      Float64 ecc_end = GetHarpedStrandEccentricity( nStrands, 0.00, endShift, hpShift );
      Float64 ecc_hp  = GetHarpedStrandEccentricity( nStrands, hp1, endShift, hpShift );

      slope = hp1 / (ecc_hp - ecc_end);
   }
   else if ( hp2 < distFromStart )
   {
      // Requested location is right of the second harping point

      Float64 ecc_end = GetHarpedStrandEccentricity( GetLength() );
      Float64 ecc_hp  = GetHarpedStrandEccentricity( hp2 );

      slope = ( GetLength() - hp2 ) / ( ecc_hp - ecc_end );
   }
   else
   {
      // Requested location is between harping points
      CHECK( hp1 <= distFromStart && distFromStart <= hp2 );
      slope = Float64_Max;
   }

   return slope;
}

StrandIndexType bmfPrecastGirder::GetMaxStraightStrands() const
{
   return m_SsPtrn.GetMaxStrandCount();
}

StrandIndexType bmfPrecastGirder::GetMaxTemporaryStrands() const
{
   return m_TmpPtrn.GetMaxStrandCount();
}

StrandIndexType bmfPrecastGirder::GetMaxHarpedStrands() const
{
   return m_EndPtrn.GetMaxStrandCount();
}

StrandIndexType bmfPrecastGirder::GetMaxStrands(bool bIncTemp) const
{
   StrandIndexType nMax = GetMaxStraightStrands() + GetMaxHarpedStrands();
   if ( bIncTemp )
      nMax += GetMaxTemporaryStrands();

   return nMax;
}

bool bmfPrecastGirder::AddHarpedStrand()
{
   if ( m_EndPtrn.AddStrand() == 0 || m_HPPtrn.AddStrand() == 0 )
      return false;

   return true;
}

bool bmfPrecastGirder::AddStraightStrand()
{
   if ( m_SsPtrn.AddStrand() == 0 )
      return false;

   return true;
}

bool bmfPrecastGirder::AddTemporaryStrand()
{
   if ( m_TmpPtrn.AddStrand() == 0 )
      return false;

   return true;
}


bool bmfPrecastGirder::RemoveHarpedStrand()
{
   if ( m_EndPtrn.RemoveStrand() == 0 || m_HPPtrn.RemoveStrand() == 0 )
      return false;

   return true;
}

bool bmfPrecastGirder::RemoveStraightStrand()
{
   if ( m_SsPtrn.RemoveStrand() == 0 )
      return false;

   return true;
}

bool bmfPrecastGirder::RemoveTemporaryStrand()
{
   if ( m_TmpPtrn.RemoveStrand() == 0 )
      return false;

   return true;
}

StrandIndexType bmfPrecastGirder::SetNumHarpedStrands( StrandIndexType nStrands )
{
   StrandIndexType outcome = m_EndPtrn.SetStrandCount( nStrands );
   StrandIndexType outcome2 = m_HPPtrn.SetStrandCount( nStrands );
   CHECK(outcome == outcome2);
   return outcome;
}

StrandIndexType bmfPrecastGirder::SetNumStraightStrands( StrandIndexType nStrands )
{
   StrandIndexType outcome = m_SsPtrn.SetStrandCount( nStrands );
   return outcome;
}

StrandIndexType bmfPrecastGirder::SetNumTemporaryStrands( StrandIndexType nStrands )
{
   StrandIndexType outcome = m_TmpPtrn.SetStrandCount( nStrands );
   return outcome;
}

StrandIndexType bmfPrecastGirder::GetNumStraightStrands() const
{
   return m_SsPtrn.GetStrandCount();
}

StrandIndexType bmfPrecastGirder::GetNumHarpedStrands() const
{
   CHECK(m_EndPtrn.GetStrandCount() == m_HPPtrn.GetStrandCount());
   return m_EndPtrn.GetStrandCount();
}

StrandIndexType bmfPrecastGirder::GetNumTemporaryStrands() const
{
   return m_TmpPtrn.GetStrandCount();
}

void bmfPrecastGirder::ShiftHarpedStrandPattern(Float64 dy)
{
   m_EndShift.Dy() = dy;
}

Float64 bmfPrecastGirder::GetHarpedStrandPatternShift() const
{
   return m_EndShift.Dy();
}

void bmfPrecastGirder::ShiftBundlePattern(Float64 dy)
{
   m_HpShift.Dy() = dy;
}

Float64 bmfPrecastGirder::GetBundlePatternShift() const
{
   return m_HpShift.Dy();
}

void bmfPrecastGirder::ResetHarpedStrandShift()
{
   m_EndShift = gpSize2d(0,0);
   m_HpShift  = gpSize2d(0,0);
}

Uint32 bmfPrecastGirder::GetHarpingPointCount() const
{
   return GetTemplate()->GetHarpingPointCount();
}

void bmfPrecastGirder::GetHarpingPointLocations(Float64* pHpLoc1, Float64* pHpLoc2) const
{
   Float64 x = GetTemplate()->GetHarpPointLocation();
   Float64 left_end_size = GetLeftEndSize();
   Float64 right_end_size = GetRightEndSize();
   Float64 len;
   
   if ( x < 0 )
   {
      // Fractional...
      x *= -1.0;
      switch( GetTemplate()->HarpPointLocationMeasuredFrom() )
      {
      case LeftEnd:
      case RightEnd:
         len = GetLength();
         *pHpLoc1 = x*len;
         *pHpLoc2 = (1.0-x)*len;
         break;

      case LeftBearing:
         len = GetSpanLength();
         *pHpLoc1 = x*len + left_end_size;
         *pHpLoc2 = (1.0-x)*len + left_end_size;
         break;

      case RightBearing:
         len = GetSpanLength();
         *pHpLoc1 = GetLength() - ((1.0 - x)*len + right_end_size);
         *pHpLoc2 = GetLength() - (x*len + right_end_size);
         break;
      }
   }
   else
   {
      // absolute measure
      switch( GetTemplate()->HarpPointLocationMeasuredFrom() )
      {
      case LeftEnd:
      case RightEnd:
         len = GetLength();
         if ( len/2.0 < x )
         {
            // beyond midspan so force HP to midspan
            *pHpLoc1 = len/2.0;
            *pHpLoc2 = len/2.0;
         }
         else
         {
            *pHpLoc1 = x;
            *pHpLoc2 = len - x;
         }
         break;

      case LeftBearing:
      case RightBearing:
         len = GetSpanLength();
         if ( len/2 + left_end_size < x )
         {
            // beyond midspan so force HP to midspan
            *pHpLoc1 = (left_end_size + len + right_end_size)/2;
            *pHpLoc2 = (left_end_size + len + right_end_size)/2;
         }
         else
         {
            *pHpLoc1 = x + left_end_size;
            *pHpLoc2 = left_end_size + len - x;
         }
         break;
      }
   }

   CHECK( *pHpLoc1 <= *pHpLoc2 );
}

const bmfPrecastGirderTemplate* bmfPrecastGirder::GetTemplate() const
{
   // Cast to recover type information.
   // We only allow bmfPrecastGirderTemplates in.  If this cast fails
   // then something is really wrong.
   const bmfPrecastGirderTemplate* pTpl;
   pTpl = dynamic_cast<const bmfPrecastGirderTemplate*>( bmfGirder::GetTemplate() );
   CHECK( pTpl != 0 );
   return pTpl;
}

bmfPrecastGirderTemplate* bmfPrecastGirder::GetTemplate()
{
   // Cast to recover type information.
   // We only allow bmfPrecastGirderTemplates in.  If this cast fails
   // then something is really wrong.
   bmfPrecastGirderTemplate* pTpl;
   pTpl = dynamic_cast<bmfPrecastGirderTemplate*>( bmfGirder::GetTemplate() );
   CHECK( pTpl != 0 );
   return pTpl;
}

const bmfLrLayout& bmfPrecastGirder::GetLrLayout() const
{
   return m_LrLayout;
}

void bmfPrecastGirder::SetLrLayout(const bmfLrLayout& rLayout)
{
   m_LrLayout = rLayout;
}
//
//Uint32 bmfPrecastGirder::GetNumberOfBundles() const
//{
//   return m_Bundle.GetBundleCount();
//}
//
//Float64 bmfPrecastGirder::GetBundlePosition(Uint32 bundleIdx) const
//{
//   return m_Bundle.GetBundleHeight(bundleIdx);
//}
//
//Int16 bmfPrecastGirder::GetMaxStrandsInBundle(Uint32 bundleIdx) const
//{
//   return m_Bundle.GetMaxStrandCount(bundleIdx);
//}

//======================== INQUIRY    =======================================

//#if defined _DEBUG
//void bmfPrecastGirder::Dump(std::ostream& os)
//{
//   bmfGirder::Dump( os );
//
//
//   os << "# Straight Strands : " << m_NumStraightStrands << std::endl;
//   os << "# Harped   Strands : " << m_NumHarpedStrands << std::endl;
//   os << std::endl;
//
//   os << "Harping Points" << std::endl;
//   os << "==============" << std::endl;
//   os << std::endl;
//
//   HpIterator begin = m_HarpingPoints.begin();
//   HpIterator end   = m_HarpingPoints.end();
//   while ( begin != end )
//   {
//      WsHarpingPoint& hp = *begin++;
//      os << "Location        : " << hp.m_DistFromStart << std::endl;
//      os << "# Strand Points : " << hp.m_StrandPattern.GetStrandPointCount() << std::endl;
//      os << std::endl;
//   }
//   os << std::endl;
//
//}
//#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void bmfPrecastGirder::UpdateTopFlangeCorners()
{
   const bmfGirderPath* p_path = GetGirderPath();
   CHECK( p_path != 0 );

   Float64 length = GetLength();

   std::auto_ptr<gmIPrecastBeam> p_start_gdr_shape( GetTemplate()->CreateShape(0.0,length) );
   CHECK( p_start_gdr_shape.get() != 0 );

   std::auto_ptr<gmIPrecastBeam> p_end_gdr_shape( GetTemplate()->CreateShape(length,length) );
   CHECK( p_end_gdr_shape.get() != 0 );

   Float64 top_width_start = p_start_gdr_shape->GetTopWidth();
   Float64 top_width_end   = p_end_gdr_shape->GetTopWidth();

   // Get coordinates of start and end points of the girder (on the cl girder)
   CComPtr<IPoint2d> start_pnt, end_pnt;
   p_path->GetStartPoint(&start_pnt);
   p_path->GetEndPoint(&end_pnt);

   const bmfPier* p_start_pier = GetSpan()->GetStartPier();
   const bmfPier* p_end_pier   = GetSpan()->GetEndPier();

   CComPtr<IAngle> start_skew, end_skew;
   p_start_pier->GetSkewAngle(&start_skew);
   p_end_pier->GetSkewAngle(&end_skew);
   Float64 start_skew_value, end_skew_value;
   start_skew->get_Value(&start_skew_value);
   end_skew->get_Value(&end_skew_value);

   // Use a local cogo model
   CComPtr<ICogoEngine> engine;
   engine.CoCreateInstance(CLSID_CogoEngine);
   ATLASSERT(engine != NULL);

   CComQIPtr<ILocate2> locate(engine);

   Float64 dist; // need distance along skewed line

   m_StartLeft.Release();
   m_StartRight.Release();
   m_EndLeft.Release();
   m_EndRight.Release();

   // Start end of girder
   CHECK( !IsEqual(start_skew_value, PI_OVER_2) && !IsEqual(start_skew_value, -PI_OVER_2) );
   dist = fabs((top_width_start / 2.0) / cos( start_skew_value ));

   locate->ByDistDefAngle( end_pnt, start_pnt, dist, CComVariant(PI_OVER_2   + start_skew_value), 0.00, &m_StartLeft );
   locate->ByDistDefAngle( end_pnt, start_pnt, dist, CComVariant(3*PI_OVER_2 + start_skew_value), 0.00, &m_StartRight );

   CHECK( !IsEqual(end_skew_value, PI_OVER_2) && !IsEqual(end_skew_value, -PI_OVER_2) );
   dist = fabs((top_width_end / 2.0) / cos( end_skew_value ));
   locate->ByDistDefAngle( start_pnt, end_pnt, dist, CComVariant(3*PI_OVER_2 + end_skew_value), 0.00, &m_EndLeft);
   locate->ByDistDefAngle( start_pnt, end_pnt, dist, CComVariant(PI_OVER_2   + end_skew_value), 0.00, &m_EndRight);
}

void bmfPrecastGirder::MakeCopy( const bmfPrecastGirder& rOther)
{
   m_EndPtrn.RemoveAllStrands();
   m_HPPtrn.RemoveAllStrands();
   m_SsPtrn.RemoveAllStrands();
   m_TmpPtrn.RemoveAllStrands();

   m_EndPtrn  = rOther.m_EndPtrn;
   m_HPPtrn  = rOther.m_HPPtrn;
   m_SsPtrn  = rOther.m_SsPtrn;
   m_TmpPtrn = rOther.m_TmpPtrn;

   // copy long. reinf. layout and take ownership
   m_LrLayout = rOther.m_LrLayout;
   m_LrLayout.SetGirder(this);
}

void bmfPrecastGirder::MakeAssignment( const bmfPrecastGirder& rOther )
{
   bmfGirder::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//Uint32 bmfPrecastGirder::GetStrandBundle(Uint32 strIdx) const
//{
//   // 1. Determine how many strands are below this strand
//   gpPoint2d pnt = m_HsPtrn.GetStrandPoint(strIdx);
//   Float64 y = pnt.Y();
//
//   Uint32 nBelow = 0;
//   for ( Uint32 i = 0; i < GetNumHarpedStrands(); i++ )
//   {
//      pnt = m_HsPtrn.GetStrandPoint(i);
//      if ( pnt.Y() < y )
//         nBelow++;
//   }
//
//   // 2. Determine how many strands can fit in the lower bundle
//   Uint32 cLowerBundle = m_Bundle.GetMaxStrandCount(0);
//
//   // 3. Determine if this strand belongs in the lower bundle
//   if ( nBelow < cLowerBundle )
//      return 0; // Yes, lower bundle
//   else
//      return 1; // Nope... The strands below this one fill the lower bundle.
//                // This strand is in the upper bundle.
//
////   // Determine which bundle the strand belongs in.
////   Uint32 iBundle = m_Bundle.GetBundleIdx( strIdx );
////
////   // If the number of harped strands exceed the number of in the lower bundle
////   // then some of the first few strands get bumped to the upper bundle
////   Uint32 cLowerBundle   = m_Bundle.GetMaxStrandCount(0);
////   Uint32 nHarpedStrands = m_HsPtrn.GetStrandCount();
////   if ( nHarpedStrands > cLowerBundle )
////   {
////      bool bOdd = (nHarpedStrands % 2 != 0);
////      Uint32 nUpperBundle = nHarpedStrands - cLowerBundle;
////      nUpperBundle += (bOdd ? 1 : 0); // if odd, then and even number must go in upper bundle
////                                      // so odd strand is in lower bundle
////      if ( strIdx < nUpperBundle )
////      {
////         iBundle = 1;
////      }
////      else
////      {
////         iBundle = 0;
////      }
////   }
////
////   return iBundle;
//}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _DEBUG
bool bmfPrecastGirder::AssertValid() const
{
   return true;
}

void bmfPrecastGirder::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfPrecastGirder" << endl;
}

#endif // _DEBUG

#if defined _UNITTEST
bool bmfPrecastGirder::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE( "bmfPrecastGirder" );
   TESTME_EPILOG( "bmfPrecastGirder" );
}
#endif // _UNITTEST
