///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
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
#include <FEA2D\FEA2DLib.h>
#include "Matrix.h"
#include <algorithm>
#include <iomanip>

using namespace WBFL::FEA2D::Internals;

Matrix::Matrix(LONG nr,LONG nc)
{
   m_NRows = 0;
   m_NCols = 0;
   Resize(nr,nc);
}

Matrix::Matrix()
{
   m_NRows = 0;
   m_NCols = 0;
}

void Matrix::Resize(LONG nr,LONG nc)
{
   m_NRows = nr;
   m_NCols = nc;
   m_Matrix.resize(m_NRows*m_NCols);
}

void Matrix::Zero()
{
   std::fill(m_Matrix.begin(), m_Matrix.end(), 0.0);
}

void Matrix::GetSize(LONG &nr,LONG &nc) const
{
   nr = m_NRows;
   nc = m_NCols;
}

void Matrix::SetElement(LONG r,LONG c,Float64 val)
{
   (*this)(r,c) = val;
}

Float64 Matrix::GetElement(LONG r,LONG c) const
{
   return (*this)(r,c);
}

LONG Matrix::NumRows() const
{
   return m_NRows;
}

LONG Matrix::NumColumns() const
{
   return m_NCols;
}

// Multiply() is now a template defined in Matrix.h - see the revision-log
// note there for why.

void Matrix::operator += (const Matrix &m)
{
   CHECK(m_NRows==m.m_NRows);
   CHECK(m_NCols==m.m_NCols);

   for (LONG i = 0; i < m_NRows*m_NCols; i++)
   {
      m_Matrix[i] += m.m_Matrix[i];
   }
}

Matrix& Matrix::operator = (const Matrix &m)
{
   CHECK(m_NRows==m.m_NRows);
   CHECK(m_NCols==m.m_NCols);

   m_Matrix = m.m_Matrix;
   return *this;
}

void Matrix::operator -= (const Matrix &m)
{
   CHECK(m_NRows==m.m_NRows);
   CHECK(m_NCols==m.m_NCols);

   for (LONG i = 0; i < m_NRows*m_NCols; i++)
   {
      m_Matrix[i] -= m.m_Matrix[i];
   }
}

Float64 Matrix::operator()(LONG i,LONG j) const
{
   return m_Matrix[ Index(i,j) ];
}

Float64 &Matrix::operator() (LONG i,LONG j)
{
   return m_Matrix[ Index(i,j) ];
}


namespace WBFL::FEA2D::Internals
{
   std::_tostream& operator << (std::_tostream &os,const Matrix &m)
   {
      LONG i,j;

      for (i = 0; i < m.m_NRows; i++)
      {
         for (j = 0; j < m.m_NCols; j++)
         {
            os << std::showpoint <<std::scientific << std::setw(10) << std::setprecision(3) << m.GetElement(i,j) << " ";
         }
         os << std::endl;
      }
      os << std::endl;

      return os;
   }
}

