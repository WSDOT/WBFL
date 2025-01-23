///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
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

#include <LibraryFw\LibraryEntry.h>
#include <System\SubjectT.h>

/// @brief Dummy library entry for testing purposes.
class TestEntry : public WBFL::Library::LibraryEntry
{
public:
   TestEntry() = default;
   TestEntry(const TestEntry& rOther) = default;
   virtual ~TestEntry() = default;

   TestEntry& operator = (const TestEntry& rOther) = default;

   virtual bool Edit(bool allowEditing,int nPage=0) override {return false;}

   void Notify(int) {}

   virtual bool SaveMe(WBFL::System::IStructuredSave* pSave) override;
   virtual bool LoadMe(WBFL::System::IStructuredLoad* pLoad) override;

   void SetValue(Float64 v);
   Float64 GetValue() const;

private:
   Float64 m_Value = 0;
};
