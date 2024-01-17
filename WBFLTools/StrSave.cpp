///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2024  Washington State Department of Transportation
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

// StrSave.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <WBFLTools.h>
#include "StrSave.h"
#include <atlbase.h>
#include <WBFLAtlExt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrSave

CStrSave::CStrSave()
{
   m_bOpen = FALSE;
}

CStrSave::~CStrSave()
{
   if (m_bOpen)
      m_StrSave.EndSave();
}

/////////////////////////////////////////////////////////////////////////////
// IStructuredSave
STDMETHODIMP CStrSave::Open(LPCTSTR name)
{
   CComBSTR bnam(name);
   
   if ( !m_File.open( bnam, false ) )
      return STRSAVE_E_CANTOPEN;

   m_bOpen = TRUE;

   // :TODO: Error check stream
   try
   {
      m_StrSave.BeginSave( &m_File);
   }
   catch(WBFL::System::XStructuredSave& e )
   {
      return HandleException( e );
   }

	return S_OK;
}

STDMETHODIMP CStrSave::BeginUnit( LPCTSTR name, Float64 ver)
{
   try
   {
      m_StrSave.BeginUnit( name, ver );
   }
   catch(WBFL::System::XStructuredSave& e )
   {
      return HandleException( e );
   }

	return S_OK;
}

STDMETHODIMP CStrSave::put_Property( LPCTSTR name, VARIANT newVal)
{
   try
   {
      switch ( newVal.vt)
      {
      case VT_BSTR:
         {
         CString str( newVal.bstrVal );
         m_StrSave.Property( name, str );
         break;
         }

      case VT_R8:
         m_StrSave.Property( name, newVal.dblVal );
         break;

      case VT_I2:
         m_StrSave.Property( name, newVal.iVal );
         break;

      case VT_UI2:
         m_StrSave.Property( name, newVal.uiVal );
         break;

      case VT_I4:
         m_StrSave.Property( name, newVal.lVal );
         break;

      case VT_UI4:
         if ( newVal.ulVal == INVALID_INDEX )
            m_StrSave.Property( name, -1 );
         else
            m_StrSave.Property( name, (Uint32)newVal.ulVal );
         break;

      case VT_I8:
         m_StrSave.Property( name, newVal.llVal );
         break;

      case VT_UI8:
         if ( newVal.ullVal == INVALID_INDEX )
            m_StrSave.Property(name,-1);
         else
            m_StrSave.Property( name, (Uint64)newVal.ullVal );
         break;

      case VT_UINT:
         m_StrSave.Property( name, (UINT)newVal.uintVal );
         break;

      case VT_BOOL:
         m_StrSave.Property( name, (newVal.boolVal == VARIANT_TRUE ? true : false) );
         break;

      default:
         // all other kinds not supported
         _ASSERTE(false);
      }
   }
      catch(WBFL::System::XStructuredSave& e )
   {
      return HandleException( e );
   }

	return S_OK;
}

STDMETHODIMP CStrSave::get_TopVersion(Float64 *pVal)
{
   *pVal = m_StrSave.GetTopVersion();

	return S_OK;
}

STDMETHODIMP CStrSave::get_Version(Float64 *pVal)
{
   *pVal = m_StrSave.GetVersion();

	return S_OK;
}

STDMETHODIMP CStrSave::get_ParentVersion(Float64 *pVal)
{
   *pVal = m_StrSave.GetParentVersion();

	return S_OK;
}

STDMETHODIMP CStrSave::get_ParentUnit(BSTR* pParentUnit)
{
   USES_CONVERSION;
   *pParentUnit = T2BSTR(m_StrSave.GetParentUnit().c_str());
   return S_OK;
}

STDMETHODIMP CStrSave::EndUnit()
{
   try 
   {
      m_StrSave.EndUnit();
   }
   catch(WBFL::System::XStructuredSave& e )
   {
      return HandleException( e );
   }

   return S_OK;
}

STDMETHODIMP CStrSave::Close()
{
   try
   {
      m_StrSave.EndSave();
      m_bOpen = FALSE;
   }
   catch(WBFL::System::XStructuredSave& e )
   {
      return HandleException( e );
   }

   return S_OK;
}

STDMETHODIMP CStrSave::SaveRawUnit(LPCTSTR unitXML)
{
   m_StrSave.PutUnit(unitXML);
   return S_OK;
}

/////////////////////////////////////////////////
////////////////////////////////////////////////

HRESULT CStrSave::HandleException(WBFL::System::XStructuredSave& e )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   HRESULT hr;

   switch( e.GetReasonCode() )
   {
      case WBFL::System::XStructuredSave::BadWrite:
         hr = STRSAVE_E_BADWRITE;
         break;
   }

   return hr;
}

HRESULT CStrSave::HandleException2(WBFL::System::XStructuredSave& e)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   switch( e.GetReasonCode() )
   {
      case WBFL::System::XStructuredSave::BadWrite:
         return Error(STRSAVE_E_BADWRITE-STRSAVE_E_FIRST,IID_IStructuredSave,IDS_E_BADWRITE);
         break;
   }

   return E_FAIL;
}

//HRESULT CStrSave::Open(/*[in]*/ LPCTSTR strFileName)
//{
//   _bstr_t bstrFileName(strFileName);
//   if ( !m_File.open( bstrFileName, false ) )
//      return STRSAVE_E_CANTOPEN;
//
//   m_bOpen = TRUE;
//
//   // :TODO: Error check stream
//   try
//   {
//      m_StrSave.BeginSave( &m_File);
//   }
//   catch( sysXStructuredSave& e )
//   {
//      return HandleException2( e );
//   }
//
//	return S_OK;
//}
//
//HRESULT CStrSave::BeginUnit(/*[in]*/ LPCTSTR strUnit,/*[in]*/ Float64 ver)
//{
//   try
//   {
//      m_StrSave.BeginUnit( strUnit, ver );
//   }
//   catch( sysXStructuredSave& e )
//   {
//      return HandleException2( e );
//   }
//
//	return S_OK;
//}
//
//HRESULT CStrSave::EndUnit()
//{
//   try 
//   {
//      m_StrSave.EndUnit();
//   }
//   catch( sysXStructuredSave& e )
//   {
//      return HandleException2( e );
//   }
//
//   return S_OK;
//}
//
//HRESULT CStrSave::get_Version(/*[out, retval]*/ Float64 *pVal)
//{
//   *pVal = m_StrSave.GetVersion();
//
//	return S_OK;
//}
//
//HRESULT CStrSave::get_ParentVersion(/*[out, retval]*/ Float64 *pVal)
//{
//   *pVal = m_StrSave.GetParentVersion();
//
//	return S_OK;
//}
//
//HRESULT CStrSave::get_TopVersion(/*[out, retval]*/ Float64 *pVal)
//{
//   *pVal = m_StrSave.GetTopVersion();
//
//	return S_OK;
//}
//
//HRESULT CStrSave::put_Property(/*[in]*/ LPCTSTR strPropName, /*[in]*/ VARIANT newVal)
//{
//   try
//   {
//      switch ( newVal.vt)
//      {
//      case VT_BSTR:
//         {
//         CString str( newVal.bstrVal );
//         m_StrSave.Property( strPropName, str );
//         break;
//         }
//
//      case VT_R8:
//         m_StrSave.Property( strPropName, newVal.dblVal );
//         break;
//
//      case VT_I2:
//         m_StrSave.Property( strPropName, newVal.iVal );
//         break;
//
//      case VT_UI2:
//         m_StrSave.Property( strPropName, newVal.uiVal );
//         break;
//
//      case VT_I4:
//         m_StrSave.Property( strPropName, newVal.lVal );
//         break;
//
//      case VT_UI4:
//         m_StrSave.Property( strPropName, newVal.ulVal );
//         break;
//
//      case VT_BOOL:
//         m_StrSave.Property( strPropName, (newVal.boolVal == VARIANT_TRUE ? true : false) );
//         break;
//
//      default:
//         // all other kinds not supported
//         _ASSERTE(false);
//      }
//   }
//   catch( sysXStructuredSave& e )
//   {
//      return HandleException2( e );
//   }
//
//	return S_OK;
//}
//
//HRESULT CStrSave::Close()
//{
//   try
//   {
//      m_StrSave.EndSave();
//      m_bOpen = FALSE;
//   }
//   catch( sysXStructuredSave& e )
//   {
//      return HandleException2( e );
//   }
//
//   return S_OK;
//}
