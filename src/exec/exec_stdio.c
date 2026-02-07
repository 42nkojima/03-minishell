/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stdio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:25:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/07 13:25:00 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	save_stdio_fds(int saved[2])
{
	saved[0] = dup(FD_STDIN);
	if (saved[0] == SYSCALL_ERROR)
		return (EXIT_FAILURE);
	saved[1] = dup(FD_STDOUT);
	if (saved[1] == SYSCALL_ERROR)
	{
		close(saved[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	restore_stdio_fds(int saved[2])
{
	dup2(saved[0], FD_STDIN);
	dup2(saved[1], FD_STDOUT);
	close(saved[0]);
	close(saved[1]);
}
