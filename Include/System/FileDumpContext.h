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

#ifndef INCLUDED_SYSTEM_FILEDUMPCONTEXT_H_
#define INCLUDED_SYSTEM_FILEDUMPCONTEXT_H_
#pragma once

#include <fstream>
#include <System\DbgBuild.h>
#include <System\DumpContext.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   dbgFileDumpContext

   Class used in Dump member functions to dump class data.


DESCRIPTION
   Class used in Dump member functions to dump class data.
   This implementation dumps to an output stream (typically a file stream).


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 06.01.1998 : Created file
*****************************************************************************/

class SYSCLASS dbgFileDumpContext : public dbgDumpContext
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor - dump to std::_tcout
   dbgFileDumpContext(const std::_tstring& fname);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~dbgFileDumpContext();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // 
   // Inserters for various built-ins
   virtual dbgDumpContext& operator<<(const std::_tstring& s);
   virtual dbgDumpContext& operator<<(LPCTSTR s);
   dbgDumpContext& operator<<(char c);    
   dbgDumpContext& operator<<(bool n);
   //dbgDumpContext& operator<<(int n);
   //dbgDumpContext& operator<<(unsigned int n);
   dbgDumpContext& operator<<(Int16 n);
   dbgDumpContext& operator<<(Uint16 n);
   dbgDumpContext& operator<<(Int32 n);
   dbgDumpContext& operator<<(Uint32 n);
   dbgDumpContext& operator<<(Float32 n);    
   dbgDumpContext& operator<<(Float64 n);
   dbgDumpContext& operator<<(Float80 n);
   dbgDumpContext& operator<<(void * n);
   dbgDumpContext& operator<<(const sysSectionValue& n);

   // GROUP: OPERATIONS

   dbgDumpContext& EndLine();

   //------------------------------------------------------------------------
   // Return a reference to an ostream that we can stream to.
   std::_tostream& GetStream();
   operator std::_tostream&();
   
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
   std::_tofstream m_os;

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   dbgFileDumpContext(const dbgDumpContext&);
   dbgDumpContext& operator=(const dbgDumpContext&);

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

#endif // INCLUDED_SYSTEM_FILEDUMPCONTEXT_H_
