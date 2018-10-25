// SectionResultRequests.cpp : Implementation of CSectionResultRequests
#include "stdafx.h"
#include "LBAMTestFrame.h"
#include "SectionResultRequests.h"

/////////////////////////////////////////////////////////////////////////////
// CSectionResultRequests

STDMETHODIMP CSectionResultRequests::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISectionResultRequests
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
