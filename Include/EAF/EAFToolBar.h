// EAFToolBar.h: interface for the CEAFToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EAFTOOLBAR_H__44A9C83E_AD58_4EF2_9D53_FDD7452FFC9B__INCLUDED_)
#define AFX_EAFTOOLBAR_H__44A9C83E_AD58_4EF2_9D53_FDD7452FFC9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <EAF\EAFExp.h>
#include <afxext.h>

class CEAFMainFrame;
class CEAFDocument;
class CPluginCommandManager;
interface ICommandCallback;

class EAFCLASS CEAFToolBar  
{
public:
	CEAFToolBar();
	virtual ~CEAFToolBar();

   BOOL AddButtons(int nButtons,UINT* nIDs,UINT nBitmapID,LPCSTR lpszStrings,ICommandCallback* pCallback);
   void RemoveButtons(ICommandCallback* pCallback);

   DWORD GetID();

private:
   friend CEAFMainFrame;
   friend CEAFDocument;

   DWORD m_ID;

   bool bOwnsToolBar;
   CToolBar* m_pToolBar;
   CPluginCommandManager* m_pCmdMgr;
};

#endif // !defined(AFX_EAFTOOLBAR_H__44A9C83E_AD58_4EF2_9D53_FDD7452FFC9B__INCLUDED_)
