///////////////////////////////////////////////////////////////////////
// Sections Test - Test driver for Sections library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TestCompositeBeam.cpp: implementation of the CTestCompositeBeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCompositeBeam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCompositeBeam::CTestCompositeBeam()
{

}

CTestCompositeBeam::~CTestCompositeBeam()
{

}

void CTestCompositeBeam::Test()
{
	TestICompositeBeam();
	TestISection();
	TestIXYPosition();
}

void CTestCompositeBeam::TestICompositeBeam()
{
   CComPtr<ICompositeBeam> comp;
   TRY_TEST(comp.CoCreateInstance(CLSID_CompositeBeam),S_OK);

   // Test default values;
   CComPtr<IShape> shape;
   Float64 val;

   TRY_TEST(comp->get_Beam(NULL),E_POINTER);
   TRY_TEST(comp->get_Beam(&shape),S_OK);
   TRY_TEST(shape != 0, true);

   CComQIPtr<IRectangle> rect(shape);
   TRY_TEST(rect != 0,true);

   TRY_TEST(comp->get_BeamDensity(NULL),E_POINTER);
   TRY_TEST(comp->get_BeamDensity(&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(comp->get_BeamE(NULL),E_POINTER);
   TRY_TEST(comp->get_BeamE(&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(comp->get_EffectiveSlabWidth(NULL),E_POINTER);
   TRY_TEST(comp->get_EffectiveSlabWidth(&val),S_OK);
   TRY_TEST(IsEqual(val,0.0),true);

   TRY_TEST(comp->get_GrossSlabDepth(NULL),E_POINTER);
   TRY_TEST(comp->get_GrossSlabDepth(&val),S_OK);
   TRY_TEST(IsEqual(val,0.0),true);

   TRY_TEST(comp->get_HaunchDepth(NULL),E_POINTER);
   TRY_TEST(comp->get_HaunchDepth(&val),S_OK);
   TRY_TEST(IsEqual(val,0.0),true);

   TRY_TEST(comp->get_HaunchWidth(NULL),E_POINTER);
   TRY_TEST(comp->get_HaunchWidth(&val),S_OK);
   TRY_TEST(IsEqual(val,0.0),true);

   TRY_TEST(comp->get_SacrificialDepth(NULL),E_POINTER);
   TRY_TEST(comp->get_SacrificialDepth(&val),S_OK);
   TRY_TEST(IsEqual(val,0.0),true);

   TRY_TEST(comp->get_SlabDensity(NULL),E_POINTER);
   TRY_TEST(comp->get_SlabDensity(&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(comp->get_SlabE(NULL),E_POINTER);
   TRY_TEST(comp->get_SlabE(&val),S_OK);
   TRY_TEST(IsEqual(val,1.0),true);

   TRY_TEST(comp->get_TributarySlabWidth(NULL),E_POINTER);
   TRY_TEST(comp->get_TributarySlabWidth(&val),S_OK);
   TRY_TEST(IsEqual(val,0.0),true);


   // Set the effective slab width. The tributary width
   // should grow to match
   TRY_TEST(comp->put_EffectiveSlabWidth(-1),E_INVALIDARG);
   TRY_TEST(comp->put_EffectiveSlabWidth(50),S_OK);
   comp->get_TributarySlabWidth(&val);
   TRY_TEST(IsEqual(val,50.0),true);

   // Make the tributary width wider. Effective width should remain
   // unchanged
   TRY_TEST(comp->put_TributarySlabWidth(-1),E_INVALIDARG);
   TRY_TEST(comp->put_TributarySlabWidth(60),S_OK);
   comp->get_EffectiveSlabWidth(&val);
   TRY_TEST(IsEqual(val,50.0),true);

   // Make trib width smaller than effective.
   comp->put_TributarySlabWidth(20);
   comp->get_EffectiveSlabWidth(&val);
   TRY_TEST(IsEqual(val,20.0),true);

   // Test slab depth adjustments
   TRY_TEST(comp->put_GrossSlabDepth(-1),E_INVALIDARG);
   TRY_TEST(comp->put_GrossSlabDepth(8),S_OK);

   TRY_TEST(comp->put_SacrificialDepth(-1),E_INVALIDARG);
   TRY_TEST(comp->put_SacrificialDepth(1),S_OK);
   comp->get_GrossSlabDepth(&val);
   TRY_TEST(IsEqual(val,8.0),true);

   TRY_TEST(comp->put_SacrificialDepth(9),S_OK);
   comp->get_GrossSlabDepth(&val);
   TRY_TEST(IsEqual(val,16.0),true);

   // Check Q and QSlab for a real beam
   CComPtr<IPlateGirder> beam;
   beam.CoCreateInstance(CLSID_PlateGirder);
   beam->put_TopFlangeWidth(22);
   beam->put_TopFlangeThick(1.25);
   beam->put_BottomFlangeWidth(22);
   beam->put_BottomFlangeThick(2.25);
   beam->put_WebThick(0.438);
   beam->put_WebHeight(122);
   shape.Release();
   beam.QueryInterface(&shape);
   comp->putref_Beam(shape);

   // define the slab
   comp->put_GrossSlabDepth(7);
   comp->put_EffectiveSlabWidth(84);
   comp->put_HaunchWidth(22);
   comp->put_HaunchDepth(0.5);
   comp->put_SlabE(0.125);  // N = 8

   Float64 Q;
   TRY_TEST(comp->get_QSlab(NULL),E_POINTER);
   TRY_TEST(comp->get_QSlab(&Q),S_OK);
   TRY_TEST(IsEqual(Q,3651.6,0.1),true);

   // q top flange + slab
   TRY_TEST(comp->get_Q(124.25,NULL),E_POINTER);
   TRY_TEST(comp->get_Q(-1,&Q),E_INVALIDARG);
   TRY_TEST(comp->get_Q(124.25,&Q),S_OK);
   TRY_TEST(IsEqual(Q,4867.5,0.1),true);

   // q bottom flange
   TRY_TEST(comp->get_Q(2.25,&Q),S_OK);
   TRY_TEST(IsEqual(Q,3937.1,0.1),true);

  ///////////////////////////////////////
   // Test ISupportErrorInfo
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_CompositeBeam ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICompositeBeam ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICompositeBeamEx ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   //////////////////////////////////////////////////////////////
   // Test IObjectSafety
   CComPtr<IObjectSafety> pObjSafety;
   TRY_TEST(pObjSafety.CoCreateInstance(CLSID_CompositeBeam), S_OK);
   DWORD dwDesiredOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
   DWORD dwSupportedOptions, dwEnabledOptions;
   pObjSafety->GetInterfaceSafetyOptions(IID_ICompositeBeam,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
   pObjSafety->GetInterfaceSafetyOptions(IID_ICompositeBeamEx,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
   pObjSafety->GetInterfaceSafetyOptions(IID_ISection,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
   pObjSafety->GetInterfaceSafetyOptions(IID_IXYPosition,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
   pObjSafety->GetInterfaceSafetyOptions(IID_IStructuredStorage2,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
}

void CTestCompositeBeam::TestISection()
{
   CComPtr<ICompositeBeam> comp;
   TRY_TEST(comp.CoCreateInstance(CLSID_CompositeBeam),S_OK);

   // define the girder (Plate Girder I-Beam)
   CComPtr<IPlateGirder> beam;
   beam.CoCreateInstance(CLSID_PlateGirder);
   beam->put_TopFlangeWidth(22);
   beam->put_TopFlangeThick(1.25);
   beam->put_BottomFlangeWidth(22);
   beam->put_BottomFlangeThick(2.25);
   beam->put_WebThick(0.438);
   beam->put_WebHeight(122);
   CComQIPtr<IShape> shape(beam);
   comp->putref_Beam(shape);
   comp->put_BeamDensity(420.);
   comp->put_BeamE(1.);

   // define the slab
   comp->put_GrossSlabDepth(7);
   comp->put_EffectiveSlabWidth(84);
   comp->put_HaunchWidth(22);
   comp->put_HaunchDepth(0.5);
   comp->put_SlabE(0.125);  // N = 8
   comp->put_SlabDensity(160.);

   CComQIPtr<ISection> section(comp);
   // test bounding box
   CComPtr<IRect2d> box;
   TRY_TEST(section->get_BoundingBox(NULL),E_POINTER);
   TRY_TEST(section->get_BoundingBox(&box),S_OK);
   Float64 l,r,t,b;
   box->get_Left(&l);
   box->get_Right(&r);
   box->get_Top(&t);
   box->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-42.),true);
   TRY_TEST(IsEqual(r, 42.),true);
   TRY_TEST(IsEqual(t,133.),true);
   TRY_TEST(IsEqual(b,0.),true);

   // Elastic Properties
   CComPtr<IElasticProperties> props;
   TRY_TEST(section->get_ElasticProperties(NULL),E_POINTER);
   TRY_TEST(section->get_ElasticProperties(&props),S_OK);
   Float64 val;
   props->get_EA(&val);
   TRY_TEST(IsEqual(val,205.311),true);
   
   props->get_EIxx(&val);
   TRY_TEST(IsEqual(val,627807.85259178),true);

   props->get_EIyy(&val);
   TRY_TEST(IsEqual(val,46379.979281332),true);

   props->get_EIxy(&val);
   TRY_TEST(IsEqual(val,0.),true);

   props->get_Xleft(&val);
   TRY_TEST(IsEqual(val,42.),true);

   props->get_Xright(&val);
   TRY_TEST(IsEqual(val,42.),true);

   props->get_Ytop(&val);
   TRY_TEST(IsEqual(val,52.338305059154),true);

   props->get_Ybottom(&val);
   TRY_TEST(IsEqual(val,80.661694640846),true);
 
   CComPtr<IPoint2d> cg;
   props->get_Centroid(&cg);
   cg->get_X(&val);
   TRY_TEST(IsEqual(val,0.),true);
   cg->get_Y(&val);
   TRY_TEST(IsEqual(val,80.661694640846),true);

   // Check mass properties
   CComPtr<IMassProperties> mprops;
   TRY_TEST(section->get_MassProperties(NULL),E_POINTER);
   TRY_TEST(section->get_MassProperties(&mprops),S_OK);
   mprops->get_MassPerLength(&val);
   TRY_TEST(IsEqual(val,150623.12),true);

   // Test ClipIn
   // Clip so that only the top 1" of the slab remains
   CComPtr<IRect2d> clipRect;
   clipRect.CoCreateInstance(CLSID_Rect2d);
   clipRect->put_Left(-1000);
   clipRect->put_Right(1000);
   clipRect->put_Bottom(132.);
   clipRect->put_Top(1000);

   CComPtr<ISection> clipSection;
   TRY_TEST(section->ClipIn(NULL,&clipSection),E_INVALIDARG);
   TRY_TEST(section->ClipIn(clipRect,NULL),E_POINTER);
   TRY_TEST(section->ClipIn(clipRect,&clipSection),S_OK);
   props.Release();
   clipSection->get_ElasticProperties(&props);
   props->get_EA(&val);
   TRY_TEST(IsEqual(val,84.*1.*0.125),true);

   // Test clip with line
   CComPtr<IPoint2d> p1;
   CComPtr<IPoint2d> p2;
   clipRect->get_BottomRight(&p1);
   clipRect->get_BottomLeft(&p2);

   CComPtr<ILine2d> clipLine;
   clipLine.CoCreateInstance(CLSID_Line2d);
   clipLine->ThroughPoints(p1,p2);

   clipSection.Release();
   TRY_TEST(section->ClipWithLine(NULL,&clipSection),E_INVALIDARG);
   TRY_TEST(section->ClipWithLine(clipLine,NULL),E_POINTER);
   TRY_TEST(section->ClipWithLine(clipLine,&clipSection),S_OK);

   props.Release();
   clipSection->get_ElasticProperties(&props);
   props->get_EA(&val);
   TRY_TEST(IsEqual(val,84.*1.*0.125),true);

   // Test Clone
   CComPtr<ISection> cloneSection;
   TRY_TEST(section->Clone(NULL),E_POINTER);
   TRY_TEST(section->Clone(&cloneSection),S_OK);

   CComQIPtr<ICompositeBeam> cloneComp(cloneSection);
   TRY_TEST(cloneComp != NULL,true);
   cloneComp->get_GrossSlabDepth(&val);
   TRY_TEST(IsEqual(val,7.),true);
   cloneComp->get_EffectiveSlabWidth(&val);
   TRY_TEST(IsEqual(val,84.),true);
   cloneComp->get_TributarySlabWidth(&val);
   TRY_TEST(IsEqual(val,84.),true);
   cloneComp->get_HaunchDepth(&val);
   TRY_TEST(IsEqual(val,0.5),true);
   cloneComp->get_HaunchWidth(&val);
   TRY_TEST(IsEqual(val,22.),true);

   CComPtr<IShape> cloneShape;
   cloneComp->get_Beam(&cloneShape);
   CComQIPtr<IPlateGirder> cloneBeam(cloneShape);
   TRY_TEST(cloneBeam != NULL,true);
   cloneBeam->get_WebHeight(&val);
   TRY_TEST(IsEqual(val,122.),true);
   cloneBeam->get_WebThick(&val);
   TRY_TEST(IsEqual(val,0.438),true);
   cloneBeam->get_TopFlangeWidth(&val);
   TRY_TEST(IsEqual(val,22.),true);
   cloneBeam->get_TopFlangeThick(&val);
   TRY_TEST(IsEqual(val,1.25),true);
   cloneBeam->get_BottomFlangeWidth(&val);
   TRY_TEST(IsEqual(val,22.),true);
   cloneBeam->get_BottomFlangeThick(&val);
   TRY_TEST(IsEqual(val,2.25),true);
}

void CTestCompositeBeam::TestIXYPosition()
{
   CComPtr<ICompositeBeam> comp;
   TRY_TEST(comp.CoCreateInstance(CLSID_CompositeBeam),S_OK);

   // define the girder (Plate Girder I-Beam)
   CComPtr<IPlateGirder> beam;
   beam.CoCreateInstance(CLSID_PlateGirder);
   beam->put_TopFlangeWidth(22);
   beam->put_TopFlangeThick(1.25);
   beam->put_BottomFlangeWidth(22);
   beam->put_BottomFlangeThick(2.25);
   beam->put_WebThick(0.438);
   beam->put_WebHeight(122);
   CComQIPtr<IShape> shape(beam);
   comp->putref_Beam(shape);
   comp->put_BeamDensity(420.);
   comp->put_BeamE(1.);

   // define the slab
   comp->put_GrossSlabDepth(7);
   comp->put_EffectiveSlabWidth(84);
   comp->put_HaunchWidth(22);
   comp->put_HaunchDepth(0.5);
   comp->put_SlabE(0.125);  // N = 8
   comp->put_SlabDensity(160.);

   CComQIPtr<IXYPosition> position(comp);
   Float64 x,y;

   CComPtr<IPoint2d> hookPnt;
   beam->get_HookPoint(&hookPnt);
 
   //
   // OffsetEx and Offset
   //
   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(10);
   size->put_Dy(20);
   TRY_TEST( position->OffsetEx(NULL), E_INVALIDARG );
   TRY_TEST( position->OffsetEx(size), S_OK );

   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);

   TRY_TEST( IsEqual(x,10.), true );
   TRY_TEST( IsEqual(y,20.), true );

   TRY_TEST( position->Offset(10,20), S_OK );

   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);

   TRY_TEST( IsEqual(x,20.), true );
   TRY_TEST( IsEqual(y,40.), true );

   //
   // MoveEx
   //
   CComPtr<IPoint2d> from;
   from.CoCreateInstance( CLSID_Point2d );
   from->Move(10,10);

   CComPtr<IPoint2d> to;
   to.CoCreateInstance( CLSID_Point2d );
   to->Move(110,110);

   TRY_TEST( position->MoveEx(NULL,to),    E_INVALIDARG );
   TRY_TEST( position->MoveEx(from, NULL), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,to),    S_OK );

   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);

   TRY_TEST( IsEqual(x,120.), true );
   TRY_TEST( IsEqual(y,140.), true );

   //
   // LocatorPoint property
   //

   to->Move(0,0);
   TRY_TEST( position->put_LocatorPoint(lpBottomCenter,to), S_OK );

   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);

   TRY_TEST( IsEqual(x,0.), true );
   TRY_TEST( IsEqual(y,0.), true );

   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,NULL), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,NULL), E_POINTER );

   // BottomLeft
   to->Move(58,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x, 58.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // BottomCenter
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpBottomCenter,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpBottomCenter,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // BottomRight
   to->Move(142,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpBottomRight,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpBottomRight,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,142.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // CenterLeft
   to->Move(58,166.5);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpCenterLeft,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpCenterLeft,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x, 58.0), true );
   TRY_TEST( IsEqual(y,166.5), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // CenterCenter
   to->Move(100,166.5);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpCenterCenter,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpCenterCenter,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,166.5), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // CenterRight
   to->Move(142,166.5);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpCenterRight,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpCenterRight,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,142.0), true );
   TRY_TEST( IsEqual(y,166.5), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // TopLeft
   to->Move(58,233);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpTopLeft,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpTopLeft,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x, 58.0), true );
   TRY_TEST( IsEqual(y,233.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // TopCenter
   to->Move(100,233);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpTopCenter,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpTopCenter,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,233.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // TopRight
   to->Move(142,233);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpTopRight,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpTopRight,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,142.0), true );
   TRY_TEST( IsEqual(y,233.0), true );
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
   CComPtr<IPoint2d> rotPoint;
   rotPoint.CoCreateInstance( CLSID_Point2d );

   // Rotate about the origin of the coordinate system and check the bounding box
   to->Move(100,100);
   TRY_TEST( position->put_LocatorPoint(lpBottomCenter,to), S_OK );
   rotPoint->Move(0,0);

   TRY_TEST( position->RotateEx(NULL,PI_OVER_2), E_INVALIDARG );
   TRY_TEST( position->RotateEx(rotPoint,PI_OVER_2), S_OK );

   CComQIPtr<ISection> section(position);
   CComPtr<IRect2d> box;
   section->get_BoundingBox(&box);
   Float64 l,r,t,b;
   box->get_Left(&l);
   box->get_Right(&r);
   box->get_Top(&t);
   box->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-233.),true);
   TRY_TEST(IsEqual(r,-100.),true);
   TRY_TEST(IsEqual(t,142.),true);
   TRY_TEST(IsEqual(b,58.),true);
}

