///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <Materials/MatLib.h>
#include <Materials/FiberConcrete.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

FiberConcrete::FiberConcrete()
{
}

FiberConcrete::FiberConcrete(const std::_tstring& name,Float64 fiberLength) :
   Concrete(name),
   m_FiberLength(fiberLength)
{
}

void FiberConcrete::SetFiberLength(Float64 fiberLength)
{
   m_FiberLength = fiberLength;
   ASSERTVALID;
}

Float64 FiberConcrete::GetFiberLength() const
{
   return m_FiberLength;
}


#if defined _DEBUG
bool FiberConcrete::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void FiberConcrete::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for FiberConcrete")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool FiberConcrete::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("FiberConcrete");
   TESTME_EPILOG("FiberConcrete");
}
#endif // _UNITTEST
