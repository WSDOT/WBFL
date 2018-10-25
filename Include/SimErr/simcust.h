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
         Copyright 1997    On Target Software    All Rights Reserved

 Dave Pomerantz, Nov 1997.  Updates available at http://www.targetsoft.com
-----------------------------------------------------------------------------
samperr.h  Customized error simulation for the sample program

The error simulator DLL has to be initialized with print functions and error 
types that are specific to each application.

This is the specific information for the sample program.
---------------------------------------------------------------------------*/
#ifndef SIMCUST_H
#define SIMCUST_H

#include "SimErr\simdef.h"  // data definitions used in the function prototypes
#include "SimErr\simerr.h"  // error simulation functions

#include <System\Exception.h>

#define WIN32_LEAN_AND_MEAN
#if defined _AFXDLL
#include <afxwin.h>
#else
#if !defined STRICT
#define STRICT
#endif
#include <Windows.h>
#endif

// These are the different types of errors that you can test.
// If you change this enum, please change the g_errorInfo
// static table in simcust.cpp.
enum ERROR_TYPE
{  // IMPORTANT: The first two entries must always be 
   //            SIMERR_RESULT_ERROR and SIMERR_MEMORY_ERROR
   SIMERR_RESULT_ERROR,        // failing function returns an error code
   SIMERR_MEMORY_ERROR,        // failed to allocate memory
   SIMERR_XBASE_EXCEPTION,     // sysXBase derived exception was thrown
   SIMERR_MFC_EXCEPTION,       // CException derived exception
   NUM_SIMERR_TYPES
};

#define SIMERR_MSGLEN   256
/****************************************************************************
****** NOTE: YOU SHOULD NOT NEED TO CHANGE ANYTHING BELOW THIS COMMENT ******
****************************************************************************/

//==================== DEFINE IF SIMULATING ERRORS ====================
#ifdef SIMERR 

SIMERR_EXPORT bool SimErrCustomInit(int nSeed, SIMERR_TEST_TYPE testType);
//bool SimErrCustomInit(int nSeed, SIMERR_TEST_TYPE testType); 


template <class T>
BOOL SimErrLoadAgents(const char *strFile, int nLine, BOOL bLoaded, T** ppT,
                      long nCount = 1, double nProb = 1.0)
{
   if ((bLoaded) && 
       SimErr(strFile, nLine, SIMERR_RESULT_ERROR, nCount, nProb)) 
   { 
      (*ppT)->Release();
      *ppT = 0;
      bLoaded = FALSE; 
   } 
   return bLoaded;
}

template <class T>
T SimErrHRESULT(const char *strFile, int nLine, T hr, T hrSimResult,  
                long nCount = 1, double nProb = 1.0)
{
   if (SUCCEEDED(hr) && 
       SimErr(strFile, nLine, SIMERR_RESULT_ERROR, nCount, nProb)) 
   { 
      hr = hrSimResult; 
   }
   return hr;
}

template <class T>
T SimErrCopyFile(const char *strFile, int nLine, T nResult, LPCTSTR lpszPathName,
                 long nCount = 1, double nProb = 1.0)
{
   if ((nResult != 0) && 
       SimErr(strFile, nLine, SIMERR_RESULT_ERROR, nCount, nProb)) 
   { 
      ::DeleteFile( lpszPathName );
      nResult = 0; 
   } 
   return nResult;
}

template <class T>
T SimErrDeleteFile(const char *strFile, int nLine, T nResult, LPCTSTR lpszPathName,
                 long nCount = 1, double nProb = 1.0)
{
   if ((nResult != 0) && 
       SimErr(strFile, nLine, SIMERR_RESULT_ERROR, nCount, nProb)) 
   { 
      HANDLE hFile = ::CreateFile( lpszPathName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
      ::CloseHandle( hFile );
      nResult = 0; 
   } 
   return nResult;
}

template <class T>
T SimErrMoveFile(const char *strFile, int nLine, T nResult, LPCTSTR lpszFrom, LPCTSTR lpszTo,
                 long nCount = 1, double nProb = 1.0)
{
   if ((nResult != 0) && 
       SimErr(strFile, nLine, SIMERR_RESULT_ERROR, nCount, nProb)) 
   { 
      ::MoveFile( lpszTo, lpszFrom );
      nResult = 0; 
   } 
   return nResult;
}

inline BOOL SimErrCreateWin(const char *strFile, int nLine, BOOL bCreated, HWND hwnd, 
                 long nCount = 1, double nProb = 1.0)
{
   if ((bCreated) && 
       SimErr(strFile, nLine, SIMERR_RESULT_ERROR, nCount, nProb)) 
   { 
      ::DestroyWindow( hwnd );
      bCreated = FALSE;
   } 
   return bCreated;
}

inline void SimErrException(const char *strFile, int nLine, const sysXBase& except,  
                         long nCount = 1, double nProb = 1.0)
{
   if ( SimErr( strFile, nLine, SIMERR_XBASE_EXCEPTION, nCount, nProb ) )
      except.Throw();
}

template <class T>
inline void SimErrException(const char *strFile, int nLine, T* pExcept,  
                         long nCount = 1, double nProb = 1.0)
{
   if ( SimErr( strFile, nLine, SIMERR_MFC_EXCEPTION, nCount, nProb ) )
      throw (T*)pExcept;
   else
      pExcept->Delete();
}

//================= DEFINE IF NOT SIMULATING ERRORS ====================

#else

inline bool SimErrCustomInit(int , SIMERR_TEST_TYPE )
{ return true; }

template <class T>
BOOL SimErrLoadAgents(const char *strFile, int nLine, BOOL bLoaded, T** ppT,
                      long nCount = 1, double nProb = 1.0)
{
   return bLoaded;
}

template <class T>
T SimErrHRESULT(const char *strFile, int nLine, T hr, T hrSimResult,  
                long nCount = 1, double nProb = 1.0)
{
   return hr;
}

template <class T>
T SimErrCopyFile(const char *strFile, int nLine, T nResult, LPCTSTR lpszPathName,
                 long nCount = 1, double nProb = 1.0)
{
   return nResult;
}

template <class T>
T SimErrDeleteFile(const char *strFile, int nLine, T nResult, LPCTSTR lpszPathName,
                 long nCount = 1, double nProb = 1.0)
{
   return nResult;
}

template <class T>
T SimErrMoveFile(const char *strFile, int nLine, T nResult, LPCTSTR lpszFrom, LPCTSTR lpszTo,
                 long nCount = 1, double nProb = 1.0)
{
   return nResult;
}

inline BOOL SimErrCreateWin(const char *strFile, int nLine, BOOL bCreated, HWND hwnd, 
                 long nCount = 1, double nProb = 1.0)
{
   return bCreated;
}


inline void SimErrException(const char *strFile, int nLine, const sysXBase& except,  
                         long nCount = 1, double nProb = 1.0)
{
}

template <class T>
inline void SimErrException(const char *strFile, int nLine, T* pExcept,  
                         long nCount = 1, double nProb = 1.0)
{
   pExcept->Delete();
}

#endif // SIMERR

#endif // SIMCUST_H

