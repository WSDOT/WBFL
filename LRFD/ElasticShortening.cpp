///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <Lrfd\PsStrand.h>
#include <Lrfd\ElasticShortening.h>
#include <Lrfd/BDSManager.h>

using namespace WBFL::LRFD;

ElasticShortening::ElasticShortening() :
   m_ePerm(0,0), m_eTemp(0,0)
{
   m_FpjPerm   = 0;
   m_FpjTemp   = 0;

   m_dFpR1Perm = 0;
   m_dFpR1Temp = 0;

   m_ApsPerm   = 0;
   m_ApsTemp   = 0;

   m_Eci   = WBFL::Units::ConvertToSysUnits(25000, WBFL::Units::Measure::MPa);
   m_Ep    = PsStrand::GetModE();

   m_bGrossProperties = false; // assume transformed
   m_Ag    = WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::Millimeter2);
   m_Ixx = WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::Millimeter4);
   m_Iyy = WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::Millimeter4);
   m_Ixy = WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::Millimeter4);

   m_Mdlg  = 0;
   m_K     = 1;

   m_P = 0;

   m_FcgpMethod = FcgpComputationMethod::Iterative;

   m_dfESPerm = 0;
   m_dfESTemp = 0;

   m_FcgpPerm = 0;
   m_FcgpTemp = 0;

   m_bUpdate = true;
}

ElasticShortening::ElasticShortening(Float64 fpjPerm,   // jacking stress
                                             Float64 fpjTemp,   // jacking stress
                                             Float64 dfpR1Perm, // initial relaxation
                                             Float64 dfpR1Temp, // initial relaxation
                                             Float64 ApsPerm,   // Area of permanent prestressing steel 
                                             Float64 ApsTemp,   // Area of temporary prestressing steel
                                             bool    bGrossProperties, // true if using gross section properties
                                             Float64 Ag,    // area of girder
                                             Float64 Ixx,    // moment of inertia of girder
                                             Float64 Iyy,
                                             Float64 Ixy,
                                             const WBFL::Geometry::Point2d& ePerm, // eccentricity of permanent ps strands
                                             const WBFL::Geometry::Point2d& eTemp, // eccentricity of temporary ps strands
                                             Float64 Mdlg,  // Dead load moment of girder only
                                             Float64 K,     // coefficient for post-tension members (N-1)/(2N)
                                             Float64 Eci,   // Modulus of elasticity of concrete at transfer
                                             Float64 Ep,    // Modulus of elasticity of prestressing steel
                                             FcgpComputationMethod method)
{
   m_FpjPerm   = fpjPerm;
   m_FpjTemp   = fpjTemp;

   m_dFpR1Perm = dfpR1Perm;
   m_dFpR1Temp = dfpR1Temp;

   m_ApsPerm   = ApsPerm;
   m_ApsTemp   = ApsTemp;

   m_ePerm     = ePerm;
   m_eTemp     = eTemp;

   m_Eci   = Eci;
   m_Ep    = Ep;

   m_bGrossProperties = bGrossProperties;
   m_Ag    = Ag;
   m_Ixx = Ixx;
   m_Iyy = Iyy;
   m_Ixy = Ixy;

   m_Mdlg  = Mdlg;
   m_K     = K;

   m_P = 0;

   m_FcgpMethod = method;

   m_dfESPerm = 0;
   m_dfESTemp = 0;

   m_FcgpPerm = 0;
   m_FcgpTemp = 0;

   m_bUpdate = true;
}

Float64 ElasticShortening::P() const
{
   if ( m_bUpdate )
   {
      Update();
   }

   return m_P;
}

Float64 ElasticShortening::TemporaryStrand_ElasticShorteningLosses() const
{
   if ( m_bUpdate )
   {
      Update();
   }

   return m_dfESTemp;
}

Float64 ElasticShortening::PermanentStrand_ElasticShorteningLosses() const
{
   if ( m_bUpdate )
   {
      Update();
   }

   return m_dfESPerm;
}

Float64 ElasticShortening::TemporaryStrand_Fcgp() const
{
   if ( m_bUpdate )
   {
      Update();
   }

   return m_FcgpTemp;
}

Float64 ElasticShortening::PermanentStrand_Fcgp() const
{
   if ( m_bUpdate )
   {
      Update();
   }

   return m_FcgpPerm;
}


void ElasticShortening::SetProperties(Float64 A, Float64 Ixx, Float64 Iyy, Float64 Ixy)
{
   m_Ag = A;
   m_Ixx = Ixx;
   m_Iyy = Iyy;
   m_Ixy = Ixy;
   m_bUpdate = true;
}

void ElasticShortening::GetProperties(Float64* pA, Float64* pIxx, Float64* pIyy, Float64* pIxy) const
{
   *pA = m_Ag;
   *pIxx = m_Ixx;
   *pIyy = m_Iyy;
   *pIxy = m_Ixy;
}

void ElasticShortening::Update() const
{
   Float64 dfESPerm = 0.00; // Guess
   Float64 dfESTemp = 0.00; // Guess
   m_dfESPerm = 0.00;
   m_dfESTemp = 0.00;

   Float64 epsx = (IsZero(m_ApsPerm + m_ApsTemp) ? 0 : (m_ApsPerm*m_ePerm.X() + m_ApsTemp*m_eTemp.X()) / (m_ApsPerm + m_ApsTemp));
   Float64 epsy = (IsZero(m_ApsPerm + m_ApsTemp) ? 0 : (m_ApsPerm*m_ePerm.Y() + m_ApsTemp*m_eTemp.Y()) / (m_ApsPerm + m_ApsTemp));

   Float64 n = m_Ep / m_Eci;
   Float64 kn = m_K*n;

   Float64 Ppj = m_ApsPerm*m_FpjPerm;
   Float64 Ptj = m_ApsTemp*m_FpjTemp;

   if ( IsZero(Ppj) && IsZero(Ptj) )
   {
      m_P = 0;
      
      m_FcgpTemp = 0;
      m_FcgpPerm = 0;

      m_dfESTemp = 0;
      m_dfESPerm = 0;
   }
   else if (m_FcgpMethod == FcgpComputationMethod::Iterative)
   {
      Float64 D = m_Ixx*m_Iyy - m_Ixy*m_Ixy;

      if ( m_bGrossProperties )
      {
         Int32 iter(0);
         do
         {
            dfESPerm = m_dfESPerm;
            dfESTemp = m_dfESTemp;

            m_P = m_ApsPerm*(m_FpjPerm - m_dFpR1Perm - dfESPerm) + m_ApsTemp*(m_FpjTemp - m_dFpR1Temp - dfESTemp);
            m_P *= -1;

            Float64 Mx = m_P*epsy + m_Mdlg;
            Float64 My = m_P*epsx;

            CHECK(!IsZero(m_Ag));
            CHECK(!IsZero(D));

            if ( IsZero(Ppj) )
            {
               m_FcgpPerm = 0;
            }
            else
            {
               m_FcgpPerm = m_P / m_Ag + (My*m_Ixx + Mx*m_Ixy)*(-m_ePerm.X()) / D - (Mx*m_Iyy + My*m_Ixy)*(-m_ePerm.Y()) / D;
               m_FcgpPerm *= -1.0; // Need a sign reversal to meet code equations
            }

            if ( IsZero(Ptj) )
            {
               m_FcgpTemp = 0;
            }
            else
            {
               m_FcgpTemp = m_P / m_Ag + (My*m_Ixx + Mx*m_Ixy)*(-m_eTemp.X()) / D - (Mx*m_Iyy + My*m_Ixy)*(-m_eTemp.Y()) / D;
               m_FcgpTemp *= -1.0; // Need a sign reversal to meet code equations
            }

            m_dfESTemp = kn * m_FcgpTemp;
            m_dfESPerm = kn * m_FcgpPerm;

            iter++;
            CHECK(iter<100);// if we are taking this long, there is a problem

         } while (!IsZero(dfESTemp-m_dfESTemp,0.01) || !IsZero(dfESPerm-m_dfESPerm,0.01));
      }
      else
      {
         // Compute using transformed properties
         m_P = m_ApsPerm*(m_FpjPerm - m_dFpR1Perm) + m_ApsTemp*(m_FpjTemp - m_dFpR1Temp);
         m_P *= -1;

         Float64 Mx = m_P*epsy + m_Mdlg;
         Float64 My = m_P*epsx;

         if ( IsZero(Ppj) )
         {
            m_FcgpPerm = 0;
         }
         else
         {
            m_FcgpPerm = m_P / m_Ag + (My*m_Ixx + Mx*m_Ixy)*(-m_ePerm.X()) / D - (Mx*m_Iyy + My*m_Ixy)*(-m_ePerm.Y()) / D;
            m_FcgpPerm *= -1.0; // Need a sign reversal to meet code equations
         }

         if ( IsZero(Ptj) )
         {
            m_FcgpTemp = 0;
         }
         else
         {
            m_FcgpTemp = m_P / m_Ag + (My*m_Ixx + Mx*m_Ixy)*(-m_eTemp.X()) / D - (Mx*m_Iyy + My*m_Ixy)*(-m_eTemp.Y()) / D;
            m_FcgpTemp *= -1.0; // Need a sign reversal to meet code equations
         }

         m_dfESTemp = kn * m_FcgpTemp;
         m_dfESPerm = kn * m_FcgpPerm;
      }
   }
   else if (m_FcgpMethod == FcgpComputationMethod::AssumedFpe)
   {
      // A bit of slight of hand here: This method assumes that the strand stress after release is 0.7Fpu, 
      // but we can have negative losses for a jacking stress of less. So, just assume that our client set
      // Fpj to 0.75*Fpu and it will all work out in the wash.
      m_P = Ppj*0.7/0.75 + Ptj*0.7/0.75;
      m_P *= -1;

      // NOTE: TxDOT method does not account for asymmetry of the girder section
      if ( IsZero(Ppj) )
      {
         m_FcgpPerm = 0;
      }
      else
      {
         m_FcgpPerm = m_P/m_Ag + m_P*epsy*m_ePerm.Y()/m_Ixx + m_Mdlg*m_ePerm.Y()/m_Ixx;
         m_FcgpPerm *= -1.0; // Need a sign reversal to meet code equations
      }

      if ( IsZero(Ptj) )
      {
         m_FcgpTemp = 0;
      }
      else
      {
         m_FcgpTemp = m_P/m_Ag + m_P*epsy*m_eTemp.Y()/m_Ixx + m_Mdlg*m_eTemp.Y()/m_Ixx;
         m_FcgpTemp *= -1.0; // Need a sign reversal to meet code equations
      }

      m_dfESTemp = kn * m_FcgpTemp;
      m_dfESPerm = kn * m_FcgpPerm;
   }
   else
   {
      CHECK(false); // new method?
   }

   m_bUpdate = false;
}
