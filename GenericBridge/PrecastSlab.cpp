///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// PrecastSlab.cpp : Implementation of CPrecastSlab
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "PrecastSlab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrecastSlab
HRESULT CPrecastSlab::FinalConstruct()
{
   return IBridgeDeckImpl::Init();
}

void CPrecastSlab::FinalRelease()
{
}

STDMETHODIMP CPrecastSlab::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPrecastSlab,
      &IID_IBridgeDeck,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////
// IBridgeDeck implementation
STDMETHODIMP CPrecastSlab::get_StructuralDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_PanelDepth + m_CastDepth - m_SacrificialDepth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_GrossDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_PanelDepth + m_CastDepth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::putref_DeckBoundary(IDeckBoundary* deckBoundary)
{
   CHECK_IN(deckBoundary);
   m_pDeckBoundary = deckBoundary;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_DeckBoundary(IDeckBoundary** deckBoundary)
{
   CHECK_RETOBJ(deckBoundary);
   if ( m_pDeckBoundary )
   {
      (*deckBoundary) = m_pDeckBoundary;
      (*deckBoundary)->AddRef();
   }
   else
   {
      (*deckBoundary) = NULL;
   }

   return S_OK;
}


////////////////////////////////////////////////////////////////////////
// IPrecastSlab implementation
STDMETHODIMP CPrecastSlab::get_CastingStage(StageIndexType* pStageIdx)
{
   CHECK_RETVAL(pStageIdx);
   (*pStageIdx) = m_CastingStageIdx;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_CastingStage(StageIndexType stageIdx)
{
   if ( m_CastingStageIdx == stageIdx )
      return S_OK;

   m_CastingStageIdx = stageIdx;

   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_PanelDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_PanelDepth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_PanelDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_PanelDepth,depth) )
      return S_OK;

   m_PanelDepth = depth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_CastDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_CastDepth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_CastDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_CastDepth,depth) )
      return S_OK;

   m_CastDepth = depth;

   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_OverhangDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_OverhangDepth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_OverhangDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_OverhangDepth,depth) )
      return S_OK;

   m_OverhangDepth = depth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_SacrificialDepth(Float64* depth)
{
   CHECK_RETVAL(depth);
   *depth = m_SacrificialDepth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_SacrificialDepth(Float64 depth)
{
   if ( depth < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_SacrificialDepth,depth) )
      return S_OK;

   m_SacrificialDepth = depth;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_Fillet(Float64* fillet)
{
   CHECK_RETVAL(fillet);
   *fillet = m_Fillet;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_Fillet(Float64 fillet)
{
   if ( fillet < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_Fillet,fillet) )
      return S_OK;

   m_Fillet = fillet;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::get_OverhangTaper(DeckOverhangTaper* taper)
{
   CHECK_RETVAL(taper);
   *taper = m_Taper;
   return S_OK;
}

STDMETHODIMP CPrecastSlab::put_OverhangTaper(DeckOverhangTaper taper)
{
   if ( taper != dotNone && taper != dotTopTopFlange && taper != dotBottomTopFlange )
      return E_INVALIDARG;

   if ( m_Taper == taper )
      return S_OK;

   m_Taper = taper;
   return S_OK;
}

/////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CPrecastSlab::Load(IStructuredLoad2* load)
{
   load->BeginUnit(CComBSTR("PrecastSlab"));

   CComVariant var;

   load->get_Property(CComBSTR("Fillet"),&var);
   m_Fillet = var.dblVal;

   load->get_Property(CComBSTR("PanelDepth"),&var);
   m_PanelDepth = var.dblVal;

   load->get_Property(CComBSTR("CastDepth"),&var);
   m_CastDepth = var.dblVal;

   load->get_Property(CComBSTR("OverhangDepth"),&var);
   m_OverhangDepth = var.dblVal;

   load->get_Property(CComBSTR("SacrificialDepth"),&var);
   m_SacrificialDepth = var.dblVal;

   load->get_Property(CComBSTR("Taper"),&var);
   m_Taper = (DeckOverhangTaper)var.lVal;

   var.vt = VT_INDEX;
   load->get_Property(CComBSTR("CastingStage"),&var);
   m_CastingStageIdx = VARIANT2INDEX(var);

   IBridgeDeckImpl<CPrecastSlab>::Load(load);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CPrecastSlab::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("PrecastSlab"),1.0);

   save->put_Property(CComBSTR("Fillet"),CComVariant(m_Fillet));
   save->put_Property(CComBSTR("PanelDepth"),CComVariant(m_PanelDepth));
   save->put_Property(CComBSTR("CastDepth"),CComVariant(m_CastDepth));
   save->put_Property(CComBSTR("OverhangDepth"),CComVariant(m_OverhangDepth));
   save->put_Property(CComBSTR("SacrificalDepth"),CComVariant(m_SacrificialDepth));
   save->put_Property(CComBSTR("Taper"),CComVariant(m_Taper));
   save->put_Property(CComBSTR("CastingStage"),CComVariant(m_CastingStageIdx));
   
   IBridgeDeckImpl<CPrecastSlab>::Save(save);

   save->EndUnit();
   return S_OK;
}
