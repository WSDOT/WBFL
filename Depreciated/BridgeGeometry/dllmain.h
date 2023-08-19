///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright � 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// dllmain.h : Declaration of module class.

class CBridgeGeometryModule : public CAtlDllModuleT< CBridgeGeometryModule >
{
public :
	DECLARE_LIBID(LIBID_WBFLBridgeGeometry)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_BRIDGEGEOMETRY, "{136876E9-842B-4B06-9333-5352639498FB}")
};

extern class CBridgeGeometryModule _AtlModule;