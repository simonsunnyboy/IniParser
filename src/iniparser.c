/**
 * @addtogroup IniParser
 * @{
 * @file iniparser.c
 * @brief Simple INI file parser implementation.
 *
 * This file contains functions to parse INI configuration files,
 * including trimming whitespace, stripping comments, and parsing
 * sections and key-value pairs.
 *
 * @author Matthias Arndt <marndt@final-memory.org>
 * @copyright The MIT License (MIT)
 * 
 * Copyright (c) 2025 Matthias Arndt <marndt@final-memory.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#include "iniparser/iniparser.h"

/**
 * @brief Removes leading and trailing whitespace from a string.
 *
 * This function modifies the input string in place by:
 * - Advancing the pointer past any leading whitespace characters.
 * - Replacing trailing whitespace characters with null terminators.
 *
 * @param[in, out] str Pointer to the input string to be trimmed. Must be modifiable.
 * @return Pointer to the trimmed string (may be shifted forward from the original).
 *
 * @note The returned pointer may not be the same as the original input.
 *       The input string is modified directly and must be writable. 
 */
static char *IniParser_trim(char *str) {
    assert(str != NULL);
    while (isspace((unsigned char)*str)) str++;

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }

    return str;
}

/**
 * @brief Removes comments and trailing newline from a line of text.
 *
 * This function scans the input string and strips out comments that begin with
 * a semicolon (`;`) or hash (`#`) character, unless they appear inside double quotes.
 * It also removes a trailing newline character if present.
 *
 * @param[in, out] line Pointer to a modifiable null-terminated string. Must not be NULL.
 *
 * @return None.
 *
 * @note The input string is modified in place. Quoted comment characters are preserved.
 *
 * @warning The function uses an assertion to ensure the input is not NULL.
 *          Passing a NULL pointer will terminate the program.
 */
static void IniParser_stripComments(char *line) {
    bool in_quotes = false;

    assert(line != NULL);

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '"') {
            in_quotes = !in_quotes;
        } else if ((line[i] == ';' || line[i] == '#') && !in_quotes) {
            line[i] = '\0';
            break;
        }
        else {
            // continue scanning
        }
    }

    // Remove trailing newline
    size_t len = strlen(line);
    if ((len > 0) && (line[len - 1] == '\n')) {
        line[len - 1] = '\0';
    }
}

/**
 * @internal see iniparser.h
 */
void IniParser_parse(char *line, IniParserResult *result) {
    assert(line != NULL);
    IniParser_stripComments(line);
    char *trimmed = IniParser_trim(line);

    *result = (IniParserResult){.Section = NULL, .Key = NULL, .Value = NULL };

    if (*trimmed != '\0') {
        if (*trimmed == '[') {
            char *end = strchr(trimmed, ']');
            if (end) {
                *end = '\0';
                result->Section = IniParser_trim(trimmed + 1);
            }
        } else {
            char *equals = strchr(trimmed, '=');
            if (equals) {
                *equals = '\0';
                result->Key = IniParser_trim(trimmed);

                if(result->Key != NULL && strlen(result->Key) == 0)
                {
                    result->Key = NULL;
                }   

                result->Value = IniParser_trim(equals + 1);

                if(result->Value != NULL && strlen(result->Value) == 0)
                {
                    result->Value = NULL;
                }
            }
        }    
    }
}

/**
 * @}
 */
