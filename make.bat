@echo off
setlocal

set SOURCES=src\D3DRefactor\main.cpp
set INCLUDES=/I"%DXSDK_DIR%Include\" /I\include /I\src
set OPTIONS=/Zi /Fdobj\game.pdb /Feout\game.exe
set LINK=user32.lib d3d11.lib d3dx11.lib D3DCompiler.lib dxerr.lib dxgi.lib dxguid.lib
set OUTPUT=out\game
set CXX=cl.exe
set LINKEROPTIONS=

set SHOULDBUILD=F
if not exist %OUTPUT%.exe set SHOULDBUILD=T
if "%1" == "" set SHOULDBUILD=T
if "%SHOULDBUILD%" == "T" (
   echo. 
   echo ========= COMMAND =========
   echo %CXX% %OPTIONS% %SOURCES% %INCLUDES% %LINK% %LINKEROPTIONS%
   echo =========== END ===========
   echo.

   md out
   md obj
   %CXX% %OPTIONS% %SOURCES% %INCLUDES% %LINK% %LINKEROPTIONS%
)

if "%1" == "run" (
   %OUTPUT%.exe
)

