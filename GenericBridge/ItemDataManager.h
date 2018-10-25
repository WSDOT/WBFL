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

#ifndef INCLUDED_ITEMDATAMANAGER_H_
#define INCLUDED_ITEMDATAMANAGER_H_

#include <map>
#include <string>

/////////////////////////////////////////////////////////////////
// Helper class for managing item data
class CItemDataManager
{
public:
   HRESULT AddItemData(BSTR name,IUnknown* data);
   HRESULT GetItemData(BSTR name,IUnknown** data);
   HRESULT RemoveItemData(BSTR name);
   HRESULT GetItemDataCount(CollectionIndexType* count);

private:

   typedef std::map<std::_tstring,CComPtr<IUnknown> > ItemDataCollection;
   ItemDataCollection m_Items;
};

#endif // INCLUDED_ITEMDATAMANAGER_H_