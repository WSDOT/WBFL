// EAFDocTemplateRegistrar.h: interface for the CEAFDocTemplateRegistrar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EAFDocTemplateRegistrar_H__626A3D49_E71B_4A58_AE3B_3A00153B4626__INCLUDED_)
#define AFX_EAFDocTemplateRegistrar_H__626A3D49_E71B_4A58_AE3B_3A00153B4626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <EAF\EAFExp.h>
#include <EAF\EAFDocTemplate.h>
#include <map>

class EAFCLASS CEAFDocTemplateRegistrar  
{
public:
	CEAFDocTemplateRegistrar();
	virtual ~CEAFDocTemplateRegistrar();

   long AddDocTemplate(CEAFDocTemplate* pNewDocTemplate);
   CEAFDocTemplate* GetDocTemplate(long key);
   void RemoveDocTemplate(long key);

private:
   long m_Key;
   typedef std::map<long,CEAFDocTemplate*> TemplateContainer;
   TemplateContainer m_Templates;
};

#endif // !defined(AFX_EAFDocTemplateRegistrar_H__626A3D49_E71B_4A58_AE3B_3A00153B4626__INCLUDED_)
