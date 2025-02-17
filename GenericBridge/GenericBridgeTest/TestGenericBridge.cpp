///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
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

// TestGenericBridge.cpp: implementation of the CTestGenericBridge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestGenericBridge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

constexpr IDType ALIGNMENT_ID = 0;
constexpr IDType PROFILE_ID = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestGenericBridge::CTestGenericBridge()
{

}

CTestGenericBridge::~CTestGenericBridge()
{

}

void CTestGenericBridge::Test()
{
   // Create a bridge
   CComPtr<IGenericBridge> bridge;
   CreateBridgeModel(&bridge);

   TestPiers(bridge);
   TestSegments(bridge);

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(bridge);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IGenericBridge ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(bridge,IID_IGenericBridge,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(bridge,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

void CTestGenericBridge::TestPiers(IGenericBridge* bridge)
{
   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   PierIndexType nPiers;
   piers->get_Count(&nPiers);
   TRY_TEST(nPiers,2);

   for ( PierIndexType pierIdx = 0; pierIdx < nPiers; pierIdx++ )
   {
      CComPtr<IBridgePier> pier;
      piers->get_Item(pierIdx,&pier);

      CComPtr<IStation> station;
      pier->get_Station(&station);
      Float64 value;
      station->get_Value(&value);

      if ( pierIdx == 0 )
      {
         TRY_TEST(IsEqual(value,0.00),true);
      }
      else
      {
         TRY_TEST(IsEqual(value,100.00),true);
      }
   }
}

void CTestGenericBridge::TestSegments(IGenericBridge* bridge)
{
   for ( GirderIndexType gdrIdx = 0; gdrIdx < 6; gdrIdx++ )
   {
      GirderIDType id = (GirderIDType)gdrIdx;
      CComPtr<ISuperstructureMember> ssMbr;
      TRY_TEST(bridge->get_SuperstructureMember(id,&ssMbr),S_OK);

      IndexType nSegments;
      ssMbr->get_SegmentCount(&nSegments);
      ATLASSERT(nSegments == 1);

      CComPtr<ISuperstructureMemberSegment> segment;
      ssMbr->get_Segment(0,&segment);

      Float64 length;
      segment->get_Length(&length);

      TRY_TEST(IsEqual(length,100.0),true);

      CComPtr<ISection> section;
      segment->get_Section(0,length/2,sbLeft,cstBridge,&section);

      CComPtr<IElasticProperties> elasticProps;
      section->get_ElasticProperties(&elasticProps);

      CComPtr<IShapeProperties> props;
      elasticProps->TransformProperties(1.0,&props);

      Float64 area;
      props->get_Area(&area);
      TRY_TEST(IsEqual(area,923.53125),true);
   }
}

void CTestGenericBridge::CreateBridgeModel(IGenericBridge** ppBridge)
{
   CComPtr<IGenericBridge> bridge;
   TRY_TEST(bridge.CoCreateInstance(CLSID_GenericBridge),S_OK);

   CreateAlignment(bridge);
   CreatePiers(bridge);
   CreateGirders(bridge);

   bridge.CopyTo(ppBridge);
}

void CTestGenericBridge::CreateAlignment(IGenericBridge* bridge)
{
   CComPtr<IBridgeGeometry> geometry;
   TRY_TEST(bridge->get_BridgeGeometry(&geometry),S_OK);

   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);
   CComPtr<IPoint2d> p1, p2;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0, 0);
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(100, 0);
   CComPtr<IPathSegment> segment;
   segment.CoCreateInstance(CLSID_PathSegment);
   segment->ThroughPoints(p1, p2);
   CComQIPtr<IPathElement> element(segment);
   alignment->AddPathElement(element);

   geometry->AddAlignment(ALIGNMENT_ID, alignment);
   geometry->put_BridgeAlignmentID(ALIGNMENT_ID);

   CComPtr<IProfile> profile;
   profile.CoCreateInstance(CLSID_Profile);
   alignment->AddProfile(PROFILE_ID, profile);
   geometry->put_ProfileID(PROFILE_ID);
   //geometry->put_SurfaceID(SURFACE_ID);
}

void CTestGenericBridge::CreatePiers(IGenericBridge* bridge)
{
   CComPtr<IBridgeGeometry> geometry;
   bridge->get_BridgeGeometry(&geometry);

   Float64 pier_length = 20;

   CComPtr<ISinglePierLineFactory> pier_1_factory;
   pier_1_factory.CoCreateInstance(CLSID_SinglePierLineFactory);
   pier_1_factory->put_PierLineID(0);
   pier_1_factory->put_AlignmentID(ALIGNMENT_ID);
   pier_1_factory->put_Station(CComVariant(0.0));
   pier_1_factory->put_Direction(CComBSTR("NORMAL"));
   pier_1_factory->put_Length(pier_length);
   pier_1_factory->put_Offset(pier_length / 2);
   geometry->AddPierLineFactory(pier_1_factory);

   CComPtr<ISinglePierLineFactory> pier_2_factory;
   pier_2_factory.CoCreateInstance(CLSID_SinglePierLineFactory);
   pier_2_factory->put_PierLineID(1);
   pier_2_factory->put_AlignmentID(ALIGNMENT_ID);
   pier_2_factory->put_Station(CComVariant(100.0));
   pier_2_factory->put_Direction(CComBSTR("NORMAL"));
   pier_2_factory->put_Length(pier_length);
   pier_2_factory->put_Offset(pier_length / 2);
   geometry->AddPierLineFactory(pier_2_factory);
}

void CTestGenericBridge::CreateGirders(IGenericBridge* bridge)
{
   CComPtr<IBridgeGeometry> geometry;
   bridge->get_BridgeGeometry(&geometry);

   Float64 spacing = 6.0;
   GirderIndexType nGirders = 6;

   Float64 width = spacing*(nGirders-1);

   Float64 offset = -width/2;


   // Create a girder layout line
   // Layout line is parallel to and offset from the alignment
   // Layout line IDs are the girder index
   CComPtr<IAlignmentOffsetLayoutLineFactory> factory;
   factory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory);
   factory->put_LayoutLineID(0); // ID of first layout line
   factory->put_LayoutLineIDIncrement(1);
   factory->put_LayoutLineCount(nGirders);
   factory->put_Offset(offset);
   factory->put_OffsetIncrement(spacing);
   factory->put_AlignmentID(ALIGNMENT_ID);
   geometry->AddLayoutLineFactory(factory);

   //
   // Build Girder Lines and Superstructure Members
   //


   for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirders; gdrIdx++ )
   {
      IDType gdrID = IDType(gdrIdx);

      CComPtr<ISingleGirderLineFactory> glFactory;
      glFactory.CoCreateInstance(CLSID_SingleGirderLineFactory);
      glFactory->put_GirderLineID( gdrID );   // girder line ID
      glFactory->put_LayoutLineID(gdrID);     // layout line used to layout this girder line
      glFactory->put_Type(glChord);           // layout as a chord
      glFactory->put_StartPierID(0); 
      glFactory->put_EndPierID(1);
      geometry->AddGirderLineFactory(glFactory);

      GirderIDType leftSSMbrID = (gdrIdx == 0 ? INVALID_ID : (GirderIDType)(gdrIdx - 1));
      GirderIDType rightSSMbrID = (gdrIdx == nGirders-1 ? INVALID_ID : (GirderIDType)(gdrIdx + 1));

      CComPtr<ISuperstructureMember> ssmbr;
      bridge->CreateSuperstructureMember(gdrID,leftSSMbrID,rightSSMbrID,&ssmbr);

      GirderIDType id;
      ssmbr->get_ID(&id);
      TRY_TEST(id,gdrID);

      CComPtr<IFlangedGirderSection> section;
      TRY_TEST(section.CoCreateInstance(CLSID_FlangedGirderSection),S_OK);

      CComPtr<IPrecastBeam> beam;
      beam.CoCreateInstance(CLSID_PrecastBeam);

      // WF74G
      beam->put_D1(3.0);
      beam->put_D2(3.0);
      beam->put_D3(3.0);
      beam->put_D4(5.125);
      beam->put_D5(4.5);
      beam->put_D6(3.0);
      beam->put_D7(52.375);
      beam->put_W1(18.4375);
      beam->put_W2(3.0);
      beam->put_W3(13.125);
      beam->put_W4(3.0);
      beam->put_T1(6.125);
      beam->put_T2(6.125);
      beam->put_C1(1.0);

      section->put_Beam(beam);

      CComPtr<IMaterial> material;
      material.CoCreateInstance(CLSID_Material);
      material->put_E(0,1.0);
      material->put_Density(0,1.0);

      CComPtr<IFlangedGirderEndBlockSegment> segment;
      segment.CoCreateInstance(CLSID_FlangedGirderEndBlockSegment);

      CComQIPtr<IShape> shape(section);
      ATLASSERT(shape);
      segment->AddShape(shape,material,nullptr);
      
      CComPtr<IGirderLine> girderline;
      geometry->FindGirderLine(gdrID,&girderline);
      TRY_TEST(girderline != nullptr,true);
      segment->putref_GirderLine(girderline);

      TRY_TEST(ssmbr->AddSegment(segment),S_OK);
   }
}
