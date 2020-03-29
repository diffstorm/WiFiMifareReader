@echo off

C:\AStyle\bin\AStyle.exe -j --mode=c --style=allman -xL -n -S -s4 -k3 -W3 -p -U --recursive *.c

C:\AStyle\bin\AStyle.exe -j --mode=c --style=allman -xL -n -S -s4 -k3 -W3 -p -U --recursive *.h

C:\AStyle\bin\AStyle.exe -j --mode=c --style=allman -xL -n -S -s4 -k3 -W3 -p -U --recursive *.cpp

C:\AStyle\bin\AStyle.exe -j --mode=c --style=allman -xL -n -S -s4 -k3 -W3 -p -U --recursive *.hpp

del /s /q /f *.bak