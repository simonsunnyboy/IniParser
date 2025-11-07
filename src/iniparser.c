#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1024

// Trim leading and trailing whitespace
char *trim(char *str) {
    while (isspace((unsigned char)*str)) str++;

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }

    return str;
}

// Remove comments unless inside quotes
void strip_comments(char *line) {
    bool in_quotes = false;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '"') {
            in_quotes = !in_quotes;
        } else if ((line[i] == ';' || line[i] == '#') && !in_quotes) {
            line[i] = '\0';
            break;
        }
    }

    // Remove trailing newline
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';
}

void parse_ini_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        strip_comments(line);
        char *trimmed = trim(line);

        if (*trimmed == '\0') continue; // Skip blank lines

        if (*trimmed == '[') {
            char *end = strchr(trimmed, ']');
            if (end) {
                *end = '\0';
                char *section = trim(trimmed + 1);
                printf("Section: '%s'\n", section);
            }
        } else {
            char *equals = strchr(trimmed, '=');
            if (equals) {
                *equals = '\0';
                char *key = trim(trimmed);
                char *value = trim(equals + 1);
                printf("Key: '%s', Value: '%s'\n", key, value);
            }
        }
    }

    fclose(file);
}
