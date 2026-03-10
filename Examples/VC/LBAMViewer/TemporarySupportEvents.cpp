// TemporarySupportEvents.cpp : implementation file
//

#include "stdafx.h"
#include "LBAMViewer.h"
#include "LBAMViewerDoc.h"
#include "TemporarySupportEvents.h"
#include "TemporarySupportEditDlg.h"
#include "mfcdual.h"
#include "ListID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemporarySupportEvents
UINT CTemporarySupportEvents::ms_Format = ::RegisterClipboardFormat(_T("TemporarySupports"));

CTemporarySupportEvents::CTemporarySupportEvents(CLBAMViewerDoc* pDoc)
{
   m_pDoc = pDoc;
}

CTemporarySupportEvents::~CTemporarySupportEvents()
{
}

void CTemporarySupportEvents::OnChanged(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
}

void CTemporarySupportEvents::OnDragMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,const WBFL::Geometry::Size2d& offset)
{
   // Move the support and the display object
   IDType id = pDO->GetID();
/*
   WBFLFem2d::IModelPtr model = pThis->m_pDoc->m_Model;
   WBFLFem2d::ITemporarySupportPtr jnt = model->TemporarySupports->Find(id);
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

void CTemporarySupportEvents::OnMoved(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
   // TemporarySupport got dropped in a different view... Need to delete the support and
   // all members that attach to it.
   ASSERT(FALSE);
}

void CTemporarySupportEvents::OnCopied(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
   // This support got drag/drop copied to a different view... No big deal
}

bool CTemporarySupportEvents::OnLButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   // TemporarySupport got double clicked on... Display its editing dialog
   IDType id = pDO->GetID();
   EditTemporarySupport(id);

   return true;
}

bool CTemporarySupportEvents::OnLButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
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


bool CTemporarySupportEvents::OnRButtonDblClk(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CTemporarySupportEvents::OnRButtonDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CTemporarySupportEvents::OnRButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CTemporarySupportEvents::OnLButtonUp(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}


bool CTemporarySupportEvents::OnMouseMove(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CTemporarySupportEvents::OnMouseWheel(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nFlags,short zDelta,const POINT& point)
{
   return false;
}


bool CTemporarySupportEvents::OnKeyDown(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   IDType id = pDO->GetID();

   switch(nChar)
   {
   case VK_RETURN:
      EditTemporarySupport(id);
      break;

   case VK_DELETE:
      DeleteTemporarySupport(id);
      break;
   }

   return true;
}

bool CTemporarySupportEvents::OnContextMenu(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,CWnd* pWnd,const POINT& point)
{
   return false;
}

void CTemporarySupportEvents::OnSelect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
}

void CTemporarySupportEvents::OnUnselect(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO)
{
}

UINT CTemporarySupportEvents::Format()
{
   return ms_Format;
}

bool CTemporarySupportEvents::PrepareForDrag(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,std::shared_ptr<WBFL::DManip::iDragDataSink> pSink)
{
   pSink->CreateFormat(ms_Format);

   IDType id = pDO->GetID();
   pSink->Write(ms_Format,&id,sizeof(id));
   return true;
}

void CTemporarySupportEvents::OnDrop(std::shared_ptr<WBFL::DManip::iDisplayObject> pDO,std::shared_ptr<WBFL::DManip::iDragDataSource> pSource)
{
   IDType id;
   pSource->PrepareFormat(ms_Format);
   pSource->Read(ms_Format,&id,sizeof(id));
   pDO->SetID(id);
}



void CTemporarySupportEvents::EditTemporarySupport(IDType jntID)
{
/*
   WBFLFem2d::IModelPtr model = m_pDoc->m_Model;
   WBFLFem2d::ITemporarySupportPtr jnt = model->TemporarySupports->Find(jntID);
   ASSERT(jnt != NULL);
   ASSERT(jntID == jnt->ID);
*/
   CTemporarySupportEditDlg dlg;
/*
   dlg.m_bTemporarySupportFx = jnt->IsDofReleased(WBFLFem2d::jrtFx) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_bTemporarySupportFy = jnt->IsDofReleased(WBFLFem2d::jrtFy) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_bTemporarySupportMz = jnt->IsDofReleased(WBFLFem2d::jrtMz) == VARIANT_TRUE ? FALSE : TRUE;
   dlg.m_X = jnt->X;
   dlg.m_Y = jnt->Y;
   dlg.m_JntID = jnt->ID;
*/
   if ( dlg.DoModal() )
   {
/*
      jnt->X = dlg.m_X;
      jnt->Y = dlg.m_Y;

      if ( dlg.m_bTemporarySupportFx || dlg.m_bTemporarySupportFy || dlg.m_bTemporarySupportMz )
      {
         jnt->TemporarySupport();
         if ( !dlg.m_bTemporarySupportFx )
            jnt->ReleaseDof(WBFLFem2d::jrtFx);

         if ( !dlg.m_bTemporarySupportFy )
            jnt->ReleaseDof(WBFLFem2d::jrtFy);

         if ( !dlg.m_bTemporarySupportMz )
            jnt->ReleaseDof(WBFLFem2d::jrtMz);

     }
*/   
   }
}

void CTemporarySupportEvents::DeleteTemporarySupport(IDType jntID)
{
/*
   WBFLFem2d::IModelPtr model = m_pDoc->m_Model;
   WBFLFem2d::ITemporarySupportCollectionPtr supports = model->TemporarySupports;
   WBFLFem2d::ITemporarySupportPtr support = supports->Find(jntID);
   if ( support->Members->Count == 0 )
   {
      supports->Remove(jntID,WBFLFem2d::atID);
   }
   else
   {
*/
      AfxMessageBox(_T("The support can't be deleted because it has members connected to it"));
  
}
