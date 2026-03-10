///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

// EAFDocTemplateRegistrar.cpp: implementation of the CEAFDocTemplateRegistrar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <EAF\DocTemplateRegistrar.h>

using namespace WBFL::EAF;

DocTemplateRegistrar::~DocTemplateRegistrar()
{
   // you should remove your own templates!!!
   CHECK( m_Templates.size() == 0 );
}

long DocTemplateRegistrar::AddDocTemplate(CEAFDocTemplate* pNewDocTemplate)
{
   int key = m_Key++;
   m_Templates.insert( std::make_pair( key, pNewDocTemplate ) );
   return key;
}

CEAFDocTemplate* DocTemplateRegistrar::GetDocTemplate(long key)
{
   TemplateContainer::iterator found;
   found = m_Templates.find(key);
   if ( found == m_Templates.end() )
   {
      return nullptr;
   }

   return (*found).second;
}

void DocTemplateRegistrar::RemoveDocTemplate(long key)
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