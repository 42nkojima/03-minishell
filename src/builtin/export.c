/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:23:10 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/15 13:22:00 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	parse_export(char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		*key = ft_strdup(arg);
		*value = NULL;
		return (*key != NULL);
	}
	*key = ft_substr(arg, 0, eq - arg);
	*value = ft_strdup(eq + 1);
	if (!*key || !*value)
	{
		free(*key);
		free(*value);
		return (0);
	}
	return (1);
}

int	export_one(char *arg, t_env **env)
{
	char	*key;
	char	*value;

	if (!parse_export(arg, &key, &value))
		return (SYSCALL_ERROR);
	if (!is_valid_identifier(key))
	{
		export_error(arg);
		free(key);
		free(value);
		return (SYSCALL_ERROR);
	}
	set_env(env, key, value);
	free(key);
	free(value);
	return (SYSCALL_SUCCESS);
}

int	builtin_export(char **argv, t_env **env)
{
	int	i;
	int	status;

	if (!argv[1])
		return (print_export(*env));
	status = SYSCALL_SUCCESS;
	i = 1;
	while (argv[i])
	{
		if (export_one(argv[i], env) != SYSCALL_SUCCESS)
			status = SYSCALL_ERROR;
		i++;
	}
	return (status);
}
