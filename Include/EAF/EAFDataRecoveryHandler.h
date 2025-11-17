///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

#include <EAF\EAFExp.h>
#include <afxdatarecovery.h>

/// Customizes the CDataRecoveryHandler class so data recovery works with EAFDocumentTemplate objects and provides autosave state information
class EAFCLASS CEAFDataRecoveryHandler : public CDataRecoveryHandler
{
public:
   CEAFDataRecoveryHandler(_In_ DWORD dwRestartManagerSupportFlags, _In_ int nAutosaveInterval);

   /// Overrides the default implementation to keep track if an autosave is in progress
   ///
   /// Clients can call GetDataRecoveryHandler() from the application, cast it to CEAFDataRecoveryHandler
   /// and call IsAutosaving() to see if an autosave is in progress
   virtual BOOL AutosaveDocumentInfo(_In_ CDocument* pDocument, _In_ BOOL bResetModifiedFlag = TRUE) override;

   virtual BOOL ReopenPreviousDocuments() override;

   /// Returns TRUE if an autosave is in progress
   BOOL IsAutosaving();

private:
   BOOL m_bIsAutosaving;
};