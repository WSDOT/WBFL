// Offset_Profile_Grade.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <CoordGeom/CoordGeom.h>

using namespace WBFL::COGO;

int main()
{
   Station refStation(2336.53);

   auto alignment = Alignment::Create();
   auto pbt = WBFL::Geometry::Point2d(2451859.110, 1005078.896);
   Direction bkTangent(_T("N 02 06 34 E"));
   auto pi = Utilities::LocateByDistanceAndDirection(pbt, (2587.80 - refStation.GetValue()), bkTangent, 0.0);
   Direction fwdTangent = bkTangent - Angle(_T("10 01 30 R"));
   auto pft = Utilities::LocateByDistanceAndDirection(pi, 5000.0, fwdTangent, 0.0);
   auto curve = CircularCurve::Create(pbt, pi, pft, 2864.79);
   auto pc = curve->GetPC();
   auto back_tangent_segment = PathSegment::Create(pbt, pc);

   alignment->AddPathElement(back_tangent_segment);
   alignment->AddPathElement(curve);
   alignment->SetReferenceStation(refStation);

   auto profile = Profile::Create();
   alignment->AddProfile(0, profile);
   auto vc1 = VerticalCurve::Create(ProfilePoint(2000.61, 289.97),ProfilePoint(2255.97, 293.16), 1.97585/100, 0.5187/100);
   profile->AddProfileElement(vc1);
   auto vc2 = VerticalCurve::Create(ProfilePoint(2749.94, 295.72), ProfilePoint(2997.77, 297.01), ProfilePoint(3245.63,295.74), 495.73/2, 495.73 / 2);
   profile->AddProfileElement(vc2);

   auto surface = Surface::Create(2, 2, 1); // 2 segments, alignment at ridge point 2, profile at ridge point 1
   profile->AddSurface(0, surface);
   auto surface_template = surface->CreateSurfaceTemplate(refStation);
   surface_template->UpdateSegmentParameters(0, 36, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);
   surface_template->UpdateSegmentParameters(1, 16, -0.02, SurfaceTemplateSegment::SlopeType::Horizontal);

   auto superelevation = Superelevation::Create(2198, 2300, 2770, 2872, -0.04, 1); // pivot at ridge point 1 (at PGL)
   surface->AddSuperelevation(superelevation);
   
   std::cout << std::fixed;
   std::cout.precision(5);

   // change the commented out lines to list elevations with different pivot points.
   // the profile of the left and right curb lines and the PGL are plotted in the Profile_Plot.xlsx spreadsheet
   superelevation->SetPivotPoint(0); // Pivot about left curb line
   //superelevation->SetPivotPoint(1); // Pivot about PGL
   //superelevation->SetPivotPoint(2); // Pivot about right curb line

   std::cout << "Station, Left Curb Elevation, PGL Elevation, Right Curb Elevation" << std::endl;
   for (int i = 0; i < 50; i++)
   {
      Station station(2000.61 + i * (3245.63 - 2000.61) / 50);
      auto elevL = profile->Elevation(surface, station, -52); // 52 ft left of alignment
      auto elevP = profile->Elevation(surface, station, -16); // 16 ft left of alignment
      auto elevR = profile->Elevation(surface, station, 0); // on the alignment

      std::cout << station.GetValue() << ", " << elevL << ", " << elevP << ", " << elevR << std::endl;
   }
}
