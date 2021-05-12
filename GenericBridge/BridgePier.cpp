///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

// Pier.cpp : Implementation of CBridgePier
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "BridgePier.h"
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
// CBridgePier
HRESULT CBridgePier::FinalConstruct()
{
   m_TestStation.CoCreateInstance(CLSID_Station);
   return m_PierImpl.FinalConstruct(this);
}

void CBridgePier::FinalRelease()
{
}

void CBridgePier::Init(IGenericBridge* pBridge,IPierLine* pPierLine)
{
   m_pBridge = pBridge;
   m_pPierLine = pPierLine;
}

STDMETHODIMP CBridgePier::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBridgePier,
      &IID_IStructuredStorage2
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CBridgePier::ValidateOrientation(BSTR bstrOrientation)
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
      {
         return S_OK;
      }
   }
   else
   {
      // It is an angle
      CComPtr<IAngle> angle;
      angle.CoCreateInstance(CLSID_Angle);
      HRESULT hr = angle->FromString(bstrOrientation);
      if ( SUCCEEDED(hr) )
      {
         return S_OK;
      }
   }

   return E_INVALIDARG;
}

//////////////////////////////////////////////////////////////////////////////////////
// IPier
STDMETHODIMP CBridgePier::get_DeckProfile(/*[out,retval]*/IPoint2dCollection** ppPoints)
{
#pragma Reminder("IMPLEMENT")
   ATLASSERT(false);
   return E_NOTIMPL;
}

STDMETHODIMP CBridgePier::get_DeckThickness(/*[out,retval]*/Float64* pTDeck)
{
   CComPtr<IBridgeDeck> deck;
   m_pBridge->get_Deck(&deck);
   return deck->get_GrossDepth(pTDeck);
}

STDMETHODIMP CBridgePier::get_CurbLineOffset(/*[in]*/DirectionType side,/*[in]*/CurbLineMeasurementType clMeasure,/*[out,retval]*/Float64* pCLO)
{
#pragma Reminder("IMPLEMENT")
   ATLASSERT(false);
   return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////////////////////
// IBridgePier
STDMETHODIMP CBridgePier::get_Bridge(IGenericBridge** ppBridge)
{
   CHECK_RETOBJ(ppBridge);
   if ( m_pBridge )
   {
      *ppBridge = m_pBridge;
      (*ppBridge)->AddRef();
   }
   return S_OK;
}

STDMETHODIMP CBridgePier::get_Index(PierIndexType* pIndex)
{
   return m_pPierLine->get_Index(pIndex);
}

STDMETHODIMP CBridgePier::get_ID(PierIDType* pID)
{
   return m_pPierLine->get_ID(pID);
}

STDMETHODIMP CBridgePier::get_Location(Float64* pXb)
{
   // gets the location of the pier in bridge coordinates
   CHECK_RETVAL(pXb);
   CComPtr<IStation> station;
   get_Station(&station);

   CComPtr<IPierCollection> piers;
   m_pBridge->get_Piers(&piers);

   CComPtr<IBridgePier> firstPier;
   piers->get_Item(0, &firstPier);

   CComPtr<IStation> firstStation;
   firstPier->get_Station(&firstStation);

   CComPtr<IAlignment> alignment;
   m_pBridge->get_Alignment(&alignment);

   alignment->DistanceBetweenStations(CComVariant(firstStation), CComVariant(station), pXb);
   ATLASSERT(0 <= *pXb);

   return S_OK;
}

STDMETHODIMP CBridgePier::get_Station(IStation* *station)
{
   if ( m_pPierLine == nullptr )
   {
      return m_TestStation.CopyTo(station);
   }

   return m_pPierLine->get_Station(station);
}

STDMETHODIMP CBridgePier::get_Direction(IDirection* *direction)
{
   return m_pPierLine->get_Direction(direction);
}

STDMETHODIMP CBridgePier::get_SkewAngle(IAngle* *skewAngle)
{
   // this replaces the CPierImpl implementation
   return m_pPierLine->get_Skew(skewAngle);
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CBridgePier::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);
   CComVariant var;
   load->BeginUnit(CComBSTR("BridgePier"));

#pragma Reminder("IMPLMEENT: Load BridgePier")

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CBridgePier::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("BridgePier"),1.0);

#pragma Reminder("IMPLMEENT: Save BridgePier")

   save->EndUnit();

   return S_OK;
}
