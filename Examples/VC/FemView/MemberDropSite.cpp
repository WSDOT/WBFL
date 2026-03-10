// MemberDropSite.cpp: implementation of the CMemberDropSite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FEA2D.h"
#include "FEA2DDoc.h"
#include "MemberDropSite.h"
#include "EditMemberDlg.h"
#include "mfcdual.h"
#include "AddPointLoadDlg.h"
#include "PointLoadEventsImpl.h"
#include "ListID.h"
#include "EditMbrLength.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemberDropSite::CMemberDropSite(CFEA2DDoc* pDoc)
{
   m_pDoc = pDoc;
}

CMemberDropSite::~CMemberDropSite()
{

}

void CMemberDropSite::OnChanged(std::shared_ptr<iDisplayObject> pDO)
{
   ASSERT(FALSE); // Member display objects don't have internal data that can be changed
}

void CMemberDropSite::OnDragMoved(std::shared_ptr<iDisplayObject> pDO,const WBFL::Geometry::Size2d& offset)
{
   ASSERT(FALSE); // Member shouldn't get moved
}

void CMemberDropSite::OnMoved(std::shared_ptr<iDisplayObject> pDO)
{
   ASSERT(FALSE); // Member shouldn't get moved
}

void CMemberDropSite::OnCopied(std::shared_ptr<iDisplayObject> pDO)
{
   ASSERT(FALSE); // Member shouldn't get copied
}

bool CMemberDropSite::OnLButtonDblClk(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   // Member got double clicked on... Display its editing dialog
   IDType id = pDO->GetID();
   EditMember(id);

   return true;
}

bool CMemberDropSite::OnLButtonDown(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   auto list = pDO->GetDisplayList();
   auto dispMgr = list->GetDisplayMgr();

   // If control key is pressed, don't clear current selection
   // (i.e. we want multi-select)
   BOOL bMultiSelect = nFlags & MK_CONTROL ? TRUE : FALSE;
   
   if ( bMultiSelect )
   {
      // clear all selected objects that aren't part of the member list
      dispMgr->ClearSelectedObjectsByList(MBR_LIST,AccessType::ByID,FALSE);
   }

   dispMgr->SelectObject(pDO,!bMultiSelect);

   return true;
}

bool CMemberDropSite::OnRButtonDblClk(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CMemberDropSite::OnRButtonDown(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CMemberDropSite::OnRButtonUp(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CMemberDropSite::OnLButtonUp(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CMemberDropSite::OnMouseMove(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,const POINT& point)
{
   return false;
}

bool CMemberDropSite::OnMouseWheel(std::shared_ptr<iDisplayObject> pDO,UINT nFlags,short zDelta,const POINT& point)
{
   return false;
}

void CMemberDropSite::OnSelect(std::shared_ptr<iDisplayObject> pDO)
{
   auto list = pDO->GetDisplayList();
   auto dispMgr = list->GetDisplayMgr();

   // Create a dimension line display object with in-place editable text
   // 1. Get the sockets for the line display object that represents the member
   auto connector = std::dynamic_pointer_cast<iConnector>(pDO);
   auto startPlug = connector->GetStartPlug();
   auto endPlug = connector->GetEndPlug();

   auto startSocket = startPlug->GetSocket();
   auto endSocket = endPlug->GetSocket();

   // 2. Create the dimension line display object
   //    Hook onto its connector interface
   auto dimLine = DimensionLine::Create();
   connector = std::dynamic_pointer_cast<iConnector>(dimLine);

   // 3. Attach its plugs to the same sockets the line display object is using
   startPlug = connector->GetStartPlug();
   endPlug = connector->GetEndPlug();

   DWORD dwCookie;
   dwCookie = startSocket->Connect(startPlug);
   dwCookie = endSocket->Connect(endPlug);

   // 4. Attach an inplace editable text block to the dimension line
   auto textBlock = EditableTextBlock::Create();
   dimLine->SetTextBlock(textBlock);
   dimLine->EnableAutoText(TRUE);

   // 5. Create an event sink and attach it to the dimension line
   auto pEdit = std::make_shared<CEditMbrLength>(m_pDoc);
   dimLine->RegisterEventSink(pEdit);

   // 6. Assign the member ID to the dimension line display object
   IDType mbrID = pDO->GetID();
   dimLine->SetID(mbrID);

   // 7. Add the new display object to the display
   dispMgr->AddDisplayObject(dimLine,DIMLINE_LIST,AccessType::ByID);
}

void CMemberDropSite::OnUnselect(std::shared_ptr<iDisplayObject> pDO)
{
   auto list = pDO->GetDisplayList();
   auto dispMgr = list->GetDisplayMgr();

   list = dispMgr->FindDisplayList(DIMLINE_LIST);
   list->Clear();
}

bool CMemberDropSite::OnKeyDown(std::shared_ptr<iDisplayObject> pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   IDType id = pDO->GetID();
   switch (nChar)
   {
   case VK_RETURN:
      EditMember(id);
      break;

   case VK_DELETE:
      DeleteMember(id);
      break;
   }

   return true;
}

bool CMemberDropSite::OnContextMenu(std::shared_ptr<iDisplayObject> pDO,CWnd* pWnd,const POINT& point)
{
   return false;
}

DROPEFFECT CMemberDropSite::CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,const WBFL::Geometry::Point2d& point)
{
   // Was a tool dragged over the member?
   auto tool = Tool::Create();

   if ( pDataObject->IsDataAvailable( tool->Format() ) )
   {
      auto source = DragDataSource::Create();
      source->SetDataObject(pDataObject);
      tool->OnDrop(source); // Rebuild the tool object from the data object
#pragma Reminder("Use a factory for the line above")
      if ( tool->GetID() == IDC_CONCLOAD_TOOL )
         return DROPEFFECT_MOVE;
   }

   // Was a load display object dragged over the member?
   if ( pDataObject->IsDataAvailable( CPointLoadEventsImpl::ms_Format ) )
   {
      return (dwKeyState & MK_CONTROL) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
   }


   return DROPEFFECT_NONE;
}

void CMemberDropSite::OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect, const WBFL::Geometry::Point2d& point)
{
   // Something was dropped on a display object that represents a member
   // in the fem model. We know that, because this object is a drop site
   // for just such a situation.

   // Let's see what was dropped

   // Was it a tool from the palette?
   auto tool = Tool::Create();
   if ( pDataObject->IsDataAvailable(tool->Format()) )
   {
      // Yes, but which one?
      auto source = DragDataSource::Create();
      source->SetDataObject(pDataObject);

      tool->OnDrop(source); // Rebuild the tool object from the data object
#pragma Reminder("Use a factory for the line above")

      // Was it the concentrated load tool?
      if ( tool->GetID() == IDC_CONCLOAD_TOOL )
      {
         // Yes...

         // An Add Point Load tool was dropped. Create a new point load
         // on the member the tool was dropped on.
         auto pDispObj = GetDisplayObject();
         IDType mbrID = pDispObj->GetID();

         CComPtr<IFem2dModel> model = m_pDoc->m_Model;
         CAddPointLoadDlg dlg(model,TRUE);

         dlg.m_MbrID = mbrID;
         if ( dlg.DoModal() == IDOK )
         {
            CComPtr<IFem2dLoadingCollection> loadings;
            model->get_Loadings(&loadings);

            CComPtr<IFem2dLoading> loading;
            loadings->get_Item(dlg.m_LoadingID,&loading);

            CComPtr<IFem2dPointLoadCollection> pointLoads;
            loading->get_PointLoads(&pointLoads);

            try
            {
               CComPtr<IFem2dPointLoad> ptLoad;
               IndexType count;
               pointLoads->get_Count(&count);
               pointLoads->Create(count,dlg.m_MbrID,dlg.m_Location,dlg.m_Fx,dlg.m_Fy,dlg.m_Mz,lotGlobal,&ptLoad);
            }
            catch(...)
            {
               AfxMessageBox(_T("Failed to create load"));
            }
         }
      }
   }

   // Was a display object representing a point load dropped?
   if ( pDataObject->IsDataAvailable( CPointLoadEventsImpl::ms_Format ) )
   {
      // Yes...
      // Re-create the display object

      //////////////// BEGIN HERE
      // This code should be handed by a factory
#pragma Reminder("Use a factory object for this")
      auto loadRep = PointDisplayObject::Create();

      // Associate a drag data object with it
      auto pEvents = std::make_shared<CPointLoadEventsImpl>(m_pDoc);
      loadRep->SetDragData(pEvents);

      // create a data source and associate the data object with it
      auto source = DragDataSource::Create();
      source->SetDataObject(pDataObject);

      // rebuild the display object from the data source
      loadRep->OnDrop(source);
      //////////////// END HERE

      // Create a new load in the fem model
      CComPtr<IFem2dLoadingCollection> loadings;
      m_pDoc->m_Model->get_Loadings(&loadings);
      CComPtr<IFem2dLoading> loading;
      loadings->Find(pEvents->m_Loading,&loading);
      if ( loading == NULL )
      {
         loadings->Create(pEvents->m_Loading,&loading);
      }

      CComPtr<IFem2dPointLoadCollection> ptLoads;
      loading->get_PointLoads(&ptLoads);
      IndexType id;
      ptLoads->get_Count(&id);

      try
      {
         CComPtr<IFem2dPointLoad> ptLoad;
         ptLoads->Create(id,m_DispObj.lock()->GetID(), pEvents->m_Location, pEvents->m_Fx, pEvents->m_Fy, pEvents->m_Mz, pEvents->m_Orientation, &ptLoad);
      }
      //catch(_com_error& error)
      //{
      //   CComPtr<IErrorInfo> einfo = error.ErrorInfo();
      //   CComBSTR bstrDescription;
      //   einfo->GetDescription(&bstrDescription);
      //   AfxMessageBox(CString(bstrDescription));
      //}
      catch(...)
      {
         AfxMessageBox(_T("Failed to create load"));
      }
   }
}

void CMemberDropSite::SetDisplayObject(std::weak_ptr<iDisplayObject> pDO)
{
   m_DispObj = pDO;
}

std::shared_ptr<iDisplayObject> CMemberDropSite::GetDisplayObject()
{
   return m_DispObj.lock();
}

void CMemberDropSite::Highlight(CDC* pDC,BOOL bHighlite)
{
   m_DispObj.lock()->Highlight(pDC, bHighlite);
}


void CMemberDropSite::DeleteMember(IDType mbrID)
{
   CComPtr<IFem2dModel> model = m_pDoc->m_Model;
   CComPtr<IFem2dMemberCollection> members;
   model->get_Members(&members);

   MemberIDType removedID;
   members->Remove(mbrID,atID,&removedID);
}

void CMemberDropSite::EditMember(IDType mbrID)
{
   CComPtr<IFem2dModel> model = m_pDoc->m_Model;
   CComPtr<IFem2dMemberCollection> members;
   model->get_Members(&members);

   CComPtr<IFem2dMember> mbr;
   members->Find(mbrID,&mbr);
   ASSERT(mbr != NULL);
//   ASSERT(mbrID == mbr->ID);

   CEditMemberDlg dlg(model,TRUE);
   mbr->get_ID(&dlg.m_MbrID);
   VARIANT_BOOL bIsReleased;
   mbr->IsReleased(metStart,mbrReleaseMz,&bIsReleased);
   dlg.m_bReleaseMzAtStart = bIsReleased == VARIANT_TRUE ? TRUE : FALSE;
   mbr->IsReleased(metEnd,mbrReleaseMz,&bIsReleased);
   dlg.m_bReleaseMzAtEnd = bIsReleased == VARIANT_TRUE ? TRUE : FALSE;
   mbr->get_EA(&dlg.m_EA);
   mbr->get_EI(&dlg.m_EI);
   JointIDType jntID;
   mbr->get_StartJoint(&jntID);
   dlg.m_StartJoint = jntID-1;

   mbr->get_EndJoint(&jntID);
   dlg.m_EndJoint = jntID-1;

   if ( dlg.DoModal() == IDOK )
   {
      mbr->ReleaseEnd(metStart, dlg.m_bReleaseMzAtStart ? mbrReleaseMz : mbrReleaseNone);
      mbr->ReleaseEnd(metEnd,   dlg.m_bReleaseMzAtEnd   ? mbrReleaseMz : mbrReleaseNone);
      mbr->put_EA(dlg.m_EA);
      mbr->put_EI(dlg.m_EI);
      mbr->put_StartJoint( dlg.m_StartJoint + 1 );
      mbr->put_EndJoint(   dlg.m_EndJoint   + 1 );
   }
}
