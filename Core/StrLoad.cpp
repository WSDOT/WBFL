///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
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

// StrLoad.cpp : implementation file
//

#include "stdafx.h"
#include <WBFLCore.h> // COM generated file... in Include folder
//#include "core.h" // local header file with CCoreApp
#include "StrLoad.h"
#include <atlbase.h>
#include <WBFLAtlExt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrLoad

STDMETHODIMP CStrLoad::Open(LPCTSTR name)
{
   // Check if the file exists.  If we can't get its attributes, then
   // it probably isn't there.
   DWORD dwResult = GetFileAttributes(name);
   if ( dwResult == 0xFFFFFFFF )
      return STRLOAD_E_FILENOTFOUND;

   m_bOpen = TRUE;

   CComBSTR fnam(name);

   if ( !m_File.open( fnam ) )
      return STRLOAD_E_CANTOPEN;

   // :TODO: Error check stream
   try
   {
      m_StrLoad.BeginLoad( &m_File );
   }
   catch( sysXStructuredLoad& e )
   {
      return HandleException( e );
   }

	return S_OK;
}

STDMETHODIMP CStrLoad::BeginUnit(LPCTSTR name)
{
   try
   {
   if ( !m_StrLoad.BeginUnit( name ) )
      return STRLOAD_E_INVALIDFORMAT;
   }
   catch( sysXStructuredLoad& e )
   {
      return HandleException( e );
   }

	return S_OK;
}

STDMETHODIMP CStrLoad::EndUnit()
{
   HRESULT hr;
   try
   {
      hr = m_StrLoad.EndUnit() ? S_OK : E_FAIL;
   }
   catch( sysXStructuredLoad& e )
   {
      return HandleException( e );
   }

   return hr;
}

STDMETHODIMP CStrLoad::get_Version(Float64 *pVal)
{
   *pVal = m_StrLoad.GetVersion();

	return S_OK;
}

STDMETHODIMP CStrLoad::get_ParentVersion(Float64 *pVal)
{
   *pVal = m_StrLoad.GetParentVersion();

	return S_OK;
}

STDMETHODIMP CStrLoad::get_ParentUnit(BSTR* pParentUnit)
{
   USES_CONVERSION;
   *pParentUnit = T2BSTR(m_StrLoad.GetParentUnit().c_str());
   return S_OK;
}

STDMETHODIMP CStrLoad::get_TopVersion(Float64 *pVal)
{
   *pVal = m_StrLoad.GetTopVersion();

	return S_OK;
}

STDMETHODIMP CStrLoad::get_Property(LPCTSTR name, VARIANT *pVal)
{
   bool bRetVal;
   try
   {
      std::_tstring str;
      Float64 d;
      Int32 l;
      Uint32 ul;
      Int64 ll;
      Uint64 ull;
      short i;
      unsigned short ui;
      UINT uint;
      bool b;
      switch (pVal->vt)
      {
      case VT_BSTR:
         bRetVal = m_StrLoad.Property( name, &str );
         if ( bRetVal )
            pVal->bstrVal = CString( str.c_str() ).AllocSysString();
         break;

      case VT_R8:
         bRetVal = m_StrLoad.Property( name, &d );
         if ( bRetVal )
            pVal->dblVal = d;
         break;

      case VT_I2:
         bRetVal = m_StrLoad.Property( name, &i );
         if ( bRetVal )
            pVal->iVal = i;
         break;

      case VT_UI2:
         bRetVal = m_StrLoad.Property( name, &ui );
         if ( bRetVal )
            pVal->uiVal = ui;
         break;

      case VT_I4:
         bRetVal = m_StrLoad.Property( name, &l );
         if ( bRetVal )
            pVal->lVal = l;
         break;

      case VT_UI4:
         bRetVal = m_StrLoad.Property( name, &ul );
         if ( bRetVal )
            pVal->ulVal = ul;
         break;

      case VT_I8:
         bRetVal = m_StrLoad.Property( name, &ll );
         if ( bRetVal )
            pVal->llVal = ll;
         break;

      case VT_UI8:
         bRetVal = m_StrLoad.Property( name, &ull );
         if ( bRetVal )
            pVal->ullVal = ull;
         break;

      case VT_UINT:
         bRetVal = m_StrLoad.Property( name, &uint );
         if ( bRetVal )
            pVal->uintVal = uint;
         break;

      case VT_BOOL:
         bRetVal = m_StrLoad.Property( name, &b );
         if ( bRetVal )
            pVal->boolVal = (b ? VARIANT_TRUE : VARIANT_FALSE);
         break;

      default:
         // all other kinds not supported
         _ASSERTE(false);
      }
   }
   catch( sysXStructuredLoad& e )
   {
      return HandleException( e );
   }

   return bRetVal ? S_OK : STRLOAD_E_INVALIDFORMAT;
}

STDMETHODIMP CStrLoad::Close()
{
   try 
   {
      m_StrLoad.EndLoad();
      m_bOpen = FALSE;
   }
   catch( sysXStructuredLoad& e )
   {
      return HandleException( e );
   }
   return S_OK;
}

STDMETHODIMP CStrLoad::LoadRawUnit(BSTR* pbstrUnit)
{
   CHECK_RETSTRING(pbstrUnit);

   std::_tstring strXML = m_StrLoad.GetUnit();
   *pbstrUnit = CComBSTR(strXML.c_str());
   return S_OK;
}

STDMETHODIMP CStrLoad::EndOfStorage()
{
   bool bEOF = m_StrLoad.Eof();
   return bEOF ? S_OK : S_FALSE;
}

//////////////////////////////////////////////////////////
HRESULT CStrLoad::HandleException( sysXStructuredLoad& e )
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   HRESULT hr;

   switch( e.GetExplicitReason() )
   {
      case sysXStructuredLoad::InvalidFileFormat:
      case sysXStructuredLoad::EndOfFile:
         hr = STRLOAD_E_INVALIDFORMAT;
         break;

      case sysXStructuredLoad::BadRead:
         hr = E_UNEXPECTED;
         break;

      case sysXStructuredLoad::BadVersion:
         hr = STRLOAD_E_BADVERSION;
         break;

      case sysXStructuredLoad::MemoryError:
         hr = E_OUTOFMEMORY;
         break;
   }

   return hr;
}

HRESULT CStrLoad::HandleException2( sysXStructuredLoad& e )
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   HRESULT hr;
   UINT nID;

   switch( e.GetExplicitReason() )
   {
      case sysXStructuredLoad::InvalidFileFormat:
      case sysXStructuredLoad::EndOfFile:
         hr = STRLOAD_E_INVALIDFORMAT;
         nID = IDS_E_INVALIDFORMAT;
         break;

      case sysXStructuredLoad::BadRead:
         hr = E_UNEXPECTED;
         nID = IDS_E_BADREAD;
         break;

      case sysXStructuredLoad::BadVersion:
         hr = STRLOAD_E_BADVERSION;
         nID = IDS_E_BADVERSION;
         break;

      case sysXStructuredLoad::MemoryError:
         hr = E_OUTOFMEMORY;
         nID = IDS_E_OUTOFMEMORY;
         break;
   }

   //AfxThrowOleDispatchException((WORD)hr,nID);
   return Error(hr,IID_IStructuredLoad,nID);
   //return E_FAIL;
}

////////////////////////////////////////////////////////
//
//HRESULT CStrLoad::Open(/*[in]*/ LPCTSTR strFile)
//{
//   // Check if the file exists.  If we can't get its attributes, then
//   // it probably isn't there.
//   DWORD dwResult = GetFileAttributes(strFile);
//   if ( dwResult == 0xFFFFFFFF )
//   {
//      AfxThrowOleDispatchException(STRLOAD_E_FILENOTFOUND-STRLOAD_E_FIRST,IDS_E_FILENOTFOUND);
//      return E_FAIL;
//   }
//
//   _bstr_t bstrFile(strFile);
//   if ( !m_File.open( bstrFile ) )
//   {
//      AfxThrowOleDispatchException(STRLOAD_E_CANTOPEN-STRLOAD_E_FIRST,IDS_E_CANTOPEN);
//      return E_FAIL;
//   }
//
//   m_bOpen = TRUE;
//
//   // :TODO: Error check stream
//   try
//   {
//      m_StrLoad.BeginLoad( &m_File );
//   }
//   catch( sysXStructuredLoad& e )
//   {
//      return HandleException2( e );
//   }
//
//	return S_OK;
//}
//
//HRESULT CStrLoad::BeginUnit(/*[in]*/ LPCTSTR strUnit)
//{
//   try
//   {
//      if ( !m_StrLoad.BeginUnit( strUnit ) )
//      {
//         AfxThrowOleDispatchException(STRLOAD_E_INVALIDFORMAT-STRLOAD_E_FIRST,IDS_E_INVALIDFORMAT);
//         return E_FAIL;
//      }
//   }
//   catch( sysXStructuredLoad& e )
//   {
//      return HandleException2( e );
//   }
//
//	return S_OK;
//}
//
//HRESULT CStrLoad::get_EndUnit(/*[out,retval]*/VARIANT_BOOL* bEnd)
//{
//   try
//   {
//      bool bSuccess = m_StrLoad.EndUnit();
//      *bEnd = (bSuccess ? VARIANT_TRUE : VARIANT_FALSE);
//   }
//   catch( sysXStructuredLoad& e )
//   {
//      return HandleException2( e );
//   }
//
//   return S_OK;
//}
//
//HRESULT CStrLoad::get_Version(/*[out, retval]*/ Float64 *pVal)
//{
//   *pVal = m_StrLoad.GetVersion();
//	return S_OK;
//}
//
//HRESULT CStrLoad::get_ParentVersion(/*[out, retval]*/ Float64 *pVal)
//{
//   *pVal = m_StrLoad.GetParentVersion();
//	return S_OK;
//}
//
//HRESULT CStrLoad::get_TopVersion(/*[out, retval]*/ Float64 *pVal)
//{
//   *pVal = m_StrLoad.GetTopVersion();
//	return S_OK;
//}
//
//HRESULT CStrLoad::get_Property(/*[in]*/ LPCTSTR strPropName, /*[out, retval]*/ VARIANT *pVal)
//{
//   bool bRetVal;
//   try
//   {
//      std::_tstring str;
//      Float64 d;
//      long l;
//      unsigned long ul;
//      short i;
//      unsigned short ui;
//      bool b;
//      switch (pVal->vt)
//      {
//      case VT_BSTR:
//         bRetVal = m_StrLoad.Property( strPropName, &str );
//         if ( bRetVal )
//            pVal->bstrVal = CString( str.c_str() ).AllocSysString();
//         break;
//
//      case VT_R8:
//         bRetVal = m_StrLoad.Property( strPropName, &d );
//         if ( bRetVal )
//            pVal->dblVal = d;
//         break;
//
//      case VT_I2:
//         bRetVal = m_StrLoad.Property( strPropName, &i );
//         if ( bRetVal )
//            pVal->iVal = i;
//         break;
//
//      case VT_UI2:
//         bRetVal = m_StrLoad.Property( strPropName, &ui );
//         if ( bRetVal )
//            pVal->uiVal = ui;
//         break;
//
//      case VT_I4:
//         bRetVal = m_StrLoad.Property( strPropName, &l );
//         if ( bRetVal )
//            pVal->lVal = l;
//         break;
//
//      case VT_UI4:
//         bRetVal = m_StrLoad.Property( strPropName, &ul );
//         if ( bRetVal )
//            pVal->ulVal = ul;
//         break;
//
//      case VT_BOOL:
//         bRetVal = m_StrLoad.Property( strPropName, &b );
//         if ( bRetVal )
//            pVal->boolVal = (b ? VARIANT_TRUE : VARIANT_FALSE);
//         break;
//
//      default:
//         // all other kinds not supported
//         _ASSERTE(false);
//      }
//   }
//   catch( sysXStructuredLoad& e )
//   {
//      return HandleException2( e );
//   }
//
//   if ( !bRetVal )
//   {
//      AfxThrowOleDispatchException(STRLOAD_E_INVALIDFORMAT-STRLOAD_E_FIRST,IDS_E_INVALIDFORMAT);
//      return E_FAIL;
//   }
//
//   return S_OK;
//}
//
//HRESULT CStrLoad::get_EndOfStorage(/*[out,retval]*/VARIANT_BOOL* bEnd)
//{
//   bool bEOF = m_StrLoad.Eof();
//   *bEnd = bEOF ? VARIANT_TRUE : VARIANT_FALSE;
//   return S_OK;
//}
//
//HRESULT CStrLoad::Close()
//{
//   try 
//   {
//      m_StrLoad.EndLoad();
//      m_bOpen = FALSE;
//   }
//   catch( sysXStructuredLoad& e )
//   {
//      return HandleException2( e );
//   }
//   return S_OK;
//}
