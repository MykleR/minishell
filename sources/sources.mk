# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrouves <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 16:59:36 by mrouves           #+#    #+#              #
#    Updated: 2025/03/18 02:21:32 by mykle            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SOURCES		:=	main.c\
				shell.c\
				utils/errors.c\
				utils/signals.c\
				utils/safes.c\
				utils/expands_1.c\
				utils/expands_2.c\
				utils/environment.c\
				utils/heredoc.c\
				lexer/lexer.c\
				lexer/match_quoted.c\
				lexer/match_complex.c\
				lexer/match_double.c\
				lexer/match_single.c\
				parser/ast_print.c\
				parser/ast_utils.c\
				parser/ast_prods.c\
				parser/lalr_parse.c\
				parser/lalr_getters.c\
				execution/evaluation.c\
				execution/exec_cmd.c\
				execution/exec_path.c\
				execution/exec_pipe.c\
				execution/exec_redir.c\
				execution/exec_logic.c\
				builtins/builtin_cd.c\
				builtins/builtin_exit.c\
				builtins/builtin_echo.c\
				builtins/builtin_unset.c\
				builtins/builtin_pwd.c\
				builtins/builtin_env.c\
				builtins/builtin_export.c\
