@echo off


::生成静态库

set dir=G:\Source\project_t\project

RD cmake\build\ /s /q
mkdir cmake\build\

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

cd /D %dir%\common\excel_format\cmake\build\

cmake -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=Release ..
nmake
