ECHO ON
COPY \arp\lib\lbam.dll save
PREP /LV  \arp\lib\lbam.dll
rem COPY \arp\lib\lbam._ll \arp\lib\lbam.dll
PROFILE /I \arp\lib\lbam /O \arp\lib\lbam debug\test.exe %3 %4 %5 %6
COPY save \arp\lib\lbam.dll
PREP /M \arp\lib\lbam
PLIST \arp\lib\lbam >> prof.out
del save



