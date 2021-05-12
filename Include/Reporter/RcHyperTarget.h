///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_RCHYPERTARGET_H_
#define INCLUDED_REPORTER_RCHYPERTARGET_H_
#pragma once

#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcHyperTarget

   Report content that defines a target to a hyperlink

DESCRIPTION
   This class defines a target, or anchor to a hyperlink. 
*****************************************************************************/

class REPORTERCLASS rptRcHyperTarget : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // constructor
   rptRcHyperTarget(const std::_tstring YourTarget)
   {
      m_TheTarget = YourTarget;
   }


   //------------------------------------------------------------------------
   // Copy constructor
   rptRcHyperTarget(const rptRcHyperTarget& /*rRcHyperTarget*/);               // Remove to prevent copy

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcHyperTarget();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   rptRcHyperTarget& operator = (const rptRcHyperTarget& /*rRcHyperTarget*/);  // Remove to prevent assignment

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Clone thyself
   rptReportContent* CreateClone() const;

   //------------------------------------------------------------------------
   // Accept a visitor
   void Accept( rptRcVisitor& MyVisitor );

   // GROUP: ACCESS
   //
   //------------------------------------------------------------------------
   // get the target name
   std::_tstring GetTargetName() const {return std::_tstring(m_TheTarget); }
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
   //------------------------------------------------------------------------
   // The target name
   std::_tstring m_TheTarget;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // hide the default constructor
   rptRcHyperTarget();

   // GROUP: OPERATORS

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Function to aid in copying
   void MakeCopy(const rptRcHyperTarget& rRcHyperTarget);
   //------------------------------------------------------------------------
   // Function to aid in assignment
   void MakeAssignment(const rptRcHyperTarget& rOther);
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif
