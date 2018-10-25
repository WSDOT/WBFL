///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// TestSize3d.h: interface for the CTestSize3d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSIZE3D_H__6FECF102_B6A3_11D3_8CDF_C9DF305B3C59__INCLUDED_)
#define AFX_TESTSIZE3D_H__6FECF102_B6A3_11D3_8CDF_C9DF305B3C59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestSize3d  
{
public:
	static void Test();
	CTestSize3d();
	virtual ~CTestSize3d();

private:
	static void TestISupportErrorInfo();
};

#endif // !defined(AFX_TESTSIZE3D_H__6FECF102_B6A3_11D3_8CDF_C9DF305B3C59__INCLUDED_)
