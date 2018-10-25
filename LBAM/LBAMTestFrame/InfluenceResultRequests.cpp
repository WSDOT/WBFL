// InfluenceResultRequests.cpp : Implementation of CInfluenceResultRequests
#include "stdafx.h"
#include "LBAMTestFrame.h"
#include "InfluenceResultRequests.h"

/////////////////////////////////////////////////////////////////////////////
// CInfluenceResultRequests

STDMETHODIMP CInfluenceResultRequests::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IInfluenceResultRequests
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
