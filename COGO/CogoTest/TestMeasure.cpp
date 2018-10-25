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

// TestMeasure.cpp: implementation of the CTestMeasure class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestMeasure.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestMeasure::CTestMeasure()
{

}

CTestMeasure::~CTestMeasure()
{

}

void CTestMeasure::Test()
{
   CComPtr<IMeasure> measure;
   TRY_TEST(measure.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComQIPtr<ICogoModel> model(measure);
   TRY_TEST( model != NULL, true );

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   points->Add(1,10.0,10.0,NULL);
   points->Add(2,40.0,20.0,NULL);
   points->Add(3,40.0, 0.0,NULL);

   // Test Distance
   Float64 dist;
   TRY_TEST(measure->Distance(1,2,NULL),E_POINTER);
   TRY_TEST(measure->Distance(-1,2,&dist),COGO_E_POINTNOTFOUND);
   TRY_TEST(measure->Distance(1,-2,&dist),COGO_E_POINTNOTFOUND);
   TRY_TEST(measure->Distance(1,2,&dist),S_OK);
   TRY_TEST(IsEqual(dist,31.62277660),true);

   TRY_TEST(measure->Distance(1,1,&dist),S_OK);
   TRY_TEST(IsEqual(dist,0.0),true);

   // Test Angle
   // Angle is implemented by WBFLGeometry...
   // All we need here is a simple intergration test
   points->Clear();
   points->Add(1,10.0, 0.0,NULL);
   points->Add(2, 0.0, 0.0,NULL);
   points->Add(3, 0.0,10.0,NULL);

   CComPtr<IAngle> angle;
   Float64 val;
   TRY_TEST(measure->Angle(2,1,3,NULL),E_POINTER);
   TRY_TEST(measure->Angle(-2,1,3,&angle),COGO_E_POINTNOTFOUND);
   TRY_TEST(measure->Angle(2,-1,3,&angle),COGO_E_POINTNOTFOUND);
   TRY_TEST(measure->Angle(2,1,-3,&angle),COGO_E_POINTNOTFOUND);
   TRY_TEST(measure->Angle(2,1,1,&angle),COGO_E_ANGLE);
   TRY_TEST(measure->Angle(2,2,3,&angle),COGO_E_ANGLE);
   TRY_TEST(measure->Angle(1,1,3,&angle),COGO_E_ANGLE);

   TRY_TEST(measure->Angle(1,2,3,&angle),S_OK);
   angle->get_Value(&val);
   TRY_TEST(IsEqual(val,PI_OVER_2),true);

   angle.Release();
   TRY_TEST(measure->Angle(3,2,1,&angle),S_OK);
   angle->get_Value(&val);
   TRY_TEST(IsEqual(val,3*PI_OVER_2),true);

   //
   // Test Direction
   //
   points->Clear();
   points->Add(1,10.0,10.0,NULL);
   points->Add(2,20.0,20.0,NULL);
   CComPtr<IDirection> dir;
   TRY_TEST(measure->Direction( 1,2,NULL),E_POINTER);
   TRY_TEST(measure->Direction(-1,2,&dir),COGO_E_POINTNOTFOUND);
   TRY_TEST(measure->Direction(1,-2,&dir),COGO_E_POINTNOTFOUND);
   TRY_TEST(measure->Direction( 1,2,&dir),S_OK);
   NSDirectionType ns;
   EWDirectionType ew;
   long deg, min;
   Float64 sec;
   dir->get_NSDirection(&ns);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ew);
   TRY_TEST(ns,nsNorth);
   TRY_TEST(deg,45);
   TRY_TEST(min,0);
   TRY_TEST(IsEqual(sec,0.0),true);
   TRY_TEST(ew,ewEast);

   dir.Release();
   TRY_TEST(measure->Direction(2,1,&dir),S_OK);
   dir->get_NSDirection(&ns);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ew);
   TRY_TEST(ns,nsSouth);
   TRY_TEST(deg,45);
   TRY_TEST(min,0);
   TRY_TEST(IsEqual(sec,0.0),true);
   TRY_TEST(ew,ewWest);

   // 2 points at the same location should produce a bearing that is due east
   dir.Release();
   TRY_TEST(measure->Direction( 1,1,&dir), S_OK);
   dir->get_NSDirection(&ns);
   dir->get_Degree(&deg);
   dir->get_Minute(&min);
   dir->get_Second(&sec);
   dir->get_EWDirection(&ew);
   TRY_TEST(ns,nsNorth);
   TRY_TEST(deg,90);
   TRY_TEST(min,0);
   TRY_TEST(IsEqual(sec,0.0),true);
   TRY_TEST(ew,ewEast);

   // Test Area
   points->Clear();
   points->Add(1,0,0,NULL);
   points->Add(2,10,0,NULL);
   points->Add(3,10,10,NULL);
   points->Add(4,0,10,NULL);

   SAFEARRAY* keys;
   SAFEARRAYBOUND bounds = { 4, 10 };
   keys = SafeArrayCreate(VT_I4,1,&bounds);
   for ( LONG i = bounds.lLbound; i < (LONG)(bounds.lLbound+bounds.cElements); i++ )
   {
      CogoObjectID key = CogoObjectID(i - bounds.lLbound + 1);
      SafeArrayPutElement(keys,&i,&key);
   }

   Float64 area;
   CComVariant varKeys;
   varKeys.vt = VT_ARRAY | VT_I4;
   varKeys.parray = keys;
   TRY_TEST(measure->Area(varKeys,NULL),E_POINTER);
   TRY_TEST(measure->Area(varKeys,&area),S_OK);
   TRY_TEST(IsEqual(area,100.),true);
   SafeArrayDestroy(keys);

   // Try an array with undefined points
   keys = SafeArrayCreate(VT_I4,1,&bounds);
   for ( LONG i = bounds.lLbound; i < (LONG)(bounds.lLbound+bounds.cElements); i++ )
   {
      CogoObjectID key = CogoObjectID(i - bounds.lLbound + 1);
      if ( (i-bounds.lLbound) == 2 )
         key = 400;

      SafeArrayPutElement(keys,&i,&key);
   }
   varKeys.vt = VT_ARRAY | VT_I4;
   varKeys.parray = keys;
   TRY_TEST(measure->Area(varKeys,&area),COGO_E_POINTNOTFOUND);
   SafeArrayDestroy(keys);

   // Try an array with less than 3 elements
   bounds.cElements = 2;
   keys = SafeArrayCreate(VT_I4,1,&bounds);
   for ( LONG i = bounds.lLbound; i < (LONG)(bounds.lLbound+bounds.cElements); i++ )
   {
      CogoObjectID key = CogoObjectID(i - bounds.lLbound + 1);
      SafeArrayPutElement(keys,&i,&key);
   }
   varKeys.vt = VT_ARRAY | VT_I4;
   varKeys.parray = keys;
   TRY_TEST(measure->Area(varKeys,&area),COGO_E_THREEPNTSREQD);
//   SafeArrayDestroy(keys); // This is causing the test code to crash. I don't know why.
                             // Since this is a test driver, who cares if it leaks a little
                             // memory. Time to move on. RAB: 11/14/2001
}