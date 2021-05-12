///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

// EAFDocTemplateRegistrar.cpp: implementation of the CEAFDocTemplateRegistrar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\EAFDocTemplateRegistrar.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEAFDocTemplateRegistrar::CEAFDocTemplateRegistrar()
{
   m_Key = 1;
}

CEAFDocTemplateRegistrar::~CEAFDocTemplateRegistrar()
{
   // you should remove your own templates!!!
   ASSERT( m_Templates.size() == 0 );
}

long CEAFDocTemplateRegistrar::AddDocTemplate(CEAFDocTemplate* pNewDocTemplate)
{
   int key = m_Key++;
   m_Templates.insert( std::make_pair( key, pNewDocTemplate ) );
   return key;
}

CEAFDocTemplate* CEAFDocTemplateRegistrar::GetDocTemplate(long key)
{
   TemplateContainer::iterator found;
   found = m_Templates.find(key);
   if ( found == m_Templates.end() )
   {
      return nullptr;
   }

   return (*found).second;
}

void CEAFDocTemplateRegistrar::RemoveDocTemplate(long key)
{
   TemplateContainer::iterator found;
   found = m_Templates.find(key);
   if ( found == m_Templates.end() )
   {
      return;
   }

   CEAFDocTemplate* pTemplate = (*found).second;
   m_Templates.erase(found);
   delete pTemplate;
}