///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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
#include <EAF\EAFApp.h>
#include <EAF\EAFPluginManager.h>
#include <EAF\EAFDocumentPlugin.h>
#include <WBFLCore.h> // IStructuredSave, IStructuredLoad, et. al.
#include <vector>

// Plugin manager for CEAFDocument plugins

class EAFCLASS CEAFDocPluginManager : public CEAFPluginManager<IEAFDocumentPlugin,CEAFDocument>
{
public:
   CEAFDocPluginManager();

   // Sets/Gets the SaveMissingPluginDataFlag
   // When reading a document file, if it contains data from a plugin that is not
   // currently installed, the data for that plugin is saved in a temporary cache.
   // If this flag is set, the data for the missing plugin is saved in the file,
   // otherwise the data is not saved and it is lost forever.
   void SetSaveMissingPluginDataFlag(BOOL bSaveDataForMissingPlugins = TRUE);
   BOOL GetSaveMissingPluginDataFlag();

   HRESULT SavePluginData(IStructuredSave* pStrSave);
   HRESULT LoadPluginData(IStructuredLoad* pStrLoad);

private:
   std::vector<std::_tstring> m_MissingPluginData; // holds the entire unit data block
                                                 // for plugin data that is in the file, but
                                                 // the plugin wasn't created

   BOOL m_bSaveMissingPluginData;
};
