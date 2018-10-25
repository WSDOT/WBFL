// MbrEvents.h: interface for the CMbrEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MBREVENTS_H__0C0011E0_EEA6_11D4_8CE4_0080C7380027__INCLUDED_)
#define AFX_MBREVENTS_H__0C0011E0_EEA6_11D4_8CE4_0080C7380027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMbrEvents : public IDisplayObjectEvents  
{
public:
	CMbrEvents();
	virtual ~CMbrEvents();

   virtual void OnChanged(IDisplayObject* pDO);
   virtual void OnMoved(IDisplayObject* pDO,WBFLGeometry::ISize2dPtr offset);
   virtual void OnLButtonDblClk(IDisplayObject* pDO,UINT nFlags,CPoint point);
};

#endif // !defined(AFX_MBREVENTS_H__0C0011E0_EEA6_11D4_8CE4_0080C7380027__INCLUDED_)
