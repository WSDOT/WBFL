///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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
	HRESULT Fire_UnitsChanged(
      eafTypes::UnitMode newUnitsMode)
	{
		T* pT = (T*)this;

      //if ( pT->m_bHoldingEvents )
      //{
      //   sysFlags<UINT32>::Set(&pT->m_PendingEvents,EVT_UNITS);
      //   return S_OK;
      //}

      pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
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
   void OnUnitsModeChanged(eafTypes::UnitMode newUnitMode)
   {
      Fire_UnitsChanged(newUnitMode);
   }

// IAgentEx
public:
   STDMETHOD(SetBroker)(/*[in]*/ IBroker* pBroker);
	STDMETHOD(RegInterfaces)();
	STDMETHOD(Init)();
	STDMETHOD(Init2)();
	STDMETHOD(Reset)();
	STDMETHOD(ShutDown)();
   STDMETHOD(GetClassID)(CLSID* pCLSID);

// IEAFViewRegistrar
public:
   virtual long RegisterView(UINT nResourceID,IEAFCommandCallback* pCallback,CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu=NULL,int maxViewCount=-1);
   virtual void RemoveView(long key);
   virtual CView* CreateView(long key,LPVOID pData=0);

// IEAFMainMenu
public:
   virtual CEAFMenu* GetMainMenu();
   virtual CEAFMenu* CreateContextMenu();

// IEAFToolbars
public:
   virtual UINT CreateToolBar(LPCTSTR lpszName);
   virtual CEAFToolBar* GetToolBar(UINT toolbarID);
   virtual void DestroyToolBar(CEAFToolBar* pToolBar);
   virtual void DestroyToolBar(UINT toolbarID);

// IEAFAcceleratorTable
public:
   virtual BOOL AddAccelTable(HACCEL hAccel,IEAFCommandCallback* pCallback);
   virtual BOOL AddAccelKey(BYTE fVirt,WORD key,WORD cmd,IEAFCommandCallback* pCallback);
   virtual BOOL RemoveAccelKey(WORD cmd,IEAFCommandCallback* pCallback);
   virtual BOOL RemoveAccelKey(BYTE fVirt,WORD key);


// IEAFDocument
public:
   virtual BOOL IsModified();
   virtual void SetModified(BOOL bModified);
   virtual CString GetFileName();
   virtual CString GetFileTitle();
   virtual CString GetFilePath();
   virtual CString GetFileRoot();
   virtual void UpdateAllViews(CView* pSender,LPARAM lHint = 0L,CObject* pHint = NULL);

// IEAFDisplayUnits
public:
   virtual void                            SetUnitMode(eafTypes::UnitMode unitMode);
	virtual eafTypes::UnitMode              GetUnitMode();
 	virtual const unitStationFormat&        GetStationFormat();
   virtual const unitmgtScalar&            GetScalarFormat();
   virtual const unitmgtLengthData&        GetComponentDimUnit();
   virtual const unitmgtLengthData&        GetXSectionDimUnit();
   virtual const unitmgtLengthData&        GetSpanLengthUnit();
   virtual const unitmgtLengthData&        GetDeflectionUnit() ;
   virtual const unitmgtLengthData&        GetAlignmentLengthUnit();
   virtual const unitmgtLength2Data&       GetAreaUnit();
   virtual const unitmgtLength4Data&       GetMomentOfInertiaUnit();
   virtual const unitmgtLength3Data&       GetSectModulusUnit();
   virtual const unitmgtPressureData&      GetStressUnit();
   virtual const unitmgtPressureData&      GetModEUnit();
   virtual const unitmgtForceData&         GetGeneralForceUnit();
   virtual const unitmgtForceData&         GetTonnageUnit();
   virtual const unitmgtForceData&         GetShearUnit();
   virtual const unitmgtMomentData&        GetMomentUnit();
   virtual const unitmgtMomentData&        GetSmallMomentUnit();
   virtual const unitmgtAngleData&         GetAngleUnit();
   virtual const unitmgtAngleData&         GetRadAngleUnit();  // Radians always
   virtual const unitmgtDensityData&       GetDensityUnit();
   virtual const unitmgtMassPerLengthData& GetMassPerLengthUnit();
   virtual const unitmgtForcePerLengthData& GetForcePerLengthUnit();
   virtual const unitmgtMomentPerAngleData& GetMomentPerAngleUnit();
   virtual const unitmgtTimeData&          GetShortTimeUnit();
   virtual const unitmgtTimeData&          GetWholeDaysUnit();
   virtual const unitmgtTimeData&          GetFractionalDaysUnit();
   virtual const unitmgtAreaPerLengthData& GetAvOverSUnit();
   virtual const unitmgtForceLength2Data&  GetStiffnessUnit();
   virtual const unitmgtSqrtPressureData&   GetTensionCoefficientUnit();
   virtual const unitmgtPerLengthData&      GetPerLengthUnit();
   virtual const unitmgtPerLengthData&      GetCurvatureUnit();
   virtual const unitmgtPressureData&       GetSidewalkPressureUnit();
   virtual const unitmgtPressureData&       GetOverlayWeightUnit();

// IEAFStatusCenter
public:
   virtual StatusCallbackIDType RegisterCallback(iStatusCallback* pCallback);
   virtual StatusGroupIDType CreateStatusGroupID();
   virtual StatusItemIDType Add(CEAFStatusItem* pItem);
   virtual bool RemoveByID(StatusItemIDType id);
   virtual bool RemoveByIndex(CollectionIndexType index);
   virtual bool RemoveByStatusGroupID(StatusGroupIDType statusGroupID);
   virtual CEAFStatusItem* GetByID(StatusItemIDType id);
   virtual CEAFStatusItem* GetByIndex(CollectionIndexType index);
   virtual eafTypes::StatusSeverityType GetSeverity(const CEAFStatusItem* pItem);
   virtual eafTypes::StatusSeverityType GetSeverity();
   virtual CollectionIndexType Count();

// IEAFTransactions
public:
   virtual void Execute(txnTransaction& rTxn);
   virtual void Execute(txnTransaction* pTxn);
   virtual void Undo();
   virtual void Redo();
   virtual void Repeat();
   virtual bool CanUndo();
   virtual bool CanRedo();
   virtual bool CanRepeat();
   virtual std::_tstring UndoName();
   virtual std::_tstring RedoName();
   virtual std::_tstring RepeatName();
   virtual CollectionIndexType GetTxnCount();
   virtual CollectionIndexType GetUndoCount();

// IEAFProjectLog
public:
   virtual CString GetName();
   virtual void LogMessage( LPCTSTR lpszMsg );
   virtual void Destroy();

protected:
   DECLARE_EAF_AGENT_DATA;

   CEAFBrokerDocument* m_pDoc;
   CEAFMainFrame* m_pMainFrame;

   CString m_LogFileName;
   DWORD m_dwLogFileCookie;

   bool IsLogFileOpen();
   void OpenLogFile();
};
