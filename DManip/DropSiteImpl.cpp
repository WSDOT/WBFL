///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#include "pch.h"
#include <DManip/DropSiteImpl.h>

using namespace WBFL::DManip;

DROPEFFECT DropSite::CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,const WBFL::Geometry::Point2d& point)
{
   return DROPEFFECT_NONE;
}

void DropSite::OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect, const WBFL::Geometry::Point2d& point)
{
   // Do nothing
}

void DropSite::SetDisplayObject(std::shared_ptr<iDisplayObject> pDO)
{
   m_pDispObj = pDO;
}

std::shared_ptr<iDisplayObject> DropSite::GetDisplayObject()
{
   return m_pDispObj;
}
