///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
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
// PrinterJob.h: interface for the CPrinterJob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTERJOB_H__7EADD893_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_)
#define AFX_PRINTERJOB_H__7EADD893_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <MfcTools\MfcToolsExp.h>


class MFCTOOLSCLASS CPrinterJob  
{
public:
	void OnPrepareDC(CDC * pDC, CPrintInfo * pInfo);
	CWnd * pParent;
	CString strTitle;
	bool bAlreadyAskedPageOpt;

	bool DoPreparePrinting(CPrintInfo* pInfo);
	virtual void OnFilePrint(bool direct=false);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual bool OnPreparePrinting(CPrintInfo* pInfo, bool bPrintPreview = false);
	CPrinterJob();
	virtual ~CPrinterJob();

};

#endif // !defined(AFX_PRINTERJOB_H__7EADD893_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_)
