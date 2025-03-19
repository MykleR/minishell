# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrouves <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 16:59:36 by mrouves           #+#    #+#              #
#    Updated: 2025/03/19 05:32:18 by mrouves          ###   ########.fr        #
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
				lexer/lexing_match.c\
				lexer/lexing_check.c\
				parser/ast_print.c\
				parser/ast_utils.c\
				parser/ast_prods.c\
				parser/lalr_parse.c\
				parser/lalr_getters.c\
				execution/_evaluation.c\
				execution/exec_cmd.c\
				execution/exec_path.c\
				execution/exec_pipe.c\
				execution/exec_redir.c\
				execution/exec_logic.c\
				execution/builtin_cd.c\
				execution/builtin_echo.c\
				execution/builtin_export.c\
				execution/builtin_others.c\
