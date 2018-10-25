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

#ifndef INCLUDED_BRIDGEMODELING_SLAB_H_
#define INCLUDED_BRIDGEMODELING_SLAB_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <GraphicsLib\PointMapper.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bmfBridge;
class bmfSpan;
class matConcreteEx;

// MISCELLANEOUS
//
/*****************************************************************************
CLASS 
   bmfSlab

   Roadway surface of the bridge.

DESCRIPTION
   Roadway surface of the bridge.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class BMFCLASS bmfSlab
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   bmfSlab(const matConcreteEx* pConc, // slab concrete
           Float64 grossDepth,   // gross depth of slab
           Float64 overhang,     // distance from CL exterior girder to the edge of slab (Normal to cl girder)
           Float64 offset,       // dist from top of girder to top of slab
           Float64 sacDepth,     // depth of sacrificial wearing surface
           Float64 overlayDepth, // depth of overlay surfacing
           Float64 density       // density of overlay material
           );

   //------------------------------------------------------------------------
   // Copy constructor
   bmfSlab(const bmfSlab& slab);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfSlab(); 

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   bmfSlab& operator = (const bmfSlab& slab);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Draws the plane view of the slab
   void PlanView(HDC hDC,const grlibPointMapper& mapper) const;

   //------------------------------------------------------------------------
   // Gets the plan view extents of the slab.
   gpRect2d GetExtents() const;

   //------------------------------------------------------------------------
   void OnAlignmentChanged();

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the gross depth of the slab
   void SetGrossDepth(Float64 depth);

   //------------------------------------------------------------------------
   // Sets the the overhang distance from the exterior girder path to the
   // edge of the slab
   void SetOverhang(Float64 overhang);

   //------------------------------------------------------------------------
   // Sets the offset distance from the top of a supporting girder to the top
   // of the slab.
   void SetOffset(Float64 offset);

   //------------------------------------------------------------------------
   // Sets the overlay depth
   void SetOverlayDepth(Float64 depth);

   //------------------------------------------------------------------------
   // Sets the overlay density
   void SetOverlayDensity(Float64 density);

   //------------------------------------------------------------------------
   void SetConcrete(const matConcreteEx* pConc);

   //------------------------------------------------------------------------
   // Returns the gross depth of the slab
   Float64 GetGrossDepth() const;

   //------------------------------------------------------------------------
   // Returns the structural depth of the slab.
   // The structural depth is the gross depth less the sacraficial depth.
   Float64 GetStructuralDepth() const;

   //------------------------------------------------------------------------
   // Gets the the overhang distance from the exterior girder path to the
   // edge of the slab
   Float64 GetOverhang() const;

   //------------------------------------------------------------------------
   // Returns the offset distance from the top of a supporting girder to the
   // top of the slab.
   Float64 GetOffset() const;

   //------------------------------------------------------------------------
   // Returns the sacrafical depth of the slab.  If an overlay was specified,
   // zero is returned.
   Float64 GetSacraficialDepth() const;

   //------------------------------------------------------------------------
   // Returns the overlay depth.  If a sacraficial depth was specified,
   // zero is returned.
   Float64 GetOverlayDepth() const;

   //------------------------------------------------------------------------
   // Returns the density or the overlay material.  If a sacraficial depth 
   // was specified, zero is returned.
   Float64 GetOverlayDensity() const;

   //------------------------------------------------------------------------
   const matConcreteEx* GetConcrete() const;

   //------------------------------------------------------------------------
   void SetBridge(bmfBridge* pBridge);

   //------------------------------------------------------------------------
   // Returns the edge of slab to edge of slab width
   Float64 GetWidth() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy( const bmfSlab& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment( const bmfSlab& rOther);

   //------------------------------------------------------------------------
   // Returns the width of the frame between exterior girders
   Float64 FrameWidth(const bmfSpan* pSpan) const;

   // ACCESS
   // INQUIRY

private:
   // GROUP: DATA MEMBERS
   const matConcreteEx* m_pConc;
   Float64 m_GrossDepth;
   Float64 m_Overhang;
   Float64 m_SlabOffset;
   Float64 m_SacrificialDepth;
   Float64 m_OverlayDepth;
   Float64 m_OverlayDensity;

   mutable bool m_IsGeometryCorrect;
   // cogo point ids for slab corners
   mutable Int32 m_StartLeftId;  // start of bridge, left of alignment
   mutable Int32 m_StartRightId; // start of bridge, right of alignment
   mutable Int32 m_EndLeftId;    // end of bridge, left of alignment
   mutable Int32 m_EndRightId;   // end of bridge, right of alignment

   bmfBridge* m_pBridge;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   void UpdateGeometry() const;
   void ClearPoints() const; // removes the slab corner points from the cogo model

   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//
inline Float64 bmfSlab::GetGrossDepth() const {return m_GrossDepth;}
inline Float64 bmfSlab::GetOverhang() const {return m_Overhang;}
inline Float64 bmfSlab::GetOffset() const {return m_SlabOffset;}
inline Float64 bmfSlab::GetSacraficialDepth() const { return m_SacrificialDepth; }
inline Float64 bmfSlab::GetOverlayDepth() const { return m_OverlayDepth; }
inline Float64 bmfSlab::GetOverlayDensity() const { return m_OverlayDensity; }

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_SLAB_H_
