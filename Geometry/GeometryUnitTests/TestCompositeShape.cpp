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

// TestCompositeShape.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestCompositeShape.cpp
// (legacy WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestCompositeShape)
{
public:
   TEST_METHOD(TestICompositeShape)
   {
         CComPtr<ICompositeShape> compShape;
         ASSERT_EQ(compShape.CoCreateInstance(CLSID_CompositeShape),S_OK);

         // Test container property initialization
         IndexType count;
         ASSERT_EQ(compShape->get_Count(nullptr),E_POINTER);
         ASSERT_EQ(compShape->get_Count(&count),S_OK);
         ASSERT_EQ(count,0);

         // Add an item to the container
         CComPtr<IRectangle> rectShape;
         rectShape.CoCreateInstance(CLSID_Rect);
         rectShape->put_Height(10);
         rectShape->put_Width(20);
         CComQIPtr<IShape> shape(rectShape);
         ASSERT_EQ(compShape->AddShape(nullptr,VARIANT_FALSE),E_INVALIDARG);
         ASSERT_EQ(compShape->AddShape(shape,VARIANT_FALSE),S_OK);
         ASSERT_EQ(compShape->get_Count(&count),S_OK);
         ASSERT_EQ(count,1);

         // The shape shoud be in the container by reference.
         rectShape->put_Width(30);
         CComPtr<ICompositeShapeItem> item;
         ASSERT_EQ(compShape->get_Item(-1,&item),E_INVALIDARG);
         ASSERT_EQ(compShape->get_Item(199,&item),E_INVALIDARG);
         ASSERT_EQ(compShape->get_Item(0,nullptr),E_POINTER);
         ASSERT_EQ(compShape->get_Item(0,&item),S_OK);

         shape.Release();
         item->get_Shape(&shape);
         CComQIPtr<IRectangle> refRectShape(shape);
         Float64 width;
         refRectShape->get_Width(&width);
         ASSERT_EQ(IsEqual(30.0,width),true);
         ASSERT_EQ(rectShape.IsEqualObject(refRectShape),true);

         // Test Remove
         // Note that we have a reference to item so we won't actually lose it
         ASSERT_EQ(compShape->Remove(-1),E_INVALIDARG);
         ASSERT_EQ(compShape->Remove(199),E_INVALIDARG);
         ASSERT_EQ(compShape->Remove(0),S_OK);
         ASSERT_EQ(compShape->get_Count(&count),S_OK);
         ASSERT_EQ(count,0);

         // Test AddShapeEx
         ASSERT_EQ(compShape->AddShapeEx(nullptr),E_INVALIDARG);
         ASSERT_EQ(compShape->AddShapeEx(item),S_OK);
         ASSERT_EQ(compShape->get_Count(&count),S_OK);
         ASSERT_EQ(count,1);

         CComPtr<ICompositeShapeItem> refItem;
         compShape->get_Item(0,&refItem);
         ASSERT_EQ(item.IsEqualObject(refItem),true);

         compShape->Remove(0);

         ///////////////////////////////////////
         // Test ISupportErrorInfo
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_CompositeShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ICompositeShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         //////////////////////////////////////////////////////////////
         // Test IObjectSafety
         CComPtr<IObjectSafety> pObjSafety;
         ASSERT_EQ(pObjSafety.CoCreateInstance(CLSID_CompositeShape), S_OK);
         DWORD dwDesiredOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
         DWORD dwSupportedOptions, dwEnabledOptions;
         pObjSafety->GetInterfaceSafetyOptions(IID_ICompositeShape,&dwSupportedOptions,&dwEnabledOptions);
         ASSERT_EQ( dwSupportedOptions, dwDesiredOptions );
         pObjSafety->GetInterfaceSafetyOptions(IID_IShape,&dwSupportedOptions,&dwEnabledOptions);
         ASSERT_EQ( dwSupportedOptions, dwDesiredOptions );
         pObjSafety->GetInterfaceSafetyOptions(IID_IXYPosition,&dwSupportedOptions,&dwEnabledOptions);
         ASSERT_EQ( dwSupportedOptions, dwDesiredOptions );
   }

   TEST_METHOD(TestIShape)
   {
         CComPtr<ICompositeShape> compShape;
         ASSERT_EQ(compShape.CoCreateInstance(CLSID_CompositeShape),S_OK);

         // Create a hollow box and check the properties
         //             10
         //   +------------------------+
         //   |           8            |
         //   |  +------------------+  |       A   = 40.0
         //   |  |                  |  |       Ixx = 343.33333
         //   |  |                  |  |       Iyy = 453.33333
         //   |  |                  |5 | 8     Ixy = 0.0
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

         compShape->AddShape(outerRectShape,VARIANT_FALSE);
         compShape->AddShape(innerRectShape,VARIANT_TRUE);

         CComQIPtr<IShape> shape(compShape);
         CComPtr<IShapeProperties> props;
         ASSERT_EQ(shape->get_ShapeProperties(nullptr),E_POINTER);
         ASSERT_EQ(shape->get_ShapeProperties(&props),S_OK);

         Float64 val;
         props->get_Area(&val);
         ASSERT_EQ(IsEqual(val,40.0),true);

         props->get_Ixx(&val);
         ASSERT_EQ(IsEqual(val,343.33333),true);

         props->get_Ixy(&val);
         ASSERT_EQ(IsEqual(val,0.00000),true);

         props->get_Iyy(&val);
         ASSERT_EQ(IsEqual(val,453.33333),true);

         CComPtr<IPoint2d> cg;
         props->get_Centroid(&cg);
         cg->get_X(&val);
         ASSERT_EQ(IsEqual(val,5.0),true);

         cg->get_Y(&val);
         ASSERT_EQ(IsEqual(val,4.0),true);

         CComPtr<IRect2d> box;
         ASSERT_EQ(shape->get_BoundingBox(nullptr),E_POINTER);
         ASSERT_EQ(shape->get_BoundingBox(&box),S_OK);
         box->get_Left(&val);
         ASSERT_EQ(IsEqual(val,0.0),true);
         box->get_Right(&val);
         ASSERT_EQ(IsEqual(val,10.0),true);
         box->get_Bottom(&val);
         ASSERT_EQ(IsEqual(val,0.0),true);
         box->get_Top(&val);
         ASSERT_EQ(IsEqual(val,8.0),true);

         // tweak the bounding box and use it for a clipping rectangle
         // Cover the top portion just above the void and clip.
         // Area should be 10x1.5 = 15
         box->put_Left(-100);
         box->put_Right(100);
         box->put_Bottom(6.5);
         box->put_Top(100);
         CComPtr<IShape> clippedShape;
         ASSERT_EQ(shape->ClipIn(nullptr,&clippedShape),E_INVALIDARG);
         ASSERT_EQ(shape->ClipIn(box,nullptr),E_POINTER);
         ASSERT_EQ(shape->ClipIn(box,&clippedShape),S_OK);

         props.Release();
         clippedShape->get_ShapeProperties(&props);
         props->get_Area(&val);
         ASSERT_EQ(IsEqual(val,15.0),true);

         // Clip with line... Use the bottom of the clipping rect.
         CComPtr<ILine2d> line;
         line.CoCreateInstance(CLSID_Line2d);
         CComPtr<IPoint2d> start;
         CComPtr<IPoint2d> end;
         box->get_BottomRight(&start);
         box->get_BottomLeft(&end);
         line->ThroughPoints(start,end);

         clippedShape.Release();
         ASSERT_EQ(shape->ClipWithLine(nullptr,&clippedShape),E_INVALIDARG);
         ASSERT_EQ(shape->ClipWithLine(line,nullptr),E_POINTER);
         ASSERT_EQ(shape->ClipWithLine(line,&clippedShape),S_OK);

         props.Release();
         clippedShape->get_ShapeProperties(&props);
         props->get_Area(&val);
         ASSERT_EQ(IsEqual(val,15.0),true);

         // Test clone
         CComPtr<IShape> clone;
         ASSERT_EQ(shape->Clone(nullptr),E_POINTER);
         ASSERT_EQ(shape->Clone(&clone),S_OK);

         CComQIPtr<ICompositeShape> compShapeClone(clone);
         ASSERT_EQ(compShapeClone != nullptr,true);
         IndexType count;
         compShapeClone->get_Count(&count);
         ASSERT_EQ(count,2);

         // check first shape
         CComPtr<ICompositeShapeItem> item1;
         compShapeClone->get_Item(0,&item1);
         CComPtr<IShape> shape1;
         item1->get_Shape(&shape1);
         CComQIPtr<IRectangle> rect1(shape1);
         ASSERT_EQ(rect1 != nullptr,true);
         rect1->get_Width(&val);
         ASSERT_EQ(IsEqual(val,10.0),true);
         rect1->get_Height(&val);
         ASSERT_EQ(IsEqual(val,8.0),true);

         // check second shape
         CComPtr<ICompositeShapeItem> item2;
         compShapeClone->get_Item(1,&item2);
         CComPtr<IShape> shape2;
         item2->get_Shape(&shape2);
         CComQIPtr<IRectangle> rect2(shape2);
         ASSERT_EQ(rect2 != nullptr,true);
         rect2->get_Width(&val);
         ASSERT_EQ(IsEqual(val,8.0),true);
         rect2->get_Height(&val);
         ASSERT_EQ(IsEqual(val,5.0),true);
   }

   TEST_METHOD(TestIXYPosition)
   {
         CComPtr<ICompositeShape> compShape;
         ASSERT_EQ(compShape.CoCreateInstance(CLSID_CompositeShape),S_OK);

         Float64 x,y;
         // Create a hollow box and check the properties
         //             10
         //   +------------------------+
         //   |           8            |
         //   |  +------------------+  |       A   = 40.0
         //   |  |                  |  |       Ixx = 343.33333
         //   |  |                  |  |       Iyy = 453.33333
         //   |  |                  |5 | 8     Ixy = 0.0
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

         compShape->AddShape(outerRectShape,VARIANT_FALSE);
         compShape->AddShape(innerRectShape,VARIANT_TRUE);

         // NOTE:
         // Getting HookPoint via get_LocatorPoint returns a copy of the hook point
         CComQIPtr<IXYPosition> position(compShape);

         CComPtr<IPoint2d> hookPnt;
         position->get_LocatorPoint(lpHookPoint,&hookPnt);
         hookPnt->Location(&x, &y);

         ASSERT_EQ( IsEqual(x,5.), true );
         ASSERT_EQ( IsEqual(y,4.), true );

         //
         // OffsetEx and Offset
         //
         CComPtr<ISize2d> size;
         size.CoCreateInstance( CLSID_Size2d );
         size->put_Dx(10);
         size->put_Dy(20);
         ASSERT_EQ( position->OffsetEx(nullptr), E_INVALIDARG );
         ASSERT_EQ( position->OffsetEx(size), S_OK );

         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);

         ASSERT_EQ( IsEqual(x,15.), true );
         ASSERT_EQ( IsEqual(y,24.), true );

         ASSERT_EQ( position->Offset(10,20), S_OK );

         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);


         ASSERT_EQ( IsEqual(x,25.), true );
         ASSERT_EQ( IsEqual(y,44.), true );

         //
         // MoveEx
         //
         CComPtr<IPoint2d> from;
         from.CoCreateInstance( CLSID_Point2d );
         from->Move(10,10);

         CComPtr<IPoint2d> to;
         to.CoCreateInstance( CLSID_Point2d );
         to->Move(110,110);

         ASSERT_EQ( position->MoveEx(nullptr,to),    E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from, nullptr), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,to),    S_OK );

         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);


         ASSERT_EQ( IsEqual(x,125.), true );
         ASSERT_EQ( IsEqual(y,144.), true );

         //
         // LocatorPoint property
         //
         hookPnt->Move(0,0);

         ASSERT_EQ( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

         // BottomLeft
         to->Move(95,85);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpBottomLeft,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomLeft,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,95.0), true );
         ASSERT_EQ( IsEqual(y,85.0), true );
         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y, 89.), true );

         // BottomCenter
         to->Move(100,85);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpBottomCenter,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomCenter,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y, 85.0), true );
         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y, 89.0), true );

         // BottomRight
         to->Move(105,85);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpBottomRight,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomRight,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,105.0), true );
         ASSERT_EQ( IsEqual(y, 85.0), true );
         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y, 89.), true );

         // CenterLeft
         to->Move(95,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpCenterLeft,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpCenterLeft,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 95.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // CenterCenter
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpCenterCenter,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpCenterCenter,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // CenterRight
         to->Move(105,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpCenterRight,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpCenterRight,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,105.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // TopLeft
         to->Move(95,115);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpTopLeft,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpTopLeft,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 95.0), true );
         ASSERT_EQ( IsEqual(y,115.0), true );
         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,111.), true );

         // TopCenter
         to->Move(100,115);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpTopCenter,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpTopCenter,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,115.0), true );
         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 100.), true );
         ASSERT_EQ( IsEqual(y, 111.), true );

         // TopRight
         to->Move(105,115);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpTopRight,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpTopRight,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,105.0), true );
         ASSERT_EQ( IsEqual(y,115.0), true );
         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,111.), true );

         // HookPoint
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpHookPoint,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpHookPoint,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt.Release();
         position->get_LocatorPoint(lpHookPoint, &hookPnt);
         hookPnt->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         //
         // Rotate and RotateEx
         //
         hookPnt->Move(10,20);
         position->put_LocatorPoint(lpHookPoint, hookPnt);

         CComPtr<IPoint2d> rotPoint;
         rotPoint.CoCreateInstance( CLSID_Point2d );

         // Rotate about the origin of the coordinate system and check the coordintes of the rectangle
         rotPoint->Move(0,0);

         ASSERT_EQ( position->RotateEx(nullptr,PI_OVER_2), E_INVALIDARG );
         ASSERT_EQ( position->RotateEx(rotPoint,PI_OVER_2), S_OK );

         CComPtr<IPoint2dCollection> coll;
         CComQIPtr<IShape> shape(outerRectShape);
         shape->get_PolyPoints(&coll);
         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,4 );

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         std::array<CComPtr<IPoint2d>,5> points;
         ULONG fetched;
         Enum->Next(5,&points[0],&fetched);
         ASSERT_EQ( fetched, 4 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-16.0), true );
         ASSERT_EQ( IsEqual(y, 15.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-16.0), true );
         ASSERT_EQ( IsEqual(y, 5.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-24.0), true );
         ASSERT_EQ( IsEqual(y, 5.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-24.0), true );
         ASSERT_EQ( IsEqual(y, 15.0), true );
   }
};
} // namespace GeometryUnitTests