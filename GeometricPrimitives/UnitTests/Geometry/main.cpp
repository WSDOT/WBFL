
#include <Geometry\Vector2d.h>
#include <Geometry\Line2d.h>
#include <Geometry\LineSegment2d.h>
#include <Geometry\GeomOp2d.h>
#include <Geometry\Polygon2d.h>
#include <iostream>
#include <system\system.h>


int main()
{
   dbgFileDumpContext flog("log.txt");
   dbgLog log(&flog);
   int success=0;

   // test all of the features of a size

   std::cout<<"  *** Testing Size2d ***"<<std::endl;
   if (gpSize2d::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1; 
   }

   // test all of the features of a point

   std::cout<<"  *** Testing Point2d ***"<<std::endl;
   if (gpPoint2d::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

   // test all of the features of a rect

   std::cout<<"  *** Testing Rect2d ***"<<std::endl;
   if (gpRect2d::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

   // test all of the features of a vector

   std::cout<<"  *** Testing Vector2d ***"<<std::endl;
   if (gpVector2d::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

   // test all of the features of a line

   std::cout<<"  *** Testing Line2d ***"<<std::endl;
   if (gpLine2d::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

   // test all of the features of a line segment

   std::cout<<"  *** Testing LineSegment2d ***"<<std::endl;
   if (gpLineSegment2d::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
   {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  // test all of the features of a GeomOp

   std::cout<<"  *** Testing GeomOp2d ***"<<std::endl;
   if (gpGeomOp2d::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
    {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

  // test all of the features of a Polygon

   std::cout<<"  *** Testing Polygon2d ***"<<std::endl;
   if (gpPolygon2d::TestMe(log) == 1)
      std::cout << "Passed"<<std::endl;
   else
    {
      std::cout << "Failed"<<std::endl;
      success=1;
   }

   if(log.GetNumErrors()>0)
   {
      std::cout << "***** "<<log.GetNumErrors()<<" Tests Failed - check log"<<"\a"<<std::endl;
   }
   else
   {
      std::cout << "All Tests Passed"<<std::endl;
   }
   
   return success;
}