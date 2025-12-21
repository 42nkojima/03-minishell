/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:51:41 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 12:03:57 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_H
# define LEXICAL_H

# include <stdbool.h>
# include <stdio.h>

typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			has_env;
	bool			single_quoted;
}					t_token;

typedef enum e_lex_error
{
	ERR_NONE,
	ERR_UNCLOSED_QUOTE
}					t_lex_error;

typedef struct s_token_list
{
	t_token			*tokens;
	size_t			count;
	t_lex_error		error;
}					t_token_list;

typedef enum e_quote_state
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}					t_quote_state;

bool				is_quote(char c);
bool				is_operator(char c);
size_t				handle_quoted_word(t_token_list *list, char *s, size_t i);
size_t				handle_operator(t_token_list *list, char *s, size_t i);
size_t				handle_word(t_token_list *list, char *s, size_t i);
t_token_list		*tokenizer(char *input);
bool				add_token(t_token_list *list, t_token_type type,
						char *value, bool has_env, bool single_quoted);

#endif // LEXICAL_H
