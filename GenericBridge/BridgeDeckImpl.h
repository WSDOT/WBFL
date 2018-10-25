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

#ifndef INCLUDED_BRIDGEDECKIMPL_H_
#define INCLUDED_BRIDGEDECKIMPL_H_

#include <MathEx.h>
#include "ItemDataManager.h"
#include "GenericBridgeCP.h"

template <class T>
class IBridgeDeckImpl : public IBridgeDeck, 
                        public IItemData,
                        public CProxyDBridgeDeckEvents<T>
{
public:
   IBridgeDeckImpl()
   {
      m_bComposite = VARIANT_TRUE;
      m_WearingSurfaceDepth = 0;
      m_WearingSurfaceDensity = 0;

      m_Material.CoCreateInstance(CLSID_Material);
   }


private:
   VARIANT_BOOL m_bComposite;
   CComBSTR m_bstrConstructionStage;
   CComBSTR m_bstrCompositeStage;
   Float64 m_WearingSurfaceDepth;
   Float64 m_WearingSurfaceDensity;
   CComPtr<IMaterial> m_Material;

   CItemDataManager m_ItemDataMgr;

// IBridgeDeck
public:
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
      Fire_OnBridgeDeckChanged(this);

      return S_OK;
   }

	STDMETHOD(get_ConstructionStage)(/*[out,retval]*/BSTR* bstrStage)
   {
      CHECK_RETSTRING(bstrStage);
      *bstrStage = m_bstrConstructionStage.Copy();
      return S_OK;
   }

	STDMETHOD(put_ConstructionStage)(/*[in]*/BSTR bstrStage)
   {
      if ( m_bstrConstructionStage == bstrStage )
         return S_OK;

      m_bstrConstructionStage.Empty();
      m_bstrConstructionStage = bstrStage;
      Fire_OnBridgeDeckChanged(this);

      return S_OK;
   }

	STDMETHOD(get_CompositeStage)(/*[out,retval]*/BSTR* bstrStage)
   {
      CHECK_RETSTRING(bstrStage);
      *bstrStage = m_bstrCompositeStage.Copy();
      return S_OK;
   }

   STDMETHOD(put_CompositeStage)(/*[in]*/BSTR bstrStage)
   {
      CHECK_IN(bstrStage);
      if ( m_bstrCompositeStage == bstrStage )
         return S_OK;

      m_bstrCompositeStage.Empty();
      m_bstrCompositeStage = bstrStage;
      Fire_OnBridgeDeckChanged(this);

      return S_OK;
   }

	STDMETHOD(get_WearingSurfaceDepth)(/*[out,retval]*/Float64* d)
   {
      CHECK_RETVAL(d);
      *d = m_WearingSurfaceDepth;
      return S_OK;
   }

	STDMETHOD(put_WearingSurfaceDepth)(/*[in]*/Float64 depth)
   {
      if ( depth < 0 )
         return E_INVALIDARG;

      if ( IsEqual(m_WearingSurfaceDepth,depth) )
         return S_OK;

      m_WearingSurfaceDepth = depth;
      Fire_OnBridgeDeckChanged(this);

      return S_OK;
   }

	STDMETHOD(get_WearingSurfaceDensity)(/*[out,retval]*/Float64* d)
   {
      CHECK_RETVAL(d);
      *d = m_WearingSurfaceDensity;
      return S_OK;
   }

	STDMETHOD(put_WearingSurfaceDensity)(/*[in]*/Float64 density)
   {
      if ( density < 0 )
         return E_INVALIDARG;

      if ( IsEqual(m_WearingSurfaceDensity,density) )
         return S_OK;

      m_WearingSurfaceDensity = density;
      Fire_OnBridgeDeckChanged(this);

      return S_OK;
   }

	STDMETHOD(get_Material)(/*[out,retval]*/IMaterial** material)
   {
      CHECK_RETOBJ(material);

      // by-value semantics
      CComPtr<IMaterial> clone;
      m_Material->Clone(&clone);
      (*material) = clone;
      (*material)->AddRef();
      return S_OK;
   }

	STDMETHOD(put_Material)(/*[in]*/IMaterial* material)
   {
      CHECK_IN(material);

      // by-value semantics
      CComPtr<IMaterial> clone;
      HRESULT hr = material->Clone(&clone);
      if ( FAILED(hr) )
         return hr;

      if ( m_Material.IsEqualObject(material) )
         return S_OK;

      m_Material = material;
      Fire_OnBridgeDeckChanged(this);

      return S_OK;
   }

   STDMETHOD(Clone)(/*[out,retval]*/IBridgeDeck** clone)
   {
      // Derived class must pass in a bridge deck object
      CHECK_IN(*clone);

      (*clone)->put_Composite(m_bComposite);
      (*clone)->put_CompositeStage(m_bstrCompositeStage);
      (*clone)->put_ConstructionStage(m_bstrConstructionStage);

      CComPtr<IMaterial> material_clone;
      m_Material->Clone(&material_clone);
      (*clone)->put_Material(material_clone);

      (*clone)->put_WearingSurfaceDensity(m_WearingSurfaceDensity);
      (*clone)->put_WearingSurfaceDepth(m_WearingSurfaceDepth);

      return S_OK;
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

      load->get_Property(CComBSTR("ConstructionStage"),&var);
      m_bstrConstructionStage = var.bstrVal;

      load->get_Property(CComBSTR("CompositeStage"),&var);
      m_bstrCompositeStage = var.bstrVal;

      load->get_Property(CComBSTR("WearingSurfaceDensity"),&var);
      m_WearingSurfaceDensity = var.dblVal;

      load->get_Property(CComBSTR("WearingSurfaceDepth"),&var);
      m_WearingSurfaceDepth = var.dblVal;

      load->get_Property(CComBSTR("Material"),&var);
      m_Material.Release();
      var.punkVal->QueryInterface(&m_Material);

      return S_OK;
   }

	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save)
   {
      save->put_Property(CComBSTR("Composite"),CComVariant(m_bComposite));
      save->put_Property(CComBSTR("ConstructionStage"),CComVariant(m_bstrConstructionStage));
      save->put_Property(CComBSTR("CompositeStage"),CComVariant(m_bstrCompositeStage));
      save->put_Property(CComBSTR("WearingSurfaceDensity"),CComVariant(m_WearingSurfaceDensity));
      save->put_Property(CComBSTR("WearingSurfaceDepth"),CComVariant(m_WearingSurfaceDepth));
      save->put_Property(CComBSTR("Material"),CComVariant(m_Material));

      return S_OK;
   }
};

#endif // INCLUDED_BRIDGEDECKIMPL_H_