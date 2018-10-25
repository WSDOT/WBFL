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

#ifndef INCLUDED_BRIDGEMODELING_SPLICEDGIRDERTEMPLATE_H_
#define INCLUDED_BRIDGEMODELING_SPLICEDGIRDERTEMPLATE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\GirderTemplate.h>
#include <BridgeModeling\StrandPattern.h>
#include <BridgeModeling\LrLayout.h>
#include <BridgeModeling\Ducts.h>
#include <GeomModel\IPrecastBeam.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bmfSplicedGirder;
class gmPrecastBeam;
class matConcreteEx;
class matPsStrand;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfSplicedGirderTemplate

   Template for bmfSplicedGirder objects.


DESCRIPTION
   Template for bmfSplicedGirder objects.  Used to describe and instantiate
   spliced precast girder objects. This class extends bmfGirderTemplate by accounting
   for precast girder strand patterns, splice segments, and post-tensioning ducts.

   Spliced girders are made up of three segments. The end segments are assumed to be
   identical

COPYRIGHT
   Copyright (c) 1997-2002
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.19.2002 : Created file
*****************************************************************************/

class BMFCLASS bmfSplicedGirderTemplate : public bmfGirderTemplate
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfSplicedGirderTemplate(const std::_tstring& name, // girder name
                            const bmfGirderProfile* pProfile, // girder shape is expected to be gmIPrecastBeam
                            CollectionIndexType nSplices, // number of splace joints
                            Float64* segmentLength, // array of segment lengths (left and middle segment only)
                            Float64* closurePourSize, // width of closure pour
                            const matConcreteEx* pConc,
                            const matPsStrand* pStrand,
                            const matPsStrand* pPTStrand,
                            const bmfStrandPattern* strPtrn, // strand pattern
                            const bmfStrandPattern& tmpPtrn,  // temporary strand pattern
                            const bmfLrLayout*      lrLayout, // longitudinal rebar layout
                            const bmfDucts& ducts); // collection of post-tensioning ducts

   //------------------------------------------------------------------------
   // Copy constructor
   bmfSplicedGirderTemplate(const bmfSplicedGirderTemplate& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfSplicedGirderTemplate();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bmfSplicedGirderTemplate& operator = (const bmfSplicedGirderTemplate& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Instantates a bmfSplicedGirder object.
   virtual bmfGirder* CreateGirder();

   //------------------------------------------------------------------------
   virtual bmfGirderTemplate* CreateClone() const;

   SegmentIndexType GetNumSegments() const;
   CollectionIndexType GetNumSplices() const;

   //------------------------------------------------------------------------
   void SetStrandPattern( SegmentIndexType segment,const bmfStrandPattern& rPattern );

   //------------------------------------------------------------------------
   const bmfStrandPattern& GetStrandPattern(SegmentIndexType segment) const;

   //------------------------------------------------------------------------
   bmfStrandPattern& GetStrandPattern(SegmentIndexType segment);

   //------------------------------------------------------------------------
   void SetTemporaryStrandPattern( const bmfStrandPattern& rPattern );

   //------------------------------------------------------------------------
   const bmfStrandPattern& GetTemporaryStrandPattern() const;

   //------------------------------------------------------------------------
   bmfStrandPattern& GetTemporaryStrandPattern();

   //------------------------------------------------------------------------
   const bmfLrLayout& GetLrLayout(SegmentIndexType segment) const;

   //------------------------------------------------------------------------
   void SetLrLayout(SegmentIndexType segment,const bmfLrLayout& rLayout);

   //------------------------------------------------------------------------
   gmIPrecastBeam* CreateShape(Float64 distFromStart,Float64 length) const;

   //------------------------------------------------------------------------
   void SetConcrete(const matConcreteEx* pConc);

   //------------------------------------------------------------------------
   const matConcreteEx* GetConcrete() const;

   //------------------------------------------------------------------------
   void SetStrand(const matPsStrand* pStrand);

   //------------------------------------------------------------------------
   const matPsStrand* GetStrand() const;

   //------------------------------------------------------------------------
   void SetPTStrand(const matPsStrand* pStrand);

   //------------------------------------------------------------------------
   const matPsStrand* GetPTStrand() const;

   //------------------------------------------------------------------------
   void SetClosurePourSize(CollectionIndexType splice,Float64 size);

   //------------------------------------------------------------------------
   Float64 GetClosurePourSize(CollectionIndexType splice) const;

   //------------------------------------------------------------------------
   void SetDuct(const bmfDucts& ducts);

   //------------------------------------------------------------------------
   const bmfDucts& GetDucts() const;

   //------------------------------------------------------------------------
   // if < 0, fractional
   // Actual segment lengths are computed from the girder object itself
   void SetSegmentLength(SegmentIndexType segment,Float64 length);

   //------------------------------------------------------------------------
   Float64 GetSegmentLength(SegmentIndexType segment) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy(const bmfSplicedGirderTemplate& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfSplicedGirderTemplate& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   CollectionIndexType m_nSplices;
   Float64 m_SegmentLength[2];
   Float64 m_ClosurePourSize[2];
   const matConcreteEx* m_pConc;
   const matPsStrand*   m_pStrand;
   const matPsStrand*   m_pPTStrand;
   bmfStrandPattern m_StrandPattern[3];
   bmfStrandPattern m_TempPattern;
   bmfDucts m_Ducts;
   bmfLrLayout m_LrLayout[3];

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
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

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_SPLICEDGIRDERTEMPLATE_H_

