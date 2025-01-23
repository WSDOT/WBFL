///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2025  Washington State Department of Transportation
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

// LogFile.cpp : Implementation of CLogFile
#include "stdafx.h"
#include "WBFLTools.h"
#include "LogFile.h"
#include <System\Time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogFile

STDMETHODIMP CLogFile::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILogFile
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// ILogFile
//
STDMETHODIMP CLogFile::Open(LPCTSTR name, DWORD* pdwCookie)
{
   // User passed us a bad pointer
   if (pdwCookie == 0)
      return E_POINTER;

   // Try to create a stream... Could fail in one of two ways.  Failed allocation could throw
   // and bad_alloc exception or return nullptr.
   std::shared_ptr<std::_tofstream> pofile;
   try
   {
      pofile = std::make_shared<std::_tofstream>(name);
   }
   catch (...)
   {
      return E_OUTOFMEMORY;
   }
   if (pofile.get() == nullptr)
   {
      return E_OUTOFMEMORY;
   }

   // Do we have a good stream?
   if (!(*pofile))
      return LOGFILE_E_CANTOPEN;

   // Turn exceptions on for the stream
   pofile->exceptions(std::ios_base::badbit | std::ios_base::failbit | std::ios_base::eofbit);

   // Set buffering off for stream so we get all of our data
   pofile->setf(std::ios_base::unitbuf);

   // Save the stream for future reference
   m_LogFiles.push_back(pofile);

   // Get a cookie
   // This have to come after push_back. Cookie must be > 0.
   *pdwCookie = (DWORD)m_LogFiles.size();

   // Write a little preamble
   WBFL::System::Time now;
   now.PrintDate(true);
   try
   {
      *pofile << _T("Log opened ") << now << std::endl;
      *pofile << std::endl;
   }
   catch (...)
   {
      return LOGFILE_E_BADWRITE;
   }

   return S_OK;
}

static bool is_valid_cookie(DWORD dwCookie, size_t size)
{
   return (dwCookie > (DWORD)size) ? false : true;
}

static int idx_from_cookie(DWORD dwCookie)
{
   return dwCookie - 1;
}

STDMETHODIMP CLogFile::put_EndLines(BOOL bEndLines)
{
   m_bEndLines = bEndLines;
   return S_OK;
}

STDMETHODIMP CLogFile::get_EndLines(BOOL* pbEndLines)
{
   *pbEndLines = m_bEndLines;
   return S_OK;
}

STDMETHODIMP CLogFile::LogMessage(DWORD dwCookie, LPCTSTR msg)
{
   // Is the cookie valid?
   if (!is_valid_cookie(dwCookie, m_LogFiles.size()))
      return LOGFILE_E_NOLOGFILE;

   std::shared_ptr<std::_tofstream>& pofile = m_LogFiles[idx_from_cookie(dwCookie)];

   try
   {
      *pofile << msg;
      if (m_bEndLines)
         *pofile << std::endl;
   }
   catch (...)
   {
      return LOGFILE_E_BADWRITE;
   }

   return S_OK;
}

STDMETHODIMP CLogFile::Close(DWORD dwCookie)
{
   // Is the cookie valid?
   if (!is_valid_cookie(dwCookie, m_LogFiles.size()))
      return LOGFILE_E_NOLOGFILE;

   std::shared_ptr<std::_tofstream>& pofile = m_LogFiles[idx_from_cookie(dwCookie)];

   // Write a little postscript
   WBFL::System::Time now;
   now.PrintDate(true);
   try
   {
      *pofile << std::endl;
      *pofile << _T("Log closed ") << now << std::endl;
   }
   catch (...)
   {
      return LOGFILE_E_BADWRITE;
   }

   pofile->close();

   return S_OK;
}
