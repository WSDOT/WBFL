///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <BridgeModeling\BridgeModelingLib.h>
#include "AlignmentObserver.h"
#include <BridgeModeling\Bridge.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void bmfAlignmentObserver::FinalRelease()
{
   if ( m_pBridge )
   {
      ReleaseBridge();
   }
}

void bmfAlignmentObserver::SetBridge(bmfBridge* pBridge)
{
   m_pBridge = pBridge;

   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   HRESULT hr;
   hr = AtlAdvise(alignment,this,IID_IPathEvents,&m_dwCookie);
   ATLASSERT( SUCCEEDED(hr) );
}

void bmfAlignmentObserver::ReleaseBridge()
{
   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   HRESULT hr;
   hr = AtlUnadvise(alignment,IID_IPathEvents,m_dwCookie);
   ATLASSERT(SUCCEEDED(hr));

   m_pBridge = 0;
}

STDMETHODIMP bmfAlignmentObserver::OnPathChanged(IPath* path)
{
   m_pBridge->OnAlignmentChanged();
   return S_OK;
}

STDMETHODIMP bmfAlignmentObserver::OnProfileChanged(IProfile* profile)
{
   return S_OK;
}
