// LBAMTester.cpp : Implementation of CLBAMTester
#include "stdafx.h"
#include "LBAMTestFrame.h"
#include "LBAMTestFrame.hh"
#include "LBAMTester.h"

#include "SectionResultRequests.h"
#include "InfluenceResultRequests.h"
#include "LBAMUtils.h"
#include <MathEx.h>
#include <sstream>
#include <iomanip>

#define THROW_ON_FAIL(hr) if(FAILED(hr)) throw hr;

// free functions
void GetRequestDescription(IUnknown* unk, BSTR* description);

// compare two doubles
// pActualPercentDiff is only filled for return type fcsFailPercentDiff
enum DoubleCompareStat {fcsPass, fcsFailPercentDiff, fcsFailTolerance};
DoubleCompareStat CompareDoubles(double bench, double testVal, double percentDiff, double tolerance, double* pActualPercentDiff)
{
   ATLASSERT(tolerance>=0.0);
   ATLASSERT(percentDiff>=0.0);

   if (fabs(bench)<=tolerance)
   {
      if ( fabs(testVal-bench)>tolerance)
         return fcsFailTolerance;
   }
   else
   {
      double pd = (testVal-bench)/bench;
      if (fabs(pd)>percentDiff)
      {
         *pActualPercentDiff = pd;
         return fcsFailPercentDiff;
      }
   }

   return fcsPass;
}

// write comparison of two doubles
inline void WriteDoubleCompare(std::stringstream& os, const char* field, double bench, double value, DoubleCompareStat stat, double pd)
{
   os <<std::setw(12) << field
      <<std::setw(12)<< bench
      <<std::setw(12)<< value;

   if (stat==fcsPass)
   {
      os <<std::setw(12)<< "Passed"<<std::endl;
   }    
   else if (stat==fcsFailPercentDiff)
   {
      os <<std::setw(12) <<"Failed % Diff = "
         <<std::setw(12) << pd*100.0 << std::endl;
   }
   else if (stat==fcsFailTolerance)
   {
      os <<"Failed Tolerance" << std::endl;
   }
   else
      ATLASSERT(0);
}

// write comparison of two influence values at the same location
inline void WriteCompareInfluenceLocations(std::stringstream& os, double location, InfluenceLocationType locType, double bench, double result, double tolerance, double percentDiff)
{
   os <<std::setw(12) << location;

   if (locType==iflSingle)
      os<<std::setw(7)<< " Single ";
   else if (locType==iflDualRight)
      os<<std::setw(7)<< " Right ";
   else
      os<<std::setw(7)<< " Left ";

   os <<std::setw(12)<< bench;
   os <<std::setw(12)<< result;

   double pda;
   DoubleCompareStat stat = CompareDoubles(bench, result, percentDiff, tolerance, &pda);

   if (stat==fcsPass)
   {
      os <<std::setw(12)<< "Passed"<<std::endl;
   }    
   else if (stat==fcsFailPercentDiff)
   {
      os <<std::setw(12) <<"Failed % Diff = "
         <<std::setw(12) << pda*100.0 << std::endl;
   }
   else if (stat==fcsFailTolerance)
   {
      os <<"Failed Tolerance" << std::endl;
   }
   else
      ATLASSERT(0);
}

inline void WriteInfluenceNoMatch(std::stringstream& os, double location, InfluenceLocationType locType, double value, bool benchOnly)
{
   os <<std::setw(12) << location;

   if (locType==iflSingle)
      os<<std::setw(7)<< " Single ";
   else if (locType==iflDualRight)
      os<<std::setw(7)<< " Right ";
   else
      os<<std::setw(7)<< " Left ";

   if (benchOnly)
   {
      os <<std::setw(12)<< value;
      os <<std::setw(12)<< "----";
   }
   else
   {
      os <<std::setw(12)<< "----";
      os <<std::setw(12)<< value;
   }

   os <<"  --- Failed - location mismatch"<<std::endl;
}

/////////////////////////////////////////////////////////////////////////////
// CLBAMTester

STDMETHODIMP CLBAMTester::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILBAMTester
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CLBAMTester::CLBAMTester():
m_AnalysisType(atForce),
m_ForceMinPercentDiff(0.01),
m_ForceMinTolerance(1.0e-10),
m_DoComputeForces(VARIANT_TRUE),
m_DeflectionMinPercentDiff(0.01),
m_DeflectionMinTolerance(1.0e-10),
m_DoComputeDeflections(VARIANT_TRUE),
m_StressMinPercentDiff(0.01),
m_StressMinTolerance(1.0e-10),
m_DoComputeStresses(VARIANT_TRUE),
m_Dirty(true)
{
   HRESULT hr;
   CComObject<CSectionResultRequests>* requests;
   hr = CComObject<CSectionResultRequests>::CreateInstance(&requests);
   ATLASSERT(SUCCEEDED(hr));

   m_SectionResultRequests = requests;

   // influence
   CComObject<CInfluenceResultRequests>* irequests;
   hr = CComObject<CInfluenceResultRequests>::CreateInstance(&irequests);
   ATLASSERT(SUCCEEDED(hr));

   m_InfluenceResultRequests = irequests;

}

void CLBAMTester::AssertValid()
{
   if (m_SectionResultRequests==NULL)
   {
      ATLASSERT(0);
      THROW_HR( E_FAIL);
   }

   if (m_InfluenceResultRequests==NULL)
   {
      ATLASSERT(0);
      THROW_HR( E_FAIL);
   }

   if (m_Model==NULL)
   {
      THROW_LBAMTF(NO_MODEL);
   }
}

STDMETHODIMP CLBAMTester::get_ForceMinTolerance(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_ForceMinTolerance;

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_ForceMinTolerance(double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   if (newVal<0.0)
      return E_INVALIDARG;

	m_ForceMinTolerance = newVal;

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_ForceMinPercentDiff(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_ForceMinPercentDiff;

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_ForceMinPercentDiff(double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (newVal<0.0)
      return E_INVALIDARG;

	m_ForceMinPercentDiff = newVal;

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_DeflectionMinTolerance(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_DeflectionMinTolerance;

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_DeflectionMinTolerance(double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   if (newVal<0.0)
      return E_INVALIDARG;

	m_DeflectionMinTolerance = newVal;

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_DeflectionMinPercentDiff(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_DeflectionMinPercentDiff;

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_DeflectionMinPercentDiff(double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (newVal<0.0)
      return E_INVALIDARG;

	m_DeflectionMinPercentDiff = newVal;

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_StressMinTolerance(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_StressMinTolerance;

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_StressMinTolerance(double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   if (newVal<0.0)
      return E_INVALIDARG;

	m_StressMinTolerance = newVal;

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_StressMinPercentDiff(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_StressMinPercentDiff;

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_StressMinPercentDiff(double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (newVal<0.0)
      return E_INVALIDARG;

	m_StressMinPercentDiff = newVal;

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_Model(ILBAMModel **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (m_Model)
   {
      *pVal = m_Model;
      (*pVal)->AddRef();
   }
   else
      *pVal = NULL;

	return S_OK;
}

STDMETHODIMP CLBAMTester::putref_Model(ILBAMModel *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Model = newVal;
   m_Dirty = true;

	return S_OK;
}

STDMETHODIMP CLBAMTester::AttachToModelFile(BSTR FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   // load model in file and assign it to our model pointer
   HRESULT hr;
   CComPtr<IStructuredLoad2> psl;
   hr = psl.CoCreateInstance( CLSID_StructuredLoad2 );
   if (FAILED(hr))
      return hr;

   hr = psl->Open( FileName );
   if (FAILED(hr))
      return hr;

   CComPtr<ILBAMModel> pModel;
   hr = pModel.CoCreateInstance( CLSID_LBAMModel );
   if (FAILED(hr))
      return hr;

   IStructuredStorage2* piss=NULL;
   hr = pModel.QueryInterface(&piss);
   if (FAILED(hr))
      return hr;

   // Load 
   hr = piss->Load(psl);
   if (FAILED(hr))
      return hr;

   piss->Release();

   hr = psl->Close();
   if (FAILED(hr))
      return hr;

   hr = putref_Model(pModel);
   if (FAILED(hr))
      return hr;

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_AnalysisType(AnalysisType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_AnalysisType;

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_AnalysisType(AnalysisType newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_AnalysisType = newVal;
   m_Dirty = true;

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_SectionResultRequests(ISectionResultRequests **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_SectionResultRequests;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_InfluenceResultRequests(IInfluenceResultRequests* *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_InfluenceResultRequests;
   (*pVal)->AddRef();

	return S_OK;
}

// IStructuredStorage2
static const double MY_VER=1.0;

STDMETHODIMP CLBAMTester::Load(IStructuredLoad2 * pload)
{
   try
   {

      HRESULT hr;
      VARIANT_BOOL eb;

      hr = pload->BeginUnit(CComBSTR("LBAMTester"));
      if (FAILED(hr))
         return hr;

      double ver;
      hr = pload->get_Version(&ver);
      if (FAILED(hr))
         return hr;

      if (ver!=MY_VER)
         return STRLOAD_E_BADVERSION;

      {        

         hr = pload->BeginUnit(CComBSTR("Configuration"));
         if (FAILED(hr))
            return hr;

         _variant_t var;
         hr = pload->get_Property(CComBSTR("Description"),&var);
         if (FAILED(hr))
            return hr;

         m_Description = var.bstrVal;


         var.Clear();
         hr = pload->get_Property(_bstr_t("AnalysisType"),&var);
         if (FAILED(hr))
            return hr;

         _bstr_t type(var);
         if (type== _bstr_t("Force"))
         {
            m_AnalysisType = atForce;
         }
         else if (type==_bstr_t("Deflection") )
         {
            m_AnalysisType = atDeflection;
         }
         else
         {
            ATLASSERT(0);
         }

         var.Clear();
         hr = pload->get_Property(_bstr_t("ForceMinPercentDiff"),&var);
         if (FAILED(hr))
            return hr;

         m_ForceMinPercentDiff = (double)var;
         var.Clear();

         hr = pload->get_Property(_bstr_t("ForceMinTolerance"),&var);
         if (FAILED(hr))
            return hr;

         m_ForceMinTolerance = (double)var;
         var.Clear();

         hr = pload->get_Property(_bstr_t("DoComputeForces"),&var);
         if (FAILED(hr))
            return hr;

         ATLASSERT(var.vt==VT_BOOL);
         m_DoComputeForces = var.boolVal;
         var.Clear();

         hr = pload->get_Property(_bstr_t("DeflectionMinPercentDiff"),&var);
         if (FAILED(hr))
            return hr;

         m_DeflectionMinPercentDiff = (double)var;
         var.Clear();

         hr = pload->get_Property(_bstr_t("DeflectionMinTolerance"),&var);
         if (FAILED(hr))
            return hr;

         m_DeflectionMinTolerance = (double)var;
         var.Clear();

         hr = pload->get_Property(_bstr_t("DoComputeDeflections"),&var);
         if (FAILED(hr))
            return hr;

         ATLASSERT(var.vt==VT_BOOL);
         m_DoComputeDeflections = var.boolVal;
         var.Clear();

         hr = pload->get_Property(_bstr_t("StressMinPercentDiff"),&var);
         if (FAILED(hr))
            return hr;

         m_StressMinPercentDiff = (double)var;
         var.Clear();

         hr = pload->get_Property(_bstr_t("StressMinTolerance"),&var);
         if (FAILED(hr))
            return hr;

         m_StressMinTolerance = (double)var;
         var.Clear();

         hr = pload->get_Property(_bstr_t("DoComputeStresses"),&var);
         if (FAILED(hr))
            return hr;

         ATLASSERT(var.vt==VT_BOOL);
         m_DoComputeStresses = var.boolVal;
         var.Clear();

         // end of configuration block
         hr = pload->EndUnit(&eb);
         if (FAILED(hr))
            return hr;

         if (eb!=VARIANT_TRUE)
            return STRLOAD_E_INVALIDFORMAT;

         // begin model block
         hr = pload->BeginUnit(CComBSTR("Model"));
         if (FAILED(hr))
            return hr;

         // model
         hr = pload->get_Property(_bstr_t("Model"),&var);
         if (FAILED(hr))
            return hr;

         CComPtr<ILBAMModel> pimdl;
         hr = _CopyVariantToInterface<ILBAMModel>::copy(&pimdl, &var);
         if (FAILED(hr))
            return STRLOAD_E_INVALIDFORMAT;

         hr = putref_Model(pimdl);
         if (FAILED(hr))
            return hr;

         // end of model block
         hr = pload->EndUnit(&eb);
         if (FAILED(hr))
            return hr;

         if (eb!=VARIANT_TRUE)
            return STRLOAD_E_INVALIDFORMAT;

         // begin results block
         hr = pload->BeginUnit(CComBSTR("Results"));
         if (FAILED(hr))
            return hr;

            // section results requests
            CComPtr<ISectionResultRequests> pSfr;
            hr = pSfr.CoCreateInstance( CLSID_SectionResultRequests );
            if (FAILED(hr))
               return hr;

            IStructuredStorage2* pissfr=NULL;
            hr = pSfr.QueryInterface(&pissfr);
            if (FAILED(hr))
               return hr;

            hr = pissfr->Load(pload);
            if (FAILED(hr))
               return hr;

            pissfr->Release();
            m_SectionResultRequests = pSfr;

            // Influence results requests
            CComPtr<IInfluenceResultRequests> pIfr;
            hr = pIfr.CoCreateInstance( CLSID_InfluenceResultRequests );
            if (FAILED(hr))
               return hr;

            IStructuredStorage2* piss2=NULL;
            hr = pIfr.QueryInterface(&piss2);
            if (FAILED(hr))
               return hr;

            hr = piss2->Load(pload);
            if (FAILED(hr))
               return hr;

            piss2->Release();
            m_InfluenceResultRequests = pIfr;

         // end of results block
         hr = pload->EndUnit(&eb);
         if (FAILED(hr))
            return hr;

         if (eb!=VARIANT_TRUE)
            return STRLOAD_E_INVALIDFORMAT;

         AssertValid();
      }

      hr = pload->EndUnit(&eb);
      if (FAILED(hr))
         return hr;

      if (eb!=VARIANT_TRUE)
         return STRLOAD_E_INVALIDFORMAT;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMTester);
   }

   return S_OK;
}

STDMETHODIMP CLBAMTester::Save(IStructuredSave2 * psave)
{
   try
   {
      AssertValid();

      HRESULT hr;
      hr = psave->BeginUnit(CComBSTR("LBAMTester"), MY_VER);
      if (FAILED(hr))
         return hr;

      // first write configuration block
      hr = psave->BeginUnit(CComBSTR("Configuration"), MY_VER);
      if (FAILED(hr))
         return hr;

         hr = psave->put_Property(CComBSTR("Description"),_variant_t(m_Description));
         if (FAILED(hr))
            return hr;

         if (m_AnalysisType==atForce)
         {
            hr = psave->put_Property(CComBSTR("AnalysisType"),_variant_t("Force"));
            if (FAILED(hr))
               return hr;
         }
         else
         {
            hr = psave->put_Property(CComBSTR("AnalysisType"),_variant_t("Deflection"));
            if (FAILED(hr))
               return hr;
         }

         hr = psave->put_Property(CComBSTR("ForceMinPercentDiff"),_variant_t(m_ForceMinPercentDiff));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("ForceMinTolerance"),_variant_t(m_ForceMinTolerance));
         if (FAILED(hr))
            return hr;

         VARIANT varbool;
         varbool.vt = VT_BOOL;
         varbool.boolVal = m_DoComputeForces;
          hr = psave->put_Property(CComBSTR("DoComputeForces"),varbool);
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("DeflectionMinPercentDiff"),_variant_t(m_DeflectionMinPercentDiff));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("DeflectionMinTolerance"),_variant_t(m_DeflectionMinTolerance));
         if (FAILED(hr))
            return hr;

         varbool.boolVal = m_DoComputeDeflections;
         hr = psave->put_Property(CComBSTR("DoComputeDeflections"),varbool);
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("StressMinPercentDiff"),_variant_t(m_StressMinPercentDiff));
         if (FAILED(hr))
            return hr;

         hr = psave->put_Property(CComBSTR("StressMinTolerance"),_variant_t(m_StressMinTolerance));
         if (FAILED(hr))
            return hr;

         varbool.boolVal = m_DoComputeStresses;
         hr = psave->put_Property(CComBSTR("DoComputeStresses"),varbool);
         if (FAILED(hr))
            return hr;

      // end of configuration block
      hr = psave->EndUnit();
      if (FAILED(hr))
         return hr;

      // model block
      hr = psave->BeginUnit(CComBSTR("Model"), MY_VER);
      if (FAILED(hr))
         return hr;

         // model
         hr = psave->put_Property(CComBSTR("Model"),_variant_t(m_Model));
         if (FAILED(hr))
            return hr;

      hr = psave->EndUnit();
      if (FAILED(hr))
         return hr;


      // Results block
      hr = psave->BeginUnit(CComBSTR("Results"), MY_VER);
      if (FAILED(hr))
         return hr;

         // section results requests
         IStructuredStorage2* pisfr=NULL;
         hr = m_SectionResultRequests.QueryInterface(&pisfr);
         if (FAILED(hr))
            return hr;

         hr = pisfr->Save(psave);
         if (FAILED(hr))
            return hr;

         pisfr->Release();

         // influence requests
         pisfr=NULL;
         hr = m_InfluenceResultRequests.QueryInterface(&pisfr);
         if (FAILED(hr))
            return hr;

         hr = pisfr->Save(psave);
         if (FAILED(hr))
            return hr;

         pisfr->Release();

      // end of results block
      hr = psave->EndUnit();
      if (FAILED(hr))
         return hr;

      // end of main block
      hr = psave->EndUnit();
      if (FAILED(hr))
         return hr;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMTester);
   }

   return S_OK;
}


STDMETHODIMP CLBAMTester::ValidateResults(ITestLogger *Logger)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   std::ostringstream os;
   os << "Starting Results Validation"<<std::endl;
      if (m_AnalysisType==atForce)
      {
         os << "Model Type is for Force Calculations"<<std::endl;
      }
      else
      {
         os << "Model Type is for Deflection Calculations"<<std::endl;
      }

      os<< "Min Force percent diff      = "<< m_ForceMinPercentDiff<<std::endl
      << "Min Force tolerance         = "<< m_ForceMinTolerance<<std::endl
      << "Min Deflection percent diff = "<< m_DeflectionMinPercentDiff<<std::endl
      << "Min Deflection tolerance    = "<< m_DeflectionMinTolerance<<std::endl
      << "Min Stress percent diff     = "<< m_StressMinPercentDiff<<std::endl
      << "Min Stress tolerance        = "<< m_StressMinTolerance<<std::endl;

   HRESULT hr;
   hr = Logger->AddDescriptionEntry(CComBSTR(os.str().c_str()));
   THROW_ON_FAIL(hr);

   try
   {
      UpdateEngines();

      AssertValid();

      // look at section results
      ValidateSectionResults(Logger);

      // look at section results
      ValidateInfluenceResults(Logger);

   }
   catch(...)
   {
      ATLASSERT(0);
      Logger->AddDescriptionEntry(CComBSTR("Exception caught - Test terminated early"));
      return DealWithExceptions(this, IID_ILBAMTester);
   }

   hr = Logger->AddDescriptionEntry(CComBSTR("Results Validation Finished Normally"));
   THROW_ON_FAIL(hr);

	return S_OK;
}

void CLBAMTester::ValidateSectionResults(ITestLogger *pLogger)
{
   HRESULT hr;
   hr = pLogger->AddDescriptionEntry(CComBSTR("Validating Section Forces"));
   THROW_ON_FAIL(hr);

   long cnt;
   hr = m_SectionResultRequests->get_Count(&cnt);
   THROW_ON_FAIL(hr);

   for (long i=0; i<cnt; i++)
   {
      CComPtr<ISectionResultRequest> request;
      hr = m_SectionResultRequests->get_Item(i, &request);
      THROW_ON_FAIL(hr);

      // section forces
      if (m_DoComputeForces)
         ValidateSectionForceResult(request, pLogger);

      // deflections
      if (m_DoComputeDeflections)
         ValidateDeflectionResult(request, pLogger);

      // Stresses
      if (m_DoComputeStresses)
         ValidateStressResults(request, pLogger);
   }
}

void CLBAMTester::ValidateSectionForceResult(ISectionResultRequest* pRequest, ITestLogger* pLogger)
{
   HRESULT hr;
   // get benchmark result
   CComPtr<ISectionResult3D> benchmark;
   hr = pRequest->get_SectionForceResult(&benchmark);
   THROW_ON_FAIL(hr);

   if (benchmark==NULL)
   {
      CComBSTR descr;
      GetRequestDescription(pRequest, &descr);
      CComBSTR msg = CreateErrorMsg1S(IDS_E_NO_BENCHMARK, descr);
      pLogger->AddDescriptionEntry(msg);
      THROW_LBAMTF_MSG(NO_BENCHMARK, msg);
   }

   // get result for current engine
   CComPtr<ISectionResult3D> the_result;
   ComputeSectionForceResult(pRequest, &the_result);

   // have results - now perform comparison
   CompareSectionForceResults(benchmark, the_result, pRequest, pLogger);
}

void CLBAMTester::ComputeSectionForceResult(ISectionResultRequest* request, ISectionResult3D* *pResult)
{
   HRESULT hr;
   CComBSTR stage;
   hr = request->get_Stage(&stage);
   THROW_ON_FAIL(hr);

   CComBSTR load_name;
   hr = request->get_LoadingName(&load_name);
   THROW_ON_FAIL(hr);

   ResultsOrientation orientation;
   hr = request->get_ResultsOrientation(&orientation);
   THROW_ON_FAIL(hr);

   ResultsSummationType summation;
   hr = request->get_ResultsSummationType(&summation);
   THROW_ON_FAIL(hr);

   long poi_id;
   hr = request->get_PoiId(&poi_id);
   THROW_ON_FAIL(hr);

   CComPtr<ILngArray> sa_pois;
   sa_pois.CoCreateInstance(CLSID_LngArray);
   sa_pois->Add(poi_id);

   LoadingType l_t;
   hr = request->get_LoadingType(&l_t);
   THROW_ON_FAIL(hr);

   CComPtr<ISectionResult3Ds> the_results;

   // get the result
   switch (l_t)
   {
   case ltLoadGroup:
      {
         if (m_LoadGroupResponse==NULL)
            THROW_LBAMTF(NO_LOADGROUP_RESPONSE);

         hr = m_LoadGroupResponse->ComputeForces(load_name, sa_pois, stage, 
                                                 orientation, summation, 
                                                 &the_results);
         THROW_ON_FAIL(hr);
      }
      break;
   case ltLoadCase:
   case ltLoadCombination:
   default:
      ATLASSERT(0);
   }

   // result is in an array - get it out and return it
   CComPtr<ISectionResult3D> the_result;
   hr = the_results->get_Item(0,&the_result);
   THROW_ON_FAIL(hr);

   *pResult = the_result.Detach();
}

void CLBAMTester::ValidateStressResults(ISectionResultRequest* pRequest, ITestLogger* pLogger)
{
   HRESULT hr;
   // get benchmark result
   CComPtr<ISectionStressResult> benchmark;
   hr = pRequest->get_StressResults(&benchmark);
   THROW_ON_FAIL(hr);

   if (benchmark==NULL)
   {
      return ;
      CComBSTR descr;
      GetRequestDescription(pRequest, &descr);
      CComBSTR msg = CreateErrorMsg1S(IDS_E_NO_BENCHMARK, descr);
      pLogger->AddDescriptionEntry(msg);
      THROW_LBAMTF_MSG(NO_BENCHMARK, msg);
   }

   // get result for current engine
   CComPtr<ISectionStressResult> the_result;
   ComputeStressResults(pRequest, &the_result);

   // have results - now perform comparison
   CompareStressResults(benchmark, the_result, pRequest, pLogger);
}



void CLBAMTester::ComputeStressResults(ISectionResultRequest* request, ISectionStressResult* *pResult)
{
   HRESULT hr;
   CComBSTR stage;
   hr = request->get_Stage(&stage);
   THROW_ON_FAIL(hr);

   CComBSTR load_name;
   hr = request->get_LoadingName(&load_name);
   THROW_ON_FAIL(hr);

   ResultsSummationType summation;
   hr = request->get_ResultsSummationType(&summation);
   THROW_ON_FAIL(hr);

   long poi_id;
   hr = request->get_PoiId(&poi_id);
   THROW_ON_FAIL(hr);

   LoadingType l_t;
   hr = request->get_LoadingType(&l_t);
   THROW_ON_FAIL(hr);

   // create a single member array to make poi request
   CComPtr<ILngArray> sa_pois;
   sa_pois.CoCreateInstance(CLSID_LngArray);
   sa_pois->Add(poi_id);

   CComPtr<ISectionStressResult> the_result;

   // get the result
   switch (l_t)
   {
   case ltLoadGroup:
      {
         if (m_LoadGroupResponse==NULL)
            THROW_LBAMTF(NO_LOADGROUP_RESPONSE);

         CComPtr<ISectionStressResults> lcl_results;
         hr = m_LoadGroupResponse->ComputeStresses(load_name, sa_pois, stage, 
                                                   summation,
                                                   &lcl_results);
         THROW_ON_FAIL(hr);

         hr = lcl_results->get_Item(0, &the_result);
         THROW_ON_FAIL(hr);
      }
      break;
   case ltLoadCase:
   case ltLoadCombination:
   default:
      ATLASSERT(0);
   }

   *pResult = the_result.Detach();
}

void CLBAMTester::CompareStressResults(ISectionStressResult* benchmark, ISectionStressResult* theResult, ISectionResultRequest* request, ITestLogger* Logger)
{
   HRESULT hr;

   // first check to see if new results and benchmark have the same number of stress points
   long num_bstps, num_sps;
   hr = benchmark->get_LeftCount(&num_bstps);
   THROW_ON_FAIL(hr);
   hr = theResult->get_LeftCount(&num_sps);
   THROW_ON_FAIL(hr);

   if (num_bstps != num_sps)
   {
      CComBSTR descr;
      GetRequestDescription(request, &descr);

      std::stringstream os;
      os << "The number of stress points between the benchmark and new result were different . Benchmark was";
      os << num_bstps << " and new results was "<< num_sps<<std::endl;

      CComBSTR descr2(os.str().c_str());
      descr += descr2;

      hr = Logger->AddTestEntry(trFailed, descr);
      THROW_ON_FAIL(hr);
   }
   else
   {
      // have the same number of stress points. Now need to check numbers.
      // get force results
      double sl_bench;
      double sl_result;
      double sl_pdactual; // % differences

      std::stringstream os;

      bool passed = true;
      for (long i=0; i<num_sps; i++)
      {
         hr = benchmark->GetLeftResult(i, &sl_bench);
         THROW_ON_FAIL(hr);

         hr = theResult->GetLeftResult(i, &sl_result);
         THROW_ON_FAIL(hr);

         DoubleCompareStat sl_stat;

         sl_stat = CompareDoubles(sl_bench, sl_result, m_StressMinPercentDiff,  m_StressMinTolerance, &sl_pdactual);
         if (  sl_stat != fcsPass)
         {
            passed = false;
            os << std::endl<< "Stress Result at stress point "<< i << std::endl;
            os << std::setiosflags( std::ios::left );
            os << std::setw(12)<<"Value"<<std::setw(12)<<"BenchMark"<<std::setw(12)<<"Value"<<std::setw(12)<<"Reason"<<std::setw(12)<<"% Diff"<<std::endl; 
            WriteDoubleCompare(os, "SL ",  sl_bench, sl_result, sl_stat, sl_pdactual);
         }
      }

      // report statistics
      CComBSTR descr;
      GetRequestDescription(request, &descr);

      if (!passed)
      {
         CComBSTR descr2(os.str().c_str());
         descr += descr2;
         hr = Logger->AddTestEntry(trFailed, descr);
         THROW_ON_FAIL(hr);
      }
      else
      {
         hr = Logger->AddTestEntry(trPassed, descr);
         THROW_ON_FAIL(hr);
      }
   }
}

void CLBAMTester::ValidateDeflectionResult(ISectionResultRequest* pRequest, ITestLogger* pLogger)
{
   HRESULT hr;
   // get benchmark result
   CComPtr<ISectionResult3D> benchmark;
   hr = pRequest->get_DeflectionResult(&benchmark);
   THROW_ON_FAIL(hr);

   if (benchmark==NULL)
   {
      CComBSTR descr;
      GetRequestDescription(pRequest, &descr);
      CComBSTR msg = CreateErrorMsg1S(IDS_E_NO_BENCHMARK, descr);
      pLogger->AddDescriptionEntry(msg);
      THROW_LBAMTF_MSG(NO_BENCHMARK, msg);
   }

   // get result for current engine
   CComPtr<ISectionResult3D> the_result;
   ComputeDeflectionResult(pRequest, &the_result);

   // have results - now perform comparison
   CompareDeflectionResults(benchmark, the_result, pRequest, pLogger);
}

void CLBAMTester::ComputeDeflectionResult(ISectionResultRequest* request, ISectionResult3D* *pResult)
{
   HRESULT hr;
   CComBSTR stage;
   hr = request->get_Stage(&stage);
   THROW_ON_FAIL(hr);

   CComBSTR load_name;
   hr = request->get_LoadingName(&load_name);
   THROW_ON_FAIL(hr);

   ResultsSummationType summation;
   hr = request->get_ResultsSummationType(&summation);
   THROW_ON_FAIL(hr);

   long poi_id;
   hr = request->get_PoiId(&poi_id);
   THROW_ON_FAIL(hr);

   CComPtr<ILngArray> sa_pois;
   sa_pois.CoCreateInstance(CLSID_LngArray);
   sa_pois->Add(poi_id);

   LoadingType l_t;
   hr = request->get_LoadingType(&l_t);
   THROW_ON_FAIL(hr);

   CComPtr<ISectionResult3Ds> the_results;

   // get the result
   switch (l_t)
   {
   case ltLoadGroup:
      {
         if (m_LoadGroupResponse==NULL)
            THROW_LBAMTF(NO_LOADGROUP_RESPONSE);

         hr = m_LoadGroupResponse->ComputeDeflections(load_name, sa_pois, stage, 
                                                       summation, &the_results);
         THROW_ON_FAIL(hr);
      }
      break;
   case ltLoadCase:
   case ltLoadCombination:
   default:
      ATLASSERT(0);
   }

   // result is in an array - get it out and return it
   CComPtr<ISectionResult3D> the_result;
   hr = the_results->get_Item(0,&the_result);
   THROW_ON_FAIL(hr);

   *pResult = the_result.Detach();
}

void CLBAMTester::CompareDeflectionResults(ISectionResult3D* benchmark, ISectionResult3D* theResult, ISectionResultRequest* request, ITestLogger* Logger)
{
   HRESULT hr;

   // get force results
   double dx_lbench,    dy_lbench,    rz_lbench;
   double dx_rbench,    dy_rbench,    rz_rbench;
   double dx_lresult,   dy_lresult,   rz_lresult;
   double dx_rresult,   dy_rresult,   rz_rresult;
   double dx_lpdactual, dy_lpdactual, rz_lpdactual; // % differences
   double dx_rpdactual, dy_rpdactual, rz_rpdactual; // % differences

   hr = benchmark->GetResult(&dx_lbench, &dy_lbench, &rz_lbench,&dx_rbench, &dy_rbench, &rz_rbench);
   THROW_ON_FAIL(hr);

   hr = theResult->GetResult(&dx_lresult, &dy_lresult, &rz_lresult,&dx_rresult, &dy_rresult, &rz_rresult);
   THROW_ON_FAIL(hr);

   // compare force results
   DoubleCompareStat dx_lstat, dy_lstat, rz_lstat, dx_rstat, dy_rstat, rz_rstat;

   dx_lstat = CompareDoubles(dx_lbench, dx_lresult, m_DeflectionMinPercentDiff,  m_DeflectionMinTolerance, &dx_lpdactual);
   dy_lstat = CompareDoubles(dy_lbench, dy_lresult, m_DeflectionMinPercentDiff,  m_DeflectionMinTolerance, &dy_lpdactual);
   rz_lstat = CompareDoubles(rz_lbench, rz_lresult, m_DeflectionMinPercentDiff,  m_DeflectionMinTolerance, &rz_lpdactual);
   dx_rstat = CompareDoubles(dx_rbench, dx_rresult, m_DeflectionMinPercentDiff,  m_DeflectionMinTolerance, &dx_rpdactual);
   dy_rstat = CompareDoubles(dy_rbench, dy_rresult, m_DeflectionMinPercentDiff,  m_DeflectionMinTolerance, &dy_rpdactual);
   rz_rstat = CompareDoubles(rz_rbench, rz_rresult, m_DeflectionMinPercentDiff,  m_DeflectionMinTolerance, &rz_rpdactual);

   // report statistics
   CComBSTR descr;
   GetRequestDescription(request, &descr);

   if (  dx_lstat != fcsPass || dy_lstat != fcsPass || rz_lstat != fcsPass ||  
         dx_rstat != fcsPass || dy_rstat != fcsPass || rz_rstat != fcsPass)
   {
      std::stringstream os;
      os << std::endl<< "Deflection Result"<<std::endl;
      os << std::setiosflags( std::ios::left );
      os << std::setw(12)<<"Value"<<std::setw(12)<<"BenchMark"<<std::setw(12)<<"Value"<<std::setw(12)<<"Reason"<<std::setw(12)<<"% Diff"<<std::endl; 
      WriteDoubleCompare(os, "Left  Dx ",  dx_lbench, dx_lresult, dx_lstat, dx_lpdactual);
      WriteDoubleCompare(os, "Left  Dy ",  dy_lbench, dy_lresult, dy_lstat, dy_lpdactual);
      WriteDoubleCompare(os, "Left  Rz ",  rz_lbench, rz_lresult, rz_lstat, rz_lpdactual);
      WriteDoubleCompare(os, "Right Dx ",  dx_rbench, dx_rresult, dx_rstat, dx_rpdactual);
      WriteDoubleCompare(os, "Right Dy ",  dy_rbench, dy_rresult, dy_rstat, dy_rpdactual);
      WriteDoubleCompare(os, "Right Rz ",  rz_rbench, rz_rresult, rz_rstat, rz_rpdactual);

      CComBSTR descr2(os.str().c_str());
      descr += descr2;

      hr = Logger->AddTestEntry(trFailed, descr);
      THROW_ON_FAIL(hr);
   }
   else
   {
      hr = Logger->AddTestEntry(trPassed, descr);
      THROW_ON_FAIL(hr);
   }
}

STDMETHODIMP CLBAMTester::FillResults()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   try
   {
      UpdateEngines();

      AssertValid();

      // section forces
      FillSectionResults();

      // influence lines
      FillInfluenceResults();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMTester);
   }

	return S_OK;
}
void CLBAMTester::FillInfluenceResults()
{
   HRESULT hr;

   long cnt;
   hr = m_InfluenceResultRequests->get_Count(&cnt);
   THROW_ON_FAIL(hr);

   for (long i=0; i<cnt; i++)
   {
      CComPtr<IInfluenceResultRequest> request;
      hr = m_InfluenceResultRequests->get_Item(i, &request);
      THROW_ON_FAIL(hr);

      // Influence forces
      if (m_DoComputeForces)
      {
         CComPtr<IInfluenceLine> the_result;
         ComputeInfluenceResult(request, &the_result);

         // set new result as benchmark
         hr = request->put_InfluenceLine(the_result);
         THROW_ON_FAIL(hr);
      }
   }
}

void CLBAMTester::FillSectionResults()
{
   HRESULT hr;

   long cnt;
   hr = m_SectionResultRequests->get_Count(&cnt);
   THROW_ON_FAIL(hr);

   for (long i=0; i<cnt; i++)
   {
      CComPtr<ISectionResultRequest> request;
      hr = m_SectionResultRequests->get_Item(i, &request);
      THROW_ON_FAIL(hr);

      // section forces
      if (m_DoComputeForces)
      {
         CComPtr<ISectionResult3D> the_result;
         ComputeSectionForceResult(request, &the_result);

         // set new reault as benchmark
         // get benchmark result
         hr = request->put_SectionForceResult(the_result);
         THROW_ON_FAIL(hr);
      }

      // deflections
      if (m_DoComputeDeflections)
      {
         CComPtr<ISectionResult3D> the_result;
         ComputeDeflectionResult(request, &the_result);

         // set new reault as benchmark
         // get benchmark result
         hr = request->put_DeflectionResult(the_result);
         THROW_ON_FAIL(hr);
      }

      // Stresses
      if (m_DoComputeStresses)
      {
         CComPtr<ISectionStressResult> the_result;
         ComputeStressResults(request, &the_result);

         // set new result as benchmark
         // get benchmark result
         hr = request->put_StressResults(the_result);
         THROW_ON_FAIL(hr);
      }
   }
}

void CLBAMTester::CompareSectionForceResults(ISectionResult3D* benchmark, ISectionResult3D* theResult, ISectionResultRequest* request, ITestLogger* Logger)
{
   HRESULT hr;
   bool passed = true;

   // get force results
   double fxl_bench,    fxr_bench,    fyl_bench,    fyr_bench,    mzl_bench,    mzr_bench;
   double fxl_result,   fxr_result,   fyl_result,   fyr_result,   mzl_result,   mzr_result;
   double fxl_pdactual, fxr_pdactual, fyl_pdactual, fyr_pdactual, mzl_pdactual, mzr_pdactual;

   hr = benchmark->GetResult(&fxl_bench, &fyl_bench, &mzl_bench, &fxr_bench, &fyr_bench, &mzr_bench);
   THROW_ON_FAIL(hr);

   hr = theResult->GetResult(&fxl_result, &fyl_result, &mzl_result, &fxr_result, &fyr_result, &mzr_result);
   THROW_ON_FAIL(hr);

   // compare force results
   DoubleCompareStat fxl_stat, fxr_stat, fyl_stat, fyr_stat, mzl_stat, mzr_stat;

   fxl_stat = CompareDoubles(fxl_bench, fxl_result, m_ForceMinPercentDiff,  m_ForceMinTolerance, &fxl_pdactual);
   fxr_stat = CompareDoubles(fxr_bench, fxr_result, m_ForceMinPercentDiff,  m_ForceMinTolerance, &fxr_pdactual);
   fyl_stat = CompareDoubles(fyl_bench, fyl_result, m_ForceMinPercentDiff,  m_ForceMinTolerance, &fyl_pdactual);
   fyr_stat = CompareDoubles(fyr_bench, fyr_result, m_ForceMinPercentDiff,  m_ForceMinTolerance, &fyr_pdactual);
   mzl_stat = CompareDoubles(mzl_bench, mzl_result, m_ForceMinPercentDiff,  m_ForceMinTolerance, &mzl_pdactual);
   mzr_stat = CompareDoubles(mzr_bench, mzr_result, m_ForceMinPercentDiff,  m_ForceMinTolerance, &mzr_pdactual);

   // report statistics
   CComBSTR descr;
   GetRequestDescription(request, &descr);

   if (  fxl_stat != fcsPass || fxr_stat != fcsPass ||
         fyl_stat != fcsPass || fyr_stat != fcsPass ||
         mzl_stat != fcsPass || mzr_stat != fcsPass)
   {
      std::stringstream os;
      os << std::setiosflags( std::ios::left );
      os << std::endl<< "SectionForceResult"<<std::endl;
      os << std::setw(12)<<"Value"<<std::setw(12)<<"BenchMark"<<std::setw(12)<<"Value"<<std::setw(12)<<"Reason"<<std::setw(12)<<"% Diff"<<std::endl; 
      WriteDoubleCompare(os, "Fx Left",  fxl_bench, fxl_result, fxl_stat, fxl_pdactual);
      WriteDoubleCompare(os, "Fx Right", fxr_bench, fxr_result, fxr_stat, fxr_pdactual);
      WriteDoubleCompare(os, "Fy Left",  fyl_bench, fyl_result, fyl_stat, fyl_pdactual);
      WriteDoubleCompare(os, "Fy Right", fyr_bench, fyr_result, fyr_stat, fyr_pdactual);
      WriteDoubleCompare(os, "Mz Left",  mzl_bench, mzl_result, mzl_stat, mzl_pdactual);
      WriteDoubleCompare(os, "Mz Right", mzr_bench, mzr_result, mzr_stat, mzr_pdactual);

      CComBSTR descr2(os.str().c_str());
      descr += descr2;

      hr = Logger->AddTestEntry(trFailed, descr);
      THROW_ON_FAIL(hr);
   }
   else
   {
      hr = Logger->AddTestEntry(trPassed, descr);
      THROW_ON_FAIL(hr);
   }
}

/////////////////////
// influence results
void CLBAMTester::ValidateInfluenceResults(ITestLogger *pLogger)
{
   HRESULT hr;
   hr = pLogger->AddDescriptionEntry(CComBSTR("Validating Influence Forces"));
   THROW_ON_FAIL(hr);

   long cnt;
   hr = m_InfluenceResultRequests->get_Count(&cnt);
   THROW_ON_FAIL(hr);

   for (long i=0; i<cnt; i++)
   {
      CComPtr<IInfluenceResultRequest> request;
      hr = m_InfluenceResultRequests->get_Item(i, &request);
      THROW_ON_FAIL(hr);

      // Influence forces
      ValidateInfluenceResult(request, pLogger);
   }
}

void CLBAMTester::ValidateInfluenceResult(IInfluenceResultRequest* pRequest, ITestLogger* pLogger)
{
   HRESULT hr;
   // get benchmark result
   CComPtr<IInfluenceLine> benchmark;
   hr = pRequest->get_InfluenceLine(&benchmark);
   THROW_ON_FAIL(hr);

   if (benchmark==NULL)
   {
      CComBSTR descr;
      GetRequestDescription(pRequest, &descr);
      CComBSTR msg = CreateErrorMsg1S(IDS_E_NO_BENCHMARK, descr);
      pLogger->AddDescriptionEntry(msg);
      THROW_LBAMTF_MSG(NO_BENCHMARK, msg);
   }

   // get result for current engine
   CComPtr<IInfluenceLine> the_result;
   ComputeInfluenceResult(pRequest, &the_result);

   // have results - now perform comparison
   CompareInfluenceResults(benchmark, the_result, pRequest, pLogger);
}

void CLBAMTester::ComputeInfluenceResult(IInfluenceResultRequest* request, IInfluenceLine* *pResult)
{
   if (m_InfluenceLineResponse==NULL)
      THROW_LBAMTF(NO_LOADGROUP_RESPONSE);

   HRESULT hr;
   CComBSTR stage;
   hr = request->get_Stage(&stage);
   THROW_ON_FAIL(hr);


   ResultsOrientation orientation;
   hr = request->get_ResultsOrientation(&orientation);
   THROW_ON_FAIL(hr);

   ResponseType resp_type;
   hr = request->get_ResponseType(&resp_type);
   THROW_ON_FAIL(hr);

   ForceEffectType force_type;
   hr = request->get_ForceEffectType(&force_type);
   THROW_ON_FAIL(hr);

   long poi_id;
   hr = request->get_PoiId(&poi_id);
   THROW_ON_FAIL(hr);

   // get the result
   CComPtr<IInfluenceLine> rgt_ifl;
   switch (resp_type)
   {
   case atDeflection:
      {
         hr = m_InfluenceLineResponse->ComputeDeflectionInfluenceLine(poi_id, stage, force_type, pResult, &rgt_ifl);
         THROW_ON_FAIL(hr);
      }
      break;
   case atForce:
      {
         hr = m_InfluenceLineResponse->ComputeForceInfluenceLine(poi_id, stage, force_type, orientation, pResult, &rgt_ifl);
         THROW_ON_FAIL(hr);
      }
      break;
   default:
      ATLASSERT(0);
   }

}

// free function that compares influence locations
int CompareInfluenceLocations(InfluenceLocationType benchLt, double benchLoc, InfluenceLocationType resultLt, double resultLoc)
{

   if ( IsEqual(benchLoc, resultLoc, 1.0e-9) )
   {
      if (benchLt==resultLt)
         return 0;
      else if (benchLt==iflDualLeft)
         return -1;
      else if (benchLt==iflSingle && resultLt==iflDualRight)
         return -1;
      else if (benchLt==iflSingle && resultLt==iflDualLeft)
         return 1;
      else
         return 1;
   }
   else
   {
      return benchLoc < resultLoc ? -1 : 1;
   }
}

void CLBAMTester::CompareInfluenceResults(IInfluenceLine* benchmark, IInfluenceLine* theResult, IInfluenceResultRequest* request, ITestLogger* Logger)
{
   HRESULT hr;
   bool passed = true;

   InfluenceProcessingType process_type;
   hr = request->get_InfluenceProcessing(&process_type);
   THROW_ON_FAIL(hr);

   InfluenceSideType infl_side;
   if (process_type==iptFlattenPositive)
   {
      infl_side = ilsNegative;
   }
   else if (process_type==iptFlattenNegative)
   {
      infl_side = ilsPositive;
   }
   else
   {
      infl_side = ilsBoth;
   }

   // first determine if we passed or failed
   long bench_size, result_size;
   hr = benchmark->get_Count(infl_side,&bench_size);
   THROW_ON_FAIL(hr);
   hr = theResult->get_Count(infl_side,&result_size);
   THROW_ON_FAIL(hr);

   // set up tolerances
   ResponseType rt;
   hr = request->get_ResponseType(&rt);
   double tol, percent_diff;
   if (rt == rtForces)
   {
      tol          = m_ForceMinTolerance;
      percent_diff = m_ForceMinPercentDiff;
   }
   else
   {
      tol          = m_DeflectionMinTolerance;
      percent_diff = m_DeflectionMinPercentDiff;
   }

   // perform initial comparison
   if (bench_size==result_size)
   {
      for (long i=0; i<bench_size; i++)
      {
         double bench_value, result_value;
         InfluenceLocationType bench_lt, result_lt;
         double bench_loc, result_loc;
         hr = benchmark->Item(i, infl_side, &bench_value, &bench_lt, &bench_loc);
         THROW_ON_FAIL(hr);
         hr = theResult->Item(i, infl_side, &result_value, &result_lt, &result_loc);
         THROW_ON_FAIL(hr);

         if ( !IsEqual(bench_loc, result_loc, 1.0e-9) )
         {
            passed = false;
            break;
         }

         if (bench_lt != result_lt)
         {
            passed = false;
            break;
         }

         if ( !IsEqual(bench_value, result_value, tol) )
         {
            passed = false;
            break;
         }
      }
   }
   else
   {
      passed = false;
   }

   // report statistics
   CComBSTR descr;
   GetRequestDescription(request, &descr);

   if ( passed)
   {
      hr = Logger->AddTestEntry(trPassed, descr);
      THROW_ON_FAIL(hr);
   }
   else
   {
      // failed - bummer
      std::stringstream os;
      os << std::setiosflags( std::ios::left );
      os << std::endl<< "InfluenceResult"<<std::endl;
      os << std::setw(19)<<"Location"<<std::setw(12)<<"BenchMark"<<std::setw(12)<<"Value"<<std::setw(12)<<"Reason"<<std::setw(12)<<"% Diff"<<std::endl; 

      // need to loop through and print out values - remembering that locations can be out of synch
      long i_bench = 0;
      long i_result = 0;
      while(i_bench<bench_size && i_result<result_size)
      {
         bool is_bench  = i_bench<bench_size;
         bool is_result = i_result<result_size;

         double bench_value, result_value;
         InfluenceLocationType bench_lt, result_lt;
         double bench_loc, result_loc;

         if (is_bench)
         {
            hr = benchmark->Item(i_bench, infl_side, &bench_value, &bench_lt, &bench_loc);
            THROW_ON_FAIL(hr);
         }

         if (is_result)
         {
            hr = theResult->Item(i_result, infl_side, &result_value, &result_lt, &result_loc);
            THROW_ON_FAIL(hr);
         }


         if (is_bench && is_result)
         {
            // have both results - must see if they are at the same location
            int cmp = CompareInfluenceLocations(bench_lt, bench_loc, result_lt, result_loc);
            if (cmp==0)
            {
               // two results at same location - write comparison
               WriteCompareInfluenceLocations(os, bench_loc, bench_lt, bench_value, result_value, tol, percent_diff);

               i_bench++;
               i_result++;
            }
            else if (cmp==-1)
            {
               // benchmark location is less - write benchmark only
               WriteInfluenceNoMatch(os, bench_loc, bench_lt, bench_value, true);
               i_bench++;
            }
            else
            {
               // result location is less - write result only
               WriteInfluenceNoMatch(os, result_loc, result_lt, result_value, false);
               i_result++;
            }
         }
         else if (is_bench)
         {
            // no results left and still benchmarks
            WriteInfluenceNoMatch(os, bench_loc, bench_lt, bench_value, true);
            i_bench++;
         }
         else
         {
            // no benchmarks left - still results
            WriteInfluenceNoMatch(os, result_loc, result_lt, result_value, false);
            i_result++;
         }
      }

      CComBSTR descr2(os.str().c_str());
      descr += descr2;

      hr = Logger->AddTestEntry(trFailed, descr);
      THROW_ON_FAIL(hr);
   }
}



void GetRequestDescription(IUnknown* unk, BSTR* description)
{
   CComQIPtr<ITestRequest,&IID_ITestRequest> it(unk);
   if (!it)
   {
      ATLASSERT(0);
   }

   it->get_Description(description);
}

STDMETHODIMP CLBAMTester::get_Description(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Description.Copy();

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_Description(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Description = newVal;

	return S_OK;
}

void CLBAMTester::UpdateEngines()
{

   // here we marry the engines to the model at the last minute
   if (m_Dirty || m_LoadGroupResponse==NULL )
   {
      // create our engine based on analysis type
      m_LoadGroupResponse = NULL;
      m_InfluenceLineResponse = NULL;

      if (m_AnalysisType == atForce)
      {
         m_LoadGroupResponse.CoCreateInstance(CLSID_LoadGroupForceResponse);
      }
      else
      {
         m_LoadGroupResponse.CoCreateInstance(CLSID_LoadGroupDeflectionResponse);
      }

      HRESULT hr;
      CComQIPtr<IDependOnLBAM> respctx(m_LoadGroupResponse);
      hr = respctx->putref_Model(m_Model);
      THROW_ON_FAIL(hr);

      CComQIPtr<IInfluenceLineResponse> pir(m_LoadGroupResponse);
      ATLASSERT(pir);
      m_InfluenceLineResponse = pir;

      // set tolerance for influence response
      m_InfluenceLineResponse->SetZeroTolerance(m_ForceMinTolerance,m_DeflectionMinTolerance);

      m_Dirty = false;
   }
}

STDMETHODIMP CLBAMTester::get_DoComputeForces(VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_DoComputeForces;

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_DoComputeForces(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (newVal!=VARIANT_FALSE)
      m_DoComputeForces = VARIANT_TRUE;
   else
      m_DoComputeForces= VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_DoComputeDeflections(VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_DoComputeDeflections;

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_DoComputeDeflections(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (newVal!=VARIANT_FALSE)
      m_DoComputeDeflections = VARIANT_TRUE;
   else
      m_DoComputeDeflections= VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CLBAMTester::get_DoComputeStresses(VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_DoComputeStresses;

	return S_OK;
}

STDMETHODIMP CLBAMTester::put_DoComputeStresses(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (newVal!=VARIANT_FALSE)
      m_DoComputeStresses = VARIANT_TRUE;
   else
      m_DoComputeStresses= VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CLBAMTester::ClearResults()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   try
   {
      ClearSectionResults();

      ClearInfluenceResults();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMTester);
   }

	return S_OK;
}


void CLBAMTester::ClearInfluenceResults()
{
   HRESULT hr;

   long cnt;
   hr = m_InfluenceResultRequests->get_Count(&cnt);
   THROW_ON_FAIL(hr);

   for (long i=0; i<cnt; i++)
   {
      CComPtr<IInfluenceResultRequest> request;
      hr = m_InfluenceResultRequests->get_Item(i, &request);
      THROW_ON_FAIL(hr);

      // Influence line
      hr = request->put_InfluenceLine(NULL);
      THROW_ON_FAIL(hr);
   }
}


void CLBAMTester::ClearSectionResults()
{
   HRESULT hr;

   long cnt;
   hr = m_SectionResultRequests->get_Count(&cnt);
   THROW_ON_FAIL(hr);

   for (long i=0; i<cnt; i++)
   {
      CComPtr<ISectionResultRequest> request;
      hr = m_SectionResultRequests->get_Item(i, &request);
      THROW_ON_FAIL(hr);

      // section forces
      hr = request->put_SectionForceResult(NULL);
      THROW_ON_FAIL(hr);

      // deflections
      hr = request->put_DeflectionResult(NULL);
      THROW_ON_FAIL(hr);

      // deflections
      hr = request->put_StressResults(NULL);
      THROW_ON_FAIL(hr);
   }
}

STDMETHODIMP CLBAMTester::ImportResultsFromFile(BSTR FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   HRESULT hr;

   try
   {
      // open file
      CComPtr<IStructuredLoad2> pload;
      hr = pload.CoCreateInstance( CLSID_StructuredLoad2 );
      if (FAILED(hr))
         return hr;

      hr = pload->Open( FileName );
      if (FAILED(hr))
         return hr;

      // Only read the results block
      HRESULT hr;
      VARIANT_BOOL eb;

      hr = pload->BeginUnit(CComBSTR("LBAMTester"));
      if (FAILED(hr))
         return hr;

      double ver;
      hr = pload->get_Version(&ver);
      if (FAILED(hr))
         return hr;

      if (ver!=MY_VER)
         return STRLOAD_E_BADVERSION;

      {        

         // Skip over configuration block
         hr = pload->BeginUnit(CComBSTR("Configuration"));
         if (FAILED(hr))
            return hr;

         hr = pload->EndUnit(&eb);
         if (FAILED(hr))
            return hr;

         // skip model block
         hr = pload->BeginUnit(CComBSTR("Model"));
         if (FAILED(hr))
            return hr;

         // end of model block
         hr = pload->EndUnit(&eb);
         if (FAILED(hr))
            return hr;

         // begin results block
         hr = pload->BeginUnit(CComBSTR("Results"));
         if (FAILED(hr))
            return hr;

            // section results requests
            CComPtr<ISectionResultRequests> pSfr;
            hr = pSfr.CoCreateInstance( CLSID_SectionResultRequests );
            if (FAILED(hr))
               return hr;

            IStructuredStorage2* pissfr=NULL;
            hr = pSfr.QueryInterface(&pissfr);
            if (FAILED(hr))
               return hr;

            hr = pissfr->Load(pload);
            if (FAILED(hr))
               return hr;

            pissfr->Release();
            m_SectionResultRequests = pSfr;

            // Influence results requests
            CComPtr<IInfluenceResultRequests> pIfr;
            hr = pIfr.CoCreateInstance( CLSID_InfluenceResultRequests );
            if (FAILED(hr))
               return hr;

            IStructuredStorage2* pisifr=NULL;
            hr = pSfr.QueryInterface(&pisifr);
            if (FAILED(hr))
               return hr;

            hr = pisifr->Load(pload);
            if (FAILED(hr))
               return hr;

            pissfr->Release();
            m_InfluenceResultRequests = pIfr;

         // end of results block
         hr = pload->EndUnit(&eb);
         if (FAILED(hr))
            return hr;

         if (eb!=VARIANT_TRUE)
            return STRLOAD_E_INVALIDFORMAT;

         AssertValid();
      }

      hr = pload->EndUnit(&eb);
      if (FAILED(hr))
         return hr;

      if (eb!=VARIANT_TRUE)
         return STRLOAD_E_INVALIDFORMAT;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMTester);
   }

   return S_OK;
}


STDMETHODIMP CLBAMTester::LoadFromFile(BSTR fileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   // open file
   HRESULT hr;
   CComPtr<IStructuredLoad2> psl;
   hr = psl.CoCreateInstance( CLSID_StructuredLoad2 );
   if (FAILED(hr))
      return hr;

   hr = psl->Open( fileName );
   if (FAILED(hr))
      return hr;

   // clear ourself and load
   ClearResults();

   hr = this->Load( psl );
   if (FAILED(hr))
      return hr;

   return psl->Close();

}

STDMETHODIMP CLBAMTester::SaveToFile(BSTR fileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   // open file
   HRESULT hr;
   CComPtr<IStructuredSave2> psl;
   hr = psl.CoCreateInstance( CLSID_StructuredSave2 );
   if (FAILED(hr))
      return hr;

   hr = psl->Open( fileName );
   if (FAILED(hr))
      return hr;

   hr =this->Save( psl );
   if (FAILED(hr))
      return hr;

   return psl->Close();
}


