cmake_minimum_required(VERSION 3.0.0)
project(pImpl VERSION 1.1.3 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(src)
add_subdirectory(examples)
# add_subdirectory(test)