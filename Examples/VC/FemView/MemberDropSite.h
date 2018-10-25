// MemberDropSite.h: interface for the CMemberDropSite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMBERDROPSITE_H__1F8A97C9_F789_11D4_8B9B_006097C68A9C__INCLUDED_)
#define AFX_MEMBERDROPSITE_H__1F8A97C9_F789_11D4_8B9B_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemberDropSite : public CCmdTarget  
{
public:
	CMemberDropSite(CFEA2DDoc* pDoc);
	virtual ~CMemberDropSite();

   DECLARE_INTERFACE_MAP()

   // iDisplayObjectEvents Implementation
   BEGIN_INTERFACE_PART(DisplayObjectEvents,iDisplayObjectEvents)
      STDMETHOD_(void,OnChanged)(iDisplayObject* pDO);
      STDMETHOD_(void,OnDragMoved)(iDisplayObject* pDO,ISize2d* offset);
      STDMETHOD_(void,OnMoved)(iDisplayObject* pDO);
      STDMETHOD_(void,OnCopied)(iDisplayObject* pDO);
      STDMETHOD_(bool,OnLButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnLButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnLButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnMouseMove)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnMouseWheel)(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point);
      STDMETHOD_(bool,OnKeyDown)(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags);
      STDMETHOD_(bool,OnContextMenu)(iDisplayObject* pDO,CWnd* pWnd,CPoint point);
      STDMETHOD_(void,OnSelect)(iDisplayObject* pDO);
      STDMETHOD_(void,OnUnselect)(iDisplayObject* pDO);
   END_INTERFACE_PART(DisplayObjectEvents)

   BEGIN_INTERFACE_PART(DropSite,iDropSite)
      STDMETHOD_(DROPEFFECT,CanDrop)(COleDataObject* pDataObject,DWORD dwKeyState,IPoint2d* point);
      STDMETHOD_(void,OnDropped)(COleDataObject* pDataObject,DROPEFFECT dropEffect,IPoint2d* point);
      STDMETHOD_(void,SetDisplayObject)(iDisplayObject* pDO);
      STDMETHOD_(void,GetDisplayObject)(iDisplayObject** dispObj);
      STDMETHOD_(void,Highlite)(CDC* pDC,BOOL bHighlite);
   END_INTERFACE_PART(DropSite)

private:
   CFEA2DDoc* m_pDoc;
   // weak reference
   iDisplayObject* m_DispObj;

   void DeleteMember(IDType mbrID);
   void EditMember(IDType mbrID);
};

#endif // !defined(AFX_MEMBERDROPSITE_H__1F8A97C9_F789_11D4_8B9B_006097C68A9C__INCLUDED_)
