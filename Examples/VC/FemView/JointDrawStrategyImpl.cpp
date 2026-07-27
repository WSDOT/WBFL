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

void CJointDrawStrategyImpl::SetJoint(WBFL::FEA2D::Joint* joint)
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
   WBFL::FEA2D::Model* model = m_pDoc->m_Model.get();

   JointIDType jntID = pDO->GetID();

   std::vector<MemberIDType> mbrIDs = model->GetAttachedMembers(jntID);
   for ( MemberIDType mbrID : mbrIDs )
   {
      WBFL::FEA2D::Member* member = model->FindMember(mbrID);

      JointIDType startJntID = member->GetStartJoint();
      JointIDType endJntID = member->GetEndJoint();

      WBFL::FEA2D::Joint* startJoint = model->FindJoint(startJntID);
      WBFL::FEA2D::Joint* endJoint = model->FindJoint(endJntID);

      CPoint start, end;
      if ( startJntID == jntID )
      {
         map->WPtoLP(dragPoint,&start.x,&start.y);
      }
      else
      {
         Float64 x = startJoint->GetX();
         Float64 y = startJoint->GetY();
         map->WPtoLP(x,y,&start.x,&start.y);
      }

      if ( endJntID == jntID )
      {
         map->WPtoLP(dragPoint,&end.x,&end.y);
      }
      else
      {
         Float64 x = endJoint->GetX();
         Float64 y = endJoint->GetY();
         map->WPtoLP(x,y,&end.x,&end.y);
      }

      pDC->MoveTo(start);
      pDC->LineTo(end);
   }
}

WBFL::Geometry::Rect2d CJointDrawStrategyImpl::GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const
{
   Float64 px = m_Joint->GetX();
   Float64 py = m_Joint->GetY();

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

   WBFL::FEA2D::Model* model = m_pDoc->m_Model.get();

   JointIDType jntID = pDO->GetID();
   WBFL::FEA2D::Joint* joint = model->FindJoint(jntID);


   CFont font;
   font.CreatePointFont(80, _T("Arial"), pDC);
   CFont* old_font = pDC->SelectObject(&font);
   JointIDType id = joint->GetID();
   CString strnum;
   strnum.Format(_T("%d"), id);
   pDC->SetTextAlign(TA_BOTTOM | TA_CENTER);
   pDC->TextOut(cx, cy + hgt / 5, strnum);
   pDC->SelectObject(old_font);

   if ( !joint->IsSupport() )
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
   bool bFxReleased = joint->IsDofReleased(WBFL::FEA2D::JointReleaseType::Fx);
   bool bFyReleased = joint->IsDofReleased(WBFL::FEA2D::JointReleaseType::Fy);
   bool bMzReleased = joint->IsDofReleased(WBFL::FEA2D::JointReleaseType::Mz);

   if ( !bFxReleased )
   {
      // Supported in the X direction
      pDC->MoveTo(cx-wid,cy+5);
      pDC->LineTo(cx,cy+5);
      
      pDC->MoveTo(cx-wid/4,cy+hgt/4);
      pDC->LineTo(cx,cy+5);
      
      pDC->MoveTo(cx-wid/4,cy-hgt/4);
      pDC->LineTo(cx,cy+5);
   }

   if ( !bFyReleased )
   {
      // Supported in the Y direction
      pDC->MoveTo(cx,cy+hgt+5);
      pDC->LineTo(cx,cy+5);
      
      pDC->MoveTo(cx-wid/4,cy+hgt/4+5);
      pDC->LineTo(cx,cy+5);
      
      pDC->MoveTo(cx+wid/4,cy+hgt/4+5);
      pDC->LineTo(cx,cy+5);
   }

   if ( !bMzReleased )
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
