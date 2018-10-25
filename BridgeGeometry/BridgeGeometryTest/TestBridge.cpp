#include "StdAfx.h"
#include "TestBridge.h"
#include <WBFLBridgeGeometry.h>

CTestBridge::CTestBridge(void)
{
}

CTestBridge::~CTestBridge(void)
{
}

void CTestBridge::CreateStraightAlignment(Float64 refStation,Float64 x,Float64 y,Float64 direction,IAlignment** ppAlignment)
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);

   CComPtr<IPoint2d> start, end;
   ls->get_StartPoint(&start);
   ls->get_EndPoint(&end);

   start->Move(x,y);

   x += 100*cos(direction);
   y += 100*sin(direction);
   end->Move(x,y);

   alignment->AddEx(ls);
   alignment->put_RefStation(CComVariant(refStation));

   alignment.CopyTo(ppAlignment);
}

void CTestBridge::CreateBridge(IBridgeGeometry** ppBridge)
{
   // set up the coordinate geometry model
   CComPtr<ICogoModel> cogoModel;
   TRY_TEST(cogoModel.CoCreateInstance(CLSID_CogoModel),S_OK);

   //// add the alignment
   CComPtr<IPathCollection> alignments;
   cogoModel->get_Alignments(&alignments);

   // N 45 E, (10.0,10.0) at Station 0+00
   CComPtr<IAlignment> alignment;
   CreateStraightAlignment(0.00,10.0,10.0,M_PI/4,&alignment);
   //CreateStraightAlignment(0.00,00.0,00.0,0.00,&alignment);
   alignments->AddEx(0,alignment);

   // create the bridge model
   CComPtr<IBridgeGeometry> bridge;
   TRY_TEST(bridge.CoCreateInstance(CLSID_BridgeGeometry),S_OK);

   // initialize with the cogo model and alignment
   TRY_TEST(bridge->putref_CogoModel(cogoModel),S_OK);
   TRY_TEST(bridge->putref_Alignment(999,alignment),S_OK);
   TRY_TEST(bridge->put_BridgeAlignmentID(999),S_OK);

   // build the model
   Float64 pierWidth = 20;

   // Pier 1, ID 100, Station 1+00
   CComPtr<IPierLine> pier1;
   TRY_TEST(bridge->CreatePierLine(100,999,CComVariant(100.00),CComBSTR("45 L"),pierWidth,pierWidth/2,&pier1),S_OK);

   // Pier 2, ID 200, Station 2+00
   CComPtr<IPierLine> pier2;
   TRY_TEST(bridge->CreatePierLine(200,999,CComVariant(200.00),CComBSTR("45 L"),pierWidth,pierWidth/2,&pier2),S_OK);

   // Pier 3, ID 300, Station 3+00
   CComPtr<IPierLine> pier3;
   TRY_TEST(bridge->CreatePierLine(300,999,CComVariant(300.00),CComBSTR("45 L"),pierWidth,pierWidth/2,&pier3),S_OK);

   // Create a girder layout line
   // Layout line is parallel to and offset from the alignment
   CComPtr<IAlignmentOffsetLayoutLineFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory),S_OK);
   TRY_TEST(factory->put_LayoutLineID(100),S_OK); // ID of layout line
   TRY_TEST(factory->put_LayoutLineIDInc(1),S_OK);
   TRY_TEST(factory->put_LayoutLineCount(5),S_OK);
   TRY_TEST(factory->put_Offset(10.0),S_OK); // offset from alignment (10 ft left)
   TRY_TEST(factory->put_OffsetIncrement(-5.0),S_OK); // each subsequent layout line is 5 ft to the right of the previous
   TRY_TEST(factory->put_AlignmentID(999),S_OK);
   TRY_TEST(bridge->CreateLayoutLines(factory),S_OK); // create it

   // Create a girder line
   CComPtr<ISimpleGirderLineFactory> glFactory;
   glFactory.CoCreateInstance(CLSID_SimpleGirderLineFactory);
   glFactory->put_GirderLineID(500); // girder line ID
   glFactory->put_GirderLineIDInc(1);
   glFactory->put_LeftLayoutLineID(100); // layout line used to layout this girder line
   glFactory->put_RightLayoutLineID(104); // layout line used to layout this girder line
   glFactory->put_LayoutLineIDInc(1); // layout line used to layout this girder line
   glFactory->put_Type(glChord); // layout as a chord
   glFactory->put_StartPierID(100); // layout between piers 100 and 300
   glFactory->put_EndPierID(300);
   glFactory->put_PierIDInc(100);
   glFactory->put_Continuous(VARIANT_FALSE);
   TRY_TEST(bridge->CreateGirderLines(glFactory),S_OK);

   bridge.CopyTo(ppBridge);
}

void CTestBridge::Test()
{
   Test1();
   Test2();
   Test3();
   Test4();
   TestDiaphragmLayout();
   TestSlabLayout();
}

void CTestBridge::Test1(void)
{
   // set up the coordinate geometry model
   CComPtr<ICogoModel> cogoModel;
   TRY_TEST(cogoModel.CoCreateInstance(CLSID_CogoModel),S_OK);

   //// add the alignment
   CComPtr<IPathCollection> alignments;
   cogoModel->get_Alignments(&alignments);

   // N 45 E, (10.0,10.0) at Station 0+00
   CComPtr<IAlignment> alignment;
   CreateStraightAlignment(0.00,10.0,10.0,M_PI/4,&alignment);
   alignments->AddEx(0,alignment);

   // create the bridge model
   CComPtr<IBridgeGeometry> bridge;
   TRY_TEST(bridge.CoCreateInstance(CLSID_BridgeGeometry),S_OK);

   // initialize with the cogo model and alignment
   TRY_TEST(bridge->putref_CogoModel(NULL),E_INVALIDARG);
   TRY_TEST(bridge->putref_CogoModel(cogoModel),S_OK);
   TRY_TEST(bridge->putref_CogoModel(cogoModel),BRIDGEGEOMETRY_E_INITIALIZATION);

   TRY_TEST(bridge->putref_Alignment(999,NULL),E_INVALIDARG);
   TRY_TEST(bridge->putref_Alignment(999,alignment),S_OK);
   TRY_TEST(bridge->put_BridgeAlignmentID(999),S_OK);

   // build the model
   Float64 pierWidth = 20;

   // Pier 1, ID 100, Station 1+00
   CComPtr<IPierLine> pier1;
   TRY_TEST(bridge->CreatePierLine(100,999,CComVariant((IUnknown*)NULL),CComBSTR("N 45 W"),pierWidth,pierWidth/2,&pier1),BRIDGEGEOMETRY_E_INVALIDSTATION);
   TRY_TEST(bridge->CreatePierLine(100,999,CComVariant(100.00),CComBSTR("N 45 W"),pierWidth,pierWidth/2,&pier1),S_OK);

   // Pier 2, ID 200, Station 2+00
   CComPtr<IPierLine> pier2;
   TRY_TEST(bridge->CreatePierLine(100,999,CComVariant(200.00),CComBSTR("NORMAL"),pierWidth,pierWidth/2,&pier2),BRIDGEGEOMETRY_E_ID);
   TRY_TEST(bridge->CreatePierLine(200,999,CComVariant(200.00),CComBSTR("NORMAL"),pierWidth,pierWidth/2,&pier2),S_OK);

   pier1.Release();
   pier2.Release();
   TRY_TEST(bridge->FindPierLine(0,&pier1),E_FAIL);
   TRY_TEST(bridge->FindPierLine(100,&pier1),S_OK);
   TRY_TEST(bridge->FindPierLine(200,&pier2),S_OK);

   // Define the bearing offset
   pier1->put_BearingOffset(pfAhead,2.5);
   pier1->put_BearingOffsetMeasurementType(pfAhead,mtNormal);

   pier2->put_BearingOffset(pfBack,2.5);
   pier2->put_BearingOffsetMeasurementType(pfBack,mtNormal);

   // Define the girder end distance
   pier1->put_EndDistance(pfAhead,1.0);
   pier1->put_EndDistanceMeasurementType(pfAhead,mtNormal);
   pier1->put_EndDistanceMeasurementLocation(pfAhead,mlCenterlineBearing);

   pier2->put_EndDistance(pfBack,1.0);
   pier2->put_EndDistanceMeasurementType(pfBack,mtNormal);
   pier2->put_EndDistanceMeasurementLocation(pfBack,mlCenterlineBearing);

   // Create a girder layout line
   // Layout line is parallel to and offset from the alignment
   CComPtr<IAlignmentOffsetLayoutLineFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory),S_OK);
   TRY_TEST(factory->put_LayoutLineID(100),S_OK); // ID of layout line
   TRY_TEST(factory->put_Offset(0.0),S_OK); // offset from alignment
   TRY_TEST(factory->put_AlignmentID(999),S_OK); // offset from alignment 999
   TRY_TEST(bridge->CreateLayoutLines(factory),S_OK); // create it

   // Create a girder lline
   CComPtr<ISingleGirderLineFactory> glFactory;
   glFactory.CoCreateInstance(CLSID_SingleGirderLineFactory);
   glFactory->put_GirderLineID(500); // girder line ID
   glFactory->put_LayoutLineID(100); // layout line used to layout this girder line
   glFactory->put_Type(glChord); // layout as a chord
   glFactory->put_StartPierID(100); // layout between piers 100 an d200
   glFactory->put_EndPierID(200);
   TRY_TEST(bridge->CreateGirderLines(glFactory),S_OK);

   // compute geometric parameters
   TRY_TEST(bridge->UpdateGeometry(),S_OK);

   // get geometric parameters
   CComPtr<IPierLine> pier;
   TRY_TEST(bridge->GetPierLine(0,&pier),S_OK);

   CComPtr<IPoint2d> point;
   TRY_TEST(pier->get_AlignmentPoint(&point),S_OK);

   Float64 x,y;
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,80.710678),true);
   TRY_TEST(IsEqual(y,80.710678),true);

   CComPtr<IDirection> direction;
   CComPtr<IAngle> skew;
   pier->get_Direction(&direction);
   pier->get_Skew(&skew);
   direction->get_Value(&x);
   TRY_TEST(IsEqual(x,3*M_PI/4),true);
   skew->get_Value(&x);
   TRY_TEST(IsEqual(x,0.0),true);


   // pier 2
   pier.Release();
   TRY_TEST(bridge->FindPierLine(200,&pier),S_OK);

   point.Release();
   TRY_TEST(pier->get_AlignmentPoint(&point),S_OK);

   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,151.421356),true);
   TRY_TEST(IsEqual(y,151.421356),true);

   direction.Release();
   skew.Release();
   pier->get_Direction(&direction);
   pier->get_Skew(&skew);
   direction->get_Value(&x);
   TRY_TEST(IsEqual(x,3*M_PI/4),true);
   skew->get_Value(&x);
   TRY_TEST(IsEqual(x,0.0),true);

   // girder line geometry
   CComPtr<IGirderLine> girderLine;
   TRY_TEST(bridge->FindGirderLine(500,&girderLine),S_OK);
   TRY_TEST(girderLine->get_LayoutLength(&x),S_OK);
   TRY_TEST(IsEqual(x,100.0),true);

   point.Release();
   TRY_TEST(girderLine->get_PierPoint(etStart,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,80.710678),true);
   TRY_TEST(IsEqual(y,80.710678),true);

   point.Release();
   TRY_TEST(girderLine->get_PierPoint(etEnd,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,151.421356),true);
   TRY_TEST(IsEqual(y,151.421356),true);


   point.Release();
   TRY_TEST(girderLine->get_BearingPoint(etStart,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,80.710678+2.5*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,80.710678+2.5*pow(2,0.5)/2),true);

   point.Release();
   TRY_TEST(girderLine->get_BearingPoint(etEnd,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,151.421356-2.5*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,151.421356-2.5*pow(2,0.5)/2),true);


   point.Release();
   TRY_TEST(girderLine->get_EndPoint(etStart,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,80.710678+1.5*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,80.710678+1.5*pow(2,0.5)/2),true);

   point.Release();
   TRY_TEST(girderLine->get_EndPoint(etEnd,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,151.421356-1.5*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,151.421356-1.5*pow(2,0.5)/2),true);



   // Try a different girder end geometry

   // Define the girder end distance
   pier1->put_EndDistance(pfAhead,1.0);
   pier1->put_EndDistanceMeasurementType(pfAhead,mtNormal);
   pier1->put_EndDistanceMeasurementLocation(pfAhead,mlCenterlinePier);

   pier2->put_EndDistance(pfBack,1.0);
   pier2->put_EndDistanceMeasurementType(pfBack,mtNormal);
   pier2->put_EndDistanceMeasurementLocation(pfBack,mlCenterlinePier);

   bridge->UpdateGeometry();

   point.Release();
   TRY_TEST(girderLine->get_EndPoint(etStart,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,80.710678+1.0*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,80.710678+1.0*pow(2,0.5)/2),true);

   point.Release();
   TRY_TEST(girderLine->get_EndPoint(etEnd,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,151.421356-1.0*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,151.421356-1.0*pow(2,0.5)/2),true);


   // Try a different method for locating the centerline bearing
   pier1->put_BearingOffsetMeasurementType(pfAhead,mtAlongItem);
   pier1->put_EndDistanceMeasurementLocation(pfAhead,mlCenterlineBearing);

   pier2->put_BearingOffsetMeasurementType(pfBack,mtAlongItem);
   pier2->put_EndDistanceMeasurementLocation(pfBack,mlCenterlineBearing);

   bridge->UpdateGeometry();


   point.Release();
   TRY_TEST(girderLine->get_BearingPoint(etStart,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,80.710678+2.5*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,80.710678+2.5*pow(2,0.5)/2),true);

   point.Release();
   TRY_TEST(girderLine->get_BearingPoint(etEnd,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,151.421356-2.5*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,151.421356-2.5*pow(2,0.5)/2),true);

   point.Release();
   TRY_TEST(girderLine->get_EndPoint(etStart,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,80.710678+1.5*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,80.710678+1.5*pow(2,0.5)/2),true);

   point.Release();
   TRY_TEST(girderLine->get_EndPoint(etEnd,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,151.421356-1.5*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,151.421356-1.5*pow(2,0.5)/2),true);


   // Try a different girder end geometry
   pier1->put_BearingOffsetMeasurementType(pfAhead,mtAlongItem);
   pier1->put_EndDistanceMeasurementLocation(pfAhead,mlCenterlinePier);

   pier2->put_BearingOffsetMeasurementType(pfBack,mtAlongItem);
   pier2->put_EndDistanceMeasurementLocation(pfBack,mlCenterlinePier);

   bridge->UpdateGeometry();

   point.Release();
   TRY_TEST(girderLine->get_EndPoint(etStart,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,80.710678+1.0*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,80.710678+1.0*pow(2,0.5)/2),true);

   point.Release();
   TRY_TEST(girderLine->get_EndPoint(etEnd,&point),S_OK);
   point->Location(&x,&y);
   TRY_TEST(IsEqual(x,151.421356-1.0*pow(2,0.5)/2),true);
   TRY_TEST(IsEqual(y,151.421356-1.0*pow(2,0.5)/2),true);
}

void CTestBridge::Test2(void)
{
   // set up the coordinate geometry model
   CComPtr<ICogoModel> cogoModel;
   TRY_TEST(cogoModel.CoCreateInstance(CLSID_CogoModel),S_OK);

   //// add the alignment
   CComPtr<IPathCollection> alignments;
   cogoModel->get_Alignments(&alignments);

   // N 45 E, (10.0,10.0) at Station 0+00
   CComPtr<IAlignment> alignment;
   CreateStraightAlignment(0.00,10.0,10.0,M_PI/4,&alignment);
   alignments->AddEx(0,alignment);

   // create the bridge model
   CComPtr<IBridgeGeometry> bridge;
   TRY_TEST(bridge.CoCreateInstance(CLSID_BridgeGeometry),S_OK);

   // initialize with the cogo model and alignment
   TRY_TEST(bridge->putref_CogoModel(cogoModel),S_OK);
   TRY_TEST(bridge->putref_Alignment(999,alignment),S_OK);
   TRY_TEST(bridge->put_BridgeAlignmentID(999),S_OK);

   // build the model
   Float64 pierWidth = 20;

   // Pier 1, ID 100, Station 1+00
   CComPtr<IPierLine> pier1;
   TRY_TEST(bridge->CreatePierLine(100,999,CComVariant(100.00),CComBSTR("N 45 W"),pierWidth,pierWidth/2,&pier1),S_OK);

   // Pier 2, ID 200, Station 2+00
   CComPtr<IPierLine> pier2;
   TRY_TEST(bridge->CreatePierLine(200,999,CComVariant(200.00),CComBSTR("NORMAL"),pierWidth,pierWidth/2,&pier2),S_OK);

   // Pier 3, ID 300, Station 3+00
   CComPtr<IPierLine> pier3;
   TRY_TEST(bridge->CreatePierLine(300,999,CComVariant(300.00),CComBSTR("NORMAL"),pierWidth,pierWidth/2,&pier3),S_OK);

   // Create a girder layout line
   // Layout line is parallel to and offset from the alignment
   CComPtr<IAlignmentOffsetLayoutLineFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory),S_OK);
   TRY_TEST(factory->put_LayoutLineID(100),S_OK); // ID of layout line
   TRY_TEST(factory->put_LayoutLineIDInc(1),S_OK);
   TRY_TEST(factory->put_LayoutLineCount(5),S_OK);
   TRY_TEST(factory->put_Offset(-10.0),S_OK); // offset from alignment
   TRY_TEST(factory->put_OffsetIncrement(5.0),S_OK);
   TRY_TEST(factory->put_AlignmentID(999),S_OK);
   TRY_TEST(bridge->CreateLayoutLines(factory),S_OK); // create it

   // Create a girder line
   CComPtr<ISimpleGirderLineFactory> glFactory;
   glFactory.CoCreateInstance(CLSID_SimpleGirderLineFactory);
   glFactory->put_GirderLineID(500); // girder line ID
   glFactory->put_GirderLineIDInc(1);
   glFactory->put_LeftLayoutLineID(100); // layout line used to layout this girder line
   glFactory->put_RightLayoutLineID(104); // layout line used to layout this girder line
   glFactory->put_LayoutLineIDInc(1); // layout line used to layout this girder line
   glFactory->put_Type(glChord); // layout as a chord
   glFactory->put_StartPierID(100); // layout between piers 100 and 300
   glFactory->put_EndPierID(300);
   glFactory->put_PierIDInc(100);
   glFactory->put_Continuous(VARIANT_TRUE);
   TRY_TEST(bridge->CreateGirderLines(glFactory),S_OK);

   // compute geometric parameters
   TRY_TEST(bridge->UpdateGeometry(),S_OK);

   CollectionIndexType nGirderLines;
   TRY_TEST(bridge->get_GirderLineCount(NULL),E_POINTER);
   TRY_TEST(bridge->get_GirderLineCount(&nGirderLines),S_OK);
   TRY_TEST(nGirderLines,5);
}

void CTestBridge::Test3(void)
{
   // set up the coordinate geometry model
   CComPtr<ICogoModel> cogoModel;
   TRY_TEST(cogoModel.CoCreateInstance(CLSID_CogoModel),S_OK);

   //// add the alignment
   CComPtr<IPathCollection> alignments;
   cogoModel->get_Alignments(&alignments);

   // N 45 E, (10.0,10.0) at Station 0+00
   CComPtr<IAlignment> alignment;
   CreateStraightAlignment(0.00,10.0,10.0,M_PI/4,&alignment);
   alignments->AddEx(0,alignment);

   // create the bridge model
   CComPtr<IBridgeGeometry> bridge;
   TRY_TEST(bridge.CoCreateInstance(CLSID_BridgeGeometry),S_OK);

   // initialize with the cogo model and alignment
   TRY_TEST(bridge->putref_CogoModel(cogoModel),S_OK);
   TRY_TEST(bridge->putref_Alignment(999,alignment),S_OK);
   TRY_TEST(bridge->put_BridgeAlignmentID(999),S_OK);

   // build the model
   Float64 pierWidth = 20;

   // Pier 1, ID 100, Station 1+00
   CComPtr<IPierLine> pier1;
   TRY_TEST(bridge->CreatePierLine(100,999,CComVariant(100.00),CComBSTR("N 45 W"),pierWidth,pierWidth/2,&pier1),S_OK);

   // Pier 2, ID 200, Station 2+00
   CComPtr<IPierLine> pier2;
   TRY_TEST(bridge->CreatePierLine(200,999,CComVariant(200.00),CComBSTR("NORMAL"),pierWidth,pierWidth/2,&pier2),S_OK);

   // Pier 3, ID 300, Station 3+00
   CComPtr<IPierLine> pier3;
   TRY_TEST(bridge->CreatePierLine(300,999,CComVariant(300.00),CComBSTR("NORMAL"),pierWidth,pierWidth/2,&pier3),S_OK);

   // Create a girder layout line
   // Layout line is parallel to and offset from the alignment
   CComPtr<IAlignmentOffsetLayoutLineFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory),S_OK);
   TRY_TEST(factory->put_LayoutLineID(100),S_OK); // ID of layout line
   TRY_TEST(factory->put_LayoutLineIDInc(1),S_OK);
   TRY_TEST(factory->put_LayoutLineCount(5),S_OK);
   TRY_TEST(factory->put_Offset(-10.0),S_OK); // offset from alignment
   TRY_TEST(factory->put_AlignmentID(999),S_OK);
   TRY_TEST(factory->put_OffsetIncrement(5.0),S_OK);
   TRY_TEST(bridge->CreateLayoutLines(factory),S_OK); // create it

   // Create a girder line
   CComPtr<ISimpleGirderLineFactory> glFactory;
   glFactory.CoCreateInstance(CLSID_SimpleGirderLineFactory);
   glFactory->put_GirderLineID(500); // girder line ID
   glFactory->put_GirderLineIDInc(1);
   glFactory->put_LeftLayoutLineID(100); // layout line used to layout this girder line
   glFactory->put_RightLayoutLineID(104); // layout line used to layout this girder line
   glFactory->put_LayoutLineIDInc(1); // layout line used to layout this girder line
   glFactory->put_Type(glChord); // layout as a chord
   glFactory->put_StartPierID(100); // layout between piers 100 and 300
   glFactory->put_EndPierID(300);
   glFactory->put_PierIDInc(100);
   glFactory->put_Continuous(VARIANT_FALSE);
   TRY_TEST(bridge->CreateGirderLines(glFactory),S_OK);

   // compute geometric parameters
   TRY_TEST(bridge->UpdateGeometry(),S_OK);

   CollectionIndexType nGirderLines;
   TRY_TEST(bridge->get_GirderLineCount(NULL),E_POINTER);
   TRY_TEST(bridge->get_GirderLineCount(&nGirderLines),S_OK);
   TRY_TEST(nGirderLines,10);
}

void CTestBridge::Test4(void)
{
   // set up the coordinate geometry model
   CComPtr<ICogoModel> cogoModel;
   TRY_TEST(cogoModel.CoCreateInstance(CLSID_CogoModel),S_OK);

   //// add the alignment
   CComPtr<IPathCollection> alignments;
   cogoModel->get_Alignments(&alignments);

   // N 45 E, (10.0,10.0) at Station 0+00
   CComPtr<IAlignment> alignment;
   CreateStraightAlignment(0.00,10.0,10.0,M_PI/4,&alignment);
   alignments->AddEx(0,alignment);

   // create the bridge model
   CComPtr<IBridgeGeometry> bridge;
   TRY_TEST(bridge.CoCreateInstance(CLSID_BridgeGeometry),S_OK);

   // initialize with the cogo model and alignment
   TRY_TEST(bridge->putref_CogoModel(cogoModel),S_OK);
   TRY_TEST(bridge->putref_Alignment(999,alignment),S_OK);
   TRY_TEST(bridge->put_BridgeAlignmentID(999),S_OK);

   // build the model
   Float64 pierWidth = 20;

   // Pier 1, ID 100, Station 1+00
   CComPtr<IPierLine> pier1;
   TRY_TEST(bridge->CreatePierLine(100,999,CComVariant(100.00),CComBSTR("N 45 W"),pierWidth,pierWidth/2,&pier1),S_OK);

   // Pier 2, ID 200, Station 2+00
   CComPtr<IPierLine> pier2;
   TRY_TEST(bridge->CreatePierLine(200,999,CComVariant(200.00),CComBSTR("NORMAL"),pierWidth,pierWidth/2,&pier2),S_OK);

   // Pier 3, ID 300, Station 3+00
   CComPtr<IPierLine> pier3;
   TRY_TEST(bridge->CreatePierLine(300,999,CComVariant(300.00),CComBSTR("NORMAL"),pierWidth,pierWidth/2,&pier3),S_OK);

   // Girder Spacing in span 1 (4 girders -> 3 spaces)
   CComPtr<IDblArray> span1Spacing;
   span1Spacing.CoCreateInstance(CLSID_DblArray);
   span1Spacing->Add(6.0);
   span1Spacing->Add(6.0);
   span1Spacing->Add(6.0);

   // Girder Spacing in span 2 (5 girders -> 4 spaces)
   CComPtr<IDblArray> span2Spacing;
   span2Spacing.CoCreateInstance(CLSID_DblArray);
   span2Spacing->Add(6.0);
   span2Spacing->Add(6.0);
   span2Spacing->Add(6.0);
   span2Spacing->Add(6.0);

   // Create girder layout lines for span 1
   CComPtr<IUniformSpacingLayoutLineFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_UniformSpacingLayoutLineFactory),S_OK);
   TRY_TEST(factory->put_AlignmentID(999),S_OK);
   TRY_TEST(factory->put_StartPierID(100),S_OK);
   TRY_TEST(factory->put_EndPierID(200),S_OK);
   TRY_TEST(factory->put_PierIDInc(100),S_OK);
   TRY_TEST(factory->put_StartSpacingOffset(-12.0),S_OK);
   TRY_TEST(factory->put_EndSpacingOffset(-12.0),S_OK);
   TRY_TEST(factory->put_StartSpacing(span1Spacing),S_OK);
   TRY_TEST(factory->put_EndSpacing(span1Spacing),S_OK);
   TRY_TEST(factory->put_LayoutLineID(100),S_OK);
   TRY_TEST(bridge->CreateLayoutLines(factory),S_OK); // create layout lines 100, 101, 102, 103

   // Create girder layout lines for span 2
   TRY_TEST(factory->put_StartPierID(200),S_OK);
   TRY_TEST(factory->put_EndPierID(300),S_OK);
   TRY_TEST(factory->put_StartSpacingOffset(-12.0),S_OK);
   TRY_TEST(factory->put_EndSpacingOffset(-12.0),S_OK);
   TRY_TEST(factory->put_StartSpacing(span2Spacing),S_OK);
   TRY_TEST(factory->put_EndSpacing(span2Spacing),S_OK);
   TRY_TEST(factory->put_LayoutLineID(200),S_OK);
   TRY_TEST(bridge->CreateLayoutLines(factory),S_OK); // create layout lines 200, 201, 202, 203, 204

   // Create girder lines in span 1
   CComPtr<ISimpleGirderLineFactory> glFactory;
   glFactory.CoCreateInstance(CLSID_SimpleGirderLineFactory);
   glFactory->put_GirderLineID(100); // girder line ID
   glFactory->put_GirderLineIDInc(1);
   glFactory->put_LeftLayoutLineID(100); // layout line used to layout this girder line
   glFactory->put_RightLayoutLineID(103); // layout line used to layout this girder line
   glFactory->put_LayoutLineIDInc(1); // layout line used to layout this girder line
   glFactory->put_Type(glChord); // layout as a chord
   glFactory->put_StartPierID(100); // layout between piers 100 and 300
   glFactory->put_EndPierID(200);
   glFactory->put_PierIDInc(100);
   glFactory->put_Continuous(VARIANT_FALSE);
   TRY_TEST(bridge->CreateGirderLines(glFactory),S_OK);

   // Create girder lines in span 2
   glFactory->put_GirderLineID(200); // girder line ID
   glFactory->put_GirderLineIDInc(1);
   glFactory->put_LeftLayoutLineID(200); // layout line used to layout this girder line
   glFactory->put_RightLayoutLineID(204); // layout line used to layout this girder line
   glFactory->put_LayoutLineIDInc(1); // layout line used to layout this girder line
   glFactory->put_Type(glChord); // layout as a chord
   glFactory->put_StartPierID(200); // layout between piers 100 and 300
   glFactory->put_EndPierID(300);
   glFactory->put_Continuous(VARIANT_FALSE);
   TRY_TEST(bridge->CreateGirderLines(glFactory),S_OK);

   // compute geometric parameters
   TRY_TEST(bridge->UpdateGeometry(),S_OK);

   CollectionIndexType nGirderLines;
   TRY_TEST(bridge->get_GirderLineCount(NULL),E_POINTER);
   TRY_TEST(bridge->get_GirderLineCount(&nGirderLines),S_OK);
   TRY_TEST(nGirderLines,9);
}

void CTestBridge::TestDiaphragmLayout()
{
   CComPtr<IBridgeGeometry> bridge;
   CreateBridge(&bridge);

   // Generate diaphragms in span 1
   CComPtr<IEqualSpaceDiaphragmLineFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_EqualSpaceDiaphragmLineFactory),S_OK);
   factory->put_AlignmentID(999);
   factory->put_StartStation(100); // pier 1 is at station 1+00
   factory->put_EndStation(200);   // pier 2 is at station 2+00
   factory->put_DiaphragmLineID(0);
   factory->put_DiaphragmLineIDInc(1);
   factory->put_LeftGirderLineID(500);
   factory->put_RightGirderLineID(504);
   factory->put_Divisor(4);
   factory->put_Staggered(VARIANT_TRUE);
   TRY_TEST(bridge->CreateDiaphragmLines(factory),S_OK);

   // compute geometric parameters
   TRY_TEST(bridge->UpdateGeometry(),S_OK);

   CollectionIndexType nDiaphragmLines;
   TRY_TEST(bridge->get_DiaphragmLineCount(NULL),E_POINTER);
   TRY_TEST(bridge->get_DiaphragmLineCount(&nDiaphragmLines),S_OK);
   TRY_TEST(nDiaphragmLines,3);

   for ( CollectionIndexType idx = 0; idx < nDiaphragmLines; idx++ )
   {
      CComPtr<IDiaphragmLine> diaphragmLine;
      bridge->FindDiaphragmLine( LineIDType(idx), &diaphragmLine );

      LineIDType ID;
      diaphragmLine->get_ID(&ID);
      TRY_TEST(ID,LineIDType(idx));

      for ( GirderIDType gdrID = 500; gdrID < 504; gdrID++ )
      {
         Float64 length;
         diaphragmLine->get_Length(gdrID,&length);
         TRY_TEST(IsEqual(length,5.0),true);

         CComPtr<IPoint2d> pntLeft, pntRight;
         diaphragmLine->get_Point(gdrID,etStart,&pntLeft);
         diaphragmLine->get_Point(gdrID,etEnd,  &pntRight);

         //Float64 x,y;
         //pntLeft->Location(&x,&y);
         //TRY_TEST(IsEqual(x,0.0),true);
         //TRY_TEST(IsEqual(y,0.0),true);

         //pntRight->Location(&x,&y);
         //TRY_TEST(IsEqual(x,0.0),true);
         //TRY_TEST(IsEqual(y,0.0),true);
      }
   }


   // Generate diaphragms in span 2
   CComPtr<ISingleDiaphragmLineFactory> sdlfactory;
   TRY_TEST(sdlfactory.CoCreateInstance(CLSID_SingleDiaphragmLineFactory),S_OK);
   sdlfactory->put_AlignmentID(999);
   sdlfactory->put_Station(250); // middle of span 2 (2+50)
   sdlfactory->put_Orientation(CComBSTR("45 L"));
   sdlfactory->put_DiaphragmLineID(4);
   sdlfactory->put_LeftGirderLineID(505);
   sdlfactory->put_RightGirderLineID(509);
   sdlfactory->put_Staggered(VARIANT_TRUE);
   TRY_TEST(bridge->CreateDiaphragmLines(sdlfactory),S_OK);

   // compute geometric parameters
   TRY_TEST(bridge->UpdateGeometry(),S_OK);
   TRY_TEST(bridge->get_DiaphragmLineCount(&nDiaphragmLines),S_OK);
   TRY_TEST(nDiaphragmLines,4);

   CComPtr<IDiaphragmLine> diaphragmLine;
   bridge->FindDiaphragmLine( 4, &diaphragmLine );

   for ( GirderIDType gdrID = 505; gdrID < 509; gdrID++ )
   {
      Float64 length;
      diaphragmLine->get_Length(gdrID,&length);
      TRY_TEST(IsEqual(length,5.0),true);

      CComPtr<IPoint2d> pntLeft, pntRight;
      diaphragmLine->get_Point(gdrID,etStart,&pntLeft);
      diaphragmLine->get_Point(gdrID,etEnd,  &pntRight);

      Float64 x,y;
      pntLeft->Location(&x,&y);
      //TRY_TEST(IsEqual(x,0.0),true);
      //TRY_TEST(IsEqual(y,0.0),true);

      pntRight->Location(&x,&y);
      //TRY_TEST(IsEqual(x,0.0),true);
      //TRY_TEST(IsEqual(y,0.0),true);
   }


   // Generate diaphragms with line through a point
   CComPtr<IThroughPointDiaphragmLineFactory> tpfactory;
   TRY_TEST(tpfactory.CoCreateInstance(CLSID_ThroughPointDiaphragmLineFactory),S_OK);
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance(CLSID_Point2d);
   pnt->Move(151.421,151.421); // pier 3 at station 3+00

   CComPtr<IDirection> dir;
   dir.CoCreateInstance(CLSID_Direction);
   dir->put_Value(0.0);

   tpfactory->put_Point(pnt);
   tpfactory->put_Direction(dir);

   tpfactory->put_DiaphragmLineID(5);
   tpfactory->put_LeftGirderLineID(505);
   tpfactory->put_RightGirderLineID(509);
   tpfactory->put_Staggered(VARIANT_TRUE);
   TRY_TEST(bridge->CreateDiaphragmLines(tpfactory),S_OK);

   // compute geometric parameters
   TRY_TEST(bridge->UpdateGeometry(),S_OK);
   TRY_TEST(bridge->get_DiaphragmLineCount(&nDiaphragmLines),S_OK);
   TRY_TEST(nDiaphragmLines,5);

   diaphragmLine.Release();
   bridge->FindDiaphragmLine( 5, &diaphragmLine );

   for ( GirderIDType gdrID = 505; gdrID < 509; gdrID++ )
   {
      Float64 length;
      diaphragmLine->get_Length(gdrID,&length);
      TRY_TEST(IsEqual(length,5.0),true);

      CComPtr<IPoint2d> pntLeft, pntRight;
      diaphragmLine->get_Point(gdrID,etStart,&pntLeft);
      diaphragmLine->get_Point(gdrID,etEnd,  &pntRight);

      Float64 x,y;
      pntLeft->Location(&x,&y);
      //TRY_TEST(IsEqual(x,0.0),true);
      //TRY_TEST(IsEqual(y,0.0),true);

      pntRight->Location(&x,&y);
      //TRY_TEST(IsEqual(x,0.0),true);
      //TRY_TEST(IsEqual(y,0.0),true);
   }
}

void CTestBridge::TestSlabLayout()
{
   CComPtr<IBridgeGeometry> bridge;
   CreateBridge(&bridge);

   // Create slab edge paths
   CComPtr<IAlignmentOffsetLayoutLineFactory> factory;
   factory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory);
   factory->put_AlignmentID(999);
   factory->put_LayoutLineID(1000); // left edge = 1000, right edge = 2000
   factory->put_LayoutLineIDInc(1000);
   factory->put_LayoutLineCount(2);
   factory->put_Offset(-12);
   factory->put_OffsetIncrement(24);
   bridge->CreateLayoutLines(factory);

   // create break lines
   factory->put_LayoutLineID(1001);
   factory->put_Offset(-10);
   factory->put_OffsetIncrement(20);
   bridge->CreateLayoutLines(factory);

   CComPtr<ISimpleDeckBoundaryFactory> deckBoundaryFactory;
   deckBoundaryFactory.CoCreateInstance(CLSID_SimpleDeckBoundaryFactory);
   deckBoundaryFactory->put_BackEdgeID(100); // use pier 1 (ID=100) for back edge transverse slab line
   deckBoundaryFactory->put_BackEdgeType(setPier);
   deckBoundaryFactory->put_ForwardEdgeID(300); // use pier 3 (ID=300) for forward edge transverse slab line
   deckBoundaryFactory->put_ForwardEdgeType(setPier);
   deckBoundaryFactory->put_LeftEdgeID(1000); // left edge of slab (layout line 1000)
   deckBoundaryFactory->put_RightEdgeID(2000); // right edge of slab (layout line 2000)

   // break slab at all four corners
   deckBoundaryFactory->put_BreakLeftEdge(etStart,VARIANT_TRUE);
   deckBoundaryFactory->put_BreakLeftEdge(etEnd,VARIANT_TRUE);
   deckBoundaryFactory->put_BreakRightEdge(etStart,VARIANT_TRUE);
   deckBoundaryFactory->put_BreakRightEdge(etEnd,VARIANT_TRUE);
   deckBoundaryFactory->put_LeftEdgeBreakID(1001);
   deckBoundaryFactory->put_RightEdgeBreakID(2001);
   
   bridge->CreateDeckBoundary(deckBoundaryFactory);

   TRY_TEST(bridge->UpdateGeometry(),S_OK);

   CComPtr<IDeckBoundary> deckBoundary;
   bridge->get_DeckBoundary(&deckBoundary);

   CComPtr<IPoint2dCollection> points;
   deckBoundary->get_Perimeter(10,&points);

   CollectionIndexType nPoints;
   points->get_Count(&nPoints);
   for ( CollectionIndexType idx = 0; idx < nPoints; idx++ )
   {
      CComPtr<IPoint2d> p;
      points->get_Item(idx,&p);

      Float64 x,y;
      p->Location(&x,&y);
      std::_tcout << x << ", " << y << std::endl;
   }
}