/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:46:31 by nkojima           #+#    #+#             */
/*   Updated: 2025/11/29 11:20:36 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// 	struct termios	term;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

// void	restore_terminal(void)
// {
// 	struct termios	term;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag |= ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }
bool init_signal_handlers(void)
{
    if (assign_signal_handler(SIGINT, sigint_handler, SA_RESTART) == false)
        return (false);
    if (assign_signal_handler(SIGQUIT, SIG_IGN, SA_RESTART) == false)
        return (false);
    return (true);
}

int	main(void)
{
	// setup_terminal();
	if (!init_signal_handlers())
    {
		ft_putstr_fd("Error: sigint_handler assign failed\n", 2);
        return 1;
    }
	run_repl();
	// restore_terminal();
	return (0);
}
