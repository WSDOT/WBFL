///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// TestNUBeam.cpp: implementation of the CTestNUBeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestNUBeam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CTestNUBeam::TestIShape3()
{
   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_NUBeam ), S_OK );
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
   TRY_TEST(shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
   TRY_TEST(shape->ClipWithLine(clipLine,nullptr), E_POINTER );
   TRY_TEST(shape->ClipWithLine(clipLine,&clip), S_OK );
   TRY_TEST( clip != nullptr, true );
   
   // Verify clip by checking points
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   const IndexType nPoints = 172;
   CComPtr<IPoint2d> points[nPoints];
   ULONG fetched;
   Enum->Next(nPoints,&points[0],&fetched);
   TRY_TEST( fetched, nPoints );

   coll.Release();
   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   IndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 90 );

   std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });

   Enum.Release();
   coll->get__Enum(&Enum);
   Enum->Next(90,&points[0],&fetched);
   TRY_TEST( fetched, 90 );

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

   TRY_TEST(i,cPoints);

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

   TRY_TEST( shape->ClipIn(nullptr,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipIn(clipRect,nullptr), E_POINTER );
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 89 );

   coll->get__Enum(&Enum);
   Enum->Next(89,&points[0],&fetched);
   TRY_TEST( fetched, 89 );

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

   TRY_TEST(i,cPoints);
}
