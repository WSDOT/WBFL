# COGO (Coordinate Geometry) {#WBFL_CoordGeom}

The WBFL COGO library has three functional areas. The first is coordinate geometry modeling. A coordinate geometry model manages geometric objects such as Points, Line Segments, Horizontal Curves, and Alignments. Primitive operations may be performed on the model to locate points in the geometric space. These operations include locating points by distance and direction, projecting points onto geometric objects, computing the intersection point of geometric objects, and dividing lines, arc, and curves. Inspiration for this functional area is taken from ICES COGO.

The second functional area is roadway geometrics. The curvilinear path of a roadway is modeled with a horizontal alignment. An alignment is comprised of Path Segments, Transition Curves, Circular Curves, Compound Curves, and Cubic Spline curves. Vertical profiles can be associated with an alignment to model the elevation along the curvilinear alignment. Vertical profiles consist of Profile Segments and Vertical Curves. Roadway cross sections may be associated with the profile to describe the roadway surface on the left and right sides of the survey line. The cross sections are used to model crown slopes. Surfaces can be modified with Widening and Superelevation objects. Section cuts can be created normal to the alignment or at a specified direction. Inspiration for this functional area is taken from TxDOT BGS.

The third functional area is bridge framing geometry. The BridgeGeometry object provides a wide variety of methods of defining plan view bridge framing geometry. The geometry of pier lines, girder lines, and deck edges and end boundaries are defined. The geometry can be defined directly or through the use of layout lines. An example is defining layout lines that are parallel to a curved alignment, and then defining layout lines as chords that intersect the layout lines at centerlines of piers. This functional area is also inspired from TxDOT BGS.

@subpage WBFL_COGO_Using_this_library

@subpage WBFL_COGO_Implementor_Notes
