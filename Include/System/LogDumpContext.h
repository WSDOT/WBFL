///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

#ifndef INCLUDED_SYSTEM_LOGDUMPCONTEXT_H_
#define INCLUDED_SYSTEM_LOGDUMPCONTEXT_H_
#pragma once

#include <WBFLCore.h>
#include <System\DbgBuild.h>
#include <System\DumpContext.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
interface ILogFile;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   dbgLogDumpContext

   Class used in Dump member functions to dump class data.


DESCRIPTION
   Class used in Dump member functions to dump class data.
   This implemententation dumps the data to an ILogFile object.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 06.01.1998 : Created file
*****************************************************************************/

class SYSCLASS dbgLogDumpContext : public dbgDumpContext
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   dbgLogDumpContext(ILogFile* pLog = 0,DWORD dwCookie = 0);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~dbgLogDumpContext();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Inserters for various built-ins
#if defined UNICODE
   virtual dbgDumpContext& operator<<(const std::_tstring& s);
#else
   virtual dbgDumpContext& operator<<(const std::_tstring& s);
#endif
   virtual dbgDumpContext& operator<<(LPCTSTR s);
   dbgDumpContext& operator<<(TCHAR c);    
   dbgDumpContext& operator<<(bool n);
   dbgDumpContext& operator<<(Int16 n);
   dbgDumpContext& operator<<(Uint16 n);
   dbgDumpContext& operator<<(Int32 n);
   dbgDumpContext& operator<<(Uint32 n);
   dbgDumpContext& operator<<(Int64 n);
   dbgDumpContext& operator<<(Uint64 n);
   dbgDumpContext& operator<<(Float32 n);    
   dbgDumpContext& operator<<(Float64 n);
   dbgDumpContext& operator<<(Float80 n);
   dbgDumpContext& operator<<(void * n);
   dbgDumpContext& operator<<(const sysSectionValue& n);

   // GROUP: OPERATIONS

   dbgDumpContext& EndLine();

   void SetLog(ILogFile* pLog,DWORD dwCookie);
   void GetLog(ILogFile** ppLog,DWORD* pdwCookie);
   
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
   ILogFile* m_pLog;
   DWORD m_dwCookie;

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   dbgLogDumpContext(const dbgLogDumpContext&);
   dbgLogDumpContext& operator=(const dbgLogDumpContext&);

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



#endif // INCLUDED_SYSTEM_LOGDUMPCONTEXT_H_
