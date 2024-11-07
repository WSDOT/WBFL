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

void CLoadGroupDumper::DumpAnalysisPOIs(std::_tostream& os)
{
   DumpAPOIs(os);
   DumpPOIDistributionFactors(os);
   DumpPOIStressPoints(os);
}

void CLoadGroupDumper::DumpAPOIs(std::_tostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   CComPtr<IAnalysisPOIs> apois;
   hr = m_Engine->get_AnalysisPOIs(&apois);

   os<<endl;
   os<<_T(" Superstructure Anaysis POIs for all Stages (negative POI ID's denotes internally generated)")<<endl;
   os<<_T(" -------------------------------------------------------------------------------------------")<<endl;

   PoiIDType spoi_inc,cpoi_inc;
   hr = apois->get_SpanPoiIncrement(&spoi_inc);
   os<<_T("    Span POI increment is ")<<spoi_inc<<endl;
   hr = apois->get_CantileverPoiIncrement(&cpoi_inc);
   os<<_T("    Cantilever POI increment is ")<<cpoi_inc<<endl<<endl;

   StageIndexType stg_cnt = m_Util->StageCount();

   for (StageIndexType is=0; is<stg_cnt; is++)
   {
      CComBSTR stgnm;
      m_Util->StageName(is, &stgnm);

      os<<_T("    Analysis POIs for stage: ")<<W2A(stgnm)<<endl<<endl;

      CComPtr<IDblArray> poi_locs;
      CComPtr<IIDArray> poi_ids;
      m_Util->GetSuperstructurePOIs(is, rsIncremental, &poi_ids,&poi_locs); // use incremental since we want all pois

      IndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<_T("           Member              Member     Member     Global X ")<<endl;
      os<<_T(" POI ID     Type                ID       Location    Location ")<<endl;
      os<<_T(" ------ -------------------- ---------- ----------- -----------")<<endl;

      for (IndexType ip=0; ip<poi_cnt; ip++)
      {
         IDType id;
         hr = poi_ids->get_Item(ip, &id);
         Float64 gx;
         hr = poi_locs->get_Item(ip, &gx);

         MemberType membertype;
         MemberIDType memberid;
         Float64 memberloc;
         hr = apois->GetPoiInfo(stgnm, id, &membertype, &memberid, &memberloc);

         std::_tstring tmp = Fl(memberloc);

         os<<right<<setw(7)<<id<<_T(" ")<<left<<setw(21)<<MTToString(membertype)
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
      os<<_T(" Support POIs")<<endl;
      os<<_T(" ------------")<<endl;

      CComPtr<IIDArray> poi_ids;
      m_Util->GetSupportPOIs(0, &poi_ids);

      IndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<_T("           Member              Member     Member  ")<<endl;
      os<<_T(" POI ID     Type                ID       Location ")<<endl;
      os<<_T(" ------ -------------------- ---------- -----------")<<endl;

      for (IndexType ip=0; ip<poi_cnt; ip++)
      {
         IDType id;
         hr = poi_ids->get_Item(ip, &id);

         MemberType membertype;
         MemberIDType memberid;
         Float64 memberloc;
         hr = apois->GetPoiInfo(stgnm, id, &membertype, &memberid, &memberloc);

         os<<right<<setw(7)<<id<<_T(" ")<<left<<setw(21)<<MTToString(membertype)
           <<right<<setw(10)<<memberid<<Fl(memberloc)<<endl;
      }
   }

   os<<endl;
}


void CLoadGroupDumper::DumpPOIDistributionFactors(std::_tostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   CComPtr<IAnalysisPOIs> apois;
   hr = m_Engine->get_AnalysisPOIs(&apois);

   // undocumented qi
   CComQIPtr<IGetDistributionFactors> getdfs(apois);
   ATLASSERT(getdfs);

   os<<endl;
   os<<_T(" Distribution Factors At POIs for all Stages")<<endl;
   os<<_T(" -------------------------------------------")<<endl<<endl;;

   StageIndexType stg_cnt = m_Util->StageCount();
   for (StageIndexType is=0; is<stg_cnt; is++)
   {
      CComBSTR stage;
      m_Util->StageName(is, &stage);

      os<<_T("    Distribution Factors At Superstructure POIs for stage: ")<<W2A(stage)<<endl<<endl;

      CComPtr<IDblArray> poi_locs;
      CComPtr<IIDArray> poi_ids;
      m_Util->GetSuperstructurePOIs(is, rsIncremental, &poi_ids,&poi_locs); // use incremental since we want all pois

      IndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<_T("         Global X ")<<endl;
      os<<_T(" POI ID  Location    gPMSgl   gPMMul   gNMSgl   gNMMul   gVSgl    gVMul    gDSgl    gDMul    gRSgl    gRMul    gTSgl    gTMul     gFatM    gFatV    gPed ")<<endl;
      os<<_T(" ------ ----------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- --------")<<endl;

      for (IndexType ip=0; ip<poi_cnt; ip++)
      {
         IDType id;
         hr = poi_ids->get_Item(ip, &id);
         Float64 gx;
         hr = poi_locs->get_Item(ip, &gx);

         CComPtr<IDistributionFactor> left_df, right_df;
         hr = getdfs->GetPOIDistributionFactor(id, stage, &left_df, &right_df);

         Float64 gPMSgl, gPMMul, gNMSgl, gNMMul, gVSgl, gVMul, gDSgl, gDMul, gRSgl, gRMul, gTSgl, gTMul, gFatM, gFatV, gPed;
         hr = left_df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFatM, &gFatV, &gPed);

         os<<right<<setw(7)<<id<<Fl(gx)
           <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
           <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul
           <<setw(9)<<gFatM<<setw(9)<<gFatV<<setw(9)<<gPed<<endl;

         if(right_df)
         {
            hr = right_df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFatM, &gFatV, &gPed);

            os<<right<<setw(19)<<_T(" ")
              <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
              <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul
              <<setw(9)<<gFatM<<setw(9)<<gFatV<<setw(9)<<gPed<<endl;
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
      os<<_T(" Support POI Distribution Factors")<<endl;
      os<<_T(" --------------------------------")<<endl;

      CComPtr<IIDArray> poi_ids;
      m_Util->GetSupportPOIs(0, &poi_ids);

      IndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<_T("       ")<<endl;
      os<<_T(" POI ID  gPMSgl   gPMMul   gNMSgl   gNMMul   gVSgl    gVMul    gDSgl    gDMul    gRSgl    gRMul    gTSgl    gTMul     gFat")<<endl;
      os<<_T(" ------ -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- --------")<<endl;

      for (IndexType ip=0; ip<poi_cnt; ip++)
      {
         IDType id;
         hr = poi_ids->get_Item(ip, &id);

         CComPtr<IDistributionFactor> left_df, right_df;
         hr = getdfs->GetPOIDistributionFactor(id, stage, &left_df, &right_df);

         Float64 gPMSgl, gPMMul, gNMSgl, gNMMul, gVSgl, gVMul, gDSgl, gDMul, gRSgl, gRMul, gTSgl, gTMul, gFatM, gFatV, gPed;
         hr = left_df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFatM, &gFatV, &gPed);

         os<<right<<setw(7)<<id
           <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
           <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul
           <<setw(9)<<gFatM<<setw(9)<<gFatV<<setw(9)<<gPed<<endl;


         if(right_df)
         {
            hr = right_df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFatM, &gFatV, &gPed);

            os<<right<<setw(19)<<_T(" ")
              <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
              <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul
              <<setw(9)<<gFatM<<setw(9)<<gFatV<<setw(9)<<gPed<<endl;
         }
      }
   }

   // next support dfs - report stage 0 only - only can remove temporary supports
   if (stg_cnt>0)
   {
      CComBSTR stage;
      m_Util->StageName(0, &stage);

      os<<endl;
      os<<_T(" Support Distribution Factors - First Stage Only")<<endl;
      os<<_T(" -----------------------------------------------")<<endl;

      CComPtr<IIDArray> spt_ids;
      m_Util->GetSupportIDs(0, &spt_ids);

      IndexType spt_cnt; 
      hr = spt_ids->get_Count(&spt_cnt);

      os<<_T("       ")<<endl;
      os<<_T(" Suppt   gPMSgl   gPMMul   gNMSgl   gNMMul   gVSgl    gVMul    gDSgl    gDMul    gRSgl    gRMul    gTSgl    gTMul     gFatM    gFatV    gPed")<<endl;
      os<<_T(" ------ -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- --------")<<endl;

      for (IndexType ip=0; ip<spt_cnt; ip++)
      {
         IDType id;
         hr = spt_ids->get_Item(ip, &id);

         CComPtr<IDistributionFactor> s_df;
         hr = getdfs->GetSupportDistributionFactor(id, stage, &s_df);

         Float64 gPMSgl, gPMMul, gNMSgl, gNMMul, gVSgl, gVMul, gDSgl, gDMul, gRSgl, gRMul, gTSgl, gTMul, gFatM, gFatV, gPed;
         hr = s_df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFatM, &gFatV, &gPed);

         os<<right<<setw(7)<<id
           <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
           <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul
           <<setw(9)<<gFatM<<setw(9)<<gFatV<<setw(9)<<gPed<<endl;
      }
   }

   os<<endl;
}

void CLoadGroupDumper::DumpPOIStressPoints(std::_tostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   CComPtr<IAnalysisPOIs> apois;
   hr = m_Engine->get_AnalysisPOIs(&apois);

   // undocumented qi
   CComQIPtr<IGetStressPoints> getsps(apois);
   ATLASSERT(getsps);

   os<<endl;
   os<<_T(" Stress Points At POIs for all Stages")<<endl;
   os<<_T(" -------------------------------------------")<<endl<<endl;;

   StageIndexType stg_cnt = m_Util->StageCount();
   for (StageIndexType is=0; is<stg_cnt; is++)
   {
      CComBSTR stage;
      m_Util->StageName(is, &stage);

      os<<_T("    Stress Points At Superstructure POIs for stage: ")<<W2A(stage)<<endl<<endl;

      CComPtr<IDblArray> poi_locs;
      CComPtr<IIDArray> poi_ids;
      m_Util->GetSuperstructurePOIs(is, rsIncremental, &poi_ids,&poi_locs); // use incremental since we want all pois

      IndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<_T("         Global X         <-------- Left -----> <------ Right ------>")<<endl;
      os<<_T(" POI ID  Location    SP #      Sa           Sm         Sa          Sm    ")<<endl;
      os<<_T(" ------ ----------- ------ ----------- ----------- ----------- -----------")<<endl;

      for (IndexType ip=0; ip<poi_cnt; ip++)
      {
         IDType id;
         hr = poi_ids->get_Item(ip, &id);
         Float64 gx;
         hr = poi_locs->get_Item(ip, &gx);

         CComPtr<IStressPoints> left_sps, right_sps;
         hr = getsps->GetStressPointsAtPOI(id, stage, &left_sps, &right_sps);

         IndexType left_cnt=0, right_cnt=0;
         hr = left_sps->get_Count(&left_cnt);
         if (right_sps)
            hr = right_sps->get_Count(&right_cnt);

         IndexType max_cnt = max(left_cnt, right_cnt);

         for (IndexType isp=0; isp<max_cnt; isp++)
         {
            _tstring str_lft_sa, str_rgt_sa;
            _tstring str_lft_sm, str_rgt_sm;
            if (isp<left_cnt)
            {
               CComPtr<IStressPoint> sp;
               hr = left_sps->get_Item(isp, &sp);

               Float64 sa, sm;
               hr = sp->get_Sa(&sa);
               hr = sp->get_Sm(&sm);

               str_lft_sa = Fl(sa);
               str_lft_sm = Fl(sm);
            }

            if (isp<right_cnt)
            {
               CComPtr<IStressPoint> sp;
               hr = right_sps->get_Item(isp, &sp);

               Float64 sa, sm;
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
               os<<right<<setw(19)<<_T(" ")<<setw(7)<<isp<<setw(11)<<str_lft_sa<<setw(11)<<str_lft_sm
                 <<setw(11)<<str_rgt_sa<<setw(11)<<str_rgt_sm<<endl;
            }
         }
      }

      os<<endl;
   }

   // next support pois
   for (StageIndexType is=0; is<stg_cnt; is++)
   {
      CComBSTR stage;
      m_Util->StageName(is, &stage);

      os<<endl;
      os<<_T(" Support POI Stress Points - Stage \"")<<W2A(stage)<<_T("\"")<<endl;
      os<<_T(" ------------------------------------------------------------")<<endl;

      CComPtr<IIDArray> poi_ids;
      m_Util->GetSupportPOIs(is, &poi_ids);

      IndexType poi_cnt; 
      hr = poi_ids->get_Count(&poi_cnt);

      os<<_T("               <-------- Left -----> <------ Right ------>")<<endl;
      os<<_T(" POI ID  SP #      Sa          Sm          Sa          Sm    ")<<endl;
      os<<_T(" ------ ------ ----------- ----------- ----------- -----------")<<endl;

      for (IndexType ip=0; ip<poi_cnt; ip++)
      {
         IDType id;
         hr = poi_ids->get_Item(ip, &id);

         CComPtr<IStressPoints> left_sps, right_sps;
         hr = getsps->GetStressPointsAtPOI(id, stage, &left_sps, &right_sps);

         IndexType left_cnt=0, right_cnt=0;
         hr = left_sps->get_Count(&left_cnt);
         if (right_sps)
            hr = right_sps->get_Count(&right_cnt);

         IndexType max_cnt = max(left_cnt, right_cnt);

         for (IndexType isp=0; isp<max_cnt; isp++)
         {
            _tstring str_lft_sa, str_rgt_sa;
            _tstring str_lft_sm, str_rgt_sm;
            if (isp<left_cnt)
            {
               CComPtr<IStressPoint> sp;
               hr = left_sps->get_Item(isp, &sp);

               Float64 sa, sm;
               hr = sp->get_Sa(&sa);
               hr = sp->get_Sm(&sm);

               str_lft_sa = Fl(sa);
               str_lft_sm = Fl(sm);
            }

            if (isp<right_cnt)
            {
               CComPtr<IStressPoint> sp;
               hr = right_sps->get_Item(isp, &sp);

               Float64 sa, sm;
               hr = sp->get_Sa(&sa);
               hr = sp->get_Sm(&sm);

               str_rgt_sa = Fl(sa);
               str_rgt_sm = Fl(sm);
            }

            if (isp==0)
            {
               os<<right<<setw(7)<<id<<_T(" ")<<setw(6)<<isp<<setw(11)<<str_lft_sa<<setw(11)<<str_lft_sm
                 <<setw(11)<<str_rgt_sa<<setw(11)<<str_rgt_sm<<endl;
            }
            else
            {
               os<<right<<setw(8)<<_T(" ")<<setw(6)<<isp<<setw(11)<<str_lft_sa<<setw(11)<<str_lft_sm
                 <<setw(11)<<str_rgt_sa<<setw(11)<<str_rgt_sm<<endl;
            }
         }
      }
   }
}

void CLoadGroupDumper::DumpLoadGroupResponse(std::_tostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   os<<endl<<endl;
   os<<_T(" DUMP OF LOADGROUP RESPONSES")<<endl;
   os<<_T(" ===========================")<<endl<<endl;

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

   IndexType lg_cnt;
   hr = loadgroups->get_Count(&lg_cnt);
   for (IndexType ilg=0; ilg<lg_cnt; ilg++)
   {
      CComPtr<ILoadGroup> loadgroup;
      hr = loadgroups->get_Item(ilg, &loadgroup);

      CComBSTR lg_name;
      hr = loadgroup->get_Name(&lg_name);

      IndexType idx;
      HRESULT hres = active_lgs->Find(lg_name, &idx);
      if (FAILED(hres))
      {
         // not found in active list
         hr = dead_lgs->Add(lg_name);
      }
   }

   IndexType dead_cnt;
   hr = dead_lgs->get_Count(&dead_cnt);
   if (dead_cnt>0)
   {
      os<<_T("  There are ")<<dead_cnt<<_T(" LoadGroups in this model with no loads (zero results). They are: ")<<endl;
      for (IndexType ilg=0; ilg<dead_cnt; ilg++)
      {
         CComBSTR name;
         hr = dead_lgs->get_Item(ilg, &name);
         os<<_T("    ")<<W2A(name)<<endl;
      }

      os<<_T("  No Results will be be reported for these LoadGroups")<<endl<<endl;
   }

   // loop over all of our active loadgroups and stages and report responses
   StageIndexType stg_cnt = m_Util->StageCount();

   IndexType alg_cnt;
   hr = active_lgs->get_Count(&alg_cnt);
   for (IndexType ilg=0; ilg<alg_cnt; ilg++)
   {
      CComBSTR lg_name;
      hr = active_lgs->get_Item(ilg, &lg_name);

      // forces
      for (StageIndexType ist=0; ist<stg_cnt; ist++)
      {
         DumpLoadGroupForces(os, lg_name, ist, rsIncremental);
         DumpLoadGroupForces(os, lg_name, ist, rsCumulative);
      }

      // deflections
      for (StageIndexType ist=0; ist<stg_cnt; ist++)
      {
         DumpLoadGroupDeflections(os, lg_name, ist, rsIncremental);
         DumpLoadGroupDeflections(os, lg_name, ist, rsCumulative);
      }

      // stresses
      for (StageIndexType ist=0; ist<stg_cnt; ist++)
      {
         DumpLoadGroupStresses(os, lg_name, ist, rsIncremental);
         DumpLoadGroupStresses(os, lg_name, ist, rsCumulative);
      }
   }
}

void CLoadGroupDumper::DumpInfluenceLines(std::_tostream& os)
{
   StageIndexType stg_cnt = m_Util->StageCount();

   os<<_T(" INFLUENCE LINE RESPONSE")<<endl;
   os<<_T(" -----------------------")<<endl;

   for (StageIndexType ist=0; ist<stg_cnt; ist++)
   {
      DumpForceInfluenceLines(os, ist, fetFx);
      DumpForceInfluenceLines(os, ist, fetFy);
      DumpForceInfluenceLines(os, ist, fetMz);
   }

   for (StageIndexType ist=0; ist<stg_cnt; ist++)
   {
      DumpDeflectionInfluenceLines(os, ist, fetFx);
      DumpDeflectionInfluenceLines(os, ist, fetFy);
      DumpDeflectionInfluenceLines(os, ist, fetMz);
   }
}



void CLoadGroupDumper::DumpLoadGroupForces(std::_tostream& os, BSTR lgName, StageIndexType ist, ResultsSummationType summ)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   os<<endl;
   os<<_T("   Forces for LoadGroup: \"")<<W2A(lgName)<<_T("\", Stage: \"")<<W2A(stage)<<_T("\", SummationType:")<<(summ==rsIncremental?_T("Incremental"):_T("Cumulative"))<<endl<<endl;
   os<<_T("   Superstructure POIs sorted by location")<<endl;
   os<<_T("   --------------------------------------")<<endl;
   os<<endl;
   os<<_T("                  <----------- Left -------------> <----------- Right ------------>")<<endl;
   os<<_T("  POI   Location     Axial      Shear      Moment    Axial      Shear      Moment")<<endl;
   os<<_T(" ------ --------- ---------- ---------- ---------- ---------- ---------- ----------")<<endl;

   // compute member responses
   CComPtr<IIDArray> poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, summ, &poi_ids, &poi_locs);

   CComPtr<ILoadGroupResponse> response;
   hr = m_Engine->get_LoadGroupResponse(&response);

   CComPtr<ISectionResult3Ds> force_results;
   hr=response->ComputeForces(lgName, poi_ids, stage, roMember, summ, &force_results);

   IndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (IndexType ip=0; ip<num_pois; ip++)
   {
      IDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      Float64 rgt_moment, rgt_shear, rgt_axial;
      Float64 lft_moment, lft_shear, lft_axial;
      CComPtr<ISectionResult3D> force_result;
      hr = force_results->get_Item(ip, &force_result);
      hr = force_result->get_XLeft(&lft_axial);
      hr = force_result->get_YLeft(&lft_shear);
      hr = force_result->get_ZLeft(&lft_moment);
      hr = force_result->get_XRight(&rgt_axial);
      hr = force_result->get_YRight(&rgt_shear);
      hr = force_result->get_ZRight(&rgt_moment);

      Float64 poi_loc;
      hr = poi_locs->get_Item(ip,&poi_loc);
      os<<right<<setw(7)<<poi_id<<setw(10)<<poi_loc
        <<Ff(lft_axial)<<Ff(lft_shear)<<Ff(lft_moment)
        <<Ff(rgt_axial)<<Ff(rgt_shear)<<Ff(rgt_moment)<<endl;
   }

   os<<endl;
   os<<_T("   Support POIs (forces in member coordinates)")<<endl;
   os<<_T("   -------------------------------------------")<<endl;

   os<<endl;
   os<<_T("        <----------- Left -------------> <----------- Right ------------>")<<endl;
   os<<_T("  POI      Axial      Shear      Moment    Axial      Shear      Moment")<<endl;
   os<<_T(" ------ ---------- ---------- ---------- ---------- ---------- ----------")<<endl;

   // compute member responses
   CComPtr<IIDArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   CComPtr<ISectionResult3Ds> spt_force_results;
   hr=response->ComputeForces(lgName, spt_poi_ids, stage, roMember, summ, &spt_force_results);

   IndexType num_spt_pois;
   hr = spt_poi_ids->get_Count(&num_spt_pois);
   for (IndexType ip=0; ip<num_spt_pois; ip++)
   {
      IDType poi_id;
      hr = spt_poi_ids->get_Item(ip, &poi_id);

      Float64 rgt_moment, rgt_shear, rgt_axial;
      Float64 lft_moment, lft_shear, lft_axial;
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
   os<<_T("   Reactions (global coordinates)")<<endl
     <<_T("   ------------------------------")<<endl;
   CComPtr<IIDArray> supp_ids;
   m_Util->GetSupportIDs(ist, &supp_ids);

   CComPtr<IResult3Ds> react_results;
   hr=response->ComputeReactions(lgName, supp_ids, stage, summ, &react_results);

   os<<_T("   POI    X React    Y React    MZ React")<<std::endl;
   os<<_T(" ------ ---------- ---------- ----------")<<std::endl;

   IndexType num_supp;
   hr = supp_ids->get_Count(&num_supp);
   for (IndexType is=0; is<num_supp; is++)
   {
      IDType poi_id;
      hr = supp_ids->get_Item(is,&poi_id);

      Float64 xreac, yreac, zreac;
      CComPtr<IResult3D> react_result;
      hr = react_results->get_Item(is, &react_result);
      hr = react_result->get_X(&xreac);
      hr = react_result->get_Y(&yreac);
      hr = react_result->get_Z(&zreac);

      os<<std::setw(7)<<poi_id<<Ff(xreac)<<Ff(yreac)<<Ff(zreac)<<endl;
   }

   os<<endl;
}

void CLoadGroupDumper::DumpLoadGroupDeflections(std::_tostream& os, BSTR lgName, StageIndexType ist, ResultsSummationType summ)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   os<<endl;
   os<<_T("   Deflections for LoadGroup: \"")<<W2A(lgName)<<_T("\", Stage: \"")<<W2A(stage)<<_T("\", SummationType:")<<(summ==rsIncremental?_T("Incremental"):_T("Cumulative"))<<endl<<endl;
   os<<_T("   Superstructure POIs sorted by location. Deflections are in Global Coordinates")<<endl;
   os<<_T("   -----------------------------------------------------------------------------")<<endl;
   os<<endl;
   os<<_T("                  <----------- Left -------------> <----------- Right ------------>")<<endl;
   os<<_T("  POI   Location     Dx          Dy         Rz        Dx         Dy          Rz")<<endl;
   os<<_T(" ------ --------- ---------- ---------- ---------- ---------- ---------- ----------")<<endl;

   // compute member responses
   CComPtr<IIDArray> poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, summ, &poi_ids, &poi_locs);

   CComPtr<ILoadGroupResponse> response;
   hr = m_Engine->get_LoadGroupResponse(&response);

   CComPtr<ISectionResult3Ds> defl_results;
   hr=response->ComputeDeflections(lgName, poi_ids, stage, summ, &defl_results);

   IndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (IndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      Float64 rgt_rz, rgt_dy, rgt_dx;
      Float64 lft_rz, lft_dy, lft_dx;
      CComPtr<ISectionResult3D> defl_result;
      hr = defl_results->get_Item(ip, &defl_result);
      hr = defl_result->get_XLeft(&lft_dx);
      hr = defl_result->get_YLeft(&lft_dy);
      hr = defl_result->get_ZLeft(&lft_rz);
      hr = defl_result->get_XRight(&rgt_dx);
      hr = defl_result->get_YRight(&rgt_dy);
      hr = defl_result->get_ZRight(&rgt_rz);

      Float64 poi_loc;
      hr = poi_locs->get_Item(ip,&poi_loc);
      os<<right<<setw(7)<<poi_id<<setw(10)<<poi_loc
        <<Fd(lft_dx)<<Fd(lft_dy)<<Fd(lft_rz)
        <<Fd(rgt_dx)<<Fd(rgt_dy)<<Fd(rgt_rz)<<endl;
   }

   os<<endl;
   os<<_T("   Support POIs (deflections in global coordinates)")<<endl;
   os<<_T("   -------------------------------------------------")<<endl;

   os<<endl;
   os<<_T("        <----------- Left -------------> <----------- Right ------------>")<<endl;
   os<<_T("  POI        Dx        Dy          Rz        Dx         Dy         Rz")<<endl;
   os<<_T(" ------ ---------- ---------- ---------- ---------- ---------- ----------")<<endl;

   // compute member responses
   CComPtr<IIDArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   CComPtr<ISectionResult3Ds> spt_defl_results;
   hr=response->ComputeDeflections(lgName, spt_poi_ids, stage, summ, &spt_defl_results);

   IndexType num_spt_pois;
   hr = spt_poi_ids->get_Count(&num_spt_pois);
   for (IndexType ip=0; ip<num_spt_pois; ip++)
   {
      PoiIDType poi_id;
      hr = spt_poi_ids->get_Item(ip, &poi_id);

      Float64 rgt_rz, rgt_dy, rgt_dx;
      Float64 lft_rz, lft_dy, lft_dx;
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
   os<<_T("   Support Deflections (global coordinates)")<<endl
     <<_T("   ----------------------------------------")<<endl;
   CComPtr<IIDArray> supp_ids;
   m_Util->GetSupportIDs(ist, &supp_ids);

   CComPtr<IResult3Ds> react_results;
   hr=response->ComputeSupportDeflections(lgName, supp_ids, stage, summ, &react_results);

   os<<_T("   POI      Dx         Dy          Rz")<<std::endl;
   os<<_T(" ------ ---------- ---------- ----------")<<std::endl;

   IndexType num_supp;
   hr = supp_ids->get_Count(&num_supp);
   for (IndexType is=0; is<num_supp; is++)
   {
      PoiIDType poi_id;
      hr = supp_ids->get_Item(is,&poi_id);

      Float64 xreac, yreac, zreac;
      CComPtr<IResult3D> react_result;
      hr = react_results->get_Item(is, &react_result);
      hr = react_result->get_X(&xreac);
      hr = react_result->get_Y(&yreac);
      hr = react_result->get_Z(&zreac);

      os<<std::setw(7)<<poi_id<<Fd(xreac)<<Fd(yreac)<<Fd(zreac)<<endl;
   }

   os<<endl;
}

void CLoadGroupDumper::DumpLoadGroupStresses(std::_tostream& os, BSTR lgName, StageIndexType ist, ResultsSummationType summ)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   os<<endl;
   os<<_T("   Stresses for LoadGroup: \"")<<W2A(lgName)<<_T("\", Stage: \"")<<W2A(stage)<<_T("\", SummationType:")<<(summ==rsIncremental?_T("Incremental"):_T("Cumulative"))<<endl<<endl;
   os<<_T("   Superstructure POIs sorted by location")<<endl;
   os<<_T("   --------------------------------------")<<endl;
   os<<endl;
   os<<_T("                  <------------------ Left -----------------> <----------------- Right ----------------->")<<endl;
   os<<_T("  POI    Locaton    sP0          Sp1        Sp2        Sp3       Sp0        Sp1        Sp2        Sp3")<<endl;
   os<<_T(" ------ --------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------")<<endl;

   // compute member responses
   CComPtr<IIDArray> poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, summ, &poi_ids, &poi_locs);

   CComPtr<ILoadGroupResponse> response;
   hr = m_Engine->get_LoadGroupResponse(&response);

   CComPtr<ISectionStressResults> stress_results;
   hr=response->ComputeStresses(lgName, poi_ids, stage, summ, &stress_results);

   IndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (IndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      CComPtr<ISectionStressResult> stress_result;
      hr = stress_results->get_Item(ip, &stress_result);

      std::_tstring rgt_sp0, rgt_sp1, rgt_sp2, rgt_sp3;
      std::_tstring lft_sp0, lft_sp1, lft_sp2, lft_sp3;

      IndexType cnt;
      Float64 val;
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

      Float64 poi_loc;
      hr = poi_locs->get_Item(ip,&poi_loc);

      os<<right<<setw(7)<<poi_id<<setw(10)<<poi_loc
        <<setw(11)<<lft_sp0<<setw(11)<<lft_sp1<<setw(11)<<lft_sp2<<setw(11)<<lft_sp3
        <<setw(11)<<rgt_sp0<<setw(11)<<rgt_sp1<<setw(11)<<rgt_sp2<<setw(11)<<rgt_sp3<<endl;
   }

   os<<endl;
   os<<_T("   Stresses At Support POIs")<<endl;
   os<<_T("   ------------------------")<<endl;

   os<<endl;
   os<<_T("        <------------------ Left -----------------> <----------------- Right ----------------->")<<endl;
   os<<_T("  POI     sP0          Sp1        Sp2        Sp3       Sp0        Sp1        Sp2        Sp3")<<endl;
   os<<_T(" ------ ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------")<<endl;

   // compute member responses
   CComPtr<IIDArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   CComPtr<ISectionStressResults> spt_stress_results;
   hr=response->ComputeStresses(lgName, spt_poi_ids, stage, summ, &spt_stress_results);

   IndexType num_spt_pois;
   hr = spt_poi_ids->get_Count(&num_spt_pois);
   for (IndexType ip=0; ip<num_spt_pois; ip++)
   {
      PoiIDType poi_id;
      hr = spt_poi_ids->get_Item(ip, &poi_id);

      CComPtr<ISectionStressResult> stress_result;
      hr = spt_stress_results->get_Item(ip, &stress_result);

      std::_tstring rgt_sp0, rgt_sp1, rgt_sp2, rgt_sp3;
      std::_tstring lft_sp0, lft_sp1, lft_sp2, lft_sp3;

      IndexType cnt;
      Float64 val;
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

void CLoadGroupDumper::DumpForceInfluenceLines(std::_tostream& os, StageIndexType ist, ForceEffectType feType)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   // get all pois in structure
   CComPtr<IIDArray> ss_poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, rsIncremental, &ss_poi_ids, &poi_locs);

   CComPtr<IIDArray> poi_ids;
   hr = ss_poi_ids->Clone(&poi_ids);  // clone so we don't modify original

   CComPtr<IIDArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   // append support pois to ss pois
   IndexType spt_cnt;
   hr = spt_poi_ids->get_Count(&spt_cnt);
   for (IndexType is=0; is<spt_cnt; is++)
   {
      PoiIDType id;
      hr = spt_poi_ids->get_Item(is,&id);

      hr = poi_ids->Add(id);
   }

   CComPtr<IInfluenceLineResponse> response;
   hr = m_Engine->get_InfluenceLineResponse(&response);

   std::_tstring efftype;
   if (feType==fetFx)
      efftype = _T("Axial");
   else if (feType==fetFy)
      efftype = _T("Shear");
   else if (feType==fetMz)
      efftype = _T("Moment");
   else
      ATLASSERT(0);

   IndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (IndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      os<<endl;
      os<<_T("   Force Influence Line for ")<<efftype<<_T(" in  Stage: \"")<<W2A(stage)<<_T("\" at POI ")<<poi_id<<endl;
      os<<_T("   ---------------------------------------------------------------------------------------------")<<endl;
      os<<endl;

      CComPtr<IInfluenceLine> lft_infl, rgt_infl;
      hr = response->ComputeForceInfluenceLine(poi_id, stage, feType, roMember, &lft_infl, &rgt_infl);

      if (rgt_infl!=NULL)
      {
         os<<_T("Left Influence Line")<<endl;
      }

      os<<_T("   #     Location     Value")<<endl;
      os<<_T(" ------ ----------- -----------")<<endl;

      IndexType ip_cnt;
      hr = lft_infl->get_Count(ilsBoth, &ip_cnt);

      for (IndexType ip=0; ip<ip_cnt; ip++)
      {
         Float64 value, loc;
         InfluenceLocationType iltype;
         hr = lft_infl->Item(ip, ilsBoth, &value, &iltype, &loc);

         std::_tstring strloc( Fl(loc) );
         if (iltype==iflDualLeft)
            strloc += _T("L");
         else if (iltype==iflDualRight)
            strloc += _T("R");
         else
            strloc += _T(" ");

         os<<right<<setw(7)<<ip<<strloc<<Ff(value)<<endl;
      }

      // deal with right influence line if we have one
      if (rgt_infl!=NULL)
      {
         os<<endl<<_T("Right Influence Line - values not adjusted for sign changes")<<endl;

         os<<_T("   #     Location     Value")<<endl;
         os<<_T(" ------ ----------- -----------")<<endl;

         hr = rgt_infl->get_Count(ilsBoth, &ip_cnt);

         for (IndexType ip=0; ip<ip_cnt; ip++)
         {
            Float64 value, loc;
            InfluenceLocationType iltype;
            hr = rgt_infl->Item(ip, ilsBoth, &value, &iltype, &loc);

            std::_tstring strloc( Fl(loc) );
            if (iltype==iflDualLeft)
               strloc += _T("L");
            else if (iltype==iflDualRight)
               strloc += _T("R");
            else
               strloc += _T(" ");

            os<<right<<setw(7)<<ip<<strloc<<Ff(value)<<endl;
         }
      }

   }

   os<<endl;
}

void CLoadGroupDumper::DumpDeflectionInfluenceLines(std::_tostream& os, StageIndexType ist, ForceEffectType feType)
{
   CHRException hr;
   USES_CONVERSION;

   CComBSTR stage;
   m_Util->StageName(ist, &stage);

   // get all pois in structure
   CComPtr<IIDArray> ss_poi_ids;
   CComPtr<IDblArray> poi_locs;
   m_Util->GetSuperstructurePOIs(ist, rsIncremental, &ss_poi_ids, &poi_locs);

   CComPtr<IIDArray> poi_ids;
   hr = ss_poi_ids->Clone(&poi_ids);  // clone so we don't modify original

   CComPtr<IIDArray> spt_poi_ids;
   m_Util->GetSupportPOIs(ist, &spt_poi_ids);

   // append support pois to ss pois
   IndexType spt_cnt;
   hr = spt_poi_ids->get_Count(&spt_cnt);
   for (IndexType is=0; is<spt_cnt; is++)
   {
      PoiIDType id;
      hr = spt_poi_ids->get_Item(is,&id);

      hr = poi_ids->Add(id);
   }

   CComPtr<IInfluenceLineResponse> response;
   hr = m_Engine->get_InfluenceLineResponse(&response);

   std::_tstring efftype;
   if (feType==fetFx)
      efftype = _T("Dx");
   else if (feType==fetFy)
      efftype = _T("Dy");
   else if (feType==fetMz)
      efftype = _T("Rz");
   else
      ATLASSERT(0);

   IndexType num_pois;
   hr = poi_ids->get_Count(&num_pois);
   for (IndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      hr = poi_ids->get_Item(ip, &poi_id);

      os<<endl;
      os<<_T("   Deflection Influence Line for ")<<efftype<<_T(" in  Stage: \"")<<W2A(stage)<<_T("\" at POI ")<<poi_id<<endl;
      os<<_T("   --------------------------------------------------------------------------------------------------------")<<endl;
      os<<endl;

      CComPtr<IInfluenceLine> lft_infl, rgt_infl;
      hr = response->ComputeDeflectionInfluenceLine(poi_id, stage, feType, &lft_infl, &rgt_infl);

      if (rgt_infl!=NULL)
      {
         os<<_T("Left Influence Line")<<endl;
      }

      os<<_T("   #     Location     Value")<<endl;
      os<<_T(" ------ ----------- -----------")<<endl;

      IndexType ip_cnt;
      hr = lft_infl->get_Count(ilsBoth, &ip_cnt);

      for (IndexType ip=0; ip<ip_cnt; ip++)
      {
         Float64 value, loc;
         InfluenceLocationType iltype;
         hr = lft_infl->Item(ip, ilsBoth, &value, &iltype, &loc);

         std::_tstring strloc( Fl(loc) );
         if (iltype==iflDualLeft)
            strloc += _T("L");
         else if (iltype==iflDualRight)
            strloc += _T("R");
         else
            strloc += _T(" ");

         os<<right<<setw(7)<<ip<<strloc<<Ff(value)<<endl;
      }

      // deal with right influence line if we have one
      if (rgt_infl!=NULL)
      {
         os<<endl<<_T("Right Influence Line")<<endl;

         os<<_T("   #     Location     Value")<<endl;
         os<<_T(" ------ ----------- -----------")<<endl;

         hr = rgt_infl->get_Count(ilsBoth, &ip_cnt);

         for (IndexType ip=0; ip<ip_cnt; ip++)
         {
            Float64 value, loc;
            InfluenceLocationType iltype;
            hr = rgt_infl->Item(ip, ilsBoth, &value, &iltype, &loc);

            std::_tstring strloc( Fl(loc) );
            if (iltype==iflDualLeft)
               strloc += _T("L");
            else if (iltype==iflDualRight)
               strloc += _T("R");
            else
               strloc += _T(" ");

            os<<right<<setw(7)<<ip<<strloc<<Ff(value)<<endl;
         }
      }
   }

   os<<endl;
}

void CLoadGroupDumper::DumpContraflexureResponse(std::_tostream& os)
{
   CHRException hr;
   USES_CONVERSION;

   StageIndexType stg_cnt = m_Util->StageCount();

   CComPtr<IContraflexureResponse> response;
   hr = m_Engine->get_ContraflexureResponse(&response);

   CComPtr<ILiveLoadNegativeMomentRegion> llnmr;
   hr = m_Engine->get_LiveLoadNegativeMomentRegion(&llnmr);

   for (StageIndexType istg=0; istg<stg_cnt; istg++)
   {
      CComBSTR stage;
      m_Util->StageName(istg, &stage);

      os<<endl;
      os<<_T("  Contraflexure Response for Stage: \"")<<W2A(stage)<<_T("\"")<<endl;
      os<<_T("  --------------------------------------------------------------")<<endl<<endl;


      os<<_T("  Live Load Negative Moment Regions - Stage \"")<<W2A(stage)<<_T("\"")<<endl;

      os<<_T("    Negative Moment Region Locations ")<<endl;
      os<<_T("    #    Location")<<endl;
      os<<_T("  ----- -----------")<<endl;


      CComPtr<IDblArray> llnm_locs;
      hr = llnmr->ComputeNegativeMomentRegions(stage, &llnm_locs);

      IndexType num_nmrs;
      hr = llnm_locs->get_Count(&num_nmrs);

      for (IndexType inm=0; inm<num_nmrs; inm++)
      {
         Float64 loc;
         hr = llnm_locs->get_Item(inm, &loc);

         os<<right<<setw(7)<<inm<<Fl(loc)<<endl;
      }

      os<<endl;
      os<<_T("    Raw Contraflexure Locations  - Stage \"")<<W2A(stage)<<_T("\"")<<endl;
      os<<_T("    #    Location")<<endl;
      os<<_T("  ----- -----------")<<endl;

      CComPtr<IDblArray> contr_locs;
      hr = response->ComputeContraflexureLocations(stage, &contr_locs);

      IndexType contr_cnt;
      hr = contr_locs->get_Count(&contr_cnt);

      for (IndexType icl=0; icl<contr_cnt; icl++)
      {
         Float64 loc;
         hr = contr_locs->get_Item(icl, &loc);

         os<<right<<setw(7)<<icl<<Fl(loc)<<endl;
      }

      os<<endl;
      // contraflexure moment response
      os<<_T(" Moment Response Due to Uniform Unit Contraflexure Load - Stage \"")<<W2A(stage)<<_T("\"")<<endl<<endl;
      os<<_T("   #     Location      Value")<<endl;
      os<<_T(" ------ ----------- -----------")<<endl;

      CComPtr<IInfluenceLine> cf_resp;
      hr = response->ComputeContraflexureResponse(stage, fetMz, &cf_resp);

      IndexType ip_cnt;
      hr = cf_resp->get_Count(ilsBoth, &ip_cnt);

      for (IndexType ip=0; ip<ip_cnt; ip++)
      {
         Float64 value, loc;
         InfluenceLocationType iltype;
         hr = cf_resp->Item(ip, ilsBoth, &value, &iltype, &loc);

         std::_tstring strloc( Fl(loc) );
         if (iltype==iflDualLeft)
            strloc += _T("L");
         else if (iltype==iflDualRight)
            strloc += _T("R");
         else
            strloc += _T(" ");

         os<<right<<setw(7)<<ip<<strloc<<Ff(value)<<endl;
      }
 
      // next status of superstructure pois wrt contraflexure zones
      CComPtr<IIDArray> poi_ids;
      CComPtr<IDblArray> poi_locs;
      m_Util->GetSuperstructurePOIs(istg, rsIncremental, &poi_ids, &poi_locs);

      os<<endl;
      os<<_T("  Status of Superstructure POIs WRT Contraflexure Zones - Stage \"")<<W2A(stage)<<_T("\"")<<endl<<endl;
      os<<_T("  POI    Location   In CF Zone?")<<endl;
      os<<_T(" ------ ---------- --------------")<<endl;

      IndexType num_pois;
      hr = poi_ids->get_Count(&num_pois);
      for (IndexType ip=0; ip<num_pois; ip++)
      {
         PoiIDType poi_id;
         hr = poi_ids->get_Item(ip, &poi_id);

         Float64 poi_loc;
         hr = poi_locs->get_Item(ip, &poi_loc);

         InZoneType inzone;
         response->get_IsPOIInContraflexureZone(poi_id, stage, &inzone);

         _tstring striz;
		   if (inzone==izInside)
            striz = _T("Inside");
		   else if (inzone==izOutside)
            striz = _T("Outside");
         else if (inzone==izLeftEdge)
            striz = _T("Left Edge");
         else if (inzone==izRightEdge)
            striz = _T("Right Edge");
         else
            ATLASSERT(0);

         os<<right<<setw(7)<<poi_id<<Fl(poi_loc)<<_T("   ")<<left<<striz<<endl;
      }
   }

   os<<endl;
}
