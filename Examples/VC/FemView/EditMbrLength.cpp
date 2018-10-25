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


BEGIN_MESSAGE_MAP(CEditMbrLength, CCmdTarget)
	//{{AFX_MSG_MAP(CEditMbrLength)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditMbrLength message handlers

BEGIN_INTERFACE_MAP(CEditMbrLength,CCmdTarget)
   INTERFACE_PART(CEditMbrLength,IID_iDisplayObjectEvents,DisplayObjectEvents)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CEditMbrLength,DisplayObjectEvents);

STDMETHODIMP_(void) CEditMbrLength::XDisplayObjectEvents::OnChanged(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   // The member length was in-place edited

   // Get the new length
   CComQIPtr<iDimensionLine,&IID_iDimensionLine> dimLine(pDO);
   CComPtr<iTextBlock> textBlock;
   dimLine->GetTextBlock(&textBlock);

   CComQIPtr<iEditableTextBlock,&IID_iEditableTextBlock> edTextBlock(textBlock);
   CString strText = edTextBlock->GetEditedText();

   double length = _tstof(strText);

   // Compute the new coordinates of the member end joint.
   MemberIDType mbrID = pDO->GetID();
   CComPtr<IFem2dModel> model = pThis->m_pDoc->m_Model;
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

STDMETHODIMP_(void) CEditMbrLength::XDisplayObjectEvents::OnDragMoved(iDisplayObject* pDO,ISize2d* offset)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
}

STDMETHODIMP_(void) CEditMbrLength::XDisplayObjectEvents::OnMoved(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
}

STDMETHODIMP_(void) CEditMbrLength::XDisplayObjectEvents::OnCopied(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
}

STDMETHODIMP_(bool) CEditMbrLength::XDisplayObjectEvents::OnLButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CEditMbrLength::XDisplayObjectEvents::OnLButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CEditMbrLength::XDisplayObjectEvents::OnRButtonDblClk(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CEditMbrLength::XDisplayObjectEvents::OnRButtonDown(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CEditMbrLength::XDisplayObjectEvents::OnRButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CEditMbrLength::XDisplayObjectEvents::OnLButtonUp(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CEditMbrLength::XDisplayObjectEvents::OnMouseMove(iDisplayObject* pDO,UINT nFlags,CPoint point)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CEditMbrLength::XDisplayObjectEvents::OnMouseWheel(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(void) CEditMbrLength::XDisplayObjectEvents::OnSelect(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
}

STDMETHODIMP_(void) CEditMbrLength::XDisplayObjectEvents::OnUnselect(iDisplayObject* pDO)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
}

STDMETHODIMP_(bool) CEditMbrLength::XDisplayObjectEvents::OnKeyDown(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   return false;
}

STDMETHODIMP_(bool) CEditMbrLength::XDisplayObjectEvents::OnContextMenu(iDisplayObject* pDO,CWnd* pWnd,CPoint point)
{
   METHOD_PROLOGUE(CEditMbrLength,DisplayObjectEvents);
   return false;
}
