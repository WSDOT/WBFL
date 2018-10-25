///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// TestStationEquationCollection.h: interface for the CTestStationEquationCollection class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class ATL_NO_VTABLE CTestStationEquationCollection :
   public CComObjectRootEx<CComSingleThreadModel>,
   public IStationEquationCollectionEvents
{
public:
   CTestStationEquationCollection();

   static void Test();

   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestStationEquationCollection)
   COM_INTERFACE_ENTRY(IStationEquationCollectionEvents)
END_COM_MAP()

// IStationEquationCollectionEvents
public:
   STDMETHOD(OnEquationAdded)(CollectionIndexType idx,IStationEquation* pp);
   STDMETHOD(OnEquationRemoved)(CollectionIndexType idx);
   STDMETHOD(OnEquationsCleared)();

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }
};
