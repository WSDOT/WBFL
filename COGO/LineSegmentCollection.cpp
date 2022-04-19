///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2022  Washington State Department of Transportation
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

// LineSegmentCollection.cpp : Implementation of CLineSegmentCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "LineSegmentCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineSegmentCollection
HRESULT CLineSegmentCollection::FinalConstruct()
{
   return S_OK;
}

void CLineSegmentCollection::FinalRelease()
{
   m_coll.clear();
}

//STDMETHODIMP CLineSegmentCollection::InterfaceSupportsErrorInfo(REFIID riid)
//{
//	static const IID* arr[] = 
//	{
//		&IID_ILineSegmentCollection
//	};
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
//	{
//		if (InlineIsEqualGUID(*arr[i],riid))
//			return S_OK;
//	}
//	return S_FALSE;
//}

//STDMETHODIMP CLineSegmentCollection::get__NewEnum(IUnknown** retval)
//{
//   return S_OK;
//}

STDMETHODIMP CLineSegmentCollection::get_Item(CogoObjectID id, ILineSegment2d* *pVal)
{
   CHECK_RETVAL(pVal);
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return LineSegNotFound(id);
   }

   std::pair<CogoObjectID,CComVariant> p = *found;
   p.second.pdispVal->QueryInterface(pVal);

	return S_OK;
}

STDMETHODIMP CLineSegmentCollection::putref_Item(CogoObjectID id, ILineSegment2d* newVal)
{
   CHECK_IN(newVal);

   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return LineSegNotFound(id);
   }

   CComVariant& var = (*found).second;
   var = newVal;

	return S_OK;
}

STDMETHODIMP CLineSegmentCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
   return S_OK;
}

STDMETHODIMP CLineSegmentCollection::Add(CogoObjectID id, IPoint2d* start, IPoint2d* end,ILineSegment2d* *ls)
{
   CHECK_IN(start);
   CHECK_IN(end);

   if ( ls != nullptr )
   {
      CHECK_RETOBJ(ls);
   }

   CComPtr<ILineSegment2d> newLS;
   newLS.CoCreateInstance(CLSID_LineSegment2d);

   newLS->putref_StartPoint(start);
   newLS->putref_EndPoint(end);

   if ( ls != nullptr )
   {
      (*ls) = newLS;
      (*ls)->AddRef();
   }

   return AddEx(id,newLS);
}

STDMETHODIMP CLineSegmentCollection::AddEx(CogoObjectID id, ILineSegment2d* newVal)
{
   CHECK_IN(newVal);
   
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found != m_coll.end() )
   {
      return LineSegAlreadyDefined(id);
   }

   CComQIPtr<IUnknown,&IID_IUnknown> pDisp(newVal);
   CComVariant var(pDisp);
   m_coll.insert(std::make_pair(id,var));

	return S_OK;
}

STDMETHODIMP CLineSegmentCollection::Remove(CogoObjectID id)
{
   std::map<CogoObjectID,CComVariant>::iterator found;
   found = m_coll.find(id);
   if ( found == m_coll.end() )
   {
      return LineSegNotFound(id);
   }

   m_coll.erase(found);

	return S_OK;
}

STDMETHODIMP CLineSegmentCollection::Clear()
{
   m_coll.clear();
	return S_OK;
}

STDMETHODIMP CLineSegmentCollection::FindID(ILineSegment2d* ls, CogoObjectID* id)
{
   CHECK_IN(ls);
   CHECK_RETVAL(id);

   std::map<CogoObjectID,CComVariant>::iterator iter;
   for ( iter = m_coll.begin(); iter != m_coll.end(); iter++ )
   {
      std::pair<CogoObjectID,CComVariant> item = *iter;
      CComQIPtr<ILineSegment2d> value( item.second.pdispVal );
      ATLASSERT( value != nullptr );
      if ( value.IsEqualObject(ls) )
      {
         *id = item.first;
         return S_OK;
      }
   }

   return E_FAIL;
}

STDMETHODIMP CLineSegmentCollection::get__EnumIDs(IEnumIDs** ppenum)
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

STDMETHODIMP CLineSegmentCollection::get__EnumLineSegments(IEnumLineSegments** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumLineSegments,&IID_IEnumLineSegments, ILineSegment2d*, MapCopyValueToInterface<std::map<CogoObjectID,CComVariant>,ILineSegment2d*>, std::map<CogoObjectID,CComVariant> > Enum;
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

STDMETHODIMP CLineSegmentCollection::ID(CollectionIndexType index,CogoObjectID* id)
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

STDMETHODIMP CLineSegmentCollection::Clone(ILineSegmentCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CLineSegmentCollection>* pClone;
   CComObject<CLineSegmentCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   CollectionIndexType count = 0;
   CComPtr<IEnumLineSegments> enumLS;
   get__EnumLineSegments(&enumLS);
   CComPtr<ILineSegment2d> ls;
   while ( enumLS->Next(1,&ls,nullptr) != S_FALSE )
   {
      CComPtr<ILineSegment2d> cloneLS;
      cloneLS.CoCreateInstance(CLSID_LineSegment2d);

      CComPtr<IPoint2d> start;
      CComPtr<IPoint2d> end;
      ls->get_StartPoint(&start);
      ls->get_EndPoint(&end);

      CComPtr<IPoint2d> cloneStart;
      CComPtr<IPoint2d> cloneEnd;
      cloneLS->get_StartPoint(&cloneStart);
      cloneLS->get_EndPoint(&cloneEnd);

      cloneStart->MoveEx(start);
      cloneEnd->MoveEx(end);

      CogoObjectID id;
      ID(count++,&id);

      (*clone)->AddEx(id,cloneLS);

      ls.Release();
   };

   return S_OK;
}

HRESULT CLineSegmentCollection::LineSegNotFound(CogoObjectID id)
{
   return LineSegIDError(id,IDS_E_LINESEGMENTNOTFOUND,COGO_E_LINESEGMENTNOTFOUND);
}

HRESULT CLineSegmentCollection::LineSegAlreadyDefined(CogoObjectID id)
{
   return LineSegIDError(id,IDS_E_LINESEGMENTALREADYDEFINED,COGO_E_LINESEGMENTALREADYDEFINED);
}

HRESULT CLineSegmentCollection::LineSegIDError(CogoObjectID id,UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, id );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return CComCoClass<CLineSegmentCollection,&CLSID_LineSegmentCollection>::Error(oleMsg, IID_ILineSegmentCollection, hRes);
}

HRESULT CLineSegmentCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   //pSave->put_Property(CComBSTR("LineSegmentFactory"),CComVariant(m_Factory));
   return S_OK;
}

HRESULT CLineSegmentCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   //CComVariant var;
   //pLoad->get_Property(CComBSTR("LineSegmentFactory"),&var);
   //m_Factory.Release();
   //_CopyVariantToInterface<ILineSegment2dFactory>::copy(&m_Factory,&var);
   return S_OK;
}
