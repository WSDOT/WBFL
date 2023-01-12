///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\Shear.h>
#include <Lrfd\XShear.h>
#include <Lrfd\XCodeVersion.h>
#include <Lrfd\VersionMgr.h>
#include <MathEx.h>
#include <Units\Units.h>
#include <GeomModel/GeomModel.h>
#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdShear
****************************************************************************/


// Helper functions
void compute_theta_and_beta1(lrfdShearData* pData);
void compute_theta_and_beta2(lrfdShearData* pData);
void compute_theta_and_beta3(lrfdShearData* pData,bool bWSDOT);
void compute_theta_and_beta3_tbl1(lrfdShearData* pData,bool bWSDOT);
void compute_theta_and_beta3_tbl2(lrfdShearData* pData,bool bWSDOT);
void compute_theta_and_beta4(lrfdShearData* pData); // WSDOT method per June 18, 2001 Design Memo (7-2001)
void compute_theta_and_beta5(lrfdShearData* pData);
Float64 compute_strain(lrfdShearData* pData,Float64 theta);
Float64 get_theta(Float64 vfc,Float64 ex);
Float64 get_beta(Float64 vfc,Float64 ex);
Float64 get_ex(Float64 vfc,Float64 theta);
void get_row_index(Float64 vfc,Int16* pr1,Int16* pr2);
void get_col_index(Int16 row,Float64 theta,Int16* pc1,Int16* pc2);
void get_col_index(Float64 ex,Int16* pc1,Int16* pc2);
void get_row_and_col_index(Float64 vfc,Float64 ex,
                           Int16* pr1,Int16* pr2,
                           Int16* pc1,Int16* pc2);

// Constants
static const Float64 gs_vfc[] = {0.05,0.075,0.1,0.125,0.150,0.175,0.2,0.225,0.25};
static const Float64 gs_ex[] = {-0.2e-3,-0.15e-3,-0.1e-3,0.0e-3,0.125e-3,0.25e-3,0.50e-3,0.75e-3,1.00e-3,1.50e-3,2.00e-3};
static const Int16 gs_vfc_count = sizeof(gs_vfc)/sizeof(Float64);
static const Int16 gs_ex_count = sizeof(gs_ex)/sizeof(Float64);

// constants from 2000 interims to 2002 interims
static const Float64 gs_vfc_2000[] = {0.075,0.1,0.125,0.150,0.175,0.2,0.225,0.25};
static const Float64 gs_ex_2000[] = {-0.2e-3,-0.1e-3,-0.5e-4,0.0e-3,0.125e-3,0.25e-3,0.50e-3,0.75e-3,1.00e-3,1.50e-3,2.00e-3};
static const Int16 gs_vfc_count_2000 = sizeof(gs_vfc_2000)/sizeof(Float64);
static const Int16 gs_ex_count_2000 = sizeof(gs_ex_2000)/sizeof(Float64);

// constants from 2003 interims and later
static const Float64 gs_vfc_2003[] = {0.075,0.1,0.125,0.150,0.175,0.2,0.225,0.25};
static const Float64 gs_ex_2003[] = {-0.2e-3,-0.1e-3,-0.5e-4,0.0e-3,0.125e-3,0.25e-3,0.50e-3,0.75e-3,1.00e-3};
static const Int16 gs_vfc_count_2003 = sizeof(gs_vfc_2003)/sizeof(Float64);
static const Int16 gs_ex_count_2003 = sizeof(gs_ex_2003)/sizeof(Float64);

Float64 get_vfc(Int16 row)
{
   lrfdVersionMgr::Version version = lrfdVersionMgr::GetVersion();
   if ( version < lrfdVersionMgr::SecondEditionWith2000Interims )
   {
      return gs_vfc[row];  // 1994 to 1999
   }
   else if ( lrfdVersionMgr::SecondEditionWith2000Interims <= version && version <= lrfdVersionMgr::SecondEditionWith2002Interims )
   {
      return gs_vfc_2000[row]; // 2000-2002
   }
   else // 2003 - Present
   {
      return gs_vfc_2003[row];
   }
}

Int16 get_vfc_count()
{
   lrfdVersionMgr::Version version = lrfdVersionMgr::GetVersion();
   if ( version < lrfdVersionMgr::SecondEditionWith2000Interims )
   {
      return gs_vfc_count;  // 1994 to 1999
   }
   else if ( lrfdVersionMgr::SecondEditionWith2000Interims <= version && version <= lrfdVersionMgr::SecondEditionWith2002Interims )
   {
      return gs_vfc_count_2000; // 2000-2002
   }
   else // 2003 - Present
   {
      return gs_vfc_count_2003;
   }
}

Float64 get_ex(Int16 col)
{
   lrfdVersionMgr::Version version = lrfdVersionMgr::GetVersion();
   if ( version < lrfdVersionMgr::SecondEditionWith2000Interims )
   {
      return gs_ex[col];  // 1994 to 1999
   }
   else if ( lrfdVersionMgr::SecondEditionWith2000Interims <= version && version <= lrfdVersionMgr::SecondEditionWith2002Interims )
   {
      return gs_ex_2000[col]; // 2000-2002
   }
   else // 2003 - Present
   {
      return gs_ex_2003[col];
   }
}

Int16 get_ex_count()
{
   lrfdVersionMgr::Version version = lrfdVersionMgr::GetVersion();
   if ( version < lrfdVersionMgr::SecondEditionWith2000Interims )
   {
      return gs_ex_count;  // 1994 to 1999
   }
   else if ( lrfdVersionMgr::SecondEditionWith2000Interims <= version && version <= lrfdVersionMgr::SecondEditionWith2002Interims )
   {
      return gs_ex_count_2000; // 2000-2002
   }
   else // 2003 - Present
   {
      return gs_ex_count_2003;
   }
}

struct BT
{
   Float64 Theta;
   Float64 Beta;
};

static const BT gs_Data_pre_97_interims[gs_vfc_count][gs_ex_count] = 
{            // -0,20       -0.15         -0.10        0.0         0.125         0.25        0.50        0.75          1.00          1.50          2.00
/* 0.005 */ {{27.0,6.78}, {27.0,6.17}, {27.0,5.63}, {27.0,4.88}, {27.0,3.99}, {28.5,3.49}, {29.0,2.51}, {33.0,2.37}, {36.0,2.23}, {41.0,1.95}, {43.0,1.72}},
/* 0.075 */ {{27.0,6.78}, {27.0,6.17}, {27.0,5.63}, {27.0,4.88}, {27.0,3.65}, {27.5,3.01}, {30.0,2.47}, {33.5,2.33}, {36.0,2.16}, {40.0,1.90}, {42.0,1.65}},
/* 0.100 */ {{23.5,6.50}, {23.5,5.87}, {23.5,5.31}, {23.5,3.26}, {24.0,2.61}, {26.5,2.54}, {30.5,2.41}, {34.0,2.28}, {36.0,2.09}, {38.0,1.72}, {39.0,1.45}},
/* 0.125 */ {{20.0,2.71}, {21.0,2.71}, {22.0,2.71}, {23.5,2.60}, {26.0,2.57}, {28.0,2.50}, {31.5,2.37}, {34.0,2.18}, {36.0,2.01}, {37.0,1.60}, {38.0,1.35}},
/* 0.150 */ {{22.0,2.66}, {22.5,2.61}, {23.5,2.61}, {25.0,2.55}, {27.0,2.50}, {29.0,2.45}, {32.0,2.28}, {34.0,2.06}, {36.0,1.93}, {36.5,1.50}, {37.0,1.24}},
/* 0.175 */ {{23.5,2.59}, {24.0,2.58}, {25.0,2.54}, {26.5,2.50}, {28.0,2.41}, {30.0,2.39}, {32.5,2.20}, {34.0,1.95}, {35.0,1.74}, {35.5,1.35}, {36.0,1.11}},
/* 0.200 */ {{25.0,2.55}, {25.5,2.49}, {26.5,2.48}, {27.5,2.45}, {29.0,2.37}, {31.0,2.33}, {33.0,2.10}, {34.0,1.82}, {34.5,1.58}, {35.0,1.21}, {36.0,1.00}},
/* 0.225 */ {{26.5,2.45}, {27.0,2.38}, {27.5,2.43}, {29.0,2.37}, {30.5,2.33}, {32.0,2.27}, {33.0,1.92}, {34.0,1.67}, {34.5,1.43}, {36.5,1.18}, {39.0,1.14}},
/* 0.250 */ {{28.0,2.36}, {28.5,2.32}, {29.0,2.36}, {30.0,2.30}, {31.0,2.28}, {32.0,2.01}, {33.0,1.64}, {34.0,1.52}, {35.5,1.40}, {38.5,1.30}, {41.5,1.25}}
};

static const BT gs_Data_97_interims[gs_vfc_count][gs_ex_count] = 
{            // -0,20       -0.15         -0.10        0.0         0.125         0.25        0.50        0.75          1.00          1.50          2.00
/* 0.005 */ {{27.0,6.78}, {27.0,6.17}, {27.0,5.63}, {27.0,4.88}, {27.0,3.99}, {28.5,3.49}, {29.0,2.51}, {33.0,2.37}, {36.0,2.23}, {41.0,1.95}, {43.0,1.72}},
/* 0.075 */ {{27.0,6.78}, {27.0,6.17}, {27.0,5.63}, {27.0,4.88}, {27.0,3.65}, {27.5,3.01}, {30.0,2.47}, {33.5,2.33}, {36.0,2.16}, {40.0,1.90}, {42.0,1.65}},
/* 0.100 */ {{23.5,6.50}, {23.5,5.87}, {23.5,5.31}, {23.5,3.26}, {24.0,2.61}, {26.5,2.54}, {30.5,2.41}, {34.0,2.28}, {36.0,2.09}, {38.0,1.72}, {39.0,1.45}},
/* 0.125 */ {{20.0,2.71}, {21.0,2.71}, {22.0,2.71}, {23.5,2.60}, {26.0,2.57}, {28.0,2.50}, {31.5,2.37}, {34.0,2.18}, {36.0,2.01}, {37.0,1.60}, {38.0,1.35}},
/* 0.150 */ {{22.0,2.66}, {22.5,2.61}, {23.5,2.61}, {25.0,2.55}, {27.0,2.50}, {29.0,2.45}, {32.0,2.28}, {34.0,2.06}, {36.0,1.93}, {36.5,1.50}, {37.0,1.24}},
/* 0.175 */ {{23.5,2.59}, {24.0,2.58}, {25.0,2.54}, {26.5,2.50}, {28.0,2.41}, {30.0,2.39}, {32.5,2.20}, {34.0,1.95}, {35.0,1.74}, {35.5,1.35}, {36.0,1.11}},
/* 0.200 */ {{25.0,2.55}, {25.5,2.49}, {26.5,2.48}, {27.5,2.45}, {29.0,2.37}, {31.0,2.33}, {33.0,2.10}, {34.0,1.82}, {34.5,1.58}, {35.0,1.21}, {36.0,1.00}},
/* 0.225 */ {{26.5,2.45}, {27.0,2.38}, {27.5,2.43}, {29.0,2.37}, {30.5,2.33}, {32.0,2.27}, {33.0,1.92}, {34.0,1.67}, {34.5,1.43}, {36.5,1.18}, {39.0,1.14}},
/* 0.250 */ {{28.0,2.36}, {28.5,2.36}, {29.0,2.32}, {30.0,2.30}, {31.0,2.28}, {32.0,2.01}, {33.0,1.64}, {34.0,1.52}, {35.5,1.40}, {38.5,1.30}, {41.5,1.25}}
};

static const BT gs_Data_2000_interims[gs_vfc_count_2000][gs_ex_count_2000] = 
{            // -0.20       -0.10         -0.05        0.0         0.125         0.25        0.50        0.75          1.00          1.50          2.00
/* 0.075 */ {{22.3,6.32}, {20.4,4.75}, {21.0,4.10}, {21.8,3.75}, {24.3,3.24}, {26.6,2.94}, {30.5,2.59}, {33.7,2.38}, {36.4,2.23}, {40.8,1.95}, {43.9,1.67}},
/* 0.100 */ {{18.1,3.79}, {20.4,3.38}, {21.4,3.24}, {22.5,3.14}, {24.9,2.91}, {27.1,2.75}, {30.8,2.50}, {34.0,2.32}, {36.7,2.18}, {40.8,1.93}, {43.1,1.69}},
/* 0.125 */ {{19.9,3.18}, {21.9,2.99}, {22.8,2.94}, {23.7,2.87}, {25.9,2.74}, {27.9,2.62}, {31.4,2.42}, {34.4,2.26}, {37.0,2.13}, {41.0,1.90}, {43.2,1.67}},
/* 0.150 */ {{21.6,2.88}, {23.3,2.79}, {24.2,2.78}, {25.0,2.72}, {26.9,2.60}, {28.8,2.52}, {32.1,2.36}, {34.9,2.21}, {37.3,2.08}, {40.5,1.82}, {42.8,1.61}},
/* 0.175 */ {{23.2,2.73}, {24.7,2.66}, {25.5,2.65}, {26.2,2.60}, {28.0,2.52}, {29.7,2.44}, {32.7,2.28}, {35.2,2.14}, {36.8,1.96}, {39.7,1.71}, {42.2,1.54}},
/* 0.200 */ {{24.7,2.63}, {26.1,2.59}, {26.7,2.52}, {27.4,2.51}, {29.0,2.43}, {30.6,2.37}, {32.8,2.14}, {34.5,1.94}, {36.1,1.79}, {39.2,1.61}, {41.7,1.47}},
/* 0.225 */ {{26.1,2.53}, {27.3,2.45}, {27.9,2.42}, {28.5,2.40}, {30.0,2.34}, {30.8,2.14}, {32.2,1.86}, {34.0,1.73}, {35.7,1.64}, {38.8,1.51}, {41.4,1.39}},
/* 0.250 */ {{27.5,2.39}, {28.6,2.39}, {29.1,2.33}, {29.7,2.33}, {30.6,2.12}, {31.3,1.93}, {32.8,1.70}, {34.3,1.58}, {35.8,1.50}, {38.6,1.38}, {41.2,1.29}}
};

static const BT gs_Data_2003_interims[gs_vfc_count_2003][gs_ex_count_2003] = 
{            // -0.20       -0.10         -0.05        0.0         0.125         0.25        0.50        0.75          1.00
/* 0.075 */ {{22.3,6.32}, {20.4,4.75}, {21.0,4.10}, {21.8,3.75}, {24.3,3.24}, {26.6,2.94}, {30.5,2.59}, {33.7,2.38}, {36.4,2.23}},
/* 0.100 */ {{18.1,3.79}, {20.4,3.38}, {21.4,3.24}, {22.5,3.14}, {24.9,2.91}, {27.1,2.75}, {30.8,2.50}, {34.0,2.32}, {36.7,2.18}},
/* 0.125 */ {{19.9,3.18}, {21.9,2.99}, {22.8,2.94}, {23.7,2.87}, {25.9,2.74}, {27.9,2.62}, {31.4,2.42}, {34.4,2.26}, {37.0,2.13}},
/* 0.150 */ {{21.6,2.88}, {23.3,2.79}, {24.2,2.78}, {25.0,2.72}, {26.9,2.60}, {28.8,2.52}, {32.1,2.36}, {34.9,2.21}, {37.3,2.08}},
/* 0.175 */ {{23.2,2.73}, {24.7,2.66}, {25.5,2.65}, {26.2,2.60}, {28.0,2.52}, {29.7,2.44}, {32.7,2.28}, {35.2,2.14}, {36.8,1.96}},
/* 0.200 */ {{24.7,2.63}, {26.1,2.59}, {26.7,2.52}, {27.4,2.51}, {29.0,2.43}, {30.6,2.37}, {32.8,2.14}, {34.5,1.94}, {36.1,1.79}},
/* 0.225 */ {{26.1,2.53}, {27.3,2.45}, {27.9,2.42}, {28.5,2.40}, {30.0,2.34}, {30.8,2.14}, {32.2,1.86}, {34.0,1.73}, {35.7,1.64}},
/* 0.250 */ {{27.5,2.39}, {28.6,2.39}, {29.1,2.33}, {29.7,2.33}, {30.6,2.12}, {31.3,1.93}, {32.8,1.70}, {34.3,1.58}, {35.8,1.50}}
};

BT get_beta_theta(Int16 row,Int16 col)
{
   lrfdVersionMgr::Version version = lrfdVersionMgr::GetVersion();
   if ( version < lrfdVersionMgr::FirstEditionWith1997Interims )
   {
      return gs_Data_pre_97_interims[row][col];  // 1994 to 1996
   }
   else if ( lrfdVersionMgr::FirstEditionWith1997Interims <= version && // 1997 - 1999
             version < lrfdVersionMgr::SecondEditionWith2000Interims )
   {
      return gs_Data_97_interims[row][col];
   }
   else if ( lrfdVersionMgr::SecondEditionWith2000Interims <= version && version <= lrfdVersionMgr::SecondEditionWith2002Interims )
   {
      return gs_Data_2000_interims[row][col]; // 2000-2002
   }
   else // 2003 - Present
   {
      return gs_Data_2003_interims[row][col];
   }
}

// Functions, constants and data for Sections with Less than Minimum Transverse Reinforcement.
static const Float64 gs_sxe_mtr[] = {5, 10, 15, 20, 30, 40, 60, 80};
static const Float64 gs_ex_mtr[] = {-0.2e-3,-0.1e-3,-0.5e-4,0.0e-3,0.125e-3,0.25e-3,0.50e-3,0.75e-3,1.00e-3,1.50e-3,2.00e-3};
static const Int16 gs_sxe_count_mtr = sizeof(gs_sxe_mtr)/sizeof(Float64);
static const Int16 gs_ex_count_mtr = sizeof(gs_ex_mtr)/sizeof(Float64);

static const BT gs_Data_Min_Transverse_Reinf[gs_sxe_count_mtr][gs_ex_count_mtr] = 
{            // -0,20       -0.10         -0.05        0.0           0.125         0.25        0.50        0.75          1.00          1.50          2.00
/*   5   */ {{25.4,6.36}, {25.5,6.06}, {25.9,5.56}, {26.4,5.15}, {27.7,4.41}, {28.9,3.91}, {30.9,3.26}, {32.4,2.86}, {33.7,2.58}, {35.6,2.21}, {37.2,1.96}},
/*  10   */ {{27.6,5.78}, {27.6,5.78}, {28.3,5.38}, {29.3,4.89}, {31.6,4.05}, {33.5,3.52}, {36.3,2.88}, {38.4,2.50}, {40.1,2.23}, {42.7,1.88}, {44.7,1.65}},
/*  15   */ {{29.5,5.34}, {29.5,5.34}, {29.7,5.27}, {31.1,4.73}, {34.1,3.82}, {36.5,3.28}, {39.9,2.64}, {42.4,2.26}, {44.4,2.01}, {47.4,1.68}, {49.7,1.46}},
/*  20   */ {{31.2,4.99}, {31.2,4.99}, {31.2,4.99}, {32.3,4.61}, {36.0,3.65}, {38.8,3.09}, {42.7,2.46}, {45.5,2.09}, {47.6,1.85}, {50.9,1.52}, {53.4,1.31}},
/*  30   */ {{34.1,4.46}, {34.1,4.46}, {34.1,4.46}, {34.2,4.43}, {38.9,3.39}, {42.3,2.82}, {46.9,2.19}, {50.1,1.84}, {52.6,1.60}, {56.3,1.30}, {59.0,1.10}},
/*  40   */ {{36.6,4.06}, {36.6,4.06}, {36.6,4.06}, {36.6,4.06}, {41.2,3.20}, {45.0,2.62}, {50.2,2.00}, {53.7,1.66}, {56.3,1.43}, {60.2,1.14}, {63.0,0.95}},
/*  60   */ {{40.8,3.50}, {40.8,3.50}, {40.8,3.50}, {40.8,3.50}, {44.5,2.92}, {49.2,2.32}, {55.1,1.72}, {58.9,1.40}, {61.8,1.18}, {65.8,0.92}, {68.6,0.75}},
/*  80   */ {{44.3,3.10}, {44.3,3.10}, {44.3,3.10}, {44.3,3.10}, {47.1,2.71}, {52.3,2.11}, {58.7,1.52}, {62.8,1.21}, {65.7,1.01}, {69.7,0.76}, {72.4,0.62}}
};

Float64 get_sxe_mtr(Int16 row)
{
   return gs_sxe_mtr[row];
}

Int16 get_sxe_count_mtr()
{
   return gs_sxe_count_mtr;
}

Float64 get_ex_mtr(Int16 col)
{
   return gs_ex_mtr[col];
}

Int16 get_ex_count_mtr()
{
   return gs_ex_count_mtr;
}

BT get_beta_theta_mtr(Int16 row,Int16 col)
{
   return gs_Data_Min_Transverse_Reinf[row][col];
}

void get_row_index_mtr(Float64 sxe,Int16* pr1,Int16* pr2);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdShear::~lrfdShear()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdShear::ComputeThetaAndBeta(lrfdShearData* pData, lrfdShear::Method method )
{
   // if 4th or before, method must be tables
   CHECK( (lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::FourthEdition2007 && method == lrfdShear::Tables) ||
      lrfdVersionMgr::FourthEdition2007 < lrfdVersionMgr::GetVersion() );

   if ( lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::SecondEditionWith1999Interims )
   {
      compute_theta_and_beta2( pData );
   }
   else if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FourthEdition2007 )
   {
      compute_theta_and_beta3( pData, false );
   }
   else
   {
      method == lrfdShear::Tables ? compute_theta_and_beta3(pData,false) : compute_theta_and_beta5( pData );
   }


// compute_theta_and_beta1 uses a much slower iteration...
//   try
//   {
//      compute_theta_and_beta1( pData );
//   }
//   catch( lrfdXShear& )
//   {
//      compute_theta_and_beta2( pData );
//   }
}

void lrfdShear::ComputeVciVcw(lrfdShearData* pData)
{
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FourthEdition2007   ||
        lrfdVersionMgr::GetVersion() >= lrfdVersionMgr::EighthEdition2017)
   {
      // Vci/Vcw wasn't in LRFD before 4th edition, and was removed in the 8th... 
      // set values to zero
      pData->VciMin  = 0;
      pData->VciCalc = 0;
      pData->Vci     = 0;
      pData->Vcw     = 0;

      // and throw an exception
      THROW(lrfdXCodeVersion,BadVersion);
      return;
   }

   Float64 fc   = pData->fc;
   Float64 fct  = pData->fct;
   Float64 fpc  = pData->fpc;
   Float64 dv   = pData->dv;
   Float64 bv   = pData->bv;
   Float64 Vp   = pData->Vp;
   Float64 Vd   = pData->Vd;
   Float64 Vi   = pData->Vi;
   Float64 Mmax = pData->Mu;
   Float64 Mcre = pData->Mcre;
   Float64 lambda = pData->lambda;

   Float64 VciMin  = 0;
   Float64 VciCalc = 0;
   Float64 Vci     = 0;
   Float64 Vcw     = 0;

   const WBFL::Units::Force* p_force_unit;

   Float64 K1, K2, Kfct;
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      fc   = WBFL::Units::ConvertFromSysUnits(fc,   WBFL::Units::Measure::MPa);
      fct  = WBFL::Units::ConvertFromSysUnits(fct,  WBFL::Units::Measure::MPa);
      fpc  = WBFL::Units::ConvertFromSysUnits(fpc,  WBFL::Units::Measure::MPa);
      dv   = WBFL::Units::ConvertFromSysUnits(dv,   WBFL::Units::Measure::Millimeter);
      bv   = WBFL::Units::ConvertFromSysUnits(bv,   WBFL::Units::Measure::Millimeter);
      Vp   = WBFL::Units::ConvertFromSysUnits(Vp,   WBFL::Units::Measure::Kilonewton);
      Vd   = WBFL::Units::ConvertFromSysUnits(Vd,   WBFL::Units::Measure::Kilonewton);
      Vi   = WBFL::Units::ConvertFromSysUnits(Vi,   WBFL::Units::Measure::Kilonewton);
      Mmax = WBFL::Units::ConvertFromSysUnits(Mmax, WBFL::Units::Measure::NewtonMillimeter);
      Mcre = WBFL::Units::ConvertFromSysUnits(Mcre, WBFL::Units::Measure::NewtonMillimeter);

      Kfct = 1.8;

      K1 = 0.0525;
      K2 = 0.16;


      p_force_unit = &WBFL::Units::Measure::Kilonewton;
   }
   else
   {
      fc   = WBFL::Units::ConvertFromSysUnits(fc,   WBFL::Units::Measure::KSI);
      fct  = WBFL::Units::ConvertFromSysUnits(fct,  WBFL::Units::Measure::KSI);
      fpc  = WBFL::Units::ConvertFromSysUnits(fpc,  WBFL::Units::Measure::KSI);
      dv   = WBFL::Units::ConvertFromSysUnits(dv,   WBFL::Units::Measure::Inch);
      bv   = WBFL::Units::ConvertFromSysUnits(bv,   WBFL::Units::Measure::Inch);
      Vp   = WBFL::Units::ConvertFromSysUnits(Vp,   WBFL::Units::Measure::Kip);
      Vd   = WBFL::Units::ConvertFromSysUnits(Vd,   WBFL::Units::Measure::Kip);
      Vi   = WBFL::Units::ConvertFromSysUnits(Vi,   WBFL::Units::Measure::Kip);
      Mmax = WBFL::Units::ConvertFromSysUnits(Mmax, WBFL::Units::Measure::InchLbf); // should be k-in, but we are dividing Mcre/Mmax so this is ok
      Mcre = WBFL::Units::ConvertFromSysUnits(Mcre, WBFL::Units::Measure::InchLbf); // should be k-in, but we are dividing Mcre/Mmax so this is ok

      Kfct = 4.7;

      K1 = 0.02;
      K2 = 0.06;

      p_force_unit = &WBFL::Units::Measure::Kip;
   }

   Float64 sqrt_fc;
   if ( lrfdVersionMgr::SeventhEditionWith2016Interims <= lrfdVersionMgr::GetVersion() )
   {
      sqrt_fc = lambda*sqrt(fc);
   }
   else
   {
      if (pData->ConcreteType == WBFL::Materials::ConcreteType::Normal)
      {
         sqrt_fc = sqrt(fc);
      }
      else if ((pData->ConcreteType == WBFL::Materials::ConcreteType::AllLightweight || pData->ConcreteType == WBFL::Materials::ConcreteType::SandLightweight) && pData->bHasfct)
      {
         sqrt_fc = min(Kfct*fct, sqrt(fc));
      }
      else if (pData->ConcreteType == WBFL::Materials::ConcreteType::AllLightweight && !pData->bHasfct)
      {
         sqrt_fc = 0.75*sqrt(fc);
      }
      else if (pData->ConcreteType == WBFL::Materials::ConcreteType::SandLightweight && !pData->bHasfct)
      {
         sqrt_fc = 0.85*sqrt(fc);
      }
      else if (pData->ConcreteType == WBFL::Materials::ConcreteType::PCI_UHPC)
      {
         ATLASSERT(false); // Vci/Vcw doesn't support PCI UHPC
      }
      else
      {
         ATLASSERT(false); // is there a new concrete type?
      }
   }



   VciCalc = IsZero(Mmax) ? 1e100 : K1*sqrt_fc*bv*dv + Vd + Vi*Mcre/Mmax; // 5.8.3.4.3-1
   VciMin = K2*sqrt_fc*bv*dv;// 5.8.3.4.3-1
   Vci = Max(VciCalc,VciMin);
   Vcw = (K2*sqrt_fc + 0.30*fpc)*bv*dv + Vp; // 5.8.3.4.3-2

   pData->VciMin  = WBFL::Units::ConvertToSysUnits(VciMin,  *p_force_unit);
   pData->VciCalc = WBFL::Units::ConvertToSysUnits(VciCalc, *p_force_unit);
   pData->Vci     = WBFL::Units::ConvertToSysUnits(Vci,     *p_force_unit);
   pData->Vcw     = WBFL::Units::ConvertToSysUnits(Vcw,     *p_force_unit);
}

Float64  lrfdShear::ComputeShearStress(Float64 Vu, Float64 Vp, Float64 phi, Float64 bv, Float64 dv)
{
   Float64 vu;

   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FourthEdition2007 )
   {
      vu = (Vu - phi*Vp)/(phi*bv*dv);
   }
   else
   {
      vu = fabs(Vu - phi*Vp)/(phi*bv*dv);
   }

   return vu;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdShear::AssertValid() const
{
   return true;
}

void lrfdShear::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for lrfdShear" << WBFL::Debug::endl;
}
#endif // _DEBUG


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdWsdotShear::~lrfdWsdotShear()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdWsdotShear::ComputeThetaAndBeta(lrfdShearData* pData,bool bEndRegion)
{
   if ( lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::SecondEditionWith1999Interims )
   {
      lrfdShear::ComputeThetaAndBeta(pData);
   }
   else
   {
      compute_theta_and_beta4( pData );
   }
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdWsdotShear::AssertValid() const
{
   return true;
}

void lrfdWsdotShear::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for lrfdWsdotShear" << WBFL::Debug::endl;
   lrfdShear::Dump(os);
}
#endif // _DEBUG


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


////////////////////////////////////////////////////////////////
void compute_theta_and_beta1(lrfdShearData* pData)
{
   // Copy input data (this will make life a little easier)
   Float64 Mu  = pData->Mu;
   Float64 Nu  = pData->Nu;
   Float64 Vu  = pData->Vu;
   Float64 phi = pData->phi;
   Float64 Vp  = pData->Vp;
   Float64 dv  = pData->dv;
   Float64 bv  = pData->bv;
   Float64 Es  = pData->Es;
   Float64 As  = pData->As;
   Float64 Eps = pData->Eps;
   Float64 Aps = pData->Aps;
   Float64 EptSegment = pData->EptSegment;
   Float64 AptSegment = pData->AptSegment;
   Float64 EptGirder = pData->EptGirder;
   Float64 AptGirder = pData->AptGirder;
   Float64 Ec  = pData->Ec;
   Float64 Ac  = pData->Ac;
   Float64 fpops = pData->fpops;
   Float64 fpoptSegment = pData->fpoptSegment;
   Float64 fpoptGirder = pData->fpoptGirder;
   Float64 fc  = pData->fc;

   pData->Eqn = 0; // Not applicable

   // Setup problem
   const Float64 v = (Vu - phi*Vp)/(phi*bv*dv);
   Float64 vfc = v/fc;

   pData->vu = v;
   pData->vufc = vfc;

   if ( get_vfc(get_vfc_count()-1) < vfc )
   {
      vfc = get_vfc(get_vfc_count()-1);  // used to THROW(lrfdXShear,vfcOutOfRange);
      WARN(true,"v/fc > 0.25 - Setting to 0.25 in lrfdShear");
   }

   if ( vfc < get_vfc(0) )
   {
      vfc = get_vfc(0);
   }

   Float64 theta;
   Float64 theta_guess = 20.000;
   const Float64 theta_tol = 0.1;
   Int16 cIter = 0;
   const Int16 max_iter = 100;
   bool done = false;
   Float64 ex = 0;

   Float64 deja_vu_angle; // This is the angle that was used to compute
                          // strain two iterations ago.  If it is the
                          // same as the currently computed theta, then
                          // we are most likely cycling and wont converge.
   deja_vu_angle = theta_guess/2.;

   // Iterate until theta is found
   //WATCH( _T("*** Begin Iteration to find Theta ***") );
   //WATCH( _T("   vfc      = ") << vfc );
   while ( !done && (cIter < max_iter) )
   {
      cIter++;
      ex = compute_strain(pData,theta_guess);
      theta = get_theta(vfc,ex);
      //WATCH( _T("theta_guess = ") << theta_guess );
      //WATCH( _T("   ex       = ") << ex );
      //WATCH( _T("theta       = ") << theta );

      if ( IsEqual( theta, theta_guess, theta_tol) )
      {
         done = true;
      }
      else
      {
         // On even iterations, check the deja vu angle 
         if ( cIter % 2 == 0 )
         {
            Float64 temp_theta = theta;
            if ( IsEqual(theta,deja_vu_angle) )
            {
               // We're cycling (deja vu - we've used this theta guess before)
               theta = (deja_vu_angle + theta_guess)/2.;
               //WATCH( _T("*** deja vu *** ") << deja_vu_angle );
            }

            deja_vu_angle = temp_theta;
         }

         // Next guess
         theta_guess = theta;
      }
   };

   if ( max_iter <= cIter )
   {
      THROW(lrfdXShear,MaxIterExceeded);
   }

   CHECK( IsEqual( theta, theta_guess, theta_tol ) );

   // Compute beta
   Float64 beta = get_beta( vfc,ex );

   pData->Theta = WBFL::Units::ConvertToSysUnits( theta, WBFL::Units::Measure::Degree );
   pData->Beta  = beta;
   pData->ex    = ex;
}

void compute_theta_and_beta2(lrfdShearData* pData)
{
   // Copy input data (this will make life a little easier)
   Float64 Mu  = pData->Mu;
   Float64 Nu  = pData->Nu;
   Float64 Vu  = pData->Vu;
   Float64 phi = pData->phi;
   Float64 Vp  = pData->Vp;
   Float64 dv  = pData->dv;
   Float64 bv  = pData->bv;
   Float64 Es  = pData->Es;
   Float64 As  = pData->As;
   Float64 Eps = pData->Eps;
   Float64 Aps = pData->Aps;
   Float64 EptSegment = pData->EptSegment;
   Float64 AptSegment = pData->AptSegment;
   Float64 EptGirder = pData->EptGirder;
   Float64 AptGirder = pData->AptGirder;
   Float64 Ec  = pData->Ec;
   Float64 Ac  = pData->Ac;
   Float64 fpops = pData->fpops;
   Float64 fpoptSegment = pData->fpoptSegment;
   Float64 fpoptGirder = pData->fpoptGirder;
   Float64 fc  = pData->fc;

   pData->Eqn = 0; // Not applicable

   // Setup problem
   const Float64 v = (Vu - phi*Vp)/(phi*bv*dv);
   Float64 vfc = v/fc;

   pData->vu = v;
   pData->vufc = vfc;

   if ( get_vfc(get_vfc_count()-1) < vfc )
   {
      vfc = get_vfc(get_vfc_count()-1);  // used to THROW(lrfdXShear,vfcOutOfRange);
      WARN(true,"v/fc > 0.25 - Setting to 0.25 in lrfdShear");
   }

   if ( vfc < get_vfc(0) )
   {
      vfc = get_vfc(0);
   }

   // Find out which rows we are spanning
   Int16 row1, row2;
   get_row_index( vfc, &row1, &row2 );

   Float64 ex_calc[2];
   Float64 ex_table[2];
   Float64 theta_guess[2];

   bool bFoundSolution = false;
   Float64 theta;
   Float64 ex;

   //WATCH( _T("*** Begin Iteration to find Theta ***") );
   //WATCH( _T("vfc      = ") << vfc );
   //WATCH( _T("Spanning rows ") << row1 << _T(" and ") << row2 );

   
   Int16 col;
   for ( col = 0; col < get_ex_count()-1; col++ )
   {
      WATCH( _T("Checking for intersection between col ") << col << _T(" and ") << (col+1) );

      // Interpolation variables
      Float64 a;
      Float64 l;
      Float64 h;
      Float64 delta;

      // Interpolate between rows
      a = vfc - get_vfc(row1);
      l = get_beta_theta(row1,col).Theta;
      h = get_beta_theta(row2,col).Theta;
      delta = get_vfc(row2) - get_vfc(row1);
      theta_guess[0] = LinInterp(a, l, h, delta );
      ex_table[0] = get_ex(col);
      ex_calc[0] = compute_strain(pData,theta_guess[0]);

      a = vfc - get_vfc(row1);
      l = get_beta_theta(row1,col+1).Theta;
      h = get_beta_theta(row2,col+1).Theta;
      delta = get_vfc(row2) - get_vfc(row1);
      theta_guess[1] = LinInterp(a, l, h, delta );
      ex_table[1] = get_ex(col+1);
      ex_calc[1] = compute_strain(pData,theta_guess[1]);

      WBFL::Geometry::LineSegment2d l1(WBFL::Geometry::Point2d(theta_guess[0],ex_calc[0]),  WBFL::Geometry::Point2d(theta_guess[1],ex_calc[1]));
      WBFL::Geometry::LineSegment2d l2(WBFL::Geometry::Point2d(theta_guess[0],ex_table[0]), WBFL::Geometry::Point2d(theta_guess[1],ex_table[1]));

      //WATCH( _T("L1 = ") << l1.GetStartPoint() << _T(" ") << l1.GetEndPoint() );
      //WATCH( _T("L2 = ") << l2.GetStartPoint() << _T(" ") << l2.GetEndPoint() );

      WBFL::Geometry::Point2d p;
      if (WBFL::Geometry::GeometricOperations::Intersect( l1, l2, &p ) == 1 )
      {
         bFoundSolution = true;
         theta = p.X();
         ex    = p.Y();

         //WATCH(_T("Intersection found ") << p );

         break;
      }
   }


   if ( !bFoundSolution )
   {
      THROW(lrfdXShear,MaxIterExceeded);
   }

   if (pData->bLimitNetTensionStrainToPositiveValues && ex < 0)
   {
      ex = 0;
   }
   

   // Compute beta
   Float64 beta = get_beta( vfc, ex );

   pData->Theta = WBFL::Units::ConvertToSysUnits( theta, WBFL::Units::Measure::Degree );
   pData->Beta  = beta;
   pData->ex    = ex;

   // Back out Fe... If ex > 0, use a code value of -1
   if ( ex < 0 )
   {
      pData->Fe = (pData->Es*pData->As + pData->Eps*pData->Aps + pData->EptSegment*pData->AptSegment + pData->EptGirder*pData->AptGirder)/(pData->Ec*pData->Ac + pData->Es*pData->As + pData->Eps*pData->Aps + pData->EptSegment*pData->AptSegment + pData->EptGirder*pData->AptGirder);
   }
   else
   {
      pData->Fe = -1;
   }
}


// Method from LRFD 2nd Edition, 2000 interims and later.
// All we have to do is find the "box" from table 5.8.3.4.2-1 
// There is no need to interpolate between rows and columns as in version 2 of this method
void compute_theta_and_beta3(lrfdShearData* pData, bool bWSDOT)
{
   Float64 bv  = pData->bv;
   Float64 fc  = pData->fc;
   Float64 fy  = pData->fy;
   Float64 Avs = pData->AvS;

   // we are using a table
   pData->BetaEqn = 0;

   // Determine whether we meet minimum steel requirements - then we can choose equations and tables
   Float64 minSteel;
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      minSteel = 0.083*sqrt(WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::MPa))*WBFL::Units::ConvertFromSysUnits(bv,WBFL::Units::Measure::Millimeter)/WBFL::Units::ConvertFromSysUnits(fy,WBFL::Units::Measure::MPa);
      minSteel = WBFL::Units::ConvertToSysUnits(minSteel,WBFL::Units::Measure::Millimeter); // (mm^2/mm)
   }
   else
   {
      minSteel = 0.0316*sqrt(WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI))*WBFL::Units::ConvertFromSysUnits(bv,WBFL::Units::Measure::Inch)/WBFL::Units::ConvertFromSysUnits(fy,WBFL::Units::Measure::KSI);
      minSteel = WBFL::Units::ConvertToSysUnits(minSteel,WBFL::Units::Measure::Inch); // (in^2/in)
   }

   if ( Avs < minSteel && !pData->bIgnoreMiniumStirrupRequirementForBeta)
   {
      compute_theta_and_beta3_tbl2(pData, bWSDOT); // Use LRFD Eqn 5.8.3.4.2-2 and table 2
   }
   else
   {
      compute_theta_and_beta3_tbl1(pData, bWSDOT); // Use LRFD Eqn 5.8.3.4.2-1 and table 1
   }
}

void compute_theta_and_beta3_tbl1(lrfdShearData* pData, bool bWSDOT)
{
   // Compute beta and theta for case where steel meets min steel requirments
   Float64 Mu  = pData->Mu;
   Float64 Nu  = pData->Nu;
   Float64 Vu  = pData->Vu;
   Float64 phi = pData->phi;
   Float64 Vp  = pData->Vp;
   Float64 dv  = pData->dv;
   Float64 bv  = pData->bv;
   Float64 Es  = pData->Es;
   Float64 As  = pData->As;
   Float64 Eps = pData->Eps;
   Float64 Aps = pData->Aps;
   Float64 EptSegment = pData->EptSegment;
   Float64 AptSegment = pData->AptSegment;
   Float64 EptGirder = pData->EptGirder;
   Float64 AptGirder = pData->AptGirder;
   Float64 Ec  = pData->Ec;
   Float64 Ac  = pData->Ac;
   Float64 fpops = pData->fpops;
   Float64 fpoptSegment = pData->fpoptSegment;
   Float64 fpoptGirder = pData->fpoptGirder;
   Float64 fc  = pData->fc;
   Float64 fy  = pData->fy;
   Float64 Avs = pData->AvS;

   Int16 eqn = 1; // Use LRFD Eqn 5.8.3.4.2-1 - we always meet min steel in this function

   // Setup problem
   const Float64 v = (Vu - phi*Vp)/(phi*bv*dv);
   Float64 vfc = v/fc;

   pData->vu = v;
   pData->vufc = vfc;

   // Bound vc
   if ( get_vfc(get_vfc_count()-1) < vfc )
   {
      vfc = get_vfc(get_vfc_count()-1);  // used to THROW(lrfdXShear,vfcOutOfRange);
      WARN(true,"v/fc > 0.25 - Setting to 0.25 in lrfdShear");
   }

   if ( vfc < get_vfc(0) )
   {
      vfc = get_vfc(0);
   }

   // Find out which rows we are spanning
   Int16 row1, row2;
   get_row_index( vfc, &row1, &row2 ); // row 2 is the one we want to use
   Int16 row = row2;

   // start at the right most column in table 5.8.3.4.2-1 and work backwards until
   // we come to a column where ex_calc < ex_table. The column we are looking for is
   // the one to the right of the current column.
   bool bFoundSolution = false;
   Int16 col = get_ex_count()-1; 
   Float64 ex_calc;
   Float64 ex_last;
   Int16 eq_last;
   while ( 0 <= col && !bFoundSolution )
   {
      BT bt = get_beta_theta(row,col);

// This is being removed from the BDM... RAB 7/25/2006
//      // Minimum theta is 25degrees per BDM 5.2.4F.2
//      if ( bWSDOT && bt.Theta < 25 )
//         bt.Theta = 25;

      Float64 angle = WBFL::Units::Convert(bt.Theta,WBFL::Units::Measure::Degree,WBFL::Units::Measure::Radian);
      Float64 cot = 1.0/tan(angle);

      if ( eqn == 1 )
      {
         // Eqn 5.8.3.4.2-1
         if ( IsZero(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder) )
         {
            ex_calc = 0.0;
         }
         else
         {
            if ( lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion() )
            {
               ex_calc = (fabs(Mu)/dv + 0.5*Nu + 0.5*fabs(Vu-Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/(2*(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
            else
            {
               ex_calc = (Mu/dv + 0.5*Nu + 0.5*(Vu-Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/(2*(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
         }

         if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SecondEditionWith2003Interims )
         {
            ex_calc = (ex_calc > 0.002) ? 0.002 : ex_calc;
         }
         else
         {
            ex_calc = (ex_calc > 0.001) ? 0.001 : ex_calc;
         }

         pData->Eqn = 1;
      }
      else
      {
         // Eqn 5.8.3.4.2-2
         if ( IsZero(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder) )
         {
            ex_calc = 0.0;
         }
         else
         {
            if ( lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion() )
            {
               ex_calc = (fabs(Mu)/dv + 0.5*Nu + 0.5*fabs(Vu-Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/((Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
            else
            {
               ex_calc = (Mu/dv + 0.5*Nu + 0.5*(Vu-Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/((Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
         }

         ex_calc = (ex_calc > 0.002) ? 0.002 : ex_calc;
         pData->Eqn = 2;
      }

      if ( ex_calc < 0 )
      {
         if (pData->bLimitNetTensionStrainToPositiveValues)
         {
            ex_calc = 0;
         }
         else
         {
            // Eqn 5.8.3.4.2-3
            pData->Eqn = (pData->Eqn == 1 ? 31 : 32);

            if (lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion())
            {
               ex_calc = (fabs(Mu) / dv + 0.5*Nu + 0.5*fabs(Vu - Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder) / (2 * (Ec*Ac + Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
            else
            {
               ex_calc = (Mu / dv + 0.5*Nu + 0.5*(Vu - Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder) / (2 * (Ec*Ac + Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
         }
      }

      if ( col == get_ex_count()-1 )
      {
         // first time through loop, initiliaze with current values
         ex_last = ex_calc;
         eq_last = pData->Eqn;
      }

      Float64 ex_table = get_ex(col);

      if ( ex_table < ex_calc )
      {
         col++;
         bFoundSolution = true;
         pData->ex = ex_last;
         pData->Eqn = eq_last;
      }
      else
      {
         col--;
         ex_last = ex_calc;
         eq_last = pData->Eqn;
      }
   }

   // The computed strain is less than the strain limit in the left most column. The solution is column 0
   if ( col < 0 )
   {
      col = 0; 
   }

   assert(0 <= col && col < get_ex_count());

   BT bt = get_beta_theta(row,col);

// This is being removed from the BDM... RAB 7/25/2006
//   // Minimum theta is 25degrees per BDM 5.2.4F.2
//   if ( bWSDOT && bt.Theta < 25 )
//      bt.Theta = 25;

   pData->BetaTheta_tbl = 1; 
   pData->vufc_tbl = get_vfc(row);
   pData->ex_tbl = get_ex(col);
   pData->Beta = bt.Beta;
   pData->Theta = WBFL::Units::ConvertToSysUnits(bt.Theta,WBFL::Units::Measure::Degree);
   pData->Fe = -1; // Not appicable
}

void compute_theta_and_beta3_tbl2(lrfdShearData* pData, bool bWSDOT)
{
   // Compute beta and theta for case min steel requirments are not met
   Float64 Mu  = pData->Mu;
   Float64 Nu  = pData->Nu;
   Float64 Vu  = pData->Vu;
   Float64 phi = pData->phi;
   Float64 Vp  = pData->Vp;
   Float64 dv  = pData->dv;
   Float64 bv  = pData->bv;
   Float64 Es  = pData->Es;
   Float64 As  = pData->As;
   Float64 Eps = pData->Eps;
   Float64 Aps = pData->Aps;
   Float64 EptSegment = pData->EptSegment;
   Float64 AptSegment = pData->AptSegment;
   Float64 EptGirder = pData->EptGirder;
   Float64 AptGirder = pData->AptGirder;
   Float64 Ec  = pData->Ec;
   Float64 Ac  = pData->Ac;
   Float64 fpops = pData->fpops;
   Float64 fpoptSegment = pData->fpoptSegment;
   Float64 fpoptGirder = pData->fpoptGirder;
   Float64 fc  = pData->fc;
   Float64 fy  = pData->fy;
   Float64 Avs = pData->AvS;
   Float64 sx  = pData->sx;
   Float64 ag  = pData->ag;

   Int16 eqn = 2;

   // Setup problem
   // 5.8.3.4.2-5
   Float64 sxe = WBFL::Units::ConvertFromSysUnits(sx,WBFL::Units::Measure::Inch) * 1.38/(WBFL::Units::ConvertFromSysUnits(ag,WBFL::Units::Measure::Inch)+0.63);

   // Bound sxe
   sxe = ForceIntoRange(5.0, sxe, 80.0); // Note: any spec changes to table range would affect this

   pData->sxe   =  WBFL::Units::ConvertToSysUnits(sxe,WBFL::Units::Measure::Inch);

   // Find out which rows we are spanning
   Int16 row1, row2;
   get_row_index_mtr( sxe, &row1, &row2 ); // row 2 is the one we want to use
   Int16 row = row2;

   // start at the right most column in table 5.8.3.4.2-2 and work backwards until
   // we come to a column where ex_calc < ex_table. The column we are looking for is
   // the one to the right of the current column.
   bool bFoundSolution = false;
   Int16 col = get_ex_count_mtr()-1;
   Float64 ex_calc;
   Float64 ex_last;
   Int16 eq_last;
   while ( 0 <= col && !bFoundSolution )
   {
      BT bt = get_beta_theta_mtr(row,col);

// This is being removed from the BDM... RAB 7/25/2006
//      // Minimum theta is 25degrees per BDM 5.2.4F.2
//      if ( bWSDOT && bt.Theta < 25 )
//         bt.Theta = 25;

      Float64 angle = WBFL::Units::Convert(bt.Theta,WBFL::Units::Measure::Degree,WBFL::Units::Measure::Radian);
      Float64 cot = 1.0/tan(angle);

      if ( eqn == 1 )
      {
         // Eqn 5.8.3.4.2-1
         if ( IsZero(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder) )
         {
            ex_calc = 0.0;
         }
         else
         {
            if ( lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion() )
            {
               ex_calc = (fabs(Mu)/dv + 0.5*Nu + 0.5*fabs(Vu-Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/(2*(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
            else
            {
               ex_calc = (Mu/dv + 0.5*Nu + 0.5*(Vu-Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/(2*(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
         }

         if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SecondEditionWith2003Interims )
         {
            ex_calc = (ex_calc > 0.002) ? 0.002 : ex_calc;
         }
         else
         {
            ex_calc = (ex_calc > 0.001) ? 0.001 : ex_calc;
         }

         pData->Eqn = 1;
      }
      else
      {
         // Eqn 5.8.3.4.2-2
         if ( IsZero(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder) )
         {
            ex_calc = 0.0;
         }
         else
         {
            if ( lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion() )
            {
               ex_calc = (fabs(Mu)/dv + 0.5*Nu + 0.5*fabs(Vu-Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/((Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
            else
            {
               ex_calc = (Mu/dv + 0.5*Nu + 0.5*(Vu-Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/((Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
         }

         ex_calc = (ex_calc > 0.002) ? 0.002 : ex_calc;
         pData->Eqn = 2;
      }

      if ( ex_calc < 0 )
      {
         if (pData->bLimitNetTensionStrainToPositiveValues)
         {
            ex_calc = 0;
         }
         else
         {
            // Eqn 5.8.3.4.2-3
            pData->Eqn = (pData->Eqn == 1 ? 31 : 32);

            if (lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion())
            {
               ex_calc = (fabs(Mu) / dv + 0.5*Nu + 0.5*fabs(Vu - Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder) / (2 * (Ec*Ac + Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
            else
            {
               ex_calc = (Mu / dv + 0.5*Nu + 0.5*(Vu - Vp)*cot - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder) / (2 * (Ec*Ac + Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
            }
         }
      }

      Float64 ex_table = get_ex_mtr(col);

      if ( col == get_ex_count_mtr()-1 )
      {
         // first time through the loop, initialize with current values
         ex_last = ex_calc;
         eq_last = pData->Eqn;
      }

      if ( ex_table < ex_calc )
      {
         col++;
         bFoundSolution = true;
         pData->ex = ex_last;
         pData->Eqn = eq_last;
      }
      else
      {
         col--;
         ex_last = ex_calc;
         eq_last = pData->Eqn;
      }
   }

   // The computed strain is less than the strain limit in the left most column. The solution is column 0
   if ( col < 0 )
   {
      col = 0; 
   }

   assert(0 <= col && col < get_ex_count_mtr());

   BT bt = get_beta_theta_mtr(row,col);

// This is being removed from the BDM... RAB 7/25/2006
//   // Minimum theta is 25degrees per BDM 5.2.4F.2
//   if ( bWSDOT && bt.Theta < 25 )
//      bt.Theta = 25;

   pData->BetaTheta_tbl = 2; 
   pData->sxe_tbl = WBFL::Units::ConvertToSysUnits(get_sxe_mtr(row), WBFL::Units::Measure::Inch);
   pData->ex_tbl = get_ex_mtr(col);
   pData->Beta = bt.Beta;
   pData->Theta = WBFL::Units::ConvertToSysUnits(bt.Theta,WBFL::Units::Measure::Degree);
   pData->Fe = -1; // Not appicable
}


void compute_theta_and_beta4(lrfdShearData* pData)
{
   // LRFD Shear 2001 Interims, modified by WSDOT Design Memo 7-2001... Dated June 18, 2001

   // Copy input data (this will make life a little easier)
   Float64 Mu  = pData->Mu;
   Float64 Nu  = pData->Nu;
   Float64 Vu  = pData->Vu;
   Float64 phi = pData->phi;
   Float64 Vp  = pData->Vp;
   Float64 dv  = pData->dv;
   Float64 bv  = pData->bv;
   Float64 Es  = pData->Es;
   Float64 As  = pData->As;
   Float64 Eps = pData->Eps;
   Float64 Aps = pData->Aps;
   Float64 EptSegment = pData->EptSegment;
   Float64 AptSegment = pData->AptSegment;
   Float64 EptGirder = pData->EptGirder;
   Float64 AptGirder = pData->AptGirder;
   Float64 Ec  = pData->Ec;
   Float64 Ac  = pData->Ac;
   Float64 fpops = pData->fpops;
   Float64 fpoptSegment = pData->fpoptSegment;
   Float64 fpoptGirder = pData->fpoptGirder;
   Float64 fc  = pData->fc;
   Float64 fy  = pData->fy;
   Float64 Avs = pData->AvS;
   Float64 sx  = pData->sx;
   Float64 ag  = pData->ag;

   Float64 minSteel;
   Int16 eqn;

   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      minSteel = 0.083*sqrt(WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::MPa))*WBFL::Units::ConvertFromSysUnits(bv,WBFL::Units::Measure::Millimeter)/WBFL::Units::ConvertFromSysUnits(fy,WBFL::Units::Measure::MPa);
      minSteel = WBFL::Units::ConvertToSysUnits(minSteel,WBFL::Units::Measure::Millimeter); // (mm^2/mm)
   }
   else
   {
      minSteel = 0.0316*sqrt(WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI))*WBFL::Units::ConvertFromSysUnits(bv,WBFL::Units::Measure::Inch)/WBFL::Units::ConvertFromSysUnits(fy,WBFL::Units::Measure::KSI);
      minSteel = WBFL::Units::ConvertToSysUnits(minSteel,WBFL::Units::Measure::Inch); // (in^2/in)
   }

   if ( Avs < minSteel )
   {
      eqn = 2; // Use LRFD Eqn 5.8.3.4.2-2
   }
   else
   {
      eqn = 1; // Use LRFD Eqn 5.8.3.4.2-1
   }


   // Setup problem
   const Float64 v = (Vu - phi*Vp)/(phi*bv*dv);
   Float64 vfc = v/fc;

   pData->vu = v;
   pData->vufc = vfc;

   // Bound vc
   if ( get_vfc(get_vfc_count()-1) < vfc )
   {
      vfc = get_vfc(get_vfc_count()-1);  // used to THROW(lrfdXShear,vfcOutOfRange);
      WARN(true,"v/fc > 0.25 - Setting to 0.25 in lrfdShear");
   }

   if ( vfc < get_vfc(0) )
   {
      vfc = get_vfc(0);
   }

   // Find out which rows we are spanning
   Int16 row1, row2;
   get_row_index( vfc, &row1, &row2 ); // row 2 is the one we want to use
   Int16 row = row2;

   // Compute strain based on WSDOT modified equations
   Float64 ex_calc;
   if ( eqn == 1 )
   {
      if ( IsZero(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder) )
      {
         ex_calc = 0.0;
      }
      else
      {
         ex_calc = (Mu/dv + 0.5*Nu + fabs(Vu-Vp) - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/(2*(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
      }

      if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SecondEditionWith2003Interims )
      {
         ex_calc = (ex_calc > 0.002) ? 0.002 : ex_calc;
      }
      else
      {
         ex_calc = (ex_calc > 0.001) ? 0.001 : ex_calc;
      }

      pData->Eqn = 1;
   }
   else
   {
      // Eqn 5.8.3.4.2-2
      if ( IsZero(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder) )
      {
         ex_calc = 0.0;
      }
      else
      {
         ex_calc = (Mu/dv + 0.5*Nu + fabs(Vu-Vp) - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/((Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
      }

      ex_calc = (ex_calc > 0.002) ? 0.002 : ex_calc;
      pData->Eqn = 2;
   }

   if ( ex_calc < 0 )
   {
      if (pData->bLimitNetTensionStrainToPositiveValues)
      {
         ex_calc = 0;
      }
      else
      {
         // Eqn 5.8.3.4.2-3
         pData->Eqn = (pData->Eqn == 1 ? 31 : 32);

         ATLASSERT(!IsZero(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder)); // should be able to get here if zero
         ex_calc = (Mu / dv + 0.5*Nu + fabs(Vu - Vp) - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder) / (2 * (Ec*Ac + Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder));
      }
   }

   if ( pData->Eqn == 1 || pData->Eqn == 31 )
   {
      // Find the column in the beta/theta table (table 5.8.3.4.2-1) with a strain that is
      // more than this
      Int16 col;
      for ( col = 0; col < get_ex_count(); col++ )
      {
         Float64 ex_tbl = get_ex(col);
         if ( ex_calc <= ex_tbl )
         {
            // this is the first strain greater than the computed strain
            pData->ex_tbl = ex_tbl;
            break;
         }
      }

      assert(0 <= col && col < get_ex_count());

      // Get Beta/Theta;
      const BT& bt = get_beta_theta(row,col);
      pData->ex = ex_calc;
      pData->vufc_tbl = get_vfc(row);
      pData->Beta = bt.Beta;
      pData->Theta = WBFL::Units::ConvertToSysUnits(bt.Theta,WBFL::Units::Measure::Degree);
      pData->Fe = -1; // Not appicable
   }
   else
   {
      Float64 sxe = WBFL::Units::ConvertFromSysUnits(sx,WBFL::Units::Measure::Inch) * 1.38/(WBFL::Units::ConvertFromSysUnits(ag,WBFL::Units::Measure::Inch)+0.63);

      // Bound sxe
      sxe = ForceIntoRange(5.0, sxe, 80.0); // Note: any spec changes to table range would affect this

      pData->sxe   =  WBFL::Units::ConvertToSysUnits(sxe,WBFL::Units::Measure::Inch);

      // Find out which rows we are spanning
      Int16 row1, row2;
      get_row_index_mtr( sxe, &row1, &row2 ); // row 2 is the one we want to use
      Int16 row = row2;

      // start at the right most column in table 5.8.3.4.2-2 and work backwards until
      // we come to a column where ex_calc < ex_table. The column we are looking for is
      // the one to the right of the current column.
      bool bFoundSolution = false;
      Int16 col = get_ex_count_mtr()-1;
      Float64 ex_last;
      Int16 eq_last;
      while ( 0 <= col && !bFoundSolution )
      {
         BT bt = get_beta_theta_mtr(row,col);

         Float64 ex_table = get_ex_mtr(col);

         if ( col == get_ex_count_mtr()-1 )
         {
            // first time through the loop, initialize with current values
            ex_last = ex_calc;
            eq_last = pData->Eqn;
         }

         if ( ex_table < ex_calc )
         {
            col++;
            bFoundSolution = true;
            pData->ex = ex_last;
            pData->Eqn = eq_last;
         }
         else
         {
            col--;
            ex_last = ex_calc;
            eq_last = pData->Eqn;
         }
      }

      // The computed strain is less than the strain limit in the left most column. The solution is column 0
      if ( col < 0 )
      {
         col = 0; 
      }

      assert(0 <= col && col < get_ex_count_mtr());

      BT bt = get_beta_theta_mtr(row,col);

      pData->BetaTheta_tbl = 2; 
      pData->sxe_tbl = WBFL::Units::ConvertToSysUnits(get_sxe_mtr(row), WBFL::Units::Measure::Inch);
      pData->ex_tbl = get_ex_mtr(col);
      pData->Beta = bt.Beta;
      pData->Theta = WBFL::Units::ConvertToSysUnits(bt.Theta,WBFL::Units::Measure::Degree);
      pData->Fe = -1; // Not appicable
   }
}

void compute_theta_and_beta5(lrfdShearData* pData)
{
   // LRFD 2008 - Beta and Theta by equations

   // Copy input data (this will make life a little easier)
   Float64 Mu  = pData->Mu;
   Float64 Nu  = pData->Nu;
   Float64 Vu  = pData->Vu;
   Float64 phi = pData->phi;
   Float64 Vp  = pData->Vp;
   Float64 dv  = pData->dv;
   Float64 bv  = pData->bv;
   Float64 Es  = pData->Es;
   Float64 As  = pData->As;
   Float64 Eps = pData->Eps;
   Float64 Aps = pData->Aps;
   Float64 EptSegment = pData->EptSegment;
   Float64 AptSegment = pData->AptSegment;
   Float64 EptGirder = pData->EptGirder;
   Float64 AptGirder = pData->AptGirder;
   Float64 Ec  = pData->Ec;
   Float64 Ac  = pData->Ac;
   Float64 fpops = pData->fpops;
   Float64 fpoptSegment = pData->fpoptSegment;
   Float64 fpoptGirder = pData->fpoptGirder;
   Float64 fc  = pData->fc;
   Float64 fy  = pData->fy;
   Float64 Avs = pData->AvS;
   Float64 ag  = pData->ag;
   Float64 sx  = pData->sx;

   // Setup problem
   Float64 ex_max = 6e-3;
   Float64 ex_min = -0.4e-3;

   // Compute strain 
   Float64 ex_calc;
   if ( IsZero(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder) )
   {
      ex_calc = ex_max; // no tension tie so use maximum strain
   }
   else
   {
      ex_calc = (fabs(Mu)/dv + 0.5*Nu + fabs(Vu-Vp) - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder)/(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder);
   }

   if ( ex_calc < 0 )
   {
      if (pData->bLimitNetTensionStrainToPositiveValues)
      {
         ex_calc = 0;
      }
      else
      {
         ex_calc = (fabs(Mu) / dv + 0.5*Nu + fabs(Vu - Vp) - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder) / (Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder + Ec*Ac);
      }
   }

   ex_calc = ForceIntoRange(ex_min,ex_calc,ex_max);


   // Get Beta/Theta;
   Float64 minSteel;
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      minSteel = 0.083*sqrt(WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::MPa))*WBFL::Units::ConvertFromSysUnits(bv,WBFL::Units::Measure::Millimeter)/WBFL::Units::ConvertFromSysUnits(fy,WBFL::Units::Measure::MPa);
      minSteel = WBFL::Units::ConvertToSysUnits(minSteel,WBFL::Units::Measure::Millimeter); // (mm^2/mm)
   }
   else
   {
      minSteel = 0.0316*sqrt(WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI))*WBFL::Units::ConvertFromSysUnits(bv,WBFL::Units::Measure::Inch)/WBFL::Units::ConvertFromSysUnits(fy,WBFL::Units::Measure::KSI);
      minSteel = WBFL::Units::ConvertToSysUnits(minSteel,WBFL::Units::Measure::Inch); // (in^2/in)
   }

   if ( Avs < minSteel && !pData->bIgnoreMiniumStirrupRequirementForBeta)
   {
      pData->BetaEqn = 2; // Use LRFD Eqn 5.8.3.4.2-2

      // 5.8.3.4.2-5
      Float64 sxe = WBFL::Units::ConvertFromSysUnits(sx,WBFL::Units::Measure::Inch) * 1.38/(WBFL::Units::ConvertFromSysUnits(ag,WBFL::Units::Measure::Inch)+0.63);
      sxe = ForceIntoRange(12.0, sxe, 80.0);

      pData->sxe   =  WBFL::Units::ConvertToSysUnits(sxe,WBFL::Units::Measure::Inch);
      pData->Beta  = (4.8/(1 + 750*ex_calc)) * (51/(39 + sxe));
   }
   else
   {
      pData->BetaEqn = 1; // Use LRFD Eqn 5.8.3.4.2-1

      pData->Beta    = 4.8/(1 + 750*ex_calc);
   }

   pData->ex = ex_calc;
   Float64 v = fabs(Vu - phi*Vp)/(phi*bv*dv);
   pData->vu = v;
   pData->vufc = v/fc;
   pData->vufc_tbl = -1; // Not applicable
   pData->Theta = WBFL::Units::ConvertToSysUnits(29+3500*ex_calc,WBFL::Units::Measure::Degree);
   pData->Fe = -1; // Not appicable
}

Float64 compute_strain(lrfdShearData* pData,Float64 theta)
{
   // Copy input data (this will make life a little easier)
   Float64 Mu  = pData->Mu;
   Float64 Nu  = pData->Nu;
   Float64 Vu  = pData->Vu;
   Float64 phi = pData->phi;
   Float64 Vp  = pData->Vp;
   Float64 dv  = pData->dv;
   Float64 bv  = pData->bv;
   Float64 Es  = pData->Es;
   Float64 As  = pData->As;
   Float64 Eps = pData->Eps;
   Float64 Aps = pData->Aps;
   Float64 EptSegment = pData->EptSegment;
   Float64 AptSegment = pData->AptSegment;
   Float64 EptGirder = pData->EptGirder;
   Float64 AptGirder = pData->AptGirder;
   Float64 Ec  = pData->Ec;
   Float64 Ac  = pData->Ac;
   Float64 fpops = pData->fpops;
   Float64 fpoptSegment = pData->fpoptSegment;
   Float64 fpoptGirder = pData->fpoptGirder;
   Float64 fc  = pData->fc;

   Float64 ex;

   theta = WBFL::Units::Convert(theta, WBFL::Units::Measure::Degree, WBFL::Units::Measure::Radian);
   if ( IsZero(Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder) )
   {
      ex = 0;
   }
   else
   {
      ex = Mu/dv + 0.5*Nu + 0.5*Vu/tan(theta) - Aps*fpops - AptSegment*fpoptSegment - AptGirder*fpoptGirder;
      ex /= Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder;
   }

   if ( ex < 0.0 )
   {
      if (pData->bLimitNetTensionStrainToPositiveValues)
      {
         ex = 0;
      }
      else
      {
         Float64 Fe;
         if (IsZero(Ec*Ac + Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder))
         {
            Fe = 0;
         }
         else
         {
            Fe = Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder;
            Fe /= Ec*Ac + Es*As + Eps*Aps + EptSegment*AptSegment + EptGirder*AptGirder;
         }

         ex *= Fe; // See "Design of Highway Bridges", Barker and Puckett, pg 641
      }
   }

   // :KLUDGE:  It is unclear what to do when the computed strain
   //           falls off the left end of table 5.8.3.4.2-1.
   //           According to Collins and Mitchel, pg 362, they
   //           state "Hence, if ex is negative, the value will be overestimated.
   //           In this case it will be conservative to take ex as equal to zero."
   //           For this reason, ex is forced to fit within the bounds
   //           of the table;
   ex = ForceIntoRange(get_ex(0), ex, get_ex(get_ex_count()-1));

   return ex;
}

Float64 get_theta(Float64 vfc,Float64 ex)
{
   Int16 row1, row2;
   Int16 col1, col2;
   
   get_row_and_col_index(vfc,ex,&row1,&row2,&col1,&col2);
   ASSERT( 0 <= row1 && 0 <= row2 && 0 <= col1 && 0 <= col2 );

   Float64 theta11;  // Theta on row 1, col 1
   Float64 theta12;  // Theta on row 1, col 2
   Float64 theta21;  // Theta on row 2, col 1
   Float64 theta22;  // Theta on row 2, col 2
   Float64 theta;

   theta11 = get_beta_theta(row1,col1).Theta;
   theta12 = get_beta_theta(row1,col2).Theta;
   theta21 = get_beta_theta(row2,col1).Theta;
   theta22 = get_beta_theta(row2,col2).Theta;

   Float64 theta1; // Theta on row 1
   Float64 theta2; // Theta on row 2

   // Interpolate on row 1
   Float64 a = ex - get_ex(col1);
   Float64 l = get_beta_theta(row1,col1).Theta;
   Float64 h = get_beta_theta(row1,col2).Theta;
   Float64 delta = get_ex(col2) - get_ex(col1);
   theta1 = LinInterp( a, l, h, delta );

   // Interpolate on row 2
   a = ex - get_ex(col1);
   l = get_beta_theta(row2,col1).Theta;
   h = get_beta_theta(row2,col2).Theta;
   delta = get_ex(col2) - get_ex(col1);
   theta2 = LinInterp( a, l, h, delta );

   // Interpolate between rows
   a = vfc - get_vfc(row1);
   l = theta1;
   h = theta2;
   delta = get_vfc(row2) - get_vfc(row1);
   theta = LinInterp(a, l, h, delta );

   return theta;
}

Float64 get_beta(Float64 vfc,Float64 ex)
{
   Int16 row1, row2;
   Int16 col1, col2;
   
   get_row_and_col_index(vfc,ex,&row1,&row2,&col1,&col2);
   ASSERT( 0 <= row1 && 0 <= row2 && 0 <= col1 && 0 <= col2 );

   Float64 beta11;  // beta on row 1, col 1
   Float64 beta12;  // beta on row 1, col 2
   Float64 beta21;  // beta on row 2, col 1
   Float64 beta22;  // beta on row 2, col 2
   Float64 beta;

   beta11 = get_beta_theta(row1,col1).Beta;
   beta12 = get_beta_theta(row1,col2).Beta;
   beta21 = get_beta_theta(row2,col1).Beta;
   beta22 = get_beta_theta(row2,col2).Beta;

   Float64 beta1; // beta on row 1
   Float64 beta2; // beta on row 2

   // Interpolate on row 1
   Float64 a = ex - get_ex(col1);
   Float64 l = get_beta_theta(row1,col1).Beta;
   Float64 h = get_beta_theta(row1,col2).Beta;
   Float64 delta = get_ex(col2) - get_ex(col1);
   beta1 = LinInterp( a, l, h, delta );

   // Interpolate on row 2
   a = ex - get_ex(col1);
   l = get_beta_theta(row2,col1).Beta;
   h = get_beta_theta(row2,col2).Beta;
   delta = get_ex(col2) - get_ex(col1);
   beta2 = LinInterp( a, l, h, delta );

   // Interpolate between rows
   a = vfc - get_vfc(row1);
   l = beta1;
   h = beta2;
   delta = get_vfc(row2) - get_vfc(row1);
   beta = LinInterp(a, l, h, delta );

   return beta;
}


Float64 get_ex(Float64 vfc,Float64 theta)
{
   Int16 row1, row2;
   Int16 col11, col12;
   Int16 col21, col22;

   get_row_index( vfc, &row1, &row2 );
   get_col_index( row1, theta, &col11, &col12 );
   get_col_index( row2, theta, &col21, &col22 );

   return theta;
}

void get_row_index(Float64 vfc,Int16* pr1,Int16* pr2)
{
   //
   // Sanity check the input
   //

   // vfc > 0.25 is not allowed. This condition should
   // have been trapped long before reacing this point
   CHECK( IsLE(vfc,get_vfc(get_vfc_count()-1)) );

   // Don't pass nullptr pointers
   CHECK( pr1 != 0 && pr2 != 0 );

   // Initialize indexes
   *pr1 = -1;
   *pr2 = -1;

   // Find the row index
   if ( vfc <= get_vfc(0) )
   {
         *pr1 = 0;
         *pr2 = 0;
   }
   else
   {
      for ( Int16 i = 0; i < get_vfc_count()-1; i++ )
      {
         if ( get_vfc(i) < vfc  && vfc <= get_vfc(i+1) )
         {
            *pr1 = i;
            *pr2 = i+1;
            break;
         }
      }
   }

   // We should always get valid row indices
   // If v/fc is < 0.05, using row 0 for *pr1
   // If v/fc is > 0.25, this method should have never been called.
   CHECK( *pr1 != -1 && *pr2 != -1 );
}

void get_col_index(Int16 row,Float64 theta,Int16* pc1,Int16* pc2)
{
   //
   // Sanity check the input
   //

   // ex is limited to 0.002.
   CHECK( 0 <= row && row < get_vfc_count() );

   // Don't pass nullptr pointers
   CHECK( pc1 != 0 &&
          pc2 != 0 );

   // Initialize indexes
   *pc1 = -1;
   *pc2 = -1;

   // Find the column index
   for ( Int16 col = 0; col < get_ex_count()-1; col++ )
   {
      if ( InRange( get_beta_theta(row,col).Theta, theta, get_beta_theta(row,col+1).Theta ) )
      {
         *pc1 = col;
         *pc2 = col+1;
         break;
      }
   }

   // Column indexes should not be the same
   CHECK( *pc1 != *pc2 && *pc1 < *pc2 );

   // At runtime we could get bad column indexes
   // There are no lrfd provisions describing what to do when ex < -0.002
   if ( *pc1 < 0 || *pc2 < 0 )
   {
      THROW(lrfdXShear,StrainOutOfRange);
   }
}

void get_col_index(Float64 ex,Int16* pc1,Int16* pc2)
{
   //
   // Sanity check the input
   //

   // ex is limited to 0.002.
   CHECK( IsLE(ex,get_ex(get_ex_count()-1)));

   // Don't pass nullptr pointers
   CHECK( pc1 != nullptr && pc2 != nullptr );

   // Initialize indexes
   *pc1 = -1;
   *pc2 = -1;

   // Find the column index
   for ( Int16 i = 0; i < get_ex_count()-1; i++ )
   {
      if ( InRange(get_ex(i),ex,get_ex(i+1) ) )
      {
         *pc1 = i;
         *pc2 = i+1;
         break;
      }
   }

   // Column indexes should not be the same
   CHECK( *pc1 != *pc2 && *pc1 < *pc2 );

   // At runtime we could get bad column indexes
   // There are no lrfd provisions describing what to do when ex < -0.002
   if ( *pc1 < 0 || *pc2 < 0 )
   {
      THROW(lrfdXShear,StrainOutOfRange);
   }
}

void get_row_and_col_index(Float64 vfc,Float64 ex,
                           Int16* pr1,Int16* pr2,
                           Int16* pc1,Int16* pc2)
{
   get_col_index(ex, pc1,pc2);
   get_row_index(vfc,pr1,pr2);
}


// More functions for minimum transverse reinforcement
void get_row_index_mtr(Float64 sxe,Int16* pr1,Int16* pr2)
{
   //
   // Sanity check the input
   //
   // Don't pass nullptr pointers
   CHECK( pr1 != nullptr && pr2 != nullptr );

   // Initialize indexes
   *pr1 = -1;
   *pr2 = -1;

   // Find the row index
   if ( sxe <= get_sxe_mtr(0) )
   {
         *pr1 = 0;
         *pr2 = 0;
   }
   else
   {
      for ( Int16 i = 0; i < get_sxe_count_mtr()-1; i++ )
      {
         if ( get_sxe_mtr(i) < sxe  && sxe <= get_sxe_mtr(i+1) )
         {
            *pr1 = i;
            *pr2 = i+1;
            break;
         }
      }
   }

   // We should always get valid row indices
   CHECK( *pr1 != -1 && *pr2 != -1 );
}


#if defined _UNITTEST
bool lrfdShear::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("lrfdShear");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for lrfdShear");
   TESTME_EPILOG("lrfdShear");
}
#endif // _UNITTEST


