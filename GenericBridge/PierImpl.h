///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

class mathPwLinearFunction2dUsingPoints;

class CPierImpl
{
public:
   HRESULT FinalConstruct(IPier* pPier);

private:
   void SetItems(ICrossBeam* pCrossBeam,IBearingLayout* pBearingLayout,IColumnLayout* pLayout);
   Float64 GetSkewAngle();
   Float64 GetDelta();

   bool m_bIsDirty;
   Float64 m_Delta;

// IPier (partial implementation)
public:
   HRESULT put_Type(/*[in]*/PierType type);
   HRESULT get_Type(/*[out,retval]*/PierType* type);
   //HRESULT get_DeckElevation(/*[out,retval]*/Float64* pElev);
   //HRESULT get_CrownPointOffset(/*[out,retval]*/Float64* pCPO);
   //HRESULT get_CrownSlope(/*[in]*/DirectionType side,/*[out,retval]*/Float64* pSlope);
   //HRESULT get_CurbLineOffset(/*[in]*/DirectionType side,/*[in]*/CurbLineMeasurementType clMeasure,/*[out,retval]*/Float64* pCLO);
   HRESULT get_CurbToCurbWidth(/*[in]*/CurbLineMeasurementType clMeasure,/*[out,retval]*/Float64* pWcc);
   HRESULT putref_SkewAngle(/*[in]*/IAngle* pSkew);
   HRESULT get_SkewAngle(/*[out,retval]*/ IAngle* *skewAngle);
   HRESULT putref_CrossBeam(/*[in]*/ICrossBeam* pCrossBeam);
   HRESULT get_CrossBeam(/*[out,retval]*/ICrossBeam** ppCrossBeam);
   HRESULT putref_BearingLayout(/*[in]*/IBearingLayout* pBearingLayout);
   HRESULT get_BearingLayout(/*[out,retval]*/IBearingLayout** ppBearingLayout);
   HRESULT putref_ColumnLayout(/*[in]*/IColumnLayout* pColumnLayout);
   HRESULT get_ColumnLayout(/*[out,retval]*/IColumnLayout** ppColumnLayout);
   HRESULT get_Column(/*[in]*/ ColumnIndexType columnIdx,/*[out,retval]*/IColumn* *column);
   HRESULT ConvertCrossBeamToCurbLineCoordinate(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pXcl);
   HRESULT ConvertCurbLineToCrossBeamCoordinate(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pXxb);
   HRESULT ConvertPierToCrossBeamCoordinate(/*[in]*/Float64 Xp,/*[out,retval]*/Float64* pXxb);
   HRESULT ConvertCrossBeamToPierCoordinate(/*[in]*/Float64 Xxb,/*[out,retval]*/Float64* pXp);
   HRESULT ConvertPierToCurbLineCoordinate(/*[in]*/Float64 Xp,/*[out,retval]*/Float64* pXcl);
   HRESULT ConvertCurbLineToPierCoordinate(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pXp);
   HRESULT get_Elevation(/*[in]*/Float64 Xcl,/*[out,retval]*/Float64* pElev);
   HRESULT get_CurbLineElevation(/*[in]*/DirectionType side,/*[out,retval]*/Float64* pElev);

public:
   IPier* m_pPier; // weak reference
   PierType m_Type;
   CComPtr<IAngle> m_Skew;
   CComPtr<ICrossBeam> m_CrossBeam;
   CComPtr<IBearingLayout> m_BearingLayout;
   CComPtr<IColumnLayout> m_ColumnLayout;

   void CreateDeckProfileFunction(mathPwLinearFunction2dUsingPoints* pFN);
};