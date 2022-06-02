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

#ifndef INCLUDED_BRIDGEMODELING_SPAN_H_
#define INCLUDED_BRIDGEMODELING_SPAN_H_
#pragma once

// SYSTEM INCLUDES
//
#include <boost\shared_ptr.hpp>

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>

// LOCAL INCLUDES
//
#include <GraphicsLib\PointMapper.h>

// FORWARD DECLARATIONS
//
class bmfBridge;
class bmfGirder;
class bmfGirderPath;
class bmfPier;
class bmfGirderTemplate;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfSpan

   A structural component connecting adjacent piers.
   This is a composite component consisting of girder paths
   and girders associated with the girder paths.

DESCRIPTION
   A structural component connecting adjacent piers.
   This is a composite component consisting of girder paths
   and girders associated with the girder paths.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class BMFCLASS bmfSpan
{
public:
   enum Side { Left, Right };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfSpan();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfSpan(); 

   // GROUP: OPERATORS

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Creates a new girder on <i>gdrPathIdx</i> conforming to template <i>name</i>.
   // If a girder currently assigned to the subject path, it is deleted.
   void CreateGirder(bmfGirderTemplate* pTpl,GirderIndexType gdrPathIdx = -1);

   //------------------------------------------------------------------------
   // Returns a pointer to the girder associated with the girder path
   // defined by <i>gdrPathIdx</i>. Returns 0 if a girder does not exist
   // on the specified path.
   bmfGirder* GetGirder(GirderIndexType gdrPathIdx);

   //------------------------------------------------------------------------
   const bmfGirder* GetGirder(GirderIndexType gdrPathIdx) const;

   //------------------------------------------------------------------------
   void GetGirders(std::vector<bmfGirder*>& vGirders);

   //------------------------------------------------------------------------
   void GetGirders(std::vector<const bmfGirder*>& vGirders) const;

   //------------------------------------------------------------------------
   // Called by the framework,  just after the span is added to a bridge.
   virtual void OnSetup();

   //------------------------------------------------------------------------
   // Called by framework, just after the pier at the start of the span is 
   // changed.  This is the first chance for the span to do something with 
   // the pier.
   virtual void OnStartPierChanged();

   //------------------------------------------------------------------------
   // Called by framework, immediately after the pier at the
   // end of the span is replaced.
   virtual void OnEndPierChanged();

   //------------------------------------------------------------------------
   // Called by the framework when ever the alignment changes.
   virtual void OnAlignmentChanged();

   //------------------------------------------------------------------------
   // Generates girder parallel girder lines
   void LayoutGirderPaths(GirderIndexType nGirders,
                          Float64 spacing,
                          bmfMeasuredWhere where,
                          bmfMeasuredHow how);

   //------------------------------------------------------------------------
   // Retreives the girder line layout information
   void GetGirderPathLayout(GirderIndexType& nGirders,
                            Float64& spacing,
                            bmfMeasuredWhere& where,
                            bmfMeasuredHow& how) const;

   //------------------------------------------------------------------------
   // Removes all the girder paths from the span
   void ClearGirderPaths();

   //------------------------------------------------------------------------
   // Draws the plan view of the span
   virtual void PlanView(HDC hDC, const grlibPointMapper& mapper,
                         bool bLabelAlignment=true, bool bLabelGirders=true ) const;

   //------------------------------------------------------------------------
   virtual gpRect2d GetBoundingBox() const;

   // GROUP: ACCESS
   
   //------------------------------------------------------------------------
   // Sets the span identifier
   void SetID(SpanIDType id);

   //------------------------------------------------------------------------
   // Returns the span identifier
   SpanIDType GetID() const;
   
   //------------------------------------------------------------------------
   // Returns the span length measured aInt32 the alignment
   Float64 GetLength() const; 

   //------------------------------------------------------------------------
   // Returns the spacing between girder paths, measured
   // normal to the referenced girder path.  If the specified <i>gdrPathIdx</i>
   // and <i>side</i> represent the exterior side of an exterior girder path,
   // the distance to the edge of the slab is returned. If there is not a
   // slab, zero is returned.
   Float64 GetGirderPathSpacing(GirderIndexType gdrPathIdx,
                               Side side,
                               Float64 distFromStart);

   //------------------------------------------------------------------------
   // Returns the horizontal normal offset distance from the roadway alighment
   // to the girder path at a station
   Float64 GetGirderPathOffset(GirderIndexType gdrPathIdx, Float64 station) const;

   //------------------------------------------------------------------------
   // Returns the tributary slab width, measured normal to the
   // referenced girder path.
   Float64 GetTributaryWidth(GirderIndexType gdrPathIdx, Float64 distFromStart);

   //------------------------------------------------------------------------
   // Returns the number of girder paths in this span
   GirderIndexType GetGirderPathCount() const;

   //------------------------------------------------------------------------
   // Returns a pointer to the containing bridge object
   bmfBridge* GetBridge() const;

   //------------------------------------------------------------------------
   // Associates a bridge with this span
   void SetBridge(bmfBridge* pBridge);

   //------------------------------------------------------------------------
   // Returns a pointer to the pier at the start of the span
   bmfPier* GetStartPier() const;

   //------------------------------------------------------------------------
   // Connects the start end of this span to a pier.
   void SetStartPier(bmfPier* pPier);

   //------------------------------------------------------------------------
   // Returns a pointer to the pier at the end of the span
   bmfPier* GetEndPier() const;

   //------------------------------------------------------------------------
   // Connects the end end of this span to a pier.
   void SetEndPier(bmfPier* pPier);

   //------------------------------------------------------------------------
   // Returns the station at the start of the span
   Float64 StartStation() const;

   //------------------------------------------------------------------------
   // Returns the bearing line station at the start of the span
   Float64 StartBrgStation() const;

   //------------------------------------------------------------------------
   // Returns the station at the end of the span
   Float64 EndStation() const;

   //------------------------------------------------------------------------
   // Returns the bearing line station at the end of the span
   Float64 EndBrgStation() const;

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Returns the bearing of the centerline of this span
   void GetBearing(IDirection** ppBearing) const;

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void UpdateGirderPaths();

   //------------------------------------------------------------------------
   // Called by the framework when a girder is created. Does nothing by 
   // default. Derived class can override this method to perform additional
   // initialization.
   virtual void DoInitGirder( bmfGirder* pGirder );

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void StoreGirderPath(GirderIndexType gdrPathIdx, bmfGirderPath* pGirderPath);

   //------------------------------------------------------------------------
   bmfGirderPath* GetGirderPath(GirderIndexType gdrPathIdx) const;

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   bool IsInteriorGirderPath(GirderIndexType gdrPathIdx) const;

   //------------------------------------------------------------------------
   bool IsExteriorGirderPath(GirderIndexType gdrPathIdx) const;

   //------------------------------------------------------------------------
   bool IsFirstGirderPath(GirderIndexType gdrPathIdx) const;

   //------------------------------------------------------------------------
   bool IsLastGirderPath(GirderIndexType gdrPathIdx) const;

private:
   // GROUP: DATA MEMBERS
   SpanIDType m_ID;
   bmfBridge* m_pBridge;
   bmfPier* m_pStartPier;
   bmfPier* m_pEndPier;

   // These will change when variable girder spacing is used
   GirderIndexType m_GirderCount;
   Float64 m_GirderLineSpacing;
   bmfMeasuredWhere m_Where;
   bmfMeasuredHow m_How;
/*
   Int32 m_RefGirderIndex;
   GirderLineLayout m_RefGirderStartLocation;
   GirderLineLayout m_RefGirderEndLocation;
*/
   // :COMPILER: rab 11.18.96 : Supressed warning
   // :FILE: Span.h
   // Warning C4251 has been suppressed. No need to export private data
   #pragma warning (disable : 4251)
   typedef std::vector<boost::shared_ptr<bmfGirderPath> > GirderPathContainer;
   typedef GirderPathContainer::iterator GirderPathIterator;
   typedef GirderPathContainer::const_iterator ConstGirderPathIterator;
   GirderPathContainer m_GirderPaths;


   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS

   // GROUP: INQUIRY
};

// INLINE METHODS
//
inline CollectionIndexType bmfSpan::GetGirderPathCount() const { return m_GirderPaths.size(); }

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_SPAN_H_
