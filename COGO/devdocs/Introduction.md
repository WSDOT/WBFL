WBFL COGO {#WBFL_COGO}
=========
The WBFL COGO library has two functional areas. The first is coordinate geometry modeling. A coordinate geometry model manages geometric objects such as Points, Line Segments, Horizontal Curves, and Alignments. Primitive operations may be performed on the model to locate points in the geometric space. These operations include locating points by distance and direction, projecting points onto geometric objects, computing the intersection point of geometric objects, and dividing lines, arc, and curves.

The second functional area roadway geometrics. The curvilinear path of a roadway is modeled with a horizontal alignment. An alignment is comprised of Points, Line Segments, and Horizontal Curves with or without transition spirals. A vertical profile can be associated with an alignment to model the elevation along the curvilinear alignment. Vertical profiles consist of Profile Points and Vertical Curves. Roadway cross sections may be associated with the profile to describe the roadway surface on the left and right sides of the survey line. The cross sections are used to model crown slopes and superelevation transitions.

General Concepts
----------------
There are several general concepts used consistently throughout the WBFL COGO library. The following topics explain them.

\subpage WBFL_COGO_CogoModel

\subpage WBFL_Cogo_Collections_and_Enumerators

\subpage WBFL_COGO_Angles_Directions_Stations

\subpage WBFL_COGO_Factories

\subpage WBFL_COGO_Offsets

\subpage WBFL_COGO_Units
