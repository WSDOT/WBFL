///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2022  Washington State Department of Transportation
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

// TestCrossSection.h: interface for the CTestCrossSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCrossSection_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
#define AFX_TESTCrossSection_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATL_NO_VTABLE CTestCrossSection :
   public CComObjectRootEx<CComSingleThreadModel>,
   public ICrossSectionEvents
{
public:
   CTestCrossSection();

   static void Test();

   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestCrossSection)
   COM_INTERFACE_ENTRY(ICrossSectionEvents)
END_COM_MAP()

// ICrossSectionEvents
public:
	STDMETHOD(OnCrossSectionChanged)(ICrossSection* CrossSection);
	STDMETHOD(OnCrossSectionMoved)(ICrossSection* CrossSection);

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }
};

#endif // !defined(AFX_TESTCrossSection_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
