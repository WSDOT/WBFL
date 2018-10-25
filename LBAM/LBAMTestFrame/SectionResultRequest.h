// SectionResultRequest.h : Declaration of the CSectionResultRequest

#ifndef __SECTIONRESULTREQUEST_H_
#define __SECTIONRESULTREQUEST_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSectionResultRequest
class ATL_NO_VTABLE CSectionResultRequest : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSectionResultRequest, &CLSID_SectionResultRequest>,
	public IDispatchImpl<ISectionResultRequest, &IID_ISectionResultRequest, &LIBID_WBFLLBAMTESTFRAMELib>,
   public IPersistImpl<CSectionResultRequest>,
	public IDispatchImpl<ITestRequest, &IID_ITestRequest, &LIBID_WBFLTools>,
	public IDispatchImpl<IStructuredStorage2, &IID_IStructuredStorage2, &LIBID_WBFLTools>
{
public: 
   CSectionResultRequest():
   m_ResultsOrientation(roGlobal),
   m_ResultsSummationType(rsIncremental),
   m_LoadingType(ltLoadGroup),
   m_PoiId(-1)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SECTIONRESULTREQUEST)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSectionResultRequest)
	COM_INTERFACE_ENTRY(ISectionResultRequest)
	COM_INTERFACE_ENTRY2(IDispatch,ISectionResultRequest)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ITestRequest)
END_COM_MAP()

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

   // ITestRequest
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);

// ISectionResultRequest
public:
	STDMETHOD(get_StressResults)(/*[out, retval]*/ ISectionStressResult* *pVal);
	STDMETHOD(put_StressResults)(/*[in]*/ ISectionStressResult* newVal);
	STDMETHOD(get_DeflectionResult)(/*[out, retval]*/ ISectionResult3D* *pVal);
	STDMETHOD(put_DeflectionResult)(/*[in]*/ ISectionResult3D* newVal);
	STDMETHOD(Clone)(/*[out]*/ISectionResultRequest* *clone);
	STDMETHOD(get_SectionForceResult)(/*[out, retval]*/ ISectionResult3D* *pVal);
	STDMETHOD(put_SectionForceResult)(/*[in]*/ ISectionResult3D* newVal);
	STDMETHOD(get_ResultsOrientation)(/*[out, retval]*/ ResultsOrientation *pVal);
	STDMETHOD(put_ResultsOrientation)(/*[in]*/ ResultsOrientation newVal);
	STDMETHOD(get_ResultsSummationType)(/*[out, retval]*/ ResultsSummationType *pVal);
	STDMETHOD(put_ResultsSummationType)(/*[in]*/ ResultsSummationType newVal);
	STDMETHOD(get_LoadingName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_LoadingName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_LoadingType)(/*[out, retval]*/ LoadingType *pVal);
	STDMETHOD(put_LoadingType)(/*[in]*/ LoadingType newVal);
	STDMETHOD(get_Stage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Stage)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_PoiId)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PoiId)(/*[in]*/ long newVal);

protected:
   _bstr_t                      m_Stage;
   long                         m_PoiId;
   LoadingType                  m_LoadingType;
   _bstr_t                      m_LoadingName;
   ResultsOrientation           m_ResultsOrientation;
   ResultsSummationType         m_ResultsSummationType;
   CComPtr<ISectionResult3D> m_SfResult;
   CComPtr<ISectionResult3D>   m_DeflResult;
   CComPtr<ISectionStressResult>      m_StressResults;

};

#endif //__SectionResultRequest_H_
