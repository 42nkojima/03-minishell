/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:48:38 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/08 08:55:24 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPL_H
# define REPL_H

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_prompt_status
{
	PROMPT_OK,
	PROMPT_INTERRUPT,
	PROMPT_EOF
}	t_prompt_status;

extern volatile sig_atomic_t	g_signal_status;

int		run_repl(t_env *env);
void	sigint_handler(int signo);
bool	assign_signal_handler(int signum, void (*handler)(int), int flags);

#endif // REPL_H
