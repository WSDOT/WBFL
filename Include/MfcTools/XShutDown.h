///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_XSHUTDOWN_H_
#define INCLUDED_XSHUTDOWN_H_
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
   CXShutDown

   Shut down exception.


DESCRIPTION
   Shut down exception.  Throw this exception when a fatal error has occured
   in PGSuper.  This will cause the application to shut down.  Optionally,
   the user can be given an opportunity to save their work.  If possible, 
   the exception data will be written into the log file.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.16.1998 : Created file
*****************************************************************************/

class MFCTOOLSCLASS CXShutDown : public CException
{
public:
   DECLARE_DYNAMIC(CXShutDown)

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   CXShutDown(LPCTSTR msg,   // The error message
              Int32 reason,      // A reason code
              bool bAttemptSave, // if true asks user if they want to save
                                 // before the shut down
              LPCTSTR file,  // File where the exception occured
              Int16 line         // Line number where the exception occured
              );

   //------------------------------------------------------------------------
   // Destructor
   virtual ~CXShutDown();

   // GROUP: OPERATORS

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Returns a reason code for the exception.
   virtual Int32 GetReason() const;

   //------------------------------------------------------------------------
   virtual void GetErrorMessage(std::_tstring* pMsg) const;

   //------------------------------------------------------------------------
   // overload mfc error message
   virtual BOOL GetErrorMessage( LPTSTR lpszError, INT nChar, UINT nMaxError, PUINT pnHelpContext = NULL);

   //------------------------------------------------------------------------
   // Returns true if the catch block should offer the user the chance to
   // save before the application shuts down
   bool AttemptSave() const;

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

#endif // INCLUDED_XSHUTDOWN_H_
