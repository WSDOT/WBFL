#ifndef INCLUDED_ATLDDX_H_
#define INCLUDED_ATLDDX_H_
///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// 4500 3rd Ave SE, P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


// Some helper methods for moving data in and out of dialog controls for
// ATL ActiveX components. Using the DDX notations to mimix the MFC
// procedures for the same purpose, however this has nothing to do
// with MFC

#include <float.h> // for DBL_DIG

inline void DDX_GetDouble(HWND hwndDlg,int nIDC,double* value)
{
   HWND hWndCtrl = ::GetDlgItem(hwndDlg,nIDC);
   ATLASSERT( hWndCtrl != NULL);

   TCHAR szBuffer[32];
   ::GetWindowText(hWndCtrl,szBuffer,sizeof(szBuffer)/sizeof(szBuffer[0]));

   *value = _tcstod(szBuffer,(LPTSTR*)&szBuffer);
}

inline void DDX_PutDouble(HWND hwndDlg,int nIDC,double value)
{
   HWND hWndCtrl = ::GetDlgItem(hwndDlg,nIDC);
   ATLASSERT( hWndCtrl != NULL);

   TCHAR szBuffer[32];
   _stprintf_s(szBuffer,sizeof(szBuffer),_T("%.*g"),DBL_DIG,value);
   ::SetWindowText(hWndCtrl,szBuffer);
}

inline void DDX_GetUnitValue(HWND hwndDlg,int nIDC,CComBSTR bstrGroup,double* value,IDocUnitSystem* unitSystem)
{
   // Get the value in display units
   DDX_GetDouble(hwndDlg,nIDC,value);

   // Convert value to system units
   unitSystem->ConvertFromDisplayUnits(*value,bstrGroup,value);
}

inline void DDX_PutUnitValue(HWND hwndDlg,int nIDC,int nIDCTag,CComBSTR bstrGroup,double value,IDocUnitSystem* unitSystem)
{
   USES_CONVERSION;

   HWND hWndEditCtrl = ::GetDlgItem(hwndDlg,nIDC);
   ATLASSERT( hWndEditCtrl != NULL);

   HWND hWndTagCtrl = ::GetDlgItem(hwndDlg,nIDCTag);
   ATLASSERT( hWndTagCtrl != NULL);

   // Get the unit tag and put it in the text control
   CComBSTR bstrTag;
   unitSystem->get_Tag(bstrGroup,&bstrTag);
   ::SetWindowText(hWndTagCtrl,OLE2T(bstrTag));

   // Convert the value to display units and put it in the edit control
   CComBSTR bstrValue;
   unitSystem->Format(value,bstrGroup,VARIANT_FALSE,&bstrValue);
   ::SetWindowText(hWndEditCtrl,OLE2T(bstrValue));
}

#endif // INCLUDED_ATLDDX_H_