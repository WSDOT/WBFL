///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

/*---------------------------------------------------------------------------
Copyright (c) 1998 by On Target Software. Permission is granted to use this
source code only if this copyright notice and the web address
http://www.targetsoft.com both appear at the beginning of all source files
that contain excerpts or complete copies of the code herein.

Dave Pomerantz, March 1998.  Updates available at http://www.targetsoft.com
-----------------------------------------------------------------------------
simstmt.h  definition of CSimStmt

CSimStmt represents a single simulator statement, which is a function call
to the simulator in a particular source file, at a particular line number.  

CErrorSimulator maintains an array of these objects, representing all the
places the source program wants to simulate errors.
---------------------------------------------------------------------------*/
#ifndef SIMSTMT_H
#define SIMSTMT_H

//---------------------------------------------------------------------------
class CSimStmt
{
public:     // constants
   enum { ARCHIVE_LINE_LEN = 256 };
   enum { FILENAME_LEN = 256 };

public:     // data members
   char     m_strFile[FILENAME_LEN];   // source filename
   long     m_nLine;         // line number within file
   int      m_nType;         // type of error
   long     m_nPrevCount;    // count at start of session
   long     m_nSessCount;    // count added during session
   long     m_nTargetCount;  // total failure count requested
   double   m_nProb;         // probability of random failure

   // static functions
   static void TrimFilePath(char* filename, const char *fullpath);
   
   // constructors, destructor
   CSimStmt(void);
   CSimStmt(const char * strFile, int nLine, int nType, 
            long nTarget=1, double nProb=1.0);
   CSimStmt(const CSimStmt &src);
   virtual ~CSimStmt(void);

   // assignment
   CSimStmt &operator=(const CSimStmt &src);
   // equality (STL required operator)
   friend bool operator==(const CSimStmt &lhs, const CSimStmt &rhs);
   // less-than (STL required operator)
   friend int operator<(const CSimStmt &lhs, const CSimStmt &rhs);

   // read/write a line from the log file from/to a CSimStmt
   bool Read(FILE *pFile);
   bool Write(FILE *pFile);
};

#endif //SIMSTMT_H

