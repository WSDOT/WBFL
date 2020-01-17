///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include "stdafx.h"
#include "matrix.h"
#include <iomanip>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Matrix::Matrix(LONG nr,LONG nc)
{
   m_NRows = 0;
   m_NCols = 0;
   m_pMatrix = nullptr;
   Resize(nr,nc);
}

Matrix::Matrix()
{
   m_NRows = 0;
   m_NCols = 0;
   m_pMatrix = nullptr;
}

Matrix::~Matrix()
{
   Clear();
}

void Matrix::Resize(LONG nr,LONG nc)
{
   Clear();
   m_NRows = nr;
   m_NCols = nc;
   m_pMatrix = new Float64[m_NRows*m_NCols];
}

void Matrix::Clear()
{
   if (m_pMatrix)
      {
         delete[] m_pMatrix;
      }
}

void Matrix::Zero()
{
   for (LONG i = 0; i < m_NRows*m_NCols; i++)
      m_pMatrix[i]=0.0;
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

void Matrix::Multiply(const iActLikeMatrix *m,iActLikeMatrix *r,LONG mode)
{
   LONG i,j,k;
   Float64 v;
   LONG left, middle, right;

   // left and right are the dimension of r.
   // middle is the common dimension for both matrices.

   // Set up loop controls
   if ( (mode == AB) || (mode == ABT) )
      {
      // A (this) is not transposed
      left = m_NRows;
      middle = m_NCols;
      }
   else
      {
      // A (this) is transposed
      left = m_NCols;
      middle = m_NRows;
      }

   if ( (mode == AB) || (mode == ATB) )
      {
      // B is not transposed
      right = m->NumColumns();
      }
   else
      {
      // B is transposed
      right = m->NumRows();
      }

   for (i = 0; i < left; i++)
      {
      for (j = 0; j < right; j++)
         {
         v = 0;
         for (k = 0; k < middle; k++)
            {
            // Get matrix indices... Remember the matrix is not really
            // transposed. But the loop counters are setup as if it is.
            LONG r1,c1,r2,c2;
            if ( (mode == AB) || (mode == ABT) )
               {
               r1 = i;
               c1 = k;
               }
            else
               {
               r1 = k;
               c1 = i;
               }

            if ( (mode == AB) || (mode == ATB) )
               {
               r2 = k;
               c2 = j;
               }
            else
               {
               r2 = j;
               c2 = k;
               }

            v += (*this)(r1,c1) * (*m)(r2,c2);
            }
         // Assign v to r
         (*r)(i,j) = v;
         }
      }
}

void Matrix::operator += (const Matrix &m)
{
   LONG i;
   ATLASSERT(m_NRows==m.m_NRows);
   ATLASSERT(m_NCols==m.m_NCols);

   for (i = 0; i < m_NRows*m_NCols; i++)
   {
         m_pMatrix[i] += m.m_pMatrix[i];
   }

}


void Matrix::operator = (const Matrix &m)
{
   LONG i;
   ATLASSERT(m_NRows==m.m_NRows);
   ATLASSERT(m_NCols==m.m_NCols);

   for (i = 0; i < m_NRows*m_NCols; i++)
   {
         m_pMatrix[i] = m.m_pMatrix[i];
   }
}

void Matrix::operator -= (const Matrix &m)
{
   LONG i;
   ATLASSERT(m_NRows==m.m_NRows);
   ATLASSERT(m_NCols==m.m_NCols);

   for (i = 0; i < m_NRows*m_NCols; i++)
   {
         m_pMatrix[i] -= m.m_pMatrix[i];
   }
}

Float64 Matrix::operator()(LONG i,LONG j) const
{
   return m_pMatrix[ Index(i,j) ];
}

Float64 &Matrix::operator() (LONG i,LONG j)
{
   return m_pMatrix[ Index(i,j) ];
}


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

