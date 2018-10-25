// LoadCombinationDumper.cpp: implementation of the CLoadCombinationDumper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoadCombinationDumper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// utility class to allow stacking up of optimization parameters for the load combination
struct LcParams
{
   LcParams(BSTR lcName, StageIndexType iStg, ForceEffectType fet, OptimizationType Opt, 
            ResultsSummationType summ, VARIANT_BOOL includeLL):
   LcName(lcName),
   Stage(iStg),
   ForceEffect(fet),
   Optimization(Opt),
   Summation(summ),
   DoIncludeLiveLoad(includeLL)
   {;}

   std::_tstring AsString(bool isForce, CDumperUtil* util) const;
  
   CComBSTR             LcName;
   StageIndexType       Stage;
   ForceEffectType      ForceEffect;
   OptimizationType     Optimization;
   VARIANT_BOOL         DoIncludeLiveLoad;
   ResultsSummationType Summation;
};


class CLcParameterStack
{
public:

   CLcParameterStack()
   {;}
   void Init(ILBAMAnalysisEngine* Engine);

   class iterator
   {
      friend CLcParameterStack;
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

      const LcParams& operator *() const
      {
         return *m_Iter;
      }

   private:
      std::vector<LcParams>::iterator m_Iter;
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
   std::vector<LcParams> m_Params;
};

void CLcParameterStack::Init(ILBAMAnalysisEngine* Engine)
{
   CHRException hr;

   CComPtr<ILBAMModel> model;
   hr = Engine->get_Model(&model);

   CComPtr<ILoadCombinations> loadcombos;
   hr = model->get_LoadCombinations(&loadcombos);

   CollectionIndexType lc_cnt;
   hr = loadcombos->get_Count(&lc_cnt);

   CComPtr<IStages> stages;
   hr = model->get_Stages(&stages);

   StageIndexType stg_cnt;
   hr = stages->get_Count(&stg_cnt);

   // build paramters in the order in which they will be run
   for (CollectionIndexType ilc=0; ilc<lc_cnt; ilc++)
   {
      CComPtr<ILoadCombination> load_combo;
      hr = loadcombos->get_Item(ilc, &load_combo);

      CComBSTR lc_name;
      hr = load_combo->get_Name(&lc_name);

      for (StageIndexType istg=0; istg<stg_cnt; istg++)
      {
         // only apply live load in last stage
         VARIANT_BOOL do_apply_liveload;
         if (istg<stg_cnt-1)
            do_apply_liveload = VARIANT_FALSE;
         else
            do_apply_liveload = VARIANT_TRUE;

         for (StageIndexType is=0; is<2; is++)
         {
            ResultsSummationType rs_type = (is==0 ? rsIncremental : rsCumulative);

            m_Params.push_back( LcParams(lc_name, istg, fetFx, optMaximize, rs_type, do_apply_liveload) );
            m_Params.push_back( LcParams(lc_name, istg, fetFx, optMinimize, rs_type, do_apply_liveload) );
            m_Params.push_back( LcParams(lc_name, istg, fetFy, optMaximize, rs_type, do_apply_liveload) );
            m_Params.push_back( LcParams(lc_name, istg, fetFy, optMinimize, rs_type, do_apply_liveload) );
            m_Params.push_back( LcParams(lc_name, istg, fetMz, optMaximize, rs_type, do_apply_liveload) );
            m_Params.push_back( LcParams(lc_name, istg, fetMz, optMinimize, rs_type, do_apply_liveload) );
         }
      }
   }
}

std::_tstring LcParams::AsString(bool isForce, CDumperUtil* util) const
{
   USES_CONVERSION;

   std::_tostringstream msg;

   CComBSTR stgnm;
   util->StageName(Stage, &stgnm);

   msg<<"Load Combination \""<<W2A(LcName)<<"\" in Stage \""<<W2A(stgnm)<<"\" for ";

   if (Optimization==optMaximize)
      msg<<"Maximized ";
   else
      msg<<"Minimized ";

   if (Summation==rsIncremental)
      msg<<"Incremental ";
   else
      msg<<"Cumulative ";

   if (isForce)
   {
      if (ForceEffect==fetFx)
         msg<<"Fx Force, ";
      else if (ForceEffect==fetFy)
         msg<<"Fy Force, ";
      else if (ForceEffect==fetMz)
         msg<<"Mz Moment, ";
      else
         ATLASSERT(0);
   }
   else
   {
      if (ForceEffect==fetFx)
         msg<<"Dx Deflection, ";
      else if (ForceEffect==fetFy)
         msg<<"Dy Deflection,";
      else if (ForceEffect==fetMz)
         msg<<"Rz Deflection, ";
      else
         ATLASSERT(0);
   }

   if (DoIncludeLiveLoad!=VARIANT_FALSE)
      msg<<"Live Load Included";
   else
      msg<<"Live Load not Included";

   return msg.str();
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoadCombinationDumper::CLoadCombinationDumper(ILBAMAnalysisEngine* engine, CDumperUtil* util):
m_Engine(engine),
m_Util(util),
m_LastKey(5000000)
{
   HRESULT hr;
   hr = engine->get_LoadCombinationResponse(&m_LCR);
   hr = engine->get_ConcurrentLoadCombinationResponse(&m_CCR);

}

CLoadCombinationDumper::~CLoadCombinationDumper()
{

}


void CLoadCombinationDumper::DumpLoadCaseResponse(std::_tostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   os<<endl<<endl;
   os<<" DUMP OF LOADCASE RESPONSES"<<endl;
   os<<" =========================="<<endl<<endl;

   // first need to report the load groups where there were no responses
   CComPtr<ILBAMModel> model;
   hr = m_Engine->get_Model(&model);

   CComPtr<ILoadCases> loadcases;
   hr = model->get_LoadCases(&loadcases);

   CComPtr<ILoadCaseResponse> lc_response;
   hr = m_Engine->get_LoadCaseResponse(&lc_response);
   
   CComQIPtr<IGetActiveLoadCases> galc(lc_response);
   ATLASSERT(galc);

   CComPtr<IBstrArray> active_lcs;
   hr = galc->GetActiveLoadCases(&active_lcs);

   // loop over all loadcases and find the dead ones
   CComPtr<IBstrArray> dead_lcs;
   hr = dead_lcs.CoCreateInstance(CLSID_BstrArray);

   CollectionIndexType lc_cnt;
   hr = loadcases->get_Count(&lc_cnt);
   for (CollectionIndexType ilc=0; ilc<lc_cnt; ilc++)
   {
      CComPtr<ILoadCase> loadcase;
      hr = loadcases->get_Item(ilc, &loadcase);

      CComBSTR lc_name;
      hr = loadcase->get_Name(&lc_name);

      CollectionIndexType idx;
      active_lcs->Find(lc_name, &idx);
      if (idx == -1)
      {
         // not found in active list
         hr = dead_lcs->Add(lc_name);
      }
   }

   CollectionIndexType dead_cnt;
   hr = dead_lcs->get_Count(&dead_cnt);
   if (dead_cnt>0)
   {
      os<<"  There are "<<dead_cnt<<" LoadCases in this model with no loads (zero results). They are: "<<endl;
      for (CollectionIndexType ilc=0; ilc<dead_cnt; ilc++)
      {
         CComBSTR name;
         hr = dead_lcs->get_Item(ilc, &name);
         os<<"    "<<W2A(name)<<endl;
      }

      os<<"  No Results will be be reported for these LoadCases"<<endl<<endl;
   }

   // loop over all of our active loadcases and stages and report responses
   StageIndexType stg_cnt = m_Util->StageCount();

   CollectionIndexType alc_cnt;
   hr = active_lcs->get_Count(&alc_cnt);
   for (CollectionIndexType ilc=0; ilc<alc_cnt; ilc++)
   {
      CComBSTR lc_name;
      hr = active_lcs->get_Item(ilc, &lc_name);

      // forces
      for (StageIndexType ist=0; ist<stg_cnt; ist++)
      {
         DumpLoadCaseForces(os, lc_name, ist, rsIncremental);
         DumpLoadCaseForces(os, lc_name, ist, rsCumulative);
      }

      // deflections
      for (StageIndexType ist=0; ist<stg_cnt; ist++)
      {
         DumpLoadCaseDeflections(os, lc_name, ist, rsIncremental);
         DumpLoadCaseDeflections(os, lc_name, ist, rsCumulative);
      }

      // stresses
      for (StageIndexType ist=0; ist<stg_cnt; ist++)
      {
         DumpLoadCaseStresses(os, lc_name, ist, rsIncremental);
         DumpLoadCaseStresses(os, lc_name, ist, rsCumulative);
      }

   }
}


void CLoadCombinationDumper::DumpLoadCaseForces(std::_tostream& os, BSTR lcName, StageIndexType ist, ResultsSummationType summ)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   os<<endl;
   os<<"   Forces for LoadCase: \""<<W2A(lcName)<<"\", Stage: \""<<W2A(stage)<<"\", SummationType:"<<(summ==rsIncremental?"Incremental":"Cumulative")<<endl<<endl;
   os<<"   Superstructure POIs sorted by location"<<endl;
   os<<"   --------------------------------------"<<endl;
   os<<endl;
   os<<"                   <----------- Left -------------> <----------- Right ------------>"<<endl;
   os<<"  POI   Location     Axial       Shear      Moment    Axial      Shear      Moment"<<endl;
   os<<" ------ ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;

   // compute member responses
   CComPtr<IIDArray> poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, summ, &poi_ids, &poi_locs);

   CComPtr<ILoadCaseResponse> response;
   hr = m_Engine->get_LoadCaseResponse(&response);

   CComPtr<ISectionResult3Ds> force_results;
   hr=response->ComputeForces(lcName, poi_ids, stage, roMember, summ, &force_results);

   CollectionIndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (CollectionIndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      double rgt_moment, rgt_shear, rgt_axial;
      double lft_moment, lft_shear, lft_axial;
      CComPtr<ISectionResult3D> force_result;
      hr = force_results->get_Item(ip, &force_result);
      hr = force_result->get_XLeft(&lft_axial);
      hr = force_result->get_YLeft(&lft_shear);
      hr = force_result->get_ZLeft(&lft_moment);
      hr = force_result->get_XRight(&rgt_axial);
      hr = force_result->get_YRight(&rgt_shear);
      hr = force_result->get_ZRight(&rgt_moment);

      double poi_loc;
      hr = poi_locs->get_Item(ip,&poi_loc);
      os<<right<<setw(7)<<poi_id<<Fl(poi_loc)
        <<Ff(lft_axial)<<Ff(lft_shear)<<Ff(lft_moment)
        <<Ff(rgt_axial)<<Ff(rgt_shear)<<Ff(rgt_moment)<<endl;
   }

   os<<endl;
   os<<"   Support POIs (forces in member coordinates)"<<endl;
   os<<"   -------------------------------------------"<<endl;

   os<<endl;
   os<<"        <----------- Left -------------> <----------- Right ------------>"<<endl;
   os<<"  POI      Axial      Shear      Moment    Axial      Shear      Moment"<<endl;
   os<<" ------ ---------- ---------- ---------- ---------- ---------- ----------"<<endl;

   // compute member responses
   CComPtr<IIDArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   CComPtr<ISectionResult3Ds> spt_force_results;
   hr=response->ComputeForces(lcName, spt_poi_ids, stage, roMember, summ, &spt_force_results);

   CollectionIndexType num_spt_pois;
   hr = spt_poi_ids->get_Count(&num_spt_pois);
   for (CollectionIndexType ip=0; ip<num_spt_pois; ip++)
   {
      PoiIDType poi_id;
      hr = spt_poi_ids->get_Item(ip, &poi_id);

      double rgt_moment, rgt_shear, rgt_axial;
      double lft_moment, lft_shear, lft_axial;
      CComPtr<ISectionResult3D> force_result;
      hr = spt_force_results->get_Item(ip, &force_result);
      hr = force_result->get_XLeft(&lft_axial);
      hr = force_result->get_YLeft(&lft_shear);
      hr = force_result->get_ZLeft(&lft_moment);
      hr = force_result->get_XRight(&rgt_axial);
      hr = force_result->get_YRight(&rgt_shear);
      hr = force_result->get_ZRight(&rgt_moment);

      os<<right<<setw(7)<<poi_id
        <<Ff(lft_axial)<<Ff(lft_shear)<<Ff(lft_moment)
        <<Ff(rgt_axial)<<Ff(rgt_shear)<<Ff(rgt_moment)<<endl;
   }

   os<<endl;
   os<<"   Reactions (global coordinates)"<<endl
     <<"   ------------------------------"<<endl;
   CComPtr<IIDArray> supp_ids;
   m_Util->GetSupportIDs(ist, &supp_ids);

   CComPtr<IResult3Ds> react_results;
   hr=response->ComputeReactions(lcName, supp_ids, stage, summ, &react_results);

   os<<"   POI    X React    Y React    MZ React"<<std::endl;
   os<<" ------ ---------- ---------- ----------"<<std::endl;

   CollectionIndexType num_supp;
   hr = supp_ids->get_Count(&num_supp);
   for (CollectionIndexType is=0; is<num_supp; is++)
   {
      PoiIDType poi_id;
      hr = supp_ids->get_Item(is,&poi_id);

      double xreac, yreac, zreac;
      CComPtr<IResult3D> react_result;
      hr = react_results->get_Item(is, &react_result);
      hr = react_result->get_X(&xreac);
      hr = react_result->get_Y(&yreac);
      hr = react_result->get_Z(&zreac);

      os<<std::setw(7)<<poi_id<<Ff(xreac)<<Ff(yreac)<<Ff(zreac)<<endl;
   }

   os<<endl;
}

void CLoadCombinationDumper::DumpLoadCaseDeflections(std::_tostream& os, BSTR lcName, StageIndexType ist, ResultsSummationType summ)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   os<<endl;
   os<<"   Deflections for LoadCase: \""<<W2A(lcName)<<"\", Stage: \""<<W2A(stage)<<"\", SummationType:"<<(summ==rsIncremental?"Incremental":"Cumulative")<<endl<<endl;
   os<<"   Superstructure POIs sorted by location. Deflections are in Global Coordinates"<<endl;
   os<<"   -----------------------------------------------------------------------------"<<endl;
   os<<endl;
   os<<"                  <----------- Left -------------> <----------- Right ------------>"<<endl;
   os<<"  POI   Location     Dx          Dy         Rz        Dx         Dy          Rz"<<endl;
   os<<" ------ ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;

   // compute member responses
   CComPtr<IIDArray> poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, summ, &poi_ids, &poi_locs);

   CComPtr<ILoadCaseResponse> response;
   hr = m_Engine->get_LoadCaseResponse(&response);

   CComPtr<ISectionResult3Ds> defl_results;
   hr=response->ComputeDeflections(lcName, poi_ids, stage, summ, &defl_results);

   CollectionIndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (CollectionIndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      double rgt_rz, rgt_dy, rgt_dx;
      double lft_rz, lft_dy, lft_dx;
      CComPtr<ISectionResult3D> defl_result;
      hr = defl_results->get_Item(ip, &defl_result);
      hr = defl_result->get_XLeft(&lft_dx);
      hr = defl_result->get_YLeft(&lft_dy);
      hr = defl_result->get_ZLeft(&lft_rz);
      hr = defl_result->get_XRight(&rgt_dx);
      hr = defl_result->get_YRight(&rgt_dy);
      hr = defl_result->get_ZRight(&rgt_rz);

      double poi_loc;
      hr = poi_locs->get_Item(ip,&poi_loc);
      os<<right<<setw(7)<<poi_id<<Fl(poi_loc)
        <<Fd(lft_dx)<<Fd(lft_dy)<<Fd(lft_rz)
        <<Fd(rgt_dx)<<Fd(rgt_dy)<<Fd(rgt_rz)<<endl;
   }

   os<<endl;
   os<<"   Support POIs (deflections in global coordinates)"<<endl;
   os<<"   -------------------------------------------------"<<endl;

   os<<endl;
   os<<"        <----------- Left -------------> <----------- Right ------------>"<<endl;
   os<<"  POI        Dx        Dy          Rz        Dx         Dy         Rz"<<endl;
   os<<" ------ ---------- ---------- ---------- ---------- ---------- ----------"<<endl;

   // compute member responses
   CComPtr<IIDArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   CComPtr<ISectionResult3Ds> spt_defl_results;
   hr=response->ComputeDeflections(lcName, spt_poi_ids, stage, summ, &spt_defl_results);

   CollectionIndexType num_spt_pois;
   hr = spt_poi_ids->get_Count(&num_spt_pois);
   for (CollectionIndexType ip=0; ip<num_spt_pois; ip++)
   {
      PoiIDType poi_id;
      hr = spt_poi_ids->get_Item(ip, &poi_id);

      double rgt_rz, rgt_dy, rgt_dx;
      double lft_rz, lft_dy, lft_dx;
      CComPtr<ISectionResult3D> defl_result;
      hr = spt_defl_results->get_Item(ip, &defl_result);
      hr = defl_result->get_XLeft(&lft_dx);
      hr = defl_result->get_YLeft(&lft_dy);
      hr = defl_result->get_ZLeft(&lft_rz);
      hr = defl_result->get_XRight(&rgt_dx);
      hr = defl_result->get_YRight(&rgt_dy);
      hr = defl_result->get_ZRight(&rgt_rz);

      os<<right<<setw(7)<<poi_id
        <<Fd(lft_dx)<<Fd(lft_dy)<<Fd(lft_rz)
        <<Fd(rgt_dx)<<Fd(rgt_dy)<<Fd(rgt_rz)<<endl;
   }

   os<<endl;
   os<<"   Support Deflections (global coordinates)"<<endl
     <<"   ----------------------------------------"<<endl;
   CComPtr<IIDArray> supp_ids;
   m_Util->GetSupportIDs(ist, &supp_ids);

   CComPtr<IResult3Ds> react_results;
   hr=response->ComputeSupportDeflections(lcName, supp_ids, stage, summ, &react_results);

   os<<"   POI      Dx         Dy          Rz"<<std::endl;
   os<<" ------ ---------- ---------- ----------"<<std::endl;

   CollectionIndexType num_supp;
   hr = supp_ids->get_Count(&num_supp);
   for (CollectionIndexType is=0; is<num_supp; is++)
   {
      PoiIDType poi_id;
      hr = supp_ids->get_Item(is,&poi_id);

      double xreac, yreac, zreac;
      CComPtr<IResult3D> react_result;
      hr = react_results->get_Item(is, &react_result);
      hr = react_result->get_X(&xreac);
      hr = react_result->get_Y(&yreac);
      hr = react_result->get_Z(&zreac);

      os<<std::setw(7)<<poi_id<<Fd(xreac)<<Fd(yreac)<<Fd(zreac)<<endl;
   }

   os<<endl;
}

void CLoadCombinationDumper::DumpLoadCaseStresses(std::_tostream& os, BSTR lcName, StageIndexType ist, ResultsSummationType summ)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   os<<endl;
   os<<"   Stresses for LoadCase: \""<<W2A(lcName)<<"\", Stage: \""<<W2A(stage)<<"\", SummationType:"<<(summ==rsIncremental?"Incremental":"Cumulative")<<endl<<endl;
   os<<"   Superstructure POIs sorted by location"<<endl;
   os<<"   --------------------------------------"<<endl;
   os<<endl;
   os<<"                    <------------------ Left -----------------> <----------------- Right ----------------->"<<endl;
   os<<"  POI    Location      sP0          Sp1        Sp2        Sp3       Sp0        Sp1        Sp2        Sp3"<<endl;
   os<<" ------ ----------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;

   // compute member responses
   CComPtr<IIDArray> poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, summ, &poi_ids, &poi_locs);

   CComPtr<ILoadCaseResponse> response;
   hr = m_Engine->get_LoadCaseResponse(&response);

   CComPtr<ISectionStressResults> stress_results;
   hr=response->ComputeStresses(lcName, poi_ids, stage, summ, &stress_results);

   CollectionIndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (CollectionIndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      CComPtr<ISectionStressResult> stress_result;
      hr = stress_results->get_Item(ip, &stress_result);

      std::_tstring rgt_sp0, rgt_sp1, rgt_sp2, rgt_sp3;
      std::_tstring lft_sp0, lft_sp1, lft_sp2, lft_sp3;

      CollectionIndexType cnt;
      double val;
      hr = stress_result->get_LeftCount(&cnt);
      if (cnt>0)
      {
         hr = stress_result->GetLeftResult(0,&val);
         lft_sp0 = Ff(val);
      }

      if (cnt>1)
      {
         hr = stress_result->GetLeftResult(1,&val);
         lft_sp1 = Ff(val);
      }

      if (cnt>2)
      {
         hr = stress_result->GetLeftResult(2,&val);
         lft_sp2 = Ff(val);
      }

      if (cnt>3)
      {
         hr = stress_result->GetLeftResult(3,&val);
         lft_sp3 = Ff(val);
      }

      hr = stress_result->get_RightCount(&cnt);
      if (cnt>0)
      {
         hr = stress_result->GetRightResult(0,&val);
         rgt_sp0 = Ff(val);
      }

      if (cnt>1)
      {
         hr = stress_result->GetRightResult(1,&val);
         rgt_sp1 = Ff(val);
      }

      if (cnt>2)
      {
         hr = stress_result->GetRightResult(2,&val);
         rgt_sp2 = Ff(val);
      }
      if (cnt>3)
      {
         hr = stress_result->GetRightResult(3,&val);
         rgt_sp3 = Ff(val);
      }

      double poi_loc;
      hr = poi_locs->get_Item(ip,&poi_loc);

      os<<right<<setw(7)<<poi_id<<Fl(poi_loc)
        <<setw(11)<<lft_sp0<<setw(11)<<lft_sp1<<setw(11)<<lft_sp2<<setw(11)<<lft_sp3
        <<setw(11)<<rgt_sp0<<setw(11)<<rgt_sp1<<setw(11)<<rgt_sp2<<setw(11)<<rgt_sp3<<endl;
   }

   os<<endl;
   os<<"   Stresses At Support POIs"<<endl;
   os<<"   ------------------------"<<endl;

   os<<endl;
   os<<"        <------------------ Left -----------------> <----------------- Right ----------------->"<<endl;
   os<<"  POI     sP0          Sp1        Sp2        Sp3       Sp0        Sp1        Sp2        Sp3"<<endl;
   os<<" ------ ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;

   // compute member responses
   CComPtr<IIDArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   CComPtr<ISectionStressResults> spt_stress_results;
   hr=response->ComputeStresses(lcName, spt_poi_ids, stage, summ, &spt_stress_results);

   CollectionIndexType num_spt_pois;
   hr = spt_poi_ids->get_Count(&num_spt_pois);
   for (CollectionIndexType ip=0; ip<num_spt_pois; ip++)
   {
      PoiIDType poi_id;
      hr = spt_poi_ids->get_Item(ip, &poi_id);

      CComPtr<ISectionStressResult> stress_result;
      hr = stress_results->get_Item(ip, &stress_result);

      std::_tstring rgt_sp0, rgt_sp1, rgt_sp2, rgt_sp3;
      std::_tstring lft_sp0, lft_sp1, lft_sp2, lft_sp3;

      CollectionIndexType cnt;
      double val;
      hr = stress_result->get_LeftCount(&cnt);
      if (cnt>0)
      {
         hr = stress_result->GetLeftResult(0,&val);
         lft_sp0 = Ff(val);
      }

      if (cnt>1)
      {
         hr = stress_result->GetLeftResult(1,&val);
         lft_sp1 = Ff(val);
      }

      if (cnt>2)
      {
         hr = stress_result->GetLeftResult(2,&val);
         lft_sp2 = Ff(val);
      }

      if (cnt>3)
      {
         hr = stress_result->GetLeftResult(3,&val);
         lft_sp3 = Ff(val);
      }

      hr = stress_result->get_RightCount(&cnt);
      if (cnt>0)
      {
         hr = stress_result->GetRightResult(0,&val);
         rgt_sp0 = Ff(val);
      }

      if (cnt>1)
      {
         hr = stress_result->GetRightResult(1,&val);
         rgt_sp1 = Ff(val);
      }

      if (cnt>2)
      {
         hr = stress_result->GetRightResult(2,&val);
         rgt_sp2 = Ff(val);
      }
      if (cnt>3)
      {
         hr = stress_result->GetRightResult(3,&val);
         rgt_sp3 = Ff(val);
      }

      os<<right<<setw(7)<<poi_id
        <<setw(11)<<lft_sp0<<setw(11)<<lft_sp1<<setw(11)<<lft_sp2<<setw(11)<<lft_sp3
        <<setw(11)<<rgt_sp0<<setw(11)<<rgt_sp1<<setw(11)<<rgt_sp2<<setw(11)<<rgt_sp3<<endl;
   }

   os<<endl;
}


void CLoadCombinationDumper::DumpLoadCombinationResponse(std::_tostream& os, std::_tostream& cos)
{
   CHRException hr;
   USES_CONVERSION;

   os<<" LOAD COMBINATION RESPONSE"<<endl;
   os<<" ========================="<<endl<<endl;


   // use a parameter stack object to avoid a whole bunch of repetitive looking looping code
   CLcParameterStack parameters;
   parameters.Init(m_Engine);

   for (CLcParameterStack::iterator it=parameters.begin(); it!=parameters.end(); it++)
   {
      const LcParams& params = *it;

      DumpLoadCombinationForces(os, cos, params);
   }

   for (CLcParameterStack::iterator it=parameters.begin(); it!=parameters.end(); it++)
   {
      const LcParams& params = *it;

      DumpLoadCombinationDeflections(os, cos, params);
   }

   for (CLcParameterStack::iterator it=parameters.begin(); it!=parameters.end(); it++)
   {
      const LcParams& params = *it;

      DumpLoadCombinationStresses(os, cos, params);
   }

   for (CLcParameterStack::iterator it=parameters.begin(); it!=parameters.end(); it++)
   {
      const LcParams& params = *it;

      DumpLoadCombinationReactions(os, cos, params);
   }

   for (CLcParameterStack::iterator it=parameters.begin(); it!=parameters.end(); it++)
   {
      const LcParams& params = *it;

      DumpLoadCombinationSupportDeflections(os, cos, params);
   }

}

void CLoadCombinationDumper::DumpLoadCombinationForces(std::_tostream& os, std::_tostream& cos, 
                                                       const LcParams& params)
{
   CHRException hr;
   USES_CONVERSION;

   // get all pois
   CComPtr<IIDArray> poi_ids;
   m_Util->GetAllPOIs(params.Stage , rsCumulative, &poi_ids);

   CComBSTR stgn;
   m_Util->StageName(params.Stage, &stgn);

   os<<endl;
   os<<"   Summary Force Responses"<<endl;
   os<<"  "<<params.AsString(true, m_Util)<<endl;
   os<<"    ----------------------------------------------------------------------------------------"<<endl;

   // save first results key so we can write out concurrent results below
   long start_key = m_LastKey;
   CComPtr<ILoadCombinationSectionResults> lcresults;
   hr = m_LCR->ComputeForces(params.LcName, poi_ids, stgn, roMember, params.Summation, 
                             params.ForceEffect, params.Optimization,
					    	        params.DoIncludeLiveLoad, VARIANT_TRUE, VARIANT_TRUE, &lcresults);

   os<<"        <------ Left -----> <----- Right ----->"<<endl;
   os<<"   POI    Result      Key     Result      Key"<<endl;
   os<<" ------ ---------- -------- ---------- --------"<<endl;

   CollectionIndexType res_cnt;
   hr = lcresults->get_Count(&res_cnt);
   for (CollectionIndexType ires=0; ires<res_cnt; ires++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ires, &poi_id);

      double left_res, right_res;
      CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
      hr = lcresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

      long left_key = m_LastKey++;
      long right_key = m_LastKey++;

      os<<right<<setw(7)<<poi_id<<Ff(left_res)<<" K"<<setw(6)<<left_key<<Ff(right_res)<<" K"<<setw(6)<<right_key<<endl;
   }

   os<<endl;

   if (m_Util->DoDetails())
   {

      long curr_key = start_key;

      CComPtr<IIDArray> one_poi;
      hr = one_poi.CoCreateInstance(CLSID_LongArray);
      hr = one_poi->Add(-1);

      for (CollectionIndexType ires=0; ires<res_cnt; ires++)
      {
         PoiIDType poi_id;
         hr = poi_ids->get_Item(ires, &poi_id);

         hr = one_poi->put_Item(0, poi_id);

         long left_key  = curr_key++;
         long right_key = curr_key++;

         double left_res, right_res;
         CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
         hr = lcresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

         cos<<endl;
         cos<<"    Concurrent, Detailed, Force Responses"<<endl;
         cos<<"    For "<<params.AsString(true, m_Util)<<endl;
         cos<<"    At POI "<<poi_id<<" Left Side. Key is K"<<left_key<<endl;
         cos<<"    ----------------------------------------------------------------------------------------"<<endl;

         CComPtr<ISectionResult3Ds> left_res3ds;
         hr = m_CCR->ComputeForces(one_poi, stgn, roMember, left_config, &left_res3ds);

         CComPtr<ISectionResult3D> left_res3d;
         hr = left_res3ds->get_Item(0,&left_res3d);
         double lfx,lfy,lmz,rfx,rfy,rmz;
         hr = left_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

         cos<<"  Optimized <-------- Conc Left -----------> <------- Conc Right ----------->"<<endl;
         cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
         cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
         cos<<Ff(left_res)<<Ff(lfx)<<Ff(lfy)<<Ff(lmz)<<Ff(rfx)<<Ff(rfy)<<Ff(rmz)<<endl<<endl;

         DumpLoadCombinationConfiguration(cos, left_config);

         cos<<endl;
         cos<<"    Concurrent, Detailed, Force Responses"<<endl;
         cos<<"    For "<<params.AsString(true, m_Util)<<endl;
         cos<<"    At POI "<<poi_id<<" Right Side. Key is K"<<right_key<<endl;
         cos<<"    ----------------------------------------------------------------------------------------"<<endl;

         CComPtr<ISectionResult3Ds> right_res3ds;
         hr = m_CCR->ComputeForces(one_poi, stgn, roMember, right_config, &right_res3ds);

         CComPtr<ISectionResult3D> right_res3d;
         hr = right_res3ds->get_Item(0,&right_res3d);
         hr = right_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

         cos<<"  Optimized <-------- Conc Left -----------> <------- Conc Right ----------->"<<endl;
         cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
         cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
         cos<<Ff(right_res)<<Ff(lfx)<<Ff(lfy)<<Ff(lmz)<<Ff(rfx)<<Ff(rfy)<<Ff(rmz)<<endl<<endl;

         DumpLoadCombinationConfiguration(cos, right_config);
      }
   }
}

void CLoadCombinationDumper::DumpLoadCombinationDeflections(std::_tostream& os, std::_tostream& cos, 
                                                       const LcParams& params)
{
   CHRException hr;
   USES_CONVERSION;

   // get all pois
   CComPtr<IIDArray> poi_ids;
   m_Util->GetAllPOIs(params.Stage , rsCumulative, &poi_ids);

   CComBSTR stgn;
   m_Util->StageName(params.Stage, &stgn);

   os<<endl;
   os<<"   Summary Deflection Responses"<<endl;
   os<<"  "<<params.AsString(false, m_Util)<<endl;
   os<<"    ----------------------------------------------------------------------------------------"<<endl;

   // save first results key so we can write out concurrent results below
   long start_key = m_LastKey;
   CComPtr<ILoadCombinationSectionResults> lcresults;
   hr = m_LCR->ComputeDeflections(params.LcName, poi_ids, stgn, params.Summation, 
                             params.ForceEffect, params.Optimization,
					    	        params.DoIncludeLiveLoad, VARIANT_TRUE, VARIANT_TRUE, &lcresults);

   os<<"        <------ Left -----> <----- Right ----->"<<endl;
   os<<"   POI    Result      Key     Result      Key"<<endl;
   os<<" ------ ---------- -------- ---------- --------"<<endl;

   CollectionIndexType res_cnt;
   hr = lcresults->get_Count(&res_cnt);
   for (CollectionIndexType ires=0; ires<res_cnt; ires++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ires, &poi_id);

      double left_res, right_res;
      CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
      hr = lcresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

      long left_key = m_LastKey++;
      long right_key = m_LastKey++;

      os<<right<<setw(7)<<poi_id<<Fd(left_res)<<" K"<<setw(6)<<left_key<<Fd(right_res)<<" K"<<setw(6)<<right_key<<endl;
   }

   os<<endl;

   if (m_Util->DoDetails())
   {

      long curr_key = start_key;

      CComPtr<IIDArray> one_poi;
      hr = one_poi.CoCreateInstance(CLSID_LongArray);
      hr = one_poi->Add(-1);

      for (CollectionIndexType ires=0; ires<res_cnt; ires++)
      {
         PoiIDType poi_id;
         hr = poi_ids->get_Item(ires, &poi_id);

         hr = one_poi->put_Item(0, poi_id);

         long left_key  = curr_key++;
         long right_key = curr_key++;

         double left_res, right_res;
         CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
         hr = lcresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

         cos<<endl;
         cos<<"    Concurrent, Detailed, Deflection Responses"<<endl;
         cos<<"    For "<<params.AsString(false, m_Util)<<endl;
         cos<<"    At POI "<<poi_id<<" Left Side. Key is K"<<left_key<<endl;
         cos<<"    ----------------------------------------------------------------------------------------"<<endl;

         CComPtr<ISectionResult3Ds> left_res3ds;
         hr = m_CCR->ComputeDeflections(one_poi, stgn, left_config, &left_res3ds);

         CComPtr<ISectionResult3D> left_res3d;
         hr = left_res3ds->get_Item(0,&left_res3d);
         double lfx,lfy,lmz,rfx,rfy,rmz;
         hr = left_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

         cos<<"  Optimized <-------- Conc Left -----------> <------- Conc Right ----------->"<<endl;
         cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
         cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
         cos<<Ff(left_res)<<Ff(lfx)<<Ff(lfy)<<Ff(lmz)<<Ff(rfx)<<Ff(rfy)<<Ff(rmz)<<endl<<endl;

         DumpLoadCombinationConfiguration(cos, left_config);

         cos<<endl;
         cos<<"    Concurrent, Detailed, Deflection Responses"<<endl;
         cos<<"    For "<<params.AsString(false, m_Util)<<endl;
         cos<<"    At POI "<<poi_id<<" Right Side. Key is K"<<right_key<<endl;
         cos<<"    ----------------------------------------------------------------------------------------"<<endl;

         CComPtr<ISectionResult3Ds> right_res3ds;
         hr = m_CCR->ComputeDeflections(one_poi, stgn, right_config, &right_res3ds);

         CComPtr<ISectionResult3D> right_res3d;
         hr = right_res3ds->get_Item(0,&right_res3d);
         hr = right_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

         cos<<"  Optimized <-------- Conc Left ------------> <------- Conc Right ----------->"<<endl;
         cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
         cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
         cos<<Ff(right_res)<<Ff(lfx)<<Ff(lfy)<<Ff(lmz)<<Ff(rfx)<<Ff(rfy)<<Ff(rmz)<<endl<<endl;

         DumpLoadCombinationConfiguration(cos, right_config);
      }
   }
}


void CLoadCombinationDumper::DumpLoadCombinationStresses(std::_tostream& os, std::_tostream& cos, 
                                                       const LcParams& params)
{
   CHRException hr;
   USES_CONVERSION;

   // get all pois
   CComPtr<IIDArray> poi_ids;
   m_Util->GetAllPOIs(params.Stage , rsCumulative, &poi_ids);

   CComBSTR stgn;
   m_Util->StageName(params.Stage, &stgn);

   os<<endl;
   os<<"   Summary Stress Responses"<<endl;
   os<<"  "<<params.AsString(true, m_Util)<<endl;
   os<<"    ----------------------------------------------------------------------------------------"<<endl;

   // save first results key so we can write out concurrent results below
   long start_key = m_LastKey;
   CComPtr<ILoadCombinationStressResults> lcresults;
   hr = m_LCR->ComputeStresses(params.LcName, poi_ids, stgn, params.Summation, 
                             params.ForceEffect, params.Optimization,
					    	        params.DoIncludeLiveLoad, VARIANT_TRUE, VARIANT_TRUE, &lcresults);

   os<<"        <----------------- Left ---------------------------> <-------------------------- Right -------------------->"<<endl;
   os<<"   POI     SP0        SP1         SP2        SP3      Key       SP0        SP1        SP2        SP3       Key"<<endl;
   os<<" ------ ---------- ---------- ---------- ---------- -------- ---------- ---------- ---------- ---------- --------"<<endl;

   CollectionIndexType res_cnt;
   hr = lcresults->get_Count(&res_cnt);
   for (CollectionIndexType ires=0; ires<res_cnt; ires++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ires, &poi_id);

      CComPtr<IStressResult> left_res, right_res;
      CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
      hr = lcresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

      std::_tstring rgt_sp0, rgt_sp1, rgt_sp2, rgt_sp3;
      std::_tstring lft_sp0, lft_sp1, lft_sp2, lft_sp3;

      CollectionIndexType cnt;
      double val;
      hr = left_res->get_Count(&cnt);
      if (cnt>0)
      {
         hr = left_res->GetResult(0,&val);
         lft_sp0 = Ff(val);
      }

      if (cnt>1)
      {
         hr = left_res->GetResult(1,&val);
         lft_sp1 = Ff(val);
      }

      if (cnt>2)
      {
         hr = left_res->GetResult(2,&val);
         lft_sp2 = Ff(val);
      }

      if (cnt>3)
      {
         hr = left_res->GetResult(3,&val);
         lft_sp3 = Ff(val);
      }

      hr = right_res->get_Count(&cnt);
      if (cnt>0)
      {
         hr = right_res->GetResult(0,&val);
         rgt_sp0 = Ff(val);
      }

      if (cnt>1)
      {
         hr = right_res->GetResult(1,&val);
         rgt_sp1 = Ff(val);
      }

      if (cnt>2)
      {
         hr = right_res->GetResult(2,&val);
         rgt_sp2 = Ff(val);
      }
      if (cnt>3)
      {
         hr = right_res->GetResult(3,&val);
         rgt_sp3 = Ff(val);
      }

      long left_key = m_LastKey++;
      long right_key = m_LastKey++;

      os<<right<<setw(7)<<poi_id
        <<setw(11)<<lft_sp0<<setw(11)<<lft_sp1<<setw(11)<<lft_sp2<<setw(11)<<lft_sp3<<setw(9)<<left_key
        <<setw(11)<<rgt_sp0<<setw(11)<<rgt_sp1<<setw(11)<<rgt_sp2<<setw(11)<<rgt_sp3<<setw(9)<<right_key<<endl;
   }

   os<<" "<<endl;

   os<<endl;

   if (m_Util->DoDetails())
   {

      long curr_key = start_key;

      CComPtr<IIDArray> one_poi;
      hr = one_poi.CoCreateInstance(CLSID_LongArray);
      hr = one_poi->Add(-1);

      for (CollectionIndexType ires=0; ires<res_cnt; ires++)
      {
         PoiIDType poi_id;
         hr = poi_ids->get_Item(ires, &poi_id);

         hr = one_poi->put_Item(0, poi_id);

         long left_key  = curr_key++;
         long right_key = curr_key++;

         CComPtr<IStressResult> left_res, right_res;
         CComPtr<ILoadCombinationResultConfiguration> left_config, right_config;
         hr = lcresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

         cos<<endl;
         cos<<"    Concurrent, Detailed, Stress Responses"<<endl;
         cos<<"    For "<<params.AsString(true, m_Util)<<endl;
         cos<<"    At POI "<<poi_id<<" Left Side. Key is K"<<left_key<<endl;
         cos<<"    ----------------------------------------------------------------------------------------"<<endl;

         DumpLoadCombinationConfiguration(cos, left_config);

         cos<<endl;
         cos<<"    Concurrent, Detailed, Stress Responses"<<endl;
         cos<<"    For "<<params.AsString(true, m_Util)<<endl;
         cos<<"    At POI "<<poi_id<<" Right Side. Key is K"<<right_key<<endl;
         cos<<"    ----------------------------------------------------------------------------------------"<<endl;

         DumpLoadCombinationConfiguration(cos, right_config);
      }
   }
}



void CLoadCombinationDumper::DumpLoadCombinationReactions(std::_tostream& os, std::_tostream& cos, 
                                                       const LcParams& params)
{
   CHRException hr;
   USES_CONVERSION;

   // get all pois
   CComPtr<IIDArray> spt_ids;
   m_Util->GetSupportIDs(params.Stage, &spt_ids);

   CComBSTR stgn;
   m_Util->StageName(params.Stage, &stgn);

   os<<endl;
   os<<"   Summary Reaction Responses"<<endl;
   os<<"  "<<params.AsString(true, m_Util)<<endl;
   os<<"    ----------------------------------------------------------------------------------------"<<endl;

   // save first results key so we can write out concurrent results below
   long start_key = m_LastKey;
   CComPtr<ILoadCombinationResults> lcresults;
   hr = m_LCR->ComputeReactions(params.LcName, spt_ids, stgn, params.Summation, 
                             params.ForceEffect, params.Optimization,
					    	        params.DoIncludeLiveLoad, VARIANT_TRUE, VARIANT_TRUE, &lcresults);

   os<<"   SPT    Result      Key  "<<endl;
   os<<" ------ ---------- --------"<<endl;

   CollectionIndexType res_cnt;
   hr = lcresults->get_Count(&res_cnt);
   for (CollectionIndexType ires=0; ires<res_cnt; ires++)
   {
      IDType spt_id;
      hr = spt_ids->get_Item(ires, &spt_id);

      double res;
      CComPtr<ILoadCombinationResultConfiguration> config;
      hr = lcresults->GetResult(ires, &res, &config);

      long key = m_LastKey++;

      os<<right<<setw(7)<<spt_id<<Ff(res)<<" K"<<setw(6)<<key<<endl;
   }

   os<<endl;

   if (m_Util->DoDetails())
   {

      long curr_key = start_key;

      CComPtr<IIDArray> one_poi;
      hr = one_poi.CoCreateInstance(CLSID_LongArray);
      hr = one_poi->Add(-1);

      for (CollectionIndexType ires=0; ires<res_cnt; ires++)
      {
         IDType spt_id;
         hr = spt_ids->get_Item(ires, &spt_id);

         hr = one_poi->put_Item(0, spt_id);

         long key  = curr_key++;

         double res;
         CComPtr<ILoadCombinationResultConfiguration> config;
         hr = lcresults->GetResult(ires, &res, &config);

         cos<<endl;
         cos<<"    Concurrent, Detailed, Reaction Responses"<<endl;
         cos<<"    For "<<params.AsString(true, m_Util)<<endl;
         cos<<"    At Support "<<spt_id<<" Key is K"<<key<<endl;
         cos<<"    ----------------------------------------------------------------------------------------"<<endl;

         CComPtr<IResult3Ds> res3ds;
         hr = m_CCR->ComputeReactions(one_poi, stgn, config, &res3ds);

         CComPtr<IResult3D> res3d;
         hr = res3ds->get_Item(0,&res3d);
         double fx,fy,mz;
         hr = res3d->GetResult(&fx,&fy,&mz);

         cos<<"  Optimized <-----Concurrent Values ------->"<<endl;
         cos<<"   Value        Fx         Fy         Mz    "<<endl;
         cos<<" ---------- ---------- ---------- ----------"<<endl;
         cos<<Ff(res)<<Ff(fx)<<Ff(fy)<<Ff(mz)<<endl<<endl;

         DumpLoadCombinationConfiguration(cos, config);
      }
   }
}



void CLoadCombinationDumper::DumpLoadCombinationSupportDeflections(std::_tostream& os, std::_tostream& cos, 
                                                       const LcParams& params)
{
   CHRException hr;
   USES_CONVERSION;

   // get all pois
   CComPtr<IIDArray> spt_ids;
   m_Util->GetSupportIDs(params.Stage, &spt_ids);

   CComBSTR stgn;
   m_Util->StageName(params.Stage, &stgn);

   os<<endl;
   os<<"   Summary SupportDeflection Responses"<<endl;
   os<<"  "<<params.AsString(false, m_Util)<<endl;
   os<<"    ----------------------------------------------------------------------------------------"<<endl;

   // save first results key so we can write out concurrent results below
   long start_key = m_LastKey;
   CComPtr<ILoadCombinationResults> lcresults;
   hr = m_LCR->ComputeSupportDeflections(params.LcName, spt_ids, stgn, params.Summation, 
                             params.ForceEffect, params.Optimization,
					    	        params.DoIncludeLiveLoad, VARIANT_TRUE, VARIANT_TRUE, &lcresults);

   os<<"   SPT    Result      Key  "<<endl;
   os<<" ------ ---------- --------"<<endl;

   CollectionIndexType res_cnt;
   hr = lcresults->get_Count(&res_cnt);
   for (CollectionIndexType ires=0; ires<res_cnt; ires++)
   {
      IDType spt_id;
      hr = spt_ids->get_Item(ires, &spt_id);

      double res;
      CComPtr<ILoadCombinationResultConfiguration> config;
      hr = lcresults->GetResult(ires, &res, &config);

      long key = m_LastKey++;

      os<<right<<setw(7)<<spt_id<<Fd(res)<<" K"<<setw(6)<<key<<endl;
   }

   os<<endl;

   if (m_Util->DoDetails())
   {

      long curr_key = start_key;

      CComPtr<IIDArray> one_poi;
      hr = one_poi.CoCreateInstance(CLSID_LongArray);
      hr = one_poi->Add(-1);

      for (CollectionIndexType ires=0; ires<res_cnt; ires++)
      {
         IDType spt_id;
         hr = spt_ids->get_Item(ires, &spt_id);

         hr = one_poi->put_Item(0, spt_id);

         long key  = curr_key++;

         double res;
         CComPtr<ILoadCombinationResultConfiguration> config;
         hr = lcresults->GetResult(ires, &res, &config);

         cos<<"    Concurrent, Detailed, Support Deflection Responses"<<endl;
         cos<<"    For "<<params.AsString(false, m_Util)<<endl;
         cos<<"    At Support "<<spt_id<<" Key is K"<<key<<endl;
         cos<<"    ----------------------------------------------------------------------------------------"<<endl;

         CComPtr<IResult3Ds> res3ds;
         hr = m_CCR->ComputeSupportDeflections(one_poi, stgn, config, &res3ds);

         CComPtr<IResult3D> res3d;
         hr = res3ds->get_Item(0,&res3d);
         double fx,fy,mz;
         hr = res3d->GetResult(&fx,&fy,&mz);

         cos<<"  Optimized <-----Concurrent Values ------->"<<endl;
         cos<<"   Value        Fx         Fy         Mz    "<<endl;
         cos<<" ---------- ---------- ---------- ----------"<<endl;
         cos<<Fd(res)<<Fd(fx)<<Fd(fy)<<Fd(mz)<<endl<<endl;

         DumpLoadCombinationConfiguration(cos, config);
      }
   }
}


void CLoadCombinationDumper::DumpLoadCombinationConfiguration(std::_tostream& os, ILoadCombinationResultConfiguration* config)
{
   CHRException hr;
   USES_CONVERSION;

   os<<_T(" Dump of Load Combination Configuration")<<endl;

   ResultsSummationType rs;
   hr = config->get_SummationType(&rs);
   std::_tstring str_rs((rs==rsIncremental ? _T("Incremental"):_T("Cumulative")));

   double llf;
   hr = config->get_LiveLoadFactor(&llf);

   CollectionIndexType lcf_cnt;
   hr = config->get_LoadCaseFactorCount(&lcf_cnt);

   os<<_T("                  Live Load  <-----------Load Case Factors ------------>")<<endl;
   os<<_T("  Summation Type   Factor          Load Case                   Factor")<<endl;
   os<<_T("  --------------- ---------- ------------------------------- ----------")<<endl;
   if (lcf_cnt==0)
   {
      os<<left<<setw(15)<<str_rs<<Ff(llf)<<endl;
   }
   else
   {
      for (CollectionIndexType icf=0; icf<lcf_cnt; icf++)
      {
         double fac;
         CComBSTR lcn;
         hr = config->GetLoadCaseFactor(icf,&lcn,&fac);

         if (icf==0)
         {
            os<<_T("  ")<<left<<setw(15)<<str_rs<<right<<Ff(llf)<<_T(" ")<<setw(31)<<left<<W2A(lcn)<<right<<Ff(fac)<<endl;
         }
         else
         {
            os<<_T("  ")<<left<<setw(27)<<_T(" ")<<setw(31)<<W2A(lcn)<<right<<Ff(fac)<<endl;
         }
      }
   }

   os<<endl;

   // Next, live load configuration. 
   // This is a pinta since we need to dive deep to get the number of axles in the controlling truck
   CollectionIndexType nLiveLoadConfigurations;
   config->GetLiveLoadConfigurationCount(&nLiveLoadConfigurations);

   for ( CollectionIndexType llc = 0; llc < nLiveLoadConfigurations; llc++ )
   {
      CComPtr<ILiveLoadConfiguration> lvlc;
      hr = config->GetLiveLoadConfiguration(llc,&lvlc);

      if (lvlc==NULL)
      {
         os<<endl<<_T("  No Live Load Was Applied for this Combination")<<endl;
      }
      else
      {
         LiveLoadModelType type;
         hr = lvlc->get_LiveLoadModel(&type);

         if (type==lltNone)
         {
            os<<endl<<_T("  No Live Load Was Applied for this Combination")<<endl;
         }
         else
         {
            CComPtr<ILBAMModel> model;
            hr = m_Engine->get_Model(&model);

            CComPtr<ILiveLoad> liveload;
            hr = model->get_LiveLoad(&liveload);

            CComPtr<ILiveLoadModel> llm;
            GetLiveLoadModel( type, liveload, &llm);

            CComPtr<IVehicularLoads> vhls;
            hr = llm->get_VehicularLoads(&vhls);

            AxleIndexType axle_cnt = GetAxleCnt(vhls, lvlc);

            DumpLiveLoadConfiguration(os, lvlc, axle_cnt, m_Util);
         }
      }

      os<<endl;
   }
}



