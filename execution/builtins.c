#include "../minishell.h"

extern t_global g_data;

void    ft_cd(char **av)
{
    int i;
    char tmp[1000];
    char *holder;
    i = 0;
    while (av[i])
        i++;
    if (i > 2)
    {
        printf("too many arguments\n");
        exit_s(1);
        return;
    }
    if (av[1] == NULL)
    {
        if (chdir(ft_get_env("HOME", *get_env())) == -1)
        {
            perror("cd");
            exit_s(1);
        }
        else
        {
            g_data.pwd = ft_strdup(ft_get_env("HOME", *get_env()));
            exit_s(0);
        }
    }
    else if (chdir(av[1]) == -1)
    {
        printf("minishell: cd: %s: No such file or directory\n", av[1]);
        // perror("cd");
        exit_s(1);
    }
    else
    {  
        g_data.oldpwd = ft_strdup(g_data.pwd);
        holder = getcwd(NULL, 0);
        g_data.pwd = ft_strdup(holder);
        free(holder);
        exit_s(0);
    }
}

int    check_n(char **av, int *i)
{
    int j;

    while (av[*i] && ft_strncmp(av[*i], "-n", 2) == 0)
    {
        j = 1;
        while (av[*i][j] == 'n')
            j++;
        if (av[*i][j] == '\0')
            (*i)++;
        else
            break;
    }
    return (0);
}

int check_nbr_n(char **av)
{
    int j;

    j = 1;
    if (av[1][0] == '-')
    {
        while (av[1][j] == 'n')
            j++;
        if (av[1][j] == '\0')
            return (1);
    }
    return (0);
}

void    ft_echo(char **av)
{
    int i;

    i = 1;
    check_n(av, &i);
    while (av[i])
    {
        ft_putstr(av[i]);
        if (av[i + 1])
            ft_putstr(" ");
        i++;
    }
    if (check_nbr_n(av) == 0)
    {
        ft_putstr("\n");
        exit_s(0);
    }
    else
        exit_s(0);
}

char	*cm_strdup(const char *s1)
{
	int		i;
	char	*dest;

	if (!s1)
		return (ft_strdup(""));
	dest = ft_malloc((ft_strlen(s1) + 1) * 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest [i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void    ft_pwd(void)
{
    // static char    *cwd;
    // static char     *old_wd;
    // char            *holder;

    // if (cwd != NULL)
    // {
    //     old_wd = cm_strdup(cwd);
    //     cwd = NULL;
    // }
    // holder = getcwd(NULL, 0);
    // printf(">>: %s\n", holder);
    // if (holder == NULL)
    //     cwd = NULL;
    // else
    //     cwd = cm_strdup(holder);
    // free(holder);
    // if (cwd != NULL)
    // {
    //     printf("%s\n", cwd);
    //     exit_s(0);
    // }
    // else if (old_wd != NULL)
    // {
    //     printf("%s\n", old_wd);
    //     exit_s(0);
    // }
    printf("%s\n", g_data.pwd);
}

char **sorting(char **str)
{
    int i = 0;
    int j;
    char *tmp;

    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (ft_strcmp(str[i], str[j]) > 0)
            {
                tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
            }
            j++;
        }
        i++;
    }
    return str;
}

int    check_valid_arg(char *av)
{
    int i;

    i = 1;
    if (ft_is_alpha(av[0]) == 0 && av[0] != '_')
    	return (1);
    while (av[i] != '\0' && av[i] != '=' && av[i] != '+')
    {
        if (ft_is_alpha(av[i]) == 0 && ft_isdigit(av[i]) == 0 && av[i] != '_')
            return (1);
        i++;
    }
    if (av[i] == '+' && av[i + 1] != '=')
        return (1);
    return (0);
}

int compaire(char *str1, char *str2)
{
    int i;

    i = 0;

    while (str1[i] && str2[i] && str1[i] != '=' && str2[i] != '=' && str2[i] != '+')
    {
        if (str1[i] != str2[i])
            break ;
        i++;
    }
    if ((str1[i] == '\0' || str1[i] == '=' || str1[i] == '+') && (str2[i] == '\0' || str2[i] == '=' || str2[i] == '+'))
            return (0);
    else
        return (1);
}

int already_exist(char *str)
{
    char    **env;
    int i;

    env = *get_env();
    i = 0;
    while (env[i])
    {
        if (compaire(env[i], str) == 0)
        {
            return (i);
        }
            // printf("i = %d\n", i);
        i++;
    }
    return (-1);
}


int count_valid_av(char **av)
{
    int i;
    int count;

    i = 1;
    count = 0;
    // exist_arg(av);
    while (av[i])
    {
        if (check_valid_arg(av[i]) == 0 && already_exist(av[i]) == -1)
			count++;
		i++;
    }
    return (count);
}

int check_sign(char *av)
{
    int i;

    i = 0;
    while (av[i])
    {
        if (av[i] == '=')
            return (1);
        else if (av[i] == '+' && av[i + 1] == '=')
            return (0);
        i++;
    }
    return (-1);
}

char    **get_new_env(char **av, char **env)
{
    int i;
    int j;
    char **new_env;
    int count;
    int temp;
    int index;
    char    *holder;

    count = count_valid_av(av);
    new_env = ft_malloc(sizeof(char *) * (dblptr_len(env) + count + 1));
    i = 0;
    while (env[i])
    {
        new_env[i] = cm_strdup(env[i]);
        i++;
    }
    j = 1;
    while (av[j])
    {
        if (check_valid_arg(av[j]) == 1)
		{
            printf("export: `%s': not a valid identifier\n", av[j]);
			j++;
            continue ;
		}
        temp = already_exist(av[j]);
        // printf("im here\n");
        if (temp != -1)
        {

            if (check_sign(av[j]) == 1)
            {
                new_env[temp] = cm_strdup(av[j++]);
            }
            else if (check_sign(av[j]) == 0)
            {
                index = 0;
                while (av[j][index] != '=')
                    index++;
                if (cm_strchr(new_env[temp], '=') == NULL)
                {
                    holder = new_env[temp];
                    new_env[temp] = ft_ft_strjoin(new_env[temp], "=");
                }
                holder = new_env[temp];
                new_env[temp] = ft_ft_strjoin(new_env[temp], &av[j++][index + 1]);
            }
            else
                j++;
        }
        else
        {
            if (check_sign(av[j]) == 0)
            {
                index = 0;
                while (av[j][index] != '+')
                    index++;
                while (av[j][index])
                {
                    av[j][index] = av[j][index + 1];
                    index++;
                }
            }
            new_env[i++] = cm_strdup(av[j++]);
            new_env[i] = NULL;
            *get_env() = new_env;
        }
    }
	new_env[i] = NULL;
    return (new_env);
}

// void    ft_delenv(int index, char **env)
// {
//     int i;
//     int j;
//     char    **new_env;

//     i = 0;
//     j = 0;
//     new_env = ft_malloc(sizeof(char *) * (dblptr_len(env)));
//     // printf("dblptr_len(env) = %d\n", dblptr_len(env));
//     // printf("index = %d\n", index);
//     // printf("env[index] = %s\n", env[index]);
//     // printf("env[index + 1] = %s\n", env[index + 1]);
//     while (i < index)
//     {
//         new_env[j] = cm_strdup(env[i]);
//         i++;
//         j++;
//     }
//     i++;
//     while (env[i])
//     {
//         new_env[j] = cm_strdup(env[i]);
//         i++;
//         j++;
//     }
//     new_env[j] = NULL;
//     *get_env() = new_env;
//      i = 0;
//     while (new_env[i])
//     {
//         printf("new_env[%d] = %s\n", i, new_env[i]);
//         i++;
//     }
// }

// void    check_dupli(char **env)
// {
//     int i;
//     int j;
//     int index;
//     // char    *holder;

//     i = 0;
//     while (env[i])
//     {
//         j = i + 1;
//         while (env[j])
//         {
//             index = 0;
//             while (env[i][index] == env[j][index] && ((env[i][index] != '\0' && env[j][index] != '=') || (env[i][index] != '=' && env[j][index] != '=') || (env[i][index] != '=' && env[j][index] != '\0')))
//                 index++;
//             if ((env[i][index] == '\0' && env[j][index] == '=') || (env[i][index] == '=' && env[j][index] == '='))
//             {
//                 printf("i = %d\n", i);
//                 ft_delenv(i, env);
//             }
//             j++;
//         }
//         i++;
//     }
// }

void    ft_export(char **av, char **env)
{
    int i;
    int j;
    char    **copy_env;

    i = 0;
    if (av[1] == NULL)
    {
        int flag;
        // copy_env = check_dupli(env);
        copy_env = get_copy_with_malloc(env);
        sorting(copy_env);
        while (copy_env[i])
        {
            j = 0;
            flag = 0;
            write(1, "declare -x ", 11);
            while (copy_env[i][j])
            {
                write(1, &copy_env[i][j], 1);
                if (copy_env[i][j] == '=' && flag == 0)
                {
                    flag = 1;
                    write(1, "\"", 1);
                }
                j++;
            }
            if (flag == 1)
                write(1, "\"", 1);
            write(1, "\n", 1);
            i++;
        }
        // cm_free(copy_env);
    }
    else
    {
        copy_env = get_new_env(av, env);
        // cm_free(env);
		//TODO: dbl_free(env);
        *get_env() = copy_env;
    }
    // check_dupli(env);
}

void    ft_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
    exit_s(0);
}


int check_exist(char **av, char **env)
{
    int i;
    int j;
    int index;
    int count;

    count = 0;
    i = 1;
    index = 0;
    while (av[i])
    {
        j = 0;
        index = 0;
        while (env[j])
        {
            // printf ("av[1] = %s\n", av[i]);
            while ((av[i][index] == env[j][index]) && (av[i][index] && env[j][index]))
                index++;
            // printf ("env[j] = %s\n", env[j]);
            if ((av[i][index] == '\0' && env[j][index] == '=') || (av[i][index] == '\0' && env[j][index] == '\0'))
            {
                count++;
                break ;
            }
            j++;

        }
        i++;
    }
    return (count);
}

int c_for_unset(char **av, char *env)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (env[j] != '=' && av[i][j] != '\0' && av[i][j] == env[j])
            j++;
        if ((av[i][j] == '\0' && env[j] == '=') || (av[i][j] == '\0' && env[j] == '\0'))
            return (0);
        i++;
    }
    return (1);
}


void    ft_unset(char **av, char **env)
{
    int i;
    int j;
    int counter;
    char **new_env;

    counter = check_exist(av, env);
    // printf("counter = %d\n", counter);
    new_env = ft_malloc(sizeof(char *) * (dblptr_len(env) - (counter) + 1));
    i = 0;
    j = 0;
    while (env[i])
    {
        if (c_for_unset(av, env[i]) == 1)
        {
            new_env[j] = cm_strdup(env[i]);
            j++;
            i++;
        }
        else
            i++;
        // printf("new_env[j] = %s\n", new_env[j]);
    }
    new_env[j] = NULL;
    *get_env() = new_env;
}

int str_digit(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

long long    ft_atoll(const char *str)
{
    long long    res;
    int                    sign;
    int                    i;

    i = 0;
    res = 0;
    sign = 1;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    if (str[i] == '+')
        i++;
    while (str[i])
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res * sign);
}

void    ft_exit(char **av)
{
    char    **str;
    long long   res;

    res = 0;
    str = NULL;
    if (!av[1])
        exit(ret_status());
    if (av[2] == NULL)
    {
        str = ft_split(av[1]);
        if (str_digit(av[1]) == 0 && str[1] == NULL && (ft_atoll(str[0]) < LLONG_MAX && ft_atoll(str[0]) > LLONG_MIN))
        {
            res = ft_atoll(str[0]);
            free_g();
            printf("exit\n");
            exit(res);
        }
        else
        {    
            printf("exit\nminishell: exit: %s: numeric argument required\n", av[1]);
            exit(2);
        }
    }
    else 
    {
        if (str_digit(av[1]) == 0 && str_digit(av[2]) == 0)
        {
            printf("exit\nminishell: exit: too many arguments\n");
            exit_s(1);
            return ;
        }
        else if ( str_digit(av[1]) == 0 && str_digit(av[2]) == 1)
        {
            printf("exit\nminishell: exit: too many arguments\n");
            exit_s(1);
            return ;
        }
        else if (str_digit(av[1]) == 1 && str_digit(av[2]) == 0)
        {
            printf("exit\nminishell: exit: %s: numeric argument required\n", av[1]);
            exit(2);
        }
        else
        {
            printf("exit\nminishell: exit: %s: numeric argument required\n", av[1]);
            exit(2);
        }
    }

}

int    builtins(t_exec *exec, char **env)
{
        if (ft_strcmp(exec->av[0], "cd") == 0)
            ft_cd(exec->av);
        else if (ft_strcmp(exec->av[0], "echo") == 0)
            ft_echo(exec->av);
        else if (ft_strcmp(exec->av[0], "pwd") == 0)
            ft_pwd();
        else if (ft_strcmp(exec->av[0], "export") == 0)
            ft_export(exec->av, env);
        else if (ft_strcmp(exec->av[0], "unset") == 0)
            ft_unset(exec->av, env);
        else if (ft_strcmp(exec->av[0], "env") == 0)
            ft_env(env);
        else if (ft_strcmp(exec->av[0], "exit") == 0)
            ft_exit(exec->av);
        else
            return (0);
    return (1);
}

