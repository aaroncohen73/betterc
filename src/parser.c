#include <stdlib.h>
#include "lexer.h"

#include "parser.h"

struct ast_node * create_ast_node(void)
{
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->atom = malloc(sizeof(struct ast_atom));

    return node;
}

struct ast_node * parse_tokens(struct token *t)
{
    struct ast_node *root;
    struct token *cur;

    if (t == NULL)
        return NULL;

    root = create_ast_node();
    cur = t;

    while (cur != NULL)
    {
        
    }
}
