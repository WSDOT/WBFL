///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// TestCompoundCurve.h: interface for the CTestCompoundCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCompoundCurve_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
#define AFX_TESTCompoundCurve_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestCompoundCurve
{
public:
   CTestCompoundCurve();

   static void Test();

   static void Test1(); // Unsymmertical Spiral-Curve-Spiral
   static void Test2(); // Spiral-Curve
   static void Test3(); // Curve-Spiral
   static void Test4(); // Circular curve
   static void Test5(); // Left curve
   static void Test6(); 
   static void Test7(); // Error conditions
   static void Test8a(); // Line Curve intersection
   static void Test8b(); // Line Curve intersection
   static void Test9a(); // Line Curve intersection
   static void Test9b(); // Line Curve intersection
   static void Test10a(); // Line Curve intersection
   static void Test10b(); // Line Curve intersection
   static void Test11a(); // Line Curve intersection
   static void Test11b(); // Line Curve intersection
};

#endif // !defined(AFX_TESTCompoundCurve_H__9066FECB_C9F3_11D3_8A20_006097C68A9C__INCLUDED_)
