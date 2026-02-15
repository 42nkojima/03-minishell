#include "minishell.h"


static int count_visible_env(t_env *env)
{
    int count = 0;
    while (env)
    {
        if (env->is_show == VISIBLE && env->value != NULL)
            count++;
        env = env->next;
    }
    return count;
}



char **env_to_array(t_env *env)
{
    char **envp;
    t_env *cur;
    int count;
    int i;

    count = count_visible_env(env);
    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return NULL;

    i = 0;
    cur = env;
    while (cur)
    {
        if (cur->is_show == VISIBLE && cur->value != NULL)
        {
            char *tmp = ft_strjoin("=", cur->value);
            if (!tmp)
            {
                envp[i] = NULL;
                free_envp(envp);
                return (NULL);
            }
            envp[i] = ft_strjoin(cur->key, tmp);
            free(tmp);
            if (!envp[i])
            {
                envp[i] = NULL;
                free_envp(envp);
                return (NULL);
            }            
            i++;
        }
        cur = cur->next;
    }
    envp[i] = NULL;
    return envp;
}

