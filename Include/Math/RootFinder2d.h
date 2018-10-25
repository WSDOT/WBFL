///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_MATH_ROOTFINDER2D_H_
#define INCLUDED_MATH_ROOTFINDER2D_H_
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
class MATHCLASS mathRootFinder2d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   mathXRootFinder2dFailed

   Exception class for mathRootFinder2d.


DESCRIPTION
   Exception class for mathRootFinder2d.

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATHCLASS mathXRootFinder2dFailed : public sysXBase
{
public:
   // GROUP: ENUMERATIONS
   enum Reason {
      Unknown,        // The reason is unknown
      RootNotPresent, // A root is not present
      BracketFailed,  // could not bracket root in range.
      MaxIterExceeded // The maximum number of iterations were exceeded
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   mathXRootFinder2dFailed(Reason reason,LPCTSTR file,Int16 line);

   //------------------------------------------------------------------------
   // Default constructor
   mathXRootFinder2dFailed(const mathXRootFinder2dFailed& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathXRootFinder2dFailed();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   mathXRootFinder2dFailed& operator=(const mathXRootFinder2dFailed& rOther);

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
   mathRootFinder2d

   Abstract base class for two dimensional root finders.


DESCRIPTION
   Abstract base class for two dimensional root finders.  Root finders of
   this type find zeros in mathFunction2d objects.  Root finders are neutral
   to mathFunction2d exceptions.

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATHCLASS mathRootFinder2d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   mathRootFinder2d();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathRootFinder2d();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Finds the root of f that is nearest to xNearest, such that -tol < f(x) < tol.
   // Throws a mathXRootFinderFailed exception if a root could not be found.
   virtual Float64 FindRoot(const mathFunction2d& f,Float64 xNearest,Float64 tol);

   //------------------------------------------------------------------------
   // Finds the root of f that is nearest to xNearest, subject to the constraint
   // x > xMin, such that -tol < f(x) < tol.
   // Throws a mathXRootFinderFailed exception if a root could not be found.
   virtual Float64 FindRootConstrainedMin(const mathFunction2d& f,Float64 xNearest,
                                          Float64 xMin, Float64 tol);

   //------------------------------------------------------------------------
   // Finds the root of f that is nearest to xNearest, subject to the constraint
   // x < xMax, such that -tol < f(x) < tol.
   // Throws a mathXRootFinderFailed exception if a root could not be found.
   virtual Float64 FindRootConstrainedMax(const mathFunction2d& f,Float64 xNearest,
                                          Float64 xMax, Float64 tol);

   //------------------------------------------------------------------------
   // Finds the root of f that is in the range [xMin,xMax], such that -tol < f(x) < tol.
   // Throws a mathXRootFinderFailed exception if a root could not be found.
   virtual Float64 FindRootInRange(const mathFunction2d& f,Float64 xMin,Float64 xMax,Float64 tol) = 0;

   // GROUP: ACCESS
   //------------------------------------------------------------------------
   void SetMaxIter(Int32 maxIter);

   //------------------------------------------------------------------------
   Int32 GetMaxIter() const;

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
   enum BracketOutcome { Bracketted, // bracket was sucessful. put in x[0,1]
                         FoundRoot,  // found a root - stored it in x[0]
                         Failed      // bracket failed.
   };

   //------------------------------------------------------------------------
   // bracketing functions. These functions are not meant to find a root, merely
   // find x values on either side of it.If they sucessfully bracket a root they will
   // return Bracketted put the x values in x[0,1]. However, if they are lucky enough
   // to actually find a root, they will return FoundRoot and place the root into x[0].

   virtual BracketOutcome Bracket(const mathFunction2d& eval, Float64 x[], Float64 tol);
   virtual BracketOutcome BracketConstrainedMin(const mathFunction2d& eval,
                                                Float64 x[], Float64 xmin, Float64 tol);
   virtual BracketOutcome BracketConstrainedMax(const mathFunction2d& eval, 
                                                Float64 x[], Float64 xmax, Float64 tol);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Int32 m_MaxIter;

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   mathRootFinder2d(const mathRootFinder2d&);
   mathRootFinder2d& operator=(const mathRootFinder2d&) = delete;

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_MATH_ROOTFINDER2D_H_
