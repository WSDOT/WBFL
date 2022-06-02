///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#ifndef INCLUDED_GEOMMODEL_IPRECASTBEAM_H_
#define INCLUDED_GEOMMODEL_IPRECASTBEAM_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

#include <GeomModel\ShapeImp.h>

// LOCAL INCLUDES
//


// FORWARD DECLARATIONS
//
struct IPlane3d;

// MISCELLANEOUS
//


/*****************************************************************************
CLASS 
   gmIPrecastBeam

   Abstract interface for precast beams

DESCRIPTION

LOG
   rab : 09.11.2001 : Created file (Never forget this day!)
*****************************************************************************/

class GEOMMODELCLASS gmIPrecastBeam : public gmShapeImp
{
public:

   // GROUP: ENUMERATIONS
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns the top flange width of the girder
   virtual Float64 GetTopFlangeWidth() const = 0;

   //------------------------------------------------------------------------
   // Returns the bottom flange width of the girder
   virtual Float64 GetBottomFlangeWidth() const = 0;

   //------------------------------------------------------------------------
   // Returns the total top width of the girder
   virtual Float64 GetTopWidth() const = 0;

   //------------------------------------------------------------------------
   // Returns the web width for shear
   virtual Float64 GetShearWidth() const = 0;

   //------------------------------------------------------------------------
   // Returns the minimum web width
   virtual Float64 GetMinWebWidth() const = 0;

   //------------------------------------------------------------------------
   // Returns the the overall girder height
   virtual Float64 GetHeight() const = 0;

   //------------------------------------------------------------------------
   // Returns the minimum bottom flange thickness
   virtual Float64 GetMinBottomFlangeThickness() const = 0;

   //------------------------------------------------------------------------
   // Returns the minimum top flange thickness
   virtual Float64 GetMinTopFlangeThickness() const = 0;

   //------------------------------------------------------------------------
   // Returns the number of mating surfaces
   virtual MatingSurfaceIndexType GetNumberOfMatingSurfaces() const = 0;

   //------------------------------------------------------------------------
   // Returns the width of the mating surface between the girder and a
   // composite slab. This may or may not be equal to the top flange width
   virtual Float64 GetMatingSurfaceWidth(MatingSurfaceIndexType idx) const = 0;

   //------------------------------------------------------------------------
   // Returns the location of the center of the mating surface, relative
   // to the centerline of the beam. The mating surface is left of the centerline if
   // the location is less than zero.
   virtual Float64 GetMatingSurfaceLocation(MatingSurfaceIndexType idx) const = 0;

   //------------------------------------------------------------------------
   // Returns true if the point is contained within the shape of the beam
   virtual bool Contains(const gpPoint2d& pnt) const = 0;

   //------------------------------------------------------------------------
   // Returns a plane object that represents the mid-plane member of a web
   virtual void GetWebPlane(WebIndexType webIdx,IPlane3d** ppPlane) const = 0;

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif 
