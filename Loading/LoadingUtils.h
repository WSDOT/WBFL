///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// LoadingUtils.h

#ifndef INCLUDED_LOADINGUTILS_H_
#define INCLUDED_LOADINGUTILS_H_

#include <MathEx.h>
#include <vector>

#include <ComException.h>
#include <WbflAtlExt.h>

///////////////////////////////////////
//// Error Messages and help
//
#define THROW_HR(hr) { ATLASSERT(false); throw hr;}
// short-hand version if consistent naming conventions are used
#define THROW_EXCEPTION(errNam) { /*ATLASSERT(false);*/ throw CComException(_T(__FILE__),__LINE__, IDS_E_##errNam, LOADING_E_##errNam, IDH_E_##errNam);}
//#define THROW_LBAM_MSG(errNam, msg) { /*ATLASSERT(false);*/ throw CComException(_T(__FILE__),__LINE__, msg, LBAM_E_##errNam, IDH_E_##errNam);}
//
/*
#define CHECK_MEMBERTYPE(mbrType) if (mbrType<mtUndefined || mbrType>mtSuperstructureMember) return E_INVALIDARG;

inline CComBSTR CreateContextMsg(MemberType lbamMbrType, long lbamMbrId)
{
   TCHAR msg[48];

   switch (lbamMbrType)
   {
   case mtSpan:
      {
         TCHAR format[]=_T("Span %d.");
         int cOut = _stprintf( msg, format, lbamMbrId);
         ATLASSERT( cOut < 48 );
      }
      break;
   case mtSuperstructureMember:
      {
         TCHAR format[]=_T("SuperstructureMember %d.");
         int cOut = _stprintf( msg, format, lbamMbrId);
         ATLASSERT( cOut < 48 );
      }
      break;
   case mtSupport:
      {
         TCHAR format[]=_T("Support %d.");
         int cOut = _stprintf( msg, format, lbamMbrId);
         ATLASSERT( cOut < 48 );
      }
      break;
   case mtTemporarySupport:
      {
         TCHAR format[]=_T("TemporarySupport %d.");
         int cOut = _stprintf( msg, format, lbamMbrId);
         ATLASSERT( cOut < 48 );
      }
      break;
   default:
      THROW_HR(E_FAIL);
   }

   return CComBSTR(msg);
}
*/

template< class T>
HRESULT DealWithExceptionsInContext(T* psource, const IID& iid)
{
   // try to put what got thrown into context
   try
   {
      try
      {
         throw; // throw whatever got thrown last to be caught immediately!
      }
      catch (CComException& re)
      {
         // Local flavor. Append context to message
        CComBSTR msg = CreateContextMsg(psource->GetMemberType(), psource->m_ID);
        re.AppendToMessage(msg);
        throw re;
      }
      catch (...)
      {
         throw;
      }
   }
   catch(...)
   {
      // now deal with as any exception
      return DealWithExceptions(psource, iid);
   }
}

//////////////////////////////////////////////////////////
// Useful LBAM-specific stuff
//
/*
inline CComBSTR MemberTypeToString(MemberType type)
{
   CComBSTR strtype;
   if (type==mtSpan)
   {
      strtype = "Span";
   }
   else if (type==mtSuperstructureMember)
   {
      strtype = "SuperstructureMember";
   }
   else if (type == mtSupport)
   {
      strtype = "Support";
   }
   else if (type == mtTemporarySupport)
   {
      strtype = "TemporarySupport";
   }
   else if (type == mtUndefined)
   {
      strtype = "Undefined";
   }
   else
   {
      ATLASSERT(false);
   }

   return strtype;
}

inline HRESULT StringToMemberType(BSTR bstrtype, MemberType* ptype)
{
   CComBSTR strtype = bstrtype;
   MemberType type;
   if (strtype == CComBSTR("Span"))
   {
      type = mtSpan;
   }
   else if (strtype == CComBSTR("SuperstructureMember"))
   {
      type = mtSuperstructureMember;
   }
   else if (strtype == CComBSTR("Support"))
   {
      type = mtSupport;
   }
   else if (strtype == CComBSTR("TemporarySupport"))
   {
      type = mtTemporarySupport;
   }
   else if (strtype == CComBSTR("Undefined"))
   {
      type = mtUndefined;
   }
   else
   {
      ATLASSERT(false);
      return STRLOAD_E_INVALIDFORMAT;
   }

   *ptype = type;

   return S_OK;
}  
*/
inline CComBSTR LoadOrientationToString(ldLoadOrientation type)
{
   CComBSTR strtype;
   if (type==ldloGlobal)
   {
      strtype = "Global";
   }
   else if (type==ldloMember)
   {
      strtype = "Member";
   }
   else if (type == ldloGlobalProjected)
   {
      strtype = "GlobalProjected";
   }
   else
   {
      ATLASSERT(false);
   }

   return strtype;
}

inline HRESULT StringToLoadOrientation(BSTR bstrtype, ldLoadOrientation* ptype)
{
   CComBSTR strtype = bstrtype;
   ldLoadOrientation type;
   if (strtype == CComBSTR("Global"))
   {
      type = ldloGlobal;
   }
   else if (strtype == CComBSTR("Member"))
   {
      type = ldloMember;
   }
   else if (strtype == CComBSTR("GlobalProjected"))
   {
      type = ldloGlobalProjected;
   }
   else
   {
      ATLASSERT(false);
      return STRLOAD_E_INVALIDFORMAT;
   }

   *ptype = type;

   return S_OK;
} 

inline CComBSTR LoadDirectionToString(ldLoadDirection type)
{
   CComBSTR strtype;
   if (type==ldldFx)
   {
      strtype = "Fx";
   }
   else if (type==ldldFy)
   {
      strtype = "Fy";
   }
   else
   {
      ATLASSERT(false);
   }

   return strtype;
}

inline HRESULT StringToLoadDirection(BSTR bstrtype, ldLoadDirection* ptype)
{
   CComBSTR strtype = bstrtype;
   ldLoadDirection type;
   if (strtype == CComBSTR("Fx"))
   {
      type = ldldFx;
   }
   else if (strtype == CComBSTR("Fy"))
   {
      type = ldldFy;
   }
   else
   {
      ATLASSERT(false);
      return STRLOAD_E_INVALIDFORMAT;
   }

   *ptype = type;

   return S_OK;
} 
//
//// function to deal with fractional and absolute values
//enum FracRes {frTooSmall, frTooBig};
//
//inline Float64 GetFracDistance(Float64 fracLoc, Float64 Length, bool ignoreTooBig=false) // throw FracRes
//{
//   ATLASSERT(Length>0.0);
//
//   if (fracLoc>=0.0)
//   {
//      if (ignoreTooBig || fracLoc<=Length+1.0e-08) // IsLE(fracLoc,Length))
//      {
//         return fracLoc;
//      }
//      else
//      {
//         throw frTooBig;
//      }
//   }
//   else
//   {
//      if (-1.0<=fracLoc)
//      {
//         return -fracLoc*Length;
//      }
//      else
//         throw frTooSmall;
//   }
//
//   ATLASSERT(false); //can't get here
//   return 0.0;
//}
//
//// slimmed-down class for handling 2d points
//struct XyLoc
//{
//   XyLoc():
//   m_X(0.0), m_Y(0.0) {;}
//
//   XyLoc(Float64 x, Float64 y):
//   m_X(x), m_Y(y) {;}
//
//   static Float64 squared(Float64 x) { return x*x; }
//
//   Float64 Distance(const XyLoc& rother)
//   {
//      return sqrt( squared(m_X-rother.m_X) + squared(m_Y-rother.m_Y) );
//   }
//
//   Float64 m_X;
//   Float64 m_Y;
//};
//
//inline void ComputeSubNodeLocation(const XyLoc& bottom, const XyLoc& top, Float64 location, Float64 support_length, XyLoc* pNodeLoc)
//{
//   ATLASSERT(location>=0.0);
//   ATLASSERT(support_length>0.0);
//   ATLASSERT(location<=support_length);
//   Float64 frac = location/support_length;
//   pNodeLoc->m_X = bottom.m_X + frac * (top.m_X - bottom.m_X);
//   pNodeLoc->m_Y = bottom.m_Y + frac * (top.m_Y - bottom.m_Y);
//}
//
//inline void FindTemporarySupport(ILBAMModel* pModel, long tsId, ITemporarySupport* *ptempSupport, long* pSpanNo)
//{
//   // only way to find a ts is to search through spans
//   // Note this search returns when it finds the first support with the given id. It
//   // does not look for duplicates or out of bounds values.
//   CComPtr<ISpans> spans;
//   CHRException hr;
//   hr = pModel->get_Spans(&spans);
//
//   long num_spans;
//   hr = spans->get_Count(&num_spans);
//
//   // id of temporary support cannot be in the range of the regular support numbers
//   if (tsId<0 || tsId>num_spans)
//   {
//
//      for (long ispan = 0; ispan<num_spans; ispan++)
//      {
//         CComPtr<ISpan> span;
//         hr = spans->get_Item(ispan, &span);
//
//         CComPtr<ITemporarySupports> tss;
//         hr = span->get_TemporarySupports(&tss);
//
//         long ts_cnt;
//         hr = tss->get_Count(&ts_cnt);
//
//         for (long its = 0; its<ts_cnt; its++)
//         {
//            CComPtr<ITemporarySupport> ts;
//            hr = tss->get_Item(its, &ts);
//
//            long id;
//            hr = ts->get_ID(&id);
//
//            if (id == tsId)
//            {
//               // found our support
//               *pSpanNo = ispan;
//               *ptempSupport = ts;
//               (*ptempSupport)->AddRef();
//               return;
//            }
//         }
//      }
//   }
//
//   // if we get here, the support was not found
//   *pSpanNo = -1;
//   *ptempSupport = 0;
//}
//
//
//// Helper template class for dealing with the IDbl/ILng/IBStr Array classes
//// Note this this thing throws with an error occurs - so wrap it in a try block
//template <class T, class TArr>
//class TIArrayHelper
//{
//public:
//   TIArrayHelper(TArr* arr):
//   m_Arr(arr)
//   {;}
//
//   T operator[] (long i) const
//   {
//      ATLASSERT(m_Arr!=nullptr);
//      T val;
//      CHRException hr;
//      hr = m_Arr->get_Item(i, &val);
//      return val;
//   }
//
//   long Size()
//   {
//      long siz;
//      CHRException hr;
//      hr = m_Arr->get_Count(&siz);
//      return siz;
//   }
//
//private:
//   CComPtr<TArr> m_Arr;
//};
//


#endif //
