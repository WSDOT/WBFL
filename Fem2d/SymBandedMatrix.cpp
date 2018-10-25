///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2017  Washington State Department of Transportation
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

#include "stdafx.h"
#include <iomanip>
#include "SymBandedMatrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SymBandedMatrix::SymBandedMatrix(LONG size, LONG bw)
{
   m_Size = 0;
   m_BandWidth = 0;
   m_ppMatrix = 0;
   m_pData = 0;
   Resize(size,bw);
}

SymBandedMatrix::SymBandedMatrix()
{
   m_Size = 0;
   m_BandWidth = 0;
   m_ppMatrix = nullptr;
   m_pData = 0;
}

SymBandedMatrix::~SymBandedMatrix()
{
   Clear();
}

void SymBandedMatrix::Resize(LONG size, LONG bw)
{
   ATLASSERT(m_Size >= 0);
   ATLASSERT(m_BandWidth >= 0);
   ATLASSERT(m_Size>=m_BandWidth);

   // no reason to reallocate if being resized to same size
   if (m_ppMatrix==0 || size!=m_Size || bw!=m_BandWidth)
   {
      Clear();
      m_Size = size;
      m_BandWidth = bw;

      m_ppMatrix = new Float64*[m_Size];

      // allocate entire matrix in a single chunk rather than multiple allocations
      m_pData =    new Float64[m_Size*m_BandWidth];

      for (LONG i = 0; i<m_Size; i++)
         m_ppMatrix[i] = m_pData+(i*m_BandWidth);
   }
}

void SymBandedMatrix::Zero()
{
   ATLASSERT(m_pData!=0);
   ATLASSERT(m_ppMatrix!=0);

   Float64* p = m_pData;
   for (LONG i = 0; i<m_Size*m_BandWidth; i++)
   {
       *p= 0.0;
       ++p;
   }
}

void SymBandedMatrix::Clear()
{
   if (m_ppMatrix)
   {
      delete[] m_ppMatrix;
      delete[] m_pData;
   }
}

LONG SymBandedMatrix::NumRows() const
{
   return m_Size;
}

LONG SymBandedMatrix::NumColumns() const
{
   return m_Size;
}

LONG SymBandedMatrix::BandWidth() const
{
   return m_BandWidth;
}

std::_tostream& operator<< ( std::_tostream& os, SymBandedMatrix& m )
{
   LONG i,j;

   os << std::showpoint<< std::scientific << std::setw(10) << std::setprecision(3);

   for (i = 0; i < m.NumColumns(); i++)
   {
      for (j = 0; j < m.NumRows(); j++)
      {
          os << m(i,j)<<"  ";
      }
      os << std::endl;
   }
   os << std::endl;

   return os;
}


void SymBandedMatrix::Factor()
{
/*------------------------------------------------------------------
  symmetric, banded matrix equation solver
  gauss-doolittle method
  solves equations [KBand]{x}={FBand}
  Original Fortran source code by Walter Haisler of Texas A&M University
  converted to C by Richard Brice. Hacked once again by Richard Pickings in 12/00

  Usage:
      1) Factor the matrix into triangular form by calling Factor. 
         This triangularizes the matrix in preparation for back substitution.
      2) Call Solve for as many right hand sides as you have.

  Warning:
  This routine assumes that the matrix is positive definite and
  diagonally dominate. It attempts to throw an exception for zero or negative
  pivot numbers, but may provide garbage solutions to ill-conditioned matrices.
*/

	LONG nrs, nr, n, mr, m, i, j, k, l;
	Float64 pivot, cp;

	nrs = m_Size - 1;
	nr = m_Size;

	/**************************************/
	/* perform triangularization of KBand */
	/**************************************/

   for (n = 1; n <= nrs; n++)
   {
      m = n - 1;
      mr = Min(m_BandWidth,nr-m);
      pivot = m_ppMatrix[n-1][0];
      if (pivot<=0.0)
      {
          SymBandedSolverException e(n);
          throw e;
      }

      for (l = 2; l <= mr; l++)
      {
         cp = m_ppMatrix[n-1][l-1]/pivot;
         i = m + l;
         j = 0;
         for (k = l;k <= mr;k++)
         {
            j++;
            m_ppMatrix[i-1][j-1] -= cp*m_ppMatrix[n-1][k-1];
         }
         m_ppMatrix[n-1][l-1] = cp;
      }
   }
}

void SymBandedMatrix::Solve(Float64 *F)
{

	/*******************************/
	/* foward elimination of F */
	/*******************************/

	LONG nrs = m_Size - 1;
	LONG nr = m_Size;
   LONG mr, i, k, l, m, n;
   Float64 cp, cd;

   for (n = 1;n <= nrs;n++)
   {
      m = n - 1;
      mr = Min(m_BandWidth,nr-m);
      cp = F[n-1];
      cd = m_ppMatrix[n-1][0];
      if ( cd != 0.0) // don't allow divide by zero
      {
         F[n-1] = cp/cd;
         for (l = 2;l <= mr;l++)
         {
            i = m + l;
            F[i-1] -= m_ppMatrix[n-1][l-1]*cp;
         }
      }
      else
      {
          SymBandedSolverException e(n-1);
          throw e;
      }
   }

	  /********************************************/
	  /* backward substitution to obtain solution */
	  /********************************************/

   Float64 d=m_ppMatrix[nr-1][0];
   if (d<=0.0)
   {
       SymBandedSolverException e(nr-1);
       throw e;
   }

   F[nr-1] /= d;
   for (i = 1;i <= nrs;i++)
   {
      n = nr - i;
      m = n - 1;
      mr = Min(m_BandWidth,nr-m);
      for (k = 2;k <= mr;k++)
      {
         l = m + k;
         F[n-1] -= m_ppMatrix[n-1][k-1]*F[l-1];
      }
   }
}

