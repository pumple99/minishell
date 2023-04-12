#ifndef MAIN_H
# define MAIN_H

#include "list.h"

void	make_hash_map(t_admin *hash_map, char *envp[], char ***new_envp);

void	make_new_envp(t_admin *hash_map, char ***envp);

void	free_double_pointer(char **pptr);

void	malloc_error(void);

#endif
