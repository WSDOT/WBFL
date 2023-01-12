///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2023  Washington State Department of Transportation
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


#include "stdafx.h"
#include "StagesAgg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSegmentItem

STDMETHODIMP CStagesAgg::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ISegmentItem
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CStagesAgg::get_Item(/*[in]*/StageIndexType index, /*[out,retval]*/ IStage* *pVal)
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->get_Item( index, pVal);
}

STDMETHODIMP CStagesAgg::get__NewEnum(/*[out,retval]*/ IUnknown** retval)  
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->get__NewEnum(retval);
}

STDMETHODIMP CStagesAgg::get_Count(/*[out,retval]*/ StageIndexType *pVal)
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->get_Count(pVal);
}

STDMETHODIMP CStagesAgg::get__EnumElements(/*[out,retval]*/ IEnumStage* *pVal)
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->get__EnumElements(pVal);
}

STDMETHODIMP CStagesAgg::Add(/*[in]*/IStage* Stage)
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->Add(Stage);
}

STDMETHODIMP CStagesAgg::RemoveByName(/*[in]*/BSTR name)
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->RemoveByName(name);
}

STDMETHODIMP CStagesAgg::RemoveByIndex(/*[in]*/StageIndexType index)
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->RemoveByIndex(index);
}

STDMETHODIMP CStagesAgg::Clone(/*[out,retval]*/IStages** Stages)
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->Clone(Stages);
}

STDMETHODIMP CStagesAgg::Clear()
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->Clear();
}

STDMETHODIMP CStagesAgg::Insert(/*[in]*/StageIndexType relPosition, /*[in]*/IStage* member)
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->Insert(relPosition, member);
}

STDMETHODIMP CStagesAgg::MoveTo(/*[in]*/ StageIndexType fromPosition, /*[in]*/ StageIndexType toPosition)
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->MoveTo(fromPosition, toPosition);
}

STDMETHODIMP CStagesAgg::Reverse()
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->Reverse();
}

STDMETHODIMP CStagesAgg::FindIndex(/*[in]*/BSTR name, /*[out,retval]*/StageIndexType* index)
{
   ATLASSERT(m_Stages!=nullptr);
   return m_Stages->FindIndex(name, index);
}
