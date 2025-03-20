/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:13:35 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/20 09:01:49 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_loop(void);

static void	minishell_loop(void)
{
	char		*input;
	t_command	*commands;
	int			flag_quit;

	flag_quit = 0;
	while (!flag_quit)
	{
		if (isatty(STDIN_FILENO))
			write(1, "> ", 3);
		input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			write(1, "\nExiting...\n", 12);
			break ;
		}
		if (input[ft_strlen(input) - 1] == '\n')
			input[ft_strlen(input) - 1] = '\0';
		if (*input)
		{
			commands = get_commands(input);
			flag_quit = execute_commands(commands);
			free_commands(commands);
		}
		free(input);
	}
}

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "--help", 6) == 0)
		{
			write(1, "Usage: ./minishell\n", 19);
			write(1, "This shell does not accept any arguments.\n", 43);
			return (EXIT_SUCCESS);
		}
		else if (ft_strncmp(argv[1], "--debug", 7) == 0)
			enable_debug_mode();
		else
		{
			write(2, "Invalid argument. Type --help\n", 31);
			return (EXIT_FAILURE);
		}
	}
	else
		log_output("Running in non-interactive mode\n");
	minishell_loop();
	return (EXIT_SUCCESS);
}
