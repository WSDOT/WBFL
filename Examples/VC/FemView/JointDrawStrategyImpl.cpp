#include "stdafx.h"
#include "FEA2D.h"
#include "FEA2DDoc.h"
#include "JointDrawStrategyImpl.h"
#include "mfcdual.h"
#include <Math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// make our symbols 3/8" in size
static const long SSIZE = 1440 * 3/8; // (twips)

CJointDrawStrategyImpl::CJointDrawStrategyImpl(CFEA2DDoc* pDoc)
{
   m_pDoc = pDoc;
}

BEGIN_INTERFACE_MAP(CJointDrawStrategyImpl,CCmdTarget)
   INTERFACE_PART(CJointDrawStrategyImpl,IID_iDrawPointStrategy,DrawPointStrategy)
   INTERFACE_PART(CJointDrawStrategyImpl,IID_iJointDrawStrategy,Strategy)
END_INTERFACE_MAP()

DELEGATE_CUSTOM_INTERFACE(CJointDrawStrategyImpl,DrawPointStrategy);
DELEGATE_CUSTOM_INTERFACE(CJointDrawStrategyImpl,Strategy);

STDMETHODIMP_(void) CJointDrawStrategyImpl::XStrategy::SetJoint(IFem2dJoint* joint)
{
   METHOD_PROLOGUE(CJointDrawStrategyImpl,Strategy)

   pThis->m_Joint = joint;
}

STDMETHODIMP_(void) CJointDrawStrategyImpl::XDrawPointStrategy::Draw(iPointDisplayObject* pDO,CDC* pDC)
{
   METHOD_PROLOGUE(CJointDrawStrategyImpl,DrawPointStrategy);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   COLORREF color;

   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();
   else
      color = RGB(0,255,0);

   CComPtr<IPoint2d> pos;
   pDO->GetPosition(&pos);

   pThis->Draw(pDO,pDC,color,pos);
}

STDMETHODIMP_(void) CJointDrawStrategyImpl::XDrawPointStrategy::DrawHighlite(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   METHOD_PROLOGUE(CJointDrawStrategyImpl,DrawPointStrategy);
   Draw(pDO,pDC);
}

STDMETHODIMP_(void) CJointDrawStrategyImpl::XDrawPointStrategy::DrawDragImage(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& cpdragPoint)
{
   METHOD_PROLOGUE(CJointDrawStrategyImpl,DrawPointStrategy);

   CComPtr<IPoint2d> dragPoint;
   map->LPtoWP(cpdragPoint.x, cpdragPoint.y, &dragPoint);

   // Draw the joint
   pThis->Draw(pDO,pDC,RGB(255,0,0),dragPoint);

   // Draw the members that attach to the joint
   CComPtr<IFem2dModel> model = pThis->m_pDoc->m_Model;
   CComPtr<IFem2dJointCollection> joints;
   model->get_Joints(&joints);

   CComPtr<IFem2dMemberCollection> members;
   model->get_Members(&members);

   JointIDType jntID = pDO->GetID();
   CComPtr<IFem2dJoint> joint;
   joints->Find(jntID,&joint);

   CComPtr<ILongArray> mbrIDs;
   joint->get_Members(&mbrIDs);

   CollectionIndexType count;
   mbrIDs->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      MemberIDType mbrID;
      mbrIDs->get_Item(i,&mbrID);

      CComPtr<IFem2dMember> member;
      members->Find(mbrID,&member);

      JointIDType startJntID, endJntID;
      member->get_StartJoint(&startJntID);
      member->get_EndJoint(&endJntID);

      CComPtr<IFem2dJoint> startJoint, endJoint;
      joints->Find(startJntID,&startJoint);
      joints->Find(endJntID,  &endJoint);

      CPoint start, end;
      if ( startJntID == jntID )
      {
         map->WPtoLP(dragPoint,&start.x,&start.y);
      }
      else
      {
         Float64 x,y;
         startJoint->get_X(&x);
         startJoint->get_Y(&y);
         map->WPtoLP(x,y,&start.x,&start.y);
      }

      if ( endJntID == jntID )
      {
         map->WPtoLP(dragPoint,&end.x,&end.y);
      }
      else
      {
         Float64 x,y;
         endJoint->get_X(&x);
         endJoint->get_Y(&y);
         map->WPtoLP(x,y,&end.x,&end.y);
      }

      pDC->MoveTo(start);
      pDC->LineTo(end);
   }
}

STDMETHODIMP_(void) CJointDrawStrategyImpl::XDrawPointStrategy::GetBoundingBox(iPointDisplayObject* pDO,IRect2d** ppRect)
{
   METHOD_PROLOGUE(CJointDrawStrategyImpl,DrawPointStrategy);

   Float64 px, py;
   pThis->m_Joint->get_X(&px);
   pThis->m_Joint->get_Y(&py);

   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);
   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);
   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   double xo,yo;
   pMap->TPtoWP(0,0,&xo,&yo);
   double x2,y2;
   pMap->TPtoWP(SSIZE,SSIZE,&x2,&y2);

   double wid = fabs(x2-xo)/2.0;
   double hgt = fabs(y2-yo)/2.0;

   CComPtr<IRect2d> rect;
   rect.CoCreateInstance(CLSID_Rect2d);

   rect->put_Left(px-wid);
   rect->put_Bottom(py-hgt);
   rect->put_Right(px+wid);
   rect->put_Top(py+hgt);

   (*ppRect) = rect;
   (*ppRect)->AddRef();
}

void CJointDrawStrategyImpl::Draw(iPointDisplayObject* pDO,CDC* pDC,COLORREF color,IPoint2d* loc)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   long cx,cy;
   pMap->WPtoLP(loc,&cx,&cy);

   // height and width
   long xo,yo;
   pMap->TPtoLP(0,0,&xo,&yo);
   long x2,y2;
   pMap->TPtoLP(SSIZE,SSIZE,&x2,&y2);
   long wid = abs(x2-xo)/2;
   long hgt = abs(y2-yo)/2;

   CPen pen(PS_SOLID,1,color);
   CPen* pOldPen = pDC->SelectObject(&pen);

   CComPtr<IFem2dModel> model = m_pDoc->m_Model;
   CComPtr<IFem2dJointCollection> joints;
   model->get_Joints(&joints);

   JointIDType jntID = pDO->GetID();
   CComPtr<IFem2dJoint> joint;
   joints->Find(jntID,&joint);

   VARIANT_BOOL bIsSupport;
   joint->IsSupport(&bIsSupport);
   if ( bIsSupport == VARIANT_FALSE )
   {
      // Not a support... Draw an O and return
      CRect rect(cx-wid/2,cy-hgt/2,cx+wid/2,cy+hgt/2);

      pDC->Ellipse(rect);

      pDC->SelectObject(pOldPen);
      return;
   }

   // This is a support... Found out which DOF are actually supported
   VARIANT_BOOL bFxReleased;
   joint->IsDofReleased(jrtFx,&bFxReleased);

   VARIANT_BOOL bFyReleased;
   joint->IsDofReleased(jrtFy,&bFyReleased);

   VARIANT_BOOL bMzReleased;
   joint->IsDofReleased(jrtMz,&bMzReleased);

   if ( bFxReleased == VARIANT_FALSE )
   {
      // Supported in the X direction
      pDC->MoveTo(cx-wid,cy);
      pDC->LineTo(cx,cy);
      
      pDC->MoveTo(cx-wid/4,cy+hgt/4);
      pDC->LineTo(cx,cy);
      
      pDC->MoveTo(cx-wid/4,cy-hgt/4);
      pDC->LineTo(cx,cy);
   }

   if ( bFyReleased == VARIANT_FALSE )
   {
      // Supported in the Y direction
      pDC->MoveTo(cx,cy+hgt);
      pDC->LineTo(cx,cy);
      
      pDC->MoveTo(cx-wid/4,cy+hgt/4);
      pDC->LineTo(cx,cy);
      
      pDC->MoveTo(cx+wid/4,cy+hgt/4);
      pDC->LineTo(cx,cy);
   }

   if ( bMzReleased == VARIANT_FALSE )
   {
      // Moment support
      pDC->Arc(CRect(CPoint(cx-wid/2,cy-hgt/2),CSize(wid,hgt)),
               CPoint(cx-wid/2,cy),CPoint(cx+wid/2,cy));

      pDC->MoveTo(CPoint(cx+wid/2,cy));
      pDC->LineTo(CPoint(cx+wid/2-wid/4,cy+hgt/4));

      pDC->MoveTo(CPoint(cx+wid/2,cy));
      pDC->LineTo(CPoint(cx+wid/2+wid/4,cy+hgt/4));
   }

   pDC->SelectObject(pOldPen);
}
