///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <Cogo\CogoLib.h>

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          CogoModel           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <Cogo\CogoModel.h>           // class implementation
#include <Cogo\Roadway.h>
#include <Cogo\CogoHelpers.h>
#include <Cogo\Engine.h>
#include <MathEx.h>

#include <GeometricPrimitives\GeomOp2d.h> // for gpGeomOp2d

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

cogoModel::cogoModel()
{
} // CogoModel

cogoModel::~cogoModel()
{
   Clear();
} // ~CogoModel

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Int32 cogoModel::StorePoint(Float64 x, Float64 y)
{
   return StorePoint( gpPoint2d(x,y) );
} // StorePoint

Int32 cogoModel::StorePoint(const gpPoint2d& rPnt)
{
   Int32 id = COGO_ERROR;
   try
   {
      id = m_PointIdMgr.ReserveNextId();
      m_Points.insert( std::make_pair( id, rPnt ) );
   }
   catch( ... )
   {
      return COGO_ERROR;
   }

   return id;
} // StorePoint

bool cogoModel::GetPoint(gpPoint2d* pPnt,Int32 id) const
{
   PRECONDITION( pPnt != 0 );

   const gpPoint2d* pPoint = GetPoint(id);
   if ( pPoint == 0 )
      return false;

   *pPnt = *pPoint;
   return true;
} // GetPoint

bool cogoModel::GetPoints(std::vector<gpPoint2d>* pPoints,
                          const std::vector<Int32>& id) const
{
   PRECONDITION( pPoints != 0 );
   pPoints->clear();

   std::vector<Int32>::const_iterator iter;
   for ( iter = id.begin(); iter != id.end(); iter++)
   {
      const gpPoint2d* pPoint = GetPoint( *iter );
      if ( pPoint == 0 )
         return false;

      pPoints->push_back( *pPoint );
   }
   return true;
}

void cogoModel::GetPoints(std::vector<gpPoint2d>* pPoints) const
{
   PRECONDITION( pPoints != 0 );
   pPoints->clear();

   ConstPointIterator iter;
   for (iter = m_Points.begin(); iter != m_Points.end(); iter++ )
   {
      pPoints->push_back( (*iter).second );
   }
}

bool cogoModel::RemovePoint(Int32 id)
{
   m_Points.erase( id );
   m_PointIdMgr.RestoreId( id );

   return true;
} // RemovePoint

bool cogoModel::MovePoint(Int32 id, Float64 newX, Float64 newY)
{
   gpPoint2d* pPoint = GetPoint( id );
   if ( pPoint == 0 )
      return false;

   pPoint->Move( newX, newY );

   return true;
} // MovePoint

bool cogoModel::MovePoint( Int32 id, const gpPoint2d& newPoint)
{
   return MovePoint( id, newPoint.X(), newPoint.Y() );
}

bool cogoModel::OffsetPoint(Int32 id, Float64 dx, Float64 dy)
{
   gpPoint2d* pPoint = GetPoint( id );
   if ( pPoint == 0 )
      return false;

   pPoint->Offset( dx, dy );

   return true;
} // OffsetPoint

bool cogoModel::OffsetPoint(Int32 id, const gpSize2d& offset)
{
   return OffsetPoint(id,offset.Dx(),offset.Dy());
} // OffsetPoint

Int32 cogoModel::StoreCurve(const cogoCurve& curve)
{
   Int32 id = COGO_ERROR;
   try
   {
      id = m_CurveIdMgr.ReserveNextId();
      m_Curves.insert( std::make_pair( id, curve ) );
   }
   catch( ... )
   {
      return COGO_ERROR;
   }

   return id;
}

Int32 cogoModel::StoreCurve(const gpPoint2d& pc,const gpPoint2d& pi,const gpPoint2d& pt,const gpPoint2d& cc)
{
   return StoreCurve( cogoCurve(pc,pi,pt,cc) );
}

Int32 cogoModel::StoreCurve(Int32 pc,Int32 pi,Int32 pt,Int32 cc)
{
   const gpPoint2d* pPC = GetPoint(pc);
   const gpPoint2d* pPI = GetPoint(pi);
   const gpPoint2d* pPT = GetPoint(pt);
   const gpPoint2d* pCC = GetPoint(cc);

   if ( pPC == 0 || pPI == 0 || pPT == 0 || pCC == 0 )
      return COGO_ERROR;

   return StoreCurve( *pPC, *pPI, *pPT, *pCC );
}

bool cogoModel::GetCurve(cogoCurve* pCurve,Int32 id)
{
   PRECONDITION( pCurve != 0 );

   const cogoCurve* pCrv = GetCurve(id);
   if ( pCrv == 0 )
      return false;

   *pCurve = *pCrv;
   return true;
}

bool cogoModel::ReplaceCurve(const cogoCurve& curve,Int32 id)
{
   cogoCurve* pCrv = GetCurve(id);
   if ( pCrv == 0 )
      return false;

   *pCrv = curve;
   return true;
}

bool cogoModel::RemoveCurve(Int32 id)
{
   CurveContainer::iterator found = m_Curves.find(id);
   if ( found == m_Curves.end() )
      return false;

   m_Curves.erase( found );
   return true;
}

Int32 cogoModel::CreateAlignment(Int32 id1,Int32 id2)
{
   Int32 id = COGO_ERROR;
   try
   {
      id = m_AlignmentIdMgr.ReserveNextId();
   }
   catch( ... )
   {
      return COGO_ERROR;
   }

   gpPoint2d* p1 = GetPoint(id1);
   gpPoint2d* p2 = GetPoint(id2);

   if ( p1 == 0 || p2 == 0 )
      return COGO_ERROR; // One of the specified points doesn't exist

   boost::shared_ptr<cogoRoadway> pRoadway( new cogoRoadway(id,this) );
   pRoadway->AddPoint(id1);
   pRoadway->AddPoint(id2);
   m_Alignments.insert( AlignmentEntry(id,pRoadway) );

   return id;
}

Int32 cogoModel::CreateAlignment(Int32 cid)
{
   Int32 id = COGO_ERROR;
   try
   {
      id = m_AlignmentIdMgr.ReserveNextId();
   }
   catch( ... )
   {
      return COGO_ERROR;
   }

   cogoCurve* pCurve = GetCurve(cid);

   if ( pCurve == 0 )
      return COGO_ERROR; // The specifed curve doesn't exist

   std::auto_ptr<cogoRoadway> pRoadway( new cogoRoadway(id,this) );
   pRoadway->AddCurve(cid);
   m_Alignments.insert( AlignmentEntry(id,pRoadway) );

   return id;
}

cogoRoadway* cogoModel::GetAlignment(Int32 id)
{
   AlignmentIterator location = m_Alignments.find( id );

   if ( location == m_Alignments.end() )
   {
      WARN(location == m_Alignments.end(),"Alignment " << id << " not found");
      return 0;
   }
   else
      return (*location).second.get();
}

const cogoRoadway* cogoModel::GetAlignment(Int32 id) const
{
   ConstAlignmentIterator location = m_Alignments.find( id );

   if ( location == m_Alignments.end() )
   {
      WARN(location == m_Alignments.end(),"Alignment " << id << " not found");
      return 0;
   }
   else
      return (*location).second.get();
}

bool cogoModel::RemoveAlignment(Int32 id)
{
   AlignmentIterator location = m_Alignments.find( id );

   if ( location == m_Alignments.end() )
   {
      WARN(location == m_Alignments.end(),"Alignment " << id << " not found");
      return false;
   }

   
   m_Alignments.erase(location); // auto_ptr will delete cogoRoadway object.
   m_AlignmentIdMgr.RestoreId( id );
   return true;
}

bool cogoModel::Inverse(Float64* pDistance, 
                        cogoDirection* pDirection,
                        Int32 fromPointId, 
                        Int32 toPointId) const
{
   PRECONDITION( pDistance  != 0 );
   PRECONDITION( pDirection != 0 );

   const gpPoint2d* pFromPoint = GetPoint( fromPointId );
   const gpPoint2d* pToPoint = GetPoint( toPointId );
   if ( pFromPoint == 0 || pToPoint == 0 )
      return false;

   cogoEngine::Inverse(pDistance,pDirection,*pFromPoint,*pToPoint);

   return true;
} // Inverse

Int32 cogoModel::LocateByDistDir(Int32 refPointId,
                                 Float64 distance,
                                 const cogoDirection& direction)
{
   gpPoint2d newPoint;
   if ( !LocateByDistDir( &newPoint, refPointId, distance, direction ) )
      return COGO_ERROR;

   return StorePoint( newPoint );
} // LocatePoint

bool cogoModel::LocateByDistDir(gpPoint2d* pNewPoint,
                                Int32 refPointId,
                                Float64 distance,
                                const cogoDirection& direction)
{
   PRECONDITION( pNewPoint != 0 );

   gpPoint2d* pRefPoint = GetPoint( refPointId );
   if ( pRefPoint == 0 )
      return false;

   *pNewPoint = cogoEngine::LocateByDistDir( *pRefPoint, distance, direction );
   return true;
} // LocatePoint

Int32 cogoModel::LocateByDistDir(const gpPoint2d& rRefPoint,
                                 Float64 distance,
                                 const cogoDirection& direction)
{
   gpPoint2d point;
   point = cogoEngine::LocateByDistDir( rRefPoint, distance, direction );
   return StorePoint( point );
} // LocatePoint

Int32 cogoModel::LocatePointOnLine( Int32 fromPointId,
                                    Int32 toPointId, Float64 distance)
{
   gpPoint2d* pFromPnt = GetPoint( fromPointId );
   gpPoint2d* pToPnt = GetPoint( toPointId );
   if ( pFromPnt == 0 || pToPnt == 0 )
      return COGO_ERROR;

   gpPoint2d point;
   point = cogoEngine::LocatePointOnLine( *pFromPnt, *pToPnt, distance ) ;
   return StorePoint( point );
} // LocatePointOnLine

bool cogoModel::LocatePointOnLine(gpPoint2d* pNewPoint,
                                  Int32 fromPointId, Int32 toPointId,
                                  Float64 distance) const
{
   PRECONDITION( pNewPoint != 0 );

   const gpPoint2d* pFromPnt = GetPoint( fromPointId );
   const gpPoint2d* pToPnt = GetPoint( toPointId );
   if ( pFromPnt == 0 || pToPnt == 0 )
      return false;

   *pNewPoint = cogoEngine::LocatePointOnLine( *pFromPnt,  *pToPnt, distance );
   return true;
} // LocatePointOnLine

Int32 cogoModel::LocatePointOnLine(const gpPoint2d& fromPoint,
                                   const gpPoint2d& toPoint,
                                   Float64 distance)
{
   gpPoint2d point;
   point = cogoEngine::LocatePointOnLine( fromPoint, toPoint, distance );
   return StorePoint( point );
} // LocatePointOnLine


bool cogoModel::LocateByDistAngle(gpPoint2d* pNewPoint,
                                  Int32 fromPointId,
                                  Int32 toPointId,
                                  Float64 distance,
                                  const cogoAngle& angle ) const
{
   PRECONDITION( pNewPoint != 0 );

   const gpPoint2d* pFromPoint = GetPoint( fromPointId );
   const gpPoint2d* pToPoint   = GetPoint( toPointId );
   if ( pFromPoint == 0 || pToPoint == 0 )
      return false;

   *pNewPoint = cogoEngine::LocateByDistAngle( *pFromPoint, *pToPoint, distance, angle );
   return true;
}

Int32 cogoModel::LocateByDistAngle(const gpPoint2d& fromPoint,
                                   const gpPoint2d& toPoint,
                                   Float64 distance,
                                   const cogoAngle& angle)
{
   gpPoint2d newPoint;
   newPoint = cogoEngine::LocateByDistAngle( fromPoint, toPoint, distance, angle );
   return StorePoint( newPoint );
}

Int32 cogoModel::LocateByDistAngle(Int32 fromPointId,
                                   Int32 toPointId,
                                   Float64 distance,
                                   const cogoAngle& angle)
{
   gpPoint2d* pFromPoint = GetPoint( fromPointId );
   gpPoint2d* pToPoint   = GetPoint( toPointId );
   if ( pFromPoint == 0 || pToPoint == 0 )
      return COGO_ERROR;

   gpPoint2d newPoint;
   newPoint = cogoEngine::LocateByDistAngle( *pFromPoint, *pToPoint, distance, angle );
   return StorePoint( newPoint );
}

bool cogoModel::LocateByDistDefAngle(gpPoint2d* pNewPoint,
                                     Int32 fromPointId,
                                     Int32 toPointId,
                                     Float64 distance,
                                     const cogoAngle& angle) const
{
   PRECONDITION( pNewPoint != 0 );

   const gpPoint2d* pFromPnt = GetPoint( fromPointId );
   const gpPoint2d* pToPnt   = GetPoint( toPointId );
   if ( pFromPnt == 0 || pToPnt == 0 )
      return false;

   *pNewPoint = cogoEngine::LocateByDistDefAngle( *pFromPnt, 
                                                  *pToPnt,
                                                  distance,
                                                  angle );

   return true;
}

Int32 cogoModel::LocateByDistDefAngle(const gpPoint2d& fromPoint,
                                      const gpPoint2d& toPoint,
                                      Float64 distance,
                                      const cogoAngle& angle)
{
   gpPoint2d pnt;
   pnt = cogoEngine::LocateByDistDefAngle( fromPoint,
                                           toPoint,
                                           distance,
                                           angle );

   return StorePoint( pnt );
}

Int32 cogoModel::LocateByDistDefAngle(Int32 fromPointId,
                                      Int32 toPointId,
                                      Float64 distance,
                                      const cogoAngle& angle)
{
   gpPoint2d* pFromPnt = GetPoint( fromPointId );
   gpPoint2d* pToPnt   = GetPoint( toPointId );
   if ( pFromPnt == 0 || pToPnt == 0 )
      return COGO_ERROR;

   gpPoint2d pnt;
   pnt = cogoEngine::LocateByDistDefAngle( *pFromPnt, 
                                           *pToPnt,
                                           distance,
                                           angle );

   return StorePoint( pnt );
} // LocateByDistDefangle


bool cogoModel::LocateParallelLine(gpPoint2d* pStart,
                                   gpPoint2d* pEnd,
                                   Int32 fromPointId,
                                   Int32 toPointId,
                                   Float64 distance) const
{
   PRECONDITION( pStart != 0 );
   PRECONDITION( pEnd   != 0 );

   const gpPoint2d* pFromPnt = GetPoint( fromPointId );
   const gpPoint2d* pToPnt   = GetPoint( toPointId );
   if ( pFromPnt == 0 || pToPnt == 0 )
      return false;

   cogoEngine::LocateParallelLine( pStart, pEnd, *pFromPnt, *pToPnt, distance );
   return true;
}   

Int32 cogoModel::LocateParallelLine(Int32* pStartId,
                                    Int32* pEndId,
                                    Int32 fromPointId,
                                    Int32 toPointId,
                                    Float64 distance)
{
   PRECONDITION( pStartId != 0 );
   PRECONDITION( pEndId   != 0 );

   gpPoint2d* pFromPnt = GetPoint( fromPointId );
   gpPoint2d* pToPnt   = GetPoint( toPointId );
   if ( pFromPnt == 0 || pToPnt == 0 )
      return COGO_ERROR;

   gpPoint2d p3, p4;
   cogoEngine::LocateParallelLine( &p3, &p4, *pFromPnt, *pToPnt, distance );

   *pStartId = StorePoint( p3 );
   *pEndId   = StorePoint( p4 );

   return (*pStartId == COGO_ERROR || *pEndId == COGO_ERROR) ? COGO_ERROR : 0;
}

Int32 cogoModel::LocateParallelLine(Int32* pStartId,
                                    Int32* pEndId,
                                    const gpPoint2d& p1,
                                    const gpPoint2d& p2,
                                    Float64 distance)
{
   PRECONDITION( pStartId != 0 );
   PRECONDITION( pEndId   != 0 );

   gpPoint2d p3, p4;
   cogoEngine::LocateParallelLine( &p3, &p4, p1, p2, distance );

   *pStartId = StorePoint( p3 );
   *pEndId   = StorePoint( p4 );

   return (*pStartId == COGO_ERROR || *pEndId == COGO_ERROR) ? COGO_ERROR : 0;
}



bool cogoModel::ProjectPointOnLine(gpPoint2d* pNewPoint,
                                   Int32 fromPointId,
                                   Int32 toPointId,
                                   Float64 offset,
                                   Int32 projPointId) const
{
   PRECONDITION( pNewPoint != 0 );

   const gpPoint2d* pFromPnt = GetPoint( fromPointId );
   const gpPoint2d* pToPnt   = GetPoint( toPointId );
   const gpPoint2d* pProjPnt = GetPoint( projPointId );

   if ( pFromPnt == 0 || pToPnt == 0 || pProjPnt == 0 )
      return false;

   *pNewPoint = cogoEngine::ProjectPointOnLine( *pFromPnt, *pToPnt, offset, *pProjPnt );

   return true;
}

Int32 cogoModel::ProjectPointOnLine(Int32 fromPointId,
                                    Int32 toPointId,
                                    Float64 offset,
                                    Int32 projPointId)
{
   gpPoint2d* pFromPnt = GetPoint( fromPointId );
   gpPoint2d* pToPnt   = GetPoint( toPointId );
   gpPoint2d* pProjPnt = GetPoint( projPointId );

   if ( pFromPnt == 0 || pToPnt == 0 || pProjPnt == 0 )
      return COGO_ERROR;

   return ProjectPointOnLine( *pFromPnt, *pToPnt, offset, *pProjPnt );
}

Int32 cogoModel::ProjectPointOnLine(const gpPoint2d& fromPoint,
                                    const gpPoint2d& toPoint,
                                    Float64 offset,
                                    const gpPoint2d& projPoint)
{
   gpPoint2d point;
   point = cogoEngine::ProjectPointOnLine( fromPoint, toPoint, offset, projPoint );
   return StorePoint( point );
}


bool cogoModel::LineLineIntersect(gpPoint2d* pNewPoint,
                                  Int32 pnt1,const cogoDirection& d1,Float64 offset1,
                                  Int32 pnt2,const cogoDirection& d2,Float64 offset2)
{
   PRECONDITION( pNewPoint != 0 );

   gpPoint2d* pPnt1;
   gpPoint2d* pPnt2;

   pPnt1 = GetPoint( pnt1 );
   pPnt2 = GetPoint( pnt2 );

   if ( pPnt1 == 0 || pPnt2 == 0 )
      return false;

   return cogoEngine::LineLineIntersect(pNewPoint, 
                                        *pPnt1,d1,offset1,
                                        *pPnt2,d2,offset2);
}

Int32 cogoModel::LineLineIntersect(Int32 p1,
                                   Int32 p2,
                                   Float64 offset1,
                                   Int32 p3,
                                   Int32 p4,
                                   Float64 offset2)
{
   gpPoint2d pnt;
   if ( LineLineIntersect( &pnt, p1, p2, offset1, p3, p4, offset2 ) )
   {
      return StorePoint( pnt );
   }
  
   return COGO_ERROR;
}

bool cogoModel::LineLineIntersect(gpPoint2d* pNewPoint,
                                  Int32 p1,
                                  Int32 p2,
                                  Float64 offset1,
                                  Int32 p3,
                                  Int32 p4,
                                  Float64 offset2)
{
   PRECONDITION( pNewPoint != 0 );

   gpPoint2d* pnt1;
   gpPoint2d* pnt2;
   gpPoint2d* pnt3;
   gpPoint2d* pnt4;
   cogoDirection d1, d2;
   Float64 temp;
   pnt1 = GetPoint( p1 );
   pnt2 = GetPoint( p2 );
   pnt3 = GetPoint( p3 );
   pnt4 = GetPoint( p4 );

   // One of the point's doesn't exist
   if ( pnt1 == 0 ||
        pnt2 == 0 ||
        pnt3 == 0 ||
        pnt4 == 0 )
        return false;

   cogoEngine::Inverse( &temp, &d1, *pnt1, *pnt2 );
   cogoEngine::Inverse( &temp, &d2, *pnt3, *pnt4 );
   return cogoEngine::LineLineIntersect( pNewPoint,
                                         *pnt1, d1, offset1,
                                         *pnt3, d2, offset2 );
}

//======================== OPERATIONS - Divide ==============================

bool cogoModel::DivideLine(std::vector<gpPoint2d>* pPoints,
                           Int32 fromPointId, Int32 toPointId, Uint16 nParts ) const
{
   const gpPoint2d* pFromPnt = GetPoint( fromPointId );
   const gpPoint2d* pToPnt   = GetPoint( toPointId );
   if ( pFromPnt == 0 || pToPnt == 0 )
      return false;

   *pPoints = cogoEngine::DivideLine( *pFromPnt, *pToPnt, nParts );
   return true;
}

bool cogoModel::DivideLine(std::vector<Int32>* pIds,
                           Int32 fromPointId, Int32 toPointId, Uint16 nParts)
{
   const gpPoint2d* pFromPnt = GetPoint( fromPointId );
   const gpPoint2d* pToPnt   = GetPoint( toPointId );
   if ( pFromPnt == 0 || pToPnt == 0 )
      return false;

   DivideLine( pIds, *pFromPnt, *pToPnt, nParts );
   return true;
}

void cogoModel::DivideLine(std::vector<Int32>* pIds,
                           const gpPoint2d& p1, const gpPoint2d& p2,Uint16 nParts)
{
   std::vector<gpPoint2d> points;
   points = cogoEngine::DivideLine( p1, p2, nParts );
   std::vector<gpPoint2d>::iterator i;
   for ( i = points.begin(); i < points.end(); i++ )
   {
      pIds->push_back( StorePoint( *i ) );
   }
}


bool cogoModel::DivideArc(std::vector<gpPoint2d>* pPoints,
                          Int32 fromId,Int32 vertexId,Int32 toId,Uint16 nParts) const
{
   const gpPoint2d* pFromPnt = GetPoint( fromId );
   const gpPoint2d* pVertex  = GetPoint( vertexId );
   const gpPoint2d* pToPnt   = GetPoint( toId );

   if ( pFromPnt == 0 || pVertex == 0 || pToPnt == 0 )
      return false;

   *pPoints = cogoEngine::DivideArc( *pFromPnt, *pVertex, *pToPnt, nParts );
   return true;
}

bool cogoModel::DivideArc(std::vector<Int32>* pIds,
                          Int32 fromId,Int32 vertexId,Int32 toId,Uint16 nParts)
{
   gpPoint2d* pFromPnt = GetPoint( fromId );
   gpPoint2d* pVertex  = GetPoint( vertexId );
   gpPoint2d* pToPnt   = GetPoint( toId );

   if ( pFromPnt == 0 || pVertex == 0 || pToPnt == 0 )
      return false;

   DivideArc( pIds, *pFromPnt, *pVertex, *pToPnt, nParts );
   return true;
}

void cogoModel::DivideArc(std::vector<Int32>* pIds,
                          const gpPoint2d& fromPnt,const gpPoint2d& vertex,const gpPoint2d& toPnt,Uint16 nParts)
{
   std::vector<gpPoint2d> points;
   points = cogoEngine::DivideArc( fromPnt, vertex, toPnt, nParts );
   std::vector<gpPoint2d>::iterator i;
   for ( i = points.begin(); i < points.end(); i++ )
   {
      pIds->push_back( StorePoint( *i ) );
   }
}

bool cogoModel::ComputeArea(Float64* pArea,const std::vector<Int32>& vPointIds) const
{
   PRECONDITION ( pArea != 0 );

   std::vector<gpPoint2d> vPoints;
   std::vector<Int32>::const_iterator begin = vPointIds.begin();
   std::vector<Int32>::const_iterator end   = vPointIds.end();
   while ( begin != end )
   {
      const gpPoint2d* pPoint = GetPoint( *begin++ );
      if ( pPoint == 0 )
         return false;

      vPoints.push_back( *pPoint );
   }

   *pArea = cogoEngine::ComputeArea( vPoints );

   return true;
}

bool cogoModel::ComputeAngle(cogoAngle* pAngle,
                             Int32 fromId,Int32 vertexId,Int32 toId) const
{
   PRECONDITION( pAngle != 0 );

   if ( fromId == vertexId || toId == vertexId )
      return false;

   const gpPoint2d* pFromPnt = GetPoint( fromId );
   const gpPoint2d* pVertex  = GetPoint( vertexId );
   const gpPoint2d* pToPnt   = GetPoint( toId );

   if ( pFromPnt == 0 || pVertex == 0 || pToPnt == 0 )
      return false;

   *pAngle = cogoEngine::ComputeAngle( *pFromPnt, *pVertex, *pToPnt );
   return true;
}

void cogoModel::Clear()
{
   m_Points.clear();
   m_PointIdMgr.Reset();

   m_Curves.clear();
   m_CurveIdMgr.Reset();

   m_Alignments.clear();
   m_AlignmentIdMgr.Reset();
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
gpPoint2d* cogoModel::GetPoint(Int32 id)
{
   PointContainer::iterator i;
   i = m_Points.find( id );
   if ( i == m_Points.end() )
      return 0;

   return &(*i).second;
}

const gpPoint2d* cogoModel::GetPoint(Int32 id) const
{
   PointContainer::const_iterator i;
   i = m_Points.find( id );
   if ( i == m_Points.end() )
      return 0;

   return &(*i).second;
}

cogoCurve* cogoModel::GetCurve(Int32 id)
{
   CurveContainer::iterator i;
   i = m_Curves.find( id );
   if ( i == m_Curves.end() )
      return 0;

   return &(*i).second;
}

const cogoCurve* cogoModel::GetCurve(Int32 id) const
{
   CurveContainer::const_iterator i;
   i = m_Curves.find( id );
   if ( i == m_Curves.end() )
      return 0;

   return &(*i).second;
}


//======================== INQUERY ==========================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool cogoModel::AssertValid() const
{
   return true;
}

void cogoModel::Dump(dbgDumpContext& os) const
{
   os << "Dump for cogoModel - Not Implemented" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST

bool test_LocateByDistAngle(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoModel::LocateByDistAngle");

   cogoModel model;

   Float64 dist = 10;
   gpPoint2d from(0,0);
   gpPoint2d to(dist,0);
   gpPoint2d p;
   cogoAngle angle[] = { cogoAngle(  0,0,0),
                         cogoAngle( 45,0,0),
                         cogoAngle( 90,0,0),
                         cogoAngle(135,0,0),
                         cogoAngle(180,0,0),
                         cogoAngle(225,0,0),
                         cogoAngle(270,0,0),
                         cogoAngle(315,0,0),
                         cogoAngle(360,0,0) };
   Uint16 cAngle = sizeof( angle ) / sizeof( cogoAngle );

   for ( Uint16 i = 0; i < cAngle; i++ )
   {
      p = cogoEngine::LocateByDistAngle( from, to, dist, angle[i] );
      gpPoint2d test;
      test.X() = to.X() - dist*cos(angle[i].AsFloat64());
      test.Y() = to.Y() + dist*sin(angle[i].AsFloat64());
      TRY_TESTME( p == test );
   }

   TESTME_EPILOG("cogoModel::LocateByDistAngle");
}

bool test_LocateByDistDefAngle(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoModel::LocateByDistDefAngle");

   cogoModel model;

   Float64 dist = 10;
   gpPoint2d from(0,0);
   gpPoint2d to(dist,0);
   gpPoint2d p;
   cogoAngle angle[] = { cogoAngle(  0,0,0),
                         cogoAngle( 45,0,0),
                         cogoAngle( 90,0,0),
                         cogoAngle(135,0,0),
                         cogoAngle(180,0,0),
                         cogoAngle(225,0,0),
                         cogoAngle(270,0,0),
                         cogoAngle(315,0,0),
                         cogoAngle(360,0,0) };
   Uint16 cAngle = sizeof( angle ) / sizeof( cogoAngle );

   for ( Uint16 i = 0; i < cAngle; i++ )
   {
      p = cogoEngine::LocateByDistDefAngle( from, to, dist, angle[i] );
      gpPoint2d test;
      test.X() = to.X() + dist*cos(angle[i].AsFloat64());
      test.Y() = to.Y() - dist*sin(angle[i].AsFloat64());
      TRY_TESTME( p == test );
   }

   TESTME_EPILOG("cogoModel::LocateByDistDefAngle");
}

bool test_LocateByDistDir(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoModel::LocateByDistDir");

   cogoModel model;
   Float64 dist = 10;
   gpPoint2d from(0,0);
   gpPoint2d p;
   cogoDirection dir[] = { cogoDirection('N', 0,0,0,'W'),
                           cogoDirection('N',45,0,0,'W'),
                           cogoDirection('N',90,0,0,'W'),
                           cogoDirection('S',45,0,0,'W'),
                           cogoDirection('S', 0,0,0,'W'),
                           cogoDirection('S',45,0,0,'E'),
                           cogoDirection('N',90,0,0,'E'),
                           cogoDirection('N',45,0,0,'E') };

   Uint16 cDir = sizeof( dir ) / sizeof( cogoDirection );

   for ( Uint16 i = 0; i < cDir; i++ )
   {
      p = cogoEngine::LocateByDistDir( from, dist, dir[i] );
      gpPoint2d test;
      test.X() = from.X() + dist*sin(dir[i].AsFloat64());
      test.Y() = from.Y() + dist*cos(dir[i].AsFloat64());
      TRY_TESTME( p == test );
   }

   TESTME_EPILOG("cogoModel::LocateByDistDir");
}

bool cogoModel::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoModel");

#pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for cogoModel");

   TRY_TESTME( test_LocateByDistAngle(rlog) );
   TRY_TESTME( test_LocateByDistDefAngle(rlog) );
   TRY_TESTME( test_LocateByDistDir(rlog) );


   TESTME_EPILOG("cogoModel");
}
#endif