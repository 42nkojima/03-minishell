/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:48:38 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/24 17:17:02 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPL_H
# define REPL_H
# define _GNU_SOURCE

# include "types.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
#include <termios.h>

t_bool	run_repl(void);
void	sigint_handler(int signo);
t_bool assign_signal_handler(int signum, void (*handler)(int), int flags);
void setup_terminal(void);
void restore_terminal(void);

#endif // REPL_H
