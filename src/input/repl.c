/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:44:57 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/29 11:19:52 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_interrupt = 1;

int	noop(void)
{
	return (0);
}

bool	run_repl(void)
{
	char	*input;

	rl_event_hook = noop;
	while (TRUE)
	{
		g_interrupt = 0;
		input = readline("minishell$ ");
		if (g_interrupt)
		{
			free(input);
			continue ;
		}
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		free(input);
	}
	return (true);
}

void	sigint_handler(int signo)
{
	(void)signo;
	g_interrupt = 1;
	rl_done = 1;
}

bool assign_signal_handler(int signum, void (*handler)(int), int flags)
{
	struct sigaction	sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handler;
    sa.sa_flags = flags;

    if (sigaction(signum, &sa, NULL) == -1)
    {
        perror("Error setting up sigaction");
        return false;
    }
    return true;
}

void setup_terminal(void)
{
   struct termios term;

   tcgetattr(STDIN_FILENO, &term);
   term.c_lflag &= ~ECHOCTL;
   tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void restore_terminal(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
