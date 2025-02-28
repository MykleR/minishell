/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:25:55 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/28 00:49:08 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdio.h>

/////////////////////////////////////////////////////
//                  AST PRINTING                   //
//                 GENERATED BY AI                 //
//             NEEDS TO BE REFACTORED              //
/////////////////////////////////////////////////////

// ANSI color codes
#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_WHITE   "\x1b[37m"
#define BOLD          "\x1b[1m"

/**
 * Helper function to get string representation and color of AST node type
 */
static void ast_type_info(t_ast_type type, const char **str, const char **color)
{
    switch (type)
    {
        case AST_TOKEN:
            *str = "TOKEN";
            *color = COLOR_WHITE;
            break;
        case AST_AND:
            *str = "AND";
            *color = COLOR_YELLOW;
            break;
        case AST_OR:
            *str = "OR";
            *color = COLOR_YELLOW;
            break;
        case AST_PIPE:
            *str = "PIPE";
            *color = COLOR_BLUE;
            break;
        case AST_REDIR_IN:
            *str = "REDIR_IN";
            *color = COLOR_MAGENTA;
            break;
        case AST_REDIR_OUT:
            *str = "REDIR_OUT";
            *color = COLOR_MAGENTA;
            break;
        case AST_REDIR_APP:
            *str = "APPEND";
            *color = COLOR_MAGENTA;
            break;
        case AST_CMD:
            *str = "CMD";
            *color = COLOR_GREEN;
            break;
        case AST_SUBSHELL:
            *str = "SUBSHELL";
            *color = COLOR_CYAN;
            break;
        default:
            *str = "UNKNOWN";
            *color = COLOR_RED;
            break;
    }
}

static void print_cmd_args(t_cmd_expr *cmd, int indent)
{
    int i;
    
    for (i = 0; i < cmd->argc; i++)
    {
        printf("%*s└─ ARG[%d]: %s'%s'%s\n", 
               indent + 2, "", i, COLOR_CYAN, cmd->argv[i], COLOR_RESET);
    }
}

static void ast_print_recursive(t_ast *node, int indent)
{
    if (!node)
        return;

    const char *type_str;
    const char *color;
    
    // Get type info with color
    ast_type_info(node->type, &type_str, &color);

    // Print current node
    printf("%*s%s%s%s%s", indent, "", BOLD, color, type_str, COLOR_RESET);
    
    // Print additional node-specific information
    switch (node->type)
    {
        case AST_TOKEN:
            if (node->expr.token)
                printf(" (%s'%s'%s)", COLOR_CYAN, node->expr.token->val, COLOR_RESET);
            break;
            
        case AST_CMD:
            if (node->expr.cmd.argc > 0)
                printf(" [%s%s%s]", COLOR_CYAN, node->expr.cmd.argv[0], COLOR_RESET);
            break;
            
        case AST_REDIR_IN:
        case AST_REDIR_OUT:
        case AST_REDIR_APP:
            if (node->expr.redir.file)
                printf(" -> %s'%s'%s", COLOR_CYAN, node->expr.redir.file, COLOR_RESET);
            break;
            
        default:
            break;
    }
    printf("\n");
    
    // Print command arguments if it's a command node
    if (node->type == AST_CMD)
        print_cmd_args(&node->expr.cmd, indent);
    
    // Recursively print children
    switch (node->type)
    {
        case AST_AND:
        case AST_OR:
        case AST_PIPE:
        case AST_SUBSHELL:
            // Binary expressions
            if (node->expr.binary.left)
            {
                printf("%*s└─ %sLEFT%s:\n", indent + 2, "", BOLD, COLOR_RESET);
                ast_print_recursive(node->expr.binary.left, indent + 4);
            }
            if (node->expr.binary.right)
            {
                printf("%*s└─ %sRIGHT%s:\n", indent + 2, "", BOLD, COLOR_RESET);
                ast_print_recursive(node->expr.binary.right, indent + 4);
            }
            break;
            
        case AST_REDIR_IN:
        case AST_REDIR_OUT:
        case AST_REDIR_APP:
            // Redirection expressions
            if (node->expr.redir.next)
            {
                printf("%*s└─ %sCMD%s:\n", indent + 2, "", BOLD, COLOR_RESET);
                ast_print_recursive(node->expr.redir.next, indent + 4);
            }
            break;
        default:
            break;
    }
}

/**
 * Public function to print the AST
 */
void ast_print(t_ast *root)
{
    if (!root)
    {
        printf("%sEmpty AST (NULL)%s\n", COLOR_RED, COLOR_RESET);
        return;
    }
    
    printf("%sAST Structure:%s\n", BOLD, COLOR_RESET);
    ast_print_recursive(root, 0);
}
