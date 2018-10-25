///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// Revision Log
// ============
// May 1997 - Created, Richard Brice, PE
// Oct 1999 - Released as Open Source

#if !defined FEM2D_MATRIX_H_
#define FEM2D_MATRIX_H_
#pragma once

#include <vector>
#include <ostream>

/********
This really should be part of a matrix math library
******/

#define AB        0
#define ATB       1
#define ABT       2
#define ATBT      3

class iActLikeVector
{
public:
   virtual Float64 operator()(LONG i) const =0;
   virtual Float64 &operator()(LONG i) =0;
   virtual LONG    NumRows() const =0;
};

class iActLikeMatrix
{
public:
   virtual Float64 operator()(LONG i,LONG j) const =0;
   virtual Float64 &operator()(LONG i,LONG j) =0;
   virtual LONG    NumRows() const =0;
   virtual LONG    NumColumns() const =0;
};


class  Matrix: public iActLikeMatrix
{
// Data Members
protected:
   LONG m_NRows;
   LONG m_NCols;
   Float64* m_pMatrix;

   LONG Index( LONG r, LONG c ) const { return r + m_NCols * c; }

// Constructors/Destructor
public:
   Matrix(LONG nr,LONG nc);
   Matrix();
   virtual ~Matrix();

   void Resize(LONG nr,LONG nc);
   friend std::_tostream& operator<< ( std::_tostream& os, const Matrix& m );

// Member Functions
private:
   void Clear();

public:
   void    GetSize(LONG &nr,LONG &nc) const;
   void    SetElement(LONG r,LONG c,Float64 val);
   Float64  GetElement(LONG r,LONG c) const;
   void    Multiply(const iActLikeMatrix *b,iActLikeMatrix *c,LONG mode = AB);
   LONG    NumRows() const;
   LONG    NumColumns() const;
   void Zero();

   void operator = (const Matrix &m);
   void operator += (const Matrix &m);
   void operator -= (const Matrix &m);
   Float64 operator()(LONG i,LONG j) const;
   Float64 &operator()(LONG i,LONG j);
};

// Vector of length 6. Would be very easy to make this a fixed size vector
// template class, but let's give the optimizer all the chances possible
class  Vector6 : public  iActLikeVector, public  iActLikeMatrix
{
private:
   Float64 m_Vec[6];
public:

   virtual Float64 operator()(LONG i) const
   {
      ATLASSERT(i<6);
      return m_Vec[i];
   }

   virtual Float64 &operator() (LONG i)
   {
      ATLASSERT(i<6);
      return m_Vec[i];
   }

   virtual Float64 operator()(LONG i,LONG j) const
   {
      ATLASSERT(i<6);
      ATLASSERT(j==0);
      return m_Vec[i];
   }

   virtual Float64& operator()(LONG i,LONG j)
   {
      ATLASSERT(i<6);
      ATLASSERT(j==0);
      return m_Vec[i];
   }

   virtual LONG NumRows() const
   {
      return 6;
   }

   virtual LONG NumColumns() const
   {
      return 1;
   }

   void operator += (const Vector6 &m)
   {
      for (int i = 0; i < 6; i++)
      {
         m_Vec[i] += m.m_Vec[i];
      }
   }

   void operator -= (const Vector6 &m)
   {
      for (int i = 0; i < 6; i++)
      {
         m_Vec[i] -= m.m_Vec[i];
      }
   }

   void Zero()
   {
      for (int i = 0; i < 6; i++)
      {
         m_Vec[i] = 0.0;
      }
   }
};


#endif // FEM2D_MATRIX_H_
