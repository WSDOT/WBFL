///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
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

#include <WBFLComCollections.h>

template <class TISegment, const CLSID* pSegmentCLSID,  class TIContainer, 
          const CLSID* pContainerCLSID, class TListen, class TEvents, 
          const UUID* pEventUUID,class TIEnum,class IndexType>
class ContainerTester
{
public:
static HRESULT TestSegmentContainer(TListen* pMe)
{
   IndexType cnt;

   // create some segments
   CComPtr<TISegment> pss0, pss1, pss2,pss3,pss4, pss5, pss6;
   TRY_TEST( pss0.CoCreateInstance( *pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss0), S_OK);
   TRY_TEST( pss1.CoCreateInstance( *pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss1), S_OK);
   TRY_TEST( pss2.CoCreateInstance( *pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss2), S_OK);
   TRY_TEST( pss3.CoCreateInstance( *pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss3), S_OK);
   TRY_TEST( pss4.CoCreateInstance( *pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss4), S_OK);
   TRY_TEST( pss5.CoCreateInstance(*pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss5), S_OK);
   TRY_TEST( pss6.CoCreateInstance(*pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss6), S_OK);

   // create the container
   CComPtr<TIContainer> pcnt1, pcnt2;
   TRY_TEST( pcnt1.CoCreateInstance( *pContainerCLSID ) , S_OK );

   // set up the listener for the container
   DWORD dwCookie;
   CComQIPtr<TEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pcnt1,punk,*pEventUUID,&dwCookie),S_OK);

   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 0);
   TRY_TEST( pcnt1->Add(pss0) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 1);
   TRY_TEST( pcnt1->Add(pss1) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 2);
   TRY_TEST( pcnt1->Add(pss3) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 3);
   TRY_TEST( pcnt1->Insert(2,pss2) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 4);
   TRY_TEST( pcnt1->Insert(4,pss4) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);
   TRY_TEST( pcnt1->Insert(0,pss5) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);
   TRY_TEST( pcnt1->MoveTo(0,5) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);
   TRY_TEST( pcnt1->Add(pss6) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 7);

   CComPtr<TISegment> pss0t, pss1t, pss2t,pss3t,pss4t, pss5t, pss6t;
   TRY_TEST( pcnt1->get_Item(0,&pss0t) , S_OK );
   TRY_TEST(pss0t.IsEqualObject(pss0), true);
   TRY_TEST( pcnt1->get_Item(1,&pss1t) , S_OK );
   TRY_TEST(pss1t.IsEqualObject(pss1), true);
   TRY_TEST( pcnt1->get_Item(2,&pss2t) , S_OK );
   TRY_TEST(pss2t.IsEqualObject(pss2), true);
   TRY_TEST( pcnt1->get_Item(3,&pss3t) , S_OK );
   TRY_TEST(pss3t.IsEqualObject(pss3), true);
   TRY_TEST( pcnt1->get_Item(4,&pss4t) , S_OK );
   TRY_TEST(pss4t.IsEqualObject(pss4), true);
   TRY_TEST( pcnt1->get_Item(5,&pss5t) , S_OK );
   TRY_TEST(pss5t.IsEqualObject(pss5), true);
   TRY_TEST( pcnt1->get_Item(6,&pss6t) , S_OK );
   TRY_TEST(pss6t.IsEqualObject(pss6), true);

   TRY_TEST( pcnt1->CopyTo(0,7) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 8);

   TRY_TEST( pcnt1->Remove(7) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 7);

   TRY_TEST( pcnt1->Remove(0) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);

   TRY_TEST( pcnt1->Reverse() , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);

   CComPtr<TISegment> pss1r, pss2r,pss3r,pss4r, pss5r, pss6r;
   TRY_TEST( pcnt1->get_Item(5,&pss1r) , S_OK );
   TRY_TEST(pss1r.IsEqualObject(pss1), true);
   TRY_TEST( pcnt1->get_Item(4,&pss2r) , S_OK );
   TRY_TEST(pss2r.IsEqualObject(pss2), true);
   TRY_TEST( pcnt1->get_Item(3,&pss3r) , S_OK );
   TRY_TEST(pss3r.IsEqualObject(pss3), true);
   TRY_TEST( pcnt1->get_Item(2,&pss4r) , S_OK );
   TRY_TEST(pss4r.IsEqualObject(pss4), true);
   TRY_TEST( pcnt1->get_Item(1,&pss5r) , S_OK );
   TRY_TEST(pss5r.IsEqualObject(pss5), true);
   TRY_TEST( pcnt1->get_Item(0,&pss6r) , S_OK );
   TRY_TEST(pss6r.IsEqualObject(pss6), true);

   // check some bounds
   TRY_TEST( pcnt1->Remove(-1) , E_INVALIDARG );
   TRY_TEST( pcnt1->Remove(6) , E_INVALIDARG );
   TRY_TEST( pcnt1->MoveTo(-1, 2) , E_INVALIDARG );
   TRY_TEST( pcnt1->MoveTo( 2,-2) , E_INVALIDARG );
   TRY_TEST( pcnt1->MoveTo( 6, 2) , E_INVALIDARG );
   TRY_TEST( pcnt1->MoveTo( 2, 6) , E_INVALIDARG );
   TRY_TEST( pcnt1->CopyTo(-1, 2) , E_INVALIDARG );
   TRY_TEST( pcnt1->CopyTo( 2,-2) , E_INVALIDARG );
   TRY_TEST( pcnt1->CopyTo( 7, 2) , E_INVALIDARG );
   TRY_TEST( pcnt1->CopyTo( 2, 7) , E_INVALIDARG );
   pss0t.Release();
   TRY_TEST( pcnt1->get_Item(-1,&pss0t) , E_INVALIDARG );
   TRY_TEST( pcnt1->get_Item( 6,&pss0t) , E_INVALIDARG );

   // clone
   TRY_TEST( pcnt1->Clone(&pcnt2) , S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);

   // enumerators
   CComPtr<TIEnum> penum;
   pcnt1->get__EnumElements(&penum);//, S_OK);
   cnt = 0;
   ULONG fetched=1;
   while(fetched==1)
   {
      CComPtr<TISegment> isegi;
      TRY_TEST( SUCCEEDED( penum->Next(1, &isegi, &fetched) ), TRUE);
      if (fetched)
         cnt++;
   }
   TRY_TEST(cnt, 6);

   // stop listening
   TRY_TEST(AtlUnadvise(pcnt1,*pEventUUID,dwCookie),S_OK);


   return S_OK;
}


static HRESULT TestVectorContainer(TListen* pMe)
{
   VehicleIndexType cnt;

   // create some segments
   CComPtr<TISegment> pss0, pss1, pss2,pss3,pss4, pss5, pss6;
   TRY_TEST( pss0.CoCreateInstance( *pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss0), S_OK);
   TRY_TEST( pss1.CoCreateInstance( *pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss1), S_OK);
   TRY_TEST( pss2.CoCreateInstance( *pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss2), S_OK);
   TRY_TEST( pss3.CoCreateInstance( *pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss3), S_OK);
   TRY_TEST( pss4.CoCreateInstance( *pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss4), S_OK);
   TRY_TEST( pss5.CoCreateInstance(*pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss5), S_OK);
   TRY_TEST( pss6.CoCreateInstance(*pSegmentCLSID ) , S_OK );
   TRY_TEST( pMe->OnCreateSegment(pss6), S_OK);

   // create the container
   CComPtr<TIContainer> pcnt1, pcnt2;
   TRY_TEST( pcnt1.CoCreateInstance( *pContainerCLSID ) , S_OK );

   // set up the listener for the container
   DWORD dwCookie;
   CComQIPtr<TEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pcnt1,punk,*pEventUUID,&dwCookie),S_OK);

   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 0);
   TRY_TEST( pcnt1->Add(pss0) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 1);
   TRY_TEST( pcnt1->Add(pss1) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 2);
   TRY_TEST( pcnt1->Add(pss3) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 3);
   TRY_TEST( pcnt1->Insert(2,pss2) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 4);
   TRY_TEST( pcnt1->Insert(4,pss4) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);
   TRY_TEST( pcnt1->Add(pss6) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);
   TRY_TEST( pcnt1->Insert(5,pss5) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 7);

   CComPtr<TISegment> pss0t, pss1t, pss2t,pss3t,pss4t, pss5t, pss6t;
   TRY_TEST( pcnt1->get_Item(0,&pss0t) , S_OK );
   TRY_TEST(pss0t.IsEqualObject(pss0), true);
   TRY_TEST( pcnt1->get_Item(1,&pss1t) , S_OK );
   TRY_TEST(pss1t.IsEqualObject(pss1), true);
   TRY_TEST( pcnt1->get_Item(2,&pss2t) , S_OK );
   TRY_TEST(pss2t.IsEqualObject(pss2), true);
   TRY_TEST( pcnt1->get_Item(3,&pss3t) , S_OK );
   TRY_TEST(pss3t.IsEqualObject(pss3), true);
   TRY_TEST( pcnt1->get_Item(4,&pss4t) , S_OK );
   TRY_TEST(pss4t.IsEqualObject(pss4), true);
   TRY_TEST( pcnt1->get_Item(5,&pss5t) , S_OK );
   TRY_TEST(pss5t.IsEqualObject(pss5), true);
   TRY_TEST( pcnt1->get_Item(6,&pss6t) , S_OK );
   TRY_TEST(pss6t.IsEqualObject(pss6), true);

   TRY_TEST( pcnt1->Remove(6) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);

   TRY_TEST( pcnt1->Remove(0) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);

   // check some bounds
   TRY_TEST( pcnt1->Remove(-1) , E_INVALIDARG );
   TRY_TEST( pcnt1->Remove(6) , E_INVALIDARG );
   pss0t.Release();
   TRY_TEST( pcnt1->get_Item(-1,&pss0t) , E_INVALIDARG );
   TRY_TEST( pcnt1->get_Item( 6,&pss0t) , E_INVALIDARG );

   // clone
   TRY_TEST( pcnt1->Clone(&pcnt2) , S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);

   // enumerators
   CComPtr<TIEnum> penum;
   pcnt1->get__EnumElements(&penum);//, S_OK);
   cnt = 0;
   ULONG fetched=1;
   while(fetched==1)
   {
      CComPtr<TISegment> isegi;
      TRY_TEST( SUCCEEDED( penum->Next(1, &isegi, &fetched) ), TRUE);
      if (fetched)
         cnt++;
   }
   TRY_TEST(cnt, 5);

   // stop listening
   TRY_TEST(AtlUnadvise(pcnt1,*pEventUUID,dwCookie),S_OK);


   return S_OK;
}


};