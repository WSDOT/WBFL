///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
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
// Fem2dCollection.h : 

#ifndef __FEM2DCOLLECTION_H_
#define __FEM2DCOLLECTION_H_

#include "ComKeyedCollection.h"

// These are collections specific to the Fem2d Package.

// template class specialized for Fem2d (may be useful for general cases later).
//////////////////////////////////////////////////////////

template <class T, class ItemType, class StoredType, class EnumType, const IID* piidenum,typename IDType>
class  CFem2dCollection : public CComKeyedCollection< T, ItemType, StoredType, EnumType, piidenum,IDType>
{
protected:
   // virtual function for initializing newly-created StoredTypes
   virtual void CallOnCreate(StoredType* pcreate)=0;

public:

   // saving and loading might work just as well as a mix-in feature. keep here for now
   virtual HRESULT Load(BSTR name, Float64 version, IStructuredLoad2 *pload)
   {
      HRESULT hr;
      hr = pload->BeginUnit(name);
      if (FAILED(hr))
         return hr;

      Float64 ver;
      hr = pload->get_Version(&ver);
      if (FAILED(hr))
         return hr;

      if (ver!=version)
         return STRLOAD_E_BADVERSION;

      // see how many joints we have
      CComVariant varlong;
      varlong.vt = VT_UI4;
      hr = pload->get_Property(CComBSTR("Count"),&varlong);
      if (FAILED(hr))
         return hr;

      CollectionIndexType count = varlong.ulVal;

      for (CollectionIndexType i=0; i<count; i++)
      {
         // create a new joint
         CComObject<StoredType>* pjnt;
         hr = CComObject<StoredType>::CreateInstance( &pjnt );
         if (FAILED(hr))
            return hr;

         CComPtr<ItemType> item(pjnt);

         // intialize using virtual function
         CallOnCreate(pjnt);

         // load
         hr = pjnt->Load(pload);
         if (FAILED(hr))
            return hr;

         IDType id;
         pjnt->get_ID(&id);

         // insert new joint
         std::pair<ContainerIteratorType, bool> st;
         st = m_coll.insert(ContainerValueType(id, item));
         if (!st.second)
         {
            ATLASSERT(0); // insert failed - better check why
            return E_FAIL;
         }
      }

      VARIANT_BOOL eb;
      hr = pload->EndUnit(&eb);
      if (FAILED(hr))
         return hr;

      if (eb!=VARIANT_TRUE)
         return STRLOAD_E_INVALIDFORMAT;

      return S_OK;
   }

   virtual HRESULT Save(BSTR name, Float64 version, IStructuredSave2 *save)
   {
      HRESULT hr;
      hr = save->BeginUnit(name, version);
      if (FAILED(hr))
         return hr;

      // save out count
      CollectionIndexType count = m_coll.size();
      hr = save->put_Property(CComBSTR("Count"),CComVariant(count));
      if (FAILED(hr))
         return hr;

      // cycle though collection and save members
      for (ContainerIteratorType it= m_coll.begin(); it != m_coll.end(); it++)
      {
         CComQIPtr<ItemType> item (it->second);
         StoredType* pItem = dynamic_cast<StoredType*>(item.p);
         hr = pItem->Save(save);
         //hr = it->second->Save(save);
         if (FAILED(hr))
            return hr;
      }

      hr = save->EndUnit();
      if (FAILED(hr))
         return hr;

      return S_OK;
   }
};


// Collection class for the main Model collections
class ModelEvents;

template <class T, class ItemType, class StoredType, class EnumType, const IID* piidenum,typename IDType>
class  CModelCollection : public CFem2dCollection< T, ItemType, StoredType, EnumType, piidenum,IDType>
{
protected:
   // will want to move this out when generalizing this class
   IFem2dModel* m_pModel; 
   ModelEvents* m_pEvents; // for sending events back to model

   // virtual function to create a new StoredType
   virtual void CallOnCreate(StoredType* pcreate)
   {
      ATLASSERT(m_pModel!=0 );
      pcreate->OnCreate(m_pModel, m_pEvents, -1);
   }

public:
   void InitCollection(IFem2dModel* pModel, ModelEvents* pEvents)
   {
      ATLASSERT(pModel!=0 );
      ATLASSERT(pEvents!=0 );
      m_pModel  = pModel;
      m_pEvents = pEvents;
   }
};

// Collection class for the IFem2dLoading collections
//class IFem2dLoading;

template <class T, class ItemType, class StoredType, class EnumType, const IID* piidenum,typename LOADIDTYPE>
class  CLoadsCollection : public CFem2dCollection< T, ItemType, StoredType, EnumType, piidenum,typename LOADIDTYPE>
{
protected:
   // will want to move this out when generalizing this class
   IFem2dModel* m_pModel; 
   ModelEvents* m_pEvents; // for sending events back to model
   IFem2dLoading* m_pLoading;

   // virtual function to create a new StoredType
   virtual void CallOnCreate(StoredType* pcreate)
   {
      ATLASSERT(m_pModel!=0 && m_pLoading!=0);
      pcreate->Init(m_pModel, m_pEvents, m_pLoading, -1);
   }

public:
   void InitCollection(IFem2dModel* pModel, ModelEvents* pEvents, IFem2dLoading* pLoading)
   {
      ATLASSERT(pModel!=0 && pLoading!=0);

      m_pModel = pModel;
      m_pEvents = pEvents;
      m_pLoading = pLoading;
   }
};

#endif //
