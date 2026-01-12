/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:48:38 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/06 16:43:08 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPL_H
# define REPL_H
# define _GNU_SOURCE

# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
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
