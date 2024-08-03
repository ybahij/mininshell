#include "mini.h"

lexer_t *lexer_c(char type, char *value)
{
    lexer_t *lexer = malloc(sizeof(lexer_t));

    if (!lexer)
        return (NULL);
    lexer->type = strdup(&type);
    lexer->value = strdup(value);
    lexer->next = NULL;
    return (lexer);
}