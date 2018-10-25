///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_PRIMITIVES_HH_
#define INCLUDED_PRIMITIVES_HH_

#define IDH_ISize2d                    100
#define IDH_ISize2d_Dx                 101
#define IDH_ISize2d_Dy                 102
#define IDH_ISize2d_Magnitude          103
#define IDH_ISize2d_Scale              104
#define IDH_ISize2d_Dimensions         105

#define IDH_IPoint2d                   200
#define IDH_IPoint2d_X                 201
#define IDH_IPoint2d_Y                 202
#define IDH_IPoint2d_Move              203
#define IDH_IPoint2d_MoveEx            204
#define IDH_IPoint2d_Offset            205
#define IDH_IPoint2d_OffsetEx          206
#define IDH_IPoint2d_Rotate            207
#define IDH_IPoint2d_RotateEx          208
#define IDH_IPoint2d_OnChanged         209
#define IDH_IPoint2d_SameLocation      210
#define IDH_IPoint2d_Location          211
#define IDH_IPoint2d_Distance          212
#define IDH_IPoint2d_DistanceEx        213

#define IDH_IRect2d                    300
#define IDH_IRect2d_Area               301
#define IDH_IRect2d_Bottom             302
#define IDH_IRect2d_BottomCenter       303
#define IDH_IRect2d_BottomLeft         304
#define IDH_IRect2d_BottomRight        305
#define IDH_IRect2d_BoundPoint         306
#define IDH_IRect2d_BoundPointEx       307
#define IDH_IRect2d_CenterCenter       308
#define IDH_IRect2d_ContainsPoint      309
#define IDH_IRect2d_ContainsRect       310
#define IDH_IRect2d_Height             311
#define IDH_IRect2d_Inflate            312
#define IDH_IRect2d_InflateEx          313
#define IDH_IRect2d_Intersect          314
#define IDH_IRect2d_IsNormalized       315
#define IDH_IRect2d_IsNull             316
#define IDH_IRect2d_Left               317
#define IDH_IRect2d_CenterLeft         318
#define IDH_IRect2d_Normalize          319
#define IDH_IRect2d_Offset             320
#define IDH_IRect2d_OffsetEx           321
#define IDH_IRect2d_Right              322
#define IDH_IRect2d_CenterRight        323
#define IDH_IRect2d_SetEmpty           324
#define IDH_IRect2d_SetNull            325
#define IDH_IRect2d_Size               326
#define IDH_IRect2d_Top                327
#define IDH_IRect2d_TopCenter          328
#define IDH_IRect2d_TopLeft            329
#define IDH_IRect2d_TopRight           330
#define IDH_IRect2d_Touches            331
#define IDH_IRect2d_Union              332
#define IDH_IRect2d_UnionBy            333
#define IDH_IRect2d_Width              334

#define IDH_IVector2d                  400
#define IDH_IVector2d_AngleBetween     401
#define IDH_IVector2d_Direction        402
#define IDH_IVector2d_Dot              403
#define IDH_IVector2d_IsZero           404
#define IDH_IVector2d_Magnitude        405
#define IDH_IVector2d_Normal           406
#define IDH_IVector2d_Normalize        407
#define IDH_IVector2d_Offset           408
#define IDH_IVector2d_OffsetEx         409
#define IDH_IVector2d_Projection       410
#define IDH_IVector2d_Reflect          411
#define IDH_IVector2d_Rotate           412
#define IDH_IVector2d_Scale            413
#define IDH_IVector2d_Size             414
#define IDH_IVector2d_X                415
#define IDH_IVector2d_Y                416
#define IDH_IVector2d_IncrementBy      417
#define IDH_IVector2d_Increment        418
#define IDH_IVector2d_DecrementBy      419
#define IDH_IVector2d_Decrement        420

#define IDH_ILineSegment2d             500
#define IDH_ILineSegment2d_StartPoint  501
#define IDH_ILineSegment2d_EndPoint    502
#define IDH_ILineSegment2d_Length      503
#define IDH_ILineSegment2d_Offset      504
#define IDH_ILineSegment2d_OffsetEx    505
#define IDH_ILineSegment2d_Rotate      506
#define IDH_ILineSegment2d_RotateEx    507
#define IDH_ILineSegment2d_OnChanged   508

#define IDH_ILine2d                    600
#define IDH_ILine2d_GetExplicit        601
#define IDH_ILine2d_GetImplicit        602
#define IDH_ILine2d_Offset             603
#define IDH_ILine2d_Rotate             604
#define IDH_ILine2d_RotateEx           605
#define IDH_ILine2d_SetExplicit        606
#define IDH_ILine2d_SetImplicit        607
#define IDH_ILine2d_ThroughPoints      608
#define IDH_ILine2d_Reverse			   609

#define IDH_ISize3d                    700
#define IDH_ISize3d_Dx                 701
#define IDH_ISize3d_Dy                 702
#define IDH_ISize3d_Dz                 703
#define IDH_ISize3d_Magnitude          704
#define IDH_ISize3d_Scale              705
#define IDH_ISize3d_Dimensions         706

#define IDH_IPoint3d                   800
#define IDH_IPoint3d_X                 801
#define IDH_IPoint3d_Y                 802
#define IDH_IPoint3d_Z                 803
#define IDH_IPoint3d_Move              804
#define IDH_IPoint3d_MoveEx            805
#define IDH_IPoint3d_Offset            806
#define IDH_IPoint3d_OffsetEx          807
#define IDH_IPoint3d_Rotate            808
#define IDH_IPoint3d_RotateEx          809
#define IDH_IPoint3d_OnChanged         810
#define IDH_IPoint3d_SameLocation      811
#define IDH_IPoint3d_Location          812

#define IDH_IPoint2dCollection                    900
#define IDH_IPoint2dCollection__Enum              901
#define IDH_IPoint2dCollection_Add                902
#define IDH_IPoint2dCollection_Clear              903
#define IDH_IPoint2dCollection_Count              904
#define IDH_IPoint2dCollection_Item               905
#define IDH_IPoint2dCollection_Remove             906
#define IDH_IPoint2dCollection_OnPoint2dsChanged  907
#define IDH_IPoint2dCollection_OnPoint2dAdded     908
#define IDH_IPoint2dCollection_OnPoint2dRemoved   909
#define IDH_IPoint2dCollection_OnPoint2dsCleared  910

#define IDH_ICircle                    1000
#define IDH_ICircle_Center             1001
#define IDH_ICircle_Radius             1002
#define IDH_ICircle_XYPosition         1003
#define IDH_ICircle_Shape              1004
#define IDH_ICircle_ThroughTwoPoints   1005
#define IDH_ICircle_ThroughThreePoints 1006
#define IDH_ICircle_ContainsPoint      1007
#define IDH_ICircle_PointOnCircle      1008

#define IDH_ICircularSegment                1050
#define IDH_ICircularSegment_Center         1051
#define IDH_ICircularSegment_HookPoint      1052
#define IDH_ICircularSegment_InteriorAngle  1053
#define IDH_ICircularSegment_MidOrdinate    1054
#define IDH_ICircularSegment_Radius         1055
#define IDH_ICircularSegment_Rotation       1056
#define IDH_ICircularSegment_Shape          1057
#define IDH_ICircularSegment_XYPosition     1058

#define IDH_ICoordinateXform2d         1100
#define IDH_ICoordinateXform2d_NewOrigin 1101
#define IDH_ICoordinateXform2d_RotationAngle 1102
#define IDH_ICoordinateXform2d_Xform   1103
#define IDH_ICoordinateXform2d_XformEx 1104

#define IDH_ICoordinateXform3d         1200
#define IDH_ICoordinateXform3d_NewOrigin 1201
#define IDH_ICoordinateXform3d_RotationAngle 1202
#define IDH_ICoordinateXform3d_RotationVector 1203
#define IDH_ICoordinateXform3d_Xform   1204
#define IDH_ICoordinateXform3d_XformEx 1205

#define IDH_IPoint3dCollection                    1300
#define IDH_IPoint3dCollection__Enum              1301
#define IDH_IPoint3dCollection_Add                1302
#define IDH_IPoint3dCollection_Clear              1303
#define IDH_IPoint3dCollection_Count              1304
#define IDH_IPoint3dCollection_Item               1305
#define IDH_IPoint3dCollection_Remove             1306
#define IDH_IPoint3dCollection_OnPoint3dsChanged  1307
#define IDH_IPoint3dCollection_OnPoint3dAdded     1308
#define IDH_IPoint3dCollection_OnPoint3dRemoved   1309
#define IDH_IPoint3dCollection_OnPoint3dsCleared  1310

#define IDH_IPolyShape                 1400
#define IDH_IPolyShape_AddPoint        1401
#define IDH_IPolyShape_AddPointEx      1402
#define IDH_IPolyShape_AddPoints       1403
#define IDH_IPolyShape_Clear           1404
#define IDH_IPolyShape_NumPoints       1405
#define IDH_IPolyShape_Point           1406
#define IDH_IPolyShape_Points          1407
#define IDH_IPolyShape_RemovePoint     1408
#define IDH_IPolyShape_Shape           1409
#define IDH_IPolyShape_XYPosition      1410

#define IDH_IVector3d                  1500
#define IDH_IVector3d_AngleBetween     1501
#define IDH_IVector3d_Cross            1502
#define IDH_IVector3d_Dot              1503
#define IDH_IVector3d_IsZero           1504
#define IDH_IVector3d_Magnitude        1505
#define IDH_IVector3d_Normalize        1506
#define IDH_IVector3d_Offset           1507
#define IDH_IVector3d_OffsetEx         1508
#define IDH_IVector3d_Projection       1509
#define IDH_IVector3d_Reflect          1510
#define IDH_IVector3d_Scale            1511
#define IDH_IVector3d_Size             1512
#define IDH_IVector3d_X                1513
#define IDH_IVector3d_Y                1514
#define IDH_IVector3d_Z                1515
#define IDH_IVector3d_IncrementBy      1516
#define IDH_IVector3d_Increment        1517
#define IDH_IVector3d_DecrementBy      1518
#define IDH_IVector3d_Decrement        1519

#define IDH_IPlane3d                   1600
#define IDH_IPlane3d_ThroughAltitude   1601
#define IDH_IPlane3d_ThroughLineEx     1602
#define IDH_IPlane3d_ThroughPoints     1603
#define IDH_IPlane3d_GetX              1604
#define IDH_IPlane3d_GetY              1605
#define IDH_IPlane3d_GetZ              1606
#define IDH_IPlane3d_Clone			   1607

#define IDH_PrimitiveFactory                         1700
#define IDH_ILine2dFactory                           1710
#define IDH_ILine2dFactory_CreateLine                1711
#define IDH_ILineSegment2dFactory                    1720
#define IDH_ILineSegment2dFactory_CreateLineSegment  1721
#define IDH_IPoint2dFactory                          1730
#define IDH_IPoint2dFactory_CreatePoint              1731
#define IDH_IPoint3dFactory                          1740
#define IDH_IPoint3dFactory_CreatePoint              1741

#define IDH_IPrecastBeam                             1800
#define IDH_IPrecastBeam_W1                          1801
#define IDH_IPrecastBeam_W2                          1802
#define IDH_IPrecastBeam_W3                          1803
#define IDH_IPrecastBeam_W4                          1804
#define IDH_IPrecastBeam_D1                          1805
#define IDH_IPrecastBeam_D2                          1806
#define IDH_IPrecastBeam_D3                          1807
#define IDH_IPrecastBeam_D4                          1808
#define IDH_IPrecastBeam_D5                          1809
#define IDH_IPrecastBeam_D6                          1810
#define IDH_IPrecastBeam_D7                          1811
#define IDH_IPrecastBeam_T1                          1812
#define IDH_IPrecastBeam_T2                          1813
#define IDH_IPrecastBeam_HookPoint                   1814
#define IDH_IPrecastBeam_Height                      1815
#define IDH_IPrecastBeam_AvgWebWidth                 1816
#define IDH_IPrecastBeam_BottomFlangeWidth           1817
#define IDH_IPrecastBeam_TopFlangeWidth              1818
#define IDH_IPrecastBeam_XYPosition                  1819
#define IDH_IPrecastBeam_Shape                       1820
#define IDH_IPrecastBeam_C1                          1821


#define IDH_IBulbTee                             1830
#define IDH_IBulbTee_W1                          1831
#define IDH_IBulbTee_W2                          1832
#define IDH_IBulbTee_W3                          1833
#define IDH_IBulbTee_W4                          1834
#define IDH_IBulbTee_W5                          1835
#define IDH_IBulbTee_D1                          1836
#define IDH_IBulbTee_D2                          1837
#define IDH_IBulbTee_D3                          1838
#define IDH_IBulbTee_D4                          1839
#define IDH_IBulbTee_D5                          1840
#define IDH_IBulbTee_D6                          1841
#define IDH_IBulbTee_D7                          1842
#define IDH_IBulbTee_T1                          1843
#define IDH_IBulbTee_T2                          1844
#define IDH_IBulbTee_HookPoint                   1844
#define IDH_IBulbTee_Height                      1846
#define IDH_IBulbTee_AvgWebWidth                 1847
#define IDH_IBulbTee_BottomFlangeWidth           1848
#define IDH_IBulbTee_TopFlangeWidth              1849
#define IDH_IBulbTee_XYPosition                  1850
#define IDH_IBulbTee_Shape                       1851
#define IDH_IBulbTee_C1                          1852

#define IDH_INUBeam                                  1860
#define IDH_INUBeam_W1                               1861
#define IDH_INUBeam_W2                               1862
#define IDH_INUBeam_D1                               1863
#define IDH_INUBeam_D2                               1864
#define IDH_INUBeam_D3                               1865
#define IDH_INUBeam_D4                               1866
#define IDH_INUBeam_D5                               1867
#define IDH_INUBeam_T                                1868
#define IDH_INUBeam_R1                               1869
#define IDH_INUBeam_R2                               1870
#define IDH_INUBeam_R3                               1871
#define IDH_INUBeam_R4                               1872
#define IDH_INUBeam_C1                               1873
#define IDH_INUBeam_HookPoint                        1874
#define IDH_INUBeam_Height                           1875
#define IDH_INUBeam_AvgWebWidth                      1876
#define IDH_INUBeam_BottomFlangeWidth                1877
#define IDH_INUBeam_TopFlangeWidth                   1878
#define IDH_INUBeam_XYPosition                       1879
#define IDH_INUBeam_Shape                            1880

#define IDH_ITrafficBarrier                          1900
#define IDH_ITrafficBarrier_X1                       1901
#define IDH_ITrafficBarrier_X2                       1902
#define IDH_ITrafficBarrier_X3                       1903
#define IDH_ITrafficBarrier_X4                       1904
#define IDH_ITrafficBarrier_X5                       1905
#define IDH_ITrafficBarrier_Y1                       1906
#define IDH_ITrafficBarrier_Y2                       1907
#define IDH_ITrafficBarrier_Y3                       1908
#define IDH_ITrafficBarrier_Y4                       1909
#define IDH_ITrafficBarrier_HookPoint                1910
#define IDH_ITrafficBarrier_Orientation              1911
#define IDH_ITrafficBarrier_XYPosition               1912
#define IDH_ITrafficBarrier_Shape                    1913

#define IDH_IRectangle                               2000
#define IDH_IRectangle_Height                        2001
#define IDH_IRectangle_Width                         2002
#define IDH_IRectangle_HookPoint                     2003
#define IDH_IRectangle_XYPosition                    2004
#define IDH_IRectangle_Shape                         2005

#define IDH_CoordinateSystemType                     2100
#define IDH_LocatorPointType                         2101
#define IDH_TrafficBarrierOrientation                2102
#define IDH_XformType                                2103

#define IDH_IShape                                   2200
#define IDH_IShape_ShapeProperties                   2201
#define IDH_IShape_BoundingBox                       2202
#define IDH_IShape_PolyPoints                        2203
#define IDH_IShape_PointInShape                      2204
#define IDH_IShape_Clone                             2205
#define IDH_IShape_ClipWithLine                      2206
#define IDH_IShape_ClipIn                            2207
#define IDH_IShape_Perimeter                         2208
#define IDH_IShape_FurthestDistance                  2209

#define IDH_IXYPosition                              2300
#define IDH_IXYPosition_Offset                       2301
#define IDH_IXYPosition_OffsetEx                     2302
#define IDH_IXYPosition_LocatorPoint                 2303
#define IDH_IXYPosition_MoveEx                       2304
#define IDH_IXYPosition_RotateEx                     2305
#define IDH_IXYPosition_Rotate                       2306

#define IDH_IShapeProperties                         2400
#define IDH_IShapeProperties_Area                    2401
#define IDH_IShapeProperties_Centroid                2402
#define IDH_IShapeProperties_I11                     2403
#define IDH_IShapeProperties_I22                     2404
#define IDH_IShapeProperties_I12Max                  2405
#define IDH_IShapeProperties_I12Min                  2406
#define IDH_IShapeProperties_Ixx                     2407
#define IDH_IShapeProperties_Iyy                     2408
#define IDH_IShapeProperties_Ixy                     2409
#define IDH_IShapeProperties_Xleft                   2410
#define IDH_IShapeProperties_Xright                  2411
#define IDH_IShapeProperties_Ytop                    2412 
#define IDH_IShapeProperties_Ybottom                 2413
#define IDH_IShapeProperties_Origin                  2414
#define IDH_IShapeProperties_Orientation             2415
#define IDH_IShapeProperties_CoordinateSystem        2416
#define IDH_IShapeProperties_PrincipleDirection      2417

#define IDH_IShapePropertiesEx                       2450
#define IDH_IShapePropertiesEx_AddProperties         2451

#define IDH_IGeomUtil                                2500
#define IDH_IGeomUtil_Geom2d                         2501
#define IDH_IGeomUtil_Geom3d                         2502
#define IDH_IGeomUtil_Point2dFactory                 2503
#define IDH_IGeomUtil_Point3dFactory                 2504
#define IDH_IGeomUtil_Line2dFactory                  2505
#define IDH_IGeomUtil_LineSegment2dFactory           2506

#define IDH_IGeomUtil3d                              2600
#define IDH_IGeomUtil3d_Distance                     2601
#define IDH_IGeomUtil3d_Magnitude                    2602

#define IDH_IGeomUtil2d                                  2700
#define IDH_IGeomUtil2d_GenerateCircle                   2701
#define IDH_IGeomUtil2d_Distance                         2702
#define IDH_IGeomUtil2d_Magnitude                        2703
#define IDH_IGeomUtil2d_Angle                            2704
#define IDH_IGeomUtil2d_ShortestDistanceToPoint          2705
#define IDH_IGeomUtil2d_PointOnLineNearest               2706
#define IDH_IGeomUtil2d_CreateParallelLineThroughPoint   2707
#define IDH_IGeomUtil2d_CreateParallelLine               2708
#define IDH_IGeomUtil2d_CreateNormalLineThroughPoint     2709
#define IDH_IGeomUtil2d_AreLinesColinear                 2710
#define IDH_IGeomUtil2d_DoesLineContainPoint             2711
#define IDH_IGeomUtil2d_DoesLineSegmentContainPoint      2712 
#define IDH_IGeomUtil2d_DivideLineSegment                2713
#define IDH_IGeomUtil2d_DivideArc                        2714
#define IDH_IGeomUtil2d_LineLineIntersect                2715
#define IDH_IGeomUtil2d_SegSegIntersect                  2716
#define IDH_IGeomUtil2d_IntersectLineWithLineSegment     2717
#define IDH_IGeomUtil2d_LineCircleIntersect              2718
#define IDH_IGeomUtil2d_CircleCircleIntersect            2719
#define IDH_IGeomUtil2d_AreLinesParallel                 2720
#define IDH_IGeomUtil2d_AreLineSegmentsParallel          2721
#define IDH_IGeomUtil2d_IsLineParallelToLineSegment      2722
#define IDH_IGeomUtil2d_CreateParallelLineSegment        2723

#define IDH_IEnumPoint2d                                 2800
#define IDH_IEnumPoint2d_Clone                           2801
#define IDH_IEnumPoint2d_Next                            2802
#define IDH_IEnumPoint2d_Reset                           2803
#define IDH_IEnumPoint2d_Skip                            2804

#define IDH_IEnumPoint3d                                 2900
#define IDH_IEnumPoint3d_Clone                           2901
#define IDH_IEnumPoint3d_Next                            2902
#define IDH_IEnumPoint3d_Reset                           2903
#define IDH_IEnumPoint3d_Skip                            2904

#define IDH_ITriangle                                    3000
#define IDH_ITriangle_Width                              3001
#define IDH_ITriangle_Height                             3002
#define IDH_ITriangle_Offset                             3003
#define IDH_ITriangle_HookPoint                          3004
#define IDH_ITriangle_XYPosition                         3005
#define IDH_ITriangle_Shape                              3006

#define IDH_IShapeCollection                             3200
#define IDH_IShapeCollection__Enum                       3201
#define IDH_IShapeCollection_Add                         3202
#define IDH_IShapeCollection_Clear                       3203
#define IDH_IShapeCollection_Count                       3204
#define IDH_IShapeCollection_Item                        3205
#define IDH_IShapeCollection_Remove                      3206
#define IDH_IShapeCollection_ShapeProperties             3207

#define IDH_IEnumShape                                   3300
#define IDH_IEnumShape_Clone                             3301
#define IDH_IEnumShape_Next                              3302
#define IDH_IEnumShape_Reset                             3303
#define IDH_IEnumShape_Skip                              3304

#define IDH_IPlateGirder                                 3400
#define IDH_IPlateGirder_TopFlangeWidth                  3401
#define IDH_IPlateGirder_TopFlangeThick                  3402
#define IDH_IPlateGirder_BottomFlangeWidth               3403
#define IDH_IPlateGirder_BottomFlangeThick               3404
#define IDH_IPlateGirder_WebHeight                       3405
#define IDH_IPlateGirder_WebThick                        3406
#define IDH_IPlateGirder_Height                          3407
#define IDH_IPlateGirder_QTopFlange                      3408
#define IDH_IPlateGirder_QBottomFlange                   3409
#define IDH_IPlateGirder_Shape                           3410
#define IDH_IPlateGirder_XYPosition                      3411
#define IDH_IPlateGirder_HookPoint                       3412

#define IDH_IFasterPolyShape                 3500
#define IDH_IFasterPolyShape_AddPoint        3501
#define IDH_IFasterPolyShape_AddPointEx      3502
#define IDH_IFasterPolyShape_AddPoints       3503
#define IDH_IFasterPolyShape_Clear           3504
#define IDH_IFasterPolyShape_NumPoints       3505
#define IDH_IFasterPolyShape_Point           3506
#define IDH_IFasterPolyShape_CreatePoints    3507
#define IDH_IFasterPolyShape_RemovePoint     3508
#define IDH_IFasterPolyShape_Shape           3509
#define IDH_IFasterPolyShape_XYPosition      3510
#define IDH_IFasterPolyShape_ChangePoint     3501


#define IDH_IUBeam                             1800
#define IDH_IUBeam_W1                          1801
#define IDH_IUBeam_W2                          1802
#define IDH_IUBeam_W3                          1803
#define IDH_IUBeam_W4                          1804
#define IDH_IUBeam_W5                          1805
#define IDH_IUBeam_D1                          1806
#define IDH_IUBeam_D2                          1807
#define IDH_IUBeam_D3                          1808
#define IDH_IUBeam_D4                          1809
#define IDH_IUBeam_D5                          1810
#define IDH_IUBeam_D6                          1811
#define IDH_IUBeam_D7                          1812
#define IDH_IUBeam_T                           1813
#define IDH_IUBeam_HookPoint                   1814
#define IDH_IUBeam_Height                      1815
#define IDH_IUBeam_XYPosition                  1816
#define IDH_IUBeam_Shape                       1817
#define IDH_IUBeam_Slope                       1818
#define IDH_IUBeam_TopWidth                    1819
#define IDH_IUBeam_TopFlangeWidth              1820
#define IDH_IUBeam_WebLocation                 1821
#define IDH_IUBeam_WebSpacing                  1822

#define IDH_IMultiWeb                                 3500
#define IDH_IMultiWeb_W1                              3501
#define IDH_IMultiWeb_W2                              3502
#define IDH_IMultiWeb_D1                              3503
#define IDH_IMultiWeb_D2                              3504
#define IDH_IMultiWeb_T1                              3505
#define IDH_IMultiWeb_T2                              3506
#define IDH_IMultiWeb_WebCount                        3507
#define IDH_IMultiWeb_WebLocation                     3508
#define IDH_IMultiWeb_WebSpacing                      3509
#define IDH_IMultiWeb_HookPoint                       3510
#define IDH_IMultiWeb_Height                          3511
#define IDH_IMultiWeb_AvgWebWidth                     3512
#define IDH_IMultiWeb_BottomFlangeWidth               3513
#define IDH_IMultiWeb_TopFlangeWidth                  3514
#define IDH_IMultiWeb_XYPosition                      3515
#define IDH_IMultiWeb_Shape                           3516

#define IDH_IUBeam2                             3600
#define IDH_IUBeam2_W1                          3601
#define IDH_IUBeam2_W2                          3602
#define IDH_IUBeam2_W3                          3603
#define IDH_IUBeam2_W4                          3604
#define IDH_IUBeam2_W5                          3605
#define IDH_IUBeam2_W6                          3606
#define IDH_IUBeam2_W7                          3607
#define IDH_IUBeam2_D1                          3608
#define IDH_IUBeam2_D2                          3609
#define IDH_IUBeam2_D3                          3610
#define IDH_IUBeam2_D4                          3611
#define IDH_IUBeam2_D5                          3612
#define IDH_IUBeam2_D6                          3613
#define IDH_IUBeam2_T                           3614
#define IDH_IUBeam2_HookPoint                   3615
#define IDH_IUBeam2_Height                      3616
#define IDH_IUBeam2_XYPosition                  3617
#define IDH_IUBeam2_Shape                       3618
#define IDH_IUBeam2_Slope                       3619
#define IDH_IUBeam2_TopWidth                    3620
#define IDH_IUBeam2_TopFlangeWidth              3621
#define IDH_IUBeam2_WebLocation                 3622
#define IDH_IUBeam2_WebSpacing                  3623
#define IDH_IUBeam2_C1                          3624

#define IDH_IMultiWeb2							3700
#define IDH_IMultiWeb2_W1						3701
#define IDH_IMultiWeb2_W2						3702
#define IDH_IMultiWeb2_H1						3703
#define IDH_IMultiWeb2_H2						3704
#define IDH_IMultiWeb2_H3						3075
#define IDH_IMultiWeb2_T1						3706
#define IDH_IMultiWeb2_T2						3707
#define IDH_IMultiWeb2_T3						3708
#define IDH_IMultiWeb2_T4						3709
#define IDH_IMultiWeb2_T5						3710
#define IDH_IMultiWeb2_F1						3711
#define IDH_IMultiWeb2_F2						3712
#define IDH_IMultiWeb2_WebCount					3713
#define IDH_IMultiWeb2_WebLocation				3714
#define IDH_IMultiWeb2_HookPoint				3715
#define IDH_IMultiWeb2_Height					3716
#define IDH_IMultiWeb2_TopFlangeWidth			3717
#define IDH_IMultiWeb2_AvgWebWidth				3718
#define IDH_IMultiWeb2_XYPosition				3719
#define IDH_IMultiWeb2_Shape					3720
#define IDH_IMultiWeb2_C1						3721
#define IDH_IMultiWeb2_C2						3722


#define IDH_IGenericShape                 3800
#define IDH_IGenericShape_Area            3801
#define IDH_IGenericShape_Perimeter       3802
#define IDH_IGenericShape_Centroid        3803
#define IDH_IGenericShape_Ixx             3804
#define IDH_IGenericShape_Iyy             3805
#define IDH_IGenericShape_Ixy             3806
#define IDH_IGenericShape_Shape           3807
#define IDH_IGenericShape_XYPosition      3808

#endif // INCLUDED_PRIMITIVES_HH_