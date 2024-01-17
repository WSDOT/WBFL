///////////////////////////////////////////////////////////////////////
// Copyright © 1999-2024  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library was developed as part of the Alternate Route Project
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

///////////////////////////////////////////////////////////////////////
// Revision Log
// ============
// May 1997 - Created, Richard Brice, PE
// Oct 1999 - Released as Open Source



#if !defined FEM2D_SymBandedMatrix_H_
#define FEM2D_SymBandedMatrix_H_
#pragma once

#include <ostream>
#include <WBFLTypes.h>

// Hokey class to represent a symmetric banded matrix. 
// Optimized and specialized for the Fem2d library

class  SymBandedMatrix
{
public:
   // exception class that is thrown if Factor or Solve routines go awry.
   class SymBandedSolverException
   {
   public:
      SymBandedSolverException(LONG dof):
      m_OffendingDof(dof)
      {}
      LONG m_OffendingDof;
   };

// Data Members
protected:
   LONG m_Size;
   LONG m_BandWidth;
   Float64 **m_ppMatrix;
   Float64* m_pData; // our memory

// Constructors/Destructor
public:
   SymBandedMatrix(LONG size, LONG bandWidth);
   SymBandedMatrix();
   virtual ~SymBandedMatrix();

   void Resize(LONG size, LONG bw);
   void Zero(); // zero out all elements

// Member Functions
private:
   void Clear();
   // map row, col to storage
   void MapIndex(LONG row, LONG col, LONG* pi, LONG *pj) const
   {
      ATLASSERT(row>=0 && col>=0);
      LONG ti=row;
      LONG tj=col-row;
      if (tj<0)
      {
         // on lower triangle - transpose
         ti=col;
         tj= row-col;
      }
      ATLASSERT(ti<m_Size);
      ATLASSERT(tj<m_Size);
      *pi = ti;
      *pj = tj;
   }

public:
   void Factor();
   void Solve(Float64 *F);

   LONG NumRows() const;
   LONG NumColumns() const;
   LONG BandWidth() const;

   // accessor functions
   Float64 operator()(LONG row,LONG col) const
   {
      LONG i, j;
      MapIndex(row,col, &i, &j);
      if (j<m_BandWidth)
         return m_ppMatrix[i][j];
      else
         return 0.0;
   }

   void SumVal(LONG row,LONG col, Float64& val)
   {
      LONG i, j;
      MapIndex(row,col, &i, &j);
      ATLASSERT(j<m_BandWidth); // can't set value beyond stated bandwidth
      m_ppMatrix[i][j] += val;
   }

   void SetVal(LONG row,LONG col, Float64& val)
   {
      LONG i, j;
      MapIndex(row,col, &i, &j);
      ATLASSERT(j<m_BandWidth); // can't set value beyond stated bandwidth
      m_ppMatrix[i][j] = val;
   }

   friend std::_tostream& operator<< ( std::_tostream& os, SymBandedMatrix& m );

};


#endif // FEM2D_SymBandedMatrix_H_
