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

// EAFDocProxyAgent.h: interface for the CEAFDocProxyAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EAFDocProxyAgent_H__F3E2AEF7_0B1E_41B3_979B_63CF96EB1B2F__INCLUDED_)
#define AFX_EAFDocProxyAgent_H__F3E2AEF7_0B1E_41B3_979B_63CF96EB1B2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
// CProxyIDisplayUnitsEventSink
template <class T>
class CProxyIDisplayUnitsEventSink : public IConnectionPointImpl<T, &IID_IDisplayUnitsEventSink, CComDynamicUnkArray>
{
public:

//IDisplayUnitsEventSink : IUnknown
public:
	HRESULT Fire_UnitsChanged(
      eafTypes::UnitMode newUnitsMode)
	{
		T* pT = (T*)this;

      //if ( pT->m_bHoldingEvents )
      //{
      //   sysFlags<Uint32>::Set(&pT->m_PendingEvents,EVT_UNITS);
      //   return S_OK;
      //}

      pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IDisplayUnitsEventSink* pIDisplayUnitsEventSink = reinterpret_cast<IDisplayUnitsEventSink*>(*pp);
				ret = pIDisplayUnitsEventSink->OnUnitsChanged(newUnitsMode);
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
   public CProxyIDisplayUnitsEventSink<CEAFDocProxyAgent>,
   public iUnitModeListener,
   public IAgentEx,
   public IViewRegistrar,
   public IMainMenu,
   public IToolBars,
   public IDocument,
   public IDisplayUnits,
   public IStatusCenter,
   public ITransactions,
   public IProjectLog
{
public:
	CEAFDocProxyAgent();
	virtual ~CEAFDocProxyAgent();

BEGIN_COM_MAP(CEAFDocProxyAgent)
   COM_INTERFACE_ENTRY(IAgent)
   COM_INTERFACE_ENTRY(IAgentEx)
   COM_INTERFACE_ENTRY(IViewRegistrar)
   COM_INTERFACE_ENTRY(IMainMenu)
   COM_INTERFACE_ENTRY(IToolBars)
   COM_INTERFACE_ENTRY(IDocument)
   COM_INTERFACE_ENTRY(IDisplayUnits)
   COM_INTERFACE_ENTRY(IStatusCenter)
   COM_INTERFACE_ENTRY(ITransactions)
	COM_INTERFACE_ENTRY(IProjectLog)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CEAFDocProxyAgent)
   CONNECTION_POINT_ENTRY( IID_IDisplayUnitsEventSink )
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

// IViewRegistrar
public:
   virtual long RegisterView(CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu=NULL,int maxViewCount=-1);
   virtual void RemoveView(long key);
   virtual CView* CreateView(long key,LPVOID pData=0);

// IMainMenu
public:
   virtual CEAFMenu* GetMainMenu();

// IToolBars
public:
   virtual UINT CreateToolBar(LPCTSTR lpszName);
   virtual CEAFToolBar* GetToolBar(UINT toolbarID);
   virtual void DestroyToolBar(CEAFToolBar* pToolBar);
   virtual void DestroyToolBar(UINT toolbarID);

// IDocument
public:
   virtual BOOL IsModified();
   virtual void SetModified(BOOL bModified);
   virtual CString GetFileName();
   virtual CString GetFileTitle();
   virtual CString GetFilePath();
   virtual CString GetFileRoot();
   virtual void UpdateAllViews(CView* pSender,LPARAM lHint = 0L,CObject* pHint = NULL);

// IDisplayUnits
public:
   virtual void                            SetUnitMode(eafTypes::UnitMode unitMode);
	virtual eafTypes::UnitMode              GetUnitMode();
 	virtual const unitStationFormat&        GetStationFormat();
   virtual const unitmgtScalar&            GetScalarFormat();
   virtual const unitmgtLengthData&        GetComponentDimUnit();
   virtual const unitmgtLengthData&        GetXSectionDimUnit();
   virtual const unitmgtLengthData&        GetSpanLengthUnit();
   virtual const unitmgtLengthData&        GetDisplacementUnit() ;
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
   virtual const unitmgtTimeData&          GetLongTimeUnit();
   virtual const unitmgtAreaPerLengthData& GetAvOverSUnit();
   virtual const unitmgtForceLength2Data&  GetStiffnessUnit();
   virtual const unitmgtSqrtPressureData&   GetTensionCoefficientUnit();
   virtual const unitmgtPerLengthData&      GetPerLengthUnit();
   virtual const unitmgtPressureData&       GetSidewalkPressureUnit();
   virtual const unitmgtPressureData&       GetOverlayWeightUnit();

// IStatusCenter
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

// ITransactions
public:
   virtual void Execute(txnTransaction& rTxn);
   virtual void Execute(txnTransaction* pTxn);
   virtual void Undo();
   virtual void Redo();
   virtual void Repeat();
   virtual bool CanUndo();
   virtual bool CanRedo();
   virtual bool CanRepeat();
   virtual std::string UndoName();
   virtual std::string RedoName();
   virtual std::string RepeatName();
   virtual CollectionIndexType GetTxnCount();
   virtual CollectionIndexType GetUndoCount();

// IProjectLog
public:
   virtual CString GetName();
   virtual void LogMessage( const char* lpszMsg );
   virtual void Destroy();

protected:
   DECLARE_AGENT_DATA;
   CEAFBrokerDocument* m_pDoc;
   CEAFMainFrame* m_pMainFrame;

   CString m_LogFileName;
   DWORD m_dwLogFileCookie;

   bool IsLogFileOpen();
   void OpenLogFile();
};

#endif // !defined(AFX_EAFDocProxyAgent_H__F3E2AEF7_0B1E_41B3_979B_63CF96EB1B2F__INCLUDED_)
