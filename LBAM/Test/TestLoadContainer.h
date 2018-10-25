///////////////////////////////////////////////////////////////////////
// LBAM Test - Test driver for LBAM analysis library
// Copyright © 1999-2010  Washington State Department of Transportation
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


template <class T , const CLSID* pCLSID, class TItem,   class TIContainer, 
          const CLSID* pContainerCLSID, class TListen, class TEvents, 
          const UUID* pEventDSPID, class TIEnum>
class LoadContainerTester
{
public:
static HRESULT TestContainer(TListen* pMe)
{
   CollectionIndexType cnt;

   // create some Items and give them names
   CComPtr<T> pss0,pss1,pss2,pss3,pss4,pss5,pss6;
   TRY_TEST( pss0.CoCreateInstance( *pCLSID ) , S_OK );
   TRY_TEST( pss0->put_MemberID(0) , S_OK );
   TRY_TEST( pss1.CoCreateInstance( *pCLSID ) , S_OK );
   TRY_TEST( pss1->put_MemberID(1) , S_OK );
   TRY_TEST( pss2.CoCreateInstance( *pCLSID ) , S_OK );
   TRY_TEST( pss2->put_MemberID(2) , S_OK );
   TRY_TEST( pss3.CoCreateInstance( *pCLSID ) , S_OK );
   TRY_TEST( pss3->put_MemberID(3) , S_OK );
   TRY_TEST( pss4.CoCreateInstance( *pCLSID ) , S_OK );
   TRY_TEST( pss4->put_MemberID(4) , S_OK );
   TRY_TEST( pss5.CoCreateInstance(*pCLSID ) , S_OK );
   TRY_TEST( pss5->put_MemberID(5) , S_OK );
   TRY_TEST( pss6.CoCreateInstance(*pCLSID ) , S_OK );
   TRY_TEST( pss6->put_MemberID(6) , S_OK );

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

   CComPtr<TItem> pItem0,pItem1,pItem2,pItem3,pItem4,pItem5,pItem6;
   TRY_TEST( pcnt1->Add(CComBSTR("Stage1"), CComBSTR("LoadGroup 1"), pss0, &pItem0) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 1);
   TRY_TEST( pcnt1->Add(CComBSTR("Stage1"), CComBSTR("LoadGroup 1"), pss1, &pItem1) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 2);
   TRY_TEST( pcnt1->Add(CComBSTR("Stage1"), CComBSTR("LoadGroup 1"), pss2, &pItem2) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 3);
   TRY_TEST( pcnt1->Add(CComBSTR("Stage2"), CComBSTR("LoadGroup 1"), pss3, &pItem3) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 4);
   TRY_TEST( pcnt1->Add(CComBSTR("Stage2"), CComBSTR("LoadGroup 2"), pss4, &pItem4) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);
   TRY_TEST( pcnt1->Add(CComBSTR("Stage3"), CComBSTR("LoadGroup 1"), pss5, &pItem5) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);
   TRY_TEST( pcnt1->Add(CComBSTR("Stage1"), CComBSTR("LoadGroup 2"), pss6, &pItem6) , S_OK );
   TEST_CONTAINER_FIRED();
   TRY_TEST( pcnt1->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 7);


   // set will be in order as input
   CComPtr<TItem> pss0t, pss1t, pss2t,pss3t,pss4t, pss5t, pss6t;
   CComPtr<T>     pss0c, pss1c, pss2c,pss3c,pss4c, pss5c, pss6c;
   MemberIDType           id[7];
   TRY_TEST( pcnt1->get_Item(0,&pss0t) , S_OK );
   TRY_TEST( pss0t->get_Load(&pss0c), S_OK );
   TRY_TEST(pss0c.IsEqualObject(pss0), true);
   TRY_TEST(pss0t->get_ID(&id[0]), S_OK);
   TRY_TEST( pcnt1->get_Item(1,&pss1t) , S_OK );
   TRY_TEST( pss1t->get_Load(&pss1c), S_OK );
   TRY_TEST(pss1c.IsEqualObject(pss1), true);
   TRY_TEST(pss1t->get_ID(&id[1]), S_OK);
   TRY_TEST( pcnt1->get_Item(2,&pss2t) , S_OK );
   TRY_TEST( pss2t->get_Load(&pss2c), S_OK );
   TRY_TEST(pss2c.IsEqualObject(pss2), true);
   TRY_TEST(pss2t->get_ID(&id[2]), S_OK);
   TRY_TEST( pcnt1->get_Item(3,&pss3t) , S_OK );
   TRY_TEST( pss3t->get_Load(&pss3c), S_OK );
   TRY_TEST(pss3c.IsEqualObject(pss3), true);
   TRY_TEST(pss3t->get_ID(&id[3]), S_OK);
   TRY_TEST( pcnt1->get_Item(4,&pss4t) , S_OK );
   TRY_TEST( pss4t->get_Load(&pss4c), S_OK );
   TRY_TEST(pss4c.IsEqualObject(pss4), true);
   TRY_TEST(pss4t->get_ID(&id[4]), S_OK);
   TRY_TEST( pcnt1->get_Item(5,&pss5t) , S_OK );
   TRY_TEST( pss5t->get_Load(&pss5c), S_OK );
   TRY_TEST(pss5c.IsEqualObject(pss5), true);
   TRY_TEST(pss5t->get_ID(&id[5]), S_OK);
   TRY_TEST( pcnt1->get_Item(6,&pss6t) , S_OK );
   TRY_TEST( pss6t->get_Load(&pss6c), S_OK );
   TRY_TEST(pss6c.IsEqualObject(pss6), true);
   TRY_TEST(pss6t->get_ID(&id[6]), S_OK);

   // find
   CComPtr<TItem> pss3u, pss5u;
   CComPtr<T>     pss3d, pss5d;
   TRY_TEST( pcnt1->Find(id[3],&pss3u) , S_OK );
   TRY_TEST( pss3u->get_Load(&pss3d), S_OK );
   TRY_TEST(pss3d.IsEqualObject(pss3), true);
   TRY_TEST( pcnt1->Find(id[5],&pss5u) , S_OK );
   TRY_TEST( pss5u->get_Load(&pss5d), S_OK );
   TRY_TEST(pss5d.IsEqualObject(pss5), true);

   // get_Load
   CComPtr<T>     pss3e, pss6e;
   TRY_TEST( pcnt1->get_Load(id[3],&pss3e) , S_OK );
   TRY_TEST(pss3e.IsEqualObject(pss3), true);
   TRY_TEST( pcnt1->get_Load(id[6],&pss6e) , S_OK );
   TRY_TEST(pss6e.IsEqualObject(pss6), true);

   TRY_TEST( pcnt1->putref_Load(id[6],pss5) , S_OK );
   pss6e.Release();
   TRY_TEST( pcnt1->get_Load(id[6],&pss6e) , S_OK );
   TRY_TEST(pss6e.IsEqualObject(pss5), true);

   // clone
   TRY_TEST( pcnt1->Clone(&pcnt2) , S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 7);

   // removes
   TRY_TEST( pcnt2->RemoveByID(id[6]) , S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 6);

   TRY_TEST( pcnt2->RemoveByIndex(0), S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);

   TRY_TEST( pcnt2->RemoveStage(CComBSTR("Stage3")) , S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 4);

   TRY_TEST( pcnt2->RemoveStage(CComBSTR("bogus Stage")) , S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 4);

   TRY_TEST( pcnt1->RemoveByID(id[6]) , S_OK );

   // enumerators
   CComPtr<TIEnum> penum;
   pcnt1->get__EnumElements(&penum);//, S_OK);
   cnt = 0;
   ULONG fetched=1;
   while(fetched==1)
   {
      CComPtr<TItem> isegi;
      TRY_TEST( SUCCEEDED( penum->Next(1, &isegi, &fetched) ), TRUE);
      if (fetched)
         cnt++;
   }
   TRY_TEST(cnt, 6);

   // filters
   CComPtr<TIContainer> pcnt3, pcnt4, pcnt5, pcnt6;
   TRY_TEST(pcnt1->FilterByStageGroup(CComBSTR("Stage1"),CComBSTR("LoadGroup 1"), &pcnt3), S_OK);
   TRY_TEST( pcnt3->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 3);

   TRY_TEST(pcnt1->FilterByStageGroup(CComBSTR("Stage1"),CComBSTR("*"), &pcnt4), S_OK);
   TRY_TEST( pcnt4->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 3);

   TRY_TEST(pcnt1->FilterByStageGroup(CComBSTR("*"),CComBSTR("LoadGroup 1"), &pcnt5), S_OK);
   TRY_TEST( pcnt5->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 5);

   TRY_TEST(pcnt1->FilterByStageGroup(CComBSTR("bogus Stage1"),CComBSTR("LoadGroup 1"), &pcnt6), S_OK);
   TRY_TEST( pcnt6, NULL);

   TRY_TEST( pcnt2->Clear() , S_OK );
   TRY_TEST( pcnt2->get_Count(&cnt) , S_OK );
   TRY_TEST(cnt, 0);

   // test persistence by saving and retrieving data and comparing raw xml
   HRESULT hr;
   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestLoadContainer"), 1.0);

      // get interface pointer to Save
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pcnt1.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }

   {
      // make a new member to work with
      CComPtr<TIContainer> pcnt2;
      TRY_TEST(pcnt2.CoCreateInstance( *pContainerCLSID ), S_OK );

      // now let's load and save to another file
      {
         CComPtr<IStructuredLoad2> psl;
         TRY_TEST( psl.CoCreateInstance( CLSID_StructuredLoad2 ), S_OK );
         TRY_TEST( psl->Open( CComBSTR("Test.xml")), S_OK );

         hr = psl->BeginUnit(CComBSTR("TestLoadContainer"));

         IStructuredStorage2* piss2=NULL;
         TRY_TEST( pcnt2.QueryInterface(&piss2), S_OK);

         // Load 
         TRY_TEST( piss2->Load(psl), S_OK );

         piss2->Release();

         VARIANT_BOOL end;
         hr = psl->EndUnit(&end);

         TRY_TEST( psl->Close(), S_OK );

         // now save to a different file so we can compare files
         CComPtr<IStructuredSave2> pss2;
         TRY_TEST( pss2.CoCreateInstance( CLSID_StructuredSave2 ), S_OK );
         TRY_TEST( pss2->Open( CComBSTR("Test2.xml")), S_OK );

         // save our loaded version
         hr = pss2->BeginUnit(CComBSTR("TestLoadContainer"), 1.0);
         TRY_TEST( piss2->Save(pss2), S_OK );
         hr = pss2->EndUnit();
         TRY_TEST( pss2->Close(), S_OK );
      }
   }

   // compare two files by comparing strings. note that xml parser based files have only two lines
   // the first line is the xml processing instruction and the second line is all of the data
   // for this simple case we can simply compare the two data strings. For huge files, we
   // might have to resort to less memory intensive methods.
   try
   {
      std::_tstring x1;
      std::_tifstream if1("Test.xml");
      std::getline(if1, x1);
      std::getline(if1, x1); // second line is the data

      std::_tstring x2;
      std::_tifstream if2("Test2.xml");
      std::getline(if2, x2);
      std::getline(if2, x2);

      TRY_TEST( x1, x2 );

   }
   catch(...)
   {
      ATLASSERT(0); // big problems
      TRY_TEST(0,1); 
   }

   // create a clone and save it
   CComPtr<TIContainer> pclone;
   TRY_TEST(pcnt1->Clone(&pclone), S_OK);

   {
      CComPtr<IStructuredSave2> pss;
      TRY_TEST( pss.CoCreateInstance(CLSID_StructuredSave2), S_OK );
      TRY_TEST( pss->Open( CComBSTR("Test.xml")), S_OK );

      hr = pss->BeginUnit(CComBSTR("TestLoadContainer"), 1.0);

      // get interface pointer to Save
      CComPtr<IStructuredStorage2> piss;
      TRY_TEST( pclone.QueryInterface(&piss), S_OK);

      // save
      piss->Save( pss );

      hr = pss->EndUnit();
      TRY_TEST( pss->Close(), S_OK );
   }


   // compare clone's file with original
   try
   {
      std::_tstring x1;
      std::_tifstream if1("Test.xml");
      std::getline(if1, x1);
      std::getline(if1, x1); // second line is the data

      std::_tstring x2;
      std::_tifstream if2("Test2.xml");
      std::getline(if2, x2);
      std::getline(if2, x2);

      TRY_TEST( x1, x2 );

   }
   catch(...)
   {
      ATLASSERT(0); // big problems
      TRY_TEST(0,1); 
   }



   // stop listening
   TRY_TEST(AtlUnadvise(pcnt1,*pEventDSPID,dwCookie),S_OK);


   return S_OK;
}

};