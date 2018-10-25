

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:38:55 2017
 */
/* Compiler settings for ..\Include\WBFLRCCapacity.idl:
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


#ifndef __WBFLRCCapacity_h__
#define __WBFLRCCapacity_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IStressStrain_FWD_DEFINED__
#define __IStressStrain_FWD_DEFINED__
typedef interface IStressStrain IStressStrain;

#endif 	/* __IStressStrain_FWD_DEFINED__ */


#ifndef __IRCBeam_FWD_DEFINED__
#define __IRCBeam_FWD_DEFINED__
typedef interface IRCBeam IRCBeam;

#endif 	/* __IRCBeam_FWD_DEFINED__ */


#ifndef __IRCBeam2_FWD_DEFINED__
#define __IRCBeam2_FWD_DEFINED__
typedef interface IRCBeam2 IRCBeam2;

#endif 	/* __IRCBeam2_FWD_DEFINED__ */


#ifndef __IRCBeam2Ex_FWD_DEFINED__
#define __IRCBeam2Ex_FWD_DEFINED__
typedef interface IRCBeam2Ex IRCBeam2Ex;

#endif 	/* __IRCBeam2Ex_FWD_DEFINED__ */


#ifndef __IRCSolution_FWD_DEFINED__
#define __IRCSolution_FWD_DEFINED__
typedef interface IRCSolution IRCSolution;

#endif 	/* __IRCSolution_FWD_DEFINED__ */


#ifndef __ILRFDSolution_FWD_DEFINED__
#define __ILRFDSolution_FWD_DEFINED__
typedef interface ILRFDSolution ILRFDSolution;

#endif 	/* __ILRFDSolution_FWD_DEFINED__ */


#ifndef __IRCSolutionEx_FWD_DEFINED__
#define __IRCSolutionEx_FWD_DEFINED__
typedef interface IRCSolutionEx IRCSolutionEx;

#endif 	/* __IRCSolutionEx_FWD_DEFINED__ */


#ifndef __ILRFDSolutionEx_FWD_DEFINED__
#define __ILRFDSolutionEx_FWD_DEFINED__
typedef interface ILRFDSolutionEx ILRFDSolutionEx;

#endif 	/* __ILRFDSolutionEx_FWD_DEFINED__ */


#ifndef __IRCSolver_FWD_DEFINED__
#define __IRCSolver_FWD_DEFINED__
typedef interface IRCSolver IRCSolver;

#endif 	/* __IRCSolver_FWD_DEFINED__ */


#ifndef __IRCSolver2_FWD_DEFINED__
#define __IRCSolver2_FWD_DEFINED__
typedef interface IRCSolver2 IRCSolver2;

#endif 	/* __IRCSolver2_FWD_DEFINED__ */


#ifndef __IRCSolver2Ex_FWD_DEFINED__
#define __IRCSolver2Ex_FWD_DEFINED__
typedef interface IRCSolver2Ex IRCSolver2Ex;

#endif 	/* __IRCSolver2Ex_FWD_DEFINED__ */


#ifndef __IPCISolver_FWD_DEFINED__
#define __IPCISolver_FWD_DEFINED__
typedef interface IPCISolver IPCISolver;

#endif 	/* __IPCISolver_FWD_DEFINED__ */


#ifndef __INLSolver_FWD_DEFINED__
#define __INLSolver_FWD_DEFINED__
typedef interface INLSolver INLSolver;

#endif 	/* __INLSolver_FWD_DEFINED__ */


#ifndef __ILRFDSolver_FWD_DEFINED__
#define __ILRFDSolver_FWD_DEFINED__
typedef interface ILRFDSolver ILRFDSolver;

#endif 	/* __ILRFDSolver_FWD_DEFINED__ */


#ifndef __ILRFDSolver2_FWD_DEFINED__
#define __ILRFDSolver2_FWD_DEFINED__
typedef interface ILRFDSolver2 ILRFDSolver2;

#endif 	/* __ILRFDSolver2_FWD_DEFINED__ */


#ifndef __ILFDSolver_FWD_DEFINED__
#define __ILFDSolver_FWD_DEFINED__
typedef interface ILFDSolver ILFDSolver;

#endif 	/* __ILFDSolver_FWD_DEFINED__ */


#ifndef __IMixedSolver_FWD_DEFINED__
#define __IMixedSolver_FWD_DEFINED__
typedef interface IMixedSolver IMixedSolver;

#endif 	/* __IMixedSolver_FWD_DEFINED__ */


#ifndef __IUnconfinedConcrete_FWD_DEFINED__
#define __IUnconfinedConcrete_FWD_DEFINED__
typedef interface IUnconfinedConcrete IUnconfinedConcrete;

#endif 	/* __IUnconfinedConcrete_FWD_DEFINED__ */


#ifndef __IRebarModel_FWD_DEFINED__
#define __IRebarModel_FWD_DEFINED__
typedef interface IRebarModel IRebarModel;

#endif 	/* __IRebarModel_FWD_DEFINED__ */


#ifndef __IStrainHardenedRebarModel_FWD_DEFINED__
#define __IStrainHardenedRebarModel_FWD_DEFINED__
typedef interface IStrainHardenedRebarModel IStrainHardenedRebarModel;

#endif 	/* __IStrainHardenedRebarModel_FWD_DEFINED__ */


#ifndef __IPCISolution_FWD_DEFINED__
#define __IPCISolution_FWD_DEFINED__
typedef interface IPCISolution IPCISolution;

#endif 	/* __IPCISolution_FWD_DEFINED__ */


#ifndef __IPCISolutionEx_FWD_DEFINED__
#define __IPCISolutionEx_FWD_DEFINED__
typedef interface IPCISolutionEx IPCISolutionEx;

#endif 	/* __IPCISolutionEx_FWD_DEFINED__ */


#ifndef __IRoundColumn_FWD_DEFINED__
#define __IRoundColumn_FWD_DEFINED__
typedef interface IRoundColumn IRoundColumn;

#endif 	/* __IRoundColumn_FWD_DEFINED__ */


#ifndef __IGeneralSection_FWD_DEFINED__
#define __IGeneralSection_FWD_DEFINED__
typedef interface IGeneralSection IGeneralSection;

#endif 	/* __IGeneralSection_FWD_DEFINED__ */


#ifndef __IGeneralSectionSlice_FWD_DEFINED__
#define __IGeneralSectionSlice_FWD_DEFINED__
typedef interface IGeneralSectionSlice IGeneralSectionSlice;

#endif 	/* __IGeneralSectionSlice_FWD_DEFINED__ */


#ifndef __IGeneralSectionSolution_FWD_DEFINED__
#define __IGeneralSectionSolution_FWD_DEFINED__
typedef interface IGeneralSectionSolution IGeneralSectionSolution;

#endif 	/* __IGeneralSectionSolution_FWD_DEFINED__ */


#ifndef __IGeneralSectionSolver_FWD_DEFINED__
#define __IGeneralSectionSolver_FWD_DEFINED__
typedef interface IGeneralSectionSolver IGeneralSectionSolver;

#endif 	/* __IGeneralSectionSolver_FWD_DEFINED__ */


#ifndef __IMomentCurvatureSolution_FWD_DEFINED__
#define __IMomentCurvatureSolution_FWD_DEFINED__
typedef interface IMomentCurvatureSolution IMomentCurvatureSolution;

#endif 	/* __IMomentCurvatureSolution_FWD_DEFINED__ */


#ifndef __IMomentCurvatureSolver_FWD_DEFINED__
#define __IMomentCurvatureSolver_FWD_DEFINED__
typedef interface IMomentCurvatureSolver IMomentCurvatureSolver;

#endif 	/* __IMomentCurvatureSolver_FWD_DEFINED__ */


#ifndef __IMomentCapacitySolution_FWD_DEFINED__
#define __IMomentCapacitySolution_FWD_DEFINED__
typedef interface IMomentCapacitySolution IMomentCapacitySolution;

#endif 	/* __IMomentCapacitySolution_FWD_DEFINED__ */


#ifndef __IMomentCapacitySolver_FWD_DEFINED__
#define __IMomentCapacitySolver_FWD_DEFINED__
typedef interface IMomentCapacitySolver IMomentCapacitySolver;

#endif 	/* __IMomentCapacitySolver_FWD_DEFINED__ */


#ifndef __IInteractionCurveSolution_FWD_DEFINED__
#define __IInteractionCurveSolution_FWD_DEFINED__
typedef interface IInteractionCurveSolution IInteractionCurveSolution;

#endif 	/* __IInteractionCurveSolution_FWD_DEFINED__ */


#ifndef __IInteractionCurveSolver_FWD_DEFINED__
#define __IInteractionCurveSolver_FWD_DEFINED__
typedef interface IInteractionCurveSolver IInteractionCurveSolver;

#endif 	/* __IInteractionCurveSolver_FWD_DEFINED__ */


#ifndef __IInteractionCapacityCurveSolution_FWD_DEFINED__
#define __IInteractionCapacityCurveSolution_FWD_DEFINED__
typedef interface IInteractionCapacityCurveSolution IInteractionCapacityCurveSolution;

#endif 	/* __IInteractionCapacityCurveSolution_FWD_DEFINED__ */


#ifndef __IAxialInteractionCurveSolver_FWD_DEFINED__
#define __IAxialInteractionCurveSolver_FWD_DEFINED__
typedef interface IAxialInteractionCurveSolver IAxialInteractionCurveSolver;

#endif 	/* __IAxialInteractionCurveSolver_FWD_DEFINED__ */


#ifndef __IMomentInteractionCurveSolver_FWD_DEFINED__
#define __IMomentInteractionCurveSolver_FWD_DEFINED__
typedef interface IMomentInteractionCurveSolver IMomentInteractionCurveSolver;

#endif 	/* __IMomentInteractionCurveSolver_FWD_DEFINED__ */


#ifndef __ICrackedSectionSlice_FWD_DEFINED__
#define __ICrackedSectionSlice_FWD_DEFINED__
typedef interface ICrackedSectionSlice ICrackedSectionSlice;

#endif 	/* __ICrackedSectionSlice_FWD_DEFINED__ */


#ifndef __ICrackedSectionSolution_FWD_DEFINED__
#define __ICrackedSectionSolution_FWD_DEFINED__
typedef interface ICrackedSectionSolution ICrackedSectionSolution;

#endif 	/* __ICrackedSectionSolution_FWD_DEFINED__ */


#ifndef __ICrackedSectionSolver_FWD_DEFINED__
#define __ICrackedSectionSolver_FWD_DEFINED__
typedef interface ICrackedSectionSolver ICrackedSectionSolver;

#endif 	/* __ICrackedSectionSolver_FWD_DEFINED__ */


#ifndef __IManderModelSection_FWD_DEFINED__
#define __IManderModelSection_FWD_DEFINED__
typedef interface IManderModelSection IManderModelSection;

#endif 	/* __IManderModelSection_FWD_DEFINED__ */


#ifndef __ICircularManderSection_FWD_DEFINED__
#define __ICircularManderSection_FWD_DEFINED__
typedef interface ICircularManderSection ICircularManderSection;

#endif 	/* __ICircularManderSection_FWD_DEFINED__ */


#ifndef __IManderModel_FWD_DEFINED__
#define __IManderModel_FWD_DEFINED__
typedef interface IManderModel IManderModel;

#endif 	/* __IManderModel_FWD_DEFINED__ */


#ifndef __IPowerFormula_FWD_DEFINED__
#define __IPowerFormula_FWD_DEFINED__
typedef interface IPowerFormula IPowerFormula;

#endif 	/* __IPowerFormula_FWD_DEFINED__ */


#ifndef __ILRFDPrestressFormula_FWD_DEFINED__
#define __ILRFDPrestressFormula_FWD_DEFINED__
typedef interface ILRFDPrestressFormula ILRFDPrestressFormula;

#endif 	/* __ILRFDPrestressFormula_FWD_DEFINED__ */


#ifndef __ISectionBuilder_FWD_DEFINED__
#define __ISectionBuilder_FWD_DEFINED__
typedef interface ISectionBuilder ISectionBuilder;

#endif 	/* __ISectionBuilder_FWD_DEFINED__ */


#ifndef __ICapacityReductionFactor_FWD_DEFINED__
#define __ICapacityReductionFactor_FWD_DEFINED__
typedef interface ICapacityReductionFactor ICapacityReductionFactor;

#endif 	/* __ICapacityReductionFactor_FWD_DEFINED__ */


#ifndef __IRCCrackedSectionSolver_FWD_DEFINED__
#define __IRCCrackedSectionSolver_FWD_DEFINED__
typedef interface IRCCrackedSectionSolver IRCCrackedSectionSolver;

#endif 	/* __IRCCrackedSectionSolver_FWD_DEFINED__ */


#ifndef __IRCCrackedSectionSolver2_FWD_DEFINED__
#define __IRCCrackedSectionSolver2_FWD_DEFINED__
typedef interface IRCCrackedSectionSolver2 IRCCrackedSectionSolver2;

#endif 	/* __IRCCrackedSectionSolver2_FWD_DEFINED__ */


#ifndef __IRCCrackedSectionSolver2Ex_FWD_DEFINED__
#define __IRCCrackedSectionSolver2Ex_FWD_DEFINED__
typedef interface IRCCrackedSectionSolver2Ex IRCCrackedSectionSolver2Ex;

#endif 	/* __IRCCrackedSectionSolver2Ex_FWD_DEFINED__ */


#ifndef __UnconfinedConcrete_FWD_DEFINED__
#define __UnconfinedConcrete_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnconfinedConcrete UnconfinedConcrete;
#else
typedef struct UnconfinedConcrete UnconfinedConcrete;
#endif /* __cplusplus */

#endif 	/* __UnconfinedConcrete_FWD_DEFINED__ */


#ifndef __PSPowerFormula_FWD_DEFINED__
#define __PSPowerFormula_FWD_DEFINED__

#ifdef __cplusplus
typedef class PSPowerFormula PSPowerFormula;
#else
typedef struct PSPowerFormula PSPowerFormula;
#endif /* __cplusplus */

#endif 	/* __PSPowerFormula_FWD_DEFINED__ */


#ifndef __LRFDPrestressFormula_FWD_DEFINED__
#define __LRFDPrestressFormula_FWD_DEFINED__

#ifdef __cplusplus
typedef class LRFDPrestressFormula LRFDPrestressFormula;
#else
typedef struct LRFDPrestressFormula LRFDPrestressFormula;
#endif /* __cplusplus */

#endif 	/* __LRFDPrestressFormula_FWD_DEFINED__ */


#ifndef __RebarModel_FWD_DEFINED__
#define __RebarModel_FWD_DEFINED__

#ifdef __cplusplus
typedef class RebarModel RebarModel;
#else
typedef struct RebarModel RebarModel;
#endif /* __cplusplus */

#endif 	/* __RebarModel_FWD_DEFINED__ */


#ifndef __StrainHardenedRebarModel_FWD_DEFINED__
#define __StrainHardenedRebarModel_FWD_DEFINED__

#ifdef __cplusplus
typedef class StrainHardenedRebarModel StrainHardenedRebarModel;
#else
typedef struct StrainHardenedRebarModel StrainHardenedRebarModel;
#endif /* __cplusplus */

#endif 	/* __StrainHardenedRebarModel_FWD_DEFINED__ */


#ifndef __RCBeam_FWD_DEFINED__
#define __RCBeam_FWD_DEFINED__

#ifdef __cplusplus
typedef class RCBeam RCBeam;
#else
typedef struct RCBeam RCBeam;
#endif /* __cplusplus */

#endif 	/* __RCBeam_FWD_DEFINED__ */


#ifndef __RCBeam2_FWD_DEFINED__
#define __RCBeam2_FWD_DEFINED__

#ifdef __cplusplus
typedef class RCBeam2 RCBeam2;
#else
typedef struct RCBeam2 RCBeam2;
#endif /* __cplusplus */

#endif 	/* __RCBeam2_FWD_DEFINED__ */


#ifndef __RCBeam2Ex_FWD_DEFINED__
#define __RCBeam2Ex_FWD_DEFINED__

#ifdef __cplusplus
typedef class RCBeam2Ex RCBeam2Ex;
#else
typedef struct RCBeam2Ex RCBeam2Ex;
#endif /* __cplusplus */

#endif 	/* __RCBeam2Ex_FWD_DEFINED__ */


#ifndef __LRFDSolver_FWD_DEFINED__
#define __LRFDSolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class LRFDSolver LRFDSolver;
#else
typedef struct LRFDSolver LRFDSolver;
#endif /* __cplusplus */

#endif 	/* __LRFDSolver_FWD_DEFINED__ */


#ifndef __LRFDSolver2_FWD_DEFINED__
#define __LRFDSolver2_FWD_DEFINED__

#ifdef __cplusplus
typedef class LRFDSolver2 LRFDSolver2;
#else
typedef struct LRFDSolver2 LRFDSolver2;
#endif /* __cplusplus */

#endif 	/* __LRFDSolver2_FWD_DEFINED__ */


#ifndef __LFDSolver_FWD_DEFINED__
#define __LFDSolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class LFDSolver LFDSolver;
#else
typedef struct LFDSolver LFDSolver;
#endif /* __cplusplus */

#endif 	/* __LFDSolver_FWD_DEFINED__ */


#ifndef __PCISolver_FWD_DEFINED__
#define __PCISolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class PCISolver PCISolver;
#else
typedef struct PCISolver PCISolver;
#endif /* __cplusplus */

#endif 	/* __PCISolver_FWD_DEFINED__ */


#ifndef __NLSolver_FWD_DEFINED__
#define __NLSolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class NLSolver NLSolver;
#else
typedef struct NLSolver NLSolver;
#endif /* __cplusplus */

#endif 	/* __NLSolver_FWD_DEFINED__ */


#ifndef __RCSolution_FWD_DEFINED__
#define __RCSolution_FWD_DEFINED__

#ifdef __cplusplus
typedef class RCSolution RCSolution;
#else
typedef struct RCSolution RCSolution;
#endif /* __cplusplus */

#endif 	/* __RCSolution_FWD_DEFINED__ */


#ifndef __RCSolutionEx_FWD_DEFINED__
#define __RCSolutionEx_FWD_DEFINED__

#ifdef __cplusplus
typedef class RCSolutionEx RCSolutionEx;
#else
typedef struct RCSolutionEx RCSolutionEx;
#endif /* __cplusplus */

#endif 	/* __RCSolutionEx_FWD_DEFINED__ */


#ifndef __LRFDSolution_FWD_DEFINED__
#define __LRFDSolution_FWD_DEFINED__

#ifdef __cplusplus
typedef class LRFDSolution LRFDSolution;
#else
typedef struct LRFDSolution LRFDSolution;
#endif /* __cplusplus */

#endif 	/* __LRFDSolution_FWD_DEFINED__ */


#ifndef __LRFDSolutionEx_FWD_DEFINED__
#define __LRFDSolutionEx_FWD_DEFINED__

#ifdef __cplusplus
typedef class LRFDSolutionEx LRFDSolutionEx;
#else
typedef struct LRFDSolutionEx LRFDSolutionEx;
#endif /* __cplusplus */

#endif 	/* __LRFDSolutionEx_FWD_DEFINED__ */


#ifndef __PCISolution_FWD_DEFINED__
#define __PCISolution_FWD_DEFINED__

#ifdef __cplusplus
typedef class PCISolution PCISolution;
#else
typedef struct PCISolution PCISolution;
#endif /* __cplusplus */

#endif 	/* __PCISolution_FWD_DEFINED__ */


#ifndef __PCISolutionEx_FWD_DEFINED__
#define __PCISolutionEx_FWD_DEFINED__

#ifdef __cplusplus
typedef class PCISolutionEx PCISolutionEx;
#else
typedef struct PCISolutionEx PCISolutionEx;
#endif /* __cplusplus */

#endif 	/* __PCISolutionEx_FWD_DEFINED__ */


#ifndef __MixedSolver_FWD_DEFINED__
#define __MixedSolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class MixedSolver MixedSolver;
#else
typedef struct MixedSolver MixedSolver;
#endif /* __cplusplus */

#endif 	/* __MixedSolver_FWD_DEFINED__ */


#ifndef __RoundColumn_FWD_DEFINED__
#define __RoundColumn_FWD_DEFINED__

#ifdef __cplusplus
typedef class RoundColumn RoundColumn;
#else
typedef struct RoundColumn RoundColumn;
#endif /* __cplusplus */

#endif 	/* __RoundColumn_FWD_DEFINED__ */


#ifndef __GeneralSection_FWD_DEFINED__
#define __GeneralSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class GeneralSection GeneralSection;
#else
typedef struct GeneralSection GeneralSection;
#endif /* __cplusplus */

#endif 	/* __GeneralSection_FWD_DEFINED__ */


#ifndef __GeneralSectionSlice_FWD_DEFINED__
#define __GeneralSectionSlice_FWD_DEFINED__

#ifdef __cplusplus
typedef class GeneralSectionSlice GeneralSectionSlice;
#else
typedef struct GeneralSectionSlice GeneralSectionSlice;
#endif /* __cplusplus */

#endif 	/* __GeneralSectionSlice_FWD_DEFINED__ */


#ifndef __GeneralSectionSolution_FWD_DEFINED__
#define __GeneralSectionSolution_FWD_DEFINED__

#ifdef __cplusplus
typedef class GeneralSectionSolution GeneralSectionSolution;
#else
typedef struct GeneralSectionSolution GeneralSectionSolution;
#endif /* __cplusplus */

#endif 	/* __GeneralSectionSolution_FWD_DEFINED__ */


#ifndef __GeneralSectionSolver_FWD_DEFINED__
#define __GeneralSectionSolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class GeneralSectionSolver GeneralSectionSolver;
#else
typedef struct GeneralSectionSolver GeneralSectionSolver;
#endif /* __cplusplus */

#endif 	/* __GeneralSectionSolver_FWD_DEFINED__ */


#ifndef __MomentCurvatureSolution_FWD_DEFINED__
#define __MomentCurvatureSolution_FWD_DEFINED__

#ifdef __cplusplus
typedef class MomentCurvatureSolution MomentCurvatureSolution;
#else
typedef struct MomentCurvatureSolution MomentCurvatureSolution;
#endif /* __cplusplus */

#endif 	/* __MomentCurvatureSolution_FWD_DEFINED__ */


#ifndef __MomentCurvatureSolver_FWD_DEFINED__
#define __MomentCurvatureSolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class MomentCurvatureSolver MomentCurvatureSolver;
#else
typedef struct MomentCurvatureSolver MomentCurvatureSolver;
#endif /* __cplusplus */

#endif 	/* __MomentCurvatureSolver_FWD_DEFINED__ */


#ifndef __MomentCapacitySolution_FWD_DEFINED__
#define __MomentCapacitySolution_FWD_DEFINED__

#ifdef __cplusplus
typedef class MomentCapacitySolution MomentCapacitySolution;
#else
typedef struct MomentCapacitySolution MomentCapacitySolution;
#endif /* __cplusplus */

#endif 	/* __MomentCapacitySolution_FWD_DEFINED__ */


#ifndef __MomentCapacitySolver_FWD_DEFINED__
#define __MomentCapacitySolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class MomentCapacitySolver MomentCapacitySolver;
#else
typedef struct MomentCapacitySolver MomentCapacitySolver;
#endif /* __cplusplus */

#endif 	/* __MomentCapacitySolver_FWD_DEFINED__ */


#ifndef __CircularManderSection_FWD_DEFINED__
#define __CircularManderSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class CircularManderSection CircularManderSection;
#else
typedef struct CircularManderSection CircularManderSection;
#endif /* __cplusplus */

#endif 	/* __CircularManderSection_FWD_DEFINED__ */


#ifndef __ManderModel_FWD_DEFINED__
#define __ManderModel_FWD_DEFINED__

#ifdef __cplusplus
typedef class ManderModel ManderModel;
#else
typedef struct ManderModel ManderModel;
#endif /* __cplusplus */

#endif 	/* __ManderModel_FWD_DEFINED__ */


#ifndef __InteractionCurveSolution_FWD_DEFINED__
#define __InteractionCurveSolution_FWD_DEFINED__

#ifdef __cplusplus
typedef class InteractionCurveSolution InteractionCurveSolution;
#else
typedef struct InteractionCurveSolution InteractionCurveSolution;
#endif /* __cplusplus */

#endif 	/* __InteractionCurveSolution_FWD_DEFINED__ */


#ifndef __InteractionCurveSolver_FWD_DEFINED__
#define __InteractionCurveSolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class InteractionCurveSolver InteractionCurveSolver;
#else
typedef struct InteractionCurveSolver InteractionCurveSolver;
#endif /* __cplusplus */

#endif 	/* __InteractionCurveSolver_FWD_DEFINED__ */


#ifndef __InteractionCapacityCurveSolution_FWD_DEFINED__
#define __InteractionCapacityCurveSolution_FWD_DEFINED__

#ifdef __cplusplus
typedef class InteractionCapacityCurveSolution InteractionCapacityCurveSolution;
#else
typedef struct InteractionCapacityCurveSolution InteractionCapacityCurveSolution;
#endif /* __cplusplus */

#endif 	/* __InteractionCapacityCurveSolution_FWD_DEFINED__ */


#ifndef __AxialInteractionCurveSolver_FWD_DEFINED__
#define __AxialInteractionCurveSolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class AxialInteractionCurveSolver AxialInteractionCurveSolver;
#else
typedef struct AxialInteractionCurveSolver AxialInteractionCurveSolver;
#endif /* __cplusplus */

#endif 	/* __AxialInteractionCurveSolver_FWD_DEFINED__ */


#ifndef __MomentInteractionCurveSolver_FWD_DEFINED__
#define __MomentInteractionCurveSolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class MomentInteractionCurveSolver MomentInteractionCurveSolver;
#else
typedef struct MomentInteractionCurveSolver MomentInteractionCurveSolver;
#endif /* __cplusplus */

#endif 	/* __MomentInteractionCurveSolver_FWD_DEFINED__ */


#ifndef __SectionBuilder_FWD_DEFINED__
#define __SectionBuilder_FWD_DEFINED__

#ifdef __cplusplus
typedef class SectionBuilder SectionBuilder;
#else
typedef struct SectionBuilder SectionBuilder;
#endif /* __cplusplus */

#endif 	/* __SectionBuilder_FWD_DEFINED__ */


#ifndef __CapacityReductionFactor_FWD_DEFINED__
#define __CapacityReductionFactor_FWD_DEFINED__

#ifdef __cplusplus
typedef class CapacityReductionFactor CapacityReductionFactor;
#else
typedef struct CapacityReductionFactor CapacityReductionFactor;
#endif /* __cplusplus */

#endif 	/* __CapacityReductionFactor_FWD_DEFINED__ */


#ifndef __CrackedSectionSolution_FWD_DEFINED__
#define __CrackedSectionSolution_FWD_DEFINED__

#ifdef __cplusplus
typedef class CrackedSectionSolution CrackedSectionSolution;
#else
typedef struct CrackedSectionSolution CrackedSectionSolution;
#endif /* __cplusplus */

#endif 	/* __CrackedSectionSolution_FWD_DEFINED__ */


#ifndef __CrackedSectionSolver_FWD_DEFINED__
#define __CrackedSectionSolver_FWD_DEFINED__

#ifdef __cplusplus
typedef class CrackedSectionSolver CrackedSectionSolver;
#else
typedef struct CrackedSectionSolver CrackedSectionSolver;
#endif /* __cplusplus */

#endif 	/* __CrackedSectionSolver_FWD_DEFINED__ */


#ifndef __CrackedSectionSlice_FWD_DEFINED__
#define __CrackedSectionSlice_FWD_DEFINED__

#ifdef __cplusplus
typedef class CrackedSectionSlice CrackedSectionSlice;
#else
typedef struct CrackedSectionSlice CrackedSectionSlice;
#endif /* __cplusplus */

#endif 	/* __CrackedSectionSlice_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"
#include "WBFLGeometry.h"
#include "WBFLUnitServer.h"
#include "WBFLSections.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLRCCapacity_0000_0000 */
/* [local] */ 

#define RC_E_INITCONCRETE           MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,512)
#define RC_E_SOLUTIONNOTFOUND       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,513)
#define RC_E_BEAMNOTSYMMETRIC       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,514)
#define RC_E_MATERIALFAILURE        MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,515)
#define RC_E_NEUTRALAXISNOTBOUNDED  MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,516)
#define RC_E_SECTION                MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,517)
#define RC_E_FGMATERIAL             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,518)
#define RC_E_BGMATERIAL             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,519)


extern RPC_IF_HANDLE __MIDL_itf_WBFLRCCapacity_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLRCCapacity_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLRCCapacity_LIBRARY_DEFINED__
#define __WBFLRCCapacity_LIBRARY_DEFINED__

/* library WBFLRCCapacity */
/* [helpstring][version][uuid] */ 

typedef /* [public][public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("7EEAA5E8-7AAE-4e1b-8F6B-0740BFE02F2F") 
enum __MIDL___MIDL_itf_WBFLRCCapacity_0000_0000_0001
    {
        trtSpiral	= 1,
        trtHoops	= 2
    } 	TransvReinforcementType;

typedef /* [public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("464B228A-D182-4823-BE7E-B8A20A22D055") 
enum __MIDL___MIDL_itf_WBFLRCCapacity_0000_0000_0002
    {
        smFixedCurvature	= 1,
        smFixedCompressiveStrain	= 2
    } 	SolutionMethod;

typedef /* [public][public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("3BE4F7FC-A94D-4BA3-90A8-D81BA56709EF") 
enum __MIDL___MIDL_itf_WBFLRCCapacity_0000_0000_0003
    {
        sgtGrade250	= 1,
        sgtGrade270	= 2
    } 	StrandGradeType;

typedef /* [public][public][public][public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("16237E1D-9EB8-4B93-B8F7-B33FAD9F0208") 
enum __MIDL___MIDL_itf_WBFLRCCapacity_0000_0000_0004
    {
        pmtLowRelaxation	= 1,
        pmtStressRelieved	= 2
    } 	ProductionMethodType;


EXTERN_C const IID LIBID_WBFLRCCapacity;

#ifndef __IStressStrain_INTERFACE_DEFINED__
#define __IStressStrain_INTERFACE_DEFINED__

/* interface IStressStrain */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStressStrain;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0EE9658D-A9AB-45ba-8BBD-6486353E5885")
    IStressStrain : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_YieldStrain( 
            /* [retval][out] */ Float64 *pey) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ModulusOfElasticity( 
            /* [retval][out] */ Float64 *pE) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeStress( 
            /* [in] */ Float64 strain,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE StrainLimits( 
            /* [out] */ Float64 *minStrain,
            /* [out] */ Float64 *maxStrain) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrainAtPeakStress( 
            /* [retval][out] */ Float64 *strain) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStressStrainVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStressStrain * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStressStrain * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStressStrain * This);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IStressStrain * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IStressStrain * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_YieldStrain )( 
            IStressStrain * This,
            /* [retval][out] */ Float64 *pey);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ModulusOfElasticity )( 
            IStressStrain * This,
            /* [retval][out] */ Float64 *pE);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeStress )( 
            IStressStrain * This,
            /* [in] */ Float64 strain,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *StrainLimits )( 
            IStressStrain * This,
            /* [out] */ Float64 *minStrain,
            /* [out] */ Float64 *maxStrain);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrainAtPeakStress )( 
            IStressStrain * This,
            /* [retval][out] */ Float64 *strain);
        
        END_INTERFACE
    } IStressStrainVtbl;

    interface IStressStrain
    {
        CONST_VTBL struct IStressStrainVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStressStrain_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStressStrain_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStressStrain_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStressStrain_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 

#define IStressStrain_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IStressStrain_get_YieldStrain(This,pey)	\
    ( (This)->lpVtbl -> get_YieldStrain(This,pey) ) 

#define IStressStrain_get_ModulusOfElasticity(This,pE)	\
    ( (This)->lpVtbl -> get_ModulusOfElasticity(This,pE) ) 

#define IStressStrain_ComputeStress(This,strain,pVal)	\
    ( (This)->lpVtbl -> ComputeStress(This,strain,pVal) ) 

#define IStressStrain_StrainLimits(This,minStrain,maxStrain)	\
    ( (This)->lpVtbl -> StrainLimits(This,minStrain,maxStrain) ) 

#define IStressStrain_get_StrainAtPeakStress(This,strain)	\
    ( (This)->lpVtbl -> get_StrainAtPeakStress(This,strain) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStressStrain_INTERFACE_DEFINED__ */


#ifndef __IRCBeam_INTERFACE_DEFINED__
#define __IRCBeam_INTERFACE_DEFINED__

/* interface IRCBeam */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCBeam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("53B5167D-154B-44AB-9735-56A8953B0D4A")
    IRCBeam : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_b( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_b( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_bw( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_bw( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_hf( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_hf( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_h( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_h( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_As( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_As( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Aps( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Aps( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ds( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_ds( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_dps( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_dps( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fpu( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fpu( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fpy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fpy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fpe( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fpe( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_FcSlab( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_FcSlab( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_FcBeam( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_FcBeam( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Es( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Es( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Eps( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Eps( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCBeamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCBeam * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCBeam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCBeam * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_b )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_b )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_bw )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_bw )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hf )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_hf )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_h )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_h )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_As )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_As )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Aps )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Aps )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ds )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ds )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_dps )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_dps )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fy )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fy )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fpu )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fpu )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fpy )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fpy )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fpe )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fpe )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FcSlab )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FcSlab )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FcBeam )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FcBeam )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Es )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Es )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Eps )( 
            IRCBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Eps )( 
            IRCBeam * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IRCBeamVtbl;

    interface IRCBeam
    {
        CONST_VTBL struct IRCBeamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCBeam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCBeam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCBeam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCBeam_get_b(This,pVal)	\
    ( (This)->lpVtbl -> get_b(This,pVal) ) 

#define IRCBeam_put_b(This,newVal)	\
    ( (This)->lpVtbl -> put_b(This,newVal) ) 

#define IRCBeam_get_bw(This,pVal)	\
    ( (This)->lpVtbl -> get_bw(This,pVal) ) 

#define IRCBeam_put_bw(This,newVal)	\
    ( (This)->lpVtbl -> put_bw(This,newVal) ) 

#define IRCBeam_get_hf(This,pVal)	\
    ( (This)->lpVtbl -> get_hf(This,pVal) ) 

#define IRCBeam_put_hf(This,newVal)	\
    ( (This)->lpVtbl -> put_hf(This,newVal) ) 

#define IRCBeam_get_h(This,pVal)	\
    ( (This)->lpVtbl -> get_h(This,pVal) ) 

#define IRCBeam_put_h(This,newVal)	\
    ( (This)->lpVtbl -> put_h(This,newVal) ) 

#define IRCBeam_get_As(This,pVal)	\
    ( (This)->lpVtbl -> get_As(This,pVal) ) 

#define IRCBeam_put_As(This,newVal)	\
    ( (This)->lpVtbl -> put_As(This,newVal) ) 

#define IRCBeam_get_Aps(This,pVal)	\
    ( (This)->lpVtbl -> get_Aps(This,pVal) ) 

#define IRCBeam_put_Aps(This,newVal)	\
    ( (This)->lpVtbl -> put_Aps(This,newVal) ) 

#define IRCBeam_get_ds(This,pVal)	\
    ( (This)->lpVtbl -> get_ds(This,pVal) ) 

#define IRCBeam_put_ds(This,newVal)	\
    ( (This)->lpVtbl -> put_ds(This,newVal) ) 

#define IRCBeam_get_dps(This,pVal)	\
    ( (This)->lpVtbl -> get_dps(This,pVal) ) 

#define IRCBeam_put_dps(This,newVal)	\
    ( (This)->lpVtbl -> put_dps(This,newVal) ) 

#define IRCBeam_get_fy(This,pVal)	\
    ( (This)->lpVtbl -> get_fy(This,pVal) ) 

#define IRCBeam_put_fy(This,newVal)	\
    ( (This)->lpVtbl -> put_fy(This,newVal) ) 

#define IRCBeam_get_fpu(This,pVal)	\
    ( (This)->lpVtbl -> get_fpu(This,pVal) ) 

#define IRCBeam_put_fpu(This,newVal)	\
    ( (This)->lpVtbl -> put_fpu(This,newVal) ) 

#define IRCBeam_get_fpy(This,pVal)	\
    ( (This)->lpVtbl -> get_fpy(This,pVal) ) 

#define IRCBeam_put_fpy(This,newVal)	\
    ( (This)->lpVtbl -> put_fpy(This,newVal) ) 

#define IRCBeam_get_fpe(This,pVal)	\
    ( (This)->lpVtbl -> get_fpe(This,pVal) ) 

#define IRCBeam_put_fpe(This,newVal)	\
    ( (This)->lpVtbl -> put_fpe(This,newVal) ) 

#define IRCBeam_get_FcSlab(This,pVal)	\
    ( (This)->lpVtbl -> get_FcSlab(This,pVal) ) 

#define IRCBeam_put_FcSlab(This,newVal)	\
    ( (This)->lpVtbl -> put_FcSlab(This,newVal) ) 

#define IRCBeam_get_FcBeam(This,pVal)	\
    ( (This)->lpVtbl -> get_FcBeam(This,pVal) ) 

#define IRCBeam_put_FcBeam(This,newVal)	\
    ( (This)->lpVtbl -> put_FcBeam(This,newVal) ) 

#define IRCBeam_get_Es(This,pVal)	\
    ( (This)->lpVtbl -> get_Es(This,pVal) ) 

#define IRCBeam_put_Es(This,newVal)	\
    ( (This)->lpVtbl -> put_Es(This,newVal) ) 

#define IRCBeam_get_Eps(This,pVal)	\
    ( (This)->lpVtbl -> get_Eps(This,pVal) ) 

#define IRCBeam_put_Eps(This,newVal)	\
    ( (This)->lpVtbl -> put_Eps(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCBeam_INTERFACE_DEFINED__ */


#ifndef __IRCBeam2_INTERFACE_DEFINED__
#define __IRCBeam2_INTERFACE_DEFINED__

/* interface IRCBeam2 */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCBeam2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1344FBEC-4225-477A-A99A-B7460191C650")
    IRCBeam2 : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_b( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_b( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_bw( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_bw( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_hf( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_hf( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_h( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_h( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE AddRebarLayer( 
            /* [in] */ Float64 ds,
            /* [in] */ Float64 As,
            /* [in] */ Float64 devFactor) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayerCount( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayerDepth( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *ds) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayerSteel( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *As) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayerDevFactor( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *devFactor) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE GetRebarLayer( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *ds,
            /* [out] */ Float64 *As,
            /* [out] */ Float64 *devFactor) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE RemoveRebarLayer( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ClearRebarLayers( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE AddStrandLayer( 
            /* [in] */ Float64 dps,
            /* [in] */ Float64 Aps,
            /* [in] */ Float64 devFactor) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandLayerCount( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandLayerDepth( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *dps) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandLayerSteel( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *Aps) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandLayerDevFactor( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *devFactor) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE GetStrandLayer( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *dps,
            /* [out] */ Float64 *Aps,
            /* [out] */ Float64 *devFactor) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE RemoveStrandLayer( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ClearStrandLayers( void) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fpu( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fpu( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fpy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fpy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fpe( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fpe( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_FcSlab( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_FcSlab( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_FcBeam( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_FcBeam( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Es( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Es( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Eps( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Eps( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCBeam2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCBeam2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCBeam2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCBeam2 * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_b )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_b )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_bw )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_bw )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hf )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_hf )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_h )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_h )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *AddRebarLayer )( 
            IRCBeam2 * This,
            /* [in] */ Float64 ds,
            /* [in] */ Float64 As,
            /* [in] */ Float64 devFactor);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayerCount )( 
            IRCBeam2 * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayerDepth )( 
            IRCBeam2 * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *ds);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayerSteel )( 
            IRCBeam2 * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *As);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayerDevFactor )( 
            IRCBeam2 * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *devFactor);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *GetRebarLayer )( 
            IRCBeam2 * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *ds,
            /* [out] */ Float64 *As,
            /* [out] */ Float64 *devFactor);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *RemoveRebarLayer )( 
            IRCBeam2 * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ClearRebarLayers )( 
            IRCBeam2 * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *AddStrandLayer )( 
            IRCBeam2 * This,
            /* [in] */ Float64 dps,
            /* [in] */ Float64 Aps,
            /* [in] */ Float64 devFactor);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandLayerCount )( 
            IRCBeam2 * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandLayerDepth )( 
            IRCBeam2 * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *dps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandLayerSteel )( 
            IRCBeam2 * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *Aps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandLayerDevFactor )( 
            IRCBeam2 * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *devFactor);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *GetStrandLayer )( 
            IRCBeam2 * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *dps,
            /* [out] */ Float64 *Aps,
            /* [out] */ Float64 *devFactor);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *RemoveStrandLayer )( 
            IRCBeam2 * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ClearStrandLayers )( 
            IRCBeam2 * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fy )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fy )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fpu )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fpu )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fpy )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fpy )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fpe )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fpe )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FcSlab )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FcSlab )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FcBeam )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FcBeam )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Es )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Es )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Eps )( 
            IRCBeam2 * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Eps )( 
            IRCBeam2 * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IRCBeam2Vtbl;

    interface IRCBeam2
    {
        CONST_VTBL struct IRCBeam2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCBeam2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCBeam2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCBeam2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCBeam2_get_b(This,pVal)	\
    ( (This)->lpVtbl -> get_b(This,pVal) ) 

#define IRCBeam2_put_b(This,newVal)	\
    ( (This)->lpVtbl -> put_b(This,newVal) ) 

#define IRCBeam2_get_bw(This,pVal)	\
    ( (This)->lpVtbl -> get_bw(This,pVal) ) 

#define IRCBeam2_put_bw(This,newVal)	\
    ( (This)->lpVtbl -> put_bw(This,newVal) ) 

#define IRCBeam2_get_hf(This,pVal)	\
    ( (This)->lpVtbl -> get_hf(This,pVal) ) 

#define IRCBeam2_put_hf(This,newVal)	\
    ( (This)->lpVtbl -> put_hf(This,newVal) ) 

#define IRCBeam2_get_h(This,pVal)	\
    ( (This)->lpVtbl -> get_h(This,pVal) ) 

#define IRCBeam2_put_h(This,newVal)	\
    ( (This)->lpVtbl -> put_h(This,newVal) ) 

#define IRCBeam2_AddRebarLayer(This,ds,As,devFactor)	\
    ( (This)->lpVtbl -> AddRebarLayer(This,ds,As,devFactor) ) 

#define IRCBeam2_get_RebarLayerCount(This,count)	\
    ( (This)->lpVtbl -> get_RebarLayerCount(This,count) ) 

#define IRCBeam2_get_RebarLayerDepth(This,index,ds)	\
    ( (This)->lpVtbl -> get_RebarLayerDepth(This,index,ds) ) 

#define IRCBeam2_get_RebarLayerSteel(This,index,As)	\
    ( (This)->lpVtbl -> get_RebarLayerSteel(This,index,As) ) 

#define IRCBeam2_get_RebarLayerDevFactor(This,index,devFactor)	\
    ( (This)->lpVtbl -> get_RebarLayerDevFactor(This,index,devFactor) ) 

#define IRCBeam2_GetRebarLayer(This,index,ds,As,devFactor)	\
    ( (This)->lpVtbl -> GetRebarLayer(This,index,ds,As,devFactor) ) 

#define IRCBeam2_RemoveRebarLayer(This,index)	\
    ( (This)->lpVtbl -> RemoveRebarLayer(This,index) ) 

#define IRCBeam2_ClearRebarLayers(This)	\
    ( (This)->lpVtbl -> ClearRebarLayers(This) ) 

#define IRCBeam2_AddStrandLayer(This,dps,Aps,devFactor)	\
    ( (This)->lpVtbl -> AddStrandLayer(This,dps,Aps,devFactor) ) 

#define IRCBeam2_get_StrandLayerCount(This,count)	\
    ( (This)->lpVtbl -> get_StrandLayerCount(This,count) ) 

#define IRCBeam2_get_StrandLayerDepth(This,index,dps)	\
    ( (This)->lpVtbl -> get_StrandLayerDepth(This,index,dps) ) 

#define IRCBeam2_get_StrandLayerSteel(This,index,Aps)	\
    ( (This)->lpVtbl -> get_StrandLayerSteel(This,index,Aps) ) 

#define IRCBeam2_get_StrandLayerDevFactor(This,index,devFactor)	\
    ( (This)->lpVtbl -> get_StrandLayerDevFactor(This,index,devFactor) ) 

#define IRCBeam2_GetStrandLayer(This,index,dps,Aps,devFactor)	\
    ( (This)->lpVtbl -> GetStrandLayer(This,index,dps,Aps,devFactor) ) 

#define IRCBeam2_RemoveStrandLayer(This,index)	\
    ( (This)->lpVtbl -> RemoveStrandLayer(This,index) ) 

#define IRCBeam2_ClearStrandLayers(This)	\
    ( (This)->lpVtbl -> ClearStrandLayers(This) ) 

#define IRCBeam2_get_fy(This,pVal)	\
    ( (This)->lpVtbl -> get_fy(This,pVal) ) 

#define IRCBeam2_put_fy(This,newVal)	\
    ( (This)->lpVtbl -> put_fy(This,newVal) ) 

#define IRCBeam2_get_fpu(This,pVal)	\
    ( (This)->lpVtbl -> get_fpu(This,pVal) ) 

#define IRCBeam2_put_fpu(This,newVal)	\
    ( (This)->lpVtbl -> put_fpu(This,newVal) ) 

#define IRCBeam2_get_fpy(This,pVal)	\
    ( (This)->lpVtbl -> get_fpy(This,pVal) ) 

#define IRCBeam2_put_fpy(This,newVal)	\
    ( (This)->lpVtbl -> put_fpy(This,newVal) ) 

#define IRCBeam2_get_fpe(This,pVal)	\
    ( (This)->lpVtbl -> get_fpe(This,pVal) ) 

#define IRCBeam2_put_fpe(This,newVal)	\
    ( (This)->lpVtbl -> put_fpe(This,newVal) ) 

#define IRCBeam2_get_FcSlab(This,pVal)	\
    ( (This)->lpVtbl -> get_FcSlab(This,pVal) ) 

#define IRCBeam2_put_FcSlab(This,newVal)	\
    ( (This)->lpVtbl -> put_FcSlab(This,newVal) ) 

#define IRCBeam2_get_FcBeam(This,pVal)	\
    ( (This)->lpVtbl -> get_FcBeam(This,pVal) ) 

#define IRCBeam2_put_FcBeam(This,newVal)	\
    ( (This)->lpVtbl -> put_FcBeam(This,newVal) ) 

#define IRCBeam2_get_Es(This,pVal)	\
    ( (This)->lpVtbl -> get_Es(This,pVal) ) 

#define IRCBeam2_put_Es(This,newVal)	\
    ( (This)->lpVtbl -> put_Es(This,newVal) ) 

#define IRCBeam2_get_Eps(This,pVal)	\
    ( (This)->lpVtbl -> get_Eps(This,pVal) ) 

#define IRCBeam2_put_Eps(This,newVal)	\
    ( (This)->lpVtbl -> put_Eps(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCBeam2_INTERFACE_DEFINED__ */


#ifndef __IRCBeam2Ex_INTERFACE_DEFINED__
#define __IRCBeam2Ex_INTERFACE_DEFINED__

/* interface IRCBeam2Ex */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCBeam2Ex;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F34B969D-6139-4A12-B75D-85D08C56A236")
    IRCBeam2Ex : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_b( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_b( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_hf( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_hf( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Beam( 
            /* [in] */ IShape *newVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE AddRebarLayer( 
            /* [in] */ Float64 ds,
            /* [in] */ Float64 As,
            /* [in] */ Float64 devFactor) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayerCount( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayerDepth( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *ds) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayerSteel( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *As) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarLayerDevFactor( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *devFactor) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE GetRebarLayer( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *ds,
            /* [out] */ Float64 *As,
            /* [out] */ Float64 *devFactor) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE RemoveRebarLayer( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ClearRebarLayers( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE AddStrandLayer( 
            /* [in] */ Float64 dps,
            /* [in] */ Float64 Aps,
            /* [in] */ Float64 devFactor) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandLayerCount( 
            /* [retval][out] */ CollectionIndexType *count) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandLayerDepth( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *dps) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandLayerSteel( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *Aps) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandLayerDevFactor( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *devFactor) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE GetStrandLayer( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *dps,
            /* [out] */ Float64 *Aps,
            /* [out] */ Float64 *devFactor) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE RemoveStrandLayer( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ClearStrandLayers( void) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fpu( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fpu( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fpy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fpy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fpe( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fpe( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_FcSlab( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_FcSlab( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_FcBeam( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_FcBeam( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Es( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Es( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Eps( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Eps( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCBeam2ExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCBeam2Ex * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCBeam2Ex * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCBeam2Ex * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_b )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_b )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hf )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_hf )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Beam )( 
            IRCBeam2Ex * This,
            /* [in] */ IShape *newVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *AddRebarLayer )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 ds,
            /* [in] */ Float64 As,
            /* [in] */ Float64 devFactor);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayerCount )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayerDepth )( 
            IRCBeam2Ex * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *ds);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayerSteel )( 
            IRCBeam2Ex * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *As);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarLayerDevFactor )( 
            IRCBeam2Ex * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *devFactor);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *GetRebarLayer )( 
            IRCBeam2Ex * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *ds,
            /* [out] */ Float64 *As,
            /* [out] */ Float64 *devFactor);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *RemoveRebarLayer )( 
            IRCBeam2Ex * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ClearRebarLayers )( 
            IRCBeam2Ex * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *AddStrandLayer )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 dps,
            /* [in] */ Float64 Aps,
            /* [in] */ Float64 devFactor);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandLayerCount )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ CollectionIndexType *count);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandLayerDepth )( 
            IRCBeam2Ex * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *dps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandLayerSteel )( 
            IRCBeam2Ex * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *Aps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandLayerDevFactor )( 
            IRCBeam2Ex * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *devFactor);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *GetStrandLayer )( 
            IRCBeam2Ex * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ Float64 *dps,
            /* [out] */ Float64 *Aps,
            /* [out] */ Float64 *devFactor);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *RemoveStrandLayer )( 
            IRCBeam2Ex * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ClearStrandLayers )( 
            IRCBeam2Ex * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fy )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fy )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fpu )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fpu )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fpy )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fpy )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fpe )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fpe )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FcSlab )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FcSlab )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FcBeam )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FcBeam )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Es )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Es )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Eps )( 
            IRCBeam2Ex * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Eps )( 
            IRCBeam2Ex * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IRCBeam2ExVtbl;

    interface IRCBeam2Ex
    {
        CONST_VTBL struct IRCBeam2ExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCBeam2Ex_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCBeam2Ex_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCBeam2Ex_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCBeam2Ex_get_b(This,pVal)	\
    ( (This)->lpVtbl -> get_b(This,pVal) ) 

#define IRCBeam2Ex_put_b(This,newVal)	\
    ( (This)->lpVtbl -> put_b(This,newVal) ) 

#define IRCBeam2Ex_get_hf(This,pVal)	\
    ( (This)->lpVtbl -> get_hf(This,pVal) ) 

#define IRCBeam2Ex_put_hf(This,newVal)	\
    ( (This)->lpVtbl -> put_hf(This,newVal) ) 

#define IRCBeam2Ex_get_Beam(This,pVal)	\
    ( (This)->lpVtbl -> get_Beam(This,pVal) ) 

#define IRCBeam2Ex_putref_Beam(This,newVal)	\
    ( (This)->lpVtbl -> putref_Beam(This,newVal) ) 

#define IRCBeam2Ex_AddRebarLayer(This,ds,As,devFactor)	\
    ( (This)->lpVtbl -> AddRebarLayer(This,ds,As,devFactor) ) 

#define IRCBeam2Ex_get_RebarLayerCount(This,count)	\
    ( (This)->lpVtbl -> get_RebarLayerCount(This,count) ) 

#define IRCBeam2Ex_get_RebarLayerDepth(This,index,ds)	\
    ( (This)->lpVtbl -> get_RebarLayerDepth(This,index,ds) ) 

#define IRCBeam2Ex_get_RebarLayerSteel(This,index,As)	\
    ( (This)->lpVtbl -> get_RebarLayerSteel(This,index,As) ) 

#define IRCBeam2Ex_get_RebarLayerDevFactor(This,index,devFactor)	\
    ( (This)->lpVtbl -> get_RebarLayerDevFactor(This,index,devFactor) ) 

#define IRCBeam2Ex_GetRebarLayer(This,index,ds,As,devFactor)	\
    ( (This)->lpVtbl -> GetRebarLayer(This,index,ds,As,devFactor) ) 

#define IRCBeam2Ex_RemoveRebarLayer(This,index)	\
    ( (This)->lpVtbl -> RemoveRebarLayer(This,index) ) 

#define IRCBeam2Ex_ClearRebarLayers(This)	\
    ( (This)->lpVtbl -> ClearRebarLayers(This) ) 

#define IRCBeam2Ex_AddStrandLayer(This,dps,Aps,devFactor)	\
    ( (This)->lpVtbl -> AddStrandLayer(This,dps,Aps,devFactor) ) 

#define IRCBeam2Ex_get_StrandLayerCount(This,count)	\
    ( (This)->lpVtbl -> get_StrandLayerCount(This,count) ) 

#define IRCBeam2Ex_get_StrandLayerDepth(This,index,dps)	\
    ( (This)->lpVtbl -> get_StrandLayerDepth(This,index,dps) ) 

#define IRCBeam2Ex_get_StrandLayerSteel(This,index,Aps)	\
    ( (This)->lpVtbl -> get_StrandLayerSteel(This,index,Aps) ) 

#define IRCBeam2Ex_get_StrandLayerDevFactor(This,index,devFactor)	\
    ( (This)->lpVtbl -> get_StrandLayerDevFactor(This,index,devFactor) ) 

#define IRCBeam2Ex_GetStrandLayer(This,index,dps,Aps,devFactor)	\
    ( (This)->lpVtbl -> GetStrandLayer(This,index,dps,Aps,devFactor) ) 

#define IRCBeam2Ex_RemoveStrandLayer(This,index)	\
    ( (This)->lpVtbl -> RemoveStrandLayer(This,index) ) 

#define IRCBeam2Ex_ClearStrandLayers(This)	\
    ( (This)->lpVtbl -> ClearStrandLayers(This) ) 

#define IRCBeam2Ex_get_fy(This,pVal)	\
    ( (This)->lpVtbl -> get_fy(This,pVal) ) 

#define IRCBeam2Ex_put_fy(This,newVal)	\
    ( (This)->lpVtbl -> put_fy(This,newVal) ) 

#define IRCBeam2Ex_get_fpu(This,pVal)	\
    ( (This)->lpVtbl -> get_fpu(This,pVal) ) 

#define IRCBeam2Ex_put_fpu(This,newVal)	\
    ( (This)->lpVtbl -> put_fpu(This,newVal) ) 

#define IRCBeam2Ex_get_fpy(This,pVal)	\
    ( (This)->lpVtbl -> get_fpy(This,pVal) ) 

#define IRCBeam2Ex_put_fpy(This,newVal)	\
    ( (This)->lpVtbl -> put_fpy(This,newVal) ) 

#define IRCBeam2Ex_get_fpe(This,pVal)	\
    ( (This)->lpVtbl -> get_fpe(This,pVal) ) 

#define IRCBeam2Ex_put_fpe(This,newVal)	\
    ( (This)->lpVtbl -> put_fpe(This,newVal) ) 

#define IRCBeam2Ex_get_FcSlab(This,pVal)	\
    ( (This)->lpVtbl -> get_FcSlab(This,pVal) ) 

#define IRCBeam2Ex_put_FcSlab(This,newVal)	\
    ( (This)->lpVtbl -> put_FcSlab(This,newVal) ) 

#define IRCBeam2Ex_get_FcBeam(This,pVal)	\
    ( (This)->lpVtbl -> get_FcBeam(This,pVal) ) 

#define IRCBeam2Ex_put_FcBeam(This,newVal)	\
    ( (This)->lpVtbl -> put_FcBeam(This,newVal) ) 

#define IRCBeam2Ex_get_Es(This,pVal)	\
    ( (This)->lpVtbl -> get_Es(This,pVal) ) 

#define IRCBeam2Ex_put_Es(This,newVal)	\
    ( (This)->lpVtbl -> put_Es(This,newVal) ) 

#define IRCBeam2Ex_get_Eps(This,pVal)	\
    ( (This)->lpVtbl -> get_Eps(This,pVal) ) 

#define IRCBeam2Ex_put_Eps(This,newVal)	\
    ( (This)->lpVtbl -> put_Eps(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCBeam2Ex_INTERFACE_DEFINED__ */


#ifndef __IRCSolution_INTERFACE_DEFINED__
#define __IRCSolution_INTERFACE_DEFINED__

/* interface IRCSolution */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCSolution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6AAEF03C-D41E-4206-9CA0-EDF467325F52")
    IRCSolution : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE InitSolution( 
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ Float64 fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb,
            /* [in] */ VARIANT_BOOL bOverReinforced) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Mn( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_IsOverReinforced( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_NeutralAxisDepth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fps( 
            /* [retval][out] */ Float64 *fps) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Cflange( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Cweb( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_T( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Yflange( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Yweb( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCSolutionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCSolution * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCSolution * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCSolution * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSolution )( 
            IRCSolution * This,
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ Float64 fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb,
            /* [in] */ VARIANT_BOOL bOverReinforced);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mn )( 
            IRCSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsOverReinforced )( 
            IRCSolution * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeutralAxisDepth )( 
            IRCSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fps )( 
            IRCSolution * This,
            /* [retval][out] */ Float64 *fps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cflange )( 
            IRCSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cweb )( 
            IRCSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T )( 
            IRCSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Yflange )( 
            IRCSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Yweb )( 
            IRCSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        END_INTERFACE
    } IRCSolutionVtbl;

    interface IRCSolution
    {
        CONST_VTBL struct IRCSolutionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCSolution_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCSolution_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCSolution_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCSolution_InitSolution(This,Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bOverReinforced)	\
    ( (This)->lpVtbl -> InitSolution(This,Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bOverReinforced) ) 

#define IRCSolution_get_Mn(This,pVal)	\
    ( (This)->lpVtbl -> get_Mn(This,pVal) ) 

#define IRCSolution_get_IsOverReinforced(This,pVal)	\
    ( (This)->lpVtbl -> get_IsOverReinforced(This,pVal) ) 

#define IRCSolution_get_NeutralAxisDepth(This,pVal)	\
    ( (This)->lpVtbl -> get_NeutralAxisDepth(This,pVal) ) 

#define IRCSolution_get_fps(This,fps)	\
    ( (This)->lpVtbl -> get_fps(This,fps) ) 

#define IRCSolution_get_Cflange(This,pVal)	\
    ( (This)->lpVtbl -> get_Cflange(This,pVal) ) 

#define IRCSolution_get_Cweb(This,pVal)	\
    ( (This)->lpVtbl -> get_Cweb(This,pVal) ) 

#define IRCSolution_get_T(This,pVal)	\
    ( (This)->lpVtbl -> get_T(This,pVal) ) 

#define IRCSolution_get_Yflange(This,pVal)	\
    ( (This)->lpVtbl -> get_Yflange(This,pVal) ) 

#define IRCSolution_get_Yweb(This,pVal)	\
    ( (This)->lpVtbl -> get_Yweb(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCSolution_INTERFACE_DEFINED__ */


#ifndef __ILRFDSolution_INTERFACE_DEFINED__
#define __ILRFDSolution_INTERFACE_DEFINED__

/* interface ILRFDSolution */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILRFDSolution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12CD51C9-087E-4608-9821-AE321C1CFA0C")
    ILRFDSolution : public IRCSolution
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitLRFDSolution( 
            /* [in] */ Float64 alpha1,
            /* [in] */ Float64 beta1,
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ Float64 fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb,
            /* [in] */ VARIANT_BOOL bOverReinforced) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Alpha1( 
            /* [retval][out] */ Float64 *pAlpha1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Beta1( 
            /* [retval][out] */ Float64 *pBeta1) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILRFDSolutionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILRFDSolution * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILRFDSolution * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILRFDSolution * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSolution )( 
            ILRFDSolution * This,
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ Float64 fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb,
            /* [in] */ VARIANT_BOOL bOverReinforced);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mn )( 
            ILRFDSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsOverReinforced )( 
            ILRFDSolution * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeutralAxisDepth )( 
            ILRFDSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fps )( 
            ILRFDSolution * This,
            /* [retval][out] */ Float64 *fps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cflange )( 
            ILRFDSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cweb )( 
            ILRFDSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T )( 
            ILRFDSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Yflange )( 
            ILRFDSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Yweb )( 
            ILRFDSolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        HRESULT ( STDMETHODCALLTYPE *InitLRFDSolution )( 
            ILRFDSolution * This,
            /* [in] */ Float64 alpha1,
            /* [in] */ Float64 beta1,
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ Float64 fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb,
            /* [in] */ VARIANT_BOOL bOverReinforced);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alpha1 )( 
            ILRFDSolution * This,
            /* [retval][out] */ Float64 *pAlpha1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beta1 )( 
            ILRFDSolution * This,
            /* [retval][out] */ Float64 *pBeta1);
        
        END_INTERFACE
    } ILRFDSolutionVtbl;

    interface ILRFDSolution
    {
        CONST_VTBL struct ILRFDSolutionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILRFDSolution_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILRFDSolution_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILRFDSolution_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILRFDSolution_InitSolution(This,Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bOverReinforced)	\
    ( (This)->lpVtbl -> InitSolution(This,Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bOverReinforced) ) 

#define ILRFDSolution_get_Mn(This,pVal)	\
    ( (This)->lpVtbl -> get_Mn(This,pVal) ) 

#define ILRFDSolution_get_IsOverReinforced(This,pVal)	\
    ( (This)->lpVtbl -> get_IsOverReinforced(This,pVal) ) 

#define ILRFDSolution_get_NeutralAxisDepth(This,pVal)	\
    ( (This)->lpVtbl -> get_NeutralAxisDepth(This,pVal) ) 

#define ILRFDSolution_get_fps(This,fps)	\
    ( (This)->lpVtbl -> get_fps(This,fps) ) 

#define ILRFDSolution_get_Cflange(This,pVal)	\
    ( (This)->lpVtbl -> get_Cflange(This,pVal) ) 

#define ILRFDSolution_get_Cweb(This,pVal)	\
    ( (This)->lpVtbl -> get_Cweb(This,pVal) ) 

#define ILRFDSolution_get_T(This,pVal)	\
    ( (This)->lpVtbl -> get_T(This,pVal) ) 

#define ILRFDSolution_get_Yflange(This,pVal)	\
    ( (This)->lpVtbl -> get_Yflange(This,pVal) ) 

#define ILRFDSolution_get_Yweb(This,pVal)	\
    ( (This)->lpVtbl -> get_Yweb(This,pVal) ) 


#define ILRFDSolution_InitLRFDSolution(This,alpha1,beta1,Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bOverReinforced)	\
    ( (This)->lpVtbl -> InitLRFDSolution(This,alpha1,beta1,Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bOverReinforced) ) 

#define ILRFDSolution_get_Alpha1(This,pAlpha1)	\
    ( (This)->lpVtbl -> get_Alpha1(This,pAlpha1) ) 

#define ILRFDSolution_get_Beta1(This,pBeta1)	\
    ( (This)->lpVtbl -> get_Beta1(This,pBeta1) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILRFDSolution_INTERFACE_DEFINED__ */


#ifndef __IRCSolutionEx_INTERFACE_DEFINED__
#define __IRCSolutionEx_INTERFACE_DEFINED__

/* interface IRCSolutionEx */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCSolutionEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BDBC6326-24AA-433D-9703-1B6E0EC083EB")
    IRCSolutionEx : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE InitSolution( 
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ IDblArray *fs,
            /* [in] */ IDblArray *fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Mn( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_NeutralAxisDepth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fs( 
            /* [retval][out] */ IDblArray **fs) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fps( 
            /* [retval][out] */ IDblArray **fps) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Cflange( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Cweb( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_T( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Yflange( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Yweb( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCSolutionExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCSolutionEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCSolutionEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCSolutionEx * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSolution )( 
            IRCSolutionEx * This,
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ IDblArray *fs,
            /* [in] */ IDblArray *fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mn )( 
            IRCSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeutralAxisDepth )( 
            IRCSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fs )( 
            IRCSolutionEx * This,
            /* [retval][out] */ IDblArray **fs);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fps )( 
            IRCSolutionEx * This,
            /* [retval][out] */ IDblArray **fps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cflange )( 
            IRCSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cweb )( 
            IRCSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T )( 
            IRCSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Yflange )( 
            IRCSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Yweb )( 
            IRCSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        END_INTERFACE
    } IRCSolutionExVtbl;

    interface IRCSolutionEx
    {
        CONST_VTBL struct IRCSolutionExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCSolutionEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCSolutionEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCSolutionEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCSolutionEx_InitSolution(This,Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb)	\
    ( (This)->lpVtbl -> InitSolution(This,Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb) ) 

#define IRCSolutionEx_get_Mn(This,pVal)	\
    ( (This)->lpVtbl -> get_Mn(This,pVal) ) 

#define IRCSolutionEx_get_NeutralAxisDepth(This,pVal)	\
    ( (This)->lpVtbl -> get_NeutralAxisDepth(This,pVal) ) 

#define IRCSolutionEx_get_fs(This,fs)	\
    ( (This)->lpVtbl -> get_fs(This,fs) ) 

#define IRCSolutionEx_get_fps(This,fps)	\
    ( (This)->lpVtbl -> get_fps(This,fps) ) 

#define IRCSolutionEx_get_Cflange(This,pVal)	\
    ( (This)->lpVtbl -> get_Cflange(This,pVal) ) 

#define IRCSolutionEx_get_Cweb(This,pVal)	\
    ( (This)->lpVtbl -> get_Cweb(This,pVal) ) 

#define IRCSolutionEx_get_T(This,pVal)	\
    ( (This)->lpVtbl -> get_T(This,pVal) ) 

#define IRCSolutionEx_get_Yflange(This,pVal)	\
    ( (This)->lpVtbl -> get_Yflange(This,pVal) ) 

#define IRCSolutionEx_get_Yweb(This,pVal)	\
    ( (This)->lpVtbl -> get_Yweb(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCSolutionEx_INTERFACE_DEFINED__ */


#ifndef __ILRFDSolutionEx_INTERFACE_DEFINED__
#define __ILRFDSolutionEx_INTERFACE_DEFINED__

/* interface ILRFDSolutionEx */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILRFDSolutionEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("53A8F18F-04C5-499d-8CFA-C73203344388")
    ILRFDSolutionEx : public IRCSolutionEx
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitLRFDSolution( 
            /* [in] */ Float64 alpha1,
            /* [in] */ Float64 beta1,
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ IDblArray *fs,
            /* [in] */ IDblArray *fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Alpha1( 
            /* [retval][out] */ Float64 *pAlpha1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Beta1( 
            /* [retval][out] */ Float64 *pBeta1) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILRFDSolutionExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILRFDSolutionEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILRFDSolutionEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILRFDSolutionEx * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSolution )( 
            ILRFDSolutionEx * This,
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ IDblArray *fs,
            /* [in] */ IDblArray *fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mn )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeutralAxisDepth )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fs )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ IDblArray **fs);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fps )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ IDblArray **fps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cflange )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cweb )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_T )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Yflange )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Yweb )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        HRESULT ( STDMETHODCALLTYPE *InitLRFDSolution )( 
            ILRFDSolutionEx * This,
            /* [in] */ Float64 alpha1,
            /* [in] */ Float64 beta1,
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ IDblArray *fs,
            /* [in] */ IDblArray *fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alpha1 )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ Float64 *pAlpha1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beta1 )( 
            ILRFDSolutionEx * This,
            /* [retval][out] */ Float64 *pBeta1);
        
        END_INTERFACE
    } ILRFDSolutionExVtbl;

    interface ILRFDSolutionEx
    {
        CONST_VTBL struct ILRFDSolutionExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILRFDSolutionEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILRFDSolutionEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILRFDSolutionEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILRFDSolutionEx_InitSolution(This,Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb)	\
    ( (This)->lpVtbl -> InitSolution(This,Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb) ) 

#define ILRFDSolutionEx_get_Mn(This,pVal)	\
    ( (This)->lpVtbl -> get_Mn(This,pVal) ) 

#define ILRFDSolutionEx_get_NeutralAxisDepth(This,pVal)	\
    ( (This)->lpVtbl -> get_NeutralAxisDepth(This,pVal) ) 

#define ILRFDSolutionEx_get_fs(This,fs)	\
    ( (This)->lpVtbl -> get_fs(This,fs) ) 

#define ILRFDSolutionEx_get_fps(This,fps)	\
    ( (This)->lpVtbl -> get_fps(This,fps) ) 

#define ILRFDSolutionEx_get_Cflange(This,pVal)	\
    ( (This)->lpVtbl -> get_Cflange(This,pVal) ) 

#define ILRFDSolutionEx_get_Cweb(This,pVal)	\
    ( (This)->lpVtbl -> get_Cweb(This,pVal) ) 

#define ILRFDSolutionEx_get_T(This,pVal)	\
    ( (This)->lpVtbl -> get_T(This,pVal) ) 

#define ILRFDSolutionEx_get_Yflange(This,pVal)	\
    ( (This)->lpVtbl -> get_Yflange(This,pVal) ) 

#define ILRFDSolutionEx_get_Yweb(This,pVal)	\
    ( (This)->lpVtbl -> get_Yweb(This,pVal) ) 


#define ILRFDSolutionEx_InitLRFDSolution(This,alpha1,beta1,Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb)	\
    ( (This)->lpVtbl -> InitLRFDSolution(This,alpha1,beta1,Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb) ) 

#define ILRFDSolutionEx_get_Alpha1(This,pAlpha1)	\
    ( (This)->lpVtbl -> get_Alpha1(This,pAlpha1) ) 

#define ILRFDSolutionEx_get_Beta1(This,pBeta1)	\
    ( (This)->lpVtbl -> get_Beta1(This,pBeta1) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILRFDSolutionEx_INTERFACE_DEFINED__ */


#ifndef __IRCSolver_INTERFACE_DEFINED__
#define __IRCSolver_INTERFACE_DEFINED__

/* interface IRCSolver */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10426F94-AA0A-4E23-B61F-02C1F1BD99A1")
    IRCSolver : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ IRCBeam *beam,
            /* [retval][out] */ IRCSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCSolver * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IRCSolver * This,
            /* [in] */ IRCBeam *beam,
            /* [retval][out] */ IRCSolution **solution);
        
        END_INTERFACE
    } IRCSolverVtbl;

    interface IRCSolver
    {
        CONST_VTBL struct IRCSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCSolver_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCSolver_INTERFACE_DEFINED__ */


#ifndef __IRCSolver2_INTERFACE_DEFINED__
#define __IRCSolver2_INTERFACE_DEFINED__

/* interface IRCSolver2 */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCSolver2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6D40161C-A224-491b-ABE8-8523A5E64A29")
    IRCSolver2 : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ IRCBeam2 *beam,
            /* [retval][out] */ IRCSolutionEx **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCSolver2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCSolver2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCSolver2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCSolver2 * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IRCSolver2 * This,
            /* [in] */ IRCBeam2 *beam,
            /* [retval][out] */ IRCSolutionEx **solution);
        
        END_INTERFACE
    } IRCSolver2Vtbl;

    interface IRCSolver2
    {
        CONST_VTBL struct IRCSolver2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCSolver2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCSolver2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCSolver2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCSolver2_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCSolver2_INTERFACE_DEFINED__ */


#ifndef __IRCSolver2Ex_INTERFACE_DEFINED__
#define __IRCSolver2Ex_INTERFACE_DEFINED__

/* interface IRCSolver2Ex */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCSolver2Ex;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5275D90C-BE12-4ca2-89C8-648E4EFDE53D")
    IRCSolver2Ex : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ IRCBeam2Ex *beam,
            /* [retval][out] */ IRCSolutionEx **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCSolver2ExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCSolver2Ex * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCSolver2Ex * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCSolver2Ex * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IRCSolver2Ex * This,
            /* [in] */ IRCBeam2Ex *beam,
            /* [retval][out] */ IRCSolutionEx **solution);
        
        END_INTERFACE
    } IRCSolver2ExVtbl;

    interface IRCSolver2Ex
    {
        CONST_VTBL struct IRCSolver2ExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCSolver2Ex_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCSolver2Ex_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCSolver2Ex_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCSolver2Ex_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCSolver2Ex_INTERFACE_DEFINED__ */


#ifndef __IPCISolver_INTERFACE_DEFINED__
#define __IPCISolver_INTERFACE_DEFINED__

/* interface IPCISolver */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPCISolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("83AA28E9-D6BE-4663-8E3E-FBC8E8371367")
    IPCISolver : public IRCSolver
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Tolerance( 
            /* [in] */ Float64 tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Tolerance( 
            /* [retval][out] */ Float64 *tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_StrandModel( 
            /* [in] */ IStressStrain *model) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandModel( 
            /* [retval][out] */ IStressStrain **model) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_RebarModel( 
            /* [in] */ IStressStrain *model) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarModel( 
            /* [retval][out] */ IStressStrain **model) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_UnitMode( 
            /* [in] */ SpecUnitType unitMode) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitMode( 
            /* [retval][out] */ SpecUnitType *unitMode) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_IsCflangeOverhangOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_IsCflangeOverhangOnly( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPCISolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPCISolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPCISolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPCISolver * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IPCISolver * This,
            /* [in] */ IRCBeam *beam,
            /* [retval][out] */ IRCSolution **solution);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Tolerance )( 
            IPCISolver * This,
            /* [in] */ Float64 tolerance);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tolerance )( 
            IPCISolver * This,
            /* [retval][out] */ Float64 *tolerance);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StrandModel )( 
            IPCISolver * This,
            /* [in] */ IStressStrain *model);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandModel )( 
            IPCISolver * This,
            /* [retval][out] */ IStressStrain **model);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarModel )( 
            IPCISolver * This,
            /* [in] */ IStressStrain *model);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarModel )( 
            IPCISolver * This,
            /* [retval][out] */ IStressStrain **model);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UnitMode )( 
            IPCISolver * This,
            /* [in] */ SpecUnitType unitMode);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitMode )( 
            IPCISolver * This,
            /* [retval][out] */ SpecUnitType *unitMode);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsCflangeOverhangOnly )( 
            IPCISolver * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsCflangeOverhangOnly )( 
            IPCISolver * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IPCISolverVtbl;

    interface IPCISolver
    {
        CONST_VTBL struct IPCISolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPCISolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPCISolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPCISolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPCISolver_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 


#define IPCISolver_put_Tolerance(This,tolerance)	\
    ( (This)->lpVtbl -> put_Tolerance(This,tolerance) ) 

#define IPCISolver_get_Tolerance(This,tolerance)	\
    ( (This)->lpVtbl -> get_Tolerance(This,tolerance) ) 

#define IPCISolver_putref_StrandModel(This,model)	\
    ( (This)->lpVtbl -> putref_StrandModel(This,model) ) 

#define IPCISolver_get_StrandModel(This,model)	\
    ( (This)->lpVtbl -> get_StrandModel(This,model) ) 

#define IPCISolver_putref_RebarModel(This,model)	\
    ( (This)->lpVtbl -> putref_RebarModel(This,model) ) 

#define IPCISolver_get_RebarModel(This,model)	\
    ( (This)->lpVtbl -> get_RebarModel(This,model) ) 

#define IPCISolver_put_UnitMode(This,unitMode)	\
    ( (This)->lpVtbl -> put_UnitMode(This,unitMode) ) 

#define IPCISolver_get_UnitMode(This,unitMode)	\
    ( (This)->lpVtbl -> get_UnitMode(This,unitMode) ) 

#define IPCISolver_get_IsCflangeOverhangOnly(This,pVal)	\
    ( (This)->lpVtbl -> get_IsCflangeOverhangOnly(This,pVal) ) 

#define IPCISolver_put_IsCflangeOverhangOnly(This,newVal)	\
    ( (This)->lpVtbl -> put_IsCflangeOverhangOnly(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPCISolver_INTERFACE_DEFINED__ */


#ifndef __INLSolver_INTERFACE_DEFINED__
#define __INLSolver_INTERFACE_DEFINED__

/* interface INLSolver */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_INLSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CC88A1EC-B5CF-4080-8BEF-6C93FFC2DDA5")
    INLSolver : public IRCSolver
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Slices( 
            /* [in] */ long nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Slices( 
            /* [retval][out] */ long *nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Tolerance( 
            /* [in] */ Float64 tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Tolerance( 
            /* [retval][out] */ Float64 *tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_SlabConcreteModel( 
            /* [in] */ IStressStrain *model) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_SlabConcreteModel( 
            /* [retval][out] */ IStressStrain **model) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_BeamConcreteModel( 
            /* [in] */ IStressStrain *model) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_BeamConcreteModel( 
            /* [retval][out] */ IStressStrain **model) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_StrandModel( 
            /* [in] */ IStressStrain *model) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandModel( 
            /* [retval][out] */ IStressStrain **model) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_RebarModel( 
            /* [in] */ IStressStrain *model) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarModel( 
            /* [retval][out] */ IStressStrain **model) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_IsCflangeOverhangOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_IsCflangeOverhangOnly( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_ConcreteCrushingStrain( 
            /* [in] */ Float64 ec) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ConcreteCrushingStrain( 
            /* [retval][out] */ Float64 *ec) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct INLSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INLSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INLSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INLSolver * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            INLSolver * This,
            /* [in] */ IRCBeam *beam,
            /* [retval][out] */ IRCSolution **solution);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slices )( 
            INLSolver * This,
            /* [in] */ long nSlices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slices )( 
            INLSolver * This,
            /* [retval][out] */ long *nSlices);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Tolerance )( 
            INLSolver * This,
            /* [in] */ Float64 tolerance);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tolerance )( 
            INLSolver * This,
            /* [retval][out] */ Float64 *tolerance);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SlabConcreteModel )( 
            INLSolver * This,
            /* [in] */ IStressStrain *model);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SlabConcreteModel )( 
            INLSolver * This,
            /* [retval][out] */ IStressStrain **model);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_BeamConcreteModel )( 
            INLSolver * This,
            /* [in] */ IStressStrain *model);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BeamConcreteModel )( 
            INLSolver * This,
            /* [retval][out] */ IStressStrain **model);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StrandModel )( 
            INLSolver * This,
            /* [in] */ IStressStrain *model);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandModel )( 
            INLSolver * This,
            /* [retval][out] */ IStressStrain **model);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarModel )( 
            INLSolver * This,
            /* [in] */ IStressStrain *model);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarModel )( 
            INLSolver * This,
            /* [retval][out] */ IStressStrain **model);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsCflangeOverhangOnly )( 
            INLSolver * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsCflangeOverhangOnly )( 
            INLSolver * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConcreteCrushingStrain )( 
            INLSolver * This,
            /* [in] */ Float64 ec);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConcreteCrushingStrain )( 
            INLSolver * This,
            /* [retval][out] */ Float64 *ec);
        
        END_INTERFACE
    } INLSolverVtbl;

    interface INLSolver
    {
        CONST_VTBL struct INLSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INLSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INLSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INLSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INLSolver_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 


#define INLSolver_put_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> put_Slices(This,nSlices) ) 

#define INLSolver_get_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> get_Slices(This,nSlices) ) 

#define INLSolver_put_Tolerance(This,tolerance)	\
    ( (This)->lpVtbl -> put_Tolerance(This,tolerance) ) 

#define INLSolver_get_Tolerance(This,tolerance)	\
    ( (This)->lpVtbl -> get_Tolerance(This,tolerance) ) 

#define INLSolver_putref_SlabConcreteModel(This,model)	\
    ( (This)->lpVtbl -> putref_SlabConcreteModel(This,model) ) 

#define INLSolver_get_SlabConcreteModel(This,model)	\
    ( (This)->lpVtbl -> get_SlabConcreteModel(This,model) ) 

#define INLSolver_putref_BeamConcreteModel(This,model)	\
    ( (This)->lpVtbl -> putref_BeamConcreteModel(This,model) ) 

#define INLSolver_get_BeamConcreteModel(This,model)	\
    ( (This)->lpVtbl -> get_BeamConcreteModel(This,model) ) 

#define INLSolver_putref_StrandModel(This,model)	\
    ( (This)->lpVtbl -> putref_StrandModel(This,model) ) 

#define INLSolver_get_StrandModel(This,model)	\
    ( (This)->lpVtbl -> get_StrandModel(This,model) ) 

#define INLSolver_putref_RebarModel(This,model)	\
    ( (This)->lpVtbl -> putref_RebarModel(This,model) ) 

#define INLSolver_get_RebarModel(This,model)	\
    ( (This)->lpVtbl -> get_RebarModel(This,model) ) 

#define INLSolver_get_IsCflangeOverhangOnly(This,pVal)	\
    ( (This)->lpVtbl -> get_IsCflangeOverhangOnly(This,pVal) ) 

#define INLSolver_put_IsCflangeOverhangOnly(This,newVal)	\
    ( (This)->lpVtbl -> put_IsCflangeOverhangOnly(This,newVal) ) 

#define INLSolver_put_ConcreteCrushingStrain(This,ec)	\
    ( (This)->lpVtbl -> put_ConcreteCrushingStrain(This,ec) ) 

#define INLSolver_get_ConcreteCrushingStrain(This,ec)	\
    ( (This)->lpVtbl -> get_ConcreteCrushingStrain(This,ec) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INLSolver_INTERFACE_DEFINED__ */


#ifndef __ILRFDSolver_INTERFACE_DEFINED__
#define __ILRFDSolver_INTERFACE_DEFINED__

/* interface ILRFDSolver */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILRFDSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("134FCA67-6350-44e1-A133-F3BC300CC9C7")
    ILRFDSolver : public IRCSolver
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_UnitMode( 
            /* [in] */ SpecUnitType unitMode) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitMode( 
            /* [retval][out] */ SpecUnitType *unitMode) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_IsCflangeOverhangOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_IsCflangeOverhangOnly( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILRFDSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILRFDSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILRFDSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILRFDSolver * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            ILRFDSolver * This,
            /* [in] */ IRCBeam *beam,
            /* [retval][out] */ IRCSolution **solution);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UnitMode )( 
            ILRFDSolver * This,
            /* [in] */ SpecUnitType unitMode);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitMode )( 
            ILRFDSolver * This,
            /* [retval][out] */ SpecUnitType *unitMode);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsCflangeOverhangOnly )( 
            ILRFDSolver * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsCflangeOverhangOnly )( 
            ILRFDSolver * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } ILRFDSolverVtbl;

    interface ILRFDSolver
    {
        CONST_VTBL struct ILRFDSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILRFDSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILRFDSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILRFDSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILRFDSolver_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 


#define ILRFDSolver_put_UnitMode(This,unitMode)	\
    ( (This)->lpVtbl -> put_UnitMode(This,unitMode) ) 

#define ILRFDSolver_get_UnitMode(This,unitMode)	\
    ( (This)->lpVtbl -> get_UnitMode(This,unitMode) ) 

#define ILRFDSolver_get_IsCflangeOverhangOnly(This,pVal)	\
    ( (This)->lpVtbl -> get_IsCflangeOverhangOnly(This,pVal) ) 

#define ILRFDSolver_put_IsCflangeOverhangOnly(This,newVal)	\
    ( (This)->lpVtbl -> put_IsCflangeOverhangOnly(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILRFDSolver_INTERFACE_DEFINED__ */


#ifndef __ILRFDSolver2_INTERFACE_DEFINED__
#define __ILRFDSolver2_INTERFACE_DEFINED__

/* interface ILRFDSolver2 */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILRFDSolver2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F5972D37-5F5D-41d7-B1F7-960430DE2367")
    ILRFDSolver2 : public IRCSolver
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Tolerance( 
            /* [in] */ Float64 tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Tolerance( 
            /* [retval][out] */ Float64 *tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_StrandModel( 
            /* [in] */ IStressStrain *model) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrandModel( 
            /* [retval][out] */ IStressStrain **model) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_RebarModel( 
            /* [in] */ IStressStrain *model) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_RebarModel( 
            /* [retval][out] */ IStressStrain **model) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_UnitMode( 
            /* [in] */ SpecUnitType unitMode) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitMode( 
            /* [retval][out] */ SpecUnitType *unitMode) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_IsCflangeOverhangOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_IsCflangeOverhangOnly( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILRFDSolver2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILRFDSolver2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILRFDSolver2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILRFDSolver2 * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            ILRFDSolver2 * This,
            /* [in] */ IRCBeam *beam,
            /* [retval][out] */ IRCSolution **solution);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Tolerance )( 
            ILRFDSolver2 * This,
            /* [in] */ Float64 tolerance);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tolerance )( 
            ILRFDSolver2 * This,
            /* [retval][out] */ Float64 *tolerance);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_StrandModel )( 
            ILRFDSolver2 * This,
            /* [in] */ IStressStrain *model);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrandModel )( 
            ILRFDSolver2 * This,
            /* [retval][out] */ IStressStrain **model);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RebarModel )( 
            ILRFDSolver2 * This,
            /* [in] */ IStressStrain *model);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RebarModel )( 
            ILRFDSolver2 * This,
            /* [retval][out] */ IStressStrain **model);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UnitMode )( 
            ILRFDSolver2 * This,
            /* [in] */ SpecUnitType unitMode);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitMode )( 
            ILRFDSolver2 * This,
            /* [retval][out] */ SpecUnitType *unitMode);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsCflangeOverhangOnly )( 
            ILRFDSolver2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsCflangeOverhangOnly )( 
            ILRFDSolver2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } ILRFDSolver2Vtbl;

    interface ILRFDSolver2
    {
        CONST_VTBL struct ILRFDSolver2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILRFDSolver2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILRFDSolver2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILRFDSolver2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILRFDSolver2_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 


#define ILRFDSolver2_put_Tolerance(This,tolerance)	\
    ( (This)->lpVtbl -> put_Tolerance(This,tolerance) ) 

#define ILRFDSolver2_get_Tolerance(This,tolerance)	\
    ( (This)->lpVtbl -> get_Tolerance(This,tolerance) ) 

#define ILRFDSolver2_putref_StrandModel(This,model)	\
    ( (This)->lpVtbl -> putref_StrandModel(This,model) ) 

#define ILRFDSolver2_get_StrandModel(This,model)	\
    ( (This)->lpVtbl -> get_StrandModel(This,model) ) 

#define ILRFDSolver2_putref_RebarModel(This,model)	\
    ( (This)->lpVtbl -> putref_RebarModel(This,model) ) 

#define ILRFDSolver2_get_RebarModel(This,model)	\
    ( (This)->lpVtbl -> get_RebarModel(This,model) ) 

#define ILRFDSolver2_put_UnitMode(This,unitMode)	\
    ( (This)->lpVtbl -> put_UnitMode(This,unitMode) ) 

#define ILRFDSolver2_get_UnitMode(This,unitMode)	\
    ( (This)->lpVtbl -> get_UnitMode(This,unitMode) ) 

#define ILRFDSolver2_get_IsCflangeOverhangOnly(This,pVal)	\
    ( (This)->lpVtbl -> get_IsCflangeOverhangOnly(This,pVal) ) 

#define ILRFDSolver2_put_IsCflangeOverhangOnly(This,newVal)	\
    ( (This)->lpVtbl -> put_IsCflangeOverhangOnly(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILRFDSolver2_INTERFACE_DEFINED__ */


#ifndef __ILFDSolver_INTERFACE_DEFINED__
#define __ILFDSolver_INTERFACE_DEFINED__

/* interface ILFDSolver */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ILFDSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B73E6FE9-0498-48f5-9057-513403A0E776")
    ILFDSolver : public IRCSolver
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_UnitMode( 
            /* [in] */ SpecUnitType unitMode) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitMode( 
            /* [retval][out] */ SpecUnitType *unitMode) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_IsCflangeOverhangOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_IsCflangeOverhangOnly( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILFDSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILFDSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILFDSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILFDSolver * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            ILFDSolver * This,
            /* [in] */ IRCBeam *beam,
            /* [retval][out] */ IRCSolution **solution);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UnitMode )( 
            ILFDSolver * This,
            /* [in] */ SpecUnitType unitMode);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitMode )( 
            ILFDSolver * This,
            /* [retval][out] */ SpecUnitType *unitMode);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsCflangeOverhangOnly )( 
            ILFDSolver * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsCflangeOverhangOnly )( 
            ILFDSolver * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } ILFDSolverVtbl;

    interface ILFDSolver
    {
        CONST_VTBL struct ILFDSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILFDSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILFDSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILFDSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILFDSolver_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 


#define ILFDSolver_put_UnitMode(This,unitMode)	\
    ( (This)->lpVtbl -> put_UnitMode(This,unitMode) ) 

#define ILFDSolver_get_UnitMode(This,unitMode)	\
    ( (This)->lpVtbl -> get_UnitMode(This,unitMode) ) 

#define ILFDSolver_get_IsCflangeOverhangOnly(This,pVal)	\
    ( (This)->lpVtbl -> get_IsCflangeOverhangOnly(This,pVal) ) 

#define ILFDSolver_put_IsCflangeOverhangOnly(This,newVal)	\
    ( (This)->lpVtbl -> put_IsCflangeOverhangOnly(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILFDSolver_INTERFACE_DEFINED__ */


#ifndef __IMixedSolver_INTERFACE_DEFINED__
#define __IMixedSolver_INTERFACE_DEFINED__

/* interface IMixedSolver */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IMixedSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F72175D0-CBAD-49B1-89EA-92F0948B89B7")
    IMixedSolver : public IRCSolver
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_UnitMode( 
            /* [in] */ SpecUnitType unitMode) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitMode( 
            /* [retval][out] */ SpecUnitType *unitMode) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_IsCflangeOverhangOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_IsCflangeOverhangOnly( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMixedSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixedSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixedSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixedSolver * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IMixedSolver * This,
            /* [in] */ IRCBeam *beam,
            /* [retval][out] */ IRCSolution **solution);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UnitMode )( 
            IMixedSolver * This,
            /* [in] */ SpecUnitType unitMode);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitMode )( 
            IMixedSolver * This,
            /* [retval][out] */ SpecUnitType *unitMode);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsCflangeOverhangOnly )( 
            IMixedSolver * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsCflangeOverhangOnly )( 
            IMixedSolver * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IMixedSolverVtbl;

    interface IMixedSolver
    {
        CONST_VTBL struct IMixedSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixedSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMixedSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMixedSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMixedSolver_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 


#define IMixedSolver_put_UnitMode(This,unitMode)	\
    ( (This)->lpVtbl -> put_UnitMode(This,unitMode) ) 

#define IMixedSolver_get_UnitMode(This,unitMode)	\
    ( (This)->lpVtbl -> get_UnitMode(This,unitMode) ) 

#define IMixedSolver_get_IsCflangeOverhangOnly(This,pVal)	\
    ( (This)->lpVtbl -> get_IsCflangeOverhangOnly(This,pVal) ) 

#define IMixedSolver_put_IsCflangeOverhangOnly(This,newVal)	\
    ( (This)->lpVtbl -> put_IsCflangeOverhangOnly(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMixedSolver_INTERFACE_DEFINED__ */


#ifndef __IUnconfinedConcrete_INTERFACE_DEFINED__
#define __IUnconfinedConcrete_INTERFACE_DEFINED__

/* interface IUnconfinedConcrete */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnconfinedConcrete;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CF4F8C9A-DA7B-4947-9671-FEBBB75A249A")
    IUnconfinedConcrete : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fc( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fc( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnconfinedConcreteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnconfinedConcrete * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnconfinedConcrete * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnconfinedConcrete * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fc )( 
            IUnconfinedConcrete * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fc )( 
            IUnconfinedConcrete * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IUnconfinedConcreteVtbl;

    interface IUnconfinedConcrete
    {
        CONST_VTBL struct IUnconfinedConcreteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnconfinedConcrete_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnconfinedConcrete_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnconfinedConcrete_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnconfinedConcrete_get_fc(This,pVal)	\
    ( (This)->lpVtbl -> get_fc(This,pVal) ) 

#define IUnconfinedConcrete_put_fc(This,newVal)	\
    ( (This)->lpVtbl -> put_fc(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnconfinedConcrete_INTERFACE_DEFINED__ */


#ifndef __IRebarModel_INTERFACE_DEFINED__
#define __IRebarModel_INTERFACE_DEFINED__

/* interface IRebarModel */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRebarModel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7DE82909-026E-4C57-A9A3-8F1CB6AFAF1F")
    IRebarModel : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ Float64 fy,
            /* [in] */ Float64 Es,
            /* [in] */ Float64 maxStrain) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Es( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Es( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MaxStrain( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MaxStrain( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRebarModelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRebarModel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRebarModel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRebarModel * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IRebarModel * This,
            /* [in] */ Float64 fy,
            /* [in] */ Float64 Es,
            /* [in] */ Float64 maxStrain);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fy )( 
            IRebarModel * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fy )( 
            IRebarModel * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Es )( 
            IRebarModel * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Es )( 
            IRebarModel * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxStrain )( 
            IRebarModel * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxStrain )( 
            IRebarModel * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IRebarModelVtbl;

    interface IRebarModel
    {
        CONST_VTBL struct IRebarModelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRebarModel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRebarModel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRebarModel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRebarModel_Init(This,fy,Es,maxStrain)	\
    ( (This)->lpVtbl -> Init(This,fy,Es,maxStrain) ) 

#define IRebarModel_get_fy(This,pVal)	\
    ( (This)->lpVtbl -> get_fy(This,pVal) ) 

#define IRebarModel_put_fy(This,newVal)	\
    ( (This)->lpVtbl -> put_fy(This,newVal) ) 

#define IRebarModel_get_Es(This,pVal)	\
    ( (This)->lpVtbl -> get_Es(This,pVal) ) 

#define IRebarModel_put_Es(This,newVal)	\
    ( (This)->lpVtbl -> put_Es(This,newVal) ) 

#define IRebarModel_get_MaxStrain(This,pVal)	\
    ( (This)->lpVtbl -> get_MaxStrain(This,pVal) ) 

#define IRebarModel_put_MaxStrain(This,newVal)	\
    ( (This)->lpVtbl -> put_MaxStrain(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRebarModel_INTERFACE_DEFINED__ */


#ifndef __IStrainHardenedRebarModel_INTERFACE_DEFINED__
#define __IStrainHardenedRebarModel_INTERFACE_DEFINED__

/* interface IStrainHardenedRebarModel */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IStrainHardenedRebarModel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1D62DA5C-9E49-4a8a-8BAF-3F4A3CEA6E2C")
    IStrainHardenedRebarModel : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ Float64 fy,
            /* [in] */ Float64 fu,
            /* [in] */ Float64 Es,
            /* [in] */ Float64 esh,
            /* [in] */ Float64 efr) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fu( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fu( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Es( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Es( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_esh( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_esh( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_efr( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_efr( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStrainHardenedRebarModelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStrainHardenedRebarModel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStrainHardenedRebarModel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStrainHardenedRebarModel * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IStrainHardenedRebarModel * This,
            /* [in] */ Float64 fy,
            /* [in] */ Float64 fu,
            /* [in] */ Float64 Es,
            /* [in] */ Float64 esh,
            /* [in] */ Float64 efr);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fy )( 
            IStrainHardenedRebarModel * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fy )( 
            IStrainHardenedRebarModel * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fu )( 
            IStrainHardenedRebarModel * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fu )( 
            IStrainHardenedRebarModel * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Es )( 
            IStrainHardenedRebarModel * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Es )( 
            IStrainHardenedRebarModel * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_esh )( 
            IStrainHardenedRebarModel * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_esh )( 
            IStrainHardenedRebarModel * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_efr )( 
            IStrainHardenedRebarModel * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_efr )( 
            IStrainHardenedRebarModel * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IStrainHardenedRebarModelVtbl;

    interface IStrainHardenedRebarModel
    {
        CONST_VTBL struct IStrainHardenedRebarModelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStrainHardenedRebarModel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStrainHardenedRebarModel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStrainHardenedRebarModel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStrainHardenedRebarModel_Init(This,fy,fu,Es,esh,efr)	\
    ( (This)->lpVtbl -> Init(This,fy,fu,Es,esh,efr) ) 

#define IStrainHardenedRebarModel_get_fy(This,pVal)	\
    ( (This)->lpVtbl -> get_fy(This,pVal) ) 

#define IStrainHardenedRebarModel_put_fy(This,newVal)	\
    ( (This)->lpVtbl -> put_fy(This,newVal) ) 

#define IStrainHardenedRebarModel_get_fu(This,pVal)	\
    ( (This)->lpVtbl -> get_fu(This,pVal) ) 

#define IStrainHardenedRebarModel_put_fu(This,newVal)	\
    ( (This)->lpVtbl -> put_fu(This,newVal) ) 

#define IStrainHardenedRebarModel_get_Es(This,pVal)	\
    ( (This)->lpVtbl -> get_Es(This,pVal) ) 

#define IStrainHardenedRebarModel_put_Es(This,newVal)	\
    ( (This)->lpVtbl -> put_Es(This,newVal) ) 

#define IStrainHardenedRebarModel_get_esh(This,pVal)	\
    ( (This)->lpVtbl -> get_esh(This,pVal) ) 

#define IStrainHardenedRebarModel_put_esh(This,newVal)	\
    ( (This)->lpVtbl -> put_esh(This,newVal) ) 

#define IStrainHardenedRebarModel_get_efr(This,pVal)	\
    ( (This)->lpVtbl -> get_efr(This,pVal) ) 

#define IStrainHardenedRebarModel_put_efr(This,newVal)	\
    ( (This)->lpVtbl -> put_efr(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStrainHardenedRebarModel_INTERFACE_DEFINED__ */


#ifndef __IPCISolution_INTERFACE_DEFINED__
#define __IPCISolution_INTERFACE_DEFINED__

/* interface IPCISolution */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPCISolution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("08C750A1-E0D4-493C-85AE-76234B1DDFA9")
    IPCISolution : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE InitSolution( 
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ Float64 fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb,
            /* [in] */ VARIANT_BOOL bOverReinforced,
            /* [in] */ Float64 avgBeta1) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_AvgBeta1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPCISolutionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPCISolution * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPCISolution * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPCISolution * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSolution )( 
            IPCISolution * This,
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ Float64 fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb,
            /* [in] */ VARIANT_BOOL bOverReinforced,
            /* [in] */ Float64 avgBeta1);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AvgBeta1 )( 
            IPCISolution * This,
            /* [retval][out] */ Float64 *pVal);
        
        END_INTERFACE
    } IPCISolutionVtbl;

    interface IPCISolution
    {
        CONST_VTBL struct IPCISolutionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPCISolution_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPCISolution_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPCISolution_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPCISolution_InitSolution(This,Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bOverReinforced,avgBeta1)	\
    ( (This)->lpVtbl -> InitSolution(This,Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bOverReinforced,avgBeta1) ) 

#define IPCISolution_get_AvgBeta1(This,pVal)	\
    ( (This)->lpVtbl -> get_AvgBeta1(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPCISolution_INTERFACE_DEFINED__ */


#ifndef __IPCISolutionEx_INTERFACE_DEFINED__
#define __IPCISolutionEx_INTERFACE_DEFINED__

/* interface IPCISolutionEx */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPCISolutionEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0D439ED6-A724-4B8C-8141-2B3BE6E87164")
    IPCISolutionEx : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE InitSolution( 
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ IDblArray *fs,
            /* [in] */ IDblArray *fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb,
            /* [in] */ Float64 avgBeta1) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_AvgBeta1( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPCISolutionExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPCISolutionEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPCISolutionEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPCISolutionEx * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSolution )( 
            IPCISolutionEx * This,
            /* [in] */ Float64 Mn,
            /* [in] */ Float64 c,
            /* [in] */ IDblArray *fs,
            /* [in] */ IDblArray *fps,
            /* [in] */ Float64 Cflange,
            /* [in] */ Float64 Cweb,
            /* [in] */ Float64 T,
            /* [in] */ Float64 Yflange,
            /* [in] */ Float64 Yweb,
            /* [in] */ Float64 avgBeta1);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AvgBeta1 )( 
            IPCISolutionEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        END_INTERFACE
    } IPCISolutionExVtbl;

    interface IPCISolutionEx
    {
        CONST_VTBL struct IPCISolutionExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPCISolutionEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPCISolutionEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPCISolutionEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPCISolutionEx_InitSolution(This,Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb,avgBeta1)	\
    ( (This)->lpVtbl -> InitSolution(This,Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb,avgBeta1) ) 

#define IPCISolutionEx_get_AvgBeta1(This,pVal)	\
    ( (This)->lpVtbl -> get_AvgBeta1(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPCISolutionEx_INTERFACE_DEFINED__ */


#ifndef __IRoundColumn_INTERFACE_DEFINED__
#define __IRoundColumn_INTERFACE_DEFINED__

/* interface IRoundColumn */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRoundColumn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("018F0AFC-E51D-47D1-8477-974EA1C8192A")
    IRoundColumn : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Diameter( 
            /* [in] */ Float64 dia) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Diameter( 
            /* [retval][out] */ Float64 *dia) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Cover( 
            /* [in] */ Float64 cover) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Cover( 
            /* [retval][out] */ Float64 *cover) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_As( 
            /* [in] */ Float64 as) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_As( 
            /* [retval][out] */ Float64 *as) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fc( 
            /* [in] */ Float64 fc) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fc( 
            /* [retval][out] */ Float64 *fc) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fy( 
            /* [in] */ Float64 fy) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fy( 
            /* [retval][out] */ Float64 *fy) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Es( 
            /* [in] */ Float64 es) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Es( 
            /* [retval][out] */ Float64 *es) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeInteraction( 
            /* [in] */ long nSteps,
            /* [retval][out] */ IPoint2dCollection **points) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeInteractionEx( 
            /* [in] */ long nSteps,
            /* [in] */ Float64 ecl,
            /* [in] */ Float64 etl,
            /* [out] */ IPoint2dCollection **ppUnfactored,
            /* [out] */ IPoint2dCollection **ppFactored) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRoundColumnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRoundColumn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRoundColumn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRoundColumn * This);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Diameter )( 
            IRoundColumn * This,
            /* [in] */ Float64 dia);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Diameter )( 
            IRoundColumn * This,
            /* [retval][out] */ Float64 *dia);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Cover )( 
            IRoundColumn * This,
            /* [in] */ Float64 cover);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cover )( 
            IRoundColumn * This,
            /* [retval][out] */ Float64 *cover);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_As )( 
            IRoundColumn * This,
            /* [in] */ Float64 as);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_As )( 
            IRoundColumn * This,
            /* [retval][out] */ Float64 *as);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fc )( 
            IRoundColumn * This,
            /* [in] */ Float64 fc);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fc )( 
            IRoundColumn * This,
            /* [retval][out] */ Float64 *fc);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fy )( 
            IRoundColumn * This,
            /* [in] */ Float64 fy);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fy )( 
            IRoundColumn * This,
            /* [retval][out] */ Float64 *fy);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Es )( 
            IRoundColumn * This,
            /* [in] */ Float64 es);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Es )( 
            IRoundColumn * This,
            /* [retval][out] */ Float64 *es);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeInteraction )( 
            IRoundColumn * This,
            /* [in] */ long nSteps,
            /* [retval][out] */ IPoint2dCollection **points);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeInteractionEx )( 
            IRoundColumn * This,
            /* [in] */ long nSteps,
            /* [in] */ Float64 ecl,
            /* [in] */ Float64 etl,
            /* [out] */ IPoint2dCollection **ppUnfactored,
            /* [out] */ IPoint2dCollection **ppFactored);
        
        END_INTERFACE
    } IRoundColumnVtbl;

    interface IRoundColumn
    {
        CONST_VTBL struct IRoundColumnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRoundColumn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRoundColumn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRoundColumn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRoundColumn_put_Diameter(This,dia)	\
    ( (This)->lpVtbl -> put_Diameter(This,dia) ) 

#define IRoundColumn_get_Diameter(This,dia)	\
    ( (This)->lpVtbl -> get_Diameter(This,dia) ) 

#define IRoundColumn_put_Cover(This,cover)	\
    ( (This)->lpVtbl -> put_Cover(This,cover) ) 

#define IRoundColumn_get_Cover(This,cover)	\
    ( (This)->lpVtbl -> get_Cover(This,cover) ) 

#define IRoundColumn_put_As(This,as)	\
    ( (This)->lpVtbl -> put_As(This,as) ) 

#define IRoundColumn_get_As(This,as)	\
    ( (This)->lpVtbl -> get_As(This,as) ) 

#define IRoundColumn_put_fc(This,fc)	\
    ( (This)->lpVtbl -> put_fc(This,fc) ) 

#define IRoundColumn_get_fc(This,fc)	\
    ( (This)->lpVtbl -> get_fc(This,fc) ) 

#define IRoundColumn_put_fy(This,fy)	\
    ( (This)->lpVtbl -> put_fy(This,fy) ) 

#define IRoundColumn_get_fy(This,fy)	\
    ( (This)->lpVtbl -> get_fy(This,fy) ) 

#define IRoundColumn_put_Es(This,es)	\
    ( (This)->lpVtbl -> put_Es(This,es) ) 

#define IRoundColumn_get_Es(This,es)	\
    ( (This)->lpVtbl -> get_Es(This,es) ) 

#define IRoundColumn_ComputeInteraction(This,nSteps,points)	\
    ( (This)->lpVtbl -> ComputeInteraction(This,nSteps,points) ) 

#define IRoundColumn_ComputeInteractionEx(This,nSteps,ecl,etl,ppUnfactored,ppFactored)	\
    ( (This)->lpVtbl -> ComputeInteractionEx(This,nSteps,ecl,etl,ppUnfactored,ppFactored) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRoundColumn_INTERFACE_DEFINED__ */


#ifndef __IGeneralSection_INTERFACE_DEFINED__
#define __IGeneralSection_INTERFACE_DEFINED__

/* interface IGeneralSection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGeneralSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FE1EB4AB-F67A-459f-9360-6194916FDE37")
    IGeneralSection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE AddShape( 
            /* [in] */ IShape *pShape,
            /* [in] */ IStressStrain *pfgMaterial,
            /* [in] */ IStressStrain *pbgMaterial,
            /* [in] */ Float64 ei) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ShapeCount( 
            /* [retval][out] */ CollectionIndexType *nShapes) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [in] */ CollectionIndexType shapeIdx,
            /* [retval][out] */ IShape **pShape) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Shape( 
            /* [in] */ CollectionIndexType shapeIdx,
            /* [in] */ IShape *pShape) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [in] */ CollectionIndexType shapeIdx,
            /* [retval][out] */ IStressStrain **pMaterial) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_ForegroundMaterial( 
            /* [in] */ CollectionIndexType shapeIdx,
            /* [in] */ IStressStrain *pMaterial) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [in] */ CollectionIndexType shapeIdx,
            /* [retval][out] */ IStressStrain **pMaterial) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_BackgroundMaterial( 
            /* [in] */ CollectionIndexType shapeIdx,
            /* [in] */ IStressStrain *pMaterial) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_InitialStrain( 
            /* [in] */ CollectionIndexType shapeIdx,
            /* [retval][out] */ Float64 *ei) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_InitialStrain( 
            /* [in] */ CollectionIndexType shapeIdx,
            /* [in] */ Float64 ei) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGeneralSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeneralSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeneralSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeneralSection * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *AddShape )( 
            IGeneralSection * This,
            /* [in] */ IShape *pShape,
            /* [in] */ IStressStrain *pfgMaterial,
            /* [in] */ IStressStrain *pbgMaterial,
            /* [in] */ Float64 ei);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapeCount )( 
            IGeneralSection * This,
            /* [retval][out] */ CollectionIndexType *nShapes);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IGeneralSection * This,
            /* [in] */ CollectionIndexType shapeIdx,
            /* [retval][out] */ IShape **pShape);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Shape )( 
            IGeneralSection * This,
            /* [in] */ CollectionIndexType shapeIdx,
            /* [in] */ IShape *pShape);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            IGeneralSection * This,
            /* [in] */ CollectionIndexType shapeIdx,
            /* [retval][out] */ IStressStrain **pMaterial);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ForegroundMaterial )( 
            IGeneralSection * This,
            /* [in] */ CollectionIndexType shapeIdx,
            /* [in] */ IStressStrain *pMaterial);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            IGeneralSection * This,
            /* [in] */ CollectionIndexType shapeIdx,
            /* [retval][out] */ IStressStrain **pMaterial);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_BackgroundMaterial )( 
            IGeneralSection * This,
            /* [in] */ CollectionIndexType shapeIdx,
            /* [in] */ IStressStrain *pMaterial);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InitialStrain )( 
            IGeneralSection * This,
            /* [in] */ CollectionIndexType shapeIdx,
            /* [retval][out] */ Float64 *ei);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InitialStrain )( 
            IGeneralSection * This,
            /* [in] */ CollectionIndexType shapeIdx,
            /* [in] */ Float64 ei);
        
        END_INTERFACE
    } IGeneralSectionVtbl;

    interface IGeneralSection
    {
        CONST_VTBL struct IGeneralSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeneralSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGeneralSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGeneralSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGeneralSection_AddShape(This,pShape,pfgMaterial,pbgMaterial,ei)	\
    ( (This)->lpVtbl -> AddShape(This,pShape,pfgMaterial,pbgMaterial,ei) ) 

#define IGeneralSection_get_ShapeCount(This,nShapes)	\
    ( (This)->lpVtbl -> get_ShapeCount(This,nShapes) ) 

#define IGeneralSection_get_Shape(This,shapeIdx,pShape)	\
    ( (This)->lpVtbl -> get_Shape(This,shapeIdx,pShape) ) 

#define IGeneralSection_putref_Shape(This,shapeIdx,pShape)	\
    ( (This)->lpVtbl -> putref_Shape(This,shapeIdx,pShape) ) 

#define IGeneralSection_get_ForegroundMaterial(This,shapeIdx,pMaterial)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,shapeIdx,pMaterial) ) 

#define IGeneralSection_putref_ForegroundMaterial(This,shapeIdx,pMaterial)	\
    ( (This)->lpVtbl -> putref_ForegroundMaterial(This,shapeIdx,pMaterial) ) 

#define IGeneralSection_get_BackgroundMaterial(This,shapeIdx,pMaterial)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,shapeIdx,pMaterial) ) 

#define IGeneralSection_putref_BackgroundMaterial(This,shapeIdx,pMaterial)	\
    ( (This)->lpVtbl -> putref_BackgroundMaterial(This,shapeIdx,pMaterial) ) 

#define IGeneralSection_get_InitialStrain(This,shapeIdx,ei)	\
    ( (This)->lpVtbl -> get_InitialStrain(This,shapeIdx,ei) ) 

#define IGeneralSection_put_InitialStrain(This,shapeIdx,ei)	\
    ( (This)->lpVtbl -> put_InitialStrain(This,shapeIdx,ei) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGeneralSection_INTERFACE_DEFINED__ */


#ifndef __IGeneralSectionSlice_INTERFACE_DEFINED__
#define __IGeneralSectionSlice_INTERFACE_DEFINED__

/* interface IGeneralSectionSlice */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGeneralSectionSlice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D079B9D4-BEB3-40e3-B603-016F1D29CBCD")
    IGeneralSectionSlice : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE InitSlice( 
            /* [in] */ IShape *pShape,
            /* [in] */ Float64 A,
            /* [in] */ Float64 cgX,
            /* [in] */ Float64 cgY,
            /* [in] */ Float64 strain,
            /* [in] */ Float64 fgStress,
            /* [in] */ Float64 bgStress,
            /* [in] */ IStressStrain *pfgMaterial,
            /* [in] */ IStressStrain *pbgMaterial) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Area( 
            /* [retval][out] */ Float64 *pArea) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_CG( 
            /* [retval][out] */ IPoint2d **pCG) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Strain( 
            /* [retval][out] */ Float64 *pStrain) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundStress( 
            /* [retval][out] */ Float64 *pfgStress) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundStress( 
            /* [retval][out] */ Float64 *pbgStress) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pShape) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundMaterial( 
            /* [retval][out] */ IStressStrain **pMaterial) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundMaterial( 
            /* [retval][out] */ IStressStrain **pMaterial) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGeneralSectionSliceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeneralSectionSlice * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeneralSectionSlice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeneralSectionSlice * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSlice )( 
            IGeneralSectionSlice * This,
            /* [in] */ IShape *pShape,
            /* [in] */ Float64 A,
            /* [in] */ Float64 cgX,
            /* [in] */ Float64 cgY,
            /* [in] */ Float64 strain,
            /* [in] */ Float64 fgStress,
            /* [in] */ Float64 bgStress,
            /* [in] */ IStressStrain *pfgMaterial,
            /* [in] */ IStressStrain *pbgMaterial);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Area )( 
            IGeneralSectionSlice * This,
            /* [retval][out] */ Float64 *pArea);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CG )( 
            IGeneralSectionSlice * This,
            /* [retval][out] */ IPoint2d **pCG);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strain )( 
            IGeneralSectionSlice * This,
            /* [retval][out] */ Float64 *pStrain);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundStress )( 
            IGeneralSectionSlice * This,
            /* [retval][out] */ Float64 *pfgStress);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundStress )( 
            IGeneralSectionSlice * This,
            /* [retval][out] */ Float64 *pbgStress);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            IGeneralSectionSlice * This,
            /* [retval][out] */ IShape **pShape);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundMaterial )( 
            IGeneralSectionSlice * This,
            /* [retval][out] */ IStressStrain **pMaterial);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundMaterial )( 
            IGeneralSectionSlice * This,
            /* [retval][out] */ IStressStrain **pMaterial);
        
        END_INTERFACE
    } IGeneralSectionSliceVtbl;

    interface IGeneralSectionSlice
    {
        CONST_VTBL struct IGeneralSectionSliceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeneralSectionSlice_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGeneralSectionSlice_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGeneralSectionSlice_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGeneralSectionSlice_InitSlice(This,pShape,A,cgX,cgY,strain,fgStress,bgStress,pfgMaterial,pbgMaterial)	\
    ( (This)->lpVtbl -> InitSlice(This,pShape,A,cgX,cgY,strain,fgStress,bgStress,pfgMaterial,pbgMaterial) ) 

#define IGeneralSectionSlice_get_Area(This,pArea)	\
    ( (This)->lpVtbl -> get_Area(This,pArea) ) 

#define IGeneralSectionSlice_get_CG(This,pCG)	\
    ( (This)->lpVtbl -> get_CG(This,pCG) ) 

#define IGeneralSectionSlice_get_Strain(This,pStrain)	\
    ( (This)->lpVtbl -> get_Strain(This,pStrain) ) 

#define IGeneralSectionSlice_get_ForegroundStress(This,pfgStress)	\
    ( (This)->lpVtbl -> get_ForegroundStress(This,pfgStress) ) 

#define IGeneralSectionSlice_get_BackgroundStress(This,pbgStress)	\
    ( (This)->lpVtbl -> get_BackgroundStress(This,pbgStress) ) 

#define IGeneralSectionSlice_get_Shape(This,pShape)	\
    ( (This)->lpVtbl -> get_Shape(This,pShape) ) 

#define IGeneralSectionSlice_get_ForegroundMaterial(This,pMaterial)	\
    ( (This)->lpVtbl -> get_ForegroundMaterial(This,pMaterial) ) 

#define IGeneralSectionSlice_get_BackgroundMaterial(This,pMaterial)	\
    ( (This)->lpVtbl -> get_BackgroundMaterial(This,pMaterial) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGeneralSectionSlice_INTERFACE_DEFINED__ */


#ifndef __IGeneralSectionSolution_INTERFACE_DEFINED__
#define __IGeneralSectionSolution_INTERFACE_DEFINED__

/* interface IGeneralSectionSolution */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGeneralSectionSolution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("52EF7B24-5383-4c47-AED7-DF25CC071B78")
    IGeneralSectionSolution : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE InitSolution( 
            /* [in] */ Float64 fz,
            /* [in] */ Float64 mx,
            /* [in] */ Float64 my,
            /* [in] */ ILine2d *neutralAxis,
            /* [in] */ IPoint2d *cgC,
            /* [in] */ Float64 C,
            /* [in] */ IPoint2d *cgT,
            /* [in] */ Float64 T,
            /* [in] */ IUnkArray *slices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Fz( 
            /* [retval][out] */ Float64 *fz) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Mx( 
            /* [retval][out] */ Float64 *mx) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_My( 
            /* [retval][out] */ Float64 *my) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_NeutralAxis( 
            /* [retval][out] */ ILine2d **neutralAxis) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_NeutralAxisDirection( 
            /* [retval][out] */ Float64 *neutralAxis) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_CompressionResultant( 
            /* [retval][out] */ Float64 *c) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_TensionResultant( 
            /* [retval][out] */ Float64 *t) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_CompressionResultantLocation( 
            /* [retval][out] */ IPoint2d **cgC) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_TensionResultantLocation( 
            /* [retval][out] */ IPoint2d **cgT) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_SliceCount( 
            /* [retval][out] */ CollectionIndexType *nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Slice( 
            /* [in] */ CollectionIndexType sliceIdx,
            /* [retval][out] */ IGeneralSectionSlice **pSlice) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGeneralSectionSolutionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeneralSectionSolution * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeneralSectionSolution * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeneralSectionSolution * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSolution )( 
            IGeneralSectionSolution * This,
            /* [in] */ Float64 fz,
            /* [in] */ Float64 mx,
            /* [in] */ Float64 my,
            /* [in] */ ILine2d *neutralAxis,
            /* [in] */ IPoint2d *cgC,
            /* [in] */ Float64 C,
            /* [in] */ IPoint2d *cgT,
            /* [in] */ Float64 T,
            /* [in] */ IUnkArray *slices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fz )( 
            IGeneralSectionSolution * This,
            /* [retval][out] */ Float64 *fz);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mx )( 
            IGeneralSectionSolution * This,
            /* [retval][out] */ Float64 *mx);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_My )( 
            IGeneralSectionSolution * This,
            /* [retval][out] */ Float64 *my);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeutralAxis )( 
            IGeneralSectionSolution * This,
            /* [retval][out] */ ILine2d **neutralAxis);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeutralAxisDirection )( 
            IGeneralSectionSolution * This,
            /* [retval][out] */ Float64 *neutralAxis);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CompressionResultant )( 
            IGeneralSectionSolution * This,
            /* [retval][out] */ Float64 *c);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TensionResultant )( 
            IGeneralSectionSolution * This,
            /* [retval][out] */ Float64 *t);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CompressionResultantLocation )( 
            IGeneralSectionSolution * This,
            /* [retval][out] */ IPoint2d **cgC);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TensionResultantLocation )( 
            IGeneralSectionSolution * This,
            /* [retval][out] */ IPoint2d **cgT);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SliceCount )( 
            IGeneralSectionSolution * This,
            /* [retval][out] */ CollectionIndexType *nSlices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slice )( 
            IGeneralSectionSolution * This,
            /* [in] */ CollectionIndexType sliceIdx,
            /* [retval][out] */ IGeneralSectionSlice **pSlice);
        
        END_INTERFACE
    } IGeneralSectionSolutionVtbl;

    interface IGeneralSectionSolution
    {
        CONST_VTBL struct IGeneralSectionSolutionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeneralSectionSolution_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGeneralSectionSolution_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGeneralSectionSolution_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGeneralSectionSolution_InitSolution(This,fz,mx,my,neutralAxis,cgC,C,cgT,T,slices)	\
    ( (This)->lpVtbl -> InitSolution(This,fz,mx,my,neutralAxis,cgC,C,cgT,T,slices) ) 

#define IGeneralSectionSolution_get_Fz(This,fz)	\
    ( (This)->lpVtbl -> get_Fz(This,fz) ) 

#define IGeneralSectionSolution_get_Mx(This,mx)	\
    ( (This)->lpVtbl -> get_Mx(This,mx) ) 

#define IGeneralSectionSolution_get_My(This,my)	\
    ( (This)->lpVtbl -> get_My(This,my) ) 

#define IGeneralSectionSolution_get_NeutralAxis(This,neutralAxis)	\
    ( (This)->lpVtbl -> get_NeutralAxis(This,neutralAxis) ) 

#define IGeneralSectionSolution_get_NeutralAxisDirection(This,neutralAxis)	\
    ( (This)->lpVtbl -> get_NeutralAxisDirection(This,neutralAxis) ) 

#define IGeneralSectionSolution_get_CompressionResultant(This,c)	\
    ( (This)->lpVtbl -> get_CompressionResultant(This,c) ) 

#define IGeneralSectionSolution_get_TensionResultant(This,t)	\
    ( (This)->lpVtbl -> get_TensionResultant(This,t) ) 

#define IGeneralSectionSolution_get_CompressionResultantLocation(This,cgC)	\
    ( (This)->lpVtbl -> get_CompressionResultantLocation(This,cgC) ) 

#define IGeneralSectionSolution_get_TensionResultantLocation(This,cgT)	\
    ( (This)->lpVtbl -> get_TensionResultantLocation(This,cgT) ) 

#define IGeneralSectionSolution_get_SliceCount(This,nSlices)	\
    ( (This)->lpVtbl -> get_SliceCount(This,nSlices) ) 

#define IGeneralSectionSolution_get_Slice(This,sliceIdx,pSlice)	\
    ( (This)->lpVtbl -> get_Slice(This,sliceIdx,pSlice) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGeneralSectionSolution_INTERFACE_DEFINED__ */


#ifndef __IGeneralSectionSolver_INTERFACE_DEFINED__
#define __IGeneralSectionSolver_INTERFACE_DEFINED__

/* interface IGeneralSectionSolver */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGeneralSectionSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4BE67D1E-A214-4bb3-8B10-5FA0380153C7")
    IGeneralSectionSolver : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Section( 
            /* [in] */ IGeneralSection *pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ IGeneralSection **pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Slices( 
            /* [in] */ long nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Slices( 
            /* [retval][out] */ long *nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_SliceGrowthFactor( 
            /* [in] */ Float64 sliceGrowthFactor) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_SliceGrowthFactor( 
            /* [retval][out] */ Float64 *sliceGrowthFactor) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ IPlane3d *strainPlane,
            /* [retval][out] */ IGeneralSectionSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGeneralSectionSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeneralSectionSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeneralSectionSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeneralSectionSolver * This);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Section )( 
            IGeneralSectionSolver * This,
            /* [in] */ IGeneralSection *pSection);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IGeneralSectionSolver * This,
            /* [retval][out] */ IGeneralSection **pSection);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slices )( 
            IGeneralSectionSolver * This,
            /* [in] */ long nSlices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slices )( 
            IGeneralSectionSolver * This,
            /* [retval][out] */ long *nSlices);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SliceGrowthFactor )( 
            IGeneralSectionSolver * This,
            /* [in] */ Float64 sliceGrowthFactor);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SliceGrowthFactor )( 
            IGeneralSectionSolver * This,
            /* [retval][out] */ Float64 *sliceGrowthFactor);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IGeneralSectionSolver * This,
            /* [in] */ IPlane3d *strainPlane,
            /* [retval][out] */ IGeneralSectionSolution **solution);
        
        END_INTERFACE
    } IGeneralSectionSolverVtbl;

    interface IGeneralSectionSolver
    {
        CONST_VTBL struct IGeneralSectionSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeneralSectionSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGeneralSectionSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGeneralSectionSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGeneralSectionSolver_putref_Section(This,pSection)	\
    ( (This)->lpVtbl -> putref_Section(This,pSection) ) 

#define IGeneralSectionSolver_get_Section(This,pSection)	\
    ( (This)->lpVtbl -> get_Section(This,pSection) ) 

#define IGeneralSectionSolver_put_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> put_Slices(This,nSlices) ) 

#define IGeneralSectionSolver_get_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> get_Slices(This,nSlices) ) 

#define IGeneralSectionSolver_put_SliceGrowthFactor(This,sliceGrowthFactor)	\
    ( (This)->lpVtbl -> put_SliceGrowthFactor(This,sliceGrowthFactor) ) 

#define IGeneralSectionSolver_get_SliceGrowthFactor(This,sliceGrowthFactor)	\
    ( (This)->lpVtbl -> get_SliceGrowthFactor(This,sliceGrowthFactor) ) 

#define IGeneralSectionSolver_Solve(This,strainPlane,solution)	\
    ( (This)->lpVtbl -> Solve(This,strainPlane,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGeneralSectionSolver_INTERFACE_DEFINED__ */


#ifndef __IMomentCurvatureSolution_INTERFACE_DEFINED__
#define __IMomentCurvatureSolution_INTERFACE_DEFINED__

/* interface IMomentCurvatureSolution */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IMomentCurvatureSolution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7FA3E79D-9C64-4333-9BA7-5FF84F71D1C5")
    IMomentCurvatureSolution : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MaxMoment( 
            /* [retval][out] */ Float64 *Mmax) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MaxMomentCurvature( 
            /* [retval][out] */ Float64 *k) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE PeakCapacity( 
            /* [out] */ Float64 *Mmax,
            /* [out] */ Float64 *k) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Moment( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ Float64 *Mmax) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Curvature( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ Float64 *k) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrainPlane( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IPlane3d **StrainPlane) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_PointCount( 
            /* [retval][out] */ CollectionIndexType *nPoints) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMomentCurvatureSolutionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMomentCurvatureSolution * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMomentCurvatureSolution * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMomentCurvatureSolution * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxMoment )( 
            IMomentCurvatureSolution * This,
            /* [retval][out] */ Float64 *Mmax);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxMomentCurvature )( 
            IMomentCurvatureSolution * This,
            /* [retval][out] */ Float64 *k);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *PeakCapacity )( 
            IMomentCurvatureSolution * This,
            /* [out] */ Float64 *Mmax,
            /* [out] */ Float64 *k);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Moment )( 
            IMomentCurvatureSolution * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ Float64 *Mmax);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Curvature )( 
            IMomentCurvatureSolution * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ Float64 *k);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrainPlane )( 
            IMomentCurvatureSolution * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IPlane3d **StrainPlane);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointCount )( 
            IMomentCurvatureSolution * This,
            /* [retval][out] */ CollectionIndexType *nPoints);
        
        END_INTERFACE
    } IMomentCurvatureSolutionVtbl;

    interface IMomentCurvatureSolution
    {
        CONST_VTBL struct IMomentCurvatureSolutionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMomentCurvatureSolution_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMomentCurvatureSolution_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMomentCurvatureSolution_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMomentCurvatureSolution_get_MaxMoment(This,Mmax)	\
    ( (This)->lpVtbl -> get_MaxMoment(This,Mmax) ) 

#define IMomentCurvatureSolution_get_MaxMomentCurvature(This,k)	\
    ( (This)->lpVtbl -> get_MaxMomentCurvature(This,k) ) 

#define IMomentCurvatureSolution_PeakCapacity(This,Mmax,k)	\
    ( (This)->lpVtbl -> PeakCapacity(This,Mmax,k) ) 

#define IMomentCurvatureSolution_get_Moment(This,idx,Mmax)	\
    ( (This)->lpVtbl -> get_Moment(This,idx,Mmax) ) 

#define IMomentCurvatureSolution_get_Curvature(This,idx,k)	\
    ( (This)->lpVtbl -> get_Curvature(This,idx,k) ) 

#define IMomentCurvatureSolution_get_StrainPlane(This,idx,StrainPlane)	\
    ( (This)->lpVtbl -> get_StrainPlane(This,idx,StrainPlane) ) 

#define IMomentCurvatureSolution_get_PointCount(This,nPoints)	\
    ( (This)->lpVtbl -> get_PointCount(This,nPoints) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMomentCurvatureSolution_INTERFACE_DEFINED__ */


#ifndef __IMomentCurvatureSolver_INTERFACE_DEFINED__
#define __IMomentCurvatureSolver_INTERFACE_DEFINED__

/* interface IMomentCurvatureSolver */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IMomentCurvatureSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F3B5724-C503-44d1-A6E0-68D195CA2442")
    IMomentCurvatureSolver : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Section( 
            /* [in] */ IGeneralSection *pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ IGeneralSection **pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Slices( 
            /* [in] */ long nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Slices( 
            /* [retval][out] */ long *nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_AxialTolerance( 
            /* [in] */ Float64 tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_AxialTolerance( 
            /* [retval][out] */ Float64 *tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MaxIterations( 
            /* [in] */ long maxIter) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MaxIterations( 
            /* [retval][out] */ long *maxIter) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_InitialCurvatureStep( 
            /* [in] */ Float64 k) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_InitialCurvatureStep( 
            /* [retval][out] */ Float64 *k) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ Float64 Fz,
            /* [in] */ Float64 angle,
            /* [retval][out] */ IMomentCurvatureSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMomentCurvatureSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMomentCurvatureSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMomentCurvatureSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMomentCurvatureSolver * This);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Section )( 
            IMomentCurvatureSolver * This,
            /* [in] */ IGeneralSection *pSection);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IMomentCurvatureSolver * This,
            /* [retval][out] */ IGeneralSection **pSection);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slices )( 
            IMomentCurvatureSolver * This,
            /* [in] */ long nSlices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slices )( 
            IMomentCurvatureSolver * This,
            /* [retval][out] */ long *nSlices);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AxialTolerance )( 
            IMomentCurvatureSolver * This,
            /* [in] */ Float64 tolerance);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AxialTolerance )( 
            IMomentCurvatureSolver * This,
            /* [retval][out] */ Float64 *tolerance);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxIterations )( 
            IMomentCurvatureSolver * This,
            /* [in] */ long maxIter);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxIterations )( 
            IMomentCurvatureSolver * This,
            /* [retval][out] */ long *maxIter);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InitialCurvatureStep )( 
            IMomentCurvatureSolver * This,
            /* [in] */ Float64 k);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InitialCurvatureStep )( 
            IMomentCurvatureSolver * This,
            /* [retval][out] */ Float64 *k);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IMomentCurvatureSolver * This,
            /* [in] */ Float64 Fz,
            /* [in] */ Float64 angle,
            /* [retval][out] */ IMomentCurvatureSolution **solution);
        
        END_INTERFACE
    } IMomentCurvatureSolverVtbl;

    interface IMomentCurvatureSolver
    {
        CONST_VTBL struct IMomentCurvatureSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMomentCurvatureSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMomentCurvatureSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMomentCurvatureSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMomentCurvatureSolver_putref_Section(This,pSection)	\
    ( (This)->lpVtbl -> putref_Section(This,pSection) ) 

#define IMomentCurvatureSolver_get_Section(This,pSection)	\
    ( (This)->lpVtbl -> get_Section(This,pSection) ) 

#define IMomentCurvatureSolver_put_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> put_Slices(This,nSlices) ) 

#define IMomentCurvatureSolver_get_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> get_Slices(This,nSlices) ) 

#define IMomentCurvatureSolver_put_AxialTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> put_AxialTolerance(This,tolerance) ) 

#define IMomentCurvatureSolver_get_AxialTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> get_AxialTolerance(This,tolerance) ) 

#define IMomentCurvatureSolver_put_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> put_MaxIterations(This,maxIter) ) 

#define IMomentCurvatureSolver_get_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> get_MaxIterations(This,maxIter) ) 

#define IMomentCurvatureSolver_put_InitialCurvatureStep(This,k)	\
    ( (This)->lpVtbl -> put_InitialCurvatureStep(This,k) ) 

#define IMomentCurvatureSolver_get_InitialCurvatureStep(This,k)	\
    ( (This)->lpVtbl -> get_InitialCurvatureStep(This,k) ) 

#define IMomentCurvatureSolver_Solve(This,Fz,angle,solution)	\
    ( (This)->lpVtbl -> Solve(This,Fz,angle,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMomentCurvatureSolver_INTERFACE_DEFINED__ */


#ifndef __IMomentCapacitySolution_INTERFACE_DEFINED__
#define __IMomentCapacitySolution_INTERFACE_DEFINED__

/* interface IMomentCapacitySolution */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IMomentCapacitySolution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2BD13F88-3CF5-4c5d-8CF8-83DBA81AB361")
    IMomentCapacitySolution : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE InitSolution( 
            /* [in] */ Float64 fz,
            /* [in] */ Float64 mx,
            /* [in] */ Float64 my,
            /* [in] */ IPlane3d *strainPlane,
            /* [in] */ ILine2d *neutralAxis,
            /* [in] */ IPoint2d *cgC,
            /* [in] */ Float64 C,
            /* [in] */ IPoint2d *cgT,
            /* [in] */ Float64 T,
            /* [in] */ IGeneralSectionSolution *pSolution) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Fz( 
            /* [retval][out] */ Float64 *fz) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Mx( 
            /* [retval][out] */ Float64 *mx) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_My( 
            /* [retval][out] */ Float64 *my) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StrainPlane( 
            /* [retval][out] */ IPlane3d **strainPlane) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_NeutralAxis( 
            /* [retval][out] */ ILine2d **neutralAxis) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_NeutralAxisDirection( 
            /* [retval][out] */ Float64 *angle) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_CompressionResultant( 
            /* [retval][out] */ Float64 *c) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_TensionResultant( 
            /* [retval][out] */ Float64 *t) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_CompressionResultantLocation( 
            /* [retval][out] */ IPoint2d **cgC) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_TensionResultantLocation( 
            /* [retval][out] */ IPoint2d **cgT) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_GeneralSectionSolution( 
            /* [retval][out] */ IGeneralSectionSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMomentCapacitySolutionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMomentCapacitySolution * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMomentCapacitySolution * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMomentCapacitySolution * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSolution )( 
            IMomentCapacitySolution * This,
            /* [in] */ Float64 fz,
            /* [in] */ Float64 mx,
            /* [in] */ Float64 my,
            /* [in] */ IPlane3d *strainPlane,
            /* [in] */ ILine2d *neutralAxis,
            /* [in] */ IPoint2d *cgC,
            /* [in] */ Float64 C,
            /* [in] */ IPoint2d *cgT,
            /* [in] */ Float64 T,
            /* [in] */ IGeneralSectionSolution *pSolution);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fz )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ Float64 *fz);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mx )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ Float64 *mx);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_My )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ Float64 *my);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrainPlane )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ IPlane3d **strainPlane);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeutralAxis )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ ILine2d **neutralAxis);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeutralAxisDirection )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ Float64 *angle);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CompressionResultant )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ Float64 *c);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TensionResultant )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ Float64 *t);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CompressionResultantLocation )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ IPoint2d **cgC);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TensionResultantLocation )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ IPoint2d **cgT);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GeneralSectionSolution )( 
            IMomentCapacitySolution * This,
            /* [retval][out] */ IGeneralSectionSolution **solution);
        
        END_INTERFACE
    } IMomentCapacitySolutionVtbl;

    interface IMomentCapacitySolution
    {
        CONST_VTBL struct IMomentCapacitySolutionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMomentCapacitySolution_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMomentCapacitySolution_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMomentCapacitySolution_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMomentCapacitySolution_InitSolution(This,fz,mx,my,strainPlane,neutralAxis,cgC,C,cgT,T,pSolution)	\
    ( (This)->lpVtbl -> InitSolution(This,fz,mx,my,strainPlane,neutralAxis,cgC,C,cgT,T,pSolution) ) 

#define IMomentCapacitySolution_get_Fz(This,fz)	\
    ( (This)->lpVtbl -> get_Fz(This,fz) ) 

#define IMomentCapacitySolution_get_Mx(This,mx)	\
    ( (This)->lpVtbl -> get_Mx(This,mx) ) 

#define IMomentCapacitySolution_get_My(This,my)	\
    ( (This)->lpVtbl -> get_My(This,my) ) 

#define IMomentCapacitySolution_get_StrainPlane(This,strainPlane)	\
    ( (This)->lpVtbl -> get_StrainPlane(This,strainPlane) ) 

#define IMomentCapacitySolution_get_NeutralAxis(This,neutralAxis)	\
    ( (This)->lpVtbl -> get_NeutralAxis(This,neutralAxis) ) 

#define IMomentCapacitySolution_get_NeutralAxisDirection(This,angle)	\
    ( (This)->lpVtbl -> get_NeutralAxisDirection(This,angle) ) 

#define IMomentCapacitySolution_get_CompressionResultant(This,c)	\
    ( (This)->lpVtbl -> get_CompressionResultant(This,c) ) 

#define IMomentCapacitySolution_get_TensionResultant(This,t)	\
    ( (This)->lpVtbl -> get_TensionResultant(This,t) ) 

#define IMomentCapacitySolution_get_CompressionResultantLocation(This,cgC)	\
    ( (This)->lpVtbl -> get_CompressionResultantLocation(This,cgC) ) 

#define IMomentCapacitySolution_get_TensionResultantLocation(This,cgT)	\
    ( (This)->lpVtbl -> get_TensionResultantLocation(This,cgT) ) 

#define IMomentCapacitySolution_get_GeneralSectionSolution(This,solution)	\
    ( (This)->lpVtbl -> get_GeneralSectionSolution(This,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMomentCapacitySolution_INTERFACE_DEFINED__ */


#ifndef __IMomentCapacitySolver_INTERFACE_DEFINED__
#define __IMomentCapacitySolver_INTERFACE_DEFINED__

/* interface IMomentCapacitySolver */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IMomentCapacitySolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4B19FD5-ADD9-43bf-B2C6-EF65D59CD3C9")
    IMomentCapacitySolver : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Section( 
            /* [in] */ IGeneralSection *pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ IGeneralSection **pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Slices( 
            /* [in] */ long nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Slices( 
            /* [retval][out] */ long *nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_SliceGrowthFactor( 
            /* [in] */ Float64 sliceGrowthFactor) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_SliceGrowthFactor( 
            /* [retval][out] */ Float64 *sliceGrowthFactor) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_AxialTolerance( 
            /* [in] */ Float64 tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_AxialTolerance( 
            /* [retval][out] */ Float64 *tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MaxIterations( 
            /* [in] */ long maxIter) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MaxIterations( 
            /* [retval][out] */ long *maxIter) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ Float64 Fz,
            /* [in] */ Float64 angle,
            /* [in] */ Float64 k_or_ec,
            /* [in] */ SolutionMethod solutionMethod,
            /* [retval][out] */ IMomentCapacitySolution **solution) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_PlasticCentroid( 
            /* [retval][out] */ IPoint2d **pcg) = 0;
        
        virtual /* [helpcontext] */ HRESULT STDMETHODCALLTYPE CompressionLimit( 
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo) = 0;
        
        virtual /* [helpcontext] */ HRESULT STDMETHODCALLTYPE TensionLimit( 
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMomentCapacitySolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMomentCapacitySolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMomentCapacitySolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMomentCapacitySolver * This);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Section )( 
            IMomentCapacitySolver * This,
            /* [in] */ IGeneralSection *pSection);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IMomentCapacitySolver * This,
            /* [retval][out] */ IGeneralSection **pSection);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slices )( 
            IMomentCapacitySolver * This,
            /* [in] */ long nSlices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slices )( 
            IMomentCapacitySolver * This,
            /* [retval][out] */ long *nSlices);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SliceGrowthFactor )( 
            IMomentCapacitySolver * This,
            /* [in] */ Float64 sliceGrowthFactor);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SliceGrowthFactor )( 
            IMomentCapacitySolver * This,
            /* [retval][out] */ Float64 *sliceGrowthFactor);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AxialTolerance )( 
            IMomentCapacitySolver * This,
            /* [in] */ Float64 tolerance);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AxialTolerance )( 
            IMomentCapacitySolver * This,
            /* [retval][out] */ Float64 *tolerance);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxIterations )( 
            IMomentCapacitySolver * This,
            /* [in] */ long maxIter);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxIterations )( 
            IMomentCapacitySolver * This,
            /* [retval][out] */ long *maxIter);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IMomentCapacitySolver * This,
            /* [in] */ Float64 Fz,
            /* [in] */ Float64 angle,
            /* [in] */ Float64 k_or_ec,
            /* [in] */ SolutionMethod solutionMethod,
            /* [retval][out] */ IMomentCapacitySolution **solution);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PlasticCentroid )( 
            IMomentCapacitySolver * This,
            /* [retval][out] */ IPoint2d **pcg);
        
        /* [helpcontext] */ HRESULT ( STDMETHODCALLTYPE *CompressionLimit )( 
            IMomentCapacitySolver * This,
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo);
        
        /* [helpcontext] */ HRESULT ( STDMETHODCALLTYPE *TensionLimit )( 
            IMomentCapacitySolver * This,
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo);
        
        END_INTERFACE
    } IMomentCapacitySolverVtbl;

    interface IMomentCapacitySolver
    {
        CONST_VTBL struct IMomentCapacitySolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMomentCapacitySolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMomentCapacitySolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMomentCapacitySolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMomentCapacitySolver_putref_Section(This,pSection)	\
    ( (This)->lpVtbl -> putref_Section(This,pSection) ) 

#define IMomentCapacitySolver_get_Section(This,pSection)	\
    ( (This)->lpVtbl -> get_Section(This,pSection) ) 

#define IMomentCapacitySolver_put_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> put_Slices(This,nSlices) ) 

#define IMomentCapacitySolver_get_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> get_Slices(This,nSlices) ) 

#define IMomentCapacitySolver_put_SliceGrowthFactor(This,sliceGrowthFactor)	\
    ( (This)->lpVtbl -> put_SliceGrowthFactor(This,sliceGrowthFactor) ) 

#define IMomentCapacitySolver_get_SliceGrowthFactor(This,sliceGrowthFactor)	\
    ( (This)->lpVtbl -> get_SliceGrowthFactor(This,sliceGrowthFactor) ) 

#define IMomentCapacitySolver_put_AxialTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> put_AxialTolerance(This,tolerance) ) 

#define IMomentCapacitySolver_get_AxialTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> get_AxialTolerance(This,tolerance) ) 

#define IMomentCapacitySolver_put_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> put_MaxIterations(This,maxIter) ) 

#define IMomentCapacitySolver_get_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> get_MaxIterations(This,maxIter) ) 

#define IMomentCapacitySolver_Solve(This,Fz,angle,k_or_ec,solutionMethod,solution)	\
    ( (This)->lpVtbl -> Solve(This,Fz,angle,k_or_ec,solutionMethod,solution) ) 

#define IMomentCapacitySolver_get_PlasticCentroid(This,pcg)	\
    ( (This)->lpVtbl -> get_PlasticCentroid(This,pcg) ) 

#define IMomentCapacitySolver_CompressionLimit(This,Fz,Mx,My,eo)	\
    ( (This)->lpVtbl -> CompressionLimit(This,Fz,Mx,My,eo) ) 

#define IMomentCapacitySolver_TensionLimit(This,Fz,Mx,My,eo)	\
    ( (This)->lpVtbl -> TensionLimit(This,Fz,Mx,My,eo) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMomentCapacitySolver_INTERFACE_DEFINED__ */


#ifndef __IInteractionCurveSolution_INTERFACE_DEFINED__
#define __IInteractionCurveSolution_INTERFACE_DEFINED__

/* interface IInteractionCurveSolution */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IInteractionCurveSolution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("169DAD38-B2EC-4d1a-AD6B-B04671662AFA")
    IInteractionCurveSolution : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_NeutralAxisDirection( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *angle) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MomentCurvatureSolution( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IMomentCurvatureSolution **solution) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE AddSolutionPoint( 
            /* [in] */ Float64 angle,
            /* [in] */ IMomentCurvatureSolution *solution) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_SolutionPointCount( 
            /* [retval][out] */ CollectionIndexType *nPoints) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IInteractionCurveSolutionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInteractionCurveSolution * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInteractionCurveSolution * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInteractionCurveSolution * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeutralAxisDirection )( 
            IInteractionCurveSolution * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ Float64 *angle);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MomentCurvatureSolution )( 
            IInteractionCurveSolution * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IMomentCurvatureSolution **solution);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *AddSolutionPoint )( 
            IInteractionCurveSolution * This,
            /* [in] */ Float64 angle,
            /* [in] */ IMomentCurvatureSolution *solution);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SolutionPointCount )( 
            IInteractionCurveSolution * This,
            /* [retval][out] */ CollectionIndexType *nPoints);
        
        END_INTERFACE
    } IInteractionCurveSolutionVtbl;

    interface IInteractionCurveSolution
    {
        CONST_VTBL struct IInteractionCurveSolutionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInteractionCurveSolution_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInteractionCurveSolution_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInteractionCurveSolution_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInteractionCurveSolution_get_NeutralAxisDirection(This,index,angle)	\
    ( (This)->lpVtbl -> get_NeutralAxisDirection(This,index,angle) ) 

#define IInteractionCurveSolution_get_MomentCurvatureSolution(This,index,solution)	\
    ( (This)->lpVtbl -> get_MomentCurvatureSolution(This,index,solution) ) 

#define IInteractionCurveSolution_AddSolutionPoint(This,angle,solution)	\
    ( (This)->lpVtbl -> AddSolutionPoint(This,angle,solution) ) 

#define IInteractionCurveSolution_get_SolutionPointCount(This,nPoints)	\
    ( (This)->lpVtbl -> get_SolutionPointCount(This,nPoints) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInteractionCurveSolution_INTERFACE_DEFINED__ */


#ifndef __IInteractionCurveSolver_INTERFACE_DEFINED__
#define __IInteractionCurveSolver_INTERFACE_DEFINED__

/* interface IInteractionCurveSolver */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IInteractionCurveSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("750A8100-D7EB-4b17-AE36-9DDDFEF6888B")
    IInteractionCurveSolver : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Section( 
            /* [in] */ IGeneralSection *pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ IGeneralSection **pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Slices( 
            /* [in] */ long nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Slices( 
            /* [retval][out] */ long *nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_AxialTolerance( 
            /* [in] */ Float64 tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_AxialTolerance( 
            /* [retval][out] */ Float64 *tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MaxIterations( 
            /* [in] */ long maxIter) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MaxIterations( 
            /* [retval][out] */ long *maxIter) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_InitialCurvatureStep( 
            /* [in] */ Float64 k) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_InitialCurvatureStep( 
            /* [retval][out] */ Float64 *k) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ Float64 Fz,
            /* [in] */ long naIncrement,
            /* [retval][out] */ IInteractionCurveSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IInteractionCurveSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInteractionCurveSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInteractionCurveSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInteractionCurveSolver * This);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Section )( 
            IInteractionCurveSolver * This,
            /* [in] */ IGeneralSection *pSection);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IInteractionCurveSolver * This,
            /* [retval][out] */ IGeneralSection **pSection);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slices )( 
            IInteractionCurveSolver * This,
            /* [in] */ long nSlices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slices )( 
            IInteractionCurveSolver * This,
            /* [retval][out] */ long *nSlices);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AxialTolerance )( 
            IInteractionCurveSolver * This,
            /* [in] */ Float64 tolerance);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AxialTolerance )( 
            IInteractionCurveSolver * This,
            /* [retval][out] */ Float64 *tolerance);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxIterations )( 
            IInteractionCurveSolver * This,
            /* [in] */ long maxIter);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxIterations )( 
            IInteractionCurveSolver * This,
            /* [retval][out] */ long *maxIter);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InitialCurvatureStep )( 
            IInteractionCurveSolver * This,
            /* [in] */ Float64 k);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InitialCurvatureStep )( 
            IInteractionCurveSolver * This,
            /* [retval][out] */ Float64 *k);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IInteractionCurveSolver * This,
            /* [in] */ Float64 Fz,
            /* [in] */ long naIncrement,
            /* [retval][out] */ IInteractionCurveSolution **solution);
        
        END_INTERFACE
    } IInteractionCurveSolverVtbl;

    interface IInteractionCurveSolver
    {
        CONST_VTBL struct IInteractionCurveSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInteractionCurveSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInteractionCurveSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInteractionCurveSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInteractionCurveSolver_putref_Section(This,pSection)	\
    ( (This)->lpVtbl -> putref_Section(This,pSection) ) 

#define IInteractionCurveSolver_get_Section(This,pSection)	\
    ( (This)->lpVtbl -> get_Section(This,pSection) ) 

#define IInteractionCurveSolver_put_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> put_Slices(This,nSlices) ) 

#define IInteractionCurveSolver_get_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> get_Slices(This,nSlices) ) 

#define IInteractionCurveSolver_put_AxialTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> put_AxialTolerance(This,tolerance) ) 

#define IInteractionCurveSolver_get_AxialTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> get_AxialTolerance(This,tolerance) ) 

#define IInteractionCurveSolver_put_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> put_MaxIterations(This,maxIter) ) 

#define IInteractionCurveSolver_get_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> get_MaxIterations(This,maxIter) ) 

#define IInteractionCurveSolver_put_InitialCurvatureStep(This,k)	\
    ( (This)->lpVtbl -> put_InitialCurvatureStep(This,k) ) 

#define IInteractionCurveSolver_get_InitialCurvatureStep(This,k)	\
    ( (This)->lpVtbl -> get_InitialCurvatureStep(This,k) ) 

#define IInteractionCurveSolver_Solve(This,Fz,naIncrement,solution)	\
    ( (This)->lpVtbl -> Solve(This,Fz,naIncrement,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInteractionCurveSolver_INTERFACE_DEFINED__ */


#ifndef __IInteractionCapacityCurveSolution_INTERFACE_DEFINED__
#define __IInteractionCapacityCurveSolution_INTERFACE_DEFINED__

/* interface IInteractionCapacityCurveSolution */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IInteractionCapacityCurveSolution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EBFB4042-E5DC-4378-BFDB-8890C77A4E3D")
    IInteractionCapacityCurveSolution : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MomentCapacitySolution( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IMomentCapacitySolution **solution) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE AddSolutionPoint( 
            /* [in] */ IMomentCapacitySolution *solution) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_SolutionPointCount( 
            /* [retval][out] */ CollectionIndexType *nPoints) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IInteractionCapacityCurveSolutionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInteractionCapacityCurveSolution * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInteractionCapacityCurveSolution * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInteractionCapacityCurveSolution * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MomentCapacitySolution )( 
            IInteractionCapacityCurveSolution * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IMomentCapacitySolution **solution);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *AddSolutionPoint )( 
            IInteractionCapacityCurveSolution * This,
            /* [in] */ IMomentCapacitySolution *solution);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SolutionPointCount )( 
            IInteractionCapacityCurveSolution * This,
            /* [retval][out] */ CollectionIndexType *nPoints);
        
        END_INTERFACE
    } IInteractionCapacityCurveSolutionVtbl;

    interface IInteractionCapacityCurveSolution
    {
        CONST_VTBL struct IInteractionCapacityCurveSolutionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInteractionCapacityCurveSolution_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInteractionCapacityCurveSolution_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInteractionCapacityCurveSolution_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInteractionCapacityCurveSolution_get_MomentCapacitySolution(This,index,solution)	\
    ( (This)->lpVtbl -> get_MomentCapacitySolution(This,index,solution) ) 

#define IInteractionCapacityCurveSolution_AddSolutionPoint(This,solution)	\
    ( (This)->lpVtbl -> AddSolutionPoint(This,solution) ) 

#define IInteractionCapacityCurveSolution_get_SolutionPointCount(This,nPoints)	\
    ( (This)->lpVtbl -> get_SolutionPointCount(This,nPoints) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInteractionCapacityCurveSolution_INTERFACE_DEFINED__ */


#ifndef __IAxialInteractionCurveSolver_INTERFACE_DEFINED__
#define __IAxialInteractionCurveSolver_INTERFACE_DEFINED__

/* interface IAxialInteractionCurveSolver */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IAxialInteractionCurveSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AD04E104-0570-432b-9FF0-E5634F2CE942")
    IAxialInteractionCurveSolver : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Section( 
            /* [in] */ IGeneralSection *pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ IGeneralSection **pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Slices( 
            /* [in] */ long nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Slices( 
            /* [retval][out] */ long *nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_AxialTolerance( 
            /* [in] */ Float64 tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_AxialTolerance( 
            /* [retval][out] */ Float64 *tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MaxIterations( 
            /* [in] */ long maxIter) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MaxIterations( 
            /* [retval][out] */ long *maxIter) = 0;
        
        virtual /* [helpcontext] */ HRESULT STDMETHODCALLTYPE CompressionLimit( 
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo) = 0;
        
        virtual /* [helpcontext] */ HRESULT STDMETHODCALLTYPE TensionLimit( 
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ Float64 na,
            /* [in] */ long nFzSteps,
            /* [retval][out] */ IInteractionCapacityCurveSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAxialInteractionCurveSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAxialInteractionCurveSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAxialInteractionCurveSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAxialInteractionCurveSolver * This);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Section )( 
            IAxialInteractionCurveSolver * This,
            /* [in] */ IGeneralSection *pSection);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IAxialInteractionCurveSolver * This,
            /* [retval][out] */ IGeneralSection **pSection);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slices )( 
            IAxialInteractionCurveSolver * This,
            /* [in] */ long nSlices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slices )( 
            IAxialInteractionCurveSolver * This,
            /* [retval][out] */ long *nSlices);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AxialTolerance )( 
            IAxialInteractionCurveSolver * This,
            /* [in] */ Float64 tolerance);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AxialTolerance )( 
            IAxialInteractionCurveSolver * This,
            /* [retval][out] */ Float64 *tolerance);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxIterations )( 
            IAxialInteractionCurveSolver * This,
            /* [in] */ long maxIter);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxIterations )( 
            IAxialInteractionCurveSolver * This,
            /* [retval][out] */ long *maxIter);
        
        /* [helpcontext] */ HRESULT ( STDMETHODCALLTYPE *CompressionLimit )( 
            IAxialInteractionCurveSolver * This,
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo);
        
        /* [helpcontext] */ HRESULT ( STDMETHODCALLTYPE *TensionLimit )( 
            IAxialInteractionCurveSolver * This,
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IAxialInteractionCurveSolver * This,
            /* [in] */ Float64 na,
            /* [in] */ long nFzSteps,
            /* [retval][out] */ IInteractionCapacityCurveSolution **solution);
        
        END_INTERFACE
    } IAxialInteractionCurveSolverVtbl;

    interface IAxialInteractionCurveSolver
    {
        CONST_VTBL struct IAxialInteractionCurveSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAxialInteractionCurveSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAxialInteractionCurveSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAxialInteractionCurveSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAxialInteractionCurveSolver_putref_Section(This,pSection)	\
    ( (This)->lpVtbl -> putref_Section(This,pSection) ) 

#define IAxialInteractionCurveSolver_get_Section(This,pSection)	\
    ( (This)->lpVtbl -> get_Section(This,pSection) ) 

#define IAxialInteractionCurveSolver_put_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> put_Slices(This,nSlices) ) 

#define IAxialInteractionCurveSolver_get_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> get_Slices(This,nSlices) ) 

#define IAxialInteractionCurveSolver_put_AxialTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> put_AxialTolerance(This,tolerance) ) 

#define IAxialInteractionCurveSolver_get_AxialTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> get_AxialTolerance(This,tolerance) ) 

#define IAxialInteractionCurveSolver_put_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> put_MaxIterations(This,maxIter) ) 

#define IAxialInteractionCurveSolver_get_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> get_MaxIterations(This,maxIter) ) 

#define IAxialInteractionCurveSolver_CompressionLimit(This,Fz,Mx,My,eo)	\
    ( (This)->lpVtbl -> CompressionLimit(This,Fz,Mx,My,eo) ) 

#define IAxialInteractionCurveSolver_TensionLimit(This,Fz,Mx,My,eo)	\
    ( (This)->lpVtbl -> TensionLimit(This,Fz,Mx,My,eo) ) 

#define IAxialInteractionCurveSolver_Solve(This,na,nFzSteps,solution)	\
    ( (This)->lpVtbl -> Solve(This,na,nFzSteps,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAxialInteractionCurveSolver_INTERFACE_DEFINED__ */


#ifndef __IMomentInteractionCurveSolver_INTERFACE_DEFINED__
#define __IMomentInteractionCurveSolver_INTERFACE_DEFINED__

/* interface IMomentInteractionCurveSolver */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IMomentInteractionCurveSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7573B050-8EEC-4385-AFBF-9BD4690DCB7C")
    IMomentInteractionCurveSolver : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Section( 
            /* [in] */ IGeneralSection *pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ IGeneralSection **pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Slices( 
            /* [in] */ long nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Slices( 
            /* [retval][out] */ long *nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_AxialTolerance( 
            /* [in] */ Float64 tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_AxialTolerance( 
            /* [retval][out] */ Float64 *tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MaxIterations( 
            /* [in] */ long maxIter) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MaxIterations( 
            /* [retval][out] */ long *maxIter) = 0;
        
        virtual /* [helpcontext] */ HRESULT STDMETHODCALLTYPE CompressionLimit( 
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo) = 0;
        
        virtual /* [helpcontext] */ HRESULT STDMETHODCALLTYPE TensionLimit( 
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ Float64 Fz,
            /* [in] */ Float64 startNA,
            /* [in] */ Float64 endNA,
            /* [in] */ long nSteps,
            /* [retval][out] */ IInteractionCapacityCurveSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMomentInteractionCurveSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMomentInteractionCurveSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMomentInteractionCurveSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMomentInteractionCurveSolver * This);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Section )( 
            IMomentInteractionCurveSolver * This,
            /* [in] */ IGeneralSection *pSection);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IMomentInteractionCurveSolver * This,
            /* [retval][out] */ IGeneralSection **pSection);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slices )( 
            IMomentInteractionCurveSolver * This,
            /* [in] */ long nSlices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slices )( 
            IMomentInteractionCurveSolver * This,
            /* [retval][out] */ long *nSlices);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AxialTolerance )( 
            IMomentInteractionCurveSolver * This,
            /* [in] */ Float64 tolerance);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AxialTolerance )( 
            IMomentInteractionCurveSolver * This,
            /* [retval][out] */ Float64 *tolerance);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxIterations )( 
            IMomentInteractionCurveSolver * This,
            /* [in] */ long maxIter);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxIterations )( 
            IMomentInteractionCurveSolver * This,
            /* [retval][out] */ long *maxIter);
        
        /* [helpcontext] */ HRESULT ( STDMETHODCALLTYPE *CompressionLimit )( 
            IMomentInteractionCurveSolver * This,
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo);
        
        /* [helpcontext] */ HRESULT ( STDMETHODCALLTYPE *TensionLimit )( 
            IMomentInteractionCurveSolver * This,
            /* [out] */ Float64 *Fz,
            /* [out] */ Float64 *Mx,
            /* [out] */ Float64 *My,
            /* [out] */ Float64 *eo);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IMomentInteractionCurveSolver * This,
            /* [in] */ Float64 Fz,
            /* [in] */ Float64 startNA,
            /* [in] */ Float64 endNA,
            /* [in] */ long nSteps,
            /* [retval][out] */ IInteractionCapacityCurveSolution **solution);
        
        END_INTERFACE
    } IMomentInteractionCurveSolverVtbl;

    interface IMomentInteractionCurveSolver
    {
        CONST_VTBL struct IMomentInteractionCurveSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMomentInteractionCurveSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMomentInteractionCurveSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMomentInteractionCurveSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMomentInteractionCurveSolver_putref_Section(This,pSection)	\
    ( (This)->lpVtbl -> putref_Section(This,pSection) ) 

#define IMomentInteractionCurveSolver_get_Section(This,pSection)	\
    ( (This)->lpVtbl -> get_Section(This,pSection) ) 

#define IMomentInteractionCurveSolver_put_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> put_Slices(This,nSlices) ) 

#define IMomentInteractionCurveSolver_get_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> get_Slices(This,nSlices) ) 

#define IMomentInteractionCurveSolver_put_AxialTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> put_AxialTolerance(This,tolerance) ) 

#define IMomentInteractionCurveSolver_get_AxialTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> get_AxialTolerance(This,tolerance) ) 

#define IMomentInteractionCurveSolver_put_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> put_MaxIterations(This,maxIter) ) 

#define IMomentInteractionCurveSolver_get_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> get_MaxIterations(This,maxIter) ) 

#define IMomentInteractionCurveSolver_CompressionLimit(This,Fz,Mx,My,eo)	\
    ( (This)->lpVtbl -> CompressionLimit(This,Fz,Mx,My,eo) ) 

#define IMomentInteractionCurveSolver_TensionLimit(This,Fz,Mx,My,eo)	\
    ( (This)->lpVtbl -> TensionLimit(This,Fz,Mx,My,eo) ) 

#define IMomentInteractionCurveSolver_Solve(This,Fz,startNA,endNA,nSteps,solution)	\
    ( (This)->lpVtbl -> Solve(This,Fz,startNA,endNA,nSteps,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMomentInteractionCurveSolver_INTERFACE_DEFINED__ */


#ifndef __ICrackedSectionSlice_INTERFACE_DEFINED__
#define __ICrackedSectionSlice_INTERFACE_DEFINED__

/* interface ICrackedSectionSlice */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICrackedSectionSlice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3BFCCFE4-CFAA-496b-840D-1C9F8EC38015")
    ICrackedSectionSlice : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE InitSlice( 
            /* [in] */ IShape *pShape,
            /* [in] */ Float64 A,
            /* [in] */ Float64 cgX,
            /* [in] */ Float64 cgY,
            /* [in] */ Float64 Efg,
            /* [in] */ Float64 Ebg) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Area( 
            /* [retval][out] */ Float64 *pArea) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_CG( 
            /* [retval][out] */ IPoint2d **pCG) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Efg( 
            /* [retval][out] */ Float64 *pEfg) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Ebg( 
            /* [retval][out] */ Float64 *pEbg) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pShape) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICrackedSectionSliceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICrackedSectionSlice * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICrackedSectionSlice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICrackedSectionSlice * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSlice )( 
            ICrackedSectionSlice * This,
            /* [in] */ IShape *pShape,
            /* [in] */ Float64 A,
            /* [in] */ Float64 cgX,
            /* [in] */ Float64 cgY,
            /* [in] */ Float64 Efg,
            /* [in] */ Float64 Ebg);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Area )( 
            ICrackedSectionSlice * This,
            /* [retval][out] */ Float64 *pArea);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CG )( 
            ICrackedSectionSlice * This,
            /* [retval][out] */ IPoint2d **pCG);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Efg )( 
            ICrackedSectionSlice * This,
            /* [retval][out] */ Float64 *pEfg);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ebg )( 
            ICrackedSectionSlice * This,
            /* [retval][out] */ Float64 *pEbg);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ICrackedSectionSlice * This,
            /* [retval][out] */ IShape **pShape);
        
        END_INTERFACE
    } ICrackedSectionSliceVtbl;

    interface ICrackedSectionSlice
    {
        CONST_VTBL struct ICrackedSectionSliceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICrackedSectionSlice_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICrackedSectionSlice_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICrackedSectionSlice_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICrackedSectionSlice_InitSlice(This,pShape,A,cgX,cgY,Efg,Ebg)	\
    ( (This)->lpVtbl -> InitSlice(This,pShape,A,cgX,cgY,Efg,Ebg) ) 

#define ICrackedSectionSlice_get_Area(This,pArea)	\
    ( (This)->lpVtbl -> get_Area(This,pArea) ) 

#define ICrackedSectionSlice_get_CG(This,pCG)	\
    ( (This)->lpVtbl -> get_CG(This,pCG) ) 

#define ICrackedSectionSlice_get_Efg(This,pEfg)	\
    ( (This)->lpVtbl -> get_Efg(This,pEfg) ) 

#define ICrackedSectionSlice_get_Ebg(This,pEbg)	\
    ( (This)->lpVtbl -> get_Ebg(This,pEbg) ) 

#define ICrackedSectionSlice_get_Shape(This,pShape)	\
    ( (This)->lpVtbl -> get_Shape(This,pShape) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICrackedSectionSlice_INTERFACE_DEFINED__ */


#ifndef __ICrackedSectionSolution_INTERFACE_DEFINED__
#define __ICrackedSectionSolution_INTERFACE_DEFINED__

/* interface ICrackedSectionSolution */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICrackedSectionSolution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3B5642DB-676F-458d-94F6-33B325081475")
    ICrackedSectionSolution : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE InitSolution( 
            /* [in] */ IPoint2d *pntCG,
            /* [in] */ IUnkArray *slices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_CG( 
            /* [retval][out] */ IPoint2d **pntCG) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_SliceCount( 
            /* [retval][out] */ CollectionIndexType *nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Slice( 
            /* [in] */ CollectionIndexType sliceIdx,
            /* [retval][out] */ ICrackedSectionSlice **pSlice) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ElasticProperties( 
            /* [retval][out] */ IElasticProperties **ppProps) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICrackedSectionSolutionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICrackedSectionSolution * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICrackedSectionSolution * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICrackedSectionSolution * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *InitSolution )( 
            ICrackedSectionSolution * This,
            /* [in] */ IPoint2d *pntCG,
            /* [in] */ IUnkArray *slices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CG )( 
            ICrackedSectionSolution * This,
            /* [retval][out] */ IPoint2d **pntCG);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SliceCount )( 
            ICrackedSectionSolution * This,
            /* [retval][out] */ CollectionIndexType *nSlices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slice )( 
            ICrackedSectionSolution * This,
            /* [in] */ CollectionIndexType sliceIdx,
            /* [retval][out] */ ICrackedSectionSlice **pSlice);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ElasticProperties )( 
            ICrackedSectionSolution * This,
            /* [retval][out] */ IElasticProperties **ppProps);
        
        END_INTERFACE
    } ICrackedSectionSolutionVtbl;

    interface ICrackedSectionSolution
    {
        CONST_VTBL struct ICrackedSectionSolutionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICrackedSectionSolution_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICrackedSectionSolution_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICrackedSectionSolution_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICrackedSectionSolution_InitSolution(This,pntCG,slices)	\
    ( (This)->lpVtbl -> InitSolution(This,pntCG,slices) ) 

#define ICrackedSectionSolution_get_CG(This,pntCG)	\
    ( (This)->lpVtbl -> get_CG(This,pntCG) ) 

#define ICrackedSectionSolution_get_SliceCount(This,nSlices)	\
    ( (This)->lpVtbl -> get_SliceCount(This,nSlices) ) 

#define ICrackedSectionSolution_get_Slice(This,sliceIdx,pSlice)	\
    ( (This)->lpVtbl -> get_Slice(This,sliceIdx,pSlice) ) 

#define ICrackedSectionSolution_get_ElasticProperties(This,ppProps)	\
    ( (This)->lpVtbl -> get_ElasticProperties(This,ppProps) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICrackedSectionSolution_INTERFACE_DEFINED__ */


#ifndef __ICrackedSectionSolver_INTERFACE_DEFINED__
#define __ICrackedSectionSolver_INTERFACE_DEFINED__

/* interface ICrackedSectionSolver */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICrackedSectionSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E4FD79AB-580B-4037-AFAC-56DE678B545A")
    ICrackedSectionSolver : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Section( 
            /* [in] */ IGeneralSection *pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ IGeneralSection **pSection) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_CGTolerance( 
            /* [in] */ Float64 tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_CGTolerance( 
            /* [retval][out] */ Float64 *tolerance) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MaxIterations( 
            /* [in] */ long maxIter) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MaxIterations( 
            /* [retval][out] */ long *maxIter) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Slices( 
            /* [in] */ long nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Slices( 
            /* [retval][out] */ long *nSlices) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_SliceGrowthFactor( 
            /* [in] */ Float64 sliceGrowthFactor) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_SliceGrowthFactor( 
            /* [retval][out] */ Float64 *sliceGrowthFactor) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ Float64 naAngle,
            /* [retval][out] */ ICrackedSectionSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICrackedSectionSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICrackedSectionSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICrackedSectionSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICrackedSectionSolver * This);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Section )( 
            ICrackedSectionSolver * This,
            /* [in] */ IGeneralSection *pSection);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            ICrackedSectionSolver * This,
            /* [retval][out] */ IGeneralSection **pSection);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CGTolerance )( 
            ICrackedSectionSolver * This,
            /* [in] */ Float64 tolerance);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CGTolerance )( 
            ICrackedSectionSolver * This,
            /* [retval][out] */ Float64 *tolerance);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxIterations )( 
            ICrackedSectionSolver * This,
            /* [in] */ long maxIter);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxIterations )( 
            ICrackedSectionSolver * This,
            /* [retval][out] */ long *maxIter);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slices )( 
            ICrackedSectionSolver * This,
            /* [in] */ long nSlices);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slices )( 
            ICrackedSectionSolver * This,
            /* [retval][out] */ long *nSlices);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SliceGrowthFactor )( 
            ICrackedSectionSolver * This,
            /* [in] */ Float64 sliceGrowthFactor);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SliceGrowthFactor )( 
            ICrackedSectionSolver * This,
            /* [retval][out] */ Float64 *sliceGrowthFactor);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            ICrackedSectionSolver * This,
            /* [in] */ Float64 naAngle,
            /* [retval][out] */ ICrackedSectionSolution **solution);
        
        END_INTERFACE
    } ICrackedSectionSolverVtbl;

    interface ICrackedSectionSolver
    {
        CONST_VTBL struct ICrackedSectionSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICrackedSectionSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICrackedSectionSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICrackedSectionSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICrackedSectionSolver_putref_Section(This,pSection)	\
    ( (This)->lpVtbl -> putref_Section(This,pSection) ) 

#define ICrackedSectionSolver_get_Section(This,pSection)	\
    ( (This)->lpVtbl -> get_Section(This,pSection) ) 

#define ICrackedSectionSolver_put_CGTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> put_CGTolerance(This,tolerance) ) 

#define ICrackedSectionSolver_get_CGTolerance(This,tolerance)	\
    ( (This)->lpVtbl -> get_CGTolerance(This,tolerance) ) 

#define ICrackedSectionSolver_put_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> put_MaxIterations(This,maxIter) ) 

#define ICrackedSectionSolver_get_MaxIterations(This,maxIter)	\
    ( (This)->lpVtbl -> get_MaxIterations(This,maxIter) ) 

#define ICrackedSectionSolver_put_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> put_Slices(This,nSlices) ) 

#define ICrackedSectionSolver_get_Slices(This,nSlices)	\
    ( (This)->lpVtbl -> get_Slices(This,nSlices) ) 

#define ICrackedSectionSolver_put_SliceGrowthFactor(This,sliceGrowthFactor)	\
    ( (This)->lpVtbl -> put_SliceGrowthFactor(This,sliceGrowthFactor) ) 

#define ICrackedSectionSolver_get_SliceGrowthFactor(This,sliceGrowthFactor)	\
    ( (This)->lpVtbl -> get_SliceGrowthFactor(This,sliceGrowthFactor) ) 

#define ICrackedSectionSolver_Solve(This,naAngle,solution)	\
    ( (This)->lpVtbl -> Solve(This,naAngle,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICrackedSectionSolver_INTERFACE_DEFINED__ */


#ifndef __IManderModelSection_INTERFACE_DEFINED__
#define __IManderModelSection_INTERFACE_DEFINED__

/* interface IManderModelSection */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IManderModelSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("84A90446-34BC-445d-B7E1-EBC915159529")
    IManderModelSection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_TransvYieldStrength( 
            /* [in] */ Float64 fyh) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_TransvYieldStrength( 
            /* [retval][out] */ Float64 *fyh) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_TransvReinforcementRatio( 
            /* [retval][out] */ Float64 *ps) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ConfinementEffectivenessCoefficient( 
            /* [retval][out] */ Float64 *ke) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IManderModelSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IManderModelSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IManderModelSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IManderModelSection * This);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransvYieldStrength )( 
            IManderModelSection * This,
            /* [in] */ Float64 fyh);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransvYieldStrength )( 
            IManderModelSection * This,
            /* [retval][out] */ Float64 *fyh);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransvReinforcementRatio )( 
            IManderModelSection * This,
            /* [retval][out] */ Float64 *ps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConfinementEffectivenessCoefficient )( 
            IManderModelSection * This,
            /* [retval][out] */ Float64 *ke);
        
        END_INTERFACE
    } IManderModelSectionVtbl;

    interface IManderModelSection
    {
        CONST_VTBL struct IManderModelSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IManderModelSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IManderModelSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IManderModelSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IManderModelSection_put_TransvYieldStrength(This,fyh)	\
    ( (This)->lpVtbl -> put_TransvYieldStrength(This,fyh) ) 

#define IManderModelSection_get_TransvYieldStrength(This,fyh)	\
    ( (This)->lpVtbl -> get_TransvYieldStrength(This,fyh) ) 

#define IManderModelSection_get_TransvReinforcementRatio(This,ps)	\
    ( (This)->lpVtbl -> get_TransvReinforcementRatio(This,ps) ) 

#define IManderModelSection_get_ConfinementEffectivenessCoefficient(This,ke)	\
    ( (This)->lpVtbl -> get_ConfinementEffectivenessCoefficient(This,ke) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IManderModelSection_INTERFACE_DEFINED__ */


#ifndef __ICircularManderSection_INTERFACE_DEFINED__
#define __ICircularManderSection_INTERFACE_DEFINED__

/* interface ICircularManderSection */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_ICircularManderSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6BA241A3-73FC-48a4-AE85-E2B4B496E3C1")
    ICircularManderSection : public IManderModelSection
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_TransvReinforcementType( 
            /* [in] */ TransvReinforcementType trt) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_TransvReinforcementType( 
            /* [retval][out] */ TransvReinforcementType *trt) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Asp( 
            /* [in] */ Float64 asp) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Asp( 
            /* [retval][out] */ Float64 *asp) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_As( 
            /* [in] */ Float64 as) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_As( 
            /* [retval][out] */ Float64 *as) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_db( 
            /* [in] */ Float64 db) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_db( 
            /* [retval][out] */ Float64 *db) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_S( 
            /* [in] */ Float64 s) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_S( 
            /* [retval][out] */ Float64 *s) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Diameter( 
            /* [in] */ Float64 d) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Diameter( 
            /* [retval][out] */ Float64 *d) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Cover( 
            /* [in] */ Float64 c) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Cover( 
            /* [retval][out] */ Float64 *c) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICircularManderSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICircularManderSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICircularManderSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICircularManderSection * This);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransvYieldStrength )( 
            ICircularManderSection * This,
            /* [in] */ Float64 fyh);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransvYieldStrength )( 
            ICircularManderSection * This,
            /* [retval][out] */ Float64 *fyh);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransvReinforcementRatio )( 
            ICircularManderSection * This,
            /* [retval][out] */ Float64 *ps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConfinementEffectivenessCoefficient )( 
            ICircularManderSection * This,
            /* [retval][out] */ Float64 *ke);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransvReinforcementType )( 
            ICircularManderSection * This,
            /* [in] */ TransvReinforcementType trt);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransvReinforcementType )( 
            ICircularManderSection * This,
            /* [retval][out] */ TransvReinforcementType *trt);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Asp )( 
            ICircularManderSection * This,
            /* [in] */ Float64 asp);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Asp )( 
            ICircularManderSection * This,
            /* [retval][out] */ Float64 *asp);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_As )( 
            ICircularManderSection * This,
            /* [in] */ Float64 as);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_As )( 
            ICircularManderSection * This,
            /* [retval][out] */ Float64 *as);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_db )( 
            ICircularManderSection * This,
            /* [in] */ Float64 db);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_db )( 
            ICircularManderSection * This,
            /* [retval][out] */ Float64 *db);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_S )( 
            ICircularManderSection * This,
            /* [in] */ Float64 s);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_S )( 
            ICircularManderSection * This,
            /* [retval][out] */ Float64 *s);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Diameter )( 
            ICircularManderSection * This,
            /* [in] */ Float64 d);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Diameter )( 
            ICircularManderSection * This,
            /* [retval][out] */ Float64 *d);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Cover )( 
            ICircularManderSection * This,
            /* [in] */ Float64 c);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cover )( 
            ICircularManderSection * This,
            /* [retval][out] */ Float64 *c);
        
        END_INTERFACE
    } ICircularManderSectionVtbl;

    interface ICircularManderSection
    {
        CONST_VTBL struct ICircularManderSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICircularManderSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICircularManderSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICircularManderSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICircularManderSection_put_TransvYieldStrength(This,fyh)	\
    ( (This)->lpVtbl -> put_TransvYieldStrength(This,fyh) ) 

#define ICircularManderSection_get_TransvYieldStrength(This,fyh)	\
    ( (This)->lpVtbl -> get_TransvYieldStrength(This,fyh) ) 

#define ICircularManderSection_get_TransvReinforcementRatio(This,ps)	\
    ( (This)->lpVtbl -> get_TransvReinforcementRatio(This,ps) ) 

#define ICircularManderSection_get_ConfinementEffectivenessCoefficient(This,ke)	\
    ( (This)->lpVtbl -> get_ConfinementEffectivenessCoefficient(This,ke) ) 


#define ICircularManderSection_put_TransvReinforcementType(This,trt)	\
    ( (This)->lpVtbl -> put_TransvReinforcementType(This,trt) ) 

#define ICircularManderSection_get_TransvReinforcementType(This,trt)	\
    ( (This)->lpVtbl -> get_TransvReinforcementType(This,trt) ) 

#define ICircularManderSection_put_Asp(This,asp)	\
    ( (This)->lpVtbl -> put_Asp(This,asp) ) 

#define ICircularManderSection_get_Asp(This,asp)	\
    ( (This)->lpVtbl -> get_Asp(This,asp) ) 

#define ICircularManderSection_put_As(This,as)	\
    ( (This)->lpVtbl -> put_As(This,as) ) 

#define ICircularManderSection_get_As(This,as)	\
    ( (This)->lpVtbl -> get_As(This,as) ) 

#define ICircularManderSection_put_db(This,db)	\
    ( (This)->lpVtbl -> put_db(This,db) ) 

#define ICircularManderSection_get_db(This,db)	\
    ( (This)->lpVtbl -> get_db(This,db) ) 

#define ICircularManderSection_put_S(This,s)	\
    ( (This)->lpVtbl -> put_S(This,s) ) 

#define ICircularManderSection_get_S(This,s)	\
    ( (This)->lpVtbl -> get_S(This,s) ) 

#define ICircularManderSection_put_Diameter(This,d)	\
    ( (This)->lpVtbl -> put_Diameter(This,d) ) 

#define ICircularManderSection_get_Diameter(This,d)	\
    ( (This)->lpVtbl -> get_Diameter(This,d) ) 

#define ICircularManderSection_put_Cover(This,c)	\
    ( (This)->lpVtbl -> put_Cover(This,c) ) 

#define ICircularManderSection_get_Cover(This,c)	\
    ( (This)->lpVtbl -> get_Cover(This,c) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICircularManderSection_INTERFACE_DEFINED__ */


#ifndef __IManderModel_INTERFACE_DEFINED__
#define __IManderModel_INTERFACE_DEFINED__

/* interface IManderModel */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IManderModel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5580011C-EE53-4323-8239-17C10E1F10CA")
    IManderModel : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Section( 
            /* [in] */ IManderModelSection *section) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ IManderModelSection **section) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_fco( 
            /* [in] */ Float64 fco) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_fco( 
            /* [retval][out] */ Float64 *fco) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_eco( 
            /* [in] */ Float64 eco) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_eco( 
            /* [retval][out] */ Float64 *eco) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_R( 
            /* [in] */ Float64 r) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_R( 
            /* [retval][out] */ Float64 *r) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IManderModelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IManderModel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IManderModel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IManderModel * This);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Section )( 
            IManderModel * This,
            /* [in] */ IManderModelSection *section);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IManderModel * This,
            /* [retval][out] */ IManderModelSection **section);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fco )( 
            IManderModel * This,
            /* [in] */ Float64 fco);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fco )( 
            IManderModel * This,
            /* [retval][out] */ Float64 *fco);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_eco )( 
            IManderModel * This,
            /* [in] */ Float64 eco);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_eco )( 
            IManderModel * This,
            /* [retval][out] */ Float64 *eco);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_R )( 
            IManderModel * This,
            /* [in] */ Float64 r);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_R )( 
            IManderModel * This,
            /* [retval][out] */ Float64 *r);
        
        END_INTERFACE
    } IManderModelVtbl;

    interface IManderModel
    {
        CONST_VTBL struct IManderModelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IManderModel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IManderModel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IManderModel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IManderModel_putref_Section(This,section)	\
    ( (This)->lpVtbl -> putref_Section(This,section) ) 

#define IManderModel_get_Section(This,section)	\
    ( (This)->lpVtbl -> get_Section(This,section) ) 

#define IManderModel_put_fco(This,fco)	\
    ( (This)->lpVtbl -> put_fco(This,fco) ) 

#define IManderModel_get_fco(This,fco)	\
    ( (This)->lpVtbl -> get_fco(This,fco) ) 

#define IManderModel_put_eco(This,eco)	\
    ( (This)->lpVtbl -> put_eco(This,eco) ) 

#define IManderModel_get_eco(This,eco)	\
    ( (This)->lpVtbl -> get_eco(This,eco) ) 

#define IManderModel_put_R(This,r)	\
    ( (This)->lpVtbl -> put_R(This,r) ) 

#define IManderModel_get_R(This,r)	\
    ( (This)->lpVtbl -> get_R(This,r) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IManderModel_INTERFACE_DEFINED__ */


#ifndef __IPowerFormula_INTERFACE_DEFINED__
#define __IPowerFormula_INTERFACE_DEFINED__

/* interface IPowerFormula */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IPowerFormula;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("262F134D-3A3F-496A-8A10-ACBBA783DDEA")
    IPowerFormula : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Grade( 
            /* [retval][out] */ StrandGradeType *grade) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Grade( 
            /* [in] */ StrandGradeType grade) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ProductionMethod( 
            /* [retval][out] */ ProductionMethodType *type) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_ProductionMethod( 
            /* [in] */ ProductionMethodType type) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPowerFormulaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPowerFormula * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPowerFormula * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPowerFormula * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Grade )( 
            IPowerFormula * This,
            /* [retval][out] */ StrandGradeType *grade);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Grade )( 
            IPowerFormula * This,
            /* [in] */ StrandGradeType grade);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProductionMethod )( 
            IPowerFormula * This,
            /* [retval][out] */ ProductionMethodType *type);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProductionMethod )( 
            IPowerFormula * This,
            /* [in] */ ProductionMethodType type);
        
        END_INTERFACE
    } IPowerFormulaVtbl;

    interface IPowerFormula
    {
        CONST_VTBL struct IPowerFormulaVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPowerFormula_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPowerFormula_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPowerFormula_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPowerFormula_get_Grade(This,grade)	\
    ( (This)->lpVtbl -> get_Grade(This,grade) ) 

#define IPowerFormula_put_Grade(This,grade)	\
    ( (This)->lpVtbl -> put_Grade(This,grade) ) 

#define IPowerFormula_get_ProductionMethod(This,type)	\
    ( (This)->lpVtbl -> get_ProductionMethod(This,type) ) 

#define IPowerFormula_put_ProductionMethod(This,type)	\
    ( (This)->lpVtbl -> put_ProductionMethod(This,type) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPowerFormula_INTERFACE_DEFINED__ */


#ifndef __ILRFDPrestressFormula_INTERFACE_DEFINED__
#define __ILRFDPrestressFormula_INTERFACE_DEFINED__

/* interface ILRFDPrestressFormula */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_ILRFDPrestressFormula;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D08B042B-0B5D-4a7a-A5E0-8EC204078438")
    ILRFDPrestressFormula : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Fpu( 
            /* [in] */ Float64 fpu) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Fpu( 
            /* [retval][out] */ Float64 *pFpu) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Eps( 
            /* [in] */ Float64 Eps) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ProductionMethod( 
            /* [retval][out] */ ProductionMethodType *type) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_ProductionMethod( 
            /* [in] */ ProductionMethodType type) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILRFDPrestressFormulaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILRFDPrestressFormula * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILRFDPrestressFormula * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILRFDPrestressFormula * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fpu )( 
            ILRFDPrestressFormula * This,
            /* [in] */ Float64 fpu);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fpu )( 
            ILRFDPrestressFormula * This,
            /* [retval][out] */ Float64 *pFpu);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Eps )( 
            ILRFDPrestressFormula * This,
            /* [in] */ Float64 Eps);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProductionMethod )( 
            ILRFDPrestressFormula * This,
            /* [retval][out] */ ProductionMethodType *type);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProductionMethod )( 
            ILRFDPrestressFormula * This,
            /* [in] */ ProductionMethodType type);
        
        END_INTERFACE
    } ILRFDPrestressFormulaVtbl;

    interface ILRFDPrestressFormula
    {
        CONST_VTBL struct ILRFDPrestressFormulaVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILRFDPrestressFormula_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILRFDPrestressFormula_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILRFDPrestressFormula_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILRFDPrestressFormula_put_Fpu(This,fpu)	\
    ( (This)->lpVtbl -> put_Fpu(This,fpu) ) 

#define ILRFDPrestressFormula_get_Fpu(This,pFpu)	\
    ( (This)->lpVtbl -> get_Fpu(This,pFpu) ) 

#define ILRFDPrestressFormula_put_Eps(This,Eps)	\
    ( (This)->lpVtbl -> put_Eps(This,Eps) ) 

#define ILRFDPrestressFormula_get_ProductionMethod(This,type)	\
    ( (This)->lpVtbl -> get_ProductionMethod(This,type) ) 

#define ILRFDPrestressFormula_put_ProductionMethod(This,type)	\
    ( (This)->lpVtbl -> put_ProductionMethod(This,type) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILRFDPrestressFormula_INTERFACE_DEFINED__ */


#ifndef __ISectionBuilder_INTERFACE_DEFINED__
#define __ISectionBuilder_INTERFACE_DEFINED__

/* interface ISectionBuilder */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_ISectionBuilder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4239F42F-055D-418a-B42A-D2A3DB540D69")
    ISectionBuilder : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE RectangularColumn( 
            /* [in] */ Float64 H,
            /* [in] */ Float64 W,
            /* [in] */ Float64 cover,
            /* [in] */ long Nh,
            /* [in] */ long Nw,
            /* [in] */ Float64 As,
            /* [in] */ IStressStrain *concrete,
            /* [in] */ IStressStrain *rebar,
            /* [retval][out] */ IGeneralSection **section) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE CircularColumn( 
            /* [in] */ Float64 D,
            /* [in] */ Float64 cover,
            /* [in] */ long Nb,
            /* [in] */ Float64 As,
            /* [in] */ IStressStrain *concrete,
            /* [in] */ IStressStrain *rebar,
            /* [retval][out] */ IGeneralSection **section) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISectionBuilderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISectionBuilder * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISectionBuilder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISectionBuilder * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *RectangularColumn )( 
            ISectionBuilder * This,
            /* [in] */ Float64 H,
            /* [in] */ Float64 W,
            /* [in] */ Float64 cover,
            /* [in] */ long Nh,
            /* [in] */ long Nw,
            /* [in] */ Float64 As,
            /* [in] */ IStressStrain *concrete,
            /* [in] */ IStressStrain *rebar,
            /* [retval][out] */ IGeneralSection **section);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *CircularColumn )( 
            ISectionBuilder * This,
            /* [in] */ Float64 D,
            /* [in] */ Float64 cover,
            /* [in] */ long Nb,
            /* [in] */ Float64 As,
            /* [in] */ IStressStrain *concrete,
            /* [in] */ IStressStrain *rebar,
            /* [retval][out] */ IGeneralSection **section);
        
        END_INTERFACE
    } ISectionBuilderVtbl;

    interface ISectionBuilder
    {
        CONST_VTBL struct ISectionBuilderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISectionBuilder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISectionBuilder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISectionBuilder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISectionBuilder_RectangularColumn(This,H,W,cover,Nh,Nw,As,concrete,rebar,section)	\
    ( (This)->lpVtbl -> RectangularColumn(This,H,W,cover,Nh,Nw,As,concrete,rebar,section) ) 

#define ISectionBuilder_CircularColumn(This,D,cover,Nb,As,concrete,rebar,section)	\
    ( (This)->lpVtbl -> CircularColumn(This,D,cover,Nb,As,concrete,rebar,section) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISectionBuilder_INTERFACE_DEFINED__ */


#ifndef __ICapacityReductionFactor_INTERFACE_DEFINED__
#define __ICapacityReductionFactor_INTERFACE_DEFINED__

/* interface ICapacityReductionFactor */
/* [object][unique][helpcontext][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_ICapacityReductionFactor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A328DF26-75F1-4433-B74D-C0929A481B8C")
    ICapacityReductionFactor : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Compute( 
            /* [in] */ IGeneralSection *section,
            /* [in] */ CollectionIndexType nConcShapes,
            /* [in] */ ILine2d *neutralAxis,
            /* [in] */ Float64 ppr,
            /* [out] */ Float64 *c,
            /* [out] */ Float64 *dt,
            /* [out] */ Float64 *phi) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeEx( 
            /* [in] */ IUnkArray *pConcShapes,
            /* [in] */ IUnkArray *pReinfShapes,
            /* [in] */ ILine2d *neutralAxis,
            /* [in] */ Float64 ppr,
            /* [out] */ Float64 *c,
            /* [out] */ Float64 *dt,
            /* [out] */ Float64 *phi) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICapacityReductionFactorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICapacityReductionFactor * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICapacityReductionFactor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICapacityReductionFactor * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Compute )( 
            ICapacityReductionFactor * This,
            /* [in] */ IGeneralSection *section,
            /* [in] */ CollectionIndexType nConcShapes,
            /* [in] */ ILine2d *neutralAxis,
            /* [in] */ Float64 ppr,
            /* [out] */ Float64 *c,
            /* [out] */ Float64 *dt,
            /* [out] */ Float64 *phi);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeEx )( 
            ICapacityReductionFactor * This,
            /* [in] */ IUnkArray *pConcShapes,
            /* [in] */ IUnkArray *pReinfShapes,
            /* [in] */ ILine2d *neutralAxis,
            /* [in] */ Float64 ppr,
            /* [out] */ Float64 *c,
            /* [out] */ Float64 *dt,
            /* [out] */ Float64 *phi);
        
        END_INTERFACE
    } ICapacityReductionFactorVtbl;

    interface ICapacityReductionFactor
    {
        CONST_VTBL struct ICapacityReductionFactorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICapacityReductionFactor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICapacityReductionFactor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICapacityReductionFactor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICapacityReductionFactor_Compute(This,section,nConcShapes,neutralAxis,ppr,c,dt,phi)	\
    ( (This)->lpVtbl -> Compute(This,section,nConcShapes,neutralAxis,ppr,c,dt,phi) ) 

#define ICapacityReductionFactor_ComputeEx(This,pConcShapes,pReinfShapes,neutralAxis,ppr,c,dt,phi)	\
    ( (This)->lpVtbl -> ComputeEx(This,pConcShapes,pReinfShapes,neutralAxis,ppr,c,dt,phi) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICapacityReductionFactor_INTERFACE_DEFINED__ */


#ifndef __IRCCrackedSectionSolver_INTERFACE_DEFINED__
#define __IRCCrackedSectionSolver_INTERFACE_DEFINED__

/* interface IRCCrackedSectionSolver */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCCrackedSectionSolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F351EDCA-2D3A-499a-B1E2-2A54673F087A")
    IRCCrackedSectionSolver : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ IRCBeam *beam,
            /* [retval][out] */ ICrackedSectionSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCCrackedSectionSolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCCrackedSectionSolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCCrackedSectionSolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCCrackedSectionSolver * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IRCCrackedSectionSolver * This,
            /* [in] */ IRCBeam *beam,
            /* [retval][out] */ ICrackedSectionSolution **solution);
        
        END_INTERFACE
    } IRCCrackedSectionSolverVtbl;

    interface IRCCrackedSectionSolver
    {
        CONST_VTBL struct IRCCrackedSectionSolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCCrackedSectionSolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCCrackedSectionSolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCCrackedSectionSolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCCrackedSectionSolver_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCCrackedSectionSolver_INTERFACE_DEFINED__ */


#ifndef __IRCCrackedSectionSolver2_INTERFACE_DEFINED__
#define __IRCCrackedSectionSolver2_INTERFACE_DEFINED__

/* interface IRCCrackedSectionSolver2 */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCCrackedSectionSolver2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0D0E0A6B-DB53-443e-BC76-CDED1C7C7528")
    IRCCrackedSectionSolver2 : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ IRCBeam2 *beam,
            /* [retval][out] */ ICrackedSectionSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCCrackedSectionSolver2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCCrackedSectionSolver2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCCrackedSectionSolver2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCCrackedSectionSolver2 * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IRCCrackedSectionSolver2 * This,
            /* [in] */ IRCBeam2 *beam,
            /* [retval][out] */ ICrackedSectionSolution **solution);
        
        END_INTERFACE
    } IRCCrackedSectionSolver2Vtbl;

    interface IRCCrackedSectionSolver2
    {
        CONST_VTBL struct IRCCrackedSectionSolver2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCCrackedSectionSolver2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCCrackedSectionSolver2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCCrackedSectionSolver2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCCrackedSectionSolver2_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCCrackedSectionSolver2_INTERFACE_DEFINED__ */


#ifndef __IRCCrackedSectionSolver2Ex_INTERFACE_DEFINED__
#define __IRCCrackedSectionSolver2Ex_INTERFACE_DEFINED__

/* interface IRCCrackedSectionSolver2Ex */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRCCrackedSectionSolver2Ex;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3D186B71-8511-43ef-BBD3-DDBA3808CFB4")
    IRCCrackedSectionSolver2Ex : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ IRCBeam2Ex *beam,
            /* [retval][out] */ ICrackedSectionSolution **solution) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRCCrackedSectionSolver2ExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRCCrackedSectionSolver2Ex * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRCCrackedSectionSolver2Ex * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRCCrackedSectionSolver2Ex * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Solve )( 
            IRCCrackedSectionSolver2Ex * This,
            /* [in] */ IRCBeam2Ex *beam,
            /* [retval][out] */ ICrackedSectionSolution **solution);
        
        END_INTERFACE
    } IRCCrackedSectionSolver2ExVtbl;

    interface IRCCrackedSectionSolver2Ex
    {
        CONST_VTBL struct IRCCrackedSectionSolver2ExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRCCrackedSectionSolver2Ex_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRCCrackedSectionSolver2Ex_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRCCrackedSectionSolver2Ex_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRCCrackedSectionSolver2Ex_Solve(This,beam,solution)	\
    ( (This)->lpVtbl -> Solve(This,beam,solution) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRCCrackedSectionSolver2Ex_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UnconfinedConcrete;

#ifdef __cplusplus

class DECLSPEC_UUID("4FAFD823-B4C9-4F88-8D46-74F84682893C")
UnconfinedConcrete;
#endif

EXTERN_C const CLSID CLSID_PSPowerFormula;

#ifdef __cplusplus

class DECLSPEC_UUID("75C05DC6-48F7-476B-B67A-ABD58180F9FB")
PSPowerFormula;
#endif

EXTERN_C const CLSID CLSID_LRFDPrestressFormula;

#ifdef __cplusplus

class DECLSPEC_UUID("F3C1A16E-C1F0-4d60-93F2-4017A0472B7C")
LRFDPrestressFormula;
#endif

EXTERN_C const CLSID CLSID_RebarModel;

#ifdef __cplusplus

class DECLSPEC_UUID("9F2A88AB-C3AF-49AB-9685-47444F74C3DC")
RebarModel;
#endif

EXTERN_C const CLSID CLSID_StrainHardenedRebarModel;

#ifdef __cplusplus

class DECLSPEC_UUID("030BB55E-DCE1-4bc2-9036-2D9F74A8A814")
StrainHardenedRebarModel;
#endif

EXTERN_C const CLSID CLSID_RCBeam;

#ifdef __cplusplus

class DECLSPEC_UUID("3DB23ADB-A45F-4093-A7B4-DE198847A825")
RCBeam;
#endif

EXTERN_C const CLSID CLSID_RCBeam2;

#ifdef __cplusplus

class DECLSPEC_UUID("F9D85972-E047-4EA7-BC7A-24C67CDC5492")
RCBeam2;
#endif

EXTERN_C const CLSID CLSID_RCBeam2Ex;

#ifdef __cplusplus

class DECLSPEC_UUID("BD03891B-48D5-4324-8C37-B88865B5F5DA")
RCBeam2Ex;
#endif

EXTERN_C const CLSID CLSID_LRFDSolver;

#ifdef __cplusplus

class DECLSPEC_UUID("8B5C753D-82DC-46B8-9D89-6F28CFF9D3B8")
LRFDSolver;
#endif

EXTERN_C const CLSID CLSID_LRFDSolver2;

#ifdef __cplusplus

class DECLSPEC_UUID("8AE96CF8-F16B-4488-904B-1F7B27E0C125")
LRFDSolver2;
#endif

EXTERN_C const CLSID CLSID_LFDSolver;

#ifdef __cplusplus

class DECLSPEC_UUID("267BF7DB-1E9F-43e7-95AF-157776848D60")
LFDSolver;
#endif

EXTERN_C const CLSID CLSID_PCISolver;

#ifdef __cplusplus

class DECLSPEC_UUID("F7F99D32-5E9E-4618-A858-ABE7089EE425")
PCISolver;
#endif

EXTERN_C const CLSID CLSID_NLSolver;

#ifdef __cplusplus

class DECLSPEC_UUID("E5848EAC-5DE6-4147-8771-78225B66F8B7")
NLSolver;
#endif

EXTERN_C const CLSID CLSID_RCSolution;

#ifdef __cplusplus

class DECLSPEC_UUID("DE9971B2-8ED4-4840-80EF-07B0F295410E")
RCSolution;
#endif

EXTERN_C const CLSID CLSID_RCSolutionEx;

#ifdef __cplusplus

class DECLSPEC_UUID("FD1C3AFB-609A-4633-A0FE-2EE6A0154C33")
RCSolutionEx;
#endif

EXTERN_C const CLSID CLSID_LRFDSolution;

#ifdef __cplusplus

class DECLSPEC_UUID("F3E82C7F-E2E1-4949-B724-B15D0329ECE0")
LRFDSolution;
#endif

EXTERN_C const CLSID CLSID_LRFDSolutionEx;

#ifdef __cplusplus

class DECLSPEC_UUID("96CB9016-C37A-4c09-A710-850FAB1A27B0")
LRFDSolutionEx;
#endif

EXTERN_C const CLSID CLSID_PCISolution;

#ifdef __cplusplus

class DECLSPEC_UUID("D24CC053-6C5B-4392-B0F8-B34D07D815B3")
PCISolution;
#endif

EXTERN_C const CLSID CLSID_PCISolutionEx;

#ifdef __cplusplus

class DECLSPEC_UUID("C1CD05E5-C0A6-48A6-98A4-E00011EAEAD0")
PCISolutionEx;
#endif

EXTERN_C const CLSID CLSID_MixedSolver;

#ifdef __cplusplus

class DECLSPEC_UUID("29CA6786-FA0C-402C-9683-404C6275E378")
MixedSolver;
#endif

EXTERN_C const CLSID CLSID_RoundColumn;

#ifdef __cplusplus

class DECLSPEC_UUID("0778C329-BF14-42DD-BC00-596BFDF80F5C")
RoundColumn;
#endif

EXTERN_C const CLSID CLSID_GeneralSection;

#ifdef __cplusplus

class DECLSPEC_UUID("62ABC849-D56B-4918-87AD-B7DF219E5909")
GeneralSection;
#endif

EXTERN_C const CLSID CLSID_GeneralSectionSlice;

#ifdef __cplusplus

class DECLSPEC_UUID("F57C14E7-B13A-4afd-8B48-CD68417457BB")
GeneralSectionSlice;
#endif

EXTERN_C const CLSID CLSID_GeneralSectionSolution;

#ifdef __cplusplus

class DECLSPEC_UUID("D9E5208E-8DE6-41b6-8700-4A0EFB749E1C")
GeneralSectionSolution;
#endif

EXTERN_C const CLSID CLSID_GeneralSectionSolver;

#ifdef __cplusplus

class DECLSPEC_UUID("4B0F6910-9548-4629-B6DF-6CDA76F911CF")
GeneralSectionSolver;
#endif

EXTERN_C const CLSID CLSID_MomentCurvatureSolution;

#ifdef __cplusplus

class DECLSPEC_UUID("2048EC33-ACCC-4f35-A2AC-DEFB64126D45")
MomentCurvatureSolution;
#endif

EXTERN_C const CLSID CLSID_MomentCurvatureSolver;

#ifdef __cplusplus

class DECLSPEC_UUID("ABACF363-FDFF-4ae3-B305-4DD2B478174F")
MomentCurvatureSolver;
#endif

EXTERN_C const CLSID CLSID_MomentCapacitySolution;

#ifdef __cplusplus

class DECLSPEC_UUID("B5DB837E-F239-4d17-8A13-D16219BE2F16")
MomentCapacitySolution;
#endif

EXTERN_C const CLSID CLSID_MomentCapacitySolver;

#ifdef __cplusplus

class DECLSPEC_UUID("C7173DB8-37C5-4800-A9DF-70379BD71530")
MomentCapacitySolver;
#endif

EXTERN_C const CLSID CLSID_CircularManderSection;

#ifdef __cplusplus

class DECLSPEC_UUID("9374FC6E-D9F9-4d58-BE0E-D6D74DFB66CD")
CircularManderSection;
#endif

EXTERN_C const CLSID CLSID_ManderModel;

#ifdef __cplusplus

class DECLSPEC_UUID("89C63EF1-9DA6-4fef-8892-D6C9E6359459")
ManderModel;
#endif

EXTERN_C const CLSID CLSID_InteractionCurveSolution;

#ifdef __cplusplus

class DECLSPEC_UUID("3D136232-2592-4751-8D6C-55C0481C2FC6")
InteractionCurveSolution;
#endif

EXTERN_C const CLSID CLSID_InteractionCurveSolver;

#ifdef __cplusplus

class DECLSPEC_UUID("4D75A698-EF7C-4ca5-A0B2-C6F4C8FC3B6D")
InteractionCurveSolver;
#endif

EXTERN_C const CLSID CLSID_InteractionCapacityCurveSolution;

#ifdef __cplusplus

class DECLSPEC_UUID("90596D18-7307-49a8-8F7D-3FD9FB4AFF31")
InteractionCapacityCurveSolution;
#endif

EXTERN_C const CLSID CLSID_AxialInteractionCurveSolver;

#ifdef __cplusplus

class DECLSPEC_UUID("E2032086-9161-453b-ABF0-2150CAA924AF")
AxialInteractionCurveSolver;
#endif

EXTERN_C const CLSID CLSID_MomentInteractionCurveSolver;

#ifdef __cplusplus

class DECLSPEC_UUID("F4816F27-B4D5-44e4-843B-4B3E8B2FF9FE")
MomentInteractionCurveSolver;
#endif

EXTERN_C const CLSID CLSID_SectionBuilder;

#ifdef __cplusplus

class DECLSPEC_UUID("4BD04EC7-9116-480c-9BED-607753E2E3F5")
SectionBuilder;
#endif

EXTERN_C const CLSID CLSID_CapacityReductionFactor;

#ifdef __cplusplus

class DECLSPEC_UUID("A6C78DC5-0FD1-48b0-B393-D7241232AE11")
CapacityReductionFactor;
#endif

EXTERN_C const CLSID CLSID_CrackedSectionSolution;

#ifdef __cplusplus

class DECLSPEC_UUID("88B40E54-6EB0-4701-AC9B-71AA90841C73")
CrackedSectionSolution;
#endif

EXTERN_C const CLSID CLSID_CrackedSectionSolver;

#ifdef __cplusplus

class DECLSPEC_UUID("A3B11833-C6C5-4fad-96C0-5E162B8C4228")
CrackedSectionSolver;
#endif

EXTERN_C const CLSID CLSID_CrackedSectionSlice;

#ifdef __cplusplus

class DECLSPEC_UUID("EFF46265-14C7-41e3-AF39-45B820745A64")
CrackedSectionSlice;
#endif
#endif /* __WBFLRCCapacity_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


