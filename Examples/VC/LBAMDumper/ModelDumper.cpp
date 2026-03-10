// ModelDumper.cpp: implementation of the CModelDumper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModelDumper.h"

#include "DumperUtils.h"
#include<sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|
//         1         2         3         4         5         6         7         8         9         0     


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace std;

static std::_tstring LoToString(LoadOrientation or)
{
   std::_tstring sor;
   switch (or)
   {
   case loGlobal:
         sor = _T("Global");
         break;   case loMember:
         sor = _T("Member");
         break;
   case loGlobalProjected:
         sor = _T("GloPrj");
         break;
   default:
      ATLASSERT(0);
   }

   return sor;
}

static std::_tstring LctToString(LoadCombinationType lct)
{
   std::_tstring str;
   switch(lct)
   {
   case lctService:
      str = _T("Service");
      break;
   case lctStrength:
      str = _T("Strength");
      break;
   case lctExtremeEvent:
      str = _T("ExtremeEvent");
      break;
   case lctFatigue:
      str = _T("Fatigue");
      break;
   case lctPermit:
      str = _T("Permit");
      break;
   case lctUserDefined:
      str = _T("UserDefined");
      break;
   default:
      ATLASSERT(0);
   }

   return str;
}

static std::_tstring LdToString(LoadDirection dir)
{
   std::_tstring sor;
   switch (dir)
   {
   case ldFx:
      sor = _T("Fx");
      break;
   case ldFy:
      sor = _T("Fy");
      break;
   default:
      ATLASSERT(0);
   }

   return sor;
}


static std::_tstring LltToString (LiveLoadModelType type)
{
   std::_tstring str;
   switch(type)
   {
   case lltNone:
      str=_T("None");
      break;
   case lltDeflection:
      str=_T("Deflection");
      break;
   case lltDesign:
      str=_T("Design");
      break;
   case lltPedestrian:
      str=_T("Pedestrian");
      break;
   case lltFatigue:
      str=_T("Fatigue");
      break;
   case lltPermit:
      str=_T("Permit");
      break;
   case lltSpecial:
      str=_T("Special");
      break;
   case lltLegalRoutineRating:
      str=_T("LegalRoutineRating");
      break;
   case lltLegalSpecialRating:
      str=_T("LegalSpecialRating");
      break;
   case lltPermitRoutineRating:
      str=_T("PermitRoutineRating");
      break;
   case lltLegalEmergencyRating:
      str=_T("LegalEmergencyRating");
      break;
   case lltPermitSpecialRating:
      str = _T("PermitSpecialRating");
      break;
   default:
      ATLASSERT(0);
   }

   return str;
}


static void DumpDistributionFactors(std::_tostream& os, ILBAMModel* model)
{
   CHRException hr;
   USES_CONVERSION;

   os<<_T(" Distribution Factors Along Superstructure")<<endl
     <<_T(" -----------------------------------------")<<endl<<endl;

   CComPtr<ISuperstructureMembers> ssms;
   hr = model->get_SuperstructureMembers(&ssms);
   double ssm_length;
   hr = ssms->get_Length(&ssm_length);
   os<<_T("  Total length of superstructure is ")<<ssm_length<<endl<<endl;
   double oh;
   hr = ssms->get_Offset(&oh);

   CComPtr<IDistributionFactors> dfs;
   hr = model->get_DistributionFactors(&dfs);
   CComPtr<IFilteredDfSegmentCollection> fdfc;
   hr = dfs->GetMemberSegments(ssm_length, &fdfc);

   os<<_T("      Start     End")<<endl;
   os<<_T(" Seg Location Location  gPMSgl   gPMMul   gNMSgl   gNMMul   gVSgl    gVMul    gDSgl    gDMul    gRSgl    gRMul    gTSgl    gTMul     gFatM    gFatV    gPed ")<<endl;
   os<<_T(" --- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- --------")<<endl;

   double start_loc=oh;
   IndexType df_cnt;
   hr = fdfc->get_Count(&df_cnt);
   for (IndexType idf=0; idf<df_cnt; idf++)
   {
      CComPtr<IDistributionFactorSegment> dfseg;
      hr = fdfc->get_Item(idf, &dfseg);
      double length;
      hr = dfseg->get_Length(&length);

      double end_loc = start_loc + length;

      CComPtr<IDistributionFactor> df;
      hr = dfseg->get_DistributionFactor(&df);

      double gPMSgl, gPMMul, gNMSgl, gNMMul, gVSgl, gVMul, gDSgl, gDMul, gRSgl, gRMul, gTSgl, gTMul, gFatM, gFatV, gPed;
      hr = df->GetG(&gPMSgl, &gPMMul, &gNMSgl, &gNMMul, &gVSgl, &gVMul, &gDSgl, &gDMul, &gRSgl, &gRMul, &gTSgl, &gTMul, &gFatM, &gFatV, &gPed);

      os<<setw(4)<<idf<<setw(9)<<start_loc<<setw(9)<<end_loc
        <<setw(9)<<gPMSgl<<setw(9)<<gPMMul<<setw(9)<<gNMSgl<<setw(9)<<gNMMul<<setw(9)<<gVSgl<<setw(9)<<gVMul
        <<setw(9)<<gDSgl<<setw(9)<<gDMul<<setw(9)<<gRSgl<<setw(9)<<gRMul<<setw(9)<<gTSgl<<setw(9)<<gTMul<<setw(9)<<gFatM
        <<setw(9)<<gFatV<<setw(9)<<gPed<<endl;
   }
}

static void DumpStages(std::_tostream& os, ILBAMModel* model)
{
   CHRException hr;
   USES_CONVERSION;

   os<<_T(" Stages in Model")<<endl
     <<_T(" ---------------")<<endl<<endl;

   CComPtr<IStages> stages;
   hr = model->get_Stages(&stages);

   StageIndexType cnt;
   hr = stages->get_Count(&cnt);
   if (cnt>0)
   {
      os<<_T(" No.            Name                                            Description")<<endl
        <<_T(" --- -------------------------------- --------------------------------------------------------------------------------")<<endl;

      for (StageIndexType i=0; i<cnt; i++)
      {
         CComPtr<IStage> stage;
         hr = stages->get_Item(i,&stage);
         CComBSTR name, descr;
         hr = stage->get_Name(&name);
         hr = stage->get_Description(&descr);
         os<<setw(4)<<i<<_T(" ")<<setw(33)<<left<<W2A(name)<<setw(80)<<W2A(descr)<<right<<endl;
      }
   }
   else
   {
      os<<_T(" ERROR No Stages exist in this model")<<endl<<endl;
   }
}

static void DumpLoadGroups(std::_tostream& os, ILBAMModel* model)
{
   CHRException hr;
   USES_CONVERSION;

   os<<_T(" LoadGroups in Model")<<endl
     <<_T(" -------------------")<<endl<<endl;

   CComPtr<ILoadGroups> LoadGroups;
   hr = model->get_LoadGroups(&LoadGroups);

   IndexType cnt;
   hr = LoadGroups->get_Count(&cnt);
   if (cnt>0)
   {
      os<<_T(" No.            Name                  Transient                             Description")<<endl
        <<_T(" --- -------------------------------- --------- --------------------------------------------------------------------------------")<<endl;

      for (IndexType i=0; i<cnt; i++)
      {
         CComPtr<ILoadGroup> LoadGroup;
         hr = LoadGroups->get_Item(i,&LoadGroup);
         CComBSTR name, descr;
         hr = LoadGroup->get_Name(&name);
         hr = LoadGroup->get_Description(&descr);
         VARIANT_BOOL istr;
         hr = LoadGroup->get_Transient(&istr);
         os<<setw(4)<<i<<_T(" ")<<setw(33)<<left<<W2A(name)<<setw(10)<<(istr!=VARIANT_FALSE?_T("True"):_T("False"))<<setw(80)<<W2A(descr)<<right<<endl;
      }
   }
   else
   {
      os<<_T("   No LoadGroups exist in this model")<<endl<<endl;
   }
}

static void DumpLoadCases(std::_tostream& os, ILBAMModel* model)
{
   CHRException hr;
   USES_CONVERSION;

   os<<_T(" LoadCases in Model")<<endl
     <<_T(" -------------------")<<endl<<endl;

   CComPtr<ILoadCases> LoadCases;
   hr = model->get_LoadCases(&LoadCases);

   IndexType cnt;
   hr = LoadCases->get_Count(&cnt);
   if (cnt>0)
   {
      os<<_T(" No.            Name                         LoadGroups                                        Description")<<endl
        <<_T(" --- -------------------------------- -------------------------------- --------------------------------------------------------------------------------")<<endl;

      for (IndexType i=0; i<cnt; i++)
      {
         CComPtr<ILoadCase> LoadCase;
         hr = LoadCases->get_Item(i,&LoadCase);
         CComBSTR name, descr;
         hr = LoadCase->get_Name(&name);
         hr = LoadCase->get_Description(&descr);
         
         IndexType lg_cnt;
         hr = LoadCase->get_LoadGroupCount(&lg_cnt);
         // the first load group
         CComBSTR lg0(_T(" "));
         if (lg_cnt>0)
         {
            hr = LoadCase->GetLoadGroup(0,&lg0);
         }

         os<<right<<setw(4)<<i<<_T(" ")<<setw(33)<<left<<W2A(name)<<setw(33)<<W2A(lg0)<<setw(80)<<W2A(descr)<<right<<endl;

         // the rest of the loadgroups
         for (IndexType ilg=1; ilg<lg_cnt; ilg++)
         {
            CComBSTR lg;
            hr = LoadCase->GetLoadGroup(ilg, &lg);
            os<<left<<setw(38)<<_T(" ")<<setw(40)<<W2A(lg)<<endl;
         }
      }
   }
   else
   {
      os<<_T("   No LoadCases exist in this model")<<endl<<endl;
   }
}


static void DumpLoadCombos(std::_tostream& os, ILBAMModel* model)
{
   CHRException hr;
   USES_CONVERSION;

   os<<_T(" LoadCombinations in Model")<<endl
     <<_T(" -------------------")<<endl<<endl;

   CComPtr<ILoadCombinations> LoadCombinations;
   hr = model->get_LoadCombinations(&LoadCombinations);

   IndexType cnt;
   hr = LoadCombinations->get_Count(&cnt);
   if (cnt>0)
   {
      os<<_T("                                      Combination                                      Min        Max     Live Load   Live Load")<<endl;
      os<<_T(" No.            Name                     Type             LoadCases                   Factor     Factor     Type       Factor                  Description")<<endl
        <<_T(" --- -------------------------------- ------------ -------------------------------- ---------- ---------- ---------- ---------- --------------------------------------------------------------------------------")<<endl;

      for (IndexType i=0; i<cnt; i++)
      {
         CComPtr<ILoadCombination> LoadCombination;
         hr = LoadCombinations->get_Item(i,&LoadCombination);
         CComBSTR name, descr;
         hr = LoadCombination->get_Name(&name);
         hr = LoadCombination->get_Description(&descr);

         LoadCombinationType lct;
         hr = LoadCombination->get_LoadCombinationType(&lct);

         double llf;
         hr = LoadCombination->get_LiveLoadFactor(&llf);
         
         IndexType lc_cnt;
         hr = LoadCombination->get_LoadCaseFactorCount(&lc_cnt);
         // the first load case
         CComBSTR lc0(_T(" "));
         double lc0_min(0), lc0_max(0);
         if (lc_cnt>0)
         {
            hr = LoadCombination->GetLoadCaseFactor(0,&lc0,&lc0_min,&lc0_max);
         }


         IndexType nLiveLoadModels;
         LoadCombination->GetLiveLoadModelCount(&nLiveLoadModels);
         for ( IndexType i = 0; i < nLiveLoadModels; i++ )
         {
            LiveLoadModelType llt;
            hr = LoadCombination->GetLiveLoadModel(i,&llt);

            os<<right<<setw(4)<<i<<_T(" ")<<setw(33)<<left<<W2A(name)<<setw(13)<<LctToString(lct)<<setw(32)<<W2A(lc0)
              <<right<<setw(11)<<lc0_min<<setw(11)<<lc0_max<<_T(" ")<<left<<setw(10)<<LltToString(llt)
              <<right<<setw(11)<<llf<<_T(" ")<<left<<setw(80)<<W2A(descr)<<right<<endl;

            // the rest of the loadcases
            for (IndexType ilc=1; ilc<lc_cnt; ilc++)
            {
               CComBSTR lc;
               double minf, maxf;
               hr = LoadCombination->GetLoadCaseFactor(ilc, &lc, &minf, &maxf);
               os<<left<<setw(51)<<_T(" ")<<setw(32)<<W2A(lc)<<right<<setw(11)<<minf<<setw(11)<<maxf<<endl;
            }

            os<<endl;
         }
      }
   }
   else
   {
      os<<_T("   No LoadCombinations exist in this model")<<endl<<endl;
   }
}




void CModelDumper::DumpSegmentData(std::_tostream& os, IFilteredSegmentCollection* segments)
{
   CHRException hr;

   SegmentIndexType seg_cnt;
   hr = segments->get_Count(&seg_cnt);

   if (seg_cnt>0)
   {
      for (SegmentIndexType i=0; i<seg_cnt; i++)
      {
         CComPtr<ISegment> segment;
         hr = segments->get_Item(i, &segment);
         double length;
         hr = segment->get_Length(&length);
         CComPtr<ISegmentCrossSection> cs;
         hr = segment->get_SegmentCrossSection(&cs);
         double depth;
         hr = cs->get_Depth(&depth);
         double eaf, eif, ead, eid;
         hr = cs->GetStiffness(&eaf, &eif, &ead, &eid);
         double tc;
         hr = cs->get_ThermalCoeff(&tc);
         os<<_T("                                EA         EI         EA         EI        Thermal ")<<endl;
         os<<_T(" Seg   Length       Depth      Force      Force    Deflection Deflection  Coefficient")<<endl;
         os<<_T(" --- ----------- ----------- ---------- ---------- ---------- ----------  ----------")<<endl;
         os<<setw(4)<<i<<Fl(length)<<Fl(depth)<<Ff(eaf)<<Ff(eif)
           <<Ff(ead)<<Ff(eid)<<Ff(tc)<<endl;
      }

      os<<endl;

      // stress points
      for (SegmentIndexType i=0; i<seg_cnt; i++)
      {
         os<<_T(" Stress Points for Segment ")<<i<<endl;
         CComPtr<ISegment> segment;
         hr = segments->get_Item(i, &segment);
         double length;
         hr = segment->get_Length(&length);
         CComPtr<ISegmentCrossSection> cs;
         hr = segment->get_SegmentCrossSection(&cs);
         CComPtr<IStressPoints> sps;
         hr = cs->get_StressPoints(&sps);
         IndexType sps_cnt;
         hr = sps->get_Count(&sps_cnt);
         if (sps_cnt>0)
         {
            os<<_T(" Point     Sa         Sm")<<endl;
            os<<_T(" ----- ---------- ----------")<<endl;
            for (IndexType isp=0; isp<sps_cnt; isp++)
            {
               CComPtr<IStressPoint> sp;
               hr = sps->get_Item(isp, &sp);
               double sa, sm;
               hr = sp->get_Sa(&sa);
               hr = sp->get_Sm(&sm);
               os<<setw(6)<<isp<<Ff(sa)<<Ff(sm)<<endl;
            }
         }
         else
         {
            os<<_T(" There are no stress points for segment ")<<i<<endl;
         }

         os<<endl;
      }
   }
   else
   {
      os<<_T("     No Segments along this member")<<endl;
   }

}

static std::_tstring GetMRTString(ISuperstructureMember* ssm,Side side)
{
   CHRException hr;
   VARIANT_BOOL bIsReleasedNone, bIsReleasedFx, bIsReleasedMz;
   hr = ssm->IsEndReleased(side, mrtNone, &bIsReleasedNone);
   hr = ssm->IsEndReleased(side, mrtFx, &bIsReleasedFx);
   hr = ssm->IsEndReleased(side, mrtMz, &bIsReleasedMz);

   if ( bIsReleasedNone == VARIANT_TRUE )
   {
      return std::_tstring(_T("Cont."));
   }
   else
   {
      if (bIsReleasedFx == VARIANT_TRUE && bIsReleasedMz == VARIANT_FALSE)
      {
         return std::_tstring(_T("Fx"));
      }
      else if (bIsReleasedFx == VARIANT_FALSE && bIsReleasedMz == VARIANT_TRUE)
      {
         return std::_tstring(_T("Mz"));
      }
      else if (bIsReleasedFx == VARIANT_TRUE && bIsReleasedMz == VARIANT_TRUE)
      {
         return std::_tstring(_T("Fx, Mz"));
      }
   }

   ATLASSERT(false);
   return std::_tstring(_T("Error"));
}

void CModelDumper::DumpSSMData(std::_tostream& os, ILBAMModel* model)
{
   USES_CONVERSION;
   CHRException hr;

   os<<endl;
   os<<_T(" SupstructureMember Data")<<endl
     <<_T(" -----------------------")<<endl<<endl;

   CComPtr<ISuperstructureMembers> ssms;
   hr = model->get_SuperstructureMembers(&ssms);

   IndexType ssm_cnt;
   hr = ssms->get_Count(&ssm_cnt);

   if (ssm_cnt>0)
   {
      os<<_T("               <-------------------- End Releases -------------------->")<<endl;
      os<<_T(" SSM  Length    Left     Removal Stage      Right     Removal Stage     Symmetrical")<<endl;
      os<<_T(" --- --------- ------ --------------------  ------ -------------------- ----------- ")<<endl;

      for (IndexType i=0; i<ssm_cnt; i++)
      {
         CComPtr<ISuperstructureMember> ssm;
         hr = ssms->get_Item(i, &ssm);
         double length;
         hr = ssm->get_Length(&length);
         CComBSTR lft_stg, rgt_stg;
         hr = ssm->GetEndReleaseRemovalStage(ssLeft, &lft_stg);
         hr = ssm->GetEndReleaseRemovalStage(ssRight,&rgt_stg);
 
         VARIANT_BOOL symm;
         hr = ssm->get_IsSymmetrical(&symm);

         os <<right<<setw(3)<<i<<Fl(length)<<_T(" ")<<left<<setw(8)<<GetMRTString(ssm,ssLeft)<<setw(21)<<W2A(lft_stg)
            <<setw(7)<<GetMRTString(ssm,ssRight)<<setw(21)<<W2A(rgt_stg)
            <<setw(12)<<(symm!=VARIANT_FALSE?_T("True"):_T("False"))<<endl;
      }

      os<<right<<endl;

      CComPtr<IStages> stages;
      hr = model->get_Stages(&stages);
      StageIndexType stg_cnt;
      hr = stages->get_Count(&stg_cnt);

      // segments
      for (IndexType i=0; i<ssm_cnt; i++)
      {
         os<<_T(" Segment Information for SuperstructureMember ")<<i<<endl;
         os<<_T(" ------------------------------------------------")<<endl;
         CComPtr<ISuperstructureMember> ssm;
         hr = ssms->get_Item(i, &ssm);


         for (StageIndexType is=0; is<stg_cnt; is++)
         {
            CComPtr<IStage> stage;
            hr = stages->get_Item(is, &stage);
            CComBSTR sn;
            hr = stage->get_Name(&sn);
            CComPtr<IFilteredSegmentCollection> segments;
            hr = ssm->GetSegmentsForStage(sn, &segments);
            os <<_T("   Segments in Stage ")<<W2A(sn)<<endl;

            DumpSegmentData(os, segments);
         }

         os<<endl;
      }
   }
   else
   {
      os<<_T(" ERROR No Spans exist in this model")<<endl<<endl;
   }
}


void CModelDumper::DumpPOIData(std::_tostream& os, ILBAMModel* model)
{
   USES_CONVERSION;
   CHRException hr;

   os<<endl;
   os<<_T(" POI Data")<<endl
     <<_T(" --------")<<endl<<endl;

   CComPtr<IPOIs> pois;
   hr = model->get_POIs(&pois);
   IndexType poi_cnt;
   hr = pois->get_Count(&poi_cnt);

   os<<_T("                                                   # of POI          X           Y")<<endl;
   os<<_T("  POI      Member Type       Member ID   Location  Stress Points  Location    Location")<<endl;
   os<<_T(" ----- --------------------- --------- ----------- ------------- ----------- -----------")<<endl;

   for (IndexType ipoi=0; ipoi<poi_cnt; ipoi++)
   {
      CComPtr<IPOI> poi;
      hr = pois->get_Item(ipoi, &poi);

      PoiIDType id;
      hr = poi->get_ID(&id);
      double loc;
      hr = poi->get_Location(&loc);
      MemberIDType mid;
      hr = poi->get_MemberID(&mid);
      MemberType mtype;
      hr = poi->get_MemberType(&mtype);
      CComPtr<IPOIStressPoints> psps;
      hr = poi->get_POIStressPoints(&psps);
      IndexType nsps;
      hr = psps->get_Count(&nsps);

      double xloc, yloc;
      model->ComputeLocation(mid,mtype,loc,&xloc,&yloc);

      os<<setw(6)<<id<<_T(" ")<<left<<setw(21)<<MTToString(mtype)<<right<<setw(10)<<mid<<setw(12)
        <<loc<<setw(14)<<nsps<<Fl(xloc)<<Fl(yloc)<<endl;
   }

   os<<endl;
}

void CModelDumper::DumpPointLoadData(std::_tostream& os, ILBAMModel* model)
{
   USES_CONVERSION;
   CHRException hr;

   os<<endl;
   os<<_T(" Point Load Data")<<endl
     <<_T(" ---------------")<<endl<<endl;

   CComPtr<IPointLoads> pls;
   hr = model->get_PointLoads(&pls);
   IndexType pl_cnt;
   hr = pls->get_Count(&pl_cnt);

   if (pl_cnt>0)
   {
      os<<_T("          Stage                  Load Group          Member Type        Member ID  Location       Fx          Fy           Mz")<<endl;
      os<<_T(" ------------------------ ------------------------ -------------------- --------- ----------- ----------- ----------- -----------")<<endl;

      for (IndexType ip=0; ip<pl_cnt; ip++)
      {
         CComPtr<IPointLoadItem> pli;
         hr = pls->get_Item(ip, &pli);

         CComBSTR stage, loadgroup;
         hr = pli->get_Stage(&stage);
         hr = pli->get_LoadGroup(&loadgroup);

         CComPtr<IPointLoad> pl;
         hr = pli->get_Load(&pl);

         double loc;
         hr = pl->get_Location(&loc);
         MemberIDType mid;
         hr = pl->get_MemberID(&mid);
         MemberType mtype;
         hr = pl->get_MemberType(&mtype);
         double fx, fy, mz;
         hr = pl->GetForce(&fx, &fy, &mz);

         os<<left<<_T(" ")<<setw(25)<<W2A(stage)<<setw(25)<<W2A(loadgroup)<<setw(20)<<MTToString(mtype)<<right<<setw(10)<<mid<<Fl(loc)<<Ff(fx)<<Ff(fy)<<Ff(mz)<<endl;
      }
   }
   else
   {
      os<<_T("   No Point Loads in Model")<<endl;
   }

   os<<endl;
}

static void DumpTemperatureLoadData(std::_tostream& os, ILBAMModel* model)
{
   USES_CONVERSION;
   CHRException hr;

   os<<endl;
   os<<_T(" Temperature Load Data")<<endl
     <<_T(" ---------------------")<<endl<<endl;

   CComPtr<ITemperatureLoads> pls;
   hr = model->get_TemperatureLoads(&pls);
   IndexType pl_cnt;
   hr = pls->get_Count(&pl_cnt);

   if (pl_cnt>0)
   {
      os<<_T("          Stage                  Load Group          Member Type        Member ID    TTop        TBot")<<endl;
      os<<_T(" ------------------------ ------------------------ -------------------- --------- ----------- -----------")<<endl;

      for (IndexType ip=0; ip<pl_cnt; ip++)
      {
         CComPtr<ITemperatureLoadItem> pli;
         hr = pls->get_Item(ip, &pli);

         CComBSTR stage, loadgroup;
         hr = pli->get_Stage(&stage);
         hr = pli->get_LoadGroup(&loadgroup);

         CComPtr<ITemperatureLoad> pl;
         hr = pli->get_Load(&pl);

         MemberIDType mid;
         hr = pl->get_MemberID(&mid);
         MemberType mtype;
         hr = pl->get_MemberType(&mtype);
         double ttop, tbot;
         hr = pl->get_TTop(&ttop);
         hr = pl->get_TBottom(&tbot);

         os<<left<<_T(" ")<<setw(25)<<W2A(stage)<<setw(25)<<W2A(loadgroup)<<setw(20)<<MTToString(mtype)<<right<<setw(10)<<mid
                      <<setw(12)<<ttop<<setw(12)<<tbot<<endl;
      }
   }
   else
   {
      os<<_T("   No Temperature Loads in Model")<<endl;
   }

   os<<endl;
}

static void DumpStrainLoadData(std::_tostream& os, ILBAMModel* model)
{
   USES_CONVERSION;
   CHRException hr;

   os<<endl;
   os<<_T(" Strain Load Data")<<endl
     <<_T(" ---------------------")<<endl<<endl;

   CComPtr<IStrainLoads> pls;
   hr = model->get_StrainLoads(&pls);
   IndexType pl_cnt;
   hr = pls->get_Count(&pl_cnt);

   if (pl_cnt>0)
   {
      os<<_T("          Stage                  Load Group          Member Type        Member ID   Start        End      Axial Strain Curve Strain")<<endl;
      os<<_T(" ------------------------ ------------------------ -------------------- --------- ----------- ----------- ------------ ------------")<<endl;

      for (IndexType ip=0; ip<pl_cnt; ip++)
      {
         CComPtr<IStrainLoadItem> pli;
         hr = pls->get_Item(ip, &pli);

         CComBSTR stage, loadgroup;
         hr = pli->get_Stage(&stage);
         hr = pli->get_LoadGroup(&loadgroup);

         CComPtr<IStrainLoad> pl;
         hr = pli->get_Load(&pl);

         MemberIDType mid;
         hr = pl->get_MemberID(&mid);
         MemberType mtype;
         hr = pl->get_MemberType(&mtype);
         double sloc, eloc;
         hr = pl->get_StartLocation(&sloc);
         hr = pl->get_EndLocation(&eloc);
         double as, cs;
         hr = pl->get_AxialStrain(&as);
         hr = pl->get_CurvatureStrain(&cs);

         os<<left<<_T(" ")<<setw(25)<<W2A(stage)<<setw(25)<<W2A(loadgroup)<<setw(20)<<MTToString(mtype)<<right<<setw(10)<<mid
                      <<setw(12)<<sloc<<setw(12)<<eloc<<setw(13)<<as<<setw(13)<<cs<<endl;
      }
   }
   else
   {
      os<<_T("   No Strain Loads in Model")<<endl;
   }

   os<<endl;
}



static void DumpSettlementLoadData(std::_tostream& os, ILBAMModel* model)
{
   USES_CONVERSION;
   CHRException hr;

   os<<endl;
   os<<_T(" Settlement Load Data")<<endl
     <<_T(" --------------------")<<endl<<endl;

   CComPtr<ISettlementLoads> pls;
   hr = model->get_SettlementLoads(&pls);
   IndexType pl_cnt;
   hr = pls->get_Count(&pl_cnt);

   if (pl_cnt>0)
   {
      os<<_T("          Stage                  Load Group        Supprt ID     Dx          Dy           Rz")<<endl;
      os<<_T(" ------------------------ ------------------------ --------- ----------- ----------- -----------")<<endl;

      for (IndexType ip=0; ip<pl_cnt; ip++)
      {
         CComPtr<ISettlementLoadItem> pli;
         hr = pls->get_Item(ip, &pli);

         CComBSTR stage, loadgroup;
         hr = pli->get_Stage(&stage);
         hr = pli->get_LoadGroup(&loadgroup);

         CComPtr<ISettlementLoad> pl;
         hr = pli->get_Load(&pl);

         MemberIDType mid;
         hr = pl->get_MemberID(&mid);
         double dx, dy, rz;
         hr = pl->get_Dx(&dx);
         hr = pl->get_Dy(&dy);
         hr = pl->get_Rz(&rz);

         os<<left<<_T(" ")<<setw(25)<<W2A(stage)<<setw(24)<<W2A(loadgroup)<<right<<setw(10)<<mid<<setw(12)<<dx<<setw(12)<<dy<<setw(12)<<rz<<endl;
      }
   }
   else
   {
      os<<_T("   No Settlement Loads in Model")<<endl;
   }

   os<<endl;
}


static void DumpDistrLoadData(std::_tostream& os, ILBAMModel* model)
{
   USES_CONVERSION;
   CHRException hr;

   os<<endl;
   os<<_T(" Distributed Load Data")<<endl
     <<_T(" ---------------------")<<endl;

   CComPtr<IDistributedLoads> dls;
   hr = model->get_DistributedLoads(&dls);
   IndexType dl_cnt;
   hr = dls->get_Count(&dl_cnt);

   if (dl_cnt>0)
   {
      os<<_T("                                                                                               Start       End          W            W")<<endl;
      os<<_T("          Stage                  Load Group          Member Type        Member ID Orient Dir  Location    Location     Start        End ")<<endl;
      os<<_T(" ------------------------ ------------------------ -------------------- --------- ------ --- ----------- ----------- ----------- -----------")<<endl;

      for (IndexType id=0; id<dl_cnt; id++)
      {
         CComPtr<IDistributedLoadItem> dli;
         hr = dls->get_Item(id, &dli);

         CComBSTR stage, loadgroup;
         hr = dli->get_Stage(&stage);
         hr = dli->get_LoadGroup(&loadgroup);

         CComPtr<IDistributedLoad> dl;
         hr = dli->get_Load(&dl);

         MemberIDType mid;
         hr = dl->get_MemberID(&mid);
         MemberType mtype;
         hr = dl->get_MemberType(&mtype);
         LoadOrientation or;
         hr = dl->get_Orientation(&or);
         LoadDirection dir;
         hr = dl->get_Direction(&dir);
         double sloc, eloc;
         hr = dl->get_StartLocation(&sloc);
         hr = dl->get_EndLocation(&eloc);
         double wstart, wend;
         hr = dl->get_WStart(&wstart);
         hr = dl->get_WEnd(&wend);

         os<<left<<_T(" ")<<setw(25)<<W2A(stage)<<setw(25)<<W2A(loadgroup)<<setw(20)<<MTToString(mtype)<<setw(8)
           <<right<<setw(10)<<mid<<_T(" ")<<left<<setw(7)<<LoToString(or)<<setw(3)<<LdToString(dir)
           <<right<<setw(12)<<sloc<<setw(12)<<eloc<<setw(12)<<wstart<<setw(12)<<wend<<endl;
      }
   }
   else
   {
      os<<_T("   No Distributed Loads in Model")<<endl;
   }

   os<<endl;
}


void CModelDumper::DumpSupportData(std::_tostream& os, ILBAMModel* model)
{
   USES_CONVERSION;
   CHRException hr;

   os<<endl;
   os<<_T(" Support Data")<<endl
     <<_T(" ------------")<<endl<<endl;

   CComPtr<ISupports> sups;
   hr = model->get_Supports(&sups);

   IndexType sup_cnt;
   hr = sups->get_Count(&sup_cnt);

   if (sup_cnt>0)
   {
      os<<_T("                                                      <---------------------- Load Modifiers ------------------------------>")<<endl;
      os<<_T("                  Bottom   Bottom  Top                 Service    Strength  ExtremeEvent   Fatigue     Permit   UserDefined")<<endl;
      os<<_T(" SUP  Length      Offset     BC   Hinge  Symmetrical  Min   Max   Min   Max   Min   Max   Min   Max   Min   Max   Min   Max")<<endl;
      os<<_T(" --- ---------- ---------- ------ ------ ----------- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----")<<endl;

      for (IndexType i=0; i<sup_cnt; i++)
      {
         CComPtr<ISupport> sup;
         hr = sups->get_Item(i, &sup);
         double length;
         hr = sup->get_Length(&length);
         double offset;
         hr = sup->get_BottomOffset(&offset);
         BoundaryConditionType bc;
         hr = sup->get_BoundaryCondition(&bc);

         std::_tstring sbc;
         switch (bc)
         {
         case bcFixed:
            sbc = _T("Fixed");
            break;
         case bcPinned:
            sbc = _T("Pinned");
            break;
         case bcRoller:
            sbc = _T("Roller");
            break;
         default:
            ATLASSERT(0);
         };

         VARIANT_BOOL toprel;
         hr = sup->get_TopRelease(&toprel);
         VARIANT_BOOL symm;
         hr = sup->get_IsSymmetrical(&symm);

         double svc_min, svc_max;
         hr = sup->GetLoadModifier(lctService , &svc_min, &svc_max);
         double str_min, str_max;
         hr = sup->GetLoadModifier(lctStrength , &str_min, &str_max);
         double exe_min, exe_max;
         hr = sup->GetLoadModifier(lctExtremeEvent , &exe_min, &exe_max);
         double fat_min, fat_max;
         hr = sup->GetLoadModifier(lctFatigue , &fat_min, &fat_max);
         double pmt_min, pmt_max;
         hr = sup->GetLoadModifier(lctPermit , &pmt_min, &pmt_max);
         double usd_min, usd_max;
         hr = sup->GetLoadModifier(lctUserDefined , &usd_min, &usd_max);

         os <<right<<setw(4)<<i<<setw(11)<<length<<setw(11)<<offset<<_T(" ")<<left<<setw(6)<<sbc<<_T(" ")
            <<setw(6)<<(toprel!=VARIANT_FALSE?_T("True"):_T("False"))<<_T(" ")<<setw(11)<<(symm!=VARIANT_FALSE?_T("True"):_T("False"))
            <<right<<setw(6)<<svc_min<<setw(6)<<svc_max<<setw(6)
            <<str_min<<setw(6)<<str_max<<setw(6)<<exe_min<<setw(6)<<exe_max<<setw(6)<<fat_min<<setw(6)<<fat_max
            <<setw(6)<<pmt_min<<setw(6)<<pmt_max<<setw(6)<<usd_min<<setw(6)<<usd_max<<setw(6)<<endl;
      }

      os<<right<<endl;

      CComPtr<IStages> stages;
      hr = model->get_Stages(&stages);
      StageIndexType stg_cnt;
      hr = stages->get_Count(&stg_cnt);

      // segments
      for (IndexType i=0; i<sup_cnt; i++)
      {
         os<<_T(" Segment Information for Support ")<<i<<endl;
         os<<_T(" ------------------------------------")<<endl;
         CComPtr<ISupport> sup;
         hr = sups->get_Item(i, &sup);

         for (StageIndexType is=0; is<stg_cnt; is++)
         {
            CComPtr<IStage> stage;
            hr = stages->get_Item(is, &stage);
            CComBSTR sn;
            hr = stage->get_Name(&sn);
            CComPtr<IFilteredSegmentCollection> segments;
            hr = sup->GetSegmentsForStage(sn, &segments);
            os <<_T("   Segments in Stage ")<<W2A(sn)<<endl;

            DumpSegmentData(os, segments);
         }

         os<<endl;
      }
   }
   else
   {
      os<<_T(" ERROR No Supports exist in this model")<<endl<<endl;
   }

}

void CModelDumper::DumpTempSupportData(std::_tostream& os, ILBAMModel* model)
{
   USES_CONVERSION;
   CHRException hr;

   os<<endl;
   os<<_T(" Temporary Support Data")<<endl
     <<_T(" ----------------------")<<endl<<endl;

   CComPtr<ISpans> spans;
   hr = model->get_Spans(&spans);

   SpanIndexType span_cnt;
   hr = spans->get_Count(&span_cnt);

   if (span_cnt>0)
   {
      os<<_T("                                                                                          <---------------------- Load Modifiers ------------------------------>")<<endl;
      os<<_T("                          Stage                        Bottom   Bottom  Top                 Service    Strength  ExtremeEvent   Fatigue     Permit   UserDefined")<<endl;
      os<<_T("  ID Span  Location      Removed            Length     Offset     BC   Hinge  Symmetrical  Min   Max   Min   Max   Min   Max   Min   Max   Min   Max   Min   Max")<<endl;
      os<<_T(" --- ---- ---------- -------------------- ---------- ---------- ------ ------ ----------- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----")<<endl;

      for (SpanIndexType ispn=0; ispn<span_cnt; ispn++)
      {
         CComPtr<ISpan> span;
         hr = spans->get_Item(ispn, &span);
         CComPtr<ITemporarySupports> tss;
         hr = span->get_TemporarySupports(&tss);
         SupportIndexType ts_cnt;
         hr = tss->get_Count(&ts_cnt);
         for (SupportIndexType i=0; i<ts_cnt; i++)
         {
            CComPtr<ITemporarySupport> sup;
            hr = tss->get_Item(i,&sup);

            SupportIDType id;
            hr = sup->get_ID(&id);
            double location;
            hr = sup->get_Location(&location);
            CComBSTR remstg;
            hr = sup->get_StageRemoved(&remstg);
            double length;
            hr = sup->get_Length(&length);
            double offset;
            hr = sup->get_BottomOffset(&offset);
            BoundaryConditionType bc;
            hr = sup->get_BoundaryCondition(&bc);

            std::_tstring sbc;
            switch (bc)
            {
            case bcFixed:
               sbc = _T("Fixed");
               break;
            case bcPinned:
               sbc = _T("Pinned");
               break;
            case bcRoller:
               sbc = _T("Roller");
               break;
            default:
               ATLASSERT(0);
            };

            VARIANT_BOOL toprel;
            hr = sup->get_TopRelease(&toprel);
            VARIANT_BOOL symm;
            hr = sup->get_IsSymmetrical(&symm);

            double svc_min, svc_max;
            hr = sup->GetLoadModifier(lctService , &svc_min, &svc_max);
            double str_min, str_max;
            hr = sup->GetLoadModifier(lctStrength , &str_min, &str_max);
            double exe_min, exe_max;
            hr = sup->GetLoadModifier(lctExtremeEvent , &exe_min, &exe_max);
            double fat_min, fat_max;
            hr = sup->GetLoadModifier(lctFatigue , &fat_min, &fat_max);
            double pmt_min, pmt_max;
            hr = sup->GetLoadModifier(lctPermit , &pmt_min, &pmt_max);
            double usd_min, usd_max;
            hr = sup->GetLoadModifier(lctUserDefined , &usd_min, &usd_max);

            os <<right<<setw(4)<<id<<setw(5)<<ispn<<setw(11)<<location<<left<<_T(" ")<<setw(20)<<W2A(remstg)<<right<<setw(11)
               <<length<<setw(11)<<offset<<_T(" ")<<left<<setw(6)<<sbc<<_T(" ")
               <<setw(6)<<(toprel!=VARIANT_FALSE?_T("True"):_T("False"))<<_T(" ")<<setw(11)<<(symm!=VARIANT_FALSE?_T("True"):_T("False"))
               <<right<<setw(6)<<svc_min<<setw(6)<<svc_max<<setw(6)
               <<str_min<<setw(6)<<str_max<<setw(6)<<exe_min<<setw(6)<<exe_max<<setw(6)<<fat_min<<setw(6)<<fat_max
               <<setw(6)<<pmt_min<<setw(6)<<pmt_max<<setw(6)<<usd_min<<setw(6)<<usd_max<<setw(6)<<endl;
         }
      }

      os<<right<<endl;

      CComPtr<IStages> stages;
      hr = model->get_Stages(&stages);
      StageIndexType stg_cnt;
      hr = stages->get_Count(&stg_cnt);

      // segments
      for (SpanIndexType ispn=0; ispn<span_cnt; ispn++)
      {
         CComPtr<ISpan> span;
         hr = spans->get_Item(ispn, &span);
         CComPtr<ITemporarySupports> tss;
         hr = span->get_TemporarySupports(&tss);
         SupportIndexType ts_cnt;
         hr = tss->get_Count(&ts_cnt);
         for (SupportIndexType i=0; i<ts_cnt; i++)
         {
            CComPtr<ITemporarySupport> sup;
            hr = tss->get_Item(i,&sup);

            SupportIDType id;
            hr = sup->get_ID(&id);

            os<<_T("  Segment Data for TemporarySupport ")<<id<<endl;

            for (StageIndexType is=0; is<stg_cnt; is++)
            {
               CComPtr<IStage> stage;
               hr = stages->get_Item(is, &stage);
               CComBSTR sn;
               hr = stage->get_Name(&sn);
               CComPtr<IFilteredSegmentCollection> segments;
               hr = sup->GetSegmentsForStage(sn, &segments);
               os <<_T("   Segments in Stage ")<<W2A(sn)<<endl;

               DumpSegmentData(os, segments);
            }
         }

         os<<endl;
      }
   }
}


static void DumpSpanData(std::_tostream& os, ILBAMModel* model)
{
   CHRException hr;

   os<<endl;
   os<<_T(" Span Data")<<endl
     <<_T(" ---------")<<endl<<endl;

   CComPtr<ISpans> spans;
   hr = model->get_Spans(&spans);

   double spans_len;
   hr = spans->get_Length(&spans_len);

   CComPtr<ISuperstructureMembers> ssms;
   hr = model->get_SuperstructureMembers(&ssms);

   double lft_oh, ssms_len;
   hr = ssms->get_Offset(&lft_oh);
   hr = ssms->get_Length(&ssms_len);

   os<<_T(" Left  Overhang: ")<<lft_oh<<endl;
   os<<_T(" Right Overhang: ")<<ssms_len-(spans_len+lft_oh)<<endl;
   os<<_T(" Total Length of superstructure: ")<<ssms_len<<endl<<endl;

   SpanIndexType cnt;
   hr = spans->get_Count(&cnt);
   if (cnt>0)
   {
      os<<_T("                         <---------------------- Load Modifiers ------------------------------>")<<endl
        <<_T("                   # of   Service    Strength  ExtremeEvent   Fatigue     Permit   UserDefined")<<endl
        <<_T(" Span    Length    TS's  Min   Max   Min   Max   Min   Max   Min   Max   Min   Max   Min   Max")<<endl
        <<_T(" ---- ------------ ---- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----")<<endl;

      for (SpanIndexType i=0; i<cnt; i++)
      {
         CComPtr<ISpan> span;
         hr = spans->get_Item(i,&span);
         double length;
         hr = span->get_Length(&length);
         CComPtr<ITemporarySupports> tss;
         hr = span->get_TemporarySupports(&tss);
         SupportIndexType ts_cnt;
         hr = tss->get_Count(&ts_cnt);
         double svc_min, svc_max;
         hr = span->GetLoadModifier(lctService , &svc_min, &svc_max);
         double str_min, str_max;
         hr = span->GetLoadModifier(lctStrength , &str_min, &str_max);
         double exe_min, exe_max;
         hr = span->GetLoadModifier(lctExtremeEvent , &exe_min, &exe_max);
         double fat_min, fat_max;
         hr = span->GetLoadModifier(lctFatigue , &fat_min, &fat_max);
         double pmt_min, pmt_max;
         hr = span->GetLoadModifier(lctPermit , &pmt_min, &pmt_max);
         double usd_min, usd_max;
         hr = span->GetLoadModifier(lctUserDefined , &usd_min, &usd_max);

         os<<setw(5)<<i<<setw(13)<<length<<setw(5)<<ts_cnt<<setw(6)<<svc_min<<setw(6)<<svc_max<<setw(6)
           <<str_min<<setw(6)<<str_max<<setw(6)<<exe_min<<setw(6)<<exe_max<<setw(6)<<fat_min<<setw(6)<<fat_max
           <<setw(6)<<pmt_min<<setw(6)<<pmt_max<<setw(6)<<usd_min<<setw(6)<<usd_max<<setw(6)<<endl;
      }

      os<<endl;
   }
   else
   {
      os<<_T(" ERROR No Spans exist in this model")<<endl<<endl;
   }
}

static void DumpLiveLoadModel(std::_tostream& os, const std::_tstring& name, ILiveLoadModel* model)
{
   USES_CONVERSION;
   CHRException hr;

   DistributionFactorType dftype;
   hr = model->get_DistributionFactorType(&dftype);
   CComBSTR bname;
   hr = model->get_Name(&bname);

   CComPtr<IVehicularLoads> vehlds;
   hr = model->get_VehicularLoads(&vehlds);

   VehicleIndexType vl_cnt;
   hr = vehlds->get_Count(&vl_cnt);
   
   _tostringstream oss;
   oss<<_T(" Data for LiveLoad Model: ")<<name;
   _tstring::size_type len = oss.str().size();
   std::_tstring dashes;
   dashes.assign(_T("-"), len);
   os<<oss.str()<<endl;
   os<<dashes<<endl;

   os<<_T("                                                 # of")<<endl;
   os<<_T(" Internal Name                     DF Type     Veh Loads")<<endl;
   os<<_T(" -------------------------------- ------------ ---------")<<endl;
   os<<_T(" ")<<left<<setw(33)<<W2A(bname)<<setw(13)<<DftToString(dftype)<<right<<setw(10)<<vl_cnt<<endl<<endl;

   for (VehicleIndexType iv=0; iv<vl_cnt; iv++)
   {
      os<<_T("   Vehicular Load ")<<iv<<endl;
      os<<_T("   ------------------")<<endl<<endl;
      CComPtr<IVehicularLoad> vehld;
      hr = vehlds->get_Item(iv,&vehld);

      CComBSTR vnam;
      hr = vehld->get_Name(&vnam);

      LiveLoadApplicabilityType llappl;
      hr = vehld->get_Applicability(&llappl);
      std::_tstring strappl;
      if (llappl==llaEntireStructure)
      {
         strappl = _T("Entire Super");
      }
      else if (llappl==llaContraflexure)
      {
         strappl = _T("Contraflexure");
      }
      else
      {
         ATLASSERT(0);
      }

      VehicularLoadConfigurationType conft;
      hr = vehld->get_Configuration(&conft);

      double imlane, imtruck;
      hr = vehld->get_IMLane(&imlane);
      hr = vehld->get_IMTruck(&imtruck);

      double lanefct, truckfct;
      hr = vehld->get_LaneFactor(&lanefct);
      hr = vehld->get_TruckFactor(&truckfct);

      double laneld, sidewld;
      hr = vehld->get_LaneLoad(&laneld);
      hr = vehld->get_SidewalkLoad(&sidewld);

      AxleIndexType varaxl;
      hr = vehld->get_VariableAxle(&varaxl);

      VARIANT_BOOL usenot;
      hr = vehld->get_UseNotional(&usenot);

      double maxvar;
      hr = vehld->get_VariableMaxSpacing(&maxvar);

      os<<_T(" Vehicular Live Load                          Vehicular Load      Truck       Lane      Truck       Lane      Lane     Sidewalk      Is       Variable   Max Var.")<<endl;
      os<<_T("       Name              Applicability         Configuration      Factor     Factor     Impact     Impact     Load       Load      Notional     Axle     Spacing")<<endl;
      os<<_T(" -------------------- --------------------- -------------------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------")<<endl;
      os<<_T(" ")<<left<<setw(21)<<W2A(vnam)<<setw(22)<<strappl<<setw(20)<<VlcToString(conft)<<right
        <<setw(11)<<truckfct<<setw(11)<<lanefct<<setw(11)<<imtruck<<setw(11)<<imlane
        <<setw(11)<<laneld<<setw(11)<<sidewld<<setw(11)<<(usenot!=VARIANT_FALSE?_T("True"):_T("False"))<<setw(11)<<varaxl<<setw(11)<<maxvar<<endl<<endl;

      CComPtr<IAxles> axles;
      hr = vehld->get_Axles(&axles);
      AxleIndexType axl_cnt;
      hr = axles->get_Count(&axl_cnt);
      os<<_T("    The number of Axles for this VehicularLoad is ")<<axl_cnt<<endl<<endl;
      if (axl_cnt>0)
      {
         os<<_T("     Axle   Weight    Spacing")<<endl;
         os<<_T("     ---- ---------- ----------")<<endl;
         for (AxleIndexType ia=0; ia<axl_cnt; ia++)
         {
            CComPtr<IAxle> axl;
            hr = axles->get_Item(ia,&axl);
            double weight, spacing;
            hr = axl->get_Weight(&weight);
            hr = axl->get_Spacing(&spacing);
            os<<setw(9)<<ia<<setw(11)<<weight<<setw(11)<<spacing<<endl;
         }
      }
      os<<endl;
   }
   os<<endl;
}

static void DumpLiveLoad(std::_tostream& os, ILBAMModel* model)
{
   CHRException hr;

   CComPtr<ILiveLoad> liveload;
   hr = model->get_LiveLoad(&liveload);

   CComPtr<ILiveLoadModel> ped, spec, perm, fat, defl, desgn;

	hr = liveload->get_Deflection(&defl);
   DumpLiveLoadModel(os, _T("Deflection"), defl);

	hr = liveload->get_Design(&desgn);
   DumpLiveLoadModel(os, _T("Design"), desgn);

	hr = liveload->get_Fatigue(&fat);
   DumpLiveLoadModel(os, _T("Fatigue"), fat);

	hr =liveload->get_Pedestrian(&ped);
   DumpLiveLoadModel(os, _T("Pedestrian"), ped);

	hr = liveload->get_Permit(&perm);
   DumpLiveLoadModel(os, _T("Permit"), perm);

	hr = liveload->get_Special(&spec);
   DumpLiveLoadModel(os, _T("Special"), spec);
}


CModelDumper::CModelDumper(CDumperUtil* util):
m_Util(util)
{

}

CModelDumper::~CModelDumper()
{

}

void CModelDumper::DumpModel(std::_tostream& os, ILBAMModel* model)
{

   os<<_T(" MODEL GEOMETRY AND PROPERTIES")<<endl
     <<_T(" =============================")<<endl<<endl;

   DumpStages(os, model);
   DumpSpanData( os, model);
   DumpSSMData( os, model);
   DumpSupportData( os, model);
   DumpTempSupportData( os, model);
   DumpPOIData( os, model);
   DumpDistributionFactors( os, model);

   os<<endl;
   os<<_T(" LOAD GROUPS AND APPLIED LOADS")<<endl
     <<_T(" =============================")<<endl<<endl;

   DumpLoadGroups(os, model);
   DumpPointLoadData(os, model);
   DumpDistrLoadData(os, model);
   DumpTemperatureLoadData(os, model);
   DumpStrainLoadData(os, model);
   DumpSettlementLoadData(os, model);

   os<<endl;
   os<<_T(" LIVE LOADS")<<endl
     <<_T(" ==========")<<endl<<endl;

   DumpLiveLoad(os, model);

   os<<endl;
   os<<_T(" LOAD COMBINATIONS")<<endl
     <<_T(" =================")<<endl<<endl;

   DumpLoadCases(os, model);
   DumpLoadCombos(os, model);

}
