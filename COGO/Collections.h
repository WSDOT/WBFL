///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

#ifndef INCLUDED_COLLECTIONS_H_
#define INCLUDED_COLLECTIONS_H_
#pragma once

#include <map>

	template <class DestinationType, class SourceType = DestinationType>
	class GenericCopy
	{
	public :
		typedef DestinationType	destination_type;
		typedef SourceType		source_type;

		static void init(destination_type* p)
		{
			_Copy<destination_type>::init(p);
		}
		static void destroy(destination_type* p)
		{
			_Copy<destination_type>::destroy(p);
		}
		static HRESULT copy(destination_type* pTo, const source_type* pFrom)
		{
			return _Copy<destination_type>::copy(pTo, const_cast<source_type*>(pFrom));
		}

	}; // class GenericCopy

	template <class MapType, class DestinationType = MapType::referent_type>
	class MapCopy
	{
	public :
		typedef DestinationType			destination_type;
		typedef typename MapType::value_type		source_type;
		
		typedef MapType					map_type;
		typedef typename MapType::referent_type	pseudosource_type;

		static void init(destination_type* p)
		{
			GenericCopy<destination_type, pseudosource_type>::init(p);
		}
		static void destroy(destination_type* p)
		{
			GenericCopy<destination_type, pseudosource_type>::destroy(p);
		}
		static HRESULT copy(destination_type* pTo, const source_type* pFrom)
		{
			return GenericCopy<destination_type, pseudosource_type>::copy(pTo, &(pFrom->second));
		}

	}; // class MapCopy

   template <class InterfaceType>
   class UnpackageInterfaceFromVariant
   {
      public:
         static InterfaceType Unpack(const CComVariant& wrapper)
         {
            InterfaceType iface;
            wrapper.punkVal->QueryInterface(&iface); // calls AddRef(). Release() is called
                                                     // in the destroy() method of the copy policy object
            return iface;
         }
   };

	template <class MapType, class InterfaceType,class UnpackageType = UnpackageInterfaceFromVariant<InterfaceType> >
	class MapCopyValueToInterface
	{
	public :
		typedef InterfaceType			interface_type;
		typedef typename MapType::value_type		source_type;
		
		typedef MapType					map_type;
		typedef typename MapType::referent_type	pseudosource_type;

		static void init(interface_type* p)
		{
			GenericCopy<interface_type, pseudosource_type>::init(p);
		}
		static void destroy(interface_type* p)
		{
			//GenericCopy<interface_type, pseudosource_type>::destroy(p);
         if ( (*p) )
         {
            (*p)->Release();
            (*p) = NULL;
         }
		}
		static HRESULT copy(interface_type* pTo, const source_type* pFrom)
		{
         interface_type from(UnpackageType::Unpack(pFrom->second));
         (*pTo) = from;
         (*pTo)->AddRef();
         from->Release();
         return S_OK;
		}

	}; // class MapCopyValueToInterface

   template <class MapType>
	class MapCopyID
	{
	public :
		typedef typename MapType::value_type	source_type;
      typedef typename MapType::key_type     key_type;
		typedef MapType					map_type;

		static void init(key_type* p)
		{
			GenericCopy<key_type, key_type>::init(p);
		}
		static void destroy(key_type* p)
		{
			GenericCopy<key_type, key_type>::destroy(p);
		}
		static HRESULT copy(key_type* pTo, const source_type* pFrom)
		{
         return GenericCopy<key_type,key_type>::copy(pTo,&(*pFrom).first);
		}

	}; // class MapCopyID

   template <class PairType,class DestinationType=PairType::first_type>
   class CopyFromPair1
   {
   public:
      typedef PairType pair_type;
      typedef typename PairType::first_type first_type;
      typedef typename PairType::second_type second_type;
      typedef DestinationType destination_type;

      static void init(destination_type* p)
      {
         GenericCopy<destination_type,destination_type>::init(p);
      }
      static void destroy(destination_type* p)
      {
         GenericCopy<destination_type,destination_type>::destroy(p);
      }
		static HRESULT copy(destination_type* pTo, const destination_type* pFrom)
		{
         return GenericCopy<destination_type,destination_type>::copy(pTo,&(*pFrom).first);
		}
   };

   template <class PairType,class DestinationType=PairType::second_type>
   class CopyFromPair2
   {
   public:
      typedef PairType pair_type;
      typedef typename PairType::first_type first_type;
      typedef typename PairType::second_type second_type;
      typedef DestinationType destination_type;

      static void init(second_type* p)
      {
         GenericCopy<destination_type,destination_type>::init(p);
      }
      static void destroy(destination_type* p)
      {
         GenericCopy<destination_type,destination_type>::destroy(p);
      }
		static HRESULT copy(destination_type* pTo,const pair_type* pFrom)
		{
         return GenericCopy<destination_type,destination_type>::copy(pTo,&(*pFrom).second);
		}
   };

   template <class PairType,class InterfaceType,class UnpackageType = UnpackageInterfaceFromVariant<InterfaceType> >
   class CopyFromPair2Interface
   {
   public:
      typedef PairType pair_type;
      typedef typename PairType::first_type first_type;
      typedef typename PairType::second_type second_type;
      typedef InterfaceType interface_type;

      static void init(second_type* p)
      {
         GenericCopy<interface_type,interface_type>::init(p);
      }
      static void destroy(interface_type* p)
      {
         if ( (*p) )
         {
            (*p)->Release();
            (*p) = NULL;
         }
      }
		static HRESULT copy(interface_type* pTo, const pair_type* pFrom)
		{
         interface_type from(UnpackageType::Unpack(pFrom->second));
         (*pTo) = from;
         (*pTo)->AddRef();
         from->Release();
         return S_OK;
		}
   };

//typedef std::map<CogoObjectID,CComVariant> MyMap;
//typedef CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, MapCopy<std::map<IDType,Iitem>,VARIANT>, std::map<IDType,Iitem> > MapEnum;

template <class T,class Icoll,const IID* piid,typename IDType,class Iitem>
class PersistentIDCollection :
   public ICollectionOnSTLImpl<Icoll,std::map<IDType,CComVariant>,VARIANT,MapCopy<std::map<IDType,CComVariant>,VARIANT>, CComEnumOnSTL<IEnumVARIANT,&IID_IEnumVARIANT, VARIANT, MapCopy<std::map<IDType,CComVariant>,VARIANT>, std::map<IDType,CComVariant> > >,
   public IStructuredStorage2,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<T,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IPersistImpl<T>
{
public:
   typedef PersistentIDCollection<T,Icoll,piid,IDType,Iitem> _ThisClass;

   PersistentIDCollection<T,Icoll,piid,IDType,Iitem>(Float64 colVersion=1.0,Float64 itemVersion=1.0)
   {
      m_CollectionVersion = colVersion;
      m_ItemVersion = itemVersion;
   }

   Float64 m_CollectionVersion;
   Float64 m_ItemVersion;

BEGIN_COM_MAP(_ThisClass)
	COM_INTERFACE_ENTRY(Icoll)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

   virtual CComBSTR GetCollectionName() { return CComBSTR("Collection"); }
   virtual CComBSTR GetItemName() { return CComBSTR("Item"); }

   virtual HRESULT OnBeforeSave(IStructuredSave2* pSave) { return S_OK; }
   virtual HRESULT OnAfterSave(IStructuredSave2* pSave) { return S_OK; }
   virtual HRESULT OnBeforeLoad(IStructuredLoad2* pLoad) { return S_OK; }
   virtual HRESULT OnAfterLoad(IStructuredLoad2* pLoad) { return S_OK; }

   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
   {
	   static const IID* arr[] = 
	   {
		   piid,
         &IID_IStructuredStorage2,
	   };
	   for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	   {
		   if (InlineIsEqualGUID(*arr[i],riid))
			   return S_OK;
	   }
	   return S_FALSE;
   }

   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *stg)
   {
      CHECK_RETOBJ(stg);
      return QueryInterface(IID_IStructuredStorage2,(void**)stg);
   }

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave)
   {
      CHECK_IN(pSave);
      HRESULT hr;

      pSave->BeginUnit(GetCollectionName(),m_CollectionVersion);
 
      // save anything you want to prior to saving the stuff in the collection
      hr = OnBeforeSave(pSave);
      if ( FAILED(hr) )
         return hr;

      pSave->put_Property(CComBSTR("Count"),CComVariant(m_coll.size()));

      std::map<IDType,CComVariant>::const_iterator iter;
      CComBSTR bstrItemName(GetItemName());
      for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
      {
         pSave->BeginUnit(bstrItemName,m_ItemVersion);

         const std::pair<IDType,CComVariant>& pair = *iter;
         pSave->put_Property(CComBSTR("ID"),CComVariant(pair.first));
         pSave->put_Property(CComBSTR("Value"),CComVariant(pair.second));

         pSave->EndUnit();
      }

      // save anything you want to after to saving the stuff in the collection
      hr = OnAfterSave(pSave);
      if ( FAILED(hr) )
         return hr;

      pSave->EndUnit();

      return S_OK;
   }

   STDMETHOD(Load)(IStructuredLoad2* pLoad)
   {
      CHECK_IN(pLoad);

      CComVariant var;
      VARIANT_BOOL bEnd;
      HRESULT hr;

      pLoad->BeginUnit(GetCollectionName());

      hr = OnBeforeLoad(pLoad);
      if ( FAILED(hr) )
         return hr;

      CollectionIndexType count;
      pLoad->get_Property(CComBSTR("Count"),&var);
      count = var.lVal;

      for ( CollectionIndexType i = 0; i < count; i++ )
      {
         IDType ID;
         pLoad->BeginUnit(GetItemName());

         pLoad->get_Property(CComBSTR("ID"),&var);
         ID = (IDType)var.lVal;

         pLoad->get_Property(CComBSTR("Value"),&var);
         CComPtr<Iitem> point;
         _CopyVariantToInterface<Iitem>::copy(&point,&var);

         AddEx(ID,point);

         pLoad->EndUnit(&bEnd);
      }

      hr = OnAfterLoad(pLoad);
      if ( FAILED(hr) )
         return hr;

      pLoad->EndUnit(&bEnd);

      return S_OK;
   }
};

#endif // INCLUDED_COLLECTIONS_H_