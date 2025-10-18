@echo off
REM Build script that works in both CMD and PowerShell

REM Add compiler to PATH (works in both CMD and PowerShell)
set "PATH=C:\dev\WinMG32\bin;%PATH%"

echo Building main.cpp with debug info...
clang -g -O0 -m32 main.cpp -o main.exe
clang -g -O0 -m32 main3.cpp -o main3.exe

if %errorlevel% neq 0 (
    echo Build failed!
    exit /b 1
)

echo Dumping raw DWARF info...
llvm-dwarfdump main.exe > dwarf_dump.txt 2>&1
llvm-dwarfdump main3.exe > dwarf_dump3.txt 2>&1

echo Converting DWARF to PDB...
..\bin\Debug_x64\cv2pdb.exe main.exe main_new.exe main.pdb > dwarf2pdb_log.txt 2>&1
..\bin\Debug_x64\cv2pdb.exe main3.exe main3_new.exe main3.pdb > dwarf2pdb_log3.txt 2>&1

if %errorlevel% neq 0 (
    echo cv2pdb conversion failed!
    exit /b 1
)

echo Dumping PDB information...
llvm-pdbutil dump -types main.pdb > types.txt 2>&1
llvm-pdbutil dump -symbols main.pdb > symbols.txt 2>&1
llvm-pdbutil dump -summary main.pdb > summary.txt 2>&1

echo Build complete! Check types.txt, symbols.txt, summary.txt, and dwarf_dump.txt for details.