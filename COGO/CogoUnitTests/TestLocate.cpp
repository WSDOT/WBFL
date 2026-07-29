///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// TestLocate.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestLocate.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestLocate)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<ILocate> locate;
         ASSERT_EQ(locate.CoCreateInstance(CLSID_CogoModel),S_OK);

         CComQIPtr<ICogoModel> model(locate);
         ASSERT_EQ( model != nullptr, true );

         CComPtr<IPoint2d> pnt;
         Float64 x,y;

         model->StorePoint(1,0.0,0.0);
         model->StorePoint(2,10.0,0.0);

         // Locate ByDistDir
         ASSERT_EQ(locate->ByDistDir(1,2,10.0,CComVariant(PI_OVER_2),0.00), S_FALSE);
         ASSERT_EQ(locate->ByDistDir(3,-1,10.0,CComVariant(PI_OVER_2),0.00), E_INVALIDARG);
         ASSERT_EQ(locate->ByDistDir(3,2,10.0,CComVariant(PI_OVER_2),0.00),S_OK);
         model->GetPointByID(3,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,10.0),true);
         ASSERT_EQ(IsEqual(y,10.0),true);

         pnt.Release();
         ASSERT_EQ(locate->ByDistDir(4,2,10.0,CComVariant(PI_OVER_2),5.00),S_OK);
         model->GetPointByID(4,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,15.0),true);
         ASSERT_EQ(IsEqual(y,10.0),true);

         pnt.Release();
         ASSERT_EQ(locate->ByDistDir(5,2,10.0,CComVariant(PI_OVER_2),-5.00),S_OK);
         model->GetPointByID(5,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 5.0),true);
         ASSERT_EQ(IsEqual(y,10.0),true);

         CComPtr<IDirection> dir;
         dir.CoCreateInstance(CLSID_Direction);
         dir->FromDMS(nsNorth,45,0,0.0,ewWest);
         CComPtr<IUnknown> unkDir(dir);
         pnt.Release();
         ASSERT_EQ(locate->ByDistDir(6,2,10.0,CComVariant(unkDir),0.00),S_OK);
         model->GetPointByID(6,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,2.92893218813),true);
         ASSERT_EQ(IsEqual(y,7.07106781187),true);

         pnt.Release();
         ASSERT_EQ(locate->ByDistDir(7,2,10.0,CComVariant(dir),5.00),S_OK);
         model->GetPointByID(7,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,6.46446609407),true);
         ASSERT_EQ(IsEqual(y,10.6066017178),true);

         pnt.Release();
         ASSERT_EQ(locate->ByDistDir(8,2,10.0,CComVariant(dir),-5.00),S_OK);
         model->GetPointByID(8,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,-0.60660171781),true);
         ASSERT_EQ(IsEqual(y,3.53553390593),true);

         pnt.Release();
         ASSERT_EQ(locate->ByDistDir(9,2,-10.0,CComVariant(dir),0.00),S_OK);
         model->GetPointByID(9,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,17.07106781187),true);
         ASSERT_EQ(IsEqual(y,-7.07106781187),true);

         // Locate ByDistAngle
         model->ClearPoints();
         model->StorePoint(1,10,10);
         model->StorePoint(2,0,0);

         ASSERT_EQ(locate->ByDistAngle(1,1,2,10.0,CComVariant(M_PI),0.0), S_FALSE);
         ASSERT_EQ(locate->ByDistAngle(3,-1,2,10.0,CComVariant(M_PI),0.0), E_INVALIDARG);
         ASSERT_EQ(locate->ByDistAngle(3,1,-2,10.0,CComVariant(M_PI),0.0), E_INVALIDARG);

         ASSERT_EQ(locate->ByDistAngle(3,1,2,10.0,CComVariant(M_PI),0.0),S_OK);
         pnt.Release();
         model->GetPointByID(3,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,-7.07106781187),true);
         ASSERT_EQ(IsEqual(y,-7.07106781187),true);

         ASSERT_EQ(locate->ByDistAngle(4,1,2,10.0,CComVariant(M_PI/4),0.0),S_OK);
         pnt.Release();
         model->GetPointByID(4,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 0.0),true);
         ASSERT_EQ(IsEqual(y,10.0),true);

         CComPtr<IAngle> angle;
         angle.CoCreateInstance(CLSID_Angle);
         angle->FromDMS(225,0,0);
         ASSERT_EQ(locate->ByDistAngle(5,1,2,10.0,CComVariant(angle),-5.0),S_OK);
         pnt.Release();
         model->GetPointByID(5,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,  3.53553390594),true);
         ASSERT_EQ(IsEqual(y,-13.53553390594),true);

         ASSERT_EQ(locate->ByDistAngle(6,1,2,-10.0,CComVariant(angle),-5.0),S_OK);
         pnt.Release();
         model->GetPointByID(6,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,3.53553390594),true);
         ASSERT_EQ(IsEqual(y,6.46446609406),true);

         // Locate ByDistDefAngle
         model->ClearPoints();
         model->StorePoint(1,10,10);
         model->StorePoint(2,0,0);

         ASSERT_EQ(locate->ByDistDefAngle(1,1,2,10.0,CComVariant(M_PI),0.0), S_FALSE);
         ASSERT_EQ(locate->ByDistDefAngle(3,-1,2,10.0,CComVariant(M_PI),0.0), E_INVALIDARG);
         ASSERT_EQ(locate->ByDistDefAngle(3,1,-2,10.0,CComVariant(M_PI),0.0), E_INVALIDARG);

         ASSERT_EQ(locate->ByDistDefAngle(3,1,2,10.0,CComVariant(M_PI),0.0),S_OK);
         pnt.Release();
         model->GetPointByID(3,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,7.07106781187),true);
         ASSERT_EQ(IsEqual(y,7.07106781187),true);

         ASSERT_EQ(locate->ByDistDefAngle(4,1,2,10.0,CComVariant(M_PI/4),0.0),S_OK);
         pnt.Release();
         model->GetPointByID(4,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,  0.0),true);
         ASSERT_EQ(IsEqual(y,-10.0),true);

         CComPtr<IAngle> defAngle;
         defAngle.CoCreateInstance(CLSID_Angle);
         defAngle->FromDMS(45,0,0);
         ASSERT_EQ(locate->ByDistDefAngle(5,1,2,10.0,CComVariant(defAngle),-5.0),S_OK);
         pnt.Release();
         model->GetPointByID(5,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,  3.53553390594),true);
         ASSERT_EQ(IsEqual(y,-13.53553390594),true);

         ASSERT_EQ(locate->ByDistDefAngle(6,1,2,-10.0,CComVariant(defAngle),-5.0),S_OK);
         pnt.Release();
         model->GetPointByID(6,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,3.53553390594),true);
         ASSERT_EQ(IsEqual(y,6.46446609406),true);

         // Locate PointOnLine
         model->ClearPoints();
         model->StorePoint(1,10,10);
         model->StorePoint(2,20,20);

         ASSERT_EQ(locate->PointOnLine(3,1,2,20.0,0.0),S_OK);
         pnt.Release();
         model->GetPointByID(3,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,24.1421356237),true);
         ASSERT_EQ(IsEqual(y,24.1421356237),true);

         ASSERT_EQ(locate->PointOnLine(4,1,2,-20.0,0.0),S_OK);
         pnt.Release();
         model->GetPointByID(4,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,-4.1421356237),true);
         ASSERT_EQ(IsEqual(y,-4.1421356237),true);

         ASSERT_EQ(locate->PointOnLine(5,1,2,10.0,5.0),S_OK);
         pnt.Release();
         model->GetPointByID(5,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,20.6066017178),true);
         ASSERT_EQ(IsEqual(y,13.5355339059),true);

         ASSERT_EQ(locate->PointOnLine(6,1,2,10.0,-5.0),S_OK);
         pnt.Release();
         model->GetPointByID(6,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,13.5355339059),true);
         ASSERT_EQ(IsEqual(y,20.6066017178),true);

         // Test ParallelLineSegment and ParallelLineByPoints
         //
         model->ClearPoints();
         model->StorePoint(1,0,0);
         model->StorePoint(2,20,20);
         CComPtr<IPoint2d> p1, p2;
         model->GetPointByID(1,&p1);
         model->GetPointByID(2,&p2);

         model->ClearPathSegments();
         model->StorePathSegment(1,1,2);

         ASSERT_EQ(locate->ParallelLineSegment(1,3,4,1,5.0), S_FALSE);
         ASSERT_EQ(locate->ParallelLineSegment(2,1,4,1,5.0), S_FALSE);
         ASSERT_EQ(locate->ParallelLineSegment(2,3,1,1,5.0), S_FALSE);
         ASSERT_EQ(locate->ParallelLineSegment(2,3,4,-1,5.0), E_INVALIDARG);
         ASSERT_EQ(locate->ParallelLineByPoints(3,4,-1,2,5.0), E_INVALIDARG);
         ASSERT_EQ(locate->ParallelLineByPoints(3,4,1,-2,5.0), E_INVALIDARG);

         ASSERT_EQ(locate->ParallelLineSegment(2,3,4,1,5.0),S_OK);
         IDType startID, endID;
         ASSERT_EQ(model->GetPathSegmentByID(2,&startID,&endID),S_OK);
         ASSERT_EQ(startID, 3);
         ASSERT_EQ(endID, 4);

         ASSERT_EQ(locate->ParallelLineByPoints(3,4,1,2,5.0), S_FALSE);
         ASSERT_EQ(locate->ParallelLineByPoints(13,4,1,2,5.0), S_FALSE);
         ASSERT_EQ(locate->ParallelLineByPoints(13,14,1,2,5.0),S_OK);
         pnt.Release();
         ASSERT_EQ(model->GetPointByID(13,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 3.53553390594),true);
         ASSERT_EQ(IsEqual(y,-3.53553390594),true);
         pnt.Release();
         ASSERT_EQ(model->GetPointByID(14,&pnt),S_OK);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,23.5355339059),true);
         ASSERT_EQ(IsEqual(y,16.4644660940),true);
   }
};
} // namespace CogoUnitTests