///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#include <Reporter\ReporterLib.h>
#include <Reporter\RiStyle.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptRiStyle           
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

rptRiStyle::rptRiStyle()
{
   Init();

} // rptRiStyle

rptRiStyle::rptRiStyle(FontType fontType,
                       Uint16 fontSize,
                       bool bBold,
                       bool bItalic, 
                       bool bUnderlined,
                       FontColor fontColor,
                       AlignmentType alignType,
                       VerticalAlignmentType valignType)
{
   Init();

   m_Font = fontType;
   m_FontSize = fontSize;
   SetBold( bBold );
   SetItalic( bItalic );
   SetUnderlined( bUnderlined );
   SetColor( fontColor );
   SetBGColor( White );
   SetAlignment( alignType );
   SetVerticalAlignment(valignType);
}


rptRiStyle::rptRiStyle(const rptRiStyle& rOther)
{
   Init();
   MakeCopy( rOther );
} // rptRiStyle

rptRiStyle::~rptRiStyle()
{
} // ~rptRiStyle

//======================== OPERATORS  =======================================

rptRiStyle& rptRiStyle::operator = (const rptRiStyle& rOther)
{
   if ( this != &rOther )
      MakeAssignment(rOther);

   return *this;
} // operator =

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void rptRiStyle::SetFontType( FontType fontType )
{
   m_Font = fontType;
}

void rptRiStyle::SetFontSize( Uint16 fontSize )
{
   m_FontSize = fontSize;
}

void rptRiStyle::SetAlignment( AlignmentType alignType )
{
   m_Alignment = alignType;
}

void rptRiStyle::SetVerticalAlignment( VerticalAlignmentType valignType )
{
   m_VAlignment = valignType;
}

void rptRiStyle::SetUnderlined( bool bUnderline )
{
   m_FontModifiers.set(UNDERLINE, bUnderline);
}

void rptRiStyle::SetBold ( bool bBold )
{
   m_FontModifiers.set(BOLD, bBold);
}

void rptRiStyle::SetItalic( bool bItalic )
{
   m_FontModifiers.set(ITALIC, bItalic );
}

void rptRiStyle::SetBullet( BulletType bulletType )
{
   m_BulletType = bulletType;
}

void rptRiStyle::SetColor( FontColor fontColor )
{
   m_Color = fontColor;
}

void rptRiStyle::SetBGColor( FontColor fontColor )
{
   m_BgColor = fontColor;
}

bool rptRiStyle::IsBorder() const
{
    return (m_BorderStyles[BTOP]    ||
            m_BorderStyles[BBOTTOM] || 
            m_BorderStyles[BLEFT]   ||
            m_BorderStyles[BRIGHT]);
}

//======================== INQUIRY    =======================================
rptRiStyle::FontType rptRiStyle::GetFontType() const
{
   return m_Font;
}

Uint16 rptRiStyle::GetFontSize() const
{
   return m_FontSize;
}

rptRiStyle::AlignmentType rptRiStyle::GetAlignment() const
{
   return m_Alignment;
}

rptRiStyle::VerticalAlignmentType rptRiStyle::GetVerticalAlignment() const
{
   return m_VAlignment;
}

bool rptRiStyle::GetUnderlined() const
{
   return m_FontModifiers[UNDERLINE];
}

bool rptRiStyle::GetBold () const
{
   return m_FontModifiers[BOLD];
}

bool rptRiStyle::GetItalic() const
{
   return m_FontModifiers[ITALIC];
}

rptRiStyle::BulletType rptRiStyle::GetBullet() const
{
   return m_BulletType;
}

rptRiStyle::FontColor rptRiStyle::GetColor() const
{
   return m_Color;
}

rptRiStyle::FontColor rptRiStyle::GetBGColor() const
{
   return m_BgColor;
}

void rptRiStyle::SetMediaType(rptRiStyle::MediaType mt)
{
   m_MediaType = mt;
}

rptRiStyle::MediaType rptRiStyle::GetMediaType() const
{
   return m_MediaType;
}


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
void rptRiStyle::Init()
{
   //
   // initialize the style with some reasonable defaults
   //
   m_Font       = NIL;
   m_FontSize   = 10;
   m_Alignment  = LEFT;
   m_VAlignment = MIDDLE;
   m_BulletType = NOBULLET;
   m_Color      = Black;
   m_BgColor    = White;
   m_MediaType  = Both;

   m_BorderStyles[BTOP]    = NOBORDER;
   m_BorderStyles[BBOTTOM] = NOBORDER;
   m_BorderStyles[BLEFT]   = NOBORDER;
   m_BorderStyles[BRIGHT]  = NOBORDER;
}
//======================== OPERATIONS =======================================

void rptRiStyle::MakeCopy(const rptRiStyle& rIStyle)
{
   m_Font          = rIStyle.m_Font;     
   m_FontSize      = rIStyle.m_FontSize;  
   m_Alignment     = rIStyle.m_Alignment; 
   m_VAlignment    = rIStyle.m_VAlignment;
   m_BulletType    = rIStyle.m_BulletType;
   m_Color         = rIStyle.m_Color;
   m_BgColor       = rIStyle.m_BgColor;
   m_FontModifiers = rIStyle.m_FontModifiers;
   m_MediaType     = rIStyle.m_MediaType;

   for (int i=0; i<NUMBORDERS; i++)
   {
      m_BorderStyles[i] = rIStyle.m_BorderStyles[i];
   }
}


void rptRiStyle::MakeAssignment(const rptRiStyle& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

std::_tstring rptRiStyle::GetColorCode(FontColor color)
{
   std::_tstring strColor;
   switch(color)
   {
      // Red colors
      case rptRiStyle::IndianRed:   strColor = _T("#cd5c5c"); break;
      case rptRiStyle::LightCoral:  strColor = _T("#f08080"); break;
      case rptRiStyle::Salmon:      strColor = _T("#fa8072"); break;
      case rptRiStyle::DarkSalmon:  strColor = _T("#e9967a"); break;
      case rptRiStyle::LightSalmon: strColor = _T("#ffa07a"); break;
      case rptRiStyle::Crimson:     strColor = _T("#dc143c"); break;
      case rptRiStyle::Red:         strColor = _T("#ff0000"); break;
      case rptRiStyle::FireBrick:   strColor = _T("#b22222"); break;
      case rptRiStyle::DarkRed:     strColor = _T("#8b0000"); break;
     
      // Pink colors
      case rptRiStyle::Pink:            strColor = _T("#ffc0cb"); break;
      case rptRiStyle::LightPink:       strColor = _T("#ffb6c1"); break;
      case rptRiStyle::HotPink:         strColor = _T("#ff69b4"); break;
      case rptRiStyle::DeepPink:        strColor = _T("#ff1493"); break;
      case rptRiStyle::MediumVioletRed: strColor = _T("#c71585"); break;
      case rptRiStyle::PaleVioletRed:   strColor = _T("#db7093"); break;
     
      // Orange colors
      case rptRiStyle::Coral:      strColor = _T("#ff7f50"); break;
      case rptRiStyle::Tomato:     strColor = _T("#ff6347"); break;
      case rptRiStyle::OrangeRed:  strColor = _T("#ff4500"); break;
      case rptRiStyle::DarkOrange: strColor = _T("#ff8c00"); break;
      case rptRiStyle::Orange:     strColor = _T("#ffa500"); break;
     
      // Yellow colors
      case rptRiStyle::Gold:                 strColor = _T("#ffd700"); break;
      case rptRiStyle::Yellow:               strColor = _T("#ffff00"); break;
      case rptRiStyle::LightYellow:          strColor = _T("#ffffe0"); break;
      case rptRiStyle::LemonChiffon:         strColor = _T("#fffacd"); break;
      case rptRiStyle::LightGoldenrodYellow: strColor = _T("#fafad2"); break;
      case rptRiStyle::PapayaWhip:           strColor = _T("#ffefd5"); break;
      case rptRiStyle::Moccasin:             strColor = _T("#ffe4b5"); break;
      case rptRiStyle::PeachPuff:            strColor = _T("#ffdab9"); break;
      case rptRiStyle::PaleGoldenrod:        strColor = _T("#eee8aa"); break;
      case rptRiStyle::Khaki:                strColor = _T("#f0e68c"); break;
      case rptRiStyle::DarkKhaki:            strColor = _T("#bdb76b"); break;

      // Purple colors
      case rptRiStyle::Lavender:        strColor = _T("#e6e6fa"); break;
      case rptRiStyle::Thistle:         strColor = _T("#d8bfd8"); break;
      case rptRiStyle::Plum:            strColor = _T("#dda0dd"); break;
      case rptRiStyle::Violet:          strColor = _T("#ee82ee"); break;
      case rptRiStyle::Ochrid:          strColor = _T("#da70d6"); break;
      case rptRiStyle::Fuchsia:         strColor = _T("#ff00ff"); break;
      case rptRiStyle::Magenta:         strColor = _T("#ff00ff"); break;
      case rptRiStyle::MediumOrchid:    strColor = _T("#ba55d3"); break;
      case rptRiStyle::MediumPurple:    strColor = _T("#9370d3"); break;
      case rptRiStyle::BlueViolet:      strColor = _T("#8a2be2"); break;
      case rptRiStyle::DarkViolet:      strColor = _T("#9400d3"); break;
      case rptRiStyle::DarkOrchid:      strColor = _T("#9932cc"); break;
      case rptRiStyle::DarkMagenta:     strColor = _T("#8b008b"); break;
      case rptRiStyle::Purple:          strColor = _T("#800080"); break;
      case rptRiStyle::Indigo:          strColor = _T("#4b0082"); break;
      case rptRiStyle::SlateBlue:       strColor = _T("#6a5acd"); break;
      case rptRiStyle::DarkSlateBlue:   strColor = _T("#483d8b"); break;
      case rptRiStyle::MediumSlateBlue: strColor = _T("#b68ee"); break;

      // Green colors
      case rptRiStyle::GreenYellow:       strColor = _T("#adff2f"); break;
      case rptRiStyle::Chartreuse:        strColor = _T("#7fff00"); break;
      case rptRiStyle::LawnGreen:         strColor = _T("#7cfc00"); break;
      case rptRiStyle::Lime:              strColor = _T("#00ff00"); break;
      case rptRiStyle::LimeGreen:         strColor = _T("#32cd32"); break;
      case rptRiStyle::PaleGreen:         strColor = _T("#98fb98"); break;
      case rptRiStyle::LightGreen:        strColor = _T("#90ee90"); break;
      case rptRiStyle::MediumSpringGreen: strColor = _T("#00fa9a"); break;
      case rptRiStyle::SpringGreen:       strColor = _T("#00ff7f"); break;
      case rptRiStyle::MediumSeaGreen:    strColor = _T("#3cb371"); break;
      case rptRiStyle::SeaGreen:          strColor = _T("#2e8b57"); break;
      case rptRiStyle::ForestGreen:       strColor = _T("#228b22"); break;
      case rptRiStyle::Green:             strColor = _T("#008000"); break;
      case rptRiStyle::DarkGreen:         strColor = _T("#006400"); break;
      case rptRiStyle::YellowGreen:       strColor = _T("#9acd32"); break;
      case rptRiStyle::OliveDrab:         strColor = _T("#6b8e23"); break;
      case rptRiStyle::Olive:             strColor = _T("#808000"); break;
      case rptRiStyle::DarkOliveGreen:    strColor = _T("#556b2f"); break;
      case rptRiStyle::MediumAquamarine:  strColor = _T("#66cdaa"); break;
      case rptRiStyle::DarkSeaGreen:      strColor = _T("#8fbc8f"); break;
      case rptRiStyle::LightSeaGreen:     strColor = _T("#20b2aa"); break;
      case rptRiStyle::DarkCyan:          strColor = _T("#008b8b"); break;
      case rptRiStyle::Teal:              strColor = _T("#008080"); break;

      // Blue colors
      case rptRiStyle::Aqua:            strColor = _T("#00ffff"); break;
      case rptRiStyle::Cyan:            strColor = _T("#00ffff"); break;
      case rptRiStyle::LightCyan:       strColor = _T("#e0ffff"); break;
      case rptRiStyle::PaleTurquoise:   strColor = _T("#afeeee"); break;
      case rptRiStyle::Aquarmarine:     strColor = _T("#7fffd4"); break;
      case rptRiStyle::Turquoise:       strColor = _T("#40e0d0"); break;
      case rptRiStyle::MediumTurquoise: strColor = _T("#48d1cc"); break;
      case rptRiStyle::DarkTurquoise:   strColor = _T("#00ced1"); break;
      case rptRiStyle::CadetBlue:       strColor = _T("#5f9ea0"); break;
      case rptRiStyle::SteelBlue:       strColor = _T("#4682b4"); break;
      case rptRiStyle::LightSteelBlue:  strColor = _T("#b0c4de"); break;
      case rptRiStyle::PowderBlue:      strColor = _T("#b0e0de"); break;
      case rptRiStyle::LightBlue:       strColor = _T("#add8e6"); break;
      case rptRiStyle::SkyBlue:         strColor = _T("#87ceeb"); break;
      case rptRiStyle::LightSkyBlue:    strColor = _T("#87cefa"); break;
      case rptRiStyle::DeepSkyBlue:     strColor = _T("#00bfff"); break;
      case rptRiStyle::DodgerBlue:      strColor = _T("#1e90ff"); break;
      case rptRiStyle::CornflowerBlue:  strColor = _T("#6495ed"); break;
      case rptRiStyle::RoyalBlue:       strColor = _T("#4169ed"); break;
      case rptRiStyle::Blue:            strColor = _T("#0000ff"); break;
      case rptRiStyle::MediumBlue:      strColor = _T("#0000cd"); break;
      case rptRiStyle::DarkBlue:        strColor = _T("#00008b"); break;
      case rptRiStyle::Navy:            strColor = _T("#000080"); break;
      case rptRiStyle::MidnightBlue:    strColor = _T("#191970"); break;

      // Brown colors
      case rptRiStyle::CornSilk:       strColor = _T("#fff8dc"); break;
      case rptRiStyle::BlanchedAlmond: strColor = _T("#ffebcd"); break;
      case rptRiStyle::Bisque:         strColor = _T("#ffe4c4"); break;
      case rptRiStyle::NavajoWhite:    strColor = _T("#ffdead"); break;
      case rptRiStyle::Wheat:          strColor = _T("#f5deb3"); break;
      case rptRiStyle::BurlyWood:      strColor = _T("#deb887"); break;
      case rptRiStyle::Tan:            strColor = _T("#d2b48c"); break;
      case rptRiStyle::RosyBrown:      strColor = _T("#bc8f8f"); break;
      case rptRiStyle::SandyBrown:     strColor = _T("#f4a460"); break;
      case rptRiStyle::Goldenrod:      strColor = _T("#daa520"); break;
      case rptRiStyle::DarkGoldenrod:  strColor = _T("#b8860b"); break;
      case rptRiStyle::Peru:           strColor = _T("#cd853f"); break;
      case rptRiStyle::Chocolate:      strColor = _T("#d2691e"); break;
      case rptRiStyle::SaddleBrown:    strColor = _T("#8b4513"); break;
      case rptRiStyle::Sienna:         strColor = _T("#a0522d"); break;
      case rptRiStyle::Brown:          strColor = _T("#a52a2a"); break;
      case rptRiStyle::Maroon:         strColor = _T("#800000"); break;

      // White colors
      case rptRiStyle::White:         strColor = _T("#ffffff"); break;
      case rptRiStyle::Snow:          strColor = _T("#fffafa"); break;
      case rptRiStyle::Honeydew:      strColor = _T("#f0fff0"); break;
      case rptRiStyle::MintCream:     strColor = _T("#f5fffa"); break;
      case rptRiStyle::Azure:         strColor = _T("#f0ffff"); break;
      case rptRiStyle::AliceBlue:     strColor = _T("#f0f8ff"); break;
      case rptRiStyle::GhostWhite:    strColor = _T("#f8f8ff"); break;
      case rptRiStyle::WhiteSmoke:    strColor = _T("#f5f5f5"); break;
      case rptRiStyle::Seashell:      strColor = _T("#fff5ee"); break;
      case rptRiStyle::Beige:         strColor = _T("#f5f5ee"); break;
      case rptRiStyle::OldLace:       strColor = _T("#f5f5dc"); break;
      case rptRiStyle::FloralWhite:   strColor = _T("#fffaf0"); break;
      case rptRiStyle::Ivory:         strColor = _T("#fffff0"); break;
      case rptRiStyle::AntiqueWhite:  strColor = _T("#faebd7"); break;
      case rptRiStyle::Linen:         strColor = _T("#faf0e6"); break;
      case rptRiStyle::LavenderBlush: strColor = _T("#fff0f5"); break;
      case rptRiStyle::MistyRose:     strColor = _T("#ffe4e1"); break;

      // Gray colors
      case rptRiStyle::Gainsboro:      strColor = _T("#dcdcdc"); break;
      case rptRiStyle::LightGray:      strColor = _T("#d3d3d3"); break;
      case rptRiStyle::Silver:         strColor = _T("#c0c0c0"); break;
      case rptRiStyle::DarkGray:       strColor = _T("#a9a9a9"); break;
      case rptRiStyle::Gray:           strColor = _T("#808080"); break;
      case rptRiStyle::DimGray:        strColor = _T("#696969"); break;
      case rptRiStyle::LightSlateGray: strColor = _T("#778899"); break;
      case rptRiStyle::SlateGray:      strColor = _T("#708090"); break;
      case rptRiStyle::DarkSlateGray:  strColor = _T("#2f4f4f"); break;
      case rptRiStyle::Black:          strColor = _T("#000000"); break;
   }
   

   return strColor;
}
