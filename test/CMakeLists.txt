add_executable(test_iniparser
    test_iniparser.c
)
target_link_libraries(test_iniparser IniParser)

add_test(NAME IniParserTest COMMAND test_iniparser ${CMAKE_CURRENT_SOURCE_DIR}/simple.ini)