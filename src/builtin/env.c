/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:47:13 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/01 15:11:58 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit_status	builtin_env(char **argv, t_env *env)
{
	if (!argv[1])
	{
		while (env)
		{
			if (env->value != NULL)
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
