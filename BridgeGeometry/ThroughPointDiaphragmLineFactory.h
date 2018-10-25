// ThroughPointDiaphragmLineFactory.h : Declaration of the CThroughPointDiaphragmLineFactory

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CThroughPointDiaphragmLineFactory
//
// Create a single diaphragm line through a point at a given direction

class ATL_NO_VTABLE CThroughPointDiaphragmLineFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CThroughPointDiaphragmLineFactory, &CLSID_ThroughPointDiaphragmLineFactory>,
	public IThroughPointDiaphragmLineFactory
{
public:
	CThroughPointDiaphragmLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_THROUGHPOINTDIAPHRAGMLINEFACTORY)

DECLARE_NOT_AGGREGATABLE(CThroughPointDiaphragmLineFactory)

BEGIN_COM_MAP(CThroughPointDiaphragmLineFactory)
	COM_INTERFACE_ENTRY(IThroughPointDiaphragmLineFactory)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      return Reset();
	}

	void FinalRelease()
	{
	}

   LineIDType m_ID;
   CComPtr<IPoint2d> m_Point;
   CComPtr<IDirection> m_Direction;
   VARIANT_BOOL m_bStaggered;
   GirderIDType m_LeftGirderID;
   GirderIDType m_RightGirderID;

public:
   STDMETHOD(put_Point)(IPoint2d* point);
   STDMETHOD(get_Point)(IPoint2d** point);
   STDMETHOD(put_Direction)(IDirection* direction);
   STDMETHOD(get_Direction)(IDirection** direction);
   STDMETHOD(put_DiaphragmLineID)(LineIDType newVal);
   STDMETHOD(get_DiaphragmLineID)(LineIDType* pVal);
   STDMETHOD(put_Staggered)(VARIANT_BOOL bStaggered);
   STDMETHOD(get_Staggered)(VARIANT_BOOL* bStaggered);
   STDMETHOD(put_LeftGirderLineID)(GirderIDType ID);
   STDMETHOD(get_LeftGirderLineID)(GirderIDType* ID);
   STDMETHOD(put_RightGirderLineID)(GirderIDType ID);
   STDMETHOD(get_RightGirderLineID)(GirderIDType* ID);

   STDMETHOD(Create)(IBridgeGeometry* pBridge,IUnkArray** ppArrayDiaphagmLines);
   STDMETHOD(Reset)();
};

OBJECT_ENTRY_AUTO(__uuidof(ThroughPointDiaphragmLineFactory), CThroughPointDiaphragmLineFactory)
