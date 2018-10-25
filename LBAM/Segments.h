///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2015  Washington State Department of Transportation
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

// Segments.h : Declaration of the CSegments

#ifndef __SEGMENTS_H_
#define __SEGMENTS_H_

#include "resource.h"       // main symbols
#include <map>
#include <vector>
#include "FilteredSegmentCollection.h"

class  CSegments;
// Class that owners of CSegments must implement so event handling is
// set up properly
class CSegmentsOwner
{
public:
   virtual HRESULT SetUpConnection(ISegmentItem* pCp, DWORD* pcookie)=0;
   virtual void BreakConnection(ISegmentItem* pCp, DWORD cookie)=0;
   // don't need a real connection point here. let parent fire
   virtual void OnSegmentsChanged(CSegments* psegments, BSTR stage, ChangeType change)=0;
};

// A copy class for IEnumSegments

template <class T>
class _CopySegments
{
public:
   static HRESULT copy(VARIANT* pv, const T* piter)
   {
      HRESULT hr = (*piter)->second->QueryInterface(IID_IDispatch, (void**)&pv->pdispVal);
      if (SUCCEEDED(hr))
         pv->vt = VT_DISPATCH;

      return hr;
   }

   static void init(VARIANT*) {}
   static void destroy(VARIANT* p) { VariantClear(p); }
};


/////////////////////////////////////////////////////////////////////////////
// CSegments
//
// A C++ implementation class for handling cross-section segments for superstructure
// and support members
//
class  CSegments 
{
public:
   CSegments(CSegmentsOwner* pown)
	{
      m_pOwner = pown;
	}

   ~CSegments();

public:
	HRESULT GetMemberSegments(/*[in]*/BSTR stage, /*[in]*/Float64 Length, /*[in]*/VARIANT_BOOL isSymmetrical, /*[out,retval]*/IFilteredSegmentCollection* * collection);
	HRESULT GetSegmentsForStage(/*[in]*/BSTR stage, /*[out,retval]*/IFilteredSegmentCollection* *);
	HRESULT GetSegmentForMemberLocation(/*[in]*/BSTR stage, /*[in]*/Float64 Length, /*[in]*/VARIANT_BOOL isSymmetrical, /*[in]*/Float64 location, /*[out]*/ISegmentItem** ppLeftSegi, /*[out]*/ISegmentItem** ppRightSegi);
	HRESULT Reverse(/*[in]*/BSTR stage);
	HRESULT Remove(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType index);
	HRESULT CopyTo(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType fromIndex, /*[in]*/SegmentIndexType toIndex);
	HRESULT MoveTo(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType fromIndex, /*[in]*/SegmentIndexType toIndex);
	HRESULT Insert(/*[in]*/SegmentIndexType relPosition, /*[in]*/BSTR stage, /*[in]*/ISegment* segment);
	HRESULT Add(/*[in]*/BSTR stage, /*[in]*/ISegment* segment);
	HRESULT get_Segment(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[out, retval]*/ ISegment* *pVal);
	HRESULT put_Segment(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[in]*/ ISegment* newVal);
	HRESULT get_Count(/*[in]*/ BSTR stage, /*[out, retval]*/ SegmentIndexType *pVal);
	HRESULT get_Length(/*[in]*/ BSTR stage, Float64 Length, /*[out, retval]*/ Float64 *pVal);
	HRESULT RemoveStage(/*[in]*/BSTR stage);

   void Clear();

   // IStructuredStorage2
	void Load(IStructuredLoad2 * Load);
	void Save(IStructuredSave2 * Save);

   STDMETHOD(Copy)(CSegments* copy);

   typedef  ISegmentItem* ItemType;

private:
   CSegments();

// data members               cookie
   typedef CAdapt<CComPtr<ISegmentItem>> ValueType;
   typedef std::pair< DWORD, ValueType > StoredType; 
   typedef std::vector<StoredType> VectorType;
   typedef VectorType::iterator  VectorIteratorType;
   typedef std::map< CComBSTR, VectorType > ContainerType;
   typedef ContainerType::iterator  ContainerIteratorType;
   typedef ContainerType::const_iterator  ContainerConstIteratorType;

   ContainerType m_Segments;

   // pointer back to our owner
   CSegmentsOwner* m_pOwner;

// utility functions
   VectorType* GetVector(BSTR stage);
   void UpdateRelPositions(CSegments::VectorType* pvec);
   HRESULT LayoutSegments(Float64 layoutLength, Float64 totalLength, VectorType* pvec, CFilteredSegmentCollection* pnew_coll);

// Classes for local C++ clients
public:

   // iterator class for iterating entire collection

   class iterator
   {
      friend CSegments;
   public:
      iterator()
      {
         m_pColl = 0;
      }

      iterator(const iterator& other)
      {
         MakeCopy(other);
      }

      iterator& operator=(const iterator& other)
      {
         MakeCopy(other);
         return *this;
      }

   private:
      ContainerIteratorType m_cit;
      VectorIteratorType    m_vit;
      CSegments*          m_pColl;

      void MakeCopy(const iterator& other)
      {
         m_cit = other.m_cit;
         m_vit = other.m_vit;
         m_pColl = other.m_pColl;
      }

   public:
		iterator& operator++()
      {
         // a bit tricky here since we're iterating through a nested collection
         m_vit++;
         if (m_vit == m_cit->second.end()) // test if at end of vector for current stage
         {
            m_cit++;
            if (m_cit != m_pColl->m_Segments.end()) // are we really at the end?
            {
               // set to start of vector for this stage
               m_vit = m_cit->second.begin();
            }
         }
         return (*this); 
      }

      // postfix
		iterator operator++(int)
      {
         iterator tmp = *this;
         m_vit++;
         if (m_vit == m_cit->second.end()) // test if at end of vector for current stage
         {
            m_cit++;
            if (m_cit != m_pColl->m_Segments.end()) // are we really at the end?
            {
               // no, set to start of vector for this stage
               m_vit = m_cit->second.begin();
            }
         }
			return (tmp); 
      }

		ItemType& operator*() const
      {
         return m_vit->second.m_T.p;   // dangerous here, but what we must do to compile
      }

		ItemType& operator->() const
      {
         return m_vit->second.m_T.p;
      }

		bool operator==(const iterator& rit) const
		{
         bool bEqual = true;
         // NOTE: Evaluation order matters
         if ( m_pColl == rit.m_pColl )
         {
            // same collection

            if ( m_cit == rit.m_cit )
            {
               // at the same location in the m_Segments container
               if (m_cit != m_pColl->m_Segments.end() )
               {
                  bEqual = (m_vit == rit.m_vit) ? true : false;
               }
               else
               {
                  bEqual = true;
               }
            }
            else
            {
               bEqual = false;
            }
         }
         else
         {
            bEqual = false;
         }

         return bEqual;
      }

		bool operator!=(const iterator& rit) const
		{
         return !(*this==rit);
      }

   };

   iterator begin()
   {
      iterator it;
      it.m_pColl = this;
      it.m_cit = m_Segments.begin();
      it.m_vit = m_Segments.begin()->second.begin();
      return it;
   }

   iterator end()
   {
      iterator it;
      it.m_pColl = this;
      it.m_cit = m_Segments.end();

      return it;
   }

   friend iterator; // this is NOT VERY OBVIOUS HERE!!! , but it won't compile elsewhere

   typedef iterator const_iterator;
};

#endif //__SEGMENTS_H_
