#include <System\SysLib.h>
#include <System\Dispatcher.h>

//
// Passes param2 as an int and returns int32
//
Int32 I32_I32_Dispatch(GENERIC& generic,
                       Int32  (GENERIC::*pmf)(Int16),
                       Uint16,
                       Int32    param2)
{
   return (generic.*pmf)((Int16)param2);
}

//
// Passes wParam as an uint and lParam as an int32 and returns int32
//
Int32 I32_U_I32_Dispatch(GENERIC& generic,
                         Int32 (GENERIC::*pmf)(Uint16,Int32),
                         Uint16 param1,
                         Int32 param2)
{
   return (generic.*pmf)(param1,param2);
}

//
// Passes lParam as const char* and returns int32
//
Int32 I32_CS_Dispatch(GENERIC& generic,
                      Int32 (GENERIC::*pmf)(const char*),
                      Uint16 wParam,
                      Int32 lParam )
{
   return (generic.*pmf)( (const char*)(lParam) );   
}

//
// Passes lParam as char* and returns int32
//
Int32 I32_Str_Dispatch(GENERIC& generic,
                       Int32 (GENERIC::*pmf)(char*),
                       Uint16 wParam,
                       Int32 lParam )
{
   return (generic.*pmf)( (char*)(lParam) );   
}
