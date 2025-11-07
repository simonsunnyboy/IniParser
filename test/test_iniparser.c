/**
 * @addtogroup IniParser
 * @{
 * @file test_iniparser.c
 * @brief Simple INI file parser unit test with output to terminal
 *
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

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "iniparser/iniparser.h"

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ini_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        IniParserResult result;
        IniParser_parse(line, &result);
        
        if (result.Section) {
            printf("Parsed Section: '%s'\n", result.Section);
        } else if (result.Key) {
            if(result.Value) {
                printf("Parsed Key: '%s', Value: '%s'\n", result.Key, result.Value);
            } else {
                printf("Parsed Key: '%s' WITHOUT value\n", result.Key);
            }        
        } else if (result.Key == NULL) {
            if(result.Value != NULL) {
                printf("Parsed Value: '%s' WITHOUT key\n", result.Value);
            }
        }
        else {
            // Blank line or comment
        }       
    }

    fclose(file);
    return 0;
}
