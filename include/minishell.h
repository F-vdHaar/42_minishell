/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:16:11 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/20 13:41:00 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h" 
# include "ft_printf.h"
# include "get_next_line.h"

# include "parser.h"

typedef struct s_command
{
	char				**args;
	int					argc;
	t_operator			operator;
	struct s_command	*next;
}	t_command;

extern int	g_debug_mode;

// gen_utils
void		log_error(const char *message);
void		enable_debug_mode(void);
void		log_output(const char *message);

// Commands ALL DUMMY
t_command	*new_command(char **args, t_operator operator);
int			add_command(t_command **head, char **args, t_operator operator);
void		free_commands(t_command *head);
int			execute_commands(t_command *commands);
t_command	*get_commands(char *input);

#endif