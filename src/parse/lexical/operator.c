#include "minishell.h"

bool is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}


size_t	handle_operator(t_token_list *list, char *s, size_t i)
{
	if (s[i] == '|')
	{
		add_token(list, PIPE, ft_strdup("|"), false, false);
		return (i + 1);
	}
	if (s[i] == '<' && s[i + 1] == '<')
	{
		add_token(list, HEREDOC, ft_strdup("<<"), false, false);
		return (i + 2);
	}
	if (s[i] == '>' && s[i + 1] == '>')
	{
		add_token(list, REDIR_APPEND, ft_strdup(">>"), false, false);
		return (i + 2);
	}
	if (s[i] == '<')
	{
		add_token(list, REDIR_IN, ft_strdup("<"), false, false);
		return (i + 1);
	}
	if (s[i] == '>')
	{
		add_token(list, REDIR_OUT, ft_strdup(">"), false, false);
		return (i + 1);
	}
	return (i);
}
