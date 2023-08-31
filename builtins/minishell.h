#ifndef MINISHELL_H
# define MINISHELL_H

void builtins(int argc, char *command, char **args,/* char **envp, */t_env **env);
void echo(int argc, char **args);
void pwd();
# endif
