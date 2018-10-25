///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2018  Washington State Department of Transportation
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
#pragma once

#include <MfcTools\MfcToolsExp.h>

/////////////////////////////////////////////////////////////////////////////
// CCacheEdit window

class MFCTOOLSCLASS CCacheEdit : public CEdit
{
	DECLARE_DYNAMIC(CCacheEdit)

public:
	CCacheEdit();
	virtual ~CCacheEdit();

// Attributes
public:

// Operations
public:
   void ShowDefaultWhenDisabled(BOOL bShowDefault);
   BOOL ShowDefaultWhenDisabled() const;

   // When the edit control is disabled, the window text is cached and the window is clear
   // When enabled, the cached window text is restored.
   void EnableWindow(BOOL bEnable);

   // Set/Get the default value... When using DDX_UnitValueAndTag, data put into 
   // the control becomes the default value. When the data is extracted from the control
   // and the control is disabled, this default value is returned.
   // the default value. 
   void SetDefaultValue(Float64 value,LPCTSTR strDefault);
   Float64 GetDefaultValue() const;

   CString GetCache() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCacheEdit)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
   CString m_strCache;
   CString m_strDefault;
   Float64 m_DefaultValue;
   BOOL m_bShowDefault;

	//{{AFX_MSG(CCacheEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
