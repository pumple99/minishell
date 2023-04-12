#ifndef BUILTIN_H
# define BUILTIN_H

#include "list.h"

void	builtin_env(char *envp[]);
int		builtin_export(t_admin *hash_map, char ***envp, char **export_args);
int		builtin_unset(t_admin *hash_map, char ***envp, char **args);
int		builtin_exit(char **args);
int		builtin_cd(t_admin *hash_map, char ***envp, char **args);
int		builtin_pwd(t_admin *hash_map);
int		builtin_echo(char **args);

#endif
