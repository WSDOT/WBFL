// TestDisplayUnitMgrEvents.h : Declaration of the CTestDisplayUnitMgrEvents

#pragma once

#include "CUnknown.h"

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnitGroup
class CTestDisplayUnitMgrEvents : 
	public CUnknown,
   public IDisplayUnitMgr2Events
{
public:
	CTestDisplayUnitMgrEvents() ;
   static void Test();

   DECLARE_IUNKNOWN; // Implement IUknown

   // Extent QI
   STDMETHOD(NondelegatingQueryInterface)(const IID& iid, void** ppv);

private:
   static bool m_bTestState;
   static void InitTest() { m_bTestState = false; }
   static void Pass() { m_bTestState = true; }

// IDisplayUnitMgr2Events
public:
   STDMETHOD(OnFormatChanged)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit2* displayUnit);
   STDMETHOD(OnDisplayUnitCreated)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit2* displayUnit);
   STDMETHOD(OnDisplayUnitRemoved)(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/BSTR displayUnit);
   STDMETHOD(OnDisplayUnitGroupCleared)(/*[in]*/ IDisplayUnitGroup* group);
   STDMETHOD(OnDisplayUnitGroupCreated)(/*[in]*/ IDisplayUnitGroup* group);
   STDMETHOD(OnDisplayUnitGroupRemoved)(/*[in]*/ BSTR group);
   STDMETHOD(OnDisplayUnitGroupsCleared)();
};

