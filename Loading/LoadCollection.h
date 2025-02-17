///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright � 1999-2025  Washington State Department of Transportation
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

#include "ComCollections.h"
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
	   for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	   {
		   if (InlineIsEqualGUID(*arr[i],riid))
			   return S_OK;
	   }
	   return S_FALSE;
   }


// TInterface
public:

   STDMETHOD(get_ID)(IDType *pVal)
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
         CComVariant var;
         hr = pload->get_Property(CComBSTR("Stage"),&var);
         if (FAILED(hr))
            return hr;

         m_Stage = var.bstrVal;
         var.Clear();

         var.Clear();
         hr = pload->get_Property(CComBSTR("LoadGroup"),&var);
         if (FAILED(hr))
            return hr;

         m_LoadGroup = var.bstrVal;

         var.Clear();
         hr = pload->get_Property(CComBSTR("ID"),&var);
         if (FAILED(hr))
            return hr;

         m_ID = var.iVal;

         var.Clear();
         hr = pload->get_Property(CComBSTR("Load"),&var);
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

      hr = psave->put_Property(CComBSTR("Stage"),CComVariant(m_Stage));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("LoadGroup"),CComVariant(m_LoadGroup));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("ID"),CComVariant(m_ID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Load"),CComVariant(m_Load));
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
   IDType              m_ID;

   DWORD       m_LoadCookie; // for events
};


///////////////////////////////////////
// The collection class
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
   using _ThisClass = CLoadCollection<T, piidT, TDerived, LoadType, IItemType, CItemType, EnumType, piidEnum>;

   BEGIN_COM_MAP(_ThisClass)
      COM_INTERFACE_ENTRY(IStructuredStorage2)
      COM_INTERFACE_ENTRY(T)
      COM_INTERFACE_ENTRY(IPersist)
   END_COM_MAP()

private:
   using StoredType = CComPtr<IItemType>;
   using ContainerType = typename std::map<IDType, StoredType>;
   using ContainerIteratorType = typename ContainerType::iterator;
   using ContainerValueType = typename ContainerType::value_type;

   ContainerType m_Container; // key value pair
   IDType        m_LastUniqueKey;

   Float64 m_Version;

   // for persistence
   CComBSTR m_Name;


   // some virtual methods for dealing with adding and 
   // removing items from this collection
protected:
   virtual void    FireAfterAdd(IItemType* pitem) {};
   virtual void    FireBeforeRemove(IItemType* pitem) {};
   virtual void    FireAfterRemove() {};
   virtual void    FireOnChanged(IItemType* pitem) {};
   // connection point routines must be at bottom of class hiearch becase of Release calls 
   virtual HRESULT MakeConnection(CItemType* pitem) = 0;
   virtual HRESULT BreakConnection(CItemType* pitem) = 0;

public:
   CLoadCollection():
   m_LastUniqueKey(0)
   {
      m_Version = 1.0;
   }

   STDMETHOD(get_Count)(IndexType *pVal)
   {
	   CHECK_RETVAL(pVal);

      *pVal = m_Container.size();

	   return S_OK;
   }

   STDMETHOD(get_Item)(IndexType index, IItemType **pVal)
   {
	   CHECK_RETOBJ(pVal);

      if (index<0)
         return E_INVALIDARG;

      ContainerIteratorType it = m_Container.begin();
      for (IndexType i = 0; i<index; i++)
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

   STDMETHOD(get_Load)(IDType ID, LoadType* *pVal)
   {
      CHECK_RETOBJ(pVal);
   
      CComPtr<IItemType> tmp;
      HRESULT hr = Find(ID, &tmp);
      if (FAILED(hr))
         return hr;

      if (tmp==nullptr)
      {
         *pVal=nullptr;
         return E_INVALIDARG;
      }

      return tmp->get_Load(pVal);
   }

   STDMETHOD(putref_Load)(IDType ID, LoadType* newLoad)
   {
      ContainerIteratorType it = m_Container.find(ID);
      if ( it == m_Container.end() )
         return E_INVALIDARG;

      CComPtr<IItemType> pItem = (*it).second;

      HRESULT hr = DoPutLoad(this,pItem,newLoad);

   	return hr;
   }

   STDMETHOD(get__EnumElements)(EnumType **ppenum)
   {
      CHECK_RETOBJ(ppenum);

      using CopyType = _CopyMapOfCComVariantsToInterface<IItemType, ContainerType>;
      using MyEnumType = CComEnumOnSTL<EnumType, piidEnum, IItemType*, CopyType, ContainerType>;
      CComObject<MyEnumType>* pEnum;
      HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
      if ( FAILED(hr) )
         return hr;

      hr = pEnum->Init( nullptr, m_Container );
      if ( FAILED(hr) )
         return hr;

      *ppenum = pEnum;
      (*ppenum)->AddRef(); // for client

      return S_OK;
   }

   STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
   {
	   if (ppUnk == nullptr)
		   return E_POINTER;

	   *ppUnk = nullptr;
	   HRESULT hRes = S_OK;

      using CopyVariantType = _CopyMapOfCComVariants<ContainerType>;
      using VecEnumType = CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyVariantType, ContainerType >;
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

   STDMETHOD(Add)(BSTR Stage, BSTR LoadGroup, LoadType * pLoad)
   {
      CHECK_IN(Stage);
      CHECK_IN(LoadGroup);
      CHECK_IN(pLoad);

      IDType ID = ++m_LastUniqueKey;
      using Parameters = AddLoadParams;
      Parameters parameters(ID,Stage,LoadGroup,pLoad);

      HRESULT hr = DoAddLoad(this,parameters);
      return hr;

   }

   STDMETHOD(Find)(IDType ID, IItemType ** retVal )
   {
      CHECK_RETOBJ(retVal);

      ContainerIteratorType it = m_Container.find(ID);
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

   STDMETHOD(RemoveByID)(IDType ID)
   {
      // Get the item to remove
      ContainerIteratorType iter = m_Container.find(ID);
      if ( iter == m_Container.end() )
         return S_FALSE; // Not found

      StoredType item = iter->second;

      HRESULT hr = DoRemoveByID(this,item);
      return hr;
   }

   STDMETHOD(RemoveByIndex)(IndexType index)
   {
      // NOTE: If this is undone, the item will be put back in the container,
      //       but its index will change.
      if ( !IsValidIndex(index,m_Container) )
         return E_INVALIDARG;

      // run the iterator throught the container
      ContainerIteratorType iter = m_Container.begin();
      for (IndexType i = 0; i<index; i++, iter++)
      ;
   
      ATLASSERT(iter != m_Container.end()); // should be past at end because of check on index above
      
      StoredType item = iter->second;
      IDType ID;
      item->get_ID(&ID);
      return RemoveByID(ID);
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
      for (ContainerIteratorType i=m_Container.begin(); i!=m_Container.end(); i++)
      {
         // we know that all IItemType's under our watch are CItemType's
         CItemType* pitm = dynamic_cast<CItemType*>(i->second.p);
         if (pitm == 0)
         {
            ATLASSERT(false); // this should never happen since we are eating our own dog food here
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
               hr = pcoll->Add(pitm->m_Stage, pitm->m_LoadGroup, pitm->m_Load);
               if (FAILED(hr))
                  return hr;
            }
         }
      }

      *filteredcoll = pcoll;

      if (pcoll!=nullptr)
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
      for (ContainerIteratorType it= m_Container.begin(); it != m_Container.end(); it++)
      {
         // we know that all IItem's under our watch are CItem's
         CItemType* pitem = dynamic_cast<CItemType*>(it->second.p);
         if (pitem == 0)
         {
            ATLASSERT(false); // this should never happen since we are eating our own dog food here
            return E_FAIL;
         }

         // deep clone
         CComPtr<LoadType>     isp;
         hr = pitem->m_Load->Clone(&isp);
         if (FAILED(hr))
            return hr;

         hr = pnew->Add(pitem->m_Stage, pitem->m_LoadGroup, isp);
         if (FAILED(hr))
            return hr;
      }

      *pColl = pnew;
      (*pColl)->AddRef();

      return S_OK;
   }

   STDMETHOD(Clear)()
   {
      HRESULT hr = DoClear(this,m_Container);
      return hr;
   }
 

   STDMETHOD(OnBeforeRemove)(IItemType* item)
   {
      // we know that all IPointLoadItem's under our watch are CItemType's
      CItemType* pitm = dynamic_cast<CItemType*>(item);
      if (pitm == 0)
      {
         ATLASSERT(false); // this should never happen since we are eating our own dog food here
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
         ATLASSERT(false);
         return E_FAIL;
      }

      // fire event
      FireBeforeRemove(pitm);

      return S_OK;
   }


   STDMETHOD(RemoveStage)(BSTR stage)
   {
      CHECK_IN(stage);
      RemoveStageParams parameters(stage);
      HRESULT hr = DoRemoveStage(this,parameters);
      return hr;
   }

   STDMETHOD(SwapLoad)(IItemType* item, LoadType* newVal)
   {
      // we know that all IItemType's under our watch are CItemType's
      CItemType* pitm = dynamic_cast<CItemType*>(item);
      if (pitm == 0)
      {
         ATLASSERT(false); // this should never happen since we are eating our own dog food here
         return E_FAIL;
      }

      // now we have the right item, just twiddle it's inside parts

      // don't bother if someone is assigning same collection
      if ( pitm->m_Load.IsEqualObject(newVal) )
         return S_OK;

      // first we must break our cp with old collection if we had one
      HRESULT hr;
      if (pitm->m_Load)
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
   virtual CComBSTR GetCollectionName()
   {
      const type_info& t = typeid(TDerived);
      // string is in the form "struct Name". Need to get rid of the "struct " part
      const char* nm = t.name();
      nm += 7;
      std::string name(nm);

      return CComBSTR(nm);
   }

   virtual Float64 GetVersion()
   {
      return m_Version;
   }

   virtual CComBSTR GetStoredName()
   {
      const type_info& t = typeid(LoadType);
      // string is in the form "struct Name". Need to get rid of the "struct " part
      const char* nm = t.name();
      nm += 7;
      std::string name(nm);

      return CComBSTR(nm);
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
      CComVariant varlong;
      hr = pload->get_Property(CComBSTR("Count"),&varlong);
      if (FAILED(hr))
         return hr;

      IndexType count = varlong.iVal;
      m_LastUniqueKey = 1;
      for (IndexType i = 0; i<count; i++)
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

         // temporarly remove load from item and then use SwapLoad to put it back.
         // this sets up the connection points
         // add new item
         CComPtr<LoadType> tmp = pitem->m_Load;
         pitem->m_Load = nullptr;

         hr = SwapLoad(pitem, tmp);
         if (FAILED(hr))
            return hr;

         // insert new member
         std::pair<ContainerIteratorType,bool> st;
         st = m_Container.insert(ContainerValueType(pitem->m_ID, pitem));
         if (!st.second)
         {
            ATLASSERT(false); // insert failed - better check why
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
      IndexType count;
      this->get_Count(&count);
      hr = save->put_Property(CComBSTR("Count"),CComVariant(count));
      if (FAILED(hr))
         return hr;

      // cycle though collection and save members
      for (ContainerIteratorType it=m_Container.begin(); it!=m_Container.end(); it++)
      {
         CItemType* pitm = dynamic_cast<CItemType*>(it->second.p);
         if (pitm == 0)
         {
            ATLASSERT(false); // this should never happen since we are eating our own dog food here
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

   ///////////////////////////////////////////
   // Transaction Callback functions
   static HRESULT DoPutLoad(_ThisClass* pThis,IItemType* item,LoadType* newLoad)
   {
      CHECK_IN(newLoad);
      HRESULT hr;

      hr = pThis->SwapLoad( item, newLoad);
      if (FAILED(hr))
         return hr;

      // tell the world we've changed
      pThis->FireOnChanged(item);

	   return S_OK;
   }

   struct AddLoadParams
   {
      AddLoadParams() {}
      AddLoadParams(IDType id,BSTR stage,BSTR loadGroup,LoadType* pload) :
         ID(id), bstrStage(stage), bstrLoadGroup(loadGroup), Load(pload) {}

      IDType            ID;
      CComBSTR          bstrStage;
      CComBSTR          bstrLoadGroup;
      CComPtr<LoadType> Load;
   };
   static HRESULT DoAddLoad(_ThisClass* pThis,AddLoadParams& params)
   {
      if (params.bstrStage.Length() == 0)
         return E_INVALIDARG;

      if (params.bstrLoadGroup.Length() == 0)
         return E_INVALIDARG;

      // create a new Item
      CComObject<CItemType>* pitem;
      HRESULT hr = CComObject<CItemType>::CreateInstance( &pitem );
      if (FAILED(hr))
         return hr;

      CComPtr<IItemType> psafe(pitem); // exception safety

      pitem->m_ID        = params.ID;
      pitem->m_Stage     = params.bstrStage;
      pitem->m_LoadGroup = params.bstrLoadGroup;
   
      hr = pThis->SwapLoad(pitem, params.Load);
      if (FAILED(hr))
         return hr;

      // insert new member
      std::pair<ContainerIteratorType,bool> st;
      st = pThis->m_Container.insert(ContainerValueType(pitem->m_ID, pitem));
      if (!st.second)
      {
         ATLASSERT(false); // insert failed - better check why
         return E_POINTER;
      }

      pThis->FireAfterAdd(pitem);

	   return S_OK;
   }
   static HRESULT UndoAddLoad(_ThisClass* pThis,AddLoadParams& params)
   {
      ContainerIteratorType it = pThis->m_Container.find(params.ID);
      if ( it == pThis->m_Container.end() )
         return E_INVALIDARG;

      StoredType& item = it->second;
      return DoRemoveByID(pThis,item);
   }
   static HRESULT DoRemoveByID(_ThisClass* pThis,StoredType& item)
   {
      HRESULT hr = pThis->OnBeforeRemove(item);
      if ( FAILED(hr) )
         return hr;

      IDType ID;
      item->get_ID(&ID);
      auto nRemoved = pThis->m_Container.erase(ID);
      ATLASSERT(nRemoved == 1);

      pThis->FireAfterRemove();

	   return S_OK;
   }
   static HRESULT UndoRemoveLoad(_ThisClass* pThis,StoredType& item)
   {
      IDType ID;
      item->get_ID(&ID);
      std::pair<ContainerIteratorType,bool> st;
      st = pThis->m_Container.insert(ContainerValueType(ID, item));
      if (!st.second)
      {
         ATLASSERT(false); // insert failed - better check why
         return E_POINTER;
      }

      pThis->FireAfterAdd(item);
      return S_OK;
   }

   static HRESULT DoClear(_ThisClass* pThis,ContainerType& originalContainer)
   {
      for (ContainerIteratorType it= pThis->m_Container.begin(); it != pThis->m_Container.end(); it++)
      {
         pThis->OnBeforeRemove(it->second);
      }

      pThis->m_Container.clear();
      pThis->FireAfterRemove();

      return S_OK;
   }

   static HRESULT UndoClear(_ThisClass* pThis,ContainerType& originalContainer)
   {
      ATLASSERT(pThis->m_Container.size() == 0); // should be empty

      // fill up the current container with the original items
      // we have to re-establish the connection points because they were broken
      // when the container was cleared. Also, fire events after an item is loaded
      ContainerIteratorType iter;
      for ( iter = originalContainer.begin(); iter != originalContainer.end(); iter++ )
      {
         ContainerValueType& item = *iter;
         pThis->MakeConnection(dynamic_cast<CItemType*>(item.second.p));
         pThis->m_Container.insert(ContainerValueType(item.first, item.second));
         pThis->FireAfterAdd(item.second);
      }
      return S_OK;
   }

   struct RemoveStageParams
   {
      RemoveStageParams() {}
      RemoveStageParams(BSTR stage) : Stage(stage) {}
      CComBSTR Stage;
      ContainerType RemovedLoads;
   };
   static HRESULT DoRemoveStage(_ThisClass* pThis,RemoveStageParams& params)
   {
      if (params.Stage.Length() == 0)
         return E_INVALIDARG;

      // iterate through our collection and find matching items
      ContainerIteratorType cur = pThis->m_Container.begin();
      ContainerIteratorType end = pThis->m_Container.end();

      while( cur != end )
      {
         // we know that all ILoadItem's under our watch are CItemType's
         CItemType* pitm = dynamic_cast<CItemType*>(cur->second.p);
         if (pitm == 0)
         {
            ATLASSERT(false); // this should never happen since we are eating our own dog food here
            return E_FAIL;
         }

         if (params.Stage == pitm->m_Stage)
         {
            // found match, remove it
            HRESULT hr = pThis->OnBeforeRemove(pitm);
            if (FAILED(hr))
               return hr;

            // Hang onto the load so it can be put back on Undo
            params.RemovedLoads.insert(ContainerValueType(cur->first, cur->second));

            // have to be careful here since erase can reorder container
            cur = pThis->m_Container.erase(cur);
            end = pThis->m_Container.end();
            pThis->FireAfterRemove();
         }
         else
         {
            cur++;
         }
      }

      return S_OK;
   }

   static HRESULT UndoRemoveStage(_ThisClass* pThis,RemoveStageParams& params)
   {
      ContainerIteratorType iter;
      for ( iter = params.RemovedLoads.begin(); iter != params.RemovedLoads.end(); iter++ )
      {
         ContainerValueType& item = *iter;
         pThis->MakeConnection(dynamic_cast<CItemType*>(item.second.p));
         pThis->m_Container.insert(ContainerValueType(item.first, item.second));
         pThis->FireAfterAdd(item.second);
      }
      return S_OK;
   }
};


#endif //
