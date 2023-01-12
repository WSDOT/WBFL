///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <System\Exception.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::System;

XBase::XBase(const std::_tstring& file, Uint32 line ) :
m_File( file ),
m_Line( line )
{
}

XBase::~XBase()
{
}

void XBase::GetErrorMessage(std::_tstring* pMsg) const
{
   const type_info& ti = typeid(*this);
   std::_tostringstream os;
   os << "A " << ti.name() << " error, number " << GetReason()
      << ", has occurred in " << GetFile() << " at line " << GetLine() << std::endl;
   *pMsg = os.str();
}

const std::_tstring& XBase::GetFile() const noexcept
{
   return m_File;
}

Uint32 XBase::GetLine() const noexcept
{
   return m_Line;
}
