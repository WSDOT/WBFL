///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#ifndef INCLUDED_BRIDGEMODELING_PRECASTGIRDERTEMPLATE_H_
#define INCLUDED_BRIDGEMODELING_PRECASTGIRDERTEMPLATE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <BridgeModeling\GirderTemplate.h>
#include <BridgeModeling\StrandPattern.h>
#include <BridgeModeling\BundlePattern.h>
#include <BridgeModeling\LrLayout.h>
#include <BridgeModeling\PrismaticGirderProfile.h>
#include <GeomModel\IPrecastBeam.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bmfPrecastGirder;
class gmPrecastBeam;
class matConcreteEx;
class matPsStrand;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfPrecastGirderTemplate

   Template for bmfPrecastGirder objects.


DESCRIPTION
   Template for bmfPrecastGirder objects.  Used to describe and instantiate
   precast girder objects. This class extends bmfGirderTemplate by accounting
   for precast girder strand patterns.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 05.17.1997 : Created file
*****************************************************************************/

class BMFCLASS bmfPrecastGirderTemplate : public bmfGirderTemplate
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bmfPrecastGirderTemplate(const std::string& name, // girder name
                            const bmfGirderProfile* pProfile, // girder shape is expected to be gmIPrecastBeam
                            const matConcreteEx* pConc,
                            const matPsStrand* pStrand,
                            const bmfStrandPattern& strPtrn, // straight strand pattern
                            const bmfStrandPattern& endPtrn, // harped strand pattern
                            const bmfStrandPattern& hpPtrn, // harped strand bundle pattern
                            const bmfStrandPattern& tmpPtrn,  // temporary strand pattern
                            const bmfLrLayout&      lrLayout, // longitudinal rebar layout

                            Float64 hpLoc,      // Location of harping point (0.0 < hpLoc <= 0.5)
                            bmfMeasuredFrom hpLocFrom = LeftBearing);

   //------------------------------------------------------------------------
   // Copy constructor
   bmfPrecastGirderTemplate(const bmfPrecastGirderTemplate& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bmfPrecastGirderTemplate();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bmfPrecastGirderTemplate& operator = (const bmfPrecastGirderTemplate& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Instantates a bmfPrecastGirder object.
   virtual bmfGirder* CreateGirder();

   //------------------------------------------------------------------------
   virtual bmfGirderTemplate* CreateClone() const;

   //------------------------------------------------------------------------
   void SetStraightStrandPattern( const bmfStrandPattern& rPattern );

   //------------------------------------------------------------------------
   const bmfStrandPattern& GetStraightStrandPattern() const;

   //------------------------------------------------------------------------
   bmfStrandPattern& GetStraightStrandPattern();

   //------------------------------------------------------------------------
   void SetHarpedStrandPatternEnd(const bmfStrandPattern& rEndPtrns);

   //------------------------------------------------------------------------
   bmfStrandPattern& GetHarpedStrandPatternEnd();

   //------------------------------------------------------------------------
   const bmfStrandPattern& GetHarpedStrandPatternEnd() const;

   //------------------------------------------------------------------------
   void SetHarpedStrandPatternHP(const bmfStrandPattern& rEndPtrns);

   //------------------------------------------------------------------------
   bmfStrandPattern& GetHarpedStrandPatternHP();

   //------------------------------------------------------------------------
   const bmfStrandPattern& GetHarpedStrandPatternHP() const;

   //------------------------------------------------------------------------
   void SetTemporaryStrandPattern( const bmfStrandPattern& rPattern );

   //------------------------------------------------------------------------
   const bmfStrandPattern& GetTemporaryStrandPattern() const;

   //------------------------------------------------------------------------
   bmfStrandPattern& GetTemporaryStrandPattern();

   //------------------------------------------------------------------------
   const bmfLrLayout& GetLrLayout() const;

   //------------------------------------------------------------------------
   void SetLrLayout(const bmfLrLayout& rLayout);
   
   //------------------------------------------------------------------------
   void SetHarpPointLocation( Float64 hpLoc, bmfMeasuredFrom measFrom );

   //------------------------------------------------------------------------
   // Returns the harping point location as input in the constructor or
   // SetHarpPointLocation
   Float64 GetHarpPointLocation() const;

   //------------------------------------------------------------------------
   // Returns the where the harping point location is measured from as input 
   // in the constructor or SetHarpPointLocation.
   bmfMeasuredFrom HarpPointLocationMeasuredFrom() const;

   //------------------------------------------------------------------------
   Uint32 GetHarpingPointCount() const;

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

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy(const bmfPrecastGirderTemplate& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfPrecastGirderTemplate& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   const matConcreteEx* m_pConc;
   const matPsStrand*   m_pStrand;
   bmfStrandPattern m_StraightPattern;
   bmfStrandPattern m_TempPattern;
   bmfStrandPattern m_HPPattern;
   bmfStrandPattern m_EndPattern;
   Float64 m_HpLoc;
   bmfMeasuredFrom m_HpLocMeasuredFrom;
   bmfLrLayout m_LrLayout;

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

#endif // INCLUDED_BRIDGEMODELING_PRECASTGIRDERTEMPLATE_H_

