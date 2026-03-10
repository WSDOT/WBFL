///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#ifndef INCLUDED_EDITABLEUNITVALUETEXTBLOCK_H_
#define INCLUDED_EDITABLEUNITVALUETEXTBLOCK_H_
#pragma once

#include <DManip\TextBlock.h>
#include <WBFLUnitServer.h>

interface iEditableUnitValueTextBlock : public iTextBlock
{
   STDMETHOD_(void,EnableAutoUpdate)(BOOL bEnable) PURE;
   STDMETHOD_(BOOL,IsAutoUpdateEnabled)() PURE;
   STDMETHOD_(void,SetUnitSystem)(IDocUnitSystem* docUnitSystem) PURE;
   STDMETHOD_(void,SetDisplayUnitGroupName)(LPCTSTR strGroupName) PURE;
   STDMETHOD_(void,SetValue)(Float64 value) PURE;
   STDMETHOD_(Float64,GetValue)() PURE;
   STDMETHOD_(Float64,GetEditedValue)() PURE;
   STDMETHOD_(bool,IsStation)() PURE;
   STDMETHOD_(void,IsStation)(bool bIsStation) PURE;
};

#endif // INCLUDED_EDITABLEUNITVALUETEXTBLOCK_H_