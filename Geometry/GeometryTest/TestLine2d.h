///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// TestLine2d.h: interface for the CTestLine2d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTLINE2D_H__5B12E401_AF9C_11D3_8CDF_FF25C5D0C656__INCLUDED_)
#define AFX_TESTLINE2D_H__5B12E401_AF9C_11D3_8CDF_FF25C5D0C656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestLine2d  
{
public:
	static void Test();
	CTestLine2d();
	virtual ~CTestLine2d();

private:
	static void TestISupportErrorInfo();
};

#endif // !defined(AFX_TESTLINE2D_H__5B12E401_AF9C_11D3_8CDF_FF25C5D0C656__INCLUDED_)
