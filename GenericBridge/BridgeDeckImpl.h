///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEDECKIMPL_H_
#define INCLUDED_BRIDGEDECKIMPL_H_

#include <MathEx.h>
#include "ItemDataManager.h"

template <class T>
class IBridgeDeckImpl : public IBridgeDeck, 
                        public IItemData//,
//                        public CProxyDBridgeDeckEvents<T>
{
public:
   IBridgeDeckImpl()
   {
      m_pBridge = NULL;

      m_bComposite = VARIANT_TRUE;

      m_Material.CoCreateInstance(CLSID_Material);
   }

   HRESULT Init()
   {
      return S_OK;
   }

protected:
   IGenericBridge* m_pBridge; // weak reference


private:
   VARIANT_BOOL m_bComposite;
   //StageIndexType m_ConstructionStage;
   //StageIndexType m_CompositeStage;
   CComPtr<IMaterial> m_Material;

   CItemDataManager m_ItemDataMgr;
   CComPtr<IBridgeDeckRebarLayout> m_RebarLayout;

// IBridgeDeck
public:
   STDMETHOD(putref_Bridge)(/*[in]*/IGenericBridge* pBridge)
   {
      CHECK_IN(pBridge);
      m_pBridge = pBridge; // weak reference
      return S_OK;
   }

   STDMETHOD(get_Bridge)(/*[out,retval]*/IGenericBridge** ppBridge)
   {
      CHECK_RETOBJ(ppBridge);
      (*ppBridge) = m_pBridge;
      if ( *ppBridge )
         (*ppBridge)->AddRef();

      return S_OK;
   }

   STDMETHOD(get_Composite)(/*[out,retval]*/VARIANT_BOOL* bComposite)
   {
      CHECK_RETVAL(bComposite);
      *bComposite = m_bComposite;
      return S_OK;
   }

	STDMETHOD(put_Composite)(/*[in]*/VARIANT_BOOL bComposite)
   {
      if ( m_bComposite == bComposite )
         return S_OK;

      m_bComposite = bComposite;

      return S_OK;
   }

	STDMETHOD(get_Material)(/*[out,retval]*/IMaterial** material)
   {
      CHECK_RETOBJ(material);
      return m_Material.CopyTo(material);
   }

	STDMETHOD(putref_Material)(/*[in]*/IMaterial* material)
   {
      CHECK_IN(material);
      m_Material = material;
      return S_OK;
   }

   STDMETHOD(putref_RebarLayout)(IBridgeDeckRebarLayout* rebarLayout)
   {
      CHECK_IN(rebarLayout);
      m_RebarLayout = rebarLayout;
      return S_OK;
   }

   STDMETHOD(get_RebarLayout)(IBridgeDeckRebarLayout** rebarLayout)
   {
      CHECK_RETOBJ(rebarLayout);
      return m_RebarLayout.CopyTo(rebarLayout);
   }

   ///////////////////////////////////////////////////////////////////////
   // IItemData
   STDMETHOD(AddItemData)(/*[in]*/BSTR name,/*[in]*/IUnknown* data)
   {
      return m_ItemDataMgr.AddItemData(name,data);
   }

   STDMETHOD(GetItemData)(/*[in]*/BSTR name,/*[out,retval]*/IUnknown** data)
   {
      return m_ItemDataMgr.GetItemData(name,data);
   }

   STDMETHOD(RemoveItemData)(/*[in]*/BSTR name)
   {
      return m_ItemDataMgr.RemoveItemData(name);
   }

   STDMETHOD(GetItemDataCount)(/*[out,retval]*/CollectionIndexType* count)
   {
      return m_ItemDataMgr.GetItemDataCount(count);
   }

protected:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load)
   {
      CComVariant var;

      load->get_Property(CComBSTR("Composite"),&var);
      m_bComposite = var.boolVal;

      load->get_Property(CComBSTR("Material"),&var);
      m_Material.Release();
      var.punkVal->QueryInterface(&m_Material);

      return S_OK;
   }

	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save)
   {
      save->put_Property(CComBSTR("Composite"),CComVariant(m_bComposite));
      save->put_Property(CComBSTR("Material"),CComVariant(m_Material));

      return S_OK;
   }
};

#endif // INCLUDED_BRIDGEDECKIMPL_H_