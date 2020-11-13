// FEA2DDoc.cpp : implementation of the CFEA2DDoc class
//

#include "stdafx.h"
#include "FEA2D.h"

#include "FEA2DDoc.h"

#include "ModelPropertiesDlg.h"

#include <MathEx.h>
#include <UnitMgt\UnitMgt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID(_id_) _T("'") << (_id_+1) << _T("'")

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

BEGIN_DISPATCH_MAP(CFEA2DDoc,CDocument)
   DISP_FUNCTION(CFEA2DDoc,"OnModelChanged",OnModelChanged,VT_EMPTY,VTS_NONE)
   DISP_FUNCTION(CFEA2DDoc,"OnLoadingChanged",OnModelChanged,VT_EMPTY,VTS_I4)
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFEA2DDoc construction/destruction
LPUNKNOWN CFEA2DDoc::GetInterfaceHook(const void* piid)
{
   if ( ::IsEqualIID(__uuidof(IFem2dModelEvents), *(IID*)piid) )
      return GetInterface(&IID_IUnknown);
   else
      return NULL;
}

CFEA2DDoc::CFEA2DDoc()
{
   EnableAutomation();
   m_Model.CoCreateInstance(CLSID_Fem2dModel);
   IUnknown* pUnk = GetInterface(&IID_IUnknown);
   AfxConnectionAdvise(m_Model,__uuidof(IFem2dModelEvents),pUnk,TRUE,&m_dwCookie);
}

CFEA2DDoc::~CFEA2DDoc()
{
   IUnknown* pUnk = GetInterface(&IID_IUnknown);
   AfxConnectionUnadvise(m_Model,__uuidof(IFem2dModelEvents),pUnk,TRUE,m_dwCookie);
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
   CComPtr<IStructuredLoad2> pLoad;
   pLoad.CoCreateInstance(CLSID_StructuredLoad2);

   CComQIPtr<IStructuredStorage2> pSS(m_Model);

   pLoad->Open(CComBSTR(lpszPathName));

   pSS->Load(pLoad);

   pLoad->Close();
	
	return TRUE;
}

BOOL CFEA2DDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
   CComPtr<IStructuredSave2> pSave;
   pSave.CoCreateInstance(CLSID_StructuredSave2);
   pSave->Open(CComBSTR(lpszPathName));

   CComQIPtr<IStructuredStorage2> pSS(m_Model);
   pSS->Save(pSave);

   pSave->Close();

   SetModifiedFlag(FALSE);

   return TRUE;
//	return CDocument::OnSaveDocument(lpszPathName);
}

//STDMETHODIMP CFEA2DDoc::XModelEvents::OnModelChanged()
//{
//   return raw_OnModelChanged();
//}
//
//STDMETHODIMP CFEA2DDoc::XModelEvents::OnLoadingChanged(long id)
//{
//   return raw_OnLoadingChanged(id);
//}
//
//STDMETHODIMP CFEA2DDoc::XModelEvents::raw_OnModelChanged()
//{
//   METHOD_PROLOGUE(CFEA2DDoc,ModelEvents);
//   pThis->SetModifiedFlag(TRUE);
//   pThis->UpdateAllViews(0,1,0);
//   return S_OK;
//}
//
//STDMETHODIMP CFEA2DDoc::XModelEvents::raw_OnLoadingChanged(long id)
//{
//   METHOD_PROLOGUE(CFEA2DDoc,ModelEvents);
//    pThis->SetModifiedFlag(TRUE);
//  pThis->UpdateAllViews(0,2,0);
//   return S_OK;
//}

BOOL CFEA2DDoc::OnModelChanged()
{
   SetModifiedFlag(TRUE);
   UpdateAllViews(0,1,0);
   return S_OK;
}

BOOL CFEA2DDoc::OnLoadingChanged(long id)
{
   SetModifiedFlag(TRUE);
   UpdateAllViews(0,2,0);
   return S_OK;
}

void CFEA2DDoc::OnViewModelProperties()
{
   // TODO: Add your command handler code here
   CModelPropertiesDlg dlg(_T("Model Properties"));
   dlg.m_pFem2d = m_Model;
   dlg.DoModal();
}

void CFEA2DDoc::OnGTStrudl()
{
   USES_CONVERSION;
   CComBSTR bstrName;
   m_Model->get_Name(&bstrName);

   CString strName;
   strName.Format(_T("%s.gti"),OLE2T(bstrName));

   std::_tofstream ofile(strName);

   ofile << _T("STRUDL") << std::endl;
   ofile << _T("TYPE PLANE FRAME XY") << std::endl;
   ofile << _T("UNITS FEET KIP DEG FAH") << std::endl;

   // Joint Coordinates
   ofile << _T("JOINT COORDINATES GLOBAL") << std::endl;
   CComPtr<IFem2dJointCollection> joints;
   m_Model->get_Joints(&joints);
   CollectionIndexType nJoints;
   joints->get_Count(&nJoints);
   for ( CollectionIndexType jntIdx = 0; jntIdx < nJoints; jntIdx++ )
   {
      CComPtr<IFem2dJoint> joint;
      joints->get_Item(jntIdx,&joint);
      Float64 x,y;
      joint->get_X(&x);
      joint->get_Y(&y);

      JointIDType id;
      joint->get_ID(&id);

      x = ::ConvertFromSysUnits(x, unitMeasure::Feet);
      y = ::ConvertFromSysUnits(y, unitMeasure::Feet);
      ofile << ID(id) << _T(" ") << x << _T(" ") << y << std::endl;
   }

   // Status Support
   ofile << _T("STATUS SUPPORT");
   for ( CollectionIndexType jntIdx = 0; jntIdx < nJoints; jntIdx++ )
   {
      CComPtr<IFem2dJoint> joint;
      joints->get_Item(jntIdx,&joint);

      VARIANT_BOOL bSupport;
      joint->IsSupport(&bSupport);

      if ( bSupport == VARIANT_TRUE )
      {
         JointIDType id;
         joint->get_ID(&id);

         ofile << _T(" ") << ID(id);
      }
   }
   ofile << std::endl;

   // Joint Releases
   ofile << _T("JOINT RELEASES") << std::endl;
   for ( CollectionIndexType jntIdx = 0; jntIdx < nJoints; jntIdx++ )
   {
      CComPtr<IFem2dJoint> joint;
      joints->get_Item(jntIdx,&joint);

      VARIANT_BOOL bSupport;
      joint->IsSupport(&bSupport);

      if ( bSupport == VARIANT_TRUE )
      {
         JointIDType id;
         joint->get_ID(&id);

         VARIANT_BOOL bFx, bFy, bMz;
         joint->IsDofReleased(jrtFx,&bFx);
         joint->IsDofReleased(jrtFy,&bFy);
         joint->IsDofReleased(jrtMz,&bMz);

         if (bFx == VARIANT_TRUE || bFy == VARIANT_TRUE || bMz == VARIANT_TRUE)
         {
            ofile << ID(id);
            if (bFx == VARIANT_TRUE)
            {
               ofile << _T(" FORCE X");
            }

            if (bFy == VARIANT_TRUE)
            {
               ofile << _T(" FORCE Y");
            }

            if (bMz == VARIANT_TRUE)
            {
               ofile << _T(" MOMENT Z");
            }

            ofile << std::endl;
         }
      }
   }

   // Member Incidences
   ofile << _T("MEMBER INCIDENCES") << std::endl;
   CComPtr<IFem2dMemberCollection> members;
   m_Model->get_Members(&members);
   CollectionIndexType nMembers;
   members->get_Count(&nMembers);
   for ( CollectionIndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++ )
   {
      CComPtr<IFem2dMember> member;
      members->get_Item(mbrIdx,&member);

      MemberIDType mbrID;
      member->get_ID(&mbrID);

      JointIDType startJnt, endJnt;
      member->get_StartJoint(&startJnt);
      member->get_EndJoint(&endJnt);

      ofile << ID(mbrID) << _T(" ") << ID(startJnt) << _T(" ") << ID(endJnt) << std::endl;
   }

   // Member Releases
   ofile << _T("MEMBER RELEASES") << std::endl;
   for (CollectionIndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++)
   {
      CComPtr<IFem2dMember> member;
      members->get_Item(mbrIdx, &member);

      MemberIDType mbrID;
      member->get_ID(&mbrID);

      VARIANT_BOOL bReleaseStartFx, bReleaseEndFx;
      member->IsReleased(metStart, mbrReleaseFx, &bReleaseStartFx);
      member->IsReleased(metEnd, mbrReleaseFx, &bReleaseEndFx);

      VARIANT_BOOL bReleaseStartMz, bReleaseEndMz;
      member->IsReleased(metStart, mbrReleaseMz, &bReleaseStartMz);
      member->IsReleased(metEnd, mbrReleaseMz, &bReleaseEndMz);

      if (bReleaseStartFx == VARIANT_TRUE || bReleaseEndFx == VARIANT_TRUE || bReleaseStartMz == VARIANT_TRUE || bReleaseEndMz == VARIANT_TRUE)
      {
         ofile << ID(mbrID);
         if (bReleaseStartFx == VARIANT_TRUE || bReleaseStartMz == VARIANT_TRUE)
         {
            ofile << _T(" START");
            if (bReleaseStartFx == VARIANT_TRUE)
            {
               ofile << _T(" FORCE X");
            }

            if (bReleaseStartMz == VARIANT_TRUE)
            {
               ofile << _T(" MOMENT Z");
            }
         }

         if (bReleaseEndFx == VARIANT_TRUE || bReleaseEndMz == VARIANT_TRUE)
         {
            ofile << _T(" END");
            if (bReleaseEndFx == VARIANT_TRUE)
            {
               ofile << _T(" FORCE X");
            }

            if (bReleaseEndMz == VARIANT_TRUE)
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
   ofile << _T("$ The properies below for A are really EA (kip) and I are really EI (kip*in^2).") << std::endl;
   ofile << _T("$ E will be set to 1.0 below.") << std::endl;
   for ( CollectionIndexType mbrIdx = 0; mbrIdx < nMembers; mbrIdx++ )
   {
      CComPtr<IFem2dMember> member;
      members->get_Item(mbrIdx,&member);

      MemberIDType mbrID;
      member->get_ID(&mbrID);

      Float64 EA, EI;
      member->get_EA(&EA);
      member->get_EI(&EI);

      // (ksi)*(in2) = kip
      EA = ::ConvertFromSysUnits(EA, unitMeasure::Kip);

      // (ksi)*(in4) = kip*in2
      EI = ::ConvertFromSysUnits(EI, unitMeasure::KipInch2);
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
   CComPtr<IFem2dLoadingCollection> loadings;
   m_Model->get_Loadings(&loadings);

   CollectionIndexType nLoadings;
   loadings->get_Count(&nLoadings);
   for ( CollectionIndexType ldIdx = 0; ldIdx < nLoadings; ldIdx++ )
   {
      CComPtr<IFem2dLoading> loading;
      loadings->get_Item(ldIdx,&loading);

      LoadCaseIDType lcID;
      loading->get_ID(&lcID);

      ofile << _T("LOADING ") << ID(abs((int)lcID)) << std::endl;
      ofile << _T("MEMBER LOADS") << std::endl;

      CComPtr<IFem2dDistributedLoadCollection> distLoads;
      loading->get_DistributedLoads(&distLoads);

      CollectionIndexType nLoads;
      distLoads->get_Count(&nLoads);

      for ( CollectionIndexType idx = 0; idx < nLoads; idx++ )
      {
         CComPtr<IFem2dDistributedLoad> load;
         distLoads->get_Item(idx,&load);

         MemberIDType mbrID;
         load->get_MemberID(&mbrID);

         Float64 xStart, xEnd, wStart, wEnd;
         load->get_StartLocation(&xStart);
         load->get_EndLocation(&xEnd);
         load->get_WStart(&wStart);
         load->get_WEnd(&wEnd);

         xStart = ::ConvertFromSysUnits(xStart, unitMeasure::Feet);
         xEnd = ::ConvertFromSysUnits(xEnd, unitMeasure::Feet);
         wStart = ::ConvertFromSysUnits(wStart, unitMeasure::KipPerFoot);
         wEnd = ::ConvertFromSysUnits(wEnd, unitMeasure::KipPerFoot);

         if (!IsZero(wStart) && !IsZero(wEnd))
         {
            if (xStart < 0 || xEnd < 0)
            {
               ofile << ID(mbrID) << _T(" FORCE Y LINEAR FRA WA ") << wStart << _T(" WB ") << wEnd << _T(" LA ") << fabs(xStart) << _T(" LB ") << fabs(xEnd) << std::endl;
            }
            else
            {
               ofile << ID(mbrID) << _T(" FORCE Y LINEAR WA ") << wStart << _T(" WB ") << wEnd << _T(" LA ") << fabs(xStart) << _T(" LB ") << fabs(xEnd) << std::endl;
            }
         }
      }


      CComPtr<IFem2dPointLoadCollection> pointLoads;
      loading->get_PointLoads(&pointLoads);

      pointLoads->get_Count(&nLoads);

      for ( CollectionIndexType idx = 0; idx < nLoads; idx++ )
      {
         CComPtr<IFem2dPointLoad> load;
         pointLoads->get_Item(idx,&load);

         MemberIDType mbrID;
         load->get_MemberID(&mbrID);

         Float64 Fx, Fy, Mz, X;
         load->GetForce(&Fx,&Fy,&Mz);
         load->get_Location(&X);

         X = ::ConvertFromSysUnits(X, unitMeasure::Feet);
         Fy = ::ConvertToSysUnits(Fy, unitMeasure::Kip);

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
