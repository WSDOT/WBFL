#include "StdAfx.h"
#include "TestDisplayUnitMgrEvents.h"

bool CTestDisplayUnitMgrEvents::m_bTestState = false;

CTestDisplayUnitMgrEvents::CTestDisplayUnitMgrEvents() :
CUnknown()
{
}

STDMETHODIMP CTestDisplayUnitMgrEvents::NondelegatingQueryInterface(const IID& iid, void** ppv)
{
   if (iid == IID_IDisplayUnitMgr2Events)
   {
      return FinishQI(static_cast<IDisplayUnitMgr2Events*>(this),ppv);
   }
   else
   {
      return CUnknown::NondelegatingQueryInterface(iid,ppv);
   }

   return E_FAIL;
}

void CTestDisplayUnitMgrEvents::Test()
{
   DWORD dwCookie;

   // Create event sink
   CTestDisplayUnitMgrEvents* pMe = new CTestDisplayUnitMgrEvents;

   // Create Unit System
   CComPtr<IUnitSystem> pUS;
   pUS.CoCreateInstance( CLSID_UnitSystem );

   // Get display unit mgr
   CComPtr<IDisplayUnitMgr2> pDUM;
   pUS->get_DisplayUnitMgr(&pDUM);

   // Sink the events to the connection pointer
   pDUM.Advise( pMe, IID_IDisplayUnitMgr2Events, &dwCookie );

   ///////////////////////////////////////////////////////////////
   // Do the tests.
   // The purpose here is to make sure the events fire when they
   // are supposed to, they pass the right data, and they are
   // received by an event sink
   //
   // The stragety is to cause events to fire from the DisplayUnitMgr
   // and then sink them to this test sink. Since the events are
   // heirarchical for this object, this is an effective way to test
   // all the events and event sinks in the subordinate objects.
   ///////////////////////////////////////////////////////////////

   //
   // Test events for creating a display unit group
   //
   InitTest();
   CComPtr<IDisplayUnitGroup> pGroup;
   pDUM->CreateGroup(CComBSTR("LongLength"),CComBSTR("Length"),&pGroup);
   TRY_TEST( m_bTestState, true );

   //
   // Test Clear event on DisplayUnitMgr
   //
   InitTest();
   pDUM->Clear();
   TRY_TEST( m_bTestState, true );

   ///////////////////////////////////////////////////////////////
   // Disconnection from Connection point
   CComQIPtr<IConnectionPointContainer> pCPC( pDUM );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IDisplayUnitMgr2Events, &pCP );
   pCP->Unadvise( dwCookie );

   delete pMe;
}

STDMETHODIMP CTestDisplayUnitMgrEvents::OnFormatChanged(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit2* displayUnit)
{
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgrEvents::OnDisplayUnitCreated(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit2* displayUnit)
{
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgrEvents::OnDisplayUnitRemoved(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/BSTR displayUnit)
{
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgrEvents::OnDisplayUnitGroupCleared(/*[in]*/ IDisplayUnitGroup* group)
{
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgrEvents::OnDisplayUnitGroupCreated(/*[in]*/ IDisplayUnitGroup* group)
{
#pragma Reminder("Refine this test")
   // How do you know if group is the same group that was return in the create call above?
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgrEvents::OnDisplayUnitGroupRemoved(/*[in]*/ BSTR group)
{
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgrEvents::OnDisplayUnitGroupsCleared()
{
   Pass();
   return S_OK;
}


