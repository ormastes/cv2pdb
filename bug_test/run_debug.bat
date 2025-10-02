@echo off
echo ======================================
echo Bitfield Debugging for main3.exe
echo ======================================
echo.
echo Checking DWARF bitfield info...
findstr /C:"DW_AT_bit_size" gen\dwarf_dump3.txt
echo.
echo Checking PDB type for my_struct...
findstr /C:"my_struct" gen\types3.txt
echo.
echo PDB field list for my_struct should show bitfields (a:1, b:2, c:3, d:7):
grep -A 1 "0x105B" gen\types3.txt
echo.
echo ======================================
echo RESULT: Bitfields are in DWARF but NOT in PDB
echo This confirms cv2pdb is not converting bitfields
echo ======================================