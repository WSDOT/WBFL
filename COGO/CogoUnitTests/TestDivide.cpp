///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// TestDivide.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestDivide.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestDivide)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IDivide> divide;
         ASSERT_EQ(divide.CoCreateInstance(CLSID_CogoModel),S_OK);

         CComQIPtr<ICogoModel> model(divide);
         ASSERT_EQ( model != nullptr, true );

         model->StorePoint(1,0,0);
         model->StorePoint(2,10,0);
         model->StorePoint(3,-10,0);

         CComPtr<IPoint2d> pnt;
         Float64 x,y;

         // Test DivideArc
         ASSERT_EQ(divide->Arc(4,1,2,1,3,-1),E_INVALIDARG);
         ASSERT_EQ(divide->Arc(4,1,2,1,3,0),E_INVALIDARG);
         ASSERT_EQ(divide->Arc(4,1,2,1,3,1),E_INVALIDARG);
         ASSERT_EQ(divide->Arc(4,1,-2,1,3,4), E_INVALIDARG);
         ASSERT_EQ(divide->Arc(4,1,2,-1,3,4), E_INVALIDARG);
         ASSERT_EQ(divide->Arc(4,1,2,1,-3,4), E_INVALIDARG);
         ASSERT_EQ(divide->Arc(1,1,2,1,3,4), S_FALSE);
         ASSERT_EQ(divide->Arc(4,0,2,1,3,4),E_INVALIDARG);
         ASSERT_EQ(divide->Arc(4,1,1,1,3,4), S_FALSE);
         ASSERT_EQ(divide->Arc(4,1,2,1,1,4), S_FALSE);
         //ASSERT_EQ(divide->Arc(4,1,2,1,2,4), E_INVALIDARG);
         ASSERT_EQ(divide->Arc(4,1,2,1,3,4),S_OK);
         pnt.Release();
         ASSERT_EQ(model->GetPointByID(4,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,7.07106781187),true);
         ASSERT_EQ(IsEqual(y,7.07106781187),true);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(5,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,0.0),true);
         ASSERT_EQ(IsEqual(y,10.0),true);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(6,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,-7.07106781187),true);
         ASSERT_EQ(IsEqual(y,7.07106781187),true);

         // Test Divide BetweenPoints
         model->ClearPoints();
         model->StorePoint(1,10,10);
         model->StorePoint(2,110,110);

         ASSERT_EQ(divide->BetweenPoints(3,1,1,2,-1),  E_INVALIDARG);
         ASSERT_EQ(divide->BetweenPoints(3,1,1,2, 0),  E_INVALIDARG);
         ASSERT_EQ(divide->BetweenPoints(3,1,1,2, 1),  E_INVALIDARG);
         ASSERT_EQ(divide->BetweenPoints(3,0,1,2,10),  E_INVALIDARG);
         ASSERT_EQ(divide->BetweenPoints(3,1,-1,2,10), E_INVALIDARG);
         ASSERT_EQ(divide->BetweenPoints(3,1,1,-2,10), E_INVALIDARG);
         ASSERT_EQ(divide->BetweenPoints(1,1,1,2,10), S_FALSE);

         ASSERT_EQ(divide->BetweenPoints(3,1,1,2,10),S_OK);
         for ( IDType i = 3; i <= 11; i++ )
         {
            pnt.Release();
            ASSERT_EQ(model->GetPointByID(i,&pnt),S_OK);
            pnt->get_X(&x);
            pnt->get_Y(&y);
            ASSERT_EQ(IsEqual(x,(i-1)*10.),true);
            ASSERT_EQ(IsEqual(y,(i-1)*10.),true);
         }

         // Test Divide LineSegment
         model->ClearPoints();
         model->StorePoint(1,10,10);
         model->StorePoint(2,110,110);
         CComPtr<IPoint2d> p1, p2;
         model->GetPointByID(1,&p1);
         model->GetPointByID(2,&p2);

         model->StorePathSegment(1,1,2);

         ASSERT_EQ(divide->LineSegment(3,1,1,-1),  E_INVALIDARG);
         ASSERT_EQ(divide->LineSegment(3,1,1, 0),  E_INVALIDARG);
         ASSERT_EQ(divide->LineSegment(3,1,1, 1),  E_INVALIDARG);
         ASSERT_EQ(divide->LineSegment(3,0,1,10),  E_INVALIDARG);
         ASSERT_EQ(divide->LineSegment(3,1,-1,10), E_INVALIDARG);
         ASSERT_EQ(divide->LineSegment(1,1,1,10),  S_FALSE);

         ASSERT_EQ(divide->LineSegment(3,1,1,10),S_OK);
         for ( int i = 3; i <= 11; i++ )
         {
            pnt.Release();
            ASSERT_EQ(model->GetPointByID(i,&pnt),S_OK);
            pnt->get_X(&x);
            pnt->get_Y(&y);
            ASSERT_EQ(IsEqual(x,(i-1)*10.),true);
            ASSERT_EQ(IsEqual(y,(i-1)*10.),true);
         }

         // Test CompoundCurve
         model->StorePoint(101,0,1000);
         model->StorePoint(102,700,1000);
         model->StorePoint(103,1000,700);

         model->StoreCompoundCurve(1,101,102,103,500,100,TransitionCurveType::Clothoid,200, TransitionCurveType::Clothoid);

         ASSERT_EQ(divide->CompoundCurve(150,1,1,-1),E_INVALIDARG);
         ASSERT_EQ(divide->CompoundCurve(150,0,1,5),E_INVALIDARG);
         ASSERT_EQ(divide->CompoundCurve(150,1,-1,5), E_INVALIDARG);
         ASSERT_EQ(divide->CompoundCurve(99,1,1,5),S_FALSE);

         ASSERT_EQ(divide->CompoundCurve(150,1,1,10),S_OK);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(150,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,493.3008,0.001),true);
         ASSERT_EQ(IsEqual(y,999.4672,0.001),true);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(151,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,547.4251,0.001),true);
         ASSERT_EQ(IsEqual(y,995.7440,0.001),true);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(152,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,600.8740,0.001),true);
         ASSERT_EQ(IsEqual(y,986.4948,0.001),true);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(153,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,653.0065,0.001),true);
         ASSERT_EQ(IsEqual(y,971.5102,0.001),true);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(154,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,703.2089,0.001),true);
         ASSERT_EQ(IsEqual(y,950.9663,0.001),true);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(155,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,750.8904,0.001),true);
         ASSERT_EQ(IsEqual(y,925.1051,0.001),true);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(156,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,795.5411,0.001),true);
         ASSERT_EQ(IsEqual(y,894.2997,0.001),true);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(157,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,837.3133,0.001),true);
         ASSERT_EQ(IsEqual(y,859.6735,0.001),true);

         pnt.Release();
         ASSERT_EQ(model->GetPointByID(158,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,876.9803,0.001),true);
         ASSERT_EQ(IsEqual(y,822.6429,0.001),true);
   }
};
} // namespace CogoUnitTests