# main.cpp Build Configuration

## Overview
This directory contains a CMake-based build setup for `main.cpp` that:
- Builds with Clang compiler (DWARF debug format)
- Automatically converts DWARF debug info to PDB format using cv2pdb
- **Overwrites the executable in-place** with PDB-enhanced version
- Generates Visual Studio-compatible debugging files

## Files Generated

### Build Configuration
- `CMakeLists.txt` - Main CMake configuration
- `mingw-clang-toolchain.cmake` - Clang toolchain file (optional)
- `build.bat` - Automated build script

### Build Outputs (in build/ directory)
- `main.exe` - Executable with PDB debug info (overwritten by cv2pdb)
- `main.pdb` - PDB file for Visual Studio debugger
- `main_debug.sln` - Visual Studio solution for debugging

## Quick Start

### Option 1: Using the build script
```batch
build.bat
```

### Option 2: Manual build
```batch
mkdir build
cd build
cmake -G "Ninja" ^
  -DCMAKE_C_COMPILER="C:/dev/install/clang+llvm-18.1.8-x86_64-pc-windows-msvc/bin/clang.exe" ^
  -DCMAKE_CXX_COMPILER="C:/dev/install/clang+llvm-18.1.8-x86_64-pc-windows-msvc/bin/clang++.exe" ^
  -DCMAKE_BUILD_TYPE=Debug ^
  ..
ninja
```

## Debugging in Visual Studio

1. Navigate to `bug_test/build/`
2. Open `main_debug.sln` in Visual Studio
3. Press F5 to start debugging
4. The debugger will use `main.exe` and `main.pdb`

## How It Works

1. **Compilation**: Clang compiles `main.cpp` with `-gdwarf-2` flag to generate DWARF debug info
2. **Linking**: Executable is created with embedded DWARF sections
3. **Post-Build**: CMake runs `cv2pdb main.exe main.exe` automatically
4. **Conversion**: cv2pdb converts DWARF to PDB and **overwrites the original executable**
5. **Output**: Single `main.exe` with PDB format + separate `main.pdb` file

## Key Features

- **In-Place Update**: cv2pdb overwrites the executable (no separate `_pdb` files)
- **Bitfield Support**: Includes latest cv2pdb with bitfield support
- **Automatic PDB Generation**: No manual steps needed after running build
- **VS Debugging Ready**: Generated files work directly with Visual Studio debugger

## Rebuilding

To clean and rebuild:
```batch
rd /s /q build
build.bat
```

## File Comparison

### Before cv2pdb (after linking)
- `main.exe` - Contains DWARF debug sections

### After cv2pdb (post-build)
- `main.exe` - **Updated** with PDB debug format (DWARF sections removed/replaced)
- `main.pdb` - PDB debug database (newly created)

The executable is **overwritten in-place**, not copied to a new file.
