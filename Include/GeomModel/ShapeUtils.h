///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2019  Washington State Department of Transportation
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

#ifndef INCLUDED_GEOMMODEL_SHAPEUTILS_H_
#define INCLUDED_GEOMMODEL_SHAPEUTILS_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeomModel\GeomModelExp.h>
#include <GeomModel\ShapeImp.h>
#include <GeomModel\Properties.h>
#include <GeomModel\ElasticProperties.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gmCompositeShape;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmShapeUtils

   Class to encapsulate utility functions for gmIShape-derived objects


DESCRIPTION
   All member functions should be static.

LOG
   rdp : 12.24.1997 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmShapeUtils
{
public:
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Copy cosmetic properties from one shape to another.
   static void CopyTraits(const gmShapeImp& rFrom, gmIShape* pTo);

   //------------------------------------------------------------------------
   // GetRootNode
   // Returns a pointer to the root node in a composite shape hierarchy.  If 
   // rShape is not a composite,  returns 0.
   static gmCompositeShape* GetRootNode(gmIShape& rShape);
   static const gmCompositeShape* GetRootNode(const gmIShape& rShape);

   //------------------------------------------------------------------------
   // Transforms elastic properties to a particular material.
   static gmProperties TransformProperties(const gmElasticProperties& ep,Float64 e);

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST


protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // Default constructor
   gmShapeUtils();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmShapeUtils();
   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   gmShapeUtils(const gmShapeUtils&);
   gmShapeUtils& operator=(const gmShapeUtils&) = delete;

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GEOMMODEL_SHAPEUTILS_H_
