

#include "minishell.h"

// Function to duplicate arguments and handle memory allocation.
char **duplicate_args(char **args)
{
	int i;
	int count;
	char **copy;

	i = 0;
	count = 0;
	log_output("[duplicate_args]");
	if (!args)
		return (log_error("[duplicate_args] NULL args provided"), NULL);
	while (args[count])
		count++;
	copy = ft_calloc(count + 1, sizeof(char *));
	if (!copy)
		return (log_error("[duplicate_args] malloc failed"), NULL);
	while (i < count)
	{
		copy[i] = ft_strdup(args[i]);
		if (!copy[i])
		{
			log_error("[duplicate_args] ft_strdup failed for argument");
			while (i-- > 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

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

// Parses a single command, tokenizing arguments and determining the operator.
t_command *parse_command(char *cmd_str)
{
	t_command *head;
	char **args;
	t_operator operator;

	log_output("[parse_commands]");
	head = NULL;
	args = tokenize_arguments(cmd_str);
	operator = determine_operator(cmd_str);
	head = NULL;
	if (add_command(&head, args, operator) == EXIT_FAILURE)
	{
		log_error("[parse_command] Failed to add command");
		return (NULL);
	}
	if (g_debug_mode)
		print_tokens(args); 
	return (head);
}

// Main function to get commands from input, parsing and validating.
t_command *get_commands(char *input)
{
	t_command	*head;
	t_token		*tokens;
	t_token		*current;
	
	head  = NULL;
	log_output("[get_commands]");
	log_output(input);
	if (validate_input(input) == EXIT_FAILURE)
	{
		log_error("[get_commands] Input validation failed");
		return (NULL);
	}
	tokens = tokenize_arguments(input);
	if (!tokens)
	{
		log_error("[get_commands] Tokenization failed");
		return (NULL);
	}
	current = tokens;
	while (current)
	{
		log_output("[get_commands]Parsing command");
		if (!add_command(&head, duplicate_args(current->value), current->type))
		{
			log_error("[get_commands] Failed to add command");
			free_tokens(tokens);
			return (NULL);
		}
		current = current->next;
	}
	free_tokens(tokens);
	log_output("[get_commands] Command parsing complete");
	return (head);
}

void print_tokens(t_token *head)
{
	while (head)
	{
		printf("Token: [%s]\n", head->value);
		head = head->next;
	}
}
