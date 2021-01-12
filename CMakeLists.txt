cmake_minimum_required(VERSION 3.0.0)
project(Argon VERSION 0.1.0)


include(CTest)
enable_testing()

include_directories(include)
set(SOURCE_FILES src/main.cpp src/token.cpp include/token.h src/tokenizer.cpp include/tokenizer.h src/token_unit.cpp include/token_unit.h)
add_executable(Argon "${SOURCE_FILES}")
set_property(TARGET Argon PROPERTY CXX_STANDARD 17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
