/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:13:35 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/08 16:01:38 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_loop(void);
static int	handle_input(char *input);

static int	handle_input(char *input)
{
	t_token		*tokens;
	t_command	*commands;

	if (g_debug_mode != 2)
	{
		if (!input)
		return (EXIT_FAILURE);
		tokens = tokenize_arguments(input);
		if (!tokens)
		{
			log_error("[handle_input] Tokenization failed");
			return (EXIT_FAILURE);
		}
		if (g_debug_mode)
		print_tokens(tokens);
		commands = parse_tokens(tokens, NULL);
		if (!commands)
		{
			log_error("[handle_input] Parsing tokens failed");
			free_tokens(tokens);
			return (EXIT_FAILURE);
		}
	}
	if (g_debug_mode == 2)
		commands = generated_commands();
	if (g_debug_mode)
		print_commands(commands);
	execute_commands(commands);
	//free_tokens(tokens);
	//tokens = NULL;
	//free_commands(commands);
	//commands = NULL;
	return (EXIT_SUCCESS);
}

static void	minishell_loop(void)
{
	char		*input;
	int			flag_quit;
	int			flag_interactive;

	flag_quit = 0;
	flag_interactive = isatty(STDIN_FILENO);
	while (!flag_quit)
	{
		if (flag_interactive)
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
			handle_input(input);
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
		else if (ft_strncmp(argv[1], "--debug1", 8) == 0)
		{
			enable_debug_mode(1);
		}
		else if (ft_strncmp(argv[1], "--debug2", 8) == 0)
		{
			enable_debug_mode(2);
		}
		else if (ft_strncmp(argv[1], "--debug", 7) == 0)
		{
			enable_debug_mode(1);
		}
		else
		{
			write(2, "Invalid argument. Type --help\n", 31);
			return (EXIT_FAILURE);
		}
		if (init_log_session("output_log.txt") != 0) {
				// If log session fails, handle the error
				write(1, "Error: Log file couldn't be opened\n", 36);
				return 1;
			}
	}
	else
	log_output("Running in non-interactive mode\n");
	minishell_loop();
	close_log_session();
	return (EXIT_SUCCESS);
}
