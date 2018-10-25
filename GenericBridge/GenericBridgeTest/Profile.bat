ECHO ON
COPY %1.dll save
PREP /OM /LV /EXCALL /INC TransversePierDescription.cpp(0-0) %1.dll
rem PREP /OM /LV %1.dll
COPY %1._ll %1.dll
PROFILE /I %1 /O %1 %2 %3 %4 %5 %6 > test.out
COPY save %1.dll
DEL save
PREP /M %1
PLIST %1 > Profile.out

