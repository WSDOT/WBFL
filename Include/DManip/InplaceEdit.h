///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_INPLACEEDITABLE_H_
#define INCLUDED_INPLACEEDITABLE_H_
#pragma once

class CInplaceEdit;

interface iInplaceEditable : public IUnknown
{
   // Call to start the Inplace Editing process
   // This is a Template Method.
   STDMETHOD_(void,DoInplaceEdit)() PURE;

   // Called when it is time to create an edit control on the screen
   STDMETHOD_(void,CreateEditControl)() PURE;

   // Called when it is time to destroy the edit control
   STDMETHOD_(void,DestroyEditControl)() PURE;

   STDMETHOD_(BOOL,ValidateData)() PURE;

   STDMETHOD_(void,OnDataChanged)() PURE;
};

#endif // INCLUDED_INPLACEEDITABLE_H_