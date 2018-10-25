// dllmain.h : Declaration of module class.

class CBridgeGeometryModule : public CAtlDllModuleT< CBridgeGeometryModule >
{
public :
	DECLARE_LIBID(LIBID_WBFLBridgeGeometry)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_BRIDGEGEOMETRY, "{136876E9-842B-4B06-9333-5352639498FB}")
};

extern class CBridgeGeometryModule _AtlModule;
