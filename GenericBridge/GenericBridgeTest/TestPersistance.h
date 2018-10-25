///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2013  Washington State Department of Transportation
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

// TestPersistance.h: interface for the CTestPersistance class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_TESTPERSISTANCE_H_
#define INCLUDED_TESTPERSISTANCE_H_


class ATL_NO_VTABLE CTestPersistance
{
public:
	static void Test();

	CTestPersistance();
	virtual ~CTestPersistance();

private:
   static bool TestBridge(IGenericBridge* pBridge);
   static void BuildSegment(IPrismaticSegment* segment);
};

#endif // INCLUDED_TESTPERSISTANCE_H_
