///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2014  Washington State Department of Transportation
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

///////////////////////////////////////////////////////////////////////
// Copyright © 1999-2014  Washington State Department of Transportation
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

#include <WBFLComCollections.h>
#include "resource.h"       // main symbols

#ifndef __CLoadCollection_H_
#define __CLoadCollection_H_


/////////////////////////////////////////////////////////////////////////////
// CLoadItem
template <class TInterface, class TLoad, const IID* piid> 
class ATL_NO_VTABLE CLoadItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLoadItem<TInterface,TLoad,piid> >,
	public TInterface
{
public:
   CLoadItem():
   m_ID(-1),
   m_LoadCookie(0)
	{
	}

// DECLARE_REGISTRY_RESOURCEID(IDR_POINTLOADITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadItem)
	COM_INTERFACE_ENTRY(TInterface)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadItem)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
   {
	   static const IID* arr[] = 
	   {
		   piid
	   };
	   for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	   {
		   if (InlineIsEqualGUID(*arr[i],riid))
			   return S_OK;
	   }
	   return S_FALSE;
   }


// TInterface
public:

   STDMETHOD(get_ID)(LoadIDType *pVal)
   {
	   *pVal = m_ID;

	   return S_OK;
   }

   STDMETHOD(get_Stage)(BSTR *pVal)
   {
      CHECK_RETVAL(pVal);
	   *pVal = m_Stage.Copy();

	   return S_OK;
   }

   STDMETHOD(get_LoadGroup)(BSTR *pVal)
   {
      CHECK_RETVAL(pVal);
	   *pVal = m_LoadGroup.Copy();

	   return S_OK;
   }

   STDMETHOD(get_Load)(TLoad **pVal)
   {
	   CHECK_RETOBJ(pVal);
	   return m_Load.CopyTo(pVal);
   }

   // IStructuredStorage2
#define MY_VER 1.0
   STDMETHOD(Load)(IStructuredLoad2 * pload)
   {
      HRESULT hr;

      hr = pload->BeginUnit(CComBSTR("LoadItem"));
      if (FAILED(hr))
         return hr;

      Float64 ver;
      hr = pload->get_Version(&ver);
      if (FAILED(hr))
         return hr;

      if (ver!=MY_VER)
         return STRLOAD_E_BADVERSION;

      {
         _variant_t var;
         hr = pload->get_Property(_bstr_t("Stage"),&var);
         if (FAILED(hr))
            return hr;

         _bstr_t stage(var);
         m_Stage = (LPCTSTR)stage;
         var.Clear();

         var.Clear();
         hr = pload->get_Property(_bstr_t("LoadGroup"),&var);
         if (FAILED(hr))
            return hr;

         _bstr_t lg(var);
         m_LoadGroup = (LPCTSTR)lg;

         var.Clear();
         hr = pload->get_Property(_bstr_t("ID"),&var);
         if (FAILED(hr))
            return hr;

         m_ID = var;

         var.Clear();
         hr = pload->get_Property(_bstr_t("Load"),&var);
         if (FAILED(hr))
            return hr;

         // get variant into more convenient form
         CComPtr<TLoad> pisps;
         hr = _CopyVariantToInterface<TLoad>::copy(&pisps, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         m_Load = pisps;
      }

      VARIANT_BOOL eb;
      hr = pload->EndUnit(&eb);
      if (FAILED(hr))
         return hr;

      if (eb!=VARIANT_TRUE)
         return STRLOAD_E_INVALIDFORMAT;

      return S_OK;
   }

   STDMETHOD(Save)(IStructuredSave2 * psave)
   {
      HRESULT hr;
      hr = psave->BeginUnit(CComBSTR("LoadItem"), MY_VER);
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Stage"),_variant_t(m_Stage));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("LoadGroup"),_variant_t(m_LoadGroup));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("ID"),_variant_t(m_ID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Load"),_variant_t(m_Load));
      if (FAILED(hr))
         return hr;

      hr = psave->EndUnit();
      return hr;
   }

// members
public:
   CComPtr<TLoad>      m_Load;
   CComBSTR            m_Stage;
   CComBSTR            m_LoadGroup;
   LoadIDType          m_ID;

   DWORD               m_LoadCookie; // for events
};


// The collection class
///////////////////////////////////////
template <class T, const IID* piidT, class TDerived, class LoadType, class IItemType, class CItemType,
          class EnumType, const IID* piidEnum>
class  CLoadCollection :
   public T,
   public IStructuredStorage2,
   public IPersistImpl<TDerived>
{
public:

   // Interface Map here so that clients don't have to remember to
   // build it. However clients do have to add
   // COM_INTERFACE_ENTRY_CHAIN(CPersistentCollection<Tderived,TColl,Version>)
   // to their interface maps.
   // This chains their primary map to this secondary map
   typedef CLoadCollection<T, piidT, TDerived, LoadType, IItemType, CItemType,
           EnumType, piidEnum> _ThisClass;

   BEGIN_COM_MAP(_ThisClass)
      COM_INTERFACE_ENTRY(IStructuredStorage2)
      COM_INTERFACE_ENTRY(T)
      COM_INTERFACE_ENTRY(IPersist)
   END_COM_MAP()

private:
   typedef CComPtr<IItemType>         StoredType;
   typedef typename std::map<LoadIDType, StoredType> ContainerType;
   typedef typename ContainerType::iterator    ContainerIteratorType;
   typedef typename ContainerType::value_type  ContainerValueType;

   ContainerType m_Container; // key value pair
   LoadIDType    m_LastUniqueKey;

   // for persistence
   _bstr_t m_Name;
   Float64 m_Version;


   // some virtual methods for dealing with adding and 
   // removing items from this collection
protected:
   virtual void    FireAfterAdd(IItemType* pitem)=0;
   virtual void    FireBeforeRemove(IItemType* pitem)=0;
   virtual void    FireOnChanged(IItemType* pitem)=0;
   // connection point routines must be at bottom of class hiearch becase of Release calls 
   virtual HRESULT MakeConnection(CItemType* pitem)=0;
   virtual HRESULT BreakConnection(CItemType* pitem)=0;

public:
   CLoadCollection():
   m_LastUniqueKey(0)
   {
      m_Version = 1.0;
   }

   STDMETHOD(get_Count)(CollectionIndexType *pVal)
   {
	   CHECK_RETVAL(pVal);

      *pVal = m_Container.size();

	   return S_OK;
   }

   STDMETHOD(get_Item)(CollectionIndexType index, IItemType **pVal)
   {
	   CHECK_RETOBJ(pVal);

      if (index<0)
         return E_INVALIDARG;

      ContainerIteratorType it( m_Container.begin() );
      for (CollectionIndexType i=0; i<index; i++)
         it++;

      if (it != m_Container.end())
      {
         *pVal = it->second;
         (*pVal)->AddRef();
      }
      else
         return E_INVALIDARG;

	   return S_OK;
   }

   STDMETHOD(get_Load)(LoadIDType ID, LoadType* *pVal)
   {
      CHECK_RETOBJ(pVal);
   
      CComPtr<IItemType> tmp;
      HRESULT hr = Find(ID, &tmp);
      if (FAILED(hr))
         return hr;

      if (tmp==NULL)
      {
         *pVal=NULL;
         return E_INVALIDARG;
      }

      return tmp->get_Load(pVal);
   }

   STDMETHOD(putref_Load)(LoadIDType ID, LoadType* newVal)
   {
      CHECK_IN(newVal);
      HRESULT hr;

      ContainerIteratorType it( m_Container.find(ID) );
      if (it != m_Container.end())
      {
         IItemType* item = it->second;
         hr = PutLoad( item, newVal);
         if (FAILED(hr))
            return hr;

         // tell the world we've changed
         FireOnChanged(item);
      }
      else
      {
         return E_INVALIDARG;
      }

	   return S_OK;
   }

   STDMETHOD(get__EnumElements)(EnumType **ppenum)
   {
      CHECK_RETOBJ(ppenum);

      typedef _CopyMapOfCComVariantsToInterface<IItemType, ContainerType> CopyType;
      typedef CComEnumOnSTL<EnumType, piidEnum, IItemType*, CopyType, ContainerType> MyEnumType;
      CComObject<MyEnumType>* pEnum;
      HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
      if ( FAILED(hr) )
         return hr;

      hr = pEnum->Init( NULL, m_Container );
      if ( FAILED(hr) )
         return hr;

      *ppenum = pEnum;
      (*ppenum)->AddRef(); // for client

      return S_OK;
   }

   STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
   {
	   if (ppUnk == NULL)
		   return E_POINTER;

	   *ppUnk = NULL;
	   HRESULT hRes = S_OK;

      typedef _CopyMapOfCComVariants<ContainerType> CopyVariantType;
      typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyVariantType, ContainerType > VecEnumType;
	   CComObject<VecEnumType>* p;
	   hRes = CComObject<VecEnumType>::CreateInstance(&p);
	   if (SUCCEEDED(hRes))
	   {
         IUnknown* punkthis;
   	   hRes = this->QueryInterface(IID_IUnknown, (void**)&punkthis);
         ATLASSERT(SUCCEEDED(hRes));

   		hRes = p->Init(punkthis, m_Container);
		   if (hRes == S_OK)
			   hRes = p->QueryInterface(IID_IUnknown, (void**)ppUnk);
	   }
	   if (hRes != S_OK)
		   delete p;
	   return hRes;
   }

   STDMETHOD(Add)(BSTR Stage, BSTR LoadGroup, LoadType * pLoad, IItemType** Item)
   {
      CHECK_IN(pLoad);

      CComBSTR bstg(Stage);
      if (bstg.Length() == 0)
         return E_INVALIDARG;

      CComBSTR blg(LoadGroup);
      if (blg.Length() == 0)
         return E_INVALIDARG;

      // create a new Item
      CComObject<CItemType>* pitem;
      HRESULT hr = CComObject<CItemType>::CreateInstance( &pitem );
      if (FAILED(hr))
         return hr;

      CComPtr<IItemType> psafe(pitem); // exception safety

      pitem->m_Stage = bstg;
      pitem->m_LoadGroup = blg;
      pitem->m_ID = ++m_LastUniqueKey;
   
      hr = PutLoad(pitem, pLoad);
      if (FAILED(hr))
         return hr;

      if (Item!=NULL)
      {
         *Item = pitem;
         (*Item)->AddRef(); // for client
      }

      // insert new member
      std::pair<ContainerIteratorType,bool> st( m_Container.insert(ContainerValueType(pitem->m_ID, pitem)) );
      if (!st.second)
      {
         ATLASSERT(0); // insert failed - better check why
         return E_POINTER;
      }

      FireAfterAdd(pitem);

	   return S_OK;
   }

   STDMETHOD(Find)(LoadIDType ID, IItemType ** retVal )
   {
      CHECK_RETOBJ(retVal);

      ContainerIteratorType it( m_Container.find(ID) );
      if (it != m_Container.end())
      {
         *retVal = it->second;
         (*retVal)->AddRef();
      }
      else
      {
         *retVal = 0;
      }

	   return S_OK;
   }

   STDMETHOD(RemoveByID)(LoadIDType ID)
   {
      ContainerIteratorType it( m_Container.find(ID) );
      if (it != m_Container.end())
      {
         HRESULT hr = OnBeforeRemove(it->second);
         if (FAILED(hr))
            return hr;

         m_Container.erase(it);

      }

	   return S_OK;
   }

   STDMETHOD(RemoveByIndex)(CollectionIndexType index)
   {
      if (index<0)
         return E_INVALIDARG;

      ContainerIteratorType it( m_Container.begin() );
      for (CollectionIndexType i=0; i<index; i++, it++)
      ;

      if (it != m_Container.end())
      {
         HRESULT hr = OnBeforeRemove(it->second);
         if (FAILED(hr))
            return hr;

         m_Container.erase(it);

      }
      else
         return E_INVALIDARG;

	   return S_OK;
   }

   STDMETHOD(FilterByStageGroup)(BSTR stage, BSTR loadgroup, T **filteredcoll)
   {
      CHECK_RETOBJ(filteredcoll);
      HRESULT hr;

      CComBSTR bstg(stage);
      if (bstg.Length() == 0)
         return E_INVALIDARG;

      CComBSTR blg(loadgroup);
      if (blg.Length() == 0)
         return E_INVALIDARG;

      // pointer to hold collection - only assigned if needed
      CComPtr<T> pcoll;

      CComBSTR wildcard("*");

      // iterate through our collection and find matching items
      bool first = true;
      ContainerIteratorType i(m_Container.begin());
      ContainerIteratorType iend(m_Container.end());
      for (; i!=iend; i++)
      {
         // we know that all IItemType's under our watch are CItemType's
         CItemType* pitm = dynamic_cast<CItemType*>(i->second.p);
         if (pitm == 0)
         {
            ATLASSERT(0); // this should never happen since we are eating our own dog food here
            return E_FAIL;
         }

         if (bstg == pitm->m_Stage || bstg == wildcard)
         {
            if (blg == pitm->m_LoadGroup || blg == wildcard)
            {

               if (first)
               {
                  first = false;

                  // only create a new collection if we have a first match
                  CComObject<TDerived>* ptmp;
                  HRESULT hr = CComObject<TDerived>::CreateInstance( &ptmp );
                  if (FAILED(hr))
                     return hr;

                  pcoll = ptmp;
               }

               // have a match - add it to Container
               CComPtr<IItemType> tmp;
               hr = pcoll->Add(pitm->m_Stage, pitm->m_LoadGroup, pitm->m_Load, &tmp);
               if (FAILED(hr))
                  return hr;
            }
         }
      }

      *filteredcoll = pcoll;

      if (pcoll!=NULL)
         (*filteredcoll)->AddRef();

	   return S_OK;
   }

   STDMETHOD(Clone)(T **pColl)
   {
      CHECK_RETOBJ(pColl);

      // create a new  collection and fill it up
      CComObject<TDerived>* pnew;
      HRESULT hr = CComObject<TDerived>::CreateInstance(&pnew);
      if (FAILED(hr))
         return hr;

      CComPtr<TDerived> save(pnew);

      // clone properties

      // clone collection
      ContainerIteratorType it( m_Container.begin() );
      ContainerIteratorType itend( m_Container.end() );
      for (; it != itend; it++)
      {
         // we know that all IItem's under our watch are CItem's
         CItemType* pitem = dynamic_cast<CItemType*>(it->second.p);
         if (pitem == 0)
         {
            ATLASSERT(0); // this should never happen since we are eating our own dog food here
            return E_FAIL;
         }

         // deep clone
         CComPtr<LoadType>     isp;
         hr = pitem->m_Load->Clone(&isp);
         if (FAILED(hr))
            return hr;

         CComPtr<IItemType> tmp;
         hr = pnew->Add(pitem->m_Stage, pitem->m_LoadGroup, isp, &tmp);
         if (FAILED(hr))
            return hr;
      }

      *pColl = pnew;
      (*pColl)->AddRef();

      return S_OK;
   }

   STDMETHOD(Clear)()
   {
      ContainerIteratorType it(m_Container.begin());
      ContainerIteratorType itend(m_Container.end());
      for (; it != itend; it++)
      {
         OnBeforeRemove(it->second);
      }

      m_Container.clear();

      return S_OK;
   }
 

   STDMETHOD(OnBeforeRemove)(IItemType* item)
   {
      // we know that all IPointLoadItem's under our watch are CItemType's
      CItemType* pitm = dynamic_cast<CItemType*>(item);
      if (pitm == 0)
      {
         ATLASSERT(0); // this should never happen since we are eating our own dog food here
         return E_FAIL;
      }


      try
      {
         // release connection point
         HRESULT hr;
         hr = BreakConnection(pitm);
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(0);
         return E_FAIL;
      }

      // fire event
      FireBeforeRemove(pitm);

      return S_OK;
   }


   STDMETHOD(RemoveStage)(BSTR stage)
   {
      CComBSTR bstg(stage);
      if (bstg.Length() == 0)
         return E_INVALIDARG;

      // iterate through our collection and find matching items
      ContainerIteratorType cur( m_Container.begin() );
      ContainerIteratorType end( m_Container.end() );

      while( cur != end )
      {
         // we know that all ILoadItem's under our watch are CItemType's
         CItemType* pitm = dynamic_cast<CItemType*>(cur->second.p);
         if (pitm == 0)
         {
            ATLASSERT(0); // this should never happen since we are eating our own dog food here
            return E_FAIL;
         }

         if (bstg == pitm->m_Stage)
         {
            // found match, remove it
            HRESULT hr = OnBeforeRemove(pitm);
            if (FAILED(hr))
               return hr;

            // have to be careful here since erase can reorder container
            cur = m_Container.erase(cur);
            end = m_Container.end();
         }
         else
         {
            cur++;
         }
      }

	   return S_OK;
   }


   STDMETHOD(PutLoad)(IItemType* item, LoadType* newVal)
   {
      // we know that all IItemType's under our watch are CItemType's
      CItemType* pitm = dynamic_cast<CItemType*>(item);
      if (pitm == 0)
      {
         ATLASSERT(0); // this should never happen since we are eating our own dog food here
         return E_FAIL;
      }

      // now we have the right item, just twiddle it's inside parts

      // don't bother if someone is assigning same collection
      if ( pitm->m_Load.IsEqualObject(newVal) )
         return S_OK;

      // first we must break our cp with old collection if we had one
      HRESULT hr;
      if (!!(pitm->m_Load))
      {
         hr = BreakConnection(pitm);
         if (FAILED(hr))
            return hr;
      }

      // assign new 
      pitm->m_Load = newVal;

      // establish cp with new collection
      hr = MakeConnection(pitm);
      if (FAILED(hr))
         return hr;

      return S_OK;
   }

   // Virtual functions to describe collection name, version and stored objects
   // Override these if you want prettier names than typeid gives you
   virtual _bstr_t GetCollectionName()
   {
      const type_info& t = typeid(TDerived);
      // string is in the form "struct Name". Need to get rid of the "struct " part
      const char* nm = t.name();
      nm += 7;
      std::string name(nm);

      return _bstr_t(nm);
   }

   virtual Float64 GetVersion()
   {
      return m_Version;
   }

   virtual _bstr_t GetStoredName()
   {
      const type_info& t = typeid(LoadType);
      // string is in the form "struct Name". Need to get rid of the "struct " part
      const char* nm = t.name();
      nm += 7;
      std::string name(nm);

      return _bstr_t(nm);
   }



public:
   // IStructuredStorage2
   // Load from storage
   STDMETHOD(Load)(IStructuredLoad2 *pload)
   {
      HRESULT hr;
      hr = pload->BeginUnit( GetCollectionName() );
      if (FAILED(hr))
         return hr;

      Float64 ver;
      hr = pload->get_Version(&ver);
      if (FAILED(hr))
         return hr;

      if (ver != GetVersion() )
         return STRLOAD_E_BADVERSION;

      // see how many items we have
      _variant_t varlong;
      hr = pload->get_Property(_bstr_t("Count"),&varlong);
      if (FAILED(hr))
         return hr;

      CollectionIndexType count = varlong;
      m_LastUniqueKey = 1;
      for (CollectionIndexType i=0; i<count; i++)
      {

         // items are not creatable, so we need to create and load manually
         CComObject<CItemType>* pitem;
         HRESULT hr = CComObject<CItemType>::CreateInstance( &pitem );
         if (FAILED(hr))
            return hr;

         CComPtr<IItemType> psafe(pitem); // exception safety

         // get item from store
         CComVariant var;
         hr = pitem->Load(pload);
         if (FAILED(hr))
            return hr;

         // we want to maintain id's for items pulled from store - need to make sure 
         // that any new items are unique
         m_LastUniqueKey = max(m_LastUniqueKey, pitem->m_ID);

         // temporarly remove load from item and then use PutLoad to put it back.
         // this sets up the connection points
         // add new item
         CComPtr<LoadType> tmp = pitem->m_Load;
         pitem->m_Load = NULL;

         hr = PutLoad(pitem, tmp);
         if (FAILED(hr))
            return hr;

         // insert new member
         std::pair<ContainerIteratorType,bool> st( m_Container.insert(ContainerValueType(pitem->m_ID, pitem)) );
         if (!st.second)
         {
            ATLASSERT(0); // insert failed - better check why
            return E_POINTER;
         }

      }

      VARIANT_BOOL eb;
      hr = pload->EndUnit(&eb);
      if (FAILED(hr))
         return hr;

      // not checking strict units here 
      // if (eb!=VARIANT_TRUE)
      //    return STRLOAD_E_INVALIDFORMAT;

      return S_OK;
   }

   STDMETHOD(Save)(IStructuredSave2 *save)
   {
      HRESULT hr;
      hr = save->BeginUnit(GetCollectionName(), GetVersion() );
      if (FAILED(hr))
         return hr;

      // save out count
      CollectionIndexType count;
      this->get_Count(&count);
      hr = save->put_Property(_bstr_t("Count"),_variant_t(count));
      if (FAILED(hr))
         return hr;

      // cycle though collection and save members
      ContainerIteratorType it(  m_Container.begin() );
      ContainerIteratorType itend(  m_Container.end() );
      for (; it!=itend; it++)
      {
         CItemType* pitm = dynamic_cast<CItemType*>(it->second.p);
         if (pitm == 0)
         {
            ATLASSERT(0); // this should never happen since we are eating our own dog food here
            return E_FAIL;
         }

         // can use Save here instead of Property since we know that all of our items are unique.
         hr = pitm->Save(save);
         if (FAILED(hr))
            return hr;
      }

      hr = save->EndUnit();
      if (FAILED(hr))
         return hr;

      return S_OK;
   }

/////////////
// Classes for local C++ clients
protected:

   // trimmed-down iterator class
   class iterator
   {
      friend CLoadCollection;

   public:
		iterator& operator++()
      {
         m_it++;			
         return (*this); 
      }

		iterator operator++(int)
      {
         iterator tmp = *this;
			m_it++;
			return (tmp); 
      }

		IItemType* operator*() const
      {
         return (m_it->second);
      }

		IItemType* operator->() const
      {
         return (m_it->second);
      }

		bool operator==(const iterator& rit) const
		{
         return (m_it == rit.m_it);
      }

		bool operator!=(const iterator& rit) const
		{
         return (m_it != rit.m_it);
      }

   private:
      ContainerIteratorType m_it;
   };

   iterator begin()
   {
      iterator it;
      it.m_it = m_Container.begin();
      return it;
   }

   iterator end()
   {
      iterator it;
      it.m_it = m_Container.end();
      return it;
   }

};


#endif //
