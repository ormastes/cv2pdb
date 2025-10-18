@echo off
echo Cleaning up generated files in bug_test folder...

REM Remove executables (except source files)
del /q main.exe 2>nul
del /q main_*.exe 2>nul
del /q main3.exe 2>nul
del /q main3_*.exe 2>nul
del /q test_*.exe 2>nul

REM Remove PDB files
del /q *.pdb 2>nul

REM Remove ILK files
del /q *.ilk 2>nul

REM Remove log and dump files
del /q dwarf_dump*.txt 2>nul
del /q dwarf2pdb_log*.txt 2>nul
del /q types*.txt 2>nul
del /q symbols.txt 2>nul
del /q summary.txt 2>nul

REM Remove debug script files
del /q cdb_script.txt 2>nul
del /q debug_commands.txt 2>nul
del /q debug_test.txt 2>nul

REM Remove object files if any
del /q *.obj 2>nul
del /q *.o 2>nul

echo Cleanup complete!
echo.
echo Remaining files:
dir /b *.cpp *.c *.h *.bat *.md 2>nul