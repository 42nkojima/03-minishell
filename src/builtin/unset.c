#include "minishell.h"


int	env_remove(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			env->is_show = HIDDEN;
			return SYSCALL_SUCCESS;
		}
		env = env->next;
	}
    return SYSCALL_SUCCESS;
}


int	builtin_unset(char **argv, t_env **env)
{
	int	status;

	status = 0;
    if (!is_valid_identifier(argv[1]))
    {
        ft_putstr_fd("minishell: unset: `", 2);
        ft_putstr_fd(argv[1], 2);
        ft_putendl_fd("': not a valid identifier", 2);
        status = 1;
    }
    else
    {
        env_remove(*env, argv[1]);
    }
	return (status);
}
