///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__D1C61424_FCF0_4558_927A_DA7F59EECA25__INCLUDED_)
#define AFX_STDAFX_H__D1C61424_FCF0_4558_927A_DA7F59EECA25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <Private\WBFLPackage.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <Atlctl.h>

#include <COMDEF.H>

#include <WbflAtlExt.h> // WBFL ATL Extensions and helpers

inline CComBSTR GetHelpFile()
{
   return CComBSTR("WBFLLBAM.chm");
}

#include <WBFLTools.h>
#include <WBFLUnitServer.h>
#include <WBFLLBAM.h>
#include <WBFLLBAMAnalysis.h>
#include <WBFLLBAMUtility.h>
#include <WBFLLBAMLiveLoader.h>

#include <LBAMUtils.h>

 
// macros to help error processing
// short-hand version if consistent naming conventions are used
#define THROW_LBAMC(errNam) { THROW_LBAMC_NOA(errNam);}
#define THROW_LBAMC_NOA(errNam) { throw CComException(_T(__FILE__),__LINE__, IDS_E_##errNam, LBAMC_E_##errNam, IDH_E_##errNam);}
#define THROW_LBAMC_MSG(errNam, msg) { throw CComException(_T(__FILE__),__LINE__, msg, LBAMC_E_##errNam, IDH_E_##errNam);}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D1C61424_FCF0_4558_927A_DA7F59EECA25__INCLUDED)
