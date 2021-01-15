///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_RISTYLE_H_
#define INCLUDED_REPORTER_RISTYLE_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportingUtils.h>
#include <bitset>
#include <array>

/// This class encapsulates report item styles such as fonts, font modifiers (bold, italic...), and color.
class REPORTERCLASS rptRiStyle
{
public:
   /// Font Types
   ///
   /// Do not change the ordering of this list unless you plan to change the mappings in the visitors that use it.
   enum FontType {
      NIL,     ///< default (pot luck)
      ROMAN,   ///< typically times new roman
      SWISS,   ///< arial
      MODERN,  ///< fixed pitch - courier
      TECH     ///< symbol font (not portable)
   };

   /// Font colors
   enum FontColor {
      Default, ///< Default means do not modify font color

      // Red colors
      IndianRed,
      LightCoral,
      Salmon,
      DarkSalmon,
      LightSalmon,
      Crimson,
      Red,
      FireBrick,
      DarkRed,
      
      // Pink colors
      Pink,
      LightPink,
      HotPink,
      DeepPink,
      MediumVioletRed,
      PaleVioletRed,
      
      // Orange colors
      Coral,
      Tomato,
      OrangeRed,
      DarkOrange,
      Orange,
      
      // Yellow colors
      Gold,
      Yellow,
      LightYellow,
      LemonChiffon,
      LightGoldenrodYellow,
      PapayaWhip,
      Moccasin,
      PeachPuff,
      PaleGoldenrod,
      Khaki,
      DarkKhaki,

      // Purple colors
      Lavender,
      Thistle,
      Plum,
      Violet,
      Ochrid,
      Fuchsia,
      Magenta,
      MediumOrchid,
      MediumPurple,
      BlueViolet,
      DarkViolet,
      DarkOrchid,
      DarkMagenta,
      Purple,
      Indigo,
      SlateBlue,
      DarkSlateBlue,
      MediumSlateBlue,

      // Green colors
      GreenYellow,
      Chartreuse,
      LawnGreen,
      Lime,
      LimeGreen,
      PaleGreen,
      LightGreen,
      MediumSpringGreen,
      SpringGreen,
      MediumSeaGreen,
      SeaGreen,
      ForestGreen,
      Green,
      DarkGreen,
      YellowGreen,
      OliveDrab,
      Olive,
      DarkOliveGreen,
      MediumAquamarine,
      DarkSeaGreen,
      LightSeaGreen,
      DarkCyan,
      Teal,

      // Blue colors
      Aqua,
      Cyan,
      LightCyan,
      PaleTurquoise,
      Aquarmarine,
      Turquoise,
      MediumTurquoise,
      DarkTurquoise,
      CadetBlue,
      SteelBlue,
      LightSteelBlue,
      PowderBlue,
      LightBlue,
      SkyBlue,
      LightSkyBlue,
      DeepSkyBlue,
      DodgerBlue,
      CornflowerBlue,
      RoyalBlue,
      Blue,
      MediumBlue,
      DarkBlue,
      Navy,
      MidnightBlue,

      // Brown colors
      CornSilk,
      BlanchedAlmond,
      Bisque,
      NavajoWhite,
      Wheat,
      BurlyWood,
      Tan,
      RosyBrown,
      SandyBrown,
      Goldenrod,
      DarkGoldenrod,
      Peru,
      Chocolate,
      SaddleBrown,
      Sienna,
      Brown,
      Maroon,

      // White colors
      White,
      Snow,
      Honeydew,
      MintCream,
      Azure,
      AliceBlue,
      GhostWhite,
      WhiteSmoke,
      Seashell,
      Beige,
      OldLace,
      FloralWhite,
      Ivory,
      AntiqueWhite,
      Linen,
      LavenderBlush,
      MistyRose,

      // Gray colors
      Gainsboro,
      LightGray,
      Silver,
      DarkGray,
      Gray,
      DimGray,
      LightSlateGray,
      SlateGray,
      DarkSlateGray,
      Black
   };

   /// Returns the hex color code equivalent
   static std::_tstring GetColorCode(FontColor color);


   /// Font characteristic modifiers
   enum FontModifier  
   { 
      BOLD, 
      ITALIC, 
      UNDERLINE, 
      OVERLINE, 
      LINETHROUGH, 
      SUBSCRIPT, 
      SUPERSCRIPT,
      FMSIZE ///< Used for sizing info only
   }; 

   /// Horizontal paragraph alignment types
   enum AlignmentType { LEFT, RIGHT, CENTER, FULL };

   /// Vertical paragraph alignments types
   enum VerticalAlignmentType { BASELINE, BOTTOM, MIDDLE, TOP };

   /// Bullet types
   enum BulletType { NOBULLET, DASH, ROUND };

   /// Border styles
   enum BorderStyle { NOBORDER, HAIR_THICK, SINGLE_THICK, DOUBLE_THICK,
   DOUBLE_LINE, DASHED, DOTTED, BRDRSIZE /**! Used as sizing info only.**/ };

   /// Media type
   enum MediaType { Screen = 0, Print = 1, Both = 2 };

   rptRiStyle();

   rptRiStyle(FontType fontType, 
              Uint16 fontSize,
              bool bBold              = false, 
              bool bItalic            = false,
              bool bUnderline         = false,
              bool bOverline          = false,
              bool bLineThrough       = false,
              FontColor fontColor     = Black,
              AlignmentType alignType = LEFT,
              VerticalAlignmentType valignType = BASELINE,
              bool isHeading=false);

   rptRiStyle(const rptRiStyle& rOther);

   virtual ~rptRiStyle(); 

   rptRiStyle& operator=(const rptRiStyle& rOther);

   /// Set the font type 
   void SetFontType( FontType fontType );

   /// Set the font size in points
   void SetFontSize( Uint16 fontSize );

   /// Set the horizontal text alignment
   void SetAlignment( AlignmentType alignType );

   /// Set the vertical text alignment
   void SetVerticalAlignment( VerticalAlignmentType valignType );

   /// Set the underlined attribute
   void SetUnderlined( bool bUnderline = true);

   /// Set the overline attribute
   void SetOverlined( bool bOverline = true);

   /// Set the line-through attribute
   void SetLineThrough( bool bLineThrough = true);

   /// Set the Bold attribute
   void SetBold ( bool bBold = true);

   /// Set the Italic attribue
   void SetItalic( bool bItalic = true);

   /// Set the bullet type
   void SetBullet( BulletType bulletType );

   /// Set the foreground color
   void SetColor ( FontColor fontColor );

   /// Set the background color
   void SetBGColor( FontColor fontColor );

   /// Returns the font face
   FontType GetFontType() const;

   /// Returns the font size in points
   Uint16 GetFontSize() const;

   /// Relturns the text alignment
   AlignmentType GetAlignment() const;

   /// Returns the text alignment
   VerticalAlignmentType GetVerticalAlignment() const;

   /// Returns the underlined attriute
   bool GetUnderlined() const;

   /// Returns the overlined attribute
   bool GetOverlined() const;

   /// Returns the line-through attribute
   bool GetLineThrough() const;

   /// Returns the bold attribute
   bool GetBold() const;

   /// Returns the italics attribute
   bool GetItalic() const;

   /// Returns the bullet type
   BulletType GetBullet() const;

   /// Returns the foreground color
   FontColor GetColor() const;

   /// Returns the background color
   FontColor GetBGColor() const;

   /// Sets the heading attribute.
   ///
   /// If this is a heading style a margin will be put before it
   void SetIsHeading(bool isHead);

   /// Returns the headding attribute
   bool IsHeading() const;

   /// Returns true if the styled item has a border
   bool IsBorder() const;

   /// Returns top border style
   BorderStyle GetTopBorder() const
   {return m_BorderStyles[BTOP];}

   /// Sets top border style
   void SetTopBorder(BorderStyle borderStyle)
   { m_BorderStyles[BTOP] = borderStyle; }

   /// Returns bottom border style
   BorderStyle GetBottomBorder() const
   {return m_BorderStyles[BBOTTOM];}

   /// Sets the bottom border style
   void SetBottomBorder(BorderStyle borderStyle)
   { m_BorderStyles[BBOTTOM] = borderStyle; }

   /// Returns the left border style
   BorderStyle GetLeftBorder() const
   {return m_BorderStyles[BLEFT];}

   /// Sets the left border style
   void SetLeftBorder(BorderStyle borderStyle)
   { m_BorderStyles[BLEFT] = borderStyle; }

   /// Returns the right border style
   BorderStyle GetRightBorder() const
   {return m_BorderStyles[BRIGHT];}

   /// Sets the right border style
   void SetRightBorder(BorderStyle borderStyle)
   { m_BorderStyles[BRIGHT] = borderStyle; }

   /// Sets the media type
   void SetMediaType(MediaType mt);

   /// Returns the media type
   MediaType GetMediaType() const;

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRiStyle& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRiStyle& rOther);

private:
	typedef std::bitset<FMSIZE> FmSetType;
   enum BorderLoc {BTOP, BBOTTOM, BLEFT, BRIGHT};

   FontType      m_Font;
   unsigned      m_FontSize;
   FontColor     m_Color;
   FontColor     m_BgColor;
   FmSetType     m_FontModifiers;
   AlignmentType m_Alignment;
   VerticalAlignmentType m_VAlignment;
   BulletType    m_BulletType;
   MediaType m_MediaType;
   bool m_IsHeading;

   std::array<BorderStyle, 4> m_BorderStyles;

   void Init(); ///< Common initialization
};

#endif // INCLUDED_REPORTER_RISTYLE_H_
