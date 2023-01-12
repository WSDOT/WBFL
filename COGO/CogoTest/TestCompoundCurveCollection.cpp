///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestCompoundCurveCollection.cpp: implementation of the CTestCompoundCurveCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCompoundCurveCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCompoundCurveCollection::CTestCompoundCurveCollection()
{

}

void CTestCompoundCurveCollection::Test()
{
   CComPtr<ICompoundCurveCollection> pColl;
   TRY_TEST(pColl.CoCreateInstance( CLSID_CompoundCurveCollection ), S_OK);

   CollectionIndexType count;
   TRY_TEST(pColl->get_Count(nullptr),E_POINTER);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(0,1000);
   pi->Move(700,1000);
   pft->Move(1000,700);

   CComPtr<ICompoundCurveFactory> factory;
   TRY_TEST(pColl->get_Factory(nullptr),E_POINTER);
   TRY_TEST(pColl->get_Factory(&factory),S_OK);
   TRY_TEST( factory != nullptr, true );
   TRY_TEST(pColl->putref_Factory(nullptr),E_INVALIDARG);
   TRY_TEST(pColl->putref_Factory(factory),S_OK);

   //
   // Test Add method
   //
   TRY_TEST(pColl->Add(1,nullptr,pi,pft,500,100,200,nullptr),  E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,nullptr,pft,500,100,200,nullptr), E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,pi,nullptr,500,100,200,nullptr),  E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,pi,pft,-500,100,200,nullptr),  E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,pi,pft,0,100,200,nullptr),     E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,pi,pft,500,-100,200,nullptr),  E_INVALIDARG);
   TRY_TEST(pColl->Add(1,pbt,pi,pft,500,100,-200,nullptr),  E_INVALIDARG);

   TRY_TEST(pColl->Add(1,pbt,pi,pft,500,100,200,nullptr),S_OK);
   TRY_TEST(pColl->Add(1,pbt,pi,pft,500,100,200,nullptr),COGO_E_COMPOUNDCURVEALREADYDEFINED);
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(pColl->get_Item(1,&hc),S_OK);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,1);

   //
   // Test AddEx method
   //
   TRY_TEST(pColl->AddEx(0,nullptr),E_INVALIDARG);


   // Test Item property
   hc.Release();
   TRY_TEST(pColl->get_Item(-1,&hc),COGO_E_COMPOUNDCURVENOTFOUND);
   TRY_TEST(pColl->get_Item(1,nullptr),E_POINTER);
   TRY_TEST(pColl->get_Item(1,&hc),S_OK);

   //
   // Test Remove
   //
   TRY_TEST(pColl->Remove(-1),COGO_E_COMPOUNDCURVENOTFOUND);
   TRY_TEST(pColl->Remove(1),S_OK);

   //
   // Test Clear
   //
   pColl->Add(1,pbt,pi,pft,500,100,200,nullptr);
   pColl->get_Count(&count);
   TRY_TEST(count,1);
   TRY_TEST( pColl->Clear(), S_OK );
   pColl->get_Count(&count);
   TRY_TEST(count,0);

   //
   // Test put_Item
   //
   TRY_TEST(pColl->AddEx(1,hc),S_OK);

   TRY_TEST(pColl->putref_Item(1,nullptr),E_INVALIDARG);
   TRY_TEST(pColl->putref_Item(-1,hc),COGO_E_COMPOUNDCURVENOTFOUND);
   TRY_TEST(pColl->putref_Item(1,hc),S_OK);

   //
   // Test FindID
   //
   CogoObjectID id;
   TRY_TEST(pColl->FindID(nullptr,&id),E_INVALIDARG);
   TRY_TEST(pColl->FindID(hc,nullptr),E_POINTER);
   TRY_TEST(pColl->FindID(hc,&id),S_OK);
   TRY_TEST(id,1);

   //
   // Test ID
   //
   pColl->Clear();
   pColl->Add(1,pbt,pi,pft,500,100,200,nullptr);
   pColl->Add(2,pbt,pi,pft,500,100,200,nullptr);
   pColl->Add(3,pbt,pi,pft,500,100,200,nullptr);
   pColl->Add(4,pbt,pi,pft,500,100,200,nullptr);

   TRY_TEST(pColl->ID(-1,&id),E_INVALIDARG);
   TRY_TEST(pColl->ID(500,&id),E_INVALIDARG);
   TRY_TEST(pColl->ID(3,nullptr),E_POINTER);
   TRY_TEST(pColl->ID(3,&id),S_OK);
   TRY_TEST(id,4);
   

   //
   // Test _Enum
   //
   CComPtr<ICompoundCurve> hcurve[4];
   pColl->Clear();
   pColl->Add(1,pbt,pi,pft,500,100,200,nullptr);
   pColl->Add(2,pbt,pi,pft,500,100,200,nullptr);
   pColl->Add(3,pbt,pi,pft,500,100,200,nullptr);
   pColl->Add(4,pbt,pi,pft,500,100,200,nullptr);
   pColl->get_Item(1,&hcurve[0]);
   pColl->get_Item(2,&hcurve[1]);
   pColl->get_Item(3,&hcurve[2]);
   pColl->get_Item(4,&hcurve[3]);
   CComPtr<IEnumIDs> pEnum;
   TRY_TEST(pColl->get__EnumIDs(nullptr), E_POINTER );
   TRY_TEST( pColl->get__EnumIDs(&pEnum), S_OK );

   ULONG fetched;
   CogoObjectID target_id = 1;
   while( pEnum->Next(1,&id,&fetched ) == S_OK )
   {
      TRY_TEST(id,target_id++);
   }
   
   //
   // Test _EnumCompoundCurves
   //
   hcurve[0].Release();
   hcurve[1].Release();
   hcurve[2].Release();
   hcurve[3].Release();
   pColl->Clear();
   pColl->Add(1,pbt,pi,pft,500,100,200,nullptr);
   pColl->Add(2,pbt,pi,pft,500,100,200,nullptr);
   pColl->Add(3,pbt,pi,pft,500,100,200,nullptr);
   pColl->Add(4,pbt,pi,pft,500,100,200,nullptr);
   pColl->get_Item(1,&hcurve[0]);
   pColl->get_Item(2,&hcurve[1]);
   pColl->get_Item(3,&hcurve[2]);
   pColl->get_Item(4,&hcurve[3]);
   CComPtr<IEnumCompoundCurves> pEnumCompoundCurves;
   TRY_TEST(pColl->get__EnumCompoundCurves(nullptr), E_POINTER );
   TRY_TEST( pColl->get__EnumCompoundCurves(&pEnumCompoundCurves), S_OK );

   for ( long i = 0; i < 4; i++ )
   {
      CComPtr<ICompoundCurve> CompoundCurve;
      pEnumCompoundCurves->Next(1,&CompoundCurve,&fetched);
      TRY_TEST(CompoundCurve.IsEqualObject(hcurve[i]),true);
   }

   //
   // Test ISupportErrorInfo
   //
   CComQIPtr<ISupportErrorInfo> eInfo(pColl);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICompoundCurveCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_CompoundCurveCollection,IID_ICompoundCurveCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CompoundCurveCollection,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
