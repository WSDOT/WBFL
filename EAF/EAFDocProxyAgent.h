///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <EAF\EAFApp.h>
#include <EAF\EAFInterfaceCache.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFUIIntegration.h>
#include <EAF\EAFDisplayUnits.h>
#include <EAF\EAFStatusCenter.h>
#include <EAF\EAFTransactions.h>
#include <EAF\EAFProjectLog.h>

#include <WBFLCore.h> // IBroker, et. al.


//////////////////////////////////////////////////////////////////////////////
// CProxyIEAFDisplayUnitsEventSink
template <class T>
class CProxyIEAFDisplayUnitsEventSink : public IConnectionPointImpl<T, &IID_IEAFDisplayUnitsEventSink, CComDynamicUnkArray>
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

      pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = this->m_vec.begin();
		while (pp < this->m_vec.end())
		{
			if (*pp != nullptr)
			{
				IEAFDisplayUnitsEventSink* pIEAFDisplayUnitsEventSink = reinterpret_cast<IEAFDisplayUnitsEventSink*>(*pp);
				ret = pIEAFDisplayUnitsEventSink->OnUnitsChanging();
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_UnitsChanged(eafTypes::UnitMode newUnitsMode)
	{
		T* pT = (T*)this;

      //if ( pT->m_bHoldingEvents )
      //{
      //   WBFL::System::Flags<UINT32>::Set(&pT->m_PendingEvents,EVT_UNITS);
      //   return S_OK;
      //}

      pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = this->m_vec.begin();
		while (pp < this->m_vec.end())
		{
			if (*pp != nullptr)
			{
				IEAFDisplayUnitsEventSink* pIEAFDisplayUnitsEventSink = reinterpret_cast<IEAFDisplayUnitsEventSink*>(*pp);
				ret = pIEAFDisplayUnitsEventSink->OnUnitsChanged(newUnitsMode);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

// {FFBDF482-53B0-42e5-92C8-0D1301816F70}
DEFINE_GUID(CLSID_EAFDocProxyAgent, 
0xffbdf482, 0x53b0, 0x42e5, 0x92, 0xc8, 0xd, 0x13, 0x1, 0x81, 0x6f, 0x70);

class ATL_NO_VTABLE CEAFDocProxyAgent : 
   public CComObjectRootEx<CComSingleThreadModel>,
   //public CComRefCountTracer<CEAFDocProxyAgent,CComObjectRootEx<CComSingleThreadModel> >,
   public CComCoClass<CEAFDocProxyAgent,&CLSID_EAFDocProxyAgent>,
   public IConnectionPointContainerImpl<CEAFDocProxyAgent>,
   public CProxyIEAFDisplayUnitsEventSink<CEAFDocProxyAgent>,
   public iUnitModeListener,
   public IAgentEx,
   public IEAFViewRegistrar,
   public IEAFMainMenu,
   public IEAFToolbars,
   public IEAFAcceleratorTable,
   public IEAFDocument,
   public IEAFDisplayUnits,
   public IEAFStatusCenter,
   public IEAFTransactions,
   public IEAFProjectLog
{
public:
	CEAFDocProxyAgent();
	virtual ~CEAFDocProxyAgent();

BEGIN_COM_MAP(CEAFDocProxyAgent)
   COM_INTERFACE_ENTRY(IAgent)
   COM_INTERFACE_ENTRY(IAgentEx)
   COM_INTERFACE_ENTRY(IEAFViewRegistrar)
   COM_INTERFACE_ENTRY(IEAFMainMenu)
   COM_INTERFACE_ENTRY(IEAFToolbars)
   COM_INTERFACE_ENTRY(IEAFAcceleratorTable)
   COM_INTERFACE_ENTRY(IEAFDocument)
   COM_INTERFACE_ENTRY(IEAFDisplayUnits)
   COM_INTERFACE_ENTRY(IEAFStatusCenter)
   COM_INTERFACE_ENTRY(IEAFTransactions)
	COM_INTERFACE_ENTRY(IEAFProjectLog)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CEAFDocProxyAgent)
   CONNECTION_POINT_ENTRY( IID_IEAFDisplayUnitsEventSink )
END_CONNECTION_POINT_MAP()

   void SetDocument(CEAFBrokerDocument* pDoc);
   void SetMainFrame(CEAFMainFrame* pFrame);
   CEAFMainFrame* GetMainFrame();

// iUnitModeListener
   void OnUnitsModeChanging()
   {
      Fire_UnitsChanging();
   }

   void OnUnitsModeChanged(eafTypes::UnitMode newUnitMode)
   {
      Fire_UnitsChanged(newUnitMode);
   }

   // IAgentEx
public:
   STDMETHOD(SetBroker)(/*[in]*/ IBroker* pBroker) override;
	STDMETHOD(RegInterfaces)() override;
	STDMETHOD(Init)() override;
	STDMETHOD(Init2)() override;
	STDMETHOD(Reset)() override;
	STDMETHOD(ShutDown)() override;
   STDMETHOD(GetClassID)(CLSID* pCLSID) override;

// IEAFViewRegistrar
public:
   virtual long RegisterView(UINT nResourceID,IEAFCommandCallback* pCallback,CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu=nullptr,int maxViewCount=-1) override;
   virtual void RemoveView(long key) override;
   virtual CView* CreateView(long key,LPVOID pData=0) override;
   virtual void UpdateRegisteredView(long key,CView* pSender,LPARAM lHint,CObject* pHint) override;
   virtual std::vector<CView*> GetRegisteredView(long key) override;

// IEAFMainMenu
public:
   virtual CEAFMenu* GetMainMenu() override;
   virtual CEAFMenu* CreateContextMenu() override;

// IEAFToolbars
public:
   virtual UINT CreateToolBar(LPCTSTR lpszName) override;
   virtual CEAFToolBar* GetToolBar(UINT toolbarID) override;
   virtual void DestroyToolBar(CEAFToolBar* pToolBar) override;
   virtual void DestroyToolBar(UINT toolbarID) override;

// IEAFAcceleratorTable
public:
   virtual BOOL AddAccelTable(HACCEL hAccel,IEAFCommandCallback* pCallback) override;
   virtual BOOL AddAccelKey(BYTE fVirt,WORD key,WORD cmd,IEAFCommandCallback* pCallback) override;
   virtual BOOL RemoveAccelKey(WORD cmd,IEAFCommandCallback* pCallback) override;
   virtual BOOL RemoveAccelKey(BYTE fVirt,WORD key) override;


// IEAFDocument
public:
   virtual BOOL IsModified() override;
   virtual void SetModified(BOOL bModified) override;
   virtual void Save() override;
   virtual void SaveAs(LPCTSTR strPathName,BOOL bReplace) override;
   virtual CString GetFileName() override;
   virtual CString GetFileTitle() override;
   virtual CString GetFilePath() override;
   virtual CString GetFileRoot() override;
   virtual void UpdateAllViews(CView* pSender,LPARAM lHint = 0L,CObject* pHint = nullptr) override;

// IEAFDisplayUnits
public:
   virtual void                            SetUnitMode(eafTypes::UnitMode unitMode) override;
	virtual eafTypes::UnitMode              GetUnitMode() override;
 	virtual const WBFL::Units::StationFormat&        GetStationFormat() override;
   virtual const WBFL::Units::ScalarData&            GetScalarFormat() override;
   virtual const WBFL::Units::ScalarData&            GetPercentageFormat() override;
   virtual const WBFL::Units::LengthData&        GetComponentDimUnit() override;
   virtual const WBFL::Units::LengthData&        GetXSectionDimUnit() override;
   virtual const WBFL::Units::LengthData&        GetSpanLengthUnit() override;
   virtual const WBFL::Units::LengthData&        GetDeflectionUnit()  override;
   virtual const WBFL::Units::LengthData&        GetAlignmentLengthUnit() override;
   virtual const WBFL::Units::Length2Data&       GetAreaUnit() override;
   virtual const WBFL::Units::Length4Data&       GetMomentOfInertiaUnit() override;
   virtual const WBFL::Units::Length3Data&       GetSectModulusUnit() override;
   virtual const WBFL::Units::PressureData&      GetStressUnit() override;
   virtual const WBFL::Units::PressureData&      GetModEUnit() override;
   virtual const WBFL::Units::ForceData&         GetGeneralForceUnit() override;
   virtual const WBFL::Units::ForceData&         GetTonnageUnit() override;
   virtual const WBFL::Units::ForceData&         GetShearUnit() override;
   virtual const WBFL::Units::MomentData&        GetMomentUnit() override;
   virtual const WBFL::Units::MomentData&        GetSmallMomentUnit() override;
   virtual const WBFL::Units::AngleData&         GetAngleUnit() override;
   virtual const WBFL::Units::AngleData&         GetRadAngleUnit() override;  // Radians always
   virtual const WBFL::Units::DensityData&       GetDensityUnit() override;
   virtual const WBFL::Units::MassPerLengthData& GetMassPerLengthUnit() override;
   virtual const WBFL::Units::ForcePerLengthData& GetForcePerLengthUnit() override;
   virtual const WBFL::Units::MomentPerAngleData& GetMomentPerAngleUnit() override;
   virtual const WBFL::Units::TimeData&          GetShortTimeUnit() override;
   virtual const WBFL::Units::TimeData&          GetWholeDaysUnit() override;
   virtual const WBFL::Units::TimeData&          GetFractionalDaysUnit() override;
   virtual const WBFL::Units::AreaPerLengthData& GetAvOverSUnit() override;
   virtual const WBFL::Units::ForceLength2Data&  GetStiffnessUnit() override;
   virtual const WBFL::Units::SqrtPressureData&   GetTensionCoefficientUnit() override;
   virtual const WBFL::Units::PerLengthData&      GetPerLengthUnit() override;
   virtual const WBFL::Units::PerLengthData&      GetCurvatureUnit() override;
   virtual const WBFL::Units::PressureData&       GetSidewalkPressureUnit() override;
   virtual const WBFL::Units::PressureData&       GetOverlayWeightUnit() override;
   virtual const WBFL::Units::PressureData&       GetWindPressureUnit() override;
   virtual const WBFL::Units::VelocityData&       GetVelocityUnit() override;

// IEAFStatusCenter
public:
   virtual StatusCallbackIDType RegisterCallback(iStatusCallback* pCallback) override;
   virtual StatusGroupIDType CreateStatusGroupID() override;
   virtual StatusItemIDType Add(CEAFStatusItem* pItem) override;
   virtual bool RemoveByID(StatusItemIDType id) override;
   virtual bool RemoveByIndex(IndexType index) override;
   virtual bool RemoveByStatusGroupID(StatusGroupIDType statusGroupID) override;
   virtual CEAFStatusItem* GetByID(StatusItemIDType id) override;
   virtual CEAFStatusItem* GetByIndex(IndexType index) override;
   virtual eafTypes::StatusSeverityType GetSeverity(const CEAFStatusItem* pItem) override;
   virtual eafTypes::StatusSeverityType GetSeverity() override;
   virtual IndexType Count() override;

// IEAFTransactions
public:
   virtual void Execute(const CEAFTransaction& rTxn) override;
   virtual void Execute(std::unique_ptr<CEAFTransaction>&& pTxn) override;
   virtual void Undo() override;
   virtual void Redo() override;
   virtual void Repeat() override;
   virtual bool CanUndo() const override;
   virtual bool CanRedo() const override;
   virtual bool CanRepeat() const override;
   virtual std::_tstring UndoName() const override;
   virtual std::_tstring RedoName() const override;
   virtual std::_tstring RepeatName() const override;
   virtual IndexType GetTxnCount() const override;
   virtual IndexType GetUndoCount() const override;

// IEAFProjectLog
public:
   virtual CString GetName() override;
   virtual void LogMessage( LPCTSTR lpszMsg ) override;
   virtual void Destroy() override;

protected:
   DECLARE_EAF_AGENT_DATA;

   CEAFBrokerDocument* m_pDoc;
   CEAFMainFrame* m_pMainFrame;

   CString m_LogFileName;
   DWORD m_dwLogFileCookie;

   bool IsLogFileOpen();
   void OpenLogFile();
};
