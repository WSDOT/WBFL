///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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
#include "Span.h"
#include "LongitudinalPierDescription.h"
#include "TransversePierDescription.h"
#include "Connection.h"
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
   m_Station.CoCreateInstance(CLSID_Station);
   m_Station->put_Value(0);
   AdviseStation();

   CComObject<CLongitudinalPierDescription>* pLPD;
   CComObject<CLongitudinalPierDescription>::CreateInstance(&pLPD);
   pLPD->SetPier(this);
   m_LongPierDesc = pLPD;
   AdviseLongPierDesc();

   CComObject<CConnection>* pConnection;
   CComObject<CConnection>::CreateInstance(&pConnection);
   m_Connection[qcbBefore] = pConnection;

   pConnection = NULL;
   CComObject<CConnection>::CreateInstance(&pConnection);
   m_Connection[qcbAfter] = pConnection;

   return S_OK;
}

void CPier::FinalRelease()
{
   UnadviseLongPierDesc();
   UnadviseTransPierDesc();
   UnadviseStation();

   m_Station.Release();
   m_TransPierDesc.Release();
   m_LongPierDesc.Release();

   m_Connection[qcbBefore].Release();
   m_Connection[qcbAfter].Release();
}

void CPier::SetBridge(IGenericBridge* pBridge)
{
   m_pBridge = pBridge; 

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

void CPier::SetStationValue(Float64 newVal)
{
   // Disconnect from station object so we don't hear the OnStationChanged event
   UnadviseStation();

   m_Station->put_Value(newVal);

   // Reconnect to station
   AdviseStation();
}

void CPier::SetStationValueEx(Float64 newVal)
{
   // Moves this pier, and all piers ahead on station, maintaining span length for
   // all ahead on station piers
   CComPtr<IStation> objStation;
   get_Station(&objStation);
   Float64 currValue;
   objStation->get_Value(&currValue);
   Float64 delta = newVal - currValue;

   if ( !IsZero(delta) )
   {
      // First set the station for this pier
      SetStationValue(newVal);

      // Now set it for all ahead on station piers
      CSpan* pSpan = GetNextSpan();
      while ( pSpan )
      {
         CPier* pPier = pSpan->GetNextPier();
         CComPtr<IStation> station;
         pPier->get_Station(&station);
         Float64 staValue;
         station->get_Value(&staValue);

         // Determine how much the pier (station) has moved so the ahead on station piers
         // can be moved the same amount
         Float64 newStation = staValue + delta;

         // Sets the station without firing events or generating transactions
         pPier->SetStationValue(newStation);

         pSpan = pPier->GetNextSpan();
      }
   }
}

STDMETHODIMP CPier::Clone(IPier* *clone)
{
   // Creates a deep copy...
   // Cloning does not include refereces to the adjacent spans
   // Doing so would totally mess up pier/span/pier traversal
   //
   // cloned pier->span->ORIGINAL PIER->span->original pier...
   CHECK_RETOBJ(clone);

   CComObject<CPier>* pClone;
   CComObject<CPier>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->put_Orientation(m_bstrOrientation);

   // New a new Station object (put is by reference, we need by value)
   CComPtr<IStation> stationClone;
   stationClone.CoCreateInstance(CLSID_Station);
   Float64 value;
   m_Station->get_Value(&value);
   stationClone->put_Value(value);
   pClone->putref_Station(stationClone);

   // casting because Clone is on the private side of things
   CLongitudinalPierDescription* pLPD = dynamic_cast<CLongitudinalPierDescription*>(m_LongPierDesc.p);
   CComPtr<ILongitudinalPierDescription> lpdClone;
   pLPD->Clone(&lpdClone);
   pClone->SetLongitudinalPierDescription(lpdClone);

   if ( m_TransPierDesc )
   {
      CTransversePierDescription* pTPD = dynamic_cast<CTransversePierDescription*>(m_TransPierDesc.p);
      CComPtr<ITransversePierDescription> tpdClone;
      pTPD->Clone(&tpdClone);
      pClone->SetTransversePierDescription(tpdClone);
   }

   return S_OK;
}

void CPier::SetLongitudinalPierDescription(ILongitudinalPierDescription* cloneLPD)
{
   if ( m_LongPierDesc )
   {
      UnadviseLongPierDesc();
   }

   CLongitudinalPierDescription* pClone = dynamic_cast<CLongitudinalPierDescription*>(cloneLPD);
   pClone->SetPier(this);

   m_LongPierDesc = cloneLPD;

   AdviseLongPierDesc();
}

void CPier::SetTransversePierDescription(ITransversePierDescription* cloneTPD)
{
   if ( m_TransPierDesc )
      UnadviseTransPierDesc();

   CTransversePierDescription* pClone = dynamic_cast<CTransversePierDescription*>(cloneTPD);
   pClone->SetPier(this);

   m_TransPierDesc = cloneTPD;

   AdviseTransPierDesc();
}

void CPier::RenameStageReferences(BSTR bstrOldName,BSTR bstrNewName)
{
   CLongitudinalPierDescription* pLPD = dynamic_cast<CLongitudinalPierDescription*>(m_LongPierDesc.p);
   pLPD->RenameStageReferences(bstrOldName,bstrNewName);
}

void CPier::AddDataForStage(BSTR bstrName)
{
   CLongitudinalPierDescription* pLPD = dynamic_cast<CLongitudinalPierDescription*>(m_LongPierDesc.p);
   pLPD->AddDataForStage(bstrName);
}

void CPier::RemoveDataForStage(BSTR bstrName)
{
   CLongitudinalPierDescription* pLPD = dynamic_cast<CLongitudinalPierDescription*>(m_LongPierDesc.p);
   pLPD->RemoveDataForStage(bstrName);
}

//////////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CPier::get_Station(IStation* *station)
{
   CHECK_RETOBJ(station);
   (*station) = m_Station;
   (*station)->AddRef();
   return S_OK;
}

STDMETHODIMP CPier::putref_Station(IStation* station)
{
   CHECK_IN(station);

   if ( m_Station.IsEqualObject(station) )
      return S_OK;

   UnadviseStation();
   m_Station = station;
   AdviseStation();

   Fire_OnPierChanged(this);
   return S_OK;
}

STDMETHODIMP CPier::get_Orientation(BSTR* orientation)
{
   CHECK_RETVAL(orientation);

   *orientation = m_bstrOrientation.Copy();

   return S_OK;
}

STDMETHODIMP CPier::put_Orientation(BSTR bstrOrientation)
{
   if ( m_bstrOrientation == bstrOrientation )
      return S_OK;

   HRESULT hr = ValidateOrientation(bstrOrientation);

   if ( FAILED(hr) )
      return CComCoClass<CPier>::Error("Invalid pier orientation",IID_IPier,hr);

   m_bstrOrientation = bstrOrientation;
   Fire_OnPierChanged(this);

   return S_OK;
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
   USES_CONVERSION;
   CHECK_RETOBJ(direction);

   // Convert the orientation string to something we can work with
   // Make it upper case for easy conparison
   std::_tstring strOrientation(OLE2T(m_bstrOrientation));
   std::transform(strOrientation.begin(),strOrientation.end(),strOrientation.begin(),(int(*)(int))std::toupper);

   // Get the alignment object

   CComPtr<IAlignment> alignment;
   m_pBridge->get_Alignment(&alignment);

   // process the orientation string
   if ( strOrientation.compare(_T("N")) == 0 || strOrientation.compare(_T("NORMAL")) == 0 )
   {
      // Pier is normal to the alignment
      CComPtr<IDirection> normal;
      alignment->Normal(CComVariant(m_Station),&normal); // This is the normal to the right

      // We want the normal to the left... Increment by 180 degrees
      normal->IncrementBy(CComVariant(M_PI));

      (*direction) = normal;
      (*direction)->AddRef();
      return S_OK;
   }
   else if (strOrientation[0] == _T('N') || strOrientation[0] == _T('S'))
   {
      // Pier is defined by an explicit bearing
      CComPtr<IDirection> brg;
      brg.CoCreateInstance(CLSID_Direction);
      brg->FromString(m_bstrOrientation);

      // if the bearing is to the right of the alignment, reverse it
      CComPtr<IDirection> align_dir;
      alignment->Bearing(CComVariant(m_Station),&align_dir);

      CComPtr<IAngle> angle;
      brg->AngleBetween(align_dir,&angle);

      Float64 value;
      angle->get_Value(&value);

      // if the angle between is between 0 and 180, bearing is to the left
      if ( M_PI < value )
      {
         // bearing is to the right of the alignment.... increment by 180 degrees
         brg->IncrementBy(CComVariant(M_PI));
      }

      (*direction) = brg;
      (*direction)->AddRef();
      return S_OK;
   }
   else
   {
      // Pier is defined by a skew angle
      CComPtr<IDirection> normal;
      alignment->Normal(CComVariant(m_Station),&normal); // This is the normal to the right

      // We want the normal to the left... Increment by 180 degrees
      normal->IncrementBy(CComVariant(M_PI));

      CComPtr<IAngle> angle;
      angle.CoCreateInstance(CLSID_Angle);
      angle->FromString(m_bstrOrientation);

      normal->IncrementBy(CComVariant(angle));

      (*direction) = normal;
      (*direction)->AddRef();
      return S_OK;
   }

   return E_FAIL;
}

STDMETHODIMP CPier::get_SkewAngle(IAngle* *skewAngle)
{
   CHECK_RETOBJ(skewAngle);

   CComPtr<IDirection> pierDirection;
   get_Direction(&pierDirection);

   CComPtr<IDirection> normal;
   CComPtr<IAlignment> alignment;
   m_pBridge->get_Alignment(&alignment);
   alignment->Normal(CComVariant(m_Station),&normal); // This is the normal to the right

   // We want the normal to the left... Increment by 180 degrees
   normal->IncrementBy(CComVariant(M_PI));

   // Skew angle is the difference between the pier direction and the normal
   pierDirection->AngleBetween(normal,skewAngle);

   // If the angle is more than PI/2, it is a right skew... Right skews are negative... adjust
   Float64 angle;
   (*skewAngle)->get_Value(&angle);
   if ( PI_OVER_2 < angle )
   {
      angle = angle - TWO_PI;
      (*skewAngle)->put_Value(angle);
   }

   return S_OK;
}

STDMETHODIMP CPier::get_GirderSpacing(PositionType posType,IGirderSpacing** ppGirderSpacing)
{
   CHECK_RETOBJ(ppGirderSpacing);

   if ( posType == qcbBefore && m_pPrevSpan )
   {
      return m_pPrevSpan->get_GirderSpacing(etEnd,ppGirderSpacing);
   }
   else if ( posType == qcbAfter && m_pNextSpan )
   {
      return m_pNextSpan->get_GirderSpacing(etStart,ppGirderSpacing);
   }
   else
   {
      (*ppGirderSpacing) = NULL;
      return S_OK;
   }
}

STDMETHODIMP CPier::get_Connection(PositionType posType,IConnection** ppConnection)
{
   CHECK_RETOBJ(ppConnection);
   (*ppConnection) = m_Connection[posType];
   (*ppConnection)->AddRef();
   return S_OK;
}

STDMETHODIMP CPier::CreateTransversePierDescription()
{
   if ( !m_TransPierDesc )
   {
      CComObject<CTransversePierDescription>* pTPD;
      CComObject<CTransversePierDescription>::CreateInstance(&pTPD);
      m_TransPierDesc = pTPD;

      AdviseTransPierDesc();

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

STDMETHODIMP CPier::RemoveTransversePierDescription()
{
   if ( m_TransPierDesc )
   {
      UnadviseTransPierDesc();
   }

   m_TransPierDesc.Release();
   return S_OK;
}

STDMETHODIMP CPier::get_PrevSpan(ISpan** ppSpan)
{
   CHECK_RETOBJ(ppSpan);
   if ( m_pPrevSpan )
   {
      (*ppSpan) = m_pPrevSpan;
      (*ppSpan)->AddRef();
   }
   else
   {
      (*ppSpan) = NULL;
   }

   return S_OK;
}

STDMETHODIMP CPier::get_NextSpan(ISpan** ppSpan)
{
   CHECK_RETOBJ(ppSpan);
   if ( m_pNextSpan )
   {
      (*ppSpan) = m_pNextSpan;
      (*ppSpan)->AddRef();
   }
   else
   {
      (*ppSpan) = NULL;
   }

   return S_OK;
}

STDMETHODIMP CPier::get_Index(PierIndexType* pIndex)
{
   CHECK_RETVAL(pIndex);
   *pIndex = m_Index;
   return S_OK;
}

/////////////////////////////////////////////////////
// IStationEvents implementation
STDMETHODIMP CPier::OnStationChanged(Float64 newVal)
{
   // Both this pier and the AdaptStation object listen to events on the aggregated station object
   // The responsiblity of the pier object is to move all ahead on station piers 
   // and to forward the event as an OnPierChanged event.
   //
   // The responsiblity of the adaptor is to create a transaction so that the property change
   // can be undone
   SetStationValueEx(newVal);


   // Fire event last so that the bridge is in a correct configuration
   // NOTE: When the ahead on station piers fire their events, the bridge won't be in
   // correct configuration... Stations may "seem" to be out of order
   Fire_OnPierChanged(this);
   
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CPier::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);
   CComVariant var;
   load->BeginUnit(CComBSTR("Pier"));

   load->get_Property(CComBSTR("Station"),&var);
   m_Station->put_Value(var.dblVal);

   load->get_Property(CComBSTR("Orientation"),&var);
   m_bstrOrientation = var.bstrVal;
   var.Clear();

   CComQIPtr<IStructuredStorage2> ssLPD(m_LongPierDesc);
   ssLPD->Load(load);

   load->get_Property(CComBSTR("TransPierDesc"),&var);
   if ( var.boolVal == VARIANT_TRUE )
   {
      CreateTransversePierDescription();
      CComQIPtr<IStructuredStorage2> ssTPD(m_TransPierDesc);
      ssTPD->Load(load);
   }

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CPier::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("Pier"),1.0);

   Float64 value;
   m_Station->get_Value(&value);
   save->put_Property(CComBSTR("Station"),CComVariant(value));

   save->put_Property(CComBSTR("Orientation"),CComVariant(m_bstrOrientation));

   CComQIPtr<IStructuredStorage2> ssLPD(m_LongPierDesc);
   ssLPD->Save(save);

   if (m_TransPierDesc )
   {
      save->put_Property(CComBSTR("TransPierDesc"),CComVariant(VARIANT_TRUE));
      CComQIPtr<IStructuredStorage2> ssTPD(m_TransPierDesc);
      ssTPD->Save(save);
   }
   else
   {
      save->put_Property(CComBSTR("TransPierDesc"),CComVariant(VARIANT_FALSE));
   }

   save->EndUnit();

   return S_OK;
}

//////////////////////////////////////////////////////
// Helper methods
HRESULT CPier::AdviseLongPierDesc()
{
   HRESULT hr = m_LongPierDesc.Advise(GetUnknown(),IID_ILongitudinalPierDescriptionEvents,&m_dwLPDCookie);
   ATLASSERT( SUCCEEDED(hr) );

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CPier::UnadviseLongPierDesc()
{
   InternalAddRef(); // conteract InternalRelease() in advise
   CComQIPtr<IConnectionPointContainer> pCPC(m_LongPierDesc);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(IID_ILongitudinalPierDescriptionEvents,&pCP);

   HRESULT hr = pCP->Unadvise(m_dwLPDCookie);
   ATLASSERT( SUCCEEDED(hr) );

   return hr;
}

HRESULT CPier::AdviseTransPierDesc()
{
   if ( m_TransPierDesc == NULL )
      return S_OK;

   HRESULT hr = m_TransPierDesc.Advise(GetUnknown(),IID_ITransversePierDescriptionEvents,&m_dwTPDCookie);
   ATLASSERT( SUCCEEDED(hr) );

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CPier::UnadviseTransPierDesc()
{
   if ( m_TransPierDesc == NULL )
      return S_OK;

   InternalAddRef(); // conteract InternalRelease() in advise
   CComQIPtr<IConnectionPointContainer> pCPC(m_TransPierDesc);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(IID_ITransversePierDescriptionEvents,&pCP);

   HRESULT hr = pCP->Unadvise(m_dwTPDCookie);
   ATLASSERT( SUCCEEDED(hr) );

   return hr;
}

HRESULT CPier::AdviseStation()
{
   HRESULT hr = m_Station.Advise(GetUnknown(),IID_IStationEvents,&m_dwStationCookie);
   ATLASSERT( SUCCEEDED(hr) );

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CPier::UnadviseStation()
{
   InternalAddRef(); // conteract InternalRelease() in advise
   CComQIPtr<IConnectionPointContainer> pCPC(m_Station);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(IID_IStationEvents,&pCP);

   HRESULT hr = pCP->Unadvise(m_dwStationCookie);
   ATLASSERT( SUCCEEDED(hr) );

   return hr;
}




