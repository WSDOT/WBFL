///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

// Stage.cpp : Implementation of CStage
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Stage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStage

void CStage::Init(CComBSTR bstrName,CComBSTR bstrDesc)
{
   m_bstrName = bstrName;
   m_bstrDescription = bstrDesc;
}

STDMETHODIMP CStage::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStage,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStage::Clone(IStage* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CStage>* pClone;
   CComObject<CStage>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->Init(m_bstrName,m_bstrDescription);

   return S_OK;
}

HRESULT CStage::PutDescription(CStage* pThis,CComBSTR bstrDesc)
{
   CHECK_IN(bstrDesc.m_str);

   if ( pThis->m_bstrDescription == bstrDesc )
      return S_OK;

   pThis->m_bstrDescription = bstrDesc;
   pThis->Fire_OnDescriptionChanged(pThis);
	return S_OK;
}

STDMETHODIMP CStage::get_Name(BSTR *pVal)
{
   CHECK_RETSTRING(pVal);

   *pVal = m_bstrName.Copy();
	return S_OK;
}

STDMETHODIMP CStage::put_Name(BSTR bstrName)
{
   CHECK_IN(bstrName);

   if ( bstrName == CComBSTR("") )
      return E_INVALIDARG;

   if ( m_bstrName == bstrName )
      return S_OK;

   // Check to see if this name is already being used
   CComPtr<IStageCollection> stages;

   m_pBridge->get_Stages(&stages);
   CComPtr<IStage> sameStage;
   stages->Find(bstrName,&sameStage);
   if ( sameStage != NULL )
   {
      // A stage with this name already exists
      return Error(IDS_E_DUPLICATENAME,IID_IStage,GB_E_DUPLICATENAME);
   }

   CComBSTR bstrOldName = m_bstrName;

   m_bstrName = bstrName;
   Fire_OnNameChanged(bstrOldName,this);
	return S_OK;
}

STDMETHODIMP CStage::get_Description(BSTR *pVal)
{
   CHECK_RETSTRING(pVal);

   *pVal = m_bstrDescription.Copy();
	return S_OK;
}

STDMETHODIMP CStage::put_Description(BSTR bstrDesc)
{
   CHECK_IN(bstrDesc);

   if ( m_bstrDescription == bstrDesc )
      return S_OK;

   m_bstrDescription = bstrDesc;
   Fire_OnDescriptionChanged(this);

	return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CStage::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("Stage"));

   load->get_Property(CComBSTR("Name"),&var);
   m_bstrName = var.bstrVal;
   var.Clear();

   load->get_Property(CComBSTR("Description"),&var);
   m_bstrDescription = var.bstrVal;
   var.Clear();


   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CStage::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("Stage"),1.0);
   save->put_Property(CComBSTR("Name"),CComVariant(m_bstrName));
   save->put_Property(CComBSTR("Description"),CComVariant(m_bstrDescription));
   save->EndUnit();

   return S_OK;
}
