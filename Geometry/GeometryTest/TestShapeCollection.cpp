///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// TestShapeCollection.cpp: implementation of the CTestShapeCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestShapeCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestShapeCollection::CTestShapeCollection()
{

}

CTestShapeCollection::~CTestShapeCollection()
{

}

void CTestShapeCollection::Test()
{
   CComPtr<IShapeCollection> pColl;
   TRY_TEST(pColl.CoCreateInstance( CLSID_ShapeCollection ), S_OK);

   CollectionIndexType count;
   TRY_TEST(pColl->get_Count(nullptr),E_POINTER);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   //
   // Test Add method
   //
   TRY_TEST(pColl->Add(nullptr),E_INVALIDARG);

   // add some shapes and see if we get them back
   CComPtr<IRectangle> rect1;
   rect1.CoCreateInstance(CLSID_Rect);
   rect1->put_Height(10);
   rect1->put_Width(5);

   CComPtr<IPoint2d> hp;
   rect1->get_HookPoint(&hp);
   hp->Move(7.5,20);

   CComQIPtr<IShape> shape1(rect1);
   TRY_TEST(pColl->Add(shape1),S_OK);

   CComPtr<IRectangle> rect2;
   rect2.CoCreateInstance(CLSID_Rect);
   rect2->put_Height(5);
   rect2->put_Width(2);

   hp.Release();
   rect2->get_HookPoint(&hp);
   hp->Move(21,7.5);

   CComQIPtr<IShape> shape2(rect2);
   TRY_TEST(pColl->Add(shape2),S_OK);

   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,2);

   // Test Item property
   CComPtr<IShape> shape;
   TRY_TEST(pColl->get_Item(-1,&shape),E_INVALIDARG); // invalid index
   TRY_TEST(pColl->get_Item(10,&shape),E_INVALIDARG); // index out of range - too high
   TRY_TEST(pColl->get_Item(1,nullptr),E_POINTER);
   TRY_TEST(pColl->get_Item(0,&shape),S_OK);

   TRY_TEST(shape.IsEqualObject(shape1),true);

   // Shapes in the container should be references. Change shape and see if rect1 changes
   CComQIPtr<IRectangle> rect(shape);
   rect->put_Height(50);
   Float64 val;
   rect1->get_Height(&val);
   TRY_TEST(IsEqual(val,50.),true);

   //
   // Test Remove
   //
   TRY_TEST(pColl->Remove(-1),E_INVALIDARG); // invalid index
   TRY_TEST(pColl->Remove(10),E_INVALIDARG); // index out of range - too high
   TRY_TEST(pColl->Remove(1),S_OK);

   // The count should now be 1
   pColl->get_Count(&count);
   TRY_TEST(count,1);

   //
   // Test Clear
   //
   TRY_TEST( pColl->Clear(), S_OK );
   pColl->get_Count(&count);
   TRY_TEST(count,0);

   //
   // Test _Enum
   //
   
   // put the height of rect1 back the way it should be
   rect1->put_Height(10);
   pColl->Add(shape1);
   pColl->Add(shape2);
   CComPtr<IEnumShape> pEnum;
   TRY_TEST(pColl->get__Enum(nullptr), E_POINTER );
   TRY_TEST( pColl->get__Enum(&pEnum), S_OK );

   ULONG fetched;
   shape.Release();
   while( pEnum->Next(1,&shape,&fetched ) == S_OK )
   {
      rect.Release();
      shape.QueryInterface(&rect);
      TRY_TEST( rect != nullptr, true );
      shape.Release();
   }

   // Test shape properties
   CComPtr<IShapeProperties> props;
   TRY_TEST(pColl->get_ShapeProperties(nullptr),E_POINTER);
   TRY_TEST(pColl->get_ShapeProperties(&props),S_OK);

   props->put_CoordinateSystem(csGlobal);

   Float64 area,ixx,iyy,ixy;
   props->get_Area(&area);
   TRY_TEST(IsEqual(area,60.),true);

   props->get_Ixx(&ixx);
   TRY_TEST(IsEqual(ixx,21000.),true);

   props->get_Iyy(&iyy);
   TRY_TEST(IsEqual(iyy,7330.),true);

   props->get_Ixy(&ixy);
   TRY_TEST(IsEqual(ixy,9075.),true);

   CComPtr<IPoint2d> cg;
   props->get_Centroid(&cg);
   Float64 cgx, cgy;
   cg->get_X(&cgx);
   cg->get_Y(&cgy);

   TRY_TEST(IsEqual(cgx, 9.750000, 0.01),   true);
   TRY_TEST(IsEqual(cgy,17.916667, 0.0001), true);

   Float64 l,r,t,b;
   props->get_Xleft(&l);
   props->get_Xright(&r);
   props->get_Ytop(&t);
   props->get_Ybottom(&b);

   TRY_TEST(IsEqual(l,4.75),true);
   TRY_TEST(IsEqual(r,12.25),true);
   TRY_TEST(IsEqual(t,7.083333,0.0001),true);
   TRY_TEST(IsEqual(b,12.916666,0.0001),true);

   TestISupportErrorInfo();
}

void CTestShapeCollection::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_ShapeCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShapeCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
