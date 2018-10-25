#pragma once

#include <BridgeGeometry\BridgeGeometryExp.h>

// CBridgeGeometryFrame frame

class BGCLASS CBridgeGeometryFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CBridgeGeometryFrame)
protected:
	CBridgeGeometryFrame();           // protected constructor used by dynamic creation
	virtual ~CBridgeGeometryFrame();

protected:
	DECLARE_MESSAGE_MAP()
};


