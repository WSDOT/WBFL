///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright � 1999-2025  Washington State Department of Transportation
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

#include <RCSection\RCSectionLib.h>
#include <RCSection\XRCSection.h>

using namespace WBFL::RCSection;


XRCSection::XRCSection(const std::_tstring& lpszReason, const std::_tstring& file, Uint32 line) :
   WBFL::System::XBase(file, line), m_Reason(lpszReason)
{
}

void XRCSection::Throw() const
{
   throw* static_cast<const XRCSection*>(this);
}

Int32 XRCSection::GetReason() const noexcept
{
   return 0;
}

std::_tstring XRCSection::GetErrorMessage() const
{
   auto msg = __super::GetErrorMessage();
   msg += m_Reason;
   return msg;
}

