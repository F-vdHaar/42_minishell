

#include "minishell.h"



int validate_input(char *input)
{
	int i;
	
	i = 0;
	log_output("[validate_input]");
	if (!input || *input == '\0')
		return (log_error("[validate_input] Empty input"), EXIT_FAILURE);
	while (input[i] != '\0')
	{
		if (input[i] == '\n')
			return (log_error("[validate_input] new line"), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}


void print_tokens(t_token *head)
{
	while (head)
	{
		printf("Token: [%s]\n", head->value);
		head = head->next;
	}
}

void	print_commands(t_command *commands)
{
	int				i;
	t_redirection	*redir;
    
	printf("Parsed Commands:\n");
	while (commands)
	{
        printf("-------------------------\n");
		printf("Command: ");
		i = 0;
		while (i < commands->argc)
		{
			printf("%s ", commands->args[i]);
			i++;
		}
		printf("\n");
		if (commands->operator != NONE)
		{
			printf("Operator: ");
			if (commands->operator == AND)
				printf("&& ");
			else if (commands->operator == OR)
				printf("|| ");
			else if (commands->operator == PIPE)
				printf("| ");
			else if (commands->operator == SEMICOLON)
				printf("; ");
			printf("\n");
		}
		redir = commands->redir;
		while (redir)
		{
			printf("  Redirection: ");
			if (redir->type == REDIR_IN)
				printf("< ");
			else if (redir->type == REDIR_OUT)
				printf("> ");
			else if (redir->type == APPEND)
				printf(">> ");
			else if (redir->type == HEREDOC)
				printf("<< ");
			else
				printf("? ");
			printf("%s\n", redir->file);
			redir = redir->next;
		}
		commands = commands->next;
	}
}