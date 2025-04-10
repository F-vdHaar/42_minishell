/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:43:47 by fvon-de           #+#    #+#             */
/*   Updated: 2025/04/10 18:34:48 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h" 
#include <utils.h>

typedef int (*t_builtin_func)(int argc, char **argv);

typedef struct s_builtin {
    char *name;
	t_builtin_func func;
} t_builtin;


t_builtin_func  get_builtin(char *name);
// DUMMY
int             builtin_cd(int argc, char **argv);
int             builtin_echo(int argc, char **argv);
int             builtin_exit(int argc, char **argv);

#endif