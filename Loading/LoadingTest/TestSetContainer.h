///////////////////////////////////////////////////////////////////////
// Loading Test - Test driver for Loading library
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

#include <WBFLComCollections.h>

template <class TIItem, class TIContainer, 
          class TListen, class TEvents, 
          const UUID* pEventDSPID, class TIEnum>
class BSTRSetContainerTester
{
public:
static HRESULT TestContainer(TListen* pMe,const CLSID& itemCLSID, const CLSID& containerCLSID)
{
   CollectionIndexType cnt;

   // create some Items and give them names
   CComPtr<TIItem> pss0,pss1,pss2,pss3,pss4,pss5,pss6;
   TRY_TEST( pss0.CoCreateInstance( itemCLSID ) , S_OK );
   TRY_TEST( pss1.CoCreateInstance( itemCLSID ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( itemCLSID ) , S_OK );
   TRY_TEST( pss3.CoCreateInstance( itemCLSID ) , S_OK );
   TRY_TEST( pss4.CoCreateInstance( itemCLSID ) , S_OK );
   TRY_TEST( pss5.CoCreateInstance( itemCLSID ) , S_OK );
   TRY_TEST( pss6.CoCreateInstance( itemCLSID ) , S_OK );

   TRY_TEST( pss0->put_Name(CComBSTR("Item 0")) , S_OK );
   TRY_TEST( pss1->put_Name(CComBSTR("Item 1")) , S_OK );
   TRY_TEST( pss2->put_Name(CComBSTR("Item 2")) , S_OK );
   TRY_TEST( pss3->put_Name(CComBSTR("Item 3")) , S_OK );
   TRY_TEST( pss4->put_Name(CComBSTR("Item 4")) , S_OK );
   TRY_TEST( pss5->put_Name(CComBSTR("Item 5")) , S_OK );
   TRY_TEST( pss6->put_Name(CComBSTR("Item 6")) , S_OK );

   // create the container
   CComPtr<TIContainer> pcnt1, pcnt2;
   TRY_TEST( pcnt1.CoCreateInstance( containerCLSID ) , S_OK );

   // set up the listener for the container
   DWORD dwCookie;
   CComQIPtr<TEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pcnt1,punk,*pEventDSPID,&dwCookie),S_OK);

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
   TRY_TEST( pcnt1->Add(pss2) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 4);
   TRY_TEST( pcnt1->Add(pss4) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);
   TRY_TEST( pcnt1->Add(pss5) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);
   TRY_TEST( pcnt1->Add(pss6) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 7);

   // set will be in sorted order
   CComPtr<TIItem> pss0t, pss1t, pss2t,pss3t,pss4t, pss5t, pss6t;
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

   pss3t.Release();
   TRY_TEST( pcnt1->Find(CComBSTR("Item 3"),&pss3t) , S_OK );
   TRY_TEST(pss3t.IsEqualObject(pss3), true);
   
   CComBSTR nm, nmt("Item 6");
   TRY_TEST( pcnt1->RemoveByIndex(6,&nm) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST(nm, nmt);
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);

   TRY_TEST( pcnt1->RemoveByName(CComBSTR("Item 0")) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);

   // check some bounds
   TRY_TEST( pcnt1->RemoveByIndex(-1,&nm) , E_INVALIDARG );
   TRY_TEST( pcnt1->RemoveByIndex(5,&nm) , E_INVALIDARG );
   TRY_TEST( pcnt1->RemoveByName(CComBSTR("Bogus")) , E_INVALIDARG );
   pss0t.Release();
   TRY_TEST( pcnt1->get_Item(-1,&pss0t) , E_INVALIDARG );
   TRY_TEST( pcnt1->get_Item( 5,&pss0t) , E_INVALIDARG );

   // check add duplicate
   CComPtr<TIItem> pss2a;
   TRY_TEST( pss2a.CoCreateInstance( itemCLSID ) , S_OK );
   TRY_TEST( pss2a->put_Name(CComBSTR("Item 2")) , S_OK );
   TRY_TEST( pcnt1->Add(pss2a) , WCC_E_NAME_ALREADY_EXISTS );

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
      CComPtr<TIItem> isegi;
      TRY_TEST( SUCCEEDED( penum->Next(1, &isegi, &fetched) ), TRUE);
      if (fetched)
         cnt++;
   }
   TRY_TEST(cnt, 5);

   TRY_TEST( pcnt2->Clear() , S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 0);

   // stop listening
   TRY_TEST(AtlUnadvise(pcnt1,*pEventDSPID,dwCookie),S_OK);

   return S_OK;
}

};



template <class TIItem, const CLSID* pItemCLSID,  class TIContainer, 
          const CLSID* pContainerCLSID, class TListen, class TEvents, 
          const UUID* pEventDSPID, class TIEnum>
class LongSetContainerTester
{
public:
static HRESULT TestContainer(TListen* pMe)
{
   long cnt;

   // create some Items and give them names
   CComPtr<TIItem> pss0,pss1,pss2,pss3,pss4,pss5,pss6;
   TRY_TEST( pss0.CoCreateInstance( *pItemCLSID ) , S_OK );
   TRY_TEST( pss1.CoCreateInstance( *pItemCLSID ) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( *pItemCLSID ) , S_OK );
   TRY_TEST( pss3.CoCreateInstance( *pItemCLSID ) , S_OK );
   TRY_TEST( pss4.CoCreateInstance( *pItemCLSID ) , S_OK );
   TRY_TEST( pss5.CoCreateInstance(*pItemCLSID ) , S_OK );
   TRY_TEST( pss6.CoCreateInstance(*pItemCLSID ) , S_OK );

   TRY_TEST( pss0->put_ID(100) , S_OK );
   TRY_TEST( pss1->put_ID(101) , S_OK );
   TRY_TEST( pss2->put_ID(102) , S_OK );
   TRY_TEST( pss3->put_ID(103) , S_OK );
   TRY_TEST( pss4->put_ID(104) , S_OK );
   TRY_TEST( pss5->put_ID(105) , S_OK );
   TRY_TEST( pss6->put_ID(106) , S_OK );

   // create the container
   CComPtr<TIContainer> pcnt1, pcnt2;
   TRY_TEST( pcnt1.CoCreateInstance( *pContainerCLSID ) , S_OK );

   // set up the listener for the container
   DWORD dwCookie;
   CComQIPtr<TEvents> events(pMe);
   CComPtr<IUnknown> punk(events);
   TRY_TEST(AtlAdvise(pcnt1,punk,*pEventDSPID,&dwCookie),S_OK);

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
   TRY_TEST( pcnt1->Add(pss2) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 4);
   TRY_TEST( pcnt1->Add(pss4) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);
   TRY_TEST( pcnt1->Add(pss5) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);
   TRY_TEST( pcnt1->Add(pss6) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 7);

   // set will be in sorted order
   CComPtr<TIItem> pss0t, pss1t, pss2t,pss3t,pss4t, pss5t, pss6t;
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

   pss3t.Release();
   TRY_TEST( pcnt1->Find(103,&pss3t) , S_OK );
   TRY_TEST(pss3t.IsEqualObject(pss3), true);
   
   long nm, nmt(106);
   TRY_TEST( pcnt1->RemoveByIndex(6,&nm) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST(nm, nmt);
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);

   TRY_TEST( pcnt1->RemoveByID(100) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);

   // check some bounds
   TRY_TEST( pcnt1->RemoveByIndex(-1,&nm) , E_INVALIDARG );
   TRY_TEST( pcnt1->RemoveByIndex(5,&nm) , E_INVALIDARG );
   TRY_TEST( pcnt1->RemoveByID(200) , E_FAIL);
   pss0t.Release();
   TRY_TEST( pcnt1->get_Item(-1,&pss0t) , E_INVALIDARG );
   TRY_TEST( pcnt1->get_Item( 5,&pss0t) , E_INVALIDARG );

   // check add duplicate
   CComPtr<TIItem> pss2a;
   TRY_TEST( pss2a.CoCreateInstance( *pItemCLSID ) , S_OK );
   TRY_TEST( pss2a->put_ID(102) , S_OK );
   TRY_TEST( pcnt1->Add(pss2a) , WCC_E_NAME_ALREADY_EXISTS );

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
      CComPtr<TIItem> isegi;
      TRY_TEST( SUCCEEDED( penum->Next(1, &isegi, &fetched) ), TRUE);
      if (fetched)
         cnt++;
   }
   TRY_TEST(cnt, 5);

   TRY_TEST( pcnt2->Clear() , S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 0);

   // stop listening
   TRY_TEST(AtlUnadvise(pcnt1,*pEventDSPID,dwCookie),S_OK);


   return S_OK;
}

};