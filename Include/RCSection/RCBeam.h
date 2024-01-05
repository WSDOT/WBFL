///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
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
#pragma once

#include <RCSection/RCSectionExp.h>

namespace WBFL
{
   namespace RCSection
   {
      /// Model of a simple reinforced concrete T-Beam.
      class RCSCLASS RCBeam
      {
      public:
         RCBeam() = default;
         RCBeam(Float64 fcBeam,
            Float64 fcSlab,
            Float64 fpy, Float64 fpu, Float64 fy, Float64 Aps, Float64 As, Float64 hf, Float64 b, Float64 bw, Float64 ds, Float64 dsMax, Float64 dps, Float64 dpsMax, Float64 fpe)
         {
            Init(fcBeam, fcSlab, fpy, fpu, fy, Aps, As, hf, b, bw, ds, dsMax, dps, dpsMax, fpe);
         }

         RCBeam(const RCBeam& other) = default;
         ~RCBeam() = default;
         
         RCBeam& operator=(const RCBeam& other) = default;

         void Init(Float64 fcBeam,
            Float64 fcSlab,
            Float64 fpy, Float64 fpu, Float64 fy, Float64 Aps, Float64 As, Float64 hf, Float64 b, Float64 bw, Float64 ds, Float64 dsMax,Float64 dps, Float64 dpsMax,Float64 fpe)
         {
            m_fcBeam = fcBeam;
            m_fcSlab = fcSlab;
            m_fpy = fpy;
            m_fpu = fpu;
            m_fy = fy;
            m_Aps = Aps;
            m_As = As;
            m_hf = hf;
            m_b = b;
            m_bw = bw;
            m_ds = ds;
            m_dsMax = dsMax;
            m_dps = dps;
            m_dpsMax = dpsMax;
            m_fpe = fpe;
         }

         Float64 GetFpe() const { return m_fpe; }
         void SetFpe(Float64 fpe) { m_fpe = fpe; }

         Float64 GetDps() const { return m_dps; }
         void SetDps(Float64 dps) { m_dps = dps; }

         Float64 GetDpsMax() const { return m_dpsMax; }
         void SetDpsMax(Float64 dps) { m_dpsMax = dps; }

         Float64 GetDs() const { return m_ds; }
         void SetDs(Float64 ds) { m_ds = ds; }

         Float64 GetDsMax() const { return m_dsMax; }
         void SetDsMax(Float64 ds) { m_dsMax = ds; }

         Float64 GetFcBeam() const { return m_fcBeam; }
         void SetFcBeam(Float64 fc) { m_fcBeam = fc; }

         Float64 GetFcSlab() const { return m_fcSlab; }
         void SetFcSlab(Float64 fc) { m_fcSlab = fc; }

         Float64 GetFpy() const { return m_fpy; }
         void SetFpy(Float64 fpy) { m_fpy = fpy; }

         Float64 GetFpu() const { return m_fpu; }
         void SetFpu(Float64 fpu) { m_fpu = fpu; }

         Float64 GetAps() const { return m_Aps; }
         void SetAps(Float64 aps) { m_Aps = aps; }

         Float64 GetFy() const { return m_fy; }
         void SetFy(Float64 fy) { m_fy = fy; }

         Float64 GetAs() const { return m_As; }
         void SetAs(Float64 as) { m_As = as; }

         Float64 GetHf() const { return m_hf; }
         void setHf(Float64 hf) { m_hf = hf; }

         Float64 GetBw() const { return m_bw; }
         void SetBw(Float64 bw) { m_bw = bw; }

         Float64 GetB() const { return m_b; }
         void SetB(Float64 b) { m_b = b; }

      private:
         Float64 m_fcBeam = 0.0;
         Float64 m_fcSlab = 0.0;
         Float64 m_fpy = 0.0;
         Float64 m_fpu = 0.0;
         Float64 m_fy = 0.0;
         Float64 m_Aps = 0.0;
         Float64 m_As = 0.0;
         Float64 m_hf = 0.0;
         Float64 m_b = 0.0;
         Float64 m_bw = 0.0;
         Float64 m_ds = 0.0;
         Float64 m_dsMax = 0.0;
         Float64 m_dps = 0.0;
         Float64 m_dpsMax = 0.0;
         Float64 m_fpe = 0.0;
      };
   };
};