// DistributionFactorDataSetBuilder.cpp: implementation of the DistributionFactorDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "DistributionFactorDataSetBuilder.h"
#include "GraphXYDisplayObjectImpl.h"
#include "DataSetUtils.h"
#include "Legend.h"
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

void DistributionFactorDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, const CString& currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
{
   // create dataset 
   auto dataset_p = std::make_shared<CGraphXyDataProvider>();

   // deal with legend
   auto fac = dataset_p->GetDataPointFactory();
   auto entry = std::dynamic_pointer_cast<iSymbolLegendEntry>(fac);

   entry->SetColor(color);
   entry->SetSymbolCharacterCode(187);
   entry->DoDrawLine(TRUE);

   entry->SetName(_T("Dist. Factor"));

   auto dataset = dataset_p->GetDataSet();

   // need to get information at pois
   CComPtr<ILBAMFactory> poi_utility;
   HRESULT hr = poi_utility.CoCreateInstance(CLSID_LRFDFactory);
   PROCESS_HR(hr);

   IndexType num_pois;
   poiList->get_Count(&num_pois);
   for (IndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      poiList->get_Item(ip, &poi_id);
      CComPtr<IDistributionFactor> left_df, right_df;
      HRESULT hr = m_pDfs->GetPOIDistributionFactor(poi_id, CComBSTR(currStg), &left_df, &right_df);
      PROCESS_HR(hr);

      if (left_df != NULL)
      {

         // fill up data set
         double loc;
         locList->get_Item(ip, &loc);

         double val = GetVal(left_df);

         WBFL::Geometry::Point2d pnt(loc, val);
         dataset->Add(pnt);
      }
      else
         ATLASSERT(0);

      if (right_df != NULL)
      {

         // fill up data set
         double loc;
         locList->get_Item(ip, &loc);

         double val = GetVal(right_df);

         WBFL::Geometry::Point2d pnt(loc, val);
         dataset->Add(pnt);
      }
   }
   dataSets->push_back(dataset_p);
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
      Float64 val2;
      hr = pdf->GetGFat(&val,&val2);
      break;
   default:
      ATLASSERT(0);
      break;
   }

   ATLASSERT(SUCCEEDED(hr));

   return val;
}


