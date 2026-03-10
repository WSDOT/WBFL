///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

// EAFPluginManager.h: interface for the CEAFPluginManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\EAFExp.h>

/////////////////////////////////////////////////////////////////////////////
// IProgress status codes
#define PROGRESS_E_FIRST    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x0200)
#define PROGRESS_E_LAST     MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x020F)

#define PROGRESS_E_CREATE           (PROGRESS_E_FIRST+0) // Error creating progress window


// Progress Window Flags
#define PW_ALL        0x0000
#define PW_NOMESSAGE  0x0001
#define PW_NOGAUGE    0x0002
#define PW_NOCANCEL   0x0004

// {B7B035CF-5B1E-426E-BB4D-176B5D7311F0}
DEFINE_GUID(IID_IEAFProgress,
	0xb7b035cf, 0x5b1e, 0x426e, 0xbb, 0x4d, 0x17, 0x6b, 0x5d, 0x73, 0x11, 0xf0);
class EAFCLASS IEAFProgress
{
public:
	virtual HRESULT CreateProgressWindow(DWORD dwMask, UINT nDelay) = 0;
	virtual HRESULT Init(short begin,short end,short inc) = 0;
	virtual HRESULT Increment() = 0;
	virtual HRESULT UpdateMessage(LPCTSTR msg) = 0;
	virtual HRESULT Continue() = 0;
	virtual HRESULT DestroyProgressWindow() = 0;
};
