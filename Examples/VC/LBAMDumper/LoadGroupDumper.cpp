// LoadGroupDumper.cpp: implementation of the CLoadGroupDumper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoadGroupDumper.h"

#include "DumperUtils.h"
#include "WBFLTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace std;

CLoadGroupDumper::CLoadGroupDumper(ILBAMAnalysisEngine* engine, CDumperUtil* util):
m_Engine(engine),
m_Util(util)
{

}

CLoadGroupDumper::~CLoadGroupDumper()
{

}

void CLoadGroupDumper::DumpAnalysisPOIs(std::ostream& os)
{
   DumpAPOIs(os);
   DumpPOIDistributionFactors(os);
   DumpPOIStressPoints(os);
}

void CLoadGroupDumper::DumpAPOIs(std::ostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   CComPtr<IAnalysisPOIs> apois;
   hr = m_Engine->get_AnalysisPOIs(&apois);

   os<<endl;
   os<<" Superstructure Anaysis POIs for all Stages (negative POI ID's denotes internally generated)"<<endl;
   os<<" -------------------------------------------------------------------------------------------"<<endl;

   long spoi_inc,cpoi_inc;
   hr = apois->get_SpanPoiIncrement(&spoi_inc);
   os<<"    Span POI increment is "<<spoi_inc<<endl;
   hr = apois->get_CantileverPoiIncrement(&cpoi_inc);
   os<<"    Cantilever POI increment is "<<cpoi_inc<<endl<<endl;

   long stg_cnt = m_Util->StageCount();

   for (long is=0; is<stg_cnt; is++)
   {
      CComBSTR stgnm;
      m_Util->StageName(is, &stgnm);

      os<<"    Analysis POIs for stage: "<<W2A(stgnm)<<endl<<endl;

      CComPtr<IDblArray> poi_locs;
      CComPtr<ILongArray> poi_ids;
      m_Util->GetSuperstructurePOIs(is, rsIncremental, &poi_ids,&poi_locs); // use incremental since we want all pois

      CollectionIndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<"           Member              Member     Member     Global X "<<endl;
      os<<" POI ID     Type                ID       Location    Location "<<endl;
      os<<" ------ -------------------- ---------- ----------- -----------"<<endl;

      for (CollectionIndexType ip=0; ip<poi_cnt; ip++)
      {
         PoiIDType id;
         hr = poi_ids->get_Item(ip, &id);
         double gx;
         hr = poi_locs->get_Item(ip, &gx);

         MemberType membertype;
         long memberid;
         double memberloc;
         hr = apois->GetPoiInfo(stgnm, id, &membertype, &memberid, &memberloc);

         std::string tmp = Fl(memberloc);

         os<<right<<setw(7)<<id<<" "<<left<<setw(21)<<MTToString(membertype)
           <<right<<setw(10)<<memberid<<Fl(memberloc)<<Fl(gx)<<endl;
      }

      os<<endl;
   }

   // next support pois - report stage 0 only - only can remove temporary supports
   if (stg_cnt>0)
   {
      CComBSTR stgnm;
      m_Util->StageName(0, &stgnm);

      os<<endl;
      os<<" Support POIs"<<endl;
      os<<" ------------"<<endl;

      CComPtr<ILongArray> poi_ids;
      m_Util->GetSupportPOIs(0, &poi_ids);

      CollectionIndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<"           Member              Member     Member  "<<endl;
      os<<" POI ID     Type                ID       Location "<<endl;
      os<<" ------ -------------------- ---------- -----------"<<endl;

      for (CollectionIndexType ip=0; ip<poi_cnt; ip++)
      {
         PoiIDType id;
         hr = poi_ids->get_Item(ip, &id);

         MemberType membertype;
         MemberIDType memberid;
         double memberloc;
         hr = apois->GetPoiInfo(stgnm, id, &membertype, &memberid, &memberloc);

         os<<right<<setw(7)<<id<<" "<<left<<setw(21)<<MTToString(membertype)
           <<right<<setw(10)<<memberid<<Fl(memberloc)<<endl;
      }
   }

   os<<endl;
}


void CLoadGroupDumper::DumpPOIDistributionFactors(std::ostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   CComPtr<IAnalysisPOIs> apois;
   hr = m_Engine->get_AnalysisPOIs(&apois);

   // undocumented qi
   CComQIPtr<IGetDistributionFactors> getdfs(apois);
   ATLASSERT(getdfs);

   os<<endl;
   os<<" Distribution Factors At POIs for all Stages"<<endl;
   os<<" -------------------------------------------"<<endl<<endl;;

   long stg_cnt = m_Util->StageCount();
   for (long is=0; is<stg_cnt; is++)
   {
      CComBSTR stage;
      m_Util->StageName(is, &stage);

      os<<"    Distribution Factors At Superstructure POIs for stage: "<<W2A(stage)<<endl<<endl;

      CComPtr<IDblArray> poi_locs;
      CComPtr<ILongArray> poi_ids;
      m_Util->GetSuperstructurePOIs(is, rsIncremental, &poi_ids,&poi_locs); // use incremental since we want all pois

      CollectionIndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<"         Global X "<<endl;
      os<<" POI ID  Location    gPMSgl   gPMMul   gNMSgl   gNMMul   gVSgl    gVMul    gDSgl    gDMul    gRSgl    gRMul    gTSgl    gTMul     gFat"<<endl;
      os<<" ------ ----------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- --------"<<endl;

      for (CollectionIndexType ip=0; ip<poi_cnt; ip++)
      {
         PoiIDType id;
         hr = poi_ids->get_Item(ip, &id);
         double gx;
         hr = poi_locs->get_Item(ip, &gx);

         CComPtr<IDistributionFactor> left_df, right_df;
         hr = getdfs->GetPOIDistributionFactor(id, stage, &left_df, &right_df);

         double gPMSgl, gPMMul, gNMSgl, gNMMul, gVSgl, gVMul, gDSgl, gDMul, gRSgl, gRMul, gTSgl, gTMul, gFat;
         hr = left_df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFat);

         os<<right<<setw(7)<<id<<Fl(gx)
           <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
           <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul<<setw(9)<<gFat<<endl;

         if(right_df)
         {
            hr = right_df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFat);

            os<<right<<setw(19)<<" "
              <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
              <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul<<setw(9)<<gFat<<endl;
         }
      }

      os<<endl;
   }

   // next support pois - report stage 0 only - only can remove temporary supports
   if (stg_cnt>0)
   {
      CComBSTR stage;
      m_Util->StageName(0, &stage);

      os<<endl;
      os<<" Support POI Distribution Factors"<<endl;
      os<<" --------------------------------"<<endl;

      CComPtr<ILongArray> poi_ids;
      m_Util->GetSupportPOIs(0, &poi_ids);

      CollectionIndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<"       "<<endl;
      os<<" POI ID  gPMSgl   gPMMul   gNMSgl   gNMMul   gVSgl    gVMul    gDSgl    gDMul    gRSgl    gRMul    gTSgl    gTMul     gFat"<<endl;
      os<<" ------ -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- --------"<<endl;

      for (CollectionIndexType ip=0; ip<poi_cnt; ip++)
      {
         PoiIDType id;
         hr = poi_ids->get_Item(ip, &id);

         CComPtr<IDistributionFactor> left_df, right_df;
         hr = getdfs->GetPOIDistributionFactor(id, stage, &left_df, &right_df);

         double gPMSgl, gPMMul, gNMSgl, gNMMul, gVSgl, gVMul, gDSgl, gDMul, gRSgl, gRMul, gTSgl, gTMul, gFat;
         hr = left_df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFat);

         os<<right<<setw(7)<<id
           <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
           <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul<<setw(9)<<gFat<<endl;

         if(right_df)
         {
            hr = right_df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFat);

            os<<right<<setw(19)<<" "
              <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
              <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul<<setw(9)<<gFat<<endl;
         }
      }
   }

   // next support dfs - report stage 0 only - only can remove temporary supports
   if (stg_cnt>0)
   {
      CComBSTR stage;
      m_Util->StageName(0, &stage);

      os<<endl;
      os<<" Support Distribution Factors - First Stage Only"<<endl;
      os<<" -----------------------------------------------"<<endl;

      CComPtr<ILongArray> spt_ids;
      m_Util->GetSupportIDs(0, &spt_ids);

      CollectionIndexType spt_cnt; 
      hr = spt_ids->get_Count(&spt_cnt);

      os<<"       "<<endl;
      os<<" Suppt   gPMSgl   gPMMul   gNMSgl   gNMMul   gVSgl    gVMul    gDSgl    gDMul    gRSgl    gRMul    gTSgl    gTMul     gFat"<<endl;
      os<<" ------ -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- --------"<<endl;

      for (CollectionIndexType ip=0; ip<spt_cnt; ip++)
      {
         PoiIDType id;
         hr = spt_ids->get_Item(ip, &id);

         CComPtr<IDistributionFactor> s_df;
         hr = getdfs->GetSupportDistributionFactor(id, stage, &s_df);

         double gPMSgl, gPMMul, gNMSgl, gNMMul, gVSgl, gVMul, gDSgl, gDMul, gRSgl, gRMul, gTSgl, gTMul, gFat;
         hr = s_df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFat);

         os<<right<<setw(7)<<id
           <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
           <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul<<setw(9)<<gFat<<endl;
      }
   }

   os<<endl;
}

void CLoadGroupDumper::DumpPOIStressPoints(std::ostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   CComPtr<IAnalysisPOIs> apois;
   hr = m_Engine->get_AnalysisPOIs(&apois);

   // undocumented qi
   CComQIPtr<IGetStressPoints> getsps(apois);
   ATLASSERT(getsps);

   os<<endl;
   os<<" Stress Points At POIs for all Stages"<<endl;
   os<<" -------------------------------------------"<<endl<<endl;;

   long stg_cnt = m_Util->StageCount();
   for (long is=0; is<stg_cnt; is++)
   {
      CComBSTR stage;
      m_Util->StageName(is, &stage);

      os<<"    Stress Points At Superstructure POIs for stage: "<<W2A(stage)<<endl<<endl;

      CComPtr<IDblArray> poi_locs;
      CComPtr<ILongArray> poi_ids;
      m_Util->GetSuperstructurePOIs(is, rsIncremental, &poi_ids,&poi_locs); // use incremental since we want all pois

      CollectionIndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<"         Global X         <-------- Left -----> <------ Right ------>"<<endl;
      os<<" POI ID  Location    SP #      Sa           Sm         Sa          Sm    "<<endl;
      os<<" ------ ----------- ------ ----------- ----------- ----------- -----------"<<endl;

      for (CollectionIndexType ip=0; ip<poi_cnt; ip++)
      {
         PoiIDType id;
         hr = poi_ids->get_Item(ip, &id);
         double gx;
         hr = poi_locs->get_Item(ip, &gx);

         CComPtr<IStressPoints> left_sps, right_sps;
         hr = getsps->GetStressPointsAtPOI(id, stage, &left_sps, &right_sps);

         CollectionIndexType left_cnt=0, right_cnt=0;
         hr = left_sps->get_Count(&left_cnt);
         if (right_sps)
            hr = right_sps->get_Count(&right_cnt);

         CollectionIndexType max_cnt = max(left_cnt, right_cnt);

         for (CollectionIndexType isp=0; isp<max_cnt; isp++)
         {
            string str_lft_sa, str_rgt_sa;
            string str_lft_sm, str_rgt_sm;
            if (isp<left_cnt)
            {
               CComPtr<IStressPoint> sp;
               hr = left_sps->get_Item(isp, &sp);

               double sa, sm;
               hr = sp->get_Sa(&sa);
               hr = sp->get_Sm(&sm);

               str_lft_sa = Fl(sa);
               str_lft_sm = Fl(sm);
            }

            if (isp<right_cnt)
            {
               CComPtr<IStressPoint> sp;
               hr = right_sps->get_Item(isp, &sp);

               double sa, sm;
               hr = sp->get_Sa(&sa);
               hr = sp->get_Sm(&sm);

               str_rgt_sa = Fl(sa);
               str_rgt_sm = Fl(sm);
            }

            if (isp==0)
            {
               os<<right<<setw(7)<<id<<Fl(gx)<<setw(7)<<isp<<setw(11)<<str_lft_sa<<setw(11)<<str_lft_sm
                 <<setw(11)<<str_rgt_sa<<setw(11)<<str_rgt_sm<<endl;
            }
            else
            {
               os<<right<<setw(19)<<" "<<setw(7)<<isp<<setw(11)<<str_lft_sa<<setw(11)<<str_lft_sm
                 <<setw(11)<<str_rgt_sa<<setw(11)<<str_rgt_sm<<endl;
            }
         }
      }

      os<<endl;
   }

   // next support pois
   for (long is=0; is<stg_cnt; is++)
   {
      CComBSTR stage;
      m_Util->StageName(is, &stage);

      os<<endl;
      os<<" Support POI Stress Points - Stage \""<<W2A(stage)<<"\""<<endl;
      os<<" ------------------------------------------------------------"<<endl;

      CComPtr<ILongArray> poi_ids;
      m_Util->GetSupportPOIs(is, &poi_ids);

      CollectionIndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<"               <-------- Left -----> <------ Right ------>"<<endl;
      os<<" POI ID  SP #      Sa          Sm          Sa          Sm    "<<endl;
      os<<" ------ ------ ----------- ----------- ----------- -----------"<<endl;

      for (CollectionIndexType ip=0; ip<poi_cnt; ip++)
      {
         PoiIDType id;
         hr = poi_ids->get_Item(ip, &id);

         CComPtr<IStressPoints> left_sps, right_sps;
         hr = getsps->GetStressPointsAtPOI(id, stage, &left_sps, &right_sps);

         CollectionIndexType left_cnt=0, right_cnt=0;
         hr = left_sps->get_Count(&left_cnt);
         if (right_sps)
            hr = right_sps->get_Count(&right_cnt);

         CollectionIndexType max_cnt = max(left_cnt, right_cnt);

         for (CollectionIndexType isp=0; isp<max_cnt; isp++)
         {
            string str_lft_sa, str_rgt_sa;
            string str_lft_sm, str_rgt_sm;
            if (isp<left_cnt)
            {
               CComPtr<IStressPoint> sp;
               hr = left_sps->get_Item(isp, &sp);

               double sa, sm;
               hr = sp->get_Sa(&sa);
               hr = sp->get_Sm(&sm);

               str_lft_sa = Fl(sa);
               str_lft_sm = Fl(sm);
            }

            if (isp<right_cnt)
            {
               CComPtr<IStressPoint> sp;
               hr = right_sps->get_Item(isp, &sp);

               double sa, sm;
               hr = sp->get_Sa(&sa);
               hr = sp->get_Sm(&sm);

               str_rgt_sa = Fl(sa);
               str_rgt_sm = Fl(sm);
            }

            if (isp==0)
            {
               os<<right<<setw(7)<<id<<" "<<setw(6)<<isp<<setw(11)<<str_lft_sa<<setw(11)<<str_lft_sm
                 <<setw(11)<<str_rgt_sa<<setw(11)<<str_rgt_sm<<endl;
            }
            else
            {
               os<<right<<setw(8)<<" "<<setw(6)<<isp<<setw(11)<<str_lft_sa<<setw(11)<<str_lft_sm
                 <<setw(11)<<str_rgt_sa<<setw(11)<<str_rgt_sm<<endl;
            }
         }
      }
   }
}

void CLoadGroupDumper::DumpLoadGroupResponse(std::ostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   os<<endl<<endl;
   os<<" DUMP OF LOADGROUP RESPONSES"<<endl;
   os<<" ==========================="<<endl<<endl;

   // first need to report the load groups where there were no responses
   CComPtr<ILBAMModel> model;
   hr = m_Engine->get_Model(&model);

   CComPtr<ILoadGroups> loadgroups;
   hr = model->get_LoadGroups(&loadgroups);

   CComPtr<ILoadGroupResponse> lg_response;
   hr = m_Engine->get_LoadGroupResponse(&lg_response);
   
   CComQIPtr<IGetActiveLoadGroups> galg(lg_response);
   ATLASSERT(galg);

   CComPtr<IBstrArray> active_lgs;
   hr = galg->GetActiveLoadGroups(&active_lgs);

   // loop over all loadgroups and find the dead ones
   CComPtr<IBstrArray> dead_lgs;
   hr = dead_lgs.CoCreateInstance(CLSID_BstrArray);

   CollectionIndexType lg_cnt;
   hr = loadgroups->get_Count(&lg_cnt);
   for (CollectionIndexType ilg=0; ilg<lg_cnt; ilg++)
   {
      CComPtr<ILoadGroup> loadgroup;
      hr = loadgroups->get_Item(ilg, &loadgroup);

      CComBSTR lg_name;
      hr = loadgroup->get_Name(&lg_name);

      CollectionIndexType idx;
      hr = active_lgs->Find(lg_name, &idx);
      if (idx == -1)
      {
         // not found in active list
         hr = dead_lgs->Add(lg_name);
      }
   }

   CollectionIndexType dead_cnt;
   hr = dead_lgs->get_Count(&dead_cnt);
   if (dead_cnt>0)
   {
      os<<"  There are "<<dead_cnt<<" LoadGroups in this model with no loads (zero results). They are: "<<endl;
      for (CollectionIndexType ilg=0; ilg<dead_cnt; ilg++)
      {
         CComBSTR name;
         hr = dead_lgs->get_Item(ilg, &name);
         os<<"    "<<W2A(name)<<endl;
      }

      os<<"  No Results will be be reported for these LoadGroups"<<endl<<endl;
   }

   // loop over all of our active loadgroups and stages and report responses
   long stg_cnt = m_Util->StageCount();

   CollectionIndexType alg_cnt;
   hr = active_lgs->get_Count(&alg_cnt);
   for (CollectionIndexType ilg=0; ilg<alg_cnt; ilg++)
   {
      CComBSTR lg_name;
      hr = active_lgs->get_Item(ilg, &lg_name);

      // forces
      for (long ist=0; ist<stg_cnt; ist++)
      {
         DumpLoadGroupForces(os, lg_name, ist, rsIncremental);
         DumpLoadGroupForces(os, lg_name, ist, rsCumulative);
      }

      // deflections
      for (long ist=0; ist<stg_cnt; ist++)
      {
         DumpLoadGroupDeflections(os, lg_name, ist, rsIncremental);
         DumpLoadGroupDeflections(os, lg_name, ist, rsCumulative);
      }

      // stresses
      for (long ist=0; ist<stg_cnt; ist++)
      {
         DumpLoadGroupStresses(os, lg_name, ist, rsIncremental);
         DumpLoadGroupStresses(os, lg_name, ist, rsCumulative);
      }
   }
}

void CLoadGroupDumper::DumpInfluenceLines(std::ostream& os)
{
   long stg_cnt = m_Util->StageCount();

   os<<" INFLUENCE LINE RESPONSE"<<endl;
   os<<" -----------------------"<<endl;

   for (long ist=0; ist<stg_cnt; ist++)
   {
      DumpForceInfluenceLines(os, ist, fetFx);
      DumpForceInfluenceLines(os, ist, fetFy);
      DumpForceInfluenceLines(os, ist, fetMz);
   }

   for (long ist=0; ist<stg_cnt; ist++)
   {
      DumpDeflectionInfluenceLines(os, ist, fetFx);
      DumpDeflectionInfluenceLines(os, ist, fetFy);
      DumpDeflectionInfluenceLines(os, ist, fetMz);
   }
}



void CLoadGroupDumper::DumpLoadGroupForces(std::ostream& os, BSTR lgName, long ist, ResultsSummationType summ)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   os<<endl;
   os<<"   Forces for LoadGroup: \""<<W2A(lgName)<<"\", Stage: \""<<W2A(stage)<<"\", SummationType:"<<(summ==rsIncremental?"Incremental":"Cumulative")<<endl<<endl;
   os<<"   Superstructure POIs sorted by location"<<endl;
   os<<"   --------------------------------------"<<endl;
   os<<endl;
   os<<"                  <----------- Left -------------> <----------- Right ------------>"<<endl;
   os<<"  POI   Location     Axial      Shear      Moment    Axial      Shear      Moment"<<endl;
   os<<" ------ --------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;

   // compute member responses
   CComPtr<ILongArray> poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, summ, &poi_ids, &poi_locs);

   CComPtr<ILoadGroupResponse> response;
   hr = m_Engine->get_LoadGroupResponse(&response);

   CComPtr<ISectionResult3Ds> force_results;
   hr=response->ComputeForces(lgName, poi_ids, stage, roMember, summ, &force_results);

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
      os<<right<<setw(7)<<poi_id<<setw(10)<<poi_loc
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
   CComPtr<ILongArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   CComPtr<ISectionResult3Ds> spt_force_results;
   hr=response->ComputeForces(lgName, spt_poi_ids, stage, roMember, summ, &spt_force_results);

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
   CComPtr<ILongArray> supp_ids;
   m_Util->GetSupportIDs(ist, &supp_ids);

   CComPtr<IResult3Ds> react_results;
   hr=response->ComputeReactions(lgName, supp_ids, stage, summ, &react_results);

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

void CLoadGroupDumper::DumpLoadGroupDeflections(std::ostream& os, BSTR lgName, long ist, ResultsSummationType summ)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   os<<endl;
   os<<"   Deflections for LoadGroup: \""<<W2A(lgName)<<"\", Stage: \""<<W2A(stage)<<"\", SummationType:"<<(summ==rsIncremental?"Incremental":"Cumulative")<<endl<<endl;
   os<<"   Superstructure POIs sorted by location. Deflections are in Global Coordinates"<<endl;
   os<<"   -----------------------------------------------------------------------------"<<endl;
   os<<endl;
   os<<"                  <----------- Left -------------> <----------- Right ------------>"<<endl;
   os<<"  POI   Location     Dx          Dy         Rz        Dx         Dy          Rz"<<endl;
   os<<" ------ --------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;

   // compute member responses
   CComPtr<ILongArray> poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, summ, &poi_ids, &poi_locs);

   CComPtr<ILoadGroupResponse> response;
   hr = m_Engine->get_LoadGroupResponse(&response);

   CComPtr<ISectionResult3Ds> defl_results;
   hr=response->ComputeDeflections(lgName, poi_ids, stage, summ, &defl_results);

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
      os<<right<<setw(7)<<poi_id<<setw(10)<<poi_loc
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
   CComPtr<ILongArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   CComPtr<ISectionResult3Ds> spt_defl_results;
   hr=response->ComputeDeflections(lgName, spt_poi_ids, stage, summ, &spt_defl_results);

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
   CComPtr<ILongArray> supp_ids;
   m_Util->GetSupportIDs(ist, &supp_ids);

   CComPtr<IResult3Ds> react_results;
   hr=response->ComputeSupportDeflections(lgName, supp_ids, stage, summ, &react_results);

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

void CLoadGroupDumper::DumpLoadGroupStresses(std::ostream& os, BSTR lgName, long ist, ResultsSummationType summ)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   os<<endl;
   os<<"   Stresses for LoadGroup: \""<<W2A(lgName)<<"\", Stage: \""<<W2A(stage)<<"\", SummationType:"<<(summ==rsIncremental?"Incremental":"Cumulative")<<endl<<endl;
   os<<"   Superstructure POIs sorted by location"<<endl;
   os<<"   --------------------------------------"<<endl;
   os<<endl;
   os<<"                  <------------------ Left -----------------> <----------------- Right ----------------->"<<endl;
   os<<"  POI    Locaton    sP0          Sp1        Sp2        Sp3       Sp0        Sp1        Sp2        Sp3"<<endl;
   os<<" ------ --------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;

   // compute member responses
   CComPtr<ILongArray> poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, summ, &poi_ids, &poi_locs);

   CComPtr<ILoadGroupResponse> response;
   hr = m_Engine->get_LoadGroupResponse(&response);

   CComPtr<ISectionStressResults> stress_results;
   hr=response->ComputeStresses(lgName, poi_ids, stage, summ, &stress_results);

   CollectionIndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (CollectionIndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      CComPtr<ISectionStressResult> stress_result;
      hr = stress_results->get_Item(ip, &stress_result);

      std::string rgt_sp0, rgt_sp1, rgt_sp2, rgt_sp3;
      std::string lft_sp0, lft_sp1, lft_sp2, lft_sp3;

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

      os<<right<<setw(7)<<poi_id<<setw(10)<<poi_loc
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
   CComPtr<ILongArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   CComPtr<ISectionStressResults> spt_stress_results;
   hr=response->ComputeStresses(lgName, spt_poi_ids, stage, summ, &spt_stress_results);

   CollectionIndexType num_spt_pois;
   hr = spt_poi_ids->get_Count(&num_spt_pois);
   for (CollectionIndexType ip=0; ip<num_spt_pois; ip++)
   {
      PoiIDType poi_id;
      hr = spt_poi_ids->get_Item(ip, &poi_id);

      CComPtr<ISectionStressResult> stress_result;
      hr = spt_stress_results->get_Item(ip, &stress_result);

      std::string rgt_sp0, rgt_sp1, rgt_sp2, rgt_sp3;
      std::string lft_sp0, lft_sp1, lft_sp2, lft_sp3;

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

void CLoadGroupDumper::DumpForceInfluenceLines(std::ostream& os, long ist, ForceEffectType feType)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   // get all pois in structure
   CComPtr<ILongArray> ss_poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, rsIncremental, &ss_poi_ids, &poi_locs);

   CComPtr<ILongArray> poi_ids;
   hr = ss_poi_ids->Clone(&poi_ids);  // clone so we don't modify original

   CComPtr<ILongArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   // append support pois to ss pois
   CollectionIndexType spt_cnt;
   hr = spt_poi_ids->get_Count(&spt_cnt);
   for (CollectionIndexType is=0; is<spt_cnt; is++)
   {
      PoiIDType id;
      hr = spt_poi_ids->get_Item(is,&id);

      hr = poi_ids->Add(id);
   }

   CComPtr<IInfluenceLineResponse> response;
   hr = m_Engine->get_InfluenceLineResponse(&response);

   std::string efftype;
   if (feType==fetFx)
      efftype = "Axial";
   else if (feType==fetFy)
      efftype = "Shear";
   else if (feType==fetMz)
      efftype = "Moment";
   else
      ATLASSERT(0);

   CollectionIndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (CollectionIndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      os<<endl;
      os<<"   Force Influence Line for "<<efftype<<" in  Stage: \""<<W2A(stage)<<"\" at POI "<<poi_id<<endl;
      os<<"   ---------------------------------------------------------------------------------------------"<<endl;
      os<<endl;

      CComPtr<IInfluenceLine> lft_infl, rgt_infl;
      hr = response->ComputeForceInfluenceLine(poi_id, stage, feType, roMember, &lft_infl, &rgt_infl);

      if (rgt_infl!=NULL)
      {
         os<<"Left Influence Line"<<endl;
      }

      os<<"   #     Location     Value"<<endl;
      os<<" ------ ----------- -----------"<<endl;

      CollectionIndexType ip_cnt;
      hr = lft_infl->get_Count(ilsBoth, &ip_cnt);

      for (CollectionIndexType ip=0; ip<ip_cnt; ip++)
      {
         double value, loc;
         InfluenceLocationType iltype;
         hr = lft_infl->Item(ip, ilsBoth, &value, &iltype, &loc);

         std::string strloc( Fl(loc) );
         if (iltype==iflDualLeft)
            strloc += "L";
         else if (iltype==iflDualRight)
            strloc += "R";
         else
            strloc += " ";

         os<<right<<setw(7)<<ip<<strloc<<Ff(value)<<endl;
      }

      // deal with right influence line if we have one
      if (rgt_infl!=NULL)
      {
         os<<endl<<"Right Influence Line - values not adjusted for sign changes"<<endl;

         os<<"   #     Location     Value"<<endl;
         os<<" ------ ----------- -----------"<<endl;

         hr = rgt_infl->get_Count(ilsBoth, &ip_cnt);

         for (CollectionIndexType ip=0; ip<ip_cnt; ip++)
         {
            double value, loc;
            InfluenceLocationType iltype;
            hr = rgt_infl->Item(ip, ilsBoth, &value, &iltype, &loc);

            std::string strloc( Fl(loc) );
            if (iltype==iflDualLeft)
               strloc += "L";
            else if (iltype==iflDualRight)
               strloc += "R";
            else
               strloc += " ";

            os<<right<<setw(7)<<ip<<strloc<<Ff(value)<<endl;
         }
      }

   }

   os<<endl;
}

void CLoadGroupDumper::DumpDeflectionInfluenceLines(std::ostream& os, long ist, ForceEffectType feType)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   // get all pois in structure
   CComPtr<ILongArray> ss_poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, rsIncremental, &ss_poi_ids, &poi_locs);

   CComPtr<ILongArray> poi_ids;
   hr = ss_poi_ids->Clone(&poi_ids);  // clone so we don't modify original

   CComPtr<ILongArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   // append support pois to ss pois
   CollectionIndexType spt_cnt;
   hr = spt_poi_ids->get_Count(&spt_cnt);
   for (CollectionIndexType is=0; is<spt_cnt; is++)
   {
      PoiIDType id;
      hr = spt_poi_ids->get_Item(is,&id);

      hr = poi_ids->Add(id);
   }

   CComPtr<IInfluenceLineResponse> response;
   hr = m_Engine->get_InfluenceLineResponse(&response);

   std::string efftype;
   if (feType==fetFx)
      efftype = "Dx";
   else if (feType==fetFy)
      efftype = "Dy";
   else if (feType==fetMz)
      efftype = "Rz";
   else
      ATLASSERT(0);

   CollectionIndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (CollectionIndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      os<<endl;
      os<<"   Deflection Influence Line for "<<efftype<<" in  Stage: \""<<W2A(stage)<<"\" at POI "<<poi_id<<endl;
      os<<"   --------------------------------------------------------------------------------------------------------"<<endl;
      os<<endl;

      CComPtr<IInfluenceLine> lft_infl, rgt_infl;
      hr = response->ComputeDeflectionInfluenceLine(poi_id, stage, feType, &lft_infl, &rgt_infl);

      if (rgt_infl!=NULL)
      {
         os<<"Left Influence Line"<<endl;
      }

      os<<"   #     Location     Value"<<endl;
      os<<" ------ ----------- -----------"<<endl;

      CollectionIndexType ip_cnt;
      hr = lft_infl->get_Count(ilsBoth, &ip_cnt);

      for (CollectionIndexType ip=0; ip<ip_cnt; ip++)
      {
         double value, loc;
         InfluenceLocationType iltype;
         hr = lft_infl->Item(ip, ilsBoth, &value, &iltype, &loc);

         std::string strloc( Fl(loc) );
         if (iltype==iflDualLeft)
            strloc += "L";
         else if (iltype==iflDualRight)
            strloc += "R";
         else
            strloc += " ";

         os<<right<<setw(7)<<ip<<strloc<<Ff(value)<<endl;
      }

      // deal with right influence line if we have one
      if (rgt_infl!=NULL)
      {
         os<<endl<<"Right Influence Line"<<endl;

         os<<"   #     Location     Value"<<endl;
         os<<" ------ ----------- -----------"<<endl;

         hr = rgt_infl->get_Count(ilsBoth, &ip_cnt);

         for (CollectionIndexType ip=0; ip<ip_cnt; ip++)
         {
            double value, loc;
            InfluenceLocationType iltype;
            hr = rgt_infl->Item(ip, ilsBoth, &value, &iltype, &loc);

            std::string strloc( Fl(loc) );
            if (iltype==iflDualLeft)
               strloc += "L";
            else if (iltype==iflDualRight)
               strloc += "R";
            else
               strloc += " ";

            os<<right<<setw(7)<<ip<<strloc<<Ff(value)<<endl;
         }
      }
   }

   os<<endl;
}

void CLoadGroupDumper::DumpContraflexureResponse(std::ostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   long stg_cnt = m_Util->StageCount();

   CComPtr<IContraflexureResponse> response;
   hr = m_Engine->get_ContraflexureResponse(&response);

   CComPtr<ILiveLoadNegativeMomentRegion> llnmr;
   hr = m_Engine->get_LiveLoadNegativeMomentRegion(&llnmr);

   for (long istg=0; istg<stg_cnt; istg++)
   {
      CComBSTR stage;
      m_Util->StageName(istg, &stage);

      os<<endl;
      os<<"  Contraflexure Response for Stage: \""<<W2A(stage)<<"\""<<endl;
      os<<"  --------------------------------------------------------------"<<endl<<endl;


      os<<"  Live Load Negative Moment Regions - Stage \""<<W2A(stage)<<"\""<<endl;

      os<<"    Negative Moment Region Locations "<<endl;
      os<<"    #    Location"<<endl;
      os<<"  ----- -----------"<<endl;


      CComPtr<IDblArray> llnm_locs;
      hr = llnmr->ComputeNegativeMomentRegions(stage, &llnm_locs);

      CollectionIndexType num_nmrs;
      hr = llnm_locs->get_Count(&num_nmrs);

      for (CollectionIndexType inm=0; inm<num_nmrs; inm++)
      {
         double loc;
         hr = llnm_locs->get_Item(inm, &loc);

         os<<right<<setw(7)<<inm<<Fl(loc)<<endl;
      }

      os<<endl;
      os<<"    Raw Contraflexure Locations  - Stage \""<<W2A(stage)<<"\""<<endl;
      os<<"    #    Location"<<endl;
      os<<"  ----- -----------"<<endl;

      CComPtr<IDblArray> contr_locs;
      hr = response->ComputeContraflexureLocations(stage, &contr_locs);

      CollectionIndexType contr_cnt;
      hr = contr_locs->get_Count(&contr_cnt);

      for (CollectionIndexType icl=0; icl<contr_cnt; icl++)
      {
         double loc;
         hr = contr_locs->get_Item(icl, &loc);

         os<<right<<setw(7)<<icl<<Fl(loc)<<endl;
      }

      os<<endl;
      // contraflexure moment response
      os<<" Moment Response Due to Uniform Unit Contraflexure Load - Stage \""<<W2A(stage)<<"\""<<endl<<endl;
      os<<"   #     Location      Value"<<endl;
      os<<" ------ ----------- -----------"<<endl;

      CComPtr<IInfluenceLine> cf_resp;
      hr = response->ComputeContraflexureResponse(stage, fetMz, &cf_resp);

      CollectionIndexType ip_cnt;
      hr = cf_resp->get_Count(ilsBoth, &ip_cnt);

      for (CollectionIndexType ip=0; ip<ip_cnt; ip++)
      {
         double value, loc;
         InfluenceLocationType iltype;
         hr = cf_resp->Item(ip, ilsBoth, &value, &iltype, &loc);

         std::string strloc( Fl(loc) );
         if (iltype==iflDualLeft)
            strloc += "L";
         else if (iltype==iflDualRight)
            strloc += "R";
         else
            strloc += " ";

         os<<right<<setw(7)<<ip<<strloc<<Ff(value)<<endl;
      }
 
      // next status of superstructure pois wrt contraflexure zones
      CComPtr<ILongArray> poi_ids;
      CComPtr<IDblArray> poi_locs;
      m_Util->GetSuperstructurePOIs(istg, rsIncremental, &poi_ids, &poi_locs);

      os<<endl;
      os<<"  Status of Superstructure POIs WRT Contraflexure Zones - Stage \""<<W2A(stage)<<"\""<<endl<<endl;
      os<<"  POI    Location   In CF Zone?"<<endl;
      os<<" ------ ---------- --------------"<<endl;

      CollectionIndexType num_pois;
      hr = poi_ids->get_Count(&num_pois);
      for (CollectionIndexType ip=0; ip<num_pois; ip++)
      {
         PoiIDType poi_id;
         hr = poi_ids->get_Item(ip, &poi_id);

         double poi_loc;
         hr = poi_locs->get_Item(ip, &poi_loc);

         InZoneType inzone;
         response->get_IsPOIInContraflexureZone(poi_id, stage, &inzone);

         string striz;
		   if (inzone==izInside)
            striz = "Inside";
		   else if (inzone==izOutside)
            striz = "Outside";
         else if (inzone==izLeftEdge)
            striz = "Left Edge";
         else if (inzone==izRightEdge)
            striz = "Right Edge";
         else
            ATLASSERT(0);

         os<<right<<setw(7)<<poi_id<<Fl(poi_loc)<<"   "<<left<<striz<<endl;
      }
   }

   os<<endl;
}
