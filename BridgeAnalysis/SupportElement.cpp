///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2011  Washington State Department of Transportation
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
#include <BridgeAnalysis\SupportElement.h>
#include <BridgeAnalysis\BridgeModel.h>
#include <BridgeAnalysis\SpanElement.h>
#include <BridgeAnalysis\Load.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bamSupportElement::bamSupportElement(const bamSupportElementInfo& rSupportElementInfo)
{
   m_pModel = 0;
   m_ID = rSupportElementInfo.m_SupportElementId;
   m_Location = rSupportElementInfo.m_Location;
   m_Fixity = rSupportElementInfo.m_SupportFixity;

   m_Color = RGB(0,0,255); // blue
   m_SupportSize = 125; // 1/8"
}

bamSupportElement::bamSupportElement(SupportIDType id,Float64 location,bamSupportFixity fixity)
{
   m_pModel = 0;

   m_ID = id;
   m_Location = location;
   m_Fixity = fixity;

   m_Color = RGB(0,0,255); // blue
   m_SupportSize = 125; // 1/8"
}

bamSupportElement::~bamSupportElement()
{
}

void bamSupportElement::GetSupportElementInfo(bamSupportElementInfo& rSupportElementInfo) const
{
   rSupportElementInfo.m_SupportElementId = GetID();
   rSupportElementInfo.m_Location = GetLocation();
   rSupportElementInfo.m_SupportFixity = GetFixity();
}

Float64 bamSupportElement::GetLocation() const
{
   return m_Location;
}

bamSupportFixity bamSupportElement::GetFixity() const
{
   return m_Fixity;
}

bamSupportElement* bamSupportElement::Clone() const
{
   return new bamSupportElement(m_ID,GetLocation(),GetFixity());
}

bamLoad* bamSupportElement::GetSelfWeightLoad()
{
   return 0;
} // GetSelfWeightLoad

void bamSupportElement::Draw(HDC hDC,const grlibPointMapper& mapper) const
{
   Float64 wx,wy;
   LONG dx,dy;

   wy = 0;
   wx = GetLocation();
   mapper.WPtoDP(wx,wy,&dx,&dy);

   int map_mode;
   HPEN hOldPen, hPen;
   HBRUSH hOldBrush,  hBrush;

   // Setup DC
   map_mode = ::SetMapMode(hDC,MM_HIENGLISH);
   hPen = ::CreatePen(PS_SOLID,1,m_Color);
   hBrush = ::CreateSolidBrush( m_Color );
   hOldPen = (HPEN)::SelectObject(hDC,hPen);
   hOldBrush  = (HBRUSH)::SelectObject(hDC,hBrush);

   POINT p;
   p.x = dx;
   p.y = dy;
   ::DPtoLP(hDC,&p,1);

   switch( GetFixity() )
   {
   case Pin:
        POINT point[3];
        point[0].x = p.x;
        point[0].y = p.y;
        point[1].x = p.x + (866 * m_SupportSize) / 1000; // Sin 60
        point[1].y = p.y - m_SupportSize;
        point[2].x = p.x - (866 * m_SupportSize) / 1000;
        point[2].y = p.y - m_SupportSize;
        ::Polygon(hDC,point,sizeof(point)/sizeof(POINT));
        break;

   case HRoller:
        RECT rect;
        rect.left   = p.x - m_SupportSize/2;
        rect.right  = p.x + m_SupportSize/2;
        rect.top    = p.y;
        rect.bottom = p.y - m_SupportSize;
        ::Ellipse(hDC,rect.left,rect.top,rect.right,rect.bottom);
        break;

   default:
        CHECKX( false, _T("Unknown support type encountered"));
        break;
   }

   // Clean up
   ::SelectObject(hDC,hOldPen);
   ::SelectObject(hDC,hOldBrush);
   ::DeleteObject(hPen);
   ::DeleteObject(hBrush);
   ::SetMapMode(hDC,map_mode);
} // Draw

void bamSupportElement::AddSpanElement(bamSpanElement* pSpanElement)
{
   m_SpanElements.insert( std::pair<SpanIDType,bamSpanElement*>(pSpanElement->GetID(),
                                                  pSpanElement) );
}

void bamSupportElement::RemoveSpanElement(bamSpanElement* pSpanElement)
{
   m_SpanElements.erase( pSpanElement->GetID() );
}

void bamSupportElement::OnRemove()
{
   // Tell every SpanElement that connects to me that
   // I am about to be removed from the model.
   SpanElementIterator begin = m_SpanElements.begin();
   SpanElementIterator end   = m_SpanElements.end();

   while ( begin != end )
   {
      bamSpanElement* pSpanElement = (*begin++).second;
      pSpanElement->RemoveSupportElement(this);
   }
}

void bamSupportElement::SetModel(bamBridgeModel* pModel)
{
   m_pModel = pModel;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bamSupportElement::AssertValid() const
{
   return true;
}

void bamSupportElement::Dump(dbgDumpContext& os) const
{
   os << "Dump for bamSupportElement" << endl;
   os << "m_ID = " << m_ID << endl;
   os << "m_Location = " << m_Location << endl;

   os << "m_Fixity = ";
   switch( m_Fixity )
   {
   case Pin:
      os << "Pin";
      break;
      
   case HRoller:
      os << "HRoller";
      break;
      
   case VRoller:
      os << "VRoller";
      break;
      
   case Fixed:
      os << "Fixed";
      break;
      
   case HGuide:
      os << "HGuide";
      break;
      
   case VGuide:
      os << "VGuide";
      break;
   }
   os << endl;


}
#endif // _DEBUG

#if defined _UNITTEST
bool bamSupportElement::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bamSupportElement");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bamSupportElement");

   TESTME_EPILOG("SupportElement");
}
#endif // _UNITTEST
