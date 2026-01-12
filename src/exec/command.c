/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by nkojima           #+#    #+#             */
/*   Updated: 2025/12/14 20:33:19 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../libs/libft/libft.h"
#include <stdlib.h>

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*build_path(char *dir, char *cmd)
{
	char	*slash;
	char	*path;

	slash = ft_strjoin(dir, "/");
	if (!slash)
		return (NULL);
	path = ft_strjoin(slash, cmd);
	free(slash);
	return (path);
}

static char	*check_executable(char *path)
{
	char	*dup;

	if (access(path, F_OK) == SYSCALL_ERROR)
		return (NULL);
	if (access(path, X_OK) == SYSCALL_ERROR)
		return (NULL);
	dup = ft_strdup(path);
	return (dup);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == SYSCALL_SUCCESS)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/*
** Find command path from PATH environment variable
** @param cmd: Command name (e.g. "ls")
** @param envp: Environment variables array
** @return: Full path to command (e.g. "/bin/ls"), or NULL if not found
*/
char	*find_command(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (ft_strchr(cmd, '/'))
		return (check_executable(cmd));
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	free_split(paths);
	return (result);
}
