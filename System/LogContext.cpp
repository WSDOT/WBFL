///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright � 1999-2022  Washington State Department of Transportation
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

#include <System\SysLib.h>
#include <System\LogContext.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Debug;

#define BUFSIZE 256

LogContext::LogContext()
{
}

LogContext::~LogContext()
{
}

namespace WBFL
{
   namespace Debug
   {
      LogContext& operator<<(LogContext& context, LogContext& (*pf)(LogContext&))
      {
         return (*pf)(context);
      }

      LogContext& endl(LogContext& context)
      {
         return context.EndLine();
      }
   }
}
