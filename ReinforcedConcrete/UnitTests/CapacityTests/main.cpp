#include <iostream>
#include <ReinforcedConcrete\UnitTest.h>


#include <GeomModel\Polygon.h>
#include <GeomModel\Properties.h>
#include <GeomModel\ShapeUtils.h>
void test(gmPolygon& rect);

int main()
{

   dbgFileDumpContext fctx("test.out");
   dbgLog my_log(&fctx);
   return (int)rcaUnitTest::TestMe(my_log);

   return 0;
}


void test(gmPolygon& rect)
{
   Uint32 p1 = rect.AddPoint(gpPoint2d(0 , 0));
   p1 = rect.AddPoint(gpPoint2d(0 ,50));
   p1 = rect.AddPoint(gpPoint2d(40,50));
   p1 = rect.AddPoint(gpPoint2d(40,0));
   gpLine2d up_left(gpPoint2d(0,0), gpVector2d(gpSize2d(1,1)));
   gpLine2d up_rgt(gpPoint2d(40,0), gpVector2d(gpSize2d(-3,5)));
   std::auto_ptr<gmIShape> pfirst(rect.CreateClippedShape(up_left, gpLine2d::Right));
   pfirst->EnableBorderMode(true);
}
