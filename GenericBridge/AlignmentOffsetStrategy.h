///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// AlignmentOffsetStrategy.h : Declaration of the CAlignmentOffsetStrategy

#ifndef __ALIGNMENTOFFSETSTRATEGY_H_
#define __ALIGNMENTOFFSETSTRATEGY_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAlignmentOffsetStrategy
class ATL_NO_VTABLE CAlignmentOffsetStrategy : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CAlignmentOffsetStrategy,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CAlignmentOffsetStrategy, &CLSID_AlignmentOffsetStrategy>,
	public ISupportErrorInfo,
   public IAlignmentOffsetStrategy,
   public IStructuredStorage2,
   public IOverhangPathStrategy,
   public IObjectSafetyImpl<CAlignmentOffsetStrategy,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CAlignmentOffsetStrategy()
	{
      m_Offset = 0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

private:
   Float64 m_Offset;
   CComPtr<IAlignment> m_Alignment;
   CComPtr<IPath> m_Path;

public:
DECLARE_REGISTRY_RESOURCEID(IDR_ALIGNMENTOFFSETSTRATEGY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAlignmentOffsetStrategy)
	COM_INTERFACE_ENTRY(IAlignmentOffsetStrategy)
	COM_INTERFACE_ENTRY(IOverhangPathStrategy)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IOverhangPathStrategy
public:
   STDMETHOD(get_Path)(/*[out,retval]*/IPath** path);

// IAlignmentOffsetStrategy
public:
   STDMETHOD(putref_Alignment)(/*[in]*/IAlignment* alignment);
	STDMETHOD(put_Offset)(/*[in]*/Float64 offset);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};

#endif //__ALIGNMENTOFFSETSTRATEGY_H_
