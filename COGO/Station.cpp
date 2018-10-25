///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2013  Washington State Department of Transportation
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

// Station.cpp : Implementation of CStation
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Station.h"
#include <stdio.h>
#include "CogoHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define E_BADSTATIONSTRING CComCoClass<CStation,&CLSID_Station>::Error(IDS_E_BADSTATIONSTRING,IID_IStation,COGO_E_BADSTATIONSTRING)

/////////////////////////////////////////////////////////////////////////////
// CStation

STDMETHODIMP CStation::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IStation,
      &IID_IStructuredStorage2
   };
   for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

STDMETHODIMP CStation::get_StationZoneIndex(ZoneIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_ZoneIdx;
   return S_OK;
}

STDMETHODIMP CStation::put_StationZoneIndex(ZoneIndexType newVal)
{
   if ( m_ZoneIdx != newVal )
   {
      m_ZoneIdx = newVal;
      Fire_OnStationChanged(m_ZoneIdx,m_Value);
   }
   return S_OK;
}

STDMETHODIMP CStation::get_Value(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Value;
	return S_OK;
}

STDMETHODIMP CStation::put_Value(Float64 newVal)
{
   if ( !IsEqual(m_Value,newVal) )
   {
      m_Value = newVal;
      Fire_OnStationChanged(m_ZoneIdx,m_Value);
   }

	return S_OK;
}

STDMETHODIMP CStation::get_NormalizedValue(IAlignment* pAlignment,Float64* pValue)
{
   CHECK_RETVAL(pValue);
   *pValue = cogoUtil::GetNormalizedStationValue(pAlignment,this);
   return S_OK;
}

STDMETHODIMP CStation::GetStation(ZoneIndexType* pZoneIdx,Float64* pStation)
{
   CHECK_RETVAL(pZoneIdx);
   CHECK_RETVAL(pStation);
   *pZoneIdx = m_ZoneIdx;
   *pStation = m_Value;
   return S_OK;
}

STDMETHODIMP CStation::SetStation(ZoneIndexType zoneIdx,Float64 station)
{
   if ( m_ZoneIdx != zoneIdx || !IsEqual(m_Value,station) )
   {
      m_ZoneIdx = zoneIdx;
      m_Value = station;
      Fire_OnStationChanged(m_ZoneIdx,m_Value);
   }
   return S_OK;
}

STDMETHODIMP CStation::FromVariant(VARIANT varStation)
{
   CComPtr<IStation> station;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&station);
   if ( FAILED(hr) )
      return hr;

   station->GetStation(&m_ZoneIdx,&m_Value);

   return S_OK;
}

STDMETHODIMP CStation::FromString(BSTR station,UnitModeType unitMode)
{
   if ( unitMode == umSI )
      return StringToStation(station,3,3);
   else
      return StringToStation(station,2,2);
}

STDMETHODIMP CStation::AsString(UnitModeType unitMode,VARIANT_BOOL vbIncludeStationZone, BSTR *station)
{
   if ( unitMode == umSI )
      return StationToString(3,3,vbIncludeStationZone,station);
   else
      return StationToString(2,2,vbIncludeStationZone,station);
}

STDMETHODIMP CStation::Clone(IStation* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CStation>* pClone;
   CComObject<CStation>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->SetStation(m_ZoneIdx,m_Value);

   return S_OK;
}

STDMETHODIMP CStation::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CStation::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("Station"),1.0);
   pSave->put_Property(CComBSTR("Value"),CComVariant(m_Value));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CStation::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Station"));

   pLoad->get_Property(CComBSTR("Value"),&var);
   m_Value = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

//////////////////////////////////////////////////
// Helpers
HRESULT CStation::StationToString(int nDigOffset,int nDec,VARIANT_BOOL vbIncludeStationZone,BSTR* strStation)
{
   USES_CONVERSION;

   Float64 station = fabs(m_Value);

   Float64 shifter = pow(10.,nDigOffset);
   int v1 = (int)floor(station/shifter);
   Float64 v2 = station - v1*shifter;
   
   // Check to make sure that v2 is not basically the same as shifter
   // If station = 69500.00000, we sometimes get 694+100.00 instead of
   // 695+00.
   if ( IsZero(v2-shifter,5*pow(10.,-(nDec+1))) )
   {
      v2 = 0;
      v1++;
   }

   int width = nDigOffset + nDec + 1; // add one for the '.'

   int nChar;
   nChar = (v1 == 0) ? 1 : (int)log10((Float64)v1) + 1;
   nChar += width; // includes one for the '.'
   nChar++; // one for the '+'
   nChar++; // one for the '\n'
   if ( m_Value < 0 )
      nChar++; // for the leading "-" sign


   ZoneIndexType zoneIdx = (m_ZoneIdx == INVALID_INDEX ? 0 : m_ZoneIdx);
   if ( vbIncludeStationZone == VARIANT_TRUE )
   {
      if ( zoneIdx == 0 )
         nChar += 2; // ",1" will be added to the station string
      else
         nChar += (int)log10((Float64)zoneIdx) + 2; // ",nnn" where nnn is the zone index
   }

   LPTSTR pBuffer = new TCHAR[nChar];
   if ( vbIncludeStationZone == VARIANT_TRUE )
   {
      _stprintf_s(pBuffer,nChar,(m_Value < 0 ? _T("-%d+%0*.*f,%d") : _T("%d+%0*.*f,%d") ),v1,width,nDec,v2,zoneIdx+1);
   }
   else
   {
      _stprintf_s(pBuffer,nChar,(m_Value < 0 ? _T("-%d+%0*.*f") : _T("%d+%0*.*f") ),v1,width,nDec,v2);
   }
   *strStation = T2BSTR(pBuffer);

   delete[] pBuffer;

   return S_OK;
}

HRESULT CStation::StringToStation(BSTR strString,int nDigOffset,int nDec)
{
   USES_CONVERSION;

   CComBSTR bstrStation(strString);

   TCHAR* pBuffer = 0;
   HRESULT hr = S_OK;

   TCHAR chFirst;
   Float64 d;

   // Look for the +
   int nChar = bstrStation.Length()+1;
   pBuffer = new TCHAR[nChar];
   _tcscpy_s( pBuffer, bstrStation.Length()+1, OLE2T(bstrStation) );

   LPTSTR pChar = pBuffer+nChar-2;
   int idx = nChar-2;
	while (*pChar != _T(',') && 0 <= idx )
	{
		pChar--;
      idx--;
	}

   ZoneIndexType zoneIdx = INVALID_INDEX;
   if ( *pChar == _T(',') )
   {
      // found a zone index
      LPTSTR pEnd = pBuffer+nChar-2;
      zoneIdx = (ZoneIndexType)_tcstol(pChar+1,&pEnd,10)-1;
      *pChar = _T('\0');
   }

   pChar = pBuffer;
	while (*pChar != _T('+') && *pChar != _T('\0') )
	{
		pChar++;
	}

	if (*pChar == _T('+') )
	{
		// The + was found

		// Verify that the station is not ill-formed
		// That is, there must be nOffsetDigits between the +
		// and the decimal point or the end of the string

      // first, the string must be long enough to hold the correct number of digits
      CollectionIndexType pos = (pChar - pBuffer);
      CollectionIndexType min_length = pos + nDigOffset + 2;
      if ( nChar < min_length )
      {
         hr = E_BADSTATIONSTRING;
         goto CleanUp;
      }

		TCHAR cDecimal = *(pChar + nDigOffset + 1);
		if ( cDecimal != _T('.') && cDecimal != 0 && cDecimal != _T('\n') && !isspace(cDecimal) )
		{
         hr = E_BADSTATIONSTRING;
         goto CleanUp;
		}


	   // Remove the + by shifting the remaining characters 1 to the left
	   _tcscpy_s(pChar,nChar - size_t(pChar-pBuffer),pChar+1);
	}
   else
   {
      // The + wasn't found, this must be a regular number
      d = _tstof( pBuffer );
      if ( IsZero( d ) && pBuffer[0] != _T('0') )
      {
         hr = E_BADSTATIONSTRING;
         goto CleanUp;
      }
      
      put_Value(d);
      hr = S_OK;
      goto CleanUp;
   }
		
	// Now that the + has been removed, convert the string to a Float64
	chFirst = pBuffer[0];
   d = _tcstod(pBuffer,&pChar);

   if (d == 0.0 && chFirst != _T('0') )
	{
		// Could not convert
      hr = CComCoClass<CStation,&CLSID_Station>::Error(IDS_E_BADSTATIONSTRING,IID_IStation,COGO_E_BADSTATIONSTRING);
      goto CleanUp;
	}

	while (*pChar == _T(' ') || *pChar == _T('\t') )
	   pChar++;

   if (*pChar != _T('\0') )
	{
	   // Not terminated properly
      hr = E_BADSTATIONSTRING;
      goto CleanUp;
	}

   SetStation(zoneIdx,d);
   hr = S_OK;

CleanUp:
   delete[] pBuffer;
   return hr;
}
