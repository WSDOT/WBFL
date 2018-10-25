///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#ifndef INCLUDED_REINFORCEDCONCRETE_CAPACITYSOLVERERROR_H_
#define INCLUDED_REINFORCEDCONCRETE_CAPACITYSOLVERERROR_H_

#if !defined INCLUDED_REINFORCEDCONCRETE_REINFCONCEXP_H_
#include <ReinforcedConcrete\ReinfConcExp.h>
#endif

#if !defined INCLUDED_SYSTEM_SYSXBASE_H_
#include <System\Exception.h>
#endif

/*****************************************************************************
CLASS 
   rcaXCapacitySolverError

   Exception class for solver errors. Derived from sysXBase.


DESCRIPTION
   Exception class for solver errors. Derived from sysXBase.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 01.20.1998 : Created file
*****************************************************************************/

class REINFCONCCLASS rcaXCapacitySolverError : public sysXBase
{
public:

enum Reason { ProblemRepError,             // There is a problem w/ the problem
                                           // representation
              NoTensileCapacity,           // Model has no tensile capacity
              NoCompressiveCapacity,       // Model has no compressive capacity
              TensileCapacityExceeded,     // Applied axial load was to large
              CompressiveCapacityExceeded, // Applied axial load was to large
              MaxIterExceeded,             // Exceeded the maximum number of 
                                           // iterations
              Unknown
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Supply the file and line number where the 
   // exception occured.
   rcaXCapacitySolverError(Reason reason, const char* file, Int16 line);
   rcaXCapacitySolverError(const std::string &reinterpMsg,Reason reason, const char* file, Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   rcaXCapacitySolverError(const rcaXCapacitySolverError& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rcaXCapacitySolverError();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rcaXCapacitySolverError& operator = (const rcaXCapacitySolverError& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Throw
   // Implements the Throw() interface
   void Throw() const;

   //------------------------------------------------------------------------
   // GetReason
   // Returns the reason the solver failed in int format to satisfy base class
   // rcaXCapacitySolverError::Reason 
   Int32 GetReason() const;

   //------------------------------------------------------------------------
   // GetReasonCode
   // Returns the reason the solver failed.
   // rcaXCapacitySolverError::Reason 
   Reason GetReasonCode() const;

   //------------------------------------------------------------------------
   // GetErrorMessage
   // Overrides the standard error message with the error messages listed below
   //    Reason                Message
   // MaterialNotFound	    "Material not found"
   // ElementNotFound	    "Element not found"
   // InvalidProblemRep	    "The problem representation is invalid"
   void GetErrorMessage(std::string* pMsg,Int32 reserved) const;


   // GROUP: ACCESS
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

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const rcaXCapacitySolverError& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const rcaXCapacitySolverError& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Reason m_Reason;
   std::string m_ReinterpertMsg;

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   rcaXCapacitySolverError();
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   void Clean();

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REINFORCEDCONCRETE_CAPACITYSOLVERERROR_H_