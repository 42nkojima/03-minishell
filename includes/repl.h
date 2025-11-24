/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:48:38 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/24 13:21:32 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPL_H
# define REPL_H

# include <stdio.h>
# include <stdlib.h>
# include "types.h"
# include <readline/history.h>
# include <readline/readline.h>

t_bool	run_repl(void);

#endif // REPL_H
