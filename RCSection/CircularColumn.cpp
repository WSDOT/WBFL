///////////////////////////////////////////////////////////////////////
// RCSection - Reinforced concrete section analysis modeling
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

#if defined _UNITTEST
struct PM { Float64 P; Float64 M; };

bool CircularColumn::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CircularColumn");
   CircularColumn column(72,3,10,4,60,29000);

   auto results = column.ComputeInteraction(37);

   static PM datum[] = {
      {287.2848746, 10493.21979},
      {-259.9527058, 27246.45396},
      {-846.4345725, 43248.35621},
      {-1492.644891, 58743.86342},
      {-2259.446164, 74511.36885},
      {-3014.816758, 87409.23471},
      {-3844.13023, 98740.05594},
      {-4590.484531, 106425.1228},
      {-5520.696536, 112896.4532},
      {-6330.609276, 115562.4822},
      {-7160.623561, 115308.0894},
      {-7983.30927, 112623.8928},
      {-8930.346629, 106717.6939},
      {-9691.083634, 99502.87508},
      {-10539.87688, 88865.96765},
      {-11314.52527, 76585.26225},
      {-12003.65098, 63477.17158},
      {-12598.89774, 50389.12453},
      {-13233.81625, 34420.86843},
      {-13696.65124, 21339.02324},
      {-14093.40885, 8930.83373},
      {-14249.39515, 3758.73538},
      {-14263.19028, 3476.500725},
      {-14275.69861, 3216.658878},
      {-14287.07821, 2976.708707},
      {-14297.46005, 2754.506713},
      {-14306.95557, 2548.224968},
      {-14315.66016, 2356.295113},
      {-14323.65596, 2177.363962},
      {-14331.014, 2010.257996},
      {-14337.79594, 1853.954921},
      {-14344.05373, 1707.565645},
      {-14349.8368, 1570.303536},
      {-14355.18674, 1441.475904},
      {-14360.14027, 1320.470342},
      {-14364.72995, 1206.743856},
      {-14368.98471, 1099.813739}
   };

   IndexType count = results.size();
   TRY_TESTME(count == 37);

   for (IndexType i = 0; i < count; i++)
   {
      Float64 M = results[i].first;
      Float64 P = results[i].second;

      TRY_TESTME(IsEqual(datum[i].P, P, 0.0001));
      TRY_TESTME(IsEqual(datum[i].M, M, 0.0001));
   }
   TESTME_EPILOG("CircularColumn");
}
#endif // _UNITTEST
