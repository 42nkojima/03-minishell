/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:44:57 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/06 16:39:10 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

volatile sig_atomic_t	g_interrupt = 1;
extern char				**environ;

int	noop(void)
{
	return (0);
}

static void	execute_simple_command(char *input)
{
	t_command	cmd;
	char		**argv;

	argv = ft_split(input, ' ');
	if (!argv || !argv[0])
	{
		free_split(argv);
		return ;
	}
	cmd.argv = argv;
	cmd.envp = environ;
	execute_command(&cmd);
	free_split(argv);
}

bool	run_repl(void)
{
	char	*input;

	rl_event_hook = noop;
	while (true)
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
		{
			add_history(input);
			execute_simple_command(input);
		}
		free(input);
	}
	return (true);
}

void	sigint_handler(int signo)
{
	(void)signo;
	g_interrupt = 1;
	rl_done = 1;
}

bool	assign_signal_handler(int signum, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = flags;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, NULL) == -1)
	{
		perror("Error setting up sigaction");
		return (false);
	}
	return (true);
}
