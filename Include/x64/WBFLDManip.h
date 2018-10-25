

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:37:38 2017
 */
/* Compiler settings for ..\Include\WBFLDManip.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __WBFLDManip_h__
#define __WBFLDManip_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __DisplayList_FWD_DEFINED__
#define __DisplayList_FWD_DEFINED__

#ifdef __cplusplus
typedef class DisplayList DisplayList;
#else
typedef struct DisplayList DisplayList;
#endif /* __cplusplus */

#endif 	/* __DisplayList_FWD_DEFINED__ */


#ifndef __DisplayMgr_FWD_DEFINED__
#define __DisplayMgr_FWD_DEFINED__

#ifdef __cplusplus
typedef class DisplayMgr DisplayMgr;
#else
typedef struct DisplayMgr DisplayMgr;
#endif /* __cplusplus */

#endif 	/* __DisplayMgr_FWD_DEFINED__ */


#ifndef __InplaceEditTask_FWD_DEFINED__
#define __InplaceEditTask_FWD_DEFINED__

#ifdef __cplusplus
typedef class InplaceEditTask InplaceEditTask;
#else
typedef struct InplaceEditTask InplaceEditTask;
#endif /* __cplusplus */

#endif 	/* __InplaceEditTask_FWD_DEFINED__ */


#ifndef __RectSelectTask_FWD_DEFINED__
#define __RectSelectTask_FWD_DEFINED__

#ifdef __cplusplus
typedef class RectSelectTask RectSelectTask;
#else
typedef struct RectSelectTask RectSelectTask;
#endif /* __cplusplus */

#endif 	/* __RectSelectTask_FWD_DEFINED__ */


#ifndef __LocalDragDropTask_FWD_DEFINED__
#define __LocalDragDropTask_FWD_DEFINED__

#ifdef __cplusplus
typedef class LocalDragDropTask LocalDragDropTask;
#else
typedef struct LocalDragDropTask LocalDragDropTask;
#endif /* __cplusplus */

#endif 	/* __LocalDragDropTask_FWD_DEFINED__ */


#ifndef __ForeignDragDropTask_FWD_DEFINED__
#define __ForeignDragDropTask_FWD_DEFINED__

#ifdef __cplusplus
typedef class ForeignDragDropTask ForeignDragDropTask;
#else
typedef struct ForeignDragDropTask ForeignDragDropTask;
#endif /* __cplusplus */

#endif 	/* __ForeignDragDropTask_FWD_DEFINED__ */


#ifndef __DragDataSource_FWD_DEFINED__
#define __DragDataSource_FWD_DEFINED__

#ifdef __cplusplus
typedef class DragDataSource DragDataSource;
#else
typedef struct DragDataSource DragDataSource;
#endif /* __cplusplus */

#endif 	/* __DragDataSource_FWD_DEFINED__ */


#ifndef __DragDataSink_FWD_DEFINED__
#define __DragDataSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class DragDataSink DragDataSink;
#else
typedef struct DragDataSink DragDataSink;
#endif /* __cplusplus */

#endif 	/* __DragDataSink_FWD_DEFINED__ */


#ifndef __CenterOnPointTask_FWD_DEFINED__
#define __CenterOnPointTask_FWD_DEFINED__

#ifdef __cplusplus
typedef class CenterOnPointTask CenterOnPointTask;
#else
typedef struct CenterOnPointTask CenterOnPointTask;
#endif /* __cplusplus */

#endif 	/* __CenterOnPointTask_FWD_DEFINED__ */


#ifndef __ZoomRectTask_FWD_DEFINED__
#define __ZoomRectTask_FWD_DEFINED__

#ifdef __cplusplus
typedef class ZoomRectTask ZoomRectTask;
#else
typedef struct ZoomRectTask ZoomRectTask;
#endif /* __cplusplus */

#endif 	/* __ZoomRectTask_FWD_DEFINED__ */


#ifndef __TaskFactory_FWD_DEFINED__
#define __TaskFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class TaskFactory TaskFactory;
#else
typedef struct TaskFactory TaskFactory;
#endif /* __cplusplus */

#endif 	/* __TaskFactory_FWD_DEFINED__ */


#ifndef __DisplayObjectFactory_FWD_DEFINED__
#define __DisplayObjectFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class DisplayObjectFactory DisplayObjectFactory;
#else
typedef struct DisplayObjectFactory DisplayObjectFactory;
#endif /* __cplusplus */

#endif 	/* __DisplayObjectFactory_FWD_DEFINED__ */


#ifndef __Mapping_FWD_DEFINED__
#define __Mapping_FWD_DEFINED__

#ifdef __cplusplus
typedef class Mapping Mapping;
#else
typedef struct Mapping Mapping;
#endif /* __cplusplus */

#endif 	/* __Mapping_FWD_DEFINED__ */


#ifndef __Plug_FWD_DEFINED__
#define __Plug_FWD_DEFINED__

#ifdef __cplusplus
typedef class Plug Plug;
#else
typedef struct Plug Plug;
#endif /* __cplusplus */

#endif 	/* __Plug_FWD_DEFINED__ */


#ifndef __Socket_FWD_DEFINED__
#define __Socket_FWD_DEFINED__

#ifdef __cplusplus
typedef class Socket Socket;
#else
typedef struct Socket Socket;
#endif /* __cplusplus */

#endif 	/* __Socket_FWD_DEFINED__ */


#ifndef __SocketFactory_FWD_DEFINED__
#define __SocketFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class SocketFactory SocketFactory;
#else
typedef struct SocketFactory SocketFactory;
#endif /* __cplusplus */

#endif 	/* __SocketFactory_FWD_DEFINED__ */


#ifndef __PointDisplayObject_FWD_DEFINED__
#define __PointDisplayObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointDisplayObject PointDisplayObject;
#else
typedef struct PointDisplayObject PointDisplayObject;
#endif /* __cplusplus */

#endif 	/* __PointDisplayObject_FWD_DEFINED__ */


#ifndef __SimpleDrawPointStrategy_FWD_DEFINED__
#define __SimpleDrawPointStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleDrawPointStrategy SimpleDrawPointStrategy;
#else
typedef struct SimpleDrawPointStrategy SimpleDrawPointStrategy;
#endif /* __cplusplus */

#endif 	/* __SimpleDrawPointStrategy_FWD_DEFINED__ */


#ifndef __TextBlock_FWD_DEFINED__
#define __TextBlock_FWD_DEFINED__

#ifdef __cplusplus
typedef class TextBlock TextBlock;
#else
typedef struct TextBlock TextBlock;
#endif /* __cplusplus */

#endif 	/* __TextBlock_FWD_DEFINED__ */


#ifndef __EditableTextBlock_FWD_DEFINED__
#define __EditableTextBlock_FWD_DEFINED__

#ifdef __cplusplus
typedef class EditableTextBlock EditableTextBlock;
#else
typedef struct EditableTextBlock EditableTextBlock;
#endif /* __cplusplus */

#endif 	/* __EditableTextBlock_FWD_DEFINED__ */


#ifndef __EditableUnitValueTextBlock_FWD_DEFINED__
#define __EditableUnitValueTextBlock_FWD_DEFINED__

#ifdef __cplusplus
typedef class EditableUnitValueTextBlock EditableUnitValueTextBlock;
#else
typedef struct EditableUnitValueTextBlock EditableUnitValueTextBlock;
#endif /* __cplusplus */

#endif 	/* __EditableUnitValueTextBlock_FWD_DEFINED__ */


#ifndef __LineDisplayObject_FWD_DEFINED__
#define __LineDisplayObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class LineDisplayObject LineDisplayObject;
#else
typedef struct LineDisplayObject LineDisplayObject;
#endif /* __cplusplus */

#endif 	/* __LineDisplayObject_FWD_DEFINED__ */


#ifndef __DimensionLineDisplayObject_FWD_DEFINED__
#define __DimensionLineDisplayObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class DimensionLineDisplayObject DimensionLineDisplayObject;
#else
typedef struct DimensionLineDisplayObject DimensionLineDisplayObject;
#endif /* __cplusplus */

#endif 	/* __DimensionLineDisplayObject_FWD_DEFINED__ */


#ifndef __Tool_FWD_DEFINED__
#define __Tool_FWD_DEFINED__

#ifdef __cplusplus
typedef class Tool Tool;
#else
typedef struct Tool Tool;
#endif /* __cplusplus */

#endif 	/* __Tool_FWD_DEFINED__ */


#ifndef __CompositeDisplayObject_FWD_DEFINED__
#define __CompositeDisplayObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompositeDisplayObject CompositeDisplayObject;
#else
typedef struct CompositeDisplayObject CompositeDisplayObject;
#endif /* __cplusplus */

#endif 	/* __CompositeDisplayObject_FWD_DEFINED__ */


#ifndef __SimpleDrawLineStrategy_FWD_DEFINED__
#define __SimpleDrawLineStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleDrawLineStrategy SimpleDrawLineStrategy;
#else
typedef struct SimpleDrawLineStrategy SimpleDrawLineStrategy;
#endif /* __cplusplus */

#endif 	/* __SimpleDrawLineStrategy_FWD_DEFINED__ */


#ifndef __SimpleDrawDashedLineStrategy_FWD_DEFINED__
#define __SimpleDrawDashedLineStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleDrawDashedLineStrategy SimpleDrawDashedLineStrategy;
#else
typedef struct SimpleDrawDashedLineStrategy SimpleDrawDashedLineStrategy;
#endif /* __cplusplus */

#endif 	/* __SimpleDrawDashedLineStrategy_FWD_DEFINED__ */


#ifndef __RectangleDrawLineStrategy_FWD_DEFINED__
#define __RectangleDrawLineStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class RectangleDrawLineStrategy RectangleDrawLineStrategy;
#else
typedef struct RectangleDrawLineStrategy RectangleDrawLineStrategy;
#endif /* __cplusplus */

#endif 	/* __RectangleDrawLineStrategy_FWD_DEFINED__ */


#ifndef __ShapeDrawStrategy_FWD_DEFINED__
#define __ShapeDrawStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShapeDrawStrategy ShapeDrawStrategy;
#else
typedef struct ShapeDrawStrategy ShapeDrawStrategy;
#endif /* __cplusplus */

#endif 	/* __ShapeDrawStrategy_FWD_DEFINED__ */


#ifndef __TargetDrawStrategy_FWD_DEFINED__
#define __TargetDrawStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class TargetDrawStrategy TargetDrawStrategy;
#else
typedef struct TargetDrawStrategy TargetDrawStrategy;
#endif /* __cplusplus */

#endif 	/* __TargetDrawStrategy_FWD_DEFINED__ */


#ifndef __CompoundDrawLineStrategy_FWD_DEFINED__
#define __CompoundDrawLineStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompoundDrawLineStrategy CompoundDrawLineStrategy;
#else
typedef struct CompoundDrawLineStrategy CompoundDrawLineStrategy;
#endif /* __cplusplus */

#endif 	/* __CompoundDrawLineStrategy_FWD_DEFINED__ */


#ifndef __ExtRectangleDrawLineStrategy_FWD_DEFINED__
#define __ExtRectangleDrawLineStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExtRectangleDrawLineStrategy ExtRectangleDrawLineStrategy;
#else
typedef struct ExtRectangleDrawLineStrategy ExtRectangleDrawLineStrategy;
#endif /* __cplusplus */

#endif 	/* __ExtRectangleDrawLineStrategy_FWD_DEFINED__ */


#ifndef __ViewTitle_FWD_DEFINED__
#define __ViewTitle_FWD_DEFINED__

#ifdef __cplusplus
typedef class ViewTitle ViewTitle;
#else
typedef struct ViewTitle ViewTitle;
#endif /* __cplusplus */

#endif 	/* __ViewTitle_FWD_DEFINED__ */


#ifndef __NorthArrow_FWD_DEFINED__
#define __NorthArrow_FWD_DEFINED__

#ifdef __cplusplus
typedef class NorthArrow NorthArrow;
#else
typedef struct NorthArrow NorthArrow;
#endif /* __cplusplus */

#endif 	/* __NorthArrow_FWD_DEFINED__ */


#ifndef __ShapeGravityWellStrategy_FWD_DEFINED__
#define __ShapeGravityWellStrategy_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShapeGravityWellStrategy ShapeGravityWellStrategy;
#else
typedef struct ShapeGravityWellStrategy ShapeGravityWellStrategy;
#endif /* __cplusplus */

#endif 	/* __ShapeGravityWellStrategy_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WBFLDManip_LIBRARY_DEFINED__
#define __WBFLDManip_LIBRARY_DEFINED__

/* library WBFLDManip */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_WBFLDManip,0x011408A7,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

DEFINE_GUID(CLSID_DisplayList,0xA2703706,0xF85B,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("A2703706-F85B-11d4-8B9C-006097C68A9C")
DisplayList;
#endif

DEFINE_GUID(CLSID_DisplayMgr,0x011408A6,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408A6-F865-11d4-8B9C-006097C68A9C")
DisplayMgr;
#endif

DEFINE_GUID(CLSID_InplaceEditTask,0x011408C4,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408C4-F865-11d4-8B9C-006097C68A9C")
InplaceEditTask;
#endif

DEFINE_GUID(CLSID_RectSelectTask,0x011408C5,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408C5-F865-11d4-8B9C-006097C68A9C")
RectSelectTask;
#endif

DEFINE_GUID(CLSID_LocalDragDropTask,0x011408C6,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408C6-F865-11d4-8B9C-006097C68A9C")
LocalDragDropTask;
#endif

DEFINE_GUID(CLSID_ForeignDragDropTask,0x011408CB,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408CB-F865-11d4-8B9C-006097C68A9C")
ForeignDragDropTask;
#endif

DEFINE_GUID(CLSID_DragDataSource,0x011408C7,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408C7-F865-11d4-8B9C-006097C68A9C")
DragDataSource;
#endif

DEFINE_GUID(CLSID_DragDataSink,0x011408C8,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408C8-F865-11d4-8B9C-006097C68A9C")
DragDataSink;
#endif

DEFINE_GUID(CLSID_CenterOnPointTask,0x011408CC,0xF865,0x11D4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408CC-F865-11D4-8B9C-006097C68A9C")
CenterOnPointTask;
#endif

DEFINE_GUID(CLSID_ZoomRectTask,0x011408CD,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408CD-F865-11d4-8B9C-006097C68A9C")
ZoomRectTask;
#endif

DEFINE_GUID(CLSID_TaskFactory,0x011408CE,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408CE-F865-11d4-8B9C-006097C68A9C")
TaskFactory;
#endif

DEFINE_GUID(CLSID_DisplayObjectFactory,0x011408CF,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408CF-F865-11d4-8B9C-006097C68A9C")
DisplayObjectFactory;
#endif

DEFINE_GUID(CLSID_Mapping,0x011408D0,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408D0-F865-11d4-8B9C-006097C68A9C")
Mapping;
#endif

DEFINE_GUID(CLSID_Plug,0x011408D1,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408D1-F865-11d4-8B9C-006097C68A9C")
Plug;
#endif

DEFINE_GUID(CLSID_Socket,0x011408D2,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408D2-F865-11d4-8B9C-006097C68A9C")
Socket;
#endif

DEFINE_GUID(CLSID_SocketFactory,0x011408D3,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408D3-F865-11d4-8B9C-006097C68A9C")
SocketFactory;
#endif

DEFINE_GUID(CLSID_PointDisplayObject,0x011408D4,0xF865,0x11d4,0x8B,0x9C,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#ifdef __cplusplus

class DECLSPEC_UUID("011408D4-F865-11d4-8B9C-006097C68A9C")
PointDisplayObject;
#endif

DEFINE_GUID(CLSID_SimpleDrawPointStrategy,0x38D4D890,0xDF6E,0x404c,0x93,0x74,0xE9,0x37,0x5B,0xDE,0x0D,0xF0);

#ifdef __cplusplus

class DECLSPEC_UUID("38D4D890-DF6E-404c-9374-E9375BDE0DF0")
SimpleDrawPointStrategy;
#endif

DEFINE_GUID(CLSID_TextBlock,0x8EB55FED,0x8056,0x4d6b,0x9F,0x89,0x09,0xFC,0x59,0xC8,0x46,0x18);

#ifdef __cplusplus

class DECLSPEC_UUID("8EB55FED-8056-4d6b-9F89-09FC59C84618")
TextBlock;
#endif

DEFINE_GUID(CLSID_EditableTextBlock,0xD66088C8,0x7E4A,0x49d7,0xA3,0x06,0x28,0xBF,0x10,0xB5,0x3A,0x88);

#ifdef __cplusplus

class DECLSPEC_UUID("D66088C8-7E4A-49d7-A306-28BF10B53A88")
EditableTextBlock;
#endif

DEFINE_GUID(CLSID_EditableUnitValueTextBlock,0xC24E4B67,0xAAC1,0x4da4,0xA3,0xF2,0x37,0x3C,0x55,0x83,0x33,0xD6);

#ifdef __cplusplus

class DECLSPEC_UUID("C24E4B67-AAC1-4da4-A3F2-373C558333D6")
EditableUnitValueTextBlock;
#endif

DEFINE_GUID(CLSID_LineDisplayObject,0x531F5C30,0xFFC3,0x4a22,0xAD,0xE5,0xD6,0x40,0xC8,0xCB,0xE2,0x84);

#ifdef __cplusplus

class DECLSPEC_UUID("531F5C30-FFC3-4a22-ADE5-D640C8CBE284")
LineDisplayObject;
#endif

DEFINE_GUID(CLSID_DimensionLineDisplayObject,0x9B7A1DE8,0xC7DB,0x4512,0xA9,0x4F,0xD6,0xFF,0x62,0x50,0x5B,0x12);

#ifdef __cplusplus

class DECLSPEC_UUID("9B7A1DE8-C7DB-4512-A94F-D6FF62505B12")
DimensionLineDisplayObject;
#endif

DEFINE_GUID(CLSID_Tool,0x44D1610A,0xA8FF,0x41b0,0xB9,0x4F,0x24,0xB0,0xA5,0x9C,0x62,0x9A);

#ifdef __cplusplus

class DECLSPEC_UUID("44D1610A-A8FF-41b0-B94F-24B0A59C629A")
Tool;
#endif

DEFINE_GUID(CLSID_CompositeDisplayObject,0xA1C5BEE7,0x6799,0x462b,0xB7,0x2A,0xF4,0xBD,0x47,0xE9,0x43,0x41);

#ifdef __cplusplus

class DECLSPEC_UUID("A1C5BEE7-6799-462b-B72A-F4BD47E94341")
CompositeDisplayObject;
#endif

DEFINE_GUID(CLSID_SimpleDrawLineStrategy,0x2F67AF5C,0x6D47,0x4dea,0x9D,0x1F,0xD6,0xF3,0x96,0xE6,0x83,0x1C);

#ifdef __cplusplus

class DECLSPEC_UUID("2F67AF5C-6D47-4dea-9D1F-D6F396E6831C")
SimpleDrawLineStrategy;
#endif

DEFINE_GUID(CLSID_SimpleDrawDashedLineStrategy,0x1E2884E3,0x105B,0x4618,0xB2,0x85,0x90,0xE4,0x4F,0x92,0xE0,0xA0);

#ifdef __cplusplus

class DECLSPEC_UUID("1E2884E3-105B-4618-B285-90E44F92E0A0")
SimpleDrawDashedLineStrategy;
#endif

DEFINE_GUID(CLSID_RectangleDrawLineStrategy,0x682DF075,0x020C,0x45b1,0xBB,0xF4,0x11,0xC1,0x59,0x64,0x4B,0xA5);

#ifdef __cplusplus

class DECLSPEC_UUID("682DF075-020C-45b1-BBF4-11C159644BA5")
RectangleDrawLineStrategy;
#endif

DEFINE_GUID(CLSID_ShapeDrawStrategy,0x4D0A0066,0xE3FE,0x41a7,0x8A,0xE7,0x8E,0x8A,0x77,0x85,0x1E,0xA8);

#ifdef __cplusplus

class DECLSPEC_UUID("4D0A0066-E3FE-41a7-8AE7-8E8A77851EA8")
ShapeDrawStrategy;
#endif

DEFINE_GUID(CLSID_TargetDrawStrategy,0xE9E341BF,0xF158,0x46ae,0x8D,0xB2,0x3E,0x70,0x9E,0x02,0xAD,0x8A);

#ifdef __cplusplus

class DECLSPEC_UUID("E9E341BF-F158-46ae-8DB2-3E709E02AD8A")
TargetDrawStrategy;
#endif

DEFINE_GUID(CLSID_CompoundDrawLineStrategy,0x326E7437,0xFC61,0x41ed,0xAA,0x42,0x6E,0xF8,0xCE,0x25,0x83,0xFF);

#ifdef __cplusplus

class DECLSPEC_UUID("326E7437-FC61-41ed-AA42-6EF8CE2583FF")
CompoundDrawLineStrategy;
#endif

DEFINE_GUID(CLSID_ExtRectangleDrawLineStrategy,0x383B8C08,0xA236,0x44c7,0xBE,0xE1,0xE4,0x1A,0xDD,0x83,0x1A,0xC7);

#ifdef __cplusplus

class DECLSPEC_UUID("383B8C08-A236-44c7-BEE1-E41ADD831AC7")
ExtRectangleDrawLineStrategy;
#endif

DEFINE_GUID(CLSID_ViewTitle,0x6DBAF4E1,0x4291,0x4112,0x96,0x87,0x9C,0x8F,0x9E,0x04,0x25,0xB4);

#ifdef __cplusplus

class DECLSPEC_UUID("6DBAF4E1-4291-4112-9687-9C8F9E0425B4")
ViewTitle;
#endif

DEFINE_GUID(CLSID_NorthArrow,0xDC3F42E8,0x7A6A,0x48be,0x8E,0x0C,0x5D,0x86,0xE9,0xD5,0xEE,0xBE);

#ifdef __cplusplus

class DECLSPEC_UUID("DC3F42E8-7A6A-48be-8E0C-5D86E9D5EEBE")
NorthArrow;
#endif

DEFINE_GUID(CLSID_ShapeGravityWellStrategy,0x4F2C8970,0x5720,0x437b,0xB6,0xCA,0xEA,0x90,0x92,0x31,0x12,0x44);

#ifdef __cplusplus

class DECLSPEC_UUID("4F2C8970-5720-437b-B6CA-EA9092311244")
ShapeGravityWellStrategy;
#endif
#endif /* __WBFLDManip_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


