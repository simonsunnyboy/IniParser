# .INI file parser

Copyright (c) 2025 Matthias Arndt <marndt@final-memory.org>

The MIT License applies. See the file LICENSE for details

## Abstract

This is a parser for .INI files used by older Windows programs written in C99.
A service function determines section names, key and value pairs from a given input.

## System requirements

- C99 compliant C compiler
- CMake

## File format understood

- section names given in [ and ] or key names are trimmed by leading and trailing whitespace
  E.g. [ section name ] gives the valid section "section name"
- key/value pairs may be indented with white space
- leading and trailing whitespace is eliminated
- comments with # and ; are both identified and ignored
- lines may start with comment or have a trailing comment
- empty lines are ignored

## Limitations

- The parser cannot handle values given in quotes stretching over multiple
  lines.
