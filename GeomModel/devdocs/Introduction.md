Geometric Modeling {#WBFL_GeomModel}
====================================
This library provides WBFL Engineering Services Layer geometric modeling services. Geometric modeling services include Geometric Primitives, Shape Modeling, Section Modeling, and Geometric Utilities to facilite basic geometry calculations. This library primarly supports 2D geometry, however there is support for 3D points, lines, and planes.

Geometric Primitives
--------------------
Geometric primitive are the most basic building blocks of a geometric model. Primitives include points, lines, line segments, rectangles, arcs, circles, and vectors.

Shape Modeling
---------------
Building on the geometric primitives, geometric shapes can represent the shape of anything. Examples include the cross section of a beam and a parcel of land. Every shape is positioned on the XY plane by a hook point and oriented with a rotation angle.

Basic shapes can be modeled, such as rectangles, circles, circular segments, triangles, and a general polygon. Composite shapes comprised of multiple shapes can also be modeled. Composite shapes can include shapes with voids created by other shapes. 

Commonly used bridge beam shapes, such as Box Beams, Voided Slabs, UBeams, and others are provided.

The geometric properties of shapes can be computed. Shape properties including area, moment of inertia, centroid, and bounding box. Using the shape properties object, you can transform the geometric properties into a coordinate system of your choice.

Section Modeling
----------------
Shape modeling is exteneded to modeling of structural sections. The Section object models a collection of shapes and associated material properties. Shapes can be designated as structural elements and non-structural elements. Elastic properties, such as EA and EI, can be computed. Elastic properties can tranformed into shape properties.

Geometric Utilities
--------------------
Several geometric utility objects are implemented in this library. These objects perform geometric manipulations such as coordinate transformations, computing intersection points of line and circle, and generating coordinates.
 
