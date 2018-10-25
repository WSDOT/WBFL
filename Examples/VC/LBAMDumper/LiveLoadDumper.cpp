// LiveLoadDumper.cpp: implementation of the CLiveLoadDumper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LiveLoadDumper.h"

#include "WBFLTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CLiveLoadDumper::CLiveLoadDumper(ILBAMAnalysisEngine* engine, CDumperUtil* util):
m_Engine(engine),
m_Util(util),
m_LastKey(1000000)
{
   CHRException hr;
   try
   {
      // live load results are reported for last stage only
      m_StageId = m_Util->StageCount()-1;
      m_Util->StageName(m_StageId, &m_Stage);

      hr = engine->get_EnvelopedVehicularResponse(&m_EVR);
      hr = engine->get_BasicVehicularResponse(&m_BVR);
      hr = engine->get_LiveLoadModelResponse(&m_LLM);

      // initialize our parameter stacks
      m_LlmParams.Init();
      m_EvrParams.Init();
   }
   catch(...)
   {
      ATLASSERT(0); // we are in a bad state here. future use of the dumper will cause access violations
   }
}

CLiveLoadDumper::~CLiveLoadDumper()
{
}

void CLiveLoadDumper::DumpEnvelopedVehicularResponse(std::_tostream& os, std::_tostream& cos)
{
   CHRException hr;
   USES_CONVERSION;

// NOTE: A brief note here - There are about a trillion diffent options when computing force responses
//       via the IEnvelopedVehicularResponse interface. We could exhaust ourselves (and our cpu) trying 
//       to exercise each possible option. Hence, this routine will only dump the most likely options 
//       used to compute vehicular responses.

   os<<endl<<endl;
   os<<" DUMP OF ENVELOPED VEHICULAR RESPONSES"<<endl;
   os<<" ====================================="<<endl;
   os<<" (Results Reported For Last Stage Only)"<<endl;
   os<<"  Integer keys in the form \"K1000000\" may be used to look up detailed and concurrent results for a given value"<<endl<<endl;

   // need to loop over all possible vehicular loads in the model
   CComPtr<ILBAMModel> model;
   hr = m_Engine->get_Model(&model);

   CComPtr<ILiveLoad> liveload;
   hr = model->get_LiveLoad(&liveload);

   CComPtr<ILiveLoadModel> llm_deflection, llm_design, llm_pedestrian, llm_fatigue, llm_permit, llm_special;
   hr = liveload->get_Deflection(&llm_deflection);
   hr = liveload->get_Design(&llm_design);
   hr = liveload->get_Pedestrian(&llm_pedestrian);
   hr = liveload->get_Fatigue(&llm_fatigue);
   hr = liveload->get_Permit(&llm_permit);
   hr = liveload->get_Special(&llm_special);

   // Envelopes for each live load type
   DumpLlmForces(os, cos, lltDeflection, llm_deflection, "Deflection");
   DumpLlmForces(os, cos, lltDesign, llm_design, "Design");
   DumpLlmForces(os, cos, lltPedestrian, llm_pedestrian, "Pedestrian");
   DumpLlmForces(os, cos, lltFatigue, llm_fatigue, "Fatigue");
   DumpLlmForces(os, cos, lltPermit, llm_permit, "Permit");
   DumpLlmForces(os, cos, lltSpecial, llm_special, "Special");

   // deflections 
   DumpLlmDeflections(os, cos, lltDeflection, llm_deflection, "Deflection");
   DumpLlmDeflections(os, cos, lltDesign, llm_design, "Design");
   DumpLlmDeflections(os, cos, lltPedestrian, llm_pedestrian, "Pedestrian");
   DumpLlmDeflections(os, cos, lltFatigue, llm_fatigue, "Fatigue");
   DumpLlmDeflections(os, cos, lltPermit, llm_permit, "Permit");
   DumpLlmDeflections(os, cos, lltSpecial, llm_special, "Special");

   // Stresses 
   DumpLlmStresses(os, cos, lltDeflection, llm_deflection, "Deflection");
   DumpLlmStresses(os, cos, lltDesign, llm_design, "Design");
   DumpLlmStresses(os, cos, lltPedestrian, llm_pedestrian, "Pedestrian");
   DumpLlmStresses(os, cos, lltFatigue, llm_fatigue, "Fatigue");
   DumpLlmStresses(os, cos, lltPermit, llm_permit, "Permit");
   DumpLlmStresses(os, cos, lltSpecial, llm_special, "Special");

   // Reactions 
   DumpLlmReactions(os, cos, lltDeflection, llm_deflection, "Deflection");
   DumpLlmReactions(os, cos, lltDesign, llm_design, "Design");
   DumpLlmReactions(os, cos, lltPedestrian, llm_pedestrian, "Pedestrian");
   DumpLlmReactions(os, cos, lltFatigue, llm_fatigue, "Fatigue");
   DumpLlmReactions(os, cos, lltPermit, llm_permit, "Permit");
   DumpLlmReactions(os, cos, lltSpecial, llm_special, "Special");

   // SupportDeflections 
   DumpLlmSupportDeflections(os, cos, lltDeflection, llm_deflection, "Deflection");
   DumpLlmSupportDeflections(os, cos, lltDesign, llm_design, "Design");
   DumpLlmSupportDeflections(os, cos, lltPedestrian, llm_pedestrian, "Pedestrian");
   DumpLlmSupportDeflections(os, cos, lltFatigue, llm_fatigue, "Fatigue");
   DumpLlmSupportDeflections(os, cos, lltPermit, llm_permit, "Permit");
   DumpLlmSupportDeflections(os, cos, lltSpecial, llm_special, "Special");

 
   // Enveloped responses for each vehicular load
   // dump forces first
   DumpEvrForces(os, cos, lltDeflection, llm_deflection, "Deflection");
   DumpEvrForces(os, cos, lltDesign, llm_design, "Design");
   DumpEvrForces(os, cos, lltPedestrian, llm_pedestrian, "Pedestrian");
   DumpEvrForces(os, cos, lltFatigue, llm_fatigue, "Fatigue");
   DumpEvrForces(os, cos, lltPermit, llm_permit, "Permit");
   DumpEvrForces(os, cos, lltSpecial, llm_special, "Special");

   // deflections 
   DumpEvrDeflections(os, cos, lltDeflection, llm_deflection, "Deflection");
   DumpEvrDeflections(os, cos, lltDesign, llm_design, "Design");
   DumpEvrDeflections(os, cos, lltPedestrian, llm_pedestrian, "Pedestrian");
   DumpEvrDeflections(os, cos, lltFatigue, llm_fatigue, "Fatigue");
   DumpEvrDeflections(os, cos, lltPermit, llm_permit, "Permit");
   DumpEvrDeflections(os, cos, lltSpecial, llm_special, "Special");

   // Stresses 
   DumpEvrStresses(os, cos, lltDeflection, llm_deflection, "Deflection");
   DumpEvrStresses(os, cos, lltDesign, llm_design, "Design");
   DumpEvrStresses(os, cos, lltPedestrian, llm_pedestrian, "Pedestrian");
   DumpEvrStresses(os, cos, lltFatigue, llm_fatigue, "Fatigue");
   DumpEvrStresses(os, cos, lltPermit, llm_permit, "Permit");
   DumpEvrStresses(os, cos, lltSpecial, llm_special, "Special");

   // Reactions 
   DumpEvrReactions(os, cos, lltDeflection, llm_deflection, "Deflection");
   DumpEvrReactions(os, cos, lltDesign, llm_design, "Design");
   DumpEvrReactions(os, cos, lltPedestrian, llm_pedestrian, "Pedestrian");
   DumpEvrReactions(os, cos, lltFatigue, llm_fatigue, "Fatigue");
   DumpEvrReactions(os, cos, lltPermit, llm_permit, "Permit");
   DumpEvrReactions(os, cos, lltSpecial, llm_special, "Special");

   // SupportDeflections 
   DumpEvrSupportDeflections(os, cos, lltDeflection, llm_deflection, "Deflection");
   DumpEvrSupportDeflections(os, cos, lltDesign, llm_design, "Design");
   DumpEvrSupportDeflections(os, cos, lltPedestrian, llm_pedestrian, "Pedestrian");
   DumpEvrSupportDeflections(os, cos, lltFatigue, llm_fatigue, "Fatigue");
   DumpEvrSupportDeflections(os, cos, lltPermit, llm_permit, "Permit");
   DumpEvrSupportDeflections(os, cos, lltSpecial, llm_special, "Special");
}

void CLiveLoadDumper::DumpLlmForces(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName)
{
   CHRException hr;
   USES_CONVERSION;

   // no need to do anything if we have no vehicular loads
   CComPtr<IVehicularLoads> vloads;
   hr = llModel->get_VehicularLoads(&vloads);

   CollectionIndexType vl_cnt;
   hr = vloads->get_Count(&vl_cnt);

   if (vl_cnt==0)
      return;

   // get all pois
   CComPtr<IIDArray> poi_ids;
   m_Util->GetAllPOIs(m_StageId, rsCumulative, &poi_ids);

   // use a parameter stack instead of writing nested loops over force effects
   for (CLlmParameterStack::iterator piter=m_LlmParams.begin(); piter!=m_LlmParams.end(); piter++)
   {
      const CLlmParameterStack::LlParams& params = *piter;

      os<<endl;
      os<<_T("   Summary Force Responses for ") << params.AsString(true)<<endl;
      os<<"    For Enveloped for LiveLoadModel \""<<llName<<"\""<<endl;
      os<<"    ----------------------------------------------------------------------------------------"<<endl;

      // save first results key so we can write out concurrent results below
      long start_key = m_LastKey;
      CComPtr<ILiveLoadModelSectionResults> llsresults;
      hr = m_LLM->ComputeForces(poi_ids, m_Stage, llmType, roMember, params.ForceEffect, params.Optimization,
					    	           vlcDefault, params.DoApplyImpact, params.DoApplyDistf, VARIANT_TRUE, &llsresults);

      os<<"        <------ Left -----> <----- Right ----->"<<endl;
      os<<"   POI    Result      Key     Result      Key"<<endl;
      os<<" ------ ---------- -------- ---------- --------"<<endl;

      CollectionIndexType res_cnt;
      hr = llsresults->get_Count(&res_cnt);
      for (CollectionIndexType ires=0; ires<res_cnt; ires++)
      {
         PoiIDType poi_id;
         hr = poi_ids->get_Item(ires, &poi_id);

         Float64 left_res, right_res;
         CComPtr<ILiveLoadConfiguration> left_config, right_config;
         hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

         long left_key = m_LastKey++;
         long right_key = m_LastKey++;

         os<<right<<setw(7)<<poi_id<<Ff(left_res)<<" K"<<setw(6)<<left_key<<Ff(right_res)<<" K"<<setw(6)<<right_key<<endl;
      }

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

            Float64 left_res, right_res;
            CComPtr<ILiveLoadConfiguration> left_config, right_config;
            hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

            cos<<endl;
            cos<<"    Concurrent, Detailed, Force Responses for " << params.AsString(true)<<endl;
            cos<<"    For Envelope for LiveLoadModel \""<<llName<<"\""<<endl;
            cos<<"    At POI "<<poi_id<<" Left Side. Key is K"<<left_key<<endl;
            cos<<"    ----------------------------------------------------------------------------------------"<<endl;

            CComPtr<ISectionResult3Ds> left_res3ds;
            hr = m_BVR->ComputeForces(one_poi, m_Stage, roMember, left_config, &left_res3ds);

            CComPtr<ISectionResult3D> left_res3d;
            hr = left_res3ds->get_Item(0,&left_res3d);
            Float64 lfx,lfy,lmz,rfx,rfy,rmz;
            hr = left_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

            cos<<"  Optimized <-------- Conc Left -----------> <------- Conc Right ----------->"<<endl;
            cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
            cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
            cos<<Ff(left_res)<<Ff(lfx)<<Ff(lfy)<<Ff(lmz)<<Ff(rfx)<<Ff(rfy)<<Ff(rmz)<<endl<<endl;

            AxleIndexType axle_cnt = GetAxleCnt(vloads, left_config);
            DumpLiveLoadConfiguration(cos, left_config, axle_cnt, m_Util);

            cos<<endl;
            cos<<"    Concurrent, Detailed, Force Responses for " << params.AsString(true)<<endl;
            cos<<"    For Envelope for LiveLoadModel \""<<llName<<"\""<<endl;
            cos<<"    At POI "<<poi_id<<" Right Side. Key is K"<<right_key<<endl;
            cos<<"    ----------------------------------------------------------------------------------------"<<endl;

            CComPtr<ISectionResult3Ds> right_res3ds;
            hr = m_BVR->ComputeForces(one_poi, m_Stage, roMember, right_config, &right_res3ds);

            CComPtr<ISectionResult3D> right_res3d;
            hr = right_res3ds->get_Item(0,&right_res3d);
            hr = right_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

            cos<<"  Optimized <-------- Conc Right -----------> <------- Conc Right ----------->"<<endl;
            cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
            cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
            cos<<Ff(right_res)<<Ff(lfx)<<Ff(lfy)<<Ff(lmz)<<Ff(rfx)<<Ff(rfy)<<Ff(rmz)<<endl<<endl;

            axle_cnt = GetAxleCnt(vloads, right_config);
            DumpLiveLoadConfiguration(cos, right_config, axle_cnt, m_Util);
         }
      }
   }
}

void CLiveLoadDumper::DumpLlmDeflections(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName)
{
   CHRException hr;
   USES_CONVERSION;

   // no need to do anything if we have no vehicular loads
   CComPtr<IVehicularLoads> vloads;
   hr = llModel->get_VehicularLoads(&vloads);

   VehicleIndexType vl_cnt;
   hr = vloads->get_Count(&vl_cnt);

   if (vl_cnt==0)
      return;

   // get all pois
   CComPtr<IIDArray> poi_ids;
   m_Util->GetAllPOIs(m_StageId, rsCumulative, &poi_ids);

   // use a parameter stack instead of writing nested loops over force effects
   for (CLlmParameterStack::iterator piter=m_LlmParams.begin(); piter!=m_LlmParams.end(); piter++)
   {
      const CLlmParameterStack::LlParams& params = *piter;

      os<<endl;
      os<<"    Summary Deflection Responses for " << params.AsString(true)<<endl;
      os<<"    For Envelope of LiveLoadModel \""<<llName<<"\""<<endl;
      os<<"    ----------------------------------------------------------------------------------------"<<endl;

      // save first results key so we can write out concurrent results below
      long start_key = m_LastKey;
      CComPtr<ILiveLoadModelSectionResults> llsresults;
      hr = m_LLM->ComputeDeflections(poi_ids, m_Stage, llmType, params.ForceEffect, params.Optimization,
					    	                vlcDefault, params.DoApplyImpact, params.DoApplyDistf, VARIANT_TRUE, &llsresults);

      os<<"        <------ Left -----> <----- Right ----->"<<endl;
      os<<"   POI    Result      Key     Result      Key"<<endl;
      os<<" ------ ---------- -------- ---------- --------"<<endl;

      CollectionIndexType res_cnt;
      hr = llsresults->get_Count(&res_cnt);
      for (CollectionIndexType ires=0; ires<res_cnt; ires++)
      {
         PoiIDType poi_id;
         hr = poi_ids->get_Item(ires, &poi_id);

         Float64 left_res, right_res;
         CComPtr<ILiveLoadConfiguration> left_config, right_config;
         hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

         long left_key = m_LastKey++;
         long right_key = m_LastKey++;

         os<<right<<setw(7)<<poi_id<<Fd(left_res)<<" K"<<setw(6)<<left_key<<Fd(right_res)<<" K"<<setw(6)<<right_key<<endl;
      }

      os<<" "<<endl;

      if (m_Util->DoDetails())
      {
         long curr_key = start_key;

         CComPtr<IIDArray> one_poi;
         hr = one_poi.CoCreateInstance(CLSID_LongArray);
         hr = one_poi->Add(-1);

         for (CollectionIndexType ires=0; ires<res_cnt; ires++)
         {
            IDType poi_id;
            hr = poi_ids->get_Item(ires, &poi_id);

            hr = one_poi->put_Item(0, poi_id);

            long left_key  = curr_key++;
            long right_key = curr_key++;

            Float64 left_res, right_res;
            CComPtr<ILiveLoadConfiguration> left_config, right_config;
            hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

            cos<<endl;
            cos<<"    Concurrent, Detailed, Deflection Responses for " << params.AsString(false)<<endl;
            cos<<"    For Envelope for LiveLoadModel \""<<llName<<"\""<<endl;
            cos<<"    At POI "<<poi_id<<" Left Side. Key is K"<<left_key<<endl;
            cos<<"    ----------------------------------------------------------------------------------------"<<endl;

            CComPtr<ISectionResult3Ds> left_res3ds;
            hr = m_BVR->ComputeDeflections(one_poi, m_Stage, left_config, &left_res3ds);

            CComPtr<ISectionResult3D> left_res3d;
            hr = left_res3ds->get_Item(0,&left_res3d);
            Float64 lfx,lfy,lmz,rfx,rfy,rmz;
            hr = left_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

            cos<<"  Optimized <-------- Conc Left -----------> <------- Conc Right ----------->"<<endl;
            cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
            cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
            cos<<Fd(left_res)<<Fd(lfx)<<Fd(lfy)<<Fd(lmz)<<Fd(rfx)<<Fd(rfy)<<Fd(rmz)<<endl<<endl;

            AxleIndexType axle_cnt = GetAxleCnt(vloads, left_config);
            DumpLiveLoadConfiguration(cos, left_config, axle_cnt, m_Util);

            cos<<endl;
            cos<<"    Concurrent, Detailed, Deflection Responses for " << params.AsString(false)<<endl;
            cos<<"    For Envelope for LiveLoadModel \""<<llName<<"\""<<endl;
            cos<<"    At POI "<<poi_id<<" Right Side. Key is K"<<right_key<<endl;
            cos<<"    ----------------------------------------------------------------------------------------"<<endl;

            CComPtr<ISectionResult3Ds> right_res3ds;
            hr = m_BVR->ComputeDeflections(one_poi, m_Stage, right_config, &right_res3ds);

            CComPtr<ISectionResult3D> right_res3d;
            hr = right_res3ds->get_Item(0,&right_res3d);
            hr = right_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

            cos<<"  Optimized <-------- Conc Right -----------> <------- Conc Right ----------->"<<endl;
            cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
            cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
            cos<<Fd(right_res)<<Fd(lfx)<<Fd(lfy)<<Fd(lmz)<<Fd(rfx)<<Fd(rfy)<<Fd(rmz)<<endl<<endl;

            axle_cnt = GetAxleCnt(vloads, right_config);
            DumpLiveLoadConfiguration(cos, right_config, axle_cnt, m_Util);
            cos<<endl;
         }
      }
   }
}

void CLiveLoadDumper::DumpLlmStresses(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName)
{
   CHRException hr;
   USES_CONVERSION;

   CComPtr<IVehicularLoads> vloads;
   hr = llModel->get_VehicularLoads(&vloads);

   VehicleIndexType vl_cnt;
   hr = vloads->get_Count(&vl_cnt);

   if (vl_cnt==0)
      return;

   // get all pois
   CComPtr<IIDArray> poi_ids;
   m_Util->GetAllPOIs(m_StageId, rsCumulative, &poi_ids);

   // use a parameter stack instead of writing nested loops over force effects
   for (CLlmParameterStack::iterator piter=m_LlmParams.begin(); piter!=m_LlmParams.end(); piter++)
   {
      const CLlmParameterStack::LlParams& params = *piter;

      os<<endl;
      os<<"   Summary Stress Responses for " << params.AsString(true)<<endl;
      os<<"    For Envelope for LiveLoadModel \""<<llName<<"\""<<endl;
      os<<"    ----------------------------------------------------------------------------------------"<<endl;

      // save first results key so we can write out concurrent results below
      long start_key = m_LastKey;
      CComPtr<ILiveLoadModelStressResults> llsresults;
      hr = m_LLM->ComputeStresses(poi_ids, m_Stage, llmType, params.ForceEffect, params.Optimization,
					    	             vlcDefault, params.DoApplyImpact, params.DoApplyDistf, VARIANT_TRUE, &llsresults);

      os<<"        <----------------- Left ---------------------------> <-------------------------- Right -------------------->"<<endl;
      os<<"   POI     SP0        SP1         SP2        SP3      Key       SP0        SP1        SP2        SP3       Key"<<endl;
      os<<" ------ ---------- ---------- ---------- ---------- -------- ---------- ---------- ---------- ---------- --------"<<endl;

      CollectionIndexType res_cnt;
      hr = llsresults->get_Count(&res_cnt);
      for (CollectionIndexType ires=0; ires<res_cnt; ires++)
      {
         PoiIDType poi_id;
         hr = poi_ids->get_Item(ires, &poi_id);

         CComPtr<IStressResult> left_res, right_res;
         CComPtr<ILiveLoadConfiguration> left_config, right_config;
         hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

         std::_tstring rgt_sp0, rgt_sp1, rgt_sp2, rgt_sp3;
         std::_tstring lft_sp0, lft_sp1, lft_sp2, lft_sp3;

         CollectionIndexType cnt;
         Float64 val;
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

      if (m_Util->DoDetails())
      {
         long curr_key = start_key;

         CComPtr<IIDArray> one_poi;
         hr = one_poi.CoCreateInstance(CLSID_LongArray);
         hr = one_poi->Add(-1);

         for (CollectionIndexType ires=0; ires<res_cnt; ires++)
         {
            IDType poi_id;
            hr = poi_ids->get_Item(ires, &poi_id);

            hr = one_poi->put_Item(0, poi_id);

            long left_key  = curr_key++;
            long right_key = curr_key++;

            CComPtr<IStressResult> left_res, right_res;
            CComPtr<ILiveLoadConfiguration> left_config, right_config;
            hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

            cos<<"    Detailed Configuration for Stress Responses for " << params.AsString(true)<<endl;
            cos<<"    For Envelope for LiveLoadModel \""<<llName<<"\""<<endl;
            cos<<"    At POI "<<poi_id<<" Left Side. Key is K"<<left_key<<endl;
            cos<<"    ----------------------------------------------------------------------------------------"<<endl;

            AxleIndexType axle_cnt = GetAxleCnt(vloads, left_config);
            DumpLiveLoadConfiguration(cos, left_config, axle_cnt, m_Util);

            cos<<endl;
            cos<<"    Detailed Configuration for Stress Responses for " << params.AsString(true)<<endl;
            cos<<"    For Envelope for LiveLoadModel \"\""<<endl;
            cos<<"    At POI "<<poi_id<<" Right Side. Key is K"<<right_key<<endl;
            cos<<"    ----------------------------------------------------------------------------------------"<<endl;

            axle_cnt = GetAxleCnt(vloads, right_config);
            DumpLiveLoadConfiguration(cos, right_config, axle_cnt, m_Util);
            cos<<endl;
         }
      }
   }
}

void CLiveLoadDumper::DumpLlmReactions(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName)
{
   CHRException hr;
   USES_CONVERSION;

   CComPtr<IVehicularLoads> vloads;
   hr = llModel->get_VehicularLoads(&vloads);

   VehicleIndexType vl_cnt;
   hr = vloads->get_Count(&vl_cnt);

   if (vl_cnt==0)
      return;

   // get all supports
   CComPtr<IIDArray> spt_ids;
   m_Util->GetSupportIDs(m_StageId, &spt_ids);

   // use a parameter stack instead of writing nested loops over force effects
   for (CLlmParameterStack::iterator piter=m_LlmParams.begin(); piter!=m_LlmParams.end(); piter++)
   {
      const CLlmParameterStack::LlParams& params = *piter;

      os<<endl;
      os<<"   Summary Reaction Responses for " << params.AsString(true)<<endl;
      os<<"    For Envelope for LiveLoadModel \""<<llName<<"\""<<endl;
      os<<"    ----------------------------------------------------------------------------------------"<<endl;

      // save first results key so we can write out concurrent results below
      long start_key = m_LastKey;
      CComPtr<ILiveLoadModelResults> llsresults;
      hr = m_LLM->ComputeReactions(spt_ids, m_Stage, llmType, params.ForceEffect, params.Optimization,
					    	              vlcDefault, params.DoApplyImpact, params.DoApplyDistf, VARIANT_TRUE, &llsresults);

      os<<"   Spt"<<endl;
      os<<"   ID      Result      Key"<<endl;
      os<<" ------ ---------- --------"<<endl;

      CollectionIndexType res_cnt;
      hr = llsresults->get_Count(&res_cnt);
      for (CollectionIndexType ires=0; ires<res_cnt; ires++)
      {
         IDType spt_id;
         hr = spt_ids->get_Item(ires, &spt_id);

         Float64 res;
         CComPtr<ILiveLoadConfiguration> config;
         hr = llsresults->GetResult(ires, &res, &config);

         long key = m_LastKey++;

         os<<right<<setw(7)<<spt_id<<Fd(res)<<" K"<<setw(6)<<key<<endl;
      }

      os<<" "<<endl;

      if (m_Util->DoDetails())
      {

         long curr_key = start_key;

         CComPtr<IIDArray> one_spt;
         hr = one_spt.CoCreateInstance(CLSID_LongArray);
         hr = one_spt->Add(-1);

         for (CollectionIndexType ires=0; ires<res_cnt; ires++)
         {
            IDType spt_id;
            hr = spt_ids->get_Item(ires, &spt_id);

            hr = one_spt->put_Item(0, spt_id);

            long key  = curr_key++;

            Float64 res;
            CComPtr<ILiveLoadConfiguration> config;
            hr = llsresults->GetResult(ires, &res, &config);

            cos<<endl;
            cos<<"    Concurrent, Detailed, Reaction Responses for " << params.AsString(true)<<endl;
            cos<<"    For Envelope for LiveLoadModel \""<<llName<<"\""<<endl;
            cos<<"    At Support "<<spt_id<<".  Key is K"<<key<<endl;
            cos<<"    ----------------------------------------------------------------------------------------"<<endl;

            CComPtr<IResult3Ds> res3ds;
            hr = m_BVR->ComputeReactions(one_spt, m_Stage, config, &res3ds);

            CComPtr<IResult3D> res3d;
            hr = res3ds->get_Item(0,&res3d);
            Float64 fx,fy,mz;
            hr = res3d->GetResult(&fx,&fy,&mz);

            cos<<"  Optimized <------Concurrent Values ------>"<<endl;
            cos<<"   Value        Fx         Fy         Mz    "<<endl;
            cos<<" ---------- ---------- ---------- ----------"<<endl;
            cos<<Fd(res)<<Fd(fx)<<Fd(fy)<<Fd(mz)<<endl<<endl;

            AxleIndexType axle_cnt = GetAxleCnt(vloads, config);
            DumpLiveLoadConfiguration(cos, config, axle_cnt, m_Util);

            cos<<endl;
         }
      }
   }
}


void CLiveLoadDumper::DumpLlmSupportDeflections(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName)
{
   CHRException hr;
   USES_CONVERSION;

   CComPtr<IVehicularLoads> vloads;
   hr = llModel->get_VehicularLoads(&vloads);

   VehicleIndexType vl_cnt;
   hr = vloads->get_Count(&vl_cnt);

   if (vl_cnt==0)
      return;

   // get all supports
   CComPtr<IIDArray> spt_ids;
   m_Util->GetSupportIDs(m_StageId, &spt_ids);

   // use a parameter stack instead of writing nested loops over force effects
   for (CLlmParameterStack::iterator piter=m_LlmParams.begin(); piter!=m_LlmParams.end(); piter++)
   {
      const CLlmParameterStack::LlParams& params = *piter;

      os<<endl;
      os<<"   Summary Support Deflection Responses for " << params.AsString(false)<<endl;
      os<<"    For Envelope For LiveLoadModel \""<<llName<<"\""<<endl;
      os<<"    ----------------------------------------------------------------------------------------"<<endl;

      // save first results key so we can write out concurrent results below
      long start_key = m_LastKey;
      CComPtr<ILiveLoadModelResults> llsresults;
      hr = m_LLM->ComputeSupportDeflections(spt_ids, m_Stage, llmType, params.ForceEffect, params.Optimization,
					    	              vlcDefault, params.DoApplyImpact, params.DoApplyDistf, VARIANT_TRUE, &llsresults);

      os<<"   Spt"<<endl;
      os<<"   ID      Result      Key"<<endl;
      os<<" ------ ---------- --------"<<endl;

      CollectionIndexType res_cnt;
      hr = llsresults->get_Count(&res_cnt);
      for (CollectionIndexType ires=0; ires<res_cnt; ires++)
      {
         IDType spt_id;
         hr = spt_ids->get_Item(ires, &spt_id);

         Float64 res;
         CComPtr<ILiveLoadConfiguration> config;
         hr = llsresults->GetResult(ires, &res, &config);

         long key = m_LastKey++;

         os<<right<<setw(7)<<spt_id<<Fd(res)<<" K"<<setw(6)<<key<<endl;
      }

      os<<endl;

      if (m_Util->DoDetails())
      {
         long curr_key = start_key;

         CComPtr<IIDArray> one_spt;
         hr = one_spt.CoCreateInstance(CLSID_LongArray);
         hr = one_spt->Add(-1);

         for (CollectionIndexType ires=0; ires<res_cnt; ires++)
         {
            IDType spt_id;
            hr = spt_ids->get_Item(ires, &spt_id);

            hr = one_spt->put_Item(0, spt_id);

            long key  = curr_key++;

            Float64 res;
            CComPtr<ILiveLoadConfiguration> config;
            hr = llsresults->GetResult(ires, &res, &config);

            cos<<endl;
            cos<<"    Concurrent, Detailed, Support Deflection Responses for " << params.AsString(false)<<endl;
            cos<<"    For Envelope For LiveLoadModel \""<<llName<<"\""<<endl;
            cos<<"    At Support "<<spt_id<<".  Key is K"<<key<<endl;
            cos<<"    ----------------------------------------------------------------------------------------"<<endl;

            CComPtr<IResult3Ds> res3ds;
            hr = m_BVR->ComputeSupportDeflections(one_spt, m_Stage, config, &res3ds);

            CComPtr<IResult3D> res3d;
            hr = res3ds->get_Item(0,&res3d);
            Float64 fx,fy,mz;
            hr = res3d->GetResult(&fx,&fy,&mz);

            cos<<"  Optimized <------Concurrent Values ------>"<<endl;
            cos<<"   Value        Dx         Dy         Rz    "<<endl;
            cos<<" ---------- ---------- ---------- ----------"<<endl;
            cos<<Fd(res)<<Fd(fx)<<Fd(fy)<<Fd(mz)<<endl<<endl;

            AxleIndexType axle_cnt = GetAxleCnt(vloads, config);
            DumpLiveLoadConfiguration(cos, config, axle_cnt, m_Util);

            cos<<endl;
         }
      }
   }
}


void CLiveLoadDumper::DumpEvrForces(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName)
{
   CHRException hr;
   USES_CONVERSION;

   // get all pois
   CComPtr<IIDArray> poi_ids;
   m_Util->GetAllPOIs(m_StageId, rsCumulative, &poi_ids);

   // use distribution factor type specified by liveloadmodel 
   DistributionFactorType df_type;
   hr = llModel->get_DistributionFactorType(&df_type);

   CComPtr<IVehicularLoads> vloads;
   hr = llModel->get_VehicularLoads(&vloads);

   VehicleIndexType vl_cnt;
   hr = vloads->get_Count(&vl_cnt);

   for (VehicleIndexType ivl=0; ivl<vl_cnt; ivl++)
   {
      CComPtr<IVehicularLoad> vload;
      hr = vloads->get_Item(ivl, &vload);

      CComBSTR vl_name;
      hr = vload->get_Name(&vl_name);

      VehicularLoadConfigurationType vl_type;
      hr = vload->get_Configuration(&vl_type);

      CComPtr<IAxles> axles;
      hr = vload->get_Axles(&axles);
      AxleIndexType axle_cnt;
      hr = axles->get_Count(&axle_cnt);

      // use a parameter stack instead of writing nested loops over force effects
      for (CEvrParameterStack::iterator piter=m_EvrParams.begin(); piter!=m_EvrParams.end(); piter++)
      {
         const CEvrParameterStack::LlParams& params = *piter;

         os<<endl;
         os<<"   Summary Force Responses for " << params.AsString(true)<<endl;
         os<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<endl;
         os<<"    ----------------------------------------------------------------------------------------"<<endl;

         // save first results key so we can write out concurrent results below
         long start_key = m_LastKey;
         CComPtr<ILiveLoadModelSectionResults> llsresults;
         hr = m_EVR->ComputeForces(poi_ids, m_Stage, llmType, ivl, roMember, params.ForceEffect, params.Optimization,
					    	              vl_type, params.DoApplyImpact, df_type, VARIANT_TRUE, &llsresults);

         os<<"        <------ Left -----> <----- Right ----->"<<endl;
         os<<"   POI    Result      Key     Result      Key"<<endl;
         os<<" ------ ---------- -------- ---------- --------"<<endl;

         CollectionIndexType res_cnt;
         hr = llsresults->get_Count(&res_cnt);
         for (CollectionIndexType ires=0; ires<res_cnt; ires++)
         {
            PoiIDType poi_id;
            hr = poi_ids->get_Item(ires, &poi_id);

            Float64 left_res, right_res;
            CComPtr<ILiveLoadConfiguration> left_config, right_config;
            hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

            long left_key = m_LastKey++;
            long right_key = m_LastKey++;

            os<<right<<setw(7)<<poi_id<<Ff(left_res)<<" K"<<setw(6)<<left_key<<Ff(right_res)<<" K"<<setw(6)<<right_key<<endl;
         }

         if (m_Util->DoDetails())
         {

            long curr_key = start_key;

            CComPtr<IIDArray> one_poi;
            hr = one_poi.CoCreateInstance(CLSID_LongArray);
            hr = one_poi->Add(-1);

            for (CollectionIndexType ires=0; ires<res_cnt; ires++)
            {
               IDType poi_id;
               hr = poi_ids->get_Item(ires, &poi_id);

               hr = one_poi->put_Item(0, poi_id);

               long left_key  = curr_key++;
               long right_key = curr_key++;

               Float64 left_res, right_res;
               CComPtr<ILiveLoadConfiguration> left_config, right_config;
               hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

               cos<<endl;
               cos<<"    Concurrent, Detailed, Force Responses for " << params.AsString(true)<<endl;
               cos<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<"\""<<endl;
               cos<<"    At POI "<<poi_id<<" Left Side. Key is K"<<left_key<<endl;
               cos<<"    ----------------------------------------------------------------------------------------"<<endl;

               CComPtr<ISectionResult3Ds> left_res3ds;
               hr = m_BVR->ComputeForces(one_poi, m_Stage, roMember, left_config, &left_res3ds);

               CComPtr<ISectionResult3D> left_res3d;
               hr = left_res3ds->get_Item(0,&left_res3d);
               Float64 lfx,lfy,lmz,rfx,rfy,rmz;
               hr = left_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

               cos<<"  Optimized <-------- Conc Left -----------> <------- Conc Right ----------->"<<endl;
               cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
               cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
               cos<<Ff(left_res)<<Ff(lfx)<<Ff(lfy)<<Ff(lmz)<<Ff(rfx)<<Ff(rfy)<<Ff(rmz)<<endl<<endl;

               DumpLiveLoadConfiguration(cos, left_config, axle_cnt, m_Util);

               cos<<endl;
               cos<<"    Concurrent, Detailed, Force Responses for " << params.AsString(true)<<endl;
               cos<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<"\""<<endl;
               cos<<"    At POI "<<poi_id<<" Right Side. Key is K"<<right_key<<endl;
               cos<<"    ----------------------------------------------------------------------------------------"<<endl;

               CComPtr<ISectionResult3Ds> right_res3ds;
               hr = m_BVR->ComputeForces(one_poi, m_Stage, roMember, right_config, &right_res3ds);

               CComPtr<ISectionResult3D> right_res3d;
               hr = right_res3ds->get_Item(0,&right_res3d);
               hr = right_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

               cos<<"  Optimized <-------- Conc Right -----------> <------- Conc Right ----------->"<<endl;
               cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
               cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
               cos<<Ff(right_res)<<Ff(lfx)<<Ff(lfy)<<Ff(lmz)<<Ff(rfx)<<Ff(rfy)<<Ff(rmz)<<endl<<endl;

               DumpLiveLoadConfiguration(cos, right_config, axle_cnt, m_Util);
            }
         }
      }
   }
}

void CLiveLoadDumper::DumpEvrDeflections(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName)
{
   CHRException hr;
   USES_CONVERSION;

   // get all pois
   CComPtr<IIDArray> poi_ids;
   m_Util->GetAllPOIs(m_StageId, rsCumulative, &poi_ids);

   // use distribution factor type specified by liveloadmodel 
   DistributionFactorType df_type;
   hr = llModel->get_DistributionFactorType(&df_type);

   CComPtr<IVehicularLoads> vloads;
   hr = llModel->get_VehicularLoads(&vloads);

   VehicleIndexType vl_cnt;
   hr = vloads->get_Count(&vl_cnt);

   for (VehicleIndexType ivl=0; ivl<vl_cnt; ivl++)
   {
      CComPtr<IVehicularLoad> vload;
      hr = vloads->get_Item(ivl, &vload);

      CComBSTR vl_name;
      hr = vload->get_Name(&vl_name);

      VehicularLoadConfigurationType vl_type;
      hr = vload->get_Configuration(&vl_type);

      CComPtr<IAxles> axles;
      hr = vload->get_Axles(&axles);
      AxleIndexType axle_cnt;
      hr = axles->get_Count(&axle_cnt);

      // use a parameter stack instead of writing nested loops over force effects
      for (CEvrParameterStack::iterator piter=m_EvrParams.begin(); piter!=m_EvrParams.end(); piter++)
      {
         const CEvrParameterStack::LlParams& params = *piter;

         os<<endl;
         os<<"   Summary Deflection Responses for " << params.AsString(true)<<endl;
         os<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<endl;
         os<<"    ----------------------------------------------------------------------------------------"<<endl;

         // save first results key so we can write out concurrent results below
         long start_key = m_LastKey;
         CComPtr<ILiveLoadModelSectionResults> llsresults;
         hr = m_EVR->ComputeDeflections(poi_ids, m_Stage, llmType, ivl, params.ForceEffect, params.Optimization,
					    	                   vl_type, params.DoApplyImpact, df_type, VARIANT_TRUE, &llsresults);

         os<<"        <------ Left -----> <----- Right ----->"<<endl;
         os<<"   POI    Result      Key     Result      Key"<<endl;
         os<<" ------ ---------- -------- ---------- --------"<<endl;

         CollectionIndexType res_cnt;
         hr = llsresults->get_Count(&res_cnt);
         for (CollectionIndexType ires=0; ires<res_cnt; ires++)
         {
            PoiIDType poi_id;
            hr = poi_ids->get_Item(ires, &poi_id);

            Float64 left_res, right_res;
            CComPtr<ILiveLoadConfiguration> left_config, right_config;
            hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

            long left_key = m_LastKey++;
            long right_key = m_LastKey++;

            os<<right<<setw(7)<<poi_id<<Fd(left_res)<<" K"<<setw(6)<<left_key<<Fd(right_res)<<" K"<<setw(6)<<right_key<<endl;
         }

         os<<" "<<endl;

         if (m_Util->DoDetails())
         {

            long curr_key = start_key;

            CComPtr<IIDArray> one_poi;
            hr = one_poi.CoCreateInstance(CLSID_LongArray);
            hr = one_poi->Add(-1);

            for (CollectionIndexType ires=0; ires<res_cnt; ires++)
            {
               IDType poi_id;
               hr = poi_ids->get_Item(ires, &poi_id);

               hr = one_poi->put_Item(0, poi_id);

               long left_key  = curr_key++;
               long right_key = curr_key++;

               Float64 left_res, right_res;
               CComPtr<ILiveLoadConfiguration> left_config, right_config;
               hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

               cos<<endl;
               cos<<"    Concurrent, Detailed, Deflection Responses for " << params.AsString(false)<<endl;
               cos<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<"\""<<endl;
               cos<<"    At POI "<<poi_id<<" Left Side. Key is K"<<left_key<<endl;
               cos<<"    ----------------------------------------------------------------------------------------"<<endl;

               CComPtr<ISectionResult3Ds> left_res3ds;
               hr = m_BVR->ComputeDeflections(one_poi, m_Stage, left_config, &left_res3ds);

               CComPtr<ISectionResult3D> left_res3d;
               hr = left_res3ds->get_Item(0,&left_res3d);
               Float64 lfx,lfy,lmz,rfx,rfy,rmz;
               hr = left_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

               cos<<"  Optimized <-------- Conc Left -----------> <------- Conc Right ----------->"<<endl;
               cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
               cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
               cos<<Fd(left_res)<<Fd(lfx)<<Fd(lfy)<<Fd(lmz)<<Fd(rfx)<<Fd(rfy)<<Fd(rmz)<<endl<<endl;

               DumpLiveLoadConfiguration(cos, left_config, axle_cnt, m_Util);

               cos<<endl;
               cos<<"    Concurrent, Detailed, Deflection Responses for " << params.AsString(false)<<endl;
               cos<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<"\""<<endl;
               cos<<"    At POI "<<poi_id<<" Right Side. Key is K"<<right_key<<endl;
               cos<<"    ----------------------------------------------------------------------------------------"<<endl;

               CComPtr<ISectionResult3Ds> right_res3ds;
               hr = m_BVR->ComputeDeflections(one_poi, m_Stage, right_config, &right_res3ds);

               CComPtr<ISectionResult3D> right_res3d;
               hr = right_res3ds->get_Item(0,&right_res3d);
               hr = right_res3d->GetResult(&lfx,&lfy,&lmz,&rfx,&rfy,&rmz);

               cos<<"  Optimized <-------- Conc Right -----------> <------- Conc Right ----------->"<<endl;
               cos<<"   Value        Fx         Fy         Mz        Fx          Fy        Mz"<<endl;
               cos<<" ---------- ---------- ---------- ---------- ---------- ---------- ----------"<<endl;
               cos<<Fd(right_res)<<Fd(lfx)<<Fd(lfy)<<Fd(lmz)<<Fd(rfx)<<Fd(rfy)<<Fd(rmz)<<endl<<endl;

               DumpLiveLoadConfiguration(cos, right_config, axle_cnt, m_Util);
               cos<<endl;
            }
         }
      }
   }
}

void CLiveLoadDumper::DumpEvrReactions(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName)
{
   CHRException hr;
   USES_CONVERSION;

   // get all supports
   CComPtr<IIDArray> spt_ids;
   m_Util->GetSupportIDs(m_StageId, &spt_ids);

   // use distribution factor type specified by liveloadmodel 
   DistributionFactorType df_type;
   hr = llModel->get_DistributionFactorType(&df_type);

   CComPtr<IVehicularLoads> vloads;
   hr = llModel->get_VehicularLoads(&vloads);

   VehicleIndexType vl_cnt;
   hr = vloads->get_Count(&vl_cnt);

   for (VehicleIndexType ivl=0; ivl<vl_cnt; ivl++)
   {
      CComPtr<IVehicularLoad> vload;
      hr = vloads->get_Item(ivl, &vload);

      CComBSTR vl_name;
      hr = vload->get_Name(&vl_name);

      VehicularLoadConfigurationType vl_type;
      hr = vload->get_Configuration(&vl_type);

      CComPtr<IAxles> axles;
      hr = vload->get_Axles(&axles);
      AxleIndexType axle_cnt;
      hr = axles->get_Count(&axle_cnt);

      // use a parameter stack instead of writing nested loops over force effects
      for (CEvrParameterStack::iterator piter=m_EvrParams.begin(); piter!=m_EvrParams.end(); piter++)
      {
         const CEvrParameterStack::LlParams& params = *piter;

         os<<endl;
         os<<"   Summary Reaction Responses for " << params.AsString(true)<<endl;
         os<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<endl;
         os<<"    ----------------------------------------------------------------------------------------"<<endl;

         // save first results key so we can write out concurrent results below
         long start_key = m_LastKey;
         CComPtr<ILiveLoadModelResults> llsresults;
         hr = m_EVR->ComputeReactions(spt_ids, m_Stage, llmType, ivl, params.ForceEffect, params.Optimization,
					    	                 vl_type, params.DoApplyImpact, df_type, VARIANT_TRUE, &llsresults);

         os<<"   Spt"<<endl;
         os<<"   ID      Result      Key"<<endl;
         os<<" ------ ---------- --------"<<endl;

         CollectionIndexType res_cnt;
         hr = llsresults->get_Count(&res_cnt);
         for (CollectionIndexType ires=0; ires<res_cnt; ires++)
         {
            IDType spt_id;
            hr = spt_ids->get_Item(ires, &spt_id);

            Float64 res;
            CComPtr<ILiveLoadConfiguration> config;
            hr = llsresults->GetResult(ires, &res, &config);

            long key = m_LastKey++;

            os<<right<<setw(7)<<spt_id<<Fd(res)<<" K"<<setw(6)<<key<<endl;
         }

         os<<" "<<endl;

         if (m_Util->DoDetails())
         {

            long curr_key = start_key;

            CComPtr<IIDArray> one_spt;
            hr = one_spt.CoCreateInstance(CLSID_LongArray);
            hr = one_spt->Add(-1);

            for (CollectionIndexType ires=0; ires<res_cnt; ires++)
            {
               IDType spt_id;
               hr = spt_ids->get_Item(ires, &spt_id);

               hr = one_spt->put_Item(0, spt_id);

               long key  = curr_key++;

               Float64 res;
               CComPtr<ILiveLoadConfiguration> config;
               hr = llsresults->GetResult(ires, &res, &config);

               cos<<endl;
               cos<<"    Concurrent, Detailed, Reaction Responses for " << params.AsString(true)<<endl;
               cos<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<"\""<<endl;
               cos<<"    At Support "<<spt_id<<".  Key is K"<<key<<endl;
               cos<<"    ----------------------------------------------------------------------------------------"<<endl;

               CComPtr<IResult3Ds> res3ds;
               hr = m_BVR->ComputeReactions(one_spt, m_Stage, config, &res3ds);

               CComPtr<IResult3D> res3d;
               hr = res3ds->get_Item(0,&res3d);
               Float64 fx,fy,mz;
               hr = res3d->GetResult(&fx,&fy,&mz);

               cos<<"  Optimized <------Concurrent Values ------>"<<endl;
               cos<<"   Value        Fx         Fy         Mz    "<<endl;
               cos<<" ---------- ---------- ---------- ----------"<<endl;
               cos<<Fd(res)<<Fd(fx)<<Fd(fy)<<Fd(mz)<<endl<<endl;

               DumpLiveLoadConfiguration(cos, config, axle_cnt, m_Util);

               cos<<endl;
            }
         }
      }
   }
}

void CLiveLoadDumper::DumpEvrSupportDeflections(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName)
{
   CHRException hr;
   USES_CONVERSION;

   // get all supports
   CComPtr<IIDArray> spt_ids;
   m_Util->GetSupportIDs(m_StageId, &spt_ids);

   // use distribution factor type specified by liveloadmodel 
   DistributionFactorType df_type;
   hr = llModel->get_DistributionFactorType(&df_type);

   CComPtr<IVehicularLoads> vloads;
   hr = llModel->get_VehicularLoads(&vloads);

   VehicleIndexType vl_cnt;
   hr = vloads->get_Count(&vl_cnt);

   for (VehicleIndexType ivl=0; ivl<vl_cnt; ivl++)
   {
      CComPtr<IVehicularLoad> vload;
      hr = vloads->get_Item(ivl, &vload);

      CComBSTR vl_name;
      hr = vload->get_Name(&vl_name);

      VehicularLoadConfigurationType vl_type;
      hr = vload->get_Configuration(&vl_type);

      CComPtr<IAxles> axles;
      hr = vload->get_Axles(&axles);
      AxleIndexType axle_cnt;
      hr = axles->get_Count(&axle_cnt);

      // use a parameter stack instead of writing nested loops over force effects
      for (CEvrParameterStack::iterator piter=m_EvrParams.begin(); piter!=m_EvrParams.end(); piter++)
      {
         const CEvrParameterStack::LlParams& params = *piter;

         os<<endl;
         os<<"   Summary Support Deflection Responses for " << params.AsString(false)<<endl;
         os<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<endl;
         os<<"    ----------------------------------------------------------------------------------------"<<endl;

         // save first results key so we can write out concurrent results below
         long start_key = m_LastKey;
         CComPtr<ILiveLoadModelResults> llsresults;
         hr = m_EVR->ComputeSupportDeflections(spt_ids, m_Stage, llmType, ivl, params.ForceEffect, params.Optimization,
					    	                 vl_type, params.DoApplyImpact, df_type, VARIANT_TRUE, &llsresults);

         os<<"   Spt"<<endl;
         os<<"   ID      Result      Key"<<endl;
         os<<" ------ ---------- --------"<<endl;

         CollectionIndexType res_cnt;
         hr = llsresults->get_Count(&res_cnt);
         for (CollectionIndexType ires=0; ires<res_cnt; ires++)
         {
            IDType spt_id;
            hr = spt_ids->get_Item(ires, &spt_id);

            Float64 res;
            CComPtr<ILiveLoadConfiguration> config;
            hr = llsresults->GetResult(ires, &res, &config);

            long key = m_LastKey++;

            os<<right<<setw(7)<<spt_id<<Fd(res)<<" K"<<setw(6)<<key<<endl;
         }

         os<<" "<<endl;

         if (m_Util->DoDetails())
         {

            long curr_key = start_key;

            CComPtr<IIDArray> one_spt;
            hr = one_spt.CoCreateInstance(CLSID_LongArray);
            hr = one_spt->Add(-1);

            for (CollectionIndexType ires=0; ires<res_cnt; ires++)
            {
               IDType spt_id;
               hr = spt_ids->get_Item(ires, &spt_id);

               hr = one_spt->put_Item(0, spt_id);

               long key  = curr_key++;

               Float64 res;
               CComPtr<ILiveLoadConfiguration> config;
               hr = llsresults->GetResult(ires, &res, &config);

               cos<<endl;
               cos<<"    Concurrent, Detailed, Support Deflection Responses for " << params.AsString(false)<<endl;
               cos<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<"\""<<endl;
               cos<<"    At Support "<<spt_id<<".  Key is K"<<key<<endl;
               cos<<"    ----------------------------------------------------------------------------------------"<<endl;

               CComPtr<IResult3Ds> res3ds;
               hr = m_BVR->ComputeSupportDeflections(one_spt, m_Stage, config, &res3ds);

               CComPtr<IResult3D> res3d;
               hr = res3ds->get_Item(0,&res3d);
               Float64 fx,fy,mz;
               hr = res3d->GetResult(&fx,&fy,&mz);

               cos<<"  Optimized <------Concurrent Values ------>"<<endl;
               cos<<"   Value        Dx         Dy         Rz    "<<endl;
               cos<<" ---------- ---------- ---------- ----------"<<endl;
               cos<<Fd(res)<<Fd(fx)<<Fd(fy)<<Fd(mz)<<endl<<endl;

               DumpLiveLoadConfiguration(cos, config, axle_cnt, m_Util);

               cos<<endl;
            }
         }
      }
   }
}



void CLiveLoadDumper::DumpEvrStresses(std::_tostream& os, std::_tostream& cos, LiveLoadModelType llmType, ILiveLoadModel* llModel, const char* llName)
{
   CHRException hr;
   USES_CONVERSION;

   // get all pois
   CComPtr<IIDArray> poi_ids;
   m_Util->GetAllPOIs(m_StageId, rsCumulative, &poi_ids);

   // use distribution factor type specified by liveloadmodel 
   DistributionFactorType df_type;
   hr = llModel->get_DistributionFactorType(&df_type);

   CComPtr<IVehicularLoads> vloads;
   hr = llModel->get_VehicularLoads(&vloads);

   VehicleIndexType vl_cnt;
   hr = vloads->get_Count(&vl_cnt);

   for (VehicleIndexType ivl=0; ivl<vl_cnt; ivl++)
   {
      CComPtr<IVehicularLoad> vload;
      hr = vloads->get_Item(ivl, &vload);

      CComBSTR vl_name;
      hr = vload->get_Name(&vl_name);

      VehicularLoadConfigurationType vl_type;
      hr = vload->get_Configuration(&vl_type);

      CComPtr<IAxles> axles;
      hr = vload->get_Axles(&axles);
      AxleIndexType axle_cnt;
      hr = axles->get_Count(&axle_cnt);

      // use a parameter stack instead of writing nested loops over force effects
      for (CEvrParameterStack::iterator piter=m_EvrParams.begin(); piter!=m_EvrParams.end(); piter++)
      {
         const CEvrParameterStack::LlParams& params = *piter;

         os<<endl;
         os<<"   Summary Stress Responses for " << params.AsString(true)<<endl;
         os<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<endl;
         os<<"    ----------------------------------------------------------------------------------------"<<endl;

         // save first results key so we can write out concurrent results below
         long start_key = m_LastKey;
         CComPtr<ILiveLoadModelStressResults> llsresults;
         hr = m_EVR->ComputeStresses(poi_ids, m_Stage, llmType, ivl, params.ForceEffect, params.Optimization,
					    	                vl_type, params.DoApplyImpact, df_type, VARIANT_TRUE, &llsresults);

         os<<"        <----------------- Left ---------------------------> <-------------------------- Right -------------------->"<<endl;
         os<<"   POI     SP0        SP1         SP2        SP3      Key       SP0        SP1        SP2        SP3       Key"<<endl;
         os<<" ------ ---------- ---------- ---------- ---------- -------- ---------- ---------- ---------- ---------- --------"<<endl;

         CollectionIndexType res_cnt;
         hr = llsresults->get_Count(&res_cnt);
         for (CollectionIndexType ires=0; ires<res_cnt; ires++)
         {
            IDType poi_id;
            hr = poi_ids->get_Item(ires, &poi_id);

            CComPtr<IStressResult> left_res, right_res;
            CComPtr<ILiveLoadConfiguration> left_config, right_config;
            hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

            std::_tstring rgt_sp0, rgt_sp1, rgt_sp2, rgt_sp3;
            std::_tstring lft_sp0, lft_sp1, lft_sp2, lft_sp3;

            CollectionIndexType cnt;
            Float64 val;
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

         if (m_Util->DoDetails())
         {

            long curr_key = start_key;

            CComPtr<IIDArray> one_poi;
            hr = one_poi.CoCreateInstance(CLSID_LongArray);
            hr = one_poi->Add(-1);

            for (CollectionIndexType ires=0; ires<res_cnt; ires++)
            {
               IDType poi_id;
               hr = poi_ids->get_Item(ires, &poi_id);

               hr = one_poi->put_Item(0, poi_id);

               long left_key  = curr_key++;
               long right_key = curr_key++;

               CComPtr<IStressResult> left_res, right_res;
               CComPtr<ILiveLoadConfiguration> left_config, right_config;
               hr = llsresults->GetResult(ires, &left_res, &left_config, &right_res, &right_config);

               cos<<"    Detailed Configuration for Stress Responses for " << params.AsString(true)<<endl;
               cos<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<"\""<<endl;
               cos<<"    At POI "<<poi_id<<" Left Side. Key is K"<<left_key<<endl;
               cos<<"    ----------------------------------------------------------------------------------------"<<endl;

               DumpLiveLoadConfiguration(cos, left_config, axle_cnt, m_Util);

               cos<<endl;
               cos<<"    Detailed Configuration for Stress Responses for " << params.AsString(true)<<endl;
               cos<<"    For LiveLoadModel \""<<llName<<"\" No. "<<ivl<<" with name \""<<W2A(vl_name)<<"\""<<endl;
               cos<<"    At POI "<<poi_id<<" Right Side. Key is K"<<right_key<<endl;
               cos<<"    ----------------------------------------------------------------------------------------"<<endl;

               DumpLiveLoadConfiguration(cos, right_config, axle_cnt, m_Util);
               cos<<endl;
            }
         }
      }
   }
}


void CLiveLoadDumper::DumpLiveLoadModelResponse(std::_tostream& os, std::_tostream& cos)
{

}



///////////////////////////////////////////////////
// initialize live load parameter stack

CEvrParameterStack::CEvrParameterStack()
{
}

void CEvrParameterStack::Init()
{
   m_Params.reserve(24);

   for (long ii=0; ii<2; ii++)
   {
      VARIANT_BOOL impact = (ii==0 ? VARIANT_TRUE : VARIANT_FALSE);

      m_Params.push_back( LlParams(fetFx, optMinimize, impact) );
      m_Params.push_back( LlParams(fetFx, optMaximize, impact) );
      m_Params.push_back( LlParams(fetFy, optMinimize, impact) );
      m_Params.push_back( LlParams(fetFy, optMaximize, impact) );
      m_Params.push_back( LlParams(fetMz, optMinimize, impact) );
      m_Params.push_back( LlParams(fetMz, optMaximize, impact) );
   }
}

std::_tstring CEvrParameterStack::LlParams::AsString(bool isForce) const
{
   std::_tstring msg;

   if (Optimization==optMaximize)
      msg = _T("Maximized ");
   else
      msg = _T("Minimized ");

   if (isForce)
   {
      if (ForceEffect==fetFx)
         msg+=_T("Fx Force, ");
      else if (ForceEffect==fetFy)
         msg+=_T("Fy Force, ");
      else if (ForceEffect==fetMz)
         msg+=_T("Mz Moment, ");
      else
         ATLASSERT(0);
   }
   else
   {
      if (ForceEffect==fetFx)
         msg+=_T("Dx Deflection, ");
      else if (ForceEffect==fetFy)
         msg+=_T("Dy Deflection,");
      else if (ForceEffect==fetMz)
         msg+=_T("Rz Deflection, ");
      else
         ATLASSERT(0);
   }

   if (DoApplyImpact!=VARIANT_FALSE)
      msg += _T("Impact Applied. ");
   else
      msg += _T("Impact Not Applied. ");

   return msg;
}


CLlmParameterStack::CLlmParameterStack()
{
}

void CLlmParameterStack::Init()
{
   m_Params.reserve(24);

   for (long ii=0; ii<2; ii++)
   {
      VARIANT_BOOL impact = (ii==0 ? VARIANT_TRUE : VARIANT_FALSE);
      for (long id=0; id<2; id++)
      {
         VARIANT_BOOL distf = (id==0 ? VARIANT_TRUE : VARIANT_FALSE);

         m_Params.push_back( LlParams(fetFx, optMinimize, impact, distf) );
         m_Params.push_back( LlParams(fetFx, optMaximize, impact, distf) );
         m_Params.push_back( LlParams(fetFy, optMinimize, impact, distf) );
         m_Params.push_back( LlParams(fetFy, optMaximize, impact, distf) );
         m_Params.push_back( LlParams(fetMz, optMinimize, impact, distf) );
         m_Params.push_back( LlParams(fetMz, optMaximize, impact, distf) );
      }
   }
}

std::_tstring CLlmParameterStack::LlParams::AsString(bool isForce) const
{
   std::_tstring msg;

   if (Optimization==optMaximize)
      msg = _T("Maximized ");
   else
      msg = _T("Minimized ");

   if (isForce)
   {
      if (ForceEffect==fetFx)
         msg+=_T("Fx Force, ");
      else if (ForceEffect==fetFy)
         msg+=_T("Fy Force, ");
      else if (ForceEffect==fetMz)
         msg+=_T("Mz Moment, ");
      else
         ATLASSERT(0);
   }
   else
   {
      if (ForceEffect==fetFx)
         msg+=_T("Dx Deflection, ");
      else if (ForceEffect==fetFy)
         msg+=_T("Dy Deflection,");
      else if (ForceEffect==fetMz)
         msg+=_T("Rz Deflection, ");
      else
         ATLASSERT(0);
   }

   if (DoApplyImpact!=VARIANT_FALSE)
      msg += _T("Impact Applied, ");
   else
      msg += _T("Impact Not Applied, ");

   if (DoApplyDistf!=VARIANT_FALSE)
      msg += _T("Distribution Factors Applied. ");
   else
      msg += _T("Distribution Factors Not Applied. ");

   return msg;
}

