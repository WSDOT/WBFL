///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 2009  Washington State Department of Transportation
//                   Bridge and Structures Office
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

#include "StdAfx.h"
#include "TestSeg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void SetupSegment(ISegment* pseg)
{
   CComPtr<ISegmentCrossSection> pcs;
   TRY_TEST(pcs.CoCreateInstance( CLSID_SegmentCrossSection ), S_OK );

   TRY_TEST( pcs->put_EAForce(1.1), S_OK );
   TRY_TEST( pcs->put_EIForce(1.2), S_OK );
   TRY_TEST( pcs->put_EADefl(1.3), S_OK );
   TRY_TEST( pcs->put_EIDefl(1.4), S_OK );
   TRY_TEST( pcs->put_ThermalCoeff(1.5), S_OK );
   TRY_TEST( pcs->put_Depth(1.6), S_OK );

   CComPtr<IStressPoints> psps;
   TRY_TEST( pcs->get_StressPoints(&psps), S_OK );

   CComPtr<IStressPoint> pss1, pss2;
   TRY_TEST( pss1.CoCreateInstance( CLSID_StressPoint ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( CLSID_StressPoint ) , S_OK );

   TRY_TEST( pss1->put_Sm(11.2), S_OK );
   TRY_TEST( pss1->put_Sa(11.141), S_OK );

   TRY_TEST( psps->Add(pss1), S_OK);
   CollectionIndexType cnt;
   TRY_TEST( psps->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);

   TRY_TEST( psps->Add(pss2), S_OK);
   TRY_TEST( pss2->put_Sm(211.2), S_OK );
   TRY_TEST( pss2->put_Sa(211.141), S_OK );

   TRY_TEST( pseg->putref_SegmentCrossSection(pcs), S_OK);
}