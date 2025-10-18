@echo off
echo ===================================
echo Building main.cpp with Clang
echo ===================================

if not exist build mkdir build
cd build

echo.
echo [1/3] Configuring CMake...
cmake -G "Ninja" ^
  -DCMAKE_C_COMPILER="C:/dev/install/clang+llvm-18.1.8-x86_64-pc-windows-msvc/bin/clang.exe" ^
  -DCMAKE_CXX_COMPILER="C:/dev/install/clang+llvm-18.1.8-x86_64-pc-windows-msvc/bin/clang++.exe" ^
  -DCMAKE_BUILD_TYPE=Debug ^
  ..

if %errorlevel% neq 0 (
    echo CMake configuration failed!
    exit /b %errorlevel%
)

echo.
echo [2/3] Building with Ninja...
ninja

if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)

echo.
echo [3/3] Verifying outputs...
echo.
dir main.exe main.pdb
echo.
echo ===================================
echo SUCCESS! Files generated:
echo   - main.exe    (Updated with PDB debug info)
echo   - main.pdb    (PDB file for Visual Studio debugging)
echo.
echo To debug in Visual Studio:
echo   1. Open main_debug.sln
echo   2. Press F5 to start debugging
echo ===================================
