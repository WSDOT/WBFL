///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2025  Washington State Department of Transportation
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

#ifndef INCLUDED_WBFLTOOLS_LogContext_H_
#define INCLUDED_WBFLTOOLS_LogContext_H_
#pragma once

#include <WBFLTools\WBFLToolsExp.h>
#include <System\LogContext.h>
#include <atlbase.h>
#include <atlcom.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
interface ILogFile;

// MISCELLANEOUS
//

/// Wrapper class for ILogFile objects
///
/// This implementation provides an easy C++-style interface to a COM ILogFile object.
/// Stream insertion operators are provided for common data types.
class WBFLTOOLSCLASS LogContext : public WBFL::Debug::LogContext
{
public:
   LogContext(
      ILogFile* pLog = nullptr, ///< pointer to the ILogFile implementation to wrap
      DWORD dwCookie = 0 ///< A cookie defining the log stream
   );

   LogContext(const LogContext&) = delete;
   LogContext& operator=(const LogContext&) = delete;

   virtual ~LogContext();

   virtual WBFL::Debug::LogContext& operator<<(const std::_tstring& s) override;
   virtual WBFL::Debug::LogContext& operator<<(LPCTSTR s) override;
   virtual WBFL::Debug::LogContext& operator<<(TCHAR c) override;    
   virtual WBFL::Debug::LogContext& operator<<(DWORD n) override;
   virtual WBFL::Debug::LogContext& operator<<(bool n) override;
   virtual WBFL::Debug::LogContext& operator<<(Int16 n) override;
   virtual WBFL::Debug::LogContext& operator<<(Uint16 n) override;
   virtual WBFL::Debug::LogContext& operator<<(Int32 n) override;
   virtual WBFL::Debug::LogContext& operator<<(Uint32 n) override;
   virtual WBFL::Debug::LogContext& operator<<(Int64 n) override;
   virtual WBFL::Debug::LogContext& operator<<(Uint64 n) override;
   virtual WBFL::Debug::LogContext& operator<<(Float32 n) override;    
   virtual WBFL::Debug::LogContext& operator<<(Float64 n) override;
   virtual WBFL::Debug::LogContext& operator<<(Float80 n) override;
   virtual WBFL::Debug::LogContext& operator<<(void * n) override;
   virtual WBFL::Debug::LogContext& operator<<(const WBFL::System::SectionValue& n) override;

   virtual WBFL::Debug::LogContext& EndLine() override;

   /// Set the log file object and cookie if no set in the constructor
   void SetLog(ILogFile* pLog,DWORD dwCookie);

   /// Get the log file object and cookie
   void GetLog(ILogFile** ppLog,DWORD* pdwCookie);

private:
   CComPtr<ILogFile> m_LogFile;
   DWORD m_dwCookie;
};

#endif // INCLUDED_WBFLTOOLS_LogContext_H_
