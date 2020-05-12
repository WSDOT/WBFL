///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

// EAFDialog.cpp : implementation file
//

#include <EAF\EAFSizeTestingDialog.h>
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CEAFSizeTestingDialog::m_bCheck = FALSE;
INT CEAFSizeTestingDialog::m_cx = -1;
INT CEAFSizeTestingDialog::m_cy = -1;

void CEAFSizeTestingDialog::CheckDialogSize(BOOL bCheck, INT cx, INT cy)
{
   m_bCheck = bCheck;
   m_cx = cx;
   m_cy = cy;
}


IMPLEMENT_DYNAMIC(CEAFSizeTestingDialog, CDialog)

CEAFSizeTestingDialog::CEAFSizeTestingDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd) :
   CDialog(lpszTemplateName, pParentWnd)
{
}

CEAFSizeTestingDialog::CEAFSizeTestingDialog(UINT nIDTemplate, CWnd* pParentWnd) :
   CDialog(nIDTemplate, pParentWnd)
{
}

CEAFSizeTestingDialog::CEAFSizeTestingDialog() : CDialog()
{
}

BEGIN_MESSAGE_MAP(CEAFSizeTestingDialog, CDialog)
END_MESSAGE_MAP()

BOOL CEAFSizeTestingDialog::OnInitDialog()
{
   CEAFSizeTestingDialog::EvaluateWindowSize(this);
   return CDialog::OnInitDialog();
}

void CEAFSizeTestingDialog::EvaluateWindowSize(CWnd* pWnd)
{
   if (m_bCheck)
   {
      static CWnd* pDesktop = GetDesktopWindow();
      int cx, cy;
      if (m_cx < 0 || m_cy < 0)
      {
         // maximum size not given... use the size defined in the windows UX Guide
         // https://docs.microsoft.com/en-us/windows/win32/uxguide/top-violations
         //CDC* pDC = pDesktop->GetDC();
         //auto dpiX = pDC->GetDeviceCaps(LOGPIXELSX);
         //auto dpiY = pDC->GetDeviceCaps(LOGPIXELSY);
         //ATLASSERT(dpiX == dpiY);

         if (m_cx < 0)
         {
            cx = 800;// (dpiX == 96 ? 800 : dpiX == 120 ? 1024 : 1200);
         }
         else
         {
            cx = m_cx;
         }

         if (m_cy < 0)
         {
            cy = 600; // (dpiY == 96 ? 600 : dpiX == 120 ? 768 : 900);
         }
         else
         {
            cy = m_cy;
         }
      }
      else
      {
         cx = m_cx;
         cy = m_cy;
      }

      CRect rect;
      if (pWnd->IsKindOf(RUNTIME_CLASS(CPropertyPage)))
      {
         CWnd* pParent = pWnd->GetParent();
         pParent->GetWindowRect(&rect);
      }
      else
      {
         pWnd->GetWindowRect(&rect);
      }

      if (cx < rect.Width() || cy < rect.Height())
      {
         USES_CONVERSION;
         CRect rDT;
         pDesktop->GetWindowRect(&rDT);

         CString str;
         str.Format(_T("%s\r\nDialog exceeds target size (%d x %d).\r\nActual size is: (%d x %d)\r\nEffective desktop size is: (%d x %d)"), A2T(pWnd->GetRuntimeClass()->m_lpszClassName), cx, cy, rect.Width(), rect.Height(), rDT.Width(), rDT.Height());
         AfxMessageBox(str);
      }
   }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CEAFSizeTestingPropertyPage, CPropertyPage)

CEAFSizeTestingPropertyPage::CEAFSizeTestingPropertyPage() :
   CPropertyPage()
{
}

CEAFSizeTestingPropertyPage::CEAFSizeTestingPropertyPage(UINT nIDTemplate, UINT nIDCaption, DWORD dwSize) :
   CPropertyPage(nIDTemplate, nIDCaption, dwSize)
{
}

CEAFSizeTestingPropertyPage::CEAFSizeTestingPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption, DWORD dwSize) :
   CPropertyPage(lpszTemplateName, nIDCaption, dwSize)
{
}

CEAFSizeTestingPropertyPage::CEAFSizeTestingPropertyPage(UINT nIDTemplate, UINT nIDCaption, UINT nIDHeaderTitle, UINT nIDHeaderSubTitle, DWORD dwSize) :
   CPropertyPage(nIDTemplate, nIDCaption, nIDHeaderTitle, nIDHeaderSubTitle, dwSize)
{
}

CEAFSizeTestingPropertyPage::CEAFSizeTestingPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption, UINT nIDHeaderTitle, UINT nIDHeaderSubTitle, DWORD dwSize) :
   CPropertyPage(lpszTemplateName, nIDCaption, nIDHeaderTitle, nIDHeaderSubTitle, dwSize)
{
}

BEGIN_MESSAGE_MAP(CEAFSizeTestingPropertyPage, CPropertyPage)
END_MESSAGE_MAP()

BOOL CEAFSizeTestingPropertyPage::OnInitDialog()
{
   CEAFSizeTestingDialog::EvaluateWindowSize(this);
   return CPropertyPage::OnInitDialog();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CEAFSizeTestingPropertySheet, CPropertySheet)

CEAFSizeTestingPropertySheet::CEAFSizeTestingPropertySheet() :
   CPropertySheet()
{
}

CEAFSizeTestingPropertySheet::CEAFSizeTestingPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage) :
   CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CEAFSizeTestingPropertySheet::CEAFSizeTestingPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage) :
   CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CEAFSizeTestingPropertySheet::CEAFSizeTestingPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage, HBITMAP hbmWatermark, HPALETTE hpalWatermark, HBITMAP hbmHeader) :
   CPropertySheet(nIDCaption, pParentWnd, iSelectPage, hbmWatermark, hpalWatermark, hbmHeader)
{
}

CEAFSizeTestingPropertySheet::CEAFSizeTestingPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage, HBITMAP hbmWatermark, HPALETTE hpalWatermark, HBITMAP hbmHeader) :
   CPropertySheet(pszCaption, pParentWnd, iSelectPage, hbmWatermark, hpalWatermark, hbmHeader)
{
}

BEGIN_MESSAGE_MAP(CEAFSizeTestingPropertySheet, CPropertySheet)
END_MESSAGE_MAP()

BOOL CEAFSizeTestingPropertySheet::OnInitDialog()
{
   CEAFSizeTestingDialog::EvaluateWindowSize(this);
   return CPropertySheet::OnInitDialog();
}

//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//IMPLEMENT_DYNAMIC(CEAFSizeTestingMFCPropertyPage, CMFCPropertyPage)
//
//CEAFSizeTestingMFCPropertyPage::CEAFSizeTestingMFCPropertyPage() :
//   CMFCPropertyPage()
//{
//}
//
//CEAFSizeTestingMFCPropertyPage::CEAFSizeTestingMFCPropertyPage(UINT nIDTemplate, UINT nIDCaption) :
//   CMFCPropertyPage(nIDTemplate, nIDCaption)
//{
//}
//
//CEAFSizeTestingMFCPropertyPage::CEAFSizeTestingMFCPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption) :
//   CMFCPropertyPage(lpszTemplateName, nIDCaption)
//{
//}
//
//BEGIN_MESSAGE_MAP(CEAFSizeTestingMFCPropertyPage, CMFCPropertyPage)
//END_MESSAGE_MAP()
//
//BOOL CEAFSizeTestingMFCPropertyPage::OnInitDialog()
//{
//   CEAFSizeTestingDialog::EvaluateWindowSize(this);
//   return __super::OnInitDialog();
//}
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//IMPLEMENT_DYNAMIC(CEAFSizeTestingMFCPropertySheet, CMFCPropertySheet)
//
//CEAFSizeTestingMFCPropertySheet::CEAFSizeTestingMFCPropertySheet() :
//   CMFCPropertySheet()
//{
//}
//
//CEAFSizeTestingMFCPropertySheet::CEAFSizeTestingMFCPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage) :
//   CMFCPropertySheet(nIDCaption, pParentWnd, iSelectPage)
//{
//}
//
//CEAFSizeTestingMFCPropertySheet::CEAFSizeTestingMFCPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage) :
//   CMFCPropertySheet(pszCaption, pParentWnd, iSelectPage)
//{
//}
//
//BEGIN_MESSAGE_MAP(CEAFSizeTestingMFCPropertySheet, CMFCPropertySheet)
//END_MESSAGE_MAP()
//
//BOOL CEAFSizeTestingMFCPropertySheet::OnInitDialog()
//{
//   CEAFSizeTestingDialog::EvaluateWindowSize(this);
//   return __super::OnInitDialog();
//}
