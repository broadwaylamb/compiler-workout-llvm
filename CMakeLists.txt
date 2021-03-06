cmake_minimum_required(VERSION 3.0.0)

project(compiler-workout-llvm)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(LLVM_LIBS support core irreader)

set(SOURCES_DIR lib)
set(HEADERS_DIR include)
set(TEST_DIR tests)

# SOURCES
set(SOURCES ${SOURCES_DIR}/Expr.cpp
            ${SOURCES_DIR}/Stmt.cpp
            ${SOURCES_DIR}/ASTPrinter.cpp)

# HEADERS
set(HEADERS ${HEADERS_DIR}/Expr.h
            ${HEADERS_DIR}/Stmt.h
            ${HEADERS_DIR}/ASTPrinter.h)

set(LIBRARY_NAME compiler-workout-llvm)

add_library(${LIBRARY_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${HEADERS_DIR})

# Link against LLVM libraries
target_link_libraries(${LIBRARY_NAME} ${LLVM_LIBS})

find_program(CLANG_FORMAT NAMES clang-format)

if(CLANG_FORMAT)
  foreach(TARGET_NAME ${LIBRARY_NAME} ${TEST_TARGET_NAMES})
    add_custom_command(TARGET ${TARGET_NAME}
                       POST_BUILD
                       COMMAND ${CLANG_FORMAT} -i ${SOURCES} ${HEADERS} ${TESTS}
                       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                       COMMENT "Running clang-format...")
  endforeach(TARGET_NAME)
endif(CLANG_FORMAT)

enable_testing()

