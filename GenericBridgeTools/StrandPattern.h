// StrandPattern.h : Declaration of the CStrandPattern

#ifndef __STRANDPATTERN_H_
#define __STRANDPATTERN_H_

#include "resource.h"       // main symbols
#include <vector>
#include <set>
#include <MathEx.h>

/////////////////////////////////////////////////////////////////////////////
// CStrandPattern
class ATL_NO_VTABLE CStrandPattern : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStrandPattern, &CLSID_StrandPattern>,
	public ISupportErrorInfo,
	public IStrandPattern,
   public IObjectSafetyImpl<CStrandPattern,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CStrandPattern()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_STRANDPATTERN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrandPattern)
	COM_INTERFACE_ENTRY(IStrandPattern)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   CComPtr<IPoint2dCollection> m_PatternPoints;
   VARIANT_BOOL m_bReflectionEnabled;

   struct StrandPoint
   {
      StrandPoint(IPoint2d* point) { Point = point; FillSequence = -1; bHasStrand = false; bIsDebonded = false; }

      bool operator==(const StrandPoint& rOther)
      { return FillSequence == rOther.FillSequence && bHasStrand == rOther.bHasStrand && bIsDebonded == rOther.bIsDebonded; }

      CComPtr<IPoint2d> Point;
      long FillSequence;
      bool bHasStrand;
      bool bIsDebonded;
      double DebondLength[2]; // both ends of the strand
   };
   std::vector<StrandPoint> m_StrandPoints;

   struct Row
   {
      double Elevation;
      std::vector<long> StrandPoints;
      bool operator==(const Row& rOther) const { ::IsEqual(Elevation,rOther.Elevation); }
      bool operator<(const Row& rOther) const { return Elevation < rOther.Elevation; }
   };

   std::set<Row> m_Rows;

   struct Section
   {
      double Location;
      std::set<long> StrandPoint;
      bool operator==(const Section& rOther) const { ::IsEqual(Location,rOther.Location); }
      bool operator<(const Section& rOther) const { return Location < rOther.Location; }
   };
   std::set<Section> m_LeftSections, m_RightSections;

   void AddDebondSection(long strandIdx,double left,double right);

   CComPtr<IRect2d> m_PatternBoundingBox;
   bool m_bUpdatePatternBoundingBox;

   CComPtr<IRect2d> m_StrandBoundingBox;
   bool m_bUpdateStrandBoundingBox;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStrandPattern
public:
   STDMETHOD(AddPatternPoint)(/*[in]*/IPoint2d* point);
	STDMETHOD(AddPatternPoints)(/*[in]*/IPoint2dCollection* points);
	STDMETHOD(get_PatternPointCount)(/*[out,retval]*/long* count);
	STDMETHOD(get_PatternPoint)(/*[in]*/ long idx,/*[out,retval]*/IPoint2d** point);
	STDMETHOD(get_PatternPoints)(/*[out,retval]*/IPoint2dCollection** point2);
	STDMETHOD(RemovePatternPoint)(/*[in]*/ long idx);
	STDMETHOD(ClearPatternPoints)();
	   
	STDMETHOD(EnablePointReflection)(/*[in]*/ VARIANT_BOOL bEnable);
	STDMETHOD(IsPointReflectionEnabled)(/*[out,retval]*/ VARIANT_BOOL* bEnable);

   STDMETHOD(get_StrandPointCount)(/*[out,retval]*/long* count);
   STDMETHOD(get_MaxStrandCount)(/*[out,retval]*/long* count);

	STDMETHOD(get_StrandPatternPoint)(/*[in]*/long idx,/*[out,retval]*/IPoint2d** point);
	STDMETHOD(get_StrandPoint)(/*[in]*/long idx,/*[out,retval]*/IPoint2d** point);
	STDMETHOD(AddStrand)(/*[out,retval]*/long* nAdded);
	STDMETHOD(RemoveStrand)(/*[out,retval]*/long* nRemoved);
	STDMETHOD(RemoveAllStrands)();
	STDMETHOD(TestStrandCount)(/*[in]*/ long nStrands,/*[out,retval]*/long* nValid);
	STDMETHOD(SetStrandCount)(/*[in]*/ long nStrands,/*[out,retval]*/long* nResult);
	STDMETHOD(GetStrandCount)(/*[out,retval]*/long* nStrands);

	STDMETHOD(get_RowsWithStrand)(/*[out,retval]*/long* nRows);
	STDMETHOD(get_StrandsInRow)(/*[in]*/long rowIdx,/*[out,retval]*/long* nStrands);

	STDMETHOD(AddDebondedStrand)(/*[in]*/ double l1,/*[in]*/ double l2,/*[out,retval]*/long* nAdded);
	STDMETHOD(IsDebonded)(/*[in]*/ long index,/*[out,retval]*/ VARIANT_BOOL* bResult);
	STDMETHOD(DebondStrand)(/*[in]*/ long index,/*[in]*/ double l1,/*[in]*/ double l2);
	STDMETHOD(BondStrand)(/*[in]*/ long index);
	STDMETHOD(GetDebondLength)(/*[in]*/ long index,/*[out]*/double* l1,/*[out]*/ double* l2);
   STDMETHOD(get_DebondStrandsInRow)(/*[in]*/ long rowIdx,/*[out,retval]*/long* nStrands);
   STDMETHOD(IsExteriorStrandDebondedInRow)(/*[in]*/ long rowIndex,/*[out,retval]*/VARIANT_BOOL* bResult);
   STDMETHOD(GetDebondStrandCount)(/*[out,retval]*/long* nDebondedStrands);

   STDMETHOD(GetDebondSections)(/*[out]*/IDblArray** left,/*[out]*/ IDblArray** right);
	STDMETHOD(DebondStrandsAtLeftSection)(/*[in]*/long sectionIdx,/*[out,retval]*/long* nDebondedStrands);
	STDMETHOD(DebondStrandsAtRightSection)(/*[in]*/long sectionIdx,/*[out,retval]*/long* nDebondedStrands);


	STDMETHOD(get_CG)(/*[in]*/double distFromStart,/*[in]*/double gdrLength,/*[out,retval]*/IPoint2d** cg);
	STDMETHOD(get_CGEx)(/*[in]*/ long nStrands,/*[in]*/double distFromStart,/*[in]*/double gdrLength,/*[out,retval]*/IPoint2d** cg);

   STDMETHOD(get_PatternBoundingBox)(/*[out,retval]*/IRect2d** box);
   STDMETHOD(get_StrandBoundingBox)(/*[out,retval]*/IRect2d** box);
};

#endif //__STRANDPATTERN_H_
