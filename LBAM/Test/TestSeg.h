///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2019  Washington State Department of Transportation
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


// function for setting up segements
void SetupSegment(ISegment* pseg);

// template class for testing segments portion of member interfaces

template <class TTest, class TSegs>
HRESULT TestSegments(TTest* pMe, TSegs* pSegs)
{
   SegmentIndexType cnt;
   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Bogus Stage"),&cnt), S_OK );
   TRY_TEST(cnt,0);

   CComPtr<ISegment> pss1, pss2,pss3,pss4, pssf2, pssf6;

   TRY_TEST( pss1.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pss3.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pss4.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pssf2.CoCreateInstance( CLSID_Segment ) , S_OK );
   TRY_TEST( pssf6.CoCreateInstance( CLSID_Segment ) , S_OK );

   TRY_TEST( pss1->put_Length(8.2), S_OK );
   SetupSegment(pss1); // set up cross section and stress points
   TRY_TEST( pss2->put_Length(4.1), S_OK );
   SetupSegment(pss2);
   TRY_TEST( pss3->put_Length(5.9), S_OK );
   SetupSegment(pss3);
   TRY_TEST( pss4->put_Length(12.3), S_OK );
   SetupSegment(pss4);
   TRY_TEST( pssf2->put_Length(-0.5), S_OK );
   SetupSegment(pssf2);
   TRY_TEST( pssf6->put_Length(-1.0/6.0), S_OK );
   SetupSegment(pssf6);
   TRY_TEST( pssf6->put_Length(-1.1), E_INVALIDARG );

   // create some stages with different segment combinations
   TRY_TEST( pSegs->AddSegment(CComBSTR("Too Short"), pss2), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->AddSegment(CComBSTR("Too Short"), pss3), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->AddSegment(CComBSTR("Just Right"), pss1), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->AddSegment(CComBSTR("Just Right"), pss2), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->AddSegment(CComBSTR("Too Long"), pss1), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->AddSegment(CComBSTR("Too Long"), pss2), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->AddSegment(CComBSTR("Too Long"), pss3), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->AddSegment(CComBSTR("Only One"), pss4), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->AddSegment(CComBSTR("Fractional"), pssf2), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->AddSegment(CComBSTR("Fractional"), pssf6), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->AddSegment(CComBSTR("Fractional"), pss2), S_OK);
   TEST_STIFFNESS_FIRED();

   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Too Short"), &cnt), S_OK);
   TRY_TEST( cnt, 2);
   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Too Long"), &cnt), S_OK);
   TRY_TEST( cnt, 3);
   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Only One"), &cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Fractional"), &cnt), S_OK);
   TRY_TEST( cnt, 3);

   Float64 d;
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Too Short"), &d), S_OK);
   TRY_TEST( d, 10.0);
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Just Right"), &d), S_OK);
   TRY_TEST( IsEqual(d, 12.3), true);
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Too Long"), &d), S_OK);
   TRY_TEST( d, 18.2);
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Only One"), &d), S_OK);
   TRY_TEST( d, 12.3);
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Fractional"), &d), S_OK);
   TRY_TEST( IsEqual(d,12.3), true);

   // copy to
   TRY_TEST( pSegs->CopySegmentTo(CComBSTR("Too Long"), 0, 3), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Too Long"), &cnt), S_OK);
   TRY_TEST( cnt, 4);
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Too Long"), &d), S_OK);
   TRY_TEST( d, 26.4);
   TRY_TEST( pSegs->CopySegmentTo(CComBSTR("Too Long"),-1, 2), E_INVALIDARG);
   TRY_TEST( pSegs->CopySegmentTo(CComBSTR("Too Long"), 5, 2), E_INVALIDARG);
   TRY_TEST( pSegs->CopySegmentTo(CComBSTR("Too Long"), 1,-1), E_INVALIDARG);
   TRY_TEST( pSegs->CopySegmentTo(CComBSTR("Too Long"), 1, 5), E_INVALIDARG);

   // reverse
   CComPtr<ISegment> ps1, ps2;
   TRY_TEST( pSegs->get_Segment(CComBSTR("Too Long"), 1, &ps1), S_OK);
   TRY_TEST( ps1->get_Length(&d), S_OK);
   TRY_TEST( d, 4.1);
   TRY_TEST( pSegs->ReverseSegments(CComBSTR("Too Long")), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Too Long"), &d), S_OK);
   TRY_TEST( d, 26.4);
   TRY_TEST( pSegs->get_Segment(CComBSTR("Too Long"), 1,&ps2), S_OK);
   TRY_TEST( ps2->get_Length(&d), S_OK);
   TRY_TEST( d, 5.9);
   TRY_TEST( ps2->put_Length(5.0), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( ps2->get_Length(&d), S_OK);
   TRY_TEST( d, 5.0);
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Too Long"), &d), S_OK);
   TRY_TEST( IsEqual(d, 25.5), true);

   TRY_TEST( pSegs->ReverseSegments(CComBSTR("Too Long")), S_OK);

   // move to
   TRY_TEST( pSegs->MoveSegmentTo(CComBSTR("Too Long"), 1, 3), S_OK);
   CComPtr<ISegment> ps3;
   TRY_TEST( pSegs->get_Segment(CComBSTR("Too Long"), 3, &ps3), S_OK);
   TRY_TEST( ps3->get_Length(&d), S_OK);
   TRY_TEST( d, 4.1);
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Too Long"), &d), S_OK);
   TRY_TEST( IsEqual(d, 25.5), true);
   TRY_TEST( pSegs->MoveSegmentTo(CComBSTR("Too Long"),-1, 2), E_INVALIDARG);
   TRY_TEST( pSegs->MoveSegmentTo(CComBSTR("Too Long"), 4, 2), E_INVALIDARG);
   TRY_TEST( pSegs->MoveSegmentTo(CComBSTR("Too Long"), 1,-1), E_INVALIDARG);
   TRY_TEST( pSegs->MoveSegmentTo(CComBSTR("Too Long"), 1, 4), E_INVALIDARG);

   CComPtr<ISegment> ibog;
   TRY_TEST( pSegs->get_Segment(CComBSTR("Too Long"), 4,&ibog), E_INVALIDARG);
   ibog.Release();
   TRY_TEST( pSegs->get_Segment(CComBSTR("bogus"), 0,&ibog), S_OK);
   TRY_TEST( ibog, 0);

   // remove & segment clone
   TRY_TEST( pSegs->RemoveSegment(CComBSTR("Too Long"), 3), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Too Long"), &cnt), S_OK);
   TRY_TEST( cnt, 3);
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Too Long"), &d), S_OK);
   TRY_TEST( IsEqual(d, 21.4), true);
   CComPtr<ISegment> ps4;
   TRY_TEST( ps3->Clone(&ps4), S_OK);
   TRY_TEST( ps4->get_Length(&d), S_OK);
   TRY_TEST( d, 4.1);
   TRY_TEST( pSegs->RemoveSegment(CComBSTR("Too Long"), -1), E_INVALIDARG);
   TRY_TEST( pSegs->RemoveSegment(CComBSTR("Too Long"), 3), E_INVALIDARG);
   TRY_TEST( pSegs->CopySegmentTo(CComBSTR("Too Long"), 1, 3), S_OK);
   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Too Long"), &cnt), S_OK);
   TRY_TEST( cnt, 4);
   TRY_TEST( pSegs->RemoveSegment(CComBSTR("Too Long"), 3), S_OK); // remove last
   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Too Long"), &cnt), S_OK);
   TRY_TEST( cnt, 3);

   // insert
   TRY_TEST( pSegs->InsertSegment(CComBSTR("Too Long"), 3, ps4), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Too Long"), &cnt), S_OK);
   TRY_TEST( cnt, 4);
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Too Long"), &d), S_OK);
   TRY_TEST( IsEqual(d, 25.5), true);
   TRY_TEST( pSegs->InsertSegment(CComBSTR("Too Long"), -1, ps4), E_INVALIDARG);
   TRY_TEST( pSegs->InsertSegment(CComBSTR("Too Long"), 5, ps4), E_INVALIDARG);

   // put
   TRY_TEST( pSegs->putref_Segment(CComBSTR("Only One"), 0, ps4), S_OK);
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->get_SegmentCount(CComBSTR("Only One"), &cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST( pSegs->get_SegmentLength(CComBSTR("Only One"), &d), S_OK);
   TRY_TEST( IsEqual(d, 4.1), true);
   TRY_TEST( ps4->put_Length(12.3), S_OK );
   TEST_STIFFNESS_FIRED();
   TRY_TEST( pSegs->putref_Segment(CComBSTR("Only One"), -1, ps4), E_INVALIDARG);
   TRY_TEST( pSegs->putref_Segment(CComBSTR("Only One"), 1, ps4), E_INVALIDARG);

   // collections stuff
   // IEnum
   CComPtr<IEnumSegmentItem> penum;
   pSegs->get__EnumElements(&penum);//, S_OK);
   cnt = 0;
   ULONG fetched=1;
   while(fetched==1)
   {
      CComPtr<ISegmentItem> isegi;
      TRY_TEST( SUCCEEDED( penum->Next(1, &isegi, &fetched) ), TRUE);
      if (fetched)
         cnt++;
   }
   TRY_TEST(cnt, 12);

   // Segments for stage
   CComPtr<IFilteredSegmentCollection> pfs1, pfs2, pfs3;
   TRY_TEST( pSegs->GetSegmentsForStage(CComBSTR("Only One"), &pfs1), S_OK);
   TRY_TEST( pfs1->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   CComPtr<ISegment> pseg1;
   TRY_TEST( pfs1->get_Item(0, &pseg1), S_OK);
   TRY_TEST( pseg1->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   TRY_TEST( pSegs->GetSegmentsForStage(CComBSTR("Too Long"), &pfs2), S_OK);
   TRY_TEST( pfs2->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 4);
   Float64 l = 0;
   for (SegmentIndexType i = 0; i<cnt; i++)
   {
      CComPtr<ISegment> ptseg;
      TRY_TEST( pfs2->get_Item(i, &ptseg), S_OK);
      TRY_TEST( ptseg->get_Length(&d), S_OK);
      l += d;
   }
   TRY_TEST(l, 33.7);
   TRY_TEST( pSegs->GetSegmentsForStage(CComBSTR("bogus"), &pfs3), S_OK);
   TRY_TEST(pfs3->get_Count(&cnt),S_OK);
   TRY_TEST(cnt, 0);

   CComPtr<IEnumSegment> penums;
   TRY_TEST( pfs2->get__EnumElements(&penums), S_OK);
   cnt = 0;
   fetched=1;
   while(fetched==1)
   {
      CComPtr<ISegment> iseg;
      TRY_TEST( SUCCEEDED( penums->Next(1, &iseg, &fetched) ), TRUE);
      if (fetched)
         cnt++;
   }
   TRY_TEST(cnt, 4);

   // segments for member
   CComPtr<IFilteredSegmentCollection> pfms1, pfms2, pfms3, pfms4, pfms5;
   CComPtr<IFilteredSegmentCollection> pfms1s, pfms2s, pfms3s, pfms4s, pfms5s;
   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pSegs->GetMemberSegments(CComBSTR("Only One"), &pfms1), S_OK);
   TRY_TEST( pfms1->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   CComPtr<ISegment> po1seg;
   TRY_TEST( pfms1->get_Item(0, &po1seg), S_OK);
   TRY_TEST( po1seg->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pSegs->GetMemberSegments(CComBSTR("Only One"), &pfms1s), S_OK);
   TRY_TEST( pfms1s->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   CComPtr<ISegment> po1segs;
   TRY_TEST( pfms1s->get_Item(0, &po1segs), S_OK);
   TRY_TEST( po1segs->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pSegs->GetMemberSegments(CComBSTR("Too Short"), &pfms2), S_OK);
   TRY_TEST( pfms2->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 2);
   CComPtr<ISegment> po2seg;
   TRY_TEST( pfms2->get_Item(0, &po2seg), S_OK);
   TRY_TEST( po2seg->get_Length(&d), S_OK);
   TRY_TEST(d,  4.1);
   CComPtr<ISegment> po21seg;
   TRY_TEST( pfms2->get_Item(1, &po21seg), S_OK);
   TRY_TEST( po21seg->get_Length(&d), S_OK);
   TRY_TEST( IsEqual(d, 8.2), true);

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pSegs->GetMemberSegments(CComBSTR("Too Short"), &pfms2s), S_OK);
   TRY_TEST( pfms2s->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 3);
   CComPtr<ISegment> po20segs, po21segs, po22segs;
   TRY_TEST( pfms2s->get_Item(0, &po20segs), S_OK);
   TRY_TEST( po20segs->get_Length(&d), S_OK);
   TRY_TEST(d, 4.1);
   TRY_TEST( pfms2s->get_Item(1, &po21segs), S_OK);
   TRY_TEST( po21segs->get_Length(&d), S_OK);
   TRY_TEST(IsEqual(d, 4.1), true );
   TRY_TEST( pfms2s->get_Item(2, &po22segs), S_OK);
   TRY_TEST( po22segs->get_Length(&d), S_OK);
   TRY_TEST(d, 4.1);

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pSegs->GetMemberSegments(CComBSTR("Too Long"), &pfms3), S_OK);
   TRY_TEST( pfms3->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 2);
   CComPtr<ISegment> po3seg;
   TRY_TEST( pfms3->get_Item(0, &po3seg), S_OK);
   TRY_TEST( po3seg->get_Length(&d), S_OK);
   TRY_TEST(d,  8.2);
   CComPtr<ISegment> po31seg;
   TRY_TEST( pfms3->get_Item(1, &po31seg), S_OK);
   TRY_TEST( po31seg->get_Length(&d), S_OK);
   TRY_TEST( IsEqual(d, 4.1), true);

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pSegs->GetMemberSegments(CComBSTR("Too Long"), &pfms3s), S_OK);
   TRY_TEST( pfms3s->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   CComPtr<ISegment> po30segs, po31segs, po33segs;
   TRY_TEST( pfms3s->get_Item(0, &po30segs), S_OK);
   TRY_TEST( po30segs->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pSegs->GetMemberSegments(CComBSTR("Just Right"), &pfms4), S_OK);
   TRY_TEST( pfms4->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 2);
   CComPtr<ISegment> po4seg;
   TRY_TEST( pfms4->get_Item(0, &po4seg), S_OK);
   TRY_TEST( po4seg->get_Length(&d), S_OK);
   TRY_TEST(d,  8.2);
   CComPtr<ISegment> po41seg;
   TRY_TEST( pfms4->get_Item(1, &po41seg), S_OK);
   TRY_TEST( po41seg->get_Length(&d), S_OK);
   TRY_TEST( IsEqual(d, 4.1), true);

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pSegs->GetMemberSegments(CComBSTR("Just Right"), &pfms4s), S_OK);
   TRY_TEST( pfms4s->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   CComPtr<ISegment> po40segs, po41segs, po44segs;
   TRY_TEST( pfms4s->get_Item(0, &po40segs), S_OK);
   TRY_TEST( po40segs->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pSegs->GetMemberSegments(CComBSTR("Fractional"), &pfms5), S_OK);
   TRY_TEST( pfms5->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 3);
   CComPtr<ISegment> po5seg;
   TRY_TEST( pfms5->get_Item(0, &po5seg), S_OK);
   TRY_TEST( po5seg->get_Length(&d), S_OK);
   TRY_TEST(d, -0.5);
   CComPtr<ISegment> po51seg;
   TRY_TEST( pfms5->get_Item(1, &po51seg), S_OK);
   TRY_TEST( po51seg->get_Length(&d), S_OK);
   TRY_TEST( IsEqual(d, -1.0/6.0), true);

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   TRY_TEST( pSegs->GetMemberSegments(CComBSTR("Fractional"), &pfms5s), S_OK);
   TRY_TEST( pfms5s->get_Count(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   CComPtr<ISegment> po50segs;
   TRY_TEST( pfms5s->get_Item(0, &po50segs), S_OK);
   TRY_TEST( po50segs->get_Length(&d), S_OK);
   TRY_TEST(d, 12.3);


   // get segment for location
   CComPtr<ISegmentItem> spsiL1, spsiL2, spsiL3;
   CComPtr<ISegmentItem> spsiR1, spsiR2, spsiR3;
   CComPtr<ISegment> sps1, sps2, sps3;
   CComBSTR bstr;
   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Only One"), 0.0, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1->get_Segment(&sps1), S_OK);
   TRY_TEST(sps1.IsEqualObject(ps4), true);
   TRY_TEST(spsiL1->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL1->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Only One"));
   TRY_TEST(spsiR1, nullptr);
   bstr.Empty();
   spsiL1.Release();spsiR1.Release();
   sps1.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Only One"), 2.0, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1->get_Segment(&sps1), S_OK);
   TRY_TEST(sps1.IsEqualObject(ps4), true);
   TRY_TEST(spsiL1->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL1->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Only One"));
   TRY_TEST(spsiR1, nullptr);
   bstr.Empty();
   spsiL1.Release();spsiR1.Release();
   sps1.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Only One"), 8.0, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1->get_Segment(&sps1), S_OK);
   TRY_TEST(sps1.IsEqualObject(ps4), true);
   TRY_TEST(spsiL1->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL1->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Only One"));
   TRY_TEST(spsiR1, nullptr);
   bstr.Empty();
   spsiL1.Release();spsiR1.Release();
   sps1.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Only One"), 12.3, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1->get_Segment(&sps1), S_OK);
   TRY_TEST(sps1.IsEqualObject(ps4), true);
   TRY_TEST(spsiL1->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL1->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Only One"));
   TRY_TEST(spsiR1, nullptr);
   bstr.Empty();

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   spsiL1.Release();spsiR1.Release();
   sps1.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Only One"), 0.0, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1->get_Segment(&sps1), S_OK);
   TRY_TEST(sps1.IsEqualObject(ps4), true);
   TRY_TEST(spsiL1->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL1->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Only One"));
   TRY_TEST(spsiR1, nullptr);
   bstr.Empty();
   spsiL1.Release();spsiR1.Release();
   sps1.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Only One"), 2.0, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1->get_Segment(&sps1), S_OK);
   TRY_TEST(sps1.IsEqualObject(ps4), true);
   TRY_TEST(spsiL1->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL1->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Only One"));
   TRY_TEST(spsiR1, nullptr);
   bstr.Empty();
   spsiL1.Release();spsiR1.Release();
   sps1.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Only One"), 8.0, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1->get_Segment(&sps1), S_OK);
   TRY_TEST(sps1.IsEqualObject(ps4), true);
   TRY_TEST(spsiL1->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL1->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Only One"));
   TRY_TEST(spsiR1, nullptr);
   bstr.Empty();
   spsiL1.Release();spsiR1.Release();
   sps1.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Only One"), 12.3, &spsiL1, &spsiR1), S_OK);
   TRY_TEST(spsiL1->get_Segment(&sps1), S_OK);
   TRY_TEST(sps1.IsEqualObject(ps4), true);
   TRY_TEST(spsiL1->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL1->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Only One"));
   TRY_TEST(spsiR1, nullptr);
   bstr.Empty();

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 0.0, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST( sps2->get_Length(&d), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss2), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   TRY_TEST(spsiR2, nullptr);
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   // location is at junction where segments meet
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 4.1, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss2), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   bstr.Empty();
   sps2.Release();
   TRY_TEST(spsiR2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiR2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 8.0, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   TRY_TEST(spsiR2, nullptr);
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   // right at end of last segment
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 10.0, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   TRY_TEST(spsiR2, nullptr);
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   // right at end of last segment
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 11.0, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   TRY_TEST(spsiR2, nullptr);
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   TRY_TEST(spsiR2, nullptr);
   bstr.Empty();
   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 0.0, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST( sps2->get_Length(&d), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss2), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   TRY_TEST(spsiR2, nullptr);
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 4.1, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss2), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   bstr.Empty();
   sps2.Release();
   TRY_TEST(spsiR2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiR2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   bstr.Empty();
   sps2.Release();
   TRY_TEST(spsiR2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiR2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), -1./3., &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss2), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   bstr.Empty();
   sps2.Release();
   TRY_TEST(spsiR2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiR2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   bstr.Empty();
   sps2.Release();
   TRY_TEST(spsiR2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiR2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiR2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 4.101, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   TRY_TEST(spsiR2, nullptr);
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 5.1, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   TRY_TEST(spsiR2, nullptr);
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 8.0, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss3), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   TRY_TEST(spsiR2, nullptr);
   bstr.Empty();
   spsiL2.Release();spsiR2.Release();
   sps2.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Short"), 12.3, &spsiL2, &spsiR2), S_OK);
   TRY_TEST(spsiL2->get_Segment(&sps2), S_OK);
   TRY_TEST(sps2.IsEqualObject(pss2), true);
   TRY_TEST(spsiL2->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL2->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Short"));
   TRY_TEST(spsiR2, nullptr);
   bstr.Empty();

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Long"), 0.0, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST( sps3->get_Length(&d), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss1), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Long"), 4.1, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss1), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Long"), 8.2, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss1), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   bstr.Empty();
   sps3.Release();
   TRY_TEST(spsiR3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss3), true);
   TRY_TEST(spsiR3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiR3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Long"), 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss3), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Long"), 0.0, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST( sps3->get_Length(&d), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss1), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Long"), 4.1, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss1), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Long"), 4.101, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss1), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Long"), 5.1, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss1), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Long"), 8.0, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss1), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Too Long"), 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss1), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Too Long"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_FALSE), S_OK);
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), 0.0, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST( sps3->get_Length(&d), S_OK);
   TRY_TEST(sps3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), -0.5, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   bstr.Empty();
   sps3.Release();
   TRY_TEST(spsiR3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pssf6), true);
   TRY_TEST(spsiR3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiR3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), 4.1, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), 8.2, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pssf6), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 1);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), 8.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss2), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 2);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pss2), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 2);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();

   TRY_TEST( pSegs->put_IsSymmetrical(VARIANT_TRUE), S_OK);
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), 0.0, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST( sps3->get_Length(&d), S_OK);
   TRY_TEST(sps3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), 4.1, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), 4.101, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), 8.0, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();
   spsiL3.Release();spsiR3.Release();
   sps3.Release();
   TRY_TEST( pSegs->GetSegmentForMemberLocation(CComBSTR("Fractional"), 12.3, &spsiL3, &spsiR3), S_OK);
   TRY_TEST(spsiL3->get_Segment(&sps3), S_OK);
   TRY_TEST(sps3.IsEqualObject(pssf2), true);
   TRY_TEST(spsiL3->get_RelPosition(&cnt), S_OK);
   TRY_TEST( cnt, 0);
   TRY_TEST(spsiL3->get_Stage(&bstr), S_OK);
   TRY_TEST( bstr, CComBSTR("Fractional"));
   TRY_TEST(spsiR3, nullptr);
   bstr.Empty();

   // see if events bubble all the way from stress points
   ps1.Release();
   TRY_TEST( pSegs->get_Segment(CComBSTR("Too Long"), 1, &ps1), S_OK);
   CComPtr<ISegmentCrossSection> pcss;
   TRY_TEST( ps1->get_SegmentCrossSection(&pcss), S_OK);
   CComPtr<IStressPoints> pspss;
   TRY_TEST( pcss->get_StressPoints(&pspss), S_OK);
   CComPtr<IStressPoint> psp;
   TRY_TEST( pspss->get_Item(0, &psp), S_OK);
   TRY_TEST( psp->put_Sa(3.14), S_OK);
   TEST_STRESS_FIRED();

   // clear out fractional stage
   TRY_TEST( pSegs->RemoveStage(CComBSTR("Fractional")), S_OK);
   ps1.Release();
   TRY_TEST( pSegs->get_Segment(CComBSTR("Fractional"), 1, &ps1), S_OK);
   TRY_TEST(ps1, 0);

   return S_OK;
}