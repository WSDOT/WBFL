

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:22:34 2017
 */
/* Compiler settings for ..\Include\WBFLGeometry.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __WBFLGeometry_h__
#define __WBFLGeometry_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISize2d_FWD_DEFINED__
#define __ISize2d_FWD_DEFINED__
typedef interface ISize2d ISize2d;

#endif 	/* __ISize2d_FWD_DEFINED__ */


#ifndef __ISize3d_FWD_DEFINED__
#define __ISize3d_FWD_DEFINED__
typedef interface ISize3d ISize3d;

#endif 	/* __ISize3d_FWD_DEFINED__ */


#ifndef __IVector3d_FWD_DEFINED__
#define __IVector3d_FWD_DEFINED__
typedef interface IVector3d IVector3d;

#endif 	/* __IVector3d_FWD_DEFINED__ */


#ifndef __IPoint2d_FWD_DEFINED__
#define __IPoint2d_FWD_DEFINED__
typedef interface IPoint2d IPoint2d;

#endif 	/* __IPoint2d_FWD_DEFINED__ */


#ifndef __IPoint2dEvents_FWD_DEFINED__
#define __IPoint2dEvents_FWD_DEFINED__
typedef interface IPoint2dEvents IPoint2dEvents;

#endif 	/* __IPoint2dEvents_FWD_DEFINED__ */


#ifndef __IRect2d_FWD_DEFINED__
#define __IRect2d_FWD_DEFINED__
typedef interface IRect2d IRect2d;

#endif 	/* __IRect2d_FWD_DEFINED__ */


#ifndef __IVector2d_FWD_DEFINED__
#define __IVector2d_FWD_DEFINED__
typedef interface IVector2d IVector2d;

#endif 	/* __IVector2d_FWD_DEFINED__ */


#ifndef __IEnumPoint2d_FWD_DEFINED__
#define __IEnumPoint2d_FWD_DEFINED__
typedef interface IEnumPoint2d IEnumPoint2d;

#endif 	/* __IEnumPoint2d_FWD_DEFINED__ */


#ifndef __IPoint2dCollection_FWD_DEFINED__
#define __IPoint2dCollection_FWD_DEFINED__
typedef interface IPoint2dCollection IPoint2dCollection;

#endif 	/* __IPoint2dCollection_FWD_DEFINED__ */


#ifndef __IPoint2dCollectionEvents_FWD_DEFINED__
#define __IPoint2dCollectionEvents_FWD_DEFINED__
typedef interface IPoint2dCollectionEvents IPoint2dCollectionEvents;

#endif 	/* __IPoint2dCollectionEvents_FWD_DEFINED__ */


#ifndef __ILineSegment2d_FWD_DEFINED__
#define __ILineSegment2d_FWD_DEFINED__
typedef interface ILineSegment2d ILineSegment2d;

#endif 	/* __ILineSegment2d_FWD_DEFINED__ */


#ifndef __ILineSegment2dEvents_FWD_DEFINED__
#define __ILineSegment2dEvents_FWD_DEFINED__
typedef interface ILineSegment2dEvents ILineSegment2dEvents;

#endif 	/* __ILineSegment2dEvents_FWD_DEFINED__ */


#ifndef __ILine2d_FWD_DEFINED__
#define __ILine2d_FWD_DEFINED__
typedef interface ILine2d ILine2d;

#endif 	/* __ILine2d_FWD_DEFINED__ */


#ifndef __IPoint3d_FWD_DEFINED__
#define __IPoint3d_FWD_DEFINED__
typedef interface IPoint3d IPoint3d;

#endif 	/* __IPoint3d_FWD_DEFINED__ */


#ifndef __IPoint3dEvents_FWD_DEFINED__
#define __IPoint3dEvents_FWD_DEFINED__
typedef interface IPoint3dEvents IPoint3dEvents;

#endif 	/* __IPoint3dEvents_FWD_DEFINED__ */


#ifndef __ILineSegment3d_FWD_DEFINED__
#define __ILineSegment3d_FWD_DEFINED__
typedef interface ILineSegment3d ILineSegment3d;

#endif 	/* __ILineSegment3d_FWD_DEFINED__ */


#ifndef __ILineSegment3dEvents_FWD_DEFINED__
#define __ILineSegment3dEvents_FWD_DEFINED__
typedef interface ILineSegment3dEvents ILineSegment3dEvents;

#endif 	/* __ILineSegment3dEvents_FWD_DEFINED__ */


#ifndef __IPlane3d_FWD_DEFINED__
#define __IPlane3d_FWD_DEFINED__
typedef interface IPlane3d IPlane3d;

#endif 	/* __IPlane3d_FWD_DEFINED__ */


#ifndef __IEnumPoint3d_FWD_DEFINED__
#define __IEnumPoint3d_FWD_DEFINED__
typedef interface IEnumPoint3d IEnumPoint3d;

#endif 	/* __IEnumPoint3d_FWD_DEFINED__ */


#ifndef __IPoint3dCollection_FWD_DEFINED__
#define __IPoint3dCollection_FWD_DEFINED__
typedef interface IPoint3dCollection IPoint3dCollection;

#endif 	/* __IPoint3dCollection_FWD_DEFINED__ */


#ifndef __IPoint3dCollectionEvents_FWD_DEFINED__
#define __IPoint3dCollectionEvents_FWD_DEFINED__
typedef interface IPoint3dCollectionEvents IPoint3dCollectionEvents;

#endif 	/* __IPoint3dCollectionEvents_FWD_DEFINED__ */


#ifndef __IShapeProperties_FWD_DEFINED__
#define __IShapeProperties_FWD_DEFINED__
typedef interface IShapeProperties IShapeProperties;

#endif 	/* __IShapeProperties_FWD_DEFINED__ */


#ifndef __IShape_FWD_DEFINED__
#define __IShape_FWD_DEFINED__
typedef interface IShape IShape;

#endif 	/* __IShape_FWD_DEFINED__ */


#ifndef __IEnumShape_FWD_DEFINED__
#define __IEnumShape_FWD_DEFINED__
typedef interface IEnumShape IEnumShape;

#endif 	/* __IEnumShape_FWD_DEFINED__ */


#ifndef __IShapeCollection_FWD_DEFINED__
#define __IShapeCollection_FWD_DEFINED__
typedef interface IShapeCollection IShapeCollection;

#endif 	/* __IShapeCollection_FWD_DEFINED__ */


#ifndef __IXYPosition_FWD_DEFINED__
#define __IXYPosition_FWD_DEFINED__
typedef interface IXYPosition IXYPosition;

#endif 	/* __IXYPosition_FWD_DEFINED__ */


#ifndef __IGenericShape_FWD_DEFINED__
#define __IGenericShape_FWD_DEFINED__
typedef interface IGenericShape IGenericShape;

#endif 	/* __IGenericShape_FWD_DEFINED__ */


#ifndef __IPolyShape_FWD_DEFINED__
#define __IPolyShape_FWD_DEFINED__
typedef interface IPolyShape IPolyShape;

#endif 	/* __IPolyShape_FWD_DEFINED__ */


#ifndef __ICircle_FWD_DEFINED__
#define __ICircle_FWD_DEFINED__
typedef interface ICircle ICircle;

#endif 	/* __ICircle_FWD_DEFINED__ */


#ifndef __IRectangle_FWD_DEFINED__
#define __IRectangle_FWD_DEFINED__
typedef interface IRectangle IRectangle;

#endif 	/* __IRectangle_FWD_DEFINED__ */


#ifndef __ITriangle_FWD_DEFINED__
#define __ITriangle_FWD_DEFINED__
typedef interface ITriangle ITriangle;

#endif 	/* __ITriangle_FWD_DEFINED__ */


#ifndef __IPrecastBeam_FWD_DEFINED__
#define __IPrecastBeam_FWD_DEFINED__
typedef interface IPrecastBeam IPrecastBeam;

#endif 	/* __IPrecastBeam_FWD_DEFINED__ */


#ifndef __INUBeam_FWD_DEFINED__
#define __INUBeam_FWD_DEFINED__
typedef interface INUBeam INUBeam;

#endif 	/* __INUBeam_FWD_DEFINED__ */


#ifndef __IBulbTee_FWD_DEFINED__
#define __IBulbTee_FWD_DEFINED__
typedef interface IBulbTee IBulbTee;

#endif 	/* __IBulbTee_FWD_DEFINED__ */


#ifndef __IBulbTee2_FWD_DEFINED__
#define __IBulbTee2_FWD_DEFINED__
typedef interface IBulbTee2 IBulbTee2;

#endif 	/* __IBulbTee2_FWD_DEFINED__ */


#ifndef __IMultiWeb_FWD_DEFINED__
#define __IMultiWeb_FWD_DEFINED__
typedef interface IMultiWeb IMultiWeb;

#endif 	/* __IMultiWeb_FWD_DEFINED__ */


#ifndef __IMultiWeb2_FWD_DEFINED__
#define __IMultiWeb2_FWD_DEFINED__
typedef interface IMultiWeb2 IMultiWeb2;

#endif 	/* __IMultiWeb2_FWD_DEFINED__ */


#ifndef __ITrafficBarrier_FWD_DEFINED__
#define __ITrafficBarrier_FWD_DEFINED__
typedef interface ITrafficBarrier ITrafficBarrier;

#endif 	/* __ITrafficBarrier_FWD_DEFINED__ */


#ifndef __IPoint2dFactory_FWD_DEFINED__
#define __IPoint2dFactory_FWD_DEFINED__
typedef interface IPoint2dFactory IPoint2dFactory;

#endif 	/* __IPoint2dFactory_FWD_DEFINED__ */


#ifndef __IPoint3dFactory_FWD_DEFINED__
#define __IPoint3dFactory_FWD_DEFINED__
typedef interface IPoint3dFactory IPoint3dFactory;

#endif 	/* __IPoint3dFactory_FWD_DEFINED__ */


#ifndef __ILine2dFactory_FWD_DEFINED__
#define __ILine2dFactory_FWD_DEFINED__
typedef interface ILine2dFactory ILine2dFactory;

#endif 	/* __ILine2dFactory_FWD_DEFINED__ */


#ifndef __ILineSegment2dFactory_FWD_DEFINED__
#define __ILineSegment2dFactory_FWD_DEFINED__
typedef interface ILineSegment2dFactory ILineSegment2dFactory;

#endif 	/* __ILineSegment2dFactory_FWD_DEFINED__ */


#ifndef __IGeomUtil2d_FWD_DEFINED__
#define __IGeomUtil2d_FWD_DEFINED__
typedef interface IGeomUtil2d IGeomUtil2d;

#endif 	/* __IGeomUtil2d_FWD_DEFINED__ */


#ifndef __IGeomUtil3d_FWD_DEFINED__
#define __IGeomUtil3d_FWD_DEFINED__
typedef interface IGeomUtil3d IGeomUtil3d;

#endif 	/* __IGeomUtil3d_FWD_DEFINED__ */


#ifndef __IGeomUtil_FWD_DEFINED__
#define __IGeomUtil_FWD_DEFINED__
typedef interface IGeomUtil IGeomUtil;

#endif 	/* __IGeomUtil_FWD_DEFINED__ */


#ifndef __ICoordinateXform3d_FWD_DEFINED__
#define __ICoordinateXform3d_FWD_DEFINED__
typedef interface ICoordinateXform3d ICoordinateXform3d;

#endif 	/* __ICoordinateXform3d_FWD_DEFINED__ */


#ifndef __ICoordinateXform2d_FWD_DEFINED__
#define __ICoordinateXform2d_FWD_DEFINED__
typedef interface ICoordinateXform2d ICoordinateXform2d;

#endif 	/* __ICoordinateXform2d_FWD_DEFINED__ */


#ifndef __ICircularSegment_FWD_DEFINED__
#define __ICircularSegment_FWD_DEFINED__
typedef interface ICircularSegment ICircularSegment;

#endif 	/* __ICircularSegment_FWD_DEFINED__ */


#ifndef __IPlateGirder_FWD_DEFINED__
#define __IPlateGirder_FWD_DEFINED__
typedef interface IPlateGirder IPlateGirder;

#endif 	/* __IPlateGirder_FWD_DEFINED__ */


#ifndef __IUBeam_FWD_DEFINED__
#define __IUBeam_FWD_DEFINED__
typedef interface IUBeam IUBeam;

#endif 	/* __IUBeam_FWD_DEFINED__ */


#ifndef __IUBeam2_FWD_DEFINED__
#define __IUBeam2_FWD_DEFINED__
typedef interface IUBeam2 IUBeam2;

#endif 	/* __IUBeam2_FWD_DEFINED__ */


#ifndef __ICompositeShapeItem_FWD_DEFINED__
#define __ICompositeShapeItem_FWD_DEFINED__
typedef interface ICompositeShapeItem ICompositeShapeItem;

#endif 	/* __ICompositeShapeItem_FWD_DEFINED__ */


#ifndef __ICompositeShape_FWD_DEFINED__
#define __ICompositeShape_FWD_DEFINED__
typedef interface ICompositeShape ICompositeShape;

#endif 	/* __ICompositeShape_FWD_DEFINED__ */


#ifndef __IVoidedSlab_FWD_DEFINED__
#define __IVoidedSlab_FWD_DEFINED__
typedef interface IVoidedSlab IVoidedSlab;

#endif 	/* __IVoidedSlab_FWD_DEFINED__ */


#ifndef __IVoidedSlab2_FWD_DEFINED__
#define __IVoidedSlab2_FWD_DEFINED__
typedef interface IVoidedSlab2 IVoidedSlab2;

#endif 	/* __IVoidedSlab2_FWD_DEFINED__ */


#ifndef __IBoxBeam_FWD_DEFINED__
#define __IBoxBeam_FWD_DEFINED__
typedef interface IBoxBeam IBoxBeam;

#endif 	/* __IBoxBeam_FWD_DEFINED__ */


#ifndef __IDeckedSlabBeam_FWD_DEFINED__
#define __IDeckedSlabBeam_FWD_DEFINED__
typedef interface IDeckedSlabBeam IDeckedSlabBeam;

#endif 	/* __IDeckedSlabBeam_FWD_DEFINED__ */


#ifndef __IFasterPolyShape_FWD_DEFINED__
#define __IFasterPolyShape_FWD_DEFINED__
typedef interface IFasterPolyShape IFasterPolyShape;

#endif 	/* __IFasterPolyShape_FWD_DEFINED__ */


#ifndef __Point2d_FWD_DEFINED__
#define __Point2d_FWD_DEFINED__

#ifdef __cplusplus
typedef class Point2d Point2d;
#else
typedef struct Point2d Point2d;
#endif /* __cplusplus */

#endif 	/* __Point2d_FWD_DEFINED__ */


#ifndef __Size2d_FWD_DEFINED__
#define __Size2d_FWD_DEFINED__

#ifdef __cplusplus
typedef class Size2d Size2d;
#else
typedef struct Size2d Size2d;
#endif /* __cplusplus */

#endif 	/* __Size2d_FWD_DEFINED__ */


#ifndef __Rect2d_FWD_DEFINED__
#define __Rect2d_FWD_DEFINED__

#ifdef __cplusplus
typedef class Rect2d Rect2d;
#else
typedef struct Rect2d Rect2d;
#endif /* __cplusplus */

#endif 	/* __Rect2d_FWD_DEFINED__ */


#ifndef __Vector2d_FWD_DEFINED__
#define __Vector2d_FWD_DEFINED__

#ifdef __cplusplus
typedef class Vector2d Vector2d;
#else
typedef struct Vector2d Vector2d;
#endif /* __cplusplus */

#endif 	/* __Vector2d_FWD_DEFINED__ */


#ifndef __Point2dCollection_FWD_DEFINED__
#define __Point2dCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Point2dCollection Point2dCollection;
#else
typedef struct Point2dCollection Point2dCollection;
#endif /* __cplusplus */

#endif 	/* __Point2dCollection_FWD_DEFINED__ */


#ifndef __LineSegment2d_FWD_DEFINED__
#define __LineSegment2d_FWD_DEFINED__

#ifdef __cplusplus
typedef class LineSegment2d LineSegment2d;
#else
typedef struct LineSegment2d LineSegment2d;
#endif /* __cplusplus */

#endif 	/* __LineSegment2d_FWD_DEFINED__ */


#ifndef __Line2d_FWD_DEFINED__
#define __Line2d_FWD_DEFINED__

#ifdef __cplusplus
typedef class Line2d Line2d;
#else
typedef struct Line2d Line2d;
#endif /* __cplusplus */

#endif 	/* __Line2d_FWD_DEFINED__ */


#ifndef __ShapeProperties_FWD_DEFINED__
#define __ShapeProperties_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShapeProperties ShapeProperties;
#else
typedef struct ShapeProperties ShapeProperties;
#endif /* __cplusplus */

#endif 	/* __ShapeProperties_FWD_DEFINED__ */


#ifndef __PolyShape_FWD_DEFINED__
#define __PolyShape_FWD_DEFINED__

#ifdef __cplusplus
typedef class PolyShape PolyShape;
#else
typedef struct PolyShape PolyShape;
#endif /* __cplusplus */

#endif 	/* __PolyShape_FWD_DEFINED__ */


#ifndef __FasterPolyShape_FWD_DEFINED__
#define __FasterPolyShape_FWD_DEFINED__

#ifdef __cplusplus
typedef class FasterPolyShape FasterPolyShape;
#else
typedef struct FasterPolyShape FasterPolyShape;
#endif /* __cplusplus */

#endif 	/* __FasterPolyShape_FWD_DEFINED__ */


#ifndef __Circle_FWD_DEFINED__
#define __Circle_FWD_DEFINED__

#ifdef __cplusplus
typedef class Circle Circle;
#else
typedef struct Circle Circle;
#endif /* __cplusplus */

#endif 	/* __Circle_FWD_DEFINED__ */


#ifndef __Rect_FWD_DEFINED__
#define __Rect_FWD_DEFINED__

#ifdef __cplusplus
typedef class Rect Rect;
#else
typedef struct Rect Rect;
#endif /* __cplusplus */

#endif 	/* __Rect_FWD_DEFINED__ */


#ifndef __Triangle_FWD_DEFINED__
#define __Triangle_FWD_DEFINED__

#ifdef __cplusplus
typedef class Triangle Triangle;
#else
typedef struct Triangle Triangle;
#endif /* __cplusplus */

#endif 	/* __Triangle_FWD_DEFINED__ */


#ifndef __PrecastBeam_FWD_DEFINED__
#define __PrecastBeam_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrecastBeam PrecastBeam;
#else
typedef struct PrecastBeam PrecastBeam;
#endif /* __cplusplus */

#endif 	/* __PrecastBeam_FWD_DEFINED__ */


#ifndef __NUBeam_FWD_DEFINED__
#define __NUBeam_FWD_DEFINED__

#ifdef __cplusplus
typedef class NUBeam NUBeam;
#else
typedef struct NUBeam NUBeam;
#endif /* __cplusplus */

#endif 	/* __NUBeam_FWD_DEFINED__ */


#ifndef __BulbTee_FWD_DEFINED__
#define __BulbTee_FWD_DEFINED__

#ifdef __cplusplus
typedef class BulbTee BulbTee;
#else
typedef struct BulbTee BulbTee;
#endif /* __cplusplus */

#endif 	/* __BulbTee_FWD_DEFINED__ */


#ifndef __BulbTee2_FWD_DEFINED__
#define __BulbTee2_FWD_DEFINED__

#ifdef __cplusplus
typedef class BulbTee2 BulbTee2;
#else
typedef struct BulbTee2 BulbTee2;
#endif /* __cplusplus */

#endif 	/* __BulbTee2_FWD_DEFINED__ */


#ifndef __TrafficBarrier_FWD_DEFINED__
#define __TrafficBarrier_FWD_DEFINED__

#ifdef __cplusplus
typedef class TrafficBarrier TrafficBarrier;
#else
typedef struct TrafficBarrier TrafficBarrier;
#endif /* __cplusplus */

#endif 	/* __TrafficBarrier_FWD_DEFINED__ */


#ifndef __Point3d_FWD_DEFINED__
#define __Point3d_FWD_DEFINED__

#ifdef __cplusplus
typedef class Point3d Point3d;
#else
typedef struct Point3d Point3d;
#endif /* __cplusplus */

#endif 	/* __Point3d_FWD_DEFINED__ */


#ifndef __LineSegment3d_FWD_DEFINED__
#define __LineSegment3d_FWD_DEFINED__

#ifdef __cplusplus
typedef class LineSegment3d LineSegment3d;
#else
typedef struct LineSegment3d LineSegment3d;
#endif /* __cplusplus */

#endif 	/* __LineSegment3d_FWD_DEFINED__ */


#ifndef __Size3d_FWD_DEFINED__
#define __Size3d_FWD_DEFINED__

#ifdef __cplusplus
typedef class Size3d Size3d;
#else
typedef struct Size3d Size3d;
#endif /* __cplusplus */

#endif 	/* __Size3d_FWD_DEFINED__ */


#ifndef __Vector3d_FWD_DEFINED__
#define __Vector3d_FWD_DEFINED__

#ifdef __cplusplus
typedef class Vector3d Vector3d;
#else
typedef struct Vector3d Vector3d;
#endif /* __cplusplus */

#endif 	/* __Vector3d_FWD_DEFINED__ */


#ifndef __Plane3d_FWD_DEFINED__
#define __Plane3d_FWD_DEFINED__

#ifdef __cplusplus
typedef class Plane3d Plane3d;
#else
typedef struct Plane3d Plane3d;
#endif /* __cplusplus */

#endif 	/* __Plane3d_FWD_DEFINED__ */


#ifndef __Point3dCollection_FWD_DEFINED__
#define __Point3dCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Point3dCollection Point3dCollection;
#else
typedef struct Point3dCollection Point3dCollection;
#endif /* __cplusplus */

#endif 	/* __Point3dCollection_FWD_DEFINED__ */


#ifndef __GeomUtil_FWD_DEFINED__
#define __GeomUtil_FWD_DEFINED__

#ifdef __cplusplus
typedef class GeomUtil GeomUtil;
#else
typedef struct GeomUtil GeomUtil;
#endif /* __cplusplus */

#endif 	/* __GeomUtil_FWD_DEFINED__ */


#ifndef __CoordinateXform3d_FWD_DEFINED__
#define __CoordinateXform3d_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoordinateXform3d CoordinateXform3d;
#else
typedef struct CoordinateXform3d CoordinateXform3d;
#endif /* __cplusplus */

#endif 	/* __CoordinateXform3d_FWD_DEFINED__ */


#ifndef __CoordinateXform2d_FWD_DEFINED__
#define __CoordinateXform2d_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoordinateXform2d CoordinateXform2d;
#else
typedef struct CoordinateXform2d CoordinateXform2d;
#endif /* __cplusplus */

#endif 	/* __CoordinateXform2d_FWD_DEFINED__ */


#ifndef __PrimitiveFactory_FWD_DEFINED__
#define __PrimitiveFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrimitiveFactory PrimitiveFactory;
#else
typedef struct PrimitiveFactory PrimitiveFactory;
#endif /* __cplusplus */

#endif 	/* __PrimitiveFactory_FWD_DEFINED__ */


#ifndef __CircularSegment_FWD_DEFINED__
#define __CircularSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class CircularSegment CircularSegment;
#else
typedef struct CircularSegment CircularSegment;
#endif /* __cplusplus */

#endif 	/* __CircularSegment_FWD_DEFINED__ */


#ifndef __ShapeCollection_FWD_DEFINED__
#define __ShapeCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShapeCollection ShapeCollection;
#else
typedef struct ShapeCollection ShapeCollection;
#endif /* __cplusplus */

#endif 	/* __ShapeCollection_FWD_DEFINED__ */


#ifndef __PlateGirder_FWD_DEFINED__
#define __PlateGirder_FWD_DEFINED__

#ifdef __cplusplus
typedef class PlateGirder PlateGirder;
#else
typedef struct PlateGirder PlateGirder;
#endif /* __cplusplus */

#endif 	/* __PlateGirder_FWD_DEFINED__ */


#ifndef __UBeam_FWD_DEFINED__
#define __UBeam_FWD_DEFINED__

#ifdef __cplusplus
typedef class UBeam UBeam;
#else
typedef struct UBeam UBeam;
#endif /* __cplusplus */

#endif 	/* __UBeam_FWD_DEFINED__ */


#ifndef __UBeam2_FWD_DEFINED__
#define __UBeam2_FWD_DEFINED__

#ifdef __cplusplus
typedef class UBeam2 UBeam2;
#else
typedef struct UBeam2 UBeam2;
#endif /* __cplusplus */

#endif 	/* __UBeam2_FWD_DEFINED__ */


#ifndef __MultiWeb_FWD_DEFINED__
#define __MultiWeb_FWD_DEFINED__

#ifdef __cplusplus
typedef class MultiWeb MultiWeb;
#else
typedef struct MultiWeb MultiWeb;
#endif /* __cplusplus */

#endif 	/* __MultiWeb_FWD_DEFINED__ */


#ifndef __MultiWeb2_FWD_DEFINED__
#define __MultiWeb2_FWD_DEFINED__

#ifdef __cplusplus
typedef class MultiWeb2 MultiWeb2;
#else
typedef struct MultiWeb2 MultiWeb2;
#endif /* __cplusplus */

#endif 	/* __MultiWeb2_FWD_DEFINED__ */


#ifndef __CompositeShapeItem_FWD_DEFINED__
#define __CompositeShapeItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompositeShapeItem CompositeShapeItem;
#else
typedef struct CompositeShapeItem CompositeShapeItem;
#endif /* __cplusplus */

#endif 	/* __CompositeShapeItem_FWD_DEFINED__ */


#ifndef __CompositeShape_FWD_DEFINED__
#define __CompositeShape_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompositeShape CompositeShape;
#else
typedef struct CompositeShape CompositeShape;
#endif /* __cplusplus */

#endif 	/* __CompositeShape_FWD_DEFINED__ */


#ifndef __VoidedSlab_FWD_DEFINED__
#define __VoidedSlab_FWD_DEFINED__

#ifdef __cplusplus
typedef class VoidedSlab VoidedSlab;
#else
typedef struct VoidedSlab VoidedSlab;
#endif /* __cplusplus */

#endif 	/* __VoidedSlab_FWD_DEFINED__ */


#ifndef __VoidedSlab2_FWD_DEFINED__
#define __VoidedSlab2_FWD_DEFINED__

#ifdef __cplusplus
typedef class VoidedSlab2 VoidedSlab2;
#else
typedef struct VoidedSlab2 VoidedSlab2;
#endif /* __cplusplus */

#endif 	/* __VoidedSlab2_FWD_DEFINED__ */


#ifndef __BoxBeam_FWD_DEFINED__
#define __BoxBeam_FWD_DEFINED__

#ifdef __cplusplus
typedef class BoxBeam BoxBeam;
#else
typedef struct BoxBeam BoxBeam;
#endif /* __cplusplus */

#endif 	/* __BoxBeam_FWD_DEFINED__ */


#ifndef __DeckedSlabBeam_FWD_DEFINED__
#define __DeckedSlabBeam_FWD_DEFINED__

#ifdef __cplusplus
typedef class DeckedSlabBeam DeckedSlabBeam;
#else
typedef struct DeckedSlabBeam DeckedSlabBeam;
#endif /* __cplusplus */

#endif 	/* __DeckedSlabBeam_FWD_DEFINED__ */


#ifndef __GenericShape_FWD_DEFINED__
#define __GenericShape_FWD_DEFINED__

#ifdef __cplusplus
typedef class GenericShape GenericShape;
#else
typedef struct GenericShape GenericShape;
#endif /* __cplusplus */

#endif 	/* __GenericShape_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLGeometry_0000_0000 */
/* [local] */ 

#define GEOMETRY_E_NOTNORMALIZED             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,512)
#define GEOMETRY_E_ZEROMAGNITUDE             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,513)
#define GEOMETRY_E_MAGNITUDELESSTHANZERO     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,514)
#define GEOMETRY_E_SAMEPOINTS                MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,515)
#define GEOMETRY_E_INFINITESOLUTIONS         MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,516)
#define GEOMETRY_E_NOSOLUTIONS               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,517)
#define GEOMETRY_E_RADIUS                    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,518)
#define GEOMETRY_E_DIMENSION                 MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,519)
#define GEOMETRY_E_POINTONLINE               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,520)
#define GEOMETRY_E_MIDORDINATE               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,521)
#define GEOMETRY_E_ANGLE                     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,522)
#define GEOMETRY_E_DISTANCE                  MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,523)
#define GEOMETRY_E_COINCIDENTPOINTS          MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,524)
#define GEOMETRY_E_COLINEAR                  MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,525)


extern RPC_IF_HANDLE __MIDL_itf_WBFLGeometry_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLGeometry_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLGeometry_LIBRARY_DEFINED__
#define __WBFLGeometry_LIBRARY_DEFINED__

/* library WBFLGeometry */
/* [helpstring][helpcontext][helpfile][version][uuid] */ 

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("7615DFC0-0013-11d3-8CDF-8BF0A4AD5B35") 
enum __MIDL___MIDL_itf_WBFLGeometry_0000_0000_0001
    {
        lpHookPoint	= 0,
        lpTopLeft	= 1,
        lpTopCenter	= 2,
        lpTopRight	= 3,
        lpCenterLeft	= 4,
        lpCenterCenter	= 5,
        lpCenterRight	= 6,
        lpBottomLeft	= 7,
        lpBottomCenter	= 8,
        lpBottomRight	= 9
    } 	LocatorPointType;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("FABE04A0-FF96-11d2-8CDF-F43C3928A334") 
enum __MIDL___MIDL_itf_WBFLGeometry_0000_0000_0002
    {
        csCentroidal	= 0,
        csGlobal	= 1,
        csPrinciple	= 2,
        csUser	= 3
    } 	CoordinateSystemType;

typedef /* [public][public][public][public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("D03C2CC0-5DD8-11d3-8CDF-A057587EDC05") 
enum __MIDL___MIDL_itf_WBFLGeometry_0000_0000_0003
    {
        xfrmOldToNew	= 1,
        xfrmNewToOld	= 2
    } 	XformType;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("C64376A0-03CF-11d3-8CDF-EBFB6612CA35") 
enum __MIDL___MIDL_itf_WBFLGeometry_0000_0000_0004
    {
        tboLeft	= 0,
        tboRight	= ( tboLeft + 1 ) 
    } 	TrafficBarrierOrientation;





EXTERN_C const IID LIBID_WBFLGeometry;

#ifndef __ISize2d_INTERFACE_DEFINED__
#define __ISize2d_INTERFACE_DEFINED__

/* interface ISize2d */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISize2d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("55B8EF97-FADF-11D2-8CDF-9849C70CC734")
    ISize2d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dx( 
            /* [retval][out] */ Float64 *dx) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dx( 
            /* [in] */ Float64 dx) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dy( 
            /* [retval][out] */ Float64 *dy) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dy( 
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Magnitude( 
            /* [retval][out] */ Float64 *mag) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Scale( 
            /* [in] */ Float64 factor) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Dimensions( 
            /* [out] */ Float64 *pDx,
            /* [out] */ Float64 *pDy) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISize2d **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISize2dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISize2d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISize2d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISize2d * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dx )( 
            ISize2d * This,
            /* [retval][out] */ Float64 *dx);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dx )( 
            ISize2d * This,
            /* [in] */ Float64 dx);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dy )( 
            ISize2d * This,
            /* [retval][out] */ Float64 *dy);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dy )( 
            ISize2d * This,
            /* [in] */ Float64 dy);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Magnitude )( 
            ISize2d * This,
            /* [retval][out] */ Float64 *mag);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Scale )( 
            ISize2d * This,
            /* [in] */ Float64 factor);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ISize2d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Dimensions )( 
            ISize2d * This,
            /* [out] */ Float64 *pDx,
            /* [out] */ Float64 *pDy);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISize2d * This,
            /* [retval][out] */ ISize2d **clone);
        
        END_INTERFACE
    } ISize2dVtbl;

    interface ISize2d
    {
        CONST_VTBL struct ISize2dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISize2d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISize2d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISize2d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISize2d_get_Dx(This,dx)	\
    ( (This)->lpVtbl -> get_Dx(This,dx) ) 

#define ISize2d_put_Dx(This,dx)	\
    ( (This)->lpVtbl -> put_Dx(This,dx) ) 

#define ISize2d_get_Dy(This,dy)	\
    ( (This)->lpVtbl -> get_Dy(This,dy) ) 

#define ISize2d_put_Dy(This,dy)	\
    ( (This)->lpVtbl -> put_Dy(This,dy) ) 

#define ISize2d_get_Magnitude(This,mag)	\
    ( (This)->lpVtbl -> get_Magnitude(This,mag) ) 

#define ISize2d_Scale(This,factor)	\
    ( (This)->lpVtbl -> Scale(This,factor) ) 

#define ISize2d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define ISize2d_Dimensions(This,pDx,pDy)	\
    ( (This)->lpVtbl -> Dimensions(This,pDx,pDy) ) 

#define ISize2d_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISize2d_INTERFACE_DEFINED__ */


#ifndef __ISize3d_INTERFACE_DEFINED__
#define __ISize3d_INTERFACE_DEFINED__

/* interface ISize3d */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISize3d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("75DB33E0-0449-11D3-8CDF-9E53F9A4BF35")
    ISize3d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dx( 
            /* [retval][out] */ Float64 *dx) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dx( 
            /* [in] */ Float64 dx) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dy( 
            /* [retval][out] */ Float64 *dy) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dy( 
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dz( 
            /* [retval][out] */ Float64 *dz) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dz( 
            /* [in] */ Float64 dz) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Magnitude( 
            /* [retval][out] */ Float64 *mag) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Scale( 
            /* [in] */ Float64 factor) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Dimensions( 
            /* [out] */ Float64 *pDx,
            /* [out] */ Float64 *pDy,
            /* [out] */ Float64 *pDz) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISize3d **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISize3dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISize3d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISize3d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISize3d * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dx )( 
            ISize3d * This,
            /* [retval][out] */ Float64 *dx);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dx )( 
            ISize3d * This,
            /* [in] */ Float64 dx);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dy )( 
            ISize3d * This,
            /* [retval][out] */ Float64 *dy);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dy )( 
            ISize3d * This,
            /* [in] */ Float64 dy);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dz )( 
            ISize3d * This,
            /* [retval][out] */ Float64 *dz);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dz )( 
            ISize3d * This,
            /* [in] */ Float64 dz);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Magnitude )( 
            ISize3d * This,
            /* [retval][out] */ Float64 *mag);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Scale )( 
            ISize3d * This,
            /* [in] */ Float64 factor);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ISize3d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Dimensions )( 
            ISize3d * This,
            /* [out] */ Float64 *pDx,
            /* [out] */ Float64 *pDy,
            /* [out] */ Float64 *pDz);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISize3d * This,
            /* [retval][out] */ ISize3d **clone);
        
        END_INTERFACE
    } ISize3dVtbl;

    interface ISize3d
    {
        CONST_VTBL struct ISize3dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISize3d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISize3d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISize3d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISize3d_get_Dx(This,dx)	\
    ( (This)->lpVtbl -> get_Dx(This,dx) ) 

#define ISize3d_put_Dx(This,dx)	\
    ( (This)->lpVtbl -> put_Dx(This,dx) ) 

#define ISize3d_get_Dy(This,dy)	\
    ( (This)->lpVtbl -> get_Dy(This,dy) ) 

#define ISize3d_put_Dy(This,dy)	\
    ( (This)->lpVtbl -> put_Dy(This,dy) ) 

#define ISize3d_get_Dz(This,dz)	\
    ( (This)->lpVtbl -> get_Dz(This,dz) ) 

#define ISize3d_put_Dz(This,dz)	\
    ( (This)->lpVtbl -> put_Dz(This,dz) ) 

#define ISize3d_get_Magnitude(This,mag)	\
    ( (This)->lpVtbl -> get_Magnitude(This,mag) ) 

#define ISize3d_Scale(This,factor)	\
    ( (This)->lpVtbl -> Scale(This,factor) ) 

#define ISize3d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define ISize3d_Dimensions(This,pDx,pDy,pDz)	\
    ( (This)->lpVtbl -> Dimensions(This,pDx,pDy,pDz) ) 

#define ISize3d_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISize3d_INTERFACE_DEFINED__ */


#ifndef __IVector3d_INTERFACE_DEFINED__
#define __IVector3d_INTERFACE_DEFINED__

/* interface IVector3d */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVector3d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F97D8401-1871-11D3-8CDF-925649DD1F63")
    IVector3d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Z( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Z( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IsZero( 
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Magnitude( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Magnitude( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Normalize( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy,
            /* [in] */ Float64 dz) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OffsetEx( 
            /* [in] */ ISize3d *pSize) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Projection( 
            /* [in] */ IVector3d *pVector,
            /* [retval][out] */ Float64 *pDist) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reflect( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Scale( 
            /* [in] */ Float64 factor) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ ISize3d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Cross( 
            /* [in] */ IVector3d *v,
            /* [retval][out] */ IVector3d **result) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Dot( 
            /* [in] */ IVector3d *v,
            /* [retval][out] */ Float64 *val) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AngleBetween( 
            /* [in] */ IVector3d *v,
            /* [retval][out] */ Float64 *angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IncrementBy( 
            /* [in] */ IVector3d *v,
            /* [retval][out] */ IVector3d **val) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Increment( 
            /* [in] */ IVector3d *v) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DecrementBy( 
            /* [in] */ IVector3d *v,
            /* [retval][out] */ IVector3d **val) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Decrement( 
            /* [in] */ IVector3d *v) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IVector3d **ppClone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVector3dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVector3d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVector3d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVector3d * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IVector3d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IVector3d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IVector3d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IVector3d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Z )( 
            IVector3d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Z )( 
            IVector3d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsZero )( 
            IVector3d * This,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Magnitude )( 
            IVector3d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Magnitude )( 
            IVector3d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Normalize )( 
            IVector3d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IVector3d * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy,
            /* [in] */ Float64 dz);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffsetEx )( 
            IVector3d * This,
            /* [in] */ ISize3d *pSize);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Projection )( 
            IVector3d * This,
            /* [in] */ IVector3d *pVector,
            /* [retval][out] */ Float64 *pDist);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reflect )( 
            IVector3d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Scale )( 
            IVector3d * This,
            /* [in] */ Float64 factor);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IVector3d * This,
            /* [retval][out] */ ISize3d **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Cross )( 
            IVector3d * This,
            /* [in] */ IVector3d *v,
            /* [retval][out] */ IVector3d **result);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Dot )( 
            IVector3d * This,
            /* [in] */ IVector3d *v,
            /* [retval][out] */ Float64 *val);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AngleBetween )( 
            IVector3d * This,
            /* [in] */ IVector3d *v,
            /* [retval][out] */ Float64 *angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IncrementBy )( 
            IVector3d * This,
            /* [in] */ IVector3d *v,
            /* [retval][out] */ IVector3d **val);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Increment )( 
            IVector3d * This,
            /* [in] */ IVector3d *v);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecrementBy )( 
            IVector3d * This,
            /* [in] */ IVector3d *v,
            /* [retval][out] */ IVector3d **val);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Decrement )( 
            IVector3d * This,
            /* [in] */ IVector3d *v);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IVector3d * This,
            /* [retval][out] */ IVector3d **ppClone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IVector3d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IVector3dVtbl;

    interface IVector3d
    {
        CONST_VTBL struct IVector3dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVector3d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVector3d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVector3d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVector3d_get_X(This,pVal)	\
    ( (This)->lpVtbl -> get_X(This,pVal) ) 

#define IVector3d_put_X(This,newVal)	\
    ( (This)->lpVtbl -> put_X(This,newVal) ) 

#define IVector3d_get_Y(This,pVal)	\
    ( (This)->lpVtbl -> get_Y(This,pVal) ) 

#define IVector3d_put_Y(This,newVal)	\
    ( (This)->lpVtbl -> put_Y(This,newVal) ) 

#define IVector3d_get_Z(This,pVal)	\
    ( (This)->lpVtbl -> get_Z(This,pVal) ) 

#define IVector3d_put_Z(This,newVal)	\
    ( (This)->lpVtbl -> put_Z(This,newVal) ) 

#define IVector3d_IsZero(This,pbResult)	\
    ( (This)->lpVtbl -> IsZero(This,pbResult) ) 

#define IVector3d_get_Magnitude(This,pVal)	\
    ( (This)->lpVtbl -> get_Magnitude(This,pVal) ) 

#define IVector3d_put_Magnitude(This,newVal)	\
    ( (This)->lpVtbl -> put_Magnitude(This,newVal) ) 

#define IVector3d_Normalize(This)	\
    ( (This)->lpVtbl -> Normalize(This) ) 

#define IVector3d_Offset(This,dx,dy,dz)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy,dz) ) 

#define IVector3d_OffsetEx(This,pSize)	\
    ( (This)->lpVtbl -> OffsetEx(This,pSize) ) 

#define IVector3d_Projection(This,pVector,pDist)	\
    ( (This)->lpVtbl -> Projection(This,pVector,pDist) ) 

#define IVector3d_Reflect(This)	\
    ( (This)->lpVtbl -> Reflect(This) ) 

#define IVector3d_Scale(This,factor)	\
    ( (This)->lpVtbl -> Scale(This,factor) ) 

#define IVector3d_get_Size(This,pVal)	\
    ( (This)->lpVtbl -> get_Size(This,pVal) ) 

#define IVector3d_Cross(This,v,result)	\
    ( (This)->lpVtbl -> Cross(This,v,result) ) 

#define IVector3d_Dot(This,v,val)	\
    ( (This)->lpVtbl -> Dot(This,v,val) ) 

#define IVector3d_AngleBetween(This,v,angle)	\
    ( (This)->lpVtbl -> AngleBetween(This,v,angle) ) 

#define IVector3d_IncrementBy(This,v,val)	\
    ( (This)->lpVtbl -> IncrementBy(This,v,val) ) 

#define IVector3d_Increment(This,v)	\
    ( (This)->lpVtbl -> Increment(This,v) ) 

#define IVector3d_DecrementBy(This,v,val)	\
    ( (This)->lpVtbl -> DecrementBy(This,v,val) ) 

#define IVector3d_Decrement(This,v)	\
    ( (This)->lpVtbl -> Decrement(This,v) ) 

#define IVector3d_Clone(This,ppClone)	\
    ( (This)->lpVtbl -> Clone(This,ppClone) ) 

#define IVector3d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVector3d_INTERFACE_DEFINED__ */


#ifndef __IPoint2d_INTERFACE_DEFINED__
#define __IPoint2d_INTERFACE_DEFINED__

/* interface IPoint2d */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPoint2d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("55B8EF96-FADF-11D2-8CDF-9849C70CC734")
    IPoint2d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ Float64 *x) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X( 
            /* [in] */ Float64 x) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ Float64 *y) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y( 
            /* [in] */ Float64 y) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ Float64 x,
            /* [in] */ Float64 y) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveEx( 
            /* [in] */ IPoint2d *to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OffsetEx( 
            /* [in] */ ISize2d *size) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ Float64 cx,
            /* [in] */ Float64 cy,
            /* [in] */ Float64 angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RotateEx( 
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 angle) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SameLocation( 
            /* [in] */ IPoint2d *pOther) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Location( 
            /* [out] */ Float64 *pX,
            /* [out] */ Float64 *pY) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Distance( 
            /* [in] */ Float64 x,
            /* [in] */ Float64 y,
            /* [retval][out] */ Float64 *pDistance) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DistanceEx( 
            /* [in] */ IPoint2d *pOther,
            /* [retval][out] */ Float64 *pDistance) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPoint2dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint2d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint2d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint2d * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IPoint2d * This,
            /* [retval][out] */ Float64 *x);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IPoint2d * This,
            /* [in] */ Float64 x);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IPoint2d * This,
            /* [retval][out] */ Float64 *y);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IPoint2d * This,
            /* [in] */ Float64 y);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IPoint2d * This,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveEx )( 
            IPoint2d * This,
            /* [in] */ IPoint2d *to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IPoint2d * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffsetEx )( 
            IPoint2d * This,
            /* [in] */ ISize2d *size);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            IPoint2d * This,
            /* [in] */ Float64 cx,
            /* [in] */ Float64 cy,
            /* [in] */ Float64 angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RotateEx )( 
            IPoint2d * This,
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 angle);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPoint2d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SameLocation )( 
            IPoint2d * This,
            /* [in] */ IPoint2d *pOther);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Location )( 
            IPoint2d * This,
            /* [out] */ Float64 *pX,
            /* [out] */ Float64 *pY);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Distance )( 
            IPoint2d * This,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y,
            /* [retval][out] */ Float64 *pDistance);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DistanceEx )( 
            IPoint2d * This,
            /* [in] */ IPoint2d *pOther,
            /* [retval][out] */ Float64 *pDistance);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPoint2d * This,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        END_INTERFACE
    } IPoint2dVtbl;

    interface IPoint2d
    {
        CONST_VTBL struct IPoint2dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint2d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPoint2d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPoint2d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPoint2d_get_X(This,x)	\
    ( (This)->lpVtbl -> get_X(This,x) ) 

#define IPoint2d_put_X(This,x)	\
    ( (This)->lpVtbl -> put_X(This,x) ) 

#define IPoint2d_get_Y(This,y)	\
    ( (This)->lpVtbl -> get_Y(This,y) ) 

#define IPoint2d_put_Y(This,y)	\
    ( (This)->lpVtbl -> put_Y(This,y) ) 

#define IPoint2d_Move(This,x,y)	\
    ( (This)->lpVtbl -> Move(This,x,y) ) 

#define IPoint2d_MoveEx(This,to)	\
    ( (This)->lpVtbl -> MoveEx(This,to) ) 

#define IPoint2d_Offset(This,dx,dy)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy) ) 

#define IPoint2d_OffsetEx(This,size)	\
    ( (This)->lpVtbl -> OffsetEx(This,size) ) 

#define IPoint2d_Rotate(This,cx,cy,angle)	\
    ( (This)->lpVtbl -> Rotate(This,cx,cy,angle) ) 

#define IPoint2d_RotateEx(This,center,angle)	\
    ( (This)->lpVtbl -> RotateEx(This,center,angle) ) 

#define IPoint2d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define IPoint2d_SameLocation(This,pOther)	\
    ( (This)->lpVtbl -> SameLocation(This,pOther) ) 

#define IPoint2d_Location(This,pX,pY)	\
    ( (This)->lpVtbl -> Location(This,pX,pY) ) 

#define IPoint2d_Distance(This,x,y,pDistance)	\
    ( (This)->lpVtbl -> Distance(This,x,y,pDistance) ) 

#define IPoint2d_DistanceEx(This,pOther,pDistance)	\
    ( (This)->lpVtbl -> DistanceEx(This,pOther,pDistance) ) 

#define IPoint2d_Clone(This,ppPoint)	\
    ( (This)->lpVtbl -> Clone(This,ppPoint) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPoint2d_INTERFACE_DEFINED__ */


#ifndef __IPoint2dEvents_INTERFACE_DEFINED__
#define __IPoint2dEvents_INTERFACE_DEFINED__

/* interface IPoint2dEvents */
/* [unique][helpstring][helpcontext][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IPoint2dEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11B3531F-ACDA-4b32-AAAB-28F9693256B2")
    IPoint2dEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointChanged( 
            IPoint2d *point) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPoint2dEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint2dEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint2dEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint2dEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointChanged )( 
            IPoint2dEvents * This,
            IPoint2d *point);
        
        END_INTERFACE
    } IPoint2dEventsVtbl;

    interface IPoint2dEvents
    {
        CONST_VTBL struct IPoint2dEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint2dEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPoint2dEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPoint2dEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPoint2dEvents_OnPointChanged(This,point)	\
    ( (This)->lpVtbl -> OnPointChanged(This,point) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPoint2dEvents_INTERFACE_DEFINED__ */


#ifndef __IRect2d_INTERFACE_DEFINED__
#define __IRect2d_INTERFACE_DEFINED__

/* interface IRect2d */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRect2d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("55B8EF98-FADF-11D2-8CDF-9849C70CC734")
    IRect2d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Right( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Right( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Bottom( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Bottom( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Area( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomLeft( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomCenter( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomRight( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CenterCenter( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CenterLeft( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CenterRight( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopLeft( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopCenter( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopRight( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE BoundPoint( 
            /* [in] */ Float64 x,
            /* [in] */ Float64 y) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE BoundPointEx( 
            /* [in] */ IPoint2d *pPoint) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Inflate( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE InflateEx( 
            /* [in] */ ISize2d *pSize) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Normalize( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OffsetEx( 
            /* [in] */ ISize2d *pSize) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Intersect( 
            /* [in] */ IRect2d *pRect,
            /* [retval][out] */ IRect2d **ppIntersection) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Union( 
            /* [in] */ IRect2d *pRect) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE UnionBy( 
            /* [in] */ IRect2d *pRect,
            /* [retval][out] */ IRect2d **ppUnion) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Size( 
            /* [retval][out] */ ISize2d **ppSize) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetEmpty( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetNull( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ContainsPoint( 
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ContainsRect( 
            /* [in] */ IRect2d *pRect,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Touches( 
            /* [in] */ IRect2d *pRect,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IsNull( 
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IsNormalized( 
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IRect2d **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetBounds( 
            /* [in] */ Float64 Left,
            /* [in] */ Float64 Right,
            /* [in] */ Float64 Bottom,
            /* [in] */ Float64 Top) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBounds( 
            /* [out] */ Float64 *pLeft,
            /* [out] */ Float64 *pRight,
            /* [out] */ Float64 *pBottom,
            /* [out] */ Float64 *pTop) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRect2dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRect2d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRect2d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRect2d * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Left )( 
            IRect2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Left )( 
            IRect2d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Right )( 
            IRect2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Right )( 
            IRect2d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Top )( 
            IRect2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Top )( 
            IRect2d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bottom )( 
            IRect2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Bottom )( 
            IRect2d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Area )( 
            IRect2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomLeft )( 
            IRect2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomCenter )( 
            IRect2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomRight )( 
            IRect2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CenterCenter )( 
            IRect2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CenterLeft )( 
            IRect2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CenterRight )( 
            IRect2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopLeft )( 
            IRect2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopCenter )( 
            IRect2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopRight )( 
            IRect2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *BoundPoint )( 
            IRect2d * This,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *BoundPointEx )( 
            IRect2d * This,
            /* [in] */ IPoint2d *pPoint);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IRect2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IRect2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Inflate )( 
            IRect2d * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *InflateEx )( 
            IRect2d * This,
            /* [in] */ ISize2d *pSize);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Normalize )( 
            IRect2d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IRect2d * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffsetEx )( 
            IRect2d * This,
            /* [in] */ ISize2d *pSize);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Intersect )( 
            IRect2d * This,
            /* [in] */ IRect2d *pRect,
            /* [retval][out] */ IRect2d **ppIntersection);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Union )( 
            IRect2d * This,
            /* [in] */ IRect2d *pRect);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnionBy )( 
            IRect2d * This,
            /* [in] */ IRect2d *pRect,
            /* [retval][out] */ IRect2d **ppUnion);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Size )( 
            IRect2d * This,
            /* [retval][out] */ ISize2d **ppSize);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            IRect2d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetNull )( 
            IRect2d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ContainsPoint )( 
            IRect2d * This,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ContainsRect )( 
            IRect2d * This,
            /* [in] */ IRect2d *pRect,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Touches )( 
            IRect2d * This,
            /* [in] */ IRect2d *pRect,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsNull )( 
            IRect2d * This,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsNormalized )( 
            IRect2d * This,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IRect2d * This,
            /* [retval][out] */ IRect2d **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IRect2d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetBounds )( 
            IRect2d * This,
            /* [in] */ Float64 Left,
            /* [in] */ Float64 Right,
            /* [in] */ Float64 Bottom,
            /* [in] */ Float64 Top);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBounds )( 
            IRect2d * This,
            /* [out] */ Float64 *pLeft,
            /* [out] */ Float64 *pRight,
            /* [out] */ Float64 *pBottom,
            /* [out] */ Float64 *pTop);
        
        END_INTERFACE
    } IRect2dVtbl;

    interface IRect2d
    {
        CONST_VTBL struct IRect2dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRect2d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRect2d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRect2d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRect2d_get_Left(This,pVal)	\
    ( (This)->lpVtbl -> get_Left(This,pVal) ) 

#define IRect2d_put_Left(This,newVal)	\
    ( (This)->lpVtbl -> put_Left(This,newVal) ) 

#define IRect2d_get_Right(This,pVal)	\
    ( (This)->lpVtbl -> get_Right(This,pVal) ) 

#define IRect2d_put_Right(This,newVal)	\
    ( (This)->lpVtbl -> put_Right(This,newVal) ) 

#define IRect2d_get_Top(This,pVal)	\
    ( (This)->lpVtbl -> get_Top(This,pVal) ) 

#define IRect2d_put_Top(This,newVal)	\
    ( (This)->lpVtbl -> put_Top(This,newVal) ) 

#define IRect2d_get_Bottom(This,pVal)	\
    ( (This)->lpVtbl -> get_Bottom(This,pVal) ) 

#define IRect2d_put_Bottom(This,newVal)	\
    ( (This)->lpVtbl -> put_Bottom(This,newVal) ) 

#define IRect2d_get_Area(This,pVal)	\
    ( (This)->lpVtbl -> get_Area(This,pVal) ) 

#define IRect2d_get_BottomLeft(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomLeft(This,pVal) ) 

#define IRect2d_get_BottomCenter(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomCenter(This,pVal) ) 

#define IRect2d_get_BottomRight(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomRight(This,pVal) ) 

#define IRect2d_get_CenterCenter(This,pVal)	\
    ( (This)->lpVtbl -> get_CenterCenter(This,pVal) ) 

#define IRect2d_get_CenterLeft(This,pVal)	\
    ( (This)->lpVtbl -> get_CenterLeft(This,pVal) ) 

#define IRect2d_get_CenterRight(This,pVal)	\
    ( (This)->lpVtbl -> get_CenterRight(This,pVal) ) 

#define IRect2d_get_TopLeft(This,pVal)	\
    ( (This)->lpVtbl -> get_TopLeft(This,pVal) ) 

#define IRect2d_get_TopCenter(This,pVal)	\
    ( (This)->lpVtbl -> get_TopCenter(This,pVal) ) 

#define IRect2d_get_TopRight(This,pVal)	\
    ( (This)->lpVtbl -> get_TopRight(This,pVal) ) 

#define IRect2d_BoundPoint(This,x,y)	\
    ( (This)->lpVtbl -> BoundPoint(This,x,y) ) 

#define IRect2d_BoundPointEx(This,pPoint)	\
    ( (This)->lpVtbl -> BoundPointEx(This,pPoint) ) 

#define IRect2d_get_Width(This,pVal)	\
    ( (This)->lpVtbl -> get_Width(This,pVal) ) 

#define IRect2d_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define IRect2d_Inflate(This,dx,dy)	\
    ( (This)->lpVtbl -> Inflate(This,dx,dy) ) 

#define IRect2d_InflateEx(This,pSize)	\
    ( (This)->lpVtbl -> InflateEx(This,pSize) ) 

#define IRect2d_Normalize(This)	\
    ( (This)->lpVtbl -> Normalize(This) ) 

#define IRect2d_Offset(This,dx,dy)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy) ) 

#define IRect2d_OffsetEx(This,pSize)	\
    ( (This)->lpVtbl -> OffsetEx(This,pSize) ) 

#define IRect2d_Intersect(This,pRect,ppIntersection)	\
    ( (This)->lpVtbl -> Intersect(This,pRect,ppIntersection) ) 

#define IRect2d_Union(This,pRect)	\
    ( (This)->lpVtbl -> Union(This,pRect) ) 

#define IRect2d_UnionBy(This,pRect,ppUnion)	\
    ( (This)->lpVtbl -> UnionBy(This,pRect,ppUnion) ) 

#define IRect2d_Size(This,ppSize)	\
    ( (This)->lpVtbl -> Size(This,ppSize) ) 

#define IRect2d_SetEmpty(This)	\
    ( (This)->lpVtbl -> SetEmpty(This) ) 

#define IRect2d_SetNull(This)	\
    ( (This)->lpVtbl -> SetNull(This) ) 

#define IRect2d_ContainsPoint(This,pPoint,pbResult)	\
    ( (This)->lpVtbl -> ContainsPoint(This,pPoint,pbResult) ) 

#define IRect2d_ContainsRect(This,pRect,pbResult)	\
    ( (This)->lpVtbl -> ContainsRect(This,pRect,pbResult) ) 

#define IRect2d_Touches(This,pRect,pbResult)	\
    ( (This)->lpVtbl -> Touches(This,pRect,pbResult) ) 

#define IRect2d_IsNull(This,pbResult)	\
    ( (This)->lpVtbl -> IsNull(This,pbResult) ) 

#define IRect2d_IsNormalized(This,pbResult)	\
    ( (This)->lpVtbl -> IsNormalized(This,pbResult) ) 

#define IRect2d_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IRect2d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define IRect2d_SetBounds(This,Left,Right,Bottom,Top)	\
    ( (This)->lpVtbl -> SetBounds(This,Left,Right,Bottom,Top) ) 

#define IRect2d_GetBounds(This,pLeft,pRight,pBottom,pTop)	\
    ( (This)->lpVtbl -> GetBounds(This,pLeft,pRight,pBottom,pTop) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRect2d_INTERFACE_DEFINED__ */


#ifndef __IVector2d_INTERFACE_DEFINED__
#define __IVector2d_INTERFACE_DEFINED__

/* interface IVector2d */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVector2d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("55B8EF9A-FADF-11D2-8CDF-9849C70CC734")
    IVector2d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Direction( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Magnitude( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Magnitude( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ ISize2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IsZero( 
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Normal( 
            /* [retval][out] */ IVector2d **ppNormal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Normalize( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OffsetEx( 
            /* [in] */ ISize2d *pSize) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Projection( 
            /* [in] */ IVector2d *pVector,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reflect( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ Float64 angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Scale( 
            /* [in] */ Float64 factor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Dot( 
            /* [in] */ IVector2d *v,
            /* [retval][out] */ Float64 *val) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AngleBetween( 
            /* [in] */ IVector2d *v,
            /* [retval][out] */ Float64 *val) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IncrementBy( 
            /* [in] */ IVector2d *v,
            /* [retval][out] */ IVector2d **val) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Increment( 
            /* [in] */ IVector2d *v) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DecrementBy( 
            /* [in] */ IVector2d *v,
            /* [retval][out] */ IVector2d **val) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Decrement( 
            /* [in] */ IVector2d *v) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IVector2d **ppClone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVector2dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVector2d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVector2d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVector2d * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IVector2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IVector2d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IVector2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IVector2d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Direction )( 
            IVector2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Direction )( 
            IVector2d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Magnitude )( 
            IVector2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Magnitude )( 
            IVector2d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IVector2d * This,
            /* [retval][out] */ ISize2d **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsZero )( 
            IVector2d * This,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Normal )( 
            IVector2d * This,
            /* [retval][out] */ IVector2d **ppNormal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Normalize )( 
            IVector2d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IVector2d * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffsetEx )( 
            IVector2d * This,
            /* [in] */ ISize2d *pSize);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Projection )( 
            IVector2d * This,
            /* [in] */ IVector2d *pVector,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reflect )( 
            IVector2d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            IVector2d * This,
            /* [in] */ Float64 angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Scale )( 
            IVector2d * This,
            /* [in] */ Float64 factor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Dot )( 
            IVector2d * This,
            /* [in] */ IVector2d *v,
            /* [retval][out] */ Float64 *val);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AngleBetween )( 
            IVector2d * This,
            /* [in] */ IVector2d *v,
            /* [retval][out] */ Float64 *val);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IncrementBy )( 
            IVector2d * This,
            /* [in] */ IVector2d *v,
            /* [retval][out] */ IVector2d **val);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Increment )( 
            IVector2d * This,
            /* [in] */ IVector2d *v);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecrementBy )( 
            IVector2d * This,
            /* [in] */ IVector2d *v,
            /* [retval][out] */ IVector2d **val);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Decrement )( 
            IVector2d * This,
            /* [in] */ IVector2d *v);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IVector2d * This,
            /* [retval][out] */ IVector2d **ppClone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IVector2d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IVector2dVtbl;

    interface IVector2d
    {
        CONST_VTBL struct IVector2dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVector2d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVector2d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVector2d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVector2d_get_X(This,pVal)	\
    ( (This)->lpVtbl -> get_X(This,pVal) ) 

#define IVector2d_put_X(This,newVal)	\
    ( (This)->lpVtbl -> put_X(This,newVal) ) 

#define IVector2d_get_Y(This,pVal)	\
    ( (This)->lpVtbl -> get_Y(This,pVal) ) 

#define IVector2d_put_Y(This,newVal)	\
    ( (This)->lpVtbl -> put_Y(This,newVal) ) 

#define IVector2d_get_Direction(This,pVal)	\
    ( (This)->lpVtbl -> get_Direction(This,pVal) ) 

#define IVector2d_put_Direction(This,newVal)	\
    ( (This)->lpVtbl -> put_Direction(This,newVal) ) 

#define IVector2d_get_Magnitude(This,pVal)	\
    ( (This)->lpVtbl -> get_Magnitude(This,pVal) ) 

#define IVector2d_put_Magnitude(This,newVal)	\
    ( (This)->lpVtbl -> put_Magnitude(This,newVal) ) 

#define IVector2d_get_Size(This,pVal)	\
    ( (This)->lpVtbl -> get_Size(This,pVal) ) 

#define IVector2d_IsZero(This,pbResult)	\
    ( (This)->lpVtbl -> IsZero(This,pbResult) ) 

#define IVector2d_Normal(This,ppNormal)	\
    ( (This)->lpVtbl -> Normal(This,ppNormal) ) 

#define IVector2d_Normalize(This)	\
    ( (This)->lpVtbl -> Normalize(This) ) 

#define IVector2d_Offset(This,dx,dy)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy) ) 

#define IVector2d_OffsetEx(This,pSize)	\
    ( (This)->lpVtbl -> OffsetEx(This,pSize) ) 

#define IVector2d_Projection(This,pVector,pVal)	\
    ( (This)->lpVtbl -> Projection(This,pVector,pVal) ) 

#define IVector2d_Reflect(This)	\
    ( (This)->lpVtbl -> Reflect(This) ) 

#define IVector2d_Rotate(This,angle)	\
    ( (This)->lpVtbl -> Rotate(This,angle) ) 

#define IVector2d_Scale(This,factor)	\
    ( (This)->lpVtbl -> Scale(This,factor) ) 

#define IVector2d_Dot(This,v,val)	\
    ( (This)->lpVtbl -> Dot(This,v,val) ) 

#define IVector2d_AngleBetween(This,v,val)	\
    ( (This)->lpVtbl -> AngleBetween(This,v,val) ) 

#define IVector2d_IncrementBy(This,v,val)	\
    ( (This)->lpVtbl -> IncrementBy(This,v,val) ) 

#define IVector2d_Increment(This,v)	\
    ( (This)->lpVtbl -> Increment(This,v) ) 

#define IVector2d_DecrementBy(This,v,val)	\
    ( (This)->lpVtbl -> DecrementBy(This,v,val) ) 

#define IVector2d_Decrement(This,v)	\
    ( (This)->lpVtbl -> Decrement(This,v) ) 

#define IVector2d_Clone(This,ppClone)	\
    ( (This)->lpVtbl -> Clone(This,ppClone) ) 

#define IVector2d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVector2d_INTERFACE_DEFINED__ */


#ifndef __IEnumPoint2d_INTERFACE_DEFINED__
#define __IEnumPoint2d_INTERFACE_DEFINED__

/* interface IEnumPoint2d */
/* [unique][restricted][hidden][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumPoint2d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2DB720E8-B7F8-11d3-8A0B-006097C68A9C")
    IEnumPoint2d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPoint2d **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IPoint2d **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumPoint2dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPoint2d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPoint2d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPoint2d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPoint2d * This,
            /* [out] */ IEnumPoint2d **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPoint2d * This,
            /* [in] */ ULONG celt,
            /* [out] */ IPoint2d **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPoint2d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPoint2d * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumPoint2dVtbl;

    interface IEnumPoint2d
    {
        CONST_VTBL struct IEnumPoint2dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPoint2d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumPoint2d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumPoint2d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumPoint2d_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumPoint2d_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumPoint2d_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumPoint2d_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumPoint2d_INTERFACE_DEFINED__ */


#ifndef __IPoint2dCollection_INTERFACE_DEFINED__
#define __IPoint2dCollection_INTERFACE_DEFINED__

/* interface IPoint2dCollection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPoint2dCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B0D56FA3-C8D6-11d2-8CDF-C55C1CA84A34")
    IPoint2dCollection : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType Index,
            /* [retval][out] */ IPoint2d **pPoint) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IPoint2d *pPoint) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType Index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__Enum( 
            /* [retval][out] */ IEnumPoint2d **ppenum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ IPoint2d *pPoint) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPoint2dCollection **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OffsetEx( 
            /* [in] */ ISize2d *size) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveDuplicatePoints( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPoint2dCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint2dCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint2dCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint2dCollection * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPoint2dCollection * This,
            /* [in] */ CollectionIndexType Index,
            /* [retval][out] */ IPoint2d **pPoint);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IPoint2dCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPoint2dCollection * This,
            /* [in] */ IPoint2d *pPoint);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPoint2dCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IPoint2dCollection * This,
            /* [in] */ CollectionIndexType Index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IPoint2dCollection * This);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__Enum )( 
            IPoint2dCollection * This,
            /* [retval][out] */ IEnumPoint2d **ppenum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPoint2dCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            IPoint2dCollection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IPoint2dCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ IPoint2d *pPoint);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPoint2dCollection * This,
            /* [retval][out] */ IPoint2dCollection **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IPoint2dCollection * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffsetEx )( 
            IPoint2dCollection * This,
            /* [in] */ ISize2d *size);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveDuplicatePoints )( 
            IPoint2dCollection * This);
        
        END_INTERFACE
    } IPoint2dCollectionVtbl;

    interface IPoint2dCollection
    {
        CONST_VTBL struct IPoint2dCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint2dCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPoint2dCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPoint2dCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPoint2dCollection_get_Item(This,Index,pPoint)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pPoint) ) 

#define IPoint2dCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IPoint2dCollection_Add(This,pPoint)	\
    ( (This)->lpVtbl -> Add(This,pPoint) ) 

#define IPoint2dCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPoint2dCollection_Remove(This,Index)	\
    ( (This)->lpVtbl -> Remove(This,Index) ) 

#define IPoint2dCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IPoint2dCollection_get__Enum(This,ppenum)	\
    ( (This)->lpVtbl -> get__Enum(This,ppenum) ) 

#define IPoint2dCollection_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define IPoint2dCollection_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define IPoint2dCollection_Insert(This,index,pPoint)	\
    ( (This)->lpVtbl -> Insert(This,index,pPoint) ) 

#define IPoint2dCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IPoint2dCollection_Offset(This,dx,dy)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy) ) 

#define IPoint2dCollection_OffsetEx(This,size)	\
    ( (This)->lpVtbl -> OffsetEx(This,size) ) 

#define IPoint2dCollection_RemoveDuplicatePoints(This)	\
    ( (This)->lpVtbl -> RemoveDuplicatePoints(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPoint2dCollection_INTERFACE_DEFINED__ */


#ifndef __IPoint2dCollectionEvents_INTERFACE_DEFINED__
#define __IPoint2dCollectionEvents_INTERFACE_DEFINED__

/* interface IPoint2dCollectionEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPoint2dCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("06927385-F7D8-4398-A34B-FE7CDF8D7E40")
    IPoint2dCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointChanged( 
            /* [in] */ IPoint2d *Point2d) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointAdded( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPoint2d *Point2d) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointRemoved( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointsCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPoint2dCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint2dCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint2dCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint2dCollectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointChanged )( 
            IPoint2dCollectionEvents * This,
            /* [in] */ IPoint2d *Point2d);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointAdded )( 
            IPoint2dCollectionEvents * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPoint2d *Point2d);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointRemoved )( 
            IPoint2dCollectionEvents * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointsCleared )( 
            IPoint2dCollectionEvents * This);
        
        END_INTERFACE
    } IPoint2dCollectionEventsVtbl;

    interface IPoint2dCollectionEvents
    {
        CONST_VTBL struct IPoint2dCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint2dCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPoint2dCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPoint2dCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPoint2dCollectionEvents_OnPointChanged(This,Point2d)	\
    ( (This)->lpVtbl -> OnPointChanged(This,Point2d) ) 

#define IPoint2dCollectionEvents_OnPointAdded(This,idx,Point2d)	\
    ( (This)->lpVtbl -> OnPointAdded(This,idx,Point2d) ) 

#define IPoint2dCollectionEvents_OnPointRemoved(This,idx)	\
    ( (This)->lpVtbl -> OnPointRemoved(This,idx) ) 

#define IPoint2dCollectionEvents_OnPointsCleared(This)	\
    ( (This)->lpVtbl -> OnPointsCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPoint2dCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __ILineSegment2d_INTERFACE_DEFINED__
#define __ILineSegment2d_INTERFACE_DEFINED__

/* interface ILineSegment2d */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILineSegment2d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DB32B4E0-FCD6-11D2-8CDF-F5BC1C124434")
    ILineSegment2d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartPoint( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_StartPoint( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPoint( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_EndPoint( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ Float64 cx,
            /* [in] */ Float64 cy,
            /* [in] */ Float64 angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RotateEx( 
            /* [in] */ IPoint2d *pCenter,
            /* [in] */ Float64 angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OffsetEx( 
            /* [in] */ ISize2d *pSize) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset2( 
            /* [in] */ Float64 distance) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ThroughPoints( 
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILineSegment2d **ppClone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILineSegment2dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILineSegment2d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILineSegment2d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILineSegment2d * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPoint )( 
            ILineSegment2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StartPoint )( 
            ILineSegment2d * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPoint )( 
            ILineSegment2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_EndPoint )( 
            ILineSegment2d * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ILineSegment2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            ILineSegment2d * This,
            /* [in] */ Float64 cx,
            /* [in] */ Float64 cy,
            /* [in] */ Float64 angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RotateEx )( 
            ILineSegment2d * This,
            /* [in] */ IPoint2d *pCenter,
            /* [in] */ Float64 angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            ILineSegment2d * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffsetEx )( 
            ILineSegment2d * This,
            /* [in] */ ISize2d *pSize);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset2 )( 
            ILineSegment2d * This,
            /* [in] */ Float64 distance);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ThroughPoints )( 
            ILineSegment2d * This,
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILineSegment2d * This,
            /* [retval][out] */ ILineSegment2d **ppClone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ILineSegment2d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ILineSegment2dVtbl;

    interface ILineSegment2d
    {
        CONST_VTBL struct ILineSegment2dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILineSegment2d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILineSegment2d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILineSegment2d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILineSegment2d_get_StartPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_StartPoint(This,pVal) ) 

#define ILineSegment2d_putref_StartPoint(This,newVal)	\
    ( (This)->lpVtbl -> putref_StartPoint(This,newVal) ) 

#define ILineSegment2d_get_EndPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_EndPoint(This,pVal) ) 

#define ILineSegment2d_putref_EndPoint(This,newVal)	\
    ( (This)->lpVtbl -> putref_EndPoint(This,newVal) ) 

#define ILineSegment2d_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ILineSegment2d_Rotate(This,cx,cy,angle)	\
    ( (This)->lpVtbl -> Rotate(This,cx,cy,angle) ) 

#define ILineSegment2d_RotateEx(This,pCenter,angle)	\
    ( (This)->lpVtbl -> RotateEx(This,pCenter,angle) ) 

#define ILineSegment2d_Offset(This,dx,dy)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy) ) 

#define ILineSegment2d_OffsetEx(This,pSize)	\
    ( (This)->lpVtbl -> OffsetEx(This,pSize) ) 

#define ILineSegment2d_Offset2(This,distance)	\
    ( (This)->lpVtbl -> Offset2(This,distance) ) 

#define ILineSegment2d_ThroughPoints(This,p1,p2)	\
    ( (This)->lpVtbl -> ThroughPoints(This,p1,p2) ) 

#define ILineSegment2d_Clone(This,ppClone)	\
    ( (This)->lpVtbl -> Clone(This,ppClone) ) 

#define ILineSegment2d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILineSegment2d_INTERFACE_DEFINED__ */


#ifndef __ILineSegment2dEvents_INTERFACE_DEFINED__
#define __ILineSegment2dEvents_INTERFACE_DEFINED__

/* interface ILineSegment2dEvents */
/* [unique][helpstring][helpcontext][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILineSegment2dEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EBECEDED-AF2B-4f51-8A8B-815EA425319F")
    ILineSegment2dEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLineSegmentChanged( 
            ILineSegment2d *lineSegment) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILineSegment2dEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILineSegment2dEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILineSegment2dEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILineSegment2dEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLineSegmentChanged )( 
            ILineSegment2dEvents * This,
            ILineSegment2d *lineSegment);
        
        END_INTERFACE
    } ILineSegment2dEventsVtbl;

    interface ILineSegment2dEvents
    {
        CONST_VTBL struct ILineSegment2dEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILineSegment2dEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILineSegment2dEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILineSegment2dEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILineSegment2dEvents_OnLineSegmentChanged(This,lineSegment)	\
    ( (This)->lpVtbl -> OnLineSegmentChanged(This,lineSegment) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILineSegment2dEvents_INTERFACE_DEFINED__ */


#ifndef __ILine2d_INTERFACE_DEFINED__
#define __ILine2d_INTERFACE_DEFINED__

/* interface ILine2d */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILine2d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("54A873E0-FCE2-11D2-8CDF-B23210011634")
    ILine2d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetExplicit( 
            /* [in] */ IPoint2d *p,
            /* [in] */ IVector2d *d) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetExplicit( 
            /* [out] */ IPoint2d **p,
            /* [out] */ IVector2d **d) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetImplicit( 
            /* [in] */ Float64 c,
            /* [in] */ IVector2d *n) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetImplicit( 
            /* [out] */ Float64 *c,
            /* [out] */ IVector2d **n) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ThroughPoints( 
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ Float64 cx,
            /* [in] */ Float64 cy,
            /* [in] */ Float64 angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RotateEx( 
            /* [in] */ IPoint2d *pCenter,
            /* [in] */ Float64 angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILine2d **ppLine) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILine2dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILine2d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILine2d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILine2d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetExplicit )( 
            ILine2d * This,
            /* [in] */ IPoint2d *p,
            /* [in] */ IVector2d *d);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetExplicit )( 
            ILine2d * This,
            /* [out] */ IPoint2d **p,
            /* [out] */ IVector2d **d);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetImplicit )( 
            ILine2d * This,
            /* [in] */ Float64 c,
            /* [in] */ IVector2d *n);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetImplicit )( 
            ILine2d * This,
            /* [out] */ Float64 *c,
            /* [out] */ IVector2d **n);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ThroughPoints )( 
            ILine2d * This,
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            ILine2d * This,
            /* [in] */ Float64 offset);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            ILine2d * This,
            /* [in] */ Float64 cx,
            /* [in] */ Float64 cy,
            /* [in] */ Float64 angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RotateEx )( 
            ILine2d * This,
            /* [in] */ IPoint2d *pCenter,
            /* [in] */ Float64 angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            ILine2d * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILine2d * This,
            /* [retval][out] */ ILine2d **ppLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ILine2d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ILine2dVtbl;

    interface ILine2d
    {
        CONST_VTBL struct ILine2dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILine2d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILine2d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILine2d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILine2d_SetExplicit(This,p,d)	\
    ( (This)->lpVtbl -> SetExplicit(This,p,d) ) 

#define ILine2d_GetExplicit(This,p,d)	\
    ( (This)->lpVtbl -> GetExplicit(This,p,d) ) 

#define ILine2d_SetImplicit(This,c,n)	\
    ( (This)->lpVtbl -> SetImplicit(This,c,n) ) 

#define ILine2d_GetImplicit(This,c,n)	\
    ( (This)->lpVtbl -> GetImplicit(This,c,n) ) 

#define ILine2d_ThroughPoints(This,p1,p2)	\
    ( (This)->lpVtbl -> ThroughPoints(This,p1,p2) ) 

#define ILine2d_Offset(This,offset)	\
    ( (This)->lpVtbl -> Offset(This,offset) ) 

#define ILine2d_Rotate(This,cx,cy,angle)	\
    ( (This)->lpVtbl -> Rotate(This,cx,cy,angle) ) 

#define ILine2d_RotateEx(This,pCenter,angle)	\
    ( (This)->lpVtbl -> RotateEx(This,pCenter,angle) ) 

#define ILine2d_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define ILine2d_Clone(This,ppLine)	\
    ( (This)->lpVtbl -> Clone(This,ppLine) ) 

#define ILine2d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILine2d_INTERFACE_DEFINED__ */


#ifndef __IPoint3d_INTERFACE_DEFINED__
#define __IPoint3d_INTERFACE_DEFINED__

/* interface IPoint3d */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPoint3d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F37A660-03FE-11D3-8CDF-882D80988F34")
    IPoint3d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ Float64 *x) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X( 
            /* [in] */ Float64 x) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ Float64 *y) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y( 
            /* [in] */ Float64 y) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Z( 
            /* [retval][out] */ Float64 *z) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Z( 
            /* [in] */ Float64 z) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ Float64 x,
            /* [in] */ Float64 y,
            /* [in] */ Float64 z) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveEx( 
            /* [in] */ IPoint3d *to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy,
            /* [in] */ Float64 dz) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OffsetEx( 
            /* [in] */ ISize3d *size) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ Float64 cx,
            /* [in] */ Float64 cy,
            /* [in] */ Float64 cz,
            /* [in] */ IVector3d *vector,
            /* [in] */ Float64 angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RotateEx( 
            /* [in] */ IPoint3d *center,
            /* [in] */ IVector3d *vector,
            /* [in] */ Float64 angle) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SameLocation( 
            /* [in] */ IPoint3d *pOther) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Location( 
            /* [out] */ Float64 *pX,
            /* [out] */ Float64 *pY,
            /* [out] */ Float64 *pZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Distance( 
            /* [in] */ Float64 x,
            /* [in] */ Float64 y,
            /* [in] */ Float64 z,
            /* [retval][out] */ Float64 *pDistance) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DistanceEx( 
            /* [in] */ IPoint3d *pOther,
            /* [retval][out] */ Float64 *pDistance) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPoint3d **ppPoint) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPoint3dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint3d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint3d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint3d * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IPoint3d * This,
            /* [retval][out] */ Float64 *x);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IPoint3d * This,
            /* [in] */ Float64 x);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IPoint3d * This,
            /* [retval][out] */ Float64 *y);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IPoint3d * This,
            /* [in] */ Float64 y);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Z )( 
            IPoint3d * This,
            /* [retval][out] */ Float64 *z);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Z )( 
            IPoint3d * This,
            /* [in] */ Float64 z);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IPoint3d * This,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y,
            /* [in] */ Float64 z);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveEx )( 
            IPoint3d * This,
            /* [in] */ IPoint3d *to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IPoint3d * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy,
            /* [in] */ Float64 dz);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffsetEx )( 
            IPoint3d * This,
            /* [in] */ ISize3d *size);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            IPoint3d * This,
            /* [in] */ Float64 cx,
            /* [in] */ Float64 cy,
            /* [in] */ Float64 cz,
            /* [in] */ IVector3d *vector,
            /* [in] */ Float64 angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RotateEx )( 
            IPoint3d * This,
            /* [in] */ IPoint3d *center,
            /* [in] */ IVector3d *vector,
            /* [in] */ Float64 angle);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPoint3d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SameLocation )( 
            IPoint3d * This,
            /* [in] */ IPoint3d *pOther);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Location )( 
            IPoint3d * This,
            /* [out] */ Float64 *pX,
            /* [out] */ Float64 *pY,
            /* [out] */ Float64 *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Distance )( 
            IPoint3d * This,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y,
            /* [in] */ Float64 z,
            /* [retval][out] */ Float64 *pDistance);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DistanceEx )( 
            IPoint3d * This,
            /* [in] */ IPoint3d *pOther,
            /* [retval][out] */ Float64 *pDistance);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPoint3d * This,
            /* [retval][out] */ IPoint3d **ppPoint);
        
        END_INTERFACE
    } IPoint3dVtbl;

    interface IPoint3d
    {
        CONST_VTBL struct IPoint3dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint3d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPoint3d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPoint3d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPoint3d_get_X(This,x)	\
    ( (This)->lpVtbl -> get_X(This,x) ) 

#define IPoint3d_put_X(This,x)	\
    ( (This)->lpVtbl -> put_X(This,x) ) 

#define IPoint3d_get_Y(This,y)	\
    ( (This)->lpVtbl -> get_Y(This,y) ) 

#define IPoint3d_put_Y(This,y)	\
    ( (This)->lpVtbl -> put_Y(This,y) ) 

#define IPoint3d_get_Z(This,z)	\
    ( (This)->lpVtbl -> get_Z(This,z) ) 

#define IPoint3d_put_Z(This,z)	\
    ( (This)->lpVtbl -> put_Z(This,z) ) 

#define IPoint3d_Move(This,x,y,z)	\
    ( (This)->lpVtbl -> Move(This,x,y,z) ) 

#define IPoint3d_MoveEx(This,to)	\
    ( (This)->lpVtbl -> MoveEx(This,to) ) 

#define IPoint3d_Offset(This,dx,dy,dz)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy,dz) ) 

#define IPoint3d_OffsetEx(This,size)	\
    ( (This)->lpVtbl -> OffsetEx(This,size) ) 

#define IPoint3d_Rotate(This,cx,cy,cz,vector,angle)	\
    ( (This)->lpVtbl -> Rotate(This,cx,cy,cz,vector,angle) ) 

#define IPoint3d_RotateEx(This,center,vector,angle)	\
    ( (This)->lpVtbl -> RotateEx(This,center,vector,angle) ) 

#define IPoint3d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define IPoint3d_SameLocation(This,pOther)	\
    ( (This)->lpVtbl -> SameLocation(This,pOther) ) 

#define IPoint3d_Location(This,pX,pY,pZ)	\
    ( (This)->lpVtbl -> Location(This,pX,pY,pZ) ) 

#define IPoint3d_Distance(This,x,y,z,pDistance)	\
    ( (This)->lpVtbl -> Distance(This,x,y,z,pDistance) ) 

#define IPoint3d_DistanceEx(This,pOther,pDistance)	\
    ( (This)->lpVtbl -> DistanceEx(This,pOther,pDistance) ) 

#define IPoint3d_Clone(This,ppPoint)	\
    ( (This)->lpVtbl -> Clone(This,ppPoint) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPoint3d_INTERFACE_DEFINED__ */


#ifndef __IPoint3dEvents_INTERFACE_DEFINED__
#define __IPoint3dEvents_INTERFACE_DEFINED__

/* interface IPoint3dEvents */
/* [unique][helpstring][helpcontext][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IPoint3dEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C001AE86-7A31-434e-8649-3096457FE412")
    IPoint3dEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointChanged( 
            IPoint3d *point) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPoint3dEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint3dEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint3dEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint3dEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointChanged )( 
            IPoint3dEvents * This,
            IPoint3d *point);
        
        END_INTERFACE
    } IPoint3dEventsVtbl;

    interface IPoint3dEvents
    {
        CONST_VTBL struct IPoint3dEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint3dEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPoint3dEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPoint3dEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPoint3dEvents_OnPointChanged(This,point)	\
    ( (This)->lpVtbl -> OnPointChanged(This,point) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPoint3dEvents_INTERFACE_DEFINED__ */


#ifndef __ILineSegment3d_INTERFACE_DEFINED__
#define __ILineSegment3d_INTERFACE_DEFINED__

/* interface ILineSegment3d */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILineSegment3d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0356DD54-DC34-47b2-B324-3C6A20930301")
    ILineSegment3d : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartPoint( 
            /* [retval][out] */ IPoint3d **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_StartPoint( 
            /* [in] */ IPoint3d *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPoint( 
            /* [retval][out] */ IPoint3d **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_EndPoint( 
            /* [in] */ IPoint3d *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ThroughPoints( 
            /* [in] */ IPoint3d *p1,
            /* [in] */ IPoint3d *p2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy,
            /* [in] */ Float64 dz) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OffsetEx( 
            /* [in] */ ISize3d *pSize) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILineSegment3d **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILineSegment3dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILineSegment3d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILineSegment3d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILineSegment3d * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPoint )( 
            ILineSegment3d * This,
            /* [retval][out] */ IPoint3d **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StartPoint )( 
            ILineSegment3d * This,
            /* [in] */ IPoint3d *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPoint )( 
            ILineSegment3d * This,
            /* [retval][out] */ IPoint3d **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_EndPoint )( 
            ILineSegment3d * This,
            /* [in] */ IPoint3d *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ILineSegment3d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ThroughPoints )( 
            ILineSegment3d * This,
            /* [in] */ IPoint3d *p1,
            /* [in] */ IPoint3d *p2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            ILineSegment3d * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy,
            /* [in] */ Float64 dz);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffsetEx )( 
            ILineSegment3d * This,
            /* [in] */ ISize3d *pSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILineSegment3d * This,
            /* [retval][out] */ ILineSegment3d **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ILineSegment3d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ILineSegment3dVtbl;

    interface ILineSegment3d
    {
        CONST_VTBL struct ILineSegment3dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILineSegment3d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILineSegment3d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILineSegment3d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILineSegment3d_get_StartPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_StartPoint(This,pVal) ) 

#define ILineSegment3d_putref_StartPoint(This,newVal)	\
    ( (This)->lpVtbl -> putref_StartPoint(This,newVal) ) 

#define ILineSegment3d_get_EndPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_EndPoint(This,pVal) ) 

#define ILineSegment3d_putref_EndPoint(This,newVal)	\
    ( (This)->lpVtbl -> putref_EndPoint(This,newVal) ) 

#define ILineSegment3d_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ILineSegment3d_ThroughPoints(This,p1,p2)	\
    ( (This)->lpVtbl -> ThroughPoints(This,p1,p2) ) 

#define ILineSegment3d_Offset(This,dx,dy,dz)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy,dz) ) 

#define ILineSegment3d_OffsetEx(This,pSize)	\
    ( (This)->lpVtbl -> OffsetEx(This,pSize) ) 

#define ILineSegment3d_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ILineSegment3d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILineSegment3d_INTERFACE_DEFINED__ */


#ifndef __ILineSegment3dEvents_INTERFACE_DEFINED__
#define __ILineSegment3dEvents_INTERFACE_DEFINED__

/* interface ILineSegment3dEvents */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILineSegment3dEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("708930E0-84C3-4f3e-A8FD-524E80D50918")
    ILineSegment3dEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnLineSegmentChanged( 
            ILineSegment3d *lineSegment) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILineSegment3dEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILineSegment3dEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILineSegment3dEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILineSegment3dEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLineSegmentChanged )( 
            ILineSegment3dEvents * This,
            ILineSegment3d *lineSegment);
        
        END_INTERFACE
    } ILineSegment3dEventsVtbl;

    interface ILineSegment3dEvents
    {
        CONST_VTBL struct ILineSegment3dEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILineSegment3dEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILineSegment3dEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILineSegment3dEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILineSegment3dEvents_OnLineSegmentChanged(This,lineSegment)	\
    ( (This)->lpVtbl -> OnLineSegmentChanged(This,lineSegment) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILineSegment3dEvents_INTERFACE_DEFINED__ */


#ifndef __IPlane3d_INTERFACE_DEFINED__
#define __IPlane3d_INTERFACE_DEFINED__

/* interface IPlane3d */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPlane3d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F97D8403-1871-11D3-8CDF-925649DD1F63")
    IPlane3d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ThroughPoints( 
            /* [in] */ IPoint3d *p1,
            /* [in] */ IPoint3d *p2,
            /* [in] */ IPoint3d *p3) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ThroughLineEx( 
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint3d *pPnt) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ThroughAltitude( 
            /* [in] */ Float64 altitude) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetX( 
            /* [in] */ Float64 y,
            /* [in] */ Float64 z,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetY( 
            /* [in] */ Float64 x,
            /* [in] */ Float64 z,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetZ( 
            /* [in] */ Float64 x,
            /* [in] */ Float64 y,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LineSegmentIntersect( 
            /* [in] */ ILineSegment3d *pLineSegment,
            /* [retval][out] */ IPoint3d **ppPoint) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SortestDistance( 
            IPoint3d *point,
            Float64 *pDistance) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PointOnPlaneNearestOrigin( 
            /* [retval][out] */ IPoint3d **ppPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPlane3d **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPlane3dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPlane3d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPlane3d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPlane3d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ThroughPoints )( 
            IPlane3d * This,
            /* [in] */ IPoint3d *p1,
            /* [in] */ IPoint3d *p2,
            /* [in] */ IPoint3d *p3);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ThroughLineEx )( 
            IPlane3d * This,
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint3d *pPnt);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ThroughAltitude )( 
            IPlane3d * This,
            /* [in] */ Float64 altitude);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetX )( 
            IPlane3d * This,
            /* [in] */ Float64 y,
            /* [in] */ Float64 z,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetY )( 
            IPlane3d * This,
            /* [in] */ Float64 x,
            /* [in] */ Float64 z,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetZ )( 
            IPlane3d * This,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LineSegmentIntersect )( 
            IPlane3d * This,
            /* [in] */ ILineSegment3d *pLineSegment,
            /* [retval][out] */ IPoint3d **ppPoint);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SortestDistance )( 
            IPlane3d * This,
            IPoint3d *point,
            Float64 *pDistance);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnPlaneNearestOrigin )( 
            IPlane3d * This,
            /* [retval][out] */ IPoint3d **ppPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPlane3d * This,
            /* [retval][out] */ IPlane3d **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPlane3d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IPlane3dVtbl;

    interface IPlane3d
    {
        CONST_VTBL struct IPlane3dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPlane3d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPlane3d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPlane3d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPlane3d_ThroughPoints(This,p1,p2,p3)	\
    ( (This)->lpVtbl -> ThroughPoints(This,p1,p2,p3) ) 

#define IPlane3d_ThroughLineEx(This,pLine,pPnt)	\
    ( (This)->lpVtbl -> ThroughLineEx(This,pLine,pPnt) ) 

#define IPlane3d_ThroughAltitude(This,altitude)	\
    ( (This)->lpVtbl -> ThroughAltitude(This,altitude) ) 

#define IPlane3d_GetX(This,y,z,pVal)	\
    ( (This)->lpVtbl -> GetX(This,y,z,pVal) ) 

#define IPlane3d_GetY(This,x,z,pVal)	\
    ( (This)->lpVtbl -> GetY(This,x,z,pVal) ) 

#define IPlane3d_GetZ(This,x,y,pVal)	\
    ( (This)->lpVtbl -> GetZ(This,x,y,pVal) ) 

#define IPlane3d_LineSegmentIntersect(This,pLineSegment,ppPoint)	\
    ( (This)->lpVtbl -> LineSegmentIntersect(This,pLineSegment,ppPoint) ) 

#define IPlane3d_SortestDistance(This,point,pDistance)	\
    ( (This)->lpVtbl -> SortestDistance(This,point,pDistance) ) 

#define IPlane3d_PointOnPlaneNearestOrigin(This,ppPoint)	\
    ( (This)->lpVtbl -> PointOnPlaneNearestOrigin(This,ppPoint) ) 

#define IPlane3d_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IPlane3d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPlane3d_INTERFACE_DEFINED__ */


#ifndef __IEnumPoint3d_INTERFACE_DEFINED__
#define __IEnumPoint3d_INTERFACE_DEFINED__

/* interface IEnumPoint3d */
/* [unique][restricted][hidden][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumPoint3d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2DB720E9-B7F8-11d3-8A0B-006097C68A9C")
    IEnumPoint3d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IPoint3d **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPoint3d **ppenum) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumPoint3dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPoint3d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPoint3d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPoint3d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPoint3d * This,
            /* [in] */ ULONG celt,
            /* [out] */ IPoint3d **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPoint3d * This,
            /* [in] */ ULONG celt);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPoint3d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPoint3d * This,
            /* [out] */ IEnumPoint3d **ppenum);
        
        END_INTERFACE
    } IEnumPoint3dVtbl;

    interface IEnumPoint3d
    {
        CONST_VTBL struct IEnumPoint3dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPoint3d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumPoint3d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumPoint3d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumPoint3d_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumPoint3d_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumPoint3d_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumPoint3d_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumPoint3d_INTERFACE_DEFINED__ */


#ifndef __IPoint3dCollection_INTERFACE_DEFINED__
#define __IPoint3dCollection_INTERFACE_DEFINED__

/* interface IPoint3dCollection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPoint3dCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("818E5100-1942-11D3-8CDF-DCD8D8F12565")
    IPoint3dCollection : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IPoint3d *pPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType Index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__Enum( 
            /* [retval][out] */ IEnumPoint3d **ppenum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType Index,
            /* [retval][out] */ IPoint3d **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ IPoint3d *pPoint) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPoint3dCollection **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy,
            /* [in] */ Float64 dz) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OffsetEx( 
            /* [in] */ ISize3d *size) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveDuplicatePoints( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPoint3dCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint3dCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint3dCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint3dCollection * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPoint3dCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPoint3dCollection * This,
            /* [in] */ IPoint3d *pPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IPoint3dCollection * This,
            /* [in] */ CollectionIndexType Index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IPoint3dCollection * This);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__Enum )( 
            IPoint3dCollection * This,
            /* [retval][out] */ IEnumPoint3d **ppenum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IPoint3dCollection * This,
            /* [retval][out] */ LPUNKNOWN *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPoint3dCollection * This,
            /* [in] */ CollectionIndexType Index,
            /* [retval][out] */ IPoint3d **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPoint3dCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            IPoint3dCollection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IPoint3dCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ IPoint3d *pPoint);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPoint3dCollection * This,
            /* [retval][out] */ IPoint3dCollection **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IPoint3dCollection * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy,
            /* [in] */ Float64 dz);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffsetEx )( 
            IPoint3dCollection * This,
            /* [in] */ ISize3d *size);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveDuplicatePoints )( 
            IPoint3dCollection * This);
        
        END_INTERFACE
    } IPoint3dCollectionVtbl;

    interface IPoint3dCollection
    {
        CONST_VTBL struct IPoint3dCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint3dCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPoint3dCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPoint3dCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPoint3dCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPoint3dCollection_Add(This,pPoint)	\
    ( (This)->lpVtbl -> Add(This,pPoint) ) 

#define IPoint3dCollection_Remove(This,Index)	\
    ( (This)->lpVtbl -> Remove(This,Index) ) 

#define IPoint3dCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IPoint3dCollection_get__Enum(This,ppenum)	\
    ( (This)->lpVtbl -> get__Enum(This,ppenum) ) 

#define IPoint3dCollection_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define IPoint3dCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IPoint3dCollection_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define IPoint3dCollection_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define IPoint3dCollection_Insert(This,index,pPoint)	\
    ( (This)->lpVtbl -> Insert(This,index,pPoint) ) 

#define IPoint3dCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IPoint3dCollection_Offset(This,dx,dy,dz)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy,dz) ) 

#define IPoint3dCollection_OffsetEx(This,size)	\
    ( (This)->lpVtbl -> OffsetEx(This,size) ) 

#define IPoint3dCollection_RemoveDuplicatePoints(This)	\
    ( (This)->lpVtbl -> RemoveDuplicatePoints(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPoint3dCollection_INTERFACE_DEFINED__ */


#ifndef __IPoint3dCollectionEvents_INTERFACE_DEFINED__
#define __IPoint3dCollectionEvents_INTERFACE_DEFINED__

/* interface IPoint3dCollectionEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPoint3dCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C895D8CE-7D4D-417b-838D-C55379830D21")
    IPoint3dCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointChanged( 
            /* [in] */ IPoint3d *Point3d) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointAdded( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPoint3d *Point3d) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointRemoved( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointsCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPoint3dCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint3dCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint3dCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint3dCollectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointChanged )( 
            IPoint3dCollectionEvents * This,
            /* [in] */ IPoint3d *Point3d);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointAdded )( 
            IPoint3dCollectionEvents * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPoint3d *Point3d);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointRemoved )( 
            IPoint3dCollectionEvents * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointsCleared )( 
            IPoint3dCollectionEvents * This);
        
        END_INTERFACE
    } IPoint3dCollectionEventsVtbl;

    interface IPoint3dCollectionEvents
    {
        CONST_VTBL struct IPoint3dCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint3dCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPoint3dCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPoint3dCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPoint3dCollectionEvents_OnPointChanged(This,Point3d)	\
    ( (This)->lpVtbl -> OnPointChanged(This,Point3d) ) 

#define IPoint3dCollectionEvents_OnPointAdded(This,idx,Point3d)	\
    ( (This)->lpVtbl -> OnPointAdded(This,idx,Point3d) ) 

#define IPoint3dCollectionEvents_OnPointRemoved(This,idx)	\
    ( (This)->lpVtbl -> OnPointRemoved(This,idx) ) 

#define IPoint3dCollectionEvents_OnPointsCleared(This)	\
    ( (This)->lpVtbl -> OnPointsCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPoint3dCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __IShapeProperties_INTERFACE_DEFINED__
#define __IShapeProperties_INTERFACE_DEFINED__

/* interface IShapeProperties */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IShapeProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("66172CA4-FF5A-11D2-8CDF-F43C3928A334")
    IShapeProperties : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Area( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Area( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Centroid( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Centroid( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_I11( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_I22( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_I12Max( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_I12Min( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ixx( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ixx( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Iyy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Iyy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ixy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ixy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Xleft( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Xleft( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Xright( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Xright( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ytop( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ytop( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ybottom( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ybottom( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Origin( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Origin( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CoordinateSystem( 
            /* [retval][out] */ CoordinateSystemType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CoordinateSystem( 
            /* [in] */ CoordinateSystemType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PrincipleDirection( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddProperties( 
            /* [in] */ IShapeProperties *props) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IShapePropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShapeProperties * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShapeProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShapeProperties * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Area )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Area )( 
            IShapeProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Centroid )( 
            IShapeProperties * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Centroid )( 
            IShapeProperties * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_I11 )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_I22 )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_I12Max )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_I12Min )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ixx )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ixx )( 
            IShapeProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Iyy )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Iyy )( 
            IShapeProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ixy )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ixy )( 
            IShapeProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Xleft )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Xleft )( 
            IShapeProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Xright )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Xright )( 
            IShapeProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ytop )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ytop )( 
            IShapeProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ybottom )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ybottom )( 
            IShapeProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Origin )( 
            IShapeProperties * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Origin )( 
            IShapeProperties * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IShapeProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CoordinateSystem )( 
            IShapeProperties * This,
            /* [retval][out] */ CoordinateSystemType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CoordinateSystem )( 
            IShapeProperties * This,
            /* [in] */ CoordinateSystemType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrincipleDirection )( 
            IShapeProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddProperties )( 
            IShapeProperties * This,
            /* [in] */ IShapeProperties *props);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IShapeProperties * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IShapePropertiesVtbl;

    interface IShapeProperties
    {
        CONST_VTBL struct IShapePropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShapeProperties_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShapeProperties_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShapeProperties_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShapeProperties_get_Area(This,pVal)	\
    ( (This)->lpVtbl -> get_Area(This,pVal) ) 

#define IShapeProperties_put_Area(This,newVal)	\
    ( (This)->lpVtbl -> put_Area(This,newVal) ) 

#define IShapeProperties_get_Centroid(This,pVal)	\
    ( (This)->lpVtbl -> get_Centroid(This,pVal) ) 

#define IShapeProperties_put_Centroid(This,newVal)	\
    ( (This)->lpVtbl -> put_Centroid(This,newVal) ) 

#define IShapeProperties_get_I11(This,pVal)	\
    ( (This)->lpVtbl -> get_I11(This,pVal) ) 

#define IShapeProperties_get_I22(This,pVal)	\
    ( (This)->lpVtbl -> get_I22(This,pVal) ) 

#define IShapeProperties_get_I12Max(This,pVal)	\
    ( (This)->lpVtbl -> get_I12Max(This,pVal) ) 

#define IShapeProperties_get_I12Min(This,pVal)	\
    ( (This)->lpVtbl -> get_I12Min(This,pVal) ) 

#define IShapeProperties_get_Ixx(This,pVal)	\
    ( (This)->lpVtbl -> get_Ixx(This,pVal) ) 

#define IShapeProperties_put_Ixx(This,newVal)	\
    ( (This)->lpVtbl -> put_Ixx(This,newVal) ) 

#define IShapeProperties_get_Iyy(This,pVal)	\
    ( (This)->lpVtbl -> get_Iyy(This,pVal) ) 

#define IShapeProperties_put_Iyy(This,newVal)	\
    ( (This)->lpVtbl -> put_Iyy(This,newVal) ) 

#define IShapeProperties_get_Ixy(This,pVal)	\
    ( (This)->lpVtbl -> get_Ixy(This,pVal) ) 

#define IShapeProperties_put_Ixy(This,newVal)	\
    ( (This)->lpVtbl -> put_Ixy(This,newVal) ) 

#define IShapeProperties_get_Xleft(This,pVal)	\
    ( (This)->lpVtbl -> get_Xleft(This,pVal) ) 

#define IShapeProperties_put_Xleft(This,newVal)	\
    ( (This)->lpVtbl -> put_Xleft(This,newVal) ) 

#define IShapeProperties_get_Xright(This,pVal)	\
    ( (This)->lpVtbl -> get_Xright(This,pVal) ) 

#define IShapeProperties_put_Xright(This,newVal)	\
    ( (This)->lpVtbl -> put_Xright(This,newVal) ) 

#define IShapeProperties_get_Ytop(This,pVal)	\
    ( (This)->lpVtbl -> get_Ytop(This,pVal) ) 

#define IShapeProperties_put_Ytop(This,newVal)	\
    ( (This)->lpVtbl -> put_Ytop(This,newVal) ) 

#define IShapeProperties_get_Ybottom(This,pVal)	\
    ( (This)->lpVtbl -> get_Ybottom(This,pVal) ) 

#define IShapeProperties_put_Ybottom(This,newVal)	\
    ( (This)->lpVtbl -> put_Ybottom(This,newVal) ) 

#define IShapeProperties_get_Origin(This,pVal)	\
    ( (This)->lpVtbl -> get_Origin(This,pVal) ) 

#define IShapeProperties_put_Origin(This,newVal)	\
    ( (This)->lpVtbl -> put_Origin(This,newVal) ) 

#define IShapeProperties_get_Orientation(This,pVal)	\
    ( (This)->lpVtbl -> get_Orientation(This,pVal) ) 

#define IShapeProperties_put_Orientation(This,newVal)	\
    ( (This)->lpVtbl -> put_Orientation(This,newVal) ) 

#define IShapeProperties_get_CoordinateSystem(This,pVal)	\
    ( (This)->lpVtbl -> get_CoordinateSystem(This,pVal) ) 

#define IShapeProperties_put_CoordinateSystem(This,newVal)	\
    ( (This)->lpVtbl -> put_CoordinateSystem(This,newVal) ) 

#define IShapeProperties_get_PrincipleDirection(This,pVal)	\
    ( (This)->lpVtbl -> get_PrincipleDirection(This,pVal) ) 

#define IShapeProperties_AddProperties(This,props)	\
    ( (This)->lpVtbl -> AddProperties(This,props) ) 

#define IShapeProperties_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IShapeProperties_INTERFACE_DEFINED__ */


#ifndef __IShape_INTERFACE_DEFINED__
#define __IShape_INTERFACE_DEFINED__

/* interface IShape */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IShape;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8A8FF0A0-0002-11d3-8CDF-F43C3928A334")
    IShape : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeProperties( 
            /* [retval][out] */ IShapeProperties **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BoundingBox( 
            /* [retval][out] */ IRect2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PolyPoints( 
            /* [retval][out] */ IPoint2dCollection **ppPolyPoints) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointInShape( 
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IShape **pClone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ClipWithLine( 
            /* [in] */ ILine2d *pLine,
            /* [retval][out] */ IShape **pShape) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ClipIn( 
            /* [in] */ IRect2d *pRect,
            /* [retval][out] */ IShape **pShape) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Perimeter( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FurthestDistance( 
            /* [in] */ ILine2d *line,
            /* [retval][out] */ Float64 *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShape * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShape * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShape * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeProperties )( 
            IShape * This,
            /* [retval][out] */ IShapeProperties **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BoundingBox )( 
            IShape * This,
            /* [retval][out] */ IRect2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PolyPoints )( 
            IShape * This,
            /* [retval][out] */ IPoint2dCollection **ppPolyPoints);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointInShape )( 
            IShape * This,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IShape * This,
            /* [retval][out] */ IShape **pClone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClipWithLine )( 
            IShape * This,
            /* [in] */ ILine2d *pLine,
            /* [retval][out] */ IShape **pShape);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClipIn )( 
            IShape * This,
            /* [in] */ IRect2d *pRect,
            /* [retval][out] */ IShape **pShape);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Perimeter )( 
            IShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FurthestDistance )( 
            IShape * This,
            /* [in] */ ILine2d *line,
            /* [retval][out] */ Float64 *pVal);
        
        END_INTERFACE
    } IShapeVtbl;

    interface IShape
    {
        CONST_VTBL struct IShapeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShape_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShape_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShape_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShape_get_ShapeProperties(This,pVal)	\
    ( (This)->lpVtbl -> get_ShapeProperties(This,pVal) ) 

#define IShape_get_BoundingBox(This,pVal)	\
    ( (This)->lpVtbl -> get_BoundingBox(This,pVal) ) 

#define IShape_get_PolyPoints(This,ppPolyPoints)	\
    ( (This)->lpVtbl -> get_PolyPoints(This,ppPolyPoints) ) 

#define IShape_PointInShape(This,pPoint,pbResult)	\
    ( (This)->lpVtbl -> PointInShape(This,pPoint,pbResult) ) 

#define IShape_Clone(This,pClone)	\
    ( (This)->lpVtbl -> Clone(This,pClone) ) 

#define IShape_ClipWithLine(This,pLine,pShape)	\
    ( (This)->lpVtbl -> ClipWithLine(This,pLine,pShape) ) 

#define IShape_ClipIn(This,pRect,pShape)	\
    ( (This)->lpVtbl -> ClipIn(This,pRect,pShape) ) 

#define IShape_get_Perimeter(This,pVal)	\
    ( (This)->lpVtbl -> get_Perimeter(This,pVal) ) 

#define IShape_FurthestDistance(This,line,pVal)	\
    ( (This)->lpVtbl -> FurthestDistance(This,line,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IShape_INTERFACE_DEFINED__ */


#ifndef __IEnumShape_INTERFACE_DEFINED__
#define __IEnumShape_INTERFACE_DEFINED__

/* interface IEnumShape */
/* [unique][restricted][hidden][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumShape;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A9E6E20-B982-11d4-8B56-006097C68A9C")
    IEnumShape : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumShape **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IShape **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumShape * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumShape * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumShape * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumShape * This,
            /* [out] */ IEnumShape **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumShape * This,
            /* [in] */ ULONG celt,
            /* [out] */ IShape **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumShape * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumShape * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumShapeVtbl;

    interface IEnumShape
    {
        CONST_VTBL struct IEnumShapeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumShape_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumShape_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumShape_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumShape_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumShape_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumShape_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumShape_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumShape_INTERFACE_DEFINED__ */


#ifndef __IShapeCollection_INTERFACE_DEFINED__
#define __IShapeCollection_INTERFACE_DEFINED__

/* interface IShapeCollection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IShapeCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A9E6E21-B982-11d4-8B56-006097C68A9C")
    IShapeCollection : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType Index,
            /* [retval][out] */ IShape **shape) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IShape *shape) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType Index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeProperties( 
            /* [retval][out] */ IShapeProperties **props) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__Enum( 
            /* [retval][out] */ IEnumShape **ppenum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IShapeCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShapeCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShapeCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShapeCollection * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IShapeCollection * This,
            /* [in] */ CollectionIndexType Index,
            /* [retval][out] */ IShape **shape);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IShapeCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IShapeCollection * This,
            /* [in] */ IShape *shape);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IShapeCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IShapeCollection * This,
            /* [in] */ CollectionIndexType Index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IShapeCollection * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeProperties )( 
            IShapeCollection * This,
            /* [retval][out] */ IShapeProperties **props);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__Enum )( 
            IShapeCollection * This,
            /* [retval][out] */ IEnumShape **ppenum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IShapeCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IShapeCollectionVtbl;

    interface IShapeCollection
    {
        CONST_VTBL struct IShapeCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShapeCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShapeCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShapeCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShapeCollection_get_Item(This,Index,shape)	\
    ( (This)->lpVtbl -> get_Item(This,Index,shape) ) 

#define IShapeCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IShapeCollection_Add(This,shape)	\
    ( (This)->lpVtbl -> Add(This,shape) ) 

#define IShapeCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IShapeCollection_Remove(This,Index)	\
    ( (This)->lpVtbl -> Remove(This,Index) ) 

#define IShapeCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IShapeCollection_get_ShapeProperties(This,props)	\
    ( (This)->lpVtbl -> get_ShapeProperties(This,props) ) 

#define IShapeCollection_get__Enum(This,ppenum)	\
    ( (This)->lpVtbl -> get__Enum(This,ppenum) ) 

#define IShapeCollection_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IShapeCollection_INTERFACE_DEFINED__ */


#ifndef __IXYPosition_INTERFACE_DEFINED__
#define __IXYPosition_INTERFACE_DEFINED__

/* interface IXYPosition */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IXYPosition;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C2EBFAA0-0013-11d3-8CDF-8BF0A4AD5B35")
    IXYPosition : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OffsetEx( 
            /* [in] */ ISize2d *pSize) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LocatorPoint( 
            /* [in] */ LocatorPointType lp,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LocatorPoint( 
            /* [in] */ LocatorPointType lp,
            /* [in] */ IPoint2d *point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveEx( 
            /* [in] */ IPoint2d *pFrom,
            /* [in] */ IPoint2d *pTo) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RotateEx( 
            /* [in] */ IPoint2d *pPoint,
            /* [in] */ Float64 angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ Float64 cx,
            /* [in] */ Float64 cy,
            /* [in] */ Float64 angle) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IXYPositionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXYPosition * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXYPosition * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXYPosition * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IXYPosition * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OffsetEx )( 
            IXYPosition * This,
            /* [in] */ ISize2d *pSize);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocatorPoint )( 
            IXYPosition * This,
            /* [in] */ LocatorPointType lp,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocatorPoint )( 
            IXYPosition * This,
            /* [in] */ LocatorPointType lp,
            /* [in] */ IPoint2d *point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveEx )( 
            IXYPosition * This,
            /* [in] */ IPoint2d *pFrom,
            /* [in] */ IPoint2d *pTo);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RotateEx )( 
            IXYPosition * This,
            /* [in] */ IPoint2d *pPoint,
            /* [in] */ Float64 angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            IXYPosition * This,
            /* [in] */ Float64 cx,
            /* [in] */ Float64 cy,
            /* [in] */ Float64 angle);
        
        END_INTERFACE
    } IXYPositionVtbl;

    interface IXYPosition
    {
        CONST_VTBL struct IXYPositionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXYPosition_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IXYPosition_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IXYPosition_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IXYPosition_Offset(This,dx,dy)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy) ) 

#define IXYPosition_OffsetEx(This,pSize)	\
    ( (This)->lpVtbl -> OffsetEx(This,pSize) ) 

#define IXYPosition_get_LocatorPoint(This,lp,point)	\
    ( (This)->lpVtbl -> get_LocatorPoint(This,lp,point) ) 

#define IXYPosition_put_LocatorPoint(This,lp,point)	\
    ( (This)->lpVtbl -> put_LocatorPoint(This,lp,point) ) 

#define IXYPosition_MoveEx(This,pFrom,pTo)	\
    ( (This)->lpVtbl -> MoveEx(This,pFrom,pTo) ) 

#define IXYPosition_RotateEx(This,pPoint,angle)	\
    ( (This)->lpVtbl -> RotateEx(This,pPoint,angle) ) 

#define IXYPosition_Rotate(This,cx,cy,angle)	\
    ( (This)->lpVtbl -> Rotate(This,cx,cy,angle) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IXYPosition_INTERFACE_DEFINED__ */


#ifndef __IGenericShape_INTERFACE_DEFINED__
#define __IGenericShape_INTERFACE_DEFINED__

/* interface IGenericShape */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGenericShape;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("06762F74-9BD3-4f96-B2F4-946D64F9C37D")
    IGenericShape : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Area( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Area( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Perimeter( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Centroid( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Centroid( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Xleft( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Xleft( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Xright( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Xright( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ytop( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ytop( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ybottom( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ybottom( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ixx( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ixx( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Iyy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Iyy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ixy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ixy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGenericShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGenericShape * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGenericShape * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGenericShape * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Area )( 
            IGenericShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Area )( 
            IGenericShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Perimeter )( 
            IGenericShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Centroid )( 
            IGenericShape * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Centroid )( 
            IGenericShape * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Xleft )( 
            IGenericShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Xleft )( 
            IGenericShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Xright )( 
            IGenericShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Xright )( 
            IGenericShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ytop )( 
            IGenericShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ytop )( 
            IGenericShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ybottom )( 
            IGenericShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ybottom )( 
            IGenericShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ixx )( 
            IGenericShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ixx )( 
            IGenericShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Iyy )( 
            IGenericShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Iyy )( 
            IGenericShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ixy )( 
            IGenericShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ixy )( 
            IGenericShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IGenericShape * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IGenericShape * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IGenericShape * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IGenericShapeVtbl;

    interface IGenericShape
    {
        CONST_VTBL struct IGenericShapeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGenericShape_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGenericShape_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGenericShape_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGenericShape_get_Area(This,pVal)	\
    ( (This)->lpVtbl -> get_Area(This,pVal) ) 

#define IGenericShape_put_Area(This,newVal)	\
    ( (This)->lpVtbl -> put_Area(This,newVal) ) 

#define IGenericShape_put_Perimeter(This,newVal)	\
    ( (This)->lpVtbl -> put_Perimeter(This,newVal) ) 

#define IGenericShape_get_Centroid(This,pVal)	\
    ( (This)->lpVtbl -> get_Centroid(This,pVal) ) 

#define IGenericShape_putref_Centroid(This,newVal)	\
    ( (This)->lpVtbl -> putref_Centroid(This,newVal) ) 

#define IGenericShape_get_Xleft(This,pVal)	\
    ( (This)->lpVtbl -> get_Xleft(This,pVal) ) 

#define IGenericShape_put_Xleft(This,newVal)	\
    ( (This)->lpVtbl -> put_Xleft(This,newVal) ) 

#define IGenericShape_get_Xright(This,pVal)	\
    ( (This)->lpVtbl -> get_Xright(This,pVal) ) 

#define IGenericShape_put_Xright(This,newVal)	\
    ( (This)->lpVtbl -> put_Xright(This,newVal) ) 

#define IGenericShape_get_Ytop(This,pVal)	\
    ( (This)->lpVtbl -> get_Ytop(This,pVal) ) 

#define IGenericShape_put_Ytop(This,newVal)	\
    ( (This)->lpVtbl -> put_Ytop(This,newVal) ) 

#define IGenericShape_get_Ybottom(This,pVal)	\
    ( (This)->lpVtbl -> get_Ybottom(This,pVal) ) 

#define IGenericShape_put_Ybottom(This,newVal)	\
    ( (This)->lpVtbl -> put_Ybottom(This,newVal) ) 

#define IGenericShape_get_Ixx(This,pVal)	\
    ( (This)->lpVtbl -> get_Ixx(This,pVal) ) 

#define IGenericShape_put_Ixx(This,newVal)	\
    ( (This)->lpVtbl -> put_Ixx(This,newVal) ) 

#define IGenericShape_get_Iyy(This,pVal)	\
    ( (This)->lpVtbl -> get_Iyy(This,pVal) ) 

#define IGenericShape_put_Iyy(This,newVal)	\
    ( (This)->lpVtbl -> put_Iyy(This,newVal) ) 

#define IGenericShape_get_Ixy(This,pVal)	\
    ( (This)->lpVtbl -> get_Ixy(This,pVal) ) 

#define IGenericShape_put_Ixy(This,newVal)	\
    ( (This)->lpVtbl -> put_Ixy(This,newVal) ) 

#define IGenericShape_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IGenericShape_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IGenericShape_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGenericShape_INTERFACE_DEFINED__ */


#ifndef __IPolyShape_INTERFACE_DEFINED__
#define __IPolyShape_INTERFACE_DEFINED__

/* interface IPolyShape */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPolyShape;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("94FD8E63-0013-11D3-8CDF-8BF0A4AD5B35")
    IPolyShape : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddPoint( 
            /* [in] */ Float64 x,
            /* [in] */ Float64 y) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddPointEx( 
            /* [in] */ IPoint2d *pPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddPoints( 
            /* [in] */ IPoint2dCollection *pPoints) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemovePoint( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumPoints( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Point( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Points( 
            /* [retval][out] */ IPoint2dCollection **coll) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPolyShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPolyShape * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPolyShape * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPolyShape * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPoint )( 
            IPolyShape * This,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPointEx )( 
            IPolyShape * This,
            /* [in] */ IPoint2d *pPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPoints )( 
            IPolyShape * This,
            /* [in] */ IPoint2dCollection *pPoints);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemovePoint )( 
            IPolyShape * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IPolyShape * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IPolyShape * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumPoints )( 
            IPolyShape * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Point )( 
            IPolyShape * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IPolyShape * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Points )( 
            IPolyShape * This,
            /* [retval][out] */ IPoint2dCollection **coll);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPolyShape * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IPolyShapeVtbl;

    interface IPolyShape
    {
        CONST_VTBL struct IPolyShapeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPolyShape_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPolyShape_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPolyShape_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPolyShape_AddPoint(This,x,y)	\
    ( (This)->lpVtbl -> AddPoint(This,x,y) ) 

#define IPolyShape_AddPointEx(This,pPoint)	\
    ( (This)->lpVtbl -> AddPointEx(This,pPoint) ) 

#define IPolyShape_AddPoints(This,pPoints)	\
    ( (This)->lpVtbl -> AddPoints(This,pPoints) ) 

#define IPolyShape_RemovePoint(This,index)	\
    ( (This)->lpVtbl -> RemovePoint(This,index) ) 

#define IPolyShape_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IPolyShape_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IPolyShape_get_NumPoints(This,pVal)	\
    ( (This)->lpVtbl -> get_NumPoints(This,pVal) ) 

#define IPolyShape_get_Point(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Point(This,index,pVal) ) 

#define IPolyShape_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IPolyShape_get_Points(This,coll)	\
    ( (This)->lpVtbl -> get_Points(This,coll) ) 

#define IPolyShape_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPolyShape_INTERFACE_DEFINED__ */


#ifndef __ICircle_INTERFACE_DEFINED__
#define __ICircle_INTERFACE_DEFINED__

/* interface ICircle */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICircle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("219B8FC1-0154-11D3-8CDF-CCA4ADEF4534")
    ICircle : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Radius( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Radius( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Center( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Center( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ThroughTwoPoints( 
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ThroughThreePoints( 
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2,
            /* [in] */ IPoint2d *p3) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ContainsPoint( 
            /* [in] */ IPoint2d *p,
            /* [retval][out] */ VARIANT_BOOL *pResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnCircle( 
            /* [in] */ IPoint2d *p,
            /* [retval][out] */ VARIANT_BOOL *pResult) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICircleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICircle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICircle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICircle * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Radius )( 
            ICircle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Radius )( 
            ICircle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Center )( 
            ICircle * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Center )( 
            ICircle * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ThroughTwoPoints )( 
            ICircle * This,
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ThroughThreePoints )( 
            ICircle * This,
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2,
            /* [in] */ IPoint2d *p3);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ContainsPoint )( 
            ICircle * This,
            /* [in] */ IPoint2d *p,
            /* [retval][out] */ VARIANT_BOOL *pResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnCircle )( 
            ICircle * This,
            /* [in] */ IPoint2d *p,
            /* [retval][out] */ VARIANT_BOOL *pResult);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            ICircle * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ICircle * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICircle * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICircleVtbl;

    interface ICircle
    {
        CONST_VTBL struct ICircleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICircle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICircle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICircle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICircle_get_Radius(This,pVal)	\
    ( (This)->lpVtbl -> get_Radius(This,pVal) ) 

#define ICircle_put_Radius(This,newVal)	\
    ( (This)->lpVtbl -> put_Radius(This,newVal) ) 

#define ICircle_get_Center(This,pVal)	\
    ( (This)->lpVtbl -> get_Center(This,pVal) ) 

#define ICircle_putref_Center(This,newVal)	\
    ( (This)->lpVtbl -> putref_Center(This,newVal) ) 

#define ICircle_ThroughTwoPoints(This,p1,p2)	\
    ( (This)->lpVtbl -> ThroughTwoPoints(This,p1,p2) ) 

#define ICircle_ThroughThreePoints(This,p1,p2,p3)	\
    ( (This)->lpVtbl -> ThroughThreePoints(This,p1,p2,p3) ) 

#define ICircle_ContainsPoint(This,p,pResult)	\
    ( (This)->lpVtbl -> ContainsPoint(This,p,pResult) ) 

#define ICircle_PointOnCircle(This,p,pResult)	\
    ( (This)->lpVtbl -> PointOnCircle(This,p,pResult) ) 

#define ICircle_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define ICircle_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define ICircle_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICircle_INTERFACE_DEFINED__ */


#ifndef __IRectangle_INTERFACE_DEFINED__
#define __IRectangle_INTERFACE_DEFINED__

/* interface IRectangle */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRectangle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3E07BAA1-01A2-11D3-8CDF-D8B830C3A934")
    IRectangle : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRectangleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRectangle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRectangle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRectangle * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IRectangle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IRectangle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IRectangle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IRectangle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IRectangle * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IRectangle * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IRectangle * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IRectangle * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IRectangle * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IRectangleVtbl;

    interface IRectangle
    {
        CONST_VTBL struct IRectangleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRectangle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRectangle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRectangle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRectangle_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define IRectangle_put_Height(This,newVal)	\
    ( (This)->lpVtbl -> put_Height(This,newVal) ) 

#define IRectangle_get_Width(This,pVal)	\
    ( (This)->lpVtbl -> get_Width(This,pVal) ) 

#define IRectangle_put_Width(This,newVal)	\
    ( (This)->lpVtbl -> put_Width(This,newVal) ) 

#define IRectangle_get_HookPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_HookPoint(This,pVal) ) 

#define IRectangle_putref_HookPoint(This,newVal)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,newVal) ) 

#define IRectangle_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IRectangle_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IRectangle_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRectangle_INTERFACE_DEFINED__ */


#ifndef __ITriangle_INTERFACE_DEFINED__
#define __ITriangle_INTERFACE_DEFINED__

/* interface ITriangle */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITriangle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0C89D3A1-02E2-11D3-8CDF-DDE6AA65DF35")
    ITriangle : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Offset( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Offset( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITriangleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITriangle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITriangle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITriangle * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            ITriangle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            ITriangle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            ITriangle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            ITriangle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Offset )( 
            ITriangle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Offset )( 
            ITriangle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            ITriangle * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            ITriangle * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            ITriangle * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ITriangle * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ITriangle * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ITriangleVtbl;

    interface ITriangle
    {
        CONST_VTBL struct ITriangleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITriangle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITriangle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITriangle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITriangle_get_Width(This,pVal)	\
    ( (This)->lpVtbl -> get_Width(This,pVal) ) 

#define ITriangle_put_Width(This,newVal)	\
    ( (This)->lpVtbl -> put_Width(This,newVal) ) 

#define ITriangle_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define ITriangle_put_Height(This,newVal)	\
    ( (This)->lpVtbl -> put_Height(This,newVal) ) 

#define ITriangle_get_Offset(This,pVal)	\
    ( (This)->lpVtbl -> get_Offset(This,pVal) ) 

#define ITriangle_put_Offset(This,newVal)	\
    ( (This)->lpVtbl -> put_Offset(This,newVal) ) 

#define ITriangle_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define ITriangle_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define ITriangle_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define ITriangle_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define ITriangle_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITriangle_INTERFACE_DEFINED__ */


#ifndef __IPrecastBeam_INTERFACE_DEFINED__
#define __IPrecastBeam_INTERFACE_DEFINED__

/* interface IPrecastBeam */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPrecastBeam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E7E272C1-032F-11D3-8CDF-861E1B8C3634")
    IPrecastBeam : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D6( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D6( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D7( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D7( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AvgWebWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPrecastBeamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPrecastBeam * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPrecastBeam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPrecastBeam * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W1 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W1 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W2 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W2 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W3 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W3 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W4 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W4 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D1 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D1 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D2 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D2 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D3 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D3 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D4 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D4 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D5 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D5 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D6 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D6 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D7 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D7 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T1 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T1 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T2 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T2 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C1 )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C1 )( 
            IPrecastBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IPrecastBeam * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IPrecastBeam * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AvgWebWidth )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeWidth )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IPrecastBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IPrecastBeam * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IPrecastBeam * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPrecastBeam * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IPrecastBeamVtbl;

    interface IPrecastBeam
    {
        CONST_VTBL struct IPrecastBeamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrecastBeam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPrecastBeam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPrecastBeam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPrecastBeam_get_W1(This,pVal)	\
    ( (This)->lpVtbl -> get_W1(This,pVal) ) 

#define IPrecastBeam_put_W1(This,newVal)	\
    ( (This)->lpVtbl -> put_W1(This,newVal) ) 

#define IPrecastBeam_get_W2(This,pVal)	\
    ( (This)->lpVtbl -> get_W2(This,pVal) ) 

#define IPrecastBeam_put_W2(This,newVal)	\
    ( (This)->lpVtbl -> put_W2(This,newVal) ) 

#define IPrecastBeam_get_W3(This,pVal)	\
    ( (This)->lpVtbl -> get_W3(This,pVal) ) 

#define IPrecastBeam_put_W3(This,newVal)	\
    ( (This)->lpVtbl -> put_W3(This,newVal) ) 

#define IPrecastBeam_get_W4(This,pVal)	\
    ( (This)->lpVtbl -> get_W4(This,pVal) ) 

#define IPrecastBeam_put_W4(This,newVal)	\
    ( (This)->lpVtbl -> put_W4(This,newVal) ) 

#define IPrecastBeam_get_D1(This,pVal)	\
    ( (This)->lpVtbl -> get_D1(This,pVal) ) 

#define IPrecastBeam_put_D1(This,newVal)	\
    ( (This)->lpVtbl -> put_D1(This,newVal) ) 

#define IPrecastBeam_get_D2(This,pVal)	\
    ( (This)->lpVtbl -> get_D2(This,pVal) ) 

#define IPrecastBeam_put_D2(This,newVal)	\
    ( (This)->lpVtbl -> put_D2(This,newVal) ) 

#define IPrecastBeam_get_D3(This,pVal)	\
    ( (This)->lpVtbl -> get_D3(This,pVal) ) 

#define IPrecastBeam_put_D3(This,newVal)	\
    ( (This)->lpVtbl -> put_D3(This,newVal) ) 

#define IPrecastBeam_get_D4(This,pVal)	\
    ( (This)->lpVtbl -> get_D4(This,pVal) ) 

#define IPrecastBeam_put_D4(This,newVal)	\
    ( (This)->lpVtbl -> put_D4(This,newVal) ) 

#define IPrecastBeam_get_D5(This,pVal)	\
    ( (This)->lpVtbl -> get_D5(This,pVal) ) 

#define IPrecastBeam_put_D5(This,newVal)	\
    ( (This)->lpVtbl -> put_D5(This,newVal) ) 

#define IPrecastBeam_get_D6(This,pVal)	\
    ( (This)->lpVtbl -> get_D6(This,pVal) ) 

#define IPrecastBeam_put_D6(This,newVal)	\
    ( (This)->lpVtbl -> put_D6(This,newVal) ) 

#define IPrecastBeam_get_D7(This,pVal)	\
    ( (This)->lpVtbl -> get_D7(This,pVal) ) 

#define IPrecastBeam_put_D7(This,newVal)	\
    ( (This)->lpVtbl -> put_D7(This,newVal) ) 

#define IPrecastBeam_get_T1(This,pVal)	\
    ( (This)->lpVtbl -> get_T1(This,pVal) ) 

#define IPrecastBeam_put_T1(This,newVal)	\
    ( (This)->lpVtbl -> put_T1(This,newVal) ) 

#define IPrecastBeam_get_T2(This,pVal)	\
    ( (This)->lpVtbl -> get_T2(This,pVal) ) 

#define IPrecastBeam_put_T2(This,newVal)	\
    ( (This)->lpVtbl -> put_T2(This,newVal) ) 

#define IPrecastBeam_get_C1(This,pVal)	\
    ( (This)->lpVtbl -> get_C1(This,pVal) ) 

#define IPrecastBeam_put_C1(This,newVal)	\
    ( (This)->lpVtbl -> put_C1(This,newVal) ) 

#define IPrecastBeam_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define IPrecastBeam_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define IPrecastBeam_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define IPrecastBeam_get_AvgWebWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_AvgWebWidth(This,pVal) ) 

#define IPrecastBeam_get_BottomFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomFlangeWidth(This,pVal) ) 

#define IPrecastBeam_get_TopFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,pVal) ) 

#define IPrecastBeam_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IPrecastBeam_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IPrecastBeam_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPrecastBeam_INTERFACE_DEFINED__ */


#ifndef __INUBeam_INTERFACE_DEFINED__
#define __INUBeam_INTERFACE_DEFINED__

/* interface INUBeam */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_INUBeam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF453AD4-38FF-4493-B988-4E871CBE0F2E")
    INUBeam : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBlock( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndBlock( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_R1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_R1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_R2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_R2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_R3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_R3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_R4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_R4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AvgWebWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct INUBeamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INUBeam * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INUBeam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INUBeam * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W1 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W1 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W2 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W2 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D1 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D1 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D2 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D2 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D3 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D3 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D4 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D4 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D5 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D5 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBlock )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndBlock )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_R1 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_R1 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_R2 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_R2 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_R3 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_R3 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_R4 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_R4 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C1 )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C1 )( 
            INUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            INUBeam * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            INUBeam * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AvgWebWidth )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeWidth )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            INUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            INUBeam * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            INUBeam * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            INUBeam * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } INUBeamVtbl;

    interface INUBeam
    {
        CONST_VTBL struct INUBeamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INUBeam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INUBeam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INUBeam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INUBeam_get_W1(This,pVal)	\
    ( (This)->lpVtbl -> get_W1(This,pVal) ) 

#define INUBeam_put_W1(This,newVal)	\
    ( (This)->lpVtbl -> put_W1(This,newVal) ) 

#define INUBeam_get_W2(This,pVal)	\
    ( (This)->lpVtbl -> get_W2(This,pVal) ) 

#define INUBeam_put_W2(This,newVal)	\
    ( (This)->lpVtbl -> put_W2(This,newVal) ) 

#define INUBeam_get_D1(This,pVal)	\
    ( (This)->lpVtbl -> get_D1(This,pVal) ) 

#define INUBeam_put_D1(This,newVal)	\
    ( (This)->lpVtbl -> put_D1(This,newVal) ) 

#define INUBeam_get_D2(This,pVal)	\
    ( (This)->lpVtbl -> get_D2(This,pVal) ) 

#define INUBeam_put_D2(This,newVal)	\
    ( (This)->lpVtbl -> put_D2(This,newVal) ) 

#define INUBeam_get_D3(This,pVal)	\
    ( (This)->lpVtbl -> get_D3(This,pVal) ) 

#define INUBeam_put_D3(This,newVal)	\
    ( (This)->lpVtbl -> put_D3(This,newVal) ) 

#define INUBeam_get_D4(This,pVal)	\
    ( (This)->lpVtbl -> get_D4(This,pVal) ) 

#define INUBeam_put_D4(This,newVal)	\
    ( (This)->lpVtbl -> put_D4(This,newVal) ) 

#define INUBeam_get_D5(This,pVal)	\
    ( (This)->lpVtbl -> get_D5(This,pVal) ) 

#define INUBeam_put_D5(This,newVal)	\
    ( (This)->lpVtbl -> put_D5(This,newVal) ) 

#define INUBeam_get_T(This,pVal)	\
    ( (This)->lpVtbl -> get_T(This,pVal) ) 

#define INUBeam_put_T(This,newVal)	\
    ( (This)->lpVtbl -> put_T(This,newVal) ) 

#define INUBeam_get_EndBlock(This,pVal)	\
    ( (This)->lpVtbl -> get_EndBlock(This,pVal) ) 

#define INUBeam_put_EndBlock(This,newVal)	\
    ( (This)->lpVtbl -> put_EndBlock(This,newVal) ) 

#define INUBeam_get_R1(This,pVal)	\
    ( (This)->lpVtbl -> get_R1(This,pVal) ) 

#define INUBeam_put_R1(This,newVal)	\
    ( (This)->lpVtbl -> put_R1(This,newVal) ) 

#define INUBeam_get_R2(This,pVal)	\
    ( (This)->lpVtbl -> get_R2(This,pVal) ) 

#define INUBeam_put_R2(This,newVal)	\
    ( (This)->lpVtbl -> put_R2(This,newVal) ) 

#define INUBeam_get_R3(This,pVal)	\
    ( (This)->lpVtbl -> get_R3(This,pVal) ) 

#define INUBeam_put_R3(This,newVal)	\
    ( (This)->lpVtbl -> put_R3(This,newVal) ) 

#define INUBeam_get_R4(This,pVal)	\
    ( (This)->lpVtbl -> get_R4(This,pVal) ) 

#define INUBeam_put_R4(This,newVal)	\
    ( (This)->lpVtbl -> put_R4(This,newVal) ) 

#define INUBeam_get_C1(This,pVal)	\
    ( (This)->lpVtbl -> get_C1(This,pVal) ) 

#define INUBeam_put_C1(This,newVal)	\
    ( (This)->lpVtbl -> put_C1(This,newVal) ) 

#define INUBeam_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define INUBeam_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define INUBeam_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define INUBeam_get_AvgWebWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_AvgWebWidth(This,pVal) ) 

#define INUBeam_get_BottomFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomFlangeWidth(This,pVal) ) 

#define INUBeam_get_TopFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,pVal) ) 

#define INUBeam_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define INUBeam_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define INUBeam_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INUBeam_INTERFACE_DEFINED__ */


#ifndef __IBulbTee_INTERFACE_DEFINED__
#define __IBulbTee_INTERFACE_DEFINED__

/* interface IBulbTee */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBulbTee;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("84F1406D-0AF3-400b-92A4-1EE4804921AD")
    IBulbTee : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D6( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D6( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D7( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D7( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AvgWebWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBulbTeeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBulbTee * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBulbTee * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBulbTee * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W1 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W1 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W2 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W2 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W3 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W3 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W4 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W4 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W5 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W5 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C1 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C1 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D1 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D1 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D2 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D2 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D3 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D3 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D4 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D4 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D5 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D5 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D6 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D6 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D7 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D7 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T1 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T1 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T2 )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T2 )( 
            IBulbTee * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IBulbTee * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IBulbTee * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AvgWebWidth )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeWidth )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IBulbTee * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IBulbTee * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IBulbTee * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IBulbTee * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IBulbTeeVtbl;

    interface IBulbTee
    {
        CONST_VTBL struct IBulbTeeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBulbTee_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBulbTee_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBulbTee_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBulbTee_get_W1(This,pVal)	\
    ( (This)->lpVtbl -> get_W1(This,pVal) ) 

#define IBulbTee_put_W1(This,newVal)	\
    ( (This)->lpVtbl -> put_W1(This,newVal) ) 

#define IBulbTee_get_W2(This,pVal)	\
    ( (This)->lpVtbl -> get_W2(This,pVal) ) 

#define IBulbTee_put_W2(This,newVal)	\
    ( (This)->lpVtbl -> put_W2(This,newVal) ) 

#define IBulbTee_get_W3(This,pVal)	\
    ( (This)->lpVtbl -> get_W3(This,pVal) ) 

#define IBulbTee_put_W3(This,newVal)	\
    ( (This)->lpVtbl -> put_W3(This,newVal) ) 

#define IBulbTee_get_W4(This,pVal)	\
    ( (This)->lpVtbl -> get_W4(This,pVal) ) 

#define IBulbTee_put_W4(This,newVal)	\
    ( (This)->lpVtbl -> put_W4(This,newVal) ) 

#define IBulbTee_get_W5(This,pVal)	\
    ( (This)->lpVtbl -> get_W5(This,pVal) ) 

#define IBulbTee_put_W5(This,newVal)	\
    ( (This)->lpVtbl -> put_W5(This,newVal) ) 

#define IBulbTee_get_C1(This,pVal)	\
    ( (This)->lpVtbl -> get_C1(This,pVal) ) 

#define IBulbTee_put_C1(This,newVal)	\
    ( (This)->lpVtbl -> put_C1(This,newVal) ) 

#define IBulbTee_get_D1(This,pVal)	\
    ( (This)->lpVtbl -> get_D1(This,pVal) ) 

#define IBulbTee_put_D1(This,newVal)	\
    ( (This)->lpVtbl -> put_D1(This,newVal) ) 

#define IBulbTee_get_D2(This,pVal)	\
    ( (This)->lpVtbl -> get_D2(This,pVal) ) 

#define IBulbTee_put_D2(This,newVal)	\
    ( (This)->lpVtbl -> put_D2(This,newVal) ) 

#define IBulbTee_get_D3(This,pVal)	\
    ( (This)->lpVtbl -> get_D3(This,pVal) ) 

#define IBulbTee_put_D3(This,newVal)	\
    ( (This)->lpVtbl -> put_D3(This,newVal) ) 

#define IBulbTee_get_D4(This,pVal)	\
    ( (This)->lpVtbl -> get_D4(This,pVal) ) 

#define IBulbTee_put_D4(This,newVal)	\
    ( (This)->lpVtbl -> put_D4(This,newVal) ) 

#define IBulbTee_get_D5(This,pVal)	\
    ( (This)->lpVtbl -> get_D5(This,pVal) ) 

#define IBulbTee_put_D5(This,newVal)	\
    ( (This)->lpVtbl -> put_D5(This,newVal) ) 

#define IBulbTee_get_D6(This,pVal)	\
    ( (This)->lpVtbl -> get_D6(This,pVal) ) 

#define IBulbTee_put_D6(This,newVal)	\
    ( (This)->lpVtbl -> put_D6(This,newVal) ) 

#define IBulbTee_get_D7(This,pVal)	\
    ( (This)->lpVtbl -> get_D7(This,pVal) ) 

#define IBulbTee_put_D7(This,newVal)	\
    ( (This)->lpVtbl -> put_D7(This,newVal) ) 

#define IBulbTee_get_T1(This,pVal)	\
    ( (This)->lpVtbl -> get_T1(This,pVal) ) 

#define IBulbTee_put_T1(This,newVal)	\
    ( (This)->lpVtbl -> put_T1(This,newVal) ) 

#define IBulbTee_get_T2(This,pVal)	\
    ( (This)->lpVtbl -> get_T2(This,pVal) ) 

#define IBulbTee_put_T2(This,newVal)	\
    ( (This)->lpVtbl -> put_T2(This,newVal) ) 

#define IBulbTee_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define IBulbTee_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define IBulbTee_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define IBulbTee_get_AvgWebWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_AvgWebWidth(This,pVal) ) 

#define IBulbTee_get_BottomFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomFlangeWidth(This,pVal) ) 

#define IBulbTee_get_TopFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,pVal) ) 

#define IBulbTee_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IBulbTee_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IBulbTee_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBulbTee_INTERFACE_DEFINED__ */


#ifndef __IBulbTee2_INTERFACE_DEFINED__
#define __IBulbTee2_INTERFACE_DEFINED__

/* interface IBulbTee2 */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBulbTee2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("08EA1719-7EF6-44EC-9B49-FF4E967DF74A")
    IBulbTee2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W6( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W6( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D6( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D6( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D7( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D7( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_n1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_n1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_n2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_n2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MinHeight( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxHeight( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CLHeight( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AvgWebWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBulbTee2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBulbTee2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBulbTee2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBulbTee2 * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W1 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W1 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W2 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W2 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W3 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W3 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W4 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W4 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W5 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W5 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W6 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W6 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C1 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C1 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C2 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C2 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D1 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D1 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D2 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D2 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D3 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D3 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D4 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D4 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D5 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D5 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D6 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D6 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D7 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D7 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T1 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T1 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T2 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T2 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_n1 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_n1 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_n2 )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_n2 )( 
            IBulbTee2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IBulbTee2 * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IBulbTee2 * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinHeight )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxHeight )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CLHeight )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AvgWebWidth )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeWidth )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IBulbTee2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IBulbTee2 * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IBulbTee2 * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IBulbTee2 * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IBulbTee2Vtbl;

    interface IBulbTee2
    {
        CONST_VTBL struct IBulbTee2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBulbTee2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBulbTee2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBulbTee2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBulbTee2_get_W1(This,pVal)	\
    ( (This)->lpVtbl -> get_W1(This,pVal) ) 

#define IBulbTee2_put_W1(This,newVal)	\
    ( (This)->lpVtbl -> put_W1(This,newVal) ) 

#define IBulbTee2_get_W2(This,pVal)	\
    ( (This)->lpVtbl -> get_W2(This,pVal) ) 

#define IBulbTee2_put_W2(This,newVal)	\
    ( (This)->lpVtbl -> put_W2(This,newVal) ) 

#define IBulbTee2_get_W3(This,pVal)	\
    ( (This)->lpVtbl -> get_W3(This,pVal) ) 

#define IBulbTee2_put_W3(This,newVal)	\
    ( (This)->lpVtbl -> put_W3(This,newVal) ) 

#define IBulbTee2_get_W4(This,pVal)	\
    ( (This)->lpVtbl -> get_W4(This,pVal) ) 

#define IBulbTee2_put_W4(This,newVal)	\
    ( (This)->lpVtbl -> put_W4(This,newVal) ) 

#define IBulbTee2_get_W5(This,pVal)	\
    ( (This)->lpVtbl -> get_W5(This,pVal) ) 

#define IBulbTee2_put_W5(This,newVal)	\
    ( (This)->lpVtbl -> put_W5(This,newVal) ) 

#define IBulbTee2_get_W6(This,pVal)	\
    ( (This)->lpVtbl -> get_W6(This,pVal) ) 

#define IBulbTee2_put_W6(This,newVal)	\
    ( (This)->lpVtbl -> put_W6(This,newVal) ) 

#define IBulbTee2_get_C1(This,pVal)	\
    ( (This)->lpVtbl -> get_C1(This,pVal) ) 

#define IBulbTee2_put_C1(This,newVal)	\
    ( (This)->lpVtbl -> put_C1(This,newVal) ) 

#define IBulbTee2_get_C2(This,pVal)	\
    ( (This)->lpVtbl -> get_C2(This,pVal) ) 

#define IBulbTee2_put_C2(This,newVal)	\
    ( (This)->lpVtbl -> put_C2(This,newVal) ) 

#define IBulbTee2_get_D1(This,pVal)	\
    ( (This)->lpVtbl -> get_D1(This,pVal) ) 

#define IBulbTee2_put_D1(This,newVal)	\
    ( (This)->lpVtbl -> put_D1(This,newVal) ) 

#define IBulbTee2_get_D2(This,pVal)	\
    ( (This)->lpVtbl -> get_D2(This,pVal) ) 

#define IBulbTee2_put_D2(This,newVal)	\
    ( (This)->lpVtbl -> put_D2(This,newVal) ) 

#define IBulbTee2_get_D3(This,pVal)	\
    ( (This)->lpVtbl -> get_D3(This,pVal) ) 

#define IBulbTee2_put_D3(This,newVal)	\
    ( (This)->lpVtbl -> put_D3(This,newVal) ) 

#define IBulbTee2_get_D4(This,pVal)	\
    ( (This)->lpVtbl -> get_D4(This,pVal) ) 

#define IBulbTee2_put_D4(This,newVal)	\
    ( (This)->lpVtbl -> put_D4(This,newVal) ) 

#define IBulbTee2_get_D5(This,pVal)	\
    ( (This)->lpVtbl -> get_D5(This,pVal) ) 

#define IBulbTee2_put_D5(This,newVal)	\
    ( (This)->lpVtbl -> put_D5(This,newVal) ) 

#define IBulbTee2_get_D6(This,pVal)	\
    ( (This)->lpVtbl -> get_D6(This,pVal) ) 

#define IBulbTee2_put_D6(This,newVal)	\
    ( (This)->lpVtbl -> put_D6(This,newVal) ) 

#define IBulbTee2_get_D7(This,pVal)	\
    ( (This)->lpVtbl -> get_D7(This,pVal) ) 

#define IBulbTee2_put_D7(This,newVal)	\
    ( (This)->lpVtbl -> put_D7(This,newVal) ) 

#define IBulbTee2_get_T1(This,pVal)	\
    ( (This)->lpVtbl -> get_T1(This,pVal) ) 

#define IBulbTee2_put_T1(This,newVal)	\
    ( (This)->lpVtbl -> put_T1(This,newVal) ) 

#define IBulbTee2_get_T2(This,pVal)	\
    ( (This)->lpVtbl -> get_T2(This,pVal) ) 

#define IBulbTee2_put_T2(This,newVal)	\
    ( (This)->lpVtbl -> put_T2(This,newVal) ) 

#define IBulbTee2_get_n1(This,pVal)	\
    ( (This)->lpVtbl -> get_n1(This,pVal) ) 

#define IBulbTee2_put_n1(This,newVal)	\
    ( (This)->lpVtbl -> put_n1(This,newVal) ) 

#define IBulbTee2_get_n2(This,pVal)	\
    ( (This)->lpVtbl -> get_n2(This,pVal) ) 

#define IBulbTee2_put_n2(This,newVal)	\
    ( (This)->lpVtbl -> put_n2(This,newVal) ) 

#define IBulbTee2_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define IBulbTee2_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define IBulbTee2_get_MinHeight(This,pVal)	\
    ( (This)->lpVtbl -> get_MinHeight(This,pVal) ) 

#define IBulbTee2_get_MaxHeight(This,pVal)	\
    ( (This)->lpVtbl -> get_MaxHeight(This,pVal) ) 

#define IBulbTee2_get_CLHeight(This,pVal)	\
    ( (This)->lpVtbl -> get_CLHeight(This,pVal) ) 

#define IBulbTee2_get_AvgWebWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_AvgWebWidth(This,pVal) ) 

#define IBulbTee2_get_BottomFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomFlangeWidth(This,pVal) ) 

#define IBulbTee2_get_TopFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,pVal) ) 

#define IBulbTee2_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IBulbTee2_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IBulbTee2_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBulbTee2_INTERFACE_DEFINED__ */


#ifndef __IMultiWeb_INTERFACE_DEFINED__
#define __IMultiWeb_INTERFACE_DEFINED__

/* interface IMultiWeb */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IMultiWeb;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("754A6B13-2256-41d9-8D48-B40E95C9A117")
    IMultiWeb : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebCount( 
            /* [retval][out] */ WebIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WebCount( 
            /* [in] */ WebIndexType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebLocation( 
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *location) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AvgWebWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMultiWebVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiWeb * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiWeb * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiWeb * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W1 )( 
            IMultiWeb * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W1 )( 
            IMultiWeb * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W2 )( 
            IMultiWeb * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W2 )( 
            IMultiWeb * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D1 )( 
            IMultiWeb * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D1 )( 
            IMultiWeb * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D2 )( 
            IMultiWeb * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D2 )( 
            IMultiWeb * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T1 )( 
            IMultiWeb * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T1 )( 
            IMultiWeb * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T2 )( 
            IMultiWeb * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T2 )( 
            IMultiWeb * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebCount )( 
            IMultiWeb * This,
            /* [retval][out] */ WebIndexType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WebCount )( 
            IMultiWeb * This,
            /* [in] */ WebIndexType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebLocation )( 
            IMultiWeb * This,
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IMultiWeb * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IMultiWeb * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IMultiWeb * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AvgWebWidth )( 
            IMultiWeb * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IMultiWeb * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IMultiWeb * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IMultiWeb * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IMultiWeb * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IMultiWebVtbl;

    interface IMultiWeb
    {
        CONST_VTBL struct IMultiWebVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiWeb_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMultiWeb_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMultiWeb_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMultiWeb_get_W1(This,pVal)	\
    ( (This)->lpVtbl -> get_W1(This,pVal) ) 

#define IMultiWeb_put_W1(This,newVal)	\
    ( (This)->lpVtbl -> put_W1(This,newVal) ) 

#define IMultiWeb_get_W2(This,pVal)	\
    ( (This)->lpVtbl -> get_W2(This,pVal) ) 

#define IMultiWeb_put_W2(This,newVal)	\
    ( (This)->lpVtbl -> put_W2(This,newVal) ) 

#define IMultiWeb_get_D1(This,pVal)	\
    ( (This)->lpVtbl -> get_D1(This,pVal) ) 

#define IMultiWeb_put_D1(This,newVal)	\
    ( (This)->lpVtbl -> put_D1(This,newVal) ) 

#define IMultiWeb_get_D2(This,pVal)	\
    ( (This)->lpVtbl -> get_D2(This,pVal) ) 

#define IMultiWeb_put_D2(This,newVal)	\
    ( (This)->lpVtbl -> put_D2(This,newVal) ) 

#define IMultiWeb_get_T1(This,pVal)	\
    ( (This)->lpVtbl -> get_T1(This,pVal) ) 

#define IMultiWeb_put_T1(This,newVal)	\
    ( (This)->lpVtbl -> put_T1(This,newVal) ) 

#define IMultiWeb_get_T2(This,pVal)	\
    ( (This)->lpVtbl -> get_T2(This,pVal) ) 

#define IMultiWeb_put_T2(This,newVal)	\
    ( (This)->lpVtbl -> put_T2(This,newVal) ) 

#define IMultiWeb_get_WebCount(This,pVal)	\
    ( (This)->lpVtbl -> get_WebCount(This,pVal) ) 

#define IMultiWeb_put_WebCount(This,newVal)	\
    ( (This)->lpVtbl -> put_WebCount(This,newVal) ) 

#define IMultiWeb_get_WebLocation(This,webIdx,location)	\
    ( (This)->lpVtbl -> get_WebLocation(This,webIdx,location) ) 

#define IMultiWeb_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define IMultiWeb_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define IMultiWeb_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define IMultiWeb_get_AvgWebWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_AvgWebWidth(This,pVal) ) 

#define IMultiWeb_get_TopFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,pVal) ) 

#define IMultiWeb_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IMultiWeb_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IMultiWeb_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMultiWeb_INTERFACE_DEFINED__ */


#ifndef __IMultiWeb2_INTERFACE_DEFINED__
#define __IMultiWeb2_INTERFACE_DEFINED__

/* interface IMultiWeb2 */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IMultiWeb2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12CBCFA5-F5C9-4a3b-A071-D277F72FD730")
    IMultiWeb2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_F1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_F1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_F2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_F2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebCount( 
            /* [retval][out] */ WebIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WebCount( 
            /* [in] */ WebIndexType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebLocation( 
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *location) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AvgWebWidth( 
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LeftBlockOut( 
            /* [in] */ VARIANT_BOOL bLeftBlockOut) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftBlockOut( 
            /* [retval][out] */ VARIANT_BOOL *pbLeftBlockOut) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RightBlockOut( 
            /* [in] */ VARIANT_BOOL bRightBlockOut) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightBlockOut( 
            /* [retval][out] */ VARIANT_BOOL *pbRightBlockOut) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMultiWeb2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiWeb2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiWeb2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiWeb2 * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W1 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W1 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W2 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W2 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H1 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H1 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H2 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H2 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H3 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H3 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T1 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T1 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T2 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T2 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T3 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T3 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T4 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T4 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T5 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T5 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_F1 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_F1 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_F2 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_F2 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C1 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C1 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C2 )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C2 )( 
            IMultiWeb2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebCount )( 
            IMultiWeb2 * This,
            /* [retval][out] */ WebIndexType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WebCount )( 
            IMultiWeb2 * This,
            /* [in] */ WebIndexType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebLocation )( 
            IMultiWeb2 * This,
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IMultiWeb2 * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IMultiWeb2 * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IMultiWeb2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AvgWebWidth )( 
            IMultiWeb2 * This,
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IMultiWeb2 * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IMultiWeb2 * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IMultiWeb2 * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LeftBlockOut )( 
            IMultiWeb2 * This,
            /* [in] */ VARIANT_BOOL bLeftBlockOut);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftBlockOut )( 
            IMultiWeb2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbLeftBlockOut);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RightBlockOut )( 
            IMultiWeb2 * This,
            /* [in] */ VARIANT_BOOL bRightBlockOut);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightBlockOut )( 
            IMultiWeb2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbRightBlockOut);
        
        END_INTERFACE
    } IMultiWeb2Vtbl;

    interface IMultiWeb2
    {
        CONST_VTBL struct IMultiWeb2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiWeb2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMultiWeb2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMultiWeb2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMultiWeb2_get_W1(This,pVal)	\
    ( (This)->lpVtbl -> get_W1(This,pVal) ) 

#define IMultiWeb2_put_W1(This,newVal)	\
    ( (This)->lpVtbl -> put_W1(This,newVal) ) 

#define IMultiWeb2_get_W2(This,pVal)	\
    ( (This)->lpVtbl -> get_W2(This,pVal) ) 

#define IMultiWeb2_put_W2(This,newVal)	\
    ( (This)->lpVtbl -> put_W2(This,newVal) ) 

#define IMultiWeb2_get_H1(This,pVal)	\
    ( (This)->lpVtbl -> get_H1(This,pVal) ) 

#define IMultiWeb2_put_H1(This,newVal)	\
    ( (This)->lpVtbl -> put_H1(This,newVal) ) 

#define IMultiWeb2_get_H2(This,pVal)	\
    ( (This)->lpVtbl -> get_H2(This,pVal) ) 

#define IMultiWeb2_put_H2(This,newVal)	\
    ( (This)->lpVtbl -> put_H2(This,newVal) ) 

#define IMultiWeb2_get_H3(This,pVal)	\
    ( (This)->lpVtbl -> get_H3(This,pVal) ) 

#define IMultiWeb2_put_H3(This,newVal)	\
    ( (This)->lpVtbl -> put_H3(This,newVal) ) 

#define IMultiWeb2_get_T1(This,pVal)	\
    ( (This)->lpVtbl -> get_T1(This,pVal) ) 

#define IMultiWeb2_put_T1(This,newVal)	\
    ( (This)->lpVtbl -> put_T1(This,newVal) ) 

#define IMultiWeb2_get_T2(This,pVal)	\
    ( (This)->lpVtbl -> get_T2(This,pVal) ) 

#define IMultiWeb2_put_T2(This,newVal)	\
    ( (This)->lpVtbl -> put_T2(This,newVal) ) 

#define IMultiWeb2_get_T3(This,pVal)	\
    ( (This)->lpVtbl -> get_T3(This,pVal) ) 

#define IMultiWeb2_put_T3(This,newVal)	\
    ( (This)->lpVtbl -> put_T3(This,newVal) ) 

#define IMultiWeb2_get_T4(This,pVal)	\
    ( (This)->lpVtbl -> get_T4(This,pVal) ) 

#define IMultiWeb2_put_T4(This,newVal)	\
    ( (This)->lpVtbl -> put_T4(This,newVal) ) 

#define IMultiWeb2_get_T5(This,pVal)	\
    ( (This)->lpVtbl -> get_T5(This,pVal) ) 

#define IMultiWeb2_put_T5(This,newVal)	\
    ( (This)->lpVtbl -> put_T5(This,newVal) ) 

#define IMultiWeb2_get_F1(This,pVal)	\
    ( (This)->lpVtbl -> get_F1(This,pVal) ) 

#define IMultiWeb2_put_F1(This,newVal)	\
    ( (This)->lpVtbl -> put_F1(This,newVal) ) 

#define IMultiWeb2_get_F2(This,pVal)	\
    ( (This)->lpVtbl -> get_F2(This,pVal) ) 

#define IMultiWeb2_put_F2(This,newVal)	\
    ( (This)->lpVtbl -> put_F2(This,newVal) ) 

#define IMultiWeb2_get_C1(This,pVal)	\
    ( (This)->lpVtbl -> get_C1(This,pVal) ) 

#define IMultiWeb2_put_C1(This,newVal)	\
    ( (This)->lpVtbl -> put_C1(This,newVal) ) 

#define IMultiWeb2_get_C2(This,pVal)	\
    ( (This)->lpVtbl -> get_C2(This,pVal) ) 

#define IMultiWeb2_put_C2(This,newVal)	\
    ( (This)->lpVtbl -> put_C2(This,newVal) ) 

#define IMultiWeb2_get_WebCount(This,pVal)	\
    ( (This)->lpVtbl -> get_WebCount(This,pVal) ) 

#define IMultiWeb2_put_WebCount(This,newVal)	\
    ( (This)->lpVtbl -> put_WebCount(This,newVal) ) 

#define IMultiWeb2_get_WebLocation(This,webIdx,location)	\
    ( (This)->lpVtbl -> get_WebLocation(This,webIdx,location) ) 

#define IMultiWeb2_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define IMultiWeb2_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define IMultiWeb2_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define IMultiWeb2_get_TopFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,pVal) ) 

#define IMultiWeb2_get_AvgWebWidth(This,webIdx,pVal)	\
    ( (This)->lpVtbl -> get_AvgWebWidth(This,webIdx,pVal) ) 

#define IMultiWeb2_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IMultiWeb2_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IMultiWeb2_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define IMultiWeb2_put_LeftBlockOut(This,bLeftBlockOut)	\
    ( (This)->lpVtbl -> put_LeftBlockOut(This,bLeftBlockOut) ) 

#define IMultiWeb2_get_LeftBlockOut(This,pbLeftBlockOut)	\
    ( (This)->lpVtbl -> get_LeftBlockOut(This,pbLeftBlockOut) ) 

#define IMultiWeb2_put_RightBlockOut(This,bRightBlockOut)	\
    ( (This)->lpVtbl -> put_RightBlockOut(This,bRightBlockOut) ) 

#define IMultiWeb2_get_RightBlockOut(This,pbRightBlockOut)	\
    ( (This)->lpVtbl -> get_RightBlockOut(This,pbRightBlockOut) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMultiWeb2_INTERFACE_DEFINED__ */


#ifndef __ITrafficBarrier_INTERFACE_DEFINED__
#define __ITrafficBarrier_INTERFACE_DEFINED__

/* interface ITrafficBarrier */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITrafficBarrier;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2558CFC1-03CE-11D3-8CDF-EBFB6612CA35")
    ITrafficBarrier : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ TrafficBarrierOrientation *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ TrafficBarrierOrientation newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITrafficBarrierVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITrafficBarrier * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITrafficBarrier * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITrafficBarrier * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X1 )( 
            ITrafficBarrier * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X1 )( 
            ITrafficBarrier * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X2 )( 
            ITrafficBarrier * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X2 )( 
            ITrafficBarrier * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X3 )( 
            ITrafficBarrier * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X3 )( 
            ITrafficBarrier * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X4 )( 
            ITrafficBarrier * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X4 )( 
            ITrafficBarrier * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X5 )( 
            ITrafficBarrier * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X5 )( 
            ITrafficBarrier * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y1 )( 
            ITrafficBarrier * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y1 )( 
            ITrafficBarrier * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y2 )( 
            ITrafficBarrier * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y2 )( 
            ITrafficBarrier * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y3 )( 
            ITrafficBarrier * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y3 )( 
            ITrafficBarrier * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y4 )( 
            ITrafficBarrier * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y4 )( 
            ITrafficBarrier * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            ITrafficBarrier * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            ITrafficBarrier * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            ITrafficBarrier * This,
            /* [retval][out] */ TrafficBarrierOrientation *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            ITrafficBarrier * This,
            /* [in] */ TrafficBarrierOrientation newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            ITrafficBarrier * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ITrafficBarrier * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ITrafficBarrier * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ITrafficBarrierVtbl;

    interface ITrafficBarrier
    {
        CONST_VTBL struct ITrafficBarrierVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrafficBarrier_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITrafficBarrier_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITrafficBarrier_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITrafficBarrier_get_X1(This,pVal)	\
    ( (This)->lpVtbl -> get_X1(This,pVal) ) 

#define ITrafficBarrier_put_X1(This,newVal)	\
    ( (This)->lpVtbl -> put_X1(This,newVal) ) 

#define ITrafficBarrier_get_X2(This,pVal)	\
    ( (This)->lpVtbl -> get_X2(This,pVal) ) 

#define ITrafficBarrier_put_X2(This,newVal)	\
    ( (This)->lpVtbl -> put_X2(This,newVal) ) 

#define ITrafficBarrier_get_X3(This,pVal)	\
    ( (This)->lpVtbl -> get_X3(This,pVal) ) 

#define ITrafficBarrier_put_X3(This,newVal)	\
    ( (This)->lpVtbl -> put_X3(This,newVal) ) 

#define ITrafficBarrier_get_X4(This,pVal)	\
    ( (This)->lpVtbl -> get_X4(This,pVal) ) 

#define ITrafficBarrier_put_X4(This,newVal)	\
    ( (This)->lpVtbl -> put_X4(This,newVal) ) 

#define ITrafficBarrier_get_X5(This,pVal)	\
    ( (This)->lpVtbl -> get_X5(This,pVal) ) 

#define ITrafficBarrier_put_X5(This,newVal)	\
    ( (This)->lpVtbl -> put_X5(This,newVal) ) 

#define ITrafficBarrier_get_Y1(This,pVal)	\
    ( (This)->lpVtbl -> get_Y1(This,pVal) ) 

#define ITrafficBarrier_put_Y1(This,newVal)	\
    ( (This)->lpVtbl -> put_Y1(This,newVal) ) 

#define ITrafficBarrier_get_Y2(This,pVal)	\
    ( (This)->lpVtbl -> get_Y2(This,pVal) ) 

#define ITrafficBarrier_put_Y2(This,newVal)	\
    ( (This)->lpVtbl -> put_Y2(This,newVal) ) 

#define ITrafficBarrier_get_Y3(This,pVal)	\
    ( (This)->lpVtbl -> get_Y3(This,pVal) ) 

#define ITrafficBarrier_put_Y3(This,newVal)	\
    ( (This)->lpVtbl -> put_Y3(This,newVal) ) 

#define ITrafficBarrier_get_Y4(This,pVal)	\
    ( (This)->lpVtbl -> get_Y4(This,pVal) ) 

#define ITrafficBarrier_put_Y4(This,newVal)	\
    ( (This)->lpVtbl -> put_Y4(This,newVal) ) 

#define ITrafficBarrier_get_HookPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_HookPoint(This,pVal) ) 

#define ITrafficBarrier_putref_HookPoint(This,newVal)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,newVal) ) 

#define ITrafficBarrier_get_Orientation(This,pVal)	\
    ( (This)->lpVtbl -> get_Orientation(This,pVal) ) 

#define ITrafficBarrier_put_Orientation(This,newVal)	\
    ( (This)->lpVtbl -> put_Orientation(This,newVal) ) 

#define ITrafficBarrier_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define ITrafficBarrier_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define ITrafficBarrier_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITrafficBarrier_INTERFACE_DEFINED__ */


#ifndef __IPoint2dFactory_INTERFACE_DEFINED__
#define __IPoint2dFactory_INTERFACE_DEFINED__

/* interface IPoint2dFactory */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPoint2dFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC5AC145-5CD0-11D3-8CDF-A057587EDC05")
    IPoint2dFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreatePoint( 
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPoint2dFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint2dFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint2dFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint2dFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatePoint )( 
            IPoint2dFactory * This,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPoint2dFactory * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IPoint2dFactoryVtbl;

    interface IPoint2dFactory
    {
        CONST_VTBL struct IPoint2dFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint2dFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPoint2dFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPoint2dFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPoint2dFactory_CreatePoint(This,ppPoint)	\
    ( (This)->lpVtbl -> CreatePoint(This,ppPoint) ) 

#define IPoint2dFactory_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPoint2dFactory_INTERFACE_DEFINED__ */


#ifndef __IPoint3dFactory_INTERFACE_DEFINED__
#define __IPoint3dFactory_INTERFACE_DEFINED__

/* interface IPoint3dFactory */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPoint3dFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E74E1AA0-5D87-11d3-8CDF-A057587EDC05")
    IPoint3dFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreatePoint( 
            /* [retval][out] */ IPoint3d **ppPoint) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPoint3dFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint3dFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint3dFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint3dFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatePoint )( 
            IPoint3dFactory * This,
            /* [retval][out] */ IPoint3d **ppPoint);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPoint3dFactory * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IPoint3dFactoryVtbl;

    interface IPoint3dFactory
    {
        CONST_VTBL struct IPoint3dFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint3dFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPoint3dFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPoint3dFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPoint3dFactory_CreatePoint(This,ppPoint)	\
    ( (This)->lpVtbl -> CreatePoint(This,ppPoint) ) 

#define IPoint3dFactory_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPoint3dFactory_INTERFACE_DEFINED__ */


#ifndef __ILine2dFactory_INTERFACE_DEFINED__
#define __ILine2dFactory_INTERFACE_DEFINED__

/* interface ILine2dFactory */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILine2dFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A2954980-5D17-11d3-8CDF-A057587EDC05")
    ILine2dFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateLine( 
            /* [retval][out] */ ILine2d **ppLine) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILine2dFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILine2dFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILine2dFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILine2dFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateLine )( 
            ILine2dFactory * This,
            /* [retval][out] */ ILine2d **ppLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ILine2dFactory * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ILine2dFactoryVtbl;

    interface ILine2dFactory
    {
        CONST_VTBL struct ILine2dFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILine2dFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILine2dFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILine2dFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILine2dFactory_CreateLine(This,ppLine)	\
    ( (This)->lpVtbl -> CreateLine(This,ppLine) ) 

#define ILine2dFactory_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILine2dFactory_INTERFACE_DEFINED__ */


#ifndef __ILineSegment2dFactory_INTERFACE_DEFINED__
#define __ILineSegment2dFactory_INTERFACE_DEFINED__

/* interface ILineSegment2dFactory */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILineSegment2dFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C62D94E0-8AEB-11d3-8CDF-EFB6C2561C46")
    ILineSegment2dFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateLineSegment( 
            /* [retval][out] */ ILineSegment2d **ppLineSeg) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILineSegment2dFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILineSegment2dFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILineSegment2dFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILineSegment2dFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateLineSegment )( 
            ILineSegment2dFactory * This,
            /* [retval][out] */ ILineSegment2d **ppLineSeg);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ILineSegment2dFactory * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ILineSegment2dFactoryVtbl;

    interface ILineSegment2dFactory
    {
        CONST_VTBL struct ILineSegment2dFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILineSegment2dFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILineSegment2dFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILineSegment2dFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILineSegment2dFactory_CreateLineSegment(This,ppLineSeg)	\
    ( (This)->lpVtbl -> CreateLineSegment(This,ppLineSeg) ) 

#define ILineSegment2dFactory_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILineSegment2dFactory_INTERFACE_DEFINED__ */


#ifndef __IGeomUtil2d_INTERFACE_DEFINED__
#define __IGeomUtil2d_INTERFACE_DEFINED__

/* interface IGeomUtil2d */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGeomUtil2d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("110FFB8A-2B04-11D3-8952-006097C68A9C")
    IGeomUtil2d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GenerateCircle( 
            /* [in] */ IndexType nPoints,
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 radius,
            /* [defaultvalue][in] */ Float64 initAngle,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Distance( 
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2,
            /* [retval][out] */ Float64 *dist) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Magnitude( 
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ Float64 *pMag) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Angle( 
            /* [in] */ IPoint2d *pStart,
            /* [in] */ IPoint2d *pCenter,
            /* [in] */ IPoint2d *pEnd,
            /* [retval][out] */ Float64 *angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ShortestDistanceToPoint( 
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ Float64 *pDist) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnLineNearest( 
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ IPoint2d **ppPOLN) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateParallelLineThroughPoint( 
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ ILine2d **ppLine) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateParallelLine( 
            /* [in] */ ILine2d *pLine,
            /* [in] */ Float64 dist,
            /* [retval][out] */ ILine2d **ppLine) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateNormalLineThroughPoint( 
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ ILine2d **ppLine) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AreLinesColinear( 
            /* [in] */ ILine2d *pLine1,
            /* [in] */ ILine2d *pLine2,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DoesLineContainPoint( 
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint2d *pPoint,
            /* [in] */ Float64 tolerance,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DoesLineSegmentContainPoint( 
            /* [in] */ ILineSegment2d *pSeg,
            /* [in] */ IPoint2d *pPoint,
            /* [in] */ Float64 tolerance,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DivideLineSegment( 
            /* [in] */ ILineSegment2d *pSeg,
            /* [in] */ IndexType nSpaces,
            /* [retval][out] */ IPoint2dCollection **ppPoints) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DivideArc( 
            /* [in] */ IPoint2d *pStart,
            /* [in] */ IPoint2d *pCenter,
            /* [in] */ IPoint2d *pEnd,
            /* [in] */ IndexType nSpaces,
            /* [retval][out] */ IPoint2dCollection **ppPoints) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LineLineIntersect( 
            /* [in] */ ILine2d *l1,
            /* [in] */ ILine2d *l2,
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SegSegIntersect( 
            /* [in] */ ILineSegment2d *pSeg1,
            /* [in] */ ILineSegment2d *pSeg2,
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IntersectLineWithLineSegment( 
            /* [in] */ ILine2d *pLine,
            /* [in] */ ILineSegment2d *pSeg,
            /* [retval][out] */ IPoint2d **ppPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LineCircleIntersect( 
            /* [in] */ ILine2d *line,
            /* [in] */ ICircle *circle,
            /* [out] */ IPoint2d **p1,
            /* [out] */ IPoint2d **p2,
            /* [retval][out] */ short *nIntersect) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CircleCircleIntersect( 
            /* [in] */ ICircle *circle1,
            /* [in] */ ICircle *circle2,
            /* [out] */ IPoint2d **p1,
            /* [out] */ IPoint2d **p2,
            /* [retval][out] */ short *nIntersect) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AreLinesParallel( 
            /* [in] */ ILine2d *pLine1,
            /* [in] */ ILine2d *pLine2,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AreLineSegmentsParallel( 
            /* [in] */ ILineSegment2d *pSeg1,
            /* [in] */ ILineSegment2d *pSeg2,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IsLineParallelToLineSegment( 
            /* [in] */ ILine2d *pLine,
            /* [in] */ ILineSegment2d *pSeg,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateParallelLineSegment( 
            /* [in] */ ILineSegment2d *pSeg,
            /* [in] */ Float64 offset,
            /* [retval][out] */ ILineSegment2d **pNewSeg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PointInTriangle( 
            /* [in] */ IPoint2d *p,
            /* [in] */ IPoint2d *pA,
            /* [in] */ IPoint2d *pB,
            /* [in] */ IPoint2d *pC,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGeomUtil2dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeomUtil2d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeomUtil2d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeomUtil2d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GenerateCircle )( 
            IGeomUtil2d * This,
            /* [in] */ IndexType nPoints,
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 radius,
            /* [defaultvalue][in] */ Float64 initAngle,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Distance )( 
            IGeomUtil2d * This,
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2,
            /* [retval][out] */ Float64 *dist);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Magnitude )( 
            IGeomUtil2d * This,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ Float64 *pMag);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Angle )( 
            IGeomUtil2d * This,
            /* [in] */ IPoint2d *pStart,
            /* [in] */ IPoint2d *pCenter,
            /* [in] */ IPoint2d *pEnd,
            /* [retval][out] */ Float64 *angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShortestDistanceToPoint )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ Float64 *pDist);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnLineNearest )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ IPoint2d **ppPOLN);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateParallelLineThroughPoint )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ ILine2d **ppLine);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateParallelLine )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *pLine,
            /* [in] */ Float64 dist,
            /* [retval][out] */ ILine2d **ppLine);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateNormalLineThroughPoint )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint2d *pPoint,
            /* [retval][out] */ ILine2d **ppLine);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AreLinesColinear )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *pLine1,
            /* [in] */ ILine2d *pLine2,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DoesLineContainPoint )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *pLine,
            /* [in] */ IPoint2d *pPoint,
            /* [in] */ Float64 tolerance,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DoesLineSegmentContainPoint )( 
            IGeomUtil2d * This,
            /* [in] */ ILineSegment2d *pSeg,
            /* [in] */ IPoint2d *pPoint,
            /* [in] */ Float64 tolerance,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DivideLineSegment )( 
            IGeomUtil2d * This,
            /* [in] */ ILineSegment2d *pSeg,
            /* [in] */ IndexType nSpaces,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DivideArc )( 
            IGeomUtil2d * This,
            /* [in] */ IPoint2d *pStart,
            /* [in] */ IPoint2d *pCenter,
            /* [in] */ IPoint2d *pEnd,
            /* [in] */ IndexType nSpaces,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LineLineIntersect )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *l1,
            /* [in] */ ILine2d *l2,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SegSegIntersect )( 
            IGeomUtil2d * This,
            /* [in] */ ILineSegment2d *pSeg1,
            /* [in] */ ILineSegment2d *pSeg2,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IntersectLineWithLineSegment )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *pLine,
            /* [in] */ ILineSegment2d *pSeg,
            /* [retval][out] */ IPoint2d **ppPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LineCircleIntersect )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *line,
            /* [in] */ ICircle *circle,
            /* [out] */ IPoint2d **p1,
            /* [out] */ IPoint2d **p2,
            /* [retval][out] */ short *nIntersect);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CircleCircleIntersect )( 
            IGeomUtil2d * This,
            /* [in] */ ICircle *circle1,
            /* [in] */ ICircle *circle2,
            /* [out] */ IPoint2d **p1,
            /* [out] */ IPoint2d **p2,
            /* [retval][out] */ short *nIntersect);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AreLinesParallel )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *pLine1,
            /* [in] */ ILine2d *pLine2,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AreLineSegmentsParallel )( 
            IGeomUtil2d * This,
            /* [in] */ ILineSegment2d *pSeg1,
            /* [in] */ ILineSegment2d *pSeg2,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsLineParallelToLineSegment )( 
            IGeomUtil2d * This,
            /* [in] */ ILine2d *pLine,
            /* [in] */ ILineSegment2d *pSeg,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateParallelLineSegment )( 
            IGeomUtil2d * This,
            /* [in] */ ILineSegment2d *pSeg,
            /* [in] */ Float64 offset,
            /* [retval][out] */ ILineSegment2d **pNewSeg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointInTriangle )( 
            IGeomUtil2d * This,
            /* [in] */ IPoint2d *p,
            /* [in] */ IPoint2d *pA,
            /* [in] */ IPoint2d *pB,
            /* [in] */ IPoint2d *pC,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        END_INTERFACE
    } IGeomUtil2dVtbl;

    interface IGeomUtil2d
    {
        CONST_VTBL struct IGeomUtil2dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeomUtil2d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGeomUtil2d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGeomUtil2d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGeomUtil2d_GenerateCircle(This,nPoints,center,radius,initAngle,points)	\
    ( (This)->lpVtbl -> GenerateCircle(This,nPoints,center,radius,initAngle,points) ) 

#define IGeomUtil2d_Distance(This,p1,p2,dist)	\
    ( (This)->lpVtbl -> Distance(This,p1,p2,dist) ) 

#define IGeomUtil2d_Magnitude(This,pPoint,pMag)	\
    ( (This)->lpVtbl -> Magnitude(This,pPoint,pMag) ) 

#define IGeomUtil2d_Angle(This,pStart,pCenter,pEnd,angle)	\
    ( (This)->lpVtbl -> Angle(This,pStart,pCenter,pEnd,angle) ) 

#define IGeomUtil2d_ShortestDistanceToPoint(This,pLine,pPoint,pDist)	\
    ( (This)->lpVtbl -> ShortestDistanceToPoint(This,pLine,pPoint,pDist) ) 

#define IGeomUtil2d_PointOnLineNearest(This,pLine,pPoint,ppPOLN)	\
    ( (This)->lpVtbl -> PointOnLineNearest(This,pLine,pPoint,ppPOLN) ) 

#define IGeomUtil2d_CreateParallelLineThroughPoint(This,pLine,pPoint,ppLine)	\
    ( (This)->lpVtbl -> CreateParallelLineThroughPoint(This,pLine,pPoint,ppLine) ) 

#define IGeomUtil2d_CreateParallelLine(This,pLine,dist,ppLine)	\
    ( (This)->lpVtbl -> CreateParallelLine(This,pLine,dist,ppLine) ) 

#define IGeomUtil2d_CreateNormalLineThroughPoint(This,pLine,pPoint,ppLine)	\
    ( (This)->lpVtbl -> CreateNormalLineThroughPoint(This,pLine,pPoint,ppLine) ) 

#define IGeomUtil2d_AreLinesColinear(This,pLine1,pLine2,pbResult)	\
    ( (This)->lpVtbl -> AreLinesColinear(This,pLine1,pLine2,pbResult) ) 

#define IGeomUtil2d_DoesLineContainPoint(This,pLine,pPoint,tolerance,pbResult)	\
    ( (This)->lpVtbl -> DoesLineContainPoint(This,pLine,pPoint,tolerance,pbResult) ) 

#define IGeomUtil2d_DoesLineSegmentContainPoint(This,pSeg,pPoint,tolerance,pbResult)	\
    ( (This)->lpVtbl -> DoesLineSegmentContainPoint(This,pSeg,pPoint,tolerance,pbResult) ) 

#define IGeomUtil2d_DivideLineSegment(This,pSeg,nSpaces,ppPoints)	\
    ( (This)->lpVtbl -> DivideLineSegment(This,pSeg,nSpaces,ppPoints) ) 

#define IGeomUtil2d_DivideArc(This,pStart,pCenter,pEnd,nSpaces,ppPoints)	\
    ( (This)->lpVtbl -> DivideArc(This,pStart,pCenter,pEnd,nSpaces,ppPoints) ) 

#define IGeomUtil2d_LineLineIntersect(This,l1,l2,ppPoint)	\
    ( (This)->lpVtbl -> LineLineIntersect(This,l1,l2,ppPoint) ) 

#define IGeomUtil2d_SegSegIntersect(This,pSeg1,pSeg2,ppPoint)	\
    ( (This)->lpVtbl -> SegSegIntersect(This,pSeg1,pSeg2,ppPoint) ) 

#define IGeomUtil2d_IntersectLineWithLineSegment(This,pLine,pSeg,ppPoint)	\
    ( (This)->lpVtbl -> IntersectLineWithLineSegment(This,pLine,pSeg,ppPoint) ) 

#define IGeomUtil2d_LineCircleIntersect(This,line,circle,p1,p2,nIntersect)	\
    ( (This)->lpVtbl -> LineCircleIntersect(This,line,circle,p1,p2,nIntersect) ) 

#define IGeomUtil2d_CircleCircleIntersect(This,circle1,circle2,p1,p2,nIntersect)	\
    ( (This)->lpVtbl -> CircleCircleIntersect(This,circle1,circle2,p1,p2,nIntersect) ) 

#define IGeomUtil2d_AreLinesParallel(This,pLine1,pLine2,pbResult)	\
    ( (This)->lpVtbl -> AreLinesParallel(This,pLine1,pLine2,pbResult) ) 

#define IGeomUtil2d_AreLineSegmentsParallel(This,pSeg1,pSeg2,pbResult)	\
    ( (This)->lpVtbl -> AreLineSegmentsParallel(This,pSeg1,pSeg2,pbResult) ) 

#define IGeomUtil2d_IsLineParallelToLineSegment(This,pLine,pSeg,pbResult)	\
    ( (This)->lpVtbl -> IsLineParallelToLineSegment(This,pLine,pSeg,pbResult) ) 

#define IGeomUtil2d_CreateParallelLineSegment(This,pSeg,offset,pNewSeg)	\
    ( (This)->lpVtbl -> CreateParallelLineSegment(This,pSeg,offset,pNewSeg) ) 

#define IGeomUtil2d_PointInTriangle(This,p,pA,pB,pC,pbResult)	\
    ( (This)->lpVtbl -> PointInTriangle(This,p,pA,pB,pC,pbResult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGeomUtil2d_INTERFACE_DEFINED__ */


#ifndef __IGeomUtil3d_INTERFACE_DEFINED__
#define __IGeomUtil3d_INTERFACE_DEFINED__

/* interface IGeomUtil3d */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGeomUtil3d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A60E4EC0-5D87-11d3-8CDF-A057587EDC05")
    IGeomUtil3d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Distance( 
            /* [in] */ IPoint3d *p1,
            /* [in] */ IPoint3d *p2,
            /* [retval][out] */ Float64 *pDist) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Magnitude( 
            /* [in] */ IPoint3d *p,
            /* [retval][out] */ Float64 *pMag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PointInTriangle( 
            /* [in] */ IPoint3d *p,
            /* [in] */ IPoint3d *pA,
            /* [in] */ IPoint3d *pB,
            /* [in] */ IPoint3d *pC,
            /* [retval][out] */ VARIANT_BOOL *pbResult) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGeomUtil3dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeomUtil3d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeomUtil3d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeomUtil3d * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Distance )( 
            IGeomUtil3d * This,
            /* [in] */ IPoint3d *p1,
            /* [in] */ IPoint3d *p2,
            /* [retval][out] */ Float64 *pDist);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Magnitude )( 
            IGeomUtil3d * This,
            /* [in] */ IPoint3d *p,
            /* [retval][out] */ Float64 *pMag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointInTriangle )( 
            IGeomUtil3d * This,
            /* [in] */ IPoint3d *p,
            /* [in] */ IPoint3d *pA,
            /* [in] */ IPoint3d *pB,
            /* [in] */ IPoint3d *pC,
            /* [retval][out] */ VARIANT_BOOL *pbResult);
        
        END_INTERFACE
    } IGeomUtil3dVtbl;

    interface IGeomUtil3d
    {
        CONST_VTBL struct IGeomUtil3dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeomUtil3d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGeomUtil3d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGeomUtil3d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGeomUtil3d_Distance(This,p1,p2,pDist)	\
    ( (This)->lpVtbl -> Distance(This,p1,p2,pDist) ) 

#define IGeomUtil3d_Magnitude(This,p,pMag)	\
    ( (This)->lpVtbl -> Magnitude(This,p,pMag) ) 

#define IGeomUtil3d_PointInTriangle(This,p,pA,pB,pC,pbResult)	\
    ( (This)->lpVtbl -> PointInTriangle(This,p,pA,pB,pC,pbResult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGeomUtil3d_INTERFACE_DEFINED__ */


#ifndef __IGeomUtil_INTERFACE_DEFINED__
#define __IGeomUtil_INTERFACE_DEFINED__

/* interface IGeomUtil */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGeomUtil;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B9B8520-C46E-11d3-8A19-006097C68A9C")
    IGeomUtil : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Geom2d( 
            /* [retval][out] */ IGeomUtil2d **util) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Geom3d( 
            /* [retval][out] */ IGeomUtil3d **util) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Point2dFactory( 
            /* [retval][out] */ IPoint2dFactory **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Point2dFactory( 
            /* [in] */ IPoint2dFactory *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Point3dFactory( 
            /* [retval][out] */ IPoint3dFactory **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Point3dFactory( 
            /* [in] */ IPoint3dFactory *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Line2dFactory( 
            /* [retval][out] */ ILine2dFactory **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Line2dFactory( 
            /* [in] */ ILine2dFactory *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LineSegment2dFactory( 
            /* [retval][out] */ ILineSegment2dFactory **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_LineSegment2dFactory( 
            /* [in] */ ILineSegment2dFactory *newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGeomUtilVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeomUtil * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeomUtil * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeomUtil * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geom2d )( 
            IGeomUtil * This,
            /* [retval][out] */ IGeomUtil2d **util);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geom3d )( 
            IGeomUtil * This,
            /* [retval][out] */ IGeomUtil3d **util);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Point2dFactory )( 
            IGeomUtil * This,
            /* [retval][out] */ IPoint2dFactory **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Point2dFactory )( 
            IGeomUtil * This,
            /* [in] */ IPoint2dFactory *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Point3dFactory )( 
            IGeomUtil * This,
            /* [retval][out] */ IPoint3dFactory **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Point3dFactory )( 
            IGeomUtil * This,
            /* [in] */ IPoint3dFactory *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Line2dFactory )( 
            IGeomUtil * This,
            /* [retval][out] */ ILine2dFactory **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Line2dFactory )( 
            IGeomUtil * This,
            /* [in] */ ILine2dFactory *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineSegment2dFactory )( 
            IGeomUtil * This,
            /* [retval][out] */ ILineSegment2dFactory **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_LineSegment2dFactory )( 
            IGeomUtil * This,
            /* [in] */ ILineSegment2dFactory *newVal);
        
        END_INTERFACE
    } IGeomUtilVtbl;

    interface IGeomUtil
    {
        CONST_VTBL struct IGeomUtilVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeomUtil_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGeomUtil_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGeomUtil_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGeomUtil_get_Geom2d(This,util)	\
    ( (This)->lpVtbl -> get_Geom2d(This,util) ) 

#define IGeomUtil_get_Geom3d(This,util)	\
    ( (This)->lpVtbl -> get_Geom3d(This,util) ) 

#define IGeomUtil_get_Point2dFactory(This,pVal)	\
    ( (This)->lpVtbl -> get_Point2dFactory(This,pVal) ) 

#define IGeomUtil_putref_Point2dFactory(This,newVal)	\
    ( (This)->lpVtbl -> putref_Point2dFactory(This,newVal) ) 

#define IGeomUtil_get_Point3dFactory(This,pVal)	\
    ( (This)->lpVtbl -> get_Point3dFactory(This,pVal) ) 

#define IGeomUtil_putref_Point3dFactory(This,newVal)	\
    ( (This)->lpVtbl -> putref_Point3dFactory(This,newVal) ) 

#define IGeomUtil_get_Line2dFactory(This,pVal)	\
    ( (This)->lpVtbl -> get_Line2dFactory(This,pVal) ) 

#define IGeomUtil_putref_Line2dFactory(This,newVal)	\
    ( (This)->lpVtbl -> putref_Line2dFactory(This,newVal) ) 

#define IGeomUtil_get_LineSegment2dFactory(This,pVal)	\
    ( (This)->lpVtbl -> get_LineSegment2dFactory(This,pVal) ) 

#define IGeomUtil_putref_LineSegment2dFactory(This,newVal)	\
    ( (This)->lpVtbl -> putref_LineSegment2dFactory(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGeomUtil_INTERFACE_DEFINED__ */


#ifndef __ICoordinateXform3d_INTERFACE_DEFINED__
#define __ICoordinateXform3d_INTERFACE_DEFINED__

/* interface ICoordinateXform3d */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICoordinateXform3d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D146B4A4-5103-11D3-8CDF-BFEA3D98042F")
    ICoordinateXform3d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NewOrigin( 
            /* [retval][out] */ IPoint3d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_NewOrigin( 
            /* [in] */ IPoint3d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RotationAngle( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RotationAngle( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RotationVector( 
            /* [retval][out] */ IVector3d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_RotationVector( 
            /* [in] */ IVector3d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Xform( 
            /* [out][in] */ IPoint3d **point,
            /* [in] */ XformType type) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE XformEx( 
            /* [in] */ IPoint3d *point,
            /* [in] */ XformType type,
            /* [retval][out] */ IPoint3d **result) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICoordinateXform3dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICoordinateXform3d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICoordinateXform3d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICoordinateXform3d * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NewOrigin )( 
            ICoordinateXform3d * This,
            /* [retval][out] */ IPoint3d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NewOrigin )( 
            ICoordinateXform3d * This,
            /* [in] */ IPoint3d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RotationAngle )( 
            ICoordinateXform3d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RotationAngle )( 
            ICoordinateXform3d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RotationVector )( 
            ICoordinateXform3d * This,
            /* [retval][out] */ IVector3d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RotationVector )( 
            ICoordinateXform3d * This,
            /* [in] */ IVector3d *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Xform )( 
            ICoordinateXform3d * This,
            /* [out][in] */ IPoint3d **point,
            /* [in] */ XformType type);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *XformEx )( 
            ICoordinateXform3d * This,
            /* [in] */ IPoint3d *point,
            /* [in] */ XformType type,
            /* [retval][out] */ IPoint3d **result);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICoordinateXform3d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICoordinateXform3dVtbl;

    interface ICoordinateXform3d
    {
        CONST_VTBL struct ICoordinateXform3dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICoordinateXform3d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICoordinateXform3d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICoordinateXform3d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICoordinateXform3d_get_NewOrigin(This,pVal)	\
    ( (This)->lpVtbl -> get_NewOrigin(This,pVal) ) 

#define ICoordinateXform3d_putref_NewOrigin(This,newVal)	\
    ( (This)->lpVtbl -> putref_NewOrigin(This,newVal) ) 

#define ICoordinateXform3d_get_RotationAngle(This,pVal)	\
    ( (This)->lpVtbl -> get_RotationAngle(This,pVal) ) 

#define ICoordinateXform3d_put_RotationAngle(This,newVal)	\
    ( (This)->lpVtbl -> put_RotationAngle(This,newVal) ) 

#define ICoordinateXform3d_get_RotationVector(This,pVal)	\
    ( (This)->lpVtbl -> get_RotationVector(This,pVal) ) 

#define ICoordinateXform3d_putref_RotationVector(This,newVal)	\
    ( (This)->lpVtbl -> putref_RotationVector(This,newVal) ) 

#define ICoordinateXform3d_Xform(This,point,type)	\
    ( (This)->lpVtbl -> Xform(This,point,type) ) 

#define ICoordinateXform3d_XformEx(This,point,type,result)	\
    ( (This)->lpVtbl -> XformEx(This,point,type,result) ) 

#define ICoordinateXform3d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICoordinateXform3d_INTERFACE_DEFINED__ */


#ifndef __ICoordinateXform2d_INTERFACE_DEFINED__
#define __ICoordinateXform2d_INTERFACE_DEFINED__

/* interface ICoordinateXform2d */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICoordinateXform2d;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1A1AD39B-5184-11D3-8985-006097C68A9C")
    ICoordinateXform2d : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NewOrigin( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_NewOrigin( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RotationAngle( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RotationAngle( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Xform( 
            /* [out][in] */ IPoint2d **point,
            /* [in] */ XformType type) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE XformEx( 
            /* [in] */ IPoint2d *point,
            /* [in] */ XformType type,
            /* [retval][out] */ IPoint2d **result) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICoordinateXform2dVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICoordinateXform2d * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICoordinateXform2d * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICoordinateXform2d * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NewOrigin )( 
            ICoordinateXform2d * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_NewOrigin )( 
            ICoordinateXform2d * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RotationAngle )( 
            ICoordinateXform2d * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RotationAngle )( 
            ICoordinateXform2d * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Xform )( 
            ICoordinateXform2d * This,
            /* [out][in] */ IPoint2d **point,
            /* [in] */ XformType type);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *XformEx )( 
            ICoordinateXform2d * This,
            /* [in] */ IPoint2d *point,
            /* [in] */ XformType type,
            /* [retval][out] */ IPoint2d **result);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICoordinateXform2d * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICoordinateXform2dVtbl;

    interface ICoordinateXform2d
    {
        CONST_VTBL struct ICoordinateXform2dVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICoordinateXform2d_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICoordinateXform2d_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICoordinateXform2d_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICoordinateXform2d_get_NewOrigin(This,pVal)	\
    ( (This)->lpVtbl -> get_NewOrigin(This,pVal) ) 

#define ICoordinateXform2d_putref_NewOrigin(This,newVal)	\
    ( (This)->lpVtbl -> putref_NewOrigin(This,newVal) ) 

#define ICoordinateXform2d_get_RotationAngle(This,pVal)	\
    ( (This)->lpVtbl -> get_RotationAngle(This,pVal) ) 

#define ICoordinateXform2d_put_RotationAngle(This,newVal)	\
    ( (This)->lpVtbl -> put_RotationAngle(This,newVal) ) 

#define ICoordinateXform2d_Xform(This,point,type)	\
    ( (This)->lpVtbl -> Xform(This,point,type) ) 

#define ICoordinateXform2d_XformEx(This,point,type,result)	\
    ( (This)->lpVtbl -> XformEx(This,point,type,result) ) 

#define ICoordinateXform2d_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICoordinateXform2d_INTERFACE_DEFINED__ */


#ifndef __ICircularSegment_INTERFACE_DEFINED__
#define __ICircularSegment_INTERFACE_DEFINED__

/* interface ICircularSegment */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICircularSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6C2A640-6563-11D4-8CE4-0080C7380027")
    ICircularSegment : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Radius( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Radius( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Center( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Center( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MidOrdinate( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MidOrdinate( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InteriorAngle( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_InteriorAngle( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Rotation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Rotation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICircularSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICircularSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICircularSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICircularSegment * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ICircularSegment * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            ICircularSegment * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            ICircularSegment * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            ICircularSegment * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Radius )( 
            ICircularSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Radius )( 
            ICircularSegment * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Center )( 
            ICircularSegment * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Center )( 
            ICircularSegment * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MidOrdinate )( 
            ICircularSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MidOrdinate )( 
            ICircularSegment * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InteriorAngle )( 
            ICircularSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InteriorAngle )( 
            ICircularSegment * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rotation )( 
            ICircularSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Rotation )( 
            ICircularSegment * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICircularSegment * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICircularSegmentVtbl;

    interface ICircularSegment
    {
        CONST_VTBL struct ICircularSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICircularSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICircularSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICircularSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICircularSegment_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define ICircularSegment_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define ICircularSegment_get_HookPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_HookPoint(This,pVal) ) 

#define ICircularSegment_putref_HookPoint(This,newVal)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,newVal) ) 

#define ICircularSegment_get_Radius(This,pVal)	\
    ( (This)->lpVtbl -> get_Radius(This,pVal) ) 

#define ICircularSegment_put_Radius(This,newVal)	\
    ( (This)->lpVtbl -> put_Radius(This,newVal) ) 

#define ICircularSegment_get_Center(This,pVal)	\
    ( (This)->lpVtbl -> get_Center(This,pVal) ) 

#define ICircularSegment_putref_Center(This,newVal)	\
    ( (This)->lpVtbl -> putref_Center(This,newVal) ) 

#define ICircularSegment_get_MidOrdinate(This,pVal)	\
    ( (This)->lpVtbl -> get_MidOrdinate(This,pVal) ) 

#define ICircularSegment_put_MidOrdinate(This,newVal)	\
    ( (This)->lpVtbl -> put_MidOrdinate(This,newVal) ) 

#define ICircularSegment_get_InteriorAngle(This,pVal)	\
    ( (This)->lpVtbl -> get_InteriorAngle(This,pVal) ) 

#define ICircularSegment_put_InteriorAngle(This,newVal)	\
    ( (This)->lpVtbl -> put_InteriorAngle(This,newVal) ) 

#define ICircularSegment_get_Rotation(This,pVal)	\
    ( (This)->lpVtbl -> get_Rotation(This,pVal) ) 

#define ICircularSegment_put_Rotation(This,newVal)	\
    ( (This)->lpVtbl -> put_Rotation(This,newVal) ) 

#define ICircularSegment_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICircularSegment_INTERFACE_DEFINED__ */


#ifndef __IPlateGirder_INTERFACE_DEFINED__
#define __IPlateGirder_INTERFACE_DEFINED__

/* interface IPlateGirder */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPlateGirder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9F28211D-09D6-11D5-8BBF-006097C68A9C")
    IPlateGirder : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TopFlangeWidth( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeThick( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TopFlangeThick( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BottomFlangeWidth( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeThick( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BottomFlangeThick( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebHeight( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WebHeight( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebThick( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WebThick( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_QTopFlange( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_QBottomFlange( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPlateGirderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPlateGirder * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPlateGirder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPlateGirder * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IPlateGirder * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TopFlangeWidth )( 
            IPlateGirder * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeThick )( 
            IPlateGirder * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TopFlangeThick )( 
            IPlateGirder * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeWidth )( 
            IPlateGirder * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BottomFlangeWidth )( 
            IPlateGirder * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeThick )( 
            IPlateGirder * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BottomFlangeThick )( 
            IPlateGirder * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebHeight )( 
            IPlateGirder * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WebHeight )( 
            IPlateGirder * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebThick )( 
            IPlateGirder * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WebThick )( 
            IPlateGirder * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IPlateGirder * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QTopFlange )( 
            IPlateGirder * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QBottomFlange )( 
            IPlateGirder * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IPlateGirder * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IPlateGirder * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IPlateGirder * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IPlateGirder * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPlateGirder * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IPlateGirderVtbl;

    interface IPlateGirder
    {
        CONST_VTBL struct IPlateGirderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPlateGirder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPlateGirder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPlateGirder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPlateGirder_get_TopFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,pVal) ) 

#define IPlateGirder_put_TopFlangeWidth(This,newVal)	\
    ( (This)->lpVtbl -> put_TopFlangeWidth(This,newVal) ) 

#define IPlateGirder_get_TopFlangeThick(This,pVal)	\
    ( (This)->lpVtbl -> get_TopFlangeThick(This,pVal) ) 

#define IPlateGirder_put_TopFlangeThick(This,newVal)	\
    ( (This)->lpVtbl -> put_TopFlangeThick(This,newVal) ) 

#define IPlateGirder_get_BottomFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomFlangeWidth(This,pVal) ) 

#define IPlateGirder_put_BottomFlangeWidth(This,newVal)	\
    ( (This)->lpVtbl -> put_BottomFlangeWidth(This,newVal) ) 

#define IPlateGirder_get_BottomFlangeThick(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomFlangeThick(This,pVal) ) 

#define IPlateGirder_put_BottomFlangeThick(This,newVal)	\
    ( (This)->lpVtbl -> put_BottomFlangeThick(This,newVal) ) 

#define IPlateGirder_get_WebHeight(This,pVal)	\
    ( (This)->lpVtbl -> get_WebHeight(This,pVal) ) 

#define IPlateGirder_put_WebHeight(This,newVal)	\
    ( (This)->lpVtbl -> put_WebHeight(This,newVal) ) 

#define IPlateGirder_get_WebThick(This,pVal)	\
    ( (This)->lpVtbl -> get_WebThick(This,pVal) ) 

#define IPlateGirder_put_WebThick(This,newVal)	\
    ( (This)->lpVtbl -> put_WebThick(This,newVal) ) 

#define IPlateGirder_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define IPlateGirder_get_QTopFlange(This,pVal)	\
    ( (This)->lpVtbl -> get_QTopFlange(This,pVal) ) 

#define IPlateGirder_get_QBottomFlange(This,pVal)	\
    ( (This)->lpVtbl -> get_QBottomFlange(This,pVal) ) 

#define IPlateGirder_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IPlateGirder_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IPlateGirder_get_HookPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_HookPoint(This,pVal) ) 

#define IPlateGirder_putref_HookPoint(This,newVal)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,newVal) ) 

#define IPlateGirder_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPlateGirder_INTERFACE_DEFINED__ */


#ifndef __IUBeam_INTERFACE_DEFINED__
#define __IUBeam_INTERFACE_DEFINED__

/* interface IUBeam */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUBeam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("231FB083-6FBE-417D-93E2-90C5FE345249")
    IUBeam : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D6( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D6( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D7( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D7( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_T( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Slope( 
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *slope) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopWidth( 
            /* [retval][out] */ Float64 *width) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [retval][out] */ Float64 *width) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebLocation( 
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *location) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebSpacing( 
            /* [retval][out] */ Float64 *spacing) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUBeamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUBeam * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUBeam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUBeam * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W1 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W1 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W2 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W2 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W3 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W3 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W4 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W4 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W5 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W5 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D1 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D1 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D2 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D2 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D3 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D3 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D4 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D4 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D5 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D5 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D6 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D6 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D7 )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D7 )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_T )( 
            IUBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IUBeam * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IUBeam * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IUBeam * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IUBeam * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IUBeam * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            IUBeam * This,
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *slope);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopWidth )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebLocation )( 
            IUBeam * This,
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebSpacing )( 
            IUBeam * This,
            /* [retval][out] */ Float64 *spacing);
        
        END_INTERFACE
    } IUBeamVtbl;

    interface IUBeam
    {
        CONST_VTBL struct IUBeamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUBeam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUBeam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUBeam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUBeam_get_W1(This,pVal)	\
    ( (This)->lpVtbl -> get_W1(This,pVal) ) 

#define IUBeam_put_W1(This,newVal)	\
    ( (This)->lpVtbl -> put_W1(This,newVal) ) 

#define IUBeam_get_W2(This,pVal)	\
    ( (This)->lpVtbl -> get_W2(This,pVal) ) 

#define IUBeam_put_W2(This,newVal)	\
    ( (This)->lpVtbl -> put_W2(This,newVal) ) 

#define IUBeam_get_W3(This,pVal)	\
    ( (This)->lpVtbl -> get_W3(This,pVal) ) 

#define IUBeam_put_W3(This,newVal)	\
    ( (This)->lpVtbl -> put_W3(This,newVal) ) 

#define IUBeam_get_W4(This,pVal)	\
    ( (This)->lpVtbl -> get_W4(This,pVal) ) 

#define IUBeam_put_W4(This,newVal)	\
    ( (This)->lpVtbl -> put_W4(This,newVal) ) 

#define IUBeam_get_W5(This,pVal)	\
    ( (This)->lpVtbl -> get_W5(This,pVal) ) 

#define IUBeam_put_W5(This,newVal)	\
    ( (This)->lpVtbl -> put_W5(This,newVal) ) 

#define IUBeam_get_D1(This,pVal)	\
    ( (This)->lpVtbl -> get_D1(This,pVal) ) 

#define IUBeam_put_D1(This,newVal)	\
    ( (This)->lpVtbl -> put_D1(This,newVal) ) 

#define IUBeam_get_D2(This,pVal)	\
    ( (This)->lpVtbl -> get_D2(This,pVal) ) 

#define IUBeam_put_D2(This,newVal)	\
    ( (This)->lpVtbl -> put_D2(This,newVal) ) 

#define IUBeam_get_D3(This,pVal)	\
    ( (This)->lpVtbl -> get_D3(This,pVal) ) 

#define IUBeam_put_D3(This,newVal)	\
    ( (This)->lpVtbl -> put_D3(This,newVal) ) 

#define IUBeam_get_D4(This,pVal)	\
    ( (This)->lpVtbl -> get_D4(This,pVal) ) 

#define IUBeam_put_D4(This,newVal)	\
    ( (This)->lpVtbl -> put_D4(This,newVal) ) 

#define IUBeam_get_D5(This,pVal)	\
    ( (This)->lpVtbl -> get_D5(This,pVal) ) 

#define IUBeam_put_D5(This,newVal)	\
    ( (This)->lpVtbl -> put_D5(This,newVal) ) 

#define IUBeam_get_D6(This,pVal)	\
    ( (This)->lpVtbl -> get_D6(This,pVal) ) 

#define IUBeam_put_D6(This,newVal)	\
    ( (This)->lpVtbl -> put_D6(This,newVal) ) 

#define IUBeam_get_D7(This,pVal)	\
    ( (This)->lpVtbl -> get_D7(This,pVal) ) 

#define IUBeam_put_D7(This,newVal)	\
    ( (This)->lpVtbl -> put_D7(This,newVal) ) 

#define IUBeam_get_T(This,pVal)	\
    ( (This)->lpVtbl -> get_T(This,pVal) ) 

#define IUBeam_put_T(This,newVal)	\
    ( (This)->lpVtbl -> put_T(This,newVal) ) 

#define IUBeam_get_HookPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_HookPoint(This,pVal) ) 

#define IUBeam_putref_HookPoint(This,newVal)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,newVal) ) 

#define IUBeam_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define IUBeam_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IUBeam_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IUBeam_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define IUBeam_get_Slope(This,webIdx,slope)	\
    ( (This)->lpVtbl -> get_Slope(This,webIdx,slope) ) 

#define IUBeam_get_TopWidth(This,width)	\
    ( (This)->lpVtbl -> get_TopWidth(This,width) ) 

#define IUBeam_get_TopFlangeWidth(This,width)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,width) ) 

#define IUBeam_get_WebLocation(This,webIdx,location)	\
    ( (This)->lpVtbl -> get_WebLocation(This,webIdx,location) ) 

#define IUBeam_get_WebSpacing(This,spacing)	\
    ( (This)->lpVtbl -> get_WebSpacing(This,spacing) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUBeam_INTERFACE_DEFINED__ */


#ifndef __IUBeam2_INTERFACE_DEFINED__
#define __IUBeam2_INTERFACE_DEFINED__

/* interface IUBeam2 */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUBeam2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4A262C68-AE3A-405f-A7E9-7A7BA09B70ED")
    IUBeam2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W6( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W6( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W7( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W7( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_D6( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_D6( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Slope( 
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *slope) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopWidth( 
            /* [retval][out] */ Float64 *width) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [retval][out] */ Float64 *width) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebLocation( 
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *location) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebSpacing( 
            /* [retval][out] */ Float64 *spacing) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_UseOutlineOnly( 
            /* [in] */ VARIANT_BOOL bUseOutlineOnly) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UseOutlineOnly( 
            /* [retval][out] */ VARIANT_BOOL *bUseOutlineOnly) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUBeam2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUBeam2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUBeam2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUBeam2 * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W1 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W1 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W2 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W2 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W3 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W3 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W4 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W4 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W5 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W5 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W6 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W6 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W7 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W7 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D1 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D1 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D2 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D2 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D3 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D3 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D4 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D4 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D5 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D5 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_D6 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_D6 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C1 )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C1 )( 
            IUBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IUBeam2 * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IUBeam2 * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IUBeam2 * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IUBeam2 * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            IUBeam2 * This,
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *slope);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopWidth )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebLocation )( 
            IUBeam2 * This,
            /* [in] */ WebIndexType webIdx,
            /* [retval][out] */ Float64 *location);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebSpacing )( 
            IUBeam2 * This,
            /* [retval][out] */ Float64 *spacing);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IUBeam2 * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseOutlineOnly )( 
            IUBeam2 * This,
            /* [in] */ VARIANT_BOOL bUseOutlineOnly);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseOutlineOnly )( 
            IUBeam2 * This,
            /* [retval][out] */ VARIANT_BOOL *bUseOutlineOnly);
        
        END_INTERFACE
    } IUBeam2Vtbl;

    interface IUBeam2
    {
        CONST_VTBL struct IUBeam2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUBeam2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUBeam2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUBeam2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUBeam2_get_W1(This,pVal)	\
    ( (This)->lpVtbl -> get_W1(This,pVal) ) 

#define IUBeam2_put_W1(This,newVal)	\
    ( (This)->lpVtbl -> put_W1(This,newVal) ) 

#define IUBeam2_get_W2(This,pVal)	\
    ( (This)->lpVtbl -> get_W2(This,pVal) ) 

#define IUBeam2_put_W2(This,newVal)	\
    ( (This)->lpVtbl -> put_W2(This,newVal) ) 

#define IUBeam2_get_W3(This,pVal)	\
    ( (This)->lpVtbl -> get_W3(This,pVal) ) 

#define IUBeam2_put_W3(This,newVal)	\
    ( (This)->lpVtbl -> put_W3(This,newVal) ) 

#define IUBeam2_get_W4(This,pVal)	\
    ( (This)->lpVtbl -> get_W4(This,pVal) ) 

#define IUBeam2_put_W4(This,newVal)	\
    ( (This)->lpVtbl -> put_W4(This,newVal) ) 

#define IUBeam2_get_W5(This,pVal)	\
    ( (This)->lpVtbl -> get_W5(This,pVal) ) 

#define IUBeam2_put_W5(This,newVal)	\
    ( (This)->lpVtbl -> put_W5(This,newVal) ) 

#define IUBeam2_get_W6(This,pVal)	\
    ( (This)->lpVtbl -> get_W6(This,pVal) ) 

#define IUBeam2_put_W6(This,newVal)	\
    ( (This)->lpVtbl -> put_W6(This,newVal) ) 

#define IUBeam2_get_W7(This,pVal)	\
    ( (This)->lpVtbl -> get_W7(This,pVal) ) 

#define IUBeam2_put_W7(This,newVal)	\
    ( (This)->lpVtbl -> put_W7(This,newVal) ) 

#define IUBeam2_get_D1(This,pVal)	\
    ( (This)->lpVtbl -> get_D1(This,pVal) ) 

#define IUBeam2_put_D1(This,newVal)	\
    ( (This)->lpVtbl -> put_D1(This,newVal) ) 

#define IUBeam2_get_D2(This,pVal)	\
    ( (This)->lpVtbl -> get_D2(This,pVal) ) 

#define IUBeam2_put_D2(This,newVal)	\
    ( (This)->lpVtbl -> put_D2(This,newVal) ) 

#define IUBeam2_get_D3(This,pVal)	\
    ( (This)->lpVtbl -> get_D3(This,pVal) ) 

#define IUBeam2_put_D3(This,newVal)	\
    ( (This)->lpVtbl -> put_D3(This,newVal) ) 

#define IUBeam2_get_D4(This,pVal)	\
    ( (This)->lpVtbl -> get_D4(This,pVal) ) 

#define IUBeam2_put_D4(This,newVal)	\
    ( (This)->lpVtbl -> put_D4(This,newVal) ) 

#define IUBeam2_get_D5(This,pVal)	\
    ( (This)->lpVtbl -> get_D5(This,pVal) ) 

#define IUBeam2_put_D5(This,newVal)	\
    ( (This)->lpVtbl -> put_D5(This,newVal) ) 

#define IUBeam2_get_D6(This,pVal)	\
    ( (This)->lpVtbl -> get_D6(This,pVal) ) 

#define IUBeam2_put_D6(This,newVal)	\
    ( (This)->lpVtbl -> put_D6(This,newVal) ) 

#define IUBeam2_get_C1(This,pVal)	\
    ( (This)->lpVtbl -> get_C1(This,pVal) ) 

#define IUBeam2_put_C1(This,newVal)	\
    ( (This)->lpVtbl -> put_C1(This,newVal) ) 

#define IUBeam2_get_T(This,pVal)	\
    ( (This)->lpVtbl -> get_T(This,pVal) ) 

#define IUBeam2_get_HookPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_HookPoint(This,pVal) ) 

#define IUBeam2_putref_HookPoint(This,newVal)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,newVal) ) 

#define IUBeam2_get_Height(This,pVal)	\
    ( (This)->lpVtbl -> get_Height(This,pVal) ) 

#define IUBeam2_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IUBeam2_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IUBeam2_get_Slope(This,webIdx,slope)	\
    ( (This)->lpVtbl -> get_Slope(This,webIdx,slope) ) 

#define IUBeam2_get_TopWidth(This,width)	\
    ( (This)->lpVtbl -> get_TopWidth(This,width) ) 

#define IUBeam2_get_TopFlangeWidth(This,width)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,width) ) 

#define IUBeam2_get_WebLocation(This,webIdx,location)	\
    ( (This)->lpVtbl -> get_WebLocation(This,webIdx,location) ) 

#define IUBeam2_get_WebSpacing(This,spacing)	\
    ( (This)->lpVtbl -> get_WebSpacing(This,spacing) ) 

#define IUBeam2_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define IUBeam2_put_UseOutlineOnly(This,bUseOutlineOnly)	\
    ( (This)->lpVtbl -> put_UseOutlineOnly(This,bUseOutlineOnly) ) 

#define IUBeam2_get_UseOutlineOnly(This,bUseOutlineOnly)	\
    ( (This)->lpVtbl -> get_UseOutlineOnly(This,bUseOutlineOnly) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUBeam2_INTERFACE_DEFINED__ */


#ifndef __ICompositeShapeItem_INTERFACE_DEFINED__
#define __ICompositeShapeItem_INTERFACE_DEFINED__

/* interface ICompositeShapeItem */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICompositeShapeItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A76E22D6-6C41-49d8-94C2-10D10CF0DB04")
    ICompositeShapeItem : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Shape( 
            /* [in] */ IShape *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Void( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Void( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICompositeShapeItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICompositeShapeItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICompositeShapeItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICompositeShapeItem * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ICompositeShapeItem * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Shape )( 
            ICompositeShapeItem * This,
            /* [in] */ IShape *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Void )( 
            ICompositeShapeItem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Void )( 
            ICompositeShapeItem * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICompositeShapeItem * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICompositeShapeItemVtbl;

    interface ICompositeShapeItem
    {
        CONST_VTBL struct ICompositeShapeItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICompositeShapeItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICompositeShapeItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICompositeShapeItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICompositeShapeItem_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define ICompositeShapeItem_putref_Shape(This,newVal)	\
    ( (This)->lpVtbl -> putref_Shape(This,newVal) ) 

#define ICompositeShapeItem_get_Void(This,pVal)	\
    ( (This)->lpVtbl -> get_Void(This,pVal) ) 

#define ICompositeShapeItem_put_Void(This,newVal)	\
    ( (This)->lpVtbl -> put_Void(This,newVal) ) 

#define ICompositeShapeItem_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICompositeShapeItem_INTERFACE_DEFINED__ */


#ifndef __ICompositeShape_INTERFACE_DEFINED__
#define __ICompositeShape_INTERFACE_DEFINED__

/* interface ICompositeShape */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICompositeShape;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0BAF0D09-6A8D-4818-AAA6-C5B72C3641FE")
    ICompositeShape : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ICompositeShapeItem **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *shape,
            /* [in] */ VARIANT_BOOL bVoid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddShapeEx( 
            /* [in] */ ICompositeShapeItem *shapeItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Replace( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IShape *pShape) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReplaceEx( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ ICompositeShapeItem *pShapeItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICompositeShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICompositeShape * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICompositeShape * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICompositeShape * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ICompositeShape * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ICompositeShape * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ICompositeShapeItem **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            ICompositeShape * This,
            /* [in] */ IShape *shape,
            /* [in] */ VARIANT_BOOL bVoid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddShapeEx )( 
            ICompositeShape * This,
            /* [in] */ ICompositeShapeItem *shapeItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Replace )( 
            ICompositeShape * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IShape *pShape);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReplaceEx )( 
            ICompositeShape * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ ICompositeShapeItem *pShapeItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ICompositeShape * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ICompositeShape * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICompositeShape * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ICompositeShape * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICompositeShape * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICompositeShapeVtbl;

    interface ICompositeShape
    {
        CONST_VTBL struct ICompositeShapeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICompositeShape_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICompositeShape_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICompositeShape_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICompositeShape_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define ICompositeShape_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define ICompositeShape_AddShape(This,shape,bVoid)	\
    ( (This)->lpVtbl -> AddShape(This,shape,bVoid) ) 

#define ICompositeShape_AddShapeEx(This,shapeItem)	\
    ( (This)->lpVtbl -> AddShapeEx(This,shapeItem) ) 

#define ICompositeShape_Replace(This,idx,pShape)	\
    ( (This)->lpVtbl -> Replace(This,idx,pShape) ) 

#define ICompositeShape_ReplaceEx(This,idx,pShapeItem)	\
    ( (This)->lpVtbl -> ReplaceEx(This,idx,pShapeItem) ) 

#define ICompositeShape_Remove(This,idx)	\
    ( (This)->lpVtbl -> Remove(This,idx) ) 

#define ICompositeShape_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ICompositeShape_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ICompositeShape_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define ICompositeShape_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICompositeShape_INTERFACE_DEFINED__ */


#ifndef __IVoidedSlab_INTERFACE_DEFINED__
#define __IVoidedSlab_INTERFACE_DEFINED__

/* interface IVoidedSlab */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVoidedSlab;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("82ABF099-2BCB-4119-AAFC-C3E6B04624C7")
    IVoidedSlab : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ Float64 h) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *h) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ Float64 w) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ Float64 *w) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VoidDiameter( 
            /* [in] */ Float64 d) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VoidDiameter( 
            /* [retval][out] */ Float64 *d) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VoidSpacing( 
            /* [in] */ Float64 s) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VoidSpacing( 
            /* [retval][out] */ Float64 *s) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VoidCount( 
            /* [in] */ CollectionIndexType nv) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VoidCount( 
            /* [retval][out] */ CollectionIndexType *nv) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVoidedSlabVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVoidedSlab * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVoidedSlab * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVoidedSlab * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IVoidedSlab * This,
            /* [in] */ Float64 h);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IVoidedSlab * This,
            /* [retval][out] */ Float64 *h);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IVoidedSlab * This,
            /* [in] */ Float64 w);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IVoidedSlab * This,
            /* [retval][out] */ Float64 *w);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VoidDiameter )( 
            IVoidedSlab * This,
            /* [in] */ Float64 d);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VoidDiameter )( 
            IVoidedSlab * This,
            /* [retval][out] */ Float64 *d);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VoidSpacing )( 
            IVoidedSlab * This,
            /* [in] */ Float64 s);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VoidSpacing )( 
            IVoidedSlab * This,
            /* [retval][out] */ Float64 *s);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VoidCount )( 
            IVoidedSlab * This,
            /* [in] */ CollectionIndexType nv);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VoidCount )( 
            IVoidedSlab * This,
            /* [retval][out] */ CollectionIndexType *nv);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IVoidedSlab * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IVoidedSlab * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IVoidedSlab * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IVoidedSlab * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IVoidedSlab * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IVoidedSlabVtbl;

    interface IVoidedSlab
    {
        CONST_VTBL struct IVoidedSlabVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoidedSlab_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVoidedSlab_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVoidedSlab_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVoidedSlab_put_Height(This,h)	\
    ( (This)->lpVtbl -> put_Height(This,h) ) 

#define IVoidedSlab_get_Height(This,h)	\
    ( (This)->lpVtbl -> get_Height(This,h) ) 

#define IVoidedSlab_put_Width(This,w)	\
    ( (This)->lpVtbl -> put_Width(This,w) ) 

#define IVoidedSlab_get_Width(This,w)	\
    ( (This)->lpVtbl -> get_Width(This,w) ) 

#define IVoidedSlab_put_VoidDiameter(This,d)	\
    ( (This)->lpVtbl -> put_VoidDiameter(This,d) ) 

#define IVoidedSlab_get_VoidDiameter(This,d)	\
    ( (This)->lpVtbl -> get_VoidDiameter(This,d) ) 

#define IVoidedSlab_put_VoidSpacing(This,s)	\
    ( (This)->lpVtbl -> put_VoidSpacing(This,s) ) 

#define IVoidedSlab_get_VoidSpacing(This,s)	\
    ( (This)->lpVtbl -> get_VoidSpacing(This,s) ) 

#define IVoidedSlab_put_VoidCount(This,nv)	\
    ( (This)->lpVtbl -> put_VoidCount(This,nv) ) 

#define IVoidedSlab_get_VoidCount(This,nv)	\
    ( (This)->lpVtbl -> get_VoidCount(This,nv) ) 

#define IVoidedSlab_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define IVoidedSlab_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define IVoidedSlab_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IVoidedSlab_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IVoidedSlab_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVoidedSlab_INTERFACE_DEFINED__ */


#ifndef __IVoidedSlab2_INTERFACE_DEFINED__
#define __IVoidedSlab2_INTERFACE_DEFINED__

/* interface IVoidedSlab2 */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVoidedSlab2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F8EC30FA-8C49-4b8d-AA93-B0D83A785142")
    IVoidedSlab2 : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ Float64 h) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ Float64 *h) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ Float64 w) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ Float64 *w) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C1( 
            /* [in] */ Float64 c1) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C1( 
            /* [retval][out] */ Float64 *c1) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C2( 
            /* [in] */ Float64 c2) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C2( 
            /* [retval][out] */ Float64 *c2) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C3( 
            /* [in] */ Float64 c3) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C3( 
            /* [retval][out] */ Float64 *c3) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LeftBlockOut( 
            /* [in] */ VARIANT_BOOL bLeftBlockOut) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftBlockOut( 
            /* [retval][out] */ VARIANT_BOOL *pbLeftBlockOut) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RightBlockOut( 
            /* [in] */ VARIANT_BOOL bRightBlockOut) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightBlockOut( 
            /* [retval][out] */ VARIANT_BOOL *pbRightBlockOut) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ExteriorVoidDiameter( 
            /* [in] */ Float64 d) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExteriorVoidDiameter( 
            /* [retval][out] */ Float64 *d) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_InteriorVoidDiameter( 
            /* [in] */ Float64 d) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InteriorVoidDiameter( 
            /* [retval][out] */ Float64 *d) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ExteriorVoidSpacing( 
            /* [in] */ Float64 s) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExteriorVoidSpacing( 
            /* [retval][out] */ Float64 *s) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_InteriorVoidSpacing( 
            /* [in] */ Float64 s) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InteriorVoidSpacing( 
            /* [retval][out] */ Float64 *s) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ExteriorVoidElevation( 
            /* [in] */ Float64 h1) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExteriorVoidElevation( 
            /* [retval][out] */ Float64 *h1) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_InteriorVoidElevation( 
            /* [in] */ Float64 h2) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InteriorVoidElevation( 
            /* [retval][out] */ Float64 *h2) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VoidCount( 
            /* [in] */ CollectionIndexType nv) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VoidCount( 
            /* [retval][out] */ CollectionIndexType *nv) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVoidedSlab2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVoidedSlab2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVoidedSlab2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVoidedSlab2 * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 h);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *h);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 w);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *w);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C1 )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 c1);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C1 )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *c1);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C2 )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 c2);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C2 )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *c2);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C3 )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 c3);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C3 )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *c3);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LeftBlockOut )( 
            IVoidedSlab2 * This,
            /* [in] */ VARIANT_BOOL bLeftBlockOut);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftBlockOut )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbLeftBlockOut);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RightBlockOut )( 
            IVoidedSlab2 * This,
            /* [in] */ VARIANT_BOOL bRightBlockOut);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightBlockOut )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ VARIANT_BOOL *pbRightBlockOut);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExteriorVoidDiameter )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 d);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExteriorVoidDiameter )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *d);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InteriorVoidDiameter )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 d);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InteriorVoidDiameter )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *d);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExteriorVoidSpacing )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 s);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExteriorVoidSpacing )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *s);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InteriorVoidSpacing )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 s);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InteriorVoidSpacing )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *s);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExteriorVoidElevation )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 h1);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExteriorVoidElevation )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *h1);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InteriorVoidElevation )( 
            IVoidedSlab2 * This,
            /* [in] */ Float64 h2);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InteriorVoidElevation )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ Float64 *h2);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VoidCount )( 
            IVoidedSlab2 * This,
            /* [in] */ CollectionIndexType nv);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VoidCount )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ CollectionIndexType *nv);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IVoidedSlab2 * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IVoidedSlab2 * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IVoidedSlab2Vtbl;

    interface IVoidedSlab2
    {
        CONST_VTBL struct IVoidedSlab2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoidedSlab2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVoidedSlab2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVoidedSlab2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVoidedSlab2_put_Height(This,h)	\
    ( (This)->lpVtbl -> put_Height(This,h) ) 

#define IVoidedSlab2_get_Height(This,h)	\
    ( (This)->lpVtbl -> get_Height(This,h) ) 

#define IVoidedSlab2_put_Width(This,w)	\
    ( (This)->lpVtbl -> put_Width(This,w) ) 

#define IVoidedSlab2_get_Width(This,w)	\
    ( (This)->lpVtbl -> get_Width(This,w) ) 

#define IVoidedSlab2_put_C1(This,c1)	\
    ( (This)->lpVtbl -> put_C1(This,c1) ) 

#define IVoidedSlab2_get_C1(This,c1)	\
    ( (This)->lpVtbl -> get_C1(This,c1) ) 

#define IVoidedSlab2_put_C2(This,c2)	\
    ( (This)->lpVtbl -> put_C2(This,c2) ) 

#define IVoidedSlab2_get_C2(This,c2)	\
    ( (This)->lpVtbl -> get_C2(This,c2) ) 

#define IVoidedSlab2_put_C3(This,c3)	\
    ( (This)->lpVtbl -> put_C3(This,c3) ) 

#define IVoidedSlab2_get_C3(This,c3)	\
    ( (This)->lpVtbl -> get_C3(This,c3) ) 

#define IVoidedSlab2_put_LeftBlockOut(This,bLeftBlockOut)	\
    ( (This)->lpVtbl -> put_LeftBlockOut(This,bLeftBlockOut) ) 

#define IVoidedSlab2_get_LeftBlockOut(This,pbLeftBlockOut)	\
    ( (This)->lpVtbl -> get_LeftBlockOut(This,pbLeftBlockOut) ) 

#define IVoidedSlab2_put_RightBlockOut(This,bRightBlockOut)	\
    ( (This)->lpVtbl -> put_RightBlockOut(This,bRightBlockOut) ) 

#define IVoidedSlab2_get_RightBlockOut(This,pbRightBlockOut)	\
    ( (This)->lpVtbl -> get_RightBlockOut(This,pbRightBlockOut) ) 

#define IVoidedSlab2_put_ExteriorVoidDiameter(This,d)	\
    ( (This)->lpVtbl -> put_ExteriorVoidDiameter(This,d) ) 

#define IVoidedSlab2_get_ExteriorVoidDiameter(This,d)	\
    ( (This)->lpVtbl -> get_ExteriorVoidDiameter(This,d) ) 

#define IVoidedSlab2_put_InteriorVoidDiameter(This,d)	\
    ( (This)->lpVtbl -> put_InteriorVoidDiameter(This,d) ) 

#define IVoidedSlab2_get_InteriorVoidDiameter(This,d)	\
    ( (This)->lpVtbl -> get_InteriorVoidDiameter(This,d) ) 

#define IVoidedSlab2_put_ExteriorVoidSpacing(This,s)	\
    ( (This)->lpVtbl -> put_ExteriorVoidSpacing(This,s) ) 

#define IVoidedSlab2_get_ExteriorVoidSpacing(This,s)	\
    ( (This)->lpVtbl -> get_ExteriorVoidSpacing(This,s) ) 

#define IVoidedSlab2_put_InteriorVoidSpacing(This,s)	\
    ( (This)->lpVtbl -> put_InteriorVoidSpacing(This,s) ) 

#define IVoidedSlab2_get_InteriorVoidSpacing(This,s)	\
    ( (This)->lpVtbl -> get_InteriorVoidSpacing(This,s) ) 

#define IVoidedSlab2_put_ExteriorVoidElevation(This,h1)	\
    ( (This)->lpVtbl -> put_ExteriorVoidElevation(This,h1) ) 

#define IVoidedSlab2_get_ExteriorVoidElevation(This,h1)	\
    ( (This)->lpVtbl -> get_ExteriorVoidElevation(This,h1) ) 

#define IVoidedSlab2_put_InteriorVoidElevation(This,h2)	\
    ( (This)->lpVtbl -> put_InteriorVoidElevation(This,h2) ) 

#define IVoidedSlab2_get_InteriorVoidElevation(This,h2)	\
    ( (This)->lpVtbl -> get_InteriorVoidElevation(This,h2) ) 

#define IVoidedSlab2_put_VoidCount(This,nv)	\
    ( (This)->lpVtbl -> put_VoidCount(This,nv) ) 

#define IVoidedSlab2_get_VoidCount(This,nv)	\
    ( (This)->lpVtbl -> get_VoidCount(This,nv) ) 

#define IVoidedSlab2_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define IVoidedSlab2_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define IVoidedSlab2_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IVoidedSlab2_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IVoidedSlab2_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVoidedSlab2_INTERFACE_DEFINED__ */


#ifndef __IBoxBeam_INTERFACE_DEFINED__
#define __IBoxBeam_INTERFACE_DEFINED__

/* interface IBoxBeam */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IBoxBeam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DD2E8D6C-2EC0-4370-AC01-11EA0C01294C")
    IBoxBeam : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H3( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H3( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H4( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H4( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H5( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H5( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H6( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H6( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H7( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_H7( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_F1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_F1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_F2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_F2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VoidCount( 
            /* [in] */ CollectionIndexType nv) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VoidCount( 
            /* [retval][out] */ CollectionIndexType *nv) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WebWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopFlangeWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LeftBlockOut( 
            /* [in] */ VARIANT_BOOL bLeftBlockOut) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftBlockOut( 
            /* [retval][out] */ VARIANT_BOOL *pbLeftBlockOut) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RightBlockOut( 
            /* [in] */ VARIANT_BOOL bRightBlockOut) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightBlockOut( 
            /* [retval][out] */ VARIANT_BOOL *pbRightBlockOut) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_UseOverallWidth( 
            /* [in] */ VARIANT_BOOL bUseOverallWidth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UseOverallWidth( 
            /* [retval][out] */ VARIANT_BOOL *pbUseOverallWidth) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBoxBeamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBoxBeam * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBoxBeam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBoxBeam * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W1 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W1 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W2 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W2 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W3 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W3 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W4 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W4 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H1 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H1 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H2 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H2 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H3 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H3 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H4 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H4 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H5 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H5 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H6 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H6 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H7 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_H7 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_F1 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_F1 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_F2 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_F2 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C1 )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C1 )( 
            IBoxBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VoidCount )( 
            IBoxBeam * This,
            /* [in] */ CollectionIndexType nv);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VoidCount )( 
            IBoxBeam * This,
            /* [retval][out] */ CollectionIndexType *nv);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IBoxBeam * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IBoxBeam * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebWidth )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomFlangeWidth )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopFlangeWidth )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IBoxBeam * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IBoxBeam * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IBoxBeam * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LeftBlockOut )( 
            IBoxBeam * This,
            /* [in] */ VARIANT_BOOL bLeftBlockOut);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftBlockOut )( 
            IBoxBeam * This,
            /* [retval][out] */ VARIANT_BOOL *pbLeftBlockOut);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RightBlockOut )( 
            IBoxBeam * This,
            /* [in] */ VARIANT_BOOL bRightBlockOut);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightBlockOut )( 
            IBoxBeam * This,
            /* [retval][out] */ VARIANT_BOOL *pbRightBlockOut);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IBoxBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseOverallWidth )( 
            IBoxBeam * This,
            /* [in] */ VARIANT_BOOL bUseOverallWidth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseOverallWidth )( 
            IBoxBeam * This,
            /* [retval][out] */ VARIANT_BOOL *pbUseOverallWidth);
        
        END_INTERFACE
    } IBoxBeamVtbl;

    interface IBoxBeam
    {
        CONST_VTBL struct IBoxBeamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBoxBeam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBoxBeam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBoxBeam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBoxBeam_get_W1(This,pVal)	\
    ( (This)->lpVtbl -> get_W1(This,pVal) ) 

#define IBoxBeam_put_W1(This,newVal)	\
    ( (This)->lpVtbl -> put_W1(This,newVal) ) 

#define IBoxBeam_get_W2(This,pVal)	\
    ( (This)->lpVtbl -> get_W2(This,pVal) ) 

#define IBoxBeam_put_W2(This,newVal)	\
    ( (This)->lpVtbl -> put_W2(This,newVal) ) 

#define IBoxBeam_get_W3(This,pVal)	\
    ( (This)->lpVtbl -> get_W3(This,pVal) ) 

#define IBoxBeam_put_W3(This,newVal)	\
    ( (This)->lpVtbl -> put_W3(This,newVal) ) 

#define IBoxBeam_get_W4(This,pVal)	\
    ( (This)->lpVtbl -> get_W4(This,pVal) ) 

#define IBoxBeam_put_W4(This,newVal)	\
    ( (This)->lpVtbl -> put_W4(This,newVal) ) 

#define IBoxBeam_get_H1(This,pVal)	\
    ( (This)->lpVtbl -> get_H1(This,pVal) ) 

#define IBoxBeam_put_H1(This,newVal)	\
    ( (This)->lpVtbl -> put_H1(This,newVal) ) 

#define IBoxBeam_get_H2(This,pVal)	\
    ( (This)->lpVtbl -> get_H2(This,pVal) ) 

#define IBoxBeam_put_H2(This,newVal)	\
    ( (This)->lpVtbl -> put_H2(This,newVal) ) 

#define IBoxBeam_get_H3(This,pVal)	\
    ( (This)->lpVtbl -> get_H3(This,pVal) ) 

#define IBoxBeam_put_H3(This,newVal)	\
    ( (This)->lpVtbl -> put_H3(This,newVal) ) 

#define IBoxBeam_get_H4(This,pVal)	\
    ( (This)->lpVtbl -> get_H4(This,pVal) ) 

#define IBoxBeam_put_H4(This,newVal)	\
    ( (This)->lpVtbl -> put_H4(This,newVal) ) 

#define IBoxBeam_get_H5(This,pVal)	\
    ( (This)->lpVtbl -> get_H5(This,pVal) ) 

#define IBoxBeam_put_H5(This,newVal)	\
    ( (This)->lpVtbl -> put_H5(This,newVal) ) 

#define IBoxBeam_get_H6(This,pVal)	\
    ( (This)->lpVtbl -> get_H6(This,pVal) ) 

#define IBoxBeam_put_H6(This,newVal)	\
    ( (This)->lpVtbl -> put_H6(This,newVal) ) 

#define IBoxBeam_get_H7(This,pVal)	\
    ( (This)->lpVtbl -> get_H7(This,pVal) ) 

#define IBoxBeam_put_H7(This,newVal)	\
    ( (This)->lpVtbl -> put_H7(This,newVal) ) 

#define IBoxBeam_get_F1(This,pVal)	\
    ( (This)->lpVtbl -> get_F1(This,pVal) ) 

#define IBoxBeam_put_F1(This,newVal)	\
    ( (This)->lpVtbl -> put_F1(This,newVal) ) 

#define IBoxBeam_get_F2(This,pVal)	\
    ( (This)->lpVtbl -> get_F2(This,pVal) ) 

#define IBoxBeam_put_F2(This,newVal)	\
    ( (This)->lpVtbl -> put_F2(This,newVal) ) 

#define IBoxBeam_get_C1(This,pVal)	\
    ( (This)->lpVtbl -> get_C1(This,pVal) ) 

#define IBoxBeam_put_C1(This,newVal)	\
    ( (This)->lpVtbl -> put_C1(This,newVal) ) 

#define IBoxBeam_put_VoidCount(This,nv)	\
    ( (This)->lpVtbl -> put_VoidCount(This,nv) ) 

#define IBoxBeam_get_VoidCount(This,nv)	\
    ( (This)->lpVtbl -> get_VoidCount(This,nv) ) 

#define IBoxBeam_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define IBoxBeam_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define IBoxBeam_get_WebWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_WebWidth(This,pVal) ) 

#define IBoxBeam_get_BottomFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomFlangeWidth(This,pVal) ) 

#define IBoxBeam_get_TopFlangeWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_TopFlangeWidth(This,pVal) ) 

#define IBoxBeam_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IBoxBeam_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IBoxBeam_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#define IBoxBeam_put_LeftBlockOut(This,bLeftBlockOut)	\
    ( (This)->lpVtbl -> put_LeftBlockOut(This,bLeftBlockOut) ) 

#define IBoxBeam_get_LeftBlockOut(This,pbLeftBlockOut)	\
    ( (This)->lpVtbl -> get_LeftBlockOut(This,pbLeftBlockOut) ) 

#define IBoxBeam_put_RightBlockOut(This,bRightBlockOut)	\
    ( (This)->lpVtbl -> put_RightBlockOut(This,bRightBlockOut) ) 

#define IBoxBeam_get_RightBlockOut(This,pbRightBlockOut)	\
    ( (This)->lpVtbl -> get_RightBlockOut(This,pbRightBlockOut) ) 

#define IBoxBeam_get_Width(This,pVal)	\
    ( (This)->lpVtbl -> get_Width(This,pVal) ) 

#define IBoxBeam_put_UseOverallWidth(This,bUseOverallWidth)	\
    ( (This)->lpVtbl -> put_UseOverallWidth(This,bUseOverallWidth) ) 

#define IBoxBeam_get_UseOverallWidth(This,pbUseOverallWidth)	\
    ( (This)->lpVtbl -> get_UseOverallWidth(This,pbUseOverallWidth) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBoxBeam_INTERFACE_DEFINED__ */


#ifndef __IDeckedSlabBeam_INTERFACE_DEFINED__
#define __IDeckedSlabBeam_INTERFACE_DEFINED__

/* interface IDeckedSlabBeam */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDeckedSlabBeam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ED1C099C-E020-408c-B9B5-952E0DAAB8D6")
    IDeckedSlabBeam : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_A( 
            /* [in] */ Float64 a) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_A( 
            /* [retval][out] */ Float64 *a) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_B( 
            /* [in] */ Float64 b) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_B( 
            /* [retval][out] */ Float64 *b) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_C( 
            /* [in] */ Float64 c) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_C( 
            /* [retval][out] */ Float64 *c) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_W( 
            /* [in] */ Float64 W) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_W( 
            /* [retval][out] */ Float64 *W) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tt( 
            /* [in] */ Float64 Tt) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tt( 
            /* [retval][out] */ Float64 *Tt) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Tb( 
            /* [in] */ Float64 Tb) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tb( 
            /* [retval][out] */ Float64 *Tb) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_F( 
            /* [in] */ Float64 F) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_F( 
            /* [retval][out] */ Float64 *F) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LeftBlockOut( 
            /* [in] */ VARIANT_BOOL bLeftBlockOut) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftBlockOut( 
            /* [retval][out] */ VARIANT_BOOL *pbLeftBlockOut) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RightBlockOut( 
            /* [in] */ VARIANT_BOOL bRightBlockOut) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightBlockOut( 
            /* [retval][out] */ VARIANT_BOOL *pbRightBlockOut) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VoidCount( 
            /* [in] */ CollectionIndexType nv) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VoidCount( 
            /* [retval][out] */ CollectionIndexType *nv) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HookPoint( 
            /* [retval][out] */ IPoint2d **hookPnt) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HookPoint( 
            /* [in] */ IPoint2d *hookPnt) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDeckedSlabBeamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDeckedSlabBeam * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDeckedSlabBeam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDeckedSlabBeam * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_A )( 
            IDeckedSlabBeam * This,
            /* [in] */ Float64 a);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_A )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ Float64 *a);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_B )( 
            IDeckedSlabBeam * This,
            /* [in] */ Float64 b);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_B )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ Float64 *b);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_C )( 
            IDeckedSlabBeam * This,
            /* [in] */ Float64 c);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_C )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ Float64 *c);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_W )( 
            IDeckedSlabBeam * This,
            /* [in] */ Float64 W);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_W )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ Float64 *W);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Tt )( 
            IDeckedSlabBeam * This,
            /* [in] */ Float64 Tt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tt )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ Float64 *Tt);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Tb )( 
            IDeckedSlabBeam * This,
            /* [in] */ Float64 Tb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tb )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ Float64 *Tb);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_F )( 
            IDeckedSlabBeam * This,
            /* [in] */ Float64 F);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_F )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ Float64 *F);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LeftBlockOut )( 
            IDeckedSlabBeam * This,
            /* [in] */ VARIANT_BOOL bLeftBlockOut);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftBlockOut )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ VARIANT_BOOL *pbLeftBlockOut);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RightBlockOut )( 
            IDeckedSlabBeam * This,
            /* [in] */ VARIANT_BOOL bRightBlockOut);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightBlockOut )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ VARIANT_BOOL *pbRightBlockOut);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VoidCount )( 
            IDeckedSlabBeam * This,
            /* [in] */ CollectionIndexType nv);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VoidCount )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ CollectionIndexType *nv);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HookPoint )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ IPoint2d **hookPnt);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HookPoint )( 
            IDeckedSlabBeam * This,
            /* [in] */ IPoint2d *hookPnt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IDeckedSlabBeam * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IDeckedSlabBeamVtbl;

    interface IDeckedSlabBeam
    {
        CONST_VTBL struct IDeckedSlabBeamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDeckedSlabBeam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDeckedSlabBeam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDeckedSlabBeam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDeckedSlabBeam_put_A(This,a)	\
    ( (This)->lpVtbl -> put_A(This,a) ) 

#define IDeckedSlabBeam_get_A(This,a)	\
    ( (This)->lpVtbl -> get_A(This,a) ) 

#define IDeckedSlabBeam_put_B(This,b)	\
    ( (This)->lpVtbl -> put_B(This,b) ) 

#define IDeckedSlabBeam_get_B(This,b)	\
    ( (This)->lpVtbl -> get_B(This,b) ) 

#define IDeckedSlabBeam_put_C(This,c)	\
    ( (This)->lpVtbl -> put_C(This,c) ) 

#define IDeckedSlabBeam_get_C(This,c)	\
    ( (This)->lpVtbl -> get_C(This,c) ) 

#define IDeckedSlabBeam_put_W(This,W)	\
    ( (This)->lpVtbl -> put_W(This,W) ) 

#define IDeckedSlabBeam_get_W(This,W)	\
    ( (This)->lpVtbl -> get_W(This,W) ) 

#define IDeckedSlabBeam_put_Tt(This,Tt)	\
    ( (This)->lpVtbl -> put_Tt(This,Tt) ) 

#define IDeckedSlabBeam_get_Tt(This,Tt)	\
    ( (This)->lpVtbl -> get_Tt(This,Tt) ) 

#define IDeckedSlabBeam_put_Tb(This,Tb)	\
    ( (This)->lpVtbl -> put_Tb(This,Tb) ) 

#define IDeckedSlabBeam_get_Tb(This,Tb)	\
    ( (This)->lpVtbl -> get_Tb(This,Tb) ) 

#define IDeckedSlabBeam_put_F(This,F)	\
    ( (This)->lpVtbl -> put_F(This,F) ) 

#define IDeckedSlabBeam_get_F(This,F)	\
    ( (This)->lpVtbl -> get_F(This,F) ) 

#define IDeckedSlabBeam_put_LeftBlockOut(This,bLeftBlockOut)	\
    ( (This)->lpVtbl -> put_LeftBlockOut(This,bLeftBlockOut) ) 

#define IDeckedSlabBeam_get_LeftBlockOut(This,pbLeftBlockOut)	\
    ( (This)->lpVtbl -> get_LeftBlockOut(This,pbLeftBlockOut) ) 

#define IDeckedSlabBeam_put_RightBlockOut(This,bRightBlockOut)	\
    ( (This)->lpVtbl -> put_RightBlockOut(This,bRightBlockOut) ) 

#define IDeckedSlabBeam_get_RightBlockOut(This,pbRightBlockOut)	\
    ( (This)->lpVtbl -> get_RightBlockOut(This,pbRightBlockOut) ) 

#define IDeckedSlabBeam_put_VoidCount(This,nv)	\
    ( (This)->lpVtbl -> put_VoidCount(This,nv) ) 

#define IDeckedSlabBeam_get_VoidCount(This,nv)	\
    ( (This)->lpVtbl -> get_VoidCount(This,nv) ) 

#define IDeckedSlabBeam_get_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> get_HookPoint(This,hookPnt) ) 

#define IDeckedSlabBeam_putref_HookPoint(This,hookPnt)	\
    ( (This)->lpVtbl -> putref_HookPoint(This,hookPnt) ) 

#define IDeckedSlabBeam_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IDeckedSlabBeam_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IDeckedSlabBeam_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDeckedSlabBeam_INTERFACE_DEFINED__ */


#ifndef __IFasterPolyShape_INTERFACE_DEFINED__
#define __IFasterPolyShape_INTERFACE_DEFINED__

/* interface IFasterPolyShape */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFasterPolyShape;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8F4AC52C-4C4E-4015-934E-58E1C35DC39E")
    IFasterPolyShape : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddPoint( 
            /* [in] */ Float64 x,
            /* [in] */ Float64 y) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddPointEx( 
            /* [in] */ IPoint2d *pPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddPoints( 
            /* [in] */ IPoint2dCollection *pPoints) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ChangePoint( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemovePoint( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumPoints( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetPoint( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *pX,
            /* [out] */ Float64 *pY) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFasterPolyShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFasterPolyShape * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFasterPolyShape * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFasterPolyShape * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPoint )( 
            IFasterPolyShape * This,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPointEx )( 
            IFasterPolyShape * This,
            /* [in] */ IPoint2d *pPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPoints )( 
            IFasterPolyShape * This,
            /* [in] */ IPoint2dCollection *pPoints);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ChangePoint )( 
            IFasterPolyShape * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemovePoint )( 
            IFasterPolyShape * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IFasterPolyShape * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            IFasterPolyShape * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumPoints )( 
            IFasterPolyShape * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPoint )( 
            IFasterPolyShape * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *pX,
            /* [out] */ Float64 *pY);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFasterPolyShape * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IFasterPolyShape * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IFasterPolyShapeVtbl;

    interface IFasterPolyShape
    {
        CONST_VTBL struct IFasterPolyShapeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFasterPolyShape_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFasterPolyShape_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFasterPolyShape_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFasterPolyShape_AddPoint(This,x,y)	\
    ( (This)->lpVtbl -> AddPoint(This,x,y) ) 

#define IFasterPolyShape_AddPointEx(This,pPoint)	\
    ( (This)->lpVtbl -> AddPointEx(This,pPoint) ) 

#define IFasterPolyShape_AddPoints(This,pPoints)	\
    ( (This)->lpVtbl -> AddPoints(This,pPoints) ) 

#define IFasterPolyShape_ChangePoint(This,index,x,y)	\
    ( (This)->lpVtbl -> ChangePoint(This,index,x,y) ) 

#define IFasterPolyShape_RemovePoint(This,index)	\
    ( (This)->lpVtbl -> RemovePoint(This,index) ) 

#define IFasterPolyShape_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define IFasterPolyShape_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define IFasterPolyShape_get_NumPoints(This,pVal)	\
    ( (This)->lpVtbl -> get_NumPoints(This,pVal) ) 

#define IFasterPolyShape_GetPoint(This,index,pX,pY)	\
    ( (This)->lpVtbl -> GetPoint(This,index,pX,pY) ) 

#define IFasterPolyShape_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IFasterPolyShape_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFasterPolyShape_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Point2d;

#ifdef __cplusplus

class DECLSPEC_UUID("B0D56FA0-C8D6-11D2-8CDF-C55C1CA84A34")
Point2d;
#endif

EXTERN_C const CLSID CLSID_Size2d;

#ifdef __cplusplus

class DECLSPEC_UUID("B77D2444-96A0-11D2-88A7-006097C68A9C")
Size2d;
#endif

EXTERN_C const CLSID CLSID_Rect2d;

#ifdef __cplusplus

class DECLSPEC_UUID("B77D2446-96A0-11D2-88A7-006097C68A9C")
Rect2d;
#endif

EXTERN_C const CLSID CLSID_Vector2d;

#ifdef __cplusplus

class DECLSPEC_UUID("55B8EF84-FADF-11D2-8CDF-9849C70CC734")
Vector2d;
#endif

EXTERN_C const CLSID CLSID_Point2dCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("B77D2448-96A0-11D2-88A7-006097C68A9C")
Point2dCollection;
#endif

EXTERN_C const CLSID CLSID_LineSegment2d;

#ifdef __cplusplus

class DECLSPEC_UUID("546BBDC2-96C0-11D2-8D11-14830CC10000")
LineSegment2d;
#endif

EXTERN_C const CLSID CLSID_Line2d;

#ifdef __cplusplus

class DECLSPEC_UUID("D72D7403-F9DB-11D2-8CDF-444553540000")
Line2d;
#endif

EXTERN_C const CLSID CLSID_ShapeProperties;

#ifdef __cplusplus

class DECLSPEC_UUID("66172CA5-FF5A-11D2-8CDF-F43C3928A334")
ShapeProperties;
#endif

EXTERN_C const CLSID CLSID_PolyShape;

#ifdef __cplusplus

class DECLSPEC_UUID("94FD8E64-0013-11D3-8CDF-8BF0A4AD5B35")
PolyShape;
#endif

EXTERN_C const CLSID CLSID_FasterPolyShape;

#ifdef __cplusplus

class DECLSPEC_UUID("AFB02F20-6824-491f-B804-1AD34DAA965E")
FasterPolyShape;
#endif

EXTERN_C const CLSID CLSID_Circle;

#ifdef __cplusplus

class DECLSPEC_UUID("219B8FC2-0154-11D3-8CDF-CCA4ADEF4534")
Circle;
#endif

EXTERN_C const CLSID CLSID_Rect;

#ifdef __cplusplus

class DECLSPEC_UUID("3E07BAA2-01A2-11D3-8CDF-D8B830C3A934")
Rect;
#endif

EXTERN_C const CLSID CLSID_Triangle;

#ifdef __cplusplus

class DECLSPEC_UUID("0C89D3A2-02E2-11D3-8CDF-DDE6AA65DF35")
Triangle;
#endif

EXTERN_C const CLSID CLSID_PrecastBeam;

#ifdef __cplusplus

class DECLSPEC_UUID("E7E272C2-032F-11D3-8CDF-861E1B8C3634")
PrecastBeam;
#endif

EXTERN_C const CLSID CLSID_NUBeam;

#ifdef __cplusplus

class DECLSPEC_UUID("411AA7A2-67F2-4bb6-86E2-09C2C0F5A096")
NUBeam;
#endif

EXTERN_C const CLSID CLSID_BulbTee;

#ifdef __cplusplus

class DECLSPEC_UUID("83B73726-F71A-4400-BCD0-542E1332EE2A")
BulbTee;
#endif

EXTERN_C const CLSID CLSID_BulbTee2;

#ifdef __cplusplus

class DECLSPEC_UUID("05EB3E1B-4844-43F3-A104-D85B204DEFE2")
BulbTee2;
#endif

EXTERN_C const CLSID CLSID_TrafficBarrier;

#ifdef __cplusplus

class DECLSPEC_UUID("2558CFC2-03CE-11D3-8CDF-EBFB6612CA35")
TrafficBarrier;
#endif

EXTERN_C const CLSID CLSID_Point3d;

#ifdef __cplusplus

class DECLSPEC_UUID("4F37A661-03FE-11D3-8CDF-882D80988F34")
Point3d;
#endif

EXTERN_C const CLSID CLSID_LineSegment3d;

#ifdef __cplusplus

class DECLSPEC_UUID("56CD2A28-FABF-4015-AA70-F27D95334249")
LineSegment3d;
#endif

EXTERN_C const CLSID CLSID_Size3d;

#ifdef __cplusplus

class DECLSPEC_UUID("75DB33E1-0449-11D3-8CDF-9E53F9A4BF35")
Size3d;
#endif

EXTERN_C const CLSID CLSID_Vector3d;

#ifdef __cplusplus

class DECLSPEC_UUID("F97D8402-1871-11D3-8CDF-925649DD1F63")
Vector3d;
#endif

EXTERN_C const CLSID CLSID_Plane3d;

#ifdef __cplusplus

class DECLSPEC_UUID("F97D8404-1871-11D3-8CDF-925649DD1F63")
Plane3d;
#endif

EXTERN_C const CLSID CLSID_Point3dCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("818E5101-1942-11D3-8CDF-DCD8D8F12565")
Point3dCollection;
#endif

EXTERN_C const CLSID CLSID_GeomUtil;

#ifdef __cplusplus

class DECLSPEC_UUID("110FFB89-2B04-11D3-8952-006097C68A9C")
GeomUtil;
#endif

EXTERN_C const CLSID CLSID_CoordinateXform3d;

#ifdef __cplusplus

class DECLSPEC_UUID("D146B4A5-5103-11D3-8CDF-BFEA3D98042F")
CoordinateXform3d;
#endif

EXTERN_C const CLSID CLSID_CoordinateXform2d;

#ifdef __cplusplus

class DECLSPEC_UUID("1A1AD39C-5184-11D3-8985-006097C68A9C")
CoordinateXform2d;
#endif

EXTERN_C const CLSID CLSID_PrimitiveFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("EC5AC146-5CD0-11D3-8CDF-A057587EDC05")
PrimitiveFactory;
#endif

EXTERN_C const CLSID CLSID_CircularSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("C6C2A641-6563-11D4-8CE4-0080C7380027")
CircularSegment;
#endif

EXTERN_C const CLSID CLSID_ShapeCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("2A9E6E22-B982-11d4-8B56-006097C68A9C")
ShapeCollection;
#endif

EXTERN_C const CLSID CLSID_PlateGirder;

#ifdef __cplusplus

class DECLSPEC_UUID("9F28211E-09D6-11D5-8BBF-006097C68A9C")
PlateGirder;
#endif

EXTERN_C const CLSID CLSID_UBeam;

#ifdef __cplusplus

class DECLSPEC_UUID("F2921D46-E60C-41FC-84DD-FB4D198902C2")
UBeam;
#endif

EXTERN_C const CLSID CLSID_UBeam2;

#ifdef __cplusplus

class DECLSPEC_UUID("F75025D7-77F4-4581-A74D-4726755462D0")
UBeam2;
#endif

EXTERN_C const CLSID CLSID_MultiWeb;

#ifdef __cplusplus

class DECLSPEC_UUID("3D4E4B7B-A78C-4419-8DCD-DAF644499AC1")
MultiWeb;
#endif

EXTERN_C const CLSID CLSID_MultiWeb2;

#ifdef __cplusplus

class DECLSPEC_UUID("E115FF80-E81C-4f3f-B275-D7799BFF82A5")
MultiWeb2;
#endif

EXTERN_C const CLSID CLSID_CompositeShapeItem;

#ifdef __cplusplus

class DECLSPEC_UUID("C0D62C37-8408-4fcb-8E9A-AA3D4498CEF4")
CompositeShapeItem;
#endif

EXTERN_C const CLSID CLSID_CompositeShape;

#ifdef __cplusplus

class DECLSPEC_UUID("57B8E907-F0CD-4915-A7C6-2060C53D7E16")
CompositeShape;
#endif

EXTERN_C const CLSID CLSID_VoidedSlab;

#ifdef __cplusplus

class DECLSPEC_UUID("3B31027D-48F3-4a8e-A9F2-3887B74E3D96")
VoidedSlab;
#endif

EXTERN_C const CLSID CLSID_VoidedSlab2;

#ifdef __cplusplus

class DECLSPEC_UUID("16313108-22B1-4103-9D06-1934A1AF9C3D")
VoidedSlab2;
#endif

EXTERN_C const CLSID CLSID_BoxBeam;

#ifdef __cplusplus

class DECLSPEC_UUID("62292381-C515-4aba-871B-040D739F1BA2")
BoxBeam;
#endif

EXTERN_C const CLSID CLSID_DeckedSlabBeam;

#ifdef __cplusplus

class DECLSPEC_UUID("09785C7E-27E9-4709-B4E1-4B8120CB1ECD")
DeckedSlabBeam;
#endif

EXTERN_C const CLSID CLSID_GenericShape;

#ifdef __cplusplus

class DECLSPEC_UUID("15C754B8-415F-4bf0-89C2-D5E991D51D7C")
GenericShape;
#endif
#endif /* __WBFLGeometry_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


