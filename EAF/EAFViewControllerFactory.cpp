///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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


// EAFViewControllerFactory.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFViewControllerFactory.h>
#include "EAFViewController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEAFViewControllerFactory::CEAFViewControllerFactory()
{
   m_pFrame = nullptr;
}

CEAFViewControllerFactory::~CEAFViewControllerFactory()
{
}

void CEAFViewControllerFactory::Init(CMDIChildWnd* pFrame)
{
   m_pFrame = pFrame;
}

void CEAFViewControllerFactory::GetViewController(IEAFViewController** ppController)
{
   if (m_pViewController == nullptr)
   {
      CreateViewController(&m_pViewController);
   }
   m_pViewController.CopyTo(ppController);
}

void CEAFViewControllerFactory::CreateViewController(IEAFViewController** ppController)
{
   ATLASSERT(m_pFrame != nullptr); // did you forget to call Init?

   CComObject<CEAFViewController>* pController;
   CComObject<CEAFViewController>::CreateInstance(&pController);
   pController->Init(m_pFrame);

   (*ppController) = pController;
   (*ppController)->AddRef();
}
