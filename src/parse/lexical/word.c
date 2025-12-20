#include "minishell.h"

size_t	handle_word(t_token_list *list, char *s, size_t i)
{
	size_t	start;
	bool	has_env;
	char	*word;

	start = i;
	has_env = false;

	while (s[i]
		&& s[i] != ' '
		&& !is_operator(s[i])
		&& !is_quote(s[i]))
	{
		if (s[i] == '$')
			has_env = true;
		i++;
	}

	word = ft_substr(s, start, i - start);
	add_token(list, WORD, word, has_env, false);
	return (i);
}
