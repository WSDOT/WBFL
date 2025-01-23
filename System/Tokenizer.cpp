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

#include <System\SysLib.h>

/* tokenizer.cc
   
   Author: Marko Meyer
   Date:   97/06/30
   Time-stamp: <97/11/26 00:39:47 mme>
   
   Definition of a string tokenizing class.

   */
// rdp : adopted this class from :
// http://www.tu-chemnitz.de/~marme/programs/tokenizer/index.html
// on 6 / 24 / 99.

#include <System\tokenizer.h>
#include <algorithm>
#include <math.h>
#include <errno.h>

using namespace WBFL::System;

Tokenizer::Tokenizer(LPCTSTR OneDel):
    Vector_Rep(), Token_Rep()
{
    if(OneDel) Delims.push_back(CS_to_TS(OneDel));
}

Tokenizer::Tokenizer(LPCTSTR *Token_Del):
    Vector_Rep(), Token_Rep()
{
    if(Token_Del && Token_Del[0]){
        // Prepare delimiter vector.
        for(LPCTSTR  Di = *Token_Del; Di ; Di = *(Token_Del++))
            Delims.push_back(CS_to_TS(Di));
    }
}

Tokenizer::~Tokenizer()
{
}

Tokenizer::iterator Tokenizer::begin()
{
    return Token_Rep.begin();
}

Tokenizer::const_iterator Tokenizer::begin() const
{
    return Token_Rep.begin();
}

Tokenizer::iterator Tokenizer::end()
{
    return Token_Rep.end();
}

Tokenizer::const_iterator Tokenizer::end() const
{
    return Token_Rep.end();
}

Tokenizer::reverse_iterator Tokenizer::rbegin()
{
    return Token_Rep.rbegin();
}

Tokenizer::const_reverse_iterator Tokenizer::rbegin() const
{
    return Token_Rep.rbegin();
}

Tokenizer::reverse_iterator Tokenizer::rend()
{
    return Token_Rep.rend();
}

Tokenizer::const_reverse_iterator Tokenizer::rend() const
{
    return Token_Rep.rend();
}

Tokenizer &Tokenizer::operator=(const Tokenizer &T)
{
    if(&T == this) return *this;

    Vector_Rep = T.Vector_Rep;
    Token_Rep = T.Token_Rep;
    Delims = T.Delims;
    
    return *this;
}

bool Tokenizer::operator==(const Tokenizer &T) const
{
    if(&T == this) return true;
    return Token_Rep == T.Token_Rep;
}

bool Tokenizer::operator!=(const Tokenizer &T) const
{
    return !operator == (T);
}

bool Tokenizer::operator<(const Tokenizer &T) const
{
    return Token_Rep < T.Token_Rep;
}


Tokenizer::reference Tokenizer::operator[](Tokenizer::size_type n)
{
    return *(begin() + n);
}


Tokenizer::const_reference Tokenizer::operator[](Tokenizer::size_type n) const
{
    return *(begin() + n);
}

Tokenizer::size_type Tokenizer::size() const
{
    return Token_Rep.size();
}

Tokenizer::size_type Tokenizer::max_size() const
{
    return Token_Rep.max_size();
}

bool Tokenizer::empty() const
{
    return Token_Rep.empty();
}

void Tokenizer::push_back(LPCTSTR cstr)
{
    if(cstr){

        // Prepare internal representations
        Vector_Rep.erase(Vector_Rep.begin(),Vector_Rep.end());
        Token_Rep.erase(Token_Rep.begin(),Token_Rep.end());

        Vector_Rep = std::_tstring(cstr);

        // Tokenize now.
        Token TRes;
        for(TIter I = Vector_Rep.begin(); I != Vector_Rep.end(); )
        {
            TRes = find_next_token(Vector_Rep,I);
            if(TRes != Token()) Token_Rep.push_back(TRes);
        }
    }
}

void Tokenizer::push_back(const std::_tstring& VC)
{
    Token_Rep.erase(Token_Rep.begin(),Token_Rep.end());
    Vector_Rep = VC;

    // Tokenize now.
    Token TRes;
    for(TIter I = Vector_Rep.begin(); I != Vector_Rep.end(); )
    {
        TRes = find_next_token(Vector_Rep,I);
        if (!TRes.empty())
        {
           if (TRes != Token()) Token_Rep.push_back(TRes);
        }
    }
}

TString Tokenizer::CS_to_TS(LPCTSTR CS)
{
    TString TS(CS);
    
    return TS;
}

LPTSTR Tokenizer::TS_to_CS(TString &TS)
{
    LPTSTR CS = 0;
    
    if(TS.size())
    {
       CS = new TCHAR[TS.size() + 1];
		 for(std::_tstring::size_type i = 0; i < TS.size(); i++) 
		 {
		    CS[i] = TS[i];
		 }

       CS[TS.size()] = 0;
    }
    
    return CS;
}

Token Tokenizer::find_next_token(TString &TS, TIter &Ti)
{
    // An iterator which points to the end of TS ...
    TIter End_Token = TS.end();
    TIter Ti_Update = TS.end();

    // for each Delimiter ...

    for(std::vector<Delimiter>::iterator VDI = Delims.begin();
        VDI != Delims.end();
        VDI++)
	{
        /* Test, if the actual end of the delimiter is lower than the 
           end of the "rest of TS". 
           TS is searched in the range [ Ti, TS.end() ) */
		if(std::vector<Delimiter>::size_type(TS.end() - Ti) >= (*VDI).size()){
            TIter End;
            if((End = std::search(Ti,TS.end(), 
                                   (*VDI).begin(),(*VDI).end())) < End_Token){
                End_Token = End;
                for(Ti_Update = End_Token + (*VDI).size();
                    std::vector<Delimiter>::size_type(TS.end() - Ti_Update) >= (*VDI).size() && 
                       std::equal((*VDI).begin(),(*VDI).end(),Ti_Update);
                    Ti_Update += (*VDI).size());
            }
        }
	}
    
    // If we have found something, we should copy it into a Token for return. 
    Token T;
    if(End_Token - Ti){
       T.insert(T.begin(),Ti,End_Token);
    }
    
    // Now we have to Update Ti;
    Ti = Ti_Update;

    // And we return the result, be it as it is.
    return T;
}


bool Tokenizer::ParseDouble(LPCTSTR lpszText, Float64* d)
{
	CHECK(lpszText != 0);
	while (*lpszText == _T(' ') || *lpszText == _T('\t'))
		lpszText++;

	TCHAR chFirst = lpszText[0];
   LPTSTR stopstr;
   errno = 0;
	*d = _tcstod(lpszText, &stopstr);
   if (errno != 0 || *stopstr != '\0')
   {
      return false; // could not convert
   }

   if (*d==HUGE_VAL || *d==-HUGE_VAL)
   {
      CHECK(0);
      return false; // overflow or underflow
   }

	while (*stopstr == _T(' ') || *stopstr == _T('\t'))
		stopstr++;

	if (*stopstr != _T('\0'))
		return false;   // not terminated properly

	return true;
}

bool Tokenizer::ParseLong(LPCTSTR lpszText, long* l)
{
	CHECK(lpszText != 0);
	while (*lpszText == _T(' ') || *lpszText == _T('\t'))
		lpszText++;

	TCHAR chFirst = lpszText[0];
   LPTSTR stopstr;
	*l = _tcstol(lpszText, &stopstr, 10);
	if (*l == 0 && chFirst != _T('0'))
		return false;   // could not convert

   if (*l==LONG_MAX || *l==LONG_MIN)
   {
      CHECK(0);
      return false; // overflow or underflow
   }

	while (*stopstr == _T(' ') || *stopstr == _T('\t'))
		stopstr++;

	if (*stopstr != _T('\0'))
		return false;   // not terminated properly

	return true;
}

bool Tokenizer::ParseULong(LPCTSTR lpszText, unsigned long* l)
{
	CHECK(lpszText != 0);
	while (*lpszText == _T(' ') || *lpszText == _T('\t'))
		lpszText++;

	TCHAR chFirst = lpszText[0];
   LPTSTR stopstr;
	*l = _tcstoul(lpszText, &stopstr, 10);
	if (*l == 0 && chFirst != _T('0'))
		return false;   // could not convert

   if (*l==ULONG_MAX )
   {
      CHECK(0);
      return false; // overflow or underflow
   }

	while (*stopstr == _T(' ') || *stopstr == _T('\t'))
		stopstr++;

	if (*stopstr != _T('\0'))
		return false;   // not terminated properly

	return true;
}

bool Tokenizer::ParseShort(LPCTSTR lpszText, short* l)
{
   CHECK(lpszText != 0);
   while (*lpszText == _T(' ') || *lpszText == _T('\t'))
      lpszText++;

   TCHAR chFirst = lpszText[0];
   LPTSTR stopstr;
   *l = (short)_tcstol(lpszText, &stopstr, 10);
   if (*l == 0 && chFirst != _T('0'))
      return false;   // could not convert

   if (*l == SHRT_MAX || *l == SHRT_MIN)
   {
      CHECK(0);
      return false; // overflow or underflow
   }

   while (*stopstr == _T(' ') || *stopstr == _T('\t'))
      stopstr++;

   if (*stopstr != _T('\0'))
      return false;   // not terminated properly

   return true;
}

bool Tokenizer::ParseUShort(LPCTSTR lpszText, unsigned short* l)
{
   CHECK(lpszText != 0);
   while (*lpszText == _T(' ') || *lpszText == _T('\t'))
      lpszText++;

   TCHAR chFirst = lpszText[0];
   LPTSTR stopstr;
   *l = (short)_tcstoul(lpszText, &stopstr, 10);
   if (*l == 0 && chFirst != _T('0'))
      return false;   // could not convert

   if (*l == USHRT_MAX)
   {
      CHECK(0);
      return false; // overflow or underflow
   }

   while (*stopstr == _T(' ') || *stopstr == _T('\t'))
      stopstr++;

   if (*stopstr != _T('\0'))
      return false;   // not terminated properly

   return true;
}

inline std::_tostream &operator<<(std::_tostream &os, const TString &TS) 
{
    for(TString::const_iterator cti = TS.begin();
        cti != TS.end();
        os<<*cti++);

    return os;
}

inline std::_tostream &operator<<(std::_tostream &os, const std::vector<Token> &VT)
{
    os<<_T("[");
    for(std::vector<Token>::const_iterator cvti = VT.begin();
        cvti != VT.end();
        os<<_T(" (")<<*cvti++<<_T(") "));
    os<<_T("]");
    return os;
}
