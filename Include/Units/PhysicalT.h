///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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

#ifndef INCLUDED_UNITS_PHYSICALT_H_
#define INCLUDED_UNITS_PHYSICALT_H_
#pragma once

// SYSTEM INCLUDES
//
#include <string>
#include <system\checks.h>
#include <MathEx.h>

// PROJECT INCLUDES
//
#include <Units\UnitsExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   unitPhysicalT

   A template class that defines a physical unit.


DESCRIPTION
   A template class that defines a physical unit.  A physical unit defines a
   unit of measure like length or time.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.29.1997 : Created file
*****************************************************************************/

template <Int16 m, Int16 l, Int16 t, Int16 k, Int16 a>
class unitPhysicalT
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.
   unitPhysicalT( Float64 pre, Float64 cf, Float64 post, const std::string& tag) :
      m_PreTerm( pre ), m_ConvFactor( cf ), m_PostTerm( post ), m_UnitTag( tag )
      {
         CHECK( cf != 0.0 );
      }

   //------------------------------------------------------------------------
   // Copy constructor
   unitPhysicalT(const unitPhysicalT& rOther)
   {
      MakeCopy( rOther );
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~unitPhysicalT()
   {
   }

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   unitPhysicalT& operator = (const unitPhysicalT& rOther)
   {
      if ( this != &rOther )
         MakeAssignment( rOther );

      return *this;
   }

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the pre-addition term.
   Float64 GetPreTerm() const { return m_PreTerm; }

   //------------------------------------------------------------------------
   // Returns the conversion factor.
   Float64 GetConvFactor() const { return m_ConvFactor; }

   //------------------------------------------------------------------------
   // Returns the post-addition term.
   Float64 GetPostTerm() const { return m_PostTerm; }

   //------------------------------------------------------------------------
   // Returns the unit tag.
   std::string UnitTag() const { return m_UnitTag; }

   //------------------------------------------------------------------------
   // Returns the mass dimensionality.
   static Float64 MassDim() { return m/10.; }

   //------------------------------------------------------------------------
   // Returns the length dimensionality.
   static Float64 LengthDim() { return l/10.; }

   //------------------------------------------------------------------------
   // Returns the time dimensionality.
   static Float64 TimeDim() { return t/10.; }

   //------------------------------------------------------------------------
   // Returns the temperature dimensionality.
   static Float64 TemperatureDim() { return k/10.; }

   //------------------------------------------------------------------------
   // Returns the angle dimensionality.
   static Float64 AngleDim() { return a/10.; }

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const
   {
      // At least one of the dimensionalities must be non-zero
      if ( MassDim()        == 0 &&
           LengthDim()      == 0 &&
           TimeDim()        == 0 &&
           TemperatureDim() == 0 &&
           AngleDim()       == 0 )
      {
         return false;
      }

      // The conversion factor must be non-zero.
      if ( IsZero( m_ConvFactor, 1.0e-24 ))
         return false;

      return true;
   }

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const
   {
      os << m_UnitTag.c_str() << endl;
      os << '\t' << "Dimensionality : (" 
         << MassDim()        << ","
         << LengthDim()      << ","
         << TimeDim()        << ","
         << TemperatureDim() << ","
         << AngleDim()
         << ")" << endl;
      os << '\t' << "Pre Term    : " << m_PreTerm << endl;
      os << '\t' << "Conv Factor : " << m_ConvFactor << endl;
      os << '\t' << "Post Term   : " << m_PostTerm << endl;
   }
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const unitPhysicalT& rOther)
   {
      m_PreTerm    = rOther.m_PreTerm;
      m_ConvFactor = rOther.m_ConvFactor;
      m_PostTerm   = rOther.m_PostTerm;
      m_UnitTag    = rOther.m_UnitTag;
   }

   //------------------------------------------------------------------------
   void MakeAssignment(const unitPhysicalT& rOther)
   {
      MakeCopy( rOther );
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_PreTerm;
   Float64 m_ConvFactor;
   Float64 m_PostTerm;
   std::string m_UnitTag;

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

#define DECLARE_PHYSICAL_UNIT(m,l,t,k,a,name) \
   UNITSTPL unitPhysicalT<m,l,t,k,a>; \
   typedef unitPhysicalT<m,l,t,k,a> name

// Basic Physical Units
#pragma warning( disable : 4231 ) // using non-ANSI standard compiler extension (suppress the warning)
DECLARE_PHYSICAL_UNIT( 10,  0,  0,  0,  0, unitMass );
DECLARE_PHYSICAL_UNIT(  0, 10,  0,  0,  0, unitLength );
DECLARE_PHYSICAL_UNIT(  0,  0, 10,  0,  0, unitTime );
DECLARE_PHYSICAL_UNIT(  0,  0,  0, 10,  0, unitTemperature );
DECLARE_PHYSICAL_UNIT(  0,  0,  0,  0, 10, unitAngle );

// Complex Physical Units
DECLARE_PHYSICAL_UNIT(  0, 10,-20,  0,  0, unitAcceleration );
DECLARE_PHYSICAL_UNIT( 10,-10,  0,  0,  0, unitMassPerLength );
DECLARE_PHYSICAL_UNIT(  0, 20,  0,  0,  0, unitLength2 );
DECLARE_PHYSICAL_UNIT(  0, 30,  0,  0,  0, unitLength3 );
DECLARE_PHYSICAL_UNIT(  0, 40,  0,  0,  0, unitLength4 );
DECLARE_PHYSICAL_UNIT( 10,-10,-20,  0,  0, unitPressure );
DECLARE_PHYSICAL_UNIT( 10,-30,-30,  0,  0, unitUnitWeight );
DECLARE_PHYSICAL_UNIT( 10,-30,  0,  0,  0, unitDensity );
DECLARE_PHYSICAL_UNIT( 10, 10,-20,  0,  0, unitForce );
DECLARE_PHYSICAL_UNIT( 10,  0,-20,  0,  0, unitForcePerLength );
DECLARE_PHYSICAL_UNIT( 10, 20,-20,  0,  0, unitMoment );
DECLARE_PHYSICAL_UNIT( 10, 20,-20,  0,-10, unitMomentPerAngle );
DECLARE_PHYSICAL_UNIT(  5, -5,-10,  0,  0, unitSqrtPressure );
DECLARE_PHYSICAL_UNIT(  0,-10,  0,  0,  0, unitPerLength );
DECLARE_PHYSICAL_UNIT( 10, 30,-20,  0,  0, unitForceLength2 );  // Used for E*I

// Other aliases
typedef unitLength2       unitArea;
typedef unitLength3       unitVolume;
typedef unitPressure      unitStress;
typedef unitLength        unitAreaPerLength; // can only have like units for area/length
                                             // shear Av/S is an example of this

#endif // INCLUDED_UNITS_PHYSICALT_H_

