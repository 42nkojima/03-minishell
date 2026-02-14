/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:23:26 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/14 10:29:56 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	swap_env_content(t_env *a, t_env *b)
{
	char			*tmp_key;
	char			*tmp_value;
	t_unset_type	tmp_show;

	tmp_key = a->key;
	tmp_value = a->value;
	tmp_show = a->is_show;
	a->key = b->key;
	a->value = b->value;
	a->is_show = b->is_show;
	b->key = tmp_key;
	b->value = tmp_value;
	b->is_show = tmp_show;
	return (true);
}

bool	sort_env(t_env *env)
{
	t_env	*i;
	t_env	*j;

	i = env;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
				swap_env_content(i, j);
			j = j->next;
		}
		i = i->next;
	}
	return (true);
}

static t_env	*copy_env_node(t_env *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(env->key);
	if (!new->key)
		return (free(new), NULL);
	if (env->value)
	{
		new->value = ft_strdup(env->value);
		if (!new->value)
			return (free(new->key), free(new), NULL);
	}
	else
		new->value = NULL;
	new->is_show = env->is_show;
	new->next = NULL;
	return (new);
}

t_env	*copy_env(t_env *env)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new;

	head = NULL;
	tail = NULL;
	while (env)
	{
		new = copy_env_node(env);
		if (!new)
			return (free_env_list(head), NULL);
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		env = env->next;
	}
	return (head);
}

int	print_export(t_env *env)
{
	t_env	*copy;
	t_env	*tmp;

	copy = copy_env(env);
	if (!copy)
		return (SYSCALL_ERROR);
	sort_env(copy);
	tmp = copy;
	while (copy)
	{
		if (ft_strcmp(copy->key, "_") != 0 && copy->is_show == VISIBLE)
		{
			printf("declare -x %s", copy->key);
			if (copy->value)
				printf("=\"%s\"", copy->value);
			printf("\n");
		}
		copy = copy->next;
	}
	free_env_list(tmp);
	return (SYSCALL_SUCCESS);
}
