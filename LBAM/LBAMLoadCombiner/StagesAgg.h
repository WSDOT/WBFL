///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2019  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// StagesAgg.h : Declaration of the CStagesAgg

#ifndef __StageSAGG_H_
#define __StageSAGG_H_

#include "resource.h"       // main symbols
#include "WBFLLBAM.h"

/////////////////////////////////////////////////////////////////////////////
// CStagesAgg
class ATL_NO_VTABLE CStagesAgg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public IStages
{
public:

	CStagesAgg()
	{
	}

	~CStagesAgg()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStagesAgg)
	COM_INTERFACE_ENTRY(IStages)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStagesAgg)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStagesAgg
public:
// IStages
   STDMETHOD(get_Item)(/*[in]*/StageIndexType index, /*[out,retval]*/ IStage* *pVal) override;
   STDMETHOD(get__NewEnum)(/*[out,retval]*/ IUnknown** retval) override;  
   STDMETHOD(get_Count)(/*[out,retval]*/ StageIndexType *pVal) override;
   STDMETHOD(get__EnumElements)(/*[out,retval]*/ IEnumStage* *pVal) override;
   STDMETHOD(Add)(/*[in]*/IStage*) override;
   STDMETHOD(RemoveByName)(/*[in]*/BSTR name) override;
   STDMETHOD(RemoveByIndex)(/*[in]*/StageIndexType index) override;
   STDMETHOD(Clone)(/*[out,retval]*/IStages**) override;
   STDMETHOD(Clear)() override;

   STDMETHOD(Insert)(/*[in]*/StageIndexType relPosition, /*[in]*/IStage* member) override;
   STDMETHOD(MoveTo)(/*[in]*/ StageIndexType fromPosition, /*[in]*/ StageIndexType toPosition) override;
   STDMETHOD(Reverse)() override;
   STDMETHOD(FindIndex)(/*[in]*/BSTR name, /*[out,retval]*/StageIndexType* index) override;

   // internal implementation
   CComPtr<IStages> m_Stages;
};

#endif //__StagesAgg_H_
