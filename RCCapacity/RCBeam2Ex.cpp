///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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

// RCBeam2ExEx.cpp : Implementation of CRCBeam2Ex2
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "RCBeam2Ex.h"
#include <WBFLGeometry.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRCBeam2Ex
HRESULT CRCBeam2Ex::FinalConstruct()
{
   HRESULT hr = m_UnitServer.CoCreateInstance(CLSID_UnitServer);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CComPtr<IUnitConvert> convert;
   m_UnitServer->get_UnitConvert(&convert);

   convert->ConvertToBaseUnits(    7.0,CComBSTR("ksi"),&m_FcBeam);
   convert->ConvertToBaseUnits(    4.0,CComBSTR("ksi"),&m_FcSlab);
   convert->ConvertToBaseUnits(  270.0,CComBSTR("ksi"),&m_Fpu);
   convert->ConvertToBaseUnits(  149.0,CComBSTR("ksi"),&m_Fpe);
   convert->ConvertToBaseUnits(   60.0,CComBSTR("ksi"),&m_Fy);
   convert->ConvertToBaseUnits(29000.0,CComBSTR("ksi"),&m_Es);
   convert->ConvertToBaseUnits(28600.0,CComBSTR("ksi"),&m_Eps);

   convert->ConvertToBaseUnits( 6.0,CComBSTR("in"),&m_hf);
   convert->ConvertToBaseUnits(72.0,CComBSTR("in"),&m_b);

   Float64 h, bw;
   convert->ConvertToBaseUnits(62.0,CComBSTR("in"),&h);
   convert->ConvertToBaseUnits( 6.0,CComBSTR("in"),&bw);
   CComPtr<IRectangle> beam;
   hr = beam.CoCreateInstance(CLSID_Rect);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
      return hr;

   beam->put_Height(h);
   beam->put_Width(bw);

   beam.QueryInterface(&m_pBeam);

   m_Fpy    = 0.9*m_Fpu;

   return S_OK;
}

void CRCBeam2Ex::FinalRelease()
{
   m_UnitServer.Release();
}


STDMETHODIMP CRCBeam2Ex::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRCBeam2Ex,
      &IID_IStructuredStorage2
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CRCBeam2Ex::get_b(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_b;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::put_b(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_b = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_hf(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_hf;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::put_hf(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_hf = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_fy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Fy;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::put_fy(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Fy = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_fpu(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Fpu;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::put_fpu(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Fpu = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_fpy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Fpy;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::put_fpy(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Fpy = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_FcSlab(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_FcSlab;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::put_FcSlab(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_FcSlab = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_FcBeam(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_FcBeam;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::put_FcBeam(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_FcBeam = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_fpe(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Fpe;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::put_fpe(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Fpe = newVal;
	return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_Beam(IShape* *pVal)
{
   CHECK_RETOBJ(pVal);

   (*pVal) = m_pBeam;
   (*pVal)->AddRef();
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::putref_Beam(IShape* newVal)
{
   CHECK_IN(newVal);

   m_pBeam = newVal;
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_Es(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Es;
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::put_Es(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_Es = newVal;
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_Eps(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Eps;
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::put_Eps(Float64 newVal)
{
   if ( newVal < 0 || IsZero(newVal) )
      return E_INVALIDARG;

   m_Eps = newVal;
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::AddRebarLayer(Float64 ds,Float64 As,Float64 devFactor)
{
   if ( IsLE(ds,0.0) )
      return E_INVALIDARG;

   if ( As < 0 )
      return E_INVALIDARG;

   if ( devFactor < 0 || 1.0 < devFactor)
      return E_INVALIDARG;

   m_Rebar.emplace_back(ds,As,devFactor);

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_RebarLayerCount(CollectionIndexType * count)
{
   CHECK_RETVAL(count);
   *count = m_Rebar.size();
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_RebarLayerDepth(CollectionIndexType index,Float64 * ds)
{
   CHECK_RETVAL(ds);
   if ( index < 0 || (CollectionIndexType)m_Rebar.size() <= index )
      return E_INVALIDARG;

   *ds = m_Rebar[index].ds;

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_RebarLayerSteel(CollectionIndexType index,Float64 * As)
{
   CHECK_RETVAL(As);
   if ( index < 0 || (CollectionIndexType)m_Rebar.size() <= index )
      return E_INVALIDARG;

   *As = m_Rebar[index].As;

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_RebarLayerDevFactor(CollectionIndexType index,Float64 * devFactor)
{
   CHECK_RETVAL(devFactor);
   if ( index < 0 || (CollectionIndexType)m_Rebar.size() <= index )
      return E_INVALIDARG;

   *devFactor = m_Rebar[index].DevFactor;

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::GetRebarLayer(CollectionIndexType index,Float64 * ds,Float64 * As,Float64 * devFactor)
{
   CHECK_RETVAL(ds);
   CHECK_RETVAL(As);
   CHECK_RETVAL(devFactor);
   if ( index < 0 || (CollectionIndexType)m_Rebar.size() <= index )
      return E_INVALIDARG;

   *ds        = m_Rebar[index].ds;
   *As        = m_Rebar[index].As;
   *devFactor = m_Rebar[index].DevFactor;

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::RemoveRebarLayer(CollectionIndexType index)
{
   if ( index < 0 || (CollectionIndexType)m_Rebar.size() <= index )
      return E_INVALIDARG;

   m_Rebar.erase(m_Rebar.begin() + index);
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::ClearRebarLayers()
{
   m_Rebar.clear();
   return S_OK;
}


STDMETHODIMP CRCBeam2Ex::AddStrandLayer(Float64 dps,Float64 Aps,Float64 devFactor)
{
   if ( IsLE(dps,0.0) )
      return E_INVALIDARG;

   if ( Aps < 0 )
      return E_INVALIDARG;

   if ( devFactor < 0 || 1.0 < devFactor)
      return E_INVALIDARG;

   m_Strands.emplace_back(dps,Aps,devFactor);

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_StrandLayerCount(CollectionIndexType * count)
{
   CHECK_RETVAL(count);
   *count = m_Strands.size();
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_StrandLayerDepth(CollectionIndexType index,Float64 * dps)
{
   CHECK_RETVAL(dps);
   if ( index < 0 || (CollectionIndexType)m_Strands.size() <= index )
      return E_INVALIDARG;

   *dps = m_Strands[index].ds;

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_StrandLayerSteel(CollectionIndexType index,Float64 * Aps)
{
   CHECK_RETVAL(Aps);
   if ( index < 0 || (CollectionIndexType)m_Strands.size() <= index )
      return E_INVALIDARG;

   *Aps = m_Strands[index].As;

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_StrandLayerDevFactor(CollectionIndexType index,Float64 * devFactor)
{
   CHECK_RETVAL(devFactor);
   if ( index < 0 || (CollectionIndexType)m_Strands.size() <= index )
      return E_INVALIDARG;

   *devFactor = m_Strands[index].DevFactor;

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::GetStrandLayer(CollectionIndexType index,Float64 * dps,Float64 * Aps,Float64 * devFactor)
{
   CHECK_RETVAL(dps);
   CHECK_RETVAL(Aps);
   CHECK_RETVAL(devFactor);
   if ( index < 0 || (CollectionIndexType)m_Strands.size() <= index )
      return E_INVALIDARG;

   *dps       = m_Strands[index].ds;
   *Aps       = m_Strands[index].As;
   *devFactor = m_Strands[index].DevFactor;

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::RemoveStrandLayer(CollectionIndexType index)
{
   if ( index < 0 || (CollectionIndexType)m_Strands.size() <= index )
      return E_INVALIDARG;

   m_Strands.erase(m_Strands.begin() + index);
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::ClearStrandLayers()
{
   m_Strands.clear();
   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::get_UnitServer(IUnitServer** ppVal )
{
   CHECK_RETOBJ(ppVal);

   (*ppVal) = m_UnitServer;
   (*ppVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::putref_UnitServer(IUnitServer* pNewVal )
{
   CHECK_IN(pNewVal);

   m_UnitServer = pNewVal;
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CRCBeam2Ex::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("RCBeam2Ex"),1.0);

   pSave->put_Property(CComBSTR("b"),  CComVariant(m_b));
   pSave->put_Property(CComBSTR("hf"), CComVariant(m_hf));
   pSave->put_Property(CComBSTR("Beam"),CComVariant(m_pBeam));

   pSave->BeginUnit(CComBSTR("Rebar"),1.0);
   pSave->put_Property(CComBSTR("Count"),CComVariant(m_Rebar.size()));
   std::vector<Reinforcement>::iterator rebar_iter;
   for (rebar_iter = m_Rebar.begin(); rebar_iter != m_Rebar.end(); rebar_iter++ )
   {
      pSave->put_Property(CComBSTR("ds"),CComVariant((*rebar_iter).ds));
      pSave->put_Property(CComBSTR("As"),CComVariant((*rebar_iter).As));
      pSave->put_Property(CComBSTR("DevFactor"),CComVariant((*rebar_iter).DevFactor));
   }
   pSave->EndUnit();

   pSave->BeginUnit(CComBSTR("Strand"),1.0);
   pSave->put_Property(CComBSTR("Count"),CComVariant(m_Strands.size()));
   std::vector<Reinforcement>::iterator strand_iter;
   for (strand_iter = m_Strands.begin(); strand_iter != m_Strands.end(); strand_iter++ )
   {
      pSave->put_Property(CComBSTR("dps"),CComVariant((*rebar_iter).ds));
      pSave->put_Property(CComBSTR("Aps"),CComVariant((*rebar_iter).As));
      pSave->put_Property(CComBSTR("DevFactor"),CComVariant((*rebar_iter).DevFactor));
   }
   pSave->EndUnit();

   pSave->put_Property(CComBSTR("Es"), CComVariant(m_Es));
   pSave->put_Property(CComBSTR("Eps"),CComVariant(m_Eps));

   pSave->put_Property(CComBSTR("FcBeam"),CComVariant(m_FcBeam));
   pSave->put_Property(CComBSTR("FcSlab"),CComVariant(m_FcSlab));

   pSave->put_Property(CComBSTR("fpu"),CComVariant(m_Fpu));
   pSave->put_Property(CComBSTR("fpe"),CComVariant(m_Fpe));
   pSave->put_Property(CComBSTR("fpy"),CComVariant(m_Fpy));
   pSave->put_Property(CComBSTR("fy"), CComVariant(m_Fy));

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CRCBeam2Ex::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   VARIANT_BOOL bEnd;
   CComVariant var;

   pLoad->BeginUnit(CComBSTR("RCBeam2Ex"));

   if ( FAILED(pLoad->get_Property(CComBSTR("b"),  &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_b = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("hf"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_hf = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("Beam"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_pBeam.Release();
   var.pdispVal->QueryInterface(&m_pBeam);



   m_Rebar.clear();
   pLoad->BeginUnit(CComBSTR("Rebar"));

   CollectionIndexType nRebarLayers;
   if ( FAILED(pLoad->get_Property(CComBSTR("Count"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   nRebarLayers = var.iVal;

   for ( CollectionIndexType rebar = 0; rebar < nRebarLayers; rebar++ )
   {
      Float64 ds, As, devFactor;
      if ( FAILED(pLoad->get_Property(CComBSTR("ds"),&var) ) )
         return STRLOAD_E_INVALIDFORMAT;
      ds = var.dblVal;

      if ( FAILED(pLoad->get_Property(CComBSTR("As"),&var) ) )
         return STRLOAD_E_INVALIDFORMAT;
      As = var.dblVal;

      if ( FAILED(pLoad->get_Property(CComBSTR("DevFactor"),&var) ) )
         return STRLOAD_E_INVALIDFORMAT;
      devFactor = var.dblVal;
      
      m_Rebar.emplace_back(ds,As,devFactor);
   }

   pLoad->EndUnit(&bEnd);




   m_Strands.clear();
   pLoad->BeginUnit(CComBSTR("Strand"));

   CollectionIndexType nStrandLayers;
   if ( FAILED(pLoad->get_Property(CComBSTR("Count"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   nStrandLayers = var.iVal;

   for ( CollectionIndexType strand = 0; strand < nStrandLayers; strand++ )
   {
      Float64 dps, Aps, devFactor;
      if ( FAILED(pLoad->get_Property(CComBSTR("dps"),&var) ) )
         return STRLOAD_E_INVALIDFORMAT;
      dps = var.dblVal;

      if ( FAILED(pLoad->get_Property(CComBSTR("Aps"),&var) ) )
         return STRLOAD_E_INVALIDFORMAT;
      Aps = var.dblVal;

      if ( FAILED(pLoad->get_Property(CComBSTR("DevFactor"),&var) ) )
         return STRLOAD_E_INVALIDFORMAT;
      devFactor = var.dblVal;
      
      m_Strands.emplace_back(dps,Aps,devFactor);
   }

   pLoad->EndUnit(&bEnd);



   if ( FAILED(pLoad->get_Property(CComBSTR("Es"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Es = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("Eps"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Eps = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("FcBeam"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_FcBeam = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("FcSlab"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_FcSlab = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("fpu"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Fpu = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("fpe"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Fpe = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("fpy"),&var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Fpy = var.dblVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("fy"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_Fy = var.dblVal;

   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
