#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define DEFAULT_LINE_SIZE 100

/**
 * Tests whether or not c is a character signifying the end of a line
 *
 * char c - The character to test
 *
 * return - 1 if the character is a line end, 0 if not
 */
int is_endl(char c);

/**
 * Prints a format string followed by a newline
 *
 * char const *format - The format string
 * ... - Arguments following the format string
 *
 * return - Number of characters written (minus newline)
 */
int emit(char const *format, ...);

/**
 * Reads a line from stdin and returns a string representation
 *
 * return - String containing the line read
 */
char * read_line(int *length);
