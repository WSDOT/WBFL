///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2018  Washington State Department of Transportation
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

#pragma once

// SYSTEM INCLUDES
//
#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\RcScalar.h>
#include <System\NumericFormatTool.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcPercentage

   Report content for a percentage value.

*****************************************************************************/

class REPORTERCLASS rptRcPercentage : public rptRcScalar
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcPercentage();

   //------------------------------------------------------------------------
   // Constructor
   rptRcPercentage(Float64 value);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcPercentage(const rptRcPercentage& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcPercentage();

   //------------------------------------------------------------------------
   // Accept a visitor
   virtual void Accept( rptRcVisitor& rVisitor ) override;

   //------------------------------------------------------------------------
   // Make a virtual copy
   virtual rptReportContent* CreateClone() const override;

   //------------------------------------------------------------------------
   std::_tstring AsString() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const override;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const override;
#endif // _DEBUG

};
