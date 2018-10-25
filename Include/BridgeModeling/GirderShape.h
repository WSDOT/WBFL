///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODELING_GIRDERSHAPE_H_
#define INCLUDED_BRIDGEMODELING_GIRDERSHAPE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <GeomModel\GeomModel.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfGirderShape

   Represents the shape of a girder.

DESCRIPTION
   Represents the shape of a girder.
   This is an abstract base class that provides an interface for functionality
   that is common to all girder shapes.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class BMFCLASS bmfGirderShape : public gmShapeImp
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   virtual ~bmfGirderShape() {}

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Creates a clone of this girder shape
   virtual bmfGirderShape* CreateClone() const = 0;

   //------------------------------------------------------------------------
   // Draws the girder cross section using the supplied device context and
   // mapping tool.
   virtual void Draw(HDC hdc,const grlibPointMapper& mapper) const = 0;

   //------------------------------------------------------------------------
   // Returns the geometric properties of the girder shape.
   // Subclasses might want to provide extended versions of this method
   // that return shape-specific properties.
   virtual gmProperties GetProperties() const = 0;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_GIRDERSHAPE_H_
