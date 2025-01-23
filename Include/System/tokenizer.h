///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2025  Washington State Department of Transportation
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

#pragma once
#include <System\SysExp.h>

#include <vector>
#include <string>
#include <istream>

#include <System/Debug.h>


namespace WBFL
{
   namespace System
   {
         using Token = std::_tstring; ///< A token
         using Delimiter = std::_tstring; ///< A delimiter
         using TString = std::_tstring; ///< A string of tokens
         using TIter = TString::iterator; ///< An iterator for the tokens

         /// String tokenizer
         ///
         /// Given a string of tokens and a token delimiter, this class provides
         /// token iteration.
         class SYSCLASS Tokenizer
         {
  
         public:
             // Typedefs for use as STL container:
             using value_type = std::vector<Token>::value_type;
             using reference = std::vector<Token>::reference;
             using const_reference = std::vector<Token>::const_reference;
             using iterator = std::vector<Token>::iterator;
             using const_iterator = std::vector<Token>::const_iterator;
             using reverse_iterator = std::vector<Token>::reverse_iterator;
             using const_reverse_iterator = std::vector<Token>::const_reverse_iterator;
             using difference_type = std::vector<Token>::difference_type;
             using size_type = std::vector<Token>::size_type;
    
             Tokenizer(LPCTSTR OneDel /*! a single delimiter*/);
             Tokenizer(LPCTSTR *Token_Del/*! a null terminated string of single character delimiters*/);

             ~Tokenizer();

             Tokenizer& operator=(const Tokenizer& T);

             // Methods for making this class look STL container alike.
             iterator begin();
             const_iterator begin() const;
             iterator end();
             const_iterator end() const;
             reverse_iterator rbegin();
             const_reverse_iterator rbegin() const;
             reverse_iterator rend();
             const_reverse_iterator rend() const;
    
    
             bool operator==(const Tokenizer &T) const;
             bool operator!=(const Tokenizer &T) const;
             bool operator<(const Tokenizer &T) const;

             reference operator[](size_type n);
             const_reference operator[](size_type n) const;

             size_type size() const;
             size_type max_size() const;
             bool empty() const;
    
             /// Add a null terminated string of delimiter separated tokens for tokenizing
             void push_back(LPCTSTR CString);

             /// Add a string of delimiter separated tokens for tokenizing
             void push_back(const std::_tstring& str);

             // Utilities for dealing with tokens once they are identified
             /// Parse a null-terminated string to a Float64. Return false if not a number.
             static bool ParseDouble(LPCTSTR lpszText, Float64* d);
             /// Parse a null-terminated string to a long. Return false if not a number.
             static bool ParseLong(LPCTSTR lpszText, long* i);
             /// Parse a null-terminated string to an unsigned. Return false if not a number.
             static bool ParseULong(LPCTSTR lpszText, unsigned long* l);
             /// Parse a null-terminated string to a short. Return false if not a number.
             static bool ParseShort(LPCTSTR lpszText, short* i);
             /// Parse a null-terminated string to an unsigned short. Return false if not a number.
             static bool ParseUShort(LPCTSTR lpszText, unsigned short* l);

    
         private:
            // The three representations of our contents:
            TString Vector_Rep;                      // original string
            std::vector<Token> Token_Rep;            // string separated in tokens.
            std::vector<Delimiter> Delims;           // The delimiters of tokens.
            
            TString CS_to_TS(LPCTSTR CS);
            LPTSTR TS_to_CS(TString &Vec);
    
            Token find_next_token(TString &TS, TIter &Ti);
         };
   };
};

/// Compares tokenizers
inline bool operator<(const WBFL::System::Tokenizer &T1, const WBFL::System::Tokenizer &T2)
{
    return T1.operator < (T2);
}

/// Populates tokenizer with values from an input stream
inline std::_tistream& operator>>(std::_tistream &is, WBFL::System::Tokenizer &T)
{
    std::_tstring vec;

    for(TCHAR c = 0; is && c != _T('\n'); is.get(c))
        if(c != _T('\n') && c > 0) vec += c;
    
    T.push_back(0);
    if(is) T.push_back(vec);
    
    return is;
}


