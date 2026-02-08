/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:46:31 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/08 08:55:49 by nkojima          ###   ########.fr       */
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

t_env	*init_env_node(char *env_str)
{
	t_env	*node;
	char	*equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal = ft_strchr(env_str, '=');
	if (!equal)
	{
		node->key = ft_strdup(env_str);
		node->value = NULL;
		if (!node->key)
			return (free(node), NULL);
	}
	else
	{
		node->key = ft_substr(env_str, 0, equal - env_str);
		if (!node->key)
			return (free(node), NULL);
		node->value = ft_strdup(equal + 1);
		if (!node->value)
			return (free(node->key), free(node), NULL);
	}
	return (node->is_show = VISIBLE, node->next = NULL, node);
}

t_env	*init_env(char *envp[])
{
	int		i;
	t_env	*env_list;
	t_env	*new_node;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		new_node = init_env_node(envp[i]);
		if (!new_node)
		{
			return (free_env_list(env_list), NULL);
		}
		env_add_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env;
	int		status;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
	{
		ft_putstr_fd("Error: init_env failed\n", 2);
		return (1);
	}
	if (!init_signal_handlers())
	{
		ft_putstr_fd("Error: init_signal_handlers failed\n", 2);
		free_env_list(env);
		return (1);
	}
	status = run_repl(env);
	free_env_list(env);
	return (status);
}
