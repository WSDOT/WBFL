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

#ifndef INCLUDED_BRIDGEMODELING_IGIRDERSECTION_H_
#define INCLUDED_BRIDGEMODELING_IGIRDERSECTION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <GeomModel\GeomModel.h>
#include <GraphicsLib\PointMapper.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfIGirderSection

   Abstract base class for a girder section


DESCRIPTION
   Abstract base class for a girder section

COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.08.1998 : Created file
*****************************************************************************/

struct BMFCLASS bmfIGirderSection
{
   //------------------------------------------------------------------------
   virtual ~bmfIGirderSection() {}

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual bmfIGirderSection* CreateClone() const = 0;

   //------------------------------------------------------------------------
   virtual gmElasticProperties GetElasticProperties() const = 0;

   //------------------------------------------------------------------------
   virtual void Draw(HDC hdc,const grlibPointMapper& mapper) const = 0;

   //------------------------------------------------------------------------
   // Pure virtual function to get top flange width. This is used to determine
   // the mating surface with the slab, among other things.
   virtual Float64 GetTopFlangeWidth() const=0;

   //------------------------------------------------------------------------
   // Pure virtual function to get top flange width. This is used to determine
   // the mating surface with the slab, among other things.
   virtual Float64 GetTopWidth() const=0;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_IGIRDERSECTION_H_

