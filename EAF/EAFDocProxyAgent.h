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

// EAFDocProxyAgent.h: interface for the CEAFDocProxyAgent class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\Agent.h>
#include <EAF\EAFApp.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFUIIntegration.h>
#include <EAF\EAFDisplayUnits.h>
#include <EAF\EAFStatusCenter.h>
#include <EAF\EAFTransactions.h>
#include <EAF\EAFProjectLog.h>
#include <EAF\EAFProgress.h>

//#include "ProgressThread.h"


//////////////////////////////////////////////////////////////////////////////
// CProxyIEAFDisplayUnitsEventSink
template <class T>
class CProxyIEAFDisplayUnitsEventSink : public WBFL::EAF::EventSinkManager<T>
{
public:

//IEAFDisplayUnitsEventSink : IUnknown
public:
	HRESULT Fire_UnitsChanging()
	{
		T* pT = (T*)this;

      //if ( pT->m_bHoldingEvents )
      //{
      //   WBFL::System::Flags<UINT32>::Set(&pT->m_PendingEvents,EVT_UNITS);
      //   return S_OK;
      //}

      //pT->Lock();
		HRESULT ret = S_OK;
      for (auto& [id,sink] : this->m_EventSinks)
		{
		 auto callback = sink.lock();
			if (callback != nullptr)
			{
				ret = callback->OnUnitsChanging();
			}
		}
		//pT->Unlock();
		return ret;
	}
	HRESULT Fire_UnitsChanged(WBFL::EAF::UnitMode newUnitsMode)
	{
		T* pT = (T*)this;

      //if ( pT->m_bHoldingEvents )
      //{
      //   WBFL::System::Flags<UINT32>::Set(&pT->m_PendingEvents,EVT_UNITS);
      //   return S_OK;
      //}

      //pT->Lock();
		HRESULT ret = S_OK;

      for (auto& [id, sink] : this->m_EventSinks)
      {
		 auto callback = sink.lock();
         if (callback != nullptr)
         {
            ret = callback->OnUnitsChanged(newUnitsMode);
			}
		}
		//pT->Unlock();
		return ret;
	}
};

// {FFBDF482-53B0-42e5-92C8-0D1301816F70}
DEFINE_GUID(CLSID_EAFDocProxyAgent, 
0xffbdf482, 0x53b0, 0x42e5, 0x92, 0xc8, 0xd, 0x13, 0x1, 0x81, 0x6f, 0x70);

class CEAFDocProxyAgent : public WBFL::EAF::Agent,
   public CProxyIEAFDisplayUnitsEventSink<IEAFDisplayUnitsEventSink>,
   public iUnitModeListener,
   public IEAFViewRegistrar,
   public IEAFMainMenu,
   public IEAFToolbars,
   public IEAFAcceleratorTable,
   public IEAFDocument,
   public IEAFDisplayUnits,
   public IEAFStatusCenter,
   public IEAFTransactions,
   //public IEAFProgress, // This isn't working here, so it is implemented by SysAgent in WBFLCore.dll
   public IEAFProjectLog
{
public:
	CEAFDocProxyAgent(CEAFBrokerDocument* pDoc, CEAFMainFrame* pFrame);
	virtual ~CEAFDocProxyAgent() = default;

   CEAFMainFrame* GetMainFrame();

// iUnitModeListener
   void OnUnitsModeChanging()
   {
      Fire_UnitsChanging();
   }

   void OnUnitsModeChanged(WBFL::EAF::UnitMode newUnitMode)
   {
      Fire_UnitsChanged(newUnitMode);
   }

   // Agent
public:
   std::_tstring GetName() const override { return _T("EAFDocProxyAgent"); }
   bool Init() override;
	bool RegisterInterfaces() override;
   bool ShutDown() override;
   CLSID GetCLSID() const override;


// IEAFViewRegistrar
public:
   long RegisterView(UINT nResourceID,std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback,CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu=nullptr,int maxViewCount=-1) override;
   void RemoveView(long key) override;
   CView* CreateView(long key,LPVOID pData=0) override;
   void UpdateRegisteredView(long key,CView* pSender,LPARAM lHint,CObject* pHint) override;
   std::vector<CView*> GetRegisteredView(long key) override;

// IEAFMainMenu
public:
   std::shared_ptr<WBFL::EAF::Menu> GetMainMenu() override;
   std::shared_ptr<WBFL::EAF::Menu> CreateContextMenu() override;

// IEAFToolbars
public:
   UINT CreateToolBar(LPCTSTR lpszName) override;
   std::shared_ptr<WBFL::EAF::ToolBar> GetToolBar(UINT toolbarID) override;
   void DestroyToolBar(UINT toolbarID) override;

// IEAFAcceleratorTable
public:
   BOOL AddAccelTable(HACCEL hAccel,std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) override;
   BOOL AddAccelKey(BYTE fVirt,WORD key,WORD cmd, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) override;
   BOOL RemoveAccelKey(WORD cmd, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback) override;
   BOOL RemoveAccelKey(BYTE fVirt,WORD key) override;


// IEAFDocument
public:
   BOOL IsModified() override;
   void SetModified(BOOL bModified) override;
   void Save() override;
   void SaveAs(LPCTSTR strPathName,BOOL bReplace) override;
   CString GetFileName() override;
   CString GetFileTitle() override;
   CString GetFilePath() override;
   CString GetFileRoot() override;
   void UpdateAllViews(CView* pSender,LPARAM lHint = 0L,CObject* pHint = nullptr) override;

// IEAFDisplayUnits
public:
   void                            SetUnitMode(WBFL::EAF::UnitMode unitMode) override;
   WBFL::EAF::UnitMode              GetUnitMode() override;
   const WBFL::Units::StationFormat&        GetStationFormat() override;
   const WBFL::Units::ScalarData&            GetScalarFormat() override;
   const WBFL::Units::ScalarData&            GetPercentageFormat() override;
   const WBFL::Units::LengthData&        GetComponentDimUnit() override;
   const WBFL::Units::LengthData&        GetXSectionDimUnit() override;
   const WBFL::Units::LengthData&        GetSpanLengthUnit() override;
   const WBFL::Units::LengthData&        GetDeflectionUnit()  override;
   const WBFL::Units::LengthData&        GetAlignmentLengthUnit() override;
   const WBFL::Units::Length2Data&       GetAreaUnit() override;
   const WBFL::Units::Length4Data&       GetMomentOfInertiaUnit() override;
   const WBFL::Units::Length3Data&       GetSectModulusUnit() override;
   const WBFL::Units::PressureData&      GetStressUnit() override;
   const WBFL::Units::PressureData&      GetModEUnit() override;
   const WBFL::Units::ForceData&         GetGeneralForceUnit() override;
   const WBFL::Units::ForceData&         GetTonnageUnit() override;
   const WBFL::Units::ForceData&         GetShearUnit() override;
   const WBFL::Units::MomentData&        GetMomentUnit() override;
   const WBFL::Units::MomentData&        GetSmallMomentUnit() override;
   const WBFL::Units::AngleData&         GetAngleUnit() override;
   const WBFL::Units::AngleData&         GetRadAngleUnit() override;  // Radians always
   const WBFL::Units::DensityData&       GetDensityUnit() override;
   const WBFL::Units::MassPerLengthData& GetMassPerLengthUnit() override;
   const WBFL::Units::ForcePerLengthData& GetForcePerLengthUnit() override;
   const WBFL::Units::MomentPerAngleData& GetMomentPerAngleUnit() override;
   const WBFL::Units::TimeData&          GetShortTimeUnit() override;
   const WBFL::Units::TimeData&          GetWholeDaysUnit() override;
   const WBFL::Units::TimeData&          GetFractionalDaysUnit() override;
   const WBFL::Units::AreaPerLengthData& GetAvOverSUnit() override;
   const WBFL::Units::ForceLength2Data&  GetStiffnessUnit() override;
   const WBFL::Units::SqrtPressureData&   GetTensionCoefficientUnit() override;
   const WBFL::Units::PerLengthData&      GetPerLengthUnit() override;
   const WBFL::Units::PerLengthData&      GetCurvatureUnit() override;
   const WBFL::Units::PressureData&       GetSidewalkPressureUnit() override;
   const WBFL::Units::PressureData&       GetOverlayWeightUnit() override;
   const WBFL::Units::PressureData&       GetWindPressureUnit() override;
   const WBFL::Units::TemperatureData&    GetTemperatureUnit() override;
   const WBFL::Units::VelocityData&       GetVelocityUnit() override;

// IEAFStatusCenter
public:
   StatusCallbackIDType RegisterCallback(std::shared_ptr<WBFL::EAF::StatusCallback> pCallback) override;
   StatusGroupIDType CreateStatusGroupID() override;
   StatusItemIDType Add(std::shared_ptr<WBFL::EAF::StatusItem> pItem) override;
   bool RemoveByID(StatusItemIDType id) override;
   bool RemoveByIndex(IndexType index) override;
   bool RemoveByStatusGroupID(StatusGroupIDType statusGroupID) override;
   std::shared_ptr<WBFL::EAF::StatusItem> GetByID(StatusItemIDType id) override;
   std::shared_ptr<WBFL::EAF::StatusItem> GetByIndex(IndexType index) override;
   WBFL::EAF::StatusSeverityType GetSeverity(std::shared_ptr<const WBFL::EAF::StatusItem> pItem) override;
   WBFL::EAF::StatusSeverityType GetSeverity() override;
   IndexType Count() override;

// IEAFTransactions
public:
   void Execute(const WBFL::EAF::Transaction& rTxn) override;
   void Execute(std::unique_ptr<WBFL::EAF::Transaction>&& pTxn) override;
   void Undo() override;
   void Redo() override;
   void Repeat() override;
   bool CanUndo() const override;
   bool CanRedo() const override;
   bool CanRepeat() const override;
   std::_tstring UndoName() const override;
   std::_tstring RedoName() const override;
   std::_tstring RepeatName() const override;
   IndexType GetTxnCount() const override;
   IndexType GetUndoCount() const override;

// IEAFProjectLog
public:
   void LogMessage( LPCTSTR lpszMsg ) override;

//// IEAFProgress
//public:
//   HRESULT CreateProgressWindow(DWORD dwMask, UINT nDelay) override;
//   HRESULT Init(short begin, short end, short inc) override;
//   HRESULT Increment() override;
//   HRESULT UpdateMessage(LPCTSTR msg) override;
//   HRESULT Continue() override;
//   HRESULT DestroyProgressWindow() override;

protected:
   EAF_DECLARE_AGENT_DATA;

   CEAFBrokerDocument* m_pDoc;
   CEAFMainFrame* m_pMainFrame;

   //CProgressThread* m_pThread = nullptr;
   //Int16 m_cProgressRef = 0; // progress thread ref count
   //HRESULT ValidateThread();
   //std::vector<std::_tstring> m_MessageStack;
   //std::_tstring m_LastMessage;

   //CEAFCommandLineInfo::CommandLineDisplayMode m_CommandLineDisplayMode;  // display mode if in command line mode

   bool IsLogFileOpen();
   void OpenLogFile();
};
