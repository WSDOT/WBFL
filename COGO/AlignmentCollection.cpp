///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// AlignmentCollection.cpp : Implementation of CAlignmentCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "AlignmentCollection.h"
#include "AlignmentFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlignmentCollection
HRESULT CAlignmentCollection::FinalConstruct()
{
   CComObject<CAlignmentFactory>* pFactory;
   CComObject<CAlignmentFactory>::CreateInstance(&pFactory);

   m_Factory = pFactory;
   return S_OK;
}

void CAlignmentCollection::FinalRelease()
{
   m_coll.clear();
}

STDMETHODIMP CAlignmentCollection::get_Item(CogoObjectID id, IAlignment **pVal)
{
   CHECK_RETVAL(pVal);
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return AlignmentNotFound(id);
   }

   std::pair<CogoObjectID,CComVariant> p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CAlignmentCollection::putref_Item(CogoObjectID id, IAlignment *newVal)
{
   CHECK_IN(newVal);

   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return AlignmentNotFound(id);
   }

   CComVariant& var = (*found).second;

   CComQIPtr<IAlignment> old_Alignment(var.pdispVal);
   var = newVal;

	return S_OK;
}

STDMETHODIMP CAlignmentCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
	return S_OK;
}

STDMETHODIMP CAlignmentCollection::Remove(CogoObjectID id)
{
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return AlignmentNotFound(id);
   }

   CComVariant& var = (*found).second;
   CComQIPtr<IAlignment> pp(var.pdispVal);

   m_coll.erase(found);

	return S_OK;
}

STDMETHODIMP CAlignmentCollection::Add(CogoObjectID id, IAlignment* *pAlignment)
{
   if ( pAlignment != nullptr )
   {
      CHECK_RETOBJ(pAlignment);
   }

   CComPtr<IAlignment> newAlignment;
   m_Factory->CreateAlignment(&newAlignment);

   if ( pAlignment != nullptr )
   {
      (*pAlignment) = newAlignment;
      (*pAlignment)->AddRef();
   }

   return AddEx(id,newAlignment);
}

STDMETHODIMP CAlignmentCollection::AddEx(CogoObjectID id, IAlignment* newVal)
{
   CHECK_IN(newVal);

   VARIANT_BOOL bIsValid;
   m_Factory->IsValidType(newVal,&bIsValid);
   if ( bIsValid != VARIANT_TRUE )
      return E_INVALIDARG;
   
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found != m_coll.end() )
   {
      return AlignmentAlreadyDefined(id);
   }

   CComQIPtr<IUnknown,&IID_IUnknown> pDisp(newVal);
   CComVariant var(pDisp);
   m_coll.insert(std::make_pair(id,var));

	return S_OK;
}

STDMETHODIMP CAlignmentCollection::Clear()
{
   m_coll.clear();
	return S_OK;
}

STDMETHODIMP CAlignmentCollection::FindID(IAlignment* pp,CogoObjectID* id)
{
   CHECK_IN(pp);
   CHECK_RETVAL(id);

   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      std::pair<CogoObjectID,CComVariant> item = *iter;
      CComQIPtr<IAlignment> value( item.second.pdispVal );
      ATLASSERT( value != nullptr );
      if ( value.IsEqualObject(pp) )
      {
         *id = item.first;
         return S_OK;
      }
   }

   return E_FAIL;
}

STDMETHODIMP CAlignmentCollection::get__EnumIDs(IEnumIDs** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumIDs,&IID_IEnumIDs, CogoObjectID, MapCopyID<std::map<CogoObjectID,CComVariant>>, std::map<CogoObjectID,CComVariant> > Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( nullptr, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( ppenum );

   return S_OK;
}

STDMETHODIMP CAlignmentCollection::ID(CollectionIndexType index,CogoObjectID* id)
{
   CHECK_RETVAL(id);

   if ( !IsValidIndex(index,m_coll) )
      return E_INVALIDARG;

   std::map<CogoObjectID,CComVariant>::iterator iter = m_coll.begin();
   for ( CollectionIndexType i = 0; i < index; i++ )
      iter++;

   std::pair<CogoObjectID,CComVariant> p = *iter;
   *id = p.first;

   return S_OK;
}

STDMETHODIMP CAlignmentCollection::get_Factory(IAlignmentFactory** factory)
{
   CHECK_RETOBJ(factory);

   (*factory) = m_Factory;
   (*factory)->AddRef();

   return S_OK;
}

STDMETHODIMP CAlignmentCollection::putref_Factory(IAlignmentFactory* factory)
{
   CHECK_IN(factory);
   m_Factory = factory;
   return S_OK;
}

STDMETHODIMP CAlignmentCollection::get__EnumAlignments(IEnumAlignments** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumAlignments,&IID_IEnumAlignments, IAlignment*, MapCopyValueToInterface<std::map<CogoObjectID,CComVariant>,IAlignment*>, std::map<CogoObjectID,CComVariant> > Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( nullptr, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( ppenum );

   return S_OK;
}

STDMETHODIMP CAlignmentCollection::Clone(IAlignmentCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CAlignmentCollection>* pClone;
   CComObject<CAlignmentCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CollectionIndexType count = 0;
   CComPtr<IEnumAlignments> enumAlignments;
   get__EnumAlignments(&enumAlignments);
   CComPtr<IAlignment> alignment;
   while ( enumAlignments->Next(1,&alignment,nullptr) != S_FALSE )
   {
      CComPtr<IAlignment> cloneAlignment;
      alignment->Clone(&cloneAlignment);

      CogoObjectID id;
      ID(count++,&id);

      (*clone)->AddEx(id,cloneAlignment);

      alignment.Release();
   };

   (*clone)->putref_Factory(m_Factory);

   return S_OK;
}

HRESULT CAlignmentCollection::AlignmentNotFound(CogoObjectID id)
{
   return AlignmentIDError(id,IDS_E_ALIGNMENTNOTFOUND,COGO_E_ALIGNMENTNOTFOUND);
}

HRESULT CAlignmentCollection::AlignmentAlreadyDefined(CogoObjectID id)
{
   return AlignmentIDError(id,IDS_E_ALIGNMENTALREADYDEFINED,COGO_E_ALIGNMENTALREADYDEFINED);
}

HRESULT CAlignmentCollection::AlignmentIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, id );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return CComCoClass<CAlignmentCollection,&CLSID_AlignmentCollection>::Error(oleMsg, IID_IAlignmentCollection, hRes);
}

HRESULT CAlignmentCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   pSave->put_Property(CComBSTR("AlignmentFactory"),CComVariant(m_Factory));
   return S_OK;
}

HRESULT CAlignmentCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->get_Property(CComBSTR("AlignmentFactory"),&var);
   m_Factory.Release();
   _CopyVariantToInterface<IAlignmentFactory>::copy(&m_Factory,&var);
   return S_OK;
}
