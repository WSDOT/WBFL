# C++ 20 Port {#WBFL_CPP20}

An effort has been made to port all of the WBFL and BridgeLink projects to C++ 20 as part of the modernization effort. This has generally been successful, however there are a few DLLs that are stuck back in C++ 14.

The biggest issue is the Code Synthesis tool. This tool reads XSD schema files and generates C++ code. The generated code is not compliant with C++ after version 14. Specifically, the std::auto_ptr class has been removed in C++ 17. Code Synthesis claims version 4.0 is compliant however, there is a bug in the generated header files and they don't offer a solution other than grabbing the latest build from their git site (which is not GitHub).

The following WBFL DLLs are stuck at C++ 14:

| Project | Compiler Setting |
|---------|-------|
| WBFLUnitServer | C++ 14 with Default conformance mode |
| UnitServerTest | C++ 14 with conformance mode |

Though not strictly part of WBFL, the following BridgeLink applications and application plugins DLLs are stuck at C++ 14:

| Project | Compiler Setting |
|---------|-------|
| Barlist | C++ 14 with Default conformance mode |
| BEToolbox | C++ 14 with conformance mode |
| BEToolboxXML | C++ 14 with Default conformance mode |
| KDOTExport | C++ 14 with Default conformance mode |


`Default conformance mode` is nonconformance with C++ language standard.

`With conformance mode` is the /permissive- compiler option which requires the code to conform to the C++ language standard. This option is slightly better than `Default conformance mode` because there is conformance with the language standard, albeit an older standard.

The compiler setting we want to achieve for C++ 20 is (found in Project Properties, C/C++ -> Language):
* C++ Language Standard : ISO C++ 20 Standard (/std:c++20)
* Conformance mode : Yes (/permissive-)


