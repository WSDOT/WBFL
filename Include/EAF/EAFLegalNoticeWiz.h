///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright � 1999-2026  Washington State Department of Transportation
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
#include <EAF\EAFLegalNoticeStep1.h>
#include <EAF\EAFLegalNoticeStep2.h>

// Which license text to display in the wizard
enum class EAFLicenseType
{
   AROSL = 1, // Alternate Route Open Source License
   ARLOSL = 2 // Alternate Route Library Open Source License
};

// Whether the user accepted or rejected the license
enum class EAFAcceptanceType
{
   Accept = 1,
   Reject = 2
};

// Text content shown by the wizard, compiled into this DLL as TEXT-type resources.
// Resolve against this DLL's own module handle regardless of which module is
// ambiently active on the calling thread, since FindResource/LoadResource (unlike
// MFC's chain-searching dialog-template loader) only look in the exact module
// handle given to them.
EAFCLASS CString EAFGetLicenseText(EAFLicenseType license);
EAFCLASS CString EAFGetDisclaimerText();

// CEAFLegalNoticeWiz

class EAFCLASS CEAFLegalNoticeWiz : public CPropertySheet
{
	DECLARE_DYNAMIC(CEAFLegalNoticeWiz)

public:
	CEAFLegalNoticeWiz(CWnd* pParent, EAFLicenseType license = EAFLicenseType::AROSL);
	virtual ~CEAFLegalNoticeWiz();

   void GiveChoice(BOOL bGiveChoice);
   void ShowLegalNoticeAgain(BOOL bShow);
   BOOL ShowLegalNoticeAgain();

	virtual BOOL OnInitDialog() override;

protected:
   CEAFLegalNoticeStep1 m_Page1;
   CEAFLegalNoticeStep2 m_Page2;
   EAFLicenseType m_License;

   BOOL m_bGiveChoice;

   void Init();
	DECLARE_MESSAGE_MAP()
};
