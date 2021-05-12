///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// TestProfile.h: interface for the CTestProfile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTProfile_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
#define AFX_TESTProfile_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATL_NO_VTABLE CTestProfile :
   public CComObjectRootEx<CComSingleThreadModel>,
   public IProfileEvents
{
public:
   CTestProfile();

   static void Test();

   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestProfile)
   COM_INTERFACE_ENTRY(IProfileEvents)
END_COM_MAP()


// IProfileEvents
public:
	STDMETHOD(OnProfileChanged)(IProfile* pp);

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }

   static void Test1();
   static void Test2();
   static void Test3();
   static void Test4();
   static void Test5();
   static void Test6();
   static void Test7();
   static void Test8();
   static void Test9();
   static void Test10();
   static void Test11();
   static void Test12();
   static void Test13();
   static void Test14();
   static void Test15();
};

#endif // !defined(AFX_TESTProfile_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
