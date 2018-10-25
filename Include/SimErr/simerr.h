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
 SIMERR.h   MACROS FOR FORCING ERRORS AND EXCEPTIONS
                 Public Interface Header File
-----------------------------------------------------------------------------
Insert calls to these function templates after your own program statements 
that may generate errors or throw exceptions.  If SIMERR is defined, the 
SimXXX functions will return errors and throw exceptions.  This tests
the effectiveness of error detection, propagation and recovery.
---------------------------------------------------------------------------*/
#ifndef SIMERR_H
#define SIMERR_H

#include "simdef.h"  // data definitions used in the function prototypes



//==================== DEFINE ONLY IF SIMULATING ERRORS ====================
#ifdef SIMERR 

SIMERR_EXPORT bool SimErrInit(simerrInit_t *pInit);

SIMERR_EXPORT void SimErrExit  (bool bFullReport=true);
SIMERR_EXPORT bool SimErrEnable(bool bEnable = true);

SIMERR_EXPORT bool SimErr(const char *file,  // source file name
                          int line,          // source file line
                          int nType,         // app-defined error type
                          long nCount=1,     // # times to simulate
                          double nProb=1.0); // probability each time

//---------------------------------------------------------------------------
// Simulate errors in functions that return zero on success
template <class T>
T SimErrResult(const char *strFile, int nLine, T nResult, T nSimResult,  
               long nCount = 1, double nProb = 1.0)
{
   if ((nResult == 0) && 
       SimErr(strFile, nLine, SIMERR_RESULT_ERROR, nCount, nProb)) 
   { 
      nResult = nSimResult; 
   }
   return nResult;
}
//---------------------------------------------------------------------------
// Simulate errors in functions that return non-zero on success
template <class T>
T SimErrZero(const char *strFile, int nLine, T nResult, 
             long nCount = 1, double nProb = 1.0)
{
   if ((nResult != 0) && 
       SimErr(strFile, nLine, SIMERR_RESULT_ERROR, nCount, nProb)) 
   { 
      nResult = 0; 
   } 
   return nResult;
}
//---------------------------------------------------------------------------
// Simulate failed C++ allocation
template <class T>
T *SimErrNew(const char *strFile, int nLine, T *pObject, 
          long nCount = 1, double nProb = 1.0)
{
   if ((pObject != NULL) && 
       SimErr(strFile, nLine, SIMERR_MEMORY_ERROR, nCount, nProb)) 
   { 
      delete pObject;
      pObject = 0;
   } 
   return pObject;
}
//---------------------------------------------------------------------------
// Simulate failed C allocation
template <class T>
T *SimErrMalloc(const char *strFile, int nLine, T *pData, 
                 long nCount = 1, double nProb = 1.0)
{
   if ((pData != NULL) && 
       SimErr(strFile, nLine, SIMERR_MEMORY_ERROR, nCount, nProb)) 
   { 
      free(pData);
      pData = NULL;
   } 
   return pData;
}
//---------------------------------------------------------------------------
// Simulate exceptions
inline void SimErrException(const char *strFile, int nLine, int nType,  
                         long nCount = 1, double nProb = 1.0)
{
   SimErr(strFile, nLine, nType, nCount, nProb);
}




//================= DEFINE ONLY IF NOT SIMULATING ERRORS ====================
#else
#pragma warning( disable : 4100 )   
inline bool SimErrInit(simerrInit_t *pInit ) 
{ return true; }

inline void SimErrExit(bool bFullReport = true)
{}

inline bool SimErrEnable(bool bEnable = true)
{ return false; }

template <class T>
T SimErrResult(const char *, int , T nResult, T ,  
          long nCount = 1, double nProb = 1.0)
{
#pragma warning( disable : 4100 )   
   return nResult; 
}

template <class T>
T SimErrZero(const char *, int , T nResult, 
           long nCount = 1, double nProb = 1.0)
{ 
#pragma warning( disable : 4100 )   
   return nResult;
}

template <class T>
T *SimErrNew(const char *, int , T *pObject, 
             long nCount = 1, double nProb = 1.0)
{
#pragma warning( disable : 4100 )   
   return pObject; 
}

template <class T>
T *SimErrMalloc(const char *, int , T *pData, 
                long nCount = 1, double nProb = 1.0)
{
#pragma warning( disable : 4100 )   
   return pData; 
}

inline void SimErrException(const char *, int , int , 
                         long nCount = 1, double nProb = 1.0)
{}
#pragma warning( default : 4100 )   

#endif // SIMERR


#endif // SIMERR_H

