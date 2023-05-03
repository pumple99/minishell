# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 15:20:31 by seunghoy          #+#    #+#              #
#    Updated: 2023/05/03 17:09:35 by seunghoy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CC := cc
CFLAGS := #-Werror -Wall -Wextra
LDFLAGS := -lreadline -L/opt/homebrew/opt/readline/lib
DEBUG_FLAGS := -g -fsanitize=address
LIB := libft.a
LIB_DIR := libft
SRCS_DIR := srcs
INCLUDES = includes

SRCS_BUILTIN = $(addprefix builtin/, cd.c cd_change_pwd_oldpwd.c cd_find_path.c \
					echo.c env.c exit.c exit_util.c export.c make_hash_map.c \
					make_new_envp.c pwd.c unset.c)
SRCS_ERR = $(addprefix err_handle/, err_exit.c use_dir_safe.c use_fd_safe.c \
					use_file_safe.c use_heap_safe.c use_process_safe.c \
					use_write_getcwd_safe.c use_libft_safe.c)
SRCS_EXECUTE = $(addprefix execute/, execute.c execute_cmd.c execute_cmd_utils.c \
					execute_heredoc.c execute_heredoc_utils.c execute_minimal.c \
					execute_minimal_utils.c execute_pipe.c execute_redirection.c \
					execute_subshell.c execute_utils.c wait.c set_questionmark.c)
SRCS_PARSE = $(addprefix parse/, expand.c expand_filename.c expand_filename_utils.c \
					expand_param.c expand_word_split.c get_path_and_pattern.c \
					get_wild_card_str.c is_match.c join_quote_split.c parse_line.c \
					quote_split.c recursive_search_file.c syntax_err.c syntax_state.c \
					tl_basic_func.c tl_utils.c tokenize.c tokenize_state.c tokenize_utils.c \
					sort_matched_list.c)
SRCS_LIST = $(addprefix list/, list_add_node.c list_create_node.c list_delete_node.c \
					list_search_node.c list_utils.c)

SRCS := $(addprefix $(SRCS_DIR)/, main.c main_conf.c main_utils.c utils.c \
			$(SRCS_BUILTIN) $(SRCS_ERR) $(SRCS_EXECUTE) $(SRCS_PARSE) $(SRCS_LIST))

OBJS := $(SRCS:%.c=%.o)

$(NAME) :: $(LIB)
$(NAME) :: $(OBJS) $(CHANGABLE_HEADERS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(DEBUG_FLAGS) -o $(NAME) -lreadline -L/opt/homebrew/opt/readline/lib 

all : $(NAME)

#bonus : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I. -I$(LIB_DIR) -I$(INCLUDES) -I/opt/homebrew/opt/readline/include -c $< $(DEBUG_FLAGS) -o $@ 

$(LIB) :
	make -C $(LIB_DIR) all
	cp $(LIB_DIR)/$(LIB) $(LIB)

clean :
	make -C $(LIB_DIR) clean
	rm -rf $(OBJS) $(LIB)

fclean : clean
	make -C $(LIB_DIR) fclean
	rm -rf $(NAME) $(BONUS)

re :
	make fclean
	make all

.PHONY : clean fclean re
