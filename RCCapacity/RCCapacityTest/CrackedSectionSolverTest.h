///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// CrackedSectionSolverTest.h: interface for the CCrackedSectionSolverTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CrackedSectionSolverTest_H__69A6DB73_8BC5_4D0E_B0E6_50ACD5E81A11__INCLUDED_)
#define AFX_CrackedSectionSolverTest_H__69A6DB73_8BC5_4D0E_B0E6_50ACD5E81A11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCrackedSectionSolverTest  
{
public:
	static void Test();
	CCrackedSectionSolverTest();
	virtual ~CCrackedSectionSolverTest();

private:
   static void TestRectangularBeam();
   static void TestTeeBeam1();
   static void TestTeeBeam2();
   static void TestTeeBeam3();
};

#endif // !defined(AFX_CrackedSectionSolverTest_H__69A6DB73_8BC5_4D0E_B0E6_50ACD5E81A11__INCLUDED_)
