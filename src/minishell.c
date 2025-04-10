/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:13:35 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/10 19:14:15 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	minishell_loop(char **envp);
static t_command	*handle_input(char *input, t_env *env_list);

static t_command	*handle_input(char *input, t_env *env_list)
{
	t_token		*tokens = NULL;
	t_command	*commands = NULL;

	// Debug mode: inject predefined commands
	if (g_debug_mode & DEBUG_GEN_COMMANDS)
	{
		log_output("DEBUG_GEN_COMMANDS: Using generated command structure.");
		return generated_commands(); // Early return – nothing else needed
	}
	if (g_debug_mode & DEBUG_GEN_TOKENS)
	{
		log_output("DEBUG_GEN_TOKENS: Using generated token list.");
		tokens = generated_tokens();
	}
	else
	{
		if (!input)
			return NULL;

		tokens = tokenize_arguments(input);
		if (!tokens)
		{
			log_error("[handle_input] Tokenization failed");
			return NULL;
		}

		if (g_debug_mode & DEBUG_GEN_TOKENS)
		{
			log_output("DEBUG_GEN_TOKENS: Tokenized input: \"%s\"\n", input);
			print_tokens(tokens);
		}
	}
	if (g_debug_mode & DEBUG_GEN_ENV)
		print_env(env_list);
	if (tokens)
		expand_tokens(&tokens, env_list);
	if (g_debug_mode & DEBUG_VAR_EXPANSION)
		print_tokens(tokens);
	commands = parse_tokens(tokens, NULL);
	if (!commands)
	{
		log_error("[handle_input] Parsing tokens failed");
		free_tokens(tokens);
		return NULL;
	}
	if (g_debug_mode & DEBUG_GEN_COMMANDS)
		print_commands(commands);

	//free_tokens(tokens);
	return commands;
}



static void	minishell_loop(char **envp)
{
	char		*input;
	int			flag_quit = 0;
	int			flag_interactive = isatty(STDIN_FILENO);
	t_env		*env_list;
	t_command	*commands = NULL;

	// Init environment (debug or real)
	if (g_debug_mode & DEBUG_GEN_ENV)
	{
		log_output("DEBUG_GEN_ENV: Using generated environment.");
		env_list = generated_env();
	}
	else
	{
		env_list = init_env(envp);
	}

	while (!flag_quit)
	{
		if (flag_interactive)
			write(STDOUT_FILENO, "> ", 2);

		input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			write(STDOUT_FILENO, "\nExiting...\n", 12);
			break;
		}

		// Trim newline
		size_t len = ft_strlen(input);
		if (len > 0 && input[len - 1] == '\n')
			input[len - 1] = '\0';

		// Process input if not empty
		if (*input)
		{
			commands = handle_input(input, env_list);

			if (commands)
			{
				if (g_debug_mode & DEBUG_GEN_EXECUTION)
					log_output("DEBUG_GEN_EXECUTION: About to execute parsed commands...");

				execute_commands(commands);
				free(commands);
			}
		}

		free(input);
	}
}



int main(int argc, char *argv[], char **envp)
{
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "--help", 6) == 0)
		{
			write(1, "Usage: ./minishell [debug_level]\n", 33);
			write(1, "Debug levels:\n", 14);
			write(1, "--debug 1  : General debug mode\n", 31);
			write(1, "--debug 2  : Parse Token debug\n", 31);
			write(1, "--debug 3  : Parse Command debug\n", 33);
			write(1, "--debug 4  : Executor debug\n", 28);
			write(1, "--debug 5  : Expander debug\n", 29);
			return (EXIT_SUCCESS);
		}
		else if (ft_strncmp(argv[1], "--debug", 7) == 0)
		{
			if (argc > 2)
			{
				int debug_level = ft_atoi(argv[2]);  
				if (debug_level >= 1 && debug_level <= 5)
				{
					ft_printf("Debug mode : %d\n", debug_level);
					enable_debug_mode(debug_level); 
				}
				else
				{
					write(2, "Invalid debug level. Type --help for usage.\n", 45);
					return (EXIT_FAILURE);
				}
			}
			else
			{
				write(2, "Missing debug level argument. Type --help for usage.\n", 55);
				return (EXIT_FAILURE);
			}
		}
		else
		{
			write(2, "Invalid argument. Type --help\n", 31);
			return (EXIT_FAILURE);
		}
		if (g_debug_mode != 0)
		{
			if (init_log_session("output_log.txt") != 0) {
				write(1, "Error: Log file couldn't be opened\n", 36);
				enable_debug_mode(0);
			}
		}
	}
	else
	{
		log_output("Running in non-interactive mode\n");
	}
	log_debug_mode();
	minishell_loop(envp);
	close_log_session();
	return (EXIT_SUCCESS);
}
