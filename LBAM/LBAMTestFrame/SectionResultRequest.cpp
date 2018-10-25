// SectionResultRequest.cpp : Implementation of CSectionResultRequest
#include "stdafx.h"
#include "LBAMTestFrame.h"
#include "LBAMTestFrame.hh"
#include "SectionResultRequest.h"

#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// CSectionResultRequest

STDMETHODIMP CSectionResultRequest::get_PoiId(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_PoiId;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::put_PoiId(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_PoiId = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::get_Stage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Stage.copy();

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::put_Stage(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Stage = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::get_LoadingType(LoadingType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_LoadingType;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::put_LoadingType(LoadingType newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_LoadingType = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::get_LoadingName(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_LoadingName.copy();

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::put_LoadingName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_LoadingName = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::get_ResultsSummationType(ResultsSummationType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_ResultsSummationType;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::put_ResultsSummationType(ResultsSummationType newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_ResultsSummationType = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::get_ResultsOrientation(ResultsOrientation *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_ResultsOrientation;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::put_ResultsOrientation(ResultsOrientation newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_ResultsOrientation = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::get_SectionForceResult(ISectionResult3D **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (m_SfResult!=NULL)
   {
	   *pVal = m_SfResult;
      (*pVal)->AddRef();
   }
   else
   {
      *pVal=0;
   }

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::put_SectionForceResult(ISectionResult3D *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_SfResult = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::get_DeflectionResult(ISectionResult3D **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (m_DeflResult!=NULL)
   {
	   *pVal = m_DeflResult;
      (*pVal)->AddRef();
   }
   else
   {
      *pVal=0;
   }

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::put_DeflectionResult(ISectionResult3D *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_DeflResult = newVal;

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::get_StressResults(ISectionStressResult **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (m_StressResults!=NULL)
   {
	   *pVal = m_StressResults;
      (*pVal)->AddRef();
   }
   else
   {
      *pVal=0;
   }

	return S_OK;
}

STDMETHODIMP CSectionResultRequest::put_StressResults(ISectionStressResult *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_StressResults = newVal;

	return S_OK;
}


STDMETHODIMP CSectionResultRequest::get_Description(/*[out, retval]*/ BSTR *pVal)
{
   std::stringstream os;

   os << "SectionResultRequest at POI "<<m_PoiId<<" for stage '"<< (char*)m_Stage<<"'";

   if (m_LoadingType==ltLoadGroup)
      os << " for LoadGroup '"<< (char*)m_LoadingName<<"'";
   else if (m_LoadingType==ltLoadCase)
      os << " for LoadCase '"<< (char*)m_LoadingName<<"'";
   else if (m_LoadingType==ltLoadCombination)
      os << " for LoadCombination '"<< (char*)m_LoadingName<<"'";
   else
      ATLASSERT(0);

   if (m_ResultsOrientation==roGlobal)
      os << " oriented Globally ";
   else if (m_ResultsOrientation==roMember)
      os << " oriented by Member ";
   else
      ATLASSERT(0);


   if (m_ResultsSummationType==rsCumulative)
      os << " summed rsCumulative ";
   else if (m_ResultsSummationType==rsIncremental)
      os << " summed rsIncremental ";
   else
      ATLASSERT(0);

   //os <<std::endl;

   std::string tmp(os.str());
   _bstr_t desc(tmp.c_str());
   *pVal = desc.copy();

   return S_OK;
}

// IStructuredStorage2
static const double MY_VER=1.0;

STDMETHODIMP CSectionResultRequest::Load(IStructuredLoad2 * pload)
{
   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("SectionResultRequest"));
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

      hr = pload->get_Property(_bstr_t("LoadingType"),&var);
      if (FAILED(hr))
         return hr;

      long type = (long)var;
      if (type==ltLoadGroup)
      {
         m_LoadingType = ltLoadGroup;
      }
      else if (type== ltLoadCase)
      {
         m_LoadingType = ltLoadCase;
      }
      else if (type== ltLoadCombination)
      {
         m_LoadingType = ltLoadCombination;
      }
      else
      {
         THROW_LBAMTF(INVALID_LOADING_TYPE);
      }

      var.Clear();

      hr = pload->get_Property(_bstr_t("LoadingName"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t name(var);
      m_LoadingName = (const char*)name;

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
      hr = pload->get_Property(_bstr_t("ResultsSummationType"),&var);
      if (FAILED(hr))
         return hr;

      type = (long)var;
      if (type==rsCumulative)
      {
         m_ResultsSummationType = rsCumulative;
      }
      else if (type==rsIncremental)
      {
         m_ResultsSummationType = rsIncremental;
      }
      else
      {
         THROW_LBAMTF(INVALID_RESULTS_SUMMATION);
      }


      // section force results
      var.Clear();
      hr = pload->get_Property(_bstr_t("IsForceResult"),&var);
      if (FAILED(hr))
         return hr;

      // only load result if it was saved
      VARIANT_BOOL is_result = var;
      if (is_result==VARIANT_TRUE)
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("ForceResult"),&var);
         if (FAILED(hr))
            return hr;

         // get variant into more convenient form
         CComPtr<ISectionResult3D> pir;
         hr = _CopyVariantToInterface<ISectionResult3D>::copy(&pir, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         hr = put_SectionForceResult(pir);
         if (FAILED(hr))
            return hr;
      }
      else
      {
         hr = put_SectionForceResult(NULL);
         if (FAILED(hr))
            return hr;
      }

      // section Deflection results
      var.Clear();
      hr = pload->get_Property(_bstr_t("IsDeflectionResult"),&var);
      if (FAILED(hr))
         return hr;

      // only load result if it was saved
      is_result = var;
      if (is_result==VARIANT_TRUE)
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("DeflectionResult"),&var);
         if (FAILED(hr))
            return hr;

         // get variant into more convenient form
         CComPtr<ISectionResult3D> pir;
         hr = _CopyVariantToInterface<ISectionResult3D>::copy(&pir, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         hr = put_DeflectionResult(pir);
         if (FAILED(hr))
            return hr;
      }
      else
      {
         hr = put_DeflectionResult(NULL);
         if (FAILED(hr))
            return hr;
      }

      // section Stress results
      var.Clear();
      hr = pload->get_Property(_bstr_t("IsStressResults"),&var);
      if (FAILED(hr))
         return hr;

      // only load result if it was saved
      is_result = var;
      if (is_result==VARIANT_TRUE)
      {
         var.Clear();
         hr = pload->get_Property(_bstr_t("StressResults"),&var);
         if (FAILED(hr))
            return hr;

         // get variant into more convenient form
         CComPtr<ISectionStressResult> pir;
         hr = _CopyVariantToInterface<ISectionStressResult>::copy(&pir, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         hr = put_StressResults(pir);
         if (FAILED(hr))
            return hr;
      }
      else
      {
         hr = put_StressResults(NULL);
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

STDMETHODIMP CSectionResultRequest::Save(IStructuredSave2 * psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("SectionResultRequest"), MY_VER);
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("Stage"),_variant_t(m_Stage));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("PoiId"),_variant_t(m_PoiId));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("LoadingType"),_variant_t((long)m_LoadingType));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("LoadingName"),_variant_t(m_LoadingName));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("ResultsOrientation"),_variant_t((long)m_ResultsOrientation));
   if (FAILED(hr))
      return hr;

   hr = psave->put_Property(CComBSTR("ResultsSummationType"),_variant_t((long)m_ResultsSummationType));
   if (FAILED(hr))
      return hr;

   // only save result if it exists
   _variant_t is_res;
   is_res.vt = VT_BOOL;
   is_res.boolVal = (m_SfResult==NULL)? VARIANT_FALSE : VARIANT_TRUE;

   hr = psave->put_Property(CComBSTR("IsForceResult"),is_res);
   if (FAILED(hr))
      return hr;

   if (m_SfResult!=NULL)
   {
      hr = psave->put_Property(CComBSTR("ForceResult"),_variant_t(m_SfResult));
      if (FAILED(hr))
         return hr;
   }

   is_res.boolVal = (m_DeflResult==NULL)? VARIANT_FALSE : VARIANT_TRUE;

   hr = psave->put_Property(CComBSTR("IsDeflectionResult"),is_res);
   if (FAILED(hr))
      return hr;

   if (m_DeflResult!=NULL)
   {
      hr = psave->put_Property(CComBSTR("DeflectionResult"),_variant_t(m_DeflResult));
      if (FAILED(hr))
         return hr;
   }

   is_res.boolVal = (m_StressResults==NULL)? VARIANT_FALSE : VARIANT_TRUE;

   hr = psave->put_Property(CComBSTR("IsStressResults"),is_res);
   if (FAILED(hr))
      return hr;

   if (m_StressResults!=NULL)
   {
      hr = psave->put_Property(CComBSTR("StressResults"),_variant_t(m_StressResults));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   return hr;
}


STDMETHODIMP CSectionResultRequest::Clone(ISectionResultRequest **clone)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   CHECK_RETOBJ(clone);

   // create a new one and copy properties
   CComObject<CSectionResultRequest>* pnew;
   HRESULT hr = CComObject<CSectionResultRequest>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<CSectionResultRequest> pscs(pnew); // for exception safety

   pnew->m_Stage = m_Stage;
   pnew->m_PoiId = m_PoiId; 
   pnew->m_LoadingType = m_LoadingType;
   pnew->m_LoadingName = m_LoadingName;
   pnew->m_ResultsOrientation = m_ResultsOrientation;
   pnew->m_ResultsSummationType = m_ResultsSummationType;
   pnew->m_SfResult = m_SfResult; // lazy copy
   pnew->m_DeflResult = m_DeflResult; // lazy copy
   pnew->m_StressResults = m_StressResults; // lazy copy

   *clone = pnew;
   (*clone)->AddRef();

	return S_OK;
}


