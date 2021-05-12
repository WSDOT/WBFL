///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2021  Washington State Department of Transportation
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

// TestHarness.h: interface for the CTestHarness class.
//
//////////////////////////////////////////////////////////////////////
 
#if !defined(AFX_TESTHARNESS_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
#define AFX_TESTHARNESS_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Macros to monitor testing 
#include <WBFLTest.h>

// Two macros where no event is expected
#define TRY_TEST_HR(x) TRY_TEST(x, S_OK)
#define TRY_TEST_B(x) TRY_TEST(x, true)
// Model changed event
#define TRY_TEST_MC(x)  TRY_TEST_HR(x); \
                        TRY_TEST(this->PassedModelChangedTest(),true);
// Loading changed event
#define TRY_TEST_LC(x)  TRY_TEST_HR(x); \
                        TRY_TEST(this->PassedLoadingChangedTest(),true);

class ATL_NO_VTABLE CTestHarness :
   public CComObjectRootEx<CComSingleThreadModel>,
   public IFem2dModelEvents
{
public:
   CTestHarness();
	virtual ~CTestHarness();

   CComPtr<IFem2dModel> CreateModel();
   void ReleaseModel(IFem2dModel* pmodel);

BEGIN_COM_MAP(CTestHarness)
   COM_INTERFACE_ENTRY(IFem2dModelEvents)
END_COM_MAP()

// IFem2dModelEvents
public:
   STDMETHOD(OnModelChanged)();
	STDMETHOD(OnLoadingChanged)(LoadCaseIDType Loading);

private:
   bool m_bModelChangedState;
   bool m_bLoadingChangedState;
   DWORD m_dwCookie; // Connection point cookie
   void ModelPass() { m_bModelChangedState = true; }
   void LoadingPass() { m_bLoadingChangedState = true; }
   void InitEventTest() { m_bModelChangedState=false; m_bLoadingChangedState=false; }

protected:
   bool PassedModelChangedTest() 
   {
      bool b = m_bModelChangedState;
      m_bModelChangedState=false;
      return b; 
   }

   bool PassedLoadingChangedTest() 
   {
      bool b = m_bLoadingChangedState;
      m_bLoadingChangedState=false;
      return b; 
   }

};

#endif // !defined(AFX_TESTHarness_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
