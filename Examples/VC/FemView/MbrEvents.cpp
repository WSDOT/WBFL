// MbrEvents.cpp: implementation of the CMbrEvents class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FEA2D.h"
#include "MbrEvents.h"

#include "MainFrm.h"
#include "FEA2DDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMbrEvents::CMbrEvents()
{

}

CMbrEvents::~CMbrEvents()
{

}

void CMbrEvents::OnChanged(IDisplayObject* pDO)
{
}

void CMbrEvents::OnMoved(IDisplayObject* pDO,WBFLGeometry::ISize2dPtr offset)
{
}

void CMbrEvents::OnLButtonDblClk(IDisplayObject* pDO,UINT nFlags,CPoint point)
{
   CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

   // Get the active MDI child window.
   CMDIChildWnd *pChild = 
                (CMDIChildWnd *) pMainFrm->GetActiveFrame();


   CFEA2DDoc* pDoc = (CFEA2DDoc*)pChild->GetActiveDocument();


   WBFLFem2d::IModelPtr model = pDoc->m_Model;

   WBFLFem2d::ILoadingCollectionPtr lcases = model->Loadings;
   long count = lcases->Count;
   for ( long i = 0; i < count; i++ )
   {
      WBFLFem2d::ILoadingPtr lcase = lcases->Item[i];

      double Fx1,Fy1,Mz1;
      double Fx2,Fy2,Mz2;

      model->ComputeMemberForces(lcase->ID,pDO->GetID(),&Fx1,&Fy1,&Mz1,&Fx2,&Fy2,&Mz2);

      CString strMsg;
      strMsg.Format("Member %d\nLoading %d\nFx1 = %f, Fy1 = %f, Mz1 = %f\nFx2 = %f, Fy2 = %f, Mz2 = %f",
         pDO->GetID(),lcase->ID,Fx1,Fy1,Mz1,Fx2,Fy2,Mz2);

      AfxMessageBox(strMsg);
   }

}
