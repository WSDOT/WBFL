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

#ifndef INCLUDED_REPORTER_RISTYLE_H_
#define INCLUDED_REPORTER_RISTYLE_H_
#pragma once

// COCOON: rab 03.05.97 : Cocoon limitations
// FILE:   RiStyle.h
//
// All preprocessor stuff must go up here because of limitations in
// Cocoon.

// SYSTEM INCLUDES
//
#include <bitset>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportingUtils.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRiStyle

   Report Item Style

DESCRIPTION
   This class encapsulates report item styles. this includes fonts, font
   modifiers (bold, italic...), and color.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class REPORTERCLASS rptRiStyle
{
public:
   //------------------------------------------------------------------------
   // Font Types
   // Do not change the ordering of this list unless you plan to change the mappings in the
   // visitors that use it.
   enum FontType {NIL,     // - default (pot luck)
                  ROMAN,   // - typically times new roman
                  SWISS,   // - arial
                  MODERN,  // - fixed pitch - courier
                  TECH};   // - symbol font (not portable)

   //------------------------------------------------------------------------
   // Font colors
   enum FontColor { 
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
   static std::_tstring GetColorCode(FontColor color);


   //------------------------------------------------------------------------
   // types for changing font characteristics
   enum FontModifier  { BOLD, ITALIC, UNDERLINE, SUBSCRIPT, SUPERSCRIPT,
                        FMSIZE}; // FMSIZE is used for sizing info only

   //------------------------------------------------------------------------
   // paragraph alignments
   enum AlignmentType { LEFT, RIGHT, CENTER, FULL };

   //------------------------------------------------------------------------
   // vertical paragraph alignments
   enum VerticalAlignmentType { BASELINE, BOTTOM, MIDDLE, TOP };

   //------------------------------------------------------------------------
   // bullets
   enum BulletType    { NOBULLET, DASH, ROUND };

   //------------------------------------------------------------------------
   // border styles
   enum BorderStyle   { NOBORDER, HAIR_THICK, SINGLE_THICK, Float64_THICK,
   Float64_LINE, DASHED, DOTTED, BRDRSIZE}; // BRDSIZE to be used as sizing info only.

   //------------------------------------------------------------------------
   // media type
   enum MediaType { Screen = 0, Print = 1, Both = 2 };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRiStyle();

   //------------------------------------------------------------------------
   // Construct with more options
   rptRiStyle(FontType fontType, 
              Uint16 fontSize,
              bool bBold              = false, 
              bool bItalic            = false,
              bool bUnderlined        = false,
              FontColor fontColor     = Black,
              AlignmentType alignType = LEFT,
              VerticalAlignmentType valignType = MIDDLE);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRiStyle(const rptRiStyle& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRiStyle(); 

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   rptRiStyle& operator = (const rptRiStyle& rOther);

   // GROUP: OPERATIONS

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // set the font type 
   void SetFontType( FontType fontType );

   //------------------------------------------------------------------------
   // Set the font size in points
   void SetFontSize( Uint16 fontSize );

   //------------------------------------------------------------------------
   // Set the horizontal text alignment
   void SetAlignment( AlignmentType alignType );

   //------------------------------------------------------------------------
   // Set the vertical text alignment
   void SetVerticalAlignment( VerticalAlignmentType valignType );

   //------------------------------------------------------------------------
   // Set the underlined attribute
   void SetUnderlined( bool bUnderline = true);

   //------------------------------------------------------------------------
   // Set the Bold attribute
   void SetBold ( bool bBold = true);

   //------------------------------------------------------------------------
   // Set the Italic attribue
   void SetItalic( bool bItalic = true);

   //------------------------------------------------------------------------
   // Set the bullet type
   void SetBullet( BulletType bulletType );

   //------------------------------------------------------------------------
   // Set the color
   void SetColor ( FontColor fontColor );
   void SetBGColor( FontColor fontColor );

   //------------------------------------------------------------------------
   // Get the font face
   FontType GetFontType() const;

   //------------------------------------------------------------------------
   // Get the font size in points
   Uint16 GetFontSize() const;

   //------------------------------------------------------------------------
   // Get the text alignment
   AlignmentType GetAlignment() const;

   //------------------------------------------------------------------------
   // Get the text alignment
   VerticalAlignmentType GetVerticalAlignment() const;

   //------------------------------------------------------------------------
   // Determine if report item is underlined
   bool GetUnderlined() const;

   //------------------------------------------------------------------------
   // Determine if report item is bold
   bool GetBold () const;

   //------------------------------------------------------------------------
   // Determine if report item is in italics
   bool GetItalic() const;

   //------------------------------------------------------------------------
   // Get the bullet type
   BulletType GetBullet() const;

   //------------------------------------------------------------------------
   // Get the color of the item
   FontColor  GetColor() const;
   FontColor GetBGColor() const;

   // Border Properties
   //------------------------------------------------------------------------
   // Is there a border around the paragraph?
   //
   bool IsBorder() const;

   //------------------------------------------------------------------------
   // Get style of top border
   BorderStyle GetTopBorder() const
   {return m_BorderStyles[BTOP];}

   //------------------------------------------------------------------------
   // Set style of top border
   void SetTopBorder(BorderStyle borderStyle)
   { m_BorderStyles[BTOP] = borderStyle; }

   //------------------------------------------------------------------------
   // Get style of Bottom border
   BorderStyle GetBottomBorder() const
   {return m_BorderStyles[BBOTTOM];}

   //------------------------------------------------------------------------
   // Set style of Bottom border
   void SetBottomBorder(BorderStyle borderStyle)
   { m_BorderStyles[BBOTTOM] = borderStyle; }

   //------------------------------------------------------------------------
   // Get style of Left border
   BorderStyle GetLeftBorder() const
   {return m_BorderStyles[BLEFT];}

   //------------------------------------------------------------------------
   // Set style of Left border
   void SetLeftBorder(BorderStyle borderStyle)
   { m_BorderStyles[BLEFT] = borderStyle; }

   //------------------------------------------------------------------------
   // Get style of Right border
   BorderStyle GetRightBorder() const
   {return m_BorderStyles[BRIGHT];}

   //------------------------------------------------------------------------
   // Set style of Right border
   void SetRightBorder(BorderStyle borderStyle)
   { m_BorderStyles[BRIGHT] = borderStyle; }

   void SetMediaType(MediaType mt);
   MediaType GetMediaType() const;

   // GROUP: INQUIRY


protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
	typedef std::bitset<FMSIZE> FmSetType;
   enum BorderLoc {BTOP, BBOTTOM, BLEFT, BRIGHT};

   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // The current font type
   FontType      m_Font;

   //------------------------------------------------------------------------
   // The current font size
   unsigned      m_FontSize;

   //------------------------------------------------------------------------
   // The current color
   FontColor     m_Color;
   FontColor     m_BgColor;

   //------------------------------------------------------------------------
   // State of the font modifiers: bold, italic, underline
   FmSetType     m_FontModifiers;

   //------------------------------------------------------------------------
   // Current alignment
   AlignmentType m_Alignment;
   VerticalAlignmentType m_VAlignment;

   //------------------------------------------------------------------------
   // Current bullet type
   BulletType    m_BulletType;

   MediaType m_MediaType;

   //------------------------------------------------------------------------
   // border styles for all four sides of paragraph
   // styles are stored in the order given in BorderLoc
   // refer to the enum BorderStyle for available styles
   #define NUMBORDERS 4
   BorderStyle   m_BorderStyles[NUMBORDERS];


   // GROUP: LIFECYCLE

   // GROUP: OPERATORS

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Initialize all data members
   //
   void Init();

   void MakeCopy(const rptRiStyle& rOther);
   void MakeAssignment(const rptRiStyle& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_RISTYLE_H_
