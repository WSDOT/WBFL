///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <System\SysLib.h>
#include <System\ComCatMgr.h>

using namespace WBFL::System;

HRESULT ComCatMgr::CreateCategory(OLECHAR* lpszDesc,const CATID& catid)
{
   // Create the standard COM Category Manager
   ICatRegister* pICatReg = nullptr;
   HRESULT hr = ::CoCreateInstance( CLSID_StdComponentCategoriesMgr,
                                    nullptr,
                                    CLSCTX_ALL,
                                    IID_ICatRegister,
                                    (void**)&pICatReg );
   if ( FAILED(hr) )
      return hr;

   // Fill in CATEGORYINFO struct
   CATEGORYINFO CatInfo;
   CatInfo.catid = catid;
   CatInfo.lcid = LOCALE_SYSTEM_DEFAULT;
   _tcscpy_s(CatInfo.szDescription,lpszDesc);

   // Array of categories
   const int nID = 1;
   CATID ID[nID];
   ID[0] = catid;

   // Register the category
   hr = pICatReg->RegisterCategories(1,&CatInfo);
   pICatReg->Release();
   
   return hr;
}

HRESULT ComCatMgr::RemoveCategory(const CATID& catid,bool bLeaveIfUsed)
{
   // Create the standard COM Category Manager
   ICatRegister* pICatReg = nullptr;
   HRESULT hr = ::CoCreateInstance( CLSID_StdComponentCategoriesMgr,
                                    nullptr,
                                    CLSCTX_ALL,
                                    IID_ICatRegister,
                                    (void**)&pICatReg );
   if ( FAILED(hr) )
      return hr;

   const int nID = 1;
   CATID ID[nID];
   ID[0] = catid;

   ICatInformation* pICatInfo = nullptr;
   hr = pICatReg->QueryInterface( IID_ICatInformation, (void**)&pICatInfo );

   IEnumCLSID* pIEnumCLSID = nullptr;
   hr = pICatInfo->EnumClassesOfCategories( nID, ID, 0, nullptr, &pIEnumCLSID );

   CLSID clsid;
   hr = pIEnumCLSID->Next(1,&clsid,nullptr);
   if ( hr != S_FALSE && bLeaveIfUsed )
   {
      // Do nothing
   }
   else
   {
      pICatReg->UnRegisterCategories(nID,ID);
   }

   pIEnumCLSID->Release();
   pICatInfo->Release();
   pICatReg->Release();
   
   return S_OK;
}

HRESULT ComCatMgr::RegWithCategory(const CLSID& clsid,const CATID& catid,bool bReg)
{
   HRESULT hr = S_OK;
   ICatRegister* pICatReg = nullptr;
   hr = ::CoCreateInstance( CLSID_StdComponentCategoriesMgr,
                            nullptr,
                            CLSCTX_ALL,
                            IID_ICatRegister,
                            (void**)&pICatReg );

   if ( FAILED(hr) )
      return hr;


   const int nID = 1;
   CATID ID[nID];
   ID[0] = catid;

   if ( bReg )
   {
      hr = pICatReg->RegisterClassImplCategories( clsid, 1, ID );
      if ( FAILED(hr) )
         return hr;
   }
   else
   {
      hr = pICatReg->UnRegisterClassImplCategories( clsid, 1, ID );
      if ( FAILED(hr) )
         return hr;
   }

   pICatReg->Release();

   return S_OK;
}
