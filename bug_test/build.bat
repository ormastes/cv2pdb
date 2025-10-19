@echo off
setlocal

echo =====================================
echo Building with Clang 32-bit
echo =====================================
echo.

REM Clean previous builds
if exist build (
    echo Cleaning previous build...
    rmdir /s /q build
)

REM Create build directory
mkdir build
cd build

REM Configure with Clang 32-bit
echo Configuring with CMake (Clang 32-bit, Ninja)...
cmake -G "Ninja" ^
      -DCMAKE_C_COMPILER=clang ^
      -DCMAKE_CXX_COMPILER=clang++ ^
      -DCMAKE_BUILD_TYPE=Debug ^
      ..

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: CMake configuration failed!
    echo Make sure Clang is installed and in your PATH.
    cd ..
    pause
    exit /b 1
)

echo.
echo Building...
cmake --build .

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo =====================================
echo Build completed successfully!
echo =====================================
echo.
echo Executables with PDB files:
dir /b *.exe *.pdb 2>nul
echo.
echo You can now debug these in Visual Studio:
echo   1. Open Visual Studio
echo   2. File -^> Open -^> File... and select an .exe
echo   3. Press F5 to start debugging
echo.
cd ..
pause