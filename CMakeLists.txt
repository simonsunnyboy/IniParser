if(NOT PROJECT_NAME)
    cmake_minimum_required(VERSION 3.10)
    project(IniParser)
    set(INIPARSER_ENABLE_UNITTEST ON)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(IniParser
    src/iniparser.c
)

if(INIPARSER_ENABLE_UNITTEST)
    message(STATUS "Enabling unit tests")
    enable_testing()
    add_subdirectory(test)
endif()
