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

#pragma once

#include <EAF\EAFExp.h>
#include <afxdlgs.h>
//#include <afxpropertypage.h>
//#include <afxpropertysheet.h>


class CEAFSizeTestingPropertyPage;
class CEAFSizeTestingPropertySheet;
//class CEAFSizeTestingMFCPropertyPage;
//class CEAFSizeTestingMFCPropertySheet;

class EAFCLASS CEAFSizeTestingDialog : public CDialog
{
public:
   explicit CEAFSizeTestingDialog(
      LPCTSTR lpszTemplateName,
      CWnd* pParentWnd = NULL);

   explicit CEAFSizeTestingDialog(
      UINT nIDTemplate,
      CWnd* pParentWnd = NULL);

   CEAFSizeTestingDialog();

   static void CheckDialogSize(BOOL bCheck = TRUE, INT cx = -1, INT cy = -1);

   virtual BOOL OnInitDialog() override;

protected:
   DECLARE_DYNAMIC(CEAFSizeTestingDialog)
   DECLARE_MESSAGE_MAP()
   
private:
   static BOOL m_bCheck;
   static INT m_cx;
   static INT m_cy;

   static void EvaluateWindowSize(CWnd* pWnd);
   friend CEAFSizeTestingPropertyPage;
   friend CEAFSizeTestingPropertySheet;
   //friend CEAFSizeTestingMFCPropertyPage;
   //friend CEAFSizeTestingMFCPropertySheet;
};

class EAFCLASS CEAFSizeTestingPropertyPage : public CPropertyPage
{
public:
   CEAFSizeTestingPropertyPage();
   explicit CEAFSizeTestingPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));
   explicit CEAFSizeTestingPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));
   CEAFSizeTestingPropertyPage(UINT nIDTemplate, UINT nIDCaption,
      UINT nIDHeaderTitle, UINT nIDHeaderSubTitle = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));
   CEAFSizeTestingPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption,
      UINT nIDHeaderTitle, UINT nIDHeaderSubTitle = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));

   virtual BOOL OnInitDialog() override;

protected:
   DECLARE_DYNAMIC(CEAFSizeTestingPropertyPage)
   DECLARE_MESSAGE_MAP()
};

class EAFCLASS CEAFSizeTestingPropertySheet : public CPropertySheet
{
public:
   CEAFSizeTestingPropertySheet();
   explicit CEAFSizeTestingPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL,
      UINT iSelectPage = 0);
   explicit CEAFSizeTestingPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL,
      UINT iSelectPage = 0);
   CEAFSizeTestingPropertySheet(UINT nIDCaption, CWnd* pParentWnd,
      UINT iSelectPage, HBITMAP hbmWatermark,
      HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);
   CEAFSizeTestingPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd,
      UINT iSelectPage, HBITMAP hbmWatermark,
      HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);
   virtual BOOL OnInitDialog() override;

protected:
   DECLARE_DYNAMIC(CEAFSizeTestingPropertySheet)
   DECLARE_MESSAGE_MAP()
};
//
//class EAFCLASS CEAFSizeTestingMFCPropertyPage : public CMFCPropertyPage
//{
//public:
//   CEAFSizeTestingMFCPropertyPage();
//   explicit CEAFSizeTestingMFCPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0);
//   explicit CEAFSizeTestingMFCPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0);
//
//   virtual BOOL OnInitDialog() override;
//
//protected:
//   DECLARE_DYNAMIC(CEAFSizeTestingMFCPropertyPage)
//   DECLARE_MESSAGE_MAP()
//};
//
//
//class EAFCLASS CEAFSizeTestingMFCPropertySheet : public CMFCPropertySheet
//{
//public:
//   CEAFSizeTestingMFCPropertySheet();
//   explicit CEAFSizeTestingMFCPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
//   explicit CEAFSizeTestingMFCPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
//   virtual BOOL OnInitDialog() override;
//
//protected:
//   DECLARE_DYNAMIC(CEAFSizeTestingMFCPropertySheet)
//   DECLARE_MESSAGE_MAP()
//};
