@echo off
setlocal

set SOURCES=src\D3DRefactor\main.cpp
set INCLUDES=/I"%DXSDK_DIR%Include\"
set OPTIONS=/Zi /Foobj\game.obj /Fdobj\game.pdb
set LINK=user32.lib d3d11.lib d3dx11.lib D3DCompiler.lib dxerr.lib dxgi.lib dxguid.lib
set OUTPUT=bin\game.exe
set CXX=cl.exe
set LINKEROPTIONS=/link /OUT:out\game.exe /PDB:out\game.pdb

echo. 
echo ========= COMMAND =========
echo %CXX% %OPTIONS% %SOURCES% %LINK% %LINKEROPTIONS%
echo =========== END ===========
echo.

md out
md obj
%CXX% %OPTIONS% %SOURCES% %LINK% %LINKEROPTIONS%
