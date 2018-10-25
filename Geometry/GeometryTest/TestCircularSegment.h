///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TestCircularSegment.h: interface for the CTestCircularSegment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCIRCULARSEGMENT_H__C6C2A644_6563_11D4_8CE4_0080C7380027__INCLUDED_)
#define AFX_TESTCIRCULARSEGMENT_H__C6C2A644_6563_11D4_8CE4_0080C7380027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestCircularSegment  
{
public:
	static void Test();
	CTestCircularSegment();
	virtual ~CTestCircularSegment();

private:
	static void TestIXYPosition();
	static void TestISupportErrorInfo();
	static void TestIShape();
	static void TestIObjectSafety();
	static void TestICircularSegment();

   static void OtherTests();
};

#endif // !defined(AFX_TESTCIRCULARSEGMENT_H__C6C2A644_6563_11D4_8CE4_0080C7380027__INCLUDED_)
