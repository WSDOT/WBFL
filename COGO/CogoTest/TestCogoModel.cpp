///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2024  Washington State Department of Transportation
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
}
