/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:47:13 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/08 15:23:54 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0&&env->is_show==VISIBLE)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node),NULL);
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (free(node->key),free(node),NULL);
	}
	else
		node->value = NULL;
	node->is_show = VISIBLE;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **list, t_env *new_node)
{
	t_env	*tmp;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	set_env(t_env **env, char *key, char *value)
{
	t_env	*cur;
	char	*new_value;
	
	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			new_value = NULL;
			if (value)
			{
				new_value = ft_strdup(value);
				if (!new_value)
					return;
			}
			free(cur->value);
			cur->value = new_value;
            cur->is_show = VISIBLE;
			return;
		}
		cur = cur->next;
	}
	env_add_back(env, new_env_node(key, value));
}

t_exit_status	builtin_env(char **argv, t_env *env)
{
	if (!argv[1])
	{
		while (env)
		{
			if (env->value != NULL&&env->is_show ==VISIBLE)
				printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
		return (EXIT_SUCCESS);
	}
	ft_putstr_fd("env: ‘", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putstr_fd("’: No such file or directory\n", 2);
	return (EXIT_CMD_NOT_FOUND);
}
