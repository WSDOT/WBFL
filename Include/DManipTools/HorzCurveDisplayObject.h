///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2018  Washington State Department of Transportation
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

#ifndef INCLUDED_HORZCURVEDISPLAYOBJECT_H_
#define INCLUDED_HORZCURVEDISPLAYOBJECT_H_
#pragma once

interface IHorzCurve;

enum HorzCurveDrawMode
{
	hcCurveOnly,
	hcCurveWithTangents,
	hcFull
};

// {02F9ADCE-5FCF-4519-9783-6C78A1483E35}
DEFINE_GUID(IID_iHorzCurveDisplayObject, 
0x2f9adce, 0x5fcf, 0x4519, 0x97, 0x83, 0x6c, 0x78, 0xa1, 0x48, 0x3e, 0x35);
struct __declspec(uuid("{02F9ADCE-5FCF-4519-9783-6C78A1483E35}")) iHorzCurveDisplayObject;
interface iHorzCurveDisplayObject : public iDisplayObject
{
   STDMETHOD_(void,putref_HorzCurve)(IHorzCurve* hc,BOOL bRedraw,BOOL bFireEvent) PURE;
   STDMETHOD_(void,get_HorzCurve)(IHorzCurve* *hc) PURE;

   STDMETHOD_(void,put_DrawMode)(HorzCurveDrawMode mode) PURE;
   STDMETHOD_(void,get_DrawMode)(HorzCurveDrawMode* mode) PURE;

   // Font for labels. Note that font height is in 10th of points.
   // Note that Title is drawn in bold version of same font
   STDMETHOD_(void,put_Font)(const LOGFONT& Font) PURE;
   STDMETHOD_(void,get_Font)(LOGFONT* pFont) PURE;
};

#endif // INCLUDED_HORZCURVEDISPLAYOBJECT_H_