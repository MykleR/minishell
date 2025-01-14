# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrouves <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 18:27:35 by mrouves           #+#    #+#              #
#    Updated: 2025/01/14 17:19:39 by mrouves          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include sources/sources.mk
include sources/pretty_compile.mk

NAME 			:= minishell

DIR_HEADERS		:= headers
DIR_SOURCES		:= sources
DIR_OBJS		:= .objs
DIR_LIB			:= lib

DIR_LIBFT		:= $(DIR_LIB)/libft
LIBFT_INCLUDES	:= $(DIR_LIBFT)/headers
LIBFT			:= $(DIR_LIBFT)/libft.a

OBJS			:= $(addprefix $(DIR_OBJS)/, $(SOURCES:%.c=%.o))

CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror
IFLAGS			:= -I $(DIR_HEADERS) -I $(LIBFT_INCLUDES)
DIR_DUP			= mkdir -p $(@D)

all: $(NAME) $(OBJS)

$(NAME): $(OBJS) $(LIBFT)
	@$(call run_and_test, $(CC) $(CFLAGS) $(IFLAGS) $^ -o $@ -lreadline)
	@printf "$(BOLD)$@$(NO_COLOR) compiled $(OK_COLOR)successfully$(NO_COLOR)\n"

$(LIBFT):
	@$(MAKE) -C $(DIR_LIBFT) --no-print-directory -j

$(DIR_OBJS)/%.o: $(DIR_SOURCES)/%.c
	@$(DIR_DUP)
	@$(call run_and_test,$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@)

clean:
	@rm -rf $(DIR_OBJS)
	@printf "Cleaned $(BOLD)$(DIR_OBJS)$(NO_COLOR)\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@printf "Cleaned $(BOLD)$(NAME)$(NO_COLOR)\n"

re: fclean all

.PHONY: clean fclean re all
