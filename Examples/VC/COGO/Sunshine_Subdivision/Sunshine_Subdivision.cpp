// Sunshine_Subdivision.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <CoordGeom/CoordGeom.h>

using namespace WBFL::COGO;

int main()
{
    // This example is based on the Sunshine Subdivision Lot 18 Example in the ICES COGO manual
    Model model;
    
    // Store Point 4
    model.StorePoint(4, 172359.243, 539284.175);

    // Locate Point 8 from Point 4
    model.LocateByDistanceAndDirection(8, 4, 561.74, Direction(Direction::NSDirection::North, 45, 15, 20, Direction::EWDirection::East), 0.0);

    // Locate Point 10 (the unlabeled curve PI)
    model.LocateByDistanceAndAngle(10, 4, 8, 660.0, Angle(75, 30, 0.0), 0.0);

    // Store Circular Curve 3 using points 8, 10, 4 and a 100 ft radius
    model.StoreCircularCurve(3, 8, 10, 4, 100.0);

    // Locate Point 2 by dividing the line segment between points 10 and 4 into two equal parts
    model.DivideBetweenPoints(2, 1, 10, 4, 2);

    // Locate Point 7 be computing the direction of the line segment between points 10 and 4, 
    // decrementing the direction, and intersecting a line from point 4 at N 45 15 20 E and
    // a line from point 2 projected towards point 7
    auto direction = model.MeasureDirection(10, 4);
    direction -= Angle(47,0,0);
    model.IntersectBearings(7, 4, Direction(Direction::NSDirection::North, 45, 15, 20, Direction::EWDirection::East), 0.0, 2, direction , 0.0);

    // Define a path for the lot boundary
    model.StorePath(0);
    model.AppendElementToPath(0, Model::PathElementType::Point, 7);
    model.AppendElementToPath(0, Model::PathElementType::Point, 8);
    model.AppendElementToPath(0, Model::PathElementType::CircularCurve, 3);
    model.AppendElementToPath(0, Model::PathElementType::Point, 2);
    model.AppendElementToPath(0, Model::PathElementType::Point, 7);

    // Output properties of the model
    std::_tcout.precision(12);

    auto dist = model.MeasureDistance(4, 7);
    std::_tcout << _T("Distance from point 4 to point 7: ") << dist << std::endl;

    dist = model.MeasureDistance(4, 2);
    std::_tcout << _T("Distance from point 4 to point 2: ") << dist << std::endl;

    std::_tcout << _T("Description of Path 0") << std::endl;
    const auto& path = model.GetPath(0);

    for (const auto& record : path)
    {
       switch (record.first)
       {
       case Model::PathElementType::Point:
       {
          auto point = model.GetPoint(record.second);
          std::_tcout << _T("Point ") << record.second << _T(" N ") << point.Y() << _T(", ") << _T("E ") << point.X() << std::endl;
          break;
       }

       case Model::PathElementType::CircularCurve:
       {
          auto curve = model.CreateCircularCurve(record.second);
          std::_tcout << _T("Curve ") << record.second << std::endl;
          std::_tcout << _T("Radius: ") << curve->GetRadius() << std::endl;
          std::_tcout << _T("Length: ") << curve->GetLength() << std::endl;
          std::_tcout << _T("Tangent: ") << curve->GetTangent() << std::endl;
          std::_tcout << _T("External: ") << curve->GetExternal() << std::endl;
          std::_tcout << _T("Chord: ") << curve->GetChord() << std::endl;
          std::_tcout << _T("Mid-ordinate: ") << curve->GetMidOrdinate() << std::endl;
          std::_tcout << _T("Degree of curvature: ") << curve->GetDegreeOfCurvature(curve->GetAngle(),DegreeCurvature::Highway).AsString() << std::endl;
          std::_tcout << _T("Delta: ") << curve->GetAngle().AsString() << std::endl;
          std::_tcout << _T("Back: ") << curve->GetBackTangentBearing().AsString() << std::endl;
          std::_tcout << _T("Ahead: ") << curve->GetForwardTangentBearing().AsString() << std::endl;
          auto pc = curve->GetPC();
          std::_tcout << _T("PC: ") << _T("N ") << pc.Y() << _T(", ") << _T("E ") << pc.X() << std::endl;
          auto pi = curve->GetPI();
          std::_tcout << _T("PI: ") << _T("N ") << pi.Y() << _T(", ") << _T("E ") << pi.X() << std::endl;
          auto pt = curve->GetPT();
          std::_tcout << _T("PT: ") << _T("N ") << pt.Y() << _T(", ") << _T("E ") << pt.X() << std::endl;

          break;
       }

       default:
          std::_tcout << L"Unexpected path element" << std::endl;
       }
    }
}
