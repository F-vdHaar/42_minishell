/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:13:35 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/18 19:20:45 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	write(1, "I AM ALIVE!\n", 13);
	return (EXIT_SUCCESS);
}
