///////////////////////////////////////////////////////////////////////
// LBAM Analysis Test - Test driver for LBAM analysis library
// Copyright © 1999-2018  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <iomanip>

static void DumpSectionForceResults(std::_tofstream& os, IIDArray* pois , CComPtr<ISectionResult3Ds> pres, std::vector<Float64>& poi_locs)
{
   // have to attach and detach variant to safearray

   CollectionIndexType poi_cnt;
   pois->get_Count(&poi_cnt);
   for (CollectionIndexType i = 0; i<poi_cnt; i++)
   {
      CComPtr<ISectionResult3D> res;
      pres->get_Item(i,&res);

      Float64 fx_left, fx_right, fy_left, fy_right, mz_left, mz_right;
      res->GetResult(&fx_left, &fy_left, &mz_left, &fx_right, &fy_right, &mz_right);

      // print in diagram form
      PoiIDType pid;
      pois->get_Item(i, &pid);
      os<< pid<<", "<<poi_locs[i]<<", "<< fx_left<<", "<<fy_left<<", "<<mz_left<< std::endl;

      bool twice=false;
      Float64 fx, fy, mz;
      if (!IsEqual(fx_left, -fx_right))
      {
         fx = -fx_right;
         twice = true;
      }
      else
      {
         fx = fx_left;
      }

      if (!IsEqual(fy_left, -fy_right))
      {
         fy = -fy_right;
         twice = true;
      }
      else
      {
         fy = fy_left;
      }

      if (!IsEqual(mz_left, -mz_right))
      {
         mz = -mz_right;
         twice = true;
      }
      else
      {
         mz = mz_left;
      }

      if (twice)
      {
         os<< pid<<", "<<poi_locs[i]<<", "<< fx<<", "<<fy<<", "<<mz<< std::endl;
      }
   }

   // blank after each print
   os<<std::endl;
}

static void DumpDeflectionResults(std::_tofstream& os, IIDArray* pois , CComPtr<ISectionResult3Ds> pres, std::vector<Float64>& poi_locs)
{
   CollectionIndexType poi_cnt;
   pois->get_Count(&poi_cnt);

   for (CollectionIndexType i = 0; i<poi_cnt; i++)
   {
      CComPtr<ISectionResult3D> res;
      pres->get_Item(i,&res);

      Float64 ldx, ldy, lrz, rdx, rdy, rrz;
      res->GetResult( &ldx, &ldy, &lrz, &rdx, &rdy, &rrz);

      // print in diagram form
      PoiIDType pid;
      pois->get_Item(i,&pid);
      os<< pid<<", "<<poi_locs[i]<<", "<< ldx<<", "<<ldy<<", "<<lrz<<", "<< rdx<<", "<<rdy<<", "<<rrz<< std::endl;
   }

   // blank after each print
   os<<std::endl;
}

static void DumpSupportDeflectionResults(std::_tofstream& os, IIDArray* pois , CComPtr<IResult3Ds> pres)
{
   CollectionIndexType poi_cnt;
   pois->get_Count(&poi_cnt);

   for (CollectionIndexType i = 0; i<poi_cnt; i++)
   {
      CComPtr<IResult3D> res;
      pres->get_Item(i,&res);

      Float64 dx, dy, rz;
      res->GetResult( &dx, &dy, &rz);

      PoiIDType pid;
      pois->get_Item(i,&pid);
      os<< pid <<", "<< dx<<", "<<dy<<", "<<rz<< std::endl;
   }

   // blank after each print
   os<<std::endl;

}

static void DumpReactionResults(std::_tofstream& os, IIDArray* pois , CComPtr<IResult3Ds> pres)
{
   // have to attach and detach variant to safearray
   CollectionIndexType poi_cnt;
   pois->get_Count(&poi_cnt);

   for (CollectionIndexType i = 0; i<poi_cnt; i++)
   {
      CComPtr<IResult3D> res;
      pres->get_Item(i,&res);

      Float64 fx, fy, mz;
      res->GetResult(&fx, &fy, &mz);

      PoiIDType pid;
      pois->get_Item(i, &pid);
      os<< pid<<", "<< fx<<", "<<fy<<", "<<mz<< std::endl;
   }

   // blank after each print
   os<<std::endl;
}

static void DumpStressResults(std::_tofstream& os, IIDArray* pois , CComPtr<ISectionStressResults> pres)
{
   CollectionIndexType poi_cnt;
   pois->get_Count(&poi_cnt);
   for (CollectionIndexType i = 0; i<poi_cnt; i++)
   {
      CComPtr<ISectionStressResult> res;
      pres->get_Item(i,&res);

      PoiIDType pid;
      pois->get_Item(i,&pid);

      CollectionIndexType num_left, num_right;
      res->get_LeftCount(&num_left);
      res->get_RightCount(&num_right);

      for (CollectionIndexType j = 0; j<max(num_left,num_right); j++)
      {
         os<<std::setw(6)<< pid;

         Float64 left_res, right_res;
         if (i<num_left)
         {
            res->GetLeftResult(j, &left_res);
            os<<std::setw(12)<<left_res;
         }
         else
         {
            os<<std::setw(12)<<" ";
         }

         if (i<num_right)
         {
            res->GetRightResult(j, &right_res);
            os<<std::setw(12)<<left_res;
         }
      }
   }

   // blank after each print
   os<<std::endl;
}



