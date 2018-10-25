// BridgeGeometry.h : Declaration of the CBridgeGeometry

#pragma once
#include "resource.h"       // main symbols

#include <WBFLBridgeGeometry.h>
#include <WBFLGenericBridge.h>
#include <WBFLCogo.h>
#include "BridgeGeometryInterfaces.h"
#include "CPBridgeGeometryAgent.h"
#include <EAF\EAFUIIntegration.h> // for ICommandCallback

class CBridgeGeometryAgent;

// It is easiest to use the MFC command routing
// system. Create a specialized command target
// that routes the messages back to the agent.
//
// If I was really smart, I'd figure out how
// to use the ATL message routing system instead of
// CCmdTarget... That will be for another day
class CMyCmdTarget : public CCmdTarget
{
public:
   CMyCmdTarget() {};
   CBridgeGeometryAgent* m_pAgent;

   void OnEditAlignment();

   DECLARE_MESSAGE_MAP()
};

// CBridgeGeometry

class ATL_NO_VTABLE CBridgeGeometryAgent :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBridgeGeometryAgent, &CLSID_BridgeGeometryAgent>,
	public IConnectionPointContainerImpl<CBridgeGeometryAgent>,
   public CProxyIRoadwayDataEventSink<CBridgeGeometryAgent>,
   public IAgentEx,
   public IAgentUIIntegration,
   public IEAFCommandCallback,
   public IRoadwayData,
   public IRoadway,
   public IRoadwayDisplayBuilder
{
public:
   friend CMyCmdTarget;
	CBridgeGeometryAgent()
	{
      m_CmdTarget.m_pAgent = this;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BRIDGEGEOMETRYAGENT)


BEGIN_COM_MAP(CBridgeGeometryAgent)
	COM_INTERFACE_ENTRY(IAgentEx)
   COM_INTERFACE_ENTRY(IAgentUIIntegration)
   COM_INTERFACE_ENTRY(IEAFCommandCallback)
   COM_INTERFACE_ENTRY(IRoadwayData)
   COM_INTERFACE_ENTRY(IRoadway)
   COM_INTERFACE_ENTRY(IRoadwayDisplayBuilder)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()


BEGIN_CONNECTION_POINT_MAP(CBridgeGeometryAgent)
   CONNECTION_POINT_ENTRY( IID_IRoadwayDataEvents )
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      m_bNeedsValidation = true;
      HRESULT hr = m_CogoModel.CoCreateInstance(CLSID_CogoModel);
      ATLASSERT(SUCCEEDED(hr));
      return hr;
	}

	void FinalRelease()
	{
	}

private:
   IBroker* m_pBroker;
   CMyCmdTarget m_CmdTarget;

   bool m_bNeedsValidation;
   CComPtr<ICogoModel> m_CogoModel;

   DWORD m_dwCookie; // connection point cookie for roadway data
   void AdviseConnectionPoints();
   void UnadviseConnectionPoints();

   long m_ViewKey;
   void RegisterViews();
   void UnregisterViews();

   void Validate();
   HRESULT GetAlignment(CogoObjectID alignmentID,IAlignment** ppAlignment);


   //CAlignmentManager m_AlignmentMgr;

   // Initialization helper functions
   CEAFMenu* m_pAlignmentMenu;
   void IntegrateMenuCommands();
   void RemoveMenuCommands();

   // Message map functions
   void OnEditAlignment();

// IAgentEx
public:
   STDMETHOD(SetBroker)(/*[in]*/ IBroker* pBroker);
   STDMETHOD(RegInterfaces)();
	STDMETHOD(Init)();
	STDMETHOD(Init2)();
	STDMETHOD(Reset)();
	STDMETHOD(ShutDown)();
   STDMETHOD(GetClassID)(CLSID* pCLSID);

// IAgentUIIntegration
public:
   STDMETHOD(IntegrateWithUI)(BOOL bIntegrate);

// IRoadway
public:
   virtual void GetBearing(IDType alignmentID,Float64 station,IDirection** ppBearing);
   virtual void GetNormal(IDType alignmentID,Float64 station,IDirection** ppBearing);

// ICommandCallback
public:
   virtual BOOL OnCommandMessage(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo);
   virtual BOOL GetStatusBarMessageString(UINT nID, CString& rMessage) const;
   virtual BOOL GetToolTipMessageString(UINT nID, CString& rMessage) const;

// IRoadwayData
public:
   virtual IndexType GetAlignmentCount();
   virtual IndexType GetAlignmentIndex(IDType alignmentID);
   virtual IDType GetAlignmentID(IndexType alignmentIdx);
//   virtual void SetAlignmentDescription(Int32 alignmentID,const CAlignmentDescription& alignmentDesc);
   //virtual CAlignmentDescription GetAlignmentDescription(Int32 alignmentID);

// IRoadwayDisplayBuilder
public:
   virtual void BuildRoadwayDisplay(CDisplayView* pView);
};

OBJECT_ENTRY_AUTO(__uuidof(BridgeGeometryAgent), CBridgeGeometryAgent)
