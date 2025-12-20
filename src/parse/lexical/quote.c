#include "minishell.h"

bool is_quote(char c)
{
    return (c == '\'' || c == '"');
}

size_t	handle_quoted_word(t_token_list *list, char *s, size_t i)
{
	char	quote;
	size_t	start;
	char	*word;
	bool	has_env;

	quote = s[i];
	i++;
	start = i;
	has_env = false;

	while (s[i] && s[i] != quote)
	{
		if (quote == '"' && s[i] == '$')
			has_env = true;
		i++;
	}

	if (!s[i])
		return (start);

	word = ft_substr(s, start, i - start);
	add_token(
		list,
		WORD,
		word,
		has_env,
		quote == '\''
	);
	return (i + 1);
}

