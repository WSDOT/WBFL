///////////////////////////////////////////////////////////////////////
// Sections Test - Test driver for Sections library
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

// TestCompositeBeam.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestCompositeBeam.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the methods below, which are now independent TEST_METHODs; the dispatcher itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestCompositeBeam)
{
public:
   TEST_METHOD(TestICompositeBeam)
   {
         CComPtr<ICompositeBeam> comp;
         ASSERT_EQ(comp.CoCreateInstance(CLSID_CompositeBeam),S_OK);

         // Test default values;
         CComPtr<IShape> shape;
         Float64 val;

         ASSERT_EQ(comp->get_Beam(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_Beam(&shape),S_OK);
         ASSERT_EQ(shape != nullptr, true);

         CComQIPtr<IRectangle> rect(shape);
         ASSERT_EQ(rect != nullptr,true);

         ASSERT_EQ(comp->get_BeamDensity(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_BeamDensity(&val),S_OK);
         ASSERT_EQ(IsEqual(val,1.0),true);

         ASSERT_EQ(comp->get_BeamE(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_BeamE(&val),S_OK);
         ASSERT_EQ(IsEqual(val,1.0),true);

         ASSERT_EQ(comp->get_EffectiveSlabWidth(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_EffectiveSlabWidth(&val),S_OK);
         ASSERT_EQ(IsEqual(val,0.0),true);

         ASSERT_EQ(comp->get_GrossSlabDepth(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_GrossSlabDepth(&val),S_OK);
         ASSERT_EQ(IsEqual(val,0.0),true);

         ASSERT_EQ(comp->get_HaunchDepth(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_HaunchDepth(&val),S_OK);
         ASSERT_EQ(IsEqual(val,0.0),true);

         ASSERT_EQ(comp->get_HaunchWidth(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_HaunchWidth(&val),S_OK);
         ASSERT_EQ(IsEqual(val,0.0),true);

         ASSERT_EQ(comp->get_SacrificialDepth(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_SacrificialDepth(&val),S_OK);
         ASSERT_EQ(IsEqual(val,0.0),true);

         ASSERT_EQ(comp->get_SlabDensity(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_SlabDensity(&val),S_OK);
         ASSERT_EQ(IsEqual(val,1.0),true);

         ASSERT_EQ(comp->get_SlabE(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_SlabE(&val),S_OK);
         ASSERT_EQ(IsEqual(val,1.0),true);

         ASSERT_EQ(comp->get_TributarySlabWidth(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_TributarySlabWidth(&val),S_OK);
         ASSERT_EQ(IsEqual(val,0.0),true);


         // Set the effective slab width. The tributary width
         // should grow to match
         ASSERT_EQ(comp->put_EffectiveSlabWidth(-1),E_INVALIDARG);
         ASSERT_EQ(comp->put_EffectiveSlabWidth(50),S_OK);
         comp->get_TributarySlabWidth(&val);
         ASSERT_EQ(IsEqual(val,50.0),true);

         // Make the tributary width wider. Effective width should remain
         // unchanged
         ASSERT_EQ(comp->put_TributarySlabWidth(-1),E_INVALIDARG);
         ASSERT_EQ(comp->put_TributarySlabWidth(60),S_OK);
         comp->get_EffectiveSlabWidth(&val);
         ASSERT_EQ(IsEqual(val,50.0),true);

         // Make trib width smaller than effective.
         comp->put_TributarySlabWidth(20);
         comp->get_EffectiveSlabWidth(&val);
         ASSERT_EQ(IsEqual(val,20.0),true);

         // Test slab depth adjustments
         ASSERT_EQ(comp->put_GrossSlabDepth(-1),E_INVALIDARG);
         ASSERT_EQ(comp->put_GrossSlabDepth(8),S_OK);

         ASSERT_EQ(comp->put_SacrificialDepth(-1),E_INVALIDARG);
         ASSERT_EQ(comp->put_SacrificialDepth(1),S_OK);
         comp->get_GrossSlabDepth(&val);
         ASSERT_EQ(IsEqual(val,8.0),true);

         ASSERT_EQ(comp->put_SacrificialDepth(9),S_OK);
         comp->get_GrossSlabDepth(&val);
         ASSERT_EQ(IsEqual(val,16.0),true);

         // Check Q and QSlab for a real beam
         CComPtr<IPlateGirder> beam;
         beam.CoCreateInstance(CLSID_PlateGirder);
         beam->put_TopFlangeWidth(22);
         beam->put_TopFlangeThickness(1.25);
         beam->put_BottomFlangeWidth(22);
         beam->put_BottomFlangeThickness(2.25);
         beam->put_WebWidth(0.438);
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
         ASSERT_EQ(comp->get_QSlab(nullptr),E_POINTER);
         ASSERT_EQ(comp->get_QSlab(&Q),S_OK);
         ASSERT_EQ(IsEqual(Q,3651.6,0.1),true);

         // q top flange + slab
         ASSERT_EQ(comp->get_Q(124.25,nullptr),E_POINTER);
         ASSERT_EQ(comp->get_Q(-1,&Q),E_INVALIDARG);
         ASSERT_EQ(comp->get_Q(124.25,&Q),S_OK);
         ASSERT_EQ(IsEqual(Q,4867.5,0.1),true);

         // q bottom flange
         ASSERT_EQ(comp->get_Q(2.25,&Q),S_OK);
         ASSERT_EQ(IsEqual(Q,3937.1,0.1),true);

        ///////////////////////////////////////
         // Test ISupportErrorInfo
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_CompositeBeam ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ICompositeBeam ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISection ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         //////////////////////////////////////////////////////////////
         // Test IObjectSafety
         CComPtr<IObjectSafety> pObjSafety;
         ASSERT_EQ(pObjSafety.CoCreateInstance(CLSID_CompositeBeam), S_OK);
         DWORD dwDesiredOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
         DWORD dwSupportedOptions, dwEnabledOptions;
         pObjSafety->GetInterfaceSafetyOptions(IID_ICompositeBeam,&dwSupportedOptions,&dwEnabledOptions);
         ASSERT_EQ( dwSupportedOptions, dwDesiredOptions );
         pObjSafety->GetInterfaceSafetyOptions(IID_ISection,&dwSupportedOptions,&dwEnabledOptions);
         ASSERT_EQ( dwSupportedOptions, dwDesiredOptions );
         pObjSafety->GetInterfaceSafetyOptions(IID_IXYPosition,&dwSupportedOptions,&dwEnabledOptions);
         ASSERT_EQ( dwSupportedOptions, dwDesiredOptions );
   }

   TEST_METHOD(TestISection)
   {
         CComPtr<ICompositeBeam> comp;
         ASSERT_EQ(comp.CoCreateInstance(CLSID_CompositeBeam),S_OK);

         // define the girder (Plate Girder I-Beam)
         CComPtr<IPlateGirder> beam;
         beam.CoCreateInstance(CLSID_PlateGirder);
         beam->put_TopFlangeWidth(22);
         beam->put_TopFlangeThickness(1.25);
         beam->put_BottomFlangeWidth(22);
         beam->put_BottomFlangeThickness(2.25);
         beam->put_WebWidth(0.438);
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
         ASSERT_EQ(section->get_BoundingBox(nullptr),E_POINTER);
         ASSERT_EQ(section->get_BoundingBox(&box),S_OK);
         Float64 l,r,t,b;
         box->get_Left(&l);
         box->get_Right(&r);
         box->get_Top(&t);
         box->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,-42.),true);
         ASSERT_EQ(IsEqual(r, 42.),true);
         ASSERT_EQ(IsEqual(t,133.),true);
         ASSERT_EQ(IsEqual(b,0.),true);

         // Elastic Properties
         CComPtr<IElasticProperties> props;
         ASSERT_EQ(section->get_ElasticProperties(nullptr),E_POINTER);
         ASSERT_EQ(section->get_ElasticProperties(&props),S_OK);
         Float64 val;
         props->get_EA(&val);
         ASSERT_EQ(IsEqual(val,205.311),true);

         props->get_EIxx(&val);
         ASSERT_EQ(IsEqual(val,627807.85259178),true);

         props->get_EIyy(&val);
         ASSERT_EQ(IsEqual(val,46379.979281332),true);

         props->get_EIxy(&val);
         ASSERT_EQ(IsEqual(val,0.),true);

         props->get_Xleft(&val);
         ASSERT_EQ(IsEqual(val,42.),true);

         props->get_Xright(&val);
         ASSERT_EQ(IsEqual(val,42.),true);

         props->get_Ytop(&val);
         ASSERT_EQ(IsEqual(val,52.338305059154),true);

         props->get_Ybottom(&val);
         ASSERT_EQ(IsEqual(val,80.661694640846),true);

         CComPtr<IPoint2d> cg;
         props->get_Centroid(&cg);
         cg->get_X(&val);
         ASSERT_EQ(IsEqual(val,0.),true);
         cg->get_Y(&val);
         ASSERT_EQ(IsEqual(val,80.661694640846),true);

         // Check mass properties
         CComPtr<IMassProperties> mprops;
         ASSERT_EQ(section->get_MassProperties(nullptr),E_POINTER);
         ASSERT_EQ(section->get_MassProperties(&mprops),S_OK);
         mprops->get_MassPerLength(&val);
         ASSERT_EQ(IsEqual(val,150623.12),true);

         // Test ClipIn
         // Clip so that only the top 1" of the slab remains
         CComPtr<IRect2d> clipRect;
         clipRect.CoCreateInstance(CLSID_Rect2d);
         clipRect->put_Left(-1000);
         clipRect->put_Right(1000);
         clipRect->put_Bottom(132.);
         clipRect->put_Top(1000);

         CComPtr<ISection> clipSection;
         ASSERT_EQ(section->ClipIn(nullptr,&clipSection),E_INVALIDARG);
         ASSERT_EQ(section->ClipIn(clipRect,nullptr),E_POINTER);
         ASSERT_EQ(section->ClipIn(clipRect,&clipSection),S_OK);
         props.Release();
         clipSection->get_ElasticProperties(&props);
         props->get_EA(&val);
         ASSERT_EQ(IsEqual(val,84.*1.*0.125),true);

         // Test clip with line
         CComPtr<IPoint2d> p1;
         CComPtr<IPoint2d> p2;
         clipRect->get_BottomRight(&p1);
         clipRect->get_BottomLeft(&p2);

         CComPtr<ILine2d> clipLine;
         clipLine.CoCreateInstance(CLSID_Line2d);
         clipLine->ThroughPoints(p1,p2);

         clipSection.Release();
         ASSERT_EQ(section->ClipWithLine(nullptr,&clipSection),E_INVALIDARG);
         ASSERT_EQ(section->ClipWithLine(clipLine,nullptr),E_POINTER);
         ASSERT_EQ(section->ClipWithLine(clipLine,&clipSection),S_OK);

         props.Release();
         clipSection->get_ElasticProperties(&props);
         props->get_EA(&val);
         ASSERT_EQ(IsEqual(val,84.*1.*0.125),true);

         // Test Clone
         CComPtr<ISection> cloneSection;
         ASSERT_EQ(section->Clone(nullptr),E_POINTER);
         ASSERT_EQ(section->Clone(&cloneSection),S_OK);

         CComQIPtr<ICompositeBeam> cloneComp(cloneSection);
         ASSERT_EQ(cloneComp != nullptr,true);
         cloneComp->get_GrossSlabDepth(&val);
         ASSERT_EQ(IsEqual(val,7.),true);
         cloneComp->get_EffectiveSlabWidth(&val);
         ASSERT_EQ(IsEqual(val,84.),true);
         cloneComp->get_TributarySlabWidth(&val);
         ASSERT_EQ(IsEqual(val,84.),true);
         cloneComp->get_HaunchDepth(&val);
         ASSERT_EQ(IsEqual(val,0.5),true);
         cloneComp->get_HaunchWidth(&val);
         ASSERT_EQ(IsEqual(val,22.),true);

         CComPtr<IShape> cloneShape;
         cloneComp->get_Beam(&cloneShape);
         CComQIPtr<IPlateGirder> cloneBeam(cloneShape);
         ASSERT_EQ(cloneBeam != nullptr,true);
         cloneBeam->get_WebHeight(&val);
         ASSERT_EQ(IsEqual(val,122.),true);
         cloneBeam->get_WebWidth(&val);
         ASSERT_EQ(IsEqual(val,0.438),true);
         cloneBeam->get_TopFlangeWidth(&val);
         ASSERT_EQ(IsEqual(val,22.),true);
         cloneBeam->get_TopFlangeThickness(&val);
         ASSERT_EQ(IsEqual(val,1.25),true);
         cloneBeam->get_BottomFlangeWidth(&val);
         ASSERT_EQ(IsEqual(val,22.),true);
         cloneBeam->get_BottomFlangeThickness(&val);
         ASSERT_EQ(IsEqual(val,2.25),true);
   }

   TEST_METHOD(TestIXYPosition)
   {
         CComPtr<ICompositeBeam> comp;
         ASSERT_EQ(comp.CoCreateInstance(CLSID_CompositeBeam),S_OK);

         // define the girder (Plate Girder I-Beam)
         CComPtr<IPlateGirder> beam;
         beam.CoCreateInstance(CLSID_PlateGirder);
         beam->put_TopFlangeWidth(22);
         beam->put_TopFlangeThickness(1.25);
         beam->put_BottomFlangeWidth(22);
         beam->put_BottomFlangeThickness(2.25);
         beam->put_WebWidth(0.438);
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
         ASSERT_EQ( position->OffsetEx(nullptr), E_INVALIDARG );
         ASSERT_EQ( position->OffsetEx(size), S_OK );

         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);

         ASSERT_EQ( IsEqual(x,10.), true );
         ASSERT_EQ( IsEqual(y,20.), true );

         ASSERT_EQ( position->Offset(10,20), S_OK );

         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);

         ASSERT_EQ( IsEqual(x,20.), true );
         ASSERT_EQ( IsEqual(y,40.), true );

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

         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);

         ASSERT_EQ( IsEqual(x,120.), true );
         ASSERT_EQ( IsEqual(y,140.), true );

         //
         // LocatorPoint property
         //

         to->Move(0,0);
         ASSERT_EQ( position->put_LocatorPoint(lpBottomCenter,to), S_OK );

         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);

         ASSERT_EQ( IsEqual(x,0.), true );
         ASSERT_EQ( IsEqual(y,0.), true );

         ASSERT_EQ( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

         // BottomLeft
         to->Move(58,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpBottomLeft,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomLeft,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 58.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // BottomCenter
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpBottomCenter,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomCenter,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // BottomRight
         to->Move(142,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpBottomRight,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomRight,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,142.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // CenterLeft
         to->Move(58,166.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpCenterLeft,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpCenterLeft,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 58.0), true );
         ASSERT_EQ( IsEqual(y,166.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // CenterCenter
         to->Move(100,166.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpCenterCenter,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpCenterCenter,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,166.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // CenterRight
         to->Move(142,166.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpCenterRight,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpCenterRight,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,142.0), true );
         ASSERT_EQ( IsEqual(y,166.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // TopLeft
         to->Move(58,233);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpTopLeft,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpTopLeft,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 58.0), true );
         ASSERT_EQ( IsEqual(y,233.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // TopCenter
         to->Move(100,233);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpTopCenter,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpTopCenter,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,233.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // TopRight
         to->Move(142,233);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpTopRight,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpTopRight,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,142.0), true );
         ASSERT_EQ( IsEqual(y,233.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         // HookPoint
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpHookPoint,to), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpHookPoint,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         //
         // Rotate and RotateEx
         //
         CComPtr<IPoint2d> rotPoint;
         rotPoint.CoCreateInstance( CLSID_Point2d );

         // Rotate about the origin of the coordinate system and check the bounding box
         to->Move(100,100);
         ASSERT_EQ( position->put_LocatorPoint(lpBottomCenter,to), S_OK );
         rotPoint->Move(0,0);

         ASSERT_EQ( position->RotateEx(nullptr,PI_OVER_2), E_INVALIDARG );
         ASSERT_EQ( position->RotateEx(rotPoint,PI_OVER_2), S_OK );

         CComQIPtr<ISection> section(position);
         CComPtr<IRect2d> box;
         section->get_BoundingBox(&box);
         Float64 l,r,t,b;
         box->get_Left(&l);
         box->get_Right(&r);
         box->get_Top(&t);
         box->get_Bottom(&b);
         ASSERT_EQ(IsEqual(l,-233.),true);
         ASSERT_EQ(IsEqual(r,-100.),true);
         ASSERT_EQ(IsEqual(t,311.),true);
         ASSERT_EQ(IsEqual(b,58.),true);
   }
};
} // namespace GeometryUnitTests