
#include "StdAfx.h"
#include "DumperUtils.h"
#include "WBFLTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void CDumperUtil::Compute()
{
   CHRException hr;

   // optimism prevents recursion
   m_Dirty=false;

   hr = m_Factory.CoCreateInstance(CLSID_LRFDFactory);

   // start with superstructure sorted list of pois
   CComPtr<IAnalysisPOIs> apois;
   hr = m_Engine->get_AnalysisPOIs(&apois);

   CComPtr<ILBAMModel> model;
   hr = m_Engine->get_Model(&model);
   CComPtr<IStages> stages;
   hr = model->get_Stages(&stages);

   StageIndexType stg_cnt;
   hr = stages->get_Count(&stg_cnt);

   m_SsPoiIds.reserve(stg_cnt);
   m_SsPoiLocs.reserve(stg_cnt);

   for (StageIndexType is=0; is<stg_cnt; is++)
   {
      CComPtr<IStage> stage;
      hr = stages->get_Item(is,&stage);

      CComBSTR stgnm;
      hr = stage->get_Name(&stgnm);

      m_StageNames.push_back(stgnm);

      CComPtr<IDblArray> poi_locs;
      CComPtr<IIDArray> poi_ids;
      hr = apois->GetSuperstructurePois(stgnm, &poi_ids,&poi_locs);

      m_SsPoiIds.push_back(poi_ids);
      m_SsPoiLocs.push_back(poi_locs);

      // get pois for cummulative summation type - (no internal pois)
      CComPtr<IIDArray> cum_poi_ids;
      CComPtr<IDblArray> cum_poi_locs;
      hr = cum_poi_ids.CoCreateInstance(CLSID_IDArray);
      hr = cum_poi_locs.CoCreateInstance(CLSID_DblArray);

      CollectionIndexType npois;
      hr = poi_ids->get_Count(&npois);
      for (CollectionIndexType ip=0; ip<npois; ip++)
      {
         IDType poi_id;
         hr = poi_ids->get_Item(ip, &poi_id);

         if (poi_id>=0)
         {
            hr = cum_poi_ids->Add(poi_id);

            double poi_loc;
            hr = poi_locs->get_Item(ip, &poi_loc);

            hr = cum_poi_locs->Add(poi_loc);
         }
      }

      m_CumSsPoiIds.push_back(cum_poi_ids);
      m_CumSsPoiLocs.push_back(cum_poi_locs);

   }

   // next we need support poi's - unsorted for now
   CComPtr<IPOIs> pois;
   hr = model->get_POIs(&pois);

   for (StageIndexType is=0; is<stg_cnt; is++)
   {
      CComPtr<IIDArray> sptpoiids;
      hr = sptpoiids.CoCreateInstance(CLSID_IDArray);

      CComPtr<IIDArray> sptids;
      this->GetSupportIDs(is, &sptids);

      CollectionIndexType poi_cnt;
      hr = pois->get_Count(&poi_cnt);

      for (CollectionIndexType ip=0; ip<poi_cnt; ip++)
      {
         CComPtr<IPOI> poi;
         hr = pois->get_Item(ip,&poi);

         MemberType mt;
         hr = poi->get_MemberType(&mt);

         if (mt==mtSupport || mt==mtTemporarySupport)
         {
            MemberIDType spt_id;
            hr = poi->get_MemberID(&spt_id);

            CollectionIndexType idx;
            HRESULT hresult = sptids->Find(spt_id, &idx);

            if (FAILED(hresult))
            {
               // support is in this stage
               PoiIDType poi_id;
               hr = poi->get_ID(&poi_id);
               sptpoiids->Add(poi_id);
            }
         }
      }

      m_SptPoiIds.push_back( sptpoiids );

   }
}

void CDumperUtil::GetSuperstructurePOIs(StageIndexType iStage, ResultsSummationType summ, IIDArray** poiIDs, IDblArray** poiLocs)
{
   CHRException hr;

   if (m_Dirty)
      Compute();

   try
   {
      if (summ==rsIncremental)
      {
         hr = m_SsPoiIds[iStage].m_T.CopyTo(poiIDs);
         hr = m_SsPoiLocs[iStage].m_T.CopyTo(poiLocs);
      }
      else
      {
         hr = m_CumSsPoiIds[iStage].m_T.CopyTo(poiIDs);
         hr = m_CumSsPoiLocs[iStage].m_T.CopyTo(poiLocs);
      }
   }
   catch(...)
   {
      ATLASSERT(0);
      throw;
   }
}



StageIndexType CDumperUtil::StageCount()
{
   if (m_Dirty)
      Compute();

   return m_StageNames.size();
}

void CDumperUtil::StageName(StageIndexType i, BSTR* name)
{
   if (m_Dirty)
      Compute();

   m_StageNames[i].m_T.CopyTo(name);
}

void CDumperUtil::GetSupportPOIs(StageIndexType iStage, IIDArray** poiIDs)
{
   CHRException hr;

   if (m_Dirty)
      Compute();

   hr = m_SptPoiIds[iStage].m_T.CopyTo(poiIDs);
}

void CDumperUtil::GetSupportIDs(StageIndexType iStage,  IIDArray** sptIDs)
{
   CHRException hr;

   try
   {

      if (m_Dirty)
         Compute();

      CComPtr<ILBAMModel> model;
      hr = m_Engine->get_Model(&model);

      hr = m_Factory->GetSupportIDsForStage(model, m_StageNames[iStage].m_T, sptIDs); 
   }
   catch(...)
   {
      ATLASSERT(0);
      throw;
   }
}

void CDumperUtil::GetAllPOIs(StageIndexType iStage, ResultsSummationType summ, IIDArray** poiIDs)
{
   CHRException hr;

   if (m_Dirty)
      Compute();

   try
   {
      CComPtr<IIDArray> ssids;
      CComPtr<IDblArray> sslocs;

      // get superstructure ids first
      this->GetSuperstructurePOIs(iStage, summ, &ssids, &sslocs);

      CComPtr<IIDArray> allids;
      hr = ssids->Clone(&allids);

      CComPtr<IIDArray> spids;

      // get substructure pois and append them to the list
      this->GetSupportPOIs(iStage, &spids);

      CollectionIndexType sp_cnt;
      hr = spids->get_Count(&sp_cnt);

      for (CollectionIndexType ip=0; ip<sp_cnt; ip++)
      {
         IDType id;
         hr = spids->get_Item(ip, &id);

         hr = allids->Add(id);
      }

      hr = allids.CopyTo(poiIDs);
   }
   catch(...)
   {
      ATLASSERT(0);
      throw;
   }
}
