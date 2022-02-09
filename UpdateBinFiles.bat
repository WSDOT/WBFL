REM - Script to xcopy /y /d  the various binary files to the "bin" folder
REM - Run this script just prior to tagging the repository with ready-x-y-z-b

REM - Binary Files for basic development

set BINTARGET=bin

xcopy /y /d  "RegFreeCOM\x64\Release\WBFL*.dll"	"%BINTARGET%\Libraries\x64\"
xcopy /y /d  "RegFreeCOM\x64\Release\WBFL*.lib"	"%BINTARGET%\Lib\x64\"


xcopy /y /d  License.rtf 			"%BINTARGET%"

REM - Other important files
xcopy /y /d  License.txt			"%BINTARGET%\App\"
