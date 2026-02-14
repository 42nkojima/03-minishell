/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 11:18:49 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/07 11:50:44 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pwd_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0&&env->is_show==VISIBLE)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_cd_target(char **argv, t_env *env)
{
	if (!argv[1])
		return (get_pwd_value(env, "HOME"));
	if (ft_strcmp(argv[1], "-") == 0)
		return (get_pwd_value(env, "OLDPWD"));
	return (argv[1]);
}

int	cd_error_not_set(char *name)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(" not set", 2);
	return (1);
}

void	update_pwd(t_env **env, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		set_env(env, "OLDPWD", oldpwd);
		set_env(env, "PWD", newpwd);
		free(newpwd);
	}
}

int	builtin_cd(char **argv, t_env **env)
{
	char	*target;
	char	*oldpwd;

	target = get_cd_target(argv, *env);
	if (!target)
	{
		if (argv[1])
			return (cd_error_not_set("OLDPWD"));
		return (cd_error_not_set("HOME"));
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		free(oldpwd);
		return (1);
	}
	update_pwd(env, oldpwd);
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		ft_putendl_fd(get_env_value(*env, "PWD"), 1);
	free(oldpwd);
	return (0);
}
