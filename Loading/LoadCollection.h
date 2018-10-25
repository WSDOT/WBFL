///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2011  Washington State Department of Transportation
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
#include "TxnMgrImpl.h"

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

   STDMETHOD(get_ID)(long *pVal)
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

         m_ID = var.lVal;

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
   long                m_ID;

   unsigned long       m_LoadCookie; // for events
};


///////////////////////////////////////////
// Custom transactions
template <class T,class ItemType,class LoadType>
class ATL_NO_VTABLE CSwapLoadTxn:
public CTransactionImpl<T,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading>
{
public:
   typedef HRESULT (*PutPropFunc)(T* pThis,ItemType* item,LoadType* newLoad);

void Init(T* pTarget,LPCTSTR strName,PutPropFunc putFunc,ItemType* item,LoadType* newLoad)
   {
      CTransactionImpl<T,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading>::Init(pTarget,strName);
      m_PutFunc = putFunc;
      m_Item    = item;
      m_NewLoad = newLoad;
      m_Item->get_Load(&m_OldLoad);
   }

   STDMETHOD(Execute)()
   {
      return m_PutFunc(m_pTarget,m_Item,m_NewLoad);
   }

	STDMETHOD(Undo)()
   {
      return m_PutFunc(m_pTarget,m_Item,m_OldLoad);
   }

protected:
   PutPropFunc m_PutFunc;
   CComPtr<LoadType> m_NewLoad;
   CComPtr<LoadType> m_OldLoad;
   CComPtr<ItemType> m_Item;
};

///////////////////////////////////////
// The collection class
template <class T, const IID* piidT, class TDerived, class LoadType, class IItemType, class CItemType,
          class EnumType, const IID* piidEnum>
class  CLoadCollection :
   public T,
   public IStructuredStorage2,
   public ISupportTransactionsImpl,
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
   typedef typename std::map<long, StoredType> ContainerType;
   typedef typename ContainerType::iterator    ContainerIteratorType;
   typedef typename ContainerType::value_type  ContainerValueType;

   ContainerType m_Container; // key value pair
   long          m_LastUniqueKey;

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

      ContainerIteratorType it = m_Container.begin();
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

   STDMETHOD(get_Load)(long ID, LoadType* *pVal)
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

   STDMETHOD(putref_Load)(long ID, LoadType* newLoad)
   {
      ContainerIteratorType it = m_Container.find(ID);
      if ( it == m_Container.end() )
         return E_INVALIDARG;

      CComPtr<IItemType> pItem = (*it).second;

      HRESULT hr;
      if ( m_TxnMgr )
      {
         typedef CSwapLoadTxn<_ThisClass,IItemType,LoadType> CPutLoadTxn;
         CComObject<CPutLoadTxn>* pTxn;
         CComObject<CPutLoadTxn>::CreateInstance(&pTxn);
         pTxn->Init(this,_T("Put Load"),&DoPutLoad,pItem,newLoad);

         return m_TxnMgr->Execute(pTxn);
      }
      else
      {
         hr = DoPutLoad(this,pItem,newLoad);
      }

	return hr;
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

   STDMETHOD(Add)(BSTR Stage, BSTR LoadGroup, LoadType * pLoad)
   {
      CHECK_IN(Stage);
      CHECK_IN(LoadGroup);
      CHECK_IN(pLoad);

      long ID = ++m_LastUniqueKey;
      typedef AddLoadParams Parameters;
      Parameters parameters(ID,Stage,LoadGroup,pLoad);

      HRESULT hr;
      if ( m_TxnMgr )
      {
         typedef CActionTransaction1<_ThisClass,Parameters,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CAddLoadTxn;
         CComObject<CAddLoadTxn>* pTxn;
         CComObject<CAddLoadTxn>::CreateInstance(&pTxn);
         pTxn->Init(this,_T("Add Load"),DoAddLoad,UndoAddLoad,parameters);
         hr = m_TxnMgr->Execute(pTxn);
      }
      else
      {
         hr = DoAddLoad(this,parameters);
      }
      return hr;

   }

   STDMETHOD(Find)(long ID, IItemType ** retVal )
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

   STDMETHOD(RemoveByID)(long ID)
   {
      // Get the item to remove
      ContainerIteratorType iter = m_Container.find(ID);
      if ( iter == m_Container.end() )
         return S_FALSE; // Not found

      StoredType item = iter->second;

      HRESULT hr;
      if ( m_TxnMgr )
      {
         typedef CActionTransaction1<_ThisClass,StoredType,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CRemoveByIDTxn;
         CComObject<CRemoveByIDTxn>* pTxn;
         CComObject<CRemoveByIDTxn>::CreateInstance(&pTxn);
         pTxn->Init(this,_T("Remove Load"),DoRemoveByID,UndoRemoveLoad,item);
         hr = m_TxnMgr->Execute(pTxn);
      }
      else
      {
         hr = DoRemoveByID(this,item);
      }
      return hr;
   }

   STDMETHOD(RemoveByIndex)(CollectionIndexType index)
   {
      // NOTE: If this is undone, the item will be put back in the container,
      //       but its index will change.
      if ( !IsValidIndex(index,m_Container) )
         return E_INVALIDARG;

      // run the iterator throught the container
      ContainerIteratorType iter = m_Container.begin();
      for (CollectionIndexType i=0; i<index; i++, iter++)
      ;
   
      ATLASSERT(iter != m_Container.end()); // should be past at end because of check on index above
      
      StoredType item = iter->second;
      long ID;
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
               hr = pcoll->Add(pitm->m_Stage, pitm->m_LoadGroup, pitm->m_Load);
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
      for (ContainerIteratorType it= m_Container.begin(); it != m_Container.end(); it++)
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

         hr = pnew->Add(pitem->m_Stage, pitem->m_LoadGroup, isp);
         if (FAILED(hr))
            return hr;
      }

      *pColl = pnew;
      (*pColl)->AddRef();

      // Set the transaction manager
      CComQIPtr<ISupportTransactions> supTxns(*pColl);
      if ( supTxns )
         supTxns->putref_TransactionMgr(m_TxnMgr);

      return S_OK;
   }

   STDMETHOD(Clear)()
   {
      HRESULT hr;
      if ( m_TxnMgr )
      {
         typedef CActionTransaction1<_ThisClass,ContainerType,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CClearTxn;
         CComObject<CClearTxn>* pTxn;
         CComObject<CClearTxn>::CreateInstance(&pTxn);
         pTxn->Init(this,_T("Clear Loads"),DoClear,UndoClear,m_Container);
         hr = m_TxnMgr->Execute(pTxn);
      }
      else
      {
         hr = DoClear(this,m_Container);
      }
      return hr;
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
      CHECK_IN(stage);
      RemoveStageParams parameters(stage);
      HRESULT hr;
      if ( m_TxnMgr )
      {
         typedef CActionTransaction1<_ThisClass,RemoveStageParams,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLLoading> CRemoveStageTxn;
         CComObject<CRemoveStageTxn>* pTxn;
         CComObject<CRemoveStageTxn>::CreateInstance(&pTxn);
         pTxn->Init(this,_T("Remove Stage"),DoRemoveStage,UndoRemoveStage,parameters);
         hr = m_TxnMgr->Execute(pTxn);
      }
      else
      {
         hr = DoRemoveStage(this,parameters);
      }
      return hr;
   }

   STDMETHOD(SwapLoad)(IItemType* item, LoadType* newVal)
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

      long count = varlong.lVal;
      m_LastUniqueKey = 1;
      for (long i=0; i<count; i++)
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
         pitem->m_Load = NULL;

         hr = SwapLoad(pitem, tmp);
         if (FAILED(hr))
            return hr;

         // insert new member
         std::pair<ContainerIteratorType,bool> st;
         st = m_Container.insert(ContainerValueType(pitem->m_ID, pitem));
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
      hr = save->put_Property(CComBSTR("Count"),CComVariant(count));
      if (FAILED(hr))
         return hr;

      // cycle though collection and save members
      for (ContainerIteratorType it=m_Container.begin(); it!=m_Container.end(); it++)
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

   //////////////////////////////////////////////
   // ISupportTransactions 
   STDMETHOD(putref_TransactionMgr)(ITransactionMgr* txnMgr)
   {
      HRESULT hr = ISupportTransactionsImpl::putref_TransactionMgr(txnMgr);
      if ( FAILED(hr) )
         return hr;

      // Set the transaction mgr on all the loads
      ContainerIteratorType iter;
      for ( iter = m_Container.begin(); iter != m_Container.end(); iter++ )
      {
         ContainerValueType& value = *iter;
         CComPtr<IItemType> item = value.second;
         CComPtr<LoadType> load;
         item->get_Load(&load);

         CComQIPtr<ISupportTransactions> supTxns(load);
         ATLASSERT(supTxns); // should be supporting Tranactions
         if ( supTxns )
            supTxns->putref_TransactionMgr(m_TxnMgr);
      }

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
      AddLoadParams(long id,BSTR stage,BSTR loadGroup,LoadType* pload) :
         ID(id), bstrStage(stage), bstrLoadGroup(loadGroup), Load(pload) {}

      long              ID;
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
         ATLASSERT(0); // insert failed - better check why
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

      long ID;
      item->get_ID(&ID);
      ContainerType::size_type nRemoved = pThis->m_Container.erase(ID);
      ATLASSERT(nRemoved == 1);

      pThis->FireAfterRemove();

	   return S_OK;
   }
   static HRESULT UndoRemoveLoad(_ThisClass* pThis,StoredType& item)
   {
      long ID;
      item->get_ID(&ID);
      std::pair<ContainerIteratorType,bool> st;
      st = pThis->m_Container.insert(ContainerValueType(ID, item));
      if (!st.second)
      {
         ATLASSERT(0); // insert failed - better check why
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
            ATLASSERT(0); // this should never happen since we are eating our own dog food here
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
