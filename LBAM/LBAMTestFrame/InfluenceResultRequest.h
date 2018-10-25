// InfluenceResultRequest.h : Declaration of the CInfluenceResultRequest

#ifndef __INFLUENCERESULTREQUEST_H_
#define __INFLUENCERESULTREQUEST_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CInfluenceResultRequest
class ATL_NO_VTABLE CInfluenceResultRequest : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInfluenceResultRequest, &CLSID_InfluenceResultRequest>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CInfluenceResultRequest>,
	public IDispatchImpl<IInfluenceResultRequest, &IID_IInfluenceResultRequest, &LIBID_WBFLLBAMTESTFRAMELib>,
   public IPersistImpl<CInfluenceResultRequest>,
	public IDispatchImpl<ITestRequest, &IID_ITestRequest, &LIBID_WBFLTools>,
	public IDispatchImpl<IStructuredStorage2, &IID_IStructuredStorage2, &LIBID_WBFLTools>
{
public:
   CInfluenceResultRequest():
   m_PoiId(-1),
   m_ForceEffectType(fetFx),
   m_ResponseType(rtForces),
   m_ZeroTolerance(0.0),
   m_InfluenceProcessingType(iptRaw)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_INFLUENCERESULTREQUEST)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CInfluenceResultRequest)
	COM_INTERFACE_ENTRY(IInfluenceResultRequest)
	COM_INTERFACE_ENTRY2(IDispatch,IInfluenceResultRequest)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ITestRequest)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CInfluenceResultRequest)
END_CONNECTION_POINT_MAP()


   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

   // ITestRequest
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IInfluenceResultRequest
	STDMETHOD(Clone)(/*[out]*/IInfluenceResultRequest* *clone);
	STDMETHOD(get_InfluenceLine)(/*[out, retval]*/ IInfluenceLine* *pVal);
	STDMETHOD(put_InfluenceLine)(/*[in]*/ IInfluenceLine* newVal);
	STDMETHOD(get_ForceEffectType)(/*[out, retval]*/ ForceEffectType *pVal);
	STDMETHOD(put_ForceEffectType)(/*[in]*/ ForceEffectType newVal);
	STDMETHOD(get_ResultsOrientation)(/*[out, retval]*/ ResultsOrientation *pVal);
	STDMETHOD(put_ResultsOrientation)(/*[in]*/ ResultsOrientation newVal);
	STDMETHOD(get_Stage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Stage)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_PoiId)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PoiId)(/*[in]*/ long newVal);
public:
	STDMETHOD(get_InfluenceProcessing)(/*[out, retval]*/ InfluenceProcessingType *pVal);
	STDMETHOD(put_InfluenceProcessing)(/*[in]*/ InfluenceProcessingType newVal);
	STDMETHOD(get_ResponseType)(/*[out, retval]*/ ResponseType *pVal);
	STDMETHOD(put_ResponseType)(/*[in]*/ ResponseType newVal);

protected:
   _bstr_t                      m_Stage;
   long                         m_PoiId;
   ForceEffectType              m_ForceEffectType;
   ResponseType                 m_ResponseType;
   ResultsOrientation           m_ResultsOrientation;
   double                       m_ZeroTolerance;
   InfluenceProcessingType      m_InfluenceProcessingType;
   CComPtr<IInfluenceLine>      m_InfluenceLine;
};

#endif //__INFLUENCERESULTREQUEST_H_
