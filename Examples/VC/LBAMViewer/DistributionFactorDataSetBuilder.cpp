// DistributionFactorDataSetBuilder.cpp: implementation of the DistributionFactorDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "DistributionFactorDataSetBuilder.h"

#include "DataSetUtils.h"
#include <iomanip>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DistributionFactorDataSetBuilder::DistributionFactorDataSetBuilder(DfType type, IGetDistributionFactors* pdfs):
m_Type(type),
m_pDfs(pdfs)
{

}

DistributionFactorDataSetBuilder::~DistributionFactorDataSetBuilder()
{

}

void DistributionFactorDataSetBuilder::BuildDataSets(ILongArray* poiList, IDblArray* locList, BSTR currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets)
{
   HRESULT hr;

   // create dataset 
   // create dataset 
   CComPtr<iGraphXyDataProvider> dataset_p;
   hr = dataset_p.CoCreateInstance(CLSID_GraphXyDataProvider);
   ATLASSERT(SUCCEEDED(hr));

   // deal with legend
   CComPtr<iDataPointFactory> fac;
   dataset_p->get_DataPointFactory(&fac);
   CComQIPtr<iSymbolLegendEntry> entry(fac);

   entry->put_Color(color);
   entry->put_SymbolCharacterCode(187);
   entry->put_DoDrawLine(TRUE);

   CComBSTR btmp("Dist. Factor");
   entry->put_Name(btmp);

   CComPtr<iDataSet2d> dataset;
   dataset_p->get_DataSet(&dataset);

   // need to get information at pois
   CComPtr<ILBAMFactory> poi_utility;
   hr = poi_utility.CoCreateInstance(CLSID_LRFDFactory);
   PROCESS_HR(hr);

   CollectionIndexType num_pois;
   poiList->get_Count(&num_pois);
   for (CollectionIndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      poiList->get_Item(ip, &poi_id);
      CComPtr<IDistributionFactor> left_df, right_df;
      HRESULT hr = m_pDfs->GetPOIDistributionFactor(poi_id, currStg, &left_df, &right_df);
      PROCESS_HR(hr);

      if (left_df != NULL)
      {

         // fill up data set
         CComPtr<IPoint2d> pnt;
         hr = pnt.CoCreateInstance(CLSID_Point2d);
         ATLASSERT(SUCCEEDED(hr));
         double loc;
         locList->get_Item(ip, &loc);
         pnt->put_X(loc);

         double val = GetVal(left_df);
         pnt->put_Y(val);
         dataset->Add(pnt);
      }
      else
         ATLASSERT(0);

      if (right_df != NULL)
      {

         // fill up data set
         CComPtr<IPoint2d> pnt;
         hr = pnt.CoCreateInstance(CLSID_Point2d);
         ATLASSERT(SUCCEEDED(hr));
         double loc;
         locList->get_Item(ip, &loc);
         pnt->put_X(loc);

         double val = GetVal(right_df);
         pnt->put_Y(val);
         dataset->Add(pnt);
      }
   }
   dataSets->push_back(dataset_p.Detach());
}

double DistributionFactorDataSetBuilder::GetVal(IDistributionFactor* pdf)
{
   HRESULT hr;
   double val;

   switch (m_Type)
   {
   case dtGPMSgl:
      hr = pdf->get_GPMSgl(&val);
      break;
   case dtGPMMul:
      hr = pdf->get_GPMMul(&val);
      break;
   case dtGNMSgl:
      hr = pdf->get_GNMSgl(&val);
      break;
   case dtGNMMul:
      hr = pdf->get_GNMMul(&val);
      break;
   case dtGVSgl:
      hr = pdf->get_GVSgl(&val);
      break;
   case dtGVMul: 
      hr = pdf->get_GVMul(&val);
      break;
   case dtGDSgl: 
      hr = pdf->get_GDSgl(&val);
      break;
   case dtGDMul:
      hr = pdf->get_GDMul(&val);
      break;
   case dtGTSgl:
      hr = pdf->get_GTSgl(&val);
      break;
   case dtGTMul:
      hr = pdf->get_GTMul(&val);
      break;
   case dtGRSgl:
      hr = pdf->get_GRSgl(&val);
      break;
   case dtGRMul:
      hr = pdf->get_GRMul(&val);
      break;
   case dtGFat:
      hr = pdf->get_GFat(&val);
      break;
   default:
      ATLASSERT(0);
      break;
   }

   ATLASSERT(SUCCEEDED(hr));

   return val;
}


