///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
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

// TestUnitModeController.cpp: implementation of the CTestUnitModeController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestUnitModeController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestUnitModeController::CTestUnitModeController()
{

}

CTestUnitModeController::~CTestUnitModeController()
{

}

void CTestUnitModeController::Test()
{
   CComPtr<IUnitModeController> umc;
   TRY_TEST( umc.CoCreateInstance( CLSID_UnitModeController ), S_OK );

//   umc->ShowSelectionDialog();
//   umc->ShowSelectionDialog();
//   umc->ShowSelectionDialogEx(CComBSTR("c:\\Program Files\\Washington State Department of Transportation\\PGSuper\\PGSuper.chm"),106);

   // Note: These tests don't check to see if the OnUnitModeChanged event fires
   TRY_TEST( umc->put_UnitMode( umSI ), S_OK );
   TRY_TEST( umc->put_UnitMode( umUS ), S_OK );
   UnitModeType um;
   TRY_TEST( umc->get_UnitMode(nullptr), E_POINTER);
   TRY_TEST( umc->get_UnitMode(&um), S_OK);
   TRY_TEST( um, umUS );

   // ****************************************************
   // * Test ISupportErrorInfo
   // ****************************************************
   CComQIPtr<ISupportErrorInfo>  pSEI(umc);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IUnitModeController ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
