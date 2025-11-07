if(NOT PROJECT_NAME)
    project(IniParser)
    set(INIPARSER_ENABLE_UNITTEST)
endif()

add_executable(IniParser
    src/iniparser.c
)
