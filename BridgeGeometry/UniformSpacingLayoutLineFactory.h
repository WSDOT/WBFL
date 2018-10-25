// UniformSpacingLayoutLineFactory.h : Declaration of the CUniformSpacingLayoutLineFactory

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CUniformSpacingLayoutLineFactory
//
// Creates Layout Lines from a path object

class ATL_NO_VTABLE CUniformSpacingLayoutLineFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUniformSpacingLayoutLineFactory, &CLSID_UniformSpacingLayoutLineFactory>,
	public IUniformSpacingLayoutLineFactory
{
public:
	CUniformSpacingLayoutLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_UNIFORMSPACINGLAYOUTLINEFACTORY)

BEGIN_COM_MAP(CUniformSpacingLayoutLineFactory)
	COM_INTERFACE_ENTRY(ILayoutLineFactory)
	COM_INTERFACE_ENTRY(IUniformSpacingLayoutLineFactory)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      return Reset();
	}

	void FinalRelease()
	{
	}

   CogoObjectID m_AlignmentID;
   PierIDType m_StartPierID;
   PierIDType m_EndPierID;
   PierIDType m_PierIDInc;
   Float64 m_StartOffset;
   Float64 m_EndOffset;
   CComPtr<IDblArray> m_StartSpacing;
   CComPtr<IDblArray> m_EndSpacing;
   LineIDType m_LayoutLineID; // ID of first layout line
   LineIDType m_LayoutLineIDInc; // Layout line ID increment

public:
   STDMETHOD(Create)(IBridgeGeometry* pBridge,IPathCollection* pPaths);
   STDMETHOD(Reset)();

   STDMETHOD(get_AlignmentID)(CogoObjectID* ID);
   STDMETHOD(put_AlignmentID)(CogoObjectID ID);
   STDMETHOD(get_StartPierID)(PierIDType* pVal);
   STDMETHOD(put_StartPierID)(PierIDType newVal);
   STDMETHOD(get_EndPierID)(PierIDType* pVal);
   STDMETHOD(put_EndPierID)(PierIDType newVal);
   STDMETHOD(get_PierIDInc)(PierIDType* pVal);
   STDMETHOD(put_PierIDInc)(PierIDType newVal);
   STDMETHOD(get_StartSpacingOffset)(Float64* pVal);
   STDMETHOD(put_StartSpacingOffset)(Float64 newVal);
   STDMETHOD(get_EndSpacingOffset)(Float64* pVal);
   STDMETHOD(put_EndSpacingOffset)(Float64 newVal);
   STDMETHOD(get_StartSpacing)(IDblArray** pVal);
   STDMETHOD(put_StartSpacing)(IDblArray* newVal);
   STDMETHOD(get_EndSpacing)(IDblArray** pVal);
   STDMETHOD(put_EndSpacing)(IDblArray* newVal);
   STDMETHOD(put_LayoutLineID)(LineIDType ID);
   STDMETHOD(get_LayoutLineID)(LineIDType* ID);
   STDMETHOD(put_LayoutLineIDInc)(LineIDType inc);
   STDMETHOD(get_LayoutLineIDInc)(LineIDType* inc);

};

OBJECT_ENTRY_AUTO(__uuidof(UniformSpacingLayoutLineFactory), CUniformSpacingLayoutLineFactory)
