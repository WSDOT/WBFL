///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2018  Washington State Department of Transportation
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

// TestCogoModel.cpp: implementation of the CTestCogoModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCogoModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCogoModel::CTestCogoModel()
{

}

CTestCogoModel::~CTestCogoModel()
{

}

void CTestCogoModel::Test()
{
   CComPtr<ICogoModel> model;
   TRY_TEST(model.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComPtr<IPointCollection> points;
   TRY_TEST(model->get_Points(nullptr),E_POINTER);
   TRY_TEST(model->get_Points(&points),S_OK);

   CComPtr<ILineSegmentCollection> lines;
   TRY_TEST(model->get_LineSegments(nullptr),E_POINTER);
   TRY_TEST(model->get_LineSegments(&lines),S_OK);

   CComPtr<IProfilePointCollection> profilePoints;
   TRY_TEST(model->get_ProfilePoints(nullptr),E_POINTER);
   TRY_TEST(model->get_ProfilePoints(&profilePoints),S_OK);

   CComPtr<IVertCurveCollection> vertCurves;
   TRY_TEST(model->get_VertCurves(nullptr),E_POINTER);
   TRY_TEST(model->get_VertCurves(&vertCurves),S_OK);

   CComPtr<IHorzCurveCollection> horzCurves;
   TRY_TEST(model->get_HorzCurves(nullptr),E_POINTER);
   TRY_TEST(model->get_HorzCurves(&horzCurves),S_OK);

   CComPtr<IAlignmentCollection> alignments;
   TRY_TEST(model->get_Alignments(nullptr),E_POINTER);
   TRY_TEST(model->get_Alignments(&alignments),S_OK);

   // Test Clear
   points->Add(1,5,5,nullptr);
   points->Add(2,15,15,nullptr);
   points->Add(3,25,25,nullptr);
   CComPtr<IPoint2d> p1, p2, p3;
   points->get_Item(1,&p1);
   points->get_Item(2,&p2);
   points->get_Item(3,&p3);
   lines->Add(1,p1,p2,nullptr);
   profilePoints->Add(1,CComVariant(50),50,nullptr);
   profilePoints->Add(2,CComVariant(150),150,nullptr);
   profilePoints->Add(3,CComVariant(250),250,nullptr);
   CComPtr<IProfilePoint> bvc, pvi, evc;
   profilePoints->get_Item(1,&bvc);
   profilePoints->get_Item(2,&pvi);
   profilePoints->get_Item(3,&evc);
   vertCurves->Add(1,bvc,pvi,evc,400,400,nullptr);
   horzCurves->Add(1,p1,p2,p3,50,1,1,nullptr);
   alignments->Add(1,nullptr);

   TRY_TEST(model->Clear(),S_OK);
   CollectionIndexType count;
   points->get_Count(&count);
   TRY_TEST(count,0);
   lines->get_Count(&count);
   TRY_TEST(count,0);
   profilePoints->get_Count(&count);
   TRY_TEST(count,0);
   vertCurves->get_Count(&count);
   TRY_TEST(count,0);
   horzCurves->get_Count(&count);
   TRY_TEST(count,0);
   alignments->get_Count(&count);
   TRY_TEST(count,0);


   // Test factories
   CComPtr<IPoint2dFactory> pointFactory;
   TRY_TEST(model->get_PointFactory(nullptr),E_POINTER);
   TRY_TEST(model->get_PointFactory(&pointFactory),S_OK);
   TRY_TEST(pointFactory != nullptr, true);
   TRY_TEST(model->putref_PointFactory(nullptr),E_INVALIDARG);
   TRY_TEST(model->putref_PointFactory(pointFactory),S_OK);

   CComPtr<ILineSegment2dFactory> lsFactory;
   TRY_TEST(model->get_LineSegmentFactory(nullptr),E_POINTER);
   TRY_TEST(model->get_LineSegmentFactory(&lsFactory),S_OK);
   TRY_TEST(lsFactory != nullptr, true);
   TRY_TEST(model->putref_LineSegmentFactory(nullptr),E_INVALIDARG);
   TRY_TEST(model->putref_LineSegmentFactory(lsFactory),S_OK);

   CComPtr<IProfilePointFactory> ppFactory;
   TRY_TEST(model->get_ProfilePointFactory(nullptr),E_POINTER);
   TRY_TEST(model->get_ProfilePointFactory(&ppFactory),S_OK);
   TRY_TEST(ppFactory != nullptr, true);
   TRY_TEST(model->putref_ProfilePointFactory(nullptr),E_INVALIDARG);
   TRY_TEST(model->putref_ProfilePointFactory(ppFactory),S_OK);

   CComPtr<IVertCurveFactory> vcFactory;
   TRY_TEST(model->get_VertCurveFactory(nullptr),E_POINTER);
   TRY_TEST(model->get_VertCurveFactory(&vcFactory),S_OK);
   TRY_TEST(vcFactory != nullptr, true);
   TRY_TEST(model->putref_VertCurveFactory(nullptr),E_INVALIDARG);
   TRY_TEST(model->putref_VertCurveFactory(vcFactory),S_OK);

   CComPtr<IHorzCurveFactory> hcFactory;
   TRY_TEST(model->get_HorzCurveFactory(nullptr),E_POINTER);
   TRY_TEST(model->get_HorzCurveFactory(&hcFactory),S_OK);
   TRY_TEST(hcFactory != nullptr, true);
   TRY_TEST(model->putref_HorzCurveFactory(nullptr),E_INVALIDARG);
   TRY_TEST(model->putref_HorzCurveFactory(hcFactory),S_OK);

   CComPtr<IAlignmentFactory> alignmentFactory;
   TRY_TEST(model->get_AlignmentFactory(nullptr),E_POINTER);
   TRY_TEST(model->get_AlignmentFactory(&alignmentFactory),S_OK);
   TRY_TEST(alignmentFactory != nullptr, true);
   TRY_TEST(model->putref_AlignmentFactory(nullptr),E_INVALIDARG);
   TRY_TEST(model->putref_AlignmentFactory(alignmentFactory),S_OK);
   
   CComPtr<ILocate> locate;
   TRY_TEST(model->get_Locate(nullptr),E_POINTER);
   TRY_TEST(model->get_Locate(&locate),S_OK);
   TRY_TEST(model.IsEqualObject(locate),true);
   locate.Release();

   CComPtr<IIntersect> intersect;
   TRY_TEST(model->get_Intersect(nullptr),E_POINTER);
   TRY_TEST(model->get_Intersect(&intersect),S_OK);
   TRY_TEST(model.IsEqualObject(intersect),true);
   intersect.Release();

   CComPtr<IMeasure> measure;
   TRY_TEST(model->get_Measure(nullptr),E_POINTER);
   TRY_TEST(model->get_Measure(&measure),S_OK);
   TRY_TEST(model.IsEqualObject(measure),true);
   measure.Release();

   CComPtr<IProject> project;
   TRY_TEST(model->get_Project(nullptr),E_POINTER);
   TRY_TEST(model->get_Project(&project),S_OK);
   TRY_TEST(model.IsEqualObject(project),true);
   project.Release();

   CComPtr<IDivide> divide;
   TRY_TEST(model->get_Divide(nullptr),E_POINTER);
   TRY_TEST(model->get_Divide(&divide),S_OK);
   TRY_TEST(model.IsEqualObject(divide),true);
   divide.Release();

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(model);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICogoModel ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IIntersect ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ILocate ),    S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IMeasure ),   S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IProject ),   S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IDivide ),    S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ITangent ),    S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   eInfo.Release();

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_CogoModel,IID_ICogoModel,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CogoModel,IID_IDivide,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CogoModel,IID_ITangent,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CogoModel,IID_IIntersect,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CogoModel,IID_ILocate,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CogoModel,IID_IMeasure,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CogoModel,IID_IProject,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CogoModel,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
