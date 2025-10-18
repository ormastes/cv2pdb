cmake_minimum_required(VERSION 3.15)
project(main_test)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force MinGW Clang compiler flags for DWARF debug info
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Use DWARF debug format (required for cv2pdb)
    set(CMAKE_CXX_FLAGS_DEBUG "-g -gdwarf-2 -O0")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -gdwarf-2 -O2")

    # Disable incremental linking
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--disable-auto-image-base")
endif()

# Find cv2pdb executable
find_program(CV2PDB_EXE
    NAMES cv2pdb.exe cv2pdb
    PATHS
        "${CMAKE_SOURCE_DIR}/../bin/Release_x64"
        "${CMAKE_SOURCE_DIR}/../bin/Debug_x64"
    NO_DEFAULT_PATH
)

if(NOT CV2PDB_EXE)
    message(WARNING "cv2pdb not found. PDB generation will be skipped.")
endif()

# Create the executable
add_executable(main main.cpp)

# Post-build step to generate PDB using cv2pdb
if(CV2PDB_EXE)
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Running cv2pdb to generate PDB and overwrite executable..."
        COMMAND ${CV2PDB_EXE} "$<TARGET_FILE:main>" "$<TARGET_FILE:main>"
        COMMAND ${CMAKE_COMMAND} -E echo "====================================="
        COMMAND ${CMAKE_COMMAND} -E echo "Build complete!"
        COMMAND ${CMAKE_COMMAND} -E echo "Executable (with PDB): $<TARGET_FILE:main>"
        COMMAND ${CMAKE_COMMAND} -E echo "PDB file:              $<TARGET_FILE_DIR:main>/main.pdb"
        COMMAND ${CMAKE_COMMAND} -E echo "====================================="
        COMMENT "Converting DWARF debug info to PDB format and updating executable"
        VERBATIM
    )
endif()

# Install target (optional)
install(TARGETS main DESTINATION bin)
