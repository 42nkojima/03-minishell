/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:44:57 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/08 07:16:34 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

int	noop(void)
{
	return (0);
}

static void	process_input(char *input, t_env **env, int *last_status)
{
	t_ast_node	*ast;
	int			status;

	if (!*input)
		return ;
	add_history(input);
	ast = parse(input, *env, *last_status);
	if (!ast)
		return ;
	status = prepare_heredocs(ast);
	if (status == EXIT_SUCCESS)
		*last_status = execute_ast(ast, env);
	*last_status = status;
	close_prepared_heredocs(ast);
	free_ast(ast);
}

char	*read_prompt(t_prompt_status *status)
{
	char	*input;

	*status = PROMPT_OK;
	g_signal_status = 0;
	input = readline("minishell$ ");
	if (g_signal_status == SIGINT)
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
	int				last_status;

	rl_event_hook = noop;
	last_status = 0;
	while (true)
	{
		input = read_prompt(&status);
		if (status == PROMPT_INTERRUPT)
			continue ;
		if (status == PROMPT_EOF)
			break ;
		process_input(input, &env, &last_status);
		free(input);
	}
	return (true);
}

void	sigint_handler(int signo)
{
	g_signal_status = signo;
	rl_done = 1;
}
