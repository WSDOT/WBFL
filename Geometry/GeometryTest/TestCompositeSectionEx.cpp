///////////////////////////////////////////////////////////////////////
// Sections Test - Test driver for Sections library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// TestCompositeSectionEx.cpp: implementation of the CTestCompositeSectionEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCompositeSectionEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCompositeSectionEx::CTestCompositeSectionEx()
{

}

CTestCompositeSectionEx::~CTestCompositeSectionEx()
{

}

void CTestCompositeSectionEx::Test()
{
   TestICompositeSection();
   TestISection();
   TestIXYPosition();
}

void CTestCompositeSectionEx::TestICompositeSection()
{
   CComPtr<ICompositeSectionEx> compSect;
   TRY_TEST(compSect.CoCreateInstance(CLSID_CompositeSectionEx),S_OK);

   // Test container property initialization
   IndexType count;
   TRY_TEST(compSect->get_Count(nullptr),E_POINTER);
   TRY_TEST(compSect->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   // Add an item to the container
   CComPtr<IRectangle> rectShape;
   rectShape.CoCreateInstance(CLSID_Rect);
   rectShape->put_Height(10);
   rectShape->put_Width(20);
   CComQIPtr<IShape> shape(rectShape);
   TRY_TEST(compSect->AddSection(shape,1,0,1,0,VARIANT_TRUE),S_OK);
   TRY_TEST(compSect->get_Count(&count),S_OK);
   TRY_TEST(count,1);

   // The shape shoud be in the container by reference.
   rectShape->put_Width(30);
   CComPtr<ICompositeSectionItemEx> item;
   TRY_TEST(compSect->get_Item(-1,&item),E_INVALIDARG);
   TRY_TEST(compSect->get_Item(199,&item),E_INVALIDARG);
   TRY_TEST(compSect->get_Item(0,nullptr),E_POINTER);
   TRY_TEST(compSect->get_Item(0,&item),S_OK);

   shape.Release();
   item->get_Shape(&shape);
   CComQIPtr<IRectangle> refRectShape(shape);
   Float64 width;
   refRectShape->get_Width(&width);
   TRY_TEST(IsEqual(30.0,width),true);
   TRY_TEST(rectShape.IsEqualObject(refRectShape),true);

   // Test Remove
   // Note that we have a reference to item so we won't actually lose it
   TRY_TEST(compSect->Remove(-1),E_INVALIDARG);
   TRY_TEST(compSect->Remove(199),E_INVALIDARG);
   TRY_TEST(compSect->Remove(0),S_OK);
   TRY_TEST(compSect->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   // Test AddSectionEx
   TRY_TEST(compSect->AddSectionEx(nullptr),E_INVALIDARG);
   TRY_TEST(compSect->AddSectionEx(item),S_OK);
   TRY_TEST(compSect->get_Count(&count),S_OK);
   TRY_TEST(count,1);

   CComPtr<ICompositeSectionItemEx> refItem;
   compSect->get_Item(0,&refItem);
   TRY_TEST(item.IsEqualObject(refItem),true);

   compSect->Remove(0);

   ///////////////////////////////////////
   // Test ISupportErrorInfo
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_CompositeSectionEx ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICompositeSectionEx ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   //////////////////////////////////////////////////////////////
   // Test IObjectSafety
   CComPtr<IObjectSafety> pObjSafety;
   TRY_TEST(pObjSafety.CoCreateInstance(CLSID_CompositeSectionEx), S_OK);
   DWORD dwDesiredOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
   DWORD dwSupportedOptions, dwEnabledOptions;
   pObjSafety->GetInterfaceSafetyOptions(IID_ICompositeSectionEx,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
   pObjSafety->GetInterfaceSafetyOptions(IID_ISection,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
   pObjSafety->GetInterfaceSafetyOptions(IID_IXYPosition,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
}

void CTestCompositeSectionEx::TestISection()
{
   CComPtr<ICompositeSectionEx> compSect;
   TRY_TEST(compSect.CoCreateInstance(CLSID_CompositeSectionEx),S_OK);

   // Create a hollow box and check the properties
   //             10
   //   +------------------------+
   //   |           8            |
   //   |  +------------------+  |       EA   = 40.0
   //   |  |                  |  |       EIxx = 343.33333
   //   |  |                  |  |       EIyy = 453.33333
   //   |  |                  |5 | 8     EIxy = 0.0
   //   |  |                  |  |       cg   = (5,4)
   //   |  |                  |  |
   //   |  +------------------+  |
   //   |                        |
   //   +------------------------+
   //
   CComPtr<IRectangle> outerRect;
   outerRect.CoCreateInstance(CLSID_Rect);
   outerRect->put_Width(10);
   outerRect->put_Height(8);
   
   CComQIPtr<IXYPosition> outerRectPos(outerRect);
   CComPtr<IPoint2d> lp;
   outerRectPos->get_LocatorPoint(lpBottomLeft,&lp);
   lp->Move(0,0);
   outerRectPos->put_LocatorPoint(lpBottomLeft,lp);

   CComPtr<IRectangle> innerRect;
   innerRect.CoCreateInstance(CLSID_Rect);
   innerRect->put_Width(8);
   innerRect->put_Height(5);

   CComQIPtr<IXYPosition> innerRectPos(innerRect);
   lp.Release();
   innerRectPos->get_LocatorPoint(lpCenterCenter,&lp);
   lp->Move(5,4);
   innerRectPos->put_LocatorPoint(lpCenterCenter,lp);

   CComQIPtr<IShape> outerRectShape(outerRect);
   CComQIPtr<IShape> innerRectShape(innerRect);

   compSect->AddSection(outerRectShape,1.0,0.0,1.0,0.0,VARIANT_TRUE);
   compSect->AddSection(innerRectShape,0.0,1.0,0.0,1.0,VARIANT_TRUE);

   CComQIPtr<ISection> section(compSect);
   CComPtr<IElasticProperties> props;
   TRY_TEST(section->get_ElasticProperties(nullptr),E_POINTER);
   TRY_TEST(section->get_ElasticProperties(&props),S_OK);

   Float64 val;
   props->get_EA(&val);
   TRY_TEST(IsEqual(val,40.0),true);

   props->get_EIxx(&val);
   TRY_TEST(IsEqual(val,343.33333),true);

   props->get_EIxy(&val);
   TRY_TEST(IsEqual(val,0.00000),true);

   props->get_EIyy(&val);
   TRY_TEST(IsEqual(val,453.33333),true);

   CComPtr<IPoint2d> cg;
   props->get_Centroid(&cg);
   cg->get_X(&val);
   TRY_TEST(IsEqual(val,5.0),true);

   cg->get_Y(&val);
   TRY_TEST(IsEqual(val,4.0),true);

   CComPtr<IMassProperties> massProps;
   TRY_TEST(section->get_MassProperties(nullptr),E_POINTER);
   TRY_TEST(section->get_MassProperties(&massProps),S_OK);
   massProps->get_MassPerLength(&val);
   TRY_TEST(IsEqual(val,40.0),true);

   CComPtr<IRect2d> box;
   TRY_TEST(section->get_BoundingBox(nullptr),E_POINTER);
   TRY_TEST(section->get_BoundingBox(&box),S_OK);
   box->get_Left(&val);
   TRY_TEST(IsEqual(val,0.0),true);
   box->get_Right(&val);
   TRY_TEST(IsEqual(val,10.0),true);
   box->get_Bottom(&val);
   TRY_TEST(IsEqual(val,0.0),true);
   box->get_Top(&val);
   TRY_TEST(IsEqual(val,8.0),true);

   // tweak the bounding box and use it for a clipping rectangle
   // Cover the top portion just above the void and clip.
   // Area should be 10x1.5 = 15
   box->put_Left(-100);
   box->put_Right(100);
   box->put_Bottom(6.5);
   box->put_Top(100);
   CComPtr<ISection> clippedSection;
   TRY_TEST(section->ClipIn(nullptr,&clippedSection),E_INVALIDARG);
   TRY_TEST(section->ClipIn(box,nullptr),E_POINTER);
   TRY_TEST(section->ClipIn(box,&clippedSection),S_OK);

   props.Release();
   clippedSection->get_ElasticProperties(&props);
   props->get_EA(&val);
   TRY_TEST(IsEqual(val,15.0),true);

   // Clip with line... Use the bottom of the clipping rect.
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   CComPtr<IPoint2d> start;
   CComPtr<IPoint2d> end;
   box->get_BottomRight(&start);
   box->get_BottomLeft(&end);
   line->ThroughPoints(start,end);

   clippedSection.Release();
   TRY_TEST(section->ClipWithLine(nullptr,&clippedSection),E_INVALIDARG);
   TRY_TEST(section->ClipWithLine(line,nullptr),E_POINTER);
   TRY_TEST(section->ClipWithLine(line,&clippedSection),S_OK);

   props.Release();
   clippedSection->get_ElasticProperties(&props);
   props->get_EA(&val);
   TRY_TEST(IsEqual(val,15.0),true);

   // Test clone
   CComPtr<ISection> clone;
   TRY_TEST(section->Clone(nullptr),E_POINTER);
   TRY_TEST(section->Clone(&clone),S_OK);

   CComQIPtr<ICompositeSectionEx> compSectClone(clone);
   TRY_TEST(compSectClone != nullptr,true);
   IndexType count;
   compSectClone->get_Count(&count);
   TRY_TEST(count,2);

   // check first shape
   CComPtr<ICompositeSectionItemEx> item1;
   compSectClone->get_Item(0,&item1);
   CComPtr<IShape> shape1;
   item1->get_Shape(&shape1);
   CComQIPtr<IRectangle> rect1(shape1);
   TRY_TEST(rect1 != nullptr,true);
   rect1->get_Width(&val);
   TRY_TEST(IsEqual(val,10.0),true);
   rect1->get_Height(&val);
   TRY_TEST(IsEqual(val,8.0),true);

   // check second shape
   CComPtr<ICompositeSectionItemEx> item2;
   compSectClone->get_Item(1,&item2);
   CComPtr<IShape> shape2;
   item2->get_Shape(&shape2);
   CComQIPtr<IRectangle> rect2(shape2);
   TRY_TEST(rect2 != nullptr,true);
   rect2->get_Width(&val);
   TRY_TEST(IsEqual(val,8.0),true);
   rect2->get_Height(&val);
   TRY_TEST(IsEqual(val,5.0),true);
}

void CTestCompositeSectionEx::TestIXYPosition()
{
   Float64 x,y;

   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_CompositeSectionEx ), S_OK );

   CComQIPtr<ICompositeSectionEx> compSect(position);
   TRY_TEST( compSect != nullptr, true );

   CComPtr<IRectangle> rect;
   rect.CoCreateInstance(CLSID_Rect);
   rect->put_Width(10);
   rect->put_Height(30);

   CComPtr<IPoint2d> hookPnt;
   rect->get_HookPoint(&hookPnt);
   hookPnt->put_X(10);
   hookPnt->put_Y(20);

   CComQIPtr<IShape> rectShape(rect);
   compSect->AddSection(rectShape,1.0,0.0,1.0,0.0,VARIANT_TRUE);

   // NOTE:
   // Earlier testing has demonstrated that the Shape objects in the composite
   // are ByRef. As such, we can simply check the results of each operation
   // against the properties of the rect object and the hookPnt object. There
   // is no need to drill into the composite to get the shape.

   //
   // OffsetEx and Offset
   //
   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(10);
   size->put_Dy(20);
   TRY_TEST( position->OffsetEx(nullptr), E_INVALIDARG );
   TRY_TEST( position->OffsetEx(size), S_OK );

   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);

   TRY_TEST( IsEqual(x,20.), true );
   TRY_TEST( IsEqual(y,40.), true );

   TRY_TEST( position->Offset(10,20), S_OK );

   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);

   TRY_TEST( IsEqual(x,30.), true );
   TRY_TEST( IsEqual(y,60.), true );

   //
   // MoveEx
   //
   CComPtr<IPoint2d> from;
   from.CoCreateInstance( CLSID_Point2d );
   from->Move(10,10);

   CComPtr<IPoint2d> to;
   to.CoCreateInstance( CLSID_Point2d );
   to->Move(110,110);

   TRY_TEST( position->MoveEx(nullptr,to),    E_INVALIDARG );
   TRY_TEST( position->MoveEx(from, nullptr), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,to),    S_OK );

   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);

   TRY_TEST( IsEqual(x,130.), true );
   TRY_TEST( IsEqual(y,160.), true );

   //
   // LocatorPoint property
   //
   hookPnt->Move(0,0);

   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

   // BottomLeft
   to->Move(95,85);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,95.0), true );
   TRY_TEST( IsEqual(y,85.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // BottomCenter
   to->Move(100,85);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpBottomCenter,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpBottomCenter,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y, 85.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // BottomRight
   to->Move(105,85);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpBottomRight,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpBottomRight,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,105.0), true );
   TRY_TEST( IsEqual(y, 85.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // CenterLeft
   to->Move(95,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpCenterLeft,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpCenterLeft,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x, 95.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // CenterCenter
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpCenterCenter,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpCenterCenter,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // CenterRight
   to->Move(105,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpCenterRight,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpCenterRight,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,105.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // TopLeft
   to->Move(95,115);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpTopLeft,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpTopLeft,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x, 95.0), true );
   TRY_TEST( IsEqual(y,115.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // TopCenter
   to->Move(100,115);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpTopCenter,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpTopCenter,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,115.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // TopRight
   to->Move(105,115);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpTopRight,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpTopRight,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,105.0), true );
   TRY_TEST( IsEqual(y,115.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // HookPoint
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpHookPoint,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpHookPoint,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   //
   // Rotate and RotateEx
   //
   hookPnt->Move(10,20);
   CComPtr<IPoint2d> rotPoint;
   rotPoint.CoCreateInstance( CLSID_Point2d );

   // Rotate about the origin of the coordinate system and check the coordintes of the rectangle
   rotPoint->Move(0,0);

   TRY_TEST( position->RotateEx(nullptr,PI_OVER_2), E_INVALIDARG );
   TRY_TEST( position->RotateEx(rotPoint,PI_OVER_2), S_OK );

   CComPtr<IPoint2dCollection> coll;
   CComQIPtr<IShape> shape(rect);
   shape->get_PolyPoints(&coll);
   IndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,4 );
   
   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[5];
   ULONG fetched;
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   int i = 0;
   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-5.0), true );
   TRY_TEST( IsEqual(y,15.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-5.0), true );
   TRY_TEST( IsEqual(y, 5.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-35.0), true );
   TRY_TEST( IsEqual(y,  5.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-35.0), true );
   TRY_TEST( IsEqual(y, 15.0), true );
}
