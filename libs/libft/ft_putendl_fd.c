/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:20:15 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/25 19:08:56 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Outputs the string `s` to the specified file descriptor with newline.
 *
 * Params:
 * @s: The string to output.
 * @fd: The file descriptor on which to write.
 */
void	ft_putendl_fd(char *str, int fd)
{
	if (!str)
		return ;
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
}
