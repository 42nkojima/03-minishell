/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:23:29 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/15 13:23:32 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_remove(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			free(env->value);
			env->value = NULL;
			env->is_show = HIDDEN;
			return (SYSCALL_SUCCESS);
		}
		env = env->next;
	}
	return (SYSCALL_SUCCESS);
}

int	builtin_unset(char **argv, t_env **env)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
			env_remove(*env, argv[i]);
		i++;
	}
	return (status);
}
