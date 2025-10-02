@echo off
REM Build script that works in both CMD and PowerShell

REM Add compiler to PATH (works in both CMD and PowerShell)
set "PATH=C:\dev\WinMG32\bin;%PATH%"

echo Building main.cpp with debug info...
clang -g -O0 -m32 main.cpp -o gen/main.exe
clang -g -O0 -m32 main3.cpp -o gen/main3.exe

if %errorlevel% neq 0 (
    echo Build failed!
    exit /b 1
)

echo Dumping raw DWARF info...
llvm-dwarfdump gen/main.exe > gen/dwarf_dump.txt 2>&1
llvm-dwarfdump gen/main3.exe > gen/dwarf_dump3.txt 2>&1

echo Converting DWARF to PDB...
..\bin\Release_x64\cv2pdb.exe gen/main.exe gen/main_new.exe gen/main.pdb > gen/dwarf2pdb_log.txt 2>&1
..\bin\Release_x64\cv2pdb.exe gen/main3.exe gen/main3_new.exe gen/main3.pdb > gen/dwarf2pdb_log3.txt 2>&1

if %errorlevel% neq 0 (
    echo cv2pdb conversion failed!
    exit /b 1
)

echo Dumping PDB information...
llvm-pdbutil dump -types gen/main.pdb > gen/types.txt 2>&1
llvm-pdbutil dump -symbols gen/main.pdb > gen/symbols.txt 2>&1
llvm-pdbutil dump -summary gen/main.pdb > gen/summary.txt 2>&1
llvm-pdbutil dump -types gen/main3.pdb > gen/types3.txt 2>&1
llvm-pdbutil dump -symbols gen/main3.pdb > gen/symbols3.txt 2>&1
llvm-pdbutil dump -summary gen/main3.pdb > gen/summary3.txt 2>&1

echo Build complete! Check types.txt, symbols.txt, summary.txt, and dwarf_dump.txt for details.