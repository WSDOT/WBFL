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

#ifndef INCLUDED_BRIDGEMODELING_CONCRETEGIRDERSECTION_H_
#define INCLUDED_BRIDGEMODELING_CONCRETEGIRDERSECTION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\IGirderSection.h>
#include <GeomModel\GeomModel.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gmIShape;
class matConcreteEx;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfConcGirderSection

   Concrete girder section.


DESCRIPTION
   Concrete girder section.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 07.24.1997 : Created file
*****************************************************************************/

class BMFCLASS bmfConcGirderSection : public bmfIGirderSection
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Creates a new girder section. Creats a clone of the shape and material.
   bmfConcGirderSection(const gmIShape* pShape,
                        const matConcreteEx* pConc);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfConcGirderSection(const bmfConcGirderSection& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfConcGirderSection();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bmfConcGirderSection& operator = (const bmfConcGirderSection& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual gmElasticProperties GetElasticProperties() const;

   //------------------------------------------------------------------------
   virtual void Draw(HDC hdc,const grlibPointMapper& mapper) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Pure virtual function to get top flange width. This is used to determine
   // the mating surface with the slab, among other things.
   virtual Float64 GetTopFlangeWidth() const=0;

   //------------------------------------------------------------------------
   const gmIShape* GetGirderShape() const;

   //------------------------------------------------------------------------
   const matConcreteEx* GetConcrete() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   mutable bool m_bUpdateSection;
   mutable std::auto_ptr<gmCompositeShape> m_pShape;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy(const bmfConcGirderSection& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const bmfConcGirderSection& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY
   virtual void UpdateSection() const;

private:
   // GROUP: DATA MEMBERS
   mutable std::auto_ptr<gmSection> m_pSection;
   const matConcreteEx* m_pConc;

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

#endif // INCLUDED_BRIDGEMODELING_CONCRETEGIRDERSECTION_H_

