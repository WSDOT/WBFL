///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifndef INCLUDED_MATH_NUMERICINTEGRATOR_H_
#define INCLUDED_MATH_NUMERICINTEGRATOR_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Math\MathExp.h>
#include <System\Exception.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class MATHCLASS mathFunction2d;
class MATHCLASS mathNumericIntegrator2d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   mathXNumericIntegrator2dFailed

   Exception class for mathNumericIntegrator2d.


DESCRIPTION
   Exception class for mathNumericIntegrator2d.

LOG
   rab : 06.24.2008 : Created file
*****************************************************************************/

class MATHCLASS mathXNumericIntegrator2dFailed : public sysXBase
{
public:
   // GROUP: ENUMERATIONS
   enum Reason {
      Unknown,        // The reason is unknown
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   mathXNumericIntegrator2dFailed(Reason reason,LPCTSTR file,Int16 line);

   //------------------------------------------------------------------------
   // Default constructor
   mathXNumericIntegrator2dFailed(const mathXNumericIntegrator2dFailed& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathXNumericIntegrator2dFailed();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   mathXNumericIntegrator2dFailed& operator=(const mathXNumericIntegrator2dFailed& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void Throw() const;
   //------------------------------------------------------------------------
   Int32 GetReason() const;
   //------------------------------------------------------------------------
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
   Reason m_Reason;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

/*****************************************************************************
CLASS 
   mathNumericIntegrator2d

   Abstract base class for two dimensional numerical integration.


DESCRIPTION
   Abstract base class for two dimensional numerical integration.

LOG
   rab : 06.24.2008 : Created file
*****************************************************************************/

class MATHCLASS mathNumericIntegrator2d
{
public:
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Evaluations the integral
   virtual Float64 Evaluate(const mathFunction2d& f,Float64 xMin,Float64 xMax,Uint16 nIntervals) = 0;

   // GROUP: ACCESS

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

#endif // INCLUDED_MATH_NUMERICINTEGRATOR_H_
