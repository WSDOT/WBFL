#ifndef __LBAMDumperUtils_H_
#define __LBAMDumperUtils_H_

#include <WBFLLBAMUtility.h>
#include <System\NumericFormatTool.h>
#include <vector>

using namespace std;

static std::string TkdToString(TruckDirectionType type)
{
   std::string strtype;
   if (type==ltdForward)
   {
      strtype = "Forward";
   }
   else if (type==ltdReverse)
   {
      strtype = "Reverse";
   }
   else
      ATLASSERT(0);

   return strtype;
}


static std::string VbToString(VARIANT_BOOL vb)
{
   std::string strtype;
   if (vb!=VARIANT_FALSE)
   {
      strtype = "True";
   }
   else
   {
      strtype = "False";
   }

   return strtype;
}

static std::string OptToString(OptimizationType type)
{
   std::string strtype;
   if (type==optMinimize)
   {
      strtype = "Minimize";
   }
   else if (type==optMaximize)
   {
      strtype = "Maximize";
   }
   else 
   {
      ATLASSERT(0);
   }

   return strtype;
}

static std::string FetToString(ForceEffectType type)
{
   std::string strtype;
   if (type==fetFx)
   {
      strtype = "Fx";
   }
   else if (type==fetFy)
   {
      strtype = "Fy";
   }
   else if (type==fetMz)
   {
      strtype = "Mz";
   }
   else 
   {
      ATLASSERT(0);
   }

   return strtype;
}


static std::string VlcToString(VehicularLoadConfigurationType vlc)
{
   std::string str;
   switch(vlc)
   {
   case vlcDefault:
      str = "Default";
      break;
   case vlcTruckOnly:
      str = "Truck Only";
      break;
   case vlcLaneOnly:
      str = "Lane Only";
      break;
   case vlcTruckPlusLane:
      str = "Truck Plus Lane";
      break;
   case vlcTruckLaneEnvelope:
      str = "Truck Lane Envelope";
      break;
   case vlcSidewalkOnly:
      str = "Sidewalk Only";
      break;
   default:
      ATLASSERT(0);
   }

   return str;
}

static std::string DftToString(DistributionFactorType type)
{
   std::string strtype;
   if (type==dftNone)
   {
      strtype = "None";
   }
   else if (type==dftSingleLane)
   {
      strtype = "SingleLane";
   }
   else if (type==dftMultipleLane)
   {
      strtype = "MultipleLane";
   }
   else if (type==dftEnvelope)
   {
      strtype = "Envelope";
   }
   else if (type==dftFatigue)
   {
      strtype = "Fatigue";
   }
   else 
   {
      ATLASSERT(0);
   }

   return strtype;
}

static std::string LlMtToString(LiveLoadModelType type)
{
   std::string strtype;
   if (type==lltNone)
   {
      strtype = "None";
   }
   else if (type==lltDeflection)
   {
      strtype = "Deflection";
   }
   else if (type==lltDesign)
   {
      strtype = "Design";
   }
   else if (type==lltPedestrian)
   {
      strtype = "Pedestrian";
   }
   else if (type==lltFatigue)
   {
      strtype = "Fatigue";
   }
   else if (type==lltPermit)
   {
      strtype = "Permit";
   }
   else if (type==lltSpecial)
   {
      strtype = "Special";
   }
   else 
   {
      ATLASSERT(0);
   }

   return strtype;
}

static std::string MTToString(MemberType type)
{
   std::string strtype;
   if (type==mtSpan)
   {
      strtype = "Span";
   }
   else if (type==mtSuperstructureMember)
   {
      strtype = "SuperstructureMember";
   }
   else if (type == mtSupport)
   {
      strtype = "Support";
   }
   else if (type == mtTemporarySupport)
   {
      strtype = "TemporarySupport";
   }
   else if (type == mtUndefined)
   {
      strtype = "Undefined";
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
   std::string Ff(double val)  // force
   {
      if (fabs(val)<1.0e-07)
         val = 0.0;

      return m_Ff.AsString(val);
   }

   std::string Fd(double val)  // deflection
   {
      if (fabs(val)<1.0e-09)
         val = 0.0;

      return m_Fd.AsString(val);
   }

   std::string Fl(double val)  // location
   {
      if (fabs(val)<1.0e-07)
         val = 0.0;

      return m_Fl.AsString(val);
   }

   void GetSuperstructurePOIs(long iStage, ResultsSummationType summ, ILongArray** poiIDs, IDblArray** poiLocs);
   void GetSupportPOIs(long iStage, ILongArray** poiIDs);
   void GetSupportIDs(long iStage,  ILongArray** poiIDs);
   void GetAllPOIs(long iStage, ResultsSummationType summ, ILongArray** poiIDs);

   long StageCount();
   void StageName(long i, BSTR* name);

private:
   CDumperUtil();
   void Compute();

   CComPtr<ILBAMAnalysisEngine> m_Engine;

   bool m_Dirty;
   bool m_DoDumpDetails;
   std::vector< CAdapt< CComPtr<ILongArray> > > m_SsPoiIds;
   std::vector< CAdapt< CComPtr<IDblArray> > > m_SsPoiLocs;

   std::vector< CAdapt< CComPtr<ILongArray> > > m_CumSsPoiIds;
   std::vector< CAdapt< CComPtr<IDblArray> > > m_CumSsPoiLocs;

   std::vector< CAdapt< CComPtr<ILongArray> > > m_SptPoiIds;

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


static void DumpLiveLoadConfiguration(std::ostream& os, ILiveLoadConfiguration* config, long axleCnt, CDumperUtil* m_Util)
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

   CComPtr<ILongArray> axle_cfg;
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
   std::string strtrkpos;
   std::string strtrkdir;
   std::string strvarspc;
   std::string straxlcfg;
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
         AxleIndexType nax;
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


static long GetAxleCnt(IVehicularLoads* vloads, ILiveLoadConfiguration* config)
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