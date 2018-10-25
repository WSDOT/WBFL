///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 2003  Washington State Department of Transportation
//                   Bridge and Structures Office
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
// 4500 3rd Ave SE, P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


// CComCollections.h

#ifndef __WBFLCComCollections_H_
#define __WBFLCComCollections_H_

#pragma once

#include <vector>
#include <map>
#include <AtlMapCopy.h>
#include <algorithm>
#include <atlcom.h>
#include <WBFLTools.h>
#include <typeinfo.h>
#include <WBFLAtlExt.h>
#include <WBFLTypes.h>

// some useful error messages
#define WCC_E_NAME_ALREADY_EXISTS      				     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1492)
#define WCC_E_BLANK_NAMES_NOT_ALLOWED  				     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,1493)

template <class ContainerType,typename IndexType>
bool IsValidIndex(IndexType index,const ContainerType& container)
{
   return (0 <= index && index < (IndexType)(container.size()));
}

// Misc Copy classes
template <class T>
class _CopyVariantFromInterfacePair
{
public:
   static HRESULT copy(VARIANT* pv, const T* ppair)
   {
      HRESULT hr = ppair->second.m_T->QueryInterface(IID_IDispatch, (void**)&pv->pdispVal);
      if (SUCCEEDED(hr))
         pv->vt = VT_DISPATCH;

      return hr;
   }

   static void init(VARIANT*) {}
   static void destroy(VARIANT* p) { VariantClear(p); }
};

template <class T, class TPair>
class _CopyInterfacePair
{
public:
	static HRESULT copy(T** p1, const TPair* p2)
	{
		*p1 = (p2->second).m_T;
		if (*p1)
			(*p1)->AddRef();
		return S_OK;
	}
	static void init(T** ) {}
	static void destroy(T** p) {if (*p) (*p)->Release();}
};


template <class T>
class _CopyVariantFromInterfacePairPair
{
public:
   static HRESULT copy(VARIANT* pv, const T* ppair)
   {
      HRESULT hr = ppair->second.second.m_T->QueryInterface(IID_IDispatch, (void**)&pv->pdispVal);
      if (SUCCEEDED(hr))
         pv->vt = VT_DISPATCH;

      return hr;
   }

   static void init(VARIANT*) {}
   static void destroy(VARIANT* p) { VariantClear(p); }
};

template <class T, class TPair>
class _CopyInterfacePairPair
{
public:
	static HRESULT copy(T** p1, const TPair* p2)
	{
		*p1 = p2->second.second.m_T;
		if (*p1)
			(*p1)->AddRef();
		return S_OK;
	}
	static void init(T** ) {}
	static void destroy(T** p) {if (*p) (*p)->Release();}
};



template <class InterfaceType>
class _CopyInterfaceToVariant
{
   public:
      static HRESULT copy(VARIANT* vDest, const InterfaceType* pSource)
      {
         CComVariant vSource(*pSource);
         return ::VariantCopy(vDest,&vSource);
      }

      static void init(InterfaceType*) {}
      static void destroy(VARIANT* var) {}
};


//////////////////////////////////////////////////////////
// Persistant collection of COM Interfaces
template <class Tderived, class TColl,class IndexType>
class  ATL_NO_VTABLE CPersistentCollection : 

   // CPersistentCollection to be derived from IStructuredStorage2
   public IStructuredStorage2,

   // The rest of the collection interface is implemented by TColl
   // CPersistentCollection needs access to the members functions on TColl.
   // In order to accomplish this, it must inherit from TColl (which it does via
   // IDispatchImpl).  However, this means that children cannot
   // derive directly, or indirectly from both TColl and CPersistentCollection.
   // If it does, children will be inheriting from TColl twice.
   // This will result in ambiguous methods
   public TColl,
   public IPersistImpl<Tderived>
{
public:
   // Added Interface Map here so that clients don't have to remember to
   // build it. However clients do have to add
   // COM_INTERFACE_ENTRY_CHAIN(CPersistentCollection<Tderived,TColl,Version>)
   // to their interface maps.
   //
   // This chains their primary map to this secondary map
   typedef typename CPersistentCollection<Tderived,TColl,IndexType> _ThisClass;
   BEGIN_COM_MAP(_ThisClass)
      COM_INTERFACE_ENTRY(IStructuredStorage2)

      COM_INTERFACE_ENTRY(TColl::CollectionType)

      COM_INTERFACE_ENTRY(IPersist)
   END_COM_MAP()

protected:
   CPersistentCollection<Tderived,TColl,IndexType>()
   {
      m_Version = 1.0;
   }


   // Virtual functions to describe collection name, version and stored objects
   // Override these if you want prettier names than typeid gives you
   virtual CComBSTR GetCollectionName()
   {
      const type_info& t = typeid(CollectionType);
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

   virtual void SetVersion(Float64 version)
   {
      m_Version = version;
   }

   virtual CComBSTR GetStoredName()
   {
      const type_info& t = typeid(TColl::ItemType);
      // string is in the form "struct Name". Need to get rid of the "struct " part
      const char* nm = t.name();
      nm += 7;
      std::string name(nm);

      return CComBSTR(nm);
   }


   // virtual function for initializing newly-created StoredTypes
   virtual void CallOnCreate(typename TColl::ItemType* pcreate)
   {;} // do nothing by default - don't force client to overload this if they don't need it

   // virtual functions that allow you to save and load additional properties along with your collection
   virtual HRESULT SaveAdditionalProperties(IStructuredSave2 *save)
   {return S_OK;}
   virtual HRESULT LoadAdditionalProperties(IStructuredLoad2 *load)
   {return S_OK;}

public:
   // IStructuredStorage2
   // Load from storage
   virtual HRESULT STDMETHODCALLTYPE Load(IStructuredLoad2 *pload)
   {
      CHECK_IN(pload);

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

      // allow children to save properties
      hr = LoadAdditionalProperties(pload);
      if (FAILED(hr))
         return hr;

      // see how many items we have
      CComVariant varlong;
      hr = pload->get_Property(CComBSTR("Count"),&varlong);
      if (FAILED(hr))
         return hr;

      IndexType count = (IndexType)varlong.lVal;

      for (IndexType i=0; i<count; i++)
      {
         CComPtr<TColl::ItemType> pitm;
         DoLoadItem(pload,&pitm);

         // add new item
         this->Add(pitm);
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

   virtual HRESULT STDMETHODCALLTYPE Save(IStructuredSave2 *save)
   {
      CHECK_IN(save);

      HRESULT hr;
      hr = save->BeginUnit(GetCollectionName(), GetVersion() );
      if (FAILED(hr))
         return hr;

      // allow children to save properties
      hr = SaveAdditionalProperties(save);
      if (FAILED(hr))
         return hr;

      // save out count
      IndexType count;
      this->get_Count(&count);
      hr = save->put_Property(CComBSTR("Count"),CComVariant(count));
      if (FAILED(hr))
         return hr;

      // cycle though collection and save members
      for (iterator it= begin(); it != end(); it++)
      {
         CComPtr<ItemType> value = it->second;
         hr = DoSaveItem(save,value);
         if (FAILED(hr))
            return hr;
      }

      hr = save->EndUnit();
      if (FAILED(hr))
         return hr;

      return S_OK;
   }

protected:

   // Override these methods if the item in the collection cannot be stored/restored directly
   virtual HRESULT DoSaveItem(IStructuredSave2* save,typename TColl::ItemType* item)
   {
      return save->put_Property(GetStoredName(),CComVariant(item));
   }

   virtual HRESULT DoLoadItem(IStructuredLoad2* load,typename TColl::ItemType* *ppItem)
   {
      // get item from store
      CComVariant var;
      HRESULT hr = load->get_Property(GetStoredName(), &var);
      if (FAILED(hr))
         return hr;

      _CopyVariantToInterface<TColl::ItemType>::copy(ppItem, &var);

      // intialize using virtual function
      CallOnCreate(*ppItem);

      return S_OK;
   }

private:
   CComBSTR m_Name;
   Float64 m_Version;
};


/////////////////////////////////////////////////////////////////////////////
// CComVectorCollectionNoEnum
template <class T, class ItemType,class IndexType>
class  CComVectorCollectionNoEnum :
public T
{
public:

   // typedef used by CPersistentCollection to identify the interface
   // of the collection
   typedef T                                     CollectionType;
   typedef ItemType                              ItemType;
   // Store a cookie along with interface pointer to facilitate dealing with connection points
   // Could have externalized this to make more extensible
   typedef std::pair< DWORD, CAdapt<CComPtr<ItemType>>>          StoredType; // <cookie, pointer>

protected:
   // some virtual methods for dealing with adding and 
   // removing items from this collection
   // Default implementation is "do nothing"
   virtual HRESULT OnBeforeAdd( StoredType* pVal) { return S_OK; }
   virtual HRESULT OnAfterAdd( StoredType* pVal, IndexType idx) { return S_OK; }
   virtual HRESULT OnBeforeRemove( StoredType* pVal, IndexType idx) { return S_OK; }
   virtual HRESULT OnAfterRemove( IndexType idx) { return S_OK; }
   virtual HRESULT OnBeforeReplace( StoredType* pVal, IndexType idx) { return S_OK; }
   virtual HRESULT OnAfterReplace( StoredType* pVal, IndexType idx) { return S_OK; }
   virtual HRESULT OnBeforeClear() { return S_OK; }
   virtual HRESULT OnAfterClear() { return S_OK; }

protected:
   typedef typename std::vector< StoredType >             ContainerType;
   typedef typename ContainerType::iterator               ContainerIteratorType;
   ContainerType m_coll;

   typedef typename _CopyInterfacePair<ItemType,StoredType> CustomCopyType;
   typedef typename _CopyVariantFromInterfacePair<StoredType> CopyType;

public:
	CComVectorCollectionNoEnum()
	{
	}

	virtual ~CComVectorCollectionNoEnum()
	{
	}

   // count
	STDMETHOD(get_Count)(IndexType* pcount)
	{
      CHECK_RETVAL(pcount);

      *pcount = m_coll.size();
		return S_OK;
	}

   STDMETHOD(Reverse)()
   {
      std::reverse(m_coll.begin(),m_coll.end());
      return S_OK;
   }

   // add a new element
	STDMETHOD(Add)(ItemType* pVal)
	{
      CHECK_IN(pVal);

      HRESULT hr;

      StoredType store( 0, CAdapt<CComPtr<ItemType>>(pVal));
      hr = OnBeforeAdd(&store);
		if (FAILED(hr))
         return hr;

      // add
      m_coll.push_back( store );

      StoredType& realStoredItem = m_coll.back();

      return OnAfterAdd(&realStoredItem,IndexType(m_coll.size()-1));
   }

   // insert a new element
	STDMETHOD(Insert)(IndexType index, ItemType* pVal)
	{
      CHECK_IN(pVal);

      HRESULT hr;

      if ( index < 0 || (IndexType)m_coll.size() < index ) // ok to insert at end of collection
         return E_INVALIDARG;

      StoredType store( 0, CAdapt<CComPtr<ItemType>>(pVal));
      hr = OnBeforeAdd(&store);
		if (FAILED(hr))
         return hr;

      // erase by index
      ContainerType::iterator it( m_coll.begin() );
      it += index;

      ContainerType::iterator insertLoc( m_coll.insert(it, store) );

      StoredType& realStoredItem = *insertLoc;

      return OnAfterAdd(&realStoredItem,index);
   }

	STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
	{
      CHECK_RETOBJ(ppUnk);

		*ppUnk = NULL;
		HRESULT hRes = S_OK;

      typedef typename CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyType, ContainerType > VecEnumType;
		CComObject<VecEnumType>* p;
		hRes = CComObject<VecEnumType>::CreateInstance(&p);
		if (SUCCEEDED(hRes))
		{
			hRes = p->Init(this, m_coll);
			if (hRes == S_OK)
				hRes = p->QueryInterface(IID_IUnknown, (void**)ppUnk);
		}
		if (hRes != S_OK)
			delete p;
		return hRes;
	}

   STDMETHOD(Remove)(/*[in]*/IndexType index)
   {
      if (!IsValidIndex(index,m_coll))
         return E_INVALIDARG;

      // erase by index
      ContainerType::iterator it( m_coll.begin() );
      it += index;

  		HRESULT hr = S_OK;
      hr = OnBeforeRemove(&*it, index);  // veto rights 
		if (SUCCEEDED(hr))
		{
         m_coll.erase(it);
      }

      return OnAfterRemove(index);
   }


   STDMETHOD(get_Item)(IndexType idx, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

		HRESULT hr = S_OK;

      if (!IsValidIndex(idx,m_coll))
         return E_INVALIDARG;

      StoredType& rs = m_coll[idx];

      hr = CustomCopyType::copy(pVal, &rs);
      if ( FAILED(hr) )
         return hr;

      ATLASSERT(*pVal!=0);

		return hr;
  }

   STDMETHOD(putref_Item)(IndexType idx, ItemType* newVal)
   {
      CHECK_IN(newVal);

		HRESULT hr = S_OK;

      if (!IsValidIndex(idx,m_coll))
         return E_INVALIDARG;

      StoredType& rs = m_coll[idx];
      OnBeforeReplace(&rs,idx);
      rs.second = newVal;
      OnAfterReplace(&rs,idx);

		return hr;
  }

   STDMETHOD(Clear)()
   {
      // can't use a standard for loop since we are erasing as we iterate
      IndexType idx=0;
      bool go = true;
      OnBeforeClear();
      while (go)
      {
         ContainerIteratorType it( m_coll.begin() );
         ContainerIteratorType itend( m_coll.end() );
         if (it!=itend)
         {
  		      HRESULT hr = S_OK;
            hr = OnBeforeRemove(&*it, idx);
		      if (SUCCEEDED(hr))
		      {
               m_coll.erase(it);
            }
            else
            {
               return hr;
            }

            hr = OnAfterRemove(idx++);
            if (FAILED(hr))
               return hr;
         }
         else
         {
            go = false; // done with loop
         }
      }
      OnAfterClear();

      return S_OK;
   }

   STDMETHOD(Reserve)(IndexType size)
   {
      // allocate some space to optimize use of collection if possible
      if (size < 0)
         return E_INVALIDARG;

      m_coll.reserve(size);

      return S_OK;
   }


/////////////
// Classes for local C++ clients
protected:

   // trimmed-down iterator class
   class iterator
   {
      friend CComVectorCollectionNoEnum;

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

		StoredType* operator*() const
      {
         return &(*m_it);
      }

		StoredType* operator->() const
      {
         return &(*m_it);
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
      it.m_it = m_coll.begin();
      return it;
   }

   iterator end()
   {
      iterator it;
      it.m_it = m_coll.end();
      return it;
   }
}; // CComVectorCollectionNoEnum


/////////////////////////////////////////////////////////////////////////////
// CComVectorCollection
template <class T, class ItemType, class EnumType, const IID* piidenum,class IndexType>
class  CComVectorCollection :
public CComVectorCollectionNoEnum<T,ItemType,IndexType>
{
public:

	STDMETHOD(get__EnumElements)(/*[out, retval]*/ EnumType* *ppenum)
   {
      CHECK_RETOBJ(ppenum);

      typedef typename CComEnumOnSTL<EnumType, piidenum, ItemType*, CustomCopyType, ContainerType> MyEnumType;
      CComObject<MyEnumType>* pEnum;
      HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
      if ( FAILED(hr) )
         return hr;

      CComPtr<EnumType> pHolder(pEnum); // memory leak avoidance

      hr = pEnum->Init( NULL, m_coll );
      if ( FAILED(hr) )
         return hr;

      *ppenum = pEnum;
      (*ppenum)->AddRef(); // for client

      return S_OK;
   }
}; // CComVectorCollection


/////////////////////////////////////////////////////////////////////////////
// CComSegmentCollection
template <class T, class ItemType, class EnumType, const IID* piidenum,class IndexType>
class  CComSegmentCollection : public T
{
public:

   // typedef's used to identify the interface of the collection and its items
   typedef T                                             CollectionType;
   typedef ItemType                                      ItemType;
   // Store a cookie along with interface pointer to facilitate dealing with connection points
   // Could have externalized this to make more extensible
   typedef typename std::pair< DWORD, CAdapt<CComPtr<ItemType>>> StoredType; // <cookie, pointer>

protected:
   // some virtual methods for allowing parents to deal with adding and 
   // removing items from this collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal) { return S_OK; }
   virtual HRESULT OnAfterAdd( StoredType* pVal, IndexType index) { return S_OK; }
   virtual HRESULT OnBeforeRemove( StoredType* pVal, IndexType index) { return S_OK; }
   virtual HRESULT OnAfterRemove( IndexType index) { return S_OK; }
   virtual HRESULT OnAfterMoveTo( IndexType from, IndexType to) { return S_OK; }
   virtual HRESULT OnAfterCopyTo( IndexType from, IndexType to) { return S_OK; }
   virtual HRESULT OnAfterReverse() { return S_OK; }

private:
   typedef typename std::vector< StoredType >             ContainerType;
   typedef typename ContainerType::iterator               ContainerIteratorType;
   ContainerType m_coll;

   typedef typename _CopyInterfacePair<ItemType,StoredType> CustomCopyType;
   typedef typename _CopyVariantFromInterfacePair<StoredType> CopyType;

public:
	CComSegmentCollection()
	{
	}

	virtual ~CComSegmentCollection()
	{
	}

   // count
	STDMETHOD(get_Count)(IndexType* pcount)
	{
      CHECK_RETVAL(pcount);

      *pcount = m_coll.size();

		return S_OK;
	}

   // add a new element
	STDMETHOD(Add)(ItemType* pVal)
	{
      CHECK_IN(pVal);

      HRESULT hr;

      StoredType store( 0, CAdapt<CComPtr<ItemType>>(pVal));
      hr = OnBeforeAdd(&store);
		if (FAILED(hr))
         return hr;

      // add
      m_coll.push_back( store );

      StoredType& realStoredItem = m_coll.back();
      return OnAfterAdd(&realStoredItem,m_coll.size()-1);
   }

   // insert a new element
	STDMETHOD(Insert)(IndexType index, ItemType* pVal)
	{
      HRESULT hr;

      if ( index < 0 || m_coll.size() < index ) // ok to insert at end of collection
         return E_INVALIDARG;

      CHECK_IN(pVal);

      StoredType store( 0, CAdapt<CComPtr<ItemType>>(pVal));
      hr = OnBeforeAdd(&store);
		if (FAILED(hr))
         return hr;

      // insert by index
      ContainerType::iterator it( m_coll.begin() );
      it += index;

      ContainerType::iterator insertLoc( m_coll.insert(it, store) );
      StoredType& realStoredItem = *insertLoc;
      return OnAfterAdd(&realStoredItem, index);
   }

   // move an element from one location to another
	STDMETHOD(MoveTo)(IndexType fromIndex, IndexType toIndex)
	{
      // check bounds
      if ((fromIndex < 0 || (IndexType)m_coll.size() <= fromIndex) || 
          (toIndex   < 0 || (IndexType)m_coll.size() <=  toIndex  ))
         return E_INVALIDARG;

      // do nothing if from==to
      if (fromIndex == toIndex)
         return S_OK;

      // make temporary copy
      StoredType store( m_coll[fromIndex] );

      // erase by index
      ContainerType::iterator it( m_coll.begin() );
      it += fromIndex;

      m_coll.erase(it);

      // insert by index
      it = m_coll.begin();
      it += toIndex;

      m_coll.insert(it, store);

      return OnAfterMoveTo(fromIndex, toIndex);
   }

   // copy an element from one location to another
   STDMETHOD(CopyTo)(IndexType fromIndex, IndexType toIndex)
	{
      // check bounds
      if ((fromIndex < 0 || (IndexType)m_coll.size() <= fromIndex) || 
          (toIndex   < 0 || (IndexType)m_coll.size() <  toIndex  ))
         return E_INVALIDARG;

      // make temporary copy
      StoredType store( m_coll[fromIndex] );

      HRESULT hr = OnBeforeAdd(&store);
		if (FAILED(hr))
         return hr;

      // insert by index
      ContainerType::iterator it( m_coll.begin() );
      it += toIndex;

      m_coll.insert(it, store);

      return OnAfterCopyTo(fromIndex, toIndex);
   }

   STDMETHOD(Remove)(/*[in]*/IndexType index)
   {
      if ( !IsValidIndex(index,m_coll) )
         return E_INVALIDARG;

      // erase by index
      ContainerType::iterator it( m_coll.begin() );
      it += index;

  		HRESULT hr = S_OK;
      hr = OnBeforeRemove(&*it, index);  // veto rights 
		if (SUCCEEDED(hr))
		{
         m_coll.erase(it);
         return OnAfterRemove(index);
      }
      else
         ATLASSERT(0); // may want to remove this if vetoing on purpose

      return S_OK;
   }

	STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
	{
		if (ppUnk == NULL)
			return E_POINTER;

		*ppUnk = NULL;
		HRESULT hRes = S_OK;

      typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyType, ContainerType > VecEnumType;
		CComObject<VecEnumType>* p;
		hRes = CComObject<VecEnumType>::CreateInstance(&p);
		if (SUCCEEDED(hRes))
		{
			hRes = p->Init(this, m_coll);
			if (hRes == S_OK)
				hRes = p->QueryInterface(IID_IUnknown, (void**)ppUnk);
		}
		if (hRes != S_OK)
			delete p;
		return hRes;
	}

   STDMETHOD(get__EnumElements)(/*[out, retval]*/ EnumType* *ppenum)
   {
      CHECK_RETOBJ(ppenum);

      typedef typename CComEnumOnSTL<EnumType, piidenum, ItemType*, CustomCopyType, ContainerType> MyEnumType;
      CComObject<MyEnumType>* pEnum;
      HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
      if ( FAILED(hr) )
         return hr;

      CComPtr<EnumType> pHolder(pEnum); // memory leak avoidance

      hr = pEnum->Init( NULL, m_coll );
      if ( FAILED(hr) )
         return hr;

      *ppenum = pEnum;
      (*ppenum)->AddRef(); // for client

      return S_OK;
   }

   STDMETHOD(get_Item)(IndexType idx, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

		HRESULT hr = S_OK;

      if ( !IsValidIndex(idx,m_coll) )
         return E_INVALIDARG;

      StoredType& rs = m_coll[idx];

      hr = CustomCopyType::copy(pVal, &rs);
      if ( FAILED(hr) )
         return hr;

      ATLASSERT(*pVal!=0);

		return hr;
  }

   STDMETHOD(putref_Item)(IndexType idx, /*[in]*/ ItemType* pVal)
   {
      CHECK_IN(pVal);

		HRESULT hr = S_OK;

      if ( !IsValidIndex(idx,m_coll) )
         return E_INVALIDARG;

      hr = this->Remove(idx);
      if (FAILED(hr))
         return hr;

      hr = this->Insert(idx, pVal);
      if (FAILED(hr))
         return hr;

		return hr;
  }


   STDMETHOD(Clear)()
   {
      // can't use a standard for loop since we are erasing as we iterate
      IndexType idx=0;
      bool go = true;
      while (go)
      {
         ContainerIteratorType it( m_coll.begin() );
         ContainerIteratorType itend( m_coll.end() );
         if (it!=itend)
         {
  		      HRESULT hr = S_OK;
            hr = OnBeforeRemove(&*it, idx);
		      if (SUCCEEDED(hr))
		      {
               m_coll.erase(it);

               hr = OnAfterRemove(idx++);
               if (FAILED(hr))
                  return hr;
            }
            else
            {
               return hr;
            }

         }
         else
         {
            go = false; // done with loop
         }
      }

      return S_OK;
   }

   STDMETHOD(Reverse)()
   {
      if (m_coll.size() < 2)
         return S_OK;

      std::reverse(m_coll.begin(), m_coll.end());

      return OnAfterReverse();
   }


/////////////
// Classes for local C++ clients
protected:

   // trimmed-down iterator class
   class iterator
   {
      friend CComSegmentCollection;

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

		StoredType* operator*() const
      {
         return &(*m_it);
      }

		StoredType* operator->() const
      {
         return &(*m_it);
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
      it.m_it = m_coll.begin();
      return it;
   }

   iterator end()
   {
      iterator it;
      it.m_it = m_coll.end();
      return it;
   }

   StoredType* back()
   {
      ATLASSERT(!m_coll.empty());
      return &(m_coll.back());
   }

}; // CComSegmentCollection



/////////////////////////////////////////////////////////////////////////////
// CComBSTRKeyedCollection
template <class T, class ItemType, class EnumType, const IID* piidenum,class IndexType>
class  CComBSTRKeyedCollection : public T
{
public:
   // typedef's used to identify the interface of the collection and its items
   typedef T                                             CollectionType;
   typedef ItemType                                      ItemType;
   // Store a cookie along with interface pointer to facilitate dealing with connection points
   // Could have externalized this to make more extensible
   typedef std::pair< unsigned long, CAdapt<CComPtr<ItemType>>> StoredType; // <cookie, pointer>

protected:
   typedef typename std::map<CComBSTR, StoredType>  ContainerType;
   typedef typename ContainerType::iterator     ContainerIteratorType;
   typedef typename ContainerType::value_type   ContainerValueType;
   ContainerType m_coll;

   typedef typename _CopyInterfacePairPair<ItemType,ContainerValueType> CustomCopyType;
   typedef typename _CopyVariantFromInterfacePairPair<ContainerValueType> CopyType;

public:
	CComBSTRKeyedCollection()
	{
	}

	virtual ~CComBSTRKeyedCollection()
	{
	}

   // some virtual methods for dealing with adding and 
   // removing items from this collection
protected:
   virtual HRESULT OnBeforeAdd ( StoredType* pVal) {return S_OK;}
   virtual HRESULT OnAfterAdd ( StoredType* pVal) {return S_OK;}
   virtual HRESULT OnBeforeRemove ( StoredType* pVal) {return S_OK;}
   virtual HRESULT OnAfterRemove ( BSTR name) {return S_OK;}

public:
   // count
	STDMETHOD(get_Count)(IndexType* pcount)
	{
      CHECK_RETVAL(pcount);

      *pcount = m_coll.size();
		return S_OK;
	}

   // add a new element
	STDMETHOD(Add)(ItemType* pVal)
	{
      CHECK_IN(pVal);

      CComBSTR name;
      HRESULT hr;
      hr = pVal->get_Name(&name);
		if (FAILED(hr))
         return E_FAIL;

      // zero length names are no good
      if (name.Length()==0)
      {
         return WCC_E_BLANK_NAMES_NOT_ALLOWED;
      }

      // check if already in container
      ContainerIteratorType ifnd( m_coll.find(name) );
      if (ifnd != m_coll.end())
      {
         return WCC_E_NAME_ALREADY_EXISTS;
      }

      StoredType store( 0, CAdapt<CComPtr<ItemType>>(pVal));
      hr = OnBeforeAdd(&store);
		if (FAILED(hr))
         return hr;

      // insert 
      std::pair<ContainerIteratorType, bool> st( m_coll.insert(ContainerValueType(name, store)) );
      if (!st.second)
      {
         ATLASSERT(0); // insert failed - better check why
         return E_FAIL;
      }

      StoredType& realStoredItem = (*st.first).second;
      return OnAfterAdd(&realStoredItem);
   }

	STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
	{
      CHECK_RETOBJ(ppUnk);

		*ppUnk = NULL;
		HRESULT hRes = S_OK;

      typedef typename CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyType, ContainerType > VecEnumType;
		CComObject<VecEnumType>* p;
		hRes = CComObject<VecEnumType>::CreateInstance(&p);
		if (SUCCEEDED(hRes))
		{
			hRes = p->Init(this, m_coll);
			if (hRes == S_OK)
				hRes = p->QueryInterface(IID_IUnknown, (void**)ppUnk);
		}
		if (hRes != S_OK)
			delete p;
		return hRes;
	}

   STDMETHOD(get__EnumElements)(/*[out, retval]*/ EnumType* *ppenum)
   {
      CHECK_RETOBJ(ppenum);

      typedef typename CComEnumOnSTL<EnumType, piidenum, ItemType*, CustomCopyType, ContainerType> MyEnumType;
      CComObject<MyEnumType>* pEnum;
      HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
      if ( FAILED(hr) )
         return hr;

      CComPtr<EnumType> pHolder(pEnum); // memory leak avoidance

      hr = pEnum->Init( NULL, m_coll );
      if ( FAILED(hr) )
         return hr;

      *ppenum = pEnum;
      (*ppenum)->AddRef(); // for client

      return S_OK;
   }


public:
   STDMETHOD(RemoveByName)(/*[in]*/BSTR name)
   {
      CHECK_IN(name);

      // erase by id
      ContainerIteratorType it( m_coll.find(name) );
      if (it!=m_coll.end())
      {
         // must release element before erasing it
  		   HRESULT hr = S_OK;
         hr = OnBeforeRemove(&(it->second));
		   if (SUCCEEDED(hr))
		   {
            m_coll.erase(it);
         }
         OnAfterRemove(name);
         return S_OK;
      }

      return E_INVALIDARG;
   }

   STDMETHOD(RemoveByIndex)(/*[in]*/IndexType Index,/*[out]*/BSTR* name)
   {
      CHECK_RETSTRING(name);

      // erase by index
      if ( !IsValidIndex(Index,m_coll) )
      {
         return E_INVALIDARG;
      }
      else
      {
         // zero-based access
         ContainerIteratorType it( m_coll.begin() );
         for (IndexType i=0; i<Index; i++)
         {
            it++;
         }

         *name = (it->first).Copy();

  		   HRESULT hr = S_OK;
         hr = OnBeforeRemove(&(it->second));
		   if (SUCCEEDED(hr))
		   {
            m_coll.erase(it);
         }
          OnAfterRemove(*name);
      }

	   return S_OK;
   }

	STDMETHOD(Find)(BSTR name, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_IN(name);
      CHECK_RETOBJ(pVal);

      HRESULT hrResult = S_OK;
      ContainerIteratorType it( m_coll.find(name) );
      if (it!=m_coll.end())
      {
         CComPtr<ItemType> pi;

         HRESULT hr = CustomCopyType::copy(&pi, &*it);
         if ( FAILED(hr) )
            return hr;

         ATLASSERT(pi!=0);
         (*pVal) = pi;
         (*pVal)->AddRef();
         hrResult = S_OK;
      }
      else
      {
         *pVal = NULL;
         hrResult = E_FAIL;
      }

      return hrResult;
   }


   STDMETHOD(get_Item)(IndexType idx, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

		HRESULT hr = E_FAIL;

      if ( !IsValidIndex(idx,m_coll) )
         return E_INVALIDARG;

 		// idx--; uncomment this line if you want one-based access
		ContainerType::iterator iter( m_coll.begin() );
		ContainerType::iterator iterend( m_coll.end() );
		while (iter != iterend && idx > 0)
		{
			iter++;
			idx--;
		}

		if (iter != iterend)
      {
         // have to be able to cast ItemType to ItemType
         ItemType* pi = 0;

         hr = CustomCopyType::copy(&pi, &*iter);
         if ( FAILED(hr) )
            return hr;

         ATLASSERT(pi!=0);
         *pVal = pi;
      }

		return hr;
  }

   STDMETHOD(Clear)()
   {
      // release all members first, then clear
      ContainerIteratorType it( m_coll.begin() );
      ContainerIteratorType itend( m_coll.end() );
      for (; it != itend; it++)
      {
         CComBSTR name(it->first);
  		   HRESULT hr = S_OK;
         hr = OnBeforeRemove( &(it->second) );
		   if (FAILED(hr))
		   {
            return hr;
         }

         OnAfterRemove(name);
      }

      m_coll.clear();
      return S_OK;
   }
/////////////
// Classes for local C++ clients
   ItemType* Find(BSTR name)
   {
      ContainerIteratorType it( m_coll.find(name) );
      if (it!=m_coll.end())
      {
         return it->second.second;
      }
      else
         return 0;
   }

   // trimmed-down iterator class
   class iterator
   {
      friend CComBSTRKeyedCollection;

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

		StoredType* operator*() const
      {
         return &(m_it->second); 
      }

		StoredType* operator->() const
      {
         return &(m_it->second); 
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
      it.m_it = m_coll.begin();
      return it;
   }

   iterator end()
   {
      iterator it;
      it.m_it = m_coll.end();
      return it;
   }
}; // CComBSTRKeyedCollection

/////////////////////////////////////////////////////////////////////////////
// CComLongKeyedCollection
template <class T, class ItemType, class EnumType, const IID* piidenum,class KeyType>
class  CComLongKeyedCollection : public T
{
public:
   // typedef's used to identify the interface of the collection and its items
   typedef T                                             CollectionType;
   typedef ItemType                                      ItemType;
   // Store a cookie along with interface pointer to facilitate dealing with connection points
   // Could have externalized this to make more extensible
   typedef typename std::pair< DWORD, CAdapt<CComPtr<ItemType>>> StoredType; // <cookie, pointer>

protected:
   typedef typename std::map<KeyType, StoredType>  ContainerType;
   typedef typename ContainerType::iterator     ContainerIteratorType;
   typedef typename ContainerType::value_type   ContainerValueType;
   ContainerType m_coll;

   typedef typename _CopyInterfacePairPair<ItemType,ContainerValueType> CustomCopyType;
   typedef typename _CopyVariantFromInterfacePairPair<ContainerValueType> CopyType;

public:
	CComLongKeyedCollection()
	{
	}

	virtual ~CComLongKeyedCollection()
	{
	}

   // some virtual methods for dealing with adding and 
   // removing items from this collection
protected:
   virtual HRESULT OnBeforeAdd ( StoredType* pVal) {return S_OK;}
   virtual HRESULT OnAfterAdd ( StoredType* pVal) {return S_OK;}
   virtual HRESULT OnBeforeRemove ( StoredType* pVal) {return S_OK;}
   virtual HRESULT OnAfterRemove (KeyType key) {return S_OK;}

public:
   // count
	STDMETHOD(get_Count)(CollectionIndexType* pcount)
	{
      CHECK_RETVAL(pcount);

      *pcount = m_coll.size();
		return S_OK;
	}

   // add a new element
	STDMETHOD(Add)(ItemType* pVal)
	{
      CHECK_IN(pVal);
      KeyType id;
      HRESULT hr;
      hr = pVal->get_ID(&id);
		if (FAILED(hr))
         return E_FAIL;

      // check if already in container
      ContainerIteratorType ifnd( m_coll.find(id) );
      if (ifnd != m_coll.end())
      {
         return WCC_E_NAME_ALREADY_EXISTS;
      }

      StoredType store( 0, CAdapt<CComPtr<ItemType>>(pVal));
      hr = OnBeforeAdd(&store);
		if (FAILED(hr))
         return hr;

      // insert 
      std::pair<ContainerIteratorType, bool> st( m_coll.insert(ContainerValueType(id, store)) );
      if (!st.second)
      {
         ATLASSERT(0); // insert failed - better check why
         return E_FAIL;
      }

      StoredType& realStoredItem = (*st.first).second;
      return OnAfterAdd(&realStoredItem);
   }

	STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
	{
      CHECK_RETOBJ(ppUnk);

		*ppUnk = NULL;
		HRESULT hRes = S_OK;

      typedef typename CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyType, ContainerType > VecEnumType;
		CComObject<VecEnumType>* p;
		hRes = CComObject<VecEnumType>::CreateInstance(&p);
		if (SUCCEEDED(hRes))
		{
			hRes = p->Init(this, m_coll);
			if (hRes == S_OK)
				hRes = p->QueryInterface(IID_IUnknown, (void**)ppUnk);
		}
		if (hRes != S_OK)
			delete p;
		return hRes;
	}

   STDMETHOD(get__EnumElements)(/*[out, retval]*/ EnumType* *ppenum)
   {
      CHECK_RETOBJ(ppenum);

      typedef typename CComEnumOnSTL<EnumType, piidenum, ItemType*, CustomCopyType, ContainerType> MyEnumType;
      CComObject<MyEnumType>* pEnum;
      HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
      if ( FAILED(hr) )
         return hr;

      CComPtr<EnumType> pHolder(pEnum); // memory leak avoidance

      hr = pEnum->Init( NULL, m_coll );
      if ( FAILED(hr) )
         return hr;

      *ppenum = pEnum;
      (*ppenum)->AddRef(); // for client

      return S_OK;
   }


public:
   STDMETHOD(RemoveByKey)(/*[in]*/KeyType key)
   {
      // erase by id
      ContainerIteratorType it( m_coll.find(key) );
      if (it!=m_coll.end())
      {
         // must release element before erasing it
  		   HRESULT hr = S_OK;
         hr = OnBeforeRemove(&(it->second));
		   if (SUCCEEDED(hr))
		   {
            m_coll.erase(it);
         }
         OnAfterRemove(key);
         return S_OK;
      }

      return E_FAIL;
   }

   STDMETHOD(RemoveByIndex)(/*[in]*/CollectionIndexType Index,/*[out]*/KeyType* key)
   {
      CHECK_RETVAL(key);

      // erase by index
      if ( !IsValidIndex(Index,m_coll) )
      {
         return E_INVALIDARG;
      }
      else
      {
         // zero-based access
         ContainerIteratorType it( m_coll.begin() );
         for (CollectionIndexType i=0; i<Index; i++)
         {
            it++;
         }

         *key = it->first;

  		   HRESULT hr = S_OK;
         hr = OnBeforeRemove(&(it->second));
		   if (SUCCEEDED(hr))
		   {
            m_coll.erase(it);
         }
          OnAfterRemove(*key);
      }

	   return S_OK;
   }

	STDMETHOD(Find)(KeyType key, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

      HRESULT hrResult = S_OK;

      ContainerIteratorType it( m_coll.find(key) );
      if (it!=m_coll.end())
      {
         CComPtr<ItemType> pi;

         HRESULT hr = CustomCopyType::copy(&pi, &*it);
         if ( FAILED(hr) )
            return hr;

         ATLASSERT(pi!=0);
         (*pVal) = pi;
         (*pVal)->AddRef();

         hrResult = S_OK;
      }
      else
      {
         *pVal = NULL;
         hrResult = E_FAIL;
      }

      return hrResult;
   }


   STDMETHOD(get_Item)(CollectionIndexType idx, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

		HRESULT hr = E_FAIL;

      if ( !IsValidIndex(idx,m_coll) )
         return E_INVALIDARG;

 		// idx--; uncomment this line if you want one-based access
		ContainerType::iterator iter( m_coll.begin() );
		ContainerType::iterator iterend( m_coll.end() );
		while (iter != iterend && idx > 0)
		{
			iter++;
			idx--;
		}

		if (iter != iterend)
      {
         // have to be able to cast ItemType to ItemType
         ItemType* pi = 0;

         hr = CustomCopyType::copy(&pi, &*iter);
         if ( FAILED(hr) )
            return hr;

         ATLASSERT(pi!=0);
         *pVal = pi;
      }

		return hr;
  }

   STDMETHOD(Clear)()
   {
      // release all members first, then clear
      ContainerIteratorType it( m_coll.begin() );
      ContainerIteratorType itend( m_coll.end() );
      for (; it != itend; it++)
      {
         SIZE_T id = it->first;
  		   HRESULT hr = S_OK;
         hr = OnBeforeRemove( &(it->second) );
		   if (FAILED(hr))
		   {
            return hr;
         }

         OnAfterRemove(id);
      }

      m_coll.clear();
      return S_OK;
   }
/////////////
// Classes for local C++ clients
   ItemType* Find(KeyType id)
   {
      ContainerIteratorType it( m_coll.find(id) );
      if (it!=m_coll.end())
      {
         return it->second.second;
      }
      else
         return 0;
   }

   // trimmed-down iterator class
   class iterator
   {
      friend CComLongKeyedCollection;

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

		StoredType* operator*() const
      {
         return &(m_it->second); 
      }

		StoredType* operator->() const
      {
         return &(m_it->second); 
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
      it.m_it = m_coll.begin();
      return it;
   }

   iterator end()
   {
      iterator it;
      it.m_it = m_coll.end();
      return it;
   }
}; // CComLongKeyedCollection


/////////////////////////////////////////////////////////////////////////////
// CComIDKeyedCollection
template <class T, class ItemType, class EnumType, const IID* piidenum,class IndexType>
class  CComIDKeyedCollection : public T
{
public:
   // typedef's used to identify the interface of the collection and its items
   typedef T                                             CollectionType;
   typedef ItemType                                      ItemType;
   // Store a cookie along with interface pointer to facilitate dealing with connection points
   // Could have externalized this to make more extensible
   typedef typename std::pair< DWORD, CAdapt<CComPtr<ItemType>>> StoredType; // <cookie, pointer>

protected:
   typedef typename std::map<IDType, StoredType>  ContainerType;
   typedef typename ContainerType::iterator     ContainerIteratorType;
   typedef typename ContainerType::value_type   ContainerValueType;
   ContainerType m_coll;

   typedef typename _CopyInterfacePairPair<ItemType,ContainerValueType> CustomCopyType;
   typedef typename _CopyVariantFromInterfacePairPair<ContainerValueType> CopyType;

public:
	CComIDKeyedCollection()
	{
	}

	virtual ~CComIDKeyedCollection()
	{
	}

   // some virtual methods for dealing with adding and 
   // removing items from this collection
protected:
   virtual HRESULT OnBeforeAdd ( StoredType* pVal) {return S_OK;}
   virtual HRESULT OnAfterAdd ( StoredType* pVal) {return S_OK;}
   virtual HRESULT OnBeforeRemove ( StoredType* pVal) {return S_OK;}
   virtual HRESULT OnAfterRemove (IDType ID) {return S_OK;}

public:
   // count
	STDMETHOD(get_Count)(IndexType* pcount)
	{
      CHECK_RETVAL(pcount);

      *pcount = m_coll.size();
		return S_OK;
	}

   // add a new element
	STDMETHOD(Add)(ItemType* pVal)
	{
      CHECK_IN(pVal);
      IDType id;
      HRESULT hr;
      hr = pVal->get_ID(&id);
		if (FAILED(hr))
         return E_FAIL;

      // check if already in container
      ContainerIteratorType ifnd(m_coll.find(id));
      if (ifnd != m_coll.end())
      {
         return WCC_E_NAME_ALREADY_EXISTS;
      }

      StoredType store( 0, CAdapt<CComPtr<ItemType>>(pVal));
      hr = OnBeforeAdd(&store);
		if (FAILED(hr))
         return hr;

      // insert 
      std::pair<ContainerIteratorType, bool> st(m_coll.insert(ContainerValueType(id, store)));
      if (!st.second)
      {
         ATLASSERT(0); // insert failed - better check why
         return E_FAIL;
      }

      StoredType& realStoredItem = (*st.first).second;
      return OnAfterAdd(&realStoredItem);
   }

	STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
	{
      CHECK_RETOBJ(ppUnk);

		*ppUnk = NULL;
		HRESULT hRes = S_OK;

      typedef typename CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyType, ContainerType > VecEnumType;
		CComObject<VecEnumType>* p;
		hRes = CComObject<VecEnumType>::CreateInstance(&p);
		if (SUCCEEDED(hRes))
		{
			hRes = p->Init(this, m_coll);
			if (hRes == S_OK)
				hRes = p->QueryInterface(IID_IUnknown, (void**)ppUnk);
		}
		if (hRes != S_OK)
			delete p;
		return hRes;
	}

   STDMETHOD(get__EnumElements)(/*[out, retval]*/ EnumType* *ppenum)
   {
      CHECK_RETOBJ(ppenum);

      typedef typename CComEnumOnSTL<EnumType, piidenum, ItemType*, CustomCopyType, ContainerType> MyEnumType;
      CComObject<MyEnumType>* pEnum;
      HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
      if ( FAILED(hr) )
         return hr;

      CComPtr<EnumType> pHolder(pEnum); // memory leak avoidance

      hr = pEnum->Init( NULL, m_coll );
      if ( FAILED(hr) )
         return hr;

      *ppenum = pEnum;
      (*ppenum)->AddRef(); // for client

      return S_OK;
   }


public:
   STDMETHOD(RemoveByID)(/*[in]*/IDType id)
   {
      // erase by id
      ContainerIteratorType it(m_coll.find(id));
      if (it!=m_coll.end())
      {
         // must release element before erasing it
  		   HRESULT hr = S_OK;
         hr = OnBeforeRemove(&(it->second));
		   if (SUCCEEDED(hr))
		   {
            m_coll.erase(it);
         }
         OnAfterRemove(id);
         return S_OK;
      }

      return E_FAIL;
   }

   STDMETHOD(RemoveByIndex)(/*[in]*/IndexType Index,/*[out]*/IDType* ID)
   {
      CHECK_RETVAL(ID);

      // erase by index
      if ( !IsValidIndex(Index,m_coll) )
      {
         return E_INVALIDARG;
      }
      else
      {
         // zero-based access
         ContainerIteratorType it(m_coll.begin());
         for (IndexType i=0; i<Index; i++)
         {
            it++;
         }

         *ID = it->first;

  		   HRESULT hr = S_OK;
         hr = OnBeforeRemove(&(it->second));
		   if (SUCCEEDED(hr))
		   {
            m_coll.erase(it);
         }
          OnAfterRemove(*ID);
      }

	   return S_OK;
   }

	STDMETHOD(Find)(IDType ID, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

      HRESULT hrResult = S_OK;

      ContainerIteratorType it(m_coll.find(ID));
      if (it!=m_coll.end())
      {
         CComPtr<ItemType> pi;

         HRESULT hr = CustomCopyType::copy(&pi, &*it);
         if ( FAILED(hr) )
            return hr;

         ATLASSERT(pi!=0);
         (*pVal) = pi;
         (*pVal)->AddRef();

         hrResult = S_OK;
      }
      else
      {
         *pVal = NULL;
         hrResult = E_FAIL;
      }

      return hrResult;
   }


   STDMETHOD(get_Item)(IndexType idx, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

		HRESULT hr = E_FAIL;

      if ( !IsValidIndex(idx,m_coll) )
         return E_INVALIDARG;

 		// idx--; uncomment this line if you want one-based access
		ContainerType::iterator iter( m_coll.begin() );
		ContainerType::iterator end( m_coll.end() );
		while (iter != end && idx > 0)
		{
			iter++;
			idx--;
		}
		if (iter != end)
      {
         // have to be able to cast ItemType to ItemType
         ItemType* pi = 0;

         hr = CustomCopyType::copy(&pi, &*iter);
         if ( FAILED(hr) )
            return hr;

         ATLASSERT(pi!=0);
         *pVal = pi;
      }

		return hr;
  }

   STDMETHOD(Clear)()
   {
      // release all members first, then clear
      ContainerIteratorType it(m_coll.begin());
      ContainerIteratorType end(m_coll.end());
      for ( ; it != end; it++ )
      {
         IDType id = it->first;
  		   HRESULT hr = S_OK;
         hr = OnBeforeRemove( &(it->second) );
		   if (FAILED(hr))
		   {
            return hr;
         }

         OnAfterRemove(id);
      }

      m_coll.clear();
      return S_OK;
   }
/////////////
// Classes for local C++ clients
   ItemType* Find(IDType id)
   {
      ContainerIteratorType it(m_coll.find(id));
      if (it!=m_coll.end())
      {
         return it->second.second;
      }
      else
         return 0;
   }

   // trimmed-down iterator class
   class iterator
   {
      friend CComIDKeyedCollection;

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

		StoredType* operator*() const
      {
         return &(m_it->second); 
      }

		StoredType* operator->() const
      {
         return &(m_it->second); 
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
      it.m_it = m_coll.begin();
      return it;
   }

   iterator end()
   {
      iterator it;
      it.m_it = m_coll.end();
      return it;
   }
}; // CComIDKeyedCollection

#endif //__WBFLCComCollections_H_
