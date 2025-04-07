/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:03:58 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/07 16:41:23 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>

void	log_error_msg(const char *message)
{
	log_error("%s\n", message);
}

void	log_error(const char *fmt, ...)
{
	int		fd;
	va_list	args;

	va_start(args, fmt);
	ft_printf("Error: ");
	ft_dprintf(STDERR_FILENO, fmt, args);
	va_end(args);
	fd = open("error_log.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_printf("Error: Failed to open log file\n");
		return ;
	}
	va_start(args, fmt);
	ft_dprintf(fd, fmt, args);
	va_end(args);
	close(fd);
}
