///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// CrackedSectionSolution.cpp : Implementation of CCrackedSectionSolution
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "CrackedSectionSolution.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCrackedSectionSolution
HRESULT CCrackedSectionSolution::FinalConstruct()
{
   return S_OK;
}

void CCrackedSectionSolution::FinalRelease()
{
}


STDMETHODIMP CCrackedSectionSolution::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICrackedSectionSolution,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// ICrackedSectionSolution
STDMETHODIMP CCrackedSectionSolution::InitSolution(IPoint2d* pntCG,IUnkArray* slices)
{
   m_pntCG = pntCG;
   m_Slices = slices;

   return S_OK;
}

STDMETHODIMP CCrackedSectionSolution::get_CG(IPoint2d** pntCG)
{
   CHECK_RETOBJ(pntCG);
   (*pntCG) = m_pntCG;
   if ( *pntCG )
      (*pntCG)->AddRef();

   return S_OK;
}

STDMETHODIMP CCrackedSectionSolution::get_SliceCount(CollectionIndexType* nSlices)
{
   return m_Slices->get_Count(nSlices);
}

STDMETHODIMP CCrackedSectionSolution::get_Slice(CollectionIndexType sliceIdx,ICrackedSectionSlice** pSlice)
{
   CollectionIndexType nSlices;
   m_Slices->get_Count(&nSlices);
   if ( sliceIdx < 0 || nSlices <= sliceIdx )
      return E_INVALIDARG;

   CComPtr<IUnknown> punk;
   m_Slices->get_Item(sliceIdx,&punk);
   punk.QueryInterface(pSlice);
   return S_OK;
}

STDMETHODIMP CCrackedSectionSolution::get_ElasticProperties(IElasticProperties** ppProps)
{
   CHECK_RETOBJ(ppProps);

   CComPtr<ICompositeSectionEx> composite_section;
   composite_section.CoCreateInstance(CLSID_CompositeSectionEx);

   // add each slice into a composite section object
   CollectionIndexType nSlices;
   get_SliceCount(&nSlices);
   for ( CollectionIndexType sliceIdx = 0; sliceIdx < nSlices; sliceIdx++ )
   {
      CComPtr<ICrackedSectionSlice> slice;
      get_Slice(sliceIdx,&slice);

      CComPtr<IShape> shape;
      slice->get_Shape(&shape);

      Float64 Efg, Ebg;
      slice->get_Efg(&Efg);
      slice->get_Ebg(&Ebg);

      if ( !IsZero(Efg) )
      {
         // only add slices that aren't cracked
         composite_section->AddSection(shape,Efg,1,0.0,0.0,VARIANT_TRUE);

         if ( !IsZero(Ebg) )
         {
            // add the void
            composite_section->AddSection(shape,0.0,0.0,Ebg,1,VARIANT_TRUE);
         }
      }
   }

   // get the elastic properties
   CComQIPtr<ISection> section(composite_section);
   return section->get_ElasticProperties(ppProps);
}
