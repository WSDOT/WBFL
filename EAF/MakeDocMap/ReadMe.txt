========================================================================
    CONSOLE APPLICATION : MakeDocMap Project Overview
========================================================================
This is a utility program to make a documenation map file for the BridgeLink documenation system.

This utility reads the .HH and .ALI files and creates a .DM file

.HH files have the help topic IDs as
#define IDH_MY_HELP_TOPIC  200

.ALI files map the #define name to a help topic
IDC_MY_HELP_TOPIC=\subfolder\mytopic.html

The DM file (documentation map) is loaded at runtime by BridgeLink applications and maps a topic id to a topic
200=\subfolder\mytopic.html

To use this application, make the folder where the HH and ALI files are located the current directory. Run the application with the documentation set name as the only argument.
MakeDocMap.exe PGSuper


The application will look for PGSuper.hh and PGSuper.ali in the current folder and will create PGSuper.dm. Publish the documentation map file along with the documentation.