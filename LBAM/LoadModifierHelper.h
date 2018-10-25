///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2016  Washington State Department of Transportation
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

// LoadModifierHelper - encapsulates common code/behaviour for classes that support loadmodifiers

#ifndef __LOADMODIFIERHELPER_H_
#define __LOADMODIFIERHELPER_H_

const int LM_ARRSIZE=lctUserDefined+1;


class CLoadModifierHelper
{
public:

   CLoadModifierHelper()
   {
      // initialize all factors to 1.0
      Float64* pnt = &m_LoadModifiers[0][0];
      for (int i=0; i<LM_ARRSIZE*2; i++)
      {
         *pnt++ = 1.0;
      }
   }

	STDMETHOD(GetLoadModifier)(LoadCombinationType type, Float64 *minVal, Float64* maxVal)
   {
      CHECK_RETVAL(minVal);
      CHECK_RETVAL(maxVal);

      if (type<0 || type>lctUserDefined)
         return E_INVALIDARG;

      Float64* pnt = &(m_LoadModifiers[type][0]);
      *minVal = *pnt++;
      *maxVal = *pnt;

   	return S_OK;   
   }

	STDMETHOD(SetLoadModifier)(LoadCombinationType type, Float64 minVal, Float64 maxVal, bool* doFire)
   {
      if (minVal<=0.0 || maxVal<=0.0)
         return E_INVALIDARG;

      if (type<0 || type>lctUserDefined)
         return E_INVALIDARG;

      *doFire = false;

      Float64* pnt = &(m_LoadModifiers[type][0]);
      if (minVal != *pnt)
      {
         *pnt = minVal;
         *doFire = true;
      }

      pnt++;
      if (maxVal != *pnt)
      {
         *pnt = maxVal;
         *doFire = true;
      }

   	return S_OK;
   }


STDMETHODIMP Load(IStructuredLoad2 * pload)
{
   HRESULT hr;
   _variant_t var;
   hr = pload->get_Property(_bstr_t("MinServiceLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctService][0] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MaxServiceLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctService][1] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MinStrengthLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctStrength][0] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MaxStrengthLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctStrength][1] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MinExtremeEventLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctExtremeEvent][0] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MaxExtremeEventLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctExtremeEvent][1] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MinFatigueLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctFatigue][0] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MaxFatigueLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctFatigue][1] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MinPermitLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctPermit][0] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MaxPermitLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctPermit][1] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MinUserDefinedLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctUserDefined][0] = var;

   var.Clear();
   hr = pload->get_Property(_bstr_t("MaxUserDefinedLoadModifier"),&var);
   if (FAILED(hr))
      return hr;

   m_LoadModifiers[lctUserDefined][1] = var;

   var.Clear();



   return S_OK;
}

STDMETHODIMP Save(IStructuredSave2 * psave)
{
   HRESULT hr;

   hr = psave->put_Property(CComBSTR("MinServiceLoadModifier"),_variant_t(m_LoadModifiers[lctService][0]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MaxServiceLoadModifier"),_variant_t(m_LoadModifiers[lctService][1]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MinStrengthLoadModifier"),_variant_t(m_LoadModifiers[lctStrength][0]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MaxStrengthLoadModifier"),_variant_t(m_LoadModifiers[lctStrength][1]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MinExtremeEventLoadModifier"),_variant_t(m_LoadModifiers[lctExtremeEvent][0]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MaxExtremeEventLoadModifier"),_variant_t(m_LoadModifiers[lctExtremeEvent][1]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MinFatigueLoadModifier"),_variant_t(m_LoadModifiers[lctFatigue][0]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MaxFatigueLoadModifier"),_variant_t(m_LoadModifiers[lctFatigue][1]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MinPermitLoadModifier"),_variant_t(m_LoadModifiers[lctPermit][0]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MaxPermitLoadModifier"),_variant_t(m_LoadModifiers[lctPermit][1]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MinUserDefinedLoadModifier"),_variant_t(m_LoadModifiers[lctUserDefined][0]));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("MaxUserDefinedLoadModifier"),_variant_t(m_LoadModifiers[lctUserDefined][1]));
   if (FAILED(hr))
      return hr;

   return S_OK;
}

private:
   Float64 m_LoadModifiers[LM_ARRSIZE][2];
};

#endif