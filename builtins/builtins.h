#ifndef BUILTILNS_H
# define BUILTILNS_H
# include "builtin_utils.h"

void	echo(int argc, char **args);
void	cd(int argc, char *arg);
void	my_exit(char *arg);
void	export(int argc, char **argv, t_env **env);
void	unset(int argc, char **args, t_env **env);
void	append_to_env(t_env **env, char *value);
void	edit_env(t_env *node, char *value);
void	env_(t_env **env);
void	pwd();
#endif
