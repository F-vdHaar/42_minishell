/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:56:45 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/09 13:49:13 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_tokens(t_token *head)
{
	while (head)
	{
		// TODO WP  Logging
	//	log_output("Token: [%s]\n", head->value);
		ft_printf("Token: [%s]\n", head->value);
		head = head->next;
	}
}

void	print_operator(t_command *cmd)
{
	if (cmd->operator == AND)
		log_output("&&\n");
	else if (cmd->operator == OR)
		log_output("||\n");
	else if (cmd->operator == PIPE)
		log_output("|\n");
	else if (cmd->operator == SEMICOLON)
		log_output(";\n");
	else if (cmd->operator == NONE)
		log_output("NONE\n");
	
}

void	print_redirections(t_redirection *redir)
{
	while (redir)
	{
		log_output("  Redirection: ");
		if (redir->type == REDIR_IN)
			log_output("< ");
		else if (redir->type == REDIR_OUT)
			log_output("> ");
		else if (redir->type == APPEND)
			log_output(">> ");
		else if (redir->type == HEREDOC)
			log_output("<< ");
		log_output("%s\n", redir->file);
		redir = redir->next;
	}
}


// COM while this shouls have used log_outout, something gets messed up then 
void print_commands(t_command *cmd)
{
    int i;

    printf("[print_commands]:");

    while (cmd)
    {
        printf("\n--Command--\n");
        if (cmd->args == NULL) {
            printf(" No arguments in this command.");
        } else
		{
            i = 0;
            while (i < cmd->argc)
            {
            
                if (cmd->args[i] == NULL) {
                    printf(" Argument %d is NULL.\n", i);
                } else {
                    printf(" Argument %d: %s\n", i, cmd->args[i]);
                }
				i++;
            }
        }
        printf("\nOperator: ");
        print_operator(cmd);

        printf("Redirection: ");
        print_redirections(cmd->redir);
        
        cmd = cmd->next;
    }
}
