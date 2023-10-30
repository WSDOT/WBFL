# Value Semantics of Point2d and ProfilePoint objects {#WBFL_COGO_Value_Semantics_for_Points}

WBFL::Geometry::Point2d and WBFL::COGO::ProfilePoint objects have value sematics in this library. The implication of this is PathSegment and ProfileSegent objects own copies of their end points, Point2d and ProfilePoint, respectively. To modify the end points of these objects their SetStartPoint/SetEndPoint methods must be called.

Value semantics are required because there is not a way to detect changes in these point objects which would trigger the required call to OnPathElementChanged or OnProfileElementChanged.
