///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2019  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestTangent.h: interface for the CTestTangent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTTangent_H__B9E4933F_5E73_11D5_8C32_006097C68A9C__INCLUDED_)
#define AFX_TESTTangent_H__B9E4933F_5E73_11D5_8C32_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestTangent  
{
public:
   static void Test();
	CTestTangent();
	virtual ~CTestTangent();

private:
   static void TestExternal();
   static void TestCross();
   static void TestPoint();
};

#endif // !defined(AFX_TESTTangent_H__B9E4933F_5E73_11D5_8C32_006097C68A9C__INCLUDED_)
