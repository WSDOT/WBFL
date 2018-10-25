///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2014  Washington State Department of Transportation
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

// 
// MetaFileStatic.cpp : implementation file
//

#include "stdafx.h"
#include <MfcTools\MetaFileStatic.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetaFileStatic

CMetaFileStatic::CMetaFileStatic()
{
}

CMetaFileStatic::~CMetaFileStatic()
{
}

BEGIN_MESSAGE_MAP(CMetaFileStatic, CStatic)
	//{{AFX_MSG_MAP(CMetaFileStatic)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetaFileStatic message handlers


void DDX_MetaFileStatic( CDataExchange* pDX, int nIDC, CMetaFileStatic& rControl,LPCTSTR lpName, LPCTSTR lpType)
{
   DDX_MetaFileStatic(pDX,nIDC,rControl,AfxGetResourceHandle(),lpName,lpType);
}


void DDX_MetaFileStatic( CDataExchange* pDX, int nIDC, CMetaFileStatic& rControl,HINSTANCE hInstance,LPCTSTR lpName, LPCTSTR lpType)
{
   DDX_Control(pDX, nIDC, rControl);

	if ( !pDX->m_bSaveAndValidate )
   {
      rControl.SetImage(hInstance,lpName,lpType);
   }
}

void CMetaFileStatic::SetImage( LPCTSTR lpName, LPCTSTR lpType)
{
   SetImage(AfxGetResourceHandle(),lpName,lpType);
}

void CMetaFileStatic::SetImage( HINSTANCE hInstance,LPCTSTR lpName, LPCTSTR lpType)
{
   // delete old meta file if one is already attached
   HENHMETAFILE holdmeta;
   holdmeta = GetEnhMetaFile( );
   if (holdmeta!=NULL)
      ::DeleteEnhMetaFile(holdmeta);

   // load resource and set it to static

   HRSRC hResInfo = ::FindResource( hInstance, lpName, lpType );
   DWORD dwError(0);
   if ( hResInfo == 0 )
      dwError = ::GetLastError();

   DWORD dwSize = ::SizeofResource( hInstance, hResInfo );
   HGLOBAL hResData = ::LoadResource( hInstance, hResInfo );
   LPVOID pVoid = ::LockResource( hResData );

   HENHMETAFILE hmeta;
   hmeta = ::SetEnhMetaFileBits(dwSize,(BYTE*)pVoid);
   ASSERT(hmeta!=NULL);
   SetEnhMetaFile(hmeta);
}

void CMetaFileStatic::OnDestroy() 
{
	CStatic::OnDestroy();
	
   HENHMETAFILE hmeta;
   hmeta = GetEnhMetaFile( );
   if (hmeta!=NULL)
      ::DeleteEnhMetaFile(hmeta);
}
