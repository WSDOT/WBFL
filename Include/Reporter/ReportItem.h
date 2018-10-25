///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_REPORTITEM_H_
#define INCLUDED_REPORTER_REPORTITEM_H_
#pragma once

#include <string>
#include <Reporter\ReporterExp.h>

// :WARNING: Bad dependancy
// The only reason this header depends on FontStyleLibrary is for
// the rptStyleName typedef.
#include <Reporter\FontStyleLibrary.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class rptReportVisitor;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptReportItem

   Highest-level base class that represents all items that may be part of a report.

DESCRIPTION
   This class is an abstract representation of the qualities needed for items that are
   to be a part of a report. The main duty of this class is to implement the style chain
   of responsibility.
*****************************************************************************/

class REPORTERCLASS rptReportItem
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptReportItem();

   //------------------------------------------------------------------------
   // Copy constructor
   // Note that when copy is made, the new copy points to the same parent as the
   // original. Use ClearParent and then SetParent to change family.
   rptReportItem(const rptReportItem& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptReportItem();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment
   // Note that when copy is made, the new copy points to the same parent as the
   // original. Use ClearParent and then SetParent to change family.
   virtual rptReportItem& operator = (const rptReportItem& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // set parent for chain of responsibility
   // This call will fail if the item already has a parent. If you want to 
   // change parents, you must add and intermediate call to ClearParent.
   virtual void SetParent( rptReportItem* pParent);

   //------------------------------------------------------------------------
   // Clear parent for chain of responsibility. This will typically be done
   // after a ReportItem is copied.
   virtual void ClearParent(){m_pParent=0;}

   //
   // GROUP: ACCESS
   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Name of style that I'm using. This routine makes a copy
   virtual rptStyleName GetStyleName() const;

   //------------------------------------------------------------------------
   // set my style (locally)
   void SetStyleName(const rptStyleName& rStyleName);

   //------------------------------------------------------------------------
   // return true if this element has a local style, or false if the style
   // is gotten from a parent
   bool IsStyleLocal() const {return m_pStyleName ? true:false;}

   //------------------------------------------------------------------------
   // Clear my style. This will remove a local style if it exists and 
   // make it so item inherits it's style from its parent chain of 
   // reposibility. 
   //
   // GOTCHA: If you clear the style of the object at the top of the 
   // reponsibility chain (e.g., the Report), you will cause a crash.
   void ClearStyle();

protected:
   // GROUP: DATA MEMBERS

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // constructor with style
   rptReportItem(const rptStyleName& rStyleName);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const rptReportItem& rItem);
   virtual void MakeAssignment(const rptReportItem& rOther);

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Return a pointer to the style parent of this object.
	rptReportItem*  GetpParent() const {return  m_pParent;}

   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //
   //------------------------------------------------------------------------
   // pointer to parent for chain of responsibility
   rptReportItem* m_pParent;

   //------------------------------------------------------------------------
   //  Name of style that this piece of content points to
   rptStyleName* m_pStyleName;

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

#endif // ReportItem_H_
