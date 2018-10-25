///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2015  Washington State Department of Transportation
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

// RebarSection.cpp : Implementation of CRebarSection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "RebarSection.h"
#include "RebarSectionItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebarSection
void CRebarSection::FinalRelease()
{
}

STDMETHODIMP CRebarSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRebarSection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CRebarSection::get__EnumRebarSectionItem(IEnumRebarSectionItem* *enumRSI)
{
   return get__EnumElements(enumRSI);
}

/////////////////////////////////////////////////////////////////
HRESULT CRebarSection::DoSaveItem(IStructuredSave2* save,IRebarSectionItem* item)
{
   CComQIPtr<IStructuredStorage2> ssRSI(item);
   return ssRSI->Save(save);
}

HRESULT CRebarSection::DoLoadItem(IStructuredLoad2* load,IRebarSectionItem* *ppItem)
{
   // Create a new span object
   CComObject<CRebarSectionItem>* pRSI;
   CComObject<CRebarSectionItem>::CreateInstance(&pRSI);
   CComPtr<IRebarSectionItem> newRSI = pRSI;

   CComQIPtr<IStructuredStorage2> ssRSI(newRSI);
   HRESULT hr = ssRSI->Load(load);
   if ( FAILED(hr) )
      return hr;

   (*ppItem) = newRSI;
   (*ppItem)->AddRef();

   return S_OK;
}
