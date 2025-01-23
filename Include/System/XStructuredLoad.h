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

#pragma once

#include <System\SysExp.h>
#include <System\Exception.h>
#include <crtdbg.h>

#undef THROW_LOAD
#define THROW_LOAD(code,pload) {WBFL::System::XStructuredLoad alzxb_(WBFL::System::XStructuredLoad::code, _T(__FILE__), __LINE__ ); \
                                _ASSERT(false); \
                                 alzxb_.Throw();}

namespace WBFL
{
   namespace System
   {
      /// Exception class for classes implementing the IStructuredLoad interface.
      /// Use this class when throwing out of classes derived from IStructuredLoad
      class SYSCLASS XStructuredLoad : public XBase
      {
      public:
         // Reasons for hucking
         enum Reason {InvalidFileFormat, EndOfFile, BadRead, BadVersion, MemoryError,CantInitializeTheParser, UserDefined, Unspecified};

         XStructuredLoad() = default;
         XStructuredLoad( Reason reason, const std::_tstring& file, Uint32 line);
         virtual ~XStructuredLoad() = default;

         XStructuredLoad& operator=(const XStructuredLoad&) = default;

         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;
         Reason GetReasonCode() const noexcept;

         virtual std::_tstring GetErrorMessage() const override;

         /// Set an extended message containing state data of the loader that crashed
         /// This message will be appended to the message from the base class
         void SetExtendedMessage(LPCTSTR msg);


      private:
         Reason m_Reason{ Unspecified };
         std::_tstring m_ExtendedMessage;
      };
   };
};
