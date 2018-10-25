///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODEL_GIRDERPATH_H_
#define INCLUDED_BRIDGEMODEL_GIRDERPATH_H_
#pragma once

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bmfGirderPath
// SYNOPSIS:      
// DESCRIPTION:   A geometric line that a girder follows.
//
//                Girder paths can be the length of an entire bridge
//                or simply the length of a span.  This implementation
//                assumes that a girder path is limited by the length of a
//                span. This is consistent for bridges constructed with
//                prefabricated girder components such as prestressed girders.
//
//                A girder path owns the girder that is attached to it.
// EXAMPLES:      
// BUGS:          
// ALSO SEE:
//////////////////X////////////////////X/////////////////////////////////////

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <GraphicsLib\PointMapper.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bmfGirder;
class bmfSpan;
class bmfGirderTemplate;

// MISCELLANEOUS
//

class BMFCLASS bmfGirderPath
{
public:
   // LIFECYCLE

   // Method:      GirderPath
   // Description: Default c'tor
   // Return:      N/A
   bmfGirderPath();

   // Method:      GirderPath
   // Description: Explicit c'tor
   // Return:      N/A
   bmfGirderPath(bmfSpan* pSpan, 
                 GirderIndexType girderIdx,  // zero based index
                 Float64 startOffset,
                 bmfMeasuredWhere startWhere,
                 bmfMeasuredHow startHow,
                 Float64 endOffset,
                 bmfMeasuredWhere endWhere, 
                 bmfMeasuredHow endHow);

   // Method:      ~GirderPath
   // Description: d'tor
   // Return:      N/A
   virtual ~bmfGirderPath(); 

   // OPERATORS

   // Method:      operator =
   // Description: Assignment operator
   // Return:      Reference to self

   // OPERATIONS

   void BuildGirder(bmfGirderTemplate* pTemplate);

   // Method:      Draw
   // Description: Draws the girder path
   // Return:      None
   void Draw(HDC hDC, const grlibPointMapper& mapper) const;

   // Method:      Update
   // Description: Forces the girder path to update itself in the cogo model
   // Return:      None
   virtual void OnSpanChanged();

   // Method:      NormalOffsetFromAlignment
   // Description: Gets the normal distance from the bridge alignment to a point
   //              on the girder path at a given station.
   // Return:      The distance. positive if girder is in pos Y from alignment
   Float64 NormalOffsetFromAlignment(Float64 station) const;

   // Returns the station and normal offset for a point on the girder, measured
   // from the start end of the girder.
   void GetStationAndOffset(Float64 distFromStart,Float64* pStation,Float64* pOffset) const;

   // Method:      EndDistanceFromStation
   // Description: Returns the distance from the start end of the beam to the section
   //              normal to the road alignment at a given section
   // Return:      The distance. Can be negative, or greater than the girder length.
   Float64 EndDistanceFromStation(Float64 station) const;

   void GetBrgStartPoint(IPoint2d** ppPoint) const;
   void GetBrgEndPoint(IPoint2d** ppPoint) const;
   void GetStartPoint(IPoint2d** ppPoint) const;
   void GetEndPoint(IPoint2d** ppPoint) const;
   void GetBearing(IDirection** ppBearing) const;

   // Returns the skew of the cross section from a normal
   // to the alignment. On curved bridges, the cross section is
   // skewed with respect to normals to the alignment
   void GetSectionSkew(Float64 station,IAngle** ppSkewAngle) const;

   bmfGirder* GetGirder() const;

   GirderIndexType GetGirderIdx() const;

   // ACCESS

   // Method:      Length
   // Description: Computes the length of the girder path
   // Return:      Length of the girder path (brg to brg)
   Float64 Length() const;
   
   // INQUIRY


protected:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   GirderIndexType m_GirderIdx;      // Index of associated girder

   Float64 m_OffsetStart;  // Offset from alignment at start of span
   bmfMeasuredWhere m_OffsetStartWhere; // Place where offset is measured
   bmfMeasuredHow   m_OffsetStartHow; // How offset is measured

   Float64 m_OffsetEnd;    // Offset from alignment at end of span
   bmfMeasuredWhere m_OffsetEndWhere; // Place where offset is measured
   bmfMeasuredHow   m_OffsetEndHow; // How offset is measured

   bmfSpan* m_pSpan;  // Associated span
   std::auto_ptr<bmfGirder> m_pGirder; // Associated Girder

   IDType m_StartBrgPnt;    // Id of cogo point at cl girder, cl bearing
   IDType m_StartGirderPnt; // Id of cogo point at cl girder, end of girder
   IDType m_EndBrgPnt;      // Id of cogo point at cl girder, cl bearing
   IDType m_EndGirderPnt;   // Id of cogo point at cl girder, end of girder

   // LIFECYCLE
   bmfGirderPath(const bmfGirderPath&);

   // OPERATORS
   bmfGirderPath& operator = (const bmfGirderPath& rOther);

   // OPERATIONS
   void DoLayoutPierPier();
   void DoLayoutPierBearing();
   void DoLayoutBearingPier();
   void DoLayoutBearingBearing();

   void ClearCogoPoints();
   void SetCogoPointIDs();

   // ACCESS
   void GetCogoModel(ICogoModel** ppModel) const;
   void GetAlignment(IAlignment** ppAlignment) const;

   void GetLine(ILine2d** line) const;

   // INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GIRDERPATH_H_
