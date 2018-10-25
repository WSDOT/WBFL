///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright © 1999-2018  Washington State Department of Transportation
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

// SolverTest.h: interface for the CSolverTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLVERTEST_H__A2D8EBF0_20FB_4964_8DDD_54376FCABCB7__INCLUDED_)
#define AFX_SOLVERTEST_H__A2D8EBF0_20FB_4964_8DDD_54376FCABCB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSolverTest  
{
public:
	static void Test();
	CSolverTest();
	virtual ~CSolverTest();

private:
   static void CheckSolution(IRCSolution*   pSolution,Float64 c,Float64 Mn,Float64 Cflange,Float64 Cweb,Float64 Yflange,Float64 Yweb,Float64 T, Float64 fps,VARIANT_BOOL bIsOverReinforced);
   static void CheckSolution(IRCSolutionEx* pSolution,Float64 c,Float64 Mn,Float64 Cflange,Float64 Cweb,Float64 Yflange,Float64 Yweb,Float64 T);
   static void Test1();
   static void Test2();

};

#endif // !defined(AFX_SOLVERTEST_H__A2D8EBF0_20FB_4964_8DDD_54376FCABCB7__INCLUDED_)
