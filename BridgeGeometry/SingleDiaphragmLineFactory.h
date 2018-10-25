// SingleDiaphragmLineFactory.h : Declaration of the CSingleDiaphragmLineFactory

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CSingleDiaphragmLineFactory
//
// Create a single diaphragm line

class ATL_NO_VTABLE CSingleDiaphragmLineFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSingleDiaphragmLineFactory, &CLSID_SingleDiaphragmLineFactory>,
	public ISingleDiaphragmLineFactory
{
public:
	CSingleDiaphragmLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SINGLEDIAPHRAGMLINEFACTORY)

DECLARE_NOT_AGGREGATABLE(CSingleDiaphragmLineFactory)

BEGIN_COM_MAP(CSingleDiaphragmLineFactory)
	COM_INTERFACE_ENTRY(ISingleDiaphragmLineFactory)
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
   CogoObjectID m_AlignmentID;
   Float64 m_Station;
   CComBSTR m_bstrOrientation;
   Int16 m_Divisor;
   VARIANT_BOOL m_bStaggered;
   GirderIDType m_LeftGirderID;
   GirderIDType m_RightGirderID;

public:
   STDMETHOD(put_AlignmentID)(CogoObjectID ID);
   STDMETHOD(get_AlignmentID)(CogoObjectID* ID);
   STDMETHOD(put_Station)(Float64 station);
   STDMETHOD(get_Station)(Float64* pStation);
   STDMETHOD(put_Orientation)(BSTR orientation);
   STDMETHOD(get_Orientation)(BSTR* orientation);
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

OBJECT_ENTRY_AUTO(__uuidof(SingleDiaphragmLineFactory), CSingleDiaphragmLineFactory)
