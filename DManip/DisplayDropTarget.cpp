///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2026  Washington State Department of Transportation
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
#include <DManip/DisplayDropTarget.h>
#include <DManip/DisplayWnd.h> // full definition needed here


DROPEFFECT CDisplayDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

    // Use MFC runtime check instead of C++ dynamic_cast (cross-module RTTI can fail)
    CDisplayWnd* pDispWnd = nullptr;
    if (m_pWnd && m_pWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
        pDispWnd = static_cast<CDisplayWnd*>(m_pWnd);

    if (!pDispWnd)
        return COleDropTarget::OnDragEnter(pWnd, pDataObject, dwKeyState, point);

    POINT pt = point;
    auto pMgr = pDispWnd->GetDisplayMgr();
    if (pMgr)
        return pMgr->OnDragEnter(pDataObject, dwKeyState, pt);

    return COleDropTarget::OnDragEnter(pWnd, pDataObject, dwKeyState, point);
}

DROPEFFECT CDisplayDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

    CDisplayWnd* pDispWnd = nullptr;
    if (m_pWnd && m_pWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
        pDispWnd = static_cast<CDisplayWnd*>(m_pWnd);

    if (!pDispWnd)
        return COleDropTarget::OnDragOver(pWnd, pDataObject, dwKeyState, point);

    POINT pt = point;
    auto pMgr = pDispWnd->GetDisplayMgr();
    if (pMgr)
        return pMgr->OnDragOver(pDataObject, dwKeyState, pt);

    return COleDropTarget::OnDragOver(pWnd, pDataObject, dwKeyState, point);
}

void CDisplayDropTarget::OnDragLeave(CWnd* pWnd)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

    CDisplayWnd* pDispWnd = nullptr;
    if (m_pWnd && m_pWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
        pDispWnd = static_cast<CDisplayWnd*>(m_pWnd);

    if (!pDispWnd)
    {
        COleDropTarget::OnDragLeave(pWnd);
        return;
    }

    auto pMgr = pDispWnd->GetDisplayMgr();
    if (pMgr)
        pMgr->OnDragLeave();
    else
        COleDropTarget::OnDragLeave(pWnd);
}

BOOL CDisplayDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

    CDisplayWnd* pDispWnd = nullptr;
    if (m_pWnd && m_pWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
        pDispWnd = static_cast<CDisplayWnd*>(m_pWnd);

    if (!pDispWnd)
        return COleDropTarget::OnDrop(pWnd, pDataObject, dropEffect, point);

    POINT pt = point;
    auto pMgr = pDispWnd->GetDisplayMgr();
    if (pMgr)
        return pMgr->OnDrop(pDataObject, dropEffect, pt);

    return COleDropTarget::OnDrop(pWnd, pDataObject, dropEffect, point);
}