# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrouves <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 16:59:36 by mrouves           #+#    #+#              #
#    Updated: 2025/03/03 23:56:32 by mrouves          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SOURCES		:=	main.c\
				utils.c\
				shell/shell.c\
				shell/shell_rl.c\
				lexer/lexer.c\
				lexer/lexer_utils.c\
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
				execution/exec_pipe.c\
				execution/exec_redir.c\
				execution/exec_logic.c\
