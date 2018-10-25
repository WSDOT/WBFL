///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2010  Washington State Department of Transportation
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

// mfcdual.cpp: Helpful functions for adding dual interface support to
//		        MFC applications

// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"

#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C"
{
/////////////////////////////////////////////////////////////////////////////
// DualHandleException

HRESULT DualHandleException(REFIID riidSource, const CException* pAnyException)
{
    USES_CONVERSION;

    ASSERT_VALID(pAnyException);

    TRACE0("DualHandleException called\n");

    // Set ErrInfo object so that VTLB binding container
    // applications can get rich error information.
    ICreateErrorInfo* pcerrinfo;
    HRESULT hr = CreateErrorInfo(&pcerrinfo);
    if (SUCCEEDED(hr))
    {
	    TCHAR   szDescription[256];
	    LPCTSTR pszDescription = szDescription;
        GUID    guid = GUID_NULL;
        DWORD   dwHelpContext = 0;
        BSTR    bstrHelpFile = NULL;
        BSTR    bstrSource = NULL;
	    if (pAnyException->IsKindOf(RUNTIME_CLASS(COleDispatchException)))
	    {
		    // specific IDispatch style exception
		    COleDispatchException* e = (COleDispatchException*)pAnyException;

            guid = riidSource;
		    hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 
							  (e->m_wCode + 0x200));

		    pszDescription = e->m_strDescription;
		    dwHelpContext = e->m_dwHelpContext;

		    // propagate source and help file if present
            // call ::SysAllocString directly so no further exceptions are thrown
		    if (!e->m_strHelpFile.IsEmpty())
			    bstrHelpFile = ::SysAllocString(T2COLE(e->m_strHelpFile));
		    if (!e->m_strSource.IsEmpty())
			    bstrSource = ::SysAllocString(T2COLE(e->m_strSource));

	    }
	    else if (pAnyException->IsKindOf(RUNTIME_CLASS(CMemoryException)))
	    {
		    // failed memory allocation
		    AfxLoadString(AFX_IDP_FAILED_MEMORY_ALLOC, szDescription);
		    hr = E_OUTOFMEMORY;
	    }
	    else
	    {
		    // other unknown/uncommon error
		    AfxLoadString(AFX_IDP_INTERNAL_FAILURE, szDescription);
		    hr = E_UNEXPECTED;
	    }

	    if (bstrHelpFile == NULL && dwHelpContext != 0)
		    bstrHelpFile = ::SysAllocString(T2COLE(AfxGetApp()->m_pszHelpFilePath));

	    if (bstrSource == NULL)
		    bstrSource = ::SysAllocString(T2COLE(AfxGetAppName()));

        // Set up ErrInfo object
        pcerrinfo->SetGUID(guid);
	    pcerrinfo->SetDescription(::SysAllocString(T2COLE(pszDescription)));
        pcerrinfo->SetHelpContext(dwHelpContext);
        pcerrinfo->SetHelpFile(bstrHelpFile);
        pcerrinfo->SetSource(bstrSource);

        TRACE("\tSource = %ws\n", bstrSource);
        TRACE("\tDescription = %s\n", pszDescription);
        TRACE("\tHelpContext = %lx\n", dwHelpContext);
        TRACE("\tHelpFile = %ws\n", bstrHelpFile);

        // Set the ErrInfo object for the current thread
        IErrorInfo* perrinfo;
        if (SUCCEEDED(pcerrinfo->QueryInterface(IID_IErrorInfo, (LPVOID*)&perrinfo)))
        {
            SetErrorInfo(0, perrinfo);
            perrinfo->Release();
        }

        pcerrinfo->Release();
    }

    TRACE("DualHandleException returning HRESULT %lx\n", hr);
    
    return hr;
}

} // extern "C"