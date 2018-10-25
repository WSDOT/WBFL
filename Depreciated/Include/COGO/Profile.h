///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_COGO_PROFILE_H_
#define INCLUDED_COGO_PROFILE_H_
#pragma once

// SYSTEM INCLUDES
//
#include <list>
#include <Cogo\CogoExp.h>
#include <Cogo\VCurve.h>
#include <GeometricPrimitives\Primitives.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class cogoRoadway;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   cogoProfile

   Encapsulates an alignment profile.

DESCRIPTION
   Encapsulates an alignment profile.

COPYRIGHT
   Copyright (c) 1999
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   Richard Brice : 04.23.1999 : Created file
*****************************************************************************/
class COGOCLASS cogoProfile
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   cogoProfile(cogoRoadway* pAlignment);

   cogoProfile(const cogoProfile& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~cogoProfile(); 

   // GROUP: OPERATORS
   cogoProfile& operator = (const cogoProfile& rOther);

   // GROUP: OPERATIONS
   
   //------------------------------------------------------------------------
   Float64 GetElevation(Float64 station,Float64 offset = 0.0) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns a pointer to the associated alignment
   const cogoRoadway* GetAlignment() const;

   //------------------------------------------------------------------------
   // Returns a pointer to the associated alignment
   cogoRoadway* GetAlignment();

   //------------------------------------------------------------------------
   // Adds a point to the profile
   void AddPoint(Float64 station,Float64 elev);

   //------------------------------------------------------------------------
   // Adds a vertical curve to the profile
   void AddCurve(const cogoVCurve& vcurve);

   //------------------------------------------------------------------------
   // Sets the crown point offset.  The crown point offset is the offset
   // distance from the alignment to the crown point.  This profile passes
   // through the crown point.  If the crown point is to the right of the alignment
   // enter a negative value for offset.
   void SetCrownPointOffset(Float64 offset);

   //------------------------------------------------------------------------
   // Returns the crown point offset.
   Float64 GetCrownPointOffset() const;

   //------------------------------------------------------------------------
   // Adds a super elevation entry to the profile.
   // The super elevation defines the cross slopes on the left and right
   // side of the crown point.  Downward slopes are negative.
   void AddSuperElevation(Float64 station,Float64 left,Float64 right);

   //------------------------------------------------------------------------
   void GetSuperElevation(Float64 station, Float64* pLeft,Float64* pRight) const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // elements of the profile
   enum ElementType { etPoint, etCurve };
   struct Element
   {
      ElementType Type;
      gpPoint2d Point;
      cogoVCurve Curve;
      bool operator>(const Element& el) const;
   };
   std::list<Element> m_Elements;
   friend Element;

   struct SuperElevation
   {
      Float64 Station; // Station where this entry is defined
      Float64 Left;    // cross slope left of crown point
      Float64 Right;   // cross slope right of crown point
      bool operator>(const SuperElevation& super) const;
   };
   std::list<SuperElevation> m_SuperElevations;
   friend SuperElevation;

   cogoRoadway* m_pAlignment; // Alignment to which this profile is attached

   Float64 m_CrownPointOffset;

   // GROUP: LIFECYCLE

   // GROUP: OPERATORS

   // GROUP: OPERATIONS
   void SortElements();
   void SortSuperElevations();

   
   // Computes the elevation on the profile.
   // This method calls the next three helper methods.
   Float64 GetProfileElevation(Float64 station) const;

   // Computes the elevation where station occurs prior to the
   // first element in the profile
   Float64 BeforeProfileElevation(Float64 station) const;

   // Computes the elevation where station occurs after to the
   // last element in the profile
   Float64 AfterProfileElevation(Float64 station) const;

   // Computes the elevation where station occurs somewhere within
   // the defined profile.
   Float64 ProfileElevation(Float64 station) const;


   // GROUP: ACCESS
   // GROUP: INQUIRY

#if defined _DEBUG
public:
   bool AssertValid() const;
   void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
public:
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_COGO_PROFILE_H_
