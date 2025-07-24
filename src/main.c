/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:06:14 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/24 22:04:47 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal_status = 0;


void get_signal_exit(t_minishell *minishell)
{
	if (g_signal_status == SIGINT)
	{
		minishell->last_exit_status = 130;
		g_signal_status = 0;
	}
	else if (g_signal_status == SIGQUIT)
	{
		g_signal_status = 0;
	}
}

static void	minishell_loop(t_minishell *minishell)
{
	while (1)
	{
		setup_signal_handlers();
		get_signal_exit(minishell);
		minishell->input = get_prompt_input(minishell);
		if (!minishell->input)
		{
			exit_minishell(minishell);
		}
		tokenization(minishell);
		if (syntax_analysis(minishell) == 1)
			continue ;

		minishell->last_exit_status = execution(minishell);
		free_cmds(&(minishell->cmd_pipelines)); /// ONLY FOR DEBUGGING WITHOUT EXECUTION
		//print_environ(minishell->environment);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	initialize_minishell(&minishell, envp);
	minishell_loop(&minishell);
	return (0);
}
