///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
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

// UnitModeController.cpp : Implementation of CUnitModeController
#include "stdafx.h"
#include "WBFLUnitServer.h"
#include "UnitModeController.h"
#include "UnitsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CUnitModeController


STDMETHODIMP CUnitModeController::get_UnitMode(UnitModeType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_UnitMode;
	return S_OK;
}

STDMETHODIMP CUnitModeController::put_UnitMode(UnitModeType newVal)
{
   if ( newVal != m_UnitMode )
   {
      m_UnitMode = newVal;
      Fire_OnUnitModeChanged(m_UnitMode);
   }

	return S_OK;
}

STDMETHODIMP CUnitModeController::ShowSelectionDialog()
{
   CUnitsDialog dlg;
   dlg.SetUnitMode(m_UnitMode);
   if (dlg.DoModal() == IDOK)
   {
      put_UnitMode(dlg.GetUnitMode());
   }

	return S_OK;
}
