// SupportEvents.cpp : implementation file
//

#include "stdafx.h"
#include "LBAMViewer.h"
#include "LBAMViewerDoc.h"
#include "SupportEvents.h"
#include "SupportEditDlg.h"
#include "mfcdual.h"
#include "ListID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSupportEvents
UINT CSupportEvents::ms_Format = ::RegisterClipboardFormat(_T("Supports"));

CSupportEvents::CSupportEvents(CLBAMViewerDoc* pDoc)
{
   m_pDoc = pDoc;
}

CSupportEvents::~CSupportEvents()
{
}

void CSupportEvents::OnChanged(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
}

void CSupportEvents::OnDragMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO, const WBFL::Geometry::Size2d& offset)
{
   // Move the support and the display object
   IDType id = pDO->GetID();
/*
   WBFLFem2d::IModelPtr model = pThis->m_pDoc->m_Model;
   WBFLFem2d::ISupportPtr jnt = model->Supports->Find(id);
   ASSERT(jnt != NULL);
   ASSERT(id == jnt->ID);

   double x,y;
   x = jnt->X;
   y = jnt->Y;
   x += offset->dx;
   y += offset->dy;
   jnt->X = x;
   jnt->Y = y;
*/
   auto jntRep = std::dynamic_pointer_cast<WBFL::DManip::iPointDisplayObject>(pDO);
   ASSERT(jntRep != NULL);
   jntRep->Offset(offset,TRUE,FALSE);
}

void CSupportEvents::OnMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
   // Support got dropped in a different view... Need to delete the support and
   // all members that attach to it.
   ASSERT(FALSE);
}

void CSupportEvents::OnCopied(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
   // This support got drag/drop copied to a different view... No big deal
}

bool CSupportEvents::OnLButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   // Support got double clicked on... Display its editing dialog
   IDType id = pDO->GetID();
   EditSupport(id);

   return true;
}

bool CSupportEvents::OnLButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   // Select the display object and start a drag and drop task

   auto list = pDO->GetDisplayList();
   auto dispMgr = list->GetDisplayMgr();

   // If control key is pressed, don't clear current selection
   // (i.e. we want multi-select)
   BOOL bMultiSelect = nFlags & MK_CONTROL ? TRUE : FALSE;
   
   if ( bMultiSelect )
   {
      // clear all selected objects that aren't part of the support list
      dispMgr->ClearSelectedObjectsByList(SUPPORT_LIST,AccessType::ByIndex,FALSE);
   }

   dispMgr->SelectObject(pDO,!bMultiSelect);

   // d&d task
   auto factory = dispMgr->GetTaskFactory();
   auto task = factory->CreateLocalDragDropTask(dispMgr,point);
   dispMgr->SetTask(task);

   return true;
}

bool CSupportEvents::OnRButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CSupportEvents::OnRButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CSupportEvents::OnRButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CSupportEvents::OnLButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CSupportEvents::OnMouseMove(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CSupportEvents::OnMouseWheel(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,short zDelta,const POINT& point)
{
   return false;
}

bool CSupportEvents::OnKeyDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   IDType id = pDO->GetID();

   switch(nChar)
   {
   case VK_RETURN:
      EditSupport(id);
      break;

   case VK_DELETE:
      DeleteSupport(id);
      break;
   }

   return true;
}

bool CSupportEvents::OnContextMenu(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,CWnd* pWnd,const POINT& point)
{
   return false;
}

void CSupportEvents::OnSelect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
}

void CSupportEvents::OnUnselect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
}

UINT CSupportEvents::Format()
{
   return ms_Format;
}

bool CSupportEvents::PrepareForDrag(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,std::shared_ptr<WBFL::DManip::iDragDataSink> pSink)
{
   pSink->CreateFormat(ms_Format);

   IDType id = pDO->GetID();
   pSink->Write(ms_Format,&id,sizeof(id));
   return TRUE;
}

void CSupportEvents::OnDrop(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,std::shared_ptr<WBFL::DManip::iDragDataSource> pSource)
{
   IDType id;
   pSource->PrepareFormat(ms_Format);
   pSource->Read(ms_Format,&id,sizeof(id));
   pDO->SetID(id);
}

void CSupportEvents::EditSupport(IDType jntID)
{
/*
   WBFLFem2d::IModelPtr model = m_pDoc->m_Model;
   WBFLFem2d::ISupportPtr jnt = model->Supports->Find(jntID);
   ASSERT(jnt != NULL);
   ASSERT(jntID == jnt->ID);
*/
   CSupportEditDlg dlg;
/*
   dlg.m_bSupportFx = jnt->IsDofReleased(WBFLFem2d::jrtFx) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_bSupportFy = jnt->IsDofReleased(WBFLFem2d::jrtFy) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_bSupportMz = jnt->IsDofReleased(WBFLFem2d::jrtMz) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_X = jnt->X;
   dlg.m_Y = jnt->Y;
   dlg.m_JntID = jnt->ID;
*/
   if ( dlg.DoModal() )
   {
/*
      jnt->X = dlg.m_X;
      jnt->Y = dlg.m_Y;

      if ( dlg.m_bSupportFx || dlg.m_bSupportFy || dlg.m_bSupportMz )
      {
         jnt->Support();
         if ( !dlg.m_bSupportFx )
            jnt->ReleaseDof(WBFLFem2d::jrtFx);

         if ( !dlg.m_bSupportFy )
            jnt->ReleaseDof(WBFLFem2d::jrtFy);

         if ( !dlg.m_bSupportMz )
            jnt->ReleaseDof(WBFLFem2d::jrtMz);

     }
*/   
   }
}

void CSupportEvents::DeleteSupport(IDType jntID)
{
/*
   WBFLFem2d::IModelPtr model = m_pDoc->m_Model;
   WBFLFem2d::ISupportCollectionPtr supports = model->Supports;
   WBFLFem2d::ISupportPtr support = supports->Find(jntID);
   if ( support->Members->Count == 0 )
   {
      supports->Remove(jntID,WBFLFem2d::atID);
   }
   else
   {
*/
      AfxMessageBox(_T("The support can't be deleted because it has members connected to it"));
  
}
