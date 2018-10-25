///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner Test - Test driver for LBAM analysis library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// stdafx.cpp : source file that includes just the standard includes
//	LoadCombinerTest.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "initguid.h"

#include "WBFLLBAMLoadCombiner_i.c"
#include "WBFLLBAMLiveLoader_i.c"
#include "WBFLLBAMAnalysis_i.c"
#include "WBFLLBAMAnalysisUtility_i.c"
#include "WBFLLBAMUtility_i.c"
#include "WBFLLBAM_i.c"
#include "WBFLTools_i.c"

#if defined _DEBUG
#if defined _WIN64
#include "BogusCombinationContext/x64/Debug/BogusCombinationContext_i.c"
#else
#include "BogusCombinationContext/Win32/Debug/BogusCombinationContext_i.c"
#endif
#else
#if defined _WIN64
#include "BogusCombinationContext/x64/Release/BogusCombinationContext_i.c"
#else
#include "BogusCombinationContext/Win32/Release/BogusCombinationContext_i.c"
#endif
#endif

