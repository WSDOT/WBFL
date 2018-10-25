///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2016  Washington State Department of Transportation
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
// TestHarness.cpp: implementation of the CTestHarness class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestHarness.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestHarness::CTestHarness():
   m_bModelChangedState(false),
   m_bLoadingChangedState(false)
{
}

CTestHarness::~CTestHarness()
{

}

STDMETHODIMP CTestHarness::OnModelChanged()
{
   ModelPass();
   return S_OK;
}

STDMETHODIMP CTestHarness::OnLoadingChanged(LoadCaseIDType loading)
{
   LoadingPass();
   return S_OK;
}

CComPtr<IFem2dModel> CTestHarness::CreateModel()
{
   CComPtr<IFem2dModel> pmodel;
   TRY_TEST(pmodel.CoCreateInstance(CLSID_Fem2dModel),S_OK);
   ATLASSERT(pmodel);

   TRY_TEST(AtlAdvise(pmodel,this,IID_IFem2dModelEvents,&m_dwCookie),S_OK);
   return pmodel;
}

void CTestHarness::ReleaseModel(IFem2dModel* pmodel)
{
   TRY_TEST(AtlUnadvise(pmodel,IID_IFem2dModelEvents,m_dwCookie),S_OK);
}


