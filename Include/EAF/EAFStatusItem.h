///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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
#include <string>

class CEAFStatusItem;

interface iStatusCallback
{
   virtual eafTypes::StatusSeverityType GetSeverity() = 0;
   virtual void Execute(CEAFStatusItem* pItem) = 0;
};

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   CEAFStatusItem
   
DESCRIPTION
   Base class for Status Items. Derived classes must implement the IsEqual
   method.
   
COPYRIGHT
   Copyright © 1997-2004
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class EAFCLASS CEAFStatusItem
{
public:
   CEAFStatusItem(StatusGroupIDType statusGroupID,StatusCallbackIDType callbackID,LPCTSTR strDescription);
   virtual ~CEAFStatusItem();

   // Called by the framework to assign a unique identifier
   // to the status item. Don't call this method
   void SetID(StatusItemIDType id);

   StatusItemIDType GetID() const;
   StatusGroupIDType GetStatusGroupID() const;

   // framework will remove status item after edit if true
   bool RemoveAfterEdit();
   void RemoveAfterEdit(bool bRemoveAfterEdit);

   const std::_tstring& GetDescription() const;
   StatusCallbackIDType GetCallbackID() const;

   virtual bool IsEqual(CEAFStatusItem* pOther) = 0;

private:
   StatusItemIDType m_ID;
   StatusGroupIDType m_StatusGroupID;
   StatusCallbackIDType m_CallbackID;
   bool m_bRemoveAfterEdit;
   std::_tstring m_Description;
};
