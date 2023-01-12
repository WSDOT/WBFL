///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// TestModel.h: interface for the CTestModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTMODEL_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
#define AFX_TESTMODEL_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestModel :
public CComObjectRootEx<CComSingleThreadModel>,
public ILBAMModelEvents
{
public:
	static void Test();

	CTestModel();
	virtual ~CTestModel();

BEGIN_COM_MAP(CTestModel)
   COM_INTERFACE_ENTRY(ILBAMModelEvents)
END_COM_MAP()

public:
   STDMETHOD(OnModelChanged)(/*[in]*/ILBAMModel* Model, ChangeType change);

   bool m_csStiffnessFired;
   bool m_csStressPointsFired;
   bool m_csCombinationFired;
   bool m_csStageFired;
   bool m_csPOIFired;
   bool m_csLoadFired;
   bool m_csDescriptionFired;
   bool m_csLiveLoadFired;
   bool m_csLoadCombinationFired;
   bool m_csUserDataFired;
   bool m_csDfDataFired;
   unsigned long m_CsCookie;

protected:
   void InitFired()
   {
      m_csStiffnessFired=false; 
      m_csStressPointsFired=false; 
      m_csCombinationFired=false;
      m_csStageFired=false;
      m_csPOIFired=false;
      m_csLoadFired=false;
      m_csDescriptionFired=false;
      m_csLiveLoadFired=false;
      m_csUserDataFired = false;
      m_csDfDataFired = false;
   }

   void TestLLM(ILiveLoadModel* pllm);

   template <class T>
   void TestLoadModifier(CTestModel* pMe, T* thingWithLm);
};

#endif // !defined(AFX_TESTModel_H__4A50DAE5_753F_11D5_B02C_00105A9AF985__INCLUDED_)
