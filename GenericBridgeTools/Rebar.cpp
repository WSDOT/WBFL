///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2011  Washington State Department of Transportation
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

// Rebar.cpp : Implementation of CRebar
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "Rebar.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebar
HRESULT CRebar::FinalConstruct()
{
   return S_OK;
}

void CRebar::FinalRelease()
{
}

STDMETHODIMP CRebar::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRebar,
      &IID_IMaterial,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CRebar::Clone(IMaterial** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CRebar>* pClone;
   CComObject<CRebar>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->Init(m_Name,m_E,m_Density,m_fpu,m_fpy,m_db,m_Ab);

   CComQIPtr<ISupportTransactions> supTxn(*clone);
   if ( supTxn )
      supTxn->putref_TransactionMgr(m_TxnMgr);

   return S_OK;
}

HRESULT CRebar::PutE(CRebar* pThis,Float64 E)
{
   pThis->m_E = E;
   pThis->Fire_OnMaterialChanged(pThis);
   return S_OK;
}

HRESULT CRebar::PutDensity(CRebar* pThis,Float64 w)
{
   pThis->m_Density = w;
   pThis->Fire_OnMaterialChanged(pThis);
   return S_OK;
}

HRESULT CRebar::PutName(CRebar* pThis,BSTR name)
{
   pThis->m_Name = name;
   pThis->Fire_OnMaterialChanged(pThis);
   return S_OK;
}

HRESULT CRebar::PutUltimateStrength(CRebar* pThis,Float64 fpu)
{
   pThis->m_fpu = fpu;
   pThis->Fire_OnMaterialChanged(pThis);
   return S_OK;
}

HRESULT CRebar::PutYieldStrength(CRebar* pThis,Float64 fpy)
{
   pThis->m_fpy = fpy;
   pThis->Fire_OnMaterialChanged(pThis);
   return S_OK;
}

HRESULT CRebar::PutNominalDiameter(CRebar* pThis,Float64 db)
{
   pThis->m_db = db;
   pThis->Fire_OnMaterialChanged(pThis);
   return S_OK;
}

HRESULT CRebar::PutNominalArea(CRebar* pThis,Float64 Ab)
{
   pThis->m_Ab = Ab;
   pThis->Fire_OnMaterialChanged(pThis);
   return S_OK;
}

STDMETHODIMP CRebar::Init(BSTR name,Float64 Es,Float64 density,Float64 fpu,Float64 fpy,Float64 db,Float64 Ab)
{
   m_Name    = CComBSTR(name);
   m_E       = Es;
   m_Density = density;
   m_fpu     = fpu;
   m_fpy     = fpy;
   m_db      = db;
   m_Ab      = Ab;
   return S_OK;
}

STDMETHODIMP CRebar::get_E(Float64* E)
{
   CHECK_RETVAL(E);
   (*E) = m_E;
   return S_OK;
}

STDMETHODIMP CRebar::put_E(Float64 E)
{
   if ( E <= 0.0 )
      return E_INVALIDARG;

   if ( IsEqual(m_E,E) )
      return S_OK;

   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CRebar,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditETxn;
      CComObject<CEditETxn>* pTxn;
      CComObject<CEditETxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("E"),&PutE,m_E,E);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutE(this,E);
   }

   return E_FAIL;
}

STDMETHODIMP CRebar::get_Density(Float64* w)
{
   CHECK_RETVAL(w);
   (*w) = m_Density;
   return S_OK;
}

STDMETHODIMP CRebar::put_Density(Float64 w)
{
   if ( IsEqual(m_Density,w) )
      return S_OK;

   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CRebar,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditDensityTxn;
      CComObject<CEditDensityTxn>* pTxn;
      CComObject<CEditDensityTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("E"),&PutDensity,m_Density,w);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutDensity(this,w);
   }

   return E_FAIL;
}

STDMETHODIMP CRebar::get_Name(BSTR* name)
{
   CHECK_RETSTRING(name);
   (*name) = m_Name.Copy();
   return S_OK;
}

STDMETHODIMP CRebar::put_Name(BSTR name)
{
   if ( CComBSTR(name) == m_Name )
      return S_OK;

   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CRebar,BSTR,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditNameTxn;
      CComObject<CEditNameTxn>* pTxn;
      CComObject<CEditNameTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Name"),&PutName,m_Name,name);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutName(this,name);
   }

   return E_FAIL;
}

STDMETHODIMP CRebar::get_UltimateStrength(Float64* fpu)
{
   CHECK_RETVAL(fpu);
   *fpu = m_fpu;
   return S_OK;
}

STDMETHODIMP CRebar::put_UltimateStrength(Float64 fpu)
{
   if ( IsEqual(m_fpu,fpu) )
      return S_OK;

   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CRebar,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditUltimateStrengthTxn;
      CComObject<CEditUltimateStrengthTxn>* pTxn;
      CComObject<CEditUltimateStrengthTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Ultimate Strength"),&PutUltimateStrength,m_fpu,fpu);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutUltimateStrength(this,fpu);
   }

   return E_FAIL;
}

STDMETHODIMP CRebar::get_YieldStrength(Float64* fpy)
{
   CHECK_RETVAL(fpy);
   *fpy = m_fpy;
   return S_OK;
}

STDMETHODIMP CRebar::put_YieldStrength(Float64 fpy)
{
   if ( IsEqual(m_fpy,fpy) )
      return S_OK;

   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CRebar,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditYieldStrengthTxn;
      CComObject<CEditYieldStrengthTxn>* pTxn;
      CComObject<CEditYieldStrengthTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Yield Strength"),&PutYieldStrength,m_fpy,fpy);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutYieldStrength(this,fpy);
   }

   return E_FAIL;
}

STDMETHODIMP CRebar::get_NominalDiameter(Float64* db)
{
   CHECK_RETVAL(db);
   *db = m_db;
   return S_OK;
}

STDMETHODIMP CRebar::put_NominalDiameter(Float64 db)
{
   if ( IsEqual(m_db,db) )
      return S_OK;

   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CRebar,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditNominalDiameterTxn;
      CComObject<CEditNominalDiameterTxn>* pTxn;
      CComObject<CEditNominalDiameterTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Nominal Diameter"),&PutNominalDiameter,m_db,db);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutNominalDiameter(this,db);
   }

   return E_FAIL;
}

STDMETHODIMP CRebar::get_NominalArea(Float64* Ab)
{
   CHECK_RETVAL(Ab);
   *Ab = m_Ab;
   return S_OK;
}

STDMETHODIMP CRebar::put_NominalArea(Float64 Ab)
{
   if ( IsEqual(m_Ab,Ab) )
      return S_OK;

   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CRebar,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditNominalAreaTxn;
      CComObject<CEditNominalAreaTxn>* pTxn;
      CComObject<CEditNominalAreaTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Nominal Area"),&PutNominalArea,m_Ab,Ab);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutNominalArea(this,Ab);
   }

   return E_FAIL;
}

////////////////////////////////////////////////////////////////////
// ISupportTransactions implementation
STDMETHODIMP CRebar::putref_TransactionMgr(ITransactionMgr* txnMgr)
{
   return ISupportTransactionsImpl::putref_TransactionMgr(txnMgr);
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CRebar::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("Rebar"));

   load->get_Property(CComBSTR("Name"),&var);
   m_Name = var.bstrVal;

   load->get_Property(CComBSTR("E"),&var);
   m_E = var.dblVal;

   load->get_Property(CComBSTR("Density"),&var);
   m_Density = var.dblVal;

   load->get_Property(CComBSTR("UltimateStrength"),&var);
   m_fpu = var.dblVal;

   load->get_Property(CComBSTR("YieldStrength"),&var);
   m_fpy = var.dblVal;

   load->get_Property(CComBSTR("NominalDiameter"),&var);
   m_db = var.dblVal;

   load->get_Property(CComBSTR("NominalArea"),&var);
   m_Ab = var.dblVal;

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CRebar::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("Rebar"),1.0);

   save->put_Property(CComBSTR("Name"),CComVariant(m_Name));
   save->put_Property(CComBSTR("E"),CComVariant(m_E));
   save->put_Property(CComBSTR("Density"),CComVariant(m_Density));
   save->put_Property(CComBSTR("UltimateStrength"),CComVariant(m_fpu));
   save->put_Property(CComBSTR("YieldStrength"),CComVariant(m_fpy));
   save->put_Property(CComBSTR("NominalDiameter"),CComVariant(m_db));
   save->put_Property(CComBSTR("NominalArea"),CComVariant(m_Ab));

   save->EndUnit();

   return S_OK;
}
