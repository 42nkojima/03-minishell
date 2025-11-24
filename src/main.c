/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:46:31 by nkojima           #+#    #+#             */
/*   Updated: 2025/11/29 11:13:08 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	setup_terminal();
	if (assign_signal_handler(SIGINT, sigint_handler, 0) == 0)
    {
		ft_putstr_fd("Error: sigint_handler assign failed\n", 2);
        return 1;
    }
	run_repl();
	restore_terminal();
	return (0);
}
