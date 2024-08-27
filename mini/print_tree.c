
#include "minishell.h"

void print_tree(t_cmd *tree)
{
  t_pipe *pipe;
  t_exec *exec;
  t_redir *redir;
  t_heredoc *heredoc;


    if (tree->type == AND)
    {
      t_and *and = (t_and *)tree;
      printf("AND\n");
      printf("________LEFT\n");
      print_tree(and->left);
      printf("________RIGHT\n");
      print_tree(and->right);
    }
    else if (tree->type == OR)
    {
      t_or *or = (t_or *)tree;
      printf("OR\n");
      printf("________LEFT\n");
      print_tree(or->left);
      printf("________RIGHT\n");
      print_tree(or->right);
    }
    else if (tree->type == PIPE)
    {
      pipe = (t_pipe *)tree;
      printf("PIPE\n");
      printf("________LEFT\n");
      print_tree(pipe->left);
      printf("________RIGHT\n");
      print_tree(pipe->right);
    }
    else if (tree->type == REDIRECTION)
    {
      redir = (t_redir *)tree;
      printf("REDIRECTION\n");
      printf("file: %s\n", redir->file);
      printf("fd: %d\n", redir->fd);
      printf("mode: %d\n", redir->mode);
      print_tree(redir->next);
    }
    else if (tree->type == HEREDOC)
    {
      heredoc = (t_heredoc *)tree;
      printf("HEREDOC\n");
      printf("content: %s\n", heredoc->content);
      print_tree(heredoc->next);
    }
    else if (tree->type == EXEC)
    {
      exec = (t_exec *)tree;
      printf("EXEC\n");
      int i = 0;
      while (exec->av[i])
      {
        printf("av[%d]: %s\n", i, exec->av[i]);
        i++;
      }
    }
}