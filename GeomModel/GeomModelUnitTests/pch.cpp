// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"

// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.

#include <GeomModel/Primitives.h>
using namespace WBFL::Geometry;
bool TestHookPoint(Shape& shape)
{
   // Hook point must have by-reference semantics
   auto hookPnt = shape.GetHookPoint();
   Point2d original_point(*hookPnt);

   // set the hook point, expecting hookPnt to change
   shape.SetHookPoint(Point2d(15, 15));
   if (*hookPnt != Point2d(15, 15)) return false;

   // replace the hook point with a new point object
   std::shared_ptr<Point2d> new_hook_point(std::make_shared<Point2d>(50, 50));
   shape.SetHookPoint(new_hook_point);

   // hookPnt is no longer associated with shape
   auto hookPnt2 = shape.GetHookPoint();
   if (hookPnt == hookPnt2) return false;

   // moving the old hook point shoudn't alter the new hook point
   hookPnt->Move(100, 100);
   if (*hookPnt == *hookPnt2) return false;

   if (*hookPnt2 != Point2d(50, 50)) return false;

   // put the shape back the way it was when this method started
   hookPnt->Move(original_point);
   shape.SetHookPoint(hookPnt);

   return true;
}