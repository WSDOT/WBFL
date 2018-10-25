///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// Direction.cpp : Implementation of CDirection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Direction.h"
#include "Angle.h"

#include "CogoHelpers.h"
#include <string>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirection

STDMETHODIMP CDirection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDirection,
		&IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDirection::get_Value(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Direction;
	return S_OK;
}

STDMETHODIMP CDirection::put_Value(Float64 newVal)
{
   m_Direction = cogoUtil::NormalizeAngle(newVal);
	return S_OK;
}

STDMETHODIMP CDirection::get_NSDirection(NSDirectionType *pVal)
{
   CHECK_RETVAL(pVal);
   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   cogoUtil::GetBrgParts(m_Direction,&nsDir,&deg,&min,&sec,&ewDir);

   *pVal = nsDir;

	return S_OK;
}

STDMETHODIMP CDirection::put_NSDirection(NSDirectionType newVal)
{
   // Validation handled by UpdateDirection
   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   cogoUtil::GetBrgParts(m_Direction,&nsDir,&deg,&min,&sec,&ewDir);

   return UpdateDirection(newVal,deg,min,sec,ewDir);
}

STDMETHODIMP CDirection::get_EWDirection(EWDirectionType *pVal)
{
   CHECK_RETVAL(pVal);
   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   cogoUtil::GetBrgParts(m_Direction,&nsDir,&deg,&min,&sec,&ewDir);

   *pVal = ewDir;

	return S_OK;
}

STDMETHODIMP CDirection::put_EWDirection(EWDirectionType newVal)
{
   // Validation handled by UpdateDirection
   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   cogoUtil::GetBrgParts(m_Direction,&nsDir,&deg,&min,&sec,&ewDir);

   return UpdateDirection(nsDir,deg,min,sec,newVal);
}

STDMETHODIMP CDirection::get_Degree(long *pVal)
{
   CHECK_RETVAL(pVal);
   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   cogoUtil::GetBrgParts(m_Direction,&nsDir,&deg,&min,&sec,&ewDir);

   *pVal = deg;

	return S_OK;
}

STDMETHODIMP CDirection::put_Degree(long newVal)
{
   // Validation handled by UpdateDirection

   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   cogoUtil::GetBrgParts(m_Direction,&nsDir,&deg,&min,&sec,&ewDir);

   return UpdateDirection(nsDir,newVal,min,sec,ewDir);
}

STDMETHODIMP CDirection::get_Minute(long *pVal)
{
   CHECK_RETVAL(pVal);
   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   cogoUtil::GetBrgParts(m_Direction,&nsDir,&deg,&min,&sec,&ewDir);

   *pVal = min;

	return S_OK;
}

STDMETHODIMP CDirection::put_Minute(long newVal)
{
   // Validation handled by UpdateDirection
   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   cogoUtil::GetBrgParts(m_Direction,&nsDir,&deg,&min,&sec,&ewDir);

   return UpdateDirection(nsDir,deg,newVal,sec,ewDir);
}

STDMETHODIMP CDirection::get_Second(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   cogoUtil::GetBrgParts(m_Direction,&nsDir,&deg,&min,&sec,&ewDir);

   *pVal = sec;

	return S_OK;
}

STDMETHODIMP CDirection::put_Second(Float64 newVal)
{
   // Validation handled by UpdateDirection
   NSDirectionType nsDir;
   long deg, min;
   Float64 sec;
   EWDirectionType ewDir;

   cogoUtil::GetBrgParts(m_Direction,&nsDir,&deg,&min,&sec,&ewDir);

   return UpdateDirection(nsDir,deg,min,newVal,ewDir);
}

STDMETHODIMP CDirection::IncrementBy(VARIANT varAngle)
{
   Float64 val;
   CComPtr<IAngle> angle;
   HRESULT hr = cogoUtil::AngleFromVariant(varAngle,&angle);
   if ( FAILED(hr) )
      return hr;

   angle->get_Value(&val);

   m_Direction += val;
   m_Direction = cogoUtil::NormalizeAngle(m_Direction);

	return S_OK;
}

STDMETHODIMP CDirection::Increment(VARIANT varAngle, IDirection* *pVal)
{
   CHECK_RETOBJ(pVal);
   
   CComObject<CDirection>* pDir;
   CComObject<CDirection>::CreateInstance(&pDir);
   (*pVal) = pDir;
   (*pVal)->AddRef();
   pDir = NULL;

   (*pVal)->put_Value(m_Direction);
   HRESULT hr = (*pVal)->IncrementBy(varAngle);
   if ( FAILED(hr) )
   {
      (*pVal)->Release();
      (*pVal) = NULL;
   }

   return hr;
}

STDMETHODIMP CDirection::FromString(BSTR bstrDir)
{
   USES_CONVERSION;

   CHECK_IN(bstrDir);
   std::_tstring strDir(OLE2T(bstrDir));

   TCHAR cY;
   long deg;
   long min;
   Float64 sec;
   TCHAR cX;
   
   // Trim the whitespace off both ends
   std::_tstring::size_type last_leading_space   = strDir.find_first_not_of(_T(" "));
   if ( last_leading_space == std::_tstring::npos )
      return BadDirectionString();

   std::_tstring::size_type cChar;
   cChar = last_leading_space;  // number of characters to remove
   strDir.erase( 0, cChar );

   std::_tstring::size_type first_trailing_space = strDir.find_last_not_of(_T(" "));
   cChar = strDir.length() - first_trailing_space - 1;
   strDir.erase( first_trailing_space+1, cChar );

   // Determine the number of "parts" used in the angle by counting the 
   // remaining spaces (spaces are the delimeters between the parts)
   // nParts = 3 ->  N dd E
   // nParts = 4 ->  N dd mm E
   // nParts = 5 ->  N dd mm ss.s E
   CollectionIndexType nParts = std::count( strDir.begin(), strDir.end(), _T(' ') ) + 1;
   ATLASSERT( nParts > 0 );
   if ( nParts < 3 || 5 < nParts )
      return BadDirectionString();

   //
   // Lets start breaking apart the string
   //

   // Get N/S part. Make sure it is an N or an S, and there
   // is a space following it.
   cY = toupper( strDir[0] );
   if ( cY != _T('N') && cY != _T('S') || strDir[1] != _T(' ') )
      return BadDirectionString();

   NSDirectionType nsDir = (cY == _T('N') ? nsNorth : nsSouth);

   // Get the E/W part. Make sure it is an E or a W, and there
   // is a space following it.
   cX = toupper( strDir[strDir.size()-1] );
   if ( cX != _T('E') && cX != _T('W') || strDir[strDir.size()-2] != _T(' ') )
      return BadDirectionString();

   EWDirectionType ewDir = (cX == _T('E') ? ewEast : ewWest);

   //
   // Get the degrees
   //
   std::_tstring::size_type pos;
   pos = strDir.find_first_of( _T(' ') );
   strDir.erase( 0, pos+1 );
   pos = strDir.find_first_of( _T(' ') );
   std::_tstring strDeg( strDir, 0, pos );
   strDir.erase( 0, pos+1 );
   deg = _ttoi( strDeg.c_str() ); 

   // If the value of deg is zero, make sure that "0" or "00" were
   // in the string and not some other value that atoi evalutes to zero
   if ( deg == 0 && (strDeg != _T("0") && strDeg != _T("00")) )
      return BadDirectionString();

   if ( 90 < deg )
      return BadDirectionString();

   min = 0;
   sec = 0;

   if ( 4 <= nParts )
   {
      // get the minutes part
      pos = strDir.find_first_of( _T(' ') );
      std::_tstring strMin( strDir, 0, pos );
      strDir.erase( 0, pos + 1 );
      min = _ttoi( strMin.c_str() );

      if ( min == 0 && (strMin != _T("0") && strMin != _T("00") ) )
         return BadDirectionString();

      if ( 59 < min )
         return BadDirectionString();

      if ( nParts == 5 )
      {
         // get the seconds part
         pos = strDir.find_first_of( _T(' ') );
         std::_tstring strSec( strDir, 0, pos );
         sec = _tstof( strSec.c_str() );

         if ( IsZero(sec) && strSec[0] != _T('0') )
            return BadDirectionString();

         if ( 60.0 <= sec )
            return BadDirectionString();
      }
   }

   HRESULT hr = UpdateDirection(nsDir,deg,min,sec,ewDir);
   ATLASSERT(SUCCEEDED(hr));

	return S_OK;
}

STDMETHODIMP CDirection::FromDMS(NSDirectionType ns, long Degree, long Minute, Float64 Second, EWDirectionType ew)
{
   return UpdateDirection(ns,Degree,Minute,Second,ew);
}

STDMETHODIMP CDirection::FromAzimuth(long Degree, long Minute, Float64 Second)
{
   if ( Degree <= -360 || 360 <= Degree )
      return BadAzimuth();

   if ( Minute < 0 || 60 <= Minute )
      return BadAzimuth();

   if ( Second < 0.0 || 60.0 <= Second )
      return BadAzimuth();

   Float64 azimuth = cogoUtil::FromDMS( Degree, Minute, Second );
   ATLASSERT( -TWO_PI < azimuth && azimuth < TWO_PI );

   m_Direction = cogoUtil::NormalizeAngle( 5*PI_OVER_2 - azimuth );

   return S_OK;
}

STDMETHODIMP CDirection::FromVariant(VARIANT varDirection)
{
   CComPtr<IDirection> dir;
   HRESULT hr = cogoUtil::DirectionFromVariant(varDirection,&dir);
   if ( FAILED(hr) )
      return hr;

   dir->get_Value(&m_Direction);
   return S_OK;
}

STDMETHODIMP CDirection::AngleBetween(IDirection* dir,IAngle** pVal)
{
   CHECK_IN(dir);
   CHECK_RETOBJ(pVal);

   Float64 val;
   dir->get_Value(&val);

   Float64 angle = m_Direction - val;
   if ( IsZero(angle) )
      angle = 0;

   CComObject<CAngle>* pAngle;
   CComObject<CAngle>::CreateInstance(&pAngle);
   pAngle->put_Value(angle);
   pAngle->Normalize();

   (*pVal) = pAngle;
   (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CDirection::Clone(IDirection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CDirection>* pClone;
   CComObject<CDirection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->put_Value(m_Direction);

   return S_OK;
}

STDMETHODIMP CDirection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CDirection::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("Direction"),1.0);
   pSave->put_Property(CComBSTR("Value"),CComVariant(m_Direction));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CDirection::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Direction"));
   pLoad->get_Property(CComBSTR("Value"),&var);
   m_Direction = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

//////////////////////////////////////////////////////
// Helper methods

HRESULT CDirection::UpdateDirection(NSDirectionType nsDir, long deg, long min, Float64 sec, EWDirectionType ewDir)
{
   if ( nsDir != nsNorth && nsDir != nsSouth)
      return BadDirection();

   if ( ewDir != ewEast && ewDir != ewWest )
      return BadDirection();

   if ( deg < 0 || 90 < deg )
      return BadDirection();

   if ( min < 0 || 60 <= min )
      return BadDirection();
   
   if ( sec < 0 || 60.0 <= sec )
      return BadDirection();

   Float64 angle;
   Float64 sign;

   if ( 90. < (deg + min/60. + sec/3600.) )
      return BadDirection();

   // Convert component parts to a decimal angle (radians)
   if( nsDir == nsNorth && ewDir == ewEast)
   {
      angle = PI_OVER_2;
      sign  = -1.0;
   }
   else if (nsDir == nsSouth && ewDir == ewWest)
   {
      angle = 1.5*M_PI;
      sign  = -1.0;
   }
   else if (nsDir == nsSouth && ewDir == ewEast)
   {
      angle = 1.5*M_PI;
      sign  = 1.0;
   }
   else if (nsDir == nsNorth && ewDir == ewWest)
   {
      angle = PI_OVER_2;
      sign  = 1.0;
   }
   else
   {
      // Should never get here
      ATLASSERT(false);
   }

   angle += sign * cogoUtil::FromDMS(deg,min,sec);

   if ( IsEqual( angle, TWO_PI ) )
      angle = 0;

   m_Direction = angle;
   return S_OK;
}

HRESULT CDirection::BadDirectionString()
{
   return CComCoClass<CDirection,&CLSID_Direction>::Error(IDS_E_BADDIRECTIONSTRING, IID_IDirection, COGO_E_BADDIRECTIONSTRING);
}

HRESULT CDirection::BadAzimuth()
{
   return CComCoClass<CDirection,&CLSID_Direction>::Error(IDS_E_BADAZIMUTH, IID_IDirection, COGO_E_BADAZIMUTH);
}

HRESULT CDirection::BadDirection()
{
   return CComCoClass<CDirection,&CLSID_Direction>::Error(IDS_E_BADDIRECTION,IID_IDirection,COGO_E_BADDIRECTION);
}