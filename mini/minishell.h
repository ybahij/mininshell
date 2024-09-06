/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:41:43 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/06 15:34:59 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PIPE 1
# define REDIRECTION 2
# define HEREDOC 3
# define EXEC 4
# define AND 5
# define OR 6

typedef struct s_cmd
{
	int					type;
}						t_cmd;

typedef struct s_redir
{
	int					type;
	char				*file;
	int					fd;
	int					mode;
	t_cmd				*next;
}						t_redir;

typedef struct s_exec
{
	int					type;
	char				**av;
}						t_exec;

typedef struct s_pipe
{
	int					type;
	t_cmd				*left;
	t_cmd				*right;
}						t_pipe;

typedef struct s_heredoc
{
	int					type;
	char				*content;
	t_cmd				*next;
}						t_heredoc;

typedef struct s_and
{
	int					type;
	t_cmd				*left;
	t_cmd				*right;
}						t_and;

typedef struct s_or
{
	int					type;
	t_cmd				*left;
	t_cmd				*right;
}						t_or;

typedef struct lexer_s
{
	struct lexer_s		*prev;
	char				*content;
	char				type;
	char				*b_appand;
	struct lexer_s		*next;
}						lexer_t;

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
}						t_garbage;

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

int						ft_isdigit(int c);
int						ft_isalnum(int c);
size_t					ft_strlen(const char *s);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
char					*ft_strrchr(const char *s, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					*ft_calloc(size_t count, size_t size);
char					*ft_strdup(const char *s1);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char *s1, char *s2);
char					**ft_split(char *str);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*cm_strchr(const char *s, int c);

//------------added functions----------------//

lexer_t					*ft_lstlast(lexer_t *lst);
void					ft_lstadd_back(lexer_t **lst, lexer_t *new);
lexer_t					*lexer(char *input, char type);
int						is_space(char c);
lexer_t					*ferst_s(char *input);
int						free_list(lexer_t *head);
void					print_tree(t_cmd *tree);
char					*dellt_q_char(char *tmp);
char					*cheak_env(char *str, char **env);
int						qoute(int *k, char *input, lexer_t **head);
void					free_digit(char *input, int k, int j, lexer_t **g_head);
int						cheak_digit(char *input, int *i);
int						redir_o(char *input, int *j, lexer_t **head);
int						redir_i(char *input, int *j, lexer_t **head);
int						redir(char *input, int *i, lexer_t **head);
int						r_pipe(char *input, int *j, lexer_t **head);
int						cmd_lexer(char *input, int *j, lexer_t **head, char t,
							int i);
int						n_cmd(char *input, int *j, lexer_t **head);
int						and_or(char *input, int *i, lexer_t **head);
int						pars_quote(char *content);
int						pars_(lexer_t *tmp, char *newline);
void					count_herdoc(lexer_t *tmp);
char					*quote_(char *content);
char					*herdoc_appand(char *content, char type, char **g_env);
int						heandal_herdoc(lexer_t *tmp, char **g_env);
int						cmd_syntax(lexer_t *tmp, char **g_env, char *newline,
							lexer_t *tmp2);
void					free_(lexer_t *cmd);
int						appand_in_fille(lexer_t *cmd, int fd, char **env,
							char hold);
void					free_array(char **str);
int						expand_w(lexer_t *cmd, char **env);
int						expand(lexer_t *cmd, char **env);
char					*dellt_q(lexer_t *cmd, int i);
int						del_quote(lexer_t *cmd);
lexer_t					*split_1(lexer_t *head, char **str, int i);
lexer_t					*spilt_(lexer_t *head, int i);
int						split_cmd(lexer_t *head);
int						get_cmd_len(lexer_t *token);
char					**get_cmd_args(lexer_t *token);
t_cmd					*parse_cmd(lexer_t *token);
void					handle_redirection(t_redir *redir, lexer_t *token);
t_cmd					*herdoc_construct(lexer_t *token, lexer_t *head,
							char **env);
t_cmd					*redir_construct(lexer_t *token, lexer_t *head,
							char **env);
t_cmd					*parse_redir(lexer_t *head, char **env);
t_cmd					*parse_pipe(lexer_t *head, char **env);
t_cmd					*parse_or(lexer_t *head, char **env);
t_cmd					*parse_and(lexer_t *head, char **env);
lexer_t					*peek(lexer_t *head, char type);
int						appand_u(int *j, int i, lexer_t *cmd, int fd,
							char **env);
char					*herdoc_appand1(char *content, char **g_env, char *str,
							int *i);
int						syntax_error_(lexer_t *tmp, char **g_env,
							char *newline);
lexer_t					*syntax_error(lexer_t *tmp, char **g_env,
							char *newline);
int						pars_pipe_(lexer_t *tmp, char *newline);
int						parenthesis(char *input, int *i, lexer_t **head);
void					free_garbage(void);
void					add_garbage(void *content);
void					*ft_malloc(size_t size);
void					free_g(t_garbage *head);
int						pars_parenthesis(lexer_t *tmp, char **g_env);
t_cmd					*parenthesis_c(lexer_t *head, char **env);
int						token_cmd(char *line, lexer_t **cmd, char **env,
							char *newline);
char					*remaove_parenthesis(char *content);

#endif
