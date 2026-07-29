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

// TestTransitionCurve.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestTransitionCurve.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

// Ported unchanged from F:\ARP\WBFL\COGO\CogoTest\TestTransitionCurve.cpp: walks
// a transition curve at 5 stations and compares each point against expected
// (x,y) values, used by Test1() below.
void Verify(Float64 L, ITransitionCurve* pCurve, std::array<std::pair<Float64, Float64>, 6>& values)
{
   CComQIPtr<IPathElement> element(pCurve);
   static Float64 tol = 0.0001;
   auto size = values.size();
   for (auto i = 0; i < size; i++)
   {
      Float64 s = i*L / (size-1);
      CComPtr<IPoint2d> p;
      element->PointOnCurve(s, &p);

      Float64 x, y;
      p->Location(&x, &y);

      ASSERT_EQ(IsEqual(values[i].first, x, tol), true);
      ASSERT_EQ(IsEqual(values[i].second, y, tol), true);
   }
}

TEST_CLASS(TestTransitionCurve)
{
public:
   TEST_METHOD(Test1)
   {
         // CCW (left) curves
         Float64 R1 = 0;
         Float64 R2 = 50;
         Float64 L = 100;

         CComPtr<ITransitionCurve> curve;
         ASSERT_EQ(curve.CoCreateInstance(CLSID_TransitionCurve),S_OK);
         ASSERT_EQ(curve->Init(nullptr, CComVariant(), R1, R2, L, Clothoid), S_OK);

         std::array<std::pair<Float64, Float64>,6> values1
         {
            std::make_pair(0.0, 0.0),
            std::make_pair(19.9968, 0.266636),
            std::make_pair(39.8977, 2.12944),
            std::make_pair(59.2271, 7.13362),
            std::make_pair(76.7848, 16.5738),
            std::make_pair(90.4523, 31.0268)
         };
         Verify(L, curve, values1);

         R1 = 300;
         std::array<std::pair<Float64, Float64>, 6> values2
         {
            std::make_pair(0,0),
            std::make_pair(19.9312,1.55332),
            std::make_pair(39.4645,5.73933),
            std::make_pair(57.7564,13.7137),
            std::make_pair(73.2775,26.2078),
            std::make_pair(83.8359,43.0612)
         };

         ASSERT_EQ(curve->Init(nullptr, CComVariant(), R1, R2, L, Clothoid), S_OK);
         Verify(L, curve, values2);

         // CW (right) curves
         R1 = 0;
         R2 = -50;
         ASSERT_EQ(curve->Init(nullptr, CComVariant(), R1, R2, L, Clothoid), S_OK);

         std::array<std::pair<Float64, Float64>, 6> values3
         {
            std::make_pair(0, 0),
            std::make_pair(19.9968, -0.266636),
            std::make_pair(39.8977, -2.12944),
            std::make_pair(59.2271, -7.13362),
            std::make_pair(76.7848, -16.5738),
            std::make_pair(90.4523, -31.0268)
         };
         Verify(L, curve, values3);

         R1 = -50;
         R2 = 0;
         ASSERT_EQ(curve->Init(nullptr, CComVariant(), R1, R2, L, Clothoid), S_OK);

         std::array<std::pair<Float64, Float64>, 6> values4
         {
            std::make_pair(0, 0),
            std::make_pair(19.5464, -3.69183),
            std::make_pair(36.9765, -13.3656),
            std::make_pair(51.6311, -26.9269),
            std::make_pair(63.9511, -42.6664),
            std::make_pair(74.9797, -59.3491)
         };
         Verify(L, curve, values4);

         // loop to dump values to screen
         //for (int i = 0; i <= 5; i++)
         //{
         //   Float64 s = i*L / 5.0;
         //   CComPtr<IPoint2d> p;
         //   curve->Point(s, &p);

         //   Float64 x, y;
         //   p->Location(&x, &y);

         //   std::cout << x << "," << y << std::endl;
         //}

         ////////////////////////////////////
         // Test ISupportErrorInfo
         CComQIPtr<ISupportErrorInfo> eInfo(curve);
         ASSERT_EQ( eInfo != nullptr, true );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ITransitionCurve ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         // Test IObjectSafety
         ASSERT_EQ( TestIObjectSafety(CLSID_TransitionCurve,IID_ITransitionCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }

   TEST_METHOD(ObjectSafety)
   {
         ASSERT_EQ( TestIObjectSafety(CLSID_TransitionCurve,IID_ITransitionCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }
};
} // namespace CogoUnitTests