/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:47:13 by tshimizu          #+#    #+#             */
/*   Updated: 2026/01/31 18:24:43 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **argv, t_env *env)
{
	if (!argv[1])
	{
		while (env)
		{
			if (env->value != NULL)
				printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
		return (0);
	}
	ft_putstr_fd("env: ‘", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putstr_fd("’: No such file or directory\n", 2);
	return (127);
}
