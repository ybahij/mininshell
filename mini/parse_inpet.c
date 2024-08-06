#include "libft.h"

int    parse_quote(char *av)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

        while (av[i])
        {
            if (av[i] == '"' )
            {
                i++;
                while (av[i] && av[i] != '"' )
                    i++;
                if (av[i] != '"' )
                    return(printf("Error:syntax error\n"), 0);
            }
            if (av[i] == '\'' )
            {
                i++;
                while (av[i] && av[i] != '\'' )
                    i++;
                if (av[i] != '\'' )
                    return(printf("Error:syntax error\n"), 0);
            }
            i++;
        }
        return (1);
}

int    cheak_apipe(char *av, int i)
{
    i++;
    while (av[i])
    {
        if ((av[i] != '\t' && av[i] != ' ' && av[i] != '\n' && av[i] != '\v' && av[i] != '\f' && av[i] != '\r'))
            return (1);
        i++;
    }
    return (0);
}

int    cheak_bpipe(char *av, int i)
{
    int j = 0;

    while (j < i)
    {
        if ((av[j] != '\t' && av[j] != ' ' && av[j] != '\n' && av[j] != '\v' && av[j] != '\f' && av[j] != '\r'))
            return (1);
        j++;
    }
    return (0);
}

int    parse_pipe(char *av)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    while (av[i] &&( (av[i] <= 13 && av[i] >= 9) || av[i] == ' '))
        i++;
    while (av[i])
    {
        if (av[i] == '|' )
        {
            if (i == 0)
                return(printf("Error:syntax error\n"), 0);
            if (!cheak_bpipe(av, i) )
                return(printf("Error:syntax error\n"), 0);
            if (!cheak_apipe(av, i))
                return(printf("Error:syntax error\n"), 0);

        }
        i++;
    }
    return (1);
}

int pars_her_doc(char *av, int *i)
{
    while (av[*i] && av[*i] != '\n')
    {
        while (av[*i] && av[*i] == ' ' || av[*i] == '\t' || av[*i] == '\v' || av[*i] == '\f' || av[*i] == '\r')
            (*i)++;
        if (av[*i] == '|' || av[*i] == '<' || av[*i] == '>')
            return(printf("Error:syntax error\n"), 0);
        else if (av[*i] != '\n')
            return (1);
        (*i)++;
    }
    return (printf("Error:syntax error\n"), 0);
}

int    cheak_ar(char *av, int i)
{
    while (av[i])
    {
        if ((av[i] != '\t' && av[i] != ' ' && av[i] != '\n'
                && av[i] != '\v' && av[i] != '\f' && av[i] != '\r'
                    && av[i] != '|' && av[i] != '<' && av[i] != '>'))
            return (1);
        i++;
    }
    return (0);
}

int parse_redirection(char *av)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    while (av[i] &&( (av[i] <= 13 && av[i] >= 9) || av[i] == ' '))
        i++;
    while (av[i])
    {
        if (av[i] == '>' )
        {
            i++;
            if  (av[i] == '>')
                i++;
            while (av[i] &&( (av[i] <= 13 && av[i] >= 9) || av[i] == ' '))
                i++;
            if (!cheak_ar(av, i))
                return(printf("Error:syntax error\n"), 0);
            if ((av[i] == '"' && av[i + 1] == '"') || (av[i] == '\'' && av[i + 1] == '\''))
                return(printf("Error: :No such file or directory\n"), 0);

            if (av[i] == '\0')
                return(printf("Error:syntax error\n"), 0);
            if (av[i] == '|' || av[i] == '<' || av[i] == '>')
                return(printf("Error:syntax error\n"), 0);
        }
        if (av[i] == '<' )
        {
            i++;
            if (av[i] == '<')
            {
                i++;
                if (!pars_her_doc(av, &i))
                    return (0);
            }
            while (av[i] &&( (av[i] <= 13 && av[i] >= 9) || av[i] == ' '))
                i++;
            if (!cheak_ar(av, i))
                return(printf("Error:syntax error\n"), 0);
            if  ((av[i] == '"' && av[i + 1] == '"') || (av[i] == '\'' && av[i + 1] == '\''))
                return(printf("Error: :No such file or directory\n"), 0);

            if (av[i] == '\0')
                return(printf("Error:syntax error\n"), 0);
            if (av[i] == '|' || av[i] == '<' || av[i] == '>')
                return(printf("Error:syntax error\n"), 0);
        }
        i++;
    }
    return (1);
}

int    parse_cmd(char *av)
{
    if (!parse_quote(av))
        return (free(av), 0);
    if (!parse_pipe(av))
        return (free(av), 0);
    if (!parse_redirection(av))
        return (free(av), 0);
    return (1);
}


char *ft_strncpy(char *s1, char *s2, int n)
{
	int i = -1;

	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

// char	**ft_split(char *str, char c)
// {
// 	int i = 0;
// 	int j = 0;
// 	int k = 0;
// 	int wc = 0;

// 	while (str[i])
// 	{
// 		while (str[i] && (str[i] == c))
// 			i++;
// 		if (str[i])
// 			wc++;
// 		while (str[i] && (str[i] != c))
// 			i++;
// 	}

// 	char **out = (char **)malloc(sizeof(char *) * (wc + 1));
// 	i = 0;

// 	while (str[i])
// 	{
// 		while (str[i] && (str[i] == c))
// 			i++;
// 		j = i;
// 		while (str[i] && (str[i] != c))
// 			i++;
// 		if (i > j)
// 		{
// 			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
// 			ft_strncpy(out[k++], &str[j], i - j);
// 		}
// 	}
// 	out[k] = NULL;
// 	return (out);
// }

// cmd_t **split_cmd(char *av)
// {
//     int i = 0;
//     char **cmd_line = NULL;
//     cmd_line = ft_split(av, '|');
//     while (cmd_line[i])
//         i++;
//     cmd_t **cmd = (cmd_t **)malloc(sizeof(cmd_t *) * (i + 1));
//     i = 0;
// }

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    lexer_t *cmd;
    lexer_t *tmp;
    int i = 0;

    while(1)
    {
        line = readline("mysh> ");
        // if (!parse_cmd(line))
        //     i = 1;
        if (i == 0)
        {
            cmd = ferst_s(line);
            while (cmd)
            {
                tmp = cmd->next;
                printf("cmd->content = [%s] = ", cmd->content);
                printf("cmd->type = %c\n", cmd->type);
                free(cmd);
                cmd = tmp;
            }
            free(line);
        }
    }
    return (0);
}