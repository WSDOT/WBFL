// Connection.h : Declaration of the CConnection

#ifndef __CONNECTION_H_
#define __CONNECTION_H_

#include "resource.h"       // main symbols
#include "TxnMgrImpl.h"
#include "GenericBridgeCP.h"


/////////////////////////////////////////////////////////////////////////////
// CConnection
class ATL_NO_VTABLE CConnection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CConnection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CConnection, &CLSID_Connection>,
	public ISupportErrorInfo,
	public IConnection,
   public IStructuredStorage2,
//   public CProxyDConnectionEvents< CConnection >,
//   public IConnectionPointContainerImpl<CConnection>,
   public IObjectSafetyImpl<CConnection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CConnection()
	{
      m_BearingOffset        = 0;
      m_EndDistance          = 0;
      m_BearingOffsetMeasurementType   = mtNormal;
      m_EndDistanceMeasurementType     = mtNormal;
      m_EndDistanceMeasurementLocation = mlCenterlinePier;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_CONNECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CConnection)
	COM_INTERFACE_ENTRY(IConnection)

	COM_INTERFACE_ENTRY(IStructuredStorage2)

	COM_INTERFACE_ENTRY(ISupportErrorInfo)

//   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CConnection)
//	CONNECTION_POINT_ENTRY(IID_IConnectionEvents)
END_CONNECTION_POINT_MAP()

private:
   Float64 m_BearingOffset;
   Float64 m_EndDistance;
   Float64 m_SupportWidth;
   MeasurementType m_BearingOffsetMeasurementType;
   MeasurementType m_EndDistanceMeasurementType;
   MeasurementLocation m_EndDistanceMeasurementLocation;

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IConnection
public:
   STDMETHOD(get_BearingOffset)(/*[out,retval]*/ Float64* brgOffset);
	STDMETHOD(put_BearingOffset)(/*[in]*/ Float64 brgOffset);
   STDMETHOD(get_BearingOffsetMeasurementType)(/*[out,retval]*/ MeasurementType* measure);
   STDMETHOD(put_BearingOffsetMeasurementType)(/*[in]*/ MeasurementType measure);
	STDMETHOD(get_EndDistance)(/*[out,retval]*/ Float64* endDist);
	STDMETHOD(put_EndDistance)(/*[in]*/ Float64 endDist);
   STDMETHOD(get_EndDistanceMeasurementType)(/*[out,retval]*/ MeasurementType* measure);
   STDMETHOD(put_EndDistanceMeasurementType)(/*[in]*/ MeasurementType measure);
   STDMETHOD(get_EndDistanceMeasurementLocation)(/*[out,retval]*/ MeasurementLocation* measure);
   STDMETHOD(put_EndDistanceMeasurementLocation)(/*[in]*/ MeasurementLocation measure);
   STDMETHOD(get_SupportWidth)(/*[out,retval]*/ Float64* supportWidth);
	STDMETHOD(put_SupportWidth)(/*[in]*/ Float64 supportWidth);
   STDMETHOD(Clone)(/*[out,retval]*/IConnection** clone);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};

#endif //__CONNECTION_H_
