///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

#include "stdafx.h"
#include <EAF\EAFViewController.h>
#include "EAFViewController.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEAFViewController::CEAFViewController()
{
   m_pFrame = nullptr;
}

CEAFViewController::~CEAFViewController()
{

}

void CEAFViewController::Init(CMDIChildWnd* pFrame)
{
   m_pFrame = pFrame;
}

//////////////////////////////////////////
// IEAFViewController
bool CEAFViewController::IsOpen() const
{
   return m_pFrame->GetSafeHwnd() != 0;
}

void CEAFViewController::Close()
{
   if (IsOpen())
   {
      m_pFrame->DestroyWindow();
   }
}

void CEAFViewController::Minimize()
{
   if (IsOpen())
   {
      m_pFrame->ShowWindow(SW_RESTORE);
      m_pFrame->ShowWindow(SW_MINIMIZE);
   }
}

void CEAFViewController::Maximize()
{
   if (IsOpen())
   {
      m_pFrame->ShowWindow(SW_RESTORE);
      m_pFrame->ShowWindow(SW_MAXIMIZE);
   }
}

void CEAFViewController::Restore()
{
   if (IsOpen())
   {
      m_pFrame->ShowWindow(SW_RESTORE);
   }
}
