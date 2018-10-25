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

// Angle.cpp : Implementation of CAngle
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Angle.h"

#include "CogoHelpers.h"
#include <MathEx.h>
#include <string>
#include <algorithm>
#include <System\Tokenizer.h>
#include <Units\SysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAngle

STDMETHODIMP CAngle::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAngle,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAngle::get_Value(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Angle;
	return S_OK;
}

STDMETHODIMP CAngle::put_Value(Float64 newVal)
{
   m_Angle = newVal;
	return S_OK;
}

STDMETHODIMP CAngle::get_Degree(long *pVal)
{
   CHECK_RETVAL(pVal);

   long deg,min;
   Float64 sec;
   cogoUtil::ToDMS(m_Angle,&deg,&min,&sec);

   *pVal = deg;

	return S_OK;
}

STDMETHODIMP CAngle::get_Minute(long *pVal)
{
   CHECK_RETVAL(pVal);

   long deg,min;
   Float64 sec;
   cogoUtil::ToDMS(m_Angle,&deg,&min,&sec);

   *pVal = min;

	return S_OK;
}

STDMETHODIMP CAngle::get_Second(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   long deg,min;
   Float64 sec;
   cogoUtil::ToDMS(m_Angle,&deg,&min,&sec);

   *pVal = sec;

	return S_OK;
}

STDMETHODIMP CAngle::Normalize()
{
   m_Angle = cogoUtil::NormalizeAngle(m_Angle);
	return S_OK;
}

STDMETHODIMP CAngle::FromDMS(long deg, long min, Float64 sec)
{
   if ( min < 0 || 60 <= min )
   {
      return BadAngle();
   }

   if ( sec < 0.0 || 60.0 <= sec )
   {
      return BadAngle();
   }

   m_Angle = cogoUtil::FromDMS(deg,min,sec);

	return S_OK;
}

STDMETHODIMP CAngle::FromString(BSTR bstrAngle)
{
   USES_CONVERSION;

   CHECK_IN(bstrAngle);

   std::_tstring str( OLE2T(bstrAngle) );

   // parse into space-delimited tokens
   LPCTSTR delims[] = {_T(" "),_T("\t"), 0};
   sysTokenizer tokizer(delims);
   tokizer.push_back(str);

   sysTokenizer::size_type nParts = tokizer.size();
   if (nParts < 1 || 4 < nParts)
      return BadAngleString();  // string is empty or has too many parts

   if ( nParts == 1 )
   {
      // String is of the format [+|-]ddd.ddd[R|L]
      // check for R or L
      std::_tstring stmp = tokizer[0];
      std::_tstring::size_type endloc = stmp.length()-1;
      TCHAR end = stmp[endloc];
      Float64 rlfactor=1.;
      if (end == _T('R') || end == _T('r') || end == _T('L') || end == _T('l') )
      {
         // can't begin with a - or + sign and have L/R
         if ( stmp[0] == _T('+') || stmp[0] == _T('-') )
            return BadAngleString();

         if (end == _T('R') || end == _T('r') )
            rlfactor = -1;

         stmp.erase(endloc,endloc);
      }

      Float64 angle;
      if (!sysTokenizer::ParseDouble(stmp.c_str(),&angle))
         return BadAngleString();

      angle *=rlfactor;

      m_Angle = ::Convert(angle,unitMeasure::Degree,unitMeasure::Radian);
   }
   else if ( nParts == 2 )
   {
      // String is of the format ddd.ddd [L|R]

      std::_tstring stmp = tokizer[0];

      Float64 angle;
      if (!sysTokenizer::ParseDouble(stmp.c_str(),&angle))
         return BadAngleString();

      std::_tstring rl = tokizer[1];
      if (rl == _T("L") || rl == _T("l") || rl == _T("R") || rl == _T("r") )
      {
         // can't begin with a - or + sign
         if ( stmp[0] == _T('+') || stmp[0] == _T('-') )
            return BadAngleString();

         if (rl == _T("R") || rl == _T("r") )
            angle *= -1;
      }
      else 
         return BadAngleString();

      m_Angle = ::Convert(angle,unitMeasure::Degree,unitMeasure::Radian);
   }
   else if ( nParts == 3 || nParts == 4)
   {
      // String is of the format [+|-]ddd mm ss.s or ddd mm ss.s [L|R]
      std::_tstring stmp = tokizer[0];

      // deal with [L|R]
      std::_tstring rl = tokizer[nParts-1];

      long rlfactor = 0;
      if (rl == _T("L") || rl == _T("l") || rl == _T("R") || rl == _T("r") )
      {
         // can't begin with a - or + sign
         if ( stmp[0] == _T('+') || stmp[0] == _T('-') )
            return BadAngleString();

         rlfactor = (rl == _T("R") || rl == _T("r") ) ? -1 : 1;
      }
      else if (nParts==4)
      {
         // we are expecting L|R
         return BadAngleString();
      }

      // ddd
	   long deg;
      LPCTSTR lpszDeg = stmp.c_str();
      Float64 sign = 1;
      if ( lpszDeg[0] == _T('-') )
      {
         // the angle is signed...
         sign = -1;
         lpszDeg++;
      }

      if (!sysTokenizer::ParseLong(lpszDeg,&deg))
         return BadAngleString();

      deg = abs(deg); // make sure deg is unsigned because we will be multiplying it by "sign" below

      // mm
	   long min;
      stmp = tokizer[1];
      if (!sysTokenizer::ParseLong(stmp.c_str(),&min))
         return BadAngleString();

      // sss.s
	   Float64 sec = 0.0;
      // only parse seconds if they exist
      if (rlfactor==0 || nParts==4)
      {
         stmp = tokizer[2];
         if (!sysTokenizer::ParseDouble(stmp.c_str(),&sec))
            return BadAngleString();
      }


      HRESULT hr = this->FromDMS( deg, min, sec );
      if (FAILED(hr))
      {
         return BadAngleString();
      }

      m_Angle *= sign;

      if ( rlfactor != 0 )
      {
         m_Angle *= rlfactor;
      }
   }

	return S_OK;
}

STDMETHODIMP CAngle::FromVariant(VARIANT varAngle)
{
   CComPtr<IAngle> angle;
   HRESULT hr = cogoUtil::AngleFromVariant(varAngle,&angle);
   if ( FAILED(hr) )
      return hr;

   angle->get_Value(&m_Angle);
   return S_OK;
}

STDMETHODIMP CAngle::Increment( VARIANT varAngle, IAngle* *pVal)
{
   CHECK_RETOBJ(pVal);
   
   CComObject<CAngle>* pAngle;
   CComObject<CAngle>::CreateInstance(&pAngle);
   (*pVal) = pAngle;
   (*pVal)->AddRef();
   pAngle = NULL;

   (*pVal)->put_Value(m_Angle);
   HRESULT hr = (*pVal)->IncrementBy(varAngle);
   if ( FAILED(hr) )
   {
      (*pVal)->Release();
      (*pVal) = NULL;
   }

   return hr;
}

STDMETHODIMP CAngle::IncrementBy(VARIANT varAngle)
{
   Float64 val;
   CComPtr<IAngle> angle;
   HRESULT hr = cogoUtil::AngleFromVariant(varAngle,&angle);
   if ( FAILED(hr) )
      return hr;

   angle->get_Value(&val);

   m_Angle += val;

	return S_OK;
}

STDMETHODIMP CAngle::Clone(IAngle* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CAngle>* pClone;
   CComObject<CAngle>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->put_Value(m_Angle);

   return S_OK;
}

STDMETHODIMP CAngle::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CAngle::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("Angle"),1.0);
   pSave->put_Property(CComBSTR("Value"),CComVariant(m_Angle));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CAngle::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Angle"));
   pLoad->get_Property(CComBSTR("Value"),&var);
   m_Angle = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

////////////////////////////////////////////////////////////////
// Helper methods
HRESULT CAngle::BadAngle()
{
   return CComCoClass<CAngle,&CLSID_Angle>::Error(IDS_E_BADANGLE,IID_IAngle,COGO_E_BADANGLE);
}

HRESULT CAngle::BadAngleString()
{
   return CComCoClass<CAngle,&CLSID_Angle>::Error(IDS_E_BADANGLESTRING,IID_IAngle,COGO_E_BADANGLESTRING);
}