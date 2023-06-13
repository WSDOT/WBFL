///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// Girder.h : Declaration of the CGirder

#pragma once
#include "resource.h"       // main symbols

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CGirder

class ATL_NO_VTABLE CGirderLine :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGirderLine, &CLSID_GirderLine>,
	public IGirderLine
{
public:
	CGirderLine()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GIRDERLINE)

DECLARE_NOT_AGGREGATABLE(CGirderLine)

BEGIN_COM_MAP(CGirderLine)
	COM_INTERFACE_ENTRY(IGirderLine)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      return S_OK;
	}

	void FinalRelease()
	{
	}

   void SetGirderLine(std::shared_ptr<WBFL::COGO::GirderLine> GirderLine) { m_GirderLine = GirderLine; }
   std::shared_ptr<WBFL::COGO::GirderLine> GetGirderLine(){ return m_GirderLine; }

public:
   STDMETHOD(get_ID)(IDType* pVal) override;
   STDMETHOD(get_StartPier)(IPierLine** pVal) override;
   STDMETHOD(get_EndPier)( IPierLine** pVal) override;
   STDMETHOD(get_GirderLength)(Float64* pLength) override;
   STDMETHOD(get_SpanLength)(Float64* pLength) override;
   STDMETHOD(get_LayoutLength)(Float64* pLength) override;
   STDMETHOD(get_PierPoint)(EndType endType, IPoint2d** ppPoint) override;
   STDMETHOD(get_BearingPoint)(EndType endType, IPoint2d** ppPoint) override;
   STDMETHOD(get_EndPoint)(EndType endType, IPoint2d** ppPoint) override;
   STDMETHOD(GetEndPoints)(IPoint2d** pntPier1, IPoint2d** pntEnd1, IPoint2d** pntBrg1, IPoint2d** pntBrg2, IPoint2d** pntEnd2, IPoint2d** pntPier2) override;
   STDMETHOD(get_Path)(IPath** pVal) override;
   STDMETHOD(get_Direction)(IDirection** ppDirection) override;
   STDMETHOD(get_BearingOffset)(EndType endType, Float64* pBrgOffset) override;
   STDMETHOD(get_EndDistance)(EndType endType, Float64* pEndDist) override;


private:
   std::shared_ptr<WBFL::COGO::GirderLine> m_GirderLine;
};
