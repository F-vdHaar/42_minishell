/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/utils/gen_utils.c
/*   Created: 2025/03/18 19:51:18 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/04 18:20:36 by fvon-der         ###   ########.fr       */
=======
/*   Created: 2025/04/07 16:35:01 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/07 17:16:21 by fvon-de          ###   ########.fr       */
>>>>>>> 83f9e24 (Better Logging):src/utils/utils/utils_debug.c
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>

static int	g_debug_mode = 0;

void	enable_debug_mode(void)
{
	g_debug_mode = 1;
	log_output("Debug mode enabled\n");
}

void	log_out_msg(const char *message)
{
	log_output("%s\n", message);
}

void	log_output(const char *fmt, ...)
{
	const char	*debug_prefix = "[DEBUG] ";
	int			fd;
	va_list		args;

	if (g_debug_mode)
	{
		write(STDERR_FILENO, debug_prefix, 8);
		va_start(args, fmt);
		ft_dprintf(STDERR_FILENO, fmt, args);
		va_end(args);
		write(STDERR_FILENO, "\n", 1);
		fd = open("output_log.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
		{
			ft_dprintf(STDERR_FILENO, "Error: Failed to open output_log.txt\n");
			return ;
		}
		va_start(args, fmt);
		ft_dprintf(fd, debug_prefix);
		ft_dprintf(fd, fmt, args);
		va_end(args);
		write(fd, "\n", 1);
		close(fd);
	}
}
