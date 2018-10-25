
Sectionsps.dll: dlldata.obj Sections_p.obj Sections_i.obj
	link /dll /out:Sectionsps.dll /def:Sectionsps.def /entry:DllMain dlldata.obj Sections_p.obj Sections_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Sectionsps.dll
	@del Sectionsps.lib
	@del Sectionsps.exp
	@del dlldata.obj
	@del Sections_p.obj
	@del Sections_i.obj
