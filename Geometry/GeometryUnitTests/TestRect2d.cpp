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

// TestRect2d.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestRect2d.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestRect2d)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IRect2d> pRect;
         ASSERT_EQ(pRect.CoCreateInstance(CLSID_Rect2d),S_OK);

         // Test Basic Properties
         Float64 left,right,top,bottom;
         left = 10;
         top = 10;
         right = 20;
         bottom = 5;

         Float64 l,r,t,b;
         ASSERT_EQ(pRect->put_Left(left),S_OK);
         ASSERT_EQ(pRect->get_Left(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_Left(&l),S_OK);
         ASSERT_EQ(IsEqual(l,left),true);

         ASSERT_EQ(pRect->put_Top(top),S_OK);
         ASSERT_EQ(pRect->get_Top(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_Top(&t),S_OK);
         ASSERT_EQ(IsEqual(t,top),true);

         ASSERT_EQ(pRect->put_Right(right),S_OK);
         ASSERT_EQ(pRect->get_Right(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_Right(&r),S_OK);
         ASSERT_EQ(IsEqual(r,right),true);

         ASSERT_EQ(pRect->put_Bottom(bottom),S_OK);
         ASSERT_EQ(pRect->get_Bottom(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_Bottom(&b),S_OK);
         ASSERT_EQ(IsEqual(b,bottom),true);

         //
         // Test Derived Properties
         //

         // Height and Width
         Float64 w,h;
         ASSERT_EQ(pRect->get_Width(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_Width(&w),S_OK);
         ASSERT_EQ(IsEqual(w,right-left),true);

         ASSERT_EQ(pRect->get_Height(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_Height(&h),S_OK);
         ASSERT_EQ(IsEqual(h,top-bottom),true);

         // Area
         Float64 area;
         ASSERT_EQ(pRect->get_Area(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_Area(&area),S_OK);
         ASSERT_EQ(IsEqual(area,(right-left)*(top-bottom)),true);

         // Points
         // Make it an easy rectangle
         pRect->put_Left(-10);
         pRect->put_Right(10);
         pRect->put_Top(10);
         pRect->put_Bottom(-10);
         CComPtr<IPoint2d> pPoint;
         Float64 x,y;
         ASSERT_EQ(pRect->get_TopLeft(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_TopLeft(&pPoint),S_OK);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         ASSERT_EQ(IsEqual(x,-10.0),true);
         ASSERT_EQ(IsEqual(y, 10.0),true);

         pPoint.Release();
         ASSERT_EQ(pRect->get_TopCenter(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_TopCenter(&pPoint),S_OK);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         ASSERT_EQ(IsEqual(x,  0.0),true);
         ASSERT_EQ(IsEqual(y, 10.0),true);

         pPoint.Release();
         ASSERT_EQ(pRect->get_TopRight(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_TopRight(&pPoint),S_OK);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 10.0),true);
         ASSERT_EQ(IsEqual(y, 10.0),true);

         pPoint.Release();
         ASSERT_EQ(pRect->get_CenterLeft(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_CenterLeft(&pPoint),S_OK);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         ASSERT_EQ(IsEqual(x,-10.0),true);
         ASSERT_EQ(IsEqual(y,  0.0),true);

         pPoint.Release();
         ASSERT_EQ(pRect->get_CenterCenter(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_CenterCenter(&pPoint),S_OK);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         ASSERT_EQ(IsEqual(x,  0.0),true);
         ASSERT_EQ(IsEqual(y,  0.0),true);

         pPoint.Release();
         ASSERT_EQ(pRect->get_CenterRight(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_CenterRight(&pPoint),S_OK);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 10.0),true);
         ASSERT_EQ(IsEqual(y,  0.0),true);

         pPoint.Release();
         ASSERT_EQ(pRect->get_BottomLeft(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_BottomLeft(&pPoint),S_OK);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         ASSERT_EQ(IsEqual(x,-10.0),true);
         ASSERT_EQ(IsEqual(y,-10.0),true);

         pPoint.Release();
         ASSERT_EQ(pRect->get_BottomCenter(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_BottomCenter(&pPoint),S_OK);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         ASSERT_EQ(IsEqual(x,  0.0),true);
         ASSERT_EQ(IsEqual(y,-10.0),true);

         pPoint.Release();
         ASSERT_EQ(pRect->get_BottomRight(nullptr),E_POINTER);
         ASSERT_EQ(pRect->get_BottomRight(&pPoint),S_OK);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 10.0),true);
         ASSERT_EQ(IsEqual(y,-10.0),true);

         // Test ContainsPoint method
         pRect->put_Left(0);
         pRect->put_Right(10);
         pRect->put_Bottom(0);
         pRect->put_Top(10);
         pPoint->put_X(5);
         pPoint->put_Y(5);
         VARIANT_BOOL bContains;
         ASSERT_EQ(pRect->ContainsPoint(nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,nullptr),E_POINTER);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_TRUE);

         pPoint->put_X(50);
         pPoint->put_Y(50);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         // Test a point a the middle of each side and at each corner
         // (points on bottom and left sides are contained)
         pPoint->put_X(0);
         pPoint->put_Y(0);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_TRUE);

         pPoint->put_X(5);
         pPoint->put_Y(0);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_TRUE);

         pPoint->put_X(10);
         pPoint->put_Y(0);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         pPoint->put_X(10);
         pPoint->put_Y(5);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         pPoint->put_X(10);
         pPoint->put_Y(10);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         pPoint->put_X(5);
         pPoint->put_Y(10);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         pPoint->put_X(0);
         pPoint->put_Y(10);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         pPoint->put_X(0);
         pPoint->put_Y(5);
         ASSERT_EQ(pRect->ContainsPoint(pPoint,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_TRUE);

         //
         // Test ContainsRect and Touches
         //
         pRect->put_Left(0);
         pRect->put_Right(10);
         pRect->put_Bottom(0);
         pRect->put_Top(10);

         VARIANT_BOOL bTouches;
         CComPtr<IRect2d> pRect2;
         pRect2.CoCreateInstance(CLSID_Rect2d);
         pRect2->put_Left(20);
         pRect2->put_Right(30);
         pRect2->put_Top(10);
         pRect2->put_Bottom(0);

         ASSERT_EQ(pRect->ContainsRect(nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(pRect->ContainsRect(pRect2,nullptr),E_POINTER);
         ASSERT_EQ(pRect->ContainsRect(pRect2,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         ASSERT_EQ(pRect->Touches(nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(pRect->Touches(pRect2,nullptr),E_POINTER);
         ASSERT_EQ(pRect->Touches(pRect2,&bTouches),S_OK);
         ASSERT_EQ(bTouches,VARIANT_FALSE);

         // Boths rects are the same
         pRect2->put_Left(0);
         pRect2->put_Right(10);
         pRect2->put_Top(10);
         pRect2->put_Bottom(0);
         ASSERT_EQ(pRect->ContainsRect(pRect2,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_TRUE);

         ASSERT_EQ(pRect->Touches(pRect2,&bTouches),S_OK);
         ASSERT_EQ(bTouches,VARIANT_TRUE);

         pRect2->put_Left(2);
         pRect2->put_Right(8);
         pRect2->put_Top(8);
         pRect2->put_Bottom(2);
         ASSERT_EQ(pRect->ContainsRect(pRect2,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_TRUE);

         ASSERT_EQ(pRect->Touches(pRect2,&bTouches),S_OK);
         ASSERT_EQ(bTouches,VARIANT_TRUE);

         // Covers top right corner
         pRect2->put_Left(2);
         pRect2->put_Right(12);
         pRect2->put_Top(12);
         pRect2->put_Bottom(2);
         ASSERT_EQ(pRect->ContainsRect(pRect2,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         ASSERT_EQ(pRect->Touches(pRect2,&bTouches),S_OK);
         ASSERT_EQ(bTouches,VARIANT_TRUE);

         // Covers top left corner
         pRect2->put_Left(-2);
         pRect2->put_Right(8);
         pRect2->put_Top(12);
         pRect2->put_Bottom(2);
         ASSERT_EQ(pRect->ContainsRect(pRect2,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         ASSERT_EQ(pRect->Touches(pRect2,&bTouches),S_OK);
         ASSERT_EQ(bTouches,VARIANT_TRUE);

         // Covers bottom left corner
         pRect2->put_Left(-2);
         pRect2->put_Right(8);
         pRect2->put_Top(8);
         pRect2->put_Bottom(-2);
         ASSERT_EQ(pRect->ContainsRect(pRect2,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         ASSERT_EQ(pRect->Touches(pRect2,&bTouches),S_OK);
         ASSERT_EQ(bTouches,VARIANT_TRUE);

         // Covers bottom right corner
         pRect2->put_Left(2);
         pRect2->put_Right(12);
         pRect2->put_Top(8);
         pRect2->put_Bottom(-2);
         ASSERT_EQ(pRect->ContainsRect(pRect2,&bContains),S_OK);
         ASSERT_EQ(bContains,VARIANT_FALSE);

         ASSERT_EQ(pRect->Touches(pRect2,&bTouches),S_OK);
         ASSERT_EQ(bTouches,VARIANT_TRUE);

         // Test Normalize/IsNormalized Methods
         // Create a non-normalized rect
         pRect->put_Left(100);
         pRect->put_Right(0);
         pRect->put_Top(100);
         pRect->put_Bottom(0);
         VARIANT_BOOL bIsNormalized;
         ASSERT_EQ(pRect->IsNormalized(nullptr), E_POINTER);
         ASSERT_EQ(pRect->IsNormalized(&bIsNormalized),S_OK);
         ASSERT_EQ(bIsNormalized,VARIANT_FALSE);

         ASSERT_EQ(pRect->Normalize(),S_OK);
         ASSERT_EQ(pRect->IsNormalized(&bIsNormalized),S_OK);
         ASSERT_EQ(bIsNormalized,VARIANT_TRUE);
         pRect->get_Left(&l);
         pRect->get_Top(&t);
         pRect->get_Right(&r);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,  0.00),true);
         ASSERT_EQ(IsEqual(r,100.00),true);
         ASSERT_EQ(IsEqual(b,  0.00),true);
         ASSERT_EQ(IsEqual(t,100.00),true);

         pRect->put_Left(0);
         pRect->put_Right(100);
         pRect->put_Top(0);
         pRect->put_Bottom(100);
         ASSERT_EQ(pRect->IsNormalized(&bIsNormalized),S_OK);
         ASSERT_EQ(bIsNormalized,VARIANT_FALSE);

         ASSERT_EQ(pRect->Normalize(),S_OK);
         ASSERT_EQ(pRect->IsNormalized(&bIsNormalized),S_OK);
         ASSERT_EQ(bIsNormalized,VARIANT_TRUE);
         pRect->get_Left(&l);
         pRect->get_Top(&t);
         pRect->get_Right(&r);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,  0.00),true);
         ASSERT_EQ(IsEqual(r,100.00),true);
         ASSERT_EQ(IsEqual(b,  0.00),true);
         ASSERT_EQ(IsEqual(t,100.00),true);

         //
         // Test SetNull/SetEmpty/IsNull methods
         //
         pRect->put_Left(0);
         pRect->put_Right(100);
         pRect->put_Top(100);
         pRect->put_Bottom(0);
         VARIANT_BOOL bIsNull;
         ASSERT_EQ(pRect->IsNull(nullptr),E_POINTER);
         ASSERT_EQ(pRect->IsNull(&bIsNull),S_OK);
         ASSERT_EQ(bIsNull,VARIANT_FALSE);

         pRect->SetNull();
         ASSERT_EQ(pRect->IsNull(&bIsNull),S_OK);
         ASSERT_EQ(bIsNull,VARIANT_TRUE);

         pRect->put_Left(0);
         pRect->put_Right(100);
         pRect->put_Top(100);
         pRect->put_Bottom(0);
         pRect->SetEmpty();
         ASSERT_EQ(pRect->IsNull(&bIsNull),S_OK);
         ASSERT_EQ(bIsNull,VARIANT_TRUE);

         pRect->get_Left(&l);
         pRect->get_Top(&t);
         pRect->get_Right(&r);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,0.00),true);
         ASSERT_EQ(IsEqual(r,0.00),true);
         ASSERT_EQ(IsEqual(b,0.00),true);
         ASSERT_EQ(IsEqual(t,0.00),true); 

         //
         // Test the Union method
         //
         pRect->put_Left(0);
         pRect->put_Top(10);
         pRect->put_Right(10);
         pRect->put_Bottom(0);

         // Rect2 is to the left
         pRect2->put_Left(20);
         pRect2->put_Right(30);
         pRect2->put_Top(10);
         pRect2->put_Bottom(0);

         ASSERT_EQ(pRect->Union(nullptr),E_INVALIDARG);

         ASSERT_EQ(pRect->Union(pRect2),S_OK);
         pRect->get_Left(&l);
         pRect->get_Right(&r);
         pRect->get_Top(&t);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l, 0.00),true);
         ASSERT_EQ(IsEqual(r,30.00),true);
         ASSERT_EQ(IsEqual(t,10.00),true);
         ASSERT_EQ(IsEqual(b, 0.00),true);

         // reset Rect
         pRect->put_Left(0);
         pRect->put_Top(10);
         pRect->put_Right(10);
         pRect->put_Bottom(0);

         //Rect2 is to the right
         pRect2->put_Left(-30);
         pRect2->put_Right(-20);
         pRect2->put_Top(10);
         pRect2->put_Bottom(0);

         ASSERT_EQ(pRect->Union(pRect2),S_OK);
         pRect->get_Left(&l);
         pRect->get_Right(&r);
         pRect->get_Top(&t);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,-30.00),true);
         ASSERT_EQ(IsEqual(r, 10.00),true);
         ASSERT_EQ(IsEqual(t, 10.00),true);
         ASSERT_EQ(IsEqual(b,  0.00),true);

         // reset Rect
         pRect->put_Left(0);
         pRect->put_Top(10);
         pRect->put_Right(10);
         pRect->put_Bottom(0);

         //Rect2 is above
         pRect2->put_Left(0);
         pRect2->put_Right(10);
         pRect2->put_Top(30);
         pRect2->put_Bottom(20);

         ASSERT_EQ(pRect->Union(pRect2),S_OK);
         pRect->get_Left(&l);
         pRect->get_Right(&r);
         pRect->get_Top(&t);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l, 0.00),true);
         ASSERT_EQ(IsEqual(r,10.00),true);
         ASSERT_EQ(IsEqual(t,30.00),true);
         ASSERT_EQ(IsEqual(b, 0.00),true);

         // reset Rect
         pRect->put_Left(0);
         pRect->put_Top(10);
         pRect->put_Right(10);
         pRect->put_Bottom(0);

         //Rect2 is below
         pRect2->put_Left(0);
         pRect2->put_Right(10);
         pRect2->put_Top(-20);
         pRect2->put_Bottom(-30);

         ASSERT_EQ(pRect->Union(pRect2),S_OK);
         pRect->get_Left(&l);
         pRect->get_Right(&r);
         pRect->get_Top(&t);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,  0.00),true);
         ASSERT_EQ(IsEqual(r, 10.00),true);
         ASSERT_EQ(IsEqual(t, 10.00),true);
         ASSERT_EQ(IsEqual(b,-30.00),true);

         // pRect is not normalized
         pRect->put_Left(10);
         pRect->put_Top(10);
         pRect->put_Right(0);
         pRect->put_Bottom(0);

         pRect2->put_Left(10);
         pRect2->put_Top(20);
         pRect2->put_Bottom(10);
         pRect2->put_Right(20);

         ASSERT_EQ(pRect->Union(pRect2),GEOMETRY_E_NOTNORMALIZED);

         // pRect2 is not normalized
         pRect->put_Left(0);
         pRect->put_Top(10);
         pRect->put_Right(10);
         pRect->put_Bottom(0);

         pRect2->put_Left(20);
         pRect2->put_Top(20);
         pRect2->put_Bottom(10);
         pRect2->put_Right(10);

         ASSERT_EQ(pRect->Union(pRect2),GEOMETRY_E_NOTNORMALIZED);

         //
         // Test the UnionBy method
         //
         CComPtr<IRect2d> pUnion;

         pRect->put_Left(0);
         pRect->put_Top(10);
         pRect->put_Right(10);
         pRect->put_Bottom(0);

         // Rect2 is to the left
         pRect2->put_Left(20);
         pRect2->put_Right(30);
         pRect2->put_Top(10);
         pRect2->put_Bottom(0);

         ASSERT_EQ(pRect->UnionBy(nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(pRect->UnionBy(pRect2,nullptr),E_POINTER);

         ASSERT_EQ(pRect->UnionBy(pRect2,&pUnion),S_OK);
         pUnion->get_Left(&l);
         pUnion->get_Right(&r);
         pUnion->get_Top(&t);
         pUnion->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l, 0.00),true);
         ASSERT_EQ(IsEqual(r,30.00),true);
         ASSERT_EQ(IsEqual(t,10.00),true);
         ASSERT_EQ(IsEqual(b, 0.00),true);

         //Rect2 is to the right
         pRect2->put_Left(-30);
         pRect2->put_Right(-20);
         pRect2->put_Top(10);
         pRect2->put_Bottom(0);

         pUnion.Release();

         ASSERT_EQ(pRect->UnionBy(pRect2,&pUnion),S_OK);
         pUnion->get_Left(&l);
         pUnion->get_Right(&r);
         pUnion->get_Top(&t);
         pUnion->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,-30.00),true);
         ASSERT_EQ(IsEqual(r, 10.00),true);
         ASSERT_EQ(IsEqual(t, 10.00),true);
         ASSERT_EQ(IsEqual(b,  0.00),true);

         //Rect2 is above
         pRect2->put_Left(0);
         pRect2->put_Right(10);
         pRect2->put_Top(30);
         pRect2->put_Bottom(20);

         pUnion.Release();

         ASSERT_EQ(pRect->UnionBy(pRect2,&pUnion),S_OK);
         pUnion->get_Left(&l);
         pUnion->get_Right(&r);
         pUnion->get_Top(&t);
         pUnion->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l, 0.00),true);
         ASSERT_EQ(IsEqual(r,10.00),true);
         ASSERT_EQ(IsEqual(t,30.00),true);
         ASSERT_EQ(IsEqual(b, 0.00),true);

         //Rect2 is below
         pRect2->put_Left(0);
         pRect2->put_Right(10);
         pRect2->put_Top(-20);
         pRect2->put_Bottom(-30);

         pUnion.Release();

         ASSERT_EQ(pRect->UnionBy(pRect2,&pUnion),S_OK);
         pUnion->get_Left(&l);
         pUnion->get_Right(&r);
         pUnion->get_Top(&t);
         pUnion->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,  0.00),true);
         ASSERT_EQ(IsEqual(r, 10.00),true);
         ASSERT_EQ(IsEqual(t, 10.00),true);
         ASSERT_EQ(IsEqual(b,-30.00),true);

         // pRect is not normalized
         pRect->put_Left(10);
         pRect->put_Top(10);
         pRect->put_Right(0);
         pRect->put_Bottom(0);

         pRect2->put_Left(10);
         pRect2->put_Top(20);
         pRect2->put_Bottom(10);
         pRect2->put_Right(20);

         pUnion.Release();
         ASSERT_EQ(pRect->UnionBy(pRect2,&pUnion),GEOMETRY_E_NOTNORMALIZED);

         // pRect2 is not normalized
         pRect->put_Left(0);
         pRect->put_Top(10);
         pRect->put_Right(10);
         pRect->put_Bottom(0);

         pRect2->put_Left(20);
         pRect2->put_Top(20);
         pRect2->put_Bottom(10);
         pRect2->put_Right(10);

         pUnion.Release();
         ASSERT_EQ(pRect->UnionBy(pRect2,&pUnion),GEOMETRY_E_NOTNORMALIZED);

         //
         // Test BoundPoint and BoundPointEx
         //
         pRect->put_Left(0);
         pRect->put_Right(10);
         pRect->put_Top(10);
         pRect->put_Bottom(0);

         pPoint->put_X(20);
         pPoint->put_Y(20);
         ASSERT_EQ(pRect->BoundPointEx(nullptr),E_INVALIDARG);
         ASSERT_EQ(pRect->BoundPointEx(pPoint),S_OK); // Grow left and up
         ASSERT_EQ(pRect->BoundPoint(-10,-10), S_OK); // Grow right and down
         pRect->get_Left(&l);
         pRect->get_Right(&r);
         pRect->get_Top(&t);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,-10.00),true);
         ASSERT_EQ(IsEqual(r, 20.00),true);
         ASSERT_EQ(IsEqual(t, 20.00),true);
         ASSERT_EQ(IsEqual(b,-10.00),true);

         // pRect is not normalized
         pRect->put_Left(10);
         pRect->put_Right(0);
         pRect->put_Top(10);
         pRect->put_Bottom(0);
         ASSERT_EQ(pRect->BoundPoint(-10,-10),GEOMETRY_E_NOTNORMALIZED);

         // make sure pRect didn't change
         pRect->get_Left(&l);
         pRect->get_Right(&r);
         pRect->get_Top(&t);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,10.00),true);
         ASSERT_EQ(IsEqual(r, 0.00),true);
         ASSERT_EQ(IsEqual(t,10.00),true);
         ASSERT_EQ(IsEqual(b, 0.00),true);

         //
         // Test Inflate and InflateEx
         //
         pRect->put_Left(0);
         pRect->put_Right(10);
         pRect->put_Top(10);
         pRect->put_Bottom(0);

         CComPtr<ISize2d> pInflate;
         pInflate.CoCreateInstance(CLSID_Size2d);
         pInflate->put_Dx(10);
         pInflate->put_Dy(10);

         ASSERT_EQ(pRect->InflateEx(nullptr),E_INVALIDARG);
         ASSERT_EQ(pRect->InflateEx(pInflate),S_OK);
         pRect->get_Left(&l);
         pRect->get_Right(&r);
         pRect->get_Top(&t);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,-10.00),true);
         ASSERT_EQ(IsEqual(r, 20.00),true);
         ASSERT_EQ(IsEqual(t, 20.00),true);
         ASSERT_EQ(IsEqual(b,-10.00),true);

         ASSERT_EQ(pRect->Inflate(-10,-10),S_OK);
         pRect->get_Left(&l);
         pRect->get_Right(&r);
         pRect->get_Top(&t);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l, 0.00),true);
         ASSERT_EQ(IsEqual(r,10.00),true);
         ASSERT_EQ(IsEqual(t,10.00),true);
         ASSERT_EQ(IsEqual(b, 0.00),true);

         //
         // Test Size method
         //
         pRect->put_Left(0);
         pRect->put_Right(10);
         pRect->put_Top(10);
         pRect->put_Bottom(0);

         CComPtr<ISize2d> pSize;
         ASSERT_EQ(pRect->Size(nullptr),E_POINTER);
         ASSERT_EQ(pRect->Size(&pSize),S_OK);
         Float64 dx,dy;
         pSize->get_Dx(&dx);
         pSize->get_Dy(&dy);
         ASSERT_EQ(IsEqual(dx,10.0),true);
         ASSERT_EQ(IsEqual(dy,10.0),true);

         pRect->put_Left(10);
         pRect->put_Right(0);
         pRect->put_Top(0);
         pRect->put_Bottom(10);

         pSize.Release();
         ASSERT_EQ(pRect->Size(&pSize),S_OK);
         pSize->get_Dx(&dx);
         pSize->get_Dy(&dy);
         ASSERT_EQ(IsEqual(dx,-10.0),true);
         ASSERT_EQ(IsEqual(dy,-10.0),true);

         //
         // Test Offset and OffsetEx
         //
         pRect->put_Left(0);
         pRect->put_Right(10);
         pRect->put_Top(10);
         pRect->put_Bottom(0);

         CComPtr<ISize2d> pOffset;
         pOffset.CoCreateInstance(CLSID_Size2d);
         pOffset->put_Dx(10);
         pOffset->put_Dy(10);

         ASSERT_EQ(pRect->OffsetEx(nullptr),E_INVALIDARG);
         ASSERT_EQ(pRect->OffsetEx(pOffset),S_OK);
         pRect->get_Left(&l);
         pRect->get_Right(&r);
         pRect->get_Top(&t);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,10.00),true);
         ASSERT_EQ(IsEqual(r,20.00),true);
         ASSERT_EQ(IsEqual(t,20.00),true);
         ASSERT_EQ(IsEqual(b,10.00),true);

         ASSERT_EQ(pRect->Offset(20,20),S_OK);
         pRect->get_Left(&l);
         pRect->get_Right(&r);
         pRect->get_Top(&t);
         pRect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,30.00),true);
         ASSERT_EQ(IsEqual(r,40.00),true);
         ASSERT_EQ(IsEqual(t,40.00),true);
         ASSERT_EQ(IsEqual(b,30.00),true);

         //
         // Test Intersect
         //
         pRect->put_Left(0);
         pRect->put_Top(10);
         pRect->put_Bottom(0);
         pRect->put_Right(10);


         CComPtr<IRect2d> pIntersect;
         ASSERT_EQ(pRect->Intersect(nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(pRect->Intersect(pRect2,nullptr),E_POINTER);

         // Rectangles don't intersect

         pRect2.Release();
         pRect2.CoCreateInstance(CLSID_Rect2d);
         pRect2->put_Left(25);
         pRect2->put_Top(15);
         pRect2->put_Bottom(5);
         pRect2->put_Right(35);

         pIntersect.Release();

         ASSERT_EQ(pRect->Intersect(pRect2,&pIntersect),S_OK);
         pIntersect->get_Left(&l);
         pIntersect->get_Right(&r);
         pIntersect->get_Top(&t);
         pIntersect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,0.0), true);
         ASSERT_EQ(IsEqual(t,0.0),true);
         ASSERT_EQ(IsEqual(r,0.0),true);
         ASSERT_EQ(IsEqual(b,0.0), true);

         // Basic intersection
         pRect2->put_Left(5);
         pRect2->put_Top(15);
         pRect2->put_Bottom(5);
         pRect2->put_Right(15);

         pIntersect.Release();

         ASSERT_EQ(pRect->Intersect(pRect2,&pIntersect),S_OK);
         pIntersect->get_Left(&l);
         pIntersect->get_Right(&r);
         pIntersect->get_Top(&t);
         pIntersect->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,5.0), true);
         ASSERT_EQ(IsEqual(t,10.0),true);
         ASSERT_EQ(IsEqual(r,10.0),true);
         ASSERT_EQ(IsEqual(b,5.0), true);

         // pRect is not normalized
         pRect->put_Left(10);
         pRect->put_Top(10);
         pRect->put_Bottom(0);
         pRect->put_Right(0);

         pRect2->put_Left(5);
         pRect2->put_Top(15);
         pRect2->put_Bottom(5);
         pRect2->put_Right(15);

         pIntersect.Release();

         ASSERT_EQ(pRect->Intersect(pRect2,&pIntersect),GEOMETRY_E_NOTNORMALIZED);

         // pRect2 is not normalized
         pRect->put_Left(0);
         pRect->put_Top(10);
         pRect->put_Bottom(0);
         pRect->put_Right(10);

         pRect2->put_Left(15);
         pRect2->put_Top(15);
         pRect2->put_Bottom(5);
         pRect2->put_Right(5);

         pIntersect.Release();

         ASSERT_EQ(pRect->Intersect(pRect2,&pIntersect),GEOMETRY_E_NOTNORMALIZED);
   }

   TEST_METHOD(SupportsErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_Rect2d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IRect2d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests