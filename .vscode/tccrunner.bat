
@setlocal
@echo off

set TCCDIR=%~dp0tcc

set PATH=%TCCDIR%;%PATH%

set CURDIR=%~1
if "x%~1" == "x" call :GET_CUR_DIRNAME %CD%

set ALLCFILES=
for /F "" %%i in ('dir /B *.c') do call :ADD_C_SRCFILE %%i

echo Compile %ALLCFILES%...
tcc -g -o %CURDIR%.exe %ALLCFILES%
if errorlevel 1 exit /B 1

echo Run %CURDIR%.exe , and output ...
echo.

%CURDIR%.exe
if errorlevel 1 exit /B 1


goto END_OF_FILE

:GET_CUR_DIRNAME
set CURDIR=%~n1
exit /b 0

:ADD_C_SRCFILE
set ALLCFILES=%ALLCFILES% %1
exit /b 0

:END_OF_FILE

