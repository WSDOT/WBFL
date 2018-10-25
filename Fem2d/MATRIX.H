///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2010  Washington State Department of Transportation
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

class  Matrix
{
// Data Members
protected:
   long m_NRows;
   long m_NCols;
   Float64 **m_ppMatrix;

// Constructors/Destructor
public:
   Matrix(long nr,long nc);
   Matrix();
   virtual ~Matrix();

   void Resize(long nr,long nc);
   friend std::ostream& operator<< ( std::ostream& os, const Matrix& m );


// Member Functions
private:
   void Clear();

public:
   void    GetSize(long &nr,long &nc) const;
   void    SetElement(long r,long c,Float64 val);
   Float64  GetElement(long r,long c) const;
   void    Multiply(const Matrix *b,Matrix *c,long mode = AB);
   long    NumRows() const;
   long    NumColumns() const;
   void Zero();

   void operator = (const Matrix &m);
   void operator += (const Matrix &m);
   void operator -= (const Matrix &m);
   Float64 operator()(long i,long j) const;
   Float64 &operator()(long i,long j);
};

class  Vector : public Matrix
{
public:
   Vector(long nr) : Matrix(nr,1) {};
   Float64 operator()(long i) const;
   Float64 &operator()(long i);
};


#endif // FEM2D_MATRIX_H_
