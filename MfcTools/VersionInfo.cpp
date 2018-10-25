///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2018  Washington State Department of Transportation
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
#include <MfcTools\VersionInfo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Automatically pull in the win32 version Library
#pragma comment(lib, "version.lib")


//////////////// Implementation ///////////////////////////////////////////////

CVersionInfo::CVersionInfo() : m_pffi(nullptr),
                               m_wLangID(0),
                               m_wCharset(1252), //Use the ANSI code page as a default
                               m_pTranslations(nullptr),
                               m_nTranslations(0),
                               m_VerData(nullptr)
{
}

CVersionInfo::~CVersionInfo()
{
  Unload();
}

void CVersionInfo::Unload()
{
  m_pffi = nullptr;
  if ( m_VerData != nullptr )
     free( m_VerData );

  m_wLangID = 0;
  m_wCharset = 1252; //Use the ANSI code page as a default
  m_pTranslations = nullptr;
  m_nTranslations = 0;
}

BOOL CVersionInfo::Load(LPCTSTR szFileName)
{
  //Free up any previous memory lying around
  Unload();

  BOOL bSuccess = FALSE;
  DWORD dwHandle = 0;
  CString strFileName(szFileName);
  LPTSTR pszFileName = strFileName.LockBuffer();
  DWORD dwSize = GetFileVersionInfoSize(pszFileName, &dwHandle);
  if (dwSize)
  {
    //Allocate some memory to hold the version info data
    ASSERT(m_VerData == nullptr);
    m_VerData = (BYTE*)malloc(dwSize);
    if (!m_VerData)
    {
      SetLastError(ERROR_OUTOFMEMORY);
      return FALSE;
    }
    if (GetFileVersionInfo(pszFileName, dwHandle, dwSize, m_VerData))
    {
      //Get the fixed size version info data
      UINT nLen = 0;
      if (VerQueryValue(m_VerData, _T("\\"), reinterpret_cast<LPVOID*>(&m_pffi), &nLen))
      {
        //Retrieve the Lang ID and Character set ID
        if (VerQueryValue(m_VerData, _T("\\VarFileInfo\\Translation"), reinterpret_cast<LPVOID*>(&m_pTranslations), &nLen) && (nLen >= sizeof(TRANSLATION))) 
        {
          m_nTranslations = nLen / sizeof(TRANSLATION);
          m_wLangID = m_pTranslations[0].m_wLangID;
          m_wCharset = m_pTranslations[0].m_wCodePage;
        }
        bSuccess = TRUE;
      }
      else
        TRACE(_T("CVersionInfo::Load, Failed to query file size version info for file %s, LastError:%d\n"), szFileName, ::GetLastError());
    }
    else
      TRACE(_T("CVersionInfo::Load, Failed to read in version info for file %s, LastError:%d\n"), szFileName, ::GetLastError());
  }
  else
    TRACE(_T("CVersionInfo::Load, Failed to get version info for file %s, LastError:%d\n"), szFileName, ::GetLastError());

  return bSuccess;
}

VS_FIXEDFILEINFO* CVersionInfo::GetFixedFileInfo()
{
  ASSERT(m_VerData != nullptr); //Must have been loaded successfully
  return m_pffi;
}

DWORD CVersionInfo::GetFileFlagsMask()
{
  ASSERT(m_VerData != nullptr); //Must have been loaded successfully
  return m_pffi->dwFileFlagsMask;
}

DWORD CVersionInfo::GetFileFlags()
{
  ASSERT(m_VerData != nullptr); //Must have been loaded successfully
  return m_pffi->dwFileFlags;
}

DWORD CVersionInfo::GetOS()
{
  ASSERT(m_VerData != nullptr); //Must have been loaded successfully
  return m_pffi->dwFileOS;
}

DWORD CVersionInfo::GetFileType()
{
  ASSERT(m_VerData != nullptr); //Must have been loaded successfully
  return m_pffi->dwFileType;
}

DWORD CVersionInfo::GetFileSubType()
{
  ASSERT(m_VerData != nullptr); //Must have been loaded successfully
  return m_pffi->dwFileSubtype;
}

FILETIME CVersionInfo::GetCreationTime()
{
  ASSERT(m_VerData != nullptr); //Must have been loaded successfully
  FILETIME CreationTime;
  CreationTime.dwHighDateTime = m_pffi->dwFileDateMS; 
  CreationTime.dwLowDateTime = m_pffi->dwFileDateLS; 
  return CreationTime;
}

unsigned __int64 CVersionInfo::GetFileVersion()
{
  ASSERT(m_VerData != nullptr); //Must have been loaded successfully
  unsigned __int64 nFileVersion = 0;
  nFileVersion = m_pffi->dwFileVersionLS;
  nFileVersion += ((static_cast<unsigned __int64>(m_pffi->dwFileVersionMS)) << 32);
  return nFileVersion;
}

unsigned __int64 CVersionInfo::GetProductVersion()
{
  ASSERT(m_VerData != nullptr); //Must have been loaded successfully
  unsigned __int64 nProductVersion = 0;
  nProductVersion = m_pffi->dwProductVersionLS;
  nProductVersion += ((static_cast<unsigned __int64>(m_pffi->dwProductVersionMS)) << 32);
  return nProductVersion;
}

CString CVersionInfo::GetValue(const CString& sKey)
{
  //Validate our parameters
  ASSERT(m_VerData != nullptr);

  //What will be the return value from this function
  CString sVal;

  //Form the string to query with
  CString sQueryValue;
  sQueryValue.Format(_T("\\StringFileInfo\\%04x%04x\\%s"), m_wLangID, m_wCharset, sKey.operator LPCTSTR());

  //Note that the definition for VerQueryValue in the VC 2005 Winver.h header file is incorrectly
  //defined as taking a non-const 2nd parameter, so to avoid this issue, lets get a non const pointer
  //to the "sQueryValue" buffer
  LPTSTR pszQueryValue = sQueryValue.GetBuffer(sQueryValue.GetLength());

  //Do the query
  LPTSTR pVal = nullptr;
  UINT nLen = 0;
  if (VerQueryValue(m_VerData, pszQueryValue, reinterpret_cast<LPVOID*>(&pVal), &nLen)) 
    sVal = pVal;
    
  //Release the non-const buffer now that we are finished with it    
  sQueryValue.ReleaseBuffer();

  return sVal;
}

CString CVersionInfo::GetCompanyName()
{
  return GetValue(_T("CompanyName"));
}

CString CVersionInfo::GetFileDescription()
{
  return GetValue(_T("FileDescription"));
}

CString CVersionInfo::GetFileVersionAsString()
{
  return GetValue(_T("FileVersion"));
}

CString CVersionInfo::GetInternalName()
{
  return GetValue(_T("InternalName"));
}

CString CVersionInfo::GetLegalCopyright()
{
  return GetValue(_T("LegalCopyright"));
}

CString CVersionInfo::GetOriginalFilename()
{
  return GetValue(_T("OriginalFilename"));
}

CString CVersionInfo::GetProductName()
{
  return GetValue(_T("Productname"));
}

CString CVersionInfo::GetProductVersionAsString()
{
  return GetValue(_T("ProductVersion"));
}
  
int CVersionInfo::GetNumberOfTranslations()
{
  return m_nTranslations;
}

CString CVersionInfo::GetComments()
{
  return GetValue(_T("Comments"));
}

CString CVersionInfo::GetLegalTrademarks()
{
  return GetValue(_T("LegalTrademarks"));
}

CString CVersionInfo::GetPrivateBuild()
{
  return GetValue(_T("PrivateBuild"));
}

CString CVersionInfo::GetSpecialBuild()
{
  return GetValue(_T("SpecialBuild"));
}

CVersionInfo::TRANSLATION* CVersionInfo::GetTranslation(int nIndex)
{
  ASSERT(nIndex >= 0 && nIndex < m_nTranslations);
  ASSERT(m_pTranslations);
  return &m_pTranslations[nIndex];
}

void CVersionInfo::SetTranslation(int nIndex)
{
  TRANSLATION* pTranslation = GetTranslation(nIndex);
  m_wLangID = pTranslation->m_wLangID;
  m_wCharset = pTranslation->m_wCodePage;
}
