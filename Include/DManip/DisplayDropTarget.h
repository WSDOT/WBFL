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
#pragma once

#include <DManip/DManipExp.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>
#include <DManip/Mapping.h>

#include "afxwin.h"
#include "afxole.h"


class WBFL::DManip::iTask;
class WBFL::DManip::TaskFactory;


// Forward
class CDisplayWnd;

/// Small COleDropTarget subclass that forwards events to the CDisplayWnd / DisplayMgr
class CDisplayDropTarget : public COleDropTarget
{
public:
    CDisplayDropTarget() : m_pWnd(nullptr) {}
    // Register overload stores the CWnd pointer and registers with OLE.
    // Use CWnd* here so header does not need the full CDisplayWnd definition.
    bool Register(CWnd* pWnd)
    {
        // store as CWnd*; conversion to CDisplayWnd* will be done in the .cpp
        m_pWnd = pWnd;
        return COleDropTarget::Register(pWnd);
    }

protected:
    // forwarders - implementations are in DisplayWnd.cpp
    virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) override;
    virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) override;
    virtual void      OnDragLeave(CWnd* pWnd) override;
    virtual BOOL      OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) override;

private:
    CWnd* m_pWnd;
};
