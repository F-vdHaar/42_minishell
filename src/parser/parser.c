

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
	while (input[i] != '\0')
	{
		if (input[i] == '\n')
			return (EXIT_FAILURE);
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
	args = tokenize_arguments(cmd_str);
	operator = determine_operator(cmd_str);
	head = NULL;
	if (add_command(&head, args, operator) == EXIT_FAILURE)
	{
		log_error("[parse_command] Failed to add command");
		return (NULL);
	}
	return (head);
}

// Main function to get commands from input, parsing and validating.
t_command *get_commands(char *input)
{
	t_command *head = NULL;
	char *cmd_str;

	log_output("[get_commands]");
	if (validate_input(input) == EXIT_FAILURE)
	{
		log_error("[get_commands] Input validation failed");
		return (NULL);
	}
	cmd_str = strtok(input, ";");
	while (cmd_str != NULL)
	{
		log_output("[get_commands]Parsing command");
		head = parse_command(cmd_str);
		if (!head)
			break;
		cmd_str = strtok(NULL, ";");
	}

	log_output("[get_commands] Command parsing complete");
	return (head);
}
