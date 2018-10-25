
RCCapacityps.dll: dlldata.obj RCCapacity_p.obj RCCapacity_i.obj
	link /dll /out:RCCapacityps.dll /def:RCCapacityps.def /entry:DllMain dlldata.obj RCCapacity_p.obj RCCapacity_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del RCCapacityps.dll
	@del RCCapacityps.lib
	@del RCCapacityps.exp
	@del dlldata.obj
	@del RCCapacity_p.obj
	@del RCCapacity_i.obj
