///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// TestTransversePierDescription.h: interface for the CTestTransversePierDescription class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_TESTTransversePIERDESCRIPTION_H_
#define INCLUDED_TESTTransversePIERDESCRIPTION_H_

class ATL_NO_VTABLE CTestTransversePierDescription :
   public CComObjectRootEx<CComSingleThreadModel>,
   public ITransversePierDescriptionEvents
{
public:
	static void Test();
	CTestTransversePierDescription();
	virtual ~CTestTransversePierDescription();

   void InitEventTest() { m_bTestState = false; }
   bool PassedEventTest() { return m_bTestState; }

BEGIN_COM_MAP(CTestTransversePierDescription)
   COM_INTERFACE_ENTRY(ITransversePierDescriptionEvents)
END_COM_MAP()

// ITransversePierDescriptionEvents
public:
   STDMETHOD(OnChanged)();

private:
   bool m_bTestState;
   void Pass() { m_bTestState = true; }
};

#endif // INCLUDED_TESTTransversePIERDESCRIPTION_H_
