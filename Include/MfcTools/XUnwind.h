///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2024  Washington State Department of Transportation
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

#ifndef INCLUDED_XUNWIND_H_
#define INCLUDED_XUNWIND_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <MfcTools\MfcToolsExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   CXUnwind

   Exception used to un-wind the stack back to the message loop in the event
   of a non-fatal exceptional condition.


DESCRIPTION
   Exception used to un-wind the stack back to the message loop in the event
   of a non-fatal exceptional condition.  Such a condition is characterized by
   something that the program cannot process correctly.

LOG
   rab : 10.16.1998 : Created file
*****************************************************************************/

class MFCTOOLSCLASS CXUnwind : public CException
{
public:
   DECLARE_DYNAMIC(CXUnwind)

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   CXUnwind(LPCTSTR msg,   // The error message
            Int32 reason,      // A reason code
            LPCTSTR file,  // File where the exception occurred
            Int16 line         // Line number where the exception occurred
            );

   //------------------------------------------------------------------------
   // Destructor
   virtual ~CXUnwind();

   // GROUP: OPERATORS

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns a reason code for the exception.
   virtual Int32 GetReason() const;

   //------------------------------------------------------------------------
   virtual void GetErrorMessage(std::_tstring* pMsg) const;

   //------------------------------------------------------------------------
   // overload mfc error message
   virtual BOOL GetErrorMessage( LPTSTR lpszError, INT nChar, UINT nMaxError, PUINT pnHelpContext = nullptr);

   //------------------------------------------------------------------------
   // Returns the filename where the exceptions thrown from.
   std::_tstring GetFile() const;

   //------------------------------------------------------------------------
   // Returns the line number where the exception was thrown from.
   Int16 GetLine() const;

   // GROUP: ACCESS
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
   Int32 m_Reason;
   std::_tstring m_Message;
   bool m_bAttemptSave;
   std::_tstring m_File;
   Int16 m_Line;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_XUNWIND_H_
