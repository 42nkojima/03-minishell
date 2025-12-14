/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:48:22 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/06 16:41:23 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "lexical.h"
# include "repl.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_parse_result
{
	t_token_list	*token_list;
}					t_parse_result;

typedef struct s_command
{
	char			**argv;
	char			**envp;
}					t_command;

bool				init_signal_handlers(void);

void				free_token_list(t_token_list *list);
void				free_split(char **arr);

#endif // MINISHELL_H
