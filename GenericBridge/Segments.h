///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// Segments.h : Declaration of the CSegments

#ifndef __SEGMENTS_H_
#define __SEGMENTS_H_

#include "resource.h"       // main symbols
#include <map>
#include <vector>

class  CSegments;
// Class that owners of CSegments must implement so event handling is
// set up properly
class CSegmentsOwner
{
public:
   //virtual HRESULT SetUpConnection(ISegmentItem* pCp, unsigned long* pcookie) = 0;
   //virtual void BreakConnection(ISegmentItem* pCp, unsigned long cookie) = 0;
   //// don't need a real connection point here. let parent fire
   //virtual void OnSegmentsChanged(CSegments* psegments) = 0;
   // get total length of owner
   virtual Float64 Length() = 0;
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
   CSegments(CSegmentsOwner* pown):
   m_pOwner(pown)
	{
      m_bFractional = false;
      m_pBridge = NULL;
	}

   ~CSegments();

   void SetBridge(IGenericBridge* pBridge);

   void MakeFractional();
   void MakeAbsolute();
   bool IsFractional();

   HRESULT ConfirmStageExists(BSTR bstrStage);

public:
	HRESULT GetMemberSegments(/*[in]*/Float64 Length, /*[in]*/VARIANT_BOOL isSymmetrical, /*[out,retval]*/IFilteredSegmentCollection* * collection);
	HRESULT GetSegments(/*[out,retval]*/IFilteredSegmentCollection* *);
	HRESULT GetDistanceFromStartOfSegment(/*[in]*/Float64 Length, /*[in]*/VARIANT_BOOL isSymmetrical, /*[in]*/Float64 location, /*[out]*/ Float64* dist,/*[out]*/ISegmentItem** ppSeg);
	HRESULT Reverse();
   HRESULT RemoveSegments();
	HRESULT Remove(/*[in]*/CollectionIndexType index);
	HRESULT CopyTo(/*[in]*/CollectionIndexType fromIndex, /*[in]*/CollectionIndexType toIndex);
	HRESULT MoveTo(/*[in]*/CollectionIndexType fromIndex, /*[in]*/CollectionIndexType toIndex);
	HRESULT Insert(/*[in]*/CollectionIndexType relPosition, /*[in]*/ISegment* segment);
	HRESULT Add(/*[in]*/ISegment* segment);
	HRESULT get_Segment(/*[in]*/CollectionIndexType relPosition, /*[out, retval]*/ ISegment* *pVal);
	HRESULT get_Count(/*[out, retval]*/ CollectionIndexType *pVal);
	HRESULT get_Length(/*[out, retval]*/ Float64 *pVal);

   void Clear();

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);


   typedef  ISegmentItem* ItemType;
private:
   CSegments();

// data members               cookie
   //typedef std::pair< DWORD, CAdapt<CComPtr<ISegmentItem> > > StoredType; 
   typedef CAdapt<CComPtr<ISegmentItem>> StoredType; 
   typedef std::vector<StoredType> VectorType;
   typedef VectorType::iterator  VectorIteratorType;

   VectorType m_Segments;

   bool m_bFractional; // keeps track of the current state of length measurement

   // pointer back to our owner
   CSegmentsOwner* m_pOwner;

   IGenericBridge* m_pBridge;// weak referce to bridge

// utility functions
   void UpdateRelPositions(CSegments::VectorType* pvec);

   void MakeFractional(bool bFractional);

// Classes for local C++ clients
public:

   // iterator class for iterating entire collection

   class iterator
   {
      friend CSegments;
   private:
      VectorIteratorType    m_vit;
      CSegments*          m_pColl;

   public:
		iterator& operator++()
      {
         // a bit tricky here since we're iterating through a nested collection
         m_vit++;
         return (*this); 
      }

      // postfix
		iterator operator++(int)
      {
         ++m_vit;
			return (*this); 
      }

		ItemType& operator*() const
      {
         return m_vit->m_T.p;   // dangerous here, but what we must do to compile
      }

		ItemType& operator->() const
      {
         return m_vit->m_T.p;
      }

		bool operator==(const iterator& rit) const
		{
         return (m_vit==rit.m_vit);
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
      it.m_vit = m_Segments.begin();

      return it;
   }

   iterator end()
   {
      iterator it;
      it.m_pColl = this;
      it.m_vit = m_Segments.end();

      return it;
   }

   friend iterator; // this is NOT VERY OBVIOUS HERE!!! , but it won't compile elsewhere
};

#endif //__SEGMENTS_H_
