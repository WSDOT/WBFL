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

#include <RCSection\RCSectionLib.h>
#include <RCSection\SectionBuilder.h>
#include <GeomModel/Circle.h>
#include <GeomModel/GeomOp2d.h>
#include <GeomModel/GenericShape.h>
#include <GeomModel/Rectangle.h>

using namespace WBFL::RCSection;

std::shared_ptr<GeneralSection> SectionBuilder::RectangularColumn(
   Float64 H, ///< Height of cross section
   Float64 W, ///< Width of cross section
   Float64 cover, ///< Cover to center of reinforcement
   IndexType Nh, ///< Number of bars over the height of the section (N2)
   IndexType Nw, ///< Number of bars over the width of the section (N1)
   Float64 As, ///< Area of one reinforcing bar
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& concrete, ///< Constituative model for concrete
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& rebar, ///< Constituative model for reinforcing bars
   bool bModelBarsAsGenericShape ///< If true, bars are modeled as a generic shape, otherwise they are modeled as a circle
)
{
   auto section(std::make_shared<GeneralSection>());

   // overall column shape
   auto column(std::make_unique<WBFL::Geometry::Rectangle>());
   column->SetHeight(H);
   column->SetWidth(W);

   section->AddShape(_T("Column"), std::move(column), concrete, nullptr, nullptr, 1.0, true);


   // rebar
   Float64 radius = sqrt(As / M_PI);

   // top and bottom rebars
   for (IndexType i = 0; i < Nw; i++)
   {
      Float64 x = -W / 2 + cover + i * (W - 2 * cover) / (Nw - 1);
      Float64 y = H / 2 - cover;

      if (bModelBarsAsGenericShape)
      {
         auto top_bar(std::make_unique<WBFL::Geometry::GenericShape>(As, WBFL::Geometry::Point2d(x, y)));
         section->AddShape(_T("Top Bar"), std::move(top_bar), rebar, concrete, nullptr, 1.0);

         auto bottom_bar(std::make_unique<WBFL::Geometry::GenericShape>(As, WBFL::Geometry::Point2d(x, -y)));
         section->AddShape(_T("Bottom Bar"), std::move(bottom_bar), rebar, concrete, nullptr, 1.0);
      }
      else
      {
         auto top_bar(std::make_unique<WBFL::Geometry::Circle>(WBFL::Geometry::Point2d(x, y), radius));
         section->AddShape(_T("Top Bar"), std::move(top_bar), rebar, concrete, nullptr, 1.0);

         auto bottom_bar(std::make_unique<WBFL::Geometry::Circle>(WBFL::Geometry::Point2d(x, -y), radius));
         section->AddShape(_T("Bottom Bar"), std::move(bottom_bar), rebar, concrete, nullptr, 1.0);
      }
   }

   // left and right bars
   for (IndexType i = 1; i < Nh - 1; i++) // skip first and last bar because they would Float64 up with top/bottom bars
   {
      Float64 x = -W / 2 + cover;
      Float64 y = H / 2 - cover - i * (H - 2 * cover) / (Nh - 1);

      if (bModelBarsAsGenericShape)
      {
         auto left_bar(std::make_unique<WBFL::Geometry::GenericShape>(As, WBFL::Geometry::Point2d(-x, y)));
         section->AddShape(_T("Left Bar"), std::move(left_bar), rebar, concrete, nullptr, 1.0);

         auto right_bar(std::make_unique<WBFL::Geometry::GenericShape>(As, WBFL::Geometry::Point2d(x, y)));
         section->AddShape(_T("Right Bar"), std::move(right_bar), rebar, concrete, nullptr, 1.0);
      }
      else
      {
         auto left_bar(std::make_unique<WBFL::Geometry::Circle>(WBFL::Geometry::Point2d(-x, y), radius));
         section->AddShape(_T("Left Bar"), std::move(left_bar), rebar, concrete, nullptr, 1.0);

         auto right_bar(std::make_unique<WBFL::Geometry::Circle>(WBFL::Geometry::Point2d(x, y), radius));
         section->AddShape(_T("Right Bar"), std::move(right_bar), rebar, concrete, nullptr, 1.0);
      }
   }

   return section;
}

std::shared_ptr<GeneralSection> SectionBuilder::CircularColumn(
   Float64 D, ///< Diameter of the column
   Float64 cover,  ///< Cover to center of reinforcement
   IndexType Nb, ///< Number of reinforcing bars
   Float64 As, ///< Area of one reinforcing bar
   Float64 startAngle,
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& concrete, ///< Constituative model for concrete
   const std::shared_ptr<const WBFL::Materials::StressStrainModel>& rebar, ///< Constituative model for reinforcing bars
   bool bModelBarsAsGenericShape ///< If true, bars are modeled as a generic shape, otherwise they are modeled as a circle
)
{
   auto section(std::make_shared<GeneralSection>());

   // overall column shape
   auto circle(std::make_unique<WBFL::Geometry::Circle>(WBFL::Geometry::Point2d(0, 0), D / 2));

   const auto& center = circle->GetHookPoint();

   section->AddShape(_T("Column"), std::move(circle), concrete, nullptr, nullptr, 1.0, true);

   // rebar of bar (A = PI*r^2), solver for r
   Float64 radius = sqrt(As / M_PI);

   // create a utility class that can layout the rebar points
   std::vector<WBFL::Geometry::Point2d> points;
   WBFL::Geometry::GeometricOperations::GenerateCircle(Nb, *center, D / 2 - cover, startAngle, &points);

   CHECK(points.size()  == Nb);

   // loop through the points, create new rebars, and add them to the section
   for(const auto& point : points)
   {
      if (bModelBarsAsGenericShape)
      {
         auto bar(std::make_unique<WBFL::Geometry::GenericShape>(As, point));
         section->AddShape(_T("Bar"), std::move(bar), rebar, concrete, nullptr, 1.0);
      }
      else
      {
         auto bar(std::make_unique<WBFL::Geometry::Circle>(point, radius));
         section->AddShape(_T("Bar"), std::move(bar), rebar, concrete, nullptr, 1.0);
      }
   }

   return section;
}

#if defined _UNITTEST
bool SectionBuilder::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("SectionBuilder");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for SectionBuilder");
   TESTME_EPILOG("SectionBuilder");
}
#endif // _UNITTEST
