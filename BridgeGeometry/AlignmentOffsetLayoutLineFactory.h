// AlignmentOffsetLayoutLineFactory.h : Declaration of the CAlignmentOffsetLayoutLineFactory

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CAlignmentOffsetLayoutLineFactory
//
// Creates Layout Lines that are offset from and parallel to the alignment

class ATL_NO_VTABLE CAlignmentOffsetLayoutLineFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAlignmentOffsetLayoutLineFactory, &CLSID_AlignmentOffsetLayoutLineFactory>,
	public IAlignmentOffsetLayoutLineFactory
{
public:
	CAlignmentOffsetLayoutLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ALIGNMENTOFFSETLAYOUTLINEFACTORY)

BEGIN_COM_MAP(CAlignmentOffsetLayoutLineFactory)
	COM_INTERFACE_ENTRY(ILayoutLineFactory)
	COM_INTERFACE_ENTRY(IAlignmentOffsetLayoutLineFactory)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      return Reset();
	}

	void FinalRelease()
	{
	}

   LineIDType m_ID;             // ID of the first layout line
   LineIDType m_IDInc;          // Layout Line ID increment
   LineIDType m_nLayoutLines;   // Number of layout lines to generate

   Float64 m_Offset;            // Offset of the first layout line from the alignment (Positive is left of alignment)
   Float64 m_OffsetInc;         // Amount by which to increment the offset for each subsequent layout line (Positive puts next line to the left of the previous)

   CogoObjectID m_AlignmentID; // ID of the alignment that the layout lines are offset from

public:
   STDMETHOD(Create)(IBridgeGeometry* pBridge,IPathCollection* pPaths);
   STDMETHOD(Reset)();

   STDMETHOD(put_LayoutLineID)(LineIDType ID);
   STDMETHOD(get_LayoutLineID)(LineIDType* ID);
   STDMETHOD(put_LayoutLineIDInc)(LineIDType inc);
   STDMETHOD(get_LayoutLineIDInc)(LineIDType* inc);
   STDMETHOD(put_LayoutLineCount)(LineIDType nLayoutLines);
   STDMETHOD(get_LayoutLineCount)(LineIDType* nLayoutLines);
   STDMETHOD(get_Offset)(Float64* offset);
   STDMETHOD(put_Offset)(Float64 offset);
   STDMETHOD(get_OffsetIncrement)(Float64* inc);
   STDMETHOD(put_OffsetIncrement)(Float64 inc);
   STDMETHOD(get_AlignmentID)(CogoObjectID* ID);
   STDMETHOD(put_AlignmentID)(CogoObjectID ID);
};

OBJECT_ENTRY_AUTO(__uuidof(AlignmentOffsetLayoutLineFactory), CAlignmentOffsetLayoutLineFactory)
