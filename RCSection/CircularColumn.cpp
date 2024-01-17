///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
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

#include <RCSection\RCSectionLib.h>
#include <RCSection\CircularColumn.h>

using namespace WBFL::RCSection;

static void ComputeInteractionCurve(const CircularColumn& column,IndexType nSteps, Float64 ecl, Float64 etl, std::vector<std::pair<Float64, Float64>>* pUnfactored, std::vector<std::pair<Float64, Float64>>* pFactored);

CircularColumn::CircularColumn(Float64 diameter, Float64 cover, Float64 As, Float64 fc, Float64 fy, Float64 Es) :
   m_Diameter(diameter), m_Cover(cover), m_As(As), m_Fc(fc), m_Fy(fy), m_Es(Es)
{
}

void CircularColumn::SetDiameter(Float64 diameter)
{
   m_Diameter = diameter;
}

Float64 CircularColumn::GetDiameter() const
{
   return m_Diameter;
}

void CircularColumn::SetCover(Float64 cover)
{
   m_Cover = cover;
}

Float64 CircularColumn::GetCover() const
{
   return m_Cover;
}

void CircularColumn::SetAs(Float64 As)
{
   m_As = As;
}

Float64 CircularColumn::GetAs() const
{
   return m_As;
}

void CircularColumn::SetFc(Float64 fc)
{
   m_Fc = fc;
}

Float64 CircularColumn::GetFc() const
{
   return m_Fc;
}

void CircularColumn::SetFy(Float64 fy)
{
   m_Fy = fy;
}

Float64 CircularColumn::GetFy() const
{
   return m_Fy;
}

void CircularColumn::SetEs(Float64 Es)
{
   m_Es = Es;
}

Float64 CircularColumn::GetEs() const
{
   return m_Es;
}

void CircularColumn::SetStressBlockFactor(const std::shared_ptr<const StressBlockFactor>& stressBlockFactor)
{
   m_StressBlockFactor = stressBlockFactor;
}

const std::shared_ptr<const StressBlockFactor>& CircularColumn::GetStressBlockFactor() const
{
   return m_StressBlockFactor;
}

std::vector<std::pair<Float64, Float64>> CircularColumn::ComputeInteraction(IndexType nSteps) const
{
   std::vector<std::pair<Float64, Float64>> results;
   ::ComputeInteractionCurve(*this, nSteps, 0, 0, &results, nullptr);
   return results;
}

void CircularColumn::ComputeInteraction(IndexType nSteps, Float64 ecl, Float64 etl, std::vector<std::pair<Float64, Float64>>& unfactored, std::vector<std::pair<Float64, Float64>>& factored) const
{
   ::ComputeInteractionCurve(*this, nSteps, ecl, etl, &unfactored, &factored);
}

void ComputeInteractionCurve(const CircularColumn& column, IndexType nSteps, Float64 ecl, Float64 etl, std::vector<std::pair<Float64, Float64>>* pUnfactored, std::vector<std::pair<Float64, Float64>>* pFactored)
{
   // This is a C translation from an old FORTRAN routine
   // The numbers refer to the line numbers in the original FORTRAN source

   Float64 p1, xm;
   Uint32 nb;
   Float64 b;
   Float64 r1, r2, x1, y1, x2, y2, o, o1, o2, z1, z2, w, a;
   Float64 f, f1, dol, sgn;
   Uint32 count;

   p1 = 0;
   xm = 0;

   Float64 diameter = column.GetDiameter();
   Float64 cover = column.GetCover();
   Float64 As = column.GetAs();
   Float64 fc = column.GetFc();
   Float64 fy = column.GetFy();
   Float64 Es = column.GetEs();

   Float64 step_size = 2 * diameter / nSteps;

   Float64 alpha1 = column.GetStressBlockFactor()->GetIntensityFactor();
   Float64 beta1 = column.GetStressBlockFactor()->GetDepthFactor();

   r1 = diameter / 2;
   r2 = r1 - cover;
   a = As / 360;

   count = 0;
   for (IndexType i = 1; i <= nSteps; i++)
   {
      w = i * step_size; // depth to neutral axis
      for (nb = 1; nb <= 180; nb++)
      {
         b = nb * 1;
         o = b * M_PI / 180.0;
         o1 = (b - 0.5) * M_PI / 180;
         x1 = r1 * sin(o);
         y1 = r1 * cos(o) + r1;
         x2 = r2 * sin(o1);
         y2 = r2 * cos(o1) + r1;
         z1 = (1 - y1 / w) * 0.003;
         z2 = (1 - y2 / w) * 0.003;
         // Comp = plus, Tension = minus
         // Compute forces in steel ring
         if (!((y2 - beta1 * w) > 0))
         {
            if (!(fabs(z2) >= fy / Es))
            {
               f = a * (z2 * Es - alpha1 * fc);
            }
            else // 120
            {
               if (z2 < 0)
                  sgn = -1; // 121
               else
                  sgn = 1;  // 122

               f = sgn * (fy - alpha1 * fc) * a; // 123
            }
         }
         else // 125
         {
            if (!(fabs(z2) >= fy / Es)) // 150
            {
               f = z2 * Es * a;
            }
            else // 160
            {
               if (z2 < 0)
                  sgn = -1; // 161
               else
                  sgn = 1; // 162

               f = sgn * fy * a; // 163
            }
         } // 165

      // Compute forces due to concrete

         o2 = (b - 1) * M_PI / 180.;
         dol = fabs(y1 - r1 * cos(o2) - r1);
         if (!((y1 - beta1 * w) >= 0))
         {
            f1 = (x1 + r1 * sin(o2)) / 2 * dol * alpha1 * fc;
         }
         else // 190
         {
            f1 = 0;
         }

         // 195

         // Compute total axial force
         p1 += f + f1;

         // Compute total moment
         xm += f * (r1 - y2) + f1 * (r1 - (y1 + r1 * cos(o2) + r1) / 2);

      } // 220 CONTINUE

      p1 *= 2;
      xm *= 2;

      pUnfactored->emplace_back(xm, -p1); // make tension + and compression -

      if (pFactored)
      {
         Float64 et = 0.003 * ((diameter - cover) / w - 1);
         Float64 phi = 0.75 + 0.15 * (et - ecl) / (etl - ecl);
         phi = ::ForceIntoRange(0.75, phi, 0.9);

         xm *= phi;
         p1 *= phi;

         pFactored->emplace_back(xm, -p1);
      }

      count++;

      p1 = 0;
      xm = 0;
   } // 235 CONTINUE
}
