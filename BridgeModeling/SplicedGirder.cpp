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
   bmfSplicedGirder
****************************************************************************/

#include <BridgeModeling\SplicedGirder.h>        // class implementation
#include <BridgeModeling\Span.h>
#include <BridgeModeling\Pier.h>
#include <BridgeModeling\Connection.h>
#include <BridgeModeling\SplicedGirderSection.h>
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
bmfSplicedGirder::bmfSplicedGirder(bmfSplicedGirderTemplate* pTpl) :
bmfGirder( pTpl )
{
   for ( SegmentIndexType segment = 0; segment < pTpl->GetNumSegments(); segment++ )
   {
      m_StrandPtrn[segment]   = pTpl->GetStrandPattern(segment);
      m_StrandPtrn[segment].RemoveAllStrands();
   }

   m_TmpPtrn = pTpl->GetTemporaryStrandPattern();
   m_TmpPtrn.RemoveAllStrands();

   for ( SegmentIndexType segment = 0; segment < pTpl->GetNumSegments(); segment++ )
   {
      m_LrLayout[segment] = pTpl->GetLrLayout(segment);
      m_LrLayout[segment].SetGirder(this);
   }

   m_Ducts = pTpl->GetDucts();
   m_Ducts.SetGirder(this);

   m_bGrouted = false;
}

bmfSplicedGirder::bmfSplicedGirder(const bmfSplicedGirder& rOther) :
bmfGirder( rOther )
{
   m_StrandPtrn[0].RemoveAllStrands();
   m_StrandPtrn[1].RemoveAllStrands();
   m_StrandPtrn[2].RemoveAllStrands();
   m_TmpPtrn.RemoveAllStrands();

   m_Ducts.RemoveAllDucts();

   MakeCopy( rOther );
}

bmfSplicedGirder::~bmfSplicedGirder()
{
}

//======================== OPERATORS  =======================================
bmfSplicedGirder& bmfSplicedGirder::operator=(const bmfSplicedGirder& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
SegmentIndexType bmfSplicedGirder::GetNumSegments() const
{
   return GetTemplate()->GetNumSegments();
}

Uint16 bmfSplicedGirder::GetNumSplices() const
{
   return GetTemplate()->GetNumSplices();
}

Float64 bmfSplicedGirder::GetSpliceLocation(Uint16 splice) const
{
   const bmfSplicedGirderTemplate* pTemplate = GetTemplate();

   Uint16 nSplices = pTemplate->GetNumSplices();
   CHECK( splice < nSplices );

   Float64 total_length = GetLength();
   if ( nSplices == 0 )
      return 0.0;

   Float64 location;
   if ( 0 <= splice )
   {
      Float64 left_length = pTemplate->GetSegmentLength(0);
      if ( left_length < 0 )
         left_length = -1*left_length*total_length;

      location = left_length;
   }

   if ( 1 <= splice )
   {
      Float64 middle_length = pTemplate->GetSegmentLength(1);
      if ( middle_length < 0 )
         middle_length = -1*middle_length*total_length;

      location += middle_length;
   }

   return location;
}

void bmfSplicedGirder::PlanView(HDC hDC,const grlibPointMapper& mapper) const
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

gpRect2d bmfSplicedGirder::GetBoundingBox() const
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

void bmfSplicedGirder::OnGirderPathChanged()
{
   bmfGirder::OnGirderPathChanged();
   UpdateTopFlangeCorners();
}

bmfIGirderSection* bmfSplicedGirder::CreateGirderSection(Float64 distFromStart) const
{
   std::auto_ptr<gmIPrecastBeam> pBeam( GetTemplate()->CreateShape(distFromStart,GetLength()) );
   CHECK( pBeam.get() != 0 );

   const matConcreteEx* pConc = GetTemplate()->GetConcrete();
   CHECK( pConc != 0 );

#pragma Reminder("Should the girder section account for strands?")

   bmfIGirderSection* p_section;
   std::vector<bmfSplicedGirderSection::Duct> ducts;
   
   if ( !m_bGrouted )
   {
      // Deduct holes for all ducts
      Uint32 nDucts = m_Ducts.GetDuctCount();

      for ( Uint32 i = 0; i < nDucts; i++ )
      {
         bmfSplicedGirderSection::Duct duct;
         duct.location = m_Ducts.GetDuctLocation(i,distFromStart);
         duct.diameter = m_Ducts.GetDuctDiameter(i);

         ducts.push_back(duct);
      }
   }

   p_section = new bmfSplicedGirderSection( pBeam.get(), ducts, pConc );

   return p_section;
}

//======================== ACCESS     =======================================
const matConcreteEx* bmfSplicedGirder::GetConcrete() const
{
   return GetTemplate()->GetConcrete();
}

const matPsStrand* bmfSplicedGirder::GetStrand() const
{
   return GetTemplate()->GetStrand();
}

const matPsStrand* bmfSplicedGirder::GetPTStrand() const
{
   return GetTemplate()->GetPTStrand();
}

const bmfStrandPattern& bmfSplicedGirder::GetStrandPattern(SegmentIndexType segment) const
{
   return m_StrandPtrn[segment];
}

bmfStrandPattern& bmfSplicedGirder::GetStrandPattern(SegmentIndexType segment)
{
   return m_StrandPtrn[segment];
}

Float64 bmfSplicedGirder::GetTemporaryStrandEccentricity( Float64 distFromStart ) const
{
   return GetTemporaryStrandEccentricity( GetNumTemporaryStrands(), distFromStart );
}

Float64 bmfSplicedGirder::GetTemporaryStrandEccentricity( StrandIndexType nStrands, Float64 distFromStart ) const
{
   // Get the CG of the straight strand pattern for nStrands.
   // The CG is measured up from the bottom of the girder.
   if (nStrands==0)
      return 0.0;
   else
   {
      gpPoint2d cg = m_TmpPtrn.GetCenterOfGravity( nStrands );

      CHECK( IsZero(cg.X()) );

      const bmfSplicedGirderTemplate* pTpl = GetTemplate();
      std::auto_ptr<gmIPrecastBeam> pBeam(pTpl->CreateShape(distFromStart,GetLength()));
      gmProperties prop;
      pBeam->GetProperties( &prop );

      Float64 ecc = fabs(prop.Ybottom()) - cg.Y();
      return ecc;
   }
}

Float64 bmfSplicedGirder::GetStrandEccentricity( SegmentIndexType segment, Float64 distFromStart ) const
{
   return GetStrandEccentricity( segment, GetNumStrands(segment), distFromStart );
}

Float64 bmfSplicedGirder::GetStrandEccentricity( SegmentIndexType segment, StrandIndexType nStrands, Float64 distFromStart ) const
{
   // Get the CG of the straight strand pattern for nStrands.
   // The CG is measured up from the bottom of the girder.
   if (nStrands==0)
      return 0.0;
   else
   {
      gpPoint2d cg = m_StrandPtrn[segment].GetCenterOfGravity( nStrands );

      CHECK( IsZero(cg.X()) );

      const bmfSplicedGirderTemplate* pTpl = GetTemplate();

      // distFromStart is the distance from the start of the segment
      // In order to cut the proper section we need the distance from the start
      // of the girder.
      Float64 dist_from_start_of_girder;
      switch(segment)
      {
      case 0: // left
         dist_from_start_of_girder = distFromStart;
         break;

      case 1: // middle
         dist_from_start_of_girder = GetSegmentLength(0) + distFromStart;
         break;

      case 2: // right
         dist_from_start_of_girder = GetSegmentLength(0) + GetSegmentLength(1) + distFromStart;
         break;

      }

      std::auto_ptr<gmIPrecastBeam> pBeam( pTpl->CreateShape(dist_from_start_of_girder,GetLength()) );
      gmProperties prop;
      pBeam->GetProperties( &prop );

      Float64 ecc = fabs(prop.Ybottom()) - cg.Y();
      return ecc;
   }
}

gpPoint2d bmfSplicedGirder::GetTemporaryStrandPosition(Float64 distFromStart, StrandIndexType strIdx) const
{
   return m_TmpPtrn.GetStrandPoint( strIdx );
}

gpPoint2d bmfSplicedGirder::GetTemporaryStrandPoint(Float64 distFromStart, StrandIndexType strIdx) const
{
   return m_TmpPtrn.GetStrandPatternPoint( strIdx );
}

gpPoint2d bmfSplicedGirder::GetTendonEccentricity( Float64 distFromStart ) const
{
   if ( m_Ducts.GetNumStrands() == 0 )
      return gpPoint2d(0,0);

   gpPoint2d location( m_Ducts.GetPTCG(distFromStart) );

   // Eccentricity is measured from the CG of the beam
   const bmfSplicedGirderTemplate* pTpl = GetTemplate();
   std::auto_ptr<gmIPrecastBeam> pBeam( pTpl->CreateShape(distFromStart,GetLength()) );
   gmProperties prop;
   pBeam->GetProperties( &prop );

   gpPoint2d ecc;
   ecc.Y() = fabs(prop.Ybottom()) - location.Y();
   ecc.X() = location.X();

   return ecc;
}

gpPoint2d bmfSplicedGirder::GetTendonEccentricity( Float64 distFromStart, Uint32 ductIdx ) const
{
   if ( m_Ducts.GetNumStrands(ductIdx) == 0 )
      return gpPoint2d(0,0);

   Float64 x,y;
   const bmfDuct& duct = m_Ducts.GetDuct(ductIdx);
   duct.GetTendonCG(distFromStart,GetLength(),&x,&y);
   gpPoint2d location(x,y);

   // Eccentricity is measured from the CG of the beam
   const bmfSplicedGirderTemplate* pTpl = GetTemplate();
   std::auto_ptr<gmIPrecastBeam> pBeam( pTpl->CreateShape(distFromStart,GetLength()) );
   gmProperties prop;
   pBeam->GetProperties( &prop );

   gpPoint2d ecc;
   ecc.Y() = fabs(prop.Ybottom()) - location.Y();
   ecc.X() = location.X();

   return ecc;
}

//Float64 bmfSplicedGirder::GetTendonEccentricity( Float64 distFromStart, Uint32 nStrands ) const
//{
//   Float64 y = m_Ducts.GetCG(distFromStart,nStrands);
//
//   const bmfSplicedGirderTemplate* pTpl = GetTemplate();
//   std::auto_ptr<gmIPrecastBeam> pBeam( pTpl->CreateShape(distFromStart,GetLength()) );
//   gmProperties prop;
//   pBeam->GetProperties( &prop );
//
//   Float64 ecc = fabs(prop.Ybottom()) - y;
//   return ecc;
//}

gpPoint2d bmfSplicedGirder::GetDuctEccentricity( Float64 distFromStart, Uint32 ductIndex ) const
{
   gpPoint2d location = m_Ducts.GetDuctLocation(ductIndex,distFromStart);

   const bmfSplicedGirderTemplate* pTpl = GetTemplate();
   std::auto_ptr<gmIPrecastBeam> pBeam( pTpl->CreateShape(distFromStart,GetLength()) );
   gmProperties prop;
   pBeam->GetProperties( &prop );

   gpPoint2d ecc;
   ecc.Y() = fabs(prop.Ybottom()) - location.Y();
   ecc.X() = location.X();

   return ecc;
}

gpPoint2d bmfSplicedGirder::GetDuctLocation( Float64 distFromStart, Uint32 ductIndex ) const
{
   return m_Ducts.GetDuctLocation(ductIndex,distFromStart);
}

gpPoint2d bmfSplicedGirder::GetStrandPosition(SegmentIndexType segment,Float64 distFromStart, StrandIndexType strIdx) const
{
   return m_StrandPtrn[segment].GetStrandPoint( strIdx );
}


bool bmfSplicedGirder::IsStrandDebonded(SegmentIndexType segment, StrandIndexType strIdx) const
{
   return m_StrandPtrn[segment].IsStrandDebonded( strIdx );
}


gpPoint2d bmfSplicedGirder::GetStrandPoint(SegmentIndexType segment,Float64 distFromStart, StrandIndexType strIdx) const
{
   return m_StrandPtrn[segment].GetStrandPatternPoint( strIdx );
}

StrandIndexType bmfSplicedGirder::GetMaxStrands(SegmentIndexType segment) const
{
   return m_StrandPtrn[segment].GetMaxStrandCount();
}

bool bmfSplicedGirder::AddStrand(SegmentIndexType segment)
{
   if ( m_StrandPtrn[segment].AddStrand() == 0 )
      return false;

   return true;
}

bool bmfSplicedGirder::RemoveStrand(SegmentIndexType segment)
{
   if ( m_StrandPtrn[segment].RemoveStrand() == 0 )
      return false;

   return true;
}

StrandIndexType bmfSplicedGirder::SetNumStrands( SegmentIndexType segment,StrandIndexType nStrands )
{
   StrandIndexType outcome = m_StrandPtrn[segment].SetStrandCount( nStrands );
   return outcome;
}

StrandIndexType bmfSplicedGirder::GetNumStrands(SegmentIndexType segment) const
{
   return m_StrandPtrn[segment].GetStrandCount();
}

StrandIndexType bmfSplicedGirder::GetMaxTemporaryStrands() const
{
   return m_TmpPtrn.GetMaxStrandCount();
}

bool bmfSplicedGirder::AddTemporaryStrand()
{
   if ( m_TmpPtrn.AddStrand() == 0 )
      return false;

   return true;
}

bool bmfSplicedGirder::RemoveTemporaryStrand()
{
   if ( m_TmpPtrn.RemoveStrand() == 0 )
      return false;

   return true;
}

StrandIndexType bmfSplicedGirder::SetNumTemporaryStrands( StrandIndexType nStrands )
{
   StrandIndexType outcome = m_TmpPtrn.SetStrandCount( nStrands );
   return outcome;
}

StrandIndexType bmfSplicedGirder::GetNumTemporaryStrands() const
{
   return m_TmpPtrn.GetStrandCount();
}

StrandIndexType bmfSplicedGirder::GetNumDebondedStrands(SegmentIndexType segment) const
{
   return m_StrandPtrn[segment].GetDebondStrandCount();
}

void bmfSplicedGirder::SetNumDebondedStrands(SegmentIndexType segment,StrandIndexType nStrands)
{
   m_StrandPtrn[segment].SetDebondStrandCount(nStrands);
}

Float64 bmfSplicedGirder::GetDebondLength(SegmentIndexType segment) const
{
   return m_StrandPtrn[segment].GetDebondLength();
}

void bmfSplicedGirder::SetDebondLength(SegmentIndexType segment,Float64 l)
{
   m_StrandPtrn[segment].SetDebondLength(l);
}

StrandIndexType bmfSplicedGirder::GetMaxPTStrands() const
{
   return m_Ducts.GetMaxStrands();
}

//bool bmfSplicedGirder::AddPTStrand()
//{
//   return m_Ducts.AddStrand();
//}
//
//bool bmfSplicedGirder::RemovePTStrand()
//{
//   return m_Ducts.RemoveStrand();
//}

StrandIndexType bmfSplicedGirder::SetNumPTStrands( Uint32 ductIndex, StrandIndexType nStrands )
{
   m_Ducts.SetNumStrands(ductIndex,nStrands);
   return 0;
}

StrandIndexType bmfSplicedGirder::GetNumPTStrands(Uint32 ductIndex) const
{
   return m_Ducts.GetNumStrands(ductIndex);
}

StrandIndexType bmfSplicedGirder::GetNumPTStrands() const
{
   return m_Ducts.GetNumStrands();
}

Uint32 bmfSplicedGirder::GetNumDucts() const
{
   return m_Ducts.GetDuctCount();
}

Float64 bmfSplicedGirder::GetDuctSlope(Float64 x,Uint32 ductIndex) const
{
   return m_Ducts.GetDuctSlope(x,ductIndex);
}

void bmfSplicedGirder::GetDuctControlPoints(Uint32 ductIndex,gpPoint2d* pe1,gpPoint2d* pe2)
{
   m_Ducts.GetDuctControlPoints(ductIndex,pe1,pe2);
}

Float64 bmfSplicedGirder::GetDuctDiameter(Uint32 ductIndex) const
{
   return m_Ducts.GetDuctDiameter(ductIndex);
}

const bmfSplicedGirderTemplate* bmfSplicedGirder::GetTemplate() const
{
   // Cast to recover type information.
   // We only allow bmfSplicedGirderTemplates in.  If this cast fails
   // then something is really wrong.
   const bmfSplicedGirderTemplate* pTpl;
   pTpl = dynamic_cast<const bmfSplicedGirderTemplate*>( bmfGirder::GetTemplate() );
   CHECK( pTpl != 0 );
   return pTpl;
}

bmfSplicedGirderTemplate* bmfSplicedGirder::GetTemplate()
{
   // Cast to recover type information.
   // We only allow bmfSplicedGirderTemplates in.  If this cast fails
   // then something is really wrong.
   bmfSplicedGirderTemplate* pTpl;
   pTpl = dynamic_cast<bmfSplicedGirderTemplate*>( bmfGirder::GetTemplate() );
   CHECK( pTpl != 0 );
   return pTpl;
}

const bmfLrLayout& bmfSplicedGirder::GetLrLayout(SegmentIndexType segment) const
{
   return m_LrLayout[segment];
}

void bmfSplicedGirder::SetLrLayout(SegmentIndexType segment,const bmfLrLayout& rLayout)
{
   m_LrLayout[segment] = rLayout;
}

Float64 bmfSplicedGirder::GetSegmentLength(SegmentIndexType segment) const
{
   const bmfSplicedGirderTemplate* pTemplate = GetTemplate();

   SegmentIndexType nSegments = pTemplate->GetNumSegments();
   CHECK( segment < nSegments );

   Float64 total_length = GetLength();
   if ( nSegments == 1 )
      return total_length;

   Float64 left_length;
   Float64 middle_length;
   Float64 right_length;
   if ( nSegments == 2 )
   {
      left_length = pTemplate->GetSegmentLength(0);
      if ( left_length < 0 )
         left_length = -1*left_length*total_length;

      middle_length = total_length - left_length;

      right_length = 0;

      Float64 closure_pour = pTemplate->GetClosurePourSize(0);
      left_length -= closure_pour/2;
      middle_length -= closure_pour/2;
   }
   else if ( nSegments == 3 )
   {
      left_length = pTemplate->GetSegmentLength(0);
      if ( left_length < 0 )
         left_length = -1*left_length*total_length;

      middle_length = pTemplate->GetSegmentLength(1);
      if ( middle_length < 0 )
         middle_length = -1*middle_length*total_length;

      right_length = total_length - left_length - middle_length;

      Float64 closure_pour = pTemplate->GetClosurePourSize(0);
      left_length -= closure_pour/2;
      middle_length -= closure_pour/2;

      closure_pour = pTemplate->GetClosurePourSize(1);
      middle_length -= closure_pour/2;
      right_length -= closure_pour/2;
   }

   if ( segment == 0 )
      return left_length;
   else if ( segment == 1 )
      return middle_length;
   else
      return right_length;
}

Float64 bmfSplicedGirder::GetClosurePourSize(Uint16 splice) const
{
   const bmfSplicedGirderTemplate* pTemplate = GetTemplate();

   return pTemplate->GetClosurePourSize(splice);
}

bool bmfSplicedGirder::AreDuctsGrouted() const
{
   return m_bGrouted;
}

void bmfSplicedGirder::Grout(bool bGrout)
{
   m_bGrouted = bGrout;
}

//======================== INQUIRY    =======================================

//#if defined _DEBUG
//void bmfSplicedGirder::Dump(std::ostream& os)
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

void bmfSplicedGirder::UpdateTopFlangeCorners()
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

void bmfSplicedGirder::MakeCopy( const bmfSplicedGirder& rOther)
{
   for ( SegmentIndexType segment = 0; segment < GetNumSegments(); segment ++ )
   {
      m_StrandPtrn[segment].RemoveAllStrands();
      m_StrandPtrn[segment]  = rOther.m_StrandPtrn[segment];

      // copy long. reinf. layout and take ownership
      m_LrLayout[segment] = rOther.m_LrLayout[segment];
      m_LrLayout[segment].SetGirder(this);
   }

   m_TmpPtrn.RemoveAllStrands();
   m_TmpPtrn = rOther.m_TmpPtrn;

   m_Ducts    = rOther.m_Ducts;
   m_Ducts.SetGirder(this);
   m_bGrouted = rOther.m_bGrouted;
}

void bmfSplicedGirder::MakeAssignment( const bmfSplicedGirder& rOther )
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

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _DEBUG
bool bmfSplicedGirder::AssertValid() const
{
   return true;
}

void bmfSplicedGirder::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfSplicedGirder" << endl;
}

#endif // _DEBUG

#if defined _UNITTEST
bool bmfSplicedGirder::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE( "bmfSplicedGirder" );
   TESTME_EPILOG( "bmfSplicedGirder" );
}
#endif // _UNITTEST
