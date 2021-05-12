///////////////////////////////////////////////////////////////////////
// GenericBridgeToolsTest - Test driver for generic bridge tools library
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

// TestEffectiveFlangeWidthTool.h: interface for the CTestEffectiveFlangeWidthTool class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_TESTEFFECTIVEFLANGEWIDTHTOOL_H_
#define INCLUDED_TESTEFFECTIVEFLANGEWIDTHTOOL_H_

class CTestEffectiveFlangeWidthTool
{
public:
	static void Test();
	CTestEffectiveFlangeWidthTool();
	virtual ~CTestEffectiveFlangeWidthTool();

private:
   static void TestPrecastGirderBridge();
   static void TestSpliceGirderBridge();
};

#endif // INCLUDED_TESTEFFECTIVEFLANGEWIDTHTOOL_H_
