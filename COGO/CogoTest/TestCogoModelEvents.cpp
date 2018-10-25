///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TestCogoModelEvents.cpp: implementation of the CTestCogoModelEvents class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCogoModelEvents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCogoModelEvents::CTestCogoModelEvents()
{

}

void CTestCogoModelEvents::Test()
{
   CComPtr<ICogoModel> model;
   model.CoCreateInstance(CLSID_CogoModel);

   CComObject<CTestCogoModelEvents>* pTestCogoModel;
   CComObject<CTestCogoModelEvents>::CreateInstance(&pTestCogoModel);
   pTestCogoModel->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestCogoModel);
   TRY_TEST(AtlAdvise(model,punk,IID_ICogoModelEvents,&dwCookie),S_OK);

   // Points
   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   pTestCogoModel->InitEventTest();
   points->Clear();
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   points->Add(1,20,30,nullptr);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   CComPtr<IPoint2d> point;
   points->get_Item(1,&point);

   pTestCogoModel->InitEventTest();
   point->Move(50,50);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   points->Remove(1);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   // LineSegments
   CComPtr<ILineSegmentCollection> lines;
   model->get_LineSegments(&lines);

   pTestCogoModel->InitEventTest();
   lines->Clear();
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   lines->Add(1,point,point,nullptr);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   CComPtr<ILineSegment2d> ls;
   lines->get_Item(1,&ls);

   pTestCogoModel->InitEventTest();
   ls->putref_StartPoint(point);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   lines->Remove(1);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   // ProfilePoints
   CComPtr<IProfilePointCollection> profilePoints;
   model->get_ProfilePoints(&profilePoints);

   pTestCogoModel->InitEventTest();
   profilePoints->Clear();
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   profilePoints->Add(1,CComVariant(20),30,nullptr);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   CComPtr<IProfilePoint> pp;
   profilePoints->get_Item(1,&pp);

   pTestCogoModel->InitEventTest();
   pp->put_Station(CComVariant(10));
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   pp->put_Elevation(10);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   profilePoints->Remove(1);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   // VertCurve
   CComPtr<IVertCurveCollection> vcurves;
   model->get_VertCurves(&vcurves);

   CComPtr<IProfilePoint> bvc, pvi, evc;
   bvc.CoCreateInstance(CLSID_ProfilePoint);
   pvi.CoCreateInstance(CLSID_ProfilePoint);
   evc.CoCreateInstance(CLSID_ProfilePoint);

   pTestCogoModel->InitEventTest();
   vcurves->Clear();
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   vcurves->Add(1,bvc,pvi,evc,400,400,nullptr);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   CComPtr<IVertCurve> vc;
   vcurves->get_Item(1,&vc);

   pTestCogoModel->InitEventTest();
   vc->putref_PBG(bvc);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   vcurves->Remove(1);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   // HorzCurve
   CComPtr<IHorzCurveCollection> hcurves;
   model->get_HorzCurves(&hcurves);

   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pTestCogoModel->InitEventTest();
   hcurves->Clear();
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   hcurves->Add(1,pbt,pi,pft,500,100,200,nullptr);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   CComPtr<IHorzCurve> hc;
   hcurves->get_Item(1,&hc);

   pTestCogoModel->InitEventTest();
   hc->putref_PBT(pbt);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   pTestCogoModel->InitEventTest();
   hcurves->Remove(1);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   // Alignment
   CComPtr<IAlignmentCollection> alignments;
   model->get_Alignments(&alignments);
   pTestCogoModel->InitEventTest();
   TRY_TEST(alignments->Add(1,nullptr),S_OK);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   CComPtr<IAlignment> alignment;
   alignments->get_Item(1,&alignment);
   point.Release();
   point.CoCreateInstance(CLSID_Point2d);

   pTestCogoModel->InitEventTest();
   alignment->AddEx(point);
   TRY_TEST(pTestCogoModel->PassedEventTest(),true);

   pTestCogoModel->InitEventTest();
   point->Move(10,10);
   TRY_TEST(pTestCogoModel->PassedEventTest(),true);

   pp.Release();
   pp.CoCreateInstance(CLSID_ProfilePoint);
   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);
   pTestCogoModel->InitEventTest();
   profile->AddEx(pp);
   TRY_TEST(pTestCogoModel->PassedEventTest(),true);

   CComPtr<IStationEquationCollection> equations;
   alignment->get_StationEquations(&equations);
   pTestCogoModel->InitEventTest();
   CComPtr<IStationEquation> equation;
   equations->Add(10,50,&equation);
   TRY_TEST(pTestCogoModel->PassedEventTest(),true);

   alignments->Add(2,nullptr);
   pTestCogoModel->InitEventTest();
   alignments->Remove(1);
   TRY_TEST(pTestCogoModel->PassedEventTest(),true);

   pTestCogoModel->InitEventTest();
   alignments->Clear();
   TRY_TEST(pTestCogoModel->PassedEventTest(),true);

   // Path
   CComPtr<IPathCollection> paths;
   model->get_Paths(&paths);
   pTestCogoModel->InitEventTest();
   TRY_TEST(paths->Add(1,nullptr),S_OK);
   TRY_TEST(pTestCogoModel->PassedEventTest(), true );

   CComPtr<IPath> path;
   paths->get_Item(1,&path);
   point.Release();
   point.CoCreateInstance(CLSID_Point2d);

   pTestCogoModel->InitEventTest();
   path->AddEx(point);
   TRY_TEST(pTestCogoModel->PassedEventTest(),true);

   pTestCogoModel->InitEventTest();
   point->Move(10,10);
   TRY_TEST(pTestCogoModel->PassedEventTest(),true);

   paths->Add(2,nullptr);
   pTestCogoModel->InitEventTest();
   paths->Remove(1);
   TRY_TEST(pTestCogoModel->PassedEventTest(),true);

   pTestCogoModel->InitEventTest();
   paths->Clear();
   TRY_TEST(pTestCogoModel->PassedEventTest(),true);
   
   // Clean up
   TRY_TEST(AtlUnadvise(model,IID_ICogoModelEvents,dwCookie),S_OK);
   pTestCogoModel->Release();
}

STDMETHODIMP CTestCogoModelEvents::OnPointChanged(ICogoModel* cm,CogoObjectID key,IPoint2d* point)
{
//   ::MessageBox(nullptr,"OnPointChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnPointAdded(ICogoModel* cm,CogoObjectID key,IPoint2d* point)
{
//   ::MessageBox(nullptr,"OnPointAdded","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnPointRemoved(ICogoModel* cm,CogoObjectID key)
{
//   ::MessageBox(nullptr,"OnPointRemoved","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnPointsCleared(ICogoModel* cm)
{
//   ::MessageBox(nullptr,"OnPointsCleared","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnLineSegmentChanged(ICogoModel* cm,CogoObjectID key,ILineSegment2d* lineSeg)
{
//   ::MessageBox(nullptr,"OnLineSegmentChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnLineSegmentAdded(ICogoModel* cm,CogoObjectID key,ILineSegment2d* lineSeg)
{
//   ::MessageBox(nullptr,"OnLineSegmentAdded","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnLineSegmentRemoved(ICogoModel* cm,CogoObjectID key)
{
//   ::MessageBox(nullptr,"OnLineSegmentRemoved","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnLineSegmentsCleared(ICogoModel* cm)
{
//   ::MessageBox(nullptr,"OnLineSegmentsCleared","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnProfilePointChanged(ICogoModel* cm,CogoObjectID key,IProfilePoint* pp)
{
//   ::MessageBox(nullptr,"OnProfilePointChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnProfilePointAdded(ICogoModel* cm,CogoObjectID key,IProfilePoint* pp)
{
//   ::MessageBox(nullptr,"OnProfilePointAdded","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnProfilePointRemoved(ICogoModel* cm,CogoObjectID key)
{
//   ::MessageBox(nullptr,"OnProfilePointRemoved","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnProfilePointsCleared(ICogoModel* cm)
{
//   ::MessageBox(nullptr,"OnProfilePointsCleared","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnVertCurveChanged(ICogoModel* cm,CogoObjectID key,IVertCurve* vc)
{
//   ::MessageBox(nullptr,"OnVertCurveChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnVertCurveAdded(ICogoModel* cm,CogoObjectID key,IVertCurve* vc)
{
//   ::MessageBox(nullptr,"OnVertCurveAdded","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnVertCurveRemoved(ICogoModel* cm,CogoObjectID key)
{
//   ::MessageBox(nullptr,"OnVertCurveRemoved","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnVertCurvesCleared(ICogoModel* cm)
{
//   ::MessageBox(nullptr,"OnVertCurvesCleared","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnHorzCurveChanged(ICogoModel* cm,CogoObjectID key,IHorzCurve* vc)
{
//   ::MessageBox(nullptr,"OnHorzCurveChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnHorzCurveAdded(ICogoModel* cm,CogoObjectID key,IHorzCurve* vc)
{
//   ::MessageBox(nullptr,"OnHorzCurveAdded","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnHorzCurveRemoved(ICogoModel* cm,CogoObjectID key)
{
//   ::MessageBox(nullptr,"OnHorzCurveRemoved","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnHorzCurvesCleared(ICogoModel* cm)
{
//   ::MessageBox(nullptr,"OnHorzCurvesCleared","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnAlignmentChanged(ICogoModel* cm,CogoObjectID key, IAlignment* alignment)
{
//   ::MessageBox(nullptr,"OnAlignmentChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnProfileChanged(ICogoModel* cm,IProfile* profile)
{
//   ::MessageBox(nullptr,"OnProfileChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnStationEquationsChanged(ICogoModel* cm,IStationEquationCollection* equations)
{
//   ::MessageBox(nullptr,"OnStationEquationsChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnAlignmentAdded(ICogoModel* cm,CogoObjectID key,IAlignment* alignment)
{
//   ::MessageBox(nullptr,"OnAlignmentAdded","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnAlignmentRemoved(ICogoModel* cm,CogoObjectID key)
{
//   ::MessageBox(nullptr,"OnAlignmentRemoved","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnAlignmentsCleared(ICogoModel* cm)
{
//   ::MessageBox(nullptr,"OnAlignmentsCleared","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnPathChanged(ICogoModel* cm,CogoObjectID key, IPath* path)
{
//   ::MessageBox(nullptr,"OnPathChanged","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnPathAdded(ICogoModel* cm,CogoObjectID key,IPath* path)
{
//   ::MessageBox(nullptr,"OnPathAdded","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnPathRemoved(ICogoModel* cm,CogoObjectID key)
{
//   ::MessageBox(nullptr,"OnPathRemoved","Event",MB_OK);
   Pass();
   return S_OK;
}

STDMETHODIMP CTestCogoModelEvents::OnPathsCleared(ICogoModel* cm)
{
//   ::MessageBox(nullptr,"OnPathsCleared","Event",MB_OK);
   Pass();
   return S_OK;
}
