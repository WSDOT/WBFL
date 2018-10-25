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

#ifndef INCLUDED_BRIDGEMODELING_PRECASTGIRDERSECTION_H_
#define INCLUDED_BRIDGEMODELING_PRECASTGIRDERSECTION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\ConcGirderSection.h>
#include <GeomModel\GeomModel.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gmPrecastBeam;
class matConcreteEx;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfPrecastGirderSection

   Precast girder section.


DESCRIPTION
   Precast girder section.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 07.24.1997 : Created file
*****************************************************************************/

class BMFCLASS bmfPrecastGirderSection : public bmfConcGirderSection
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Creates a new precast girder section. Creats a clone of the shape
   // and material.
   bmfPrecastGirderSection(const gmIPrecastBeam* pShape,
                           const matConcreteEx* pConc);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfPrecastGirderSection(const bmfPrecastGirderSection& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfPrecastGirderSection();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bmfPrecastGirderSection& operator = (const bmfPrecastGirderSection& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual bmfIGirderSection* CreateClone() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   const gmIPrecastBeam* GetGirderShape() const;

   //------------------------------------------------------------------------
   Float64 GetAvgWebWidth() const;

   //------------------------------------------------------------------------
   Float64 GetTopFlangeWidth() const;

   //------------------------------------------------------------------------
   Float64 GetTopWidth() const;

   //------------------------------------------------------------------------
   Float64 GetHeight() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy(const bmfPrecastGirderSection& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfPrecastGirderSection& rOther);

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

#endif // INCLUDED_BRIDGEMODELING_PRECASTGIRDERSECTION_H_

