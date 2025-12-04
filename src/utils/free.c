


#include "minishell.h"

void free_token_list(t_token_list *list)
{
    size_t i;

    if (!list)
        return;

    i = 0;
    while (i < list->count)
    {
        free(list->tokens[i].value);
        i++;
    }
    free(list->tokens);
    free(list);
}
