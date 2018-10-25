///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2015  Washington State Department of Transportation
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
#include <WBFLAll.h>
#include <System\DbgBuild.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class sysSectionValue;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   dbgDumpContext

   Class used in Dump member functions to dump class data.


DESCRIPTION
   Class used in Dump member functions to dump class data.
   This implementation dumps to the debug window.

COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 06.01.1998 : Created file
*****************************************************************************/

class SYSCLASS dbgDumpContext
{
public:
   // GROUP: LIFECYCLE
   dbgDumpContext();
   virtual ~dbgDumpContext();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // 
   // Inserters for various built-ins
   virtual dbgDumpContext& operator<<(const std::_tstring& s);
   virtual dbgDumpContext& operator<<(LPCTSTR s);
   virtual dbgDumpContext& operator<<(TCHAR ch);    
   virtual dbgDumpContext& operator<<(DWORD n);    
   virtual dbgDumpContext& operator<<(bool n);
   virtual dbgDumpContext& operator<<(Int16 n);
   virtual dbgDumpContext& operator<<(Uint16 n);
   virtual dbgDumpContext& operator<<(Int32 n);
   virtual dbgDumpContext& operator<<(Uint32 n);
   virtual dbgDumpContext& operator<<(Int64 n);
   virtual dbgDumpContext& operator<<(Uint64 n);
   virtual dbgDumpContext& operator<<(Float32 n);    
   virtual dbgDumpContext& operator<<(Float64 n);
   virtual dbgDumpContext& operator<<(Float80 n);
   virtual dbgDumpContext& operator<<(void * n);
   virtual dbgDumpContext& operator<<(const sysSectionValue& n);

   // GROUP: OPERATIONS
   virtual dbgDumpContext& EndLine();
  
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
SYSFUNC dbgDumpContext& operator<<(dbgDumpContext& dc,dbgDumpContext& (*pf)(dbgDumpContext&));
SYSFUNC dbgDumpContext& endl(dbgDumpContext& dmpCtx);
