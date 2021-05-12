///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

#pragma once

#include <EAF\EAFExp.h>



class EAFCLASS CEAFCommandLineInfo : public CCommandLineInfo
{
public:
   CEAFCommandLineInfo();
   virtual ~CEAFCommandLineInfo();

   UINT m_nParams;
   BOOL  m_bUsageMessage; // set to TRUE if a usage message is required (/?)
   BOOL  m_bCommandLineMode; // set this to TRUE if this is a batch run
   BOOL  m_bError; // set this to TRUE if there is a problem with the command line and the application
                   // needs to display the command line usage message and exit
   BOOL m_bTargetApp;

   virtual void ParseParam(LPCTSTR lpszParam,BOOL bFlag,BOOL bLast);

   void SetErrorInfo(LPCTSTR strError);

   virtual CString GetUsageMessage();
   virtual CString GetErrorMessage();
   virtual CString GetTargetApp();

   CEAFCommandLineInfo& operator=(const CEAFCommandLineInfo& other);

protected:
   // Prevent accidental copying and assignment
   CEAFCommandLineInfo(const CEAFCommandLineInfo&) = delete;

   CString m_strErrorMsg;
   CString m_strTargetApp; // name of EAF Application Plugin that is to process the command line options
};
