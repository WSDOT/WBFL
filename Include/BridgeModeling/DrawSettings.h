///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODELING_DRAWSETTINGS_H_
#define INCLUDED_BRIDGEMODELING_DRAWSETTINGS_H_
#pragma once

// Bridge Model Editor
//================================================
// all possible settings for bridge model editor;
//       plan view
#define BMF_PV_LABEL_PIERS      ((DWORD)0x00000001)
#define BMF_PV_LABEL_ALIGNMENT  ((DWORD)0x00000002)
#define BMF_PV_LABEL_GIRDERS    ((DWORD)0x00000004)
#define BMF_PV_LABEL_TICKMARKS  ((DWORD)0x00000008)
#define BMF_PV_SHOW_TICKMARKS   ((DWORD)0x00000010)
#define BMF_PV_DRAW_ISOTROPIC   ((DWORD)0x00000020)
#define BMF_PV_DRAW_TO_SCALE    ((DWORD)0x00000040)

// reserve
// #define                   ((DWORD)0x00000080)

// section view
#define BMF_CS_LABEL_GIRDERS    ((DWORD)0x00000100)
#define BMF_CS_SHOW_DIMENSIONS  ((DWORD)0x00000200)
#define BMF_CS_DRAW_ISOTROPIC   ((DWORD)0x00000400)
#define BMF_CS_DRAW_TO_SCALE    ((DWORD)0x00000800)
// #define                   ((DWORD)0x00001000)

// Girder Model 
// ======================================
// all possible settings for girder model editor;
//       section view
#define BMF_GSV_SHOW_STRANDS     ((DWORD)0x00000001)
#define BMF_GSV_SHOW_PS_CG       ((DWORD)0x00000002)
#define BMF_GSV_SHOW_DIMENSIONS  ((DWORD)0x00000004)
#define BMF_GSV_DRAW_ISOTROPIC   ((DWORD)0x00000008)
#define BMF_GSV_DRAW_TO_SCALE    ((DWORD)0x00000010)
#define BMF_GSV_SHOW_LONG_REINF  ((DWORD)0x00000020)
// reserve
//#define BMF_GSV_  ((DWORD)0x00000040)
//#define          ((DWORD)0x00000080)

// elevation view
#define BMF_GEV_SHOW_STRANDS     ((DWORD)0x00000100)
#define BMF_GEV_SHOW_PS_CG       ((DWORD)0x00000200)
#define BMF_GEV_SHOW_DIMENSIONS  ((DWORD)0x00000400)
#define BMF_GEV_DRAW_ISOTROPIC   ((DWORD)0x00000800)
#define BMF_GEV_DRAW_TO_SCALE    ((DWORD)0x00001000)
#define BMF_GEV_SHOW_STIRRUPS    ((DWORD)0x00002000)
#define BMF_GEV_SHOW_LONG_REINF  ((DWORD)0x00004000)

#endif // INCLUDED_BRIDGEMODELING_DRAWSETTINGS_H_