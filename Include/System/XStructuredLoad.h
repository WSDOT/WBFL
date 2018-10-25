///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#ifndef INCLUDED_SYSTEM_XSTRUCTUREDLOAD_H_
#define INCLUDED_SYSTEM_XSTRUCTUREDLOAD_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <System\SysExp.h>
#include <System\Exception.h>
#include <crtdbg.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

#undef THROW_LOAD
#define THROW_LOAD(code,pload) {sysXStructuredLoad alzxb_(sysXStructuredLoad::code, _T(__FILE__), __LINE__ ); \
                                /*alzxb_.SetExtendedMessage(pload->GetStateDump().c_str()); */\
                                _ASSERT(false); \
                                alzxb_.Throw();}


/*****************************************************************************
CLASS 
   sysXStructuredLoad

   Exception class for classes implementing the IStructuredLoad interface.


DESCRIPTION
   Use this class when throwing out of classes derived from IStructuredLoad

LOG
   rdp : 07.15.1998 : Created file
*****************************************************************************/

class SYSCLASS sysXStructuredLoad : public sysXBase
{
public:
   // Reasons for hucking
   enum Reason {InvalidFileFormat, EndOfFile, BadRead, BadVersion, MemoryError,CantInitializeTheParser, UserDefined};

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   sysXStructuredLoad( Reason reason, LPCTSTR file, Int16 line);

   //------------------------------------------------------------------------
   // Copy constructor
   sysXStructuredLoad(const sysXStructuredLoad& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysXStructuredLoad();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   sysXStructuredLoad& operator = (const sysXStructuredLoad& rOther);

   // GROUP: OPERATIONS
   // All classes derived from sysXBase must implement this method as follows:
   // void myClass::Throw() const { throw *static_cast<myClass*>this; }
   virtual void Throw() const override;

   //------------------------------------------------------------------------
   // Returns a reason code for the exception.  Concrete classes derived
   // from sysXBase must provide an implementation for this method that
   // returns an enum value as the actual enum type (Recall that enum's
   // can be safely converted to integer values, but not the other way
   // around).
   virtual Int32 GetReason() const override;

   //------------------------------------------------------------------------
   // Get the reason using an enum our direct clients can understand
   Reason GetExplicitReason() const;

   //------------------------------------------------------------------------
   // Set an extended message containing state data of the loader that crashed
   // this message will be appended to the message from the base class in 
   // GetErrorMessage
   void SetExtendedMessage(LPCTSTR msg);

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
   virtual void GetErrorMessage(std::_tstring* pMsg) const override;


   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const sysXStructuredLoad& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const sysXStructuredLoad& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Reason m_Reason;
   std::_tstring m_ExtendedMessage;

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor
   sysXStructuredLoad();
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

#endif // INCLUDED_SYSTEM_XSTRUCTUREDLOAD_H_
