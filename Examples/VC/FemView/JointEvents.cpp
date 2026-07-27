// JointEvents.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "FEA2DDoc.h"
#include "JointEvents.h"
#include "EditJointDlg.h"
#include "mfcdual.h"
#include "ListID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJointEvents
UINT CJointEvents::ms_Format = ::RegisterClipboardFormat(_T("Joints"));

CJointEvents::CJointEvents(CFEA2DDoc* pDoc)
{
   m_pDoc = pDoc;
}

CJointEvents::~CJointEvents()
{
}

void CJointEvents::OnChanged(std::shared_ptr<iDisplayObject> pDO)
{
}

void CJointEvents::OnDragMoved(std::shared_ptr<iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset)
{
   // Move the joint and the display object
   JointIDType id = pDO->GetID();

   WBFL::FEA2D::Model* model = m_pDoc->m_Model.get();
   WBFL::FEA2D::Joint* jnt = model->FindJoint(id);

   ASSERT(jnt != NULL);
   ASSERT(id == jnt->GetID());

   Float64 x = jnt->GetX();
   Float64 y = jnt->GetY();

   auto [dx,dy] = offset.GetDimensions();

   x += dx;
   y += dy;

   jnt->SetX(x);
   jnt->SetY(y);

   m_pDoc->OnModelChanged();

   auto jntRep = std::dynamic_pointer_cast<iPointDisplayObject>(pDO);
   ASSERT(jntRep != NULL);
   jntRep->Offset(offset,TRUE,FALSE);
}

void CJointEvents::OnMoved(std::shared_ptr<iDisplayObject> pDO)
{
   // Joint got dropped in a different view... Need to delete the joint and
   // all members that attach to it.
   ASSERT(FALSE);
}

void CJointEvents::OnCopied(std::shared_ptr<iDisplayObject> pDO)
{
   // This joint got drag/drop copied to a different view... No big deal
}

bool CJointEvents::OnLButtonDblClk(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   // Joint got double clicked on... Display its editing dialog
   IDType id = pDO->GetID();
   EditJoint(id);

   return true;
}

bool CJointEvents::OnLButtonDown(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   // Select the display object and start a drag and drop task

   auto list = pDO->GetDisplayList();

   auto dispMgr = list->GetDisplayMgr();

   // If control key is pressed, don't clear current selection
   // (i.e. we want multi-select)
   BOOL bMultiSelect = nFlags & MK_CONTROL ? TRUE : FALSE;
   
   if ( bMultiSelect )
   {
      // clear all selected objects that aren't part of the joint list
      dispMgr->ClearSelectedObjectsByList(JNT_LIST,AccessType::ByID,FALSE);
   }

   dispMgr->SelectObject(pDO,!bMultiSelect);

   // d&d task
   auto factory = dispMgr->GetTaskFactory();
   auto task = factory->CreateLocalDragDropTask(dispMgr,point);
   dispMgr->SetTask(task);

   return true;
}

bool CJointEvents::OnRButtonDblClk(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CJointEvents::OnRButtonDown(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CJointEvents::OnRButtonUp(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CJointEvents::OnLButtonUp(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CJointEvents::OnMouseMove(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CJointEvents::OnMouseWheel(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,short zDelta,const POINT& point)
{
   return false;
}

bool CJointEvents::OnKeyDown(std::shared_ptr<iDisplayObject> pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   IDType id = pDO->GetID();

   switch(nChar)
   {
   case VK_RETURN:
      EditJoint(id);
      break;

   case VK_DELETE:
      DeleteJoint(id);
      break;
   }

   return true;
}

bool CJointEvents::OnContextMenu(std::shared_ptr<iDisplayObject> pDO,CWnd* pWnd,const POINT& point)
{
   return false;
}

void CJointEvents::OnSelect(std::shared_ptr<iDisplayObject> pDO)
{
}

void CJointEvents::OnUnselect(std::shared_ptr<iDisplayObject> pDO)
{
}

UINT CJointEvents::Format()
{
   return ms_Format;
}

bool CJointEvents::PrepareForDrag(std::shared_ptr<iDisplayObject> pDO,std::shared_ptr<iDragDataSink> pSink)
{
   pSink->CreateFormat(ms_Format);

   IDType id = pDO->GetID();
   pSink->Write(ms_Format,&id,sizeof(id));
   return TRUE;
}

void CJointEvents::OnDrop(std::shared_ptr<iDisplayObject> pDO,std::shared_ptr<iDragDataSource> pSource)
{
   IDType id;
   pSource->PrepareFormat(ms_Format);
   pSource->Read(ms_Format,&id,sizeof(id));
   pDO->SetID(id);
}



void CJointEvents::EditJoint(IDType jntID)
{
   WBFL::FEA2D::Model* model = m_pDoc->m_Model.get();
   WBFL::FEA2D::Joint* jnt = model->FindJoint(jntID);

   ASSERT(jnt != NULL);
//   ASSERT(jntID == jnt->ID);

   CEditJointDlg dlg;
   dlg.m_bSupportFx = jnt->IsDofReleased(WBFL::FEA2D::JointReleaseType::Fx) ? FALSE : TRUE;
   dlg.m_bSupportFy = jnt->IsDofReleased(WBFL::FEA2D::JointReleaseType::Fy) ? FALSE : TRUE;
   dlg.m_bSupportMz = jnt->IsDofReleased(WBFL::FEA2D::JointReleaseType::Mz) ? FALSE : TRUE;

   dlg.m_X = jnt->GetX();
   dlg.m_Y = jnt->GetY();
   dlg.m_JntID = jnt->GetID();

   if ( dlg.DoModal() )
   {
      jnt->SetX(dlg.m_X);
      jnt->SetY(dlg.m_Y);

      if ( dlg.m_bSupportFx || dlg.m_bSupportFy || dlg.m_bSupportMz )
      {
         jnt->Support();
         if ( !dlg.m_bSupportFx )
            jnt->ReleaseDof(WBFL::FEA2D::JointReleaseType::Fx);

         if ( !dlg.m_bSupportFy )
            jnt->ReleaseDof(WBFL::FEA2D::JointReleaseType::Fy);

         if ( !dlg.m_bSupportMz )
            jnt->ReleaseDof(WBFL::FEA2D::JointReleaseType::Mz);
      }

      m_pDoc->OnModelChanged();
   }
}

void CJointEvents::DeleteJoint(IDType jntID)
{
   WBFL::FEA2D::Model* model = m_pDoc->m_Model.get();

   std::vector<MemberIDType> mbrIDs = model->GetAttachedMembers(jntID);
   if ( mbrIDs.empty() )
   {
      model->RemoveJoint(jntID);
      m_pDoc->OnModelChanged();
   }
   else
   {
      AfxMessageBox(_T("The joint can't be deleted because it has members connected to it"));
   }
}
