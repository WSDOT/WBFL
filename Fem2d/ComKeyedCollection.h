///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright � 1999-2025  Washington State Department of Transportation
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
         CComPtr<IUnknown> punk(pSource->second);
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
   using ContainerType = typename std::map<IDType, CComPtr<ItemType>>;
   using ContainerIteratorType = typename ContainerType::iterator;
   using ContainerValueType = typename ContainerType::value_type;
   ContainerType m_coll;

   using CopyVariantType = typename _CopyMapOfCComVariants<ContainerType>;
   using MapEnumType = typename CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, CopyVariantType, ContainerType >;
   using CustomCopyType = typename _CustomCopy<ContainerType, ItemType>;

public:
	CComKeyedCollection()
	{
	}

	virtual ~CComKeyedCollection()
	{
      ContainerIteratorType it(m_coll.begin());
      ContainerIteratorType itend(m_coll.end());
      for (; it != itend; it++)
      {
         it->second.Release();
      }
	}

   // from atl
	STDMETHOD(get_Count)(IndexType* pcount)
	{
		if (pcount == nullptr)
			return E_POINTER;
		*pcount = m_coll.size();
		return S_OK;
	}

	STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
	{
		if (ppUnk == nullptr)
			return E_POINTER;
		*ppUnk = nullptr;
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
   STDMETHOD(Remove)(/*[in]*/IndexType IDorIndex, /*[in]*/Fem2dAccessType AccessMethod,/*[out]*/IDType* pid)
   {
      CHECK_RETVAL(pid);

      if (AccessMethod==atID)
      {
         // erase by id
         auto it(m_coll.find(IDorIndex));
         if (it!=m_coll.end())
         {
            // must release element before erasing it
            it->second.Release();
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
         ATLASSERT(IDorIndex < (IndexType)m_coll.size());

         if (IDorIndex<0 || (IndexType)m_coll.size()<=IDorIndex)
         {
            return E_INVALIDARG;
         }
         else
         {
            // zero-based access
            auto it(m_coll.begin());
            for (IndexType i = 0; i<IDorIndex; i++)
            {
               it++;
            }
            *pid = it->first;
            it->second.Release();
            m_coll.erase(it);
         }
      }
	   return S_OK;
   }

	STDMETHOD(Find)(IDType id, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

      auto it(m_coll.find(id));
      if (it!=m_coll.end())
      {
         *pVal = it->second;
         (*pVal)->AddRef();
         return S_OK;
      }
      else
      {
         *pVal = nullptr;
      }

      return S_OK;
   }

	STDMETHOD(get__EnumElements)(/*[out, retval]*/ EnumType* *ppenum)
   {
      CHECK_RETOBJ(ppenum);

      using MyEnumType = CComEnumOnSTL<EnumType, piidenum, ItemType*, CustomCopyType, ContainerType>;
      CComObject<MyEnumType>* pEnum;
      HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
      if ( FAILED(hr) )
         return hr;

      hr = pEnum->Init( nullptr, m_coll );
      if ( FAILED(hr) )
         return hr;

      *ppenum = pEnum;
      (*ppenum)->AddRef(); // for client

      return S_OK;
   }

   STDMETHOD(get_Item)(IndexType idx, /*[out, retval]*/ ItemType* *pVal)
   {
      CHECK_RETOBJ(pVal);

		HRESULT hr = E_FAIL;

      if (idx<0 || (IndexType)m_coll.size()<=idx)
         return E_INVALIDARG;

 		// idx--; uncomment this line if you want one-based access
		auto iter(m_coll.begin());
		auto iterend(m_coll.end());
		while (iter != iterend && idx > 0)
		{
			iter++;
			idx--;
		}
		if (iter != iterend)
      {
         *pVal = iter->second;
         (*pVal)->AddRef();
         hr = S_OK;
      }

		return hr;
  }

   STDMETHOD(Clear)()
   {
      // release all members first, then clear
		auto it(m_coll.begin());
		auto itend(m_coll.end());
      for (; it != itend; it++)
      {
         it->second.Release();
      }

      m_coll.clear();
      return S_OK;
   }
/////////////
// Classes for local C++ clients
   StoredType* Find(IDType id)
   {
      auto it(m_coll.find(id));
      if (it!=m_coll.end())
      {
         // Get the COM pointer
         // Cast it to the C++ type
         StoredType* pItem = dynamic_cast<StoredType*>(it->second.p);
         return pItem;
      }
      else
      {
         return nullptr;
      }
   }



   // trimmed-down iterator class
   class iterator
   {
      friend CComKeyedCollection;

   public:
      iterator(const ContainerIteratorType& rit):
      m_it(rit)
      {;}

		iterator& operator++()
      {
         m_it++;			
         return (*this); 
      }

		iterator operator++(int)
      {
         iterator tmp(this->m_it);
			m_it++;
			return (tmp); 
      }

		StoredType* operator*() const
      {
         // Cast to the C++ type
         StoredType* pItem = dynamic_cast<StoredType*>(m_it->second.p);
         return pItem;
      }

		StoredType* operator->() const
      {
         // Cast to the C++ type
         StoredType* pItem = dynamic_cast<StoredType*>(m_it->second.p);
         return pItem;
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
      iterator it(m_coll.begin());
      return it;
   }

   iterator end()
   {
      iterator it(m_coll.end());
      return it;
   }
};



#endif //
