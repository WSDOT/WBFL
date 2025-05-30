///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TestBeamShapeFactory.cpp: implementation of the CTestBeamShapeFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestBeamShapeFactory.h"


enum PropertyType
{ Area, Ixx, Iyy, Ixy, Height, Yt, Yb };

static Float64 gs_Properties[][7]
{
   //  Area,       Ixx,       Iyy,   Ixy,  Height,      Yt,     Yb
      { 276,   	22744.1,	   3352.3,	0, 	28,	   15.411,	12.589 }, // Type I
      { 369,   	50978.7,	   5332.5,	0, 	36,	   20.171,	15.829 }, // Type II
      { 559.5,	   125390.3,   12216.6,	0, 	45,	   24.727,	20.273 }, // Type III
      { 789,	   260740.6,   24373.5,	0, 	54,	   29.266,	24.734 }, // Type IV
      { 1013,	   521162.6,   61235.2,	0, 	63,	   31.043,	31.957 }, // Type V
      { 1085,	   733320.3,   61619.2,	0, 	72,	   35.619,	36.381 }, // Type VI
      { 659,	   268050.6,   37310.3,	0, 	54,	   26.366,	27.634 }, // BT54
      { 713,	   392515.8,   37472.3,	0, 	63,	   30.882,	32.118 }, // BT63
      { 767,	   545857.2,   37634.3,	0, 	72,	   35.396,	36.604 }, // BT72

      { 373.25,	76091.6,	   5407.8,	0,    42,	   23.057,	18.943}, // W42G
      { 525.5,	   164957.5,   13362.8, 0,    50,	   27.19,	22.81},	// W50G
      { 603.5,	   264609.2,   17065.3,	0,    58,	   29.997,	28.003}, //W58G
      { 746.687,	546110.5,   34759.4,	0,    73.5,	   35.423,	38.077 }, //W74G
      { 690.781,	124771.6,   71290.8,	0,    36,	   18.464,	17.536 }, //WF36G
      { 727.531,	183642.4,   71405.7, 0,	   42,	   21.64,	20.36 }, //WF42G
      { 776.531,	282559.4,   71558.9, 0,	   50,	   25.849,	24.151 }, //WF50G
      { 825.531,	406265.7,   71712.1, 0,	   58,	   30.033,	27.967 }, //WF58G
      { 874.531,	556339.2,   71865.3, 0,	   66,	   34.196,	31.804 }, //WF66G
      { 923.531,	734356,	   72018.4, 0,	   74,	   38.343,	35.657 }, //WF74G
      { 976.359,	959392.9,   72183.6, 0,	   82.625,	42.796,	39.829 }, //WF83G
      { 1049.094,	1328994.7,  72411,   0,	   94.5, 	48.905,	45.595 }, //WF95G
      { 1082.781,	1524912.4,  72516.3, 0,	   100,	   51.726,	48.274 }, //WF100G

      { 585.313,	52771.5,	   40559.5,	0,	28,	15.02,	12.98 }, //Tx28
      { 627.312,	88355.5,	   40731,	0,	34,	18.489,	15.511 }, //Tx34
      { 669.313,	134989.9,	40902.5,	0,	40,	21.899,	18.101 }, //Tx40
      { 761.312,	198089.4,	46478.2,	0,	46,	25.896,	20.104 }, //Tx46
      { 817.313,	299739.7,	46706.8,	0,	54,	30.492,	23.508 }, //Tx54
      { 910.063,	463072,  	57350.6,	0,	62,	33.723,	28.277 }, //Tx62
      { 966.063,	628746.8,	57579.3,	0,	70,	38.085,	31.915 }, //Tx70


      { 1038.823,	292422.8,	493926.2,	0,	54,	33.03,	20.97 }, //U54G4
      { 1110.823,	314382,	   788289.2,	0,	54,	34.195,	19.805 }, //U54G5
      { 1254.823,	341728.5,	1189384.3,	0,	54,	35.836,	18.164 }, //U54G6
      { 1208.528,	516676.6,	637750.8,	0,	66,	39.549,	26.451 }, //U66G4
      { 1280.528,	554261.7,	997353.8,	0,	66,	40.868,	25.132 }, //U66G5
      { 1424.528,	605412.1,	1475907.9,	0,	66,	42.852,	23.148 }, //U66G6
      { 1378.234,	827453.2,	798968.7,	0,	78,	45.941,	32.059 }, //U78G4
      { 1450.234,	885450.7,	1227302.8,	0,	78,	47.383,	30.617 }, //U78G5
      { 1594.234,	969346.9,	1786806.8,	0,	78,	49.652,	28.348 }, //U78G6
      { 1207.675,	483298.3,	639795,  	0,	60,	33.968,	26.032 }, //UF60G4
      { 1279.675,	519560.7,	999184.3,	0,	60,	35.263,	24.737 }, //UF60G5
      { 1423.675,	568717.3,	1477463.3,	0,	60,	37.209,	22.791 }, //UF60G6
      { 1377.381,	787604.6,	800958,  	0,	72,	40.311,	31.689 }, //UF72G4
      { 1449.381,	844135.5,	1229061, 	0,	72,	41.737,	30.263 }, //UF72G5
      { 1593.381,	925720,  	1788272.3,	0,	72,	43.975,	28.025 }, //UF72G6
      { 1547.087,	1190828.2,	980506.7,	0,	84,	46.58,	37.42 }, //UF84G4
      { 1619.087,	1272553, 	1480814.4,	0,	84,	48.11,	35.89 }, //UF84G5
      { 1763.087,	1395938.9,	2124449.3,	0,	84,	50.592,	33.408 }, //UF84G6

      {977.002,	183050.2,	670768.9,	0,	40,	23.65,	16.35}, //	U40
      {1121.084,	403458,	910531.7,	0,	54,	31.543,	22.457 },	// U54

};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestBeamShapeFactory::CTestBeamShapeFactory()
{

}

CTestBeamShapeFactory::~CTestBeamShapeFactory()
{

}

void CTestBeamShapeFactory::Test()
{
   TestIBeamShapeFactory();
   TestISupportErrorInfo();
}

void CTestBeamShapeFactory::TestIBeamShapeFactory()
{
   CComPtr<IBeamShapeFactory> factory;
   TRY_TEST(factory.CoCreateInstance(CLSID_BeamShapeFactory), S_OK );

   Test(factory, AASHTO_TypeI);
   Test(factory, AASHTO_TypeII);
   Test(factory, AASHTO_TypeIII);
   Test(factory, AASHTO_TypeIV);
   Test(factory, AASHTO_TypeV);
   Test(factory, AASHTO_TypeVI);
   Test(factory, AASHTO_BT54);
   Test(factory, AASHTO_BT63);
   Test(factory, AASHTO_BT72);

   Test(factory, WSDOT_W42G);
   Test(factory, WSDOT_W50G);
   Test(factory, WSDOT_W58G);
   Test(factory, WSDOT_W74G);
   Test(factory, WSDOT_WF36G);
   Test(factory, WSDOT_WF42G);
   Test(factory, WSDOT_WF50G);
   Test(factory, WSDOT_WF58G);
   Test(factory, WSDOT_WF66G);
   Test(factory, WSDOT_WF74G);
   Test(factory, WSDOT_WF83G);
   Test(factory, WSDOT_WF95G);
   Test(factory, WSDOT_WF100G);

   Test(factory, TxDOT_Tx28);
   Test(factory, TxDOT_Tx34);
   Test(factory, TxDOT_Tx40);
   Test(factory, TxDOT_Tx46);
   Test(factory, TxDOT_Tx54);
   Test(factory, TxDOT_Tx62);
   Test(factory, TxDOT_Tx70);

   Test(factory, WSDOT_U54G4);
   Test(factory, WSDOT_U54G5);
   Test(factory, WSDOT_U54G6);
   Test(factory, WSDOT_U66G4);
   Test(factory, WSDOT_U66G5);
   Test(factory, WSDOT_U66G6);
   Test(factory, WSDOT_U78G4);
   Test(factory, WSDOT_U78G5);
   Test(factory, WSDOT_U78G6);
   Test(factory, WSDOT_UF60G4);
   Test(factory, WSDOT_UF60G5);
   Test(factory, WSDOT_UF60G6);
   Test(factory, WSDOT_UF72G4);
   Test(factory, WSDOT_UF72G5);
   Test(factory, WSDOT_UF72G6);
   Test(factory, WSDOT_UF84G4);
   Test(factory, WSDOT_UF84G5);
   Test(factory, WSDOT_UF84G6);
   Test(factory, TxDOT_U40);
   Test(factory, TxDOT_U54);
}

void CTestBeamShapeFactory::Test(IBeamShapeFactory* pFactory, BeamShapeType type)
{
   CComPtr<IShape> shape;
   TRY_TEST(pFactory->CreateShape(type, &shape),S_OK);
   VerifyShape(type, shape);
}

void CTestBeamShapeFactory::VerifyShape(BeamShapeType type, IShape* pShape)
{
   CComPtr<IShapeProperties> props;
   pShape->get_ShapeProperties(&props);

   Float64 a, ixx, iyy, ixy, h, yt, yb;
   props->get_Area(&a);
   props->get_Ixx(&ixx);
   props->get_Iyy(&iyy);
   props->get_Ixy(&ixy);
   props->get_Ytop(&yt);
   props->get_Ybottom(&yb);

   CComPtr<IRect2d> box;
   pShape->get_BoundingBox(&box);
   box->get_Height(&h);

   TRY_TEST(IsEqual(a, gs_Properties[type][Area],0.1),true);
   TRY_TEST(IsEqual(ixx, gs_Properties[type][Ixx], 0.1), true);
   TRY_TEST(IsEqual(iyy, gs_Properties[type][Iyy], 0.1), true);
   TRY_TEST(IsEqual(ixy, gs_Properties[type][Ixy], 0.1), true);
   TRY_TEST(IsEqual(h, gs_Properties[type][Height], 0.1), true);
   TRY_TEST(IsEqual(yt, gs_Properties[type][Yt], 0.3), true);
   TRY_TEST(IsEqual(yb, gs_Properties[type][Yb], 0.3), true);
}

void CTestBeamShapeFactory::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_BeamShapeFactory ), S_OK );
   TRY_TEST( eInfo != nullptr, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IBeamShapeFactory ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
