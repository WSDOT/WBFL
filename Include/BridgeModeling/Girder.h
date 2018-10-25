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

#ifndef INCLUDED_BRIDGEMODELING_GIRDER_H_
#define INCLUDED_BRIDGEMODELING_GIRDER_H_
#pragma once

// SYSTEM INCLUDES
//
#if defined _DEBUG
#include <iostream>
#endif // _DEBUG

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\GirderTemplate.h>
#include <BridgeModeling\GirderPath.h>
#include <System\SectionValue.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
struct bmfIGirderSection;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfGirder

   A Girder is a component that is part of a span.

DESCRIPTION
   A Girder is a component that is part of a span.  A basic girder is
   described by its cross section and its location within a span.
   
   The girder's cross section is descibed by bmfGirderShape objects. For non-
   prismatic girders, a step-wise approximation of is used. The girder's
   cross section is assumed to be constant between bmfGirderShapes. 
   Care must be taken when specifing the location of GirderShape objects.
   The bmfGirderShapes must be defined in such a way that they do not extent
   beyond the end of the girder.

   The girder's location is defined by associating a bmfGirder with a bmfGirderPath.
   The association, along with the bmfConnection at the Span - Pier interface
   define the girder's length and position.

   When the geometry of the parent span changes, OnSpanChanged() is called.
   This is a virtual method that you can extend in subclasses.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class BMFCLASS bmfGirder
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   bmfGirder( bmfGirderTemplate* pTpl );

   //------------------------------------------------------------------------
   // Copy constructor.
   bmfGirder(const bmfGirder& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfGirder(); 

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   bmfGirder& operator = (const bmfGirder& rOther );

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual void PlanView(HDC hDC,const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   // Creates a section object that will represent the girder's cross section
   // at <i>distFromStart</i> from the start of the girder.  You are
   // responsible for the destruction of this shape object.
   virtual bmfIGirderSection* CreateGirderSection(Float64 distFromStart) const = 0;

   //------------------------------------------------------------------------
   virtual gpRect2d GetBoundingBox() const = 0;

   //------------------------------------------------------------------------
   // Called by the associated girder path when it changes.
   virtual void OnGirderPathChanged();
   
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the horizonal span length of the girder component measured
   // between points of bearing.
   Float64 GetSpanLength() const;

   //------------------------------------------------------------------------
   // Returns the length of the girder, measured between girder ends,
   // accounting for horizontal and vertical geometric effects.
   Float64 GetLength() const;

   //------------------------------------------------------------------------
   // Adds the girder to a span.
   void Associate( const bmfSpan* pSpan, const bmfGirderPath* pGirderPath );

   //------------------------------------------------------------------------
   const bmfSpan* GetSpan() const;

   //------------------------------------------------------------------------
   const bmfGirderPath* GetGirderPath() const;

   //------------------------------------------------------------------------
   Float64 GetLeftEndSize() const;

   //------------------------------------------------------------------------
   Float64 GetRightEndSize() const;

   //------------------------------------------------------------------------
   // Distance from C.L. Pier to bearing along girder
   Float64 GetLeftBearingOffset() const;

   //------------------------------------------------------------------------
   Float64 GetRightBearingOffset() const;

   //------------------------------------------------------------------------
   bmfGirderTemplate* GetTemplate();
   const bmfGirderTemplate* GetTemplate() const;

   // GROUP: INQUIRY

#if defined _DEBUG
   virtual void Dump(std::_tostream& os);
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS

   //------------------------------------------------------------------------
   // Pointer to the parent span.
   const bmfSpan* m_pSpan;

   //------------------------------------------------------------------------
   // Pointer to the template upon which this girder is based.
   bmfGirderTemplate* m_pTemplate;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bmfGirder& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfGirder& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   const bmfGirderPath* m_pGirderPath;  // The associated girder path

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

#endif // INCLUDED_BRIDGEMODELING_GIRDER_H_
