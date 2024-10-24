// PropertyDataSetBuilder.cpp: implementation of the PropertyDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lbamviewer.h"
#include "PropertyDataSetBuilder.h"

#include "DataSetUtils.h"
#include <iomanip>

#include "GraphXYDisplayObjectImpl.h"
#include "Legend.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


static void GetPInfo(PropertyDataSetBuilder::PType type, UINT* symbol, CComBSTR& str);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PropertyDataSetBuilder::PropertyDataSetBuilder(PType type, IGetSegmentCrossSection* pgs):
m_Type(type),
m_pGetCrossSection(pgs)
{

}

PropertyDataSetBuilder::~PropertyDataSetBuilder()
{

}

void PropertyDataSetBuilder::BuildDataSets(IIDArray* poiList, IDblArray* locList, const CString& currStg,
                                           CLBAMViewerDoc::ResponseType currRt, ResultsSummationType summType,
                                           COLORREF color, std::vector<std::shared_ptr<iGraphXyDataProvider>>* dataSets)
{
   // create dataset 
   // create dataset 
   auto dataset_p = std::make_shared<CGraphXyDataProvider>();

   // deal with legend
   auto fac = dataset_p->GetDataPointFactory();
   auto entry = std::dynamic_pointer_cast<iSymbolLegendEntry>(fac);

   entry->SetColor(color);

   CComBSTR bstr;
   UINT symbol;
   GetPInfo(m_Type, &symbol, bstr);
   entry->SetSymbolCharacterCode(symbol);
   entry->DoDrawLine(TRUE);
   entry->SetName(OLE2T(bstr));

   auto dataset = dataset_p->GetDataSet();

   IndexType num_pois;
   poiList->get_Count(&num_pois);
   for (IndexType ip=0; ip<num_pois; ip++)
   {
      PoiIDType poi_id;
      poiList->get_Item(ip,&poi_id);
      CComPtr<ISegmentCrossSection> left_cs, right_cs;
      HRESULT hr = m_pGetCrossSection->GetSegmentCrossSectionAtPOI(poi_id, CComBSTR(currStg), &left_cs, &right_cs);
      PROCESS_HR(hr);

      double xloc;
      locList->get_Item(ip,&xloc);

      if (left_cs != NULL)
      {
         double val = GetVal(left_cs);

         // fill up data set
         WBFL::Geometry::Point2d pnt(xloc, val);
         dataset->Add(pnt);
      }
      else
         ATLASSERT(0);

      if (right_cs != NULL)
      {
         double val = GetVal(right_cs);

         // fill up data set
         WBFL::Geometry::Point2d pnt(xloc, val);
         dataset->Add(pnt);
      }
   }
   dataSets->push_back(dataset_p);
}

double PropertyDataSetBuilder::GetVal(ISegmentCrossSection* pcs)
{
   HRESULT hr;
   double val;

   switch (m_Type)
   {
   case ptEAForce:
      hr = pcs->get_EAForce(&val);
      break;
   case ptEADefl:
      hr = pcs->get_EADefl(&val);
      break;
   case ptEIForce:
      hr = pcs->get_EIForce(&val);
      break;
   case ptEIDefl:
      hr = pcs->get_EIDefl(&val);
      break;
   case ptDepth:
      hr = pcs->get_Depth(&val);
      break;
   case ptThermal:
      hr = pcs->get_ThermalCoeff(&val);
      break;
   default:
      ATLASSERT(0);
      break;
   }

   ATLASSERT(SUCCEEDED(hr));

   return val;
}


void GetPInfo(PropertyDataSetBuilder::PType type, UINT* symbol, CComBSTR& str)
{
   switch (type)
   {
   case PropertyDataSetBuilder::ptEAForce:
      *symbol = 65;
      str = "EA Force";
      break;
   case PropertyDataSetBuilder::ptEADefl:
      *symbol = 65;
      str = "EA Defl";
      break;
   case PropertyDataSetBuilder::ptEIForce:
      *symbol = 73;
      str = "EI Force";
      break;
   case PropertyDataSetBuilder::ptEIDefl:
      *symbol = 73;
      str = "EI Defl";
      break;
   case PropertyDataSetBuilder::ptDepth:
      *symbol = 68;
      str = "Depth";
      break;
   case PropertyDataSetBuilder::ptThermal:
      *symbol = 97;
      str = "Thermal";
      break;
   default:
      ATLASSERT(0);
      break;
   }
}