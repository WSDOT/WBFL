///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// Circular transitions for point-defined crossbeam bottom profiles.
#pragma once
#include <algorithm>
#include <cmath>

namespace WBFL { namespace Geometry {
class PointDefinedArc
{
public:
   bool Initialize(double x0, double y0, double x1, double y1, double radius, bool upward)
   {
      if (!std::isfinite(x0) || !std::isfinite(y0) || !std::isfinite(x1) ||
          !std::isfinite(y1) || !std::isfinite(radius) || x1 <= x0 || radius <= 0)
         return false;
      const double dx = x1 - x0, dy = y1 - y0;
      const double chord = std::hypot(dx, dy);
      if (!std::isfinite(chord) || radius < chord / 2)
         return false;
      const double half = chord / 2;
      const double ratio = half / radius;
      const double h = radius * std::sqrt((1 - ratio) * (1 + ratio));
      // Reject arcs that turn back horizontally: the bottom must be single-valued in X.
      if (h * (dx / chord) + chord * 1e-12 < std::abs(dy) / 2)
         return false;
      m_X0 = x0; m_Y0 = y0; m_X1 = x1; m_Y1 = y1;
      m_Radius = radius; m_Sign = upward ? 1 : -1;
      m_Cx = x0 + dx / 2 + m_Sign * h * (dy / chord);
      m_Cy = y0 + dy / 2 - m_Sign * h * (dx / chord);
      m_Start = std::atan2(y0 - m_Cy, x0 - m_Cx);
      m_Sweep = -m_Sign * 2 * std::asin(ratio);
      return std::isfinite(m_Cx) && std::isfinite(m_Cy);
   }

   double Evaluate(double x) const
   {
      if (x <= m_X0) return m_Y0;
      if (x >= m_X1) return m_Y1;
      const double a = m_X0 - m_Cx, b = x - m_Cx;
      const double q0 = std::sqrt((std::max)(0.0, (m_Radius - std::abs(a)) * (m_Radius + std::abs(a))));
      const double q = std::sqrt((std::max)(0.0, (m_Radius - std::abs(b)) * (m_Radius + std::abs(b))));
      // Rationalized circle ordinate avoids cancellation for very shallow arcs.
      return m_Y0 + m_Sign * (a - b) * (a + b) / (q0 + q);
   }

   void PointAtFraction(double fraction, double& x, double& y) const
   {
      if (fraction <= 0) { x = m_X0; y = m_Y0; return; }
      if (fraction >= 1) { x = m_X1; y = m_Y1; return; }
      const double da = fraction * m_Sweep;
      x = m_X0 - 2 * (m_Radius * std::sin(da / 2)) * std::sin(m_Start + da / 2);
      y = Evaluate(x);
   }

   int GetSegmentCount() const
   {
      const double tolerance = (m_X1 - m_X0) * 1e-6;
      const double step = std::sqrt(8 * tolerance / m_Radius);
      return (std::min)(8192, (std::max)(8, int(std::ceil(std::abs(m_Sweep) / step))));
   }

   bool IsBelowLine(double x0, double y0, double x1, double y1) const
   {
      const double slope = (y1 - y0) / (x1 - x0);
      if (Evaluate(x0) > y0 + 1e-9 || Evaluate(x1) > y1 + 1e-9)
         return false;
      if (m_Sign > 0)
      {
         const double x = m_Cx - slope * m_Radius / std::hypot(1.0, slope);
         if (x0 < x && x < x1 && Evaluate(x) > y0 + slope * (x - x0) + 1e-9)
            return false;
      }
      return true;
   }

private:
   double m_X0 = 0, m_Y0 = 0, m_X1 = 0, m_Y1 = 0;
   double m_Cx = 0, m_Cy = 0, m_Radius = 0, m_Start = 0, m_Sweep = 0;
   int m_Sign = 1;
};
}}
