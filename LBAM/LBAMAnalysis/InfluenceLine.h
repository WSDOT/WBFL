///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2022  Washington State Department of Transportation
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

// InfluenceLine.h : Declaration of the CInfluenceLine

#ifndef __INFLUENCELINE_H_
#define __INFLUENCELINE_H_

#include "resource.h"       // main symbols

#include "LBAMUtils.h"
#include <vector>
#include <MathEx.h>

/////////////////////////////////////////////////////////////////////////////
// CInfluenceLine
class ATL_NO_VTABLE CInfluenceLine : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInfluenceLine, &CLSID_InfluenceLine>,
	public ISupportErrorInfo,
	public IInfluenceLine,
   public IPersistImpl<CInfluenceLine>,
   public IObjectSafetyImpl<CInfluenceLine,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
   // determines whether influence line values are to be returned as input (raw), or 
   // if the line should be optimized.
   enum ProcessingType {iptRaw, iptProcessed};

   CInfluenceLine():
   m_ZeroTolerance(1.0e-06),   // no tolerance
   m_ProcessingType(iptProcessed) // optimize values by default
	{
      m_GlobalX = -1;
      m_idPOI   = -1;

     m_LastFound[0] = 0;
     m_LastFound[1] = 0;
     m_LastFound[2] = 0;

     m_IsComputed[0] = false;
     m_IsComputed[1] = false;
     m_IsComputed[2] = false;
	}

   void Initialize(Float64 globalX,PoiIDType poiID)
   {
      m_GlobalX = globalX;
      m_idPOI   = poiID;
   }

DECLARE_REGISTRY_RESOURCEID(IDR_INFLUENCELINE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CInfluenceLine)
	COM_INTERFACE_ENTRY(IInfluenceLine)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// IInfluenceLine
public:
   STDMETHOD(get_Location)(/*[out,retval]*/Float64* location) override;
   STDMETHOD(get_POI)(/*[out,retval]*/PoiIDType* poi) override;
   STDMETHOD(Item)(/*[in]*/CollectionIndexType idx, /*[in]*/InfluenceSideType side, /*[out]*/ Float64* value, /*[out]*/InfluenceLocationType* locationType, /*[out]*/Float64* location) override;
   STDMETHOD(get_Count)( /*[in]*/InfluenceSideType side, /*[out,retval]*/ CollectionIndexType *pVal) override;
   STDMETHOD(Add)(/*[in]*/InfluenceLocationType locationType, /*[in]*/Float64 location, /*[in]*/Float64 value) override;
   STDMETHOD(Remove)(/*[in]*/CollectionIndexType index) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(Clone)(/*[out,retval]*/IInfluenceLine** clone) override;
   STDMETHOD(Bounds)(/*[out]*/Float64* start, Float64* end) override;
   STDMETHOD(Evaluate)(/*[in]*/Float64 location, /*[in]*/InfluenceSideType side, /*[out]*/VARIANT_BOOL* isDualValue, /*[out]*/Float64* leftValue, /*[out]*/Float64* rightValue) override;
	STDMETHOD(ComputeNonZeroRegions)(/*[in]*/InfluenceSideType side, /*[out,retval]*/IDblArray* *locations) override;
	STDMETHOD(ComputeArea)(/*[in]*/InfluenceSideType side,/*[out,retval]*/Float64* area) override;
	STDMETHOD(ComputeAreaInRegions)(/*[in]*/IDblArray* locations,/*[out,retval]*/Float64* area) override;
	STDMETHOD(IsZero)(/*[in]*/InfluenceSideType side,/*[out,retval]*/VARIANT_BOOL* isZero) override;
   STDMETHOD(FindMaxValue)(/*[in]*/Float64 start,/*[in]*/ Float64 end,/*[out]*/Float64* pLocation,/*[out]*/Float64* pValue) override;
   STDMETHOD(FindMinValue)(/*[in]*/Float64 start,/*[in]*/ Float64 end,/*[out]*/Float64* pLocation,/*[out]*/Float64* pValue) override;

public:
   // C++ public
   // pre-allocate some space
   HRESULT Reserve(CollectionIndexType n);
   // set up tolerancing - this should only be done once at initialization
   HRESULT GetZeroTolerance(/*[out,retval]*/ Float64 *pVal);
   HRESULT SetZeroTolerance(/*[in]*/ Float64 Val);

   // Set up whether influence values are to be optimized (zeroed, redundants removed), or left raw
   // iptProcessed is the default
   ProcessingType GetProcessingType()
   {
      return m_ProcessingType;
   }

   void SetProcessingType(ProcessingType type)
   {
      m_ProcessingType = type;
   }

#if defined(_DEBUG_LOGGING)
   void TraceInfluenceLine(InfluenceSideType side);
#endif

// Data
   struct InflPoint
   {
      Float64 m_Value;
      Float64 m_Location;
      InfluenceLocationType m_LocationType;

      // constructor
      InflPoint(Float64 value, Float64 location, InfluenceLocationType locationType):
      m_Value(value),
      m_Location(location),
      m_LocationType(locationType)
      {
      }

      InflPoint CopyAndZero() const
      {
         return InflPoint(0.0, m_Location, m_LocationType);
      }

      InflPoint CopySingle() const
      {
         return InflPoint(m_Value, m_Location, iflSingle);
      }

      // for life in a container
      bool operator< (const InflPoint& other) const
      { 
         if (IsEqual(m_Location, other.m_Location))
         {
            // tie breaker if equal locations and left-right
            if (m_Location==iflDualLeft)
            {
               if (other.m_Location==iflDualRight)
               {
                  return true;
               }
               else
               {
                  ATLASSERT(false); // container should prevent this
                  return m_Location < other.m_Location; 
               }
            }
            else if (m_Location==iflDualRight)
            {
               if (other.m_Location==iflDualLeft)
               {
                  return false;
               }
               else
               {
                  ATLASSERT(false); // container should prevent this
                  return m_Location < other.m_Location; 
               }
            }
            else
            {
               ATLASSERT(false); // container should prevent duplicate iflSingle values
               return m_Location < other.m_Location; 
            }
         }
         else
         {
            return m_Location < other.m_Location; 
         }
      }

   private:
      InflPoint();
   };
protected:

   static Float64 ms_LocationTolerance;

   // local functional class used in stl algoritm for zeroing out influence values
   class ZeroOutInflPoint
   {
      Float64 m_Tolerance;
   public:
      ZeroOutInflPoint(Float64 tolerance) : m_Tolerance(tolerance) {;}

      void operator()(InflPoint& pnt)
      {
          if ( fabs(pnt.m_Value) < m_Tolerance )
          {
             pnt.m_Value=0.0;
          }
      }
   };

   // our main container
   typedef std::vector<InflPoint> InfluencePointContainer;
   typedef InfluencePointContainer::iterator InfluencePointIterator;
   typedef InfluencePointContainer::const_iterator ConstInfluencePointIterator;

   InfluencePointContainer m_InfluencePoints[3]; // one container for each InfluenceSideType
   Float64 m_Area[3];

   Float64 m_ZeroTolerance;
   bool m_IsComputed[3];
   ProcessingType m_ProcessingType;

   // cached values
   CollectionIndexType m_LastFound[3];
   Float64 m_StartBound;
   Float64 m_EndBound;

   Float64 m_GlobalX;
   PoiIDType m_idPOI;

private:
   void Compute(InfluenceSideType side);
   void ComputeMainValues();
   void DoComputeArea();
   void Invalidate();
   void OptimizeInfluence(const InfluencePointContainer& source, InfluencePointContainer& target);
   void Flatten(InfluenceSideType side);

   void FindInflPnt(Float64 location, InfluencePointIterator& cursor, InfluencePointIterator& end);
   Float64 CalcInflArea(Float64 startLoc, Float64 endLoc, InfluencePointIterator& cursor, InfluencePointIterator& end);


   InfluencePointContainer& GetContainer(InfluenceSideType side)
   {
      ATLASSERT(side>=0 && side<3);
      return m_InfluencePoints[side];
   }

};

#endif //__INFLUENCELine_H_
