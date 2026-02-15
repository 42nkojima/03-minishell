/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:20:45 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/15 13:31:47 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_visible_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->is_show == VISIBLE && env->value != NULL)
			count++;
		env = env->next;
	}
	return (count);
}

static char	*env_to_entry(t_env *cur)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin("=", cur->value);
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(cur->key, tmp);
	free(tmp);
	return (entry);
}

char	**env_to_array(t_env *env)
{
	char	**envp;
	t_env	*cur;
	int		i;

	envp = malloc(sizeof(char *) * (count_visible_env(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	cur = env;
	while (cur)
	{
		if (cur->is_show == VISIBLE && cur->value != NULL)
		{
			envp[i] = env_to_entry(cur);
			if (!envp[i])
				return (envp[i] = NULL, free_envp(envp), NULL);
			i++;
		}
		cur = cur->next;
	}
	envp[i] = NULL;
	return (envp);
}
