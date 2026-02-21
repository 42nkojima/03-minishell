/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:44:59 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/10 17:18:28 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_too_many_args(char **argv)
{
	return (argv[2] != NULL);
}

static void	print_numeric_argument_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", FD_STDERR);
	ft_putstr_fd(arg, FD_STDERR);
	ft_putendl_fd(": numeric argument required", FD_STDERR);
}

static int	print_too_many_arguments_error(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", FD_STDERR);
	return (EXIT_FAILURE);
}

int	builtin_exit(char **argv)
{
	long long	code;

	ft_putendl_fd("exit", FD_STDERR);
	if (!argv[1])
		return (EXIT_FLAG | EXIT_SUCCESS);
	if (!validate_str_to_ll(argv[1], &code))
	{
		print_numeric_argument_error(argv[1]);
		return (EXIT_FLAG | EXIT_BUILTIN_MISUSE);
	}
	if (has_too_many_args(argv))
		return (print_too_many_arguments_error());
	return (EXIT_FLAG | (unsigned char)code);
}
