/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:46:21 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/21 06:39:58 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_operator
{
	NONE,
	PIPE,			// |
	REDIR_IN,		// <
	REDIR_OUT,		// >
	APPEND,			// >>
	HEREDOC,		// <<
	AND,			// &&
	OR,				// ||
	BACKGROUND,		// &   -- e.g.: sleep 5 & wait
	SEMICOLON,		// ; Seq exec -- e.g.: echo "Hello"; ls -l
	SUBSHELL_OPEN,	// (   Subshells  -- e.g.: (cd /tmp && ls)
	SUBSHELL_CLOSE// )   Subshells
}	t_operator;

t_operator determine_operator(char *cmd_str);


char **duplicate_args(char **args);
#endif