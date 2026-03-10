///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TestLine2d.cpp: implementation of the CTestLine2d class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestLine2d.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestLine2d::CTestLine2d()
{

}

CTestLine2d::~CTestLine2d()
{

}

void CTestLine2d::Test()
{
   CComPtr<ILine2d> pLine;
   TRY_TEST(pLine.CoCreateInstance( CLSID_Line2d ), S_OK );

   //
   // Test Set/GetExplicit
   //
   CComPtr<IVector2d> v;
   v.CoCreateInstance( CLSID_Vector2d );
   v->put_X(0);
   v->put_Y(0);

   CComPtr<IPoint2d> p;
   p.CoCreateInstance( CLSID_Point2d );
   p->put_X(5);
   p->put_Y(5);

   TRY_TEST( pLine->SetExplicit(nullptr,nullptr), E_INVALIDARG );
   TRY_TEST( pLine->SetExplicit(p,nullptr), E_INVALIDARG );
   TRY_TEST( pLine->SetExplicit(p,v), GEOMETRY_E_ZEROMAGNITUDE );

   v->put_X(10);
   v->put_Y(10);
   TRY_TEST( pLine->SetExplicit(p,v), S_OK );

   CComPtr<IVector2d> vec;
   CComPtr<IPoint2d>  pnt;
   TRY_TEST( pLine->GetExplicit(nullptr,nullptr), E_POINTER );
   TRY_TEST( pLine->GetExplicit(&pnt,nullptr), E_POINTER );
   TRY_TEST( pLine->GetExplicit(nullptr,&vec), E_POINTER );
   TRY_TEST( pLine->GetExplicit(&pnt,&vec), S_OK );
   
   Float64 x,y;
   // Check the point - It should be the point nearest the origin
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,0.0),true);
   TRY_TEST(IsEqual(y,0.0),true);
   // Check the vector - It should be a unit vector now
   vec->get_X(&x);
   vec->get_Y(&y);
   TRY_TEST(IsEqual(x,0.70710678),true);
   TRY_TEST(IsEqual(y,0.70710678),true);

   //
   // Test Set/GetImplicit
   //
   v->put_X(0);
   v->put_Y(0);
   TRY_TEST( pLine->SetImplicit(5.0,v), GEOMETRY_E_ZEROMAGNITUDE );

   v->put_X(0);
   v->put_Y(1);
   TRY_TEST(pLine->SetImplicit(5.0,nullptr),E_INVALIDARG);
   TRY_TEST(pLine->SetImplicit(5.0,v),S_OK);

   Float64 c;
   vec.Release();
   TRY_TEST(pLine->GetImplicit(nullptr,nullptr),E_POINTER);
   TRY_TEST(pLine->GetImplicit(&c,nullptr),E_POINTER);
   TRY_TEST(pLine->GetImplicit(nullptr,&vec),E_POINTER);
   TRY_TEST(pLine->GetImplicit(&c,&vec),S_OK);

   TRY_TEST(IsEqual(c,5.0),true);
   vec->get_X(&x);
   vec->get_Y(&y);
   TRY_TEST(IsEqual(x,0.0),true);
   TRY_TEST(IsEqual(y,1.0),true);

   //
   // Test ThroughPoints
   //
   CComPtr<IPoint2d> p1;
   CComPtr<IPoint2d> p2;
   p1.CoCreateInstance( CLSID_Point2d );
   p2.CoCreateInstance( CLSID_Point2d );
   p1->put_X(0.0);
   p1->put_Y(10.0);
   p2->put_X(20.0);
   p2->put_Y(30.0);
   TRY_TEST(pLine->ThroughPoints(nullptr,nullptr),E_INVALIDARG);
   TRY_TEST(pLine->ThroughPoints(p1,nullptr),E_INVALIDARG);
   TRY_TEST(pLine->ThroughPoints(p1,p2),S_OK);

   vec.Release();
   pLine->GetImplicit(&c,&vec);

   TRY_TEST(IsEqual(c,7.0710678),true);
   vec->get_X(&x);
   vec->get_Y(&y);
   TRY_TEST(IsEqual(x,-0.70710678),true);
   TRY_TEST(IsEqual(y, 0.70710678),true);

   pnt.Release();
   vec.Release();
   pLine->GetExplicit(&pnt,&vec);

   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-5.0),true);
   TRY_TEST(IsEqual(y, 5.0),true);
   vec->get_X(&x);
   vec->get_Y(&y);
   TRY_TEST(IsEqual(x,0.70710678),true);
   TRY_TEST(IsEqual(y,0.70710678),true);

   p1->put_X(10.0);
   p1->put_Y(10.0);
   p2->put_X(10.0);
   p2->put_Y(10.0);
   TRY_TEST( pLine->ThroughPoints(p1,p2),GEOMETRY_E_SAMEPOINTS);

   p1->put_X(0.0);
   p1->put_Y(10.0);
   p2->put_X(10.0);
   p2->put_Y(00.0);
   TRY_TEST(pLine->ThroughPoints(p1,p2),S_OK);

   vec.Release();
   pLine->GetImplicit(&c,&vec);

   TRY_TEST(IsEqual(c,7.0710678),true);
   vec->get_X(&x);
   vec->get_Y(&y);
   TRY_TEST(IsEqual(x, 0.70710678),true);
   TRY_TEST(IsEqual(y, 0.70710678),true);

   pnt.Release();
   vec.Release();
   pLine->GetExplicit(&pnt,&vec);

   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 5.0),true);
   TRY_TEST(IsEqual(y, 5.0),true);
   vec->get_X(&x);
   vec->get_Y(&y);
   TRY_TEST(IsEqual(x,0.70710678),true);
   TRY_TEST(IsEqual(y,-0.70710678),true);

   //
   // Test Offset
   //
   v->put_X(1);
   v->put_Y(0);
   pLine->SetImplicit(10,v);
   TRY_TEST(pLine->Offset(20),S_OK);

   vec.Release();
   pLine->GetImplicit(&c,&vec);

   TRY_TEST(IsEqual(c,30.0),true);
   vec->get_X(&x);
   vec->get_Y(&y);
   TRY_TEST(IsEqual(x,1.0),true);
   TRY_TEST(IsEqual(y,0.0),true);

   //
   // Test Rotate
   //
   v->put_X(0);
   v->put_Y(1);
   pLine->SetImplicit(10,v);
   TRY_TEST( pLine->Rotate(1,0,M_PI/2), S_OK );

   vec.Release();
   pLine->GetImplicit(&c,&vec);

   TRY_TEST( IsEqual(c,9.0), true );
   vec->get_X(&x);
   vec->get_Y(&y);
   TRY_TEST(IsEqual(x,-1.0),true);
   TRY_TEST(IsEqual(y, 0.0),true);

   //
   // Test RotateEx
   //
   v->put_X(0);
   v->put_Y(1);
   pLine->SetImplicit(10,v);
   p1->put_X(1);
   p1->put_Y(0);
   TRY_TEST( pLine->RotateEx(nullptr,M_PI/2), E_INVALIDARG );
   TRY_TEST( pLine->RotateEx(p1,M_PI/2), S_OK);

   vec.Release();
   pLine->GetImplicit(&c,&vec);

   TRY_TEST( IsEqual(c,9.0), true );
   vec->get_X(&x);
   vec->get_Y(&y);
   TRY_TEST(IsEqual(x,-1.0),true);
   TRY_TEST(IsEqual(y, 0.0),true);

   TestISupportErrorInfo();
}

void CTestLine2d::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_Line2d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ILine2d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
