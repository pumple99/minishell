# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 15:20:31 by seunghoy          #+#    #+#              #
#    Updated: 2023/05/04 20:26:06 by dongyshi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
BONUS := minishell_bonus
CC := cc
CFLAGS := -Werror -Wall -Wextra
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

SRCS_BUILTIN_B = $(addprefix builtin/, cd_bonus.c cd_change_pwd_oldpwd_bonus.c \
					cd_find_path_bonus.c echo_bonus.c env_bonus.c exit_bonus.c \
					exit_util_bonus.c export_bonus.c make_hash_map_bonus.c \
					make_new_envp_bonus.c pwd_bonus.c unset_bonus.c)
SRCS_ERR_B = $(addprefix err_handle/,err_exit_bonus.c use_dir_safe_bonus.c \
					use_fd_safe_bonus.c use_file_safe_bonus.c use_heap_safe_bonus.c \
					use_libft_safe_bonus.c use_process_safe_bonus.c use_write_getcwd_safe_bonus.c)
SRCS_EXECUTE_B = $(addprefix execute/, execute_bonus.c execute_cmd_bonus.c \
					execute_cmd_utils_bonus.c execute_heredoc_bonus.c execute_heredoc_utils_bonus.c \
					execute_minimal_bonus.c execute_minimal_utils_bonus.c execute_pipe_bonus.c \
					execute_redirection_bonus.c execute_subshell_bonus.c execute_utils_bonus.c \
					set_questionmark_bonus.c wait_bonus.c)
SRCS_PARSE_B = $(addprefix parse/, expand_bonus.c expand_filename_bonus.c \
					expand_filename_utils_bonus.c expand_param_bonus.c \
					expand_word_split_bonus.c get_path_and_pattern_bonus.c \
					get_wild_card_str_bonus.c is_match_bonus.c join_quote_split_bonus.c \
					parse_line_bonus.c quote_split_bonus.c recursive_search_file_bonus.c \
					sort_matched_list_bonus.c syntax_err_bonus.c syntax_state_bonus.c \
					tl_basic_func_bonus.c tl_utils_bonus.c tokenize_bonus.c tokenize_state_bonus.c \
					tokenize_utils_bonus.c)
SRCS_LIST_B = $(addprefix list/, list_add_node_bonus.c list_create_node_bonus.c list_delete_node_bonus.c \
					list_search_node_bonus.c list_utils_bonus.c)

SRCS := $(addprefix $(SRCS_DIR)/, main.c main_conf.c main_utils.c utils.c \
			$(SRCS_BUILTIN) $(SRCS_ERR) $(SRCS_EXECUTE) $(SRCS_PARSE) $(SRCS_LIST))

SRCS_B := $(addprefix $(SRCS_DIR)/, main_bonus.c main_conf_bonus.c main_utils_bonus.c utils_bonus.c \
			$(SRCS_BUILTIN_B) $(SRCS_ERR_B) $(SRCS_EXECUTE_B) $(SRCS_PARSE_B) $(SRCS_LIST_B))

OBJS := $(SRCS:%.c=%.o)

OBJS_B := $(SRCS_B:%.c=%.o)

$(NAME) :: $(LIB)
$(NAME) :: $(OBJS) $(CHANGABLE_HEADERS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(DEBUG_FLAGS) -o $(NAME) -lreadline -L/Users/dongyshi/.brew/opt/readline/lib

$(BONUS) :: $(LIB)
$(BONUS) :: $(OBJS_B) $(CHANGABLE_HEADERS)
	$(CC) $(CFLAGS) $(OBJS_B) $(LIB) $(DEBUG_FLAGS) -o $(BONUS) -lreadline -L/Users/dongyshi/.brew/opt/readline/lib

all : $(NAME)

bonus : $(BONUS)

%.o : %.c
	$(CC) $(CFLAGS) -I. -I$(LIB_DIR) -I$(INCLUDES) -I/Users/dongyshi/.brew/opt/readline/include -c $< $(DEBUG_FLAGS) -o $@ 

$(LIB) :
	make -C $(LIB_DIR) all
	cp $(LIB_DIR)/$(LIB) $(LIB)

clean :
	make -C $(LIB_DIR) clean
	rm -rf $(OBJS) $(OBJS_B) $(LIB)

fclean : clean
	make -C $(LIB_DIR) fclean
	rm -rf $(NAME) $(BONUS)

re :
	make fclean
	make all

.PHONY : clean fclean re all bonus
