/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:44:57 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/24 21:53:45 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_interrupt = 1;

int	noop(void)
{
	return (0);
}

t_bool	run_repl(void)
{
	char	*input;

	rl_event_hook = noop;
	while (TRUE)
	{
		g_interrupt = 0;
		input = readline("minishell$ ");
		if (g_interrupt)
		{
			free(input);
			continue ;
		}
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		free(input);
	}
	return (TRUE);
}

void	sigint_handler(int signo)
{
	(void)signo;
	g_interrupt = 1;
	rl_done = 1;
}

t_bool	assign_signal_handler(int signum, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = flags;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, NULL) == -1)
	{
		perror("Error setting up sigaction");
		return (FALSE);
	}
	return (TRUE);
}
