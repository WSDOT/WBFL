///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_TARGETDRAWSTRATEGY_H_
#define INCLUDED_TARGETDRAWSTRATEGY_H_
#pragma once

#include <DManip\DrawPointStrategy.h>

interface iTargetDrawStrategy : public iDrawPointStrategy
{
   STDMETHOD_(void,SetRadius)(LONG radius) PURE;
   STDMETHOD_(LONG,GetRadius)() PURE;
   STDMETHOD_(void,SetFgColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF,GetFgColor)() PURE;
   STDMETHOD_(void,SetBgColor)(COLORREF crColor) PURE;
   STDMETHOD_(COLORREF,GetBgColor)() PURE;
};

#endif // INCLUDED_TARGETDRAWSTRATEGY_H_
