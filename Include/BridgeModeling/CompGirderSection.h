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

#ifndef INCLUDED_BRIDGEMODELING_COMPGIRDERSECTION_H_
#define INCLUDED_BRIDGEMODELING_COMPGIRDERSECTION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\GirderSection.h>
#include <Material\ConcreteEx.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfCompGirderSection

   Composite girder section.


DESCRIPTION
   Composite girder section.
   Provides composite girder section properties in the form of elastic
   properties from the Geometric Modeling Package.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 04.11.1997 : Created file
*****************************************************************************/

class BMFCLASS bmfCompGirderSection : public bmfGirderSection
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   bmfCompGirderSection(const gmIShape* pGdrShape,
                        const matConcreteEx* pGdrConc,
                        Float64 tribWidth,Float64 effWidth,
                        Float64 grossDepth,Float64 sacDepth,
                        const matConcreteEx* pSlabConc);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfCompGirderSection(const bmfCompGirderSection& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfCompGirderSection();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bmfCompGirderSection& operator = (const bmfCompGirderSection& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   bmfGirderSection* CreateClone() const;

   //------------------------------------------------------------------------
   gmElasticProperties GetElasticProperties() const;

   //------------------------------------------------------------------------
   void Draw(HDC hdc,const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   // Section modulus for the top of the girder. S = Icomposite / YtopGirder
   Float64 GetStopGirder() const;

   //------------------------------------------------------------------------
   // Distance from the centriod of the composite section to the top of
   // the girder
   Float64 GetYtopGirder() const;

   //------------------------------------------------------------------------
   // Returns the first moment of area of the slab.
   Float64 GetQslab() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Changes the girder shape.
   void SetGirderShape(const gmIShape* pGdrShape);

   //------------------------------------------------------------------------
   // Returns a reference to the girder shape.
   const gmIShape* GetGirderShape() const;

   //------------------------------------------------------------------------
   // Sets the tributary slab width
   void SetTribWidth( Float64 tribWidth );

   //------------------------------------------------------------------------
   // Returns the tributary slab width
   Float64 GetTribWidth() const;

   //------------------------------------------------------------------------
   // Sets the effective slab width
   void SetEffWidth( Float64 effWidth );

   //------------------------------------------------------------------------
   // Returns the effective slab width
   Float64 GetEffWidth() const;

   //------------------------------------------------------------------------
   // Sets the gross slab depth
   void SetGrossDepth( Float64 grossDepth );

   //------------------------------------------------------------------------
   // Returns the gross slab depth
   Float64 GetGrossDepth() const;

   //------------------------------------------------------------------------
   // Sets the sacrificial slab depth
   void SetSacrificialDepth( Float64 sacDepth );

   //------------------------------------------------------------------------
   // Returns the sacrificial slab depth
   Float64 GetSacrificialDepth() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const bmfCompGirderSection& rOther);
   void MakeAssignment(const bmfCompGirderSection& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   const gmIShape* m_pGdrShape;
   const matConcreteEx* m_pGdrConc;
   const matConcreteEx* m_pSlabConc;
   Float64 m_TribWidth;
   Float64 m_EffWidth;
   Float64 m_GrossDepth;
   Float64 m_SacDepth;

   mutable Float64 m_StopGirder;
   mutable Float64 m_YtopGirder;
   mutable Float64 m_Qslab;
   mutable gmElasticProperties m_Props;
   mutable bool m_bUpdateProperties;
   mutable gmSection m_Section;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void UpdateProperties() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_COMPGIRDERSECTION_H_

