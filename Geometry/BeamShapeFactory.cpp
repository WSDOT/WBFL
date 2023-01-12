///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// BeamShapeFactory.cpp : Implementation of CBeamShapeFactory
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "BeamShapeFactory.h"

#include "PrecastBeam.h"
#include "UBeam.h"
#include "UBeam2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace IBeam
{
   // this enum needs to be in a namespace so we can use dimensions D1, D2, etc with
   // other beam types as well
   enum IBeamDimensions { C1, D1, D2, D3, D4, D5, D6, D7, T1, T2, W1, W2, W3, W4 };
}

static Float64 gs_IBeamDimensions[][14] = 
{
   { 0,4,3,0,5,5,0,11,6,6,3,0,5,0 }, // AASHTO_TypeI
   { 0,6,3,0,6,6,0,15,6,6,3,0,6,0 }, // AASHTO_TypeII
   { 0,7,4.5,0,7,7.5,0,19,7,7,4.5,0,7.5,0 }, // AASHTO_TypeIII
   { 0,8,6,0,8,9,0,23,8,8,6,0,9,0 }, // AASHTO_TypeIV
   { 0,5,3,4,8,10,0,33,8,8,13,4,10,0 }, // AASHTO_TypeV
   { 0,5,3,4,8,10,0,42,8,8,13,4,10,0 }, // AASHTO_TypeVI
   { 0,3.5,2,2,6,4.5,0,36,6,6,16,2,10,0 }, // AASHTO_BT54
   { 0,3.5,2,2,6,4.5,0,45,6,6,16,2,10,0 }, // AASHTO_BT63
   { 0,3.5,2,2,6,4.5,0,54,6,6,16,2,10,0 }, // AASHTO_BT72
   { 1,3.5,1.5,0,5,2,0,30,6,6,4.5,0,7,0 },// WSDOT_W42G
   { 1,5,2,0,6,3,0,34,6,6,7,0,9.5,0 },// WSDOT_W50G
   { 1,5,2,0,6,3,0,42,6,6,9.5,0,9.5,0 },// WSDOT_W58G
   { 1,2.875,2.625,2,6,3,0,57,6,6,16.5,2,9.5,0 },// WSDOT_W74G
   { 1,3,3,3,5.125,4.5,3,14.375,6.125,6.125,18.4375,3,13.125,3 },// WSDOT_WF36G
   { 1,3,3,3,5.125,4.5,3,20.375,6.125,6.125,18.4375,3,13.125,3 },// WSDOT_WF42G
   { 1,3,3,3,5.125,4.5,3,28.375,6.125,6.125,18.4375,3,13.125,3 },// WSDOT_WF50G
   { 1,3,3,3,5.125,4.5,3,36.375,6.125,6.125,18.4375,3,13.125,3 },// WSDOT_WF58G
   { 1,3,3,3,5.125,4.5,3,44.375,6.125,6.125,18.4375,3,13.125,3 },// WSDOT_WF66G
   { 1,3,3,3,5.125,4.5,3,52.375,6.125,6.125,18.4375,3,13.125,3 },// WSDOT_WF74G
   { 1,3,3,3,5.125,4.5,3,61.000,6.125,6.125,18.4375,3,13.125,3 },// WSDOT_WF83G
   { 1,3,3,3,5.125,4.5,3,72.875,6.125,6.125,18.4375,3,13.125,3 },// WSDOT_WF95G
   { 1,3,3,3,5.125,4.5,3,78.375,6.125,6.125,18.4375,3,13.125,3 },// WSDOT_WF100G
   { 0.75, 3.5, 2, 2, 6.75, 4.75, 3, 6, 7, 7, 12.5, 2, 9.5, 3 },// TxDOT_Tx28
   { 0.75, 3.5, 2, 2, 6.75, 4.75, 3, 12, 7, 7, 12.5, 2, 9.5, 3 },// TxDOT_Tx34
   { 0.75, 3.5, 2, 2, 6.75, 4.75, 3, 18, 7, 7, 12.5, 2, 9.5, 3 }, //TxDOT_Tx40
   { 0.75, 3.5, 2, 2, 8.75, 4.75, 3, 22, 7, 7, 12.5, 2, 9.5, 3 }, //TxDOT_Tx46
   { 0.75, 3.5, 2, 2, 8.75, 4.75, 3, 30, 7, 7, 12.5, 2, 9.5, 3 }, //TxDOT_Tx54
   { 0.75, 3.5, 2.5, 2, 8.75, 4.75, 3, 37.5, 7, 7, 15.5, 2, 9.5, 3 }, //TxDOT_Tx62
   { 0.75, 3.5, 2.5, 2, 8.75, 4.75, 3, 45.5, 7, 7, 15.5, 2, 9.5, 3 },//TxDOT_Tx70
};

namespace _UBeam
{
   // this enum needs to be in a namespace so we can use dimensions D1, D2, etc with
   // other beam types as well
   enum Dimensions { D1, D2, D3, D4, D5, D6, D7, T, W1, W2, W3, W4, W5 };
}

static Float64 gs_UBeamDimensions[][13] =
{
   { 54, 6, 6, 0, 0, 0, 0, 7, 48, 63.42857143, 12, 0, 0 }, // WSDOT_U54G4
   { 54, 6, 6, 0, 0, 0, 0, 7, 60, 75.42857143, 12, 0, 0 }, // WSDOT_U54G5
   { 54, 6, 6, 0, 0, 0, 0, 7, 72, 87.42857143, 24, 0, 0 }, // WSDOT_U54G6
   { 66, 6, 6, 0, 0, 0, 0, 7, 48, 66.85714286, 12, 0, 0 }, // WSDOT_U66G4
   { 66, 6, 6, 0, 0, 0, 0, 7, 60, 78.85714286, 12, 0, 0 }, // WSDOT_U66G5
   { 66, 6, 6, 0, 0, 0, 0, 7, 72, 90.85714286, 24, 0, 0 }, // WSDOT_U66G6
   { 78, 6, 6, 0, 0, 0, 0, 7, 48, 70.28571429, 12, 0, 0 }, // WSDOT_U78G4
   { 78, 6, 6, 0, 0, 0, 0, 7, 60, 82.28571429, 12, 0, 0 }, // WSDOT_U78G5
   { 78, 6, 6, 0, 0, 0, 0, 7, 72, 94.28571429, 24, 0, 0 }, // WSDOT_U78G6
   { 60, 6, 6, 4.5, 1.5, 4.5, 1.5, 7, 48, 73.428571, 12, 3, 5 }, // WSDOT_UF60G4
   { 60, 6, 6, 4.5, 1.5, 4.5, 1.5, 7, 60, 85.428571, 12, 3, 5 }, // WSDOT_UF60G5
   { 60, 6, 6, 4.5, 1.5, 4.5, 1.5, 7, 72, 97.428571, 24, 3, 5 }, // WSDOT_UF60G6
   { 72, 6, 6, 4.5, 1.5, 4.5, 1.5, 7, 48, 76.857143, 12, 3, 5 }, // WSDOT_UF72G4
   { 72, 6, 6, 4.5, 1.5, 4.5, 1.5, 7, 60, 88.857143, 12, 3, 5 }, // WSDOT_UF72G5
   { 72, 6, 6, 4.5, 1.5, 4.5, 1.5, 7, 72, 100.85714, 24, 3, 5 }, // WSDOT_UF72G6
   { 84, 6, 6, 4.5, 1.5, 4.5, 1.5, 7, 48, 80.285714, 12, 3, 5 }, // WSDOT_UF84G4
   { 84, 6, 6, 4.5, 1.5, 4.5, 1.5, 7, 60, 92.285714, 12, 3, 5 }, // WSDOT_UF84G5
   { 84, 6, 6, 4.5, 1.5, 4.5, 1.5, 7, 72, 104.285714, 24, 3, 5 }, // WSDOT_UF84G6
};

namespace _UBeam2
{
   // this enum needs to be in a namespace so we can use dimensions D1, D2, etc with
   // other beam types as well
   enum Dimensions { C1, D1, D2, D3, D4, D5, D6, W1, W2, W3, W4, W5, W6, W7 };
}

static Float64 gs_UBeam2Dimensions[][14] =
{
   { 0.75, 40, 8.25, 3, 0.875, 5.875, 21.625, 55, 89, 3, 0.375, 8.25, 15.75, 1.75 }, //TxDOT_U40
   { 0.75, 54, 8.25, 3, 0.875, 5.875, 21.625, 55, 96, 3, 0.375, 8.25, 15.75, 1.75 }, // TxDOT_U54
};

/////////////////////////////////////////////////////////////////////////////
// CBeamShapeFactory

STDMETHODIMP CBeamShapeFactory::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBeamShapeFactory,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CBeamShapeFactory::CreateShape(BeamShapeType type,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   HRESULT hr = S_OK;

   if ((int)AASHTO_TypeI <= (int)type && (int)type <= (int)TxDOT_Tx70)
   {
      CComObject<CPrecastBeam>* pBeam;
      CComObject<CPrecastBeam>::CreateInstance(&pBeam);

      int i = (int)type - (int)AASHTO_TypeI;
      ATLASSERT(0 <= i);

      using namespace IBeam; // this is so we don't have to use the name space below (eg IBeam::C1, IBeam::D2...)

      pBeam->put_C1(gs_IBeamDimensions[i][C1]);
      pBeam->put_D1(gs_IBeamDimensions[i][D1]);
      pBeam->put_D2(gs_IBeamDimensions[i][D2]);
      pBeam->put_D3(gs_IBeamDimensions[i][D3]);
      pBeam->put_D4(gs_IBeamDimensions[i][D4]);
      pBeam->put_D5(gs_IBeamDimensions[i][D5]);
      pBeam->put_D6(gs_IBeamDimensions[i][D6]);
      pBeam->put_D7(gs_IBeamDimensions[i][D7]);
      pBeam->put_T1(gs_IBeamDimensions[i][T1]);
      pBeam->put_T2(gs_IBeamDimensions[i][T2]);
      pBeam->put_W1(gs_IBeamDimensions[i][W1]);
      pBeam->put_W2(gs_IBeamDimensions[i][W2]);
      pBeam->put_W3(gs_IBeamDimensions[i][W3]);
      pBeam->put_W4(gs_IBeamDimensions[i][W4]);

      pBeam->QueryInterface(ppShape);
   }
   else if ((int)WSDOT_U54G4 <= (int)type && (int)type <= (int)WSDOT_UF84G6)
   {
      CComObject<CUBeam>* pBeam;
      CComObject<CUBeam>::CreateInstance(&pBeam);

      int i = (int)type - (int)WSDOT_U54G4;
      ATLASSERT(0 <= i);

      using namespace _UBeam; // this is so we don't have to use the name space below (eg _UBeam::D1, _UBeam::D2...)

      pBeam->put_D1(gs_UBeamDimensions[i][D1]);
      pBeam->put_D2(gs_UBeamDimensions[i][D2]);
      pBeam->put_D3(gs_UBeamDimensions[i][D3]);
      pBeam->put_D4(gs_UBeamDimensions[i][D4]);
      pBeam->put_D5(gs_UBeamDimensions[i][D5]);
      pBeam->put_D6(gs_UBeamDimensions[i][D6]);
      pBeam->put_D7(gs_UBeamDimensions[i][D7]);
      pBeam->put_T(gs_UBeamDimensions[i][T]);
      pBeam->put_W1(gs_UBeamDimensions[i][W1]);
      pBeam->put_W2(gs_UBeamDimensions[i][W2]);
      pBeam->put_W3(gs_UBeamDimensions[i][W3]);
      pBeam->put_W4(gs_UBeamDimensions[i][W4]);
      pBeam->put_W5(gs_UBeamDimensions[i][W5]);

      pBeam->QueryInterface(ppShape);
   }
   else if ((int)TxDOT_U40 <= (int)type && (int)type <= (int)TxDOT_U54)
   {
      CComObject<CUBeam2>* pBeam;
      CComObject<CUBeam2>::CreateInstance(&pBeam);

      int i = (int)type - (int)TxDOT_U40;
      ATLASSERT(0 <= i);

      using namespace _UBeam2; // this is so we don't have to use the name space below (eg _UBeam::D1, _UBeam::D2...)

      pBeam->put_C1(gs_UBeam2Dimensions[i][C1]);
      pBeam->put_D1(gs_UBeam2Dimensions[i][D1]);
      pBeam->put_D2(gs_UBeam2Dimensions[i][D2]);
      pBeam->put_D3(gs_UBeam2Dimensions[i][D3]);
      pBeam->put_D4(gs_UBeam2Dimensions[i][D4]);
      pBeam->put_D5(gs_UBeam2Dimensions[i][D5]);
      pBeam->put_D6(gs_UBeam2Dimensions[i][D6]);
      pBeam->put_W1(gs_UBeam2Dimensions[i][W1]);
      pBeam->put_W2(gs_UBeam2Dimensions[i][W2]);
      pBeam->put_W3(gs_UBeam2Dimensions[i][W3]);
      pBeam->put_W4(gs_UBeam2Dimensions[i][W4]);
      pBeam->put_W5(gs_UBeam2Dimensions[i][W5]);
      pBeam->put_W6(gs_UBeam2Dimensions[i][W6]);
      pBeam->put_W7(gs_UBeam2Dimensions[i][W7]);

      pBeam->QueryInterface(ppShape);
   }
   else
   {
      return E_FAIL;
   }

   return hr;
}
