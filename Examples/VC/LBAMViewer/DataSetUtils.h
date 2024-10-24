#ifndef INCLUDED_DATASETUTILS_H_
#define INCLUDED_DATASETUTILS_H_

#include <MathEx.h>
#include "LBAMViewerDoc.h"
#include "DataSet2d.h"

// carriage return for reports
#define C_R _T("\\par ")

enum  llResponseType{llrTruckLaneCombo, llrTruckEnvelope, llrTruckOnly, llrLaneOnly, llrSidewalkOnly};


inline void FillDataSet(IDblArray* locList, std::shared_ptr<iDataSet2d> dataSet, ISectionResult3Ds* secRes, CLBAMViewerDoc::ResponseType currRt)
{
   HRESULT hr;
   IndexType size;
   hr = secRes->get_Count(&size);
   ATLASSERT(SUCCEEDED(hr));

   for (IndexType i=0; i<size; i++)
   {
      CComPtr<ISectionResult3D> res;
      hr = secRes->get_Item(i, &res);
      ATLASSERT(SUCCEEDED(hr));
   
      // values
      double left, right;
      if (currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtDx)
      {
         hr = res->get_XLeft(&left);
         ATLASSERT(SUCCEEDED(hr));
         hr = res->get_XRight(&right);
         ATLASSERT(SUCCEEDED(hr));
      }
      else if (currRt==CLBAMViewerDoc::rtFy || currRt==CLBAMViewerDoc::rtDy)
      {
         hr = res->get_YLeft(&left);
         ATLASSERT(SUCCEEDED(hr));
         hr = res->get_YRight(&right);
         ATLASSERT(SUCCEEDED(hr));

         if (currRt==CLBAMViewerDoc::rtFy)
         {
            // convert shears to beam diagram coordinates
            left  *= -1;
            right *= -1;
         }
      }
      else if (currRt==CLBAMViewerDoc::rtMz || currRt==CLBAMViewerDoc::rtRz)
      {
         hr = res->get_ZLeft(&left);
         ATLASSERT(SUCCEEDED(hr));
         hr = res->get_ZRight(&right);
         ATLASSERT(SUCCEEDED(hr));
      }
      else
         ATLASSERT(0);

      // set left value
      double loc;
      locList->get_Item(i,&loc);

      dataSet->Add(WBFL::Geometry::Point2d(loc,left));

      // only set right value if it's different
      if ((currRt==CLBAMViewerDoc::rtFx || currRt==CLBAMViewerDoc::rtFy|| currRt==CLBAMViewerDoc::rtMz))
      {
         // force values have this equal and opposite sign convention at a slice thing going
         right *= -1.0;
      }

      //if (!IsEqual(left, right))
      {
         dataSet->Add(WBFL::Geometry::Point2d(loc,right));
      }
   }
}

inline VehicularLoadConfigurationType GetConfigType(llResponseType respType, std::_tstring& strvlc)
{
   switch (respType)
   {
   case llrTruckLaneCombo:
      strvlc = _T("Default");
      return vlcDefault;
      break;
   case llrTruckOnly:
      strvlc = _T("Truck Only");
      return vlcTruckOnly;
      break;
   case llrLaneOnly:
      strvlc = _T("Lane Only Only");
      return vlcLaneOnly;
      break;
   case llrSidewalkOnly:
      strvlc = _T("Sidewalk Only");
      return vlcSidewalkOnly;
      break;
   default:
      ATLASSERT(0);
   }

   strvlc = _T("Unknown VehicularLoadConfigurationType");
   return vlcDefault;
}


#endif
