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

CMemberDropSite::CMemberDropSite(CFEA2DDoc* pDoc):
m_DispObj(0)
{
   m_pDoc = pDoc;
}

CMemberDropSite::~CMemberDropSite()
{

}

BEGIN_INTERFACE_MAP(CMemberDropSite,CCmdTarget)
   INTERFACE_PART(CMemberDropSite,IID_iDisplayObjectEvents,DisplayObjectEvents)
   INTERFACE_PART(CMemberDropSite,IID_iDropSite,DropSite)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CMemberDropSite,DisplayObjectEvents);
DELEGATE_CUSTOM_INTERFACE(CMemberDropSite,DropSite);

STDMETHODIMP_(void) CMemberDropSite::XDisplayObjectEvents::OnChanged(iDisplayObject* pDO)
{
   ASSERT(FALSE); // Member display objects don't have internal data that can be changed
}

STDMETHODIMP_(void) CMemberDropSite::XDisplayObjectEvents::OnDragMoved(iDisplayObject* pDO,ISize2d* offset)
{
   ASSERT(FALSE); // Member shouldn't get moved
}

STDMETHODIMP_(void) CMemberDropSite::XDisplayObjectEvents::OnMoved(iDisplayObject* pDO)
{
   ASSERT(FALSE); // Member shouldn't get moved
}

STDMETHODIMP_(void) CMemberDropSite::XDisplayObjectEvents::OnCopied(iDisplayObject* pDO)
{
   ASSERT(FALSE); // Member shouldn't get copied
}

STDMETHODIMP_(bool) CMemberDropSite::XDisplayObjectEvents::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);

   // Member got double clicked on... Display its editing dialog
   long id = pDO->GetID();
   pThis->EditMember(id);

   return true;
}

STDMETHODIMP_(bool) CMemberDropSite::XDisplayObjectEvents::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   CComPtr<iDisplayList> list;
   pDO->GetDisplayList(&list);

   CComPtr<iDisplayMgr> dispMgr;
   list->GetDisplayMgr(&dispMgr);

   // If control key is pressed, don't clear current selection
   // (i.e. we want multi-select)
   BOOL bMultiSelect = nFlags & MK_CONTROL ? TRUE : FALSE;
   
   if ( bMultiSelect )
   {
      // clear all selected objects that aren't part of the member list
      dispMgr->ClearSelectedObjectsByList(MBR_LIST,atByID,FALSE);
   }

   dispMgr->SelectObject(pDO,!bMultiSelect);

   return true;
}

STDMETHODIMP_(bool) CMemberDropSite::XDisplayObjectEvents::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CMemberDropSite::XDisplayObjectEvents::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CMemberDropSite::XDisplayObjectEvents::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CMemberDropSite::XDisplayObjectEvents::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CMemberDropSite::XDisplayObjectEvents::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CMemberDropSite::XDisplayObjectEvents::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(void) CMemberDropSite::XDisplayObjectEvents::OnSelect(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);

   CComPtr<iDisplayList> list;
   pDO->GetDisplayList(&list);

   CComPtr<iDisplayMgr> dispMgr;
   list->GetDisplayMgr(&dispMgr);

   // Create a dimension line display object with in-place editable text
   // 1. Get the sockets for the line display object that represents the member
   CComQIPtr<iConnector,&IID_iConnector> connector(pDO);
   CComPtr<iPlug> startPlug;
   CComPtr<iPlug> endPlug;
   connector->GetStartPlug(&startPlug);
   connector->GetEndPlug(&endPlug);

   CComPtr<iSocket> startSocket;
   CComPtr<iSocket> endSocket;
   startPlug->GetSocket(&startSocket);
   endPlug->GetSocket(&endSocket);

   // 2. Create the dimension line display object
   //    Hook onto its connector interface
   CComPtr<iDimensionLine> dimLine;
   ::CoCreateInstance(CLSID_DimensionLineDisplayObject,NULL,CLSCTX_ALL,IID_iDimensionLine,(void**)&dimLine);
   connector.Release();
   dimLine->QueryInterface(IID_iConnector,(void**)&connector);

   // 3. Attach its plugs to the same sockets the line display object is using
   startPlug.Release();
   endPlug.Release();
   connector->GetStartPlug(&startPlug);
   connector->GetEndPlug(&endPlug);

   DWORD dwCookie;
   startSocket->Connect(startPlug,&dwCookie);
   endSocket->Connect(endPlug,&dwCookie);

   // 4. Attach an inplace editable text block to the dimension line
   CComPtr<iEditableTextBlock> textBlock;
   ::CoCreateInstance(CLSID_EditableTextBlock,NULL,CLSCTX_ALL,IID_iEditableTextBlock,(void**)&textBlock);
   dimLine->SetTextBlock(textBlock);
   dimLine->EnableAutoText(TRUE);

   // 5. Create an event sink and attach it to the dimension line
   CEditMbrLength* pEdit = new CEditMbrLength(pThis->m_pDoc);
   CComPtr<iDisplayObjectEvents> pDOE = (iDisplayObjectEvents*)pEdit->GetInterface(&IID_iDisplayObjectEvents);
   dimLine->RegisterEventSink(pDOE);

   // 6. Assign the member ID to the dimension line display object
   long mbrID = pDO->GetID();
   dimLine->SetID(mbrID);

   // 7. Add the new display object to the display
   dispMgr->AddDisplayObject(dimLine,DIMLINE_LIST,atByID);
}

STDMETHODIMP_(void) CMemberDropSite::XDisplayObjectEvents::OnUnselect(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);

   CComPtr<iDisplayList> list;
   pDO->GetDisplayList(&list);

   CComPtr<iDisplayMgr> dispMgr;
   list->GetDisplayMgr(&dispMgr);

   list.Release();
   dispMgr->FindDisplayList(DIMLINE_LIST,&list);
   list->Clear();
}

STDMETHODIMP_(bool) CMemberDropSite::XDisplayObjectEvents::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);

   long id = pDO->GetID();
   switch (nChar)
   {
   case VK_RETURN:
      pThis->EditMember(id);
      break;

   case VK_DELETE:
      pThis->DeleteMember(id);
      break;
   }

   return true;
}

STDMETHODIMP_(bool) CMemberDropSite::XDisplayObjectEvents::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   METHOD_PROLOGUE(CMemberDropSite,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(DROPEFFECT) CMemberDropSite::XDropSite::CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,IPoint2d* point)
{
   METHOD_PROLOGUE(CMemberDropSite,DropSite);

   // Was a tool dragged over the member?
   CComPtr<iTool> tool;
   ::CoCreateInstance(CLSID_Tool,NULL,CLSCTX_ALL,IID_iTool,(void**)&tool);
   CComQIPtr<iDraggable,&IID_iDraggable> draggable(tool);

   if ( pDataObject->IsDataAvailable( draggable->Format() ) )
   {
      CComPtr<iDragDataSource> source;
      ::CoCreateInstance(CLSID_DragDataSource,NULL,CLSCTX_ALL,IID_iDragDataSource,(void**)&source);
      source->SetDataObject(pDataObject);
      draggable->OnDrop(source); // Rebuild the tool object from the data object
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

STDMETHODIMP_(void) CMemberDropSite::XDropSite::OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect,IPoint2d* point)
{
   METHOD_PROLOGUE(CMemberDropSite,DropSite);

   // Something was dropped on a display object that represents a member
   // in the fem model. We know that, because this object is a drop site
   // for just such a situation.

   // Let's see what was dropped

   // Was it a tool from the palette?
   CComPtr<iTool> tool;
   ::CoCreateInstance(CLSID_Tool,NULL,CLSCTX_ALL,IID_iTool,(void**)&tool);
   CComQIPtr<iDraggable,&IID_iDraggable> draggable(tool);
   if ( pDataObject->IsDataAvailable(draggable->Format()) )
   {
      // Yes, but which one?
      CComPtr<iDragDataSource> source;
      ::CoCreateInstance(CLSID_DragDataSource,NULL,CLSCTX_ALL,IID_iDragDataSource,(void**)&source);
      source->SetDataObject(pDataObject);

      draggable->OnDrop(source); // Rebuild the tool object from the data object
#pragma Reminder("Use a factory for the line above")

      // Was it the concentrated load tool?
      if ( tool->GetID() == IDC_CONCLOAD_TOOL )
      {
         // Yes...

         // An Add Point Load tool was dropped. Create a new point load
         // on the member the tool was dropped on.
         CComPtr<iDisplayObject> pDispObj;
         GetDisplayObject(&pDispObj);
         long mbrID = pDispObj->GetID();

         CComPtr<IFem2dModel> model = pThis->m_pDoc->m_Model;
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
               CollectionIndexType count;
               pointLoads->get_Count(&count);
               pointLoads->Create(count,dlg.m_MbrID,dlg.m_Location,dlg.m_Fx,dlg.m_Fy,dlg.m_Mz,lotGlobal,&ptLoad);
            }
            catch(...)
            {
               AfxMessageBox("Failed to create load");
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
      CComPtr<iPointDisplayObject> loadRep;
      ::CoCreateInstance(CLSID_PointDisplayObject,NULL,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&loadRep);

      // Associate a drag data object with it
      CPointLoadEventsImpl* pEvents = new CPointLoadEventsImpl(pThis->m_pDoc);
      CComQIPtr<iDragData,&IID_iDragData> dd(pEvents->GetInterface(&IID_IUnknown));
      CComQIPtr<iDraggable,&IID_iDraggable> draggable(loadRep);
      draggable->SetDragData(dd);

      // create a data source and associate the data object with it
      CComPtr<iDragDataSource> source;
      ::CoCreateInstance(CLSID_DragDataSource,NULL,CLSCTX_ALL,IID_iDragDataSource,(void**)&source);
      source->SetDataObject(pDataObject);

      // rebuild the display object from the data source
      draggable->OnDrop(source);
      //////////////// END HERE

      // Create a new load in the fem model
      CComPtr<IFem2dLoadingCollection> loadings;
      pThis->m_pDoc->m_Model->get_Loadings(&loadings);
      CComPtr<IFem2dLoading> loading;
      loadings->Find(pEvents->m_Loading,&loading);
      if ( loading == NULL )
      {
         loadings->Create(pEvents->m_Loading,&loading);
      }

      CComPtr<IFem2dPointLoadCollection> ptLoads;
      loading->get_PointLoads(&ptLoads);
      CollectionIndexType id;
      ptLoads->get_Count(&id);

      try
      {
         CComPtr<IFem2dPointLoad> ptLoad;
         ptLoads->Create(id,pThis->m_DispObj->GetID(),pEvents->m_Location,pEvents->m_Fx,pEvents->m_Fy,pEvents->m_Mz, pEvents->m_Orientation,&ptLoad);
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
         AfxMessageBox("Failed to create load");
      }
   }
}

STDMETHODIMP_(void) CMemberDropSite::XDropSite::SetDisplayObject(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CMemberDropSite,DropSite);
   pThis->m_DispObj = pDO;
}

STDMETHODIMP_(void) CMemberDropSite::XDropSite::GetDisplayObject(iDisplayObject** dispObj)
{
   METHOD_PROLOGUE(CMemberDropSite,DropSite);
   *dispObj = pThis->m_DispObj;
   (*dispObj)->AddRef();
}

STDMETHODIMP_(void) CMemberDropSite::XDropSite::Highlite(CDC* pDC,BOOL bHighlite)
{
   METHOD_PROLOGUE(CMemberDropSite,DropSite);
   pThis->m_DispObj->Highlite(pDC,bHighlite);
}


void CMemberDropSite::DeleteMember(long mbrID)
{
   CComPtr<IFem2dModel> model = m_pDoc->m_Model;
   CComPtr<IFem2dMemberCollection> members;
   model->get_Members(&members);

   MemberIDType removedID;
   members->Remove(mbrID,atID,&removedID);
}

void CMemberDropSite::EditMember(long mbrID)
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
   mbr->IsReleased(metStart,&bIsReleased);
   dlg.m_bReleaseMzAtStart = bIsReleased == VARIANT_TRUE ? TRUE : FALSE;
   mbr->IsReleased(metEnd,&bIsReleased);
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
