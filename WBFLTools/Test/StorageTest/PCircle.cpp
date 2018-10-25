///////////////////////////////////////////////////////////////////////
// ToolsStorage - Test driver for WBFLTools library
// Copyright © 1999-2011  Washington State Department of Transportation
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
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// PCircle.cpp : Implementation of CPCircle
#include "stdafx.h"
#if defined _DEBUG
#include "Debug\StorageTest.h"
#else
#include "Release\StorageTest.h"
#endif

#include "PCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCircle


STDMETHODIMP CPCircle::get_Diameter(Float64 *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Diameter;

	return S_OK;
}

STDMETHODIMP CPCircle::put_Diameter(Float64 newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Diameter = newVal;

	return S_OK;
}
