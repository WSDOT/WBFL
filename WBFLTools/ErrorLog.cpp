///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// ErrorLog.cpp : Implementation of CErrorLog
#include "stdafx.h"
#include "WBFLTools.h"
#include "ErrorLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool is_valid_cookie( DWORD dwCookie, CollectionIndexType size );
int idx_from_cookie( DWORD dwCookie );

/////////////////////////////////////////////////////////////////////////////
// CErrorLog
STDMETHODIMP CErrorLog::Open(BSTR fileName,DWORD* dwCookie)
{
   USES_CONVERSION;

   // User passed us a bad pointer
   if ( dwCookie == 0 )
      return E_POINTER;

   // Try to create a stream... Could fail in one of two ways.  Failed allocation could throw
   // and bad_alloc exception or return NULL.
   boost::shared_ptr<std::_tofstream> pofile;
   try
   {
	   pofile = boost::shared_ptr<std::_tofstream>( new std::_tofstream(OLE2T(fileName)) );
   }
   catch ( ... )
   {
      return E_OUTOFMEMORY;
   }
   if ( pofile.get() == 0 )
   {
      return E_OUTOFMEMORY;
   }

   // Do we have a good stream?
   if ( !(*pofile) )
      return LOGFILE_E_CANTOPEN;

   // Turn exceptions on for the stream
   pofile->exceptions( std::ios_base::badbit | std::ios_base::failbit | std::ios_base::eofbit );

   // Set buffering off for stream so we get all of our data
   pofile->setf(std::ios_base::unitbuf);

   // Save the stream for future reference
   m_LogFiles.push_back( pofile );

   // Get a cookie
   // This have to come after push_back. Cookie must be > 0.
   *dwCookie = (DWORD)m_LogFiles.size();

   // Write a little preamble
   try
   {
      *pofile << "Log opened" << std::endl;
      *pofile << std::endl;
   }
   catch (...)
   {
      return LOGFILE_E_BADWRITE;
   }

   return S_OK;
}

STDMETHODIMP CErrorLog::LogMessage(DWORD dwCookie,BSTR msg)
{
   USES_CONVERSION;

   // Is the cookie valid?
   if ( !is_valid_cookie( dwCookie, m_LogFiles.size() ) )
      return LOGFILE_E_NOLOGFILE;

   boost::shared_ptr<std::_tofstream>& pofile = m_LogFiles[ idx_from_cookie(dwCookie) ];

   try
   {
      *pofile << OLE2T(msg) << std::endl;
   }
   catch(...)
   {
      return LOGFILE_E_BADWRITE;
   }

   return S_OK;
}

STDMETHODIMP CErrorLog::Close(DWORD dwCookie)
{
   // Is the cookie valid?
   if ( !is_valid_cookie( dwCookie, m_LogFiles.size() ) )
      return LOGFILE_E_NOLOGFILE;

   boost::shared_ptr<std::_tofstream>& pofile = m_LogFiles[ idx_from_cookie(dwCookie) ];

   // Write a little postscript
   try
   {
      *pofile << std::endl;
      *pofile << "Log closed" << std::endl;
   }
   catch(...)
   {
      return LOGFILE_E_BADWRITE;
   }

   pofile->close();

   return S_OK;
}

bool is_valid_cookie( DWORD dwCookie, CollectionIndexType size )
{
   return ( dwCookie > (DWORD)size ) ? false : true;
}

int idx_from_cookie( DWORD dwCookie )
{
   return dwCookie - 1;
}
