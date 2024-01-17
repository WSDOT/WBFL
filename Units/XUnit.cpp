///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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

#include <Units\UnitsLib.h>
#include <Units\XUnit.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Units;

XUnit::XUnit(Reason reason,const std::_tstring& file,Uint32 line) :
WBFL::System::XBase(file,line),
m_Reason( reason )
{
}

XUnit::~XUnit()
{
}

void XUnit::Throw() const
{
   throw *static_cast<const XUnit*>(this);
}

Int32 XUnit::GetReason() const noexcept
{
   return std::underlying_type<XUnit::Reason>::type(m_Reason);
}

XUnit::Reason XUnit::GetReasonCode() const noexcept
{
   return m_Reason;
}

#if defined _DEBUG
bool XUnit::AssertValid() const
{
   return true; // __super::AssertValid();
}
#endif // _DEBUG
