///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "ItemDataManager.h"
#include "TxnMgrImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT CItemDataManager::AddItemData(BSTR name,IUnknown* data)
{
   USES_CONVERSION;
   m_Items.insert( std::make_pair(OLE2T(name),data) );
   return S_OK;
}

HRESULT CItemDataManager::GetItemData(BSTR name,IUnknown** data)
{
   CHECK_IN(name);
   CHECK_RETOBJ(data);

   USES_CONVERSION;

   std::_tstring strName(OLE2T(name));
   ItemDataCollection::iterator found( m_Items.find(strName) );

   if ( found != m_Items.end() )
   {
      (*data) = (*found).second;
      (*data)->AddRef();
   }
   else
   {
#pragma Reminder("UPDATE: Need a custom err return value")
      (*data) = NULL;
   }

   return S_OK;
}

HRESULT CItemDataManager::RemoveItemData(BSTR name)
{
   USES_CONVERSION;
   m_Items.erase(OLE2T(name));
   return S_OK;
}

HRESULT CItemDataManager::GetItemDataCount(CollectionIndexType* count)
{
   CHECK_RETVAL(count);

   *count = m_Items.size();
   return S_OK;
}
