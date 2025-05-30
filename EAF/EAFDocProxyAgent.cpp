///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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
// this Agent needs to sink the event and fire it through the IDisplayUnitEventSink interface
//
// Need persistence of unit mode

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEAFDocProxyAgent::CEAFDocProxyAgent(CEAFBrokerDocument* pDoc, CEAFMainFrame* pFrame) :
   m_pDoc(pDoc), m_pMainFrame(pFrame)
{
   CEAFApp* pApp = EAFGetApp();
   pApp->AddUnitModeListener(this);
}

CEAFMainFrame* CEAFDocProxyAgent::GetMainFrame()
{
   return m_pMainFrame;
}

//////////////////////////////////////////
// Agent
bool CEAFDocProxyAgent::Init()
{
   EAF_AGENT_INIT;

   // An attempt was made to implement IEAFProgress in DocProxyAgent so the WBFLCore DLL could be eliminated. There were problems with resources.
   // The progress window dialog could not be created because the resource handle was invalid. I suspect this is because EAF is an MFC Extension DLL.
   // All the code related to IEAFProgress is still in DocProxyAgent, but commented out.
   // Try again later, but for now IEAFProgress is implemented in WBFLCore.DLL SysAgent
   //m_CommandLineDisplayMode = EAFGetApp()->GetCommandLineMode();
   //return SUCCEEDED(ValidateThread());

   return true;
}
//
//HRESULT CEAFDocProxyAgent::ValidateThread()
//{
//   if (m_pThread == nullptr)
//   {
//      AFX_MANAGE_STATE(AfxGetStaticModuleState());
//
//      // Run the progress window in a UI thread
//      m_pThread = (CProgressThread*)AfxBeginThread(RUNTIME_CLASS(CProgressThread));
//      ATLASSERT(m_pThread != nullptr);
//   }
//   return S_OK;
//}

bool CEAFDocProxyAgent::RegisterInterfaces()
{
   EAF_AGENT_REGISTER_INTERFACES;

   REGISTER_INTERFACE(IEAFViewRegistrar);
   REGISTER_INTERFACE(IEAFMainMenu);
   REGISTER_INTERFACE(IEAFToolbars);
   REGISTER_INTERFACE(IEAFDocument);
   REGISTER_INTERFACE(IEAFAcceleratorTable);
   REGISTER_INTERFACE(IEAFDisplayUnits);
   REGISTER_INTERFACE(IEAFStatusCenter);
   REGISTER_INTERFACE(IEAFTransactions);
   REGISTER_INTERFACE(IEAFProjectLog);
   //REGISTER_INTERFACE(IEAFProgress);

   return true;
}


bool CEAFDocProxyAgent::ShutDown()
{
   EAF_AGENT_SHUTDOWN;

   CEAFApp* pApp = EAFGetApp();
   pApp->RemoveUnitModeListener(this);

   //if (m_pThread != nullptr)
   //{
   //   m_pThread->PostThreadMessage(WM_KILLTHREAD, 0, 0);
   //   DWORD result = ::WaitForSingleObject(m_pThread->m_hThread, 10000/*INFINITE*/); // wait for thread to terminate
   //   if (result == WAIT_TIMEOUT || result == WAIT_FAILED)
   //   {
   //      ATLASSERT(false); // for some reason, the WM_KILLTHREAD message never got to the message handler
   //      m_pThread->OnKillThread(0, 0);
   //   }
   //}
   //m_pThread = nullptr;

   //if (m_CommandLineDisplayMode == CEAFCommandLineInfo::cldEchoProgress)
   //{
   //   // echo message when app is finished
   //   std::cout << "Finished." << std::endl;
   //}
   return true;
}

CLSID CEAFDocProxyAgent::GetCLSID() const
{
   return CLSID_EAFDocProxyAgent;
}

///////////////////////////////////////////////////////
// IEAFViewRegistrar
long CEAFDocProxyAgent::RegisterView(UINT nResourceID, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback,CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu,int maxViewCount)
{
   return m_pDoc->RegisterView(nResourceID,pCallback,pFrameClass,pViewClass,hSharedMenu,maxViewCount);
}

void CEAFDocProxyAgent::RemoveView(long key)
{
   m_pDoc->RemoveView(key);
}

CView* CEAFDocProxyAgent::CreateView(long key,LPVOID pData)
{
   return m_pDoc->CreateView(key,pData);
}

void CEAFDocProxyAgent::UpdateRegisteredView(long key,CView* pSender,LPARAM lHint,CObject* pHint)
{
   m_pDoc->UpdateRegisteredView(key,pSender,lHint,pHint);
}

std::vector<CView*> CEAFDocProxyAgent::GetRegisteredView(long key)
{
   return m_pDoc->GetRegisteredView(key);
}

///////////////////////////////////////////////////////
// IEAFMainMenu
std::shared_ptr<WBFL::EAF::Menu> CEAFDocProxyAgent::GetMainMenu()
{
   return m_pDoc->GetMainMenu();
}

std::shared_ptr<WBFL::EAF::Menu> CEAFDocProxyAgent::CreateContextMenu()
{
   return WBFL::EAF::Menu::CreateContextMenu(m_pDoc->GetPluginCommandManager());
}

///////////////////////////////////////////////////////
// IEAFToolbars
UINT CEAFDocProxyAgent::CreateToolBar(LPCTSTR lpszName)
{
   return m_pDoc->CreateToolBar(lpszName);
}

std::shared_ptr<WBFL::EAF::ToolBar> CEAFDocProxyAgent::GetToolBar(UINT toolbarID)
{
   return m_pDoc->GetToolBar(toolbarID);
}

void CEAFDocProxyAgent::DestroyToolBar(UINT toolbarID)
{
   m_pDoc->DestroyToolBar(toolbarID);
}

///////////////////////////////////////////////////////
// IEAFAcceleratorTable
BOOL CEAFDocProxyAgent::AddAccelTable(HACCEL hAccel, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   return m_pDoc->GetAcceleratorTable()->AddAccelTable(hAccel,pCallback);
}

BOOL CEAFDocProxyAgent::AddAccelKey(BYTE fVirt,WORD key,WORD cmd, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   return m_pDoc->GetAcceleratorTable()->AddAccelKey(fVirt,key,cmd,pCallback);
}

BOOL CEAFDocProxyAgent::RemoveAccelKey(WORD cmd, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback)
{
   return m_pDoc->GetAcceleratorTable()->RemoveAccelKey(cmd,pCallback);
}

BOOL CEAFDocProxyAgent::RemoveAccelKey(BYTE fVirt,WORD key)
{
   return m_pDoc->GetAcceleratorTable()->RemoveAccelKey(fVirt,key);
}

///////////////////////////////////////////////////////
// IEAFDocument
BOOL CEAFDocProxyAgent::IsModified()
{
   return m_pDoc->IsModified();
}

void CEAFDocProxyAgent::SetModified(BOOL bModified)
{
   m_pDoc->SetModifiedFlag(bModified);
}

void CEAFDocProxyAgent::Save()
{
   m_pDoc->SaveModified();
}

void CEAFDocProxyAgent::SaveAs(LPCTSTR lpszPathname,BOOL bReplace)
{
   m_pDoc->DoSave(lpszPathname,bReplace);
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

   if ( strResult.IsEmpty() )
   {
      strResult = m_pDoc->GetTitle();
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
   m_pDoc->OnUpdateAllViews(pSender,lHint,pHint);
}

////////////////////////////////////////////////////////////////////////
// IEAFDisplayUnits
//
void CEAFDocProxyAgent::SetUnitMode(WBFL::EAF::UnitMode unitMode)
{
   CEAFApp* pApp = EAFGetApp();
   pApp->SetUnitsMode(unitMode);
}

WBFL::EAF::UnitMode CEAFDocProxyAgent::GetUnitMode()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetUnitsMode();
}

const WBFL::Units::StationFormat& CEAFDocProxyAgent::GetStationFormat()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->StationFormat;
}

const WBFL::Units::ScalarData& CEAFDocProxyAgent::GetScalarFormat()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Scalar;
}

const WBFL::Units::ScalarData& CEAFDocProxyAgent::GetPercentageFormat()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Percentage;
}

const WBFL::Units::LengthData& CEAFDocProxyAgent::GetComponentDimUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->ComponentDim;
}

const WBFL::Units::LengthData& CEAFDocProxyAgent::GetXSectionDimUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->XSectionDim;
}

const WBFL::Units::LengthData& CEAFDocProxyAgent::GetSpanLengthUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->SpanLength;
}

const WBFL::Units::LengthData&  CEAFDocProxyAgent::GetAlignmentLengthUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->AlignmentLength;
}

const WBFL::Units::LengthData&  CEAFDocProxyAgent::GetDeflectionUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Deflection;
}

const WBFL::Units::Length2Data& CEAFDocProxyAgent::GetAreaUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Area;
}

const WBFL::Units::Length4Data& CEAFDocProxyAgent::GetMomentOfInertiaUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->MomentOfInertia;
}

const WBFL::Units::Length3Data& CEAFDocProxyAgent::GetSectModulusUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->SectModulus;
}

const WBFL::Units::PressureData& CEAFDocProxyAgent::GetStressUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Stress;
}

const WBFL::Units::PressureData& CEAFDocProxyAgent::GetModEUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->ModE;
}

const WBFL::Units::ForceData& CEAFDocProxyAgent::GetGeneralForceUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->GeneralForce;
}

const WBFL::Units::ForceData& CEAFDocProxyAgent::GetTonnageUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Tonnage;
}

const WBFL::Units::ForceData& CEAFDocProxyAgent::GetShearUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Shear;
}

const WBFL::Units::MomentData& CEAFDocProxyAgent::GetMomentUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Moment;
}

const WBFL::Units::MomentData& CEAFDocProxyAgent::GetSmallMomentUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->SmallMoment;
}

const WBFL::Units::AngleData& CEAFDocProxyAgent::GetAngleUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Angle;
}

const WBFL::Units::AngleData& CEAFDocProxyAgent::GetRadAngleUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->RadAngle;
}

const WBFL::Units::DensityData& CEAFDocProxyAgent::GetDensityUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Density;
}

const WBFL::Units::MassPerLengthData& CEAFDocProxyAgent::GetMassPerLengthUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->MassPerLength;
}

const WBFL::Units::ForcePerLengthData& CEAFDocProxyAgent::GetForcePerLengthUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->ForcePerLength;
}

const WBFL::Units::MomentPerAngleData& CEAFDocProxyAgent::GetMomentPerAngleUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->MomentPerAngle;
}

const WBFL::Units::TimeData& CEAFDocProxyAgent::GetShortTimeUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Time;
}

const WBFL::Units::TimeData& CEAFDocProxyAgent::GetWholeDaysUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Time2;
}

const WBFL::Units::TimeData& CEAFDocProxyAgent::GetFractionalDaysUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Time3;
}

const WBFL::Units::AreaPerLengthData& CEAFDocProxyAgent::GetAvOverSUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->AvOverS;
}

const WBFL::Units::ForceLength2Data& CEAFDocProxyAgent::GetStiffnessUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->ForceLength2;
}

const WBFL::Units::SqrtPressureData& CEAFDocProxyAgent::GetTensionCoefficientUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->SqrtPressure;
}

const WBFL::Units::PerLengthData& CEAFDocProxyAgent::GetPerLengthUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->PerLength;
}

const WBFL::Units::PerLengthData& CEAFDocProxyAgent::GetCurvatureUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Curvature;
}

const WBFL::Units::PressureData& CEAFDocProxyAgent::GetSidewalkPressureUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->SmallStress;
}

const WBFL::Units::PressureData& CEAFDocProxyAgent::GetOverlayWeightUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->SmallStress;
}

const WBFL::Units::PressureData& CEAFDocProxyAgent::GetWindPressureUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->WindPressure;
}

const WBFL::Units::TemperatureData& CEAFDocProxyAgent::GetTemperatureUnit()
{
    CEAFApp* pApp = EAFGetApp();
    return pApp->GetDisplayUnits()->Temperature;
}

const WBFL::Units::VelocityData& CEAFDocProxyAgent::GetVelocityUnit()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetDisplayUnits()->Velocity;
}

//////////////////////////////////////////////////////////////
// IEAFStatusCenter
StatusCallbackIDType CEAFDocProxyAgent::RegisterCallback(std::shared_ptr<WBFL::EAF::StatusCallback> pCallback)
{
   return m_pDoc->GetStatusCenter().RegisterCallbackItem(pCallback);
}

StatusGroupIDType CEAFDocProxyAgent::CreateStatusGroupID()
{
   return m_pDoc->GetStatusCenter().CreateStatusGroupID();
}

StatusItemIDType CEAFDocProxyAgent::Add(std::shared_ptr<WBFL::EAF::StatusItem> pItem)
{
   return m_pDoc->GetStatusCenter().Add(pItem);
}

bool CEAFDocProxyAgent::RemoveByID(StatusItemIDType id)
{
   return m_pDoc->GetStatusCenter().RemoveByID(id);
}

bool CEAFDocProxyAgent::RemoveByIndex(IndexType index)
{
   return m_pDoc->GetStatusCenter().RemoveByIndex(index);
}

bool CEAFDocProxyAgent::RemoveByStatusGroupID(StatusGroupIDType id)
{
   return m_pDoc->GetStatusCenter().RemoveByStatusGroupID(id);
}

std::shared_ptr<WBFL::EAF::StatusItem> CEAFDocProxyAgent::GetByID(StatusItemIDType id)
{
   return m_pDoc->GetStatusCenter().GetByID(id);
}

std::shared_ptr<WBFL::EAF::StatusItem> CEAFDocProxyAgent::GetByIndex(IndexType index)
{
   return m_pDoc->GetStatusCenter().GetByIndex(index);
}

WBFL::EAF::StatusSeverityType CEAFDocProxyAgent::GetSeverity(std::shared_ptr<const WBFL::EAF::StatusItem> pItem)
{
   return m_pDoc->GetStatusCenter().GetSeverity(pItem->GetCallbackID());
}

WBFL::EAF::StatusSeverityType CEAFDocProxyAgent::GetSeverity()
{
   return m_pDoc->GetStatusCenter().GetSeverity();
}

IndexType CEAFDocProxyAgent::Count()
{
   return m_pDoc->GetStatusCenter().Count();
}

///////////////////////////////////////////////////////////////////////////////////
// IEAFTransactions
void CEAFDocProxyAgent::Execute(const WBFL::EAF::Transaction& rTxn)
{
   m_pDoc->Execute(rTxn);
}

void CEAFDocProxyAgent::Execute(std::unique_ptr<WBFL::EAF::Transaction>&& pTxn)
{
   m_pDoc->Execute(std::move(pTxn));
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

bool CEAFDocProxyAgent::CanUndo() const
{
   return m_pDoc->CanUndo();
}

bool CEAFDocProxyAgent::CanRedo() const
{
   return m_pDoc->CanRedo();
}

bool CEAFDocProxyAgent::CanRepeat() const
{
   return m_pDoc->CanRepeat();
}

std::_tstring CEAFDocProxyAgent::UndoName() const
{
   return m_pDoc->UndoName();
}

std::_tstring CEAFDocProxyAgent::RedoName() const
{
   return m_pDoc->RedoName();
}

std::_tstring CEAFDocProxyAgent::RepeatName() const
{
   return m_pDoc->RepeatName();
}

IndexType CEAFDocProxyAgent::GetTxnCount() const
{
   return m_pDoc->GetTxnCount();
}

IndexType CEAFDocProxyAgent::GetUndoCount() const
{
   return m_pDoc->GetUndoCount();
}


//////////////////////////////////////////////////////////////////////////////////
// IEAFProjectLog implementation
void CEAFDocProxyAgent::LogMessage( LPCTSTR lpszMsg )
{
   WBFL::System::Logger::Info(lpszMsg);
}

//STDMETHODIMP CEAFDocProxyAgent::CreateProgressWindow(DWORD dwMask, UINT nDelay)
//{
//   if (m_CommandLineDisplayMode != CEAFCommandLineInfo::cldDefault)
//   {
//      // do nothing if UI is not to be shown
//      return S_OK;
//   }
//   else
//   {
//      // must have a valid thread before we can do anything else
//      if (FAILED(ValidateThread()))
//      {
//         return PROGRESS_E_CREATE;
//      }
//
//      m_cProgressRef++;
//
//      if (1 == m_cProgressRef)
//      {
//         CWnd* pMainWnd = nullptr;
//         {
//            AFX_MANAGE_STATE(AfxGetAppModuleState());
//            pMainWnd = AfxGetMainWnd();
//         }
//
//         HRESULT hr = m_pThread->CreateProgressWindow(pMainWnd, dwMask, nDelay);
//         ATLASSERT(SUCCEEDED(hr));
//         if (FAILED(hr))
//         {
//            m_cProgressRef--;
//            return PROGRESS_E_CREATE;
//         }
//      }
//
//      // Save last message that was issued by the previous window
//      if (0 < m_LastMessage.size())
//      {
//         m_MessageStack.push_back(m_LastMessage);
//      }
//      else
//      {
//         UpdateMessage(_T("Working..."));
//      }
//
//      return S_OK;
//   }
//}
//
//STDMETHODIMP CEAFDocProxyAgent::Init(short begin, short end, short inc)
//{
//   if (m_CommandLineDisplayMode != CEAFCommandLineInfo::cldDefault)
//   {
//      // do nothing if UI is not to be shown
//      return S_OK;
//   }
//   else
//   {
//      // must have a valid thread before we can do anything else
//      if (FAILED(ValidateThread()))
//      {
//         return E_FAIL;
//      }
//      m_pThread->Init(begin, end, inc);
//      return S_OK;
//   }
//}
//
//STDMETHODIMP CEAFDocProxyAgent::Increment()
//{
//   if (m_CommandLineDisplayMode != CEAFCommandLineInfo::cldDefault)
//   {
//      // do nothing if UI is not to be shown
//      return S_OK;
//   }
//   else
//   {
//      // must have a valid thread before we can do anything else
//      if (FAILED(ValidateThread()))
//      {
//         return E_FAIL;
//      }
//      m_pThread->Increment();
//      return S_OK;
//   }
//}
//
//STDMETHODIMP CEAFDocProxyAgent::UpdateMessage(LPCTSTR msg)
//{
//   if (m_CommandLineDisplayMode != CEAFCommandLineInfo::cldDefault)
//   {
//      if (m_CommandLineDisplayMode == CEAFCommandLineInfo::cldEchoProgress)
//      {
//         // Don't show "Working...". There are 10's of thousands
//         int result = lstrcmp(msg, _T("Wor"));
//         if (result != 0)
//         {
//            std::cout << CStringA(msg) << std::endl;
//         }
//      }
//
//      return S_OK;
//   }
//   else
//   {
//      // must have a valid thread before we can do anything else
//      if (FAILED(ValidateThread()))
//      {
//         return E_FAIL;
//      }
//
//      m_LastMessage = msg;
//      m_pThread->UpdateMessage(msg);
//
//      return S_OK;
//   }
//}
//
//STDMETHODIMP CEAFDocProxyAgent::Continue()
//{
//   if (m_CommandLineDisplayMode != CEAFCommandLineInfo::cldDefault)
//   {
//      // do nothing if UI is not to be shown
//      return S_OK;
//   }
//   else
//   {
//      // must have a valid thread before we can do anything else
//      if (FAILED(ValidateThread()))
//      {
//         return E_FAIL;
//      }
//
//      return m_pThread->Continue() ? S_OK : S_FALSE;
//   }
//}
//
//STDMETHODIMP CEAFDocProxyAgent::DestroyProgressWindow()
//{
//   if (m_CommandLineDisplayMode != CEAFCommandLineInfo::cldDefault)
//   {
//      // do nothing if UI is not to be shown
//      return S_OK;
//   }
//   else
//   {
//      // must have a valid thread before we can do anything else
//      if (FAILED(ValidateThread()))
//      {
//         return E_FAIL;
//      }
//
//#if defined _DEBUG
//      if (0 < m_cProgressRef)
//      {
//         // if there is at least one creater of the progress window
//         // the thread had better still be alive
//         ATLASSERT(m_pThread != nullptr);
//      }
//#endif
//
//      m_cProgressRef--;
//      ATLASSERT(0 <= m_cProgressRef);
//
//      if (m_cProgressRef == 0)
//      {
//         m_pThread->ResetContinueState();
//         m_pThread->DestroyProgressWindow();
//      }
//      else
//      {
//         // restore message from previous window in stack
//         if (!m_MessageStack.empty())
//         {
//            m_LastMessage = m_MessageStack.back();
//            m_MessageStack.pop_back();
//            m_pThread->UpdateMessage(m_LastMessage.c_str());
//         }
//      }
//
//      return S_OK;
//   }
//}
