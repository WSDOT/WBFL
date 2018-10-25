///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2010  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_MFCTOOLS_MFCTOOLS_H_
#define INCLUDED_MFCTOOLS_MFCTOOLS_H_
#pragma once

// This is a master include file for the MFC Tools Package
#if defined(BUILDMFCTOOLSLIB)
	#error Do not use this header file in the MFC Tools Package
   #error It is for external users only
#endif

#include <MfcTools\CogoDDX.h>
#include <MfcTools\CustomDDX.h>
#include <MfcTools\Watermark.h>
#include <MfcTools\WatermarkMainFrm.h>
#include <MfcTools\Exceptions.h>
#include <MfcTools\ddxfile.h>
#include <MfcTools\ddxfolder.h>
#include <MfcTools\ModifyButton.h>
#include <MfcTools\MetaFileStatic.h>
#include <MfcTools\Text.h>
#include <MfcTools\HyperLink.h>
#include <MfcTools\VersionInfo.h>

#endif //  INCLUDED_MFCTOOLS_MFCTOOLS_H_