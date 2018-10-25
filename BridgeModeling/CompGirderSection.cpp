///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2014  Washington State Department of Transportation
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfCompGirderSection
****************************************************************************/

#include <BridgeModeling\CompGirderSection.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bmfCompGirderSection::bmfCompGirderSection(const gmIShape* pGdrShape,
                                           const matConcreteEx* pGdrConc,
                                           Float64 tribWidth,Float64 effWidth,
                                           Float64 grossDepth,Float64 sacDepth,
                                           const matConcreteEx* pSlabConc)
{
   PRECONDITION( tribWidth+1.0e-05 >= effWidth );

   m_pGdrShape  = pGdrShape;
   m_pGdrConc   = pGdrConc;
   m_pSlabConc  = pSlabConc;

   m_TribWidth  = tribWidth;
   m_EffWidth   = effWidth;
   m_GrossDepth = grossDepth;
   m_SacDepth   = sacDepth;
   m_bUpdateProperties = true;
}

bmfCompGirderSection::bmfCompGirderSection(const bmfCompGirderSection& rOther)
{
   m_bUpdateProperties = true;
   MakeCopy(rOther);
}

bmfCompGirderSection::~bmfCompGirderSection()
{
}

//======================== OPERATORS  =======================================
bmfCompGirderSection& bmfCompGirderSection::operator= (const bmfCompGirderSection& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
bmfGirderSection* bmfCompGirderSection::CreateClone() const
{
   return new bmfCompGirderSection( m_pGdrShape,
                                    m_pGdrConc,
                                    m_TribWidth,
                                    m_EffWidth,
                                    m_GrossDepth,
                                    m_SacDepth,
                                    m_pSlabConc);
}

gmElasticProperties bmfCompGirderSection::GetElasticProperties() const
{
   if ( m_bUpdateProperties )
      UpdateProperties();

   return m_Props;
}

void bmfCompGirderSection::Draw(HDC hdc,const grlibPointMapper& mapper) const
{
   m_Section.Draw( hdc, mapper );
}

Float64 bmfCompGirderSection::GetStopGirder() const
{
   if ( m_bUpdateProperties )
      UpdateProperties();

   return m_StopGirder;
}

Float64 bmfCompGirderSection::GetYtopGirder() const
{
   if ( m_bUpdateProperties )
      UpdateProperties();

   return m_YtopGirder;
}

Float64 bmfCompGirderSection::GetQslab() const
{
   if ( m_bUpdateProperties )
      UpdateProperties();

   return m_Qslab;
}

//======================== ACCESS     =======================================

void bmfCompGirderSection::SetGirderShape(const gmIShape* pGdrShape)
{
   m_pGdrShape = pGdrShape;
   m_bUpdateProperties = true;
}

const gmIShape* bmfCompGirderSection::GetGirderShape() const
{
   return m_pGdrShape;
}

void bmfCompGirderSection::SetTribWidth( Float64 tribWidth )
{
   m_TribWidth = tribWidth;
   m_bUpdateProperties = true;
}

Float64 bmfCompGirderSection::GetTribWidth() const
{
   return m_TribWidth;
}

void bmfCompGirderSection::SetEffWidth( Float64 effWidth )
{
   m_EffWidth = effWidth;
   m_bUpdateProperties = true;
}

Float64 bmfCompGirderSection::GetEffWidth() const
{
   return m_EffWidth;
}

void bmfCompGirderSection::SetGrossDepth( Float64 grossDepth )
{
   m_GrossDepth = grossDepth;
   m_bUpdateProperties = true;
}

Float64 bmfCompGirderSection::GetGrossDepth() const
{
   return m_GrossDepth;
}

void bmfCompGirderSection::SetSacrificialDepth( Float64 sacDepth )
{
   m_SacDepth = sacDepth;
   m_bUpdateProperties = true;
}

Float64 bmfCompGirderSection::GetSacrificialDepth() const
{
   return m_SacDepth;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfCompGirderSection::MakeCopy(const bmfCompGirderSection& rOther)
{
   m_pGdrShape  = rOther.m_pGdrShape;
   m_pGdrConc   = rOther.m_pGdrConc;
   m_pSlabConc  = rOther.m_pSlabConc;
   m_TribWidth  = rOther.m_TribWidth;
   m_EffWidth   = rOther.m_EffWidth;
   m_GrossDepth = rOther.m_GrossDepth;
   m_SacDepth   = rOther.m_SacDepth;

   m_bUpdateProperties = true;
}

void bmfCompGirderSection::MakeAssignment(const bmfCompGirderSection& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfCompGirderSection::UpdateProperties() const
{
   Float64 Eg, Es;
   Float64 density;

   m_Section.RemoveAllComponents();

   Eg = m_pGdrConc->GetE();
   density = m_pGdrConc->GetDensityForWeight();
   m_Section.AddComponent( *m_pGdrShape, Eg, density );

   Es = m_pSlabConc->GetE();
   density = m_pSlabConc->GetDensityForWeight();

   gpPoint2d gdr_top_center = m_pGdrShape->GetLocatorPoint( gmIShape::TopCenter );


   // Main Slab
   Float64 w, h;
   w = m_EffWidth;
   h = m_GrossDepth - m_SacDepth;
   gmRectangle main_slab( gpPoint2d(0,0), w, h );
   main_slab.Move( gmIShape::BottomCenter, gdr_top_center );

   // Left and right block ( accounts for difference in width between effective and trib
   // slab width)
   w = (m_TribWidth - m_EffWidth) / 2.0;
   if (w<0.0 && IsZero(w,0.001)) 
      w=0.0;
   CHECK(w>=0.0);
   gmRectangle left_block( gpPoint2d(0,0), w, h );
   gmRectangle right_block( gpPoint2d(0,0), w, h );
   left_block.Move( gmIShape::TopRight, main_slab.GetLocatorPoint( gmIShape::TopLeft ) );
   right_block.Move( gmIShape::TopLeft, main_slab.GetLocatorPoint( gmIShape::TopRight ) );

   // Sacrifical wearing surface
   w = m_TribWidth;
   h = m_SacDepth;
   gmRectangle sac( gpPoint2d(0,0), w, h );
   sac.Move( gmIShape::BottomCenter, main_slab.GetLocatorPoint( gmIShape::TopCenter ) );

   CHECK( left_block.GetLocatorPoint( gmIShape::TopLeft ) ==
          sac.GetLocatorPoint( gmIShape::BottomLeft ) );

   CHECK( right_block.GetLocatorPoint( gmIShape::TopRight ) ==
          sac.GetLocatorPoint( gmIShape::BottomRight ) );

   // Add the slab components to the section object.
   m_Section.AddComponent( main_slab,   Es, density );
   // the following are non-structural
   m_Section.AddComponent( left_block,  Es, density, false );
   m_Section.AddComponent( right_block, Es, density, false );
   m_Section.AddComponent( sac,         Es, density, false );

   m_Section.GetElasticProperties( &m_Props );


   // Compute Ytop girder
   gmProperties prop;
   m_pGdrShape->GetProperties( &prop );
   Float64 h_girder = prop.Ytop() - prop.Ybottom(); // Ybottom is neg.
   m_YtopGirder = h_girder + m_Props.Ybottom();

   // Compute Stop girder
   Float64 EIxx = m_Props.EIxx();
   Float64 Ixx = EIxx / m_pGdrConc->GetE();

   m_StopGirder = -Ixx / m_YtopGirder;

   // Compute Qslab
   m_Qslab = (Es/Eg)*m_EffWidth*(m_GrossDepth - m_SacDepth)*(m_YtopGirder + (m_GrossDepth-m_SacDepth)/2.0);
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

