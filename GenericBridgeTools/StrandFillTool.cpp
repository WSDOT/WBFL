///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2017  Washington State Department of Transportation
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

// StrandFillTool.cpp : Implementation of CStrandFillTool
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "StrandFillTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrandFillTool

STDMETHODIMP CStrandFillTool::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStrandFillTool
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CStrandFillTool::FinalConstruct()
{
   return S_OK;
}

void CStrandFillTool::FinalRelease()
{
}

/////////////////////////////////////////////////////////////
// IStrandFillTool
STDMETHODIMP CStrandFillTool::ComputeHarpedStrandMaxFill(IStrandGridFiller* pEndGridFiller,IStrandGridFiller* pHPGridFiller,StrandIndexType* pMaxStrandCount,IIndexArray** ppStrandFill)
{
   CHECK_IN(pEndGridFiller);
   CHECK_IN(pHPGridFiller);
   CHECK_RETVAL(pMaxStrandCount);
   CHECK_RETOBJ(ppStrandFill);

   CComPtr<IIndexArray> hp_fill, end_fill;
   pEndGridFiller->GetMaxStrandFill(&end_fill);
   pHPGridFiller->GetMaxStrandFill(&hp_fill);

   CollectionIndexType num_hp, num_end;
   hp_fill->get_Count(&num_hp);
   end_fill->get_Count(&num_end);
   if (num_hp != num_end)
   {
      ATLASSERT(false);
      return E_FAIL;
   }

   CComPtr<IIndexArray> array;
   array.CoCreateInstance(CLSID_IndexArray);
   array->Reserve(num_hp);
   *pMaxStrandCount = 0;
   for ( CollectionIndexType i = 0; i < num_hp; i++ )
   {
      StrandIndexType hp,end;
      hp_fill->get_Item(i,&hp);
      end_fill->get_Item(i,&end);
      hp = max(hp,end);
      array->Add(hp);
      *pMaxStrandCount += StrandIndexType(hp);
   }

   return array.CopyTo(ppStrandFill);
}
