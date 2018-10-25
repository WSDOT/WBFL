// DocUnitSystem.h : Declaration of the CDocUnitSystem

#ifndef __DOCUNITSYSTEM_H_
#define __DOCUNITSYSTEM_H_

#include "resource.h"       // main symbols
#include "UnitModeController.h"
#include "AppUnitSystem.h"
#include "WbflUnitServerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CDocUnitSystem
class ATL_NO_VTABLE CDocUnitSystem : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CDocUnitSystem,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CDocUnitSystem, &CLSID_DocUnitSystem>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CDocUnitSystem>,
   public IObjectSafetyImpl<CDocUnitSystem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IDocUnitSystem,
   public IUnitModeControllerEvents,
   public CProxyDDocUnitSystemEvents< CDocUnitSystem >
{
public:
	CDocUnitSystem()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_DOCUNITSYSTEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDocUnitSystem)
	COM_INTERFACE_ENTRY(IDocUnitSystem)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IUnitModeControllerEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDocUnitSystem)
CONNECTION_POINT_ENTRY(IID_IDocUnitSystemEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IAppUnitSystem> m_pAppUnitSys;
   CComPtr<IUnitModeController> m_pUMC;
   DWORD m_dwUMCCookie;

   HRESULT BadDisplayUnitGroupError(BSTR name);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IDocUnitSystem
public:
	STDMETHOD(get_AppUnitSystem)(/*[out, retval]*/ IAppUnitSystem* *pVal) override;
	STDMETHOD(putref_AppUnitSystem)(/*[in]*/ IAppUnitSystem* newVal) override;
	STDMETHOD(get_UnitModeController)(/*[out, retval]*/ IUnitModeController* *pVal) override;
	STDMETHOD(get_UnitMode)(/*[out, retval]*/ UnitModeType *pVal) override;
	STDMETHOD(put_UnitMode)(/*[in]*/ UnitModeType newVal) override;
	STDMETHOD(ConvertToDisplayUnits)(/*[in]*/ Float64 value,/*[in]*/ BSTR group,/*[out,retval]*/Float64* result) override;
	STDMETHOD(ConvertFromDisplayUnits)(/*[in]*/ Float64 value,/*[in]*/ BSTR group,/*[out,retval]*/Float64* result) override;
	STDMETHOD(get_Tag)(/*[in]*/ BSTR group,/*[out,retval]*/BSTR* tag) override;
	STDMETHOD(Format)(/*[in]*/ Float64 val,/*[in]*/ BSTR group,/*[in]*/ VARIANT_BOOL bShowUnitTag,/*[out,retval]*/BSTR* fmtString) override;

// _IUnitModeControllerEvents
public:
	STDMETHOD(OnUnitModeChanged)(UnitModeType newMode)
	{
      Fire_OnUpdateDisplay();
      return S_OK;
	}
};

#endif //__DOCUNITSYSTEM_H_
