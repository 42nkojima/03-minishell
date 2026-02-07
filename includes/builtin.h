/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:11:17 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/07 11:29:41 by tshimizu         ###   ########.fr       */
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

void				set_env(t_env **env, char *key, char *value);
void				env_add_back(t_env **list, t_env *new_node);
char				*get_env_value(t_env *env, char *key);
int					builtin_echo(char **argv);
int					builtin_pwd(void);
int					builtin_cd(char **argv, t_env **env);
t_exit_status		builtin_env(char **argv, t_env *env);

#endif // BUILTIN_H
