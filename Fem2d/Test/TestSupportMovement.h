///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2010  Washington State Department of Transportation
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

// TestSupportMovement.h: interface for the CTestSupportMovement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSUPPORTMOVEMENT_H__861F0A3A_B19D_11D4_AF3B_00105A9AF985__INCLUDED_)
#define AFX_TESTSUPPORTMOVEMENT_H__861F0A3A_B19D_11D4_AF3B_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestSupportMovement : public CTestHarness
{
public:
	void Test();
	void TestBeam();
	void TestTruss();
   void TestBar();
	CTestSupportMovement();
	virtual ~CTestSupportMovement();

};

#endif // !defined(AFX_TESTSUPPORTMOVEMENT_H__861F0A3A_B19D_11D4_AF3B_00105A9AF985__INCLUDED_)
