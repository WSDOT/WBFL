// InfluenceResultRequest.cpp : Implementation of CInfluenceResultRequest
#include "stdafx.h"
#include "LBAMTestFrame.h"
#include "LBAMTestFrame.hh"
#include "InfluenceResultRequest.h"

#include <sstream>
/////////////////////////////////////////////////////////////////////////////
// CInfluenceResultRequest

STDMETHODIMP CInfluenceResultRequest::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IInfluenceResultRequest
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CInfluenceResultRequest::get_PoiId(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_PoiId;

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::put_PoiId(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_PoiId = newVal;

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::get_Stage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Stage.copy();

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::put_Stage(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Stage = newVal;

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::get_ForceEffectType(ForceEffectType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_ForceEffectType;

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::get_ResultsOrientation(ResultsOrientation *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_ResultsOrientation;

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::put_ResultsOrientation(ResultsOrientation newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_ResultsOrientation = newVal;

	return S_OK;
}


STDMETHODIMP CInfluenceResultRequest::put_ForceEffectType(ForceEffectType newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_ForceEffectType = newVal;

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::get_ResponseType(ResponseType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_ResponseType;

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::put_ResponseType(ResponseType newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_ResponseType = newVal;

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::get_InfluenceLine(IInfluenceLine **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (m_InfluenceLine!=NULL)
   {
	   *pVal = m_InfluenceLine;
      (*pVal)->AddRef();
   }
   else
   {
      *pVal=0;
   }

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::put_InfluenceLine(IInfluenceLine *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_InfluenceLine = newVal;

	return S_OK;
}


STDMETHODIMP CInfluenceResultRequest::get_InfluenceProcessing(InfluenceProcessingType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_InfluenceProcessingType;

	return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::put_InfluenceProcessing(InfluenceProcessingType newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_InfluenceProcessingType = newVal;

	return S_OK;
}


STDMETHODIMP CInfluenceResultRequest::get_Description(/*[out, retval]*/ BSTR *pVal)
{
   std::stringstream os;

   os << "Influence Line at POI "<<m_PoiId<<" for stage '"<< (char*)m_Stage<<"'";

   if (m_ResponseType==rtForces)
   {
      if (m_ForceEffectType==fetFx)
         os << " for Fx";
      else if (m_ForceEffectType==fetFy)
         os << " for Fy";
      else if (m_ForceEffectType==fetMz)
         os << " for Mz";
   }
   else if (m_ResponseType==rtDeflections)
   {
      if (m_ForceEffectType==fetFx)
         os << " for Dx";
      else if (m_ForceEffectType==fetFy)
         os << " for Dy";
      else if (m_ForceEffectType==fetMz)
         os << " for Rz";
   }
   else
      ATLASSERT(0);

   if (m_InfluenceProcessingType==iptRaw)
      os<<", Raw Values";
   else if(m_InfluenceProcessingType==iptFlattenNegative)
      os<<", Negative Values Flattened";
   else
      os<<", Positive Values Flattened";

   std::string tmp(os.str());
   _bstr_t desc(tmp.c_str());
   *pVal = desc.copy();

   return S_OK;
}

// IStructuredStorage2
static const double MY_VER=1.0;

STDMETHODIMP CInfluenceResultRequest::Load(IStructuredLoad2 * pload)
{
   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("InfluenceResultRequest"));
   if (FAILED(hr))
      return hr;

   double ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      _variant_t var;
      hr = pload->get_Property(_bstr_t("Stage"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t stage(var);
      m_Stage = (const char*)stage;
      var.Clear();

      hr = pload->get_Property(_bstr_t("PoiId"),&var);
      if (FAILED(hr))
         return hr;

      m_PoiId = (long)var;
      var.Clear();

      hr = pload->get_Property(_bstr_t("ForceEffectType"),&var);
      if (FAILED(hr))
         return hr;

      long type = (long)var;
      if (type==fetFx)
      {
         m_ForceEffectType = fetFx;
      }
      else if (type== fetFy)
      {
         m_ForceEffectType = fetFy;
      }
      else if (type== fetMz)
      {
         m_ForceEffectType = fetMz;
      }
      else
      {
         THROW_LBAMTF(INVALID_FORCE_EFFECT);
      }

      var.Clear();

      hr = pload->get_Property(_bstr_t("ResponseType"),&var);
      if (FAILED(hr))
         return hr;

      type = (long)var;
      if (type==rtForces)
      {
         m_ResponseType = rtForces;
      }
      else if (type== rtDeflections)
      {
         m_ResponseType = rtDeflections;
      }
      else
      {
         THROW_LBAMTF(INVALID_RESPONSE_TYPE);
      }

      var.Clear();

      hr = pload->get_Property(_bstr_t("ResultsOrientation"),&var);
      if (FAILED(hr))
         return hr;

      type = (long)var;
      if (type==roGlobal)
      {
         m_ResultsOrientation = roGlobal;
      }
      else if (type==roMember)
      {
         m_ResultsOrientation = roMember;
      }
      else
      {
         THROW_LBAMTF(INVALID_RESULTS_ORIENTATION);
      }

      var.Clear();
      hr = pload->get_Property(_bstr_t("ZeroTolerance"),&var);
      if (FAILED(hr))
         return hr;

      m_ZeroTolerance = (double)var;


      var.Clear();
      hr = pload->get_Property(_bstr_t("InfluenceProcessingType"),&var);
      if (FAILED(hr))
         return hr;

      type = (long)var;
      if (type==iptRaw)
      {
         m_InfluenceProcessingType = iptRaw;
      }
      else if (type==iptFlattenNegative)
      {
         m_InfluenceProcessingType = iptFlattenNegative;
      }
      else if (type==iptFlattenPositive)
      {
         m_InfluenceProcessingType = iptFlattenPositive;
      }
      else
      {
         THROW_LBAMTF(INVALID_PROCESSINGTYPE);
      }

      // section force results
      var.Clear();
      hr = pload->get_Property(_bstr_t("IsInfluenceLine"),&var);
      if (FAILED(hr))
         return hr;

      // only load result if it was saved
      VARIANT_BOOL is_result = var;
      if (is_result==VARIANT_TRUE)
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("InfluenceLine"),&var);
         if (FAILED(hr))
            return hr;

         // get variant into more convenient form
         CComPtr<IInfluenceLine> pir;
         hr = _CopyVariantToInterface<IInfluenceLine>::copy(&pir, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         hr = put_InfluenceLine(pir);
         if (FAILED(hr))
            return hr;
      }
      else
      {
         hr = put_InfluenceLine(NULL);
         if (FAILED(hr))
            return hr;
      }
   }
   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CInfluenceResultRequest::Save(IStructuredSave2 * psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("InfluenceResultRequest"), MY_VER);
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("Stage"),_variant_t(m_Stage));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("PoiId"),_variant_t(m_PoiId));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("ForceEffectType"),_variant_t((long)m_ForceEffectType));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("ResponseType"),_variant_t((long)m_ResponseType));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("ResultsOrientation"),_variant_t((long)m_ResultsOrientation));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("ZeroTolerance"),_variant_t((long)m_ZeroTolerance));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("InfluenceProcessingType"),_variant_t((long)m_InfluenceProcessingType));
   if (FAILED(hr))
      return hr;

   // only save result if it exists
   _variant_t is_res;
   is_res.vt = VT_BOOL;
   is_res.boolVal = (m_InfluenceLine==NULL)? VARIANT_FALSE : VARIANT_TRUE;

   hr = psave->put_Property(CComBSTR("IsInfluenceLine"),is_res);
   if (FAILED(hr))
      return hr;

   if (m_InfluenceLine!=NULL)
   {
      hr = psave->put_Property(CComBSTR("InfluenceLine"),_variant_t(m_InfluenceLine));
      if (FAILED(hr))
         return hr;
   }


   hr = psave->EndUnit();
   return hr;
}


STDMETHODIMP CInfluenceResultRequest::Clone(IInfluenceResultRequest **clone)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   CHECK_RETOBJ(clone);

   // create a new one and copy properties
   CComObject<CInfluenceResultRequest>* pnew;
   HRESULT hr = CComObject<CInfluenceResultRequest>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<CInfluenceResultRequest> pscs(pnew); // for exception safety

   pnew->m_Stage = m_Stage;
   pnew->m_PoiId = m_PoiId; 
   pnew->m_ForceEffectType = m_ForceEffectType;
   pnew->m_ResultsOrientation = m_ResultsOrientation;
   pnew->m_ZeroTolerance = m_ZeroTolerance;
   pnew->m_InfluenceProcessingType = m_InfluenceProcessingType;
   pnew->m_InfluenceLine = m_InfluenceLine; // lazy copy
   pnew->m_ResponseType  = m_ResponseType;

   *clone = pnew;
   (*clone)->AddRef();

	return S_OK;
}

