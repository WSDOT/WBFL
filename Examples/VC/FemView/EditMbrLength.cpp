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
   WBFL::FEA2D::Model* model = m_pDoc->m_Model.get();

   WBFL::FEA2D::Member* mbr = model->FindMember(mbrID);

   JointIDType startJntID = mbr->GetStartJoint();
   JointIDType endJntID = mbr->GetEndJoint();

   WBFL::FEA2D::Joint* startJnt = model->FindJoint(startJntID);
   WBFL::FEA2D::Joint* endJnt = model->FindJoint(endJntID);

   Float64 startX = startJnt->GetX();
   Float64 startY = startJnt->GetY();

   Float64 endX = endJnt->GetX();
   Float64 endY = endJnt->GetY();

   double angle = atan2(endY - startY, endX - startX);
   double dx = length * cos(angle);
   double dy = length * sin(angle);

   endX = startX + dx;
   endY = startY + dy;

   endJnt->SetX(endX);
   endJnt->SetY(endY);

   m_pDoc->OnModelChanged();
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
