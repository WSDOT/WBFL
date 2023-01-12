///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2023  Washington State Department of Transportation
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

#ifndef INCLUDED_MATERIAL_MATLIB_H_
#define INCLUDED_MATERIAL_MATLIB_H_
#pragma once

/*****************************************************************************
LIBRARY
   Material

   The material modeling package provides product and analytical modeling
   services for common civil engineering materials.

DESCRIPTION
   The material modeling package provides product models for common civil
   engineering materials like concrete and steel.  The package also provides
   analytical modeling services that can be used to predict their stress-strain
   behavior.

   The sign convension used for the material models is compressive stresses
   and strains are less than zero and tensile stresses and strains are
   greater than zero.
*****************************************************************************/

#include <Private\WBFLPackage.h>

#endif // INCLUDED_MATERIAL_MATLIB_H_