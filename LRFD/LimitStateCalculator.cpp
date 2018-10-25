///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include <Lrfd\LrfdLib.h>

#include <Lrfd\LimitStateCalculator.h>
#include <Lrfd\VersionMgr.h>
#include <MathEx.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdLimitStateCalculator
****************************************************************************/

// Maintain as many load factors in tables as possible.
struct LoadFactors
{
   Float64 Max;
   Float64 Min;
   Float64 MaxDeflection;
   Float64 MinDeflection;
};

const LoadFactors g_DCFactors[] = { 
   {1.25,0.90,1.25,0.90},  // Strength I
   {1.25,0.90,1.25,0.90},  // Strength II
   {1.25,0.90,1.25,0.90},  // Strength III
   {1.50,1.50,1.50,1.50},  // Strength IV
   {1.25,0.90,1.25,0.90},  // Strength V
   {1.25,0.90,1.25,0.90},  // Extreme Event I
   {1.25,0.90,1.25,0.90},  // Extreme Event II IC
   {1.25,0.90,1.25,0.90},  // Extreme Event II CV
   {1.25,0.90,1.25,0.90},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.50,0.50,0.50,0.50},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_DDFactors[] = { 
   {1.80,0.45,1.80,0.45},  // Strength I
   {1.80,0.45,1.80,0.45},  // Strength II
   {1.80,0.45,1.80,0.45},  // Strength III
   {1.80,0.45,1.80,0.45},  // Strength IV
   {1.80,0.45,1.80,0.45},  // Strength V
   {1.80,0.45,1.80,0.45},  // Extreme Event I
   {1.80,0.45,1.80,0.45},  // Extreme Event II IC
   {1.80,0.45,1.80,0.45},  // Extreme Event II CV
   {1.80,0.45,1.80,0.45},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_DWFactors[] = { 
   {1.50,0.65,1.50,0.65},  // Strength I
   {1.50,0.65,1.50,0.65},  // Strength II
   {1.50,0.65,1.50,0.65},  // Strength III
   {1.50,0.65,1.50,0.65},  // Strength IV
   {1.50,0.65,1.50,0.65},  // Strength V
   {1.50,0.65,1.50,0.65},  // Extreme Event I
   {1.50,0.65,1.50,0.65},  // Extreme Event II IC
   {1.50,0.65,1.50,0.65},  // Extreme Event II CV
   {1.50,0.65,1.50,0.65},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.50,0.50,0.50,0.50},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_EHActiveFactors[] = { 
   {1.50,0.90,1.50,0.90},  // Strength I
   {1.50,0.90,1.50,0.90},  // Strength II
   {1.50,0.90,1.50,0.90},  // Strength III
   {1.50,0.90,1.50,0.90},  // Strength IV
   {1.50,0.90,1.50,0.90},  // Strength V
   {1.50,0.90,1.50,0.90},  // Extreme Event I
   {1.50,0.90,1.50,0.90},  // Extreme Event II IC
   {1.50,0.90,1.50,0.90},  // Extreme Event II CV
   {1.50,0.90,1.50,0.90},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_EHAtRestFactors[] = { 
   {1.35,0.90,1.35,0.90},  // Strength I
   {1.35,0.90,1.35,0.90},  // Strength II
   {1.35,0.90,1.35,0.90},  // Strength III
   {1.35,0.90,1.35,0.90},  // Strength IV
   {1.35,0.90,1.35,0.90},  // Strength V
   {1.35,0.90,1.35,0.90},  // Extreme Event I
   {1.35,0.90,1.35,0.90},  // Extreme Event II IC
   {1.35,0.90,1.35,0.90},  // Extreme Event II CV
   {1.35,0.90,1.35,0.90},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_EVOverallStabilityFactors[] = { 
   {1.35,0.00,1.35,0.00},  // Strength I
   {1.35,0.00,1.35,0.00},  // Strength II
   {1.35,0.00,1.35,0.00},  // Strength III
   {1.35,0.00,1.35,0.00},  // Strength IV
   {1.35,0.00,1.35,0.00},  // Strength V
   {1.35,0.00,1.35,0.00},  // Extreme Event I
   {1.35,0.00,1.35,0.00},  // Extreme Event II IC
   {1.35,0.00,1.35,0.00},  // Extreme Event II CV
   {1.35,0.00,1.35,0.00},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_EVRetainingStructuresFactors[] = { 
   {1.35,1.00,1.35,1.00},  // Strength I
   {1.35,1.00,1.35,1.00},  // Strength II
   {1.35,1.00,1.35,1.00},  // Strength III
   {1.35,1.00,1.35,1.00},  // Strength IV
   {1.35,1.00,1.35,1.00},  // Strength V
   {1.35,1.00,1.35,1.00},  // Extreme Event I
   {1.35,1.00,1.35,1.00},  // Extreme Event II IC
   {1.35,1.00,1.35,1.00},  // Extreme Event II CV
   {1.35,1.00,1.35,1.00},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_EVRigidBuriedStructuresFactors[] = { 
   {1.30,0.90,1.30,0.90},  // Strength I
   {1.30,0.90,1.30,0.90},  // Strength II
   {1.30,0.90,1.30,0.90},  // Strength III
   {1.30,0.90,1.30,0.90},  // Strength IV
   {1.30,0.90,1.30,0.90},  // Strength V
   {1.30,0.90,1.30,0.90},  // Extreme Event I
   {1.30,0.90,1.30,0.90},  // Extreme Event II IC
   {1.30,0.90,1.30,0.90},  // Extreme Event II CV
   {1.30,0.90,1.30,0.90},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_EVRigidFramesFactors[] = { 
   {1.35,0.90,1.35,0.90},  // Strength I
   {1.35,0.90,1.35,0.90},  // Strength II
   {1.35,0.90,1.35,0.90},  // Strength III
   {1.35,0.90,1.35,0.90},  // Strength IV
   {1.35,0.90,1.35,0.90},  // Strength V
   {1.35,0.90,1.35,0.90},  // Extreme Event I
   {1.35,0.90,1.35,0.90},  // Extreme Event II IC
   {1.35,0.90,1.35,0.90},  // Extreme Event II CV
   {1.35,0.90,1.35,0.90},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_EVFlexibleBuriedStructuresFactors[] = { 
   {1.95,0.90,1.95,0.90},  // Strength I
   {1.95,0.90,1.95,0.90},  // Strength II
   {1.95,0.90,1.95,0.90},  // Strength III
   {1.95,0.90,1.95,0.90},  // Strength IV
   {1.95,0.90,1.95,0.90},  // Strength V
   {1.95,0.90,1.95,0.90},  // Extreme Event I
   {1.95,0.90,1.95,0.90},  // Extreme Event II IC
   {1.95,0.90,1.95,0.90},  // Extreme Event II CV
   {1.95,0.90,1.95,0.90},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_EVFlexibleMetalBoxCulvertsFactors[] = { 
   {1.50,0.90,1.50,0.90},  // Strength I
   {1.50,0.90,1.50,0.90},  // Strength II
   {1.50,0.90,1.50,0.90},  // Strength III
   {1.50,0.90,1.50,0.90},  // Strength IV
   {1.50,0.90,1.50,0.90},  // Strength V
   {1.50,0.90,1.50,0.90},  // Extreme Event I
   {1.50,0.90,1.50,0.90},  // Extreme Event II IC
   {1.50,0.90,1.50,0.90},  // Extreme Event II CV
   {1.50,0.90,1.50,0.90},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_ESFactors[] = { 
   {1.50,0.75,1.50,0.75},  // Strength I
   {1.50,0.75,1.50,0.75},  // Strength II
   {1.50,0.75,1.50,0.75},  // Strength III
   {1.50,0.75,1.50,0.75},  // Strength IV
   {1.50,0.75,1.50,0.75},  // Strength V
   {1.50,0.75,1.50,0.75},  // Extreme Event I
   {1.50,0.75,1.50,0.75},  // Extreme Event II IC
   {1.50,0.75,1.50,0.75},  // Extreme Event II CV
   {1.50,0.75,1.50,0.75},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_LLIMFactors[] = { 
   {1.75,1.75,1.75,1.75},  // Strength I
   {1.35,1.35,1.35,1.35},  // Strength II
   {0.00,0.00,0.00,0.00},  // Strength III
   {0.00,0.00,0.00,0.00},  // Strength IV
   {1.35,1.35,1.35,1.35},  // Strength V
   {0.00,0.00,0.00,0.00},  // Extreme Event I
   {0.50,0.50,0.50,0.50},  // Extreme Event II IC
   {0.50,0.50,0.50,0.50},  // Extreme Event II CV
   {0.50,0.50,0.50,0.50},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {1.00,1.00,1.00,1.00},  // Service IA
   {1.30,1.30,1.30,1.30},  // Service II
   {0.80,0.80,0.80,0.80},  // Service III
   {0.75,0.75,0.75,0.75}   // Fatigue
};

const LoadFactors g_WAFactors[] = { 
   {1.00,1.00,1.00,1.00},  // Strength I
   {1.00,1.00,1.00,1.00},  // Strength II
   {1.00,1.00,1.00,1.00},  // Strength III
   {1.00,1.00,1.00,1.00},  // Strength IV
   {1.00,1.00,1.00,1.00},  // Strength V
   {1.00,1.00,1.00,1.00},  // Extreme Event I
   {1.00,1.00,1.00,1.00},  // Extreme Event II IC
   {1.00,1.00,1.00,1.00},  // Extreme Event II CV
   {1.00,1.00,1.00,1.00},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_WSFactors[] = { 
   {0.00,0.00,0.00,0.00},  // Strength I
   {0.00,0.00,0.00,0.00},  // Strength II
   {1.40,1.40,1.40,1.40},  // Strength III
   {0.00,0.00,0.00,0.00},  // Strength IV
   {0.40,0.40,0.40,0.40},  // Strength V
   {0.00,0.00,0.00,0.00},  // Extreme Event I
   {0.00,0.00,0.00,0.00},  // Extreme Event II IC
   {0.00,0.00,0.00,0.00},  // Extreme Event II CV
   {0.00,0.00,0.00,0.00},  // Extreme Event II CT
   {0.30,0.30,0.30,0.30},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {0.00,0.00,0.00,0.00},  // Service II
   {0.00,0.00,0.00,0.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};


const LoadFactors g_WLFactors[] = { 
   {0.00,0.00,0.00,0.00},  // Strength I
   {0.00,0.00,0.00,0.00},  // Strength II
   {0.00,0.00,0.00,0.00},  // Strength III
   {0.00,0.00,0.00,0.00},  // Strength IV
   {1.00,1.00,1.00,1.00},  // Strength V
   {0.00,0.00,0.00,0.00},  // Extreme Event I
   {0.00,0.00,0.00,0.00},  // Extreme Event II IC
   {0.00,0.00,0.00,0.00},  // Extreme Event II CV
   {0.00,0.00,0.00,0.00},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {0.00,0.00,0.00,0.00},  // Service II
   {0.00,0.00,0.00,0.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_FRFactors[] = { 
   {1.00,1.00,1.00,1.00},  // Strength I
   {1.00,1.00,1.00,1.00},  // Strength II
   {1.00,1.00,1.00,1.00},  // Strength III
   {1.00,1.00,1.00,1.00},  // Strength IV
   {1.00,1.00,1.00,1.00},  // Strength V
   {1.00,1.00,1.00,1.00},  // Extreme Event I
   {1.00,1.00,1.00,1.00},  // Extreme Event II IC
   {1.00,1.00,1.00,1.00},  // Extreme Event II CV
   {1.00,1.00,1.00,1.00},  // Extreme Event II CT
   {1.00,1.00,1.00,1.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.00,1.00},  // Service II
   {1.00,1.00,1.00,1.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_TUFactors[] = { 
   {0.50,0.50,1.20,1.20},  // Strength I
   {0.50,0.50,1.20,1.20},  // Strength II
   {0.50,0.50,1.20,1.20},  // Strength III
   {0.50,0.50,1.20,1.20},  // Strength IV
   {0.50,0.50,1.20,1.20},  // Strength V
   {0.00,0.00,0.00,0.00},  // Extreme Event I
   {0.00,0.00,0.00,0.00},  // Extreme Event II IC
   {0.00,0.00,0.00,0.00},  // Extreme Event II CV
   {0.00,0.00,0.00,0.00},  // Extreme Event II CT
   {1.00,1.00,1.20,1.20},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.20,1.20},  // Service II
   {1.00,1.00,1.20,1.20},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_CRFactors[] = { 
   {0.50,0.50,1.20,1.20},  // Strength I
   {0.50,0.50,1.20,1.20},  // Strength II
   {0.50,0.50,1.20,1.20},  // Strength III
   {0.50,0.50,1.20,1.20},  // Strength IV
   {0.50,0.50,1.20,1.20},  // Strength V
   {0.00,0.00,0.00,0.00},  // Extreme Event I
   {0.00,0.00,0.00,0.00},  // Extreme Event II IC
   {0.00,0.00,0.00,0.00},  // Extreme Event II CV
   {0.00,0.00,0.00,0.00},  // Extreme Event II CT
   {1.00,1.00,1.20,1.20},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.20,1.20},  // Service II
   {1.00,1.00,1.20,1.20},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_SHFactors[] = { 
   {0.50,0.50,1.20,1.20},  // Strength I
   {0.50,0.50,1.20,1.20},  // Strength II
   {0.50,0.50,1.20,1.20},  // Strength III
   {0.50,0.50,1.20,1.20},  // Strength IV
   {0.50,0.50,1.20,1.20},  // Strength V
   {0.00,0.00,0.00,0.00},  // Extreme Event I
   {0.00,0.00,0.00,0.00},  // Extreme Event II IC
   {0.00,0.00,0.00,0.00},  // Extreme Event II CV
   {0.00,0.00,0.00,0.00},  // Extreme Event II CT
   {1.00,1.00,1.20,1.20},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {1.00,1.00,1.20,1.20},  // Service II
   {1.00,1.00,1.20,1.20},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_EQFactors[] = { 
   {0.00,0.00,0.00,0.00},  // Strength I
   {0.00,0.00,0.00,0.00},  // Strength II
   {0.00,0.00,0.00,0.00},  // Strength III
   {0.00,0.00,0.00,0.00},  // Strength IV
   {0.00,0.00,0.00,0.00},  // Strength V
   {1.00,1.00,1.00,1.00},  // Extreme Event I
   {0.00,0.00,0.00,0.00},  // Extreme Event II IC
   {0.00,0.00,0.00,0.00},  // Extreme Event II CV
   {0.00,0.00,0.00,0.00},  // Extreme Event II CT
   {0.00,0.00,0.00,0.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {0.00,0.00,0.00,0.00},  // Service II
   {0.00,0.00,0.00,0.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_ICFactors[] = { 
   {0.00,0.00,0.00,0.00},  // Strength I
   {0.00,0.00,0.00,0.00},  // Strength II
   {0.00,0.00,0.00,0.00},  // Strength III
   {0.00,0.00,0.00,0.00},  // Strength IV
   {0.00,0.00,0.00,0.00},  // Strength V
   {0.00,0.00,0.00,0.00},  // Extreme Event I
   {1.00,1.00,1.00,1.00},  // Extreme Event II IC
   {0.00,0.00,0.00,0.00},  // Extreme Event II CV
   {0.00,0.00,0.00,0.00},  // Extreme Event II CT
   {0.00,0.00,0.00,0.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {0.00,0.00,0.00,0.00},  // Service II
   {0.00,0.00,0.00,0.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_CTFactors[] = { 
   {0.00,0.00,0.00,0.00},  // Strength I
   {0.00,0.00,0.00,0.00},  // Strength II
   {0.00,0.00,0.00,0.00},  // Strength III
   {0.00,0.00,0.00,0.00},  // Strength IV
   {0.00,0.00,0.00,0.00},  // Strength V
   {0.00,0.00,0.00,0.00},  // Extreme Event I
   {0.00,0.00,0.00,0.00},  // Extreme Event II IC
   {1.00,1.00,1.00,1.00},  // Extreme Event II CV
   {0.00,0.00,0.00,0.00},  // Extreme Event II CT
   {0.00,0.00,0.00,0.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {0.00,0.00,0.00,0.00},  // Service II
   {0.00,0.00,0.00,0.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

const LoadFactors g_CVFactors[] = { 
   {0.00,0.00,0.00,0.00},  // Strength I
   {0.00,0.00,0.00,0.00},  // Strength II
   {0.00,0.00,0.00,0.00},  // Strength III
   {0.00,0.00,0.00,0.00},  // Strength IV
   {0.00,0.00,0.00,0.00},  // Strength V
   {0.00,0.00,0.00,0.00},  // Extreme Event I
   {0.00,0.00,0.00,0.00},  // Extreme Event II IC
   {0.00,0.00,0.00,0.00},  // Extreme Event II CV
   {1.00,1.00,1.00,1.00},  // Extreme Event II CT
   {0.00,0.00,0.00,0.00},  // Service I
   {0.00,0.00,0.00,0.00},  // Service IA
   {0.00,0.00,0.00,0.00},  // Service II
   {0.00,0.00,0.00,0.00},  // Service III
   {0.00,0.00,0.00,0.00}   // Fatigue
};

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdLimitStateCalculator::lrfdLimitStateCalculator()
{
   m_HorizEarthPressure = Active;
   m_VertEarthPressure = OverallStability;
   m_MinTG  = 0.0;
   m_MaxTG  = 0.0;
   m_MinDeflTG = 0.0;
   m_MaxDeflTG = 0.0;
   m_MinEQ  = 0.0;
   m_MaxEQ  = 0.0;
   m_MinDeflEQ = 0.0;
   m_MaxDeflEQ = 0.0;
   m_MinSE  = 0.0;
   m_MaxSE  = 0.0;
   m_MinDeflSE = 0.0;
   m_MaxDeflSE = 0.0;

   m_gFx = 1.0;
   m_gFy = 1.0;
   m_gMz = 1.0;
   m_gDx = 1.0;
   m_gDy = 1.0;
   m_gRz = 1.0;
}

lrfdLimitStateCalculator::lrfdLimitStateCalculator(const lrfdLimitStateCalculator& rOther)
{
   MakeCopy(rOther);
}

lrfdLimitStateCalculator::~lrfdLimitStateCalculator()
{
}

//======================== OPERATORS  =======================================
lrfdLimitStateCalculator& lrfdLimitStateCalculator::operator= (const lrfdLimitStateCalculator& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
sysSectionAction lrfdLimitStateCalculator::ComputeLimitState(lrfdTypes::LimitState ls,Action action,lrfdTypes::Optimization opt)
{
   sysSectionAction sa;

   for ( int i = 0; i < lrfdTypes::LoadCombinationCount; i++ )
   {
      sysSectionValue design_variable;
      sysSectionValue force_load_factor;
      sysSectionValue defl_load_factor;

      switch( action )
      {
      case Fx:
         design_variable = m_Actions[i].Fx();
         break;

      case Fy:
         design_variable = m_Actions[i].Fy();
         break;

      case Mz:
         design_variable = m_Actions[i].Mz();
         break;

      case Dx:
         design_variable = m_Actions[i].Dx();
         break;

      case Dy:
         design_variable = m_Actions[i].Dy();
         break;

      case Rz:
         design_variable = m_Actions[i].Rz();
         break;
      }

      bool bMinimizing = (opt == lrfdTypes::Min ? true : false);
      if ( design_variable.Left() < 0 )
      {
         if ( bMinimizing )
         {
            force_load_factor.Left() = GetMaxLoadFactor(ls,(lrfdTypes::LoadCombination)i);
            defl_load_factor.Left()  = GetMaxDeflLoadFactor(ls,(lrfdTypes::LoadCombination)i);
         }
         else
         {
            force_load_factor.Left() = GetMinLoadFactor(ls,(lrfdTypes::LoadCombination)i);
            defl_load_factor.Left()  = GetMinDeflLoadFactor(ls,(lrfdTypes::LoadCombination)i);
         }
      }
      else
      {
         if ( bMinimizing )
         {
            force_load_factor.Left() = GetMinLoadFactor(ls,(lrfdTypes::LoadCombination)i);
            defl_load_factor.Left()  = GetMinDeflLoadFactor(ls,(lrfdTypes::LoadCombination)i);
         }
         else
         {
            force_load_factor.Left() = GetMaxLoadFactor(ls,(lrfdTypes::LoadCombination)i);
            defl_load_factor.Left()  = GetMaxDeflLoadFactor(ls,(lrfdTypes::LoadCombination)i);
         }
      }

      if ( design_variable.Right() < 0 )
      {
         if ( bMinimizing )
         {
            force_load_factor.Right() = GetMaxLoadFactor(ls,(lrfdTypes::LoadCombination)i);
            defl_load_factor.Right()  = GetMaxDeflLoadFactor(ls,(lrfdTypes::LoadCombination)i);
         }
         else
         {
            force_load_factor.Right() = GetMinLoadFactor(ls,(lrfdTypes::LoadCombination)i);
            defl_load_factor.Right()  = GetMinDeflLoadFactor(ls,(lrfdTypes::LoadCombination)i);
         }
      }
      else
      {
         if ( bMinimizing )
         {
            force_load_factor.Right() = GetMinLoadFactor(ls,(lrfdTypes::LoadCombination)i);
            defl_load_factor.Right()  = GetMinDeflLoadFactor(ls,(lrfdTypes::LoadCombination)i);
         }
         else
         {
            force_load_factor.Right() = GetMaxLoadFactor(ls,(lrfdTypes::LoadCombination)i);
            defl_load_factor.Right()  = GetMaxDeflLoadFactor(ls,(lrfdTypes::LoadCombination)i);
         }
      }

      if ( lrfdVersionMgr::GetVersion() != lrfdVersionMgr::FirstEdition1994 )
      {
         lrfdTypes::Optimization load_modifier_opt = opt;
         if ( IsEqual( GetMaxLoadFactor(ls,(lrfdTypes::LoadCombination)i),
                       GetMinLoadFactor(ls,(lrfdTypes::LoadCombination)i) 
                     ) 
            )
         {
            // If the min and max factors are the same, the use the load modifier
            // for maximum.
            load_modifier_opt = lrfdTypes::Max;
         }
         sysSectionValue load_modifier;
         load_modifier = m_LoadModifier.LoadModifier( ls, load_modifier_opt );
         force_load_factor *= load_modifier;

         load_modifier_opt = opt;
         if ( IsEqual( GetMaxDeflLoadFactor(ls,(lrfdTypes::LoadCombination)i),
                       GetMinDeflLoadFactor(ls,(lrfdTypes::LoadCombination)i) 
                     ) 
            )
         {
            // If the min and max factors are the same, the use the load modifier
            // for maximum.
            load_modifier_opt = lrfdTypes::Max;
         }
         load_modifier = m_LoadModifier.LoadModifier( ls, load_modifier_opt );
         defl_load_factor  *= load_modifier;
      }

      sysSectionValue gFx = 1;
      sysSectionValue gFy = 1;
      sysSectionValue gMz = 1;
      sysSectionValue gDx = 1;
      sysSectionValue gDy = 1;
      sysSectionValue gRz = 1;

      // Apply live load distribution factors if this is the live load + impact case
      if ( (lrfdTypes::LoadCombination)i == lrfdTypes::LLIM )
      {
         gFx = m_gFx;
         gFy = m_gFy;
         gMz = m_gMz;
         gDx = m_gDx;
         gDy = m_gDy;
         gRz = m_gRz;
      }

      // combine
      sa.Fx() += gFx * force_load_factor * m_Actions[i].Fx();
      sa.Fy() += gFy * force_load_factor * m_Actions[i].Fy();
      sa.Mz() += gMz * force_load_factor * m_Actions[i].Mz();
      sa.Dx() += gDx * defl_load_factor  * m_Actions[i].Dx();
      sa.Dy() += gDy * defl_load_factor  * m_Actions[i].Dy();
      sa.Rz() += gRz * defl_load_factor  * m_Actions[i].Rz();
   }


   if ( lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEdition1994 )
   {
      sysSectionValue load_modifier;
      load_modifier = m_LoadModifier.LoadModifier( ls );
      sa *= load_modifier;
   }


   return sa;
}

//======================== ACCESS     =======================================
void lrfdLimitStateCalculator::SetLoadModifier(const lrfdLoadModifier& lm)
{
   m_LoadModifier = lm;
}

lrfdLoadModifier lrfdLimitStateCalculator::GetLoadModifier()
{
   return m_LoadModifier;
}

void lrfdLimitStateCalculator::SetLiveLoadDistFactors(const sysSectionValue& gFx,const sysSectionValue& gFy,const sysSectionValue& gMz,
                                                      const sysSectionValue& gDx,const sysSectionValue& gDy,const sysSectionValue& gRz)
{
   m_gFx = gFx;
   m_gFy = gFy;
   m_gMz = gMz;
   m_gDx = gDx;
   m_gDy = gDy;
   m_gRz = gRz;
}

void lrfdLimitStateCalculator::GetLiveLoadDistFactors(sysSectionValue* pgFx,sysSectionValue* pgFy,sysSectionValue* pgMz,
                                                      sysSectionValue* pgDx,sysSectionValue* pgDy,sysSectionValue* pgRz)
{
   *pgFx = m_gFx;
   *pgFy = m_gFy;
   *pgMz = m_gMz;
   *pgDx = m_gDx;
   *pgDy = m_gDy;
   *pgRz = m_gRz;
}

void lrfdLimitStateCalculator::SetDC(const sysSectionAction& dc)
{
   m_Actions[lrfdTypes::DC] = dc;
}

void lrfdLimitStateCalculator::SetDD(const sysSectionAction& dd)
{
   m_Actions[lrfdTypes::DD] = dd;
}

void lrfdLimitStateCalculator::SetDW(const sysSectionAction& dw)
{
   m_Actions[lrfdTypes::DW] = dw;
}

void lrfdLimitStateCalculator::SetEH(const sysSectionAction& eh,HorizEarthPressure hep)
{
   m_Actions[lrfdTypes::EH] = eh;
   m_HorizEarthPressure = hep;
}

void lrfdLimitStateCalculator::SetEV(const sysSectionAction& ev,VertEarthPressure vep)
{
   m_Actions[lrfdTypes::EV] = ev;
   m_VertEarthPressure = vep;
}

void lrfdLimitStateCalculator::SetES(const sysSectionAction& es)
{
   m_Actions[lrfdTypes::ES] = es;
}

void lrfdLimitStateCalculator::SetLLIM(const sysSectionAction& llim)
{
   m_Actions[lrfdTypes::LLIM] = llim;
}

void lrfdLimitStateCalculator::SetCE(const sysSectionAction& ce)
{
   m_Actions[lrfdTypes::CE] = ce;
}

void lrfdLimitStateCalculator::SetBR(const sysSectionAction& br)
{
   m_Actions[lrfdTypes::BR] = br;
}

void lrfdLimitStateCalculator::SetPL(const sysSectionAction& pl)
{
   m_Actions[lrfdTypes::PL] = pl;
}

void lrfdLimitStateCalculator::SetLS(const sysSectionAction& ls)
{
   m_Actions[lrfdTypes::LS] = ls;
}

void lrfdLimitStateCalculator::SetEL(const sysSectionAction& el)
{
   m_Actions[lrfdTypes::EL] = el;
}

void lrfdLimitStateCalculator::SetWA(const sysSectionAction& wa)
{
   m_Actions[lrfdTypes::WA] = wa;
}

void lrfdLimitStateCalculator::SetWS(const sysSectionAction& ws)
{
   m_Actions[lrfdTypes::WS] = ws;
}

void lrfdLimitStateCalculator::SetWL(const sysSectionAction& wl)
{
   m_Actions[lrfdTypes::WL] = wl;
}

void lrfdLimitStateCalculator::SetFR(const sysSectionAction& fr)
{
   m_Actions[lrfdTypes::FR] = fr;
}

void lrfdLimitStateCalculator::SetTU(const sysSectionAction& tu)
{
   m_Actions[lrfdTypes::TU] = tu;
}

void lrfdLimitStateCalculator::SetCR(const sysSectionAction& cr)
{
   m_Actions[lrfdTypes::CR] = cr;
}

void lrfdLimitStateCalculator::SetSH(const sysSectionAction& sh)
{
   m_Actions[lrfdTypes::SH] = sh;
}

void lrfdLimitStateCalculator::SetTG(const sysSectionAction& tg)
{
   m_Actions[lrfdTypes::TG] = tg;
}

void lrfdLimitStateCalculator::SetSE(const sysSectionAction& se)
{
   m_Actions[lrfdTypes::SE] = se;
}

void lrfdLimitStateCalculator::SetEQ(const sysSectionAction& eq)
{
   m_Actions[lrfdTypes::EQ] = eq;
}

void lrfdLimitStateCalculator::SetIC(const sysSectionAction& ic)
{
   m_Actions[lrfdTypes::IC] = ic;
}

void lrfdLimitStateCalculator::SetCT(const sysSectionAction& ct)
{
   m_Actions[lrfdTypes::CT] = ct;
}

void lrfdLimitStateCalculator::SetCV(const sysSectionAction& cv)
{
   m_Actions[lrfdTypes::CV] = cv;
}

sysSectionAction lrfdLimitStateCalculator::GetDC() const
{
   return m_Actions[lrfdTypes::DC];
}

sysSectionAction lrfdLimitStateCalculator::GetDD() const
{
   return m_Actions[lrfdTypes::DD];
}

sysSectionAction lrfdLimitStateCalculator::GetDW() const
{
   return m_Actions[lrfdTypes::DW];
}

sysSectionAction lrfdLimitStateCalculator::GetEH() const
{
   return m_Actions[lrfdTypes::EH];
}

sysSectionAction lrfdLimitStateCalculator::GetEV() const
{
   return m_Actions[lrfdTypes::EV];
}

sysSectionAction lrfdLimitStateCalculator::GetES() const
{
   return m_Actions[lrfdTypes::ES];
}

sysSectionAction lrfdLimitStateCalculator::GetLLIM() const
{
   return m_Actions[lrfdTypes::LLIM];
}

sysSectionAction lrfdLimitStateCalculator::GetCE() const
{
   return m_Actions[lrfdTypes::CE];
}

sysSectionAction lrfdLimitStateCalculator::GetBR() const
{
   return m_Actions[lrfdTypes::BR];
}

sysSectionAction lrfdLimitStateCalculator::GetPL() const
{
   return m_Actions[lrfdTypes::PL];
}

sysSectionAction lrfdLimitStateCalculator::GetLS() const
{
   return m_Actions[lrfdTypes::LS];
}

sysSectionAction lrfdLimitStateCalculator::GetEL() const
{
   return m_Actions[lrfdTypes::EL];
}

sysSectionAction lrfdLimitStateCalculator::GetWA() const
{
   return m_Actions[lrfdTypes::WA];
}

sysSectionAction lrfdLimitStateCalculator::GetWS() const
{
   return m_Actions[lrfdTypes::WS];
}

sysSectionAction lrfdLimitStateCalculator::GetWL() const
{
   return m_Actions[lrfdTypes::WL];
}

sysSectionAction lrfdLimitStateCalculator::GetFR() const
{
   return m_Actions[lrfdTypes::FR];
}

sysSectionAction lrfdLimitStateCalculator::GetTU() const
{
   return m_Actions[lrfdTypes::TU];
}

sysSectionAction lrfdLimitStateCalculator::GetCR() const
{
   return m_Actions[lrfdTypes::CR];
}

sysSectionAction lrfdLimitStateCalculator::GetSH() const
{
   return m_Actions[lrfdTypes::SH];
}

sysSectionAction lrfdLimitStateCalculator::GetTG() const
{
   return m_Actions[lrfdTypes::TG];
}

sysSectionAction lrfdLimitStateCalculator::GetSE() const
{
   return m_Actions[lrfdTypes::SE];
}

sysSectionAction lrfdLimitStateCalculator::GetEQ() const
{
   return m_Actions[lrfdTypes::EQ];
}

sysSectionAction lrfdLimitStateCalculator::GetIC() const
{
   return m_Actions[lrfdTypes::IC];
}

sysSectionAction lrfdLimitStateCalculator::GetCT() const
{
   return m_Actions[lrfdTypes::CT];
}

sysSectionAction lrfdLimitStateCalculator::GetCV() const
{
   return m_Actions[lrfdTypes::CV];
}

lrfdLimitStateCalculator::HorizEarthPressure lrfdLimitStateCalculator::GetHorizEarthPressure() const
{
   return m_HorizEarthPressure;
}

lrfdLimitStateCalculator::VertEarthPressure lrfdLimitStateCalculator::GetVertEarthPressure() const
{
   return m_VertEarthPressure;
}

Float64 lrfdLimitStateCalculator::GetMaxDCLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DCFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinDCLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DCFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionDCLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DCFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionDCLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DCFactors[ls].MinDeflection;
}

Float64 lrfdLimitStateCalculator::GetMaxDDLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DDFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinDDLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DDFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionDDLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DDFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionDDLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DDFactors[ls].MinDeflection;
}

Float64 lrfdLimitStateCalculator::GetMaxDWLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DWFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinDWLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DWFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionDWLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DWFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionDWLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_DWFactors[ls].MinDeflection;
}

Float64 lrfdLimitStateCalculator::GetMaxEHLoadFactor(lrfdTypes::LimitState ls,HorizEarthPressure hep) const
{
   return hep == Active ? g_EHActiveFactors[ls].Max : g_EHAtRestFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinEHLoadFactor(lrfdTypes::LimitState ls,HorizEarthPressure hep) const
{
   return hep == Active ? g_EHActiveFactors[ls].Min : g_EHAtRestFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionEHLoadFactor(lrfdTypes::LimitState ls,HorizEarthPressure hep) const
{
   return hep == Active ? g_EHActiveFactors[ls].MaxDeflection : g_EHAtRestFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionEHLoadFactor(lrfdTypes::LimitState ls,HorizEarthPressure hep) const
{
   return hep == Active ? g_EHActiveFactors[ls].MinDeflection : g_EHAtRestFactors[ls].MinDeflection;
}

Float64 lrfdLimitStateCalculator::GetMaxEVLoadFactor(lrfdTypes::LimitState ls,VertEarthPressure vep) const
{
   Float64 g;
   switch( vep )
   {
   case OverallStability:
      g = g_EVOverallStabilityFactors[ls].Max;
      break;

   case RetainingStructures:
      g = g_EVRetainingStructuresFactors[ls].Max;
      break;

   case RigidBuriedStructures:
      g = g_EVRigidBuriedStructuresFactors[ls].Max;
      break;

   case RigidFrames:
      g = g_EVRigidFramesFactors[ls].Max;
      break;

   case FlexibleBuriedStructures:
      g = g_EVFlexibleBuriedStructuresFactors[ls].Max;
      break;

   case FlexibleMetalBoxCulverts:
      g = g_EVFlexibleMetalBoxCulvertsFactors[ls].Max;
      break;
   }
   return g;
}

Float64 lrfdLimitStateCalculator::GetMinEVLoadFactor(lrfdTypes::LimitState ls,VertEarthPressure vep) const
{
   Float64 g;
   switch( vep )
   {
   case OverallStability:
      g = g_EVOverallStabilityFactors[ls].Min;
      break;

   case RetainingStructures:
      g = g_EVRetainingStructuresFactors[ls].Min;
      break;

   case RigidBuriedStructures:
      g = g_EVRigidBuriedStructuresFactors[ls].Min;
      break;

   case RigidFrames:
      g = g_EVRigidFramesFactors[ls].Min;
      break;

   case FlexibleBuriedStructures:
      g = g_EVFlexibleBuriedStructuresFactors[ls].Min;
      break;

   case FlexibleMetalBoxCulverts:
      g = g_EVFlexibleMetalBoxCulvertsFactors[ls].Min;
      break;
   }
   return g;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionEVLoadFactor(lrfdTypes::LimitState ls,VertEarthPressure vep) const
{
   Float64 g;
   switch( vep )
   {
   case OverallStability:
      g = g_EVOverallStabilityFactors[ls].MaxDeflection;
      break;

   case RetainingStructures:
      g = g_EVRetainingStructuresFactors[ls].MaxDeflection;
      break;

   case RigidBuriedStructures:
      g = g_EVRigidBuriedStructuresFactors[ls].MaxDeflection;
      break;

   case RigidFrames:
      g = g_EVRigidFramesFactors[ls].MaxDeflection;
      break;

   case FlexibleBuriedStructures:
      g = g_EVFlexibleBuriedStructuresFactors[ls].MaxDeflection;
      break;

   case FlexibleMetalBoxCulverts:
      g = g_EVFlexibleMetalBoxCulvertsFactors[ls].MaxDeflection;
      break;
   }
   return g;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionEVLoadFactor(lrfdTypes::LimitState ls,VertEarthPressure vep) const
{
   Float64 g;
   switch( vep )
   {
   case OverallStability:
      g = g_EVOverallStabilityFactors[ls].MinDeflection;
      break;

   case RetainingStructures:
      g = g_EVRetainingStructuresFactors[ls].MinDeflection;
      break;

   case RigidBuriedStructures:
      g = g_EVRigidBuriedStructuresFactors[ls].MinDeflection;
      break;

   case RigidFrames:
      g = g_EVRigidFramesFactors[ls].MinDeflection;
      break;

   case FlexibleBuriedStructures:
      g = g_EVFlexibleBuriedStructuresFactors[ls].MinDeflection;
      break;

   case FlexibleMetalBoxCulverts:
      g = g_EVFlexibleMetalBoxCulvertsFactors[ls].MinDeflection;
      break;
   }
   return g;
}

Float64 lrfdLimitStateCalculator::GetMaxESLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_ESFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinESLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_ESFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionESLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_ESFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionESLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_ESFactors[ls].MinDeflection;
}

Float64 lrfdLimitStateCalculator::GetMaxLLIMLoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   if ( ls == lrfdTypes::ExtremeEventI )
      g = m_MaxEQ;
   else
      g = g_LLIMFactors[ls].Max;

   return g;
}

Float64 lrfdLimitStateCalculator::GetMinLLIMLoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   if ( ls == lrfdTypes::ExtremeEventI )
      g = m_MinEQ;
   else
      g = g_LLIMFactors[ls].Min;

   return g;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionLLIMLoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   if ( ls == lrfdTypes::ExtremeEventI )
      g = m_MaxDeflEQ;
   else
      g = g_LLIMFactors[ls].MaxDeflection;

   return g;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionLLIMLoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   if ( ls == lrfdTypes::ExtremeEventI )
      g = m_MinDeflEQ;
   else
      g = g_LLIMFactors[ls].MinDeflection;

   return g;
}

Float64 lrfdLimitStateCalculator::GetMaxCELoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMaxLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMinCELoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMinLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionCELoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMaxDeflectionLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionCELoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMinDeflectionLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMaxBRLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMaxLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMinBRLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMinLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionBRLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMaxDeflectionLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionBRLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMinDeflectionLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMaxPLLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMaxLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMinPLLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMinLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionPLLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMaxDeflectionLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionPLLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMinDeflectionLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMaxLSLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMaxLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMinLSLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMinLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionLSLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMaxDeflectionLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionLSLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMinDeflectionLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMaxELLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMaxLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMinELLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMinLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionELLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMaxDeflectionLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionELLoadFactor(lrfdTypes::LimitState ls) const
{
   return GetMinDeflectionLLIMLoadFactor(ls);
}

Float64 lrfdLimitStateCalculator::GetMaxWALoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WAFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinWALoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WAFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionWALoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WAFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionWALoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WAFactors[ls].MinDeflection;
}

Float64 lrfdLimitStateCalculator::GetMaxWSLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WSFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinWSLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WSFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionWSLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WSFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionWSLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WSFactors[ls].MinDeflection;
}

Float64 lrfdLimitStateCalculator::GetMaxWLLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WLFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinWLLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WLFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionWLLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WLFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionWLLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_WLFactors[ls].MinDeflection;
}

Float64 lrfdLimitStateCalculator::GetMaxFRLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_FRFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinFRLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_FRFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionFRLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_FRFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionFRLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_FRFactors[ls].MinDeflection;
}

Float64 lrfdLimitStateCalculator::GetMaxTULoadFactor(lrfdTypes::LimitState ls) const
{
   return g_TUFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinTULoadFactor(lrfdTypes::LimitState ls) const
{
   return g_TUFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionTULoadFactor(lrfdTypes::LimitState ls) const
{
   return g_TUFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionTULoadFactor(lrfdTypes::LimitState ls) const
{
   return g_TUFactors[ls].MinDeflection;
}


Float64 lrfdLimitStateCalculator::GetMaxCRLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CRFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinCRLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CRFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionCRLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CRFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionCRLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CRFactors[ls].MinDeflection;
}


Float64 lrfdLimitStateCalculator::GetMaxSHLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_SHFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinSHLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_SHFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionSHLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_SHFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionSHLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_SHFactors[ls].MinDeflection;
}

void lrfdLimitStateCalculator::SetTGLoadFactors(Float64 gTGmin,Float64 gTGmax,Float64 gTGdmin, Float64 gTGdmax)
{
   m_MinTG = gTGmin;
   m_MaxTG = gTGmax;
   m_MinDeflTG = gTGdmin;
   m_MaxDeflTG = gTGdmax;
}

Float64 lrfdLimitStateCalculator::GetMaxTGLoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   switch( ls )
   { 
   case lrfdTypes::StrengthI:
   case lrfdTypes::StrengthII:
   case lrfdTypes::StrengthIII:
   case lrfdTypes::StrengthV:
   case lrfdTypes::ServiceI:
   case lrfdTypes::ServiceIII:
      g = m_MaxTG;
      break;

   case lrfdTypes::StrengthIV:
   case lrfdTypes::ExtremeEventI:
   case lrfdTypes::ExtremeEventII_IC:
   case lrfdTypes::ExtremeEventII_CV:
   case lrfdTypes::ExtremeEventII_CT:
   case lrfdTypes::ServiceIA:
   case lrfdTypes::ServiceII:
   case lrfdTypes::FatigueI:
   case lrfdTypes::FatigueII:
      g = 0.0;
      break;
   }

   return g;
}

Float64 lrfdLimitStateCalculator::GetMinTGLoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   switch( ls )
   { 
   case lrfdTypes::StrengthI:
   case lrfdTypes::StrengthII:
   case lrfdTypes::StrengthIII:
   case lrfdTypes::StrengthV:
   case lrfdTypes::ServiceI:
   case lrfdTypes::ServiceIII:
      g = m_MinTG;
      break;

   case lrfdTypes::StrengthIV:
   case lrfdTypes::ExtremeEventI:
   case lrfdTypes::ExtremeEventII_IC:
   case lrfdTypes::ExtremeEventII_CV:
   case lrfdTypes::ExtremeEventII_CT:
   case lrfdTypes::ServiceIA:
   case lrfdTypes::ServiceII:
   case lrfdTypes::FatigueI:
   case lrfdTypes::FatigueII:
      g = 0.0;
      break;
   }

   return g;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionTGLoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   switch( ls )
   { 
   case lrfdTypes::StrengthI:
   case lrfdTypes::StrengthII:
   case lrfdTypes::StrengthIII:
   case lrfdTypes::StrengthV:
   case lrfdTypes::ServiceI:
   case lrfdTypes::ServiceIII:
      g = m_MaxDeflTG;
      break;

   case lrfdTypes::StrengthIV:
   case lrfdTypes::ExtremeEventI:
   case lrfdTypes::ExtremeEventII_IC:
   case lrfdTypes::ExtremeEventII_CV:
   case lrfdTypes::ExtremeEventII_CT:
   case lrfdTypes::ServiceIA:
   case lrfdTypes::ServiceII:
   case lrfdTypes::FatigueI:
   case lrfdTypes::FatigueII:
      g = 0.0;
      break;
   }

   return g;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionTGLoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   switch( ls )
   { 
   case lrfdTypes::StrengthI:
   case lrfdTypes::StrengthII:
   case lrfdTypes::StrengthIII:
   case lrfdTypes::StrengthV:
   case lrfdTypes::ServiceI:
   case lrfdTypes::ServiceIII:
      g = m_MinDeflTG;
      break;

   case lrfdTypes::StrengthIV:
   case lrfdTypes::ExtremeEventI:
   case lrfdTypes::ExtremeEventII_IC:
   case lrfdTypes::ExtremeEventII_CV:
   case lrfdTypes::ExtremeEventII_CT:
   case lrfdTypes::ServiceIA:
   case lrfdTypes::ServiceII:
   case lrfdTypes::FatigueI:
   case lrfdTypes::FatigueII:
      g = 0.0;
      break;
   }

   return g;
}


void lrfdLimitStateCalculator::SetSELoadFactors(Float64 gSEmin,Float64 gSEmax,Float64 gSEdmin,Float64 gSEdmax)
{
   m_MinSE = gSEmin;
   m_MaxSE = gSEmax;
   m_MinDeflSE = gSEdmin;
   m_MaxDeflSE = gSEdmax;
}

Float64 lrfdLimitStateCalculator::GetMaxSELoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   switch( ls )
   { 
   case lrfdTypes::StrengthI:
   case lrfdTypes::StrengthII:
   case lrfdTypes::StrengthIII:
   case lrfdTypes::StrengthV:
   case lrfdTypes::ServiceI:
   case lrfdTypes::ServiceIII:
      g = m_MaxSE;
      break;

   case lrfdTypes::StrengthIV:
   case lrfdTypes::ExtremeEventI:
   case lrfdTypes::ExtremeEventII_IC:
   case lrfdTypes::ExtremeEventII_CV:
   case lrfdTypes::ExtremeEventII_CT:
   case lrfdTypes::ServiceIA:
   case lrfdTypes::ServiceII:
   case lrfdTypes::FatigueI:
   case lrfdTypes::FatigueII:
      g = 0.0;
      break;
   }

   return g;
}

Float64 lrfdLimitStateCalculator::GetMinSELoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   switch( ls )
   { 
   case lrfdTypes::StrengthI:
   case lrfdTypes::StrengthII:
   case lrfdTypes::StrengthIII:
   case lrfdTypes::StrengthV:
   case lrfdTypes::ServiceI:
   case lrfdTypes::ServiceIII:
      g = m_MinSE;
      break;

   case lrfdTypes::StrengthIV:
   case lrfdTypes::ExtremeEventI:
   case lrfdTypes::ExtremeEventII_IC:
   case lrfdTypes::ExtremeEventII_CV:
   case lrfdTypes::ExtremeEventII_CT:
   case lrfdTypes::ServiceIA:
   case lrfdTypes::ServiceII:
   case lrfdTypes::FatigueI:
   case lrfdTypes::FatigueII:
      g = 0.0;
      break;
   }

   return g;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionSELoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   switch( ls )
   { 
   case lrfdTypes::StrengthI:
   case lrfdTypes::StrengthII:
   case lrfdTypes::StrengthIII:
   case lrfdTypes::StrengthV:
   case lrfdTypes::ServiceI:
   case lrfdTypes::ServiceIII:
      g = m_MaxDeflSE;
      break;

   case lrfdTypes::StrengthIV:
   case lrfdTypes::ExtremeEventI:
   case lrfdTypes::ExtremeEventII_IC:
   case lrfdTypes::ExtremeEventII_CV:
   case lrfdTypes::ExtremeEventII_CT:
   case lrfdTypes::ServiceIA:
   case lrfdTypes::ServiceII:
   case lrfdTypes::FatigueI:
   case lrfdTypes::FatigueII:
      g = 0.0;
      break;
   }

   return g;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionSELoadFactor(lrfdTypes::LimitState ls) const
{
   Float64 g;
   switch( ls )
   { 
   case lrfdTypes::StrengthI:
   case lrfdTypes::StrengthII:
   case lrfdTypes::StrengthIII:
   case lrfdTypes::StrengthV:
   case lrfdTypes::ServiceI:
   case lrfdTypes::ServiceIII:
      g = m_MinDeflSE;
      break;

   case lrfdTypes::StrengthIV:
   case lrfdTypes::ExtremeEventI:
   case lrfdTypes::ExtremeEventII_IC:
   case lrfdTypes::ExtremeEventII_CV:
   case lrfdTypes::ExtremeEventII_CT:
   case lrfdTypes::ServiceIA:
   case lrfdTypes::ServiceII:
   case lrfdTypes::FatigueI:
   case lrfdTypes::FatigueII:
      g = 0.0;
      break;
   }

   return g;
}

void lrfdLimitStateCalculator::SetEQLoadFactors(Float64 gEQmin,Float64 gEQmax,Float64 gEQdmin,Float64 gEQdmax)
{
   m_MinEQ = gEQmin;
   m_MaxEQ = gEQmax;
   m_MinDeflEQ = gEQdmin;
   m_MaxDeflEQ = gEQdmax;
}

Float64 lrfdLimitStateCalculator::GetMaxEQLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_EQFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinEQLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_EQFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionEQLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_EQFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionEQLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_EQFactors[ls].MinDeflection;
}


Float64 lrfdLimitStateCalculator::GetMaxICLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_ICFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinICLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_ICFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionICLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_ICFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionICLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_ICFactors[ls].MinDeflection;
}


Float64 lrfdLimitStateCalculator::GetMaxCTLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CTFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinCTLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CTFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionCTLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CTFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionCTLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CTFactors[ls].MinDeflection;
}


Float64 lrfdLimitStateCalculator::GetMaxCVLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CVFactors[ls].Max;
}

Float64 lrfdLimitStateCalculator::GetMinCVLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CVFactors[ls].Min;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflectionCVLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CVFactors[ls].MaxDeflection;
}

Float64 lrfdLimitStateCalculator::GetMinDeflectionCVLoadFactor(lrfdTypes::LimitState ls) const
{
   return g_CVFactors[ls].MinDeflection;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdLimitStateCalculator::MakeCopy(const lrfdLimitStateCalculator& rOther)
{
   // Add copy code here...
   for ( int i = 0; i < lrfdTypes::LoadCombinationCount; i++ )
      m_Actions[i] = rOther.m_Actions[i];

   m_LoadModifier = rOther.m_LoadModifier;

   m_HorizEarthPressure = rOther.m_HorizEarthPressure;
   m_VertEarthPressure = rOther.m_VertEarthPressure;
   m_MinTG  = rOther.m_MinTG;
   m_MaxTG  = rOther.m_MaxTG;
   m_MinDeflTG = rOther.m_MinDeflTG;
   m_MaxDeflTG = rOther.m_MaxDeflTG;
   m_MinEQ  = rOther.m_MinEQ;
   m_MaxEQ  = rOther.m_MaxEQ;
   m_MinDeflEQ = rOther.m_MinDeflEQ;
   m_MaxDeflEQ = rOther.m_MaxDeflEQ;
   m_MinSE  = rOther.m_MinSE;
   m_MaxSE  = rOther.m_MaxSE;
   m_MinDeflSE = rOther.m_MinDeflSE;
   m_MaxDeflSE = rOther.m_MaxDeflSE;

   m_gFx = rOther.m_gFx;
   m_gFy = rOther.m_gFy;
   m_gMz = rOther.m_gMz;
   m_gDx = rOther.m_gDx;
   m_gDy = rOther.m_gDy;
   m_gRz = rOther.m_gRz;
}

void lrfdLimitStateCalculator::MakeAssignment(const lrfdLimitStateCalculator& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
Float64 lrfdLimitStateCalculator::GetMaxLoadFactor(lrfdTypes::LimitState ls,lrfdTypes::LoadCombination combo)
{
   Float64 g;

   switch( combo )
   {
   case lrfdTypes::DC:
      g = GetMaxDCLoadFactor(ls);
      break;

   case lrfdTypes::DD:
      g = GetMaxDDLoadFactor(ls);
      break;

   case lrfdTypes::DW:
      g = GetMaxDWLoadFactor(ls);
      break;

   case lrfdTypes::EH:
      g = GetMaxEHLoadFactor(ls,m_HorizEarthPressure);
      break;

   case lrfdTypes::EV:
      g = GetMaxEVLoadFactor(ls,m_VertEarthPressure);
      break;

   case lrfdTypes::ES:
      g = GetMaxESLoadFactor(ls);
      break;

   case lrfdTypes::LLIM:
      g = GetMaxLLIMLoadFactor(ls);
      break;

   case lrfdTypes::CE:
      g = GetMaxCELoadFactor(ls);
      break;

   case lrfdTypes::BR:
      g = GetMaxBRLoadFactor(ls);
      break;

   case lrfdTypes::PL:
      g = GetMaxPLLoadFactor(ls);
      break;

   case lrfdTypes::LS:
      g = GetMaxLSLoadFactor(ls);
      break;

   case lrfdTypes::EL:
      g = GetMaxELLoadFactor(ls);
      break;

   case lrfdTypes::WA:
      g = GetMaxWALoadFactor(ls);
      break;

   case lrfdTypes::WS:
      g = GetMaxWSLoadFactor(ls);
      break;

   case lrfdTypes::WL:
      g = GetMaxWLLoadFactor(ls);
      break;

   case lrfdTypes::FR:
      g = GetMaxFRLoadFactor(ls);
      break;

   case lrfdTypes::TU:
      g = GetMaxTULoadFactor(ls);
      break;

   case lrfdTypes::CR:
      g = GetMaxCRLoadFactor(ls);
      break;

   case lrfdTypes::SH:
      g = GetMaxSHLoadFactor(ls);
      break;

   case lrfdTypes::TG:
      g = GetMaxTGLoadFactor(ls);
      break;

   case lrfdTypes::SE:
      g = GetMaxSELoadFactor(ls);
      break;

   case lrfdTypes::EQ:
      g = GetMaxEQLoadFactor(ls);
      break;

   case lrfdTypes::IC:
      g = GetMaxICLoadFactor(ls);
      break;

   case lrfdTypes::CT:
      g = GetMaxCTLoadFactor(ls);
      break;

   case lrfdTypes::CV:
      g = GetMaxCVLoadFactor(ls);
      break;
   }

   return g;
}

Float64 lrfdLimitStateCalculator::GetMinLoadFactor(lrfdTypes::LimitState ls,lrfdTypes::LoadCombination combo)
{
   Float64 g;

   switch( combo )
   {
   case lrfdTypes::DC:
      g = GetMinDCLoadFactor(ls);
      break;

   case lrfdTypes::DD:
      g = GetMinDDLoadFactor(ls);
      break;

   case lrfdTypes::DW:
      g = GetMinDWLoadFactor(ls);
      break;

   case lrfdTypes::EH:
      g = GetMinEHLoadFactor(ls,m_HorizEarthPressure);
      break;

   case lrfdTypes::EV:
      g = GetMinEVLoadFactor(ls,m_VertEarthPressure);
      break;

   case lrfdTypes::ES:
      g = GetMinESLoadFactor(ls);
      break;

   case lrfdTypes::LLIM:
      g = GetMinLLIMLoadFactor(ls);
      break;

   case lrfdTypes::CE:
      g = GetMinCELoadFactor(ls);
      break;

   case lrfdTypes::BR:
      g = GetMinBRLoadFactor(ls);
      break;

   case lrfdTypes::PL:
      g = GetMinPLLoadFactor(ls);
      break;

   case lrfdTypes::LS:
      g = GetMinLSLoadFactor(ls);
      break;

   case lrfdTypes::EL:
      g = GetMinELLoadFactor(ls);
      break;

   case lrfdTypes::WA:
      g = GetMinWALoadFactor(ls);
      break;

   case lrfdTypes::WS:
      g = GetMinWSLoadFactor(ls);
      break;

   case lrfdTypes::WL:
      g = GetMinWLLoadFactor(ls);
      break;

   case lrfdTypes::FR:
      g = GetMinFRLoadFactor(ls);
      break;

   case lrfdTypes::TU:
      g = GetMinTULoadFactor(ls);
      break;

   case lrfdTypes::CR:
      g = GetMinCRLoadFactor(ls);
      break;

   case lrfdTypes::SH:
      g = GetMinSHLoadFactor(ls);
      break;

   case lrfdTypes::TG:
      g = GetMinTGLoadFactor(ls);
      break;

   case lrfdTypes::SE:
      g = GetMinSELoadFactor(ls);
      break;

   case lrfdTypes::EQ:
      g = GetMinEQLoadFactor(ls);
      break;

   case lrfdTypes::IC:
      g = GetMinICLoadFactor(ls);
      break;

   case lrfdTypes::CT:
      g = GetMinCTLoadFactor(ls);
      break;

   case lrfdTypes::CV:
      g = GetMinCVLoadFactor(ls);
      break;
   }

   return g;
}

Float64 lrfdLimitStateCalculator::GetMaxDeflLoadFactor(lrfdTypes::LimitState ls,lrfdTypes::LoadCombination combo)
{
   Float64 g;

   switch( combo )
   {
   case lrfdTypes::DC:
      g = GetMaxDeflectionDCLoadFactor(ls);
      break;

   case lrfdTypes::DD:
      g = GetMaxDeflectionDDLoadFactor(ls);
      break;

   case lrfdTypes::DW:
      g = GetMaxDeflectionDWLoadFactor(ls);
      break;

   case lrfdTypes::EH:
      g = GetMaxDeflectionEHLoadFactor(ls,m_HorizEarthPressure);
      break;

   case lrfdTypes::EV:
      g = GetMaxDeflectionEVLoadFactor(ls,m_VertEarthPressure);
      break;

   case lrfdTypes::ES:
      g = GetMaxDeflectionESLoadFactor(ls);
      break;

   case lrfdTypes::LLIM:
      g = GetMaxDeflectionLLIMLoadFactor(ls);
      break;

   case lrfdTypes::CE:
      g = GetMaxDeflectionCELoadFactor(ls);
      break;

   case lrfdTypes::BR:
      g = GetMaxDeflectionBRLoadFactor(ls);
      break;

   case lrfdTypes::PL:
      g = GetMaxDeflectionPLLoadFactor(ls);
      break;

   case lrfdTypes::LS:
      g = GetMaxDeflectionLSLoadFactor(ls);
      break;

   case lrfdTypes::EL:
      g = GetMaxDeflectionELLoadFactor(ls);
      break;

   case lrfdTypes::WA:
      g = GetMaxDeflectionWALoadFactor(ls);
      break;

   case lrfdTypes::WS:
      g = GetMaxDeflectionWSLoadFactor(ls);
      break;

   case lrfdTypes::WL:
      g = GetMaxDeflectionWLLoadFactor(ls);
      break;

   case lrfdTypes::FR:
      g = GetMaxDeflectionFRLoadFactor(ls);
      break;

   case lrfdTypes::TU:
      g = GetMaxDeflectionTULoadFactor(ls);
      break;

   case lrfdTypes::CR:
      g = GetMaxDeflectionCRLoadFactor(ls);
      break;

   case lrfdTypes::SH:
      g = GetMaxDeflectionSHLoadFactor(ls);
      break;

   case lrfdTypes::TG:
      g = GetMaxDeflectionTGLoadFactor(ls);
      break;

   case lrfdTypes::SE:
      g = GetMaxDeflectionSELoadFactor(ls);
      break;

   case lrfdTypes::EQ:
      g = GetMaxDeflectionEQLoadFactor(ls);
      break;

   case lrfdTypes::IC:
      g = GetMaxDeflectionICLoadFactor(ls);
      break;

   case lrfdTypes::CT:
      g = GetMaxDeflectionCTLoadFactor(ls);
      break;

   case lrfdTypes::CV:
      g = GetMaxDeflectionCVLoadFactor(ls);
      break;
   }

   return g;
}

Float64 lrfdLimitStateCalculator::GetMinDeflLoadFactor(lrfdTypes::LimitState ls,lrfdTypes::LoadCombination combo)
{
   Float64 g;

   switch( combo )
   {
   case lrfdTypes::DC:
      g = GetMinDeflectionDCLoadFactor(ls);
      break;

   case lrfdTypes::DD:
      g = GetMinDeflectionDDLoadFactor(ls);
      break;

   case lrfdTypes::DW:
      g = GetMinDeflectionDWLoadFactor(ls);
      break;

   case lrfdTypes::EH:
      g = GetMinDeflectionEHLoadFactor(ls,m_HorizEarthPressure);
      break;

   case lrfdTypes::EV:
      g = GetMinDeflectionEVLoadFactor(ls,m_VertEarthPressure);
      break;

   case lrfdTypes::ES:
      g = GetMinDeflectionESLoadFactor(ls);
      break;

   case lrfdTypes::LLIM:
      g = GetMinDeflectionLLIMLoadFactor(ls);
      break;

   case lrfdTypes::CE:
      g = GetMinDeflectionCELoadFactor(ls);
      break;

   case lrfdTypes::BR:
      g = GetMinDeflectionBRLoadFactor(ls);
      break;

   case lrfdTypes::PL:
      g = GetMinDeflectionPLLoadFactor(ls);
      break;

   case lrfdTypes::LS:
      g = GetMinDeflectionLSLoadFactor(ls);
      break;

   case lrfdTypes::EL:
      g = GetMinDeflectionELLoadFactor(ls);
      break;

   case lrfdTypes::WA:
      g = GetMinDeflectionWALoadFactor(ls);
      break;

   case lrfdTypes::WS:
      g = GetMinDeflectionWSLoadFactor(ls);
      break;

   case lrfdTypes::WL:
      g = GetMinDeflectionWLLoadFactor(ls);
      break;

   case lrfdTypes::FR:
      g = GetMinDeflectionFRLoadFactor(ls);
      break;

   case lrfdTypes::TU:
      g = GetMinDeflectionTULoadFactor(ls);
      break;

   case lrfdTypes::CR:
      g = GetMinDeflectionCRLoadFactor(ls);
      break;

   case lrfdTypes::SH:
      g = GetMinDeflectionSHLoadFactor(ls);
      break;

   case lrfdTypes::TG:
      g = GetMinDeflectionTGLoadFactor(ls);
      break;

   case lrfdTypes::SE:
      g = GetMinDeflectionSELoadFactor(ls);
      break;

   case lrfdTypes::EQ:
      g = GetMinDeflectionEQLoadFactor(ls);
      break;

   case lrfdTypes::IC:
      g = GetMinDeflectionICLoadFactor(ls);
      break;

   case lrfdTypes::CT:
      g = GetMinDeflectionCTLoadFactor(ls);
      break;

   case lrfdTypes::CV:
      g = GetMinDeflectionCVLoadFactor(ls);
      break;
   }

   return g;
}

//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdLimitStateCalculator::AssertValid() const
{
   return true;
}

void lrfdLimitStateCalculator::Dump(dbgDumpContext& os) const
{
   os << "Dump for lrfdLimitStateCalculator" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdLimitStateCalculator::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdLimitStateCalculator");

   lrfdLoadModifier lm;
   lm.SetImportanceFactor( lrfdLoadModifier::Low, 0.98 );
   lm.SetDuctilityFactor( lrfdLoadModifier::Low, 0.98 );
   lm.SetRedundancyFactor( lrfdLoadModifier::Normal );

   lrfdLimitStateCalculator lsc;
   lsc.SetLoadModifier( lm );

   lsc.SetDC( 10 );
   lsc.SetDW( 10 );
   lsc.SetLLIM( -20 );

   sysSectionAction sa;
   sa = lsc.ComputeLimitState(lrfdTypes::StrengthI,
                              lrfdLimitStateCalculator::Mz,
                              lrfdTypes::Min);

   TRY_TESTME( IsEqual( sa.Mz().Left(), -18.1, 0.1 ) );

   sa = lsc.ComputeLimitState(lrfdTypes::StrengthI,
                              lrfdLimitStateCalculator::Mz,
                              lrfdTypes::Max);

   TRY_TESTME( IsEqual( sa.Mz().Left(), -7.2, 0.1 ) );

   lsc.SetLLIM( 20 );
   sa = lsc.ComputeLimitState(lrfdTypes::StrengthI,
                              lrfdLimitStateCalculator::Mz,
                              lrfdTypes::Min);

   TRY_TESTME( IsEqual( sa.Mz().Left(), 49.1, 0.1 ) );

   sa = lsc.ComputeLimitState(lrfdTypes::StrengthI,
                              lrfdLimitStateCalculator::Mz,
                              lrfdTypes::Max);

   TRY_TESTME( IsEqual( sa.Mz().Left(), 60.0, 0.1 ) );

   lsc.SetDC(-10);
   lsc.SetDW(-10);
   lsc.SetLLIM(-20);

   sa = lsc.ComputeLimitState(lrfdTypes::StrengthI,
                              lrfdLimitStateCalculator::Mz,
                              lrfdTypes::Min);

   TRY_TESTME( IsEqual( sa.Mz().Left(), -61.1, 0.1 ) );

   sa = lsc.ComputeLimitState(lrfdTypes::StrengthI,
                              lrfdLimitStateCalculator::Mz,
                              lrfdTypes::Max);

   TRY_TESTME( IsEqual( sa.Mz().Left(), -48.5, 0.1 ) );


   TESTME_EPILOG("LimitStateCalculator");
}
#endif // _UNITTEST
