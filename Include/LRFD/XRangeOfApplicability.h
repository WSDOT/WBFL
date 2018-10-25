///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_XRANGEOFAPPLICABILITY_H_
#define INCLUDED_LRFD_XRANGEOFAPPLICABILITY_H_
#pragma once

// SYSTEM INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <System\Exception.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdXRangeOfApplicability

   Range of applicability errors.


DESCRIPTION
   Range of applicability errors. Exception that is thrown when the range of
   applicability of live load distribution factors is violated.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.25.1997 : Created file
*****************************************************************************/

class LRFDCLASS lrfdXRangeOfApplicability : public sysXBase
{
public:
   // GROUP: DATA MEMBERS

   //------------------------------------------------------------------------
   // Range of applicability error types
   enum Reason
   {
      Spacing,        // Girder spacing (S)
      SlabDepth,      // Slab depth (ts)
      SpanLength,     // Span length (L)
      NumGirders,     // Number of girders (Nb)
      CurbLineOffset, // de
      LongStiffness,  // Kg
      SkewAngle,      // Excessive Skew Angle
      SkewAngleDiff,   // Difference in skew angles between adjacent piers
      GirderDepth,    // Girder depth (d)
      NumLanes,         // Number of lanes (Nl)
      TorsionalConstant, // J
      MomentOfInertia, // I
      BeamWidth // b
   };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdXRangeOfApplicability(Reason reason,LPCTSTR msg,LPCTSTR file, long line);

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdXRangeOfApplicability(const lrfdXRangeOfApplicability& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdXRangeOfApplicability();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   lrfdXRangeOfApplicability& operator = (const lrfdXRangeOfApplicability& rOther);

   // GROUP: OPERATIONS
   void Throw() const { throw *static_cast<const lrfdXRangeOfApplicability*>(this); }
   Int32 GetReason() const { return (Int32)m_Reason; }
   lrfdXRangeOfApplicability::Reason GetReasonCode() const { return m_Reason; }
   virtual void GetErrorMessage(std::_tstring* pMsg) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const lrfdXRangeOfApplicability& rOther);
   void MakeAssignment(const lrfdXRangeOfApplicability& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Reason m_Reason;
   std::_tstring m_Message;

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

#endif // INCLUDED_LRFD_XRANGEOFAPPLICABILITY_H_

