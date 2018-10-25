///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#ifndef INCLUDED_MATERIAL_STRESSSTRAINCURVE_H_
#define INCLUDED_MATERIAL_STRESSSTRAINCURVE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Material\MaterialExp.h>
#include <System\Exception.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class MATCLASS matStressStrainCurve;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   matXStressStrainEvalError

   Interface class for material stress strain product models.


DESCRIPTION
   Interface class for material stress strain product models.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATCLASS matXStressStrainEvalError : public sysXBase
{
public:
   // GROUP: ENUMERATIONS

   //------------------------------------------------------------------------
   enum Reason { Unknown,
                 MultiValuedStress
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor. Initializes the stress strain curve with the supplied parameters.
   matXStressStrainEvalError(Reason reason,
                             LPCTSTR file,
                             Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   matXStressStrainEvalError(const matXStressStrainEvalError& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matXStressStrainEvalError();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   matXStressStrainEvalError& operator = (const matXStressStrainEvalError& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   void Throw() const;

   //------------------------------------------------------------------------
   // Returns the reason the exception was thrown.
   Int32 GetReason() const;

   //------------------------------------------------------------------------
   // Returns the reason the exception was thrown.
   Reason GetReasonCode() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Reason      m_Reason;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};


/*****************************************************************************
CLASS 
   matStressStrainCurve

   Interface class for material stress strain product models.


DESCRIPTION
   Interface class for material stress strain product models.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATCLASS matStressStrainCurve
{
public:
   // GROUP: ENUMERATIONS

   //------------------------------------------------------------------------
   // StrainState
   // Represents the strain condition of the material.
   // NOTE: These values are sorted in ascending order from most compressive to most
   //       tensile.
   enum StrainState { Crushed      = -3,  // Material crushed in compression
                      CompUltimate = -2,  // Beyond ultimate not yet crushed
                      CompPlastic  = -1,  // Beyond yield not yet ultimate
                      Elastic      = 0,   // Material is in the elastic range
                      TensPlastic  = 1,   // Beyond yield not yet ultimate
                      TensUltimate = 2,   // Beyond ultimate not yet fractured
                      Fractured    = 3 }; // Material fractured in tension

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor. Initalizes name to "Unknown" and the rupture stress
   // strain values to zero.
   matStressStrainCurve();

   //------------------------------------------------------------------------
   // Constructor. Initializes the stress strain curve with the supplied parameters.
   matStressStrainCurve(const std::_tstring& name,
                        Float64 fractureStrain,
                        Float64 fractureStress,
                        Float64 crushingStrain,
                        Float64 crushingStress);

   //------------------------------------------------------------------------
   // Copy constructor
   matStressStrainCurve(const matStressStrainCurve& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~matStressStrainCurve();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   matStressStrainCurve& operator = (const matStressStrainCurve& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // CreateClone
   // Creates a polymorphic type-safe clone of this curve.
   virtual matStressStrainCurve * CreateClone() const =0;

   //------------------------------------------------------------------------
   // Computes the stress for the given strain.  Returns the strain state
   // for the material for the given strain level.  If the return value
   // is Fractured or Crushed, the value pointed to
   // by pStress is undefined.  Throws a matXStressStrainEvalError
   // exception if an error occurs when evaluating the stress strain curve.
   virtual StrainState GetStress(Float64 strain,Float64* pStress) const = 0;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetName(const std::_tstring& name);

   //------------------------------------------------------------------------
   std::_tstring GetName() const;

   //------------------------------------------------------------------------
   Float64 GetFractureStrain() const;

   //------------------------------------------------------------------------
   Float64 GetFractureStress() const;

   //------------------------------------------------------------------------
   Float64 GetCrushingStrain() const;

   //------------------------------------------------------------------------
   Float64 GetCrushingStress() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy(const matStressStrainCurve& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const matStressStrainCurve& rOther);

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void SetFractureStrain(Float64 trs);

   //------------------------------------------------------------------------
   void SetFractureStress(Float64 trs);

   //------------------------------------------------------------------------
   void SetCrushingStrain(Float64 crs);

   //------------------------------------------------------------------------
   void SetCrushingStress(Float64 crs);

   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::_tstring m_Name;
   Float64 m_FractureStrain;
   Float64 m_FractureStress;
   Float64 m_CrushingStrain;
   Float64 m_CrushingStress;

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

#endif // INCLUDED_MATERIAL_STRESSSTRAINCURVE_H_
