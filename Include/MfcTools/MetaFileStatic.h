///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2012  Washington State Department of Transportation
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
#if !defined(AFX_METAFILESTATIC_H__8D398A4E_9072_11D3_ADE0_00105A9AF985__INCLUDED_)
#define AFX_METAFILESTATIC_H__8D398A4E_9072_11D3_ADE0_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*****************************************************************************
CLASS 
   CMetaFileStatic

   CStatic-derived control for displaying a metafile 


DESCRIPTION
   CStatic-derived control for displaying a metafile. To use this class, add it
   as a member to a dialog and then use the DDX_MetaFileStatic method to connect
   it to the metafile.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 11.1.1999 : Created file
*****************************************************************************/

#include <MfcTools\MfcToolsExp.h>

class CMetaFileStatic;
void MFCTOOLSFUNC DDX_MetaFileStatic( CDataExchange* pDX, int nIDC, CMetaFileStatic& rControl,LPCTSTR lpName, LPCTSTR lpType);
void MFCTOOLSFUNC DDX_MetaFileStatic( CDataExchange* pDX, int nIDC, CMetaFileStatic& rControl,HINSTANCE hInstance,LPCTSTR lpName, LPCTSTR lpType);

/////////////////////////////////////////////////////////////////////////////
// CMetaFileStatic window

class MFCTOOLSCLASS CMetaFileStatic : public CStatic
{
// Construction
public:
	CMetaFileStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetaFileStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMetaFileStatic();

   void SetImage( LPCTSTR lpName, LPCTSTR lpType);
   void SetImage( HINSTANCE hInstance,LPCTSTR lpName, LPCTSTR lpType);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMetaFileStatic)
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METAFILESTATIC_H__8D398A4E_9072_11D3_ADE0_00105A9AF985__INCLUDED_)
