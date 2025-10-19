cmake_minimum_required(VERSION 3.15)
project(main_test)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")

# Verify we're using Clang
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(WARNING "")
    message(WARNING "!!! Not using Clang compiler! Detected: ${CMAKE_CXX_COMPILER_ID}")
    message(WARNING "!!! Please specify Clang explicitly:")
    message(WARNING "!!!   cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..")
    message(WARNING "")
endif()

# FORCE 32-bit compilation for all builds
message(STATUS "Configuring for 32-bit build")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -target i686-pc-windows-gnu")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -target i686-pc-windows-gnu")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")

# Use DWARF debug info (DWARF-5 for Clang 14+)
set(CMAKE_CXX_FLAGS_DEBUG "-g -gdwarf-5 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-g -gdwarf-5 -O2")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -gdwarf-5 -O2")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-g -gdwarf-5 -Os")

# Also set C flags
set(CMAKE_C_FLAGS_DEBUG "-g -gdwarf-5 -O0")
set(CMAKE_C_FLAGS_RELEASE "-g -gdwarf-5 -O2")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g -gdwarf-5 -O2")
set(CMAKE_C_FLAGS_MINSIZEREL "-g -gdwarf-5 -Os")

message(STATUS "Debug flags: ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")

# Find cv2pdb executable - REQUIRED for debugging
set(CV2PDB_SEARCH_PATHS
    "${CMAKE_SOURCE_DIR}/../bin/Release_x64"
    "${CMAKE_SOURCE_DIR}/../bin/Debug_x64"
    "${CMAKE_SOURCE_DIR}/../bin/Release"
    "${CMAKE_SOURCE_DIR}/../bin/Debug"
    "${CMAKE_SOURCE_DIR}/../bin"
    "${CMAKE_SOURCE_DIR}/.."
)

find_program(CV2PDB_EXE
    NAMES cv2pdb.exe cv2pdb
    PATHS ${CV2PDB_SEARCH_PATHS}
    NO_DEFAULT_PATH
)

if(NOT CV2PDB_EXE)
    message(FATAL_ERROR "\n"
        "=====================================\n"
        "ERROR: cv2pdb.exe not found!\n"
        "=====================================\n"
        "cv2pdb is REQUIRED for debugging.\n"
        "\n"
        "Please build cv2pdb first:\n"
        "  1. Open ../src/cv2pdb.sln in Visual Studio\n"
        "  2. Build the solution (Release or Debug)\n"
        "  3. Re-run cmake\n"
        "\n"
        "Searched in:\n"
        "  ${CV2PDB_SEARCH_PATHS}\n"
        "=====================================\n"
    )
else()
    message(STATUS "Found cv2pdb: ${CV2PDB_EXE}")
endif()

# Create the main executables
add_executable(main3 main3.cpp)
add_executable(main main.cpp)

# Force 32-bit for each target explicitly
set_target_properties(main3 main PROPERTIES
    COMPILE_FLAGS "-m32"
    LINK_FLAGS "-m32"
)

# Create additional test executables if their source files exist
set(ALL_TARGETS main3 main)
set(OPTIONAL_SOURCES test_bitfield_only test_struct test_union simple_bitfield)

foreach(target ${OPTIONAL_SOURCES})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${target}.cpp")
        add_executable(${target} ${target}.cpp)
        set_target_properties(${target} PROPERTIES
            COMPILE_FLAGS "-m32"
            LINK_FLAGS "-m32"
        )
        list(APPEND ALL_TARGETS ${target})
        message(STATUS "Adding target: ${target}")
    endif()
endforeach()

# Post-build step to generate PDB using cv2pdb
foreach(target ${ALL_TARGETS})
    if(TARGET ${target})
        # Convert DWARF to PDB
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "====================================="
            COMMAND ${CMAKE_COMMAND} -E echo "Converting DWARF to PDB for ${target}..."
            COMMAND ${CMAKE_COMMAND} -E echo "Running: ${CV2PDB_EXE} $<TARGET_FILE:${target}>"
            COMMAND ${CV2PDB_EXE} "$<TARGET_FILE:${target}>" "$<TARGET_FILE:${target}>"
            COMMAND ${CMAKE_COMMAND} -E echo "PDB generated: $<TARGET_FILE_DIR:${target}>/${target}.pdb"
            COMMAND ${CMAKE_COMMAND} -E echo "====================================="
            COMMENT "Converting DWARF debug info to PDB format for ${target}"
            VERBATIM
        )

        # Copy PDB to build directory root for easier access
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE_DIR:${target}>/${target}.pdb"
                "${CMAKE_BINARY_DIR}/${target}.pdb"
            COMMENT "Copying ${target}.pdb to build directory"
            VERBATIM
        )
    endif()
endforeach()

# Set main3 as the startup project for IDEs
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main3)

# Print configuration summary
message(STATUS "")
message(STATUS "=====================================")
message(STATUS "Configuration Summary:")
message(STATUS "  Compiler: Clang 32-bit")
message(STATUS "  Debug Format: DWARF-5")
message(STATUS "  cv2pdb: ${CV2PDB_EXE}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Targets: ${ALL_TARGETS}")
message(STATUS "=====================================")
message(STATUS "")

# Install targets
install(TARGETS ${ALL_TARGETS} DESTINATION bin)