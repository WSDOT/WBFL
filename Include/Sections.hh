#ifndef INCLUDED_SECTIONS_HH_
#define INCLUDED_SECTIONS_HH_

#define IDH_WBLFSections 1

#define IDH_IElasticProperties                           100
#define IDH_IElasticProperties_EA                        101
#define IDH_IElasticProperties_Centroid                  102
#define IDH_IElasticProperties_EI11                      103
#define IDH_IElasticProperties_EI22                      104
#define IDH_IElasticProperties_EI12Max                   105
#define IDH_IElasticProperties_EI12Min                   106
#define IDH_IElasticProperties_EIxx                      107
#define IDH_IElasticProperties_EIyy                      108
#define IDH_IElasticProperties_EIxy                      109
#define IDH_IElasticProperties_Xleft                     110
#define IDH_IElasticProperties_Xright                    111
#define IDH_IElasticProperties_Ytop                      112
#define IDH_IElasticProperties_Ybottom                   113
#define IDH_IElasticProperties_Origin                    114
#define IDH_IElasticProperties_Orientation               115
#define IDH_IElasticProperties_CoordinateSystem          116
#define IDH_IElasticProperties_PrincipleDirection        117
#define IDH_IElasticProperties_AddProperties             118
#define IDH_IElasticProperties_TransformProperties       119

#define IDH_IMassProperties                              200
#define IDH_IMassProperties_MassPerLength                201
#define IDH_IMassProperties_AddProperties                202

#define IDH_ISection                                     300
#define IDH_ISection_BoundingBox                         301
#define IDH_ISection_ElasticProperties                   302
#define IDH_ISection_MassProperties                      303
#define IDH_ISection_ClipIn                              304
#define IDH_ISection_ClipWithLine                        305
#define IDH_ISection_Clone                               306

#define IDH_ICompositeSectionItem                        400
#define IDH_ICompositeSectionItem_Shape                  401
#define IDH_ICompositeSectionItem_E                      402
#define IDH_ICompositeSectionItem_Density                403
#define IDH_ICompositeSectionItem_Void                   404
#define IDH_ICompositeSectionItem_Structural             405

#define IDH_ICompositeSection                            500
#define IDH_ICompositeSection_Item                       501
#define IDH_ICompositeSection_AddSection                 502
#define IDH_ICompositeSection_AddSectionEx               503
#define IDH_ICompositeSection_Remove                     504
#define IDH_ICompositeSection_Count                      505
#define IDH_ICompositeSection_Section                    506
#define IDH_ICompositeSection_XYPosition                 507

#define IDH_ICompositeBeam                               600
#define IDH_ICompositeBeam_Beam                          601
#define IDH_ICompositeBeam_EffectiveSlabWidth            602
#define IDH_ICompositeBeam_TributarySlabWidth            603
#define IDH_ICompositeBeam_GrossSlabDepth                604
#define IDH_ICompositeBeam_SacrificialDepth              605
#define IDH_ICompositeBeam_SlabE                         606
#define IDH_ICompositeBeam_SlabDensity                   607
#define IDH_ICompositeBeam_HaunchWidth                   608
#define IDH_ICompositeBeam_HaunchDepth                   609
#define IDH_ICompositeBeam_Section                       610
#define IDH_ICompositeBeam_XYPosition                    611
#define IDH_ICompositeBeam_BeamE                         612
#define IDH_ICompositeBeam_BeamDensity                   613
#define IDH_ICompositeBeam_QSlab                         614 
#define IDH_ICompositeBeam_Q                             615

#endif // INCLUDED_SECTIONS_HH_