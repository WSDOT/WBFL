// LBAMTester.h : Declaration of the CLBAMTester

#ifndef __LBAMTESTER_H_
#define __LBAMTESTER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLBAMTester
class ATL_NO_VTABLE CLBAMTester : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLBAMTester, &CLSID_LBAMTester>,
	public ISupportErrorInfo,
   public IPersistImpl<CLBAMTester>,
	public IDispatchImpl<ILBAMTester, &IID_ILBAMTester, &LIBID_WBFLLBAMTESTFRAMELib>,
	public IDispatchImpl<IStructuredStorage2, &IID_IStructuredStorage2, &LIBID_WBFLTools>
{
public:
   CLBAMTester();

DECLARE_REGISTRY_RESOURCEID(IDR_LBAMTESTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLBAMTester)
	COM_INTERFACE_ENTRY(ILBAMTester)
	COM_INTERFACE_ENTRY2(IDispatch,ILBAMTester)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

// ILBAMTester
public:
	STDMETHOD(get_InfluenceResultRequests)(/*[out, retval]*/ IInfluenceResultRequests* *pVal);
	STDMETHOD(SaveToFile)(/*[in]*/BSTR fileName);
	STDMETHOD(LoadFromFile)(/*[in]*/BSTR fileName);
	STDMETHOD(ImportResultsFromFile)(/*[in]*/BSTR FileName);
	STDMETHOD(ClearResults)();
	STDMETHOD(get_DoComputeStresses)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DoComputeStresses)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_StressMinTolerance)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_StressMinTolerance)(/*[in]*/ double newVal);
	STDMETHOD(get_StressMinPercentDiff)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_StressMinPercentDiff)(/*[in]*/ double newVal);
	STDMETHOD(get_DeflectionMinTolerance)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_DeflectionMinTolerance)(/*[in]*/ double newVal);
	STDMETHOD(get_DeflectionMinPercentDiff)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_DeflectionMinPercentDiff)(/*[in]*/ double newVal);
	STDMETHOD(get_DoComputeDeflections)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DoComputeDeflections)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DoComputeForces)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DoComputeForces)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);
	STDMETHOD(FillResults)();
	STDMETHOD(ValidateResults)(/*[in]*/ITestLogger* Logger);
	STDMETHOD(get_SectionResultRequests)(/*[out, retval]*/ ISectionResultRequests* *pVal);
	STDMETHOD(get_AnalysisType)(/*[out, retval]*/ AnalysisType* pVal);
	STDMETHOD(put_AnalysisType)(/*[in]*/ AnalysisType newVal);
	STDMETHOD(AttachToModelFile)(/*[in]*/BSTR FileName);
	STDMETHOD(get_Model)(/*[out, retval]*/ ILBAMModel* *pVal);
	STDMETHOD(putref_Model)(/*[in]*/ ILBAMModel* newVal);
	STDMETHOD(get_ForceMinPercentDiff)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_ForceMinPercentDiff)(/*[in]*/ double newVal);
	STDMETHOD(get_ForceMinTolerance)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_ForceMinTolerance)(/*[in]*/ double newVal);

private:
	void AssertValid();
   void UpdateEngines();
	void ValidateSectionResults(ITestLogger* Logger);
	void ValidateInfluenceResults(ITestLogger* Logger);

   void FillSectionResults();
   void ClearSectionResults();
   void FillInfluenceResults();
   void ClearInfluenceResults();

	void ValidateSectionForceResult(ISectionResultRequest* pRequest, ITestLogger* pLogger);
   void ComputeSectionForceResult(ISectionResultRequest* request, ISectionResult3D* *pResult);
   void CompareSectionForceResults(ISectionResult3D* benchmark, ISectionResult3D* the_result, ISectionResultRequest* request, ITestLogger* Logger);

	void ValidateDeflectionResult(ISectionResultRequest* pRequest, ITestLogger* pLogger);
   void ComputeDeflectionResult(ISectionResultRequest* request, ISectionResult3D* *pResult);
   void CompareDeflectionResults(ISectionResult3D* benchmark, ISectionResult3D* the_result, ISectionResultRequest* request, ITestLogger* Logger);

	void ValidateStressResults(ISectionResultRequest* pRequest, ITestLogger* pLogger);
   void ComputeStressResults(ISectionResultRequest* request, ISectionStressResult* *pResult);
   void CompareStressResults(ISectionStressResult* benchmark, ISectionStressResult* the_result, ISectionResultRequest* request, ITestLogger* Logger);

	void ValidateInfluenceResult(IInfluenceResultRequest* pRequest, ITestLogger* pLogger);
   void ComputeInfluenceResult(IInfluenceResultRequest* request, IInfluenceLine* *pResult);
   void CompareInfluenceResults(IInfluenceLine* benchmark, IInfluenceLine* theResult, IInfluenceResultRequest* request, ITestLogger* Logger);

   // member data
   AnalysisType                   m_AnalysisType;
   CComBSTR                       m_Description;
   CComPtr<ILBAMModel>            m_Model;
   double                         m_ForceMinPercentDiff;
   double                         m_ForceMinTolerance;
   VARIANT_BOOL                   m_DoComputeForces;
   double                         m_DeflectionMinPercentDiff;
   double                         m_DeflectionMinTolerance;
   VARIANT_BOOL                   m_DoComputeDeflections;
   double                         m_StressMinPercentDiff;
   double                         m_StressMinTolerance;
   VARIANT_BOOL                   m_DoComputeStresses;

   CComPtr<ISectionResultRequests>   m_SectionResultRequests;
   CComPtr<IInfluenceResultRequests> m_InfluenceResultRequests;

   // response calculation engines - not persistent
   CComPtr<ILoadGroupResponse>      m_LoadGroupResponse;
   CComPtr<IInfluenceLineResponse>  m_InfluenceLineResponse;

   bool m_Dirty; // dirty when an engine or model changes
};

#endif //__LBAMTESTER_H_
