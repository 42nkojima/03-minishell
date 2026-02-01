/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:44:57 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/01 16:09:30 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

volatile sig_atomic_t	g_interrupt = 1;

int	noop(void)
{
	return (0);
}

static void	process_input(char *input, t_env *env)
{
	t_ast_node	*ast;

	if (!*input)
		return ;
	add_history(input);
	ast = parse(input);
	if (!ast)
		return ;
	execute_ast(ast, env);
	free_ast(ast);
}

char	*read_prompt(t_prompt_status *status)
{
	char	*input;

	*status = PROMPT_OK;
	g_interrupt = 0;
	input = readline("minishell$ ");
	if (g_interrupt)
	{
		*status = PROMPT_INTERRUPT;
		free(input);
		return (NULL);
	}
	if (input == NULL)
	{
		*status = PROMPT_EOF;
		return (NULL);
	}
	return (input);
}

bool	run_repl(t_env *env)
{
	char			*input;
	t_prompt_status	status;

	rl_event_hook = noop;
	while (true)
	{
		input = read_prompt(&status);
		if (status == PROMPT_INTERRUPT)
			continue ;
		if (status == PROMPT_EOF)
			break ;
		process_input(input, env);
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
