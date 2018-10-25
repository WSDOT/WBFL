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

#ifndef INCLUDED_COGO_IMODEL_H_
#define INCLUDED_COGO_IMODEL_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <WbflTypes.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gpPoint2d;
class gpSize2d;
class cogoCurve;
class cogoRoadway;

// MISCELLANEOUS
//
#define COGO_ERROR      -1

/*****************************************************************************
INTERFACE 
   cogoIModel

   Interface for a coordinate geometry model.

DESCRIPTION
   Interface for a coordinate geometry model.
   Used to manipulate COGO primitives

LOG
   Richard Brice : 04.22.1999 : Created File
*****************************************************************************/

struct cogoIModel
{
   //------------------------------------------------------------------------
   virtual ~cogoIModel() {}

   // GROUP: OPERATIONS - Points
   
   //------------------------------------------------------------------------
   // Stores a new point in the COGO model. Returns point id or COGO_ERROR
   virtual Int32 StorePoint(Float64 x,Float64 y) = 0;

   //------------------------------------------------------------------------
   // Stores a new point in the COGO model. Returns point id or COGO_ERROR
   virtual Int32 StorePoint(const gpPoint2d& rPnt) = 0;

   //------------------------------------------------------------------------
   // Assigns a copy of point id to pnt.  Returns false
   // if point id is not defined in the model.
   virtual bool GetPoint(gpPoint2d* pPnt,Int32 id) const = 0;

   //------------------------------------------------------------------------
   // Retreives a vector of points.  For each point id in id, the 
   // corrosponding point is stored in points.  Returns true
   // if all poitns in id where found, otherwise false. To
   // determine the number of points found, call points.size().
   virtual bool GetPoints(std::vector<gpPoint2d>* pPoints,
                          const std::vector<Int32>& id) const = 0;

   //------------------------------------------------------------------------
   // Fills points with all of the points in the model.
   virtual void GetPoints(std::vector<gpPoint2d>* pPoints) const = 0;

   //------------------------------------------------------------------------
   // Removes a point from the cogo model.
   virtual bool RemovePoint(Int32 id) = 0;

   //------------------------------------------------------------------------
   // Moves the point to a new position
   virtual bool MovePoint(Int32 id, Float64 newX, Float64 newY) = 0;

   //------------------------------------------------------------------------
   // Moves the point to a new position
   virtual bool MovePoint(Int32 id, const gpPoint2d& newPoint) = 0;

   //------------------------------------------------------------------------
   // Offsets a point
   virtual bool OffsetPoint(Int32 id, Float64 dx, Float64 dy) = 0;

   //------------------------------------------------------------------------
   // Offsets a point
   virtual bool OffsetPoint(Int32 id, const gpSize2d& offset) = 0;

   // GROUP: OPERATIONS - Curves

   //------------------------------------------------------------------------
   virtual Int32 StoreCurve(const cogoCurve& curve) = 0;
   //------------------------------------------------------------------------
   virtual Int32 StoreCurve(const gpPoint2d& pc,const gpPoint2d& pi,const gpPoint2d& pt,const gpPoint2d& cc) = 0;
   //------------------------------------------------------------------------
   virtual Int32 StoreCurve(Int32 pc,Int32 pi,Int32 pt,Int32 cc) = 0;

   //------------------------------------------------------------------------
   virtual bool GetCurve(cogoCurve* pCurve,Int32 id) = 0;

   //------------------------------------------------------------------------
   virtual bool ReplaceCurve(const cogoCurve& curve,Int32 id) = 0;

   //------------------------------------------------------------------------
   virtual bool RemoveCurve(Int32 id) = 0;

   // GROUP: OPERATIONS - Alignments

   //------------------------------------------------------------------------
   // Creates an Alignment chain using two points
   virtual Int32 CreateAlignment(Int32 id1,Int32 id2) = 0;

   //------------------------------------------------------------------------
   // Creates an Alignment chain using a curve
   virtual Int32 CreateAlignment(Int32 id) = 0;

   //------------------------------------------------------------------------
   // Returns a pointer to a previously created Alignment chain
   virtual cogoRoadway* GetAlignment(Int32 id) = 0;

   //------------------------------------------------------------------------
   virtual const cogoRoadway* GetAlignment(Int32 id) const = 0;

   //------------------------------------------------------------------------
   // Destroy a previously created Alignment chain
   virtual bool RemoveAlignment(Int32 id) = 0;

   // GROUP: OPERATIONS - Misc

   //------------------------------------------------------------------------
   // Clears the entire cogo model.  All points and alignments are destroyed.
   // Point and Alignment indices are reset.
   virtual void Clear() = 0;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

#endif // INCLUDED_COGO_IMODEL_H_
