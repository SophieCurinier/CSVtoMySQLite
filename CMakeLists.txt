cmake_minimum_required(VERSION 3.0.0)
project(vals VERSION 0.1.0)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

## Google Test ##
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)
## Google Test ##

## SQLite3 ##
SET(DCMAKE_TOOLCHAIN_FILE "/usr/bin/vcpkg/scripts/buildsystems/vcpkg.cmake")
include("/usr/bin/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(unofficial-sqlite3 CONFIG REQUIRED)

enable_testing()

add_executable(
  hello_test
  tests/hello_test.cpp
)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)

target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
