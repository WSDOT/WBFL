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
SIMDEF.h   Data definitions used in simulation function prototypes

This file defines the data types used by the error simulation functions.
---------------------------------------------------------------------------*/
#ifndef SIMDEF_H
#define SIMDEF_H


#ifdef SIMERR_DLL
#define SIMERR_EXPORT __declspec(dllexport)
#else
#define SIMERR_EXPORT __declspec(dllimport)
#endif

// SIMERR_ISEXCEPTION is more obvious than true/false
enum SIMERR_ISEXCEPTION
{
   SIMERR_TYPE_ERROR,
   SIMERR_TYPE_EXCEPTION
};

// CErrorInfo defines an error type
struct errorInfo_t
{
   int                 m_nErrorType;  // type of error
   char *              m_pName;       // name of error (for trace output)
   SIMERR_ISEXCEPTION  m_bException;  // whether the error is a C++ exception
};

// This is a parameter to the SimErrInit function.  
enum SIMERR_TEST_TYPE
{
   SIMERR_SYSTEMATIC,    // simulate every error exactly once, even random errors
   SIMERR_RANDOM         // allow random errors 
};

#define SIMERR_FOREVER (-1)

// This is a convenience macro for use with the SimXXX function templates.
#define SIMLINE  __FILE__, __LINE__

// All trace output is sent through a single function.  A pointer to the
// function is passed at initialization.
typedef void (*pfSimErrMessage_t) (const char *pMsg);

// The DLL calls back to the application to throw exceptions.  This allows
// the application to define its own exceptions.
typedef void (*pfThrowException_t) (int nErrorType,
                                    const char *pSourceFilename,
                                    int nSourceLine);

// This structure initializes the error simulation library
struct simerrInit_t
{
   int                     m_nVersion;    // set this to SIMERR_VERSION
   const char *            m_pFilename;   // simulator log file
   int                     m_nSeed;       // random number seed
   SIMERR_TEST_TYPE        m_testType;    // systematic or random test
   pfSimErrMessage_t       m_pfMsg;       // callback for message output
   pfThrowException_t      m_pfThrow;     // callback for throwing exceptions
   const errorInfo_t *     m_pErrInfo;    // info on each error type
   int                     m_nErrTypes;   // number of error types
};
#define SIMERR_VERSION   1           // version of the error testing library
#define SIMERR_TIME_SEED       (-1)        // time-based random number seed

#endif // SIMDEF_H
