///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// GeometryTestUtil.h
//
// Shared test infrastructure for the GeometryUnitTests suite. This is the
// CppUnitTestFramework analogue of the legacy Geometry\GeometryTest\StdAfx.h:
// - ASSERT_EQ is the CppUnitTestFramework equivalent of the old TRY_TEST(x,y)
//   macro (see WBFLTest.h), preserving the same semantics: TRY_TEST(x,y)
//   compared x==y, so ASSERT_EQ does the same rather than relying on
//   Assert::AreEqual's type-specific overloads (several of the COM enum/
//   HRESULT types used here have no ToString<T> specialization).
// - TEST_POINT and TestIObjectSafety are ported unchanged from StdAfx.h.

#pragma once

// ASSERT_EQ(actual,expected) mirrors the legacy TRY_TEST(x,y) macro: it compares
// with operator== rather than Assert::AreEqual, since several COM enum/typedef
// types used throughout these tests don't have a CppUnitTestFramework
// ToString<T> specialization.
#define ASSERT_EQ(actual, expected) Assert::IsTrue((actual) == (expected), L#actual L" != " L#expected)

// ASSERT_TRUE(x) mirrors the legacy TRY_TEST(x,true) idiom used throughout
// GeometryTest (typically wrapping an IsEqual(...) comparison).
#define ASSERT_TRUE(expr) Assert::IsTrue((expr), L#expr)

// Ported unchanged from StdAfx.h.
#define TEST_POINT(_point_,_x_,_y_) _point_[i]->get_X(&x); _point_[i++]->get_Y(&y); ASSERT_TRUE(IsEqual(x,_x_)); ASSERT_TRUE(IsEqual(y,_y_));

// Ported unchanged from StdAfx.h (was `inline` there since it lived in a
// header included by every translation unit; same effect here).
inline bool TestIObjectSafety(REFCLSID rclsid, REFIID riid, DWORD dwSupportedOptions)
{
   CComPtr<IObjectSafety> safety;
   safety.CoCreateInstance(rclsid);

   if (safety == nullptr)
      return false;

   DWORD dwSupported, dwEnabled;
   safety->GetInterfaceSafetyOptions(riid, &dwSupported, &dwEnabled);
   return dwSupported == dwSupportedOptions;
}
