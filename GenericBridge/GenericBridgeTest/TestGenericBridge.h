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

// TestGenericBridge.h: interface for the CTestGenericBridge class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_TESTGENERICBRIDGE_H_
#define INCLUDED_TESTGENERICBRIDGE_H_

class CTestGenericBridge
{
public:
	static void Test();
	CTestGenericBridge();
	virtual ~CTestGenericBridge();
private:
   static void TestPiers(IGenericBridge* bridge);
   static void TestSegments(IGenericBridge* bridge);


   static void CreateBridgeModel(IGenericBridge** bridge);
   static void CreateAlignment(IGenericBridge* bridge);
   static void CreatePiers(IGenericBridge* bridge);
   static void CreateGirders(IGenericBridge* bridge);

   static void DumpBridge(IGenericBridge* bridge);
   static void ValidateBridge(IGenericBridge* bridge,Float64 stations[],Float64 spanLengths[],CComBSTR orientations[],Float64 spacings[]);
};

#endif // INCLUDED_TESTGENERICBRIDGE_H_
