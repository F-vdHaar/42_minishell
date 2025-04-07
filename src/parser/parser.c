

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

