///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2016  Washington State Department of Transportation
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

#include "StdAfx.h"
#include <MFCTools\AutoRegistry.h>

CAutoRegistry::CAutoRegistry(LPCTSTR lpszProfile)
{
   CWinApp* pApp = AfxGetApp();

   m_strAppProfileName = pApp->m_pszProfileName;
   free((void*)pApp->m_pszProfileName);
   pApp->m_pszProfileName = _tcsdup(lpszProfile);
}

CAutoRegistry::~CAutoRegistry()
{
   CWinApp* pApp = AfxGetApp();
   free((void*)pApp->m_pszProfileName);
   pApp->m_pszProfileName = _tcsdup(m_strAppProfileName);
}
