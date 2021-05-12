///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// RoundColumnTest.cpp: implementation of the CRoundColumnTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoundColumnTest.h"
#include "GeneralTests.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoundColumnTest::CRoundColumnTest()
{

}

CRoundColumnTest::~CRoundColumnTest()
{

}

struct PM { Float64 P; Float64 M; };

void CRoundColumnTest::Test()
{
   CComPtr<IRoundColumn> column;
   TRY_TEST(column.CoCreateInstance(CLSID_RoundColumn),S_OK);

	column->put_Diameter(72.0);
	column->put_Cover(3.0);
	column->put_fc(4);
	column->put_fy(60);
	column->put_Es(29000);
	column->put_As(10);

	CComPtr<IPoint2dCollection> points;
	column->ComputeInteraction(37,&points);

	PM results[] = {  
      {287.285, 10493.2},
      {-259.953, 27246.5},
      {-846.435, 43248.4},
      {-1492.64, 58743.9},
      {-2259.45, 74511.4},
      {-3014.82, 87409.2},
      {-3844.13, 98740.1},
      {-4590.48, 106425},
      {-5520.7, 112896},
      {-6330.61, 115562},
      {-7160.62, 115308},
      {-7983.31, 112624},
      {-8930.35, 106718},
      {-9691.08, 99502.9},
      {-10539.9, 88866},
      {-11314.5, 76585.3},
      {-12003.7, 63477.2},
      {-12598.9, 50389.1},
      {-13233.8, 34420.9},
      {-13696.7, 21339},
      {-14093.4, 8930.83},
      {-14249.4, 3758.74},
      {-14263.2, 3476.5},
      {-14275.7, 3216.66},
      {-14287.1, 2976.71},
      {-14297.5, 2754.51},
      {-14307, 2548.22},
      {-14315.7, 2356.3},
      {-14323.7, 2177.36},
      {-14331, 2010.26},
      {-14337.8, 1853.95},
      {-14344.1, 1707.57},
      {-14349.8, 1570.3},
      {-14355.2, 1441.48},
      {-14360.1, 1320.47},
      {-14364.7, 1206.74},
      {-14369, 1099.81}
   };

   CollectionIndexType count;
	points->get_Count(&count);
	TRY_TEST( count, 37);

	for ( CollectionIndexType i = 0; i < count; i++ )
	{
		CComPtr<IPoint2d> point;
		points->get_Item(i,&point);
		Float64 P, M;
		point->get_X(&M);
		point->get_Y(&P);

		TRY_TEST(IsEqual( results[i].P, P, 1.0), true );
		TRY_TEST(IsEqual( results[i].M, M, 1.0), true );
	}


   CComQIPtr<ISupportErrorInfo> eInfo(column);
   TRY_TEST( eInfo != nullptr, true);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_IRoundColumn),       S_OK);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo),   S_FALSE);
}
