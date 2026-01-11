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

volatile sig_atomic_t	g_interrupt = 1;

int	noop(void)
{
	return (0);
}

static void	process_input(char *input)
{
	t_ast_node	*ast;

	if (!*input)
		return ;
	add_history(input);
	ast = parse(input);
	if (!ast)
		return ;
	//ToDo: execute(ast);
	free_ast(ast);
}

static char	*read_prompt(void)
{
	char	*input;

	g_interrupt = 0;
	input = readline("minishell$ ");
	if (g_interrupt)
	{
		free(input);
		return (NULL);
	}
	return (input);
}

bool	run_repl(void)
{
	char	*input;

	rl_event_hook = noop;
	while (true)
	{
		input = read_prompt();
		if (!input)
			continue;
		if (input == NULL)
			break ;
		process_input(input);
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
