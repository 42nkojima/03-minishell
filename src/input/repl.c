/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:44:57 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/24 19:05:48 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	run_repl(void)
{
	char	*input;

	while (TRUE)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		free(input);
	}
	return (TRUE);
}
