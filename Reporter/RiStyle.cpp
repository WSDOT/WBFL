///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

std::string rptRiStyle::GetColorCode(FontColor color)
{
   std::string strColor;
   switch(color)
   {
      // Red colors
      case rptRiStyle::IndianRed:   strColor = "#cd5c5c"; break;
      case rptRiStyle::LightCoral:  strColor = "#f08080"; break;
      case rptRiStyle::Salmon:      strColor = "#fa8072"; break;
      case rptRiStyle::DarkSalmon:  strColor = "#e9967a"; break;
      case rptRiStyle::LightSalmon: strColor = "#ffa07a"; break;
      case rptRiStyle::Crimson:     strColor = "#dc143c"; break;
      case rptRiStyle::Red:         strColor = "#ff0000"; break;
      case rptRiStyle::FireBrick:   strColor = "#b22222"; break;
      case rptRiStyle::DarkRed:     strColor = "#8b0000"; break;
     
      // Pink colors
      case rptRiStyle::Pink:            strColor = "#ffc0cb"; break;
      case rptRiStyle::LightPink:       strColor = "#ffb6c1"; break;
      case rptRiStyle::HotPink:         strColor = "#ff69b4"; break;
      case rptRiStyle::DeepPink:        strColor = "#ff1493"; break;
      case rptRiStyle::MediumVioletRed: strColor = "#c71585"; break;
      case rptRiStyle::PaleVioletRed:   strColor = "#db7093"; break;
     
      // Orange colors
      case rptRiStyle::Coral:      strColor = "#ff7f50"; break;
      case rptRiStyle::Tomato:     strColor = "#ff6347"; break;
      case rptRiStyle::OrangeRed:  strColor = "#ff4500"; break;
      case rptRiStyle::DarkOrange: strColor = "#ff8c00"; break;
      case rptRiStyle::Orange:     strColor = "#ff1500"; break;
     
      // Yellow colors
      case rptRiStyle::Gold:                 strColor = "#ffd700"; break;
      case rptRiStyle::Yellow:               strColor = "#ffff00"; break;
      case rptRiStyle::LightYellow:          strColor = "#ffffe0"; break;
      case rptRiStyle::LemonChiffon:         strColor = "#fffacd"; break;
      case rptRiStyle::LightGoldenrodYellow: strColor = "#fafad2"; break;
      case rptRiStyle::PapayaWhip:           strColor = "#ffefd5"; break;
      case rptRiStyle::Moccasin:             strColor = "#ffe4b5"; break;
      case rptRiStyle::PeachPuff:            strColor = "#ffdab9"; break;
      case rptRiStyle::PaleGoldenrod:        strColor = "#eee8aa"; break;
      case rptRiStyle::Khaki:                strColor = "#f0e68c"; break;
      case rptRiStyle::DarkKhaki:            strColor = "#bdb76b"; break;

      // Purple colors
      case rptRiStyle::Lavender:        strColor = "#e6e6fa"; break;
      case rptRiStyle::Thistle:         strColor = "#d8bfd8"; break;
      case rptRiStyle::Plum:            strColor = "#dda0dd"; break;
      case rptRiStyle::Violet:          strColor = "#ee82ee"; break;
      case rptRiStyle::Ochrid:          strColor = "#da70d6"; break;
      case rptRiStyle::Fuchsia:         strColor = "#ff00ff"; break;
      case rptRiStyle::Magenta:         strColor = "#ff00ff"; break;
      case rptRiStyle::MediumOrchid:    strColor = "#ba55d3"; break;
      case rptRiStyle::MediumPurple:    strColor = "#9370d3"; break;
      case rptRiStyle::BlueViolet:      strColor = "#8a2be2"; break;
      case rptRiStyle::DarkViolet:      strColor = "#9400d3"; break;
      case rptRiStyle::DarkOrchid:      strColor = "#9932cc"; break;
      case rptRiStyle::DarkMagenta:     strColor = "#8b008b"; break;
      case rptRiStyle::Purple:          strColor = "#800080"; break;
      case rptRiStyle::Indigo:          strColor = "#4b0082"; break;
      case rptRiStyle::SlateBlue:       strColor = "#6a5acd"; break;
      case rptRiStyle::DarkSlateBlue:   strColor = "#483d8b"; break;
      case rptRiStyle::MediumSlateBlue: strColor = "#b68ee"; break;

      // Green colors
      case rptRiStyle::GreenYellow:       strColor = "#adff2f"; break;
      case rptRiStyle::Chartreuse:        strColor = "#7fff00"; break;
      case rptRiStyle::LawnGreen:         strColor = "#7cfc00"; break;
      case rptRiStyle::Lime:              strColor = "#00ff00"; break;
      case rptRiStyle::LimeGreen:         strColor = "#32cd32"; break;
      case rptRiStyle::PaleGreen:         strColor = "#98fb98"; break;
      case rptRiStyle::LightGreen:        strColor = "#90ee90"; break;
      case rptRiStyle::MediumSpringGreen: strColor = "#00fa9a"; break;
      case rptRiStyle::SpringGreen:       strColor = "#00ff7f"; break;
      case rptRiStyle::MediumSeaGreen:    strColor = "#3cb371"; break;
      case rptRiStyle::SeaGreen:          strColor = "#2e8b57"; break;
      case rptRiStyle::ForestGreen:       strColor = "#228b22"; break;
      case rptRiStyle::Green:             strColor = "#008000"; break;
      case rptRiStyle::DarkGreen:         strColor = "#006400"; break;
      case rptRiStyle::YellowGreen:       strColor = "#9acd32"; break;
      case rptRiStyle::OliveDrab:         strColor = "#6b8e23"; break;
      case rptRiStyle::Olive:             strColor = "#808000"; break;
      case rptRiStyle::DarkOliveGreen:    strColor = "#556b2f"; break;
      case rptRiStyle::MediumAquamarine:  strColor = "#66cdaa"; break;
      case rptRiStyle::DarkSeaGreen:      strColor = "#8fbc8f"; break;
      case rptRiStyle::LightSeaGreen:     strColor = "#20b2aa"; break;
      case rptRiStyle::DarkCyan:          strColor = "#008b8b"; break;
      case rptRiStyle::Teal:              strColor = "#008080"; break;

      // Blue colors
      case rptRiStyle::Aqua:            strColor = "#00ffff"; break;
      case rptRiStyle::Cyan:            strColor = "#00ffff"; break;
      case rptRiStyle::LightCyan:       strColor = "#e0ffff"; break;
      case rptRiStyle::PaleTurquoise:   strColor = "#afeeee"; break;
      case rptRiStyle::Aquarmarine:     strColor = "#7fffd4"; break;
      case rptRiStyle::Turquoise:       strColor = "#40e0d0"; break;
      case rptRiStyle::MediumTurquoise: strColor = "#48d1cc"; break;
      case rptRiStyle::DarkTurquoise:   strColor = "#00ced1"; break;
      case rptRiStyle::CadetBlue:       strColor = "#5f9ea0"; break;
      case rptRiStyle::SteelBlue:       strColor = "#4682b4"; break;
      case rptRiStyle::LightSteelBlue:  strColor = "#b0c4de"; break;
      case rptRiStyle::PowderBlue:      strColor = "#b0e0de"; break;
      case rptRiStyle::LightBlue:       strColor = "#add8e6"; break;
      case rptRiStyle::SkyBlue:         strColor = "#87ceeb"; break;
      case rptRiStyle::LightSkyBlue:    strColor = "#87cefa"; break;
      case rptRiStyle::DeepSkyBlue:     strColor = "#00bfff"; break;
      case rptRiStyle::DodgerBlue:      strColor = "#1e90ff"; break;
      case rptRiStyle::CornflowerBlue:  strColor = "#6495ed"; break;
      case rptRiStyle::RoyalBlue:       strColor = "#4169ed"; break;
      case rptRiStyle::Blue:            strColor = "#0000ff"; break;
      case rptRiStyle::MediumBlue:      strColor = "#0000cd"; break;
      case rptRiStyle::DarkBlue:        strColor = "#00008b"; break;
      case rptRiStyle::Navy:            strColor = "#000080"; break;
      case rptRiStyle::MidnightBlue:    strColor = "#191970"; break;

      // Brown colors
      case rptRiStyle::CornSilk:       strColor = "#fff8dc"; break;
      case rptRiStyle::BlanchedAlmond: strColor = "#ffebcd"; break;
      case rptRiStyle::Bisque:         strColor = "#ffe4c4"; break;
      case rptRiStyle::NavajoWhite:    strColor = "#ffdead"; break;
      case rptRiStyle::Wheat:          strColor = "#f5deb3"; break;
      case rptRiStyle::BurlyWood:      strColor = "#deb887"; break;
      case rptRiStyle::Tan:            strColor = "#d2b48c"; break;
      case rptRiStyle::RosyBrown:      strColor = "#bc8f8f"; break;
      case rptRiStyle::SandyBrown:     strColor = "#f4a460"; break;
      case rptRiStyle::Goldenrod:      strColor = "#daa520"; break;
      case rptRiStyle::DarkGoldenrod:  strColor = "#b8860b"; break;
      case rptRiStyle::Peru:           strColor = "#cd853f"; break;
      case rptRiStyle::Chocolate:      strColor = "#d2691e"; break;
      case rptRiStyle::SaddleBrown:    strColor = "#8b4513"; break;
      case rptRiStyle::Sienna:         strColor = "#a0522d"; break;
      case rptRiStyle::Brown:          strColor = "#a52a2a"; break;
      case rptRiStyle::Maroon:         strColor = "#800000"; break;

      // White colors
      case rptRiStyle::White:         strColor = "#ffffff"; break;
      case rptRiStyle::Snow:          strColor = "#fffafa"; break;
      case rptRiStyle::Honeydew:      strColor = "#f0fff0"; break;
      case rptRiStyle::MintCream:     strColor = "#f5fffa"; break;
      case rptRiStyle::Azure:         strColor = "#f0ffff"; break;
      case rptRiStyle::AliceBlue:     strColor = "#f0f8ff"; break;
      case rptRiStyle::GhostWhite:    strColor = "#f8f8ff"; break;
      case rptRiStyle::WhiteSmoke:    strColor = "#f5f5f5"; break;
      case rptRiStyle::Seashell:      strColor = "#fff5ee"; break;
      case rptRiStyle::Beige:         strColor = "#f5f5ee"; break;
      case rptRiStyle::OldLace:       strColor = "#f5f5dc"; break;
      case rptRiStyle::FloralWhite:   strColor = "#fffaf0"; break;
      case rptRiStyle::Ivory:         strColor = "#fffff0"; break;
      case rptRiStyle::AntiqueWhite:  strColor = "#faebd7"; break;
      case rptRiStyle::Linen:         strColor = "#faf0e6"; break;
      case rptRiStyle::LavenderBlush: strColor = "#fff0f5"; break;
      case rptRiStyle::MistyRose:     strColor = "#ffe4e1"; break;

      // Gray colors
      case rptRiStyle::Gainsboro:      strColor = "#dcdcdc"; break;
      case rptRiStyle::LightGray:      strColor = "#d3d3d3"; break;
      case rptRiStyle::Silver:         strColor = "#c0c0c0"; break;
      case rptRiStyle::DarkGray:       strColor = "#a9a9a9"; break;
      case rptRiStyle::Gray:           strColor = "#808080"; break;
      case rptRiStyle::DimGray:        strColor = "#696969"; break;
      case rptRiStyle::LightSlateGray: strColor = "#778899"; break;
      case rptRiStyle::SlateGray:      strColor = "#708090"; break;
      case rptRiStyle::DarkSlateGray:  strColor = "#2f4f4f"; break;
      case rptRiStyle::Black:          strColor = "#000000"; break;
   }
   

   return strColor;
}
