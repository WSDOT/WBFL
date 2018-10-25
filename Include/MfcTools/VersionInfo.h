///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_MFCTOOLS_VERSIONINFO_H_
#define INCLUDED_MFCTOOLS_VERSIONINFO_H_
#pragma once

//
#include <MfcTools\MfcToolsExp.h>

class MFCTOOLSCLASS CVersionInfo
{
public:
  struct TRANSLATION
  {
    WORD m_wLangID;   //e.g. 0x0409 LANG_ENGLISH, SUBLANG_ENGLISH_USA
    WORD m_wCodePage; //e.g. 1252 Codepage for Windows:Multilingual
  };

//Constructors / Destructors
  CVersionInfo();
  ~CVersionInfo();

//methods:
  BOOL                          Load(LPCTSTR szFileName);
  VS_FIXEDFILEINFO*             GetFixedFileInfo();
  DWORD                         GetFileFlagsMask();
  DWORD                         GetFileFlags();
  DWORD                         GetOS();
  DWORD                         GetFileType();
  DWORD                         GetFileSubType();
  FILETIME                      GetCreationTime();
  unsigned __int64              GetFileVersion();
  unsigned __int64              GetProductVersion();
  CString                       GetValue(const CString& sKeyName);
  CString                       GetComments();
  CString                       GetCompanyName();
  CString                       GetFileDescription();
  CString                       GetFileVersionAsString();
  CString                       GetInternalName();
  CString                       GetLegalCopyright();
  CString                       GetLegalTrademarks();
  CString                       GetOriginalFilename();
  CString                       GetPrivateBuild();
  CString                       GetProductName();
  CString                       GetProductVersionAsString();
  CString                       GetSpecialBuild();
  int                           GetNumberOfTranslations();
  TRANSLATION*                  GetTranslation(int nIndex);
  void                          SetTranslation(int nIndex);
  
protected:
//Methods
  void Unload();

//Data
  WORD                m_wLangID;       //The current language ID of the resource
  WORD                m_wCharset;      //The current Character set ID of the resource
  BYTE* m_VerData;       //Pointer to the version info blob
  TRANSLATION*        m_pTranslations; //Pointer to the "\\VarFileInfo\\Translation" version info
  int                 m_nTranslations; //The number of translated version infos in the resource
  VS_FIXEDFILEINFO*   m_pffi;          //Pointer to the fixed size version info data
};

#endif //INCLUDED_MFCTOOLS_VERSIONINFO_H_
