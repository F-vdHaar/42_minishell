/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:00:37 by fvon-der          #+#    #+#             */
/*   Updated: 2025/04/10 18:55:07 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.h"

int	g_debug_mode = DEBUG_NONE;

void	enable_debug_mode(int i)
{
	g_debug_mode = i;
}

// Function to log the debug modes enabled
void log_debug_mode() {
	if (g_debug_mode == DEBUG_NONE) {
		ft_printf("Debugging is off\n");
	} else {
		ft_printf("Enabled debug modes: ");
		if (g_debug_mode & DEBUG_GEN_ENV) ft_printf("GEN_ENV ");
		if (g_debug_mode & DEBUG_GEN_TOKENS) ft_printf("GEN_TOKENS ");
		if (g_debug_mode & DEBUG_GEN_COMMANDS) ft_printf("GEN_COMMANDS ");
		if (g_debug_mode & DEBUG_GEN_EXECUTION) ft_printf("GEN_EXECUTION ");
		if (g_debug_mode & DEBUG_GEN_QUOTES) ft_printf("GEN_QUOTES ");
		if (g_debug_mode & DEBUG_GEN_REDIRECTS) ft_printf("GEN_REDIRECTS ");
		if (g_debug_mode & DEBUG_GEN_PIPELINES) ft_printf("GEN_PIPELINES ");
		if (g_debug_mode & DEBUG_GEN_ASSIGNMENTS) ft_printf("GEN_ASSIGNMENTS ");
		if (g_debug_mode & DEBUG_EXEC_FORK) ft_printf("EXEC_FORK ");
		if (g_debug_mode & DEBUG_EXEC_WAIT) ft_printf("EXEC_WAIT ");
		if (g_debug_mode & DEBUG_EXEC_PATH) ft_printf("EXEC_PATH ");
		if (g_debug_mode & DEBUG_EXEC_FD) ft_printf("EXEC_FD ");
		if (g_debug_mode & DEBUG_EXEC_SIG) ft_printf("EXEC_SIG ");
		if (g_debug_mode & DEBUG_MEM_ALLOC) ft_printf("MEM_ALLOC ");
		if (g_debug_mode & DEBUG_RESOURCES) ft_printf("RESOURCES ");
		if (g_debug_mode & DEBUG_JOB_CONTROL) ft_printf("JOB_CONTROL ");
		if (g_debug_mode & DEBUG_BG_FG) ft_printf("BG_FG ");
		if (g_debug_mode & DEBUG_SIG_HANDLER) ft_printf("SIG_HANDLER ");
		if (g_debug_mode & DEBUG_EXIT_STATUS) ft_printf("EXIT_STATUS ");
		if (g_debug_mode & DEBUG_CMD_SUBST) ft_printf("CMD_SUBST ");
		if (g_debug_mode & DEBUG_VAR_EXPANSION) ft_printf("VAR_EXPANSION ");
		if (g_debug_mode & DEBUG_SYS_INFO) ft_printf("SYS_INFO ");
		if (g_debug_mode & DEBUG_PATH) ft_printf("PATH ");
		ft_printf("\n");
	}
}