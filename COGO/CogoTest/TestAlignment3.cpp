///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2013  Washington State Department of Transportation
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

// TestAlignment3.cpp: implementation of the CTestAlignment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAlignment3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAlignment3::CTestAlignment3()
{

}

void CTestAlignment3::Test()
{
   Test1();
   Test2();
   Test3();
   Test4();
//   Test5();
}

void CTestAlignment3::Test1()
{
   // Test sub path with no-point alignment
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IAlignment> subAlignment;
   // sub path that captures entire element
   TRY_TEST(alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(300),NULL), E_POINTER);
   TRY_TEST(alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(300),&subAlignment), S_OK);

   CollectionIndexType nElements;
   subAlignment->get_Count(&nElements);

   TRY_TEST(nElements,2);

   CComPtr<IPathElement> element;
   subAlignment->get_Item(0,&element);

   PathElementType type;
   element->get_Type(&type);
   TRY_TEST(type,petPoint);

   CComPtr<IUnknown> punk;
   element->get_Value(&punk);
   CComQIPtr<IPoint2d> pnt(punk);
   
   Float64 x,y;
   pnt->get_X(&x);
   pnt->get_Y(&y);

   TRY_TEST(IsEqual(x,-110.0),true);
   TRY_TEST(IsEqual(y,   0.0),true);

   element.Release();
   subAlignment->get_Item(1,&element);
   element->get_Type(&type);
   TRY_TEST(type,petLineSegment);

   punk.Release();
   element->get_Value(&punk);
   CComQIPtr<ILineSegment2d> ls(punk);
   CComPtr<IPoint2d> p1,p2;
   ls->get_StartPoint(&p1);
   ls->get_EndPoint(&p2);

   p1->get_X(&x);
   p1->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true);
   TRY_TEST( IsEqual(y,0.0), true);

   p2->get_X(&x);
   p2->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true);
   TRY_TEST( IsEqual(y,  0.0), true);

   // sub-Alignment that captures start
   subAlignment.Release();
   TRY_TEST(alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(-5.0),&subAlignment),S_OK);

   subAlignment->get_Count(&nElements);

   TRY_TEST(nElements,3);

   element.Release();
   subAlignment->get_Item(0,&element);

   element->get_Type(&type);
   TRY_TEST(type,petPoint);

   punk.Release();
   element->get_Value(&punk);
   pnt.Release();
   punk.QueryInterface(&pnt);
   pnt->get_X(&x);
   pnt->get_Y(&y);

   TRY_TEST(IsEqual(x,-110.0),true);
   TRY_TEST(IsEqual(y,   0.0),true);

   element.Release();
   subAlignment->get_Item(1,&element);
   punk.Release();
   element->get_Value(&punk);
   element->get_Type(&type);
   TRY_TEST(type,petPoint);
   pnt.Release();
   punk.QueryInterface(&pnt);
   pnt->get_X(&x);
   pnt->get_Y(&y);

   TRY_TEST(IsEqual(x,-110.0),true);
   TRY_TEST(IsEqual(y,   0.0),true);

   element.Release();
   subAlignment->get_Item(2,&element);
   punk.Release();
   element->get_Value(&punk);
   element->get_Type(&type);
   TRY_TEST(type,petPoint);
   pnt.Release();
   punk.QueryInterface(&pnt);
   pnt->get_X(&x);
   pnt->get_Y(&y);

   TRY_TEST(IsEqual(x,-105.0),true);
   TRY_TEST(IsEqual(y,   0.0),true);

   // sub-alignment that captures "middle"
   subAlignment.Release();
   TRY_TEST(alignment->CreateSubAlignment(CComVariant(110.0),CComVariant(200.0),&subAlignment),S_OK);

   subAlignment->get_Count(&nElements);

   TRY_TEST(nElements,2);

   element.Release();
   subAlignment->get_Item(1,&element);

   element->get_Type(&type);
   TRY_TEST(type,petLineSegment);

   punk.Release();
   element->get_Value(&punk);
   ls.Release();
   punk.QueryInterface(&ls);

   p1.Release();
   p2.Release();

   ls->get_StartPoint(&p1);
   ls->get_EndPoint(&p2);

   p1->get_X(&x);
   p1->get_Y(&y);
   TRY_TEST( IsEqual(x,  10.0), true);
   TRY_TEST( IsEqual(y,   0.0), true);

   p2->get_X(&x);
   p2->get_Y(&y);
   TRY_TEST( IsEqual(x, 100.0), true);
   TRY_TEST( IsEqual(y,   0.0), true);
}

void CTestAlignment3::Test2()
{
   // Test sub path with 2-point alignment
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> pnt1, pnt2;
   pnt1.CoCreateInstance(CLSID_Point2d);
   pnt2.CoCreateInstance(CLSID_Point2d);
   pnt1->Move(10,10);
   pnt2->Move(110,110);

   alignment->AddEx(pnt1);
   alignment->AddEx(pnt2);

   CComPtr<IAlignment> subAlignment;
   // sub alignment that captures entire element
   TRY_TEST(alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(300),NULL), E_POINTER);
   TRY_TEST(alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(300),&subAlignment), S_OK);

   CollectionIndexType nElements;
   subAlignment->get_Count(&nElements);

   TRY_TEST(nElements,2);

   CComPtr<IPathElement> element;
   subAlignment->get_Item(0,&element);

   PathElementType type;
   element->get_Type(&type);
   TRY_TEST(type,petPoint);

   CComPtr<IUnknown> punk;
   element->get_Value(&punk);
   CComQIPtr<IPoint2d> pnt(punk);
   Float64 x,y;
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-67.781745930520231),true);
   TRY_TEST(IsEqual(y,-67.781745930520231),true);

   element.Release();
   subAlignment->get_Item(1,&element);

   element->get_Type(&type);
   TRY_TEST(type,petLineSegment);

   punk.Release();
   element->get_Value(&punk);
   CComQIPtr<ILineSegment2d> ls(punk);
   CComPtr<IPoint2d> p1,p2;
   ls->get_StartPoint(&p1);
   ls->get_EndPoint(&p2);

   p1->get_X(&x);
   p1->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true);
   TRY_TEST( IsEqual(y,10.0), true);

   p2->get_X(&x);
   p2->get_Y(&y);
   TRY_TEST( IsEqual(x,110.0), true);
   TRY_TEST( IsEqual(y,110.0), true);

   // sub-alignment that captures start
   subAlignment.Release();
   TRY_TEST(alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(-5.0),&subAlignment),S_OK);

   subAlignment->get_Count(&nElements);

   TRY_TEST(nElements,3);

   element.Release();
   subAlignment->get_Item(0,&element);

   element->get_Type(&type);
   TRY_TEST(type,petPoint);

   punk.Release();
   element->get_Value(&punk);
   pnt.Release();
   punk.QueryInterface(&pnt);
   pnt->get_X(&x);
   pnt->get_Y(&y);

   TRY_TEST(IsEqual(x,-67.781745930520231),true);
   TRY_TEST(IsEqual(y,-67.781745930520231),true);

   element.Release();
   subAlignment->get_Item(1,&element);
   punk.Release();
   element->get_Value(&punk);
   element->get_Type(&type);
   TRY_TEST(type,petPoint);
   pnt.Release();
   punk.QueryInterface(&pnt);
   pnt->get_X(&x);
   pnt->get_Y(&y);

   TRY_TEST(IsEqual(x,-67.781745930520231),true);
   TRY_TEST(IsEqual(y,-67.781745930520231),true);

   element.Release();
   subAlignment->get_Item(2,&element);
   punk.Release();
   element->get_Value(&punk);
   element->get_Type(&type);
   TRY_TEST(type,petPoint);
   pnt.Release();
   punk.QueryInterface(&pnt);
   pnt->get_X(&x);
   pnt->get_Y(&y);

   TRY_TEST(IsEqual(x,-64.246212024587493),true);
   TRY_TEST(IsEqual(y,-64.246212024587493),true);

   // sub-alignment that captures "middle"
   subAlignment.Release();
   TRY_TEST(alignment->CreateSubAlignment(CComVariant(110.0),CComVariant(200.0),&subAlignment),S_OK);

   subAlignment->get_Count(&nElements);

   TRY_TEST(nElements,2);

   element.Release();
   subAlignment->get_Item(1,&element);

   element->get_Type(&type);
   TRY_TEST(type,petLineSegment);

   punk.Release();
   element->get_Value(&punk);
   ls.Release();
   punk.QueryInterface(&ls);

   p1.Release();
   p2.Release();

   ls->get_StartPoint(&p1);
   ls->get_EndPoint(&p2);

   p1->get_X(&x);
   p1->get_Y(&y);
   TRY_TEST( IsEqual(x,17.071067811865476), true);
   TRY_TEST( IsEqual(y,17.071067811865476), true);

   p2->get_X(&x);
   p2->get_Y(&y);
   TRY_TEST( IsEqual(x,80.710678118654755), true);
   TRY_TEST( IsEqual(y,80.710678118654755), true);

   CompareAlignments(alignment,subAlignment,110,200,10);
}

void CTestAlignment3::Test3()
{
   // Alignment consisting of a single horizontal curve
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(0,0);
   pi->Move(1000,0);
   pft->Move(5000,5000);

   CComPtr<IHorzCurve> hc;
   hc.CoCreateInstance(CLSID_HorzCurve);
   hc->putref_PBT(pbt);
   hc->putref_PI(pi);
   hc->putref_PFT(pft);
   hc->put_Radius(500);
   hc->put_SpiralLength(spEntry,20);
   hc->put_SpiralLength(spExit, 30);

   alignment->AddEx(hc);

   CComPtr<IAlignment> subAlignment;

   // sub alignment that captures entire element
   TRY_TEST(alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(300),NULL), E_POINTER);

   // start on back tangent, end in circular curve
   TRY_TEST(alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(300),&subAlignment), S_OK);

   CompareAlignments(alignment,subAlignment,-10,300,10);

   CollectionIndexType nElements;
   subAlignment->get_Count(&nElements);

   TRY_TEST(nElements,2);

   CComPtr<IPathElement> element;
   subAlignment->get_Item(0,&element);

   PathElementType type;
   element->get_Type(&type);
   TRY_TEST(type,petPoint);

   CComPtr<IUnknown> punk;
   element->get_Value(&punk);
   CComQIPtr<IPoint2d> pnt(punk);
   Float64 x,y;
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,639.61833209788472),true);
   TRY_TEST(IsEqual(y,  0.),true);

   element.Release();
   subAlignment->get_Item(1,&element);
   element->get_Type(&type);
   TRY_TEST(type,petHorzCurve);

   punk.Release();
   element->get_Value(&punk);
   CComQIPtr<IHorzCurve> objHC(punk);

   Float64 value;
   objHC->get_Radius(&value);
   TRY_TEST( IsEqual(value,500.), true);

   objHC->get_SpiralLength(spEntry,&value);
   TRY_TEST( IsEqual(value,20.), true);

   objHC->get_SpiralLength(spExit,&value);
   TRY_TEST( IsEqual(value,0.), true);

   // start on back tangent and end in entry spiral
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(110.),&subAlignment);
   CompareAlignments(alignment,subAlignment,-10.0,110.0,10);

   // start on back tangent and end in exit spiral
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(550.),&subAlignment);
   CompareAlignments(alignment,subAlignment,-10.0,550.0,10);

   // start on back tangent and end on forward tangent
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(-10.0),CComVariant(800.),&subAlignment);
   CompareAlignments(alignment,subAlignment,-10.0,800.0,10);

   // start in entry spiral, end in entry spiral
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(110.),CComVariant(118.),&subAlignment);
   CompareAlignments(alignment,subAlignment,110.0,118.0,10);

   // start in entry spiral, end in circular curve
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(110.),CComVariant(300.),&subAlignment);
   CompareAlignments(alignment,subAlignment,110.0,300.0,10);

   // start in entry spiral, end in exit spiral
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(110.),CComVariant(560.),&subAlignment);
   CompareAlignments(alignment,subAlignment,110.0,560.0,10);

   // start in entry spiral, end on fwd tangent
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(110.),CComVariant(800.),&subAlignment);
   CompareAlignments(alignment,subAlignment,110.0,800.0,10);

   // start and end in circular curve
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(200.),CComVariant(500.),&subAlignment);
   CompareAlignments(alignment,subAlignment,200.0,500.0,10);

   // start in circular curve, end in exit spiral
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(300.),CComVariant(550.),&subAlignment);
   CompareAlignments(alignment,subAlignment,300.0,550.0,10);

   // start in circular curve, end in fwd tangent
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(300.),CComVariant(1000.),&subAlignment);
   CompareAlignments(alignment,subAlignment,300.0,1000.0,10);

   // start in exit spiral, end in exit spiral
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(545.),CComVariant(570.),&subAlignment);
   CompareAlignments(alignment,subAlignment,545.0,570.0,10);

   // start in exit spiral, end in fwd tangent
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(545.),CComVariant(1000.),&subAlignment);
   CompareAlignments(alignment,subAlignment,545.0,1000.0,10);

   // start and end on back tangent
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(-10.),CComVariant(50.),&subAlignment);
   CompareAlignments(alignment,subAlignment,-10.0,50.0,10);

   // start and end on fwd tangent
   subAlignment.Release();
   alignment->CreateSubAlignment(CComVariant(600.),CComVariant(800.),&subAlignment);
   CompareAlignments(alignment,subAlignment,600.0,800.0,10);
}


void CTestAlignment3::Test4()
{
   // Alignment consisting of a spline
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   Float64 refStation = 100.;
   alignment->put_RefStation(CComVariant(refStation));

   CComPtr<ICubicSpline> spline;
   spline.CoCreateInstance(CLSID_CubicSpline);

   spline->AddPoint(5,5);
   spline->AddPoint(8,7);
   spline->AddPoint(13,9);
   spline->AddPoint(16,10);
   spline->AddPoint(17,15);
   spline->AddPoint(22,16);

   spline->put_StartDirection(CComVariant(M_PI/4));
   spline->put_EndDirection(CComVariant(M_PI/6));

   Float64 Ls;
   spline->get_Length(&Ls);
   alignment->AddEx(spline);

   // full length of spline
   CComPtr<IAlignment> subAlignment;
   Float64 startStation = refStation;
   Float64 endStation = startStation+Ls;
   alignment->CreateSubAlignment(CComVariant(startStation),CComVariant(endStation),&subAlignment);
   CompareAlignments(alignment,subAlignment,startStation,endStation,10);


   // before spline
   subAlignment.Release();
   startStation = refStation-50;
   endStation = startStation+49;
   alignment->CreateSubAlignment(CComVariant(startStation),CComVariant(endStation),&subAlignment);
   CompareAlignments(alignment,subAlignment,startStation,endStation,10);


   // after spline
   subAlignment.Release();
   startStation = refStation+Ls+50;
   endStation = startStation+50;
   alignment->CreateSubAlignment(CComVariant(startStation),CComVariant(endStation),&subAlignment);
   CompareAlignments(alignment,subAlignment,startStation,endStation,10);

   // mid-spline
   subAlignment.Release();
   startStation = refStation+int(Ls/4);
   endStation = startStation+int(Ls/2);
   alignment->CreateSubAlignment(CComVariant(startStation),CComVariant(endStation),&subAlignment);
   CompareAlignments(alignment,subAlignment,startStation,endStation,10);

   // start before spline, end mid-spline
   subAlignment.Release();
   startStation = refStation-20;
   endStation = startStation+3*Ls/4;
   alignment->CreateSubAlignment(CComVariant(startStation),CComVariant(endStation),&subAlignment);
   CompareAlignments(alignment,subAlignment,startStation,endStation,10);

   // start mid-spline, end after spline
   subAlignment.Release();
   startStation = refStation+Ls/4;
   endStation = startStation+Ls+10;
   alignment->CreateSubAlignment(CComVariant(startStation),CComVariant(endStation),&subAlignment);
   CompareAlignments(alignment,subAlignment,startStation,endStation,10);
}
//
//void CTestAlignment3::Test5()
//{
//   // Alignment consisting of a two line segments
//   CComPtr<IAlignment> alignment;
//   alignment.CoCreateInstance(CLSID_Alignment);
//
//   alignment->put_RefStation(CComVariant(100.00));
//
//   CComPtr<IPoint2d> p1, p2, p3, p4;
//   p1.CoCreateInstance(CLSID_Point2d);
//   p2.CoCreateInstance(CLSID_Point2d);
//   p3.CoCreateInstance(CLSID_Point2d);
//   p4.CoCreateInstance(CLSID_Point2d);
//
//   p1->Move(0,0);
//   p2->Move(10,0);
//   p3->Move(10,10);
//   p4->Move(20,10);
//
//   CComPtr<ILineSegment2d> ls1, ls2;
//   ls1.CoCreateInstance(CLSID_LineSegment2d);
//   ls2.CoCreateInstance(CLSID_LineSegment2d);
//
//   ls1->putref_StartPoint(p1);
//   ls1->putref_EndPoint(p2);
//   ls2->putref_StartPoint(p3);
//   ls2->putref_EndPoint(p4);
//
//   alignment->AddEx(ls1);
//   alignment->AddEx(ls2);
//
//   //////////////
//   // Bearing,Normal,LocatePoint, Station, and Offset
//   CComPtr<IDirection> dir;
//   Float64 dirVal;
//   CComPtr<IPoint2d> pnt;
//   Float64 x,y;
//   CComPtr<IStation> station;
//   Float64 stationVal, offset;
//
//   // Sta 1+15
//   TRY_TEST(alignment->Bearing(CComVariant(115.00),&dir),S_OK);
//   dir->get_Value(&dirVal);
//   TRY_TEST(IsEqual(dirVal,PI_OVER_2),true);
//
//   dir.Release();
//   TRY_TEST(alignment->Normal(CComVariant(115.00),&dir),S_OK);
//   dir->get_Value(&dirVal);
//   TRY_TEST(IsEqual(dirVal,0.0),true);
//   pnt.Release();
//
//   TRY_TEST(alignment->LocatePoint(CComVariant(115),omtAlongDirection, 3,CComVariant(dirVal),&pnt),S_OK);
//   pnt->get_X(&x);
//   pnt->get_Y(&y);
//   TRY_TEST(IsEqual(x, 13.0),true);
//   TRY_TEST(IsEqual(y,  5.0),true);
//
//   station.Release();
//   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
//   TRY_TEST(IsEqual(offset,3.0),true);
//   station->get_Value(&stationVal);
//   TRY_TEST(IsEqual(stationVal,115.00),true);
//}

void CTestAlignment3::CompareAlignments(IAlignment* pAlignment1,IAlignment* pAlignment2,Float64 start,Float64 end,long nPoints)
{
   Float64 x1,y1;
   Float64 x2,y2;
   for ( long i = 0; i < nPoints; i++ )
   {
      Float64 station = start + (end-start)*i/(nPoints-1);
      CComPtr<IPoint2d> point;
      pAlignment1->LocatePoint(CComVariant(station),omtAlongDirection, 0.00,CComVariant(0.00),&point);

      point->get_X(&x1);
      point->get_Y(&y1);

      point.Release();
      pAlignment2->LocatePoint(CComVariant(station),omtAlongDirection, 0.00,CComVariant(0.00),&point);

      point->get_X(&x2);
      point->get_Y(&y2);

      // I think the error may accumulate over the lenght of the sub-spline????
      TRY_TEST(IsEqual(x1,x2,0.2),true);
      TRY_TEST(IsEqual(y1,y2,0.2),true);

      CComPtr<IDirection> d1,d2;
      Float64 value1,value2;
      pAlignment1->Normal(CComVariant(station),&d1);
      pAlignment2->Normal(CComVariant(station),&d2);

      d1->get_Value(&value1);
      d2->get_Value(&value2);
      TRY_TEST(IsEqual(value1,value2,0.2),true);
   }
}
