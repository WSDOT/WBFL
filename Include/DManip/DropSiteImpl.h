#ifndef INCLUDED_DROPSITEIMPL_H_
#define INCLUDED_DROPSITEIMPL_H_

#include <DManip\DManipExp.h>
#include <DManip\DropSite.h>

class DMANIPCLASS CDropSiteImpl : public iDropSite
{
public:
   CDropSiteImpl();
   ~CDropSiteImpl();

   virtual DROPEFFECT CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,WBFLGeometry::IPoint2dPtr point);
   virtual void OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect,WBFLGeometry::IPoint2dPtr point);

   virtual void SetDisplayObject(iDisplayObject* pDO);
   virtual iDisplayObject* GetDisplayObject();

private:
   iDisplayObject* m_pDispObj;
};

#endif // INCLUDED_DROPSITEIMPL_H_