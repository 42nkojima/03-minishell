/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:48:38 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/16 22:46:51 by nkojima          ###   ########.fr       */
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

bool	run_repl(void);
void	sigint_handler(int signo);
bool	assign_signal_handler(int signum, void (*handler)(int), int flags);

#endif // REPL_H
