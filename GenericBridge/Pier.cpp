///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// Pier.cpp : Implementation of CPier
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Pier.h"
#include "LongitudinalPierDescription.h"
#include "TransversePierDescription.h"
#include <MathEx.h>
#include <xlocale>
#include <algorithm>
#include <cctype>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPier
HRESULT CPier::FinalConstruct()
{
   CComObject<CLongitudinalPierDescription>* pLPD;
   CComObject<CLongitudinalPierDescription>::CreateInstance(&pLPD);
   pLPD->SetPier(this);
   m_LongPierDesc = pLPD;

   return S_OK;
}

void CPier::FinalRelease()
{
   m_TransPierDesc.Release();
   m_LongPierDesc.Release();
}

void CPier::Init(IGenericBridge* pBridge,IPierLine* pPierLine)
{
   m_pBridge = pBridge;
   m_pPierLine = pPierLine;

   CLongitudinalPierDescription* pLPD = dynamic_cast<CLongitudinalPierDescription*>(m_LongPierDesc.p);
   pLPD->SetBridge(m_pBridge);

   if ( m_TransPierDesc )
   {
      CTransversePierDescription* pTPD = dynamic_cast<CTransversePierDescription*>(m_TransPierDesc.p);
      pTPD->SetBridge(m_pBridge);
   }
}

STDMETHODIMP CPier::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPier,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CPier::ValidateOrientation(BSTR bstrOrientation)
{
   USES_CONVERSION;

   // convert and make uppercase
   std::_tstring strOrientation = OLE2T(bstrOrientation);
   std::transform(strOrientation.begin(),strOrientation.end(),strOrientation.begin(),(int(*)(int))std::toupper);

   // Trim off the leading and trailing whitespace
   std::_tstring::size_type last_leading_space   = strOrientation.find_first_not_of(_T(" "));
   if ( last_leading_space == std::_tstring::npos )
      return E_INVALIDARG;

   std::_tstring::size_type cChar;
   cChar = last_leading_space;  // number of characters to remove
   strOrientation.erase( 0, cChar );

   std::_tstring::size_type first_trailing_space = strOrientation.find_last_not_of(_T(" "));
   cChar = strOrientation.length() - first_trailing_space - 1;
   strOrientation.erase( first_trailing_space+1, cChar );

   // string is made uppercase above
   //std::ctype<char> helper;
   //helper.toupper(strOrientation.begin(),strOrientation.end());

   // Validate
   if ( (strOrientation.length() == 1 && strOrientation[0] == _T('N')) || 
         strOrientation.compare(_T("NORMAL")) == 0 )
   {
      return S_OK;
   }
   else if ( strOrientation[0] == _T('N') || strOrientation[0] == _T('S') )
   {
      // It is a bearing
      CComPtr<IDirection> bearing;
      bearing.CoCreateInstance(CLSID_Direction);
      HRESULT hr = bearing->FromString(bstrOrientation);
      if ( SUCCEEDED(hr) )
         return S_OK;
   }
   else
   {
      // It is an angle
      CComPtr<IAngle> angle;
      angle.CoCreateInstance(CLSID_Angle);
      HRESULT hr = angle->FromString(bstrOrientation);
      if ( SUCCEEDED(hr) )
         return S_OK;
   }

   return E_INVALIDARG;
}

void CPier::SetLongitudinalPierDescription(ILongitudinalPierDescription* cloneLPD)
{
   CLongitudinalPierDescription* pClone = dynamic_cast<CLongitudinalPierDescription*>(cloneLPD);
   pClone->SetPier(this);

   m_LongPierDesc = cloneLPD;
}

void CPier::SetTransversePierDescription(ITransversePierDescription* cloneTPD)
{
   CTransversePierDescription* pClone = dynamic_cast<CTransversePierDescription*>(cloneTPD);
   pClone->SetPier(this);

   m_TransPierDesc = cloneTPD;
}

//////////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CPier::get_Station(IStation* *station)
{
   return m_pPierLine->get_Station(station);
}

STDMETHODIMP CPier::get_LongitudinalPierDescription(ILongitudinalPierDescription* *pVal)
{
   CHECK_RETOBJ(pVal);

   (*pVal) = m_LongPierDesc;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CPier::get_Direction(IDirection* *direction)
{
   return m_pPierLine->get_Direction(direction);
}

STDMETHODIMP CPier::get_SkewAngle(IAngle* *skewAngle)
{
   return m_pPierLine->get_Skew(skewAngle);
}

STDMETHODIMP CPier::CreateTransversePierDescription()
{
   if ( !m_TransPierDesc )
   {
      CComObject<CTransversePierDescription>* pTPD;
      CComObject<CTransversePierDescription>::CreateInstance(&pTPD);
      m_TransPierDesc = pTPD;

      pTPD->SetPier(this);
      pTPD->SetBridge(m_pBridge);
   }
   return S_OK;
}

STDMETHODIMP CPier::get_TransversePierDescription(ITransversePierDescription* *pVal)
{
   CHECK_RETVAL(pVal);
   if ( m_TransPierDesc )
   {
      (*pVal) = m_TransPierDesc;
      (*pVal)->AddRef();
   }
   else
   {
      (*pVal) = NULL;
   }

   return S_OK;
}

STDMETHODIMP CPier::get_Index(PierIndexType* pIndex)
{
   return m_pPierLine->get_Index(pIndex);
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CPier::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);
   CComVariant var;
   load->BeginUnit(CComBSTR("Pier"));


   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CPier::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("Pier"),1.0);


   save->EndUnit();

   return S_OK;
}
