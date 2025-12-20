#include "libht.h"
#include "lexical.h"
#include <stdio.h>
#include <stdlib.h>

bool	add_token(
	t_token_list *list,
	t_token_type type,
	char *value,
	bool has_env,
	bool single_quoted)
{
	list->tokens[list->count].type = type;
	list->tokens[list->count].value = value;
	list->tokens[list->count].has_env = has_env;
	list->tokens[list->count].single_quoted = single_quoted;
	list->count++;
	return (true);
}

t_token_list	*token_list_init(size_t count)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	if (!list)
		return (NULL);
	list->tokens = malloc(sizeof(t_token) * count);
	if (!list->tokens)
		return (free(list), NULL);
	list->count = count;
	return (list);
}

static size_t	skip_spaces(char *s, size_t i)
{
	while (s[i] == ' ')
		i++;
	return (i);
}

t_token_list	*tokenizer(char *input)
{
	t_token_list	*list;
	size_t			i;

	if (!input)
		return (NULL);
    list = token_list_init(ft_strlen(input)+1);
    if (!list)
        return (NULL);
    i = 0;
    while(input[i])
    {
		i = skip_spaces(input, i);
		if (!input[i])
			break;
        if (is_quote(input[i])) 
            i = handle_quoted_word(list,input,i);
        else if (is_operator(input[i])) 
            i = handle_operator(list,input,i);
        else
            i = handle_word(list,input,i);
    }

    return (list);
}

const char *token_type_to_str(t_token_type type)
{
	if (type == WORD) return "WORD";
	if (type == PIPE) return "PIPE";
	if (type == REDIR_IN) return "REDIR_IN";
	if (type == REDIR_OUT) return "REDIR_OUT";
	if (type == REDIR_APPEND) return "REDIR_APPEND";
	if (type == HEREDOC) return "HEREDOC";
	return "UNKNOWN";
}

void	print_tokens(t_token_list *list)
{
	size_t	i;

	i = 0;
	while (i < list->count)
	{
		printf(
			"[%zu] type=%s, value=\"%s\", has_env=%d, single_quoted=%d\n",
			i,
			token_type_to_str(list->tokens[i].type),
			list->tokens[i].value,
			list->tokens[i].has_env,
			list->tokens[i].single_quoted
		);
		i++;
	}
}

int	main(void)
{
	char *inputs[] = {
		"ls -l",
		"echo hello | grep h",
		"echo \"hello world\"",
		"echo '$HOME'",
		"cat << EOF",
		"echo $HOME >> out.txt",
		NULL
	};

	for (int i = 0; inputs[i]; i++)
	{
		printf("\nINPUT: %s\n", inputs[i]);
		t_token_list *list = tokenizer(inputs[i]);
		print_tokens(list);
		// free_token_list(list); ← 後で必ず
	}
}



