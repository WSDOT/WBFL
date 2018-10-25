// LiveLoadDumper.h: interface for the CLiveLoadDumper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIVELOADDUMPER_H__0F75E61A_17D0_4872_BF8C_0845609B3635__INCLUDED_)
#define AFX_LIVELOADDUMPER_H__0F75E61A_17D0_4872_BF8C_0845609B3635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DumperUtils.h"


// utility class to allow stacking up of optimization parameters for the live load dump
class CEvrParameterStack
{
public:

   CEvrParameterStack();
   void Init();

   struct LlParams
   {
      LlParams(ForceEffectType fet, OptimizationType Opt, VARIANT_BOOL applyImpact):
      ForceEffect(fet),
      Optimization(Opt),
      DoApplyImpact(applyImpact)
      {;}


      std::_tstring AsString(bool isForce) const;
     

      ForceEffectType  ForceEffect;
      OptimizationType Optimization;
      VARIANT_BOOL     DoApplyImpact;
   };

   class iterator
   {
      friend CEvrParameterStack;
   public:
      iterator& operator ++(int)
      {
         m_Iter++;
         return *this;
      }

      bool operator!=(const iterator& other)
      {
         return m_Iter!=other.m_Iter;
      }

      const LlParams& operator *() const
      {
         return *m_Iter;
      }

   private:
      std::vector<LlParams>::iterator m_Iter;
   };

   iterator begin()
   {
      iterator it;
      it.m_Iter = m_Params.begin();
      return it;
   }

   iterator end()
   {
      iterator it;
      it.m_Iter = m_Params.end();
      return it;
   }

private:
   std::vector<LlParams> m_Params;
};

class CLlmParameterStack
{
public:

   CLlmParameterStack();
   void Init();

   struct LlParams
   {
      LlParams(ForceEffectType fet, OptimizationType Opt, VARIANT_BOOL applyImpact, VARIANT_BOOL applyDistf):
      ForceEffect(fet),
      Optimization(Opt),
      DoApplyImpact(applyImpact),
      DoApplyDistf(applyDistf)
      {;}


      std::_tstring AsString(bool isForce) const;
     

      ForceEffectType  ForceEffect;
      OptimizationType Optimization;
      VARIANT_BOOL     DoApplyImpact;
      VARIANT_BOOL     DoApplyDistf;
   };

   class iterator
   {
      friend CLlmParameterStack;
   public:
      iterator& operator ++(int)
      {
         m_Iter++;
         return *this;
      }

      bool operator!=(const iterator& other)
      {
         return m_Iter!=other.m_Iter;
      }

      const LlParams& operator *() const
      {
         return *m_Iter;
      }

   private:
      std::vector<LlParams>::iterator m_Iter;
   };

   iterator begin()
   {
      iterator it;
      it.m_Iter = m_Params.begin();
      return it;
   }

   iterator end()
   {
      iterator it;
      it.m_Iter = m_Params.end();
      return it;
   }

private:
   std::vector<LlParams> m_Params;
};



class CLiveLoadDumper  
{
public:
	CLiveLoadDumper(ILBAMAnalysisEngine* engine, CDumperUtil* util);
	virtual ~CLiveLoadDumper();

   void DumpEnvelopedVehicularResponse(std::_tostream& os, std::_tostream& cos);
   void DumpLiveLoadModelResponse(std::_tostream& os, std::_tostream& cos);

private:
	CLiveLoadDumper();
   void DumpEvrForces(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName);
   void DumpEvrDeflections(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName);
   void DumpEvrStresses(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName);
   void DumpEvrReactions(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName);
   void DumpEvrSupportDeflections(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName);

   void DumpLlmForces(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName);
   void DumpLlmDeflections(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName);
   void DumpLlmStresses(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName);
   void DumpLlmReactions(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName);
   void DumpLlmSupportDeflections(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName);
   
   CComPtr<ILBAMAnalysisEngine> m_Engine;
   CComPtr<ILiveLoadModelResponse> m_LLM;
   CComPtr<IEnvelopedVehicularResponse> m_EVR;
   CComPtr<IBasicVehicularResponse>     m_BVR;
   CDumperUtil*                 m_Util;
   CComBSTR                     m_Stage;
   CollectionIndexType          m_StageId;

   CLlmParameterStack            m_LlmParams; // stack of max/min live load parameters
   CEvrParameterStack            m_EvrParams; // stack of max/min live load parameters

   long                         m_LastKey;

};

#endif // !defined(AFX_LIVELOADDUMPER_H__0F75E61A_17D0_4872_BF8C_0845609B3635__INCLUDED_)
