///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <System\IStructuredSave.h>
#include <System\XStructuredSave.h>
#include <memory>

struct IStream;

namespace WBFL
{
   namespace System
   {
      class StructuredSaveXml_Impl;

      /// This class implements the IStructuredSave interface for xml files.
      /// Write to xml files using the IStructuredSave interface.
      class SYSCLASS StructuredSaveXml : public IStructuredSave
      {
      public:
         StructuredSaveXml();
         StructuredSaveXml(const StructuredSaveXml&) = delete;
         virtual ~StructuredSaveXml();

         StructuredSaveXml& operator=(const StructuredSaveXml&) = delete;

         /// Initializes the structured save object before writing a stream.
         /// Call this method before calling any other method of this class.
         void BeginSave(IStream* pis);

         /// Call this method after you are done with your structured save
         void EndSave();

         /// Mark the Beginning of a structured data chunk. This call must be always
         /// balanced by a corresponding call to EndUnit. An optional version number
         /// may be used to tag major units.
         /// Version 0.0 means no version was attached.
         virtual void BeginUnit(LPCTSTR name, Float64 version=0.0) override;

         /// Mark the end of a structured data chunk that was started by a call to 
         /// BeginUnit.
         virtual void EndUnit() override;

         /// Get the version number of the current unit
         virtual Float64 GetVersion() override;

         /// Get the version number of the unit that is the parent to this unit
         virtual Float64 GetParentVersion();

         /// Get the name of the unit that is the parent to this unit
         virtual std::_tstring GetParentUnit();

         /// Get the version number of the top-most unit
         virtual Float64 GetTopVersion() override;

         /// Write a string property
         virtual void Property(LPCTSTR name, LPCTSTR value) override;

         /// Write a real number property
         virtual void Property(LPCTSTR name, Float64 value) override;

         /// Write an integral property
         virtual void Property(LPCTSTR name, Int16 value) override;

         /// Write an unsigned integral property
         virtual void Property(LPCTSTR name, Uint16 value) override;

         /// Write an integral property
         virtual void Property(LPCTSTR name, Int32 value) override;

         /// Write an unsigned integral property
         virtual void Property(LPCTSTR name, Uint32 value) override;

         /// Write an integral property
         virtual void Property(LPCTSTR name, Int64 value) override;

         /// Write an unsigned integral property
         virtual void Property(LPCTSTR name, Uint64 value) override;

         /// Write an unsigned integral property
         virtual void Property(LPCTSTR name, LONG value) override;

         /// Write an unsigned integral property
         virtual void Property(LPCTSTR name, ULONG value) override;

         /// Write a bool property
         virtual void Property(LPCTSTR name, bool value) override;

         virtual void PutUnit(LPCTSTR xml);

      private:
         std::unique_ptr<StructuredSaveXml_Impl> m_pImp;

      public:
      #if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST
      };
   };
};
