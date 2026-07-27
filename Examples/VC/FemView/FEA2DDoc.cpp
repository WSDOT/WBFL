// FEA2DDoc.cpp : implementation of the CFEA2DDoc class
//

#include "stdafx.h"
#include "FEA2D.h"

#include "FEA2DDoc.h"

#include "ModelPropertiesDlg.h"

#include <MathEx.h>
#include <Units\Units.h>
#include <System\FileStream.h>
#include <System\StructuredSaveXml.h>
#include <System\StructuredLoadXml.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID(_id_) _T("'") << (_id_+1) << _T("'")

using namespace WBFL::Units;

/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc

IMPLEMENT_DYNCREATE(CFEA2DDoc, CDocument)

BEGIN_MESSAGE_MAP(CFEA2DDoc, CDocument)
	//{{AFX_MSG_MAP(CFEA2DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
   ON_COMMAND(ID_VIEW_MODEL, &CFEA2DDoc::OnViewModelProperties)
   ON_COMMAND(ID_GTSTRUDL,&CFEA2DDoc::OnGTStrudl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc construction/destruction

CFEA2DDoc::CFEA2DDoc()
{
   m_Model = std::make_unique<WBFL::FEA2D::Model>();
}

CFEA2DDoc::~CFEA2DDoc()
{
}

BOOL CFEA2DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc serialization

void CFEA2DDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc diagnostics

#ifdef _DEBUG
void CFEA2DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFEA2DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc commands

BOOL CFEA2DDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;

	// TODO: Add your specialized creation code here
   WBFL::System::FileStream file;
   file.open(lpszPathName, /*read=*/true);
   WBFL::System::StructuredLoadXml load;
   load.BeginLoad(&file);

   m_Model->Load(&load);

   load.EndLoad();

	return TRUE;
}

BOOL CFEA2DDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class
   WBFL::System::FileStream file;
   file.open(lpszPathName, /*read=*/false);
   WBFL::System::StructuredSaveXml save;
   save.BeginSave(&file);

   m_Model->Save(&save);

   save.EndSave();

   SetModifiedFlag(FALSE);

   return TRUE;
//	return CDocument::OnSaveDocument(lpszPathName);
}

void CFEA2DDoc::OnModelChanged()
{
   SetModifiedFlag(TRUE);
   UpdateAllViews(0,1,0);
}

void CFEA2DDoc::OnLoadingChanged(LoadCaseIDType id)
{
   SetModifiedFlag(TRUE);
   UpdateAllViews(0,2,0);
}

void CFEA2DDoc::OnViewModelProperties()
{
   // TODO: Add your command handler code here
   CModelPropertiesDlg dlg(_T("Model Properties"));
   dlg.m_pFem2d = m_Model.get();
   dlg.DoModal();
}

void CFEA2DDoc::OnGTStrudl()
{
   CString strName;
   strName.Format(_T("%s.gti"),m_Model->GetName().c_str());

   std::_tofstream ofile(strName);

   ofile << _T("STRUDL") << std::endl;
   ofile << _T("TYPE PLANE FRAME XY") << std::endl;
   ofile << _T("UNITS FEET KIP DEG FAH") << std::endl;

   // Joint Coordinates
   ofile << _T("JOINT COORDINATES GLOBAL") << std::endl;
   IndexType nJoints = m_Model->GetJointCount();
   for ( IndexType jntIdx = 0; jntIdx < nJoints; jntIdx++ )
   {
      WBFL::FEA2D::Joint* joint = m_Model->FindJointByIndex(jntIdx);
      Float64 x = joint->GetX();
      Float64 y = joint->GetY();

      JointIDType id = joint->GetID();

      x = ::ConvertFromSysUnits(x, Measure::Feet);
      y = ::ConvertFromSysUnits(y, Measure::Feet);
      ofile << ID(id) << _T(" ") << x << _T(" ") << y << std::endl;
   }

   // Status Support
   ofile << _T("STATUS SUPPORT");
   for ( IndexType jntIdx = 0; jntIdx < nJoints; jntIdx++ )
   {
      WBFL::FEA2D::Joint* joint = m_Model->FindJointByIndex(jntIdx);

      if ( joint->IsSupport() )
      {
         JointIDType id = joint->GetID();

         ofile << _T(" ") << ID(id);
      }
   }
   ofile << std::endl;

   // Joint Releases
   ofile << _T("JOINT RELEASES") << std::endl;
   for ( IndexType jntIdx = 0; jntIdx < nJoints; jntIdx++ )
   {
      WBFL::FEA2D::Joint* joint = m_Model->FindJointByIndex(jntIdx);

      if ( joint->IsSupport() )
      {
         JointIDType id = joint->GetID();

         bool bFx = joint->IsDofReleased(WBFL::FEA2D::JointReleaseType::Fx);
         bool bFy = joint->IsDofReleased(WBFL::FEA2D::JointReleaseType::Fy);
         bool bMz = joint->IsDofReleased(WBFL::FEA2D::JointReleaseType::Mz);

         if (bFx || bFy || bMz)
         {
            ofile << ID(id);
            if (bFx)
            {
               ofile << _T(" FORCE X");
            }

            if (bFy)
            {
               ofile << _T(" FORCE Y");
            }

            if (bMz)
            {
               ofile << _T(" MOMENT Z");
            }

            ofile << std::endl;
         }
      }
   }

   // Member Incidences
   ofile << _T("MEMBER INCIDENCES") << std::endl;
   IndexType nMembers = m_Model->GetMemberCount();
   for ( IndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++ )
   {
      WBFL::FEA2D::Member* member = m_Model->FindMemberByIndex(mbrIdx);

      MemberIDType mbrID = member->GetID();

      JointIDType startJnt = member->GetStartJoint();
      JointIDType endJnt = member->GetEndJoint();

      ofile << ID(mbrID) << _T(" ") << ID(startJnt) << _T(" ") << ID(endJnt) << std::endl;
   }

   // Member Releases
   ofile << _T("MEMBER RELEASES") << std::endl;
   for (IndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++)
   {
      WBFL::FEA2D::Member* member = m_Model->FindMemberByIndex(mbrIdx);

      MemberIDType mbrID = member->GetID();

      bool bReleaseStartFx = member->IsReleased(WBFL::FEA2D::MemberEndType::Start, WBFL::FEA2D::MemberReleaseType::Fx);
      bool bReleaseEndFx   = member->IsReleased(WBFL::FEA2D::MemberEndType::End,   WBFL::FEA2D::MemberReleaseType::Fx);

      bool bReleaseStartMz = member->IsReleased(WBFL::FEA2D::MemberEndType::Start, WBFL::FEA2D::MemberReleaseType::Mz);
      bool bReleaseEndMz   = member->IsReleased(WBFL::FEA2D::MemberEndType::End,   WBFL::FEA2D::MemberReleaseType::Mz);

      if (bReleaseStartFx || bReleaseEndFx || bReleaseStartMz || bReleaseEndMz)
      {
         ofile << ID(mbrID);
         if (bReleaseStartFx || bReleaseStartMz)
         {
            ofile << _T(" START");
            if (bReleaseStartFx)
            {
               ofile << _T(" FORCE X");
            }

            if (bReleaseStartMz)
            {
               ofile << _T(" MOMENT Z");
            }
         }

         if (bReleaseEndFx || bReleaseEndMz)
         {
            ofile << _T(" END");
            if (bReleaseEndFx)
            {
               ofile << _T(" FORCE X");
            }

            if (bReleaseEndMz)
            {
               ofile << _T(" MOMENT Z");
            }
         }
         ofile << std::endl;
      }
   }

   // Member Properties
   ofile << _T("UNITS INCH KIP DEG FAH") << std::endl;
   ofile << _T("MEMBER PROPERTIES PRISMATIC") << std::endl;
   ofile << _T("$ WSDOT Internal FEM model has EA and EI. Strudl wants E, A, and I.") << std::endl;
   ofile << _T("$ The properties below for A are really EA (kip) and I are really EI (kip*in^2).") << std::endl;
   ofile << _T("$ E will be set to 1.0 below.") << std::endl;
   for ( IndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++ )
   {
      WBFL::FEA2D::Member* member = m_Model->FindMemberByIndex(mbrIdx);

      MemberIDType mbrID = member->GetID();

      Float64 EA = member->GetEA();
      Float64 EI = member->GetEI();

      // (ksi)*(in2) = kip
      EA = ::ConvertFromSysUnits(EA, Measure::Kip);

      // (ksi)*(in4) = kip*in2
      EI = ::ConvertFromSysUnits(EI, Measure::KipInch2);
      ofile << ID(mbrID) << _T(" AX ") << EA << _T(" IZ ") << EI << std::endl;
   }
   ofile << _T("UNITS FEET KIP DEG FAH") << std::endl;

   // Constants
   ofile << _T("UNITS INCH KIP DEG FAH") << std::endl;
   ofile << _T("CONSTANTS") << std::endl;
   ofile << _T("$ E is set to 1.0 KSI. See comments above for section properties") << std::endl;
   ofile << _T("E 1.0 ALL") << std::endl;
   ofile << _T("G 1.0 ALL") << std::endl;
   ofile << _T("POI 0.3 ALL") << std::endl;
   ofile << _T("DEN 1.0 ALL") << std::endl;
   ofile << _T("UNITS FEET KIP DEG FAH") << std::endl;

   // Loads
   IndexType nLoadings = m_Model->GetLoadingCount();
   for ( IndexType ldIdx = 0; ldIdx < nLoadings; ldIdx++ )
   {
      WBFL::FEA2D::Loading* loading = m_Model->FindLoadingByIndex(ldIdx);

      LoadCaseIDType lcID = loading->GetID();

      ofile << _T("LOADING ") << ID(abs((int)lcID)) << std::endl;
      ofile << _T("MEMBER LOADS") << std::endl;

      IndexType nLoads = loading->GetDistributedLoadCount();
      for ( IndexType idx = 0; idx < nLoads; idx++ )
      {
         WBFL::FEA2D::DistributedLoad* load = loading->FindDistributedLoadByIndex(idx);

         MemberIDType mbrID = load->GetMemberID();

         Float64 xStart = load->GetStartLocation();
         Float64 xEnd   = load->GetEndLocation();
         Float64 wStart = load->GetWStart();
         Float64 wEnd   = load->GetWEnd();

         xStart = ::ConvertFromSysUnits(xStart, Measure::Feet);
         xEnd = ::ConvertFromSysUnits(xEnd, Measure::Feet);
         wStart = ::ConvertFromSysUnits(wStart, Measure::KipPerFoot);
         wEnd = ::ConvertFromSysUnits(wEnd, Measure::KipPerFoot);

         if (!IsZero(wStart) && !IsZero(wEnd))
         {
            if (xStart < 0 && xEnd < 0)
            {
               ofile << ID(mbrID) << _T(" FORCE Y LINEAR FRA WA ") << wStart << _T(" WB ") << wEnd << _T(" LA ") << fabs(xStart) << _T(" LB ") << fabs(xEnd) << std::endl;
            }
            else
            {
               ofile << ID(mbrID) << _T(" FORCE Y LINEAR WA ") << wStart << _T(" WB ") << wEnd << _T(" LA ") << fabs(xStart) << _T(" LB ") << fabs(xEnd) << std::endl;
            }
         }
      }

      IndexType nPtLoads = loading->GetPointLoadCount();
      for ( IndexType idx = 0; idx < nPtLoads; idx++ )
      {
         WBFL::FEA2D::PointLoad* load = loading->FindPointLoadByIndex(idx);

         MemberIDType mbrID = load->GetMemberID();

         Float64 Fx, Fy, Mz;
         load->GetForce(&Fx,&Fy,&Mz);
         Float64 X = load->GetLocation();

         X = ::ConvertFromSysUnits(X, Measure::Feet);
         Fy = ::ConvertToSysUnits(Fy, Measure::Kip);

         if ( !IsZero(Fy) )
         {
            if ( X < 0 )
            {
               ofile << ID(mbrID) << _T(" FORCE Y CONC FRA P ") << Fy << _T(" L ") << X << std::endl;
            }
            else
            {
               ofile << ID(mbrID) << _T(" FORCE Y CONC P ") << Fy << _T(" L ") << X << std::endl;
            }
         }
      }
   }

   ofile.close();
}
