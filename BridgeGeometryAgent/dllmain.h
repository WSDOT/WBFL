// dllmain.h : Declaration of module class.

class CBridgeGeometryAgentModule : public CAtlDllModuleT< CBridgeGeometryAgentModule >
{
public :
	DECLARE_LIBID(LIBID_BridgeGeometryAgentLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_BRIDGEGEOMETRY, "{D27FDDC5-835B-48C7-94EF-76287DF10AD2}")
};

extern class CBridgeGeometryAgentModule _AtlModule;
