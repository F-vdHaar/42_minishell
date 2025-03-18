/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:13:35 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/18 20:25:55 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	char	*input;

	(void)argc;
	(void)argv;
	input = NULL;
	if (argc != 1)
	{
		log_error("minishell does not want arguments");
		return (EXIT_FAILURE);
	}
	while (1)
	{
	}
	free(input);
	return (EXIT_SUCCESS);
}
