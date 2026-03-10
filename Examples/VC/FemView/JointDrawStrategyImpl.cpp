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

void CJointDrawStrategyImpl::SetJoint(IFem2dJoint* joint)
{
   m_Joint = joint;
}

void CJointDrawStrategyImpl::Draw(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC) const
{
   auto pDL = pDO->GetDisplayList();

   auto pDispMgr = pDL->GetDisplayMgr();

   COLORREF color;

   if ( pDO->IsSelected() )
      color = pDispMgr->GetSelectionLineColor();
   else
      color = RGB(0,255,0);

   auto pos = pDO->GetPosition();

   Draw(pDO,pDC,color,pos);
}

void CJointDrawStrategyImpl::DrawHighlight(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC,bool bHighlite) const
{
   Draw(pDO,pDC);
}

void CJointDrawStrategyImpl::DrawDragImage(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& cpdragPoint) const
{
   auto dragPoint = map->LPtoWP(cpdragPoint.x, cpdragPoint.y);

   // Draw the joint
   Draw(pDO,pDC,RGB(255,0,0),dragPoint);

   // Draw the members that attach to the joint
   CComPtr<IFem2dModel> model = m_pDoc->m_Model;
   CComPtr<IFem2dJointCollection> joints;
   model->get_Joints(&joints);

   CComPtr<IFem2dMemberCollection> members;
   model->get_Members(&members);

   JointIDType jntID = pDO->GetID();
   CComPtr<IFem2dJoint> joint;
   joints->Find(jntID,&joint);

   CComPtr<IIDArray> mbrIDs;
   joint->get_Members(&mbrIDs);

   IndexType count;
   mbrIDs->get_Count(&count);
   for ( IndexType i = 0; i < count; i++ )
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

WBFL::Geometry::Rect2d CJointDrawStrategyImpl::GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const
{
   Float64 px, py;
   m_Joint->get_X(&px);
   m_Joint->get_Y(&py);

   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();
   auto pMap = pDispMgr->GetCoordinateMap();

   double xo,yo;
   pMap->TPtoWP(0,0,&xo,&yo);
   double x2,y2;
   pMap->TPtoWP(SSIZE,SSIZE,&x2,&y2);

   double wid = fabs(x2-xo)/2.0;
   double hgt = fabs(y2-yo)/2.0;

   return WBFL::Geometry::Rect2d(px-wid,py-hgt,px+wid,py+hgt);
}

void CJointDrawStrategyImpl::Draw(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC,COLORREF color,const WBFL::Geometry::Point2d& loc) const
{
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();

   auto pMap = pDispMgr->GetCoordinateMap();

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


   CFont font;
   font.CreatePointFont(80, _T("Arial"), pDC);
   CFont* old_font = pDC->SelectObject(&font);
   JointIDType id;
   joint->get_ID(&id);
   CString strnum;
   strnum.Format(_T("%d"), id);
   pDC->SetTextAlign(TA_BOTTOM | TA_CENTER);
   pDC->TextOut(cx, cy + hgt / 5, strnum);
   pDC->SelectObject(old_font);

   VARIANT_BOOL bIsSupport;
   joint->IsSupport(&bIsSupport);
   if ( bIsSupport == VARIANT_FALSE )
   {
      // Not a support... Draw an O and return
      //CRect rect(cx-wid/5,cy-hgt/5,cx+wid/5,cy+hgt/5);

      //pDC->Ellipse(rect);

      pDC->MoveTo(cx,cy-hgt/5);
      pDC->LineTo(cx,cy+hgt/5);
      
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
      pDC->MoveTo(cx-wid,cy+5);
      pDC->LineTo(cx,cy+5);
      
      pDC->MoveTo(cx-wid/4,cy+hgt/4);
      pDC->LineTo(cx,cy+5);
      
      pDC->MoveTo(cx-wid/4,cy-hgt/4);
      pDC->LineTo(cx,cy+5);
   }

   if ( bFyReleased == VARIANT_FALSE )
   {
      // Supported in the Y direction
      pDC->MoveTo(cx,cy+hgt+5);
      pDC->LineTo(cx,cy+5);
      
      pDC->MoveTo(cx-wid/4,cy+hgt/4+5);
      pDC->LineTo(cx,cy+5);
      
      pDC->MoveTo(cx+wid/4,cy+hgt/4+5);
      pDC->LineTo(cx,cy+5);
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
