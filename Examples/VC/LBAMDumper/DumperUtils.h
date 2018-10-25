#ifndef __LBAMDumperUtils_H_
#define __LBAMDumperUtils_H_

#include <WBFLLBAMUtility.h>
#include <System\NumericFormatTool.h>
#include <vector>

using namespace std;

static std::_tstring TkdToString(TruckDirectionType type)
{
   std::_tstring strtype;
   if (type==ltdForward)
   {
      strtype = _T("Forward");
   }
   else if (type==ltdReverse)
   {
      strtype = _T("Reverse");
   }
   else
      ATLASSERT(0);

   return strtype;
}


static std::_tstring VbToString(VARIANT_BOOL vb)
{
   std::_tstring strtype;
   if (vb!=VARIANT_FALSE)
   {
      strtype = _T("True");
   }
   else
   {
      strtype = _T("False");
   }

   return strtype;
}

static std::_tstring OptToString(OptimizationType type)
{
   std::_tstring strtype;
   if (type==optMinimize)
   {
      strtype = _T("Minimize");
   }
   else if (type==optMaximize)
   {
      strtype = _T("Maximize");
   }
   else 
   {
      ATLASSERT(0);
   }

   return strtype;
}

static std::_tstring FetToString(ForceEffectType type)
{
   std::_tstring strtype;
   if (type==fetFx)
   {
      strtype = _T("Fx");
   }
   else if (type==fetFy)
   {
      strtype = _T("Fy");
   }
   else if (type==fetMz)
   {
      strtype = _T("Mz");
   }
   else 
   {
      ATLASSERT(0);
   }

   return strtype;
}


static std::_tstring VlcToString(VehicularLoadConfigurationType vlc)
{
   std::_tstring str;
   switch(vlc)
   {
   case vlcDefault:
      str = _T("Default");
      break;
   case vlcTruckOnly:
      str = _T("Truck Only");
      break;
   case vlcLaneOnly:
      str = _T("Lane Only");
      break;
   case vlcTruckPlusLane:
      str = _T("Truck Plus Lane");
      break;
   case vlcTruckLaneEnvelope:
      str = _T("Truck Lane Envelope");
      break;
   case vlcSidewalkOnly:
      str = _T("Sidewalk Only");
      break;
   default:
      ATLASSERT(0);
   }

   return str;
}

static std::_tstring DftToString(DistributionFactorType type)
{
   std::_tstring strtype;
   if (type==dftNone)
   {
      strtype = _T("None");
   }
   else if (type==dftSingleLane)
   {
      strtype = _T("SingleLane");
   }
   else if (type==dftMultipleLane)
   {
      strtype = _T("MultipleLane");
   }
   else if (type==dftEnvelope)
   {
      strtype = _T("Envelope");
   }
   else if (type==dftFatigue)
   {
      strtype = _T("Fatigue");
   }
   else if (type==dftPedestrian)
   {
      strtype = _T("Pedestrian");
   }
   else 
   {
      ATLASSERT(0);
   }

   return strtype;
}

static std::_tstring LlMtToString(LiveLoadModelType type)
{
   std::_tstring strtype;
   if (type==lltNone)
   {
      strtype = _T("None");
   }
   else if (type==lltDeflection)
   {
      strtype = _T("Deflection");
   }
   else if (type==lltDesign)
   {
      strtype = _T("Design");
   }
   else if (type==lltPedestrian)
   {
      strtype = _T("Pedestrian");
   }
   else if (type==lltFatigue)
   {
      strtype = _T("Fatigue");
   }
   else if (type==lltPermit)
   {
      strtype = _T("Permit");
   }
   else if (type==lltSpecial)
   {
      strtype = _T("Special");
   }
   else 
   {
      ATLASSERT(0);
   }

   return strtype;
}

static std::_tstring MTToString(MemberType type)
{
   std::_tstring strtype;
   if (type==mtSpan)
   {
      strtype = _T("Span");
   }
   else if (type==mtSuperstructureMember)
   {
      strtype = _T("SuperstructureMember");
   }
   else if (type == mtSupport)
   {
      strtype = _T("Support");
   }
   else if (type == mtTemporarySupport)
   {
      strtype = _T("TemporarySupport");
   }
   else if (type == mtUndefined)
   {
      strtype = _T("Undefined");
   }
   else
   {
      ATLASSERT(0);
   }

   return strtype;
}




// utility class for keeping sorted pois for response dumps, etc
class CDumperUtil
{
public:
   CDumperUtil(ILBAMAnalysisEngine* engine, bool doDumpDetails):
   m_Engine(engine),
   m_DoDumpDetails(doDumpDetails),
   m_Dirty(true),
   m_Ff(sysNumericFormatTool::Fixed, 11, 3),
   m_Fd(sysNumericFormatTool::Fixed, 11, 3),
   m_Fl(sysNumericFormatTool::Fixed, 12, 4)
   {
   }

   bool DoDetails() const
   {
      return m_DoDumpDetails;
   }


   // numeric formatters
   std::_tstring Ff(double val)  // force
   {
      if (fabs(val)<1.0e-07)
         val = 0.0;

      return m_Ff.AsString(val);
   }

   std::_tstring Fd(double val)  // deflection
   {
      if (fabs(val)<1.0e-09)
         val = 0.0;

      return m_Fd.AsString(val);
   }

   std::_tstring Fl(double val)  // location
   {
      if (fabs(val)<1.0e-07)
         val = 0.0;

      return m_Fl.AsString(val);
   }

   void GetSuperstructurePOIs(StageIndexType iStage, ResultsSummationType summ, IIDArray** poiIDs, IDblArray** poiLocs);
   void GetSupportPOIs(StageIndexType iStage, IIDArray** poiIDs);
   void GetSupportIDs(StageIndexType iStage,  IIDArray** poiIDs);
   void GetAllPOIs(StageIndexType iStage, ResultsSummationType summ, IIDArray** poiIDs);

   StageIndexType StageCount();
   void StageName(StageIndexType i, BSTR* name);

private:
   CDumperUtil();
   void Compute();

   CComPtr<ILBAMAnalysisEngine> m_Engine;

   bool m_Dirty;
   bool m_DoDumpDetails;
   std::vector< CAdapt< CComPtr<IIDArray> > > m_SsPoiIds;
   std::vector< CAdapt< CComPtr<IDblArray> > > m_SsPoiLocs;

   std::vector< CAdapt< CComPtr<IIDArray> > > m_CumSsPoiIds;
   std::vector< CAdapt< CComPtr<IDblArray> > > m_CumSsPoiLocs;

   std::vector< CAdapt< CComPtr<IIDArray> > > m_SptPoiIds;

   std::vector< CAdapt< CComBSTR > > m_StageNames;

   CComPtr<ILBAMFactory> m_Factory;

   sysNumericFormatTool m_Ff;
   sysNumericFormatTool m_Fd;
   sysNumericFormatTool m_Fl;

};

// Shorcuts for using formatting tool. 
// Client class must have a member CDumperUtil* called m_Util
#define Ff(val) m_Util->Ff(val)
#define Fd(val) m_Util->Fd(val)
#define Fl(val) m_Util->Fl(val)


static void DumpLiveLoadConfiguration(std::_tostream& os, ILiveLoadConfiguration* config, AxleIndexType axleCnt, CDumperUtil* m_Util)
{
   CHRException hr;
   USES_CONVERSION;

   VehicleIndexType veh_idx;
	hr = config->get_VehicleIndex(&veh_idx);

   LiveLoadModelType llm_type;
	hr = config->get_LiveLoadModel(&llm_type);

   DistributionFactorType df_type;
	hr = config->get_DistributionFactorType(&df_type);

   VARIANT_BOOL is_app;
	hr = config->get_IsApplicable(&is_app);

   VARIANT_BOOL is_imp;
	hr = config->get_DoApplyImpact(&is_imp);

   CComPtr<IIndexArray> axle_cfg;
	hr = config->get_AxleConfig( &axle_cfg);

   double var_spc;
	hr = config->get_VariableSpacing(&var_spc);

   TruckDirectionType trk_dir;
	hr = config->get_TruckDirection(&trk_dir);

   double trk_pos;
	hr = config->get_TruckPosition(&trk_pos);

   VehicularLoadConfigurationType vlc;
	hr = config->get_VehicularLoadConfiguration( &vlc);

   ForceEffectType fet;
	hr = config->get_ForceEffect(&fet);

   OptimizationType opt;
	hr = config->get_Optimization(&opt);

   AxleIndexType pivotAxleIndex;
   config->get_PivotAxleIndex(&pivotAxleIndex);

   os<<"================================"<<endl;
   os<<" Dump of Live Load Configuration"<<endl;

   os<<"  Live Load    Veh.  Dist Factor Apply    Vehicular Load     Force                   Is       Truck     Truck       Pivot     Variable    Axle Configuration"<<endl;
   os<<"  Model Type  Index     Type     Impact    Configuration     Effect Optimization Applicable  Position  Direction    Axle      Axle Spcg     ( <-Front  )    "<<endl;
   os<<" ------------ ----- ------------ ------ -------------------- ------ ------------ ---------- ---------- ---------- ---------- ---------- --------------------"<<endl;
//                                                                                           ---------|---------|---------|
   std::_tstring strtrkpos;
   std::_tstring strtrkdir;
   std::_tstring strvarspc;
   std::_tstring straxlcfg;
   if (is_app != VARIANT_FALSE)
   {
      strtrkpos = Ff(trk_pos);
      strtrkdir = TkdToString(trk_dir);
      strvarspc = Ff(var_spc);

      // string showing axles up or down
      straxlcfg.assign(axleCnt, '|');
      CollectionIndexType nax_cnt;
      hr = axle_cfg->get_Count(&nax_cnt);
      for (CollectionIndexType ix=0; ix<nax_cnt; ix++)    // loop over inactive axles
      {
         CollectionIndexType nax;
         hr = axle_cfg->get_Item(ix, &nax);

         straxlcfg.at(nax) = '0';
      }
   }

   os<<left<<" "<<setw(12)<<LlMtToString(llm_type)<<right<<setw(6)<<veh_idx<<" "<<left<<setw(13)<<DftToString(df_type)<<setw(7)<<VbToString(is_imp)
     <<setw(20)<<VlcToString(vlc)<<" "<<setw(7)<<FetToString(fet)<<setw(13)<<OptToString(opt)<<setw(10)<<VbToString(is_app)
     <<right<<setw(11)<<strtrkpos<<setw(11)<<strtrkdir <<setw(10)<<pivotAxleIndex<<" " <<setw(10)<<strvarspc<<left<<" "<<setw(20)<<straxlcfg<<endl;
}

inline void GetLiveLoadModel(LiveLoadModelType type, ILiveLoad* pll, ILiveLoadModel** ppLlm)
{
   CHRException hr;

   switch(type)
   {
   case lltDeflection:
      hr = pll->get_Deflection(ppLlm);
      break;
   case lltDesign:  
      hr = pll->get_Design(ppLlm);
      break;
   case lltPedestrian:
      hr = pll->get_Pedestrian(ppLlm);
      break;
   case lltFatigue:  
      hr = pll->get_Fatigue(ppLlm);
      break;
   case lltPermit:
      hr = pll->get_Permit(ppLlm);
      break;
   case lltSpecial:
      hr = pll->get_Special(ppLlm);
      break;
   default:
      ATLASSERT(0);
      hr = E_FAIL;
   };
}


static AxleIndexType GetAxleCnt(IVehicularLoads* vloads, ILiveLoadConfiguration* config)
{
   CHRException hr;
   VehicleIndexType index;
   hr = config->get_VehicleIndex(&index);

   CComPtr<IVehicularLoad> vload;
   hr = vloads->get_Item(index, &vload);

   CComPtr<IAxles> axles;
   hr = vload->get_Axles(&axles);

   AxleIndexType axle_cnt;
   hr = axles->get_Count(&axle_cnt);

   return axle_cnt;
}

#endif