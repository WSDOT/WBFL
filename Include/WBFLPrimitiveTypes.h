///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, P.O. Box  47340,
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
#pragma once

// This header is the single source of truth for WBFL's fundamental type aliases.
// It is consumed two ways:
//  - Directly, by plain C++ code (#include <WBFLPrimitiveTypes.h>, e.g. via WBFLTypes.h)
//  - Via MIDL, through "import "WBFLPrimitiveTypes.h";" in WBFLTypes.idl, so ATL/COM
//    libraries can use these types as real, marshalled interface parameter types.
//    WBFLTypes.vcxproj defines MIDL_PASS for its Midl build step only (not for any
//    ClCompile step), so the #if !defined(MIDL_PASS) regions below are visible to a
//    normal C++ compile but hidden from MIDL's own grammar parser, which cannot
//    parse using-declarations, inline function bodies, or a few specific typedefs
//    (see comments below).

#if !defined(MIDL_PASS)
// causes strands to be lumped together at their geometry centroid
// this setting has to be consistent with PGSplice otherwise there will be slight errors
// in the time-step analysis.
// I put this here so that it is in a global, generic location. This is a really bad spot
// but it works.
#define LUMP_STRANDS
#endif


#include <basetsd.h>

#if !defined(MIDL_PASS)

#if _WIN32_WINNT < 0x0600

#define MAXUINT8    ((UINT8)~((UINT8)0))
#define MAXINT8     ((INT8)(MAXUINT8 >> 1))
#define MININT8     ((INT8)~MAXINT8)

#define MAXUINT16   ((UINT16)~((UINT16)0))
#define MAXINT16    ((INT16)(MAXUINT16 >> 1))
#define MININT16    ((INT16)~MAXINT16)

#define MAXUINT32   ((UINT32)~((UINT32)0))
#define MAXINT32    ((INT32)(MAXUINT32 >> 1))
#define MININT32    ((INT32)~MAXINT32)

#define MAXUINT64   ((UINT64)~((UINT64)0))
#define MAXINT64    ((INT64)(MAXUINT64 >> 1))
#define MININT64    ((INT64)~MAXINT64)

#define MAXULONG32  ((ULONG32)~((ULONG32)0))
#define MAXLONG32   ((LONG32)(MAXULONG32 >> 1))
#define MINLONG32   ((LONG32)~MAXLONG32)

#define MAXULONG64  ((ULONG64)~((ULONG64)0))
#define MAXLONG64   ((LONG64)(MAXULONG64 >> 1))
#define MINLONG64   ((LONG64)~MAXLONG64)

#define MAXULONGLONG ((ULONGLONG)~((ULONGLONG)0))
#define MINLONGLONG ((LONGLONG)~MAXLONGLONG)

#define MAXSIZE_T   ((SIZE_T)~((SIZE_T)0))
#define MAXSSIZE_T  ((SSIZE_T)(MAXSIZE_T >> 1))
#define MINSSIZE_T  ((SSIZE_T)~MAXSSIZE_T)

#define MAXUINT     ((UINT)~((UINT)0))
#define MAXINT      ((INT)(MAXUINT >> 1))
#define MININT      ((INT)~MAXINT)

#define MAXDWORD32  ((DWORD32)~((DWORD32)0))
#define MAXDWORD64  ((DWORD64)~((DWORD64)0))

#endif // _WIN32_WINNT < 0x0600

#if defined UNICODE || defined _UNICODE
#define _tstring wstring
#define to_tstring to_wstring
#define _tstringstream wstringstream
#define _tostringstream wostringstream
#define _tistringstream wistringstream
#define _tifstream wifstream
#define _tofstream wofstream
#define _tostream wostream
#define _tistream wistream
#define _tcout wcout
#define _tcin wcin
#else
#define _tstring string
#define to_tstring to_string
#define _tstringstream stringstream
#define _tostringstream ostringstream
#define _tistringstream istringstream
#define _tifstream ifstream
#define _tofstream ofstream
#define _tostream ostream
#define _tistream istream
#define _tcout cout
#define _tcin cin
#endif

#include <limits.h>
#include <float.h>

typedef        INT8    Int8; // MIDL makes this an unsigned char
typedef long double Float80; // long double isn't an MIDL type

#define Int8_Max      SCHAR_MAX
#define Int8_Min      SCHAR_MIN
#define Int16_Max     SHRT_MAX
#define Int16_Min     SHRT_MIN
#define Int32_Max     LONG_MAX
#define Int32_Min     LONG_MIN
#define Int64_Max     LLONG_MAX
#define Int64_Min     LLONG_MIN
#define Uint8_Max     UCHAR_MAX
#define Uint16_Max    USHRT_MAX
#define Uint32_Max    ULONG_MAX
#define Uint64_Max    ULLONG_MAX
#define Float32_Max   FLT_MAX
#define Float32_Min   FLT_MIN
#define Float32_Inf   std::numeric_limits<Float32>::infinity()
#define Float64_Max   DBL_MAX
#define Float64_Inf   std::numeric_limits<Float64>::infinity()
#define Float64_Min   DBL_MIN
#define Float80_Max   LDBL_MAX
#define Float80_Min   LDBL_MIN

#endif // !defined(MIDL_PASS)

typedef INT16 Int16;
typedef INT32 Int32;

typedef UINT8 Uint8;
typedef UINT16 Uint16;
typedef UINT32 Uint32;

typedef INT64 Int64;
typedef UINT64 Uint64;

typedef float  Float32;
typedef double Float64;

#if defined VBA_BUILD
typedef INT16 IDType;
#if !defined(MIDL_PASS)
#pragma warning(disable:4018 4244 4267)
#define INVALID_ID -1
#define MAX_ID MAXINT16
#define VARIANT2ID(_var_) _var_.intVal
#define VT_ID VT_INT
#endif
#else
#if defined _WIN64
typedef INT64   IDType;
#if !defined(MIDL_PASS)
#define INVALID_ID -1
#define MAX_ID MAXINT64
#define VARIANT2ID(_var_) _var_.llVal
#define VT_ID VT_I8
#endif
#else
typedef INT32   IDType;
#if !defined(MIDL_PASS)
#define INVALID_ID -1
#define MAX_ID MAXINT32
#define VARIANT2ID(_var_) _var_.lVal
#define VT_ID VT_I4
#endif
#endif
#endif

typedef IDType  SpanIDType;
typedef IDType  PierIDType;
typedef IDType  JointIDType;
typedef IDType  MemberIDType;
typedef IDType  SupportIDType;
typedef IDType  LoadIDType;
typedef IDType  PoiIDType;
typedef IDType  LoadCaseIDType;
typedef IDType  LoadGroupIDType;
typedef IDType  LoadCombinationIDType;
typedef IDType  GirderIDType;
typedef IDType  GroupIDType;
typedef IDType  SegmentIDType;
typedef IDType  ClosureIDType;
typedef IDType  StageIDType;
typedef IDType  EventIDType;

typedef Int32 BarSizeType;



// VBA does not support UINT32 or UINT64 so we need to use LONG as the IndexType for VBA builds
#if defined VBA_BUILD
typedef long IndexType;
#if !defined(MIDL_PASS)
#define MAX_INDEX (MAX_LONG-1)
#define INVALID_INDEX    -1
#define VARIANT2INDEX(_var_) _var_.lVal
#define VT_INDEX VT_I4
#endif
#else
#if defined _WIN64
typedef UINT64 IndexType;
#if !defined(MIDL_PASS)
#define MAX_INDEX (MAXUINT64-1)
#define INVALID_INDEX (MAX_INDEX+1)
#define VARIANT2INDEX(_var_) _var_.ullVal
#define VT_INDEX VT_UI8
#endif
#else
typedef UINT32 IndexType;
#if !defined(MIDL_PASS)
#define MAX_INDEX (MAXUINT32-1)
#define INVALID_INDEX (MAX_INDEX+1)
#define VARIANT2INDEX(_var_) _var_.ulVal
#define VT_INDEX VT_UI4
#endif
#endif
#endif

#if !defined(MIDL_PASS)
#define FIXED_AXLE_TRUCK INVALID_INDEX
#define ALL_SPANS        INVALID_INDEX
#define ALL_PIERS        INVALID_INDEX
#define ALL_GIRDERS      INVALID_INDEX
#define ALL_BEARINGS      INVALID_INDEX
#define ALL_GROUPS       INVALID_INDEX
#define ALL_SEGMENTS     INVALID_INDEX
#define ALL_STAGES       INVALID_INDEX
#define ALL_DUCTS        INVALID_INDEX
#define INVALID_BAR_SIZE INVALID_INDEX
#endif

typedef IndexType StageIndexType;
typedef IndexType EventIndexType;
typedef IndexType SupportIndexType;
typedef IndexType StrandIndexType;
typedef IndexType SpanIndexType;
typedef IndexType GirderIndexType;
typedef IndexType BearingIndexType;
typedef IndexType PierPointIndexType;
typedef IndexType PierIndexType;
typedef IndexType ColumnIndexType;
typedef IndexType GroupIndexType;
typedef IndexType SpacingIndexType;
typedef IndexType VehicleIndexType;
typedef IndexType AxleIndexType;
typedef IndexType GridIndexType;
typedef IndexType SectionIndexType;
typedef IndexType RowIndexType;
typedef IndexType SegmentIndexType;
typedef IndexType MatingSurfaceIndexType;
typedef IndexType WebIndexType;
typedef IndexType FlangeIndexType;
typedef IndexType SplittingPlaneIndexType;
typedef IndexType ZoneIndexType;
typedef IndexType DuctIndexType;
typedef IndexType IntervalIndexType;

#if !defined(MIDL_PASS)

using SpanGirderHashType = Int64;
using PierGirderHashType = Int64;

inline Uint16 make_Uint16(Uint8  lo, Uint8  hi) {return (Uint16)(lo & 0xFF)  | (Uint16)(hi & 0xFF) << 8;}
inline Int16  make_Int16 (Int8   lo, Int8   hi) {return (Int16)(lo  & 0xFF) | (Int16) (hi & 0xFF)  << 8;}
inline Uint32 make_Uint32(Uint16 lo, Uint16 hi) {return (Uint32)(lo & 0xFFFF) | (Uint32)(hi & 0xFFFF) << 16;}
inline Int32  make_Int32 (Int16  lo, Int16  hi) {return (Int32)( lo & 0xFFFF) | (Int32)( hi & 0xFFFF) << 16;}

inline Uint16 low_Uint16(Uint32 u32) {return u32 & 0xFF;}
inline Int16  low_Int16(Int32 u32)   {return u32 & 0xFF;}

inline Uint16 high_Uint16(Uint32 u32) {  return u32 >> 16;}
inline Int16  high_Int16(Uint32 u32)  {  return u32 >> 16;}

inline Uint8 low_Uint8(Uint16 u16){ return u16 & 0xFF;}
inline Int8  low_Int8(Uint16 u16) { return u16 & 0xFF;}

inline Uint8 high_Uint8(Uint16 u16) { return u16 >> 8;}
inline Int8  high_Int8(Uint16 u16)  { return u16 >> 8;}

inline Uint64 make_Uint64(Uint32  lo, Uint32  hi) {return (Uint64)(lo &  0xFFFFFFFF) | (Uint64)( hi &  0xFFFFFFFF) << 32;}
inline Uint32 low_Uint32(Uint64 u64) {return u64 & 0xFFFFFFFF;}
inline Uint32 high_Uint32(Uint64 u64) {return u64 >> 32;}

inline Int64 make_Int64 (Int32  lo, Int32  hi) {return (Int64)(lo &  0xFFFFFFFF) | (Int64)( hi &  0xFFFFFFFF) << 32;}
inline Int32 low_Int32(Int64 u64) {return u64 & 0xFFFFFFFF;}
inline Int32 high_Int32(Int64 u64) {return u64 >> 32;}

inline SpanGirderHashType HashSpanGirder(SpanIndexType span,GirderIndexType girder) { return make_Int64((Int32)span,(Int32)girder); }
inline void UnhashSpanGirder(SpanGirderHashType hash,SpanIndexType* span,GirderIndexType* girder) { *span =  low_Int32(hash); *girder = high_Int32(hash); }
inline PierGirderHashType HashPierGirder(PierIndexType pier,GirderIndexType girder) { return make_Int64((Int32)pier,(Int32)girder); }
inline void UnhashPierGirder(PierGirderHashType hash,PierIndexType* pier,GirderIndexType* girder) { *pier =  low_Int32(hash); *girder = high_Int32(hash); }

#endif // !defined(MIDL_PASS)
