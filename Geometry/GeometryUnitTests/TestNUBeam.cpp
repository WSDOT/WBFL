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

// TestNUBeam.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestNUBeam.cpp,
// TestNUBeam2.cpp, and TestNUBeam3.cpp (the legacy harness split this single
// logical test class across three files purely due to old compiler
// function-size limits: TestNUBeam.cpp had TestINUBeam/TestIXYPosition/
// TestISupportErrorInfo, TestNUBeam2.cpp had TestIShape/TestIShape2,
// TestNUBeam3.cpp had TestIShape3) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestNUBeam)
{
public:
   TEST_METHOD(TestINUBeam)
   {
         CComPtr<INUBeam> beam;
         ASSERT_EQ( beam.CoCreateInstance(CLSID_NUBeam), S_OK );

         // Verify initialization. All dimensions should be zero.
         // Hook point (bottom center) should be zero.
         Float64 val;
         CComPtr<IPoint2d> pntVal;

         ASSERT_EQ( beam->get_D1(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_D2(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D2(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_D3(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D3(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_D4(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D4(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_D5(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D5(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_T(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_T(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_W1(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_W2(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W2(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_R1(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_R1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_R2(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_R2(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_R3(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_R3(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_R4(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_R4(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_HookPoint(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_HookPoint(&pntVal), S_OK );
         pntVal->get_X(&val);
         ASSERT_EQ( IsZero(val), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsZero(val), true );

         // Test properties
         ASSERT_EQ( beam->put_D1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D1(65), S_OK );
         beam->get_D1(&val);
         ASSERT_EQ( IsEqual(val,65.0), true );

         ASSERT_EQ( beam->put_D2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D2(45), S_OK );
         beam->get_D2(&val);
         ASSERT_EQ( IsEqual(val,45.0), true );

         ASSERT_EQ( beam->put_D3(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D3(2015), S_OK );
         beam->get_D3(&val);
         ASSERT_EQ( IsEqual(val,2015.0), true );

         ASSERT_EQ( beam->put_D4(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D4(140), S_OK );
         beam->get_D4(&val);
         ASSERT_EQ( IsEqual(val,140.0), true );

         ASSERT_EQ( beam->put_D5(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D5(135), S_OK );
         beam->get_D5(&val);
         ASSERT_EQ( IsEqual(val,135.0), true );

         ASSERT_EQ( beam->put_T(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_T(150), S_OK );
         beam->get_T(&val);
         ASSERT_EQ( IsEqual(val,150.0), true );

         ASSERT_EQ( beam->put_W1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W1(1225), S_OK );
         beam->get_W1(&val);
         ASSERT_EQ( IsEqual(val,1225.0), true );

         ASSERT_EQ( beam->put_W2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W2(975), S_OK );
         beam->get_W2(&val);
         ASSERT_EQ( IsEqual(val,975.0), true );

         ASSERT_EQ( beam->put_R1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_R1(200), S_OK );
         beam->get_R1(&val);
         ASSERT_EQ( IsEqual(val,200.0), true );

         ASSERT_EQ( beam->put_R2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_R2(200), S_OK );
         beam->get_R2(&val);
         ASSERT_EQ( IsEqual(val,200.0), true );

         ASSERT_EQ( beam->put_R3(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_R3(50), S_OK );
         beam->get_R3(&val);
         ASSERT_EQ( IsEqual(val,50.0), true );

         ASSERT_EQ( beam->put_R4(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_R4(50), S_OK );
         beam->get_R4(&val);
         ASSERT_EQ( IsEqual(val,50.0), true );

         pntVal->Move(14,14);
         ASSERT_EQ( beam->putref_HookPoint(nullptr), E_INVALIDARG );
         ASSERT_EQ( beam->putref_HookPoint(pntVal), S_OK );
         pntVal.Release();
         beam->get_HookPoint(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         // Move the beam back
         pntVal->Move(0,0);
         beam->putref_HookPoint(pntVal);

         // Test propertyes
         ASSERT_EQ(beam->get_Height(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_Height(&val), S_OK );
         ASSERT_EQ(IsEqual(val,2400.), true );

         ASSERT_EQ(beam->get_TopFlangeWidth(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_TopFlangeWidth(&val), S_OK );
         ASSERT_EQ(IsEqual(val,1225.), true );

         ASSERT_EQ(beam->get_BottomFlangeWidth(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_BottomFlangeWidth(&val), S_OK );
         ASSERT_EQ(IsEqual(val,975.), true );

         ASSERT_EQ(beam->get_AvgWebWidth(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_AvgWebWidth(&val), S_OK );
         ASSERT_EQ(IsEqual(val,150.), true );


         // Test Interface Pointers
         CComPtr<IShape> shape;
         ASSERT_EQ(beam->get_Shape(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_Shape(&shape), S_OK );
         ASSERT_EQ(shape != nullptr,true );

         CComPtr<IXYPosition> position;
         ASSERT_EQ(beam->get_XYPosition(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_XYPosition(&position), S_OK );
         ASSERT_EQ(position != nullptr,true );

         CComPtr<IUnknown> punk1;
         CComPtr<IUnknown> punk2;
         CComPtr<IUnknown> punk3;
         beam->QueryInterface(&punk1);
         shape->QueryInterface(&punk2);
         position->QueryInterface(&punk3);
         ASSERT_EQ( punk1 == punk2, true );
         ASSERT_EQ( punk1 == punk3, true );
         ASSERT_EQ( punk2 == punk3, true );
   }

   TEST_METHOD(TestIShape)
   {
         CComPtr<IShape> shape;
         ASSERT_EQ( shape.CoCreateInstance( CLSID_NUBeam ), S_OK );
         CComQIPtr<INUBeam> beam(shape);

         // Use some real dimensions (NU2400 - 150mm web)
         beam->put_W1(1225);
         beam->put_W2(975);
         beam->put_D1(65);
         beam->put_D2(45);
         beam->put_D3(2015);
         beam->put_D4(140);
         beam->put_D5(135);
         beam->put_T(150);
         beam->put_R1(200);
         beam->put_R2(200);
         beam->put_R3(50);
         beam->put_R4(50);

         //
         // Bounding Box
         //
         Float64 val;
         CComPtr<IRect2d> box;
         ASSERT_EQ( shape->get_BoundingBox(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_BoundingBox(&box), S_OK );

         box->get_Left(&val);
         ASSERT_EQ( IsEqual(val,-612.5), true );

         box->get_Right(&val);
         ASSERT_EQ( IsEqual(val, 612.5), true );

         box->get_Top(&val);
         ASSERT_EQ( IsEqual(val,2400.), true );

         box->get_Bottom(&val);
         ASSERT_EQ( IsEqual(val,0.00), true );

         //
         // ShapeProperties
         //
         CComPtr<IShapeProperties> props;
         ASSERT_EQ( shape->get_ShapeProperties(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_ShapeProperties(&props), S_OK );
         Float64 area, ixx, iyy, ixy, cgx, cgy;
         CComPtr<IPoint2d> cg;

         props->get_Area(&area);
         props->get_Ixx(&ixx);
         props->get_Iyy(&iyy);
         props->get_Ixy(&ixy);
         cg.Release();
         props->get_Centroid(&cg);
         ASSERT_EQ( IsEqual(area, 643591.88418736495), true );
         ASSERT_EQ( IsEqual(ixx, 514253978920.25220), true );
         ASSERT_EQ( IsEqual(iyy, 25969895815.002991), true );
         ASSERT_EQ( IsEqual(ixy,0.0,0.0005), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,0.0), true );
         ASSERT_EQ( IsEqual(cgy, 1093.1459162077181), true );
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

         Float64 xleft,xright,ytop,ybottom;
         props->get_Xleft(&xleft);
         props->get_Xright(&xright);
         props->get_Ytop(&ytop);
         props->get_Ybottom(&ybottom);
         ASSERT_EQ(IsEqual(xleft,612.5),true);
         ASSERT_EQ(IsEqual(xright,612.5),true);
         ASSERT_EQ(IsEqual(ytop,2400-cgy),true);
         ASSERT_EQ(IsEqual(ybottom,cgy),true);

         //
         // Perimeter
         //
         ASSERT_EQ( shape->get_Perimeter(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_Perimeter(&val), S_OK );
         ASSERT_EQ( IsEqual(val, 8308.7371100128730), true );

         //
         // FurthestDistance
         //
         CComPtr<IPoint2d> p1;
         p1.CoCreateInstance( CLSID_Point2d );

         CComPtr<IPoint2d> p2;
         p2.CoCreateInstance( CLSID_Point2d );

         CComPtr<ILine2d> line;
         line.CoCreateInstance( CLSID_Line2d );

         // Shape on right
         p1->Move(0,20);
         p2->Move(100,20);
         line->ThroughPoints(p1,p2);
         Float64 dist;
         ASSERT_EQ( shape->FurthestDistance(nullptr,&dist), E_INVALIDARG );
         ASSERT_EQ( shape->FurthestDistance(line,nullptr), E_POINTER );
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,20.000), true );

         // shape on left
         p1->Move(0,-20);
         p2->Move(100,-20);
         line->ThroughPoints(p1,p2);
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,-20.0), true );
   }

   TEST_METHOD(TestIShape2)
   {
         CComPtr<IShape> shape;
         ASSERT_EQ( shape.CoCreateInstance( CLSID_NUBeam ), S_OK );
         CComQIPtr<INUBeam> beam(shape);

         // Use some real dimensions (NU2400 - 150mm web)
         beam->put_W1(1225);
         beam->put_W2(975);
         beam->put_D1(65);
         beam->put_D2(45);
         beam->put_D3(2015);
         beam->put_D4(140);
         beam->put_D5(135);
         beam->put_T(150);
         beam->put_R1(200);
         beam->put_R2(200);
         beam->put_R3(50);
         beam->put_R4(50);

         // 
         // PolyPoints
         //
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );

         const IndexType nPoints = 175; // number of expected points
         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, nPoints );

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         CComPtr<IPoint2d> points[nPoints];
         ULONG fetched;
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, nPoints );

         Float64 x,y;
         int i = 0;

         TEST_POINT(points, 0., 0.);
         TEST_POINT(points,-487.5, 0.);
         TEST_POINT(points,-487.5, 99.1684601);
         TEST_POINT(points,-487.4033721, 102.27546);
         TEST_POINT(points,-487.1138621, 105.370451);
         TEST_POINT(points,-486.6325887, 108.4414706);
         TEST_POINT(points,-485.9614123, 111.476649);
         TEST_POINT(points,-485.1029271, 114.4642548);
         TEST_POINT(points,-484.060451, 117.3927406);
         TEST_POINT(points,-482.8380135, 120.2507875);
         TEST_POINT(points,-481.4403395, 123.0273488);
         TEST_POINT(points,-479.8728309, 125.7116927);
         TEST_POINT(points,-478.1415466, 128.2934441);
         TEST_POINT(points,-476.253178, 130.762624);
         TEST_POINT(points,-474.215024, 133.1096889);
         TEST_POINT(points,-472.0349622, 135.3255671);
         TEST_POINT(points,-469.7214189, 137.4016939);
         TEST_POINT(points,-467.2833361, 139.3300449);
         TEST_POINT(points,-464.7301372, 141.1031668);
         TEST_POINT(points,-462.0716908, 142.7142063);
         TEST_POINT(points,-459.3182721, 144.1569365);
         TEST_POINT(points,-456.4805232, 145.425781);
         TEST_POINT(points,-453.5694124, 146.5158358);
         TEST_POINT(points,-210.7223506, 228.9366568);
         TEST_POINT(points,-199.0779074, 233.2968758);
         TEST_POINT(points,-187.7269118, 238.3722542);
         TEST_POINT(points,-176.7132366, 244.1431749);
         TEST_POINT(points,-166.079451, 250.5873328);
         TEST_POINT(points,-155.8666558, 257.6798204);
         TEST_POINT(points,-146.1143245, 265.3932244);
         TEST_POINT(points,-136.8601511, 273.6977317);
         TEST_POINT(points,-128.139904, 282.5612444);
         TEST_POINT(points,-119.9872879, 291.949504);
         TEST_POINT(points,-112.4338136, 301.8262237);
         TEST_POINT(points,-105.5086763, 312.1532291);
         TEST_POINT(points,-99.2386422, 322.8906049);
         TEST_POINT(points,-93.64794584, 333.99685);
         TEST_POINT(points,-88.75819588, 345.4290376);
         TEST_POINT(points,-84.58829176, 357.1429808);
         TEST_POINT(points,-81.15435063, 369.0934041);
         TEST_POINT(points,-78.46964506, 381.2341175);
         TEST_POINT(points,-76.54455176, 393.5181959);
         TEST_POINT(points,-75.38651142, 405.8981599);
         TEST_POINT(points,-75., 418.3261596);
         TEST_POINT(points,-75., 2106.044491);
         TEST_POINT(points,-75.55273836, 2120.903489);
         TEST_POINT(points,-77.20789825, 2135.680355);
         TEST_POINT(points,-79.95633096, 2150.293413);
         TEST_POINT(points,-83.78284486, 2164.661891);
         TEST_POINT(points,-88.66628932, 2178.706367);
         TEST_POINT(points,-94.57967169, 2192.349213);
         TEST_POINT(points,-101.4903064, 2205.51502);
         TEST_POINT(points,-109.3599958, 2218.131015);
         TEST_POINT(points,-118.145241, 2230.127465);
         TEST_POINT(points,-127.7974827, 2241.438061);
         TEST_POINT(points,-138.2633691, 2252.000284);
         TEST_POINT(points,-149.4850513, 2261.755754);
         TEST_POINT(points,-161.4005028, 2270.650548);
         TEST_POINT(points,-173.9438624, 2278.635501);
         TEST_POINT(points,-187.0457979, 2285.666478);
         TEST_POINT(points,-200.6338901, 2291.704615);
         TEST_POINT(points,-214.6330323, 2296.716537);
         TEST_POINT(points,-228.9658458, 2300.674541);
         TEST_POINT(points,-243.5531078, 2303.556751);
         TEST_POINT(points,-258.3141889, 2305.347234);
         TEST_POINT(points,-566.6714528, 2331.163191);
         TEST_POINT(points,-570.361723, 2331.610812);
         TEST_POINT(points,-574.0085385, 2332.331365);
         TEST_POINT(points,-577.5917419, 2333.320866);
         TEST_POINT(points,-581.0915275, 2334.573846);
         TEST_POINT(points,-584.4885505, 2336.083381);
         TEST_POINT(points,-587.7640344, 2337.841125);
         TEST_POINT(points,-590.8998743, 2339.837363);
         TEST_POINT(points,-593.8787372, 2342.061061);
         TEST_POINT(points,-596.6841577, 2344.499929);
         TEST_POINT(points,-599.3006293, 2347.140485);
         TEST_POINT(points,-601.7136897, 2349.968134);
         TEST_POINT(points,-603.9100011, 2352.967246);
         TEST_POINT(points,-605.8774234, 2356.121245);
         TEST_POINT(points,-607.6050821, 2359.412697);
         TEST_POINT(points,-609.0834277, 2362.823408);
         TEST_POINT(points,-610.3042888, 2366.334527);
         TEST_POINT(points,-611.2609173, 2369.926647);
         TEST_POINT(points,-611.9480254, 2373.579911);
         TEST_POINT(points,-612.3618154, 2377.274128);
         TEST_POINT(points,-612.5, 2380.988877);
         TEST_POINT(points,-612.5, 2400.);
         TEST_POINT(points, 0.0, 2400.);
         TEST_POINT(points,612.5, 2400.);
         TEST_POINT(points,612.5, 2380.988877);
         TEST_POINT(points,612.3618154, 2377.274128);
         TEST_POINT(points,611.9480254, 2373.579911);
         TEST_POINT(points,611.2609173, 2369.926647);
         TEST_POINT(points,610.3042888, 2366.334527);
         TEST_POINT(points,609.0834277, 2362.823408);
         TEST_POINT(points,607.6050821, 2359.412697);
         TEST_POINT(points,605.8774234, 2356.121245);
         TEST_POINT(points,603.9100011, 2352.967246);
         TEST_POINT(points,601.7136897, 2349.968134);
         TEST_POINT(points,599.3006293, 2347.140485);
         TEST_POINT(points,596.6841577, 2344.499929);
         TEST_POINT(points,593.8787372, 2342.061061);
         TEST_POINT(points,590.8998743, 2339.837363);
         TEST_POINT(points,587.7640344, 2337.841125);
         TEST_POINT(points,584.4885505, 2336.083381);
         TEST_POINT(points,581.0915275, 2334.573846);
         TEST_POINT(points,577.5917419, 2333.320866);
         TEST_POINT(points,574.0085385, 2332.331365);
         TEST_POINT(points,570.361723, 2331.610812);
         TEST_POINT(points,566.6714528, 2331.163191);
         TEST_POINT(points,258.3141889, 2305.347234);
         TEST_POINT(points,243.5531078, 2303.556751);
         TEST_POINT(points,228.9658458, 2300.674541);
         TEST_POINT(points,214.6330323, 2296.716537);
         TEST_POINT(points,200.6338901, 2291.704615);
         TEST_POINT(points,187.0457979, 2285.666478);
         TEST_POINT(points,173.9438624, 2278.635501);
         TEST_POINT(points,161.4005028, 2270.650548);
         TEST_POINT(points,149.4850513, 2261.755754);
         TEST_POINT(points,138.2633691, 2252.000284);
         TEST_POINT(points,127.7974827, 2241.438061);
         TEST_POINT(points,118.145241, 2230.127465);
         TEST_POINT(points,109.3599958, 2218.131015);
         TEST_POINT(points,101.4903064, 2205.51502);
         TEST_POINT(points,94.57967169, 2192.349213);
         TEST_POINT(points,88.66628932, 2178.706367);
         TEST_POINT(points,83.78284486, 2164.661891);
         TEST_POINT(points,79.95633096, 2150.293413);
         TEST_POINT(points,77.20789825, 2135.680355);
         TEST_POINT(points,75.55273836, 2120.903489);
         TEST_POINT(points,75., 2106.044491);
         TEST_POINT(points,75., 418.3261596);
         TEST_POINT(points,75.38651142, 405.8981599);
         TEST_POINT(points,76.54455176, 393.5181959);
         TEST_POINT(points,78.46964506, 381.2341175);
         TEST_POINT(points,81.15435063, 369.0934041);
         TEST_POINT(points,84.58829176, 357.1429808);
         TEST_POINT(points,88.75819588, 345.4290376);
         TEST_POINT(points,93.64794584, 333.99685);
         TEST_POINT(points,99.2386422, 322.8906049);
         TEST_POINT(points,105.5086763, 312.1532291);
         TEST_POINT(points,112.4338136, 301.8262237);
         TEST_POINT(points,119.9872879, 291.949504);
         TEST_POINT(points,128.139904, 282.5612444);
         TEST_POINT(points,136.8601511, 273.6977317);
         TEST_POINT(points,146.1143245, 265.3932244);
         TEST_POINT(points,155.8666558, 257.6798204);
         TEST_POINT(points,166.079451, 250.5873328);
         TEST_POINT(points,176.7132366, 244.1431749);
         TEST_POINT(points,187.7269118, 238.3722542);
         TEST_POINT(points,199.0779074, 233.2968758);
         TEST_POINT(points,210.7223506, 228.9366568);
         TEST_POINT(points,453.5694124, 146.5158358);
         TEST_POINT(points,456.4805232, 145.425781);
         TEST_POINT(points,459.3182721, 144.1569365);
         TEST_POINT(points,462.0716908, 142.7142063);
         TEST_POINT(points,464.7301372, 141.1031668);
         TEST_POINT(points,467.2833361, 139.3300449);
         TEST_POINT(points,469.7214189, 137.4016939);
         TEST_POINT(points,472.0349622, 135.3255671);
         TEST_POINT(points,474.215024, 133.1096889);
         TEST_POINT(points,476.253178, 130.762624);
         TEST_POINT(points,478.1415466, 128.2934441);
         TEST_POINT(points,479.8728309, 125.7116927);
         TEST_POINT(points,481.4403395, 123.0273488);
         TEST_POINT(points,482.8380135, 120.2507875);
         TEST_POINT(points,484.060451, 117.3927406);
         TEST_POINT(points,485.1029271, 114.4642548);
         TEST_POINT(points,485.9614123, 111.476649);
         TEST_POINT(points,486.6325887, 108.4414706);
         TEST_POINT(points,487.1138621, 105.370451);
         TEST_POINT(points,487.4033721, 102.27546);
         TEST_POINT(points,487.5, 99.1684601);
         TEST_POINT(points,487.5, 0.);
         TEST_POINT(points, 0., 0.);

         ASSERT_EQ(i,nPoints);

         //
         // Clone
         //
         CComPtr<IShape> clone;
         ASSERT_EQ(shape->Clone(nullptr), E_POINTER );
         ASSERT_EQ(shape->Clone(&clone), S_OK);

         CComQIPtr<INUBeam> beamClone(clone);
         ASSERT_EQ( beamClone != nullptr, true );

         Float64 val;

         beamClone->get_W1(&val);
         ASSERT_EQ( IsEqual(val,1225.0), true);

         beamClone->get_W2(&val);
         ASSERT_EQ( IsEqual(val,975.0), true);

         beamClone->get_D1(&val);
         ASSERT_EQ( IsEqual(val,65.0), true);

         beamClone->get_D2(&val);
         ASSERT_EQ( IsEqual(val,45.0), true);

         beamClone->get_D3(&val);
         ASSERT_EQ( IsEqual(val,2015.0), true);

         beamClone->get_D4(&val);
         ASSERT_EQ( IsEqual(val,140.0), true);

         beamClone->get_D5(&val);
         ASSERT_EQ( IsEqual(val,135.0), true);

         beamClone->get_T(&val);
         ASSERT_EQ( IsEqual(val,150.0), true);

         beamClone->get_R1(&val);
         ASSERT_EQ( IsEqual(val,200.0), true);

         beamClone->get_R2(&val);
         ASSERT_EQ( IsEqual(val,200.0), true);

         beamClone->get_R3(&val);
         ASSERT_EQ( IsEqual(val,50.0), true);

         beamClone->get_R4(&val);
         ASSERT_EQ( IsEqual(val,50.0), true);

         //
         // PointInShape
         //
         VARIANT_BOOL bPointInShape;
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->Move(0.0, 0.5);

         ASSERT_EQ( shape->PointInShape(nullptr,&bPointInShape), E_INVALIDARG );
         ASSERT_EQ( shape->PointInShape(pnt,nullptr), E_POINTER );
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_TRUE );

         pnt->Move(500,500);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         pnt->Move(0,0); // Point on perimeter
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );
   }

   TEST_METHOD(TestIShape3)
   {
         CComPtr<IShape> shape;
         ASSERT_EQ( shape.CoCreateInstance( CLSID_NUBeam ), S_OK );
         CComQIPtr<INUBeam> beam(shape);

         // Use some real dimensions (NU2400 - 150mm web)
         beam->put_W1(1225);
         beam->put_W2(975);
         beam->put_D1(65);
         beam->put_D2(45);
         beam->put_D3(2015);
         beam->put_D4(140);
         beam->put_D5(135);
         beam->put_T(150);
         beam->put_R1(200);
         beam->put_R2(200);
         beam->put_R3(50);
         beam->put_R4(50);

         //
         // ClipWithLine
         //

         // setup clipping line
         CComPtr<IPoint2d> p1;
         p1.CoCreateInstance( CLSID_Point2d );

         CComPtr<IPoint2d> p2;
         p2.CoCreateInstance( CLSID_Point2d );

         p1->Move(-5000,1500);
         p2->Move( 5000,1500);

         CComPtr<ILine2d> clipLine;
         clipLine.CoCreateInstance( CLSID_Line2d );
         clipLine->ThroughPoints(p1,p2);

         CComPtr<IShape> clip;
         ASSERT_EQ(shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ(shape->ClipWithLine(clipLine,nullptr), E_POINTER );
         ASSERT_EQ(shape->ClipWithLine(clipLine,&clip), S_OK );
         ASSERT_EQ( clip != nullptr, true );

         // Verify clip by checking points
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         const IndexType nPoints = 172;
         CComPtr<IPoint2d> points[nPoints];
         ULONG fetched;
         Enum->Next(nPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, nPoints );

         coll.Release();
         ASSERT_EQ(clip->get_PolyPoints(&coll), S_OK );
         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, 90 );

         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });

         Enum.Release();
         coll->get__Enum(&Enum);
         Enum->Next(90,&points[0],&fetched);
         ASSERT_EQ( fetched, 90 );

         int i = 0;
         Float64 x,y;

         TEST_POINT(points, 0., 0.);
         TEST_POINT(points,-487.5, 0.);
         TEST_POINT(points,-487.5, 99.1684601);
         TEST_POINT(points,-487.4033721, 102.27546);
         TEST_POINT(points,-487.1138621, 105.370451);
         TEST_POINT(points,-486.6325887, 108.4414706);
         TEST_POINT(points,-485.9614123, 111.476649);
         TEST_POINT(points,-485.1029271, 114.4642548);
         TEST_POINT(points,-484.060451, 117.3927406);
         TEST_POINT(points,-482.8380135, 120.2507875);
         TEST_POINT(points,-481.4403395, 123.0273488);
         TEST_POINT(points,-479.8728309, 125.7116927);
         TEST_POINT(points,-478.1415466, 128.2934441);
         TEST_POINT(points,-476.253178, 130.762624);
         TEST_POINT(points,-474.215024, 133.1096889);
         TEST_POINT(points,-472.0349622, 135.3255671);
         TEST_POINT(points,-469.7214189, 137.4016939);
         TEST_POINT(points,-467.2833361, 139.3300449);
         TEST_POINT(points,-464.7301372, 141.1031668);
         TEST_POINT(points,-462.0716908, 142.7142063);
         TEST_POINT(points,-459.3182721, 144.1569365);
         TEST_POINT(points,-456.4805232, 145.425781);
         TEST_POINT(points,-453.5694124, 146.5158358);
         TEST_POINT(points,-210.7223506, 228.9366568);
         TEST_POINT(points,-199.0779074, 233.2968758);
         TEST_POINT(points,-187.7269118, 238.3722542);
         TEST_POINT(points,-176.7132366, 244.1431749);
         TEST_POINT(points,-166.079451, 250.5873328);
         TEST_POINT(points,-155.8666558, 257.6798204);
         TEST_POINT(points,-146.1143245, 265.3932244);
         TEST_POINT(points,-136.8601511, 273.6977317);
         TEST_POINT(points,-128.139904, 282.5612444);
         TEST_POINT(points,-119.9872879, 291.949504);
         TEST_POINT(points,-112.4338136, 301.8262237);
         TEST_POINT(points,-105.5086763, 312.1532291);
         TEST_POINT(points,-99.2386422, 322.8906049);
         TEST_POINT(points,-93.64794584, 333.99685);
         TEST_POINT(points,-88.75819588, 345.4290376);
         TEST_POINT(points,-84.58829176, 357.1429808);
         TEST_POINT(points,-81.15435063, 369.0934041);
         TEST_POINT(points,-78.46964506, 381.2341175);
         TEST_POINT(points,-76.54455176, 393.5181959);
         TEST_POINT(points,-75.38651142, 405.8981599);
         TEST_POINT(points,-75., 418.3261596);
         TEST_POINT(points,-75., 1500.0);
         TEST_POINT(points,75., 1500.0);
         TEST_POINT(points,75., 418.3261596);
         TEST_POINT(points,75.38651142, 405.8981599);
         TEST_POINT(points,76.54455176, 393.5181959);
         TEST_POINT(points,78.46964506, 381.2341175);
         TEST_POINT(points,81.15435063, 369.0934041);
         TEST_POINT(points,84.58829176, 357.1429808);
         TEST_POINT(points,88.75819588, 345.4290376);
         TEST_POINT(points,93.64794584, 333.99685);
         TEST_POINT(points,99.2386422, 322.8906049);
         TEST_POINT(points,105.5086763, 312.1532291);
         TEST_POINT(points,112.4338136, 301.8262237);
         TEST_POINT(points,119.9872879, 291.949504);
         TEST_POINT(points,128.139904, 282.5612444);
         TEST_POINT(points,136.8601511, 273.6977317);
         TEST_POINT(points,146.1143245, 265.3932244);
         TEST_POINT(points,155.8666558, 257.6798204);
         TEST_POINT(points,166.079451, 250.5873328);
         TEST_POINT(points,176.7132366, 244.1431749);
         TEST_POINT(points,187.7269118, 238.3722542);
         TEST_POINT(points,199.0779074, 233.2968758);
         TEST_POINT(points,210.7223506, 228.9366568);
         TEST_POINT(points,453.5694124, 146.5158358);
         TEST_POINT(points,456.4805232, 145.425781);
         TEST_POINT(points,459.3182721, 144.1569365);
         TEST_POINT(points,462.0716908, 142.7142063);
         TEST_POINT(points,464.7301372, 141.1031668);
         TEST_POINT(points,467.2833361, 139.3300449);
         TEST_POINT(points,469.7214189, 137.4016939);
         TEST_POINT(points,472.0349622, 135.3255671);
         TEST_POINT(points,474.215024, 133.1096889);
         TEST_POINT(points,476.253178, 130.762624);
         TEST_POINT(points,478.1415466, 128.2934441);
         TEST_POINT(points,479.8728309, 125.7116927);
         TEST_POINT(points,481.4403395, 123.0273488);
         TEST_POINT(points,482.8380135, 120.2507875);
         TEST_POINT(points,484.060451, 117.3927406);
         TEST_POINT(points,485.1029271, 114.4642548);
         TEST_POINT(points,485.9614123, 111.476649);
         TEST_POINT(points,486.6325887, 108.4414706);
         TEST_POINT(points,487.1138621, 105.370451);
         TEST_POINT(points,487.4033721, 102.27546);
         TEST_POINT(points,487.5, 99.1684601);
         TEST_POINT(points,487.5, 0.);
         TEST_POINT(points,0., 0.); // closed polygon... repeat first point

         ASSERT_EQ(i,cPoints);

         //
         // ClipIn
         //
         clip.Release();

         CComPtr<IRect2d> clipRect;
         clipRect.CoCreateInstance( CLSID_Rect2d );
         clipRect->put_Left(-5000);
         clipRect->put_Right(5000);
         clipRect->put_Top(10000);
         clipRect->put_Bottom(1500);

         ASSERT_EQ( shape->ClipIn(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ( shape->ClipIn(clipRect,nullptr), E_POINTER );
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK );

         // Verify clip by checking points
         coll.Release();
         Enum.Release();
         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


         ASSERT_EQ(clip->get_PolyPoints(&coll), S_OK );
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, 89 );

         coll->get__Enum(&Enum);
         Enum->Next(89,&points[0],&fetched);
         ASSERT_EQ( fetched, 89 );

         i = 0;

         TEST_POINT(points,-75., 1500.);
         TEST_POINT(points,-75., 2106.044491);
         TEST_POINT(points,-75.55273836, 2120.903489);
         TEST_POINT(points,-77.20789825, 2135.680355);
         TEST_POINT(points,-79.95633096, 2150.293413);
         TEST_POINT(points,-83.78284486, 2164.661891);
         TEST_POINT(points,-88.66628932, 2178.706367);
         TEST_POINT(points,-94.57967169, 2192.349213);
         TEST_POINT(points,-101.4903064, 2205.51502);
         TEST_POINT(points,-109.3599958, 2218.131015);
         TEST_POINT(points,-118.145241, 2230.127465);
         TEST_POINT(points,-127.7974827, 2241.438061);
         TEST_POINT(points,-138.2633691, 2252.000284);
         TEST_POINT(points,-149.4850513, 2261.755754);
         TEST_POINT(points,-161.4005028, 2270.650548);
         TEST_POINT(points,-173.9438624, 2278.635501);
         TEST_POINT(points,-187.0457979, 2285.666478);
         TEST_POINT(points,-200.6338901, 2291.704615);
         TEST_POINT(points,-214.6330323, 2296.716537);
         TEST_POINT(points,-228.9658458, 2300.674541);
         TEST_POINT(points,-243.5531078, 2303.556751);
         TEST_POINT(points,-258.3141889, 2305.347234);
         TEST_POINT(points,-566.6714528, 2331.163191);
         TEST_POINT(points,-570.361723, 2331.610812);
         TEST_POINT(points,-574.0085385, 2332.331365);
         TEST_POINT(points,-577.5917419, 2333.320866);
         TEST_POINT(points,-581.0915275, 2334.573846);
         TEST_POINT(points,-584.4885505, 2336.083381);
         TEST_POINT(points,-587.7640344, 2337.841125);
         TEST_POINT(points,-590.8998743, 2339.837363);
         TEST_POINT(points,-593.8787372, 2342.061061);
         TEST_POINT(points,-596.6841577, 2344.499929);
         TEST_POINT(points,-599.3006293, 2347.140485);
         TEST_POINT(points,-601.7136897, 2349.968134);
         TEST_POINT(points,-603.9100011, 2352.967246);
         TEST_POINT(points,-605.8774234, 2356.121245);
         TEST_POINT(points,-607.6050821, 2359.412697);
         TEST_POINT(points,-609.0834277, 2362.823408);
         TEST_POINT(points,-610.3042888, 2366.334527);
         TEST_POINT(points,-611.2609173, 2369.926647);
         TEST_POINT(points,-611.9480254, 2373.579911);
         TEST_POINT(points,-612.3618154, 2377.274128);
         TEST_POINT(points,-612.5, 2380.988877);
         TEST_POINT(points,-612.5, 2400.);
         TEST_POINT(points, 0., 2400.);
         TEST_POINT(points,612.5, 2400.);
         TEST_POINT(points,612.5, 2380.988877);
         TEST_POINT(points,612.3618154, 2377.274128);
         TEST_POINT(points,611.9480254, 2373.579911);
         TEST_POINT(points,611.2609173, 2369.926647);
         TEST_POINT(points,610.3042888, 2366.334527);
         TEST_POINT(points,609.0834277, 2362.823408);
         TEST_POINT(points,607.6050821, 2359.412697);
         TEST_POINT(points,605.8774234, 2356.121245);
         TEST_POINT(points,603.9100011, 2352.967246);
         TEST_POINT(points,601.7136897, 2349.968134);
         TEST_POINT(points,599.3006293, 2347.140485);
         TEST_POINT(points,596.6841577, 2344.499929);
         TEST_POINT(points,593.8787372, 2342.061061);
         TEST_POINT(points,590.8998743, 2339.837363);
         TEST_POINT(points,587.7640344, 2337.841125);
         TEST_POINT(points,584.4885505, 2336.083381);
         TEST_POINT(points,581.0915275, 2334.573846);
         TEST_POINT(points,577.5917419, 2333.320866);
         TEST_POINT(points,574.0085385, 2332.331365);
         TEST_POINT(points,570.361723, 2331.610812);
         TEST_POINT(points,566.6714528, 2331.163191);
         TEST_POINT(points,258.3141889, 2305.347234);
         TEST_POINT(points,243.5531078, 2303.556751);
         TEST_POINT(points,228.9658458, 2300.674541);
         TEST_POINT(points,214.6330323, 2296.716537);
         TEST_POINT(points,200.6338901, 2291.704615);
         TEST_POINT(points,187.0457979, 2285.666478);
         TEST_POINT(points,173.9438624, 2278.635501);
         TEST_POINT(points,161.4005028, 2270.650548);
         TEST_POINT(points,149.4850513, 2261.755754);
         TEST_POINT(points,138.2633691, 2252.000284);
         TEST_POINT(points,127.7974827, 2241.438061);
         TEST_POINT(points,118.145241, 2230.127465);
         TEST_POINT(points,109.3599958, 2218.131015);
         TEST_POINT(points,101.4903064, 2205.51502);
         TEST_POINT(points,94.57967169, 2192.349213);
         TEST_POINT(points,88.66628932, 2178.706367);
         TEST_POINT(points,83.78284486, 2164.661891);
         TEST_POINT(points,79.95633096, 2150.293413);
         TEST_POINT(points,77.20789825, 2135.680355);
         TEST_POINT(points,75.55273836, 2120.903489);
         TEST_POINT(points,75., 2106.044491);
         TEST_POINT(points,75., 1500.);

         ASSERT_EQ(i,cPoints);
   }

   TEST_METHOD(TestIXYPosition)
   {
         CComPtr<IXYPosition> position;
         ASSERT_EQ( position.CoCreateInstance( CLSID_NUBeam), S_OK);

         CComQIPtr<INUBeam> beam(position);
         CComQIPtr<IShape> shape(position);

         CComPtr<IPoint2d> hookPnt;
         hookPnt.CoCreateInstance( CLSID_Point2d );
         hookPnt->Move(0,0);

         // Use some real dimensions (NU2400 - 150mm web)
         beam->put_W1(1225);
         beam->put_W2(975);
         beam->put_D1(65);
         beam->put_D2(45);
         beam->put_D3(2015);
         beam->put_D4(140);
         beam->put_D5(135);
         beam->put_T(150);
         beam->put_R1(200);
         beam->put_R2(200);
         beam->put_R3(50);
         beam->put_R4(50);

         //
         // MoveEx (tests Offset as well)
         //
         CComPtr<IPoint2d> from;
         from.CoCreateInstance( CLSID_Point2d );
         from->Move(0,0);

         CComPtr<IPoint2d> to;
         to.CoCreateInstance( CLSID_Point2d );
         to->Move(100,100);

         ASSERT_EQ( position->MoveEx(nullptr,to), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,to), S_OK );

         //
         // OffsetEx
         //

         // Move the triangle back to where it was
         hookPnt->Move(0,0);

         CComPtr<ISize2d> size;
         size.CoCreateInstance( CLSID_Size2d );
         size->put_Dx(100);
         size->put_Dy(100);

         ASSERT_EQ(position->OffsetEx(nullptr), E_INVALIDARG );
         ASSERT_EQ(position->OffsetEx(size), S_OK);

         //
         // RotateEx (Provides coverage of Rotate)
         //
         hookPnt->Move(0,0);
         CComPtr<IPoint2d> c;
         c.CoCreateInstance( CLSID_Point2d );
         c->put_X(0);
         c->put_Y(0);

         ASSERT_EQ( position->RotateEx(nullptr,M_PI), E_INVALIDARG );
         ASSERT_EQ( position->RotateEx(c,M_PI), S_OK );
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_NUBeam ), S_OK );
         ASSERT_EQ( eInfo != nullptr, true );

         // Interfaces that should be supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_INUBeam ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

         // Interface that is not supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests