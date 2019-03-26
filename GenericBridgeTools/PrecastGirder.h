///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2019  Washington State Department of Transportation
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

// PrecastGirder.h : Declaration of the CPrecastGirder

#ifndef __PRECASTGIRDER_H_
#define __PRECASTGIRDER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrecastGirder
class ATL_NO_VTABLE CPrecastGirder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPrecastGirder, &CLSID_PrecastGirder>,
	public ISupportErrorInfo,
	public IPrecastGirder,
   public IObjectSafetyImpl<CPrecastGirder,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CPrecastGirder()
	{
      m_pSegment = nullptr;
      m_UpdateLengths = true;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PRECASTGIRDER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPrecastGirder)
	COM_INTERFACE_ENTRY(IPrecastGirder)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   ISuperstructureMemberSegment* m_pSegment; // weak reference to the superstructure member segment for this girder

   SpanIndexType m_SpanIdx;
   GirderIndexType m_GirderIdx;

   CComPtr<IStrandModel> m_StrandModel;
   CComPtr<IRebarLayout> m_RebarLayout;
   CComPtr<IRebarLayout> m_ClosureJointRebarLayout;

   // caching of span and girder lengths
   bool m_UpdateLengths;
   void DoUpdateLengths();

   struct Lengths
   {
      Float64 dbSpanLength;           // cl-brg to cl-brg
      Float64 dbGirderLength;         // end to end
      Float64 dbLeftEndDistance;      // cl-brg to end (left end of girder)
      Float64 dbRightEndDistance;     // cl-brg to end (right end of girder)
      Float64 dbLeftBearingOffset;    // cl-pier to cl-brg (left end of girder)
      Float64 dbRightBearingOffset;   // cl-pier to cl-brg (right end of girder)
   } m_Lengths;
  
// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPrecastGirder
public:
   STDMETHOD(Initialize)(ISuperstructureMemberSegment* segment) override;

   STDMETHOD(get_SpanLength)(/*[out,retval]*/ Float64* length) override;
   STDMETHOD(get_GirderLength)(/*[out,retval]*/ Float64* length) override;
   STDMETHOD(get_LeftEndDistance)(/*[out,retval]*/ Float64* size) override;
   STDMETHOD(get_RightEndDistance)(/*[out,retval]*/ Float64* size) override;
   STDMETHOD(get_LeftBearingOffset)(/*[out,retval]*/ Float64* offset) override;
   STDMETHOD(get_RightBearingOffset)(/*[out,retval]*/ Float64* offset) override;
   STDMETHOD(GetEndPoints)(/*[out]*/IPoint2d** pntPier1,/*[out]*/IPoint2d** pntEnd1,/*[out]*/IPoint2d** pntBrg1,/*[out]*/IPoint2d** pntBrg2,/*[out]*/IPoint2d** pntEnd2,/*[out]*/IPoint2d** pntPier2) override;

   STDMETHOD(get_SuperstructureMemberSegment)(/*[out,retval]*/ISuperstructureMemberSegment** segment) override;
   STDMETHOD(putref_StrandModel)(IStrandModel* pStrandModel);
   STDMETHOD(get_StrandModel)(IStrandModel** ppStrandModel);
   STDMETHOD(get_RebarLayout)(/*[out,retval]*/IRebarLayout** rebarLayout) override;
   STDMETHOD(get_ClosureJointRebarLayout)(/*[out,retval]*/IRebarLayout** rebarLayout) override;
};

#endif //__PRECASTGIRDER_H_
