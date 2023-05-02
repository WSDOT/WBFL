///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#include <Math\MathLib.h>
#include <Math\XFixedPointIteration.h>

using namespace WBFL::Math;

XFixedPointIteration::XFixedPointIteration(XFixedPointIteration::Reason reason, Float64 last, const std::_tstring& file, Uint32 line) :
   WBFL::System::XBase(file, line), m_Reason(reason), m_Last(last)
{
}

void XFixedPointIteration::Throw() const
{
   throw *static_cast<const XFixedPointIteration*>(this);
}

Int32 XFixedPointIteration::GetReason() const noexcept
{
   return std::underlying_type<XFixedPointIteration::Reason>::type(m_Reason);
}

XFixedPointIteration::Reason XFixedPointIteration::GetReasonCode() const noexcept
{
   return m_Reason;
}

Float64 XFixedPointIteration::GetLast() const noexcept
{
   return m_Last;
}
