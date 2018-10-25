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
      return NULL;

   return (*found).second;
}

void CEAFDocTemplateRegistrar::RemoveDocTemplate(long key)
{
   TemplateContainer::iterator found;
   found = m_Templates.find(key);
   if ( found == m_Templates.end() )
      return;

   CEAFDocTemplate* pTemplate = (*found).second;
   m_Templates.erase(found);
   delete pTemplate;
}