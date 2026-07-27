///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
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
// 2026     - Multiply() was originally virtual-dispatched through the
//            iActLikeVector/iActLikeMatrix interfaces so it could accept
//            either a Matrix or a Vector6 operand. Only those two types
//            ever implemented the interfaces (a closed set, not an open
//            extensibility point), so the virtual call on every element
//            access in the inner loop bought nothing but overhead -
//            replaced with a concept-constrained template that the
//            compiler can fully inline.
// 2026     - m_pMatrix was a raw new[]/delete[] buffer with no copy
//            constructor (only a hand-written copy assignment), so the
//            compiler-generated copy constructor did a shallow pointer
//            copy - a latent double-free bug waiting for the first
//            `Matrix a = b;`. Replaced with std::vector<Float64>, which
//            gives Matrix a correct deep-copying constructor for free.
//            Every Matrix in this codebase is 6x6 at most (Member's local
//            matrices/transforms; the real global stiffness matrix is the
//            separate, banded-storage SymBandedMatrix), so this has no
//            measurable performance effect - operator() compiles to the
//            same single indexed load/store either way.

#if !defined FEA2D_MATRIX_H_
#define FEA2D_MATRIX_H_
#pragma once

#include <array>
#include <vector>
#include <ostream>
#include <concepts>
#include <System\Checks.h>

/********
This really should be part of a matrix math library
******/

namespace WBFL
{
   namespace FEA2D
   {
      namespace Internals
      {

/// Which operand(s) of Matrix::Multiply() are treated as transposed.
enum class MultiplyMode
{
   AB,    // neither operand transposed
   ATB,   // this (A) transposed
   ABT,   // b transposed
   ATBT   // both transposed
};

/// Anything that can be read like a matrix: element access via
/// operator()(row,col), plus NumRows()/NumColumns(). Matrix::Multiply()
/// only ever needs to read its "b" operand, so this is sufficient for it.
template <typename T>
concept MatrixLike = requires(const T& t, LONG i, LONG j)
{
   { t(i, j) } -> std::convertible_to<Float64>;
   { t.NumRows() } -> std::convertible_to<LONG>;
   { t.NumColumns() } -> std::convertible_to<LONG>;
};

/// A MatrixLike that can also be written to via operator()(row,col) - what
/// Matrix::Multiply() needs for its result ("c") operand.
template <typename T>
concept MutableMatrixLike = MatrixLike<T> && requires(T& t, LONG i, LONG j)
{
   { t(i, j) } -> std::same_as<Float64&>;
};

class  Matrix
{
// Data Members
protected:
   LONG m_NRows;
   LONG m_NCols;
   std::vector<Float64> m_Matrix;

   LONG Index( LONG r, LONG c ) const { return r + m_NCols * c; }

// Constructors/Destructor
public:
   Matrix(LONG nr,LONG nc);
   Matrix();
   Matrix(const Matrix&) = default;
   Matrix(Matrix&&) = default;
   ~Matrix() = default;

   void Resize(LONG nr,LONG nc);
   friend std::_tostream& operator<< ( std::_tostream& os, const Matrix& m );

// Member Functions
public:
   void    GetSize(LONG &nr,LONG &nc) const;
   void    SetElement(LONG r,LONG c,Float64 val);
   Float64  GetElement(LONG r,LONG c) const;

   /// Computes this * b (or a transposed variant per mode) and stores the
   /// result in c. b and c may each independently be a Matrix or a Vector6
   /// (or anything else satisfying MatrixLike/MutableMatrixLike) - the
   /// element type is resolved at compile time, so there's no virtual
   /// dispatch in the inner loop.
   template <MatrixLike TB, MutableMatrixLike TC>
   void Multiply(const TB& b, TC& c, MultiplyMode mode = MultiplyMode::AB) const
   {
      LONG left, middle, right;

      // left and right are the dimension of c.
      // middle is the common dimension for both matrices.

      // Set up loop controls
      if (mode == MultiplyMode::AB || mode == MultiplyMode::ABT)
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

      if (mode == MultiplyMode::AB || mode == MultiplyMode::ATB)
      {
         // B is not transposed
         right = b.NumColumns();
      }
      else
      {
         // B is transposed
         right = b.NumRows();
      }

      for (LONG i = 0; i < left; i++)
      {
         for (LONG j = 0; j < right; j++)
         {
            Float64 v = 0;
            for (LONG k = 0; k < middle; k++)
            {
               // Get matrix indices... Remember the matrix is not really
               // transposed. But the loop counters are setup as if it is.
               LONG r1, c1, r2, c2;
               if (mode == MultiplyMode::AB || mode == MultiplyMode::ABT)
               {
                  r1 = i;
                  c1 = k;
               }
               else
               {
                  r1 = k;
                  c1 = i;
               }

               if (mode == MultiplyMode::AB || mode == MultiplyMode::ATB)
               {
                  r2 = k;
                  c2 = j;
               }
               else
               {
                  r2 = j;
                  c2 = k;
               }

               v += (*this)(r1, c1) * b(r2, c2);
            }
            // Assign v to c
            c(i, j) = v;
         }
      }
   }

   LONG    NumRows() const;
   LONG    NumColumns() const;
   void Zero();

   Matrix& operator = (const Matrix &m);
   Matrix& operator = (Matrix&&) = default;
   void operator += (const Matrix &m);
   void operator -= (const Matrix &m);
   Float64 operator()(LONG i,LONG j) const;
   Float64 &operator()(LONG i,LONG j);
};

// Fixed-size vector, N known at compile time (a non-type template parameter,
// same pattern as Result<TNForceDof,TNDispDof>) rather than a constructor
// argument like Matrix's - that's what makes this zero-overhead: N is baked
// into the generated code for each instantiation, so std::array<Float64,N>
// below compiles to exactly the same layout/codegen as a hand-written
// Float64 m_Vec[N] would, with no heap allocation and nothing for the
// optimizer to lose by comparison.
template <LONG N>
class  Vector
{
private:
   std::array<Float64, N> m_Vec{};
public:

   Float64 operator()(LONG i) const
   {
      CHECK(i<N);
      return m_Vec[i];
   }

   Float64 &operator() (LONG i)
   {
      CHECK(i<N);
      return m_Vec[i];
   }

   Float64 operator()(LONG i,LONG j) const
   {
      CHECK(i<N);
      CHECK(j==0);
      return m_Vec[i];
   }

   Float64& operator()(LONG i,LONG j)
   {
      CHECK(i<N);
      CHECK(j==0);
      return m_Vec[i];
   }

   LONG NumRows() const
   {
      return N;
   }

   LONG NumColumns() const
   {
      return 1;
   }

   void operator += (const Vector &m)
   {
      for (LONG i = 0; i < N; i++)
      {
         m_Vec[i] += m.m_Vec[i];
      }
   }

   void operator -= (const Vector &m)
   {
      for (LONG i = 0; i < N; i++)
      {
         m_Vec[i] -= m.m_Vec[i];
      }
   }

   void Zero()
   {
      m_Vec.fill(0.0);
   }
};

// Member's local/global force and deflection vectors are always 6 elements
// (Member::TotalDOF) - kept as a named alias so existing call sites don't
// need to spell out Vector<6> everywhere.
using Vector6 = Vector<6>;


      }; // namespace Internals
   }; // namespace FEA2D
}; // namespace WBFL

#endif // FEA2D_MATRIX_H_
