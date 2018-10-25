// stdafx.cpp : source file that includes just the standard includes
//	LBAMViewer.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


#include <initguid.h>


	#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#endif

// define our guids
#include "LBAMViewerGUID.c"
#include <WBFLTools_i.c>
#include <WBFLGeometry_i.c>
#include <WBFLLBAM_i.c>
#include <WBFLLBAMAnalysis_i.c>
#include <WBFLLBAMLiveLoader_i.c>
#include <WBFLLBAMUtility_i.c>
#include <WBFLLBAMAnalysisUtility_i.c>
#include <DManip\DManip_clsid.cpp>
#include "LBAMViewer_i.c"
#include "LBAMTruckDrawStrategy.h"
#include "LBAMTruckEvents.h"
#include <WBFLDManip.h>
#include <WBFLDManip_i.c>
#include <WBFLDManipTools.h>
#include <WBFLDManipTools_i.c>
