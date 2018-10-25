///////////////////////////////////////////////////////////////////////
// BogusCombinationContext - Test driver for LBAM load combinations
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// BogusComboContext.h : Declaration of the CBogusComboContext

#ifndef __BOGUSCOMBOCONTEXT_H_
#define __BOGUSCOMBOCONTEXT_H_
#pragma once

#include "resource.h"       // main symbols
#include "WBFLLBAMLoadCombiner.h"
#include "BogusCombinationContextCP.h"
#include "LBAMLoadCombinerCP.h"

#include <map>
#include "FLOAT.H"


// utility class for managing variable input data and answers for a combination at a poi or support
class ComboBenchMark
{
public:
   ComboBenchMark(PoiIDType poiID): 
      m_PoiId(poiID),
      m_MinLiveLoadValue(DBL_MAX),
      m_MaxLiveLoadValue(DBL_MAX),
      m_MinCombinationFactor(DBL_MAX),
      m_MaxCombinationFactor(DBL_MAX)
   {;}

   virtual ~ComboBenchMark()
   {
   };

   PoiIDType GetPoiID()
   {
      return m_PoiId;
   }

   // COMBO INPUT
   // responses for load groups
   HRESULT GetLoadGroupSectionValue(BSTR LoadGroup, BSTR stage, ResultsSummationType summ, bool flip, ISectionResult3Ds * * results);
   HRESULT GetLoadGroupValue(BSTR LoadGroup, BSTR stage, ResultsSummationType summ, IResult3Ds * * results);
   HRESULT GetLoadGroupStressValue(BSTR LoadGroup, BSTR stage, ResultsSummationType summ, ISectionStressResults * * results);

   // live load responses
   HRESULT GetLiveLoadSectionValue( OptimizationType optimization, bool doFlip, ILiveLoadModelSectionResults * * results);
   HRESULT GetLiveLoadSectionValue( OptimizationType optimization, bool doFlip, ISectionResult3Ds * * results);

   HRESULT GetLiveLoadValue( OptimizationType optimization, ILiveLoadModelResults * * results);
   HRESULT GetLiveLoadValue( OptimizationType optimization, IResult3Ds * * results);
   HRESULT GetLiveLoadStress( BSTR stage, OptimizationType optimization, ISectionStressResults * * results);
   
   // poi combination factors
   HRESULT GetCombinationFactors(BSTR stage, LoadCombinationType type, Float64* minFactor, Float64* maxFactor);

   // stresspoints
   HRESULT GetStressPoints(BSTR stage, IStressPoints** sps);

   // BENCHMARKS
   void GetLoadCaseResult(BSTR loadCase, BSTR stage, ResultsSummationType summ, Float64* result);
   void GetLoadCaseStress(BSTR loadCase, BSTR stage, ResultsSummationType summ, Float64* sp1result, Float64* sp2result);
   void GetCombinedResult(BSTR loadCombination, BSTR stage, ResultsSummationType summ, Float64* minResult, Float64* maxResult);
   void GetCombinedStressResult(BSTR loadCombination, BSTR stage, ResultsSummationType summ, OptimizationType opt, Float64* minResult, Float64* maxResult);

   // SET UP
   void SetCombinationFactors(BSTR stage, LoadCombinationType type, Float64 minFactor, Float64 maxFactor);
   void SetStressPoints(BSTR stage, IStressPoints* sps);
   void SetLoadGroupValue(BSTR loadGroup, BSTR stage, ResultsSummationType summ, Float64 value);
   void SetLoadGroupStressValue(BSTR loadGroup, BSTR stage, ResultsSummationType summ, Float64 valsp1, Float64 valsp2);
   void SetLiveLoadValue(Float64 minValue, Float64 maxValue);

   void SetLoadCaseBenchMark(BSTR loadCase, BSTR stage, ResultsSummationType summ, Float64 value);
   void SetLoadCaseStressBenchMark(BSTR loadCase, BSTR stage, ResultsSummationType summ, Float64 sp1value, Float64 sp2value);
   void SetCombinedBenchMark(BSTR loadCombination, BSTR stage, ResultsSummationType summ, Float64 minValue, Float64 maxValue);
   void SetCombinedStressBenchMark(BSTR loadCombination, BSTR stage, ResultsSummationType summ, OptimizationType opt, Float64 sp1Value, Float64 sp2Value);

private:
   // container to hold (string, string, ResultsSummationType) map
   class SslContainer
   {
   public:
      void SetValues( CComBSTR load, CComBSTR stage, ResultsSummationType summ, Float64 minValue, Float64 maxValue)
      {
         ComboMapIterator cmi = m_Results.find(load);
         if (cmi!= m_Results.end())
         {
            // load information is already input
            StageMapIterator stgi = cmi->second.find(stage);
            if (stgi!=cmi->second.end())
            {
               // load and stage are defined
               ResultQuad& res = stgi->second;
               res.SetValues(summ, minValue, maxValue);
           }
            else
            {
               ResultQuad res;
               res.SetValues(summ, minValue, maxValue);
               cmi->second.insert( std::make_pair(stage, res) );
            }
         }
         else
         {
            // neither load nor stage is in list - must define everything and insert
            ResultQuad res;
            res.SetValues(summ, minValue, maxValue);
            StageMap sm;
            sm.insert(std::make_pair(stage, res));
            m_Results.insert(std::make_pair(load, sm));
         }
      }

      HRESULT GetValues( CComBSTR load, CComBSTR stage, ResultsSummationType summ, Float64* minValue, Float64* maxValue)
      {
         ComboMapIterator cmi = m_Results.find(load);
         if (cmi!= m_Results.end())
         {
            // load information is already input
            StageMapIterator stgi = cmi->second.find(stage);
            if (stgi!=cmi->second.end())
            {
               // load and stage are defined
               ResultQuad& res = stgi->second;
               res.GetValues(summ, minValue, maxValue);
            }
            else
            {
               ATLASSERT(0);
               return E_FAIL;
            }
         }
         else
         {
            ATLASSERT(0);
            return E_FAIL;
         }

         return S_OK;
      }
   private:
      struct ResultQuad
      {
         Float64 m_MaxCumulative;
         Float64 m_MinCumulative;
         Float64 m_MaxIncremental;
         Float64 m_MinIncremental;

         ResultQuad():
            m_MaxCumulative(DBL_MAX),
            m_MinCumulative(DBL_MAX),
            m_MaxIncremental(DBL_MAX),
            m_MinIncremental(DBL_MAX)
         {;}

         void SetValues(ResultsSummationType summ, Float64 minValue, Float64 maxValue)
         {
            if (summ==rsCumulative)
            {
               m_MinCumulative = minValue;
               m_MaxCumulative = maxValue;
            }
            else
            {
               m_MinIncremental = minValue;
               m_MaxIncremental = maxValue;
            }
         }

         void GetValues(ResultsSummationType summ, Float64* minValue, Float64* maxValue)
         {
            if (summ==rsCumulative)
            {
               *minValue = m_MinCumulative;
               *maxValue = m_MaxCumulative;
            }
            else
            {
               *minValue = m_MinIncremental;
               *maxValue = m_MaxIncremental;
            }
         }
      };
      typedef std::map<CComBSTR, ResultQuad> StageMap;
      typedef std::map<CComBSTR, StageMap>   ComboMap;

      typedef StageMap::iterator             StageMapIterator;
      typedef ComboMap::iterator             ComboMapIterator;

      ComboMap m_Results;
   };

   // load group results
   SslContainer  m_LoadGroupResults;
   SslContainer  m_LoadGroupStressResults;
   // bench mark results
   SslContainer  m_LoadCaseBenchMarks;
   SslContainer  m_LoadCaseStressBenchMarks;
   SslContainer  m_LoadCombinationBenchMarks;
   SslContainer  m_LoadCombinationMinStressBenchMarks;
   SslContainer  m_LoadCombinationMaxStressBenchMarks;

   Float64        m_MinLiveLoadValue;
   Float64        m_MaxLiveLoadValue;

   Float64        m_MinCombinationFactor;
   Float64        m_MaxCombinationFactor;

   PoiIDType m_PoiId;

   // stress point collections by stage
   typedef std::map<CComBSTR, CComPtr<IStressPoints> > StressPointsMap;
   typedef StressPointsMap::iterator                 StressPointsIterator;

   StressPointsMap  m_StressPoints;

private:
   ComboBenchMark();

};
/////////////////////////////////////////////////////////////////////////////
// CBogusComboContext
class ATL_NO_VTABLE CBogusComboContext : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBogusComboContext, &CLSID_BogusComboContext>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CBogusComboContext>,
	public ILoadCombinationAnalysisContext,
	public ILoadGroupResponse, 
	public ILiveLoadModelResponse,
	public IBasicVehicularResponse,
	public IGetActiveLoadGroups,
	public IGetCombinationFactors,
	public IAnalysisPOIs,
	public ILoadCases,
	public IStages,
	public CProxyDLoadCombinationAnalysisContextEvents< CBogusComboContext >,
	public ILoadCombinations, 
	public ICompareBogusResults,
	public IGetStressPoints
{
public:
	CBogusComboContext()
	{
	}

	~CBogusComboContext()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_BOGUSCOMBOCONTEXT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBogusComboContext)
	COM_INTERFACE_ENTRY(ILoadCombinationAnalysisContext)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ILoadGroupResponse)
	COM_INTERFACE_ENTRY(ILiveLoadModelResponse)
	COM_INTERFACE_ENTRY(IBasicVehicularResponse)
	COM_INTERFACE_ENTRY(IGetActiveLoadGroups)
	COM_INTERFACE_ENTRY(IGetCombinationFactors)
	COM_INTERFACE_ENTRY(IAnalysisPOIs)
	COM_INTERFACE_ENTRY(ILoadCases)
	COM_INTERFACE_ENTRY(IStages)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ILoadCombinations)
	COM_INTERFACE_ENTRY(ICompareBogusResults)
	COM_INTERFACE_ENTRY(IGetStressPoints)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CBogusComboContext)
CONNECTION_POINT_ENTRY(IID_ILoadCombinationAnalysisContextEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILoadCombinationAnalysisContext
public:
	STDMETHOD(Initialize)(/*[in]*/ILBAMModel* model, /*[in]*/ILoadGroupResponse* loadGroupResponse, 
                         /*[in]*/ILiveLoadModelResponse* liveLoadModelResponse, /*[in]*/IBasicVehicularResponse* basicVres,
                         /*[in]*/IAnalysisPOIs* analysisPOIs, /*[in]*/IGetStressPoints* crossSection);
public:
// ILoadGroupResponse
	STDMETHOD(ComputeForces)(BSTR LoadGroup, IIDArray* POIs, BSTR stage, ResultsOrientation Orientation, ResultsSummationType summ, ISectionResult3Ds * * results);
	STDMETHOD(ComputeDeflections)(BSTR LoadGroup, IIDArray* POIs, BSTR stage, ResultsSummationType summ, ISectionResult3Ds * * results);
	STDMETHOD(ComputeReactions)(BSTR LoadGroup, IIDArray* Supports, BSTR stage, ResultsSummationType summ, IResult3Ds * * results);
	STDMETHOD(ComputeSupportDeflections)(BSTR LoadGroup, IIDArray* Supports, BSTR stage, ResultsSummationType summ, IResult3Ds * * results);
	STDMETHOD(ComputeStresses)(BSTR LoadGroup, IIDArray* POIs, BSTR stage, ResultsSummationType summ, ISectionStressResults * * results);

// ILiveLoadModelResponse
	STDMETHOD(ComputeForces)(IIDArray* POIs, BSTR stage, LiveLoadModelType type, ResultsOrientation Orientation, ForceEffectType effect, OptimizationType Optimization, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, VARIANT_BOOL computePlacement, ILiveLoadModelSectionResults * * results);
	STDMETHOD(ComputeDeflections)(IIDArray* POIs, BSTR stage, LiveLoadModelType type, ForceEffectType effect, OptimizationType Optimization, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, VARIANT_BOOL computePlacement, ILiveLoadModelSectionResults * * results);
	STDMETHOD(ComputeReactions)(IIDArray* Supports, BSTR stage, LiveLoadModelType type, ForceEffectType effect, OptimizationType Optimization, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, VARIANT_BOOL computePlacement, ILiveLoadModelResults * * results);
	STDMETHOD(ComputeSupportDeflections)(IIDArray* Supports, BSTR stage, LiveLoadModelType type, ForceEffectType effect, OptimizationType Optimization, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, VARIANT_BOOL computePlacement, ILiveLoadModelResults * * results);
	STDMETHOD(ComputeStresses)(IIDArray* POIs, BSTR stage, LiveLoadModelType type, ForceEffectType effect, OptimizationType Optimization, VehicularLoadConfigurationType vehConfiguration, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistribution, VARIANT_BOOL computePlacement, ILiveLoadModelStressResults * * results);

// IBasicVehicularResponse
	STDMETHOD(ComputeForces)(IIDArray* POIs, BSTR stage, ResultsOrientation Orientation, ILiveLoadConfiguration * config, ISectionResult3Ds * * results);
	STDMETHOD(ComputeDeflections)(IIDArray* POIs, BSTR stage, ILiveLoadConfiguration * config, ISectionResult3Ds * * results);
	STDMETHOD(ComputeReactions)(IIDArray* Supports, BSTR stage, ILiveLoadConfiguration * config, IResult3Ds * * results);
	STDMETHOD(ComputeSupportDeflections)(IIDArray* Supports, BSTR stage, ILiveLoadConfiguration * config, IResult3Ds * * results);
	STDMETHOD(ComputeStresses)(IIDArray* POIs, BSTR stage, ILiveLoadConfiguration * config, ISectionStressResults * * results);

// IGetActiveLoadGroups
	STDMETHOD(GetActiveLoadGroups)(IBstrArray* *loadGroups);

// IGetCombinationFactors
	STDMETHOD(GetPOICombinationFactors)(PoiIDType POI, BSTR stage, LoadCombinationType type, Float64 * minLoadModifier, Float64 * maxLoadModifier);
	STDMETHOD(GetSupportCombinationFactors)(SupportIDType supportID, BSTR stage, LoadCombinationType type, Float64 * minLoadModifier, Float64 * maxLoadModifier);

   // IAnalysisPOIs
	STDMETHOD(get_SpanPoiIncrement)(PoiIDType * pVal);
	STDMETHOD(put_SpanPoiIncrement)(PoiIDType pVal);
	STDMETHOD(get_CantileverPoiIncrement)(PoiIDType * pVal);
	STDMETHOD(put_CantileverPoiIncrement)(PoiIDType pVal);
	STDMETHOD(GetSuperstructurePois)(BSTR stage, IIDArray* * poiIDs, IDblArray* *poiLocations);
	STDMETHOD(GetPoiInfo)(BSTR stage, PoiIDType poiID, MemberType * lbamMemberType, MemberIDType * MemberID, Float64 * memberLocation);

// ILoadCases
	STDMETHOD(get_Item)(CollectionIndexType index, ILoadCase * * pVal);
	STDMETHOD(get__NewEnum)(IUnknown * * retval);
	STDMETHOD(get__EnumElements)(IEnumLoadCase * * pVal);
	STDMETHOD(Find)(BSTR Name, ILoadCase * * __MIDL_0043);
	STDMETHOD(Add)(ILoadCase * __MIDL_0044);
	STDMETHOD(RemoveByName)(BSTR Name);
	STDMETHOD(RemoveByIndex)(CollectionIndexType index, BSTR * Name);
	STDMETHOD(Clone)(ILoadCases * * __MIDL_0045);
	STDMETHOD(Clear)();
	STDMETHOD(get_Count)(CollectionIndexType* pVal);

   // IStages
	STDMETHOD(get_Item)(StageIndexType position, IStage * * pVal);
	STDMETHOD(Add)(IStage * __MIDL_0034);
	STDMETHOD(Insert)(StageIndexType relPosition, IStage * member);
	STDMETHOD(MoveTo)(StageIndexType fromPosition, StageIndexType toPosition);
	STDMETHOD(RemoveByIndex)(StageIndexType position);
	STDMETHOD(Reverse)();
	STDMETHOD(get__EnumElements)(IEnumStage * * pVal);
	STDMETHOD(Clone)(IStages * * Clone);
	STDMETHOD(FindIndex)(BSTR Name, StageIndexType * index);

   // ILoadCombinations
	STDMETHOD(get_Item)(CollectionIndexType index, ILoadCombination * * pVal);
	STDMETHOD(get__EnumElements)(IEnumLoadCombination * * pVal);
	STDMETHOD(Find)(BSTR Name, ILoadCombination * * __MIDL_0046);
	STDMETHOD(Add)(ILoadCombination * __MIDL_0047);
	STDMETHOD(Clone)(ILoadCombinations * * __MIDL_0048);

// IGetStressPoints
	STDMETHOD(GetStressPointsAtPOI)(PoiIDType poiID, BSTR stage, IStressPoints * * LeftStressPoints, IStressPoints * * RightStressPoints);

   // ICompareBogusResults
	STDMETHOD(CompareLoadCaseSectionResults)(BSTR loadCase, BSTR stage, ResultsSummationType summ, VARIANT_BOOL doFlip, ISectionResult3Ds* results);
	STDMETHOD(CompareLoadCaseResults)(BSTR loadCase, BSTR stage, ResultsSummationType summ, IResult3Ds* results);
	STDMETHOD(CompareLoadCaseStressResults)(BSTR loadCase, BSTR stage, ResultsSummationType summ, ISectionStressResults* results);
   STDMETHOD(CompareLoadCombinationSectionResults)(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                                   ForceEffectType fet, OptimizationType opt, VARIANT_BOOL doFlip,
                                                   ILoadCombinationSectionResults* results);
   STDMETHOD(CompareLoadCombinationSectionRes)(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                               OptimizationType opt, VARIANT_BOOL doFlip, 
                                               ISectionResult3Ds* results);
   STDMETHOD(CompareLoadCombinationResults)(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                                   ForceEffectType fet, OptimizationType opt,
                                                   ILoadCombinationResults* results);
   STDMETHOD(CompareLoadCombinationRes)(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                        OptimizationType opt, IResult3Ds* results);

   STDMETHOD(CompareLoadCombinationStressResults)(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                                   ForceEffectType fet, OptimizationType opt,
                                                   ILoadCombinationStressResults* results);
   STDMETHOD(CompareLoadCombinationStressRes)(BSTR loadCombo, BSTR stage, ResultsSummationType summ, 
                                        OptimizationType opt, ISectionStressResults* results);
private:
   // data members
   CComPtr<IStage> m_Stage1;
   CComPtr<IStage> m_Stage2;
   CComPtr<IStage> m_Stage3;

   CComPtr<ILoadCase> m_LoadCase1;
   CComPtr<ILoadCase> m_LoadCase2;
   CComPtr<ILoadCase> m_LoadCase3;

   CComPtr<ILoadCombination> m_LoadCombo1;
   CComPtr<ILoadCombination> m_LoadCombo2;
   CComPtr<ILoadCombination> m_LoadCombo3;

   typedef std::map<PoiIDType, ComboBenchMark> BenchMarkMap;
   typedef BenchMarkMap::iterator         BenchMarkIterator;

   BenchMarkMap m_BenchMarks;
};

#endif //__BOGUSCOMBOCONTEXT_H_
