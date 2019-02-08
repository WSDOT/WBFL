///////////////////////////////////////////////////////////////////////
// GraphManager - Manages graph definitions
// Copyright © 1999-2019  Washington State Department of Transportation
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
#include <GraphManager\GraphBuilder.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphBuilder::CGraphBuilder()
{
   m_pBitmap = nullptr;
   m_nHelpID = 0;
}

CGraphBuilder::CGraphBuilder(const CGraphBuilder& other)
{
   m_pBitmap = other.m_pBitmap;
   m_strName = other.m_strName;
   m_nHelpID = other.m_nHelpID;
   m_strDocSetName = other.m_strDocSetName;
}

CGraphBuilder::~CGraphBuilder()
{
}

void CGraphBuilder::SetName(LPCTSTR strName)
{
   m_strName = strName;
}

LPCTSTR CGraphBuilder::GetName() const
{
   return m_strName;
}

void CGraphBuilder::InitDocumentation(LPCTSTR lpszDocSetName,UINT nHID)
{
   m_strDocSetName = lpszDocSetName;
   m_nHelpID = nHID;
}

void CGraphBuilder::SetDocumentationSetName(LPCTSTR lpszDocSetName)
{
   m_strDocSetName = lpszDocSetName;
}

const CString& CGraphBuilder::GetDocumentationSetName() const
{
   return m_strDocSetName;
}

void CGraphBuilder::SetHelpID(UINT nID)
{
   m_nHelpID = nID;
}

UINT CGraphBuilder::GetHelpID() const
{
   return m_nHelpID;
}

void CGraphBuilder::SetMenuBitmap(const CBitmap* pBmp)
{
   m_pBitmap = pBmp;
}

const CBitmap* CGraphBuilder::GetMenuBitmap()
{
   return m_pBitmap;
}

void CGraphBuilder::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
}

BOOL CGraphBuilder::CanPrint()
{
   return TRUE;
}
