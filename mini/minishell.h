/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:41:43 by ybahij            #+#    #+#             */
/*   Updated: 2023/11/16 23:26:42 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE 1
# define REDIRECTION 2
# define HEREDOC 3
# define EXEC 4

typedef struct s_cmd
{
    int type;
}   t_cmd;

typedef struct s_redir
{
    int type;
    char *file;
    int fd;
    int mode;
    t_cmd *next;
}   t_redir;


typedef struct s_exec
{
    int type;
    char **av;
}   t_exec;

typedef struct s_pipe
{
    int type;
    t_cmd *left;
    t_cmd *right;
}   t_pipe;

typedef struct s_heredoc
{
    int type;
    char *content;
    t_cmd *next;
}   t_heredoc;

typedef struct lexer_s
{
    struct lexer_s *prev;
    char *content;
	char type;
    char    *b_appand;
    struct lexer_s *next;
}   lexer_t;

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c, int i);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char *str);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f) (unsigned int, char));
void	ft_striteri(char *s, void (*f) (unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*cm_strchr(const char *s, int c);

//------------added functions----------------//

lexer_t *ft_lstlast(lexer_t *lst);
void	ft_lstadd_back(lexer_t **lst, lexer_t *new);
lexer_t *lexer(char *input, char type);
int is_space(char c);
lexer_t *ferst_s(char *input);
int     free_list(lexer_t *head);
t_cmd *parse_pipe(lexer_t *head);
void print_tree(t_cmd *tree);
char *dellt_q_char(char *tmp);

#endif
