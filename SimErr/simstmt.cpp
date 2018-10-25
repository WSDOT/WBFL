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
simstmt.cpp  implementation of CSimStmt

CSimStmt represents a single error function.  CErrorSimulator maintains
an array of these objects.
---------------------------------------------------------------------------*/
#include <System\SysLib.h>

#include <stdio.h>
#include <string.h>
#include "simstmt.h"

/*---------------------------------------------------------------------------
CSimStmt void constructor
---------------------------------------------------------------------------*/
CSimStmt::CSimStmt(void)
{
   m_strFile[0]   = 0;
   m_nLine        = 0;
   m_nType        = 0;
   m_nPrevCount   = 0;
   m_nSessCount   = 0;
   m_nTargetCount = 0;
   m_nProb        = 0.0;
}

/*---------------------------------------------------------------------------
CSimStmt parameterized constructor
---------------------------------------------------------------------------*/
CSimStmt::CSimStmt(const char * strFile,   // name of source file   
                   int nLine,              // line number in source file  
                   int nType,              // error or exception type
                   long nTarget,           // number of times to simulate error
                   double nProb)           // probability of random error
{
   strcpy(m_strFile, strFile);
   m_nLine        = nLine;
   m_nType        = nType;
   m_nPrevCount   = 0;
   m_nSessCount   = 0;
   m_nTargetCount = nTarget;
   m_nProb        = nProb;
}

/*---------------------------------------------------------------------------
CSimStmt copy constructor
---------------------------------------------------------------------------*/
CSimStmt::CSimStmt(const CSimStmt &src)   
{
   *this = src;
}


/*---------------------------------------------------------------------------
CSimStmt destructor
---------------------------------------------------------------------------*/
CSimStmt::~CSimStmt(void)
{
}

/*---------------------------------------------------------------------------
CSimStmt assignment operator
---------------------------------------------------------------------------*/
CSimStmt &CSimStmt::operator=(const CSimStmt &src) 
{  
   strcpy(m_strFile, src.m_strFile);
   m_nLine        = src.m_nLine;
   m_nType        = src.m_nType;
   m_nPrevCount   = src.m_nPrevCount;
   m_nSessCount   = src.m_nSessCount;
   m_nTargetCount = src.m_nTargetCount;
   m_nProb        = src.m_nProb;
   return *this; 
}

/*---------------------------------------------------------------------------
CSimStmt equality operator, for STL vector support
         compares filename and line number

Note:    Although this function is required by STL, it's not actually used to 
         sort the vector if CSimStmt objects.  The statements are sorted in
         their arrival order.  That way, the simulation that most recently
         fired is the last one in the log file.
---------------------------------------------------------------------------*/
bool operator==(const CSimStmt &lhs, const CSimStmt &rhs)
{
   bool bEqual = (strcmp(lhs.m_strFile, rhs.m_strFile) == 0);
   if (bEqual)
   {
      bEqual = (lhs.m_nLine == rhs.m_nLine);
   }
   return bEqual;
}

/*---------------------------------------------------------------------------
CSimStmt less-than operator, for STL vector support
         compares filename and line number
---------------------------------------------------------------------------*/
int operator<(const CSimStmt &lhs, const CSimStmt &rhs)
{
   int nCompare = strcmp(lhs.m_strFile, rhs.m_strFile);
   if (nCompare == 0)
   {
      nCompare = (lhs.m_nLine < rhs.m_nLine) ? 1 : 0;
   }
   else if (nCompare < 0)
   {
      nCompare = 1;
   }
   else
   {
      nCompare = 0;
   }
   return nCompare;
}

/*---------------------------------------------------------------------------
Read           Read a line from the log file and scan it into this object
---------------------------------------------------------------------------*/
bool CSimStmt::Read(FILE *pFile)   // pointer to the open log file
{
   char  strInput[ARCHIVE_LINE_LEN];
   bool  bOK = false;
   int   nResult;
   char *pResult;

   pResult = fgets(strInput, ARCHIVE_LINE_LEN, pFile);
   if (pResult)
   {
      nResult = sscanf(strInput, "%s %ld %d %ld %ld %lf",
                                  m_strFile,
                                  &m_nLine,
                                  &m_nType,
                                  &m_nPrevCount,
                                  &m_nTargetCount,
                                  &m_nProb);
      m_nSessCount = 0;
      bOK = (nResult == 6);
   }
   return bOK;
}

/*---------------------------------------------------------------------------
Write          Format a test line entry into a line in the log file.
---------------------------------------------------------------------------*/
bool CSimStmt::Write(FILE *pFile)   // pointer to the open log file
{
   int  nResult;
   char strOutput[ARCHIVE_LINE_LEN];
   bool bOK = false;

   nResult = sprintf(strOutput, "%s %ld %d %ld %ld %7.2lf\n",
                                 m_strFile,
                                 m_nLine,
                                 m_nType,
                                 m_nPrevCount + m_nSessCount,
                                 m_nTargetCount,
                                 m_nProb);
   if (nResult < ARCHIVE_LINE_LEN)
   {
      nResult = fputs(strOutput, pFile);
      if (nResult != EOF)
      {
         bOK = true;
      }
   }
   return bOK;
}

/*---------------------------------------------------------------------------
TrimFilePath    remove the path prefixing a filename
---------------------------------------------------------------------------*/
void CSimStmt::TrimFilePath(char* filename, const char *fullpath)
{
	const char *p = fullpath;

	// Trim the path off the filename
	p += strlen(p) - 1;
	while (p >= fullpath)
	{
		if ((*p == '\\') || (*p == '/'))
		{
			++p;
			break;
		}
		--p;
	}
	if (p < fullpath)
	{
		//p == fullpath; // code from original developer?
      p = fullpath;
	}
	strncpy(filename, p, FILENAME_LEN);
   filename[FILENAME_LEN-1] = 0;
}	

