///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

#pragma once

class CSuperstructureMemberSegmentImpl
{
public:
   CSuperstructureMemberSegmentImpl();

   ////////////////////////////////////////////////////////////////////////
   // ISuperstructureMemberSegment implementation
   STDMETHOD(putref_SuperstructureMember)(ISuperstructureMember* ssMbr);
   STDMETHOD(get_SuperstructureMember)(ISuperstructureMember** ssMbr);
   STDMETHOD(putref_GirderLine)(IGirderLine* girderLine);
   STDMETHOD(get_GirderLine)(IGirderLine** girderLine);
   STDMETHOD(putref_PrevSegment)(ISegment* segment);
   STDMETHOD(get_PrevSegment)(ISegment** segment);
   STDMETHOD(putref_NextSegment)(ISegment* segment);
   STDMETHOD(get_NextSegment)(ISegment** segment);
   //STDMETHOD(get_Section)(StageIndexType stageIdx, Float64 distAlongSegment, ISection** ppSection);
   //STDMETHOD(get_PrimaryShape)(Float64 distAlongSegment, IShape** ppShape);
   //STDMETHOD(get_Profile)(VARIANT_BOOL bIncludeClosure, IShape** ppShape);
   STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(get_LayoutLength)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_Orientation)(/*[in]*/Float64 orientation);
   STDMETHOD(get_Orientation)(/*[out,retval]*/Float64* orientation);
   STDMETHOD(GetHaunchDepth)(Float64* pStartVal,Float64* pMidVal,Float64* pEndVal);
   STDMETHOD(SetHaunchDepth)(Float64 startVal,Float64 midVal,Float64 endVal);
   STDMETHOD(ComputeHaunchDepth)(Float64 distAlongSegment,Float64* pVal);
   STDMETHOD(put_Fillet)(/*[in]*/Float64 Fillet);
   STDMETHOD(get_Fillet)(/*[out,retval]*/Float64* Fillet);
   STDMETHOD(put_FilletShape)(/*[in]*/FilletShape FilletShape);
   STDMETHOD(get_FilletShape)(/*[out,retval]*/FilletShape* FilletShape);
   STDMETHOD(put_Precamber)(/*[in]*/Float64 precamber);
   STDMETHOD(get_Precamber)(/*[out,retval]*/Float64* pPrecamber);
   STDMETHOD(ComputePrecamber)(/*[in]*/Float64 distAlongSegment, /*[out,retval]*/Float64* pPrecamber);

public:
   IGirderLine* m_pGirderLine; // weak reference to the girder line in the geometry model that provies the geometry for this segment
   ISuperstructureMember* m_pSSMbr; // weak reference to parent superstructure member
   ISuperstructureMemberSegment* m_pPrevSegment; // weak reference to previous segment
   ISuperstructureMemberSegment* m_pNextSegment; // weak reference to next segment

   Float64 m_Orientation; // orientation of girder... plumb = 0... rotated CW is +... radians
   Float64 m_HaunchDepth[3];
   // Can determine how to compute haunch depth at set time
   enum HaunchMode { hmPrismatic, hmLinear, hmParabolic } m_HaunchMode;
   Float64 m_Fillet;
   FilletShape m_FilletShape;
   Float64 m_Precamber;

   Float64 ComputePrecamber(Float64 Xs, Float64 Ls);
};
