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

#ifndef INCLUDED_BRIDGEMODELING_BRIDGE_H_
#define INCLUDED_BRIDGEMODELING_BRIDGE_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\Pier.h>
#include <BridgeModeling\Span.h>
#include <BridgeModeling\Slab.h>
#include <BridgeModeling\PierLayout.h>
#include <BridgeModeling\Connection.h>
#include <System\NextAvailableId.h>
#include <System\SubjectT.h>
#include <GeomModel\CompositeShape.h>
#include <UnitMgt\UnitMgt.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bmfSpanFactory;
class bmfPierFactory;
class bmfSlab;
class bmfBridge;
class bmfTrafficBarrier;
class bmfTrafficBarrierTemplate;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfBridgeObserver

   A pure virtual entry class for observing bmfBridge objects.


DESCRIPTION
   A pure virtual entry class for observing bmfBridge objects.

COPYRIGHT
   Copyright © 1999-2022
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 09.10.1998 : Created class
*****************************************************************************/
class BMFCLASS bmfBridgeObserver
{
public:

   // GROUP: LIFECYCLE
   virtual ~bmfBridgeObserver(){}

   //------------------------------------------------------------------------
   // Called by our subject to let us now he's changed.
   virtual void Update(bmfBridge* pSubject, Uint32 hint) = 0;
};

/*****************************************************************************
CLASS 
   bmfBridge

   Surrogate for a physical bridge struture.

DESCRIPTION
   Surrogate for a physical bridge struture.

   A bridge must be attached to an alignment.  When the alignment changes the
   bridge model automatically updates its geometry.

   Clients of the bridge model can be observers of the bridge.  When any
   aspect of the bridge is modified,  the observer is notified.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/
BMFTPL sysSubjectT<bmfBridgeObserver,bmfBridge>;
typedef sysSubjectT<bmfBridgeObserver,bmfBridge> bmfBridgeBase;

class BMFCLASS bmfBridge : public bmfBridgeBase
{
public:
   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   bmfBridge(ICogoModel* pCogoModel,IDType alignmentID);

   //------------------------------------------------------------------------
   bmfBridge(const bmfBridge& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfBridge(); 

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   bmfBridge& operator=(const bmfBridge& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual bmfBridge* CreateClone() const;

   //------------------------------------------------------------------------
   // Creates a span in the bridge,  connecting the specified piers.
   // Returns a pointer to the span.  Returns NULL if an error occurs.
   bmfSpan* CreateSpan(SpanIDType id,PierIDType startPierId,PierIDType endPierId);

   //------------------------------------------------------------------------
   // Adds a span to the bridge model, connecting it to the specified piers.
   // The model assumes ownership of the span.  Returns true on success,
   // otherwise false.
   bool AddSpan(bmfSpan* pSpan,SpanIDType id,PierIDType startPierId,PierIDType endPierId);

   //------------------------------------------------------------------------
   // Removes a span from the model. All components associated with the
   // span are destroyed as well (such as girders).
   void RemoveSpan(SpanIDType spanId);

   //------------------------------------------------------------------------
   // Returns a pointer to the span object.
   const bmfSpan* GetSpan(SpanIDType spanId) const;

   //------------------------------------------------------------------------
   bmfSpan* GetSpan(SpanIDType spanId);

   //------------------------------------------------------------------------
   // Returns the span contained at the given station. Returns zero if none
   const bmfSpan* GetSpanAtStation(Float64 station) const;

   //------------------------------------------------------------------------
   void GetSpans(std::vector<bmfSpan*>& vSpans);

   //------------------------------------------------------------------------
   void GetSpans(std::vector<const bmfSpan*>& vSpans) const;

   //------------------------------------------------------------------------
   SpanIndexType GetSpanCount() const;

   //------------------------------------------------------------------------
   bmfPier* CreatePier(PierIDType id,Float64 station,const bmfPierLayout& pl,const bmfConnection* pConnection);

   //------------------------------------------------------------------------
   // Adds a pier to the bridge.
   // Calls SetupPier().
   // Returns the identifier of the pier. This is a key that you will use
   // later to gain access to the pier.
   void AddPier(bmfPier* pPier,
                PierIDType id,
                Float64 station); // Location of the pier

   //------------------------------------------------------------------------
   void AddPier(PierIDType id, bmfPier* pPier);

   //------------------------------------------------------------------------
   // Removes a pier. All components associated with the
   // pier are destroyed as well.
   void RemovePier(PierIDType pierId); 

   //------------------------------------------------------------------------
   // Returns a pointer to the pier object.
   bmfPier* GetPier(PierIDType pierId) const;

   //------------------------------------------------------------------------
   void GetPiers(std::vector<bmfPier*>& vPiers);

   //------------------------------------------------------------------------
   void GetPiers(std::vector<const bmfPier*>& vPiers) const;

   //------------------------------------------------------------------------
   PierIndexType GetPierCount() const;

   //------------------------------------------------------------------------
   // Sets the slab for the bridge.
   void SetSlab(const bmfSlab& rSlab);

   //------------------------------------------------------------------------
   // Returns a pointer to the slab.
   const bmfSlab* GetSlab() const;

   //------------------------------------------------------------------------
   bmfSlab* GetSlab();

   //------------------------------------------------------------------------
   void CreateLeftTrafficBarrier(const bmfTrafficBarrierTemplate* pTpl);

   //------------------------------------------------------------------------
   void RemoveLeftTrafficBarrier();

   //------------------------------------------------------------------------
   const bmfTrafficBarrier* GetLeftTrafficBarrier() const;

   //------------------------------------------------------------------------
   bmfTrafficBarrier* GetLeftTrafficBarrier();

   //------------------------------------------------------------------------
   void CreateRightTrafficBarrier(const bmfTrafficBarrierTemplate* pTpl);

   //------------------------------------------------------------------------
   void RemoveRightTrafficBarrier();

   //------------------------------------------------------------------------
   const bmfTrafficBarrier* GetRightTrafficBarrier() const;

   //------------------------------------------------------------------------
   bmfTrafficBarrier* GetRightTrafficBarrier();

   Float64 GetRoadwayWidth(Float64 station) const;

   //------------------------------------------------------------------------
   // Draws a plan view of the bridge
   // Settings are defined in DrawSettings.h
   virtual void PlanView(HDC hDC,       // Handle to a device context
                         RECT& rect,    // Rectangle in which to draw
                         UINT settings  // on/off settings
                         ) const;

   //------------------------------------------------------------------------
   // Draws a cross section of the bridge at the specified station.  If
   // station is before or after the end of the bridge nothing is drawn and
   // false is returned.  Returns true on success.
   // Settings are defined in DrawSettings.h
   virtual bool DrawSection(HDC hDC,                     // Handle to a device context
                            RECT& rect,                  // Rectangle in which to draw
                            Float64 station,             // station were the section is taken
                            UINT settings,               // on/off settings
                            const unitmgtLengthData& rlen// length units
                            ) const;

   //------------------------------------------------------------------------
   // consistent line width for drawing bridge elements
   // returns line width in logical coords of dc
   static int GetSolidLineWidth(HDC hDC)
   {
      // assume aspect ratio difference is not huge - only look at x dimension
      int dx = (int)::GetDeviceCaps(hDC, LOGPIXELSX);
      POINT pt[2] = { {0,0}, {dx,0}};
      ::DPtoLP(hDC,pt,2);

      // line width of about 1/2 pt
      int lx = (int)Round((float)(pt[1].x - pt[0].x) * 0.007);

      return lx;
   }

   // 
   //------------------------------------------------------------------------
   // Moves a pier to a new station
   void MovePier(PierIDType pierId,     // Id of the pier
                 Float64 station); // New station for the pier

   //------------------------------------------------------------------------
   // Gets the location of a pier
   Float64 GetPierStation(PierIDType pierId) const;

   //------------------------------------------------------------------------
   // Gets the orientation of a pier. The bearing is measured
   // counter clockwise from due East in radians.
   void GetPierBearing(PierIDType pierId,IDirection** ppBearing) const;

   //------------------------------------------------------------------------
   // Creates equally spaced, parallel girder paths within
   // a span.  The girder paths are positioned symetrically
   // with respect to the alignment at the start of the span.
   void LayoutGirderPaths(SpanIDType spanId,         // Id of the span
                          GirderIndexType nGirdersPaths,  // Number of girder paths to create
                          Float64 spacing,      // Girder path spacing
                          bmfMeasuredWhere where, // Where the spacing is measured
                          bmfMeasuredHow how);    // How the spacing is measured

   //------------------------------------------------------------------------
   // Creates a new girder in span spanId on gdrPathIdx conforming to template.
   // If a girder currently assigned to the subject path, it is deleted.
   void CreateGirder(SpanIDType spanId,bmfGirderTemplate* pTpl,GirderIndexType gdrPathIdx);

   //------------------------------------------------------------------------
   bmfGirder* GetGirder(SpanIDType spanId,GirderIndexType gdrPathIdx);

   //------------------------------------------------------------------------
   const bmfGirder* GetGirder(SpanIDType spanId,GirderIndexType gdrPathIdx) const;

   //------------------------------------------------------------------------
   // Destroys all piers and piers
   void Clear();

   //------------------------------------------------------------------------
   // Returns the length of the bridge, measured aInt32 the alignment
   Float64 GetLength();

   //------------------------------------------------------------------------
   // Returns the length of a span, measured aInt32 the alignment
   Float64 GetSpanLength(SpanIDType spanId);

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void GetCogoModel(ICogoModel** ppModel);

   //------------------------------------------------------------------------
   void GetAlignment(IAlignment** ppAlignment);

   //------------------------------------------------------------------------
   // Assigns a connection to a pier
   void SetPierConnection(PierIDType pierId,
                          const bmfConnection* pConnection);

   //------------------------------------------------------------------------
   // Orients a pier with respect to the alignment
   void LayoutPier(PierIDType pierId,
                   const bmfPierLayout& pl);

   //------------------------------------------------------------------------
   // Returns a copy of a pier's layout information
   bmfPierLayout GetPierLayout(PierIDType pierId) const;

   //------------------------------------------------------------------------
   // Returns the number of girder paths in a span
   GirderIndexType GetGirderPathCount(SpanIDType spanId) const;

   //------------------------------------------------------------------------
   // This method is only applicable for equally spaced,
   // parallel girder paths, as described with 
   // LayoutGirderPaths() above.
   void GetGirderPathLayout(SpanIDType spanId,
                            GirderIndexType& nGirders,
                            Float64& spacing,
                            bmfMeasuredWhere& where,
                            bmfMeasuredHow& how) const;

   //------------------------------------------------------------------------
   // Sets the span factory and returns a pointer to the previous span 
   // factory.  You are responsible for deleting the returned factory.
   // The framework assumes ownership of the supplied factory.
   bmfSpanFactory* SetSpanFactory(bmfSpanFactory* pFactory);

   //------------------------------------------------------------------------
   // Sets the pier factory and returns a pointer to the previous span 
   // factory.  You are responsible for deleting the returned factory.
   // The framework assumes ownership of the supplied factory.
   bmfPierFactory* SetPierFactory(bmfPierFactory* pFactory);

   //------------------------------------------------------------------------
   virtual void OnAlignmentChanged();

   // GROUP: INQUIRY

#if defined _DEBUG
   void DumpGirder(SpanIDType spanId,GirderIndexType gdrPathIdx,LPCTSTR fname);
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy(const bmfBridge& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const bmfBridge& rOther);

   //------------------------------------------------------------------------
   virtual void DoDrawPlanView(HDC hDC, const grlibPointMapper& mapper,
                               bool bLabelGirders, bool bLabelAlignment, 
                               bool bLabelPiers) const;

   //------------------------------------------------------------------------
   // Called when ever a span is added to the model.
   virtual void SetupSpan(bmfSpan* pSpan);

   //------------------------------------------------------------------------
   // Called when ever a pier is added to the model.
   virtual void SetupPier(bmfPier* pPier);

   //------------------------------------------------------------------------
   virtual gpRect2d GetBoundingBox() const;

   // GROUP: ACCESS

   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   CComPtr<IAlignment>     m_Alignment;
   CComPtr<ICogoModel>     m_CogoModel;
   std::auto_ptr<bmfSlab> m_pSlab;
   std::auto_ptr<bmfSpanFactory> m_pSpanFactory;
   std::auto_ptr<bmfPierFactory> m_pPierFactory;
   std::auto_ptr<bmfTrafficBarrier> m_pLeftBarrier;
   std::auto_ptr<bmfTrafficBarrier> m_pRightBarrier;

   CComPtr<IUnknown> m_AlignmentObserver;

   // :COMPILER: rab 11.18.96 : Supressed warning
   // :FILE: Bridge.h
   // Warning C4251 has been suppressed. No need to export private data
   #pragma warning (disable : 4251)
   typedef std::map<PierIDType,boost::shared_ptr<bmfPier> > PierContainer;
   typedef std::pair<PierIDType,boost::shared_ptr<bmfPier> > PierEntry;

   typedef std::map<SpanIDType,boost::shared_ptr<bmfSpan> > SpanContainer;
   typedef std::pair<SpanIDType,boost::shared_ptr<bmfSpan> > SpanEntry;

   PierContainer m_Piers;
   SpanContainer m_Spans;

   // cached shape and state data for drawing section
   mutable gmCompositeShape m_DrawSectionShape;
   mutable bool     m_HasShapeBeenBuilt;
   mutable Float64  m_Station;  // station of last drawing
   // save data for adding dimensions and labels to section
   mutable std::vector<gpPoint2d> m_GirderBottoms; // bottom locations of girders
   mutable gpPoint2d  m_SlabLeftTop;
   mutable gpPoint2d  m_SlabRightTop;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void StoreSpan(SpanIDType spanId,bmfSpan* pSpan);
   void StorePier(PierIDType pierId,bmfPier* pPier);

   bool BuildSectionShape(Float64 station) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_BRIDGE_H_
