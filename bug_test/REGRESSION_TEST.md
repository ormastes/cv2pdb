# Regression Test Results

## Comparison: Original (fd4ecc0) vs Fixed (merged2)

### Test Date
2025-10-19

### Purpose
Verify that bitfield support and union fix did not introduce regressions in primitive type handling.

### Methodology
1. Checked out commit fd4ecc0 (before bitfield support at 1225c71)
2. Built original cv2pdb
3. Converted main3_gcc.exe to main3_original.pdb
4. Compared with main3_fixed.pdb from current merged2 branch
5. Used llvm-pdbutil to generate full type dumps

### Results

#### NO REGRESSIONS FOUND ✓

All primitive types are handled identically between original and fixed versions:
- int, float, double, char types: **IDENTICAL**
- Pointer types: **IDENTICAL**
- Array types: **IDENTICAL**
- Struct types: **IDENTICAL**
- Class types: **IDENTICAL**
- Enum types: **IDENTICAL**

#### Improvements in Fixed Version

**Union Type Handling - FIXED**
- Original: Unions converted as `LF_STRUCTURE` (INCORRECT)
- Fixed: Unions converted as `LF_UNION` (CORRECT)

Types affected (all correctly changed from LF_STRUCTURE to LF_UNION):
- 0x1045: `_NT_TIB::[anon_7c6]`
- 0x1047: `_EXCEPTION_REGISTRATION_RECORD::[anon_818]`
- 0x1049: `_EXCEPTION_REGISTRATION_RECORD::[anon_841]`
- 0x106C: `XX` (test case union)
- 0x1088: `_IMAGE_SECTION_HEADER::[anon_21dd]`
- 0x10DA: `_IMAGE_SECTION_HEADER::[anon_41ae]`
- 0x10E5: `_IMAGE_IMPORT_DESCRIPTOR::[anon_429c]`

### Important Note: DWARF Version Requirement

**GCC DWARF-2 does NOT generate DW_TAG_union_type tags for unions.**

To test union detection, compile with DWARF-3 or DWARF-4:
- GCC: Use `-gdwarf-3` or `-gdwarf-4` flag
- DWARF-2: Unions are emitted as structures (gcc limitation)
- DWARF-3/4: Unions properly emitted with DW_TAG_union_type tags

cv2pdb currently supports DWARF-2 and DWARF-3.

### Union Fix Verification

Tested with `union_test.c` and `main3.cpp` compiled with DWARF-3:
- Simple union `SimpleUnion`: Correctly converted to `LF_UNION` ✓
- Union with anonymous struct `XX`: Correctly converted to `LF_UNION` ✓
- Type 0x1078 in main3_dw3.pdb shows: `LF_UNION [size = 20] 'XX'` ✓

### Conclusion

The union bug was **pre-existing** in the original version, NOT introduced by bitfield support.
The current merged2 branch with union fix represents an **improvement** over the original.

**Status: PASSED - No regressions detected**
**Union Fix: VERIFIED and WORKING with DWARF-3**
