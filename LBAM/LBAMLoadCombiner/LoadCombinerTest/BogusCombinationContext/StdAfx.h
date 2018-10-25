///////////////////////////////////////////////////////////////////////
// BogusCombinationContext - Test driver for LBAM load combinations
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently
#include <iostream>

#if !defined(AFX_STDAFX_H__99DDB030_A2A9_44F6_982B_F15CFE1D5C32__INCLUDED_)
#define AFX_STDAFX_H__99DDB030_A2A9_44F6_982B_F15CFE1D5C32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <Private\WBFLPackage.h>

#include <afxdisp.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <WBFLTest.h>

#include <WBFLTools.h>
#include <WBFLLBAM.h>
#include <WBFLLBAMAnalysis.h>
#include <WBFLLBAMLiveLoader.h>
#include <WBFLLBAMLoadCombiner.h>

#include <LBAMUtils.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__99DDB030_A2A9_44F6_982B_F15CFE1D5C32__INCLUDED)
