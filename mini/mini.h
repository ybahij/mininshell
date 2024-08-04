#include <stdio.h>              // Standard I/O functions
#include <stdlib.h>             // Standard library functions
#include <string.h>             // String manipulation functions
#include <unistd.h>             // POSIX API functions
#include <sys/types.h>          // Data types used in system calls
#include <sys/wait.h>           // Wait for process functions
#include <readline/readline.h>  // Readline library for input
#include <readline/history.h>

typedef struct lexer_s
{
    char *type;
    char *value;
    struct lexer_s *next;
}   lexer_t;

typedef struct append_s
{
    char *value;
    struct append_s *next;
}   append_t;

typedef struct cmd_s
{
    char *cmd;
    char **arg;
    char **input;
    char **output;
    append_t **append;
    struct cmd_s *next;
}   cmd_t;