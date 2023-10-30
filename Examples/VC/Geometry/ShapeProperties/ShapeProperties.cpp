// ShapeProperties.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <GeomModel/GeomModel.h>

int main()
{
   // Build a square that is 20x20 with the center of the bottom
   // edge at (0,0)
   WBFL::Geometry::Polygon polygon;
   polygon.SetSymmetry(WBFL::Geometry::Polygon::Symmetry::Y); // symmetric about the Y=0 axis

   //          ^ Y-axis
   //          :
   //          +----+ (10,20)
   //          :    |
   //          :    |                 Model half the shape.
   //          :    |
   //          :    |
   //          +----+.......> X-axis
   //          (0,0)

   polygon.AddPoint(0, 0); // point on axis of symmetry
   polygon.AddPoint(10, 0); // bottom right corner
   polygon.AddPoint(10, 20); // top right corner
   polygon.AddPoint(0, 20); // point on axis of symmetry

   auto properties = polygon.GetProperties();
   const auto& cg = properties.GetCentroid();
   std::_tcout << _T("CG (x,y): ") << cg.X() << _T(", ") << cg.Y() << std::endl;
   std::_tcout << _T("Distance from centroid to boundaries of the bounding box") << std::endl;
   std::_tcout << _T("Left: ") << properties.GetXleft() << std::endl;
   std::_tcout << _T("Right: ") << properties.GetXright() << std::endl;
   std::_tcout << _T("Top: ") << properties.GetYtop() << std::endl;
   std::_tcout << _T("Bottom: ") << properties.GetYbottom() << std::endl;
   std::_tcout << std::endl;
   std::_tcout << _T("Area: ") << properties.GetArea() << std::endl;
   std::_tcout << _T("Ixx: ") << properties.GetIxx() << std::endl;
   std::_tcout << _T("Iyy: ") << properties.GetIyy() << std::endl;
}
