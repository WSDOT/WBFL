// LBAMResponseDumper.h : Declaration of the CLBAMResponseDumper

#ifndef __LBAMRESPONSEDUMPER_H_
#define __LBAMRESPONSEDUMPER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLBAMResponseDumper
class ATL_NO_VTABLE CLBAMResponseDumper : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLBAMResponseDumper, &CLSID_LBAMResponseDumper>,
	public ISupportErrorInfo,
	public IDispatchImpl<ILBAMResponseDumper, &IID_ILBAMResponseDumper, &LIBID_WBFLLBAMDumper>
{
public:
	CLBAMResponseDumper();

DECLARE_REGISTRY_RESOURCEID(IDR_LBAMRESPONSEDUMPER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLBAMResponseDumper)
	COM_INTERFACE_ENTRY(ILBAMResponseDumper)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILBAMResponseDumper
public:
	STDMETHOD(get_DumpLoadCombinationResponse)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DumpLoadCombinationResponse)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DumpLoadCaseResponse)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DumpLoadCaseResponse)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DumpLiveLoadModelResponse)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DumpLiveLoadModelResponse)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DumpEnvelopedVehicularResponse)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DumpEnvelopedVehicularResponse)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DumpContraflexure)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DumpContraflexure)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DumpInfluenceLines)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DumpInfluenceLines)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DumpLoadGroupResponse)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DumpLoadGroupResponse)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DumpModel)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DumpModel)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(Dump)(/*[in]*/ILBAMAnalysisEngine* engine, /*[in]*/BSTR fileName, /*[in]*/BSTR detailsFileName);

private:
   VARIANT_BOOL m_DumpModel;
   VARIANT_BOOL m_DumpLoadGroups;
   VARIANT_BOOL m_DumpInfluenceLines;
   VARIANT_BOOL m_DumpContraflexure;
   VARIANT_BOOL m_DumpEnvelopedVehicularResponse;
   VARIANT_BOOL m_LiveLoadModelResponse;
   VARIANT_BOOL m_LoadCaseResponse;
   VARIANT_BOOL m_LoadCombinationResponse;
};

#endif //__LBAMRESPONSEDUMPER_H_
