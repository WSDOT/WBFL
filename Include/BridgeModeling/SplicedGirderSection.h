///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEMODELING_SPLICEDGIRDERSECTION_H_
#define INCLUDED_BRIDGEMODELING_SPLICEDGIRDERSECTION_H_
#pragma once

// SYSTEM INCLUDES
//
#include <vector>

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\PrecastGirderSection.h>


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
   bmfSplicedGirderSection

   Cross section of a spliced precast girder.


DESCRIPTION
   Cross section of a spliced precast girder. This class extends bmfPrecastGirderSection
   by adding the voids in the cross section where the ducts are located

COPYRIGHT
   Copyright (c) 1997-2002
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.01.2002 : Created file
*****************************************************************************/

class BMFCLASS bmfSplicedGirderSection : public bmfPrecastGirderSection
{
public:
   // GROUP: LIFECYCLE
   struct Duct
   {
      gpPoint2d location;
      Float64 diameter; // diameter of the duct
   };

   //------------------------------------------------------------------------
   // Creates a new precast girder section. Creats a clone of the shape
   // and material.
   bmfSplicedGirderSection(const gmIPrecastBeam* pShape,
                           const std::vector<Duct>& ducts, // array of duct holes that will be deducted
                           const matConcreteEx* pConc);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfSplicedGirderSection(const bmfSplicedGirderSection& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfSplicedGirderSection();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bmfSplicedGirderSection& operator = (const bmfSplicedGirderSection& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual bmfIGirderSection* CreateClone() const;

   //------------------------------------------------------------------------
   const gmIPrecastBeam* GetBasicGirderShape() const;
 
   //------------------------------------------------------------------------
   const gmCompositeShape* GetGirderShape() const;

   // GROUP: ACCESS

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy(const bmfSplicedGirderSection& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfSplicedGirderSection& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY
   virtual void UpdateSection() const;

private:
   // GROUP: DATA MEMBERS
   std::vector<Duct> m_Ducts;

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

#endif // INCLUDED_BRIDGEMODELING_SPLICEDGIRDERSECTION_H_

