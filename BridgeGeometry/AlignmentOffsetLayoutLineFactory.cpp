// AlignmentOffsetLayoutLineFactory.cpp : Implementation of CAlignmentOffsetLayoutLineFactory

#include "stdafx.h"
#include "AlignmentOffsetLayoutLineFactory.h"


// CAlignmentOffsetLayoutLineFactory

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::Create(IBridgeGeometry* pBridge,IPathCollection* pPaths)
{
   CHECK_IN(pBridge);
   CHECK_IN(pPaths);

   if ( m_ID == INVALID_INDEX )
   {
      ATLASSERT(false);
      return E_INVALIDARG;
   }

   CComPtr<IAlignment> alignment;
   if ( FAILED(pBridge->get_Alignment(m_AlignmentID,&alignment)) )
      return Error(IDS_E_ID,IID_IAlignmentOffsetLayoutLineFactory,BRIDGEGEOMETRY_E_ID);

   for ( LineIDType idx = 0; idx < m_nLayoutLines; idx++ )
   {
      LineIDType id = m_ID + idx*m_IDInc;
      Float64 offset = m_Offset + idx*m_OffsetInc;

      CComPtr<IPath> path;
      HRESULT hr = alignment->CreateParallelPath(-offset,&path); // neg because offsets are positive to the right for the COGO engine
      if ( FAILED(hr) )
         return hr;

      hr = pPaths->AddEx((CogoObjectID)id,path);
      if ( FAILED(hr) )
         return hr;
   }

   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::Reset()
{
   m_ID           = INVALID_INDEX;
   m_IDInc        = 1;
   m_nLayoutLines = 1;
   m_Offset       = 0;
   m_OffsetInc    = 0;
   m_AlignmentID  = INVALID_INDEX;
	return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_LayoutLineID(LineIDType ID)
{
   m_ID = ID;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_LayoutLineID(LineIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_ID;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_LayoutLineIDInc(LineIDType inc)
{
   m_IDInc = inc;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_LayoutLineIDInc(LineIDType* inc)
{
   CHECK_RETVAL(inc);
   *inc = m_IDInc;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_LayoutLineCount(LineIDType nLayoutLines)
{
   m_nLayoutLines = nLayoutLines;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_LayoutLineCount(LineIDType* nLayoutLines)
{
   CHECK_RETVAL(nLayoutLines);
   *nLayoutLines = m_nLayoutLines;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_Offset(Float64* offset)
{
   CHECK_RETVAL(offset);
   *offset = m_Offset;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_Offset(Float64 offset)
{
   m_Offset = offset;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_OffsetIncrement(Float64* inc)
{
   CHECK_RETVAL(inc);
   *inc = m_OffsetInc;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_OffsetIncrement(Float64 inc)
{
   m_OffsetInc = inc;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_AlignmentID(CogoObjectID* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_AlignmentID;
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_AlignmentID(CogoObjectID ID)
{
   m_AlignmentID = ID;
   return S_OK;
}
