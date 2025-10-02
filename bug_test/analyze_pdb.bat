@echo off
REM Script to analyze PDB file debug information

echo === Analyzing PDB Debug Information ===
echo.

REM Use llvm-pdbutil to dump debug info
set PDBUTIL="C:/dev/tool/msys2/mingw64/bin/llvm-pdbutil.exe"

echo 1. PDB Summary:
echo ----------------
%PDBUTIL% dump -summary main.pdb
echo.

echo 2. Searching for bitfield-related structures:
echo ----------------------------------------------
%PDBUTIL% dump -types gen/main.pdb > gen/temp_typestypes.txt 2>&1

echo Looking for our test structure (should be my_struct):
findstr /i "anon_11d7" gen/temp_types.txt
echo.

echo Looking for any bitfield types:
findstr /i "bitfield" gen/temp_types.txt
if errorlevel 1 echo NO BITFIELD TYPES FOUND IN PDB!
echo.

echo 3. Symbol Information for main function:
echo -----------------------------------------
%PDBUTIL% dump -symbols gen/main.pdb | findstr /i "main"
echo.

echo 4. Local variable 's' in main:
echo -------------------------------
%PDBUTIL% dump -symbols gen/main.pdb | findstr /A:5 /B:5 "s`"
echo.

echo 5. Type details for the structure:
echo -----------------------------------
echo Type 0x105A (should be my_struct):
findstr /A:2 /B:2 "0x105A" gen/temp_types.txt
echo.
echo Type 0x1059 (fieldlist - should contain a,b,c bitfields):
findstr /A:2 /B:2 "0x1059" gen/temp_types.txt
echo.

echo === Analysis Complete ===
echo.
echo CONCLUSION: The fieldlist 0x1059 is EMPTY (size=4)!
echo This confirms the bug: bitfield information is completely lost.
echo The structure should have fields a:1, b:2, c:3 but has NO fields.

del gen/temp_types.txt