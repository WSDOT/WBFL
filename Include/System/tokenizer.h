///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

/* tokenizer.h   -*- C++ -*-

   Author: Marko Meyer
   Date:   97/06/30
   Time-stamp: <97/11/25 22:43:20 mme>


   Declaration of a string tokenizing class.

   rdp: adopted this class from:
      http://www.tu-chemnitz.de/~marme/programs/tokenizer/index.html
      on 6/24/99. 

      Replace vector<char> version with std::_tstring's to match current version
      of standard library

   */
#pragma once
#include <System\SysExp.h>
#include <Windows.h>

#include <vector>
#include <string>
#include <istream>


typedef std::_tstring Token;
typedef std::_tstring Delimiter;
typedef std::_tstring TString;
typedef TString::iterator TIter;

// Currently, tokenizing is implemented on strings only. 
class SYSCLASS sysTokenizer 
{
    // The three representations of our contents:
    TString Vector_Rep;                      // original string
    std::vector<Token> Token_Rep;            // string separated in tokens.
    std::vector<Delimiter> Delims;           // The delimiters of tokens.
    
public:
    // Typedefs for use as STL container:
    typedef std::vector<Token>::value_type value_type;
    typedef std::vector<Token>::reference reference;
    typedef std::vector<Token>::const_reference const_reference;
    typedef std::vector<Token>::iterator iterator;
    typedef std::vector<Token>::const_iterator const_iterator;
    typedef std::vector<Token>::reverse_iterator reverse_iterator;
    typedef std::vector<Token>::const_reverse_iterator const_reverse_iterator;
    typedef std::vector<Token>::difference_type difference_type;
    typedef std::vector<Token>::size_type size_type;
    
    // Constructor; takes a set of delimiters.
    sysTokenizer();
    sysTokenizer(LPCTSTR OneDel);
    sysTokenizer(LPCTSTR *Token_Del);

    // Destructor
    ~sysTokenizer();

    // Methods for making this class look STL container alike.
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    
    sysTokenizer &operator = (const sysTokenizer &T);
    
    bool operator == (const sysTokenizer &T) const;
    bool operator != (const sysTokenizer &T) const;
    bool operator < (const sysTokenizer &T) const;

    reference operator [] (size_type n);
    const_reference operator [] (size_type n) const;

    size_type size() const;
    size_type max_size() const;
    bool empty() const;
    
    void push_back(LPCTSTR CString);
    void push_back(const std::_tstring& str);

    // Utilities for dealing with tokens once they are identified
    // parse a null-terminated string to a float. return false if not a number.
    static bool ParseDouble(LPCTSTR lpszText, Float64* d);
    static bool ParseLong(LPCTSTR lpszText, long* d);

    
private:
    TString CS_to_TS(LPCTSTR CS);
    LPTSTR TS_to_CS(TString &Vec);
    
    Token find_next_token(TString &TS, TIter &Ti);
    
};

inline bool operator < (const sysTokenizer &T1, const sysTokenizer &T2)
{
    return T1.operator < (T2);
}


inline std::_tistream & operator >> (std::_tistream &is, sysTokenizer &T)
{
    std::_tstring vec;

    for(TCHAR c = 0; is && c != _T('\n'); is.get(c))
        if(c != _T('\n') && c > 0) vec += c;
    
    T.push_back(0);
    if(is) T.push_back(vec);
    
    return is;
}


