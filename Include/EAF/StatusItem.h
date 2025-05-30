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

namespace WBFL
{
   namespace EAF
   {
      class StatusItem;

      class StatusCallback
      {
      public:
         virtual WBFL::EAF::StatusSeverityType GetSeverity() const = 0;
         virtual void Execute(std::shared_ptr<StatusItem> pItem) = 0;
      };

      class EAFCLASS StatusItem
      {
      public:
         StatusItem(StatusGroupIDType statusGroupID,StatusCallbackIDType callbackID,LPCTSTR strDescription);
         virtual ~StatusItem();

         // Called by the framework to assign a unique identifier
         // to the status item. Don't call this method
         void SetID(StatusItemIDType id);

         StatusItemIDType GetID() const;
         StatusGroupIDType GetStatusGroupID() const;

         // framework will remove status item after edit if true
         BOOL RemoveAfterEdit();
         void RemoveAfterEdit(BOOL bRemoveAfterEdit);

         LPCTSTR GetDescription() const;
         StatusCallbackIDType GetCallbackID() const;

         virtual bool IsEqual(std::shared_ptr<const StatusItem> pOther) const = 0;

         // More efficient way to compare descriptions than casting results from GetDescription
         // returns -1 (less than), 0 (equal), 1 (greater than)
         int CompareDescriptions(std::shared_ptr<const StatusItem> pOther) const
         {
            return m_strDescription.Compare(pOther->m_strDescription);
         }

      private:
         StatusItemIDType m_ID;
         StatusGroupIDType m_StatusGroupID;
         StatusCallbackIDType m_CallbackID;
         BOOL m_bRemoveAfterEdit;
         CString m_strDescription;
      };

      class EAFCLASS DefaultStatusItem : public StatusItem
      {
      public:
         DefaultStatusItem(StatusGroupIDType statusGroupID,StatusCallbackIDType callbackID,LPCTSTR strDescription) :
            StatusItem(statusGroupID,callbackID,strDescription) {}

         virtual ~DefaultStatusItem() {}

         bool IsEqual(std::shared_ptr<const StatusItem> pOther) const override { return false; }
      };

      class EAFCLASS StatusItemCallback : public StatusCallback
      {
      public:
         StatusItemCallback(WBFL::EAF::StatusSeverityType severity,LPCTSTR lpszDocSetName=nullptr,UINT helpID=0);
         WBFL::EAF::StatusSeverityType GetSeverity() const override;
         void Execute(std::shared_ptr<StatusItem> pItem) override;

      private:
         WBFL::EAF::StatusSeverityType m_Severity;
         CString m_strDocSetName;
         UINT m_HelpID;
      };
   };
};
