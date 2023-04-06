#ifndef BUILTIN_H
# define BUILTIN_H

#include "list.h"

int		export(t_admin *hash_map, char ***envp, char **export_args);
void	env(char *envp[]);

#endif
