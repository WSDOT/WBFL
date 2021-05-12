///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// TestRect2d.cpp: implementation of the CTestRect2d class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestRect2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestRect2d::CTestRect2d()
{

}

CTestRect2d::~CTestRect2d()
{

}

void CTestRect2d::Test()
{
   CComPtr<IRect2d> pRect;
   TRY_TEST(pRect.CoCreateInstance(CLSID_Rect2d),S_OK);

   // Test Basic Properties
   Float64 left,right,top,bottom;
   left = 10;
   top = 10;
   right = 20;
   bottom = 5;

   Float64 l,r,t,b;
   TRY_TEST(pRect->put_Left(left),S_OK);
   TRY_TEST(pRect->get_Left(nullptr),E_POINTER);
   TRY_TEST(pRect->get_Left(&l),S_OK);
   TRY_TEST(IsEqual(l,left),true);

   TRY_TEST(pRect->put_Top(top),S_OK);
   TRY_TEST(pRect->get_Top(nullptr),E_POINTER);
   TRY_TEST(pRect->get_Top(&t),S_OK);
   TRY_TEST(IsEqual(t,top),true);

   TRY_TEST(pRect->put_Right(right),S_OK);
   TRY_TEST(pRect->get_Right(nullptr),E_POINTER);
   TRY_TEST(pRect->get_Right(&r),S_OK);
   TRY_TEST(IsEqual(r,right),true);

   TRY_TEST(pRect->put_Bottom(bottom),S_OK);
   TRY_TEST(pRect->get_Bottom(nullptr),E_POINTER);
   TRY_TEST(pRect->get_Bottom(&b),S_OK);
   TRY_TEST(IsEqual(b,bottom),true);

   //
   // Test Derived Properties
   //

   // Height and Width
   Float64 w,h;
   TRY_TEST(pRect->get_Width(nullptr),E_POINTER);
   TRY_TEST(pRect->get_Width(&w),S_OK);
   TRY_TEST(IsEqual(w,right-left),true);

   TRY_TEST(pRect->get_Height(nullptr),E_POINTER);
   TRY_TEST(pRect->get_Height(&h),S_OK);
   TRY_TEST(IsEqual(h,top-bottom),true);

   // Area
   Float64 area;
   TRY_TEST(pRect->get_Area(nullptr),E_POINTER);
   TRY_TEST(pRect->get_Area(&area),S_OK);
   TRY_TEST(IsEqual(area,(right-left)*(top-bottom)),true);

   // Points
   // Make it an easy rectangle
   pRect->put_Left(-10);
   pRect->put_Right(10);
   pRect->put_Top(10);
   pRect->put_Bottom(-10);
   CComPtr<IPoint2d> pPoint;
   Float64 x,y;
   TRY_TEST(pRect->get_TopLeft(nullptr),E_POINTER);
   TRY_TEST(pRect->get_TopLeft(&pPoint),S_OK);
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   TRY_TEST(IsEqual(x,-10.0),true);
   TRY_TEST(IsEqual(y, 10.0),true);

   pPoint.Release();
   TRY_TEST(pRect->get_TopCenter(nullptr),E_POINTER);
   TRY_TEST(pRect->get_TopCenter(&pPoint),S_OK);
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   TRY_TEST(IsEqual(x,  0.0),true);
   TRY_TEST(IsEqual(y, 10.0),true);

   pPoint.Release();
   TRY_TEST(pRect->get_TopRight(nullptr),E_POINTER);
   TRY_TEST(pRect->get_TopRight(&pPoint),S_OK);
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   TRY_TEST(IsEqual(x, 10.0),true);
   TRY_TEST(IsEqual(y, 10.0),true);

   pPoint.Release();
   TRY_TEST(pRect->get_CenterLeft(nullptr),E_POINTER);
   TRY_TEST(pRect->get_CenterLeft(&pPoint),S_OK);
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   TRY_TEST(IsEqual(x,-10.0),true);
   TRY_TEST(IsEqual(y,  0.0),true);

   pPoint.Release();
   TRY_TEST(pRect->get_CenterCenter(nullptr),E_POINTER);
   TRY_TEST(pRect->get_CenterCenter(&pPoint),S_OK);
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   TRY_TEST(IsEqual(x,  0.0),true);
   TRY_TEST(IsEqual(y,  0.0),true);

   pPoint.Release();
   TRY_TEST(pRect->get_CenterRight(nullptr),E_POINTER);
   TRY_TEST(pRect->get_CenterRight(&pPoint),S_OK);
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   TRY_TEST(IsEqual(x, 10.0),true);
   TRY_TEST(IsEqual(y,  0.0),true);

   pPoint.Release();
   TRY_TEST(pRect->get_BottomLeft(nullptr),E_POINTER);
   TRY_TEST(pRect->get_BottomLeft(&pPoint),S_OK);
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   TRY_TEST(IsEqual(x,-10.0),true);
   TRY_TEST(IsEqual(y,-10.0),true);

   pPoint.Release();
   TRY_TEST(pRect->get_BottomCenter(nullptr),E_POINTER);
   TRY_TEST(pRect->get_BottomCenter(&pPoint),S_OK);
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   TRY_TEST(IsEqual(x,  0.0),true);
   TRY_TEST(IsEqual(y,-10.0),true);

   pPoint.Release();
   TRY_TEST(pRect->get_BottomRight(nullptr),E_POINTER);
   TRY_TEST(pRect->get_BottomRight(&pPoint),S_OK);
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   TRY_TEST(IsEqual(x, 10.0),true);
   TRY_TEST(IsEqual(y,-10.0),true);

   // Test ContainsPoint method
   pRect->put_Left(0);
   pRect->put_Right(10);
   pRect->put_Bottom(0);
   pRect->put_Top(10);
   pPoint->put_X(5);
   pPoint->put_Y(5);
   VARIANT_BOOL bContains;
   TRY_TEST(pRect->ContainsPoint(nullptr,nullptr),E_INVALIDARG);
   TRY_TEST(pRect->ContainsPoint(pPoint,nullptr),E_POINTER);
   TRY_TEST(pRect->ContainsPoint(pPoint,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_TRUE);

   pPoint->put_X(50);
   pPoint->put_Y(50);
   TRY_TEST(pRect->ContainsPoint(pPoint,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   // Test a point a the middle of each side and at each corner
   // (points on bottom and left sides are contained)
   pPoint->put_X(0);
   pPoint->put_Y(0);
   TRY_TEST(pRect->ContainsPoint(pPoint,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_TRUE);

   pPoint->put_X(5);
   pPoint->put_Y(0);
   TRY_TEST(pRect->ContainsPoint(pPoint,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_TRUE);

   pPoint->put_X(10);
   pPoint->put_Y(0);
   TRY_TEST(pRect->ContainsPoint(pPoint,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   pPoint->put_X(10);
   pPoint->put_Y(5);
   TRY_TEST(pRect->ContainsPoint(pPoint,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   pPoint->put_X(10);
   pPoint->put_Y(10);
   TRY_TEST(pRect->ContainsPoint(pPoint,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   pPoint->put_X(5);
   pPoint->put_Y(10);
   TRY_TEST(pRect->ContainsPoint(pPoint,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   pPoint->put_X(0);
   pPoint->put_Y(10);
   TRY_TEST(pRect->ContainsPoint(pPoint,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   pPoint->put_X(0);
   pPoint->put_Y(5);
   TRY_TEST(pRect->ContainsPoint(pPoint,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_TRUE);

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

   TRY_TEST(pRect->ContainsRect(nullptr,nullptr),E_INVALIDARG);
   TRY_TEST(pRect->ContainsRect(pRect2,nullptr),E_POINTER);
   TRY_TEST(pRect->ContainsRect(pRect2,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   TRY_TEST(pRect->Touches(nullptr,nullptr),E_INVALIDARG);
   TRY_TEST(pRect->Touches(pRect2,nullptr),E_POINTER);
   TRY_TEST(pRect->Touches(pRect2,&bTouches),S_OK);
   TRY_TEST(bTouches,VARIANT_FALSE);

   // Boths rects are the same
   pRect2->put_Left(0);
   pRect2->put_Right(10);
   pRect2->put_Top(10);
   pRect2->put_Bottom(0);
   TRY_TEST(pRect->ContainsRect(pRect2,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_TRUE);

   TRY_TEST(pRect->Touches(pRect2,&bTouches),S_OK);
   TRY_TEST(bTouches,VARIANT_TRUE);

   pRect2->put_Left(2);
   pRect2->put_Right(8);
   pRect2->put_Top(8);
   pRect2->put_Bottom(2);
   TRY_TEST(pRect->ContainsRect(pRect2,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_TRUE);

   TRY_TEST(pRect->Touches(pRect2,&bTouches),S_OK);
   TRY_TEST(bTouches,VARIANT_TRUE);

   // Covers top right corner
   pRect2->put_Left(2);
   pRect2->put_Right(12);
   pRect2->put_Top(12);
   pRect2->put_Bottom(2);
   TRY_TEST(pRect->ContainsRect(pRect2,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   TRY_TEST(pRect->Touches(pRect2,&bTouches),S_OK);
   TRY_TEST(bTouches,VARIANT_TRUE);

   // Covers top left corner
   pRect2->put_Left(-2);
   pRect2->put_Right(8);
   pRect2->put_Top(12);
   pRect2->put_Bottom(2);
   TRY_TEST(pRect->ContainsRect(pRect2,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   TRY_TEST(pRect->Touches(pRect2,&bTouches),S_OK);
   TRY_TEST(bTouches,VARIANT_TRUE);

   // Covers bottom left corner
   pRect2->put_Left(-2);
   pRect2->put_Right(8);
   pRect2->put_Top(8);
   pRect2->put_Bottom(-2);
   TRY_TEST(pRect->ContainsRect(pRect2,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   TRY_TEST(pRect->Touches(pRect2,&bTouches),S_OK);
   TRY_TEST(bTouches,VARIANT_TRUE);

   // Covers bottom right corner
   pRect2->put_Left(2);
   pRect2->put_Right(12);
   pRect2->put_Top(8);
   pRect2->put_Bottom(-2);
   TRY_TEST(pRect->ContainsRect(pRect2,&bContains),S_OK);
   TRY_TEST(bContains,VARIANT_FALSE);

   TRY_TEST(pRect->Touches(pRect2,&bTouches),S_OK);
   TRY_TEST(bTouches,VARIANT_TRUE);

   // Test Normalize/IsNormalized Methods
   // Create a non-normalized rect
   pRect->put_Left(100);
   pRect->put_Right(0);
   pRect->put_Top(100);
   pRect->put_Bottom(0);
   VARIANT_BOOL bIsNormalized;
   TRY_TEST(pRect->IsNormalized(nullptr), E_POINTER);
   TRY_TEST(pRect->IsNormalized(&bIsNormalized),S_OK);
   TRY_TEST(bIsNormalized,VARIANT_FALSE);

   TRY_TEST(pRect->Normalize(),S_OK);
   TRY_TEST(pRect->IsNormalized(&bIsNormalized),S_OK);
   TRY_TEST(bIsNormalized,VARIANT_TRUE);
   pRect->get_Left(&l);
   pRect->get_Top(&t);
   pRect->get_Right(&r);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,  0.00),true);
   TRY_TEST(IsEqual(r,100.00),true);
   TRY_TEST(IsEqual(b,  0.00),true);
   TRY_TEST(IsEqual(t,100.00),true);

   pRect->put_Left(0);
   pRect->put_Right(100);
   pRect->put_Top(0);
   pRect->put_Bottom(100);
   TRY_TEST(pRect->IsNormalized(&bIsNormalized),S_OK);
   TRY_TEST(bIsNormalized,VARIANT_FALSE);

   TRY_TEST(pRect->Normalize(),S_OK);
   TRY_TEST(pRect->IsNormalized(&bIsNormalized),S_OK);
   TRY_TEST(bIsNormalized,VARIANT_TRUE);
   pRect->get_Left(&l);
   pRect->get_Top(&t);
   pRect->get_Right(&r);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,  0.00),true);
   TRY_TEST(IsEqual(r,100.00),true);
   TRY_TEST(IsEqual(b,  0.00),true);
   TRY_TEST(IsEqual(t,100.00),true);

   //
   // Test SetNull/SetEmpty/IsNull methods
   //
   pRect->put_Left(0);
   pRect->put_Right(100);
   pRect->put_Top(100);
   pRect->put_Bottom(0);
   VARIANT_BOOL bIsNull;
   TRY_TEST(pRect->IsNull(nullptr),E_POINTER);
   TRY_TEST(pRect->IsNull(&bIsNull),S_OK);
   TRY_TEST(bIsNull,VARIANT_FALSE);

   pRect->SetNull();
   TRY_TEST(pRect->IsNull(&bIsNull),S_OK);
   TRY_TEST(bIsNull,VARIANT_TRUE);

   pRect->put_Left(0);
   pRect->put_Right(100);
   pRect->put_Top(100);
   pRect->put_Bottom(0);
   pRect->SetEmpty();
   TRY_TEST(pRect->IsNull(&bIsNull),S_OK);
   TRY_TEST(bIsNull,VARIANT_TRUE);

   pRect->get_Left(&l);
   pRect->get_Top(&t);
   pRect->get_Right(&r);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,0.00),true);
   TRY_TEST(IsEqual(r,0.00),true);
   TRY_TEST(IsEqual(b,0.00),true);
   TRY_TEST(IsEqual(t,0.00),true); 

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

   TRY_TEST(pRect->Union(nullptr),E_INVALIDARG);

   TRY_TEST(pRect->Union(pRect2),S_OK);
   pRect->get_Left(&l);
   pRect->get_Right(&r);
   pRect->get_Top(&t);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l, 0.00),true);
   TRY_TEST(IsEqual(r,30.00),true);
   TRY_TEST(IsEqual(t,10.00),true);
   TRY_TEST(IsEqual(b, 0.00),true);

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

   TRY_TEST(pRect->Union(pRect2),S_OK);
   pRect->get_Left(&l);
   pRect->get_Right(&r);
   pRect->get_Top(&t);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-30.00),true);
   TRY_TEST(IsEqual(r, 10.00),true);
   TRY_TEST(IsEqual(t, 10.00),true);
   TRY_TEST(IsEqual(b,  0.00),true);

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

   TRY_TEST(pRect->Union(pRect2),S_OK);
   pRect->get_Left(&l);
   pRect->get_Right(&r);
   pRect->get_Top(&t);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l, 0.00),true);
   TRY_TEST(IsEqual(r,10.00),true);
   TRY_TEST(IsEqual(t,30.00),true);
   TRY_TEST(IsEqual(b, 0.00),true);

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

   TRY_TEST(pRect->Union(pRect2),S_OK);
   pRect->get_Left(&l);
   pRect->get_Right(&r);
   pRect->get_Top(&t);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,  0.00),true);
   TRY_TEST(IsEqual(r, 10.00),true);
   TRY_TEST(IsEqual(t, 10.00),true);
   TRY_TEST(IsEqual(b,-30.00),true);

   // pRect is not normalized
   pRect->put_Left(10);
   pRect->put_Top(10);
   pRect->put_Right(0);
   pRect->put_Bottom(0);

   pRect2->put_Left(10);
   pRect2->put_Top(20);
   pRect2->put_Bottom(10);
   pRect2->put_Right(20);

   TRY_TEST(pRect->Union(pRect2),GEOMETRY_E_NOTNORMALIZED);
   
   // pRect2 is not normalized
   pRect->put_Left(0);
   pRect->put_Top(10);
   pRect->put_Right(10);
   pRect->put_Bottom(0);

   pRect2->put_Left(20);
   pRect2->put_Top(20);
   pRect2->put_Bottom(10);
   pRect2->put_Right(10);

   TRY_TEST(pRect->Union(pRect2),GEOMETRY_E_NOTNORMALIZED);

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

   TRY_TEST(pRect->UnionBy(nullptr,nullptr),E_INVALIDARG);
   TRY_TEST(pRect->UnionBy(pRect2,nullptr),E_POINTER);

   TRY_TEST(pRect->UnionBy(pRect2,&pUnion),S_OK);
   pUnion->get_Left(&l);
   pUnion->get_Right(&r);
   pUnion->get_Top(&t);
   pUnion->get_Bottom(&b);
   TRY_TEST(IsEqual(l, 0.00),true);
   TRY_TEST(IsEqual(r,30.00),true);
   TRY_TEST(IsEqual(t,10.00),true);
   TRY_TEST(IsEqual(b, 0.00),true);

   //Rect2 is to the right
   pRect2->put_Left(-30);
   pRect2->put_Right(-20);
   pRect2->put_Top(10);
   pRect2->put_Bottom(0);

   pUnion.Release();

   TRY_TEST(pRect->UnionBy(pRect2,&pUnion),S_OK);
   pUnion->get_Left(&l);
   pUnion->get_Right(&r);
   pUnion->get_Top(&t);
   pUnion->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-30.00),true);
   TRY_TEST(IsEqual(r, 10.00),true);
   TRY_TEST(IsEqual(t, 10.00),true);
   TRY_TEST(IsEqual(b,  0.00),true);

   //Rect2 is above
   pRect2->put_Left(0);
   pRect2->put_Right(10);
   pRect2->put_Top(30);
   pRect2->put_Bottom(20);

   pUnion.Release();

   TRY_TEST(pRect->UnionBy(pRect2,&pUnion),S_OK);
   pUnion->get_Left(&l);
   pUnion->get_Right(&r);
   pUnion->get_Top(&t);
   pUnion->get_Bottom(&b);
   TRY_TEST(IsEqual(l, 0.00),true);
   TRY_TEST(IsEqual(r,10.00),true);
   TRY_TEST(IsEqual(t,30.00),true);
   TRY_TEST(IsEqual(b, 0.00),true);

   //Rect2 is below
   pRect2->put_Left(0);
   pRect2->put_Right(10);
   pRect2->put_Top(-20);
   pRect2->put_Bottom(-30);

   pUnion.Release();

   TRY_TEST(pRect->UnionBy(pRect2,&pUnion),S_OK);
   pUnion->get_Left(&l);
   pUnion->get_Right(&r);
   pUnion->get_Top(&t);
   pUnion->get_Bottom(&b);
   TRY_TEST(IsEqual(l,  0.00),true);
   TRY_TEST(IsEqual(r, 10.00),true);
   TRY_TEST(IsEqual(t, 10.00),true);
   TRY_TEST(IsEqual(b,-30.00),true);

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
   TRY_TEST(pRect->UnionBy(pRect2,&pUnion),GEOMETRY_E_NOTNORMALIZED);
   
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
   TRY_TEST(pRect->UnionBy(pRect2,&pUnion),GEOMETRY_E_NOTNORMALIZED);

   //
   // Test BoundPoint and BoundPointEx
   //
   pRect->put_Left(0);
   pRect->put_Right(10);
   pRect->put_Top(10);
   pRect->put_Bottom(0);

   pPoint->put_X(20);
   pPoint->put_Y(20);
   TRY_TEST(pRect->BoundPointEx(nullptr),E_INVALIDARG);
   TRY_TEST(pRect->BoundPointEx(pPoint),S_OK); // Grow left and up
   TRY_TEST(pRect->BoundPoint(-10,-10), S_OK); // Grow right and down
   pRect->get_Left(&l);
   pRect->get_Right(&r);
   pRect->get_Top(&t);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-10.00),true);
   TRY_TEST(IsEqual(r, 20.00),true);
   TRY_TEST(IsEqual(t, 20.00),true);
   TRY_TEST(IsEqual(b,-10.00),true);

   // pRect is not normalized
   pRect->put_Left(10);
   pRect->put_Right(0);
   pRect->put_Top(10);
   pRect->put_Bottom(0);
   TRY_TEST(pRect->BoundPoint(-10,-10),GEOMETRY_E_NOTNORMALIZED);

   // make sure pRect didn't change
   pRect->get_Left(&l);
   pRect->get_Right(&r);
   pRect->get_Top(&t);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,10.00),true);
   TRY_TEST(IsEqual(r, 0.00),true);
   TRY_TEST(IsEqual(t,10.00),true);
   TRY_TEST(IsEqual(b, 0.00),true);

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

   TRY_TEST(pRect->InflateEx(nullptr),E_INVALIDARG);
   TRY_TEST(pRect->InflateEx(pInflate),S_OK);
   pRect->get_Left(&l);
   pRect->get_Right(&r);
   pRect->get_Top(&t);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-10.00),true);
   TRY_TEST(IsEqual(r, 20.00),true);
   TRY_TEST(IsEqual(t, 20.00),true);
   TRY_TEST(IsEqual(b,-10.00),true);

   TRY_TEST(pRect->Inflate(-10,-10),S_OK);
   pRect->get_Left(&l);
   pRect->get_Right(&r);
   pRect->get_Top(&t);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l, 0.00),true);
   TRY_TEST(IsEqual(r,10.00),true);
   TRY_TEST(IsEqual(t,10.00),true);
   TRY_TEST(IsEqual(b, 0.00),true);

   //
   // Test Size method
   //
   pRect->put_Left(0);
   pRect->put_Right(10);
   pRect->put_Top(10);
   pRect->put_Bottom(0);

   CComPtr<ISize2d> pSize;
   TRY_TEST(pRect->Size(nullptr),E_POINTER);
   TRY_TEST(pRect->Size(&pSize),S_OK);
   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);
   TRY_TEST(IsEqual(dx,10.0),true);
   TRY_TEST(IsEqual(dy,10.0),true);

   pRect->put_Left(10);
   pRect->put_Right(0);
   pRect->put_Top(0);
   pRect->put_Bottom(10);

   pSize.Release();
   TRY_TEST(pRect->Size(&pSize),S_OK);
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);
   TRY_TEST(IsEqual(dx,-10.0),true);
   TRY_TEST(IsEqual(dy,-10.0),true);

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

   TRY_TEST(pRect->OffsetEx(nullptr),E_INVALIDARG);
   TRY_TEST(pRect->OffsetEx(pOffset),S_OK);
   pRect->get_Left(&l);
   pRect->get_Right(&r);
   pRect->get_Top(&t);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,10.00),true);
   TRY_TEST(IsEqual(r,20.00),true);
   TRY_TEST(IsEqual(t,20.00),true);
   TRY_TEST(IsEqual(b,10.00),true);

   TRY_TEST(pRect->Offset(20,20),S_OK);
   pRect->get_Left(&l);
   pRect->get_Right(&r);
   pRect->get_Top(&t);
   pRect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,30.00),true);
   TRY_TEST(IsEqual(r,40.00),true);
   TRY_TEST(IsEqual(t,40.00),true);
   TRY_TEST(IsEqual(b,30.00),true);

   //
   // Test Intersect
   //
   pRect->put_Left(0);
   pRect->put_Top(10);
   pRect->put_Bottom(0);
   pRect->put_Right(10);


   CComPtr<IRect2d> pIntersect;
   TRY_TEST(pRect->Intersect(nullptr,nullptr),E_INVALIDARG);
   TRY_TEST(pRect->Intersect(pRect2,nullptr),E_POINTER);

   // Rectangles don't intersect

   pRect2.Release();
   pRect2.CoCreateInstance(CLSID_Rect2d);
   pRect2->put_Left(25);
   pRect2->put_Top(15);
   pRect2->put_Bottom(5);
   pRect2->put_Right(35);

   pIntersect.Release();
   
   TRY_TEST(pRect->Intersect(pRect2,&pIntersect),S_OK);
   pIntersect->get_Left(&l);
   pIntersect->get_Right(&r);
   pIntersect->get_Top(&t);
   pIntersect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,0.0), true);
   TRY_TEST(IsEqual(t,0.0),true);
   TRY_TEST(IsEqual(r,0.0),true);
   TRY_TEST(IsEqual(b,0.0), true);

   // Basic intersection
   pRect2->put_Left(5);
   pRect2->put_Top(15);
   pRect2->put_Bottom(5);
   pRect2->put_Right(15);

   pIntersect.Release();

   TRY_TEST(pRect->Intersect(pRect2,&pIntersect),S_OK);
   pIntersect->get_Left(&l);
   pIntersect->get_Right(&r);
   pIntersect->get_Top(&t);
   pIntersect->get_Bottom(&b);
   TRY_TEST(IsEqual(l,5.0), true);
   TRY_TEST(IsEqual(t,10.0),true);
   TRY_TEST(IsEqual(r,10.0),true);
   TRY_TEST(IsEqual(b,5.0), true);

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

   TRY_TEST(pRect->Intersect(pRect2,&pIntersect),GEOMETRY_E_NOTNORMALIZED);

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

   TRY_TEST(pRect->Intersect(pRect2,&pIntersect),GEOMETRY_E_NOTNORMALIZED);

   TestISupportErrorInfo();
}

void CTestRect2d::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_Rect2d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IRect2d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
