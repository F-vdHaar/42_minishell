/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:51:18 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/04 18:20:36 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_debug_mode = 0;

void	log_error(const char *message)
{
	int	fd;

	ft_printf("Error: %s\n", message);
	fd = open("error_log.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_printf("Error: Failed to open log file\n");
		return ;
	}
	ft_printf("Error: %s\n", message);
	close(fd);
}

void	log_output(const char *message)
{
	const char	*debug_prefix;

	if (g_debug_mode)
	{
		debug_prefix = "[DEBUG] ";
		write(STDERR_FILENO, debug_prefix, 8);
		while (*message)
		{
			write(STDERR_FILENO, message, 1);
			message++;
		}
		write(STDERR_FILENO, "\n", 1);
	}
}

void	enable_debug_mode(void)
{
	g_debug_mode = 1;
	log_output("Debug mode enabled\n");
}
