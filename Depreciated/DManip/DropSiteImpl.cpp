#include "stdafx.h"
#include <DManip\DropSiteImpl.h>

CDropSiteImpl::CDropSiteImpl()
{
   m_pDispObj = 0;
}

CDropSiteImpl::~CDropSiteImpl()
{
}

DROPEFFECT CDropSiteImpl::CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,WBFLGeometry::IPoint2dPtr point)
{
   return DROPEFFECT_NONE;
}

void CDropSiteImpl::OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect,WBFLGeometry::IPoint2dPtr point)
{
   // Do nothing
   AfxMessageBox("CDropSiteImpl::OnDropped");
}

void CDropSiteImpl::SetDisplayObject(iDisplayObject* pDO)
{
   m_pDispObj = pDO;
}

iDisplayObject* CDropSiteImpl::GetDisplayObject()
{
   return m_pDispObj;
}
