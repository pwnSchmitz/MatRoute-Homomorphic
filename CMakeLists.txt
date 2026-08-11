cmake_minimum_required(VERSION 3.10)
project(CryptoSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/core/Matrix.cpp
    src/core/Route.cpp
    src/core/Alphabet.cpp
    src/crypto/Encryptor.cpp
    src/crypto/Decryptor.cpp
    src/utils/FileUtils.cpp
    src/utils/StringUtils.cpp
)

# Executable
add_executable(crypto_system ${SOURCES})

# Optional: enable warnings
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(crypto_system PRIVATE -Wall -Wextra -Wpedantic)
endif()