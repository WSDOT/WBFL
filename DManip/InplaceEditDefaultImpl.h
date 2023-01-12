///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

// InplaceEditDefaultImpl.h: interface for the CInplaceEditDefaultImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPLACEEDITDEFAULTIMPL_H__FC76B7E3_E710_11D4_8B82_006097C68A9C__INCLUDED_)
#define AFX_INPLACEEDITDEFAULTIMPL_H__FC76B7E3_E710_11D4_8B82_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CInplaceEditDefaultImpl : 
   public iInplaceEditable
{
public:
	CInplaceEditDefaultImpl();
	virtual ~CInplaceEditDefaultImpl();

   // iInplaceEditable Implementation
   // Simply implements the DoInplaceEdit template method
   // All other methods must be implemented by subclasses
   STDMETHOD_(void,DoInplaceEdit)() override;
//   virtual void CreateEditControl() = 0;
//   virtual void DestroyEditControl() = 0;
//   virtual void OnTextChanged(LPCTSTR lpszText) = 0;

   virtual void Do_SetParent(iDisplayObject* pParent);
   virtual void Do_GetParent(iDisplayObject** ppParent);


protected:
   // Abstract methods that must be implemented by subclasses

   // Creates an Inplace Edit task
   virtual void CreateTask(iTask** task);

   iDisplayObject* m_pCompositeParent; // weak reference to parent object... typically used when this DO is part of a composite

public:
   // Returns the CDisplayView canvas
   virtual CDisplayView* GetDisplayView() = 0;
   virtual CInplaceEdit* GetEditObject() = 0;
};

#endif // !defined(AFX_INPLACEEDITDEFAULTIMPL_H__FC76B7E3_E710_11D4_8B82_006097C68A9C__INCLUDED_)
