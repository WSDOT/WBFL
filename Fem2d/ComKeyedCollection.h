///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 2001  Washington State Department of Transportation
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
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// CComKeyedCollection.h : Declaration of the CCComKeyedCollection

#ifndef __CComKeyedCollection_H_
#define __CComKeyedCollection_H_
#pragma once

#include <map>
#include "AtlMapCopy.h"

#include <atlcom.h>


// Template class used for implementing collection in the Fem2d Package. 
// This class creates standard COM Collection classes. Derived classes need to be 
// fitted with a factory method or an add method to be complete

template <class ContainerType, class destType>
class _CustomCopy
{
   public:
      static HRESULT copy(destType** pDest, const typename ContainerType::value_type* pSource)
      {
         CComPtr<IUnknown> punk(pSource->second.punkVal);
         CComQIPtr<destType> dest(punk);
         if ( dest == 0 )
            return E_FAIL;

         *pDest = dest;
         (*pDest)->AddRef();

         return S_OK;
      }

      static void init(typename ContainerType::value_type*) {}
      static void destroy(destType**p ) {if (*p) (*p)->Release();}
};


/////////////////////////////////////////////////////////////////////////////
// CComKeyedCollection
template <class T, class ItemType, class StoredType, class EnumType, const IID* piidenum,typename IDType>
class  CComKeyedCollection : public T
{
protected:
   typedef typename std::map<IDType, CComVariant> ContainerType;
   typedef typename ContainerType::iterator     ContainerIteratorType;
   typedef typename ContainerType::value_type   ContainerValueType;
   ContainerType m_coll;

   typedef typename _CopyMapOfCComVariants<ContainerType> CopyVariantType;
   typedef typename CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, CopyVariantType, ContainerType > MapEnumType;

   typedef typename _CustomCopy<ContainerType, ItemType> CustomCopyType;

public:
	CComKeyedCollection()
	{
	}

	virtual ~CComKeyedCollection()
	{
      for (ContainerIteratorType it= m_coll.begin(); it != m_coll.end(); it++)
      {
         CComQIPtr<ItemType> item(it->second.punkVal);
         item.Release();
      }
	}

   // from atl
	STDMETHOD(get_Count)(CollectionIndexType* pcount)
	{
		if (pcount == NULL)
			return E_POINTER;
		*pcount = m_coll.size();
		return S_OK;
	}

	STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
	{
		if (ppUnk == NULL)
			return E_POINTER;
		*ppUnk = NULL;
		HRESULT hRes = S_OK;
		CComObject<MapEnumType>* p;
		hRes = CComObject<MapEnumType>::CreateInstance(&p);
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

public:
   STDMETHOD(Remove)(/*[in]*/CollectionIndexType IDorIndex, /*[in]*/Fem2dAccessType AccessMethod,/*[out]*/IDType* pid)
   {
      CHECK_RETVAL(pid);

      if (AccessMethod==atID)
      {
         // erase by id
         ContainerType::iterator it = m_coll.find(IDorIndex);
         if (it!=m_coll.end())
         {
            // must release element before erasing it
            CComQIPtr<ItemType> item(it->second.punkVal);
            item.Release();
            m_coll.erase(it);
            *pid=IDorIndex;
            return S_OK;
         }
         else
            return E_INVALIDARG;
      }
      else
      {
         // erase by index
         ATLASSERT(IDorIndex>=0);
         ATLASSERT(IDorIndex < (CollectionIndexType)m_coll.size());

         if (IDorIndex<0 || (CollectionIndexType)m_coll.size()<=IDorIndex)
         {
            return E_INVALIDARG;
         }
         else
         {
            // zero-based access
            ContainerType::iterator it = m_coll.begin();
            for (CollectionIndexType i=0; i<IDorIndex; i++)
            {
               it++;
            }
            *pid = it->first;
            CComQIPtr<ItemType> item(it->second.punkVal);
            item.Release();
            m_coll.erase(it);
         }
      }
	   return S_OK;
   }

	STDMETHOD(Find)(IDType id, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

      ContainerType::iterator it = m_coll.find(id);
      if (it!=m_coll.end())
      {
         CComQIPtr<ItemType> item(it->second.punkVal);
         *pVal = item;
         (*pVal)->AddRef();
         return S_OK;
      }
      else
      {
         *pVal = NULL;
      }

      return S_OK;
   }

	STDMETHOD(get__EnumElements)(/*[out, retval]*/ EnumType* *ppenum)
   {
      CHECK_RETOBJ(ppenum);

      typedef CComEnumOnSTL<EnumType, piidenum, ItemType*, CustomCopyType, ContainerType> MyEnumType;
      CComObject<MyEnumType>* pEnum;
      HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
      if ( FAILED(hr) )
         return hr;

      hr = pEnum->Init( NULL, m_coll );
      if ( FAILED(hr) )
         return hr;

      *ppenum = pEnum;
      (*ppenum)->AddRef(); // for client

      return S_OK;
   }

   STDMETHOD(get_Item)(CollectionIndexType idx, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

		HRESULT hr = E_FAIL;

      if (idx<0 || (CollectionIndexType)m_coll.size()<=idx)
         return E_INVALIDARG;

 		// idx--; uncomment this line if you want one-based access
		ContainerType::iterator iter = m_coll.begin();
		while (iter != m_coll.end() && idx > 0)
		{
			iter++;
			idx--;
		}
		if (iter != m_coll.end())
      {
         CComQIPtr<ItemType> item(iter->second.punkVal);
         *pVal = item;
         (*pVal)->AddRef();
         hr = S_OK;
      }

		return hr;
  }

   STDMETHOD(Clear)()
   {
      // release all members first, then clear
      for (ContainerIteratorType it= m_coll.begin(); it != m_coll.end(); it++)
      {
         CComQIPtr<ItemType> item(it->second.punkVal);
         item.Release();
      }

      m_coll.clear();
      return S_OK;
   }
/////////////
// Classes for local C++ clients
   StoredType* Find(IDType id)
   {
      ContainerType::iterator it = m_coll.find(id);
      if (it!=m_coll.end())
      {
         // Get the COM pointer
         CComQIPtr<ItemType> item(it->second.punkVal);

         // Cast it to the C++ type
         StoredType* pItem = dynamic_cast<StoredType*>(item.p);
         return pItem;

         //return it->second;
      }
      else
         return 0;
   }



   // trimmed-down iterator class
   class iterator
   {
      friend CComKeyedCollection;

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
         // Get the COM pointer
         CComQIPtr<ItemType> item(m_it->second.punkVal);

         // Cast it to the C++ type
         StoredType* pItem = dynamic_cast<StoredType*>(item.p);
         return pItem;

         //return m_it->second; 
      }

		StoredType* operator->() const
      {
         // Get the COM pointer
         CComQIPtr<ItemType> item(m_it->second.punkVal);

         // Cast it to the C++ type
         StoredType* pItem = dynamic_cast<StoredType*>(item.p);
         return pItem;

         //return m_it->second; 
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
};



#endif //
