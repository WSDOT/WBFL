///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
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

// GraphBuilder.cpp: implementation of the CGraphBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Graphing/GraphBuilder.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace WBFL::Graphing;

GraphBuilder::GraphBuilder(LPCTSTR name) : 
   m_strName(name) 
{
};

void GraphBuilder::SetName(LPCTSTR strName)
{
   m_strName = strName;
}

const std::_tstring& GraphBuilder::GetName() const
{
   return m_strName;
}

void GraphBuilder::InitDocumentation(LPCTSTR lpszDocSetName,UINT nHID)
{
   m_strDocSetName = lpszDocSetName;
   m_nHelpID = nHID;
}

void GraphBuilder::SetDocumentationSetName(LPCTSTR lpszDocSetName)
{
   m_strDocSetName = lpszDocSetName;
}

const CString& GraphBuilder::GetDocumentationSetName() const
{
   return m_strDocSetName;
}

void GraphBuilder::SetHelpID(UINT nID)
{
   m_nHelpID = nID;
}

UINT GraphBuilder::GetHelpID() const
{
   return m_nHelpID;
}

void GraphBuilder::SetMenuBitmap(const CBitmap* pBmp)
{
   m_pBitmap = pBmp;
}

const CBitmap* GraphBuilder::GetMenuBitmap()
{
   return m_pBitmap;
}

void GraphBuilder::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
}

BOOL GraphBuilder::CanPrint()
{
   return TRUE;
}

bool GraphBuilder::HandleDoubleClick(UINT nFlags,CPoint point)
{
   // do nothing by default
    return false;
}
