#pragma once
#include <BridgeGeometry\BridgeGeometryExp.h>
#include <DManip\DManip.h>

// CBridgeGeometryView view

class BGCLASS CBridgeGeometryView : public CDisplayView
{
	DECLARE_DYNCREATE(CBridgeGeometryView)

protected:
	CBridgeGeometryView();           // protected constructor used by dynamic creation
	virtual ~CBridgeGeometryView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
   virtual void OnInitialUpdate();

protected:
   //virtual void CreateViewBuilder();  
   // This view class will be subclassed in Generic Bridge Agent.
   // The sub-classed view will create a view builder that is compatible with
   // the agent/broker stuff.

   void UpdateDisplayObjects();
   void BuildAlignmentDisplayObjects();
};


