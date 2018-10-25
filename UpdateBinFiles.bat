REM - Script to copy the various binary files to the "bin" folder
REM - Run this script just prior to tagging the repository with ready-x-y-z-b

REM - Binary Files for basic development

set BINTARGET=bin

COPY "RegFreeCOM\Release\WBFL*.dll"	"%BINTARGET%\Libraries\"
COPY "RegFreeCOM\Release\WBFL*.lib"	"%BINTARGET%\Lib\"

COPY License.rtf 			"%BINTARGET%"

REM - Help files and documentation

COPY RegFreeCOM\*.chm			"%BINTARGET%\App\"
COPY License.txt			"%BINTARGET%\App\"
