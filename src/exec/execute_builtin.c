/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:16:58 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/01 15:59:53 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin_command(t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (false);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (true);
	return (false);
}

int	execute_builtin_command(t_command *cmd, t_env **env)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(cmd->argv, *env));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (1);
}
