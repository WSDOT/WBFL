///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// AlignmentOffsetStrategy.cpp : Implementation of CConstantOverhangStrategy
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "AlignmentOffsetStrategy.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlignmentOffsetStrategy
HRESULT CAlignmentOffsetStrategy::FinalConstruct()
{
   return S_OK;
}

void CAlignmentOffsetStrategy::FinalRelease()
{
}

STDMETHODIMP CAlignmentOffsetStrategy::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAlignmentOffsetStrategy,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////
// IOverhangPathStrategy implementation
STDMETHODIMP CAlignmentOffsetStrategy::get_Path(IPath** path)
{
   CHECK_RETOBJ(path);

   // path is cached...
   if ( m_Path )
   {
      (*path) = m_Path;
      (*path)->AddRef();
      return S_OK;
   }

   // create alignment offset path and cache it
   if ( m_Alignment )
   {
      m_Alignment->CreateParallelPath(m_Offset,&m_Path);
      return get_Path(path);
   }

   return E_FAIL;
}

////////////////////////////////////////////////////////////////////////
// IAlignmentOffsetStrategy implementation
STDMETHODIMP CAlignmentOffsetStrategy::putref_Alignment(IAlignment* alignment)
{
   CHECK_IN(alignment);
   m_Alignment = alignment;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetStrategy::put_Offset(Float64 offset)
{
   m_Offset = offset;
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CAlignmentOffsetStrategy::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);
   load->BeginUnit(CComBSTR("AlignmentOffsetStrategy"));

   CComVariant var;

   if ( m_Alignment )
      m_Alignment.Release();

   load->get_Property(CComBSTR("Alignment"),&var);
   var.punkVal->QueryInterface(&m_Alignment);

   load->get_Property(CComBSTR("Offset"),&var);
   m_Offset = var.dblVal;

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetStrategy::Save(IStructuredSave2* save)
{
   CHECK_IN(save);
   save->BeginUnit(CComBSTR("AlignmentOffsetStrategy"),1.0);
   save->put_Property(CComBSTR("Alignment"),CComVariant(m_Alignment));
   save->put_Property(CComBSTR("Offset"),CComVariant(m_Offset));
   save->EndUnit();
   return S_OK;
}
