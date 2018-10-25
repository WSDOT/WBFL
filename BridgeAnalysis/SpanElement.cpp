///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>
#include <BridgeAnalysis\SpanElement.h>
#include <BridgeAnalysis\BridgeModel.h>
#include <BridgeAnalysis\SupportElement.h>
#include <BridgeAnalysis\Load.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bamSpanElement::bamSpanElement(const bamSpanElementInfo& rSpanElementInfo)
{
   CHECKX( false, _T("Don't use this c'tor yet"));
}

bamSpanElement::bamSpanElement(SpanIDType id,Float64 ax,Float64 iz,Float64 mode,Float64 density)
{
   m_pModel = 0;

   m_ID = id;
   m_Ax = ax;
   m_Iz = iz;
   m_ModE = mode;
   m_Density = density;
   m_pStartSupport = 0;
   m_pEndSupport = 0;

   m_Color = RGB(0,0,0); // black
}

bamSpanElement::~bamSpanElement()
{
}

SpanIDType bamSpanElement::GetID() const
{
   return m_ID;
}

Float64 bamSpanElement::GetAx() const
{
   return m_Ax;
}

Float64 bamSpanElement::GetIz() const
{
   return m_Iz;
}

Float64 bamSpanElement::GetModE() const
{
   return m_ModE;
}

Float64 bamSpanElement::GetDensity() const
{
   return m_Density;
}

Float64 bamSpanElement::Length() const
{
   Float64 x1, x2;
   x2 = m_pEndSupport->GetLocation();
   x1 = m_pStartSupport->GetLocation();

   return (x2-x1);
}

void bamSpanElement::GetSpanElementInfo(bamSpanElementInfo& rSpanElementInfo) const
{
   PRECONDITION( rSpanElementInfo.m_SegmentCount != 0 );
   PRECONDITION( rSpanElementInfo.m_pSegmentInfo != 0 );

   rSpanElementInfo.m_Id = GetID();
   rSpanElementInfo.m_pSegmentInfo[0].m_Ax = GetAx();
   rSpanElementInfo.m_pSegmentInfo[0].m_Iz = GetIz();
   rSpanElementInfo.m_pSegmentInfo[0].m_ModE = GetModE();
   rSpanElementInfo.m_pSegmentInfo[0].m_Density = GetDensity();

   if (m_pStartSupport)
     rSpanElementInfo.m_StartSupportId = m_pStartSupport->GetID();
   else
     rSpanElementInfo.m_StartSupportId = -1;

   if (m_pEndSupport)
      rSpanElementInfo.m_EndSupportId = m_pEndSupport->GetID();
   else
      rSpanElementInfo.m_EndSupportId = -1;
}

void bamSpanElement::SetStartSupport(bamSupportElement* pSupportElement)
{
   if (m_pStartSupport)
      m_pStartSupport->RemoveSpanElement(this);

   m_pStartSupport = pSupportElement;
   m_pStartSupport->AddSpanElement( this );
}

bamSupportElement* bamSpanElement::GetStartSupport() const
{
   return m_pStartSupport;
}

void bamSpanElement::SetEndSupport(bamSupportElement* pSupportElement)
{
   if (m_pEndSupport)
      m_pEndSupport->RemoveSpanElement(this);

   m_pEndSupport = pSupportElement;
   m_pEndSupport->AddSpanElement( this );
}

bamSupportElement* bamSpanElement::GetEndSupport() const
{
   return m_pEndSupport;
}

const bamSupportElement& bamSpanElement::StartSupport() const
{
   return *m_pStartSupport;
}

const bamSupportElement& bamSpanElement::EndSupport() const
{
   return *m_pEndSupport;
}

void bamSpanElement::RemoveSupportElement(bamSupportElement* pSupportElement)
{
   if ( m_pStartSupport &&
        m_pStartSupport->GetID() == pSupportElement->GetID())
     m_pStartSupport = 0;

   if ( m_pEndSupport &&
        m_pEndSupport->GetID() == pSupportElement->GetID())
     m_pEndSupport = 0;
}

void bamSpanElement::OnRemove()
{
   // I am being removed from the model, so I must notify
   // the supports that I rest on, and then I must terminate
   // my relationship with those supports.

   if (m_pStartSupport)
      m_pStartSupport->RemoveSpanElement(this);

   if (m_pEndSupport)
      m_pEndSupport->RemoveSpanElement(this);

   m_pStartSupport = 0;
   m_pEndSupport = 0;
}

bamSpanElement* bamSpanElement::Clone() const
{
   return new bamSpanElement(GetID(),GetAx(),GetIz(),GetModE(),GetDensity());
}

void bamSpanElement::SetModel(bamBridgeModel* pModel)
{
   m_pModel = pModel;
}

bamLoad* bamSpanElement::GetSelfWeightLoad()
{
   bamLoadFactory& rLoadFactory = m_pModel->GetLoadFactory();
   bamGravityDirection gravity = m_pModel->GetGravityDirection();

   CHECK(gravity == PositiveY || gravity == NegativeY); // Only Y direction supported for now

   Float64 w = GetAx() * GetDensity() * m_pModel->GetGravitionalAcceleration();
   w *= (gravity == NegativeY ? -1 : 1);

   // Should be using a global projection
   bamLoad* pLoad = rLoadFactory.DoCreateUnifForceY(m_ID,etSpan,0.0,1.0,w,true,Global);

   return pLoad;
} // GetSelfWeightLoad

void bamSpanElement::Draw(HDC hDC,const grlibPointMapper& mapper) const
{
   Float64 wx,wy;
   LONG dx,dy;
   LONG x1, x2;
   HPEN hOldPen,hPen;

   hPen = CreatePen(PS_SOLID,3,m_Color);
   hOldPen = (HPEN)::SelectObject(hDC,hPen);

   wy = 0;
   wx = m_pStartSupport->GetLocation();
   mapper.WPtoDP(wx,wy,&dx,&dy);
   ::MoveToEx(hDC,dx,dy,NULL);
   x1 = dx;

   wx =  m_pEndSupport->GetLocation();
   mapper.WPtoDP(wx,wy,&dx,&dy);
   ::LineTo(hDC,dx,dy);
   x2 = dx;

   TCHAR buffer[50];
   _stprintf_s(buffer,50,_T("%f"),Length());
   ::TextOut(hDC,(x1+x2)/2, dy + 10,buffer,(int)_tcslen(buffer));

   ::SelectObject(hDC,hOldPen);
   ::DeleteObject(hPen);
} // Draw

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamSpanElement::AssertValid() const
{
   return true;
}

void bamSpanElement::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamSpanElement" << endl;
   os << "m_ID          = " << m_ID << endl;
   os << "Start Support = " << m_pStartSupport->GetID() << endl;
   os << "End   Support = " << m_pEndSupport->GetID() << endl;
   os << "m_Ax          = " << m_Ax << endl;
   os << "m_Iz          = " << m_Iz << endl;
   os << "m_ModE        = " << m_ModE << endl;
   os << "m_Density     = " << m_Density << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bamSpanElement::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamSpanElement");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamSpanElement");

   TESTME_EPILOG("SpanElement");
}
#endif // _UNITTEST
