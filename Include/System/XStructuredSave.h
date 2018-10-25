///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_XSTRUCTUREDSAVE_H_
#define INCLUDED_SYSTEM_XSTRUCTUREDSAVE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <System\SysExp.h>
#include <System\Exception.h>

// LOCAL INCLUDES

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysXStructuredSave

   Exception class for classes implementing the IStructuredSave interface.


DESCRIPTION
   Use this class when throwing out of classes derived from IStructuredSave


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 07.15.1998 : Created file
*****************************************************************************/

class SYSCLASS sysXStructuredSave : public sysXBase
{
public:
   // Reasons for hucking
   enum Reason {BadWrite,CantInitializeTheParser};

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   sysXStructuredSave( Reason reason, const char* file, Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   sysXStructuredSave(const sysXStructuredSave& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysXStructuredSave();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   sysXStructuredSave& operator = (const sysXStructuredSave& rOther);

   // GROUP: OPERATIONS
   // All classes derived from sysXBase must implement this method as follows:
   // void myClass::Throw() const { throw *static_cast<myClass*>this; }
   virtual void Throw() const;

   //------------------------------------------------------------------------
   // Returns a reason code for the exception.  Concrete classes derived
   // from sysXBase must provide an implementation for this method that
   // returns an enum value as the actual enum type (Recall that enum's
   // can be safely converted to integer values, but not the other way
   // around).
   virtual Int32 GetReason() const;

   //------------------------------------------------------------------------
   // Get the reason using an enum our direct clients can understand
   Reason GetExplicitReason() const;

   //------------------------------------------------------------------------
   // Assigns an error message to pMsg.  The default implementation is to 
   // create a message in the following format:
   //
   // A <exception_type> error, number <reason>, has occured in
   // <filename> at line <line>.
   //
   // Where exception_type is the dynamic type of the exception,
   // reason is the reason code returned by GetReason(),
   // filename is the filename returned by GetFile(),  and
   // line is the line number returned by GetLine().
   virtual void GetErrorMessage(std::string* pMsg) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const sysXStructuredSave& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const sysXStructuredSave& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Reason m_Reason;
   std::string m_ExtendedMessage;

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   sysXStructuredSave();
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

#endif // INCLUDED_SYSTEM_XSTRUCTUREDSAVE_H_
