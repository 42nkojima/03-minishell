/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:46:31 by nkojima           #+#    #+#             */
/*   Updated: 2025/12/04 22:39:44 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_signal_handlers(void)
{
	if (assign_signal_handler(SIGINT, sigint_handler, SA_RESTART) == false)
		return (false);
	if (assign_signal_handler(SIGQUIT, SIG_IGN, SA_RESTART) == false)
		return (false);
	return (true);
}

int	main(void)
{
	if (!init_signal_handlers())
	{
		ft_putstr_fd("Error: init_signal_handlers failed\n", 2);
		return (1);
	}
	run_repl();
	return (0);
}
