///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2010  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// EAFDocProxyAgent.cpp: implementation of the CEAFDocProxyAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EAFDocProxyAgent.h"

#include <EAF\StatusCenter.h>

#include "AgentTools.h"

// TODO: Fix the unit mode events
// The App class needs to have a generic connection point for firing unit mode events
// this Agent needs to sink the event and fire it throught the IDisplayUnitEventSink interface
//
// Need persistance of unit mode

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEAFDocProxyAgent::CEAFDocProxyAgent()
{
   m_pBroker = 0;
   m_pDoc = 0;
   m_pMainFrame = 0;

   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   pApp->AddUnitModeListener(this);

   // Log File
   m_LogFileName = "";
   m_dwLogFileCookie = 0;
}

CEAFDocProxyAgent::~CEAFDocProxyAgent()
{

}

void CEAFDocProxyAgent::SetDocument(CEAFBrokerDocument* pDoc)
{
   m_pDoc = pDoc;
}

void CEAFDocProxyAgent::SetMainFrame(CEAFMainFrame* pFrame)
{
   m_pMainFrame = pFrame;
}

CEAFMainFrame* CEAFDocProxyAgent::GetMainFrame()
{
   return m_pMainFrame;
}

//////////////////////////////////////////
// IAgentEx
STDMETHODIMP CEAFDocProxyAgent::SetBroker(IBroker* pBroker)
{
   AGENT_SET_BROKER(pBroker);
   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::RegInterfaces()
{
   CComQIPtr<IBrokerInitEx2> pBrokerInit(m_pBroker);

   pBrokerInit->RegInterface( IID_IViewRegistrar,    this );
   pBrokerInit->RegInterface( IID_IMainMenu,         this );
   pBrokerInit->RegInterface( IID_IToolBars,         this );
   pBrokerInit->RegInterface( IID_IDocument,         this );
//   pBrokerInit->RegInterface( IID_IAcceleratorTable, this );
   pBrokerInit->RegInterface( IID_IDisplayUnits,     this );
   pBrokerInit->RegInterface( IID_IStatusCenter,     this );
   pBrokerInit->RegInterface( IID_ITransactions,    this );
   pBrokerInit->RegInterface( IID_IProjectLog,        this );

   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::Init()
{
   AGENT_INIT;
   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::Init2()
{
   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::Reset()
{
   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::ShutDown()
{
   GET_IFACE( ILogFile, pLogFile );
   if ( IsLogFileOpen() )
   {
      m_pDoc->OnLogFileClosing();
      pLogFile->Close( m_dwLogFileCookie );
   }

   AGENT_CLEAR_INTERFACE_CACHE;

   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   pApp->RemoveUnitModeListener(this);

   return S_OK;
}

STDMETHODIMP CEAFDocProxyAgent::GetClassID(CLSID* pCLSID)
{
   *pCLSID = CLSID_EAFDocProxyAgent;
   return S_OK;
}

///////////////////////////////////////////////////////
// IViewRegistrar
long CEAFDocProxyAgent::RegisterView(CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu,int maxViewCount)
{
   return m_pDoc->RegisterView(pFrameClass,pViewClass,hSharedMenu,maxViewCount);
}

void CEAFDocProxyAgent::RemoveView(long key)
{
   m_pDoc->RemoveView(key);
}

CView* CEAFDocProxyAgent::CreateView(long key,LPVOID pData)
{
   return m_pDoc->CreateView(key,pData);
}

///////////////////////////////////////////////////////
// IMainMenu
CEAFMenu* CEAFDocProxyAgent::GetMainMenu()
{
   return m_pDoc->GetMenu();
}

///////////////////////////////////////////////////////
// IToolBars
UINT CEAFDocProxyAgent::CreateToolBar(LPCTSTR lpszName)
{
   return m_pDoc->CreateToolBar(lpszName);
}

CEAFToolBar* CEAFDocProxyAgent::GetToolBar(UINT toolbarID)
{
   return m_pDoc->GetToolBar(toolbarID);
}

void CEAFDocProxyAgent::DestroyToolBar(CEAFToolBar* pToolBar)
{
   m_pDoc->DestroyToolBar(pToolBar);
}

void CEAFDocProxyAgent::DestroyToolBar(UINT toolbarID)
{
   m_pDoc->DestroyToolBar(toolbarID);
}

///////////////////////////////////////////////////////
// IDocument
BOOL CEAFDocProxyAgent::IsModified()
{
   return m_pDoc->IsModified();
}

void CEAFDocProxyAgent::SetModified(BOOL bModified)
{
   m_pDoc->SetModifiedFlag(bModified);
}

CString CEAFDocProxyAgent::GetFileName()
{
   CFileFind finder;
   CString strResult;
   if ( finder.FindFile(m_pDoc->GetPathName()) )
   {
      finder.FindNextFile();
      strResult = finder.GetFileName();
      finder.Close();
   }

   return strResult;
}

CString CEAFDocProxyAgent::GetFileTitle()
{
   CFileFind finder;
   CString strResult;
   if ( finder.FindFile(m_pDoc->GetPathName()) )
   {
      finder.FindNextFile();
      strResult = finder.GetFileTitle();
      finder.Close();
   }

   return strResult;
}

CString CEAFDocProxyAgent::GetFilePath()
{
   CFileFind finder;
   CString strResult;
   if ( finder.FindFile(m_pDoc->GetPathName()) )
   {
      finder.FindNextFile();
      strResult = finder.GetFilePath();
      finder.Close();
   }

   return strResult;
}

CString CEAFDocProxyAgent::GetFileRoot()
{
   CFileFind finder;
   CString strResult;
   if ( finder.FindFile(m_pDoc->GetPathName()) )
   {
      finder.FindNextFile();
      strResult = finder.GetRoot();
      finder.Close();
   }

   return strResult;
}

void CEAFDocProxyAgent::UpdateAllViews(CView* pSender,LPARAM lHint,CObject* pHint)
{
   m_pDoc->UpdateAllViews(pSender,lHint,pHint);
}

////////////////////////////////////////////////////////////////////////
// IDisplayUnits
//
void CEAFDocProxyAgent::SetUnitMode(eafTypes::UnitMode unitMode)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   pApp->SetUnitsMode(unitMode);
}

eafTypes::UnitMode CEAFDocProxyAgent::GetUnitMode()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetUnitsMode();
}

const unitStationFormat& CEAFDocProxyAgent::GetStationFormat()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->StationFormat;
}

const unitmgtScalar& CEAFDocProxyAgent::GetScalarFormat()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Scalar;
}

const unitmgtLengthData& CEAFDocProxyAgent::GetComponentDimUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->ComponentDim;
}

const unitmgtLengthData& CEAFDocProxyAgent::GetXSectionDimUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->XSectionDim;
}

const unitmgtLengthData& CEAFDocProxyAgent::GetSpanLengthUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->SpanLength;
}

const unitmgtLengthData&  CEAFDocProxyAgent::GetAlignmentLengthUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->AlignmentLength;
}

const unitmgtLengthData&  CEAFDocProxyAgent::GetDisplacementUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Displacement;
}

const unitmgtLength2Data& CEAFDocProxyAgent::GetAreaUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Area;
}

const unitmgtLength4Data& CEAFDocProxyAgent::GetMomentOfInertiaUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->MomentOfInertia;
}

const unitmgtLength3Data& CEAFDocProxyAgent::GetSectModulusUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->SectModulus;
}

const unitmgtPressureData& CEAFDocProxyAgent::GetStressUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Stress;
}

const unitmgtPressureData& CEAFDocProxyAgent::GetModEUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->ModE;
}

const unitmgtForceData& CEAFDocProxyAgent::GetGeneralForceUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->GeneralForce;
}

const unitmgtForceData& CEAFDocProxyAgent::GetTonnageUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Tonnage;
}

const unitmgtForceData& CEAFDocProxyAgent::GetShearUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Shear;
}

const unitmgtMomentData& CEAFDocProxyAgent::GetMomentUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Moment;
}

const unitmgtMomentData& CEAFDocProxyAgent::GetSmallMomentUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->SmallMoment;
}

const unitmgtAngleData& CEAFDocProxyAgent::GetAngleUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Angle;
}

const unitmgtAngleData& CEAFDocProxyAgent::GetRadAngleUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->RadAngle;
}

const unitmgtDensityData& CEAFDocProxyAgent::GetDensityUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Density;
}

const unitmgtMassPerLengthData& CEAFDocProxyAgent::GetMassPerLengthUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->MassPerLength;
}

const unitmgtForcePerLengthData& CEAFDocProxyAgent::GetForcePerLengthUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->ForcePerLength;
}

const unitmgtMomentPerAngleData& CEAFDocProxyAgent::GetMomentPerAngleUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->MomentPerAngle;
}

const unitmgtTimeData& CEAFDocProxyAgent::GetShortTimeUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Time;
}

const unitmgtTimeData& CEAFDocProxyAgent::GetLongTimeUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->Time2;
}

const unitmgtAreaPerLengthData& CEAFDocProxyAgent::GetAvOverSUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->AvOverS;
}

const unitmgtForceLength2Data& CEAFDocProxyAgent::GetStiffnessUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->ForceLength2;
}

const unitmgtSqrtPressureData& CEAFDocProxyAgent::GetTensionCoefficientUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->SqrtPressure;
}

const unitmgtPerLengthData& CEAFDocProxyAgent::GetPerLengthUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->PerLength;
}

const unitmgtPressureData& CEAFDocProxyAgent::GetSidewalkPressureUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->SmallStress;
}

const unitmgtPressureData& CEAFDocProxyAgent::GetOverlayWeightUnit()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CEAFApp* pApp = (CEAFApp*)AfxGetApp();
   return pApp->GetDisplayUnits()->SmallStress;
}

//////////////////////////////////////////////////////////////
// IStatusCenter
StatusCallbackIDType CEAFDocProxyAgent::RegisterCallback(iStatusCallback* pCallback)
{
   return m_pDoc->GetStatusCenter().RegisterCallbackItem(pCallback);
}

StatusGroupIDType CEAFDocProxyAgent::CreateStatusGroupID()
{
   return m_pDoc->GetStatusCenter().CreateStatusGroupID();
}

StatusItemIDType CEAFDocProxyAgent::Add(CEAFStatusItem* pItem)
{
   return m_pDoc->GetStatusCenter().Add(pItem);
}

bool CEAFDocProxyAgent::RemoveByID(StatusItemIDType id)
{
   return m_pDoc->GetStatusCenter().RemoveByID(id);
}

bool CEAFDocProxyAgent::RemoveByIndex(CollectionIndexType index)
{
   return m_pDoc->GetStatusCenter().RemoveByIndex(index);
}

bool CEAFDocProxyAgent::RemoveByStatusGroupID(StatusGroupIDType id)
{
   return m_pDoc->GetStatusCenter().RemoveByStatusGroupID(id);
}

CEAFStatusItem* CEAFDocProxyAgent::GetByID(StatusItemIDType id)
{
   return m_pDoc->GetStatusCenter().GetByID(id);
}

CEAFStatusItem* CEAFDocProxyAgent::GetByIndex(CollectionIndexType index)
{
   return m_pDoc->GetStatusCenter().GetByIndex(index);
}

eafTypes::StatusSeverityType CEAFDocProxyAgent::GetSeverity(const CEAFStatusItem* pItem)
{
   return m_pDoc->GetStatusCenter().GetSeverity(pItem->GetCallbackID());
}

eafTypes::StatusSeverityType CEAFDocProxyAgent::GetSeverity()
{
   return m_pDoc->GetStatusCenter().GetSeverity();
}

CollectionIndexType CEAFDocProxyAgent::Count()
{
   return m_pDoc->GetStatusCenter().Count();
}

///////////////////////////////////////////////////////////////////////////////////
// ITransactions
void CEAFDocProxyAgent::Execute(txnTransaction& rTxn)
{
   m_pDoc->Execute(rTxn);
}

void CEAFDocProxyAgent::Execute(txnTransaction* pTxn)
{
   m_pDoc->Execute(pTxn);
}

void CEAFDocProxyAgent::Undo()
{
   m_pDoc->Undo();
}

void CEAFDocProxyAgent::Redo()
{
   m_pDoc->Redo();
}

void CEAFDocProxyAgent::Repeat()
{
  m_pDoc->Repeat();
}

bool CEAFDocProxyAgent::CanUndo()
{
   return m_pDoc->CanUndo();
}

bool CEAFDocProxyAgent::CanRedo()
{
   return m_pDoc->CanRedo();
}

bool CEAFDocProxyAgent::CanRepeat()
{
   return m_pDoc->CanRepeat();
}

std::string CEAFDocProxyAgent::UndoName()
{
   return m_pDoc->UndoName();
}

std::string CEAFDocProxyAgent::RedoName()
{
   return m_pDoc->RedoName();
}

std::string CEAFDocProxyAgent::RepeatName()
{
   return m_pDoc->RepeatName();
}

CollectionIndexType CEAFDocProxyAgent::GetTxnCount()
{
   return m_pDoc->GetTxnCount();
}

CollectionIndexType CEAFDocProxyAgent::GetUndoCount()
{
   return m_pDoc->GetUndoCount();
}


//////////////////////////////////////////////////////////////////////////////////
// IProjectLog implementation
CString CEAFDocProxyAgent::GetName()
{
   if ( !IsLogFileOpen() )
      OpenLogFile();

   return m_LogFileName;
}

void CEAFDocProxyAgent::LogMessage( const char* lpszMsg )
{
   if ( !IsLogFileOpen() )
      OpenLogFile();

   GET_IFACE(ILogFile,pLogFile);
   pLogFile->LogMessage( m_dwLogFileCookie, lpszMsg );
}

void CEAFDocProxyAgent::Destroy()
{
   if ( !IsLogFileOpen() )
      return;

   GET_IFACE(ILogFile,pLogFile);
   pLogFile->Close( m_dwLogFileCookie );
   m_LogFileName = "";
   ::DeleteFile( m_LogFileName );
}

bool CEAFDocProxyAgent::IsLogFileOpen()
{
   return m_dwLogFileCookie == 0 ? false : true;
}

void CEAFDocProxyAgent::OpenLogFile()
{
   m_LogFileName = m_pDoc->GetLogFileName();

   GET_IFACE(ILogFile,pLogFile);
   pLogFile->Open( m_LogFileName, &m_dwLogFileCookie );
   m_pDoc->OnLogFileOpened();
}

