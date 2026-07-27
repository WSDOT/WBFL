///////////////////////////////////////////////////////////////////////
// Copyright � 1999-2026  Washington State Department of Transportation
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

// Ported near-verbatim from Fem2d\SymBandedMatrix.h - internal implementation
// detail, not part of the public FEA2D API (lives in FEA2D\ rather than
// Include\FEA2D\, same convention the original followed). Only change from
// the original: ATLASSERT -> CHECK (this library never includes ATL
// headers) and the WBFL::FEA2D::Internals namespace.

#pragma once

#include <ostream>
#include <WBFLTypes.h>
#include <System\Checks.h>

namespace WBFL
{
   namespace FEA2D
   {
      namespace Internals
      {
         // Hokey class to represent a symmetric banded matrix.
         // Optimized and specialized for the FEA2D library
         class SymBandedMatrix
         {
         public:
            // exception class that is thrown if Factor or Solve routines go awry.
            class SymBandedSolverException
            {
            public:
               SymBandedSolverException(LONG dof) :
                  m_OffendingDof(dof)
               {}
               LONG m_OffendingDof;
            };

         protected:
            LONG m_Size;
            LONG m_BandWidth;
            Float64** m_ppMatrix;
            Float64* m_pData; // our memory

         public:
            SymBandedMatrix(LONG size, LONG bandWidth);
            SymBandedMatrix();

            // m_ppMatrix/m_pData are raw-owned (see Resize()/Clear() in the
            // .cpp) - this class predates std::vector and is left alone here
            // (it's the hot-path global stiffness matrix; a storage rewrite
            // needs its own performance verification, tracked separately).
            // Nothing in this codebase copies or moves a SymBandedMatrix
            // today, so rather than let the compiler silently generate a
            // shallow-copying copy ctor/assignment (a double-free
            // waiting to happen), every special member this class doesn't
            // actually support is explicitly deleted - an attempt to copy
            // or move one is now a compile error instead of a latent bug.
            SymBandedMatrix(const SymBandedMatrix&) = delete;
            SymBandedMatrix& operator=(const SymBandedMatrix&) = delete;
            SymBandedMatrix(SymBandedMatrix&&) = delete;
            SymBandedMatrix& operator=(SymBandedMatrix&&) = delete;

            virtual ~SymBandedMatrix();

            void Resize(LONG size, LONG bw);
            void Zero(); // zero out all elements

         private:
            void Clear();
            // map row, col to storage
            void MapIndex(LONG row, LONG col, LONG* pi, LONG* pj) const
            {
               CHECK(row >= 0 && col >= 0);
               LONG ti = row;
               LONG tj = col - row;
               if (tj < 0)
               {
                  // on lower triangle - transpose
                  ti = col;
                  tj = row - col;
               }
               CHECK(ti < m_Size);
               CHECK(tj < m_Size);
               *pi = ti;
               *pj = tj;
            }

         public:
            void Factor();
            void Solve(Float64* F);

            LONG NumRows() const;
            LONG NumColumns() const;
            LONG BandWidth() const;

            // accessor functions
            Float64 operator()(LONG row, LONG col) const
            {
               LONG i, j;
               MapIndex(row, col, &i, &j);
               if (j < m_BandWidth)
                  return m_ppMatrix[i][j];
               else
                  return 0.0;
            }

            void SumVal(LONG row, LONG col, Float64& val)
            {
               LONG i, j;
               MapIndex(row, col, &i, &j);
               CHECK(j < m_BandWidth); // can't set value beyond stated bandwidth
               m_ppMatrix[i][j] += val;
            }

            void SetVal(LONG row, LONG col, Float64& val)
            {
               LONG i, j;
               MapIndex(row, col, &i, &j);
               CHECK(j < m_BandWidth); // can't set value beyond stated bandwidth
               m_ppMatrix[i][j] = val;
            }

            friend std::_tostream& operator<<(std::_tostream& os, SymBandedMatrix& m);
         };
      };
   };
};
