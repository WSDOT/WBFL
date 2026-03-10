// EditMbrLength.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "FEA2DDoc.h"
#include "EditMbrLength.h"
#include "mfcdual.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditMbrLength


CEditMbrLength::CEditMbrLength(CFEA2DDoc* pDoc)
{
   m_pDoc = pDoc;
}

CEditMbrLength::~CEditMbrLength()
{
}

void CEditMbrLength::OnChanged(std::shared_ptr<iDisplayObject> pDO)
{
   // The member length was in-place edited

   // Get the new length
   auto dimLine = std::dynamic_pointer_cast<DimensionLine>(pDO);
   auto textBlock = dimLine->GetTextBlock();

   auto edTextBlock = std::dynamic_pointer_cast<EditableTextBlock>(textBlock);
   CString strText = edTextBlock->GetEditedText();

   double length = _tstof(strText);

   // Compute the new coordinates of the member end joint.
   MemberIDType mbrID = pDO->GetID();
   CComPtr<IFem2dModel> model = m_pDoc->m_Model;
   CComPtr<IFem2dMemberCollection> members;
   model->get_Members(&members);

   CComPtr<IFem2dMember> mbr;
   members->Find(mbrID,&mbr);

   JointIDType startJntID, endJntID;
   mbr->get_StartJoint(&startJntID);
   mbr->get_EndJoint(&endJntID);

   CComPtr<IFem2dJointCollection> joints;
   model->get_Joints(&joints);

   CComPtr<IFem2dJoint> startJnt, endJnt;
   joints->Find(startJntID,&startJnt);
   joints->Find(endJntID,&endJnt);

   Float64 startX, startY;
   startJnt->get_X(&startX);
   startJnt->get_Y(&startY);

   Float64 endX, endY;
   endJnt->get_X(&endX);
   endJnt->get_Y(&endY);
   
   double angle = atan2(endY - startY, endX - startX);
   double dx = length * cos(angle);
   double dy = length * sin(angle);

   endX = startX + dx;
   endY = startY + dy;

   endJnt->put_X(endX);
   endJnt->put_Y(endY);
}

void CEditMbrLength::OnDragMoved(std::shared_ptr<iDisplayObject> pDO,const WBFL::Geometry::Size2d& offset)
{
}

void CEditMbrLength::OnMoved(std::shared_ptr<iDisplayObject> pDO)
{
}

void CEditMbrLength::OnCopied(std::shared_ptr<iDisplayObject> pDO)
{
}

bool CEditMbrLength::OnLButtonDblClk(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CEditMbrLength::OnLButtonDown(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CEditMbrLength::OnRButtonDblClk(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CEditMbrLength::OnRButtonDown(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CEditMbrLength::OnRButtonUp(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CEditMbrLength::OnLButtonUp(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CEditMbrLength::OnMouseMove(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CEditMbrLength::OnMouseWheel(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,short zDelta,const POINT& point)
{
   return false;
}

void CEditMbrLength::OnSelect(std::shared_ptr<iDisplayObject> pDO)
{
}

void CEditMbrLength::OnUnselect(std::shared_ptr<iDisplayObject> pDO)
{
}

bool CEditMbrLength::OnKeyDown(std::shared_ptr<iDisplayObject> pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   return false;
}

bool CEditMbrLength::OnContextMenu(std::shared_ptr<iDisplayObject> pDO,CWnd* pWnd,const POINT& point)
{
   return false;
}
