

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Jun 23 11:25:32 2017
 */
/* Compiler settings for ..\Include\WBFLCogo.idl:
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


#ifndef __WBFLCogo_h__
#define __WBFLCogo_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAngle_FWD_DEFINED__
#define __IAngle_FWD_DEFINED__
typedef interface IAngle IAngle;

#endif 	/* __IAngle_FWD_DEFINED__ */


#ifndef __IDirection_FWD_DEFINED__
#define __IDirection_FWD_DEFINED__
typedef interface IDirection IDirection;

#endif 	/* __IDirection_FWD_DEFINED__ */


#ifndef __IAngleDisplayUnitFormatter_FWD_DEFINED__
#define __IAngleDisplayUnitFormatter_FWD_DEFINED__
typedef interface IAngleDisplayUnitFormatter IAngleDisplayUnitFormatter;

#endif 	/* __IAngleDisplayUnitFormatter_FWD_DEFINED__ */


#ifndef __IDirectionDisplayUnitFormatter_FWD_DEFINED__
#define __IDirectionDisplayUnitFormatter_FWD_DEFINED__
typedef interface IDirectionDisplayUnitFormatter IDirectionDisplayUnitFormatter;

#endif 	/* __IDirectionDisplayUnitFormatter_FWD_DEFINED__ */


#ifndef __IPointEvents_FWD_DEFINED__
#define __IPointEvents_FWD_DEFINED__
typedef interface IPointEvents IPointEvents;

#endif 	/* __IPointEvents_FWD_DEFINED__ */


#ifndef __IEnumIDs_FWD_DEFINED__
#define __IEnumIDs_FWD_DEFINED__
typedef interface IEnumIDs IEnumIDs;

#endif 	/* __IEnumIDs_FWD_DEFINED__ */


#ifndef __IPointCollection_FWD_DEFINED__
#define __IPointCollection_FWD_DEFINED__
typedef interface IPointCollection IPointCollection;

#endif 	/* __IPointCollection_FWD_DEFINED__ */


#ifndef __IPointCollectionEvents_FWD_DEFINED__
#define __IPointCollectionEvents_FWD_DEFINED__
typedef interface IPointCollectionEvents IPointCollectionEvents;

#endif 	/* __IPointCollectionEvents_FWD_DEFINED__ */


#ifndef __IHorzCurve_FWD_DEFINED__
#define __IHorzCurve_FWD_DEFINED__
typedef interface IHorzCurve IHorzCurve;

#endif 	/* __IHorzCurve_FWD_DEFINED__ */


#ifndef __IHorzCurveEvents_FWD_DEFINED__
#define __IHorzCurveEvents_FWD_DEFINED__
typedef interface IHorzCurveEvents IHorzCurveEvents;

#endif 	/* __IHorzCurveEvents_FWD_DEFINED__ */


#ifndef __IEnumLineSegments_FWD_DEFINED__
#define __IEnumLineSegments_FWD_DEFINED__
typedef interface IEnumLineSegments IEnumLineSegments;

#endif 	/* __IEnumLineSegments_FWD_DEFINED__ */


#ifndef __ILineSegmentCollection_FWD_DEFINED__
#define __ILineSegmentCollection_FWD_DEFINED__
typedef interface ILineSegmentCollection ILineSegmentCollection;

#endif 	/* __ILineSegmentCollection_FWD_DEFINED__ */


#ifndef __ILineSegmentCollectionEvents_FWD_DEFINED__
#define __ILineSegmentCollectionEvents_FWD_DEFINED__
typedef interface ILineSegmentCollectionEvents ILineSegmentCollectionEvents;

#endif 	/* __ILineSegmentCollectionEvents_FWD_DEFINED__ */


#ifndef __IStation_FWD_DEFINED__
#define __IStation_FWD_DEFINED__
typedef interface IStation IStation;

#endif 	/* __IStation_FWD_DEFINED__ */


#ifndef __IStationEvents_FWD_DEFINED__
#define __IStationEvents_FWD_DEFINED__
typedef interface IStationEvents IStationEvents;

#endif 	/* __IStationEvents_FWD_DEFINED__ */


#ifndef __IStationEquation_FWD_DEFINED__
#define __IStationEquation_FWD_DEFINED__
typedef interface IStationEquation IStationEquation;

#endif 	/* __IStationEquation_FWD_DEFINED__ */


#ifndef __IEnumStationEquations_FWD_DEFINED__
#define __IEnumStationEquations_FWD_DEFINED__
typedef interface IEnumStationEquations IEnumStationEquations;

#endif 	/* __IEnumStationEquations_FWD_DEFINED__ */


#ifndef __IStationEquationCollection_FWD_DEFINED__
#define __IStationEquationCollection_FWD_DEFINED__
typedef interface IStationEquationCollection IStationEquationCollection;

#endif 	/* __IStationEquationCollection_FWD_DEFINED__ */


#ifndef __IStationEquationCollectionEvents_FWD_DEFINED__
#define __IStationEquationCollectionEvents_FWD_DEFINED__
typedef interface IStationEquationCollectionEvents IStationEquationCollectionEvents;

#endif 	/* __IStationEquationCollectionEvents_FWD_DEFINED__ */


#ifndef __IProfilePoint_FWD_DEFINED__
#define __IProfilePoint_FWD_DEFINED__
typedef interface IProfilePoint IProfilePoint;

#endif 	/* __IProfilePoint_FWD_DEFINED__ */


#ifndef __IProfilePointEvents_FWD_DEFINED__
#define __IProfilePointEvents_FWD_DEFINED__
typedef interface IProfilePointEvents IProfilePointEvents;

#endif 	/* __IProfilePointEvents_FWD_DEFINED__ */


#ifndef __IEnumProfilePoints_FWD_DEFINED__
#define __IEnumProfilePoints_FWD_DEFINED__
typedef interface IEnumProfilePoints IEnumProfilePoints;

#endif 	/* __IEnumProfilePoints_FWD_DEFINED__ */


#ifndef __IProfilePointFactory_FWD_DEFINED__
#define __IProfilePointFactory_FWD_DEFINED__
typedef interface IProfilePointFactory IProfilePointFactory;

#endif 	/* __IProfilePointFactory_FWD_DEFINED__ */


#ifndef __IProfilePointCollection_FWD_DEFINED__
#define __IProfilePointCollection_FWD_DEFINED__
typedef interface IProfilePointCollection IProfilePointCollection;

#endif 	/* __IProfilePointCollection_FWD_DEFINED__ */


#ifndef __IProfilePointCollectionEvents_FWD_DEFINED__
#define __IProfilePointCollectionEvents_FWD_DEFINED__
typedef interface IProfilePointCollectionEvents IProfilePointCollectionEvents;

#endif 	/* __IProfilePointCollectionEvents_FWD_DEFINED__ */


#ifndef __IVertCurve_FWD_DEFINED__
#define __IVertCurve_FWD_DEFINED__
typedef interface IVertCurve IVertCurve;

#endif 	/* __IVertCurve_FWD_DEFINED__ */


#ifndef __IVertCurveEvents_FWD_DEFINED__
#define __IVertCurveEvents_FWD_DEFINED__
typedef interface IVertCurveEvents IVertCurveEvents;

#endif 	/* __IVertCurveEvents_FWD_DEFINED__ */


#ifndef __IEnumVertCurves_FWD_DEFINED__
#define __IEnumVertCurves_FWD_DEFINED__
typedef interface IEnumVertCurves IEnumVertCurves;

#endif 	/* __IEnumVertCurves_FWD_DEFINED__ */


#ifndef __IVertCurveFactory_FWD_DEFINED__
#define __IVertCurveFactory_FWD_DEFINED__
typedef interface IVertCurveFactory IVertCurveFactory;

#endif 	/* __IVertCurveFactory_FWD_DEFINED__ */


#ifndef __IVertCurveCollection_FWD_DEFINED__
#define __IVertCurveCollection_FWD_DEFINED__
typedef interface IVertCurveCollection IVertCurveCollection;

#endif 	/* __IVertCurveCollection_FWD_DEFINED__ */


#ifndef __IVertCurveCollectionEvents_FWD_DEFINED__
#define __IVertCurveCollectionEvents_FWD_DEFINED__
typedef interface IVertCurveCollectionEvents IVertCurveCollectionEvents;

#endif 	/* __IVertCurveCollectionEvents_FWD_DEFINED__ */


#ifndef __IEnumHorzCurves_FWD_DEFINED__
#define __IEnumHorzCurves_FWD_DEFINED__
typedef interface IEnumHorzCurves IEnumHorzCurves;

#endif 	/* __IEnumHorzCurves_FWD_DEFINED__ */


#ifndef __IHorzCurveFactory_FWD_DEFINED__
#define __IHorzCurveFactory_FWD_DEFINED__
typedef interface IHorzCurveFactory IHorzCurveFactory;

#endif 	/* __IHorzCurveFactory_FWD_DEFINED__ */


#ifndef __IHorzCurveCollection_FWD_DEFINED__
#define __IHorzCurveCollection_FWD_DEFINED__
typedef interface IHorzCurveCollection IHorzCurveCollection;

#endif 	/* __IHorzCurveCollection_FWD_DEFINED__ */


#ifndef __IHorzCurveCollectionEvents_FWD_DEFINED__
#define __IHorzCurveCollectionEvents_FWD_DEFINED__
typedef interface IHorzCurveCollectionEvents IHorzCurveCollectionEvents;

#endif 	/* __IHorzCurveCollectionEvents_FWD_DEFINED__ */


#ifndef __ICubicSpline_FWD_DEFINED__
#define __ICubicSpline_FWD_DEFINED__
typedef interface ICubicSpline ICubicSpline;

#endif 	/* __ICubicSpline_FWD_DEFINED__ */


#ifndef __ICubicSplineEvents_FWD_DEFINED__
#define __ICubicSplineEvents_FWD_DEFINED__
typedef interface ICubicSplineEvents ICubicSplineEvents;

#endif 	/* __ICubicSplineEvents_FWD_DEFINED__ */


#ifndef __IWidening_FWD_DEFINED__
#define __IWidening_FWD_DEFINED__
typedef interface IWidening IWidening;

#endif 	/* __IWidening_FWD_DEFINED__ */


#ifndef __IWideningEvents_FWD_DEFINED__
#define __IWideningEvents_FWD_DEFINED__
typedef interface IWideningEvents IWideningEvents;

#endif 	/* __IWideningEvents_FWD_DEFINED__ */


#ifndef __IEnumWidenings_FWD_DEFINED__
#define __IEnumWidenings_FWD_DEFINED__
typedef interface IEnumWidenings IEnumWidenings;

#endif 	/* __IEnumWidenings_FWD_DEFINED__ */


#ifndef __IWideningCollection_FWD_DEFINED__
#define __IWideningCollection_FWD_DEFINED__
typedef interface IWideningCollection IWideningCollection;

#endif 	/* __IWideningCollection_FWD_DEFINED__ */


#ifndef __IWideningCollectionEvents_FWD_DEFINED__
#define __IWideningCollectionEvents_FWD_DEFINED__
typedef interface IWideningCollectionEvents IWideningCollectionEvents;

#endif 	/* __IWideningCollectionEvents_FWD_DEFINED__ */


#ifndef __ISuperelevation_FWD_DEFINED__
#define __ISuperelevation_FWD_DEFINED__
typedef interface ISuperelevation ISuperelevation;

#endif 	/* __ISuperelevation_FWD_DEFINED__ */


#ifndef __ISuperelevationEvents_FWD_DEFINED__
#define __ISuperelevationEvents_FWD_DEFINED__
typedef interface ISuperelevationEvents ISuperelevationEvents;

#endif 	/* __ISuperelevationEvents_FWD_DEFINED__ */


#ifndef __IEnumSuperelevations_FWD_DEFINED__
#define __IEnumSuperelevations_FWD_DEFINED__
typedef interface IEnumSuperelevations IEnumSuperelevations;

#endif 	/* __IEnumSuperelevations_FWD_DEFINED__ */


#ifndef __ISuperelevationCollection_FWD_DEFINED__
#define __ISuperelevationCollection_FWD_DEFINED__
typedef interface ISuperelevationCollection ISuperelevationCollection;

#endif 	/* __ISuperelevationCollection_FWD_DEFINED__ */


#ifndef __ISuperelevationCollectionEvents_FWD_DEFINED__
#define __ISuperelevationCollectionEvents_FWD_DEFINED__
typedef interface ISuperelevationCollectionEvents ISuperelevationCollectionEvents;

#endif 	/* __ISuperelevationCollectionEvents_FWD_DEFINED__ */


#ifndef __ITemplateSegment_FWD_DEFINED__
#define __ITemplateSegment_FWD_DEFINED__
typedef interface ITemplateSegment ITemplateSegment;

#endif 	/* __ITemplateSegment_FWD_DEFINED__ */


#ifndef __ITemplateSegmentEvents_FWD_DEFINED__
#define __ITemplateSegmentEvents_FWD_DEFINED__
typedef interface ITemplateSegmentEvents ITemplateSegmentEvents;

#endif 	/* __ITemplateSegmentEvents_FWD_DEFINED__ */


#ifndef __ISurfaceTemplate_FWD_DEFINED__
#define __ISurfaceTemplate_FWD_DEFINED__
typedef interface ISurfaceTemplate ISurfaceTemplate;

#endif 	/* __ISurfaceTemplate_FWD_DEFINED__ */


#ifndef __ISurfaceTemplateEvents_FWD_DEFINED__
#define __ISurfaceTemplateEvents_FWD_DEFINED__
typedef interface ISurfaceTemplateEvents ISurfaceTemplateEvents;

#endif 	/* __ISurfaceTemplateEvents_FWD_DEFINED__ */


#ifndef __IEnumSurfaceTemplates_FWD_DEFINED__
#define __IEnumSurfaceTemplates_FWD_DEFINED__
typedef interface IEnumSurfaceTemplates IEnumSurfaceTemplates;

#endif 	/* __IEnumSurfaceTemplates_FWD_DEFINED__ */


#ifndef __ISurfaceTemplateCollection_FWD_DEFINED__
#define __ISurfaceTemplateCollection_FWD_DEFINED__
typedef interface ISurfaceTemplateCollection ISurfaceTemplateCollection;

#endif 	/* __ISurfaceTemplateCollection_FWD_DEFINED__ */


#ifndef __ISurfaceTemplateCollectionEvents_FWD_DEFINED__
#define __ISurfaceTemplateCollectionEvents_FWD_DEFINED__
typedef interface ISurfaceTemplateCollectionEvents ISurfaceTemplateCollectionEvents;

#endif 	/* __ISurfaceTemplateCollectionEvents_FWD_DEFINED__ */


#ifndef __ISurfacePoint_FWD_DEFINED__
#define __ISurfacePoint_FWD_DEFINED__
typedef interface ISurfacePoint ISurfacePoint;

#endif 	/* __ISurfacePoint_FWD_DEFINED__ */


#ifndef __ISurfaceProfile_FWD_DEFINED__
#define __ISurfaceProfile_FWD_DEFINED__
typedef interface ISurfaceProfile ISurfaceProfile;

#endif 	/* __ISurfaceProfile_FWD_DEFINED__ */


#ifndef __ISurface_FWD_DEFINED__
#define __ISurface_FWD_DEFINED__
typedef interface ISurface ISurface;

#endif 	/* __ISurface_FWD_DEFINED__ */


#ifndef __ISurfaceEvents_FWD_DEFINED__
#define __ISurfaceEvents_FWD_DEFINED__
typedef interface ISurfaceEvents ISurfaceEvents;

#endif 	/* __ISurfaceEvents_FWD_DEFINED__ */


#ifndef __IEnumSurfaces_FWD_DEFINED__
#define __IEnumSurfaces_FWD_DEFINED__
typedef interface IEnumSurfaces IEnumSurfaces;

#endif 	/* __IEnumSurfaces_FWD_DEFINED__ */


#ifndef __ISurfaceCollection_FWD_DEFINED__
#define __ISurfaceCollection_FWD_DEFINED__
typedef interface ISurfaceCollection ISurfaceCollection;

#endif 	/* __ISurfaceCollection_FWD_DEFINED__ */


#ifndef __ISurfaceCollectionEvents_FWD_DEFINED__
#define __ISurfaceCollectionEvents_FWD_DEFINED__
typedef interface ISurfaceCollectionEvents ISurfaceCollectionEvents;

#endif 	/* __ISurfaceCollectionEvents_FWD_DEFINED__ */


#ifndef __IProfileElement_FWD_DEFINED__
#define __IProfileElement_FWD_DEFINED__
typedef interface IProfileElement IProfileElement;

#endif 	/* __IProfileElement_FWD_DEFINED__ */


#ifndef __IProfileElementEvents_FWD_DEFINED__
#define __IProfileElementEvents_FWD_DEFINED__
typedef interface IProfileElementEvents IProfileElementEvents;

#endif 	/* __IProfileElementEvents_FWD_DEFINED__ */


#ifndef __IEnumProfileElements_FWD_DEFINED__
#define __IEnumProfileElements_FWD_DEFINED__
typedef interface IEnumProfileElements IEnumProfileElements;

#endif 	/* __IEnumProfileElements_FWD_DEFINED__ */


#ifndef __IProfile_FWD_DEFINED__
#define __IProfile_FWD_DEFINED__
typedef interface IProfile IProfile;

#endif 	/* __IProfile_FWD_DEFINED__ */


#ifndef __IProfileEvents_FWD_DEFINED__
#define __IProfileEvents_FWD_DEFINED__
typedef interface IProfileEvents IProfileEvents;

#endif 	/* __IProfileEvents_FWD_DEFINED__ */


#ifndef __IPathElement_FWD_DEFINED__
#define __IPathElement_FWD_DEFINED__
typedef interface IPathElement IPathElement;

#endif 	/* __IPathElement_FWD_DEFINED__ */


#ifndef __IPathElementEvents_FWD_DEFINED__
#define __IPathElementEvents_FWD_DEFINED__
typedef interface IPathElementEvents IPathElementEvents;

#endif 	/* __IPathElementEvents_FWD_DEFINED__ */


#ifndef __IEnumPathElements_FWD_DEFINED__
#define __IEnumPathElements_FWD_DEFINED__
typedef interface IEnumPathElements IEnumPathElements;

#endif 	/* __IEnumPathElements_FWD_DEFINED__ */


#ifndef __IPath_FWD_DEFINED__
#define __IPath_FWD_DEFINED__
typedef interface IPath IPath;

#endif 	/* __IPath_FWD_DEFINED__ */


#ifndef __IPathEvents_FWD_DEFINED__
#define __IPathEvents_FWD_DEFINED__
typedef interface IPathEvents IPathEvents;

#endif 	/* __IPathEvents_FWD_DEFINED__ */


#ifndef __IEnumPaths_FWD_DEFINED__
#define __IEnumPaths_FWD_DEFINED__
typedef interface IEnumPaths IEnumPaths;

#endif 	/* __IEnumPaths_FWD_DEFINED__ */


#ifndef __IPathFactory_FWD_DEFINED__
#define __IPathFactory_FWD_DEFINED__
typedef interface IPathFactory IPathFactory;

#endif 	/* __IPathFactory_FWD_DEFINED__ */


#ifndef __IPathCollection_FWD_DEFINED__
#define __IPathCollection_FWD_DEFINED__
typedef interface IPathCollection IPathCollection;

#endif 	/* __IPathCollection_FWD_DEFINED__ */


#ifndef __IPathCollectionEvents_FWD_DEFINED__
#define __IPathCollectionEvents_FWD_DEFINED__
typedef interface IPathCollectionEvents IPathCollectionEvents;

#endif 	/* __IPathCollectionEvents_FWD_DEFINED__ */


#ifndef __IAlignment_FWD_DEFINED__
#define __IAlignment_FWD_DEFINED__
typedef interface IAlignment IAlignment;

#endif 	/* __IAlignment_FWD_DEFINED__ */


#ifndef __IAlignmentEvents_FWD_DEFINED__
#define __IAlignmentEvents_FWD_DEFINED__
typedef interface IAlignmentEvents IAlignmentEvents;

#endif 	/* __IAlignmentEvents_FWD_DEFINED__ */


#ifndef __IEnumAlignments_FWD_DEFINED__
#define __IEnumAlignments_FWD_DEFINED__
typedef interface IEnumAlignments IEnumAlignments;

#endif 	/* __IEnumAlignments_FWD_DEFINED__ */


#ifndef __IAlignmentFactory_FWD_DEFINED__
#define __IAlignmentFactory_FWD_DEFINED__
typedef interface IAlignmentFactory IAlignmentFactory;

#endif 	/* __IAlignmentFactory_FWD_DEFINED__ */


#ifndef __IAlignmentCollection_FWD_DEFINED__
#define __IAlignmentCollection_FWD_DEFINED__
typedef interface IAlignmentCollection IAlignmentCollection;

#endif 	/* __IAlignmentCollection_FWD_DEFINED__ */


#ifndef __IAlignmentCollectionEvents_FWD_DEFINED__
#define __IAlignmentCollectionEvents_FWD_DEFINED__
typedef interface IAlignmentCollectionEvents IAlignmentCollectionEvents;

#endif 	/* __IAlignmentCollectionEvents_FWD_DEFINED__ */


#ifndef __IMeasure_FWD_DEFINED__
#define __IMeasure_FWD_DEFINED__
typedef interface IMeasure IMeasure;

#endif 	/* __IMeasure_FWD_DEFINED__ */


#ifndef __IMeasure2_FWD_DEFINED__
#define __IMeasure2_FWD_DEFINED__
typedef interface IMeasure2 IMeasure2;

#endif 	/* __IMeasure2_FWD_DEFINED__ */


#ifndef __ILocate_FWD_DEFINED__
#define __ILocate_FWD_DEFINED__
typedef interface ILocate ILocate;

#endif 	/* __ILocate_FWD_DEFINED__ */


#ifndef __ILocate2_FWD_DEFINED__
#define __ILocate2_FWD_DEFINED__
typedef interface ILocate2 ILocate2;

#endif 	/* __ILocate2_FWD_DEFINED__ */


#ifndef __IIntersect_FWD_DEFINED__
#define __IIntersect_FWD_DEFINED__
typedef interface IIntersect IIntersect;

#endif 	/* __IIntersect_FWD_DEFINED__ */


#ifndef __IIntersect2_FWD_DEFINED__
#define __IIntersect2_FWD_DEFINED__
typedef interface IIntersect2 IIntersect2;

#endif 	/* __IIntersect2_FWD_DEFINED__ */


#ifndef __IProject_FWD_DEFINED__
#define __IProject_FWD_DEFINED__
typedef interface IProject IProject;

#endif 	/* __IProject_FWD_DEFINED__ */


#ifndef __IProject2_FWD_DEFINED__
#define __IProject2_FWD_DEFINED__
typedef interface IProject2 IProject2;

#endif 	/* __IProject2_FWD_DEFINED__ */


#ifndef __IDivide_FWD_DEFINED__
#define __IDivide_FWD_DEFINED__
typedef interface IDivide IDivide;

#endif 	/* __IDivide_FWD_DEFINED__ */


#ifndef __IDivide2_FWD_DEFINED__
#define __IDivide2_FWD_DEFINED__
typedef interface IDivide2 IDivide2;

#endif 	/* __IDivide2_FWD_DEFINED__ */


#ifndef __ITangent_FWD_DEFINED__
#define __ITangent_FWD_DEFINED__
typedef interface ITangent ITangent;

#endif 	/* __ITangent_FWD_DEFINED__ */


#ifndef __ITangent2_FWD_DEFINED__
#define __ITangent2_FWD_DEFINED__
typedef interface ITangent2 ITangent2;

#endif 	/* __ITangent2_FWD_DEFINED__ */


#ifndef __ICogoEngine_FWD_DEFINED__
#define __ICogoEngine_FWD_DEFINED__
typedef interface ICogoEngine ICogoEngine;

#endif 	/* __ICogoEngine_FWD_DEFINED__ */


#ifndef __ICogoModel_FWD_DEFINED__
#define __ICogoModel_FWD_DEFINED__
typedef interface ICogoModel ICogoModel;

#endif 	/* __ICogoModel_FWD_DEFINED__ */


#ifndef __ICogoModelEvents_FWD_DEFINED__
#define __ICogoModelEvents_FWD_DEFINED__
typedef interface ICogoModelEvents ICogoModelEvents;

#endif 	/* __ICogoModelEvents_FWD_DEFINED__ */


#ifndef __Angle_FWD_DEFINED__
#define __Angle_FWD_DEFINED__

#ifdef __cplusplus
typedef class Angle Angle;
#else
typedef struct Angle Angle;
#endif /* __cplusplus */

#endif 	/* __Angle_FWD_DEFINED__ */


#ifndef __Direction_FWD_DEFINED__
#define __Direction_FWD_DEFINED__

#ifdef __cplusplus
typedef class Direction Direction;
#else
typedef struct Direction Direction;
#endif /* __cplusplus */

#endif 	/* __Direction_FWD_DEFINED__ */


#ifndef __PointCollection_FWD_DEFINED__
#define __PointCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointCollection PointCollection;
#else
typedef struct PointCollection PointCollection;
#endif /* __cplusplus */

#endif 	/* __PointCollection_FWD_DEFINED__ */


#ifndef __LineSegmentCollection_FWD_DEFINED__
#define __LineSegmentCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class LineSegmentCollection LineSegmentCollection;
#else
typedef struct LineSegmentCollection LineSegmentCollection;
#endif /* __cplusplus */

#endif 	/* __LineSegmentCollection_FWD_DEFINED__ */


#ifndef __CogoModel_FWD_DEFINED__
#define __CogoModel_FWD_DEFINED__

#ifdef __cplusplus
typedef class CogoModel CogoModel;
#else
typedef struct CogoModel CogoModel;
#endif /* __cplusplus */

#endif 	/* __CogoModel_FWD_DEFINED__ */


#ifndef __ProfilePoint_FWD_DEFINED__
#define __ProfilePoint_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProfilePoint ProfilePoint;
#else
typedef struct ProfilePoint ProfilePoint;
#endif /* __cplusplus */

#endif 	/* __ProfilePoint_FWD_DEFINED__ */


#ifndef __ProfilePointCollection_FWD_DEFINED__
#define __ProfilePointCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProfilePointCollection ProfilePointCollection;
#else
typedef struct ProfilePointCollection ProfilePointCollection;
#endif /* __cplusplus */

#endif 	/* __ProfilePointCollection_FWD_DEFINED__ */


#ifndef __VertCurve_FWD_DEFINED__
#define __VertCurve_FWD_DEFINED__

#ifdef __cplusplus
typedef class VertCurve VertCurve;
#else
typedef struct VertCurve VertCurve;
#endif /* __cplusplus */

#endif 	/* __VertCurve_FWD_DEFINED__ */


#ifndef __VertCurveCollection_FWD_DEFINED__
#define __VertCurveCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class VertCurveCollection VertCurveCollection;
#else
typedef struct VertCurveCollection VertCurveCollection;
#endif /* __cplusplus */

#endif 	/* __VertCurveCollection_FWD_DEFINED__ */


#ifndef __HorzCurve_FWD_DEFINED__
#define __HorzCurve_FWD_DEFINED__

#ifdef __cplusplus
typedef class HorzCurve HorzCurve;
#else
typedef struct HorzCurve HorzCurve;
#endif /* __cplusplus */

#endif 	/* __HorzCurve_FWD_DEFINED__ */


#ifndef __HorzCurveCollection_FWD_DEFINED__
#define __HorzCurveCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class HorzCurveCollection HorzCurveCollection;
#else
typedef struct HorzCurveCollection HorzCurveCollection;
#endif /* __cplusplus */

#endif 	/* __HorzCurveCollection_FWD_DEFINED__ */


#ifndef __CubicSpline_FWD_DEFINED__
#define __CubicSpline_FWD_DEFINED__

#ifdef __cplusplus
typedef class CubicSpline CubicSpline;
#else
typedef struct CubicSpline CubicSpline;
#endif /* __cplusplus */

#endif 	/* __CubicSpline_FWD_DEFINED__ */


#ifndef __ProfileElement_FWD_DEFINED__
#define __ProfileElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProfileElement ProfileElement;
#else
typedef struct ProfileElement ProfileElement;
#endif /* __cplusplus */

#endif 	/* __ProfileElement_FWD_DEFINED__ */


#ifndef __Profile_FWD_DEFINED__
#define __Profile_FWD_DEFINED__

#ifdef __cplusplus
typedef class Profile Profile;
#else
typedef struct Profile Profile;
#endif /* __cplusplus */

#endif 	/* __Profile_FWD_DEFINED__ */


#ifndef __Widening_FWD_DEFINED__
#define __Widening_FWD_DEFINED__

#ifdef __cplusplus
typedef class Widening Widening;
#else
typedef struct Widening Widening;
#endif /* __cplusplus */

#endif 	/* __Widening_FWD_DEFINED__ */


#ifndef __WideningCollection_FWD_DEFINED__
#define __WideningCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WideningCollection WideningCollection;
#else
typedef struct WideningCollection WideningCollection;
#endif /* __cplusplus */

#endif 	/* __WideningCollection_FWD_DEFINED__ */


#ifndef __Superelevation_FWD_DEFINED__
#define __Superelevation_FWD_DEFINED__

#ifdef __cplusplus
typedef class Superelevation Superelevation;
#else
typedef struct Superelevation Superelevation;
#endif /* __cplusplus */

#endif 	/* __Superelevation_FWD_DEFINED__ */


#ifndef __SuperelevationCollection_FWD_DEFINED__
#define __SuperelevationCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class SuperelevationCollection SuperelevationCollection;
#else
typedef struct SuperelevationCollection SuperelevationCollection;
#endif /* __cplusplus */

#endif 	/* __SuperelevationCollection_FWD_DEFINED__ */


#ifndef __TemplateSegment_FWD_DEFINED__
#define __TemplateSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class TemplateSegment TemplateSegment;
#else
typedef struct TemplateSegment TemplateSegment;
#endif /* __cplusplus */

#endif 	/* __TemplateSegment_FWD_DEFINED__ */


#ifndef __SurfaceTemplate_FWD_DEFINED__
#define __SurfaceTemplate_FWD_DEFINED__

#ifdef __cplusplus
typedef class SurfaceTemplate SurfaceTemplate;
#else
typedef struct SurfaceTemplate SurfaceTemplate;
#endif /* __cplusplus */

#endif 	/* __SurfaceTemplate_FWD_DEFINED__ */


#ifndef __SurfaceTemplateCollection_FWD_DEFINED__
#define __SurfaceTemplateCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class SurfaceTemplateCollection SurfaceTemplateCollection;
#else
typedef struct SurfaceTemplateCollection SurfaceTemplateCollection;
#endif /* __cplusplus */

#endif 	/* __SurfaceTemplateCollection_FWD_DEFINED__ */


#ifndef __Surface_FWD_DEFINED__
#define __Surface_FWD_DEFINED__

#ifdef __cplusplus
typedef class Surface Surface;
#else
typedef struct Surface Surface;
#endif /* __cplusplus */

#endif 	/* __Surface_FWD_DEFINED__ */


#ifndef __SurfaceCollection_FWD_DEFINED__
#define __SurfaceCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class SurfaceCollection SurfaceCollection;
#else
typedef struct SurfaceCollection SurfaceCollection;
#endif /* __cplusplus */

#endif 	/* __SurfaceCollection_FWD_DEFINED__ */


#ifndef __PathElement_FWD_DEFINED__
#define __PathElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class PathElement PathElement;
#else
typedef struct PathElement PathElement;
#endif /* __cplusplus */

#endif 	/* __PathElement_FWD_DEFINED__ */


#ifndef __Alignment_FWD_DEFINED__
#define __Alignment_FWD_DEFINED__

#ifdef __cplusplus
typedef class Alignment Alignment;
#else
typedef struct Alignment Alignment;
#endif /* __cplusplus */

#endif 	/* __Alignment_FWD_DEFINED__ */


#ifndef __AlignmentCollection_FWD_DEFINED__
#define __AlignmentCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class AlignmentCollection AlignmentCollection;
#else
typedef struct AlignmentCollection AlignmentCollection;
#endif /* __cplusplus */

#endif 	/* __AlignmentCollection_FWD_DEFINED__ */


#ifndef __Path_FWD_DEFINED__
#define __Path_FWD_DEFINED__

#ifdef __cplusplus
typedef class Path Path;
#else
typedef struct Path Path;
#endif /* __cplusplus */

#endif 	/* __Path_FWD_DEFINED__ */


#ifndef __PathCollection_FWD_DEFINED__
#define __PathCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class PathCollection PathCollection;
#else
typedef struct PathCollection PathCollection;
#endif /* __cplusplus */

#endif 	/* __PathCollection_FWD_DEFINED__ */


#ifndef __VertCurveFactory_FWD_DEFINED__
#define __VertCurveFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class VertCurveFactory VertCurveFactory;
#else
typedef struct VertCurveFactory VertCurveFactory;
#endif /* __cplusplus */

#endif 	/* __VertCurveFactory_FWD_DEFINED__ */


#ifndef __ProfilePointFactory_FWD_DEFINED__
#define __ProfilePointFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProfilePointFactory ProfilePointFactory;
#else
typedef struct ProfilePointFactory ProfilePointFactory;
#endif /* __cplusplus */

#endif 	/* __ProfilePointFactory_FWD_DEFINED__ */


#ifndef __HorzCurveFactory_FWD_DEFINED__
#define __HorzCurveFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class HorzCurveFactory HorzCurveFactory;
#else
typedef struct HorzCurveFactory HorzCurveFactory;
#endif /* __cplusplus */

#endif 	/* __HorzCurveFactory_FWD_DEFINED__ */


#ifndef __PathFactory_FWD_DEFINED__
#define __PathFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class PathFactory PathFactory;
#else
typedef struct PathFactory PathFactory;
#endif /* __cplusplus */

#endif 	/* __PathFactory_FWD_DEFINED__ */


#ifndef __AlignmentFactory_FWD_DEFINED__
#define __AlignmentFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class AlignmentFactory AlignmentFactory;
#else
typedef struct AlignmentFactory AlignmentFactory;
#endif /* __cplusplus */

#endif 	/* __AlignmentFactory_FWD_DEFINED__ */


#ifndef __AngleDisplayUnitFormatter_FWD_DEFINED__
#define __AngleDisplayUnitFormatter_FWD_DEFINED__

#ifdef __cplusplus
typedef class AngleDisplayUnitFormatter AngleDisplayUnitFormatter;
#else
typedef struct AngleDisplayUnitFormatter AngleDisplayUnitFormatter;
#endif /* __cplusplus */

#endif 	/* __AngleDisplayUnitFormatter_FWD_DEFINED__ */


#ifndef __DirectionDisplayUnitFormatter_FWD_DEFINED__
#define __DirectionDisplayUnitFormatter_FWD_DEFINED__

#ifdef __cplusplus
typedef class DirectionDisplayUnitFormatter DirectionDisplayUnitFormatter;
#else
typedef struct DirectionDisplayUnitFormatter DirectionDisplayUnitFormatter;
#endif /* __cplusplus */

#endif 	/* __DirectionDisplayUnitFormatter_FWD_DEFINED__ */


#ifndef __PointFactory_FWD_DEFINED__
#define __PointFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointFactory PointFactory;
#else
typedef struct PointFactory PointFactory;
#endif /* __cplusplus */

#endif 	/* __PointFactory_FWD_DEFINED__ */


#ifndef __LineSegmentFactory_FWD_DEFINED__
#define __LineSegmentFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class LineSegmentFactory LineSegmentFactory;
#else
typedef struct LineSegmentFactory LineSegmentFactory;
#endif /* __cplusplus */

#endif 	/* __LineSegmentFactory_FWD_DEFINED__ */


#ifndef __Station_FWD_DEFINED__
#define __Station_FWD_DEFINED__

#ifdef __cplusplus
typedef class Station Station;
#else
typedef struct Station Station;
#endif /* __cplusplus */

#endif 	/* __Station_FWD_DEFINED__ */


#ifndef __StationEquation_FWD_DEFINED__
#define __StationEquation_FWD_DEFINED__

#ifdef __cplusplus
typedef class StationEquation StationEquation;
#else
typedef struct StationEquation StationEquation;
#endif /* __cplusplus */

#endif 	/* __StationEquation_FWD_DEFINED__ */


#ifndef __StationEquationCollection_FWD_DEFINED__
#define __StationEquationCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class StationEquationCollection StationEquationCollection;
#else
typedef struct StationEquationCollection StationEquationCollection;
#endif /* __cplusplus */

#endif 	/* __StationEquationCollection_FWD_DEFINED__ */


#ifndef __CogoEngine_FWD_DEFINED__
#define __CogoEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class CogoEngine CogoEngine;
#else
typedef struct CogoEngine CogoEngine;
#endif /* __cplusplus */

#endif 	/* __CogoEngine_FWD_DEFINED__ */


#ifndef __SurfacePoint_FWD_DEFINED__
#define __SurfacePoint_FWD_DEFINED__

#ifdef __cplusplus
typedef class SurfacePoint SurfacePoint;
#else
typedef struct SurfacePoint SurfacePoint;
#endif /* __cplusplus */

#endif 	/* __SurfacePoint_FWD_DEFINED__ */


#ifndef __SurfaceProfile_FWD_DEFINED__
#define __SurfaceProfile_FWD_DEFINED__

#ifdef __cplusplus
typedef class SurfaceProfile SurfaceProfile;
#else
typedef struct SurfaceProfile SurfaceProfile;
#endif /* __cplusplus */

#endif 	/* __SurfaceProfile_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"
#include "WBFLGeometry.h"
#include "WBFLUnitServer.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLCogo_0000_0000 */
/* [local] */ 

#include <WBFLUnitServer.h>
typedef IDType CogoObjectID;

#define COGO_ORIGINAL_SURFACE_ID 0
#define COGO_FINISHED_SURFACE_ID 1
#define COGO_E_POINTNOTFOUND                MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,512)
#define COGO_E_POINTALREADYDEFINED          MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,513)
#define COGO_E_BADDIRECTIONSTRING           MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,514)
#define COGO_E_BADAZIMUTH                   MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,515)
#define COGO_E_BADDIRECTION                 MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,516)
#define COGO_E_BADANGLE                     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,517)
#define COGO_E_BADANGLESTRING               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,518)
#define COGO_E_ANGLE                        MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,519)
#define COGO_E_AREA                         MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,520)
#define COGO_E_THREEPNTSREQD                MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,521)
#define COGO_E_RADIUS                       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,522)
#define COGO_E_LINESEGMENTNOTFOUND          MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,523)
#define COGO_E_LINESEGMENTALREADYDEFINED    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,524)
#define COGO_E_PROFILEPOINTNOTFOUND         MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,525)
#define COGO_E_PROFILEPOINTALREADYDEFINED   MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,526)
#define COGO_E_VERTCURVEPOINTS              MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,527)
#define COGO_E_VERTCURVENOTFOUND            MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,528)
#define COGO_E_VERTCURVEALREADYDEFINED      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,529)
#define COGO_E_HORZCURVENOTFOUND            MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,530)
#define COGO_E_HORZCURVEALREADYDEFINED      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,531)
#define COGO_E_PROFILEELEMENTTYPE           MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,532)
#define COGO_E_PATHELEMENTTYPE              MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,533)
#define COGO_E_PATHNOTFOUND                 MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,534)
#define COGO_E_PATHALREADYDEFINED           MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,535)
#define COGO_E_BADFORMATTAG                 MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,536)
#define COGO_E_COINCIDENTPOINTS             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,537)
#define COGO_E_BADSTATIONSTRING             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,538)
#define COGO_E_SPIRALSOVERLAP               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,539)
#define COGO_E_POINTEVENTS                  MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,540)
#define COGO_E_CUBICSPLINEPOINTS            MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,541)
#define COGO_E_POINTINCIRCLE                MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,542)
#define COGO_E_NOINTERSECTION               MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,543)
#define COGO_E_ALIGNMENTNOTFOUND            MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,544)
#define COGO_E_ALIGNMENTALREADYDEFINED      MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,545)
#define COGO_E_STATIONEQUATIONBACK          MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,546)
#define COGO_E_STATIONEQUATIONAHEAD         MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,547)
#define COGO_E_STATIONRANGEERROR            MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,548)
#define COGO_E_SUPERTRANSITIONERROR         MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,549)
#define COGO_E_SURFACELAYOUTERROR           MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,550)
#define COGO_E_SURFACEDEFINITIONERROR       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,551)
#define COGO_E_SURFACESLOPEMISMATCHERROR    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,552)
#define COGO_E_INVALIDRIDGEPOINTINDEX       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,553)






extern RPC_IF_HANDLE __MIDL_itf_WBFLCogo_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLCogo_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLCogo_LIBRARY_DEFINED__
#define __WBFLCogo_LIBRARY_DEFINED__

/* library WBFLCogo */
/* [helpstring][helpcontext][version][uuid] */ 

typedef /* [uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("AA76DB72-59E7-11d5-8C2D-006097C68A9C") 
enum NSDirectionType
    {
        nsNorth	= 1,
        nsSouth	= 2
    } 	NSDirectionType;

typedef /* [uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("AA76DB73-59E7-11d5-8C2D-006097C68A9C") 
enum EWDirectionType
    {
        ewEast	= 1,
        ewWest	= 2
    } 	EWDirectionType;

typedef /* [uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("66EB558D-4360-47d3-B3C0-0BC65E302333") 
enum SpiralType
    {
        spEntry	= 1,
        spExit	= 2
    } 	SpiralType;

typedef /* [uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("1620A21B-1D7E-437e-B7C8-FF71E6F44BED") 
enum CurveDirectionType
    {
        cdLeft	= 1,
        cdRight	= 2
    } 	CurveDirectionType;

typedef /* [uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("667D49B0-8BE7-43e6-8CE6-5245309C128C") 
enum ProfileElementType
    {
        pePoint	= 1,
        peVertCurve	= 2
    } 	ProfileElementType;

typedef /* [uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("A5FC1519-B488-4943-94FC-ACBA59BCB733") 
enum PathElementType
    {
        petPoint	= 1,
        petLineSegment	= 2,
        petHorzCurve	= 3,
        petCubicSpline	= 4
    } 	PathElementType;

typedef /* [uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("ED58941C-11B9-484e-A9D6-D07ADB1FA0A3") 
enum TangentSignType
    {
        tsCW	= 1,
        tsCCW	= -1
    } 	TangentSignType;

typedef /* [uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("26428AC0-AEE2-4bdb-8CC9-8C13F531A4B7") 
enum DegreeCurvatureType
    {
        dcChord	= 1,
        dcArc	= 2,
        dcRailroad	= 1,
        dcHighway	= 2
    } 	DegreeCurvatureType;

typedef /* [uuid][helpstring][public] */  DECLSPEC_UUID("50A94F9E-EACB-4b60-936F-23E5F4F24C86") 
enum OffsetMeasureType
    {
        omtAlongDirection	= 1,
        omtNormal	= 2
    } 	OffsetMeasureType;

typedef /* [uuid][helpstring][public] */  DECLSPEC_UUID("9CF798F5-D551-4b7f-A5BB-FAF9C3AEDA8B") 
enum SuperTransitionType
    {
        stLinear	= 0,
        stParabolic	= ( stLinear + 1 ) 
    } 	SuperTransitionType;

typedef /* [uuid][helpstring][public] */  DECLSPEC_UUID("E565E720-42ED-47b5-A00C-6435E6E8195A") 
enum TemplateSlopeType
    {
        tsHorizontal	= 0,
        tsFixedHorizontal	= ( tsHorizontal + 1 ) ,
        tsFixedVertical	= ( tsFixedHorizontal + 1 ) 
    } 	TemplateSlopeType;


EXTERN_C const IID LIBID_WBFLCogo;

#ifndef __IAngle_INTERFACE_DEFINED__
#define __IAngle_INTERFACE_DEFINED__

/* interface IAngle */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAngle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2C98A246-55F7-11D5-8C29-006097C68A9C")
    IAngle : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Degree( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Minute( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Second( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Normalize( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FromDMS( 
            /* [in] */ long deg,
            /* [in] */ long min,
            /* [in] */ Float64 sec) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FromString( 
            /* [in] */ BSTR bstrAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FromVariant( 
            /* [in] */ VARIANT varAngle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Increment( 
            /* [in] */ VARIANT varAngle,
            /* [retval][out] */ IAngle **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IncrementBy( 
            /* [in] */ VARIANT varAngle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IAngle **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAngleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAngle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAngle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAngle * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IAngle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IAngle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Degree )( 
            IAngle * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Minute )( 
            IAngle * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Second )( 
            IAngle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Normalize )( 
            IAngle * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FromDMS )( 
            IAngle * This,
            /* [in] */ long deg,
            /* [in] */ long min,
            /* [in] */ Float64 sec);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FromString )( 
            IAngle * This,
            /* [in] */ BSTR bstrAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FromVariant )( 
            IAngle * This,
            /* [in] */ VARIANT varAngle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Increment )( 
            IAngle * This,
            /* [in] */ VARIANT varAngle,
            /* [retval][out] */ IAngle **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IncrementBy )( 
            IAngle * This,
            /* [in] */ VARIANT varAngle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IAngle * This,
            /* [retval][out] */ IAngle **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IAngle * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IAngleVtbl;

    interface IAngle
    {
        CONST_VTBL struct IAngleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAngle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAngle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAngle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAngle_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define IAngle_put_Value(This,newVal)	\
    ( (This)->lpVtbl -> put_Value(This,newVal) ) 

#define IAngle_get_Degree(This,pVal)	\
    ( (This)->lpVtbl -> get_Degree(This,pVal) ) 

#define IAngle_get_Minute(This,pVal)	\
    ( (This)->lpVtbl -> get_Minute(This,pVal) ) 

#define IAngle_get_Second(This,pVal)	\
    ( (This)->lpVtbl -> get_Second(This,pVal) ) 

#define IAngle_Normalize(This)	\
    ( (This)->lpVtbl -> Normalize(This) ) 

#define IAngle_FromDMS(This,deg,min,sec)	\
    ( (This)->lpVtbl -> FromDMS(This,deg,min,sec) ) 

#define IAngle_FromString(This,bstrAngle)	\
    ( (This)->lpVtbl -> FromString(This,bstrAngle) ) 

#define IAngle_FromVariant(This,varAngle)	\
    ( (This)->lpVtbl -> FromVariant(This,varAngle) ) 

#define IAngle_Increment(This,varAngle,pVal)	\
    ( (This)->lpVtbl -> Increment(This,varAngle,pVal) ) 

#define IAngle_IncrementBy(This,varAngle)	\
    ( (This)->lpVtbl -> IncrementBy(This,varAngle) ) 

#define IAngle_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IAngle_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAngle_INTERFACE_DEFINED__ */


#ifndef __IDirection_INTERFACE_DEFINED__
#define __IDirection_INTERFACE_DEFINED__

/* interface IDirection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDirection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2C98A251-55F7-11D5-8C29-006097C68A9C")
    IDirection : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Azimuth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NSDirection( 
            /* [retval][out] */ NSDirectionType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_NSDirection( 
            /* [in] */ NSDirectionType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EWDirection( 
            /* [retval][out] */ EWDirectionType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EWDirection( 
            /* [in] */ EWDirectionType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Degree( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Degree( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Minute( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Minute( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Second( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Second( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Increment( 
            /* [in] */ VARIANT varAngle,
            /* [retval][out] */ IDirection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IncrementBy( 
            /* [in] */ VARIANT varAngle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FromString( 
            /* [in] */ BSTR bstrDir) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FromDMS( 
            /* [in] */ NSDirectionType ns,
            /* [in] */ long Degree,
            /* [in] */ long Minute,
            /* [in] */ Float64 Second,
            /* [in] */ EWDirectionType ew) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FromAzimuth( 
            /* [in] */ Float64 azimuth) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FromAzimuthEx( 
            /* [in] */ long Degree,
            /* [in] */ long Minute,
            /* [in] */ Float64 Second) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FromVariant( 
            /* [in] */ VARIANT varDirection) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AngleBetween( 
            /* [in] */ IDirection *dir,
            /* [retval][out] */ IAngle **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IDirection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDirectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDirection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDirection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDirection * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Azimuth )( 
            IDirection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IDirection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IDirection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NSDirection )( 
            IDirection * This,
            /* [retval][out] */ NSDirectionType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NSDirection )( 
            IDirection * This,
            /* [in] */ NSDirectionType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EWDirection )( 
            IDirection * This,
            /* [retval][out] */ EWDirectionType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EWDirection )( 
            IDirection * This,
            /* [in] */ EWDirectionType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Degree )( 
            IDirection * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Degree )( 
            IDirection * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Minute )( 
            IDirection * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Minute )( 
            IDirection * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Second )( 
            IDirection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Second )( 
            IDirection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Increment )( 
            IDirection * This,
            /* [in] */ VARIANT varAngle,
            /* [retval][out] */ IDirection **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IncrementBy )( 
            IDirection * This,
            /* [in] */ VARIANT varAngle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FromString )( 
            IDirection * This,
            /* [in] */ BSTR bstrDir);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FromDMS )( 
            IDirection * This,
            /* [in] */ NSDirectionType ns,
            /* [in] */ long Degree,
            /* [in] */ long Minute,
            /* [in] */ Float64 Second,
            /* [in] */ EWDirectionType ew);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FromAzimuth )( 
            IDirection * This,
            /* [in] */ Float64 azimuth);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FromAzimuthEx )( 
            IDirection * This,
            /* [in] */ long Degree,
            /* [in] */ long Minute,
            /* [in] */ Float64 Second);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FromVariant )( 
            IDirection * This,
            /* [in] */ VARIANT varDirection);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AngleBetween )( 
            IDirection * This,
            /* [in] */ IDirection *dir,
            /* [retval][out] */ IAngle **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDirection * This,
            /* [retval][out] */ IDirection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IDirection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IDirectionVtbl;

    interface IDirection
    {
        CONST_VTBL struct IDirectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDirection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDirection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDirection_get_Azimuth(This,pVal)	\
    ( (This)->lpVtbl -> get_Azimuth(This,pVal) ) 

#define IDirection_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define IDirection_put_Value(This,newVal)	\
    ( (This)->lpVtbl -> put_Value(This,newVal) ) 

#define IDirection_get_NSDirection(This,pVal)	\
    ( (This)->lpVtbl -> get_NSDirection(This,pVal) ) 

#define IDirection_put_NSDirection(This,newVal)	\
    ( (This)->lpVtbl -> put_NSDirection(This,newVal) ) 

#define IDirection_get_EWDirection(This,pVal)	\
    ( (This)->lpVtbl -> get_EWDirection(This,pVal) ) 

#define IDirection_put_EWDirection(This,newVal)	\
    ( (This)->lpVtbl -> put_EWDirection(This,newVal) ) 

#define IDirection_get_Degree(This,pVal)	\
    ( (This)->lpVtbl -> get_Degree(This,pVal) ) 

#define IDirection_put_Degree(This,newVal)	\
    ( (This)->lpVtbl -> put_Degree(This,newVal) ) 

#define IDirection_get_Minute(This,pVal)	\
    ( (This)->lpVtbl -> get_Minute(This,pVal) ) 

#define IDirection_put_Minute(This,newVal)	\
    ( (This)->lpVtbl -> put_Minute(This,newVal) ) 

#define IDirection_get_Second(This,pVal)	\
    ( (This)->lpVtbl -> get_Second(This,pVal) ) 

#define IDirection_put_Second(This,newVal)	\
    ( (This)->lpVtbl -> put_Second(This,newVal) ) 

#define IDirection_Increment(This,varAngle,pVal)	\
    ( (This)->lpVtbl -> Increment(This,varAngle,pVal) ) 

#define IDirection_IncrementBy(This,varAngle)	\
    ( (This)->lpVtbl -> IncrementBy(This,varAngle) ) 

#define IDirection_FromString(This,bstrDir)	\
    ( (This)->lpVtbl -> FromString(This,bstrDir) ) 

#define IDirection_FromDMS(This,ns,Degree,Minute,Second,ew)	\
    ( (This)->lpVtbl -> FromDMS(This,ns,Degree,Minute,Second,ew) ) 

#define IDirection_FromAzimuth(This,azimuth)	\
    ( (This)->lpVtbl -> FromAzimuth(This,azimuth) ) 

#define IDirection_FromAzimuthEx(This,Degree,Minute,Second)	\
    ( (This)->lpVtbl -> FromAzimuthEx(This,Degree,Minute,Second) ) 

#define IDirection_FromVariant(This,varDirection)	\
    ( (This)->lpVtbl -> FromVariant(This,varDirection) ) 

#define IDirection_AngleBetween(This,dir,pVal)	\
    ( (This)->lpVtbl -> AngleBetween(This,dir,pVal) ) 

#define IDirection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IDirection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDirection_INTERFACE_DEFINED__ */


#ifndef __IAngleDisplayUnitFormatter_INTERFACE_DEFINED__
#define __IAngleDisplayUnitFormatter_INTERFACE_DEFINED__

/* interface IAngleDisplayUnitFormatter */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAngleDisplayUnitFormatter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("739D2AB4-A3E9-4BCC-AC06-75E8293C08B7")
    IAngleDisplayUnitFormatter : public IDisplayUnitFormatter
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CondensedFormat( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CondensedFormat( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Signed( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Signed( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAngleDisplayUnitFormatterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAngleDisplayUnitFormatter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAngleDisplayUnitFormatter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAngleDisplayUnitFormatter * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *FormatSpecifiers )( 
            IAngleDisplayUnitFormatter * This,
            /* [in] */ Uint32 width,
            /* [in] */ Uint32 precision,
            /* [in] */ TextJustificationType justify,
            /* [in] */ NumericFormatType fmt,
            /* [in] */ Float64 zeroVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IAngleDisplayUnitFormatter * This,
            /* [retval][out] */ Uint32 *val);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Precision )( 
            IAngleDisplayUnitFormatter * This,
            /* [retval][out] */ Uint32 *val);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Notation )( 
            IAngleDisplayUnitFormatter * This,
            /* [retval][out] */ NumericFormatType *notation);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Justification )( 
            IAngleDisplayUnitFormatter * This,
            /* [retval][out] */ TextJustificationType *justify);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZeroTolerance )( 
            IAngleDisplayUnitFormatter * This,
            /* [retval][out] */ Float64 *zeroTol);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Format )( 
            IAngleDisplayUnitFormatter * This,
            /* [in] */ Float64 val,
            /* [in] */ BSTR tag,
            /* [retval][out] */ BSTR *fmtString);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UsesTag )( 
            IAngleDisplayUnitFormatter * This,
            /* [retval][out] */ VARIANT_BOOL *bUsesTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CondensedFormat )( 
            IAngleDisplayUnitFormatter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CondensedFormat )( 
            IAngleDisplayUnitFormatter * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Signed )( 
            IAngleDisplayUnitFormatter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Signed )( 
            IAngleDisplayUnitFormatter * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IAngleDisplayUnitFormatterVtbl;

    interface IAngleDisplayUnitFormatter
    {
        CONST_VTBL struct IAngleDisplayUnitFormatterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAngleDisplayUnitFormatter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAngleDisplayUnitFormatter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAngleDisplayUnitFormatter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAngleDisplayUnitFormatter_FormatSpecifiers(This,width,precision,justify,fmt,zeroVal)	\
    ( (This)->lpVtbl -> FormatSpecifiers(This,width,precision,justify,fmt,zeroVal) ) 

#define IAngleDisplayUnitFormatter_get_Width(This,val)	\
    ( (This)->lpVtbl -> get_Width(This,val) ) 

#define IAngleDisplayUnitFormatter_get_Precision(This,val)	\
    ( (This)->lpVtbl -> get_Precision(This,val) ) 

#define IAngleDisplayUnitFormatter_get_Notation(This,notation)	\
    ( (This)->lpVtbl -> get_Notation(This,notation) ) 

#define IAngleDisplayUnitFormatter_get_Justification(This,justify)	\
    ( (This)->lpVtbl -> get_Justification(This,justify) ) 

#define IAngleDisplayUnitFormatter_get_ZeroTolerance(This,zeroTol)	\
    ( (This)->lpVtbl -> get_ZeroTolerance(This,zeroTol) ) 

#define IAngleDisplayUnitFormatter_Format(This,val,tag,fmtString)	\
    ( (This)->lpVtbl -> Format(This,val,tag,fmtString) ) 

#define IAngleDisplayUnitFormatter_get_UsesTag(This,bUsesTag)	\
    ( (This)->lpVtbl -> get_UsesTag(This,bUsesTag) ) 


#define IAngleDisplayUnitFormatter_get_CondensedFormat(This,pVal)	\
    ( (This)->lpVtbl -> get_CondensedFormat(This,pVal) ) 

#define IAngleDisplayUnitFormatter_put_CondensedFormat(This,newVal)	\
    ( (This)->lpVtbl -> put_CondensedFormat(This,newVal) ) 

#define IAngleDisplayUnitFormatter_get_Signed(This,pVal)	\
    ( (This)->lpVtbl -> get_Signed(This,pVal) ) 

#define IAngleDisplayUnitFormatter_put_Signed(This,newVal)	\
    ( (This)->lpVtbl -> put_Signed(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAngleDisplayUnitFormatter_INTERFACE_DEFINED__ */


#ifndef __IDirectionDisplayUnitFormatter_INTERFACE_DEFINED__
#define __IDirectionDisplayUnitFormatter_INTERFACE_DEFINED__

/* interface IDirectionDisplayUnitFormatter */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDirectionDisplayUnitFormatter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FFA2F69D-8B5B-40ED-9802-35BEA09551B7")
    IDirectionDisplayUnitFormatter : public IDisplayUnitFormatter
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CondensedFormat( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CondensedFormat( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BearingFormat( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BearingFormat( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDirectionDisplayUnitFormatterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDirectionDisplayUnitFormatter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDirectionDisplayUnitFormatter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDirectionDisplayUnitFormatter * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *FormatSpecifiers )( 
            IDirectionDisplayUnitFormatter * This,
            /* [in] */ Uint32 width,
            /* [in] */ Uint32 precision,
            /* [in] */ TextJustificationType justify,
            /* [in] */ NumericFormatType fmt,
            /* [in] */ Float64 zeroVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IDirectionDisplayUnitFormatter * This,
            /* [retval][out] */ Uint32 *val);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Precision )( 
            IDirectionDisplayUnitFormatter * This,
            /* [retval][out] */ Uint32 *val);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Notation )( 
            IDirectionDisplayUnitFormatter * This,
            /* [retval][out] */ NumericFormatType *notation);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Justification )( 
            IDirectionDisplayUnitFormatter * This,
            /* [retval][out] */ TextJustificationType *justify);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZeroTolerance )( 
            IDirectionDisplayUnitFormatter * This,
            /* [retval][out] */ Float64 *zeroTol);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Format )( 
            IDirectionDisplayUnitFormatter * This,
            /* [in] */ Float64 val,
            /* [in] */ BSTR tag,
            /* [retval][out] */ BSTR *fmtString);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UsesTag )( 
            IDirectionDisplayUnitFormatter * This,
            /* [retval][out] */ VARIANT_BOOL *bUsesTag);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CondensedFormat )( 
            IDirectionDisplayUnitFormatter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CondensedFormat )( 
            IDirectionDisplayUnitFormatter * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BearingFormat )( 
            IDirectionDisplayUnitFormatter * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BearingFormat )( 
            IDirectionDisplayUnitFormatter * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IDirectionDisplayUnitFormatterVtbl;

    interface IDirectionDisplayUnitFormatter
    {
        CONST_VTBL struct IDirectionDisplayUnitFormatterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectionDisplayUnitFormatter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDirectionDisplayUnitFormatter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDirectionDisplayUnitFormatter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDirectionDisplayUnitFormatter_FormatSpecifiers(This,width,precision,justify,fmt,zeroVal)	\
    ( (This)->lpVtbl -> FormatSpecifiers(This,width,precision,justify,fmt,zeroVal) ) 

#define IDirectionDisplayUnitFormatter_get_Width(This,val)	\
    ( (This)->lpVtbl -> get_Width(This,val) ) 

#define IDirectionDisplayUnitFormatter_get_Precision(This,val)	\
    ( (This)->lpVtbl -> get_Precision(This,val) ) 

#define IDirectionDisplayUnitFormatter_get_Notation(This,notation)	\
    ( (This)->lpVtbl -> get_Notation(This,notation) ) 

#define IDirectionDisplayUnitFormatter_get_Justification(This,justify)	\
    ( (This)->lpVtbl -> get_Justification(This,justify) ) 

#define IDirectionDisplayUnitFormatter_get_ZeroTolerance(This,zeroTol)	\
    ( (This)->lpVtbl -> get_ZeroTolerance(This,zeroTol) ) 

#define IDirectionDisplayUnitFormatter_Format(This,val,tag,fmtString)	\
    ( (This)->lpVtbl -> Format(This,val,tag,fmtString) ) 

#define IDirectionDisplayUnitFormatter_get_UsesTag(This,bUsesTag)	\
    ( (This)->lpVtbl -> get_UsesTag(This,bUsesTag) ) 


#define IDirectionDisplayUnitFormatter_get_CondensedFormat(This,pVal)	\
    ( (This)->lpVtbl -> get_CondensedFormat(This,pVal) ) 

#define IDirectionDisplayUnitFormatter_put_CondensedFormat(This,newVal)	\
    ( (This)->lpVtbl -> put_CondensedFormat(This,newVal) ) 

#define IDirectionDisplayUnitFormatter_get_BearingFormat(This,pVal)	\
    ( (This)->lpVtbl -> get_BearingFormat(This,pVal) ) 

#define IDirectionDisplayUnitFormatter_put_BearingFormat(This,newVal)	\
    ( (This)->lpVtbl -> put_BearingFormat(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDirectionDisplayUnitFormatter_INTERFACE_DEFINED__ */


#ifndef __IPointEvents_INTERFACE_DEFINED__
#define __IPointEvents_INTERFACE_DEFINED__

/* interface IPointEvents */
/* [unique][helpstring][helpcontext][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IPointEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74B1E8A0-5EAC-11d5-8C32-006097C68A9C")
    IPointEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointChanged( 
            IPoint2d *point) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPointEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointChanged )( 
            IPointEvents * This,
            IPoint2d *point);
        
        END_INTERFACE
    } IPointEventsVtbl;

    interface IPointEvents
    {
        CONST_VTBL struct IPointEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPointEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPointEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPointEvents_OnPointChanged(This,point)	\
    ( (This)->lpVtbl -> OnPointChanged(This,point) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPointEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumIDs_INTERFACE_DEFINED__
#define __IEnumIDs_INTERFACE_DEFINED__

/* interface IEnumIDs */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumIDs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5C3C09D6-5E7F-11d5-8C32-006097C68A9C")
    IEnumIDs : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumIDs **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ CogoObjectID *rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumIDsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumIDs * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumIDs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumIDs * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumIDs * This,
            /* [out] */ IEnumIDs **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumIDs * This,
            /* [in] */ ULONG celt,
            /* [out] */ CogoObjectID *rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumIDs * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumIDs * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumIDsVtbl;

    interface IEnumIDs
    {
        CONST_VTBL struct IEnumIDsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumIDs_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumIDs_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumIDs_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumIDs_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumIDs_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumIDs_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumIDs_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumIDs_INTERFACE_DEFINED__ */


#ifndef __IPointCollection_INTERFACE_DEFINED__
#define __IPointCollection_INTERFACE_DEFINED__

/* interface IPointCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPointCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5559C9A5-5C16-11D5-8C31-006097C68A9C")
    IPointCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ CogoObjectID id,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FindID( 
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumIDs( 
            /* [retval][out] */ IEnumIDs **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Factory( 
            /* [retval][out] */ IPoint2dFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Factory( 
            /* [in] */ IPoint2dFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ID( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumPoints( 
            /* [retval][out] */ IEnumPoint2d **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPointCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPointCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointCollection * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IPointCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPointCollection * This,
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IPointCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPointCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPointCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            IPointCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IPointCollection * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IPointCollection * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindID )( 
            IPointCollection * This,
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumIDs )( 
            IPointCollection * This,
            /* [retval][out] */ IEnumIDs **ppenum);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Factory )( 
            IPointCollection * This,
            /* [retval][out] */ IPoint2dFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Factory )( 
            IPointCollection * This,
            /* [in] */ IPoint2dFactory *factory);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ID )( 
            IPointCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumPoints )( 
            IPointCollection * This,
            /* [retval][out] */ IEnumPoint2d **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPointCollection * This,
            /* [retval][out] */ IPointCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPointCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IPointCollectionVtbl;

    interface IPointCollection
    {
        CONST_VTBL struct IPointCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPointCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPointCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPointCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IPointCollection_get_Item(This,id,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,id,pVal) ) 

#define IPointCollection_putref_Item(This,id,newVal)	\
    ( (This)->lpVtbl -> putref_Item(This,id,newVal) ) 

#define IPointCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPointCollection_Add(This,id,x,y,point)	\
    ( (This)->lpVtbl -> Add(This,id,x,y,point) ) 

#define IPointCollection_AddEx(This,id,newVal)	\
    ( (This)->lpVtbl -> AddEx(This,id,newVal) ) 

#define IPointCollection_Remove(This,id)	\
    ( (This)->lpVtbl -> Remove(This,id) ) 

#define IPointCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IPointCollection_FindID(This,point,ID)	\
    ( (This)->lpVtbl -> FindID(This,point,ID) ) 

#define IPointCollection_get__EnumIDs(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumIDs(This,ppenum) ) 

#define IPointCollection_get_Factory(This,factory)	\
    ( (This)->lpVtbl -> get_Factory(This,factory) ) 

#define IPointCollection_putref_Factory(This,factory)	\
    ( (This)->lpVtbl -> putref_Factory(This,factory) ) 

#define IPointCollection_ID(This,index,ID)	\
    ( (This)->lpVtbl -> ID(This,index,ID) ) 

#define IPointCollection_get__EnumPoints(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumPoints(This,ppenum) ) 

#define IPointCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IPointCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPointCollection_INTERFACE_DEFINED__ */


#ifndef __IPointCollectionEvents_INTERFACE_DEFINED__
#define __IPointCollectionEvents_INTERFACE_DEFINED__

/* interface IPointCollectionEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPointCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74B1E8A1-5EAC-11d5-8C32-006097C68A9C")
    IPointCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointChanged( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointAdded( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointRemoved( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointsCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPointCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointCollectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointChanged )( 
            IPointCollectionEvents * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointAdded )( 
            IPointCollectionEvents * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointRemoved )( 
            IPointCollectionEvents * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointsCleared )( 
            IPointCollectionEvents * This);
        
        END_INTERFACE
    } IPointCollectionEventsVtbl;

    interface IPointCollectionEvents
    {
        CONST_VTBL struct IPointCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPointCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPointCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPointCollectionEvents_OnPointChanged(This,id,point)	\
    ( (This)->lpVtbl -> OnPointChanged(This,id,point) ) 

#define IPointCollectionEvents_OnPointAdded(This,id,point)	\
    ( (This)->lpVtbl -> OnPointAdded(This,id,point) ) 

#define IPointCollectionEvents_OnPointRemoved(This,id)	\
    ( (This)->lpVtbl -> OnPointRemoved(This,id) ) 

#define IPointCollectionEvents_OnPointsCleared(This)	\
    ( (This)->lpVtbl -> OnPointsCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPointCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __IHorzCurve_INTERFACE_DEFINED__
#define __IHorzCurve_INTERFACE_DEFINED__

/* interface IHorzCurve */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IHorzCurve;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7E56BBC9-AC81-4B6D-8366-319DEE51A0D8")
    IHorzCurve : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PBT( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PBT( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PI( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PI( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PFT( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PFT( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Radius( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Radius( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SpiralLength( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SpiralLength( 
            /* [in] */ SpiralType spType,
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SpiralAngle( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ IAngle **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *x) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *y) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Q( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *q) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_T( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *t) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BkTangentBrg( 
            /* [retval][out] */ IDirection **brg) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FwdTangentBrg( 
            /* [retval][out] */ IDirection **brg) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurveAngle( 
            /* [retval][out] */ IAngle **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BkTangentLength( 
            /* [retval][out] */ Float64 *t) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FwdTangentLength( 
            /* [retval][out] */ Float64 *t) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TS( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ST( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SC( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CS( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Chord( 
            /* [retval][out] */ Float64 *chord) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CircularCurveAngle( 
            /* [retval][out] */ IAngle **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tangent( 
            /* [retval][out] */ Float64 *tangent) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MidOrdinate( 
            /* [retval][out] */ Float64 *mo) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_External( 
            /* [retval][out] */ Float64 *external) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DE( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ IAngle **pDE) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LongTangent( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *u) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShortTangent( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *v) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CC( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PCI( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SPI( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ IPoint2d **pSPI) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurveBkTangentBrg( 
            /* [retval][out] */ IDirection **brg) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurveFwdTangentBrg( 
            /* [retval][out] */ IDirection **brg) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CCC( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DF( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ IAngle **pDF) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DH( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ IAngle **pDH) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SpiralChord( 
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *cs) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ CurveDirectionType *dir) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurveLength( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TotalLength( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DegreeCurvature( 
            /* [in] */ Float64 D,
            /* [in] */ DegreeCurvatureType dcMethod,
            /* [retval][out] */ IAngle **pDC) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Bearing( 
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Normal( 
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnCurve( 
            /* [in] */ Float64 distance,
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ProjectPoint( 
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ IPoint2d **pNewPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DistanceFromStart( 
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ Float64 *dist) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Intersect( 
            /* [in] */ ILine2d *line,
            /* [in] */ VARIANT_BOOL bProjectBack,
            /* [in] */ VARIANT_BOOL bProjectAhead,
            /* [out] */ IPoint2d **p1,
            /* [out] */ IPoint2d **p2) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PointFactory( 
            /* [retval][out] */ IPoint2dFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PointFactory( 
            /* [in] */ IPoint2dFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IHorzCurve **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IHorzCurveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHorzCurve * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHorzCurve * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHorzCurve * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PBT )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PBT )( 
            IHorzCurve * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PI )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PI )( 
            IHorzCurve * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PFT )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PFT )( 
            IHorzCurve * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Radius )( 
            IHorzCurve * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Radius )( 
            IHorzCurve * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpiralLength )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SpiralLength )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpiralAngle )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ IAngle **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *x);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *y);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Q )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *q);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *t);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BkTangentBrg )( 
            IHorzCurve * This,
            /* [retval][out] */ IDirection **brg);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FwdTangentBrg )( 
            IHorzCurve * This,
            /* [retval][out] */ IDirection **brg);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurveAngle )( 
            IHorzCurve * This,
            /* [retval][out] */ IAngle **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BkTangentLength )( 
            IHorzCurve * This,
            /* [retval][out] */ Float64 *t);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FwdTangentLength )( 
            IHorzCurve * This,
            /* [retval][out] */ Float64 *t);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TS )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ST )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SC )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CS )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Chord )( 
            IHorzCurve * This,
            /* [retval][out] */ Float64 *chord);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CircularCurveAngle )( 
            IHorzCurve * This,
            /* [retval][out] */ IAngle **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tangent )( 
            IHorzCurve * This,
            /* [retval][out] */ Float64 *tangent);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MidOrdinate )( 
            IHorzCurve * This,
            /* [retval][out] */ Float64 *mo);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_External )( 
            IHorzCurve * This,
            /* [retval][out] */ Float64 *external);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DE )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ IAngle **pDE);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LongTangent )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *u);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShortTangent )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *v);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CC )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PCI )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SPI )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ IPoint2d **pSPI);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurveBkTangentBrg )( 
            IHorzCurve * This,
            /* [retval][out] */ IDirection **brg);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurveFwdTangentBrg )( 
            IHorzCurve * This,
            /* [retval][out] */ IDirection **brg);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CCC )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DF )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ IAngle **pDF);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DH )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ IAngle **pDH);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpiralChord )( 
            IHorzCurve * This,
            /* [in] */ SpiralType spType,
            /* [retval][out] */ Float64 *cs);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Direction )( 
            IHorzCurve * This,
            /* [retval][out] */ CurveDirectionType *dir);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurveLength )( 
            IHorzCurve * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TotalLength )( 
            IHorzCurve * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DegreeCurvature )( 
            IHorzCurve * This,
            /* [in] */ Float64 D,
            /* [in] */ DegreeCurvatureType dcMethod,
            /* [retval][out] */ IAngle **pDC);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Bearing )( 
            IHorzCurve * This,
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Normal )( 
            IHorzCurve * This,
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnCurve )( 
            IHorzCurve * This,
            /* [in] */ Float64 distance,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectPoint )( 
            IHorzCurve * This,
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ IPoint2d **pNewPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DistanceFromStart )( 
            IHorzCurve * This,
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ Float64 *dist);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Intersect )( 
            IHorzCurve * This,
            /* [in] */ ILine2d *line,
            /* [in] */ VARIANT_BOOL bProjectBack,
            /* [in] */ VARIANT_BOOL bProjectAhead,
            /* [out] */ IPoint2d **p1,
            /* [out] */ IPoint2d **p2);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointFactory )( 
            IHorzCurve * This,
            /* [retval][out] */ IPoint2dFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PointFactory )( 
            IHorzCurve * This,
            /* [in] */ IPoint2dFactory *factory);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IHorzCurve * This,
            /* [retval][out] */ IHorzCurve **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IHorzCurve * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IHorzCurve * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IHorzCurveVtbl;

    interface IHorzCurve
    {
        CONST_VTBL struct IHorzCurveVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHorzCurve_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHorzCurve_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHorzCurve_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHorzCurve_get_PBT(This,pVal)	\
    ( (This)->lpVtbl -> get_PBT(This,pVal) ) 

#define IHorzCurve_putref_PBT(This,newVal)	\
    ( (This)->lpVtbl -> putref_PBT(This,newVal) ) 

#define IHorzCurve_get_PI(This,pVal)	\
    ( (This)->lpVtbl -> get_PI(This,pVal) ) 

#define IHorzCurve_putref_PI(This,newVal)	\
    ( (This)->lpVtbl -> putref_PI(This,newVal) ) 

#define IHorzCurve_get_PFT(This,pVal)	\
    ( (This)->lpVtbl -> get_PFT(This,pVal) ) 

#define IHorzCurve_putref_PFT(This,newVal)	\
    ( (This)->lpVtbl -> putref_PFT(This,newVal) ) 

#define IHorzCurve_get_Radius(This,pVal)	\
    ( (This)->lpVtbl -> get_Radius(This,pVal) ) 

#define IHorzCurve_put_Radius(This,newVal)	\
    ( (This)->lpVtbl -> put_Radius(This,newVal) ) 

#define IHorzCurve_get_SpiralLength(This,spType,pVal)	\
    ( (This)->lpVtbl -> get_SpiralLength(This,spType,pVal) ) 

#define IHorzCurve_put_SpiralLength(This,spType,newVal)	\
    ( (This)->lpVtbl -> put_SpiralLength(This,spType,newVal) ) 

#define IHorzCurve_get_SpiralAngle(This,spType,pVal)	\
    ( (This)->lpVtbl -> get_SpiralAngle(This,spType,pVal) ) 

#define IHorzCurve_get_X(This,spType,x)	\
    ( (This)->lpVtbl -> get_X(This,spType,x) ) 

#define IHorzCurve_get_Y(This,spType,y)	\
    ( (This)->lpVtbl -> get_Y(This,spType,y) ) 

#define IHorzCurve_get_Q(This,spType,q)	\
    ( (This)->lpVtbl -> get_Q(This,spType,q) ) 

#define IHorzCurve_get_T(This,spType,t)	\
    ( (This)->lpVtbl -> get_T(This,spType,t) ) 

#define IHorzCurve_get_BkTangentBrg(This,brg)	\
    ( (This)->lpVtbl -> get_BkTangentBrg(This,brg) ) 

#define IHorzCurve_get_FwdTangentBrg(This,brg)	\
    ( (This)->lpVtbl -> get_FwdTangentBrg(This,brg) ) 

#define IHorzCurve_get_CurveAngle(This,pVal)	\
    ( (This)->lpVtbl -> get_CurveAngle(This,pVal) ) 

#define IHorzCurve_get_BkTangentLength(This,t)	\
    ( (This)->lpVtbl -> get_BkTangentLength(This,t) ) 

#define IHorzCurve_get_FwdTangentLength(This,t)	\
    ( (This)->lpVtbl -> get_FwdTangentLength(This,t) ) 

#define IHorzCurve_get_TS(This,pVal)	\
    ( (This)->lpVtbl -> get_TS(This,pVal) ) 

#define IHorzCurve_get_ST(This,pVal)	\
    ( (This)->lpVtbl -> get_ST(This,pVal) ) 

#define IHorzCurve_get_SC(This,pVal)	\
    ( (This)->lpVtbl -> get_SC(This,pVal) ) 

#define IHorzCurve_get_CS(This,pVal)	\
    ( (This)->lpVtbl -> get_CS(This,pVal) ) 

#define IHorzCurve_get_Chord(This,chord)	\
    ( (This)->lpVtbl -> get_Chord(This,chord) ) 

#define IHorzCurve_get_CircularCurveAngle(This,pVal)	\
    ( (This)->lpVtbl -> get_CircularCurveAngle(This,pVal) ) 

#define IHorzCurve_get_Tangent(This,tangent)	\
    ( (This)->lpVtbl -> get_Tangent(This,tangent) ) 

#define IHorzCurve_get_MidOrdinate(This,mo)	\
    ( (This)->lpVtbl -> get_MidOrdinate(This,mo) ) 

#define IHorzCurve_get_External(This,external)	\
    ( (This)->lpVtbl -> get_External(This,external) ) 

#define IHorzCurve_get_DE(This,spType,pDE)	\
    ( (This)->lpVtbl -> get_DE(This,spType,pDE) ) 

#define IHorzCurve_get_LongTangent(This,spType,u)	\
    ( (This)->lpVtbl -> get_LongTangent(This,spType,u) ) 

#define IHorzCurve_get_ShortTangent(This,spType,v)	\
    ( (This)->lpVtbl -> get_ShortTangent(This,spType,v) ) 

#define IHorzCurve_get_CC(This,pVal)	\
    ( (This)->lpVtbl -> get_CC(This,pVal) ) 

#define IHorzCurve_get_PCI(This,pVal)	\
    ( (This)->lpVtbl -> get_PCI(This,pVal) ) 

#define IHorzCurve_get_SPI(This,spType,pSPI)	\
    ( (This)->lpVtbl -> get_SPI(This,spType,pSPI) ) 

#define IHorzCurve_get_CurveBkTangentBrg(This,brg)	\
    ( (This)->lpVtbl -> get_CurveBkTangentBrg(This,brg) ) 

#define IHorzCurve_get_CurveFwdTangentBrg(This,brg)	\
    ( (This)->lpVtbl -> get_CurveFwdTangentBrg(This,brg) ) 

#define IHorzCurve_get_CCC(This,pVal)	\
    ( (This)->lpVtbl -> get_CCC(This,pVal) ) 

#define IHorzCurve_get_DF(This,spType,pDF)	\
    ( (This)->lpVtbl -> get_DF(This,spType,pDF) ) 

#define IHorzCurve_get_DH(This,spType,pDH)	\
    ( (This)->lpVtbl -> get_DH(This,spType,pDH) ) 

#define IHorzCurve_get_SpiralChord(This,spType,cs)	\
    ( (This)->lpVtbl -> get_SpiralChord(This,spType,cs) ) 

#define IHorzCurve_get_Direction(This,dir)	\
    ( (This)->lpVtbl -> get_Direction(This,dir) ) 

#define IHorzCurve_get_CurveLength(This,pVal)	\
    ( (This)->lpVtbl -> get_CurveLength(This,pVal) ) 

#define IHorzCurve_get_TotalLength(This,pVal)	\
    ( (This)->lpVtbl -> get_TotalLength(This,pVal) ) 

#define IHorzCurve_get_DegreeCurvature(This,D,dcMethod,pDC)	\
    ( (This)->lpVtbl -> get_DegreeCurvature(This,D,dcMethod,pDC) ) 

#define IHorzCurve_Bearing(This,distance,pVal)	\
    ( (This)->lpVtbl -> Bearing(This,distance,pVal) ) 

#define IHorzCurve_Normal(This,distance,pVal)	\
    ( (This)->lpVtbl -> Normal(This,distance,pVal) ) 

#define IHorzCurve_PointOnCurve(This,distance,pVal)	\
    ( (This)->lpVtbl -> PointOnCurve(This,distance,pVal) ) 

#define IHorzCurve_ProjectPoint(This,point,pNewPoint)	\
    ( (This)->lpVtbl -> ProjectPoint(This,point,pNewPoint) ) 

#define IHorzCurve_DistanceFromStart(This,point,dist)	\
    ( (This)->lpVtbl -> DistanceFromStart(This,point,dist) ) 

#define IHorzCurve_Intersect(This,line,bProjectBack,bProjectAhead,p1,p2)	\
    ( (This)->lpVtbl -> Intersect(This,line,bProjectBack,bProjectAhead,p1,p2) ) 

#define IHorzCurve_get_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> get_PointFactory(This,factory) ) 

#define IHorzCurve_putref_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_PointFactory(This,factory) ) 

#define IHorzCurve_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IHorzCurve_Offset(This,dx,dy)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy) ) 

#define IHorzCurve_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHorzCurve_INTERFACE_DEFINED__ */


#ifndef __IHorzCurveEvents_INTERFACE_DEFINED__
#define __IHorzCurveEvents_INTERFACE_DEFINED__

/* interface IHorzCurveEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IHorzCurveEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4726E8C7-5B74-4cda-844B-4F7B1B5AB1ED")
    IHorzCurveEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnHorzCurveChanged( 
            /* [in] */ IHorzCurve *hc) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IHorzCurveEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHorzCurveEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHorzCurveEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHorzCurveEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnHorzCurveChanged )( 
            IHorzCurveEvents * This,
            /* [in] */ IHorzCurve *hc);
        
        END_INTERFACE
    } IHorzCurveEventsVtbl;

    interface IHorzCurveEvents
    {
        CONST_VTBL struct IHorzCurveEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHorzCurveEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHorzCurveEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHorzCurveEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHorzCurveEvents_OnHorzCurveChanged(This,hc)	\
    ( (This)->lpVtbl -> OnHorzCurveChanged(This,hc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHorzCurveEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumLineSegments_INTERFACE_DEFINED__
#define __IEnumLineSegments_INTERFACE_DEFINED__

/* interface IEnumLineSegments */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumLineSegments;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B5850388-0046-4491-BE25-9EC1E6B66344")
    IEnumLineSegments : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumLineSegments **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ILineSegment2d **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumLineSegmentsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumLineSegments * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumLineSegments * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumLineSegments * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumLineSegments * This,
            /* [out] */ IEnumLineSegments **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumLineSegments * This,
            /* [in] */ ULONG celt,
            /* [out] */ ILineSegment2d **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumLineSegments * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumLineSegments * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumLineSegmentsVtbl;

    interface IEnumLineSegments
    {
        CONST_VTBL struct IEnumLineSegmentsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumLineSegments_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumLineSegments_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumLineSegments_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumLineSegments_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumLineSegments_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumLineSegments_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumLineSegments_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumLineSegments_INTERFACE_DEFINED__ */


#ifndef __ILineSegmentCollection_INTERFACE_DEFINED__
#define __ILineSegmentCollection_INTERFACE_DEFINED__

/* interface ILineSegmentCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILineSegmentCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43D1CADC-0D31-4C0D-868F-F890B3C09AD2")
    ILineSegmentCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ ILineSegment2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *start,
            /* [in] */ IPoint2d *end,
            /* [retval][out] */ ILineSegment2d **ls) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FindID( 
            /* [in] */ ILineSegment2d *ls,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumIDs( 
            /* [retval][out] */ IEnumIDs **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Factory( 
            /* [retval][out] */ ILineSegment2dFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Factory( 
            /* [in] */ ILineSegment2dFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ID( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumLineSegments( 
            /* [retval][out] */ IEnumLineSegments **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILineSegmentCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILineSegmentCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILineSegmentCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILineSegmentCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILineSegmentCollection * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ILineSegmentCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ILineSegmentCollection * This,
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ ILineSegment2d **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            ILineSegmentCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILineSegmentCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILineSegmentCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *start,
            /* [in] */ IPoint2d *end,
            /* [retval][out] */ ILineSegment2d **ls);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            ILineSegmentCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ILineSegmentCollection * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILineSegmentCollection * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindID )( 
            ILineSegmentCollection * This,
            /* [in] */ ILineSegment2d *ls,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumIDs )( 
            ILineSegmentCollection * This,
            /* [retval][out] */ IEnumIDs **ppenum);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Factory )( 
            ILineSegmentCollection * This,
            /* [retval][out] */ ILineSegment2dFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Factory )( 
            ILineSegmentCollection * This,
            /* [in] */ ILineSegment2dFactory *factory);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ID )( 
            ILineSegmentCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumLineSegments )( 
            ILineSegmentCollection * This,
            /* [retval][out] */ IEnumLineSegments **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILineSegmentCollection * This,
            /* [retval][out] */ ILineSegmentCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ILineSegmentCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ILineSegmentCollectionVtbl;

    interface ILineSegmentCollection
    {
        CONST_VTBL struct ILineSegmentCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILineSegmentCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILineSegmentCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILineSegmentCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILineSegmentCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ILineSegmentCollection_get_Item(This,id,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,id,pVal) ) 

#define ILineSegmentCollection_putref_Item(This,id,newVal)	\
    ( (This)->lpVtbl -> putref_Item(This,id,newVal) ) 

#define ILineSegmentCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILineSegmentCollection_Add(This,id,start,end,ls)	\
    ( (This)->lpVtbl -> Add(This,id,start,end,ls) ) 

#define ILineSegmentCollection_AddEx(This,id,newVal)	\
    ( (This)->lpVtbl -> AddEx(This,id,newVal) ) 

#define ILineSegmentCollection_Remove(This,id)	\
    ( (This)->lpVtbl -> Remove(This,id) ) 

#define ILineSegmentCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILineSegmentCollection_FindID(This,ls,ID)	\
    ( (This)->lpVtbl -> FindID(This,ls,ID) ) 

#define ILineSegmentCollection_get__EnumIDs(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumIDs(This,ppenum) ) 

#define ILineSegmentCollection_get_Factory(This,factory)	\
    ( (This)->lpVtbl -> get_Factory(This,factory) ) 

#define ILineSegmentCollection_putref_Factory(This,factory)	\
    ( (This)->lpVtbl -> putref_Factory(This,factory) ) 

#define ILineSegmentCollection_ID(This,index,ID)	\
    ( (This)->lpVtbl -> ID(This,index,ID) ) 

#define ILineSegmentCollection_get__EnumLineSegments(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumLineSegments(This,ppenum) ) 

#define ILineSegmentCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ILineSegmentCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILineSegmentCollection_INTERFACE_DEFINED__ */


#ifndef __ILineSegmentCollectionEvents_INTERFACE_DEFINED__
#define __ILineSegmentCollectionEvents_INTERFACE_DEFINED__

/* interface ILineSegmentCollectionEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILineSegmentCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("99FA2E81-A3FB-4b10-A9A6-FB1F4F6CDE75")
    ILineSegmentCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLineSegmentChanged( 
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *lineSeg) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLineSegmentAdded( 
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *lineSeg) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLineSegmentRemoved( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLineSegmentsCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILineSegmentCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILineSegmentCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILineSegmentCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILineSegmentCollectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLineSegmentChanged )( 
            ILineSegmentCollectionEvents * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *lineSeg);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLineSegmentAdded )( 
            ILineSegmentCollectionEvents * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *lineSeg);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLineSegmentRemoved )( 
            ILineSegmentCollectionEvents * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLineSegmentsCleared )( 
            ILineSegmentCollectionEvents * This);
        
        END_INTERFACE
    } ILineSegmentCollectionEventsVtbl;

    interface ILineSegmentCollectionEvents
    {
        CONST_VTBL struct ILineSegmentCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILineSegmentCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILineSegmentCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILineSegmentCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILineSegmentCollectionEvents_OnLineSegmentChanged(This,id,lineSeg)	\
    ( (This)->lpVtbl -> OnLineSegmentChanged(This,id,lineSeg) ) 

#define ILineSegmentCollectionEvents_OnLineSegmentAdded(This,id,lineSeg)	\
    ( (This)->lpVtbl -> OnLineSegmentAdded(This,id,lineSeg) ) 

#define ILineSegmentCollectionEvents_OnLineSegmentRemoved(This,id)	\
    ( (This)->lpVtbl -> OnLineSegmentRemoved(This,id) ) 

#define ILineSegmentCollectionEvents_OnLineSegmentsCleared(This)	\
    ( (This)->lpVtbl -> OnLineSegmentsCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILineSegmentCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __IStation_INTERFACE_DEFINED__
#define __IStation_INTERFACE_DEFINED__

/* interface IStation */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("337799AD-766C-4FB7-A238-9A4C61FFBE29")
    IStation : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FromVariant( 
            /* [in] */ VARIANT varStation) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StationZoneIndex( 
            /* [retval][out] */ ZoneIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StationZoneIndex( 
            /* [in] */ ZoneIndexType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStation( 
            /* [out] */ ZoneIndexType *pZoneIdx,
            /* [out] */ Float64 *pStation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetStation( 
            /* [in] */ ZoneIndexType zoneIdx,
            /* [in] */ Float64 station) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NormalizedValue( 
            /* [in] */ IAlignment *pAlignment,
            /* [retval][out] */ Float64 *pValue) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FromString( 
            /* [in] */ BSTR station,
            /* [in] */ UnitModeType unitMode) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AsString( 
            /* [in] */ UnitModeType unitMode,
            /* [in] */ VARIANT_BOOL vbIncludeStationZone,
            /* [retval][out] */ BSTR *station) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IStation **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStation * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStation * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FromVariant )( 
            IStation * This,
            /* [in] */ VARIANT varStation);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StationZoneIndex )( 
            IStation * This,
            /* [retval][out] */ ZoneIndexType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StationZoneIndex )( 
            IStation * This,
            /* [in] */ ZoneIndexType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IStation * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IStation * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStation )( 
            IStation * This,
            /* [out] */ ZoneIndexType *pZoneIdx,
            /* [out] */ Float64 *pStation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetStation )( 
            IStation * This,
            /* [in] */ ZoneIndexType zoneIdx,
            /* [in] */ Float64 station);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NormalizedValue )( 
            IStation * This,
            /* [in] */ IAlignment *pAlignment,
            /* [retval][out] */ Float64 *pValue);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FromString )( 
            IStation * This,
            /* [in] */ BSTR station,
            /* [in] */ UnitModeType unitMode);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsString )( 
            IStation * This,
            /* [in] */ UnitModeType unitMode,
            /* [in] */ VARIANT_BOOL vbIncludeStationZone,
            /* [retval][out] */ BSTR *station);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IStation * This,
            /* [retval][out] */ IStation **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IStation * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IStationVtbl;

    interface IStation
    {
        CONST_VTBL struct IStationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStation_FromVariant(This,varStation)	\
    ( (This)->lpVtbl -> FromVariant(This,varStation) ) 

#define IStation_get_StationZoneIndex(This,pVal)	\
    ( (This)->lpVtbl -> get_StationZoneIndex(This,pVal) ) 

#define IStation_put_StationZoneIndex(This,newVal)	\
    ( (This)->lpVtbl -> put_StationZoneIndex(This,newVal) ) 

#define IStation_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define IStation_put_Value(This,newVal)	\
    ( (This)->lpVtbl -> put_Value(This,newVal) ) 

#define IStation_GetStation(This,pZoneIdx,pStation)	\
    ( (This)->lpVtbl -> GetStation(This,pZoneIdx,pStation) ) 

#define IStation_SetStation(This,zoneIdx,station)	\
    ( (This)->lpVtbl -> SetStation(This,zoneIdx,station) ) 

#define IStation_get_NormalizedValue(This,pAlignment,pValue)	\
    ( (This)->lpVtbl -> get_NormalizedValue(This,pAlignment,pValue) ) 

#define IStation_FromString(This,station,unitMode)	\
    ( (This)->lpVtbl -> FromString(This,station,unitMode) ) 

#define IStation_AsString(This,unitMode,vbIncludeStationZone,station)	\
    ( (This)->lpVtbl -> AsString(This,unitMode,vbIncludeStationZone,station) ) 

#define IStation_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IStation_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStation_INTERFACE_DEFINED__ */


#ifndef __IStationEvents_INTERFACE_DEFINED__
#define __IStationEvents_INTERFACE_DEFINED__

/* interface IStationEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStationEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6FA473B2-94F8-4b46-9E28-1E05C17BFE79")
    IStationEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStationChanged( 
            ZoneIndexType zoneIdx,
            Float64 station) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStationEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStationEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStationEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStationEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStationChanged )( 
            IStationEvents * This,
            ZoneIndexType zoneIdx,
            Float64 station);
        
        END_INTERFACE
    } IStationEventsVtbl;

    interface IStationEvents
    {
        CONST_VTBL struct IStationEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStationEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStationEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStationEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStationEvents_OnStationChanged(This,zoneIdx,station)	\
    ( (This)->lpVtbl -> OnStationChanged(This,zoneIdx,station) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStationEvents_INTERFACE_DEFINED__ */


#ifndef __IStationEquation_INTERFACE_DEFINED__
#define __IStationEquation_INTERFACE_DEFINED__

/* interface IStationEquation */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStationEquation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F3EE95F1-C4B9-4c9b-9B44-17DC06F7444A")
    IStationEquation : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetEquation( 
            /* [out] */ Float64 *pBackStation,
            /* [out] */ Float64 *pAheadStation) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Back( 
            /* [retval][out] */ Float64 *pBack) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ahead( 
            /* [retval][out] */ Float64 *pAhead) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NormalizedValue( 
            /* [retval][out] */ Float64 *pNormalizedValue) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStationEquationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStationEquation * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStationEquation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStationEquation * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEquation )( 
            IStationEquation * This,
            /* [out] */ Float64 *pBackStation,
            /* [out] */ Float64 *pAheadStation);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Back )( 
            IStationEquation * This,
            /* [retval][out] */ Float64 *pBack);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ahead )( 
            IStationEquation * This,
            /* [retval][out] */ Float64 *pAhead);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NormalizedValue )( 
            IStationEquation * This,
            /* [retval][out] */ Float64 *pNormalizedValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IStationEquation * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IStationEquationVtbl;

    interface IStationEquation
    {
        CONST_VTBL struct IStationEquationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStationEquation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStationEquation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStationEquation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStationEquation_GetEquation(This,pBackStation,pAheadStation)	\
    ( (This)->lpVtbl -> GetEquation(This,pBackStation,pAheadStation) ) 

#define IStationEquation_get_Back(This,pBack)	\
    ( (This)->lpVtbl -> get_Back(This,pBack) ) 

#define IStationEquation_get_Ahead(This,pAhead)	\
    ( (This)->lpVtbl -> get_Ahead(This,pAhead) ) 

#define IStationEquation_get_NormalizedValue(This,pNormalizedValue)	\
    ( (This)->lpVtbl -> get_NormalizedValue(This,pNormalizedValue) ) 

#define IStationEquation_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStationEquation_INTERFACE_DEFINED__ */


#ifndef __IEnumStationEquations_INTERFACE_DEFINED__
#define __IEnumStationEquations_INTERFACE_DEFINED__

/* interface IEnumStationEquations */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumStationEquations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("90A4A76D-EE9D-46c3-8FC6-17786B062164")
    IEnumStationEquations : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumStationEquations **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IStationEquation **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumStationEquationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumStationEquations * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumStationEquations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumStationEquations * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumStationEquations * This,
            /* [out] */ IEnumStationEquations **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumStationEquations * This,
            /* [in] */ ULONG celt,
            /* [out] */ IStationEquation **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumStationEquations * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumStationEquations * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumStationEquationsVtbl;

    interface IEnumStationEquations
    {
        CONST_VTBL struct IEnumStationEquationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumStationEquations_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumStationEquations_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumStationEquations_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumStationEquations_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumStationEquations_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumStationEquations_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumStationEquations_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumStationEquations_INTERFACE_DEFINED__ */


#ifndef __IStationEquationCollection_INTERFACE_DEFINED__
#define __IStationEquationCollection_INTERFACE_DEFINED__

/* interface IStationEquationCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStationEquationCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DA2874E5-2A2E-439f-B35A-708863DA91E6")
    IStationEquationCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Alignment( 
            /* [retval][out] */ IAlignment **ppAlignment) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IStationEquation **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ Float64 back,
            /* [in] */ Float64 ahead,
            /* [retval][out] */ IStationEquation **pp) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumStationEquations( 
            /* [retval][out] */ IEnumStationEquations **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Distance( 
            /* [in] */ VARIANT varStation1,
            /* [in] */ VARIANT varStation2,
            /* [retval][out] */ Float64 *pDist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Increment( 
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 value,
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IncrementBy( 
            /* [in] */ IStation *station,
            /* [in] */ Float64 value) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertToNormalizedStation( 
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ Float64 *station) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertToNormalizedStationEx( 
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertFromNormalizedStation( 
            /* [in] */ Float64 normalizedStation,
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertFromNormalizedStationEx( 
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStationEquationCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStationEquationCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStationEquationCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStationEquationCollection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alignment )( 
            IStationEquationCollection * This,
            /* [retval][out] */ IAlignment **ppAlignment);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IStationEquationCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IStationEquationCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IStationEquation **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IStationEquationCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IStationEquationCollection * This,
            /* [in] */ Float64 back,
            /* [in] */ Float64 ahead,
            /* [retval][out] */ IStationEquation **pp);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IStationEquationCollection * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IStationEquationCollection * This);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumStationEquations )( 
            IStationEquationCollection * This,
            /* [retval][out] */ IEnumStationEquations **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Distance )( 
            IStationEquationCollection * This,
            /* [in] */ VARIANT varStation1,
            /* [in] */ VARIANT varStation2,
            /* [retval][out] */ Float64 *pDist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Increment )( 
            IStationEquationCollection * This,
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 value,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IncrementBy )( 
            IStationEquationCollection * This,
            /* [in] */ IStation *station,
            /* [in] */ Float64 value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertToNormalizedStation )( 
            IStationEquationCollection * This,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ Float64 *station);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertToNormalizedStationEx )( 
            IStationEquationCollection * This,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertFromNormalizedStation )( 
            IStationEquationCollection * This,
            /* [in] */ Float64 normalizedStation,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConvertFromNormalizedStationEx )( 
            IStationEquationCollection * This,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IStationEquationCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IStationEquationCollectionVtbl;

    interface IStationEquationCollection
    {
        CONST_VTBL struct IStationEquationCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStationEquationCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStationEquationCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStationEquationCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStationEquationCollection_get_Alignment(This,ppAlignment)	\
    ( (This)->lpVtbl -> get_Alignment(This,ppAlignment) ) 

#define IStationEquationCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IStationEquationCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IStationEquationCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IStationEquationCollection_Add(This,back,ahead,pp)	\
    ( (This)->lpVtbl -> Add(This,back,ahead,pp) ) 

#define IStationEquationCollection_Remove(This,idx)	\
    ( (This)->lpVtbl -> Remove(This,idx) ) 

#define IStationEquationCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IStationEquationCollection_get__EnumStationEquations(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumStationEquations(This,ppenum) ) 

#define IStationEquationCollection_Distance(This,varStation1,varStation2,pDist)	\
    ( (This)->lpVtbl -> Distance(This,varStation1,varStation2,pDist) ) 

#define IStationEquationCollection_Increment(This,varStation,value,station)	\
    ( (This)->lpVtbl -> Increment(This,varStation,value,station) ) 

#define IStationEquationCollection_IncrementBy(This,station,value)	\
    ( (This)->lpVtbl -> IncrementBy(This,station,value) ) 

#define IStationEquationCollection_ConvertToNormalizedStation(This,varStation,station)	\
    ( (This)->lpVtbl -> ConvertToNormalizedStation(This,varStation,station) ) 

#define IStationEquationCollection_ConvertToNormalizedStationEx(This,varStation,station)	\
    ( (This)->lpVtbl -> ConvertToNormalizedStationEx(This,varStation,station) ) 

#define IStationEquationCollection_ConvertFromNormalizedStation(This,normalizedStation,station)	\
    ( (This)->lpVtbl -> ConvertFromNormalizedStation(This,normalizedStation,station) ) 

#define IStationEquationCollection_ConvertFromNormalizedStationEx(This,varStation,station)	\
    ( (This)->lpVtbl -> ConvertFromNormalizedStationEx(This,varStation,station) ) 

#define IStationEquationCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStationEquationCollection_INTERFACE_DEFINED__ */


#ifndef __IStationEquationCollectionEvents_INTERFACE_DEFINED__
#define __IStationEquationCollectionEvents_INTERFACE_DEFINED__

/* interface IStationEquationCollectionEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStationEquationCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("459B10C5-0C87-4db8-9C2C-2AC15DD03A90")
    IStationEquationCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnEquationAdded( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IStationEquation *pp) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnEquationRemoved( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnEquationsCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStationEquationCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStationEquationCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStationEquationCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStationEquationCollectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnEquationAdded )( 
            IStationEquationCollectionEvents * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IStationEquation *pp);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnEquationRemoved )( 
            IStationEquationCollectionEvents * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnEquationsCleared )( 
            IStationEquationCollectionEvents * This);
        
        END_INTERFACE
    } IStationEquationCollectionEventsVtbl;

    interface IStationEquationCollectionEvents
    {
        CONST_VTBL struct IStationEquationCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStationEquationCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStationEquationCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStationEquationCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStationEquationCollectionEvents_OnEquationAdded(This,idx,pp)	\
    ( (This)->lpVtbl -> OnEquationAdded(This,idx,pp) ) 

#define IStationEquationCollectionEvents_OnEquationRemoved(This,idx)	\
    ( (This)->lpVtbl -> OnEquationRemoved(This,idx) ) 

#define IStationEquationCollectionEvents_OnEquationsCleared(This)	\
    ( (This)->lpVtbl -> OnEquationsCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStationEquationCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __IProfilePoint_INTERFACE_DEFINED__
#define __IProfilePoint_INTERFACE_DEFINED__

/* interface IProfilePoint */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProfilePoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2D5F25CA-875B-484F-B4D0-AB02B0522EC2")
    IProfilePoint : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IProfile **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Profile( 
            /* [in] */ IProfile *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Station( 
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Station( 
            /* [in] */ VARIANT varStation) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Elevation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Elevation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IProfilePoint **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProfilePointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProfilePoint * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProfilePoint * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProfilePoint * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IProfilePoint * This,
            /* [retval][out] */ IProfile **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Profile )( 
            IProfilePoint * This,
            /* [in] */ IProfile *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Station )( 
            IProfilePoint * This,
            /* [retval][out] */ IStation **station);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Station )( 
            IProfilePoint * This,
            /* [in] */ VARIANT varStation);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Elevation )( 
            IProfilePoint * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Elevation )( 
            IProfilePoint * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IProfilePoint * This,
            /* [retval][out] */ IProfilePoint **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IProfilePoint * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IProfilePointVtbl;

    interface IProfilePoint
    {
        CONST_VTBL struct IProfilePointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProfilePoint_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProfilePoint_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProfilePoint_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProfilePoint_get_Profile(This,pVal)	\
    ( (This)->lpVtbl -> get_Profile(This,pVal) ) 

#define IProfilePoint_putref_Profile(This,newVal)	\
    ( (This)->lpVtbl -> putref_Profile(This,newVal) ) 

#define IProfilePoint_get_Station(This,station)	\
    ( (This)->lpVtbl -> get_Station(This,station) ) 

#define IProfilePoint_put_Station(This,varStation)	\
    ( (This)->lpVtbl -> put_Station(This,varStation) ) 

#define IProfilePoint_get_Elevation(This,pVal)	\
    ( (This)->lpVtbl -> get_Elevation(This,pVal) ) 

#define IProfilePoint_put_Elevation(This,newVal)	\
    ( (This)->lpVtbl -> put_Elevation(This,newVal) ) 

#define IProfilePoint_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IProfilePoint_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProfilePoint_INTERFACE_DEFINED__ */


#ifndef __IProfilePointEvents_INTERFACE_DEFINED__
#define __IProfilePointEvents_INTERFACE_DEFINED__

/* interface IProfilePointEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProfilePointEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E4FDF7A1-F29D-4e44-812F-8401A67E5B09")
    IProfilePointEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfilePointChanged( 
            /* [in] */ IProfilePoint *pp) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProfilePointEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProfilePointEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProfilePointEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProfilePointEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfilePointChanged )( 
            IProfilePointEvents * This,
            /* [in] */ IProfilePoint *pp);
        
        END_INTERFACE
    } IProfilePointEventsVtbl;

    interface IProfilePointEvents
    {
        CONST_VTBL struct IProfilePointEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProfilePointEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProfilePointEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProfilePointEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProfilePointEvents_OnProfilePointChanged(This,pp)	\
    ( (This)->lpVtbl -> OnProfilePointChanged(This,pp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProfilePointEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumProfilePoints_INTERFACE_DEFINED__
#define __IEnumProfilePoints_INTERFACE_DEFINED__

/* interface IEnumProfilePoints */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumProfilePoints;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E669818B-B0E6-4fda-9255-49FDAF56114E")
    IEnumProfilePoints : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumProfilePoints **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IProfilePoint **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumProfilePointsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumProfilePoints * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumProfilePoints * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumProfilePoints * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumProfilePoints * This,
            /* [out] */ IEnumProfilePoints **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumProfilePoints * This,
            /* [in] */ ULONG celt,
            /* [out] */ IProfilePoint **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumProfilePoints * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumProfilePoints * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumProfilePointsVtbl;

    interface IEnumProfilePoints
    {
        CONST_VTBL struct IEnumProfilePointsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumProfilePoints_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumProfilePoints_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumProfilePoints_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumProfilePoints_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumProfilePoints_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumProfilePoints_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumProfilePoints_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumProfilePoints_INTERFACE_DEFINED__ */


#ifndef __IProfilePointFactory_INTERFACE_DEFINED__
#define __IProfilePointFactory_INTERFACE_DEFINED__

/* interface IProfilePointFactory */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProfilePointFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FAC877F3-A85A-4490-AC53-5F7BB80A1A6A")
    IProfilePointFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IProfile **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Profile( 
            /* [in] */ IProfile *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateProfilePoint( 
            /* [retval][out] */ IProfilePoint **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProfilePointFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProfilePointFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProfilePointFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProfilePointFactory * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IProfilePointFactory * This,
            /* [retval][out] */ IProfile **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Profile )( 
            IProfilePointFactory * This,
            /* [in] */ IProfile *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateProfilePoint )( 
            IProfilePointFactory * This,
            /* [retval][out] */ IProfilePoint **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IProfilePointFactory * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IProfilePointFactoryVtbl;

    interface IProfilePointFactory
    {
        CONST_VTBL struct IProfilePointFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProfilePointFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProfilePointFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProfilePointFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProfilePointFactory_get_Profile(This,pVal)	\
    ( (This)->lpVtbl -> get_Profile(This,pVal) ) 

#define IProfilePointFactory_putref_Profile(This,newVal)	\
    ( (This)->lpVtbl -> putref_Profile(This,newVal) ) 

#define IProfilePointFactory_CreateProfilePoint(This,pVal)	\
    ( (This)->lpVtbl -> CreateProfilePoint(This,pVal) ) 

#define IProfilePointFactory_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProfilePointFactory_INTERFACE_DEFINED__ */


#ifndef __IProfilePointCollection_INTERFACE_DEFINED__
#define __IProfilePointCollection_INTERFACE_DEFINED__

/* interface IProfilePointCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProfilePointCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11B1FEE8-8CC2-42BC-B9DE-940EE6B16BA1")
    IProfilePointCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IProfilePoint **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 elevation,
            /* [retval][out] */ IProfilePoint **pp) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FindID( 
            /* [in] */ IProfilePoint *pp,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumIDs( 
            /* [retval][out] */ IEnumIDs **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ID( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Factory( 
            /* [retval][out] */ IProfilePointFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Factory( 
            /* [in] */ IProfilePointFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumProfilePoints( 
            /* [retval][out] */ IEnumProfilePoints **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IProfilePointCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProfilePointCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProfilePointCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProfilePointCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProfilePointCollection * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IProfilePointCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IProfilePointCollection * This,
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IProfilePoint **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IProfilePointCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IProfilePointCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IProfilePointCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 elevation,
            /* [retval][out] */ IProfilePoint **pp);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            IProfilePointCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IProfilePointCollection * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IProfilePointCollection * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindID )( 
            IProfilePointCollection * This,
            /* [in] */ IProfilePoint *pp,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumIDs )( 
            IProfilePointCollection * This,
            /* [retval][out] */ IEnumIDs **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ID )( 
            IProfilePointCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Factory )( 
            IProfilePointCollection * This,
            /* [retval][out] */ IProfilePointFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Factory )( 
            IProfilePointCollection * This,
            /* [in] */ IProfilePointFactory *factory);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumProfilePoints )( 
            IProfilePointCollection * This,
            /* [retval][out] */ IEnumProfilePoints **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IProfilePointCollection * This,
            /* [retval][out] */ IProfilePointCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IProfilePointCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IProfilePointCollectionVtbl;

    interface IProfilePointCollection
    {
        CONST_VTBL struct IProfilePointCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProfilePointCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProfilePointCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProfilePointCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProfilePointCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IProfilePointCollection_get_Item(This,id,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,id,pVal) ) 

#define IProfilePointCollection_putref_Item(This,id,newVal)	\
    ( (This)->lpVtbl -> putref_Item(This,id,newVal) ) 

#define IProfilePointCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IProfilePointCollection_Add(This,id,varStation,elevation,pp)	\
    ( (This)->lpVtbl -> Add(This,id,varStation,elevation,pp) ) 

#define IProfilePointCollection_AddEx(This,id,newVal)	\
    ( (This)->lpVtbl -> AddEx(This,id,newVal) ) 

#define IProfilePointCollection_Remove(This,id)	\
    ( (This)->lpVtbl -> Remove(This,id) ) 

#define IProfilePointCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IProfilePointCollection_FindID(This,pp,ID)	\
    ( (This)->lpVtbl -> FindID(This,pp,ID) ) 

#define IProfilePointCollection_get__EnumIDs(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumIDs(This,ppenum) ) 

#define IProfilePointCollection_ID(This,index,ID)	\
    ( (This)->lpVtbl -> ID(This,index,ID) ) 

#define IProfilePointCollection_get_Factory(This,factory)	\
    ( (This)->lpVtbl -> get_Factory(This,factory) ) 

#define IProfilePointCollection_putref_Factory(This,factory)	\
    ( (This)->lpVtbl -> putref_Factory(This,factory) ) 

#define IProfilePointCollection_get__EnumProfilePoints(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumProfilePoints(This,ppenum) ) 

#define IProfilePointCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IProfilePointCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProfilePointCollection_INTERFACE_DEFINED__ */


#ifndef __IProfilePointCollectionEvents_INTERFACE_DEFINED__
#define __IProfilePointCollectionEvents_INTERFACE_DEFINED__

/* interface IProfilePointCollectionEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProfilePointCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D871C5DE-78F4-487a-9EDD-6F465BF74043")
    IProfilePointCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfilePointChanged( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *pp) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfilePointAdded( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *pp) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfilePointRemoved( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfilePointsCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProfilePointCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProfilePointCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProfilePointCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProfilePointCollectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfilePointChanged )( 
            IProfilePointCollectionEvents * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *pp);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfilePointAdded )( 
            IProfilePointCollectionEvents * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *pp);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfilePointRemoved )( 
            IProfilePointCollectionEvents * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfilePointsCleared )( 
            IProfilePointCollectionEvents * This);
        
        END_INTERFACE
    } IProfilePointCollectionEventsVtbl;

    interface IProfilePointCollectionEvents
    {
        CONST_VTBL struct IProfilePointCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProfilePointCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProfilePointCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProfilePointCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProfilePointCollectionEvents_OnProfilePointChanged(This,id,pp)	\
    ( (This)->lpVtbl -> OnProfilePointChanged(This,id,pp) ) 

#define IProfilePointCollectionEvents_OnProfilePointAdded(This,id,pp)	\
    ( (This)->lpVtbl -> OnProfilePointAdded(This,id,pp) ) 

#define IProfilePointCollectionEvents_OnProfilePointRemoved(This,id)	\
    ( (This)->lpVtbl -> OnProfilePointRemoved(This,id) ) 

#define IProfilePointCollectionEvents_OnProfilePointsCleared(This)	\
    ( (This)->lpVtbl -> OnProfilePointsCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProfilePointCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __IVertCurve_INTERFACE_DEFINED__
#define __IVertCurve_INTERFACE_DEFINED__

/* interface IVertCurve */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVertCurve;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E003ECBB-BE61-4CB1-AB4B-819D98B3C45C")
    IVertCurve : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ComputeFromGradePoints( 
            /* [retval][out] */ VARIANT_BOOL *pvbCompute) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ComputeFromGradePoints( 
            /* [in] */ VARIANT_BOOL vbCompute) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IProfile **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Profile( 
            /* [in] */ IProfile *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PBG( 
            /* [retval][out] */ IProfilePoint **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PBG( 
            /* [in] */ IProfilePoint *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PVI( 
            /* [retval][out] */ IProfilePoint **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PVI( 
            /* [in] */ IProfilePoint *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PFG( 
            /* [retval][out] */ IProfilePoint **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PFG( 
            /* [in] */ IProfilePoint *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_L1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_L1( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_L2( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_L2( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BVC( 
            /* [retval][out] */ IProfilePoint **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EVC( 
            /* [retval][out] */ IProfilePoint **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EntryGrade( 
            /* [in] */ Float64 pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EntryGrade( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ExitGrade( 
            /* [in] */ Float64 pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExitGrade( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LowPoint( 
            /* [retval][out] */ IProfilePoint **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HighPoint( 
            /* [retval][out] */ IProfilePoint **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Elevation( 
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ Float64 *elev) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Grade( 
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ Float64 *grade) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProfilePointFactory( 
            /* [retval][out] */ IProfilePointFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_ProfilePointFactory( 
            /* [in] */ IProfilePointFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IVertCurve **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_A( 
            /* [retval][out] */ Float64 *a) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_K( 
            /* [retval][out] */ Float64 *k) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_H( 
            /* [retval][out] */ Float64 *h) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_E( 
            /* [in] */ Float64 t,
            /* [retval][out] */ Float64 *e) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVertCurveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVertCurve * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVertCurve * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVertCurve * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ComputeFromGradePoints )( 
            IVertCurve * This,
            /* [retval][out] */ VARIANT_BOOL *pvbCompute);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ComputeFromGradePoints )( 
            IVertCurve * This,
            /* [in] */ VARIANT_BOOL vbCompute);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IVertCurve * This,
            /* [retval][out] */ IProfile **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Profile )( 
            IVertCurve * This,
            /* [in] */ IProfile *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PBG )( 
            IVertCurve * This,
            /* [retval][out] */ IProfilePoint **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PBG )( 
            IVertCurve * This,
            /* [in] */ IProfilePoint *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PVI )( 
            IVertCurve * This,
            /* [retval][out] */ IProfilePoint **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PVI )( 
            IVertCurve * This,
            /* [in] */ IProfilePoint *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PFG )( 
            IVertCurve * This,
            /* [retval][out] */ IProfilePoint **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PFG )( 
            IVertCurve * This,
            /* [in] */ IProfilePoint *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_L1 )( 
            IVertCurve * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_L1 )( 
            IVertCurve * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_L2 )( 
            IVertCurve * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_L2 )( 
            IVertCurve * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BVC )( 
            IVertCurve * This,
            /* [retval][out] */ IProfilePoint **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EVC )( 
            IVertCurve * This,
            /* [retval][out] */ IProfilePoint **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IVertCurve * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EntryGrade )( 
            IVertCurve * This,
            /* [in] */ Float64 pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EntryGrade )( 
            IVertCurve * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExitGrade )( 
            IVertCurve * This,
            /* [in] */ Float64 pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExitGrade )( 
            IVertCurve * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LowPoint )( 
            IVertCurve * This,
            /* [retval][out] */ IProfilePoint **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HighPoint )( 
            IVertCurve * This,
            /* [retval][out] */ IProfilePoint **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Elevation )( 
            IVertCurve * This,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ Float64 *elev);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Grade )( 
            IVertCurve * This,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ Float64 *grade);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfilePointFactory )( 
            IVertCurve * This,
            /* [retval][out] */ IProfilePointFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ProfilePointFactory )( 
            IVertCurve * This,
            /* [in] */ IProfilePointFactory *factory);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IVertCurve * This,
            /* [retval][out] */ IVertCurve **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_A )( 
            IVertCurve * This,
            /* [retval][out] */ Float64 *a);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_K )( 
            IVertCurve * This,
            /* [retval][out] */ Float64 *k);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_H )( 
            IVertCurve * This,
            /* [retval][out] */ Float64 *h);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_E )( 
            IVertCurve * This,
            /* [in] */ Float64 t,
            /* [retval][out] */ Float64 *e);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IVertCurve * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IVertCurveVtbl;

    interface IVertCurve
    {
        CONST_VTBL struct IVertCurveVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVertCurve_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVertCurve_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVertCurve_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVertCurve_get_ComputeFromGradePoints(This,pvbCompute)	\
    ( (This)->lpVtbl -> get_ComputeFromGradePoints(This,pvbCompute) ) 

#define IVertCurve_put_ComputeFromGradePoints(This,vbCompute)	\
    ( (This)->lpVtbl -> put_ComputeFromGradePoints(This,vbCompute) ) 

#define IVertCurve_get_Profile(This,pVal)	\
    ( (This)->lpVtbl -> get_Profile(This,pVal) ) 

#define IVertCurve_putref_Profile(This,newVal)	\
    ( (This)->lpVtbl -> putref_Profile(This,newVal) ) 

#define IVertCurve_get_PBG(This,pVal)	\
    ( (This)->lpVtbl -> get_PBG(This,pVal) ) 

#define IVertCurve_putref_PBG(This,newVal)	\
    ( (This)->lpVtbl -> putref_PBG(This,newVal) ) 

#define IVertCurve_get_PVI(This,pVal)	\
    ( (This)->lpVtbl -> get_PVI(This,pVal) ) 

#define IVertCurve_putref_PVI(This,newVal)	\
    ( (This)->lpVtbl -> putref_PVI(This,newVal) ) 

#define IVertCurve_get_PFG(This,pVal)	\
    ( (This)->lpVtbl -> get_PFG(This,pVal) ) 

#define IVertCurve_putref_PFG(This,newVal)	\
    ( (This)->lpVtbl -> putref_PFG(This,newVal) ) 

#define IVertCurve_get_L1(This,pVal)	\
    ( (This)->lpVtbl -> get_L1(This,pVal) ) 

#define IVertCurve_put_L1(This,newVal)	\
    ( (This)->lpVtbl -> put_L1(This,newVal) ) 

#define IVertCurve_get_L2(This,pVal)	\
    ( (This)->lpVtbl -> get_L2(This,pVal) ) 

#define IVertCurve_put_L2(This,newVal)	\
    ( (This)->lpVtbl -> put_L2(This,newVal) ) 

#define IVertCurve_get_BVC(This,pVal)	\
    ( (This)->lpVtbl -> get_BVC(This,pVal) ) 

#define IVertCurve_get_EVC(This,pVal)	\
    ( (This)->lpVtbl -> get_EVC(This,pVal) ) 

#define IVertCurve_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define IVertCurve_put_EntryGrade(This,pVal)	\
    ( (This)->lpVtbl -> put_EntryGrade(This,pVal) ) 

#define IVertCurve_get_EntryGrade(This,pVal)	\
    ( (This)->lpVtbl -> get_EntryGrade(This,pVal) ) 

#define IVertCurve_put_ExitGrade(This,pVal)	\
    ( (This)->lpVtbl -> put_ExitGrade(This,pVal) ) 

#define IVertCurve_get_ExitGrade(This,pVal)	\
    ( (This)->lpVtbl -> get_ExitGrade(This,pVal) ) 

#define IVertCurve_get_LowPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_LowPoint(This,pVal) ) 

#define IVertCurve_get_HighPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_HighPoint(This,pVal) ) 

#define IVertCurve_Elevation(This,varStation,elev)	\
    ( (This)->lpVtbl -> Elevation(This,varStation,elev) ) 

#define IVertCurve_Grade(This,varStation,grade)	\
    ( (This)->lpVtbl -> Grade(This,varStation,grade) ) 

#define IVertCurve_get_ProfilePointFactory(This,factory)	\
    ( (This)->lpVtbl -> get_ProfilePointFactory(This,factory) ) 

#define IVertCurve_putref_ProfilePointFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_ProfilePointFactory(This,factory) ) 

#define IVertCurve_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IVertCurve_get_A(This,a)	\
    ( (This)->lpVtbl -> get_A(This,a) ) 

#define IVertCurve_get_K(This,k)	\
    ( (This)->lpVtbl -> get_K(This,k) ) 

#define IVertCurve_get_H(This,h)	\
    ( (This)->lpVtbl -> get_H(This,h) ) 

#define IVertCurve_get_E(This,t,e)	\
    ( (This)->lpVtbl -> get_E(This,t,e) ) 

#define IVertCurve_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVertCurve_INTERFACE_DEFINED__ */


#ifndef __IVertCurveEvents_INTERFACE_DEFINED__
#define __IVertCurveEvents_INTERFACE_DEFINED__

/* interface IVertCurveEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVertCurveEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AD7A94E4-D030-42a0-8E6F-9CFEC582904C")
    IVertCurveEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVertCurveChanged( 
            /* [in] */ IVertCurve *vc) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVertCurveEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVertCurveEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVertCurveEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVertCurveEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVertCurveChanged )( 
            IVertCurveEvents * This,
            /* [in] */ IVertCurve *vc);
        
        END_INTERFACE
    } IVertCurveEventsVtbl;

    interface IVertCurveEvents
    {
        CONST_VTBL struct IVertCurveEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVertCurveEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVertCurveEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVertCurveEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVertCurveEvents_OnVertCurveChanged(This,vc)	\
    ( (This)->lpVtbl -> OnVertCurveChanged(This,vc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVertCurveEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumVertCurves_INTERFACE_DEFINED__
#define __IEnumVertCurves_INTERFACE_DEFINED__

/* interface IEnumVertCurves */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumVertCurves;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("57A68B13-5FEA-4b47-8211-6E58B0FF7B4E")
    IEnumVertCurves : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            ULONG celt,
            IVertCurve **rgelt,
            ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            IEnumVertCurves **ppenum) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumVertCurvesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumVertCurves * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumVertCurves * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumVertCurves * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumVertCurves * This,
            ULONG celt,
            IVertCurve **rgelt,
            ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumVertCurves * This,
            ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumVertCurves * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumVertCurves * This,
            IEnumVertCurves **ppenum);
        
        END_INTERFACE
    } IEnumVertCurvesVtbl;

    interface IEnumVertCurves
    {
        CONST_VTBL struct IEnumVertCurvesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumVertCurves_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumVertCurves_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumVertCurves_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumVertCurves_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumVertCurves_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumVertCurves_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumVertCurves_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumVertCurves_INTERFACE_DEFINED__ */


#ifndef __IVertCurveFactory_INTERFACE_DEFINED__
#define __IVertCurveFactory_INTERFACE_DEFINED__

/* interface IVertCurveFactory */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVertCurveFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3B173FA0-A475-4120-9FEB-2C1CE5FE2013")
    IVertCurveFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateVertCurve( 
            /* [retval][out] */ IVertCurve **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVertCurveFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVertCurveFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVertCurveFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVertCurveFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateVertCurve )( 
            IVertCurveFactory * This,
            /* [retval][out] */ IVertCurve **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IVertCurveFactory * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IVertCurveFactoryVtbl;

    interface IVertCurveFactory
    {
        CONST_VTBL struct IVertCurveFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVertCurveFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVertCurveFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVertCurveFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVertCurveFactory_CreateVertCurve(This,pVal)	\
    ( (This)->lpVtbl -> CreateVertCurve(This,pVal) ) 

#define IVertCurveFactory_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVertCurveFactory_INTERFACE_DEFINED__ */


#ifndef __IVertCurveCollection_INTERFACE_DEFINED__
#define __IVertCurveCollection_INTERFACE_DEFINED__

/* interface IVertCurveCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVertCurveCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6B519EB-8B34-4F34-842C-FA1912132199")
    IVertCurveCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IVertCurve **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *pbg,
            /* [in] */ IProfilePoint *pvi,
            /* [in] */ IProfilePoint *pfg,
            /* [in] */ Float64 l1,
            /* [in] */ Float64 l2,
            /* [retval][out] */ IVertCurve **vc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FindID( 
            /* [in] */ IVertCurve *vc,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumIDs( 
            /* [retval][out] */ IEnumIDs **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumVertCurves( 
            /* [retval][out] */ IEnumVertCurves **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ID( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Factory( 
            /* [in] */ IVertCurveFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Factory( 
            /* [retval][out] */ IVertCurveFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IVertCurveCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVertCurveCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVertCurveCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVertCurveCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVertCurveCollection * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IVertCurveCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IVertCurveCollection * This,
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IVertCurve **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IVertCurveCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IVertCurveCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IVertCurveCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *pbg,
            /* [in] */ IProfilePoint *pvi,
            /* [in] */ IProfilePoint *pfg,
            /* [in] */ Float64 l1,
            /* [in] */ Float64 l2,
            /* [retval][out] */ IVertCurve **vc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            IVertCurveCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IVertCurveCollection * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IVertCurveCollection * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindID )( 
            IVertCurveCollection * This,
            /* [in] */ IVertCurve *vc,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumIDs )( 
            IVertCurveCollection * This,
            /* [retval][out] */ IEnumIDs **ppenum);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumVertCurves )( 
            IVertCurveCollection * This,
            /* [retval][out] */ IEnumVertCurves **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ID )( 
            IVertCurveCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Factory )( 
            IVertCurveCollection * This,
            /* [in] */ IVertCurveFactory *factory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Factory )( 
            IVertCurveCollection * This,
            /* [retval][out] */ IVertCurveFactory **factory);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IVertCurveCollection * This,
            /* [retval][out] */ IVertCurveCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IVertCurveCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IVertCurveCollectionVtbl;

    interface IVertCurveCollection
    {
        CONST_VTBL struct IVertCurveCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVertCurveCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVertCurveCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVertCurveCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVertCurveCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IVertCurveCollection_get_Item(This,id,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,id,pVal) ) 

#define IVertCurveCollection_putref_Item(This,id,newVal)	\
    ( (This)->lpVtbl -> putref_Item(This,id,newVal) ) 

#define IVertCurveCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IVertCurveCollection_Add(This,id,pbg,pvi,pfg,l1,l2,vc)	\
    ( (This)->lpVtbl -> Add(This,id,pbg,pvi,pfg,l1,l2,vc) ) 

#define IVertCurveCollection_AddEx(This,id,newVal)	\
    ( (This)->lpVtbl -> AddEx(This,id,newVal) ) 

#define IVertCurveCollection_Remove(This,id)	\
    ( (This)->lpVtbl -> Remove(This,id) ) 

#define IVertCurveCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IVertCurveCollection_FindID(This,vc,ID)	\
    ( (This)->lpVtbl -> FindID(This,vc,ID) ) 

#define IVertCurveCollection_get__EnumIDs(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumIDs(This,ppenum) ) 

#define IVertCurveCollection_get__EnumVertCurves(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumVertCurves(This,ppenum) ) 

#define IVertCurveCollection_ID(This,index,ID)	\
    ( (This)->lpVtbl -> ID(This,index,ID) ) 

#define IVertCurveCollection_putref_Factory(This,factory)	\
    ( (This)->lpVtbl -> putref_Factory(This,factory) ) 

#define IVertCurveCollection_get_Factory(This,factory)	\
    ( (This)->lpVtbl -> get_Factory(This,factory) ) 

#define IVertCurveCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IVertCurveCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVertCurveCollection_INTERFACE_DEFINED__ */


#ifndef __IVertCurveCollectionEvents_INTERFACE_DEFINED__
#define __IVertCurveCollectionEvents_INTERFACE_DEFINED__

/* interface IVertCurveCollectionEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVertCurveCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EBD26472-9710-4c00-B1D4-88F5AE075B8D")
    IVertCurveCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVertCurveChanged( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *vc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVertCurveAdded( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *vc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVertCurveRemoved( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVertCurvesCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVertCurveCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVertCurveCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVertCurveCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVertCurveCollectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVertCurveChanged )( 
            IVertCurveCollectionEvents * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *vc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVertCurveAdded )( 
            IVertCurveCollectionEvents * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *vc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVertCurveRemoved )( 
            IVertCurveCollectionEvents * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVertCurvesCleared )( 
            IVertCurveCollectionEvents * This);
        
        END_INTERFACE
    } IVertCurveCollectionEventsVtbl;

    interface IVertCurveCollectionEvents
    {
        CONST_VTBL struct IVertCurveCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVertCurveCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVertCurveCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVertCurveCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVertCurveCollectionEvents_OnVertCurveChanged(This,id,vc)	\
    ( (This)->lpVtbl -> OnVertCurveChanged(This,id,vc) ) 

#define IVertCurveCollectionEvents_OnVertCurveAdded(This,id,vc)	\
    ( (This)->lpVtbl -> OnVertCurveAdded(This,id,vc) ) 

#define IVertCurveCollectionEvents_OnVertCurveRemoved(This,id)	\
    ( (This)->lpVtbl -> OnVertCurveRemoved(This,id) ) 

#define IVertCurveCollectionEvents_OnVertCurvesCleared(This)	\
    ( (This)->lpVtbl -> OnVertCurvesCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVertCurveCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumHorzCurves_INTERFACE_DEFINED__
#define __IEnumHorzCurves_INTERFACE_DEFINED__

/* interface IEnumHorzCurves */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumHorzCurves;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2317EF09-E0F5-49fe-B6BC-14A21A59EBAC")
    IEnumHorzCurves : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumHorzCurves **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IHorzCurve **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumHorzCurvesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumHorzCurves * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumHorzCurves * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumHorzCurves * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumHorzCurves * This,
            /* [out] */ IEnumHorzCurves **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumHorzCurves * This,
            /* [in] */ ULONG celt,
            /* [out] */ IHorzCurve **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumHorzCurves * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumHorzCurves * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumHorzCurvesVtbl;

    interface IEnumHorzCurves
    {
        CONST_VTBL struct IEnumHorzCurvesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumHorzCurves_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumHorzCurves_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumHorzCurves_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumHorzCurves_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumHorzCurves_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumHorzCurves_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumHorzCurves_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumHorzCurves_INTERFACE_DEFINED__ */


#ifndef __IHorzCurveFactory_INTERFACE_DEFINED__
#define __IHorzCurveFactory_INTERFACE_DEFINED__

/* interface IHorzCurveFactory */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IHorzCurveFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6C9AFFCA-DC58-4EA5-8FE6-A249CFED06BA")
    IHorzCurveFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateHorzCurve( 
            /* [retval][out] */ IHorzCurve **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IHorzCurveFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHorzCurveFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHorzCurveFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHorzCurveFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateHorzCurve )( 
            IHorzCurveFactory * This,
            /* [retval][out] */ IHorzCurve **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IHorzCurveFactory * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IHorzCurveFactoryVtbl;

    interface IHorzCurveFactory
    {
        CONST_VTBL struct IHorzCurveFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHorzCurveFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHorzCurveFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHorzCurveFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHorzCurveFactory_CreateHorzCurve(This,pVal)	\
    ( (This)->lpVtbl -> CreateHorzCurve(This,pVal) ) 

#define IHorzCurveFactory_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHorzCurveFactory_INTERFACE_DEFINED__ */


#ifndef __IHorzCurveCollection_INTERFACE_DEFINED__
#define __IHorzCurveCollection_INTERFACE_DEFINED__

/* interface IHorzCurveCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IHorzCurveCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2436697B-4DE1-40A1-B087-89AA074F1C2C")
    IHorzCurveCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IHorzCurve **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *pbt,
            /* [in] */ IPoint2d *pi,
            /* [in] */ IPoint2d *pft,
            /* [in] */ Float64 radius,
            /* [in] */ Float64 Ls1,
            /* [in] */ Float64 Ls2,
            /* [retval][out] */ IHorzCurve **hc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FindID( 
            /* [in] */ IHorzCurve *hc,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumIDs( 
            /* [retval][out] */ IEnumIDs **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Factory( 
            /* [retval][out] */ IHorzCurveFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Factory( 
            /* [in] */ IHorzCurveFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ID( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumHorzCurves( 
            /* [retval][out] */ IEnumHorzCurves **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IHorzCurveCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IHorzCurveCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHorzCurveCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHorzCurveCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHorzCurveCollection * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IHorzCurveCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IHorzCurveCollection * This,
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IHorzCurve **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IHorzCurveCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IHorzCurveCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IHorzCurveCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *pbt,
            /* [in] */ IPoint2d *pi,
            /* [in] */ IPoint2d *pft,
            /* [in] */ Float64 radius,
            /* [in] */ Float64 Ls1,
            /* [in] */ Float64 Ls2,
            /* [retval][out] */ IHorzCurve **hc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            IHorzCurveCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IHorzCurveCollection * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IHorzCurveCollection * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindID )( 
            IHorzCurveCollection * This,
            /* [in] */ IHorzCurve *hc,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumIDs )( 
            IHorzCurveCollection * This,
            /* [retval][out] */ IEnumIDs **ppenum);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Factory )( 
            IHorzCurveCollection * This,
            /* [retval][out] */ IHorzCurveFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Factory )( 
            IHorzCurveCollection * This,
            /* [in] */ IHorzCurveFactory *factory);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ID )( 
            IHorzCurveCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumHorzCurves )( 
            IHorzCurveCollection * This,
            /* [retval][out] */ IEnumHorzCurves **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IHorzCurveCollection * This,
            /* [retval][out] */ IHorzCurveCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IHorzCurveCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IHorzCurveCollectionVtbl;

    interface IHorzCurveCollection
    {
        CONST_VTBL struct IHorzCurveCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHorzCurveCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHorzCurveCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHorzCurveCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHorzCurveCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IHorzCurveCollection_get_Item(This,id,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,id,pVal) ) 

#define IHorzCurveCollection_putref_Item(This,id,newVal)	\
    ( (This)->lpVtbl -> putref_Item(This,id,newVal) ) 

#define IHorzCurveCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IHorzCurveCollection_Add(This,id,pbt,pi,pft,radius,Ls1,Ls2,hc)	\
    ( (This)->lpVtbl -> Add(This,id,pbt,pi,pft,radius,Ls1,Ls2,hc) ) 

#define IHorzCurveCollection_AddEx(This,id,newVal)	\
    ( (This)->lpVtbl -> AddEx(This,id,newVal) ) 

#define IHorzCurveCollection_Remove(This,id)	\
    ( (This)->lpVtbl -> Remove(This,id) ) 

#define IHorzCurveCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IHorzCurveCollection_FindID(This,hc,ID)	\
    ( (This)->lpVtbl -> FindID(This,hc,ID) ) 

#define IHorzCurveCollection_get__EnumIDs(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumIDs(This,ppenum) ) 

#define IHorzCurveCollection_get_Factory(This,factory)	\
    ( (This)->lpVtbl -> get_Factory(This,factory) ) 

#define IHorzCurveCollection_putref_Factory(This,factory)	\
    ( (This)->lpVtbl -> putref_Factory(This,factory) ) 

#define IHorzCurveCollection_ID(This,index,ID)	\
    ( (This)->lpVtbl -> ID(This,index,ID) ) 

#define IHorzCurveCollection_get__EnumHorzCurves(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumHorzCurves(This,ppenum) ) 

#define IHorzCurveCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IHorzCurveCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHorzCurveCollection_INTERFACE_DEFINED__ */


#ifndef __IHorzCurveCollectionEvents_INTERFACE_DEFINED__
#define __IHorzCurveCollectionEvents_INTERFACE_DEFINED__

/* interface IHorzCurveCollectionEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IHorzCurveCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7322B2AD-A63B-4348-854C-ED1130B7EB49")
    IHorzCurveCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnHorzCurveChanged( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *vc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnHorzCurveAdded( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *vc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnHorzCurveRemoved( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnHorzCurvesCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IHorzCurveCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHorzCurveCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHorzCurveCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHorzCurveCollectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnHorzCurveChanged )( 
            IHorzCurveCollectionEvents * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *vc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnHorzCurveAdded )( 
            IHorzCurveCollectionEvents * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *vc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnHorzCurveRemoved )( 
            IHorzCurveCollectionEvents * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnHorzCurvesCleared )( 
            IHorzCurveCollectionEvents * This);
        
        END_INTERFACE
    } IHorzCurveCollectionEventsVtbl;

    interface IHorzCurveCollectionEvents
    {
        CONST_VTBL struct IHorzCurveCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHorzCurveCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHorzCurveCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHorzCurveCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHorzCurveCollectionEvents_OnHorzCurveChanged(This,id,vc)	\
    ( (This)->lpVtbl -> OnHorzCurveChanged(This,id,vc) ) 

#define IHorzCurveCollectionEvents_OnHorzCurveAdded(This,id,vc)	\
    ( (This)->lpVtbl -> OnHorzCurveAdded(This,id,vc) ) 

#define IHorzCurveCollectionEvents_OnHorzCurveRemoved(This,id)	\
    ( (This)->lpVtbl -> OnHorzCurveRemoved(This,id) ) 

#define IHorzCurveCollectionEvents_OnHorzCurvesCleared(This)	\
    ( (This)->lpVtbl -> OnHorzCurvesCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHorzCurveCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __ICubicSpline_INTERFACE_DEFINED__
#define __ICubicSpline_INTERFACE_DEFINED__

/* interface ICubicSpline */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICubicSpline;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EA2DD8A2-5B17-4b36-AE3D-38CB7CB059E5")
    ICubicSpline : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPoints( 
            /* [in] */ IPoint2dCollection *points) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPoint( 
            /* [in] */ Float64 x,
            /* [in] */ Float64 y) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPointEx( 
            /* [in] */ IPoint2d *point) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PointCount( 
            /* [retval][out] */ CollectionIndexType *nPoints) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Point( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Points( 
            /* [retval][out] */ IPoint2dCollection **ppPoints) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartPoint( 
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPoint( 
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartDirection( 
            /* [in] */ VARIANT varDirection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartDirection( 
            /* [retval][out] */ IDirection **dir) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndDirection( 
            /* [in] */ VARIANT varDirection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndDirection( 
            /* [retval][out] */ IDirection **dir) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Bearing( 
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BearingAtPoint( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IDirection **pDir) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Normal( 
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NormalAtPoint( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IDirection **pDir) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PointOnSpline( 
            /* [in] */ Float64 distance,
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ProjectPoint( 
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ IPoint2d **pNewPoint) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DistanceFromStart( 
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ Float64 *dist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DistanceFromStartAtPoint( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ Float64 *dist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Intersect( 
            /* [in] */ ILine2d *line,
            /* [in] */ VARIANT_BOOL bProjectBack,
            /* [in] */ VARIANT_BOOL bProjectAhead,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PointFactory( 
            /* [retval][out] */ IPoint2dFactory **factory) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PointFactory( 
            /* [in] */ IPoint2dFactory *factory) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ICubicSpline **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICubicSplineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICubicSpline * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICubicSpline * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICubicSpline * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPoints )( 
            ICubicSpline * This,
            /* [in] */ IPoint2dCollection *points);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPoint )( 
            ICubicSpline * This,
            /* [in] */ Float64 x,
            /* [in] */ Float64 y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPointEx )( 
            ICubicSpline * This,
            /* [in] */ IPoint2d *point);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointCount )( 
            ICubicSpline * This,
            /* [retval][out] */ CollectionIndexType *nPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Point )( 
            ICubicSpline * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Points )( 
            ICubicSpline * This,
            /* [retval][out] */ IPoint2dCollection **ppPoints);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartPoint )( 
            ICubicSpline * This,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndPoint )( 
            ICubicSpline * This,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ICubicSpline * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartDirection )( 
            ICubicSpline * This,
            /* [in] */ VARIANT varDirection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartDirection )( 
            ICubicSpline * This,
            /* [retval][out] */ IDirection **dir);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndDirection )( 
            ICubicSpline * This,
            /* [in] */ VARIANT varDirection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndDirection )( 
            ICubicSpline * This,
            /* [retval][out] */ IDirection **dir);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Bearing )( 
            ICubicSpline * This,
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BearingAtPoint )( 
            ICubicSpline * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IDirection **pDir);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Normal )( 
            ICubicSpline * This,
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NormalAtPoint )( 
            ICubicSpline * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IDirection **pDir);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnSpline )( 
            ICubicSpline * This,
            /* [in] */ Float64 distance,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectPoint )( 
            ICubicSpline * This,
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ IPoint2d **pNewPoint);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DistanceFromStart )( 
            ICubicSpline * This,
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ Float64 *dist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DistanceFromStartAtPoint )( 
            ICubicSpline * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ Float64 *dist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Intersect )( 
            ICubicSpline * This,
            /* [in] */ ILine2d *line,
            /* [in] */ VARIANT_BOOL bProjectBack,
            /* [in] */ VARIANT_BOOL bProjectAhead,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ICubicSpline * This,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointFactory )( 
            ICubicSpline * This,
            /* [retval][out] */ IPoint2dFactory **factory);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PointFactory )( 
            ICubicSpline * This,
            /* [in] */ IPoint2dFactory *factory);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ICubicSpline * This,
            /* [retval][out] */ ICubicSpline **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICubicSpline * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ICubicSplineVtbl;

    interface ICubicSpline
    {
        CONST_VTBL struct ICubicSplineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICubicSpline_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICubicSpline_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICubicSpline_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICubicSpline_AddPoints(This,points)	\
    ( (This)->lpVtbl -> AddPoints(This,points) ) 

#define ICubicSpline_AddPoint(This,x,y)	\
    ( (This)->lpVtbl -> AddPoint(This,x,y) ) 

#define ICubicSpline_AddPointEx(This,point)	\
    ( (This)->lpVtbl -> AddPointEx(This,point) ) 

#define ICubicSpline_get_PointCount(This,nPoints)	\
    ( (This)->lpVtbl -> get_PointCount(This,nPoints) ) 

#define ICubicSpline_get_Point(This,idx,point)	\
    ( (This)->lpVtbl -> get_Point(This,idx,point) ) 

#define ICubicSpline_get_Points(This,ppPoints)	\
    ( (This)->lpVtbl -> get_Points(This,ppPoints) ) 

#define ICubicSpline_get_StartPoint(This,point)	\
    ( (This)->lpVtbl -> get_StartPoint(This,point) ) 

#define ICubicSpline_get_EndPoint(This,point)	\
    ( (This)->lpVtbl -> get_EndPoint(This,point) ) 

#define ICubicSpline_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ICubicSpline_put_StartDirection(This,varDirection)	\
    ( (This)->lpVtbl -> put_StartDirection(This,varDirection) ) 

#define ICubicSpline_get_StartDirection(This,dir)	\
    ( (This)->lpVtbl -> get_StartDirection(This,dir) ) 

#define ICubicSpline_put_EndDirection(This,varDirection)	\
    ( (This)->lpVtbl -> put_EndDirection(This,varDirection) ) 

#define ICubicSpline_get_EndDirection(This,dir)	\
    ( (This)->lpVtbl -> get_EndDirection(This,dir) ) 

#define ICubicSpline_Bearing(This,distance,pVal)	\
    ( (This)->lpVtbl -> Bearing(This,distance,pVal) ) 

#define ICubicSpline_BearingAtPoint(This,idx,pDir)	\
    ( (This)->lpVtbl -> BearingAtPoint(This,idx,pDir) ) 

#define ICubicSpline_Normal(This,distance,pVal)	\
    ( (This)->lpVtbl -> Normal(This,distance,pVal) ) 

#define ICubicSpline_NormalAtPoint(This,idx,pDir)	\
    ( (This)->lpVtbl -> NormalAtPoint(This,idx,pDir) ) 

#define ICubicSpline_PointOnSpline(This,distance,pVal)	\
    ( (This)->lpVtbl -> PointOnSpline(This,distance,pVal) ) 

#define ICubicSpline_ProjectPoint(This,point,pNewPoint)	\
    ( (This)->lpVtbl -> ProjectPoint(This,point,pNewPoint) ) 

#define ICubicSpline_DistanceFromStart(This,point,dist)	\
    ( (This)->lpVtbl -> DistanceFromStart(This,point,dist) ) 

#define ICubicSpline_DistanceFromStartAtPoint(This,idx,dist)	\
    ( (This)->lpVtbl -> DistanceFromStartAtPoint(This,idx,dist) ) 

#define ICubicSpline_Intersect(This,line,bProjectBack,bProjectAhead,points)	\
    ( (This)->lpVtbl -> Intersect(This,line,bProjectBack,bProjectAhead,points) ) 

#define ICubicSpline_get_Length(This,pLength)	\
    ( (This)->lpVtbl -> get_Length(This,pLength) ) 

#define ICubicSpline_get_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> get_PointFactory(This,factory) ) 

#define ICubicSpline_putref_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_PointFactory(This,factory) ) 

#define ICubicSpline_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ICubicSpline_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICubicSpline_INTERFACE_DEFINED__ */


#ifndef __ICubicSplineEvents_INTERFACE_DEFINED__
#define __ICubicSplineEvents_INTERFACE_DEFINED__

/* interface ICubicSplineEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICubicSplineEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7A853591-F2A0-4b22-AB22-4ECE47D28F7A")
    ICubicSplineEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSplineChanged( 
            /* [in] */ ICubicSpline *spline) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICubicSplineEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICubicSplineEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICubicSplineEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICubicSplineEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSplineChanged )( 
            ICubicSplineEvents * This,
            /* [in] */ ICubicSpline *spline);
        
        END_INTERFACE
    } ICubicSplineEventsVtbl;

    interface ICubicSplineEvents
    {
        CONST_VTBL struct ICubicSplineEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICubicSplineEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICubicSplineEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICubicSplineEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICubicSplineEvents_OnSplineChanged(This,spline)	\
    ( (This)->lpVtbl -> OnSplineChanged(This,spline) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICubicSplineEvents_INTERFACE_DEFINED__ */


#ifndef __IWidening_INTERFACE_DEFINED__
#define __IWidening_INTERFACE_DEFINED__

/* interface IWidening */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IWidening;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5FA0BC50-322E-4b8c-84AB-5315122966AE")
    IWidening : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ ISurface *pSurface,
            /* [in] */ VARIANT varBeginStation,
            /* [in] */ VARIANT varBeginFullStation,
            /* [in] */ VARIANT varEndFullStation,
            /* [in] */ VARIANT varEndStation,
            /* [in] */ Float64 widening,
            /* [in] */ IndexType pnt1,
            /* [in] */ IndexType pnt2) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Surface( 
            /* [retval][out] */ ISurface **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Surface( 
            /* [in] */ ISurface *newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BeginTransition( 
            /* [in] */ VARIANT varStation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BeginTransition( 
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BeginFullWidening( 
            /* [in] */ VARIANT varStation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BeginFullWidening( 
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndFullWidening( 
            /* [in] */ VARIANT varStation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndFullWidening( 
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndTransition( 
            /* [in] */ VARIANT varStation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndTransition( 
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Widening( 
            /* [in] */ Float64 value) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Widening( 
            /* [retval][out] */ Float64 *value) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Segment( 
            /* [in] */ IndexType pntIdx,
            /* [in] */ IndexType segmentIdx) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Segment( 
            /* [in] */ IndexType pntIdx,
            /* [retval][out] */ IndexType *segmentIdx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWidening( 
            /* [in] */ VARIANT varStation,
            /* [in] */ IndexType templateSegmentIdx,
            /* [retval][out] */ Float64 *pWidening) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IWidening **ppClone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWideningVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWidening * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWidening * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWidening * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IWidening * This,
            /* [in] */ ISurface *pSurface,
            /* [in] */ VARIANT varBeginStation,
            /* [in] */ VARIANT varBeginFullStation,
            /* [in] */ VARIANT varEndFullStation,
            /* [in] */ VARIANT varEndStation,
            /* [in] */ Float64 widening,
            /* [in] */ IndexType pnt1,
            /* [in] */ IndexType pnt2);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surface )( 
            IWidening * This,
            /* [retval][out] */ ISurface **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Surface )( 
            IWidening * This,
            /* [in] */ ISurface *newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BeginTransition )( 
            IWidening * This,
            /* [in] */ VARIANT varStation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BeginTransition )( 
            IWidening * This,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BeginFullWidening )( 
            IWidening * This,
            /* [in] */ VARIANT varStation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BeginFullWidening )( 
            IWidening * This,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndFullWidening )( 
            IWidening * This,
            /* [in] */ VARIANT varStation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndFullWidening )( 
            IWidening * This,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndTransition )( 
            IWidening * This,
            /* [in] */ VARIANT varStation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndTransition )( 
            IWidening * This,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Widening )( 
            IWidening * This,
            /* [in] */ Float64 value);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Widening )( 
            IWidening * This,
            /* [retval][out] */ Float64 *value);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Segment )( 
            IWidening * This,
            /* [in] */ IndexType pntIdx,
            /* [in] */ IndexType segmentIdx);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Segment )( 
            IWidening * This,
            /* [in] */ IndexType pntIdx,
            /* [retval][out] */ IndexType *segmentIdx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetWidening )( 
            IWidening * This,
            /* [in] */ VARIANT varStation,
            /* [in] */ IndexType templateSegmentIdx,
            /* [retval][out] */ Float64 *pWidening);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IWidening * This,
            /* [retval][out] */ IWidening **ppClone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IWidening * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IWideningVtbl;

    interface IWidening
    {
        CONST_VTBL struct IWideningVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWidening_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWidening_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWidening_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWidening_Init(This,pSurface,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,widening,pnt1,pnt2)	\
    ( (This)->lpVtbl -> Init(This,pSurface,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,widening,pnt1,pnt2) ) 

#define IWidening_get_Surface(This,pVal)	\
    ( (This)->lpVtbl -> get_Surface(This,pVal) ) 

#define IWidening_putref_Surface(This,newVal)	\
    ( (This)->lpVtbl -> putref_Surface(This,newVal) ) 

#define IWidening_put_BeginTransition(This,varStation)	\
    ( (This)->lpVtbl -> put_BeginTransition(This,varStation) ) 

#define IWidening_get_BeginTransition(This,station)	\
    ( (This)->lpVtbl -> get_BeginTransition(This,station) ) 

#define IWidening_put_BeginFullWidening(This,varStation)	\
    ( (This)->lpVtbl -> put_BeginFullWidening(This,varStation) ) 

#define IWidening_get_BeginFullWidening(This,station)	\
    ( (This)->lpVtbl -> get_BeginFullWidening(This,station) ) 

#define IWidening_put_EndFullWidening(This,varStation)	\
    ( (This)->lpVtbl -> put_EndFullWidening(This,varStation) ) 

#define IWidening_get_EndFullWidening(This,station)	\
    ( (This)->lpVtbl -> get_EndFullWidening(This,station) ) 

#define IWidening_put_EndTransition(This,varStation)	\
    ( (This)->lpVtbl -> put_EndTransition(This,varStation) ) 

#define IWidening_get_EndTransition(This,station)	\
    ( (This)->lpVtbl -> get_EndTransition(This,station) ) 

#define IWidening_put_Widening(This,value)	\
    ( (This)->lpVtbl -> put_Widening(This,value) ) 

#define IWidening_get_Widening(This,value)	\
    ( (This)->lpVtbl -> get_Widening(This,value) ) 

#define IWidening_put_Segment(This,pntIdx,segmentIdx)	\
    ( (This)->lpVtbl -> put_Segment(This,pntIdx,segmentIdx) ) 

#define IWidening_get_Segment(This,pntIdx,segmentIdx)	\
    ( (This)->lpVtbl -> get_Segment(This,pntIdx,segmentIdx) ) 

#define IWidening_GetWidening(This,varStation,templateSegmentIdx,pWidening)	\
    ( (This)->lpVtbl -> GetWidening(This,varStation,templateSegmentIdx,pWidening) ) 

#define IWidening_Clone(This,ppClone)	\
    ( (This)->lpVtbl -> Clone(This,ppClone) ) 

#define IWidening_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWidening_INTERFACE_DEFINED__ */


#ifndef __IWideningEvents_INTERFACE_DEFINED__
#define __IWideningEvents_INTERFACE_DEFINED__

/* interface IWideningEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IWideningEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4C081EEC-CB28-465c-AA42-93B92458E8F4")
    IWideningEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnWideningChanged( 
            /* [in] */ IWidening *pWidening) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWideningEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWideningEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWideningEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWideningEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnWideningChanged )( 
            IWideningEvents * This,
            /* [in] */ IWidening *pWidening);
        
        END_INTERFACE
    } IWideningEventsVtbl;

    interface IWideningEvents
    {
        CONST_VTBL struct IWideningEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWideningEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWideningEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWideningEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWideningEvents_OnWideningChanged(This,pWidening)	\
    ( (This)->lpVtbl -> OnWideningChanged(This,pWidening) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWideningEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumWidenings_INTERFACE_DEFINED__
#define __IEnumWidenings_INTERFACE_DEFINED__

/* interface IEnumWidenings */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumWidenings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F580E4A7-C6CE-4482-8C00-5639CFDC26CF")
    IEnumWidenings : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumWidenings **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IWidening **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumWideningsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumWidenings * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumWidenings * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumWidenings * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumWidenings * This,
            /* [out] */ IEnumWidenings **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumWidenings * This,
            /* [in] */ ULONG celt,
            /* [out] */ IWidening **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumWidenings * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumWidenings * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumWideningsVtbl;

    interface IEnumWidenings
    {
        CONST_VTBL struct IEnumWideningsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumWidenings_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumWidenings_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumWidenings_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumWidenings_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumWidenings_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumWidenings_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumWidenings_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumWidenings_INTERFACE_DEFINED__ */


#ifndef __IWideningCollection_INTERFACE_DEFINED__
#define __IWideningCollection_INTERFACE_DEFINED__

/* interface IWideningCollection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IWideningCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D7723EA4-F8F0-4749-AF6F-CD4A1BD53546")
    IWideningCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Surface( 
            /* [retval][out] */ ISurface **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Surface( 
            /* [in] */ ISurface *newVal) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IWidening **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IWidening *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT varBeginStation,
            /* [in] */ VARIANT varBeginFullStation,
            /* [in] */ VARIANT varEndFullStation,
            /* [in] */ VARIANT varEndStation,
            /* [in] */ Float64 widening,
            /* [in] */ IndexType pnt1,
            /* [in] */ IndexType pnt2,
            /* [retval][out] */ IWidening **pWidening) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ IWidening *csect) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumWidenings( 
            /* [retval][out] */ IEnumWidenings **retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IWideningCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWidening( 
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ IWidening **widening) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWideningCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWideningCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWideningCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWideningCollection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surface )( 
            IWideningCollection * This,
            /* [retval][out] */ ISurface **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Surface )( 
            IWideningCollection * This,
            /* [in] */ ISurface *newVal);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWideningCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWideningCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IWidening **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IWideningCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IWidening *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWideningCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWideningCollection * This,
            /* [in] */ VARIANT varBeginStation,
            /* [in] */ VARIANT varBeginFullStation,
            /* [in] */ VARIANT varEndFullStation,
            /* [in] */ VARIANT varEndStation,
            /* [in] */ Float64 widening,
            /* [in] */ IndexType pnt1,
            /* [in] */ IndexType pnt2,
            /* [retval][out] */ IWidening **pWidening);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            IWideningCollection * This,
            /* [in] */ IWidening *csect);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IWideningCollection * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IWideningCollection * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumWidenings )( 
            IWideningCollection * This,
            /* [retval][out] */ IEnumWidenings **retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IWideningCollection * This,
            /* [retval][out] */ IWideningCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IWideningCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetWidening )( 
            IWideningCollection * This,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ IWidening **widening);
        
        END_INTERFACE
    } IWideningCollectionVtbl;

    interface IWideningCollection
    {
        CONST_VTBL struct IWideningCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWideningCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWideningCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWideningCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWideningCollection_get_Surface(This,pVal)	\
    ( (This)->lpVtbl -> get_Surface(This,pVal) ) 

#define IWideningCollection_putref_Surface(This,newVal)	\
    ( (This)->lpVtbl -> putref_Surface(This,newVal) ) 

#define IWideningCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IWideningCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IWideningCollection_putref_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> putref_Item(This,idx,pVal) ) 

#define IWideningCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IWideningCollection_Add(This,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,widening,pnt1,pnt2,pWidening)	\
    ( (This)->lpVtbl -> Add(This,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,widening,pnt1,pnt2,pWidening) ) 

#define IWideningCollection_AddEx(This,csect)	\
    ( (This)->lpVtbl -> AddEx(This,csect) ) 

#define IWideningCollection_Remove(This,idx)	\
    ( (This)->lpVtbl -> Remove(This,idx) ) 

#define IWideningCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IWideningCollection_get__EnumWidenings(This,retval)	\
    ( (This)->lpVtbl -> get__EnumWidenings(This,retval) ) 

#define IWideningCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IWideningCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#define IWideningCollection_GetWidening(This,varStation,widening)	\
    ( (This)->lpVtbl -> GetWidening(This,varStation,widening) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWideningCollection_INTERFACE_DEFINED__ */


#ifndef __IWideningCollectionEvents_INTERFACE_DEFINED__
#define __IWideningCollectionEvents_INTERFACE_DEFINED__

/* interface IWideningCollectionEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IWideningCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D3C1C368-EDBF-4302-8FC0-65B2150E1C57")
    IWideningCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnWideningChanged( 
            /* [in] */ IWidening *pWidening) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnWideningAdded( 
            /* [in] */ IWidening *pWidening) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnWideningRemoved( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnWideningsCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWideningCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWideningCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWideningCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWideningCollectionEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnWideningChanged )( 
            IWideningCollectionEvents * This,
            /* [in] */ IWidening *pWidening);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnWideningAdded )( 
            IWideningCollectionEvents * This,
            /* [in] */ IWidening *pWidening);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnWideningRemoved )( 
            IWideningCollectionEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnWideningsCleared )( 
            IWideningCollectionEvents * This);
        
        END_INTERFACE
    } IWideningCollectionEventsVtbl;

    interface IWideningCollectionEvents
    {
        CONST_VTBL struct IWideningCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWideningCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWideningCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWideningCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWideningCollectionEvents_OnWideningChanged(This,pWidening)	\
    ( (This)->lpVtbl -> OnWideningChanged(This,pWidening) ) 

#define IWideningCollectionEvents_OnWideningAdded(This,pWidening)	\
    ( (This)->lpVtbl -> OnWideningAdded(This,pWidening) ) 

#define IWideningCollectionEvents_OnWideningRemoved(This)	\
    ( (This)->lpVtbl -> OnWideningRemoved(This) ) 

#define IWideningCollectionEvents_OnWideningsCleared(This)	\
    ( (This)->lpVtbl -> OnWideningsCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWideningCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __ISuperelevation_INTERFACE_DEFINED__
#define __ISuperelevation_INTERFACE_DEFINED__

/* interface ISuperelevation */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISuperelevation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C261362D-E01F-49c5-95ED-E8A8FBC68FB9")
    ISuperelevation : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ ISurface *pSurface,
            /* [in] */ VARIANT varBeginStation,
            /* [in] */ VARIANT varBeginFullStation,
            /* [in] */ VARIANT varEndFullStation,
            /* [in] */ VARIANT varEndStation,
            /* [in] */ Float64 rate,
            /* [in] */ IndexType pivotPoint,
            /* [in] */ SuperTransitionType beginType,
            /* [in] */ Float64 beginL1,
            /* [in] */ Float64 beginL2,
            /* [in] */ SuperTransitionType endType,
            /* [in] */ Float64 endL1,
            /* [in] */ Float64 endL2) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Surface( 
            /* [retval][out] */ ISurface **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Surface( 
            /* [in] */ ISurface *newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BeginTransition( 
            /* [in] */ VARIANT varBeginTransition) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BeginTransition( 
            /* [retval][out] */ IStation **ppBeginTransition) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BeginFullSuper( 
            /* [in] */ VARIANT varBeginFullSuper) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BeginFullSuper( 
            /* [retval][out] */ IStation **ppBeginFullSuper) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndFullSuper( 
            /* [in] */ VARIANT varEndFullSuper) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndFullSuper( 
            /* [retval][out] */ IStation **ppEndFullSuper) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndTransition( 
            /* [in] */ VARIANT varEndTransition) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndTransition( 
            /* [retval][out] */ IStation **ppEndTransition) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Rate( 
            /* [in] */ Float64 rate) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Rate( 
            /* [retval][out] */ Float64 *rate) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PivotPoint( 
            /* [in] */ IndexType pivotPointIdx) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PivotPoint( 
            /* [retval][out] */ IndexType *pivotPointIdx) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BeginTransitionType( 
            /* [in] */ SuperTransitionType type) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BeginTransitionType( 
            /* [retval][out] */ SuperTransitionType *type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetBeginTransitionParameters( 
            /* [in] */ Float64 L1,
            /* [in] */ Float64 L2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBeginTransitionParameters( 
            /* [out] */ Float64 *L1,
            /* [out] */ Float64 *L2) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndTransitionType( 
            /* [in] */ SuperTransitionType type) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndTransitionType( 
            /* [retval][out] */ SuperTransitionType *type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetEndTransitionParameters( 
            /* [in] */ Float64 L1,
            /* [in] */ Float64 L2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEndTransitionParameters( 
            /* [out] */ Float64 *L1,
            /* [out] */ Float64 *L2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSlope( 
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 templateSlope,
            /* [retval][out] */ Float64 *pSlope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISuperelevation **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperelevationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperelevation * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperelevation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperelevation * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            ISuperelevation * This,
            /* [in] */ ISurface *pSurface,
            /* [in] */ VARIANT varBeginStation,
            /* [in] */ VARIANT varBeginFullStation,
            /* [in] */ VARIANT varEndFullStation,
            /* [in] */ VARIANT varEndStation,
            /* [in] */ Float64 rate,
            /* [in] */ IndexType pivotPoint,
            /* [in] */ SuperTransitionType beginType,
            /* [in] */ Float64 beginL1,
            /* [in] */ Float64 beginL2,
            /* [in] */ SuperTransitionType endType,
            /* [in] */ Float64 endL1,
            /* [in] */ Float64 endL2);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surface )( 
            ISuperelevation * This,
            /* [retval][out] */ ISurface **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Surface )( 
            ISuperelevation * This,
            /* [in] */ ISurface *newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BeginTransition )( 
            ISuperelevation * This,
            /* [in] */ VARIANT varBeginTransition);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BeginTransition )( 
            ISuperelevation * This,
            /* [retval][out] */ IStation **ppBeginTransition);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BeginFullSuper )( 
            ISuperelevation * This,
            /* [in] */ VARIANT varBeginFullSuper);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BeginFullSuper )( 
            ISuperelevation * This,
            /* [retval][out] */ IStation **ppBeginFullSuper);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndFullSuper )( 
            ISuperelevation * This,
            /* [in] */ VARIANT varEndFullSuper);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndFullSuper )( 
            ISuperelevation * This,
            /* [retval][out] */ IStation **ppEndFullSuper);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndTransition )( 
            ISuperelevation * This,
            /* [in] */ VARIANT varEndTransition);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndTransition )( 
            ISuperelevation * This,
            /* [retval][out] */ IStation **ppEndTransition);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Rate )( 
            ISuperelevation * This,
            /* [in] */ Float64 rate);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rate )( 
            ISuperelevation * This,
            /* [retval][out] */ Float64 *rate);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PivotPoint )( 
            ISuperelevation * This,
            /* [in] */ IndexType pivotPointIdx);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PivotPoint )( 
            ISuperelevation * This,
            /* [retval][out] */ IndexType *pivotPointIdx);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BeginTransitionType )( 
            ISuperelevation * This,
            /* [in] */ SuperTransitionType type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BeginTransitionType )( 
            ISuperelevation * This,
            /* [retval][out] */ SuperTransitionType *type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetBeginTransitionParameters )( 
            ISuperelevation * This,
            /* [in] */ Float64 L1,
            /* [in] */ Float64 L2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBeginTransitionParameters )( 
            ISuperelevation * This,
            /* [out] */ Float64 *L1,
            /* [out] */ Float64 *L2);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndTransitionType )( 
            ISuperelevation * This,
            /* [in] */ SuperTransitionType type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndTransitionType )( 
            ISuperelevation * This,
            /* [retval][out] */ SuperTransitionType *type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEndTransitionParameters )( 
            ISuperelevation * This,
            /* [in] */ Float64 L1,
            /* [in] */ Float64 L2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEndTransitionParameters )( 
            ISuperelevation * This,
            /* [out] */ Float64 *L1,
            /* [out] */ Float64 *L2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSlope )( 
            ISuperelevation * This,
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 templateSlope,
            /* [retval][out] */ Float64 *pSlope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISuperelevation * This,
            /* [retval][out] */ ISuperelevation **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ISuperelevation * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ISuperelevationVtbl;

    interface ISuperelevation
    {
        CONST_VTBL struct ISuperelevationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperelevation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperelevation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperelevation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperelevation_Init(This,pSurface,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,rate,pivotPoint,beginType,beginL1,beginL2,endType,endL1,endL2)	\
    ( (This)->lpVtbl -> Init(This,pSurface,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,rate,pivotPoint,beginType,beginL1,beginL2,endType,endL1,endL2) ) 

#define ISuperelevation_get_Surface(This,pVal)	\
    ( (This)->lpVtbl -> get_Surface(This,pVal) ) 

#define ISuperelevation_putref_Surface(This,newVal)	\
    ( (This)->lpVtbl -> putref_Surface(This,newVal) ) 

#define ISuperelevation_put_BeginTransition(This,varBeginTransition)	\
    ( (This)->lpVtbl -> put_BeginTransition(This,varBeginTransition) ) 

#define ISuperelevation_get_BeginTransition(This,ppBeginTransition)	\
    ( (This)->lpVtbl -> get_BeginTransition(This,ppBeginTransition) ) 

#define ISuperelevation_put_BeginFullSuper(This,varBeginFullSuper)	\
    ( (This)->lpVtbl -> put_BeginFullSuper(This,varBeginFullSuper) ) 

#define ISuperelevation_get_BeginFullSuper(This,ppBeginFullSuper)	\
    ( (This)->lpVtbl -> get_BeginFullSuper(This,ppBeginFullSuper) ) 

#define ISuperelevation_put_EndFullSuper(This,varEndFullSuper)	\
    ( (This)->lpVtbl -> put_EndFullSuper(This,varEndFullSuper) ) 

#define ISuperelevation_get_EndFullSuper(This,ppEndFullSuper)	\
    ( (This)->lpVtbl -> get_EndFullSuper(This,ppEndFullSuper) ) 

#define ISuperelevation_put_EndTransition(This,varEndTransition)	\
    ( (This)->lpVtbl -> put_EndTransition(This,varEndTransition) ) 

#define ISuperelevation_get_EndTransition(This,ppEndTransition)	\
    ( (This)->lpVtbl -> get_EndTransition(This,ppEndTransition) ) 

#define ISuperelevation_put_Rate(This,rate)	\
    ( (This)->lpVtbl -> put_Rate(This,rate) ) 

#define ISuperelevation_get_Rate(This,rate)	\
    ( (This)->lpVtbl -> get_Rate(This,rate) ) 

#define ISuperelevation_put_PivotPoint(This,pivotPointIdx)	\
    ( (This)->lpVtbl -> put_PivotPoint(This,pivotPointIdx) ) 

#define ISuperelevation_get_PivotPoint(This,pivotPointIdx)	\
    ( (This)->lpVtbl -> get_PivotPoint(This,pivotPointIdx) ) 

#define ISuperelevation_put_BeginTransitionType(This,type)	\
    ( (This)->lpVtbl -> put_BeginTransitionType(This,type) ) 

#define ISuperelevation_get_BeginTransitionType(This,type)	\
    ( (This)->lpVtbl -> get_BeginTransitionType(This,type) ) 

#define ISuperelevation_SetBeginTransitionParameters(This,L1,L2)	\
    ( (This)->lpVtbl -> SetBeginTransitionParameters(This,L1,L2) ) 

#define ISuperelevation_GetBeginTransitionParameters(This,L1,L2)	\
    ( (This)->lpVtbl -> GetBeginTransitionParameters(This,L1,L2) ) 

#define ISuperelevation_put_EndTransitionType(This,type)	\
    ( (This)->lpVtbl -> put_EndTransitionType(This,type) ) 

#define ISuperelevation_get_EndTransitionType(This,type)	\
    ( (This)->lpVtbl -> get_EndTransitionType(This,type) ) 

#define ISuperelevation_SetEndTransitionParameters(This,L1,L2)	\
    ( (This)->lpVtbl -> SetEndTransitionParameters(This,L1,L2) ) 

#define ISuperelevation_GetEndTransitionParameters(This,L1,L2)	\
    ( (This)->lpVtbl -> GetEndTransitionParameters(This,L1,L2) ) 

#define ISuperelevation_GetSlope(This,varStation,templateSlope,pSlope)	\
    ( (This)->lpVtbl -> GetSlope(This,varStation,templateSlope,pSlope) ) 

#define ISuperelevation_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISuperelevation_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperelevation_INTERFACE_DEFINED__ */


#ifndef __ISuperelevationEvents_INTERFACE_DEFINED__
#define __ISuperelevationEvents_INTERFACE_DEFINED__

/* interface ISuperelevationEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISuperelevationEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B8D6C861-BFCA-4dc7-B65B-C7EE2ED6371F")
    ISuperelevationEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperelevationChanged( 
            /* [in] */ ISuperelevation *pSuperelevation) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperelevationEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperelevationEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperelevationEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperelevationEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperelevationChanged )( 
            ISuperelevationEvents * This,
            /* [in] */ ISuperelevation *pSuperelevation);
        
        END_INTERFACE
    } ISuperelevationEventsVtbl;

    interface ISuperelevationEvents
    {
        CONST_VTBL struct ISuperelevationEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperelevationEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperelevationEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperelevationEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperelevationEvents_OnSuperelevationChanged(This,pSuperelevation)	\
    ( (This)->lpVtbl -> OnSuperelevationChanged(This,pSuperelevation) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperelevationEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumSuperelevations_INTERFACE_DEFINED__
#define __IEnumSuperelevations_INTERFACE_DEFINED__

/* interface IEnumSuperelevations */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSuperelevations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FD9B1B87-7F5D-4654-80A3-F86E05DCDDE8")
    IEnumSuperelevations : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSuperelevations **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISuperelevation **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSuperelevationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSuperelevations * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSuperelevations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSuperelevations * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSuperelevations * This,
            /* [out] */ IEnumSuperelevations **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSuperelevations * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISuperelevation **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSuperelevations * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSuperelevations * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSuperelevationsVtbl;

    interface IEnumSuperelevations
    {
        CONST_VTBL struct IEnumSuperelevationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSuperelevations_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSuperelevations_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSuperelevations_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSuperelevations_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSuperelevations_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSuperelevations_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSuperelevations_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSuperelevations_INTERFACE_DEFINED__ */


#ifndef __ISuperelevationCollection_INTERFACE_DEFINED__
#define __ISuperelevationCollection_INTERFACE_DEFINED__

/* interface ISuperelevationCollection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISuperelevationCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A398C05-0903-42a7-9C50-34CD958E036E")
    ISuperelevationCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Surface( 
            /* [retval][out] */ ISurface **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Surface( 
            /* [in] */ ISurface *newVal) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISuperelevation **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ ISuperelevation *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT varBeginStation,
            /* [in] */ VARIANT varBeginFullStation,
            /* [in] */ VARIANT varEndFullStation,
            /* [in] */ VARIANT varEndStation,
            /* [in] */ Float64 rate,
            /* [in] */ IndexType pivotPoint,
            /* [in] */ SuperTransitionType beginType,
            /* [in] */ Float64 beginL1,
            /* [in] */ Float64 beginL2,
            /* [in] */ SuperTransitionType endType,
            /* [in] */ Float64 endL1,
            /* [in] */ Float64 endL2,
            /* [retval][out] */ ISuperelevation **pSuperelevation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ ISuperelevation *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSuperelevation( 
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ ISuperelevation **superelevation) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumSuperelevations( 
            /* [retval][out] */ IEnumSuperelevations **retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISuperelevationCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperelevationCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperelevationCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperelevationCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperelevationCollection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surface )( 
            ISuperelevationCollection * This,
            /* [retval][out] */ ISurface **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Surface )( 
            ISuperelevationCollection * This,
            /* [in] */ ISurface *newVal);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISuperelevationCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISuperelevationCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISuperelevation **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            ISuperelevationCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ ISuperelevation *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISuperelevationCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISuperelevationCollection * This,
            /* [in] */ VARIANT varBeginStation,
            /* [in] */ VARIANT varBeginFullStation,
            /* [in] */ VARIANT varEndFullStation,
            /* [in] */ VARIANT varEndStation,
            /* [in] */ Float64 rate,
            /* [in] */ IndexType pivotPoint,
            /* [in] */ SuperTransitionType beginType,
            /* [in] */ Float64 beginL1,
            /* [in] */ Float64 beginL2,
            /* [in] */ SuperTransitionType endType,
            /* [in] */ Float64 endL1,
            /* [in] */ Float64 endL2,
            /* [retval][out] */ ISuperelevation **pSuperelevation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            ISuperelevationCollection * This,
            /* [in] */ ISuperelevation *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ISuperelevationCollection * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISuperelevationCollection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSuperelevation )( 
            ISuperelevationCollection * This,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ ISuperelevation **superelevation);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumSuperelevations )( 
            ISuperelevationCollection * This,
            /* [retval][out] */ IEnumSuperelevations **retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISuperelevationCollection * This,
            /* [retval][out] */ ISuperelevationCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ISuperelevationCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ISuperelevationCollectionVtbl;

    interface ISuperelevationCollection
    {
        CONST_VTBL struct ISuperelevationCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperelevationCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperelevationCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperelevationCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperelevationCollection_get_Surface(This,pVal)	\
    ( (This)->lpVtbl -> get_Surface(This,pVal) ) 

#define ISuperelevationCollection_putref_Surface(This,newVal)	\
    ( (This)->lpVtbl -> putref_Surface(This,newVal) ) 

#define ISuperelevationCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ISuperelevationCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define ISuperelevationCollection_putref_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> putref_Item(This,idx,pVal) ) 

#define ISuperelevationCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISuperelevationCollection_Add(This,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,rate,pivotPoint,beginType,beginL1,beginL2,endType,endL1,endL2,pSuperelevation)	\
    ( (This)->lpVtbl -> Add(This,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,rate,pivotPoint,beginType,beginL1,beginL2,endType,endL1,endL2,pSuperelevation) ) 

#define ISuperelevationCollection_AddEx(This,pVal)	\
    ( (This)->lpVtbl -> AddEx(This,pVal) ) 

#define ISuperelevationCollection_Remove(This,idx)	\
    ( (This)->lpVtbl -> Remove(This,idx) ) 

#define ISuperelevationCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ISuperelevationCollection_GetSuperelevation(This,varStation,superelevation)	\
    ( (This)->lpVtbl -> GetSuperelevation(This,varStation,superelevation) ) 

#define ISuperelevationCollection_get__EnumSuperelevations(This,retval)	\
    ( (This)->lpVtbl -> get__EnumSuperelevations(This,retval) ) 

#define ISuperelevationCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISuperelevationCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperelevationCollection_INTERFACE_DEFINED__ */


#ifndef __ISuperelevationCollectionEvents_INTERFACE_DEFINED__
#define __ISuperelevationCollectionEvents_INTERFACE_DEFINED__

/* interface ISuperelevationCollectionEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISuperelevationCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6E02AF30-D533-4bc3-9341-B901CF331FB1")
    ISuperelevationCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperelevationChanged( 
            /* [in] */ ISuperelevation *pSuperelevation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperelevationAdded( 
            /* [in] */ ISuperelevation *pSuperelevation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperelevationRemoved( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperelevationsCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperelevationCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperelevationCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperelevationCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperelevationCollectionEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperelevationChanged )( 
            ISuperelevationCollectionEvents * This,
            /* [in] */ ISuperelevation *pSuperelevation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperelevationAdded )( 
            ISuperelevationCollectionEvents * This,
            /* [in] */ ISuperelevation *pSuperelevation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperelevationRemoved )( 
            ISuperelevationCollectionEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperelevationsCleared )( 
            ISuperelevationCollectionEvents * This);
        
        END_INTERFACE
    } ISuperelevationCollectionEventsVtbl;

    interface ISuperelevationCollectionEvents
    {
        CONST_VTBL struct ISuperelevationCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperelevationCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperelevationCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperelevationCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperelevationCollectionEvents_OnSuperelevationChanged(This,pSuperelevation)	\
    ( (This)->lpVtbl -> OnSuperelevationChanged(This,pSuperelevation) ) 

#define ISuperelevationCollectionEvents_OnSuperelevationAdded(This,pSuperelevation)	\
    ( (This)->lpVtbl -> OnSuperelevationAdded(This,pSuperelevation) ) 

#define ISuperelevationCollectionEvents_OnSuperelevationRemoved(This)	\
    ( (This)->lpVtbl -> OnSuperelevationRemoved(This) ) 

#define ISuperelevationCollectionEvents_OnSuperelevationsCleared(This)	\
    ( (This)->lpVtbl -> OnSuperelevationsCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperelevationCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __ITemplateSegment_INTERFACE_DEFINED__
#define __ITemplateSegment_INTERFACE_DEFINED__

/* interface ITemplateSegment */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITemplateSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B3D0955A-0174-4085-A6F7-C71ACAC612D7")
    ITemplateSegment : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ Float64 width,
            /* [in] */ Float64 slope,
            /* [in] */ TemplateSlopeType slopeType) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ Float64 width) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ Float64 *width) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Slope( 
            /* [in] */ Float64 slope) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Slope( 
            /* [retval][out] */ Float64 *slope) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SlopeType( 
            /* [in] */ TemplateSlopeType type) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SlopeType( 
            /* [retval][out] */ TemplateSlopeType *type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ITemplateSegment **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemplateSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemplateSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemplateSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemplateSegment * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            ITemplateSegment * This,
            /* [in] */ Float64 width,
            /* [in] */ Float64 slope,
            /* [in] */ TemplateSlopeType slopeType);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            ITemplateSegment * This,
            /* [in] */ Float64 width);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            ITemplateSegment * This,
            /* [retval][out] */ Float64 *width);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slope )( 
            ITemplateSegment * This,
            /* [in] */ Float64 slope);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            ITemplateSegment * This,
            /* [retval][out] */ Float64 *slope);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SlopeType )( 
            ITemplateSegment * This,
            /* [in] */ TemplateSlopeType type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SlopeType )( 
            ITemplateSegment * This,
            /* [retval][out] */ TemplateSlopeType *type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITemplateSegment * This,
            /* [retval][out] */ ITemplateSegment **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ITemplateSegment * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ITemplateSegmentVtbl;

    interface ITemplateSegment
    {
        CONST_VTBL struct ITemplateSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemplateSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemplateSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemplateSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemplateSegment_Init(This,width,slope,slopeType)	\
    ( (This)->lpVtbl -> Init(This,width,slope,slopeType) ) 

#define ITemplateSegment_put_Width(This,width)	\
    ( (This)->lpVtbl -> put_Width(This,width) ) 

#define ITemplateSegment_get_Width(This,width)	\
    ( (This)->lpVtbl -> get_Width(This,width) ) 

#define ITemplateSegment_put_Slope(This,slope)	\
    ( (This)->lpVtbl -> put_Slope(This,slope) ) 

#define ITemplateSegment_get_Slope(This,slope)	\
    ( (This)->lpVtbl -> get_Slope(This,slope) ) 

#define ITemplateSegment_put_SlopeType(This,type)	\
    ( (This)->lpVtbl -> put_SlopeType(This,type) ) 

#define ITemplateSegment_get_SlopeType(This,type)	\
    ( (This)->lpVtbl -> get_SlopeType(This,type) ) 

#define ITemplateSegment_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ITemplateSegment_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemplateSegment_INTERFACE_DEFINED__ */


#ifndef __ITemplateSegmentEvents_INTERFACE_DEFINED__
#define __ITemplateSegmentEvents_INTERFACE_DEFINED__

/* interface ITemplateSegmentEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITemplateSegmentEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("65775E88-FC55-4387-9752-5F45686DC55B")
    ITemplateSegmentEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnTemplateSegmentChanged( 
            /* [in] */ ITemplateSegment *pSegment) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemplateSegmentEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemplateSegmentEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemplateSegmentEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemplateSegmentEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemplateSegmentChanged )( 
            ITemplateSegmentEvents * This,
            /* [in] */ ITemplateSegment *pSegment);
        
        END_INTERFACE
    } ITemplateSegmentEventsVtbl;

    interface ITemplateSegmentEvents
    {
        CONST_VTBL struct ITemplateSegmentEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemplateSegmentEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemplateSegmentEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemplateSegmentEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemplateSegmentEvents_OnTemplateSegmentChanged(This,pSegment)	\
    ( (This)->lpVtbl -> OnTemplateSegmentChanged(This,pSegment) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemplateSegmentEvents_INTERFACE_DEFINED__ */


#ifndef __ISurfaceTemplate_INTERFACE_DEFINED__
#define __ISurfaceTemplate_INTERFACE_DEFINED__

/* interface ISurfaceTemplate */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISurfaceTemplate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D2286685-D34F-4a59-B7C7-9B531D1C9713")
    ISurfaceTemplate : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Surface( 
            /* [retval][out] */ ISurface **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Surface( 
            /* [in] */ ISurface *newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Station( 
            /* [in] */ VARIANT varStation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Station( 
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddSegment( 
            /* [in] */ Float64 width,
            /* [in] */ Float64 slope,
            /* [in] */ TemplateSlopeType slopeType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddSegmentEx( 
            /* [in] */ ITemplateSegment *segment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveSegment( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ITemplateSegment **segment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRidgePointElevationChange( 
            /* [in] */ CollectionIndexType ridgePointIdx1,
            /* [in] */ CollectionIndexType ridgePointIdx2,
            /* [retval][out] */ Float64 *deltaElevation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetElevationChange( 
            /* [in] */ CollectionIndexType ridgePointIdx,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *deltaElevation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSlope( 
            /* [in] */ CollectionIndexType ridgePointIdx,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *pSlope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentSlope( 
            /* [in] */ CollectionIndexType segmentIdx,
            /* [retval][out] */ Float64 *pSlope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRidgePointOffset( 
            /* [in] */ IndexType ridgePointIdx,
            /* [in] */ IndexType refPointIdx,
            /* [out] */ Float64 *pOffset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRidgePointElevation( 
            /* [in] */ IndexType ridgePointIdx,
            /* [in] */ IndexType refPointIdx,
            /* [out] */ Float64 *pOffset,
            /* [out] */ Float64 *pElev) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISurfaceTemplate **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfaceTemplateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurfaceTemplate * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurfaceTemplate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurfaceTemplate * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surface )( 
            ISurfaceTemplate * This,
            /* [retval][out] */ ISurface **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Surface )( 
            ISurfaceTemplate * This,
            /* [in] */ ISurface *newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Station )( 
            ISurfaceTemplate * This,
            /* [in] */ VARIANT varStation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Station )( 
            ISurfaceTemplate * This,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSegment )( 
            ISurfaceTemplate * This,
            /* [in] */ Float64 width,
            /* [in] */ Float64 slope,
            /* [in] */ TemplateSlopeType slopeType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSegmentEx )( 
            ISurfaceTemplate * This,
            /* [in] */ ITemplateSegment *segment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveSegment )( 
            ISurfaceTemplate * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISurfaceTemplate * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISurfaceTemplate * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ITemplateSegment **segment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRidgePointElevationChange )( 
            ISurfaceTemplate * This,
            /* [in] */ CollectionIndexType ridgePointIdx1,
            /* [in] */ CollectionIndexType ridgePointIdx2,
            /* [retval][out] */ Float64 *deltaElevation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetElevationChange )( 
            ISurfaceTemplate * This,
            /* [in] */ CollectionIndexType ridgePointIdx,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *deltaElevation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSlope )( 
            ISurfaceTemplate * This,
            /* [in] */ CollectionIndexType ridgePointIdx,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *pSlope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentSlope )( 
            ISurfaceTemplate * This,
            /* [in] */ CollectionIndexType segmentIdx,
            /* [retval][out] */ Float64 *pSlope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRidgePointOffset )( 
            ISurfaceTemplate * This,
            /* [in] */ IndexType ridgePointIdx,
            /* [in] */ IndexType refPointIdx,
            /* [out] */ Float64 *pOffset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRidgePointElevation )( 
            ISurfaceTemplate * This,
            /* [in] */ IndexType ridgePointIdx,
            /* [in] */ IndexType refPointIdx,
            /* [out] */ Float64 *pOffset,
            /* [out] */ Float64 *pElev);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISurfaceTemplate * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISurfaceTemplate * This,
            /* [retval][out] */ ISurfaceTemplate **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ISurfaceTemplate * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ISurfaceTemplateVtbl;

    interface ISurfaceTemplate
    {
        CONST_VTBL struct ISurfaceTemplateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurfaceTemplate_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurfaceTemplate_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurfaceTemplate_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurfaceTemplate_get_Surface(This,pVal)	\
    ( (This)->lpVtbl -> get_Surface(This,pVal) ) 

#define ISurfaceTemplate_putref_Surface(This,newVal)	\
    ( (This)->lpVtbl -> putref_Surface(This,newVal) ) 

#define ISurfaceTemplate_put_Station(This,varStation)	\
    ( (This)->lpVtbl -> put_Station(This,varStation) ) 

#define ISurfaceTemplate_get_Station(This,station)	\
    ( (This)->lpVtbl -> get_Station(This,station) ) 

#define ISurfaceTemplate_AddSegment(This,width,slope,slopeType)	\
    ( (This)->lpVtbl -> AddSegment(This,width,slope,slopeType) ) 

#define ISurfaceTemplate_AddSegmentEx(This,segment)	\
    ( (This)->lpVtbl -> AddSegmentEx(This,segment) ) 

#define ISurfaceTemplate_RemoveSegment(This,idx)	\
    ( (This)->lpVtbl -> RemoveSegment(This,idx) ) 

#define ISurfaceTemplate_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define ISurfaceTemplate_get_Item(This,idx,segment)	\
    ( (This)->lpVtbl -> get_Item(This,idx,segment) ) 

#define ISurfaceTemplate_GetRidgePointElevationChange(This,ridgePointIdx1,ridgePointIdx2,deltaElevation)	\
    ( (This)->lpVtbl -> GetRidgePointElevationChange(This,ridgePointIdx1,ridgePointIdx2,deltaElevation) ) 

#define ISurfaceTemplate_GetElevationChange(This,ridgePointIdx,offset,deltaElevation)	\
    ( (This)->lpVtbl -> GetElevationChange(This,ridgePointIdx,offset,deltaElevation) ) 

#define ISurfaceTemplate_GetSlope(This,ridgePointIdx,offset,pSlope)	\
    ( (This)->lpVtbl -> GetSlope(This,ridgePointIdx,offset,pSlope) ) 

#define ISurfaceTemplate_GetSegmentSlope(This,segmentIdx,pSlope)	\
    ( (This)->lpVtbl -> GetSegmentSlope(This,segmentIdx,pSlope) ) 

#define ISurfaceTemplate_GetRidgePointOffset(This,ridgePointIdx,refPointIdx,pOffset)	\
    ( (This)->lpVtbl -> GetRidgePointOffset(This,ridgePointIdx,refPointIdx,pOffset) ) 

#define ISurfaceTemplate_GetRidgePointElevation(This,ridgePointIdx,refPointIdx,pOffset,pElev)	\
    ( (This)->lpVtbl -> GetRidgePointElevation(This,ridgePointIdx,refPointIdx,pOffset,pElev) ) 

#define ISurfaceTemplate_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ISurfaceTemplate_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISurfaceTemplate_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfaceTemplate_INTERFACE_DEFINED__ */


#ifndef __ISurfaceTemplateEvents_INTERFACE_DEFINED__
#define __ISurfaceTemplateEvents_INTERFACE_DEFINED__

/* interface ISurfaceTemplateEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISurfaceTemplateEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E7E90090-DECB-4646-BAFB-4C8BF9B765B4")
    ISurfaceTemplateEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSurfaceTemplateChanged( 
            /* [in] */ ISurfaceTemplate *pTemplate) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnTemplateSegmentAdded( 
            /* [in] */ ISurfaceTemplate *pTemplate,
            /* [in] */ ITemplateSegment *pSegment) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnTemplateSegmentRemoved( 
            /* [in] */ ISurfaceTemplate *pTemplate) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnTemplateSegmentsCleared( 
            /* [in] */ ISurfaceTemplate *pTemplate) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfaceTemplateEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurfaceTemplateEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurfaceTemplateEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurfaceTemplateEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSurfaceTemplateChanged )( 
            ISurfaceTemplateEvents * This,
            /* [in] */ ISurfaceTemplate *pTemplate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemplateSegmentAdded )( 
            ISurfaceTemplateEvents * This,
            /* [in] */ ISurfaceTemplate *pTemplate,
            /* [in] */ ITemplateSegment *pSegment);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemplateSegmentRemoved )( 
            ISurfaceTemplateEvents * This,
            /* [in] */ ISurfaceTemplate *pTemplate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemplateSegmentsCleared )( 
            ISurfaceTemplateEvents * This,
            /* [in] */ ISurfaceTemplate *pTemplate);
        
        END_INTERFACE
    } ISurfaceTemplateEventsVtbl;

    interface ISurfaceTemplateEvents
    {
        CONST_VTBL struct ISurfaceTemplateEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurfaceTemplateEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurfaceTemplateEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurfaceTemplateEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurfaceTemplateEvents_OnSurfaceTemplateChanged(This,pTemplate)	\
    ( (This)->lpVtbl -> OnSurfaceTemplateChanged(This,pTemplate) ) 

#define ISurfaceTemplateEvents_OnTemplateSegmentAdded(This,pTemplate,pSegment)	\
    ( (This)->lpVtbl -> OnTemplateSegmentAdded(This,pTemplate,pSegment) ) 

#define ISurfaceTemplateEvents_OnTemplateSegmentRemoved(This,pTemplate)	\
    ( (This)->lpVtbl -> OnTemplateSegmentRemoved(This,pTemplate) ) 

#define ISurfaceTemplateEvents_OnTemplateSegmentsCleared(This,pTemplate)	\
    ( (This)->lpVtbl -> OnTemplateSegmentsCleared(This,pTemplate) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfaceTemplateEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumSurfaceTemplates_INTERFACE_DEFINED__
#define __IEnumSurfaceTemplates_INTERFACE_DEFINED__

/* interface IEnumSurfaceTemplates */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSurfaceTemplates;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D0644265-55FE-499e-9090-5E80B6641247")
    IEnumSurfaceTemplates : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSurfaceTemplates **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISurfaceTemplate **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSurfaceTemplatesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSurfaceTemplates * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSurfaceTemplates * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSurfaceTemplates * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSurfaceTemplates * This,
            /* [out] */ IEnumSurfaceTemplates **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSurfaceTemplates * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISurfaceTemplate **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSurfaceTemplates * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSurfaceTemplates * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSurfaceTemplatesVtbl;

    interface IEnumSurfaceTemplates
    {
        CONST_VTBL struct IEnumSurfaceTemplatesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSurfaceTemplates_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSurfaceTemplates_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSurfaceTemplates_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSurfaceTemplates_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSurfaceTemplates_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSurfaceTemplates_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSurfaceTemplates_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSurfaceTemplates_INTERFACE_DEFINED__ */


#ifndef __ISurfaceTemplateCollection_INTERFACE_DEFINED__
#define __ISurfaceTemplateCollection_INTERFACE_DEFINED__

/* interface ISurfaceTemplateCollection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISurfaceTemplateCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9F5259B4-F4A0-48b4-8899-AF80C1B26DB9")
    ISurfaceTemplateCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Surface( 
            /* [retval][out] */ ISurface **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Surface( 
            /* [in] */ ISurface *newVal) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISurfaceTemplate **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ ISurfaceTemplate *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ISurfaceTemplate *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBoundingTemplates( 
            /* [in] */ VARIANT varStation,
            /* [out] */ ISurfaceTemplate **ppStart,
            /* [out] */ ISurfaceTemplate **ppEnd) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumSurfaceTemplates( 
            /* [retval][out] */ IEnumSurfaceTemplates **retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISurfaceTemplateCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfaceTemplateCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurfaceTemplateCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurfaceTemplateCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurfaceTemplateCollection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surface )( 
            ISurfaceTemplateCollection * This,
            /* [retval][out] */ ISurface **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Surface )( 
            ISurfaceTemplateCollection * This,
            /* [in] */ ISurface *newVal);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISurfaceTemplateCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISurfaceTemplateCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISurfaceTemplate **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            ISurfaceTemplateCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ ISurfaceTemplate *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISurfaceTemplateCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISurfaceTemplateCollection * This,
            /* [in] */ ISurfaceTemplate *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ISurfaceTemplateCollection * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISurfaceTemplateCollection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBoundingTemplates )( 
            ISurfaceTemplateCollection * This,
            /* [in] */ VARIANT varStation,
            /* [out] */ ISurfaceTemplate **ppStart,
            /* [out] */ ISurfaceTemplate **ppEnd);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumSurfaceTemplates )( 
            ISurfaceTemplateCollection * This,
            /* [retval][out] */ IEnumSurfaceTemplates **retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISurfaceTemplateCollection * This,
            /* [retval][out] */ ISurfaceTemplateCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ISurfaceTemplateCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ISurfaceTemplateCollectionVtbl;

    interface ISurfaceTemplateCollection
    {
        CONST_VTBL struct ISurfaceTemplateCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurfaceTemplateCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurfaceTemplateCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurfaceTemplateCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurfaceTemplateCollection_get_Surface(This,pVal)	\
    ( (This)->lpVtbl -> get_Surface(This,pVal) ) 

#define ISurfaceTemplateCollection_putref_Surface(This,newVal)	\
    ( (This)->lpVtbl -> putref_Surface(This,newVal) ) 

#define ISurfaceTemplateCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ISurfaceTemplateCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define ISurfaceTemplateCollection_putref_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> putref_Item(This,idx,pVal) ) 

#define ISurfaceTemplateCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISurfaceTemplateCollection_Add(This,pVal)	\
    ( (This)->lpVtbl -> Add(This,pVal) ) 

#define ISurfaceTemplateCollection_Remove(This,idx)	\
    ( (This)->lpVtbl -> Remove(This,idx) ) 

#define ISurfaceTemplateCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ISurfaceTemplateCollection_GetBoundingTemplates(This,varStation,ppStart,ppEnd)	\
    ( (This)->lpVtbl -> GetBoundingTemplates(This,varStation,ppStart,ppEnd) ) 

#define ISurfaceTemplateCollection_get__EnumSurfaceTemplates(This,retval)	\
    ( (This)->lpVtbl -> get__EnumSurfaceTemplates(This,retval) ) 

#define ISurfaceTemplateCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISurfaceTemplateCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfaceTemplateCollection_INTERFACE_DEFINED__ */


#ifndef __ISurfaceTemplateCollectionEvents_INTERFACE_DEFINED__
#define __ISurfaceTemplateCollectionEvents_INTERFACE_DEFINED__

/* interface ISurfaceTemplateCollectionEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISurfaceTemplateCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32093DF8-B30F-4377-9EA0-2369B2ED7C23")
    ISurfaceTemplateCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSurfaceTemplateChanged( 
            /* [in] */ ISurfaceTemplate *pSurfaceTemplate) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSurfaceTemplateAdded( 
            /* [in] */ ISurfaceTemplate *pSurfaceTemplate) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSurfaceTemplateRemoved( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSurfaceTemplatesCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfaceTemplateCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurfaceTemplateCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurfaceTemplateCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurfaceTemplateCollectionEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSurfaceTemplateChanged )( 
            ISurfaceTemplateCollectionEvents * This,
            /* [in] */ ISurfaceTemplate *pSurfaceTemplate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSurfaceTemplateAdded )( 
            ISurfaceTemplateCollectionEvents * This,
            /* [in] */ ISurfaceTemplate *pSurfaceTemplate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSurfaceTemplateRemoved )( 
            ISurfaceTemplateCollectionEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSurfaceTemplatesCleared )( 
            ISurfaceTemplateCollectionEvents * This);
        
        END_INTERFACE
    } ISurfaceTemplateCollectionEventsVtbl;

    interface ISurfaceTemplateCollectionEvents
    {
        CONST_VTBL struct ISurfaceTemplateCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurfaceTemplateCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurfaceTemplateCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurfaceTemplateCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurfaceTemplateCollectionEvents_OnSurfaceTemplateChanged(This,pSurfaceTemplate)	\
    ( (This)->lpVtbl -> OnSurfaceTemplateChanged(This,pSurfaceTemplate) ) 

#define ISurfaceTemplateCollectionEvents_OnSurfaceTemplateAdded(This,pSurfaceTemplate)	\
    ( (This)->lpVtbl -> OnSurfaceTemplateAdded(This,pSurfaceTemplate) ) 

#define ISurfaceTemplateCollectionEvents_OnSurfaceTemplateRemoved(This)	\
    ( (This)->lpVtbl -> OnSurfaceTemplateRemoved(This) ) 

#define ISurfaceTemplateCollectionEvents_OnSurfaceTemplatesCleared(This)	\
    ( (This)->lpVtbl -> OnSurfaceTemplatesCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfaceTemplateCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __ISurfacePoint_INTERFACE_DEFINED__
#define __ISurfacePoint_INTERFACE_DEFINED__

/* interface ISurfacePoint */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISurfacePoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D4CD4F83-7F81-4ee9-B9AD-546E23014880")
    ISurfacePoint : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Surface( 
            /* [retval][out] */ ISurface **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Surface( 
            /* [in] */ ISurface *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Station( 
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Station( 
            /* [in] */ VARIANT varStation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NormalOffset( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_NormalOffset( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CutLineOffset( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CutLineOffset( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Elevation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Elevation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ IPoint2d **ppLocation) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ IPoint2d *ppLocation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPoint( 
            /* [retval][out] */ IPoint3d **ppPoint) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISurfacePoint **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfacePointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurfacePoint * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurfacePoint * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurfacePoint * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surface )( 
            ISurfacePoint * This,
            /* [retval][out] */ ISurface **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Surface )( 
            ISurfacePoint * This,
            /* [in] */ ISurface *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Station )( 
            ISurfacePoint * This,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Station )( 
            ISurfacePoint * This,
            /* [in] */ VARIANT varStation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NormalOffset )( 
            ISurfacePoint * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NormalOffset )( 
            ISurfacePoint * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CutLineOffset )( 
            ISurfacePoint * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CutLineOffset )( 
            ISurfacePoint * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Elevation )( 
            ISurfacePoint * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Elevation )( 
            ISurfacePoint * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            ISurfacePoint * This,
            /* [retval][out] */ IPoint2d **ppLocation);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Location )( 
            ISurfacePoint * This,
            /* [in] */ IPoint2d *ppLocation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPoint )( 
            ISurfacePoint * This,
            /* [retval][out] */ IPoint3d **ppPoint);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISurfacePoint * This,
            /* [retval][out] */ ISurfacePoint **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ISurfacePoint * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ISurfacePointVtbl;

    interface ISurfacePoint
    {
        CONST_VTBL struct ISurfacePointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurfacePoint_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurfacePoint_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurfacePoint_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurfacePoint_get_Surface(This,pVal)	\
    ( (This)->lpVtbl -> get_Surface(This,pVal) ) 

#define ISurfacePoint_putref_Surface(This,newVal)	\
    ( (This)->lpVtbl -> putref_Surface(This,newVal) ) 

#define ISurfacePoint_get_Station(This,station)	\
    ( (This)->lpVtbl -> get_Station(This,station) ) 

#define ISurfacePoint_put_Station(This,varStation)	\
    ( (This)->lpVtbl -> put_Station(This,varStation) ) 

#define ISurfacePoint_get_NormalOffset(This,pVal)	\
    ( (This)->lpVtbl -> get_NormalOffset(This,pVal) ) 

#define ISurfacePoint_put_NormalOffset(This,newVal)	\
    ( (This)->lpVtbl -> put_NormalOffset(This,newVal) ) 

#define ISurfacePoint_get_CutLineOffset(This,pVal)	\
    ( (This)->lpVtbl -> get_CutLineOffset(This,pVal) ) 

#define ISurfacePoint_put_CutLineOffset(This,newVal)	\
    ( (This)->lpVtbl -> put_CutLineOffset(This,newVal) ) 

#define ISurfacePoint_get_Elevation(This,pVal)	\
    ( (This)->lpVtbl -> get_Elevation(This,pVal) ) 

#define ISurfacePoint_put_Elevation(This,newVal)	\
    ( (This)->lpVtbl -> put_Elevation(This,newVal) ) 

#define ISurfacePoint_get_Location(This,ppLocation)	\
    ( (This)->lpVtbl -> get_Location(This,ppLocation) ) 

#define ISurfacePoint_put_Location(This,ppLocation)	\
    ( (This)->lpVtbl -> put_Location(This,ppLocation) ) 

#define ISurfacePoint_GetPoint(This,ppPoint)	\
    ( (This)->lpVtbl -> GetPoint(This,ppPoint) ) 

#define ISurfacePoint_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISurfacePoint_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfacePoint_INTERFACE_DEFINED__ */


#ifndef __ISurfaceProfile_INTERFACE_DEFINED__
#define __ISurfaceProfile_INTERFACE_DEFINED__

/* interface ISurfaceProfile */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISurfaceProfile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("677A9E7B-7CA1-47ef-95FF-EBB88CC2CA0A")
    ISurfaceProfile : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Surface( 
            /* [retval][out] */ ISurface **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Surface( 
            /* [in] */ ISurface *newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Station( 
            /* [in] */ VARIANT varStation) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Station( 
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Direction( 
            /* [in] */ VARIANT varDirection) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ IDirection **direction) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPoint( 
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 normalOffset,
            /* [in] */ Float64 cutLineOffset,
            /* [in] */ Float64 elev,
            /* [in] */ IPoint2d *pnt) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPointEx( 
            /* [in] */ ISurfacePoint *point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemovePoint( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISurfacePoint **point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRidgePointElevationChange( 
            /* [in] */ CollectionIndexType ridgePointIdx1,
            /* [in] */ CollectionIndexType ridgePointIdx2,
            /* [retval][out] */ Float64 *deltaElevation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetElevationChange( 
            /* [in] */ CollectionIndexType ridgePointIdx,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *deltaElevation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSlope( 
            /* [in] */ CollectionIndexType ridgePointIdx,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *pSlope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentSlope( 
            /* [in] */ CollectionIndexType segmentIdx,
            /* [retval][out] */ Float64 *pSlope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRidgePointOffset( 
            /* [in] */ IndexType ridgePointIdx,
            /* [out] */ Float64 *pOffset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRidgePointElevation( 
            /* [in] */ IndexType ridgePointIdx,
            /* [out] */ Float64 *pOffset,
            /* [out] */ Float64 *pElev) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISurfaceProfile **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfaceProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurfaceProfile * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurfaceProfile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurfaceProfile * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surface )( 
            ISurfaceProfile * This,
            /* [retval][out] */ ISurface **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Surface )( 
            ISurfaceProfile * This,
            /* [in] */ ISurface *newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Station )( 
            ISurfaceProfile * This,
            /* [in] */ VARIANT varStation);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Station )( 
            ISurfaceProfile * This,
            /* [retval][out] */ IStation **station);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Direction )( 
            ISurfaceProfile * This,
            /* [in] */ VARIANT varDirection);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Direction )( 
            ISurfaceProfile * This,
            /* [retval][out] */ IDirection **direction);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPoint )( 
            ISurfaceProfile * This,
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 normalOffset,
            /* [in] */ Float64 cutLineOffset,
            /* [in] */ Float64 elev,
            /* [in] */ IPoint2d *pnt);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPointEx )( 
            ISurfaceProfile * This,
            /* [in] */ ISurfacePoint *point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemovePoint )( 
            ISurfaceProfile * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISurfaceProfile * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISurfaceProfile * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISurfacePoint **point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRidgePointElevationChange )( 
            ISurfaceProfile * This,
            /* [in] */ CollectionIndexType ridgePointIdx1,
            /* [in] */ CollectionIndexType ridgePointIdx2,
            /* [retval][out] */ Float64 *deltaElevation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetElevationChange )( 
            ISurfaceProfile * This,
            /* [in] */ CollectionIndexType ridgePointIdx,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *deltaElevation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSlope )( 
            ISurfaceProfile * This,
            /* [in] */ CollectionIndexType ridgePointIdx,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *pSlope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentSlope )( 
            ISurfaceProfile * This,
            /* [in] */ CollectionIndexType segmentIdx,
            /* [retval][out] */ Float64 *pSlope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRidgePointOffset )( 
            ISurfaceProfile * This,
            /* [in] */ IndexType ridgePointIdx,
            /* [out] */ Float64 *pOffset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRidgePointElevation )( 
            ISurfaceProfile * This,
            /* [in] */ IndexType ridgePointIdx,
            /* [out] */ Float64 *pOffset,
            /* [out] */ Float64 *pElev);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISurfaceProfile * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISurfaceProfile * This,
            /* [retval][out] */ ISurfaceProfile **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ISurfaceProfile * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ISurfaceProfileVtbl;

    interface ISurfaceProfile
    {
        CONST_VTBL struct ISurfaceProfileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurfaceProfile_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurfaceProfile_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurfaceProfile_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurfaceProfile_get_Surface(This,pVal)	\
    ( (This)->lpVtbl -> get_Surface(This,pVal) ) 

#define ISurfaceProfile_putref_Surface(This,newVal)	\
    ( (This)->lpVtbl -> putref_Surface(This,newVal) ) 

#define ISurfaceProfile_put_Station(This,varStation)	\
    ( (This)->lpVtbl -> put_Station(This,varStation) ) 

#define ISurfaceProfile_get_Station(This,station)	\
    ( (This)->lpVtbl -> get_Station(This,station) ) 

#define ISurfaceProfile_put_Direction(This,varDirection)	\
    ( (This)->lpVtbl -> put_Direction(This,varDirection) ) 

#define ISurfaceProfile_get_Direction(This,direction)	\
    ( (This)->lpVtbl -> get_Direction(This,direction) ) 

#define ISurfaceProfile_AddPoint(This,varStation,normalOffset,cutLineOffset,elev,pnt)	\
    ( (This)->lpVtbl -> AddPoint(This,varStation,normalOffset,cutLineOffset,elev,pnt) ) 

#define ISurfaceProfile_AddPointEx(This,point)	\
    ( (This)->lpVtbl -> AddPointEx(This,point) ) 

#define ISurfaceProfile_RemovePoint(This,idx)	\
    ( (This)->lpVtbl -> RemovePoint(This,idx) ) 

#define ISurfaceProfile_get_Count(This,count)	\
    ( (This)->lpVtbl -> get_Count(This,count) ) 

#define ISurfaceProfile_get_Item(This,idx,point)	\
    ( (This)->lpVtbl -> get_Item(This,idx,point) ) 

#define ISurfaceProfile_GetRidgePointElevationChange(This,ridgePointIdx1,ridgePointIdx2,deltaElevation)	\
    ( (This)->lpVtbl -> GetRidgePointElevationChange(This,ridgePointIdx1,ridgePointIdx2,deltaElevation) ) 

#define ISurfaceProfile_GetElevationChange(This,ridgePointIdx,offset,deltaElevation)	\
    ( (This)->lpVtbl -> GetElevationChange(This,ridgePointIdx,offset,deltaElevation) ) 

#define ISurfaceProfile_GetSlope(This,ridgePointIdx,offset,pSlope)	\
    ( (This)->lpVtbl -> GetSlope(This,ridgePointIdx,offset,pSlope) ) 

#define ISurfaceProfile_GetSegmentSlope(This,segmentIdx,pSlope)	\
    ( (This)->lpVtbl -> GetSegmentSlope(This,segmentIdx,pSlope) ) 

#define ISurfaceProfile_GetRidgePointOffset(This,ridgePointIdx,pOffset)	\
    ( (This)->lpVtbl -> GetRidgePointOffset(This,ridgePointIdx,pOffset) ) 

#define ISurfaceProfile_GetRidgePointElevation(This,ridgePointIdx,pOffset,pElev)	\
    ( (This)->lpVtbl -> GetRidgePointElevation(This,ridgePointIdx,pOffset,pElev) ) 

#define ISurfaceProfile_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ISurfaceProfile_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISurfaceProfile_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfaceProfile_INTERFACE_DEFINED__ */


#ifndef __ISurface_INTERFACE_DEFINED__
#define __ISurface_INTERFACE_DEFINED__

/* interface ISurface */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISurface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07A3322F-F4C1-4635-9339-7B2954BB589D")
    ISurface : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IProfile **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Profile( 
            /* [in] */ IProfile *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ CogoObjectID *id) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ID( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SurfaceTemplates( 
            /* [retval][out] */ ISurfaceTemplateCollection **ppTemplates) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AlignmentPoint( 
            /* [in] */ IndexType pntIdx) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AlignmentPoint( 
            /* [retval][out] */ IndexType *pntIdx) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileGradePoint( 
            /* [in] */ IndexType pntIdx) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileGradePoint( 
            /* [retval][out] */ IndexType *pntIdx) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Superelevations( 
            /* [retval][out] */ ISuperelevationCollection **ppSuperelevations) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Widenings( 
            /* [retval][out] */ IWideningCollection **ppWidenings) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartBoundaryLine( 
            /* [in] */ ILineSegment2d **ppEndLine) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndBoundaryLine( 
            /* [in] */ ILineSegment2d **ppEndLine) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStationRange( 
            /* [out] */ IStation **ppStart,
            /* [out] */ IStation **ppEnd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateSurfaceTemplate( 
            /* [in] */ VARIANT varStation,
            /* [in] */ VARIANT_BOOL bApplySuperelevations,
            /* [retval][out] */ ISurfaceTemplate **ppSurfaceTemplate) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateSurfaceProfile( 
            /* [in] */ VARIANT varStation,
            /* [in] */ VARIANT varDirection,
            /* [in] */ VARIANT_BOOL bApplySuperelevations,
            /* [retval][out] */ ISurfaceProfile **ppSurfaceProfile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISurface **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurface * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            ISurface * This,
            /* [retval][out] */ IProfile **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Profile )( 
            ISurface * This,
            /* [in] */ IProfile *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            ISurface * This,
            /* [retval][out] */ CogoObjectID *id);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ID )( 
            ISurface * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SurfaceTemplates )( 
            ISurface * This,
            /* [retval][out] */ ISurfaceTemplateCollection **ppTemplates);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AlignmentPoint )( 
            ISurface * This,
            /* [in] */ IndexType pntIdx);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlignmentPoint )( 
            ISurface * This,
            /* [retval][out] */ IndexType *pntIdx);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProfileGradePoint )( 
            ISurface * This,
            /* [in] */ IndexType pntIdx);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfileGradePoint )( 
            ISurface * This,
            /* [retval][out] */ IndexType *pntIdx);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Superelevations )( 
            ISurface * This,
            /* [retval][out] */ ISuperelevationCollection **ppSuperelevations);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Widenings )( 
            ISurface * This,
            /* [retval][out] */ IWideningCollection **ppWidenings);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartBoundaryLine )( 
            ISurface * This,
            /* [in] */ ILineSegment2d **ppEndLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndBoundaryLine )( 
            ISurface * This,
            /* [in] */ ILineSegment2d **ppEndLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStationRange )( 
            ISurface * This,
            /* [out] */ IStation **ppStart,
            /* [out] */ IStation **ppEnd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSurfaceTemplate )( 
            ISurface * This,
            /* [in] */ VARIANT varStation,
            /* [in] */ VARIANT_BOOL bApplySuperelevations,
            /* [retval][out] */ ISurfaceTemplate **ppSurfaceTemplate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSurfaceProfile )( 
            ISurface * This,
            /* [in] */ VARIANT varStation,
            /* [in] */ VARIANT varDirection,
            /* [in] */ VARIANT_BOOL bApplySuperelevations,
            /* [retval][out] */ ISurfaceProfile **ppSurfaceProfile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISurface * This,
            /* [retval][out] */ ISurface **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ISurface * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ISurfaceVtbl;

    interface ISurface
    {
        CONST_VTBL struct ISurfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurface_get_Profile(This,pVal)	\
    ( (This)->lpVtbl -> get_Profile(This,pVal) ) 

#define ISurface_putref_Profile(This,newVal)	\
    ( (This)->lpVtbl -> putref_Profile(This,newVal) ) 

#define ISurface_get_ID(This,id)	\
    ( (This)->lpVtbl -> get_ID(This,id) ) 

#define ISurface_put_ID(This,id)	\
    ( (This)->lpVtbl -> put_ID(This,id) ) 

#define ISurface_get_SurfaceTemplates(This,ppTemplates)	\
    ( (This)->lpVtbl -> get_SurfaceTemplates(This,ppTemplates) ) 

#define ISurface_put_AlignmentPoint(This,pntIdx)	\
    ( (This)->lpVtbl -> put_AlignmentPoint(This,pntIdx) ) 

#define ISurface_get_AlignmentPoint(This,pntIdx)	\
    ( (This)->lpVtbl -> get_AlignmentPoint(This,pntIdx) ) 

#define ISurface_put_ProfileGradePoint(This,pntIdx)	\
    ( (This)->lpVtbl -> put_ProfileGradePoint(This,pntIdx) ) 

#define ISurface_get_ProfileGradePoint(This,pntIdx)	\
    ( (This)->lpVtbl -> get_ProfileGradePoint(This,pntIdx) ) 

#define ISurface_get_Superelevations(This,ppSuperelevations)	\
    ( (This)->lpVtbl -> get_Superelevations(This,ppSuperelevations) ) 

#define ISurface_get_Widenings(This,ppWidenings)	\
    ( (This)->lpVtbl -> get_Widenings(This,ppWidenings) ) 

#define ISurface_get_StartBoundaryLine(This,ppEndLine)	\
    ( (This)->lpVtbl -> get_StartBoundaryLine(This,ppEndLine) ) 

#define ISurface_get_EndBoundaryLine(This,ppEndLine)	\
    ( (This)->lpVtbl -> get_EndBoundaryLine(This,ppEndLine) ) 

#define ISurface_GetStationRange(This,ppStart,ppEnd)	\
    ( (This)->lpVtbl -> GetStationRange(This,ppStart,ppEnd) ) 

#define ISurface_CreateSurfaceTemplate(This,varStation,bApplySuperelevations,ppSurfaceTemplate)	\
    ( (This)->lpVtbl -> CreateSurfaceTemplate(This,varStation,bApplySuperelevations,ppSurfaceTemplate) ) 

#define ISurface_CreateSurfaceProfile(This,varStation,varDirection,bApplySuperelevations,ppSurfaceProfile)	\
    ( (This)->lpVtbl -> CreateSurfaceProfile(This,varStation,varDirection,bApplySuperelevations,ppSurfaceProfile) ) 

#define ISurface_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISurface_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurface_INTERFACE_DEFINED__ */


#ifndef __ISurfaceEvents_INTERFACE_DEFINED__
#define __ISurfaceEvents_INTERFACE_DEFINED__

/* interface ISurfaceEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISurfaceEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19B01B9A-E4F1-4c8c-A255-3234AFC13CFC")
    ISurfaceEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSurfaceChanged( 
            /* [in] */ ISurface *pSurface) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfaceEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurfaceEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurfaceEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurfaceEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSurfaceChanged )( 
            ISurfaceEvents * This,
            /* [in] */ ISurface *pSurface);
        
        END_INTERFACE
    } ISurfaceEventsVtbl;

    interface ISurfaceEvents
    {
        CONST_VTBL struct ISurfaceEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurfaceEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurfaceEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurfaceEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurfaceEvents_OnSurfaceChanged(This,pSurface)	\
    ( (This)->lpVtbl -> OnSurfaceChanged(This,pSurface) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfaceEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumSurfaces_INTERFACE_DEFINED__
#define __IEnumSurfaces_INTERFACE_DEFINED__

/* interface IEnumSurfaces */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSurfaces;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8395542A-0B80-4d6a-BA86-E3EDAA575798")
    IEnumSurfaces : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSurfaces **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISurface **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSurfacesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSurfaces * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSurfaces * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSurfaces * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSurfaces * This,
            /* [out] */ IEnumSurfaces **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSurfaces * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISurface **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSurfaces * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSurfaces * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSurfacesVtbl;

    interface IEnumSurfaces
    {
        CONST_VTBL struct IEnumSurfacesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSurfaces_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSurfaces_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSurfaces_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSurfaces_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSurfaces_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSurfaces_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSurfaces_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSurfaces_INTERFACE_DEFINED__ */


#ifndef __ISurfaceCollection_INTERFACE_DEFINED__
#define __ISurfaceCollection_INTERFACE_DEFINED__

/* interface ISurfaceCollection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISurfaceCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("44E00FE5-285A-45c2-9622-CB9E828234B7")
    ISurfaceCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IProfile **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Profile( 
            /* [in] */ IProfile *newVal) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISurface **pVal) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ ISurface *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ISurface *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindSurface( 
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ ISurface **ppSurface) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSurface( 
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ ISurface **ppSurface) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumSurfaces( 
            /* [retval][out] */ IEnumSurfaces **retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISurfaceCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfaceCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurfaceCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurfaceCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurfaceCollection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            ISurfaceCollection * This,
            /* [retval][out] */ IProfile **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Profile )( 
            ISurfaceCollection * This,
            /* [in] */ IProfile *newVal);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISurfaceCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISurfaceCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ISurface **pVal);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            ISurfaceCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ ISurface *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISurfaceCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISurfaceCollection * This,
            /* [in] */ ISurface *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ISurfaceCollection * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISurfaceCollection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindSurface )( 
            ISurfaceCollection * This,
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ ISurface **ppSurface);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSurface )( 
            ISurfaceCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ ISurface **ppSurface);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumSurfaces )( 
            ISurfaceCollection * This,
            /* [retval][out] */ IEnumSurfaces **retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISurfaceCollection * This,
            /* [retval][out] */ ISurfaceCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ISurfaceCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ISurfaceCollectionVtbl;

    interface ISurfaceCollection
    {
        CONST_VTBL struct ISurfaceCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurfaceCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurfaceCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurfaceCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurfaceCollection_get_Profile(This,pVal)	\
    ( (This)->lpVtbl -> get_Profile(This,pVal) ) 

#define ISurfaceCollection_putref_Profile(This,newVal)	\
    ( (This)->lpVtbl -> putref_Profile(This,newVal) ) 

#define ISurfaceCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ISurfaceCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define ISurfaceCollection_putref_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> putref_Item(This,idx,pVal) ) 

#define ISurfaceCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISurfaceCollection_Add(This,pVal)	\
    ( (This)->lpVtbl -> Add(This,pVal) ) 

#define ISurfaceCollection_Remove(This,idx)	\
    ( (This)->lpVtbl -> Remove(This,idx) ) 

#define ISurfaceCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ISurfaceCollection_FindSurface(This,id,ppSurface)	\
    ( (This)->lpVtbl -> FindSurface(This,id,ppSurface) ) 

#define ISurfaceCollection_GetSurface(This,id,varStation,ppSurface)	\
    ( (This)->lpVtbl -> GetSurface(This,id,varStation,ppSurface) ) 

#define ISurfaceCollection_get__EnumSurfaces(This,retval)	\
    ( (This)->lpVtbl -> get__EnumSurfaces(This,retval) ) 

#define ISurfaceCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISurfaceCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfaceCollection_INTERFACE_DEFINED__ */


#ifndef __ISurfaceCollectionEvents_INTERFACE_DEFINED__
#define __ISurfaceCollectionEvents_INTERFACE_DEFINED__

/* interface ISurfaceCollectionEvents */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISurfaceCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86CE6349-FF88-482f-91A6-E0BDC9D5B22A")
    ISurfaceCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSurfaceChanged( 
            /* [in] */ ISurface *pSurface) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSurfaceAdded( 
            /* [in] */ ISurface *pSurface) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSurfaceRemoved( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSurfacesCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISurfaceCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurfaceCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurfaceCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurfaceCollectionEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSurfaceChanged )( 
            ISurfaceCollectionEvents * This,
            /* [in] */ ISurface *pSurface);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSurfaceAdded )( 
            ISurfaceCollectionEvents * This,
            /* [in] */ ISurface *pSurface);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSurfaceRemoved )( 
            ISurfaceCollectionEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSurfacesCleared )( 
            ISurfaceCollectionEvents * This);
        
        END_INTERFACE
    } ISurfaceCollectionEventsVtbl;

    interface ISurfaceCollectionEvents
    {
        CONST_VTBL struct ISurfaceCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurfaceCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISurfaceCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISurfaceCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISurfaceCollectionEvents_OnSurfaceChanged(This,pSurface)	\
    ( (This)->lpVtbl -> OnSurfaceChanged(This,pSurface) ) 

#define ISurfaceCollectionEvents_OnSurfaceAdded(This,pSurface)	\
    ( (This)->lpVtbl -> OnSurfaceAdded(This,pSurface) ) 

#define ISurfaceCollectionEvents_OnSurfaceRemoved(This)	\
    ( (This)->lpVtbl -> OnSurfaceRemoved(This) ) 

#define ISurfaceCollectionEvents_OnSurfacesCleared(This)	\
    ( (This)->lpVtbl -> OnSurfacesCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfaceCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __IProfileElement_INTERFACE_DEFINED__
#define __IProfileElement_INTERFACE_DEFINED__

/* interface IProfileElement */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProfileElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("885D3FAE-E15A-4BF0-AAD0-8622700D4250")
    IProfileElement : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ IUnknown **dispVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Value( 
            /* [in] */ IUnknown *dispVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ ProfileElementType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IProfileElement **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProfileElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProfileElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProfileElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProfileElement * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IProfileElement * This,
            /* [retval][out] */ IUnknown **dispVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Value )( 
            IProfileElement * This,
            /* [in] */ IUnknown *dispVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IProfileElement * This,
            /* [retval][out] */ ProfileElementType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IProfileElement * This,
            /* [retval][out] */ IProfileElement **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IProfileElement * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IProfileElementVtbl;

    interface IProfileElement
    {
        CONST_VTBL struct IProfileElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProfileElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProfileElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProfileElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProfileElement_get_Value(This,dispVal)	\
    ( (This)->lpVtbl -> get_Value(This,dispVal) ) 

#define IProfileElement_putref_Value(This,dispVal)	\
    ( (This)->lpVtbl -> putref_Value(This,dispVal) ) 

#define IProfileElement_get_Type(This,pVal)	\
    ( (This)->lpVtbl -> get_Type(This,pVal) ) 

#define IProfileElement_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IProfileElement_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProfileElement_INTERFACE_DEFINED__ */


#ifndef __IProfileElementEvents_INTERFACE_DEFINED__
#define __IProfileElementEvents_INTERFACE_DEFINED__

/* interface IProfileElementEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProfileElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EEB5D577-DAAE-4a84-9010-67820CF18AE7")
    IProfileElementEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfileElementChanged( 
            /* [in] */ IProfileElement *pe) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProfileElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProfileElementEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProfileElementEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProfileElementEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfileElementChanged )( 
            IProfileElementEvents * This,
            /* [in] */ IProfileElement *pe);
        
        END_INTERFACE
    } IProfileElementEventsVtbl;

    interface IProfileElementEvents
    {
        CONST_VTBL struct IProfileElementEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProfileElementEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProfileElementEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProfileElementEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProfileElementEvents_OnProfileElementChanged(This,pe)	\
    ( (This)->lpVtbl -> OnProfileElementChanged(This,pe) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProfileElementEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumProfileElements_INTERFACE_DEFINED__
#define __IEnumProfileElements_INTERFACE_DEFINED__

/* interface IEnumProfileElements */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumProfileElements;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E570BCE7-4608-4279-8F25-4222F5B304E4")
    IEnumProfileElements : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumProfileElements **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IProfileElement **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumProfileElementsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumProfileElements * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumProfileElements * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumProfileElements * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumProfileElements * This,
            /* [out] */ IEnumProfileElements **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumProfileElements * This,
            /* [in] */ ULONG celt,
            /* [out] */ IProfileElement **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumProfileElements * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumProfileElements * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumProfileElementsVtbl;

    interface IEnumProfileElements
    {
        CONST_VTBL struct IEnumProfileElementsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumProfileElements_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumProfileElements_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumProfileElements_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumProfileElements_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumProfileElements_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumProfileElements_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumProfileElements_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumProfileElements_INTERFACE_DEFINED__ */


#ifndef __IProfile_INTERFACE_DEFINED__
#define __IProfile_INTERFACE_DEFINED__

/* interface IProfile */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProfile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("33CC0CE8-3BF5-4E27-A483-8EA6B4A2327B")
    IProfile : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Alignment( 
            /* [retval][out] */ IAlignment **ppAlignment) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Surfaces( 
            /* [retval][out] */ ISurfaceCollection **ppSurfaces) = 0;
        
        virtual /* [helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Surfaces( 
            /* [in] */ ISurfaceCollection *pSurfaces) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IProfileElement **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IProfileElement *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IProfileElement *element) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ IUnknown *dispElement) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT varID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Elevation( 
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *elev) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Grade( 
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ Float64 *grade) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Slope( 
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *slope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TemplateSegmentSlope( 
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [in] */ CollectionIndexType templateSegmentIdx,
            /* [retval][out] */ Float64 *pSlope) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSurface( 
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ ISurface **ppSurface) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RidgePointOffset( 
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [in] */ IndexType ridgePointIdx,
            /* [in] */ IndexType refPointIdx,
            /* [out] */ Float64 *pOffset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RidgePointElevation( 
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [in] */ IndexType ridgePointIdx,
            /* [in] */ IndexType refPointIdx,
            /* [out] */ Float64 *pOffset,
            /* [out] */ Float64 *pElev) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumProfileElements( 
            /* [retval][out] */ IEnumProfileElements **retval) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IProfile **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProfile * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProfile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProfile * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alignment )( 
            IProfile * This,
            /* [retval][out] */ IAlignment **ppAlignment);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Surfaces )( 
            IProfile * This,
            /* [retval][out] */ ISurfaceCollection **ppSurfaces);
        
        /* [helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Surfaces )( 
            IProfile * This,
            /* [in] */ ISurfaceCollection *pSurfaces);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IProfile * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IProfile * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IProfileElement **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IProfile * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IProfileElement *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IProfile * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IProfile * This,
            /* [in] */ IProfileElement *element);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            IProfile * This,
            /* [in] */ IUnknown *dispElement);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IProfile * This,
            /* [in] */ VARIANT varID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IProfile * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Elevation )( 
            IProfile * This,
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *elev);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Grade )( 
            IProfile * This,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ Float64 *grade);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Slope )( 
            IProfile * This,
            /* [in] */ VARIANT varStation,
            /* [in] */ Float64 offset,
            /* [retval][out] */ Float64 *slope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TemplateSegmentSlope )( 
            IProfile * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [in] */ CollectionIndexType templateSegmentIdx,
            /* [retval][out] */ Float64 *pSlope);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSurface )( 
            IProfile * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ ISurface **ppSurface);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RidgePointOffset )( 
            IProfile * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [in] */ IndexType ridgePointIdx,
            /* [in] */ IndexType refPointIdx,
            /* [out] */ Float64 *pOffset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RidgePointElevation )( 
            IProfile * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ VARIANT varStation,
            /* [in] */ IndexType ridgePointIdx,
            /* [in] */ IndexType refPointIdx,
            /* [out] */ Float64 *pOffset,
            /* [out] */ Float64 *pElev);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumProfileElements )( 
            IProfile * This,
            /* [retval][out] */ IEnumProfileElements **retval);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IProfile * This,
            /* [retval][out] */ IProfile **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IProfile * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IProfileVtbl;

    interface IProfile
    {
        CONST_VTBL struct IProfileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProfile_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProfile_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProfile_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProfile_get_Alignment(This,ppAlignment)	\
    ( (This)->lpVtbl -> get_Alignment(This,ppAlignment) ) 

#define IProfile_get_Surfaces(This,ppSurfaces)	\
    ( (This)->lpVtbl -> get_Surfaces(This,ppSurfaces) ) 

#define IProfile_putref_Surfaces(This,pSurfaces)	\
    ( (This)->lpVtbl -> putref_Surfaces(This,pSurfaces) ) 

#define IProfile_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IProfile_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IProfile_putref_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> putref_Item(This,idx,pVal) ) 

#define IProfile_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IProfile_Add(This,element)	\
    ( (This)->lpVtbl -> Add(This,element) ) 

#define IProfile_AddEx(This,dispElement)	\
    ( (This)->lpVtbl -> AddEx(This,dispElement) ) 

#define IProfile_Remove(This,varID)	\
    ( (This)->lpVtbl -> Remove(This,varID) ) 

#define IProfile_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IProfile_Elevation(This,varStation,offset,elev)	\
    ( (This)->lpVtbl -> Elevation(This,varStation,offset,elev) ) 

#define IProfile_Grade(This,varStation,grade)	\
    ( (This)->lpVtbl -> Grade(This,varStation,grade) ) 

#define IProfile_Slope(This,varStation,offset,slope)	\
    ( (This)->lpVtbl -> Slope(This,varStation,offset,slope) ) 

#define IProfile_TemplateSegmentSlope(This,id,varStation,templateSegmentIdx,pSlope)	\
    ( (This)->lpVtbl -> TemplateSegmentSlope(This,id,varStation,templateSegmentIdx,pSlope) ) 

#define IProfile_GetSurface(This,id,varStation,ppSurface)	\
    ( (This)->lpVtbl -> GetSurface(This,id,varStation,ppSurface) ) 

#define IProfile_RidgePointOffset(This,id,varStation,ridgePointIdx,refPointIdx,pOffset)	\
    ( (This)->lpVtbl -> RidgePointOffset(This,id,varStation,ridgePointIdx,refPointIdx,pOffset) ) 

#define IProfile_RidgePointElevation(This,id,varStation,ridgePointIdx,refPointIdx,pOffset,pElev)	\
    ( (This)->lpVtbl -> RidgePointElevation(This,id,varStation,ridgePointIdx,refPointIdx,pOffset,pElev) ) 

#define IProfile_get__EnumProfileElements(This,retval)	\
    ( (This)->lpVtbl -> get__EnumProfileElements(This,retval) ) 

#define IProfile_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IProfile_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProfile_INTERFACE_DEFINED__ */


#ifndef __IProfileEvents_INTERFACE_DEFINED__
#define __IProfileEvents_INTERFACE_DEFINED__

/* interface IProfileEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProfileEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0185AF42-F10A-4b4d-AB0E-58275D72E131")
    IProfileEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfileChanged( 
            /* [in] */ IProfile *profile) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProfileEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProfileEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProfileEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProfileEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfileChanged )( 
            IProfileEvents * This,
            /* [in] */ IProfile *profile);
        
        END_INTERFACE
    } IProfileEventsVtbl;

    interface IProfileEvents
    {
        CONST_VTBL struct IProfileEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProfileEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProfileEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProfileEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProfileEvents_OnProfileChanged(This,profile)	\
    ( (This)->lpVtbl -> OnProfileChanged(This,profile) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProfileEvents_INTERFACE_DEFINED__ */


#ifndef __IPathElement_INTERFACE_DEFINED__
#define __IPathElement_INTERFACE_DEFINED__

/* interface IPathElement */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPathElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("60F5D239-6851-41B6-AD37-7CBA6BB9D78A")
    IPathElement : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ PathElementType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Value( 
            /* [in] */ IUnknown *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPathElement **clone) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ Float64 dist,
            /* [in] */ IDirection *direction) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPathElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPathElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPathElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPathElement * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IPathElement * This,
            /* [retval][out] */ PathElementType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IPathElement * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Value )( 
            IPathElement * This,
            /* [in] */ IUnknown *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPathElement * This,
            /* [retval][out] */ IPathElement **clone);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IPathElement * This,
            /* [in] */ Float64 dist,
            /* [in] */ IDirection *direction);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IPathElement * This,
            /* [in] */ Float64 dx,
            /* [in] */ Float64 dy);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPathElement * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IPathElementVtbl;

    interface IPathElement
    {
        CONST_VTBL struct IPathElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPathElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPathElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPathElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPathElement_get_Type(This,pVal)	\
    ( (This)->lpVtbl -> get_Type(This,pVal) ) 

#define IPathElement_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define IPathElement_putref_Value(This,newVal)	\
    ( (This)->lpVtbl -> putref_Value(This,newVal) ) 

#define IPathElement_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IPathElement_Move(This,dist,direction)	\
    ( (This)->lpVtbl -> Move(This,dist,direction) ) 

#define IPathElement_Offset(This,dx,dy)	\
    ( (This)->lpVtbl -> Offset(This,dx,dy) ) 

#define IPathElement_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPathElement_INTERFACE_DEFINED__ */


#ifndef __IPathElementEvents_INTERFACE_DEFINED__
#define __IPathElementEvents_INTERFACE_DEFINED__

/* interface IPathElementEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPathElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6C8D62A8-6E1C-4c94-BD54-F3CDFA9E7B27")
    IPathElementEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPathElementChanged( 
            /* [in] */ IPathElement *element) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPathElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPathElementEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPathElementEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPathElementEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPathElementChanged )( 
            IPathElementEvents * This,
            /* [in] */ IPathElement *element);
        
        END_INTERFACE
    } IPathElementEventsVtbl;

    interface IPathElementEvents
    {
        CONST_VTBL struct IPathElementEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPathElementEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPathElementEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPathElementEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPathElementEvents_OnPathElementChanged(This,element)	\
    ( (This)->lpVtbl -> OnPathElementChanged(This,element) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPathElementEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumPathElements_INTERFACE_DEFINED__
#define __IEnumPathElements_INTERFACE_DEFINED__

/* interface IEnumPathElements */
/* [unique][restricted][hidden][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumPathElements;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BD543403-0846-4502-841F-1904DC1F1144")
    IEnumPathElements : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPathElements **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IPathElement **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumPathElementsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPathElements * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPathElements * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPathElements * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPathElements * This,
            /* [out] */ IEnumPathElements **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPathElements * This,
            /* [in] */ ULONG celt,
            /* [out] */ IPathElement **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPathElements * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPathElements * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumPathElementsVtbl;

    interface IEnumPathElements
    {
        CONST_VTBL struct IEnumPathElementsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPathElements_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumPathElements_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumPathElements_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumPathElements_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumPathElements_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumPathElements_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumPathElements_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumPathElements_INTERFACE_DEFINED__ */


#ifndef __IPath_INTERFACE_DEFINED__
#define __IPath_INTERFACE_DEFINED__

/* interface IPath */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPath;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A43DACE9-956A-4421-9A3A-01D2453FCE03")
    IPath : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IPathElement **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPathElement *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IPathElement *element) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ IUnknown *dispElement) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPathElement *element) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE InsertEx( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IUnknown *dispElement) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT varID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LocatePoint( 
            /* [in] */ Float64 distance,
            /* [in] */ OffsetMeasureType offsetMeasure,
            /* [in] */ Float64 offset,
            /* [in] */ VARIANT varDir,
            /* [retval][out] */ IPoint2d **newPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Bearing( 
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **dir) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Normal( 
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **dir) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ProjectPoint( 
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ IPoint2d **newPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ IPoint2d *point,
            /* [out] */ Float64 *distance,
            /* [out] */ Float64 *offset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Intersect( 
            /* [in] */ ILine2d *line,
            /* [in] */ IPoint2d *pNearest,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IntersectEx( 
            /* [in] */ ILine2d *line,
            /* [in] */ IPoint2d *pNearest,
            /* [in] */ VARIANT_BOOL vbProjectBack,
            /* [in] */ VARIANT_BOOL vbProjectAhead,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PointFactory( 
            /* [retval][out] */ IPoint2dFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PointFactory( 
            /* [in] */ IPoint2dFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumPathElements( 
            /* [retval][out] */ IEnumPathElements **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPath **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateParallelPath( 
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPath **path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateSubPath( 
            /* [in] */ Float64 start,
            /* [in] */ Float64 end,
            /* [retval][out] */ IPath **path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateConnectedPath( 
            /* [retval][out] */ IPath **path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ Float64 dist,
            /* [in] */ IDirection *direction) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPathVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPath * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPath * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPath * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IPath * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPath * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IPathElement **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IPath * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPathElement *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPath * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPath * This,
            /* [in] */ IPathElement *element);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            IPath * This,
            /* [in] */ IUnknown *dispElement);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IPath * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPathElement *element);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *InsertEx )( 
            IPath * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IUnknown *dispElement);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IPath * This,
            /* [in] */ VARIANT varID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IPath * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LocatePoint )( 
            IPath * This,
            /* [in] */ Float64 distance,
            /* [in] */ OffsetMeasureType offsetMeasure,
            /* [in] */ Float64 offset,
            /* [in] */ VARIANT varDir,
            /* [retval][out] */ IPoint2d **newPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Bearing )( 
            IPath * This,
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **dir);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Normal )( 
            IPath * This,
            /* [in] */ Float64 distance,
            /* [retval][out] */ IDirection **dir);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectPoint )( 
            IPath * This,
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ IPoint2d **newPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IPath * This,
            /* [in] */ IPoint2d *point,
            /* [out] */ Float64 *distance,
            /* [out] */ Float64 *offset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Intersect )( 
            IPath * This,
            /* [in] */ ILine2d *line,
            /* [in] */ IPoint2d *pNearest,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IntersectEx )( 
            IPath * This,
            /* [in] */ ILine2d *line,
            /* [in] */ IPoint2d *pNearest,
            /* [in] */ VARIANT_BOOL vbProjectBack,
            /* [in] */ VARIANT_BOOL vbProjectAhead,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IPath * This,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointFactory )( 
            IPath * This,
            /* [retval][out] */ IPoint2dFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PointFactory )( 
            IPath * This,
            /* [in] */ IPoint2dFactory *factory);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumPathElements )( 
            IPath * This,
            /* [retval][out] */ IEnumPathElements **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPath * This,
            /* [retval][out] */ IPath **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateParallelPath )( 
            IPath * This,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPath **path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSubPath )( 
            IPath * This,
            /* [in] */ Float64 start,
            /* [in] */ Float64 end,
            /* [retval][out] */ IPath **path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateConnectedPath )( 
            IPath * This,
            /* [retval][out] */ IPath **path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IPath * This,
            /* [in] */ Float64 dist,
            /* [in] */ IDirection *direction);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPath * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IPathVtbl;

    interface IPath
    {
        CONST_VTBL struct IPathVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPath_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPath_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPath_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPath_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IPath_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IPath_putref_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> putref_Item(This,idx,pVal) ) 

#define IPath_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPath_Add(This,element)	\
    ( (This)->lpVtbl -> Add(This,element) ) 

#define IPath_AddEx(This,dispElement)	\
    ( (This)->lpVtbl -> AddEx(This,dispElement) ) 

#define IPath_Insert(This,idx,element)	\
    ( (This)->lpVtbl -> Insert(This,idx,element) ) 

#define IPath_InsertEx(This,idx,dispElement)	\
    ( (This)->lpVtbl -> InsertEx(This,idx,dispElement) ) 

#define IPath_Remove(This,varID)	\
    ( (This)->lpVtbl -> Remove(This,varID) ) 

#define IPath_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IPath_LocatePoint(This,distance,offsetMeasure,offset,varDir,newPoint)	\
    ( (This)->lpVtbl -> LocatePoint(This,distance,offsetMeasure,offset,varDir,newPoint) ) 

#define IPath_Bearing(This,distance,dir)	\
    ( (This)->lpVtbl -> Bearing(This,distance,dir) ) 

#define IPath_Normal(This,distance,dir)	\
    ( (This)->lpVtbl -> Normal(This,distance,dir) ) 

#define IPath_ProjectPoint(This,point,newPoint)	\
    ( (This)->lpVtbl -> ProjectPoint(This,point,newPoint) ) 

#define IPath_Offset(This,point,distance,offset)	\
    ( (This)->lpVtbl -> Offset(This,point,distance,offset) ) 

#define IPath_Intersect(This,line,pNearest,point)	\
    ( (This)->lpVtbl -> Intersect(This,line,pNearest,point) ) 

#define IPath_IntersectEx(This,line,pNearest,vbProjectBack,vbProjectAhead,point)	\
    ( (This)->lpVtbl -> IntersectEx(This,line,pNearest,vbProjectBack,vbProjectAhead,point) ) 

#define IPath_get_Length(This,pLength)	\
    ( (This)->lpVtbl -> get_Length(This,pLength) ) 

#define IPath_get_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> get_PointFactory(This,factory) ) 

#define IPath_putref_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_PointFactory(This,factory) ) 

#define IPath_get__EnumPathElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumPathElements(This,pVal) ) 

#define IPath_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IPath_CreateParallelPath(This,offset,path)	\
    ( (This)->lpVtbl -> CreateParallelPath(This,offset,path) ) 

#define IPath_CreateSubPath(This,start,end,path)	\
    ( (This)->lpVtbl -> CreateSubPath(This,start,end,path) ) 

#define IPath_CreateConnectedPath(This,path)	\
    ( (This)->lpVtbl -> CreateConnectedPath(This,path) ) 

#define IPath_Move(This,dist,direction)	\
    ( (This)->lpVtbl -> Move(This,dist,direction) ) 

#define IPath_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPath_INTERFACE_DEFINED__ */


#ifndef __IPathEvents_INTERFACE_DEFINED__
#define __IPathEvents_INTERFACE_DEFINED__

/* interface IPathEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPathEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BC341CD7-1B43-4f73-9975-93B02DD949F2")
    IPathEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPathChanged( 
            /* [in] */ IPath *path) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPathEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPathEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPathEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPathEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPathChanged )( 
            IPathEvents * This,
            /* [in] */ IPath *path);
        
        END_INTERFACE
    } IPathEventsVtbl;

    interface IPathEvents
    {
        CONST_VTBL struct IPathEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPathEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPathEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPathEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPathEvents_OnPathChanged(This,path)	\
    ( (This)->lpVtbl -> OnPathChanged(This,path) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPathEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumPaths_INTERFACE_DEFINED__
#define __IEnumPaths_INTERFACE_DEFINED__

/* interface IEnumPaths */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumPaths;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D5BECD44-9730-4bf4-80B2-8B983C21E110")
    IEnumPaths : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPaths **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IPath **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumPathsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPaths * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPaths * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPaths * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPaths * This,
            /* [out] */ IEnumPaths **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPaths * This,
            /* [in] */ ULONG celt,
            /* [out] */ IPath **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPaths * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPaths * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumPathsVtbl;

    interface IEnumPaths
    {
        CONST_VTBL struct IEnumPathsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPaths_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumPaths_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumPaths_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumPaths_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumPaths_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumPaths_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumPaths_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumPaths_INTERFACE_DEFINED__ */


#ifndef __IPathFactory_INTERFACE_DEFINED__
#define __IPathFactory_INTERFACE_DEFINED__

/* interface IPathFactory */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPathFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("97990706-8447-459c-A05B-74540273CBE3")
    IPathFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreatePath( 
            /* [retval][out] */ IPath **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IsValidType( 
            /* [in] */ IPath *path,
            /* [retval][out] */ VARIANT_BOOL *bIsValid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPathFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPathFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPathFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPathFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatePath )( 
            IPathFactory * This,
            /* [retval][out] */ IPath **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsValidType )( 
            IPathFactory * This,
            /* [in] */ IPath *path,
            /* [retval][out] */ VARIANT_BOOL *bIsValid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPathFactory * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IPathFactoryVtbl;

    interface IPathFactory
    {
        CONST_VTBL struct IPathFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPathFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPathFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPathFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPathFactory_CreatePath(This,pVal)	\
    ( (This)->lpVtbl -> CreatePath(This,pVal) ) 

#define IPathFactory_IsValidType(This,path,bIsValid)	\
    ( (This)->lpVtbl -> IsValidType(This,path,bIsValid) ) 

#define IPathFactory_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPathFactory_INTERFACE_DEFINED__ */


#ifndef __IPathCollection_INTERFACE_DEFINED__
#define __IPathCollection_INTERFACE_DEFINED__

/* interface IPathCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPathCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DFDF1C35-39DB-4285-AA38-BE6C189E29E0")
    IPathCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IPath **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IPath **path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FindID( 
            /* [in] */ IPath *path,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumIDs( 
            /* [retval][out] */ IEnumIDs **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Factory( 
            /* [retval][out] */ IPathFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Factory( 
            /* [in] */ IPathFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ID( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumPaths( 
            /* [retval][out] */ IEnumPaths **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPathCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPathCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPathCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPathCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPathCollection * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IPathCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPathCollection * This,
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IPath **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IPathCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPathCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPathCollection * This,
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IPath **path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            IPathCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IPathCollection * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IPathCollection * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindID )( 
            IPathCollection * This,
            /* [in] */ IPath *path,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumIDs )( 
            IPathCollection * This,
            /* [retval][out] */ IEnumIDs **ppenum);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Factory )( 
            IPathCollection * This,
            /* [retval][out] */ IPathFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Factory )( 
            IPathCollection * This,
            /* [in] */ IPathFactory *factory);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ID )( 
            IPathCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumPaths )( 
            IPathCollection * This,
            /* [retval][out] */ IEnumPaths **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPathCollection * This,
            /* [retval][out] */ IPathCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IPathCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IPathCollectionVtbl;

    interface IPathCollection
    {
        CONST_VTBL struct IPathCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPathCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPathCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPathCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPathCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IPathCollection_get_Item(This,id,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,id,pVal) ) 

#define IPathCollection_putref_Item(This,id,pVal)	\
    ( (This)->lpVtbl -> putref_Item(This,id,pVal) ) 

#define IPathCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPathCollection_Add(This,id,path)	\
    ( (This)->lpVtbl -> Add(This,id,path) ) 

#define IPathCollection_AddEx(This,id,newVal)	\
    ( (This)->lpVtbl -> AddEx(This,id,newVal) ) 

#define IPathCollection_Remove(This,id)	\
    ( (This)->lpVtbl -> Remove(This,id) ) 

#define IPathCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IPathCollection_FindID(This,path,ID)	\
    ( (This)->lpVtbl -> FindID(This,path,ID) ) 

#define IPathCollection_get__EnumIDs(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumIDs(This,ppenum) ) 

#define IPathCollection_get_Factory(This,factory)	\
    ( (This)->lpVtbl -> get_Factory(This,factory) ) 

#define IPathCollection_putref_Factory(This,factory)	\
    ( (This)->lpVtbl -> putref_Factory(This,factory) ) 

#define IPathCollection_ID(This,index,ID)	\
    ( (This)->lpVtbl -> ID(This,index,ID) ) 

#define IPathCollection_get__EnumPaths(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumPaths(This,ppenum) ) 

#define IPathCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IPathCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPathCollection_INTERFACE_DEFINED__ */


#ifndef __IPathCollectionEvents_INTERFACE_DEFINED__
#define __IPathCollectionEvents_INTERFACE_DEFINED__

/* interface IPathCollectionEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPathCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("176DAD7B-1209-47ad-9AC7-8901C6AEC89A")
    IPathCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPathChanged( 
            /* [in] */ IPathCollection *coll,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPathAdded( 
            /* [in] */ IPathCollection *coll,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPathRemoved( 
            /* [in] */ IPathCollection *coll,
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPathsCleared( 
            /* [in] */ IPathCollection *coll) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPathCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPathCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPathCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPathCollectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPathChanged )( 
            IPathCollectionEvents * This,
            /* [in] */ IPathCollection *coll,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPathAdded )( 
            IPathCollectionEvents * This,
            /* [in] */ IPathCollection *coll,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPathRemoved )( 
            IPathCollectionEvents * This,
            /* [in] */ IPathCollection *coll,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPathsCleared )( 
            IPathCollectionEvents * This,
            /* [in] */ IPathCollection *coll);
        
        END_INTERFACE
    } IPathCollectionEventsVtbl;

    interface IPathCollectionEvents
    {
        CONST_VTBL struct IPathCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPathCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPathCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPathCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPathCollectionEvents_OnPathChanged(This,coll,id,path)	\
    ( (This)->lpVtbl -> OnPathChanged(This,coll,id,path) ) 

#define IPathCollectionEvents_OnPathAdded(This,coll,id,path)	\
    ( (This)->lpVtbl -> OnPathAdded(This,coll,id,path) ) 

#define IPathCollectionEvents_OnPathRemoved(This,coll,id)	\
    ( (This)->lpVtbl -> OnPathRemoved(This,coll,id) ) 

#define IPathCollectionEvents_OnPathsCleared(This,coll)	\
    ( (This)->lpVtbl -> OnPathsCleared(This,coll) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPathCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __IAlignment_INTERFACE_DEFINED__
#define __IAlignment_INTERFACE_DEFINED__

/* interface IAlignment */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAlignment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("30638CFA-0F23-4784-8FC9-D1A2E4A50F02")
    IAlignment : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IPathElement **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPathElement *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RefStation( 
            /* [retval][out] */ IStation **station) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RefStation( 
            /* [in] */ VARIANT varStation) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ IProfile **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StationEquations( 
            /* [retval][out] */ IStationEquationCollection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IPathElement *element) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ IUnknown *dispElement) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPathElement *element) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE InsertEx( 
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IUnknown *dispElement) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT varID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LocatePoint( 
            /* [in] */ VARIANT varStation,
            /* [in] */ OffsetMeasureType offsetMeasure,
            /* [in] */ Float64 offset,
            /* [in] */ VARIANT varDir,
            /* [retval][out] */ IPoint2d **newPoint) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Bearing( 
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ IDirection **dir) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Normal( 
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ IDirection **dir) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Offset( 
            /* [in] */ IPoint2d *point,
            /* [out] */ IStation **station,
            /* [out] */ Float64 *offset) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ProjectPoint( 
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ IPoint2d **newPoint) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Intersect( 
            /* [in] */ ILine2d *line,
            /* [in] */ IPoint2d *pNearest,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IntersectEx( 
            /* [in] */ ILine2d *line,
            /* [in] */ IPoint2d *pNearest,
            /* [in] */ VARIANT_BOOL vbProjectBack,
            /* [in] */ VARIANT_BOOL vbProjectAhead,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PointFactory( 
            /* [retval][out] */ IPoint2dFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PointFactory( 
            /* [in] */ IPoint2dFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumAlignmentElements( 
            /* [retval][out] */ IEnumPathElements **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IAlignment **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateParallelAlignment( 
            /* [in] */ Float64 offset,
            /* [retval][out] */ IAlignment **alignment) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateSubAlignment( 
            /* [in] */ VARIANT varStartStation,
            /* [in] */ VARIANT varEndStation,
            /* [retval][out] */ IAlignment **alignment) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateConnectedAlignment( 
            /* [retval][out] */ IAlignment **alignment) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateParallelPath( 
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPath **path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateSubPath( 
            /* [in] */ VARIANT varStartStation,
            /* [in] */ VARIANT varEndStation,
            /* [retval][out] */ IPath **path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateConnectedPath( 
            /* [retval][out] */ IPath **path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ Float64 dist,
            /* [in] */ IDirection *direction) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDirection( 
            /* [in] */ VARIANT varStation,
            /* [in] */ BSTR bstrOrientation,
            /* [retval][out] */ IDirection **direction) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DistanceBetweenStations( 
            /* [in] */ VARIANT station1,
            /* [in] */ VARIANT station2,
            /* [retval][out] */ Float64 *pDist) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAlignmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAlignment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAlignment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAlignment * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IAlignment * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IAlignment * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IPathElement **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IAlignment * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPathElement *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IAlignment * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RefStation )( 
            IAlignment * This,
            /* [retval][out] */ IStation **station);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RefStation )( 
            IAlignment * This,
            /* [in] */ VARIANT varStation);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IAlignment * This,
            /* [retval][out] */ IProfile **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StationEquations )( 
            IAlignment * This,
            /* [retval][out] */ IStationEquationCollection **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IAlignment * This,
            /* [in] */ IPathElement *element);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            IAlignment * This,
            /* [in] */ IUnknown *dispElement);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IAlignment * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IPathElement *element);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *InsertEx )( 
            IAlignment * This,
            /* [in] */ CollectionIndexType idx,
            /* [in] */ IUnknown *dispElement);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IAlignment * This,
            /* [in] */ VARIANT varID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IAlignment * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LocatePoint )( 
            IAlignment * This,
            /* [in] */ VARIANT varStation,
            /* [in] */ OffsetMeasureType offsetMeasure,
            /* [in] */ Float64 offset,
            /* [in] */ VARIANT varDir,
            /* [retval][out] */ IPoint2d **newPoint);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Bearing )( 
            IAlignment * This,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ IDirection **dir);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Normal )( 
            IAlignment * This,
            /* [in] */ VARIANT varStation,
            /* [retval][out] */ IDirection **dir);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Offset )( 
            IAlignment * This,
            /* [in] */ IPoint2d *point,
            /* [out] */ IStation **station,
            /* [out] */ Float64 *offset);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectPoint )( 
            IAlignment * This,
            /* [in] */ IPoint2d *point,
            /* [retval][out] */ IPoint2d **newPoint);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Intersect )( 
            IAlignment * This,
            /* [in] */ ILine2d *line,
            /* [in] */ IPoint2d *pNearest,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IntersectEx )( 
            IAlignment * This,
            /* [in] */ ILine2d *line,
            /* [in] */ IPoint2d *pNearest,
            /* [in] */ VARIANT_BOOL vbProjectBack,
            /* [in] */ VARIANT_BOOL vbProjectAhead,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IAlignment * This,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointFactory )( 
            IAlignment * This,
            /* [retval][out] */ IPoint2dFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PointFactory )( 
            IAlignment * This,
            /* [in] */ IPoint2dFactory *factory);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumAlignmentElements )( 
            IAlignment * This,
            /* [retval][out] */ IEnumPathElements **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IAlignment * This,
            /* [retval][out] */ IAlignment **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateParallelAlignment )( 
            IAlignment * This,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IAlignment **alignment);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSubAlignment )( 
            IAlignment * This,
            /* [in] */ VARIANT varStartStation,
            /* [in] */ VARIANT varEndStation,
            /* [retval][out] */ IAlignment **alignment);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateConnectedAlignment )( 
            IAlignment * This,
            /* [retval][out] */ IAlignment **alignment);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateParallelPath )( 
            IAlignment * This,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPath **path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateSubPath )( 
            IAlignment * This,
            /* [in] */ VARIANT varStartStation,
            /* [in] */ VARIANT varEndStation,
            /* [retval][out] */ IPath **path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateConnectedPath )( 
            IAlignment * This,
            /* [retval][out] */ IPath **path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IAlignment * This,
            /* [in] */ Float64 dist,
            /* [in] */ IDirection *direction);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDirection )( 
            IAlignment * This,
            /* [in] */ VARIANT varStation,
            /* [in] */ BSTR bstrOrientation,
            /* [retval][out] */ IDirection **direction);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DistanceBetweenStations )( 
            IAlignment * This,
            /* [in] */ VARIANT station1,
            /* [in] */ VARIANT station2,
            /* [retval][out] */ Float64 *pDist);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IAlignment * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IAlignmentVtbl;

    interface IAlignment
    {
        CONST_VTBL struct IAlignmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlignment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAlignment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAlignment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAlignment_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IAlignment_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IAlignment_putref_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> putref_Item(This,idx,pVal) ) 

#define IAlignment_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IAlignment_get_RefStation(This,station)	\
    ( (This)->lpVtbl -> get_RefStation(This,station) ) 

#define IAlignment_put_RefStation(This,varStation)	\
    ( (This)->lpVtbl -> put_RefStation(This,varStation) ) 

#define IAlignment_get_Profile(This,pVal)	\
    ( (This)->lpVtbl -> get_Profile(This,pVal) ) 

#define IAlignment_get_StationEquations(This,pVal)	\
    ( (This)->lpVtbl -> get_StationEquations(This,pVal) ) 

#define IAlignment_Add(This,element)	\
    ( (This)->lpVtbl -> Add(This,element) ) 

#define IAlignment_AddEx(This,dispElement)	\
    ( (This)->lpVtbl -> AddEx(This,dispElement) ) 

#define IAlignment_Insert(This,idx,element)	\
    ( (This)->lpVtbl -> Insert(This,idx,element) ) 

#define IAlignment_InsertEx(This,idx,dispElement)	\
    ( (This)->lpVtbl -> InsertEx(This,idx,dispElement) ) 

#define IAlignment_Remove(This,varID)	\
    ( (This)->lpVtbl -> Remove(This,varID) ) 

#define IAlignment_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IAlignment_LocatePoint(This,varStation,offsetMeasure,offset,varDir,newPoint)	\
    ( (This)->lpVtbl -> LocatePoint(This,varStation,offsetMeasure,offset,varDir,newPoint) ) 

#define IAlignment_Bearing(This,varStation,dir)	\
    ( (This)->lpVtbl -> Bearing(This,varStation,dir) ) 

#define IAlignment_Normal(This,varStation,dir)	\
    ( (This)->lpVtbl -> Normal(This,varStation,dir) ) 

#define IAlignment_Offset(This,point,station,offset)	\
    ( (This)->lpVtbl -> Offset(This,point,station,offset) ) 

#define IAlignment_ProjectPoint(This,point,newPoint)	\
    ( (This)->lpVtbl -> ProjectPoint(This,point,newPoint) ) 

#define IAlignment_Intersect(This,line,pNearest,point)	\
    ( (This)->lpVtbl -> Intersect(This,line,pNearest,point) ) 

#define IAlignment_IntersectEx(This,line,pNearest,vbProjectBack,vbProjectAhead,point)	\
    ( (This)->lpVtbl -> IntersectEx(This,line,pNearest,vbProjectBack,vbProjectAhead,point) ) 

#define IAlignment_get_Length(This,pLength)	\
    ( (This)->lpVtbl -> get_Length(This,pLength) ) 

#define IAlignment_get_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> get_PointFactory(This,factory) ) 

#define IAlignment_putref_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_PointFactory(This,factory) ) 

#define IAlignment_get__EnumAlignmentElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumAlignmentElements(This,pVal) ) 

#define IAlignment_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IAlignment_CreateParallelAlignment(This,offset,alignment)	\
    ( (This)->lpVtbl -> CreateParallelAlignment(This,offset,alignment) ) 

#define IAlignment_CreateSubAlignment(This,varStartStation,varEndStation,alignment)	\
    ( (This)->lpVtbl -> CreateSubAlignment(This,varStartStation,varEndStation,alignment) ) 

#define IAlignment_CreateConnectedAlignment(This,alignment)	\
    ( (This)->lpVtbl -> CreateConnectedAlignment(This,alignment) ) 

#define IAlignment_CreateParallelPath(This,offset,path)	\
    ( (This)->lpVtbl -> CreateParallelPath(This,offset,path) ) 

#define IAlignment_CreateSubPath(This,varStartStation,varEndStation,path)	\
    ( (This)->lpVtbl -> CreateSubPath(This,varStartStation,varEndStation,path) ) 

#define IAlignment_CreateConnectedPath(This,path)	\
    ( (This)->lpVtbl -> CreateConnectedPath(This,path) ) 

#define IAlignment_Move(This,dist,direction)	\
    ( (This)->lpVtbl -> Move(This,dist,direction) ) 

#define IAlignment_GetDirection(This,varStation,bstrOrientation,direction)	\
    ( (This)->lpVtbl -> GetDirection(This,varStation,bstrOrientation,direction) ) 

#define IAlignment_DistanceBetweenStations(This,station1,station2,pDist)	\
    ( (This)->lpVtbl -> DistanceBetweenStations(This,station1,station2,pDist) ) 

#define IAlignment_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAlignment_INTERFACE_DEFINED__ */


#ifndef __IAlignmentEvents_INTERFACE_DEFINED__
#define __IAlignmentEvents_INTERFACE_DEFINED__

/* interface IAlignmentEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAlignmentEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D99C606A-2AFA-4779-92BF-D2FB7E71D3B2")
    IAlignmentEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAlignmentChanged( 
            /* [in] */ IAlignment *alignment) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfileChanged( 
            /* [in] */ IProfile *profile) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStationEquationsChanged( 
            /* [in] */ IStationEquationCollection *equations) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAlignmentEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAlignmentEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAlignmentEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAlignmentEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAlignmentChanged )( 
            IAlignmentEvents * This,
            /* [in] */ IAlignment *alignment);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfileChanged )( 
            IAlignmentEvents * This,
            /* [in] */ IProfile *profile);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStationEquationsChanged )( 
            IAlignmentEvents * This,
            /* [in] */ IStationEquationCollection *equations);
        
        END_INTERFACE
    } IAlignmentEventsVtbl;

    interface IAlignmentEvents
    {
        CONST_VTBL struct IAlignmentEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlignmentEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAlignmentEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAlignmentEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAlignmentEvents_OnAlignmentChanged(This,alignment)	\
    ( (This)->lpVtbl -> OnAlignmentChanged(This,alignment) ) 

#define IAlignmentEvents_OnProfileChanged(This,profile)	\
    ( (This)->lpVtbl -> OnProfileChanged(This,profile) ) 

#define IAlignmentEvents_OnStationEquationsChanged(This,equations)	\
    ( (This)->lpVtbl -> OnStationEquationsChanged(This,equations) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAlignmentEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumAlignments_INTERFACE_DEFINED__
#define __IEnumAlignments_INTERFACE_DEFINED__

/* interface IEnumAlignments */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumAlignments;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE7730EB-3289-45de-9158-0345C1B93879")
    IEnumAlignments : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumAlignments **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IAlignment **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumAlignmentsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumAlignments * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumAlignments * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumAlignments * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumAlignments * This,
            /* [out] */ IEnumAlignments **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumAlignments * This,
            /* [in] */ ULONG celt,
            /* [out] */ IAlignment **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumAlignments * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumAlignments * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumAlignmentsVtbl;

    interface IEnumAlignments
    {
        CONST_VTBL struct IEnumAlignmentsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumAlignments_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumAlignments_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumAlignments_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumAlignments_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumAlignments_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumAlignments_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumAlignments_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumAlignments_INTERFACE_DEFINED__ */


#ifndef __IAlignmentFactory_INTERFACE_DEFINED__
#define __IAlignmentFactory_INTERFACE_DEFINED__

/* interface IAlignmentFactory */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAlignmentFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B19475E6-68F6-4afe-80CC-C513D0836508")
    IAlignmentFactory : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CreateAlignment( 
            /* [retval][out] */ IAlignment **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IsValidType( 
            /* [in] */ IAlignment *alignment,
            /* [retval][out] */ VARIANT_BOOL *bIsValid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAlignmentFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAlignmentFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAlignmentFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAlignmentFactory * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateAlignment )( 
            IAlignmentFactory * This,
            /* [retval][out] */ IAlignment **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsValidType )( 
            IAlignmentFactory * This,
            /* [in] */ IAlignment *alignment,
            /* [retval][out] */ VARIANT_BOOL *bIsValid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IAlignmentFactory * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IAlignmentFactoryVtbl;

    interface IAlignmentFactory
    {
        CONST_VTBL struct IAlignmentFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlignmentFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAlignmentFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAlignmentFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAlignmentFactory_CreateAlignment(This,pVal)	\
    ( (This)->lpVtbl -> CreateAlignment(This,pVal) ) 

#define IAlignmentFactory_IsValidType(This,alignment,bIsValid)	\
    ( (This)->lpVtbl -> IsValidType(This,alignment,bIsValid) ) 

#define IAlignmentFactory_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAlignmentFactory_INTERFACE_DEFINED__ */


#ifndef __IAlignmentCollection_INTERFACE_DEFINED__
#define __IAlignmentCollection_INTERFACE_DEFINED__

/* interface IAlignmentCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAlignmentCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9982DEC2-337E-462f-84C6-9E3CE075DE65")
    IAlignmentCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IAlignment **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IAlignment **Alignment) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddEx( 
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FindID( 
            /* [in] */ IAlignment *Alignment,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumIDs( 
            /* [retval][out] */ IEnumIDs **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Factory( 
            /* [retval][out] */ IAlignmentFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Factory( 
            /* [in] */ IAlignmentFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ID( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumAlignments( 
            /* [retval][out] */ IEnumAlignments **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IAlignmentCollection **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAlignmentCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAlignmentCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAlignmentCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAlignmentCollection * This);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IAlignmentCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IAlignmentCollection * This,
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IAlignment **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IAlignmentCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IAlignmentCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IAlignmentCollection * This,
            /* [in] */ CogoObjectID id,
            /* [retval][out] */ IAlignment **Alignment);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddEx )( 
            IAlignmentCollection * This,
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IAlignmentCollection * This,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IAlignmentCollection * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindID )( 
            IAlignmentCollection * This,
            /* [in] */ IAlignment *Alignment,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumIDs )( 
            IAlignmentCollection * This,
            /* [retval][out] */ IEnumIDs **ppenum);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Factory )( 
            IAlignmentCollection * This,
            /* [retval][out] */ IAlignmentFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Factory )( 
            IAlignmentCollection * This,
            /* [in] */ IAlignmentFactory *factory);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ID )( 
            IAlignmentCollection * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ CogoObjectID *ID);
        
        /* [helpcontext][helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumAlignments )( 
            IAlignmentCollection * This,
            /* [retval][out] */ IEnumAlignments **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IAlignmentCollection * This,
            /* [retval][out] */ IAlignmentCollection **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IAlignmentCollection * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IAlignmentCollectionVtbl;

    interface IAlignmentCollection
    {
        CONST_VTBL struct IAlignmentCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlignmentCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAlignmentCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAlignmentCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAlignmentCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IAlignmentCollection_get_Item(This,id,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,id,pVal) ) 

#define IAlignmentCollection_putref_Item(This,id,pVal)	\
    ( (This)->lpVtbl -> putref_Item(This,id,pVal) ) 

#define IAlignmentCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IAlignmentCollection_Add(This,id,Alignment)	\
    ( (This)->lpVtbl -> Add(This,id,Alignment) ) 

#define IAlignmentCollection_AddEx(This,id,newVal)	\
    ( (This)->lpVtbl -> AddEx(This,id,newVal) ) 

#define IAlignmentCollection_Remove(This,id)	\
    ( (This)->lpVtbl -> Remove(This,id) ) 

#define IAlignmentCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IAlignmentCollection_FindID(This,Alignment,ID)	\
    ( (This)->lpVtbl -> FindID(This,Alignment,ID) ) 

#define IAlignmentCollection_get__EnumIDs(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumIDs(This,ppenum) ) 

#define IAlignmentCollection_get_Factory(This,factory)	\
    ( (This)->lpVtbl -> get_Factory(This,factory) ) 

#define IAlignmentCollection_putref_Factory(This,factory)	\
    ( (This)->lpVtbl -> putref_Factory(This,factory) ) 

#define IAlignmentCollection_ID(This,index,ID)	\
    ( (This)->lpVtbl -> ID(This,index,ID) ) 

#define IAlignmentCollection_get__EnumAlignments(This,ppenum)	\
    ( (This)->lpVtbl -> get__EnumAlignments(This,ppenum) ) 

#define IAlignmentCollection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IAlignmentCollection_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAlignmentCollection_INTERFACE_DEFINED__ */


#ifndef __IAlignmentCollectionEvents_INTERFACE_DEFINED__
#define __IAlignmentCollectionEvents_INTERFACE_DEFINED__

/* interface IAlignmentCollectionEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAlignmentCollectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("46D1C201-C51F-4eb1-AFCC-922DDBC62D16")
    IAlignmentCollectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfileChanged( 
            /* [in] */ IAlignmentCollection *coll,
            /* [in] */ IProfile *profile) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStationEquationsChanged( 
            /* [in] */ IAlignmentCollection *coll,
            /* [in] */ IStationEquationCollection *equations) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAlignmentChanged( 
            /* [in] */ IAlignmentCollection *coll,
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *Alignment) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAlignmentAdded( 
            /* [in] */ IAlignmentCollection *coll,
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *Alignment) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAlignmentRemoved( 
            /* [in] */ IAlignmentCollection *coll,
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAlignmentsCleared( 
            /* [in] */ IAlignmentCollection *coll) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAlignmentCollectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAlignmentCollectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAlignmentCollectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAlignmentCollectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfileChanged )( 
            IAlignmentCollectionEvents * This,
            /* [in] */ IAlignmentCollection *coll,
            /* [in] */ IProfile *profile);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStationEquationsChanged )( 
            IAlignmentCollectionEvents * This,
            /* [in] */ IAlignmentCollection *coll,
            /* [in] */ IStationEquationCollection *equations);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAlignmentChanged )( 
            IAlignmentCollectionEvents * This,
            /* [in] */ IAlignmentCollection *coll,
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *Alignment);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAlignmentAdded )( 
            IAlignmentCollectionEvents * This,
            /* [in] */ IAlignmentCollection *coll,
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *Alignment);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAlignmentRemoved )( 
            IAlignmentCollectionEvents * This,
            /* [in] */ IAlignmentCollection *coll,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAlignmentsCleared )( 
            IAlignmentCollectionEvents * This,
            /* [in] */ IAlignmentCollection *coll);
        
        END_INTERFACE
    } IAlignmentCollectionEventsVtbl;

    interface IAlignmentCollectionEvents
    {
        CONST_VTBL struct IAlignmentCollectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlignmentCollectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAlignmentCollectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAlignmentCollectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAlignmentCollectionEvents_OnProfileChanged(This,coll,profile)	\
    ( (This)->lpVtbl -> OnProfileChanged(This,coll,profile) ) 

#define IAlignmentCollectionEvents_OnStationEquationsChanged(This,coll,equations)	\
    ( (This)->lpVtbl -> OnStationEquationsChanged(This,coll,equations) ) 

#define IAlignmentCollectionEvents_OnAlignmentChanged(This,coll,id,Alignment)	\
    ( (This)->lpVtbl -> OnAlignmentChanged(This,coll,id,Alignment) ) 

#define IAlignmentCollectionEvents_OnAlignmentAdded(This,coll,id,Alignment)	\
    ( (This)->lpVtbl -> OnAlignmentAdded(This,coll,id,Alignment) ) 

#define IAlignmentCollectionEvents_OnAlignmentRemoved(This,coll,id)	\
    ( (This)->lpVtbl -> OnAlignmentRemoved(This,coll,id) ) 

#define IAlignmentCollectionEvents_OnAlignmentsCleared(This,coll)	\
    ( (This)->lpVtbl -> OnAlignmentsCleared(This,coll) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAlignmentCollectionEvents_INTERFACE_DEFINED__ */


#ifndef __IMeasure_INTERFACE_DEFINED__
#define __IMeasure_INTERFACE_DEFINED__

/* interface IMeasure */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IMeasure;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C659E538-5EBE-11d5-8C32-006097C68A9C")
    IMeasure : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Angle( 
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID vertexID,
            /* [in] */ CogoObjectID toID,
            /* [retval][out] */ IAngle **angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Area( 
            /* [in] */ VARIANT IDs,
            /* [retval][out] */ Float64 *area) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Distance( 
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [retval][out] */ Float64 *dist) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Direction( 
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [retval][out] */ IDirection **dir) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Inverse( 
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [out] */ Float64 *dist,
            /* [out] */ IDirection **dir) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMeasureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMeasure * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMeasure * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMeasure * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Angle )( 
            IMeasure * This,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID vertexID,
            /* [in] */ CogoObjectID toID,
            /* [retval][out] */ IAngle **angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Area )( 
            IMeasure * This,
            /* [in] */ VARIANT IDs,
            /* [retval][out] */ Float64 *area);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Distance )( 
            IMeasure * This,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [retval][out] */ Float64 *dist);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Direction )( 
            IMeasure * This,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [retval][out] */ IDirection **dir);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Inverse )( 
            IMeasure * This,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [out] */ Float64 *dist,
            /* [out] */ IDirection **dir);
        
        END_INTERFACE
    } IMeasureVtbl;

    interface IMeasure
    {
        CONST_VTBL struct IMeasureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMeasure_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMeasure_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMeasure_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMeasure_Angle(This,fromID,vertexID,toID,angle)	\
    ( (This)->lpVtbl -> Angle(This,fromID,vertexID,toID,angle) ) 

#define IMeasure_Area(This,IDs,area)	\
    ( (This)->lpVtbl -> Area(This,IDs,area) ) 

#define IMeasure_Distance(This,fromID,toID,dist)	\
    ( (This)->lpVtbl -> Distance(This,fromID,toID,dist) ) 

#define IMeasure_Direction(This,fromID,toID,dir)	\
    ( (This)->lpVtbl -> Direction(This,fromID,toID,dir) ) 

#define IMeasure_Inverse(This,fromID,toID,dist,dir)	\
    ( (This)->lpVtbl -> Inverse(This,fromID,toID,dist,dir) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMeasure_INTERFACE_DEFINED__ */


#ifndef __IMeasure2_INTERFACE_DEFINED__
#define __IMeasure2_INTERFACE_DEFINED__

/* interface IMeasure2 */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IMeasure2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("677836E0-0FC9-42b3-867E-F26D7DB5591D")
    IMeasure2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Angle( 
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *vertex,
            /* [in] */ IPoint2d *to,
            /* [retval][out] */ IAngle **angle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Area( 
            /* [in] */ IPoint2dCollection *points,
            /* [retval][out] */ Float64 *area) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Distance( 
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [retval][out] */ Float64 *dist) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Direction( 
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [retval][out] */ IDirection **dir) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Inverse( 
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [out] */ Float64 *dist,
            /* [out] */ IDirection **dir) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMeasure2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMeasure2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMeasure2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMeasure2 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Angle )( 
            IMeasure2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *vertex,
            /* [in] */ IPoint2d *to,
            /* [retval][out] */ IAngle **angle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Area )( 
            IMeasure2 * This,
            /* [in] */ IPoint2dCollection *points,
            /* [retval][out] */ Float64 *area);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Distance )( 
            IMeasure2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [retval][out] */ Float64 *dist);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Direction )( 
            IMeasure2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [retval][out] */ IDirection **dir);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Inverse )( 
            IMeasure2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [out] */ Float64 *dist,
            /* [out] */ IDirection **dir);
        
        END_INTERFACE
    } IMeasure2Vtbl;

    interface IMeasure2
    {
        CONST_VTBL struct IMeasure2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMeasure2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMeasure2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMeasure2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMeasure2_Angle(This,from,vertex,to,angle)	\
    ( (This)->lpVtbl -> Angle(This,from,vertex,to,angle) ) 

#define IMeasure2_Area(This,points,area)	\
    ( (This)->lpVtbl -> Area(This,points,area) ) 

#define IMeasure2_Distance(This,from,to,dist)	\
    ( (This)->lpVtbl -> Distance(This,from,to,dist) ) 

#define IMeasure2_Direction(This,from,to,dir)	\
    ( (This)->lpVtbl -> Direction(This,from,to,dir) ) 

#define IMeasure2_Inverse(This,from,to,dist,dir)	\
    ( (This)->lpVtbl -> Inverse(This,from,to,dist,dir) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMeasure2_INTERFACE_DEFINED__ */


#ifndef __ILocate_INTERFACE_DEFINED__
#define __ILocate_INTERFACE_DEFINED__

/* interface ILocate */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILocate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("26FFDDD8-5EB8-11d5-8C32-006097C68A9C")
    ILocate : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ByDistAngle( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varAngle,
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ByDistDefAngle( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varDefAngle,
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ByDistDir( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varDir,
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnLine( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ Float64 dist,
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ParallelLineByPoints( 
            /* [in] */ CogoObjectID newFromID,
            /* [in] */ CogoObjectID newToID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ParallelLineSegment( 
            /* [in] */ CogoObjectID newLineID,
            /* [in] */ CogoObjectID newFromID,
            /* [in] */ CogoObjectID newToID,
            /* [in] */ CogoObjectID lineID,
            /* [in] */ Float64 offset) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILocateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILocate * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILocate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILocate * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ByDistAngle )( 
            ILocate * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varAngle,
            /* [in] */ Float64 offset);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ByDistDefAngle )( 
            ILocate * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varDefAngle,
            /* [in] */ Float64 offset);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ByDistDir )( 
            ILocate * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varDir,
            /* [in] */ Float64 offset);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnLine )( 
            ILocate * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ Float64 dist,
            /* [in] */ Float64 offset);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ParallelLineByPoints )( 
            ILocate * This,
            /* [in] */ CogoObjectID newFromID,
            /* [in] */ CogoObjectID newToID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ Float64 offset);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ParallelLineSegment )( 
            ILocate * This,
            /* [in] */ CogoObjectID newLineID,
            /* [in] */ CogoObjectID newFromID,
            /* [in] */ CogoObjectID newToID,
            /* [in] */ CogoObjectID lineID,
            /* [in] */ Float64 offset);
        
        END_INTERFACE
    } ILocateVtbl;

    interface ILocate
    {
        CONST_VTBL struct ILocateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILocate_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILocate_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILocate_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILocate_ByDistAngle(This,newID,fromID,toID,dist,varAngle,offset)	\
    ( (This)->lpVtbl -> ByDistAngle(This,newID,fromID,toID,dist,varAngle,offset) ) 

#define ILocate_ByDistDefAngle(This,newID,fromID,toID,dist,varDefAngle,offset)	\
    ( (This)->lpVtbl -> ByDistDefAngle(This,newID,fromID,toID,dist,varDefAngle,offset) ) 

#define ILocate_ByDistDir(This,newID,fromID,dist,varDir,offset)	\
    ( (This)->lpVtbl -> ByDistDir(This,newID,fromID,dist,varDir,offset) ) 

#define ILocate_PointOnLine(This,newID,fromID,toID,dist,offset)	\
    ( (This)->lpVtbl -> PointOnLine(This,newID,fromID,toID,dist,offset) ) 

#define ILocate_ParallelLineByPoints(This,newFromID,newToID,fromID,toID,offset)	\
    ( (This)->lpVtbl -> ParallelLineByPoints(This,newFromID,newToID,fromID,toID,offset) ) 

#define ILocate_ParallelLineSegment(This,newLineID,newFromID,newToID,lineID,offset)	\
    ( (This)->lpVtbl -> ParallelLineSegment(This,newLineID,newFromID,newToID,lineID,offset) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILocate_INTERFACE_DEFINED__ */


#ifndef __ILocate2_INTERFACE_DEFINED__
#define __ILocate2_INTERFACE_DEFINED__

/* interface ILocate2 */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILocate2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2F0AAEBF-F043-4d50-8E11-709CF6079F5F")
    ILocate2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ByDistAngle( 
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varAngle,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ByDistDefAngle( 
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varDefAngle,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ByDistDir( 
            /* [in] */ IPoint2d *from,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varDir,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnLine( 
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [in] */ Float64 dist,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ParallelLineByPoints( 
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [in] */ Float64 offset,
            /* [out] */ IPoint2d **p1,
            /* [out] */ IPoint2d **p2) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ParallelLineSegment( 
            /* [in] */ ILineSegment2d *ls,
            /* [in] */ Float64 offset,
            /* [retval][out] */ ILineSegment2d **linesegment) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILocate2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILocate2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILocate2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILocate2 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ByDistAngle )( 
            ILocate2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varAngle,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ByDistDefAngle )( 
            ILocate2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varDefAngle,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ByDistDir )( 
            ILocate2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ Float64 dist,
            /* [in] */ VARIANT varDir,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnLine )( 
            ILocate2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [in] */ Float64 dist,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ParallelLineByPoints )( 
            ILocate2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [in] */ Float64 offset,
            /* [out] */ IPoint2d **p1,
            /* [out] */ IPoint2d **p2);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ParallelLineSegment )( 
            ILocate2 * This,
            /* [in] */ ILineSegment2d *ls,
            /* [in] */ Float64 offset,
            /* [retval][out] */ ILineSegment2d **linesegment);
        
        END_INTERFACE
    } ILocate2Vtbl;

    interface ILocate2
    {
        CONST_VTBL struct ILocate2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILocate2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILocate2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILocate2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILocate2_ByDistAngle(This,from,to,dist,varAngle,offset,point)	\
    ( (This)->lpVtbl -> ByDistAngle(This,from,to,dist,varAngle,offset,point) ) 

#define ILocate2_ByDistDefAngle(This,from,to,dist,varDefAngle,offset,point)	\
    ( (This)->lpVtbl -> ByDistDefAngle(This,from,to,dist,varDefAngle,offset,point) ) 

#define ILocate2_ByDistDir(This,from,dist,varDir,offset,point)	\
    ( (This)->lpVtbl -> ByDistDir(This,from,dist,varDir,offset,point) ) 

#define ILocate2_PointOnLine(This,from,to,dist,offset,point)	\
    ( (This)->lpVtbl -> PointOnLine(This,from,to,dist,offset,point) ) 

#define ILocate2_ParallelLineByPoints(This,from,to,offset,p1,p2)	\
    ( (This)->lpVtbl -> ParallelLineByPoints(This,from,to,offset,p1,p2) ) 

#define ILocate2_ParallelLineSegment(This,ls,offset,linesegment)	\
    ( (This)->lpVtbl -> ParallelLineSegment(This,ls,offset,linesegment) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILocate2_INTERFACE_DEFINED__ */


#ifndef __IIntersect_INTERFACE_DEFINED__
#define __IIntersect_INTERFACE_DEFINED__

/* interface IIntersect */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IIntersect;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("26FFDDD6-5EB8-11d5-8C32-006097C68A9C")
    IIntersect : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Bearings( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id1,
            /* [in] */ VARIANT varDir1,
            /* [in] */ Float64 offset1,
            /* [in] */ CogoObjectID id2,
            /* [in] */ VARIANT varDir2,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ VARIANT_BOOL *bFound) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE BearingCircle( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id1,
            /* [in] */ VARIANT varDir,
            /* [in] */ Float64 offset,
            /* [in] */ CogoObjectID idc,
            /* [in] */ Float64 radius,
            /* [in] */ CogoObjectID idNearest,
            /* [retval][out] */ VARIANT_BOOL *bFound) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Circles( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id1,
            /* [in] */ Float64 r1,
            /* [in] */ CogoObjectID id2,
            /* [in] */ Float64 r2,
            /* [in] */ CogoObjectID idNearest,
            /* [retval][out] */ VARIANT_BOOL *bFound) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LineByPointsCircle( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id1,
            /* [in] */ CogoObjectID id2,
            /* [in] */ Float64 offset,
            /* [in] */ CogoObjectID idc,
            /* [in] */ Float64 radius,
            /* [in] */ CogoObjectID idNearest,
            /* [retval][out] */ VARIANT_BOOL *bFound) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LinesByPoints( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id11,
            /* [in] */ CogoObjectID id12,
            /* [in] */ Float64 offset1,
            /* [in] */ CogoObjectID id21,
            /* [in] */ CogoObjectID id22,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ VARIANT_BOOL *bFound) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Lines( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id1,
            /* [in] */ Float64 offset1,
            /* [in] */ CogoObjectID id2,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ VARIANT_BOOL *bFound) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LineSegmentCircle( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID lineID,
            /* [in] */ Float64 offset,
            /* [in] */ CogoObjectID idc,
            /* [in] */ Float64 radius,
            /* [in] */ CogoObjectID idNearest,
            /* [retval][out] */ VARIANT_BOOL *bFound) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIntersectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIntersect * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIntersect * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIntersect * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Bearings )( 
            IIntersect * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id1,
            /* [in] */ VARIANT varDir1,
            /* [in] */ Float64 offset1,
            /* [in] */ CogoObjectID id2,
            /* [in] */ VARIANT varDir2,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ VARIANT_BOOL *bFound);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *BearingCircle )( 
            IIntersect * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id1,
            /* [in] */ VARIANT varDir,
            /* [in] */ Float64 offset,
            /* [in] */ CogoObjectID idc,
            /* [in] */ Float64 radius,
            /* [in] */ CogoObjectID idNearest,
            /* [retval][out] */ VARIANT_BOOL *bFound);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Circles )( 
            IIntersect * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id1,
            /* [in] */ Float64 r1,
            /* [in] */ CogoObjectID id2,
            /* [in] */ Float64 r2,
            /* [in] */ CogoObjectID idNearest,
            /* [retval][out] */ VARIANT_BOOL *bFound);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LineByPointsCircle )( 
            IIntersect * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id1,
            /* [in] */ CogoObjectID id2,
            /* [in] */ Float64 offset,
            /* [in] */ CogoObjectID idc,
            /* [in] */ Float64 radius,
            /* [in] */ CogoObjectID idNearest,
            /* [retval][out] */ VARIANT_BOOL *bFound);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LinesByPoints )( 
            IIntersect * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id11,
            /* [in] */ CogoObjectID id12,
            /* [in] */ Float64 offset1,
            /* [in] */ CogoObjectID id21,
            /* [in] */ CogoObjectID id22,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ VARIANT_BOOL *bFound);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Lines )( 
            IIntersect * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID id1,
            /* [in] */ Float64 offset1,
            /* [in] */ CogoObjectID id2,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ VARIANT_BOOL *bFound);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LineSegmentCircle )( 
            IIntersect * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID lineID,
            /* [in] */ Float64 offset,
            /* [in] */ CogoObjectID idc,
            /* [in] */ Float64 radius,
            /* [in] */ CogoObjectID idNearest,
            /* [retval][out] */ VARIANT_BOOL *bFound);
        
        END_INTERFACE
    } IIntersectVtbl;

    interface IIntersect
    {
        CONST_VTBL struct IIntersectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIntersect_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIntersect_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIntersect_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIntersect_Bearings(This,newID,id1,varDir1,offset1,id2,varDir2,offset2,bFound)	\
    ( (This)->lpVtbl -> Bearings(This,newID,id1,varDir1,offset1,id2,varDir2,offset2,bFound) ) 

#define IIntersect_BearingCircle(This,newID,id1,varDir,offset,idc,radius,idNearest,bFound)	\
    ( (This)->lpVtbl -> BearingCircle(This,newID,id1,varDir,offset,idc,radius,idNearest,bFound) ) 

#define IIntersect_Circles(This,newID,id1,r1,id2,r2,idNearest,bFound)	\
    ( (This)->lpVtbl -> Circles(This,newID,id1,r1,id2,r2,idNearest,bFound) ) 

#define IIntersect_LineByPointsCircle(This,newID,id1,id2,offset,idc,radius,idNearest,bFound)	\
    ( (This)->lpVtbl -> LineByPointsCircle(This,newID,id1,id2,offset,idc,radius,idNearest,bFound) ) 

#define IIntersect_LinesByPoints(This,newID,id11,id12,offset1,id21,id22,offset2,bFound)	\
    ( (This)->lpVtbl -> LinesByPoints(This,newID,id11,id12,offset1,id21,id22,offset2,bFound) ) 

#define IIntersect_Lines(This,newID,id1,offset1,id2,offset2,bFound)	\
    ( (This)->lpVtbl -> Lines(This,newID,id1,offset1,id2,offset2,bFound) ) 

#define IIntersect_LineSegmentCircle(This,newID,lineID,offset,idc,radius,idNearest,bFound)	\
    ( (This)->lpVtbl -> LineSegmentCircle(This,newID,lineID,offset,idc,radius,idNearest,bFound) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIntersect_INTERFACE_DEFINED__ */


#ifndef __IIntersect2_INTERFACE_DEFINED__
#define __IIntersect2_INTERFACE_DEFINED__

/* interface IIntersect2 */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IIntersect2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5AFCF67A-4802-42cf-9C5C-AF5A61D4D0D4")
    IIntersect2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Bearings( 
            /* [in] */ IPoint2d *p1,
            /* [in] */ VARIANT varDir1,
            /* [in] */ Float64 offset1,
            /* [in] */ IPoint2d *p2,
            /* [in] */ VARIANT varDir2,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE BearingCircle( 
            /* [in] */ IPoint2d *p1,
            /* [in] */ VARIANT varDir,
            /* [in] */ Float64 offset,
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 radius,
            /* [in] */ IPoint2d *nearest,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Circles( 
            /* [in] */ IPoint2d *p1,
            /* [in] */ Float64 r1,
            /* [in] */ IPoint2d *p2,
            /* [in] */ Float64 r2,
            /* [in] */ IPoint2d *nearest,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LineByPointsCircle( 
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2,
            /* [in] */ Float64 offset,
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 radius,
            /* [in] */ IPoint2d *nearest,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LinesByPoints( 
            /* [in] */ IPoint2d *p11,
            /* [in] */ IPoint2d *p12,
            /* [in] */ Float64 offset1,
            /* [in] */ IPoint2d *p21,
            /* [in] */ IPoint2d *p22,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Lines( 
            /* [in] */ ILineSegment2d *l1,
            /* [in] */ Float64 offset1,
            /* [in] */ ILineSegment2d *l2,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LineSegmentCircle( 
            /* [in] */ ILineSegment2d *pSeg,
            /* [in] */ Float64 offset,
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 radius,
            /* [in] */ IPoint2d *nearest,
            /* [retval][out] */ IPoint2d **point) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIntersect2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIntersect2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIntersect2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIntersect2 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Bearings )( 
            IIntersect2 * This,
            /* [in] */ IPoint2d *p1,
            /* [in] */ VARIANT varDir1,
            /* [in] */ Float64 offset1,
            /* [in] */ IPoint2d *p2,
            /* [in] */ VARIANT varDir2,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *BearingCircle )( 
            IIntersect2 * This,
            /* [in] */ IPoint2d *p1,
            /* [in] */ VARIANT varDir,
            /* [in] */ Float64 offset,
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 radius,
            /* [in] */ IPoint2d *nearest,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Circles )( 
            IIntersect2 * This,
            /* [in] */ IPoint2d *p1,
            /* [in] */ Float64 r1,
            /* [in] */ IPoint2d *p2,
            /* [in] */ Float64 r2,
            /* [in] */ IPoint2d *nearest,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LineByPointsCircle )( 
            IIntersect2 * This,
            /* [in] */ IPoint2d *p1,
            /* [in] */ IPoint2d *p2,
            /* [in] */ Float64 offset,
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 radius,
            /* [in] */ IPoint2d *nearest,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LinesByPoints )( 
            IIntersect2 * This,
            /* [in] */ IPoint2d *p11,
            /* [in] */ IPoint2d *p12,
            /* [in] */ Float64 offset1,
            /* [in] */ IPoint2d *p21,
            /* [in] */ IPoint2d *p22,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Lines )( 
            IIntersect2 * This,
            /* [in] */ ILineSegment2d *l1,
            /* [in] */ Float64 offset1,
            /* [in] */ ILineSegment2d *l2,
            /* [in] */ Float64 offset2,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LineSegmentCircle )( 
            IIntersect2 * This,
            /* [in] */ ILineSegment2d *pSeg,
            /* [in] */ Float64 offset,
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 radius,
            /* [in] */ IPoint2d *nearest,
            /* [retval][out] */ IPoint2d **point);
        
        END_INTERFACE
    } IIntersect2Vtbl;

    interface IIntersect2
    {
        CONST_VTBL struct IIntersect2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIntersect2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIntersect2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIntersect2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIntersect2_Bearings(This,p1,varDir1,offset1,p2,varDir2,offset2,point)	\
    ( (This)->lpVtbl -> Bearings(This,p1,varDir1,offset1,p2,varDir2,offset2,point) ) 

#define IIntersect2_BearingCircle(This,p1,varDir,offset,center,radius,nearest,point)	\
    ( (This)->lpVtbl -> BearingCircle(This,p1,varDir,offset,center,radius,nearest,point) ) 

#define IIntersect2_Circles(This,p1,r1,p2,r2,nearest,point)	\
    ( (This)->lpVtbl -> Circles(This,p1,r1,p2,r2,nearest,point) ) 

#define IIntersect2_LineByPointsCircle(This,p1,p2,offset,center,radius,nearest,point)	\
    ( (This)->lpVtbl -> LineByPointsCircle(This,p1,p2,offset,center,radius,nearest,point) ) 

#define IIntersect2_LinesByPoints(This,p11,p12,offset1,p21,p22,offset2,point)	\
    ( (This)->lpVtbl -> LinesByPoints(This,p11,p12,offset1,p21,p22,offset2,point) ) 

#define IIntersect2_Lines(This,l1,offset1,l2,offset2,point)	\
    ( (This)->lpVtbl -> Lines(This,l1,offset1,l2,offset2,point) ) 

#define IIntersect2_LineSegmentCircle(This,pSeg,offset,center,radius,nearest,point)	\
    ( (This)->lpVtbl -> LineSegmentCircle(This,pSeg,offset,center,radius,nearest,point) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIntersect2_INTERFACE_DEFINED__ */


#ifndef __IProject_INTERFACE_DEFINED__
#define __IProject_INTERFACE_DEFINED__

/* interface IProject */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B161BA4-6582-11d5-8C3D-006097C68A9C")
    IProject : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnLineByPoints( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID startID,
            /* [in] */ CogoObjectID endID,
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnLineSegment( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID lineID,
            /* [in] */ Float64 offset) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnCurve( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID curveID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProject * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnLineByPoints )( 
            IProject * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID startID,
            /* [in] */ CogoObjectID endID,
            /* [in] */ Float64 offset);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnLineSegment )( 
            IProject * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID lineID,
            /* [in] */ Float64 offset);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnCurve )( 
            IProject * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID curveID);
        
        END_INTERFACE
    } IProjectVtbl;

    interface IProject
    {
        CONST_VTBL struct IProjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProject_PointOnLineByPoints(This,newID,fromID,startID,endID,offset)	\
    ( (This)->lpVtbl -> PointOnLineByPoints(This,newID,fromID,startID,endID,offset) ) 

#define IProject_PointOnLineSegment(This,newID,fromID,lineID,offset)	\
    ( (This)->lpVtbl -> PointOnLineSegment(This,newID,fromID,lineID,offset) ) 

#define IProject_PointOnCurve(This,newID,fromID,curveID)	\
    ( (This)->lpVtbl -> PointOnCurve(This,newID,fromID,curveID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProject_INTERFACE_DEFINED__ */


#ifndef __IProject2_INTERFACE_DEFINED__
#define __IProject2_INTERFACE_DEFINED__

/* interface IProject2 */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IProject2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FB5BBBA8-6CFD-4cfe-8A0B-DEAB8A7AF254")
    IProject2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnLineByPoints( 
            /* [in] */ IPoint2d *pnt,
            /* [in] */ IPoint2d *start,
            /* [in] */ IPoint2d *end,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnLineSegment( 
            /* [in] */ IPoint2d *from,
            /* [in] */ ILineSegment2d *seg,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE PointOnCurve( 
            /* [in] */ IPoint2d *pnt,
            /* [in] */ IHorzCurve *curve,
            /* [retval][out] */ IPoint2d **point) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProject2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProject2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProject2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProject2 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnLineByPoints )( 
            IProject2 * This,
            /* [in] */ IPoint2d *pnt,
            /* [in] */ IPoint2d *start,
            /* [in] */ IPoint2d *end,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnLineSegment )( 
            IProject2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ ILineSegment2d *seg,
            /* [in] */ Float64 offset,
            /* [retval][out] */ IPoint2d **point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *PointOnCurve )( 
            IProject2 * This,
            /* [in] */ IPoint2d *pnt,
            /* [in] */ IHorzCurve *curve,
            /* [retval][out] */ IPoint2d **point);
        
        END_INTERFACE
    } IProject2Vtbl;

    interface IProject2
    {
        CONST_VTBL struct IProject2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProject2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProject2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProject2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProject2_PointOnLineByPoints(This,pnt,start,end,offset,point)	\
    ( (This)->lpVtbl -> PointOnLineByPoints(This,pnt,start,end,offset,point) ) 

#define IProject2_PointOnLineSegment(This,from,seg,offset,point)	\
    ( (This)->lpVtbl -> PointOnLineSegment(This,from,seg,offset,point) ) 

#define IProject2_PointOnCurve(This,pnt,curve,point)	\
    ( (This)->lpVtbl -> PointOnCurve(This,pnt,curve,point) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProject2_INTERFACE_DEFINED__ */


#ifndef __IDivide_INTERFACE_DEFINED__
#define __IDivide_INTERFACE_DEFINED__

/* interface IDivide */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDivide;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2754C92C-D653-40ef-875B-D4126671E5B5")
    IDivide : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Arc( 
            /* [in] */ CogoObjectID firstID,
            /* [in] */ CogoObjectID idInc,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID vertexID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ CollectionIndexType nParts) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE BetweenPoints( 
            /* [in] */ CogoObjectID firstID,
            /* [in] */ CogoObjectID idInc,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ CollectionIndexType nParts) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LineSegment( 
            /* [in] */ CogoObjectID firstID,
            /* [in] */ CogoObjectID idInc,
            /* [in] */ CogoObjectID lineID,
            /* [in] */ CollectionIndexType nParts) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE HorzCurve( 
            /* [in] */ CogoObjectID firstID,
            /* [in] */ CogoObjectID idInc,
            /* [in] */ CogoObjectID curveID,
            /* [in] */ CollectionIndexType nParts) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Path( 
            /* [in] */ CogoObjectID firstID,
            /* [in] */ CogoObjectID idInc,
            /* [in] */ CogoObjectID pathID,
            /* [in] */ CollectionIndexType nParts,
            /* [in] */ Float64 start,
            /* [in] */ Float64 end) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDivideVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDivide * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDivide * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDivide * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Arc )( 
            IDivide * This,
            /* [in] */ CogoObjectID firstID,
            /* [in] */ CogoObjectID idInc,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID vertexID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ CollectionIndexType nParts);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *BetweenPoints )( 
            IDivide * This,
            /* [in] */ CogoObjectID firstID,
            /* [in] */ CogoObjectID idInc,
            /* [in] */ CogoObjectID fromID,
            /* [in] */ CogoObjectID toID,
            /* [in] */ CollectionIndexType nParts);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LineSegment )( 
            IDivide * This,
            /* [in] */ CogoObjectID firstID,
            /* [in] */ CogoObjectID idInc,
            /* [in] */ CogoObjectID lineID,
            /* [in] */ CollectionIndexType nParts);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *HorzCurve )( 
            IDivide * This,
            /* [in] */ CogoObjectID firstID,
            /* [in] */ CogoObjectID idInc,
            /* [in] */ CogoObjectID curveID,
            /* [in] */ CollectionIndexType nParts);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Path )( 
            IDivide * This,
            /* [in] */ CogoObjectID firstID,
            /* [in] */ CogoObjectID idInc,
            /* [in] */ CogoObjectID pathID,
            /* [in] */ CollectionIndexType nParts,
            /* [in] */ Float64 start,
            /* [in] */ Float64 end);
        
        END_INTERFACE
    } IDivideVtbl;

    interface IDivide
    {
        CONST_VTBL struct IDivideVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDivide_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDivide_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDivide_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDivide_Arc(This,firstID,idInc,fromID,vertexID,toID,nParts)	\
    ( (This)->lpVtbl -> Arc(This,firstID,idInc,fromID,vertexID,toID,nParts) ) 

#define IDivide_BetweenPoints(This,firstID,idInc,fromID,toID,nParts)	\
    ( (This)->lpVtbl -> BetweenPoints(This,firstID,idInc,fromID,toID,nParts) ) 

#define IDivide_LineSegment(This,firstID,idInc,lineID,nParts)	\
    ( (This)->lpVtbl -> LineSegment(This,firstID,idInc,lineID,nParts) ) 

#define IDivide_HorzCurve(This,firstID,idInc,curveID,nParts)	\
    ( (This)->lpVtbl -> HorzCurve(This,firstID,idInc,curveID,nParts) ) 

#define IDivide_Path(This,firstID,idInc,pathID,nParts,start,end)	\
    ( (This)->lpVtbl -> Path(This,firstID,idInc,pathID,nParts,start,end) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDivide_INTERFACE_DEFINED__ */


#ifndef __IDivide2_INTERFACE_DEFINED__
#define __IDivide2_INTERFACE_DEFINED__

/* interface IDivide2 */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDivide2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BF909705-8DEE-4797-A497-4BEDB2156BB5")
    IDivide2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Arc( 
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *vertex,
            /* [in] */ IPoint2d *to,
            /* [in] */ CollectionIndexType nParts,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE BetweenPoints( 
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [in] */ CollectionIndexType nParts,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LineSegment( 
            /* [in] */ ILineSegment2d *seg,
            /* [in] */ CollectionIndexType nParts,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE HorzCurve( 
            /* [in] */ IHorzCurve *curve,
            /* [in] */ CollectionIndexType nParts,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Path( 
            /* [in] */ IPath *pPath,
            /* [in] */ CollectionIndexType nParts,
            /* [in] */ Float64 start,
            /* [in] */ Float64 end,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDivide2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDivide2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDivide2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDivide2 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Arc )( 
            IDivide2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *vertex,
            /* [in] */ IPoint2d *to,
            /* [in] */ CollectionIndexType nParts,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *BetweenPoints )( 
            IDivide2 * This,
            /* [in] */ IPoint2d *from,
            /* [in] */ IPoint2d *to,
            /* [in] */ CollectionIndexType nParts,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LineSegment )( 
            IDivide2 * This,
            /* [in] */ ILineSegment2d *seg,
            /* [in] */ CollectionIndexType nParts,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *HorzCurve )( 
            IDivide2 * This,
            /* [in] */ IHorzCurve *curve,
            /* [in] */ CollectionIndexType nParts,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Path )( 
            IDivide2 * This,
            /* [in] */ IPath *pPath,
            /* [in] */ CollectionIndexType nParts,
            /* [in] */ Float64 start,
            /* [in] */ Float64 end,
            /* [retval][out] */ IPoint2dCollection **points);
        
        END_INTERFACE
    } IDivide2Vtbl;

    interface IDivide2
    {
        CONST_VTBL struct IDivide2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDivide2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDivide2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDivide2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDivide2_Arc(This,from,vertex,to,nParts,points)	\
    ( (This)->lpVtbl -> Arc(This,from,vertex,to,nParts,points) ) 

#define IDivide2_BetweenPoints(This,from,to,nParts,points)	\
    ( (This)->lpVtbl -> BetweenPoints(This,from,to,nParts,points) ) 

#define IDivide2_LineSegment(This,seg,nParts,points)	\
    ( (This)->lpVtbl -> LineSegment(This,seg,nParts,points) ) 

#define IDivide2_HorzCurve(This,curve,nParts,points)	\
    ( (This)->lpVtbl -> HorzCurve(This,curve,nParts,points) ) 

#define IDivide2_Path(This,pPath,nParts,start,end,points)	\
    ( (This)->lpVtbl -> Path(This,pPath,nParts,start,end,points) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDivide2_INTERFACE_DEFINED__ */


#ifndef __ITangent_INTERFACE_DEFINED__
#define __ITangent_INTERFACE_DEFINED__

/* interface ITangent */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITangent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2984C32-607E-4ca3-8424-F8041D5F49D1")
    ITangent : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE External( 
            /* [in] */ CogoObjectID newID1,
            /* [in] */ CogoObjectID idCenter1,
            /* [in] */ Float64 radius1,
            /* [in] */ CogoObjectID newID2,
            /* [in] */ CogoObjectID idCenter2,
            /* [in] */ Float64 radius2,
            /* [in] */ TangentSignType sign) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Cross( 
            /* [in] */ CogoObjectID newID1,
            /* [in] */ CogoObjectID idCenter1,
            /* [in] */ Float64 radius1,
            /* [in] */ CogoObjectID newID2,
            /* [in] */ CogoObjectID idCenter2,
            /* [in] */ Float64 radius2,
            /* [in] */ TangentSignType sign) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Point( 
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID idCenter,
            /* [in] */ Float64 radius,
            /* [in] */ CogoObjectID pointID,
            /* [in] */ TangentSignType sign) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITangentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITangent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITangent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITangent * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *External )( 
            ITangent * This,
            /* [in] */ CogoObjectID newID1,
            /* [in] */ CogoObjectID idCenter1,
            /* [in] */ Float64 radius1,
            /* [in] */ CogoObjectID newID2,
            /* [in] */ CogoObjectID idCenter2,
            /* [in] */ Float64 radius2,
            /* [in] */ TangentSignType sign);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Cross )( 
            ITangent * This,
            /* [in] */ CogoObjectID newID1,
            /* [in] */ CogoObjectID idCenter1,
            /* [in] */ Float64 radius1,
            /* [in] */ CogoObjectID newID2,
            /* [in] */ CogoObjectID idCenter2,
            /* [in] */ Float64 radius2,
            /* [in] */ TangentSignType sign);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Point )( 
            ITangent * This,
            /* [in] */ CogoObjectID newID,
            /* [in] */ CogoObjectID idCenter,
            /* [in] */ Float64 radius,
            /* [in] */ CogoObjectID pointID,
            /* [in] */ TangentSignType sign);
        
        END_INTERFACE
    } ITangentVtbl;

    interface ITangent
    {
        CONST_VTBL struct ITangentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITangent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITangent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITangent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITangent_External(This,newID1,idCenter1,radius1,newID2,idCenter2,radius2,sign)	\
    ( (This)->lpVtbl -> External(This,newID1,idCenter1,radius1,newID2,idCenter2,radius2,sign) ) 

#define ITangent_Cross(This,newID1,idCenter1,radius1,newID2,idCenter2,radius2,sign)	\
    ( (This)->lpVtbl -> Cross(This,newID1,idCenter1,radius1,newID2,idCenter2,radius2,sign) ) 

#define ITangent_Point(This,newID,idCenter,radius,pointID,sign)	\
    ( (This)->lpVtbl -> Point(This,newID,idCenter,radius,pointID,sign) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITangent_INTERFACE_DEFINED__ */


#ifndef __ITangent2_INTERFACE_DEFINED__
#define __ITangent2_INTERFACE_DEFINED__

/* interface ITangent2 */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITangent2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F51A43BB-85DD-41a1-9B32-B61D9005B0D0")
    ITangent2 : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE External( 
            /* [in] */ IPoint2d *center1,
            /* [in] */ Float64 radius1,
            /* [in] */ IPoint2d *center2,
            /* [in] */ Float64 radius2,
            /* [in] */ TangentSignType sign,
            /* [out] */ IPoint2d **t1,
            /* [out] */ IPoint2d **t2) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Cross( 
            /* [in] */ IPoint2d *center1,
            /* [in] */ Float64 radius1,
            /* [in] */ IPoint2d *center2,
            /* [in] */ Float64 radius2,
            /* [in] */ TangentSignType sign,
            /* [out] */ IPoint2d **t1,
            /* [out] */ IPoint2d **t2) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Point( 
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 radius,
            /* [in] */ IPoint2d *point,
            /* [in] */ TangentSignType sign,
            /* [out] */ IPoint2d **tangent) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITangent2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITangent2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITangent2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITangent2 * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *External )( 
            ITangent2 * This,
            /* [in] */ IPoint2d *center1,
            /* [in] */ Float64 radius1,
            /* [in] */ IPoint2d *center2,
            /* [in] */ Float64 radius2,
            /* [in] */ TangentSignType sign,
            /* [out] */ IPoint2d **t1,
            /* [out] */ IPoint2d **t2);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Cross )( 
            ITangent2 * This,
            /* [in] */ IPoint2d *center1,
            /* [in] */ Float64 radius1,
            /* [in] */ IPoint2d *center2,
            /* [in] */ Float64 radius2,
            /* [in] */ TangentSignType sign,
            /* [out] */ IPoint2d **t1,
            /* [out] */ IPoint2d **t2);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Point )( 
            ITangent2 * This,
            /* [in] */ IPoint2d *center,
            /* [in] */ Float64 radius,
            /* [in] */ IPoint2d *point,
            /* [in] */ TangentSignType sign,
            /* [out] */ IPoint2d **tangent);
        
        END_INTERFACE
    } ITangent2Vtbl;

    interface ITangent2
    {
        CONST_VTBL struct ITangent2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITangent2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITangent2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITangent2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITangent2_External(This,center1,radius1,center2,radius2,sign,t1,t2)	\
    ( (This)->lpVtbl -> External(This,center1,radius1,center2,radius2,sign,t1,t2) ) 

#define ITangent2_Cross(This,center1,radius1,center2,radius2,sign,t1,t2)	\
    ( (This)->lpVtbl -> Cross(This,center1,radius1,center2,radius2,sign,t1,t2) ) 

#define ITangent2_Point(This,center,radius,point,sign,tangent)	\
    ( (This)->lpVtbl -> Point(This,center,radius,point,sign,tangent) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITangent2_INTERFACE_DEFINED__ */


#ifndef __ICogoEngine_INTERFACE_DEFINED__
#define __ICogoEngine_INTERFACE_DEFINED__

/* interface ICogoEngine */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICogoEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF7FCB40-3E8B-45BE-B8E9-AC8ADF4DDB81")
    ICogoEngine : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Intersect( 
            /* [retval][out] */ IIntersect2 **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Locate( 
            /* [retval][out] */ ILocate2 **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Measure( 
            /* [retval][out] */ IMeasure2 **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Project( 
            /* [retval][out] */ IProject2 **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Divide( 
            /* [retval][out] */ IDivide2 **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tangent( 
            /* [retval][out] */ ITangent2 **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PointFactory( 
            /* [in] */ IPoint2dFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PointFactory( 
            /* [retval][out] */ IPoint2dFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_LineSegmentFactory( 
            /* [in] */ ILineSegment2dFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LineSegmentFactory( 
            /* [retval][out] */ ILineSegment2dFactory **factory) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICogoEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICogoEngine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICogoEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICogoEngine * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Intersect )( 
            ICogoEngine * This,
            /* [retval][out] */ IIntersect2 **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Locate )( 
            ICogoEngine * This,
            /* [retval][out] */ ILocate2 **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Measure )( 
            ICogoEngine * This,
            /* [retval][out] */ IMeasure2 **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Project )( 
            ICogoEngine * This,
            /* [retval][out] */ IProject2 **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Divide )( 
            ICogoEngine * This,
            /* [retval][out] */ IDivide2 **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tangent )( 
            ICogoEngine * This,
            /* [retval][out] */ ITangent2 **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PointFactory )( 
            ICogoEngine * This,
            /* [in] */ IPoint2dFactory *factory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointFactory )( 
            ICogoEngine * This,
            /* [retval][out] */ IPoint2dFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_LineSegmentFactory )( 
            ICogoEngine * This,
            /* [in] */ ILineSegment2dFactory *factory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineSegmentFactory )( 
            ICogoEngine * This,
            /* [retval][out] */ ILineSegment2dFactory **factory);
        
        END_INTERFACE
    } ICogoEngineVtbl;

    interface ICogoEngine
    {
        CONST_VTBL struct ICogoEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICogoEngine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICogoEngine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICogoEngine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICogoEngine_get_Intersect(This,pVal)	\
    ( (This)->lpVtbl -> get_Intersect(This,pVal) ) 

#define ICogoEngine_get_Locate(This,pVal)	\
    ( (This)->lpVtbl -> get_Locate(This,pVal) ) 

#define ICogoEngine_get_Measure(This,pVal)	\
    ( (This)->lpVtbl -> get_Measure(This,pVal) ) 

#define ICogoEngine_get_Project(This,pVal)	\
    ( (This)->lpVtbl -> get_Project(This,pVal) ) 

#define ICogoEngine_get_Divide(This,pVal)	\
    ( (This)->lpVtbl -> get_Divide(This,pVal) ) 

#define ICogoEngine_get_Tangent(This,pVal)	\
    ( (This)->lpVtbl -> get_Tangent(This,pVal) ) 

#define ICogoEngine_putref_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_PointFactory(This,factory) ) 

#define ICogoEngine_get_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> get_PointFactory(This,factory) ) 

#define ICogoEngine_putref_LineSegmentFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_LineSegmentFactory(This,factory) ) 

#define ICogoEngine_get_LineSegmentFactory(This,factory)	\
    ( (This)->lpVtbl -> get_LineSegmentFactory(This,factory) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICogoEngine_INTERFACE_DEFINED__ */


#ifndef __ICogoModel_INTERFACE_DEFINED__
#define __ICogoModel_INTERFACE_DEFINED__

/* interface ICogoModel */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICogoModel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B9E4933C-5E73-11D5-8C32-006097C68A9C")
    ICogoModel : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Points( 
            /* [retval][out] */ IPointCollection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LineSegments( 
            /* [retval][out] */ ILineSegmentCollection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProfilePoints( 
            /* [retval][out] */ IProfilePointCollection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VertCurves( 
            /* [retval][out] */ IVertCurveCollection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HorzCurves( 
            /* [retval][out] */ IHorzCurveCollection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Alignments( 
            /* [retval][out] */ IAlignmentCollection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Paths( 
            /* [retval][out] */ IPathCollection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Intersect( 
            /* [retval][out] */ IIntersect **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Locate( 
            /* [retval][out] */ ILocate **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Measure( 
            /* [retval][out] */ IMeasure **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Project( 
            /* [retval][out] */ IProject **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Divide( 
            /* [retval][out] */ IDivide **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Tangent( 
            /* [retval][out] */ ITangent **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PointFactory( 
            /* [in] */ IPoint2dFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PointFactory( 
            /* [retval][out] */ IPoint2dFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_LineSegmentFactory( 
            /* [in] */ ILineSegment2dFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LineSegmentFactory( 
            /* [retval][out] */ ILineSegment2dFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_ProfilePointFactory( 
            /* [in] */ IProfilePointFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ProfilePointFactory( 
            /* [retval][out] */ IProfilePointFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_VertCurveFactory( 
            /* [in] */ IVertCurveFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VertCurveFactory( 
            /* [retval][out] */ IVertCurveFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_HorzCurveFactory( 
            /* [in] */ IHorzCurveFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HorzCurveFactory( 
            /* [retval][out] */ IHorzCurveFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_AlignmentFactory( 
            /* [in] */ IAlignmentFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AlignmentFactory( 
            /* [retval][out] */ IAlignmentFactory **factory) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PathFactory( 
            /* [in] */ IPathFactory *factory) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PathFactory( 
            /* [retval][out] */ IPathFactory **factory) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Engine( 
            /* [retval][out] */ ICogoEngine **engine) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ICogoModel **clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICogoModelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICogoModel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICogoModel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICogoModel * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Points )( 
            ICogoModel * This,
            /* [retval][out] */ IPointCollection **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineSegments )( 
            ICogoModel * This,
            /* [retval][out] */ ILineSegmentCollection **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfilePoints )( 
            ICogoModel * This,
            /* [retval][out] */ IProfilePointCollection **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VertCurves )( 
            ICogoModel * This,
            /* [retval][out] */ IVertCurveCollection **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HorzCurves )( 
            ICogoModel * This,
            /* [retval][out] */ IHorzCurveCollection **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alignments )( 
            ICogoModel * This,
            /* [retval][out] */ IAlignmentCollection **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Paths )( 
            ICogoModel * This,
            /* [retval][out] */ IPathCollection **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ICogoModel * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Intersect )( 
            ICogoModel * This,
            /* [retval][out] */ IIntersect **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Locate )( 
            ICogoModel * This,
            /* [retval][out] */ ILocate **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Measure )( 
            ICogoModel * This,
            /* [retval][out] */ IMeasure **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Project )( 
            ICogoModel * This,
            /* [retval][out] */ IProject **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Divide )( 
            ICogoModel * This,
            /* [retval][out] */ IDivide **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tangent )( 
            ICogoModel * This,
            /* [retval][out] */ ITangent **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PointFactory )( 
            ICogoModel * This,
            /* [in] */ IPoint2dFactory *factory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointFactory )( 
            ICogoModel * This,
            /* [retval][out] */ IPoint2dFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_LineSegmentFactory )( 
            ICogoModel * This,
            /* [in] */ ILineSegment2dFactory *factory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineSegmentFactory )( 
            ICogoModel * This,
            /* [retval][out] */ ILineSegment2dFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ProfilePointFactory )( 
            ICogoModel * This,
            /* [in] */ IProfilePointFactory *factory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfilePointFactory )( 
            ICogoModel * This,
            /* [retval][out] */ IProfilePointFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_VertCurveFactory )( 
            ICogoModel * This,
            /* [in] */ IVertCurveFactory *factory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VertCurveFactory )( 
            ICogoModel * This,
            /* [retval][out] */ IVertCurveFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HorzCurveFactory )( 
            ICogoModel * This,
            /* [in] */ IHorzCurveFactory *factory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HorzCurveFactory )( 
            ICogoModel * This,
            /* [retval][out] */ IHorzCurveFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_AlignmentFactory )( 
            ICogoModel * This,
            /* [in] */ IAlignmentFactory *factory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlignmentFactory )( 
            ICogoModel * This,
            /* [retval][out] */ IAlignmentFactory **factory);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PathFactory )( 
            ICogoModel * This,
            /* [in] */ IPathFactory *factory);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PathFactory )( 
            ICogoModel * This,
            /* [retval][out] */ IPathFactory **factory);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Engine )( 
            ICogoModel * This,
            /* [retval][out] */ ICogoEngine **engine);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ICogoModel * This,
            /* [retval][out] */ ICogoModel **clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICogoModel * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ICogoModelVtbl;

    interface ICogoModel
    {
        CONST_VTBL struct ICogoModelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICogoModel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICogoModel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICogoModel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICogoModel_get_Points(This,pVal)	\
    ( (This)->lpVtbl -> get_Points(This,pVal) ) 

#define ICogoModel_get_LineSegments(This,pVal)	\
    ( (This)->lpVtbl -> get_LineSegments(This,pVal) ) 

#define ICogoModel_get_ProfilePoints(This,pVal)	\
    ( (This)->lpVtbl -> get_ProfilePoints(This,pVal) ) 

#define ICogoModel_get_VertCurves(This,pVal)	\
    ( (This)->lpVtbl -> get_VertCurves(This,pVal) ) 

#define ICogoModel_get_HorzCurves(This,pVal)	\
    ( (This)->lpVtbl -> get_HorzCurves(This,pVal) ) 

#define ICogoModel_get_Alignments(This,pVal)	\
    ( (This)->lpVtbl -> get_Alignments(This,pVal) ) 

#define ICogoModel_get_Paths(This,pVal)	\
    ( (This)->lpVtbl -> get_Paths(This,pVal) ) 

#define ICogoModel_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ICogoModel_get_Intersect(This,pVal)	\
    ( (This)->lpVtbl -> get_Intersect(This,pVal) ) 

#define ICogoModel_get_Locate(This,pVal)	\
    ( (This)->lpVtbl -> get_Locate(This,pVal) ) 

#define ICogoModel_get_Measure(This,pVal)	\
    ( (This)->lpVtbl -> get_Measure(This,pVal) ) 

#define ICogoModel_get_Project(This,pVal)	\
    ( (This)->lpVtbl -> get_Project(This,pVal) ) 

#define ICogoModel_get_Divide(This,pVal)	\
    ( (This)->lpVtbl -> get_Divide(This,pVal) ) 

#define ICogoModel_get_Tangent(This,pVal)	\
    ( (This)->lpVtbl -> get_Tangent(This,pVal) ) 

#define ICogoModel_putref_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_PointFactory(This,factory) ) 

#define ICogoModel_get_PointFactory(This,factory)	\
    ( (This)->lpVtbl -> get_PointFactory(This,factory) ) 

#define ICogoModel_putref_LineSegmentFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_LineSegmentFactory(This,factory) ) 

#define ICogoModel_get_LineSegmentFactory(This,factory)	\
    ( (This)->lpVtbl -> get_LineSegmentFactory(This,factory) ) 

#define ICogoModel_putref_ProfilePointFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_ProfilePointFactory(This,factory) ) 

#define ICogoModel_get_ProfilePointFactory(This,factory)	\
    ( (This)->lpVtbl -> get_ProfilePointFactory(This,factory) ) 

#define ICogoModel_putref_VertCurveFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_VertCurveFactory(This,factory) ) 

#define ICogoModel_get_VertCurveFactory(This,factory)	\
    ( (This)->lpVtbl -> get_VertCurveFactory(This,factory) ) 

#define ICogoModel_putref_HorzCurveFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_HorzCurveFactory(This,factory) ) 

#define ICogoModel_get_HorzCurveFactory(This,factory)	\
    ( (This)->lpVtbl -> get_HorzCurveFactory(This,factory) ) 

#define ICogoModel_putref_AlignmentFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_AlignmentFactory(This,factory) ) 

#define ICogoModel_get_AlignmentFactory(This,factory)	\
    ( (This)->lpVtbl -> get_AlignmentFactory(This,factory) ) 

#define ICogoModel_putref_PathFactory(This,factory)	\
    ( (This)->lpVtbl -> putref_PathFactory(This,factory) ) 

#define ICogoModel_get_PathFactory(This,factory)	\
    ( (This)->lpVtbl -> get_PathFactory(This,factory) ) 

#define ICogoModel_get_Engine(This,engine)	\
    ( (This)->lpVtbl -> get_Engine(This,engine) ) 

#define ICogoModel_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ICogoModel_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICogoModel_INTERFACE_DEFINED__ */


#ifndef __ICogoModelEvents_INTERFACE_DEFINED__
#define __ICogoModelEvents_INTERFACE_DEFINED__

/* interface ICogoModelEvents */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICogoModelEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BBD4B66A-6102-11d5-8C3A-006097C68A9C")
    ICogoModelEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointChanged( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointAdded( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *point) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointRemoved( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointsCleared( 
            /* [in] */ ICogoModel *cm) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLineSegmentChanged( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *lineSeg) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLineSegmentAdded( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *lineSeg) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLineSegmentRemoved( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLineSegmentsCleared( 
            /* [in] */ ICogoModel *cm) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfilePointChanged( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *pp) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfilePointAdded( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *pp) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfilePointRemoved( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfilePointsCleared( 
            /* [in] */ ICogoModel *cm) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVertCurveChanged( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *vc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVertCurveAdded( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *vc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVertCurveRemoved( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVertCurvesCleared( 
            /* [in] */ ICogoModel *cm) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnHorzCurveChanged( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *vc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnHorzCurveAdded( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *vc) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnHorzCurveRemoved( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnHorzCurvesCleared( 
            /* [in] */ ICogoModel *cm) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnProfileChanged( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ IProfile *profile) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStationEquationsChanged( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ IStationEquationCollection *equations) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAlignmentChanged( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *alignment) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAlignmentAdded( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *alignment) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAlignmentRemoved( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAlignmentsCleared( 
            /* [in] */ ICogoModel *cm) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPathChanged( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPathAdded( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *path) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPathRemoved( 
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPathsCleared( 
            /* [in] */ ICogoModel *cm) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICogoModelEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICogoModelEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICogoModelEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICogoModelEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointChanged )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointAdded )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPoint2d *point);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointRemoved )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointsCleared )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLineSegmentChanged )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *lineSeg);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLineSegmentAdded )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ ILineSegment2d *lineSeg);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLineSegmentRemoved )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLineSegmentsCleared )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfilePointChanged )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *pp);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfilePointAdded )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IProfilePoint *pp);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfilePointRemoved )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfilePointsCleared )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVertCurveChanged )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *vc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVertCurveAdded )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IVertCurve *vc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVertCurveRemoved )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVertCurvesCleared )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnHorzCurveChanged )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *vc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnHorzCurveAdded )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IHorzCurve *vc);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnHorzCurveRemoved )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnHorzCurvesCleared )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnProfileChanged )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ IProfile *profile);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStationEquationsChanged )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ IStationEquationCollection *equations);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAlignmentChanged )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *alignment);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAlignmentAdded )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IAlignment *alignment);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAlignmentRemoved )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAlignmentsCleared )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPathChanged )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPathAdded )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id,
            /* [in] */ IPath *path);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPathRemoved )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm,
            /* [in] */ CogoObjectID id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPathsCleared )( 
            ICogoModelEvents * This,
            /* [in] */ ICogoModel *cm);
        
        END_INTERFACE
    } ICogoModelEventsVtbl;

    interface ICogoModelEvents
    {
        CONST_VTBL struct ICogoModelEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICogoModelEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICogoModelEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICogoModelEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICogoModelEvents_OnPointChanged(This,cm,id,point)	\
    ( (This)->lpVtbl -> OnPointChanged(This,cm,id,point) ) 

#define ICogoModelEvents_OnPointAdded(This,cm,id,point)	\
    ( (This)->lpVtbl -> OnPointAdded(This,cm,id,point) ) 

#define ICogoModelEvents_OnPointRemoved(This,cm,id)	\
    ( (This)->lpVtbl -> OnPointRemoved(This,cm,id) ) 

#define ICogoModelEvents_OnPointsCleared(This,cm)	\
    ( (This)->lpVtbl -> OnPointsCleared(This,cm) ) 

#define ICogoModelEvents_OnLineSegmentChanged(This,cm,id,lineSeg)	\
    ( (This)->lpVtbl -> OnLineSegmentChanged(This,cm,id,lineSeg) ) 

#define ICogoModelEvents_OnLineSegmentAdded(This,cm,id,lineSeg)	\
    ( (This)->lpVtbl -> OnLineSegmentAdded(This,cm,id,lineSeg) ) 

#define ICogoModelEvents_OnLineSegmentRemoved(This,cm,id)	\
    ( (This)->lpVtbl -> OnLineSegmentRemoved(This,cm,id) ) 

#define ICogoModelEvents_OnLineSegmentsCleared(This,cm)	\
    ( (This)->lpVtbl -> OnLineSegmentsCleared(This,cm) ) 

#define ICogoModelEvents_OnProfilePointChanged(This,cm,id,pp)	\
    ( (This)->lpVtbl -> OnProfilePointChanged(This,cm,id,pp) ) 

#define ICogoModelEvents_OnProfilePointAdded(This,cm,id,pp)	\
    ( (This)->lpVtbl -> OnProfilePointAdded(This,cm,id,pp) ) 

#define ICogoModelEvents_OnProfilePointRemoved(This,cm,id)	\
    ( (This)->lpVtbl -> OnProfilePointRemoved(This,cm,id) ) 

#define ICogoModelEvents_OnProfilePointsCleared(This,cm)	\
    ( (This)->lpVtbl -> OnProfilePointsCleared(This,cm) ) 

#define ICogoModelEvents_OnVertCurveChanged(This,cm,id,vc)	\
    ( (This)->lpVtbl -> OnVertCurveChanged(This,cm,id,vc) ) 

#define ICogoModelEvents_OnVertCurveAdded(This,cm,id,vc)	\
    ( (This)->lpVtbl -> OnVertCurveAdded(This,cm,id,vc) ) 

#define ICogoModelEvents_OnVertCurveRemoved(This,cm,id)	\
    ( (This)->lpVtbl -> OnVertCurveRemoved(This,cm,id) ) 

#define ICogoModelEvents_OnVertCurvesCleared(This,cm)	\
    ( (This)->lpVtbl -> OnVertCurvesCleared(This,cm) ) 

#define ICogoModelEvents_OnHorzCurveChanged(This,cm,id,vc)	\
    ( (This)->lpVtbl -> OnHorzCurveChanged(This,cm,id,vc) ) 

#define ICogoModelEvents_OnHorzCurveAdded(This,cm,id,vc)	\
    ( (This)->lpVtbl -> OnHorzCurveAdded(This,cm,id,vc) ) 

#define ICogoModelEvents_OnHorzCurveRemoved(This,cm,id)	\
    ( (This)->lpVtbl -> OnHorzCurveRemoved(This,cm,id) ) 

#define ICogoModelEvents_OnHorzCurvesCleared(This,cm)	\
    ( (This)->lpVtbl -> OnHorzCurvesCleared(This,cm) ) 

#define ICogoModelEvents_OnProfileChanged(This,cm,profile)	\
    ( (This)->lpVtbl -> OnProfileChanged(This,cm,profile) ) 

#define ICogoModelEvents_OnStationEquationsChanged(This,cm,equations)	\
    ( (This)->lpVtbl -> OnStationEquationsChanged(This,cm,equations) ) 

#define ICogoModelEvents_OnAlignmentChanged(This,cm,id,alignment)	\
    ( (This)->lpVtbl -> OnAlignmentChanged(This,cm,id,alignment) ) 

#define ICogoModelEvents_OnAlignmentAdded(This,cm,id,alignment)	\
    ( (This)->lpVtbl -> OnAlignmentAdded(This,cm,id,alignment) ) 

#define ICogoModelEvents_OnAlignmentRemoved(This,cm,id)	\
    ( (This)->lpVtbl -> OnAlignmentRemoved(This,cm,id) ) 

#define ICogoModelEvents_OnAlignmentsCleared(This,cm)	\
    ( (This)->lpVtbl -> OnAlignmentsCleared(This,cm) ) 

#define ICogoModelEvents_OnPathChanged(This,cm,id,path)	\
    ( (This)->lpVtbl -> OnPathChanged(This,cm,id,path) ) 

#define ICogoModelEvents_OnPathAdded(This,cm,id,path)	\
    ( (This)->lpVtbl -> OnPathAdded(This,cm,id,path) ) 

#define ICogoModelEvents_OnPathRemoved(This,cm,id)	\
    ( (This)->lpVtbl -> OnPathRemoved(This,cm,id) ) 

#define ICogoModelEvents_OnPathsCleared(This,cm)	\
    ( (This)->lpVtbl -> OnPathsCleared(This,cm) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICogoModelEvents_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Angle;

#ifdef __cplusplus

class DECLSPEC_UUID("10F574FD-5735-11D3-898C-006097C68A9C")
Angle;
#endif

EXTERN_C const CLSID CLSID_Direction;

#ifdef __cplusplus

class DECLSPEC_UUID("10F574FB-5735-11D3-898C-006097C68A9C")
Direction;
#endif

EXTERN_C const CLSID CLSID_PointCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("5559C9A6-5C16-11D5-8C31-006097C68A9C")
PointCollection;
#endif

EXTERN_C const CLSID CLSID_LineSegmentCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("9E0F9B9E-99C9-40A8-9C08-47E6ACD762E9")
LineSegmentCollection;
#endif

EXTERN_C const CLSID CLSID_CogoModel;

#ifdef __cplusplus

class DECLSPEC_UUID("07E3C485-573F-11D3-8CDF-BAAC148B6002")
CogoModel;
#endif

EXTERN_C const CLSID CLSID_ProfilePoint;

#ifdef __cplusplus

class DECLSPEC_UUID("849FD333-4FC9-4093-93F6-FBEC311FF45A")
ProfilePoint;
#endif

EXTERN_C const CLSID CLSID_ProfilePointCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("3B3D6F38-F5B7-4621-B276-5421717846E2")
ProfilePointCollection;
#endif

EXTERN_C const CLSID CLSID_VertCurve;

#ifdef __cplusplus

class DECLSPEC_UUID("7581BC4E-4E7C-4761-B59E-2D75EA2E1120")
VertCurve;
#endif

EXTERN_C const CLSID CLSID_VertCurveCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("D6732CA5-6E4F-45FE-A4FC-B0E8A94667FA")
VertCurveCollection;
#endif

EXTERN_C const CLSID CLSID_HorzCurve;

#ifdef __cplusplus

class DECLSPEC_UUID("61454EB9-8040-4B74-9429-B09D1FF1E0BB")
HorzCurve;
#endif

EXTERN_C const CLSID CLSID_HorzCurveCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("2C4945D1-9B56-430C-B395-B07209328C59")
HorzCurveCollection;
#endif

EXTERN_C const CLSID CLSID_CubicSpline;

#ifdef __cplusplus

class DECLSPEC_UUID("69706DA8-D10D-4932-A566-69DE35CAF30F")
CubicSpline;
#endif

EXTERN_C const CLSID CLSID_ProfileElement;

#ifdef __cplusplus

class DECLSPEC_UUID("80AC919F-D882-4C24-9E6D-721D90925FEE")
ProfileElement;
#endif

EXTERN_C const CLSID CLSID_Profile;

#ifdef __cplusplus

class DECLSPEC_UUID("7FD9C064-1A8C-4853-B1CC-24D9C877406F")
Profile;
#endif

EXTERN_C const CLSID CLSID_Widening;

#ifdef __cplusplus

class DECLSPEC_UUID("3B817FBD-D099-49a2-8E43-E90F49A8B5B8")
Widening;
#endif

EXTERN_C const CLSID CLSID_WideningCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("9AD670B4-C5FE-4639-A714-67008906B54D")
WideningCollection;
#endif

EXTERN_C const CLSID CLSID_Superelevation;

#ifdef __cplusplus

class DECLSPEC_UUID("9D3C25CB-61D1-466e-AE30-1FD5C460D50B")
Superelevation;
#endif

EXTERN_C const CLSID CLSID_SuperelevationCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("981C286A-8B4B-4be9-BB9D-E927FFFF680C")
SuperelevationCollection;
#endif

EXTERN_C const CLSID CLSID_TemplateSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("B853F944-3791-4f03-AC3C-547C71B74743")
TemplateSegment;
#endif

EXTERN_C const CLSID CLSID_SurfaceTemplate;

#ifdef __cplusplus

class DECLSPEC_UUID("A479017E-BFE5-4e1e-B41D-E7BBF2534F52")
SurfaceTemplate;
#endif

EXTERN_C const CLSID CLSID_SurfaceTemplateCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("D3148A9A-D53F-45d0-A0B7-A03EE35A36F3")
SurfaceTemplateCollection;
#endif

EXTERN_C const CLSID CLSID_Surface;

#ifdef __cplusplus

class DECLSPEC_UUID("B8A4A5A2-A456-4161-9276-669D92B9FC5C")
Surface;
#endif

EXTERN_C const CLSID CLSID_SurfaceCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("A0AE194C-0D1D-4acb-8514-85E4B77DD326")
SurfaceCollection;
#endif

EXTERN_C const CLSID CLSID_PathElement;

#ifdef __cplusplus

class DECLSPEC_UUID("B21FFF37-F9A2-4DA0-8226-C5C3604E8262")
PathElement;
#endif

EXTERN_C const CLSID CLSID_Alignment;

#ifdef __cplusplus

class DECLSPEC_UUID("B46F91AB-53C2-4ECC-8E7F-55AFA0F67C2F")
Alignment;
#endif

EXTERN_C const CLSID CLSID_AlignmentCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("9B77429D-4A92-4ddd-BAFA-4330EEAF167C")
AlignmentCollection;
#endif

EXTERN_C const CLSID CLSID_Path;

#ifdef __cplusplus

class DECLSPEC_UUID("4A138368-CF5F-4a12-BC2D-224FC85E8B8D")
Path;
#endif

EXTERN_C const CLSID CLSID_PathCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("BB37DF4F-8AD0-4778-9036-9A340F425A50")
PathCollection;
#endif

EXTERN_C const CLSID CLSID_VertCurveFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("B61E5354-A04C-439D-9661-309897677112")
VertCurveFactory;
#endif

EXTERN_C const CLSID CLSID_ProfilePointFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("43AB1FB8-3A38-40FE-99A1-8CA49982037D")
ProfilePointFactory;
#endif

EXTERN_C const CLSID CLSID_HorzCurveFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("FC1BF8D1-D732-4C86-B98C-4B08E3C9E61E")
HorzCurveFactory;
#endif

EXTERN_C const CLSID CLSID_PathFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("016F7CE4-7013-47db-88EA-BBF0EA82AA30")
PathFactory;
#endif

EXTERN_C const CLSID CLSID_AlignmentFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("302F2E74-E561-4275-8C4E-3451EC5FD757")
AlignmentFactory;
#endif

EXTERN_C const CLSID CLSID_AngleDisplayUnitFormatter;

#ifdef __cplusplus

class DECLSPEC_UUID("0E8ADC7B-54A5-45FC-AA79-56BBE528FA47")
AngleDisplayUnitFormatter;
#endif

EXTERN_C const CLSID CLSID_DirectionDisplayUnitFormatter;

#ifdef __cplusplus

class DECLSPEC_UUID("50A4E50C-B7A8-4177-AB25-83D4E783B7A3")
DirectionDisplayUnitFormatter;
#endif

EXTERN_C const CLSID CLSID_PointFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("F0151EC9-C520-4ec7-9581-35FC1685FAAB")
PointFactory;
#endif

EXTERN_C const CLSID CLSID_LineSegmentFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("B290D560-4DFC-404c-8CAF-CFBFE211234D")
LineSegmentFactory;
#endif

EXTERN_C const CLSID CLSID_Station;

#ifdef __cplusplus

class DECLSPEC_UUID("4C22AA8F-6739-49DD-B6DF-FDCD352FF969")
Station;
#endif

EXTERN_C const CLSID CLSID_StationEquation;

#ifdef __cplusplus

class DECLSPEC_UUID("ABC35194-EDA2-4fa3-AC6B-B58A5F0C2385")
StationEquation;
#endif

EXTERN_C const CLSID CLSID_StationEquationCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("000FDA40-7B33-4354-8ADF-9E28D4EEE2D3")
StationEquationCollection;
#endif

EXTERN_C const CLSID CLSID_CogoEngine;

#ifdef __cplusplus

class DECLSPEC_UUID("C7E7D393-7C90-4AF5-88DF-A761FA3BCE19")
CogoEngine;
#endif

EXTERN_C const CLSID CLSID_SurfacePoint;

#ifdef __cplusplus

class DECLSPEC_UUID("D83C292A-4677-46ef-BEF2-CF9444A5D8E5")
SurfacePoint;
#endif

EXTERN_C const CLSID CLSID_SurfaceProfile;

#ifdef __cplusplus

class DECLSPEC_UUID("1B216215-3EEC-407e-BBEC-52BB0C0FBCBD")
SurfaceProfile;
#endif
#endif /* __WBFLCogo_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


