/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:20:39 by tshimizu          #+#    #+#             */
/*   Updated: 2026/01/24 11:14:07 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int builtin_pwd()
{
    char *cwd;

	cwd = getcwd(NULL,0);
    if (!cwd)
    {
        perror("pwd");
        return (1);
    }
    printf("%s\n", cwd);
	free(cwd);
    return (0);
}
