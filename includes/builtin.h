/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:11:17 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/01 16:16:49 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef enum e_unset_type
{
	VISIBLE,
	HIDDEN,
}					t_unset_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	t_unset_type	is_show;
	struct s_env	*next;
}					t_env;

int					builtin_echo(char **argv);
int					builtin_pwd(void);
t_exit_status		builtin_env(char **argv, t_env *env);

#endif // BUILTIN_H
