///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include "StdAfx.h"
#include "Resource.h"
#include <MfcTools\CogoDDX.h>
#include <Units\SysUnits.h>
#include <algorithm>
#include <cctype>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void DDX_Direction(CDataExchange* pDX,int nIDC,IDirection* pDirection,IDisplayUnitFormatter* formatter)
{
   HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
   ASSERT( ::IsWindow( hWndCtrl ) );

   int cLength = ::GetWindowTextLength( hWndCtrl ) + 1;
   cLength = (cLength == 1 ? 32 : cLength );
   LPTSTR lpszBuffer = new TCHAR[cLength];
	if (pDX->m_bSaveAndValidate)
	{
	   // Transfer data from the control
	   ::GetWindowText(hWndCtrl, lpszBuffer, cLength);

      // Convert to BSTR
      CString strDirection(lpszBuffer);
      BSTR bstrDirection = strDirection.AllocSysString();

      HRESULT hr = pDirection->FromString(bstrDirection);
      ::SysFreeString(bstrDirection);
      delete[] lpszBuffer;
      lpszBuffer = 0;

      if ( FAILED(hr) )
      {
         AfxMessageBox(_T("Invalid Bearing. Valid bearings are of the form\n[N|S] dd (mm (ss.s)) [E|W]\n\nExample: N 25 14 12.5 E\n\nAlso, the total angle may not exceed 90 degrees\n and negative values are not allowed"));
         pDX->Fail();
      }
    }
	else
	{
      Float64 value;
      pDirection->get_Value(&value);

      BSTR bstr;
      formatter->Format(value,NULL,&bstr);

      CString str(bstr);

      ::SetWindowText( hWndCtrl, str );

      ::SysFreeString(bstr);
	}
   delete[] lpszBuffer;
}

void DDX_Angle(CDataExchange* pDX,int nIDC,IAngle* pAngle,IDisplayUnitFormatter* formatter)
{
   HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
   ASSERT( ::IsWindow( hWndCtrl ) );

   int cLength = ::GetWindowTextLength( hWndCtrl ) + 1;
   cLength = (cLength == 1 ? 32 : cLength );
   LPTSTR lpszBuffer = new TCHAR[cLength];
	if (pDX->m_bSaveAndValidate)
	{
	   // Transfer data from the control
	   ::GetWindowText(hWndCtrl, lpszBuffer, cLength);

      // Convert to BSTR
      CString strAngle(lpszBuffer);
      BSTR bstrAngle = strAngle.AllocSysString();

      HRESULT hr = pAngle->FromString(bstrAngle);
      ::SysFreeString(bstrAngle);

      delete[] lpszBuffer;
      lpszBuffer = 0;

      if ( FAILED(hr) )
      {
         AfxMessageBox(_T("Invalid format.  Valid angles are of the form\n (+|-)ddd ((mm) (ss.s)) or\n ddd ((mm) (ss.s)) [L|R]\n\nExamples:\n -12 32 45.3\n 14 21 14.3 R"));

         // Fail throws an exception.  delete the buffer so we don't leak memory
         pDX->Fail();
      }
    }
	else
	{
      Float64 value;
      pAngle->get_Value(&value);

      BSTR bstr;
      formatter->Format(value,NULL,&bstr);

      CString str(bstr);

      ::SetWindowText( hWndCtrl, str );

      ::SysFreeString(bstr);
	}
   delete[] lpszBuffer;
}

void DDX_Station( CDataExchange* pDX, int nIDC, Float64& station, bool bUnitModeSI, const unitLength& usDisplayUnit, const unitLength& siDisplayUnit )
{
#pragma Reminder("UPDATE: does this need to take station equation zone index into account")
   const unitLength& displayUnit = ( bUnitModeSI ? siDisplayUnit : usDisplayUnit );

   HWND hWndCtrl = pDX->PrepareEditCtrl( nIDC );

   ASSERT( ::IsWindow( hWndCtrl ) );

   int cLength = ::GetWindowTextLength( hWndCtrl ) + 1;
   cLength = (cLength == 1 ? 32 : cLength );
   LPTSTR lpszBuffer = new TCHAR[cLength];

   CComPtr<IStation> objStation;
   HRESULT hr = objStation.CoCreateInstance(CLSID_Station);
   ASSERT(SUCCEEDED(hr));

	if (pDX->m_bSaveAndValidate)
	{
	   // Transfer data from the control
	   ::GetWindowText(hWndCtrl, lpszBuffer, cLength);
      hr = objStation->FromString(CComBSTR(lpszBuffer),bUnitModeSI ? umSI : umUS);
      if ( FAILED(hr) )
      {
         // Fail throws an exception delete lpszBuffer so we don't leak memory.
         delete[] lpszBuffer;
         lpszBuffer = 0;
         pDX->Fail();
      }

      objStation->get_Value(&station);
      station = ::ConvertToSysUnits( station, displayUnit );
    }
	else
	{
      station = ::ConvertFromSysUnits( station, displayUnit );
      objStation->put_Value(station);
      CComBSTR bstrStation;
      hr = objStation->AsString(bUnitModeSI ? umSI : umUS,VARIANT_FALSE,&bstrStation);
      if ( FAILED(hr) )
      {
         // Something got screwed up!!!

         // Fail throws an exception delete lpszBuffer so we don't leak memory.
         delete[] lpszBuffer;
         lpszBuffer = 0;

         pDX->Fail();
      }


		::SetWindowText(hWndCtrl,CString(bstrStation));
	}
   delete[] lpszBuffer;
}

void DDX_Station( CDataExchange* pDX, int nIDC, Float64& station, const unitStationFormat& unitStation )
{
#pragma Reminder("UPDATE: does this need to take station equation zone index into account")
   UnitModeType unitMode = unitStation.GetUnitOfMeasure() == unitStationFormat::Feet ? umUS : umSI;
   const unitLength& displayUnit = (unitMode == umUS ? unitMeasure::Feet : unitMeasure::Meter);

   HWND hWndCtrl = pDX->PrepareEditCtrl( nIDC );

   ASSERT( ::IsWindow( hWndCtrl ) );

   int cLength = ::GetWindowTextLength( hWndCtrl ) + 1;
   cLength = (cLength == 1 ? 32 : cLength );
   LPTSTR lpszBuffer = new TCHAR[cLength];

   CComPtr<IStation> objStation;
   HRESULT hr = objStation.CoCreateInstance(CLSID_Station);
   ASSERT(SUCCEEDED(hr));

	if (pDX->m_bSaveAndValidate)
	{
	   // Transfer data from the control
	   ::GetWindowText(hWndCtrl, lpszBuffer, cLength);
      hr = objStation->FromString(CComBSTR(lpszBuffer),unitMode);
      if ( FAILED(hr) )
      {
         // Fail throws an exception delete lpszBuffer so we don't leak memory.
         delete[] lpszBuffer;
         lpszBuffer = 0;
         CString strError;
         if ( unitMode == umUS )
            strError = _T("Invalid station format. Enter the station in the following format: xx+yy.zz");
         else
            strError = _T("Invalid station format. Enter the station in the following format: xx+yyy.zz");
         
         AfxMessageBox(strError);
         
         pDX->Fail();
      }

      objStation->get_Value(&station);
      station = ::ConvertToSysUnits( station, displayUnit );
   }
	else
	{  
      station = ::ConvertFromSysUnits( station, displayUnit );
      objStation->put_Value(station);
      CComBSTR bstrStation;
      hr = objStation->AsString(unitMode,VARIANT_FALSE,&bstrStation);
      if ( FAILED(hr) )
      {
         // Something got screwed up!!!

         // Fail throws an exception delete lpszBuffer so we don't leak memory.
         delete[] lpszBuffer;
         lpszBuffer = 0;

         pDX->Fail();
      }


		::SetWindowText(hWndCtrl,CString(bstrStation));
	}

   delete[] lpszBuffer;
}

void DDV_GreaterThanStation( CDataExchange* pDX, Float64 station, Float64 stationLimit, bool bUnitsModeSI, const unitLength& usDisplayUnit, const unitLength& siDisplayUnit )
{
#pragma Reminder("UPDATE: does this need to take station equation zone index into account")

   const unitLength& displayUnit = ( bUnitsModeSI ? siDisplayUnit : usDisplayUnit );
	if (!pDX->m_bSaveAndValidate)
	{
		TRACE0("Warning: initial dialog data is out of range.\n");
		return;         // don't stop now
	}

   if( !(stationLimit < station) )
   {
      CComPtr<IStation> objStation;
      HRESULT hr = objStation.CoCreateInstance(CLSID_Station);
      ATLASSERT( SUCCEEDED(hr) );

      CString msg;
      stationLimit = ::ConvertFromSysUnits( stationLimit, displayUnit );
      objStation->put_Value(stationLimit);

      CComBSTR bstrStationLimit;
      hr = objStation->AsString(bUnitsModeSI ? umSI : umUS,VARIANT_FALSE,&bstrStationLimit);
      ATLASSERT( SUCCEEDED(hr) );

      msg.Format(_T("Please enter a station that is greater than %s"), CString(bstrStationLimit));
	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

void DDV_Orientation(CDataExchange* pDX, std::_tstring& strOrientation)
{
	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

   std::transform(strOrientation.begin(),strOrientation.end(),strOrientation.begin(),toupper);

   if ( strOrientation.empty() )
   {
      AfxMessageBox(_T("Orientation must not be blank"),MB_ICONEXCLAMATION);
      pDX->Fail();
      return;
   }

   if ( strOrientation == _T("NORMAL") || (strOrientation.length() == 1 && strOrientation[0] == _T('N') ) )
      return; // valid orientation

   CComPtr<IAngle> angle;
   angle.CoCreateInstance(CLSID_Angle);
   HRESULT hr_angle = angle->FromString(CComBSTR(strOrientation.c_str()));
   if ( SUCCEEDED(hr_angle) )
   {
      Float64 stMax_Skew = M_PI*88.0/180.0;

      Float64 value;
      angle->get_Value(&value);
      if ( value < -stMax_Skew || stMax_Skew < value )
      {
         AfxMessageBox(_T("Skew angle must be less than 88 deg"),MB_ICONEXCLAMATION);
         pDX->Fail();
      }
      return;
   }

   CComPtr<IDirection> direction;
   direction.CoCreateInstance(CLSID_Direction);
   HRESULT hr_direction = direction->FromString(CComBSTR( strOrientation.c_str() ));
   if ( FAILED(hr_direction) )
   {
      AfxMessageBox(_T("Orientation is invalid"),MB_ICONEXCLAMATION);
      pDX->Fail();
   }
}
