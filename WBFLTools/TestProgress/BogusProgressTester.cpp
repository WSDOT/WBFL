// BogusProgressTester.cpp : Implementation of CBogusProgressTester
#include "stdafx.h"
#include "TestProgress.h"
#include "BogusProgressTester.h"

inline void WaitForSec(int seconds)
{
   CTime start_time = CTime::GetCurrentTime();

   CTimeSpan span;
   long secs=0;
   while(secs <seconds)
   {
      span = CTime::GetCurrentTime() - start_time;
      secs = span.GetTotalSeconds();
   }
}

/////////////////////////////////////////////////////////////////////////////
// CBogusProgressTester

STDMETHODIMP CBogusProgressTester::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProgressMonitor
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CBogusProgressTester::InitializeProgressMonitor(IProgressMonitor* newVal, long cookie)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   m_Pm = newVal;
   m_Cookie = cookie;
   return S_OK;
}

bool CBogusProgressTester::WasCancelled()
{
   VARIANT_BOOL ccl;
   m_Pm->get_WasCancelled(&ccl);
   if (ccl!=VARIANT_FALSE)
   {
      m_Pm->put_Message(m_Cookie, CComBSTR("Testing Cancelled"));
      WaitForSec(2);
      return true;
   }
   else
      return false;
}

// IBogusProgressTester
STDMETHODIMP CBogusProgressTester::RunTest()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   ATLASSERT(m_Pm != NULL);


   m_Pm->put_Message(m_Cookie, CComBSTR("Starting Test"));
   m_Pm->put_GaugeValue(m_Cookie, 0);
   WaitForSec(2);
   m_Pm->put_Message(m_Cookie, CComBSTR("Testing + 2"));
   m_Pm->put_GaugeValue(m_Cookie, 20);
   WaitForSec(2);
   if (WasCancelled())
      return S_OK;
   m_Pm->put_Message(m_Cookie, CComBSTR("Testing + 4"));
   m_Pm->put_GaugeValue(m_Cookie, 40);
   WaitForSec(2);
   if (WasCancelled())
      return S_OK;
   m_Pm->put_Message(m_Cookie, CComBSTR("Testing + 6"));
   m_Pm->put_GaugeValue(m_Cookie, 60);
   WaitForSec(2);
   if (WasCancelled())
      return S_OK;
   m_Pm->put_Message(m_Cookie, CComBSTR("Testing + 8"));
   m_Pm->put_GaugeValue(m_Cookie, 80);
   WaitForSec(2);
   if (WasCancelled())
      return S_OK;
   m_Pm->put_Message(m_Cookie, CComBSTR("Testing Done"));
   m_Pm->put_GaugeValue(m_Cookie, 100);
   WaitForSec(2);

	return S_OK;
}
