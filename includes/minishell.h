/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:48:22 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/06 11:41:48 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "repl.h"
# include "lexical.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>


bool							init_signal_handlers(void);

void free_token_list(t_token_list *list);
void	free_split(char **arr);

#endif // MINISHELL_H
