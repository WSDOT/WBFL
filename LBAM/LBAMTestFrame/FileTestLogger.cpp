// FileTestLogger.cpp : Implementation of CFileTestLogger
#include "stdafx.h"
#include "LBAMTestFrame.h"
#include "FileTestLogger.h"
#include "LBAMUtils.h"
#include "LBAMTestFrame.hh"

/////////////////////////////////////////////////////////////////////////////
// CFileTestLogger

STDMETHODIMP CFileTestLogger::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFileTestLogger
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CFileTestLogger::get_FileName(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_FileName.Copy();

	return S_OK;
}


STDMETHODIMP CFileTestLogger::Open(BSTR FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

   if (m_Stream.is_open())
      return E_FAIL;

   _bstr_t fn(FileName);
   try
   {
	   m_Stream.open((char*)fn);
      m_FileName = FileName;
      m_TotalTests=0;
      m_FailedTests=0;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMTester);
   }

	return S_OK;
}

STDMETHODIMP CFileTestLogger::Close()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   m_Stream<<std::endl;
   m_Stream<< "   ****  Tests Completed *****" << std::endl;
   m_Stream<< "  Total Number of tests:  "<< m_TotalTests<<std::endl;
   m_Stream<< "  Number of Passed tests: "<< m_TotalTests-m_FailedTests<<std::endl;
   m_Stream<< "  Number of Failed tests: "<< m_FailedTests<<std::endl;
   if (m_FailedTests>0)
   {
      m_Stream<<std::endl<< " **** Some Tests Failed ****"<<"\a";
   }

	m_Stream.close();

	return S_OK;
}

STDMETHODIMP CFileTestLogger::get_TotalTests(/*[out, retval]*/ long *pVal)
{
   *pVal = m_TotalTests;
   return S_OK;
}

STDMETHODIMP CFileTestLogger::get_TotalFails(/*[out, retval]*/ long *pVal)
{
   *pVal = m_FailedTests;
   return S_OK;
}

STDMETHODIMP CFileTestLogger::AddTestEntry(/*[in]*/TestResult result, /*[in]*/BSTR message)
{
   try
   {
      if (!m_Stream.is_open())
         THROW_LBAMTF(FILE_NOT_OPEN);

      m_TotalTests++;

      _bstr_t msg(message);
      if (result == trFailed)
      {
         m_Stream<< "FAILED: "<< (char*)msg << std::endl;
         m_FailedTests++;
      }
      else
      {
         m_Stream<< "PASSED: "<< (char*)msg << std::endl;
      }
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMTester);
   }

   return S_OK;
}

STDMETHODIMP CFileTestLogger::AddDescriptionEntry(/*[in]*/BSTR description)
{
   try
   {
      if (!m_Stream.is_open())
         THROW_LBAMTF(FILE_NOT_OPEN);

      _bstr_t msg(description);
      m_Stream<< "******: "<< (char*)msg << std::endl;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILBAMTester);
   }

   return S_OK;
}

