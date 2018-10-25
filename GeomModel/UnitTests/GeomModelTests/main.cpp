
#include <Units\SysUnitsMgr.h>

#include <GeomModel\Properties.h>

#include <GeomModel\ElasticProperties.h>
#include <GeomModel\Polygon.h>
#include <GeomModel\CompositeShape.h>
#include <GeomModel\Rectangle.h>
#include <GeomModel\Triangle.h>
#include <GeomModel\Circle.h>
#include <GeomModel\PrecastBeam.h>
#include <GeomModel\WsdotPrecastBeams.h>
#include <GeomModel\Section.h>

#include <Geometry\Polygon2d.h>
#include <iostream>

#include <MathEx.h>

int main()
{
   dbgFileDumpContext flog("log.txt");
   dbgLog log(&flog);

   unitSysUnitsMgr::SetAngleUnit(unitMeasure::Degree);
   unitSysUnitsMgr::SetLengthUnit(unitMeasure::Meter);

   int success=0;

    // test all of the features of shape properties
   std::cout<<"  *** Testing Properties ***"<<std::endl;
   if (gmProperties::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  // test all of the features of elastic properties
   std::cout<<"  *** Testing ElasticProperties ***"<<std::endl;
   if (gmElasticProperties::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

    // test all of the features of gmPolygon
   std::cout<<"  *** Testing Polygon ***"<<std::endl;
   if (gmPolygon::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

   // test all of the features of gmPolyPointIter
   std::cout<<"  *** Testing gmPolyPointIter ***"<<std::endl;
   if (gmPolyPointIter::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  // test all of the features of gmCompositeShape
   std::cout<<"  *** Testing CompositeShape ***"<<std::endl;
   if (gmCompositeShape::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  // test all of the features of gmShapeIter
   std::cout<<"  *** Testing ShapeIter ***"<<std::endl;
   if (gmShapeIter::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  // test all of the features of gmConstShapeIter
   std::cout<<"  *** Testing ShapeIter ***"<<std::endl;
   if (gmConstShapeIter::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  // test all of the features of gmRectangle
   std::cout<<"  *** Testing gmRectangle ***"<<std::endl;
   if (gmRectangle::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  // test all of the features of gmTriangle
   std::cout<<"  *** Testing gmTriangle ***"<<std::endl;
   if (gmTriangle::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  // test all of the features of gmCircle
   std::cout<<"  *** Testing gmCircle ***"<<std::endl;
   if (gmCircle::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  // test all of the features of gmPrecastBeam
   std::cout<<"  *** Testing gmPrecastBeam ***"<<std::endl;
   if (gmPrecastBeam::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

   // test all of the features of gmWsdotPrecastBeams
   std::cout<<"  *** Testing gmWsdotPrecastBeams ***"<<std::endl;
   if (gmWsdotPrecastBeams::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

 // test all of the features of gmSection
   std::cout<<"  *** Testing gmSection ***"<<std::endl;
   if (gmSection::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  if (success) std::cout<< "\a" << "Something Failed!!! - check it out!"<<std::endl;

  return success;
}