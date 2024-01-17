///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2024  Washington State Department of Transportation
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

#pragma once

#include <Lrfd\LrfdExp.h>
#include <Materials/SimpleConcrete.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Encapsulates shear data.
      struct LRFDCLASS ShearData
      {
         // Input Parameters
         Float64 Mu = 0.0;
         Float64 Nu = 0.0;
         Float64 Vu = 0.0;
         Float64 phi = 0.0;
         Float64 Vp = 0.0;
         Float64 dv = 0.0;
         Float64 bv = 0.0;
         Float64 Es = 0.0;
         Float64 As = 0.0;
         Float64 Eps = 0.0;
         Float64 Aps = 0.0;
         Float64 EptSegment = 0.0;
         Float64 AptSegment = 0.0;
         Float64 EptGirder = 0.0;
         Float64 AptGirder = 0.0;
         Float64 Ec = 0.0;
         Float64 Ac = 0.0;
         Float64 fpops = 0.0;
         Float64 fpoptSegment = 0.0;
         Float64 fpoptGirder = 0.0;
         Float64 fc = 0.0;
         WBFL::Materials::ConcreteType ConcreteType = WBFL::Materials::ConcreteType::Normal;
         bool bHasfct = false;
         Float64 fct = 0.0;
         Float64 ag = 0.0; // max aggregate size
         Float64 sx = 0.0; // spacing between layers of longitudinal cracking steel
         bool bLimitNetTensionStrainToPositiveValues = false; // sets strain at the tensile reinforcement to zero if computed to be negative
         bool bIgnoreMiniumStirrupRequirementForBeta = false; // if true, LRFD Equation 5.7.3.4.2-1 is used to compute Beta regardless of the amount of stirrups

         // Vci/Vcw parameters
         Float64 Vd = 0.0;
         Float64 Vi = 0.0; // shear corresponding to Mu (Mu = Mmax)
         Float64 Mcre = 0.0; // cracking moment per LRFD 5.8.3.4.3-2
         Float64 fpc = 0.0;
         Float64 lambda = 0.0; //concrete density modification factor per LRFD2016 5.4.2.8

         Float64 fy = 0.0;  // Yield strength of stirrup material. Only applicable for 2nd Edition 2000 Interims or later
         Float64 AvS = 0.0; // Av/s per 5.8.2.5 (equation 5.8.2.5-1)
                      // Only applicable for 2nd Edition 2000 Interims or later.

         // Output Parameters
         Float64 Beta = 0.0;
         Float64 Theta = 0.0;
         Float64 ex = 0.0;
         Float64 Fe = -1.0; // = -1 if not applicable
         Float64 vu = 0.0; // from 2.8.9.2
         Float64 vufc = 0.0;   // v/fc
         Float64 vufc_tbl = 0.0; // vfc from table (2000 and later)

         Float64 sxe = 0.0; // crack spacing parameter
         Float64 sxe_tbl = 0.0; // crack spacing parameter from table

         Float64 ex_tbl = 0.0; // ex from table (2000 and later)
         Int16 Eqn = 0; // Equation used to compute strain (ex). Only applicable
                    // 2nd Edition, 2000 Interims and later.
                    // 0 = Not applicable
                    // 1 = Eqn 5.8.3.4.2-1
                    // 2 = Eqn 5.8.3.4.2-2
                    // 31 = Eqn 5.8.3.4.2-3 after 5.8.3.4.2-1
                    // 32 = Eqn 5.8.3.4.2-3 after 5.8.3.4.2-2

         Int16 BetaEqn = 0; // Equation used to compute Beta. Only applicable 2009 and after
                    // 0 = Not applicable
                    // 1 = Eqn 5.8.3.4.2-1
                    // 2 = Eqn 5.8.3.4.2-2 - lacks minimum shear reinforcement

         Int16 BetaTheta_tbl = 0; // Table used to retrieve Beta/Theta
                    // 0 = Not applicable
                    // 1 = Table 5.8.3.4.2-1
                    // 2 = Table 5.8.3.4.2-2 - lacks minimum shear reinforcement
 
         Float64 VciMin = 0.0; // Minimum Vci calculated by equation 5.8.3.4.3-1
         Float64 VciCalc = 0.0; // Vci calculated by equation 5.8.3.4.3-1
         Float64 Vci = 0.0; // Controlling Vci (max of VciCalc and Vci)
         Float64 Vcw = 0.0; // Vcw
      };

      /// @brief Utility class for shear related provisions.
      class LRFDCLASS Shear
      {
      public:
         enum class Method { Tables, Equations };

         Shear() = delete;
         Shear(const Shear&) = delete;
         Shear& operator=(const Shear&) = delete;
         ~Shear() = delete;

         /// @brief Computes the Theta and Beta factors for LRFD shear design.
         /// If the beta and theta factors could not be determined, a
         /// XShear exception will be thrown.
         // See Article 5.8.3.4
         static void ComputeThetaAndBeta(ShearData* pData, Method method = Method::Tables);


         /// @brief Computes Vci and Vcw per LRFD 4th edition 2007
         static void ComputeVciVcw(ShearData* pData);

         /// @brief Computes shear stress via 5.8.9.2
         static Float64 ComputeShearStress(Float64 Vu, Float64 Vp, Float64 phi, Float64 bv, Float64 dv);
      };


      /// @brief Utility class for shear related provisions, incorporating WSDOT specific procedures
      class LRFDCLASS WsdotShear : public Shear
      {
      public:
         WsdotShear() = delete;
         WsdotShear(const WsdotShear&) = delete;
         ~WsdotShear() = delete;

         WsdotShear& operator=(const WsdotShear&) = delete;

         /// @brief Computes the Theta and Beta factors for LRFD shear design.
         /// If the beta and theta factors could not be determined, a
         /// XShear exception will be thrown.
         /// See Article 5.8.3.4
         ///
         /// If based on LRFD 2005, we need to know if shear is being computed in the end region
         /// If it is not in the end region, Theta is limited to 25 degrees... See BDM 5.2.4F.2
         static void ComputeThetaAndBeta(ShearData* pData,bool bEndRegion = true);
      };
   };
};
