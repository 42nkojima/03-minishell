#include "minishell.h"


static int count_visible_env(t_env *env)
{
    int count = 0;
    while (env)
    {
        if (env->is_show == VISIBLE)
            count++;
        env = env->next;
    }
    return count;
}



char **env_to_array(t_env *env)
{
    char **envp;
    char *val;
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
        if (cur->is_show == VISIBLE)
        {
            if (!cur->value) {
                val = "";
            }else{
                val = cur->value;
            }
            char *tmp = ft_strjoin("=", val);
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

