// MbrEvents.h: interface for the CMbrEvents class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class CMbrEvents : public IDisplayObjectEvents  
{
public:
	CMbrEvents();
	virtual ~CMbrEvents();

   virtual void OnChanged(IDisplayObject* pDO);
   virtual void OnMoved(IDisplayObject* pDO,WBFLGeometry::ISize2dPtr offset);
   virtual void OnLButtonDblClk(IDisplayObject* pDO,UINT nFlags,CPoint point);
};

