

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:24:02 2017
 */
/* Compiler settings for ..\Include\WBFLLBAM.idl:
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


#ifndef __WBFLLBAM_h__
#define __WBFLLBAM_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IStressPoint_FWD_DEFINED__
#define __IStressPoint_FWD_DEFINED__
typedef interface IStressPoint IStressPoint;

#endif 	/* __IStressPoint_FWD_DEFINED__ */


#ifndef __IStressPointEvents_FWD_DEFINED__
#define __IStressPointEvents_FWD_DEFINED__
typedef interface IStressPointEvents IStressPointEvents;

#endif 	/* __IStressPointEvents_FWD_DEFINED__ */


#ifndef __IEnumStressPoint_FWD_DEFINED__
#define __IEnumStressPoint_FWD_DEFINED__
typedef interface IEnumStressPoint IEnumStressPoint;

#endif 	/* __IEnumStressPoint_FWD_DEFINED__ */


#ifndef __IStressPoints_FWD_DEFINED__
#define __IStressPoints_FWD_DEFINED__
typedef interface IStressPoints IStressPoints;

#endif 	/* __IStressPoints_FWD_DEFINED__ */


#ifndef __IStressPointsEvents_FWD_DEFINED__
#define __IStressPointsEvents_FWD_DEFINED__
typedef interface IStressPointsEvents IStressPointsEvents;

#endif 	/* __IStressPointsEvents_FWD_DEFINED__ */


#ifndef __ISegmentCrossSection_FWD_DEFINED__
#define __ISegmentCrossSection_FWD_DEFINED__
typedef interface ISegmentCrossSection ISegmentCrossSection;

#endif 	/* __ISegmentCrossSection_FWD_DEFINED__ */


#ifndef __ISegmentCrossSectionEvents_FWD_DEFINED__
#define __ISegmentCrossSectionEvents_FWD_DEFINED__
typedef interface ISegmentCrossSectionEvents ISegmentCrossSectionEvents;

#endif 	/* __ISegmentCrossSectionEvents_FWD_DEFINED__ */


#ifndef __ISegment_FWD_DEFINED__
#define __ISegment_FWD_DEFINED__
typedef interface ISegment ISegment;

#endif 	/* __ISegment_FWD_DEFINED__ */


#ifndef __ISegmentEvents_FWD_DEFINED__
#define __ISegmentEvents_FWD_DEFINED__
typedef interface ISegmentEvents ISegmentEvents;

#endif 	/* __ISegmentEvents_FWD_DEFINED__ */


#ifndef __ISegmentItem_FWD_DEFINED__
#define __ISegmentItem_FWD_DEFINED__
typedef interface ISegmentItem ISegmentItem;

#endif 	/* __ISegmentItem_FWD_DEFINED__ */


#ifndef __ISegmentItemEvents_FWD_DEFINED__
#define __ISegmentItemEvents_FWD_DEFINED__
typedef interface ISegmentItemEvents ISegmentItemEvents;

#endif 	/* __ISegmentItemEvents_FWD_DEFINED__ */


#ifndef __IEnumSegment_FWD_DEFINED__
#define __IEnumSegment_FWD_DEFINED__
typedef interface IEnumSegment IEnumSegment;

#endif 	/* __IEnumSegment_FWD_DEFINED__ */


#ifndef __IEnumSegmentItem_FWD_DEFINED__
#define __IEnumSegmentItem_FWD_DEFINED__
typedef interface IEnumSegmentItem IEnumSegmentItem;

#endif 	/* __IEnumSegmentItem_FWD_DEFINED__ */


#ifndef __IFilteredSegmentCollection_FWD_DEFINED__
#define __IFilteredSegmentCollection_FWD_DEFINED__
typedef interface IFilteredSegmentCollection IFilteredSegmentCollection;

#endif 	/* __IFilteredSegmentCollection_FWD_DEFINED__ */


#ifndef __ISuperstructureMember_FWD_DEFINED__
#define __ISuperstructureMember_FWD_DEFINED__
typedef interface ISuperstructureMember ISuperstructureMember;

#endif 	/* __ISuperstructureMember_FWD_DEFINED__ */


#ifndef __ISuperstructureMemberEvents_FWD_DEFINED__
#define __ISuperstructureMemberEvents_FWD_DEFINED__
typedef interface ISuperstructureMemberEvents ISuperstructureMemberEvents;

#endif 	/* __ISuperstructureMemberEvents_FWD_DEFINED__ */


#ifndef __IEnumSuperstructureMember_FWD_DEFINED__
#define __IEnumSuperstructureMember_FWD_DEFINED__
typedef interface IEnumSuperstructureMember IEnumSuperstructureMember;

#endif 	/* __IEnumSuperstructureMember_FWD_DEFINED__ */


#ifndef __ISuperstructureMembers_FWD_DEFINED__
#define __ISuperstructureMembers_FWD_DEFINED__
typedef interface ISuperstructureMembers ISuperstructureMembers;

#endif 	/* __ISuperstructureMembers_FWD_DEFINED__ */


#ifndef __ISuperstructureMembersEvents_FWD_DEFINED__
#define __ISuperstructureMembersEvents_FWD_DEFINED__
typedef interface ISuperstructureMembersEvents ISuperstructureMembersEvents;

#endif 	/* __ISuperstructureMembersEvents_FWD_DEFINED__ */


#ifndef __IAxle_FWD_DEFINED__
#define __IAxle_FWD_DEFINED__
typedef interface IAxle IAxle;

#endif 	/* __IAxle_FWD_DEFINED__ */


#ifndef __IAxleEvents_FWD_DEFINED__
#define __IAxleEvents_FWD_DEFINED__
typedef interface IAxleEvents IAxleEvents;

#endif 	/* __IAxleEvents_FWD_DEFINED__ */


#ifndef __IEnumAxle_FWD_DEFINED__
#define __IEnumAxle_FWD_DEFINED__
typedef interface IEnumAxle IEnumAxle;

#endif 	/* __IEnumAxle_FWD_DEFINED__ */


#ifndef __IAxles_FWD_DEFINED__
#define __IAxles_FWD_DEFINED__
typedef interface IAxles IAxles;

#endif 	/* __IAxles_FWD_DEFINED__ */


#ifndef __IAxlesEvents_FWD_DEFINED__
#define __IAxlesEvents_FWD_DEFINED__
typedef interface IAxlesEvents IAxlesEvents;

#endif 	/* __IAxlesEvents_FWD_DEFINED__ */


#ifndef __IVehicularLoad_FWD_DEFINED__
#define __IVehicularLoad_FWD_DEFINED__
typedef interface IVehicularLoad IVehicularLoad;

#endif 	/* __IVehicularLoad_FWD_DEFINED__ */


#ifndef __IVehicularLoadEvents_FWD_DEFINED__
#define __IVehicularLoadEvents_FWD_DEFINED__
typedef interface IVehicularLoadEvents IVehicularLoadEvents;

#endif 	/* __IVehicularLoadEvents_FWD_DEFINED__ */


#ifndef __IEnumVehicularLoad_FWD_DEFINED__
#define __IEnumVehicularLoad_FWD_DEFINED__
typedef interface IEnumVehicularLoad IEnumVehicularLoad;

#endif 	/* __IEnumVehicularLoad_FWD_DEFINED__ */


#ifndef __IVehicularLoads_FWD_DEFINED__
#define __IVehicularLoads_FWD_DEFINED__
typedef interface IVehicularLoads IVehicularLoads;

#endif 	/* __IVehicularLoads_FWD_DEFINED__ */


#ifndef __IVehicularLoadsEvents_FWD_DEFINED__
#define __IVehicularLoadsEvents_FWD_DEFINED__
typedef interface IVehicularLoadsEvents IVehicularLoadsEvents;

#endif 	/* __IVehicularLoadsEvents_FWD_DEFINED__ */


#ifndef __ILiveLoadModel_FWD_DEFINED__
#define __ILiveLoadModel_FWD_DEFINED__
typedef interface ILiveLoadModel ILiveLoadModel;

#endif 	/* __ILiveLoadModel_FWD_DEFINED__ */


#ifndef __ILiveLoadModelEvents_FWD_DEFINED__
#define __ILiveLoadModelEvents_FWD_DEFINED__
typedef interface ILiveLoadModelEvents ILiveLoadModelEvents;

#endif 	/* __ILiveLoadModelEvents_FWD_DEFINED__ */


#ifndef __ILiveLoad_FWD_DEFINED__
#define __ILiveLoad_FWD_DEFINED__
typedef interface ILiveLoad ILiveLoad;

#endif 	/* __ILiveLoad_FWD_DEFINED__ */


#ifndef __ILiveLoadEvents_FWD_DEFINED__
#define __ILiveLoadEvents_FWD_DEFINED__
typedef interface ILiveLoadEvents ILiveLoadEvents;

#endif 	/* __ILiveLoadEvents_FWD_DEFINED__ */


#ifndef __IDistributionFactor_FWD_DEFINED__
#define __IDistributionFactor_FWD_DEFINED__
typedef interface IDistributionFactor IDistributionFactor;

#endif 	/* __IDistributionFactor_FWD_DEFINED__ */


#ifndef __ISupport_FWD_DEFINED__
#define __ISupport_FWD_DEFINED__
typedef interface ISupport ISupport;

#endif 	/* __ISupport_FWD_DEFINED__ */


#ifndef __IEnumSupport_FWD_DEFINED__
#define __IEnumSupport_FWD_DEFINED__
typedef interface IEnumSupport IEnumSupport;

#endif 	/* __IEnumSupport_FWD_DEFINED__ */


#ifndef __ISupports_FWD_DEFINED__
#define __ISupports_FWD_DEFINED__
typedef interface ISupports ISupports;

#endif 	/* __ISupports_FWD_DEFINED__ */


#ifndef __ITemporarySupport_FWD_DEFINED__
#define __ITemporarySupport_FWD_DEFINED__
typedef interface ITemporarySupport ITemporarySupport;

#endif 	/* __ITemporarySupport_FWD_DEFINED__ */


#ifndef __IEnumTemporarySupport_FWD_DEFINED__
#define __IEnumTemporarySupport_FWD_DEFINED__
typedef interface IEnumTemporarySupport IEnumTemporarySupport;

#endif 	/* __IEnumTemporarySupport_FWD_DEFINED__ */


#ifndef __ITemporarySupports_FWD_DEFINED__
#define __ITemporarySupports_FWD_DEFINED__
typedef interface ITemporarySupports ITemporarySupports;

#endif 	/* __ITemporarySupports_FWD_DEFINED__ */


#ifndef __ISpan_FWD_DEFINED__
#define __ISpan_FWD_DEFINED__
typedef interface ISpan ISpan;

#endif 	/* __ISpan_FWD_DEFINED__ */


#ifndef __IEnumSpan_FWD_DEFINED__
#define __IEnumSpan_FWD_DEFINED__
typedef interface IEnumSpan IEnumSpan;

#endif 	/* __IEnumSpan_FWD_DEFINED__ */


#ifndef __ISpans_FWD_DEFINED__
#define __ISpans_FWD_DEFINED__
typedef interface ISpans ISpans;

#endif 	/* __ISpans_FWD_DEFINED__ */


#ifndef __IPOIStressPointsItem_FWD_DEFINED__
#define __IPOIStressPointsItem_FWD_DEFINED__
typedef interface IPOIStressPointsItem IPOIStressPointsItem;

#endif 	/* __IPOIStressPointsItem_FWD_DEFINED__ */


#ifndef __IEnumPOIStressPoints_FWD_DEFINED__
#define __IEnumPOIStressPoints_FWD_DEFINED__
typedef interface IEnumPOIStressPoints IEnumPOIStressPoints;

#endif 	/* __IEnumPOIStressPoints_FWD_DEFINED__ */


#ifndef __IPOIStressPoints_FWD_DEFINED__
#define __IPOIStressPoints_FWD_DEFINED__
typedef interface IPOIStressPoints IPOIStressPoints;

#endif 	/* __IPOIStressPoints_FWD_DEFINED__ */


#ifndef __IPOI_FWD_DEFINED__
#define __IPOI_FWD_DEFINED__
typedef interface IPOI IPOI;

#endif 	/* __IPOI_FWD_DEFINED__ */


#ifndef __IEnumPOI_FWD_DEFINED__
#define __IEnumPOI_FWD_DEFINED__
typedef interface IEnumPOI IEnumPOI;

#endif 	/* __IEnumPOI_FWD_DEFINED__ */


#ifndef __IPOIs_FWD_DEFINED__
#define __IPOIs_FWD_DEFINED__
typedef interface IPOIs IPOIs;

#endif 	/* __IPOIs_FWD_DEFINED__ */


#ifndef __IStage_FWD_DEFINED__
#define __IStage_FWD_DEFINED__
typedef interface IStage IStage;

#endif 	/* __IStage_FWD_DEFINED__ */


#ifndef __IEnumStage_FWD_DEFINED__
#define __IEnumStage_FWD_DEFINED__
typedef interface IEnumStage IEnumStage;

#endif 	/* __IEnumStage_FWD_DEFINED__ */


#ifndef __IStages_FWD_DEFINED__
#define __IStages_FWD_DEFINED__
typedef interface IStages IStages;

#endif 	/* __IStages_FWD_DEFINED__ */


#ifndef __IPointLoad_FWD_DEFINED__
#define __IPointLoad_FWD_DEFINED__
typedef interface IPointLoad IPointLoad;

#endif 	/* __IPointLoad_FWD_DEFINED__ */


#ifndef __IPointLoadItem_FWD_DEFINED__
#define __IPointLoadItem_FWD_DEFINED__
typedef interface IPointLoadItem IPointLoadItem;

#endif 	/* __IPointLoadItem_FWD_DEFINED__ */


#ifndef __IEnumPointLoad_FWD_DEFINED__
#define __IEnumPointLoad_FWD_DEFINED__
typedef interface IEnumPointLoad IEnumPointLoad;

#endif 	/* __IEnumPointLoad_FWD_DEFINED__ */


#ifndef __IPointLoads_FWD_DEFINED__
#define __IPointLoads_FWD_DEFINED__
typedef interface IPointLoads IPointLoads;

#endif 	/* __IPointLoads_FWD_DEFINED__ */


#ifndef __IDistributedLoad_FWD_DEFINED__
#define __IDistributedLoad_FWD_DEFINED__
typedef interface IDistributedLoad IDistributedLoad;

#endif 	/* __IDistributedLoad_FWD_DEFINED__ */


#ifndef __IDistributedLoadItem_FWD_DEFINED__
#define __IDistributedLoadItem_FWD_DEFINED__
typedef interface IDistributedLoadItem IDistributedLoadItem;

#endif 	/* __IDistributedLoadItem_FWD_DEFINED__ */


#ifndef __IEnumDistributedLoad_FWD_DEFINED__
#define __IEnumDistributedLoad_FWD_DEFINED__
typedef interface IEnumDistributedLoad IEnumDistributedLoad;

#endif 	/* __IEnumDistributedLoad_FWD_DEFINED__ */


#ifndef __IDistributedLoads_FWD_DEFINED__
#define __IDistributedLoads_FWD_DEFINED__
typedef interface IDistributedLoads IDistributedLoads;

#endif 	/* __IDistributedLoads_FWD_DEFINED__ */


#ifndef __ITemperatureLoad_FWD_DEFINED__
#define __ITemperatureLoad_FWD_DEFINED__
typedef interface ITemperatureLoad ITemperatureLoad;

#endif 	/* __ITemperatureLoad_FWD_DEFINED__ */


#ifndef __ITemperatureLoadItem_FWD_DEFINED__
#define __ITemperatureLoadItem_FWD_DEFINED__
typedef interface ITemperatureLoadItem ITemperatureLoadItem;

#endif 	/* __ITemperatureLoadItem_FWD_DEFINED__ */


#ifndef __IEnumTemperatureLoad_FWD_DEFINED__
#define __IEnumTemperatureLoad_FWD_DEFINED__
typedef interface IEnumTemperatureLoad IEnumTemperatureLoad;

#endif 	/* __IEnumTemperatureLoad_FWD_DEFINED__ */


#ifndef __ITemperatureLoads_FWD_DEFINED__
#define __ITemperatureLoads_FWD_DEFINED__
typedef interface ITemperatureLoads ITemperatureLoads;

#endif 	/* __ITemperatureLoads_FWD_DEFINED__ */


#ifndef __ISettlementLoad_FWD_DEFINED__
#define __ISettlementLoad_FWD_DEFINED__
typedef interface ISettlementLoad ISettlementLoad;

#endif 	/* __ISettlementLoad_FWD_DEFINED__ */


#ifndef __ISettlementLoadItem_FWD_DEFINED__
#define __ISettlementLoadItem_FWD_DEFINED__
typedef interface ISettlementLoadItem ISettlementLoadItem;

#endif 	/* __ISettlementLoadItem_FWD_DEFINED__ */


#ifndef __IEnumSettlementLoad_FWD_DEFINED__
#define __IEnumSettlementLoad_FWD_DEFINED__
typedef interface IEnumSettlementLoad IEnumSettlementLoad;

#endif 	/* __IEnumSettlementLoad_FWD_DEFINED__ */


#ifndef __ISettlementLoads_FWD_DEFINED__
#define __ISettlementLoads_FWD_DEFINED__
typedef interface ISettlementLoads ISettlementLoads;

#endif 	/* __ISettlementLoads_FWD_DEFINED__ */


#ifndef __IStrainLoad_FWD_DEFINED__
#define __IStrainLoad_FWD_DEFINED__
typedef interface IStrainLoad IStrainLoad;

#endif 	/* __IStrainLoad_FWD_DEFINED__ */


#ifndef __IStrainLoadItem_FWD_DEFINED__
#define __IStrainLoadItem_FWD_DEFINED__
typedef interface IStrainLoadItem IStrainLoadItem;

#endif 	/* __IStrainLoadItem_FWD_DEFINED__ */


#ifndef __IEnumStrainLoad_FWD_DEFINED__
#define __IEnumStrainLoad_FWD_DEFINED__
typedef interface IEnumStrainLoad IEnumStrainLoad;

#endif 	/* __IEnumStrainLoad_FWD_DEFINED__ */


#ifndef __IStrainLoads_FWD_DEFINED__
#define __IStrainLoads_FWD_DEFINED__
typedef interface IStrainLoads IStrainLoads;

#endif 	/* __IStrainLoads_FWD_DEFINED__ */


#ifndef __ILoadGroup_FWD_DEFINED__
#define __ILoadGroup_FWD_DEFINED__
typedef interface ILoadGroup ILoadGroup;

#endif 	/* __ILoadGroup_FWD_DEFINED__ */


#ifndef __IEnumLoadGroup_FWD_DEFINED__
#define __IEnumLoadGroup_FWD_DEFINED__
typedef interface IEnumLoadGroup IEnumLoadGroup;

#endif 	/* __IEnumLoadGroup_FWD_DEFINED__ */


#ifndef __ILoadGroups_FWD_DEFINED__
#define __ILoadGroups_FWD_DEFINED__
typedef interface ILoadGroups ILoadGroups;

#endif 	/* __ILoadGroups_FWD_DEFINED__ */


#ifndef __ILoadCase_FWD_DEFINED__
#define __ILoadCase_FWD_DEFINED__
typedef interface ILoadCase ILoadCase;

#endif 	/* __ILoadCase_FWD_DEFINED__ */


#ifndef __IEnumLoadCase_FWD_DEFINED__
#define __IEnumLoadCase_FWD_DEFINED__
typedef interface IEnumLoadCase IEnumLoadCase;

#endif 	/* __IEnumLoadCase_FWD_DEFINED__ */


#ifndef __ILoadCases_FWD_DEFINED__
#define __ILoadCases_FWD_DEFINED__
typedef interface ILoadCases ILoadCases;

#endif 	/* __ILoadCases_FWD_DEFINED__ */


#ifndef __ILoadCombination_FWD_DEFINED__
#define __ILoadCombination_FWD_DEFINED__
typedef interface ILoadCombination ILoadCombination;

#endif 	/* __ILoadCombination_FWD_DEFINED__ */


#ifndef __IEnumLoadCombination_FWD_DEFINED__
#define __IEnumLoadCombination_FWD_DEFINED__
typedef interface IEnumLoadCombination IEnumLoadCombination;

#endif 	/* __IEnumLoadCombination_FWD_DEFINED__ */


#ifndef __ILoadCombinations_FWD_DEFINED__
#define __ILoadCombinations_FWD_DEFINED__
typedef interface ILoadCombinations ILoadCombinations;

#endif 	/* __ILoadCombinations_FWD_DEFINED__ */


#ifndef __IDistributionFactorSegment_FWD_DEFINED__
#define __IDistributionFactorSegment_FWD_DEFINED__
typedef interface IDistributionFactorSegment IDistributionFactorSegment;

#endif 	/* __IDistributionFactorSegment_FWD_DEFINED__ */


#ifndef __ILinearDistributionFactorSegment_FWD_DEFINED__
#define __ILinearDistributionFactorSegment_FWD_DEFINED__
typedef interface ILinearDistributionFactorSegment ILinearDistributionFactorSegment;

#endif 	/* __ILinearDistributionFactorSegment_FWD_DEFINED__ */


#ifndef __IEnumDistributionFactorSegment_FWD_DEFINED__
#define __IEnumDistributionFactorSegment_FWD_DEFINED__
typedef interface IEnumDistributionFactorSegment IEnumDistributionFactorSegment;

#endif 	/* __IEnumDistributionFactorSegment_FWD_DEFINED__ */


#ifndef __IFilteredDfSegmentCollection_FWD_DEFINED__
#define __IFilteredDfSegmentCollection_FWD_DEFINED__
typedef interface IFilteredDfSegmentCollection IFilteredDfSegmentCollection;

#endif 	/* __IFilteredDfSegmentCollection_FWD_DEFINED__ */


#ifndef __IDistributionFactors_FWD_DEFINED__
#define __IDistributionFactors_FWD_DEFINED__
typedef interface IDistributionFactors IDistributionFactors;

#endif 	/* __IDistributionFactors_FWD_DEFINED__ */


#ifndef __ILBAMModel_FWD_DEFINED__
#define __ILBAMModel_FWD_DEFINED__
typedef interface ILBAMModel ILBAMModel;

#endif 	/* __ILBAMModel_FWD_DEFINED__ */


#ifndef __ILBAMModelEvents_FWD_DEFINED__
#define __ILBAMModelEvents_FWD_DEFINED__
typedef interface ILBAMModelEvents ILBAMModelEvents;

#endif 	/* __ILBAMModelEvents_FWD_DEFINED__ */


#ifndef __ISupportEvents_FWD_DEFINED__
#define __ISupportEvents_FWD_DEFINED__
typedef interface ISupportEvents ISupportEvents;

#endif 	/* __ISupportEvents_FWD_DEFINED__ */


#ifndef __ISupportsEvents_FWD_DEFINED__
#define __ISupportsEvents_FWD_DEFINED__
typedef interface ISupportsEvents ISupportsEvents;

#endif 	/* __ISupportsEvents_FWD_DEFINED__ */


#ifndef __ITemporarySupportEvents_FWD_DEFINED__
#define __ITemporarySupportEvents_FWD_DEFINED__
typedef interface ITemporarySupportEvents ITemporarySupportEvents;

#endif 	/* __ITemporarySupportEvents_FWD_DEFINED__ */


#ifndef __ITemporarySupportsEvents_FWD_DEFINED__
#define __ITemporarySupportsEvents_FWD_DEFINED__
typedef interface ITemporarySupportsEvents ITemporarySupportsEvents;

#endif 	/* __ITemporarySupportsEvents_FWD_DEFINED__ */


#ifndef __ISpanEvents_FWD_DEFINED__
#define __ISpanEvents_FWD_DEFINED__
typedef interface ISpanEvents ISpanEvents;

#endif 	/* __ISpanEvents_FWD_DEFINED__ */


#ifndef __ISpansEvents_FWD_DEFINED__
#define __ISpansEvents_FWD_DEFINED__
typedef interface ISpansEvents ISpansEvents;

#endif 	/* __ISpansEvents_FWD_DEFINED__ */


#ifndef __IPOIStressPointsEvents_FWD_DEFINED__
#define __IPOIStressPointsEvents_FWD_DEFINED__
typedef interface IPOIStressPointsEvents IPOIStressPointsEvents;

#endif 	/* __IPOIStressPointsEvents_FWD_DEFINED__ */


#ifndef __IPOIEvents_FWD_DEFINED__
#define __IPOIEvents_FWD_DEFINED__
typedef interface IPOIEvents IPOIEvents;

#endif 	/* __IPOIEvents_FWD_DEFINED__ */


#ifndef __IPOIsEvents_FWD_DEFINED__
#define __IPOIsEvents_FWD_DEFINED__
typedef interface IPOIsEvents IPOIsEvents;

#endif 	/* __IPOIsEvents_FWD_DEFINED__ */


#ifndef __IStageEvents_FWD_DEFINED__
#define __IStageEvents_FWD_DEFINED__
typedef interface IStageEvents IStageEvents;

#endif 	/* __IStageEvents_FWD_DEFINED__ */


#ifndef __IStagesEvents_FWD_DEFINED__
#define __IStagesEvents_FWD_DEFINED__
typedef interface IStagesEvents IStagesEvents;

#endif 	/* __IStagesEvents_FWD_DEFINED__ */


#ifndef __IPointLoadEvents_FWD_DEFINED__
#define __IPointLoadEvents_FWD_DEFINED__
typedef interface IPointLoadEvents IPointLoadEvents;

#endif 	/* __IPointLoadEvents_FWD_DEFINED__ */


#ifndef __IPointLoadsEvents_FWD_DEFINED__
#define __IPointLoadsEvents_FWD_DEFINED__
typedef interface IPointLoadsEvents IPointLoadsEvents;

#endif 	/* __IPointLoadsEvents_FWD_DEFINED__ */


#ifndef __IDistributedLoadEvents_FWD_DEFINED__
#define __IDistributedLoadEvents_FWD_DEFINED__
typedef interface IDistributedLoadEvents IDistributedLoadEvents;

#endif 	/* __IDistributedLoadEvents_FWD_DEFINED__ */


#ifndef __IDistributedLoadsEvents_FWD_DEFINED__
#define __IDistributedLoadsEvents_FWD_DEFINED__
typedef interface IDistributedLoadsEvents IDistributedLoadsEvents;

#endif 	/* __IDistributedLoadsEvents_FWD_DEFINED__ */


#ifndef __ISettlementLoadEvents_FWD_DEFINED__
#define __ISettlementLoadEvents_FWD_DEFINED__
typedef interface ISettlementLoadEvents ISettlementLoadEvents;

#endif 	/* __ISettlementLoadEvents_FWD_DEFINED__ */


#ifndef __ISettlementLoadsEvents_FWD_DEFINED__
#define __ISettlementLoadsEvents_FWD_DEFINED__
typedef interface ISettlementLoadsEvents ISettlementLoadsEvents;

#endif 	/* __ISettlementLoadsEvents_FWD_DEFINED__ */


#ifndef __ITemperatureLoadEvents_FWD_DEFINED__
#define __ITemperatureLoadEvents_FWD_DEFINED__
typedef interface ITemperatureLoadEvents ITemperatureLoadEvents;

#endif 	/* __ITemperatureLoadEvents_FWD_DEFINED__ */


#ifndef __ITemperatureLoadsEvents_FWD_DEFINED__
#define __ITemperatureLoadsEvents_FWD_DEFINED__
typedef interface ITemperatureLoadsEvents ITemperatureLoadsEvents;

#endif 	/* __ITemperatureLoadsEvents_FWD_DEFINED__ */


#ifndef __IStrainLoadEvents_FWD_DEFINED__
#define __IStrainLoadEvents_FWD_DEFINED__
typedef interface IStrainLoadEvents IStrainLoadEvents;

#endif 	/* __IStrainLoadEvents_FWD_DEFINED__ */


#ifndef __IStrainLoadsEvents_FWD_DEFINED__
#define __IStrainLoadsEvents_FWD_DEFINED__
typedef interface IStrainLoadsEvents IStrainLoadsEvents;

#endif 	/* __IStrainLoadsEvents_FWD_DEFINED__ */


#ifndef __ILoadGroupEvents_FWD_DEFINED__
#define __ILoadGroupEvents_FWD_DEFINED__
typedef interface ILoadGroupEvents ILoadGroupEvents;

#endif 	/* __ILoadGroupEvents_FWD_DEFINED__ */


#ifndef __ILoadGroupsEvents_FWD_DEFINED__
#define __ILoadGroupsEvents_FWD_DEFINED__
typedef interface ILoadGroupsEvents ILoadGroupsEvents;

#endif 	/* __ILoadGroupsEvents_FWD_DEFINED__ */


#ifndef __ILoadCaseEvents_FWD_DEFINED__
#define __ILoadCaseEvents_FWD_DEFINED__
typedef interface ILoadCaseEvents ILoadCaseEvents;

#endif 	/* __ILoadCaseEvents_FWD_DEFINED__ */


#ifndef __ILoadCasesEvents_FWD_DEFINED__
#define __ILoadCasesEvents_FWD_DEFINED__
typedef interface ILoadCasesEvents ILoadCasesEvents;

#endif 	/* __ILoadCasesEvents_FWD_DEFINED__ */


#ifndef __ILoadCombinationEvents_FWD_DEFINED__
#define __ILoadCombinationEvents_FWD_DEFINED__
typedef interface ILoadCombinationEvents ILoadCombinationEvents;

#endif 	/* __ILoadCombinationEvents_FWD_DEFINED__ */


#ifndef __ILoadCombinationsEvents_FWD_DEFINED__
#define __ILoadCombinationsEvents_FWD_DEFINED__
typedef interface ILoadCombinationsEvents ILoadCombinationsEvents;

#endif 	/* __ILoadCombinationsEvents_FWD_DEFINED__ */


#ifndef __IDistributionFactorEvents_FWD_DEFINED__
#define __IDistributionFactorEvents_FWD_DEFINED__
typedef interface IDistributionFactorEvents IDistributionFactorEvents;

#endif 	/* __IDistributionFactorEvents_FWD_DEFINED__ */


#ifndef __IDistributionFactorSegmentEvents_FWD_DEFINED__
#define __IDistributionFactorSegmentEvents_FWD_DEFINED__
typedef interface IDistributionFactorSegmentEvents IDistributionFactorSegmentEvents;

#endif 	/* __IDistributionFactorSegmentEvents_FWD_DEFINED__ */


#ifndef __IDistributionFactorsEvents_FWD_DEFINED__
#define __IDistributionFactorsEvents_FWD_DEFINED__
typedef interface IDistributionFactorsEvents IDistributionFactorsEvents;

#endif 	/* __IDistributionFactorsEvents_FWD_DEFINED__ */


#ifndef __StressPoint_FWD_DEFINED__
#define __StressPoint_FWD_DEFINED__

#ifdef __cplusplus
typedef class StressPoint StressPoint;
#else
typedef struct StressPoint StressPoint;
#endif /* __cplusplus */

#endif 	/* __StressPoint_FWD_DEFINED__ */


#ifndef __StressPoints_FWD_DEFINED__
#define __StressPoints_FWD_DEFINED__

#ifdef __cplusplus
typedef class StressPoints StressPoints;
#else
typedef struct StressPoints StressPoints;
#endif /* __cplusplus */

#endif 	/* __StressPoints_FWD_DEFINED__ */


#ifndef __SegmentCrossSection_FWD_DEFINED__
#define __SegmentCrossSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class SegmentCrossSection SegmentCrossSection;
#else
typedef struct SegmentCrossSection SegmentCrossSection;
#endif /* __cplusplus */

#endif 	/* __SegmentCrossSection_FWD_DEFINED__ */


#ifndef __Segment_FWD_DEFINED__
#define __Segment_FWD_DEFINED__

#ifdef __cplusplus
typedef class Segment Segment;
#else
typedef struct Segment Segment;
#endif /* __cplusplus */

#endif 	/* __Segment_FWD_DEFINED__ */


#ifndef __SegmentItem_FWD_DEFINED__
#define __SegmentItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class SegmentItem SegmentItem;
#else
typedef struct SegmentItem SegmentItem;
#endif /* __cplusplus */

#endif 	/* __SegmentItem_FWD_DEFINED__ */


#ifndef __FilteredSegmentCollection_FWD_DEFINED__
#define __FilteredSegmentCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class FilteredSegmentCollection FilteredSegmentCollection;
#else
typedef struct FilteredSegmentCollection FilteredSegmentCollection;
#endif /* __cplusplus */

#endif 	/* __FilteredSegmentCollection_FWD_DEFINED__ */


#ifndef __SuperstructureMember_FWD_DEFINED__
#define __SuperstructureMember_FWD_DEFINED__

#ifdef __cplusplus
typedef class SuperstructureMember SuperstructureMember;
#else
typedef struct SuperstructureMember SuperstructureMember;
#endif /* __cplusplus */

#endif 	/* __SuperstructureMember_FWD_DEFINED__ */


#ifndef __SuperstructureMembers_FWD_DEFINED__
#define __SuperstructureMembers_FWD_DEFINED__

#ifdef __cplusplus
typedef class SuperstructureMembers SuperstructureMembers;
#else
typedef struct SuperstructureMembers SuperstructureMembers;
#endif /* __cplusplus */

#endif 	/* __SuperstructureMembers_FWD_DEFINED__ */


#ifndef __LBAMModel_FWD_DEFINED__
#define __LBAMModel_FWD_DEFINED__

#ifdef __cplusplus
typedef class LBAMModel LBAMModel;
#else
typedef struct LBAMModel LBAMModel;
#endif /* __cplusplus */

#endif 	/* __LBAMModel_FWD_DEFINED__ */


#ifndef __Support_FWD_DEFINED__
#define __Support_FWD_DEFINED__

#ifdef __cplusplus
typedef class Support Support;
#else
typedef struct Support Support;
#endif /* __cplusplus */

#endif 	/* __Support_FWD_DEFINED__ */


#ifndef __Supports_FWD_DEFINED__
#define __Supports_FWD_DEFINED__

#ifdef __cplusplus
typedef class Supports Supports;
#else
typedef struct Supports Supports;
#endif /* __cplusplus */

#endif 	/* __Supports_FWD_DEFINED__ */


#ifndef __TemporarySupports_FWD_DEFINED__
#define __TemporarySupports_FWD_DEFINED__

#ifdef __cplusplus
typedef class TemporarySupports TemporarySupports;
#else
typedef struct TemporarySupports TemporarySupports;
#endif /* __cplusplus */

#endif 	/* __TemporarySupports_FWD_DEFINED__ */


#ifndef __TemporarySupport_FWD_DEFINED__
#define __TemporarySupport_FWD_DEFINED__

#ifdef __cplusplus
typedef class TemporarySupport TemporarySupport;
#else
typedef struct TemporarySupport TemporarySupport;
#endif /* __cplusplus */

#endif 	/* __TemporarySupport_FWD_DEFINED__ */


#ifndef __Span_FWD_DEFINED__
#define __Span_FWD_DEFINED__

#ifdef __cplusplus
typedef class Span Span;
#else
typedef struct Span Span;
#endif /* __cplusplus */

#endif 	/* __Span_FWD_DEFINED__ */


#ifndef __Spans_FWD_DEFINED__
#define __Spans_FWD_DEFINED__

#ifdef __cplusplus
typedef class Spans Spans;
#else
typedef struct Spans Spans;
#endif /* __cplusplus */

#endif 	/* __Spans_FWD_DEFINED__ */


#ifndef __DistributionFactor_FWD_DEFINED__
#define __DistributionFactor_FWD_DEFINED__

#ifdef __cplusplus
typedef class DistributionFactor DistributionFactor;
#else
typedef struct DistributionFactor DistributionFactor;
#endif /* __cplusplus */

#endif 	/* __DistributionFactor_FWD_DEFINED__ */


#ifndef __POI_FWD_DEFINED__
#define __POI_FWD_DEFINED__

#ifdef __cplusplus
typedef class POI POI;
#else
typedef struct POI POI;
#endif /* __cplusplus */

#endif 	/* __POI_FWD_DEFINED__ */


#ifndef __POIs_FWD_DEFINED__
#define __POIs_FWD_DEFINED__

#ifdef __cplusplus
typedef class POIs POIs;
#else
typedef struct POIs POIs;
#endif /* __cplusplus */

#endif 	/* __POIs_FWD_DEFINED__ */


#ifndef __Stage_FWD_DEFINED__
#define __Stage_FWD_DEFINED__

#ifdef __cplusplus
typedef class Stage Stage;
#else
typedef struct Stage Stage;
#endif /* __cplusplus */

#endif 	/* __Stage_FWD_DEFINED__ */


#ifndef __Stages_FWD_DEFINED__
#define __Stages_FWD_DEFINED__

#ifdef __cplusplus
typedef class Stages Stages;
#else
typedef struct Stages Stages;
#endif /* __cplusplus */

#endif 	/* __Stages_FWD_DEFINED__ */


#ifndef __PointLoad_FWD_DEFINED__
#define __PointLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointLoad PointLoad;
#else
typedef struct PointLoad PointLoad;
#endif /* __cplusplus */

#endif 	/* __PointLoad_FWD_DEFINED__ */


#ifndef __PointLoadItem_FWD_DEFINED__
#define __PointLoadItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointLoadItem PointLoadItem;
#else
typedef struct PointLoadItem PointLoadItem;
#endif /* __cplusplus */

#endif 	/* __PointLoadItem_FWD_DEFINED__ */


#ifndef __PointLoads_FWD_DEFINED__
#define __PointLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointLoads PointLoads;
#else
typedef struct PointLoads PointLoads;
#endif /* __cplusplus */

#endif 	/* __PointLoads_FWD_DEFINED__ */


#ifndef __DistributedLoad_FWD_DEFINED__
#define __DistributedLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class DistributedLoad DistributedLoad;
#else
typedef struct DistributedLoad DistributedLoad;
#endif /* __cplusplus */

#endif 	/* __DistributedLoad_FWD_DEFINED__ */


#ifndef __DistributedLoads_FWD_DEFINED__
#define __DistributedLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class DistributedLoads DistributedLoads;
#else
typedef struct DistributedLoads DistributedLoads;
#endif /* __cplusplus */

#endif 	/* __DistributedLoads_FWD_DEFINED__ */


#ifndef __SettlementLoad_FWD_DEFINED__
#define __SettlementLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class SettlementLoad SettlementLoad;
#else
typedef struct SettlementLoad SettlementLoad;
#endif /* __cplusplus */

#endif 	/* __SettlementLoad_FWD_DEFINED__ */


#ifndef __SettlementLoads_FWD_DEFINED__
#define __SettlementLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class SettlementLoads SettlementLoads;
#else
typedef struct SettlementLoads SettlementLoads;
#endif /* __cplusplus */

#endif 	/* __SettlementLoads_FWD_DEFINED__ */


#ifndef __TemperatureLoad_FWD_DEFINED__
#define __TemperatureLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class TemperatureLoad TemperatureLoad;
#else
typedef struct TemperatureLoad TemperatureLoad;
#endif /* __cplusplus */

#endif 	/* __TemperatureLoad_FWD_DEFINED__ */


#ifndef __TemperatureLoads_FWD_DEFINED__
#define __TemperatureLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class TemperatureLoads TemperatureLoads;
#else
typedef struct TemperatureLoads TemperatureLoads;
#endif /* __cplusplus */

#endif 	/* __TemperatureLoads_FWD_DEFINED__ */


#ifndef __StrainLoad_FWD_DEFINED__
#define __StrainLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class StrainLoad StrainLoad;
#else
typedef struct StrainLoad StrainLoad;
#endif /* __cplusplus */

#endif 	/* __StrainLoad_FWD_DEFINED__ */


#ifndef __StrainLoads_FWD_DEFINED__
#define __StrainLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class StrainLoads StrainLoads;
#else
typedef struct StrainLoads StrainLoads;
#endif /* __cplusplus */

#endif 	/* __StrainLoads_FWD_DEFINED__ */


#ifndef __LoadGroup_FWD_DEFINED__
#define __LoadGroup_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadGroup LoadGroup;
#else
typedef struct LoadGroup LoadGroup;
#endif /* __cplusplus */

#endif 	/* __LoadGroup_FWD_DEFINED__ */


#ifndef __LoadGroups_FWD_DEFINED__
#define __LoadGroups_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadGroups LoadGroups;
#else
typedef struct LoadGroups LoadGroups;
#endif /* __cplusplus */

#endif 	/* __LoadGroups_FWD_DEFINED__ */


#ifndef __LiveLoad_FWD_DEFINED__
#define __LiveLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class LiveLoad LiveLoad;
#else
typedef struct LiveLoad LiveLoad;
#endif /* __cplusplus */

#endif 	/* __LiveLoad_FWD_DEFINED__ */


#ifndef __LiveLoadModel_FWD_DEFINED__
#define __LiveLoadModel_FWD_DEFINED__

#ifdef __cplusplus
typedef class LiveLoadModel LiveLoadModel;
#else
typedef struct LiveLoadModel LiveLoadModel;
#endif /* __cplusplus */

#endif 	/* __LiveLoadModel_FWD_DEFINED__ */


#ifndef __VehicularLoads_FWD_DEFINED__
#define __VehicularLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class VehicularLoads VehicularLoads;
#else
typedef struct VehicularLoads VehicularLoads;
#endif /* __cplusplus */

#endif 	/* __VehicularLoads_FWD_DEFINED__ */


#ifndef __VehicularLoad_FWD_DEFINED__
#define __VehicularLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class VehicularLoad VehicularLoad;
#else
typedef struct VehicularLoad VehicularLoad;
#endif /* __cplusplus */

#endif 	/* __VehicularLoad_FWD_DEFINED__ */


#ifndef __Axle_FWD_DEFINED__
#define __Axle_FWD_DEFINED__

#ifdef __cplusplus
typedef class Axle Axle;
#else
typedef struct Axle Axle;
#endif /* __cplusplus */

#endif 	/* __Axle_FWD_DEFINED__ */


#ifndef __Axles_FWD_DEFINED__
#define __Axles_FWD_DEFINED__

#ifdef __cplusplus
typedef class Axles Axles;
#else
typedef struct Axles Axles;
#endif /* __cplusplus */

#endif 	/* __Axles_FWD_DEFINED__ */


#ifndef __LoadCase_FWD_DEFINED__
#define __LoadCase_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadCase LoadCase;
#else
typedef struct LoadCase LoadCase;
#endif /* __cplusplus */

#endif 	/* __LoadCase_FWD_DEFINED__ */


#ifndef __LoadCases_FWD_DEFINED__
#define __LoadCases_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadCases LoadCases;
#else
typedef struct LoadCases LoadCases;
#endif /* __cplusplus */

#endif 	/* __LoadCases_FWD_DEFINED__ */


#ifndef __LoadCombination_FWD_DEFINED__
#define __LoadCombination_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadCombination LoadCombination;
#else
typedef struct LoadCombination LoadCombination;
#endif /* __cplusplus */

#endif 	/* __LoadCombination_FWD_DEFINED__ */


#ifndef __LoadCombinations_FWD_DEFINED__
#define __LoadCombinations_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadCombinations LoadCombinations;
#else
typedef struct LoadCombinations LoadCombinations;
#endif /* __cplusplus */

#endif 	/* __LoadCombinations_FWD_DEFINED__ */


#ifndef __DistributionFactors_FWD_DEFINED__
#define __DistributionFactors_FWD_DEFINED__

#ifdef __cplusplus
typedef class DistributionFactors DistributionFactors;
#else
typedef struct DistributionFactors DistributionFactors;
#endif /* __cplusplus */

#endif 	/* __DistributionFactors_FWD_DEFINED__ */


#ifndef __DistributionFactorSegment_FWD_DEFINED__
#define __DistributionFactorSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class DistributionFactorSegment DistributionFactorSegment;
#else
typedef struct DistributionFactorSegment DistributionFactorSegment;
#endif /* __cplusplus */

#endif 	/* __DistributionFactorSegment_FWD_DEFINED__ */


#ifndef __LinearDistributionFactorSegment_FWD_DEFINED__
#define __LinearDistributionFactorSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class LinearDistributionFactorSegment LinearDistributionFactorSegment;
#else
typedef struct LinearDistributionFactorSegment LinearDistributionFactorSegment;
#endif /* __cplusplus */

#endif 	/* __LinearDistributionFactorSegment_FWD_DEFINED__ */


#ifndef __FilteredDfSegmentCollection_FWD_DEFINED__
#define __FilteredDfSegmentCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class FilteredDfSegmentCollection FilteredDfSegmentCollection;
#else
typedef struct FilteredDfSegmentCollection FilteredDfSegmentCollection;
#endif /* __cplusplus */

#endif 	/* __FilteredDfSegmentCollection_FWD_DEFINED__ */


#ifndef __POIStressPointsItem_FWD_DEFINED__
#define __POIStressPointsItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class POIStressPointsItem POIStressPointsItem;
#else
typedef struct POIStressPointsItem POIStressPointsItem;
#endif /* __cplusplus */

#endif 	/* __POIStressPointsItem_FWD_DEFINED__ */


#ifndef __POIStressPoints_FWD_DEFINED__
#define __POIStressPoints_FWD_DEFINED__

#ifdef __cplusplus
typedef class POIStressPoints POIStressPoints;
#else
typedef struct POIStressPoints POIStressPoints;
#endif /* __cplusplus */

#endif 	/* __POIStressPoints_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLLBAM_0000_0000 */
/* [local] */ 

#include "LBAMErrors.h"


extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAM_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLLBAM_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLLBAM_LIBRARY_DEFINED__
#define __WBFLLBAM_LIBRARY_DEFINED__

/* library WBFLLBAM */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("98E0937E-77CB-11d5-B02F-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0001
    {
        cgtStress	= 0,
        cgtStiffness	= 1,
        cgtCombination	= 2,
        cgtPOI	= 3,
        cgtDistributionFactor	= 4,
        cgtStage	= 5,
        cgtStageOrder	= 6,
        cgtLoads	= 7,
        cgtDescription	= 8,
        cgtLiveLoad	= 9,
        cgtUserItemData	= 10,
        cgtClear	= 11,
        cgtUnknown	= 12
    } 	ChangeType;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("166AB080-7CA0-11d5-B036-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0002
    {
        mrtNone	= 0,
        mrtMz	= 1,
        mrtFx	= 2
    } 	MemberReleaseType;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("E79D58E6-8826-11d5-B043-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0003
    {
        mtUndefined	= -1,
        mtSpan	= 0,
        mtSupport	= 1,
        mtTemporarySupport	= 2,
        mtSuperstructureMember	= 3
    } 	MemberType;

typedef /* [public][public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("EA251D36-82BB-11d5-B03C-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0004
    {
        bcFixed	= 0,
        bcPinned	= 1,
        bcRoller	= 2
    } 	BoundaryConditionType;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("5E176698-4F89-4db2-8AF0-B2EFA41E3BB9") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0005
    {
        llmaEnvelope	= 0,
        llmaSum	= 1
    } 	LiveLoadModelApplicationType;

typedef /* [public][public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("166AB081-7CA0-11d5-B036-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0006
    {
        ssRight	= 0,
        ssLeft	= 1
    } 	Side;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("D133939A-9326-11d5-B04E-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0007
    {
        loGlobal	= 0,
        loMember	= 1,
        loGlobalProjected	= 2
    } 	LoadOrientation;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("D133939B-9326-11d5-B04E-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0008
    {
        ldFx	= 0,
        ldFy	= 1
    } 	LoadDirection;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("2BD2FDCB-281B-426d-8BAE-875242F7C521") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0009
    {
        dftNone	= 0,
        dftSingleLane	= 1,
        dftMultipleLane	= 2,
        dftEnvelope	= 3,
        dftFatigue	= 4,
        dftPedestrian	= 5
    } 	DistributionFactorType;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("6D4285D2-75B1-4bc4-845E-B335028C894C") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0010
    {
        vlcDefault	= 0,
        vlcTruckOnly	= 1,
        vlcLaneOnly	= 2,
        vlcTruckPlusLane	= 3,
        vlcTruckLaneEnvelope	= 4,
        vlcSidewalkOnly	= 5
    } 	VehicularLoadConfigurationType;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("557A6415-A111-4dc0-8200-F0622ACF5D90") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0011
    {
        llaEntireStructure	= 1,
        llaContraflexure	= 2,
        llaNegMomentAndInteriorPierReaction	= 3
    } 	LiveLoadApplicabilityType;

typedef /* [public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("938C51B6-E4B4-4235-AF4F-A777D9606350") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0012
    {
        lltNone	= -1,
        lltDeflection	= 0,
        lltDesign	= 1,
        lltPedestrian	= 2,
        lltFatigue	= 3,
        lltPermit	= 4,
        lltSpecial	= 5,
        lltLegalRoutineRating	= 6,
        lltLegalSpecialRating	= 7,
        lltLegalEmergencyRating	= 8,
        lltPermitRoutineRating	= 9,
        lltPermitSpecialRating	= 10
    } 	LiveLoadModelType;

typedef /* [public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("07CCC070-AEAD-409f-9468-E747C4B1D238") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0013
    {
        ltdForward	= 0,
        ltdReverse	= 1
    } 	TruckDirectionType;

typedef /* [public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("E816A20C-0146-409a-86BC-3F8652502841") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0014
    {
        izInside	= 0,
        izOutside	= 1,
        izLeftEdge	= 2,
        izRightEdge	= 3
    } 	InZoneType;

typedef /* [public][public][public][public][public][public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("AC1342FB-A684-478d-B7FC-1C6853170C5E") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0015
    {
        lctService	= 0,
        lctStrength	= 1,
        lctExtremeEvent	= 2,
        lctFatigue	= 3,
        lctPermit	= 4,
        lctUserDefined	= 5
    } 	LoadCombinationType;

typedef /* [public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("F5F85148-6409-46a1-B157-E926CA50ED3F") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0016
    {
        lcsSinglePoi	= 1,
        lcsEntireModel	= 2
    } 	ChangeScopeType;

typedef /* [public][helpstring][uuid][public] */  DECLSPEC_UUID("C1B8D971-D46F-4176-BE6F-9333E8600C1F") 
enum __MIDL___MIDL_itf_WBFLLBAM_0000_0000_0017
    {
        cttStressPoint	= 15001,
        cttStressPointsAdded	= 16001,
        cttStressPointsChanged	= 16002,
        cttStressPointsRemoved	= 16003,
        cttSegment	= 17001,
        cttSegmentItem	= 18001,
        cttSuperstructureMember	= 19001,
        cttSuperstructureMembersAdded	= 20001,
        cttSuperstructureMembersChanged	= 20002,
        cttSuperstructureMembersBeforeRemove	= 20003,
        cttSuperstructureMembersCopyTo	= 20004,
        cttSuperstructureMembersMoveTo	= 20005,
        cttSuperstructureMembersReverse	= 20006,
        cttSuperstructureMembersOffset	= 20007,
        cttModel	= 21001,
        cttSegmentCrossSection	= 22001,
        cttSupport	= 23001,
        cttSupportsAdded	= 24001,
        cttSupportsChanged	= 24002,
        cttSupportsBeforeRemove	= 24003,
        cttSupportsCopyTo	= 24004,
        cttSupportsMoveTo	= 24005,
        cttSupportsReverse	= 24006,
        cttTemporarySupport	= 25001,
        cttTemporarySupportsAdded	= 26001,
        cttTemporarySupportsChanged	= 26002,
        cttTemporarySupportsBeforeRemove	= 26003,
        cttSpan	= 27001,
        cttSpansAdded	= 28001,
        cttSpansChanged	= 28002,
        cttSpansBeforeRemove	= 28003,
        cttSpansCopyTo	= 28004,
        cttSpansMoveTo	= 28005,
        cttSpansReverse	= 28006,
        cttDistributionFactorChanged	= 29001,
        cttDistributionFactorSegmentChanged	= 29003,
        cttDistributionFactorsAdded	= 29004,
        cttDistributionFactorsChanged	= 29005,
        cttDistributionFactorsBeforeRemove	= 29006,
        cttDistributionFactorsCopyTo	= 29007,
        cttDistributionFactorsMoveTo	= 29008,
        cttDistributionFactorsReverse	= 29009,
        cttPOIChanged	= 30001,
        cttPOIRenamed	= 30002,
        cttPOIStressPointsChanged	= 30003,
        cttPOIStressPointsAdded	= 30004,
        cttPOIStressPointsBeforeRemove	= 30005,
        cttPOIsChanged	= 31001,
        cttPOIsAdded	= 31002,
        cttPOIsBeforeRemove	= 31003,
        cttPOIsRenamed	= 31004,
        cttStage	= 32001,
        cttStagesAdded	= 33001,
        cttStagesChanged	= 33002,
        cttStagesBeforeRemove	= 33003,
        cttStagesCopyTo	= 33004,
        cttStagesMoveTo	= 33005,
        cttStagesReverse	= 33006,
        cttPointLoad	= 34001,
        cttPointLoadsAdded	= 35001,
        cttPointLoadsChanged	= 35002,
        cttPointLoadsBeforeRemove	= 35003,
        cttDistributedLoad	= 36001,
        cttDistributedLoadsAdded	= 37001,
        cttDistributedLoadsChanged	= 37002,
        cttDistributedLoadsBeforeRemove	= 37003,
        cttSettlementLoad	= 38001,
        cttSettlementLoadsAdded	= 39001,
        cttSettlementLoadsChanged	= 39002,
        cttSettlementLoadsBeforeRemove	= 39003,
        cttTemperatureLoad	= 40001,
        cttTemperatureLoadsAdded	= 41001,
        cttTemperatureLoadsChanged	= 41002,
        cttTemperatureLoadsBeforeRemove	= 41003,
        cttStrainLoad	= 42001,
        cttStrainLoadsAdded	= 43001,
        cttStrainLoadsChanged	= 43002,
        cttStrainLoadsBeforeRemove	= 43003,
        cttLoadGroupChanged	= 44001,
        cttLoadGroupRenamed	= 44002,
        cttLoadGroupsAdded	= 45001,
        cttLoadGroupsChanged	= 45002,
        cttLoadGroupsBeforeRemove	= 45003,
        cttLoadGroupsRenamed	= 45004,
        cttAxle	= 46001,
        cttAxlesAdded	= 46002,
        cttAxlesChanged	= 46003,
        cttAxlesBeforeRemove	= 46004,
        cttAxlesCopyTo	= 46005,
        cttAxlesMoveTo	= 46006,
        cttAxlesReverse	= 46007,
        cttVehicularLoad	= 47001,
        cttVehicularLoadsAdded	= 47002,
        cttVehicularLoadsChanged	= 47003,
        cttVehicularLoadsBeforeRemove	= 47004,
        cttVehicularLoadsRenamed	= 47005,
        cttLiveLoadModel	= 47006,
        cttLiveLoad	= 47007,
        cttLoadCase	= 48001,
        cttLoadCaseRenamed	= 48002,
        cttLoadCasesAdded	= 49001,
        cttLoadCasesChanged	= 49002,
        cttLoadCasesBeforeRemove	= 49003,
        cttLoadCasesRenamed	= 49004,
        cttLoadCombination	= 50001,
        cttLoadCombinationRenamed	= 50002,
        cttLoadCombinationsAdded	= 51001,
        cttLoadCombinationsChanged	= 51002,
        cttLoadCombinationsBeforeRemove	= 51003,
        cttLoadCombinationsRenamed	= 51004
    } 	EventDispatchIds;


EXTERN_C const IID LIBID_WBFLLBAM;

#ifndef __IStressPoint_INTERFACE_DEFINED__
#define __IStressPoint_INTERFACE_DEFINED__

/* interface IStressPoint */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStressPoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A60E8525-3A65-11D5-AFE5-00105A9AF985")
    IStressPoint : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Sa( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Sa( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Sm( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Sm( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IStressPoint **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStressPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStressPoint * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStressPoint * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStressPoint * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sa )( 
            IStressPoint * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sa )( 
            IStressPoint * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sm )( 
            IStressPoint * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sm )( 
            IStressPoint * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IStressPoint * This,
            /* [out] */ IStressPoint **clone);
        
        END_INTERFACE
    } IStressPointVtbl;

    interface IStressPoint
    {
        CONST_VTBL struct IStressPointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStressPoint_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStressPoint_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStressPoint_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStressPoint_get_Sa(This,pVal)	\
    ( (This)->lpVtbl -> get_Sa(This,pVal) ) 

#define IStressPoint_put_Sa(This,newVal)	\
    ( (This)->lpVtbl -> put_Sa(This,newVal) ) 

#define IStressPoint_get_Sm(This,pVal)	\
    ( (This)->lpVtbl -> get_Sm(This,pVal) ) 

#define IStressPoint_put_Sm(This,newVal)	\
    ( (This)->lpVtbl -> put_Sm(This,newVal) ) 

#define IStressPoint_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStressPoint_INTERFACE_DEFINED__ */


#ifndef __IStressPointEvents_INTERFACE_DEFINED__
#define __IStressPointEvents_INTERFACE_DEFINED__

/* interface IStressPointEvents */
/* [unique][helpstring][helpcontext][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStressPointEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6128484-74B1-11d5-B02B-00105A9AF985")
    IStressPointEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStressPointChanged( 
            /* [in] */ IStressPoint *StressPoint) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStressPointEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStressPointEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStressPointEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStressPointEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStressPointChanged )( 
            IStressPointEvents * This,
            /* [in] */ IStressPoint *StressPoint);
        
        END_INTERFACE
    } IStressPointEventsVtbl;

    interface IStressPointEvents
    {
        CONST_VTBL struct IStressPointEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStressPointEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStressPointEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStressPointEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStressPointEvents_OnStressPointChanged(This,StressPoint)	\
    ( (This)->lpVtbl -> OnStressPointChanged(This,StressPoint) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStressPointEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumStressPoint_INTERFACE_DEFINED__
#define __IEnumStressPoint_INTERFACE_DEFINED__

/* interface IEnumStressPoint */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumStressPoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("72E30D12-2ABB-11d5-AFCE-00105A9AF985")
    IEnumStressPoint : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumStressPoint **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IStressPoint **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumStressPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumStressPoint * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumStressPoint * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumStressPoint * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumStressPoint * This,
            /* [out] */ IEnumStressPoint **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumStressPoint * This,
            /* [in] */ ULONG celt,
            /* [out] */ IStressPoint **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumStressPoint * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumStressPoint * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumStressPointVtbl;

    interface IEnumStressPoint
    {
        CONST_VTBL struct IEnumStressPointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumStressPoint_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumStressPoint_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumStressPoint_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumStressPoint_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumStressPoint_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumStressPoint_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumStressPoint_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumStressPoint_INTERFACE_DEFINED__ */


#ifndef __IStressPoints_INTERFACE_DEFINED__
#define __IStressPoints_INTERFACE_DEFINED__

/* interface IStressPoints */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStressPoints;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A60E8528-3A65-11D5-AFE5-00105A9AF985")
    IStressPoints : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IStressPoint **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumStressPoint **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IStressPoint *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ IStressPoint *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            IStressPoints **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStressPointsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStressPoints * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStressPoints * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStressPoints * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IStressPoints * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IStressPoint **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IStressPoints * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IStressPoints * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IStressPoints * This,
            /* [retval][out] */ IEnumStressPoint **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IStressPoints * This,
            /* [in] */ IStressPoint *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IStressPoints * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ IStressPoint *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IStressPoints * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IStressPoints * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IStressPoints * This,
            IStressPoints **clone);
        
        END_INTERFACE
    } IStressPointsVtbl;

    interface IStressPoints
    {
        CONST_VTBL struct IStressPointsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStressPoints_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStressPoints_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStressPoints_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStressPoints_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IStressPoints_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IStressPoints_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IStressPoints_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IStressPoints_Add(This,pVal)	\
    ( (This)->lpVtbl -> Add(This,pVal) ) 

#define IStressPoints_Insert(This,index,pVal)	\
    ( (This)->lpVtbl -> Insert(This,index,pVal) ) 

#define IStressPoints_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define IStressPoints_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IStressPoints_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStressPoints_INTERFACE_DEFINED__ */


#ifndef __IStressPointsEvents_INTERFACE_DEFINED__
#define __IStressPointsEvents_INTERFACE_DEFINED__

/* interface IStressPointsEvents */
/* [helpcontext][helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStressPointsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6128485-74B1-11d5-B02B-00105A9AF985")
    IStressPointsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStressPointsChanged( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStressPointsAdded( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStressPointsRemoved( 
            /* [in] */ CollectionIndexType index) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStressPointsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStressPointsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStressPointsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStressPointsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStressPointsChanged )( 
            IStressPointsEvents * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStressPointsAdded )( 
            IStressPointsEvents * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStressPointsRemoved )( 
            IStressPointsEvents * This,
            /* [in] */ CollectionIndexType index);
        
        END_INTERFACE
    } IStressPointsEventsVtbl;

    interface IStressPointsEvents
    {
        CONST_VTBL struct IStressPointsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStressPointsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStressPointsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStressPointsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStressPointsEvents_OnStressPointsChanged(This,index)	\
    ( (This)->lpVtbl -> OnStressPointsChanged(This,index) ) 

#define IStressPointsEvents_OnStressPointsAdded(This,index)	\
    ( (This)->lpVtbl -> OnStressPointsAdded(This,index) ) 

#define IStressPointsEvents_OnStressPointsRemoved(This,index)	\
    ( (This)->lpVtbl -> OnStressPointsRemoved(This,index) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStressPointsEvents_INTERFACE_DEFINED__ */


#ifndef __ISegmentCrossSection_INTERFACE_DEFINED__
#define __ISegmentCrossSection_INTERFACE_DEFINED__

/* interface ISegmentCrossSection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISegmentCrossSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("426BD2A5-6BCF-11D5-B023-00105A9AF985")
    ISegmentCrossSection : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Depth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Depth( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EAForce( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EAForce( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EIForce( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EIForce( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EADefl( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EADefl( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EIDefl( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EIDefl( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ThermalCoeff( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ThermalCoeff( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StressPoints( 
            /* [retval][out] */ IStressPoints **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_StressPoints( 
            /* [in] */ IStressPoints *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetStiffness( 
            /* [in] */ Float64 EAForce,
            /* [in] */ Float64 EIForce,
            /* [in] */ Float64 EADefl,
            /* [in] */ Float64 EIDefl) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetStiffness( 
            /* [out] */ Float64 *EAForce,
            /* [out] */ Float64 *EIForce,
            /* [out] */ Float64 *EADefl,
            /* [out] */ Float64 *EIDefl) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ISegmentCrossSection **crosssection) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISegmentCrossSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISegmentCrossSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISegmentCrossSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISegmentCrossSection * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Depth )( 
            ISegmentCrossSection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Depth )( 
            ISegmentCrossSection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EAForce )( 
            ISegmentCrossSection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EAForce )( 
            ISegmentCrossSection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EIForce )( 
            ISegmentCrossSection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EIForce )( 
            ISegmentCrossSection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EADefl )( 
            ISegmentCrossSection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EADefl )( 
            ISegmentCrossSection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EIDefl )( 
            ISegmentCrossSection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EIDefl )( 
            ISegmentCrossSection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ThermalCoeff )( 
            ISegmentCrossSection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ThermalCoeff )( 
            ISegmentCrossSection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StressPoints )( 
            ISegmentCrossSection * This,
            /* [retval][out] */ IStressPoints **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StressPoints )( 
            ISegmentCrossSection * This,
            /* [in] */ IStressPoints *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetStiffness )( 
            ISegmentCrossSection * This,
            /* [in] */ Float64 EAForce,
            /* [in] */ Float64 EIForce,
            /* [in] */ Float64 EADefl,
            /* [in] */ Float64 EIDefl);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStiffness )( 
            ISegmentCrossSection * This,
            /* [out] */ Float64 *EAForce,
            /* [out] */ Float64 *EIForce,
            /* [out] */ Float64 *EADefl,
            /* [out] */ Float64 *EIDefl);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISegmentCrossSection * This,
            /* [out] */ ISegmentCrossSection **crosssection);
        
        END_INTERFACE
    } ISegmentCrossSectionVtbl;

    interface ISegmentCrossSection
    {
        CONST_VTBL struct ISegmentCrossSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISegmentCrossSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISegmentCrossSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISegmentCrossSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISegmentCrossSection_get_Depth(This,pVal)	\
    ( (This)->lpVtbl -> get_Depth(This,pVal) ) 

#define ISegmentCrossSection_put_Depth(This,newVal)	\
    ( (This)->lpVtbl -> put_Depth(This,newVal) ) 

#define ISegmentCrossSection_get_EAForce(This,pVal)	\
    ( (This)->lpVtbl -> get_EAForce(This,pVal) ) 

#define ISegmentCrossSection_put_EAForce(This,newVal)	\
    ( (This)->lpVtbl -> put_EAForce(This,newVal) ) 

#define ISegmentCrossSection_get_EIForce(This,pVal)	\
    ( (This)->lpVtbl -> get_EIForce(This,pVal) ) 

#define ISegmentCrossSection_put_EIForce(This,newVal)	\
    ( (This)->lpVtbl -> put_EIForce(This,newVal) ) 

#define ISegmentCrossSection_get_EADefl(This,pVal)	\
    ( (This)->lpVtbl -> get_EADefl(This,pVal) ) 

#define ISegmentCrossSection_put_EADefl(This,newVal)	\
    ( (This)->lpVtbl -> put_EADefl(This,newVal) ) 

#define ISegmentCrossSection_get_EIDefl(This,pVal)	\
    ( (This)->lpVtbl -> get_EIDefl(This,pVal) ) 

#define ISegmentCrossSection_put_EIDefl(This,newVal)	\
    ( (This)->lpVtbl -> put_EIDefl(This,newVal) ) 

#define ISegmentCrossSection_get_ThermalCoeff(This,pVal)	\
    ( (This)->lpVtbl -> get_ThermalCoeff(This,pVal) ) 

#define ISegmentCrossSection_put_ThermalCoeff(This,newVal)	\
    ( (This)->lpVtbl -> put_ThermalCoeff(This,newVal) ) 

#define ISegmentCrossSection_get_StressPoints(This,pVal)	\
    ( (This)->lpVtbl -> get_StressPoints(This,pVal) ) 

#define ISegmentCrossSection_putref_StressPoints(This,newVal)	\
    ( (This)->lpVtbl -> putref_StressPoints(This,newVal) ) 

#define ISegmentCrossSection_SetStiffness(This,EAForce,EIForce,EADefl,EIDefl)	\
    ( (This)->lpVtbl -> SetStiffness(This,EAForce,EIForce,EADefl,EIDefl) ) 

#define ISegmentCrossSection_GetStiffness(This,EAForce,EIForce,EADefl,EIDefl)	\
    ( (This)->lpVtbl -> GetStiffness(This,EAForce,EIForce,EADefl,EIDefl) ) 

#define ISegmentCrossSection_Clone(This,crosssection)	\
    ( (This)->lpVtbl -> Clone(This,crosssection) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISegmentCrossSection_INTERFACE_DEFINED__ */


#ifndef __ISegmentCrossSectionEvents_INTERFACE_DEFINED__
#define __ISegmentCrossSectionEvents_INTERFACE_DEFINED__

/* interface ISegmentCrossSectionEvents */
/* [helpcontext][helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISegmentCrossSectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CF67FA9A-7546-11d5-B02C-00105A9AF985")
    ISegmentCrossSectionEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSegmentCrossSectionChanged( 
            /* [in] */ ISegmentCrossSection *crossSection,
            /* [in] */ ChangeType type) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISegmentCrossSectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISegmentCrossSectionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISegmentCrossSectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISegmentCrossSectionEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSegmentCrossSectionChanged )( 
            ISegmentCrossSectionEvents * This,
            /* [in] */ ISegmentCrossSection *crossSection,
            /* [in] */ ChangeType type);
        
        END_INTERFACE
    } ISegmentCrossSectionEventsVtbl;

    interface ISegmentCrossSectionEvents
    {
        CONST_VTBL struct ISegmentCrossSectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISegmentCrossSectionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISegmentCrossSectionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISegmentCrossSectionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISegmentCrossSectionEvents_OnSegmentCrossSectionChanged(This,crossSection,type)	\
    ( (This)->lpVtbl -> OnSegmentCrossSectionChanged(This,crossSection,type) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISegmentCrossSectionEvents_INTERFACE_DEFINED__ */


#ifndef __ISegment_INTERFACE_DEFINED__
#define __ISegment_INTERFACE_DEFINED__

/* interface ISegment */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21C1BB07-7799-11D5-B02F-00105A9AF985")
    ISegment : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentCrossSection( 
            /* [retval][out] */ ISegmentCrossSection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_SegmentCrossSection( 
            /* [in] */ ISegmentCrossSection *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ISegment **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISegment * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ISegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            ISegment * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SegmentCrossSection )( 
            ISegment * This,
            /* [retval][out] */ ISegmentCrossSection **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SegmentCrossSection )( 
            ISegment * This,
            /* [in] */ ISegmentCrossSection *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISegment * This,
            /* [out] */ ISegment **clone);
        
        END_INTERFACE
    } ISegmentVtbl;

    interface ISegment
    {
        CONST_VTBL struct ISegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ISegment_put_Length(This,newVal)	\
    ( (This)->lpVtbl -> put_Length(This,newVal) ) 

#define ISegment_get_SegmentCrossSection(This,pVal)	\
    ( (This)->lpVtbl -> get_SegmentCrossSection(This,pVal) ) 

#define ISegment_putref_SegmentCrossSection(This,newVal)	\
    ( (This)->lpVtbl -> putref_SegmentCrossSection(This,newVal) ) 

#define ISegment_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISegment_INTERFACE_DEFINED__ */


#ifndef __ISegmentEvents_INTERFACE_DEFINED__
#define __ISegmentEvents_INTERFACE_DEFINED__

/* interface ISegmentEvents */
/* [helpcontext][helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISegmentEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8917E02-779F-11d5-B02F-00105A9AF985")
    ISegmentEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSegmentChanged( 
            /* [in] */ ISegment *segment,
            /* [in] */ ChangeType type) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISegmentEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISegmentEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISegmentEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISegmentEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSegmentChanged )( 
            ISegmentEvents * This,
            /* [in] */ ISegment *segment,
            /* [in] */ ChangeType type);
        
        END_INTERFACE
    } ISegmentEventsVtbl;

    interface ISegmentEvents
    {
        CONST_VTBL struct ISegmentEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISegmentEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISegmentEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISegmentEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISegmentEvents_OnSegmentChanged(This,segment,type)	\
    ( (This)->lpVtbl -> OnSegmentChanged(This,segment,type) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISegmentEvents_INTERFACE_DEFINED__ */


#ifndef __ISegmentItem_INTERFACE_DEFINED__
#define __ISegmentItem_INTERFACE_DEFINED__

/* interface ISegmentItem */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISegmentItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21C1BB0D-7799-11D5-B02F-00105A9AF985")
    ISegmentItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RelPosition( 
            /* [retval][out] */ SegmentIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Segment( 
            /* [retval][out] */ ISegment **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISegmentItem **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISegmentItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISegmentItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISegmentItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISegmentItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            ISegmentItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RelPosition )( 
            ISegmentItem * This,
            /* [retval][out] */ SegmentIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Segment )( 
            ISegmentItem * This,
            /* [retval][out] */ ISegment **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISegmentItem * This,
            /* [retval][out] */ ISegmentItem **clone);
        
        END_INTERFACE
    } ISegmentItemVtbl;

    interface ISegmentItem
    {
        CONST_VTBL struct ISegmentItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISegmentItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISegmentItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISegmentItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISegmentItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define ISegmentItem_get_RelPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_RelPosition(This,pVal) ) 

#define ISegmentItem_get_Segment(This,pVal)	\
    ( (This)->lpVtbl -> get_Segment(This,pVal) ) 

#define ISegmentItem_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISegmentItem_INTERFACE_DEFINED__ */


#ifndef __ISegmentItemEvents_INTERFACE_DEFINED__
#define __ISegmentItemEvents_INTERFACE_DEFINED__

/* interface ISegmentItemEvents */
/* [helpcontext][helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISegmentItemEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EDC12888-77CE-11d5-B02F-00105A9AF985")
    ISegmentItemEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSegmentItemChanged( 
            /* [in] */ ISegmentItem *segmentItem,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISegmentItemEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISegmentItemEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISegmentItemEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISegmentItemEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSegmentItemChanged )( 
            ISegmentItemEvents * This,
            /* [in] */ ISegmentItem *segmentItem,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change);
        
        END_INTERFACE
    } ISegmentItemEventsVtbl;

    interface ISegmentItemEvents
    {
        CONST_VTBL struct ISegmentItemEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISegmentItemEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISegmentItemEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISegmentItemEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISegmentItemEvents_OnSegmentItemChanged(This,segmentItem,stage,change)	\
    ( (This)->lpVtbl -> OnSegmentItemChanged(This,segmentItem,stage,change) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISegmentItemEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumSegment_INTERFACE_DEFINED__
#define __IEnumSegment_INTERFACE_DEFINED__

/* interface IEnumSegment */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7D1F3626-7BD2-11d5-B035-00105A9AF985")
    IEnumSegment : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSegment **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISegment **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSegment * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSegment * This,
            /* [out] */ IEnumSegment **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSegment * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISegment **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSegment * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSegment * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSegmentVtbl;

    interface IEnumSegment
    {
        CONST_VTBL struct IEnumSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSegment_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSegment_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSegment_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSegment_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSegment_INTERFACE_DEFINED__ */


#ifndef __IEnumSegmentItem_INTERFACE_DEFINED__
#define __IEnumSegmentItem_INTERFACE_DEFINED__

/* interface IEnumSegmentItem */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSegmentItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EDC1288A-77CE-11d5-B02F-00105A9AF985")
    IEnumSegmentItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSegmentItem **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISegmentItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSegmentItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSegmentItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSegmentItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSegmentItem * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSegmentItem * This,
            /* [out] */ IEnumSegmentItem **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSegmentItem * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISegmentItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSegmentItem * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSegmentItem * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSegmentItemVtbl;

    interface IEnumSegmentItem
    {
        CONST_VTBL struct IEnumSegmentItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSegmentItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSegmentItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSegmentItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSegmentItem_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSegmentItem_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSegmentItem_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSegmentItem_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSegmentItem_INTERFACE_DEFINED__ */


#ifndef __IFilteredSegmentCollection_INTERFACE_DEFINED__
#define __IFilteredSegmentCollection_INTERFACE_DEFINED__

/* interface IFilteredSegmentCollection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFilteredSegmentCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("222A9651-7B89-11D5-B035-00105A9AF985")
    IFilteredSegmentCollection : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ SegmentIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ SegmentIndexType index,
            /* [retval][out] */ ISegment **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSegment **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFilteredSegmentCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFilteredSegmentCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFilteredSegmentCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFilteredSegmentCollection * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFilteredSegmentCollection * This,
            /* [retval][out] */ SegmentIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFilteredSegmentCollection * This,
            /* [in] */ SegmentIndexType index,
            /* [retval][out] */ ISegment **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFilteredSegmentCollection * This,
            /* [retval][out] */ IEnumSegment **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFilteredSegmentCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } IFilteredSegmentCollectionVtbl;

    interface IFilteredSegmentCollection
    {
        CONST_VTBL struct IFilteredSegmentCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilteredSegmentCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFilteredSegmentCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFilteredSegmentCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFilteredSegmentCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFilteredSegmentCollection_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IFilteredSegmentCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFilteredSegmentCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFilteredSegmentCollection_INTERFACE_DEFINED__ */


#ifndef __ISuperstructureMember_INTERFACE_DEFINED__
#define __ISuperstructureMember_INTERFACE_DEFINED__

/* interface ISuperstructureMember */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISuperstructureMember;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("787BE35B-7C53-11D5-B036-00105A9AF985")
    ISuperstructureMember : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetEndRelease( 
            /* [in] */ Side side,
            /* [in] */ MemberReleaseType newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IsEndReleased( 
            /* [in] */ Side side,
            /* [in] */ MemberReleaseType releaseType,
            /* [retval][out] */ VARIANT_BOOL *pvbIsReleased) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetEndReleaseRemovalStage( 
            /* [in] */ Side side,
            /* [in] */ BSTR removalStage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetEndReleaseRemovalStage( 
            /* [in] */ Side side,
            /* [out] */ BSTR *removalStage) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentLength( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentCount( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ SegmentIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Segment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [retval][out] */ ISegment **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Segment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddSegment( 
            /* [in] */ BSTR stage,
            /* [in] */ ISegment *__MIDL__ISuperstructureMember0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE InsertSegment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *__MIDL__ISuperstructureMember0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveSegmentTo( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CopySegmentTo( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveSegment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ReverseSegments( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentForMemberLocation( 
            /* [in] */ BSTR stage,
            /* [in] */ Float64 location,
            /* [out] */ ISegmentItem **leftSegmentItem,
            /* [out] */ ISegmentItem **rightSegmentItem) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentsForStage( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetMemberSegments( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSegmentItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISuperstructureMember **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsSymmetrical( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IsSymmetrical( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LinkMember( 
            /* [retval][out] */ VARIANT_BOOL *pbIsLinkMember) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LinkMember( 
            /* [in] */ VARIANT_BOOL bIsLinkMember) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperstructureMemberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperstructureMember * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperstructureMember * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperstructureMember * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ISuperstructureMember * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            ISuperstructureMember * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEndRelease )( 
            ISuperstructureMember * This,
            /* [in] */ Side side,
            /* [in] */ MemberReleaseType newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsEndReleased )( 
            ISuperstructureMember * This,
            /* [in] */ Side side,
            /* [in] */ MemberReleaseType releaseType,
            /* [retval][out] */ VARIANT_BOOL *pvbIsReleased);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEndReleaseRemovalStage )( 
            ISuperstructureMember * This,
            /* [in] */ Side side,
            /* [in] */ BSTR removalStage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEndReleaseRemovalStage )( 
            ISuperstructureMember * This,
            /* [in] */ Side side,
            /* [out] */ BSTR *removalStage);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SegmentLength )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SegmentCount )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ SegmentIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Segment )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [retval][out] */ ISegment **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Segment )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSegment )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [in] */ ISegment *__MIDL__ISuperstructureMember0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *InsertSegment )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *__MIDL__ISuperstructureMember0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveSegmentTo )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CopySegmentTo )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveSegment )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReverseSegments )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentForMemberLocation )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [in] */ Float64 location,
            /* [out] */ ISegmentItem **leftSegmentItem,
            /* [out] */ ISegmentItem **rightSegmentItem);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentsForStage )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMemberSegments )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ISuperstructureMember * This,
            /* [retval][out] */ IEnumSegmentItem **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISuperstructureMember * This,
            /* [retval][out] */ ISuperstructureMember **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSymmetrical )( 
            ISuperstructureMember * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsSymmetrical )( 
            ISuperstructureMember * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ISuperstructureMember * This,
            /* [in] */ BSTR stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LinkMember )( 
            ISuperstructureMember * This,
            /* [retval][out] */ VARIANT_BOOL *pbIsLinkMember);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LinkMember )( 
            ISuperstructureMember * This,
            /* [in] */ VARIANT_BOOL bIsLinkMember);
        
        END_INTERFACE
    } ISuperstructureMemberVtbl;

    interface ISuperstructureMember
    {
        CONST_VTBL struct ISuperstructureMemberVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperstructureMember_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperstructureMember_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperstructureMember_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperstructureMember_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ISuperstructureMember_put_Length(This,newVal)	\
    ( (This)->lpVtbl -> put_Length(This,newVal) ) 

#define ISuperstructureMember_SetEndRelease(This,side,newVal)	\
    ( (This)->lpVtbl -> SetEndRelease(This,side,newVal) ) 

#define ISuperstructureMember_IsEndReleased(This,side,releaseType,pvbIsReleased)	\
    ( (This)->lpVtbl -> IsEndReleased(This,side,releaseType,pvbIsReleased) ) 

#define ISuperstructureMember_SetEndReleaseRemovalStage(This,side,removalStage)	\
    ( (This)->lpVtbl -> SetEndReleaseRemovalStage(This,side,removalStage) ) 

#define ISuperstructureMember_GetEndReleaseRemovalStage(This,side,removalStage)	\
    ( (This)->lpVtbl -> GetEndReleaseRemovalStage(This,side,removalStage) ) 

#define ISuperstructureMember_get_SegmentLength(This,stage,pVal)	\
    ( (This)->lpVtbl -> get_SegmentLength(This,stage,pVal) ) 

#define ISuperstructureMember_get_SegmentCount(This,stage,pVal)	\
    ( (This)->lpVtbl -> get_SegmentCount(This,stage,pVal) ) 

#define ISuperstructureMember_get_Segment(This,stage,relPosition,pVal)	\
    ( (This)->lpVtbl -> get_Segment(This,stage,relPosition,pVal) ) 

#define ISuperstructureMember_putref_Segment(This,stage,relPosition,newVal)	\
    ( (This)->lpVtbl -> putref_Segment(This,stage,relPosition,newVal) ) 

#define ISuperstructureMember_AddSegment(This,stage,__MIDL__ISuperstructureMember0000)	\
    ( (This)->lpVtbl -> AddSegment(This,stage,__MIDL__ISuperstructureMember0000) ) 

#define ISuperstructureMember_InsertSegment(This,stage,relPosition,__MIDL__ISuperstructureMember0001)	\
    ( (This)->lpVtbl -> InsertSegment(This,stage,relPosition,__MIDL__ISuperstructureMember0001) ) 

#define ISuperstructureMember_MoveSegmentTo(This,stage,fromRelPosition,toRelPosition)	\
    ( (This)->lpVtbl -> MoveSegmentTo(This,stage,fromRelPosition,toRelPosition) ) 

#define ISuperstructureMember_CopySegmentTo(This,stage,fromRelPosition,toRelPosition)	\
    ( (This)->lpVtbl -> CopySegmentTo(This,stage,fromRelPosition,toRelPosition) ) 

#define ISuperstructureMember_RemoveSegment(This,stage,relPosition)	\
    ( (This)->lpVtbl -> RemoveSegment(This,stage,relPosition) ) 

#define ISuperstructureMember_ReverseSegments(This,stage)	\
    ( (This)->lpVtbl -> ReverseSegments(This,stage) ) 

#define ISuperstructureMember_GetSegmentForMemberLocation(This,stage,location,leftSegmentItem,rightSegmentItem)	\
    ( (This)->lpVtbl -> GetSegmentForMemberLocation(This,stage,location,leftSegmentItem,rightSegmentItem) ) 

#define ISuperstructureMember_GetSegmentsForStage(This,stage,segments)	\
    ( (This)->lpVtbl -> GetSegmentsForStage(This,stage,segments) ) 

#define ISuperstructureMember_GetMemberSegments(This,stage,segments)	\
    ( (This)->lpVtbl -> GetMemberSegments(This,stage,segments) ) 

#define ISuperstructureMember_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ISuperstructureMember_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISuperstructureMember_get_IsSymmetrical(This,pVal)	\
    ( (This)->lpVtbl -> get_IsSymmetrical(This,pVal) ) 

#define ISuperstructureMember_put_IsSymmetrical(This,newVal)	\
    ( (This)->lpVtbl -> put_IsSymmetrical(This,newVal) ) 

#define ISuperstructureMember_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define ISuperstructureMember_get_LinkMember(This,pbIsLinkMember)	\
    ( (This)->lpVtbl -> get_LinkMember(This,pbIsLinkMember) ) 

#define ISuperstructureMember_put_LinkMember(This,bIsLinkMember)	\
    ( (This)->lpVtbl -> put_LinkMember(This,bIsLinkMember) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperstructureMember_INTERFACE_DEFINED__ */


#ifndef __ISuperstructureMemberEvents_INTERFACE_DEFINED__
#define __ISuperstructureMemberEvents_INTERFACE_DEFINED__

/* interface ISuperstructureMemberEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISuperstructureMemberEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("134F50AE-7D36-11d5-B036-00105A9AF985")
    ISuperstructureMemberEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperstructureMemberChanged( 
            /* [in] */ ISuperstructureMember *SuperstructureMember,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperstructureMemberEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperstructureMemberEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperstructureMemberEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperstructureMemberEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperstructureMemberChanged )( 
            ISuperstructureMemberEvents * This,
            /* [in] */ ISuperstructureMember *SuperstructureMember,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change);
        
        END_INTERFACE
    } ISuperstructureMemberEventsVtbl;

    interface ISuperstructureMemberEvents
    {
        CONST_VTBL struct ISuperstructureMemberEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperstructureMemberEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperstructureMemberEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperstructureMemberEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperstructureMemberEvents_OnSuperstructureMemberChanged(This,SuperstructureMember,stage,change)	\
    ( (This)->lpVtbl -> OnSuperstructureMemberChanged(This,SuperstructureMember,stage,change) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperstructureMemberEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumSuperstructureMember_INTERFACE_DEFINED__
#define __IEnumSuperstructureMember_INTERFACE_DEFINED__

/* interface IEnumSuperstructureMember */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSuperstructureMember;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("621D065A-7F97-11d5-B038-00105A9AF985")
    IEnumSuperstructureMember : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSuperstructureMember **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISuperstructureMember **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSuperstructureMemberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSuperstructureMember * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSuperstructureMember * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSuperstructureMember * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSuperstructureMember * This,
            /* [out] */ IEnumSuperstructureMember **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSuperstructureMember * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISuperstructureMember **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSuperstructureMember * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSuperstructureMember * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSuperstructureMemberVtbl;

    interface IEnumSuperstructureMember
    {
        CONST_VTBL struct IEnumSuperstructureMemberVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSuperstructureMember_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSuperstructureMember_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSuperstructureMember_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSuperstructureMember_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSuperstructureMember_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSuperstructureMember_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSuperstructureMember_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSuperstructureMember_INTERFACE_DEFINED__ */


#ifndef __ISuperstructureMembers_INTERFACE_DEFINED__
#define __ISuperstructureMembers_INTERFACE_DEFINED__

/* interface ISuperstructureMembers */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISuperstructureMembers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("672A7920-7F78-11D5-B038-00105A9AF985")
    ISuperstructureMembers : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType position,
            /* [retval][out] */ ISuperstructureMember **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Offset( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Offset( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ISuperstructureMember *__MIDL__ISuperstructureMembers0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ ISuperstructureMember *member) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ CollectionIndexType fromPosition,
            /* [in] */ CollectionIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [in] */ CollectionIndexType fromPosition,
            /* [in] */ CollectionIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType position) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSuperstructureMember **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISuperstructureMembers **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperstructureMembersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperstructureMembers * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperstructureMembers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperstructureMembers * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISuperstructureMembers * This,
            /* [in] */ CollectionIndexType position,
            /* [retval][out] */ ISuperstructureMember **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISuperstructureMembers * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ISuperstructureMembers * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Offset )( 
            ISuperstructureMembers * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Offset )( 
            ISuperstructureMembers * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISuperstructureMembers * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISuperstructureMembers * This,
            /* [in] */ ISuperstructureMember *__MIDL__ISuperstructureMembers0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ISuperstructureMembers * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ ISuperstructureMember *member);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            ISuperstructureMembers * This,
            /* [in] */ CollectionIndexType fromPosition,
            /* [in] */ CollectionIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CopyTo )( 
            ISuperstructureMembers * This,
            /* [in] */ CollectionIndexType fromPosition,
            /* [in] */ CollectionIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ISuperstructureMembers * This,
            /* [in] */ CollectionIndexType position);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            ISuperstructureMembers * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ISuperstructureMembers * This,
            /* [retval][out] */ IEnumSuperstructureMember **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISuperstructureMembers * This,
            /* [retval][out] */ ISuperstructureMembers **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISuperstructureMembers * This);
        
        END_INTERFACE
    } ISuperstructureMembersVtbl;

    interface ISuperstructureMembers
    {
        CONST_VTBL struct ISuperstructureMembersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperstructureMembers_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperstructureMembers_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperstructureMembers_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperstructureMembers_get_Item(This,position,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,position,pVal) ) 

#define ISuperstructureMembers_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ISuperstructureMembers_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ISuperstructureMembers_get_Offset(This,pVal)	\
    ( (This)->lpVtbl -> get_Offset(This,pVal) ) 

#define ISuperstructureMembers_put_Offset(This,newVal)	\
    ( (This)->lpVtbl -> put_Offset(This,newVal) ) 

#define ISuperstructureMembers_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISuperstructureMembers_Add(This,__MIDL__ISuperstructureMembers0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__ISuperstructureMembers0000) ) 

#define ISuperstructureMembers_Insert(This,relPosition,member)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,member) ) 

#define ISuperstructureMembers_MoveTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> MoveTo(This,fromPosition,toPosition) ) 

#define ISuperstructureMembers_CopyTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> CopyTo(This,fromPosition,toPosition) ) 

#define ISuperstructureMembers_Remove(This,position)	\
    ( (This)->lpVtbl -> Remove(This,position) ) 

#define ISuperstructureMembers_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define ISuperstructureMembers_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ISuperstructureMembers_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISuperstructureMembers_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperstructureMembers_INTERFACE_DEFINED__ */


#ifndef __ISuperstructureMembersEvents_INTERFACE_DEFINED__
#define __ISuperstructureMembersEvents_INTERFACE_DEFINED__

/* interface ISuperstructureMembersEvents */
/* [helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISuperstructureMembersEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("621D065B-7F97-11d5-B038-00105A9AF985")
    ISuperstructureMembersEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperstructureMembersChanged( 
            /* [in] */ ISuperstructureMember *SuperstructureMember,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperstructureMembersAdded( 
            /* [in] */ ISuperstructureMember *SuperstructureMember,
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperstructureMembersBeforeRemove( 
            /* [in] */ ISuperstructureMember *SuperstructureMember,
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperstructureMembersMoveTo( 
            /* [in] */ CollectionIndexType from,
            /* [in] */ CollectionIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperstructureMembersCopyTo( 
            /* [in] */ CollectionIndexType from,
            /* [in] */ CollectionIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperstructureMembersReverse( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSuperstructureMembersOffset( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISuperstructureMembersEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISuperstructureMembersEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISuperstructureMembersEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISuperstructureMembersEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperstructureMembersChanged )( 
            ISuperstructureMembersEvents * This,
            /* [in] */ ISuperstructureMember *SuperstructureMember,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperstructureMembersAdded )( 
            ISuperstructureMembersEvents * This,
            /* [in] */ ISuperstructureMember *SuperstructureMember,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperstructureMembersBeforeRemove )( 
            ISuperstructureMembersEvents * This,
            /* [in] */ ISuperstructureMember *SuperstructureMember,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperstructureMembersMoveTo )( 
            ISuperstructureMembersEvents * This,
            /* [in] */ CollectionIndexType from,
            /* [in] */ CollectionIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperstructureMembersCopyTo )( 
            ISuperstructureMembersEvents * This,
            /* [in] */ CollectionIndexType from,
            /* [in] */ CollectionIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperstructureMembersReverse )( 
            ISuperstructureMembersEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSuperstructureMembersOffset )( 
            ISuperstructureMembersEvents * This);
        
        END_INTERFACE
    } ISuperstructureMembersEventsVtbl;

    interface ISuperstructureMembersEvents
    {
        CONST_VTBL struct ISuperstructureMembersEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISuperstructureMembersEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISuperstructureMembersEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISuperstructureMembersEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISuperstructureMembersEvents_OnSuperstructureMembersChanged(This,SuperstructureMember,stage,change)	\
    ( (This)->lpVtbl -> OnSuperstructureMembersChanged(This,SuperstructureMember,stage,change) ) 

#define ISuperstructureMembersEvents_OnSuperstructureMembersAdded(This,SuperstructureMember,index)	\
    ( (This)->lpVtbl -> OnSuperstructureMembersAdded(This,SuperstructureMember,index) ) 

#define ISuperstructureMembersEvents_OnSuperstructureMembersBeforeRemove(This,SuperstructureMember,index)	\
    ( (This)->lpVtbl -> OnSuperstructureMembersBeforeRemove(This,SuperstructureMember,index) ) 

#define ISuperstructureMembersEvents_OnSuperstructureMembersMoveTo(This,from,to)	\
    ( (This)->lpVtbl -> OnSuperstructureMembersMoveTo(This,from,to) ) 

#define ISuperstructureMembersEvents_OnSuperstructureMembersCopyTo(This,from,to)	\
    ( (This)->lpVtbl -> OnSuperstructureMembersCopyTo(This,from,to) ) 

#define ISuperstructureMembersEvents_OnSuperstructureMembersReverse(This)	\
    ( (This)->lpVtbl -> OnSuperstructureMembersReverse(This) ) 

#define ISuperstructureMembersEvents_OnSuperstructureMembersOffset(This)	\
    ( (This)->lpVtbl -> OnSuperstructureMembersOffset(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISuperstructureMembersEvents_INTERFACE_DEFINED__ */


#ifndef __IAxle_INTERFACE_DEFINED__
#define __IAxle_INTERFACE_DEFINED__

/* interface IAxle */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAxle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5373BB51-4420-499E-8ED4-1BAD52DA9F92")
    IAxle : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Weight( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Weight( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IAxle **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAxleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAxle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAxle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAxle * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Weight )( 
            IAxle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Weight )( 
            IAxle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            IAxle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            IAxle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IAxle * This,
            /* [retval][out] */ IAxle **clone);
        
        END_INTERFACE
    } IAxleVtbl;

    interface IAxle
    {
        CONST_VTBL struct IAxleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAxle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAxle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAxle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAxle_get_Weight(This,pVal)	\
    ( (This)->lpVtbl -> get_Weight(This,pVal) ) 

#define IAxle_put_Weight(This,newVal)	\
    ( (This)->lpVtbl -> put_Weight(This,newVal) ) 

#define IAxle_get_Spacing(This,pVal)	\
    ( (This)->lpVtbl -> get_Spacing(This,pVal) ) 

#define IAxle_put_Spacing(This,newVal)	\
    ( (This)->lpVtbl -> put_Spacing(This,newVal) ) 

#define IAxle_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAxle_INTERFACE_DEFINED__ */


#ifndef __IAxleEvents_INTERFACE_DEFINED__
#define __IAxleEvents_INTERFACE_DEFINED__

/* interface IAxleEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IAxleEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("987C8DE4-F396-4d77-8EDD-38CD8974490D")
    IAxleEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxleChanged( 
            /* [in] */ IAxle *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAxleEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAxleEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAxleEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAxleEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxleChanged )( 
            IAxleEvents * This,
            /* [in] */ IAxle *me);
        
        END_INTERFACE
    } IAxleEventsVtbl;

    interface IAxleEvents
    {
        CONST_VTBL struct IAxleEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAxleEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAxleEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAxleEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAxleEvents_OnAxleChanged(This,me)	\
    ( (This)->lpVtbl -> OnAxleChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAxleEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumAxle_INTERFACE_DEFINED__
#define __IEnumAxle_INTERFACE_DEFINED__

/* interface IEnumAxle */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumAxle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ADB71703-9AAF-40b2-9EC2-5C9858D4BD41")
    IEnumAxle : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumAxle **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IAxle **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumAxleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumAxle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumAxle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumAxle * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumAxle * This,
            /* [out] */ IEnumAxle **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumAxle * This,
            /* [in] */ ULONG celt,
            /* [out] */ IAxle **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumAxle * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumAxle * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumAxleVtbl;

    interface IEnumAxle
    {
        CONST_VTBL struct IEnumAxleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumAxle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumAxle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumAxle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumAxle_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumAxle_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumAxle_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumAxle_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumAxle_INTERFACE_DEFINED__ */


#ifndef __IAxles_INTERFACE_DEFINED__
#define __IAxles_INTERFACE_DEFINED__

/* interface IAxles */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAxles;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("096E2A7C-E48C-48F8-A83F-B2C6FEF4A5D8")
    IAxles : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ AxleIndexType position,
            /* [retval][out] */ IAxle **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ AxleIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IAxle *__MIDL__IAxles0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ AxleIndexType relPosition,
            /* [in] */ IAxle *member) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ AxleIndexType fromPosition,
            /* [in] */ AxleIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [in] */ AxleIndexType fromPosition,
            /* [in] */ AxleIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ AxleIndexType position) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumAxle **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IAxles **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAxlesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAxles * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAxles * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAxles * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IAxles * This,
            /* [in] */ AxleIndexType position,
            /* [retval][out] */ IAxle **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IAxles * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IAxles * This,
            /* [retval][out] */ AxleIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IAxles * This,
            /* [in] */ IAxle *__MIDL__IAxles0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IAxles * This,
            /* [in] */ AxleIndexType relPosition,
            /* [in] */ IAxle *member);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            IAxles * This,
            /* [in] */ AxleIndexType fromPosition,
            /* [in] */ AxleIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CopyTo )( 
            IAxles * This,
            /* [in] */ AxleIndexType fromPosition,
            /* [in] */ AxleIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IAxles * This,
            /* [in] */ AxleIndexType position);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            IAxles * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IAxles * This,
            /* [retval][out] */ IEnumAxle **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IAxles * This,
            /* [retval][out] */ IAxles **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IAxles * This);
        
        END_INTERFACE
    } IAxlesVtbl;

    interface IAxles
    {
        CONST_VTBL struct IAxlesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAxles_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAxles_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAxles_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAxles_get_Item(This,position,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,position,pVal) ) 

#define IAxles_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IAxles_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IAxles_Add(This,__MIDL__IAxles0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__IAxles0000) ) 

#define IAxles_Insert(This,relPosition,member)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,member) ) 

#define IAxles_MoveTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> MoveTo(This,fromPosition,toPosition) ) 

#define IAxles_CopyTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> CopyTo(This,fromPosition,toPosition) ) 

#define IAxles_Remove(This,position)	\
    ( (This)->lpVtbl -> Remove(This,position) ) 

#define IAxles_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define IAxles_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IAxles_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IAxles_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAxles_INTERFACE_DEFINED__ */


#ifndef __IAxlesEvents_INTERFACE_DEFINED__
#define __IAxlesEvents_INTERFACE_DEFINED__

/* interface IAxlesEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IAxlesEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12F0E067-6731-48D8-8C4C-9E132FE32336")
    IAxlesEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesChanged( 
            /* [in] */ IAxle *Axle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesAdded( 
            /* [in] */ IAxle *Axle,
            /* [in] */ AxleIndexType idx) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesBeforeRemove( 
            /* [in] */ IAxle *Axle,
            /* [in] */ AxleIndexType idx) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesMoveTo( 
            /* [in] */ AxleIndexType from,
            /* [in] */ AxleIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesCopyTo( 
            /* [in] */ AxleIndexType from,
            /* [in] */ AxleIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesReverse( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAxlesEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAxlesEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAxlesEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAxlesEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesChanged )( 
            IAxlesEvents * This,
            /* [in] */ IAxle *Axle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesAdded )( 
            IAxlesEvents * This,
            /* [in] */ IAxle *Axle,
            /* [in] */ AxleIndexType idx);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesBeforeRemove )( 
            IAxlesEvents * This,
            /* [in] */ IAxle *Axle,
            /* [in] */ AxleIndexType idx);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesMoveTo )( 
            IAxlesEvents * This,
            /* [in] */ AxleIndexType from,
            /* [in] */ AxleIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesCopyTo )( 
            IAxlesEvents * This,
            /* [in] */ AxleIndexType from,
            /* [in] */ AxleIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesReverse )( 
            IAxlesEvents * This);
        
        END_INTERFACE
    } IAxlesEventsVtbl;

    interface IAxlesEvents
    {
        CONST_VTBL struct IAxlesEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAxlesEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAxlesEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAxlesEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAxlesEvents_OnAxlesChanged(This,Axle)	\
    ( (This)->lpVtbl -> OnAxlesChanged(This,Axle) ) 

#define IAxlesEvents_OnAxlesAdded(This,Axle,idx)	\
    ( (This)->lpVtbl -> OnAxlesAdded(This,Axle,idx) ) 

#define IAxlesEvents_OnAxlesBeforeRemove(This,Axle,idx)	\
    ( (This)->lpVtbl -> OnAxlesBeforeRemove(This,Axle,idx) ) 

#define IAxlesEvents_OnAxlesMoveTo(This,from,to)	\
    ( (This)->lpVtbl -> OnAxlesMoveTo(This,from,to) ) 

#define IAxlesEvents_OnAxlesCopyTo(This,from,to)	\
    ( (This)->lpVtbl -> OnAxlesCopyTo(This,from,to) ) 

#define IAxlesEvents_OnAxlesReverse(This)	\
    ( (This)->lpVtbl -> OnAxlesReverse(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAxlesEvents_INTERFACE_DEFINED__ */


#ifndef __IVehicularLoad_INTERFACE_DEFINED__
#define __IVehicularLoad_INTERFACE_DEFINED__

/* interface IVehicularLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVehicularLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D3641235-4943-44D4-BAF0-B178C6771092")
    IVehicularLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Configuration( 
            /* [retval][out] */ VehicularLoadConfigurationType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Configuration( 
            /* [in] */ VehicularLoadConfigurationType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UseNotional( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_UseNotional( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Applicability( 
            /* [retval][out] */ LiveLoadApplicabilityType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Applicability( 
            /* [in] */ LiveLoadApplicabilityType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Axles( 
            /* [retval][out] */ IAxles **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Axles( 
            /* [in] */ IAxles *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VariableAxle( 
            /* [retval][out] */ AxleIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VariableAxle( 
            /* [in] */ AxleIndexType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VariableMaxSpacing( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VariableMaxSpacing( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LaneLoad( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LaneLoad( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SidewalkLoad( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SidewalkLoad( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TruckFactor( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TruckFactor( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LaneFactor( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LaneFactor( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IMTruck( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IMTruck( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IMLane( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IMLane( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IVehicularLoad **clone) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SumAxleWeights( 
            /* [retval][out] */ Float64 *pWeight) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVehicularLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVehicularLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVehicularLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVehicularLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IVehicularLoad * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IVehicularLoad * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Configuration )( 
            IVehicularLoad * This,
            /* [retval][out] */ VehicularLoadConfigurationType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Configuration )( 
            IVehicularLoad * This,
            /* [in] */ VehicularLoadConfigurationType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseNotional )( 
            IVehicularLoad * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseNotional )( 
            IVehicularLoad * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Applicability )( 
            IVehicularLoad * This,
            /* [retval][out] */ LiveLoadApplicabilityType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Applicability )( 
            IVehicularLoad * This,
            /* [in] */ LiveLoadApplicabilityType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Axles )( 
            IVehicularLoad * This,
            /* [retval][out] */ IAxles **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Axles )( 
            IVehicularLoad * This,
            /* [in] */ IAxles *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VariableAxle )( 
            IVehicularLoad * This,
            /* [retval][out] */ AxleIndexType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VariableAxle )( 
            IVehicularLoad * This,
            /* [in] */ AxleIndexType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VariableMaxSpacing )( 
            IVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VariableMaxSpacing )( 
            IVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LaneLoad )( 
            IVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LaneLoad )( 
            IVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SidewalkLoad )( 
            IVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SidewalkLoad )( 
            IVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TruckFactor )( 
            IVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TruckFactor )( 
            IVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LaneFactor )( 
            IVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LaneFactor )( 
            IVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IMTruck )( 
            IVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IMTruck )( 
            IVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IMLane )( 
            IVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IMLane )( 
            IVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IVehicularLoad * This,
            /* [retval][out] */ IVehicularLoad **clone);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SumAxleWeights )( 
            IVehicularLoad * This,
            /* [retval][out] */ Float64 *pWeight);
        
        END_INTERFACE
    } IVehicularLoadVtbl;

    interface IVehicularLoad
    {
        CONST_VTBL struct IVehicularLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVehicularLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVehicularLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVehicularLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVehicularLoad_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IVehicularLoad_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IVehicularLoad_get_Configuration(This,pVal)	\
    ( (This)->lpVtbl -> get_Configuration(This,pVal) ) 

#define IVehicularLoad_put_Configuration(This,newVal)	\
    ( (This)->lpVtbl -> put_Configuration(This,newVal) ) 

#define IVehicularLoad_get_UseNotional(This,pVal)	\
    ( (This)->lpVtbl -> get_UseNotional(This,pVal) ) 

#define IVehicularLoad_put_UseNotional(This,newVal)	\
    ( (This)->lpVtbl -> put_UseNotional(This,newVal) ) 

#define IVehicularLoad_get_Applicability(This,pVal)	\
    ( (This)->lpVtbl -> get_Applicability(This,pVal) ) 

#define IVehicularLoad_put_Applicability(This,newVal)	\
    ( (This)->lpVtbl -> put_Applicability(This,newVal) ) 

#define IVehicularLoad_get_Axles(This,pVal)	\
    ( (This)->lpVtbl -> get_Axles(This,pVal) ) 

#define IVehicularLoad_putref_Axles(This,newVal)	\
    ( (This)->lpVtbl -> putref_Axles(This,newVal) ) 

#define IVehicularLoad_get_VariableAxle(This,pVal)	\
    ( (This)->lpVtbl -> get_VariableAxle(This,pVal) ) 

#define IVehicularLoad_put_VariableAxle(This,newVal)	\
    ( (This)->lpVtbl -> put_VariableAxle(This,newVal) ) 

#define IVehicularLoad_get_VariableMaxSpacing(This,pVal)	\
    ( (This)->lpVtbl -> get_VariableMaxSpacing(This,pVal) ) 

#define IVehicularLoad_put_VariableMaxSpacing(This,newVal)	\
    ( (This)->lpVtbl -> put_VariableMaxSpacing(This,newVal) ) 

#define IVehicularLoad_get_LaneLoad(This,pVal)	\
    ( (This)->lpVtbl -> get_LaneLoad(This,pVal) ) 

#define IVehicularLoad_put_LaneLoad(This,newVal)	\
    ( (This)->lpVtbl -> put_LaneLoad(This,newVal) ) 

#define IVehicularLoad_get_SidewalkLoad(This,pVal)	\
    ( (This)->lpVtbl -> get_SidewalkLoad(This,pVal) ) 

#define IVehicularLoad_put_SidewalkLoad(This,newVal)	\
    ( (This)->lpVtbl -> put_SidewalkLoad(This,newVal) ) 

#define IVehicularLoad_get_TruckFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_TruckFactor(This,pVal) ) 

#define IVehicularLoad_put_TruckFactor(This,newVal)	\
    ( (This)->lpVtbl -> put_TruckFactor(This,newVal) ) 

#define IVehicularLoad_get_LaneFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_LaneFactor(This,pVal) ) 

#define IVehicularLoad_put_LaneFactor(This,newVal)	\
    ( (This)->lpVtbl -> put_LaneFactor(This,newVal) ) 

#define IVehicularLoad_get_IMTruck(This,pVal)	\
    ( (This)->lpVtbl -> get_IMTruck(This,pVal) ) 

#define IVehicularLoad_put_IMTruck(This,newVal)	\
    ( (This)->lpVtbl -> put_IMTruck(This,newVal) ) 

#define IVehicularLoad_get_IMLane(This,pVal)	\
    ( (This)->lpVtbl -> get_IMLane(This,pVal) ) 

#define IVehicularLoad_put_IMLane(This,newVal)	\
    ( (This)->lpVtbl -> put_IMLane(This,newVal) ) 

#define IVehicularLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IVehicularLoad_SumAxleWeights(This,pWeight)	\
    ( (This)->lpVtbl -> SumAxleWeights(This,pWeight) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVehicularLoad_INTERFACE_DEFINED__ */


#ifndef __IVehicularLoadEvents_INTERFACE_DEFINED__
#define __IVehicularLoadEvents_INTERFACE_DEFINED__

/* interface IVehicularLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IVehicularLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F5FEFFE9-F121-4AC3-BF96-66CFCF8BF9BB")
    IVehicularLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVehicularLoadChanged( 
            /* [in] */ IVehicularLoad *me,
            ChangeType type) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVehicularLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVehicularLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVehicularLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVehicularLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVehicularLoadChanged )( 
            IVehicularLoadEvents * This,
            /* [in] */ IVehicularLoad *me,
            ChangeType type);
        
        END_INTERFACE
    } IVehicularLoadEventsVtbl;

    interface IVehicularLoadEvents
    {
        CONST_VTBL struct IVehicularLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVehicularLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVehicularLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVehicularLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVehicularLoadEvents_OnVehicularLoadChanged(This,me,type)	\
    ( (This)->lpVtbl -> OnVehicularLoadChanged(This,me,type) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVehicularLoadEvents_INTERFACE_DEFINED__ */


#ifndef __IEnumVehicularLoad_INTERFACE_DEFINED__
#define __IEnumVehicularLoad_INTERFACE_DEFINED__

/* interface IEnumVehicularLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumVehicularLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("58BEF9B7-DBE2-43b1-BE1D-ECFD1BFAF44D")
    IEnumVehicularLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumVehicularLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IVehicularLoad **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumVehicularLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumVehicularLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumVehicularLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumVehicularLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumVehicularLoad * This,
            /* [out] */ IEnumVehicularLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumVehicularLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ IVehicularLoad **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumVehicularLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumVehicularLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumVehicularLoadVtbl;

    interface IEnumVehicularLoad
    {
        CONST_VTBL struct IEnumVehicularLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumVehicularLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumVehicularLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumVehicularLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumVehicularLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumVehicularLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumVehicularLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumVehicularLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumVehicularLoad_INTERFACE_DEFINED__ */


#ifndef __IVehicularLoads_INTERFACE_DEFINED__
#define __IVehicularLoads_INTERFACE_DEFINED__

/* interface IVehicularLoads */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IVehicularLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C2C4E00-6B72-4509-87A1-30CF44308FEB")
    IVehicularLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VehicleIndexType index,
            /* [retval][out] */ IVehicularLoad **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ VehicleIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumVehicularLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ VehicleIndexType index,
            /* [in] */ IVehicularLoad *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IVehicularLoad *__MIDL__IVehicularLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VehicleIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IVehicularLoads **__MIDL__IVehicularLoads0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVehicularLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVehicularLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVehicularLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVehicularLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IVehicularLoads * This,
            /* [in] */ VehicleIndexType index,
            /* [retval][out] */ IVehicularLoad **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IVehicularLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IVehicularLoads * This,
            /* [retval][out] */ VehicleIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IVehicularLoads * This,
            /* [retval][out] */ IEnumVehicularLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IVehicularLoads * This,
            /* [in] */ VehicleIndexType index,
            /* [in] */ IVehicularLoad *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IVehicularLoads * This,
            /* [in] */ IVehicularLoad *__MIDL__IVehicularLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IVehicularLoads * This,
            /* [in] */ VehicleIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IVehicularLoads * This,
            /* [retval][out] */ IVehicularLoads **__MIDL__IVehicularLoads0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IVehicularLoads * This);
        
        END_INTERFACE
    } IVehicularLoadsVtbl;

    interface IVehicularLoads
    {
        CONST_VTBL struct IVehicularLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVehicularLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVehicularLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVehicularLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVehicularLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IVehicularLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IVehicularLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IVehicularLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IVehicularLoads_Insert(This,index,pVal)	\
    ( (This)->lpVtbl -> Insert(This,index,pVal) ) 

#define IVehicularLoads_Add(This,__MIDL__IVehicularLoads0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__IVehicularLoads0000) ) 

#define IVehicularLoads_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define IVehicularLoads_Clone(This,__MIDL__IVehicularLoads0001)	\
    ( (This)->lpVtbl -> Clone(This,__MIDL__IVehicularLoads0001) ) 

#define IVehicularLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVehicularLoads_INTERFACE_DEFINED__ */


#ifndef __IVehicularLoadsEvents_INTERFACE_DEFINED__
#define __IVehicularLoadsEvents_INTERFACE_DEFINED__

/* interface IVehicularLoadsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IVehicularLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B9505B8A-5469-492E-B12D-C53192613670")
    IVehicularLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVehicularLoadsChanged( 
            /* [in] */ IVehicularLoad *load,
            /* [in] */ ChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVehicularLoadsRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVehicularLoadsAdded( 
            /* [in] */ IVehicularLoad *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVehicularLoadsBeforeRemove( 
            /* [in] */ IVehicularLoad *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVehicularLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVehicularLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVehicularLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVehicularLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVehicularLoadsChanged )( 
            IVehicularLoadsEvents * This,
            /* [in] */ IVehicularLoad *load,
            /* [in] */ ChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVehicularLoadsRenamed )( 
            IVehicularLoadsEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVehicularLoadsAdded )( 
            IVehicularLoadsEvents * This,
            /* [in] */ IVehicularLoad *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVehicularLoadsBeforeRemove )( 
            IVehicularLoadsEvents * This,
            /* [in] */ IVehicularLoad *load);
        
        END_INTERFACE
    } IVehicularLoadsEventsVtbl;

    interface IVehicularLoadsEvents
    {
        CONST_VTBL struct IVehicularLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVehicularLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVehicularLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVehicularLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVehicularLoadsEvents_OnVehicularLoadsChanged(This,load,change)	\
    ( (This)->lpVtbl -> OnVehicularLoadsChanged(This,load,change) ) 

#define IVehicularLoadsEvents_OnVehicularLoadsRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnVehicularLoadsRenamed(This,oldName,newName) ) 

#define IVehicularLoadsEvents_OnVehicularLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnVehicularLoadsAdded(This,load) ) 

#define IVehicularLoadsEvents_OnVehicularLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnVehicularLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVehicularLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __ILiveLoadModel_INTERFACE_DEFINED__
#define __ILiveLoadModel_INTERFACE_DEFINED__

/* interface ILiveLoadModel */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILiveLoadModel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4B6FCD19-775A-4D97-AE26-BEF859766840")
    ILiveLoadModel : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DistributionFactorType( 
            /* [retval][out] */ DistributionFactorType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DistributionFactorType( 
            /* [in] */ DistributionFactorType newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            ILiveLoadModel **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VehicularLoads( 
            /* [retval][out] */ IVehicularLoads **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_VehicularLoads( 
            /* [in] */ IVehicularLoads *newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadModelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoadModel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoadModel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoadModel * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ILiveLoadModel * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ILiveLoadModel * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DistributionFactorType )( 
            ILiveLoadModel * This,
            /* [retval][out] */ DistributionFactorType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DistributionFactorType )( 
            ILiveLoadModel * This,
            /* [in] */ DistributionFactorType newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILiveLoadModel * This,
            ILiveLoadModel **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILiveLoadModel * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VehicularLoads )( 
            ILiveLoadModel * This,
            /* [retval][out] */ IVehicularLoads **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_VehicularLoads )( 
            ILiveLoadModel * This,
            /* [in] */ IVehicularLoads *newVal);
        
        END_INTERFACE
    } ILiveLoadModelVtbl;

    interface ILiveLoadModel
    {
        CONST_VTBL struct ILiveLoadModelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoadModel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoadModel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoadModel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoadModel_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ILiveLoadModel_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ILiveLoadModel_get_DistributionFactorType(This,pVal)	\
    ( (This)->lpVtbl -> get_DistributionFactorType(This,pVal) ) 

#define ILiveLoadModel_put_DistributionFactorType(This,newVal)	\
    ( (This)->lpVtbl -> put_DistributionFactorType(This,newVal) ) 

#define ILiveLoadModel_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ILiveLoadModel_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILiveLoadModel_get_VehicularLoads(This,pVal)	\
    ( (This)->lpVtbl -> get_VehicularLoads(This,pVal) ) 

#define ILiveLoadModel_putref_VehicularLoads(This,newVal)	\
    ( (This)->lpVtbl -> putref_VehicularLoads(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoadModel_INTERFACE_DEFINED__ */


#ifndef __ILiveLoadModelEvents_INTERFACE_DEFINED__
#define __ILiveLoadModelEvents_INTERFACE_DEFINED__

/* interface ILiveLoadModelEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILiveLoadModelEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF38E4BF-C655-4cb6-9A3C-C3146F85272D")
    ILiveLoadModelEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnLiveLoadModelChanged( 
            /* [in] */ ILiveLoadModel *me,
            ChangeType type) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadModelEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoadModelEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoadModelEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoadModelEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLiveLoadModelChanged )( 
            ILiveLoadModelEvents * This,
            /* [in] */ ILiveLoadModel *me,
            ChangeType type);
        
        END_INTERFACE
    } ILiveLoadModelEventsVtbl;

    interface ILiveLoadModelEvents
    {
        CONST_VTBL struct ILiveLoadModelEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoadModelEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoadModelEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoadModelEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoadModelEvents_OnLiveLoadModelChanged(This,me,type)	\
    ( (This)->lpVtbl -> OnLiveLoadModelChanged(This,me,type) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoadModelEvents_INTERFACE_DEFINED__ */


#ifndef __ILiveLoad_INTERFACE_DEFINED__
#define __ILiveLoad_INTERFACE_DEFINED__

/* interface ILiveLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILiveLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7BAF8321-409A-46B8-A7F2-037B4F52A991")
    ILiveLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Design( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Design( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Deflection( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Deflection( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Fatigue( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Fatigue( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Permit( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Permit( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Special( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Special( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Pedestrian( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Pedestrian( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILiveLoad **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LegalRoutineRating( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_LegalRoutineRating( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LegalSpecialRating( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_LegalSpecialRating( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LegalEmergencyRating( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_LegalEmergencyRating( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PermitRoutineRating( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PermitRoutineRating( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PermitSpecialRating( 
            /* [retval][out] */ ILiveLoadModel **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_PermitSpecialRating( 
            /* [in] */ ILiveLoadModel *newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Design )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Design )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Deflection )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Deflection )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fatigue )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Fatigue )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Permit )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Permit )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Special )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Special )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pedestrian )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Pedestrian )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoad **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILiveLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LegalRoutineRating )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_LegalRoutineRating )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LegalSpecialRating )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_LegalSpecialRating )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LegalEmergencyRating )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_LegalEmergencyRating )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PermitRoutineRating )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PermitRoutineRating )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PermitSpecialRating )( 
            ILiveLoad * This,
            /* [retval][out] */ ILiveLoadModel **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_PermitSpecialRating )( 
            ILiveLoad * This,
            /* [in] */ ILiveLoadModel *newVal);
        
        END_INTERFACE
    } ILiveLoadVtbl;

    interface ILiveLoad
    {
        CONST_VTBL struct ILiveLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoad_get_Design(This,pVal)	\
    ( (This)->lpVtbl -> get_Design(This,pVal) ) 

#define ILiveLoad_putref_Design(This,newVal)	\
    ( (This)->lpVtbl -> putref_Design(This,newVal) ) 

#define ILiveLoad_get_Deflection(This,pVal)	\
    ( (This)->lpVtbl -> get_Deflection(This,pVal) ) 

#define ILiveLoad_putref_Deflection(This,newVal)	\
    ( (This)->lpVtbl -> putref_Deflection(This,newVal) ) 

#define ILiveLoad_get_Fatigue(This,pVal)	\
    ( (This)->lpVtbl -> get_Fatigue(This,pVal) ) 

#define ILiveLoad_putref_Fatigue(This,newVal)	\
    ( (This)->lpVtbl -> putref_Fatigue(This,newVal) ) 

#define ILiveLoad_get_Permit(This,pVal)	\
    ( (This)->lpVtbl -> get_Permit(This,pVal) ) 

#define ILiveLoad_putref_Permit(This,newVal)	\
    ( (This)->lpVtbl -> putref_Permit(This,newVal) ) 

#define ILiveLoad_get_Special(This,pVal)	\
    ( (This)->lpVtbl -> get_Special(This,pVal) ) 

#define ILiveLoad_putref_Special(This,newVal)	\
    ( (This)->lpVtbl -> putref_Special(This,newVal) ) 

#define ILiveLoad_get_Pedestrian(This,pVal)	\
    ( (This)->lpVtbl -> get_Pedestrian(This,pVal) ) 

#define ILiveLoad_putref_Pedestrian(This,newVal)	\
    ( (This)->lpVtbl -> putref_Pedestrian(This,newVal) ) 

#define ILiveLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ILiveLoad_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILiveLoad_get_LegalRoutineRating(This,pVal)	\
    ( (This)->lpVtbl -> get_LegalRoutineRating(This,pVal) ) 

#define ILiveLoad_putref_LegalRoutineRating(This,newVal)	\
    ( (This)->lpVtbl -> putref_LegalRoutineRating(This,newVal) ) 

#define ILiveLoad_get_LegalSpecialRating(This,pVal)	\
    ( (This)->lpVtbl -> get_LegalSpecialRating(This,pVal) ) 

#define ILiveLoad_putref_LegalSpecialRating(This,newVal)	\
    ( (This)->lpVtbl -> putref_LegalSpecialRating(This,newVal) ) 

#define ILiveLoad_get_LegalEmergencyRating(This,pVal)	\
    ( (This)->lpVtbl -> get_LegalEmergencyRating(This,pVal) ) 

#define ILiveLoad_putref_LegalEmergencyRating(This,newVal)	\
    ( (This)->lpVtbl -> putref_LegalEmergencyRating(This,newVal) ) 

#define ILiveLoad_get_PermitRoutineRating(This,pVal)	\
    ( (This)->lpVtbl -> get_PermitRoutineRating(This,pVal) ) 

#define ILiveLoad_putref_PermitRoutineRating(This,newVal)	\
    ( (This)->lpVtbl -> putref_PermitRoutineRating(This,newVal) ) 

#define ILiveLoad_get_PermitSpecialRating(This,pVal)	\
    ( (This)->lpVtbl -> get_PermitSpecialRating(This,pVal) ) 

#define ILiveLoad_putref_PermitSpecialRating(This,newVal)	\
    ( (This)->lpVtbl -> putref_PermitSpecialRating(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoad_INTERFACE_DEFINED__ */


#ifndef __ILiveLoadEvents_INTERFACE_DEFINED__
#define __ILiveLoadEvents_INTERFACE_DEFINED__

/* interface ILiveLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILiveLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0A1AA077-5362-461F-8CB1-09007BF14BEB")
    ILiveLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLiveLoadChanged( 
            /* [in] */ ILiveLoad *me,
            LiveLoadModelType lltype) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILiveLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILiveLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILiveLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILiveLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLiveLoadChanged )( 
            ILiveLoadEvents * This,
            /* [in] */ ILiveLoad *me,
            LiveLoadModelType lltype);
        
        END_INTERFACE
    } ILiveLoadEventsVtbl;

    interface ILiveLoadEvents
    {
        CONST_VTBL struct ILiveLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiveLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILiveLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILiveLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILiveLoadEvents_OnLiveLoadChanged(This,me,lltype)	\
    ( (This)->lpVtbl -> OnLiveLoadChanged(This,me,lltype) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILiveLoadEvents_INTERFACE_DEFINED__ */


#ifndef __IDistributionFactor_INTERFACE_DEFINED__
#define __IDistributionFactor_INTERFACE_DEFINED__

/* interface IDistributionFactor */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDistributionFactor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E6ECB213-881C-11D5-B043-00105A9AF985")
    IDistributionFactor : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GPMSgl( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GPMSgl( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GPMMul( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GPMMul( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GNMSgl( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GNMSgl( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GNMMul( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GNMMul( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GVSgl( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GVSgl( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GVMul( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GVMul( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GDSgl( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GDSgl( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GDMul( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GDMul( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GTSgl( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GTSgl( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GRSgl( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GRSgl( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GRMul( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GRMul( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetGFat( 
            /* [out] */ Float64 *pMom,
            /* [out] */ Float64 *pShear) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetGFat( 
            /* [in] */ Float64 gMom,
            /* [in] */ Float64 gShear) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GPedestrian( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GPedestrian( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetG( 
            /* [in] */ Float64 PMSgl,
            /* [in] */ Float64 PMMul,
            /* [in] */ Float64 NMSgl,
            /* [in] */ Float64 NMMul,
            /* [in] */ Float64 VSgl,
            /* [in] */ Float64 VMul,
            /* [in] */ Float64 DSgl,
            /* [in] */ Float64 DMul,
            /* [in] */ Float64 RSgl,
            /* [in] */ Float64 RMul,
            /* [in] */ Float64 TSgl,
            /* [in] */ Float64 TMul,
            /* [in] */ Float64 FatM,
            /* [in] */ Float64 FatV,
            /* [in] */ Float64 Pedes) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetG( 
            /* [out] */ Float64 *PMSgl,
            /* [out] */ Float64 *PMMul,
            /* [out] */ Float64 *NMSgl,
            /* [out] */ Float64 *NMMul,
            /* [out] */ Float64 *VSgl,
            /* [out] */ Float64 *VMul,
            /* [out] */ Float64 *DSgl,
            /* [out] */ Float64 *DMul,
            /* [out] */ Float64 *RSgl,
            /* [out] */ Float64 *RMul,
            /* [out] */ Float64 *TSgl,
            /* [out] */ Float64 *TMul,
            /* [out] */ Float64 *FatM,
            /* [out] */ Float64 *FatV,
            /* [out] */ Float64 *Pedes) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IDistributionFactor **__MIDL__IDistributionFactor0000) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GTMul( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GTMul( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributionFactorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributionFactor * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributionFactor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributionFactor * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GPMSgl )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GPMSgl )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GPMMul )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GPMMul )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GNMSgl )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GNMSgl )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GNMMul )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GNMMul )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GVSgl )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GVSgl )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GVMul )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GVMul )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GDSgl )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GDSgl )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GDMul )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GDMul )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GTSgl )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GTSgl )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GRSgl )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GRSgl )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GRMul )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GRMul )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetGFat )( 
            IDistributionFactor * This,
            /* [out] */ Float64 *pMom,
            /* [out] */ Float64 *pShear);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetGFat )( 
            IDistributionFactor * This,
            /* [in] */ Float64 gMom,
            /* [in] */ Float64 gShear);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GPedestrian )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GPedestrian )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetG )( 
            IDistributionFactor * This,
            /* [in] */ Float64 PMSgl,
            /* [in] */ Float64 PMMul,
            /* [in] */ Float64 NMSgl,
            /* [in] */ Float64 NMMul,
            /* [in] */ Float64 VSgl,
            /* [in] */ Float64 VMul,
            /* [in] */ Float64 DSgl,
            /* [in] */ Float64 DMul,
            /* [in] */ Float64 RSgl,
            /* [in] */ Float64 RMul,
            /* [in] */ Float64 TSgl,
            /* [in] */ Float64 TMul,
            /* [in] */ Float64 FatM,
            /* [in] */ Float64 FatV,
            /* [in] */ Float64 Pedes);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetG )( 
            IDistributionFactor * This,
            /* [out] */ Float64 *PMSgl,
            /* [out] */ Float64 *PMMul,
            /* [out] */ Float64 *NMSgl,
            /* [out] */ Float64 *NMMul,
            /* [out] */ Float64 *VSgl,
            /* [out] */ Float64 *VMul,
            /* [out] */ Float64 *DSgl,
            /* [out] */ Float64 *DMul,
            /* [out] */ Float64 *RSgl,
            /* [out] */ Float64 *RMul,
            /* [out] */ Float64 *TSgl,
            /* [out] */ Float64 *TMul,
            /* [out] */ Float64 *FatM,
            /* [out] */ Float64 *FatV,
            /* [out] */ Float64 *Pedes);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDistributionFactor * This,
            /* [retval][out] */ IDistributionFactor **__MIDL__IDistributionFactor0000);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GTMul )( 
            IDistributionFactor * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GTMul )( 
            IDistributionFactor * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IDistributionFactorVtbl;

    interface IDistributionFactor
    {
        CONST_VTBL struct IDistributionFactorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributionFactor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributionFactor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributionFactor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributionFactor_get_GPMSgl(This,pVal)	\
    ( (This)->lpVtbl -> get_GPMSgl(This,pVal) ) 

#define IDistributionFactor_put_GPMSgl(This,newVal)	\
    ( (This)->lpVtbl -> put_GPMSgl(This,newVal) ) 

#define IDistributionFactor_get_GPMMul(This,pVal)	\
    ( (This)->lpVtbl -> get_GPMMul(This,pVal) ) 

#define IDistributionFactor_put_GPMMul(This,newVal)	\
    ( (This)->lpVtbl -> put_GPMMul(This,newVal) ) 

#define IDistributionFactor_get_GNMSgl(This,pVal)	\
    ( (This)->lpVtbl -> get_GNMSgl(This,pVal) ) 

#define IDistributionFactor_put_GNMSgl(This,newVal)	\
    ( (This)->lpVtbl -> put_GNMSgl(This,newVal) ) 

#define IDistributionFactor_get_GNMMul(This,pVal)	\
    ( (This)->lpVtbl -> get_GNMMul(This,pVal) ) 

#define IDistributionFactor_put_GNMMul(This,newVal)	\
    ( (This)->lpVtbl -> put_GNMMul(This,newVal) ) 

#define IDistributionFactor_get_GVSgl(This,pVal)	\
    ( (This)->lpVtbl -> get_GVSgl(This,pVal) ) 

#define IDistributionFactor_put_GVSgl(This,newVal)	\
    ( (This)->lpVtbl -> put_GVSgl(This,newVal) ) 

#define IDistributionFactor_get_GVMul(This,pVal)	\
    ( (This)->lpVtbl -> get_GVMul(This,pVal) ) 

#define IDistributionFactor_put_GVMul(This,newVal)	\
    ( (This)->lpVtbl -> put_GVMul(This,newVal) ) 

#define IDistributionFactor_get_GDSgl(This,pVal)	\
    ( (This)->lpVtbl -> get_GDSgl(This,pVal) ) 

#define IDistributionFactor_put_GDSgl(This,newVal)	\
    ( (This)->lpVtbl -> put_GDSgl(This,newVal) ) 

#define IDistributionFactor_get_GDMul(This,pVal)	\
    ( (This)->lpVtbl -> get_GDMul(This,pVal) ) 

#define IDistributionFactor_put_GDMul(This,newVal)	\
    ( (This)->lpVtbl -> put_GDMul(This,newVal) ) 

#define IDistributionFactor_get_GTSgl(This,pVal)	\
    ( (This)->lpVtbl -> get_GTSgl(This,pVal) ) 

#define IDistributionFactor_put_GTSgl(This,newVal)	\
    ( (This)->lpVtbl -> put_GTSgl(This,newVal) ) 

#define IDistributionFactor_get_GRSgl(This,pVal)	\
    ( (This)->lpVtbl -> get_GRSgl(This,pVal) ) 

#define IDistributionFactor_put_GRSgl(This,newVal)	\
    ( (This)->lpVtbl -> put_GRSgl(This,newVal) ) 

#define IDistributionFactor_get_GRMul(This,pVal)	\
    ( (This)->lpVtbl -> get_GRMul(This,pVal) ) 

#define IDistributionFactor_put_GRMul(This,newVal)	\
    ( (This)->lpVtbl -> put_GRMul(This,newVal) ) 

#define IDistributionFactor_GetGFat(This,pMom,pShear)	\
    ( (This)->lpVtbl -> GetGFat(This,pMom,pShear) ) 

#define IDistributionFactor_SetGFat(This,gMom,gShear)	\
    ( (This)->lpVtbl -> SetGFat(This,gMom,gShear) ) 

#define IDistributionFactor_get_GPedestrian(This,pVal)	\
    ( (This)->lpVtbl -> get_GPedestrian(This,pVal) ) 

#define IDistributionFactor_put_GPedestrian(This,newVal)	\
    ( (This)->lpVtbl -> put_GPedestrian(This,newVal) ) 

#define IDistributionFactor_SetG(This,PMSgl,PMMul,NMSgl,NMMul,VSgl,VMul,DSgl,DMul,RSgl,RMul,TSgl,TMul,FatM,FatV,Pedes)	\
    ( (This)->lpVtbl -> SetG(This,PMSgl,PMMul,NMSgl,NMMul,VSgl,VMul,DSgl,DMul,RSgl,RMul,TSgl,TMul,FatM,FatV,Pedes) ) 

#define IDistributionFactor_GetG(This,PMSgl,PMMul,NMSgl,NMMul,VSgl,VMul,DSgl,DMul,RSgl,RMul,TSgl,TMul,FatM,FatV,Pedes)	\
    ( (This)->lpVtbl -> GetG(This,PMSgl,PMMul,NMSgl,NMMul,VSgl,VMul,DSgl,DMul,RSgl,RMul,TSgl,TMul,FatM,FatV,Pedes) ) 

#define IDistributionFactor_Clone(This,__MIDL__IDistributionFactor0000)	\
    ( (This)->lpVtbl -> Clone(This,__MIDL__IDistributionFactor0000) ) 

#define IDistributionFactor_get_GTMul(This,pVal)	\
    ( (This)->lpVtbl -> get_GTMul(This,pVal) ) 

#define IDistributionFactor_put_GTMul(This,newVal)	\
    ( (This)->lpVtbl -> put_GTMul(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributionFactor_INTERFACE_DEFINED__ */


#ifndef __ISupport_INTERFACE_DEFINED__
#define __ISupport_INTERFACE_DEFINED__

/* interface ISupport */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISupport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("80D1B106-829D-11D5-B03C-00105A9AF985")
    ISupport : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BoundaryCondition( 
            /* [retval][out] */ BoundaryConditionType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BoundaryCondition( 
            /* [in] */ BoundaryConditionType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomOffset( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BottomOffset( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentLength( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentCount( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ SegmentIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Segment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [retval][out] */ ISegment **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Segment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddSegment( 
            /* [in] */ BSTR stage,
            /* [in] */ ISegment *__MIDL__ISupport0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE InsertSegment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *__MIDL__ISupport0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveSegmentTo( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CopySegmentTo( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveSegment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ReverseSegments( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentForMemberLocation( 
            /* [in] */ BSTR stage,
            /* [in] */ Float64 location,
            /* [out] */ ISegmentItem **leftSegmentItem,
            /* [out] */ ISegmentItem **rightSegmentItem) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentsForStage( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetMemberSegments( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSegmentItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISupport **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsSymmetrical( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IsSymmetrical( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLoadModifier( 
            /* [in] */ LoadCombinationType type,
            /* [out] */ Float64 *minVal,
            /* [out] */ Float64 *maxVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetLoadModifier( 
            /* [in] */ LoadCombinationType type,
            /* [in] */ Float64 minVal,
            /* [in] */ Float64 maxVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DistributionFactor( 
            /* [retval][out] */ IDistributionFactor **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_DistributionFactor( 
            /* [in] */ IDistributionFactor *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopRelease( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TopRelease( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddAssociatedSupport( 
            /* [in] */ SupportIDType id) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAssociatedSupportCount( 
            /* [retval][out] */ SupportIndexType *pCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAssociatedSupportID( 
            /* [in] */ IndexType index,
            /* [retval][out] */ SupportIDType *pID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupport * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupport * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ISupport * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            ISupport * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BoundaryCondition )( 
            ISupport * This,
            /* [retval][out] */ BoundaryConditionType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BoundaryCondition )( 
            ISupport * This,
            /* [in] */ BoundaryConditionType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomOffset )( 
            ISupport * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BottomOffset )( 
            ISupport * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SegmentLength )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SegmentCount )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ SegmentIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Segment )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [retval][out] */ ISegment **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Segment )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSegment )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ ISegment *__MIDL__ISupport0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *InsertSegment )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *__MIDL__ISupport0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveSegmentTo )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CopySegmentTo )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveSegment )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReverseSegments )( 
            ISupport * This,
            /* [in] */ BSTR stage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentForMemberLocation )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ Float64 location,
            /* [out] */ ISegmentItem **leftSegmentItem,
            /* [out] */ ISegmentItem **rightSegmentItem);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentsForStage )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMemberSegments )( 
            ISupport * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ISupport * This,
            /* [retval][out] */ IEnumSegmentItem **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISupport * This,
            /* [retval][out] */ ISupport **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSymmetrical )( 
            ISupport * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsSymmetrical )( 
            ISupport * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ISupport * This,
            /* [in] */ BSTR stage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLoadModifier )( 
            ISupport * This,
            /* [in] */ LoadCombinationType type,
            /* [out] */ Float64 *minVal,
            /* [out] */ Float64 *maxVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLoadModifier )( 
            ISupport * This,
            /* [in] */ LoadCombinationType type,
            /* [in] */ Float64 minVal,
            /* [in] */ Float64 maxVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DistributionFactor )( 
            ISupport * This,
            /* [retval][out] */ IDistributionFactor **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DistributionFactor )( 
            ISupport * This,
            /* [in] */ IDistributionFactor *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopRelease )( 
            ISupport * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TopRelease )( 
            ISupport * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddAssociatedSupport )( 
            ISupport * This,
            /* [in] */ SupportIDType id);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAssociatedSupportCount )( 
            ISupport * This,
            /* [retval][out] */ SupportIndexType *pCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAssociatedSupportID )( 
            ISupport * This,
            /* [in] */ IndexType index,
            /* [retval][out] */ SupportIDType *pID);
        
        END_INTERFACE
    } ISupportVtbl;

    interface ISupport
    {
        CONST_VTBL struct ISupportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupport_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupport_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupport_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupport_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ISupport_put_Length(This,newVal)	\
    ( (This)->lpVtbl -> put_Length(This,newVal) ) 

#define ISupport_get_BoundaryCondition(This,pVal)	\
    ( (This)->lpVtbl -> get_BoundaryCondition(This,pVal) ) 

#define ISupport_put_BoundaryCondition(This,newVal)	\
    ( (This)->lpVtbl -> put_BoundaryCondition(This,newVal) ) 

#define ISupport_get_BottomOffset(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomOffset(This,pVal) ) 

#define ISupport_put_BottomOffset(This,newVal)	\
    ( (This)->lpVtbl -> put_BottomOffset(This,newVal) ) 

#define ISupport_get_SegmentLength(This,stage,pVal)	\
    ( (This)->lpVtbl -> get_SegmentLength(This,stage,pVal) ) 

#define ISupport_get_SegmentCount(This,stage,pVal)	\
    ( (This)->lpVtbl -> get_SegmentCount(This,stage,pVal) ) 

#define ISupport_get_Segment(This,stage,relPosition,pVal)	\
    ( (This)->lpVtbl -> get_Segment(This,stage,relPosition,pVal) ) 

#define ISupport_putref_Segment(This,stage,relPosition,newVal)	\
    ( (This)->lpVtbl -> putref_Segment(This,stage,relPosition,newVal) ) 

#define ISupport_AddSegment(This,stage,__MIDL__ISupport0000)	\
    ( (This)->lpVtbl -> AddSegment(This,stage,__MIDL__ISupport0000) ) 

#define ISupport_InsertSegment(This,stage,relPosition,__MIDL__ISupport0001)	\
    ( (This)->lpVtbl -> InsertSegment(This,stage,relPosition,__MIDL__ISupport0001) ) 

#define ISupport_MoveSegmentTo(This,stage,fromRelPosition,toRelPosition)	\
    ( (This)->lpVtbl -> MoveSegmentTo(This,stage,fromRelPosition,toRelPosition) ) 

#define ISupport_CopySegmentTo(This,stage,fromRelPosition,toRelPosition)	\
    ( (This)->lpVtbl -> CopySegmentTo(This,stage,fromRelPosition,toRelPosition) ) 

#define ISupport_RemoveSegment(This,stage,relPosition)	\
    ( (This)->lpVtbl -> RemoveSegment(This,stage,relPosition) ) 

#define ISupport_ReverseSegments(This,stage)	\
    ( (This)->lpVtbl -> ReverseSegments(This,stage) ) 

#define ISupport_GetSegmentForMemberLocation(This,stage,location,leftSegmentItem,rightSegmentItem)	\
    ( (This)->lpVtbl -> GetSegmentForMemberLocation(This,stage,location,leftSegmentItem,rightSegmentItem) ) 

#define ISupport_GetSegmentsForStage(This,stage,segments)	\
    ( (This)->lpVtbl -> GetSegmentsForStage(This,stage,segments) ) 

#define ISupport_GetMemberSegments(This,stage,segments)	\
    ( (This)->lpVtbl -> GetMemberSegments(This,stage,segments) ) 

#define ISupport_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ISupport_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISupport_get_IsSymmetrical(This,pVal)	\
    ( (This)->lpVtbl -> get_IsSymmetrical(This,pVal) ) 

#define ISupport_put_IsSymmetrical(This,newVal)	\
    ( (This)->lpVtbl -> put_IsSymmetrical(This,newVal) ) 

#define ISupport_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define ISupport_GetLoadModifier(This,type,minVal,maxVal)	\
    ( (This)->lpVtbl -> GetLoadModifier(This,type,minVal,maxVal) ) 

#define ISupport_SetLoadModifier(This,type,minVal,maxVal)	\
    ( (This)->lpVtbl -> SetLoadModifier(This,type,minVal,maxVal) ) 

#define ISupport_get_DistributionFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_DistributionFactor(This,pVal) ) 

#define ISupport_putref_DistributionFactor(This,newVal)	\
    ( (This)->lpVtbl -> putref_DistributionFactor(This,newVal) ) 

#define ISupport_get_TopRelease(This,pVal)	\
    ( (This)->lpVtbl -> get_TopRelease(This,pVal) ) 

#define ISupport_put_TopRelease(This,newVal)	\
    ( (This)->lpVtbl -> put_TopRelease(This,newVal) ) 

#define ISupport_AddAssociatedSupport(This,id)	\
    ( (This)->lpVtbl -> AddAssociatedSupport(This,id) ) 

#define ISupport_GetAssociatedSupportCount(This,pCount)	\
    ( (This)->lpVtbl -> GetAssociatedSupportCount(This,pCount) ) 

#define ISupport_GetAssociatedSupportID(This,index,pID)	\
    ( (This)->lpVtbl -> GetAssociatedSupportID(This,index,pID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupport_INTERFACE_DEFINED__ */


#ifndef __IEnumSupport_INTERFACE_DEFINED__
#define __IEnumSupport_INTERFACE_DEFINED__

/* interface IEnumSupport */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSupport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EA251D3A-82BB-11d5-B03C-00105A9AF985")
    IEnumSupport : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSupport **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISupport **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSupportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSupport * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSupport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSupport * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSupport * This,
            /* [out] */ IEnumSupport **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSupport * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISupport **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSupport * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSupport * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSupportVtbl;

    interface IEnumSupport
    {
        CONST_VTBL struct IEnumSupportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSupport_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSupport_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSupport_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSupport_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSupport_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSupport_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSupport_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSupport_INTERFACE_DEFINED__ */


#ifndef __ISupports_INTERFACE_DEFINED__
#define __ISupports_INTERFACE_DEFINED__

/* interface ISupports */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISupports;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EA251D39-82BB-11d5-B03C-00105A9AF985")
    ISupports : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ SupportIndexType position,
            /* [retval][out] */ ISupport **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ SupportIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ISupport *__MIDL__ISupports0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ SupportIndexType relPosition,
            /* [in] */ ISupport *member) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ SupportIndexType fromPosition,
            /* [in] */ SupportIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [in] */ SupportIndexType fromPosition,
            /* [in] */ SupportIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ SupportIndexType position) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSupport **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISupports **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupports * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupports * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupports * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISupports * This,
            /* [in] */ SupportIndexType position,
            /* [retval][out] */ ISupport **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISupports * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISupports * This,
            /* [retval][out] */ SupportIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISupports * This,
            /* [in] */ ISupport *__MIDL__ISupports0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ISupports * This,
            /* [in] */ SupportIndexType relPosition,
            /* [in] */ ISupport *member);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            ISupports * This,
            /* [in] */ SupportIndexType fromPosition,
            /* [in] */ SupportIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CopyTo )( 
            ISupports * This,
            /* [in] */ SupportIndexType fromPosition,
            /* [in] */ SupportIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ISupports * This,
            /* [in] */ SupportIndexType position);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            ISupports * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ISupports * This,
            /* [retval][out] */ IEnumSupport **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISupports * This,
            /* [retval][out] */ ISupports **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISupports * This);
        
        END_INTERFACE
    } ISupportsVtbl;

    interface ISupports
    {
        CONST_VTBL struct ISupportsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupports_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupports_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupports_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupports_get_Item(This,position,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,position,pVal) ) 

#define ISupports_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ISupports_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISupports_Add(This,__MIDL__ISupports0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__ISupports0000) ) 

#define ISupports_Insert(This,relPosition,member)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,member) ) 

#define ISupports_MoveTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> MoveTo(This,fromPosition,toPosition) ) 

#define ISupports_CopyTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> CopyTo(This,fromPosition,toPosition) ) 

#define ISupports_Remove(This,position)	\
    ( (This)->lpVtbl -> Remove(This,position) ) 

#define ISupports_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define ISupports_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ISupports_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISupports_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupports_INTERFACE_DEFINED__ */


#ifndef __ITemporarySupport_INTERFACE_DEFINED__
#define __ITemporarySupport_INTERFACE_DEFINED__

/* interface ITemporarySupport */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITemporarySupport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("80D1B10C-829D-11D5-B03C-00105A9AF985")
    ITemporarySupport : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BoundaryCondition( 
            /* [retval][out] */ BoundaryConditionType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BoundaryCondition( 
            /* [in] */ BoundaryConditionType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BottomOffset( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BottomOffset( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentLength( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentCount( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ SegmentIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Segment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [retval][out] */ ISegment **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Segment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddSegment( 
            /* [in] */ BSTR stage,
            /* [in] */ ISegment *__MIDL__ITemporarySupport0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE InsertSegment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *__MIDL__ITemporarySupport0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveSegmentTo( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CopySegmentTo( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveSegment( 
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ReverseSegments( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentForMemberLocation( 
            /* [in] */ BSTR stage,
            /* [in] */ Float64 location,
            /* [out] */ ISegmentItem **leftSegmentItem,
            /* [out] */ ISegmentItem **rightSegmentItem) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentsForStage( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetMemberSegments( 
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSegmentItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ITemporarySupport **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsSymmetrical( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IsSymmetrical( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StageRemoved( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StageRemoved( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ SupportIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ID( 
            /* [in] */ SupportIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLoadModifier( 
            /* [in] */ LoadCombinationType type,
            /* [out] */ Float64 *minVal,
            /* [out] */ Float64 *maxVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetLoadModifier( 
            /* [in] */ LoadCombinationType type,
            /* [in] */ Float64 minVal,
            /* [in] */ Float64 maxVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DistributionFactor( 
            /* [retval][out] */ IDistributionFactor **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_DistributionFactor( 
            /* [in] */ IDistributionFactor *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TopRelease( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TopRelease( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OmitReaction( 
            /* [retval][out] */ VARIANT_BOOL *pbOmit) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OmitReaction( 
            /* [in] */ VARIANT_BOOL bOmit) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemporarySupportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemporarySupport * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemporarySupport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemporarySupport * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ITemporarySupport * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            ITemporarySupport * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BoundaryCondition )( 
            ITemporarySupport * This,
            /* [retval][out] */ BoundaryConditionType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BoundaryCondition )( 
            ITemporarySupport * This,
            /* [in] */ BoundaryConditionType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BottomOffset )( 
            ITemporarySupport * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BottomOffset )( 
            ITemporarySupport * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SegmentLength )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SegmentCount )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ SegmentIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Segment )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [retval][out] */ ISegment **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Segment )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSegment )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ ISegment *__MIDL__ITemporarySupport0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *InsertSegment )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition,
            /* [in] */ ISegment *__MIDL__ITemporarySupport0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveSegmentTo )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CopySegmentTo )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType fromRelPosition,
            /* [in] */ SegmentIndexType toRelPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveSegment )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ SegmentIndexType relPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReverseSegments )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentForMemberLocation )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [in] */ Float64 location,
            /* [out] */ ISegmentItem **leftSegmentItem,
            /* [out] */ ISegmentItem **rightSegmentItem);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentsForStage )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMemberSegments )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage,
            /* [retval][out] */ IFilteredSegmentCollection **segments);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ITemporarySupport * This,
            /* [retval][out] */ IEnumSegmentItem **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITemporarySupport * This,
            /* [retval][out] */ ITemporarySupport **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSymmetrical )( 
            ITemporarySupport * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsSymmetrical )( 
            ITemporarySupport * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            ITemporarySupport * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Location )( 
            ITemporarySupport * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StageRemoved )( 
            ITemporarySupport * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StageRemoved )( 
            ITemporarySupport * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ITemporarySupport * This,
            /* [in] */ BSTR stage);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            ITemporarySupport * This,
            /* [retval][out] */ SupportIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ID )( 
            ITemporarySupport * This,
            /* [in] */ SupportIDType newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLoadModifier )( 
            ITemporarySupport * This,
            /* [in] */ LoadCombinationType type,
            /* [out] */ Float64 *minVal,
            /* [out] */ Float64 *maxVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLoadModifier )( 
            ITemporarySupport * This,
            /* [in] */ LoadCombinationType type,
            /* [in] */ Float64 minVal,
            /* [in] */ Float64 maxVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DistributionFactor )( 
            ITemporarySupport * This,
            /* [retval][out] */ IDistributionFactor **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DistributionFactor )( 
            ITemporarySupport * This,
            /* [in] */ IDistributionFactor *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopRelease )( 
            ITemporarySupport * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TopRelease )( 
            ITemporarySupport * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OmitReaction )( 
            ITemporarySupport * This,
            /* [retval][out] */ VARIANT_BOOL *pbOmit);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OmitReaction )( 
            ITemporarySupport * This,
            /* [in] */ VARIANT_BOOL bOmit);
        
        END_INTERFACE
    } ITemporarySupportVtbl;

    interface ITemporarySupport
    {
        CONST_VTBL struct ITemporarySupportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemporarySupport_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemporarySupport_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemporarySupport_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemporarySupport_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ITemporarySupport_put_Length(This,newVal)	\
    ( (This)->lpVtbl -> put_Length(This,newVal) ) 

#define ITemporarySupport_get_BoundaryCondition(This,pVal)	\
    ( (This)->lpVtbl -> get_BoundaryCondition(This,pVal) ) 

#define ITemporarySupport_put_BoundaryCondition(This,newVal)	\
    ( (This)->lpVtbl -> put_BoundaryCondition(This,newVal) ) 

#define ITemporarySupport_get_BottomOffset(This,pVal)	\
    ( (This)->lpVtbl -> get_BottomOffset(This,pVal) ) 

#define ITemporarySupport_put_BottomOffset(This,newVal)	\
    ( (This)->lpVtbl -> put_BottomOffset(This,newVal) ) 

#define ITemporarySupport_get_SegmentLength(This,stage,pVal)	\
    ( (This)->lpVtbl -> get_SegmentLength(This,stage,pVal) ) 

#define ITemporarySupport_get_SegmentCount(This,stage,pVal)	\
    ( (This)->lpVtbl -> get_SegmentCount(This,stage,pVal) ) 

#define ITemporarySupport_get_Segment(This,stage,relPosition,pVal)	\
    ( (This)->lpVtbl -> get_Segment(This,stage,relPosition,pVal) ) 

#define ITemporarySupport_putref_Segment(This,stage,relPosition,newVal)	\
    ( (This)->lpVtbl -> putref_Segment(This,stage,relPosition,newVal) ) 

#define ITemporarySupport_AddSegment(This,stage,__MIDL__ITemporarySupport0000)	\
    ( (This)->lpVtbl -> AddSegment(This,stage,__MIDL__ITemporarySupport0000) ) 

#define ITemporarySupport_InsertSegment(This,stage,relPosition,__MIDL__ITemporarySupport0001)	\
    ( (This)->lpVtbl -> InsertSegment(This,stage,relPosition,__MIDL__ITemporarySupport0001) ) 

#define ITemporarySupport_MoveSegmentTo(This,stage,fromRelPosition,toRelPosition)	\
    ( (This)->lpVtbl -> MoveSegmentTo(This,stage,fromRelPosition,toRelPosition) ) 

#define ITemporarySupport_CopySegmentTo(This,stage,fromRelPosition,toRelPosition)	\
    ( (This)->lpVtbl -> CopySegmentTo(This,stage,fromRelPosition,toRelPosition) ) 

#define ITemporarySupport_RemoveSegment(This,stage,relPosition)	\
    ( (This)->lpVtbl -> RemoveSegment(This,stage,relPosition) ) 

#define ITemporarySupport_ReverseSegments(This,stage)	\
    ( (This)->lpVtbl -> ReverseSegments(This,stage) ) 

#define ITemporarySupport_GetSegmentForMemberLocation(This,stage,location,leftSegmentItem,rightSegmentItem)	\
    ( (This)->lpVtbl -> GetSegmentForMemberLocation(This,stage,location,leftSegmentItem,rightSegmentItem) ) 

#define ITemporarySupport_GetSegmentsForStage(This,stage,segments)	\
    ( (This)->lpVtbl -> GetSegmentsForStage(This,stage,segments) ) 

#define ITemporarySupport_GetMemberSegments(This,stage,segments)	\
    ( (This)->lpVtbl -> GetMemberSegments(This,stage,segments) ) 

#define ITemporarySupport_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ITemporarySupport_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ITemporarySupport_get_IsSymmetrical(This,pVal)	\
    ( (This)->lpVtbl -> get_IsSymmetrical(This,pVal) ) 

#define ITemporarySupport_put_IsSymmetrical(This,newVal)	\
    ( (This)->lpVtbl -> put_IsSymmetrical(This,newVal) ) 

#define ITemporarySupport_get_Location(This,pVal)	\
    ( (This)->lpVtbl -> get_Location(This,pVal) ) 

#define ITemporarySupport_put_Location(This,newVal)	\
    ( (This)->lpVtbl -> put_Location(This,newVal) ) 

#define ITemporarySupport_get_StageRemoved(This,pVal)	\
    ( (This)->lpVtbl -> get_StageRemoved(This,pVal) ) 

#define ITemporarySupport_put_StageRemoved(This,newVal)	\
    ( (This)->lpVtbl -> put_StageRemoved(This,newVal) ) 

#define ITemporarySupport_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define ITemporarySupport_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define ITemporarySupport_put_ID(This,newVal)	\
    ( (This)->lpVtbl -> put_ID(This,newVal) ) 

#define ITemporarySupport_GetLoadModifier(This,type,minVal,maxVal)	\
    ( (This)->lpVtbl -> GetLoadModifier(This,type,minVal,maxVal) ) 

#define ITemporarySupport_SetLoadModifier(This,type,minVal,maxVal)	\
    ( (This)->lpVtbl -> SetLoadModifier(This,type,minVal,maxVal) ) 

#define ITemporarySupport_get_DistributionFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_DistributionFactor(This,pVal) ) 

#define ITemporarySupport_putref_DistributionFactor(This,newVal)	\
    ( (This)->lpVtbl -> putref_DistributionFactor(This,newVal) ) 

#define ITemporarySupport_get_TopRelease(This,pVal)	\
    ( (This)->lpVtbl -> get_TopRelease(This,pVal) ) 

#define ITemporarySupport_put_TopRelease(This,newVal)	\
    ( (This)->lpVtbl -> put_TopRelease(This,newVal) ) 

#define ITemporarySupport_get_OmitReaction(This,pbOmit)	\
    ( (This)->lpVtbl -> get_OmitReaction(This,pbOmit) ) 

#define ITemporarySupport_put_OmitReaction(This,bOmit)	\
    ( (This)->lpVtbl -> put_OmitReaction(This,bOmit) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemporarySupport_INTERFACE_DEFINED__ */


#ifndef __IEnumTemporarySupport_INTERFACE_DEFINED__
#define __IEnumTemporarySupport_INTERFACE_DEFINED__

/* interface IEnumTemporarySupport */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumTemporarySupport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A083785B-85CA-11d5-B040-00105A9AF985")
    IEnumTemporarySupport : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumTemporarySupport **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ITemporarySupport **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumTemporarySupportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumTemporarySupport * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumTemporarySupport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumTemporarySupport * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumTemporarySupport * This,
            /* [out] */ IEnumTemporarySupport **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumTemporarySupport * This,
            /* [in] */ ULONG celt,
            /* [out] */ ITemporarySupport **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumTemporarySupport * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumTemporarySupport * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumTemporarySupportVtbl;

    interface IEnumTemporarySupport
    {
        CONST_VTBL struct IEnumTemporarySupportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumTemporarySupport_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumTemporarySupport_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumTemporarySupport_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumTemporarySupport_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumTemporarySupport_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumTemporarySupport_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumTemporarySupport_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumTemporarySupport_INTERFACE_DEFINED__ */


#ifndef __ITemporarySupports_INTERFACE_DEFINED__
#define __ITemporarySupports_INTERFACE_DEFINED__

/* interface ITemporarySupports */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITemporarySupports;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BA6F5312-85BD-11D5-B040-00105A9AF985")
    ITemporarySupports : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ SupportIndexType idx,
            /* [retval][out] */ ITemporarySupport **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ SupportIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumTemporarySupport **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ITemporarySupport *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ SupportIndexType index,
            /* [in] */ ITemporarySupport *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ SupportIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            ITemporarySupports **clone) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ SupportIDType tsID,
            /* [retval][out] */ ITemporarySupport **ppTS) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemporarySupportsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemporarySupports * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemporarySupports * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemporarySupports * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITemporarySupports * This,
            /* [in] */ SupportIndexType idx,
            /* [retval][out] */ ITemporarySupport **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITemporarySupports * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITemporarySupports * This,
            /* [retval][out] */ SupportIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ITemporarySupports * This,
            /* [retval][out] */ IEnumTemporarySupport **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITemporarySupports * This,
            /* [in] */ ITemporarySupport *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ITemporarySupports * This,
            /* [in] */ SupportIndexType index,
            /* [in] */ ITemporarySupport *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITemporarySupports * This,
            /* [in] */ SupportIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ITemporarySupports * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITemporarySupports * This,
            ITemporarySupports **clone);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ITemporarySupports * This,
            /* [in] */ SupportIDType tsID,
            /* [retval][out] */ ITemporarySupport **ppTS);
        
        END_INTERFACE
    } ITemporarySupportsVtbl;

    interface ITemporarySupports
    {
        CONST_VTBL struct ITemporarySupportsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemporarySupports_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemporarySupports_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemporarySupports_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemporarySupports_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define ITemporarySupports_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ITemporarySupports_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ITemporarySupports_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ITemporarySupports_Add(This,pVal)	\
    ( (This)->lpVtbl -> Add(This,pVal) ) 

#define ITemporarySupports_Insert(This,index,pVal)	\
    ( (This)->lpVtbl -> Insert(This,index,pVal) ) 

#define ITemporarySupports_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define ITemporarySupports_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ITemporarySupports_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ITemporarySupports_Find(This,tsID,ppTS)	\
    ( (This)->lpVtbl -> Find(This,tsID,ppTS) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemporarySupports_INTERFACE_DEFINED__ */


#ifndef __ISpan_INTERFACE_DEFINED__
#define __ISpan_INTERFACE_DEFINED__

/* interface ISpan */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISpan;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BA6F5315-85BD-11D5-B040-00105A9AF985")
    ISpan : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TemporarySupports( 
            /* [retval][out] */ ITemporarySupports **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_TemporarySupports( 
            /* [in] */ ITemporarySupports *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISpan **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLoadModifier( 
            /* [in] */ LoadCombinationType type,
            /* [out] */ Float64 *minVal,
            /* [out] */ Float64 *maxVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetLoadModifier( 
            /* [in] */ LoadCombinationType type,
            /* [in] */ Float64 minVal,
            /* [in] */ Float64 maxVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            BSTR stage) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISpanVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpan * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpan * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpan * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ISpan * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            ISpan * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TemporarySupports )( 
            ISpan * This,
            /* [retval][out] */ ITemporarySupports **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_TemporarySupports )( 
            ISpan * This,
            /* [in] */ ITemporarySupports *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISpan * This,
            /* [retval][out] */ ISpan **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLoadModifier )( 
            ISpan * This,
            /* [in] */ LoadCombinationType type,
            /* [out] */ Float64 *minVal,
            /* [out] */ Float64 *maxVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLoadModifier )( 
            ISpan * This,
            /* [in] */ LoadCombinationType type,
            /* [in] */ Float64 minVal,
            /* [in] */ Float64 maxVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ISpan * This,
            BSTR stage);
        
        END_INTERFACE
    } ISpanVtbl;

    interface ISpan
    {
        CONST_VTBL struct ISpanVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpan_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISpan_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISpan_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISpan_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ISpan_put_Length(This,newVal)	\
    ( (This)->lpVtbl -> put_Length(This,newVal) ) 

#define ISpan_get_TemporarySupports(This,pVal)	\
    ( (This)->lpVtbl -> get_TemporarySupports(This,pVal) ) 

#define ISpan_putref_TemporarySupports(This,newVal)	\
    ( (This)->lpVtbl -> putref_TemporarySupports(This,newVal) ) 

#define ISpan_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISpan_GetLoadModifier(This,type,minVal,maxVal)	\
    ( (This)->lpVtbl -> GetLoadModifier(This,type,minVal,maxVal) ) 

#define ISpan_SetLoadModifier(This,type,minVal,maxVal)	\
    ( (This)->lpVtbl -> SetLoadModifier(This,type,minVal,maxVal) ) 

#define ISpan_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISpan_INTERFACE_DEFINED__ */


#ifndef __IEnumSpan_INTERFACE_DEFINED__
#define __IEnumSpan_INTERFACE_DEFINED__

/* interface IEnumSpan */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSpan;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E90F6D1-85DD-11d5-B040-00105A9AF985")
    IEnumSpan : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSpan **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISpan **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSpanVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSpan * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSpan * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSpan * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSpan * This,
            /* [out] */ IEnumSpan **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSpan * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISpan **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSpan * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSpan * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSpanVtbl;

    interface IEnumSpan
    {
        CONST_VTBL struct IEnumSpanVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSpan_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSpan_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSpan_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSpan_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSpan_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSpan_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSpan_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSpan_INTERFACE_DEFINED__ */


#ifndef __ISpans_INTERFACE_DEFINED__
#define __ISpans_INTERFACE_DEFINED__

/* interface ISpans */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISpans;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BA6F5319-85BD-11D5-B040-00105A9AF985")
    ISpans : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ SpanIndexType position,
            /* [retval][out] */ ISpan **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ SpanIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ISpan *__MIDL__ISpans0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ SpanIndexType relPosition,
            /* [in] */ ISpan *member) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ SpanIndexType fromPosition,
            /* [in] */ SpanIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [in] */ SpanIndexType fromPosition,
            /* [in] */ SpanIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ SpanIndexType position) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSpan **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISpans **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISpansVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpans * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpans * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpans * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISpans * This,
            /* [in] */ SpanIndexType position,
            /* [retval][out] */ ISpan **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISpans * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ISpans * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISpans * This,
            /* [retval][out] */ SpanIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISpans * This,
            /* [in] */ ISpan *__MIDL__ISpans0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ISpans * This,
            /* [in] */ SpanIndexType relPosition,
            /* [in] */ ISpan *member);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            ISpans * This,
            /* [in] */ SpanIndexType fromPosition,
            /* [in] */ SpanIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CopyTo )( 
            ISpans * This,
            /* [in] */ SpanIndexType fromPosition,
            /* [in] */ SpanIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ISpans * This,
            /* [in] */ SpanIndexType position);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            ISpans * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ISpans * This,
            /* [retval][out] */ IEnumSpan **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISpans * This,
            /* [retval][out] */ ISpans **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISpans * This);
        
        END_INTERFACE
    } ISpansVtbl;

    interface ISpans
    {
        CONST_VTBL struct ISpansVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpans_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISpans_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISpans_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISpans_get_Item(This,position,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,position,pVal) ) 

#define ISpans_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ISpans_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ISpans_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISpans_Add(This,__MIDL__ISpans0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__ISpans0000) ) 

#define ISpans_Insert(This,relPosition,member)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,member) ) 

#define ISpans_MoveTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> MoveTo(This,fromPosition,toPosition) ) 

#define ISpans_CopyTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> CopyTo(This,fromPosition,toPosition) ) 

#define ISpans_Remove(This,position)	\
    ( (This)->lpVtbl -> Remove(This,position) ) 

#define ISpans_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define ISpans_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ISpans_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISpans_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISpans_INTERFACE_DEFINED__ */


#ifndef __IPOIStressPointsItem_INTERFACE_DEFINED__
#define __IPOIStressPointsItem_INTERFACE_DEFINED__

/* interface IPOIStressPointsItem */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPOIStressPointsItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8944417E-61AE-4ED0-986A-3A63A2654408")
    IPOIStressPointsItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LeftStressPoints( 
            /* [retval][out] */ IStressPoints **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RightStressPoints( 
            /* [retval][out] */ IStressPoints **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPOIStressPointsItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPOIStressPointsItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPOIStressPointsItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPOIStressPointsItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            IPOIStressPointsItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftStressPoints )( 
            IPOIStressPointsItem * This,
            /* [retval][out] */ IStressPoints **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightStressPoints )( 
            IPOIStressPointsItem * This,
            /* [retval][out] */ IStressPoints **pVal);
        
        END_INTERFACE
    } IPOIStressPointsItemVtbl;

    interface IPOIStressPointsItem
    {
        CONST_VTBL struct IPOIStressPointsItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPOIStressPointsItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPOIStressPointsItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPOIStressPointsItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPOIStressPointsItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define IPOIStressPointsItem_get_LeftStressPoints(This,pVal)	\
    ( (This)->lpVtbl -> get_LeftStressPoints(This,pVal) ) 

#define IPOIStressPointsItem_get_RightStressPoints(This,pVal)	\
    ( (This)->lpVtbl -> get_RightStressPoints(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPOIStressPointsItem_INTERFACE_DEFINED__ */


#ifndef __IEnumPOIStressPoints_INTERFACE_DEFINED__
#define __IEnumPOIStressPoints_INTERFACE_DEFINED__

/* interface IEnumPOIStressPoints */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumPOIStressPoints;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7084A56F-00D9-42ea-9C9F-2AC83E94F4C4")
    IEnumPOIStressPoints : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPOIStressPoints **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IPOIStressPointsItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumPOIStressPointsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPOIStressPoints * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPOIStressPoints * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPOIStressPoints * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPOIStressPoints * This,
            /* [out] */ IEnumPOIStressPoints **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPOIStressPoints * This,
            /* [in] */ ULONG celt,
            /* [out] */ IPOIStressPointsItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPOIStressPoints * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPOIStressPoints * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumPOIStressPointsVtbl;

    interface IEnumPOIStressPoints
    {
        CONST_VTBL struct IEnumPOIStressPointsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPOIStressPoints_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumPOIStressPoints_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumPOIStressPoints_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumPOIStressPoints_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumPOIStressPoints_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumPOIStressPoints_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumPOIStressPoints_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumPOIStressPoints_INTERFACE_DEFINED__ */


#ifndef __IPOIStressPoints_INTERFACE_DEFINED__
#define __IPOIStressPoints_INTERFACE_DEFINED__

/* interface IPOIStressPoints */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPOIStressPoints;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("517D5B96-15C1-4533-8CF5-C25C30C2A048")
    IPOIStressPoints : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT idxOrStage,
            /* [retval][out] */ IPOIStressPointsItem **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ BSTR Stage,
            /* [in] */ IStressPoints *leftSps,
            /* [in] */ IStressPoints *rightSps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR Stage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPOIStressPoints **Clone) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumPOIStressPoints **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPOIStressPointsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPOIStressPoints * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPOIStressPoints * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPOIStressPoints * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPOIStressPoints * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPOIStressPoints * This,
            /* [in] */ VARIANT idxOrStage,
            /* [retval][out] */ IPOIStressPointsItem **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IPOIStressPoints * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IPOIStressPoints * This,
            /* [in] */ BSTR Stage,
            /* [in] */ IStressPoints *leftSps,
            /* [in] */ IStressPoints *rightSps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IPOIStressPoints * This,
            /* [in] */ BSTR Stage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPOIStressPoints * This,
            /* [retval][out] */ IPOIStressPoints **Clone);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IPOIStressPoints * This,
            /* [retval][out] */ IEnumPOIStressPoints **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IPOIStressPoints * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } IPOIStressPointsVtbl;

    interface IPOIStressPoints
    {
        CONST_VTBL struct IPOIStressPointsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPOIStressPoints_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPOIStressPoints_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPOIStressPoints_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPOIStressPoints_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPOIStressPoints_get_Item(This,idxOrStage,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idxOrStage,pVal) ) 

#define IPOIStressPoints_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IPOIStressPoints_Insert(This,Stage,leftSps,rightSps)	\
    ( (This)->lpVtbl -> Insert(This,Stage,leftSps,rightSps) ) 

#define IPOIStressPoints_Remove(This,Stage)	\
    ( (This)->lpVtbl -> Remove(This,Stage) ) 

#define IPOIStressPoints_Clone(This,Clone)	\
    ( (This)->lpVtbl -> Clone(This,Clone) ) 

#define IPOIStressPoints_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IPOIStressPoints_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPOIStressPoints_INTERFACE_DEFINED__ */


#ifndef __IPOI_INTERFACE_DEFINED__
#define __IPOI_INTERFACE_DEFINED__

/* interface IPOI */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPOI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E6ECB21B-881C-11D5-B043-00105A9AF985")
    IPOI : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ PoiIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ID( 
            /* [in] */ PoiIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberType( 
            /* [retval][out] */ MemberType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberType( 
            /* [in] */ MemberType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPOI **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_POIStressPoints( 
            /* [retval][out] */ IPOIStressPoints **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_POIStressPoints( 
            /* [in] */ IPOIStressPoints *newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPOIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPOI * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPOI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPOI * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IPOI * This,
            /* [retval][out] */ PoiIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ID )( 
            IPOI * This,
            /* [in] */ PoiIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberType )( 
            IPOI * This,
            /* [retval][out] */ MemberType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberType )( 
            IPOI * This,
            /* [in] */ MemberType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            IPOI * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            IPOI * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IPOI * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Location )( 
            IPOI * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPOI * This,
            /* [retval][out] */ IPOI **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_POIStressPoints )( 
            IPOI * This,
            /* [retval][out] */ IPOIStressPoints **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_POIStressPoints )( 
            IPOI * This,
            /* [in] */ IPOIStressPoints *newVal);
        
        END_INTERFACE
    } IPOIVtbl;

    interface IPOI
    {
        CONST_VTBL struct IPOIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPOI_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPOI_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPOI_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPOI_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IPOI_put_ID(This,newVal)	\
    ( (This)->lpVtbl -> put_ID(This,newVal) ) 

#define IPOI_get_MemberType(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberType(This,pVal) ) 

#define IPOI_put_MemberType(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberType(This,newVal) ) 

#define IPOI_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define IPOI_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define IPOI_get_Location(This,pVal)	\
    ( (This)->lpVtbl -> get_Location(This,pVal) ) 

#define IPOI_put_Location(This,newVal)	\
    ( (This)->lpVtbl -> put_Location(This,newVal) ) 

#define IPOI_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IPOI_get_POIStressPoints(This,pVal)	\
    ( (This)->lpVtbl -> get_POIStressPoints(This,pVal) ) 

#define IPOI_putref_POIStressPoints(This,newVal)	\
    ( (This)->lpVtbl -> putref_POIStressPoints(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPOI_INTERFACE_DEFINED__ */


#ifndef __IEnumPOI_INTERFACE_DEFINED__
#define __IEnumPOI_INTERFACE_DEFINED__

/* interface IEnumPOI */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumPOI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("713DBD94-8A7A-11d5-B045-00105A9AF985")
    IEnumPOI : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPOI **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IPOI **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumPOIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPOI * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPOI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPOI * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPOI * This,
            /* [out] */ IEnumPOI **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPOI * This,
            /* [in] */ ULONG celt,
            /* [out] */ IPOI **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPOI * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPOI * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumPOIVtbl;

    interface IEnumPOI
    {
        CONST_VTBL struct IEnumPOIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPOI_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumPOI_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumPOI_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumPOI_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumPOI_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumPOI_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumPOI_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumPOI_INTERFACE_DEFINED__ */


#ifndef __IPOIs_INTERFACE_DEFINED__
#define __IPOIs_INTERFACE_DEFINED__

/* interface IPOIs */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPOIs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E6ECB21E-881C-11D5-B043-00105A9AF985")
    IPOIs : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPOI **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumPOI **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ PoiIDType id,
            /* [retval][out] */ IPOI **__MIDL__IPOIs0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IPOI *__MIDL__IPOIs0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ PoiIDType id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ PoiIDType *id) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPOIs **__MIDL__IPOIs0002) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPOIsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPOIs * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPOIs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPOIs * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPOIs * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPOI **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IPOIs * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPOIs * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IPOIs * This,
            /* [retval][out] */ IEnumPOI **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IPOIs * This,
            /* [in] */ PoiIDType id,
            /* [retval][out] */ IPOI **__MIDL__IPOIs0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPOIs * This,
            /* [in] */ IPOI *__MIDL__IPOIs0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            IPOIs * This,
            /* [in] */ PoiIDType id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            IPOIs * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ PoiIDType *id);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPOIs * This,
            /* [retval][out] */ IPOIs **__MIDL__IPOIs0002);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IPOIs * This);
        
        END_INTERFACE
    } IPOIsVtbl;

    interface IPOIs
    {
        CONST_VTBL struct IPOIsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPOIs_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPOIs_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPOIs_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPOIs_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IPOIs_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IPOIs_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPOIs_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IPOIs_Find(This,id,__MIDL__IPOIs0000)	\
    ( (This)->lpVtbl -> Find(This,id,__MIDL__IPOIs0000) ) 

#define IPOIs_Add(This,__MIDL__IPOIs0001)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__IPOIs0001) ) 

#define IPOIs_RemoveByID(This,id)	\
    ( (This)->lpVtbl -> RemoveByID(This,id) ) 

#define IPOIs_RemoveByIndex(This,index,id)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index,id) ) 

#define IPOIs_Clone(This,__MIDL__IPOIs0002)	\
    ( (This)->lpVtbl -> Clone(This,__MIDL__IPOIs0002) ) 

#define IPOIs_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPOIs_INTERFACE_DEFINED__ */


#ifndef __IStage_INTERFACE_DEFINED__
#define __IStage_INTERFACE_DEFINED__

/* interface IStage */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2DC09B1D-8D9A-11D5-B048-00105A9AF985")
    IStage : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IStage **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStage * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IStage * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IStage * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IStage * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IStage * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IStage * This,
            /* [retval][out] */ IStage **clone);
        
        END_INTERFACE
    } IStageVtbl;

    interface IStage
    {
        CONST_VTBL struct IStageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStage_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IStage_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IStage_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define IStage_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define IStage_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStage_INTERFACE_DEFINED__ */


#ifndef __IEnumStage_INTERFACE_DEFINED__
#define __IEnumStage_INTERFACE_DEFINED__

/* interface IEnumStage */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumStage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0D3B7922-8DD9-11d5-B048-00105A9AF985")
    IEnumStage : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumStage **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IStage **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumStageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumStage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumStage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumStage * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumStage * This,
            /* [out] */ IEnumStage **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumStage * This,
            /* [in] */ ULONG celt,
            /* [out] */ IStage **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumStage * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumStage * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumStageVtbl;

    interface IEnumStage
    {
        CONST_VTBL struct IEnumStageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumStage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumStage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumStage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumStage_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumStage_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumStage_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumStage_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumStage_INTERFACE_DEFINED__ */


#ifndef __IStages_INTERFACE_DEFINED__
#define __IStages_INTERFACE_DEFINED__

/* interface IStages */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStages;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2DC09B20-8D9A-11D5-B048-00105A9AF985")
    IStages : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ StageIndexType position,
            /* [retval][out] */ IStage **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ StageIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IStage *stage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ StageIndexType relPosition,
            /* [in] */ IStage *member) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ StageIndexType fromPosition,
            /* [in] */ StageIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ StageIndexType position) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByName( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumStage **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IStages **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FindIndex( 
            /* [in] */ BSTR name,
            /* [retval][out] */ StageIndexType *index) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStagesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStages * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStages * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStages * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IStages * This,
            /* [in] */ StageIndexType position,
            /* [retval][out] */ IStage **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IStages * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IStages * This,
            /* [retval][out] */ StageIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IStages * This,
            /* [in] */ IStage *stage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IStages * This,
            /* [in] */ StageIndexType relPosition,
            /* [in] */ IStage *member);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            IStages * This,
            /* [in] */ StageIndexType fromPosition,
            /* [in] */ StageIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            IStages * This,
            /* [in] */ StageIndexType position);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByName )( 
            IStages * This,
            /* [in] */ BSTR name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            IStages * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IStages * This,
            /* [retval][out] */ IEnumStage **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IStages * This,
            /* [retval][out] */ IStages **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IStages * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindIndex )( 
            IStages * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ StageIndexType *index);
        
        END_INTERFACE
    } IStagesVtbl;

    interface IStages
    {
        CONST_VTBL struct IStagesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStages_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStages_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStages_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStages_get_Item(This,position,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,position,pVal) ) 

#define IStages_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IStages_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IStages_Add(This,stage)	\
    ( (This)->lpVtbl -> Add(This,stage) ) 

#define IStages_Insert(This,relPosition,member)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,member) ) 

#define IStages_MoveTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> MoveTo(This,fromPosition,toPosition) ) 

#define IStages_RemoveByIndex(This,position)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,position) ) 

#define IStages_RemoveByName(This,name)	\
    ( (This)->lpVtbl -> RemoveByName(This,name) ) 

#define IStages_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define IStages_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IStages_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IStages_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IStages_FindIndex(This,name,index)	\
    ( (This)->lpVtbl -> FindIndex(This,name,index) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStages_INTERFACE_DEFINED__ */


#ifndef __IPointLoad_INTERFACE_DEFINED__
#define __IPointLoad_INTERFACE_DEFINED__

/* interface IPointLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPointLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DE453FF3-90BF-11D5-B04B-00105A9AF985")
    IPointLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberType( 
            /* [retval][out] */ MemberType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberType( 
            /* [in] */ MemberType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Fx( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Fx( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Fy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Fy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Mz( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Mz( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetForce( 
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetForce( 
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPointLoad **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPointLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberType )( 
            IPointLoad * This,
            /* [retval][out] */ MemberType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberType )( 
            IPointLoad * This,
            /* [in] */ MemberType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            IPointLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            IPointLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Location )( 
            IPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fx )( 
            IPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fx )( 
            IPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fy )( 
            IPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fy )( 
            IPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mz )( 
            IPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Mz )( 
            IPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetForce )( 
            IPointLoad * This,
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetForce )( 
            IPointLoad * This,
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPointLoad * This,
            /* [retval][out] */ IPointLoad **clone);
        
        END_INTERFACE
    } IPointLoadVtbl;

    interface IPointLoad
    {
        CONST_VTBL struct IPointLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPointLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPointLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPointLoad_get_MemberType(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberType(This,pVal) ) 

#define IPointLoad_put_MemberType(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberType(This,newVal) ) 

#define IPointLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define IPointLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define IPointLoad_get_Location(This,pVal)	\
    ( (This)->lpVtbl -> get_Location(This,pVal) ) 

#define IPointLoad_put_Location(This,newVal)	\
    ( (This)->lpVtbl -> put_Location(This,newVal) ) 

#define IPointLoad_get_Fx(This,pVal)	\
    ( (This)->lpVtbl -> get_Fx(This,pVal) ) 

#define IPointLoad_put_Fx(This,newVal)	\
    ( (This)->lpVtbl -> put_Fx(This,newVal) ) 

#define IPointLoad_get_Fy(This,pVal)	\
    ( (This)->lpVtbl -> get_Fy(This,pVal) ) 

#define IPointLoad_put_Fy(This,newVal)	\
    ( (This)->lpVtbl -> put_Fy(This,newVal) ) 

#define IPointLoad_get_Mz(This,pVal)	\
    ( (This)->lpVtbl -> get_Mz(This,pVal) ) 

#define IPointLoad_put_Mz(This,newVal)	\
    ( (This)->lpVtbl -> put_Mz(This,newVal) ) 

#define IPointLoad_SetForce(This,Fx,Fy,Mz)	\
    ( (This)->lpVtbl -> SetForce(This,Fx,Fy,Mz) ) 

#define IPointLoad_GetForce(This,Fx,Fy,Mz)	\
    ( (This)->lpVtbl -> GetForce(This,Fx,Fy,Mz) ) 

#define IPointLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPointLoad_INTERFACE_DEFINED__ */


#ifndef __IPointLoadItem_INTERFACE_DEFINED__
#define __IPointLoadItem_INTERFACE_DEFINED__

/* interface IPointLoadItem */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPointLoadItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DE453FF6-90BF-11D5-B04B-00105A9AF985")
    IPointLoadItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroup( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [retval][out] */ IPointLoad **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPointLoadItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointLoadItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointLoadItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointLoadItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IPointLoadItem * This,
            /* [retval][out] */ LoadIDType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            IPointLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroup )( 
            IPointLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            IPointLoadItem * This,
            /* [retval][out] */ IPointLoad **pVal);
        
        END_INTERFACE
    } IPointLoadItemVtbl;

    interface IPointLoadItem
    {
        CONST_VTBL struct IPointLoadItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointLoadItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPointLoadItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPointLoadItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPointLoadItem_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IPointLoadItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define IPointLoadItem_get_LoadGroup(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroup(This,pVal) ) 

#define IPointLoadItem_get_Load(This,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPointLoadItem_INTERFACE_DEFINED__ */


#ifndef __IEnumPointLoad_INTERFACE_DEFINED__
#define __IEnumPointLoad_INTERFACE_DEFINED__

/* interface IEnumPointLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumPointLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7B3D50B5-90C2-11d5-B04B-00105A9AF985")
    IEnumPointLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPointLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IPointLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumPointLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPointLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPointLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPointLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPointLoad * This,
            /* [out] */ IEnumPointLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPointLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ IPointLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPointLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPointLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumPointLoadVtbl;

    interface IEnumPointLoad
    {
        CONST_VTBL struct IEnumPointLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPointLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumPointLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumPointLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumPointLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumPointLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumPointLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumPointLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumPointLoad_INTERFACE_DEFINED__ */


#ifndef __IPointLoads_INTERFACE_DEFINED__
#define __IPointLoads_INTERFACE_DEFINED__

/* interface IPointLoads */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPointLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DE453FF9-90BF-11D5-B04B-00105A9AF985")
    IPointLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPointLoadItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IPointLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Load( 
            /* [in] */ LoadIDType ID,
            /* [in] */ IPointLoad *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumPointLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IPointLoad *Load,
            /* [retval][out] */ IPointLoadItem **Item) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IPointLoadItem **__MIDL__IPointLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ LoadIDType ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FilterByStageGroup( 
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ IPointLoads **filteredcoll) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IPointLoads **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPointLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPointLoads * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPointLoads * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPointLoadItem **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            IPointLoads * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IPointLoad **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Load )( 
            IPointLoads * This,
            /* [in] */ LoadIDType ID,
            /* [in] */ IPointLoad *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IPointLoads * This,
            /* [retval][out] */ IEnumPointLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPointLoads * This,
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IPointLoad *Load,
            /* [retval][out] */ IPointLoadItem **Item);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IPointLoads * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IPointLoadItem **__MIDL__IPointLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            IPointLoads * This,
            /* [in] */ LoadIDType ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            IPointLoads * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilterByStageGroup )( 
            IPointLoads * This,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ IPointLoads **filteredcoll);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPointLoads * This,
            /* [retval][out] */ IPointLoads **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IPointLoads * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            IPointLoads * This,
            /* [in] */ BSTR stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IPointLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } IPointLoadsVtbl;

    interface IPointLoads
    {
        CONST_VTBL struct IPointLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPointLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPointLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPointLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPointLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IPointLoads_get_Load(This,ID,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,ID,pVal) ) 

#define IPointLoads_putref_Load(This,ID,newVal)	\
    ( (This)->lpVtbl -> putref_Load(This,ID,newVal) ) 

#define IPointLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IPointLoads_Add(This,Stage,LoadGroup,Load,Item)	\
    ( (This)->lpVtbl -> Add(This,Stage,LoadGroup,Load,Item) ) 

#define IPointLoads_Find(This,ID,__MIDL__IPointLoads0000)	\
    ( (This)->lpVtbl -> Find(This,ID,__MIDL__IPointLoads0000) ) 

#define IPointLoads_RemoveByID(This,ID)	\
    ( (This)->lpVtbl -> RemoveByID(This,ID) ) 

#define IPointLoads_RemoveByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index) ) 

#define IPointLoads_FilterByStageGroup(This,stage,loadgroup,filteredcoll)	\
    ( (This)->lpVtbl -> FilterByStageGroup(This,stage,loadgroup,filteredcoll) ) 

#define IPointLoads_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IPointLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IPointLoads_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define IPointLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPointLoads_INTERFACE_DEFINED__ */


#ifndef __IDistributedLoad_INTERFACE_DEFINED__
#define __IDistributedLoad_INTERFACE_DEFINED__

/* interface IDistributedLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDistributedLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("796E1EF3-9252-11D5-B04D-00105A9AF985")
    IDistributedLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IDistributedLoad **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ LoadOrientation *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ LoadOrientation newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ LoadDirection *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Direction( 
            /* [in] */ LoadDirection newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WStart( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WStart( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WEnd( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WEnd( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberType( 
            /* [retval][out] */ MemberType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberType( 
            /* [in] */ MemberType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartLocation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartLocation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndLocation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndLocation( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributedLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributedLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributedLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributedLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDistributedLoad * This,
            /* [retval][out] */ IDistributedLoad **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IDistributedLoad * This,
            /* [retval][out] */ LoadOrientation *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IDistributedLoad * This,
            /* [in] */ LoadOrientation newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Direction )( 
            IDistributedLoad * This,
            /* [retval][out] */ LoadDirection *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Direction )( 
            IDistributedLoad * This,
            /* [in] */ LoadDirection newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WStart )( 
            IDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WStart )( 
            IDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WEnd )( 
            IDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WEnd )( 
            IDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberType )( 
            IDistributedLoad * This,
            /* [retval][out] */ MemberType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberType )( 
            IDistributedLoad * This,
            /* [in] */ MemberType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            IDistributedLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            IDistributedLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartLocation )( 
            IDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartLocation )( 
            IDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndLocation )( 
            IDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndLocation )( 
            IDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IDistributedLoadVtbl;

    interface IDistributedLoad
    {
        CONST_VTBL struct IDistributedLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributedLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributedLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributedLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributedLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IDistributedLoad_get_Orientation(This,pVal)	\
    ( (This)->lpVtbl -> get_Orientation(This,pVal) ) 

#define IDistributedLoad_put_Orientation(This,newVal)	\
    ( (This)->lpVtbl -> put_Orientation(This,newVal) ) 

#define IDistributedLoad_get_Direction(This,pVal)	\
    ( (This)->lpVtbl -> get_Direction(This,pVal) ) 

#define IDistributedLoad_put_Direction(This,newVal)	\
    ( (This)->lpVtbl -> put_Direction(This,newVal) ) 

#define IDistributedLoad_get_WStart(This,pVal)	\
    ( (This)->lpVtbl -> get_WStart(This,pVal) ) 

#define IDistributedLoad_put_WStart(This,newVal)	\
    ( (This)->lpVtbl -> put_WStart(This,newVal) ) 

#define IDistributedLoad_get_WEnd(This,pVal)	\
    ( (This)->lpVtbl -> get_WEnd(This,pVal) ) 

#define IDistributedLoad_put_WEnd(This,newVal)	\
    ( (This)->lpVtbl -> put_WEnd(This,newVal) ) 

#define IDistributedLoad_get_MemberType(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberType(This,pVal) ) 

#define IDistributedLoad_put_MemberType(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberType(This,newVal) ) 

#define IDistributedLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define IDistributedLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define IDistributedLoad_get_StartLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_StartLocation(This,pVal) ) 

#define IDistributedLoad_put_StartLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_StartLocation(This,newVal) ) 

#define IDistributedLoad_get_EndLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_EndLocation(This,pVal) ) 

#define IDistributedLoad_put_EndLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_EndLocation(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributedLoad_INTERFACE_DEFINED__ */


#ifndef __IDistributedLoadItem_INTERFACE_DEFINED__
#define __IDistributedLoadItem_INTERFACE_DEFINED__

/* interface IDistributedLoadItem */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDistributedLoadItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CCB1AF47-9267-11d5-B04D-00105A9AF985")
    IDistributedLoadItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroup( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [retval][out] */ IDistributedLoad **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributedLoadItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributedLoadItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributedLoadItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributedLoadItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IDistributedLoadItem * This,
            /* [retval][out] */ LoadIDType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            IDistributedLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroup )( 
            IDistributedLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            IDistributedLoadItem * This,
            /* [retval][out] */ IDistributedLoad **pVal);
        
        END_INTERFACE
    } IDistributedLoadItemVtbl;

    interface IDistributedLoadItem
    {
        CONST_VTBL struct IDistributedLoadItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributedLoadItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributedLoadItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributedLoadItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributedLoadItem_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IDistributedLoadItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define IDistributedLoadItem_get_LoadGroup(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroup(This,pVal) ) 

#define IDistributedLoadItem_get_Load(This,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributedLoadItem_INTERFACE_DEFINED__ */


#ifndef __IEnumDistributedLoad_INTERFACE_DEFINED__
#define __IEnumDistributedLoad_INTERFACE_DEFINED__

/* interface IEnumDistributedLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumDistributedLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CCB1AF48-9267-11d5-B04D-00105A9AF985")
    IEnumDistributedLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumDistributedLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IDistributedLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumDistributedLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumDistributedLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumDistributedLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumDistributedLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumDistributedLoad * This,
            /* [out] */ IEnumDistributedLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumDistributedLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ IDistributedLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumDistributedLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumDistributedLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumDistributedLoadVtbl;

    interface IEnumDistributedLoad
    {
        CONST_VTBL struct IEnumDistributedLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumDistributedLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumDistributedLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumDistributedLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumDistributedLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumDistributedLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumDistributedLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumDistributedLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumDistributedLoad_INTERFACE_DEFINED__ */


#ifndef __IDistributedLoads_INTERFACE_DEFINED__
#define __IDistributedLoads_INTERFACE_DEFINED__

/* interface IDistributedLoads */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDistributedLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("796E1EF6-9252-11D5-B04D-00105A9AF985")
    IDistributedLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IDistributedLoadItem **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IDistributedLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Load( 
            /* [in] */ LoadIDType ID,
            /* [in] */ IDistributedLoad *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumDistributedLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IDistributedLoad *Load,
            /* [retval][out] */ IDistributedLoadItem **Item) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IDistributedLoadItem **__MIDL__IDistributedLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ LoadIDType ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FilterByStageGroup( 
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ IDistributedLoads **filteredcoll) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IDistributedLoads **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributedLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributedLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributedLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributedLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IDistributedLoads * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IDistributedLoadItem **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IDistributedLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IDistributedLoads * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            IDistributedLoads * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IDistributedLoad **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Load )( 
            IDistributedLoads * This,
            /* [in] */ LoadIDType ID,
            /* [in] */ IDistributedLoad *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IDistributedLoads * This,
            /* [retval][out] */ IEnumDistributedLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IDistributedLoads * This,
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IDistributedLoad *Load,
            /* [retval][out] */ IDistributedLoadItem **Item);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IDistributedLoads * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IDistributedLoadItem **__MIDL__IDistributedLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            IDistributedLoads * This,
            /* [in] */ LoadIDType ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            IDistributedLoads * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilterByStageGroup )( 
            IDistributedLoads * This,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ IDistributedLoads **filteredcoll);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDistributedLoads * This,
            /* [retval][out] */ IDistributedLoads **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IDistributedLoads * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            IDistributedLoads * This,
            /* [in] */ BSTR stage);
        
        END_INTERFACE
    } IDistributedLoadsVtbl;

    interface IDistributedLoads
    {
        CONST_VTBL struct IDistributedLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributedLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributedLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributedLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributedLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IDistributedLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IDistributedLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IDistributedLoads_get_Load(This,ID,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,ID,pVal) ) 

#define IDistributedLoads_putref_Load(This,ID,newVal)	\
    ( (This)->lpVtbl -> putref_Load(This,ID,newVal) ) 

#define IDistributedLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IDistributedLoads_Add(This,Stage,LoadGroup,Load,Item)	\
    ( (This)->lpVtbl -> Add(This,Stage,LoadGroup,Load,Item) ) 

#define IDistributedLoads_Find(This,ID,__MIDL__IDistributedLoads0000)	\
    ( (This)->lpVtbl -> Find(This,ID,__MIDL__IDistributedLoads0000) ) 

#define IDistributedLoads_RemoveByID(This,ID)	\
    ( (This)->lpVtbl -> RemoveByID(This,ID) ) 

#define IDistributedLoads_RemoveByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index) ) 

#define IDistributedLoads_FilterByStageGroup(This,stage,loadgroup,filteredcoll)	\
    ( (This)->lpVtbl -> FilterByStageGroup(This,stage,loadgroup,filteredcoll) ) 

#define IDistributedLoads_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IDistributedLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IDistributedLoads_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributedLoads_INTERFACE_DEFINED__ */


#ifndef __ITemperatureLoad_INTERFACE_DEFINED__
#define __ITemperatureLoad_INTERFACE_DEFINED__

/* interface ITemperatureLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITemperatureLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF2C872D-9357-11D5-B04E-00105A9AF985")
    ITemperatureLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberType( 
            /* [retval][out] */ MemberType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberType( 
            /* [in] */ MemberType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TTop( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TTop( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TBottom( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TBottom( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ITemperatureLoad **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemperatureLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemperatureLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemperatureLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemperatureLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberType )( 
            ITemperatureLoad * This,
            /* [retval][out] */ MemberType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberType )( 
            ITemperatureLoad * This,
            /* [in] */ MemberType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            ITemperatureLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            ITemperatureLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TTop )( 
            ITemperatureLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TTop )( 
            ITemperatureLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TBottom )( 
            ITemperatureLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TBottom )( 
            ITemperatureLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITemperatureLoad * This,
            /* [retval][out] */ ITemperatureLoad **clone);
        
        END_INTERFACE
    } ITemperatureLoadVtbl;

    interface ITemperatureLoad
    {
        CONST_VTBL struct ITemperatureLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemperatureLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemperatureLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemperatureLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemperatureLoad_get_MemberType(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberType(This,pVal) ) 

#define ITemperatureLoad_put_MemberType(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberType(This,newVal) ) 

#define ITemperatureLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define ITemperatureLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define ITemperatureLoad_get_TTop(This,pVal)	\
    ( (This)->lpVtbl -> get_TTop(This,pVal) ) 

#define ITemperatureLoad_put_TTop(This,newVal)	\
    ( (This)->lpVtbl -> put_TTop(This,newVal) ) 

#define ITemperatureLoad_get_TBottom(This,pVal)	\
    ( (This)->lpVtbl -> get_TBottom(This,pVal) ) 

#define ITemperatureLoad_put_TBottom(This,newVal)	\
    ( (This)->lpVtbl -> put_TBottom(This,newVal) ) 

#define ITemperatureLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemperatureLoad_INTERFACE_DEFINED__ */


#ifndef __ITemperatureLoadItem_INTERFACE_DEFINED__
#define __ITemperatureLoadItem_INTERFACE_DEFINED__

/* interface ITemperatureLoadItem */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITemperatureLoadItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D13393A6-9326-11d5-B04E-00105A9AF985")
    ITemperatureLoadItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroup( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [retval][out] */ ITemperatureLoad **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemperatureLoadItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemperatureLoadItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemperatureLoadItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemperatureLoadItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            ITemperatureLoadItem * This,
            /* [retval][out] */ LoadIDType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            ITemperatureLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroup )( 
            ITemperatureLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ITemperatureLoadItem * This,
            /* [retval][out] */ ITemperatureLoad **pVal);
        
        END_INTERFACE
    } ITemperatureLoadItemVtbl;

    interface ITemperatureLoadItem
    {
        CONST_VTBL struct ITemperatureLoadItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemperatureLoadItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemperatureLoadItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemperatureLoadItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemperatureLoadItem_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define ITemperatureLoadItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define ITemperatureLoadItem_get_LoadGroup(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroup(This,pVal) ) 

#define ITemperatureLoadItem_get_Load(This,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemperatureLoadItem_INTERFACE_DEFINED__ */


#ifndef __IEnumTemperatureLoad_INTERFACE_DEFINED__
#define __IEnumTemperatureLoad_INTERFACE_DEFINED__

/* interface IEnumTemperatureLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumTemperatureLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D13393A7-9326-11d5-B04E-00105A9AF985")
    IEnumTemperatureLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumTemperatureLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ITemperatureLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumTemperatureLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumTemperatureLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumTemperatureLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumTemperatureLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumTemperatureLoad * This,
            /* [out] */ IEnumTemperatureLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumTemperatureLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ ITemperatureLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumTemperatureLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumTemperatureLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumTemperatureLoadVtbl;

    interface IEnumTemperatureLoad
    {
        CONST_VTBL struct IEnumTemperatureLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumTemperatureLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumTemperatureLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumTemperatureLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumTemperatureLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumTemperatureLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumTemperatureLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumTemperatureLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumTemperatureLoad_INTERFACE_DEFINED__ */


#ifndef __ITemperatureLoads_INTERFACE_DEFINED__
#define __ITemperatureLoads_INTERFACE_DEFINED__

/* interface ITemperatureLoads */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITemperatureLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF2C8730-9357-11D5-B04E-00105A9AF985")
    ITemperatureLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ITemperatureLoadItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ ITemperatureLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Load( 
            /* [in] */ LoadIDType ID,
            /* [in] */ ITemperatureLoad *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumTemperatureLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ITemperatureLoad *Load,
            /* [retval][out] */ ITemperatureLoadItem **Item) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ ITemperatureLoadItem **__MIDL__ITemperatureLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ LoadIDType ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FilterByStageGroup( 
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ITemperatureLoads **filteredcoll) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ITemperatureLoads **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemperatureLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemperatureLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemperatureLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemperatureLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITemperatureLoads * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITemperatureLoads * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ITemperatureLoadItem **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ITemperatureLoads * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ ITemperatureLoad **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Load )( 
            ITemperatureLoads * This,
            /* [in] */ LoadIDType ID,
            /* [in] */ ITemperatureLoad *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ITemperatureLoads * This,
            /* [retval][out] */ IEnumTemperatureLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITemperatureLoads * This,
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ITemperatureLoad *Load,
            /* [retval][out] */ ITemperatureLoadItem **Item);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ITemperatureLoads * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ ITemperatureLoadItem **__MIDL__ITemperatureLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            ITemperatureLoads * This,
            /* [in] */ LoadIDType ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ITemperatureLoads * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilterByStageGroup )( 
            ITemperatureLoads * This,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ITemperatureLoads **filteredcoll);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITemperatureLoads * This,
            /* [retval][out] */ ITemperatureLoads **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ITemperatureLoads * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ITemperatureLoads * This,
            /* [in] */ BSTR stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITemperatureLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } ITemperatureLoadsVtbl;

    interface ITemperatureLoads
    {
        CONST_VTBL struct ITemperatureLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemperatureLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemperatureLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemperatureLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemperatureLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ITemperatureLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ITemperatureLoads_get_Load(This,ID,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,ID,pVal) ) 

#define ITemperatureLoads_putref_Load(This,ID,newVal)	\
    ( (This)->lpVtbl -> putref_Load(This,ID,newVal) ) 

#define ITemperatureLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ITemperatureLoads_Add(This,Stage,LoadGroup,Load,Item)	\
    ( (This)->lpVtbl -> Add(This,Stage,LoadGroup,Load,Item) ) 

#define ITemperatureLoads_Find(This,ID,__MIDL__ITemperatureLoads0000)	\
    ( (This)->lpVtbl -> Find(This,ID,__MIDL__ITemperatureLoads0000) ) 

#define ITemperatureLoads_RemoveByID(This,ID)	\
    ( (This)->lpVtbl -> RemoveByID(This,ID) ) 

#define ITemperatureLoads_RemoveByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index) ) 

#define ITemperatureLoads_FilterByStageGroup(This,stage,loadgroup,filteredcoll)	\
    ( (This)->lpVtbl -> FilterByStageGroup(This,stage,loadgroup,filteredcoll) ) 

#define ITemperatureLoads_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ITemperatureLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ITemperatureLoads_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define ITemperatureLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemperatureLoads_INTERFACE_DEFINED__ */


#ifndef __ISettlementLoad_INTERFACE_DEFINED__
#define __ISettlementLoad_INTERFACE_DEFINED__

/* interface ISettlementLoad */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISettlementLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF2C8727-9357-11D5-B04E-00105A9AF985")
    ISettlementLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dx( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dx( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Rz( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Rz( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISettlementLoad **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISettlementLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISettlementLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISettlementLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISettlementLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            ISettlementLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            ISettlementLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dx )( 
            ISettlementLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dx )( 
            ISettlementLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dy )( 
            ISettlementLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dy )( 
            ISettlementLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rz )( 
            ISettlementLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Rz )( 
            ISettlementLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISettlementLoad * This,
            /* [retval][out] */ ISettlementLoad **clone);
        
        END_INTERFACE
    } ISettlementLoadVtbl;

    interface ISettlementLoad
    {
        CONST_VTBL struct ISettlementLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISettlementLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISettlementLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISettlementLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISettlementLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define ISettlementLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define ISettlementLoad_get_Dx(This,pVal)	\
    ( (This)->lpVtbl -> get_Dx(This,pVal) ) 

#define ISettlementLoad_put_Dx(This,newVal)	\
    ( (This)->lpVtbl -> put_Dx(This,newVal) ) 

#define ISettlementLoad_get_Dy(This,pVal)	\
    ( (This)->lpVtbl -> get_Dy(This,pVal) ) 

#define ISettlementLoad_put_Dy(This,newVal)	\
    ( (This)->lpVtbl -> put_Dy(This,newVal) ) 

#define ISettlementLoad_get_Rz(This,pVal)	\
    ( (This)->lpVtbl -> get_Rz(This,pVal) ) 

#define ISettlementLoad_put_Rz(This,newVal)	\
    ( (This)->lpVtbl -> put_Rz(This,newVal) ) 

#define ISettlementLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISettlementLoad_INTERFACE_DEFINED__ */


#ifndef __ISettlementLoadItem_INTERFACE_DEFINED__
#define __ISettlementLoadItem_INTERFACE_DEFINED__

/* interface ISettlementLoadItem */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISettlementLoadItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D13393A0-9326-11d5-B04E-00105A9AF985")
    ISettlementLoadItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroup( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [retval][out] */ ISettlementLoad **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISettlementLoadItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISettlementLoadItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISettlementLoadItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISettlementLoadItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            ISettlementLoadItem * This,
            /* [retval][out] */ LoadIDType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            ISettlementLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroup )( 
            ISettlementLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ISettlementLoadItem * This,
            /* [retval][out] */ ISettlementLoad **pVal);
        
        END_INTERFACE
    } ISettlementLoadItemVtbl;

    interface ISettlementLoadItem
    {
        CONST_VTBL struct ISettlementLoadItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISettlementLoadItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISettlementLoadItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISettlementLoadItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISettlementLoadItem_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define ISettlementLoadItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define ISettlementLoadItem_get_LoadGroup(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroup(This,pVal) ) 

#define ISettlementLoadItem_get_Load(This,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISettlementLoadItem_INTERFACE_DEFINED__ */


#ifndef __IEnumSettlementLoad_INTERFACE_DEFINED__
#define __IEnumSettlementLoad_INTERFACE_DEFINED__

/* interface IEnumSettlementLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumSettlementLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D13393A1-9326-11d5-B04E-00105A9AF985")
    IEnumSettlementLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSettlementLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ISettlementLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumSettlementLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSettlementLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSettlementLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSettlementLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSettlementLoad * This,
            /* [out] */ IEnumSettlementLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSettlementLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ ISettlementLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSettlementLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSettlementLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumSettlementLoadVtbl;

    interface IEnumSettlementLoad
    {
        CONST_VTBL struct IEnumSettlementLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSettlementLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSettlementLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSettlementLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSettlementLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumSettlementLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSettlementLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSettlementLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumSettlementLoad_INTERFACE_DEFINED__ */


#ifndef __ISettlementLoads_INTERFACE_DEFINED__
#define __ISettlementLoads_INTERFACE_DEFINED__

/* interface ISettlementLoads */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISettlementLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF2C872A-9357-11D5-B04E-00105A9AF985")
    ISettlementLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ISettlementLoadItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ ISettlementLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Load( 
            /* [in] */ LoadIDType ID,
            /* [in] */ ISettlementLoad *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumSettlementLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ISettlementLoad *Load,
            /* [retval][out] */ ISettlementLoadItem **Item) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ ISettlementLoadItem **__MIDL__ISettlementLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ LoadIDType ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FilterByStageGroup( 
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ISettlementLoads **filteredcoll) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ISettlementLoads **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISettlementLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISettlementLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISettlementLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISettlementLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISettlementLoads * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISettlementLoads * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ISettlementLoadItem **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ISettlementLoads * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ ISettlementLoad **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Load )( 
            ISettlementLoads * This,
            /* [in] */ LoadIDType ID,
            /* [in] */ ISettlementLoad *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ISettlementLoads * This,
            /* [retval][out] */ IEnumSettlementLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISettlementLoads * This,
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ISettlementLoad *Load,
            /* [retval][out] */ ISettlementLoadItem **Item);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ISettlementLoads * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ ISettlementLoadItem **__MIDL__ISettlementLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            ISettlementLoads * This,
            /* [in] */ LoadIDType ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ISettlementLoads * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilterByStageGroup )( 
            ISettlementLoads * This,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ISettlementLoads **filteredcoll);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISettlementLoads * This,
            /* [retval][out] */ ISettlementLoads **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISettlementLoads * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ISettlementLoads * This,
            /* [in] */ BSTR stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISettlementLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } ISettlementLoadsVtbl;

    interface ISettlementLoads
    {
        CONST_VTBL struct ISettlementLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISettlementLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISettlementLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISettlementLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISettlementLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISettlementLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ISettlementLoads_get_Load(This,ID,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,ID,pVal) ) 

#define ISettlementLoads_putref_Load(This,ID,newVal)	\
    ( (This)->lpVtbl -> putref_Load(This,ID,newVal) ) 

#define ISettlementLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ISettlementLoads_Add(This,Stage,LoadGroup,Load,Item)	\
    ( (This)->lpVtbl -> Add(This,Stage,LoadGroup,Load,Item) ) 

#define ISettlementLoads_Find(This,ID,__MIDL__ISettlementLoads0000)	\
    ( (This)->lpVtbl -> Find(This,ID,__MIDL__ISettlementLoads0000) ) 

#define ISettlementLoads_RemoveByID(This,ID)	\
    ( (This)->lpVtbl -> RemoveByID(This,ID) ) 

#define ISettlementLoads_RemoveByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index) ) 

#define ISettlementLoads_FilterByStageGroup(This,stage,loadgroup,filteredcoll)	\
    ( (This)->lpVtbl -> FilterByStageGroup(This,stage,loadgroup,filteredcoll) ) 

#define ISettlementLoads_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ISettlementLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ISettlementLoads_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define ISettlementLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISettlementLoads_INTERFACE_DEFINED__ */


#ifndef __IStrainLoad_INTERFACE_DEFINED__
#define __IStrainLoad_INTERFACE_DEFINED__

/* interface IStrainLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStrainLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B468209-9584-11D5-B050-00105A9AF985")
    IStrainLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberType( 
            /* [retval][out] */ MemberType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberType( 
            /* [in] */ MemberType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AxialStrain( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AxialStrain( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurvatureStrain( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CurvatureStrain( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartLocation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartLocation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndLocation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndLocation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IStrainLoad **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStrainLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStrainLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStrainLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStrainLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberType )( 
            IStrainLoad * This,
            /* [retval][out] */ MemberType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberType )( 
            IStrainLoad * This,
            /* [in] */ MemberType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            IStrainLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            IStrainLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AxialStrain )( 
            IStrainLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AxialStrain )( 
            IStrainLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurvatureStrain )( 
            IStrainLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CurvatureStrain )( 
            IStrainLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartLocation )( 
            IStrainLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartLocation )( 
            IStrainLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndLocation )( 
            IStrainLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndLocation )( 
            IStrainLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IStrainLoad * This,
            /* [retval][out] */ IStrainLoad **clone);
        
        END_INTERFACE
    } IStrainLoadVtbl;

    interface IStrainLoad
    {
        CONST_VTBL struct IStrainLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrainLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStrainLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStrainLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStrainLoad_get_MemberType(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberType(This,pVal) ) 

#define IStrainLoad_put_MemberType(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberType(This,newVal) ) 

#define IStrainLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define IStrainLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define IStrainLoad_get_AxialStrain(This,pVal)	\
    ( (This)->lpVtbl -> get_AxialStrain(This,pVal) ) 

#define IStrainLoad_put_AxialStrain(This,newVal)	\
    ( (This)->lpVtbl -> put_AxialStrain(This,newVal) ) 

#define IStrainLoad_get_CurvatureStrain(This,pVal)	\
    ( (This)->lpVtbl -> get_CurvatureStrain(This,pVal) ) 

#define IStrainLoad_put_CurvatureStrain(This,newVal)	\
    ( (This)->lpVtbl -> put_CurvatureStrain(This,newVal) ) 

#define IStrainLoad_get_StartLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_StartLocation(This,pVal) ) 

#define IStrainLoad_put_StartLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_StartLocation(This,newVal) ) 

#define IStrainLoad_get_EndLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_EndLocation(This,pVal) ) 

#define IStrainLoad_put_EndLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_EndLocation(This,newVal) ) 

#define IStrainLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrainLoad_INTERFACE_DEFINED__ */


#ifndef __IStrainLoadItem_INTERFACE_DEFINED__
#define __IStrainLoadItem_INTERFACE_DEFINED__

/* interface IStrainLoadItem */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStrainLoadItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A085C666-958F-11d5-B050-00105A9AF985")
    IStrainLoadItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroup( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [retval][out] */ IStrainLoad **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStrainLoadItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStrainLoadItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStrainLoadItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStrainLoadItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IStrainLoadItem * This,
            /* [retval][out] */ LoadIDType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            IStrainLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroup )( 
            IStrainLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            IStrainLoadItem * This,
            /* [retval][out] */ IStrainLoad **pVal);
        
        END_INTERFACE
    } IStrainLoadItemVtbl;

    interface IStrainLoadItem
    {
        CONST_VTBL struct IStrainLoadItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrainLoadItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStrainLoadItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStrainLoadItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStrainLoadItem_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IStrainLoadItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define IStrainLoadItem_get_LoadGroup(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroup(This,pVal) ) 

#define IStrainLoadItem_get_Load(This,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrainLoadItem_INTERFACE_DEFINED__ */


#ifndef __IEnumStrainLoad_INTERFACE_DEFINED__
#define __IEnumStrainLoad_INTERFACE_DEFINED__

/* interface IEnumStrainLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumStrainLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A085C667-958F-11d5-B050-00105A9AF985")
    IEnumStrainLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumStrainLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IStrainLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumStrainLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumStrainLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumStrainLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumStrainLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumStrainLoad * This,
            /* [out] */ IEnumStrainLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumStrainLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ IStrainLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumStrainLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumStrainLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumStrainLoadVtbl;

    interface IEnumStrainLoad
    {
        CONST_VTBL struct IEnumStrainLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumStrainLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumStrainLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumStrainLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumStrainLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumStrainLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumStrainLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumStrainLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumStrainLoad_INTERFACE_DEFINED__ */


#ifndef __IStrainLoads_INTERFACE_DEFINED__
#define __IStrainLoads_INTERFACE_DEFINED__

/* interface IStrainLoads */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStrainLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B46820C-9584-11D5-B050-00105A9AF985")
    IStrainLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IStrainLoadItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IStrainLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Load( 
            /* [in] */ LoadIDType ID,
            /* [in] */ IStrainLoad *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumStrainLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IStrainLoad *Load,
            /* [retval][out] */ IStrainLoadItem **Item) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IStrainLoadItem **__MIDL__IStrainLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ LoadIDType ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FilterByStageGroup( 
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ IStrainLoads **filteredcoll) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IStrainLoads **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStrainLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStrainLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStrainLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStrainLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IStrainLoads * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IStrainLoads * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IStrainLoadItem **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            IStrainLoads * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IStrainLoad **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Load )( 
            IStrainLoads * This,
            /* [in] */ LoadIDType ID,
            /* [in] */ IStrainLoad *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IStrainLoads * This,
            /* [retval][out] */ IEnumStrainLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IStrainLoads * This,
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ IStrainLoad *Load,
            /* [retval][out] */ IStrainLoadItem **Item);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IStrainLoads * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IStrainLoadItem **__MIDL__IStrainLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            IStrainLoads * This,
            /* [in] */ LoadIDType ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            IStrainLoads * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilterByStageGroup )( 
            IStrainLoads * This,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ IStrainLoads **filteredcoll);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IStrainLoads * This,
            /* [retval][out] */ IStrainLoads **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IStrainLoads * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            IStrainLoads * This,
            /* [in] */ BSTR stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IStrainLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } IStrainLoadsVtbl;

    interface IStrainLoads
    {
        CONST_VTBL struct IStrainLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrainLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStrainLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStrainLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStrainLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IStrainLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IStrainLoads_get_Load(This,ID,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,ID,pVal) ) 

#define IStrainLoads_putref_Load(This,ID,newVal)	\
    ( (This)->lpVtbl -> putref_Load(This,ID,newVal) ) 

#define IStrainLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IStrainLoads_Add(This,Stage,LoadGroup,Load,Item)	\
    ( (This)->lpVtbl -> Add(This,Stage,LoadGroup,Load,Item) ) 

#define IStrainLoads_Find(This,ID,__MIDL__IStrainLoads0000)	\
    ( (This)->lpVtbl -> Find(This,ID,__MIDL__IStrainLoads0000) ) 

#define IStrainLoads_RemoveByID(This,ID)	\
    ( (This)->lpVtbl -> RemoveByID(This,ID) ) 

#define IStrainLoads_RemoveByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index) ) 

#define IStrainLoads_FilterByStageGroup(This,stage,loadgroup,filteredcoll)	\
    ( (This)->lpVtbl -> FilterByStageGroup(This,stage,loadgroup,filteredcoll) ) 

#define IStrainLoads_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IStrainLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IStrainLoads_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define IStrainLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrainLoads_INTERFACE_DEFINED__ */


#ifndef __ILoadGroup_INTERFACE_DEFINED__
#define __ILoadGroup_INTERFACE_DEFINED__

/* interface ILoadGroup */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D54A59A1-95B0-11D5-B050-00105A9AF985")
    ILoadGroup : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILoadGroup **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Transient( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Transient( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadGroup * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadGroup * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadGroup * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ILoadGroup * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ILoadGroup * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ILoadGroup * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ILoadGroup * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILoadGroup * This,
            /* [retval][out] */ ILoadGroup **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Transient )( 
            ILoadGroup * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Transient )( 
            ILoadGroup * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } ILoadGroupVtbl;

    interface ILoadGroup
    {
        CONST_VTBL struct ILoadGroupVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadGroup_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadGroup_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadGroup_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadGroup_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ILoadGroup_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ILoadGroup_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define ILoadGroup_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define ILoadGroup_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ILoadGroup_get_Transient(This,pVal)	\
    ( (This)->lpVtbl -> get_Transient(This,pVal) ) 

#define ILoadGroup_put_Transient(This,newVal)	\
    ( (This)->lpVtbl -> put_Transient(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadGroup_INTERFACE_DEFINED__ */


#ifndef __IEnumLoadGroup_INTERFACE_DEFINED__
#define __IEnumLoadGroup_INTERFACE_DEFINED__

/* interface IEnumLoadGroup */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumLoadGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("52DAF0E8-95B3-11d5-B050-00105A9AF985")
    IEnumLoadGroup : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumLoadGroup **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ILoadGroup **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumLoadGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumLoadGroup * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumLoadGroup * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumLoadGroup * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumLoadGroup * This,
            /* [out] */ IEnumLoadGroup **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumLoadGroup * This,
            /* [in] */ ULONG celt,
            /* [out] */ ILoadGroup **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumLoadGroup * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumLoadGroup * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumLoadGroupVtbl;

    interface IEnumLoadGroup
    {
        CONST_VTBL struct IEnumLoadGroupVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumLoadGroup_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumLoadGroup_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumLoadGroup_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumLoadGroup_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumLoadGroup_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumLoadGroup_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumLoadGroup_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumLoadGroup_INTERFACE_DEFINED__ */


#ifndef __ILoadGroups_INTERFACE_DEFINED__
#define __ILoadGroups_INTERFACE_DEFINED__

/* interface ILoadGroups */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadGroups;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D54A59A4-95B0-11D5-B050-00105A9AF985")
    ILoadGroups : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ILoadGroup **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumLoadGroup **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ BSTR name,
            /* [retval][out] */ ILoadGroup **__MIDL__ILoadGroups0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ILoadGroup *__MIDL__ILoadGroups0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByName( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILoadGroups **__MIDL__ILoadGroups0002) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadGroupsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadGroups * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadGroups * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadGroups * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ILoadGroups * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ILoadGroup **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ILoadGroups * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILoadGroups * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ILoadGroups * This,
            /* [retval][out] */ IEnumLoadGroup **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ILoadGroups * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILoadGroup **__MIDL__ILoadGroups0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILoadGroups * This,
            /* [in] */ ILoadGroup *__MIDL__ILoadGroups0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByName )( 
            ILoadGroups * This,
            /* [in] */ BSTR name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ILoadGroups * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILoadGroups * This,
            /* [retval][out] */ ILoadGroups **__MIDL__ILoadGroups0002);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILoadGroups * This);
        
        END_INTERFACE
    } ILoadGroupsVtbl;

    interface ILoadGroups
    {
        CONST_VTBL struct ILoadGroupsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadGroups_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadGroups_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadGroups_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadGroups_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ILoadGroups_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ILoadGroups_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILoadGroups_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ILoadGroups_Find(This,name,__MIDL__ILoadGroups0000)	\
    ( (This)->lpVtbl -> Find(This,name,__MIDL__ILoadGroups0000) ) 

#define ILoadGroups_Add(This,__MIDL__ILoadGroups0001)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__ILoadGroups0001) ) 

#define ILoadGroups_RemoveByName(This,name)	\
    ( (This)->lpVtbl -> RemoveByName(This,name) ) 

#define ILoadGroups_RemoveByIndex(This,index,name)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index,name) ) 

#define ILoadGroups_Clone(This,__MIDL__ILoadGroups0002)	\
    ( (This)->lpVtbl -> Clone(This,__MIDL__ILoadGroups0002) ) 

#define ILoadGroups_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadGroups_INTERFACE_DEFINED__ */


#ifndef __ILoadCase_INTERFACE_DEFINED__
#define __ILoadCase_INTERFACE_DEFINED__

/* interface ILoadCase */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2AE5DD0D-3805-4B36-A5AB-F2ECB76B6F10")
    ILoadCase : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ItemData( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ItemData( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddLoadGroup( 
            /* [in] */ BSTR loadGroupName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLoadGroup( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ BSTR *loadGroupName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetLoadGroup( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveLoadGroup( 
            /* [in] */ BSTR loadGroupName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveLoadGroupByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILoadCase **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroupCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCase * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCase * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ILoadCase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ILoadCase * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ILoadCase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ILoadCase * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ItemData )( 
            ILoadCase * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ItemData )( 
            ILoadCase * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILoadCase * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddLoadGroup )( 
            ILoadCase * This,
            /* [in] */ BSTR loadGroupName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLoadGroup )( 
            ILoadCase * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ BSTR *loadGroupName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLoadGroup )( 
            ILoadCase * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ BSTR newName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveLoadGroup )( 
            ILoadCase * This,
            /* [in] */ BSTR loadGroupName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveLoadGroupByIndex )( 
            ILoadCase * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILoadCase * This,
            /* [retval][out] */ ILoadCase **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroupCount )( 
            ILoadCase * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        END_INTERFACE
    } ILoadCaseVtbl;

    interface ILoadCase
    {
        CONST_VTBL struct ILoadCaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCase_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCase_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCase_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCase_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ILoadCase_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ILoadCase_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define ILoadCase_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define ILoadCase_get_ItemData(This,pVal)	\
    ( (This)->lpVtbl -> get_ItemData(This,pVal) ) 

#define ILoadCase_put_ItemData(This,newVal)	\
    ( (This)->lpVtbl -> put_ItemData(This,newVal) ) 

#define ILoadCase_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILoadCase_AddLoadGroup(This,loadGroupName)	\
    ( (This)->lpVtbl -> AddLoadGroup(This,loadGroupName) ) 

#define ILoadCase_GetLoadGroup(This,index,loadGroupName)	\
    ( (This)->lpVtbl -> GetLoadGroup(This,index,loadGroupName) ) 

#define ILoadCase_SetLoadGroup(This,index,newName)	\
    ( (This)->lpVtbl -> SetLoadGroup(This,index,newName) ) 

#define ILoadCase_RemoveLoadGroup(This,loadGroupName)	\
    ( (This)->lpVtbl -> RemoveLoadGroup(This,loadGroupName) ) 

#define ILoadCase_RemoveLoadGroupByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveLoadGroupByIndex(This,index) ) 

#define ILoadCase_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ILoadCase_get_LoadGroupCount(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroupCount(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCase_INTERFACE_DEFINED__ */


#ifndef __IEnumLoadCase_INTERFACE_DEFINED__
#define __IEnumLoadCase_INTERFACE_DEFINED__

/* interface IEnumLoadCase */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumLoadCase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("28F1E1A5-5EFD-4372-95E4-2022FA2840B5")
    IEnumLoadCase : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumLoadCase **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ILoadCase **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumLoadCaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumLoadCase * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumLoadCase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumLoadCase * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumLoadCase * This,
            /* [out] */ IEnumLoadCase **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumLoadCase * This,
            /* [in] */ ULONG celt,
            /* [out] */ ILoadCase **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumLoadCase * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumLoadCase * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumLoadCaseVtbl;

    interface IEnumLoadCase
    {
        CONST_VTBL struct IEnumLoadCaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumLoadCase_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumLoadCase_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumLoadCase_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumLoadCase_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumLoadCase_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumLoadCase_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumLoadCase_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumLoadCase_INTERFACE_DEFINED__ */


#ifndef __ILoadCases_INTERFACE_DEFINED__
#define __ILoadCases_INTERFACE_DEFINED__

/* interface ILoadCases */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCases;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C4676A74-6DAB-43ff-B29B-88000C98FB53")
    ILoadCases : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ILoadCase **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumLoadCase **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ BSTR name,
            /* [retval][out] */ ILoadCase **loadCase) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ILoadCase *loadCase) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByName( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILoadCases **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCasesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCases * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCases * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCases * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ILoadCases * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ILoadCase **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ILoadCases * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILoadCases * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ILoadCases * This,
            /* [retval][out] */ IEnumLoadCase **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ILoadCases * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILoadCase **loadCase);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILoadCases * This,
            /* [in] */ ILoadCase *loadCase);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByName )( 
            ILoadCases * This,
            /* [in] */ BSTR name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ILoadCases * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILoadCases * This,
            /* [retval][out] */ ILoadCases **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILoadCases * This);
        
        END_INTERFACE
    } ILoadCasesVtbl;

    interface ILoadCases
    {
        CONST_VTBL struct ILoadCasesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCases_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCases_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCases_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCases_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ILoadCases_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ILoadCases_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILoadCases_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ILoadCases_Find(This,name,loadCase)	\
    ( (This)->lpVtbl -> Find(This,name,loadCase) ) 

#define ILoadCases_Add(This,loadCase)	\
    ( (This)->lpVtbl -> Add(This,loadCase) ) 

#define ILoadCases_RemoveByName(This,name)	\
    ( (This)->lpVtbl -> RemoveByName(This,name) ) 

#define ILoadCases_RemoveByIndex(This,index,name)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index,name) ) 

#define ILoadCases_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ILoadCases_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCases_INTERFACE_DEFINED__ */


#ifndef __ILoadCombination_INTERFACE_DEFINED__
#define __ILoadCombination_INTERFACE_DEFINED__

/* interface ILoadCombination */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCombination;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4ED1D8EA-F885-45E9-BD68-B5C73771A3AC")
    ILoadCombination : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLiveLoadModelCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLiveLoadModel( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ LiveLoadModelType *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveLiveLoadModel( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearLiveLoadModel( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddLiveLoadModel( 
            /* [in] */ LiveLoadModelType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LiveLoadFactor( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LiveLoadFactor( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadCaseFactorCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetLoadCaseFactor( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ BSTR loadCaseName,
            /* [in] */ Float64 minFactor,
            /* [in] */ Float64 maxFactor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddLoadCaseFactor( 
            /* [in] */ BSTR loadCaseName,
            /* [in] */ Float64 minFactor,
            /* [in] */ Float64 maxFactor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLoadCaseFactor( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ BSTR *loadCaseName,
            /* [out] */ Float64 *minFactor,
            /* [out] */ Float64 *maxFactor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FindLoadCaseFactor( 
            /* [in] */ BSTR loadCaseName,
            /* [out] */ Float64 *minFactor,
            /* [out] */ Float64 *maxFactor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveLoadCaseFactor( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILoadCombination **lone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ItemData( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ItemData( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadCombinationType( 
            /* [retval][out] */ LoadCombinationType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LoadCombinationType( 
            /* [in] */ LoadCombinationType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LiveLoadModelApplicationType( 
            /* [retval][out] */ LiveLoadModelApplicationType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LiveLoadModelApplicationType( 
            /* [in] */ LiveLoadModelApplicationType newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombination * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombination * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombination * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ILoadCombination * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ILoadCombination * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ILoadCombination * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ILoadCombination * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLiveLoadModelCount )( 
            ILoadCombination * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLiveLoadModel )( 
            ILoadCombination * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ LiveLoadModelType *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveLiveLoadModel )( 
            ILoadCombination * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearLiveLoadModel )( 
            ILoadCombination * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddLiveLoadModel )( 
            ILoadCombination * This,
            /* [in] */ LiveLoadModelType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LiveLoadFactor )( 
            ILoadCombination * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LiveLoadFactor )( 
            ILoadCombination * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCaseFactorCount )( 
            ILoadCombination * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLoadCaseFactor )( 
            ILoadCombination * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ BSTR loadCaseName,
            /* [in] */ Float64 minFactor,
            /* [in] */ Float64 maxFactor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddLoadCaseFactor )( 
            ILoadCombination * This,
            /* [in] */ BSTR loadCaseName,
            /* [in] */ Float64 minFactor,
            /* [in] */ Float64 maxFactor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLoadCaseFactor )( 
            ILoadCombination * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ BSTR *loadCaseName,
            /* [out] */ Float64 *minFactor,
            /* [out] */ Float64 *maxFactor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindLoadCaseFactor )( 
            ILoadCombination * This,
            /* [in] */ BSTR loadCaseName,
            /* [out] */ Float64 *minFactor,
            /* [out] */ Float64 *maxFactor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILoadCombination * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveLoadCaseFactor )( 
            ILoadCombination * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILoadCombination * This,
            /* [retval][out] */ ILoadCombination **lone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ItemData )( 
            ILoadCombination * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ItemData )( 
            ILoadCombination * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCombinationType )( 
            ILoadCombination * This,
            /* [retval][out] */ LoadCombinationType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LoadCombinationType )( 
            ILoadCombination * This,
            /* [in] */ LoadCombinationType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LiveLoadModelApplicationType )( 
            ILoadCombination * This,
            /* [retval][out] */ LiveLoadModelApplicationType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LiveLoadModelApplicationType )( 
            ILoadCombination * This,
            /* [in] */ LiveLoadModelApplicationType newVal);
        
        END_INTERFACE
    } ILoadCombinationVtbl;

    interface ILoadCombination
    {
        CONST_VTBL struct ILoadCombinationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombination_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombination_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombination_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombination_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ILoadCombination_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ILoadCombination_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define ILoadCombination_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define ILoadCombination_GetLiveLoadModelCount(This,pVal)	\
    ( (This)->lpVtbl -> GetLiveLoadModelCount(This,pVal) ) 

#define ILoadCombination_GetLiveLoadModel(This,index,pVal)	\
    ( (This)->lpVtbl -> GetLiveLoadModel(This,index,pVal) ) 

#define ILoadCombination_RemoveLiveLoadModel(This,index)	\
    ( (This)->lpVtbl -> RemoveLiveLoadModel(This,index) ) 

#define ILoadCombination_ClearLiveLoadModel(This)	\
    ( (This)->lpVtbl -> ClearLiveLoadModel(This) ) 

#define ILoadCombination_AddLiveLoadModel(This,newVal)	\
    ( (This)->lpVtbl -> AddLiveLoadModel(This,newVal) ) 

#define ILoadCombination_get_LiveLoadFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_LiveLoadFactor(This,pVal) ) 

#define ILoadCombination_put_LiveLoadFactor(This,newVal)	\
    ( (This)->lpVtbl -> put_LiveLoadFactor(This,newVal) ) 

#define ILoadCombination_get_LoadCaseFactorCount(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadCaseFactorCount(This,pVal) ) 

#define ILoadCombination_SetLoadCaseFactor(This,index,loadCaseName,minFactor,maxFactor)	\
    ( (This)->lpVtbl -> SetLoadCaseFactor(This,index,loadCaseName,minFactor,maxFactor) ) 

#define ILoadCombination_AddLoadCaseFactor(This,loadCaseName,minFactor,maxFactor)	\
    ( (This)->lpVtbl -> AddLoadCaseFactor(This,loadCaseName,minFactor,maxFactor) ) 

#define ILoadCombination_GetLoadCaseFactor(This,index,loadCaseName,minFactor,maxFactor)	\
    ( (This)->lpVtbl -> GetLoadCaseFactor(This,index,loadCaseName,minFactor,maxFactor) ) 

#define ILoadCombination_FindLoadCaseFactor(This,loadCaseName,minFactor,maxFactor)	\
    ( (This)->lpVtbl -> FindLoadCaseFactor(This,loadCaseName,minFactor,maxFactor) ) 

#define ILoadCombination_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILoadCombination_RemoveLoadCaseFactor(This,index)	\
    ( (This)->lpVtbl -> RemoveLoadCaseFactor(This,index) ) 

#define ILoadCombination_Clone(This,lone)	\
    ( (This)->lpVtbl -> Clone(This,lone) ) 

#define ILoadCombination_get_ItemData(This,pVal)	\
    ( (This)->lpVtbl -> get_ItemData(This,pVal) ) 

#define ILoadCombination_put_ItemData(This,newVal)	\
    ( (This)->lpVtbl -> put_ItemData(This,newVal) ) 

#define ILoadCombination_get_LoadCombinationType(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadCombinationType(This,pVal) ) 

#define ILoadCombination_put_LoadCombinationType(This,newVal)	\
    ( (This)->lpVtbl -> put_LoadCombinationType(This,newVal) ) 

#define ILoadCombination_get_LiveLoadModelApplicationType(This,pVal)	\
    ( (This)->lpVtbl -> get_LiveLoadModelApplicationType(This,pVal) ) 

#define ILoadCombination_put_LiveLoadModelApplicationType(This,newVal)	\
    ( (This)->lpVtbl -> put_LiveLoadModelApplicationType(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombination_INTERFACE_DEFINED__ */


#ifndef __IEnumLoadCombination_INTERFACE_DEFINED__
#define __IEnumLoadCombination_INTERFACE_DEFINED__

/* interface IEnumLoadCombination */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumLoadCombination;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E114C7D0-5E53-4B48-AF97-D3021B5BF949")
    IEnumLoadCombination : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumLoadCombination **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ILoadCombination **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumLoadCombinationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumLoadCombination * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumLoadCombination * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumLoadCombination * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumLoadCombination * This,
            /* [out] */ IEnumLoadCombination **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumLoadCombination * This,
            /* [in] */ ULONG celt,
            /* [out] */ ILoadCombination **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumLoadCombination * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumLoadCombination * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumLoadCombinationVtbl;

    interface IEnumLoadCombination
    {
        CONST_VTBL struct IEnumLoadCombinationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumLoadCombination_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumLoadCombination_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumLoadCombination_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumLoadCombination_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumLoadCombination_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumLoadCombination_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumLoadCombination_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumLoadCombination_INTERFACE_DEFINED__ */


#ifndef __ILoadCombinations_INTERFACE_DEFINED__
#define __ILoadCombinations_INTERFACE_DEFINED__

/* interface ILoadCombinations */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILoadCombinations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F48D820-04C6-4b6b-91C7-2F64CE0B8279")
    ILoadCombinations : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ILoadCombination **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumLoadCombination **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ BSTR name,
            /* [retval][out] */ ILoadCombination **__MIDL__ILoadCombinations0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ILoadCombination *__MIDL__ILoadCombinations0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByName( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILoadCombinations **__MIDL__ILoadCombinations0002) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombinations * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombinations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombinations * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ILoadCombinations * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ILoadCombination **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ILoadCombinations * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ILoadCombinations * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ILoadCombinations * This,
            /* [retval][out] */ IEnumLoadCombination **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ILoadCombinations * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ILoadCombination **__MIDL__ILoadCombinations0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ILoadCombinations * This,
            /* [in] */ ILoadCombination *__MIDL__ILoadCombinations0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByName )( 
            ILoadCombinations * This,
            /* [in] */ BSTR name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ILoadCombinations * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILoadCombinations * This,
            /* [retval][out] */ ILoadCombinations **__MIDL__ILoadCombinations0002);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILoadCombinations * This);
        
        END_INTERFACE
    } ILoadCombinationsVtbl;

    interface ILoadCombinations
    {
        CONST_VTBL struct ILoadCombinationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombinations_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombinations_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombinations_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombinations_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ILoadCombinations_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ILoadCombinations_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ILoadCombinations_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ILoadCombinations_Find(This,name,__MIDL__ILoadCombinations0000)	\
    ( (This)->lpVtbl -> Find(This,name,__MIDL__ILoadCombinations0000) ) 

#define ILoadCombinations_Add(This,__MIDL__ILoadCombinations0001)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__ILoadCombinations0001) ) 

#define ILoadCombinations_RemoveByName(This,name)	\
    ( (This)->lpVtbl -> RemoveByName(This,name) ) 

#define ILoadCombinations_RemoveByIndex(This,index,name)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index,name) ) 

#define ILoadCombinations_Clone(This,__MIDL__ILoadCombinations0002)	\
    ( (This)->lpVtbl -> Clone(This,__MIDL__ILoadCombinations0002) ) 

#define ILoadCombinations_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombinations_INTERFACE_DEFINED__ */


#ifndef __IDistributionFactorSegment_INTERFACE_DEFINED__
#define __IDistributionFactorSegment_INTERFACE_DEFINED__

/* interface IDistributionFactorSegment */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDistributionFactorSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F15D6CD7-E15D-4033-9C01-8BC2151D96D8")
    IDistributionFactorSegment : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DistributionFactor( 
            /* [retval][out] */ IDistributionFactor **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_DistributionFactor( 
            /* [in] */ IDistributionFactor *newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IDistributionFactorSegment **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributionFactorSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributionFactorSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributionFactorSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributionFactorSegment * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IDistributionFactorSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            IDistributionFactorSegment * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DistributionFactor )( 
            IDistributionFactorSegment * This,
            /* [retval][out] */ IDistributionFactor **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DistributionFactor )( 
            IDistributionFactorSegment * This,
            /* [in] */ IDistributionFactor *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDistributionFactorSegment * This,
            /* [out] */ IDistributionFactorSegment **clone);
        
        END_INTERFACE
    } IDistributionFactorSegmentVtbl;

    interface IDistributionFactorSegment
    {
        CONST_VTBL struct IDistributionFactorSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributionFactorSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributionFactorSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributionFactorSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributionFactorSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define IDistributionFactorSegment_put_Length(This,newVal)	\
    ( (This)->lpVtbl -> put_Length(This,newVal) ) 

#define IDistributionFactorSegment_get_DistributionFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_DistributionFactor(This,pVal) ) 

#define IDistributionFactorSegment_putref_DistributionFactor(This,newVal)	\
    ( (This)->lpVtbl -> putref_DistributionFactor(This,newVal) ) 

#define IDistributionFactorSegment_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributionFactorSegment_INTERFACE_DEFINED__ */


#ifndef __ILinearDistributionFactorSegment_INTERFACE_DEFINED__
#define __ILinearDistributionFactorSegment_INTERFACE_DEFINED__

/* interface ILinearDistributionFactorSegment */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILinearDistributionFactorSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("176038BE-9484-469d-97DD-D2764B0FBAE9")
    ILinearDistributionFactorSegment : public IDistributionFactorSegment
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndDistributionFactor( 
            /* [retval][out] */ IDistributionFactor **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_EndDistributionFactor( 
            /* [in] */ IDistributionFactor *newVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateDistributionFactor( 
            /* [in] */ Float64 dist,
            /* [retval][out] */ IDistributionFactor **pFactor) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILinearDistributionFactorSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILinearDistributionFactorSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILinearDistributionFactorSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILinearDistributionFactorSegment * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ILinearDistributionFactorSegment * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            ILinearDistributionFactorSegment * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DistributionFactor )( 
            ILinearDistributionFactorSegment * This,
            /* [retval][out] */ IDistributionFactor **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DistributionFactor )( 
            ILinearDistributionFactorSegment * This,
            /* [in] */ IDistributionFactor *newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILinearDistributionFactorSegment * This,
            /* [out] */ IDistributionFactorSegment **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndDistributionFactor )( 
            ILinearDistributionFactorSegment * This,
            /* [retval][out] */ IDistributionFactor **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_EndDistributionFactor )( 
            ILinearDistributionFactorSegment * This,
            /* [in] */ IDistributionFactor *newVal);
        
        HRESULT ( STDMETHODCALLTYPE *CreateDistributionFactor )( 
            ILinearDistributionFactorSegment * This,
            /* [in] */ Float64 dist,
            /* [retval][out] */ IDistributionFactor **pFactor);
        
        END_INTERFACE
    } ILinearDistributionFactorSegmentVtbl;

    interface ILinearDistributionFactorSegment
    {
        CONST_VTBL struct ILinearDistributionFactorSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILinearDistributionFactorSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILinearDistributionFactorSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILinearDistributionFactorSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILinearDistributionFactorSegment_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#define ILinearDistributionFactorSegment_put_Length(This,newVal)	\
    ( (This)->lpVtbl -> put_Length(This,newVal) ) 

#define ILinearDistributionFactorSegment_get_DistributionFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_DistributionFactor(This,pVal) ) 

#define ILinearDistributionFactorSegment_putref_DistributionFactor(This,newVal)	\
    ( (This)->lpVtbl -> putref_DistributionFactor(This,newVal) ) 

#define ILinearDistributionFactorSegment_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 


#define ILinearDistributionFactorSegment_get_EndDistributionFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_EndDistributionFactor(This,pVal) ) 

#define ILinearDistributionFactorSegment_putref_EndDistributionFactor(This,newVal)	\
    ( (This)->lpVtbl -> putref_EndDistributionFactor(This,newVal) ) 

#define ILinearDistributionFactorSegment_CreateDistributionFactor(This,dist,pFactor)	\
    ( (This)->lpVtbl -> CreateDistributionFactor(This,dist,pFactor) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILinearDistributionFactorSegment_INTERFACE_DEFINED__ */


#ifndef __IEnumDistributionFactorSegment_INTERFACE_DEFINED__
#define __IEnumDistributionFactorSegment_INTERFACE_DEFINED__

/* interface IEnumDistributionFactorSegment */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumDistributionFactorSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CA93AE99-EA30-4d83-97B1-16C93210F4AD")
    IEnumDistributionFactorSegment : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumDistributionFactorSegment **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IDistributionFactorSegment **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumDistributionFactorSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumDistributionFactorSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumDistributionFactorSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumDistributionFactorSegment * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumDistributionFactorSegment * This,
            /* [out] */ IEnumDistributionFactorSegment **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumDistributionFactorSegment * This,
            /* [in] */ ULONG celt,
            /* [out] */ IDistributionFactorSegment **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumDistributionFactorSegment * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumDistributionFactorSegment * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumDistributionFactorSegmentVtbl;

    interface IEnumDistributionFactorSegment
    {
        CONST_VTBL struct IEnumDistributionFactorSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumDistributionFactorSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumDistributionFactorSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumDistributionFactorSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumDistributionFactorSegment_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumDistributionFactorSegment_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumDistributionFactorSegment_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumDistributionFactorSegment_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumDistributionFactorSegment_INTERFACE_DEFINED__ */


#ifndef __IFilteredDfSegmentCollection_INTERFACE_DEFINED__
#define __IFilteredDfSegmentCollection_INTERFACE_DEFINED__

/* interface IFilteredDfSegmentCollection */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFilteredDfSegmentCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("75CDEDAD-469A-43B3-B6EF-1F1AA5B5A81E")
    IFilteredDfSegmentCollection : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ SegmentIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ SegmentIndexType index,
            /* [retval][out] */ IDistributionFactorSegment **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumDistributionFactorSegment **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFilteredDfSegmentCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFilteredDfSegmentCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFilteredDfSegmentCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFilteredDfSegmentCollection * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFilteredDfSegmentCollection * This,
            /* [retval][out] */ SegmentIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFilteredDfSegmentCollection * This,
            /* [in] */ SegmentIndexType index,
            /* [retval][out] */ IDistributionFactorSegment **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFilteredDfSegmentCollection * This,
            /* [retval][out] */ IEnumDistributionFactorSegment **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFilteredDfSegmentCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } IFilteredDfSegmentCollectionVtbl;

    interface IFilteredDfSegmentCollection
    {
        CONST_VTBL struct IFilteredDfSegmentCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilteredDfSegmentCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFilteredDfSegmentCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFilteredDfSegmentCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFilteredDfSegmentCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFilteredDfSegmentCollection_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IFilteredDfSegmentCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFilteredDfSegmentCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFilteredDfSegmentCollection_INTERFACE_DEFINED__ */


#ifndef __IDistributionFactors_INTERFACE_DEFINED__
#define __IDistributionFactors_INTERFACE_DEFINED__

/* interface IDistributionFactors */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDistributionFactors;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("725FB633-9B25-429D-A4F7-3BA47B4DE5A2")
    IDistributionFactors : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ IDistributionFactorSegment **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Item( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IDistributionFactorSegment *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IEnumDistributionFactorSegment **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [in] */ Float64 superstructureLength,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IDistributionFactorSegment *__MIDL__IDistributionFactors0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IDistributionFactorSegment *__MIDL__IDistributionFactors0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ CollectionIndexType fromRelPosition,
            /* [in] */ CollectionIndexType toRelPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [in] */ CollectionIndexType fromRelPosition,
            /* [in] */ CollectionIndexType toRelPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType relPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSegmentForLocation( 
            /* [in] */ Float64 location,
            /* [in] */ Float64 superstructureLength,
            /* [out] */ IDistributionFactorSegment **leftSegment,
            /* [out] */ IDistributionFactorSegment **rightSegment) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetFactorForLocation( 
            /* [in] */ Float64 location,
            /* [in] */ Float64 superstructureLength,
            /* [out] */ IDistributionFactor **leftLLDF,
            /* [out] */ IDistributionFactor **rightLLDF) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetMemberSegments( 
            /* [in] */ Float64 superstructureLength,
            /* [retval][out] */ IFilteredDfSegmentCollection **segments) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IDistributionFactors **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsSymmetrical( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IsSymmetrical( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributionFactorsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributionFactors * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributionFactors * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributionFactors * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IDistributionFactors * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [retval][out] */ IDistributionFactorSegment **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Item )( 
            IDistributionFactors * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IDistributionFactorSegment *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IDistributionFactors * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IDistributionFactors * This,
            /* [retval][out] */ IEnumDistributionFactorSegment **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IDistributionFactors * This,
            /* [in] */ Float64 superstructureLength,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IDistributionFactors * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IDistributionFactors * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IDistributionFactors * This,
            /* [in] */ IDistributionFactorSegment *__MIDL__IDistributionFactors0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IDistributionFactors * This,
            /* [in] */ CollectionIndexType relPosition,
            /* [in] */ IDistributionFactorSegment *__MIDL__IDistributionFactors0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            IDistributionFactors * This,
            /* [in] */ CollectionIndexType fromRelPosition,
            /* [in] */ CollectionIndexType toRelPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CopyTo )( 
            IDistributionFactors * This,
            /* [in] */ CollectionIndexType fromRelPosition,
            /* [in] */ CollectionIndexType toRelPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IDistributionFactors * This,
            /* [in] */ CollectionIndexType relPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            IDistributionFactors * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSegmentForLocation )( 
            IDistributionFactors * This,
            /* [in] */ Float64 location,
            /* [in] */ Float64 superstructureLength,
            /* [out] */ IDistributionFactorSegment **leftSegment,
            /* [out] */ IDistributionFactorSegment **rightSegment);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFactorForLocation )( 
            IDistributionFactors * This,
            /* [in] */ Float64 location,
            /* [in] */ Float64 superstructureLength,
            /* [out] */ IDistributionFactor **leftLLDF,
            /* [out] */ IDistributionFactor **rightLLDF);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMemberSegments )( 
            IDistributionFactors * This,
            /* [in] */ Float64 superstructureLength,
            /* [retval][out] */ IFilteredDfSegmentCollection **segments);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDistributionFactors * This,
            /* [retval][out] */ IDistributionFactors **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSymmetrical )( 
            IDistributionFactors * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsSymmetrical )( 
            IDistributionFactors * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IDistributionFactorsVtbl;

    interface IDistributionFactors
    {
        CONST_VTBL struct IDistributionFactorsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributionFactors_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributionFactors_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributionFactors_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributionFactors_get_Item(This,relPosition,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,relPosition,pVal) ) 

#define IDistributionFactors_putref_Item(This,relPosition,pVal)	\
    ( (This)->lpVtbl -> putref_Item(This,relPosition,pVal) ) 

#define IDistributionFactors_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IDistributionFactors_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IDistributionFactors_get_Length(This,superstructureLength,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,superstructureLength,pVal) ) 

#define IDistributionFactors_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IDistributionFactors_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IDistributionFactors_Add(This,__MIDL__IDistributionFactors0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__IDistributionFactors0000) ) 

#define IDistributionFactors_Insert(This,relPosition,__MIDL__IDistributionFactors0001)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,__MIDL__IDistributionFactors0001) ) 

#define IDistributionFactors_MoveTo(This,fromRelPosition,toRelPosition)	\
    ( (This)->lpVtbl -> MoveTo(This,fromRelPosition,toRelPosition) ) 

#define IDistributionFactors_CopyTo(This,fromRelPosition,toRelPosition)	\
    ( (This)->lpVtbl -> CopyTo(This,fromRelPosition,toRelPosition) ) 

#define IDistributionFactors_Remove(This,relPosition)	\
    ( (This)->lpVtbl -> Remove(This,relPosition) ) 

#define IDistributionFactors_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define IDistributionFactors_GetSegmentForLocation(This,location,superstructureLength,leftSegment,rightSegment)	\
    ( (This)->lpVtbl -> GetSegmentForLocation(This,location,superstructureLength,leftSegment,rightSegment) ) 

#define IDistributionFactors_GetFactorForLocation(This,location,superstructureLength,leftLLDF,rightLLDF)	\
    ( (This)->lpVtbl -> GetFactorForLocation(This,location,superstructureLength,leftLLDF,rightLLDF) ) 

#define IDistributionFactors_GetMemberSegments(This,superstructureLength,segments)	\
    ( (This)->lpVtbl -> GetMemberSegments(This,superstructureLength,segments) ) 

#define IDistributionFactors_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define IDistributionFactors_get_IsSymmetrical(This,pVal)	\
    ( (This)->lpVtbl -> get_IsSymmetrical(This,pVal) ) 

#define IDistributionFactors_put_IsSymmetrical(This,newVal)	\
    ( (This)->lpVtbl -> put_IsSymmetrical(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributionFactors_INTERFACE_DEFINED__ */


#ifndef __ILBAMModel_INTERFACE_DEFINED__
#define __ILBAMModel_INTERFACE_DEFINED__

/* interface ILBAMModel */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILBAMModel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6B18F78-803D-11D5-B039-00105A9AF985")
    ILBAMModel : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SuperstructureMembers( 
            /* [retval][out] */ ISuperstructureMembers **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILBAMModel **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Supports( 
            /* [retval][out] */ ISupports **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Spans( 
            /* [retval][out] */ ISpans **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TemporarySupports( 
            /* [retval][out] */ ITemporarySupports **ppVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_POIs( 
            /* [retval][out] */ IPOIs **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stages( 
            /* [retval][out] */ IStages **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            BSTR stage) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RightSupport( 
            /* [in] */ SupportIndexType relPosition,
            /* [retval][out] */ ISupport **__MIDL__ILBAMModel0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LeftSupport( 
            /* [in] */ SupportIndexType relPosition,
            /* [retval][out] */ ISupport **__MIDL__ILBAMModel0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RightSpan( 
            /* [in] */ SpanIndexType relPosition,
            /* [retval][out] */ ISpan **__MIDL__ILBAMModel0002) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE LeftSpan( 
            /* [in] */ SpanIndexType relPosition,
            /* [retval][out] */ ISpan **__MIDL__ILBAMModel0003) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PointLoads( 
            /* [retval][out] */ IPointLoads **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DistributedLoads( 
            /* [retval][out] */ IDistributedLoads **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TemperatureLoads( 
            /* [retval][out] */ ITemperatureLoads **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SettlementLoads( 
            /* [retval][out] */ ISettlementLoads **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StrainLoads( 
            /* [retval][out] */ IStrainLoads **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroups( 
            /* [retval][out] */ ILoadGroups **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadCases( 
            /* [retval][out] */ ILoadCases **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadCombinations( 
            /* [retval][out] */ ILoadCombinations **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ComputeLocation( 
            /* [in] */ MemberIDType mbrID,
            /* [in] */ MemberType mbrType,
            /* [in] */ Float64 mbrLocation,
            /* [out] */ Float64 *Xloc,
            /* [out] */ Float64 *Yloc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertSpanToSuperstructureLocation( 
            /* [in] */ MemberIDType spanMbrID,
            /* [in] */ Float64 spanLoc,
            /* [out] */ MemberIDType *pSSMbrID,
            /* [out] */ Float64 *pSSMbrLoc) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LiveLoad( 
            /* [retval][out] */ ILiveLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DistributionFactors( 
            /* [retval][out] */ IDistributionFactors **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILBAMModelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILBAMModel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILBAMModel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILBAMModel * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ILBAMModel * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ILBAMModel * This,
            /* [in] */ BSTR name);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuperstructureMembers )( 
            ILBAMModel * This,
            /* [retval][out] */ ISuperstructureMembers **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILBAMModel * This,
            /* [retval][out] */ ILBAMModel **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Supports )( 
            ILBAMModel * This,
            /* [retval][out] */ ISupports **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spans )( 
            ILBAMModel * This,
            /* [retval][out] */ ISpans **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TemporarySupports )( 
            ILBAMModel * This,
            /* [retval][out] */ ITemporarySupports **ppVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ILBAMModel * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_POIs )( 
            ILBAMModel * This,
            /* [retval][out] */ IPOIs **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stages )( 
            ILBAMModel * This,
            /* [retval][out] */ IStages **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ILBAMModel * This,
            BSTR stage);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RightSupport )( 
            ILBAMModel * This,
            /* [in] */ SupportIndexType relPosition,
            /* [retval][out] */ ISupport **__MIDL__ILBAMModel0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LeftSupport )( 
            ILBAMModel * This,
            /* [in] */ SupportIndexType relPosition,
            /* [retval][out] */ ISupport **__MIDL__ILBAMModel0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RightSpan )( 
            ILBAMModel * This,
            /* [in] */ SpanIndexType relPosition,
            /* [retval][out] */ ISpan **__MIDL__ILBAMModel0002);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LeftSpan )( 
            ILBAMModel * This,
            /* [in] */ SpanIndexType relPosition,
            /* [retval][out] */ ISpan **__MIDL__ILBAMModel0003);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointLoads )( 
            ILBAMModel * This,
            /* [retval][out] */ IPointLoads **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DistributedLoads )( 
            ILBAMModel * This,
            /* [retval][out] */ IDistributedLoads **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TemperatureLoads )( 
            ILBAMModel * This,
            /* [retval][out] */ ITemperatureLoads **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SettlementLoads )( 
            ILBAMModel * This,
            /* [retval][out] */ ISettlementLoads **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrainLoads )( 
            ILBAMModel * This,
            /* [retval][out] */ IStrainLoads **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroups )( 
            ILBAMModel * This,
            /* [retval][out] */ ILoadGroups **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCases )( 
            ILBAMModel * This,
            /* [retval][out] */ ILoadCases **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCombinations )( 
            ILBAMModel * This,
            /* [retval][out] */ ILoadCombinations **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ComputeLocation )( 
            ILBAMModel * This,
            /* [in] */ MemberIDType mbrID,
            /* [in] */ MemberType mbrType,
            /* [in] */ Float64 mbrLocation,
            /* [out] */ Float64 *Xloc,
            /* [out] */ Float64 *Yloc);
        
        HRESULT ( STDMETHODCALLTYPE *ConvertSpanToSuperstructureLocation )( 
            ILBAMModel * This,
            /* [in] */ MemberIDType spanMbrID,
            /* [in] */ Float64 spanLoc,
            /* [out] */ MemberIDType *pSSMbrID,
            /* [out] */ Float64 *pSSMbrLoc);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LiveLoad )( 
            ILBAMModel * This,
            /* [retval][out] */ ILiveLoad **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DistributionFactors )( 
            ILBAMModel * This,
            /* [retval][out] */ IDistributionFactors **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ILBAMModel * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } ILBAMModelVtbl;

    interface ILBAMModel
    {
        CONST_VTBL struct ILBAMModelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILBAMModel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILBAMModel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILBAMModel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILBAMModel_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define ILBAMModel_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 

#define ILBAMModel_get_SuperstructureMembers(This,pVal)	\
    ( (This)->lpVtbl -> get_SuperstructureMembers(This,pVal) ) 

#define ILBAMModel_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ILBAMModel_get_Supports(This,pVal)	\
    ( (This)->lpVtbl -> get_Supports(This,pVal) ) 

#define ILBAMModel_get_Spans(This,pVal)	\
    ( (This)->lpVtbl -> get_Spans(This,pVal) ) 

#define ILBAMModel_get_TemporarySupports(This,ppVal)	\
    ( (This)->lpVtbl -> get_TemporarySupports(This,ppVal) ) 

#define ILBAMModel_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ILBAMModel_get_POIs(This,pVal)	\
    ( (This)->lpVtbl -> get_POIs(This,pVal) ) 

#define ILBAMModel_get_Stages(This,pVal)	\
    ( (This)->lpVtbl -> get_Stages(This,pVal) ) 

#define ILBAMModel_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define ILBAMModel_RightSupport(This,relPosition,__MIDL__ILBAMModel0000)	\
    ( (This)->lpVtbl -> RightSupport(This,relPosition,__MIDL__ILBAMModel0000) ) 

#define ILBAMModel_LeftSupport(This,relPosition,__MIDL__ILBAMModel0001)	\
    ( (This)->lpVtbl -> LeftSupport(This,relPosition,__MIDL__ILBAMModel0001) ) 

#define ILBAMModel_RightSpan(This,relPosition,__MIDL__ILBAMModel0002)	\
    ( (This)->lpVtbl -> RightSpan(This,relPosition,__MIDL__ILBAMModel0002) ) 

#define ILBAMModel_LeftSpan(This,relPosition,__MIDL__ILBAMModel0003)	\
    ( (This)->lpVtbl -> LeftSpan(This,relPosition,__MIDL__ILBAMModel0003) ) 

#define ILBAMModel_get_PointLoads(This,pVal)	\
    ( (This)->lpVtbl -> get_PointLoads(This,pVal) ) 

#define ILBAMModel_get_DistributedLoads(This,pVal)	\
    ( (This)->lpVtbl -> get_DistributedLoads(This,pVal) ) 

#define ILBAMModel_get_TemperatureLoads(This,pVal)	\
    ( (This)->lpVtbl -> get_TemperatureLoads(This,pVal) ) 

#define ILBAMModel_get_SettlementLoads(This,pVal)	\
    ( (This)->lpVtbl -> get_SettlementLoads(This,pVal) ) 

#define ILBAMModel_get_StrainLoads(This,pVal)	\
    ( (This)->lpVtbl -> get_StrainLoads(This,pVal) ) 

#define ILBAMModel_get_LoadGroups(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroups(This,pVal) ) 

#define ILBAMModel_get_LoadCases(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadCases(This,pVal) ) 

#define ILBAMModel_get_LoadCombinations(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadCombinations(This,pVal) ) 

#define ILBAMModel_ComputeLocation(This,mbrID,mbrType,mbrLocation,Xloc,Yloc)	\
    ( (This)->lpVtbl -> ComputeLocation(This,mbrID,mbrType,mbrLocation,Xloc,Yloc) ) 

#define ILBAMModel_ConvertSpanToSuperstructureLocation(This,spanMbrID,spanLoc,pSSMbrID,pSSMbrLoc)	\
    ( (This)->lpVtbl -> ConvertSpanToSuperstructureLocation(This,spanMbrID,spanLoc,pSSMbrID,pSSMbrLoc) ) 

#define ILBAMModel_get_LiveLoad(This,pVal)	\
    ( (This)->lpVtbl -> get_LiveLoad(This,pVal) ) 

#define ILBAMModel_get_DistributionFactors(This,pVal)	\
    ( (This)->lpVtbl -> get_DistributionFactors(This,pVal) ) 

#define ILBAMModel_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILBAMModel_INTERFACE_DEFINED__ */


#ifndef __ILBAMModelEvents_INTERFACE_DEFINED__
#define __ILBAMModelEvents_INTERFACE_DEFINED__

/* interface ILBAMModelEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILBAMModelEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AC860160-8050-11d5-B039-00105A9AF985")
    ILBAMModelEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnModelChanged( 
            /* [in] */ ILBAMModel *me,
            /* [in] */ ChangeType change) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILBAMModelEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILBAMModelEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILBAMModelEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILBAMModelEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnModelChanged )( 
            ILBAMModelEvents * This,
            /* [in] */ ILBAMModel *me,
            /* [in] */ ChangeType change);
        
        END_INTERFACE
    } ILBAMModelEventsVtbl;

    interface ILBAMModelEvents
    {
        CONST_VTBL struct ILBAMModelEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILBAMModelEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILBAMModelEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILBAMModelEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILBAMModelEvents_OnModelChanged(This,me,change)	\
    ( (This)->lpVtbl -> OnModelChanged(This,me,change) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILBAMModelEvents_INTERFACE_DEFINED__ */


#ifndef __ISupportEvents_INTERFACE_DEFINED__
#define __ISupportEvents_INTERFACE_DEFINED__

/* interface ISupportEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISupportEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EA251D37-82BB-11d5-B03C-00105A9AF985")
    ISupportEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSupportChanged( 
            /* [in] */ ISupport *Support,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupportEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupportEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupportEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSupportChanged )( 
            ISupportEvents * This,
            /* [in] */ ISupport *Support,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change);
        
        END_INTERFACE
    } ISupportEventsVtbl;

    interface ISupportEvents
    {
        CONST_VTBL struct ISupportEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupportEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupportEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupportEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupportEvents_OnSupportChanged(This,Support,stage,change)	\
    ( (This)->lpVtbl -> OnSupportChanged(This,Support,stage,change) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupportEvents_INTERFACE_DEFINED__ */


#ifndef __ISupportsEvents_INTERFACE_DEFINED__
#define __ISupportsEvents_INTERFACE_DEFINED__

/* interface ISupportsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISupportsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EA251D3B-82BB-11d5-B03C-00105A9AF985")
    ISupportsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSupportsChanged( 
            /* [in] */ ISupport *Support,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSupportsAdded( 
            /* [in] */ ISupport *Support,
            /* [in] */ SupportIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSupportsBeforeRemove( 
            /* [in] */ ISupport *Support,
            /* [in] */ SupportIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSupportsMoveTo( 
            /* [in] */ SupportIndexType from,
            /* [in] */ SupportIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSupportsCopyTo( 
            /* [in] */ SupportIndexType from,
            /* [in] */ SupportIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSupportsReverse( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupportsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupportsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupportsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSupportsChanged )( 
            ISupportsEvents * This,
            /* [in] */ ISupport *Support,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSupportsAdded )( 
            ISupportsEvents * This,
            /* [in] */ ISupport *Support,
            /* [in] */ SupportIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSupportsBeforeRemove )( 
            ISupportsEvents * This,
            /* [in] */ ISupport *Support,
            /* [in] */ SupportIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSupportsMoveTo )( 
            ISupportsEvents * This,
            /* [in] */ SupportIndexType from,
            /* [in] */ SupportIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSupportsCopyTo )( 
            ISupportsEvents * This,
            /* [in] */ SupportIndexType from,
            /* [in] */ SupportIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSupportsReverse )( 
            ISupportsEvents * This);
        
        END_INTERFACE
    } ISupportsEventsVtbl;

    interface ISupportsEvents
    {
        CONST_VTBL struct ISupportsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupportsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupportsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupportsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupportsEvents_OnSupportsChanged(This,Support,stage,change)	\
    ( (This)->lpVtbl -> OnSupportsChanged(This,Support,stage,change) ) 

#define ISupportsEvents_OnSupportsAdded(This,Support,index)	\
    ( (This)->lpVtbl -> OnSupportsAdded(This,Support,index) ) 

#define ISupportsEvents_OnSupportsBeforeRemove(This,Support,index)	\
    ( (This)->lpVtbl -> OnSupportsBeforeRemove(This,Support,index) ) 

#define ISupportsEvents_OnSupportsMoveTo(This,from,to)	\
    ( (This)->lpVtbl -> OnSupportsMoveTo(This,from,to) ) 

#define ISupportsEvents_OnSupportsCopyTo(This,from,to)	\
    ( (This)->lpVtbl -> OnSupportsCopyTo(This,from,to) ) 

#define ISupportsEvents_OnSupportsReverse(This)	\
    ( (This)->lpVtbl -> OnSupportsReverse(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupportsEvents_INTERFACE_DEFINED__ */


#ifndef __ITemporarySupportEvents_INTERFACE_DEFINED__
#define __ITemporarySupportEvents_INTERFACE_DEFINED__

/* interface ITemporarySupportEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ITemporarySupportEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EA251D3D-82BB-11d5-B03C-00105A9AF985")
    ITemporarySupportEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemporarySupportChanged( 
            /* [in] */ ITemporarySupport *TemporarySupport,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemporarySupportEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemporarySupportEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemporarySupportEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemporarySupportEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemporarySupportChanged )( 
            ITemporarySupportEvents * This,
            /* [in] */ ITemporarySupport *TemporarySupport,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change);
        
        END_INTERFACE
    } ITemporarySupportEventsVtbl;

    interface ITemporarySupportEvents
    {
        CONST_VTBL struct ITemporarySupportEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemporarySupportEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemporarySupportEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemporarySupportEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemporarySupportEvents_OnTemporarySupportChanged(This,TemporarySupport,stage,change)	\
    ( (This)->lpVtbl -> OnTemporarySupportChanged(This,TemporarySupport,stage,change) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemporarySupportEvents_INTERFACE_DEFINED__ */


#ifndef __ITemporarySupportsEvents_INTERFACE_DEFINED__
#define __ITemporarySupportsEvents_INTERFACE_DEFINED__

/* interface ITemporarySupportsEvents */
/* [object][helpstring][helpcontext][uuid] */ 


EXTERN_C const IID IID_ITemporarySupportsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BA6F5314-85BD-11D5-B040-00105A9AF985")
    ITemporarySupportsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemporarySupportsChanged( 
            /* [in] */ ITemporarySupport *Support,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemporarySupportsAdded( 
            /* [in] */ ITemporarySupport *Support,
            /* [in] */ SupportIndexType Index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemporarySupportsBeforeRemove( 
            /* [in] */ ITemporarySupport *Support,
            /* [in] */ SupportIndexType Index) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemporarySupportsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemporarySupportsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemporarySupportsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemporarySupportsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemporarySupportsChanged )( 
            ITemporarySupportsEvents * This,
            /* [in] */ ITemporarySupport *Support,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemporarySupportsAdded )( 
            ITemporarySupportsEvents * This,
            /* [in] */ ITemporarySupport *Support,
            /* [in] */ SupportIndexType Index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemporarySupportsBeforeRemove )( 
            ITemporarySupportsEvents * This,
            /* [in] */ ITemporarySupport *Support,
            /* [in] */ SupportIndexType Index);
        
        END_INTERFACE
    } ITemporarySupportsEventsVtbl;

    interface ITemporarySupportsEvents
    {
        CONST_VTBL struct ITemporarySupportsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemporarySupportsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemporarySupportsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemporarySupportsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemporarySupportsEvents_OnTemporarySupportsChanged(This,Support,stage,change)	\
    ( (This)->lpVtbl -> OnTemporarySupportsChanged(This,Support,stage,change) ) 

#define ITemporarySupportsEvents_OnTemporarySupportsAdded(This,Support,Index)	\
    ( (This)->lpVtbl -> OnTemporarySupportsAdded(This,Support,Index) ) 

#define ITemporarySupportsEvents_OnTemporarySupportsBeforeRemove(This,Support,Index)	\
    ( (This)->lpVtbl -> OnTemporarySupportsBeforeRemove(This,Support,Index) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemporarySupportsEvents_INTERFACE_DEFINED__ */


#ifndef __ISpanEvents_INTERFACE_DEFINED__
#define __ISpanEvents_INTERFACE_DEFINED__

/* interface ISpanEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISpanEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E90F6CC-85DD-11d5-B040-00105A9AF985")
    ISpanEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSpanChanged( 
            /* [in] */ ISpan *Span,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISpanEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpanEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpanEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpanEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSpanChanged )( 
            ISpanEvents * This,
            /* [in] */ ISpan *Span,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change);
        
        END_INTERFACE
    } ISpanEventsVtbl;

    interface ISpanEvents
    {
        CONST_VTBL struct ISpanEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpanEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISpanEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISpanEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISpanEvents_OnSpanChanged(This,Span,stage,change)	\
    ( (This)->lpVtbl -> OnSpanChanged(This,Span,stage,change) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISpanEvents_INTERFACE_DEFINED__ */


#ifndef __ISpansEvents_INTERFACE_DEFINED__
#define __ISpansEvents_INTERFACE_DEFINED__

/* interface ISpansEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISpansEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E90F6CF-85DD-11d5-B040-00105A9AF985")
    ISpansEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSpansChanged( 
            /* [in] */ ISpan *Span,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSpansAdded( 
            /* [in] */ ISpan *Span,
            /* [in] */ SpanIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSpansBeforeRemove( 
            /* [in] */ ISpan *Span,
            /* [in] */ SpanIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSpansMoveTo( 
            /* [in] */ SpanIndexType from,
            /* [in] */ SpanIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSpansCopyTo( 
            /* [in] */ SpanIndexType from,
            /* [in] */ SpanIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSpansReverse( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISpansEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpansEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpansEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpansEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSpansChanged )( 
            ISpansEvents * This,
            /* [in] */ ISpan *Span,
            /* [in] */ BSTR stage,
            /* [in] */ ChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSpansAdded )( 
            ISpansEvents * This,
            /* [in] */ ISpan *Span,
            /* [in] */ SpanIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSpansBeforeRemove )( 
            ISpansEvents * This,
            /* [in] */ ISpan *Span,
            /* [in] */ SpanIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSpansMoveTo )( 
            ISpansEvents * This,
            /* [in] */ SpanIndexType from,
            /* [in] */ SpanIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSpansCopyTo )( 
            ISpansEvents * This,
            /* [in] */ SpanIndexType from,
            /* [in] */ SpanIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSpansReverse )( 
            ISpansEvents * This);
        
        END_INTERFACE
    } ISpansEventsVtbl;

    interface ISpansEvents
    {
        CONST_VTBL struct ISpansEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpansEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISpansEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISpansEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISpansEvents_OnSpansChanged(This,Span,stage,change)	\
    ( (This)->lpVtbl -> OnSpansChanged(This,Span,stage,change) ) 

#define ISpansEvents_OnSpansAdded(This,Span,index)	\
    ( (This)->lpVtbl -> OnSpansAdded(This,Span,index) ) 

#define ISpansEvents_OnSpansBeforeRemove(This,Span,index)	\
    ( (This)->lpVtbl -> OnSpansBeforeRemove(This,Span,index) ) 

#define ISpansEvents_OnSpansMoveTo(This,from,to)	\
    ( (This)->lpVtbl -> OnSpansMoveTo(This,from,to) ) 

#define ISpansEvents_OnSpansCopyTo(This,from,to)	\
    ( (This)->lpVtbl -> OnSpansCopyTo(This,from,to) ) 

#define ISpansEvents_OnSpansReverse(This)	\
    ( (This)->lpVtbl -> OnSpansReverse(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISpansEvents_INTERFACE_DEFINED__ */


#ifndef __IPOIStressPointsEvents_INTERFACE_DEFINED__
#define __IPOIStressPointsEvents_INTERFACE_DEFINED__

/* interface IPOIStressPointsEvents */
/* [helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IPOIStressPointsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F361A3F1-1EDA-4404-9980-23BFA0F6CEB8")
    IPOIStressPointsEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnPOIStressPointsChanged( 
            /* [in] */ IPOIStressPoints *load) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnPOIStressPointsAdded( 
            /* [in] */ IPOIStressPointsItem *load) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnPOIStressPointsBeforeRemove( 
            /* [in] */ IPOIStressPointsItem *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPOIStressPointsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPOIStressPointsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPOIStressPointsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPOIStressPointsEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPOIStressPointsChanged )( 
            IPOIStressPointsEvents * This,
            /* [in] */ IPOIStressPoints *load);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPOIStressPointsAdded )( 
            IPOIStressPointsEvents * This,
            /* [in] */ IPOIStressPointsItem *load);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPOIStressPointsBeforeRemove )( 
            IPOIStressPointsEvents * This,
            /* [in] */ IPOIStressPointsItem *load);
        
        END_INTERFACE
    } IPOIStressPointsEventsVtbl;

    interface IPOIStressPointsEvents
    {
        CONST_VTBL struct IPOIStressPointsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPOIStressPointsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPOIStressPointsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPOIStressPointsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPOIStressPointsEvents_OnPOIStressPointsChanged(This,load)	\
    ( (This)->lpVtbl -> OnPOIStressPointsChanged(This,load) ) 

#define IPOIStressPointsEvents_OnPOIStressPointsAdded(This,load)	\
    ( (This)->lpVtbl -> OnPOIStressPointsAdded(This,load) ) 

#define IPOIStressPointsEvents_OnPOIStressPointsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnPOIStressPointsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPOIStressPointsEvents_INTERFACE_DEFINED__ */


#ifndef __IPOIEvents_INTERFACE_DEFINED__
#define __IPOIEvents_INTERFACE_DEFINED__

/* interface IPOIEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IPOIEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E79D58E4-8826-11d5-B043-00105A9AF985")
    IPOIEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPOIChanged( 
            /* [in] */ IPOI *me,
            /* [in] */ ChangeType type) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPOIRenamed( 
            /* [in] */ PoiIDType oldID,
            /* [in] */ PoiIDType newID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPOIEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPOIEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPOIEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPOIEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPOIChanged )( 
            IPOIEvents * This,
            /* [in] */ IPOI *me,
            /* [in] */ ChangeType type);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPOIRenamed )( 
            IPOIEvents * This,
            /* [in] */ PoiIDType oldID,
            /* [in] */ PoiIDType newID);
        
        END_INTERFACE
    } IPOIEventsVtbl;

    interface IPOIEvents
    {
        CONST_VTBL struct IPOIEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPOIEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPOIEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPOIEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPOIEvents_OnPOIChanged(This,me,type)	\
    ( (This)->lpVtbl -> OnPOIChanged(This,me,type) ) 

#define IPOIEvents_OnPOIRenamed(This,oldID,newID)	\
    ( (This)->lpVtbl -> OnPOIRenamed(This,oldID,newID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPOIEvents_INTERFACE_DEFINED__ */


#ifndef __IPOIsEvents_INTERFACE_DEFINED__
#define __IPOIsEvents_INTERFACE_DEFINED__

/* interface IPOIsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IPOIsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E79D58E7-8826-11d5-B043-00105A9AF985")
    IPOIsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPOIsChanged( 
            /* [in] */ IPOI *poi,
            ChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPOIsRenamed( 
            /* [in] */ PoiIDType oldID,
            /* [in] */ PoiIDType newID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPOIsAdded( 
            /* [in] */ IPOI *poi) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPOIsBeforeRemove( 
            /* [in] */ IPOI *poi) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPOIsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPOIsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPOIsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPOIsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPOIsChanged )( 
            IPOIsEvents * This,
            /* [in] */ IPOI *poi,
            ChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPOIsRenamed )( 
            IPOIsEvents * This,
            /* [in] */ PoiIDType oldID,
            /* [in] */ PoiIDType newID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPOIsAdded )( 
            IPOIsEvents * This,
            /* [in] */ IPOI *poi);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPOIsBeforeRemove )( 
            IPOIsEvents * This,
            /* [in] */ IPOI *poi);
        
        END_INTERFACE
    } IPOIsEventsVtbl;

    interface IPOIsEvents
    {
        CONST_VTBL struct IPOIsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPOIsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPOIsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPOIsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPOIsEvents_OnPOIsChanged(This,poi,change)	\
    ( (This)->lpVtbl -> OnPOIsChanged(This,poi,change) ) 

#define IPOIsEvents_OnPOIsRenamed(This,oldID,newID)	\
    ( (This)->lpVtbl -> OnPOIsRenamed(This,oldID,newID) ) 

#define IPOIsEvents_OnPOIsAdded(This,poi)	\
    ( (This)->lpVtbl -> OnPOIsAdded(This,poi) ) 

#define IPOIsEvents_OnPOIsBeforeRemove(This,poi)	\
    ( (This)->lpVtbl -> OnPOIsBeforeRemove(This,poi) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPOIsEvents_INTERFACE_DEFINED__ */


#ifndef __IStageEvents_INTERFACE_DEFINED__
#define __IStageEvents_INTERFACE_DEFINED__

/* interface IStageEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStageEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0D3B791E-8DD9-11d5-B048-00105A9AF985")
    IStageEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStageChanged( 
            /* [in] */ IStage *me,
            /* [in] */ ChangeType type) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStageEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStageEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStageEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStageEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStageChanged )( 
            IStageEvents * This,
            /* [in] */ IStage *me,
            /* [in] */ ChangeType type);
        
        END_INTERFACE
    } IStageEventsVtbl;

    interface IStageEvents
    {
        CONST_VTBL struct IStageEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStageEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStageEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStageEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStageEvents_OnStageChanged(This,me,type)	\
    ( (This)->lpVtbl -> OnStageChanged(This,me,type) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStageEvents_INTERFACE_DEFINED__ */


#ifndef __IStagesEvents_INTERFACE_DEFINED__
#define __IStagesEvents_INTERFACE_DEFINED__

/* interface IStagesEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStagesEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0D3B7920-8DD9-11d5-B048-00105A9AF985")
    IStagesEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStagesChanged( 
            /* [in] */ IStage *Stage,
            /* [in] */ ChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStagesAdded( 
            /* [in] */ IStage *Stage,
            /* [in] */ StageIndexType relPos) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStagesBeforeRemove( 
            /* [in] */ IStage *Stage,
            /* [in] */ StageIndexType relPos) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStagesMoveTo( 
            /* [in] */ StageIndexType from,
            /* [in] */ StageIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStagesCopyTo( 
            /* [in] */ StageIndexType from,
            /* [in] */ StageIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStagesReverse( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStagesEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStagesEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStagesEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStagesEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStagesChanged )( 
            IStagesEvents * This,
            /* [in] */ IStage *Stage,
            /* [in] */ ChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStagesAdded )( 
            IStagesEvents * This,
            /* [in] */ IStage *Stage,
            /* [in] */ StageIndexType relPos);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStagesBeforeRemove )( 
            IStagesEvents * This,
            /* [in] */ IStage *Stage,
            /* [in] */ StageIndexType relPos);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStagesMoveTo )( 
            IStagesEvents * This,
            /* [in] */ StageIndexType from,
            /* [in] */ StageIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStagesCopyTo )( 
            IStagesEvents * This,
            /* [in] */ StageIndexType from,
            /* [in] */ StageIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStagesReverse )( 
            IStagesEvents * This);
        
        END_INTERFACE
    } IStagesEventsVtbl;

    interface IStagesEvents
    {
        CONST_VTBL struct IStagesEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStagesEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStagesEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStagesEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStagesEvents_OnStagesChanged(This,Stage,change)	\
    ( (This)->lpVtbl -> OnStagesChanged(This,Stage,change) ) 

#define IStagesEvents_OnStagesAdded(This,Stage,relPos)	\
    ( (This)->lpVtbl -> OnStagesAdded(This,Stage,relPos) ) 

#define IStagesEvents_OnStagesBeforeRemove(This,Stage,relPos)	\
    ( (This)->lpVtbl -> OnStagesBeforeRemove(This,Stage,relPos) ) 

#define IStagesEvents_OnStagesMoveTo(This,from,to)	\
    ( (This)->lpVtbl -> OnStagesMoveTo(This,from,to) ) 

#define IStagesEvents_OnStagesCopyTo(This,from,to)	\
    ( (This)->lpVtbl -> OnStagesCopyTo(This,from,to) ) 

#define IStagesEvents_OnStagesReverse(This)	\
    ( (This)->lpVtbl -> OnStagesReverse(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStagesEvents_INTERFACE_DEFINED__ */


#ifndef __IPointLoadEvents_INTERFACE_DEFINED__
#define __IPointLoadEvents_INTERFACE_DEFINED__

/* interface IPointLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IPointLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7B3D50AF-90C2-11d5-B04B-00105A9AF985")
    IPointLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointLoadChanged( 
            /* [in] */ IPointLoad *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPointLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointLoadChanged )( 
            IPointLoadEvents * This,
            /* [in] */ IPointLoad *me);
        
        END_INTERFACE
    } IPointLoadEventsVtbl;

    interface IPointLoadEvents
    {
        CONST_VTBL struct IPointLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPointLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPointLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPointLoadEvents_OnPointLoadChanged(This,me)	\
    ( (This)->lpVtbl -> OnPointLoadChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPointLoadEvents_INTERFACE_DEFINED__ */


#ifndef __IPointLoadsEvents_INTERFACE_DEFINED__
#define __IPointLoadsEvents_INTERFACE_DEFINED__

/* interface IPointLoadsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IPointLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7B3D50B3-90C2-11d5-B04B-00105A9AF985")
    IPointLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointLoadsChanged( 
            /* [in] */ IPointLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointLoadsAdded( 
            /* [in] */ IPointLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointLoadsBeforeRemove( 
            /* [in] */ IPointLoadItem *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPointLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointLoadsChanged )( 
            IPointLoadsEvents * This,
            /* [in] */ IPointLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointLoadsAdded )( 
            IPointLoadsEvents * This,
            /* [in] */ IPointLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointLoadsBeforeRemove )( 
            IPointLoadsEvents * This,
            /* [in] */ IPointLoadItem *load);
        
        END_INTERFACE
    } IPointLoadsEventsVtbl;

    interface IPointLoadsEvents
    {
        CONST_VTBL struct IPointLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPointLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPointLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPointLoadsEvents_OnPointLoadsChanged(This,load)	\
    ( (This)->lpVtbl -> OnPointLoadsChanged(This,load) ) 

#define IPointLoadsEvents_OnPointLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnPointLoadsAdded(This,load) ) 

#define IPointLoadsEvents_OnPointLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnPointLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPointLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __IDistributedLoadEvents_INTERFACE_DEFINED__
#define __IDistributedLoadEvents_INTERFACE_DEFINED__

/* interface IDistributedLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IDistributedLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CCB1AF43-9267-11d5-B04D-00105A9AF985")
    IDistributedLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributedLoadChanged( 
            /* [in] */ IDistributedLoad *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributedLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributedLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributedLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributedLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributedLoadChanged )( 
            IDistributedLoadEvents * This,
            /* [in] */ IDistributedLoad *me);
        
        END_INTERFACE
    } IDistributedLoadEventsVtbl;

    interface IDistributedLoadEvents
    {
        CONST_VTBL struct IDistributedLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributedLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributedLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributedLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributedLoadEvents_OnDistributedLoadChanged(This,me)	\
    ( (This)->lpVtbl -> OnDistributedLoadChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributedLoadEvents_INTERFACE_DEFINED__ */


#ifndef __IDistributedLoadsEvents_INTERFACE_DEFINED__
#define __IDistributedLoadsEvents_INTERFACE_DEFINED__

/* interface IDistributedLoadsEvents */
/* [helpcontext][helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IDistributedLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CCB1AF45-9267-11d5-B04D-00105A9AF985")
    IDistributedLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributedLoadsChanged( 
            /* [in] */ IDistributedLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributedLoadsAdded( 
            /* [in] */ IDistributedLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributedLoadsBeforeRemove( 
            /* [in] */ IDistributedLoadItem *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributedLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributedLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributedLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributedLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributedLoadsChanged )( 
            IDistributedLoadsEvents * This,
            /* [in] */ IDistributedLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributedLoadsAdded )( 
            IDistributedLoadsEvents * This,
            /* [in] */ IDistributedLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributedLoadsBeforeRemove )( 
            IDistributedLoadsEvents * This,
            /* [in] */ IDistributedLoadItem *load);
        
        END_INTERFACE
    } IDistributedLoadsEventsVtbl;

    interface IDistributedLoadsEvents
    {
        CONST_VTBL struct IDistributedLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributedLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributedLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributedLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributedLoadsEvents_OnDistributedLoadsChanged(This,load)	\
    ( (This)->lpVtbl -> OnDistributedLoadsChanged(This,load) ) 

#define IDistributedLoadsEvents_OnDistributedLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnDistributedLoadsAdded(This,load) ) 

#define IDistributedLoadsEvents_OnDistributedLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnDistributedLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributedLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __ISettlementLoadEvents_INTERFACE_DEFINED__
#define __ISettlementLoadEvents_INTERFACE_DEFINED__

/* interface ISettlementLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISettlementLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D133939C-9326-11d5-B04E-00105A9AF985")
    ISettlementLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSettlementLoadChanged( 
            /* [in] */ ISettlementLoad *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISettlementLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISettlementLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISettlementLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISettlementLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSettlementLoadChanged )( 
            ISettlementLoadEvents * This,
            /* [in] */ ISettlementLoad *me);
        
        END_INTERFACE
    } ISettlementLoadEventsVtbl;

    interface ISettlementLoadEvents
    {
        CONST_VTBL struct ISettlementLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISettlementLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISettlementLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISettlementLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISettlementLoadEvents_OnSettlementLoadChanged(This,me)	\
    ( (This)->lpVtbl -> OnSettlementLoadChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISettlementLoadEvents_INTERFACE_DEFINED__ */


#ifndef __ISettlementLoadsEvents_INTERFACE_DEFINED__
#define __ISettlementLoadsEvents_INTERFACE_DEFINED__

/* interface ISettlementLoadsEvents */
/* [helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ISettlementLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D133939E-9326-11d5-B04E-00105A9AF985")
    ISettlementLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSettlementLoadsChanged( 
            /* [in] */ ISettlementLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSettlementLoadsAdded( 
            /* [in] */ ISettlementLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSettlementLoadsBeforeRemove( 
            /* [in] */ ISettlementLoadItem *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISettlementLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISettlementLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISettlementLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISettlementLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSettlementLoadsChanged )( 
            ISettlementLoadsEvents * This,
            /* [in] */ ISettlementLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSettlementLoadsAdded )( 
            ISettlementLoadsEvents * This,
            /* [in] */ ISettlementLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSettlementLoadsBeforeRemove )( 
            ISettlementLoadsEvents * This,
            /* [in] */ ISettlementLoadItem *load);
        
        END_INTERFACE
    } ISettlementLoadsEventsVtbl;

    interface ISettlementLoadsEvents
    {
        CONST_VTBL struct ISettlementLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISettlementLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISettlementLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISettlementLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISettlementLoadsEvents_OnSettlementLoadsChanged(This,load)	\
    ( (This)->lpVtbl -> OnSettlementLoadsChanged(This,load) ) 

#define ISettlementLoadsEvents_OnSettlementLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnSettlementLoadsAdded(This,load) ) 

#define ISettlementLoadsEvents_OnSettlementLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnSettlementLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISettlementLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __ITemperatureLoadEvents_INTERFACE_DEFINED__
#define __ITemperatureLoadEvents_INTERFACE_DEFINED__

/* interface ITemperatureLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ITemperatureLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D13393A2-9326-11d5-B04E-00105A9AF985")
    ITemperatureLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemperatureLoadChanged( 
            /* [in] */ ITemperatureLoad *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemperatureLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemperatureLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemperatureLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemperatureLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemperatureLoadChanged )( 
            ITemperatureLoadEvents * This,
            /* [in] */ ITemperatureLoad *me);
        
        END_INTERFACE
    } ITemperatureLoadEventsVtbl;

    interface ITemperatureLoadEvents
    {
        CONST_VTBL struct ITemperatureLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemperatureLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemperatureLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemperatureLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemperatureLoadEvents_OnTemperatureLoadChanged(This,me)	\
    ( (This)->lpVtbl -> OnTemperatureLoadChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemperatureLoadEvents_INTERFACE_DEFINED__ */


#ifndef __ITemperatureLoadsEvents_INTERFACE_DEFINED__
#define __ITemperatureLoadsEvents_INTERFACE_DEFINED__

/* interface ITemperatureLoadsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ITemperatureLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D13393A4-9326-11d5-B04E-00105A9AF985")
    ITemperatureLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemperatureLoadsChanged( 
            /* [in] */ ITemperatureLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemperatureLoadsAdded( 
            /* [in] */ ITemperatureLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemperatureLoadsBeforeRemove( 
            /* [in] */ ITemperatureLoadItem *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITemperatureLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITemperatureLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITemperatureLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITemperatureLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemperatureLoadsChanged )( 
            ITemperatureLoadsEvents * This,
            /* [in] */ ITemperatureLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemperatureLoadsAdded )( 
            ITemperatureLoadsEvents * This,
            /* [in] */ ITemperatureLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemperatureLoadsBeforeRemove )( 
            ITemperatureLoadsEvents * This,
            /* [in] */ ITemperatureLoadItem *load);
        
        END_INTERFACE
    } ITemperatureLoadsEventsVtbl;

    interface ITemperatureLoadsEvents
    {
        CONST_VTBL struct ITemperatureLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITemperatureLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITemperatureLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITemperatureLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITemperatureLoadsEvents_OnTemperatureLoadsChanged(This,load)	\
    ( (This)->lpVtbl -> OnTemperatureLoadsChanged(This,load) ) 

#define ITemperatureLoadsEvents_OnTemperatureLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnTemperatureLoadsAdded(This,load) ) 

#define ITemperatureLoadsEvents_OnTemperatureLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnTemperatureLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITemperatureLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __IStrainLoadEvents_INTERFACE_DEFINED__
#define __IStrainLoadEvents_INTERFACE_DEFINED__

/* interface IStrainLoadEvents */
/* [helpstring][unique][helpcontext][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStrainLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A085C664-958F-11d5-B050-00105A9AF985")
    IStrainLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStrainLoadChanged( 
            /* [in] */ IStrainLoad *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStrainLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStrainLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStrainLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStrainLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStrainLoadChanged )( 
            IStrainLoadEvents * This,
            /* [in] */ IStrainLoad *me);
        
        END_INTERFACE
    } IStrainLoadEventsVtbl;

    interface IStrainLoadEvents
    {
        CONST_VTBL struct IStrainLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrainLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStrainLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStrainLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStrainLoadEvents_OnStrainLoadChanged(This,me)	\
    ( (This)->lpVtbl -> OnStrainLoadChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrainLoadEvents_INTERFACE_DEFINED__ */


#ifndef __IStrainLoadsEvents_INTERFACE_DEFINED__
#define __IStrainLoadsEvents_INTERFACE_DEFINED__

/* interface IStrainLoadsEvents */
/* [helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IStrainLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A085C662-958F-11d5-B050-00105A9AF985")
    IStrainLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStrainLoadsChanged( 
            /* [in] */ IStrainLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStrainLoadsAdded( 
            /* [in] */ IStrainLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStrainLoadsBeforeRemove( 
            /* [in] */ IStrainLoadItem *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStrainLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStrainLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStrainLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStrainLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStrainLoadsChanged )( 
            IStrainLoadsEvents * This,
            /* [in] */ IStrainLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStrainLoadsAdded )( 
            IStrainLoadsEvents * This,
            /* [in] */ IStrainLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStrainLoadsBeforeRemove )( 
            IStrainLoadsEvents * This,
            /* [in] */ IStrainLoadItem *load);
        
        END_INTERFACE
    } IStrainLoadsEventsVtbl;

    interface IStrainLoadsEvents
    {
        CONST_VTBL struct IStrainLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrainLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStrainLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStrainLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStrainLoadsEvents_OnStrainLoadsChanged(This,load)	\
    ( (This)->lpVtbl -> OnStrainLoadsChanged(This,load) ) 

#define IStrainLoadsEvents_OnStrainLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnStrainLoadsAdded(This,load) ) 

#define IStrainLoadsEvents_OnStrainLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnStrainLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrainLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __ILoadGroupEvents_INTERFACE_DEFINED__
#define __ILoadGroupEvents_INTERFACE_DEFINED__

/* interface ILoadGroupEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILoadGroupEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("52DAF0E4-95B3-11d5-B050-00105A9AF985")
    ILoadGroupEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupChanged( 
            /* [in] */ ILoadGroup *me,
            /* [in] */ ChangeType type) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadGroupEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadGroupEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadGroupEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadGroupEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupChanged )( 
            ILoadGroupEvents * This,
            /* [in] */ ILoadGroup *me,
            /* [in] */ ChangeType type);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupRenamed )( 
            ILoadGroupEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        END_INTERFACE
    } ILoadGroupEventsVtbl;

    interface ILoadGroupEvents
    {
        CONST_VTBL struct ILoadGroupEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadGroupEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadGroupEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadGroupEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadGroupEvents_OnLoadGroupChanged(This,me,type)	\
    ( (This)->lpVtbl -> OnLoadGroupChanged(This,me,type) ) 

#define ILoadGroupEvents_OnLoadGroupRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadGroupRenamed(This,oldName,newName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadGroupEvents_INTERFACE_DEFINED__ */


#ifndef __ILoadGroupsEvents_INTERFACE_DEFINED__
#define __ILoadGroupsEvents_INTERFACE_DEFINED__

/* interface ILoadGroupsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILoadGroupsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("52DAF0E6-95B3-11d5-B050-00105A9AF985")
    ILoadGroupsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupsChanged( 
            /* [in] */ ILoadGroup *load,
            /* [in] */ ChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupsRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupsAdded( 
            /* [in] */ ILoadGroup *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupsBeforeRemove( 
            /* [in] */ ILoadGroup *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadGroupsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadGroupsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadGroupsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadGroupsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupsChanged )( 
            ILoadGroupsEvents * This,
            /* [in] */ ILoadGroup *load,
            /* [in] */ ChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupsRenamed )( 
            ILoadGroupsEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupsAdded )( 
            ILoadGroupsEvents * This,
            /* [in] */ ILoadGroup *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupsBeforeRemove )( 
            ILoadGroupsEvents * This,
            /* [in] */ ILoadGroup *load);
        
        END_INTERFACE
    } ILoadGroupsEventsVtbl;

    interface ILoadGroupsEvents
    {
        CONST_VTBL struct ILoadGroupsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadGroupsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadGroupsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadGroupsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadGroupsEvents_OnLoadGroupsChanged(This,load,change)	\
    ( (This)->lpVtbl -> OnLoadGroupsChanged(This,load,change) ) 

#define ILoadGroupsEvents_OnLoadGroupsRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadGroupsRenamed(This,oldName,newName) ) 

#define ILoadGroupsEvents_OnLoadGroupsAdded(This,load)	\
    ( (This)->lpVtbl -> OnLoadGroupsAdded(This,load) ) 

#define ILoadGroupsEvents_OnLoadGroupsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnLoadGroupsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadGroupsEvents_INTERFACE_DEFINED__ */


#ifndef __ILoadCaseEvents_INTERFACE_DEFINED__
#define __ILoadCaseEvents_INTERFACE_DEFINED__

/* interface ILoadCaseEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILoadCaseEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("420F2FB5-3F5B-4105-936D-1FE7AC729713")
    ILoadCaseEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCaseChanged( 
            /* [in] */ ILoadCase *me,
            /* [in] */ ChangeType type) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCaseRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCaseEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCaseEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCaseEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCaseEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCaseChanged )( 
            ILoadCaseEvents * This,
            /* [in] */ ILoadCase *me,
            /* [in] */ ChangeType type);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCaseRenamed )( 
            ILoadCaseEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        END_INTERFACE
    } ILoadCaseEventsVtbl;

    interface ILoadCaseEvents
    {
        CONST_VTBL struct ILoadCaseEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCaseEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCaseEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCaseEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCaseEvents_OnLoadCaseChanged(This,me,type)	\
    ( (This)->lpVtbl -> OnLoadCaseChanged(This,me,type) ) 

#define ILoadCaseEvents_OnLoadCaseRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadCaseRenamed(This,oldName,newName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCaseEvents_INTERFACE_DEFINED__ */


#ifndef __ILoadCasesEvents_INTERFACE_DEFINED__
#define __ILoadCasesEvents_INTERFACE_DEFINED__

/* interface ILoadCasesEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILoadCasesEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("72A24955-7F6A-4437-9E35-DA3DB77149B6")
    ILoadCasesEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCasesChanged( 
            /* [in] */ ILoadCase *load,
            /* [in] */ ChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCasesRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCasesAdded( 
            /* [in] */ ILoadCase *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCasesBeforeRemove( 
            /* [in] */ ILoadCase *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCasesEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCasesEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCasesEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCasesEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCasesChanged )( 
            ILoadCasesEvents * This,
            /* [in] */ ILoadCase *load,
            /* [in] */ ChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCasesRenamed )( 
            ILoadCasesEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCasesAdded )( 
            ILoadCasesEvents * This,
            /* [in] */ ILoadCase *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCasesBeforeRemove )( 
            ILoadCasesEvents * This,
            /* [in] */ ILoadCase *load);
        
        END_INTERFACE
    } ILoadCasesEventsVtbl;

    interface ILoadCasesEvents
    {
        CONST_VTBL struct ILoadCasesEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCasesEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCasesEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCasesEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCasesEvents_OnLoadCasesChanged(This,load,change)	\
    ( (This)->lpVtbl -> OnLoadCasesChanged(This,load,change) ) 

#define ILoadCasesEvents_OnLoadCasesRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadCasesRenamed(This,oldName,newName) ) 

#define ILoadCasesEvents_OnLoadCasesAdded(This,load)	\
    ( (This)->lpVtbl -> OnLoadCasesAdded(This,load) ) 

#define ILoadCasesEvents_OnLoadCasesBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnLoadCasesBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCasesEvents_INTERFACE_DEFINED__ */


#ifndef __ILoadCombinationEvents_INTERFACE_DEFINED__
#define __ILoadCombinationEvents_INTERFACE_DEFINED__

/* interface ILoadCombinationEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILoadCombinationEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2ADA1042-A225-4c59-8B0B-A7228397008B")
    ILoadCombinationEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationChanged( 
            /* [in] */ ILoadCombination *me,
            /* [in] */ ChangeType type) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombinationEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombinationEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombinationEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationChanged )( 
            ILoadCombinationEvents * This,
            /* [in] */ ILoadCombination *me,
            /* [in] */ ChangeType type);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationRenamed )( 
            ILoadCombinationEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        END_INTERFACE
    } ILoadCombinationEventsVtbl;

    interface ILoadCombinationEvents
    {
        CONST_VTBL struct ILoadCombinationEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombinationEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombinationEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombinationEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombinationEvents_OnLoadCombinationChanged(This,me,type)	\
    ( (This)->lpVtbl -> OnLoadCombinationChanged(This,me,type) ) 

#define ILoadCombinationEvents_OnLoadCombinationRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadCombinationRenamed(This,oldName,newName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombinationEvents_INTERFACE_DEFINED__ */


#ifndef __ILoadCombinationsEvents_INTERFACE_DEFINED__
#define __ILoadCombinationsEvents_INTERFACE_DEFINED__

/* interface ILoadCombinationsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ILoadCombinationsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("725290C3-BBC7-4865-B5D8-04D70117EE42")
    ILoadCombinationsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationsChanged( 
            /* [in] */ ILoadCombination *load,
            /* [in] */ ChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationsRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationsAdded( 
            /* [in] */ ILoadCombination *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationsBeforeRemove( 
            /* [in] */ ILoadCombination *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILoadCombinationsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadCombinationsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadCombinationsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadCombinationsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationsChanged )( 
            ILoadCombinationsEvents * This,
            /* [in] */ ILoadCombination *load,
            /* [in] */ ChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationsRenamed )( 
            ILoadCombinationsEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationsAdded )( 
            ILoadCombinationsEvents * This,
            /* [in] */ ILoadCombination *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationsBeforeRemove )( 
            ILoadCombinationsEvents * This,
            /* [in] */ ILoadCombination *load);
        
        END_INTERFACE
    } ILoadCombinationsEventsVtbl;

    interface ILoadCombinationsEvents
    {
        CONST_VTBL struct ILoadCombinationsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadCombinationsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILoadCombinationsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILoadCombinationsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILoadCombinationsEvents_OnLoadCombinationsChanged(This,load,change)	\
    ( (This)->lpVtbl -> OnLoadCombinationsChanged(This,load,change) ) 

#define ILoadCombinationsEvents_OnLoadCombinationsRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadCombinationsRenamed(This,oldName,newName) ) 

#define ILoadCombinationsEvents_OnLoadCombinationsAdded(This,load)	\
    ( (This)->lpVtbl -> OnLoadCombinationsAdded(This,load) ) 

#define ILoadCombinationsEvents_OnLoadCombinationsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnLoadCombinationsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILoadCombinationsEvents_INTERFACE_DEFINED__ */


#ifndef __IDistributionFactorEvents_INTERFACE_DEFINED__
#define __IDistributionFactorEvents_INTERFACE_DEFINED__

/* interface IDistributionFactorEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IDistributionFactorEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E79D58E2-8826-11d5-B043-00105A9AF985")
    IDistributionFactorEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributionFactorChanged( 
            /* [in] */ IDistributionFactor *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributionFactorEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributionFactorEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributionFactorEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributionFactorEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributionFactorChanged )( 
            IDistributionFactorEvents * This,
            /* [in] */ IDistributionFactor *me);
        
        END_INTERFACE
    } IDistributionFactorEventsVtbl;

    interface IDistributionFactorEvents
    {
        CONST_VTBL struct IDistributionFactorEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributionFactorEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributionFactorEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributionFactorEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributionFactorEvents_OnDistributionFactorChanged(This,me)	\
    ( (This)->lpVtbl -> OnDistributionFactorChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributionFactorEvents_INTERFACE_DEFINED__ */


#ifndef __IDistributionFactorSegmentEvents_INTERFACE_DEFINED__
#define __IDistributionFactorSegmentEvents_INTERFACE_DEFINED__

/* interface IDistributionFactorSegmentEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IDistributionFactorSegmentEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7D913A5F-E01C-4055-9FC5-E5EB9BBB4150")
    IDistributionFactorSegmentEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributionFactorSegmentChanged( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributionFactorSegmentEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributionFactorSegmentEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributionFactorSegmentEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributionFactorSegmentEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributionFactorSegmentChanged )( 
            IDistributionFactorSegmentEvents * This);
        
        END_INTERFACE
    } IDistributionFactorSegmentEventsVtbl;

    interface IDistributionFactorSegmentEvents
    {
        CONST_VTBL struct IDistributionFactorSegmentEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributionFactorSegmentEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributionFactorSegmentEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributionFactorSegmentEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributionFactorSegmentEvents_OnDistributionFactorSegmentChanged(This)	\
    ( (This)->lpVtbl -> OnDistributionFactorSegmentChanged(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributionFactorSegmentEvents_INTERFACE_DEFINED__ */


#ifndef __IDistributionFactorsEvents_INTERFACE_DEFINED__
#define __IDistributionFactorsEvents_INTERFACE_DEFINED__

/* interface IDistributionFactorsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IDistributionFactorsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("438D1A7E-79B0-498A-94D3-F0446FB4EFB9")
    IDistributionFactorsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributionFactorsChanged( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributionFactorsAdded( 
            /* [in] */ IDistributionFactorSegment *DistributionFactor,
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributionFactorsBeforeRemove( 
            /* [in] */ IDistributionFactorSegment *DistributionFactor,
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributionFactorsMoveTo( 
            /* [in] */ CollectionIndexType from,
            /* [in] */ CollectionIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributionFactorsCopyTo( 
            /* [in] */ CollectionIndexType from,
            /* [in] */ CollectionIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributionFactorsReverse( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDistributionFactorsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributionFactorsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributionFactorsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributionFactorsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributionFactorsChanged )( 
            IDistributionFactorsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributionFactorsAdded )( 
            IDistributionFactorsEvents * This,
            /* [in] */ IDistributionFactorSegment *DistributionFactor,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributionFactorsBeforeRemove )( 
            IDistributionFactorsEvents * This,
            /* [in] */ IDistributionFactorSegment *DistributionFactor,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributionFactorsMoveTo )( 
            IDistributionFactorsEvents * This,
            /* [in] */ CollectionIndexType from,
            /* [in] */ CollectionIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributionFactorsCopyTo )( 
            IDistributionFactorsEvents * This,
            /* [in] */ CollectionIndexType from,
            /* [in] */ CollectionIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributionFactorsReverse )( 
            IDistributionFactorsEvents * This);
        
        END_INTERFACE
    } IDistributionFactorsEventsVtbl;

    interface IDistributionFactorsEvents
    {
        CONST_VTBL struct IDistributionFactorsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributionFactorsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDistributionFactorsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDistributionFactorsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDistributionFactorsEvents_OnDistributionFactorsChanged(This)	\
    ( (This)->lpVtbl -> OnDistributionFactorsChanged(This) ) 

#define IDistributionFactorsEvents_OnDistributionFactorsAdded(This,DistributionFactor,idx)	\
    ( (This)->lpVtbl -> OnDistributionFactorsAdded(This,DistributionFactor,idx) ) 

#define IDistributionFactorsEvents_OnDistributionFactorsBeforeRemove(This,DistributionFactor,idx)	\
    ( (This)->lpVtbl -> OnDistributionFactorsBeforeRemove(This,DistributionFactor,idx) ) 

#define IDistributionFactorsEvents_OnDistributionFactorsMoveTo(This,from,to)	\
    ( (This)->lpVtbl -> OnDistributionFactorsMoveTo(This,from,to) ) 

#define IDistributionFactorsEvents_OnDistributionFactorsCopyTo(This,from,to)	\
    ( (This)->lpVtbl -> OnDistributionFactorsCopyTo(This,from,to) ) 

#define IDistributionFactorsEvents_OnDistributionFactorsReverse(This)	\
    ( (This)->lpVtbl -> OnDistributionFactorsReverse(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDistributionFactorsEvents_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_StressPoint;

#ifdef __cplusplus

class DECLSPEC_UUID("A60E8526-3A65-11D5-AFE5-00105A9AF985")
StressPoint;
#endif

EXTERN_C const CLSID CLSID_StressPoints;

#ifdef __cplusplus

class DECLSPEC_UUID("A60E8529-3A65-11D5-AFE5-00105A9AF985")
StressPoints;
#endif

EXTERN_C const CLSID CLSID_SegmentCrossSection;

#ifdef __cplusplus

class DECLSPEC_UUID("1E602C36-2A98-11D5-AFCE-00105A9AF985")
SegmentCrossSection;
#endif

EXTERN_C const CLSID CLSID_Segment;

#ifdef __cplusplus

class DECLSPEC_UUID("21C1BB08-7799-11D5-B02F-00105A9AF985")
Segment;
#endif

EXTERN_C const CLSID CLSID_SegmentItem;

#ifdef __cplusplus

class DECLSPEC_UUID("21C1BB0E-7799-11D5-B02F-00105A9AF985")
SegmentItem;
#endif

EXTERN_C const CLSID CLSID_FilteredSegmentCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("222A9652-7B89-11D5-B035-00105A9AF985")
FilteredSegmentCollection;
#endif

EXTERN_C const CLSID CLSID_SuperstructureMember;

#ifdef __cplusplus

class DECLSPEC_UUID("787BE35C-7C53-11D5-B036-00105A9AF985")
SuperstructureMember;
#endif

EXTERN_C const CLSID CLSID_SuperstructureMembers;

#ifdef __cplusplus

class DECLSPEC_UUID("672A7921-7F78-11D5-B038-00105A9AF985")
SuperstructureMembers;
#endif

EXTERN_C const CLSID CLSID_LBAMModel;

#ifdef __cplusplus

class DECLSPEC_UUID("A6B18F79-803D-11D5-B039-00105A9AF985")
LBAMModel;
#endif

EXTERN_C const CLSID CLSID_Support;

#ifdef __cplusplus

class DECLSPEC_UUID("80D1B107-829D-11D5-B03C-00105A9AF985")
Support;
#endif

EXTERN_C const CLSID CLSID_Supports;

#ifdef __cplusplus

class DECLSPEC_UUID("80D1B10A-829D-11D5-B03C-00105A9AF985")
Supports;
#endif

EXTERN_C const CLSID CLSID_TemporarySupports;

#ifdef __cplusplus

class DECLSPEC_UUID("BA6F5313-85BD-11D5-B040-00105A9AF985")
TemporarySupports;
#endif

EXTERN_C const CLSID CLSID_TemporarySupport;

#ifdef __cplusplus

class DECLSPEC_UUID("80D1B10D-829D-11D5-B03C-00105A9AF985")
TemporarySupport;
#endif

EXTERN_C const CLSID CLSID_Span;

#ifdef __cplusplus

class DECLSPEC_UUID("BA6F5316-85BD-11D5-B040-00105A9AF985")
Span;
#endif

EXTERN_C const CLSID CLSID_Spans;

#ifdef __cplusplus

class DECLSPEC_UUID("BA6F531A-85BD-11D5-B040-00105A9AF985")
Spans;
#endif

EXTERN_C const CLSID CLSID_DistributionFactor;

#ifdef __cplusplus

class DECLSPEC_UUID("E6ECB214-881C-11D5-B043-00105A9AF985")
DistributionFactor;
#endif

EXTERN_C const CLSID CLSID_POI;

#ifdef __cplusplus

class DECLSPEC_UUID("E6ECB21C-881C-11D5-B043-00105A9AF985")
POI;
#endif

EXTERN_C const CLSID CLSID_POIs;

#ifdef __cplusplus

class DECLSPEC_UUID("E6ECB21F-881C-11D5-B043-00105A9AF985")
POIs;
#endif

EXTERN_C const CLSID CLSID_Stage;

#ifdef __cplusplus

class DECLSPEC_UUID("2DC09B1E-8D9A-11D5-B048-00105A9AF985")
Stage;
#endif

EXTERN_C const CLSID CLSID_Stages;

#ifdef __cplusplus

class DECLSPEC_UUID("2DC09B21-8D9A-11D5-B048-00105A9AF985")
Stages;
#endif

EXTERN_C const CLSID CLSID_PointLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("DE453FF4-90BF-11D5-B04B-00105A9AF985")
PointLoad;
#endif

EXTERN_C const CLSID CLSID_PointLoadItem;

#ifdef __cplusplus

class DECLSPEC_UUID("DE453FF7-90BF-11D5-B04B-00105A9AF985")
PointLoadItem;
#endif

EXTERN_C const CLSID CLSID_PointLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("DE453FFA-90BF-11D5-B04B-00105A9AF985")
PointLoads;
#endif

EXTERN_C const CLSID CLSID_DistributedLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("796E1EF4-9252-11D5-B04D-00105A9AF985")
DistributedLoad;
#endif

EXTERN_C const CLSID CLSID_DistributedLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("796E1EF7-9252-11D5-B04D-00105A9AF985")
DistributedLoads;
#endif

EXTERN_C const CLSID CLSID_SettlementLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("FF2C8728-9357-11D5-B04E-00105A9AF985")
SettlementLoad;
#endif

EXTERN_C const CLSID CLSID_SettlementLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("FF2C872B-9357-11D5-B04E-00105A9AF985")
SettlementLoads;
#endif

EXTERN_C const CLSID CLSID_TemperatureLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("FF2C872E-9357-11D5-B04E-00105A9AF985")
TemperatureLoad;
#endif

EXTERN_C const CLSID CLSID_TemperatureLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("FF2C8731-9357-11D5-B04E-00105A9AF985")
TemperatureLoads;
#endif

EXTERN_C const CLSID CLSID_StrainLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("1B46820A-9584-11D5-B050-00105A9AF985")
StrainLoad;
#endif

EXTERN_C const CLSID CLSID_StrainLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("1B46820D-9584-11D5-B050-00105A9AF985")
StrainLoads;
#endif

EXTERN_C const CLSID CLSID_LoadGroup;

#ifdef __cplusplus

class DECLSPEC_UUID("D54A59A2-95B0-11D5-B050-00105A9AF985")
LoadGroup;
#endif

EXTERN_C const CLSID CLSID_LoadGroups;

#ifdef __cplusplus

class DECLSPEC_UUID("D54A59A5-95B0-11D5-B050-00105A9AF985")
LoadGroups;
#endif

EXTERN_C const CLSID CLSID_LiveLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("173739FF-52CB-40F0-A3E9-20B205472028")
LiveLoad;
#endif

EXTERN_C const CLSID CLSID_LiveLoadModel;

#ifdef __cplusplus

class DECLSPEC_UUID("897EBD27-A113-4C10-8A8A-5F875D83E54E")
LiveLoadModel;
#endif

EXTERN_C const CLSID CLSID_VehicularLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("C4A25290-DA37-4D46-90C5-81A00A088D78")
VehicularLoads;
#endif

EXTERN_C const CLSID CLSID_VehicularLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("7551A314-AAE3-4375-979C-A351EBE480DE")
VehicularLoad;
#endif

EXTERN_C const CLSID CLSID_Axle;

#ifdef __cplusplus

class DECLSPEC_UUID("FD146FE7-18DF-4218-9C40-EBC110433263")
Axle;
#endif

EXTERN_C const CLSID CLSID_Axles;

#ifdef __cplusplus

class DECLSPEC_UUID("33926EE8-E5AD-400E-B086-5A6B8BCAF850")
Axles;
#endif

EXTERN_C const CLSID CLSID_LoadCase;

#ifdef __cplusplus

class DECLSPEC_UUID("4BA47812-E350-4C5F-A7C1-5438BD9C8AFF")
LoadCase;
#endif

EXTERN_C const CLSID CLSID_LoadCases;

#ifdef __cplusplus

class DECLSPEC_UUID("133D8F6E-1421-49AB-BD4A-1CE03D9E1136")
LoadCases;
#endif

EXTERN_C const CLSID CLSID_LoadCombination;

#ifdef __cplusplus

class DECLSPEC_UUID("D428D72C-77F7-4012-99B3-9F705A8632EA")
LoadCombination;
#endif

EXTERN_C const CLSID CLSID_LoadCombinations;

#ifdef __cplusplus

class DECLSPEC_UUID("25D42977-A86B-43F3-A190-810F74EC92E9")
LoadCombinations;
#endif

EXTERN_C const CLSID CLSID_DistributionFactors;

#ifdef __cplusplus

class DECLSPEC_UUID("396DE5CB-AE29-4C27-8BCC-47B52C5A6253")
DistributionFactors;
#endif

EXTERN_C const CLSID CLSID_DistributionFactorSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("9FF81F6A-2D8E-4B59-843B-E138647F222F")
DistributionFactorSegment;
#endif

EXTERN_C const CLSID CLSID_LinearDistributionFactorSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("18CF521C-48EF-473d-856B-A7A83135D073")
LinearDistributionFactorSegment;
#endif

EXTERN_C const CLSID CLSID_FilteredDfSegmentCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("6B54598E-5CBD-4876-A0A3-5F45FEC6FFA4")
FilteredDfSegmentCollection;
#endif

EXTERN_C const CLSID CLSID_POIStressPointsItem;

#ifdef __cplusplus

class DECLSPEC_UUID("67D7B53C-2A06-4823-B193-816611B45781")
POIStressPointsItem;
#endif

EXTERN_C const CLSID CLSID_POIStressPoints;

#ifdef __cplusplus

class DECLSPEC_UUID("70817B57-E951-43E1-877E-2CBF71179561")
POIStressPoints;
#endif
#endif /* __WBFLLBAM_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


