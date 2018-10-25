///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2012  Washington State Department of Transportation
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

// TestDistributionFactor.cpp: implementation of the CTestDistributionFactor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDistributionFactor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define TEST_FIRED() TRY_TEST(pMe->m_Fired, true); pMe->m_Fired=false;

CTestDistributionFactor::CTestDistributionFactor()
{
   // set our triggers
   m_Fired = false;
}

CTestDistributionFactor::~CTestDistributionFactor()
{
}

HRESULT CTestDistributionFactor::OnDistributionFactorChanged(/*[in]*/IDistributionFactor* DistributionFactor)
{
   m_Fired = true;
   return S_OK;
}

void CTestDistributionFactor::Test()
{
   TestDfCollection();

   TestDfOnly();
}

void CTestDistributionFactor::TestDfCollection()
{
   CComPtr<IDistributionFactorSegment> pss1, pss2,pss3,pss4, pssf2, pssf6;

   TRY_TEST( pss1.CoCreateInstance( CLSID_DistributionFactorSegment ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( CLSID_DistributionFactorSegment ) , S_OK );
   TRY_TEST( pss3.CoCreateInstance( CLSID_DistributionFactorSegment ) , S_OK );
   TRY_TEST( pss4.CoCreateInstance( CLSID_DistributionFactorSegment ) , S_OK );
   TRY_TEST( pssf2.CoCreateInstance( CLSID_DistributionFactorSegment ) , S_OK );
   TRY_TEST( pssf6.CoCreateInstance( CLSID_DistributionFactorSegment ) , S_OK );

   TRY_TEST( pss1->put_Length(8.2), S_OK );
   TRY_TEST( pss2->put_Length(4.1), S_OK );
   TRY_TEST( pss3->put_Length(5.9), S_OK );
   TRY_TEST( pss4->put_Length(12.3), S_OK );
   TRY_TEST( pssf2->put_Length(-0.5), S_OK );
   TRY_TEST( pssf6->put_Length(-1.0/6.0), S_OK );
   TRY_TEST( pssf6->put_Length(-1.1), E_INVALIDARG );

   CComPtr<IDistributionFactors> pss_ts, pss_jr, pss_tl, pss_o1, pss_fr;
   TRY_TEST( pss_ts.CoCreateInstance( CLSID_DistributionFactors ) , S_OK );
   TRY_TEST( pss_jr.CoCreateInstance( CLSID_DistributionFactors ) , S_OK );
   TRY_TEST( pss_tl.CoCreateInstance( CLSID_DistributionFactors ) , S_OK );
   TRY_TEST( pss_o1.CoCreateInstance( CLSID_DistributionFactors ) , S_OK );
   TRY_TEST( pss_fr.CoCreateInstance( CLSID_DistributionFactors ) , S_OK );

   // create some stages with different segment combinations
   TRY_TEST( pss_ts->Add(pss2), S_OK); // Too Short
   TRY_TEST( pss_ts->Add(pss3), S_OK);
   TRY_TEST( pss_jr->Add(pss1), S_OK); // just right
   TRY_TEST( pss_jr->Add(pss2), S_OK);
   TRY_TEST( pss_tl->Add(pss1), S_OK); // too long
   TRY_TEST( pss_tl->Add(pss2), S_OK);
   TRY_TEST( pss_tl->Add(pss3), S_OK);
   TRY_TEST( pss_o1->Add(pss4), S_OK);  // only one
   TRY_TEST( pss_fr->Add(pssf2), S_OK); // fractional
   TRY_TEST( pss_fr->Add(pssf6), S_OK);
   TRY_TEST( pss_fr->Add(pss2), S_OK);

   CollectionIndexType cnt;
   TRY_TEST( pss_ts->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 2);
   TRY_TEST( pss_tl->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 3);
   TRY_TEST( pss_o1->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST( pss_fr->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 3);

   Float64 d;
   TRY_TEST( pss_ts->get_Length(12.3, &d), S_OK);
   TRY_TEST( d, 10.0);
   TRY_TEST( pss_jr->get_Length(12.3, &d), S_OK);
   TRY_TEST( IsEqual(d, 12.3), true);
   TRY_TEST( pss_tl->get_Length(12.3, &d), S_OK);
   TRY_TEST( d, 18.2);
   TRY_TEST( pss_o1->get_Length(12.3, &d), S_OK);
   TRY_TEST( d, 12.3);
   TRY_TEST( pss_fr->get_Length(12.3, &d), S_OK);
   TRY_TEST( IsEqual(d,12.3), true);

   // copy to
   TRY_TEST( pss_tl->CopyTo(0, 3), S_OK);
   TRY_TEST( pss_tl->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 4);
   TRY_TEST( pss_tl->get_Length(12.3, &d), S_OK);
   TRY_TEST( d, 26.4);
   TRY_TEST( pss_tl->CopyTo(-1, 2), E_INVALIDARG);
   TRY_TEST( pss_tl->CopyTo( 5, 2), E_INVALIDARG);
   TRY_TEST( pss_tl->CopyTo( 1,-1), E_INVALIDARG);
   TRY_TEST( pss_tl->CopyTo( 1, 5), E_INVALIDARG);

   // reverse
   CComPtr<IDistributionFactorSegment> ps1, ps2;
   TRY_TEST( pss_tl->get_Item( 1, &ps1), S_OK);
   TRY_TEST( ps1->get_Length(&d), S_OK);
   TRY_TEST( d, 4.1);
   TRY_TEST( pss_tl->Reverse(), S_OK);
   TRY_TEST( pss_tl->get_Length(12.3, &d), S_OK);
   TRY_TEST( d, 26.4);
   TRY_TEST( pss_tl->get_Item( 1,&ps2), S_OK);
   TRY_TEST( ps2->get_Length(&d), S_OK);
   TRY_TEST( d, 5.9);
   TRY_TEST( ps2->put_Length(5.0), S_OK);
   TRY_TEST( ps2->get_Length(&d), S_OK);
   TRY_TEST( d, 5.0);
   TRY_TEST( pss_tl->get_Length(12.3, &d), S_OK);
   TRY_TEST( IsEqual(d, 25.5), true);

   TRY_TEST( pss_tl->Reverse(), S_OK);

   // move to
   TRY_TEST( pss_tl->MoveTo(1, 3), S_OK);
   CComPtr<IDistributionFactorSegment> ps3;
   TRY_TEST( pss_tl->get_Item( 3, &ps3), S_OK);
   TRY_TEST( ps3->get_Length(&d), S_OK);
   TRY_TEST( d, 4.1);
   TRY_TEST( pss_tl->get_Length(12.3, &d), S_OK);
   TRY_TEST( IsEqual(d, 25.5), true);
   TRY_TEST( pss_tl->MoveTo(-1, 2), E_INVALIDARG);
   TRY_TEST( pss_tl->MoveTo( 4, 2), E_INVALIDARG);
   TRY_TEST( pss_tl->MoveTo( 1,-1), E_INVALIDARG);
   TRY_TEST( pss_tl->MoveTo( 1, 4), E_INVALIDARG);

   CComPtr<IDistributionFactorSegment> ibog;
   TRY_TEST( pss_tl->get_Item(4,&ibog), E_INVALIDARG);
   ibog.Release();
   TRY_TEST( pss_tl->get_Item(-1,&ibog), E_INVALIDARG);
   TRY_TEST( ibog, 0);

   // remove & segment clone
   TRY_TEST( pss_tl->Remove(3), S_OK);
   TRY_TEST( pss_tl->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 3);
   TRY_TEST( pss_tl->get_Length(12.3, &d), S_OK);
   TRY_TEST( IsEqual(d, 21.4), true);
   CComPtr<IDistributionFactorSegment> ps4;
   TRY_TEST( ps3->Clone(&ps4), S_OK);
   TRY_TEST( ps4->get_Length(&d), S_OK);
   TRY_TEST( d, 4.1);
   TRY_TEST( pss_tl->Remove(-1), E_INVALIDARG);
   TRY_TEST( pss_tl->Remove(3), E_INVALIDARG);
   TRY_TEST( pss_tl->CopyTo(1, 3), S_OK);
   TRY_TEST( pss_tl->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 4);
   TRY_TEST( pss_tl->Remove(3), S_OK); // remove last
   TRY_TEST( pss_tl->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 3);

   // insert
   TRY_TEST( pss_tl->Insert(3, ps4), S_OK);
   TRY_TEST( pss_tl->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 4);
   TRY_TEST( pss_tl->get_Length(12.3, &d), S_OK);
   TRY_TEST( IsEqual(d, 25.5), true);
   TRY_TEST( pss_tl->Insert(-1, ps4), E_INVALIDARG);
   TRY_TEST( pss_tl->Insert( 5, ps4), E_INVALIDARG);

   // put
   TRY_TEST( pss_o1->putref_Item( 0, ps4), S_OK);
   TRY_TEST( pss_o1->get_Count( &cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST( pss_o1->get_Length(12.3, &d), S_OK);
   TRY_TEST( IsEqual(d, 4.1), true);
   TRY_TEST( ps4->put_Length(12.3), S_OK );
   TRY_TEST( pss_o1->putref_Item(-1, ps4), E_INVALIDARG);
   TRY_TEST( pss_o1->putref_Item( 1, ps4), E_INVALIDARG);

   // collections stuff
   // IEnum
   CComPtr<IEnumDistributionFactorSegment> penum;
   pss_tl->get__EnumElements(&penum);//, S_OK);
   cnt = 0;
   ULONG fetched=1;
   while(fetched==1)
   {
      CComPtr<IDistributionFactorSegment> isegi;
      TRY_TEST( SUCCEEDED( penum->Next(1, &isegi, &fetched) ), TRUE);
      if (fetched)
         cnt++;
   }
   TRY_TEST(cnt, 4);

   // segments for member
   SegmentIndexType nSegments;
   CComPtr<IFilteredDfSegmentCollection> pfms1, pfms2, pfms3, pfms4, pfms5;
   CComPtr<IFilteredDfSegmentCollection> pfms1s, pfms2s, pfms3s, pfms4s, pfms5s;
   TRY_TEST( pss_o1->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pss_o1->GetMemberSegments(12.3, &pfms1), S_OK);
   TRY_TEST( pfms1->get_Count(&nSegments), S_OK);
   TRY_TEST( nSegments, 1);
   CComPtr<IDistributionFactorSegment> po1seg;
   TRY_TEST( pfms1->get_Item(0, &po1seg), S_OK);
   TRY_TEST( po1seg->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   TRY_TEST( pss_o1->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pss_o1->GetMemberSegments(12.3, &pfms1s), S_OK);
   TRY_TEST( pfms1s->get_Count(&nSegments), S_OK);
   TRY_TEST( nSegments, 1);
   CComPtr<IDistributionFactorSegment> po1segs;
   TRY_TEST( pfms1s->get_Item(0, &po1segs), S_OK);
   TRY_TEST( po1segs->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   TRY_TEST( pss_ts->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pss_ts->GetMemberSegments(12.3, &pfms2), S_OK);
   TRY_TEST( pfms2->get_Count(&nSegments), S_OK);
   TRY_TEST( nSegments, 2);
   CComPtr<IDistributionFactorSegment> po2seg;
   TRY_TEST( pfms2->get_Item(0, &po2seg), S_OK);
   TRY_TEST( po2seg->get_Length(&d), S_OK);
   TRY_TEST(d,  4.1);
   CComPtr<IDistributionFactorSegment> po21seg;
   TRY_TEST( pfms2->get_Item(1, &po21seg), S_OK);
   TRY_TEST( po21seg->get_Length(&d), S_OK);
   TRY_TEST( IsEqual(d, 8.2), true);

   TRY_TEST( pss_ts->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pss_ts->GetMemberSegments(12.3, &pfms2s), S_OK);
   TRY_TEST( pfms2s->get_Count(&nSegments), S_OK);
   TRY_TEST( nSegments, 3);
   CComPtr<IDistributionFactorSegment> po20segs, po21segs, po22segs;
   TRY_TEST( pfms2s->get_Item(0, &po20segs), S_OK);
   TRY_TEST( po20segs->get_Length(&d), S_OK);
   TRY_TEST(d, 4.1);
   TRY_TEST( pfms2s->get_Item(1, &po21segs), S_OK);
   TRY_TEST( po21segs->get_Length(&d), S_OK);
   TRY_TEST(IsEqual(d, 4.1), true );
   TRY_TEST( pfms2s->get_Item(2, &po22segs), S_OK);
   TRY_TEST( po22segs->get_Length(&d), S_OK);
   TRY_TEST(d, 4.1);

   TRY_TEST( pss_tl->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pss_tl->GetMemberSegments(12.3, &pfms3), S_OK);
   TRY_TEST( pfms3->get_Count(&nSegments), S_OK);
   TRY_TEST( nSegments, 2);
   CComPtr<IDistributionFactorSegment> po3seg;
   TRY_TEST( pfms3->get_Item(0, &po3seg), S_OK);
   TRY_TEST( po3seg->get_Length(&d), S_OK);
   TRY_TEST(d,  8.2);
   CComPtr<IDistributionFactorSegment> po31seg;
   TRY_TEST( pfms3->get_Item(1, &po31seg), S_OK);
   TRY_TEST( po31seg->get_Length(&d), S_OK);
   TRY_TEST( IsEqual(d, 4.1), true);

   TRY_TEST( pss_tl->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pss_tl->GetMemberSegments(12.3, &pfms3s), S_OK);
   TRY_TEST( pfms3s->get_Count(&nSegments), S_OK);
   TRY_TEST( nSegments, 1);
   CComPtr<IDistributionFactorSegment> po30segs, po31segs, po33segs;
   TRY_TEST( pfms3s->get_Item(0, &po30segs), S_OK);
   TRY_TEST( po30segs->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   TRY_TEST( pss_jr->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pss_jr->GetMemberSegments(12.3, &pfms4), S_OK);
   TRY_TEST( pfms4->get_Count(&nSegments), S_OK);
   TRY_TEST( nSegments, 2);
   CComPtr<IDistributionFactorSegment> po4seg;
   TRY_TEST( pfms4->get_Item(0, &po4seg), S_OK);
   TRY_TEST( po4seg->get_Length(&d), S_OK);
   TRY_TEST(d,  8.2);
   CComPtr<IDistributionFactorSegment> po41seg;
   TRY_TEST( pfms4->get_Item(1, &po41seg), S_OK);
   TRY_TEST( po41seg->get_Length(&d), S_OK);
   TRY_TEST( IsEqual(d, 4.1), true);

   TRY_TEST( pss_jr->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pss_jr->GetMemberSegments(12.3, &pfms4s), S_OK);
   TRY_TEST( pfms4s->get_Count(&nSegments), S_OK);
   TRY_TEST( nSegments, 1);
   CComPtr<IDistributionFactorSegment> po40segs, po41segs, po44segs;
   TRY_TEST( pfms4s->get_Item(0, &po40segs), S_OK);
   TRY_TEST( po40segs->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   TRY_TEST( pss_fr->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pss_fr->GetMemberSegments(12.3, &pfms5), S_OK);
   TRY_TEST( pfms5->get_Count(&nSegments), S_OK);
   TRY_TEST( nSegments, 3);
   CComPtr<IDistributionFactorSegment> po5seg;
   TRY_TEST( pfms5->get_Item(0, &po5seg), S_OK);
   TRY_TEST( po5seg->get_Length(&d), S_OK);
   TRY_TEST(d, -0.5);
   CComPtr<IDistributionFactorSegment> po51seg;
   TRY_TEST( pfms5->get_Item(1, &po51seg), S_OK);
   TRY_TEST( po51seg->get_Length(&d), S_OK);
   TRY_TEST( IsEqual(d, -1.0/6.0), true);

   TRY_TEST( pss_fr->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pss_fr->GetMemberSegments(12.3, &pfms5s), S_OK);
   TRY_TEST( pfms5s->get_Count(&nSegments), S_OK);
   TRY_TEST( nSegments, 1);
   CComPtr<IDistributionFactorSegment> po50segs;
   TRY_TEST( pfms5s->get_Item(0, &po50segs), S_OK);
   TRY_TEST( po50segs->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   // get segment for location
   CComPtr<IDistributionFactorSegment> spsiL1, spsiL2, spsiL3;
   CComPtr<IDistributionFactorSegment> spsiR1, spsiR2, spsiR3;
   CComBSTR bstr;
   TRY_TEST( pss_o1->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pss_o1->GetSegmentForLocation(0.0, 12.3, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1.IsEqualObject(ps4), true);
   TRY_TEST(spsiR1, NULL);
   spsiL1.Release();spsiR1.Release();

   TRY_TEST( pss_o1->GetSegmentForLocation(2.0, 12.3, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1.IsEqualObject(ps4), true);
   TRY_TEST(spsiR1, NULL);
   spsiL1.Release();spsiR1.Release();

   TRY_TEST( pss_o1->GetSegmentForLocation(8.0, 12.3, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1.IsEqualObject(ps4), true);
   TRY_TEST(spsiR1, NULL);
   spsiL1.Release();spsiR1.Release();

   TRY_TEST( pss_o1->GetSegmentForLocation(12.3, 12.3, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1.IsEqualObject(ps4), true);
   TRY_TEST(spsiR1, NULL);
   TRY_TEST( pss_o1->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   spsiL1.Release();spsiR1.Release();

   TRY_TEST( pss_o1->GetSegmentForLocation(0.0, 12.3, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1.IsEqualObject(ps4), true);
   TRY_TEST(spsiR1, NULL);
   spsiL1.Release();spsiR1.Release();

   TRY_TEST( pss_o1->GetSegmentForLocation(2.0, 12.3, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1.IsEqualObject(ps4), true);
   TRY_TEST(spsiR1, NULL);
   spsiL1.Release();spsiR1.Release();

   TRY_TEST( pss_o1->GetSegmentForLocation(8.0, 12.3, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1.IsEqualObject(ps4), true);
   TRY_TEST(spsiR1, NULL);
   spsiL1.Release();spsiR1.Release();

   TRY_TEST( pss_o1->GetSegmentForLocation(12.3, 12.3, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1.IsEqualObject(ps4), true);
   TRY_TEST(spsiR1, NULL);

   TRY_TEST( pss_ts->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pss_ts->GetSegmentForLocation(0.0, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST( spsiL2->get_Length(&d), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss2), true);
   TRY_TEST(spsiR2, NULL);
   spsiL2.Release();spsiR2.Release();

   // location is at junction where segments meet
   TRY_TEST( pss_ts->GetSegmentForLocation(4.1, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss2), true);
   TRY_TEST(spsiR2.IsEqualObject(pss3), true);
   spsiL2.Release();spsiR2.Release();

   TRY_TEST( pss_ts->GetSegmentForLocation(8.0, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2, NULL);
   spsiL2.Release();spsiR2.Release();

   // right at end of last segment
   TRY_TEST( pss_ts->GetSegmentForLocation(10.0, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2, NULL);
   spsiL2.Release();spsiR2.Release();

   // right at end of last segment
   TRY_TEST( pss_ts->GetSegmentForLocation(11.0, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2, NULL);
   spsiL2.Release();spsiR2.Release();

   TRY_TEST( pss_ts->GetSegmentForLocation(12.3, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2, NULL);
   spsiL2.Release();spsiR2.Release();

   TRY_TEST( pss_ts->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pss_ts->GetSegmentForLocation(0.0, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST( spsiL2->get_Length(&d), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss2), true);
   TRY_TEST(spsiR2, NULL);
   spsiL2.Release();spsiR2.Release();

   TRY_TEST( pss_ts->GetSegmentForLocation(4.1, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss2), true);
   TRY_TEST(spsiR2.IsEqualObject(pss3), true);
   spsiL2.Release();spsiR2.Release();

   TRY_TEST( pss_ts->GetSegmentForLocation(-1./3., 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss2), true);
   TRY_TEST(spsiR2.IsEqualObject(pss3), true);
   spsiL2.Release();spsiR2.Release();

   TRY_TEST( pss_ts->GetSegmentForLocation(4.101, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2, NULL);
   spsiL2.Release();spsiR2.Release();

   TRY_TEST( pss_ts->GetSegmentForLocation(5.1, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2, NULL);
   spsiL2.Release();spsiR2.Release();

   TRY_TEST( pss_ts->GetSegmentForLocation(8.0, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2, NULL);
   spsiL2.Release();spsiR2.Release();

   TRY_TEST( pss_ts->GetSegmentForLocation(12.3, 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2.IsEqualObject(pss2), true);
   TRY_TEST(spsiR2, NULL);

   TRY_TEST( pss_tl->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pss_tl->GetSegmentForLocation(0.0, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST( spsiL3->get_Length(&d), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss1), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_tl->GetSegmentForLocation(4.1, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss1), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_tl->GetSegmentForLocation(8.2, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss1), true);
   TRY_TEST(spsiR3.IsEqualObject(pss3), true);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_tl->GetSegmentForLocation(12.3, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss3), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_tl->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pss_tl->GetSegmentForLocation(0.0, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST( spsiL3->get_Length(&d), S_OK);
   TRY_TEST( spsiL3.IsEqualObject(pss1), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_tl->GetSegmentForLocation(4.1, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss1), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_tl->GetSegmentForLocation(4.101, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss1), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_tl->GetSegmentForLocation(5.1, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss1), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_tl->GetSegmentForLocation(8.0, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss1), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_tl->GetSegmentForLocation(12.3, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss1), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pss_fr->GetSegmentForLocation(0.0, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST( spsiL3->get_Length(&d), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->GetSegmentForLocation(-0.5, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiR3.IsEqualObject(pssf6), true);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->GetSegmentForLocation(4.1, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->GetSegmentForLocation(8.2, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pssf6), true);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->GetSegmentForLocation(8.3, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss2), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->GetSegmentForLocation(12.3, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pss2), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pss_fr->GetSegmentForLocation(0.0, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST( spsiL3->get_Length(&d), S_OK);
   TRY_TEST( spsiL3.IsEqualObject(pssf2), true);
   TRY_TEST( spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->GetSegmentForLocation(4.1, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->GetSegmentForLocation(4.101, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->GetSegmentForLocation(8.0, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiR3, NULL);
   spsiL3.Release();spsiR3.Release();

   TRY_TEST( pss_fr->GetSegmentForLocation(12.3, 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiR3, NULL);
}

void CTestDistributionFactor::TestDfOnly()
{

   HRESULT hr;

   // create a listener
   CComObject<CTestDistributionFactor>* pMe;
   CComObject<CTestDistributionFactor>::CreateInstance(&pMe);
   pMe->AddRef();

   // first test a stress point by itself
   CComPtr<IDistributionFactor> pg0;
   TRY_TEST( pg0.CoCreateInstance( CLSID_DistributionFactor ) , S_OK );

   Float64 g;
   TRY_TEST( pg0->get_GPedestrian(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GFat(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GRMul(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GRSgl(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GTSgl(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GTMul(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GDMul(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GDSgl(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GVMul(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GVSgl(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GNMMul(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GNMSgl(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GPMMul(&g), S_OK );
   TRY_TEST( g, 1.0 );
   TRY_TEST( pg0->get_GPMSgl(&g), S_OK );
   TRY_TEST( g, 1.0 );

   // let's listen to pg0
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pMe);
   TRY_TEST(AtlAdvise(pg0,punk,IID_IDistributionFactorEvents,&dwCookie),S_OK);

   TRY_TEST( pg0->put_GPedestrian(1.111), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GFat(1.1), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GRMul(1.2), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GRSgl(1.3), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GTSgl(1.4), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GTMul(1.45), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GDMul(1.5), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GDSgl(1.6), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GVMul(1.7), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GVSgl(1.8), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GNMMul(1.9), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GNMSgl(1.11), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GPMMul(1.12), S_OK );
   TEST_FIRED();
   TRY_TEST( pg0->put_GPMSgl(1.13), S_OK );
   TEST_FIRED();

   TRY_TEST( pg0->get_GPedestrian(&g), S_OK );
   TRY_TEST( g, 1.111 );
   TRY_TEST( pg0->get_GFat(&g), S_OK );
   TRY_TEST( g, 1.1 );
   TRY_TEST( pg0->get_GRMul(&g), S_OK );
   TRY_TEST( g, 1.2 );
   TRY_TEST( pg0->get_GRSgl(&g), S_OK );
   TRY_TEST( g, 1.3 );
   TRY_TEST( pg0->get_GTSgl(&g), S_OK );
   TRY_TEST( g, 1.4 );
   TRY_TEST( pg0->get_GTMul(&g), S_OK );
   TRY_TEST( g, 1.45);
   TRY_TEST( pg0->get_GDMul(&g), S_OK );
   TRY_TEST( g, 1.5 );
   TRY_TEST( pg0->get_GDSgl(&g), S_OK );
   TRY_TEST( g, 1.6 );
   TRY_TEST( pg0->get_GVMul(&g), S_OK );
   TRY_TEST( g, 1.7 );
   TRY_TEST( pg0->get_GVSgl(&g), S_OK );
   TRY_TEST( g, 1.8 );
   TRY_TEST( pg0->get_GNMMul(&g), S_OK );
   TRY_TEST( g, 1.9 );
   TRY_TEST( pg0->get_GNMSgl(&g), S_OK );
   TRY_TEST( g, 1.11);
   TRY_TEST( pg0->get_GPMMul(&g), S_OK );
   TRY_TEST( g, 1.12);
   TRY_TEST( pg0->get_GPMSgl(&g), S_OK );
   TRY_TEST( g, 1.13);

   TRY_TEST( pg0->put_GPedestrian(-1.111), E_INVALIDARG );
   TRY_TEST( pg0->put_GFat(-1.1), E_INVALIDARG );
   TRY_TEST( pg0->put_GRMul(-1.2), E_INVALIDARG );
   TRY_TEST( pg0->put_GRSgl(-1.3), E_INVALIDARG );
   TRY_TEST( pg0->put_GTSgl(-1.4), E_INVALIDARG );
   TRY_TEST( pg0->put_GTMul(-1.45), E_INVALIDARG );
   TRY_TEST( pg0->put_GDMul(-1.5), E_INVALIDARG );
   TRY_TEST( pg0->put_GDSgl(-1.6), E_INVALIDARG );
   TRY_TEST( pg0->put_GVMul(-1.7), E_INVALIDARG );
   TRY_TEST( pg0->put_GVSgl(-1.8), E_INVALIDARG );
   TRY_TEST( pg0->put_GNMMul(-1.9), E_INVALIDARG );
   TRY_TEST( pg0->put_GNMSgl(-1.11), E_INVALIDARG );
   TRY_TEST( pg0->put_GPMMul(-1.12), E_INVALIDARG );
   TRY_TEST( pg0->put_GPMSgl(-1.13), E_INVALIDARG );
   TRY_TEST(pMe->m_Fired, false);

   Float64 g1=2, g2=g1+.1,g3=g2+.1,g4=g3+.1,g5=g4+.1,g6=g5+.1,g7=g6+.1;
   Float64       g8=g7+.1,g9=g8+.1,g10=g9+.1,g11=g10+.1,g12=g11+.1,g13=g12+.1,g14=g13+.1;
   
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14), S_OK);
   TEST_FIRED();

   Float64 g1c, g2c,g3c,g4c,g5c,g6c,g7c,g8c,g9c,g10c,g11c,g12c, g13c, g14c;
   TRY_TEST( pg0->GetG(&g1c, &g2c, &g3c, &g4c, &g5c, &g6c, &g7c, &g8c, &g9c, &g10c, &g11c, &g12c, &g13c, &g14c), S_OK);
   TRY_TEST(g1, g1c);
   TRY_TEST(g2, g2c);
   TRY_TEST(g3, g3c);
   TRY_TEST(g4, g4c);
   TRY_TEST(g5, g5c);
   TRY_TEST(g6, g6c);
   TRY_TEST(g7, g7c);
   TRY_TEST(g8, g8c);
   TRY_TEST(g9, g9c);
   TRY_TEST(g10, g10c);
   TRY_TEST(g11, g11c);
   TRY_TEST(g12, g12c);
   TRY_TEST(g13, g13c);
   TRY_TEST(g14, g14c);

   TRY_TEST( pg0->get_GPedestrian(&g), S_OK );
   TRY_TEST( g, g14 );
   TRY_TEST( pg0->get_GFat(&g), S_OK );
   TRY_TEST( g, g13 );
   TRY_TEST( pg0->get_GTMul(&g), S_OK );
   TRY_TEST( g, g12 );
   TRY_TEST( pg0->get_GTSgl(&g), S_OK );
   TRY_TEST( g, g11 );
   TRY_TEST( pg0->get_GRMul(&g), S_OK );
   TRY_TEST( g, g10 );
   TRY_TEST( pg0->get_GRSgl(&g), S_OK );
   TRY_TEST( g, g9  );
   TRY_TEST( pg0->get_GDMul(&g), S_OK );
   TRY_TEST( g, g8 );
   TRY_TEST( pg0->get_GDSgl(&g), S_OK );
   TRY_TEST( g, g7 );
   TRY_TEST( pg0->get_GVMul(&g), S_OK );
   TRY_TEST( g, g6 );
   TRY_TEST( pg0->get_GVSgl(&g), S_OK );
   TRY_TEST( g, g5 );
   TRY_TEST( pg0->get_GNMMul(&g), S_OK );
   TRY_TEST( g, g4 );
   TRY_TEST( pg0->get_GNMSgl(&g), S_OK );
   TRY_TEST( g, g3 );
   TRY_TEST( pg0->get_GPMMul(&g), S_OK );
   TRY_TEST( g, g2 );
   TRY_TEST( pg0->get_GPMSgl(&g), S_OK );
   TRY_TEST( g, g1 );

   TRY_TEST( pg0->SetG(-1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, -2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, -3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, -4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, -5, g6, g7, g8, g9, g10, g11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, -6, g7, g8, g9, g10, g11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, g6, -7, g8, g9, g10, g11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, g6, g7, -8, g9, g10, g11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, g6, g7, g8, -9, g10, g11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, g6, g7, g8, g9, -10, g11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, -11, g12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, -12, g13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, -13, g14), E_INVALIDARG);
   TRY_TEST( pg0->SetG(g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, -14), E_INVALIDARG);
   TRY_TEST(pMe->m_Fired, false);

   // clone
   CComPtr<IDistributionFactor> pgc;
   TRY_TEST( pg0->Clone(&pgc), S_OK);
   TRY_TEST( pgc->GetG(&g1c, &g2c, &g3c, &g4c, &g5c, &g6c, &g7c, &g8c, &g9c, &g10c, &g11c, &g12c,&g13c,&g14c), S_OK);
   TRY_TEST(g1, g1c);
   TRY_TEST(g2, g2c);
   TRY_TEST(g3, g3c);
   TRY_TEST(g4, g4c);
   TRY_TEST(g5, g5c);
   TRY_TEST(g6, g6c);
   TRY_TEST(g7, g7c);
   TRY_TEST(g8, g8c);
   TRY_TEST(g9, g9c);
   TRY_TEST(g10, g10c);
   TRY_TEST(g11, g11c);
   TRY_TEST(g12, g12c);
   TRY_TEST(g13, g13c);
   TRY_TEST(g14, g14c);
   
   // persistence
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestDF"), 1.0);

      // get interface pointer to Save our cross section
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pg0.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<IDistributionFactor> psm2;
      TRY_TEST(psm2.CoCreateInstance( CLSID_DistributionFactor ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         TRY_TEST( psl->BeginUnit(CComBSTR("TestDF")), S_OK);

         IStructuredStorage2* piss2=NULL;
         TRY_TEST( psm2.QueryInterface(&piss2), S_OK);

         // Load 
         TRY_TEST( piss2->Load(psl), S_OK );

         piss2->Release();

         VARIANT_BOOL end;
         TRY_TEST( psl->EndUnit(&end), S_OK);
         TRY_TEST( psl->Close(), S_OK );

         // now compare values
         TRY_TEST( psm2->GetG(&g1c, &g2c, &g3c, &g4c, &g5c, &g6c, &g7c, &g8c, &g9c, &g10c, &g11c, &g12c, &g13c, &g14c), S_OK);
         TRY_TEST( IsEqual(g1, g1c), true);
         TRY_TEST( IsEqual(g2, g2c), true);
         TRY_TEST( IsEqual(g3, g3c), true);
         TRY_TEST( IsEqual(g4, g4c), true);
         TRY_TEST( IsEqual(g5, g5c), true);
         TRY_TEST( IsEqual(g6, g6c), true);
         TRY_TEST( IsEqual(g7, g7c), true);
         TRY_TEST( IsEqual(g8, g8c), true);
         TRY_TEST( IsEqual(g9, g9c), true);
         TRY_TEST( IsEqual(g10, g10c), true);
         TRY_TEST( IsEqual(g11, g11c), true);
         TRY_TEST( IsEqual(g12, g12c), true);
         TRY_TEST( IsEqual(g13, g13c), true);
         TRY_TEST( IsEqual(g14, g14c), true);
      }
   }

   // disconnect our connections
   TRY_TEST(AtlUnadvise(pg0,IID_IDistributionFactorEvents,dwCookie),S_OK);
   pMe->Release();
}



